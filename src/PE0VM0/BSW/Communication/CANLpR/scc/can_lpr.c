/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  CAN L-PDU Router                                                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define CAN_LPR_C_MAJOR                          (1)
#define CAN_LPR_C_MINOR                          (0)
#define CAN_LPR_C_PATCH                          (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "can_lpr_cfg_private.h"
#include "Com.h"                      /* Com_CbkTxAck is defined        */
#include "CanSM.h"
#include "BswM_CS.h"
#include "bsw_cansm_fs.h"             /* bsw_cansm_fs_stFsSts[]         */
#include "bsw_cansm_st.h"             /* bsw_cansm_st_stChSts[]         */
#include "bsw_bswm_cs_ctrl.h"         /* bsw_bswm_cs_ctrl_u1TRXStatus[] */

#if ((defined(CAN_LPR_PHY_TX_VACK_CH)) && (CAN_LPR_PHY_TX_VACK_CH < 0xffffU))
#include "Vcc.h"               /* ehvm_vcc_clear_channel and ehvm_vcc_transmit */
#endif /* #if ((defined(CAN_LPR_PHY_TX_VACK_CH)) && (CAN_LPR_PHY_TX_VACK_CH < 0xffffU)) */

#if (CAN_CFG_CV == CAN_USE)
#include "can_rscf4_cfg.h"            /* CAN_CFG_CONTROLLERNUM_MAX      */
#endif /*(CAN_CFG_CV == CAN_USE)*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((CAN_LPR_C_MAJOR != CAN_LPR_H_MAJOR) || \
     (CAN_LPR_C_MINOR != CAN_LPR_H_MINOR) || \
     (CAN_LPR_C_PATCH != CAN_LPR_H_PATCH))
#error "can_lpr.c and can_lpr.h : source and header files are inconsistent!"
#endif

#if ((CAN_LPR_C_MAJOR != CAN_LPR_CFG_H_MAJOR) || \
     (CAN_LPR_C_MINOR != CAN_LPR_CFG_H_MINOR) || \
     (CAN_LPR_C_PATCH != CAN_LPR_CFG_H_PATCH))
#error "can_lpr.c and can_lpr_cfg_private.h : source and config files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define CAN_LPR_SDL_MAX_CL                       (8U)                     /* Service Data Length / Number of Bytes Max : CAN CLassic */
#define CAN_LPR_SDL_MAX_FD                       (64U)                    /* Service Data Length / Number of Bytes Max : CAN-FD      */
#define CAN_LPR_CAN_ID_BIT_FDF                   (0x40000000U)

#define CAN_LPR_RR_LINEAR_MAX                    (4U)
#define CAN_LPR_REGR_EN_MAX                      (0xffffffffU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define CAN_LPR_NSM_ACT_LSB_EAS                  (2U)

#define CAN_LPR_NSM_EAS_CANSM                    (9U)
#define CAN_LPR_NSM_EAS_TX_FA                    (0x01U)
#define CAN_LPR_NSM_EAS_FUL_DEE                  (0x04U)
#define CAN_LPR_NSM_EAS_FUL_EEE                  (0x06U)
#define CAN_LPR_NSM_EAS_EEE_CHK                  (0x07U)

#define CAN_LPR_NSM_LSB_CANSM_H                  (8U)
#define CAN_LPR_NSM_BIT_CANSM_L                  (0x00ffU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((defined(CAN_LPR_PHY_TX_VACK_CH)) && (CAN_LPR_PHY_TX_VACK_CH < 0xffffU))
#define vd_s_CANLpRPhyTxVAckInit()               ((void)ehvm_vcc_clear_channel((U4)CAN_LPR_PHY_TX_VACK_CH))
#define vd_s_CANLpRPhyTxVAck(u2p_ack)            ((void)ehvm_vcc_transmit((U4)CAN_LPR_PHY_TX_VACK_CH,(u2p_ack), (U4)4U))
#endif /* #if ((defined(CAN_LPR_PHY_TX_VACK_CH)) && (CAN_LPR_PHY_TX_VACK_CH < 0xffffU)) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static volatile U4      u4_s_can_lpr_regr_en;
static volatile U4      u4_s_can_lpr_phy_txlock;
static U1               u1_sp_can_lpr_nsm_trx[CAN_LPR_NUM_NET];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static inline U4      u4_s_CANLpRBinarySearch(const U4 u4_a_CAN_ID, const ST_CAN_LPR_RR * const st_ap_RR, const U2 u2_a_NUM_RR);
static inline U4      u4_s_CANLpRLinearSearch(const U4 u4_a_CAN_ID, const ST_CAN_LPR_RR * const st_ap_RR, const U2 u2_a_NUM_RR);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (CAN_LPR_RR_EN_IPDU_TX == 1U)
static void    vd_s_CANLpRIPduTxAck(void);
#endif /* #if (CAN_LPR_RR_EN_IPDU_TX == 1U) */

static void    vd_s_CANLpRPhyTxInit(const U4 u4_a_REGR_EN);
static U4      u4_s_CANLpRPhyTxReqbyCtrlr(const ST_CAN_LPR_PHY_CH * st_ap_PHY_CH,
                                                 const U4 u4_a_REGR_EN, const U4 u4_a_TXLOCK);

