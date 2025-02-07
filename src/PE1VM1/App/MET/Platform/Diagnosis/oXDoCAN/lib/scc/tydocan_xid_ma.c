/* 1.2.4 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Toyota Diag on CAN XID / Message Authentication                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDOCAN_XID_MA_C_MAJOR                   (1U)
#define TYDOCAN_XID_MA_C_MINOR                   (2U)
#define TYDOCAN_XID_MA_C_PATCH                   (4U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxdocan_cfg_private.h"
#if ((defined(BSW_BSWM_CS_CFG_FUNC_CS)     ) && \
     (defined(BSW_BSWM_CS_CFG_FUNC_SECOC)  ) && \
     (BSW_BSWM_CS_CFG_FUNC_CS    == BSW_USE) && \
     (BSW_BSWM_CS_CFG_FUNC_SECOC == BSW_USE))
#include "tydocan_xid_ma_cfg_private.h"
#include "tydocan_evlog_cfg_private.h"
#include "oxdocan_aubif.h"
#endif /* #if ((defined(BSW_BSWM_CS_CFG_FUNC_CS)  ) && .. */

#include "Csm.h"
#include "Mscd.h"

#include "oxdocan_aubif_ma.h"

#include "veh_opemd.h"
#if 0   /* BEV BSW provisionally */
#else
#include "veh_opemd_xmode_STUB.h"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (TYDOCAN_XID_MA_C_MAJOR != OXDOCAN_CFG_H_MAJOR)
#error "tydocan_xid_ma.c and oxdocan_cfg_private.h : source and header files are inconsistent!"
#endif

#if (TYDOCAN_XID_MA_C_MAJOR != OXDOCAN_AUBIF_MA_H_MAJOR)
#error "tydocan_xid_ma.c and oxdocan_aubif_ma.h : source and header files are inconsistent!"
#endif

#ifdef TYDOCAN_XID_MA_CFG_H
#if ((TYDOCAN_XID_MA_C_MAJOR != TYDOCAN_XID_MA_CFG_H_MAJOR) || \
     (TYDOCAN_XID_MA_C_MINOR != TYDOCAN_XID_MA_CFG_H_MINOR) || \
     (TYDOCAN_XID_MA_C_PATCH != TYDOCAN_XID_MA_CFG_H_PATCH))
#error "tydocan_xid_ma.c and tydocan_xid_ma_cfg_private.h : source and header files are inconsistent!"
#endif
#endif /* #ifdef TYDOCAN_XID_MA_CFG_H */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*      1234567890123456789012345678901 */
#define TYDC_MAK_UV_EAS_CHK_SES                  (0x01U)  /* Session Transition Event */
#define TYDC_MAK_UV_EAS_CHK_TOUT                 (0x02U)

#define TYDC_MAK_UV_ACK_INA                      (0x00U)
#define TYDC_MAK_UV_ACK_SUC                      (0x04U)
#define TYDC_MAK_UV_ACK_FAI                      (0x08U)

#define TYDC_MAK_UV_NUM_CTRL                     (4U)
#define TYDC_MAK_UV_CTRL_STA                     (0U)
#define TYDC_MAK_UV_CTRL_RUN                     (1U)
#define TYDC_MAK_UV_CTRL_FIN                     (2U)
#define TYDC_MAK_UV_CTRL_INA                     (3U)

#define TYDC_MAK_UV_ACT_TO_ACT                   (0U)
#define TYDC_MAK_UV_ACT_TO_FIN                   (1U)
#define TYDC_MAK_UV_ACT_TO_SUC                   (2U)
#define TYDC_MAK_UV_ACT_TO_FAI                   (3U)
#define TYDC_MAK_UV_ACT_STA                      (4U)
#define TYDC_MAK_UV_ACT_RUN                      (5U)
#define TYDC_MAK_UV_ACT_FIN                      (6U)

#define TYDC_MAK_UV_NUM_STM                      (48U)  /* TYDC_MAK_UV_NUM_CTRL(4U) *         */
                                                        /* TYDC_MAK_UV_EAS_CHK_MAX(12) = 48U  */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_MAK_SU_FAC_MAX                      (5U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_MAK_UV_RID_D904                     (0U)
#define TYDC_MAK_UV_RID_D902                     (1U)
#define TYDC_MAK_UV_RID_D903                     (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_KZK_RXC_MAX                         (3U)
#define TYDC_KZK_RXTO_MAX                        (0xfffeU)

#define TYDC_KZK_RX_NUM_PDU                      (8U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_RID_D904_ANS_INA                    (0x00U)
#define TYDC_RID_D904_ANS_RUN                    (0x01U)
#define TYDC_RID_D904_ANS_SUC                    (0x02U)
#define TYDC_RID_D904_ANS_FAI                    (0x03U)
     
#define TYDC_RID_D904_ANS_RINFO                  (0x03U)
#define TYDC_RID_D902_ANS_RINFO                  (0x03U)
#define TYDC_RID_D903_ANS_RINFO                  (0x03U)

#define TYDC_RID_D903_US_BLO                     (0x00U)
#define TYDC_RID_D903_US_MAC                     (0x01U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_MAK_HREC_NUM_CTRL                   (4U)
#define TYDC_MAK_HREC_CTRL_STA                   (0U)
#define TYDC_MAK_HREC_CTRL_RUN                   (1U)
#define TYDC_MAK_HREC_CTRL_FIN                   (2U)
#define TYDC_MAK_HREC_CTRL_INA                   (3U)

#define TYDC_MAK_HREC_FCT1_RTN                   (0x01U)
#define TYDC_MAK_HREC_FCT1_CNF                   (0x02U)
#define TYDC_MAK_HREC_FCT1_PRC                   (0x04U)
#define TYDC_MAK_HREC_FCT1_FIN                   (0x08U)

#define TYDC_MAK_HREC_FCT2_IGP                   (0x10U)
#define TYDC_MAK_HREC_FCT2_IGR                   (0x20U)
#define TYDC_MAK_HREC_FCT2_ACC                   (0x40U)

#define TYDC_MAK_HREC_FCT3_CNF                   (0x01U)
#define TYDC_MAK_HREC_FCT3_PRC                   (0x02U)
#define TYDC_MAK_HREC_FCT3_TMO                   (0x04U)

#define TYDC_MAK_HREC_FCT4_STA                   (0x10U)
#define TYDC_MAK_HREC_FCT4_RST                   (0x20U)

#define TYDC_KZK_RX_CNT_IDX01                    (0U)
#define TYDC_KZK_RX_CNT_IDX02                    (1U)
#define TYDC_KZK_RX_CNT_IDX03                    (2U)
#define TYDC_KZK_RX_CNT_IDX04                    (3U)
#define TYDC_KZK_RX_CNT_IDX05                    (4U)
#define TYDC_KZK_RX_CNT_IDX06                    (5U)
#define TYDC_KZK_RX_CNT_IDX07                    (6U)
#define TYDC_KZK_RX_CNT_IDX08                    (7U)
#define TYDC_KZK_RX_CNT_MAX                      (0x0AU)

#ifdef TYDOCAN_EVLOG_CFG_H
#define TYDC_SEC_MACVRFY_JOBID                   (SECOC_JOBID_2_MSG_TBL_IDX_MAX)
#define TYDC_SEC_ENCRYPTO_JOBID                  (SECOC_JOBID_2_MSG_TBL_IDX_MAX + 1U)
#else /* #ifdef TYDOCAN_EVLOG_CFG_H */
#define TYDC_SEC_MACVRFY_JOBID                   (0U)
#define TYDC_SEC_ENCRYPTO_JOBID                  (1U)
#endif  /* #ifdef TYDOCAN_EVLOG_CFG_H */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_CSM_REQ_NWORD                       (32U)    /* 64 byte x 2                     */
#define TYDC_CSM_REQ_0                           (0U)
#define TYDC_CSM_REQ_1                           (16U)
#define TYDC_CSM_RSL_NWORD                       (12U)    /* 48 byte                         */

#define TYDC_CSM_UP_REQ_NBYTE                    (64U)
#define TYDC_CSM_UP_RSL_NBYTE                    (48U)

#define TYDC_CSM_VE_REQ_KZK_VD                   (6U)

#define TYDC_CSM_VE_IO_NWORD                     (4U)
#define TYDC_CSM_VE_IO_NBYTE                     (16U)
#define TYDC_CSM_VE_IO_NBIT                      (128U)

#define TYDC_CSM_VE_BID_KEY_ID                   (0U)
#define TYDC_CSM_VE_BID_KEY_US                   (1U)
#define TYDC_CSM_VE_BID_RN                       (8U)     /* Random Number                   */
#define TYDC_CSM_VE_BID_VD                       (24U)    /* Verified Data                   */
typedef struct{
    U4        u4p_req[TYDC_CSM_REQ_NWORD];
    U4        u4p_rsl[TYDC_CSM_RSL_NWORD];
    U4        u4_rsl_nbyte;

    U2        u2_kzk_rx;
    U1        u1_kzk_cnt;
    U1        u1_req_sel;
}ST_TYDC_CSM_IO;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U2        u2_rx_chk;
    U2        u2_nword;
}ST_TYDC_KZK_CHK;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U1        u1_fact21;
    U1        u1_fact43;
    U1        u1_kzk_rx_cnt[TYDC_KZK_RX_NUM_PDU];
    U1        u1_in_volt;
}ST_TYDC_MACUV_HST;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#ifdef TYDOCAN_XID_MA_CFG_H
static ST_TYDC_CSM_IO        st_s_tydc_csm_io; 

