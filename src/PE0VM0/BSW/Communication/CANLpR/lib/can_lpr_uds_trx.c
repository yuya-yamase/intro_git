/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  CAN L-PDU Router Universal Diagnostic Service CAN/CAN-FD Frame Tx/Rx                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define CAN_LPR_UDS_TRX_C_MAJOR                  (1)
#define CAN_LPR_UDS_TRX_C_MINOR                  (0)
#define CAN_LPR_UDS_TRX_C_PATCH                  (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "can_lpr_cfg_private.h"
#include "can_lpr_uds_trx_cfg_private.h"

#include "CanIf.h"
#include "CanIf_Cbk.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((CAN_LPR_UDS_TRX_C_MAJOR != CAN_LPR_CFG_H_MAJOR) || \
     (CAN_LPR_UDS_TRX_C_MINOR != CAN_LPR_CFG_H_MINOR) || \
     (CAN_LPR_UDS_TRX_C_PATCH != CAN_LPR_CFG_H_PATCH))
#error "can_lpr_uds_tx.c and can_lpr_cfg_private.h : source and config files are inconsistent!"
#endif

#if ((CAN_LPR_UDS_TRX_C_MAJOR != CAN_LPR_UDS_TRX_CFG_H_MAJOR) || \
     (CAN_LPR_UDS_TRX_C_MINOR != CAN_LPR_UDS_TRX_CFG_H_MINOR) || \
     (CAN_LPR_UDS_TRX_C_PATCH != CAN_LPR_UDS_TRX_CFG_H_PATCH))
#error "can_lpr_uds_tx.c and can_lpr_uds_tx_cfg_private.h : source and config files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define CAN_LPR_UDS_MIN_0_F0                     (0x000000f0U)
#define CAN_LPR_UDS_MIN_1_EF                     (0x000000efU)
#define CAN_LPR_UDS_MIN_2_E0                     (0x000000e0U)

#define CAN_LPR_UDS_TYPE_REQ_LT_DF               (0U)
#define CAN_LPR_UDS_TYPE_ANS_GE_E0               (1U)
#define CAN_LPR_UDS_TYPE_REQ_EQ_EF               (2U)
#define CAN_LPR_UDS_TYPE_ANS_GT_F0               (3U)
#define CAN_LPR_UDS_TYPE_LSB_DST                 (2U)

