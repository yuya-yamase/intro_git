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
#define SBLTWRN_FM_C_MAJOR                         (3)
#define SBLTWRN_FM_C_MINOR                         (1)
#define SBLTWRN_FM_C_PATCH                         (0)

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
#if ((SBLTWRN_FM_C_MAJOR != SBLTWRN_H_MAJOR) || \
     (SBLTWRN_FM_C_MINOR != SBLTWRN_H_MINOR) || \
     (SBLTWRN_FM_C_PATCH != SBLTWRN_H_PATCH))
#error "sbltwrn_fm.c and sbltwrn.h : source and header files are inconsistent!"
#endif

#if ((SBLTWRN_FM_C_MAJOR != SBLTWRN_CFG_PRIVATE_H_MAJOR) || \
     (SBLTWRN_FM_C_MINOR != SBLTWRN_CFG_PRIVATE_H_MINOR) || \
     (SBLTWRN_FM_C_PATCH != SBLTWRN_CFG_PRIVATE_H_PATCH))
#error "sbltwrn_fm.c and sbltwrn_cfg_private.h : source and header files are inconsistent!"
#endif

#if ((SBLTWRN_FM_C_MAJOR != SBLTWRN_PRIVATE_H_MAJOR) || \
     (SBLTWRN_FM_C_MINOR != SBLTWRN_PRIVATE_H_MINOR) || \
     (SBLTWRN_FM_C_PATCH != SBLTWRN_PRIVATE_H_PATCH))
#error "sbltwrn_fm.c and sbltwrn_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define     SBLTWRN_CHMFLG_CNT_INITIAL          (0x01U)         /* Initial timer cnt-up    */
#define     SBLTWRN_CHMFLG_CNT_UNBCKL           (0x02U)         /* Unbckl timer cnt-up    */
#define     SBLTWRN_CHMFLG_CNT_FRLV1            (0x04U)         /* Front seat Lv1 timer cnt-up    */
#define     SBLTWRN_CHMFLG_CNT_RSLV1            (0x08U)         /* Rear seat Lv1 timer cnt-up    */
#define     SBLTWRN_CHMFLG_CNT_LV2CNT           (0x10U)         /* Lv2 count timer cnt-up    */
#define     SBLTWRN_CHMFLG_CNT_RSLV2            (0x20U)         /* Rear seat Lv2 timer cnt-up    */

#define     SBLTWRN_CHMOPT_MSK_FM               (0xFFFFFF00U)
#define     SBLTWRN_CHMOPT_INITIALTM_CNTUP      (0x00000100U)
#define     SBLTWRN_CHMOPT_UNBCKLTM_CNTUP       (0x00000200U)
#define     SBLTWRN_CHMOPT_FRLV1TM_CNTUP        (0x00000400U)
#define     SBLTWRN_CHMOPT_RSLV1TM_CNTUP        (0x00000800U)
#define     SBLTWRN_CHMOPT_LV2CNTTM_CNTUP       (0x00001000U)
#define     SBLTWRN_CHMOPT_RSLV2TM_CNTUP        (0x00002000U)
#define     SBLTWRN_CHMOPT_INITIALTM_CNTSTP     (0x00004000U)
#define     SBLTWRN_CHMOPT_UNBCKLTM_CNTSTP      (0x00008000U)
#define     SBLTWRN_CHMOPT_FRLV1TM_CNTSTP       (0x00010000U)
#define     SBLTWRN_CHMOPT_RSLV1TM_CNTSTP       (0x00020000U)
#define     SBLTWRN_CHMOPT_LV2CNTTM_CNTSTP      (0x00040000U)
#define     SBLTWRN_CHMOPT_RSLV2TM_CNTSTP       (0x00080000U)
#define     SBLTWRN_CHMOPT_INITIALTM_CNTCLR     (0x00100000U)
#define     SBLTWRN_CHMOPT_UNBCKLTM_CNTCLR      (0x00200000U)
#define     SBLTWRN_CHMOPT_FRLV1TM_CNTCLR       (0x00400000U)
#define     SBLTWRN_CHMOPT_RSLV1TM_CNTCLR       (0x00800000U)
#define     SBLTWRN_CHMOPT_LV2CNTTM_CNTCLR      (0x01000000U)
#define     SBLTWRN_CHMOPT_RSLV2TM_CNTCLR       (0x02000000U)

#define     SBLTWRN_NUM_CHMTIMER_FM             (6U)
#define     SBLTWRN_CHMTIMER_INITIAL            (0U)
#define     SBLTWRN_CHMTIMER_UNBCKL             (1U)
#define     SBLTWRN_CHMTIMER_FRLV1              (2U)
#define     SBLTWRN_CHMTIMER_RSLV1              (3U)
#define     SBLTWRN_CHMTIMER_LV2CNT             (4U)
#define     SBLTWRN_CHMTIMER_RSLV2              (5U)

#define     SBLTWRN_CHMTIMER_LV2CNT_UPPER       (100000U/SBLTWRN_TICK)

#define     SBLTWRN_TTOPT_FDRTM_CNTUP           (0x00000100U)
#define     SBLTWRN_TTOPT_FDRTM_CNTSTP          (0x00000200U)
#define     SBLTWRN_TTOPT_FDRTM_CNTCLR          (0x00000400U)

#define     SBLTWRN_NUM_TTTIMER_FM              (1U)
#define     SBLTWRN_TTTIMER_FDOR                (0U)            /* The time after door closed */

#define     SBLTWRN_TIM_INITIALPR_PS            (13000U/SBLTWRN_TICK)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct {
    U2  u2p_timer[SBLTWRN_NUM_CHMTIMER_FM];   /* Elapsed Timer Counter */
    U2  u2p_prvtimer[SBLTWRN_NUM_CHMTIMER_FM];   /* Previous Elapsed Timer Counter */
    U1  u1_ctlsts;      /* Chime Status */
    U1  u1_flg;         /* Ctrl Flags (SBLTWRN_CHMFLG_xxx) */
} ST_SBLTWRN_CHMST_FM;