static U2                    u2_s_tydc_mak_uv_tm_elpsd;                     /* Key Update/Verify Elapsed       */
static U1                    u1_s_tydc_mak_uv_ctrl;                         /* Key Update/Verify Control       */
static U1                    u1_s_tydc_mak_uv_rid;
static U1                    u1_s_tydc_mak_uv_run;

static U1                    u1_s_tydc_mak_uv_ack;                          /* Key Update/Verify Ack           */
static U1                    u1_s_tydc_mak_su_ack;                          /* Key Single Update Result        */
static U1                    u1_s_tydc_mak_su_facnt;                        /* Key Single Update Failure Count */
static U1                    u1_s_tydc_mak_kvf_chk;                         /* Key Verification Failure DTC    */

static U2                    u2_s_tydc_mak_hrec_tm_elpsd;                   /* History Recording Elapsed       */
static U1                    u1_s_tydc_mak_hrec_ctrl;                       /* History Recording Control       */
static U1                    u1_s_tydc_mak_hrec_rid;
static ST_TYDC_MACUV_HST     st_s_tydc_mak_hrec_hst;
static U1                    u1_s_tydc_mak_hstkup_chk;                      /* History Key Update DTC          */
static U1                    u1_s_tydc_mak_hstkvf_chk;                      /* History Key Verification DTC    */
#ifdef TYDOCAN_EVLOG_CFG_H
static U1                    u1_s_tydc_mak_kus_chk;                         /* Key Update Success EventLogging */
static U1                    u1_s_tydc_mak_kuf_chk;                         /* Key Update Failure EventLogging */
static U1                    u1_s_tydc_ev_type;                             /* Key Update Type                 */
static U1                    u1_s_tydc_ev_sts;                              /* Key Update Status               */
#endif /* #ifdef TYDOCAN_EVLOG_CFG_H */
#endif /* #ifdef TYDOCAN_XID_MA_CFG_H */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#ifdef TYDOCAN_XID_MA_CFG_H
static void    vd_s_TydcMakUvAct_ToAct(void);
static void    vd_s_TydcMakUvAct_ToFin(void);
static void    vd_s_TydcMakUvAct_ToSuc(void);
static void    vd_s_TydcMakUvAct_ToFai(void);
static void    vd_s_TydcMakUvAct_Sta(void);

static void    vd_s_TydcXidMaKzkRxcnt(const U1 u1_a_KZK_RX);
static void    vd_s_TydcXidMaUpdtStart(void);
static void    vd_s_TydcXidMaVerifStart(void);
static U1      u1_s_TydcXidMaVerifchk(void);

static void    vd_s_TydcXidMaKzkRx(const U2 u2_a_PDU, const ST_TYDC_KZK_RX * st_tp_RX);

