/* bsw_cantp_rx_c_v3-0-0                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANTP/RX/CODE                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>

#include <bswm_cs/bsw_bswm_cs.h>
#include <comm/bsw_comm.h>
#include "../../ComM/inc/bsw_comm_config.h"
#include "../../BswM_CS/inc/bsw_bswm_cs_config.h"

#if( BSW_BSWM_CS_FUNC_CANTP == BSW_USE )
#include <cs/bsw_cs_system_memmap_pre.h>
#include <cantp/bsw_cantp.h>
#include <pdur/bsw_pdur.h>

#include "../cfg/CanTp_Cfg.h"
#include "../inc/bsw_cantp_cmn.h"

#include <pdur/bsw_pdur_cantp.h>

#include "../inc/bsw_cantp_config.h"

#include "../inc/bsw_cantp_st.h"
#include "../inc/bsw_cantp_rx.h"
#include "../inc/bsw_cantp_tx.h"
#include "../inc/bsw_cantp_snd.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define BSW_CANTP_RX_u1MIRRORVALIDATE       ((uint8)0xFFU)     /* RAM broken check pattern */
#define BSW_CANTP_RX_u2COUNTER_U1MAX        ((uint16)0x00FFU)  /* Counter MAX Value        */

/* Mediation result */
#define BSW_CANTP_RX_u1ACCEPT_NEW_SDU       ((uint8)0U)
#define BSW_CANTP_RX_u1REJECT_NEW_SDU       ((uint8)1U)

/* SendFCCtrl internal processing results */
#define BSW_CANTP_RX_u1SNDFCCTL_SND_FC      ((uint8)0U)     /* Send FC frame                                                  */
#define BSW_CANTP_RX_u1SNDFCCTL_CONT_WT     ((uint8)1U)     /* Continues waiting for upper layer's buffer to become available */
#define BSW_CANTP_RX_u1SNDFCCTL_TERM        ((uint8)2U)     /* Terminate reception                                            */
#define BSW_CANTP_RX_u1SNDFCCTL_ERROR       ((uint8)3U)     /* Error (RAM broken)                                             */

/* for XOR operation */
#define BSW_CANTP_RX_u2LOW8BIT_ON           ((uint16)0x00FFU)

#if( BSW_CANTP_CFG_FDSUPPORT == BSW_USE )
/* Expected SF_DL Value is Invalid  */
#define BSW_CANTP_RX_u1SFDL_EXP_INVALID     ((uint8) 0x00U)
#endif /* BSW_CANTP_CFG_FDSUPPORT == BSW_USE */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
static Bsw_CanTp_ReturnType     bsw_cantp_rx_VerifySF( BswConst Bsw_CanTp_RxNSduCfgType * ptRxNSduCfgTbl, BswConstR Bsw_CanTp_PduInfoType * ptTpPduInfo );
static Bsw_CanTp_ReturnType     bsw_cantp_rx_VerifyFF( BswConst Bsw_CanTp_RxNSduCfgType * ptRxNSduCfgTbl, BswConstR Bsw_CanTp_PduInfoType * ptTpPduInfo );
static Bsw_CanTp_ReturnType     bsw_cantp_rx_VerifyCF( BswConst Bsw_CanTp_RxNSduCfgType * ptRxNSduCfgTbl, BswConstR Bsw_CanTp_PduInfoType * ptTpPduInfo, Bsw_CanTp_st_ReceiverStatType * ptReceiverStatTbl );
static uint8                    bsw_cantp_rx_MedInSender( BswConst Bsw_CanTp_CfgType * ptCfgTbl, BswConst Bsw_CanTp_RxNSduCfgType * ptNewRxNSduCfgTbl );
static uint8                    bsw_cantp_rx_MedInReceiver( BswConst Bsw_CanTp_CfgType * ptCfgTbl, BswConst Bsw_CanTp_RxNSduCfgType * ptNewRxNSduCfgTbl );
static void                     bsw_cantp_rx_ReceiveSF( BswConst Bsw_CanTp_RxNSduCfgType * ptRxNSduCfgTbl, BswConstR Bsw_CanTp_PduInfoType * ptTpPduInfo );
static void                     bsw_cantp_rx_ReceiveFF( BswConst Bsw_CanTp_RxNSduCfgType * ptRxNSduCfgTbl, BswConstR Bsw_CanTp_PduInfoType * ptTpPduInfo, Bsw_CanTp_st_ReceiverStatType * ptReceiverStatTbl );
static void                     bsw_cantp_rx_ReceiveCF( BswConst Bsw_CanTp_CfgType * ptCfgTbl, BswConst Bsw_CanTp_RxNSduCfgType * ptRxNSduCfgTbl, BswConstR Bsw_CanTp_PduInfoType * ptTpPduInfo, Bsw_CanTp_st_ReceiverStatType * ptReceiverStatTbl );
static Bsw_CanTp_st_FSType      bsw_cantp_rx_JudgeFS( uint32 u4RemainNSduLen, uint32 u4UpperLayerBufSize, uint8 u1MaxCFNDataLen, uint8 u1BS );
static uint16                   bsw_cantp_rx_GetBlockNDataSize( uint8 u1CFNDataLen, uint8 u1BS );
static void                     bsw_cantp_rx_SendFCCtrl( BswConst Bsw_CanTp_CfgType * ptCfgTbl, BswConst Bsw_CanTp_RxNSduCfgType * ptRxNSduCfgTbl, Bsw_CanTp_st_ReceiverStatType * ptReceiverStatTbl );
static Bsw_CanTp_ReturnType     bsw_cantp_rx_SendFC( BswConst Bsw_CanTp_RxNSduCfgType * ptRxNSduCfgTbl, Bsw_CanTp_st_FSType u1FS, uint8 u1BS, uint8 u1STmin );
static void                     bsw_cantp_rx_TimeoutNAr( BswConst Bsw_CanTp_RxNSduCfgType * ptRxNSduCfgTbl, Bsw_CanTp_st_ReceiverStatType * ptReceiverStatTbl );
static void                     bsw_cantp_rx_TimeoutNCr( BswConst Bsw_CanTp_RxNSduCfgType * ptRxNSduCfgTbl, Bsw_CanTp_st_ReceiverStatType * ptReceiverStatTbl );
static void                     bsw_cantp_rx_TerminateRx( BswConst Bsw_CanTp_RxNSduCfgType * ptRxNSduCfgTbl, Bsw_CanTp_st_ReceiverStatType * ptReceiverStatTbl, Std_ReturnType u1Ret );
static void                     bsw_cantp_rx_ReceiverToIdle( Bsw_CanTp_st_ReceiverStatType * ptReceiverStatTbl );


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | bsw_cantp_rx_CancelReceiveCore                           */
/* Description   | Receive Cancel Request core procedure                    */
/* Preconditions | None                                                     */
/* Parameters    | ptCfgTbl       : Pointer to CanTp configuration          */
/*               | u2NSduId       : Target Rx NSdu-Id                       */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK          : Accept cancel request                   */
/*               |  E_NOT_OK      : Reject cancel request                   */
/* Notes         | When CanTp_RxIndication interferes with this API,        */
/*               | it may cancel a new reception unintentionally            */
/*               | Thus, CanTp limits a use case of this API to following   */
/*               | pattern to prevent such a situation.                     */
/*               | - This API is callable within PduR_CanTpStartOfReception.*/
/****************************************************************************/
Std_ReturnType
bsw_cantp_rx_CancelReceiveCore( BswConst Bsw_CanTp_CfgType * ptCfgTbl, uint16 u2NSduId )
{
    BswConst Bsw_CanTp_RxNSduCfgType *  pt_RxNSduCfgTbl;       /* Pointer to RxNSdu configuration */
    Bsw_CanTp_st_ReceiverStatType    *  pt_ReceiverStatTbl;    /* Pointer to receiver status info */
    uint8                               u1_MaxCFNDataLen;      /* Maximum N_DATA Length in CF     */
    uint8                               u1_ChId;               /* Channel ID                      */
    uint8                               u1_PciOffset;          /* Offset to N_PCI address         */
    uint8                               u1_AddressFormat;      /* Address Format                  */
    Std_ReturnType                      u1_Ret;                /* Return value                    */
    uint16                              u2_CanIf_PduId;        /* CanIf PduId                     */

    u1_Ret = (Std_ReturnType)E_NOT_OK;

    pt_RxNSduCfgTbl    = bsw_cantp_cmn_GetRxNSduCfgTbl( ptCfgTbl, u2NSduId );
    u1_ChId            = pt_RxNSduCfgTbl->u1ParentChId;
    pt_ReceiverStatTbl = &(bsw_cantp_st_stChStatTbl[u1_ChId].stReceiverStatTbl);

    /* NSduId Check */
    if( u2NSduId == pt_ReceiverStatTbl->u2ReceiverNSduId )
    {
        switch( pt_ReceiverStatTbl->u1ReceiverStat )
        {
            case BSW_CANTP_ST_u1STS_FC_WAIT:

                bsw_cantp_rx_TerminateRx( pt_RxNSduCfgTbl, pt_ReceiverStatTbl, (Std_ReturnType)E_NOT_OK );
                u1_Ret = (Std_ReturnType)E_OK;
                break;

            case BSW_CANTP_ST_u1STS_FC_TX:

                u2_CanIf_PduId = pt_RxNSduCfgTbl->u2CanIf_FcPduId;
                /* CancelReceive request is acceptable */
                bsw_cantp_snd_AbortSend( u2_CanIf_PduId );
                bsw_cantp_rx_TerminateRx( pt_RxNSduCfgTbl, pt_ReceiverStatTbl, (Std_ReturnType)E_NOT_OK );
                u1_Ret = (Std_ReturnType)E_OK;
                break;

            case BSW_CANTP_ST_u1STS_CF_RX:
                /* Under CF reception wait */

                /* LAST CF check */
                u1_AddressFormat = pt_RxNSduCfgTbl->u1AddressFormat;
                u1_PciOffset     = bsw_cantp_cmn_u1PciOffSetTbl[u1_AddressFormat];
#if( BSW_CANTP_CFG_FDSUPPORT == BSW_USE )
                u1_MaxCFNDataLen = pt_ReceiverStatTbl->u1ReceiverRXDL - ( u1_PciOffset + BSW_CANTP_u1PCI_SIZE_CF );
#else /* BSW_CANTP_CFG_FDSUPPORT == BSW_NOUSE */
                u1_MaxCFNDataLen = BSW_CANTP_u1CAN_DL_08 - ( u1_PciOffset + BSW_CANTP_u1PCI_SIZE_CF );
#endif /* BSW_CANTP_CFG_FDSUPPORT */
                if( pt_ReceiverStatTbl->u4ReceiverRemainNSduLen > (uint32)u1_MaxCFNDataLen )
                {   /* mid CF (it is not the last CF) */

                    /* CancelReceive request is acceptable */
                    bsw_cantp_rx_TerminateRx( pt_RxNSduCfgTbl, pt_ReceiverStatTbl, (Std_ReturnType)E_NOT_OK );
                    u1_Ret = (Std_ReturnType)E_OK;
                }
                break;

            default:
                /* u1ReceiverStat or u2ReceiverNSduId is broken */
                bsw_cantp_cmn_u1ErrState = BSW_CANTP_u1RAMERR;
                bsw_cantp_rx_ReceiverToIdle( pt_ReceiverStatTbl );
                break;
        }
    }

    return u1_Ret;
}