typedef struct {
    U2  u2p_timer[SBLTWRN_NUM_TTTIMER_FM];
    U1  u1_ctlsts;
    U1  u1_flg;
} ST_SBLTWRN_TTST_FM;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  ST_SBLTWRN_CHMST_FM         st_sp_sbltwrn_chmsts_fm[SBLTWRN_NUM_ALLSEAT];
static  ST_SBLTWRN_TTST_FM          st_sp_sbltwrn_ttsts_fm[SBLTWRN_NUM_ALLSEAT];
static  U2                          u2_s_sbltwrn_igontm_fm;
static  U2                          u2_s_sbltwrn_unbklflg_fm;
static  U2                          u2_s_sbltwrn_failsts_fm;
static  U2                          u2_s_sbltwrn_legalpretmr;
static  U1                          u1_sp_sbltwrn_sbrbit_fm[SBLTWRN_SBRBIT_IDX_ALL];
static  U1                          u1_sp_sbltwrn_sbr_oldsts_fm[SBLTWRN_NUM_3ROWSEAT];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  void    vd_s_SbltwrnBklEdgChk_FM(ST_SBLTWRN_VCLST *stp_a_vclsts);
static  void    vd_s_SbltwrnLegalPreTimerChk(const ST_SBLTWRN_VCLST *stp_a_VCLSTS);
static  void    vd_s_SbltwrnUnbkleFlgPostChk_FM(void);
static  void    vd_s_SbltwrnStm_FM(const ST_SBLTWRN_VCLST *stp_a_VCLSTS);
static  void    vd_s_SbltwrnChimeStm_FM(const ST_SBLTWRN_VCLST *stp_a_VCLSTS);
static  void    vd_s_SbltwrnTtStm_FM(const ST_SBLTWRN_VCLST *stp_a_VCLSTS);
static  U1      u1_s_SbltwrnTtStmVldChk_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS);
static  void    vd_s_SbltwrnTtTimAct_FM(ST_SBLTWRN_TTST_FM *stp_a_ttsts, const U4 u4_a_VCLSTS, U4 u4_a_ttopt, const U1 u1_a_SEATTYP, const U1 u1_a_CNT_UP);
static  U4      u4_s_SbltwrnChimeCnd_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static  void    vd_s_SbltwrnChimeTimAct_FM(ST_SBLTWRN_CHMST_FM *stp_a_chmsts, const U4 u4_a_CHMOPT, const U1 u1_a_CNT_UP);
static  U4      u4_s_SbltwrnChmTrns_condAB_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnChmTrns_condAE_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnChmTrns_condAG_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnChmTrns_condAH_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnChmTrns_condBA_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnChmTrns_condBC_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnChmTrns_condCA_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnChmTrns_condCD_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnChmTrns_condCG_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnChmTrns_condDA_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnChmTrns_condDG_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnChmTrns_condEA_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnChmTrns_condEF_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnChmTrns_condEG_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnChmTrns_condFA_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnChmTrns_condFG_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnChmTrns_condGA_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnChmTrns_condGH_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnChmTrns_condHA_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnChmTrns_condHI_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnChmTrns_condHJ_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnChmTrns_condIA_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnChmTrns_condIH_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnChmTrns_condJA_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnTtTrns_condAB_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnTtTrns_condAE_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnTtTrns_condAF_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnTtTrns_condAG_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnTtTrns_condAH_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnTtTrns_condAI_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnTtTrns_condXtoA_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnTtTrns_condBA_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnTtTrns_condBC_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnTtTrns_condCD_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnTtTrns_condCH_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnTtTrns_condDH_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnTtTrns_condEA_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnTtTrns_condEF_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnTtTrns_condFA_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnTtTrns_condGF_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnTtTrns_condGH_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnTtTrns_condHF_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnTtTrns_condHI_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnTtTrns_condIF_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnTtTrns_condIJ_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnTtTrns_condIK_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnTtTrns_condJF_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnTtTrns_condJI_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnTtTrns_condKF_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static  U4      u4_s_SbltwrnTtStmCnd_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);
static  void    vd_s_SbltwrnInitChmsts_FM(ST_SBLTWRN_CHMST_FM *stp_a_chmsts);
static  void    vd_s_SbltwrnInitTtsts_FM(ST_SBLTWRN_TTST_FM *stp_a_ttsts);
static  void    vd_s_SbltwrnSbrBzrChgDet_FM(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const SBLTWRN_CHMTYP   fp_sp_u4_SBLTWRN_CHMSTM_CND_A_FM[] = {
    &u4_s_SbltwrnChmTrns_condAB_FM,
    &u4_s_SbltwrnChmTrns_condAH_FM,
    &u4_s_SbltwrnChmTrns_condAG_FM,
    &u4_s_SbltwrnChmTrns_condAE_FM
};

static const SBLTWRN_CHMTYP   fp_sp_u4_SBLTWRN_CHMSTM_CND_B_FM[] = {
    &u4_s_SbltwrnChmTrns_condBA_FM,
    &u4_s_SbltwrnChmTrns_condBC_FM
};

static const SBLTWRN_CHMTYP   fp_sp_u4_SBLTWRN_CHMSTM_CND_C_FM[] = {
    &u4_s_SbltwrnChmTrns_condCA_FM,
    &u4_s_SbltwrnChmTrns_condCG_FM,
    &u4_s_SbltwrnChmTrns_condCD_FM
};

static const SBLTWRN_CHMTYP   fp_sp_u4_SBLTWRN_CHMSTM_CND_D_FM[] = {
    &u4_s_SbltwrnChmTrns_condDA_FM,
    &u4_s_SbltwrnChmTrns_condDG_FM
};

static const SBLTWRN_CHMTYP   fp_sp_u4_SBLTWRN_CHMSTM_CND_E_FM[] = {
    &u4_s_SbltwrnChmTrns_condEA_FM,
    &u4_s_SbltwrnChmTrns_condEG_FM,
    &u4_s_SbltwrnChmTrns_condEF_FM
};

static const SBLTWRN_CHMTYP   fp_sp_u4_SBLTWRN_CHMSTM_CND_F_FM[] = {
    &u4_s_SbltwrnChmTrns_condFA_FM,
    &u4_s_SbltwrnChmTrns_condFG_FM
};

static const SBLTWRN_CHMTYP   fp_sp_u4_SBLTWRN_CHMSTM_CND_G_FM[] = {
    &u4_s_SbltwrnChmTrns_condGA_FM,
    &u4_s_SbltwrnChmTrns_condGH_FM
};

static const SBLTWRN_CHMTYP   fp_sp_u4_SBLTWRN_CHMSTM_CND_H_FM[] = {
    &u4_s_SbltwrnChmTrns_condHA_FM,
    &u4_s_SbltwrnChmTrns_condHJ_FM,
    &u4_s_SbltwrnChmTrns_condHI_FM
};

static const SBLTWRN_CHMTYP   fp_sp_u4_SBLTWRN_CHMSTM_CND_I_FM[] = {
    &u4_s_SbltwrnChmTrns_condIA_FM,
    &u4_s_SbltwrnChmTrns_condIH_FM
};

static const SBLTWRN_CHMTYP   fp_sp_u4_SBLTWRN_CHMSTM_CND_J_FM[] = {
    &u4_s_SbltwrnChmTrns_condJA_FM
};

static const ST_SBLTWRN_CHMTYP st_sp_SBLTWRN_CHMSTM_FM[SBLTWRN_NUM_CHMSTS_FM] = {
    {&fp_sp_u4_SBLTWRN_CHMSTM_CND_A_FM[0], sizeof(fp_sp_u4_SBLTWRN_CHMSTM_CND_A_FM) / sizeof(fp_sp_u4_SBLTWRN_CHMSTM_CND_A_FM[0])},    /* SBLTWRN_CHMSTS_OFF_FM     */  
    {&fp_sp_u4_SBLTWRN_CHMSTM_CND_B_FM[0], sizeof(fp_sp_u4_SBLTWRN_CHMSTM_CND_B_FM) / sizeof(fp_sp_u4_SBLTWRN_CHMSTM_CND_B_FM[0])},    /* SBLTWRN_CHMSTS_INIPR_FM   */
    {&fp_sp_u4_SBLTWRN_CHMSTM_CND_C_FM[0], sizeof(fp_sp_u4_SBLTWRN_CHMSTM_CND_C_FM) / sizeof(fp_sp_u4_SBLTWRN_CHMSTM_CND_C_FM[0])},    /* SBLTWRN_CHMSTS_INITIAL_FM */
    {&fp_sp_u4_SBLTWRN_CHMSTM_CND_D_FM[0], sizeof(fp_sp_u4_SBLTWRN_CHMSTM_CND_D_FM) / sizeof(fp_sp_u4_SBLTWRN_CHMSTM_CND_D_FM[0])},    /* SBLTWRN_CHMSTS_INICMP_FM  */
    {&fp_sp_u4_SBLTWRN_CHMSTM_CND_E_FM[0], sizeof(fp_sp_u4_SBLTWRN_CHMSTM_CND_E_FM) / sizeof(fp_sp_u4_SBLTWRN_CHMSTM_CND_E_FM[0])},    /* SBLTWRN_CHMSTS_UNBKNT_FM  */
    {&fp_sp_u4_SBLTWRN_CHMSTM_CND_F_FM[0], sizeof(fp_sp_u4_SBLTWRN_CHMSTM_CND_F_FM) / sizeof(fp_sp_u4_SBLTWRN_CHMSTM_CND_F_FM[0])},    /* SBLTWRN_CHMSTS_UNBKCMP_FM */
    {&fp_sp_u4_SBLTWRN_CHMSTM_CND_G_FM[0], sizeof(fp_sp_u4_SBLTWRN_CHMSTM_CND_G_FM) / sizeof(fp_sp_u4_SBLTWRN_CHMSTM_CND_G_FM[0])},    /* SBLTWRN_CHMSTS_LV1_FM     */
    {&fp_sp_u4_SBLTWRN_CHMSTM_CND_H_FM[0], sizeof(fp_sp_u4_SBLTWRN_CHMSTM_CND_H_FM) / sizeof(fp_sp_u4_SBLTWRN_CHMSTM_CND_H_FM[0])},    /* SBLTWRN_CHMSTS_LV2_FM     */
    {&fp_sp_u4_SBLTWRN_CHMSTM_CND_I_FM[0], sizeof(fp_sp_u4_SBLTWRN_CHMSTM_CND_I_FM) / sizeof(fp_sp_u4_SBLTWRN_CHMSTM_CND_I_FM[0])},    /* SBLTWRN_CHMSTS_L2INT_FM   */
    {&fp_sp_u4_SBLTWRN_CHMSTM_CND_J_FM[0], sizeof(fp_sp_u4_SBLTWRN_CHMSTM_CND_J_FM) / sizeof(fp_sp_u4_SBLTWRN_CHMSTM_CND_J_FM[0])}     /* SBLTWRN_CHMSTS_L2CMP_FM   */
};

static ST_SBLTWRN_TT_STM const fp_sp_u4_SBLTWRN_TTSTM_CND_A_FM[] = {
    /* fp_u4_STM */                                /* u1_TYPMSK */
    { &u4_s_SbltwrnTtTrns_condAB_FM,       (U1)(SBLTWRN_SEATTYPBIT_FR_ALL)  },
    { &u4_s_SbltwrnTtTrns_condAI_FM,       (U1)(SBLTWRN_SEATTYPBIT_FR_ALL | SBLTWRN_SEATTYPBIT_RS_NOSN)  },
    { &u4_s_SbltwrnTtTrns_condAH_FM,       (U1)(SBLTWRN_SEATTYPBIT_FR_ALL | SBLTWRN_SEATTYPBIT_RS_NOSN)  },
    { &u4_s_SbltwrnTtTrns_condAG_FM,       (U1)(SBLTWRN_SEATTYPBIT_FR_ALL | SBLTWRN_SEATTYPBIT_RS_NOSN)  },
    { &u4_s_SbltwrnTtTrns_condAF_FM,       (U1)(SBLTWRN_SEATTYPBIT_RS_NOSN)  },
    { &u4_s_SbltwrnTtTrns_condAE_FM,       (U1)(SBLTWRN_SEATTYPBIT_RS_NOSN)  }
};

static ST_SBLTWRN_TT_STM const fp_sp_u4_SBLTWRN_TTSTM_CND_B_FM[] = {
    /* fp_u4_STM */                                /* u1_TYPMSK */
    { &u4_s_SbltwrnTtTrns_condBC_FM,       (U1)(SBLTWRN_SEATTYPBIT_FR_ALL)  },
    { &u4_s_SbltwrnTtTrns_condBA_FM,       (U1)(SBLTWRN_SEATTYPBIT_FR_ALL)  }
};

static ST_SBLTWRN_TT_STM const fp_sp_u4_SBLTWRN_TTSTM_CND_C_FM[] = {
    /* fp_u4_STM */                                /* u1_TYPMSK */
    { &u4_s_SbltwrnTtTrns_condCH_FM,       (U1)(SBLTWRN_SEATTYPBIT_FR_ALL)  },
    { &u4_s_SbltwrnTtTrns_condCD_FM,       (U1)(SBLTWRN_SEATTYPBIT_FR_ALL)  },
    { &u4_s_SbltwrnTtTrns_condXtoA_FM,     (U1)(SBLTWRN_SEATTYPBIT_FR_ALL)  }
};

static ST_SBLTWRN_TT_STM const fp_sp_u4_SBLTWRN_TTSTM_CND_D_FM[] = {
    /* fp_u4_STM */                                /* u1_TYPMSK */
    { &u4_s_SbltwrnTtTrns_condDH_FM,       (U1)(SBLTWRN_SEATTYPBIT_FR_ALL)  },
    { &u4_s_SbltwrnTtTrns_condXtoA_FM,     (U1)(SBLTWRN_SEATTYPBIT_FR_ALL)  }
};

static ST_SBLTWRN_TT_STM const fp_sp_u4_SBLTWRN_TTSTM_CND_E_FM[] = {
    /* fp_u4_STM */                                /* u1_TYPMSK */
    { &u4_s_SbltwrnTtTrns_condEF_FM,       (U1)(SBLTWRN_SEATTYPBIT_RS_NOSN)  },
    { &u4_s_SbltwrnTtTrns_condEA_FM,       (U1)(SBLTWRN_SEATTYPBIT_RS_NOSN)  }
};

static ST_SBLTWRN_TT_STM const fp_sp_u4_SBLTWRN_TTSTM_CND_F_FM[] = {
    /* fp_u4_STM */                                /* u1_TYPMSK */
    { &u4_s_SbltwrnTtTrns_condFA_FM,       (U1)(SBLTWRN_SEATTYPBIT_RS_NOSN)  }
};

static ST_SBLTWRN_TT_STM const fp_sp_u4_SBLTWRN_TTSTM_CND_G_FM[] = {
    /* fp_u4_STM */                                /* u1_TYPMSK */
    { &u4_s_SbltwrnTtTrns_condGH_FM,       (U1)(SBLTWRN_SEATTYPBIT_FR_ALL | SBLTWRN_SEATTYPBIT_RS_NOSN)  },
    { &u4_s_SbltwrnTtTrns_condGF_FM,       (U1)(SBLTWRN_SEATTYPBIT_RS_NOSN)  },
    { &u4_s_SbltwrnTtTrns_condXtoA_FM,     (U1)(SBLTWRN_SEATTYPBIT_FR_ALL | SBLTWRN_SEATTYPBIT_RS_NOSN)  }
};

static ST_SBLTWRN_TT_STM const fp_sp_u4_SBLTWRN_TTSTM_CND_H_FM[] = {
    /* fp_u4_STM */                                /* u1_TYPMSK */
    { &u4_s_SbltwrnTtTrns_condHI_FM,       (U1)(SBLTWRN_SEATTYPBIT_FR_ALL | SBLTWRN_SEATTYPBIT_RS_NOSN)  },
    { &u4_s_SbltwrnTtTrns_condHF_FM,       (U1)(SBLTWRN_SEATTYPBIT_RS_NOSN)  },
    { &u4_s_SbltwrnTtTrns_condXtoA_FM,     (U1)(SBLTWRN_SEATTYPBIT_FR_ALL | SBLTWRN_SEATTYPBIT_RS_NOSN)  }
};

static ST_SBLTWRN_TT_STM const fp_sp_u4_SBLTWRN_TTSTM_CND_I_FM[] = {
    /* fp_u4_STM */                                /* u1_TYPMSK */
    { &u4_s_SbltwrnTtTrns_condIJ_FM,       (U1)(SBLTWRN_SEATTYPBIT_FR_ALL | SBLTWRN_SEATTYPBIT_RS_NOSN)  },
    { &u4_s_SbltwrnTtTrns_condIF_FM,       (U1)(SBLTWRN_SEATTYPBIT_RS_NOSN)  },
    { &u4_s_SbltwrnTtTrns_condIK_FM,       (U1)(SBLTWRN_SEATTYPBIT_RS_NOSN)  },
    { &u4_s_SbltwrnTtTrns_condXtoA_FM,     (U1)(SBLTWRN_SEATTYPBIT_FR_ALL | SBLTWRN_SEATTYPBIT_RS_NOSN)  }
};

static ST_SBLTWRN_TT_STM const fp_sp_u4_SBLTWRN_TTSTM_CND_J_FM[] = {
    /* fp_u4_STM */                                /* u1_TYPMSK */
    { &u4_s_SbltwrnTtTrns_condJI_FM,       (U1)(SBLTWRN_SEATTYPBIT_FR_ALL | SBLTWRN_SEATTYPBIT_RS_NOSN)  },
    { &u4_s_SbltwrnTtTrns_condJF_FM,       (U1)(SBLTWRN_SEATTYPBIT_RS_NOSN)  },
    { &u4_s_SbltwrnTtTrns_condXtoA_FM,     (U1)(SBLTWRN_SEATTYPBIT_FR_ALL | SBLTWRN_SEATTYPBIT_RS_NOSN)  }
};

static ST_SBLTWRN_TT_STM const fp_sp_u4_SBLTWRN_TTSTM_CND_K_FM[] = {
    /* fp_u4_STM */                                /* u1_TYPMSK */
    { &u4_s_SbltwrnTtTrns_condKF_FM,       (U1)(SBLTWRN_SEATTYPBIT_RS_NOSN)  },
    { &u4_s_SbltwrnTtTrns_condXtoA_FM,     (U1)(SBLTWRN_SEATTYPBIT_RS_NOSN)  }
};

static const ST_SBLTWRN_TTTYP st_sp_SBLTWRN_TTTYP_FM[SBLTWRN_NUM_TTSTS_FM] = {
    {&fp_sp_u4_SBLTWRN_TTSTM_CND_A_FM[0],  sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_A_FM) / sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_A_FM[0])},
    {&fp_sp_u4_SBLTWRN_TTSTM_CND_B_FM[0],  sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_B_FM) / sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_B_FM[0])},
    {&fp_sp_u4_SBLTWRN_TTSTM_CND_C_FM[0],  sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_C_FM) / sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_C_FM[0])},
    {&fp_sp_u4_SBLTWRN_TTSTM_CND_D_FM[0],  sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_D_FM) / sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_D_FM[0])},
    {&fp_sp_u4_SBLTWRN_TTSTM_CND_E_FM[0],  sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_E_FM) / sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_E_FM[0])},
    {&fp_sp_u4_SBLTWRN_TTSTM_CND_F_FM[0],  sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_F_FM) / sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_F_FM[0])},
    {&fp_sp_u4_SBLTWRN_TTSTM_CND_G_FM[0],  sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_G_FM) / sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_G_FM[0])},
    {&fp_sp_u4_SBLTWRN_TTSTM_CND_H_FM[0],  sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_H_FM) / sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_H_FM[0])},
    {&fp_sp_u4_SBLTWRN_TTSTM_CND_I_FM[0],  sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_I_FM) / sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_I_FM[0])},
    {&fp_sp_u4_SBLTWRN_TTSTM_CND_J_FM[0],  sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_J_FM) / sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_J_FM[0])},
    {&fp_sp_u4_SBLTWRN_TTSTM_CND_K_FM[0],  sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_K_FM) / sizeof(fp_sp_u4_SBLTWRN_TTSTM_CND_K_FM[0])}
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* void            vd_g_SbltwrnInit_FM(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_SbltwrnInit_FM(void)
{
    U4  u4_t_loop;

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)SBLTWRN_NUM_ALLSEAT; u4_t_loop++) {
        vd_s_SbltwrnInitChmsts_FM(&st_sp_sbltwrn_chmsts_fm[u4_t_loop]);
        vd_s_SbltwrnInitTtsts_FM(&st_sp_sbltwrn_ttsts_fm[u4_t_loop]);
    }

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)SBLTWRN_NUM_3ROWSEAT; u4_t_loop++) {
        u1_sp_sbltwrn_sbr_oldsts_fm[u4_t_loop] = (U1)SBLTWRN_CHMSTS_OFF_FM;
    }
    
    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)SBLTWRN_SBRBIT_IDX_ALL; u4_t_loop++) {
        u1_sp_sbltwrn_sbrbit_fm[u4_t_loop] = (U1)0U;
    }

    u2_s_sbltwrn_igontm_fm         = (U2)0U;
    u2_s_sbltwrn_unbklflg_fm       = (U2)0U;
    u2_s_sbltwrn_failsts_fm        = (U2)0U;
    u2_s_sbltwrn_legalpretmr       = (U2)0U;
}

