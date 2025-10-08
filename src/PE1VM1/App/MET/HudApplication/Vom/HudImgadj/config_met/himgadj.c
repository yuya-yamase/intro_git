/* 2.2.4 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  HUD Image Adjudt                                                                                                                 */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HUDIMGADJ_C_MAJOR                        (2)
#define HUDIMGADJ_C_MINOR                        (2)
#define HUDIMGADJ_C_PATCH                        (4)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"

#include "himgadj.h"

#include "mcst.h"
#include "vardef.h"

#include "oxcan.h"
#include "nvmc_mgr.h"
#include "veh_opemd.h"

#include "calibration.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((HUDIMGADJ_C_MAJOR != HUDIMGADJ_H_MAJOR) || \
     (HUDIMGADJ_C_MINOR != HUDIMGADJ_H_MINOR) || \
     (HUDIMGADJ_C_PATCH != HUDIMGADJ_H_PATCH))
#error "source and header files are inconsistent!"
#endif /* (HUDIMGADJ_C_MAJOR != HUDIMGADJ_H_MAJOR)... */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/*  INTERFACE                                                                */
/*---------------------------------------------------------------------------*/
#define HUDIMGADJ_IF_TIMOUT_MAX             (65534U)                     /* Don't change!!! */

/*---------------------------------------------------------------------------*/
/*  OVERWRITE_STEP(I/O Control)                                              */
/*---------------------------------------------------------------------------*/
#define HUDIMGADJ_OW_ACTTO                  (5000U / 10U)                 /* 5000ms */
#define HUDIMGADJ_OW_INACTV                 (0x0000U)
#define HUDIMGADJ_OW_ACTV                   (0xFFFFU)

#define HUDIMGADJ_OWCTL_POS_CNT             (0U)
#define HUDIMGADJ_OWCTL_POS_L1              (1U)
#define HUDIMGADJ_OWCTL_POS_L2              (2U)
#define HUDIMGADJ_OWCTL_POS_L3              (3U)
#define HUDIMGADJ_OWCTL_POS_U1              (0xFDU)
#define HUDIMGADJ_OWCTL_POS_U2              (0xFEU)
#define HUDIMGADJ_OWCTL_POS_U3              (0xFFU)

#define HUDIMGADJ_OWCTL_POS_NG_VAL          (0xFFFFU)

#define HUDIMGADJ_OWCTL_POS_CALC_DIV        (3U)
#define HUDIMGADJ_OWCTL_POS_CALC_CRCT       (2U)
#define HUDIMGADJ_OWCTL_POS_CALC_ROUND      (2U)
#define HUDIMGADJ_OWCTL_POS_CALC_PLSLSB_SFT (1U)

#define HUDIMGADJ_OWCTL_RDPOS_CALC_DIV      (2U)
#define HUDIMGADJ_OWCTL_RFPOS_CALC_CRCT     (1U)
#define HUDIMGADJ_OWCTL_RDPOS_CALC_ROUND    (1U)

/*---------------------------------------------------------------------------*/
/*  DIAG_CUSTOMIZE(DID 2003)                                                 */
/*---------------------------------------------------------------------------*/
#define HUDIMGADJ_CSTMZ_DRVPS_SWACT         (0x40U)
#define HUDIMGADJ_CSTMZ_DRVPS_INITVAL       (HUDIMGADJ_CSTMZ_DRVPS_SWACT)

/*---------------------------------------------------------------------------*/
/*  USER_SWITCH_OPERATION                                                    */
/*---------------------------------------------------------------------------*/
#define HUDIMGADJ_SWSGNL_STRSW_UP           (0x08U)
#define HUDIMGADJ_SWSGNL_STRSW_DN           (0x04U)
#define HUDIMGADJ_SWSGNL_LVPS_UP            (0x02U)
#define HUDIMGADJ_SWSGNL_LVPS_DN            (0x01U)
#define HUDIMGADJ_SWSGNL_MAX                (0x10U)

#define HUDIMGADJ_SWACT_DN                  (0U)
#define HUDIMGADJ_SWACT_UP                  (1U)
#define HUDIMGADJ_SWACT_MAX                 (2U)

/*---------------------------------------------------------------------------*/
/*  DRIVING_POSITION                                                         */
/*---------------------------------------------------------------------------*/
#define HUDIMGADJ_RDDTUNDEF                 (0xFFFFU)
#define HUDIMGADJ_RDDTERR                   (0xFFFFU)

#define HUDIMGADJ_CAN_DRVPSDT_NON           (0x00U)
#define HUDIMGADJ_CAN_DRVPSREQ_NON          (0x00U)
#define HUDIMGADJ_CAN_DRVPSREQ_MEM          (0x01U)
#define HUDIMGADJ_CAN_DRVPSREQ_MOV          (0x02U)

#define HUDIMGADJ_DRVPSREQ_NON              (0U)
#define HUDIMGADJ_DRVPSREQ_MEM              (1U)
#define HUDIMGADJ_DRVPSREQ_MOV              (2U)
#define HUDIMGADJ_NUM_RVPSREQ               (4U)

#define HUDIMGADJ_DRVPSDT_NON               (255U)
#define HUDIMGADJ_DRVPSDT_01                (1U)                        /* User1 Memory No1    */
#define HUDIMGADJ_DRVPSDT_02                (2U)                        /* User1 Memory No2    */
#define HUDIMGADJ_DRVPSDT_03                (3U)                        /* User1 Memory No3    */
#define HUDIMGADJ_DRVPSDT_04                (4U)                        /* User1 Last Position */
#define HUDIMGADJ_DRVPSDT_05                (5U)                        /* User2 Memory No1    */
#define HUDIMGADJ_DRVPSDT_06                (6U)                        /* User2 Memory No2    */
#define HUDIMGADJ_DRVPSDT_07                (7U)                        /* User2 Memory No3    */
#define HUDIMGADJ_DRVPSDT_08                (8U)                        /* User2 Last Position */
#define HUDIMGADJ_DRVPSDT_09                (9U)                        /* User3 Memory No1    */
#define HUDIMGADJ_DRVPSDT_10                (10U)                       /* User3 Memory No2    */
#define HUDIMGADJ_DRVPSDT_11                (11U)                       /* User3 Memory No3    */
#define HUDIMGADJ_DRVPSDT_12                (12U)                       /* User3 Last Position */
#define HUDIMGADJ_DRVPSDT_13                (13U)                       /* Guest Memory No1    */
#define HUDIMGADJ_DRVPSDT_14                (14U)                       /* Guest Memory No2    */
#define HUDIMGADJ_DRVPSDT_15                (15U)                       /* Guest Memory No3    */
#define HUDIMGADJ_NUM_DRVPS_DT              (16U)

#define HUDIMGADJ_SGNL_NONE                 (0x00000000U)
#define HUDIMGADJ_SGNL_MEMREQ               (0x00000001U)
#define HUDIMGADJ_SGNL_MEMREQONEDGE         (0x00000001U)
#define HUDIMGADJ_SGNL_MEMREQOFFEDGE        (0x00000002U)
#define HUDIMGADJ_SGNL_MEMREQMASK           (0x00000003U)
#define HUDIMGADJ_SGNL_MOVREQ               (0x00000010U)
#define HUDIMGADJ_SGNL_MOVREQONEDGE         (0x00000010U)
#define HUDIMGADJ_SGNL_MOVREQOFFEDGE        (0x00000020U)
#define HUDIMGADJ_SGNL_MOVREQMASK           (0x00000030U)
#define HUDIMGADJ_SGNL_RDVPSCHGREQ          (0x00000100U)
#define HUDIMGADJ_SGNL_RDVPSCHGONEDGE       (0x00000100U)
#define HUDIMGADJ_SGNL_RDVPSCHGOFFEDGE      (0x00000200U)
#define HUDIMGADJ_SGNL_RDVPSCHGMASK         (0x00000300U)
#define HUDIMGADJ_SGNL_MASK                 (HUDIMGADJ_SGNL_MEMREQMASK | HUDIMGADJ_SGNL_MOVREQMASK)

#define HUDIMGADJ_MOVEVT_NONE               (0x00U)
#define HUDIMGADJ_MOVEVT_IDEQL              (0x01U)
#define HUDIMGADJ_MOVEVT_TIMOUT             (0x02U)
#define HUDIMGADJ_MOVEVT_MOVEREQ            (0x04U)
#define HUDIMGADJ_MOVEVT_MAX                (0x08U)

#define HUDIMGADJ_MOVSTS_TIMOUT             (10000U / 10U)

#define HUDIMGADJ_MOVSTS_STP                (0U)
#define HUDIMGADJ_MOVSTS_MOV                (1U)
#define HUDIMGADJ_MOVSTS_MAX                (2U)

#define HUDIMGADJ_MOVACT_STP_INI_CLR        (0U)
#define HUDIMGADJ_MOVACT_MOV_SET_CLR        (1U)
#define HUDIMGADJ_MOVACT_MOV_HLD_NON        (2U)

#define HUDIMGADJ_IDINVLD                   (0xFFU)
#define HUDIMGADJ_IMGPOSINVLD               (0xFFFFU)

#define HUDIMGADJ_HUDSTEVT_NONE             (0x00U)
#define HUDIMGADJ_HUDSTEVT_PLYREQ           (0x01U)
#define HUDIMGADJ_HUDSTEVT_CUSTOM           (0x02U)

#define HUDIMGADJ_HUDST_OFFST_NUM           (4U)
#define HUDIMGADJ_HUDST_OFFST_NON           (0x00U)
#define HUDIMGADJ_HUDST_OFFST_MAN           (0x04U)
#define HUDIMGADJ_HUDST_OFFST_PLY           (0x08U)

#define HUDIMGADJ_HUDSTEVT_MAX              (12U)

#define HUDIMGADJ_HUDCTLSTS_STP             (0U)
#define HUDIMGADJ_HUDCTLSTS_MAN             (1U)
#define HUDIMGADJ_HUDCTLSTS_PLY             (2U)
#define HUDIMGADJ_HUDCTLSTS_MAX             (3U)

#define HUDIMGADJ_HUDST_UNDET               (0U)
#define HUDIMGADJ_HUDST_STP                 (1U)
#define HUDIMGADJ_HUDST_MAN                 (2U)
#define HUDIMGADJ_HUDST_PLY                 (3U)

#define HUDIMGADJ_HUDSTACT_STP_STP_NON      (0U)
#define HUDIMGADJ_HUDSTACT_MAN_MAN_NON      (1U)
#define HUDIMGADJ_HUDSTACT_PLY_PLY_NON      (2U)
#define HUDIMGADJ_HUDSTACT_PLY_PLY_CLR      (3U)

#define HUDIMGADJ_HUDSTSHLDTIMR_TIM         ((160U * 2U) / 10U)            /* EVENT_INT Send Guard */

/*---------------------------------------------------------------------------*/
/*  ZEROPOS_INIT(Routine Control)                                            */
/*---------------------------------------------------------------------------*/
#define HUDIMGADJ_RTCTLSTS_IDLE             (0U)
#define HUDIMGADJ_RTCTLSTS_WAIT             (1U)
#define HUDIMGADJ_RTCTLSTS_RUN              (2U)
#define HUDIMGADJ_RTCTLSTS_NML              (3U)
#define HUDIMGADJ_RTCTLSTS_ERR              (4U)
#define HUDIMGADJ_RTCTLSTS_MAX              (5U)

#define HUDIMGADJ_RTCTLEVT_NONE             (0x00U)
#define HUDIMGADJ_RTCTLEVT_INPTCNT          (0x01U)
#define HUDIMGADJ_RTCTLEVT_ZPDCMP           (0x02U)
#define HUDIMGADJ_RTCTLEVT_TIMOUT           (0x04U)
#define HUDIMGADJ_RTCTLEVT_RTCTLRQ          (0x08U)
#define HUDIMGADJ_RTCTLEVT_MAX              (0x10U)

#define HUDIMGADJ_RTCTLACT_IDLE_OFF_CMP     (0U)
#define HUDIMGADJ_RTCTLACT_WAIT_ON_CLR      (1U)
#define HUDIMGADJ_RTCTLACT_WAIT_ON_HLD      (2U)
#define HUDIMGADJ_RTCTLACT_RUN_ON_HLD       (3U)
#define HUDIMGADJ_RTCTLACT_NML_OFF_CMP      (4U)
#define HUDIMGADJ_RTCTLACT_ERR_OFF_CMP      (5U)

#define HUDIMGADJ_RTCTL_INPTTIM             (1000U / 10U)
#define HUDIMGADJ_RTCTL_RESTIME_LSB         (1000U / 10U)
#define HUDIMGADJ_RTCTL_ZPDJDG              (0xFFFFU)

