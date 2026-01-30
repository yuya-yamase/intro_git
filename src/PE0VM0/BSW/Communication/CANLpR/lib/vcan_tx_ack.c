/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Virtual CAN Tx Ack                                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VCAN_TX_ACK_C_MAJOR                      (1)
#define VCAN_TX_ACK_C_MINOR                      (0)
#define VCAN_TX_ACK_C_PATCH                      (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "vcan_tx_ack_cfg_private.h"
#include "CanIf_Cbk.h"                /* void CanIf_TxConfirmation( PduIdType CanTxPduId ); */
#include "Vcc.h"                      /* ehvm_vcc_transmit(...) and ehvm_vcc_receive(...)   */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((VCAN_TX_ACK_C_MAJOR != VCAN_TX_ACK_H_MAJOR) || \
     (VCAN_TX_ACK_C_MINOR != VCAN_TX_ACK_H_MINOR) || \
     (VCAN_TX_ACK_C_PATCH != VCAN_TX_ACK_H_PATCH))
#error "vcan_tx_ack.c and vcan_tx_ack.h : source and header files are inconsistent!"
#endif

#if ((VCAN_TX_ACK_C_MAJOR != VCAN_TX_ACK_H_MAJOR) || \
     (VCAN_TX_ACK_C_MINOR != VCAN_TX_ACK_H_MINOR) || \
     (VCAN_TX_ACK_C_PATCH != VCAN_TX_ACK_H_PATCH))
#error "can_lpr_tx_vack.c and vcan_tx_ack_cfg_private.h : source and config files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VCAN_TXA_LOG_PDU_UNK                     (0xffffU)                    /* bsw_vcan_tx_transmit_lib.c 40:                      */
                                                                              /* #define BSW_VCAN_INVALID_PDU_ID         (0xFFFFU)   */
#define VCAN_TXA_NBYTE                           (4U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VCAN_TXA_LP_HTH_BIT_BGN                  (0x0000ffffU)
#define VCAN_TXA_LP_HTH_LSB_END                  (16U)
#define VCAN_TXA_LP_HTH_FIN                      (0x0001ffffU)
#define VCAN_TXA_LP_HTH_MAX                      (0x0000ffffU)
#define VCAN_TXA_LP_HTH_MIN                      (0x00000000U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u1_VCAN_TXA_RSP_WAI(u1_mbox)             ((u1_mbox) >> 5U)                              /* Word Array Index */
#define u4_VCAN_TXA_RSP_BIT(u1_mbox)             ((U4)0x00000001U << ((u1_mbox) & (U1)0x1fU))   