/*===================================================================================================================================*/
/* void            vd_g_SbltwrnTrans_FM(const U1 u1_a_DSTTYP)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_SbltwrnTrans_FM(const U1 u1_a_DSTTYP)
{
    ST_SBLTWRN_VCLST    st_t_vclsts;
    U1                  u1_t_igon;
    U1                  u1_t_dsttyp;
    U1                  u1_tp_msgsts[SBLTWRN_NUM_MSG];

    u1_t_igon = u1_g_VehopemdIgnOn();
    
    if (u1_t_igon == (U1)TRUE) {
        vd_g_SbltwrnTmcnt(&u2_s_sbltwrn_igontm_fm);
    } else {
        u2_s_sbltwrn_igontm_fm = (U2)0U;
    }

    u1_t_dsttyp = u1_a_DSTTYP;

    vd_g_MemfillU1(&u1_tp_msgsts[0], (U1)SBLTWRN_UNKNOWN, (U4)SBLTWRN_NUM_MSG);
    vd_g_SbltwrnMsgsts(u1_t_igon, &u1_tp_msgsts[0]);

    st_t_vclsts.u2_igontm       = u2_s_sbltwrn_igontm_fm;
    st_t_vclsts.stp_wrnprm      = st_gp_SBLTWRN_WRNPRM[u1_t_dsttyp];
    st_t_vclsts.stp_vclprm      = &st_gp_SBLTWRN_VCLPRM[u1_t_dsttyp];
    st_t_vclsts.u4_vclsts       = u4_g_SbltVclsts_FM(u2_s_sbltwrn_igontm_fm, &u1_tp_msgsts[0], &st_t_vclsts.stp_vclprm->u2p_spd[0]);

    vd_g_MemfillU1(&st_t_vclsts.u1p_bklsts[0], (U1)0U, (U4)SBLTWRN_NUM_ALLSEAT);
    vd_g_SbltwrnSeatsts(st_t_vclsts.u4_vclsts, &u1_tp_msgsts[0], &st_t_vclsts.u1p_bklsts[0]);

    vd_g_SbltSeatSetBklSts();

    vd_s_SbltwrnBklEdgChk_FM(&st_t_vclsts);

    vd_s_SbltwrnLegalPreTimerChk(&st_t_vclsts);

    vd_s_SbltwrnStm_FM(&st_t_vclsts);

    vd_s_SbltwrnUnbkleFlgPostChk_FM();

    vd_s_SbltwrnSbrBzrChgDet_FM();
}

/*===================================================================================================================================*/
/* U1              u1_g_SbltwrnChmStsBySeat_FM(const U1 u1_a_SEATID)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_SbltwrnChmStsBySeat_FM(const U1 u1_a_SEATID)
{
    U1  u1_t_chmsts;

    if (u1_a_SEATID < (U1)SBLTWRN_NUM_ALLSEAT) {
        u1_t_chmsts = st_sp_sbltwrn_chmsts_fm[u1_a_SEATID].u1_ctlsts;
    } else {
        u1_t_chmsts = (U1)SBLTWRN_CHMSTS_OFF_FM;
    }

    return (u1_t_chmsts);
}

/*===================================================================================================================================*/
/* U4              u4_g_SbltwrnTtSts_FM(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4              u4_g_SbltwrnTtSts_FM(void)
{
    U4  u4_t_seat;
    U4  u4_t_ttstsbit;

    u4_t_ttstsbit = (U4)0U;
    for (u4_t_seat = (U4)0U; u4_t_seat < (U4)SBLTWRN_NUM_ALLSEAT; u4_t_seat++) {
        u4_t_ttstsbit |= ((U4)1U << st_sp_sbltwrn_ttsts_fm[u4_t_seat].u1_ctlsts);
    }

    return (u4_t_ttstsbit);
}

/*===================================================================================================================================*/
/* U1              u1_g_SbltwrnTtstsBySeat_FM(const U1 u1_a_SEATID)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_SbltwrnTtStsBySeat_FM(const U1 u1_a_SEATID)
{
    U1  u1_t_ttsts;

    if (u1_a_SEATID < (U1)SBLTWRN_NUM_ALLSEAT) {
        u1_t_ttsts = st_sp_sbltwrn_ttsts_fm[u1_a_SEATID].u1_ctlsts;
    } else {
        u1_t_ttsts = (U1)SBLTWRN_TTSTS_OFF_FM;
    }

    return (u1_t_ttsts);
}

/*===================================================================================================================================*/
/*  Set/Clear unbuckle flag and Increment/Reset a buckle edge timer                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_SbltwrnBklEdgChk_FM(ST_SBLTWRN_VCLST *stp_a_vclsts)
{
    U4  u4_t_loop;
    U1  u1_t_seattyp;
    U1  u1_t_dropn;

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)SBLTWRN_NUM_ALLSEAT; u4_t_loop++) {
        u1_t_seattyp = u1_g_SbltwrnSeatTyp((U1)u4_t_loop);
        u1_t_dropn   = u1_g_SbltwrnDrchk(stp_a_vclsts->u4_vclsts, u1_t_seattyp, (U1)FALSE);
        if ((stp_a_vclsts->u1p_bklsts[u4_t_loop] & (U1)SBLTWRN_BKLSTS_UNBCKLEDG) != (U1)0U) {
            /* Set unbkleflg */
            u2_s_sbltwrn_unbklflg_fm |= (U2)((U2)1U << u4_t_loop);
        }
        if ((stp_a_vclsts->u2_igontm == (U2)0U) || ((u1_t_dropn == (U1)TRUE) && ((stp_a_vclsts->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_STP_OVER) == (U4)0U)) ||
            ((stp_a_vclsts->u1p_bklsts[u4_t_loop] & (U1)SBLTWRN_BKLSTS_UNBCKL) == (U1)0U)) {
            /* Clear unbkleflg */
            u2_s_sbltwrn_unbklflg_fm &= ((U2)U2_MAX ^ (U2)((U2)1U << u4_t_loop));
        }

        /*                                                                      */
        /* Note: If a target seat is 'D/P' or 'Rr with seatsnsr' and unbuckled, */
        /*       the unbkleflg is set by sblt_seat.c and always turns on.       */
        /*                                                                      */
        if ((u2_s_sbltwrn_unbklflg_fm & (U2)((U2)1U << u4_t_loop)) != (U2)0U) {
            stp_a_vclsts->u1p_bklsts[u4_t_loop] |= (U1)SBLTWRN_BKLSTS_UNBCKLFLG;
        }

        if ((stp_a_vclsts->u1p_bklsts[u4_t_loop] & (U1)SBLTWRN_BKLSTS_COMFAIL) != (U1)0U) {
            u2_s_sbltwrn_failsts_fm |= (U2)((U2)1U << u4_t_loop);
        } else {
            if ((u2_s_sbltwrn_failsts_fm & (U2)((U2)1U << u4_t_loop)) != (U2)0U) {
                stp_a_vclsts->u1p_bklsts[u4_t_loop] |= (U1)SBLTWRN_BKLSTS_FAILRSTEDG;
            }
            u2_s_sbltwrn_failsts_fm &= ((U2)U2_MAX ^ (U2)((U2)1U << u4_t_loop));
        }
    }
}