static void    vd_s_CANLpRPhyTxReqbyMbox(const ST_CAN_LPR_PHY_TX * st_ap_PHY_TX,
                                         const U1 u1_a_CTRLR, const U1 u1_a_MBOX, U4 * u4_ap_log);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_CANLpRInit(void)                                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_CANLpRInit(void)
{
    U4 *                                 u4_tp_log;
    U4                                   u4_t_lpcnt;

    u4_s_can_lpr_regr_en    = (U4)0U;
    u4_s_can_lpr_phy_txlock = (U4)0U;

    vd_g_CANLpFqInit();

#if (CAN_LPR_PHY_TX_VACK_CH < 0xffffU)
    vd_s_CANLpRPhyTxVAckInit();
#endif /* #if (CAN_LPR_PHY_TX_VACK_CH < 0xffffU) */

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u2_g_CAN_LPR_NUM_PHY_TX; u4_t_lpcnt++){
        u4_tp_log                         = st_gp_CAN_LPR_PHY_TX[u4_t_lpcnt].u4p_log;
        u4_tp_log[CAN_LPR_PHY_TX_LOG_FRT] = (U4)CAN_LPR_FRT_INI;
    }

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)CAN_LPR_NUM_NET; u4_t_lpcnt++){
        u1_sp_can_lpr_nsm_trx[u4_t_lpcnt] = (U1)CAN_LPR_NSM_NO__DDD;
    }

    vd_g_CANLpRCfgInit();
}
/*===================================================================================================================================*/
/*  void    vd_g_CANLpRMainTask(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_CANLpRMainTask(void)
{
    static const U1                      u1_sp_CAN_LPR_NSM_EAS_CANSM[CAN_LPR_NSM_EAS_CANSM] = {
        (U1)0x00U,  /* #define BSW_CANSM_u2CH_NOCOM            ((BswU2)0x00FFU) */
        (U1)0x02U,  /* #define BSW_CANSM_u2CH_SILENTCOM        ((BswU2)0x01FEU) */
        (U1)0x07U,  /* #define BSW_CANSM_u2CH_FULLCOM          ((BswU2)0x02FDU) */
        (U1)0x02U,  /* #define BSW_CANSM_u2CH_PRE_NOCOM_STPCTR ((BswU2)0x03FCU) */
        (U1)0x02U,  /* #define BSW_CANSM_u2CH_PRE_NOCOM_STBTRC ((BswU2)0x04FBU) */
        (U1)0x02U,  /* #define BSW_CANSM_u2CH_PRE_SILENTCOM    ((BswU2)0x05FAU) */
        (U1)0x00U,  /* #define BSW_CANSM_u2CH_FATAL            ((BswU2)0x06F9U) */
        (U1)0x00U,  /* #define BSW_CANSM_u2CH_UNINIT           ((BswU2)0x07F8U) */
        (U1)0x04U   /* #define BSW_CANSM_u2CH_PRE_FULLCOM      ((BswU2)0x08F7U) */
    };
    static const U1                      u1_sp_CAN_LPR_NSM_TRX_NEXT[] = {
        (U1)CAN_LPR_NSM_NO__DDD, (U1)CAN_LPR_NSM_NO__DDD, (U1)CAN_LPR_NSM_NO__DDD, (U1)CAN_LPR_NSM_NO__DDD,
        (U1)CAN_LPR_NSM_NO__DDD, (U1)CAN_LPR_NSM_NO__DDD, (U1)CAN_LPR_NSM_NO__DDD, (U1)CAN_LPR_NSM_NO__DDD,
        (U1)CAN_LPR_NSM_SIL_DDE, (U1)CAN_LPR_NSM_SIL_DDE, (U1)CAN_LPR_NSM_SIL_DDE, (U1)CAN_LPR_NSM_SIL_DDE,
        (U1)CAN_LPR_NSM_SIL_DDE, (U1)CAN_LPR_NSM_SIL_DDE, (U1)CAN_LPR_NSM_SIL_DDE, (U1)CAN_LPR_NSM_SIL_DDE,
        (U1)CAN_LPR_NSM_FUL_EEE, (U1)CAN_LPR_NSM_FUL_DEE, (U1)CAN_LPR_NSM_FUL_DEE, (U1)CAN_LPR_NSM_FUL_DEE,
        (U1)CAN_LPR_NSM_SIL_DDE, (U1)CAN_LPR_NSM_FUL_DEE, (U1)CAN_LPR_NSM_FUL_DEE, (U1)CAN_LPR_NSM_FUL_DEE,
        (U1)CAN_LPR_NSM_FUL_EEE, (U1)CAN_LPR_NSM_FUL_EEE, (U1)CAN_LPR_NSM_FUL_EEE, (U1)CAN_LPR_NSM_FUL_EEE,
        (U1)CAN_LPR_NSM_SIL_DDE, (U1)CAN_LPR_NSM_FUL_DEE, (U1)CAN_LPR_NSM_FUL_DEE, (U1)CAN_LPR_NSM_FUL_DEE
    };

    U4                                   u4_t_regr_en;
    U4                                   u4_t_regr_wo;
    U4                                   u4_t_lpcnt;
    U4                                   u4_t_trx;
    U4                                   u4_t_eas;
    U4                                   u4_t_net;

    U2                                   u2_t_cs_h;        /* current state / high    */
    U2                                   u2_t_cs_l;        /* current state / low     */
    U2                                   u2_t_fr;          /* failure recorvery state */

    U1                                   u1_t_txen;

#if (CAN_LPR_CFG_MAIN_START == 1U)
    vd_g_CANLpRCfgMainStart();
#endif /* #if (CAN_LPR_CFG_MAIN_START == 1U) */
    
#if (CAN_LPR_RR_EN_IPDU_TX == 1U)
    vd_s_CANLpRIPduTxAck();