#define HUDIMGADJ_RTCTL_NON                 (0x00U)
#define HUDIMGADJ_RTCTL_REQ                 (0xA5U)
#define HUDIMGADJ_RTCTL_INITREQ             (0xA5U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/*  INTERFACE                                                                */
/*---------------------------------------------------------------------------*/
static U2   u2_s_himgadj_iftimout;

static U1   u1_s_himgadj_upstrsw;
static U1   u1_s_himgadj_dwstrsw;
static U1   u1_s_himgadj_l_up_possw;
static U1   u1_s_himgadj_l_dn_possw;

static U2   u2_s_himgadj_gv_vipos_respos;
static U2   u2_s_himgadj_gv_vipos_movpos;
static U2   u2_s_himgadj_gv_vipos_minpos;
static U2   u2_s_himgadj_gv_vipos_teppos;
static U2   u2_s_himgadj_gv_vipos_maxpos;
static U1   u1_s_himgadj_gv_vipos_resid;

static U1   u1_s_himgadj_gv_vipos_hudst;

/*---------------------------------------------------------------------------*/
/*  OVERWRITE_STEP(I/O Control)                                              */
/*---------------------------------------------------------------------------*/
static U4   u4_s_himgadj_owstp_ow_unlock;
static U2   u2_s_himgadj_owstp_ow_act;
static U2   u2_s_himgadj_owstp_tocnt;
static U2   u2_s_himgadj_owstp_ow_pos;

/*---------------------------------------------------------------------------*/
/*  DIAG_CUSTOMIZE(DID 2003)                                                 */
/*---------------------------------------------------------------------------*/
static U1   u1_s_himgadj_cstmz_drvps;

/*---------------------------------------------------------------------------*/
/*  USER_SWITCH_OPERATION                                                    */
/*---------------------------------------------------------------------------*/
static U1   u1_s_himgadj_is_upswon;
static U1   u1_s_himgadj_is_dnswon;

/*---------------------------------------------------------------------------*/
/*  DRIVING_POSITION                                                         */
/*---------------------------------------------------------------------------*/
static U4   u4_s_himgadj_drvpos_sgnl;
static U2   u2_sp_himgadj_imgpos[HUDIMGADJ_NUM_DRVPS_DT];

static U2   u2_s_himgadj_stshldtimr;
static U2   u2_s_himgadj_movreq_pos;
static U2   u2_s_himgadj_movsts_tim;
static U1   u1_s_himgadj_movsts;
static U1   u1_s_himgadj_movreq_id;

static U1   u1_s_himgadj_drvpsbak;
static U1   u1_s_himgadj_hudreqbak;
static U1   u1_s_himgadj_hudctrlsts;

/*---------------------------------------------------------------------------*/
/*  ZEROPOS_INIT(Routine Control)                                            */
/*---------------------------------------------------------------------------*/
static U2   u2_s_himgadj_dgrtctltimr;
static U1   u1_s_himgadj_dgrtctrlsts;
static U1   u1_s_himgadj_dgrtctl_req;
static U1   u1_s_himgadj_dgrtinitreq;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/*  DRIVING_POSITION                                                         */
/*---------------------------------------------------------------------------*/
static const U2 u2_sp_HUDIMGADJ_TBL_NVMCID_DRVPSDT[HUDIMGADJ_NUM_DRVPS_DT] =
{
    (U2)U2_MAX,                            /* Position Request None */
    (U2)NVMCID_U2_DRVPS_MRRPOS01,          /* User1 Memory No1      */
    (U2)NVMCID_U2_DRVPS_MRRPOS02,          /* User1 Memory No2      */
    (U2)NVMCID_U2_DRVPS_MRRPOS03,          /* User1 Memory No3      */
    (U2)NVMCID_U2_DRVPS_MRRPOS04,          /* User1 Last Position   */
    (U2)NVMCID_U2_DRVPS_MRRPOS05,          /* User2 Memory No1      */
    (U2)NVMCID_U2_DRVPS_MRRPOS06,          /* User2 Memory No2      */
    (U2)NVMCID_U2_DRVPS_MRRPOS07,          /* User2 Memory No3      */
    (U2)NVMCID_U2_DRVPS_MRRPOS08,          /* User2 Last Position   */
    (U2)NVMCID_U2_DRVPS_MRRPOS09,          /* User3 Memory No1      */
    (U2)NVMCID_U2_DRVPS_MRRPOS10,          /* User3 Memory No2      */
    (U2)NVMCID_U2_DRVPS_MRRPOS11,          /* User3 Memory No3      */
    (U2)NVMCID_U2_DRVPS_MRRPOS12,          /* User3 Last Position   */
    (U2)NVMCID_U2_DRVPS_MRRPOS13,          /* Guest Memory No1      */
    (U2)NVMCID_U2_DRVPS_MRRPOS14,          /* Guest Memory No2      */
    (U2)NVMCID_U2_DRVPS_MRRPOS15           /* Guest Memory No3      */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/*  INTERFACE                                                                */
/*---------------------------------------------------------------------------*/
static void vd_s_HudImgAdjIfInit(void);
static void vd_s_HudImgAdjIfUpdt(void);
static U1   u1_s_HudImgAdjGetHudSts(void);
/* void        vd_g_HudImgAdjSetUpDwSw(const U1 u1_a_UPSW, const U1 u1_a_DWSW); */
/* void        vd_g_HudImgAdjSet_L_VIPOS_UPDW(const U1 u1_a_UPSW, const U1 u1_a_DWSW); */
/* void        vd_g_HudImgAdjSet_GV_VIPOS_RESPOS(const U2 u2_a_GV_VIPOS_RESPOS); */           /* GV_VIPOS_RESPOS    */
/* void        vd_g_HudImgAdjSet_GV_VIPOS_MOVPOS(const U2 u2_a_GV_VIPOS_MOVPOS); */           /* GV_VIPOS_MOVPOS    */
/* void        vd_g_HudImgAdjSet_GV_VIPOS_ADJMINPOS(const U2 u2_a_GV_VIPOS_ADJMINPOS); */     /* GV_VIPOS_ADJMINPOS */
/* void        vd_g_HudImgAdjSet_GV_VIPOS_ADJTEPPOS(const U2 u2_a_GV_VIPOS_ADJTEPPOS); */     /* GV_VIPOS_ADJTEPPOS */
/* void        vd_g_HudImgAdjSet_GV_VIPOS_ADJMAXPOS(const U2 u2_a_GV_VIPOS_ADJMAXPOS); */     /* GV_VIPOS_ADJMAXPOS */
/* void        vd_g_HudImgAdjSet_GV_VIPOS_RESID(const U1 u1_a_GV_VIPOS_RESID); */             /* GV_VIPOS_RESID     */
/* void        vd_g_HudImgAdjSet_GV_VIPOS_HUD_ST(const U1 u1_a_GV_VIPOS_HUD_ST); */           /* GV_VIPOS_HUD_ST    */

/*---------------------------------------------------------------------------*/
/*  OVERWRITE_STEP(I/O Control)                                              */
/*---------------------------------------------------------------------------*/
static void vd_s_HudImgAdjowstpInit(void);
static void vd_s_HudImgAdjOwStpUpdt(void);
/* void        vd_g_HudImgAdjowstpUnlock(const U4 u4_a_KEY); */
/* void        vd_g_HudImgAdjowstpOwAct(const U1 u1_a_REQ); */
/* void        vd_g_HudImgAdjowstpOwDeAct(void); */
/* U1          u1_g_HudImgAdjGetGvOwReq(void); */         /* GV_DG_VIPOS_REQ  */
/* U2          u2_g_HudImgAdjGetGvOwPos(void); */         /* GV_DG_VIPOS_POS  */
static U2   u2_s_HudImgAdjowimgpos(const U1 u1_a_REQ);
/* U1          u1_g_HudImgAdjReadDataImgPos(U1 * u1_ap_pos); */

/*---------------------------------------------------------------------------*/
/*  DIAG_CUSTOMIZE(DID 2003)                                                 */
/*---------------------------------------------------------------------------*/
static void vd_s_HudImgAdjCustomDrvPsInit(void);
static void vd_s_HudImgAdjUpdtCustomDrvPs(void);
static U1   u1_s_HudImgAdjGetCustomDrvPs(const U1 u1_a_CUSTOMTYPE);

/*---------------------------------------------------------------------------*/
/*  USER_SWITCH_OPERATION                                                    */
/*---------------------------------------------------------------------------*/
static void vd_s_HudImgAdjSwInit(void);
static void vd_s_HudImgAdjSwTask(void);
/* U1          u1_g_HudImgAdjIsUpSwOn(void); */                                               /* GV_VIPOS_UPSW      */
/* U1          u1_g_HudImgAdjIsDnSwOn(void); */                                               /* GV_VIPOS_DNSW      */

/*---------------------------------------------------------------------------*/
/*  DRIVING_POSITION                                                         */
/*---------------------------------------------------------------------------*/
static void vd_s_HudImgAdjDrvPsInit(void);
static void vd_s_HudImgAdjDrvPsInvalidInit(void);
static U2   u2_s_HudImgAdjDrvPsReadData(const U1 u1_a_ID);
static void vd_s_HudImgAdjDrvPsUpdt(void);
static void vd_s_HudImgAdjDrvPsMemUpdt(const U4 u4_a_SGNL, const U1 u1_a_ID);
static void vd_s_HudImgAdjDrvPsMovUpdt(const U4 u4_a_SGNL, const U1 u1_a_ID);
static void vd_s_HudImgAdjDrvPsMovActn(const U1 u1_a_EVT, const U1 u1_a_ID, const U2 u2_a_IMGPOS);
static void vd_s_HudImgAdjDrvPsHudStsUpdt(const U4 u4_a_SGNL);
static void vd_s_HudImgAdjDrvPsHudStsActn(const U1 u1_a_EVT);
/* U2          u2_g_HudImgAdjGetMovReqPos(void); */                                           /* GV_VIPOS_REQPOS    */
/* U1          u1_g_HudImgAdjGetMovReqID(void); */                                            /* GV_VIPOS_REQID     */

/*---------------------------------------------------------------------------*/
/*  ZEROPOS_INIT(Routine Control)                                            */
/*---------------------------------------------------------------------------*/
static void vd_s_HudImgAdjRoutInit(void);
static void vd_s_HudImgAdjRoutCtrl(void);
static void vd_s_HudImgAdjRoutCtrlActn(const U1 u1_a_EVT);
/* U1          u1_g_HudImgAdjRoutRslt(void); */
/* U1          u1_g_HudImgAdjRoutStartIsOK(void); */
/* U1          u1_g_HudImgAdjGetGvRtctlIniReq(void); */                                       /* GV_DG_VIPOS_INIT   */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  Initialization processing at the time of BON,wake up is performed                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments    -                                                                                                                   */
/*  Return       -                                                                                                                   */
/*===================================================================================================================================*/
void vd_g_HudImgAdjInit(void)
{
    /*-----------------------------------------------------------------------*/
    /*  INTERFACE                                                            */
    /*-----------------------------------------------------------------------*/
    vd_s_HudImgAdjIfInit();

    /*-----------------------------------------------------------------------*/
    /*  OVERWRITE_STEP(I/O Control)                                          */
    /*-----------------------------------------------------------------------*/
    vd_s_HudImgAdjowstpInit();

    /*-----------------------------------------------------------------------*/
    /*  DIAG_CUSTOMIZE(DID 2003)                                             */
    /*-----------------------------------------------------------------------*/
    vd_s_HudImgAdjCustomDrvPsInit();

    /*-----------------------------------------------------------------------*/
    /*  USER_SWITCH_OPERATION                                                */
    /*-----------------------------------------------------------------------*/
    vd_s_HudImgAdjSwInit();

    /*-----------------------------------------------------------------------*/
    /*  DRIVING_POSITION                                                     */
    /*-----------------------------------------------------------------------*/
    vd_s_HudImgAdjDrvPsInit();

    /*-----------------------------------------------------------------------*/
    /*  ZEROPOS_INIT(Routine Control)                                        */
    /*-----------------------------------------------------------------------*/
    vd_s_HudImgAdjRoutInit();
}

/*===================================================================================================================================*/
/*  processing HUD Image Adjudt                                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments    -                                                                                                                   */
/*  Return       -                                                                                                                   */
/*===================================================================================================================================*/
void vd_g_HudImgAdjMainTask(void)
{
    U1  u1_t_hudvalid;

    u1_t_hudvalid = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_GVIF2);
    if(u1_t_hudvalid == (U1)TRUE){
        /*-----------------------------------------------------------------------*/
        /*  INTERFACE                                                            */
        /*-----------------------------------------------------------------------*/
        vd_s_HudImgAdjIfUpdt();

        /*-----------------------------------------------------------------------*/
        /*  OVERWRITE_STEP(I/O Control)                                          */
        /*-----------------------------------------------------------------------*/
        vd_s_HudImgAdjOwStpUpdt();

        /*-----------------------------------------------------------------------*/
        /*  DIAG_CUSTOMIZE(DID 2003)                                             */
        /*-----------------------------------------------------------------------*/
        vd_s_HudImgAdjUpdtCustomDrvPs();

        /*-----------------------------------------------------------------------*/
        /*  USER_SWITCH_OPERATION                                                */
        /*-----------------------------------------------------------------------*/
        vd_s_HudImgAdjSwTask();

        /*-----------------------------------------------------------------------*/
        /*  DRIVING_POSITION                                                     */
        /*-----------------------------------------------------------------------*/
        vd_s_HudImgAdjDrvPsUpdt();

        /*-----------------------------------------------------------------------*/
        /*  ZEROPOS_INIT(Routine Control)                                        */
        /*-----------------------------------------------------------------------*/
        vd_s_HudImgAdjRoutCtrl();
    }
    else{
        /*-----------------------------------------------------------------------*/
        /*  INTERFACE                                                            */
        /*-----------------------------------------------------------------------*/
        vd_s_HudImgAdjIfInit();

        /*-----------------------------------------------------------------------*/
        /*  OVERWRITE_STEP(I/O Control)                                          */
        /*-----------------------------------------------------------------------*/
        vd_s_HudImgAdjowstpInit();

        /*-----------------------------------------------------------------------*/
        /*  DIAG_CUSTOMIZE(DID 2003)                                             */
        /*-----------------------------------------------------------------------*/
        /* vd_s_HudImgAdjCustomDrvPsInit(); */

        /*-----------------------------------------------------------------------*/
        /*  USER_SWITCH_OPERATION                                                */
        /*-----------------------------------------------------------------------*/
        vd_s_HudImgAdjSwInit();

        /*-----------------------------------------------------------------------*/
        /*  DRIVING_POSITION                                                     */
        /*-----------------------------------------------------------------------*/
        vd_s_HudImgAdjDrvPsInvalidInit();

        /*-----------------------------------------------------------------------*/
        /*  ZEROPOS_INIT(Routine Control)                                        */
        /*-----------------------------------------------------------------------*/
        vd_s_HudImgAdjRoutInit();
    }
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  INTERFACE Function Definitions                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  INTERFACE : static void vd_s_HudImgAdjIfInit(void)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_HudImgAdjIfInit(void)
{
    u2_s_himgadj_iftimout = (U2)HUDIMGADJ_IF_TIMOUT_MAX;

    u1_s_himgadj_upstrsw = (U1)FALSE;
    u1_s_himgadj_dwstrsw = (U1)FALSE;
    u1_s_himgadj_l_up_possw = (U1)FALSE;
    u1_s_himgadj_l_dn_possw = (U1)FALSE;

    u2_s_himgadj_gv_vipos_respos = (U2)HUDIMGADJ_IMGPOSINVLD;
    u2_s_himgadj_gv_vipos_movpos = (U2)HUDIMGADJ_IMGPOSINVLD;
    u2_s_himgadj_gv_vipos_minpos = (U2)HUDIMGADJ_IMGPOSINVLD;
    u2_s_himgadj_gv_vipos_teppos = (U2)HUDIMGADJ_IMGPOSINVLD;
    u2_s_himgadj_gv_vipos_maxpos = (U2)HUDIMGADJ_IMGPOSINVLD;
    u1_s_himgadj_gv_vipos_resid  = (U1)HUDIMGADJ_IDINVLD;

    u1_s_himgadj_gv_vipos_hudst = (U1)HUDIMGADJ_HUDST_STP;
}

/*===================================================================================================================================*/
/*  INTERFACE : static void vd_s_HudImgAdjIfUpdt(void)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_HudImgAdjIfUpdt(void)
{
    static const U2 u2_s_HUDIMGADJ_IF_TIMOUT = (U2)100U;      /* U2_MAX: hold, 1sec: LSB:10ms */

    U1 u1_t_ig;

    if(u2_s_himgadj_iftimout < (U2)HUDIMGADJ_IF_TIMOUT_MAX){
        u2_s_himgadj_iftimout += (U2)1U;
    }
    else{
        u2_s_himgadj_iftimout = (U2)HUDIMGADJ_IF_TIMOUT_MAX;
    }
    if(u2_s_himgadj_iftimout >= u2_s_HUDIMGADJ_IF_TIMOUT){
        vd_s_HudImgAdjIfInit();
    }

    u1_t_ig = u1_g_VehopemdIgnOn();
    if(u1_t_ig != (U1)TRUE){
        u1_s_himgadj_l_up_possw = (U1)FALSE;
        u1_s_himgadj_l_dn_possw = (U1)FALSE;
    }
}

