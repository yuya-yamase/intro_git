/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  CAN L-PDU Router SecOC Tx/Rx                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define CAN_LPR_SECOC_TRX_C_MAJOR                (1)
#define CAN_LPR_SECOC_TRX_C_MINOR                (0)
#define CAN_LPR_SECOC_TRX_C_PATCH                (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "can_lpr_cfg_private.h"
#include "can_lpr_secoc_trx_cfg_private.h"
#include "SecOC.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((CAN_LPR_SECOC_TRX_C_MAJOR != CAN_LPR_H_MAJOR) || \
     (CAN_LPR_SECOC_TRX_C_MINOR != CAN_LPR_H_MINOR) || \
     (CAN_LPR_SECOC_TRX_C_PATCH != CAN_LPR_H_PATCH))
#error "can_lpr_secoc_trx.c and can_lpr.h : source and header files are inconsistent!"
#endif

#if ((CAN_LPR_SECOC_TRX_C_MAJOR != CAN_LPR_CFG_H_MAJOR) || \
     (CAN_LPR_SECOC_TRX_C_MINOR != CAN_LPR_CFG_H_MINOR) || \
     (CAN_LPR_SECOC_TRX_C_PATCH != CAN_LPR_CFG_H_PATCH))
#error "can_lpr_secoc_trx.c and can_lpr_cfg_private.h : source and config files are inconsistent!"
#endif

#if ((CAN_LPR_SECOC_TRX_C_MAJOR != CAN_LPR_SECOC_TRX_CFG_H_MAJOR) || \
     (CAN_LPR_SECOC_TRX_C_MINOR != CAN_LPR_SECOC_TRX_CFG_H_MINOR) || \
     (CAN_LPR_SECOC_TRX_C_PATCH != CAN_LPR_SECOC_TRX_CFG_H_PATCH))
#error "can_lpr_secoc_trx.c and can_lpr_secoc_trx_cfg_private.h : source and config files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((CAN_LPR_RR_EN_SECOC_TX == 1U) || \
     (CAN_LPR_RR_EN_SECOC_TX == 2U) || \
     (CAN_LPR_RR_EN_SECOC_RX == 1U) || \
     (CAN_LPR_RR_EN_SECOC_RX == 2U))
#else
#error "can_lpr_secoc_trx.c : CAN_LPR_RR_EN_SECOC_TX shall be euqal to 1U or 2U, or CAN_LPR_RR_EN_SECOC_RX shall be euqal to 1U."
#endif /* #if ((CAN_LPR_RR_SECOC_EN == 1U) || \ */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  uint8   u1_g_CANLpRIngSecOCTRx(const PduIdType u2_a_RK, const PduInfoType * st_ap_RPDU_TRX, const uint8 u1_a_ING_SECOC_TRX)      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
uint8   u1_g_CANLpRIngSecOCTRx(const PduIdType u2_a_RK, const PduInfoType * st_ap_RPDU_TRX, const uint8 u1_a_ING_SECOC_TRX)
{
    const ST_CAN_LPR_ING *               st_tp_ING;
    const ST_CAN_LPR_RR *                st_tp_RR;
    CanMsgType                           st_t_can;
    U2                                   u2_t_num_rr;

    if(u1_a_ING_SECOC_TRX < u1_g_CAN_LPR_NUM_ING){

        st_tp_ING = stp_gp_CAN_LPR_ING[u1_a_ING_SECOC_TRX];
        if(st_tp_ING != NULL_PTR){

            u2_t_num_rr = st_tp_ING->u2_num_rr;
            if(u2_a_RK < u2_t_num_rr){  /* u2_a_RK : Routing Key  */

                st_tp_RR          = st_tp_ING->stp_RR;
                st_tp_RR          = &st_tp_RR[u2_a_RK];

                st_t_can.ptData   = st_ap_RPDU_TRX->SduDataPtr;
                st_t_can.u4Id     = st_tp_RR->u4_cid_min;
                st_t_can.u1Length = st_ap_RPDU_TRX->SduLength;

                vd_g_CANLpREgrbyRule(st_tp_ING, st_tp_RR, &st_t_can);
            }
        }
    }

    return((uint8)E_OK);
}
/*===================================================================================================================================*/

#if ((CAN_LPR_RR_EN_SECOC_TX == 2U) || (CAN_LPR_RR_EN_SECOC_RX == 2U))

#if ((CAN_LPR_RR_EN_SECOC_TX == 2U) && (CAN_LPR_RR_EN_IPDU_TX != 1U))
#warning "can_lpr_secoc_trx.c : CAN_LPR_RR_EN_IPDU_TX should be equal to 1U if CAN_LPR_RR_EN_SECOC_TX is equal to 2U."
#endif /* #if ((CAN_LPR_RR_EN_SECOC_TX == 2U) && (CAN_LPR_RR_EN_IPDU_TX != 1U)) */

