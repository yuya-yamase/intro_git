/* 2.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Vehicle Status Viewer / Toyota IPC/MET Warning Chime                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define WCHIME_REQ_CFG_C_MAJOR                   (2)
#define WCHIME_REQ_CFG_C_MINOR                   (1)
#define WCHIME_REQ_CFG_C_PATCH                   (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "wchime_cfg_private.h"

#include "veh_opemd.h"

#include "alert.h"
#if 0   /* BEV Rebase provisionally */
#include "sbltsync.h"

#include "mcst.h"
#endif   /* BEV Rebase provisionally */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((WCHIME_REQ_CFG_C_MAJOR != WCHIME_CFG_H_MAJOR) || \
     (WCHIME_REQ_CFG_C_MINOR != WCHIME_CFG_H_MINOR) || \
     (WCHIME_REQ_CFG_C_PATCH != WCHIME_CFG_H_PATCH))
#error "wchime_req_cfg.c and wchime_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (WCHIME_REQBIT_NUM_WORD > WCHIME_REQBIT_NWORD_MAX)
#error "WCHIME_REQBIT_NUM_WORD shall be less than or equal to WCHIME_REQBIT_NWORD_MAX."
#endif

#if (WCHIME_NUM_REQ > WCHIME_REQ_IDX_UPLMT)
#error "WCHIME_NUM_REQ shall be less than or equal to WCHIME_REQ_IDX_UPLMT."
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define WCHIME_NUM_OPEMD                         (2U)                               /* IG-OFF, IG-ON.                                */

#define WCHIME_WT_TIM_NOTHING                    (0U    / WCHIME_TICK)              /* Waiting time : Nothing.                       */
#define WCHIME_WT_TIM_OTHER_TO_APP               (500U  / WCHIME_TICK)              /* Waiting time :  500ms.                        */
#define WCHIME_WT_TIM_APP_TO_OTHER               (1000U / WCHIME_TICK)              /* Waiting time : 1000ms.                        */

#define WCHIME_SW_WAIT_EXCPT_NUM                 (5U)                               /* Number of exception function of wait time.    */

#define WCHIME_SBLT_BZ_NUM                       (4U)                               /* Number of SEAREM buzzer.                      */
#define WCHIME_CSR_BZ_NUM                        (12U)                              /* Number of CLESON buzzer.                      */
#define WCHIME_TURHAZ_BZ_NUM                     (6U)                               /* Number of TURHAZ buzzer.                      */

#define WCHIME_REQ_SEL_APP                       (0x01U)                            /* Bit0 : REQ_SEL  = APP buzzer.                 */
#define WCHIME_REQ_NEXT_APP                      (0x02U)                            /* Bit1 : REQ_NEXT = APP buzzer.                 */
#define WCHIME_REQ_OTHER_TO_APP                  (WCHIME_REQ_NEXT_APP)              /* Other buzzer -> APP buzzer.                   */
#define WCHIME_REQ_APP_TO_OTHER                  (WCHIME_REQ_SEL_APP)               /* APP buzzer   -> Other buzzer.                 */

#define WCHIME_VOL_CLESON_CHANGEABLE             (254U)                             /* Clearance sonar Changeable volume.            */
#define WCHIME_VOL_RCTA_CHANGEABLE               (255U)                             /* RCTA            Changeable volume.            */

#define WCHIME_VOL_MINIMUM_CHANGEABLE            (WCHIME_VOL_CLESON_CHANGEABLE)     /* Minimum         Changeable volume.            */

#if (WCHIME_NUM_VOL >= WCHIME_VOL_MINIMUM_CHANGEABLE)
#error "WCHIME_NUM_VOL shall be less than WCHIME_VOL_MINIMUM_CHANGEABLE."
#endif

#define WCHIME_CSR_VOL_LIST_NUM                  (13U)                              /* Number of CLESON volume list.                 */

#define WCHIME_CSR_VOL_NUM                       (8U)                               /* Number of CLESON volume.                      */

#define WCHIME_CSR_VOL_INDEX_0                   (0U)                               /* CLESON volume index 0.                        */
#define WCHIME_CSR_VOL_INDEX_1                   (1U)                               /* CLESON volume index 1.                        */
#define WCHIME_CSR_VOL_INDEX_2                   (2U)                               /* CLESON volume index 2.                        */
#define WCHIME_CSR_VOL_INDEX_3                   (3U)                               /* CLESON volume index 3.                        */
#define WCHIME_CSR_VOL_INDEX_4                   (4U)                               /* CLESON volume index 4.                        */
#define WCHIME_CSR_VOL_INDEX_5                   (5U)                               /* CLESON volume index 5.                        */
#define WCHIME_CSR_VOL_INDEX_6                   (6U)                               /* CLESON volume index 6.                        */
#define WCHIME_CSR_VOL_INDEX_7                   (7U)                               /* CLESON volume index 7.                        */
/* stub */
#define WCHIME_VOL_CSTM                          (3U)                               /* Number of Meter Alarm Volume Customized       */
/* stub end */


/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U1   (* const   fp_u1_chk_func)(const U1 u1_a_REQ_SEL, const U1 u1_a_REQ_NEXT); /* Check function for exception wait time.       */
    U1              u1_wait;                                                        /* TRUE: Wait is necessary, FALSE: Unnecessary.  */
    U2              u2_time;                                                        /* Exception wait time.                          */
}ST_WCHIME_SW_WAIT_EXCPT_CHK;

typedef struct{
    U1         u1_reqid;                                                          /* ID of buzzer request (WCHIME_REQ_x).            */
    U1         u1_req_vol[WCHIME_CSR_VOL_NUM];                                    /* Volume kind of CLESON buzzer(WCHIME_VOL_CSR_x). */
}ST_WCHIME_CSR_VOL;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U4                           u4_gp_wchime_reqbit[WCHIME_REQBIT_NUM_WORD]; /* Bitmap for buzzer request.                              */
U4                           u4_gp_wchime_evtbit[WCHIME_REQBIT_NUM_WORD]; /* Bitmap for event(single) buzzer request.                */
U4                           u4_gp_wchime_evtmsk[WCHIME_REQBIT_NUM_WORD]; /* Bit mask to excludes requests for the same priority.    */
                                                                          /* or lower-priority event (Single) buzzer.                */
U2                           u2_gp_wchime_wt_tim[WCHIME_NUM_CH];          /* Result of wait time(silent duration) at last judgement. */

static U1                    u1_s_wchime_rcta_vol;                        /* Last volume kind of RCTA.                               */

U1                           u1_g_wchime_silencetime_flag;                /*  silencetime_flag                                       */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1   u1_s_wChimeCfgSwExcptOtherToApp(const U1 u1_a_REQ_SEL, const U1 u1_a_REQ_NEXT);
static U1   u1_s_wChimeCfgSwExcptAppToOther(const U1 u1_a_REQ_SEL, const U1 u1_a_REQ_NEXT);
static U1   u1_s_wChimeCfgSwExcptSblt(const U1 u1_a_REQ_SEL, const U1 u1_a_REQ_NEXT);
static U1   u1_s_wChimeCfgSwExcptCsr(const U1 u1_a_REQ_SEL, const U1 u1_a_REQ_NEXT);
static U1   u1_s_wChimeCfgSwExcptTurhaz(const U1 u1_a_REQ_SEL, const U1 u1_a_REQ_NEXT);
static U1   u1_s_wChimeCfgClesonVolGet(const U1 u1_a_REQ_SEL);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U4                     u4_gp_WCHIME_REQBIT_SIN[WCHIME_REQBIT_NUM_WORD] = {                    /* Bitmap of single buzzer.      */
    (U4)0x00000980U,
    (U4)0x86480400U,
    (U4)0x17FFFE41U,
    (U4)0xFB438140U,
    (U4)0xF2D67E77U,
    (U4)0x7FFFFEFFU
};

const U4                     u4_gp_WCHIME_REQBIT_PRIFREE[WCHIME_REQBIT_NUM_WORD] = {               /* Bitmap of priority-free buzzer.*/
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x7E000000U
};
const U1                     u1_g_WCHIME_REQBIT_NUM_WORD = (U1)WCHIME_REQBIT_NUM_WORD;
const U1                     u1_g_WCHIME_NUM_REQ         = (U1)WCHIME_NUM_REQ;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U4              u4_sp_WCHIME_REQBIT_BAT_ON[WCHIME_REQBIT_NUM_WORD] = {               /* Bitmap of +B-ON start buzzer.   */
    (U4)0x00010000U,
    (U4)0x04080108U,
    (U4)0x12000000U,
    (U4)0x00000001U,
    (U4)0x011005E0U,
    (U4)0x7E00BDC0U
};

static const U4              u4_sp_WCHIME_REQBIT_IGN_ON[WCHIME_REQBIT_NUM_WORD] = {               /* Bitmap of IG-ON start buzzer.   */
    (U4)0xFFFFFFFFU,
    (U4)0xFFFFFFFFU,
    (U4)0xFFFFFFFFU,
    (U4)0xFFFFFFFFU,
    (U4)0xFFFFFF7FU,
    (U4)0x7FFFFFFFU
};