/*===================================================================================================================================*/
/*  INTERFACE : static U1   u1_s_HudImgAdjGetHudSts(void)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1   u1_s_HudImgAdjGetHudSts(void)
{
    U1  u1_t_hudonoff;
    U1  u1_t_ishudon;

    u1_t_ishudon  = (U1)FALSE;
    u1_t_hudonoff = u1_g_McstBf((U1)MCST_BFI_HUD);
    if(u1_t_hudonoff == (U1)MCST_HUD_ON){
        u1_t_ishudon = (U1)TRUE;
    }
    return(u1_t_ishudon);
}

/*===================================================================================================================================*/
/*  INTERFACE : void    vd_g_HudImgAdjSetUpDwSw(const U1 u1_a_UPSW, const U1 u1_a_DWSW)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HudImgAdjSetUpDwSw(const U1 u1_a_UPSW, const U1 u1_a_DWSW)
{
    u1_s_himgadj_upstrsw = u1_a_UPSW;
    u1_s_himgadj_dwstrsw = u1_a_DWSW;
    u2_s_himgadj_iftimout = (U2)0U;
}

/*===================================================================================================================================*/
/*  INTERFACE : void    vd_g_HudImgAdjSet_L_VIPOS_UPDW(const U1 u1_a_UPSW, const U1 u1_a_DWSW)                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HudImgAdjSet_L_VIPOS_UPDW(const U1 u1_a_UPSW, const U1 u1_a_DWSW)
{
    u1_s_himgadj_l_up_possw = u1_a_UPSW;
    u1_s_himgadj_l_dn_possw = u1_a_DWSW;
    u2_s_himgadj_iftimout = (U2)0U;
}

/*===================================================================================================================================*/
/*  INTERFACE : void    vd_g_HudImgAdjSet_GV_VIPOS_RESPOS(const U2 u2_a_GV_VIPOS_RESPOS)  GV_VIPOS_RESPOS                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HudImgAdjSet_GV_VIPOS_RESPOS(const U2 u2_a_GV_VIPOS_RESPOS)
{
    u2_s_himgadj_gv_vipos_respos = u2_a_GV_VIPOS_RESPOS;
    u2_s_himgadj_iftimout = (U2)0U;
}

/*===================================================================================================================================*/
/*  INTERFACE : void    vd_g_HudImgAdjSet_GV_VIPOS_MOVPOS(const U2 u2_a_GV_VIPOS_MOVPOS)  GV_VIPOS_MOVPOS                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HudImgAdjSet_GV_VIPOS_MOVPOS(const U2 u2_a_GV_VIPOS_MOVPOS)
{
    u2_s_himgadj_gv_vipos_movpos = u2_a_GV_VIPOS_MOVPOS;
    u2_s_himgadj_iftimout = (U2)0U;
}

/*===================================================================================================================================*/
/*  INTERFACE : void    vd_g_HudImgAdjSet_GV_VIPOS_ADJMINPOS(const U2 u2_a_GV_VIPOS_ADJMINPOS)  GV_VIPOS_ADJMINPOS                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HudImgAdjSet_GV_VIPOS_ADJMINPOS(const U2 u2_a_GV_VIPOS_ADJMINPOS)
{
    u2_s_himgadj_gv_vipos_minpos = u2_a_GV_VIPOS_ADJMINPOS;
    u2_s_himgadj_iftimout = (U2)0U;
}

/*===================================================================================================================================*/
/*  INTERFACE : void    vd_g_HudImgAdjSet_GV_VIPOS_ADJTEPPOS(const U2 u2_a_GV_VIPOS_ADJTEPPOS)  GV_VIPOS_ADJTEPPOS                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HudImgAdjSet_GV_VIPOS_ADJTEPPOS(const U2 u2_a_GV_VIPOS_ADJTEPPOS)
{
    u2_s_himgadj_gv_vipos_teppos = u2_a_GV_VIPOS_ADJTEPPOS;
    u2_s_himgadj_iftimout = (U2)0U;
}

/*===================================================================================================================================*/
/*  INTERFACE : void    vd_g_HudImgAdjSet_GV_VIPOS_ADJMAXPOS(const U2 u2_a_GV_VIPOS_ADJMAXPOS)  GV_VIPOS_ADJMAXPOS                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HudImgAdjSet_GV_VIPOS_ADJMAXPOS(const U2 u2_a_GV_VIPOS_ADJMAXPOS)
{
    u2_s_himgadj_gv_vipos_maxpos = u2_a_GV_VIPOS_ADJMAXPOS;
    u2_s_himgadj_iftimout = (U2)0U;
}

/*===================================================================================================================================*/
/*  INTERFACE : void    vd_g_HudImgAdjSet_GV_VIPOS_RESID(const U1 u1_a_GV_VIPOS_RESID)  GV_VIPOS_RESID                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HudImgAdjSet_GV_VIPOS_RESID(const U1 u1_a_GV_VIPOS_RESID)
{
    u1_s_himgadj_gv_vipos_resid = u1_a_GV_VIPOS_RESID;
    u2_s_himgadj_iftimout = (U2)0U;
}

/*===================================================================================================================================*/
/*  INTERFACE : void    vd_g_HudImgAdjSet_GV_VIPOS_HUD_ST(const U1 u1_a_GV_VIPOS_HUD_ST)  GV_VIPOS_HUD_ST                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HudImgAdjSet_GV_VIPOS_HUD_ST(const U1 u1_a_GV_VIPOS_HUD_ST)
{
    switch (u1_a_GV_VIPOS_HUD_ST){
        case (U1)HUDIMGADJ_HUDST_STP:
         /* break; */
        case (U1)HUDIMGADJ_HUDST_MAN:
         /* break; */
        case (U1)HUDIMGADJ_HUDST_PLY:
            u1_s_himgadj_gv_vipos_hudst = u1_a_GV_VIPOS_HUD_ST;
            u2_s_himgadj_iftimout = (U2)0U;
            break;

        default:
            /* Do Nothing. previous data hold. */
            break;
    }
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  OVERWRITE_STEP Function Definitions                                                                                              */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  OVERWRITE_STEP : static void vd_s_HudImgAdjowstpInit(void)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   -                                                                                                                    */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
static void vd_s_HudImgAdjowstpInit(void)
{
    vd_g_HudImgAdjowstpOwDeAct();
}

/*===================================================================================================================================*/
/*  OVERWRITE_STEP : static void vd_s_HudImgAdjOwStpUpdt(void)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   -                                                                                                                    */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
static void vd_s_HudImgAdjOwStpUpdt(void)
{
    if(u2_s_himgadj_owstp_tocnt < (U2)U2_MAX){
        u2_s_himgadj_owstp_tocnt++;
    }

    u4_s_himgadj_owstp_ow_unlock = (U4)0U;

    if((u2_s_himgadj_owstp_ow_act == (U2)HUDIMGADJ_OW_ACTV ) && 
       (u2_s_himgadj_owstp_tocnt  >  (U2)HUDIMGADJ_OW_ACTTO)){
        vd_g_HudImgAdjowstpOwDeAct();
    }
}

/*===================================================================================================================================*/
/*  OVERWRITE_STEP : void    vd_g_HudImgAdjowstpUnlock(const U4 u4_a_KEY)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   -                                                                                                                    */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
void    vd_g_HudImgAdjowstpUnlock(const U4 u4_a_KEY)
{
    u4_s_himgadj_owstp_ow_unlock = u4_a_KEY;
}

/*===================================================================================================================================*/
/*  OVERWRITE_STEP : void    vd_g_HudImgAdjowstpOwAct(const U1 u1_a_REQ)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   -                                                                                                                    */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
void    vd_g_HudImgAdjowstpOwAct(const U1 u1_a_REQ)
{
    U2 u2_t_imgpos;

    if(u4_s_himgadj_owstp_ow_unlock == (U4)HUDIMGADJ_OW_UNLOCK){
        u2_t_imgpos = u2_s_HudImgAdjowimgpos(u1_a_REQ);
        if(u2_t_imgpos != (U2)HUDIMGADJ_OWCTL_POS_NG_VAL){
            u2_s_himgadj_owstp_ow_act = (U2)HUDIMGADJ_OW_ACTV;
            u2_s_himgadj_owstp_tocnt  = (U2)0U;
            u2_s_himgadj_owstp_ow_pos = u2_t_imgpos;
        }
    }
    u4_s_himgadj_owstp_ow_unlock = (U4)0U;
}