#endif /* #if (CAN_LPR_RR_EN_IPDU_TX == 1U) */

    u4_t_regr_en = (U4)0U;
    u4_t_regr_wo = (U4)0U;
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)CAN_LPR_NUM_NET; u4_t_lpcnt++){

        u4_t_trx = (U4)u1_sp_can_lpr_nsm_trx[u4_t_lpcnt];
        if(u4_t_trx <= (U4)CAN_LPR_NSM_NO__DDD){

            u2_t_cs_h = bsw_cansm_st_stChSts[u4_t_lpcnt].u2CurrentChState;
            u2_t_cs_l = ((U2)CAN_LPR_NSM_BIT_CANSM_L ^ u2_t_cs_h) & (U2)CAN_LPR_NSM_BIT_CANSM_L;
            u2_t_cs_h = u2_t_cs_h >> CAN_LPR_NSM_LSB_CANSM_H;
            if((u2_t_cs_h == u2_t_cs_l                ) &&
               (u2_t_cs_h <  (U2)CAN_LPR_NSM_EAS_CANSM)){
                u4_t_eas = (U4)u1_sp_CAN_LPR_NSM_EAS_CANSM[u2_t_cs_h];
            }
            else{
                u4_t_eas = (U4)0U;
            }

#if (BSW_COMM_BUS_TYPE_OFFSET(CAN) > 0U)
            u4_t_net  = u4_t_lpcnt + (U4)BSW_COMM_BUS_TYPE_OFFSET(CAN);
            u1_t_txen = bsw_bswm_cs_ctrl_u1TRXStatus[u4_t_net];
#else
            u1_t_txen = bsw_bswm_cs_ctrl_u1TRXStatus[u4_t_lpcnt];
#endif /* #if (BSW_COMM_BUS_TYPE_OFFSET(CAN) > 0U) */
            if((u4_t_eas  == (U4)CAN_LPR_NSM_EAS_EEE_CHK     ) &&
               (u1_t_txen == (U1)BSW_BSWM_CS_TRXST_TRX_ENABLE)){
                u4_t_eas = (U4)CAN_LPR_NSM_EAS_FUL_EEE;
            }
            else{
                u4_t_eas = (U4)CAN_LPR_NSM_EAS_FUL_DEE;
            }

            u2_t_fr = bsw_cansm_fs_stFsSts[u4_t_lpcnt].u2FailRcvState;
            if(u2_t_fr != BSW_CANSM_u2FS_NO_FAIL){
                u4_t_eas |= (U4)CAN_LPR_NSM_EAS_TX_FA;
            }

            u4_t_trx = (u4_t_eas << CAN_LPR_NSM_ACT_LSB_EAS) + u4_t_trx;
            u4_t_trx = (U4)u1_sp_CAN_LPR_NSM_TRX_NEXT[u4_t_trx];
            if(u4_t_trx < (U4)CAN_LPR_NSM_NO__DDD){
                u4_t_net      = u4_t_regr_wo + u4_t_trx;
                u4_t_regr_en |= u4_gp_CAN_LPR_REGR_EN_BY_NET[u4_t_net];
            }
        }
        else{
            u4_t_trx = (U4)CAN_LPR_NSM_NO__DDD;
        }
        u1_sp_can_lpr_nsm_trx[u4_t_lpcnt]  = (U1)u4_t_trx;
        u4_t_regr_wo                      += (U4)CAN_LPR_NSM_NUM_TRX;
    }  /* for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)CAN_LPR_NUM_NET; u4_t_lpcnt++){ */

    u4_t_regr_en &= u4_g_CANLpRCfgEgrEnabled();

    /* ----------------------------------------------------------------------------------------------------- */
    /* Attention :                                                                                           */
    /* ----------------------------------------------------------------------------------------------------- */
    /* vd_s_CANLpRPhyTxInit shall be invoked before u4_s_can_lpr_regr_en = u4_t_regr_en;                     */
    /* ----------------------------------------------------------------------------------------------------- */
    vd_s_CANLpRPhyTxInit(u4_t_regr_en);

    /* ----------------------------------------------------------------------------------------------------- */
    /* Attention :                                                                                           */
    /* ----------------------------------------------------------------------------------------------------- */
    /* u4_s_can_lpr_regr_en shall be updated at end of vd_g_CANLpRMainTask in order to prevent from data     */
    /* race issue.                                                                                           */
    /* ----------------------------------------------------------------------------------------------------- */
    u4_s_can_lpr_regr_en = u4_t_regr_en;

#if (CAN_LPR_CFG_MAIN_FINISH == 1U)
    vd_g_CANLpRCfgMainFinish();