#define CAN_LPR_UDS_TRX_LSB_DST                  (8U)
#define CAN_LPR_UDS_TRX_BIT_ADR                  (0x000000ffU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u4_CAN_LPR_UDS_TRX_WOF(addr)             (addr >> 5U)
#define u4_CAN_LPR_UDS_TRX_LSB(addr)             (addr & (U4)0x0000001fU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static inline U4      u4_s_CANLpRUdsTypechk(const U4 u4_a_ADR);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_CANLpREgrUdsTRx(const U2 u2_a_EPDU_ID, const CanMsgType * const st_ap_ECAN)                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_CANLpREgrUdsTRx(const U2 u2_a_EPDU_ID, const CanMsgType * const st_ap_ECAN)
{
    const ST_CAN_LPR_UDS_TRX *           st_tp_TRX;
    const U4 *                           u4_tp_TA_EN;
    const U4 *                           u4_tp_SO_EN;

    U4                                   u4_t_src;
    U4                                   u4_t_tar;
    U4                                   u4_t_type;
    U4                                   u4_t_regr_en;
    U4                                   u4_t_ifrx_en;

    U4                                   u4_t_wo_ta;
    U4                                   u4_t_lsb_ta;
    U4                                   u4_t_wo_so;
    U4                                   u4_t_lsb_so;

    if(u2_a_EPDU_ID < u2_g_CAN_LPR_NUM_UDS_TRX){

        st_tp_TRX     = &st_gp_CAN_LPR_UDS_TRX[u2_a_EPDU_ID];

        u4_t_src      = st_ap_ECAN->u4Id;
        u4_t_tar      = (u4_t_src >> CAN_LPR_UDS_TRX_LSB_DST) & (U4)CAN_LPR_UDS_TRX_BIT_ADR;
        u4_t_src      =  u4_t_src & (U4)CAN_LPR_UDS_TRX_BIT_ADR;
        u4_t_type     = u4_s_CANLpRUdsTypechk(u4_t_src);
        u4_t_type    |= (u4_s_CANLpRUdsTypechk(u4_t_tar) << CAN_LPR_UDS_TYPE_LSB_DST);
        u4_t_regr_en  = (st_tp_TRX->u4_type_en >> u4_t_type) & (U4)0x00000001U;
        u4_t_ifrx_en  = u4_t_regr_en;

        u4_t_wo_ta    = u4_CAN_LPR_UDS_TRX_WOF(u4_t_tar);
        u4_t_lsb_ta   = u4_CAN_LPR_UDS_TRX_LSB(u4_t_tar);
        u4_t_wo_so    = u4_CAN_LPR_UDS_TRX_WOF(u4_t_src);
        u4_t_lsb_so   = u4_CAN_LPR_UDS_TRX_LSB(u4_t_src);

        /* ---------------------------------------------------------- */
        u4_tp_TA_EN = st_tp_TRX->u4p_EGR_TA;
        if((u4_t_regr_en != (U4)0U  ) &&
           (u4_tp_TA_EN  != NULL_PTR)){

            u4_t_regr_en &= u4_tp_TA_EN[u4_t_wo_ta] >> u4_t_lsb_ta;
        }
        u4_tp_SO_EN = st_tp_TRX->u4p_EGR_SO;
        if((u4_t_regr_en != (U4)0U  ) &&
           (u4_tp_SO_EN  != NULL_PTR)){

            u4_t_regr_en &= u4_tp_SO_EN[u4_t_wo_so] >> u4_t_lsb_so;
        }
        if(u4_t_regr_en != (U4)0U){
            (*st_tp_TRX->fp_vd_EGR)(st_tp_TRX->u2_epdu_id, st_ap_ECAN);
        }
        /* ---------------------------------------------------------- */
        u4_tp_TA_EN = st_tp_TRX->u4p_REC_TA;
        u4_tp_SO_EN = st_tp_TRX->u4p_REC_SO;
        if((u4_t_ifrx_en != (U4)0U  ) &&
           (u4_tp_TA_EN  != NULL_PTR) &&
           (u4_tp_SO_EN  != NULL_PTR)){

            u4_t_ifrx_en &= u4_tp_TA_EN[u4_t_wo_ta] >> u4_t_lsb_ta;
            u4_t_ifrx_en &= u4_tp_SO_EN[u4_t_wo_so] >> u4_t_lsb_so;

            if(u4_t_ifrx_en != (U4)0U){
                CanIf_RxIndication(st_tp_TRX->u2_hrh, st_ap_ECAN->u4Id, st_ap_ECAN->u1Length, st_ap_ECAN->ptData);
            }
        }
    }
}
/*===================================================================================================================================*/
/*  static inline U4      u4_s_CANLpRUdsTypechk(const U4 u4_a_ADR)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline U4      u4_s_CANLpRUdsTypechk(const U4 u4_a_ADR)
{
    U4                                   u4_t_type;

    if(u4_a_ADR >= (U4)CAN_LPR_UDS_MIN_0_F0){
        u4_t_type = CAN_LPR_UDS_TYPE_ANS_GT_F0;
    }
    else if(u4_a_ADR >= (U4)CAN_LPR_UDS_MIN_1_EF){
        u4_t_type = CAN_LPR_UDS_TYPE_REQ_EQ_EF;
    }
    else if(u4_a_ADR >= (U4)CAN_LPR_UDS_MIN_2_E0){
        u4_t_type = CAN_LPR_UDS_TYPE_ANS_GE_E0;
    }
    else{
        u4_t_type = CAN_LPR_UDS_TYPE_REQ_LT_DF;
    }

    return(u4_t_type);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     5/ 9/2025  TN       New.                                                                                               */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