/*===================================================================================================================================*/
/*  OVERWRITE_STEP : void    vd_g_HudImgAdjowstpOwDeAct(void)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   -                                                                                                                    */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
void    vd_g_HudImgAdjowstpOwDeAct(void)
{
    u2_s_himgadj_owstp_ow_act    = (U2)HUDIMGADJ_OW_INACTV;
    u2_s_himgadj_owstp_tocnt     = (U2)U2_MAX;
    u4_s_himgadj_owstp_ow_unlock = (U4)0U;
    u2_s_himgadj_owstp_ow_pos    = (U2)HUDIMGADJ_OWCTL_POS_NG_VAL;
}

/*===================================================================================================================================*/
/*  OVERWRITE_STEP : U1      u1_g_HudImgAdjGetGvOwReq(void) GV_DG_VIPOS_REQ                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_HudImgAdjGetGvOwReq(void)
{
    U1  u1_t_ret;

    u1_t_ret = (U1)FALSE;
    if(u2_s_himgadj_owstp_ow_act == (U2)HUDIMGADJ_OW_ACTV){
        u1_t_ret = (U1)TRUE;
    }
    return (u1_t_ret);
}

/*===================================================================================================================================*/
/*  OVERWRITE_STEP : U1      u2_g_HudImgAdjGetGvOwPos(void) GV_DG_VIPOS_POS                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2      u2_g_HudImgAdjGetGvOwPos(void)
{
    return (u2_s_himgadj_owstp_ow_pos);
}

/*===================================================================================================================================*/
/*  OVERWRITE_STEP : Over Write Image Position                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_REQ : IO Contorol Request                                                                                   */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U2   u2_s_HudImgAdjowimgpos(const U1 u1_a_REQ)
{
    U2 u2_t_imgpos;
    U2 u2_t_imgpos_nominal;
    U2 u2_t_imgpos_swlowerlimit;
    U2 u2_t_imgpos_swupperlimit;
    U2 u2_t_calpos;
    U2 u2_t_calpos_nominal;
    U2 u2_t_calpos_swlowerlimit;
    U2 u2_t_calpos_swupperlimit;

    u2_t_imgpos_nominal = u2_s_himgadj_gv_vipos_teppos;
    u2_t_imgpos_swlowerlimit = u2_s_himgadj_gv_vipos_minpos;
    u2_t_imgpos_swupperlimit = u2_s_himgadj_gv_vipos_maxpos;

    u2_t_calpos = (U2)HUDIMGADJ_OWCTL_POS_NG_VAL;
    u2_t_imgpos = (U2)HUDIMGADJ_OWCTL_POS_NG_VAL;
    if((u2_t_imgpos_nominal      != (U2)U2_MAX)               &&
       (u2_t_imgpos_swlowerlimit != (U2)U2_MAX)               &&
       (u2_t_imgpos_swupperlimit != (U2)U2_MAX)               &&
       (u2_t_imgpos_nominal      >= u2_t_imgpos_swlowerlimit) &&
       (u2_t_imgpos_swupperlimit >= u2_t_imgpos_nominal)){

        u2_t_calpos_nominal      = u2_t_imgpos_nominal >> (U2)HUDIMGADJ_OWCTL_POS_CALC_PLSLSB_SFT;
        u2_t_calpos_swlowerlimit = u2_t_imgpos_swlowerlimit >> (U2)HUDIMGADJ_OWCTL_POS_CALC_PLSLSB_SFT;
        u2_t_calpos_swupperlimit = u2_t_imgpos_swupperlimit >> (U2)HUDIMGADJ_OWCTL_POS_CALC_PLSLSB_SFT;

        switch (u1_a_REQ) {
            case (U1)HUDIMGADJ_OWCTL_POS_CNT:
                u2_t_imgpos = u2_t_imgpos_nominal;
                break;
            case (U1)HUDIMGADJ_OWCTL_POS_L1:
                /* nominal - ROUNDUP((nominal - Min)/3) */
                u2_t_calpos = u2_t_calpos_nominal -
                              (((u2_t_calpos_nominal - u2_t_calpos_swlowerlimit) + (U2)HUDIMGADJ_OWCTL_POS_CALC_ROUND) / (U2)HUDIMGADJ_OWCTL_POS_CALC_DIV);
                u2_t_imgpos = u2_t_calpos << (U2)HUDIMGADJ_OWCTL_POS_CALC_PLSLSB_SFT;
                break;
            case (U1)HUDIMGADJ_OWCTL_POS_L2:
                /* nominal - ROUNDUP((nominal - Min)*2/3) */
                u2_t_calpos = u2_t_calpos_nominal -
                              (U2)(((((U4)u2_t_calpos_nominal - (U4)u2_t_calpos_swlowerlimit) * (U4)HUDIMGADJ_OWCTL_POS_CALC_CRCT) + (U4)HUDIMGADJ_OWCTL_POS_CALC_ROUND) / (U4)HUDIMGADJ_OWCTL_POS_CALC_DIV);     /* PRQA S 3383,3384 # over detection */
                u2_t_imgpos = u2_t_calpos << (U2)HUDIMGADJ_OWCTL_POS_CALC_PLSLSB_SFT;
                break;
            case (U1)HUDIMGADJ_OWCTL_POS_L3:
                u2_t_imgpos = u2_t_imgpos_swlowerlimit;
                break;
            case (U1)HUDIMGADJ_OWCTL_POS_U1:
                /* nominal + ROUNDUP((Max - nominal)/3) */
                u2_t_calpos = u2_t_calpos_nominal +
                              (((u2_t_calpos_swupperlimit - u2_t_calpos_nominal) + (U2)HUDIMGADJ_OWCTL_POS_CALC_ROUND) / (U2)HUDIMGADJ_OWCTL_POS_CALC_DIV);
                u2_t_imgpos = u2_t_calpos << (U2)HUDIMGADJ_OWCTL_POS_CALC_PLSLSB_SFT;
                break;
            case (U1)HUDIMGADJ_OWCTL_POS_U2:
                /* nominal + ROUNDUP((Max - nominal)*2/3) */
                u2_t_calpos = u2_t_calpos_nominal +
                              (U2)(((((U4)u2_t_calpos_swupperlimit - (U4)u2_t_calpos_nominal) * (U4)HUDIMGADJ_OWCTL_POS_CALC_CRCT) + (U4)HUDIMGADJ_OWCTL_POS_CALC_ROUND) / (U4)HUDIMGADJ_OWCTL_POS_CALC_DIV);     /* PRQA S 3383,3384 # over detection */
                u2_t_imgpos = u2_t_calpos << (U2)HUDIMGADJ_OWCTL_POS_CALC_PLSLSB_SFT;
                break;
            case (U1)HUDIMGADJ_OWCTL_POS_U3:
                u2_t_imgpos = u2_t_imgpos_swupperlimit;
                break;
            default:
                /* u2_t_imgpos = (U2)HUDIMGADJ_OWCTL_POS_NG_VAL; */
                break;
        }
    }

    return(u2_t_imgpos);
}

/*===================================================================================================================================*/
/*  OVERWRITE_STEP : Read Image Position                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1 u1_g_HudImgAdjReadDataImgPos(U1 * u1_ap_pos)
{

    U2 u2_t_nowimgpos;
    U2 u2_t_nominalimgpos;
    U2 u2_t_lowerlimitimgpos;
    U2 u2_t_upperlimitimgpos;
    U2 u2_t_low1_judgeimgpos;
    U2 u2_t_up1_judgeimgpos;
    U2 u2_t_up2_judgeimgpos;
    U1 u1_t_result;

    u1_t_result = (U1)FALSE;

    u2_t_nowimgpos = u2_s_himgadj_gv_vipos_movpos;
    u2_t_nominalimgpos = u2_s_himgadj_gv_vipos_teppos;
    u2_t_lowerlimitimgpos = u2_s_himgadj_gv_vipos_minpos;
    u2_t_upperlimitimgpos = u2_s_himgadj_gv_vipos_maxpos;

    (* u1_ap_pos) = (U1)HUDIMGADJ_OWCTL_POS_CNT;
    if((u2_t_nowimgpos        != (U2)U2_MAX)            &&
       (u2_t_nominalimgpos    != (U2)U2_MAX)            &&
       (u2_t_lowerlimitimgpos != (U2)U2_MAX)            &&
       (u2_t_upperlimitimgpos != (U2)U2_MAX)            &&
       (u2_t_nominalimgpos    >= u2_t_lowerlimitimgpos) &&
       (u2_t_upperlimitimgpos >= u2_t_nominalimgpos)){

        /* U1(0xFD) */
        u2_t_up1_judgeimgpos  = u2_t_nominalimgpos + (U2)HUDIMGADJ_OWCTL_RFPOS_CALC_CRCT;

        /* L1(0x01) */
        /* ROUNDUP((U1 + Min)/2) */
        u2_t_low1_judgeimgpos = (U2)(((U4)u2_t_up1_judgeimgpos + (U4)u2_t_lowerlimitimgpos + (U4)HUDIMGADJ_OWCTL_RDPOS_CALC_ROUND) / (U4)HUDIMGADJ_OWCTL_RDPOS_CALC_DIV); /* PRQA S 3383,3384 # over detection */

        /* U2(0xFE) */
        /* ROUNDUP((nominal + Max)/2) */
        u2_t_up2_judgeimgpos  = (U2)(((U4)u2_t_nominalimgpos + (U4)u2_t_upperlimitimgpos + (U4)HUDIMGADJ_OWCTL_RDPOS_CALC_ROUND) / (U4)HUDIMGADJ_OWCTL_RDPOS_CALC_DIV);   /* PRQA S 3383,3384 # over detection */

        /* Center */
        if( u2_t_nowimgpos == u2_t_nominalimgpos ){
           (* u1_ap_pos) = (U1)HUDIMGADJ_OWCTL_POS_CNT;
        }
        /* Lower Limit */
        else if( u2_t_nowimgpos <= u2_t_lowerlimitimgpos ){
           (* u1_ap_pos) = (U1)HUDIMGADJ_OWCTL_POS_L3;
        }
        /* Upper Limi */
        else if( u2_t_nowimgpos >= u2_t_upperlimitimgpos ){
           (* u1_ap_pos) = (U1)HUDIMGADJ_OWCTL_POS_U3;
        }
        /* U2 */
        else if( u2_t_nowimgpos >= u2_t_up2_judgeimgpos ){
           (* u1_ap_pos) = (U1)HUDIMGADJ_OWCTL_POS_U2;
        }
        /* U1 */
        else if( u2_t_nowimgpos >= u2_t_up1_judgeimgpos ){
           (* u1_ap_pos) = (U1)HUDIMGADJ_OWCTL_POS_U1;
        }
        /* L1 */
        else if( u2_t_nowimgpos >= u2_t_low1_judgeimgpos ){
           (* u1_ap_pos) = (U1)HUDIMGADJ_OWCTL_POS_L1;
        }
        /* L2 */
        else{
           (* u1_ap_pos) = (U1)HUDIMGADJ_OWCTL_POS_L2;
        }

        u1_t_result = (U1)TRUE;

    }

    return(u1_t_result);
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  DIAG_CUSTOMIZE(DID 2003) Function Definitions                                                                                    */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  DIAG_CUSTOMIZE : static void vd_s_HudImgAdjCustomDrvPsInit(void)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   -                                                                                                                    */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
static void vd_s_HudImgAdjCustomDrvPsInit(void)
{
    vd_s_HudImgAdjUpdtCustomDrvPs();    /* u1_s_himgadj_cstmz_drvps */
}