#endif /* #if (CAN_LPR_CFG_MAIN_FINISH == 1U) */
}
/*===================================================================================================================================*/
/*  uint8   u1_g_CANLpRIngCANRx(const uint8 u1_a_ING_CAN_RX, const uint8 u1_a_MBOX, const CanMsgType * st_ap_CAN_RX))                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
uint8   u1_g_CANLpRIngCANRx(const uint8 u1_a_ING_CAN_RX, const uint8 u1_a_MBOX, const CanMsgType * st_ap_CAN_RX)
{
    const ST_CAN_LPR_ING *               st_tp_ING;
    const ST_CAN_LPR_RRMB *              st_tp_RRMB;
    const ST_CAN_LPR_RR *                st_tp_RR;

    U4                                   u4_t_cid;
    U4                                   u4_t_fdf;

    U4                                   u4_t_rr;
    U4                                   u4_t_rr_end;
    U4                                   u4_t_ifrx_en;

    U2                                   u2_t_sdl_max;
    U2                                   u2_t_sdl_rx;
    U2                                   u2_t_num_rr;
    U2                                   u2_t_mbox;
    U2                                   u2_t_mb_min;
    U2                                   u2_t_mb_max;

    U1                                   u1_t_canif_rx;

    u4_t_cid = st_ap_CAN_RX->u4Id;
    u4_t_fdf = u4_t_cid & (U4)CAN_LPR_CAN_ID_BIT_FDF;
    if(u4_t_fdf != (U4)0U){
        u2_t_sdl_max = (U2)CAN_LPR_SDL_MAX_FD;
    }
    else{
        u2_t_sdl_max = (U2)CAN_LPR_SDL_MAX_CL;
    }

    u2_t_sdl_rx = (U2)st_ap_CAN_RX->u1Length;
    if(u2_t_sdl_rx > u2_t_sdl_max){
        u1_t_canif_rx = (U1)CAN_PROC_NG;
    }
    else if(u1_a_ING_CAN_RX >= u1_g_CAN_LPR_NUM_ING){
        u1_t_canif_rx = (U1)CAN_PROC_OK;
    }
    else if(stp_gp_CAN_LPR_ING[u1_a_ING_CAN_RX] == NULL_PTR){
        u1_t_canif_rx = (U1)CAN_PROC_OK;
    }
    else{

        st_tp_ING   = stp_gp_CAN_LPR_ING[u1_a_ING_CAN_RX];

        u2_t_mbox   = (U2)u1_a_MBOX;
        u2_t_mb_min = st_tp_ING->u2_mb_min;
        u2_t_mb_max = st_tp_ING->u2_mb_max;
        if((u2_t_mbox >= u2_t_mb_min) && 
           (u2_t_mbox <= u2_t_mb_max)){ 

            u2_t_mbox   = u2_t_mbox - u2_t_mb_min;
            st_tp_RRMB  = st_tp_ING->stp_RRMB;
            st_tp_RRMB  = &st_tp_RRMB[u2_t_mbox];

            u4_t_rr     = (U4)st_tp_RRMB->u2_rr_begin;
            u2_t_num_rr = st_tp_RRMB->u2_num_rr;
            u4_t_rr_end = u4_t_rr + (U4)u2_t_num_rr;
            if(u4_t_rr_end <= (U4)st_tp_ING->u2_num_rr){

                st_tp_RR = st_tp_ING->stp_RR;
                st_tp_RR = &st_tp_RR[u4_t_rr];
                if(u2_t_num_rr <= (U2)CAN_LPR_RR_LINEAR_MAX){
                    u4_t_rr = u4_s_CANLpRLinearSearch(u4_t_cid, st_tp_RR, u2_t_num_rr);
                }
                else{
                    u4_t_rr = u4_s_CANLpRBinarySearch(u4_t_cid, st_tp_RR, u2_t_num_rr);
                }   /* if nest #4 */
            }
            else{
                u4_t_rr     = (U4)CAN_LPR_RR_UNK;
                u2_t_num_rr = (U2)0U;
            }       /* if nest #3 */
        }
        else{
            u4_t_rr     = (U4)CAN_LPR_RR_UNK;
            u2_t_num_rr = (U2)0U;
        }           /* if nest #2 */

        if(u4_t_rr >= (U4)u2_t_num_rr){
            u1_t_canif_rx = (U1)CAN_PROC_OK;
        }
        else if(u2_t_sdl_rx < st_tp_RR[u4_t_rr].u2_sdl_min){
            u1_t_canif_rx = (U1)CAN_PROC_NG;
        }
        else{
            vd_g_CANLpREgrbyRule(st_tp_ING, &st_tp_RR[u4_t_rr], st_ap_CAN_RX);

            u4_t_ifrx_en = st_tp_ING->u4_ifrx_en & st_tp_RR[u4_t_rr].u4_regr_en;
            if(u4_t_ifrx_en == (U4)0U){
                u1_t_canif_rx = (U1)CAN_PROC_NG;
            }
            else{
                u1_t_canif_rx = (U1)CAN_PROC_OK;
            }
        }
    }

    return(u1_t_canif_rx);
}
/*===================================================================================================================================*/
/*  void    vd_g_CANLpREgrbyRule(const ST_CAN_LPR_ING * const st_ap_ING,                                                             */
/*                               const ST_CAN_LPR_RR * const st_ap_RR, const CanMsgType * const st_ap_ECAN)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_CANLpREgrbyRule(const ST_CAN_LPR_ING * const st_ap_ING,
                             const ST_CAN_LPR_RR * const st_ap_RR, const CanMsgType * const st_ap_ECAN)
{
    const ST_CAN_LPR_EGR *               st_tp_EGR;
    const U2 *                           u2_tp_EPDU_ID;
    U4                                   u4_t_regr_en;
    U4                                   u4_t_num_egr;
    U4                                   u4_t_lpcnt;
    U4                                   u4_t_run;

    U2                                   u2_t_ep_begin;

    u4_t_regr_en = u4_s_can_lpr_regr_en & st_ap_RR->u4_regr_en;
    if(u4_t_regr_en != (U4)0U){

        st_tp_EGR     = st_ap_ING->stp_EGR;
        u2_tp_EPDU_ID = st_ap_ING->u2p_EPDU_ID;
        u4_t_num_egr  = (U4)st_ap_ING->u2_num_egr;

        u2_t_ep_begin = st_ap_RR->u2_ep_begin;
        u2_tp_EPDU_ID = &u2_tp_EPDU_ID[u2_t_ep_begin];

        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < u4_t_num_egr; u4_t_lpcnt++){

            u4_t_run = u4_t_regr_en & st_tp_EGR[u4_t_lpcnt].u4_regr_en;
            if(u4_t_run != (U4)0U){
                (*st_tp_EGR[u4_t_lpcnt].fp_vd_EGR)(u2_tp_EPDU_ID[u4_t_lpcnt], st_ap_ECAN);
            }
        }
    }
}
/*===================================================================================================================================*/

#if (CAN_LPR_RR_EN_IPDU_TX == 1U)

