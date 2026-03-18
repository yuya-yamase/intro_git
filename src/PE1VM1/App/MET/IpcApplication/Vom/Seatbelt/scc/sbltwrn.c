/* 3.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Seatbelt reminder warning                                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SBLTWRN_C_MAJOR                         (3)
#define SBLTWRN_C_MINOR                         (1)
#define SBLTWRN_C_PATCH                         (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "sbltwrn_cfg_private.h"
#include "memfill_u1.h"
#include "memfill_u2.h"
#include "sbltwrn.h"
#include "sbltwrn_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((SBLTWRN_C_MAJOR != SBLTWRN_H_MAJOR) || \
     (SBLTWRN_C_MINOR != SBLTWRN_H_MINOR) || \
     (SBLTWRN_C_PATCH != SBLTWRN_H_PATCH))
#error "sbltwrn.c and sbltwrn.h : source and header files are inconsistent!"
#endif

#if ((SBLTWRN_C_MAJOR != SBLTWRN_CFG_PRIVATE_H_MAJOR) || \
     (SBLTWRN_C_MINOR != SBLTWRN_CFG_PRIVATE_H_MINOR) || \
     (SBLTWRN_C_PATCH != SBLTWRN_CFG_PRIVATE_H_PATCH))
#error "sbltwrn.c and sbltwrn_cfg_private.h : source and header files are inconsistent!"
#endif

#if ((SBLTWRN_C_MAJOR != SBLTWRN_PRIVATE_H_MAJOR) || \
     (SBLTWRN_C_MINOR != SBLTWRN_PRIVATE_H_MINOR) || \
     (SBLTWRN_C_PATCH != SBLTWRN_PRIVATE_H_PATCH))
#error "sbltwrn.c and sbltwrn_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#define     SBLTWRN_CHMFLG_CNT_LGLTMR           (0x01U)         /* Legal warn timer cnt-up    */
#define     SBLTWRN_CHMFLG_CNT_GPTMR            (0x02U)         /* GP timer cnt-up    */
#define     SBLTWRN_CHMFLG_CNT_LV1TMR           (0x04U)         /* Lv1 timer cnt-up    */
#define     SBLTWRN_CHMFLG_CNT_LV2TMR           (0x08U)         /* Lv2 timer cnt-up    */
#define     SBLTWRN_CHMFLG_SSPND_GPLV1          (0x10U)         /* GP_Lv1 suspend flag */
#define     SBLTWRN_CHMFLG_SSPND_LV2            (0x20U)         /* Lv2 suspend flag    */
#define     SBLTWRN_CHMFLG_GPTIM_CTL            (0x40U)         /* GP timer cnt-up flag    */

#define     SBLTWRN_CHMOPT_MSK                  (0xFFFFFF00U)
#define     SBLTWRN_CHMOPT_LGLTM_CNTUP          (0x00000100U)
#define     SBLTWRN_CHMOPT_GPTM_CNTUP           (0x00000200U)
#define     SBLTWRN_CHMOPT_LV1TM_CNTUP          (0x00000400U)
#define     SBLTWRN_CHMOPT_LV2TM_CNTUP          (0x00000800U)
#define     SBLTWRN_CHMOPT_LGLTM_CNTSTP         (0x00001000U)
#define     SBLTWRN_CHMOPT_GPTM_CNTSTP          (0x00002000U)
#define     SBLTWRN_CHMOPT_LV1TM_CNTSTP         (0x00004000U)
#define     SBLTWRN_CHMOPT_LV2TM_CNTSTP         (0x00008000U)
#define     SBLTWRN_CHMOPT_LGLTM_CNTCLR         (0x00010000U)
#define     SBLTWRN_CHMOPT_GPTM_CNTCLR          (0x00020000U)
#define     SBLTWRN_CHMOPT_LV1TM_CNTCLR         (0x00040000U)
#define     SBLTWRN_CHMOPT_LV2TM_CNTCLR         (0x00080000U)
#define     SBLTWRN_CHMOPT_GPLV1_SSPND_SET      (0x00100000U)
#define     SBLTWRN_CHMOPT_LV2_SSPND_SET        (0x00200000U)
#define     SBLTWRN_CHMOPT_GPLV1_SSPND_CLR      (0x00400000U)
#define     SBLTWRN_CHMOPT_LV2_SSPND_CLR        (0x00800000U)
#define     SBLTWRN_CHMOPT_GPTMRFLG_SET         (0x01000000U)
#define     SBLTWRN_CHMOPT_GPTMRFLG_CLR         (0x02000000U)

#define     SBLTWRN_NUM_CHMTIMER                (4U)
#define     SBLTWRN_CHMTIMER_LGL                (0U)
#define     SBLTWRN_CHMTIMER_GP                 (1U)
#define     SBLTWRN_CHMTIMER_LV1                (2U)
#define     SBLTWRN_CHMTIMER_LV2                (3U)

#define     SBLTWRN_TTOPT_DRTM_CNTUP            (0x00000100U)
#define     SBLTWRN_TTOPT_UBTM_CNTUP            (0x00000200U)
#define     SBLTWRN_TTOPT_LGLTM_CNTUP           (0x00000400U)
#define     SBLTWRN_TTOPT_DRTM_CNTSTP           (0x00000800U)
#define     SBLTWRN_TTOPT_UBTM_CNTSTP           (0x00001000U)
#define     SBLTWRN_TTOPT_LGLTM_CNTSTP          (0x00002000U)
#define     SBLTWRN_TTOPT_DRTM_CNTCLR           (0x00004000U)
#define     SBLTWRN_TTOPT_UBTM_CNTCLR           (0x00008000U)
#define     SBLTWRN_TTOPT_LGLTM_CNTCLR          (0x00010000U)

#define     SBLTWRN_NUM_TTTIMER                 (3U)
#define     SBLTWRN_TTTIMER_DOR                 (0U)            /* The time after door closed */
#define     SBLTWRN_TTTIMER_UBK                 (1U)            /* Unbuckle timer */
#define     SBLTWRN_TTTIMER_LGL                 (2U)            /* Legal timer (Telltale) */

#define     SBLTWRN_NUM_WRNOFFJDG               (4U)
#define     SBLTWRN_WRNOFFJDG_NON               (0U)
#define     SBLTWRN_WRNOFFJDG_BY_SFT_R          (1U)
#define     SBLTWRN_WRNOFFJDG_BY_PARK           (2U)
#define     SBLTWRN_WRNOFFJDG_BY_DRBKL          (3U)

#define     SBLTWRN_GPTMCHK_GPTM_EXC            (0x01U)         /* GP timer exceeded        */
#define     SBLTWRN_GPTMCHK_SPD_EXC             (0x02U)         /* Speed exceeded           */
#define     SBLTWRN_GPTMCHK_GP_ENA              (0x04U)         /* GP enable                */
#define     SBLTWRN_GPTMCHK_OTH_WRN             (0x08U)         /* other seat warn is actv  */

#define     SBLTWRN_NUM_CHMSTCHK                (2U)            /* A number of Current chime status check items     */
#define     SBLTWRN_CHMSTCHK_WRN                (0U)            /* chmsts is in UNBKNT, GP, LV1, LV2, or L2CMP      */
#define     SBLTWRN_CHMSTCHK_GPLV1              (1U)            /* chmsts is in UNBKNT, GP, or LV1                  */

#define     SBLTWRN_TTSTCHK_OTHWRN              ((1U << SBLTWRN_TTSTS_RR_PARK) | (1U << SBLTWRN_TTSTS_RR_LWSP) | (1U << SBLTWRN_TTSTS_RR_LV1) | (1U << SBLTWRN_TTSTS_RR_LV2) | (1U << SBLTWRN_TTSTS_RR_L2CMP_ON))   /* Other seat warning is active */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct {
    U2  u2p_timer[SBLTWRN_NUM_CHMTIMER];   /* Elapsed Timer Counter */
    U1  u1_ctlsts;      /* Chime Status */
    U1  u1_flg;         /* Ctrl Flags (SBLTWRN_CHMFLG_xxx) */
} ST_SBLTWRN_CHMST;