/*===================================================================================================================================*/
/*  DIAG_CUSTOMIZE : Update Customize DriverPosition read value                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_HudImgAdjUpdtCustomDrvPs(void)
{
    U4  u4_t_data;
    U1  u1_t_sts;

    u4_t_data = (U4)HUDIMGADJ_CSTMZ_DRVPS_INITVAL;
    u1_t_sts = u1_g_Nvmc_ReadU4withSts((U2)NVMCID_U4_DS_2E_2003, (&u4_t_data));
    if((u1_t_sts == (U1)NVMC_STATUS_COMP   ) ||
       (u1_t_sts == (U1)NVMC_STATUS_READING)){
        u1_s_himgadj_cstmz_drvps = (U1)u4_t_data;
    }
    else {
        u1_s_himgadj_cstmz_drvps = (U1)HUDIMGADJ_CSTMZ_DRVPS_INITVAL;
    }
}

/*===================================================================================================================================*/
/*  DIAG_CUSTOMIZE : Notify Customize DriverPosition                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_CUSTOMTYPE : SEATMEMORY CUSTOMTYPE                                                                          */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1   u1_s_HudImgAdjGetCustomDrvPs(const U1 u1_a_CUSTOMTYPE)
{
    U1 u1_t_result;

    u1_t_result = (U1)FALSE;

    if ((u1_s_himgadj_cstmz_drvps & u1_a_CUSTOMTYPE) != (U1)0U ){
        u1_t_result = (U1)TRUE;
    }

    return(u1_t_result);
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  USER_SWITCH_OPERATION Function Definitions                                                                                       */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  USER_SWITCH_OPERATION : static void vd_s_HudImgAdjSwInit(void)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments    -                                                                                                                   */
/*  Return       -                                                                                                                   */
/*===================================================================================================================================*/
static void vd_s_HudImgAdjSwInit(void)
{
    u1_s_himgadj_is_upswon = (U1)FALSE;
    u1_s_himgadj_is_dnswon = (U1)FALSE;
}

/*===================================================================================================================================*/
/*  USER_SWITCH_OPERATION : processing HUD Image Adjudt - User Switch Operation                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments    -                                                                                                                   */
/*  Return       -                                                                                                                   */
/*===================================================================================================================================*/
static void vd_s_HudImgAdjSwTask(void)
{
    static const U1 u1_sp_HUDIMGADJ_SWACT[HUDIMGADJ_SWSGNL_MAX][HUDIMGADJ_SWACT_MAX] = {
        /* HUDIMGADJ_SWACT_DN , HUDIMGADJ_SWACT_UP */   /* [STRSW_UP] [STRSW_DN] [LVPS_UP] [LVPS_DN] */
        { (U1)FALSE,            (U1)FALSE },            /*          0          0         0         0 */
        { (U1)TRUE,             (U1)FALSE },            /*          0          0         0         1 */
        { (U1)FALSE,            (U1)TRUE  },            /*          0          0         1         0 */
        { (U1)FALSE,            (U1)FALSE },            /*          0          0         1         1 */
        { (U1)TRUE,             (U1)FALSE },            /*          0          1         0         0 */
        { (U1)TRUE,             (U1)FALSE },            /*          0          1         0         1 */
        { (U1)TRUE,             (U1)FALSE },            /*          0          1         1         0 */
        { (U1)TRUE,             (U1)FALSE },            /*          0          1         1         1 */
        { (U1)FALSE,            (U1)TRUE  },            /*          1          0         0         0 */
        { (U1)FALSE,            (U1)TRUE  },            /*          1          0         0         1 */
        { (U1)FALSE,            (U1)TRUE  },            /*          1          0         1         0 */
        { (U1)FALSE,            (U1)TRUE  },            /*          1          0         1         1 */
        { (U1)FALSE,            (U1)FALSE },            /*          1          1         0         0 */
        { (U1)TRUE,             (U1)FALSE },            /*          1          1         0         1 */
        { (U1)FALSE,            (U1)TRUE  },            /*          1          1         1         0 */
        { (U1)FALSE,            (U1)FALSE }             /*          1          1         1         1 */
    };

    U1              u1_t_sw_evt;
    U1              u1_t_strsw_up;
    U1              u1_t_strsw_dn;
    U1              u1_t_lvps_up;
    U1              u1_t_lvps_dn;

    u1_t_strsw_up = u1_s_himgadj_upstrsw;
    u1_t_strsw_dn = u1_s_himgadj_dwstrsw;
    u1_t_lvps_up = u1_s_himgadj_l_up_possw;
    u1_t_lvps_dn = u1_s_himgadj_l_dn_possw;

    u1_t_sw_evt = (U1)0U;
    if(u1_t_strsw_up == (U1)TRUE){
        u1_t_sw_evt = (U1)HUDIMGADJ_SWSGNL_STRSW_UP;
    }
    if(u1_t_strsw_dn == (U1)TRUE){
        u1_t_sw_evt |= (U1)HUDIMGADJ_SWSGNL_STRSW_DN;
    }
    if(u1_t_lvps_up == (U1)TRUE){
        u1_t_sw_evt |= (U1)HUDIMGADJ_SWSGNL_LVPS_UP;
    }
    if(u1_t_lvps_dn == (U1)TRUE){
        u1_t_sw_evt |= (U1)HUDIMGADJ_SWSGNL_LVPS_DN;
    }

    u1_s_himgadj_is_upswon = u1_sp_HUDIMGADJ_SWACT[u1_t_sw_evt][HUDIMGADJ_SWACT_UP];
    u1_s_himgadj_is_dnswon = u1_sp_HUDIMGADJ_SWACT[u1_t_sw_evt][HUDIMGADJ_SWACT_DN];
}

/*===================================================================================================================================*/
/*  USER_SWITCH_OPERATION : U1      u1_g_HudImgAdjIsUpSwOn(void) GV_VIPOS_UPSW                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_HudImgAdjIsUpSwOn(void)
{
    return (u1_s_himgadj_is_upswon);
}

/*===================================================================================================================================*/
/*  USER_SWITCH_OPERATION : U1      u1_g_HudImgAdjIsDnSwOn(void) GV_VIPOS_DNSW                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_HudImgAdjIsDnSwOn(void)
{
    return (u1_s_himgadj_is_dnswon);
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  DRIVING_POSITION Function Definitions                                                                                            */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  DRIVING_POSITION : static void vd_s_HudImgAdjDrvPsInit(void)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_HudImgAdjDrvPsInit(void)
{
    U1  u1_t_id;
    U1  u1_t_hudsts;

    u4_s_himgadj_drvpos_sgnl = (U4)0U;

    for(u1_t_id = (U1)0U; u1_t_id < (U1)HUDIMGADJ_NUM_DRVPS_DT; u1_t_id++){
        u2_sp_himgadj_imgpos[u1_t_id]   = u2_s_HudImgAdjDrvPsReadData(u1_t_id);
    }

    u2_s_himgadj_stshldtimr = (U2)U2_MAX;
    u2_s_himgadj_movreq_pos = (U2)HUDIMGADJ_IMGPOSINVLD;
    u2_s_himgadj_movsts_tim = (U2)0U;
    u1_s_himgadj_movsts     = (U1)HUDIMGADJ_MOVSTS_STP;
    u1_s_himgadj_movreq_id  = (U1)HUDIMGADJ_IDINVLD;

    u1_s_himgadj_drvpsbak   = (U1)HUDIMGADJ_CAN_DRVPSDT_NON;
    u1_s_himgadj_hudreqbak  = (U1)HUDIMGADJ_CAN_DRVPSREQ_NON;
    u1_s_himgadj_hudctrlsts = (U1)HUDIMGADJ_HUDCTLSTS_STP;

    u1_t_hudsts = (U1)HUDIMGADJ_HUDST_UNDET;
#ifdef ComConf_ComSignal_HUD_ST
    (void)Com_SendSignal(ComConf_ComSignal_HUD_ST, &u1_t_hudsts);  /* No event sending occur. Depend on TyCAN config. */
#endif
}
/*===================================================================================================================================*/
/*  DRIVING_POSITION : static void vd_s_HudImgAdjDrvPsInvalidInit(void)                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_HudImgAdjDrvPsInvalidInit(void)
{
    U1  u1_t_hudsts;
    U1  u1_t_hudsts_prev;

    u4_s_himgadj_drvpos_sgnl = (U4)0U;

    u2_s_himgadj_stshldtimr = (U2)U2_MAX;
    u2_s_himgadj_movreq_pos = (U2)HUDIMGADJ_IMGPOSINVLD;
    u2_s_himgadj_movsts_tim = (U2)0U;
    u1_s_himgadj_movsts     = (U1)HUDIMGADJ_MOVSTS_STP;
    u1_s_himgadj_movreq_id  = (U1)HUDIMGADJ_IDINVLD;

    u1_s_himgadj_drvpsbak   = (U1)HUDIMGADJ_CAN_DRVPSDT_NON;
    u1_s_himgadj_hudreqbak  = (U1)HUDIMGADJ_CAN_DRVPSREQ_NON;
    u1_s_himgadj_hudctrlsts = (U1)HUDIMGADJ_HUDCTLSTS_STP;

    u1_t_hudsts      = (U1)HUDIMGADJ_HUDST_UNDET;
    u1_t_hudsts_prev = (U1)HUDIMGADJ_HUDST_UNDET;
#ifdef ComConf_ComSignal_HUD_ST
    (void)Com_ReceiveSignal(ComConf_ComSignal_HUD_ST, &u1_t_hudsts_prev);
    (void)Com_SendSignal(ComConf_ComSignal_HUD_ST, &u1_t_hudsts);
#endif
    if(u1_t_hudsts_prev != u1_t_hudsts){
#ifdef MSG_HUD1S01_TXCH0
        (void)Com_TriggerIPDUSend(MSG_HUD1S01_TXCH0);        /* Event send Trigger */
#endif
    }
}
/*===================================================================================================================================*/
/*  DRIVING_POSITION : Drive Position Read Data                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U2 u2_s_HudImgAdjDrvPsReadData(const U1 u1_a_ID)
{
    U2            u2_t_read_data;
    U2            u2_t_data;
    U1            u1_t_nvmc_rsp;

    u2_t_read_data = (U2)HUDIMGADJ_RDDTUNDEF;
    if(((U1)HUDIMGADJ_DRVPSDT_01 <= u1_a_ID                   ) &&
       (u1_a_ID                  <  (U1)HUDIMGADJ_NUM_DRVPS_DT)){
        u1_t_nvmc_rsp = u1_g_Nvmc_ReadU2withSts(u2_sp_HUDIMGADJ_TBL_NVMCID_DRVPSDT[u1_a_ID], &u2_t_read_data);
        if((u1_t_nvmc_rsp == (U1)NVMC_STATUS_COMP) ||
           (u1_t_nvmc_rsp == (U1)NVMC_STATUS_READING)){
            u2_t_data = u2_t_read_data;
        }
        else{
            u2_t_data = (U2)HUDIMGADJ_RDDTERR;
        }
    }
    else{
        u2_t_data = (U2)HUDIMGADJ_RDDTERR;
    }

    return(u2_t_data);
}

/*===================================================================================================================================*/
/*  DRIVING_POSITION : Driver Position Update                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments    -                                                                                                                   */
/*  Return       -                                                                                                                   */
/*===================================================================================================================================*/
static void vd_s_HudImgAdjDrvPsUpdt(void)
{
    static const U1 u1_sp_HUDIMGADJ_TBL_DRVPSID[HUDIMGADJ_NUM_DRVPS_DT] =
    {
        (U1)HUDIMGADJ_DRVPSDT_NON,             /* Position Request None */
        (U1)HUDIMGADJ_DRVPSDT_01,              /* User1 Memory No1      */
        (U1)HUDIMGADJ_DRVPSDT_02,              /* User1 Memory No2      */
        (U1)HUDIMGADJ_DRVPSDT_03,              /* User1 Memory No3      */
        (U1)HUDIMGADJ_DRVPSDT_04,              /* User1 Last Position   */
        (U1)HUDIMGADJ_DRVPSDT_05,              /* User2 Memory No1      */
        (U1)HUDIMGADJ_DRVPSDT_06,              /* User2 Memory No2      */
        (U1)HUDIMGADJ_DRVPSDT_07,              /* User2 Memory No3      */
        (U1)HUDIMGADJ_DRVPSDT_08,              /* User2 Last Position   */
        (U1)HUDIMGADJ_DRVPSDT_09,              /* User3 Memory No1      */
        (U1)HUDIMGADJ_DRVPSDT_10,              /* User3 Memory No2      */
        (U1)HUDIMGADJ_DRVPSDT_11,              /* User3 Memory No3      */
        (U1)HUDIMGADJ_DRVPSDT_12,              /* User3 Last Position   */
        (U1)HUDIMGADJ_DRVPSDT_13,              /* Guest Memory No1      */
        (U1)HUDIMGADJ_DRVPSDT_14,              /* Guest Memory No2      */
        (U1)HUDIMGADJ_DRVPSDT_15               /* Guest Memory No3      */
    };

    static const U1 u1_sp_HUDIMGADJ_TBL_DRVPS_REQ[HUDIMGADJ_NUM_RVPSREQ] =
    {
        (U1)HUDIMGADJ_DRVPSREQ_NON,            /* Request None          */
        (U1)HUDIMGADJ_DRVPSREQ_MEM,            /* Memory Request        */
        (U1)HUDIMGADJ_DRVPSREQ_MOV,            /* Move Request          */
        (U1)HUDIMGADJ_DRVPSREQ_NON             /* Not Used              */
    };
    U1  u1_t_msg;
    U1  u1_t_id;
    U1  u1_t_req;
    U1  u1_t_drvps;
    U1  u1_t_hudreq;

    u1_t_msg = Com_GetIPDUStatus((PduIdType)MSG_BDB1F02_RXCH0);
    u1_t_msg &= ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_drvps = (U1)HUDIMGADJ_CAN_DRVPSDT_NON;
    u1_t_hudreq = (U1)HUDIMGADJ_CAN_DRVPSREQ_NON;
    if(u1_t_msg == (U1)0U){
        u1_t_drvps = (U1)0U;
        (void)Com_ReceiveSignal(ComConf_ComSignal_DRVPS_DT, &u1_t_drvps);

        u1_t_hudreq = (U1)0U;
        (void)Com_ReceiveSignal(ComConf_ComSignal_HUD_R, &u1_t_hudreq);

        if(u1_t_drvps < (U1)HUDIMGADJ_NUM_DRVPS_DT){
            u1_t_id = u1_sp_HUDIMGADJ_TBL_DRVPSID[u1_t_drvps];
        }
        else{
            u1_t_id = (U1)HUDIMGADJ_DRVPSDT_NON;
        }

        if(u1_t_hudreq < (U1)HUDIMGADJ_NUM_RVPSREQ){
            u1_t_req = u1_sp_HUDIMGADJ_TBL_DRVPS_REQ[u1_t_hudreq];
        }
        else{
            u1_t_req = (U1)HUDIMGADJ_DRVPSREQ_NON;
        }
    }
    else{
        u1_t_id  = (U1)HUDIMGADJ_DRVPSDT_NON;
        u1_t_req = (U1)HUDIMGADJ_DRVPSREQ_NON;
    }

    u4_s_himgadj_drvpos_sgnl &= (U4)HUDIMGADJ_SGNL_MASK;
    u4_s_himgadj_drvpos_sgnl <<= 1U;

    if(u1_t_req == (U1)HUDIMGADJ_DRVPSREQ_MEM){
        u4_s_himgadj_drvpos_sgnl |= (U4)HUDIMGADJ_SGNL_MEMREQ;
    }
    if(u1_t_req == (U1)HUDIMGADJ_DRVPSREQ_MOV){
        u4_s_himgadj_drvpos_sgnl |= (U4)HUDIMGADJ_SGNL_MOVREQ;
    }
    if((u1_s_himgadj_drvpsbak != u1_t_drvps) || (u1_s_himgadj_hudreqbak != u1_t_hudreq)){
        u4_s_himgadj_drvpos_sgnl |= (U4)HUDIMGADJ_SGNL_RDVPSCHGREQ;
    }

    vd_s_HudImgAdjDrvPsMemUpdt(u4_s_himgadj_drvpos_sgnl , u1_t_id);

    vd_s_HudImgAdjDrvPsMovUpdt(u4_s_himgadj_drvpos_sgnl , u1_t_id);

    vd_s_HudImgAdjDrvPsHudStsUpdt(u4_s_himgadj_drvpos_sgnl);

    u1_s_himgadj_drvpsbak = u1_t_drvps;
    u1_s_himgadj_hudreqbak = u1_t_hudreq;
}