/*===================================================================================================================================*/
/* static  void    vd_s_SbltwrnLegalPreTimerChk(const ST_SBLTWRN_VCLST *stp_a_VCLSTS)                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_SbltwrnLegalPreTimerChk(const ST_SBLTWRN_VCLST *stp_a_VCLSTS)
{
    static const U2 u2_s_FIRST_IG_ON = (U2)1U;

    if (stp_a_VCLSTS->u2_igontm == u2_s_FIRST_IG_ON) {
        u2_s_sbltwrn_legalpretmr = (U2)0U;
    }

    if (u2_s_sbltwrn_legalpretmr <= stp_a_VCLSTS->stp_wrnprm[SBLTWRN_SEATTYP_DS].u2p_tim[SBLTWRN_TIM_LGLST]) {
        vd_g_SbltwrnTmcnt(&u2_s_sbltwrn_legalpretmr);
    }
}

/*===================================================================================================================================*/
/* static  void    vd_s_SbltwrnUnbkleFlgPostChk_FM(void)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_SbltwrnUnbkleFlgPostChk_FM(void)
{
    U4  u4_t_loop;

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)SBLTWRN_NUM_ALLSEAT; u4_t_loop++) {
        if ((st_sp_sbltwrn_chmsts_fm[u4_t_loop].u1_ctlsts == (U1)SBLTWRN_CHMSTS_L2CMP_FM) &&
            (st_sp_sbltwrn_ttsts_fm[u4_t_loop].u1_ctlsts == (U1)SBLTWRN_TTSTS_L2CMP_FM)) {

            /* Clear unbkleflg */
            u2_s_sbltwrn_unbklflg_fm &= ((U2)U2_MAX ^ (U2)((U2)1U << u4_t_loop));
        }
    }
}