/*===================================================================================================================================*/
/*  uint8   u1_g_CANLpRIngIPduTx(const PduIdType u2_a_RK, const PduInfoType * st_ap_RPDU_TX)                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
uint8   u1_g_CANLpRIngIPduTx(const PduIdType u2_a_RK, const PduInfoType * st_ap_RPDU_TX)
{
    const ST_CAN_LPR_IPDU_TX *           st_tp_IPDU_TX;
    const U1 *                           u1_tp_SRC;
    U1 *                                 u1_tp_dst;

    U4                                   u4_tp_can[CAN_LPFQ_PDU_NW_MAX];
    U4                                   u4_t_regr_en;
    U4                                   u4_t_nb_sdu;
    U4                                   u4_t_lpcnt;
    U1                                   u1_t_tx_en;

    u1_t_tx_en = (U1)TRUE;

    if(u2_a_RK < (U2)CAN_LPR_NUM_IPDU_TX){

        st_tp_IPDU_TX = &st_gp_CAN_LPR_IPDU_TX[u2_a_RK];
        u4_t_regr_en  = st_tp_IPDU_TX->u4_regr_en;
        if(u4_t_regr_en != (U4)0U){

            u1_t_tx_en    = (U1)FALSE;

            u4_t_regr_en &= u4_s_can_lpr_regr_en;
            u1_tp_SRC     = st_ap_RPDU_TX->SduDataPtr;
            u4_t_nb_sdu   = st_ap_RPDU_TX->SduLength;
            if((u4_t_regr_en != (U4)0U                 ) &&
               (u1_tp_SRC    != NULL_PTR               ) &&
               (u4_t_nb_sdu  <= (U4)CAN_LPFQ_SDU_NB_MAX)){

                u4_tp_can[CAN_LPFQ_WO_HEAD]   = ((U4)st_tp_IPDU_TX->u2_epdu_id << CAN_LPFQ_HD_LSB_PDU_ID) | u4_t_nb_sdu;
                u4_tp_can[CAN_LPFQ_WO_CAN_ID] = st_tp_IPDU_TX->u4_can_id;

                u1_tp_dst                     = (U1 *)&u4_tp_can[CAN_LPFQ_WO_SDU_B0];
                for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < u4_t_nb_sdu; u4_t_lpcnt++){
                    u1_tp_dst[u4_t_lpcnt] = u1_tp_SRC[u4_t_lpcnt];
                }

                (void)(*st_tp_IPDU_TX->fp_u1_ENQ_CH)(st_tp_IPDU_TX->u2_que_ch, &u4_tp_can[0U]);
            }
        }
    }

    return(u1_t_tx_en);
}
#endif /* #if (CAN_LPR_RR_EN_IPDU_TX == 1U) */
/*===================================================================================================================================*/
/*  void    vd_g_CANLpRPhyTxPosHigh(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_CANLpRPhyTxPosHigh(void)
{
    const ST_CAN_LPR_PHY_CH *            st_tp_PHY_CH;

    U4                                   u4_t_regr_en;
    U4                                   u4_t_ch;
    U4                                   u4_t_lptx_en;
    U4                                   u4_t_txlock;

    u4_t_txlock  = (U4)0U;
    u4_t_regr_en = u4_s_can_lpr_regr_en;
    for(u4_t_ch = (U4)0U; u4_t_ch < (U4)u1_g_CAN_LPR_NUM_PHY_CH; u4_t_ch++){

        st_tp_PHY_CH = &st_gp_CAN_LPR_PHY_CH[u4_t_ch];
        u4_t_lptx_en = u4_t_regr_en & st_tp_PHY_CH->u4_regr_en;
        if(u4_t_lptx_en != (U4)0U){
            u4_t_txlock |= u4_s_CANLpRPhyTxReqbyCtrlr(st_tp_PHY_CH, u4_t_regr_en, u4_t_lptx_en);
        }
    }
    u4_s_can_lpr_phy_txlock = u4_t_txlock;
}
/*===================================================================================================================================*/
/*  void    vd_g_CANLpRPhyTxAck(const uint8 u1_a_CTRLR, const uint8 u1_a_MBOX)                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_CANLpRPhyTxAck(const uint8 u1_a_CTRLR, const uint8 u1_a_MBOX)
{
    const ST_CAN_LPR_PHY_CH *            st_tp_PHY_CH;
    const ST_CAN_LPR_PHY_TX *            st_tp_PHY_TX;
    U4 *                                 u4_tp_log;

    U4                                   u4_t_frt;
    U4                                   u4_t_lptx_en;
    U4                                   u4_t_regr_en;

#if (CAN_LPR_RR_EN_IPDU_TX == 1U)
    U4                                   u4_t_head;
#endif

    if(u1_a_CTRLR < u1_g_CAN_LPR_NUM_PHY_CTRLR){

        st_tp_PHY_CH = stp_gp_CAN_LPR_PHY_CH_BY_CTRLR[u1_a_CTRLR];
        if((st_tp_PHY_CH             != NULL_PTR      ) &&
           (st_tp_PHY_CH->u2_ctrlr   == (U2)u1_a_CTRLR) &&
           (st_tp_PHY_CH->u2_nphy_tx >  (U2)u1_a_MBOX )){

            st_tp_PHY_TX = st_tp_PHY_CH->stp_PHY_TX;
            st_tp_PHY_TX = &st_tp_PHY_TX[u1_a_MBOX];

            u4_tp_log    = st_tp_PHY_TX->u4p_log;
            u4_t_frt     = u4_tp_log[CAN_LPR_PHY_TX_LOG_FRT];
            if(u4_t_frt <= (U4)CAN_LPR_FRT_MAX){

#if ((defined(CAN_LPR_PHY_TX_VACK_CH)) && (CAN_LPR_PHY_TX_VACK_CH < 0xffffU))
                if(st_tp_PHY_TX->u2_vack == (U2)CAN_LPR_PHY_TX_VACK_EN){
                    vd_s_CANLpRPhyTxVAck(&u4_tp_log[CAN_LPR_PHY_TX_LOG_CAN_ID]);
                }
#endif /* #if ((defined(CAN_LPR_PHY_TX_VACK_CH)) && (CAN_LPR_PHY_TX_VACK_CH < 0xffffU)) */

#if (CAN_LPR_RR_EN_IPDU_TX == 1U)
                u4_t_head = u4_tp_log[CAN_LPR_PHY_TX_LOG_HEAD] >> (CAN_LPFQ_HD_LSB_PDU_ID + CAN_LPR_FQ_CAN_LSB_PDU_ID);
                if(u4_t_head < (U4)CAN_LPR_NUM_IPDU_TX){
                    u4_tp_log[CAN_LPR_PHY_TX_LOG_HEAD] = u4_t_head << CAN_LPFQ_HD_LSB_PDU_ID;
                    (void)u1_g_CANLpFqEnqCh((U2)CAN_LPFQ_CH_IPDU_TX_ACK, &u4_tp_log[CAN_LPR_PHY_TX_LOG_HEAD]);
                }