/*===================================================================================================================================*/
/*  DRIVING_POSITION : Motor Position Memory Update                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments    :  -                                                                                                                */
/*  Return       :  -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_HudImgAdjDrvPsMemUpdt(const U4 u4_a_SGNL, const U1 u1_a_ID)
{
    U2  u2_t_imgpos;
    U2  u2_t_max;                                                                /* Motor Max                                       */
    U2  u2_t_min;                                                                /* Motor Min                                       */

    U1  u1_t_ig;
    U1  u1_t_hudsts;
    U1  u1_t_isvld;

    u1_t_isvld = (U1)FALSE;
    u1_t_ig = u1_g_VehopemdIgnOn();
    u1_t_hudsts = u1_s_HudImgAdjGetHudSts();
    u2_t_imgpos = u2_s_himgadj_gv_vipos_respos;
    u2_t_max = u2_s_himgadj_gv_vipos_maxpos;
    u2_t_min = u2_s_himgadj_gv_vipos_minpos;
    if((u1_a_ID < (U1)HUDIMGADJ_NUM_DRVPS_DT)                                               &&
       (u1_t_ig == (U1)TRUE)                                                                &&
       (u1_t_hudsts == (U1)TRUE)                                                            &&
       ((u4_a_SGNL & (U4)HUDIMGADJ_SGNL_MEMREQ) == (U4)HUDIMGADJ_SGNL_MEMREQ)               &&
       ((u4_a_SGNL & (U4)HUDIMGADJ_SGNL_RDVPSCHGMASK) == (U4)HUDIMGADJ_SGNL_RDVPSCHGONEDGE) &&
       (u2_t_imgpos != (U2)HUDIMGADJ_IMGPOSINVLD)                                           &&
       ((u2_t_imgpos >= u2_t_min) && (u2_t_imgpos <= u2_t_max))){
        u1_t_isvld = (U1)TRUE;
    }

    if(u1_t_isvld == (U1)TRUE){
        u2_sp_himgadj_imgpos[u1_a_ID] = u2_t_imgpos;
        vd_g_Nvmc_WriteU2(u2_sp_HUDIMGADJ_TBL_NVMCID_DRVPSDT[u1_a_ID], u2_t_imgpos);
    }
}

/*===================================================================================================================================*/
/*  DRIVING_POSITION : Motor Position Move Update                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments    :  -                                                                                                                */
/*  Return       :  -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_HudImgAdjDrvPsMovUpdt(const U4 u4_a_SGNL, const U1 u1_a_ID)
{
    U2  u2_t_imgpos;

    U1  u1_t_id;
    U1  u1_t_custom;
    U1  u1_t_isvld;
    U1  u1_t_evt;

    u1_t_id = u1_s_himgadj_movreq_id;
    u2_t_imgpos = u2_s_himgadj_movreq_pos;

    u1_t_isvld = (U1)FALSE;
    u1_t_custom = u1_s_HudImgAdjGetCustomDrvPs((U1)HUDIMGADJ_CSTMZ_DRVPS_SWACT);
    if((u1_a_ID < (U1)HUDIMGADJ_NUM_DRVPS_DT)                                               &&
       (u1_t_custom == (U1)TRUE)                                                            &&
       ((u4_a_SGNL & (U4)HUDIMGADJ_SGNL_MOVREQ) == (U4)HUDIMGADJ_SGNL_MOVREQ)               &&
       ((u4_a_SGNL & (U4)HUDIMGADJ_SGNL_RDVPSCHGMASK) == (U4)HUDIMGADJ_SGNL_RDVPSCHGONEDGE) &&
       (u2_sp_himgadj_imgpos[u1_a_ID] != (U2)HUDIMGADJ_IMGPOSINVLD)){
        u1_t_id = u1_a_ID;
        u2_t_imgpos = u2_sp_himgadj_imgpos[u1_a_ID];
        u1_t_isvld = (U1)TRUE;
    }

    if(u2_s_himgadj_movsts_tim < (U2)U2_MAX){
        u2_s_himgadj_movsts_tim += (U2)1U;
    }

    u1_t_evt = (U1)HUDIMGADJ_MOVEVT_NONE;
    if(u1_t_isvld == (U1)TRUE){
        u1_t_evt = (U1)HUDIMGADJ_MOVEVT_MOVEREQ;
    }
    if(u1_t_id == u1_s_himgadj_gv_vipos_resid){
        u1_t_evt |= (U1)HUDIMGADJ_MOVEVT_IDEQL;
    }
    if(u2_s_himgadj_movsts_tim >= (U2)HUDIMGADJ_MOVSTS_TIMOUT){
        u1_t_evt |= (U1)HUDIMGADJ_MOVEVT_TIMOUT;
    }

    vd_s_HudImgAdjDrvPsMovActn(u1_t_evt, u1_t_id, u2_t_imgpos);
}

/*===================================================================================================================================*/
/*  DRIVING_POSITION : Motor Position Move Action                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments    :  -                                                                                                                */
/*  Return       :  -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_HudImgAdjDrvPsMovActn(const U1 u1_a_EVT, const U1 u1_a_ID, const U2 u2_a_IMGPOS)
{
    static const U1 u1_sp_HUDIMGADJ_MOVACT[HUDIMGADJ_MOVEVT_MAX][HUDIMGADJ_MOVSTS_MAX] = {
        {(U1)HUDIMGADJ_MOVACT_STP_INI_CLR, (U1)HUDIMGADJ_MOVACT_MOV_HLD_NON},
        {(U1)HUDIMGADJ_MOVACT_STP_INI_CLR, (U1)HUDIMGADJ_MOVACT_STP_INI_CLR},
        {(U1)HUDIMGADJ_MOVACT_STP_INI_CLR, (U1)HUDIMGADJ_MOVACT_STP_INI_CLR},
        {(U1)HUDIMGADJ_MOVACT_STP_INI_CLR, (U1)HUDIMGADJ_MOVACT_STP_INI_CLR},
        {(U1)HUDIMGADJ_MOVACT_MOV_SET_CLR, (U1)HUDIMGADJ_MOVACT_MOV_SET_CLR},
        {(U1)HUDIMGADJ_MOVACT_MOV_SET_CLR, (U1)HUDIMGADJ_MOVACT_MOV_SET_CLR},
        {(U1)HUDIMGADJ_MOVACT_MOV_SET_CLR, (U1)HUDIMGADJ_MOVACT_MOV_SET_CLR},
        {(U1)HUDIMGADJ_MOVACT_MOV_SET_CLR, (U1)HUDIMGADJ_MOVACT_MOV_SET_CLR}
    };

    U1  u1_t_act;

    u1_t_act = (U1)HUDIMGADJ_MOVACT_STP_INI_CLR;
    if((u1_a_EVT < (U1)HUDIMGADJ_MOVEVT_MAX) &&
       (u1_s_himgadj_movsts < (U1)HUDIMGADJ_MOVSTS_MAX)){
        u1_t_act = u1_sp_HUDIMGADJ_MOVACT[u1_a_EVT][u1_s_himgadj_movsts];
    }

    switch (u1_t_act){
        case (U1)HUDIMGADJ_MOVACT_STP_INI_CLR:
            u1_s_himgadj_movsts = (U1)HUDIMGADJ_MOVSTS_STP;
            u1_s_himgadj_movreq_id  = (U1)HUDIMGADJ_IDINVLD;
            u2_s_himgadj_movreq_pos = (U2)HUDIMGADJ_IMGPOSINVLD;
            u2_s_himgadj_movsts_tim = (U2)0U;
            break;

        case (U1)HUDIMGADJ_MOVACT_MOV_SET_CLR:
            u1_s_himgadj_movsts = (U1)HUDIMGADJ_MOVSTS_MOV;
            u1_s_himgadj_movreq_id  = u1_a_ID;
            u2_s_himgadj_movreq_pos = u2_a_IMGPOS;
            u2_s_himgadj_movsts_tim = (U2)0U;
            break;

        case (U1)HUDIMGADJ_MOVACT_MOV_HLD_NON:
            u1_s_himgadj_movsts = (U1)HUDIMGADJ_MOVSTS_MOV;
            break;

        default:
            u1_s_himgadj_movsts = (U1)HUDIMGADJ_MOVSTS_STP;
            u1_s_himgadj_movreq_id  = (U1)HUDIMGADJ_IDINVLD;
            u2_s_himgadj_movreq_pos = (U2)HUDIMGADJ_IMGPOSINVLD;
            u2_s_himgadj_movsts_tim = (U2)0U;
            break;
    }
}

/*===================================================================================================================================*/
/*  DRIVING_POSITION : Motor Position HudSts Update                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments    :  -                                                                                                                */
/*  Return       :  -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_HudImgAdjDrvPsHudStsUpdt(const U4 u4_a_SGNL)
{
    static const U1 u1_sp_HUDIMGADJ_TBL_HUDST_OFFST[HUDIMGADJ_HUDST_OFFST_NUM] = 
    {
        (U1)HUDIMGADJ_HUDST_OFFST_NON,      /* Invalid     */
        (U1)HUDIMGADJ_HUDST_OFFST_NON,      /* Stop        */
        (U1)HUDIMGADJ_HUDST_OFFST_MAN,      /* Manual      */
        (U1)HUDIMGADJ_HUDST_OFFST_PLY       /* Play        */
    };

    U1  u1_t_evt;
    U1  u1_t_custom;
    U1  u1_t_imgpos_hudst;
    U1  u1_t_offst;

    u1_t_evt = (U1)HUDIMGADJ_HUDSTEVT_NONE;
    if(((u4_a_SGNL & (U4)HUDIMGADJ_SGNL_MOVREQ) == (U4)HUDIMGADJ_SGNL_MOVREQ)               &&
       ((u4_a_SGNL & (U4)HUDIMGADJ_SGNL_RDVPSCHGMASK) == (U4)HUDIMGADJ_SGNL_RDVPSCHGONEDGE)){
        u1_t_evt = (U1)HUDIMGADJ_HUDSTEVT_PLYREQ;
    }

    u1_t_custom = u1_s_HudImgAdjGetCustomDrvPs((U1)HUDIMGADJ_CSTMZ_DRVPS_SWACT);
    if(u1_t_custom == (U1)TRUE){
        u1_t_evt |= (U1)HUDIMGADJ_HUDSTEVT_CUSTOM;
    }

    u1_t_imgpos_hudst = u1_s_himgadj_gv_vipos_hudst;
    u1_t_offst = (U1)HUDIMGADJ_HUDST_OFFST_NON;
    if(u1_t_imgpos_hudst < (U1)HUDIMGADJ_HUDST_OFFST_NUM){
        u1_t_offst = u1_sp_HUDIMGADJ_TBL_HUDST_OFFST[u1_t_imgpos_hudst];
    }

    u1_t_evt += u1_t_offst;                       /* PRQA S 3383 # over detection */
    vd_s_HudImgAdjDrvPsHudStsActn(u1_t_evt);
}