const U4 * const             u4p_gp_WCHIME_REQBIT_BY_OPEMD[WCHIME_NUM_OPEMD] = {
    &u4_sp_WCHIME_REQBIT_BAT_ON[0],  /* 0 : Battery-ON, IG-OFF. */
    &u4_sp_WCHIME_REQBIT_IGN_ON[0]   /* 1 : Battery-ON, IG-ON.  */
};
const U1                     u1_g_WCHIME_NUM_OPEMD = (U1)WCHIME_NUM_OPEMD;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Buzzer attribute to inform to the multimedia device                      */
const ST_WCHIME_MM_INFO      st_gp_WCHIME_BUZ_OUTPUT_INFO[WCHIME_NUM_REQ] = {
    /* Buzzer Level  */      /* Buzzer Length */     /* Emergency ON    */
    {(U1)WCHIME_BUZ_LV10,    (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_CO_PCS_TSTMD1         */
    {(U1)WCHIME_BUZ_LV10,    (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_PCS_TSTMD2         */
    {(U1)WCHIME_BUZ_LV10,    (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_PCS_TSTMD3         */
    {(U1)WCHIME_BUZ_LV10,    (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_PCS_TSTMD4         */
    {(U1)WCHIME_BUZ_LV10,    (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_PCS_TSTMD5         */
    {(U1)WCHIME_BUZ_LV10,    (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_PCS_TSTMD6         */
    {(U1)WCHIME_BUZ_LV10,    (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_BRK_TST_LRN        */
    {(U1)WCHIME_BUZ_LV10,    (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_BRK_TST_STRT       */
    {(U1)WCHIME_BUZ_LV10,    (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_BRK_TST_FIN        */
    {(U1)WCHIME_BUZ_LV10,    (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_FRRADA_CMP         */
    {(U1)WCHIME_BUZ_LV10,    (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_FRRADA_ERR         */
    {(U1)WCHIME_BUZ_LV9,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_PTS_RDY            */
    {(U1)WCHIME_BUZ_LV9,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMON },    /* WCHIME_REQ_IN_PCS                */
    {(U1)WCHIME_BUZ_LV9,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_ACC                */
    {(U1)WCHIME_BUZ_LV9,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_STEER_UNDRIVE      */
    {(U1)WCHIME_BUZ_LV8,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_LCS_APR            */
    {(U1)WCHIME_BUZ_LV8,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_DOA                */
    {(U1)WCHIME_BUZ_LV8,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_CO_CSR_FR_SD          */
    {(U1)WCHIME_BUZ_LV8,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_CSR_FR_MD          */
    {(U1)WCHIME_BUZ_LV8,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_CO_CSR_RR_SD          */
    {(U1)WCHIME_BUZ_LV8,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_CSR_RR_MD          */
    {(U1)WCHIME_BUZ_LV8,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_CO_CSR_FRRR_SD        */
    {(U1)WCHIME_BUZ_LV8,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_CSR_FRRR_MD        */
    {(U1)WCHIME_BUZ_LV8,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_CSR_RCTA           */
    {(U1)WCHIME_BUZ_LV7,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMON },    /* WCHIME_REQ_IN_PCS_PED            */
    {(U1)WCHIME_BUZ_LV7,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_FCTA_STEP_STOP     */
    {(U1)WCHIME_BUZ_LV7,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_EDSS_R04           */
    {(U1)WCHIME_BUZ_LV7,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_CSR_FR_LD          */
    {(U1)WCHIME_BUZ_LV7,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_CSR_RR_LD          */
    {(U1)WCHIME_BUZ_LV7,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_CSR_FRRR_LD        */
    {(U1)WCHIME_BUZ_LV7,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_DA                 */
    {(U1)WCHIME_BUZ_LV7,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_TCHAR_CYCL2        */
    {(U1)WCHIME_BUZ_LV6,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_EDSS_R03           */
    {(U1)WCHIME_BUZ_LV6,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMON },    /* WCHIME_REQ_IN_ADTJA_PTN6         */
    {(U1)WCHIME_BUZ_LV6,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_EIGCON_EG_PWROFF   */
    {(U1)WCHIME_BUZ_LV6,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_BATTRW             */
    {(U1)WCHIME_BUZ_LV6,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_SCB                */
    {(U1)WCHIME_BUZ_LV6,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_BSM                */
    {(U1)WCHIME_BUZ_LV6,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_LDA                */
    {(U1)WCHIME_BUZ_LV6,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_INFRA_INT          */
    {(U1)WCHIME_BUZ_LV6,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_SMASTA_INT3        */
    {(U1)WCHIME_BUZ_LV6,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_OAA_HFCT           */
    {(U1)WCHIME_BUZ_LV6,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_FCTA               */
    {(U1)WCHIME_BUZ_LV6,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_CSR_FR_FD          */
    {(U1)WCHIME_BUZ_LV6,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_CSR_RR_FD          */
    {(U1)WCHIME_BUZ_LV6,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_CSR_FRRR_FD        */
    {(U1)WCHIME_BUZ_LV6,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_TCHAR_CYCL1        */
    {(U1)WCHIME_BUZ_LV6,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_BRK_FLDLEAK        */
    {(U1)WCHIME_BUZ_LV6,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_STEER_STP          */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_SBLT_FMV           */
    {(U1)WCHIME_BUZ_LV5,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_ROLAWA_ENST_VRUN   */
    {(U1)WCHIME_BUZ_LV5,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_SBW_RJCT           */
    {(U1)WCHIME_BUZ_LV5,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_CO_NACCON             */
    {(U1)WCHIME_BUZ_LV5,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_CO_PEXI_HV_NDBW       */
    {(U1)WCHIME_BUZ_LV5,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_COOTEM             */
    {(U1)WCHIME_BUZ_LV5,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_CO_ACCHOL             */
    {(U1)WCHIME_BUZ_LV5,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_SBW_AUTOP          */
    {(U1)WCHIME_BUZ_LV5,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_RSA_SIGN_CAUTION2  */
    {(U1)WCHIME_BUZ_LV5,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_ESWUOC_REL         */
    {(U1)WCHIME_BUZ_LV5,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_ADTJA_PTN5         */
    {(U1)WCHIME_BUZ_LV5,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_PMAR               */
    {(U1)WCHIME_BUZ_LV5,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_PKBWAR             */
    {(U1)WCHIME_BUZ_LV5,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_CO_SOCLOW_HV          */
    {(U1)WCHIME_BUZ_LV5,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_APP_NONOPE_REQ2    */
    {(U1)WCHIME_BUZ_LV5,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_APP_NONOPE_REQ4    */
    {(U1)WCHIME_BUZ_LV5,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_OILPRE             */
    {(U1)WCHIME_BUZ_LV5,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_CO_SYSMAL_RNG_P       */
    {(U1)WCHIME_BUZ_LV5,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_CHAMAL_BAT_FAIL    */
    {(U1)WCHIME_BUZ_LV5,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_SYSMAL_REMDST_0M   */
    {(U1)WCHIME_BUZ_LV5,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_SYSMAL_REQSTP      */
    {(U1)WCHIME_BUZ_LV5,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_ADTJA_PTN3         */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_EPB                */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_CO_EIGCON_IGOFF       */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_SPDL_DISACT        */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_SFTPOS_NML         */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_ACC_LSPDCNSL       */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_BEVR_DOUBLE        */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_LTA_CNCL           */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_SPDL_REJECT        */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_LCS_CNCL           */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_APP_DIS_ASSIST     */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_APP_CMPLT          */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_DCLDSP_OPERJCT     */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_LCS_ACK            */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_XMDRJT             */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_XMGRIP_DOUBLE      */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_X_MODE_DEACTIVATE  */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_X_MODE_REJECT      */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_BSTMOD_REJ         */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_DOA_RJCT           */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_MET_WRN_VOL_CSTM   */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_CO_ROLAWA_ENST_VSTP   */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_SBW_SPL_STATE      */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_DMC_LV2            */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_SFTPOS_REV         */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_SMASTA_INT2        */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_CO_SMASTA_CON         */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_SOCLOW_NPOS        */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_CO_STOSTA             */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_ACC_BRKREQ         */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_SBLT_LV2           */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_ACC_OVERSPD        */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_ACC_SHIFTREQ       */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_TPMS_CYCL          */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_SWS                */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_MINDSPWR_LV2       */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_BGLFSPD            */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_DR_OPN             */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_BRK_SYS_MAL        */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_BRK_SYS_NOOPE2     */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_BRK_SYS_NOOPE1     */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_STEER_LMT          */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_HYB_HT             */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_SBW_MAL            */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_SBW_MAL            */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_SYSMAL_REMDST_500M */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_SYSMAL_REMDST_1KM  */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_LTA_PTN2           */
    {(U1)WCHIME_BUZ_LV4,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_LTA_PTN3           */
    {(U1)WCHIME_BUZ_LV3,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_ADTJA_PTN4         */
    {(U1)WCHIME_BUZ_LV3,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_ADTJA_PTN7         */
    {(U1)WCHIME_BUZ_LV3,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_MINDSPWR_LV1       */
    {(U1)WCHIME_BUZ_LV3,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_SBLT_LV1           */
    {(U1)WCHIME_BUZ_LV3,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_SBLT               */
    {(U1)WCHIME_BUZ_LV3,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_GPF                */
    {(U1)WCHIME_BUZ_LV3,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_RSA_SIGN_CTN1_OTH  */
    {(U1)WCHIME_BUZ_LV3,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_RSA_SIGN_CTN1_LX   */
    {(U1)WCHIME_BUZ_LV3,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_CHKENG             */
    {(U1)WCHIME_BUZ_LV3,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_DMC_LV1            */
    {(U1)WCHIME_BUZ_LV3,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_ADTJA_PTN2         */
    {(U1)WCHIME_BUZ_LV3,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_SYSMAL_FAIL        */
    {(U1)WCHIME_BUZ_LV3,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_LTA_PTN1           */
    {(U1)WCHIME_BUZ_LV3,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_INFRA_SNGL         */
    {(U1)WCHIME_BUZ_LV3,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_MLT_MSG_OTH        */
    {(U1)WCHIME_BUZ_LV3,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_MLT_MSG_LX         */
    {(U1)WCHIME_BUZ_LV2,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_BKEY               */
    {(U1)WCHIME_BUZ_LV2,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_CO_LIGHT              */
    {(U1)WCHIME_BUZ_LV2,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_ACC_AUTOSTART      */
    {(U1)WCHIME_BUZ_LV2,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_SBW_RCPT           */
    {(U1)WCHIME_BUZ_LV2,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_BEVR_SINGLE        */
    {(U1)WCHIME_BUZ_LV2,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_XMGRIP_SINGLE      */
    {(U1)WCHIME_BUZ_LV2,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_X_MODE_ON          */
    {(U1)WCHIME_BUZ_LV2,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_DMODE_CHANGE       */
    {(U1)WCHIME_BUZ_LV2,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_LDA_HFCT           */
    {(U1)WCHIME_BUZ_LV2,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_BATINS             */
    {(U1)WCHIME_BUZ_LV2,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_TPMS_SINGLE        */
    {(U1)WCHIME_BUZ_LV2,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_TCHAR_SNGL         */
    {(U1)WCHIME_BUZ_LV2,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_LDA_WARN           */
    {(U1)WCHIME_BUZ_LV2,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_SMASTA_SNGL        */
    {(U1)WCHIME_BUZ_LV2,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_TOWWAR             */
    {(U1)WCHIME_BUZ_LV2,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_BATCOO             */
    {(U1)WCHIME_BUZ_LV2,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_TMN_LVN            */
    {(U1)WCHIME_BUZ_LV1,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_SMASTA_INT1        */
    {(U1)WCHIME_BUZ_LV1,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_BRK_APP3           */
    {(U1)WCHIME_BUZ_LV1,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_BRK_APP1           */
    {(U1)WCHIME_BUZ_LV1,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_IN_BRK_APP2           */
    {(U1)WCHIME_BUZ_LV1,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_ADTJA_PTN1         */
    {(U1)WCHIME_BUZ_LV1,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_BKHLD_NOTACT_R16   */
    {(U1)WCHIME_BUZ_LV1,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_BKHLD_NOTREL       */
    {(U1)WCHIME_BUZ_LV1,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_BKHLD_NOTACT_R07   */
    {(U1)WCHIME_BUZ_LV1,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_BKHLD_NOTACT_R08   */
    {(U1)WCHIME_BUZ_LV1,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_BKHLD_NOTACT_R17   */
    {(U1)WCHIME_BUZ_LV1,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_BKHLD_REL_R10      */
    {(U1)WCHIME_BUZ_LV1,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_BKHLD_REL_R11      */
    {(U1)WCHIME_BUZ_LV1,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_BKHLD_NOTACT_R13   */
    {(U1)WCHIME_BUZ_LV1,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_ACC_APPRVLSTART    */
    {(U1)WCHIME_BUZ_LV1,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_PERSET_SUC         */
    {(U1)WCHIME_BUZ_LV1,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_PERSET_FAIL        */
    {(U1)WCHIME_BUZ_LV1,     (U1)WCHIME_BUZ_LONG,    (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_CO_PERSET_DET         */
    {(U1)WCHIME_BUZ_LV0,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_RSA_CHG_SPLDLMT    */
    {(U1)WCHIME_BUZ_LV0,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_FMSEAT_MEM_SCS     */
    {(U1)WCHIME_BUZ_LV0,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_FMSEAT_MEM_REJ     */
    {(U1)WCHIME_BUZ_LV0,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_FMSEAT_ERS_INFO    */
    {(U1)WCHIME_BUZ_LV0,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_FMSEAT_MEM_CALL    */
    {(U1)WCHIME_BUZ_LV0,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_ESWUOC_RJCT        */
    {(U1)WCHIME_BUZ_LV0,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_SMASTA_SNGL2       */
    {(U1)WCHIME_BUZ_LV0,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_EV_RJCT_HEAT       */
    {(U1)WCHIME_BUZ_LV0,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_EV_RJCT_BAT        */
    {(U1)WCHIME_BUZ_LV0,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_EV_RJCT_SPD        */
    {(U1)WCHIME_BUZ_LV0,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_EV_RJCT_ACC        */
    {(U1)WCHIME_BUZ_LV0,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_EV_RJCT_OTH        */
    {(U1)WCHIME_BUZ_LV0,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_EV_DCTV_LWBAT      */
    {(U1)WCHIME_BUZ_LV0,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_EV_DCTV_SPD        */
    {(U1)WCHIME_BUZ_LV0,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_EV_DCTV_ACCL       */
    {(U1)WCHIME_BUZ_LV0,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_EV_DCTV            */
    {(U1)WCHIME_BUZ_LV0,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_TURHAZ_STA_LS      */
    {(U1)WCHIME_BUZ_LV0,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_TURHAZ_STA_MS      */
    {(U1)WCHIME_BUZ_LV0,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_TURHAZ_STA_HS      */
    {(U1)WCHIME_BUZ_LV0,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_TURHAZ_FIN_LS      */
    {(U1)WCHIME_BUZ_LV0,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF},    /* WCHIME_REQ_SI_TURHAZ_FIN_MS      */
    {(U1)WCHIME_BUZ_LV0,     (U1)WCHIME_BUZ_SHORT,   (U1)WCHIME_BUZ_EMOFF}     /* WCHIME_REQ_SI_TURHAZ_FIN_HS      */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Volume kind for each buzzer */
static const U1              u1_sp2_WCHIME_REQ_VOL_INFO[WCHIME_NUM_REQ][WCHIME_VOL_CSTM] = {
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_CO_PCS_TSTMD1         */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_PCS_TSTMD2         */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_PCS_TSTMD3         */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_PCS_TSTMD4         */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_PCS_TSTMD5         */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_PCS_TSTMD6         */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_BRK_TST_LRN        */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_BRK_TST_STRT       */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_BRK_TST_FIN        */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_FRRADA_CMP         */
    {  (U1)WCHIME_VOL_2400HZ_63DB,           (U1)WCHIME_VOL_2400HZ_63DB,           (U1)WCHIME_VOL_2400HZ_67DB            },    /* WCHIME_REQ_IN_FRRADA_ERR         */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_SI_PTS_RDY            */
    {  (U1)WCHIME_VOL_1600HZ_73DB,           (U1)WCHIME_VOL_1600HZ_73DB,           (U1)WCHIME_VOL_1600HZ_77DB            },    /* WCHIME_REQ_IN_PCS                */
    {  (U1)WCHIME_VOL_1600HZ_73DB,           (U1)WCHIME_VOL_1600HZ_73DB,           (U1)WCHIME_VOL_1600HZ_77DB            },    /* WCHIME_REQ_IN_ACC                */
    {  (U1)WCHIME_VOL_1600HZ_73DB,           (U1)WCHIME_VOL_1600HZ_73DB,           (U1)WCHIME_VOL_1600HZ_77DB            },    /* WCHIME_REQ_IN_STEER_UNDRIVE      */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_LCS_APR            */
    {  (U1)WCHIME_VOL_1600HZ_73DB,           (U1)WCHIME_VOL_1600HZ_73DB,           (U1)WCHIME_VOL_1600HZ_77DB            },    /* WCHIME_REQ_IN_DOA                */
    {  (U1)WCHIME_VOL_CLESON_CHANGEABLE,     (U1)WCHIME_VOL_CLESON_CHANGEABLE,     (U1)WCHIME_VOL_CLESON_CHANGEABLE      },    /* WCHIME_REQ_CO_CSR_FR_SD          */
    {  (U1)WCHIME_VOL_CLESON_CHANGEABLE,     (U1)WCHIME_VOL_CLESON_CHANGEABLE,     (U1)WCHIME_VOL_CLESON_CHANGEABLE      },    /* WCHIME_REQ_IN_CSR_FR_MD          */
    {  (U1)WCHIME_VOL_CLESON_CHANGEABLE,     (U1)WCHIME_VOL_CLESON_CHANGEABLE,     (U1)WCHIME_VOL_CLESON_CHANGEABLE      },    /* WCHIME_REQ_CO_CSR_RR_SD          */
    {  (U1)WCHIME_VOL_CLESON_CHANGEABLE,     (U1)WCHIME_VOL_CLESON_CHANGEABLE,     (U1)WCHIME_VOL_CLESON_CHANGEABLE      },    /* WCHIME_REQ_IN_CSR_RR_MD          */
    {  (U1)WCHIME_VOL_CLESON_CHANGEABLE,     (U1)WCHIME_VOL_CLESON_CHANGEABLE,     (U1)WCHIME_VOL_CLESON_CHANGEABLE      },    /* WCHIME_REQ_CO_CSR_FRRR_SD        */
    {  (U1)WCHIME_VOL_CLESON_CHANGEABLE,     (U1)WCHIME_VOL_CLESON_CHANGEABLE,     (U1)WCHIME_VOL_CLESON_CHANGEABLE      },    /* WCHIME_REQ_IN_CSR_FRRR_MD        */
    {  (U1)WCHIME_VOL_CLESON_CHANGEABLE,     (U1)WCHIME_VOL_CLESON_CHANGEABLE,     (U1)WCHIME_VOL_CLESON_CHANGEABLE      },    /* WCHIME_REQ_IN_CSR_RCTA           */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_PCS_PED            */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_FCTA_STEP_STOP     */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_EDSS_R04           */
    {  (U1)WCHIME_VOL_CLESON_CHANGEABLE,     (U1)WCHIME_VOL_CLESON_CHANGEABLE,     (U1)WCHIME_VOL_CLESON_CHANGEABLE      },    /* WCHIME_REQ_IN_CSR_FR_LD          */
    {  (U1)WCHIME_VOL_CLESON_CHANGEABLE,     (U1)WCHIME_VOL_CLESON_CHANGEABLE,     (U1)WCHIME_VOL_CLESON_CHANGEABLE      },    /* WCHIME_REQ_IN_CSR_RR_LD          */
    {  (U1)WCHIME_VOL_CLESON_CHANGEABLE,     (U1)WCHIME_VOL_CLESON_CHANGEABLE,     (U1)WCHIME_VOL_CLESON_CHANGEABLE      },    /* WCHIME_REQ_IN_CSR_FRRR_LD        */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_DA                 */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_TCHAR_CYCL2        */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_EDSS_R03           */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_ADTJA_PTN6         */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_EIGCON_EG_PWROFF   */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_BATTRW             */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_SCB                */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_BSM                */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_LDA                */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_INFRA_INT          */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_SMASTA_INT3        */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_IN_OAA_HFCT           */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_SI_FCTA               */
    {  (U1)WCHIME_VOL_CLESON_CHANGEABLE,     (U1)WCHIME_VOL_CLESON_CHANGEABLE,     (U1)WCHIME_VOL_CLESON_CHANGEABLE      },    /* WCHIME_REQ_IN_CSR_FR_FD          */
    {  (U1)WCHIME_VOL_CLESON_CHANGEABLE,     (U1)WCHIME_VOL_CLESON_CHANGEABLE,     (U1)WCHIME_VOL_CLESON_CHANGEABLE      },    /* WCHIME_REQ_IN_CSR_RR_FD          */
    {  (U1)WCHIME_VOL_CLESON_CHANGEABLE,     (U1)WCHIME_VOL_CLESON_CHANGEABLE,     (U1)WCHIME_VOL_CLESON_CHANGEABLE      },    /* WCHIME_REQ_IN_CSR_FRRR_FD        */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_IN_TCHAR_CYCL1        */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_BRK_FLDLEAK        */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_STEER_STP          */
    {  (U1)WCHIME_VOL_SEAREM_FMV_MID,        (U1)WCHIME_VOL_SEAREM_FMV_MID,        (U1)WCHIME_VOL_SEAREM_FMV_MAX         },    /* WCHIME_REQ_IN_SBLT_FMV           */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_ROLAWA_ENST_VRUN   */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_SBW_RJCT           */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_CO_NACCON             */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_CO_PEXI_HV_NDBW       */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_SI_COOTEM             */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_CO_ACCHOL             */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_SBW_AUTOP          */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_RSA_SIGN_CAUTION2  */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_ESWUOC_REL         */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_IN_ADTJA_PTN5         */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_PMAR               */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_PKBWAR             */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_CO_SOCLOW_HV          */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_APP_NONOPE_REQ2    */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_APP_NONOPE_REQ4    */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_OILPRE             */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_CO_SYSMAL_RNG_P       */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_CHAMAL_BAT_FAIL    */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_SYSMAL_REMDST_0M   */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_SYSMAL_REQSTP      */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_ADTJA_PTN3         */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_EPB                */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_CO_EIGCON_IGOFF       */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_SPDL_DISACT        */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_SFTPOS_NML         */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_ACC_LSPDCNSL       */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_BEVR_DOUBLE        */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_LTA_CNCL           */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_SPDL_REJECT        */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_LCS_CNCL           */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_APP_DIS_ASSIST     */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_SI_APP_CMPLT          */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_DCLDSP_OPERJCT     */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_LCS_ACK            */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_XMDRJT             */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_XMGRIP_DOUBLE      */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_SI_X_MODE_DEACTIVATE  */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_X_MODE_REJECT      */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_BSTMOD_REJ         */
    {  (U1)WCHIME_VOL_1600HZ_73DB,           (U1)WCHIME_VOL_1600HZ_73DB,           (U1)WCHIME_VOL_1600HZ_77DB            },    /* WCHIME_REQ_SI_DOA_RJCT           */
    {  (U1)WCHIME_VOL__800HZ_57DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_SI_MET_WRN_VOL_CSTM   */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_CO_ROLAWA_ENST_VSTP   */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_SI_SBW_SPL_STATE      */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_IN_DMC_LV2            */
    {  (U1)WCHIME_VOL_REVERSE_IN_MID,        (U1)WCHIME_VOL_REVERSE_IN_MID,        (U1)WCHIME_VOL_REVERSE_IN_MAX         },    /* WCHIME_REQ_IN_SFTPOS_REV         */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_IN_SMASTA_INT2        */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_CO_SMASTA_CON         */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_IN_SOCLOW_NPOS        */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_CO_STOSTA             */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_ACC_BRKREQ         */
    {  (U1)WCHIME_VOL_SEAREM_LV2_MID,        (U1)WCHIME_VOL_SEAREM_LV2_MID,        (U1)WCHIME_VOL_SEAREM_LV2_MAX         },    /* WCHIME_REQ_IN_SBLT_LV2           */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_IN_ACC_OVERSPD        */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_SI_ACC_SHIFTREQ       */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_IN_TPMS_CYCL          */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_SI_SWS                */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_MINDSPWR_LV2       */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_BGLFSPD            */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_DR_OPN             */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_BRK_SYS_MAL        */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_BRK_SYS_NOOPE2     */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_BRK_SYS_NOOPE1     */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_SI_STEER_LMT          */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_SI_HYB_HT             */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_SBW_MAL            */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_SBW_MAL            */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_SYSMAL_REMDST_500M */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_SYSMAL_REMDST_1KM  */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_LTA_PTN2           */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_SI_LTA_PTN3           */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_IN_ADTJA_PTN4         */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_ADTJA_PTN7         */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_MINDSPWR_LV1       */
    {  (U1)WCHIME_VOL_SEAREM_LV1_MID,        (U1)WCHIME_VOL_SEAREM_LV1_MID,        (U1)WCHIME_VOL_SEAREM_LV1_MAX         },    /* WCHIME_REQ_IN_SBLT_LV1           */
    {  (U1)WCHIME_VOL_SEAREM_SI_MID,         (U1)WCHIME_VOL_SEAREM_SI_MID,         (U1)WCHIME_VOL_SEAREM_SI_MAX          },    /* WCHIME_REQ_SI_SBLT               */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_SI_GPF                */
    {  (U1)WCHIME_VOL__800HZ_57DB,           (U1)WCHIME_VOL__800HZ_57DB,           (U1)WCHIME_VOL__800HZ_61DB            },    /* WCHIME_REQ_SI_RSA_SIGN_CTN1_OTH  */
    {  (U1)WCHIME_VOL_RSA_MID,               (U1)WCHIME_VOL_RSA_MID,               (U1)WCHIME_VOL_RSA_MAX                },    /* WCHIME_REQ_SI_RSA_SIGN_CTN1_LX   */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_SI_CHKENG             */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_SI_DMC_LV1            */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_ADTJA_PTN2         */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_SYSMAL_FAIL        */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_IN_LTA_PTN1           */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_SI_INFRA_SNGL         */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_SI_MLT_MSG_OTH        */
    {  (U1)WCHIME_VOL_MC_MID,                (U1)WCHIME_VOL_MC_MID,                (U1)WCHIME_VOL_MC_MAX                 },    /* WCHIME_REQ_SI_MLT_MSG_LX         */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_IN_BKEY               */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_CO_LIGHT              */
    {  (U1)WCHIME_VOL_ACC_MID,               (U1)WCHIME_VOL_ACC_MID,               (U1)WCHIME_VOL_ACC_MAX                },    /* WCHIME_REQ_SI_ACC_AUTOSTART      */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_SBW_RCPT           */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_BEVR_SINGLE        */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_XMGRIP_SINGLE      */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_X_MODE_ON          */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_DMODE_CHANGE       */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_IN_LDA_HFCT           */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_IN_BATINS             */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_SI_TPMS_SINGLE        */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_SI_TCHAR_SNGL         */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_IN_LDA_WARN           */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_SI_SMASTA_SNGL        */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_TOWWAR             */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_SI_BATCOO             */
    {  (U1)WCHIME_VOL_TMN_MID,               (U1)WCHIME_VOL_TMN_MID,               (U1)WCHIME_VOL_TMN_MAX                },    /* WCHIME_REQ_SI_TMN_LVN            */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_IN_SMASTA_INT1        */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_BRK_APP3           */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_BRK_APP1           */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_IN_BRK_APP2           */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_SI_ADTJA_PTN1         */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_BKHLD_NOTACT_R16   */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_BKHLD_NOTREL       */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_BKHLD_NOTACT_R07   */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_BKHLD_NOTACT_R08   */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_BKHLD_NOTACT_R17   */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_BKHLD_REL_R10      */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_BKHLD_REL_R11      */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_BKHLD_NOTACT_R13   */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_ACC_APPRVLSTART    */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_PERSET_SUC         */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_PERSET_FAIL        */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_CO_PERSET_DET         */
    {  (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_63DB,           (U1)WCHIME_VOL__800HZ_67DB            },    /* WCHIME_REQ_SI_RSA_CHG_SPLDLMT    */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_FMSEAT_MEM_SCS     */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_FMSEAT_MEM_REJ     */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_FMSEAT_ERS_INFO    */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_FMSEAT_MEM_CALL    */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_ESWUOC_RJCT        */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_SMASTA_SNGL2       */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_EV_RJCT_HEAT       */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_EV_RJCT_BAT        */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_EV_RJCT_SPD        */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_EV_RJCT_ACC        */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_EV_RJCT_OTH        */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_EV_DCTV_LWBAT      */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_EV_DCTV_SPD        */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_EV_DCTV_ACCL       */
    {  (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_63DB,           (U1)WCHIME_VOL_1600HZ_67DB            },    /* WCHIME_REQ_SI_EV_DCTV            */
    {  (U1)WCHIME_VOL_TURHAZ_STA_LCSTM_LSPD, (U1)WCHIME_VOL_TURHAZ_STA_MCSTM_LSPD, (U1)WCHIME_VOL_TURHAZ_STA_HCSTM_LSPD  },    /* WCHIME_REQ_SI_TURHAZ_STA_LS      */
    {  (U1)WCHIME_VOL_TURHAZ_STA_LCSTM_MSPD, (U1)WCHIME_VOL_TURHAZ_STA_MCSTM_MSPD, (U1)WCHIME_VOL_TURHAZ_STA_HCSTM_MSPD  },    /* WCHIME_REQ_SI_TURHAZ_STA_MS      */
    {  (U1)WCHIME_VOL_TURHAZ_STA_LCSTM_HSPD, (U1)WCHIME_VOL_TURHAZ_STA_MCSTM_HSPD, (U1)WCHIME_VOL_TURHAZ_STA_HCSTM_HSPD  },    /* WCHIME_REQ_SI_TURHAZ_STA_HS      */
    {  (U1)WCHIME_VOL_TURHAZ_FIN_LCSTM_LSPD, (U1)WCHIME_VOL_TURHAZ_FIN_MCSTM_LSPD, (U1)WCHIME_VOL_TURHAZ_FIN_HCSTM_LSPD  },    /* WCHIME_REQ_SI_TURHAZ_FIN_LS      */
    {  (U1)WCHIME_VOL_TURHAZ_FIN_LCSTM_MSPD, (U1)WCHIME_VOL_TURHAZ_FIN_MCSTM_MSPD, (U1)WCHIME_VOL_TURHAZ_FIN_HCSTM_MSPD  },    /* WCHIME_REQ_SI_TURHAZ_FIN_MS      */
    {  (U1)WCHIME_VOL_TURHAZ_FIN_LCSTM_HSPD, (U1)WCHIME_VOL_TURHAZ_FIN_MCSTM_HSPD, (U1)WCHIME_VOL_TURHAZ_FIN_HCSTM_HSPD  }     /* WCHIME_REQ_SI_TURHAZ_FIN_HS      */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_wChimeReqCfgInit(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_wChimeReqCfgInit(void)
{
    u1_s_wchime_rcta_vol = (U1)WCHIME_VOL_CSR_RCTA_5;
}
/*===================================================================================================================================*/
/*  U1      u1_g_wChimeCfgOpemdchk(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_wChimeCfgOpemdchk(void)
{
#if 0   /* BEV Rebase provisionally */
    return(u1_g_VehopemdIgnOn());
#else   /* BEV Rebase provisionally */
    return((U1)0U);
#endif   /* BEV Rebase provisionally */
}
/*===================================================================================================================================*/
/*  U1      u1_g_wChimeReqSwCtrl(const U1 u1_a_REQ_SEL)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_wChimeReqSwCtrl(const U1 u1_a_REQ_SEL)
{
    /* Buzzer control specification(at switching,stopping and re-requested) */
    static const U1     u1_sp_WCHIME_REQ_SW_CTRL[WCHIME_NUM_REQ] = {
        (U1)0x08U,  /* WCHIME_REQ_CO_PCS_TSTMD1         */
        (U1)0x08U,  /* WCHIME_REQ_IN_PCS_TSTMD2         */
        (U1)0x08U,  /* WCHIME_REQ_IN_PCS_TSTMD3         */
        (U1)0x08U,  /* WCHIME_REQ_IN_PCS_TSTMD4         */
        (U1)0x08U,  /* WCHIME_REQ_IN_PCS_TSTMD5         */
        (U1)0x08U,  /* WCHIME_REQ_IN_PCS_TSTMD6         */
        (U1)0x08U,  /* WCHIME_REQ_IN_BRK_TST_LRN        */
        (U1)0x0BU,  /* WCHIME_REQ_SI_BRK_TST_STRT       */
        (U1)0x0BU,  /* WCHIME_REQ_SI_BRK_TST_FIN        */
        (U1)0x0BU,  /* WCHIME_REQ_IN_FRRADA_CMP         */
        (U1)0x0BU,  /* WCHIME_REQ_IN_FRRADA_ERR         */
        (U1)0x0BU,  /* WCHIME_REQ_SI_PTS_RDY            */
        (U1)0x08U,  /* WCHIME_REQ_IN_PCS                */
        (U1)0x08U,  /* WCHIME_REQ_IN_ACC                */
        (U1)0x08U,  /* WCHIME_REQ_IN_STEER_UNDRIVE      */
        (U1)0x08U,  /* WCHIME_REQ_IN_LCS_APR            */
        (U1)0x08U,  /* WCHIME_REQ_IN_DOA                */
        (U1)0x08U,  /* WCHIME_REQ_CO_CSR_FR_SD          */
        (U1)0x03U,  /* WCHIME_REQ_IN_CSR_FR_MD          */
        (U1)0x08U,  /* WCHIME_REQ_CO_CSR_RR_SD          */
        (U1)0x03U,  /* WCHIME_REQ_IN_CSR_RR_MD          */
        (U1)0x08U,  /* WCHIME_REQ_CO_CSR_FRRR_SD        */
        (U1)0x03U,  /* WCHIME_REQ_IN_CSR_FRRR_MD        */
        (U1)0x0BU,  /* WCHIME_REQ_IN_CSR_RCTA           */
        (U1)0x08U,  /* WCHIME_REQ_IN_PCS_PED            */
        (U1)0x08U,  /* WCHIME_REQ_IN_FCTA_STEP_STOP     */
        (U1)0x08U,  /* WCHIME_REQ_IN_EDSS_R04           */
        (U1)0x03U,  /* WCHIME_REQ_IN_CSR_FR_LD          */
        (U1)0x03U,  /* WCHIME_REQ_IN_CSR_RR_LD          */
        (U1)0x03U,  /* WCHIME_REQ_IN_CSR_FRRR_LD        */
        (U1)0x08U,  /* WCHIME_REQ_IN_DA                 */
        (U1)0x08U,  /* WCHIME_REQ_IN_TCHAR_CYCL2        */
        (U1)0x00U,  /* WCHIME_REQ_IN_EDSS_R03           */
        (U1)0x00U,  /* WCHIME_REQ_IN_ADTJA_PTN6         */
        (U1)0x00U,  /* WCHIME_REQ_IN_EIGCON_EG_PWROFF   */
        (U1)0x00U,  /* WCHIME_REQ_IN_BATTRW             */
        (U1)0x00U,  /* WCHIME_REQ_IN_SCB                */
        (U1)0x03U,  /* WCHIME_REQ_IN_BSM                */
        (U1)0x03U,  /* WCHIME_REQ_IN_LDA                */
        (U1)0x00U,  /* WCHIME_REQ_IN_INFRA_INT          */
        (U1)0x00U,  /* WCHIME_REQ_IN_SMASTA_INT3        */
        (U1)0x00U,  /* WCHIME_REQ_IN_OAA_HFCT           */
        (U1)0x03U,  /* WCHIME_REQ_SI_FCTA               */
        (U1)0x03U,  /* WCHIME_REQ_IN_CSR_FR_FD          */
        (U1)0x03U,  /* WCHIME_REQ_IN_CSR_RR_FD          */
        (U1)0x03U,  /* WCHIME_REQ_IN_CSR_FRRR_FD        */
        (U1)0x00U,  /* WCHIME_REQ_IN_TCHAR_CYCL1        */
        (U1)0x00U,  /* WCHIME_REQ_IN_BRK_FLDLEAK        */
        (U1)0x00U,  /* WCHIME_REQ_IN_STEER_STP          */
        (U1)0x07U,  /* WCHIME_REQ_IN_SBLT_FMV           */
        (U1)0x00U,  /* WCHIME_REQ_IN_ROLAWA_ENST_VRUN   */
        (U1)0x02U,  /* WCHIME_REQ_SI_SBW_RJCT           */
        (U1)0x00U,  /* WCHIME_REQ_CO_NACCON             */
        (U1)0x00U,  /* WCHIME_REQ_CO_PEXI_HV_NDBW       */
        (U1)0x03U,  /* WCHIME_REQ_SI_COOTEM             */
        (U1)0x00U,  /* WCHIME_REQ_CO_ACCHOL             */
        (U1)0x00U,  /* WCHIME_REQ_IN_SBW_AUTOP          */
        (U1)0x07U,  /* WCHIME_REQ_SI_RSA_SIGN_CAUTION2  */
        (U1)0x02U,  /* WCHIME_REQ_SI_ESWUOC_REL         */
        (U1)0x00U,  /* WCHIME_REQ_IN_ADTJA_PTN5         */
        (U1)0x00U,  /* WCHIME_REQ_IN_PMAR               */
        (U1)0x00U,  /* WCHIME_REQ_IN_PKBWAR             */
        (U1)0x00U,  /* WCHIME_REQ_CO_SOCLOW_HV          */
        (U1)0x03U,  /* WCHIME_REQ_SI_APP_NONOPE_REQ2    */
        (U1)0x03U,  /* WCHIME_REQ_SI_APP_NONOPE_REQ4    */
        (U1)0x00U,  /* WCHIME_REQ_IN_OILPRE             */
        (U1)0x00U,  /* WCHIME_REQ_CO_SYSMAL_RNG_P       */
        (U1)0x00U,  /* WCHIME_REQ_IN_CHAMAL_BAT_FAIL    */
        (U1)0x00U,  /* WCHIME_REQ_IN_SYSMAL_REMDST_0M   */
        (U1)0x00U,  /* WCHIME_REQ_IN_SYSMAL_REQSTP      */
        (U1)0x03U,  /* WCHIME_REQ_SI_ADTJA_PTN3         */
        (U1)0x00U,  /* WCHIME_REQ_IN_EPB                */
        (U1)0x00U,  /* WCHIME_REQ_CO_EIGCON_IGOFF       */
        (U1)0x03U,  /* WCHIME_REQ_SI_SPDL_DISACT        */
        (U1)0x13U,  /* WCHIME_REQ_SI_SFTPOS_NML         */
        (U1)0x03U,  /* WCHIME_REQ_SI_ACC_LSPDCNSL       */
        (U1)0x03U,  /* WCHIME_REQ_SI_BEVR_DOUBLE        */
        (U1)0x03U,  /* WCHIME_REQ_SI_LTA_CNCL           */
        (U1)0x03U,  /* WCHIME_REQ_SI_SPDL_REJECT        */
        (U1)0x03U,  /* WCHIME_REQ_SI_LCS_CNCL           */
        (U1)0x03U,  /* WCHIME_REQ_SI_APP_DIS_ASSIST     */
        (U1)0x03U,  /* WCHIME_REQ_SI_APP_CMPLT          */
        (U1)0x03U,  /* WCHIME_REQ_SI_DCLDSP_OPERJCT     */
        (U1)0x03U,  /* WCHIME_REQ_SI_LCS_ACK            */
        (U1)0x03U,  /* WCHIME_REQ_SI_XMDRJT             */
        (U1)0x03U,  /* WCHIME_REQ_SI_XMGRIP_DOUBLE      */
        (U1)0x03U,  /* WCHIME_REQ_SI_X_MODE_DEACTIVATE  */
        (U1)0x03U,  /* WCHIME_REQ_SI_X_MODE_REJECT      */
        (U1)0x03U,  /* WCHIME_REQ_SI_BSTMOD_REJ         */
        (U1)0x02U,  /* WCHIME_REQ_SI_DOA_RJCT           */
        (U1)0x03U,  /* WCHIME_REQ_SI_MET_WRN_VOL_CSTM   */
        (U1)0x00U,  /* WCHIME_REQ_CO_ROLAWA_ENST_VSTP   */
        (U1)0x02U,  /* WCHIME_REQ_SI_SBW_SPL_STATE      */
        (U1)0x00U,  /* WCHIME_REQ_IN_DMC_LV2            */
        (U1)0x00U,  /* WCHIME_REQ_IN_SFTPOS_REV         */
        (U1)0x07U,  /* WCHIME_REQ_IN_SMASTA_INT2        */
        (U1)0x00U,  /* WCHIME_REQ_CO_SMASTA_CON         */
        (U1)0x00U,  /* WCHIME_REQ_IN_SOCLOW_NPOS        */
        (U1)0x00U,  /* WCHIME_REQ_CO_STOSTA             */
        (U1)0x00U,  /* WCHIME_REQ_IN_ACC_BRKREQ         */
        (U1)0x00U,  /* WCHIME_REQ_IN_SBLT_LV2           */
        (U1)0x00U,  /* WCHIME_REQ_IN_ACC_OVERSPD        */
        (U1)0x03U,  /* WCHIME_REQ_SI_ACC_SHIFTREQ       */
        (U1)0x00U,  /* WCHIME_REQ_IN_TPMS_CYCL          */
        (U1)0x03U,  /* WCHIME_REQ_SI_SWS                */
        (U1)0x00U,  /* WCHIME_REQ_IN_MINDSPWR_LV2       */
        (U1)0x00U,  /* WCHIME_REQ_IN_BGLFSPD            */
        (U1)0x00U,  /* WCHIME_REQ_IN_DR_OPN             */
        (U1)0x00U,  /* WCHIME_REQ_IN_BRK_SYS_MAL        */
        (U1)0x00U,  /* WCHIME_REQ_IN_BRK_SYS_NOOPE2     */
        (U1)0x00U,  /* WCHIME_REQ_IN_BRK_SYS_NOOPE1     */
        (U1)0x03U,  /* WCHIME_REQ_SI_STEER_LMT          */
        (U1)0x03U,  /* WCHIME_REQ_SI_HYB_HT             */
        (U1)0x03U,  /* WCHIME_REQ_SI_SBW_MAL            */
        (U1)0x00U,  /* WCHIME_REQ_IN_SBW_MAL            */
        (U1)0x00U,  /* WCHIME_REQ_IN_SYSMAL_REMDST_500M */
        (U1)0x00U,  /* WCHIME_REQ_IN_SYSMAL_REMDST_1KM  */
        (U1)0x00U,  /* WCHIME_REQ_IN_LTA_PTN2           */
        (U1)0x03U,  /* WCHIME_REQ_SI_LTA_PTN3           */
        (U1)0x00U,  /* WCHIME_REQ_IN_ADTJA_PTN4         */
        (U1)0x03U,  /* WCHIME_REQ_SI_ADTJA_PTN7         */
        (U1)0x03U,  /* WCHIME_REQ_SI_MINDSPWR_LV1       */
        (U1)0x00U,  /* WCHIME_REQ_IN_SBLT_LV1           */
        (U1)0x03U,  /* WCHIME_REQ_SI_SBLT               */
        (U1)0x03U,  /* WCHIME_REQ_SI_GPF                */
        (U1)0x03U,  /* WCHIME_REQ_SI_RSA_SIGN_CTN1_OTH  */
        (U1)0x03U,  /* WCHIME_REQ_SI_RSA_SIGN_CTN1_LX   */
        (U1)0x03U,  /* WCHIME_REQ_SI_CHKENG             */
        (U1)0x03U,  /* WCHIME_REQ_SI_DMC_LV1            */
        (U1)0x03U,  /* WCHIME_REQ_SI_ADTJA_PTN2         */
        (U1)0x03U,  /* WCHIME_REQ_SI_SYSMAL_FAIL        */
        (U1)0x00U,  /* WCHIME_REQ_IN_LTA_PTN1           */
        (U1)0x03U,  /* WCHIME_REQ_SI_INFRA_SNGL         */
        (U1)0x02U,  /* WCHIME_REQ_SI_MLT_MSG_OTH        */
        (U1)0x02U,  /* WCHIME_REQ_SI_MLT_MSG_LX         */
        (U1)0x00U,  /* WCHIME_REQ_IN_BKEY               */
        (U1)0x00U,  /* WCHIME_REQ_CO_LIGHT              */
        (U1)0x03U,  /* WCHIME_REQ_SI_ACC_AUTOSTART      */
        (U1)0x02U,  /* WCHIME_REQ_SI_SBW_RCPT           */
        (U1)0x03U,  /* WCHIME_REQ_SI_BEVR_SINGLE        */
        (U1)0x03U,  /* WCHIME_REQ_SI_XMGRIP_SINGLE      */
        (U1)0x03U,  /* WCHIME_REQ_SI_X_MODE_ON          */
        (U1)0x03U,  /* WCHIME_REQ_SI_DMODE_CHANGE       */
        (U1)0x03U,  /* WCHIME_REQ_IN_LDA_HFCT           */
        (U1)0x00U,  /* WCHIME_REQ_IN_BATINS             */
        (U1)0x03U,  /* WCHIME_REQ_SI_TPMS_SINGLE        */
        (U1)0x03U,  /* WCHIME_REQ_SI_TCHAR_SNGL         */
        (U1)0x03U,  /* WCHIME_REQ_IN_LDA_WARN           */
        (U1)0x02U,  /* WCHIME_REQ_SI_SMASTA_SNGL        */
        (U1)0x00U,  /* WCHIME_REQ_IN_TOWWAR             */
        (U1)0x03U,  /* WCHIME_REQ_SI_BATCOO             */
        (U1)0x03U,  /* WCHIME_REQ_SI_TMN_LVN            */
        (U1)0x00U,  /* WCHIME_REQ_IN_SMASTA_INT1        */
        (U1)0x03U,  /* WCHIME_REQ_SI_BRK_APP3           */
        (U1)0x00U,  /* WCHIME_REQ_IN_BRK_APP1           */
        (U1)0x00U,  /* WCHIME_REQ_IN_BRK_APP2           */
        (U1)0x03U,  /* WCHIME_REQ_SI_ADTJA_PTN1         */
        (U1)0x03U,  /* WCHIME_REQ_SI_BKHLD_NOTACT_R16   */
        (U1)0x03U,  /* WCHIME_REQ_SI_BKHLD_NOTREL       */
        (U1)0x03U,  /* WCHIME_REQ_SI_BKHLD_NOTACT_R07   */
        (U1)0x03U,  /* WCHIME_REQ_SI_BKHLD_NOTACT_R08   */
        (U1)0x03U,  /* WCHIME_REQ_SI_BKHLD_NOTACT_R17   */
        (U1)0x03U,  /* WCHIME_REQ_SI_BKHLD_REL_R10      */
        (U1)0x03U,  /* WCHIME_REQ_SI_BKHLD_REL_R11      */
        (U1)0x03U,  /* WCHIME_REQ_SI_BKHLD_NOTACT_R13   */
        (U1)0x03U,  /* WCHIME_REQ_SI_ACC_APPRVLSTART    */
        (U1)0x02U,  /* WCHIME_REQ_SI_PERSET_SUC         */
        (U1)0x02U,  /* WCHIME_REQ_SI_PERSET_FAIL        */
        (U1)0x00U,  /* WCHIME_REQ_CO_PERSET_DET         */
        (U1)0x03U,  /* WCHIME_REQ_SI_RSA_CHG_SPLDLMT    */
        (U1)0x02U,  /* WCHIME_REQ_SI_FMSEAT_MEM_SCS     */
        (U1)0x02U,  /* WCHIME_REQ_SI_FMSEAT_MEM_REJ     */
        (U1)0x02U,  /* WCHIME_REQ_SI_FMSEAT_ERS_INFO    */
        (U1)0x02U,  /* WCHIME_REQ_SI_FMSEAT_MEM_CALL    */
        (U1)0x03U,  /* WCHIME_REQ_SI_ESWUOC_RJCT        */
        (U1)0x02U,  /* WCHIME_REQ_SI_SMASTA_SNGL2       */
        (U1)0x03U,  /* WCHIME_REQ_SI_EV_RJCT_HEAT       */
        (U1)0x03U,  /* WCHIME_REQ_SI_EV_RJCT_BAT        */
        (U1)0x03U,  /* WCHIME_REQ_SI_EV_RJCT_SPD        */
        (U1)0x03U,  /* WCHIME_REQ_SI_EV_RJCT_ACC        */
        (U1)0x03U,  /* WCHIME_REQ_SI_EV_RJCT_OTH        */
        (U1)0x03U,  /* WCHIME_REQ_SI_EV_DCTV_LWBAT      */
        (U1)0x03U,  /* WCHIME_REQ_SI_EV_DCTV_SPD        */
        (U1)0x03U,  /* WCHIME_REQ_SI_EV_DCTV_ACCL       */
        (U1)0x03U,  /* WCHIME_REQ_SI_EV_DCTV            */
        (U1)0x0EU,  /* WCHIME_REQ_SI_TURHAZ_STA_LS      */
        (U1)0x0EU,  /* WCHIME_REQ_SI_TURHAZ_STA_MS      */
        (U1)0x0EU,  /* WCHIME_REQ_SI_TURHAZ_STA_HS      */
        (U1)0x0EU,  /* WCHIME_REQ_SI_TURHAZ_FIN_LS      */
        (U1)0x0EU,  /* WCHIME_REQ_SI_TURHAZ_FIN_MS      */
        (U1)0x0EU   /* WCHIME_REQ_SI_TURHAZ_FIN_HS      */
    };

    /* ----------------------------------------------------------------------------------------------- */
    /* Attention :                                                                                     */
    /* ----------------------------------------------------------------------------------------------- */
    /* The range of u1_a_REQ_SEL is tested before u1_g_wChimeReqSwCtrl is called if the valued is less */
    /* than u1_g_WCHIME_NUM_REQ.                                                                       */
    /* ----------------------------------------------------------------------------------------------- */

    U1    u1_t_sw_ctrl;
    U1    u1_t_judge;

    u1_t_sw_ctrl = u1_sp_WCHIME_REQ_SW_CTRL[u1_a_REQ_SEL];

    if(u1_a_REQ_SEL == (U1)WCHIME_REQ_IN_SBLT_LV2){
#if 0   /* BEV Rebase provisionally */
        u1_t_judge = u1_g_SbltsyncLv2Cmp();
#else   /* BEV Rebase provisionally */
        u1_t_judge = (U1)FALSE;
#endif   /* BEV Rebase provisionally */

        if(u1_t_judge == (U1)TRUE){
            (u1_t_sw_ctrl) |= (U1)WCHIME_REQ_SWC_WAV_CYCL;
        }
    }

    return(u1_t_sw_ctrl);

}
/*===================================================================================================================================*/
/*  U1      u1_g_wChimeCfgSwWaitInsert(const U1 u1_a_REQ_SEL, const U1 u1_a_REQ_NEXT, U2 * u2p_a_wait_time)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_wChimeCfgSwWaitInsert(const U1 u1_a_REQ_SEL, const U1 u1_a_REQ_NEXT, U2 * u2p_a_wait_time)
{
    static const ST_WCHIME_SW_WAIT_EXCPT_CHK    st_sp_WCHIME_SW_WAIT_EXCPT_LIST[WCHIME_SW_WAIT_EXCPT_NUM] = {
        {&u1_s_wChimeCfgSwExcptOtherToApp, (U1)TRUE,  (U2)WCHIME_WT_TIM_OTHER_TO_APP},
        {&u1_s_wChimeCfgSwExcptAppToOther, (U1)TRUE,  (U2)WCHIME_WT_TIM_APP_TO_OTHER},
        {&u1_s_wChimeCfgSwExcptSblt,       (U1)FALSE, (U2)WCHIME_WT_TIM_NOTHING     },
        {&u1_s_wChimeCfgSwExcptCsr,        (U1)FALSE, (U2)WCHIME_WT_TIM_NOTHING     },
        {&u1_s_wChimeCfgSwExcptTurhaz,     (U1)FALSE, (U2)WCHIME_WT_TIM_NOTHING     }
    };

    static const ST_WCHIME_SW_WAIT_EXCPT_CHK *  stp_t_list;
    U4                                          u4_t_loop;
    U1                                          u1_t_jdg;
    U1                                          u1_t_wait;

    if(u1_a_REQ_SEL != u1_a_REQ_NEXT){
        u1_t_wait          = (U1)TRUE;
        (*u2p_a_wait_time) = (U2)WCHIME_WT_TIM_CMN;

        u1_t_jdg           = (U1)FALSE;
        for(u4_t_loop = (U4)0U; u4_t_loop < (U4)WCHIME_SW_WAIT_EXCPT_NUM; u4_t_loop++){
            stp_t_list = &st_sp_WCHIME_SW_WAIT_EXCPT_LIST[u4_t_loop];
            u1_t_jdg   = (stp_t_list->fp_u1_chk_func)(u1_a_REQ_SEL, u1_a_REQ_NEXT);
            if(u1_t_jdg == (U1)TRUE){
                u1_t_wait          = stp_t_list->u1_wait;
                (*u2p_a_wait_time) = stp_t_list->u2_time;
                break;
            }
        }
    }
    else{                              /* u1_a_REQ_SEL == u1_a_REQ_NEXT */
        u1_t_wait = (U1)FALSE;
        switch(u1_a_REQ_NEXT){
            case (U1)WCHIME_REQ_IN_CSR_RCTA:
                /* To sound the buzzer immediately with new volume, the silent duration must be 0. */
                if(u1_g_wchime_alrt_csr_vol_old != u1_g_wchime_alrt_csr_vol_now){
                    (*u2p_a_wait_time) = (U2)WCHIME_WT_TIM_NOTHING;
                }
                break;
            case (U1)WCHIME_REQ_SI_SMASTA_SNGL:
                /* Switching between WCHIME_REQ_SI_SMASTA_SNGL, the silent duration must be 0.  */
                (*u2p_a_wait_time) = (U2)WCHIME_WT_TIM_NOTHING;
                break;
            case (U1)WCHIME_REQ_SI_SMASTA_SNGL2:
                /* Switching between WCHIME_REQ_SI_SMASTA_SNGL2, the silent duration must be 0. */
                (*u2p_a_wait_time) = (U2)WCHIME_WT_TIM_NOTHING;
                break;
            case (U1)WCHIME_REQ_SI_APP_NONOPE_REQ2:
            case (U1)WCHIME_REQ_SI_APP_NONOPE_REQ4:
            case (U1)WCHIME_REQ_SI_APP_DIS_ASSIST:
            case (U1)WCHIME_REQ_SI_APP_CMPLT:
                /* Switching between APP and APP, the silent duration must be 300. */
                (*u2p_a_wait_time) = (U2)WCHIME_WT_TIM_CMN;
                u1_t_wait          = (U1)TRUE;
                break;
            default:
                /* Do Nothing */
                break;
        }
    }

    return(u1_t_wait);
}
/*===================================================================================================================================*/
/*  U1      u1_g_wChimeCfgVolGet(const U1 u1_a_REQ_SEL)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_wChimeCfgVolGet(const U1 u1_a_REQ_SEL)
{
    U1    u1_t_reqvol;
    U1    u1_t_metcstmvol;

    if(u1_a_REQ_SEL < (U1)WCHIME_NUM_REQ){
#if 0   /* BEV Rebase provisionally */
        u1_t_metcstmvol = u1_g_McstBf((U1)MCST_BFI_METWRNCSTM);
        if(u1_t_metcstmvol >= (U1)MCST_METWRNCSTM_VOL_NUM){
            u1_t_metcstmvol = (U1)MCST_METWRNCSTM_VOL_MID;
        }
#else   /* BEV Rebase provisionally */
        u1_t_metcstmvol = (U1)0U;
#endif   /* BEV Rebase provisionally */
        u1_t_reqvol = u1_sp2_WCHIME_REQ_VOL_INFO[u1_a_REQ_SEL][u1_t_metcstmvol];

        switch(u1_t_reqvol){
            case (U1)WCHIME_VOL_CLESON_CHANGEABLE:
                u1_t_reqvol = u1_s_wChimeCfgClesonVolGet(u1_a_REQ_SEL);
                break;

            default:
                /* Do nothing */
                break;
        }
    }
    else{
        u1_t_reqvol = (U1)U1_MAX;
    }

    return(u1_t_reqvol);
}
/*===================================================================================================================================*/
/*  static U1   u1_s_wChimeCfgSwExcptOtherToApp(const U1 u1_a_REQ_SEL, const U1 u1_a_REQ_NEXT)                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1   u1_s_wChimeCfgSwExcptOtherToApp(const U1 u1_a_REQ_SEL, const U1 u1_a_REQ_NEXT)
{
    static const U1     u1_sp_WCHIME_APP_BZ_LIST[WCHIME_APP_BZ_NUM] = {
        (U1)WCHIME_REQ_SI_APP_DIS_ASSIST,     (U1)WCHIME_REQ_SI_APP_CMPLT,
        (U1)WCHIME_REQ_SI_APP_NONOPE_REQ2,    (U1)WCHIME_REQ_SI_APP_NONOPE_REQ4
    };

    U4    u4_t_loop;
    U1    u1_t_jdg;
    U1    u1_t_reqapp;

    u1_t_jdg    = (U1)FALSE;

    u1_t_reqapp = (U1)0U;
    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)WCHIME_APP_BZ_NUM; u4_t_loop++){
        if(u1_a_REQ_SEL == u1_sp_WCHIME_APP_BZ_LIST[u4_t_loop]){
            u1_t_reqapp |= (U1)WCHIME_REQ_SEL_APP;
        }
        if(u1_a_REQ_NEXT == u1_sp_WCHIME_APP_BZ_LIST[u4_t_loop]){
            u1_t_reqapp |= (U1)WCHIME_REQ_NEXT_APP;
        }
    }
    if(u1_t_reqapp == (U1)WCHIME_REQ_OTHER_TO_APP){
        u1_t_jdg = (U1)TRUE;
    }
    if(u1_t_jdg == (U1)TRUE){
        u1_g_wchime_silencetime_flag = (U1)TRUE;
    }

    return(u1_t_jdg);
}
/*===================================================================================================================================*/
/*  static U1   u1_s_wChimeCfgSwExcptAppToOther(const U1 u1_a_REQ_SEL, const U1 u1_a_REQ_NEXT)                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1   u1_s_wChimeCfgSwExcptAppToOther(const U1 u1_a_REQ_SEL, const U1 u1_a_REQ_NEXT)
{
    static const U1     u1_sp_WCHIME_APP_BZ_LIST[WCHIME_APP_BZ_NUM] = {
        (U1)WCHIME_REQ_SI_APP_DIS_ASSIST,     (U1)WCHIME_REQ_SI_APP_CMPLT,
        (U1)WCHIME_REQ_SI_APP_NONOPE_REQ2,    (U1)WCHIME_REQ_SI_APP_NONOPE_REQ4
    };

    U4    u4_t_loop;
    U1    u1_t_jdg;
    U1    u1_t_reqapp;

    u1_t_jdg    = (U1)FALSE;

    u1_t_reqapp = (U1)0U;
    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)WCHIME_APP_BZ_NUM; u4_t_loop++){
        if(u1_a_REQ_SEL == u1_sp_WCHIME_APP_BZ_LIST[u4_t_loop]){
            u1_t_reqapp |= (U1)WCHIME_REQ_SEL_APP;
        }
        if(u1_a_REQ_NEXT == u1_sp_WCHIME_APP_BZ_LIST[u4_t_loop]){
            u1_t_reqapp |= (U1)WCHIME_REQ_NEXT_APP;
        }
    }
    if(u1_t_reqapp == (U1)WCHIME_REQ_APP_TO_OTHER){
        u1_t_jdg = (U1)TRUE;
    }

    return(u1_t_jdg);
}
/*===================================================================================================================================*/
/*  static U1   u1_s_wChimeCfgSwExcptSblt(const U1 u1_a_REQ_SEL, const U1 u1_a_REQ_NEXT)                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1   u1_s_wChimeCfgSwExcptSblt(const U1 u1_a_REQ_SEL, const U1 u1_a_REQ_NEXT)
{
    static const U1     u1_sp_WCHIME_SBLT_BZ_LIST[WCHIME_SBLT_BZ_NUM] = {
        (U1)WCHIME_REQ_IN_SBLT_FMV,           (U1)WCHIME_REQ_SI_SBLT,
        (U1)WCHIME_REQ_IN_SBLT_LV2,           (U1)WCHIME_REQ_IN_SBLT_LV1
    };

    U4    u4_t_loop;
    U1    u1_t_jdg;

    u1_t_jdg = (U1)FALSE;

    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)WCHIME_SBLT_BZ_NUM; u4_t_loop++){
        if(u1_a_REQ_NEXT == u1_sp_WCHIME_SBLT_BZ_LIST[u4_t_loop]){
            u1_t_jdg = (U1)TRUE;
            break;
        }
    }

    return(u1_t_jdg);
}
/*===================================================================================================================================*/
/*  static U1   u1_s_wChimeCfgSwExcptCsr(const U1 u1_a_REQ_SEL, const U1 u1_a_REQ_NEXT)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1   u1_s_wChimeCfgSwExcptCsr(const U1 u1_a_REQ_SEL, const U1 u1_a_REQ_NEXT)
{
    static const U1 u1_sp_WCHIME_CSR_BZ_LIST[WCHIME_CSR_BZ_NUM] = {
        (U1)WCHIME_REQ_CO_CSR_FRRR_SD,        (U1)WCHIME_REQ_CO_CSR_RR_SD,           (U1)WCHIME_REQ_CO_CSR_FR_SD,
        (U1)WCHIME_REQ_IN_CSR_FRRR_MD,        (U1)WCHIME_REQ_IN_CSR_RR_MD,           (U1)WCHIME_REQ_IN_CSR_FR_MD,
        (U1)WCHIME_REQ_IN_CSR_FRRR_LD,        (U1)WCHIME_REQ_IN_CSR_RR_LD,           (U1)WCHIME_REQ_IN_CSR_FR_LD,
        (U1)WCHIME_REQ_IN_CSR_RR_FD,          (U1)WCHIME_REQ_IN_CSR_FR_FD,           (U1)WCHIME_REQ_IN_CSR_FRRR_FD
    };

    U4    u4_t_loop;
    U1    u1_t_jdg;

    u1_t_jdg = (U1)FALSE;

    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)WCHIME_CSR_BZ_NUM; u4_t_loop++){
        if(u1_a_REQ_NEXT == u1_sp_WCHIME_CSR_BZ_LIST[u4_t_loop]){
            u1_t_jdg = (U1)TRUE;
            break;
        }
    }

    return(u1_t_jdg);
}
/*===================================================================================================================================*/
/*  static U1   u1_s_wChimeCfgSwExcptTurhaz(const U1 u1_a_REQ_SEL, const U1 u1_a_REQ_NEXT)                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1   u1_s_wChimeCfgSwExcptTurhaz(const U1 u1_a_REQ_SEL, const U1 u1_a_REQ_NEXT)
{
    static const U1 u1_sp_WCHIME_TURHAZ_BZ_LIST[WCHIME_TURHAZ_BZ_NUM] = {
        (U1)WCHIME_REQ_SI_TURHAZ_STA_LS,
        (U1)WCHIME_REQ_SI_TURHAZ_STA_MS,
        (U1)WCHIME_REQ_SI_TURHAZ_STA_HS,
        (U1)WCHIME_REQ_SI_TURHAZ_FIN_LS,
        (U1)WCHIME_REQ_SI_TURHAZ_FIN_MS,
        (U1)WCHIME_REQ_SI_TURHAZ_FIN_HS
    };

    U4    u4_t_loop;
    U1    u1_t_jdg;

    u1_t_jdg = (U1)FALSE;

    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)WCHIME_TURHAZ_BZ_NUM; u4_t_loop++){
        if(u1_a_REQ_SEL == u1_sp_WCHIME_TURHAZ_BZ_LIST[u4_t_loop]){
            u1_t_jdg = (U1)TRUE;
            break;
        }
    }

    return(u1_t_jdg);
}
/*===================================================================================================================================*/
/*  static U1   u1_s_wChimeCfgClesonVolGet(const U1 u1_a_REQ_SEL)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1   u1_s_wChimeCfgClesonVolGet(const U1 u1_a_REQ_SEL)
{
    static const ST_WCHIME_CSR_VOL st_sp_WCHIME_CSR_VOL_LIST[WCHIME_CSR_VOL_LIST_NUM] = {
        {(U1)WCHIME_REQ_CO_CSR_FRRR_SD,  {(U1)WCHIME_VOL_CSR_FRRR_SD_0,
                                          (U1)WCHIME_VOL_CSR_FRRR_SD_1,
                                          (U1)WCHIME_VOL_CSR_FRRR_SD_2,
                                          (U1)WCHIME_VOL_CSR_FRRR_SD_3,
                                          (U1)WCHIME_VOL_CSR_FRRR_SD_4,
                                          (U1)WCHIME_VOL_CSR_FRRR_SD_5,
                                          (U1)WCHIME_VOL_CSR_FRRR_SD_6,
                                          (U1)WCHIME_VOL_CSR_FRRR_SD_7  }},
        {(U1)WCHIME_REQ_CO_CSR_FR_SD,    {(U1)WCHIME_VOL_CSR_FR_SD_0,
                                          (U1)WCHIME_VOL_CSR_FR_SD_1,
                                          (U1)WCHIME_VOL_CSR_FR_SD_2,
                                          (U1)WCHIME_VOL_CSR_FR_SD_3,
                                          (U1)WCHIME_VOL_CSR_FR_SD_4,
                                          (U1)WCHIME_VOL_CSR_FR_SD_5,
                                          (U1)WCHIME_VOL_CSR_FR_SD_6,
                                          (U1)WCHIME_VOL_CSR_FR_SD_7    }},
        {(U1)WCHIME_REQ_CO_CSR_RR_SD,    {(U1)WCHIME_VOL_CSR_RR_SD_0,
                                          (U1)WCHIME_VOL_CSR_RR_SD_1,
                                          (U1)WCHIME_VOL_CSR_RR_SD_2,
                                          (U1)WCHIME_VOL_CSR_RR_SD_3,
                                          (U1)WCHIME_VOL_CSR_RR_SD_4,
                                          (U1)WCHIME_VOL_CSR_RR_SD_5,
                                          (U1)WCHIME_VOL_CSR_RR_SD_6,
                                          (U1)WCHIME_VOL_CSR_RR_SD_7    }},
        {(U1)WCHIME_REQ_IN_CSR_FRRR_MD,  {(U1)WCHIME_VOL_CSR_FRRR_MD_FR_0,
                                          (U1)WCHIME_VOL_CSR_FRRR_MD_FR_1,
                                          (U1)WCHIME_VOL_CSR_FRRR_MD_FR_2,
                                          (U1)WCHIME_VOL_CSR_FRRR_MD_FR_3,
                                          (U1)WCHIME_VOL_CSR_FRRR_MD_FR_4,
                                          (U1)WCHIME_VOL_CSR_FRRR_MD_FR_5,
                                          (U1)WCHIME_VOL_CSR_FRRR_MD_FR_6,
                                          (U1)WCHIME_VOL_CSR_FRRR_MD_FR_7   }},
        {(U1)WCHIME_REQ_IN_CSR_FR_MD,    {(U1)WCHIME_VOL_CSR_FR_MD_0,
                                          (U1)WCHIME_VOL_CSR_FR_MD_1,
                                          (U1)WCHIME_VOL_CSR_FR_MD_2,
                                          (U1)WCHIME_VOL_CSR_FR_MD_3,
                                          (U1)WCHIME_VOL_CSR_FR_MD_4,
                                          (U1)WCHIME_VOL_CSR_FR_MD_5,
                                          (U1)WCHIME_VOL_CSR_FR_MD_6,
                                          (U1)WCHIME_VOL_CSR_FR_MD_7     }},
        {(U1)WCHIME_REQ_IN_CSR_RR_MD,    {(U1)WCHIME_VOL_CSR_RR_MD_0,
                                          (U1)WCHIME_VOL_CSR_RR_MD_1,
                                          (U1)WCHIME_VOL_CSR_RR_MD_2,
                                          (U1)WCHIME_VOL_CSR_RR_MD_3,
                                          (U1)WCHIME_VOL_CSR_RR_MD_4,
                                          (U1)WCHIME_VOL_CSR_RR_MD_5,
                                          (U1)WCHIME_VOL_CSR_RR_MD_6,
                                          (U1)WCHIME_VOL_CSR_RR_MD_7     }},
        {(U1)WCHIME_REQ_IN_CSR_FRRR_LD,  {(U1)WCHIME_VOL_CSR_FRRR_LD_FR_0,
                                          (U1)WCHIME_VOL_CSR_FRRR_LD_FR_1,
                                          (U1)WCHIME_VOL_CSR_FRRR_LD_FR_2,
                                          (U1)WCHIME_VOL_CSR_FRRR_LD_FR_3,
                                          (U1)WCHIME_VOL_CSR_FRRR_LD_FR_4,
                                          (U1)WCHIME_VOL_CSR_FRRR_LD_FR_5,
                                          (U1)WCHIME_VOL_CSR_FRRR_LD_FR_6,
                                          (U1)WCHIME_VOL_CSR_FRRR_LD_FR_7   }},
        {(U1)WCHIME_REQ_IN_CSR_FR_LD,    {(U1)WCHIME_VOL_CSR_FR_LD_0,
                                          (U1)WCHIME_VOL_CSR_FR_LD_1,
                                          (U1)WCHIME_VOL_CSR_FR_LD_2,
                                          (U1)WCHIME_VOL_CSR_FR_LD_3,
                                          (U1)WCHIME_VOL_CSR_FR_LD_4,
                                          (U1)WCHIME_VOL_CSR_FR_LD_5,
                                          (U1)WCHIME_VOL_CSR_FR_LD_6,
                                          (U1)WCHIME_VOL_CSR_FR_LD_7     }},
        {(U1)WCHIME_REQ_IN_CSR_RR_LD,    {(U1)WCHIME_VOL_CSR_RR_LD_0,
                                          (U1)WCHIME_VOL_CSR_RR_LD_1,
                                          (U1)WCHIME_VOL_CSR_RR_LD_2,
                                          (U1)WCHIME_VOL_CSR_RR_LD_3,
                                          (U1)WCHIME_VOL_CSR_RR_LD_4,
                                          (U1)WCHIME_VOL_CSR_RR_LD_5,
                                          (U1)WCHIME_VOL_CSR_RR_LD_6,
                                          (U1)WCHIME_VOL_CSR_RR_LD_7     }},
        {(U1)WCHIME_REQ_IN_CSR_FRRR_FD,  {(U1)WCHIME_VOL_CSR_FRRR_FD_FR_0,
                                          (U1)WCHIME_VOL_CSR_FRRR_FD_FR_1,
                                          (U1)WCHIME_VOL_CSR_FRRR_FD_FR_2,
                                          (U1)WCHIME_VOL_CSR_FRRR_FD_FR_3,
                                          (U1)WCHIME_VOL_CSR_FRRR_FD_FR_4,
                                          (U1)WCHIME_VOL_CSR_FRRR_FD_FR_5,
                                          (U1)WCHIME_VOL_CSR_FRRR_FD_FR_6,
                                          (U1)WCHIME_VOL_CSR_FRRR_FD_FR_7   }},
        {(U1)WCHIME_REQ_IN_CSR_FR_FD,    {(U1)WCHIME_VOL_CSR_FR_FD_0,
                                          (U1)WCHIME_VOL_CSR_FR_FD_1,
                                          (U1)WCHIME_VOL_CSR_FR_FD_2,
                                          (U1)WCHIME_VOL_CSR_FR_FD_3,
                                          (U1)WCHIME_VOL_CSR_FR_FD_4,
                                          (U1)WCHIME_VOL_CSR_FR_FD_5,
                                          (U1)WCHIME_VOL_CSR_FR_FD_6,
                                          (U1)WCHIME_VOL_CSR_FR_FD_7     }},
        {(U1)WCHIME_REQ_IN_CSR_RR_FD,    {(U1)WCHIME_VOL_CSR_RR_FD_0,
                                          (U1)WCHIME_VOL_CSR_RR_FD_1,
                                          (U1)WCHIME_VOL_CSR_RR_FD_2,
                                          (U1)WCHIME_VOL_CSR_RR_FD_3,
                                          (U1)WCHIME_VOL_CSR_RR_FD_4,
                                          (U1)WCHIME_VOL_CSR_RR_FD_5,
                                          (U1)WCHIME_VOL_CSR_RR_FD_6,
                                          (U1)WCHIME_VOL_CSR_RR_FD_7     }},
        {(U1)WCHIME_REQ_IN_CSR_RCTA,     {(U1)WCHIME_VOL_CSR_RCTA_0,
                                          (U1)WCHIME_VOL_CSR_RCTA_1,
                                          (U1)WCHIME_VOL_CSR_RCTA_2,
                                          (U1)WCHIME_VOL_CSR_RCTA_3,
                                          (U1)WCHIME_VOL_CSR_RCTA_4,
                                          (U1)WCHIME_VOL_CSR_RCTA_5,
                                          (U1)WCHIME_VOL_CSR_RCTA_6,
                                          (U1)WCHIME_VOL_CSR_RCTA_7      }}
    };

    U1    u1_t_reqvol;
    U1    u1_t_volindex;
    U4    u4_t_loopcnt;

    u1_t_reqvol = (U1)U1_MAX;

    for(u4_t_loopcnt = (U4)0U; u4_t_loopcnt < (U4)WCHIME_CSR_VOL_LIST_NUM; u4_t_loopcnt++){
        if(u1_a_REQ_SEL == st_sp_WCHIME_CSR_VOL_LIST[u4_t_loopcnt].u1_reqid){
            switch(u1_g_wchime_alrt_csr_vol_now){
                case (U1)ALERT_REQ_S_CLESON_VOL_VOL0:
                    u1_t_volindex = (U1)WCHIME_CSR_VOL_INDEX_0;
                    break;
                case (U1)ALERT_REQ_S_CLESON_VOL_VOL1:
                    u1_t_volindex = (U1)WCHIME_CSR_VOL_INDEX_1;
                    break;
                case (U1)ALERT_REQ_S_CLESON_VOL_VOL2:
                    u1_t_volindex = (U1)WCHIME_CSR_VOL_INDEX_2;
                    break;
                case (U1)ALERT_REQ_S_CLESON_VOL_VOL3:
                    u1_t_volindex = (U1)WCHIME_CSR_VOL_INDEX_3;
                    break;
                case (U1)ALERT_REQ_S_CLESON_VOL_VOL4:
                    u1_t_volindex = (U1)WCHIME_CSR_VOL_INDEX_4;
                    break;
                case (U1)ALERT_REQ_S_CLESON_VOL_VOL5:
                    u1_t_volindex = (U1)WCHIME_CSR_VOL_INDEX_5;
                    break;
                case (U1)ALERT_REQ_S_CLESON_VOL_VOL6:
                    u1_t_volindex = (U1)WCHIME_CSR_VOL_INDEX_6;
                    break;
                case (U1)ALERT_REQ_S_CLESON_VOL_VOL7:
                    u1_t_volindex = (U1)WCHIME_CSR_VOL_INDEX_7;
                    break;
                default:
                    u1_t_volindex = (U1)WCHIME_CSR_VOL_INDEX_7;
                    break;
            }
            u1_t_reqvol = st_sp_WCHIME_CSR_VOL_LIST[u4_t_loopcnt].u1_req_vol[u1_t_volindex];
            break;
        }
    }

    return(u1_t_reqvol);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     3/ 2/2018  TN       New.                                                                                               */
/*  1.1.0     3/27/2018  TN       wchime_arb.c v1.0.0 -> v1.1.0.                                                                     */
/*  1.2.0    11/19/2018  TN       wchime_arb.c v1.1.0 -> v1.2.0.                                                                     */
/*  1.3.0     4/ 2/2020  ToN      wchime_arb.c v1.2.0 -> v1.3.0.                                                                     */
/*  1.4.0     7/21/2020  SK       wchime_arb.c v1.3.0 -> v1.4.0.                                                                     */
/*  1.4.1    11/24/2020  TF       wchime_arb.c v1.4.0 -> v1.4.1.                                                                     */
/*  1.5.0    12/23/2020  YK       wchime_arb.c v1.4.1 -> v1.5.0.                                                                     */
/*  2.0.1    10/21/2021  MG       wchime_arb.c v1.5.0 -> v2.0.1.                                                                     */
/*  2.1.0    11/12/2024  GM       wchime_arb.c v2.0.1 -> v2.1.0.                                                                     */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  800B-1    8/28/2020  YK       Appry 800B CV-R spec.                                                                              */
/*  800B-2   11/18/2020  SK       Correct sound pressure settings for WCHIME_REQ_IN_PKSB, WCHIME_REQ_IN_DOA, WCHIME_REQ_SI_FCTA,     */
/*                                and WCHIME_REQ_IN_DESA_R04.                                                                        */
/*  800B-3   12/23/2020  YK       Add the function to judge whether to buzzer until the end of 1 cycle or not,                       */
/*                                depend on the buzzer condition.                                                                    */
/*                                Improvement : u1_gp_WCHIME_REQ_SW_CTRL[] -> u1_g_wChimeReqSwCtrl(...)                              */
/*                                Apply priority order list of buzzer for 1A.                                                        */
/*  800B-4    2/11/2021  TF       Changes the volume setting of the reverse buzzer.                                                  */
/*  840B-1    4/19/2021  MG       Apply priority order list of buzzer for CV.                                                        */
/*  300D-1    7/20/2021  MG       Apply priority order list of buzzer for CV.                                                        */
/*  893B-1   11/11/2021  MG       Apply priority order list of buzzer for 1A.                                                        */
/*  200D-1    7/19/2022  YK       Apply priority order list of buzzer for Pre1A.                                                     */
/*  200D-2   10/13/2022  YK       Apply priority order list of buzzer for 1A.                                                        */
/*  200D-3   12/13/2022  SK       Change sound pressure for RCTA buzzer.                                                             */
/*  330D-1    1/11/2023  YKu      Apply priority order list of buzzer for CV-R.                                                      */
/*                                Add processing for Advanced Park buzzer Wait Time                                                  */
/*  330D-2    2/ 2/2023  YK       Apply priority order list of buzzer for CV-R2.                                                     */
/*  330D-3    3/14/2023  YK       Apply priority order list of buzzer for 1A.                                                        */
/*  330D-4    6/ 1/2023  YK       Apply priority order list of buzzer for MPT.                                                       */
/*  19PFv3-1  9/22/2023  SH       Add TURHAZ for each vehicle speed and separate TURHAZ by brand                                     */
/*                                Add u1_g_McstBfStb() to customize volume                                                           */
/*  19PFv3-2 12/22/2023  SI       Replace u1_g_McstBfStb() to u1_g_McstBf()                                                          */
/*                                Add parameter of MET-M_MWVCUS-                                                                     */
/*  19PFv3-3  1/19/2024  YR       Remove buzzer request for BRKHLD                                                                   */
/*  19PFv3-4  2/ 9/2024  SW       Add parameter of MET-M_MINDSPWR-                                                                   */
/*  19PFv3-5  2/16/2024  SH       Change MCUCONST v010->v012                                                                         */
/*  19PFv3-6  2/20/2024  GM       Change config for 19PFv3 CV                                                                        */
/*  19PFv3-7  4/23/2024  TR      Deleted RCTA Volume logic                                                                           */
/*  19PFv3-8  5/13/2024  DR       Changed the volume of master caution buuzzer                                                       */
/*  19PFv3-8  5/13/2024  YR       Change FCTA priority                                                                               */
/*  19PFv3-9  7/10/2024  TR       Add SBRDMB buzzer req                                                                              */
/*  19PFv3-10 9/12/2024  YR       Change SFTPOS buzzer and ITS buzzer config                                                         */
/*  19PFv3-11 9/16/2024  YR       Change config for Master Caution, SBW and Turn Hazard                                              */
/*  19PFv3-12 10/23/2024 TeN      Change RSA(Lexus) buzzer config.                                                                   */
/*  19PFv3-13 03/20/2025 SH       Added config for BATTRW                                                                            */
/*  19PFv3-14 04/07/2025 SH       Change Reverse buzzer name                                                                         */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*  * ToN  = Toshiharu Nagata, Denso Techno                                                                                          */
/*  * SK   = Sakae Kitamura, Denso Techno                                                                                            */
/*  * YK   = Yuki Kawai, Denso Techno                                                                                                */
/*  * TF   = Tomohiro Furuichi, Denso Techno                                                                                         */
/*  * MG   = Mei Godo, KSE                                                                                                           */
/*  * YKu  = Yuta Kusunoki, Denso Techno                                                                                             */
/*  * SH   = Sae Hirose, Denso Techno                                                                                                */
/*  * SI   = Shugo Ichinose, Denso Techno                                                                                            */
/*  * YR   = Yhana Regalario, Denso Techno Phil. Inc.                                                                                */
/*  * SW   = Shun Watanabe, Denso Techno                                                                                             */
/*  * GM   = Glen Monteposo, DTPH                                                                                                    */
/*  * TR   = Tebs Ramos, DTPH                                                                                                        */
/*  * DR   = Dyan Reyes, DTPH                                                                                                        */
/*  * TeN  = Tetsushi Nakano, Denso Techno                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