/*===================================================================================================================================*/
/*  void    vd_g_CANLpRSecOCTRxPosHigh(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_CANLpRSecOCTRxPosHigh(void)
{
    PduInfoType                          st_t_pduinfo;

    U4                                   u4_tp_can[CAN_LPFQ_PDU_NW_MAX];
    U4                                   u4_t_lpcnt;
    U4                                   u4_t_head;
    U4                                   u4_t_nb_sdu;
    U2                                   u2_t_num_pdu;
    U2                                   u2_t_pdu_auth;
    U1                                   u1_t_eas_chk;

#if (CAN_LPR_RR_EN_SECOC_TX == 2U)
    u2_t_num_pdu = SecOC_TxPduProcessingMax;
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_CAN_LPR_SECOC_TX_LP_LM; u4_t_lpcnt++){

        u1_t_eas_chk = u1_g_CANLpFqDeqCh(u2_g_CAN_LPR_SECOC_TX_FQ_CH, &u4_tp_can[0U], (U2)CAN_LPFQ_PDU_NW_MAX);
        if(u1_t_eas_chk == (U1)CAN_LPFQ_EAS_REQ_ACPT){

            u4_t_head     = u4_tp_can[CAN_LPFQ_WO_HEAD];
            u4_t_nb_sdu   = u4_t_head & (U4)CAN_LPFQ_HD_BIT_NB_SDU;
            u2_t_pdu_auth = (U2)(u4_t_head >> CAN_LPFQ_HD_LSB_PDU_ID);
            if((u2_t_pdu_auth < u2_t_num_pdu               ) &&
               (u4_t_nb_sdu   > (U4)CAN_LPR_SECOC_TX_NB_MIN)){

                st_t_pduinfo.SduDataPtr  = (U1 *)&u4_tp_can[CAN_LPFQ_WO_SDU_B0];
                st_t_pduinfo.MetaDataPtr = NULL_PTR;
                st_t_pduinfo.SduLength   = u4_t_nb_sdu - (U4)CAN_LPR_SECOC_TX_NB_MIN;

#if (CAN_LPR_CFG_DET == 1U)
                u1_t_eas_chk = SecOC_IfTransmit(u2_t_pdu_auth, &st_t_pduinfo);
                if(u1_t_eas_chk != (U1)E_OK){
                    vd_g_CANLpRCfgDet((U1)CAN_LPR_DET_SECOC_TX, u1_t_eas_chk, u4_tp_can[CAN_LPFQ_WO_CAN_ID]);
                } 
#else
                (void)SecOC_IfTransmit(u2_t_pdu_auth, &st_t_pduinfo);
#endif /* #if (CAN_LPR_CFG_DET == 1U) */
            }
        }
        else{
            break;
        }
    }
#endif /* #if (CAN_LPR_RR_EN_SECOC_TX == 2U) */

#if (CAN_LPR_RR_EN_SECOC_RX == 2U)
    u2_t_num_pdu = SecOC_RxPduProcessingMax;
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_CAN_LPR_SECOC_RX_LP_LM; u4_t_lpcnt++){

        u1_t_eas_chk = u1_g_CANLpFqDeqCh(u2_g_CAN_LPR_SECOC_RX_FQ_CH, &u4_tp_can[0U], (U2)CAN_LPFQ_PDU_NW_MAX);
        if(u1_t_eas_chk == (U1)CAN_LPFQ_EAS_REQ_ACPT){

            u4_t_head     = u4_tp_can[CAN_LPFQ_WO_HEAD];
            u4_t_nb_sdu   = u4_t_head & (U4)CAN_LPFQ_HD_BIT_NB_SDU;
            u2_t_pdu_auth = (U2)(u4_t_head >> CAN_LPFQ_HD_LSB_PDU_ID);
            if(u2_t_pdu_auth < u2_t_num_pdu){

                st_t_pduinfo.SduDataPtr  = (U1 *)&u4_tp_can[CAN_LPFQ_WO_SDU_B0];
                st_t_pduinfo.MetaDataPtr = NULL_PTR;
                st_t_pduinfo.SduLength   = u4_t_nb_sdu;

                SecOC_RxIndication(u2_t_pdu_auth, &st_t_pduinfo);
            }
        }
        else{
            break;
        }
    }
#endif /* #if (CAN_LPR_RR_EN_SECOC_RX == 2U) */
}
#endif /* #if ((CAN_LPR_RR_EN_SECOC_TX == 2U) || (CAN_LPR_RR_EN_SECOC_RX == 2U)) */
/*===================================================================================================================================*/

#if ((CAN_LPR_RR_EN_SECOC_TX == 1U) || (CAN_LPR_RR_EN_SECOC_TX == 2U))