/*===================================================================================================================================*/
/*  DRIVING_POSITION : Motor Position HudSts Action                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments    :  -                                                                                                                */
/*  Return       :  -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_HudImgAdjDrvPsHudStsActn(const U1 u1_a_EVT)
{
    static const U1 u1_sp_HUDIMGADJ_TBL_HUDSTS[HUDIMGADJ_HUDSTEVT_MAX][HUDIMGADJ_HUDCTLSTS_MAX] = {
        {  (U1)HUDIMGADJ_HUDSTACT_STP_STP_NON,  (U1)HUDIMGADJ_HUDSTACT_STP_STP_NON, (U1)HUDIMGADJ_HUDSTACT_STP_STP_NON},
        {  (U1)HUDIMGADJ_HUDSTACT_PLY_PLY_CLR,  (U1)HUDIMGADJ_HUDSTACT_PLY_PLY_CLR, (U1)HUDIMGADJ_HUDSTACT_PLY_PLY_NON},
        {  (U1)HUDIMGADJ_HUDSTACT_STP_STP_NON,  (U1)HUDIMGADJ_HUDSTACT_STP_STP_NON, (U1)HUDIMGADJ_HUDSTACT_STP_STP_NON},
        {  (U1)HUDIMGADJ_HUDSTACT_STP_STP_NON,  (U1)HUDIMGADJ_HUDSTACT_STP_STP_NON, (U1)HUDIMGADJ_HUDSTACT_STP_STP_NON},

        {  (U1)HUDIMGADJ_HUDSTACT_STP_STP_NON,  (U1)HUDIMGADJ_HUDSTACT_STP_STP_NON, (U1)HUDIMGADJ_HUDSTACT_STP_STP_NON},
        {  (U1)HUDIMGADJ_HUDSTACT_PLY_PLY_CLR,  (U1)HUDIMGADJ_HUDSTACT_PLY_PLY_CLR, (U1)HUDIMGADJ_HUDSTACT_PLY_PLY_NON},
        {  (U1)HUDIMGADJ_HUDSTACT_MAN_MAN_NON,  (U1)HUDIMGADJ_HUDSTACT_MAN_MAN_NON, (U1)HUDIMGADJ_HUDSTACT_MAN_MAN_NON},
        {  (U1)HUDIMGADJ_HUDSTACT_MAN_MAN_NON,  (U1)HUDIMGADJ_HUDSTACT_MAN_MAN_NON, (U1)HUDIMGADJ_HUDSTACT_MAN_MAN_NON},

        {  (U1)HUDIMGADJ_HUDSTACT_STP_STP_NON,  (U1)HUDIMGADJ_HUDSTACT_STP_STP_NON, (U1)HUDIMGADJ_HUDSTACT_STP_STP_NON},
        {  (U1)HUDIMGADJ_HUDSTACT_PLY_PLY_CLR,  (U1)HUDIMGADJ_HUDSTACT_PLY_PLY_CLR, (U1)HUDIMGADJ_HUDSTACT_PLY_PLY_NON},
        {  (U1)HUDIMGADJ_HUDSTACT_PLY_PLY_CLR,  (U1)HUDIMGADJ_HUDSTACT_PLY_PLY_CLR, (U1)HUDIMGADJ_HUDSTACT_PLY_PLY_NON},
        {  (U1)HUDIMGADJ_HUDSTACT_PLY_PLY_CLR,  (U1)HUDIMGADJ_HUDSTACT_PLY_PLY_CLR, (U1)HUDIMGADJ_HUDSTACT_PLY_PLY_NON}
    };

    U1  u1_t_actn;
    U1  u1_t_hudsts;
    U1  u1_t_hudsts_prev;

    if(u2_s_himgadj_stshldtimr < (U2)U2_MAX){
        u2_s_himgadj_stshldtimr += (U2)1U;
    }

    u1_t_actn = (U1)HUDIMGADJ_HUDSTACT_STP_STP_NON;
    if((u1_a_EVT < (U1)HUDIMGADJ_HUDSTEVT_MAX) &&
      (u1_s_himgadj_hudctrlsts < (U1)HUDIMGADJ_HUDCTLSTS_MAX)){
        u1_t_actn = u1_sp_HUDIMGADJ_TBL_HUDSTS[u1_a_EVT][u1_s_himgadj_hudctrlsts];
    }

    switch (u1_t_actn){
        case (U1)HUDIMGADJ_HUDSTACT_STP_STP_NON:
            u1_s_himgadj_hudctrlsts = (U1)HUDIMGADJ_HUDCTLSTS_STP;
            u1_t_hudsts = (U1)HUDIMGADJ_HUDST_STP;
            break;

        case (U1)HUDIMGADJ_HUDSTACT_MAN_MAN_NON:
            u1_s_himgadj_hudctrlsts = (U1)HUDIMGADJ_HUDCTLSTS_MAN;
            u1_t_hudsts = (U1)HUDIMGADJ_HUDST_MAN;
            break;

        case (U1)HUDIMGADJ_HUDSTACT_PLY_PLY_NON:
            u1_s_himgadj_hudctrlsts = (U1)HUDIMGADJ_HUDCTLSTS_PLY;
            u1_t_hudsts = (U1)HUDIMGADJ_HUDST_PLY;
            break;

        case (U1)HUDIMGADJ_HUDSTACT_PLY_PLY_CLR:
            u1_s_himgadj_hudctrlsts = (U1)HUDIMGADJ_HUDCTLSTS_PLY;
            u1_t_hudsts = (U1)HUDIMGADJ_HUDST_PLY;
            u2_s_himgadj_stshldtimr = (U2)0U;
            break;

        default:
            u1_s_himgadj_hudctrlsts = (U1)HUDIMGADJ_HUDCTLSTS_STP;
            u1_t_hudsts = (U1)HUDIMGADJ_HUDST_STP;
            u2_s_himgadj_stshldtimr = (U2)U2_MAX;
            break;
    }

    if(u2_s_himgadj_stshldtimr < (U2)HUDIMGADJ_HUDSTSHLDTIMR_TIM){
        u1_t_hudsts = (U1)HUDIMGADJ_HUDST_PLY;
    }

    u1_t_hudsts_prev = (U1)HUDIMGADJ_HUDST_STP;
#ifdef ComConf_ComSignal_HUD_ST
    (void)Com_ReceiveSignal(ComConf_ComSignal_HUD_ST, &u1_t_hudsts_prev);
    (void)Com_SendSignal(ComConf_ComSignal_HUD_ST, &u1_t_hudsts);
#endif
    if(u1_t_hudsts_prev != u1_t_hudsts){
#ifdef MSG_HUD1S01_TXCH0
        (void)Com_TriggerIPDUSend(MSG_HUD1S01_TXCH0);        /* Event send Trigger */
#endif
    }
}

/*===================================================================================================================================*/
/*  DRIVING_POSITION : U2      u2_g_HudImgAdjGetMovReqPos(void) GV_VIPOS_REQPOS                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2      u2_g_HudImgAdjGetMovReqPos(void)
{
    return (u2_s_himgadj_movreq_pos);
}

/*===================================================================================================================================*/
/*  DRIVING_POSITION : U1      u1_g_HudImgAdjGetMovReqID(void) GV_VIPOS_REQID                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_HudImgAdjGetMovReqID(void)
{
    return (u1_s_himgadj_movreq_id);
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  ZEROPOS_INIT Function Definitions                                                                                                */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  ZEROPOS_INIT : static void vd_s_HudImgAdjRoutInit(void)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_HudImgAdjRoutInit(void)
{
    u2_s_himgadj_dgrtctltimr = (U2)U2_MAX;
    u1_s_himgadj_dgrtctrlsts = (U1)HUDIMGADJ_RTCTLSTS_IDLE;
    u1_s_himgadj_dgrtctl_req = (U1)HUDIMGADJ_RTCTL_NON;
    u1_s_himgadj_dgrtinitreq = (U1)HUDIMGADJ_RTCTL_NON;
}