#endif /* #if (CAN_LPR_RR_PHY_CAN_TX_EN == 2U) && \ */

                u4_t_lptx_en = st_tp_PHY_CH->u4_regr_en | st_tp_PHY_TX->u4_regr_en;
                u4_t_regr_en = u4_s_can_lpr_regr_en & u4_t_lptx_en;
                if(u4_t_regr_en == u4_t_lptx_en){
                    vd_s_CANLpRPhyTxReqbyMbox(st_tp_PHY_TX, u1_a_CTRLR, u1_a_MBOX, u4_tp_log);
                }
                else{
                    u4_tp_log[CAN_LPR_PHY_TX_LOG_FRT] = (U4)CAN_LPR_FRT_INI;
                }
            }  /* if(u4_t_frt <= (U4)CAN_LPR_FRT_MAX){               */
        }      /* if((st_tp_PHY_CH             != NULL_PTR      ) && */
    }          /* if(u1_a_CTRLR < u1_g_CAN_LPR_NUM_PHY_CTRLR){       */
}
/*===================================================================================================================================*/
/*  uint8   u1_g_CANLpRPhyTxLock(const uint8 u1_a_NET)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
uint8   u1_g_CANLpRPhyTxLock(const uint8 u1_a_NET)
{
#if (BSW_COMM_BUS_TYPE_OFFSET(CAN) > 0U)
    static const U1                      u1_s_CAN_LPR_NET_MIN = (U1)BSW_COMM_BUS_TYPE_OFFSET(CAN);
    static const U1                      u1_s_CAN_LPR_NET_ULM = (U1)BSW_COMM_BUS_TYPE_OFFSET(CAN) + (U1)BSW_COMM_BUS_TYPE_CHNUM(CAN);
    U4                                   u4_t_bit;
    U1                                   u1_t_txlock;

    u1_t_txlock = (U1)BSW_CANSM_FAIL_NONE;
    if((u1_a_NET >= u1_s_CAN_LPR_NET_MIN) &&
       (u1_a_NET <  u1_s_CAN_LPR_NET_ULM)){

        u4_t_bit = ((U4)u1_a_NET - (U4)u1_s_CAN_LPR_NET_MIN) * (U4)CAN_LPR_NSM_NUM_TRX;
        u4_t_bit = u4_s_can_lpr_phy_txlock & u4_gp_CAN_LPR_REGR_EN_BY_NET[u4_t_bit];
        if(u4_t_bit != (U4)0U){
            u1_t_txlock = (U1)BSW_CANSM_FAIL_USER;
        }
    }

    return(u1_t_txlock);
#else
    static const U1                      u1_s_CAN_LPR_NET_ULM = (U1)BSW_COMM_BUS_TYPE_CHNUM(CAN);
    U4                                   u4_t_bit;
    U1                                   u1_t_txlock;

    u1_t_txlock = (U1)BSW_CANSM_FAIL_NONE;
    if(u1_a_NET < u1_s_CAN_LPR_NET_ULM){

        u4_t_bit = (U4)u1_a_NET * (U4)CAN_LPR_NSM_NUM_TRX;
        u4_t_bit = u4_s_can_lpr_phy_txlock & u4_gp_CAN_LPR_REGR_EN_BY_NET[u4_t_bit];
        if(u4_t_bit != (U4)0U){
            u1_t_txlock = (U1)BSW_CANSM_FAIL_USER;
        }
    }

    return(u1_t_txlock);
#endif /* #if (BSW_COMM_BUS_TYPE_OFFSET(CAN) > 0U) */
}
/*===================================================================================================================================*/
/*  void    vd_g_CANLpREgrFqCAN(const U2 u2_a_EPDU_ID, const CanMsgType * const st_ap_ECAN)                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
#if (CAN_LPR_CFG_DET == 1U)
void    vd_g_CANLpREgrFqCAN(const U2 u2_a_EPDU_ID, const CanMsgType * const st_ap_ECAN)
{
    U2                                   u2_t_fq_ch;
    U2                                   u2_t_pdu_id;
    U1                                   u1_t_eas_chk;

    u2_t_fq_ch   = u2_a_EPDU_ID & (U2)CAN_LPR_FQ_CAN_BIT_FQ_CH;
    u2_t_pdu_id  = u2_a_EPDU_ID >> CAN_LPR_FQ_CAN_LSB_PDU_ID;
    u1_t_eas_chk = u1_g_CANLpFqEnqCAN(u2_t_fq_ch, u2_t_pdu_id, st_ap_ECAN);
    if(u1_t_eas_chk != (U1)CAN_LPFQ_EAS_REQ_ACPT){
        vd_g_CANLpRCfgDet((U1)CAN_LPR_DET_FQ_CAN, u1_t_eas_chk, st_ap_ECAN->u4Id);
    }
}
#else
void    vd_g_CANLpREgrFqCAN(const U2 u2_a_EPDU_ID, const CanMsgType * const st_ap_ECAN)
{
    U2                                   u2_t_fq_ch;
    U2                                   u2_t_pdu_id;

    u2_t_fq_ch  = u2_a_EPDU_ID & (U2)CAN_LPR_FQ_CAN_BIT_FQ_CH;
    u2_t_pdu_id = u2_a_EPDU_ID >> CAN_LPR_FQ_CAN_LSB_PDU_ID;
    (void)u1_g_CANLpFqEnqCAN(u2_t_fq_ch, u2_t_pdu_id, st_ap_ECAN);
}
#endif  /* #if (CAN_LPR_CFG_DET == 1U) */
/*===================================================================================================================================*/
/*  static inline U4      u4_s_CANLpRBinarySearch(const U4 u4_a_CAN_ID, const ST_CAN_LPR_RR * const st_ap_RR, const U2 u2_a_NUM_RR)  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline U4      u4_s_CANLpRBinarySearch(const U4 u4_a_CAN_ID, const ST_CAN_LPR_RR * const st_ap_RR, const U2 u2_a_NUM_RR)
{
    U4                                   u4_t_rr_min;
    U4                                   u4_t_rr_max;

    U4                                   u4_t_rr;
    U4                                   u4_t_rr_rslt;

    if(u4_a_CAN_ID < st_ap_RR[0U].u4_cid_min){
        u4_t_rr_rslt = (U4)CAN_LPR_RR_UNK;
    }
    else if(u4_a_CAN_ID <= st_ap_RR[0U].u4_cid_max){
        u4_t_rr_rslt = (U4)0U;
    }
    else{

        u4_t_rr_rslt = (U4)CAN_LPR_RR_UNK;
        u4_t_rr_min  = (U4)1U;
        u4_t_rr_max  = (U4)u2_a_NUM_RR - (U4)1U;
        do{
            u4_t_rr  = (u4_t_rr_min + u4_t_rr_max) >> 1U;
            if(u4_a_CAN_ID < st_ap_RR[u4_t_rr].u4_cid_min){
                u4_t_rr_max = u4_t_rr - (U4)1U;
            }
            else if(u4_a_CAN_ID <= st_ap_RR[u4_t_rr].u4_cid_max){
                u4_t_rr_rslt = u4_t_rr;
                break;
            }
            else{
                u4_t_rr_min = u4_t_rr + (U4)1U;
            }
        }
        while(u4_t_rr_min <= u4_t_rr_max);
    }

    return(u4_t_rr_rslt);
}
/*===================================================================================================================================*/
/*  static inline U4      u4_s_CANLpRLinearSearch(const U4 u4_a_CAN_ID, const ST_CAN_LPR_RR * const st_ap_RR, const U2 u2_a_NUM_RR)  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline U4      u4_s_CANLpRLinearSearch(const U4 u4_a_CAN_ID, const ST_CAN_LPR_RR * const st_ap_RR, const U2 u2_a_NUM_RR)
{
    U4                                   u4_t_rr_rslt;
    U4                                   u4_t_rr;

    u4_t_rr_rslt = (U4)CAN_LPR_RR_UNK;
    for(u4_t_rr = (U4)0U; u4_t_rr < (U4)u2_a_NUM_RR; u4_t_rr++){

        if(u4_a_CAN_ID < st_ap_RR[u4_t_rr].u4_cid_min){
            break;
        }
        else if(u4_a_CAN_ID <= st_ap_RR[u4_t_rr].u4_cid_max){
            u4_t_rr_rslt = u4_t_rr;
            break;
        }
        else{
            /* do nothing */
        }
    }

    return(u4_t_rr_rslt);
}
/*===================================================================================================================================*/