/*===================================================================================================================================*/
/*  void    vd_g_CANLpREgrSecOCTx(const U2 u2_a_EPDU_ID, const CanMsgType * const st_ap_ECAN)                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_CANLpREgrSecOCTx(const U2 u2_a_EPDU_ID, const CanMsgType * const st_ap_ECAN)
{
    /* ----------------------------------------------------------------------------------------------------- */
    /* Attention :                                                                                           */
    /* ----------------------------------------------------------------------------------------------------- */
    /* Since u2_a_EPDU_ID is a const, it's unnecessary to test whether it's within a the range.              */
    /* ----------------------------------------------------------------------------------------------------- */

    /* ./inc/SecOC.h 62:                                               */
    /* FUNC(Std_ReturnType, SECOC_CODE) SecOC_IfTransmit               */
    /* (                                                               */
    /*     PduIdType TxPduId,                                          */
    /*     P2CONST(PduInfoType, AUTOMATIC, SECOC_APPL_DATA) PduInfoPtr */
    /* );                                                              */
    /* #define E_OK       ( 0x00U )                                    */
    /* #define E_NOT_OK   ( 0x01U )                                    */
#if (CAN_LPR_CFG_DET == 1U)
    PduInfoType                          st_t_pduinfo;
    U4                                   u4_t_nbyte;
    U1                                   u1_t_eas_chk;

    u4_t_nbyte = (U4)st_ap_ECAN->u1Length;
    if(u4_t_nbyte > (U4)CAN_LPR_SECOC_TX_NB_MIN){

        st_t_pduinfo.SduDataPtr  = st_ap_ECAN->ptData;
        st_t_pduinfo.MetaDataPtr = NULL_PTR;
        st_t_pduinfo.SduLength   = u4_t_nbyte - (U4)CAN_LPR_SECOC_TX_NB_MIN;

        u1_t_eas_chk = SecOC_IfTransmit(u2_a_EPDU_ID, &st_t_pduinfo);
        if(u1_t_eas_chk != (U1)E_OK){
            vd_g_CANLpRCfgDet((U1)CAN_LPR_DET_SECOC_TX, u1_t_eas_chk, st_ap_ECAN->u4Id);
        }
    }
#else
    PduInfoType                          st_t_pduinfo;
    U4                                   u4_t_nbyte;

    u4_t_nbyte = (U4)st_ap_ECAN->u1Length;
    if(u4_t_nbyte > (U4)CAN_LPR_SECOC_TX_NB_MIN){

        st_t_pduinfo.SduDataPtr  = st_ap_ECAN->ptData;
        st_t_pduinfo.MetaDataPtr = NULL_PTR;
        st_t_pduinfo.SduLength   = u4_t_nbyte - (U4)CAN_LPR_SECOC_TX_NB_MIN;

        (void)SecOC_IfTransmit(u2_a_EPDU_ID, &st_t_pduinfo);
    }
#endif /* #if (CAN_LPR_CFG_DET == 1U) */
}
#endif /* #if ((CAN_LPR_RR_EN_SECOC_TX == 1U) || (CAN_LPR_RR_EN_SECOC_TX == 2U)) */
/*===================================================================================================================================*/

#if ((CAN_LPR_RR_EN_SECOC_RX == 1U) || (CAN_LPR_RR_EN_SECOC_RX == 2U))

/*===================================================================================================================================*/
/*  void    vd_g_CANLpREgrSecOCRx(const U2 u2_a_EPDU_ID, const CanMsgType * const st_ap_ECAN)                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_CANLpREgrSecOCRx(const U2 u2_a_EPDU_ID, const CanMsgType * const st_ap_ECAN)
{
    /* ----------------------------------------------------------------------------------------------------- */
    /* Attention :                                                                                           */
    /* ----------------------------------------------------------------------------------------------------- */
    /* Since u2_a_EPDU_ID is a const, it's unnecessary to test whether it's within a the range.              */
    /* ----------------------------------------------------------------------------------------------------- */

    /* ./inc/SecOC.h 102:                                              */
    /* FUNC(void, SECOC_CODE) SecOC_RxIndication                       */
    /* (                                                               */
    /*     PduIdType RxPduId,                                          */
    /*     P2CONST(PduInfoType, AUTOMATIC, SECOC_APPL_DATA) PduInfoPtr */
    /* );                                                              */
    PduInfoType                          st_t_pduinfo;

    st_t_pduinfo.SduDataPtr  = st_ap_ECAN->ptData;
    st_t_pduinfo.MetaDataPtr = NULL_PTR;
    st_t_pduinfo.SduLength   = st_ap_ECAN->u1Length;

    SecOC_RxIndication(u2_a_EPDU_ID, &st_t_pduinfo);
}
#endif /* #if ((CAN_LPR_RR_EN_SECOC_RX == 1U) || (CAN_LPR_RR_EN_SECOC_RX == 2U)) */
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