/****************************************************************************/
/* Function Name | bsw_cantp_rx_MainFunction_Rx                             */
/* Description   | Periodical handling of receiver unit                     */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_cantp_rx_MainFunction_Rx( void )
{
    BswConst Bsw_CanTp_CfgType       *  pt_CfgTbl;                  /* Pointer to CanTp configuration    */
    BswConst Bsw_CanTp_RxNSduCfgType *  pt_RxNSduCfgTbl;            /* Pointer to RxNSdu configuration   */
    Bsw_CanTp_st_ReceiverStatType    *  pt_ReceiverStatTbl;         /* Pointer to receiver status info   */
    uint16                              u2_ReceiverNSduId;          /* Receiver Processing NSdu-Id       */
    uint16                              u2_ReceiverCycle;           /* MainFunction cycle count          */
    Bsw_CanTp_st_ProcStatType           u1_ReceiverStat;            /* Receiver processing status        */
    uint8                               u1_ChId;                    /* Channel ID                        */
    uint8                               u1_ChNum;                   /* Number of channels                */
    uint8                               u1_ReceiverAcceptedReqCnt;  /* Number of accepted request frames */

    pt_CfgTbl = bsw_cantp_cmn_GetConfigTbl();
    if( pt_CfgTbl != NULL_PTR )
    {
        u1_ChNum = pt_CfgTbl->u1ChNum;
        for( u1_ChId = (uint8)0U; u1_ChId < u1_ChNum; u1_ChId++ )
        {
            pt_ReceiverStatTbl = &(bsw_cantp_st_stChStatTbl[u1_ChId].stReceiverStatTbl);

            /********************************************/
            /*******  Start of exclusive section  *******/

            /* Snap shot of receiver status info */
            u2_ReceiverNSduId         = pt_ReceiverStatTbl->u2ReceiverNSduId;
            u2_ReceiverCycle          = pt_ReceiverStatTbl->u2ReceiverCycle;
            u1_ReceiverStat           = pt_ReceiverStatTbl->u1ReceiverStat;
            u1_ReceiverAcceptedReqCnt = pt_ReceiverStatTbl->u1ReceiverAcceptedReqCnt;

            /*******   End of exclusive section   *******/
            /********************************************/

            switch( u1_ReceiverStat )
            {
                case BSW_CANTP_ST_u1STS_IDLE:
                    /* NOP */
                    break;

                case BSW_CANTP_ST_u1STS_FC_WAIT:   /* FALLTHROUGH */
                case BSW_CANTP_ST_u1STS_FC_TX:     /* FALLTHROUGH */
                case BSW_CANTP_ST_u1STS_CF_RX:

                    pt_RxNSduCfgTbl = bsw_cantp_cmn_GetRxNSduCfgTbl( pt_CfgTbl, u2_ReceiverNSduId );
                    if( pt_RxNSduCfgTbl == NULL_PTR )
                    {   /* u2_ReceiverNSduId is broken */
                        bsw_cantp_cmn_u1ErrState = BSW_CANTP_u1RAMERR;

                        /********************************************/
                        /*******  Start of exclusive section  *******/

                        if( pt_ReceiverStatTbl->u1ReceiverAcceptedReqCnt == u1_ReceiverAcceptedReqCnt )
                        {
                            bsw_cantp_rx_ReceiverToIdle( pt_ReceiverStatTbl );
                        }

                        /*******   End of exclusive section   *******/
                        /********************************************/

                        u1_ReceiverStat = BSW_CANTP_ST_u1STS_IDLE;
                    }
                    break;

                default:
                    /* u1_ReceiverStat is broken */
                    bsw_cantp_cmn_u1ErrState = BSW_CANTP_u1RAMERR;

                    /********************************************/
                    /*******  Start of exclusive section  *******/

                    if( pt_ReceiverStatTbl->u1ReceiverAcceptedReqCnt == u1_ReceiverAcceptedReqCnt )
                    {
                        bsw_cantp_rx_ReceiverToIdle( pt_ReceiverStatTbl );
                    }

                    /*******   End of exclusive section   *******/
                    /********************************************/

                    u1_ReceiverStat = BSW_CANTP_ST_u1STS_IDLE;
                    break;
            }


            if( u1_ReceiverStat == BSW_CANTP_ST_u1STS_IDLE )
            {
                /* NOP */
            }
            else if( u1_ReceiverStat == BSW_CANTP_ST_u1STS_FC_WAIT )
            {   /* FC transmission control */
                bsw_cantp_rx_SendFCCtrl( pt_CfgTbl, pt_RxNSduCfgTbl, pt_ReceiverStatTbl );
            }
            else if( u1_ReceiverStat == BSW_CANTP_ST_u1STS_FC_TX )
            {
                if( u2_ReceiverCycle == (uint16)0U )
                {   /* N_Ar timeout */
                    bsw_cantp_rx_TimeoutNAr( pt_RxNSduCfgTbl, pt_ReceiverStatTbl );
                }
            }
            else
            {   /* u1_ReceiverStat == BSW_CANTP_ST_u1STS_CF_RX */
                if( u2_ReceiverCycle == (uint16)0U )
                {   /* N_Cr timeout */
                    bsw_cantp_rx_TimeoutNCr( pt_RxNSduCfgTbl, pt_ReceiverStatTbl );
                }
            }
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | bsw_cantp_rx_RxIndSF                                     */
/* Description   | Receive indication procedure of SF N_PDU                 */
/* Preconditions | None                                                     */
/* Parameters    | ptCfgTbl       : Pointer to CanTp configuration          */
/*               | ptRxNSduCfgTbl : Pointer to RxNSdu configuration         */
/*               | ptTpPduInfo    : Pointer to PDU information              */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_cantp_rx_RxIndSF( BswConst Bsw_CanTp_CfgType * ptCfgTbl, BswConst Bsw_CanTp_RxNSduCfgType * ptRxNSduCfgTbl, BswConstR Bsw_CanTp_PduInfoType * ptTpPduInfo )
{
    BswConst Bsw_CanTp_ChCfgType *  pt_ChCfgTblTop; /* Pointer to ChCfgTbl              */
    BswConst Bsw_CanTp_ChCfgType *  pt_ChCfgTbl;    /* Pointer to channel configuration */
    uint16                          u2_RxNSduId;    /* Target Rx NSdu-Id                */
    uint16                          u2_RecvConter;  /* ReceiverAcceptedReqCnter         */
    Bsw_CanTp_st_ProcStatType       u1_SenderStat;  /* Sender processing status         */
    uint8                           u1_ChId;        /* Channel ID                       */
    Bsw_CanTp_ReturnType            u1_Result;      /* Check result                     */
    uint8                           u1_MediStat;    /* Mediation status                 */
    Std_ReturnType                  u1_SORRet;      /* Check SOR result                 */
    uint16                          u2_PduId;       /* CanIf PduId                      */
    uint32                          u4_Length;      /* Sdu Length                       */
    uint8                        *  pt_SduData;     /* Sdu Data                         */

    /* SF format check */
    u1_Result = bsw_cantp_rx_VerifySF( ptRxNSduCfgTbl, ptTpPduInfo );
    if( u1_Result == (Bsw_CanTp_ReturnType)BSW_CANTP_E_OK )
    {
        /* Pre-Check for StartOfReception */
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
        u2_RxNSduId = ptRxNSduCfgTbl->u2NSduId;
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
        u2_RxNSduId = bsw_cantp_cmn_u2LatestRxNSduId;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
        u2_PduId = ptRxNSduCfgTbl->u2NPduId;
        u4_Length = ptTpPduInfo->u4SduLength;
        pt_SduData = ptTpPduInfo->ptSduData;

        u1_SORRet = bsw_cantp_rx_CbkPreCheckSOR( (PduIdType)u2_RxNSduId, (PduIdType)u2_PduId, (uint8)u4_Length, pt_SduData );
        if( u1_SORRet == (Std_ReturnType)E_OK )
        {
            u1_ChId     = ptRxNSduCfgTbl->u1ParentChId;
            pt_ChCfgTblTop = ptCfgTbl->ptChCfgTbl;
            pt_ChCfgTbl = &pt_ChCfgTblTop[u1_ChId];

            /* Communication status check */
            u1_SenderStat = bsw_cantp_st_stChStatTbl[u1_ChId].stSenderStatTbl.u1SenderStat;
            if( ( pt_ChCfgTbl->u1ChMode == (uint8)BSW_CANTP_MODE_HALF_DUPLEX )
            &&  ( u1_SenderStat         != BSW_CANTP_ST_u1STS_IDLE ) )
            {   /* Sending in half duplex */

                /* Mediation of the transmission and the reception during the transmission */
                u1_MediStat = bsw_cantp_rx_MedInSender( ptCfgTbl, ptRxNSduCfgTbl );
            }
            else
            {   /* Other status (Receiver stat is idle or during reception in half duplex) */
                u1_MediStat = bsw_cantp_rx_MedInReceiver( ptCfgTbl, ptRxNSduCfgTbl );
            }

            if( u1_MediStat == BSW_CANTP_RX_u1ACCEPT_NEW_SDU )
            {
                /* New request frame was accepted */
                /* Note: u1ReceiverAcceptedReqCnt is supported to wrap around. */
                u2_RecvConter = (uint16)bsw_cantp_st_stChStatTbl[u1_ChId].stReceiverStatTbl.u1ReceiverAcceptedReqCnt;
                u2_RecvConter++;
                bsw_cantp_st_stChStatTbl[u1_ChId].stReceiverStatTbl.u1ReceiverAcceptedReqCnt = (uint8)(u2_RecvConter & BSW_CANTP_RX_u2COUNTER_U1MAX);

                /* SF reception processing */
                bsw_cantp_rx_ReceiveSF( ptRxNSduCfgTbl, ptTpPduInfo );
            }
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | bsw_cantp_rx_RxIndFF                                     */
/* Description   | Receive indication procedure of FF N_PDU                 */
/* Preconditions | None                                                     */
/* Parameters    | ptCfgTbl       : Pointer to CanTp configuration          */
/*               | ptRxNSduCfgTbl : Pointer to RxNSdu configuration         */
/*               | ptTpPduInfo    : Pointer to PDU information              */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_cantp_rx_RxIndFF( BswConst Bsw_CanTp_CfgType * ptCfgTbl, BswConst Bsw_CanTp_RxNSduCfgType * ptRxNSduCfgTbl, BswConstR Bsw_CanTp_PduInfoType * ptTpPduInfo )
{
    BswConst Bsw_CanTp_ChCfgType    *  pt_ChCfgTblTop;     /* Pointer to ChCfgTbl              */
    BswConst Bsw_CanTp_ChCfgType    *  pt_ChCfgTbl;        /* Pointer to channel configuration */
    Bsw_CanTp_st_ReceiverStatType   *  pt_ReceiverStatTbl; /* Pointer to receiver status info  */
    uint16                             u2_RxNSduId;        /* Target Rx NSdu-Id                */
    uint16                             u2_RecvConter;      /* ReceiverAcceptedReqCnter         */
    Bsw_CanTp_st_ProcStatType          u1_SenderStat;      /* Sender processing status         */
    uint8                              u1_ChId;            /* Channel ID                       */
    Bsw_CanTp_ReturnType               u1_Result;          /* Check result                     */
    uint8                              u1_MediStat;        /* Mediation status                 */
    Std_ReturnType                     u1_SORRet;          /* Check SOR result                 */
    uint16                             u2_PduId;           /* CanIf PduId                      */
    uint32                             u4_Length;          /* Sdu Length                       */
    uint8                           *  pt_SduData;         /* Sdu Data                         */

    /* FF format check */
    u1_Result = bsw_cantp_rx_VerifyFF( ptRxNSduCfgTbl, ptTpPduInfo );
    if( u1_Result == (Bsw_CanTp_ReturnType)BSW_CANTP_E_OK )
    {
        /* Pre-Check for StartOfReception */
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
        u2_RxNSduId = ptRxNSduCfgTbl->u2NSduId;
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
        u2_RxNSduId = bsw_cantp_cmn_u2LatestRxNSduId;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
        u2_PduId = ptRxNSduCfgTbl->u2NPduId;
        u4_Length = ptTpPduInfo->u4SduLength;
        pt_SduData = ptTpPduInfo->ptSduData;

        u1_SORRet = bsw_cantp_rx_CbkPreCheckSOR( (PduIdType)u2_RxNSduId, (PduIdType)u2_PduId, (uint8)u4_Length, pt_SduData );
        if( u1_SORRet == (Std_ReturnType)E_OK )
        {
            u1_ChId     = ptRxNSduCfgTbl->u1ParentChId;
            pt_ChCfgTblTop = ptCfgTbl->ptChCfgTbl;
            pt_ChCfgTbl = &pt_ChCfgTblTop[u1_ChId];

            /* Communication status check */
            u1_SenderStat = bsw_cantp_st_stChStatTbl[u1_ChId].stSenderStatTbl.u1SenderStat;
            if( ( pt_ChCfgTbl->u1ChMode == (uint8)BSW_CANTP_MODE_HALF_DUPLEX )
            &&  ( u1_SenderStat         != BSW_CANTP_ST_u1STS_IDLE ) )
            {   /* Sending in half duplex */

                /* Mediation of the transmission and the reception during the transmission */
                u1_MediStat = bsw_cantp_rx_MedInSender( ptCfgTbl, ptRxNSduCfgTbl );
            }
            else
            {   /* Other status (Receiver stat is idle or during reception in half duplex) */
                u1_MediStat = bsw_cantp_rx_MedInReceiver( ptCfgTbl, ptRxNSduCfgTbl );
            }

            if( u1_MediStat == BSW_CANTP_RX_u1ACCEPT_NEW_SDU )
            {
                /* New request frame was accepted */
                pt_ReceiverStatTbl = &(bsw_cantp_st_stChStatTbl[u1_ChId].stReceiverStatTbl);
                /* Note: u1ReceiverAcceptedReqCnt is supported to wrap around. */
                u2_RecvConter = (uint16)pt_ReceiverStatTbl->u1ReceiverAcceptedReqCnt;
                u2_RecvConter++;
                pt_ReceiverStatTbl->u1ReceiverAcceptedReqCnt = (uint8)(u2_RecvConter & BSW_CANTP_RX_u2COUNTER_U1MAX);

                /* FF reception processing */
                bsw_cantp_rx_ReceiveFF( ptRxNSduCfgTbl, ptTpPduInfo, pt_ReceiverStatTbl );
            }
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | bsw_cantp_rx_RxIndCF                                     */
/* Description   | Receive indication procedure of CF N_PDU                 */
/* Preconditions | None                                                     */
/* Parameters    | ptRxNSduCfgTbl : Pointer to RxNSdu configuration         */
/*               | ptTpPduInfo    : Pointer to PDU information              */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_cantp_rx_RxIndCF( BswConst Bsw_CanTp_CfgType * ptCfgTbl, BswConst Bsw_CanTp_RxNSduCfgType * ptRxNSduCfgTbl, BswConstR Bsw_CanTp_PduInfoType * ptTpPduInfo )
{
    Bsw_CanTp_st_ReceiverStatType *    pt_ReceiverStatTbl; /* Pointer to receiver status info */
    uint16                             u2_RxNSduId;        /* Target Rx NSdu-Id               */
    Bsw_CanTp_st_ProcStatType          u1_ReceiverStat;    /* Receiver processing status      */
    uint8                              u1_ChId;            /* Channel ID                      */
    Bsw_CanTp_ReturnType               u1_Result;          /* Verify result                   */
#if( BSW_CANTP_CFG_NEXTRX_IN_TX == BSW_CANTP_TX_REGARD_OK )
    uint16                             u2_CanIf_PduId;     /* CanIf PduId                     */
#endif /* BSW_CANTP_CFG_NEXTRX_IN_TX == BSW_CANTP_TX_REGARD_OK */

    u1_ChId            = ptRxNSduCfgTbl->u1ParentChId;
    pt_ReceiverStatTbl = &(bsw_cantp_st_stChStatTbl[u1_ChId].stReceiverStatTbl);
    u1_ReceiverStat    = pt_ReceiverStatTbl->u1ReceiverStat;

    /* Check if CF reception can happen */
#if( BSW_CANTP_CFG_NEXTRX_IN_TX == BSW_CANTP_TX_REGARD_OK )
    if( (  ( u1_ReceiverStat == BSW_CANTP_ST_u1STS_FC_TX )                     /* Waiting for FC.CTS TxConfirmation (FC.CTS and CF was interchanged in lower layer) */
        && ( pt_ReceiverStatTbl->u1ReceiverFS == BSW_CANTP_u1FS_RECEIVER_CTS ) )
    ||  ( u1_ReceiverStat == BSW_CANTP_ST_u1STS_CF_RX ) )                      /* Waiting for CF RxIndication */
#else /* BSW_CANTP_CFG_NEXTRX_IN_TX == BSW_CANTP_TX_INCOMPLETE */
    if( u1_ReceiverStat == BSW_CANTP_ST_u1STS_CF_RX )                          /* Waiting for CF RxIndication */
#endif /* BSW_CANTP_CFG_NEXTRX_IN_TX == BSW_CANTP_TX_REGARD_OK */
    {
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
        u2_RxNSduId = ptRxNSduCfgTbl->u2NSduId;
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
        u2_RxNSduId = bsw_cantp_cmn_u2LatestRxNSduId;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
        /* NSduId Check */
        if( u2_RxNSduId == pt_ReceiverStatTbl->u2ReceiverNSduId )
        {
            /* CF format check */
            u1_Result = bsw_cantp_rx_VerifyCF( ptRxNSduCfgTbl, ptTpPduInfo, pt_ReceiverStatTbl );
            if( u1_Result == (Bsw_CanTp_ReturnType)BSW_CANTP_E_OK )
            {
#if( BSW_CANTP_CFG_NEXTRX_IN_TX == BSW_CANTP_TX_REGARD_OK )
                if( u1_ReceiverStat != BSW_CANTP_ST_u1STS_CF_RX )
                {
                    u2_CanIf_PduId = ptRxNSduCfgTbl->u2CanIf_FcPduId;
                    /* Replaced TxConfirmation */
                    bsw_cantp_snd_AbortSend( u2_CanIf_PduId );
                }
#endif /* BSW_CANTP_CFG_NEXTRX_IN_TX == BSW_CANTP_TX_REGARD_OK */
                /* CF reception processing */
                bsw_cantp_rx_ReceiveCF( ptCfgTbl, ptRxNSduCfgTbl, ptTpPduInfo, pt_ReceiverStatTbl );
            }
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | bsw_cantp_rx_TxConfRX                                    */
/* Description   | Transmission completion handling of FC message           */
/* Preconditions | None                                                     */
/* Parameters    | ptRxNSduCfgTbl : Pointer to RxNSdu configuration         */
/*               | u1Result       : Result of the transmission              */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_cantp_rx_TxConfRX( BswConst Bsw_CanTp_RxNSduCfgType * ptRxNSduCfgTbl, Std_ReturnType u1Result )
{
    Bsw_CanTp_st_ReceiverStatType *    pt_ReceiverStatTbl;     /* Pointer to receiver status info */
    Bsw_CanTp_st_FSType                u1_ReceiverFS;          /* Flow status                     */
    uint16                             u2_NcrCycle;            /* N_cr Cycle                      */
    uint16                             u2_WFTMax;              /* WFt Max                         */
    uint16                             u2_ReceiverFCWaitCnt;   /* Number of sent FC.WAIT          */
#if( BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE )
    uint8                              u1_RxParamPtn;          /* Rx Parameter Pattern            */
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
    uint8                              u1_ChId;                /* Channel ID                      */
    

    u1_ChId            = ptRxNSduCfgTbl->u1ParentChId;
    pt_ReceiverStatTbl = &(bsw_cantp_st_stChStatTbl[u1_ChId].stReceiverStatTbl);

    switch( pt_ReceiverStatTbl->u1ReceiverStat )
    {
        case BSW_CANTP_ST_u1STS_FC_TX:

            if( u1Result == (Std_ReturnType)E_OK )
            {
                /* Flow status check */
                u1_ReceiverFS = pt_ReceiverStatTbl->u1ReceiverFS;
                if( u1_ReceiverFS == BSW_CANTP_u1FS_RECEIVER_CTS )
                {
                    /* wait NEXT CF */
                    pt_ReceiverStatTbl->u1ReceiverStat  = BSW_CANTP_ST_u1STS_CF_RX;
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
                    u2_NcrCycle = ptRxNSduCfgTbl->u2NcrCycle;
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
                    u1_RxParamPtn = ptRxNSduCfgTbl->u1RxParamPtn;
                    u2_NcrCycle = bsw_cantp_stRxNSduParamTbl[u1_RxParamPtn].u2NcrCycle;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
                    pt_ReceiverStatTbl->u2ReceiverCycle = u2_NcrCycle + BSW_CANTP_u2MAIN_CYCLE_DOUBLE;
                }
                else if( u1_ReceiverFS == BSW_CANTP_u1FS_RECEIVER_WT )
                {
                    /* buffer check again */
                    pt_ReceiverStatTbl->u1ReceiverStat  = BSW_CANTP_ST_u1STS_FC_WAIT;
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
                    u2_WFTMax = ptRxNSduCfgTbl->u2WFTMax;
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
                    u1_RxParamPtn = ptRxNSduCfgTbl->u1RxParamPtn;
                    u2_WFTMax = bsw_cantp_stRxNSduParamTbl[u1_RxParamPtn].u2WFTMax;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
                    u2_ReceiverFCWaitCnt = pt_ReceiverStatTbl->u2ReceiverFCWaitCnt;
                    if( u2_ReceiverFCWaitCnt >= u2_WFTMax )
                    {   /* FC.WAIT has reached the Max Num of transmissions */
                        pt_ReceiverStatTbl->u2ReceiverCycle = bsw_cantp_u2FcTxTimeout + BSW_CANTP_u2MAIN_CYCLE_DOUBLE;
                    }
                    else
                    {   /* FC.WAIT has not reached the Max Num of transmissions */
                        pt_ReceiverStatTbl->u2ReceiverCycle = bsw_cantp_u2FcWaitTxPeriodTime;
                    }
                    pt_ReceiverStatTbl->u1ReceiverFS    = BSW_CANTP_u1FS_RECEIVER_WT;
                }
                else if( u1_ReceiverFS == BSW_CANTP_u1FS_RECEIVER_OVFL )
                {   /* Flow status is overflow */
                    bsw_cantp_rx_ReceiverToIdle( pt_ReceiverStatTbl );
                }
                else
                {   /* Flow status is broken */
                    bsw_cantp_cmn_u1ErrState = BSW_CANTP_u1RAMERR;
                    bsw_cantp_rx_ReceiverToIdle( pt_ReceiverStatTbl );
                }
            }
            else
            {
                /* FC transmission is not successfully finished */
                bsw_cantp_rx_TerminateRx( ptRxNSduCfgTbl, pt_ReceiverStatTbl, (Std_ReturnType)E_NOT_OK );
            }
            break;

        case BSW_CANTP_ST_u1STS_FC_WAIT:       /* FALLTHROUGH */
        case BSW_CANTP_ST_u1STS_CF_RX:
            /* NOP */
            break;

        case BSW_CANTP_ST_u1STS_IDLE:
            bsw_cantp_rx_ReceiverToIdle( pt_ReceiverStatTbl );
            break;

        default:
            /* RAM broken */
            bsw_cantp_cmn_u1ErrState = BSW_CANTP_u1RAMERR;
            bsw_cantp_rx_ReceiverToIdle( pt_ReceiverStatTbl );
            break;
    }

    return;
}


#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
#if( BSW_CANTP_CFG_CHANGE_RXPARAM == BSW_USE )
/****************************************************************************/
/* Function Name | bsw_cantp_rx_ChangeParamBS                               */
/* Description   | Store BS value of target RxNSdu to BS table              */
/* Preconditions | None                                                     */
/* Parameters    | ptRxNSduCfgTbl : Pointer to RxNSdu configuration         */
/*               | u2NewBS        : Value of BS                             */
/* Return Value  | None                                                     */
/* Notes         | The arguments are already verified                       */
/****************************************************************************/
void
bsw_cantp_rx_ChangeParamBS( BswConst Bsw_CanTp_RxNSduCfgType * ptRxNSduCfgTbl, uint16 u2NewBS )
{
    uint16  u2_TmpBS;   /* Value of BS with mirror value */

    /* Save values of BS and verifications */
    u2_TmpBS = u2NewBS ^ BSW_CANTP_RX_u2LOW8BIT_ON;
    u2_TmpBS = (uint16)(u2_TmpBS << BSW_CANTP_BIT_SHIFT8) | u2NewBS;
    bsw_cantp_stBSSTminTbl[ptRxNSduCfgTbl->u2CfgTblIdx].u2BS = u2_TmpBS;

    return;
}


/****************************************************************************/
/* Function Name | bsw_cantp_rx_ChangeParamSTmin                            */
/* Description   | Store STmin value of target RxNSdu to STmin table        */
/* Preconditions | None                                                     */
/* Parameters    | ptRxNSduCfgTbl : Pointer to RxNSdu configuration         */
/*               | u2NewSTmin     : Value of STmin                          */
/* Return Value  | None                                                     */
/* Notes         | The arguments are already verified                       */
/****************************************************************************/
void
bsw_cantp_rx_ChangeParamSTmin( BswConst Bsw_CanTp_RxNSduCfgType * ptRxNSduCfgTbl, uint16 u2NewSTmin )
{
    uint16  u2_TmpSTmin;    /* Value of STmin with mirror value */

    /* Save values of STmin and verifications */
    u2_TmpSTmin = u2NewSTmin ^ BSW_CANTP_RX_u2LOW8BIT_ON;
    u2_TmpSTmin = (uint16)(u2_TmpSTmin << BSW_CANTP_BIT_SHIFT8) | u2NewSTmin;
    bsw_cantp_stBSSTminTbl[ptRxNSduCfgTbl->u2CfgTblIdx].u2STmin = u2_TmpSTmin;

    return;
}
#endif /* BSW_CANTP_CFG_CHANGE_RXPARAM == BSW_USE */


/****************************************************************************/
/* Function Name | bsw_cantp_rx_ReadParamBS                                 */
/* Description   | Read BS value of target RxNSdu from BS table             */
/* Preconditions | None                                                     */
/* Parameters    | ptRxNSduCfgTbl : Pointer to RxNSdu configuration         */
/* Return Value  | uint16         : Block Size                              */
/* Notes         | None                                                     */
/****************************************************************************/
uint16
bsw_cantp_rx_ReadParamBS( BswConst Bsw_CanTp_RxNSduCfgType * ptRxNSduCfgTbl )
{
    uint16  u2_Ret;             /* Return value              */
#if( BSW_CANTP_CFG_CHANGE_RXPARAM == BSW_USE )
    uint16  u2_BS;              /* Block size                */
    uint8   u1_ChkBS;           /* Check value of Block size */

    /* RAM check */
    u2_BS    = bsw_cantp_stBSSTminTbl[ptRxNSduCfgTbl->u2CfgTblIdx].u2BS;
    u1_ChkBS = (uint8)(u2_BS >> BSW_CANTP_BIT_SHIFT8) ^ (uint8)(u2_BS & BSW_CANTP_u2LOW8BITMASK);
    if( u1_ChkBS != BSW_CANTP_RX_u1MIRRORVALIDATE )
    {   /* u2BS is broken */
        bsw_cantp_cmn_u1ErrState = BSW_CANTP_u1RAMERR;

        /* recovery */
        u2_BS = (uint16)(ptRxNSduCfgTbl->u1BlockSize);
        bsw_cantp_rx_ChangeParamBS( ptRxNSduCfgTbl, u2_BS );
    }

    u2_Ret = u2_BS & BSW_CANTP_u2LOW8BITMASK;
#else /* BSW_CANTP_CFG_CHANGE_RXPARAM != BSW_USE */

    u2_Ret = (uint16)(ptRxNSduCfgTbl->u1BlockSize);

#endif /* BSW_CANTP_CFG_CHANGE_RXPARAM == BSW_USE */

    return u2_Ret;
}


/****************************************************************************/
/* Function Name | bsw_cantp_rx_ReadParamSTmin                              */
/* Description   | Read parameter STmin of target RxNSdu from STmin table   */
/* Preconditions | None                                                     */
/* Parameters    | ptRxNSduCfgTbl : Pointer to RxNSdu configuration         */
/* Return Value  | uint16         : Separation Time Minimum                 */
/* Notes         | None                                                     */
/****************************************************************************/
uint16
bsw_cantp_rx_ReadParamSTmin( BswConst Bsw_CanTp_RxNSduCfgType * ptRxNSduCfgTbl )
{
    uint16  u2_Ret;             /* Return value                           */
#if( BSW_CANTP_CFG_CHANGE_RXPARAM == BSW_USE )
    uint16  u2_STmin;           /* Separation Time Minimum                */
    uint8   u1_ChkSTmin;        /* Check value of Separation Time Minimum */

    /* RAM check */
    u2_STmin    = bsw_cantp_stBSSTminTbl[ptRxNSduCfgTbl->u2CfgTblIdx].u2STmin;
    u1_ChkSTmin = (uint8)(u2_STmin >> BSW_CANTP_BIT_SHIFT8) ^ (uint8)(u2_STmin & BSW_CANTP_u2LOW8BITMASK);
    if( u1_ChkSTmin != BSW_CANTP_RX_u1MIRRORVALIDATE )
    {   /* u2STmin is broken */
        bsw_cantp_cmn_u1ErrState = BSW_CANTP_u1RAMERR;

        /* recovery */
        u2_STmin = (uint16)(ptRxNSduCfgTbl->u1STmin);
        bsw_cantp_rx_ChangeParamSTmin( ptRxNSduCfgTbl, u2_STmin );
    }

    u2_Ret = u2_STmin & BSW_CANTP_u2LOW8BITMASK;
#else /* BSW_CANTP_CFG_CHANGE_RXPARAM != BSW_USE */

    u2_Ret = (uint16)(ptRxNSduCfgTbl->u1STmin);

#endif /* BSW_CANTP_CFG_CHANGE_RXPARAM == BSW_USE */

    return u2_Ret;
}


#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
#if( BSW_CANTP_CFG_CHANGE_RXPARAM == BSW_USE )
/****************************************************************************/
/* Function Name | bsw_cantp_rx_ChangeParamBSByIdx                          */
/* Description   | Store BS value of target RxNSdu to BS table              */
/* Preconditions | None                                                     */
/* Parameters    | u2CfgTblIdx    : RxNSdu Config Table Index               */
/*               | u2NewBS        : Value of BS                             */
/* Return Value  | None                                                     */
/* Notes         | The arguments are already verified                       */
/****************************************************************************/
void
bsw_cantp_rx_ChangeParamBSByIdx( uint16 u2CfgTblIdx, uint16 u2NewBS )
{
    uint16  u2_TmpBS;           /* Value of BS with mirror value */

    /* Save values of BS and verifications */
    u2_TmpBS = u2NewBS ^ BSW_CANTP_RX_u2LOW8BIT_ON;
    u2_TmpBS = (uint16)(u2_TmpBS << BSW_CANTP_BIT_SHIFT8) | u2NewBS;
    bsw_cantp_stBSSTminTbl[u2CfgTblIdx].u2BS = u2_TmpBS;

    return;
}


/****************************************************************************/
/* Function Name | bsw_cantp_rx_ChgParamSTminByIdx                          */
/* Description   | Store STmin value of target RxNSdu to STmin table        */
/* Preconditions | None                                                     */
/* Parameters    | u2CfgTblIdx    : RxNSdu Config Table Index               */
/*               | u2NewSTmin     : Value of STmin                          */
/* Return Value  | None                                                     */
/* Notes         | The arguments are already verified                       */
/****************************************************************************/
void
bsw_cantp_rx_ChgParamSTminByIdx( uint16 u2CfgTblIdx, uint16 u2NewSTmin )
{
    uint16  u2_TmpSTmin;    /* Value of STmin with mirror value */

    /* Save values of STmin and verifications */
    u2_TmpSTmin = u2NewSTmin ^ BSW_CANTP_RX_u2LOW8BIT_ON;
    u2_TmpSTmin = (uint16)(u2_TmpSTmin << BSW_CANTP_BIT_SHIFT8) | u2NewSTmin;
    bsw_cantp_stBSSTminTbl[u2CfgTblIdx].u2STmin = u2_TmpSTmin;

    return;
}
#endif /* BSW_CANTP_CFG_CHANGE_RXPARAM == BSW_USE */


/****************************************************************************/
/* Function Name | bsw_cantp_rx_ReadParamBSByIdx                            */
/* Description   | Read BS value of target RxNSdu from BS table             */
/* Preconditions | None                                                     */
/* Parameters    | u2CfgTblIdx    : RxNSdu Config Table Index               */
/*               | u1RxParamPtn   : Rx Parameter Pattern                    */
/* Return Value  | uint16         : Block Size                              */
/* Notes         | None                                                     */
/****************************************************************************/
uint16
bsw_cantp_rx_ReadParamBSByIdx( uint16 u2CfgTblIdx, uint8 u1RxParamPtn )
{
    uint16  u2_Ret;             /* Return value              */
#if( BSW_CANTP_CFG_CHANGE_RXPARAM == BSW_USE )
    uint16  u2_BS;              /* Block size                */
    uint8   u1_ChkBS;           /* Check value of Block size */

    /* RAM check */
    u2_BS    = bsw_cantp_stBSSTminTbl[u2CfgTblIdx].u2BS;
    u1_ChkBS = (uint8)(u2_BS >> BSW_CANTP_BIT_SHIFT8) ^ (uint8)(u2_BS & BSW_CANTP_u2LOW8BITMASK);
    if( u1_ChkBS != BSW_CANTP_RX_u1MIRRORVALIDATE )
    {   /* u2BS is broken */
        bsw_cantp_cmn_u1ErrState = BSW_CANTP_u1RAMERR;

        /* recovery */
        u2_BS = (uint16)(bsw_cantp_stRxNSduParamTbl[u1RxParamPtn].u1BlockSize);
        bsw_cantp_rx_ChangeParamBSByIdx( u2CfgTblIdx, u2_BS );
    }

    u2_Ret = u2_BS & BSW_CANTP_u2LOW8BITMASK;
#else /* BSW_CANTP_CFG_CHANGE_RXPARAM != BSW_USE */

    u2_Ret = (uint16)(bsw_cantp_stRxNSduParamTbl[u1RxParamPtn].u1BlockSize);

#endif /* BSW_CANTP_CFG_CHANGE_RXPARAM == BSW_USE */

    return u2_Ret;
}


/****************************************************************************/
/* Function Name | bsw_cantp_rx_ReadParaSTminByIdx                          */
/* Description   | Read parameter STmin of target RxNSdu from STmin table   */
/* Preconditions | None                                                     */
/* Parameters    | u2CfgTblIdx    : RxNSdu Config Table Index               */
/*               | u1RxParamPtn   : Rx Parameter Pattern                    */
/* Return Value  | uint16         : Separation Time Minimum                 */
/* Notes         | None                                                     */
/****************************************************************************/
uint16
bsw_cantp_rx_ReadParaSTminByIdx( uint16 u2CfgTblIdx, uint8 u1RxParamPtn )
{
    uint16  u2_Ret;             /* Return value                           */
#if( BSW_CANTP_CFG_CHANGE_RXPARAM == BSW_USE )
    uint16  u2_STmin;           /* Separation Time Minimum                */
    uint8   u1_ChkSTmin;        /* Check value of Separation Time Minimum */

    /* RAM check */
    u2_STmin    = bsw_cantp_stBSSTminTbl[u2CfgTblIdx].u2STmin;
    u1_ChkSTmin = (uint8)(u2_STmin >> BSW_CANTP_BIT_SHIFT8) ^ (uint8)(u2_STmin & BSW_CANTP_u2LOW8BITMASK);
    if( u1_ChkSTmin != BSW_CANTP_RX_u1MIRRORVALIDATE )
    {   /* u2STmin is broken */
        bsw_cantp_cmn_u1ErrState = BSW_CANTP_u1RAMERR;

        /* recovery */
        u2_STmin = (uint16)(bsw_cantp_stRxNSduParamTbl[u1RxParamPtn].u1STmin);
        bsw_cantp_rx_ChgParamSTminByIdx( u2CfgTblIdx, u2_STmin );
    }

    u2_Ret = u2_STmin & BSW_CANTP_u2LOW8BITMASK;
#else /* BSW_CANTP_CFG_CHANGE_RXPARAM != BSW_USE */

    u2_Ret = (uint16)(bsw_cantp_stRxNSduParamTbl[u1RxParamPtn].u1STmin);

#endif /* BSW_CANTP_CFG_CHANGE_RXPARAM == BSW_USE */

    return u2_Ret;
}
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | bsw_cantp_rx_VerifySF                                    */
/* Description   | Verify of received message as SF                         */
/* Preconditions | None                                                     */
/* Parameters    | ptRxNSduCfgTbl  : Pointer to target RxNSdu configuration */
/*               | ptTpPduInfo     : Pointer to target PDU information      */
/* Return Value  | Bsw_CanTp_ReturnType                                     */
/*               |  BSW_CANTP_E_OK     : valid                              */
/*               |  BSW_CANTP_E_NOT_OK : invalid                            */
/* Notes         | None                                                     */
/****************************************************************************/
static Bsw_CanTp_ReturnType
bsw_cantp_rx_VerifySF( BswConst Bsw_CanTp_RxNSduCfgType * ptRxNSduCfgTbl, BswConstR Bsw_CanTp_PduInfoType * ptTpPduInfo )
{
    uint32                  u4_CanDl;           /* CAN_DL                                    */
    uint8                   u1_SFDL;            /* SF_DL                                     */
    uint8                   u1_PciOffset;       /* Offset to N_PCI address                   */
    Bsw_CanTp_ReturnType    u1_Ret;             /* Return value                              */
    uint8                   u1_RxPaddingAct;    /* Rx Padding Action                         */
    uint8                   u1_AddressFormat;   /* Address Format                            */
    uint8                   u1_ExpSFDL;         /* Expected SF_DL Value (CAN_DL <= 8)        */
#if( BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE )
    uint8                   u1_RxParamPtn;      /* Rx Parameter Pattern                      */
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
#if( BSW_CANTP_CFG_FDSUPPORT == BSW_USE )
    uint8                   u1_ExpMinSFDL;      /* Expected SF_DL Minimum Value (CAN_DL > 8) */
    uint8                   u1_ExpMaxSFDL;      /* Expected SF_DL Maximum Value (CAN_DL > 8) */
#endif /* CANTP_FDSUPPORT == BSW_USE */

    u1_Ret           = (Bsw_CanTp_ReturnType)BSW_CANTP_E_NOT_OK;
    u4_CanDl         = ptTpPduInfo->u4SduLength;
    u1_AddressFormat = ptRxNSduCfgTbl->u1AddressFormat;
    u1_PciOffset     = bsw_cantp_cmn_u1PciOffSetTbl[u1_AddressFormat];

    /*                    Byte | #1            | #2    | #3    | ...    | */
    /*                    Bit  | 7-4   | 3-0   |       |       | ...    | */
    /*-------------------------+-------+-------+-------+-------+--------+ */
    /* SF(CAN_DL <= 8)         | 0000b | SF_DL | -               ...    | */
    /* SF(CAN_DL >  8)(FD only)| 0000b | 0000b | SF_DL | -       ...    | */

    /* Check CAN frame payload length */
    if( u4_CanDl <= (uint32)BSW_CANTP_u1CAN_DL_08 )
    {   /* SF(CAN_DL <= 8) */

        /* Get 4 bit SF_DL value from Byte #1                        */
        /* Note: ptTpPduInfo.length is greater than or equal to 2.   */
        /*       (It has been checked in bsw_cantp_RxIndForwardByNPCI()) */

        u1_SFDL = ptTpPduInfo->ptSduData[u1_PciOffset] & BSW_CANTP_u1MASK_SF_SFDL;

        /* Check for valid SF_DL */
        /* 0000b        : Reserved                                            */
        /* 0001b-0110b  : Single Frame DataLength                             */
        /* 0111b        : Single Frame DataLength with normal addressing only */
        /* other values : Invalid                                             */
        if( ( u1_SFDL >= BSW_CANTP_u1CAN_DL_01 ) && ( u1_SFDL <= (BSW_CANTP_u1CAN_DL_07 - u1_PciOffset) ) )
        {  /* SF_DL is valid (Mixed/Extend:1-6, Normal/Fixed:1-7) */

            /* padding check */
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
            u1_RxPaddingAct = ptRxNSduCfgTbl->u1PaddingAct;
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
            u1_RxParamPtn = ptRxNSduCfgTbl->u1RxParamPtn;
            u1_RxPaddingAct = bsw_cantp_stRxNSduParamTbl[u1_RxParamPtn].u1PaddingAct;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
            if( u1_RxPaddingAct == (uint8)BSW_CANTP_ON )
            {   /* CAN frame data padding */
                if( u4_CanDl == (uint32)BSW_CANTP_u1CAN_DL_08 )
                {   /* CAN_DL is valid */
                    u1_Ret = (Bsw_CanTp_ReturnType)BSW_CANTP_E_OK;
                }
            }
            else
            {   /* CAN frame data optimization */
                if( u4_CanDl > ((uint32)u1_PciOffset + (uint32)BSW_CANTP_u1PCI_SIZE_SF) )
                {
                    u1_ExpSFDL = (uint8)u4_CanDl - (u1_PciOffset + BSW_CANTP_u1PCI_SIZE_SF);
#if ( BSW_CANTP_CFG_DLCHKSF_PTN == BSW_CANTP_DLCHKSF_PTN0 )
                    if( u1_SFDL == u1_ExpSFDL )
#else /* BSW_CANTP_CFG_DLCHKSF_PTN == BSW_CANTP_DLCHKSF_PTN1 */
                    if( u1_SFDL <= u1_ExpSFDL )
#endif /* BSW_CANTP_CFG_DLCHKSF_PTN == BSW_CANTP_DLCHKSF_PTN0 */
                    {   /* SF_DL is valid */
                        u1_Ret = (Bsw_CanTp_ReturnType)BSW_CANTP_E_OK;
                    }
                }
            }
        }
    }
#if( BSW_CANTP_CFG_FDSUPPORT == BSW_USE )
    else
    {   /* SF(CAN_DL > 8) */

        /* Check 4bit SF_DL Value in Byte #1 low nibble equals zero */
        if( ptTpPduInfo->ptSduData[u1_PciOffset] == BSW_CANTP_u1PCI_FIRSTBYTE_SF_ES )
        {   /* N_PCI Byte #1 = 0000 0000b */

            /* Get 8 bit SF_DL value from Byte #2 */
            u1_SFDL = ptTpPduInfo->ptSduData[u1_PciOffset + (uint8)BSW_CANTP_OFFSET1];

            switch( u4_CanDl )
            {
                /* Calclattion of  SF_DL's expected value range (case CAN_DL > 8) */
                case (BSW_CANTP_u1CAN_DL_12) :
                    u1_ExpMinSFDL = BSW_CANTP_u1CAN_DL_08 - ( u1_PciOffset + BSW_CANTP_u1PCI_SIZE_SF    );
                    u1_ExpMaxSFDL = BSW_CANTP_u1CAN_DL_12 - ( u1_PciOffset + BSW_CANTP_u1PCI_SIZE_SF_ES );
                    break;
                case (BSW_CANTP_u1CAN_DL_16) :
                    u1_ExpMinSFDL = BSW_CANTP_u1CAN_DL_12 - ( u1_PciOffset + BSW_CANTP_u1PCI_SIZE_SF_ES );
                    u1_ExpMaxSFDL = BSW_CANTP_u1CAN_DL_16 - ( u1_PciOffset + BSW_CANTP_u1PCI_SIZE_SF_ES );
                    break;
                case (BSW_CANTP_u1CAN_DL_20) :
                    u1_ExpMinSFDL = BSW_CANTP_u1CAN_DL_16 - ( u1_PciOffset + BSW_CANTP_u1PCI_SIZE_SF_ES );
                    u1_ExpMaxSFDL = BSW_CANTP_u1CAN_DL_20 - ( u1_PciOffset + BSW_CANTP_u1PCI_SIZE_SF_ES );
                    break;
                case (BSW_CANTP_u1CAN_DL_24) :
                    u1_ExpMinSFDL = BSW_CANTP_u1CAN_DL_20 - ( u1_PciOffset + BSW_CANTP_u1PCI_SIZE_SF_ES );
                    u1_ExpMaxSFDL = BSW_CANTP_u1CAN_DL_24 - ( u1_PciOffset + BSW_CANTP_u1PCI_SIZE_SF_ES );
                    break;
                case (BSW_CANTP_u1CAN_DL_32) :
                    u1_ExpMinSFDL = BSW_CANTP_u1CAN_DL_24 - ( u1_PciOffset + BSW_CANTP_u1PCI_SIZE_SF_ES );
                    u1_ExpMaxSFDL = BSW_CANTP_u1CAN_DL_32 - ( u1_PciOffset + BSW_CANTP_u1PCI_SIZE_SF_ES );
                    break;
                case (BSW_CANTP_u1CAN_DL_48) :
                    u1_ExpMinSFDL = BSW_CANTP_u1CAN_DL_32 - ( u1_PciOffset + BSW_CANTP_u1PCI_SIZE_SF_ES );
                    u1_ExpMaxSFDL = BSW_CANTP_u1CAN_DL_48 - ( u1_PciOffset + BSW_CANTP_u1PCI_SIZE_SF_ES );
                    break;
                case (BSW_CANTP_u1CAN_DL_64) :
                    u1_ExpMinSFDL = BSW_CANTP_u1CAN_DL_48 - ( u1_PciOffset + BSW_CANTP_u1PCI_SIZE_SF_ES );
                    u1_ExpMaxSFDL = BSW_CANTP_u1CAN_DL_64 - ( u1_PciOffset + BSW_CANTP_u1PCI_SIZE_SF_ES );
                    break;
                default :
                    /* INVALID */
                    u1_ExpMaxSFDL = BSW_CANTP_RX_u1SFDL_EXP_INVALID;
                    break;
            }

            if( ( u1_ExpMaxSFDL != BSW_CANTP_RX_u1SFDL_EXP_INVALID ) /* Expected SF_DL value is not invalid   */
            &&  ( u1_SFDL >  u1_ExpMinSFDL )                         /* SF_DL >= Expected min value + 1       */
            &&  ( u1_SFDL <= u1_ExpMaxSFDL ) )                       /* SF_DL <= Expected max value           */
            {   /* SF_DL is valid, and Using SF(CAN_DL>8) is valid. */
                u1_Ret = (Bsw_CanTp_ReturnType)BSW_CANTP_E_OK;
            }
        }
    }
#endif /* BSW_CANTP_CFG_FDSUPPORT == BSW_USE */

    return u1_Ret;
}


/****************************************************************************/
/* Function Name | bsw_cantp_rx_VerifyFF                                    */
/* Description   | Verify of received message as FF                         */
/* Preconditions | None                                                     */
/* Parameters    | ptRxNSduCfgTbl  : Pointer to target RxNSdu configuration */
/*               | ptTpPduInfo     : Pointer to target PDU information      */
/* Return Value  | Bsw_CanTp_ReturnType                                     */
/*               |  BSW_CANTP_E_OK     : valid                              */
/*               |  BSW_CANTP_E_NOT_OK : invalid                            */
/* Notes         | None                                                     */
/****************************************************************************/
static Bsw_CanTp_ReturnType
bsw_cantp_rx_VerifyFF( BswConst Bsw_CanTp_RxNSduCfgType * ptRxNSduCfgTbl, BswConstR Bsw_CanTp_PduInfoType * ptTpPduInfo )
{
    uint32                  u4_CanDl;           /* CAN_DL                           */
    uint32                  u4_FFDL;            /* FF_DL                            */
    uint32                  u4_MaxPduLength;    /* Maximum length of PDU            */
    uint32                  u4_MinFFDL;         /* Lower limit of FF_DL             */
#if( BSW_CANTP_CFG_FDSUPPORT == BSW_USE )
    uint32                  u4_MaxSFDL;         /* Upper limit of SF_DL             */
    uint8                   u1_OptCanDl;        /* Optimized CAN_DL value in CAN FD */
#endif /* BSW_CANTP_CFG_FDSUPPORT == BSW_USE */
    uint8                   u1_TaType;          /* N_TAtype                         */
    uint8                   u1_PciOffset;       /* Offset to N_PCI address          */
    uint8                   u1_AddressFormat;   /* Address Format                   */
    Bsw_CanTp_ReturnType    u1_Ret;             /* Return value                     */

    u1_Ret = (Bsw_CanTp_ReturnType)BSW_CANTP_E_NOT_OK;

    /* Check N_TAtype */
    u1_TaType = ptRxNSduCfgTbl->u1TaType;
    if( u1_TaType == (uint8)BSW_CANTP_PHYSICAL )    /* CANTP_CANFD_PHYSICAL is not necessary regardless CAN_FD or CAN2.0 */
    {
        /* Check for FC NPduId's existence */
        /*   Note: If user uses physical addressing frame, but uses single frame's length only, */
        /*         there is no FC NPduId's configuration.                                       */
        if( ptRxNSduCfgTbl->u2CanIf_FcPduId != BSW_CANTP_u2NPDUID_NA )
        {   /* FC NPduId is exist */

            u4_CanDl     = ptTpPduInfo->u4SduLength;
            u1_AddressFormat = ptRxNSduCfgTbl->u1AddressFormat;
            u1_PciOffset = bsw_cantp_cmn_u1PciOffSetTbl[u1_AddressFormat];

            /* Check CAN_DL */
#if( BSW_CANTP_CFG_FDSUPPORT == BSW_USE )
            u1_OptCanDl  = bsw_cantp_cmn_GetOptimizedCanDl( (uint8)u4_CanDl );
            if( ( u4_CanDl >= (uint32)BSW_CANTP_u1CAN_DL_08 ) && ( u4_CanDl == (uint32)u1_OptCanDl ) )
#else   /* BSW_CANTP_CFG_FDSUPPORT != BSW_USE */
            if( u4_CanDl == (uint32)BSW_CANTP_u1CAN_DL_08 )
#endif  /* BSW_CANTP_CFG_FDSUPPORT == BSW_USE */
            {   /* CAN_DL is valid */
                /* valid value : 8,12,16,20,24,32,48,64 */

                /*                    Byte | #1            | #2    | #3    | #4    | #5    | #6    | */
                /*                    Bit  | 7-4   | 3-0   |       |       |       |       |       | */
                /*-------------------------+-------+-------+-------+-------+-------+-------+-------+ */
                /* FF(FF_DL  <= 4095)      | 0001b | FF_DL         | -                             | */
                /* FF(FF_DL  >  4095)      | 0001b | 0000b | 0x00  | FF_DL                         | */

#if( BSW_CANTP_CFG_MAXPDULENGTH > BSW_CANTP_u4FFDL_4095 )
                if( ( ptTpPduInfo->ptSduData[u1_PciOffset]                        == BSW_CANTP_u1PCI_FIRSTBYTE_FF_ES )
                &&  ( ptTpPduInfo->ptSduData[u1_PciOffset + (uint8)BSW_CANTP_OFFSET1] == BSW_CANTP_u1PCI_SECNDBYTE_FF_ES ) )
                {   /* FF(FF_DL > 4095) */

                    u4_FFDL  = (uint32)(ptTpPduInfo->ptSduData[u1_PciOffset + (uint8)BSW_CANTP_OFFSET2]) << BSW_CANTP_BIT_SHIFT24;
                    u4_FFDL |= (uint32)(ptTpPduInfo->ptSduData[u1_PciOffset + (uint8)BSW_CANTP_OFFSET3]) << BSW_CANTP_BIT_SHIFT16;
                    u4_FFDL |= (uint32)(ptTpPduInfo->ptSduData[u1_PciOffset + (uint8)BSW_CANTP_OFFSET4]) << BSW_CANTP_BIT_SHIFT8;
                    u4_FFDL |= (uint32)(ptTpPduInfo->ptSduData[u1_PciOffset + (uint8)BSW_CANTP_OFFSET5]);

                    u4_MinFFDL = BSW_CANTP_u4FFDL_4096;
                }
                else
#endif /* BSW_CANTP_CFG_MAXPDULENGTH > BSW_CANTP_u4FFDL_4095 */
                {   /* FF(FF_DL <= 4095) */

                    u4_FFDL  = ((uint32)(ptTpPduInfo->ptSduData[u1_PciOffset]) & (uint32)BSW_CANTP_u1MASK_FF_FFDL_H) << BSW_CANTP_BIT_SHIFT8;
                    u4_FFDL |= (uint32)(ptTpPduInfo->ptSduData[u1_PciOffset + (uint8)BSW_CANTP_OFFSET1]);

                    /* Calculation of FF_DL minimum value */
                    /* Condition                                                               FF_DLmin value */
                    /* If the configured TX_DL is 8 and normal addressing is used.             8              */
                    /* If the configured TX_DL is 8 and mixed or extended addressing is used.  7              */
                    /* If the configured TX_DL > 8 and normal addressing is used.              TX_DL - 1      */
                    /* If the configured TX_DL > 8 and mixed or extended addressing is used.   TX_DL - 2      */
                    u4_MinFFDL = (uint32)BSW_CANTP_u1CAN_DL_08 - (uint32)u1_PciOffset;

#if( BSW_CANTP_CFG_FDSUPPORT == BSW_USE )
                    if( u4_CanDl > (uint32)BSW_CANTP_u1CAN_DL_08 )
                    {
                        u4_MaxSFDL = u4_CanDl - (uint32)u1_PciOffset - (uint32)BSW_CANTP_u1PCI_SIZE_SF_ES;
                        u4_MinFFDL = u4_MaxSFDL + BSW_CANTP_u4NDATA_LEN_01;
                    }
#endif  /* BSW_CANTP_CFG_FDSUPPORT == BSW_USE */
                }

                /* Check for valid FF_DL */
                u4_MaxPduLength = bsw_cantp_u4MaxPduLength;
                if( ( u4_FFDL >= u4_MinFFDL )
                &&  ( u4_FFDL <= u4_MaxPduLength ) )    /* Upper limit guard (check for incorrect configuration, or Pdu length capability over) */
                {
                    u1_Ret = (Bsw_CanTp_ReturnType)BSW_CANTP_E_OK;
                }
            }
        }
    }

    return u1_Ret;
}


/****************************************************************************/
/* Function Name | bsw_cantp_rx_VerifyCF                                    */
/* Description   | Verify of received message as CF                         */
/* Preconditions | None                                                     */
/* Parameters    | ptRxNSduCfgTbl    : Pointer to target RxNSdu config      */
/*               | ptTpPduInfo       : Pointer to target PDU information    */
/*               | ptReceiverStatTbl : Pointer to receiver status info      */
/* Return Value  | Bsw_CanTp_ReturnType                                     */
/*               |  BSW_CANTP_E_OK     : valid                              */
/*               |  BSW_CANTP_E_NOT_OK : invalid                            */
/* Notes         | None                                                     */
/****************************************************************************/
static Bsw_CanTp_ReturnType
bsw_cantp_rx_VerifyCF( BswConst Bsw_CanTp_RxNSduCfgType * ptRxNSduCfgTbl, BswConstR Bsw_CanTp_PduInfoType * ptTpPduInfo, Bsw_CanTp_st_ReceiverStatType * ptReceiverStatTbl )
{
    uint32                  u4_CanDl;                   /* CAN_DL                                */
    uint32                  u4_ReceiverRemainNSduLen;   /* Still unreceived NSdu data length     */
    uint8                   u1_RXDL;                    /* RX_DL                                 */
    uint8                   u1_NPDUFormatLen;           /* Length of NPDU without CAN FD padding */
    uint8                   u1_MaxCFNDataLen;           /* Maximum N_DATA Length in CF           */
    uint8                   u1_TaType;                  /* N_TAtype                              */
    uint8                   u1_PciOffset;               /* Offset to N_PCI address               */
    uint8                   u1_ReceivedSN;              /* Received Sequence number              */
    Bsw_CanTp_ReturnType    u1_LengthChk;               /* Length check result                   */
    Bsw_CanTp_ReturnType    u1_Ret;                     /* Return value                          */
    uint8                   u1_RxPaddingAct;            /* Rx Padding Action                     */
    uint8                   u1_AddressFormat;           /* Address Format                        */
#if( BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE )
    uint8                   u1_RxParamPtn;              /* Rx Parameter Pattern                  */
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */

    u1_Ret = (Bsw_CanTp_ReturnType)BSW_CANTP_E_NOT_OK;

    /*    Byte | #1            | #2    | #3    | ...    | */
    /*    Bit  | 7-4   | 3-0   |       |       | ...    | */
    /*---------+-------+-------+-------+-------+--------+ */
    /* CF      | 0010b | SN    | -               ...    | */

    /* N_TAtype check */
    u1_TaType = ptRxNSduCfgTbl->u1TaType;
    if( u1_TaType == (uint8)BSW_CANTP_PHYSICAL )    /* CANTP_CANFD_PHYSICAL is not necessary regardless CAN_FD or CAN2.0 */
    {
        u4_CanDl                 = ptTpPduInfo->u4SduLength;
        u4_ReceiverRemainNSduLen = ptReceiverStatTbl->u4ReceiverRemainNSduLen;
#if( BSW_CANTP_CFG_FDSUPPORT == BSW_USE )
        u1_RXDL                  = ptReceiverStatTbl->u1ReceiverRXDL;
#else /* BSW_CANTP_CFG_FDSUPPORT == BSW_NOUSE */
        u1_RXDL                  = BSW_CANTP_u1CAN_DL_08;
#endif /* BSW_CANTP_CFG_FDSUPPORT */
        u1_AddressFormat         = ptRxNSduCfgTbl->u1AddressFormat;
        u1_PciOffset             = bsw_cantp_cmn_u1PciOffSetTbl[u1_AddressFormat];
        u1_MaxCFNDataLen         = u1_RXDL - ( u1_PciOffset + BSW_CANTP_u1PCI_SIZE_CF );

        /* data length check */
        u1_LengthChk = (Bsw_CanTp_ReturnType)BSW_CANTP_E_NOT_OK;
        if( u4_ReceiverRemainNSduLen > (uint32)u1_MaxCFNDataLen )
        {   /* Other than last CF */
            if( u4_CanDl == (uint32)u1_RXDL )
            {   /* CAN_DL is valid */
                u1_LengthChk = (Bsw_CanTp_ReturnType)BSW_CANTP_E_OK;
            }
        }
        else
        {   /* last CF */
            u1_NPDUFormatLen = u1_PciOffset + BSW_CANTP_u1PCI_SIZE_CF + (uint8)u4_ReceiverRemainNSduLen;
            if( u4_CanDl <= (uint32)BSW_CANTP_u1CAN_DL_08 )
            {
                /* padding check */
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
                u1_RxPaddingAct = ptRxNSduCfgTbl->u1PaddingAct;
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
                u1_RxParamPtn = ptRxNSduCfgTbl->u1RxParamPtn;
                u1_RxPaddingAct = bsw_cantp_stRxNSduParamTbl[u1_RxParamPtn].u1PaddingAct;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
                if( u1_RxPaddingAct == (uint8)BSW_CANTP_ON )
                {   /* CAN frame data padding */
                    if( u4_CanDl == (uint32)BSW_CANTP_u1CAN_DL_08 )
                    {   /* CAN_DL is valid */
                        u1_LengthChk = (Bsw_CanTp_ReturnType)BSW_CANTP_E_OK;
                    }
                    else
                    {   /* padding error */
#if ( BSW_CANTP_CFG_DLCHKLCF_ERRACT == BSW_CANTP_ERRACT_ABORT )
                        /* aborting the reception session */
                        bsw_cantp_rx_TerminateRx( ptRxNSduCfgTbl, ptReceiverStatTbl, (Std_ReturnType)E_NOT_OK );
#else /* BSW_CANTP_CFG_DLCHKLCF_ERRACT == BSW_CANTP_ERRACT_IGNORE */
                        /* CF frame is ignored */
#endif /* BSW_CANTP_CFG_DLCHKLCF_ERRACT == BSW_CANTP_ERRACT_ABORT */
                    }
                }
                else
                {   /* CAN frame data optimization */
                    if( u4_CanDl >= (uint32)u1_NPDUFormatLen )
                    {   /* CAN_DL is valid */
                        u1_LengthChk = (Bsw_CanTp_ReturnType)BSW_CANTP_E_OK;
                    }
                }
            }
#if( BSW_CANTP_CFG_FDSUPPORT == BSW_USE )
            else
            {   /* CAN_DL > 8 */

                if( ( u4_CanDl >= (uint32)u1_NPDUFormatLen )    /* CAN frame length more than a necessary data length */
                &&  ( u4_CanDl <= (uint32)u1_RXDL ) )           /* Last CF's CAN_DL is shorter than RX_DL */
                {   /* CAN_DL is valid */

                    /*-------------------------------------------------------------*/
                    /* Note: The fact that CAN_DL is an appropriate value          */
                    /*       as CAN_FD presupposes that CanIf or less guarantees.  */
                    /*       This design, CanTp does not check it.                 */
                    /*       CAN_DL: 0-8 or 12 or 16 or 20 or 24 or 32 or 48 or 64 */
                    /*-------------------------------------------------------------*/
                    u1_LengthChk = (Bsw_CanTp_ReturnType)BSW_CANTP_E_OK;
                }
            }
#endif /* BSW_CANTP_CFG_FDSUPPORT == BSW_USE */
        }

        if( u1_LengthChk == (Bsw_CanTp_ReturnType)BSW_CANTP_E_OK )
        {
            /* SequenceNumber error handling */
            u1_ReceivedSN = ( ptTpPduInfo->ptSduData[u1_PciOffset] & BSW_CANTP_u1MASK_CF_SN );
            if( u1_ReceivedSN == ptReceiverStatTbl->u1ReceiverSN )
            {   /* SequenceNumber is valid */
                u1_Ret = (Bsw_CanTp_ReturnType)BSW_CANTP_E_OK;
            }
            else
            {   /* SequenceNumber is invalid */
                /* aborting the reception session */
                bsw_cantp_rx_TerminateRx( ptRxNSduCfgTbl, ptReceiverStatTbl, (Std_ReturnType)E_NOT_OK );
            }

        }
    }

    return u1_Ret;
}


/****************************************************************************/
/* Function Name | bsw_cantp_rx_MedInReceiver                               */
/* Description   | Execute mediation on Receiver status                     */
/* Preconditions | None                                                     */
/* Parameters    | ptCfgTbl          : Pointer to CanTp configuration       */
/*               | ptNewRxNSduCfgTbl : Pointer to new RxNSdu configuration  */
/* Return Value  | uint8                                                    */
/*               |  BSW_CANTP_RX_u1ACCEPT_NEW_SDU  : Accept New RxNSdu      */
/*               |  BSW_CANTP_RX_u1REJECT_NEW_SDU  : Reject New RxNSdu      */
/* Notes         | None                                                     */
/****************************************************************************/
static uint8
bsw_cantp_rx_MedInReceiver( BswConst Bsw_CanTp_CfgType * ptCfgTbl, BswConst Bsw_CanTp_RxNSduCfgType * ptNewRxNSduCfgTbl )
{
    BswConst Bsw_CanTp_RxNSduCfgType *    pt_CurRxNSduCfgTbl; /* Pointer to Current RxNSdu configuration */
    Bsw_CanTp_st_ReceiverStatType *       pt_ReceiverStatTbl; /* Pointer to receiver status info         */
    uint16                                u2_RxNSduId;        /* Target Rx NSdu-Id                       */
    uint16                                u2_ReceiverNSduId;  /* Receiver Processing NSdu-Id             */
    Bsw_CanTp_st_FSType                   u1_ReceiverFS;      /* Flow status                             */
    Bsw_CanTp_st_ProcStatType             u1_ReceiverStat;    /* Receiver processing status              */
    uint8                                 u1_Ret;             /* Return value                            */
    uint8                                 u1_CurPriority;     /* Current Priority                        */
    uint8                                 u1_NewPriority;     /* New Priority                            */
    uint16                                u2_CanIf_PduId;     /* CanIf PduId                             */


    u1_Ret             =  BSW_CANTP_RX_u1REJECT_NEW_SDU;

    pt_ReceiverStatTbl = &(bsw_cantp_st_stChStatTbl[ptNewRxNSduCfgTbl->u1ParentChId].stReceiverStatTbl);

    u1_ReceiverStat    = pt_ReceiverStatTbl->u1ReceiverStat;
    u1_ReceiverFS      = pt_ReceiverStatTbl->u1ReceiverFS;

    /* Check internal state */
    if( u1_ReceiverStat == BSW_CANTP_ST_u1STS_IDLE )
    {
        /* Idle */
        u1_Ret = BSW_CANTP_RX_u1ACCEPT_NEW_SDU;
    }
    else if( ( u1_ReceiverStat == BSW_CANTP_ST_u1STS_FC_WAIT )         /* Waiting for FC transmission */
         ||  ( u1_ReceiverStat == BSW_CANTP_ST_u1STS_CF_RX ) )         /* Waiting for CF RxIndication */
    {
        /* Receiving */
        u2_ReceiverNSduId = pt_ReceiverStatTbl->u2ReceiverNSduId;

        pt_CurRxNSduCfgTbl = bsw_cantp_cmn_GetRxNSduCfgTbl( ptCfgTbl, u2_ReceiverNSduId );
        if( pt_CurRxNSduCfgTbl != NULL_PTR )
        {
            /* Comparison of New NSduId(N_AI) and Current NSduId */
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
            u2_RxNSduId = ptNewRxNSduCfgTbl->u2NSduId;
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
            u2_RxNSduId = bsw_cantp_cmn_u2LatestRxNSduId;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
            if( u2_ReceiverNSduId == u2_RxNSduId )
            {   /* New N_AI == Current N_AI */

                /* Accept New RxNSdu */
                bsw_cantp_rx_TerminateRx( pt_CurRxNSduCfgTbl, pt_ReceiverStatTbl, (Std_ReturnType)E_NOT_OK );
                u1_Ret = BSW_CANTP_RX_u1ACCEPT_NEW_SDU;
            }
            else
            {   /* New N_AI != Current N_AI */

                /* N_AI Priority mediation by configuration */
                /* Compare priority (0:High <<<< n:Low) */
                u1_NewPriority = ptNewRxNSduCfgTbl->u1Priority;
                u1_CurPriority = pt_CurRxNSduCfgTbl->u1Priority;

                if( u1_NewPriority < u1_CurPriority )
                {   /* New msg's priority is higher than current reception */
                    /* Accept New RxNSdu */
                    bsw_cantp_rx_TerminateRx( pt_CurRxNSduCfgTbl, pt_ReceiverStatTbl, (Std_ReturnType)E_NOT_OK );
                    u1_Ret = BSW_CANTP_RX_u1ACCEPT_NEW_SDU;
                } /* The new msg's priority is less than or equal to msg that currently being reception */
                  /* Reject New RxNSdu */
            }
        }
        else
        {   /* u2ReceiverNSduId is broken */
            bsw_cantp_cmn_u1ErrState = BSW_CANTP_u1RAMERR;
            bsw_cantp_rx_ReceiverToIdle( pt_ReceiverStatTbl );
            u1_Ret = BSW_CANTP_RX_u1ACCEPT_NEW_SDU;
        }
    }
    else if( u1_ReceiverStat == BSW_CANTP_ST_u1STS_FC_TX )         /* Waiting for FC.CTS/WAIT TxConfirmation (FC and CF was interchanged in lower layer) */
    {
        /* Receiving */
        u2_ReceiverNSduId = pt_ReceiverStatTbl->u2ReceiverNSduId;

        pt_CurRxNSduCfgTbl = bsw_cantp_cmn_GetRxNSduCfgTbl( ptCfgTbl, u2_ReceiverNSduId );
        if( pt_CurRxNSduCfgTbl != NULL_PTR )
        {

            u2_CanIf_PduId = pt_CurRxNSduCfgTbl->u2CanIf_FcPduId;

            if( ( u1_ReceiverFS == BSW_CANTP_u1FS_RECEIVER_CTS )
            ||  ( u1_ReceiverFS == BSW_CANTP_u1FS_RECEIVER_WT  ) )
            {
                /* Receiving */
                u2_ReceiverNSduId = pt_ReceiverStatTbl->u2ReceiverNSduId;

                /* Comparison of New NSduId(N_AI) and Current NSduId */
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
                u2_RxNSduId = ptNewRxNSduCfgTbl->u2NSduId;
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
                u2_RxNSduId = bsw_cantp_cmn_u2LatestRxNSduId;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
                if( u2_ReceiverNSduId == u2_RxNSduId )
                {   /* New N_AI == Current N_AI */

                    /* Abort current transmission */
                    bsw_cantp_snd_AbortSend( u2_CanIf_PduId );

                    /* Accept New RxNSdu */
                    bsw_cantp_rx_TerminateRx( pt_CurRxNSduCfgTbl, pt_ReceiverStatTbl, (Std_ReturnType)E_NOT_OK );
                    u1_Ret = BSW_CANTP_RX_u1ACCEPT_NEW_SDU;
                }
                else
                {   /* New N_AI != Current N_AI */

                    /* N_AI Priority mediation by configuration */
                    /* Compare priority (0:High <<<< n:Low) */
                    u1_NewPriority = ptNewRxNSduCfgTbl->u1Priority;
                    u1_CurPriority = pt_CurRxNSduCfgTbl->u1Priority;

                    if( u1_NewPriority < u1_CurPriority )
                    {   /* New msg's priority is higher than current reception */

                        /* Abort current transmission */
                        bsw_cantp_snd_AbortSend( u2_CanIf_PduId );

                        /* Accept New RxNSdu */
                        bsw_cantp_rx_TerminateRx( pt_CurRxNSduCfgTbl, pt_ReceiverStatTbl, (Std_ReturnType)E_NOT_OK );
                        u1_Ret = BSW_CANTP_RX_u1ACCEPT_NEW_SDU;
                    } /* The new msg's priority is less than or equal to msg that currently being reception */
                      /* Reject New RxNSdu */
                }
            }
            else if( u1_ReceiverFS == BSW_CANTP_u1FS_RECEIVER_OVFL )
            {
                /* Waiting for FC.OVFLW */
                /* Abort current transmission */
                bsw_cantp_snd_AbortSend( u2_CanIf_PduId );

                bsw_cantp_rx_ReceiverToIdle( pt_ReceiverStatTbl );
                u1_Ret = BSW_CANTP_RX_u1ACCEPT_NEW_SDU;
            }
            else
            {
                /* u1_ReceiverFS is broken */
                bsw_cantp_cmn_u1ErrState = BSW_CANTP_u1RAMERR;
                bsw_cantp_rx_ReceiverToIdle( pt_ReceiverStatTbl );
                u1_Ret = BSW_CANTP_RX_u1ACCEPT_NEW_SDU;
            }
        }
        else
        {   /* u2ReceiverNSduId is broken */
            bsw_cantp_cmn_u1ErrState = BSW_CANTP_u1RAMERR;
            bsw_cantp_rx_ReceiverToIdle( pt_ReceiverStatTbl );
            u1_Ret = BSW_CANTP_RX_u1ACCEPT_NEW_SDU;
        }
    }
    else
    {
        /* Other state */
        /* - u1_ReceiverStat is broken  */
        bsw_cantp_cmn_u1ErrState = BSW_CANTP_u1RAMERR;
        bsw_cantp_rx_ReceiverToIdle( pt_ReceiverStatTbl );
        u1_Ret = BSW_CANTP_RX_u1ACCEPT_NEW_SDU;
    }

    return u1_Ret;
}


/****************************************************************************/
/* Function Name | bsw_cantp_rx_MedInSender                                 */
/* Description   | Execute mediation on Sender status                       */
/* Preconditions | None                                                     */
/* Parameters    | ptCfgTbl          : Pointer to CanTp configuration       */
/*               | ptNewRxNSduCfgTbl : Pointer to new RxNSdu configuration  */
/* Return Value  | uint8                                                    */
/*               |  BSW_CANTP_RX_u1ACCEPT_NEW_SDU  : Accept New RxNSdu      */
/*               |  BSW_CANTP_RX_u1REJECT_NEW_SDU  : Reject New RxNSdu      */
/* Notes         | None                                                     */
/****************************************************************************/
static uint8
bsw_cantp_rx_MedInSender( BswConst Bsw_CanTp_CfgType * ptCfgTbl, BswConst Bsw_CanTp_RxNSduCfgType * ptNewRxNSduCfgTbl )
{
    BswConst Bsw_CanTp_TxNSduCfgType *  pt_CurTxNSduCfgTbl;     /* Pointer to TxNSdu configuration    */
    Bsw_CanTp_st_SenderStatType      *  pt_SenderStatTbl;       /* Pointer to sender status info      */
    Bsw_CanTp_st_ProcStatType           u1_SenderStat;          /* Sender Processing Status           */
    uint8                               u1_Ret;                 /* Return value                       */
    uint8                               u1_NewMsgRxInLastMsgTx; /* New Msg Rx Handling In Last Msg Tx */
    uint8                               u1_CurPriority;         /* Current Priority                   */
    uint8                               u1_NewPriority;         /* New Priority                       */
    uint16                              u2_CanIf_PduId;         /* CanIf PduId                        */

    u1_Ret             = BSW_CANTP_RX_u1REJECT_NEW_SDU;

    pt_SenderStatTbl   = &(bsw_cantp_st_stChStatTbl[ptNewRxNSduCfgTbl->u1ParentChId].stSenderStatTbl);

    pt_CurTxNSduCfgTbl = bsw_cantp_cmn_GetTxNSduCfgTbl( ptCfgTbl, pt_SenderStatTbl->u2SenderNSduId );
    if( pt_CurTxNSduCfgTbl != NULL_PTR )
    {
        u1_NewPriority = ptNewRxNSduCfgTbl->u1Priority;
        u1_CurPriority = pt_CurTxNSduCfgTbl->u1Priority;
        u2_CanIf_PduId = pt_CurTxNSduCfgTbl->u2CanIf_PduId;

        /* Check internal state */
        u1_SenderStat = pt_SenderStatTbl->u1SenderStat;
        if( ( u1_SenderStat == BSW_CANTP_ST_u1STS_SF_TX )
        ||  ( ( u1_SenderStat == BSW_CANTP_ST_u1STS_CF_TX ) && ( pt_SenderStatTbl->u4SenderRemainNSduLen == 0UL ) ) )
        {
            /* Sending(1) */
            /* - Waiting for last frame's(SF or last CF) TxConfirmation */

            /* Check configuration for handling of last frame's TxConfirmation */
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
            u1_NewMsgRxInLastMsgTx = pt_CurTxNSduCfgTbl->u1NewMsgRxInLastMsgTx;
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
            u1_NewMsgRxInLastMsgTx = bsw_cantp_u1UnexpectedRxFunc;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
            if( u1_NewMsgRxInLastMsgTx == (uint8)BSW_CANTP_TX_INCOMPLETE )
            {   /* 1.Follow protocol specifications and the priority mediation */

                /* N_AI Priority mediation by configuration */
                /* Compare priority (0:High <<<< n:Low) */
                if( u1_NewPriority < u1_CurPriority )
                {   /* New msg's priority is higher than current transmission */

                    /* Abort current transmission */
                    bsw_cantp_snd_AbortSend( u2_CanIf_PduId );

                    bsw_cantp_tx_TerminateTx( pt_CurTxNSduCfgTbl, pt_SenderStatTbl, (Std_ReturnType)E_NOT_OK );
                    u1_Ret = BSW_CANTP_RX_u1ACCEPT_NEW_SDU;
                } /* The new msg's priority is less than or equal to msg that currently being sent. */
                  /* Reject New RxNSdu */
            }
            else if( u1_NewMsgRxInLastMsgTx == (uint8)BSW_CANTP_TX_REGARD_OK )
            {   /* 2.Regard currently transmission as success */

                /* When REGARD_OK, CanTp should not call CanIf_CancelTransmit */

                bsw_cantp_tx_TerminateTx( pt_CurTxNSduCfgTbl, pt_SenderStatTbl, (Std_ReturnType)E_OK );
                u1_Ret = BSW_CANTP_RX_u1ACCEPT_NEW_SDU;
            }
            else
            {   /* 3.Regard currently transmission as failure */

                /* Abort current transmission */
                bsw_cantp_snd_AbortSend( u2_CanIf_PduId );

                bsw_cantp_tx_TerminateTx( pt_CurTxNSduCfgTbl, pt_SenderStatTbl, (Std_ReturnType)E_NOT_OK );
                u1_Ret = BSW_CANTP_RX_u1ACCEPT_NEW_SDU;
            }

        }
        else if( ( u1_SenderStat == BSW_CANTP_ST_u1STS_FF_TX )
             ||  ( u1_SenderStat == BSW_CANTP_ST_u1STS_CF_TX ) )     /* in this block, pt_SenderStatTbl->SenderRemainNSduLen is greater than zero. */
        {
            /* Sending(2) */

            /* N_AI Priority mediation by configuration */
            /* Compare priority (0:High <<<< n:Low) */
            if( u1_NewPriority < u1_CurPriority )
            {   /* New msg's priority is higher than current transmission */
                bsw_cantp_snd_AbortSend( u2_CanIf_PduId );

                bsw_cantp_tx_TerminateTx( pt_CurTxNSduCfgTbl, pt_SenderStatTbl, (Std_ReturnType)E_NOT_OK );
                u1_Ret = BSW_CANTP_RX_u1ACCEPT_NEW_SDU;
            } /* The new msg's priority is less than or equal to msg that currently being sent. */
              /* Reject New RxNSdu */
        }
        else if( ( u1_SenderStat == BSW_CANTP_ST_u1STS_TX_WAIT )
             ||  ( u1_SenderStat == BSW_CANTP_ST_u1STS_FC_RX )
             ||  ( u1_SenderStat == BSW_CANTP_ST_u1STS_CF_WAIT_CS )
             ||  ( u1_SenderStat == BSW_CANTP_ST_u1STS_CF_WIT_STMIN ) )
        {
            /* Sending(3) */

            /* N_AI Priority mediation by configuration */
            /* Compare priority (0:High <<<< n:Low) */
            if( u1_NewPriority < u1_CurPriority )
            {   /* New msg's priority is higher than current transmission */
                bsw_cantp_tx_TerminateTx( pt_CurTxNSduCfgTbl, pt_SenderStatTbl, (Std_ReturnType)E_NOT_OK );
                u1_Ret = BSW_CANTP_RX_u1ACCEPT_NEW_SDU;
            } /* The new msg's priority is less than or equal to msg that currently being sent. */
              /* Reject New RxNSdu */
        }
        else
        {
            /* Other state */
            /* - u1_SenderStat is broken */
            bsw_cantp_cmn_u1ErrState = BSW_CANTP_u1RAMERR;
            bsw_cantp_tx_SenderToIdle( pt_SenderStatTbl );
            u1_Ret = BSW_CANTP_RX_u1ACCEPT_NEW_SDU;
        }
    }
    else
    {   /* u2SenderNSduId is broken */
        bsw_cantp_cmn_u1ErrState = BSW_CANTP_u1RAMERR;
        bsw_cantp_tx_SenderToIdle( pt_SenderStatTbl );
        u1_Ret = BSW_CANTP_RX_u1ACCEPT_NEW_SDU;
    }

    return u1_Ret;
}


/****************************************************************************/
/* Function Name | bsw_cantp_rx_ReceiveSF                                   */
/* Description   | Receive SF N_PDU                                         */
/* Preconditions | None                                                     */
/* Parameters    | ptRxNSduCfgTbl : Pointer to RxNSdu configuration         */
/*               | ptTpPduInfo    : Pointer to PDU information              */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static void
bsw_cantp_rx_ReceiveSF( BswConst Bsw_CanTp_RxNSduCfgType * ptRxNSduCfgTbl, BswConstR Bsw_CanTp_PduInfoType * ptTpPduInfo )
{
    PduInfoType         st_PduInfo;             /* Receive data                            */
    PduLengthType       UpperLayerBufSize;      /* Upper layer buffer size                 */
    PduIdType           PduR_RxIndId;           /* PDU ID for informing upper layer        */
    uint8               u1_PciOffset;           /* Offset to N_PCI address                 */
    BufReq_ReturnType   u1_BufRet;              /* Result of upper layer buffer securement */
    Std_ReturnType      u1_RxIndRet;            /* Result of receiving SF                  */
    uint8               u1_SFDL;                /* SF_DL                                   */
    uint8               u1_SFPciSize;           /* Size of SF's NPCI                       */
    uint8               u1_AddressFormat;       /* Address Format                          */

    u1_AddressFormat = ptRxNSduCfgTbl->u1AddressFormat;
    u1_PciOffset = bsw_cantp_cmn_u1PciOffSetTbl[u1_AddressFormat];

#if( BSW_CANTP_CFG_FDSUPPORT == BSW_USE )
    if( ptTpPduInfo->ptSduData[u1_PciOffset] == BSW_CANTP_u1PCI_FIRSTBYTE_SF_ES )
    {   /* SF(CAN_DL>8) */
        u1_SFDL      = ptTpPduInfo->ptSduData[u1_PciOffset + (uint8)BSW_CANTP_OFFSET1];
        u1_SFPciSize = BSW_CANTP_u1PCI_SIZE_SF_ES;
    }
    else
#endif /* BSW_CANTP_CFG_FDSUPPORT == BSW_USE */
    {   /* SF(CAN_DL<=8) */
        u1_SFDL      = ptTpPduInfo->ptSduData[u1_PciOffset] & BSW_CANTP_u1MASK_SF_SFDL;
        u1_SFPciSize = BSW_CANTP_u1PCI_SIZE_SF;
    }

    /* Make data for PduR_StartOfReception/CopyRxData */
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
    PduR_RxIndId             = (PduIdType)ptRxNSduCfgTbl->u2PduR_RxIndId;
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
    PduR_RxIndId             = (PduIdType)bsw_cantp_cmn_u2LatestRxNSduId;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
    st_PduInfo.SduLength     = (PduLengthType)u1_SFDL;
    st_PduInfo.SduDataPtr    = &(ptTpPduInfo->ptSduData[u1_PciOffset + u1_SFPciSize]);
    st_PduInfo.MetaDataPtr   = (BswU1*)NULL_PTR;
    UpperLayerBufSize        = (PduLengthType)0UL;

    u1_BufRet = PduR_CanTpStartOfReception( PduR_RxIndId, &st_PduInfo, (PduLengthType)u1_SFDL, &UpperLayerBufSize );
    if( u1_BufRet == (BufReq_ReturnType)BUFREQ_OK )
    {
        u1_RxIndRet = (Std_ReturnType)E_NOT_OK;
        if( UpperLayerBufSize >= (PduLengthType)u1_SFDL )
        {
            u1_BufRet = PduR_CanTpCopyRxData( PduR_RxIndId, &st_PduInfo, &UpperLayerBufSize );
            if( u1_BufRet == (BufReq_ReturnType)BUFREQ_OK )
            {
                /* Single frame reception is successfully finished */
                u1_RxIndRet = (Std_ReturnType)E_OK;
            }
        }
        PduR_CanTpRxIndication( PduR_RxIndId, u1_RxIndRet );
    } /* SOR:BUFREQ_E_OVFL, BUFREQ_E_NOT_OK, and unknown return code : NOP */

    return;
}


/****************************************************************************/
/* Function Name | bsw_cantp_rx_ReceiveFF                                   */
/* Description   | Receive SF N_PDU                                         */
/* Preconditions | None                                                     */
/* Parameters    | ptRxNSduCfgTbl    : Pointer to RxNSdu configuration      */
/*               | ptTpPduInfo       : Pointer to PDU information           */
/*               | ptReceiverStatTbl : Pointer to receiver status info      */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static void
bsw_cantp_rx_ReceiveFF( BswConst Bsw_CanTp_RxNSduCfgType * ptRxNSduCfgTbl, BswConstR Bsw_CanTp_PduInfoType * ptTpPduInfo, Bsw_CanTp_st_ReceiverStatType * ptReceiverStatTbl )
{
    PduInfoType         st_PduInfo;             /* Receive data                            */
    uint32              u4_FFDL;                /* FF_DL                                   */
    PduLengthType       UpperLayerBufSize;      /* Upper layer buffer size                 */
    PduIdType           PduR_RxIndId;           /* PDU ID for informing upper layer        */
    uint16              u2_RxNSduId;            /* Target Rx NSdu-Id                       */
    uint16              u2_WFTMax;              /* WFt Max                                 */
#if( BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE )
    uint8               u1_RxParamPtn;          /* Rx Parameter Pattern                    */
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
    uint8               u1_RXDL;                /* RX_DL                                   */
    uint8               u1_PciOffset;           /* Offset to N_PCI address                 */
    BufReq_ReturnType   u1_BufRet;              /* Result of upper layer buffer securement */
    uint8               u1_FFPciSize;           /* Size of SF's NPCI                       */
    uint8               u1_FFNDataLen;          /* N_DATA Length in FF                     */
    uint8               u1_AddressFormat;       /* Address Format                          */

    /* Save RXDL */
    u1_RXDL                           = (uint8)ptTpPduInfo->u4SduLength;
    ptReceiverStatTbl->u1ReceiverRXDL = u1_RXDL;

    /* Next state : Waiting for FC Transmission (in N_Br time) */
    ptReceiverStatTbl->u1ReceiverStat      = BSW_CANTP_ST_u1STS_FC_WAIT;
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
    u2_WFTMax = ptRxNSduCfgTbl->u2WFTMax;
    u2_RxNSduId = ptRxNSduCfgTbl->u2NSduId;
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
    u1_RxParamPtn = ptRxNSduCfgTbl->u1RxParamPtn;
    u2_WFTMax = bsw_cantp_stRxNSduParamTbl[u1_RxParamPtn].u2WFTMax;
    u2_RxNSduId = bsw_cantp_cmn_u2LatestRxNSduId;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
    if( u2_WFTMax == (uint16)0U )
    {
        ptReceiverStatTbl->u2ReceiverCycle = bsw_cantp_u2FcTxTimeout + BSW_CANTP_u2MAIN_CYCLE_DOUBLE;
    }
    else
    {
        ptReceiverStatTbl->u2ReceiverCycle = bsw_cantp_u2FcWaitTxPeriodTime;
    }
    ptReceiverStatTbl->u2ReceiverNSduId    = u2_RxNSduId;
    ptReceiverStatTbl->u1ReceiverSN        = BSW_CANTP_u1SN_FIRST;
    ptReceiverStatTbl->u2ReceiverFCWaitCnt = (uint16)0U;
    ptReceiverStatTbl->u1ReceiverFS        = BSW_CANTP_u1FS_RECEIVER_WT;

    /* Calculation of FF_DL */
    u1_AddressFormat = ptRxNSduCfgTbl->u1AddressFormat;
    u1_PciOffset = bsw_cantp_cmn_u1PciOffSetTbl[u1_AddressFormat];

#if( BSW_CANTP_CFG_MAXPDULENGTH > BSW_CANTP_u4FFDL_4095 )
    if( ( ptTpPduInfo->ptSduData[u1_PciOffset]                         == BSW_CANTP_u1PCI_FIRSTBYTE_FF_ES )
    &&   ( ptTpPduInfo->ptSduData[u1_PciOffset + (uint8)BSW_CANTP_OFFSET1] == BSW_CANTP_u1PCI_SECNDBYTE_FF_ES ) )
    {   /* FF(FF_DL > 4095) */
        u4_FFDL  = (uint32)(ptTpPduInfo->ptSduData[u1_PciOffset + (uint8)BSW_CANTP_OFFSET2]) << BSW_CANTP_BIT_SHIFT24;
        u4_FFDL |= (uint32)(ptTpPduInfo->ptSduData[u1_PciOffset + (uint8)BSW_CANTP_OFFSET3]) << BSW_CANTP_BIT_SHIFT16;
        u4_FFDL |= (uint32)(ptTpPduInfo->ptSduData[u1_PciOffset + (uint8)BSW_CANTP_OFFSET4]) << BSW_CANTP_BIT_SHIFT8;
        u4_FFDL |= (uint32)(ptTpPduInfo->ptSduData[u1_PciOffset + (uint8)BSW_CANTP_OFFSET5]);

        u1_FFPciSize = BSW_CANTP_u1PCI_SIZE_FF_ES;
    }
    else
#endif /* BSW_CANTP_CFG_MAXPDULENGTH > BSW_CANTP_u4FFDL_4095 */
    {   /* FF(FF_DL <= 4095) */
        u4_FFDL  = ((uint32)(ptTpPduInfo->ptSduData[u1_PciOffset]) & (uint32)BSW_CANTP_u1MASK_FF_FFDL_H) << BSW_CANTP_BIT_SHIFT8;
        u4_FFDL |= (uint32)(ptTpPduInfo->ptSduData[u1_PciOffset + (uint8)BSW_CANTP_OFFSET1]);

        u1_FFPciSize = BSW_CANTP_u1PCI_SIZE_FF;
    }

    /* Calculation of N_Data length in FF */
    u1_FFNDataLen = u1_RXDL - ( u1_PciOffset + u1_FFPciSize );

    /* Save remain received data length */
    ptReceiverStatTbl->u4ReceiverRemainNSduLen = u4_FFDL - (uint32)u1_FFNDataLen;

    /* Make data for PduR_StartOfReception/CopyRxData */
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
    PduR_RxIndId             = (PduIdType)ptRxNSduCfgTbl->u2PduR_RxIndId;
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
    PduR_RxIndId             = (PduIdType)u2_RxNSduId;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
    st_PduInfo.SduLength     = (PduLengthType)u1_FFNDataLen;
    st_PduInfo.SduDataPtr    = &(ptTpPduInfo->ptSduData[u1_PciOffset + u1_FFPciSize]);
    st_PduInfo.MetaDataPtr   = (BswU1*)NULL_PTR;
    UpperLayerBufSize        = (PduLengthType)0UL;

    u1_BufRet = PduR_CanTpStartOfReception( PduR_RxIndId, &st_PduInfo, (PduLengthType)u4_FFDL, &UpperLayerBufSize );

    if( u1_BufRet == (BufReq_ReturnType)BUFREQ_OK )
    {   /* PduR has buffer */

        if( UpperLayerBufSize < (PduLengthType)u1_FFNDataLen )
        {   /* PduR has buffer, but, Buffer are not enough for an FF reception */
            bsw_cantp_rx_TerminateRx( ptRxNSduCfgTbl, ptReceiverStatTbl, (Std_ReturnType)E_NOT_OK );
        }
        else
        {
            /* Copy data */
            u1_BufRet = PduR_CanTpCopyRxData( PduR_RxIndId, &st_PduInfo, &UpperLayerBufSize );

            if( u1_BufRet != (BufReq_ReturnType)BUFREQ_OK )
            {   /* Copy failed */
                bsw_cantp_rx_TerminateRx( ptRxNSduCfgTbl, ptReceiverStatTbl, (Std_ReturnType)E_NOT_OK );
            }
        }
    }
    else if( u1_BufRet == (BufReq_ReturnType)BUFREQ_E_OVFL )
    {   /* PduR doesn't have buffer */
        /* CanTp sends FC.OVFLW in next MainFunction */
        ptReceiverStatTbl->u1ReceiverFS = BSW_CANTP_u1FS_RECEIVER_OVFL;
    }
    else
    {   /* SOR:NOT_OK, or unknown return value */
        bsw_cantp_rx_ReceiverToIdle( ptReceiverStatTbl );
    }

    return;
}


/****************************************************************************/
/* Function Name | bsw_cantp_rx_ReceiveCF                                   */
/* Description   | Receive CF N_PDU                                         */
/* Preconditions | None                                                     */
/* Parameters    | ptCfgTbl          : Pointer to CanTp configuration       */
/*               | ptRxNSduCfgTbl    : Pointer to RxNSdu configuration      */
/*               | ptTpPduInfo       : Pointer to PDU information           */
/*               | ptReceiverStatTbl : Pointer to receiver status info      */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static void
bsw_cantp_rx_ReceiveCF( BswConst Bsw_CanTp_CfgType * ptCfgTbl, BswConst Bsw_CanTp_RxNSduCfgType * ptRxNSduCfgTbl, BswConstR Bsw_CanTp_PduInfoType * ptTpPduInfo, Bsw_CanTp_st_ReceiverStatType * ptReceiverStatTbl )
{
    PduInfoType         st_PduInfo;                 /* Receive data                            */
    uint32              u4_ReceiverRemainNSduLen;   /* Still unreceived data length            */
    PduLengthType       UpperLayerBufSize;          /* Upper layer buffer size                 */
    PduIdType           PduR_RxIndId;               /* PDU ID for informing upper layer        */
    uint16              u2_BS;                      /* Block size                              */
    uint16              u2_NcrCycle;                /* N_cr Cycle                              */
    uint16              u2_WFTMax;                  /* WFt Max                                 */
#if( BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE )
    uint16              u2_RxNSduIdx;               /* Index of RxNSdus                        */
    uint8               u1_RxParamPtn;              /* Rx Parameter Pattern                    */
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
    BufReq_ReturnType   u1_BufRet;                  /* Result of upper layer buffer securement */
    uint8               u1_NextSN;                  /* Next Sequence Number                    */
    uint8               u1_ReceiverCFNum;           /* CF Number before receiving              */
    uint8               u1_PciOffset;               /* Offset to N_PCI address                 */
    uint8               u1_NDataOffset;             /* Offset to N_DATA address                */
    uint8               u1_NDataLen;                /* Length of N_DATA                        */
    uint8               u1_MaxCFNDataLen;           /* Maximum N_DATA Length in CF             */
    uint8               u1_AddressFormat;           /* Address Format                          */

    u1_AddressFormat         = ptRxNSduCfgTbl->u1AddressFormat;
    u1_PciOffset             = bsw_cantp_cmn_u1PciOffSetTbl[u1_AddressFormat];
    u1_NDataOffset           = u1_PciOffset + BSW_CANTP_u1PCI_SIZE_CF;

    /* Calculation of N_Data length in mid CF */
    u1_MaxCFNDataLen         = (uint8)(ptTpPduInfo->u4SduLength) - u1_NDataOffset;
    u4_ReceiverRemainNSduLen = ptReceiverStatTbl->u4ReceiverRemainNSduLen;
    u1_NDataLen              = (uint8)u4_ReceiverRemainNSduLen;

#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
    PduR_RxIndId             = (PduIdType)ptRxNSduCfgTbl->u2PduR_RxIndId;
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
    PduR_RxIndId             = (PduIdType)bsw_cantp_cmn_u2LatestRxNSduId;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */

    /* CF pattern check         */
    /* - mid CF                 */
    /* - last CF of a block     */
    /* - last CF of the message */
    if( u4_ReceiverRemainNSduLen > (uint32)u1_MaxCFNDataLen )
    {   /* mid CF or last CF of a block */

        /* Calculation of received N_Data length */
        u1_NDataLen = u1_MaxCFNDataLen;

        /* Calculation of sequence number of Next CF */
        u1_NextSN  = ptTpPduInfo->ptSduData[u1_PciOffset] & BSW_CANTP_u1MASK_CF_SN;
        u1_NextSN++;
        ptReceiverStatTbl->u1ReceiverSN = u1_NextSN & BSW_CANTP_u1MASK_CF_SN;

        /* Calculation of the number of CF which Receiver has not yet received */
        /* Note: If BS=0 then u1ReceiverCFNum is 0 always */
        u1_ReceiverCFNum = ptReceiverStatTbl->u1ReceiverCFNum;
        if( u1_ReceiverCFNum > (uint8)0U )
        {
            u1_ReceiverCFNum--;
        }

        /* Judgement of Next state by CF pattern */
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
        u2_BS = bsw_cantp_rx_ReadParamBS( ptRxNSduCfgTbl );
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
        u2_RxNSduIdx = (uint16)PduR_RxIndId - ptCfgTbl->u2MinRxNSduId;
        u1_RxParamPtn = ptRxNSduCfgTbl->u1RxParamPtn;
        u2_BS        = bsw_cantp_rx_ReadParamBSByIdx( u2_RxNSduIdx, u1_RxParamPtn );
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
        if( ( u2_BS            == (uint16)0U )
        ||  ( u1_ReceiverCFNum >  (uint8)0U ) )
        {   /* mid CF */
            /* Next state : Waiting for CF RxIndication */
            ptReceiverStatTbl->u1ReceiverStat  = BSW_CANTP_ST_u1STS_CF_RX;
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
            u2_NcrCycle = ptRxNSduCfgTbl->u2NcrCycle;
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
            u2_NcrCycle = bsw_cantp_stRxNSduParamTbl[u1_RxParamPtn].u2NcrCycle;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
            ptReceiverStatTbl->u2ReceiverCycle = u2_NcrCycle + BSW_CANTP_u2MAIN_CYCLE_DOUBLE;
        }
        else
        {   /* last CF of a block */
            /* Next state : Waiting for FC Transmission (in N_Br time) */
            ptReceiverStatTbl->u1ReceiverStat  = BSW_CANTP_ST_u1STS_FC_WAIT;
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
            u2_WFTMax = ptRxNSduCfgTbl->u2WFTMax;
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
            u2_WFTMax = bsw_cantp_stRxNSduParamTbl[u1_RxParamPtn].u2WFTMax;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
            if( u2_WFTMax == (uint16)0U )
            {
                ptReceiverStatTbl->u2ReceiverCycle = bsw_cantp_u2FcTxTimeout + BSW_CANTP_u2MAIN_CYCLE_DOUBLE;
            }
            else
            {
                ptReceiverStatTbl->u2ReceiverCycle = bsw_cantp_u2FcWaitTxPeriodTime;
            }
            ptReceiverStatTbl->u1ReceiverFS    = BSW_CANTP_u1FS_RECEIVER_WT;
        }

        ptReceiverStatTbl->u1ReceiverCFNum = u1_ReceiverCFNum;
    }
    /* Calculation of data length which Receiver has not yet received */
    u4_ReceiverRemainNSduLen                   = u4_ReceiverRemainNSduLen - (uint32)u1_NDataLen;
    ptReceiverStatTbl->u4ReceiverRemainNSduLen = u4_ReceiverRemainNSduLen;

    /* Make data for CopyRxData */
    st_PduInfo.SduLength     = (PduLengthType)u1_NDataLen;
    st_PduInfo.SduDataPtr    = &(ptTpPduInfo->ptSduData[u1_NDataOffset]);
    st_PduInfo.MetaDataPtr   = (BswU1*)NULL_PTR;
    UpperLayerBufSize        = (PduLengthType)0UL;

    /* Copy data */
    u1_BufRet = PduR_CanTpCopyRxData( PduR_RxIndId, &st_PduInfo, &UpperLayerBufSize );

    if( u1_BufRet == (BufReq_ReturnType)BUFREQ_OK )
    {   /* Copy success */

        if( u4_ReceiverRemainNSduLen == 0UL )
        {   /* last CF of the message */

            /* Multi frame reception is successfully finished */
            bsw_cantp_rx_TerminateRx( ptRxNSduCfgTbl, ptReceiverStatTbl, (Std_ReturnType)E_OK );
        }
    }
    else
    {   /* Copy failed */
        bsw_cantp_rx_TerminateRx( ptRxNSduCfgTbl, ptReceiverStatTbl, (Std_ReturnType)E_NOT_OK );
    }

    return;
}


/****************************************************************************/
/* Function Name | bsw_cantp_rx_JudgeFS                                     */
/* Description   | Judgement for FC status and BS value                     */
/* Preconditions | None                                                     */
/* Parameters    | u4RemainNSduLen      ; Still unreceived NSdu data length */
/*               | u4UpperLayerBufSize  : Upper layer buffer size           */
/*               | u1MaxCFNDataLen      : Maximum N_DATA Length in CF       */
/*               | u1BS                 : Block Size                        */
/* Return Value  | Bsw_CanTp_st_FSType                                      */
/*               |  BSW_CANTP_u1FS_RECEIVER_WT  : Wait(WAIT)                */
/*               |  BSW_CANTP_u1FS_RECEIVER_CTS : ContinueToSend(CTS)       */
/* Notes         | None                                                     */
/****************************************************************************/
static Bsw_CanTp_st_FSType
bsw_cantp_rx_JudgeFS( uint32 u4RemainNSduLen, uint32 u4UpperLayerBufSize, uint8 u1MaxCFNDataLen, uint8 u1BS )
{
    uint32                 u4_ReqBufSize;          /* Required buffer size for the next block reception */
    uint16                 u2_BlockNDataSizeMax;   /* Sum of N_DATA size in a mid block                 */
    Bsw_CanTp_st_FSType    u1_Ret;                 /* Return value                                      */

    u1_Ret = BSW_CANTP_u1FS_RECEIVER_WT;

    /* Requested buffer size (for the last block) */
    u4_ReqBufSize = u4RemainNSduLen;

    if( u1BS != (uint8)0U )
    {
        /* [CF's N_DATA size] * [Block size] */
        u2_BlockNDataSizeMax = bsw_cantp_rx_GetBlockNDataSize( u1MaxCFNDataLen, u1BS );

        if( u4_ReqBufSize > (uint32)u2_BlockNDataSizeMax )
        {   /* Next Block is a mid block */

            /* Requested buffer size (for a mid block) */
            u4_ReqBufSize = (uint32)u2_BlockNDataSizeMax;
        }
    }

    if( u4UpperLayerBufSize >= u4_ReqBufSize )
    {   /* Upper layer has enough buffers. */
        u1_Ret = BSW_CANTP_u1FS_RECEIVER_CTS;
    }

    return u1_Ret;
}


/****************************************************************************/
/* Function Name | bsw_cantp_rx_GetBlockNDataSize                           */
/* Description   | Calculate N_Data size of a block                         */
/* Preconditions | None                                                     */
/* Parameters    | u1CFNDataLen : a CF N_Data size                          */
/*               | u1BS         : Block Size                                */
/* Return Value  | uint16       : N_Data size of a block                    */
/* Notes         | None                                                     */
/****************************************************************************/
static uint16
bsw_cantp_rx_GetBlockNDataSize( uint8 u1CFNDataLen, uint8 u1BS )
{
    uint16  u2_Ret;         /* Return value */
    uint8   u1_Loop;        /* Loop counter */
    uint8   u1_ShiftVal;    /* Shift value  */

    u2_Ret = (uint16)0U;

    /* This function returns multiplication result of argument 1 and argument 2 */
    /* argument 1: MAX 64, argument 2 : MAX 255, reusult : 6320(0x3FC0) in U2   */
    for( u1_Loop = (uint8)0U; u1_Loop < (uint8)BSW_CANTP_BITNUM_U1; u1_Loop++ )
    {
        u1_ShiftVal = (uint8)((uint8)BSW_CANTP_BIT0 << u1_Loop);
        if( ( u1BS & u1_ShiftVal ) != (uint8)0U )
        {
            u2_Ret += (uint16)((uint16)u1CFNDataLen << u1_Loop);
        }
    }

    return u2_Ret;
}


/****************************************************************************/
/* Function Name | bsw_cantp_rx_SendFCCtrl                                  */
/* Description   | Scheduled Receive Procedure on FC_WAIT_TX                */
/* Preconditions | None                                                     */
/* Parameters    | ptCfgTbl          : Pointer to CanTp configuration       */
/*               | ptRxNSduCfgTbl    : Pointer to RxNSdu configuration      */
/*               | ptReceiverStatTbl : Pointer to receiver status info      */
/* Return Value  | None                                                     */
/* Notes         | IMPORTANT NOTICE                                         */
/*               |                                                          */
/*               | In R5.0 v1.0 CanTp (Initial development of CanTp),       */
/*               | this API called from CanTp_MainFunction assumed that     */
/*               | the following APIs INTERRUPTED.                          */
/*               |   - CanTp_TxConfirmation                                 */
/*               |   - CanTp_RxIndication                                   */
/*               |   - CanTp_CancelReceive                                  */
/*               |                                                          */
/*               | However, there was a problem that QAC warning occurred   */
/*               | in the implementation based on that assumption.          */
/*               |                                                          */
/*               | In R5.0 v1.1 CanTp development, request to eliminate the */
/*               | QAC warning, we changed the design policy ONLY for this  */
/*               | function and changed the design on the premise that      */
/*               | NO INTERRUPT WILL OCCUR.                                 */
/****************************************************************************/
static void
bsw_cantp_rx_SendFCCtrl( BswConst Bsw_CanTp_CfgType * ptCfgTbl, BswConst Bsw_CanTp_RxNSduCfgType * ptRxNSduCfgTbl, Bsw_CanTp_st_ReceiverStatType * ptReceiverStatTbl )
{
    PduInfoType             st_PduInfo;             /* Receive data                            */
    PduLengthType           UpperLayerBufSize;      /* Upper layer buffer size                 */
    uint16                  u2_ReceiverFCWaitCnt;   /* Number of sent FC.WAIT (prev)           */
    uint16                  u2_WFTMax;              /* WFt Max                                 */
    uint16                  u2_NarCycle;            /* N_ar Cycle                              */
    uint16                  u2_PduId;               /* PduId                                   */
#if( BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE )
    uint16                  u2_RxNSduIdx;           /* Index of RxNSdus                        */
    uint8                   u1_RxParamPtn;          /* Rx Parameter Pattern                    */
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
    uint8                   u1_BS;                  /* Block size                              */
    uint8                   u1_STmin;               /* Separation time minimum                 */
    uint8                   u1_ReceiverRXDL;        /* RXDL                                    */
    Bsw_CanTp_st_FSType     u1_ReceiverFS;          /* Flow status                             */
    Bsw_CanTp_st_FSType     u1_FS;                  /* Flow status for sending                 */
    BufReq_ReturnType       u1_BufRet;              /* Result of upper layer buffer securement */
    uint8                   u1_SendFCCtrlOps;       /* SendFCCtrl operations                   */
    Bsw_CanTp_ReturnType    u1_SendFCRet;           /* Result of SendFC                        */
    uint8                   u1_MaxCFNDataLen;       /* Maximum N_DATA Length in CF             */
    uint8                   u1_PciOffset;           /* Offset to N_PCI address                 */
    uint8                   u1_AddressFormat;       /* Address Format                          */

    /* Snap shot of receiver status info */
    u2_ReceiverFCWaitCnt      = ptReceiverStatTbl->u2ReceiverFCWaitCnt;
#if( BSW_CANTP_CFG_FDSUPPORT == BSW_USE )
    u1_ReceiverRXDL           = ptReceiverStatTbl->u1ReceiverRXDL;
#else /* BSW_CANTP_CFG_FDSUPPORT == BSW_NOUSE */
    u1_ReceiverRXDL           = BSW_CANTP_u1CAN_DL_08;
#endif /* BSW_CANTP_CFG_FDSUPPORT */
    u1_ReceiverFS             = ptReceiverStatTbl->u1ReceiverFS;

#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
    u2_PduId = ptRxNSduCfgTbl->u2PduR_RxIndId;
    u1_BS    = (uint8)bsw_cantp_rx_ReadParamBS( ptRxNSduCfgTbl );
    u1_STmin = (uint8)bsw_cantp_rx_ReadParamSTmin( ptRxNSduCfgTbl );
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
    u2_PduId = ptReceiverStatTbl->u2ReceiverNSduId;
    u2_RxNSduIdx = u2_PduId - ptCfgTbl->u2MinRxNSduId;
    u1_RxParamPtn = ptRxNSduCfgTbl->u1RxParamPtn;
    u1_BS    = (uint8)bsw_cantp_rx_ReadParamBSByIdx( u2_RxNSduIdx, u1_RxParamPtn );
    u1_STmin = (uint8)bsw_cantp_rx_ReadParaSTminByIdx( u2_RxNSduIdx, u1_RxParamPtn );
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */

    /*------------------------------------*/
    /* Decisions of SendFCCtrl operations */
    /*------------------------------------*/
    /*   BSW_CANTP_RX_u1SNDFCCTL_SND_FC     : Send FC frame                                                  */
    /*   BSW_CANTP_RX_u1SNDFCCTL_CONT_WT    : Continues waiting for upper layer's buffer to become available */
    /*   BSW_CANTP_RX_u1SNDFCCTL_TERM       : Terminate reception                                            */
    /*   BSW_CANTP_RX_u1SNDFCCTL_ERROR      : Error (RAM broken)                                             */

    if( u1_ReceiverFS == BSW_CANTP_u1FS_RECEIVER_WT )
    {   /* Flow status is undecided */
        /* Acquisition of remaining Rx buffer size */
        st_PduInfo.SduLength     = (PduLengthType)0UL;
        st_PduInfo.SduDataPtr    = NULL_PTR;
        st_PduInfo.MetaDataPtr   = (BswU1*)NULL_PTR;
        UpperLayerBufSize        = (PduLengthType)0UL;

        u1_BufRet = PduR_CanTpCopyRxData( (PduIdType)u2_PduId, &st_PduInfo, &UpperLayerBufSize );
        if( u1_BufRet == (BufReq_ReturnType)BUFREQ_OK )
        {   /* CopyRxData success */
            /* Judgement of flow status */
            u1_AddressFormat = ptRxNSduCfgTbl->u1AddressFormat;
            u1_PciOffset     = bsw_cantp_cmn_u1PciOffSetTbl[u1_AddressFormat];
            u1_MaxCFNDataLen = u1_ReceiverRXDL - ( u1_PciOffset + BSW_CANTP_u1PCI_SIZE_CF );

            u1_ReceiverFS = bsw_cantp_rx_JudgeFS( ptReceiverStatTbl->u4ReceiverRemainNSduLen, (uint32)UpperLayerBufSize, u1_MaxCFNDataLen, u1_BS );
            if( u1_ReceiverFS == BSW_CANTP_u1FS_RECEIVER_CTS )
            {   /* Upper layer has enough buffer */
                /* Send FC.CTS */
                u2_ReceiverFCWaitCnt = (uint16)0U;
                u1_SendFCCtrlOps     = BSW_CANTP_RX_u1SNDFCCTL_SND_FC;
            }
            else
            {   /* Upper layer has not enough buffer */
                /* Check N_Br timer */
                if( ptReceiverStatTbl->u2ReceiverCycle == (uint16)0U )
                {   /* Check WFTmax overrun */
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
                    u2_WFTMax = ptRxNSduCfgTbl->u2WFTMax;
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
                    u2_WFTMax = bsw_cantp_stRxNSduParamTbl[u1_RxParamPtn].u2WFTMax;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
                    if( u2_ReceiverFCWaitCnt < u2_WFTMax )
                    {   /* Send FC.WAIT */
                        u2_ReceiverFCWaitCnt++;
                        u1_SendFCCtrlOps = BSW_CANTP_RX_u1SNDFCCTL_SND_FC;
                    }
                    else
                    {   /* WFTmax overrun */
                        u1_SendFCCtrlOps = BSW_CANTP_RX_u1SNDFCCTL_TERM;
                    }
                }
                else
                {   /* Time is left until the N_Br */
                    u1_SendFCCtrlOps = BSW_CANTP_RX_u1SNDFCCTL_CONT_WT;
                }
            }
        }
        else
        {   /*  CopyRxData failed */
            u1_SendFCCtrlOps = BSW_CANTP_RX_u1SNDFCCTL_TERM;
        }
    }
    else if( u1_ReceiverFS == BSW_CANTP_u1FS_RECEIVER_OVFL )
    {   /* Send FC.OVFLW */
        u2_ReceiverFCWaitCnt = (uint16)0U;
        u1_SendFCCtrlOps     = BSW_CANTP_RX_u1SNDFCCTL_SND_FC;
    }
    else
    {   /* u1ReceiverFS is broken */
        u1_SendFCCtrlOps = BSW_CANTP_RX_u1SNDFCCTL_ERROR;
    }

    /*--------------------------------*/
    /* SendFCCtrl operation execution */
    /*--------------------------------*/
    if( u1_SendFCCtrlOps == BSW_CANTP_RX_u1SNDFCCTL_SND_FC )
    {
        /* update internal state */
        ptReceiverStatTbl->u1ReceiverStat      = BSW_CANTP_ST_u1STS_FC_TX;
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
        u2_NarCycle = ptRxNSduCfgTbl->u2NarCycle;
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
        u1_RxParamPtn = ptRxNSduCfgTbl->u1RxParamPtn;
        u2_NarCycle = bsw_cantp_stRxNSduParamTbl[u1_RxParamPtn].u2NarCycle;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
        ptReceiverStatTbl->u2ReceiverCycle     = u2_NarCycle + BSW_CANTP_u2MAIN_CYCLE_SINGLE;
        ptReceiverStatTbl->u1ReceiverFS        = u1_ReceiverFS;
        ptReceiverStatTbl->u2ReceiverFCWaitCnt = u2_ReceiverFCWaitCnt;      /* CTS,OVFLW:0  WAIT:prev value+1 */
        ptReceiverStatTbl->u1ReceiverCFNum     = u1_BS;

        /* FC transmission */
        u1_FS        = u1_ReceiverFS & BSW_CANTP_u1MASK_FC_FS;
        u1_SendFCRet = bsw_cantp_rx_SendFC( ptRxNSduCfgTbl, u1_FS, u1_BS, u1_STmin );

        if( u1_SendFCRet != (Bsw_CanTp_ReturnType)BSW_CANTP_E_OK )
        {   /* Transmission failed */
            bsw_cantp_rx_TerminateRx( ptRxNSduCfgTbl, ptReceiverStatTbl, (Std_ReturnType)E_NOT_OK );
        }
    }
    else if( u1_SendFCCtrlOps == BSW_CANTP_RX_u1SNDFCCTL_CONT_WT )
    {
        /* NOP */
    }
    else if( u1_SendFCCtrlOps == BSW_CANTP_RX_u1SNDFCCTL_TERM )
    {   /* CopyRxData failed, or WFTmax overrun */
        bsw_cantp_rx_TerminateRx( ptRxNSduCfgTbl, ptReceiverStatTbl, (Std_ReturnType)E_NOT_OK );
    }
    else
    {   /* RAM broken */
        bsw_cantp_cmn_u1ErrState = BSW_CANTP_u1RAMERR;
        bsw_cantp_rx_ReceiverToIdle( ptReceiverStatTbl );
    }

    return;
}


/****************************************************************************/
/* Function Name | bsw_cantp_rx_SendFC                                      */
/* Description   | Make FC frame and transmit request                       */
/* Preconditions | None                                                     */
/* Parameters    | ptRxNSduCfgTbl : Pointer to RxNSdu configuration         */
/*               | u1FS           : Flow status                             */
/*               | u1BS           : Block size                              */
/*               | u1STmin        : Separation time minimum                 */
/* Return Value  | Bsw_CanTp_ReturnType                                     */
/*               |  BSW_CANTP_E_OK     : success                            */
/*               |  BSW_CANTP_E_NOT_OK : failed                             */
/* Notes         | None                                                     */
/****************************************************************************/
static Bsw_CanTp_ReturnType
bsw_cantp_rx_SendFC( BswConst Bsw_CanTp_RxNSduCfgType * ptRxNSduCfgTbl, Bsw_CanTp_st_FSType u1FS, uint8 u1BS, uint8 u1STmin )
{
    PduInfoType             st_PduInfo;         /* CanTp PDU data structure              */
    uint8                   u1_CanIfTxReqLen;   /* Request data Length of CanIf_Transmit */
    uint8                   u1_Offset;          /* Address offset                        */
    uint8                   u1_AddressFormat;   /* Addressing format                     */
    uint8                   u1_PaddingByte;     /* Padding byte value                    */
    Bsw_CanTp_ReturnType    u1_Ret;             /* Return value                          */
    uint8                   u1_FcTxPaddingAct;  /* Fc Tx Padding Action                  */
    uint16                  u2_CanIf_FcPduId;   /* CanIf PduId                           */
#if( BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE )
    uint8                   u1_RxParamPtn;      /* Rx Parameter Pattern                  */
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */

    /* Local buffer initialization */
    u1_PaddingByte = bsw_cantp_u1PaddingByte;
    bsw_cantp_cmn_u1TxBuffer[BSW_CANTP_OFFSET3] = u1_PaddingByte;    /* for Normal/Fixed addressing */
    bsw_cantp_cmn_u1TxBuffer[BSW_CANTP_OFFSET4] = u1_PaddingByte;
    bsw_cantp_cmn_u1TxBuffer[BSW_CANTP_OFFSET5] = u1_PaddingByte;
    bsw_cantp_cmn_u1TxBuffer[BSW_CANTP_OFFSET6] = u1_PaddingByte;
    bsw_cantp_cmn_u1TxBuffer[BSW_CANTP_OFFSET7] = u1_PaddingByte;

    /* Setting target address information for the first byte of CAN frame data field */
    u1_AddressFormat = ptRxNSduCfgTbl->u1AddressFormat;
    if( u1_AddressFormat == (uint8)BSW_CANTP_EXTENDED )
    {   /* Extended addressing format */

        /* Setting of N_SA (Network Source Address in RxNSdu Configuration) */
        /* Note: The target address of the FC frame becomes N_SA of the RxNSdu configuration. */
        bsw_cantp_cmn_u1TxBuffer[0U] = ptRxNSduCfgTbl->u1NSa;
    }
    else if( ( u1_AddressFormat == (uint8)BSW_CANTP_MIXED )
         ||  ( u1_AddressFormat == (uint8)BSW_CANTP_MIXED29BIT ) )
    {   /* Mixed addressing format */
        bsw_cantp_cmn_u1TxBuffer[0U] = ptRxNSduCfgTbl->u1NAe;
    }
    else
    {   /* Normal/Normal fixed addressing format */
        /* NOP */
    }

    /* making of FC frame data */
    u1_Offset                                          = bsw_cantp_cmn_u1PciOffSetTbl[u1_AddressFormat];
    bsw_cantp_cmn_u1TxBuffer[u1_Offset]                        = BSW_CANTP_u1PCI_FC | u1FS;
    bsw_cantp_cmn_u1TxBuffer[u1_Offset + (uint8)BSW_CANTP_OFFSET1] = u1BS;
    bsw_cantp_cmn_u1TxBuffer[u1_Offset + (uint8)BSW_CANTP_OFFSET2] = u1STmin;

    /* Calculation of length for CanIf_Transmit */
    u1_CanIfTxReqLen = BSW_CANTP_u1CAN_DL_08;
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
    u1_FcTxPaddingAct = ptRxNSduCfgTbl->u1FcTxPaddingAct;
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
    u1_RxParamPtn = ptRxNSduCfgTbl->u1RxParamPtn;
    u1_FcTxPaddingAct = bsw_cantp_stRxNSduParamTbl[u1_RxParamPtn].u1FcTxPaddingAct;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
    if( u1_FcTxPaddingAct == (uint8)BSW_CANTP_OFF )
    {   /* padding: no use */
        u1_CanIfTxReqLen = u1_Offset + BSW_CANTP_u1PCI_SIZE_FC;
    }

    /* FC Transmit */
    st_PduInfo.SduLength     = (PduLengthType)u1_CanIfTxReqLen;
    st_PduInfo.SduDataPtr    = &(bsw_cantp_cmn_u1TxBuffer[0U]);
    st_PduInfo.MetaDataPtr   = (BswU1*)NULL_PTR;

    u2_CanIf_FcPduId = ptRxNSduCfgTbl->u2CanIf_FcPduId;
    u1_Ret = bsw_cantp_snd_SendMessage( (PduIdType)u2_CanIf_FcPduId, &st_PduInfo );

    return u1_Ret;
}


/****************************************************************************/
/* Function Name | bsw_cantp_rx_TimeoutNAr                                  */
/* Description   | Recovery from N_Ar timeout                               */
/* Preconditions | None                                                     */
/* Parameters    | ptRxNSduCfgTbl    : Pointer to RxNSdu configuration      */
/*               | ptReceiverStatTbl : Pointer to receiver status info      */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static void
bsw_cantp_rx_TimeoutNAr( BswConst Bsw_CanTp_RxNSduCfgType * ptRxNSduCfgTbl, Bsw_CanTp_st_ReceiverStatType * ptReceiverStatTbl )
{
    uint8      u1_IsTimeout;     /* Timeout flag    */
    PduIdType  u2_PduId;         /* PduId           */
    uint16     u2_CanIf_FcPduId; /* CanIf PduId     */

    u1_IsTimeout = (uint8)BSW_CANTP_FALSE;
#if( BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE )
    u2_PduId = (PduIdType)ptReceiverStatTbl->u2ReceiverNSduId;
#else
    u2_PduId = (PduIdType)ptRxNSduCfgTbl->u2PduR_RxIndId;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */

    /* Protection of state transition by NAr timeout */
    /********************************************/
    /*******  Start of exclusive section  *******/

    if( ptReceiverStatTbl->u1ReceiverStat == BSW_CANTP_ST_u1STS_FC_TX )
    {   /* There is no Task interference */

        u1_IsTimeout = (uint8)BSW_CANTP_TRUE;
        bsw_cantp_rx_ReceiverToIdle( ptReceiverStatTbl );
    }

    /*******   End of exclusive section   *******/
    /********************************************/

    if( u1_IsTimeout == (uint8)BSW_CANTP_TRUE )
    {
        u2_CanIf_FcPduId = ptRxNSduCfgTbl->u2CanIf_FcPduId;
        bsw_cantp_snd_AbortSend( u2_CanIf_FcPduId );
        PduR_CanTpRxIndication( u2_PduId,  (Std_ReturnType)E_NOT_OK );
    }

    return;
}


/****************************************************************************/
/* Function Name | bsw_cantp_rx_TimeoutNCr                                  */
/* Description   | Recovery from N_Cr timeout                               */
/* Preconditions | None                                                     */
/* Parameters    | ptRxNSduCfgTbl    : Pointer to RxNSdu configuration      */
/*               | ptReceiverStatTbl : Pointer to receiver status info      */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static void
bsw_cantp_rx_TimeoutNCr( BswConst Bsw_CanTp_RxNSduCfgType * ptRxNSduCfgTbl, Bsw_CanTp_st_ReceiverStatType * ptReceiverStatTbl )
{
    uint8      u1_IsTimeout;   /* Timeout flag */
    PduIdType  u2_PduId;       /* PduId        */

    u1_IsTimeout = (uint8)BSW_CANTP_FALSE;
#if( BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE )
    u2_PduId = (PduIdType)ptReceiverStatTbl->u2ReceiverNSduId;
#else
    u2_PduId = (PduIdType)ptRxNSduCfgTbl->u2PduR_RxIndId;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */

    /* Protection of state transition by NCr timeout */
    /********************************************/
    /*******  Start of exclusive section  *******/

    if( ptReceiverStatTbl->u1ReceiverStat == BSW_CANTP_ST_u1STS_CF_RX )
    {   /* There is no Task interference */

        u1_IsTimeout = (uint8)BSW_CANTP_TRUE;
        bsw_cantp_rx_ReceiverToIdle( ptReceiverStatTbl );
    }

    /*******   End of exclusive section   *******/
    /********************************************/

    if( u1_IsTimeout == (uint8)BSW_CANTP_TRUE )
    {
        PduR_CanTpRxIndication( u2_PduId, (Std_ReturnType)E_NOT_OK );
    }

    return;
}


/****************************************************************************/
/* Function Name | bsw_cantp_rx_TerminateRx                                 */
/* Description   | Terminate the reception                                  */
/* Preconditions | None                                                     */
/* Parameters    | ptRxNSduCfgTbl    : Pointer to Target RxNSdu config      */
/*               | ptReceiverStatTbl : Pointer to sender status info        */
/*               | u1Ret             : Result of the reception              */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static void
bsw_cantp_rx_TerminateRx( BswConst Bsw_CanTp_RxNSduCfgType * ptRxNSduCfgTbl, Bsw_CanTp_st_ReceiverStatType * ptReceiverStatTbl, Std_ReturnType u1Ret )
{
    PduIdType  u2_PduId;    /* PduId */

#if( BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE )
    u2_PduId = (PduIdType)ptReceiverStatTbl->u2ReceiverNSduId;
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
    u2_PduId = (PduIdType)ptRxNSduCfgTbl->u2PduR_RxIndId;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */

    bsw_cantp_rx_ReceiverToIdle( ptReceiverStatTbl );
    PduR_CanTpRxIndication( u2_PduId, u1Ret );

    return;
}


/****************************************************************************/
/* Function Name | bsw_cantp_rx_ReceiverToIdle                              */
/* Description   | Receiver status transit to idle                          */
/* Preconditions | None                                                     */
/* Parameters    | ptReceiverStatTbl : Pointer to receiver status info      */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static void
bsw_cantp_rx_ReceiverToIdle( Bsw_CanTp_st_ReceiverStatType * ptReceiverStatTbl )
{
    ptReceiverStatTbl->u4ReceiverRemainNSduLen = 0UL;
    ptReceiverStatTbl->u2ReceiverNSduId        = BSW_CANTP_u2NSDUID_NA;
    ptReceiverStatTbl->u2ReceiverCycle         = (uint16)0U;
    ptReceiverStatTbl->u2ReceiverFCWaitCnt     = (uint16)0U;
    ptReceiverStatTbl->u1ReceiverStat          = BSW_CANTP_ST_u1STS_IDLE;
    ptReceiverStatTbl->u1ReceiverRXDL          = (uint8)0U;
    ptReceiverStatTbl->u1ReceiverSN            = BSW_CANTP_u1SN_INIT;
    ptReceiverStatTbl->u1ReceiverCFNum         = (uint8)0U;
    ptReceiverStatTbl->u1ReceiverFS            = BSW_CANTP_u1FS_RECEIVER_CTS;

    return;
}


#include <cs/bsw_cs_system_memmap_post.h>

#endif /* BSW_BSWM_CS_FUNC_CANTP == BSW_USE */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/09/25                                             */
/*  v1-1-0          :2018/12/26                                             */
/*  v1-2-0          :2020/02/16                                             */
/*  v2-0-0          :2021/09/06                                             */
/*  v3-0-0          :2024/11/05                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