/*===================================================================================================================================*/
/* static  void    vd_s_SbltwrnStm_FM(const ST_SBLTWRN_VCLST *stp_a_VCLSTS)                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_SbltwrnStm_FM(const ST_SBLTWRN_VCLST *stp_a_VCLSTS)
{
    vd_s_SbltwrnChimeStm_FM(stp_a_VCLSTS);
    vd_s_SbltwrnTtStm_FM(stp_a_VCLSTS);
}

/*===================================================================================================================================*/
/* static  void    vd_s_SbltwrnChimeStm_FM(const ST_SBLTWRN_VCLST *stp_a_VCLSTS)                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_SbltwrnChimeStm_FM(const ST_SBLTWRN_VCLST *stp_a_VCLSTS)
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
            u4_t_chmopt = u4_s_SbltwrnChimeCnd_FM((U1)u4_t_seat, u1_t_seattyp, stp_a_VCLSTS, (U2)0U);
            vd_s_SbltwrnChimeTimAct_FM(&st_sp_sbltwrn_chmsts_fm[u4_t_seat], u4_t_chmopt, (U1)FALSE);
            u2_t_sync_trgt |= (U2)((U2)1U << st_sp_sbltwrn_chmsts_fm[u4_t_seat].u1_ctlsts);
        } else {
            vd_s_SbltwrnInitChmsts_FM(&st_sp_sbltwrn_chmsts_fm[u4_t_seat]);
        }
    }

    for (u4_t_seat = (U4)0U; u4_t_seat < (U4)SBLTWRN_NUM_ALLSEAT; u4_t_seat++) {
        u1_t_seattyp = u1_g_SbltwrnSeatTyp((U1)u4_t_seat);
        if (u1_tp_valid_chk[u4_t_seat] == (U1)TRUE) {
            u4_t_chmopt = u4_s_SbltwrnChimeCnd_FM((U1)u4_t_seat, u1_t_seattyp, stp_a_VCLSTS, u2_t_sync_trgt);
            vd_s_SbltwrnChimeTimAct_FM(&st_sp_sbltwrn_chmsts_fm[u4_t_seat], u4_t_chmopt, (U1)TRUE);
        }
    }
}

/*===================================================================================================================================*/
/* static  void    vd_s_SbltwrnTtStm_FM(const ST_SBLTWRN_VCLST *stp_a_VCLSTS)                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_SbltwrnTtStm_FM(const ST_SBLTWRN_VCLST *stp_a_VCLSTS)
{
    U4  u4_t_seat;
    U4  u4_t_ttopt;
    U4  u4_t_sync_trgt;
    U1  u1_t_seattyp;
    U1  u1_tp_valid_chk[SBLTWRN_NUM_ALLSEAT];
    U4  u4_t_loop;

    u4_t_sync_trgt = (U4)SBLTWRN_TT_SYNCCND_CHK;
    for (u4_t_seat = (U4)0U; u4_t_seat < (U4)SBLTWRN_NUM_ALLSEAT; u4_t_seat++) {
        u1_t_seattyp = u1_g_SbltwrnSeatTyp((U1)u4_t_seat);
        u1_tp_valid_chk[u4_t_seat] = u1_s_SbltwrnTtStmVldChk_FM((U1)u4_t_seat, u1_t_seattyp, stp_a_VCLSTS);
        if (u1_tp_valid_chk[u4_t_seat] == (U1)TRUE) {
            u4_t_ttopt = u4_s_SbltwrnTtStmCnd_FM((U1)u4_t_seat, u1_t_seattyp, stp_a_VCLSTS, (U4)0U);
            vd_s_SbltwrnTtTimAct_FM(&st_sp_sbltwrn_ttsts_fm[u4_t_seat], stp_a_VCLSTS->u4_vclsts, u4_t_ttopt, u1_t_seattyp, (U1)FALSE);
            u4_t_sync_trgt |= ((U4)1U << st_sp_sbltwrn_ttsts_fm[u4_t_seat].u1_ctlsts);
        }
    }

    for (u4_t_seat = (U4)0U; u4_t_seat < (U4)SBLTWRN_NUM_ALLSEAT; u4_t_seat++) {
        u1_t_seattyp = u1_g_SbltwrnSeatTyp((U1)u4_t_seat);
        if (u1_tp_valid_chk[u4_t_seat] == (U1)TRUE) {
            u4_t_ttopt = u4_s_SbltwrnTtStmCnd_FM((U1)u4_t_seat, u1_t_seattyp, stp_a_VCLSTS, u4_t_sync_trgt);
            vd_s_SbltwrnTtTimAct_FM(&st_sp_sbltwrn_ttsts_fm[u4_t_seat], stp_a_VCLSTS->u4_vclsts, u4_t_ttopt, u1_t_seattyp, (U1)TRUE);
        }
    }

    for (u4_t_seat = (U4)0U; u4_t_seat < (U4)SBLTWRN_NUM_ALLSEAT; u4_t_seat++) {
        for (u4_t_loop = (U4)0U; u4_t_loop < (U4)SBLTWRN_NUM_CHMTIMER_FM; u4_t_loop++) {
            st_sp_sbltwrn_chmsts_fm[u4_t_seat].u2p_prvtimer[u4_t_loop] = st_sp_sbltwrn_chmsts_fm[u4_t_seat].u2p_timer[u4_t_loop];
        }
    }
}

/*===================================================================================================================================*/
/* static  U1      u1_s_SbltwrnTtStmVldChk_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS)     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_SbltwrnTtStmVldChk_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS)
{
    U1  u1_t_valid;

    if ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_FAILRSTEDG) != (U1)0U) {
        vd_s_SbltwrnInitTtsts_FM(&st_sp_sbltwrn_ttsts_fm[u1_a_SEATID]);
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
        vd_s_SbltwrnInitTtsts_FM(&st_sp_sbltwrn_ttsts_fm[u1_a_SEATID]);
    }

    return (u1_t_valid);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtStmCnd_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtStmCnd_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    static const U4             u4_s_CTLSTS_MSK = (U4)0x000000FFU;
    const ST_SBLTWRN_TTTYP *    stp_t_tttyp;
    U4                          u4_t_act;
    U1                          u1_t_ctlsts;
    U4                          u4_t_loop;

    u1_t_ctlsts = st_sp_sbltwrn_ttsts_fm[u1_a_SEATID].u1_ctlsts;
    if (u1_t_ctlsts >= (U1)SBLTWRN_NUM_TTSTS_FM) {
        u1_t_ctlsts = (U1)SBLTWRN_TTSTS_OFF_FM;
    }
    stp_t_tttyp = &st_sp_SBLTWRN_TTTYP_FM[u1_t_ctlsts];

    u4_t_act = (U4)SBLTWRN_TTSTS_KEEP;
    for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)stp_t_tttyp->u1_NUM_TTTYP ; u4_t_loop++){
        if (((stp_t_tttyp->st_TTSTM[u4_t_loop].u1_TYPMSK) & (U1)((U1)1U << u1_a_SEATTYP)) != (U1)0U) {
            u4_t_act = (*(stp_t_tttyp->st_TTSTM[u4_t_loop].fp_u4_STM))(u1_a_SEATID, u1_a_SEATTYP, stp_a_VCLSTS, u4_a_SYNC_TRGT);
            u1_t_ctlsts = (U1)(u4_t_act & u4_s_CTLSTS_MSK);
            if (u1_t_ctlsts < (U1)SBLTWRN_NUM_TTSTS_FM) {
                st_sp_sbltwrn_ttsts_fm[u1_a_SEATID].u1_ctlsts = u1_t_ctlsts;
                break;
            }
        }
    }

    return (u4_t_act);
}

/*===================================================================================================================================*/
/* static  void    vd_s_SbltwrnTtTimAct_FM(ST_SBLTWRN_TTST *stp_a_ttsts, const U4 u4_a_VCLSTS, U4 u4_a_ttopt, const U1 u1_a_SEATTYP, const U1 u1_a_CNT_UP)  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_SbltwrnTtTimAct_FM(ST_SBLTWRN_TTST_FM *stp_a_ttsts, const U4 u4_a_VCLSTS, U4 u4_a_ttopt, const U1 u1_a_SEATTYP, const U1 u1_a_CNT_UP)
{
    static const U4 u4_s_CNTUP_OFST = (U4)8U;
    static const U4 u4_s_CNTSTP_OFST = (U4)9U;
    static const U4 u4_s_CNTCLR_OFST = (U4)10U;
    U4  u4_t_loop;
    U4  u4_t_act_bit;
    U1 u1_t_dropn;

    u1_t_dropn  = u1_g_SbltwrnDrchk(u4_a_VCLSTS, u1_a_SEATTYP, (U1)TRUE);
    
    if (u1_t_dropn == (U1)TRUE) {
        u4_a_ttopt |= (U4)SBLTWRN_TTOPT_FDRTM_CNTCLR;
    }

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)SBLTWRN_NUM_TTTIMER_FM; u4_t_loop++) {

        /* Set/Clear SBLTWRN_CHMFLG_CNT_xxx by SBLTWRN_CHMOPT_xxx_CNTUP/STP */
        u4_t_act_bit = ((U4)1U << (u4_t_loop + u4_s_CNTUP_OFST));
        /* The maximum value of u4_t_loop is 0. The value of u4_s_CNTUP_OFST is 8.          */
        /* so (u4_t_loop + u4_s_CNTUP_OFST) is always less than U4_MAX.                     */
        if ((u4_a_ttopt & u4_t_act_bit) != (U4)0U) {
            stp_a_ttsts->u1_flg |= (U1)((U1)1U << u4_t_loop);
        }

        u4_t_act_bit = ((U4)1U << (u4_t_loop + u4_s_CNTSTP_OFST));
        /* The maximum value of u4_t_loop is 0. The value of u4_s_CNTSTP_OFST is 9.         */
        /* so (u4_t_loop + u4_s_CNTSTP_OFST) is always less than U4_MAX.                    */
        if ((u4_a_ttopt & u4_t_act_bit) != (U4)0U) {
            stp_a_ttsts->u1_flg &= ((U1)U1_MAX ^ (U1)((U1)1U << u4_t_loop));
        }

        u4_t_act_bit = ((U4)1U << (u4_t_loop + u4_s_CNTCLR_OFST));
        /* The maximum value of u4_t_loop is 0. The value of u4_s_CNTCLR_OFST is 10.        */
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
/* static  U4      u4_s_SbltwrnChimeCnd_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChimeCnd_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    static const U4 u4_s_CTLSTS_MSK = (U4)0x000000FFU;
    const ST_SBLTWRN_CHMTYP * stp_t_chm_stm;
    U4      u4_t_act;
    U4      u4_t_chmopt;
    U1      u1_t_ctlsts;
    U4      u4_t_loop;

    u1_t_ctlsts = st_sp_sbltwrn_chmsts_fm[u1_a_SEATID].u1_ctlsts;
    if (u1_t_ctlsts >= (U1)SBLTWRN_NUM_CHMSTS_FM) {
        u1_t_ctlsts = (U1)SBLTWRN_CHMSTS_OFF_FM;
    }
    stp_t_chm_stm  = &st_sp_SBLTWRN_CHMSTM_FM[u1_t_ctlsts];

    u4_t_act = (U4)SBLTWRN_CHMSTS_KEEP;
    for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)(stp_t_chm_stm->u1_NUM_CHMTYP) ; u4_t_loop++){
        u4_t_act = (stp_t_chm_stm->fp_u4_CHMTYP[u4_t_loop])(u1_a_SEATID, u1_a_SEATTYP, stp_a_VCLSTS, u2_a_SYNC_TRGT);
        u1_t_ctlsts = (U1)(u4_t_act & u4_s_CTLSTS_MSK); 
        if (u1_t_ctlsts < (U1)SBLTWRN_NUM_CHMSTS_FM) {
            st_sp_sbltwrn_chmsts_fm[u1_a_SEATID].u1_ctlsts = u1_t_ctlsts;
            break;
        }
    }

    u4_t_chmopt = u4_t_act & (U4)SBLTWRN_CHMOPT_MSK_FM;

    return (u4_t_chmopt);
}

/*===================================================================================================================================*/
/* static  void    vd_s_SbltwrnChimeTimAct_FM(ST_SBLTWRN_CHMST *stp_a_chmsts, const U4 u4_a_CHMOPT, const U1 u1_a_CNT_UP)            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_SbltwrnChimeTimAct_FM(ST_SBLTWRN_CHMST_FM *stp_a_chmsts, const U4 u4_a_CHMOPT, const U1 u1_a_CNT_UP)
{
    static const U4 u4_s_CNTUP_OFST  = (U4)8U;
    static const U4 u4_s_CNTSTP_OFST = (U4)14U;
    static const U4 u4_s_CNTCLR_OFST = (U4)20U;
    U4  u4_t_loop;
    U4  u4_t_act_bit;

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)SBLTWRN_NUM_CHMTIMER_FM; u4_t_loop++) {

        /* Set/Clear SBLTWRN_CHMFLG_CNT_xxx by SBLTWRN_CHMOPT_xxx_CNTUP/STP */
        u4_t_act_bit = ((U4)1U << (u4_t_loop + u4_s_CNTUP_OFST));
        /* The maximum value of u4_t_loop is 5. The value of u4_s_CNTUP_OFST is 8.          */
        /* so (u4_t_loop + u4_s_CNTUP_OFST) is always less than U4_MAX.                     */
        if ((u4_a_CHMOPT & u4_t_act_bit) != (U4)0U) {
            stp_a_chmsts->u1_flg |= (U1)((U1)1U << u4_t_loop);
        }

        u4_t_act_bit = ((U4)1U << (u4_t_loop + u4_s_CNTSTP_OFST));
        /* The maximum value of u4_t_loop is 5. The value of u4_s_CNTSTP_OFST is 14.        */
        /* so (u4_t_loop + u4_s_CNTSTP_OFST) is always less than U4_MAX.                    */
        if ((u4_a_CHMOPT & u4_t_act_bit) != (U4)0U) {
            stp_a_chmsts->u1_flg &= ((U1)U1_MAX ^ (U1)((U1)1U << u4_t_loop));
        }

        u4_t_act_bit = ((U4)1U << (u4_t_loop + u4_s_CNTCLR_OFST));
        /* The maximum value of u4_t_loop is 5. The value of u4_s_CNTCLR_OFST is 20.        */
        /* so (u4_t_loop + u4_s_CNTCLR_OFST) is always less than U4_MAX.                    */
        if ((u4_a_CHMOPT & u4_t_act_bit) != (U4)0U) {
            stp_a_chmsts->u2p_timer[u4_t_loop] = (U2)0U;
        }

        if (((stp_a_chmsts->u1_flg & (U1)((U1)1U << u4_t_loop)) != (U1)0U) && (u1_a_CNT_UP == (U1)TRUE)) {
            vd_g_SbltwrnTmcnt(&stp_a_chmsts->u2p_timer[u4_t_loop]);
        }
    }
    
    if (stp_a_chmsts->u2p_timer[SBLTWRN_CHMTIMER_LV2CNT] > (U2)SBLTWRN_CHMTIMER_LV2CNT_UPPER) {
        stp_a_chmsts->u2p_timer[SBLTWRN_CHMTIMER_LV2CNT] = (U2)SBLTWRN_CHMTIMER_LV2CNT_UPPER;
    }
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnChmTrns_condAB_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChmTrns_condAB_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    static const U2 u2_s_FIRST_IG_ON = (U2)1U;
    U4              u4_t_cond;

    if (((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_DS) || (u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_PS)) &&
        (stp_a_VCLSTS->u2_igontm == u2_s_FIRST_IG_ON)) {
        u4_t_cond = (U4)(SBLTWRN_CHMSTS_INIPR_FM);
    } else {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnChmTrns_condAE_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChmTrns_condAE_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U1  u1_t_dropn;

    u1_t_dropn  = u1_g_SbltwrnDrchk(stp_a_VCLSTS->u4_vclsts, u1_a_SEATTYP, (U1)TRUE);

    if ((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_RS_NOSN)                                       &&
        (u2_s_sbltwrn_legalpretmr > stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_LGLST]) && 
        ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_LOW) == (U4)0U)                  && 
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U)     && 
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKLFLG) != (U1)0U)  && 
        ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_PARK) == (U4)0U)                     && 
        (u1_t_dropn == (U1)FALSE)) {
        u4_t_cond = (U4)(SBLTWRN_CHMSTS_UNBKNT_FM | SBLTWRN_CHMOPT_UNBCKLTM_CNTCLR | SBLTWRN_CHMOPT_UNBCKLTM_CNTUP);
    } else {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnChmTrns_condAG_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChmTrns_condAG_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if (((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_DS) || (u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_PS)) &&
        ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_LOW) != (U4)0U)                     && 
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U)) {
        u4_t_cond = (U4)(SBLTWRN_CHMSTS_LV1_FM | SBLTWRN_CHMOPT_FRLV1TM_CNTCLR | SBLTWRN_CHMOPT_FRLV1TM_CNTUP);
    } else if ((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_RS_NOSN)                                   &&
        ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_LOW) != (U4)0U)                     && 
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U)        && 
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKLFLG) != (U1)0U)) {
        u4_t_cond = (U4)(SBLTWRN_CHMSTS_LV1_FM | SBLTWRN_CHMOPT_RSLV1TM_CNTCLR | SBLTWRN_CHMOPT_RSLV1TM_CNTUP);
    } else {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnChmTrns_condAH_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChmTrns_condAH_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if ((((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_DS) || (u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_PS)) &&
         ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_HIGH) != (U4)0U)                    && 
         ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U))       ||
        ((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_RS_NOSN)                                          &&
         ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_HIGH) != (U4)0U)                    && 
         ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U)        && 
         ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKLFLG) != (U1)0U))) {
        u4_t_cond = (U4)(SBLTWRN_CHMSTS_LV2_FM | 
                         SBLTWRN_CHMOPT_LV2CNTTM_CNTCLR | 
                         SBLTWRN_CHMOPT_LV2CNTTM_CNTUP | 
                         SBLTWRN_CHMOPT_RSLV2TM_CNTCLR | 
                         SBLTWRN_CHMOPT_RSLV2TM_CNTUP);
    } else {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnChmTrns_condBA_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChmTrns_condBA_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if (((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_DS) &&
         (u2_s_sbltwrn_legalpretmr > stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_LGLST]) &&
         ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) == (U1)0U)) ||
        ((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_PS) &&
         (stp_a_VCLSTS->u2_igontm > (U2)SBLTWRN_TIM_INITIALPR_PS) &&
         ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) == (U1)0U))) {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_OFF_FM;
    } else {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnChmTrns_condBC_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChmTrns_condBC_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if (((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_DS) || (u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_PS)) &&
        (u2_s_sbltwrn_legalpretmr > stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_LGLST]) && 
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U)) {
        u4_t_cond = (U4)(SBLTWRN_CHMSTS_INITIAL_FM | SBLTWRN_CHMOPT_INITIALTM_CNTCLR | SBLTWRN_CHMOPT_INITIALTM_CNTUP);
    }
    else {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnChmTrns_condCA_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChmTrns_condCA_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if (((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_DS) || (u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_PS)) &&
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) == (U1)0U)) {
        u4_t_cond = (U4)(SBLTWRN_CHMSTS_OFF_FM | SBLTWRN_CHMOPT_INITIALTM_CNTCLR | SBLTWRN_CHMOPT_INITIALTM_CNTSTP);
    } else {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnChmTrns_condCD_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChmTrns_condCD_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if (((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_DS) || (u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_PS)) &&
        (st_sp_sbltwrn_chmsts_fm[u1_a_SEATID].u2p_timer[SBLTWRN_CHMTIMER_INITIAL] >= stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_INITIAL]) && 
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U)) {
        u4_t_cond = (U4)(SBLTWRN_CHMSTS_INICMP_FM | SBLTWRN_CHMOPT_INITIALTM_CNTCLR | SBLTWRN_CHMOPT_INITIALTM_CNTSTP);
    } else {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnChmTrns_condCG_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChmTrns_condCG_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if (((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_DS) || (u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_PS)) &&
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U)        &&
        ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_LOW) != (U4)0U)) {
        u4_t_cond = (U4)(SBLTWRN_CHMSTS_LV1_FM | 
                         SBLTWRN_CHMOPT_INITIALTM_CNTCLR | 
                         SBLTWRN_CHMOPT_INITIALTM_CNTSTP | 
                         SBLTWRN_CHMOPT_FRLV1TM_CNTCLR | 
                         SBLTWRN_CHMOPT_FRLV1TM_CNTUP);
    } else {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnChmTrns_condDA_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChmTrns_condDA_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if (((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_DS) || (u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_PS)) &&
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) == (U1)0U)) {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_OFF_FM;
    } else {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnChmTrns_condDG_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChmTrns_condDG_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if (((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_DS) || (u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_PS)) &&
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U)        &&
        ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_LOW) != (U4)0U)) {
        u4_t_cond = (U4)(SBLTWRN_CHMSTS_LV1_FM | SBLTWRN_CHMOPT_FRLV1TM_CNTCLR | SBLTWRN_CHMOPT_FRLV1TM_CNTUP);
    } else {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnChmTrns_condEA_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChmTrns_condEA_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U1 u1_t_dropn;

    u1_t_dropn  = u1_g_SbltwrnDrchk(stp_a_VCLSTS->u4_vclsts, u1_a_SEATTYP, (U1)TRUE);
    
    if ((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_RS_NOSN) && 
        (((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) == (U1)0U) || 
        (((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_STP_OVER) == (U4)0U) && 
        (u1_t_dropn == (U1)TRUE)))) {
        u4_t_cond = (U4)(SBLTWRN_CHMSTS_OFF_FM | SBLTWRN_CHMOPT_UNBCKLTM_CNTCLR | SBLTWRN_CHMOPT_UNBCKLTM_CNTSTP);
    } else {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_KEEP;
    }
    
    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnChmTrns_condEF_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChmTrns_condEF_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if ((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_RS_NOSN)                                   &&
        ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_LOW) == (U4)0U)              && 
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U) && 
        (st_sp_sbltwrn_chmsts_fm[u1_a_SEATID].u2p_timer[SBLTWRN_CHMTIMER_UNBCKL] >= stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_UNBCKL])) {
        u4_t_cond = (U4)(SBLTWRN_CHMSTS_UNBKCMP_FM | SBLTWRN_CHMOPT_UNBCKLTM_CNTSTP);
    } else {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnChmTrns_condEG_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChmTrns_condEG_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if (((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_RS_NOSN))                    && 
        ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_LOW) != (U4)0U) && 
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U)) {
        u4_t_cond = (U4)(SBLTWRN_CHMSTS_LV1_FM | 
                         SBLTWRN_CHMOPT_UNBCKLTM_CNTCLR | 
                         SBLTWRN_CHMOPT_UNBCKLTM_CNTSTP | 
                         SBLTWRN_CHMOPT_RSLV1TM_CNTCLR | 
                         SBLTWRN_CHMOPT_RSLV1TM_CNTUP);
    } else {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnChmTrns_condFA_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChmTrns_condFA_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U1 u1_t_dropn;

    u1_t_dropn  = u1_g_SbltwrnDrchk(stp_a_VCLSTS->u4_vclsts, u1_a_SEATTYP, (U1)TRUE);

    if ((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_RS_NOSN) && 
        (((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) == (U1)0U) || 
        (((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_STP_OVER) == (U4)0U) && 
        (u1_t_dropn == (U1)TRUE)))) {
        u4_t_cond = (U4)(SBLTWRN_CHMSTS_OFF_FM | SBLTWRN_CHMOPT_UNBCKLTM_CNTCLR);
    } else {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_KEEP;
    }
    
    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnChmTrns_condFG_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChmTrns_condFG_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if (((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_RS_NOSN))                    && 
        ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_LOW) != (U4)0U) && 
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U)) {
        u4_t_cond = (U4)(SBLTWRN_CHMSTS_LV1_FM | 
                         SBLTWRN_CHMOPT_UNBCKLTM_CNTCLR | 
                         SBLTWRN_CHMOPT_RSLV1TM_CNTCLR | 
                         SBLTWRN_CHMOPT_RSLV1TM_CNTUP);
    } else {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnChmTrns_condGA_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChmTrns_condGA_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U1 u1_t_dropn;

    u1_t_dropn  = u1_g_SbltwrnDrchk(stp_a_VCLSTS->u4_vclsts, u1_a_SEATTYP, (U1)TRUE);

    if ((((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_DS) || (u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_PS) || (u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_RS_NOSN)) && 
         ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) == (U1)0U)) || 
        ((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_RS_NOSN) && 
         ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_STP_OVER) == (U4)0U) && 
         (u1_t_dropn == (U1)TRUE))) {
        u4_t_cond = (U4)(SBLTWRN_CHMSTS_OFF_FM | 
                         SBLTWRN_CHMOPT_FRLV1TM_CNTCLR | 
                         SBLTWRN_CHMOPT_FRLV1TM_CNTSTP | 
                         SBLTWRN_CHMOPT_RSLV1TM_CNTCLR | 
                         SBLTWRN_CHMOPT_RSLV1TM_CNTSTP);
    } else {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_KEEP;
    }
    
    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnChmTrns_condGH_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChmTrns_condGH_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    U4  u4_t_cond;

        if ((((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_DS) || (u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_PS) || (u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_RS_NOSN)) &&
             ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_HIGH) != (U4)0U) && 
             ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U)) || 
            (((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_DS) || (u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_PS)) && 
             ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U) && 
             (st_sp_sbltwrn_chmsts_fm[u1_a_SEATID].u2p_timer[SBLTWRN_CHMTIMER_FRLV1] >= stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_LV1])) || 
            ((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_RS_NOSN) && 
             ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U) && 
             (st_sp_sbltwrn_chmsts_fm[u1_a_SEATID].u2p_timer[SBLTWRN_CHMTIMER_RSLV1] >= stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_LV1]))) {
        u4_t_cond = (U4)(SBLTWRN_CHMSTS_LV2_FM | 
                         SBLTWRN_CHMOPT_FRLV1TM_CNTCLR | 
                         SBLTWRN_CHMOPT_FRLV1TM_CNTSTP | 
                         SBLTWRN_CHMOPT_RSLV1TM_CNTCLR | 
                         SBLTWRN_CHMOPT_RSLV1TM_CNTSTP | 
                         SBLTWRN_CHMOPT_LV2CNTTM_CNTCLR | 
                         SBLTWRN_CHMOPT_LV2CNTTM_CNTUP | 
                         SBLTWRN_CHMOPT_RSLV2TM_CNTCLR | 
                         SBLTWRN_CHMOPT_RSLV2TM_CNTUP);
    } else {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnChmTrns_condHA_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChmTrns_condHA_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U1 u1_t_dropn;

    u1_t_dropn  = u1_g_SbltwrnDrchk(stp_a_VCLSTS->u4_vclsts, u1_a_SEATTYP, (U1)TRUE);

    if ((((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_DS) || (u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_PS) || (u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_RS_NOSN)) && 
         ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) == (U1)0U)) || 
        ((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_RS_NOSN) && 
         ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_STP_OVER) == (U4)0U) && 
         (u1_t_dropn == (U1)TRUE))) {
        u4_t_cond = (U4)(SBLTWRN_CHMSTS_OFF_FM | 
                         SBLTWRN_CHMOPT_LV2CNTTM_CNTCLR | 
                         SBLTWRN_CHMOPT_LV2CNTTM_CNTSTP | 
                         SBLTWRN_CHMOPT_RSLV2TM_CNTCLR | 
                         SBLTWRN_CHMOPT_RSLV2TM_CNTSTP);
    } else {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnChmTrns_condHI_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChmTrns_condHI_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if ((((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_DS) || (u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_PS)) && 
         ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_STP_OVER) == (U4)0U)                && 
         ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U)        && 
         (st_sp_sbltwrn_chmsts_fm[u1_a_SEATID].u2p_timer[SBLTWRN_CHMTIMER_LV2CNT] >= stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_LV2CNT])) || 
        ((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_RS_NOSN)                                          && 
         ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_STP_OVER) == (U4)0U)                && 
         ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U)        && 
         (st_sp_sbltwrn_chmsts_fm[u1_a_SEATID].u2p_timer[SBLTWRN_CHMTIMER_LV2CNT] >= stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_LV2CNT]) && 
         (st_sp_sbltwrn_chmsts_fm[u1_a_SEATID].u2p_timer[SBLTWRN_CHMTIMER_RSLV2] < stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_LV2]))) {
        u4_t_cond = (U4)(SBLTWRN_CHMSTS_L2INT_FM | SBLTWRN_CHMOPT_LV2CNTTM_CNTSTP | SBLTWRN_CHMOPT_RSLV2TM_CNTSTP);
    } else {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnChmTrns_condHJ_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChmTrns_condHJ_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if ((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_RS_NOSN)                                          &&
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U)        && 
        (st_sp_sbltwrn_chmsts_fm[u1_a_SEATID].u2p_timer[SBLTWRN_CHMTIMER_RSLV2] >= stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_LV2])) {
        u4_t_cond = (U4)(SBLTWRN_CHMSTS_L2CMP_FM | 
                         SBLTWRN_CHMOPT_LV2CNTTM_CNTCLR | 
                         SBLTWRN_CHMOPT_LV2CNTTM_CNTSTP | 
                         SBLTWRN_CHMOPT_RSLV2TM_CNTCLR | 
                         SBLTWRN_CHMOPT_RSLV2TM_CNTSTP);
    } else {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnChmTrns_condIA_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChmTrns_condIA_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U1 u1_t_dropn;

    u1_t_dropn  = u1_g_SbltwrnDrchk(stp_a_VCLSTS->u4_vclsts, u1_a_SEATTYP, (U1)TRUE);

    if ((((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_DS) || (u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_PS) || (u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_RS_NOSN)) &&
         ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) == (U1)0U)) ||
        ((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_RS_NOSN) &&
         ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_STP_OVER) == (U4)0U) && 
         (u1_t_dropn == (U1)TRUE))) {
            u4_t_cond = (U4)(SBLTWRN_CHMSTS_OFF_FM | SBLTWRN_CHMOPT_LV2CNTTM_CNTCLR | SBLTWRN_CHMOPT_RSLV2TM_CNTCLR);
    } else {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnChmTrns_condIH_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChmTrns_condIH_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    U4      u4_t_cond;

    if (((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_DS) || (u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_PS) || (u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_RS_NOSN)) &&
        ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_LOW) != (U4)0U) && 
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U)) {
        u4_t_cond = (U4)(SBLTWRN_CHMSTS_LV2_FM | SBLTWRN_CHMOPT_LV2CNTTM_CNTUP | SBLTWRN_CHMOPT_RSLV2TM_CNTUP);
    } else {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnChmTrns_condJA_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnChmTrns_condJA_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U1 u1_t_dropn;

    u1_t_dropn  = u1_g_SbltwrnDrchk(stp_a_VCLSTS->u4_vclsts, u1_a_SEATTYP, (U1)TRUE);
    
    if ((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_RS_NOSN) &&
        (((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) == (U1)0U) ||
         (((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_STP_OVER) == (U4)0U) && 
          (u1_t_dropn == (U1)TRUE)))) {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_OFF_FM;
    } else {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condAB_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condAB_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    static const U2 u2_s_FIRST_IG_ON = (U2)1U;
    U4              u4_t_cond;

    if (stp_a_VCLSTS->u2_igontm == u2_s_FIRST_IG_ON) {
        u4_t_cond = (U4)SBLTWRN_TTSTS_INIPR_FM;
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condAE_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condAE_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    /* First 'Undetermined -> Unbuckled' Edge since IG-ON */
    if (
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_FIXUNBKL) != (U1)0U) &&
        (stp_a_VCLSTS->u2_igontm <= (stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_IGON] + (U2)SBLTWRN_TT_IGONTM_OFST))
        ) {
        u4_t_cond = (U4)SBLTWRN_TTSTS_IGON_FM;
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condAF_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condAF_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U1 u1_t_dropn;

    u1_t_dropn  = u1_g_SbltwrnDrchk(stp_a_VCLSTS->u4_vclsts, u1_a_SEATTYP, (U1)TRUE);
   
    if (
        ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_STP_OVER) == (U4)0U) && 
        (u1_t_dropn == (U1)TRUE) &&             /* some rear door(s) open */
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U)     /* unbucked               */
        ) {
        u4_t_cond = (U4)(SBLTWRN_TTSTS_DOOR_FM | SBLTWRN_TTOPT_FDRTM_CNTCLR | SBLTWRN_TTOPT_FDRTM_CNTUP);
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condAG_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condAG_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U1 u1_t_dropn;

    u1_t_dropn  = u1_g_SbltwrnDrchk(stp_a_VCLSTS->u4_vclsts, u1_a_SEATTYP, (U1)TRUE);

    if ((((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_DS) || (u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_PS)) &&
         ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_LOW) == (U4)0U) && 
         ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U)) || 
        ((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_RS_NOSN) &&
         ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_LOW) == (U4)0U) && 
         ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U) && 
         (u1_t_dropn == (U1)FALSE) && 
         ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKLFLG) != (U1)0U))) {
        u4_t_cond = (U4)SBLTWRN_TTSTS_UNBKNT_FM;
    } else {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_KEEP;
    }
    
    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condAH_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condAH_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if ((((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_DS) || (u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_PS)) &&
         ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_LOW) != (U4)0U) && 
         ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U)) || 
        ((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_RS_NOSN) &&
         ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_LOW) != (U4)0U) && 
         ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U) && 
         ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKLFLG) != (U1)0U))) {
        u4_t_cond = (U4)SBLTWRN_TTSTS_LV1_FM;
    } else {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_KEEP;
    }

    return (u4_t_cond);

}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condAI_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condAI_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if ((((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_DS) || (u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_PS)) &&
         ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_HIGH) != (U4)0U) && 
         ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U)) || 
        ((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_RS_NOSN) &&
         ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_HIGH) != (U4)0U) && 
         ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U) && 
         ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKLFLG) != (U1)0U))) {
        u4_t_cond = (U4)SBLTWRN_TTSTS_LV2_FM;
    } else {
        u4_t_cond = (U4)SBLTWRN_CHMSTS_KEEP;
    }

    return (u4_t_cond);

}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condXtoA_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condXtoA_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) == (U1)0U) {
        u4_t_cond = (U4)SBLTWRN_TTSTS_OFF_FM;
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condBA_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condBA_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if (((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_DS) &&
         (u2_s_sbltwrn_legalpretmr > stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_LGLST]) &&
         ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) == (U1)0U)) ||
        ((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_PS) &&
         (stp_a_VCLSTS->u2_igontm > (U2)SBLTWRN_TIM_INITIALPR_PS) &&
         ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) == (U1)0U))) {
        u4_t_cond = (U4)SBLTWRN_TTSTS_OFF_FM;
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condBC_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condBC_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if ((u2_s_sbltwrn_legalpretmr > stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_LGLST]) && 
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U)) {
        u4_t_cond = (U4)SBLTWRN_TTSTS_INITIAL_FM;
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condCD_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condCD_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if ((st_sp_sbltwrn_chmsts_fm[u1_a_SEATID].u2p_prvtimer[SBLTWRN_CHMTIMER_INITIAL] >= stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_INITIAL]) && 
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U)) {
        u4_t_cond = (U4)SBLTWRN_TTSTS_INICMP_FM;
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condCH_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condCH_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if (((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U) && 
        ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_LOW) != (U4)0U)) {
        u4_t_cond = (U4)SBLTWRN_TTSTS_LV1_FM;
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condDH_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condDH_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if (((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U) && 
        ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_LOW) != (U4)0U)) {
        u4_t_cond = (U4)SBLTWRN_TTSTS_LV1_FM;
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condEA_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condEA_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if (
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) == (U1)0U) ||
        (stp_a_VCLSTS->u2_igontm > (stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_IGON] + (U2)SBLTWRN_TT_IGONTM_OFST))) {
        u4_t_cond = (U4)SBLTWRN_TTSTS_OFF_FM;
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condEF_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condEF_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U1 u1_t_dropn;

    u1_t_dropn  = u1_g_SbltwrnDrchk(stp_a_VCLSTS->u4_vclsts, u1_a_SEATTYP, (U1)TRUE);

    if (
        ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_STP_OVER) == (U4)0U) && 
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U) &&
        (u1_t_dropn == (U1)TRUE)) {
        u4_t_cond = (U4)(SBLTWRN_TTSTS_DOOR_FM | SBLTWRN_TTOPT_FDRTM_CNTCLR | SBLTWRN_TTOPT_FDRTM_CNTUP);
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condFA_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condFA_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if (
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) == (U1)0U) || 
        (st_sp_sbltwrn_ttsts_fm[u1_a_SEATID].u2p_timer[SBLTWRN_TTTIMER_FDOR] >= stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_DOOR])) {
        u4_t_cond = (U4)(SBLTWRN_TTSTS_OFF_FM | SBLTWRN_TTOPT_FDRTM_CNTCLR | SBLTWRN_TTOPT_FDRTM_CNTSTP);
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condGF_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condGF_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U1 u1_t_dropn;

    u1_t_dropn  = u1_g_SbltwrnDrchk(stp_a_VCLSTS->u4_vclsts, u1_a_SEATTYP, (U1)TRUE);
    
    if (((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_STP_OVER) == (U4)0U) && 
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U) && (u1_t_dropn == (U1)TRUE)) {
        u4_t_cond = (U4)(SBLTWRN_TTSTS_DOOR_FM | SBLTWRN_TTOPT_FDRTM_CNTCLR | SBLTWRN_TTOPT_FDRTM_CNTUP);
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condGH_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condGH_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if (((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_LOW) != (U4)0U) && 
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U)) {
        u4_t_cond = (U4)SBLTWRN_TTSTS_LV1_FM;
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condHF_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condHF_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U1 u1_t_dropn;

    u1_t_dropn  = u1_g_SbltwrnDrchk(stp_a_VCLSTS->u4_vclsts, u1_a_SEATTYP, (U1)TRUE);

    if (((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_STP_OVER) == (U4)0U) && 
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U) && (u1_t_dropn == (U1)TRUE)) {
        u4_t_cond = (U4)(SBLTWRN_TTSTS_DOOR_FM | SBLTWRN_TTOPT_FDRTM_CNTCLR | SBLTWRN_TTOPT_FDRTM_CNTUP);
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condHI_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condHI_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if ((((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_HIGH) != (U4)0U) && 
         ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U)) || 
        (((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_DS) || (u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_PS)) &&
         ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U) && 
         (st_sp_sbltwrn_chmsts_fm[u1_a_SEATID].u2p_prvtimer[SBLTWRN_CHMTIMER_FRLV1] >= stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_LV1])) || 
        ((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_RS_NOSN) &&
         ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U) && 
         (st_sp_sbltwrn_chmsts_fm[u1_a_SEATID].u2p_prvtimer[SBLTWRN_CHMTIMER_RSLV1] >= stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_LV1]))) {
        u4_t_cond = (U4)SBLTWRN_TTSTS_LV2_FM;
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condIF_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condIF_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U1 u1_t_dropn;

    u1_t_dropn  = u1_g_SbltwrnDrchk(stp_a_VCLSTS->u4_vclsts, u1_a_SEATTYP, (U1)TRUE);

    if (((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_STP_OVER) == (U4)0U) && 
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U) &&
        (u1_t_dropn == (U1)TRUE)) {
        u4_t_cond = (U4)(SBLTWRN_TTSTS_DOOR_FM | SBLTWRN_TTOPT_FDRTM_CNTCLR | SBLTWRN_TTOPT_FDRTM_CNTUP);
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condIJ_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condIJ_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if ((((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_DS) || (u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_PS)) &&
         ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_STP_OVER) == (U4)0U) && 
         ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U) && 
         (st_sp_sbltwrn_chmsts_fm[u1_a_SEATID].u2p_prvtimer[SBLTWRN_CHMTIMER_LV2CNT] >= stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_LV2CNT])) || 
        (((u1_a_SEATTYP == (U1)SBLTWRN_SEATTYP_RS_NOSN)) &&
         ((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_STP_OVER) == (U4)0U) && 
         ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U) && 
         (st_sp_sbltwrn_chmsts_fm[u1_a_SEATID].u2p_prvtimer[SBLTWRN_CHMTIMER_LV2CNT] >= stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_LV2CNT]) && 
         (st_sp_sbltwrn_chmsts_fm[u1_a_SEATID].u2p_prvtimer[SBLTWRN_CHMTIMER_RSLV2] < stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_LV2]))) {
        u4_t_cond = (U4)SBLTWRN_TTSTS_L2INT_FM;
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condIK_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condIK_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if (((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U) && 
        (st_sp_sbltwrn_chmsts_fm[u1_a_SEATID].u2p_prvtimer[SBLTWRN_CHMTIMER_RSLV2] >= stp_a_VCLSTS->stp_wrnprm[u1_a_SEATTYP].u2p_tim[SBLTWRN_TIM_LV2])) {
        u4_t_cond = (U4)SBLTWRN_TTSTS_L2CMP_FM;
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condJF_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condJF_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U1 u1_t_dropn;

    u1_t_dropn  = u1_g_SbltwrnDrchk(stp_a_VCLSTS->u4_vclsts, u1_a_SEATTYP, (U1)TRUE);

    if (((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_STP_OVER) == (U4)0U) && 
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U) &&
        (u1_t_dropn == (U1)TRUE)) {
        u4_t_cond = (U4)(SBLTWRN_TTSTS_DOOR_FM | SBLTWRN_TTOPT_FDRTM_CNTCLR | SBLTWRN_TTOPT_FDRTM_CNTUP);
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condJI_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condJI_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;

    if (((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_LOW) != (U4)0U) && 
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U)) {
        u4_t_cond = (U4)SBLTWRN_TTSTS_LV2_FM;
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltwrnTtTrns_condKF_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltwrnTtTrns_condKF_FM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT)
{
    U4  u4_t_cond;
    U1 u1_t_dropn;

    u1_t_dropn  = u1_g_SbltwrnDrchk(stp_a_VCLSTS->u4_vclsts, u1_a_SEATTYP, (U1)TRUE);

    if (((stp_a_VCLSTS->u4_vclsts & (U4)SBLTWRN_VCLSTS_SPD_STP_OVER) == (U4)0U) && 
        ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_UNBCKL) != (U1)0U) && (u1_t_dropn == (U1)TRUE)) {
        u4_t_cond = (U4)(SBLTWRN_TTSTS_DOOR_FM | SBLTWRN_TTOPT_FDRTM_CNTCLR | SBLTWRN_TTOPT_FDRTM_CNTUP);
    } else {
        u4_t_cond = (U4)SBLTWRN_TTSTS_KEEP;
    }

    return (u4_t_cond);
}