static void    vd_s_TydcXidMaHstInit(void);
static void    vd_s_TydcXidMaHstRcMain(void);
static void    vd_s_TydcXidMaHstRcchk(void);
#endif /* #ifdef TYDOCAN_XID_MA_CFG_H */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#ifdef TYDOCAN_XID_MA_CFG_H
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANMakInit(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANXidMaInit(void)
{
    vd_g_MemfillU4(&(st_s_tydc_csm_io.u4p_req[0]), (U4)0U, (U4)TYDC_CSM_REQ_NWORD);
    vd_g_MemfillU4(&(st_s_tydc_csm_io.u4p_rsl[0]), (U4)0U, (U4)TYDC_CSM_RSL_NWORD);

    st_s_tydc_csm_io.u4_rsl_nbyte = (U4)0U;
    st_s_tydc_csm_io.u2_kzk_rx    = (U2)0U;
    st_s_tydc_csm_io.u1_kzk_cnt   = (U1)0U;
    st_s_tydc_csm_io.u1_req_sel   = (U1)0U;

    u2_s_tydc_mak_uv_tm_elpsd     = (U2)U2_MAX;
    u1_s_tydc_mak_uv_ctrl         = (U1)TYDC_MAK_UV_CTRL_INA;
    u1_s_tydc_mak_uv_rid          = (U1)U1_MAX;
    u1_s_tydc_mak_uv_run          = (U1)0U;

    u1_s_tydc_mak_uv_ack          = (U1)TYDC_MAK_UV_ACK_INA;
    u1_s_tydc_mak_su_ack          = (U1)TYDC_MAK_UV_ACK_INA;
    u1_s_tydc_mak_su_facnt        = (U1)0U;
    u1_s_tydc_mak_kvf_chk         = (U1)OXDC_DTC_TR_INA;

    u2_s_tydc_mak_hrec_tm_elpsd   = (U2)U2_MAX;
    u1_s_tydc_mak_hrec_ctrl       = (U1)TYDC_MAK_HREC_CTRL_INA;
    u1_s_tydc_mak_hrec_rid        = (U1)U1_MAX;
    u1_s_tydc_mak_hstkup_chk      = (U1)OXDC_DTC_TR_INA;
    u1_s_tydc_mak_hstkvf_chk      = (U1)OXDC_DTC_TR_INA;
    vd_s_TydcXidMaHstInit();

#ifdef TYDOCAN_EVLOG_CFG_H
    u1_s_tydc_mak_kus_chk         = (U1)OXDC_DTC_TR_INA;
    u1_s_tydc_mak_kuf_chk         = (U1)OXDC_DTC_TR_INA;
    u1_s_tydc_ev_type             = (U1)TYDC_EVLOG_KUP_RTN_SINGLE;
    u1_s_tydc_ev_sts              = (U1)TYDC_EVLOG_KUP_FAI_REQ;
#endif /* #ifdef TYDOCAN_EVLOG_CFG_H */
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcXidMaHstInit(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcXidMaHstInit(void)
{
    vd_g_MemfillU1(&(st_s_tydc_mak_hrec_hst.u1_kzk_rx_cnt[0]), (U1)0U, (U4)TYDC_KZK_RX_NUM_PDU);
    st_s_tydc_mak_hrec_hst.u1_fact21  = (U1)0U;
    st_s_tydc_mak_hrec_hst.u1_fact43  = (U1)0U;
    st_s_tydc_mak_hrec_hst.u1_in_volt = (U1)U1_MAX;
}
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANXidMaMainTask(const ST_OXDC_REQ * st_ap_REQ)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANXidMaMainTask(const ST_OXDC_REQ * st_ap_REQ)
{
    static const U2               u2_sp_TYDC_MAK_UV_TOUT[] = {
        /* TYDC_MAK_UV_RID_D904 (0U) */
        (U2)600U  / (U2)OXDC_MAIN_TICK,   /* TYDC_MAK_UV_CTRL_STA (0U) */
        (U2)600U  / (U2)OXDC_MAIN_TICK,   /* TYDC_MAK_UV_CTRL_RUN (1U) */
        (U2)0U,                           /* TYDC_MAK_UV_CTRL_FIN (2U) */
        (U2)0U,                           /* TYDC_MAK_UV_CTRL_INA (3U) */

        /* TYDC_MAK_UV_RID_D902 (1U) */
        (U2)6000U / (U2)OXDC_MAIN_TICK,   /* TYDC_MAK_UV_CTRL_STA (0U) */
        (U2)6000U / (U2)OXDC_MAIN_TICK,   /* TYDC_MAK_UV_CTRL_RUN (1U) */
        (U2)0U,                           /* TYDC_MAK_UV_CTRL_FIN (2U) */
        (U2)0U,                           /* TYDC_MAK_UV_CTRL_INA (3U) */

        /* TYDC_MAK_UV_RID_D903 (2U) */
        (U2)5800U / (U2)OXDC_MAIN_TICK,   /* TYDC_MAK_UV_CTRL_STA (0U) */
        (U2)5800U / (U2)OXDC_MAIN_TICK,   /* TYDC_MAK_UV_CTRL_RUN (1U) */
        (U2)0U,                           /* TYDC_MAK_UV_CTRL_FIN (2U) */
        (U2)0U                            /* TYDC_MAK_UV_CTRL_INA (3U) */
    };

    static const U1               u1_sp_TYDC_MAK_UV_STM[] = {
        /* TYDC_MAK_UV_RID_D904 (0U) */
        (U1)TYDC_MAK_UV_ACT_STA,    (U1)TYDC_MAK_UV_ACT_RUN,    (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,
        (U1)TYDC_MAK_UV_ACT_TO_FIN, (U1)TYDC_MAK_UV_ACT_TO_FIN, (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,
        (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,
        (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,
        (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_TO_SUC, (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,
        (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_TO_SUC, (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,
        (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_TO_SUC, (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,
        (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_TO_SUC, (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,
        (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,
        (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,
        (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,
        (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,

        /* TYDC_MAK_UV_RID_D902 (1U) */
        (U1)TYDC_MAK_UV_ACT_STA,    (U1)TYDC_MAK_UV_ACT_RUN,    (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,
        (U1)TYDC_MAK_UV_ACT_STA,    (U1)TYDC_MAK_UV_ACT_RUN,    (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,
        (U1)TYDC_MAK_UV_ACT_TO_FIN, (U1)TYDC_MAK_UV_ACT_TO_FIN, (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,
        (U1)TYDC_MAK_UV_ACT_TO_FIN, (U1)TYDC_MAK_UV_ACT_TO_FIN, (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,
        (U1)TYDC_MAK_UV_ACT_TO_FIN, (U1)TYDC_MAK_UV_ACT_TO_FIN, (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,
        (U1)TYDC_MAK_UV_ACT_TO_FIN, (U1)TYDC_MAK_UV_ACT_TO_FIN, (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,
        (U1)TYDC_MAK_UV_ACT_TO_FIN, (U1)TYDC_MAK_UV_ACT_TO_FIN, (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,
        (U1)TYDC_MAK_UV_ACT_TO_FIN, (U1)TYDC_MAK_UV_ACT_TO_FIN, (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,
        (U1)TYDC_MAK_UV_ACT_TO_FIN, (U1)TYDC_MAK_UV_ACT_TO_FIN, (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,
        (U1)TYDC_MAK_UV_ACT_TO_FIN, (U1)TYDC_MAK_UV_ACT_TO_FIN, (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,
        (U1)TYDC_MAK_UV_ACT_TO_FIN, (U1)TYDC_MAK_UV_ACT_TO_FIN, (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,
        (U1)TYDC_MAK_UV_ACT_TO_FIN, (U1)TYDC_MAK_UV_ACT_TO_FIN, (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,

        /* TYDC_MAK_UV_RID_D903 (2U) */
        (U1)TYDC_MAK_UV_ACT_STA,    (U1)TYDC_MAK_UV_ACT_RUN,    (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,
        (U1)TYDC_MAK_UV_ACT_STA,    (U1)TYDC_MAK_UV_ACT_RUN,    (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,
        (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,
        (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,
        (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_TO_SUC, (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,
        (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_TO_SUC, (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,
        (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_TO_SUC, (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,
        (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_TO_SUC, (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,
        (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,
        (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,
        (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT,
        (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_TO_FAI, (U1)TYDC_MAK_UV_ACT_FIN, (U1)TYDC_MAK_UV_ACT_TO_ACT
    };

    static void ( * const         fp_sp_vd_TYDC_MAK_UV_ACT[])(void) = {
        &vd_s_TydcMakUvAct_ToAct,     /* TYDC_MAK_UV_ACT_TO_ACT (0U) */
        &vd_s_TydcMakUvAct_ToFin,     /* TYDC_MAK_UV_ACT_TO_FIN (1U) */
        &vd_s_TydcMakUvAct_ToSuc,     /* TYDC_MAK_UV_ACT_TO_SUC (2U) */
        &vd_s_TydcMakUvAct_ToFai,     /* TYDC_MAK_UV_ACT_TO_FAI (3U) */
        &vd_s_TydcMakUvAct_Sta,       /* TYDC_MAK_UV_ACT_STA    (4U) */
                                      /* TYDC_MAK_UV_ACT_RUN    (5U) */
                                      /* TYDC_MAK_UV_ACT_FIN    (6U) */
    };

    U2                            u2_t_tout;
    U2                            u2_t_act;
    U1                            u1_t_ign_on;
    U1                            u1_t_eas_chk;

    u1_t_ign_on = st_ap_REQ->u1_eom_aft & (U1)OXDC_EOM_IGN_ON;
    if((u1_t_ign_on           != (U1)OXDC_EOM_IGN_ON     ) ||
       (u1_s_tydc_mak_uv_ctrl >  (U1)TYDC_MAK_UV_CTRL_INA) ||
       (u1_s_tydc_mak_uv_ack  >  (U1)TYDC_MAK_UV_ACK_FAI )){

        u1_s_tydc_mak_uv_ctrl = (U1)TYDC_MAK_UV_CTRL_INA;
    }
    else{

        if(u2_s_tydc_mak_uv_tm_elpsd < (U2)U2_MAX){
            u2_s_tydc_mak_uv_tm_elpsd++;
        }

        u1_t_eas_chk = u1_s_tydc_mak_uv_ack & ((U1)TYDC_MAK_UV_ACK_SUC | (U1)TYDC_MAK_UV_ACK_FAI);
        if(st_ap_REQ->u1_ses_bfr != st_ap_REQ->u1_ses_aft){
            u1_t_eas_chk |= (U1)TYDC_MAK_UV_EAS_CHK_SES;
        }

        if(u1_s_tydc_mak_uv_rid > (U1)TYDC_MAK_UV_RID_D903){
            u2_t_tout = (U2)u1_s_tydc_mak_uv_ctrl;
            u2_t_act  = (U2)0U;
        }
        else{
            u2_t_tout = ((U2)u1_s_tydc_mak_uv_rid * (U2)TYDC_MAK_UV_NUM_CTRL) + (U2)u1_s_tydc_mak_uv_ctrl;
            u2_t_act  = (U2)u1_s_tydc_mak_uv_rid * (U2)TYDC_MAK_UV_NUM_STM;
        }

        u2_t_tout = u2_sp_TYDC_MAK_UV_TOUT[u2_t_tout];
        if(u2_s_tydc_mak_uv_tm_elpsd >= u2_t_tout){
            u1_t_eas_chk |= (U1)TYDC_MAK_UV_EAS_CHK_TOUT;
            if((u1_s_tydc_mak_hrec_ctrl < (U1)TYDC_MAK_UV_CTRL_FIN) &&
                ((u1_s_tydc_mak_uv_rid == (U1)TYDC_MAK_UV_RID_D902) || 
                 (u1_s_tydc_mak_uv_rid == (U1)TYDC_MAK_UV_RID_D903))){
                if(u1_s_tydc_mak_uv_ctrl == (U1)TYDC_MAK_UV_CTRL_STA){
                    st_s_tydc_mak_hrec_hst.u1_fact43 |= (U1)TYDC_MAK_HREC_FCT3_CNF;
                }
                else{
                    st_s_tydc_mak_hrec_hst.u1_fact43 |= (U1)TYDC_MAK_HREC_FCT3_TMO;
                }
            }
        }

        u2_t_act += (((U2)u1_t_eas_chk * (U2)TYDC_MAK_UV_NUM_CTRL) + (U2)u1_s_tydc_mak_uv_ctrl);
        u2_t_act  = (U2)u1_sp_TYDC_MAK_UV_STM[u2_t_act];
        if(u2_t_act < (U2)TYDC_MAK_UV_ACT_RUN){
            (* fp_sp_vd_TYDC_MAK_UV_ACT[u2_t_act])();
        }
    }

    vd_s_TydcXidMaHstRcMain();
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcXidMaHstRcMain(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcXidMaHstRcMain(void)
{
    static const U2               u2_sp_TYDC_MAK_UV_TOUT[] = {
        (U2)0U,                           /* TYDC_MAK_UV_RID_D904 (0U) */
        (U2)6000U / (U2)OXDC_MAIN_TICK,   /* TYDC_MAK_UV_RID_D902 (1U) */
        (U2)5800U / (U2)OXDC_MAIN_TICK    /* TYDC_MAK_UV_RID_D903 (2U) */
    };

    U2                            u2_t_tout;

    if(u1_s_tydc_mak_hrec_ctrl >  (U1)TYDC_MAK_HREC_CTRL_INA){
        u1_s_tydc_mak_hrec_ctrl = (U1)TYDC_MAK_HREC_CTRL_INA;
    }
    else if(u1_s_tydc_mak_hrec_ctrl == (U1)TYDC_MAK_HREC_CTRL_INA){
        /* Do Nothing */
    }
    else{
        if( (u2_s_tydc_mak_hrec_tm_elpsd < (U2)U2_MAX) && 
            (u1_s_tydc_mak_hrec_ctrl < (U1)TYDC_MAK_UV_CTRL_FIN)){
            u2_s_tydc_mak_hrec_tm_elpsd++;
        }

        if( (u1_s_tydc_mak_hrec_rid == (U1)TYDC_MAK_UV_RID_D902) || 
            (u1_s_tydc_mak_hrec_rid == (U1)TYDC_MAK_UV_RID_D903)){
            u2_t_tout = u2_sp_TYDC_MAK_UV_TOUT[u1_s_tydc_mak_hrec_rid];
        }
        else{
            u2_t_tout = (U2)0U;
        }

        if( (u2_s_tydc_mak_hrec_tm_elpsd >= u2_t_tout) && 
            (u1_s_tydc_mak_hrec_ctrl < (U1)TYDC_MAK_UV_CTRL_FIN)){
            u1_s_tydc_mak_hrec_ctrl = (U1)TYDC_MAK_HREC_CTRL_RUN;
        }

        vd_s_TydcXidMaHstRcchk();

        if(u1_s_tydc_mak_hrec_ctrl == (U1)TYDC_MAK_HREC_CTRL_RUN){
            if(u1_s_tydc_mak_hrec_rid == (U1)TYDC_MAK_UV_RID_D902){
                u1_s_tydc_mak_hstkup_chk = (U1)OXDC_DTC_TR_ACT;
            }
            else if(u1_s_tydc_mak_hrec_rid == (U1)TYDC_MAK_UV_RID_D903){
                u1_s_tydc_mak_hstkvf_chk = (U1)OXDC_DTC_TR_ACT;
            }
            else{
                /* Do nothing */
            }
        }
        else if(u1_s_tydc_mak_hrec_ctrl == (U1)TYDC_MAK_HREC_CTRL_FIN){
            u1_s_tydc_mak_hrec_rid      = (U1)U1_MAX;
            u2_s_tydc_mak_hrec_tm_elpsd = (U2)U2_MAX;
            u1_s_tydc_mak_hrec_ctrl     = (U1)TYDC_MAK_HREC_CTRL_INA;
            vd_s_TydcXidMaHstInit();
        }
        else{
            /* Do nothing */
        }
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcXidMaHstRcchk(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcXidMaHstRcchk(void)
{
    U1                            u1_t_pwr;
    U1                            u1_t_volt;

    u1_t_pwr = u1_g_VehopemdIgnpOn();
    if(((st_s_tydc_mak_hrec_hst.u1_fact21 & (U1)TYDC_MAK_HREC_FCT2_IGP) == (U1)0x0U) && (u1_t_pwr == (U1)FALSE)){
        st_s_tydc_mak_hrec_hst.u1_fact21 |= (U1)TYDC_MAK_HREC_FCT2_IGP;
    }
    u1_t_pwr = u1_g_VehopemdIgnOn();
    if(((st_s_tydc_mak_hrec_hst.u1_fact21 & (U1)TYDC_MAK_HREC_FCT2_IGR) == (U1)0x0U) && (u1_t_pwr == (U1)FALSE)){
        st_s_tydc_mak_hrec_hst.u1_fact21 |= (U1)TYDC_MAK_HREC_FCT2_IGR;
    }
    u1_t_pwr = u1_g_VehopemdAccOn();
    if(((st_s_tydc_mak_hrec_hst.u1_fact21 & (U1)TYDC_MAK_HREC_FCT2_ACC) == (U1)0x0U) && (u1_t_pwr == (U1)FALSE)){
        st_s_tydc_mak_hrec_hst.u1_fact21 |= (U1)TYDC_MAK_HREC_FCT2_ACC;
    }

    u1_t_volt = u1_g_TyDoCANXidMaCfgInputVoltVal();
    if(u1_t_volt < st_s_tydc_mak_hrec_hst.u1_in_volt){
        st_s_tydc_mak_hrec_hst.u1_in_volt = u1_t_volt;
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANDtcTrchk_U13A0(const U2 u2_a_ELPSD)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANDtcTrchk_U13A0(const U2 u2_a_ELPSD)
{
    U1                            u1_t_dtc_act;

    u1_t_dtc_act = u1_s_tydc_mak_kvf_chk;
    u1_s_tydc_mak_kvf_chk = (U1)OXDC_DTC_TR_INA;

    return(u1_t_dtc_act);
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANDtcTrchk_U2300(const U2 u2_a_ELPSD)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANDtcTrchk_U2300(const U2 u2_a_ELPSD)
{
    U1                            u1_t_dtc_act;

    u1_t_dtc_act = u1_s_tydc_mak_hstkup_chk;
    u1_s_tydc_mak_hstkup_chk = (U1)OXDC_DTC_TR_INA;

    return(u1_t_dtc_act);
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANDtcTrchk_U2301(const U2 u2_a_ELPSD)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANDtcTrchk_U2301(const U2 u2_a_ELPSD)
{
    U1                            u1_t_dtc_act;

    u1_t_dtc_act = u1_s_tydc_mak_hstkvf_chk;
    u1_s_tydc_mak_hstkvf_chk = (U1)OXDC_DTC_TR_INA;

    return(u1_t_dtc_act);
}
#ifdef TYDOCAN_EVLOG_CFG_H
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANDtcTrchk_U2B19(const U2 u2_a_ELPSD)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANDtcTrchk_U2B19(const U2 u2_a_ELPSD)
{
    if(u1_s_tydc_mak_kus_chk == (U1)OXDC_DTC_TR_ACT){
        vd_g_TyDoCANEvlogKeyUpSuc(u1_s_tydc_ev_type);     /* U2B19 */
        u1_s_tydc_mak_kus_chk = (U1)OXDC_DTC_TR_INA;
    }
    
    return((U1)OXDC_DTC_TR_UNK);
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANDtcTrchk_U2B1A(const U2 u2_a_ELPSD)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANDtcTrchk_U2B1A(const U2 u2_a_ELPSD)
{
    if(u1_s_tydc_mak_kuf_chk == (U1)OXDC_DTC_TR_ACT){
        vd_g_TyDoCANEvlogKeyUpFai(u1_s_tydc_ev_type, u1_s_tydc_ev_sts);     /* U2B1A */
        u1_s_tydc_mak_kuf_chk = (U1)OXDC_DTC_TR_INA;
    }
    
    return((U1)OXDC_DTC_TR_UNK);
}
#endif /* #ifdef TYDOCAN_EVLOG_CFG_H */
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANRebyId_A901(U1 * u1_ap_ans, const U2 u2_a_ELPSD)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANRebyId_A901(U1 * u1_ap_ans, const U2 u2_a_ELPSD)
{
    U1                            u1_t_ok;
    U1                            u1_t_proc;

    u1_t_ok = u1_g_TyDoCANXidMaCfgSafeKeyNum(u1_ap_ans);
    if(u1_t_ok == (U1)TRUE){
        u1_t_proc = (U1)OXDC_SAL_PROC_FIN;
    }
    else{
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_22;
#ifdef TYDOCAN_EVLOG_CFG_H
        u1_s_tydc_mak_kuf_chk        = (U1)OXDC_DTC_TR_ACT;          /* U2B1A */
        u1_s_tydc_ev_type            = (U1)TYDC_EVLOG_KUP_RTN_SFKEY;
        u1_s_tydc_ev_sts             = (U1)TYDC_EVLOG_KUP_FAI_RES;
#endif /* #ifdef TYDOCAN_EVLOG_CFG_H */
    }

    return(u1_t_proc);
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANRoutCorchk_D904(const U1 u1_a_SUBF, const U1 * u1_ap_COR)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANRoutCorchk_D904(const U1 u1_a_SUBF, const U1 * u1_ap_COR)
{
    if((u1_a_SUBF              == (U1)OXDC_ROUT_SUBF_START) &&
       (u1_s_tydc_mak_uv_ctrl  == (U1)TYDC_MAK_UV_CTRL_FIN) &&
       (u1_s_tydc_mak_su_facnt <  (U1)TYDC_MAK_SU_FAC_MAX )){

        vd_g_MemcpyU1((U1 *)&(st_s_tydc_csm_io.u4p_req[0]), &u1_ap_COR[0], (U4)TYDC_CSM_UP_REQ_NBYTE);
    }

    return((U1)OXDC_SAL_PROC_RUN);
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANRoutStart_D904(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte)                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANRoutStart_D904(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte)
{
    U1                            u1_t_proc;

    if((u1_s_tydc_mak_uv_ctrl  == (U1)TYDC_MAK_UV_CTRL_FIN) &&
       (u1_s_tydc_mak_su_facnt <  (U1)TYDC_MAK_SU_FAC_MAX )){

        st_s_tydc_csm_io.u2_kzk_rx  = (U2)0U;
        st_s_tydc_csm_io.u1_kzk_cnt = (U1)0U;
        st_s_tydc_csm_io.u1_req_sel = (U1)0U;

        u2_s_tydc_mak_uv_tm_elpsd   = (U2)0U;
        u1_s_tydc_mak_uv_ctrl       = (U1)TYDC_MAK_UV_CTRL_STA;
        u1_s_tydc_mak_uv_rid        = (U1)TYDC_MAK_UV_RID_D904;

        u1_s_tydc_mak_uv_ack        = (U1)TYDC_MAK_UV_ACK_INA;
        u1_s_tydc_mak_su_ack        = (U1)TYDC_MAK_UV_ACK_INA;

        vd_s_TydcXidMaUpdtStart();

        u1_ap_ans[0] = (U1)TYDC_RID_D904_ANS_RINFO;
        u1_ap_ans[1] = (U1)TYDC_RID_D904_ANS_RUN;
        vd_g_MemfillU1(&u1_ap_ans[2], (U1)0U, (U4)TYDC_CSM_UP_RSL_NBYTE);

        u1_t_proc = (U1)OXDC_SAL_PROC_FIN;
    }
#ifdef TYDOCAN_EVLOG_CFG_H
    else if(u1_s_tydc_mak_uv_ctrl < (U1)TYDC_MAK_UV_CTRL_FIN){
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_24;

        u1_s_tydc_mak_kuf_chk        = (U1)OXDC_DTC_TR_ACT;          /* U2B1A */
        u1_s_tydc_ev_type            = (U1)TYDC_EVLOG_KUP_RTN_SINGLE;
        u1_s_tydc_ev_sts             = (U1)TYDC_EVLOG_KUP_FAI_REQ;
    }
    else{
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_22;

        u1_s_tydc_mak_kuf_chk        = (U1)OXDC_DTC_TR_ACT;          /* U2B1A */
        u1_s_tydc_ev_type            = (U1)TYDC_EVLOG_KUP_RTN_SINGLE;
        u1_s_tydc_ev_sts             = (U1)TYDC_EVLOG_KUP_FAI_REQ;
    }
#else /* #ifdef TYDOCAN_EVLOG_CFG_H */
    else if(u1_s_tydc_mak_uv_ctrl < (U1)TYDC_MAK_UV_CTRL_FIN){
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_24;
    }
    else{
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_22;
    }
#endif /* #ifdef TYDOCAN_EVLOG_CFG_H */

    return(u1_t_proc);
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANRoutRslt_D904(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte)                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANRoutRslt_D904(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte)
{
    U1                            u1_t_proc;

    if(u1_s_tydc_mak_uv_rid == (U1)TYDC_MAK_UV_RID_D904){
        u1_ap_ans[0] = (U1)TYDC_RID_D904_ANS_RINFO;
        u1_ap_ans[1] = (U1)TYDC_RID_D904_ANS_RUN;
        vd_g_MemfillU1(&u1_ap_ans[2], (U1)0U, (U4)TYDC_CSM_UP_RSL_NBYTE);
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_21;
    }
    else if(u1_s_tydc_mak_su_ack == (U1)TYDC_MAK_UV_ACK_SUC){
        u1_ap_ans[0] = (U1)TYDC_RID_D904_ANS_RINFO;
        u1_ap_ans[1] = (U1)TYDC_RID_D904_ANS_SUC;
        vd_g_MemcpyU1(&u1_ap_ans[2], (const U1 * )&(st_s_tydc_csm_io.u4p_rsl[0]), (U4)TYDC_CSM_UP_RSL_NBYTE);
        vd_g_MemfillU4(&(st_s_tydc_csm_io.u4p_rsl[0]), (U4)0U, (U4)TYDC_CSM_RSL_NWORD);
        u1_t_proc = (U1)OXDC_SAL_PROC_FIN;
    }
    else if(u1_s_tydc_mak_su_ack == (U1)TYDC_MAK_UV_ACK_FAI){
        u1_ap_ans[0] = (U1)TYDC_RID_D904_ANS_RINFO;
        u1_ap_ans[1] = (U1)TYDC_RID_D904_ANS_FAI;
        vd_g_MemfillU1(&u1_ap_ans[2], (U1)0U, (U4)TYDC_CSM_UP_RSL_NBYTE);
        u1_t_proc = (U1)OXDC_SAL_PROC_FIN;
    }
    else{
        u1_ap_ans[0] = (U1)TYDC_RID_D904_ANS_RINFO;
        u1_ap_ans[1] = (U1)TYDC_RID_D904_ANS_INA;
        vd_g_MemfillU1(&u1_ap_ans[2], (U1)0U, (U4)TYDC_CSM_UP_RSL_NBYTE);
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_24;
    }

    return(u1_t_proc);
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANRoutStart_D902(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte)                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANRoutStart_D902(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte)
{
    U1                            u1_t_proc;
    U1                            u1_t_bit;
    U1                            u1_t_run;

    if(u1_s_tydc_mak_hrec_ctrl == (U1)TYDC_MAK_HREC_CTRL_INA){
        vd_s_TydcXidMaHstInit();
        u2_s_tydc_mak_hrec_tm_elpsd      = (U2)0U;
        u1_s_tydc_mak_hrec_ctrl          = (U1)TYDC_MAK_HREC_CTRL_STA;
        u1_s_tydc_mak_hrec_rid           = (U1)TYDC_MAK_UV_RID_D902;
        st_s_tydc_mak_hrec_hst.u1_fact43 |= (U1)TYDC_MAK_HREC_FCT4_STA;
    }

    if(u1_s_tydc_mak_hrec_ctrl < (U1)TYDC_MAK_UV_CTRL_FIN){
        st_s_tydc_mak_hrec_hst.u1_fact43 |= (U1)TYDC_MAK_HREC_FCT4_RST;
    }

    u1_t_bit = (U1)0x01U << TYDC_MAK_UV_RID_D902;
    u1_t_run = u1_s_tydc_mak_uv_run & u1_t_bit;
    if(u1_t_run != (U1)0x00U){
        u1_ap_ans[0] = (U1)TYDC_RID_D902_ANS_RINFO;
        u1_t_proc = (U1)OXDC_SAL_PROC_FIN;
    }
    else if(u1_s_tydc_mak_uv_ctrl == (U1)TYDC_MAK_UV_CTRL_FIN){

        st_s_tydc_csm_io.u2_kzk_rx   = (U2)0U;
        st_s_tydc_csm_io.u1_kzk_cnt  = (U1)0U;
        st_s_tydc_csm_io.u1_req_sel  = (U1)0U;

        u2_s_tydc_mak_uv_tm_elpsd    = (U2)0U;
        u1_s_tydc_mak_uv_ctrl        = (U1)TYDC_MAK_UV_CTRL_STA;
        u1_s_tydc_mak_uv_rid         = (U1)TYDC_MAK_UV_RID_D902;
        u1_s_tydc_mak_uv_run        |= u1_t_bit;

        u1_s_tydc_mak_uv_ack         = (U1)TYDC_MAK_UV_ACK_INA;

        u1_ap_ans[0] = (U1)TYDC_RID_D902_ANS_RINFO;
        u1_t_proc = (U1)OXDC_SAL_PROC_FIN;

        if(u1_s_tydc_mak_hrec_ctrl < (U1)TYDC_MAK_UV_CTRL_FIN){
            st_s_tydc_mak_hrec_hst.u1_fact21 |= (U1)TYDC_MAK_HREC_FCT1_RTN;
        }
    }
#ifdef TYDOCAN_EVLOG_CFG_H
    else if(u1_s_tydc_mak_uv_ctrl < (U1)TYDC_MAK_UV_CTRL_FIN){
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_24;

        u1_s_tydc_mak_kuf_chk        = (U1)OXDC_DTC_TR_ACT;          /* U2B1A */
        u1_s_tydc_ev_type            = (U1)TYDC_EVLOG_KUP_RTN_ALL;
        u1_s_tydc_ev_sts             = (U1)TYDC_EVLOG_KUP_FAI_REQ;
    }
    else{
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_22;

        u1_s_tydc_mak_kuf_chk        = (U1)OXDC_DTC_TR_ACT;          /* U2B1A */
        u1_s_tydc_ev_type            = (U1)TYDC_EVLOG_KUP_RTN_ALL;
        u1_s_tydc_ev_sts             = (U1)TYDC_EVLOG_KUP_FAI_REQ;
    }
#else /* #ifdef TYDOCAN_EVLOG_CFG_H */
    else if(u1_s_tydc_mak_uv_ctrl < (U1)TYDC_MAK_UV_CTRL_FIN){
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_24;
    }
    else{
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_22;
    }
#endif /* #ifdef TYDOCAN_EVLOG_CFG_H */

    return(u1_t_proc);
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANRoutStart_D903(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte)                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANRoutStart_D903(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte)
{
    U1                            u1_t_proc;
    U1                            u1_t_bit;
    U1                            u1_t_run;

    if(u1_s_tydc_mak_hrec_ctrl == (U1)TYDC_MAK_HREC_CTRL_INA){
        vd_s_TydcXidMaHstInit();
        u2_s_tydc_mak_hrec_tm_elpsd      = (U2)0U;
        u1_s_tydc_mak_hrec_ctrl          = (U1)TYDC_MAK_HREC_CTRL_STA;
        u1_s_tydc_mak_hrec_rid           = (U1)TYDC_MAK_UV_RID_D903;
        st_s_tydc_mak_hrec_hst.u1_fact43 |= (U1)TYDC_MAK_HREC_FCT4_STA;
    }

    if(u1_s_tydc_mak_hrec_ctrl < (U1)TYDC_MAK_UV_CTRL_FIN){
        st_s_tydc_mak_hrec_hst.u1_fact43 |= (U1)TYDC_MAK_HREC_FCT4_RST;
    }

    u1_t_bit = (U1)0x01U << TYDC_MAK_UV_RID_D903;
    u1_t_run = u1_s_tydc_mak_uv_run & u1_t_bit;
    if(u1_t_run != (U1)0x00U){
        u1_ap_ans[0] = (U1)TYDC_RID_D903_ANS_RINFO;
        u1_t_proc = (U1)OXDC_SAL_PROC_FIN;
    }
    else if(u1_s_tydc_mak_uv_ctrl == (U1)TYDC_MAK_UV_CTRL_FIN){

        st_s_tydc_csm_io.u2_kzk_rx   = (U2)0U;
        st_s_tydc_csm_io.u1_kzk_cnt  = (U1)0U;
        st_s_tydc_csm_io.u1_req_sel  = (U1)0U;

        u2_s_tydc_mak_uv_tm_elpsd    = (U2)0U;
        u1_s_tydc_mak_uv_ctrl        = (U1)TYDC_MAK_UV_CTRL_STA;
        u1_s_tydc_mak_uv_rid         = (U1)TYDC_MAK_UV_RID_D903;
        u1_s_tydc_mak_uv_run        |= u1_t_bit;

        u1_s_tydc_mak_uv_ack         = (U1)TYDC_MAK_UV_ACK_INA;

        u1_ap_ans[0] = (U1)TYDC_RID_D903_ANS_RINFO;
        u1_t_proc = (U1)OXDC_SAL_PROC_FIN;

        if(u1_s_tydc_mak_hrec_ctrl < (U1)TYDC_MAK_UV_CTRL_FIN){
            st_s_tydc_mak_hrec_hst.u1_fact21 |= (U1)TYDC_MAK_HREC_FCT1_RTN;
        }
    }
    else if(u1_s_tydc_mak_uv_ctrl < (U1)TYDC_MAK_UV_CTRL_FIN){
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_24;
    }
    else{
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_22;
    }

    return(u1_t_proc);
}
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANAubIfComKzkRx(const uint16 u2_a_PDU)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANAubIfComKzkRx(const uint16 u2_a_PDU)
{
    if(u1_s_tydc_mak_uv_ctrl >= (U1)TYDC_MAK_UV_CTRL_FIN){
    }
    else if(u1_s_tydc_mak_uv_rid == (U1)TYDC_MAK_UV_RID_D902){
        vd_s_TydcXidMaKzkRx(u2_a_PDU, &st_gp_TYDC_KZK_RX[TYDC_KZK_RX_D902]);
    }
    else if(u1_s_tydc_mak_uv_rid == (U1)TYDC_MAK_UV_RID_D903){
        vd_s_TydcXidMaKzkRx(u2_a_PDU, &st_gp_TYDC_KZK_RX[TYDC_KZK_RX_D903]);
    }
    else{
        /* Do Nothing */
    }

    if(u1_s_tydc_mak_hrec_ctrl > (U1)TYDC_MAK_HREC_CTRL_INA){
        u1_s_tydc_mak_hrec_ctrl = (U1)TYDC_MAK_HREC_CTRL_INA;
    }
    else if(u1_s_tydc_mak_hrec_ctrl != (U1)TYDC_MAK_HREC_CTRL_INA){
        /* Do Nothing */
    }
    else if((u2_a_PDU >= st_gp_TYDC_KZK_RX[TYDC_KZK_RX_D902].u2_pdu_min) && 
            (u2_a_PDU <= st_gp_TYDC_KZK_RX[TYDC_KZK_RX_D902].u2_pdu_max)){

        u1_s_tydc_mak_hrec_rid         = (U1)TYDC_MAK_UV_RID_D902;
        u2_s_tydc_mak_hrec_tm_elpsd    = (U2)0U;
        u1_s_tydc_mak_hrec_ctrl        = (U1)TYDC_MAK_HREC_CTRL_STA;
        vd_s_TydcXidMaHstInit();
    }
    else if((u2_a_PDU >= st_gp_TYDC_KZK_RX[TYDC_KZK_RX_D903].u2_pdu_min) && 
            (u2_a_PDU <= st_gp_TYDC_KZK_RX[TYDC_KZK_RX_D903].u2_pdu_max)){

        u1_s_tydc_mak_hrec_rid         = (U1)TYDC_MAK_UV_RID_D903;
        u2_s_tydc_mak_hrec_tm_elpsd    = (U2)0U;
        u1_s_tydc_mak_hrec_ctrl        = (U1)TYDC_MAK_HREC_CTRL_STA;
        vd_s_TydcXidMaHstInit();
    }
    else{
        /* Do Nothing */
    }
}
/*===================================================================================================================================*/
/*  void   vd_g_TyDoCANAubIfCsmAck(uint32 u4_a_jobId, Crypto_ResultType u1_a_RSLT)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void   vd_g_TyDoCANAubIfCsmAck(uint32 u4_a_jobId, Crypto_ResultType u1_a_RSLT)
{
    if(u1_a_RSLT == (U1)E_OK){
        u1_s_tydc_mak_uv_ack = (U1)TYDC_MAK_UV_ACK_SUC;
    }
    else{
        u1_s_tydc_mak_uv_ack = (U1)TYDC_MAK_UV_ACK_FAI;
    }

    if((u1_s_tydc_mak_hrec_rid == (U1)TYDC_MAK_UV_RID_D903) && 
        (u1_s_tydc_mak_hrec_ctrl < (U1)TYDC_MAK_UV_CTRL_FIN)){
        st_s_tydc_mak_hrec_hst.u1_fact21 |= (U1)TYDC_MAK_HREC_FCT1_PRC;
        u1_s_tydc_mak_hrec_ctrl          = (U1)TYDC_MAK_HREC_CTRL_RUN;
        if(u1_a_RSLT == (U1)E_OK){
            st_s_tydc_mak_hrec_hst.u1_fact21 |= (U1)TYDC_MAK_HREC_FCT1_FIN;
        }
        else{
            st_s_tydc_mak_hrec_hst.u1_fact43 |= (U1)TYDC_MAK_HREC_FCT3_PRC;
        }
    }
}
#endif /* #ifdef TYDOCAN_XID_MA_CFG_H */
/*===================================================================================================================================*/
/*  void   vd_g_TyDoCANAubIfCryptoIcusAck(uint8 u1_a_ServiceId, Std_ReturnType u1_a_RSLT)                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_TyDoCANAubIfCryptoIcusAck(uint8 u1_a_ServiceId, Std_ReturnType u1_a_RSLT)
{
#ifdef TYDOCAN_XID_MA_CFG_H
#ifdef TYDOCAN_EVLOG_CFG_H
    if(u1_a_RSLT == (U1)E_OK){
        u1_s_tydc_mak_uv_ack = (U1)TYDC_MAK_UV_ACK_SUC;
        u1_s_tydc_mak_kus_chk   = (U1)OXDC_DTC_TR_ACT;          /* U2B19 */
    }
    else{
        u1_s_tydc_mak_uv_ack = (U1)TYDC_MAK_UV_ACK_FAI;
        u1_s_tydc_mak_kuf_chk   = (U1)OXDC_DTC_TR_ACT;          /* U2B1A */
        u1_s_tydc_ev_sts        = (U1)TYDC_EVLOG_KUP_FAI_RES;
    }

    if(u1_s_tydc_mak_uv_rid == (U1)TYDC_MAK_UV_RID_D904){
        u1_s_tydc_ev_type       = (U1)TYDC_EVLOG_KUP_RTN_SINGLE;
    }
    else{
        u1_s_tydc_ev_type       = (U1)TYDC_EVLOG_KUP_RTN_ALL;
    }
#else /* #ifdef TYDOCAN_EVLOG_CFG_H */
    if(u1_a_RSLT == (U1)E_OK){
        u1_s_tydc_mak_uv_ack = (U1)TYDC_MAK_UV_ACK_SUC;
    }
    else{
        u1_s_tydc_mak_uv_ack = (U1)TYDC_MAK_UV_ACK_FAI;
    }
#endif /* #ifdef TYDOCAN_EVLOG_CFG_H */
    if((u1_s_tydc_mak_hrec_rid == (U1)TYDC_MAK_UV_RID_D902) && 
        (u1_s_tydc_mak_hrec_ctrl < (U1)TYDC_MAK_UV_CTRL_FIN)){
        st_s_tydc_mak_hrec_hst.u1_fact21 |= (U1)TYDC_MAK_HREC_FCT1_PRC;
        u1_s_tydc_mak_hrec_ctrl          = (U1)TYDC_MAK_HREC_CTRL_RUN;
        if(u1_a_RSLT == (U1)E_OK){
            st_s_tydc_mak_hrec_hst.u1_fact21 |= (U1)TYDC_MAK_HREC_FCT1_FIN;
        }
        else{
            st_s_tydc_mak_hrec_hst.u1_fact43 |= (U1)TYDC_MAK_HREC_FCT3_PRC;
        }
    }
#endif /* #ifdef TYDOCAN_XID_MA_CFG_H */
}
#ifdef TYDOCAN_XID_MA_CFG_H
/*===================================================================================================================================*/
/*  static void    vd_s_TydcMakUvAct_ToAct(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcMakUvAct_ToAct(void)
{
    vd_g_MemfillU4(&(st_s_tydc_csm_io.u4p_req[0]), (U4)0U, (U4)TYDC_CSM_REQ_NWORD);
    vd_g_MemfillU4(&(st_s_tydc_csm_io.u4p_rsl[0]), (U4)0U, (U4)TYDC_CSM_RSL_NWORD);

    st_s_tydc_csm_io.u2_kzk_rx  = (U2)0U;
    st_s_tydc_csm_io.u1_kzk_cnt = (U1)0U;
    st_s_tydc_csm_io.u1_req_sel = (U1)0U;

    u2_s_tydc_mak_uv_tm_elpsd   = (U2)U2_MAX;
    u1_s_tydc_mak_uv_ctrl       = (U1)TYDC_MAK_UV_CTRL_FIN;
    u1_s_tydc_mak_uv_rid        = (U1)U1_MAX;
    u1_s_tydc_mak_uv_run        = (U1)0U;

    u1_s_tydc_mak_uv_ack        = (U1)TYDC_MAK_UV_ACK_INA;
    u1_s_tydc_mak_su_ack        = (U1)TYDC_MAK_UV_ACK_INA;
    u1_s_tydc_mak_su_facnt      = (U1)0U;
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcMakUvAct_ToFin(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcMakUvAct_ToFin(void)
{
    vd_g_MemfillU4(&(st_s_tydc_csm_io.u4p_req[0]), (U4)0U, (U4)TYDC_CSM_REQ_NWORD);
    vd_g_MemfillU4(&(st_s_tydc_csm_io.u4p_rsl[0]), (U4)0U, (U4)TYDC_CSM_RSL_NWORD);

    st_s_tydc_csm_io.u2_kzk_rx  = (U2)0U;
    st_s_tydc_csm_io.u1_kzk_cnt = (U1)0U;
    st_s_tydc_csm_io.u1_req_sel = (U1)0U;

    u2_s_tydc_mak_uv_tm_elpsd   = (U2)U2_MAX;
    u1_s_tydc_mak_uv_ctrl       = (U1)TYDC_MAK_UV_CTRL_FIN;
    u1_s_tydc_mak_uv_rid        = (U1)U1_MAX;
 /* u1_s_tydc_mak_uv_run        = (U1)0U; */

    u1_s_tydc_mak_uv_ack        = (U1)TYDC_MAK_UV_ACK_INA;
 /* u1_s_tydc_mak_su_ack        = (U1)TYDC_MAK_UV_ACK_INA; */
 /* u1_s_tydc_mak_su_facnt      = (U1)0U; */
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcMakUvAct_ToSuc(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcMakUvAct_ToSuc(void)
{
    if(u1_s_tydc_mak_uv_rid == (U1)TYDC_MAK_UV_RID_D904){
        u1_s_tydc_mak_su_ack    = (U1)TYDC_MAK_UV_ACK_SUC;
        vd_g_MemfillU4(&(st_s_tydc_csm_io.u4p_req[0]), (U4)0U, (U4)TYDC_CSM_REQ_NWORD);
    }
    else if(u1_s_tydc_mak_uv_rid == (U1)TYDC_MAK_UV_RID_D903){
        u1_s_tydc_mak_kvf_chk   = u1_s_TydcXidMaVerifchk();
        vd_g_MemfillU4(&(st_s_tydc_csm_io.u4p_req[0]), (U4)0U, (U4)TYDC_CSM_REQ_NWORD);
        vd_g_MemfillU4(&(st_s_tydc_csm_io.u4p_rsl[0]), (U4)0U, (U4)TYDC_CSM_RSL_NWORD);
    }
    else{
        /* Do Nothing */
    }

    st_s_tydc_csm_io.u2_kzk_rx  = (U2)0U;
    st_s_tydc_csm_io.u1_kzk_cnt = (U1)0U;
    st_s_tydc_csm_io.u1_req_sel = (U1)0U;

    u2_s_tydc_mak_uv_tm_elpsd   = (U2)U2_MAX;
    u1_s_tydc_mak_uv_ctrl       = (U1)TYDC_MAK_UV_CTRL_FIN;
    u1_s_tydc_mak_uv_rid        = (U1)U1_MAX;
 /* u1_s_tydc_mak_uv_run        = (U1)0U; */

    u1_s_tydc_mak_uv_ack        = (U1)TYDC_MAK_UV_ACK_INA;
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcMakUvAct_ToFai(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcMakUvAct_ToFai(void)
{
    if(u1_s_tydc_mak_uv_rid == (U1)TYDC_MAK_UV_RID_D904){

        u1_s_tydc_mak_su_ack    = (U1)TYDC_MAK_UV_ACK_FAI;
        if(u1_s_tydc_mak_su_facnt < (U1)U1_MAX){
            u1_s_tydc_mak_su_facnt++;
        }
    }
    else if(u1_s_tydc_mak_uv_rid == (U1)TYDC_MAK_UV_RID_D903){
        u1_s_tydc_mak_kvf_chk   = (U1)OXDC_DTC_TR_ACT;
    }
    else{
        /* Do Nothing */
    }

    vd_g_MemfillU4(&(st_s_tydc_csm_io.u4p_req[0]), (U4)0U, (U4)TYDC_CSM_REQ_NWORD);
    vd_g_MemfillU4(&(st_s_tydc_csm_io.u4p_rsl[0]), (U4)0U, (U4)TYDC_CSM_RSL_NWORD);

    st_s_tydc_csm_io.u2_kzk_rx  = (U2)0U;
    st_s_tydc_csm_io.u1_kzk_cnt = (U1)0U;
    st_s_tydc_csm_io.u1_req_sel = (U1)0U;

    u2_s_tydc_mak_uv_tm_elpsd   = (U2)U2_MAX;
    u1_s_tydc_mak_uv_ctrl       = (U1)TYDC_MAK_UV_CTRL_FIN;
    u1_s_tydc_mak_uv_rid        = (U1)U1_MAX;
 /* u1_s_tydc_mak_uv_run        = (U1)0U; */

    u1_s_tydc_mak_uv_ack        = (U1)TYDC_MAK_UV_ACK_INA;
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcMakUvAct_Sta(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcMakUvAct_Sta(void)
{
    if(u1_s_tydc_mak_uv_rid > (U1)TYDC_MAK_UV_RID_D903){
    }
    else if(u1_s_tydc_mak_uv_rid == (U1)TYDC_MAK_UV_RID_D904){
        vd_s_TydcXidMaUpdtStart();
    }
    else if(u1_s_tydc_mak_uv_rid == (U1)TYDC_MAK_UV_RID_D902){

        if(st_s_tydc_csm_io.u1_kzk_cnt < (U1)TYDC_KZK_RXC_MAX){
            vd_s_TydcXidMaKzkRxcnt((U1)TYDC_KZK_RX_D902);
        }
        else{
            if(u1_s_tydc_mak_hrec_ctrl < (U1)TYDC_MAK_UV_CTRL_FIN){
                st_s_tydc_mak_hrec_hst.u1_fact21 |= (U1)TYDC_MAK_HREC_FCT1_CNF;
            }
            vd_s_TydcXidMaUpdtStart();
        }
    }
    else{

        if(st_s_tydc_csm_io.u1_kzk_cnt < (U1)TYDC_KZK_RXC_MAX){
            vd_s_TydcXidMaKzkRxcnt((U1)TYDC_KZK_RX_D903);
        }
        else{
            if(u1_s_tydc_mak_hrec_ctrl < (U1)TYDC_MAK_UV_CTRL_FIN){
                st_s_tydc_mak_hrec_hst.u1_fact21 |= (U1)TYDC_MAK_HREC_FCT1_CNF;
            }
            vd_s_TydcXidMaVerifStart();
        }
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcXidMaKzkRxcnt(const U1 u1_a_KZK_RX)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcXidMaKzkRxcnt(const U1 u1_a_KZK_RX)
{
    static const ST_TYDC_KZK_CHK  st_sp_TYDC_KZK_CHK[TYDC_KZK_NUM_RX] = {
        {
            (U2)0x00ffU,               /* u2_rx_chk */
            (U2)16U                    /* u2_nword  */
        },
        {
            (U2)0x001fU,               /* u2_rx_chk */
            (U2)10U                    /* u2_nword  */
        }
    };

    const U4 *                    u4_tp_KZK_0;
    const U4 *                    u4_tp_KZK_1;

    U4                            u4_t_wid;
    U4                            u4_t_nword;

    U2                            u2_t_rx_chk;
    U2                            u2_t_rx_evt;

    U1                            u1_t_next;

    u2_t_rx_chk = st_sp_TYDC_KZK_CHK[u1_a_KZK_RX].u2_rx_chk;
    u2_t_rx_evt = st_s_tydc_csm_io.u2_kzk_rx & u2_t_rx_chk;
    if(u2_t_rx_evt == u2_t_rx_chk){

        st_s_tydc_csm_io.u2_kzk_rx = (U2)0U;

        u4_t_nword  = (U4)st_sp_TYDC_KZK_CHK[u1_a_KZK_RX].u2_nword;
        u4_tp_KZK_0 = &(st_s_tydc_csm_io.u4p_req[TYDC_CSM_REQ_0]);
        u4_tp_KZK_1 = &(st_s_tydc_csm_io.u4p_req[TYDC_CSM_REQ_1]);
        for(u4_t_wid = (U4)0U; u4_t_wid < u4_t_nword; u4_t_wid++){
            if(u4_tp_KZK_0[u4_t_wid] != u4_tp_KZK_1[u4_t_wid]){
                break;
            }
        }

        if(u4_t_wid < u4_t_nword){
            st_s_tydc_csm_io.u1_kzk_cnt = (U1)1U;
            u1_t_next = (st_s_tydc_csm_io.u1_req_sel + (U1)1U) & (U1)0x01U;
            st_s_tydc_csm_io.u1_req_sel = u1_t_next;
        }
        else if(st_s_tydc_csm_io.u1_kzk_cnt < (U1)U1_MAX){
            st_s_tydc_csm_io.u1_kzk_cnt++;
        }
        else{
            /* Do Nothing */
        }
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcXidMaUpdtStart(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcXidMaUpdtStart(void)
{
    const U1 *                    u1_tp_MX;

    U4                            u4_t_cpu_md;
    U1                            u1_t_csm;
    Mscd_MsStatusType             st_tp_sts;

    u4_t_cpu_md = u4_g_CPUM_PRIV();  /* CPU mode = privilege   */

    (void)Mscd_Msif_GetStatus(&st_tp_sts);
    if(st_tp_sts == (U1)MSCD_MS_STATE_IDLE){

        if(st_s_tydc_csm_io.u1_req_sel == (U1)0U){
            u1_tp_MX = (const U1 *)&(st_s_tydc_csm_io.u4p_req[TYDC_CSM_REQ_0]);
        }
        else{
            u1_tp_MX = (const U1 *)&(st_s_tydc_csm_io.u4p_req[TYDC_CSM_REQ_1]);
        }

        st_s_tydc_csm_io.u4_rsl_nbyte = (U4)TYDC_CSM_UP_RSL_NBYTE;
        u1_t_csm = Crypto_83_icus_Ab_SHELoadKey(
                                         u1_tp_MX,                                                   /* const uint8 *          */
                                         (U4)TYDC_CSM_UP_REQ_NBYTE,                                  /* uint32                 */
                                         (U1 *)&(st_s_tydc_csm_io.u4p_rsl[0]),                       /* uint8 *                */
                                         st_s_tydc_csm_io.u4_rsl_nbyte);                             /* uint32 *               */

        if(u1_t_csm == (U1)E_OK){
            u1_s_tydc_mak_uv_ctrl = (U1)TYDC_MAK_UV_CTRL_RUN;
        }
    }

    vd_g_CPUM_RSTR(u4_t_cpu_md);     /* CPU mode = u4_t_cpu_md */
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcXidMaVerifStart(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcXidMaVerifStart(void)
{
    const U1 *                    u1_tp_KZK;
    U4                            u4_t_cpu_md;
    U1                            u1_t_csm;

    if(st_s_tydc_csm_io.u1_req_sel == (U1)0U){
        u1_tp_KZK = (const U1 *)&(st_s_tydc_csm_io.u4p_req[TYDC_CSM_REQ_0]);
    }
    else{
        u1_tp_KZK = (const U1 *)&(st_s_tydc_csm_io.u4p_req[TYDC_CSM_REQ_1]);
    }

    if(u1_tp_KZK[TYDC_CSM_VE_BID_KEY_US] == (U1)TYDC_RID_D903_US_MAC){

        u4_t_cpu_md = u4_g_CPUM_PRIV();  /* CPU mode = privilege   */

        u1_t_csm = Csm_MacVerify((U4)TYDC_SEC_MACVRFY_JOBID, 
                                      (U1)CRYPTO_OPERATIONMODE_SINGLECALL, 
                                      &u1_tp_KZK[TYDC_CSM_VE_BID_RN],                                /* const uint8 *          */
                                      (U4)TYDC_CSM_VE_IO_NBYTE,                                      /* uint32                 */
                                      &u1_tp_KZK[TYDC_CSM_VE_BID_VD],                                /* const uint8 *          */    
                                      (U4)TYDC_CSM_VE_IO_NBIT,                                       /* uint32                 */
                                      (U1 *)&(st_s_tydc_csm_io.u4p_rsl[0]));                         /* Csm_VerifyResultType * */

        vd_g_CPUM_RSTR(u4_t_cpu_md);     /* CPU mode = u4_t_cpu_md */
    }
    else if(u1_tp_KZK[TYDC_CSM_VE_BID_KEY_US] == (U1)TYDC_RID_D903_US_BLO){

        st_s_tydc_csm_io.u4_rsl_nbyte = (U4)TYDC_CSM_VE_IO_NBYTE;

        u4_t_cpu_md = u4_g_CPUM_PRIV();  /* CPU mode = privilege   */

        u1_t_csm = Csm_Encrypt ( (U4)TYDC_SEC_ENCRYPTO_JOBID,
                                            (U1)CRYPTO_OPERATIONMODE_SINGLECALL, 
                                            &u1_tp_KZK[TYDC_CSM_VE_BID_RN],                          /* const uint8 *          */
                                            (U4)TYDC_CSM_VE_IO_NBYTE,                                /* uint32                 */
                                            (U1 *)&(st_s_tydc_csm_io.u4p_rsl[0]),                    /* uint8 *                */
                                            &(st_s_tydc_csm_io.u4_rsl_nbyte));                       /* uint32 *               */ 

        vd_g_CPUM_RSTR(u4_t_cpu_md);     /* CPU mode = u4_t_cpu_md */
    }
    else{
        u1_t_csm             = (U1)E_OK;
        u1_s_tydc_mak_uv_ack = (U1)TYDC_MAK_UV_ACK_FAI;
    }

    if(u1_t_csm == (U1)E_OK){
        u1_s_tydc_mak_uv_ctrl = (U1)TYDC_MAK_UV_CTRL_RUN;
    }
}
/*===================================================================================================================================*/
/*  static U1      u1_s_TydcXidMaVerifchk(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_TydcXidMaVerifchk(void)
{
    const U1 *                    u1_tp_KZK;
    const U1 *                    u1_tp_MAC_RSL;
    const U4 *                    u4_tp_BLO_RSL;
    const U4 *                    u4_tp_BLO_CRI;

    U4                            u4_t_lpcnt;
    U1                            u1_t_dtc_act;

    if(st_s_tydc_csm_io.u1_req_sel == (U1)0U){
        u4_tp_BLO_CRI = &(st_s_tydc_csm_io.u4p_req[TYDC_CSM_REQ_0]);
    }
    else{
        u4_tp_BLO_CRI = &(st_s_tydc_csm_io.u4p_req[TYDC_CSM_REQ_1]);
    }
    u1_tp_KZK = (const U1 *)u4_tp_BLO_CRI;

    if(u1_tp_KZK[TYDC_CSM_VE_BID_KEY_US] == (U1)TYDC_RID_D903_US_MAC){

        u1_tp_MAC_RSL = (const U1 *)&(st_s_tydc_csm_io.u4p_rsl[0]);
         if((*u1_tp_MAC_RSL) == (U1)E_OK){
             u1_t_dtc_act = (U1)OXDC_DTC_TR_INA; 
         } 
         else{
             u1_t_dtc_act = (U1)OXDC_DTC_TR_ACT;
         }
    }
    else if(u1_tp_KZK[TYDC_CSM_VE_BID_KEY_US] == (U1)TYDC_RID_D903_US_BLO){

        u1_t_dtc_act  = (U1)OXDC_DTC_TR_INA;
        u4_tp_BLO_CRI = &u4_tp_BLO_CRI[TYDC_CSM_VE_REQ_KZK_VD];
        u4_tp_BLO_RSL = (const U4 *)&(st_s_tydc_csm_io.u4p_rsl[0]);
        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)TYDC_CSM_VE_IO_NWORD; u4_t_lpcnt++){
            if(u4_tp_BLO_RSL[u4_t_lpcnt] != u4_tp_BLO_CRI[u4_t_lpcnt]){
                u1_t_dtc_act = (U1)OXDC_DTC_TR_ACT;
                break;
            }
        }
    }
    else{
        u1_t_dtc_act = (U1)OXDC_DTC_TR_ACT;
    }

    return(u1_t_dtc_act);
}
/*===================================================================================================================================*/
/*  static void    vd_s_TydcXidMaKzkRx(const U2 u2_a_PDU, const ST_TYDC_KZK_RX * st_tp_RX)                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TydcXidMaKzkRx(const U2 u2_a_PDU, const ST_TYDC_KZK_RX * st_tp_RX)
{
    U4 *                          u4_tp_kzk;

    U2                            u2_t_kzk_rx;
    U2                            u2_t_wid;

    if((u2_a_PDU >= st_tp_RX->u2_pdu_min) &&
       (u2_a_PDU <= st_tp_RX->u2_pdu_max)){

        u2_t_kzk_rx = u2_a_PDU - st_tp_RX->u2_pdu_min;
        u2_t_kzk_rx = (U2)st_tp_RX->u1p_KZK_RX[u2_t_kzk_rx];

        if(u2_t_kzk_rx < (U2)TYDC_KZK_RX_NUM_PDU){

            if(st_s_tydc_csm_io.u1_req_sel == (U1)0U){
                u2_t_wid = (U2)(u2_t_kzk_rx << 1U) + (U2)TYDC_CSM_REQ_1;
            }
            else{
                u2_t_wid = u2_t_kzk_rx << 1U;
            }

            u4_tp_kzk    = &(st_s_tydc_csm_io.u4p_req[u2_t_wid]);
            u4_tp_kzk[0] = (U4)0U;
            u4_tp_kzk[1] = (U4)0U;
            (void)Com_ReadIPDU(u2_a_PDU, (U1 *)u4_tp_kzk);
            st_s_tydc_csm_io.u2_kzk_rx  |= (U2)((U2)0x0001U << u2_t_kzk_rx);

            if(u1_s_tydc_mak_uv_ctrl < (U1)TYDC_MAK_UV_CTRL_FIN){
                if((u1_s_tydc_mak_uv_rid == (U1)TYDC_MAK_UV_RID_D902) && 
                    (st_s_tydc_mak_hrec_hst.u1_kzk_rx_cnt[u2_t_kzk_rx] < (U1)TYDC_KZK_RX_CNT_MAX)){
                    st_s_tydc_mak_hrec_hst.u1_kzk_rx_cnt[u2_t_kzk_rx] += (U1)0x10U;
                }
                else if((u1_s_tydc_mak_uv_rid == (U1)TYDC_MAK_UV_RID_D903) && 
                    (st_s_tydc_mak_hrec_hst.u1_kzk_rx_cnt[u2_t_kzk_rx] < (U1)TYDC_KZK_RX_CNT_MAX)){
                    st_s_tydc_mak_hrec_hst.u1_kzk_rx_cnt[u2_t_kzk_rx]++;
                }
                else{
                    /* Do nothing */
                }
            }
        }
    }
}
/*===================================================================================================================================*/
/*  uint8   u1_g_oXDoCANAubIfMaMacUV(uint8 * u1_ap_macuv, Dem_MonitorDataType u4_a_mon)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
uint8   u1_g_oXDoCANAubIfMacUVHst(uint8 * u1_ap_macuv, Dem_MonitorDataType u4_a_mon)
{
    if(u1_ap_macuv != vdp_PTR_NA){
        u1_ap_macuv[0U] = st_s_tydc_mak_hrec_hst.u1_fact21;
        u1_ap_macuv[1U] = st_s_tydc_mak_hrec_hst.u1_fact43;
        u1_ap_macuv[2U] = st_s_tydc_mak_hrec_hst.u1_kzk_rx_cnt[TYDC_KZK_RX_CNT_IDX01];
        u1_ap_macuv[3U] = st_s_tydc_mak_hrec_hst.u1_kzk_rx_cnt[TYDC_KZK_RX_CNT_IDX02];
        u1_ap_macuv[4U] = st_s_tydc_mak_hrec_hst.u1_in_volt;
        u1_s_tydc_mak_hrec_ctrl = (U1)TYDC_MAK_HREC_CTRL_FIN;
    }
    return((uint8)E_OK);
}
#endif /* #ifdef TYDOCAN_XID_MA_CFG_H */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     7/18/2019  TN       New.                                                                                               */
/*  1.1.0    10/10/2019  TN       tydocan_xid service application interface was optimized.                                           */
/*  1.2.0    11/ 1/2019  TN       Bug Fix : Routine ID 0x100E and 0x100F could be executed during same IG cycle.                     */
/*  1.2.1     8/22/2020  HK       Fix selfcheck and codereview cs issue.                                                             */
/*  1.2.2     4/ 2/2021  HK       QAC warnigs were fixed.                                                                            */
/*  1.2.3     9/ 9/2021  TN       Redundant typecast were delete in Csm_Ab_SymKeyUpdateSc()                                          */
/*                       HK       QAC warnigs were fixed.                                                                            */
/*  1.2.4    12/14/2022  MI       Fix Phase6(XID:A901, D902, D903, D904)                                                             */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, DENSO                                                                                                    */
/*  * HK   = Hayato Kanamori, DENSO Create                                                                                           */
/*  * MI   = Masahiko Izumi, DENSO                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