#define u1_VCAN_TXA_CTRLR(u1_ctrlr)              ((u1_ctrlr) & ((U1)0xffU ^ (U1)VCAN_VIRTUAL_CH))

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_vCANTxAckConfirmbyHth(const ST_VCAN_TXA_HTH * st_ap_HTH, const U4 u4_a_ACK, const U4 u4_a_LP_HTH);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_vCANTxAckInit(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_vCANTxAckInit(void)
{
    U4                            u4_t_lpcnt;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_VCAN_TXA_NUM_CCH; u4_t_lpcnt++){
        (void)ehvm_vcc_clear_channel(st_gp_VCAN_TXA_CCH[u4_t_lpcnt].u4_vcc_rx);
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_vCANTxAckPreHigh(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_vCANTxAckPreHigh(void)
{
    const ST_VCAN_TXA_CCH *       st_tp_CCH;
    const ST_VCAN_TXA_HTH *       st_tp_HTH;

    U4                            u4_t_cch;
    U4                            u4_t_vcc_rx;
    U4                            u4_t_lpmax;
    U4                            u4_t_lprx;
    U4                            u4_t_lphth;
    U4                            u4_t_ack;
    U4                            u4_t_nbyte;

    U1                            u1_t_vcc_ok;

    for(u4_t_cch = (U4)0U; u4_t_cch < (U4)u1_g_VCAN_TXA_NUM_CCH; u4_t_cch++){

        st_tp_CCH   = &st_gp_VCAN_TXA_CCH[u4_t_cch];

        st_tp_HTH   = st_tp_CCH->stp_HTH;
        u4_t_vcc_rx = st_tp_CCH->u4_vcc_rx;
        u4_t_lpmax  = (U4)st_tp_CCH->u2_lpmax;

        u4_t_lphth  = (U4)st_tp_CCH->u2_num_hth << VCAN_TXA_LP_HTH_LSB_END;
        for(u4_t_lprx = (U4)0U; u4_t_lprx < u4_t_lpmax; u4_t_lprx++){

            /* #define E_EHVM_OK                        ((ehvm_std_return_t)0x00U) */
            /* #define E_EHVM_NOT_OK                    ((ehvm_std_return_t)0x01U) */
            /* #define E_EHVM_RECEIVE_QUEUE_EMPTY       ((ehvm_std_return_t)0x03U) */
            /* #define E_EHVM_RECEIVE_OVERWRITE_OCCURS  ((ehvm_std_return_t)0x04U) */
            /* #define E_EHVM_HVC_ACC_DENY              ((ehvm_std_return_t)0x10U) */
            /* #define E_EHVM_MM_ACC_NG                 ((ehvm_std_return_t)0x20U) */
            u1_t_vcc_ok = ehvm_vcc_receive(u4_t_vcc_rx, &u4_t_ack, (U4)VCAN_TXA_NBYTE, &u4_t_nbyte);
            if(u1_t_vcc_ok == E_EHVM_RECEIVE_OVERWRITE_OCCURS){
                /* do nothing */
            }
            else if(u1_t_vcc_ok != E_EHVM_OK){ 
                break;
            }
            else if(u4_t_lphth != (U4)VCAN_TXA_LP_HTH_FIN){
                u4_t_lphth = u4_s_vCANTxAckConfirmbyHth(st_tp_HTH, u4_t_ack, u4_t_lphth);
            }
            else{
                /* do nothing */
            }
        }
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_vCANTxAckRxInd(const uint8 u1_a_CTRLR, const uint8 u1_a_MBOX, const CanMsgType * st_ap_CAN_RX)                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_vCANTxAckRxInd(const uint8 u1_a_CTRLR, const uint8 u1_a_MBOX, const CanMsgType * st_ap_CAN_RX)
{
    const U4 *                    u4_tp_RSP;
    U4                            u4_t_bit;
    U4                            u4_t_ack;
    U1                            u1_t_ctrlr;
    U1                            u1_t_wai;

    u1_t_ctrlr = u1_VCAN_TXA_CTRLR(u1_a_CTRLR);
    if((u1_t_ctrlr < u1_g_VCAN_TXA_NUM_CTRLR                 ) &&
       (u1_a_MBOX  < u1_gp_VCAN_TXA_NRMB_BY_CTRLR[u1_a_CTRLR])){

        u4_tp_RSP  = u4p_gp_VCAN_TXA_RSP_BY_RX[u1_t_ctrlr];
        u1_t_wai   = u1_VCAN_TXA_RSP_WAI(u1_a_MBOX); 
        u4_t_bit   = u4_VCAN_TXA_RSP_BIT(u1_a_MBOX);
        u4_t_bit  &= u4_tp_RSP[u1_t_wai];
        if(u4_t_bit != (U4)0U){
            u4_t_ack = st_ap_CAN_RX->u4Id;
            (void)ehvm_vcc_transmit(u4_g_VCAN_TXA_VCC_RSP_TX, &u4_t_ack, (U4)VCAN_TXA_NBYTE);
        }
    }
}
/*===================================================================================================================================*/
/*  static U4      u4_s_vCANTxAckConfirmbyHth(const ST_VCAN_TXA_HTH * st_ap_HTH, const U4 u4_a_ACK, const U4 u4_a_LP_HTH)            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_vCANTxAckConfirmbyHth(const ST_VCAN_TXA_HTH * st_ap_HTH, const U4 u4_a_ACK, const U4 u4_a_LP_HTH)
{
    U2 *             u2_tp_log_tx;

    U4               u4_t_begin;
    U4               u4_t_end;
    U4               u4_t_min;
    U4               u4_t_max;

    U4               u4_t_cid;
    U4               u4_t_ack;
    U4               u4_t_lphth;

    U2               u2_t_pdu_id;

    u4_t_begin = u4_a_LP_HTH & (U4)VCAN_TXA_LP_HTH_BIT_BGN;
    u4_t_end   = u4_a_LP_HTH >> (U4)VCAN_TXA_LP_HTH_LSB_END;

    u4_t_min   = (U4)VCAN_TXA_LP_HTH_MAX;
    u4_t_max   = (U4)VCAN_TXA_LP_HTH_MIN;
    while(u4_t_begin < u4_t_end){

        u2_tp_log_tx = st_ap_HTH[u4_t_begin].u2p_log_tx;
        u2_t_pdu_id  = (*u2_tp_log_tx);
        if(u2_t_pdu_id != (U2)VCAN_TXA_LOG_PDU_UNK){

            u4_t_cid = st_ap_HTH[u4_t_begin].u4_cid;
            u4_t_ack = u4_a_ACK & st_ap_HTH[u4_t_begin].u4_mask;
            if(u4_t_cid == u4_t_ack){
                (*u2_tp_log_tx) = (U2)VCAN_TXA_LOG_PDU_UNK;
                CanIf_TxConfirmation(u2_t_pdu_id);
            }
            else{

                if(u4_t_begin < u4_t_min){
                    u4_t_min = u4_t_begin;
                }
                if(u4_t_begin > u4_t_max){
                    u4_t_max = u4_t_begin;
                }
            }
        }
        u4_t_begin++;
    }
    u4_t_lphth = ((u4_t_max + (U4)1U) << VCAN_TXA_LP_HTH_LSB_END) | u4_t_min;

    return(u4_t_lphth);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     4/14/2025  TN       New.                                                                                               */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