/*===================================================================================================================================*/
/* static  void    vd_s_SbltwrnInitChmsts_FM(ST_SBLTWRN_CHMST *stp_a_chmsts)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_SbltwrnInitChmsts_FM(ST_SBLTWRN_CHMST_FM *stp_a_chmsts)
{
    stp_a_chmsts->u1_ctlsts = (U1)SBLTWRN_CHMSTS_OFF_FM;
    stp_a_chmsts->u1_flg    = (U1)0U;
    vd_g_MemfillU2(&stp_a_chmsts->u2p_timer[0], (U2)0U, (U4)SBLTWRN_NUM_CHMTIMER_FM);
    vd_g_MemfillU2(&stp_a_chmsts->u2p_prvtimer[0], (U2)0U, (U4)SBLTWRN_NUM_CHMTIMER_FM);
}

/*===================================================================================================================================*/
/* static  void    vd_s_SbltwrnInitTtsts_FM(ST_SBLTWRN_TTST *stp_t_ttsts)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_SbltwrnInitTtsts_FM(ST_SBLTWRN_TTST_FM *stp_a_ttsts)
{
    stp_a_ttsts->u1_ctlsts      = (U1)SBLTWRN_TTSTS_OFF_FM;
    stp_a_ttsts->u1_flg         = (U1)0U;
    vd_g_MemfillU2(&stp_a_ttsts->u2p_timer[0], (U2)0U, (U4)SBLTWRN_NUM_TTTIMER_FM);
}

/*===================================================================================================================================*/
/* static  void    vd_s_SbltwrnSbrBzrChgDet_FM(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_SbltwrnSbrBzrChgDet_FM(void)
{
    U4          u4_t_lpcnt;
    U1          u1_t_no_logging;

    u1_t_no_logging = (U1)FALSE;

    for (u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)SBLTWRN_NUM_3ROWSEAT; u4_t_lpcnt++) {
        if ((u1_sp_sbltwrn_sbr_oldsts_fm[u4_t_lpcnt] != (U1)SBLTWRN_CHMSTS_OFF_FM    ) &&
            (u1_sp_sbltwrn_sbr_oldsts_fm[u4_t_lpcnt] != (U1)SBLTWRN_CHMSTS_INIPR_FM  ) &&
            (u1_sp_sbltwrn_sbr_oldsts_fm[u4_t_lpcnt] != (U1)SBLTWRN_CHMSTS_INITIAL_FM) &&
            (u1_sp_sbltwrn_sbr_oldsts_fm[u4_t_lpcnt] != (U1)SBLTWRN_CHMSTS_INICMP_FM ) &&
            (u1_sp_sbltwrn_sbr_oldsts_fm[u4_t_lpcnt] != (U1)SBLTWRN_CHMSTS_UNBKCMP_FM) &&
            (u1_sp_sbltwrn_sbr_oldsts_fm[u4_t_lpcnt] != (U1)SBLTWRN_CHMSTS_L2INT_FM  ) &&
            (u1_sp_sbltwrn_sbr_oldsts_fm[u4_t_lpcnt] != (U1)SBLTWRN_CHMSTS_L2CMP_FM  )) {
            u1_t_no_logging = (U1)TRUE;
        }
        u1_sp_sbltwrn_sbr_oldsts_fm[u4_t_lpcnt] = st_sp_sbltwrn_chmsts_fm[u4_t_lpcnt].u1_ctlsts;
    }

    if (u1_t_no_logging == (U1)FALSE) {
        for (u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)SBLTWRN_NUM_3ROWSEAT; u4_t_lpcnt++) {
            if ((st_sp_sbltwrn_chmsts_fm[u4_t_lpcnt].u1_ctlsts == (U1)SBLTWRN_CHMSTS_UNBKNT_FM) ||
                (st_sp_sbltwrn_chmsts_fm[u4_t_lpcnt].u1_ctlsts == (U1)SBLTWRN_CHMSTS_LV1_FM   ) ||
                (st_sp_sbltwrn_chmsts_fm[u4_t_lpcnt].u1_ctlsts == (U1)SBLTWRN_CHMSTS_LV2_FM   )) {
                u1_sp_sbltwrn_sbrbit_fm[st_gp_SBLTWRN_SBR_STSTBL[u4_t_lpcnt].u1_idx] |= st_gp_SBLTWRN_SBR_STSTBL[u4_t_lpcnt].u1_wrtbit;
            }
        }
    }
}

/*===================================================================================================================================*/
/* void    vd_g_GetSbltwrnSbrbit(U1 *u1_ap_sbrbit)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GetSbltwrnSbrbit(U1 *u1_ap_sbrbit)
{
    U4          u4_t_loop;

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)SBLTWRN_SBRBIT_IDX_ALL; u4_t_loop++) {
        u1_ap_sbrbit[u4_t_loop] = u1_sp_sbltwrn_sbrbit_fm[u4_t_loop];
    }
}

/*===================================================================================================================================*/
/* void    vd_g_SetSbltwrnSbrbit(U1 *u1_ap_sbrbit)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_SetSbltwrnSbrbit(U1 *u1_ap_sbrbit)
{
    U4          u4_t_loop;

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)SBLTWRN_SBRBIT_IDX_ALL; u4_t_loop++) {
        u1_sp_sbltwrn_sbrbit_fm[u4_t_loop] = u1_ap_sbrbit[u4_t_loop];
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
/*  3.0.0    09/02/2025  NA       New.  Legal compliance.(FMVSS208_2025 SBR regulations)                                             */
/*  3.1.0    01/22/2026  NA       Change state transition condition in FMVSS operation (Buzzer BA, Telltale ba)                      */
/*                                                                                                                                   */
/*  * NA     = Nazirul Afham, PXT                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