#if (CAN_LPR_RR_EN_IPDU_TX == 1U)

/*===================================================================================================================================*/
/*  static void    vd_s_CANLpRIPduTxAck(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_CANLpRIPduTxAck(void)
{
    U4                                   u4_tp_ack[CAN_LPFQ_PDU_NW_MAX];

    U4                                   u4_t_lpcnt;
    U4                                   u4_t_ipdu_tx;
    U1                                   u1_t_eas_chk;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)CAN_LPR_NUM_IPDU_TX; u4_t_lpcnt++){

        u1_t_eas_chk = u1_g_CANLpFqDeqCh((U2)CAN_LPFQ_CH_IPDU_TX_ACK, &u4_tp_ack[0U], (U2)CAN_LPFQ_PDU_NW_MAX);
        if(u1_t_eas_chk == (U1)CAN_LPFQ_EAS_REQ_ACPT){
            u4_t_ipdu_tx = u4_tp_ack[CAN_LPFQ_WO_HEAD] >> CAN_LPFQ_HD_LSB_PDU_ID;
            Com_CbkTxAck((U2)u4_t_ipdu_tx);
        }
        else{
            break;
        }
    }
}
#endif /* #if (CAN_LPR_RR_EN_IPDU_TX == 1U) */
/*===================================================================================================================================*/
/*  static void    vd_s_CANLpRPhyTxInit(const U4 u4_a_REGR_EN)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_CANLpRPhyTxInit(const U4 u4_a_REGR_EN)
{
    const ST_CAN_LPR_PHY_TX *            st_tp_PHY_TX;
    U4 *                                 u4_tp_log;

    U4                                   u4_t_init;
    U4                                   u4_t_que_en;
    U4                                   u4_t_lpcnt;

    u4_t_init = u4_s_can_lpr_regr_en;
    u4_t_init = (u4_t_init ^ u4_a_REGR_EN) & u4_a_REGR_EN;
    if(u4_t_init != (U4)0U){

        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u2_g_CAN_LPR_NUM_PHY_TX; u4_t_lpcnt++){

            st_tp_PHY_TX = &st_gp_CAN_LPR_PHY_TX[u4_t_lpcnt];
            u4_t_que_en  = u4_t_init & st_tp_PHY_TX->u4_regr_en;
            if(u4_t_que_en != (U4)0U){

                u4_tp_log                         = st_tp_PHY_TX->u4p_log;
                u4_tp_log[CAN_LPR_PHY_TX_LOG_FRT] = (U4)CAN_LPR_FRT_INI;

                (*st_tp_PHY_TX->fp_vd_RES_CH)(st_tp_PHY_TX->u2_que_ch);
            }
        }
    }
}
/*===================================================================================================================================*/
/*  static U4      u4_s_CANLpRPhyTxReqbyCtrlr(const ST_CAN_LPR_PHY_CH * st_ap_PHY_CH,                                                */
/*                                                   const U4 u4_a_REGR_EN, const U4 u4_a_TXLOCK)                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_CANLpRPhyTxReqbyCtrlr(const ST_CAN_LPR_PHY_CH * st_ap_PHY_CH,
                                                 const U4 u4_a_REGR_EN, const U4 u4_a_TXLOCK)
{
    const ST_CAN_LPR_PHY_TX *            st_tp_PHY_TX;
    U4 *                                 u4_tp_log;

    U4                                   u4_t_lpfq_en;
    U4                                   u4_t_tout;
    U4                                   u4_t_nphy_tx;

    U4                                   u4_t_txlock;
    U4                                   u4_t_mbox;
    U4                                   u4_t_frt_tx;
    U4                                   u4_t_frt;
    U4                                   u4_t_elpsd;

    U1                                   u1_t_ctrlr;

    u4_t_txlock  = (U4)0U;
    u4_t_tout    = u4_g_CAN_LPR_PHY_TX_TOUT;

    st_tp_PHY_TX = st_ap_PHY_CH->stp_PHY_TX;
    u4_t_nphy_tx = (U4)st_ap_PHY_CH->u2_nphy_tx;
    u1_t_ctrlr   = (U1)st_ap_PHY_CH->u2_ctrlr;
    for(u4_t_mbox = (U4)0U; u4_t_mbox < u4_t_nphy_tx; u4_t_mbox++){

        u4_t_lpfq_en = u4_a_REGR_EN & st_tp_PHY_TX[u4_t_mbox].u4_regr_en;
        u4_tp_log    = st_tp_PHY_TX[u4_t_mbox].u4p_log;
        u4_t_frt_tx  = u4_tp_log[CAN_LPR_PHY_TX_LOG_FRT];
        if(u4_t_lpfq_en == (U4)0U){
            /* do nothing */
        }
        else if(u4_t_frt_tx > (U4)CAN_LPR_FRT_MAX){
            vd_s_CANLpRPhyTxReqbyMbox(&st_tp_PHY_TX[u4_t_mbox], u1_t_ctrlr, (U1)u4_t_mbox, u4_tp_log);
        }
        else{
            u4_t_frt   = (*u4p_g_GPT_FRT_RA);
            u4_t_elpsd = (u4_t_frt - u4_t_frt_tx) & (U4)CAN_LPR_FRT_MAX;
            if(u4_t_elpsd >= u4_t_tout){
                u4_tp_log[CAN_LPR_PHY_TX_LOG_FRT] = (u4_t_frt - u4_t_tout) & (U4)CAN_LPR_FRT_MAX;
                u4_t_txlock                       = u4_a_TXLOCK;
                break;
            }
        }
    }

    return(u4_t_txlock);
}
/*===================================================================================================================================*/
/*  static void    vd_s_CANLpRPhyTxReqbyMbox(const ST_CAN_LPR_PHY_TX * st_ap_PHY_TX,                                                 */
/*                                           const U1 u1_a_CTRLR, const U1 u1_a_MBOX, U4 * u4_ap_log)                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_CANLpRPhyTxReqbyMbox(const ST_CAN_LPR_PHY_TX * st_ap_PHY_TX,
                                         const U1 u1_a_CTRLR, const U1 u1_a_MBOX, U4 * u4_ap_log)
{
    CanMsgType                           st_t_can;

    U4                                   u4_tp_pdu_tx[CAN_LPR_PHY_TX_PDU_NW_MAX];
    U4                                   u4_t_head;
    U4                                   u4_t_can_id;
    U1                                   u1_t_eas_chk;

    u1_t_eas_chk = (*st_ap_PHY_TX->fp_u1_DEQ_CH)(st_ap_PHY_TX->u2_que_ch, &u4_tp_pdu_tx[0U], (U2)CAN_LPR_PHY_TX_PDU_NW_MAX);
    if(u1_t_eas_chk == (U1)CAN_LPR_PHY_TX_REQ_ACPT){

        u4_t_head         = u4_tp_pdu_tx[CAN_LPR_PHY_TX_REQ_HEAD];
        u4_t_can_id       = u4_tp_pdu_tx[CAN_LPR_PHY_TX_REQ_CAN_ID];

        st_t_can.ptData   = (U1 *)&u4_tp_pdu_tx[CAN_LPR_PHY_TX_REQ_SDU_B0];
        st_t_can.u4Id     = u4_t_can_id;
        st_t_can.u1Length = (U1)u4_t_head;

        u4_ap_log[CAN_LPR_PHY_TX_LOG_HEAD]   = u4_t_head;
        u4_ap_log[CAN_LPR_PHY_TX_LOG_CAN_ID] = u4_t_can_id;

        /* ----------------------------------------------------------------------------------------------------- */
        /* Attention :                                                                                           */
        /* ----------------------------------------------------------------------------------------------------- */
        /* u4_ap_log[CAN_LPR_PHY_TX_LOG_FRT] shall be updated before Can_TxReq in order to prevent from data     */
        /* race issue                                                                                            */
        /* ----------------------------------------------------------------------------------------------------- */
        u4_ap_log[CAN_LPR_PHY_TX_LOG_FRT]    = (*u4p_g_GPT_FRT_RA) & (U4)CAN_LPR_FRT_MAX;