typedef struct {
    U2  u2p_timer[SBLTWRN_NUM_TTTIMER];
    U1  u1_ctlsts;
    U1  u1_flg;
} ST_SBLTWRN_TTST;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  ST_SBLTWRN_CHMST        st_sp_sbltwrn_chmsts[SBLTWRN_NUM_ALLSEAT];
static  ST_SBLTWRN_TTST         st_sp_sbltwrn_ttsts[SBLTWRN_NUM_ALLSEAT];
static  U2                      u2_s_sbltwrn_igontm;
static  U2                      u2_s_sbltwrn_bkledgtmr;
static  U2                      u2_s_sbltwrn_unbklflg;
static  U2                      u2_s_sbltwrn_failsts;
static  U1                      u1_s_sbltwrn_precfg;
static  U1                      u1_sp_sbltwrn_sbrbit[SBLTWRN_SBRBIT_IDX_ALL];
static  U1                      u1_sp_sbltwrn_sbr_oldsts[SBLTWRN_NUM_3ROWSEAT];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static        void    vd_s_SbltwrnTrans(const U1 u1_a_DSTTYP);
static        void    vd_s_SbltwrnVarChgChk(const U1 u1_a_DSTTYP);
static        void    vd_s_SbltwrnBklEdgChk(ST_SBLTWRN_VCLST *stp_a_vclsts);
static        void    vd_s_SbltwrnUnbkleFlgPostChk(void);
static        void    vd_s_SbltwrnStm(const ST_SBLTWRN_VCLST *stp_a_VCLSTS);
static        void    vd_s_SbltwrnChimeStm(const ST_SBLTWRN_VCLST *stp_a_VCLSTS);
static        void    vd_s_SbltwrnTtStm(const ST_SBLTWRN_VCLST *stp_a_VCLSTS);
static        U1      u1_s_SbltwrnTtStmVldChk(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS);
static        void    vd_s_SbltwrnTtTimAct(ST_SBLTWRN_TTST *stp_a_ttsts, const U4 u4_a_VCLSTS, U4 u4_a_ttopt, const U1 u1_a_SEATTYP, const U1 u1_a_CNT_UP);
static        U4      u4_s_SbltwrnChimeCnd(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static        void    vd_s_SbltwrnChimeFlgPreChk(const ST_SBLTWRN_VCLST *stp_a_VCLSTS, ST_SBLTWRN_CHMST *stp_a_chmsts, const U1 u1_a_SEATID);
static        U4      u4_s_SbltwrnChimeFlgPostChk(const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U1 u1_a_SEATID, const U4 u4_a_CHMOPT, const U1 u1_a_GPFLG_PREV);
static        void    vd_s_SbltwrnChimeTimAct(ST_SBLTWRN_CHMST *stp_a_chmsts, const U4 u4_a_CHMOPT, const U1 u1_a_CNT_UP);
static        U1      u1_s_SbltwrnChmTrns_GpCndCmn(const ST_SBLTWRN_WRNPRM *stp_a_WRNPRM, const U1 u1_a_SEATTYP);
static        U4      u4_s_SbltwrnChmTrns_condAB(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnChmTrns_condAF(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnChmTrns_condAH(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnChmTrns_condAI(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnChmTrns_condBx(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnChmTrns_condLegal(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnChmTrns_condEA(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnChmTrns_condEF(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnChmTrns_condEI(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnChmTrns_condFGHtoA(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnChmTrns_condFG(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnChmTrns_condFH(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnChmTrns_condFI(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnChmTrns_condGH(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnChmTrns_condGI(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnChmTrns_condHI(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnChmTrns_condIA(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnChmTrns_condIJ(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnChmTrns_condJA(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static        U1      u1_s_SbltwrnChmTrns_OffJdgCmn(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS);
static        U4      u4_s_SbltwrnTtTrns_condAB(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condAF(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condAG(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condAI(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condBx(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condLegal(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condEH(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condEI(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condXtoA(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condFG(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condGH(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condXtoIJ(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condHtoIJ(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condIJ_JI(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condAK(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condAL(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condAN(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condAO(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condAP(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condAQ(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condAS(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condKA(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condKL(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condKO(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condLA(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condLN(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condLO(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condLP(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condLQ(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condLS(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condNA(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condNL(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condNS(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condOA(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condOL(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condON(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condOR(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condOtoPQ(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condOQtoR_cmn(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condOS(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condPA(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condPL(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condPQtoN(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condPQ(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condQA(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condQL(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condQO(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condQR(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condRA(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condRL(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condRO(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condSA(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condSL(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condSN(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condNStoO(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condNStoP(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U4      u4_s_SbltwrnTtTrns_condNStoQ(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U1      u1_s_SbltwrnTtTrns_ChmStsChk(const U1 u1_a_SEATID, const U1 u1_a_CHK_ITEM);
static        U4      u4_s_SbltwrnTtStmCnd(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static        U1      u1_s_SbltwrnChmTrns_GptmChk(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static        void    vd_s_SbltwrnInitChmsts(ST_SBLTWRN_CHMST *stp_a_chmsts);
static        void    vd_s_SbltwrnInitTtsts(ST_SBLTWRN_TTST *stp_a_ttsts);
static        void    vd_s_SbltwrnSbrBzrChgDet(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const SBLTWRN_CHMTYP   fp_sp_u4_SBLTWRN_CHMSTM_CND_A[] = {
    &u4_s_SbltwrnChmTrns_condAB,
    &u4_s_SbltwrnChmTrns_condAI,
    &u4_s_SbltwrnChmTrns_condAH,
    &u4_s_SbltwrnChmTrns_condAF
};

static const SBLTWRN_CHMTYP   fp_sp_u4_SBLTWRN_CHMSTM_CND_B[] = {
    &u4_s_SbltwrnChmTrns_condBx
};

static const SBLTWRN_CHMTYP   fp_sp_u4_SBLTWRN_CHMSTM_CND_C[] = {
    &u4_s_SbltwrnChmTrns_condLegal
};

static const SBLTWRN_CHMTYP   fp_sp_u4_SBLTWRN_CHMSTM_CND_D[] = {
    &u4_s_SbltwrnChmTrns_condLegal
};

static const SBLTWRN_CHMTYP   fp_sp_u4_SBLTWRN_CHMSTM_CND_E[] = {
    &u4_s_SbltwrnChmTrns_condEA,
    &u4_s_SbltwrnChmTrns_condEI,
    &u4_s_SbltwrnChmTrns_condAH,    /* note: Same as condAH */
    &u4_s_SbltwrnChmTrns_condEF
};

static const SBLTWRN_CHMTYP   fp_sp_u4_SBLTWRN_CHMSTM_CND_F[] = {
    &u4_s_SbltwrnChmTrns_condFGHtoA,
    &u4_s_SbltwrnChmTrns_condFI,
    &u4_s_SbltwrnChmTrns_condFH,
    &u4_s_SbltwrnChmTrns_condFG
};

static const SBLTWRN_CHMTYP   fp_sp_u4_SBLTWRN_CHMSTM_CND_G[] = {
    &u4_s_SbltwrnChmTrns_condFGHtoA,
    &u4_s_SbltwrnChmTrns_condGI,
    &u4_s_SbltwrnChmTrns_condGH
};

static const SBLTWRN_CHMTYP   fp_sp_u4_SBLTWRN_CHMSTM_CND_H[] = {
    &u4_s_SbltwrnChmTrns_condFGHtoA,
    &u4_s_SbltwrnChmTrns_condHI
};

static const SBLTWRN_CHMTYP   fp_sp_u4_SBLTWRN_CHMSTM_CND_I[] = {
    &u4_s_SbltwrnChmTrns_condIA,
    &u4_s_SbltwrnChmTrns_condIJ
};

static const SBLTWRN_CHMTYP   fp_sp_u4_SBLTWRN_CHMSTM_CND_J[] = {
    &u4_s_SbltwrnChmTrns_condJA
};

static const ST_SBLTWRN_CHMTYP st_sp_SBLTWRN_CHMSTM[SBLTWRN_NUM_CHMSTS] = {
    {&fp_sp_u4_SBLTWRN_CHMSTM_CND_A[0], sizeof(fp_sp_u4_SBLTWRN_CHMSTM_CND_A) / sizeof(fp_sp_u4_SBLTWRN_CHMSTM_CND_A[0])},    /* SBLTWRN_CHMSTS_OFF       */  
    {&fp_sp_u4_SBLTWRN_CHMSTM_CND_B[0], sizeof(fp_sp_u4_SBLTWRN_CHMSTM_CND_B) / sizeof(fp_sp_u4_SBLTWRN_CHMSTM_CND_B[0])},    /* SBLTWRN_CHMSTS_LGLPR     */
    {&fp_sp_u4_SBLTWRN_CHMSTM_CND_D[0], sizeof(fp_sp_u4_SBLTWRN_CHMSTM_CND_D) / sizeof(fp_sp_u4_SBLTWRN_CHMSTM_CND_D[0])},    /* SBLTWRN_CHMSTS_LEGAL     */
    {&fp_sp_u4_SBLTWRN_CHMSTM_CND_C[0], sizeof(fp_sp_u4_SBLTWRN_CHMSTM_CND_C) / sizeof(fp_sp_u4_SBLTWRN_CHMSTM_CND_C[0])},    /* SBLTWRN_CHMSTS_LGLWT     */
    {&fp_sp_u4_SBLTWRN_CHMSTM_CND_E[0], sizeof(fp_sp_u4_SBLTWRN_CHMSTM_CND_E) / sizeof(fp_sp_u4_SBLTWRN_CHMSTM_CND_E[0])},    /* SBLTWRN_CHMSTS_LGLCMP    */
    {&fp_sp_u4_SBLTWRN_CHMSTM_CND_F[0], sizeof(fp_sp_u4_SBLTWRN_CHMSTM_CND_F) / sizeof(fp_sp_u4_SBLTWRN_CHMSTM_CND_F[0])},    /* SBLTWRN_CHMSTS_UNBKNT    */
    {&fp_sp_u4_SBLTWRN_CHMSTM_CND_G[0], sizeof(fp_sp_u4_SBLTWRN_CHMSTM_CND_G) / sizeof(fp_sp_u4_SBLTWRN_CHMSTM_CND_G[0])},    /* SBLTWRN_CHMSTS_GP        */
    {&fp_sp_u4_SBLTWRN_CHMSTM_CND_H[0], sizeof(fp_sp_u4_SBLTWRN_CHMSTM_CND_H) / sizeof(fp_sp_u4_SBLTWRN_CHMSTM_CND_H[0])},    /* SBLTWRN_CHMSTS_LV1       */
    {&fp_sp_u4_SBLTWRN_CHMSTM_CND_I[0], sizeof(fp_sp_u4_SBLTWRN_CHMSTM_CND_I) / sizeof(fp_sp_u4_SBLTWRN_CHMSTM_CND_I[0])},    /* SBLTWRN_CHMSTS_LV2       */
    {&fp_sp_u4_SBLTWRN_CHMSTM_CND_J[0], sizeof(fp_sp_u4_SBLTWRN_CHMSTM_CND_J) / sizeof(fp_sp_u4_SBLTWRN_CHMSTM_CND_J[0])}     /* SBLTWRN_CHMSTS_L2CMP     */
};

static ST_SBLTWRN_TT_STM const fp_sp_u4_SBLTWRN_TTSTM_CND_A[] = {
    /* fp_u4_STM */                     /* u1_TYPMSK */
    { &u4_s_SbltwrnTtTrns_condAB,       (U1)(SBLTWRN_SEATTYPBIT_FR_ALL)  },
    { &u4_s_SbltwrnTtTrns_condAG,       (U1)(SBLTWRN_SEATTYPBIT_FR_ALL)  },
    { &u4_s_SbltwrnTtTrns_condAF,       (U1)(SBLTWRN_SEATTYPBIT_FR_ALL)  },
    { &u4_s_SbltwrnTtTrns_condAI,       (U1)(SBLTWRN_SEATTYPBIT_FR_ALL)  },
    { &u4_s_SbltwrnTtTrns_condAQ,       (U1)(SBLTWRN_SEATTYPBIT_RS_ALL)  },
    { &u4_s_SbltwrnTtTrns_condAP,       (U1)(SBLTWRN_SEATTYPBIT_RS_ALL)  },
    { &u4_s_SbltwrnTtTrns_condAL,       (U1)(SBLTWRN_SEATTYPBIT_RS_ALL)  },
    { &u4_s_SbltwrnTtTrns_condAS,       (U1)(SBLTWRN_SEATTYPBIT_RS_ALL)  },
    { &u4_s_SbltwrnTtTrns_condAN,       (U1)(SBLTWRN_SEATTYPBIT_RS_ALL)  },
    { &u4_s_SbltwrnTtTrns_condAK,       (U1)(SBLTWRN_SEATTYPBIT_RS_NOSN) },
    { &u4_s_SbltwrnTtTrns_condAO,       (U1)(SBLTWRN_SEATTYPBIT_RS_NOSN) }
};

static ST_SBLTWRN_TT_STM const fp_sp_u4_SBLTWRN_TTSTM_CND_B[] = {
    /* fp_u4_STM */                     /* u1_TYPMSK */
    { &u4_s_SbltwrnTtTrns_condBx,       (U1)(SBLTWRN_SEATTYPBIT_FR_ALL)  }
};

static ST_SBLTWRN_TT_STM const fp_sp_u4_SBLTWRN_TTSTM_CND_C[] = {
    /* fp_u4_STM */                     /* u1_TYPMSK */
    { &u4_s_SbltwrnTtTrns_condLegal,    (U1)(SBLTWRN_SEATTYPBIT_FR_ALL)  }
};

static ST_SBLTWRN_TT_STM const fp_sp_u4_SBLTWRN_TTSTM_CND_D[] = {
    /* fp_u4_STM */                     /* u1_TYPMSK */
    { &u4_s_SbltwrnTtTrns_condLegal,    (U1)(SBLTWRN_SEATTYPBIT_FR_ALL)  }
};

static ST_SBLTWRN_TT_STM const fp_sp_u4_SBLTWRN_TTSTM_CND_E[] = {
    /* fp_u4_STM */                     /* u1_TYPMSK */
    { &u4_s_SbltwrnTtTrns_condAG,       (U1)(SBLTWRN_SEATTYPBIT_FR_ALL)  }, /* Same as Cond A */
    { &u4_s_SbltwrnTtTrns_condAF,       (U1)(SBLTWRN_SEATTYPBIT_FR_ALL)  }, /* Same as Cond A */
    { &u4_s_SbltwrnTtTrns_condEI,       (U1)(SBLTWRN_SEATTYPBIT_FR_ALL)  },
    { &u4_s_SbltwrnTtTrns_condEH,       (U1)(SBLTWRN_SEATTYPBIT_FR_ALL)  },
    { &u4_s_SbltwrnTtTrns_condXtoA,     (U1)(SBLTWRN_SEATTYPBIT_FR_ALL)  }
};

static ST_SBLTWRN_TT_STM const fp_sp_u4_SBLTWRN_TTSTM_CND_F[] = {
    /* fp_u4_STM */                     /* u1_TYPMSK */
    { &u4_s_SbltwrnTtTrns_condFG,       (U1)(SBLTWRN_SEATTYPBIT_FR_ALL)  },
    { &u4_s_SbltwrnTtTrns_condXtoIJ,    (U1)(SBLTWRN_SEATTYPBIT_FR_ALL)  },
    { &u4_s_SbltwrnTtTrns_condXtoA,     (U1)(SBLTWRN_SEATTYPBIT_FR_ALL)  }
};

static ST_SBLTWRN_TT_STM const fp_sp_u4_SBLTWRN_TTSTM_CND_G[] = {
    /* fp_u4_STM */                     /* u1_TYPMSK */
    { &u4_s_SbltwrnTtTrns_condGH,       (U1)(SBLTWRN_SEATTYPBIT_FR_ALL)  },
    { &u4_s_SbltwrnTtTrns_condXtoIJ,    (U1)(SBLTWRN_SEATTYPBIT_FR_ALL)  },
    { &u4_s_SbltwrnTtTrns_condXtoA,     (U1)(SBLTWRN_SEATTYPBIT_FR_ALL)  }
};

static ST_SBLTWRN_TT_STM const fp_sp_u4_SBLTWRN_TTSTM_CND_H[] = {
    /* fp_u4_STM */                     /* u1_TYPMSK */
    { &u4_s_SbltwrnTtTrns_condHtoIJ,    (U1)(SBLTWRN_SEATTYPBIT_FR_ALL)  },
    { &u4_s_SbltwrnTtTrns_condXtoA,     (U1)(SBLTWRN_SEATTYPBIT_FR_ALL)  }
};

static ST_SBLTWRN_TT_STM const fp_sp_u4_SBLTWRN_TTSTM_CND_I[] = {
    /* fp_u4_STM */                     /* u1_TYPMSK */
    { &u4_s_SbltwrnTtTrns_condAG,       (U1)(SBLTWRN_SEATTYPBIT_FR_ALL)  }, /* Same as cond A */
    { &u4_s_SbltwrnTtTrns_condAF,       (U1)(SBLTWRN_SEATTYPBIT_FR_ALL)  }, /* Same as cond A */
    { &u4_s_SbltwrnTtTrns_condIJ_JI,    (U1)(SBLTWRN_SEATTYPBIT_FR_ALL)  },
    { &u4_s_SbltwrnTtTrns_condXtoA,     (U1)(SBLTWRN_SEATTYPBIT_FR_ALL)  }
};

static ST_SBLTWRN_TT_STM const fp_sp_u4_SBLTWRN_TTSTM_CND_J[] = {
    /* fp_u4_STM */                     /* u1_TYPMSK */
    { &u4_s_SbltwrnTtTrns_condXtoA,     (U1)(SBLTWRN_SEATTYPBIT_FR_ALL)  },
    { &u4_s_SbltwrnTtTrns_condAF,       (U1)(SBLTWRN_SEATTYPBIT_FR_ALL)  }, /* Same as cond A */
    { &u4_s_SbltwrnTtTrns_condAG,       (U1)(SBLTWRN_SEATTYPBIT_FR_ALL)  }, /* Same as cond A */
    { &u4_s_SbltwrnTtTrns_condIJ_JI,    (U1)(SBLTWRN_SEATTYPBIT_FR_ALL)  }
};

static ST_SBLTWRN_TT_STM const fp_sp_u4_SBLTWRN_TTSTM_CND_K[] = {
    /* fp_u4_STM */                     /* u1_TYPMSK */
    { &u4_s_SbltwrnTtTrns_condKL,       (U1)(SBLTWRN_SEATTYPBIT_RS_NOSN) },
    { &u4_s_SbltwrnTtTrns_condKO,       (U1)(SBLTWRN_SEATTYPBIT_RS_NOSN) },
    { &u4_s_SbltwrnTtTrns_condKA,       (U1)(SBLTWRN_SEATTYPBIT_RS_NOSN) }
};

static ST_SBLTWRN_TT_STM const fp_sp_u4_SBLTWRN_TTSTM_CND_L[] = {
    /* fp_u4_STM */                     /* u1_TYPMSK */
    { &u4_s_SbltwrnTtTrns_condLQ,       (U1)(SBLTWRN_SEATTYPBIT_RS_ALL)  },
    { &u4_s_SbltwrnTtTrns_condLP,       (U1)(SBLTWRN_SEATTYPBIT_RS_ALL)  },
    { &u4_s_SbltwrnTtTrns_condLS,       (U1)(SBLTWRN_SEATTYPBIT_RS_ALL)  },
    { &u4_s_SbltwrnTtTrns_condLN,       (U1)(SBLTWRN_SEATTYPBIT_RS_ALL)  },
    { &u4_s_SbltwrnTtTrns_condLO,       (U1)(SBLTWRN_SEATTYPBIT_RS_NOSN) },
    { &u4_s_SbltwrnTtTrns_condLA,       (U1)(SBLTWRN_SEATTYPBIT_RS_ALL)  }
};

static ST_SBLTWRN_TT_STM const fp_sp_u4_SBLTWRN_TTSTM_CND_N[] = {
    /* fp_u4_STM */                     /* u1_TYPMSK */
    { &u4_s_SbltwrnTtTrns_condNStoQ,    (U1)(SBLTWRN_SEATTYPBIT_RS_ALL)  },
    { &u4_s_SbltwrnTtTrns_condNStoP,    (U1)(SBLTWRN_SEATTYPBIT_RS_ALL)  },
    { &u4_s_SbltwrnTtTrns_condNL,       (U1)(SBLTWRN_SEATTYPBIT_RS_ALL)  },
    { &u4_s_SbltwrnTtTrns_condNS,       (U1)(SBLTWRN_SEATTYPBIT_RS_ALL)  },
    { &u4_s_SbltwrnTtTrns_condNStoO,    (U1)(SBLTWRN_SEATTYPBIT_RS_NOSN) },
    { &u4_s_SbltwrnTtTrns_condNA,       (U1)(SBLTWRN_SEATTYPBIT_RS_ALL)  }
};

static ST_SBLTWRN_TT_STM const fp_sp_u4_SBLTWRN_TTSTM_CND_O[] = {
    /* fp_u4_STM */                     /* u1_TYPMSK */
    { &u4_s_SbltwrnTtTrns_condOtoPQ,    (U1)(SBLTWRN_SEATTYPBIT_RS_ALL)  },
    { &u4_s_SbltwrnTtTrns_condOR,       (U1)(SBLTWRN_SEATTYPBIT_RS_ALL)  },
    { &u4_s_SbltwrnTtTrns_condOL,       (U1)(SBLTWRN_SEATTYPBIT_RS_ALL)  },
    { &u4_s_SbltwrnTtTrns_condOS,       (U1)(SBLTWRN_SEATTYPBIT_RS_ALL)  },
    { &u4_s_SbltwrnTtTrns_condON,       (U1)(SBLTWRN_SEATTYPBIT_RS_ALL)  },
    { &u4_s_SbltwrnTtTrns_condOA,       (U1)(SBLTWRN_SEATTYPBIT_RS_ALL)  }
};

static ST_SBLTWRN_TT_STM const fp_sp_u4_SBLTWRN_TTSTM_CND_P[] = {
    /* fp_u4_STM */                     /* u1_TYPMSK */
    { &u4_s_SbltwrnTtTrns_condPQ,       (U1)(SBLTWRN_SEATTYPBIT_RS_ALL)  },
    { &u4_s_SbltwrnTtTrns_condPL,       (U1)(SBLTWRN_SEATTYPBIT_RS_ALL)  },
    { &u4_s_SbltwrnTtTrns_condPQtoN,    (U1)(SBLTWRN_SEATTYPBIT_RS_ALL)  },
    { &u4_s_SbltwrnTtTrns_condPA,       (U1)(SBLTWRN_SEATTYPBIT_RS_ALL)  }
};

static ST_SBLTWRN_TT_STM const fp_sp_u4_SBLTWRN_TTSTM_CND_Q[] = {
    /* fp_u4_STM */                     /* u1_TYPMSK */
    { &u4_s_SbltwrnTtTrns_condQR,       (U1)(SBLTWRN_SEATTYPBIT_RS_ALL)  },
    { &u4_s_SbltwrnTtTrns_condQL,       (U1)(SBLTWRN_SEATTYPBIT_RS_ALL)  },
    { &u4_s_SbltwrnTtTrns_condPQtoN,    (U1)(SBLTWRN_SEATTYPBIT_RS_ALL)  },
    { &u4_s_SbltwrnTtTrns_condQO,       (U1)(SBLTWRN_SEATTYPBIT_RS_NOSN) },
    { &u4_s_SbltwrnTtTrns_condQA,       (U1)(SBLTWRN_SEATTYPBIT_RS_ALL)  }
};

static ST_SBLTWRN_TT_STM const fp_sp_u4_SBLTWRN_TTSTM_CND_R[] = {
    /* fp_u4_STM */                     /* u1_TYPMSK */
    { &u4_s_SbltwrnTtTrns_condRL,       (U1)(SBLTWRN_SEATTYPBIT_RS_ALL)  },
    { &u4_s_SbltwrnTtTrns_condRO,       (U1)(SBLTWRN_SEATTYPBIT_RS_NOSN) },
    { &u4_s_SbltwrnTtTrns_condRA,       (U1)(SBLTWRN_SEATTYPBIT_RS_ALL)  }
};

static ST_SBLTWRN_TT_STM const fp_sp_u4_SBLTWRN_TTSTM_CND_S[] = {
    /* fp_u4_STM */                     /* u1_TYPMSK */
    { &u4_s_SbltwrnTtTrns_condNStoQ,    (U1)(SBLTWRN_SEATTYPBIT_RS_ALL)  },
    { &u4_s_SbltwrnTtTrns_condNStoP,    (U1)(SBLTWRN_SEATTYPBIT_RS_ALL)  },
    { &u4_s_SbltwrnTtTrns_condSL,       (U1)(SBLTWRN_SEATTYPBIT_RS_ALL)  },
    { &u4_s_SbltwrnTtTrns_condSN,       (U1)(SBLTWRN_SEATTYPBIT_RS_ALL)  },
    { &u4_s_SbltwrnTtTrns_condNStoO,    (U1)(SBLTWRN_SEATTYPBIT_RS_NOSN) },
    { &u4_s_SbltwrnTtTrns_condSA,       (U1)(SBLTWRN_SEATTYPBIT_RS_ALL)  }
};

static const ST_SBLTWRN_TTTYP st_sp_SBLTWRN_TTTYP[SBLTWRN_NUM_TTSTS] = {
    {&fp_sp_u4_SBLTWRN_TTSTM_CND_A[0],  sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_A) / sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_A[0])},
    {&fp_sp_u4_SBLTWRN_TTSTM_CND_B[0],  sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_B) / sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_B[0])},
    {&fp_sp_u4_SBLTWRN_TTSTM_CND_C[0],  sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_C) / sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_C[0])},
    {&fp_sp_u4_SBLTWRN_TTSTM_CND_D[0],  sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_D) / sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_D[0])},
    {&fp_sp_u4_SBLTWRN_TTSTM_CND_E[0],  sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_E) / sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_E[0])},
    {&fp_sp_u4_SBLTWRN_TTSTM_CND_F[0],  sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_F) / sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_F[0])},
    {&fp_sp_u4_SBLTWRN_TTSTM_CND_G[0],  sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_G) / sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_G[0])},
    {&fp_sp_u4_SBLTWRN_TTSTM_CND_H[0],  sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_H) / sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_H[0])},
    {&fp_sp_u4_SBLTWRN_TTSTM_CND_I[0],  sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_I) / sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_I[0])},
    {&fp_sp_u4_SBLTWRN_TTSTM_CND_J[0],  sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_J) / sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_J[0])},
    {&fp_sp_u4_SBLTWRN_TTSTM_CND_K[0],  sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_K) / sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_K[0])},
    {&fp_sp_u4_SBLTWRN_TTSTM_CND_L[0],  sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_L) / sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_L[0])},
    {&fp_sp_u4_SBLTWRN_TTSTM_CND_N[0],  sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_N) / sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_N[0])},
    {&fp_sp_u4_SBLTWRN_TTSTM_CND_P[0],  sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_P) / sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_P[0])},
    {&fp_sp_u4_SBLTWRN_TTSTM_CND_Q[0],  sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_Q) / sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_Q[0])},
    {&fp_sp_u4_SBLTWRN_TTSTM_CND_R[0],  sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_R) / sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_R[0])},
    {&fp_sp_u4_SBLTWRN_TTSTM_CND_R[0],  sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_R) / sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_R[0])},
    {&fp_sp_u4_SBLTWRN_TTSTM_CND_S[0],  sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_S) / sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_S[0])},
    {&fp_sp_u4_SBLTWRN_TTSTM_CND_O[0],  sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_O) / sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_O[0])}
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* void            vd_g_SbltwrnInit(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_SbltwrnInit(void)
{
    U4  u4_t_loop;

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)SBLTWRN_NUM_ALLSEAT; u4_t_loop++) {
        vd_s_SbltwrnInitChmsts(&st_sp_sbltwrn_chmsts[u4_t_loop]);
        vd_s_SbltwrnInitTtsts(&st_sp_sbltwrn_ttsts[u4_t_loop]);
    }
    
    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)SBLTWRN_NUM_3ROWSEAT; u4_t_loop++) {
        u1_sp_sbltwrn_sbr_oldsts[u4_t_loop] = (U1)SBLTWRN_CHMSTS_OFF;
    }
    
    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)SBLTWRN_SBRBIT_IDX_ALL; u4_t_loop++) {
        u1_sp_sbltwrn_sbrbit[u4_t_loop] = (U1)0U;
    }
    
    u2_s_sbltwrn_igontm         = (U2)0U;
    u2_s_sbltwrn_bkledgtmr      = (U2)U2_MAX;
    u2_s_sbltwrn_unbklflg       = (U2)0U;
    u2_s_sbltwrn_failsts        = (U2)0U;
    u1_s_sbltwrn_precfg         = (U1)0U;

    vd_g_SbltwrnInit_FM();
    vd_g_SbltVclstsInit();
    vd_g_SbltSeatInfoInit();
    vd_g_SbltwrnGetCalibSupd();
}

/*===================================================================================================================================*/
/* void            vd_g_SbltwrnMainTask(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_SbltwrnMainTask(void)
{
    U1                  u1_t_dsttyp;

    u1_t_dsttyp = u1_g_SbltwrnDestCfg();
    if (u1_t_dsttyp >= (U1)SBLTWRN_NUM_DEST) {
        u1_t_dsttyp = (U1)SBLTWRN_DEST_US_TS;
    }
    vd_s_SbltwrnVarChgChk(u1_t_dsttyp);
    vd_g_SbltwrnGetCalibSupd();

    switch (u1_t_dsttyp) {
        case (U1)SBLTWRN_DEST_FM_SB:
        case (U1)SBLTWRN_DEST_FM_LS:
        case (U1)SBLTWRN_DEST_FM_TS:
            vd_g_SbltwrnTrans_FM(u1_t_dsttyp);
            break;
        default:
            vd_s_SbltwrnTrans(u1_t_dsttyp);
            break;
    }
}

/*===================================================================================================================================*/
/* static  void            vd_s_SbltwrnTrans(const U1 u1_a_DSTTYP)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void            vd_s_SbltwrnTrans(const U1 u1_a_DSTTYP)
{
    ST_SBLTWRN_VCLST    st_t_vclsts;
    U1                  u1_t_igon;
    U1                  u1_t_dsttyp;
    U1                  u1_tp_msgsts[SBLTWRN_NUM_MSG];

    u1_t_igon = u1_g_VehopemdIgnOn();
    
    if (u1_t_igon == (U1)TRUE) {
        vd_g_SbltwrnTmcnt(&u2_s_sbltwrn_igontm);
    } else {
        u2_s_sbltwrn_igontm = (U2)0U;
    }

    u1_t_dsttyp = u1_a_DSTTYP;

    vd_g_MemfillU1(&u1_tp_msgsts[0], (U1)SBLTWRN_UNKNOWN, (U4)SBLTWRN_NUM_MSG);
    vd_g_SbltwrnMsgsts(u1_t_igon, &u1_tp_msgsts[0]);

    st_t_vclsts.u2_igontm       = u2_s_sbltwrn_igontm;
    st_t_vclsts.u2_bkledgtmr    = u2_s_sbltwrn_bkledgtmr;
    st_t_vclsts.stp_wrnprm      = st_gp_SBLTWRN_WRNPRM[u1_t_dsttyp];
    st_t_vclsts.stp_vclprm      = &st_gp_SBLTWRN_VCLPRM[u1_t_dsttyp];
    st_t_vclsts.u4_vclsts       = u4_g_SbltVclsts(u2_s_sbltwrn_igontm, &u1_tp_msgsts[0], &st_t_vclsts.stp_vclprm->u2p_spd[0]);

    vd_g_MemfillU1(&st_t_vclsts.u1p_bklsts[0], (U1)0U, (U4)SBLTWRN_NUM_ALLSEAT);
    vd_g_SbltwrnSeatsts(st_t_vclsts.u4_vclsts, &u1_tp_msgsts[0], &st_t_vclsts.u1p_bklsts[0]);
    vd_s_SbltwrnBklEdgChk(&st_t_vclsts);

    vd_s_SbltwrnStm(&st_t_vclsts);

    vd_s_SbltwrnUnbkleFlgPostChk();
    u2_s_sbltwrn_bkledgtmr = st_t_vclsts.u2_bkledgtmr;
    vd_s_SbltwrnSbrBzrChgDet();
}

/*===================================================================================================================================*/
/* U1              u1_g_SbltwrnChmStsBySeat(const U1 u1_a_SEATID)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_SbltwrnChmStsBySeat(const U1 u1_a_SEATID)
{
    U1  u1_t_chmsts;

    if (u1_a_SEATID < (U1)SBLTWRN_NUM_ALLSEAT) {
        u1_t_chmsts = st_sp_sbltwrn_chmsts[u1_a_SEATID].u1_ctlsts;
    } else {
        u1_t_chmsts = (U1)SBLTWRN_CHMSTS_OFF;
    }

    return (u1_t_chmsts);
}

/*==================================================================================================================================*/
/* U1              u1_g_SbltwrnDiagEvCapt(const U1 u1_a_ODO_UPDT, U4 * u4_ap_ss)                                                    */
/* ---------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:      -                                                                                                               */
/*  Return:         -                                                                                                               */
/*==================================================================================================================================*/
U1              u1_g_SbltwrnDiagEvCapt(const U1 u1_a_ODO_UPDT, U4 * u4_ap_ss)
{
    U1          u1_t_capt;
    U1          u1_t_dsttyp;
    U1          u1_tp_sbrbit[SBLTWRN_SBRBIT_IDX_ALL];

    u1_t_dsttyp = u1_g_SbltwrnDestCfg();
    if (u1_t_dsttyp >= (U1)SBLTWRN_NUM_DEST) {
        u1_t_dsttyp = (U1)SBLTWRN_DEST_US_SB;
    }

    u1_t_capt = (U1)FALSE;
    switch (u1_t_dsttyp) {
        case (U1)SBLTWRN_DEST_FM_SB:
        case (U1)SBLTWRN_DEST_FM_LS:
        case (U1)SBLTWRN_DEST_FM_TS:
            vd_g_GetSbltwrnSbrbit(&u1_tp_sbrbit[0]); 
            if ((u1_tp_sbrbit[SBLTWRN_SBRBIT_IDX0] != (U1)0U) ||
                (u1_tp_sbrbit[SBLTWRN_SBRBIT_IDX1] != (U1)0U)) {
                u4_ap_ss[SBLTWRN_SBRBIT_IDX0] = (U4)u1_tp_sbrbit[SBLTWRN_SBRBIT_IDX0] & (U4)SBLTWRN_DRV_SEAT_BIT_IDX_ALL;
                u4_ap_ss[SBLTWRN_SBRBIT_IDX1] = (U4)u1_tp_sbrbit[SBLTWRN_SBRBIT_IDX1] & (U4)SBLTWRN_R3L_SEAT_BIT_IDX1;
                u1_tp_sbrbit[SBLTWRN_SBRBIT_IDX0] = (U1)0U;
                u1_tp_sbrbit[SBLTWRN_SBRBIT_IDX1] = (U1)0U;
                vd_g_SetSbltwrnSbrbit(&u1_tp_sbrbit[0]); 
                u1_t_capt = (U1)TRUE;
            }
            break;
        default:
            if ((u1_sp_sbltwrn_sbrbit[SBLTWRN_SBRBIT_IDX0] != (U1)0U) ||
                (u1_sp_sbltwrn_sbrbit[SBLTWRN_SBRBIT_IDX1] != (U1)0U)) {
                u4_ap_ss[SBLTWRN_SBRBIT_IDX0] = (U4)u1_sp_sbltwrn_sbrbit[SBLTWRN_SBRBIT_IDX0] & (U4)SBLTWRN_DRV_SEAT_BIT_IDX_ALL;
                u4_ap_ss[SBLTWRN_SBRBIT_IDX1] = (U4)u1_sp_sbltwrn_sbrbit[SBLTWRN_SBRBIT_IDX1] & (U4)SBLTWRN_R3L_SEAT_BIT_IDX1;
                u1_sp_sbltwrn_sbrbit[SBLTWRN_SBRBIT_IDX0] = (U1)0U;
                u1_sp_sbltwrn_sbrbit[SBLTWRN_SBRBIT_IDX1] = (U1)0U;
                u1_t_capt = (U1)TRUE;
            }
            break;
    }
    return(u1_t_capt);
}

/*===================================================================================================================================*/
/* U4              u4_g_SbltwrnTtSts(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4              u4_g_SbltwrnTtSts(void)
{
    U4  u4_t_seat;
    U4  u4_t_ttstsbit;

    u4_t_ttstsbit = (U4)0U;
    for (u4_t_seat = (U4)0U; u4_t_seat < (U4)SBLTWRN_NUM_ALLSEAT; u4_t_seat++) {
        u4_t_ttstsbit |= ((U4)1U << st_sp_sbltwrn_ttsts[u4_t_seat].u1_ctlsts);
    }

    return (u4_t_ttstsbit);
}

/*===================================================================================================================================*/
/* U1              u1_g_SbltwrnTtstsBySeat(const U1 u1_a_SEATID)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_SbltwrnTtStsBySeat(const U1 u1_a_SEATID)
{
    U1  u1_t_ttsts;

    if (u1_a_SEATID < (U1)SBLTWRN_NUM_ALLSEAT) {
        u1_t_ttsts = st_sp_sbltwrn_ttsts[u1_a_SEATID].u1_ctlsts;
    } else {
        u1_t_ttsts = (U1)SBLTWRN_TTSTS_OFF;
    }

    return (u1_t_ttsts);
}

/*===================================================================================================================================*/
/* static  void    vd_s_SbltwrnVarChgChk(const U1 u1_a_DSTTYP)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_SbltwrnVarChgChk(const U1 u1_a_DSTTYP)
{
    if (u1_a_DSTTYP != u1_s_sbltwrn_precfg) {
        vd_g_SbltwrnInit();
        vd_g_SbltsyncInit();
    }

    u1_s_sbltwrn_precfg = u1_a_DSTTYP;
}

/*===================================================================================================================================*/
/*  Set/Clear unbuckle flag and Increment/Reset a buckle edge timer                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_SbltwrnBklEdgChk(ST_SBLTWRN_VCLST *stp_a_vclsts)
{
    U4  u4_t_loop;
    U1  u1_t_seattyp;
    U1  u1_t_dropn;

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)SBLTWRN_NUM_ALLSEAT; u4_t_loop++) {
        u1_t_seattyp = u1_g_SbltwrnSeatTyp((U1)u4_t_loop);
        u1_t_dropn   = u1_g_SbltwrnDrchk(stp_a_vclsts->u4_vclsts, u1_t_seattyp, (U1)FALSE);
        if ((stp_a_vclsts->u1p_bklsts[u4_t_loop] & (U1)SBLTWRN_BKLSTS_UNBCKLEDG) != (U1)0U) {
            /* Set unbkleflg */
            u2_s_sbltwrn_unbklflg |= (U2)((U2)1U << u4_t_loop);
        }
        if ((stp_a_vclsts->u2_igontm == (U2)0U) || ((u1_t_dropn == (U1)TRUE) && ((stp_a_vclsts->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_STP_OVER) == (U4)0U)) || 
        ((stp_a_vclsts->u1p_bklsts[u4_t_loop] & (U1)SBLTWRN_BKLSTS_UNBCKL) == (U1)0U)) {
            /* Clear unbkleflg */
            u2_s_sbltwrn_unbklflg &= ((U2)U2_MAX ^ (U2)((U2)1U << u4_t_loop));
        }

        /*                                                                      */
        /* Note: If a target seat is 'D/P' or 'Rr with seatsnsr' and unbuckled, */
        /*       the unbkleflg is set by sblt_seat.c and always turns on.       */
        /*                                                                      */
        if ((u2_s_sbltwrn_unbklflg & (U2)((U2)1U << u4_t_loop)) != (U2)0U) {
            stp_a_vclsts->u1p_bklsts[u4_t_loop] |= (U1)SBLTWRN_BKLSTS_UNBCKLFLG;
        }
        if (((stp_a_vclsts->stp_vclprm->u4_cmnopt & (U4)SBLTWRN_CMNOPT_TTBKLEDG_ENA) != (U4)0U) &&
            ((stp_a_vclsts->u1p_bklsts[u4_t_loop] & (U1)SBLTWRN_BKLSTS_BCKLEDG) != (U1)0U)) {
            stp_a_vclsts->u2_bkledgtmr = (U2)0U;
        }

        if ((stp_a_vclsts->u1p_bklsts[u4_t_loop] & (U1)SBLTWRN_BKLSTS_COMFAIL) != (U1)0U) {
            u2_s_sbltwrn_failsts |= (U2)((U2)1U << u4_t_loop);
        } else {
            if ((u2_s_sbltwrn_failsts & (U2)((U2)1U << u4_t_loop)) != (U2)0U) {
                stp_a_vclsts->u1p_bklsts[u4_t_loop] |= (U1)SBLTWRN_BKLSTS_FAILRSTEDG;
            }
            u2_s_sbltwrn_failsts &= ((U2)U2_MAX ^ (U2)((U2)1U << u4_t_loop));
        }
    }
    vd_g_SbltwrnTmcnt(&stp_a_vclsts->u2_bkledgtmr);
}

/*===================================================================================================================================*/
/* static  void    vd_s_SbltwrnUnbkleFlgPostChk(void)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_SbltwrnUnbkleFlgPostChk(void)
{
    U4  u4_t_loop;

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)SBLTWRN_NUM_ALLSEAT; u4_t_loop++) {
        if ((st_sp_sbltwrn_chmsts[u4_t_loop].u1_ctlsts == (U1)SBLTWRN_CHMSTS_L2CMP) &&
            ((st_sp_sbltwrn_ttsts[u4_t_loop].u1_ctlsts == (U1)SBLTWRN_TTSTS_RR_L2CMP_OFF) ||
             (st_sp_sbltwrn_ttsts[u4_t_loop].u1_ctlsts == (U1)SBLTWRN_TTSTS_RR_L2CMP_ON))) {

            /* Clear unbkleflg */
            u2_s_sbltwrn_unbklflg &= ((U2)U2_MAX ^ (U2)((U2)1U << u4_t_loop));
        }
    }
}

/*===================================================================================================================================*/
/* static  void    vd_s_SbltwrnStm(const ST_SBLTWRN_VCLST *stp_a_VCLSTS)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_SbltwrnStm(const ST_SBLTWRN_VCLST *stp_a_VCLSTS)
{
    vd_s_SbltwrnChimeStm(stp_a_VCLSTS);
    vd_s_SbltwrnTtStm(stp_a_VCLSTS);
}

/*===================================================================================================================================*/
/* static  void    vd_s_SbltwrnChimeStm(const ST_SBLTWRN_VCLST *stp_a_VCLSTS)                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_SbltwrnChimeStm(const ST_SBLTWRN_VCLST *stp_a_VCLSTS)
{
    U4  u4_t_seat;
    U4  u4_t_chmopt;
    U2  u2_t_sync_trgt;
    U1  u1_t_seattyp;
    U1  u1_tp_valid_chk[SBLTWRN_NUM_ALLSEAT];

    u2_t_sync_trgt = (U2)SBLTWRN_CHM_SYNCCND_CHK;
    for (u4_t_seat = (U4)0U; u4_t_seat < (U4)SBLTWRN_NUM_ALLSEAT; u4_t_seat++) {
        u1_t_seattyp = u1_g_SbltwrnSeatTyp((U1)u4_t_seat);
        u1_tp_valid_chk[u4_t_seat] = u1_g_SbltwrnChmStmVldChk((U1)u4_t_seat, u1_t_seattyp, stp_a_VCLSTS);
        if (u1_tp_valid_chk[u4_t_seat] == (U1)TRUE) {
            u4_t_chmopt = u4_s_SbltwrnChimeCnd((U1)u4_t_seat, u1_t_seattyp, stp_a_VCLSTS, (U2)0U);
            vd_s_SbltwrnChimeTimAct(&st_sp_sbltwrn_chmsts[u4_t_seat], u4_t_chmopt, (U1)FALSE);
            u2_t_sync_trgt |= (U2)((U2)1U << st_sp_sbltwrn_chmsts[u4_t_seat].u1_ctlsts);
        } else {
            vd_s_SbltwrnInitChmsts(&st_sp_sbltwrn_chmsts[u4_t_seat]);
        }
    }

    for (u4_t_seat = (U4)0U; u4_t_seat < (U4)SBLTWRN_NUM_ALLSEAT; u4_t_seat++) {
        u1_t_seattyp = u1_g_SbltwrnSeatTyp((U1)u4_t_seat);
        if (u1_tp_valid_chk[u4_t_seat] == (U1)TRUE) {
            u4_t_chmopt = u4_s_SbltwrnChimeCnd((U1)u4_t_seat, u1_t_seattyp, stp_a_VCLSTS, u2_t_sync_trgt);
            vd_s_SbltwrnChimeTimAct(&st_sp_sbltwrn_chmsts[u4_t_seat], u4_t_chmopt, (U1)TRUE);
        }
    }
}


/*===================================================================================================================================*/
/* static  void    vd_s_SbltwrnTtStm(const ST_SBLTWRN_VCLST *stp_a_VCLSTS)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_SbltwrnTtStm(const ST_SBLTWRN_VCLST *stp_a_VCLSTS)
{
    U4  u4_t_seat;
    U4  u4_t_ttopt;
    U4  u4_t_sync_trgt;
    U1  u1_t_seattyp;
    U1  u1_tp_valid_chk[SBLTWRN_NUM_ALLSEAT];

    u4_t_sync_trgt = (U4)SBLTWRN_TT_SYNCCND_CHK;
    for (u4_t_seat = (U4)0U; u4_t_seat < (U4)SBLTWRN_NUM_ALLSEAT; u4_t_seat++) {
        u1_t_seattyp = u1_g_SbltwrnSeatTyp((U1)u4_t_seat);
        u1_tp_valid_chk[u4_t_seat] = u1_s_SbltwrnTtStmVldChk((U1)u4_t_seat, u1_t_seattyp, stp_a_VCLSTS);
        if (u1_tp_valid_chk[u4_t_seat] == (U1)TRUE) {
            u4_t_ttopt = u4_s_SbltwrnTtStmCnd((U1)u4_t_seat, u1_t_seattyp, stp_a_VCLSTS, (U4)0U);
            vd_s_SbltwrnTtTimAct(&st_sp_sbltwrn_ttsts[u4_t_seat], stp_a_VCLSTS->u4_vclsts, u4_t_ttopt, u1_t_seattyp, (U1)FALSE);
            u4_t_sync_trgt |= ((U4)1U << st_sp_sbltwrn_ttsts[u4_t_seat].u1_ctlsts);
        }
    }

    for (u4_t_seat = (U4)0U; u4_t_seat < (U4)SBLTWRN_NUM_ALLSEAT; u4_t_seat++) {
        u1_t_seattyp = u1_g_SbltwrnSeatTyp((U1)u4_t_seat);
        if (u1_tp_valid_chk[u4_t_seat] == (U1)TRUE) {
            u4_t_ttopt = u4_s_SbltwrnTtStmCnd((U1)u4_t_seat, u1_t_seattyp, stp_a_VCLSTS, u4_t_sync_trgt);
            vd_s_SbltwrnTtTimAct(&st_sp_sbltwrn_ttsts[u4_t_seat], stp_a_VCLSTS->u4_vclsts, u4_t_ttopt, u1_t_seattyp, (U1)TRUE);
        }
    }
}

/*===================================================================================================================================*/
/* static  U1      u1_s_SbltwrnTtStmVldChk(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS)        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_SbltwrnTtStmVldChk(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS)
{
    U1  u1_t_valid;

    if ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_FAILRSTEDG) != (U1)0U) {
        vd_s_SbltwrnInitTtsts(&st_sp_sbltwrn_ttsts[u1_a_SEATID]);
    }

    if ((stp_a_VCLSTS->u2_igontm > (U2)0U) && (u1_a_SEATTYP != (U1)SBLTWRN_SEATTYP_UNDEF)) {
        if ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_COMFAIL) != (U1)0U) {
            /* Keep last state (Do not initialize tt status) */
            u1_t_valid = (U1)FALSE;
        } else {
            u1_t_valid = (U1)TRUE;
        }
    } else {
        u1_t_valid = (U1)FALSE;
        vd_s_SbltwrnInitTtsts(&st_sp_sbltwrn_ttsts[u1_a_SEATID]);
    }

    return (u1_t_valid);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtStmCnd(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtStmCnd(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    static const U4             u4_s_CTLSTS_MSK = (U4)0x000000FFU;
    const ST_SBLTWRN_TTTYP *    stp_t_tttyp;
    U4                          u4_t_act;
    U1                          u1_t_ctlsts;
    U4                          u4_t_loop;

    u1_t_ctlsts = st_sp_sbltwrn_ttsts[u1_a_SEATID].u1_ctlsts;
    if (u1_t_ctlsts >= (U1)SBLTWRN_NUM_TTSTS) {
        u1_t_ctlsts = (U1)SBLTWRN_TTSTS_OFF;
    }
    stp_t_tttyp = &st_sp_SBLTWRN_TTTYP[u1_t_ctlsts];

    u4_t_act = (U4)SBLTWRN_TTSTS_KEEP;
    for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)stp_t_tttyp->u1_NUM_TTTYP ; u4_t_loop++){
        if (((stp_t_tttyp->st_TTSTM[u4_t_loop].u1_TYPMSK) & (U1)((U1)1U << u1_a_SEATTYP)) != (U1)0U) {
            u4_t_act = (*(stp_t_tttyp->st_TTSTM[u4_t_loop].fp_u4_STM))(u1_a_SEATID, u1_a_SEATTYP, stp_a_VCLSTS, u4_a_SYNC_TRGT);
            u1_t_ctlsts = (U1)(u4_t_act & u4_s_CTLSTS_MSK);
            if (u1_t_ctlsts < (U1)SBLTWRN_NUM_TTSTS) {
                st_sp_sbltwrn_ttsts[u1_a_SEATID].u1_ctlsts = u1_t_ctlsts;
                break;
            }
        }
    }

    return (u4_t_act);
}

/*===================================================================================================================================*/
/* static  void    vd_s_SbltwrnTtTimAct(ST_SBLTWRN_TTST *stp_a_ttsts, const U4 u4_a_VCLSTS, U4 u4_a_ttopt, const U1 u1_a_SEATTYP, const U1 u1_a_CNT_UP) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_SbltwrnTtTimAct(ST_SBLTWRN_TTST *stp_a_ttsts, const U4 u4_a_VCLSTS, U4 u4_a_ttopt, const U1 u1_a_SEATTYP, const U1 u1_a_CNT_UP)
{
    static const U4 u4_s_CNTUP_OFST = (U4)8U;
    static const U4 u4_s_CNTSTP_OFST = (U4)11U;
    static const U4 u4_s_CNTCLR_OFST = (U4)14U;
    U4  u4_t_loop;
    U4  u4_t_act_bit;
    U1  u1_t_dropn;

    u1_t_dropn  = u1_g_SbltwrnDrchk(u4_a_VCLSTS, u1_a_SEATTYP, (U1)TRUE);

    if ((u1_t_dropn == (U1)TRUE) || ((u4_a_VCLSTS & (U4)SBLTWRN_VCLSTS_D_DR_OP) != (U4)0U) || ((u4_a_VCLSTS & (U4)SBLTWRN_VCLSTS_P_DR_OP) != (U4)0U)) {
        u4_a_ttopt |= (U4)SBLTWRN_TTOPT_DRTM_CNTCLR;
    }

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)SBLTWRN_NUM_TTTIMER; u4_t_loop++) {

        /* Set/Clear SBLTWRN_CHMFLG_CNT_xxx by SBLTWRN_CHMOPT_xxx_CNTUP/STP */
        u4_t_act_bit = ((U4)1U << (u4_t_loop + u4_s_CNTUP_OFST));
        /* The maximum value of u4_t_loop is 2. The value of u4_s_CNTUP_OFST is 8.          */
        /* so (u4_t_loop + u4_s_CNTUP_OFST) is always less than U4_MAX.                     */
        if ((u4_a_ttopt & u4_t_act_bit) != (U4)0U) {
            stp_a_ttsts->u1_flg |= (U1)((U1)1U << u4_t_loop);
        }

        u4_t_act_bit = ((U4)1U << (u4_t_loop + u4_s_CNTSTP_OFST));
        /* The maximum value of u4_t_loop is 2. The value of u4_s_CNTSTP_OFST is 11.        */
        /* so (u4_t_loop + u4_s_CNTSTP_OFST) is always less than U4_MAX.                    */
        if ((u4_a_ttopt & u4_t_act_bit) != (U4)0U) {
            stp_a_ttsts->u1_flg &= ((U1)U1_MAX ^ (U1)((U1)1U << u4_t_loop));
        }

        u4_t_act_bit = ((U4)1U << (u4_t_loop + u4_s_CNTCLR_OFST));
        /* The maximum value of u4_t_loop is 2. The value of u4_s_CNTCLR_OFST is 14.        */
        /* so (u4_t_loop + u4_s_CNTCLR_OFST) is always less than U4_MAX.                    */
        if ((u4_a_ttopt & u4_t_act_bit) != (U4)0U) {
            stp_a_ttsts->u2p_timer[u4_t_loop] = (U2)0U;
        }

        if (((stp_a_ttsts->u1_flg & (U1)((U1)1U << u4_t_loop)) != (U1)0U) && (u1_a_CNT_UP == (U1)TRUE)) {
            vd_g_SbltwrnTmcnt(&stp_a_ttsts->u2p_timer[u4_t_loop]);
        }
    }
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnChimeCnd(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChimeCnd(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    static const U4 u4_s_CTLSTS_MSK = (U4)0x000000FFU;
    const ST_SBLTWRN_CHMTYP * stp_t_chm_stm;
    U4      u4_t_act;
    U4      u4_t_chmopt;
    U1      u1_t_ctlsts;
    U1      u1_t_gpflg_pre;
    U4      u4_t_loop;

    u1_t_ctlsts = st_sp_sbltwrn_chmsts[u1_a_SEATID].u1_ctlsts;
    if (u1_t_ctlsts >= (U1)SBLTWRN_NUM_CHMSTS) {
        u1_t_ctlsts = (U1)SBLTWRN_CHMSTS_OFF;
    }
    stp_t_chm_stm  = &st_sp_SBLTWRN_CHMSTM[u1_t_ctlsts];
    u1_t_gpflg_pre = st_sp_sbltwrn_chmsts[u1_a_SEATID].u1_flg & (U1)SBLTWRN_CHMFLG_GPTIM_CTL;

    vd_s_SbltwrnChimeFlgPreChk(stp_a_VCLSTS, &st_sp_sbltwrn_chmsts[u1_a_SEATID], u1_a_SEATID);

    u4_t_act = (U4)SBLTWRN_CHMSTS_KEEP;
    for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)(stp_t_chm_stm->u1_NUM_CHMTYP) ; u4_t_loop++){
        u4_t_act = (stp_t_chm_stm->fp_u4_CHMTYP[u4_t_loop])(u1_a_SEATID, u1_a_SEATTYP, stp_a_VCLSTS, u2_a_SYNC_TRGT);
        u1_t_ctlsts = (U1)(u4_t_act & u4_s_CTLSTS_MSK); 
        if (u1_t_ctlsts < (U1)SBLTWRN_NUM_CHMSTS) {
            st_sp_sbltwrn_chmsts[u1_a_SEATID].u1_ctlsts = u1_t_ctlsts;
            break;
        }
    }

    u4_t_chmopt = u4_t_act & (U4)SBLTWRN_CHMOPT_MSK;
    u4_t_chmopt |= u4_s_SbltwrnChimeFlgPostChk(stp_a_VCLSTS, u1_a_SEATID, u4_t_chmopt, u1_t_gpflg_pre);

    return (u4_t_chmopt);
}

/*===================================================================================================================================*/
/* static  void    vd_s_SbltwrnChimeFlgPreChk(const ST_SBLTWRN_VCLST *stp_a_VCLSTS, ST_SBLTWRN_CHMST *stp_a_chmsts, const U1 u1_a_SEATID) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_SbltwrnChimeFlgPreChk(const ST_SBLTWRN_VCLST *stp_a_VCLSTS, ST_SBLTWRN_CHMST *stp_a_chmsts, const U1 u1_a_SEATID)
{
    static const U1 u1_s_CNDSFT         = (U1)8U;
/*  static const U1 u1_s_CND_DOOR       = (U1)0x01U; */ /* Door open */
    static const U1 u1_s_CND_UNBKL      = (U1)0x02U;    /* Unbuckle flag = 1 */
    static const U1 u1_s_CND_PARK       = (U1)0x08U;    /* Parking */
    static const U1 u1_s_CND_SSPND      = (U1)0x10U;    /* Warning Suspend Flag = 1 */
    static const U1 u1_s_CND_LWSPOVR    = (U1)0x20U;    /* over Low speed */
    static const U1 u1_s_CND_SFTR_ON    = (U1)0x40U;    /* Shift in R */
    static const U2 u2_s_MSK_SSPND_CLR  = (U2)0x0209U;  /* NOT_UNBKL, PARK, DOOR (OR condition) */
    static const U2 u2_s_MSK_GPTMR_SET  = (U2)0x5022U;  /* NOT_SFTR, LWSP, UNBKL, NOT_SSPND (AND condition) */
    static const U2 u2_s_MSK_GPTMR_CLR  = (U2)0x0249U;  /* NOT_UNBKL, PARK, DOOR, SFTR (OR condition) */
    U2  u2_t_cond_chk;
    U2  u2_t_gp_tim;
    U1  u1_t_cond;
    U1  u1_t_seattyp;

    u1_t_seattyp = u1_g_SbltwrnSeatTyp(u1_a_SEATID);
    u1_t_cond    = u1_g_SbltwrnDrchk(stp_a_VCLSTS->u4_vclsts, u1_t_seattyp, (U1)TRUE);
    u2_t_gp_tim  = stp_a_VCLSTS->stp_wrnprm[u1_t_seattyp].u2p_tim[SBLTWRN_TIM_GP];

    if ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_STP_OVER) != (U4)0U) {
        u1_t_cond = (U1)FALSE;
    }
    if ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKLFLG) != (U1)0U) {
        u1_t_cond |= u1_s_CND_UNBKL;
    }
    if (((stp_a_VCLSTS->stp_wrnprm[u1_t_seattyp].u4_ctlopt & (U4)SBLTWRN_CTLOPT_PRKWRN) == (U4)0U) && ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_PARK) != (U4)0U)) {
        u1_t_cond |= u1_s_CND_PARK;
    }
    if ((stp_a_chmsts->u1_flg & (U1)(SBLTWRN_CHMFLG_SSPND_GPLV1 | SBLTWRN_CHMFLG_SSPND_LV2)) != (U1)0U) {
        u1_t_cond |= u1_s_CND_SSPND;
    }
    if ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_LOW) != (U4)0U) {
        u1_t_cond |= u1_s_CND_LWSPOVR;
    }
    if ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SHIFT_R) != (U4)0U) {
        u1_t_cond |= u1_s_CND_SFTR_ON;
    }
    
    u2_t_cond_chk = ((U2)(((U2)u1_t_cond ^ (U2)U1_MAX) << u1_s_CNDSFT) | (U2)u1_t_cond);

    if ((u2_t_cond_chk & u2_s_MSK_SSPND_CLR) != (U2)0U) {
        stp_a_chmsts->u1_flg &= (U1)(~(SBLTWRN_CHMFLG_SSPND_GPLV1 | SBLTWRN_CHMFLG_SSPND_LV2));
    }
    if ((u2_t_gp_tim > (U2)0U) && ((u2_t_cond_chk & u2_s_MSK_GPTMR_SET) == u2_s_MSK_GPTMR_SET)) {
        stp_a_chmsts->u1_flg |= (U1)SBLTWRN_CHMFLG_GPTIM_CTL;
    }
    if ((u2_t_cond_chk & u2_s_MSK_GPTMR_CLR) != (U2)0U) {
        stp_a_chmsts->u1_flg &= (U1)(~SBLTWRN_CHMFLG_GPTIM_CTL);
    }
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnChimeFlgPostChk(const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U1 u1_a_SEATID, const U4 u4_a_CHMOPT, const U1 u1_a_GPFLG_PREV) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChimeFlgPostChk(const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U1 u1_a_SEATID, const U4 u4_a_CHMOPT, const U1 u1_a_GPFLG_PREV)
{
    U4  u4_t_chmopt;

    /* Set GP timer cnt-up flag */
    if ((u4_a_CHMOPT & (U4)SBLTWRN_CHMOPT_GPTMRFLG_SET) != (U4)0U) {
        st_sp_sbltwrn_chmsts[u1_a_SEATID].u1_flg |= (U1)SBLTWRN_CHMFLG_GPTIM_CTL;
    }

    /* Clert GP timer cnt-up flag */
    if ((u4_a_CHMOPT & (U4)SBLTWRN_CHMOPT_GPTMRFLG_CLR) != (U4)0U) {
        st_sp_sbltwrn_chmsts[u1_a_SEATID].u1_flg &= (U1)(~SBLTWRN_CHMFLG_GPTIM_CTL);
    }

    /* Set GPLV1_Suspend flag */
    if ((u4_a_CHMOPT & (U4)SBLTWRN_CHMOPT_GPLV1_SSPND_SET) != (U4)0U) {
        st_sp_sbltwrn_chmsts[u1_a_SEATID].u1_flg |= (U1)SBLTWRN_CHMFLG_SSPND_GPLV1;
    }

    /* Clear GPLV1_Suspend flag */
    if ((u4_a_CHMOPT & (U4)SBLTWRN_CHMOPT_GPLV1_SSPND_CLR) != (U4)0U) {
        st_sp_sbltwrn_chmsts[u1_a_SEATID].u1_flg &= (U1)(~SBLTWRN_CHMFLG_SSPND_GPLV1);
    }

    /* Set Lv2 Suspend flag */
    if ((u4_a_CHMOPT & (U4)SBLTWRN_CHMOPT_LV2_SSPND_SET) != (U4)0U) {
        st_sp_sbltwrn_chmsts[u1_a_SEATID].u1_flg |= (U1)SBLTWRN_CHMFLG_SSPND_LV2;
    }

    /* Clear Lv2 Suspend flag */
    if ((u4_a_CHMOPT & (U4)SBLTWRN_CHMOPT_LV2_SSPND_CLR) != (U4)0U) {
        st_sp_sbltwrn_chmsts[u1_a_SEATID].u1_flg &= (U1)(~SBLTWRN_CHMFLG_SSPND_LV2);
    }

    u4_t_chmopt = (U4)0U;
    /* When on-edge detected, initiates GP timer and starts counting */
    if ((u1_a_GPFLG_PREV == (U1)0U) && ((st_sp_sbltwrn_chmsts[u1_a_SEATID].u1_flg & (U1)SBLTWRN_CHMFLG_GPTIM_CTL) != (U1)0U)) {
        u4_t_chmopt = (U4)(SBLTWRN_CHMOPT_GPTM_CNTCLR | SBLTWRN_CHMOPT_GPTM_CNTUP);
    }

    /* When the flag is not set, initiates GP timer and stops counting */
    if ((st_sp_sbltwrn_chmsts[u1_a_SEATID].u1_flg & (U1)SBLTWRN_CHMFLG_GPTIM_CTL) == (U1)0U) {
        u4_t_chmopt = (U4)(SBLTWRN_CHMOPT_GPTM_CNTCLR | SBLTWRN_CHMOPT_GPTM_CNTSTP);
    }
    return (u4_t_chmopt);
}

/*===================================================================================================================================*/
/* static  void    vd_s_SbltwrnChimeTimAct(ST_SBLTWRN_CHMST *stp_a_chmsts, const U4 u4_a_CHMOPT, const U1 u1_a_CNT_UP)               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_SbltwrnChimeTimAct(ST_SBLTWRN_CHMST *stp_a_chmsts, const U4 u4_a_CHMOPT, const U1 u1_a_CNT_UP)
{
    static const U4 u4_s_CNTUP_OFST  = (U4)8U;
    static const U4 u4_s_CNTSTP_OFST = (U4)12U;
    static const U4 u4_s_CNTCLR_OFST = (U4)16U;
    U4  u4_t_loop;
    U4  u4_t_act_bit;


    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)SBLTWRN_NUM_CHMTIMER; u4_t_loop++) {

        /* Set/Clear SBLTWRN_CHMFLG_CNT_xxx by SBLTWRN_CHMOPT_xxx_CNTUP/STP */
        u4_t_act_bit = ((U4)1U << (u4_t_loop + u4_s_CNTUP_OFST));
        /* The maximum value of u4_t_loop is 3. The value of u4_s_CNTUP_OFST is 8.          */
        /* so (u4_t_loop + u4_s_CNTUP_OFST) is always less than U4_MAX.                     */
        if ((u4_a_CHMOPT & u4_t_act_bit) != (U4)0U) {
            stp_a_chmsts->u1_flg |= (U1)((U1)1U << u4_t_loop);
        }

        u4_t_act_bit = ((U4)1U << (u4_t_loop + u4_s_CNTSTP_OFST));
        /* The maximum value of u4_t_loop is 3. The value of u4_s_CNTSTP_OFST is 12.        */
        /* so (u4_t_loop + u4_s_CNTSTP_OFST) is always less than U4_MAX.                    */
        if ((u4_a_CHMOPT & u4_t_act_bit) != (U4)0U) {
            stp_a_chmsts->u1_flg &= ((U1)U1_MAX ^ (U1)((U1)1U << u4_t_loop));
        }

        u4_t_act_bit = ((U4)1U << (u4_t_loop + u4_s_CNTCLR_OFST));
        /* The maximum value of u4_t_loop is 3. The value of u4_s_CNTCLR_OFST is 16.        */
        /* so (u4_t_loop + u4_s_CNTCLR_OFST) is always less than U4_MAX.                    */
        if ((u4_a_CHMOPT & u4_t_act_bit) != (U4)0U) {
            stp_a_chmsts->u2p_timer[u4_t_loop] = (U2)0U;
        }

        if (((stp_a_chmsts->u1_flg & (U1)((U1)1U << u4_t_loop)) != (U1)0U) && (u1_a_CNT_UP == (U1)TRUE)) {
            vd_g_SbltwrnTmcnt(&stp_a_chmsts->u2p_timer[u4_t_loop]);
        }
    }
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnChmTrns_condAB(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChmTrns_condAB(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    static const U2 u2_s_FIRST_IG_ON = (U2)1U;
    U4              u4_t_cond;

    if ((stp_a_VCLSTS->u2_igontm == u2_s_FIRST_IG_ON) && (stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_LGLST] != (U2)0U)) {
        u4_t_cond = (U4)(SBLTWRN_CHMOPT_LGLTM_CNTCLR | SBLTWRN_CHMOPT_LGLTM_CNTUP | SBLTWRN_CHMSTS_LGLPR);
    } else {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnChmTrns_condAF(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChmTrns_condAF(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    static const    U1  u1_sp_JDG_TBL[SBLTWRN_NUM_SEATTYP] = {
        (U1)0x00U,      /* Undefined */
        (U1)0xC0U,      /* D-Seat    */
        (U1)0xC0U,      /* P-Seat    */
        (U1)0xECU,      /* R-Seat (with sensor) */
        (U1)0xECU       /* R-Seat (w/o  sensor) */
    };
    U4                  u4_t_cond;
    U1                  u1_t_cnd_chk;
    U1                  u1_t_cnd_bit;

    u1_t_cnd_chk = u1_s_SbltwrnChmTrns_GptmChk(u1_a_SEATID, u1_a_SEATTYP, stp_a_VCLSTS, (U2)0x0000U);
    u1_t_cnd_bit = (U1)(1U << u1_t_cnd_chk);

    u4_t_cond    = (U4)(SBLTWRN_CHMOPT_LV1TM_CNTCLR | SBLTWRN_CHMOPT_LV1TM_CNTUP);
    if (
        ((u1_t_cnd_bit & u1_sp_JDG_TBL[u1_a_SEATTYP]) != (U1)0U)                            &&   /* GP condition is true */
        ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SHIFT_R) == (U4)0U)                  &&   /* Shift is NOT in R */
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKLFLG) != (U1)0U)       /* unbuckled */
        ) {
        u4_t_cond |= (U4)(SBLTWRN_CHMSTS_UNBKNT | SBLTWRN_CHMOPT_GPLV1_SSPND_CLR | SBLTWRN_CHMOPT_LV2_SSPND_CLR);
    } else {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnChmTrns_condAH(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChmTrns_condAH(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    static const    U2  u2_sp_JDG_TBL[SBLTWRN_NUM_SEATTYP] = {
        (U2)0x0000U,      /* Undefined */
        (U2)0xECACU,      /* D-Seat    */
        (U2)0xECACU,      /* P-Seat    */
        (U2)0x0000U,      /* R-Seat (with sensor) */
        (U2)0x0000U       /* R-Seat (w/o  sensor) */
    };
    U4  u4_t_cond;
    U2  u2_t_cnd_idx;
    U1  u1_t_cnd_sft;

    u1_t_cnd_sft = u1_s_SbltwrnChmTrns_GptmChk(u1_a_SEATID, u1_a_SEATTYP, stp_a_VCLSTS, (u2_a_SYNC_TRGT & (U2)((U2)1U << SBLTWRN_CHMSTS_LV1)));
    u2_t_cnd_idx = (U2)((U2)1U << u1_t_cnd_sft);

    if (
        ((u2_t_cnd_idx & u2_sp_JDG_TBL[u1_a_SEATTYP]) != (U2)0U)            &&                      /* GP / Other-Seat / Speed / GP-Timer Condition Check */
        ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SHIFT_R) == (U4)0U)  &&                      /* not shift R */
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKLFLG) != (U1)0U)          /* unbuckled */
        ) {
        u4_t_cond = (U4)(SBLTWRN_CHMSTS_LV1 | SBLTWRN_CHMOPT_LV1TM_CNTCLR | SBLTWRN_CHMOPT_LV1TM_CNTUP | SBLTWRN_CHMOPT_GPLV1_SSPND_CLR | SBLTWRN_CHMOPT_GPTMRFLG_CLR);
    } else {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnChmTrns_condAI(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChmTrns_condAI(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    U4      u4_t_cond;
    U4      u4_t_spdmsk;
    U1      u1_t_sspnd_cnd;

    u4_t_spdmsk = (U4)SBLTWRN_VCLSTS_SPD_RUN;
    if ((st_sp_sbltwrn_chmsts[u1_a_SEATID].u1_flg & (U1)SBLTWRN_CHMFLG_SSPND_LV2) != (U1)0U) {
        u4_t_spdmsk |= (U4)SBLTWRN_VCLSTS_SPD_RSM;
        u1_t_sspnd_cnd = (U1)TRUE;
    } else {
        if ((u2_a_SYNC_TRGT & (U2)((U2)1U << SBLTWRN_CHMSTS_LV2)) != (U2)0U) {
            u1_t_sspnd_cnd = (U1)TRUE;
        } else {
            u1_t_sspnd_cnd = (U1)FALSE;
        }
    }

    if (
        (u1_t_sspnd_cnd == (U1)TRUE) &&                                                                     /* Suspending OR other seat is Lv2 */
        ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SHIFT_R) == (U4)0U)  &&                              /* NOT shift in R */
        ((stp_a_VCLSTS->u4_vclsts & u4_t_spdmsk) != (U4)0U)                 &&                              /* speed exceeded */
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKLFLG) != (U1)0U)                  /* unbuckled */
        ) {
        u4_t_cond = (U4)(SBLTWRN_CHMSTS_LV2 | SBLTWRN_CHMOPT_LV2TM_CNTCLR | SBLTWRN_CHMOPT_LV2TM_CNTUP | SBLTWRN_CHMOPT_LV2_SSPND_CLR | SBLTWRN_CHMOPT_GPTMRFLG_CLR);
    } else {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnChmTrns_condBx(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChmTrns_condBx(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if (st_sp_sbltwrn_chmsts[u1_a_SEATID].u2p_timer[SBLTWRN_CHMTIMER_LGL] >= stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_LGLST]) {
        if ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKLFLG) == (U1)0U) {
            u4_t_cond = (U4)SBLTWRN_CHMSTS_LGLWT;
        } else {
            u4_t_cond = (U4)SBLTWRN_CHMSTS_LEGAL;
        }
    } else {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnChmTrns_condLegal(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChmTrns_condLegal(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if (st_sp_sbltwrn_chmsts[u1_a_SEATID].u2p_timer[SBLTWRN_CHMTIMER_LGL] >= stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_LGLTO]) {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_LGLCMP;
    } else {
        if ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKLFLG) == (U1)0U) {
            u4_t_cond = (U4)SBLTWRN_CHMSTS_LGLWT;
        } else {
            u4_t_cond = (U4)SBLTWRN_CHMSTS_LEGAL;
        }
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnChmTrns_condEA(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChmTrns_condEA(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKLFLG) == (U1)0U) {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_OFF;
    } else {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_KEEP;
    }
    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnChmTrns_condEF(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChmTrns_condEF(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U2  u2_t_gptim;

    u2_t_gptim = stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_GP];

    if (
        (u2_t_gptim > (U2)0U)                                               &&          /* GP Enable */
        ((stp_a_VCLSTS->u4_vclsts & (U4)(SBLTWRN_VCLSTS_SHIFT_R | SBLTWRN_VCLSTS_SPD_RUN)) == (U4)SBLTWRN_VCLSTS_SPD_RUN)  &&          /* not shift R */
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKLFLG) != (U1)0U)  /* unbuckled */
        ) {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_UNBKNT;
    } else {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnChmTrns_condEI(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChmTrns_condEI(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if (
        ((stp_a_VCLSTS->u4_vclsts & (U4)(SBLTWRN_VCLSTS_SHIFT_R | SBLTWRN_VCLSTS_SPD_RUN)) == (U4)SBLTWRN_VCLSTS_SPD_RUN) &&        /* not shift R AND speed exceeded */
        (u2_a_SYNC_TRGT == (U2)((U2)1U << SBLTWRN_CHMSTS_LV2))
        ) {
        u4_t_cond = (U4)(SBLTWRN_CHMSTS_LV2 | SBLTWRN_CHMOPT_LV2TM_CNTCLR | SBLTWRN_CHMOPT_LV2TM_CNTUP | SBLTWRN_CHMOPT_GPTMRFLG_CLR);
    } else {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnChmTrns_condFGHtoA(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChmTrns_condFGHtoA(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    static  const   U4  u4_sp_CND[SBLTWRN_NUM_WRNOFFJDG] = {
        (U4)SBLTWRN_CHMSTS_KEEP,
        (U4)(SBLTWRN_CHMSTS_OFF | SBLTWRN_CHMOPT_LV1TM_CNTCLR | SBLTWRN_CHMOPT_LV1TM_CNTSTP | SBLTWRN_CHMOPT_LV2TM_CNTCLR | SBLTWRN_CHMOPT_LV2TM_CNTSTP | SBLTWRN_CHMOPT_GPLV1_SSPND_SET),
        (U4)(SBLTWRN_CHMSTS_OFF | SBLTWRN_CHMOPT_LV1TM_CNTCLR | SBLTWRN_CHMOPT_LV1TM_CNTSTP | SBLTWRN_CHMOPT_LV2TM_CNTCLR | SBLTWRN_CHMOPT_LV2TM_CNTSTP),
        (U4)(SBLTWRN_CHMSTS_OFF | SBLTWRN_CHMOPT_LV1TM_CNTCLR | SBLTWRN_CHMOPT_LV1TM_CNTSTP | SBLTWRN_CHMOPT_LV2TM_CNTCLR | SBLTWRN_CHMOPT_LV2TM_CNTSTP)
    };
    U4  u4_t_cond;
    U1  u1_t_fac;

    u1_t_fac = u1_s_SbltwrnChmTrns_OffJdgCmn(u1_a_SEATID, u1_a_SEATTYP, stp_a_VCLSTS);
    u4_t_cond = u4_sp_CND[u1_t_fac];

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnChmTrns_condIA(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChmTrns_condIA(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    static  const   U4  u4_sp_CND[SBLTWRN_NUM_WRNOFFJDG] = {
        (U4)SBLTWRN_CHMSTS_KEEP,
        (U4)(SBLTWRN_CHMSTS_OFF | SBLTWRN_CHMOPT_LV2TM_CNTCLR | SBLTWRN_CHMOPT_LV2TM_CNTSTP | SBLTWRN_CHMOPT_LV2_SSPND_SET),
        (U4)(SBLTWRN_CHMSTS_OFF | SBLTWRN_CHMOPT_LV2TM_CNTCLR | SBLTWRN_CHMOPT_LV2TM_CNTSTP),
        (U4)(SBLTWRN_CHMSTS_OFF | SBLTWRN_CHMOPT_LV2TM_CNTCLR | SBLTWRN_CHMOPT_LV2TM_CNTSTP)
    };
    U4  u4_t_cond;
    U1  u1_t_fac;

    u1_t_fac = u1_s_SbltwrnChmTrns_OffJdgCmn(u1_a_SEATID, u1_a_SEATTYP, stp_a_VCLSTS);
    u4_t_cond = u4_sp_CND[u1_t_fac];

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnChmTrns_condJA(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChmTrns_condJA(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U1  u1_t_fac;

    u1_t_fac = u1_s_SbltwrnChmTrns_OffJdgCmn(u1_a_SEATID, u1_a_SEATTYP, stp_a_VCLSTS);
    if (u1_t_fac == (U1)SBLTWRN_WRNOFFJDG_BY_DRBKL) {
        u4_t_cond = (U4)(SBLTWRN_CHMSTS_OFF | SBLTWRN_CHMOPT_LV2TM_CNTCLR | SBLTWRN_CHMOPT_LV2TM_CNTSTP);
    } else {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnChmTrns_condFG(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChmTrns_condFG(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if (u2_a_SYNC_TRGT == (U2)0U) {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_GP;
    } else {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnChmTrns_condFH(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChmTrns_condFH(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U2  u2_t_gp_tim;
    U1  u1_t_gp_sup;

    u2_t_gp_tim = stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_GP];
    u1_t_gp_sup = u1_s_SbltwrnChmTrns_GpCndCmn(stp_a_VCLSTS->stp_wrnprm, u1_a_SEATTYP);

    if ((u1_t_gp_sup == (U1)TRUE) && (st_sp_sbltwrn_chmsts[u1_a_SEATID].u2p_timer[SBLTWRN_CHMTIMER_GP] >= u2_t_gp_tim) && (u2_a_SYNC_TRGT == (U2)0U)) {
        u4_t_cond = (U4)(SBLTWRN_CHMSTS_LV1 | SBLTWRN_CHMOPT_LV1TM_CNTCLR | SBLTWRN_CHMOPT_LV1TM_CNTUP | SBLTWRN_CHMOPT_GPTMRFLG_CLR);
    } else {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnChmTrns_condFI(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChmTrns_condFI(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U1  u1_t_gp_sup;

    u1_t_gp_sup = u1_s_SbltwrnChmTrns_GpCndCmn(stp_a_VCLSTS->stp_wrnprm, u1_a_SEATTYP);

    if ((u1_t_gp_sup == (U1)TRUE) && ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_HIGH) != (U4)0U) && (u2_a_SYNC_TRGT == (U2)0U)) {
        u4_t_cond = (U4)(SBLTWRN_CHMSTS_LV2 |
            SBLTWRN_CHMOPT_LV1TM_CNTCLR | SBLTWRN_CHMOPT_LV1TM_CNTSTP |
            SBLTWRN_CHMOPT_LV2TM_CNTCLR | SBLTWRN_CHMOPT_LV2TM_CNTUP | SBLTWRN_CHMOPT_GPTMRFLG_CLR);
    } else {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnChmTrns_condGH(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChmTrns_condGH(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U2  u2_t_gp_tim;
    U1  u1_t_gp_sup;

    u2_t_gp_tim = stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_GP];
    u1_t_gp_sup = u1_s_SbltwrnChmTrns_GpCndCmn(stp_a_VCLSTS->stp_wrnprm, u1_a_SEATTYP);

    if (u1_t_gp_sup == (U1)TRUE) {
        if (
            (st_sp_sbltwrn_chmsts[u1_a_SEATID].u2p_timer[SBLTWRN_CHMTIMER_GP] >= u2_t_gp_tim)   ||  /* GP timer exceeded */
            ((u2_a_SYNC_TRGT & (U2)((U2)1U << SBLTWRN_CHMSTS_LV1)) != (U2)0U)                       /* other seat is Lv1 */
            ) {
            u4_t_cond = (U4)(SBLTWRN_CHMSTS_LV1 | SBLTWRN_CHMOPT_LV1TM_CNTCLR | SBLTWRN_CHMOPT_LV1TM_CNTUP | SBLTWRN_CHMOPT_GPTMRFLG_CLR);
        } else {
            u4_t_cond = (U4)SBLTWRN_CHMSTS_KEEP;
        }
    } else {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_LV1;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnChmTrns_condGI(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChmTrns_condGI(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U1  u1_t_gp_sup;

    u1_t_gp_sup = u1_s_SbltwrnChmTrns_GpCndCmn(stp_a_VCLSTS->stp_wrnprm, u1_a_SEATTYP);

    if (((u2_a_SYNC_TRGT & (U2)((U2)1U << SBLTWRN_CHMSTS_LV2)) != (U2)0U) ||    /* other seat is Lv2 */
            ((u1_t_gp_sup == (U1)TRUE) &&                                                   /* Rr GP enable or front seat */
            ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_HIGH)    != (U4)0U)          /* high speed exceeded */
        )) {
        u4_t_cond = (U4)(SBLTWRN_CHMSTS_LV2 | SBLTWRN_CHMOPT_LV1TM_CNTSTP |
                         SBLTWRN_CHMOPT_LV2TM_CNTCLR | SBLTWRN_CHMOPT_LV2TM_CNTUP | SBLTWRN_CHMOPT_GPTMRFLG_CLR);
    } else {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnChmTrns_condHI(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChmTrns_condHI(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U2  u2_t_gp_tim;

    u2_t_gp_tim = stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_GP];
    if (
        ((u2_a_SYNC_TRGT & (U2)((U2)1U << SBLTWRN_CHMSTS_LV2)) != (U2)0U) ||                /* other seat is Lv2 */
        ((u2_t_gp_tim > (U2)0U) && ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_HIGH) != (U4)0U)) ||      /* GP enable AND high speed exceeded */
        (st_sp_sbltwrn_chmsts[u1_a_SEATID].u2p_timer[SBLTWRN_CHMTIMER_LV1] >= stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_LV1])  /* Lv1 timer exceeded */
        ) {
        u4_t_cond = (U4)(SBLTWRN_CHMSTS_LV2 | SBLTWRN_CHMOPT_LV1TM_CNTSTP | SBLTWRN_CHMOPT_LV2TM_CNTCLR | SBLTWRN_CHMOPT_LV2TM_CNTUP);
    } else {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnChmTrns_condIJ(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChmTrns_condIJ(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if (st_sp_sbltwrn_chmsts[u1_a_SEATID].u2p_timer[SBLTWRN_CHMTIMER_LV2] >= stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_LV2]) {
        u4_t_cond = (U4)(SBLTWRN_CHMSTS_L2CMP | SBLTWRN_CHMOPT_LV2TM_CNTSTP);
    } else {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U1      u1_s_SbltwrnChmTrns_GpCndCmn(const ST_SBLTWRN_WRNPRM *stp_a_WRNPRM, const U1 u1_a_SEATTYP)                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_SbltwrnChmTrns_GpCndCmn(const ST_SBLTWRN_WRNPRM *stp_a_WRNPRM, const U1 u1_a_SEATTYP)
{
    U2  u2_t_gp_tim;
    U1  u1_t_gp_sup;

    u2_t_gp_tim = stp_a_WRNPRM[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_GP];
    if ((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_DS) || (u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_PS)) {
        /* In front seat, GP support is ignored */
        u1_t_gp_sup = (U1)TRUE;
    } else {
        if (u2_t_gp_tim > (U2)0U) {
            u1_t_gp_sup = (U1)TRUE;
        } else {
            u1_t_gp_sup = (U1)FALSE;
        }
    }

    return (u1_t_gp_sup);
}

/*===================================================================================================================================*/
/* static  U1      u1_s_SbltwrnChmTrns_GptmChk(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_SbltwrnChmTrns_GptmChk(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    U4  u4_t_spdmsk;
    U2  u2_t_gptimthr;
    U1  u1_t_cnd_sft;

    u4_t_spdmsk  = (U4)SBLTWRN_VCLSTS_SPD_RUN;
    u1_t_cnd_sft = (U1)0U;
    if ((st_sp_sbltwrn_chmsts[u1_a_SEATID].u1_flg & (U1)SBLTWRN_CHMFLG_SSPND_GPLV1) != (U1)0U) {
        u4_t_spdmsk |= (U4)SBLTWRN_VCLSTS_SPD_RSM;
    }
    u2_t_gptimthr = stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_GP];
    
    if (u2_t_gptimthr > (U2)0U) {
        /* GP enable */
        u1_t_cnd_sft = (U1)SBLTWRN_GPTMCHK_GP_ENA;
    } else {
        u2_t_gptimthr = (U2)U2_MAX;
    }
    if ((stp_a_VCLSTS->u4_vclsts & u4_t_spdmsk) != (U4)0U) {
        u1_t_cnd_sft |= (U1)SBLTWRN_GPTMCHK_SPD_EXC;
    }
    if (st_sp_sbltwrn_chmsts[u1_a_SEATID].u2p_timer[SBLTWRN_CHMTIMER_GP] >= u2_t_gptimthr) {
        u1_t_cnd_sft |= (U1)SBLTWRN_GPTMCHK_GPTM_EXC;
    }
    if (u2_a_SYNC_TRGT != (U2)0U) {
        u1_t_cnd_sft |= (U1)SBLTWRN_GPTMCHK_OTH_WRN;
    }

    return (u1_t_cnd_sft);
}

/*===================================================================================================================================*/
/* static  U1      u1_s_SbltwrnChmTrns_OffJdgCmn(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS)  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_SbltwrnChmTrns_OffJdgCmn(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS)
{
    U1  u1_t_fac;
    U1  u1_t_dropn;

    u1_t_dropn = u1_g_SbltwrnDrchk(stp_a_VCLSTS->u4_vclsts, u1_a_SEATTYP, (U1)TRUE);
    u1_t_fac = (U1)SBLTWRN_WRNOFFJDG_NON;

    /* Factor Priority Order: DRBKL > PARK > SFTR */

    if ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SHIFT_R) != (U4)0U) {
        u1_t_fac = (U1)SBLTWRN_WRNOFFJDG_BY_SFT_R;
    }
    if (((stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u4_ctlopt & (U4)SBLTWRN_CTLOPT_PRKWRN) == (U4)0U) &&
        ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_PARK) != (U4)0U)                         /* parking */
        ) {
        u1_t_fac = (U1)SBLTWRN_WRNOFFJDG_BY_PARK;
    }
    if (
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) == (U1)0U) ||      /* buckled */
        ((u1_t_dropn == (U1)TRUE) && ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_STP_OVER) == (U4)0U))     /* the door is open */
        ) {
        u1_t_fac = (U1)SBLTWRN_WRNOFFJDG_BY_DRBKL;
    }

    return (u1_t_fac);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condAB(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condAB(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    static const U2 u2_s_FIRST_IG_ON = (U2)1U;
    U4              u4_t_cond;

    if ((stp_a_VCLSTS->u2_igontm == u2_s_FIRST_IG_ON) && (stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_LGLST] != (U2)0U)) {
        u4_t_cond = (U4)(SBLTWRN_TTSTS_LGLPR | SBLTWRN_TTOPT_LGLTM_CNTCLR | SBLTWRN_TTOPT_LGLTM_CNTUP);
    } else {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condAF(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condAF(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U1  u1_t_chm_chk;

    u1_t_chm_chk = u1_s_SbltwrnTtTrns_ChmStsChk(u1_a_SEATID, (U1)SBLTWRN_CHMSTCHK_GPLV1);

    if (((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKLFLG) != (U1)0U) && (u1_t_chm_chk == (U1)TRUE)) {
        u4_t_cond = (U4)SBLTWRN_TTSTS_FR_LV1;
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condAG(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condAG(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if (((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKLFLG) != (U1)0U) && (st_sp_sbltwrn_chmsts[u1_a_SEATID].u1_ctlsts == (U1)SBLTWRN_CHMSTS_LV2)) {
        u4_t_cond = (U4)SBLTWRN_TTSTS_FR_LV2;
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condAI(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condAI(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U1  u1_t_chm_chk;

    u1_t_chm_chk = u1_s_SbltwrnTtTrns_ChmStsChk(u1_a_SEATID, (U1)SBLTWRN_CHMSTCHK_WRN);

    if (((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKLFLG) != (U1)0U) && (u1_t_chm_chk == (U1)FALSE)) {
        u4_t_cond = (U4)SBLTWRN_TTSTS_FR_PARK;
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condBx(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condBx(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if (st_sp_sbltwrn_ttsts[u1_a_SEATID].u2p_timer[SBLTWRN_TTTIMER_LGL] >= stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_LGLST]) {
        if ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKLFLG) == (U1)0U) {
            u4_t_cond = (U4)SBLTWRN_TTSTS_LGLWT;
        } else {
            u4_t_cond = (U4)SBLTWRN_TTSTS_LEGAL;
        }
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condLegal(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condLegal(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if (st_sp_sbltwrn_ttsts[u1_a_SEATID].u2p_timer[SBLTWRN_TTTIMER_LGL] >= stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_LGLTO]) {
        u4_t_cond = (U4)SBLTWRN_TTSTS_LGLCMP;
    } else {
        if ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKLFLG) == (U1)0U) {
            u4_t_cond = (U4)SBLTWRN_TTSTS_LGLWT;
        } else {
            u4_t_cond = (U4)SBLTWRN_TTSTS_LEGAL;
        }
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condEH(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condEH(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if (((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKLFLG) != (U1)0U) && (st_sp_sbltwrn_chmsts[u1_a_SEATID].u1_ctlsts == (U1)SBLTWRN_CHMSTS_L2CMP)) {
        u4_t_cond = (U4)SBLTWRN_TTSTS_FR_L2CMP;
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condEI(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condEI(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U1  u1_t_chm_chk;

    u1_t_chm_chk = u1_s_SbltwrnTtTrns_ChmStsChk(u1_a_SEATID, (U1)SBLTWRN_CHMSTCHK_WRN);

    if (((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKLFLG) != (U1)0U) && (u1_t_chm_chk == (U1)FALSE)) {
        u4_t_cond = (U4)SBLTWRN_TTSTS_FR_PARK;
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condXtoA(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condXtoA(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKLFLG) == (U1)0U) {
        u4_t_cond = (U4)SBLTWRN_TTSTS_OFF;
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condFG(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condFG(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if (((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKLFLG) != (U1)0U) && (st_sp_sbltwrn_chmsts[u1_a_SEATID].u1_ctlsts == (U1)SBLTWRN_CHMSTS_LV2)) {
        u4_t_cond = (U4)SBLTWRN_TTSTS_FR_LV2;
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condGH(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condGH(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if (((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKLFLG) != (U1)0U) && (st_sp_sbltwrn_chmsts[u1_a_SEATID].u1_ctlsts == (U1)SBLTWRN_CHMSTS_L2CMP)) {
        u4_t_cond = (U4)SBLTWRN_TTSTS_FR_L2CMP;
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condXtoIJ(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condXtoIJ(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U4  u4_t_park;
    U4  u4_t_prkwrn;
    U1  u1_t_sts;
    U1  u1_t_dropn;

    u1_t_sts    = (U1)FALSE;
    u4_t_prkwrn = (stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u4_ctlopt & (U4)SBLTWRN_CTLOPT_PRKWRN);
    u1_t_dropn  = u1_g_SbltwrnDrchk(stp_a_VCLSTS->u4_vclsts, u1_a_SEATTYP, (U1)FALSE);
    u4_t_park   = (stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_PARK);

    if ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKLFLG) != (U1)0U) {
        if ((u4_t_prkwrn == (U4)0U) && (u4_t_park != (U4)0U)) {
            u1_t_sts = (U1)TRUE;
        }
        if (u1_t_dropn == (U1)TRUE) {
            u1_t_sts = (U1)TRUE;
        }
    }

    if (u1_t_sts == (U1)TRUE) {
        if (u4_t_park != (U4)0U) {
            u4_t_cond = (U4)SBLTWRN_TTSTS_FR_PARK;
        } else {
            if ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_STP_OVER) == (U4)0U) {
                u4_t_cond = (U4)SBLTWRN_TTSTS_FR_LWSP;
            } else {
                u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
            }
        }
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condHtoIJ(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condHtoIJ(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U1  u1_t_dropn;

    u1_t_dropn  = u1_g_SbltwrnDrchk(stp_a_VCLSTS->u4_vclsts, u1_a_SEATTYP, (U1)FALSE);

    if ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKLFLG) != (U1)0U) {
        if (u1_t_dropn == (U1)TRUE) {
            if ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_PARK) != (U4)0U) {
                u4_t_cond = (U4)SBLTWRN_TTSTS_FR_PARK;
            } else {
                if ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_STP_OVER) == (U4)0U) {
                    u4_t_cond = (U4)SBLTWRN_TTSTS_FR_LWSP;
                } else {
                    u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
                }
            }
        } else {
            u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
        }
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condIJ_JI(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condIJ_JI(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if (((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKLFLG) != (U1)0U)) {
        if ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_PARK) != (U4)0U) {
            u4_t_cond = (U4)SBLTWRN_TTSTS_FR_PARK;
        } else {
            u4_t_cond = (U4)SBLTWRN_TTSTS_FR_LWSP;
        }
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condAK(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condAK(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    /* First 'Undetermined -> Unbuckled' Edge since IG-ON */
    if (
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_FIXUNBKL) != (U1)0U) &&
        (stp_a_VCLSTS->u2_igontm <= (stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_IGON] + (U2)SBLTWRN_TT_IGONTM_OFST))
        ) {
        u4_t_cond = (U4)SBLTWRN_TTSTS_IGON;
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condAL(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condAL(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U1  u1_t_dropn;

    u1_t_dropn  = u1_g_SbltwrnDrchk(stp_a_VCLSTS->u4_vclsts, u1_a_SEATTYP, (U1)TRUE);

    if (
        ((u1_t_dropn == (U1)TRUE) ||
            ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_D_DR_OP) != (U4)0U) ||
            ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_P_DR_OP) != (U4)0U)) &&  /* some rear door(s) or D door or P door open */
        ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_STP_OVER) == (U4)0U) &&
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U)     /* unbucked               */
        ) {
        u4_t_cond = (U4)(SBLTWRN_TTSTS_DOOR | SBLTWRN_TTOPT_DRTM_CNTCLR | SBLTWRN_TTOPT_DRTM_CNTUP);
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condAN(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condAN(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U4  u4_t_vclsts;
    U1  u1_t_chmsts;
    U1  u1_t_bklsts;
    U1  u1_t_bkledgchk;
    U1  u1_t_bklprk_cnd;

    u1_t_chmsts = u1_s_SbltwrnTtTrns_ChmStsChk(u1_a_SEATID, (U1)SBLTWRN_CHMSTCHK_WRN);
    u1_t_bklsts = stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID];
    u4_t_vclsts = stp_a_VCLSTS->u4_vclsts;
    
    u1_t_bklprk_cnd = (U1)FALSE;

    if (u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_RS_SNSR) {
        /* Do not perform unbuckle edge check if seatsnsr exists. */
        u1_t_bkledgchk = (U1)SBLTWRN_BKLSTS_UNBCKLFLG;
    } else {
        u1_t_bkledgchk = (U1)SBLTWRN_BKLSTS_UNBCKLEDG;
    }

    if (((u1_t_bklsts & (U1)SBLTWRN_BKLSTS_UNBCKLFLG) != (U1)0U) && ((u4_t_vclsts & (U4)SBLTWRN_VCLSTS_PARKEDG) != (U4)0U)) {
        u1_t_bklprk_cnd = (U1)TRUE;
    }
    if (((u1_t_bklsts & u1_t_bkledgchk) != (U1)0U) && ((u4_t_vclsts & (U4)SBLTWRN_VCLSTS_PARK) != (U4)0U)) {
        u1_t_bklprk_cnd = (U1)TRUE;
    }

    if ((u1_t_bklprk_cnd == (U1)TRUE) && (u1_t_chmsts == (U1)FALSE)) {
        u4_t_cond = (U4)(SBLTWRN_TTSTS_RR_PARK | SBLTWRN_TTOPT_UBTM_CNTCLR | SBLTWRN_TTOPT_UBTM_CNTUP);
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condAO(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condAO(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if (((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U)) {
        if (((u4_a_SYNC_TRGT & (U4)SBLTWRN_TTSTCHK_OTHWRN) != (U4)0U) || (stp_a_VCLSTS->u2_bkledgtmr == (U2)1U)) {     /* other seat is buckled */
            u4_t_cond = (U4)SBLTWRN_TTSTS_SYNC;
        } else {
            u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
        }
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condAP(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condAP(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U1  u1_t_chmchk;

    u1_t_chmchk = u1_s_SbltwrnTtTrns_ChmStsChk(u1_a_SEATID, (U1)SBLTWRN_CHMSTCHK_GPLV1);

    if (((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKLFLG) != (U1)0U) && (u1_t_chmchk == (U1)TRUE)) {
        u4_t_cond = (U4)SBLTWRN_TTSTS_RR_LV1;
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condAQ(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condAQ(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if (
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKLFLG) != (U1)0U) &&
        (st_sp_sbltwrn_chmsts[u1_a_SEATID].u1_ctlsts == (U1)SBLTWRN_CHMSTS_LV2)
        ) {
        u4_t_cond = (U4)SBLTWRN_TTSTS_RR_LV2;
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condAS(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condAS(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U4  u4_t_vclsts;
    U1  u1_t_chmsts;
    U1  u1_t_bkledgchk;
    U1  u1_t_bklsts;
    U1  u1_t_bklprk_cnd;

    u1_t_chmsts = u1_s_SbltwrnTtTrns_ChmStsChk(u1_a_SEATID, (U1)SBLTWRN_CHMSTCHK_WRN);
    u1_t_bklsts = stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID];
    u4_t_vclsts = stp_a_VCLSTS->u4_vclsts;

    if (u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_RS_SNSR) {
        /* Do not perform unbuckle edge check if seatsnsr exists. */
        u1_t_bkledgchk = (U1)SBLTWRN_BKLSTS_UNBCKLFLG;
    } else {
        u1_t_bkledgchk = (U1)SBLTWRN_BKLSTS_UNBCKLEDG;
    }

    u1_t_bklprk_cnd = (U1)FALSE;
    if (((u1_t_bklsts & (U1)SBLTWRN_BKLSTS_UNBCKLFLG) != (U1)0U) && ((u4_t_vclsts & (U4)SBLTWRN_VCLSTS_UNPARKEDG) != (U4)0U)) {
        u1_t_bklprk_cnd = (U1)TRUE;
    }
    if (((u1_t_bklsts & u1_t_bkledgchk) != (U1)0U) && ((u4_t_vclsts & (U4)SBLTWRN_VCLSTS_PARK) == (U4)0U)) {
        u1_t_bklprk_cnd = (U1)TRUE;
    }

    if ((u1_t_bklprk_cnd == (U1)TRUE) && (u1_t_chmsts == (U1)FALSE)) {
        u4_t_cond = (U4)(SBLTWRN_TTSTS_RR_LWSP | SBLTWRN_TTOPT_UBTM_CNTCLR | SBLTWRN_TTOPT_UBTM_CNTUP);
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condKA(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condKA(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if (
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) == (U1)0U) ||
        (stp_a_VCLSTS->u2_igontm > (stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_IGON] + (U2)SBLTWRN_TT_IGONTM_OFST))) {
        u4_t_cond = (U4)SBLTWRN_TTSTS_OFF;
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condKL(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condKL(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U1  u1_t_dropn;

    u1_t_dropn  = u1_g_SbltwrnDrchk(stp_a_VCLSTS->u4_vclsts, u1_a_SEATTYP, (U1)TRUE);

    if (
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U) &&
        (u1_t_dropn == (U1)TRUE) &&
        ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_STP_OVER) == (U4)0U)) {
        u4_t_cond = (U4)(SBLTWRN_TTSTS_DOOR | SBLTWRN_TTOPT_DRTM_CNTCLR | SBLTWRN_TTOPT_DRTM_CNTUP);
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condKO(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condKO(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    
    if (
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U) &&                                           /* unbuckeled */
        (stp_a_VCLSTS->u2_igontm > (stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_IGON] + (U2)SBLTWRN_TT_IGONTM_OFST)) && /* IG-ON timer exceeded */
        (((u4_a_SYNC_TRGT & (U4)SBLTWRN_TTSTCHK_OTHWRN) != (U4)0U) || (stp_a_VCLSTS->u2_bkledgtmr > stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_TTBKLEDG])) /* some seat's TT are on OR buckle edge timer is exceeded */
        ) {
        u4_t_cond = (U4)SBLTWRN_TTSTS_SYNC;
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condLA(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condLA(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if (
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) == (U1)0U) ||
        (
            (u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_RS_NOSN) &&
            (st_sp_sbltwrn_ttsts[u1_a_SEATID].u2p_timer[SBLTWRN_TTTIMER_DOR] >= stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_DOOR]) &&
            (
                ((stp_a_VCLSTS->stp_vclprm->u4_cmnopt & (U4)SBLTWRN_CMNOPT_TTBKLEDG_ENA) == (U4)0U) ||
                (stp_a_VCLSTS->u2_bkledgtmr > stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_TTBKLEDG])
            )
        )
        ) {
        u4_t_cond = (U4)(SBLTWRN_TTSTS_OFF | SBLTWRN_TTOPT_DRTM_CNTCLR | SBLTWRN_TTOPT_DRTM_CNTSTP);
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condLN(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condLN(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U4  u4_t_prk_chk;
    U1  u1_t_dropn;

    u1_t_dropn  = u1_g_SbltwrnDrchk(stp_a_VCLSTS->u4_vclsts, u1_a_SEATTYP, (U1)TRUE);
    if (u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_RS_SNSR) {
        u4_t_prk_chk = (U4)SBLTWRN_VCLSTS_PARK;
    } else {
        u4_t_prk_chk = (U4)SBLTWRN_VCLSTS_PARKEDG;
    }

    if (
        ((stp_a_VCLSTS->u4_vclsts & u4_t_prk_chk) == u4_t_prk_chk) && (u1_t_dropn == (U1)FALSE) &&          /* All rear doors are closed AND park condition is true */
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKLFLG) != (U1)0U)                  /* unbuckled */
        ) {
        u4_t_cond = (U4)(SBLTWRN_TTSTS_RR_PARK | SBLTWRN_TTOPT_DRTM_CNTCLR | SBLTWRN_TTOPT_DRTM_CNTSTP | SBLTWRN_TTOPT_UBTM_CNTCLR | SBLTWRN_TTOPT_UBTM_CNTUP);
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condLO(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condLO(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U1  u1_t_dropn;

    u1_t_dropn  = u1_g_SbltwrnDrchk(stp_a_VCLSTS->u4_vclsts, u1_a_SEATTYP, (U1)TRUE);

    if (
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U) &&
        (u1_t_dropn == (U1)FALSE) &&
        (st_sp_sbltwrn_ttsts[u1_a_SEATID].u2p_timer[SBLTWRN_TTTIMER_DOR] >= stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_DOOR]) &&
        (
            ((u4_a_SYNC_TRGT & (U4)SBLTWRN_TTSTCHK_OTHWRN) != (U4)0U) ||    /* other seat's TT are active */
            (stp_a_VCLSTS->u2_bkledgtmr == (U2)1U)                          /* other seat is now buckled */
        )
        ) {
        u4_t_cond = (U4)(SBLTWRN_TTSTS_SYNC | SBLTWRN_TTOPT_DRTM_CNTCLR | SBLTWRN_TTOPT_DRTM_CNTSTP);
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condLP(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condLP(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U1  u1_t_chm_chk;

    u1_t_chm_chk = u1_s_SbltwrnTtTrns_ChmStsChk(u1_a_SEATID, (U1)SBLTWRN_CHMSTCHK_GPLV1);
    if (((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U) && (u1_t_chm_chk == (U1)TRUE)) {
        u4_t_cond = (U4)(SBLTWRN_TTSTS_RR_LV1 | SBLTWRN_TTOPT_UBTM_CNTCLR | SBLTWRN_TTOPT_UBTM_CNTSTP);
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condLQ(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condLQ(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if (
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U) &&
        (st_sp_sbltwrn_chmsts[u1_a_SEATID].u1_ctlsts == (U1)SBLTWRN_CHMSTS_LV2)
        ) {
        u4_t_cond = (U4)(SBLTWRN_TTSTS_RR_LV2 | SBLTWRN_TTOPT_UBTM_CNTCLR | SBLTWRN_TTOPT_UBTM_CNTSTP);
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condLS(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condLS(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U4  u4_t_prk_chk_trgt;
    U4  u4_t_prk_chk;
    U1  u1_t_dropn;

    u1_t_dropn  = u1_g_SbltwrnDrchk(stp_a_VCLSTS->u4_vclsts, u1_a_SEATTYP, (U1)TRUE);
    if (u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_RS_SNSR) {
        u4_t_prk_chk_trgt = (U4)SBLTWRN_VCLSTS_PARK;
        u4_t_prk_chk = (U4)0U;
    } else {
        u4_t_prk_chk_trgt = (U4)SBLTWRN_VCLSTS_UNPARKEDG;
        u4_t_prk_chk = (U4)SBLTWRN_VCLSTS_UNPARKEDG;
    }

    if (
        ((stp_a_VCLSTS->u4_vclsts & u4_t_prk_chk_trgt) == u4_t_prk_chk) && (u1_t_dropn == (U1)FALSE) &&     /* All rear doors are closed AND park condition is true */
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKLFLG) != (U1)0U)                  /* unbuckled */
        ) {
        u4_t_cond = (U4)(SBLTWRN_TTSTS_RR_LWSP | SBLTWRN_TTOPT_UBTM_CNTCLR | SBLTWRN_TTOPT_UBTM_CNTUP);
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condNA(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condNA(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if (
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) == (U1)0U) ||
        (
            (
                ((stp_a_VCLSTS->stp_vclprm->u4_cmnopt & (U4)SBLTWRN_CMNOPT_TTBKLEDG_ENA) == (U4)0U) ||
                (stp_a_VCLSTS->u2_bkledgtmr > stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_TTBKLEDG])
            ) &&
            (st_sp_sbltwrn_ttsts[u1_a_SEATID].u2p_timer[SBLTWRN_TTTIMER_UBK] >= stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_TTON])
        )
        ) {
        u4_t_cond = (U4)(SBLTWRN_TTSTS_OFF | SBLTWRN_TTOPT_UBTM_CNTCLR | SBLTWRN_TTOPT_UBTM_CNTSTP);
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condNL(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condNL(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U1  u1_t_dropn;

    u1_t_dropn  = u1_g_SbltwrnDrchk(stp_a_VCLSTS->u4_vclsts, u1_a_SEATTYP, (U1)TRUE);

    if (((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U) && 
        (u1_t_dropn == (U1)TRUE) &&
        ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_STP_OVER) == (U4)0U)) {
        u4_t_cond = (U4)(SBLTWRN_TTSTS_DOOR | SBLTWRN_TTOPT_UBTM_CNTCLR | SBLTWRN_TTOPT_UBTM_CNTSTP | SBLTWRN_TTOPT_DRTM_CNTCLR | SBLTWRN_TTOPT_DRTM_CNTUP);
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condNS(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condNS(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if (((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKLFLG) != (U1)0U) && ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_PARK) == (U4)0U)) {
        u4_t_cond = (U4)(SBLTWRN_TTSTS_RR_LWSP | SBLTWRN_TTOPT_UBTM_CNTCLR | SBLTWRN_TTOPT_UBTM_CNTUP);
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condOA(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condOA(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if (
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) == (U1)0U) ||
        (
            ((u4_a_SYNC_TRGT & (U4)SBLTWRN_TTSTCHK_OTHWRN) == (U4)0U) &&
            (
                (stp_a_VCLSTS->u2_bkledgtmr > stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_TTBKLEDG]) ||
                ((stp_a_VCLSTS->stp_vclprm->u4_cmnopt & (U4)SBLTWRN_CMNOPT_TTBKLEDG_ENA) == (U4)0U)
            )
        )
    ) {
        u4_t_cond = (U4)SBLTWRN_TTSTS_OFF;
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condOL(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condOL(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U1  u1_t_dropn;

    u1_t_dropn  = u1_g_SbltwrnDrchk(stp_a_VCLSTS->u4_vclsts, u1_a_SEATTYP, (U1)TRUE);

    if (((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U) &&  
        (u1_t_dropn == (U1)TRUE) &&
        ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_STP_OVER) == (U4)0U)) {
        u4_t_cond = (U4)(SBLTWRN_TTSTS_DOOR | SBLTWRN_TTOPT_DRTM_CNTCLR | SBLTWRN_TTOPT_DRTM_CNTUP);
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condON(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condON(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U1  u1_t_chm_chk;

    u1_t_chm_chk = u1_s_SbltwrnTtTrns_ChmStsChk(u1_a_SEATID, (U1)SBLTWRN_CHMSTCHK_WRN);

    if (
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKLFLG) != (U1)0U) &&
        ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_PARKEDG) != (U4)0U) &&
        (u1_t_chm_chk == (U1)FALSE)
        ) {
        u4_t_cond = (U4)(SBLTWRN_TTSTS_RR_PARK | SBLTWRN_TTOPT_UBTM_CNTCLR | SBLTWRN_TTOPT_UBTM_CNTUP);
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condOR(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condOR(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    return (u4_s_SbltwrnTtTrns_condOQtoR_cmn(u1_a_SEATID, u1_a_SEATTYP, stp_a_VCLSTS, u4_a_SYNC_TRGT));
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condOtoPQ(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condOtoPQ(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U1  u1_t_chm_chk;

    u1_t_chm_chk = u1_s_SbltwrnTtTrns_ChmStsChk(u1_a_SEATID, (U1)SBLTWRN_CHMSTCHK_GPLV1);

    if ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKLFLG) != (U1)0U) {
        if (st_sp_sbltwrn_chmsts[u1_a_SEATID].u1_ctlsts == (U1)SBLTWRN_CHMSTS_LV2) {
            u4_t_cond = (U4)SBLTWRN_TTSTS_RR_LV2;
        } else if (u1_t_chm_chk == (U1)TRUE) {
            u4_t_cond = (U4)SBLTWRN_TTSTS_RR_LV1;
        } else {
            u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
        }
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condOQtoR_cmn(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condOQtoR_cmn(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U1  u1_t_bklsts;
    U1  u1_t_bkledgcmp;

    u1_t_bklsts = stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID];
    if (((stp_a_VCLSTS->stp_vclprm->u4_cmnopt & (U4)SBLTWRN_CMNOPT_TTBKLEDG_ENA) == (U4)0U) || (stp_a_VCLSTS->u2_bkledgtmr > stp_a_VCLSTS->stp_wrnprm->u2p_tim[SBLTWRN_TIM_TTBKLEDG])) {
        u1_t_bkledgcmp = (U1)TRUE;
    } else {
        u1_t_bkledgcmp = (U1)FALSE;
    }

    if (
        ((u1_t_bklsts & (U1)SBLTWRN_BKLSTS_UNBCKLFLG) != (U1)0U) &&
        (st_sp_sbltwrn_chmsts[u1_a_SEATID].u1_ctlsts == (U1)SBLTWRN_CHMSTS_L2CMP) &&
        ((stp_a_VCLSTS->stp_vclprm->u4_cmnopt & (U4)SBLTWRN_CMNOPT_NOSN_L2CMP_ON) != (U4)0U)
        ) {
        u4_t_cond = (U4)SBLTWRN_TTSTS_RR_L2CMP_ON;
    } else {
        if (
            (st_sp_sbltwrn_chmsts[u1_a_SEATID].u1_ctlsts == (U1)SBLTWRN_CHMSTS_L2CMP) &&
            ((u1_t_bklsts & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U) &&
            (u1_t_bkledgcmp == (U1)TRUE) &&
            ((u4_a_SYNC_TRGT & (U4)SBLTWRN_TTSTCHK_OTHWRN) == (U4)0U)
            ) {
            u4_t_cond = (U4)SBLTWRN_TTSTS_RR_L2CMP_OFF;
        } else {
            u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
        }
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condOS(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condOS(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U1  u1_t_chm_chk;

    u1_t_chm_chk = u1_s_SbltwrnTtTrns_ChmStsChk(u1_a_SEATID, (U1)SBLTWRN_CHMSTCHK_WRN);

    if (
        (u1_t_chm_chk == (U1)FALSE) &&
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKLFLG) != (U1)0U) &&
        ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_UNPARKEDG) != (U1)0U)
        ) {
        u4_t_cond = (U4)(SBLTWRN_TTSTS_RR_LWSP | SBLTWRN_TTOPT_UBTM_CNTCLR | SBLTWRN_TTOPT_UBTM_CNTUP);
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condPA(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condPA(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) == (U1)0U) {
        u4_t_cond = (U4)SBLTWRN_TTSTS_OFF;
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condPL(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condPL(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U1  u1_t_dropn;

    u1_t_dropn  = u1_g_SbltwrnDrchk(stp_a_VCLSTS->u4_vclsts, u1_a_SEATTYP, (U1)TRUE);

    if (((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U) && 
        (u1_t_dropn == (U1)TRUE) &&
        ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_STP_OVER) == (U4)0U)) {
        u4_t_cond = (U4)(SBLTWRN_TTSTS_DOOR | SBLTWRN_TTOPT_DRTM_CNTCLR | SBLTWRN_TTOPT_DRTM_CNTUP);
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condPQtoN(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condPQtoN(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U1  u1_t_chm_chk;

    u1_t_chm_chk = u1_s_SbltwrnTtTrns_ChmStsChk(u1_a_SEATID, (U1)SBLTWRN_CHMSTCHK_WRN);

    if (
        (u1_t_chm_chk == (U1)FALSE) &&
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKLFLG) != (U1)0U) &&
        ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_PARK) != (U4)0U)
        ) {
        u4_t_cond = (U4)(SBLTWRN_TTSTS_RR_PARK | SBLTWRN_TTOPT_UBTM_CNTCLR | SBLTWRN_TTOPT_UBTM_CNTUP);
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condPQ(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condPQ(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if (
        (st_sp_sbltwrn_chmsts[u1_a_SEATID].u1_ctlsts == (U1)SBLTWRN_CHMSTS_LV2) &&
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKLFLG) != (U1)0U) 
        ) {
        u4_t_cond = (U4)SBLTWRN_TTSTS_RR_LV2;
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condQA(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condQA(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) == (U1)0U) {
        u4_t_cond = (U4)SBLTWRN_TTSTS_OFF;
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condQL(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condQL(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U1  u1_t_dropn;

    u1_t_dropn  = u1_g_SbltwrnDrchk(stp_a_VCLSTS->u4_vclsts, u1_a_SEATTYP, (U1)TRUE);

    if (
        (u1_t_dropn == (U1)TRUE) &&
        ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_STP_OVER) == (U4)0U) &&
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U) 
        ) {
        u4_t_cond = (U4)(SBLTWRN_TTSTS_DOOR | SBLTWRN_TTOPT_DRTM_CNTCLR | SBLTWRN_TTOPT_DRTM_CNTUP);
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condQO(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condQO(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U1  u1_t_bklchm_cnd;

    if (
        (st_sp_sbltwrn_chmsts[u1_a_SEATID].u1_ctlsts == (U1)SBLTWRN_CHMSTS_L2CMP) &&
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U) &&
        ((stp_a_VCLSTS->stp_vclprm->u4_cmnopt & (U4)SBLTWRN_CMNOPT_NOSN_L2CMP_ON) == (U4)0U)
        ) {
        u1_t_bklchm_cnd = (U1)TRUE;
    } else {
        u1_t_bklchm_cnd = (U1)FALSE;
    }

    if (
        (u1_t_bklchm_cnd == (U1)TRUE) &&
        (
            ((u4_a_SYNC_TRGT & (U4)SBLTWRN_TTSTCHK_OTHWRN) != (U4)0U) ||
            (((stp_a_VCLSTS->stp_vclprm->u4_cmnopt & (U4)SBLTWRN_CMNOPT_TTBKLEDG_ENA) != (U4)0U) && (stp_a_VCLSTS->u2_bkledgtmr <= stp_a_VCLSTS->stp_wrnprm->u2p_tim[SBLTWRN_TIM_TTBKLEDG]))
        )
        ) {
        u4_t_cond = (U4)SBLTWRN_TTSTS_SYNC;
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condQR(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condQR(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if (
        (u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_RS_SNSR) &&
        (st_sp_sbltwrn_chmsts[u1_a_SEATID].u1_ctlsts == (U1)SBLTWRN_CHMSTS_L2CMP) &&
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U) && 
        ((stp_a_VCLSTS->stp_vclprm->u4_cmnopt & (U4)SBLTWRN_CMNOPT_SNSR_L2CMP_ON) != (U1)0U) 
        ) {
        u4_t_cond = (U4)SBLTWRN_TTSTS_RR_L2CMP_ON;
    } else {
        u4_t_cond = u4_s_SbltwrnTtTrns_condOQtoR_cmn(u1_a_SEATID, u1_a_SEATTYP, stp_a_VCLSTS, u4_a_SYNC_TRGT);
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condRA(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condRA(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) == (U1)0U) {
        u4_t_cond = (U4)SBLTWRN_TTSTS_OFF;
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condRL(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condRL(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U1  u1_t_dropn;

    u1_t_dropn  = u1_g_SbltwrnDrchk(stp_a_VCLSTS->u4_vclsts, u1_a_SEATTYP, (U1)TRUE);

    if (((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U) && 
        (u1_t_dropn == (U1)TRUE) &&
        ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_STP_OVER) == (U4)0U)) {
        u4_t_cond = (U4)(SBLTWRN_TTSTS_DOOR | SBLTWRN_TTOPT_DRTM_CNTCLR | SBLTWRN_TTOPT_DRTM_CNTUP);
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condRO(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condRO(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if (
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U) &&
        (st_sp_sbltwrn_chmsts[u1_a_SEATID].u1_ctlsts == (U1)SBLTWRN_CHMSTS_L2CMP) &&
        ((stp_a_VCLSTS->stp_vclprm->u4_cmnopt & (U4)SBLTWRN_CMNOPT_NOSN_L2CMP_ON) == (U4)0U) &&
        (
            ((u4_a_SYNC_TRGT & (U4)SBLTWRN_TTSTCHK_OTHWRN) != (U4)0U) ||
            (((stp_a_VCLSTS->stp_vclprm->u4_cmnopt & (U4)SBLTWRN_CMNOPT_TTBKLEDG_ENA) != (U4)0U) && (stp_a_VCLSTS->u2_bkledgtmr <= stp_a_VCLSTS->stp_wrnprm->u2p_tim[SBLTWRN_TIM_TTBKLEDG]))
        )
        ) {
        u4_t_cond = (U4)SBLTWRN_TTSTS_SYNC;
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condSA(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condSA(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) == (U1)0U) {
        u4_t_cond = (U4)(SBLTWRN_TTSTS_OFF | SBLTWRN_TTOPT_UBTM_CNTCLR | SBLTWRN_TTOPT_UBTM_CNTSTP);
    } else {
        if (
            (stp_a_VCLSTS->u2_bkledgtmr > stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_TTBKLEDG]) ||
            (st_sp_sbltwrn_ttsts[u1_a_SEATID].u2p_timer[SBLTWRN_TTTIMER_UBK] >= stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_TTON])
            ) {
            u4_t_cond = (U4)(SBLTWRN_TTSTS_OFF | SBLTWRN_TTOPT_UBTM_CNTCLR | SBLTWRN_TTOPT_UBTM_CNTSTP);
        } else {
            u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
        }
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condSL(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condSL(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U1  u1_t_dropn;

    u1_t_dropn  = u1_g_SbltwrnDrchk(stp_a_VCLSTS->u4_vclsts, u1_a_SEATTYP, (U1)TRUE);

    if (((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U) && 
        (u1_t_dropn == (U1)TRUE) &&
        ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_STP_OVER) == (U4)0U)) {
        u4_t_cond = (U4)(SBLTWRN_TTSTS_DOOR | SBLTWRN_TTOPT_UBTM_CNTCLR | SBLTWRN_TTOPT_UBTM_CNTSTP | SBLTWRN_TTOPT_DRTM_CNTCLR | SBLTWRN_TTOPT_DRTM_CNTUP);
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condSN(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condSN(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if (((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKLFLG) != (U1)0U) && ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_PARK) != (U4)0U)) {
        u4_t_cond = (U4)(SBLTWRN_TTSTS_RR_PARK | SBLTWRN_TTOPT_UBTM_CNTCLR | SBLTWRN_TTOPT_UBTM_CNTUP);
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condNStoO(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condNStoO(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if (
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U) &&
        (st_sp_sbltwrn_ttsts[u1_a_SEATID].u2p_timer[SBLTWRN_TTTIMER_UBK] >= stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_TTON])
        ) {
        if (
            ((u4_a_SYNC_TRGT & (U4)SBLTWRN_TTSTCHK_OTHWRN) != (U4)0U) ||
            (
                (
                (stp_a_VCLSTS->stp_vclprm->u4_cmnopt & (U4)SBLTWRN_CMNOPT_TTBKLEDG_ENA) != (U4)0U) &&
                (stp_a_VCLSTS->u2_bkledgtmr <= stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_TTBKLEDG])
                )
            ) {
            u4_t_cond = (U4)(SBLTWRN_TTSTS_SYNC | SBLTWRN_TTOPT_UBTM_CNTCLR | SBLTWRN_TTOPT_UBTM_CNTSTP);
        } else {
            u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
        }
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condNStoP(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condNStoP(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U1  u1_t_chm_chk;

    u1_t_chm_chk = u1_s_SbltwrnTtTrns_ChmStsChk(u1_a_SEATID, (U1)SBLTWRN_CHMSTCHK_GPLV1);

    if (((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKLFLG) != (U1)0U) && (u1_t_chm_chk == (U1)TRUE)) {
        u4_t_cond = (U4)(SBLTWRN_TTSTS_RR_LV1 | SBLTWRN_TTOPT_UBTM_CNTCLR | SBLTWRN_TTOPT_UBTM_CNTSTP);
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condNStoQ(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condNStoQ(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if (((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKLFLG) != (U1)0U) && (st_sp_sbltwrn_chmsts[u1_a_SEATID].u1_ctlsts == (U1)SBLTWRN_CHMSTS_LV2)) {
        u4_t_cond = (U4)(SBLTWRN_TTSTS_RR_LV2 | SBLTWRN_TTOPT_UBTM_CNTCLR | SBLTWRN_TTOPT_UBTM_CNTSTP);
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U1      u1_s_SbltwrnTtTrns_ChmStsChk(const U1 u1_a_SEATID, const U1 u1_a_CHK_ITEM)                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_SbltwrnTtTrns_ChmStsChk(const U1 u1_a_SEATID, const U1 u1_a_CHK_ITEM)
{
    static const U2     u2_sp_CHK_BIT[SBLTWRN_NUM_CHMSTCHK] = {
        (U2)(((U2)1U << SBLTWRN_CHMSTS_UNBKNT) | ((U2)1U << SBLTWRN_CHMSTS_GP) | ((U2)1U << SBLTWRN_CHMSTS_LV1) | ((U2)1U << SBLTWRN_CHMSTS_LV2) | ((U2)1U << SBLTWRN_CHMSTS_L2CMP)),   /* SBLTWRN_CHMSTCHK_WRN */
        (U2)(((U2)1U << SBLTWRN_CHMSTS_UNBKNT) | ((U2)1U << SBLTWRN_CHMSTS_GP) | ((U2)1U << SBLTWRN_CHMSTS_LV1))                                                                        /* SBLTWRN_CHMSTCHK_GPLV1   */
    };
    U2  u2_t_chmst_bit;
    U1  u1_t_result;

    u2_t_chmst_bit = (U2)((U2)1U << st_sp_sbltwrn_chmsts[u1_a_SEATID].u1_ctlsts);

    if ((u2_t_chmst_bit & u2_sp_CHK_BIT[u1_a_CHK_ITEM]) != (U2)0U) {
        u1_t_result = (U1)TRUE;
    } else {
        u1_t_result = (U1)FALSE;
    }

    return (u1_t_result);
}

/*===================================================================================================================================*/
/* static  void    vd_s_SbltwrnInitChmsts(ST_SBLTWRN_CHMST *stp_a_chmsts)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_SbltwrnInitChmsts(ST_SBLTWRN_CHMST *stp_a_chmsts)
{
    stp_a_chmsts->u1_ctlsts = (U1)SBLTWRN_CHMSTS_OFF;
    stp_a_chmsts->u1_flg    = (U1)0U;
    vd_g_MemfillU2(&stp_a_chmsts->u2p_timer[0], (U2)0U, (U4)SBLTWRN_NUM_CHMTIMER);
}

/*===================================================================================================================================*/
/* static  void    vd_s_SbltwrnInitTtsts(ST_SBLTWRN_TTST *stp_t_ttsts)                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_SbltwrnInitTtsts(ST_SBLTWRN_TTST *stp_a_ttsts)
{
    stp_a_ttsts->u1_ctlsts      = (U1)SBLTWRN_TTSTS_OFF;
    stp_a_ttsts->u1_flg         = (U1)0U;
    vd_g_MemfillU2(&stp_a_ttsts->u2p_timer[0], (U2)0U, (U4)SBLTWRN_NUM_TTTIMER);
}

/*===================================================================================================================================*/
/* static  void    vd_s_SbltwrnSbrBzrChgDet(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_SbltwrnSbrBzrChgDet(void)
{
    U4          u4_t_lpcnt;
    U1          u1_t_no_logging;
    
    u1_t_no_logging = (U1)FALSE;
    
    for (u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)SBLTWRN_NUM_3ROWSEAT; u4_t_lpcnt++) {
        if ((u1_sp_sbltwrn_sbr_oldsts[u4_t_lpcnt] != (U1)SBLTWRN_CHMSTS_OFF   ) &&
            (u1_sp_sbltwrn_sbr_oldsts[u4_t_lpcnt] != (U1)SBLTWRN_CHMSTS_LGLPR ) &&
            (u1_sp_sbltwrn_sbr_oldsts[u4_t_lpcnt] != (U1)SBLTWRN_CHMSTS_LEGAL ) &&
            (u1_sp_sbltwrn_sbr_oldsts[u4_t_lpcnt] != (U1)SBLTWRN_CHMSTS_LGLWT ) &&
            (u1_sp_sbltwrn_sbr_oldsts[u4_t_lpcnt] != (U1)SBLTWRN_CHMSTS_LGLCMP) &&
            (u1_sp_sbltwrn_sbr_oldsts[u4_t_lpcnt] != (U1)SBLTWRN_CHMSTS_L2CMP )) {
            u1_t_no_logging = (U1)TRUE;
        }
        u1_sp_sbltwrn_sbr_oldsts[u4_t_lpcnt] = st_sp_sbltwrn_chmsts[u4_t_lpcnt].u1_ctlsts;
    }
    
    if (u1_t_no_logging == (U1)FALSE) {
        for (u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)SBLTWRN_NUM_3ROWSEAT; u4_t_lpcnt++) {
            if ((st_sp_sbltwrn_chmsts[u4_t_lpcnt].u1_ctlsts == (U1)SBLTWRN_CHMSTS_UNBKNT) ||
                (st_sp_sbltwrn_chmsts[u4_t_lpcnt].u1_ctlsts == (U1)SBLTWRN_CHMSTS_LV1   ) ||
                (st_sp_sbltwrn_chmsts[u4_t_lpcnt].u1_ctlsts == (U1)SBLTWRN_CHMSTS_LV2   )) {
                u1_sp_sbltwrn_sbrbit[st_gp_SBLTWRN_SBR_STSTBL[u4_t_lpcnt].u1_idx] |= st_gp_SBLTWRN_SBR_STSTBL[u4_t_lpcnt].u1_wrtbit;
            }
        }
    }
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    04/12/2018  HY       New.                                                                                               */
/*  1.1.0    06/03/2019  YI       Update warning parameter and Add buckled delay logic.                                              */
/*  2.0.0    08/12/2020  KK       The State Machine Mechanism was renewed (equals to the TMC spec.)                                  */
/*  2.1.0    01/12/2021  TN       Changed buzzer priority, telltale priority, and rear seat Lv2 hours.                               */
/*  2.1.1    10/18/2021  TA(M)    Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*  2.1.2    10/25/2021  TK       QAC supported.                                                                                     */
/*  2.1.3    04/05/2022  YI(M)    Delete unused define and process.                                                                  */
/*  2.2.0    02/29/2024  TH       for 19PFv3                                                                                         */
/*  2.2.1    03/20/2025  TH       Fix : Door Open Judge (Telltale al,kl,nl,ol,pl,ql,rl,sl,la,ln,lo,ls)                               */
/*  3.0.0    09/16/2025  NA       New.  Legal compliance.(FMVSS208_2025 SBR regulations)                                             */
/*  3.1.0    01/22/2026  NA       Change state transition condition in FMVSS operation (Buzzer BA, Telltale ba)                      */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/*  -------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  19PFv3-1 12/26/2023  SH       Add rear seat calibration reading logic                                                            */
/*  19PFv3-2 02/12/2024  SH       Add vd_s_SbltwrnGetCalibRear1(), vd_s_SbltwrnGetCalibRear2() and vd_s_SbltwrnGetCalibRear3()       */
/*  19PFv3-3 04/12/2024  SH       Add calibration guard                                                                              */
/*  19PFv3-4 07/05/2024  TN(DT)   Delete Calibration Guard Process except for out of array references.                               */
/*  BEV-1    03/11/2026  ED       Change for BEV FF2. (MET-B_SEAREM-CSTD-A0-09-A-C3).                                                */
/*                                Changed Telltale al judgment and Condition l timer                                                 */
/*                                                                                                                                   */
/*  * HY     = Hidefumi Yoshida, Denso                                                                                               */
/*  * YI     = Yoshiki  Iwata,   Denso                                                                                               */
/*  * KK     = Kohei Kato,       Denso Techno                                                                                        */
/*  * TN     = Tetsu Naruse,     Denso Techno                                                                                        */
/*  * TA(M)  = Teruyuki Anjima, NTT Data MSE                                                                                         */
/*  * TK     = Takanori Kuno, Denso Techno                                                                                           */
/*  * YI(M)  = Yoshiki  Iwata,   NTT Data MSE                                                                                        */
/*  * SH     = Sae Hirose,       Denso Techno                                                                                        */
/*  * TH     = Taisuke Hirakawa, KSE                                                                                                 */
/*  * TN(DT) = Tetsushi Nakano, Denso Techno                                                                                         */
/*  * NA     = Nazirul Afham,    PXT                                                                                                 */
/*  * ED     = Emoh Dagasdas,    DTPH                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