/*===================================================================================================================================*/
/*  ZEROPOS_INIT : Motor Position Routine Contorol                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_HudImgAdjRoutCtrl(void)
{
    U2  u2_t_imgpos;
    U2  u2_t_rtctl_timout;
    U1  u1_t_evt;
    U1  u1_t_restim;

    if(u2_s_himgadj_dgrtctltimr < (U2)U2_MAX){
        u2_s_himgadj_dgrtctltimr += (U2)1U;
    }

    u1_t_evt = (U1)HUDIMGADJ_RTCTLEVT_NONE;
    if(u2_s_himgadj_dgrtctltimr >= (U2)HUDIMGADJ_RTCTL_INPTTIM){
        u1_t_evt = (U1)HUDIMGADJ_RTCTLEVT_INPTCNT;
    }

    u2_t_imgpos = u2_s_himgadj_gv_vipos_movpos;
    if(u2_t_imgpos != (U2)HUDIMGADJ_RTCTL_ZPDJDG){
        u1_t_evt |= (U1)HUDIMGADJ_RTCTLEVT_ZPDCMP;
    }

    u1_t_restim = u1_CALIB_MCUID0579_RESTIME;
    u2_t_rtctl_timout  = (U2)u1_t_restim * (U2)HUDIMGADJ_RTCTL_RESTIME_LSB;
    if(u2_s_himgadj_dgrtctltimr >= u2_t_rtctl_timout){
        u1_t_evt |= (U1)HUDIMGADJ_RTCTLEVT_TIMOUT;
    }

    if(u1_s_himgadj_dgrtctl_req == (U1)HUDIMGADJ_RTCTL_REQ){
        u1_t_evt |= (U1)HUDIMGADJ_RTCTLEVT_RTCTLRQ;
    }
    u1_s_himgadj_dgrtctl_req = (U1)HUDIMGADJ_RTCTL_NON;

    vd_s_HudImgAdjRoutCtrlActn(u1_t_evt);
}

/*===================================================================================================================================*/
/*  ZEROPOS_INIT : Motor Position Routine Contorol Action                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_HudImgAdjRoutCtrlActn(const U1 u1_a_EVT)
{
    static const U1 u1_sp_HUDIMGADJ_TBL_RTCTLACT[HUDIMGADJ_RTCTLEVT_MAX][HUDIMGADJ_RTCTLSTS_MAX] = {
        { (U1)HUDIMGADJ_RTCTLACT_IDLE_OFF_CMP, (U1)HUDIMGADJ_RTCTLACT_WAIT_ON_HLD, (U1)HUDIMGADJ_RTCTLACT_RUN_ON_HLD,  (U1)HUDIMGADJ_RTCTLACT_NML_OFF_CMP, (U1)HUDIMGADJ_RTCTLACT_ERR_OFF_CMP },
        { (U1)HUDIMGADJ_RTCTLACT_IDLE_OFF_CMP, (U1)HUDIMGADJ_RTCTLACT_RUN_ON_HLD,  (U1)HUDIMGADJ_RTCTLACT_RUN_ON_HLD,  (U1)HUDIMGADJ_RTCTLACT_NML_OFF_CMP, (U1)HUDIMGADJ_RTCTLACT_ERR_OFF_CMP },
        { (U1)HUDIMGADJ_RTCTLACT_IDLE_OFF_CMP, (U1)HUDIMGADJ_RTCTLACT_WAIT_ON_HLD, (U1)HUDIMGADJ_RTCTLACT_NML_OFF_CMP, (U1)HUDIMGADJ_RTCTLACT_NML_OFF_CMP, (U1)HUDIMGADJ_RTCTLACT_ERR_OFF_CMP },
        { (U1)HUDIMGADJ_RTCTLACT_IDLE_OFF_CMP, (U1)HUDIMGADJ_RTCTLACT_RUN_ON_HLD,  (U1)HUDIMGADJ_RTCTLACT_NML_OFF_CMP, (U1)HUDIMGADJ_RTCTLACT_NML_OFF_CMP, (U1)HUDIMGADJ_RTCTLACT_ERR_OFF_CMP },
        { (U1)HUDIMGADJ_RTCTLACT_IDLE_OFF_CMP, (U1)HUDIMGADJ_RTCTLACT_WAIT_ON_HLD, (U1)HUDIMGADJ_RTCTLACT_ERR_OFF_CMP, (U1)HUDIMGADJ_RTCTLACT_NML_OFF_CMP, (U1)HUDIMGADJ_RTCTLACT_ERR_OFF_CMP },
        { (U1)HUDIMGADJ_RTCTLACT_IDLE_OFF_CMP, (U1)HUDIMGADJ_RTCTLACT_RUN_ON_HLD,  (U1)HUDIMGADJ_RTCTLACT_ERR_OFF_CMP, (U1)HUDIMGADJ_RTCTLACT_NML_OFF_CMP, (U1)HUDIMGADJ_RTCTLACT_ERR_OFF_CMP },
        { (U1)HUDIMGADJ_RTCTLACT_IDLE_OFF_CMP, (U1)HUDIMGADJ_RTCTLACT_WAIT_ON_HLD, (U1)HUDIMGADJ_RTCTLACT_ERR_OFF_CMP, (U1)HUDIMGADJ_RTCTLACT_NML_OFF_CMP, (U1)HUDIMGADJ_RTCTLACT_ERR_OFF_CMP },
        { (U1)HUDIMGADJ_RTCTLACT_IDLE_OFF_CMP, (U1)HUDIMGADJ_RTCTLACT_RUN_ON_HLD,  (U1)HUDIMGADJ_RTCTLACT_ERR_OFF_CMP, (U1)HUDIMGADJ_RTCTLACT_NML_OFF_CMP, (U1)HUDIMGADJ_RTCTLACT_ERR_OFF_CMP },
        { (U1)HUDIMGADJ_RTCTLACT_WAIT_ON_CLR,  (U1)HUDIMGADJ_RTCTLACT_WAIT_ON_HLD, (U1)HUDIMGADJ_RTCTLACT_RUN_ON_HLD,  (U1)HUDIMGADJ_RTCTLACT_WAIT_ON_CLR, (U1)HUDIMGADJ_RTCTLACT_WAIT_ON_CLR },
        { (U1)HUDIMGADJ_RTCTLACT_WAIT_ON_CLR,  (U1)HUDIMGADJ_RTCTLACT_RUN_ON_HLD,  (U1)HUDIMGADJ_RTCTLACT_RUN_ON_HLD,  (U1)HUDIMGADJ_RTCTLACT_WAIT_ON_CLR, (U1)HUDIMGADJ_RTCTLACT_WAIT_ON_CLR },
        { (U1)HUDIMGADJ_RTCTLACT_WAIT_ON_CLR,  (U1)HUDIMGADJ_RTCTLACT_WAIT_ON_HLD, (U1)HUDIMGADJ_RTCTLACT_NML_OFF_CMP, (U1)HUDIMGADJ_RTCTLACT_WAIT_ON_CLR, (U1)HUDIMGADJ_RTCTLACT_WAIT_ON_CLR },
        { (U1)HUDIMGADJ_RTCTLACT_WAIT_ON_CLR,  (U1)HUDIMGADJ_RTCTLACT_RUN_ON_HLD,  (U1)HUDIMGADJ_RTCTLACT_NML_OFF_CMP, (U1)HUDIMGADJ_RTCTLACT_WAIT_ON_CLR, (U1)HUDIMGADJ_RTCTLACT_WAIT_ON_CLR },
        { (U1)HUDIMGADJ_RTCTLACT_WAIT_ON_CLR,  (U1)HUDIMGADJ_RTCTLACT_WAIT_ON_HLD, (U1)HUDIMGADJ_RTCTLACT_ERR_OFF_CMP, (U1)HUDIMGADJ_RTCTLACT_WAIT_ON_CLR, (U1)HUDIMGADJ_RTCTLACT_WAIT_ON_CLR },
        { (U1)HUDIMGADJ_RTCTLACT_WAIT_ON_CLR,  (U1)HUDIMGADJ_RTCTLACT_RUN_ON_HLD,  (U1)HUDIMGADJ_RTCTLACT_ERR_OFF_CMP, (U1)HUDIMGADJ_RTCTLACT_WAIT_ON_CLR, (U1)HUDIMGADJ_RTCTLACT_WAIT_ON_CLR },
        { (U1)HUDIMGADJ_RTCTLACT_WAIT_ON_CLR,  (U1)HUDIMGADJ_RTCTLACT_WAIT_ON_HLD, (U1)HUDIMGADJ_RTCTLACT_ERR_OFF_CMP, (U1)HUDIMGADJ_RTCTLACT_WAIT_ON_CLR, (U1)HUDIMGADJ_RTCTLACT_WAIT_ON_CLR },
        { (U1)HUDIMGADJ_RTCTLACT_WAIT_ON_CLR,  (U1)HUDIMGADJ_RTCTLACT_RUN_ON_HLD,  (U1)HUDIMGADJ_RTCTLACT_ERR_OFF_CMP, (U1)HUDIMGADJ_RTCTLACT_WAIT_ON_CLR, (U1)HUDIMGADJ_RTCTLACT_WAIT_ON_CLR }
    };

    U1  u1_t_actn;

    u1_t_actn = (U1)HUDIMGADJ_RTCTLACT_IDLE_OFF_CMP;
    if((u1_a_EVT < (U1)HUDIMGADJ_RTCTLEVT_MAX) &&
      (u1_s_himgadj_dgrtctrlsts < (U1)HUDIMGADJ_RTCTLSTS_MAX)){
        u1_t_actn = u1_sp_HUDIMGADJ_TBL_RTCTLACT[u1_a_EVT][u1_s_himgadj_dgrtctrlsts];
    }

    switch (u1_t_actn){
        case (U1)HUDIMGADJ_RTCTLACT_IDLE_OFF_CMP:
            u1_s_himgadj_dgrtctrlsts = (U1)HUDIMGADJ_RTCTLSTS_IDLE;
            u1_s_himgadj_dgrtinitreq = (U1)HUDIMGADJ_RTCTL_NON;     /* GV_DG_VIPOS_INIT */
            u2_s_himgadj_dgrtctltimr = (U2)U2_MAX;
            break;

        case (U1)HUDIMGADJ_RTCTLACT_WAIT_ON_CLR:
            u1_s_himgadj_dgrtctrlsts = (U1)HUDIMGADJ_RTCTLSTS_WAIT;
            u1_s_himgadj_dgrtinitreq = (U1)HUDIMGADJ_RTCTL_INITREQ; /* GV_DG_VIPOS_INIT */
            u2_s_himgadj_dgrtctltimr = (U2)0U;
            break;

        case (U1)HUDIMGADJ_RTCTLACT_WAIT_ON_HLD:
            u1_s_himgadj_dgrtctrlsts = (U1)HUDIMGADJ_RTCTLSTS_WAIT;
            u1_s_himgadj_dgrtinitreq = (U1)HUDIMGADJ_RTCTL_INITREQ; /* GV_DG_VIPOS_INIT */
            break;

        case (U1)HUDIMGADJ_RTCTLACT_RUN_ON_HLD:
            u1_s_himgadj_dgrtctrlsts = (U1)HUDIMGADJ_RTCTLSTS_RUN;
            u1_s_himgadj_dgrtinitreq = (U1)HUDIMGADJ_RTCTL_INITREQ; /* GV_DG_VIPOS_INIT */
            break;

        case (U1)HUDIMGADJ_RTCTLACT_NML_OFF_CMP:
            u1_s_himgadj_dgrtctrlsts = (U1)HUDIMGADJ_RTCTLSTS_NML;
            u1_s_himgadj_dgrtinitreq = (U1)HUDIMGADJ_RTCTL_NON;     /* GV_DG_VIPOS_INIT */
            u2_s_himgadj_dgrtctltimr = (U2)U2_MAX;
            break;

        case (U1)HUDIMGADJ_RTCTLACT_ERR_OFF_CMP:
            u1_s_himgadj_dgrtctrlsts = (U1)HUDIMGADJ_RTCTLSTS_ERR;
            u1_s_himgadj_dgrtinitreq = (U1)HUDIMGADJ_RTCTL_NON;     /* GV_DG_VIPOS_INIT */
            u2_s_himgadj_dgrtctltimr = (U2)U2_MAX;
            break;

        default:
            u1_s_himgadj_dgrtctrlsts = (U1)HUDIMGADJ_RTCTLSTS_IDLE;
            u1_s_himgadj_dgrtinitreq = (U1)HUDIMGADJ_RTCTL_NON;     /* GV_DG_VIPOS_INIT */
            u2_s_himgadj_dgrtctltimr = (U2)U2_MAX;
            break;
    }
}

/*===================================================================================================================================*/
/*  ZEROPOS_INIT : U1      u1_g_HudImgAdjRoutStart(void)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_HudImgAdjRoutRslt(void)
{
    static const U1 u1_sp_HUDIMGADJ_TBL_RTCTL_RSLT[HUDIMGADJ_RTCTLSTS_MAX] = 
    {
        (U1)HUDIMGADJ_RTCTLRSLT_IDLE,       /* HUDIMGADJ_RTCTLSTS_IDLE  */
        (U1)HUDIMGADJ_RTCTLRSLT_RUN,        /* HUDIMGADJ_RTCTLSTS_WAIT  */
        (U1)HUDIMGADJ_RTCTLRSLT_RUN,        /* HUDIMGADJ_RTCTLSTS_RUN   */
        (U1)HUDIMGADJ_RTCTLRSLT_NML,        /* HUDIMGADJ_RTCTLSTS_NML   */
        (U1)HUDIMGADJ_RTCTLRSLT_ERR         /* HUDIMGADJ_RTCTLSTS_ERR   */
    };

    U1  u1_t_result;

    u1_t_result = (U1)HUDIMGADJ_RTCTLRSLT_IDLE;
    if(u1_s_himgadj_dgrtctrlsts < (U1)HUDIMGADJ_RTCTLSTS_MAX){
        u1_t_result = u1_sp_HUDIMGADJ_TBL_RTCTL_RSLT[u1_s_himgadj_dgrtctrlsts];
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  ZEROPOS_INIT : U1      u1_g_HudImgAdjRoutStartIsOK(void)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_HudImgAdjRoutStartIsOK(void)
{
    U2  u2_t_imgpos;
    U1  u1_t_result;

    u2_t_imgpos = u2_s_himgadj_gv_vipos_movpos;
    if((u1_s_himgadj_dgrtctrlsts == (U1)HUDIMGADJ_RTCTLSTS_WAIT) ||
       (u1_s_himgadj_dgrtctrlsts == (U1)HUDIMGADJ_RTCTLSTS_RUN)  ||
       (u2_t_imgpos == (U2)HUDIMGADJ_RTCTL_ZPDJDG)){
        u1_t_result = (U1)FALSE;
    }
    else{
        u1_s_himgadj_dgrtctl_req = (U1)HUDIMGADJ_RTCTL_REQ;
        u1_t_result = (U1)TRUE;
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  ZEROPOS_INIT : U1      u1_g_HudImgAdjGetGvRtctlIniReq(void) GV_DG_VIPOS_INIT                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_HudImgAdjGetGvRtctlIniReq(void)
{
    U1  u1_t_ret;

    u1_t_ret = (U1)FALSE;
    if(u1_s_himgadj_dgrtinitreq == (U1)HUDIMGADJ_RTCTL_INITREQ){
        u1_t_ret = (U1)TRUE;
    }
    return (u1_t_ret);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version          Date        Author  Change Description                                                                          */
/* ---------------   ----------  ------  ------------------------------------------------------------------------------------------- */
/* 2.0.0              2020.03.31  HS      New                                                                                        */
/* 2.1.0              2022.01.16  HiS     The Hud Function Invalid Process was added.                                                */
/* 2.1.1              2022.06.27  HT      Removed write judgement from Motor Position Memory Update Function.                        */
/* 2.2.0              2024.01.12  His     Applied calibration implementation                                                         */
/* 2.2.1              2024.07.02  His     Delete Calibration Guard Process.                                                          */
/* 2.2.2              2024.08.06  His     Routine Control Result Value was revised.                                                  */
/* 2.2.3              2024.09.13  His     DID 280C was revised. (u2_s_HudImgAdjowimgpos and u1_g_HudImgAdjReadDataImgPos)            */
/* 2.2.4              2025.03.17  YuK     Removed the max and min limits for HUD position regeneration.                              */
/*                                                                                                                                   */
/*  * HS  = Hidenobu Suzuki, NCOS                                                                                                    */
/*  * HiS = Hidenobu Suzuki, MSE                                                                                                     */
/*  * HT  = Hideki Takagi,   MSE                                                                                                     */
/*  * YuK = Yuki Koshimae,   MSE                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