#if (CAN_CFG_CV != CAN_USE)

#if (CAN_LPR_CFG_DET == 1U)
        u1_t_eas_chk = Can_TxReq(u1_a_CTRLR, u1_a_MBOX, &st_t_can);
        if(u1_t_eas_chk != (U1)CAN_PROC_OK){
            vd_g_CANLpRCfgDet((U1)CAN_LPR_DET_PHY_TX, u1_t_eas_chk, u4_t_can_id);
        }
#else   /* #if (CAN_LPR_CFG_DET == 1U) */
        (void)Can_TxReq(u1_a_CTRLR, u1_a_MBOX, &st_t_can);
#endif  /* #if (CAN_LPR_CFG_DET == 1U) */


#else  /* #if (CAN_CFG_CV != CAN_USE) */


#if (CAN_LPR_CFG_DET == 1U)
        if(u1_a_CTRLR < (U1)CAN_CFG_CONTROLLERNUM_MAX){
            u1_t_eas_chk = Can_IP0_TxReq(u1_a_CTRLR, u1_a_MBOX, &st_t_can);
        } else {
            u1_t_eas_chk = Can_IP1_TxReq((u1_a_CTRLR - (U1)CAN_CFG_CONTROLLERNUM_MAX), u1_a_MBOX, &st_t_can);
        }
        if(u1_t_eas_chk != (U1)CAN_PROC_OK){
            vd_g_CANLpRCfgDet((U1)CAN_LPR_DET_PHY_TX, u1_t_eas_chk, u4_t_can_id);
        }
#else   /* #if (CAN_LPR_CFG_DET == 1U) */
        if(u1_a_CTRLR < (U1)CAN_CFG_CONTROLLERNUM_MAX){
            (void)Can_IP0_TxReq(u1_a_CTRLR, u1_a_MBOX, &st_t_can);
        } else {
            (void)Can_IP1_TxReq((u1_a_CTRLR - (U1)CAN_CFG_CONTROLLERNUM_MAX), u1_a_MBOX, &st_t_can);
        }
#endif  /* #if (CAN_LPR_CFG_DET == 1U) */

#endif/*(CAN_CFG_CV != CAN_USE)*/
    }
    else{
        u4_ap_log[CAN_LPR_PHY_TX_LOG_FRT] = (U4)CAN_LPR_FRT_INI;
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
/*  1.0.0     3/18/2025  TN       New.                                                                                               */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
