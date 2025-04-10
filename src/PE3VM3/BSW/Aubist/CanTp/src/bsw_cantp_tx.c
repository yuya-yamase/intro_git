/* bsw_cantp_tx_c_v3-0-0                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANTP/TX/CODE                                         */
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
#include "../inc/bsw_cantp_tx.h"
#include "../inc/bsw_cantp_snd.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
static Bsw_CanTp_ReturnType bsw_cantp_tx_VerifyFC( BswConst Bsw_CanTp_TxNSduCfgType * ptTxNSduCfgTbl, BswConstR Bsw_CanTp_PduInfoType * ptTpPduInfo, Bsw_CanTp_st_SenderStatType * ptSenderStatTbl );
static void                 bsw_cantp_tx_ReceiveFC( BswConst Bsw_CanTp_TxNSduCfgType * ptTxNSduCfgTbl, BswConstR Bsw_CanTp_PduInfoType * ptTpPduInfo );
static void                 bsw_cantp_tx_SendSF( BswConst Bsw_CanTp_TxNSduCfgType * ptTxNSduCfgTbl, Bsw_CanTp_st_SenderStatType * ptSenderStatTbl, uint8 u1TxNSduLength );
static void                 bsw_cantp_tx_SendFF( BswConst Bsw_CanTp_TxNSduCfgType * ptTxNSduCfgTbl, Bsw_CanTp_st_SenderStatType * ptSenderStatTbl, uint32 u4TxNSduLength );
static void                 bsw_cantp_tx_SendCF( BswConst Bsw_CanTp_TxNSduCfgType * ptTxNSduCfgTbl, Bsw_CanTp_st_SenderStatType * ptSenderStatTbl );
static void                 bsw_cantp_tx_SetFirstByteData( BswConst Bsw_CanTp_TxNSduCfgType * ptTxNSduCfgTbl, uint8 * ptTxData );
static void                 bsw_cantp_tx_UpdateBSSTmin( Bsw_CanTp_st_SenderStatType * ptSenderStatTbl, uint8 u1BlockSize, uint8 u1STmin );
static uint8                bsw_cantp_tx_ChkTxFramePattern( BswConst Bsw_CanTp_TxNSduCfgType * ptTxNSduCfgTbl, uint32 u4TxNSduLength );
static void                 bsw_cantp_tx_TimeoutNAs( BswConst Bsw_CanTp_TxNSduCfgType * ptTxNSduCfgTbl, Bsw_CanTp_st_SenderStatType * ptSenderStatTbl );
static void                 bsw_cantp_tx_TimeoutNBs( BswConst Bsw_CanTp_TxNSduCfgType * ptTxNSduCfgTbl, Bsw_CanTp_st_SenderStatType * ptSenderStatTbl );
static void                 bsw_cantp_tx_TimeoutNCs( BswConst Bsw_CanTp_TxNSduCfgType * ptTxNSduCfgTbl, Bsw_CanTp_st_SenderStatType * ptSenderStatTbl );
static void                 bsw_cantp_tx_TimeoutSTmin( BswConst Bsw_CanTp_TxNSduCfgType * ptTxNSduCfgTbl, Bsw_CanTp_st_SenderStatType * ptSenderStatTbl );
static void                 bsw_cantp_tx_TerminateTxAbend( BswConst Bsw_CanTp_TxNSduCfgType * ptTxNSduCfgTbl, Bsw_CanTp_st_SenderStatType * ptSenderStatTbl, Bsw_CanTp_st_ProcStatType u1ExpectedSenderStat );


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
/* Function Name | bsw_cantp_tx_TransmitCore                                */
/* Description   | Transmission request core procedure                      */
/* Preconditions | None                                                     */
/* Parameters    | ptCfgTbl       : pointer to CanTp configuration          */
/*               | u2NSduId       : Target Tx NSdu-Id                       */
/*               | u4TxNSduLength : The length of the transmission data     */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK          : Transmission request success            */
/*               |  E_NOT_OK      : Transmission request failure            */
/* Notes         | None                                                     */
/****************************************************************************/
Std_ReturnType
bsw_cantp_tx_TransmitCore( BswConst Bsw_CanTp_CfgType * ptCfgTbl, uint16 u2NSduId, uint32 u4TxNSduLength )
{
    BswConst Bsw_CanTp_ChCfgType *      pt_ChCfgTblTop;     /* Pointer to ChCfgTbl              */
    BswConst Bsw_CanTp_ChCfgType *      pt_ChCfgTbl;        /* Pointer to channel configuration */
    BswConst Bsw_CanTp_TxNSduCfgType *  pt_TxNSduCfgTbl;    /* Pointer to TxNSdu configuration  */
    Bsw_CanTp_st_SenderStatType *       pt_SenderStatTbl;   /* Pointer to sender status info    */
    Bsw_CanTp_st_ReceiverStatType *     pt_ReceiverStatTbl; /* Pointer to receiver status info  */
    uint32                              u4_MaxPduLength;    /* Maximum length of PDU            */
    Bsw_CanTp_ReturnType                u1_LengthChk;       /* Length check result              */
    Bsw_CanTp_st_ProcStatType           u1_SenderStat;      /* Sender Processing Status         */
    Bsw_CanTp_st_ProcStatType           u1_ReceiverStat;    /* Receiver Processing Status       */
    uint8                               u1_ChId;            /* Channel ID                       */
    uint8                               u1_TxFramePattern;  /* Single/First frame pattern       */
    Std_ReturnType                      u1_Ret;             /* Return value                     */

    u1_Ret = (Std_ReturnType)E_NOT_OK;

    /* Length check                                       */
    /* Note: This software is available for               */
    /*       the transmission of data more than 4095 byte */
    u1_LengthChk    = (Bsw_CanTp_ReturnType)BSW_CANTP_E_NOT_OK;
    u4_MaxPduLength = bsw_cantp_u4MaxPduLength;
    if( ( u4TxNSduLength > 0UL ) && ( u4TxNSduLength <= u4_MaxPduLength ) )
    {
        pt_TxNSduCfgTbl = bsw_cantp_cmn_GetTxNSduCfgTbl( ptCfgTbl, u2NSduId );

        /* Transmit Frame Pattern check (Single-frame or Multi-frame) */
        u1_TxFramePattern = bsw_cantp_tx_ChkTxFramePattern( pt_TxNSduCfgTbl, u4TxNSduLength );
        if( u1_TxFramePattern == BSW_CANTP_u1PCI_FF )
        {   /* Multi-frame */

            /* TaType check */
            if( pt_TxNSduCfgTbl->u1TaType == (uint8)BSW_CANTP_PHYSICAL )
            {   /* Physical addressing: OK */
                u1_LengthChk = (Bsw_CanTp_ReturnType)BSW_CANTP_E_OK;
            }
        }
        else
        {   /* Single-frame */
            u1_LengthChk = (Bsw_CanTp_ReturnType)BSW_CANTP_E_OK;
        }
    }

    if( u1_LengthChk == (Bsw_CanTp_ReturnType)BSW_CANTP_E_OK )
    {
        u1_ChId     = pt_TxNSduCfgTbl->u1ParentChId;
        pt_ChCfgTblTop = ptCfgTbl->ptChCfgTbl;
        pt_ChCfgTbl = &pt_ChCfgTblTop[u1_ChId];

        pt_SenderStatTbl   = &(bsw_cantp_st_stChStatTbl[u1_ChId].stSenderStatTbl);
        pt_ReceiverStatTbl = &(bsw_cantp_st_stChStatTbl[u1_ChId].stReceiverStatTbl);

        /* Internal state check */

        /********************************************/
        /*******  Start of exclusive section  *******/

        u1_SenderStat   = pt_SenderStatTbl->u1SenderStat;
        u1_ReceiverStat = pt_ReceiverStatTbl->u1ReceiverStat;

        if( (  ( u1_SenderStat         == BSW_CANTP_ST_u1STS_IDLE )
            && ( pt_ChCfgTbl->u1ChMode == (uint8)BSW_CANTP_MODE_FULL_DUPLEX ) )
        ||  (  ( u1_SenderStat         == BSW_CANTP_ST_u1STS_IDLE )
            && ( u1_ReceiverStat       == BSW_CANTP_ST_u1STS_IDLE )
            && ( pt_ChCfgTbl->u1ChMode == (uint8)BSW_CANTP_MODE_HALF_DUPLEX ) ) )
        {
            /* Next state : Waiting for SF/FF Transmission */
            pt_SenderStatTbl->u1SenderStat          = BSW_CANTP_ST_u1STS_TX_WAIT;
            pt_SenderStatTbl->u2SenderNSduId        = u2NSduId;
            pt_SenderStatTbl->u4SenderRemainNSduLen = u4TxNSduLength;

            u1_Ret = (Std_ReturnType)E_OK;
        }

        /*******   End of exclusive section   *******/
        /********************************************/
    }

    return u1_Ret;
}


/****************************************************************************/
/* Function Name | bsw_cantp_tx_CancelTransmitCore                          */
/* Description   | Transmit Cancel Request core procedure                   */
/* Preconditions | None                                                     */
/* Parameters    | ptCfgTbl       : pointer to CanTp configuration          */
/*               | u2NSduId       : Target Tx NSdu-Id                       */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK          : Accept cancel request                   */
/*               |  E_NOT_OK      : Reject cancel request                   */
/* Notes         | None                                                     */
/****************************************************************************/
Std_ReturnType
bsw_cantp_tx_CancelTransmitCore( BswConst Bsw_CanTp_CfgType * ptCfgTbl, uint16 u2NSduId )
{
    BswConst Bsw_CanTp_TxNSduCfgType *  pt_TxNSduCfgTbl;        /* Pointer to TxNSdu configuration */
    Bsw_CanTp_st_SenderStatType *       pt_SenderStatTbl;       /* Pointer to sender status info   */
    uint16                              u2_SenderNSduId;        /* Sender Processing NSdu-Id       */
    Bsw_CanTp_st_ProcStatType           u1_SenderStat;          /* Sender Processing Status        */
    uint8                               u1_ChId;                /* Channel ID                      */
    uint8                               u1_TxFramePattern;      /* Single/First frame pattern      */
    Std_ReturnType                      u1_Ret;                 /* Return value                    */
    uint8                               u1_TxCancel;            /* Tx Cancel                       */
    uint16                              u2_CanIf_PduId;         /* CanIf PduId                     */
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
    uint16                              u2_PduId;               /* PduId                           */
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */

    u1_Ret = (Std_ReturnType)E_NOT_OK;

    pt_TxNSduCfgTbl = bsw_cantp_cmn_GetTxNSduCfgTbl( ptCfgTbl, u2NSduId );

#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
    u1_TxCancel = pt_TxNSduCfgTbl->u1TxCancel;
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
    u1_TxCancel = bsw_cantp_u1TxCancelFunc;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
    if( u1_TxCancel == (uint8)BSW_CANTP_TRUE )
    {
        u1_ChId          = pt_TxNSduCfgTbl->u1ParentChId;
        pt_SenderStatTbl = &(bsw_cantp_st_stChStatTbl[u1_ChId].stSenderStatTbl);

        /********************************************/
        /*******  Start of exclusive section  *******/

        u2_SenderNSduId = pt_SenderStatTbl->u2SenderNSduId;
        u1_SenderStat   = pt_SenderStatTbl->u1SenderStat;
        if( u2_SenderNSduId == u2NSduId )
        {
            switch( u1_SenderStat )
            {
                case BSW_CANTP_ST_u1STS_TX_WAIT:

                    /* CanTp accepts the transmission cancellation request                */
                    /*   only when it is during the transmission wait of the multi-frame. */
                    u1_TxFramePattern = bsw_cantp_tx_ChkTxFramePattern( pt_TxNSduCfgTbl, pt_SenderStatTbl->u4SenderRemainNSduLen );
                    if( u1_TxFramePattern == BSW_CANTP_u1PCI_FF )
                    {
                        u1_Ret = (Std_ReturnType)E_OK;
                        bsw_cantp_tx_SenderToIdle( pt_SenderStatTbl );
                    }
                    break;

                case BSW_CANTP_ST_u1STS_SF_TX:

                    /* Transmission cancellation is impossible when CanTp is awaiting the transmission completion of the single-frame.  */
                    /* NOP */
                    break;

                case BSW_CANTP_ST_u1STS_FF_TX:
                    u1_Ret = (Std_ReturnType)E_OK;
                    bsw_cantp_tx_SenderToIdle( pt_SenderStatTbl );
                    break;

                case BSW_CANTP_ST_u1STS_FC_RX:           /* FALLTHROUGH */
                case BSW_CANTP_ST_u1STS_CF_WAIT_CS:      /* FALLTHROUGH */
                case BSW_CANTP_ST_u1STS_CF_WIT_STMIN:

                    u1_Ret = (Std_ReturnType)E_OK;
                    bsw_cantp_tx_SenderToIdle( pt_SenderStatTbl );
                    break;

                case BSW_CANTP_ST_u1STS_CF_TX:

                    /* Transmission cancellation is impossible when CanTp is awaiting the transmission completion of the last frame of multi-frame. */

                    /* last frame check */
                    if( pt_SenderStatTbl->u4SenderRemainNSduLen > 0UL )
                    {   /* mid frame (it is not the last frame) */
                        u1_Ret = (Std_ReturnType)E_OK;
                        bsw_cantp_tx_SenderToIdle( pt_SenderStatTbl );
                    }
                    break;

                default:
                    /* u1SenderStat or u2SenderNSduId is broken */
                    bsw_cantp_cmn_u1ErrState = BSW_CANTP_u1RAMERR;
                    bsw_cantp_tx_SenderToIdle( pt_SenderStatTbl );
                    break;
            }
        }

        /*******   End of exclusive section   *******/
        /********************************************/

        if( u1_Ret == (Std_ReturnType)E_OK )
        {   /* CanTp accepts the transmission cancellation request */
            /* Confirmation of transmission finished by cancellation */
            if( ( u1_SenderStat == BSW_CANTP_ST_u1STS_FF_TX )
            ||  ( u1_SenderStat == BSW_CANTP_ST_u1STS_CF_TX ) )
            {
                u2_CanIf_PduId = pt_TxNSduCfgTbl->u2CanIf_PduId;
                bsw_cantp_snd_AbortSend( u2_CanIf_PduId );
            }
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
            u2_PduId = pt_TxNSduCfgTbl->u2PduR_TxConfId;
            PduR_CanTpTxConfirmation( (PduIdType)u2_PduId, (Std_ReturnType)E_NOT_OK );
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
            PduR_CanTpTxConfirmation( (PduIdType)u2_SenderNSduId, (Std_ReturnType)E_NOT_OK );
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
        }
    }

    return u1_Ret;
}


/****************************************************************************/
/* Function Name | bsw_cantp_tx_MainFunction_Tx                             */
/* Description   | Periodical handling of Sender unit                       */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_cantp_tx_MainFunction_Tx( void )
{
    BswConst Bsw_CanTp_CfgType *        pt_CfgTbl;              /* Pointer to CanTp configuration   */
    BswConst Bsw_CanTp_TxNSduCfgType *  pt_TxNSduCfgTbl;        /* Pointer to TxNSdu configuration  */
    Bsw_CanTp_st_SenderStatType *       pt_SenderStatTbl;       /* Pointer to sender status info    */
    uint32                              u4_SenderRemainNSduLen; /* Remain Transmission Length       */
    uint16                              u2_SenderNSduId;        /* Sender Processing NSdu-Id        */
    uint16                              u2_SenderCycle;         /* MainFunction cycle count         */
    Bsw_CanTp_st_ProcStatType           u1_SenderStat;          /* Sender Processing Status         */
    uint8                               u1_ChId;                /* Channel ID                       */
    uint8                               u1_ChNum;               /* Number of channels               */
    uint8                               u1_TxFramePattern;      /* Single/First frame pattern       */

    pt_CfgTbl = bsw_cantp_cmn_GetConfigTbl();
    if( pt_CfgTbl != NULL_PTR )
    {
        u1_ChNum = pt_CfgTbl->u1ChNum;
        for( u1_ChId = (uint8)0U; u1_ChId < u1_ChNum; u1_ChId++ )
        {
            pt_SenderStatTbl = &(bsw_cantp_st_stChStatTbl[u1_ChId].stSenderStatTbl);

            /********************************************/
            /*******  Start of exclusive section  *******/

            /* Snap shot of sender status info */
            u4_SenderRemainNSduLen = pt_SenderStatTbl->u4SenderRemainNSduLen;
            u2_SenderNSduId        = pt_SenderStatTbl->u2SenderNSduId;
            u2_SenderCycle         = pt_SenderStatTbl->u2SenderCycle;
            u1_SenderStat          = pt_SenderStatTbl->u1SenderStat;

            /*******   End of exclusive section   *******/
            /********************************************/

            switch( u1_SenderStat )
            {
                case BSW_CANTP_ST_u1STS_IDLE:
                    /* NOP */
                    break;

                case BSW_CANTP_ST_u1STS_TX_WAIT:        /* FALLTHROUGH */
                case BSW_CANTP_ST_u1STS_SF_TX:          /* FALLTHROUGH */
                case BSW_CANTP_ST_u1STS_FF_TX:          /* FALLTHROUGH */
                case BSW_CANTP_ST_u1STS_FC_RX:          /* FALLTHROUGH */
                case BSW_CANTP_ST_u1STS_CF_WAIT_CS:     /* FALLTHROUGH */
                case BSW_CANTP_ST_u1STS_CF_TX:          /* FALLTHROUGH */
                case BSW_CANTP_ST_u1STS_CF_WIT_STMIN:

                    pt_TxNSduCfgTbl = bsw_cantp_cmn_GetTxNSduCfgTbl( pt_CfgTbl, u2_SenderNSduId );
                    if( pt_TxNSduCfgTbl == NULL_PTR )
                    {   /* u2SenderNSduId is broken */
                        bsw_cantp_cmn_u1ErrState = BSW_CANTP_u1RAMERR;

                        /********************************************/
                        /*******  Start of exclusive section  *******/

                        bsw_cantp_tx_SenderToIdle( pt_SenderStatTbl );

                        /*******   End of exclusive section   *******/
                        /********************************************/

                        u1_SenderStat = BSW_CANTP_ST_u1STS_IDLE;
                    }
                    break;

                default:
                    /* u1SenderStat is broken */
                    bsw_cantp_cmn_u1ErrState = BSW_CANTP_u1RAMERR;

                    /********************************************/
                    /*******  Start of exclusive section  *******/

                    bsw_cantp_tx_SenderToIdle( pt_SenderStatTbl );

                    /*******   End of exclusive section   *******/
                    /********************************************/

                    u1_SenderStat = BSW_CANTP_ST_u1STS_IDLE;
                    break;
            }

            if( u1_SenderStat == BSW_CANTP_ST_u1STS_IDLE )
            {
                /* NOP */
            }
            else if( u1_SenderStat == BSW_CANTP_ST_u1STS_TX_WAIT )
            {
                u1_TxFramePattern = bsw_cantp_tx_ChkTxFramePattern( pt_TxNSduCfgTbl, u4_SenderRemainNSduLen );
                if( u1_TxFramePattern == BSW_CANTP_u1PCI_SF )
                {   /* SF transmission */
                    bsw_cantp_tx_SendSF( pt_TxNSduCfgTbl, pt_SenderStatTbl, (uint8)u4_SenderRemainNSduLen );
                }
                else
                {   /* FF transmission */
                    bsw_cantp_tx_SendFF( pt_TxNSduCfgTbl, pt_SenderStatTbl, u4_SenderRemainNSduLen );
                }
            }
            else if( ( u1_SenderStat == BSW_CANTP_ST_u1STS_SF_TX )
                 ||  ( u1_SenderStat == BSW_CANTP_ST_u1STS_FF_TX )
                 ||  ( u1_SenderStat == BSW_CANTP_ST_u1STS_CF_TX ) )
            {
                if( u2_SenderCycle == (uint16)0U )
                {   /* N_As timeout */
                    bsw_cantp_tx_TimeoutNAs( pt_TxNSduCfgTbl, pt_SenderStatTbl );
                }
            }
            else if( u1_SenderStat == BSW_CANTP_ST_u1STS_FC_RX )
            {
                if( u2_SenderCycle == (uint16)0U )
                {   /* N_Bs timeout */
                    bsw_cantp_tx_TimeoutNBs( pt_TxNSduCfgTbl, pt_SenderStatTbl );
                }
            }
            else if( u1_SenderStat == BSW_CANTP_ST_u1STS_CF_WAIT_CS )
            {
                /* CF transmission */
                /* Note: In the case of the period when time-out is settled, CanTp tries the last transmission */
                bsw_cantp_tx_SendCF( pt_TxNSduCfgTbl, pt_SenderStatTbl );

                if( u2_SenderCycle == (uint16)0U )
                {   /* N_Cs timeout */
                    /* Note: If bsw_cantp_tx_SendCF() is finished successfully, then bsw_cantp_tx_TimeoutNCs() does nothing. */
                    bsw_cantp_tx_TimeoutNCs( pt_TxNSduCfgTbl, pt_SenderStatTbl );
                }
            }
            else
            {   /* u1_SenderStat == BSW_CANTP_ST_u1STS_CF_WIT_STMIN */
                if( u2_SenderCycle == (uint16)0U )
                {   /* STmin timeout */
                    bsw_cantp_tx_TimeoutSTmin( pt_TxNSduCfgTbl, pt_SenderStatTbl );

                    /* CF transmission  */
                    bsw_cantp_tx_SendCF( pt_TxNSduCfgTbl, pt_SenderStatTbl );
                }
            }
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | bsw_cantp_tx_RxIndFC                                     */
/* Description   | Notice of FC message reception                           */
/* Preconditions | None                                                     */
/* Parameters    | ptTxNSduCfgTbl : pointer to TxNSdu configuration         */
/*               | ptTpPduInfo    : pointer to PDU information              */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_cantp_tx_RxIndFC( BswConst Bsw_CanTp_TxNSduCfgType * ptTxNSduCfgTbl, BswConstR Bsw_CanTp_PduInfoType * ptTpPduInfo )
{
    Bsw_CanTp_st_SenderStatType *  pt_SenderStatTbl;   /* Pointer to sender status info    */
    Bsw_CanTp_st_ProcStatType      u1_SenderStat;      /* Sender Processing Status         */
    uint8                          u1_ChId;            /* Channel ID                       */
    Bsw_CanTp_ReturnType           u1_Result;          /* Verify result                    */
#if ( BSW_CANTP_CFG_NEXTRX_IN_TX == BSW_CANTP_TX_REGARD_OK )
    uint16                         u2_CanIf_PduId;     /* CanIf PduId                      */
#endif /* BSW_CANTP_CFG_NEXTRX_IN_TX == BSW_CANTP_TX_REGARD_OK */

    u1_ChId          = ptTxNSduCfgTbl->u1ParentChId;
    pt_SenderStatTbl = &(bsw_cantp_st_stChStatTbl[u1_ChId].stSenderStatTbl);
    u1_SenderStat    = pt_SenderStatTbl->u1SenderStat;

    /* Check if FC reception can happen */
#if ( BSW_CANTP_CFG_NEXTRX_IN_TX == BSW_CANTP_TX_REGARD_OK )
    if( ( u1_SenderStat                      == BSW_CANTP_ST_u1STS_FF_TX )          /* Waiting for FF TxConfirmation (FF and FC was interchanged in lower layer) */
    ||  ( u1_SenderStat                      == BSW_CANTP_ST_u1STS_FC_RX )          /* Waiting for FC RxIndication                                               */
    ||  (  ( u1_SenderStat                   == BSW_CANTP_ST_u1STS_CF_TX )          /* Waiting for CF TxConfirmation (CF and FC was interchanged in lower layer) */
        && ( pt_SenderStatTbl->u1SenderCFNum == (uint8)0U )                         /* - last CF of a block         */
        && ( pt_SenderStatTbl->u1SenderBS    != (uint8)0U )                         /*                              */
        && ( pt_SenderStatTbl->u4SenderRemainNSduLen > 0UL ) ) )                    /* - NOT last CF of the message */
#else /* BSW_CANTP_CFG_NEXTRX_IN_TX == BSW_CANTP_TX_INCOMPLETE */
    if( u1_SenderStat                        == BSW_CANTP_ST_u1STS_FC_RX )          /* Waiting for FC RxIndication                                               */
#endif /* BSW_CANTP_CFG_NEXTRX_IN_TX == BSW_CANTP_TX_REGARD_OK */
    {
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
        /* NSduId Check */
        if( pt_SenderStatTbl->u2SenderNSduId == ptTxNSduCfgTbl->u2NSduId )
        {
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
            /* FC format check */
            u1_Result = bsw_cantp_tx_VerifyFC( ptTxNSduCfgTbl, ptTpPduInfo, pt_SenderStatTbl );
            if( u1_Result == (Bsw_CanTp_ReturnType)BSW_CANTP_E_OK )
            {
#if ( BSW_CANTP_CFG_NEXTRX_IN_TX == BSW_CANTP_TX_REGARD_OK )
                if( u1_SenderStat != BSW_CANTP_ST_u1STS_FC_RX )
                {
                    u2_CanIf_PduId = ptTxNSduCfgTbl->u2CanIf_PduId;
                    /* Replaced TxConfirmation */
                    bsw_cantp_snd_AbortSend( u2_CanIf_PduId );
                }
#endif /* BSW_CANTP_CFG_NEXTRX_IN_TX == BSW_CANTP_TX_REGARD_OK */
                /* FC reception processing */
                bsw_cantp_tx_ReceiveFC( ptTxNSduCfgTbl, ptTpPduInfo );
            }
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
        }
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
    }

    return;
}


/****************************************************************************/
/* Function Name | bsw_cantp_tx_TxConfTX                                    */
/* Description   | Transmission completion handling of SF/FF/CF message     */
/* Preconditions | None                                                     */
/* Parameters    | ptTxNSduCfgTbl : Pointer to TxNSdu configuration         */
/*               | u1Result       : Result of the transmission              */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_cantp_tx_TxConfTX( BswConst Bsw_CanTp_TxNSduCfgType * ptTxNSduCfgTbl, Std_ReturnType u1Result )
{
    Bsw_CanTp_st_SenderStatType *  pt_SenderStatTbl;       /* Pointer to sender status info */
    uint16                         u2_NbsCycle;            /* N_bs Cycle                    */
    uint8                          u1_ChId;                /* Channel ID                    */
#if( BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE )
    uint8                          u1_TxParamPtn;          /* Tx Parameter Pattern          */
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */

    u1_ChId          = ptTxNSduCfgTbl->u1ParentChId;
    pt_SenderStatTbl = &(bsw_cantp_st_stChStatTbl[u1_ChId].stSenderStatTbl);

    switch( pt_SenderStatTbl->u1SenderStat )
    {
        case BSW_CANTP_ST_u1STS_SF_TX:
            /* SF TxConfirmation */

            if( u1Result == (Std_ReturnType)E_OK )
            {
                /* Single frame transmission is successfully finished */
                bsw_cantp_tx_TerminateTx( ptTxNSduCfgTbl, pt_SenderStatTbl, (Std_ReturnType)E_OK );
            }
            else
            {
                /* Single frame transmission is not successfully finished */
                bsw_cantp_tx_TerminateTx( ptTxNSduCfgTbl, pt_SenderStatTbl, (Std_ReturnType)E_NOT_OK );
            }
            break;

        case BSW_CANTP_ST_u1STS_FF_TX:
            /* FF TxConfirmation */

            if( u1Result == (Std_ReturnType)E_OK )
            {
                /* Next state : FC reception waiting */
                pt_SenderStatTbl->u1SenderStat  = BSW_CANTP_ST_u1STS_FC_RX;
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
                u2_NbsCycle = ptTxNSduCfgTbl->u2NbsCycle;
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
                u1_TxParamPtn = ptTxNSduCfgTbl->u1TxParamPtn;
                u2_NbsCycle = bsw_cantp_stTxNSduParamTbl[u1_TxParamPtn].u2NbsCycle;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
                pt_SenderStatTbl->u2SenderCycle = u2_NbsCycle + BSW_CANTP_u2MAIN_CYCLE_DOUBLE;
            }
            else
            {
                /* FF transmission is not successfully finished */
                bsw_cantp_tx_TerminateTx( ptTxNSduCfgTbl, pt_SenderStatTbl, (Std_ReturnType)E_NOT_OK );
            }

            break;

        case BSW_CANTP_ST_u1STS_CF_TX:
            /* CF TxConfirmation */

            if( u1Result == (Std_ReturnType)E_OK )
            {
                /* CF pattern check         */
                /* - mid CF                 */
                /* - last CF of a block     */
                /* - last CF of the message */
                if( pt_SenderStatTbl->u4SenderRemainNSduLen > 0UL )
                {   /* mid CF or last CF of a block */

                    if( ( pt_SenderStatTbl->u1SenderCFNum >  (uint8)0U )
                    ||  ( pt_SenderStatTbl->u1SenderBS    == (uint8)0U ) )
                    {
                        /* mid CF */

                        /* Next state : Waiting for start of CF Transmission (in N_CS/STmin time) */

                        /* Note:                                                                                                      */
                        /*   This is start timing of STmin and N_Cs.                                                                  */
                        /*   This software starts measurement of the STmin timer at first.                                            */
                        /*   After progress of the STmin time, this software starts measurements of remaining time of the N_Cs timer. */

                        /* Next state : Waiting for STmin time passage */
                        pt_SenderStatTbl->u1SenderStat  = BSW_CANTP_ST_u1STS_CF_WIT_STMIN;
                        pt_SenderStatTbl->u2SenderCycle = (uint16)pt_SenderStatTbl->u1SenderSTminCycle;
                    }
                    else
                    {   /* Last CF of a block */

                        /* Next state : Waiting for FC RxIndication */
                        pt_SenderStatTbl->u1SenderStat  = BSW_CANTP_ST_u1STS_FC_RX;
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
                        u2_NbsCycle = ptTxNSduCfgTbl->u2NbsCycle;
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
                        u1_TxParamPtn = ptTxNSduCfgTbl->u1TxParamPtn;
                        u2_NbsCycle = bsw_cantp_stTxNSduParamTbl[u1_TxParamPtn].u2NbsCycle;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
                        pt_SenderStatTbl->u2SenderCycle = u2_NbsCycle + BSW_CANTP_u2MAIN_CYCLE_DOUBLE;
                    }
                }
                else
                {   /* last CF of the message */
                    /* Multi frame transmission is successfully finished */
                    bsw_cantp_tx_TerminateTx( ptTxNSduCfgTbl, pt_SenderStatTbl, (Std_ReturnType)E_OK );
                }
            }
            else
            {
                /* CF transmission is not successfully finished */
                bsw_cantp_tx_TerminateTx( ptTxNSduCfgTbl, pt_SenderStatTbl, (Std_ReturnType)E_NOT_OK );
            }
            break;

        case BSW_CANTP_ST_u1STS_TX_WAIT:       /* FALLTHROUGH */
        case BSW_CANTP_ST_u1STS_FC_RX:         /* FALLTHROUGH */
        case BSW_CANTP_ST_u1STS_CF_WAIT_CS:    /* FALLTHROUGH */
        case BSW_CANTP_ST_u1STS_CF_WIT_STMIN:
            /* NOP */
            break;

        case BSW_CANTP_ST_u1STS_IDLE:
            bsw_cantp_tx_SenderToIdle( pt_SenderStatTbl );
            break;

        default:
            /* RAM broken */
            bsw_cantp_cmn_u1ErrState = BSW_CANTP_u1RAMERR;
            bsw_cantp_tx_SenderToIdle( pt_SenderStatTbl );
            break;
    }

    return;
}


/****************************************************************************/
/* Function Name | bsw_cantp_tx_TerminateTx                                 */
/* Description   | Termination of the transmission                          */
/* Preconditions | None                                                     */
/* Parameters    | ptTxNSduCfgTbl  : pointer to Target TxNSdu configuration */
/*               | ptSenderStatTbl : pointer to sender status info          */
/*               | u1Ret           : Result of the transmission             */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_cantp_tx_TerminateTx( BswConst Bsw_CanTp_TxNSduCfgType * ptTxNSduCfgTbl, Bsw_CanTp_st_SenderStatType * ptSenderStatTbl, Std_ReturnType u1Ret )
{
    PduIdType  u2_PduId;       /* PduId                    */
#if( BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE )
    u2_PduId = (PduIdType)ptSenderStatTbl->u2SenderNSduId;
#else
    u2_PduId = (PduIdType)ptTxNSduCfgTbl->u2PduR_TxConfId;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */

    bsw_cantp_tx_SenderToIdle( ptSenderStatTbl );
    PduR_CanTpTxConfirmation( u2_PduId, u1Ret );

    return;
}


/****************************************************************************/
/* Function Name | bsw_cantp_tx_SenderToIdle                                */
/* Description   | Sender status transit to idle                            */
/* Preconditions | None                                                     */
/* Parameters    | ptSenderStatTbl : pointer to sender status info          */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_cantp_tx_SenderToIdle( Bsw_CanTp_st_SenderStatType * ptSenderStatTbl )
{
    ptSenderStatTbl->u4SenderRemainNSduLen = 0UL;
    ptSenderStatTbl->u2SenderNSduId        = BSW_CANTP_u2NSDUID_NA;
    ptSenderStatTbl->u2SenderCycle         = (uint16)0U;
    ptSenderStatTbl->u1SenderStat          = BSW_CANTP_ST_u1STS_IDLE;
    ptSenderStatTbl->u1SenderSN            = BSW_CANTP_u1SN_INIT;
    ptSenderStatTbl->u1SenderCFNum         = (uint8)0U;
    ptSenderStatTbl->u1SenderBS            = (uint8)0U;
    ptSenderStatTbl->u1SenderSTminCycle    = (uint8)0U;

    return;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | bsw_cantp_tx_VerifyFC                                    */
/* Description   | Verify of received message as FC                         */
/* Preconditions | None                                                     */
/* Parameters    | ptTxNSduCfgTbl : pointer to target TxNSdu configuration  */
/*               | ptTpPduInfo    : pointer to target PDU information       */
/*               | ptSenderStatTbl: pointer to sender status info           */
/* Return Value  | Bsw_CanTp_ReturnType                                     */
/*               |  BSW_CANTP_E_OK     : valid                              */
/*               |  BSW_CANTP_E_NOT_OK : invalid                            */
/* Notes         | None                                                     */
/****************************************************************************/
static Bsw_CanTp_ReturnType
bsw_cantp_tx_VerifyFC( BswConst Bsw_CanTp_TxNSduCfgType * ptTxNSduCfgTbl, BswConstR Bsw_CanTp_PduInfoType * ptTpPduInfo, Bsw_CanTp_st_SenderStatType * ptSenderStatTbl )
{
    uint32               u4_CanDl;           /* CAN_DL                                */
    Bsw_CanTp_st_FSType  u1_FS;              /* Flow status                           */
    uint8                u1_NPDUFormatLen;   /* Length of NPDU without CAN FD padding */
    uint8                u1_PciOffset;       /* Offset to N_PCI address               */
    Bsw_CanTp_ReturnType u1_LengthChk;       /* Length check result                   */
    Bsw_CanTp_ReturnType u1_Ret;             /* Return value                          */
    uint8                u1_FcRxPaddingAct;  /* Fc Rx Padding Action                  */
    uint8                u1_AddressFormat;   /* Address Format                        */
#if( BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE )
    uint8                u1_TxParamPtn;      /* Tx Parameter Pattern                  */
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */

    u1_Ret = (Bsw_CanTp_ReturnType)BSW_CANTP_E_NOT_OK;

    /*    Byte | #1            | #2    | #3    | ...    | */
    /*    Bit  | 7-4   | 3-0   |       |       | ...    | */
    /*---------+-------+-------+-------+-------+--------+ */
    /* FC      | 0011b | FS    | BS    | STmin | ...    | */

    /* N_TAtype check */
    /* Note: CANTP_CANFD_PHYSICAL is only selectable in RxNSdu. CANTP_CANFD_PHYSICAL is not selectable in TxNSdu. */
    if( ptTxNSduCfgTbl->u1TaType == (uint8)BSW_CANTP_PHYSICAL )
    {   /* N_TAtype is valid */

        u4_CanDl     = ptTpPduInfo->u4SduLength;
        u1_AddressFormat = ptTxNSduCfgTbl->u1AddressFormat;
        u1_PciOffset = bsw_cantp_cmn_u1PciOffSetTbl[u1_AddressFormat];

        /* data length check */
        /* Note: FC frame's length(CAN_DL) is 3(normal/fixed) or 4(mixed/extended) or 8(padding) */
        u1_LengthChk = (Bsw_CanTp_ReturnType)BSW_CANTP_E_NOT_OK;

        /*-------------------------------------------------------------*/
        /* Note: The fact that CAN_DL is an appropriate value          */
        /*       as CAN_FD presupposes that CanIf or less guarantees.  */
        /*       This design, CanTp does not check it.                 */
        /*       CAN_DL: 0-8 or 12 or 16 or 20 or 24 or 32 or 48 or 64 */
        /*-------------------------------------------------------------*/

        if( u4_CanDl >= (uint32)BSW_CANTP_u1CAN_DL_08 )
        {
            /* CAN_DL is valid */
            u1_LengthChk = (Bsw_CanTp_ReturnType)BSW_CANTP_E_OK;
        }
        else /* u4_CanDl < (uint32)BSW_CANTP_u1CAN_DL_08 */
        {
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
            u1_FcRxPaddingAct = ptTxNSduCfgTbl->u1FcRxPaddingAct;
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
            u1_TxParamPtn = ptTxNSduCfgTbl->u1TxParamPtn;
            u1_FcRxPaddingAct = bsw_cantp_stTxNSduParamTbl[u1_TxParamPtn].u1FcRxPaddingAct;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
            if( u1_FcRxPaddingAct == (uint8)BSW_CANTP_ON )
            {   /* CAN_DL is invalid: padding error */
#if( BSW_CANTP_CFG_DLCHKFC_ERRACT == BSW_CANTP_ERRACT_ABORT )
                /* aborting the transmission session */
                bsw_cantp_tx_TerminateTx( ptTxNSduCfgTbl, ptSenderStatTbl, (Std_ReturnType)E_NOT_OK );
#else /* BSW_CANTP_CFG_DLCHKFC_ERRACT == BSW_CANTP_ERRACT_IGNORE */
                /* FC frame is ignored */
#endif /* BSW_CANTP_CFG_DLCHKFC_ERRACT == BSW_CANTP_ERRACT_ABORT */
            }
            else
            {   /* CAN frame data optimization */
                u1_NPDUFormatLen = u1_PciOffset + BSW_CANTP_u1PCI_SIZE_FC;
                if( u4_CanDl >= (uint32)u1_NPDUFormatLen )
                {   /* CAN_DL is valid: CAN_DL is [3(normal/fixed) to 8] or [4(mixed/extended) to 8] */
                    u1_LengthChk = (Bsw_CanTp_ReturnType)BSW_CANTP_E_OK;
                }
            }
        }

        if( u1_LengthChk == (Bsw_CanTp_ReturnType)BSW_CANTP_E_OK )
        {
            /* FlowStatus error handling */
            u1_FS = (Bsw_CanTp_st_FSType)( ptTpPduInfo->ptSduData[u1_PciOffset] & BSW_CANTP_u1MASK_FC_FS );
            if( u1_FS <= BSW_CANTP_u1FS_SENDER_OVFL )
            {   /* FS is valid (0:CTS or 1:WAIT or 2:OVFLW) */
                u1_Ret = (Bsw_CanTp_ReturnType)BSW_CANTP_E_OK;
            }
            else
            {   /* FS is invalid (3-F) */
                /* aborting the transmission session */
                bsw_cantp_tx_TerminateTx( ptTxNSduCfgTbl, ptSenderStatTbl, (Std_ReturnType)E_NOT_OK );
            }
        }
    }

    return u1_Ret;
}


/****************************************************************************/
/* Function Name | bsw_cantp_tx_ReceiveFC                                   */
/* Description   | Receive FC N_PDU                                         */
/* Preconditions | None                                                     */
/* Parameters    | ptTxNSduCfgTbl : pointer to TxNSdu configuration         */
/*               | ptTpPduInfo    : pointer to PDU information              */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static void
bsw_cantp_tx_ReceiveFC( BswConst Bsw_CanTp_TxNSduCfgType * ptTxNSduCfgTbl, BswConstR Bsw_CanTp_PduInfoType * ptTpPduInfo )
{
    Bsw_CanTp_st_SenderStatType *  pt_SenderStatTbl;   /* Pointer to sender status info    */
    uint16                         u2_NbsCycle;        /* N_bs Cycle                       */
    Bsw_CanTp_st_FSType            u1_FS;              /* Flow status                      */
    uint8                          u1_PciOffset;       /* Offset to N_PCI address          */
    uint8                          u1_ReceivedBS;      /* Received Block Size              */
    uint8                          u1_ReceivedSTmin;   /* Received STmin                   */
    uint8                          u1_STminCycle;      /* STmin Cycle                      */
    uint8                          u1_AddressFormat;   /* Address Format                   */
#if( BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE )
    uint8                          u1_TxParamPtn;      /* Tx Parameter Pattern             */
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */

    pt_SenderStatTbl = &(bsw_cantp_st_stChStatTbl[ptTxNSduCfgTbl->u1ParentChId].stSenderStatTbl);
    u1_AddressFormat = ptTxNSduCfgTbl->u1AddressFormat;
    u1_PciOffset     = bsw_cantp_cmn_u1PciOffSetTbl[u1_AddressFormat];

    /* FS pattern check */
    u1_FS = (Bsw_CanTp_st_FSType)( ptTpPduInfo->ptSduData[u1_PciOffset] & BSW_CANTP_u1MASK_FC_FS );
    if( u1_FS == BSW_CANTP_u1FS_SENDER_CTS )
    {
        /* Extraction of BS/STmin from the received frame */

        u1_ReceivedBS    = ptTpPduInfo->ptSduData[u1_PciOffset + (uint8)BSW_CANTP_OFFSET1];
        u1_ReceivedSTmin = ptTpPduInfo->ptSduData[u1_PciOffset + (uint8)BSW_CANTP_OFFSET2];

        /* Save BS/STmin */
        bsw_cantp_tx_UpdateBSSTmin( pt_SenderStatTbl, u1_ReceivedBS, u1_ReceivedSTmin );

        /* Update STmin Cycle by user */
        u1_STminCycle = pt_SenderStatTbl->u1SenderSTminCycle - (uint8)1U;
        u1_STminCycle = bsw_cantp_tx_CbkFCCTSRxInd( pt_SenderStatTbl->u2SenderNSduId, u1_ReceivedBS, u1_ReceivedSTmin, u1_STminCycle );
        pt_SenderStatTbl->u1SenderSTminCycle = u1_STminCycle + (uint8)1U;

        /* Update the number of CF before the transmission */
        pt_SenderStatTbl->u1SenderCFNum = pt_SenderStatTbl->u1SenderBS;

        /* Next state : Waiting for start of CF Transmission (in N_CS time) */
        pt_SenderStatTbl->u1SenderStat  = BSW_CANTP_ST_u1STS_CF_WAIT_CS;
        pt_SenderStatTbl->u2SenderCycle = bsw_cantp_u2CfTxTimeout + BSW_CANTP_u2MAIN_CYCLE_DOUBLE;

    }
    else if( u1_FS == BSW_CANTP_u1FS_SENDER_WT )
    {
        /* Next state : Waiting for FC RxIndication */
        pt_SenderStatTbl->u1SenderStat  = BSW_CANTP_ST_u1STS_FC_RX;
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
        u2_NbsCycle = ptTxNSduCfgTbl->u2NbsCycle;
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
        u1_TxParamPtn = ptTxNSduCfgTbl->u1TxParamPtn;
        u2_NbsCycle = bsw_cantp_stTxNSduParamTbl[u1_TxParamPtn].u2NbsCycle;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
        pt_SenderStatTbl->u2SenderCycle = u2_NbsCycle + BSW_CANTP_u2MAIN_CYCLE_DOUBLE;
    }
    else
    {   /* u1_FS == CANTP_u1FS_SENDER_OVFLW */

        bsw_cantp_tx_TerminateTx( ptTxNSduCfgTbl, pt_SenderStatTbl, (Std_ReturnType)E_NOT_OK );
    }

    return;
}


/****************************************************************************/
/* Function Name | bsw_cantp_tx_SendSF                                      */
/* Description   | Transmission handling of SF message                      */
/* Preconditions | None                                                     */
/* Parameters    | ptTxNSduCfgTbl  : pointer to TxNSdu configuration        */
/*               | ptSenderStatTbl : pointer to sender status info          */
/*               | u1TxNSduLength  : The length of the transmission data    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static void
bsw_cantp_tx_SendSF( BswConst Bsw_CanTp_TxNSduCfgType * ptTxNSduCfgTbl, Bsw_CanTp_st_SenderStatType * ptSenderStatTbl, uint8 u1TxNSduLength )
{
    PduInfoType             st_PduInfo;         /* Transmission data                 */
    PduLengthType           AvailableData;      /* Dummy                             */
    uint16                  u2_NasCycle;        /* N_as Cycle                        */
    BufReq_ReturnType       u1_BufRet;          /* Result of PduR_CanTpCopyTxData    */
    uint8                   u1_CanIfTxReqLen;   /* Request data Length of CanTp_Send */
    uint8                   u1_Offset;          /* Address offset                    */
    uint8                   u1_PaddingByte;     /* Padding byte value                */
    uint8                   u1_Loop;            /* Loop counter                      */
    Bsw_CanTp_ReturnType    u1_SendRet;         /* Result of SendMessage             */
    uint8                   u1_TxPaddingAct;    /* Tx Padding Action                 */
    uint8                   u1_AddressFormat;   /* Address Format                    */
    PduIdType               u2_PduId;           /* PduId                             */
    uint16                  u2_CanIf_PduId;     /* CanIf PduId                       */

#if( BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE )
    uint8                   u1_TxParamPtn;      /* Tx Parameter Pattern              */
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */

    /* Make first byte data by the address information */
    bsw_cantp_tx_SetFirstByteData( ptTxNSduCfgTbl, &(bsw_cantp_cmn_u1TxBuffer[0U]) );

    /* Get the Offset value to N_PCI address */
    u1_AddressFormat = ptTxNSduCfgTbl->u1AddressFormat;
    u1_Offset = bsw_cantp_cmn_u1PciOffSetTbl[u1_AddressFormat];

    /* Calculation of data length, and Setting of N_PCI */
    u1_CanIfTxReqLen = u1TxNSduLength + u1_Offset + BSW_CANTP_u1PCI_SIZE_SF;
#if( BSW_CANTP_CFG_FDSUPPORT == BSW_USE )
    if( u1_CanIfTxReqLen > BSW_CANTP_u1CAN_DL_08 )
    {   /* SF(CAN_DL>8) */
        u1_CanIfTxReqLen = u1TxNSduLength + u1_Offset + BSW_CANTP_u1PCI_SIZE_SF_ES;

        bsw_cantp_cmn_u1TxBuffer[u1_Offset]                        = (uint8)0U;
        bsw_cantp_cmn_u1TxBuffer[u1_Offset + (uint8)BSW_CANTP_OFFSET1] = u1TxNSduLength;
        u1_Offset += (uint8)BSW_CANTP_OFFSET2;

        /* Calculation of data length for padding of CAN FD frame (TX_DL > 8) */
        /* Note: u1_CanIfTxReqLen is smaller than 65. It was checked in bsw_cantp_tx_ChkTxFramePattern(). */
        u1_CanIfTxReqLen = bsw_cantp_u1OptimizedCanDlTbl[u1_CanIfTxReqLen];
    }
    else
#endif /* BSW_CANTP_CFG_FDSUPPORT == BSW_USE */
    {   /* SF(CAN_DL<=8) */
        bsw_cantp_cmn_u1TxBuffer[u1_Offset] = u1TxNSduLength;
        u1_Offset += (uint8)BSW_CANTP_OFFSET1;

#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
        u1_TxPaddingAct = ptTxNSduCfgTbl->u1PaddingAct;
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
        u1_TxParamPtn = ptTxNSduCfgTbl->u1TxParamPtn;
        u1_TxPaddingAct = bsw_cantp_stTxNSduParamTbl[u1_TxParamPtn].u1PaddingAct;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
        if( u1_TxPaddingAct == (uint8)BSW_CANTP_ON )
        {   /* Calculation of data length for CAN frame data padding (TX_DL = 8) */
            u1_CanIfTxReqLen = BSW_CANTP_u1CAN_DL_08;
        }
    }

    /* Make data for the PduR_CanTpCopyTxData */
    st_PduInfo.SduLength     = (PduLengthType)u1TxNSduLength;
    st_PduInfo.SduDataPtr    = &(bsw_cantp_cmn_u1TxBuffer[u1_Offset]);
    st_PduInfo.MetaDataPtr   = (BswU1*)NULL_PTR;
    AvailableData            = (PduLengthType)0UL;

#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
    u2_PduId = (PduIdType)ptTxNSduCfgTbl->u2PduR_TxConfId;
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
    u2_PduId = (PduIdType)ptSenderStatTbl->u2SenderNSduId;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */

    /* Copy Start */
    u1_BufRet = PduR_CanTpCopyTxData( u2_PduId, &st_PduInfo, NULL_PTR, &AvailableData );

    if( u1_BufRet == (BufReq_ReturnType)BUFREQ_OK )
    {   /* Copy success */

        /* padding */
        u1_PaddingByte = bsw_cantp_u1PaddingByte;
        u1_Offset += u1TxNSduLength;
        for( u1_Loop = u1_Offset; u1_Loop < u1_CanIfTxReqLen; u1_Loop++ )
        {
            bsw_cantp_cmn_u1TxBuffer[u1_Loop] = u1_PaddingByte;
        }

        /* Data setting for CanTp_Send */
        st_PduInfo.SduLength     = (PduLengthType)u1_CanIfTxReqLen;
        st_PduInfo.SduDataPtr    = &(bsw_cantp_cmn_u1TxBuffer[0U]);

        /********************************************/
        /*******  Start of exclusive section  *******/

        if( ptSenderStatTbl->u1SenderStat == BSW_CANTP_ST_u1STS_TX_WAIT )
        {   /* There is no Task interference */

            /* Next state : Waiting for SF TxConfirmation */
            ptSenderStatTbl->u1SenderStat          = BSW_CANTP_ST_u1STS_SF_TX;
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
            u2_NasCycle = ptTxNSduCfgTbl->u2NasCycle;
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
            u1_TxParamPtn = ptTxNSduCfgTbl->u1TxParamPtn;
            u2_NasCycle = bsw_cantp_stTxNSduParamTbl[u1_TxParamPtn].u2NasCycle;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
            ptSenderStatTbl->u2SenderCycle         = u2_NasCycle + BSW_CANTP_u2MAIN_CYCLE_SINGLE;
            ptSenderStatTbl->u4SenderRemainNSduLen = 0UL;
        }

        /*******   End of exclusive section   *******/
        /********************************************/

        u2_CanIf_PduId = ptTxNSduCfgTbl->u2CanIf_PduId;
        /* SF transmission */
        u1_SendRet = bsw_cantp_snd_SendMessage( (PduIdType)u2_CanIf_PduId, &st_PduInfo );

        if( u1_SendRet != (Bsw_CanTp_ReturnType)BSW_CANTP_E_OK )
        {   /* Transmission failed */
            bsw_cantp_tx_TerminateTxAbend( ptTxNSduCfgTbl, ptSenderStatTbl, BSW_CANTP_ST_u1STS_SF_TX );
        }
    }
    else
    {   /* Copy failed */
        bsw_cantp_tx_TerminateTxAbend( ptTxNSduCfgTbl, ptSenderStatTbl, BSW_CANTP_ST_u1STS_TX_WAIT );
    }

    return;
}


/****************************************************************************/
/* Function Name | bsw_cantp_tx_SendFF                                      */
/* Description   | Transmission handling of FF message                      */
/* Preconditions | None                                                     */
/* Parameters    | ptTxNSduCfgTbl  : pointer to TxNSdu configuration        */
/*               | ptSenderStatTbl : pointer to sender status info          */
/*               | u4TxNSduLength  : The length of the transmission data    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static void
bsw_cantp_tx_SendFF( BswConst Bsw_CanTp_TxNSduCfgType * ptTxNSduCfgTbl, Bsw_CanTp_st_SenderStatType * ptSenderStatTbl, uint32 u4TxNSduLength )
{
    PduInfoType             st_PduInfo;         /* Transmission data                 */
    PduLengthType           AvailableData;      /* Dummy                             */
    uint16                  u2_NasCycle;        /* N_as Cycle                        */
    BufReq_ReturnType       u1_BufRet;          /* Result of PduR_CanTpCopyTxData    */
    uint8                   u1_MaxFFNDataLen;   /* Maximum N_DATA Length in FF       */
    uint8                   u1_TxNPduLength;    /* TX_DL                             */
    uint8                   u1_Offset;          /* Address offset                    */
    Bsw_CanTp_ReturnType    u1_SendRet;         /* Result of SendMessage             */
    uint8                   u1_AddressFormat;   /* Address Format                    */
    PduIdType               u2_PduId;           /* PduId                             */
    uint16                  u2_CanIf_PduId;     /* CanIf PduId                       */

#if( BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE )
    uint8                   u1_TxParamPtn;      /* Tx Parameter Pattern              */
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */

    /* Make first byte data by the address information */
    bsw_cantp_tx_SetFirstByteData( ptTxNSduCfgTbl, &(bsw_cantp_cmn_u1TxBuffer[0U]) );

    /* Get the Offset value to N_PCI address */
    u1_AddressFormat = ptTxNSduCfgTbl->u1AddressFormat;
    u1_Offset = bsw_cantp_cmn_u1PciOffSetTbl[u1_AddressFormat];

    /* Setting of N_PCI */
#if( BSW_CANTP_CFG_MAXPDULENGTH > BSW_CANTP_u4FFDL_4095 )
    if( u4TxNSduLength > BSW_CANTP_u4FFDL_4095 )
    {   /* FF(FF_DL>4095) */
        bsw_cantp_cmn_u1TxBuffer[u1_Offset]                        = BSW_CANTP_u1PCI_FF;
        bsw_cantp_cmn_u1TxBuffer[u1_Offset + (uint8)BSW_CANTP_OFFSET1] = (uint8)0U;
        bsw_cantp_cmn_u1TxBuffer[u1_Offset + (uint8)BSW_CANTP_OFFSET2] = (uint8)(u4TxNSduLength >> BSW_CANTP_BIT_SHIFT24);
        bsw_cantp_cmn_u1TxBuffer[u1_Offset + (uint8)BSW_CANTP_OFFSET3] = (uint8)((u4TxNSduLength >> BSW_CANTP_BIT_SHIFT16) & BSW_CANTP_u4LOW8BITMASK);
        bsw_cantp_cmn_u1TxBuffer[u1_Offset + (uint8)BSW_CANTP_OFFSET4] = (uint8)((u4TxNSduLength >> BSW_CANTP_BIT_SHIFT8) & BSW_CANTP_u4LOW8BITMASK);
        bsw_cantp_cmn_u1TxBuffer[u1_Offset + (uint8)BSW_CANTP_OFFSET5] = (uint8)(u4TxNSduLength & BSW_CANTP_u4LOW8BITMASK);
        u1_Offset += (uint8)BSW_CANTP_OFFSET6;
    }
    else
#endif /* BSW_CANTP_CFG_MAXPDULENGTH > BSW_CANTP_u4FFDL_4095 */
    {   /* FF(FF_DL <=4095) */
        bsw_cantp_cmn_u1TxBuffer[u1_Offset]                        = BSW_CANTP_u1PCI_FF | (uint8)(u4TxNSduLength >> BSW_CANTP_BIT_SHIFT8);
        bsw_cantp_cmn_u1TxBuffer[u1_Offset + (uint8)BSW_CANTP_OFFSET1] = (uint8)(u4TxNSduLength & BSW_CANTP_u4LOW8BITMASK);
        u1_Offset += (uint8)BSW_CANTP_OFFSET2;
    }

    /* Make data for the PduR_CanTpCopyTxData */
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
    u1_TxNPduLength          = ptTxNSduCfgTbl->u1TxNPduLength;
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
    u1_TxParamPtn            = ptTxNSduCfgTbl->u1TxParamPtn;
    u1_TxNPduLength          = bsw_cantp_stTxNSduParamTbl[u1_TxParamPtn].u1TxNPduLength;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
    u1_MaxFFNDataLen         = u1_TxNPduLength - u1_Offset;
    st_PduInfo.SduLength     = (PduLengthType)u1_MaxFFNDataLen;
    st_PduInfo.SduDataPtr    = &(bsw_cantp_cmn_u1TxBuffer[u1_Offset]);
    st_PduInfo.MetaDataPtr   = (BswU1*)NULL_PTR;
    AvailableData            = (PduLengthType)0UL;

#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
    u2_PduId = (PduIdType)ptTxNSduCfgTbl->u2PduR_TxConfId;
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
    u2_PduId = (PduIdType)ptSenderStatTbl->u2SenderNSduId;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */

    /* Copy Start */
    u1_BufRet = PduR_CanTpCopyTxData( u2_PduId, &st_PduInfo, NULL_PTR, &AvailableData );

    if( u1_BufRet == (BufReq_ReturnType)BUFREQ_OK )
    {   /* Copy success */

        /* Data setting for CanTp_Send */
        st_PduInfo.SduLength     = (PduLengthType)u1_TxNPduLength;
        st_PduInfo.SduDataPtr    = &(bsw_cantp_cmn_u1TxBuffer[0U]);

        /********************************************/
        /*******  Start of exclusive section  *******/

        if( ptSenderStatTbl->u1SenderStat == BSW_CANTP_ST_u1STS_TX_WAIT )
        {   /* There is no Task interference */

            ptSenderStatTbl->u1SenderStat          = BSW_CANTP_ST_u1STS_FF_TX;
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
            u2_NasCycle = ptTxNSduCfgTbl->u2NasCycle;
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
            u2_NasCycle = bsw_cantp_stTxNSduParamTbl[u1_TxParamPtn].u2NasCycle;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
            ptSenderStatTbl->u2SenderCycle         = u2_NasCycle + BSW_CANTP_u2MAIN_CYCLE_SINGLE;
            ptSenderStatTbl->u1SenderSN            = BSW_CANTP_u1SN_INIT;
            ptSenderStatTbl->u4SenderRemainNSduLen = u4TxNSduLength - (uint32)u1_MaxFFNDataLen;
        }

        /*******   End of exclusive section   *******/
        /********************************************/

        u2_CanIf_PduId = ptTxNSduCfgTbl->u2CanIf_PduId;
        /* FF transmission */
        u1_SendRet = bsw_cantp_snd_SendMessage( (PduIdType)u2_CanIf_PduId, &st_PduInfo );

        if( u1_SendRet != (Bsw_CanTp_ReturnType)BSW_CANTP_E_OK )
        {   /* Transmission failed */
            bsw_cantp_tx_TerminateTxAbend( ptTxNSduCfgTbl, ptSenderStatTbl, BSW_CANTP_ST_u1STS_FF_TX );
        }
    }
    else
    {   /* Copy failed */
        bsw_cantp_tx_TerminateTxAbend( ptTxNSduCfgTbl, ptSenderStatTbl, BSW_CANTP_ST_u1STS_TX_WAIT );
    }

    return;
}


/****************************************************************************/
/* Function Name | bsw_cantp_tx_SendCF                                      */
/* Description   | Transmission handling of CF message                      */
/* Preconditions | None                                                     */
/* Parameters    | ptTxNSduCfgTbl  : pointer to TxNSdu configuration        */
/*               | ptSenderStatTbl : pointer to sender status info          */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static void
bsw_cantp_tx_SendCF( BswConst Bsw_CanTp_TxNSduCfgType * ptTxNSduCfgTbl, Bsw_CanTp_st_SenderStatType * ptSenderStatTbl )
{
    PduInfoType             st_PduInfo;             /* Transmission data                             */
    uint32                  u4_SenderRemainNSduLen; /* Remain Transmission Length                    */
    PduLengthType           AvailableData;          /* Dummy                                         */
    uint16                  u2_NasCycle;            /* N_as Cycle                                    */
    BufReq_ReturnType       u1_BufRet;              /* Result of PduR_CanTpCopyTxData                */
    uint8                   u1_TxNPduLength;        /* TX_DL                                         */
    uint8                   u1_MaxCFNDataLen;       /* Maximum N_DATA Length in CF                   */
    uint8                   u1_PduRCopyTxReqLen;    /* Request data Length of PduR_CanTpCopyTxData   */
    uint8                   u1_CanIfTxReqLen;       /* Request data Length of CanTp_Send             */
    uint8                   u1_Offset;              /* Address offset                                */
    uint8                   u1_SenderSN;            /* Sequence number                               */
    uint8                   u1_SenderCFNum;         /* Number of CF before transmission              */
    uint8                   u1_PaddingByte;         /* Padding byte value                            */
    uint8                   u1_Loop;                /* Loop counter                                  */
    Bsw_CanTp_ReturnType    u1_SendRet;             /* Result of SendMessage                         */
    uint8                   u1_TxPaddingAct;        /* Tx Padding Action                             */
    uint8                   u1_AddressFormat;       /* Address Format                                */
    uint16                  u2_CanIf_PduId;         /* CanIf PduId                                   */
    PduIdType               u2_PduId;               /* PduId                                         */
#if( BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE )
    uint8                   u1_TxParamPtn;          /* Tx Parameter Pattern                          */
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */

    /* Make first byte data by the address information */
    bsw_cantp_tx_SetFirstByteData( ptTxNSduCfgTbl, &(bsw_cantp_cmn_u1TxBuffer[0U]) );

    /* Get the Offset value to N_PCI address */
    u1_AddressFormat = ptTxNSduCfgTbl->u1AddressFormat;
    u1_Offset = bsw_cantp_cmn_u1PciOffSetTbl[u1_AddressFormat];

    /* Calculation of sequence number */
    u1_SenderSN = ptSenderStatTbl->u1SenderSN;
    if( u1_SenderSN == BSW_CANTP_u1SN_INIT )
    {   /* The first CF transmission */
        /* Sequence number is set by 1 */
        u1_SenderSN = BSW_CANTP_u1SN_FIRST;
    }
    else
    {
        u1_SenderSN++;
        u1_SenderSN &= BSW_CANTP_u1MASK_CF_SN;  /* SN: 0x01->0x02->...->0x0F->0x00->0x01->... */
    }
    bsw_cantp_cmn_u1TxBuffer[u1_Offset] = BSW_CANTP_u1PCI_CF | u1_SenderSN;
    u1_Offset++;

    /* Calculation of data length */
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
    u1_TxNPduLength        = ptTxNSduCfgTbl->u1TxNPduLength;
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
    u1_TxParamPtn          = ptTxNSduCfgTbl->u1TxParamPtn;
    u1_TxNPduLength        = bsw_cantp_stTxNSduParamTbl[u1_TxParamPtn].u1TxNPduLength;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
    u1_MaxCFNDataLen       = u1_TxNPduLength - u1_Offset;
    u4_SenderRemainNSduLen = ptSenderStatTbl->u4SenderRemainNSduLen;
    if( u4_SenderRemainNSduLen <= (uint32)u1_MaxCFNDataLen )
    {   /* Last CF */
        /* Data length setting for PduR_CanTpCopyTxData */
        u1_PduRCopyTxReqLen = (uint8)u4_SenderRemainNSduLen;
        /* Calculation of data length for CanTp_Send */
        u1_CanIfTxReqLen    = (uint8)u4_SenderRemainNSduLen + u1_Offset;
#if( BSW_CANTP_CFG_FDSUPPORT == BSW_USE )
        if( u1_CanIfTxReqLen > BSW_CANTP_u1CAN_DL_08 )
        {   /* Calculation of data length for padding of CAN FD frame (TX_DL > 8) */
            /* Note: u1_CanIfTxReqLen is smaller than 64, because u1_TxNPduLength(=TX_DL) is smaller than 65. */
            u1_CanIfTxReqLen = bsw_cantp_u1OptimizedCanDlTbl[u1_CanIfTxReqLen];
        }
        else
#endif /* BSW_CANTP_CFG_FDSUPPORT == BSW_USE */
        {
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
            u1_TxPaddingAct = ptTxNSduCfgTbl->u1PaddingAct;
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
            u1_TxPaddingAct = bsw_cantp_stTxNSduParamTbl[u1_TxParamPtn].u1PaddingAct;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
            if( u1_TxPaddingAct == (uint8)BSW_CANTP_ON )
            {   /* Calculation of data length for CAN frame data padding (TX_DL = 8) */
                u1_CanIfTxReqLen = BSW_CANTP_u1CAN_DL_08;
            }
        }
        /* Calculation of remaining data length */
        u4_SenderRemainNSduLen = 0UL;
    }
    else
    {   /* Other CF */
        /* Data length setting for PduR_CanTpCopyTxData */
        u1_PduRCopyTxReqLen    = u1_MaxCFNDataLen;
        /* Calculation of data length for CanTp_Send */
        u1_CanIfTxReqLen       = u1_TxNPduLength;
        /* Calculation of remaining data length */
        u4_SenderRemainNSduLen = u4_SenderRemainNSduLen - (uint32)u1_MaxCFNDataLen;
    }

    /* Make data for the PduR_CanTpCopyTxData */
    st_PduInfo.SduLength     = (PduLengthType)u1_PduRCopyTxReqLen;
    st_PduInfo.SduDataPtr    = &(bsw_cantp_cmn_u1TxBuffer[u1_Offset]);
    st_PduInfo.MetaDataPtr   = (BswU1*)NULL_PTR;
    AvailableData            = (PduLengthType)0UL;
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
    u2_PduId = (PduIdType)ptTxNSduCfgTbl->u2PduR_TxConfId;
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
    u2_PduId = (PduIdType)ptSenderStatTbl->u2SenderNSduId;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */

    /* Copy Start */
    u1_BufRet = PduR_CanTpCopyTxData( u2_PduId, &st_PduInfo, NULL_PTR, &AvailableData );

    if( u1_BufRet == (BufReq_ReturnType)BUFREQ_OK )
    {   /* Copy success */

        /* padding */
        u1_PaddingByte = bsw_cantp_u1PaddingByte;
        u1_Offset += u1_PduRCopyTxReqLen;
        for( u1_Loop = u1_Offset; u1_Loop < u1_CanIfTxReqLen; u1_Loop++ )
        {
            bsw_cantp_cmn_u1TxBuffer[u1_Loop] = u1_PaddingByte;
        }

        /* Data setting for CanTp_Send */
        st_PduInfo.SduLength    = (PduLengthType)u1_CanIfTxReqLen;
        st_PduInfo.SduDataPtr   = &(bsw_cantp_cmn_u1TxBuffer[0U]);

        /********************************************/
        /*******  Start of exclusive section  *******/

        if( ptSenderStatTbl->u1SenderStat == BSW_CANTP_ST_u1STS_CF_WAIT_CS )
        {   /* There is no Task interference */

            ptSenderStatTbl->u1SenderStat          = BSW_CANTP_ST_u1STS_CF_TX;
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
            u2_NasCycle = ptTxNSduCfgTbl->u2NasCycle;
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
            u1_TxParamPtn = ptTxNSduCfgTbl->u1TxParamPtn;
            u2_NasCycle = bsw_cantp_stTxNSduParamTbl[u1_TxParamPtn].u2NasCycle;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
            ptSenderStatTbl->u2SenderCycle         = u2_NasCycle + BSW_CANTP_u2MAIN_CYCLE_SINGLE;
            ptSenderStatTbl->u1SenderSN            = u1_SenderSN;
            ptSenderStatTbl->u4SenderRemainNSduLen = u4_SenderRemainNSduLen;

            u1_SenderCFNum = ptSenderStatTbl->u1SenderCFNum;
            if( u1_SenderCFNum > (uint8)0U )
            {
                u1_SenderCFNum--;
            }
            ptSenderStatTbl->u1SenderCFNum = u1_SenderCFNum;
        }

        /*******   End of exclusive section   *******/
        /********************************************/

        /* CF transmission */
        u2_CanIf_PduId = ptTxNSduCfgTbl->u2CanIf_PduId;
        u1_SendRet = bsw_cantp_snd_SendMessage( (PduIdType)u2_CanIf_PduId, &st_PduInfo );

        if( u1_SendRet != (Bsw_CanTp_ReturnType)BSW_CANTP_E_OK )
        {   /* Transmission failed */
            bsw_cantp_tx_TerminateTxAbend( ptTxNSduCfgTbl, ptSenderStatTbl, BSW_CANTP_ST_u1STS_CF_TX );
        }
    }
    else if( u1_BufRet == (BufReq_ReturnType)BUFREQ_E_BUSY )
    {   /* Copy failed(BUSY) */
        /* NOP: CanTp tries SendCF again on next MainFunction until N_Cs time-out happens. */
    }
    else
    {   /* Copy failed */
        bsw_cantp_tx_TerminateTxAbend( ptTxNSduCfgTbl, ptSenderStatTbl, BSW_CANTP_ST_u1STS_CF_WAIT_CS );
    }

    return;
}


/****************************************************************************/
/* Function Name | bsw_cantp_tx_SetFirstByteData                            */
/* Description   | Set first byte of CAN frame data with addressing info.   */
/*               | format                                                   */
/* Preconditions | None                                                     */
/* Parameters    | ptTxNSduCfgTbl : pointer to TxNSdu configuration         */
/*               | ptTxData       : Transmission data storage addr          */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static void
bsw_cantp_tx_SetFirstByteData( BswConst Bsw_CanTp_TxNSduCfgType * ptTxNSduCfgTbl, uint8 * ptTxData )
{
    uint8   u1_AddressFormat;   /* Addressing format */

    /* Setting target address information for the first byte of CAN frame data field */
    u1_AddressFormat = ptTxNSduCfgTbl->u1AddressFormat;
    if( u1_AddressFormat == (uint8)BSW_CANTP_EXTENDED )
    {   /* Extended addressing format */

        /* Switch setting value according to channel configuration */
        /* Setting of N_TA (Network Target Address in TxNSdu Configuration) */
        /* Note: The target address of the SF/FF/CF frame becomes N_TA of the TxNSdu configuration. */
        ptTxData[0U] = ptTxNSduCfgTbl->u1NTa;
    }
    else if( ( u1_AddressFormat == (uint8)BSW_CANTP_MIXED )
         ||  ( u1_AddressFormat == (uint8)BSW_CANTP_MIXED29BIT ) )
    {   /* Mixed addressing format */
        ptTxData[0U] = ptTxNSduCfgTbl->u1NAe;
    }
    else
    {   /* Normal/Normal fixed addressing format */
        /* NOP */
    }

    return;
}


/****************************************************************************/
/* Function Name | bsw_cantp_tx_UpdateBSSTmin                               */
/* Description   | The update of the BS and STmin by the FC reception       */
/* Preconditions | None                                                     */
/* Parameters    | ptSenderStatTbl : pointer to sender status info          */
/*               | u1BlockSize     : Block Size                             */
/*               | u1STmin         : Separation Time Minimum                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static void
bsw_cantp_tx_UpdateBSSTmin( Bsw_CanTp_st_SenderStatType * ptSenderStatTbl, uint8 u1BlockSize, uint8 u1STmin )
{
#if( BSW_CANTP_CFG_DYNBSSTMIN_ADOPT == BSW_CANTP_FIXED_BSSTMIN )
    uint8   u1_FixedSTmin;       /* STmin */

    u1_FixedSTmin                       = bsw_cantp_u1FixedSTmin;
    ptSenderStatTbl->u1SenderSTminCycle = bsw_cantp_u1STminCycleTbl[u1_FixedSTmin];
    ptSenderStatTbl->u1SenderBS         = bsw_cantp_u1FixedBS;
#else   /* BSW_CANTP_CFG_DYNBSSTMIN_ADOPT != BSW_CANTP_FIXED_BSSTMIN */
#if( BSW_CANTP_CFG_DYNBSSTMIN_ADOPT == BSW_CANTP_FIRST_BSSTMIN )
    if( ptSenderStatTbl->u1SenderSN == BSW_CANTP_u1SN_INIT )
#endif  /* BSW_CANTP_CFG_DYNBSSTMIN_ADOPT == BSW_CANTP_FIRST_BSSTMIN */
    {
        ptSenderStatTbl->u1SenderSTminCycle = bsw_cantp_u1STminCycleTbl[u1STmin];
        ptSenderStatTbl->u1SenderBS         = u1BlockSize;
    }
#endif  /* BSW_CANTP_CFG_DYNBSSTMIN_ADOPT */

    return;
}


/****************************************************************************/
/* Function Name | bsw_cantp_tx_ChkTxFramePattern                           */
/* Description   | Check transmit frame pattern                             */
/* Preconditions | None                                                     */
/* Parameters    | ptTxNSduCfgTbl : pointer to TxNSdu configuration         */
/*               | u4TxNSduLength : The length of the transmission data     */
/* Return Value  | uint8                                                    */
/*               |  BSW_CANTP_u1PCI_SF : Single frame message               */
/*               |  BSW_CANTP_u1PCI_FF : Multi-frame message                */
/* Notes         | None                                                     */
/****************************************************************************/
static uint8
bsw_cantp_tx_ChkTxFramePattern( BswConst Bsw_CanTp_TxNSduCfgType * ptTxNSduCfgTbl, uint32 u4TxNSduLength )
{
#if( BSW_CANTP_CFG_FDSUPPORT == BSW_USE )
    uint8   u1_TxNPduLength;    /* TX_DL                   */
#if( BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE )
    uint8   u1_TxParamPtn;      /* Tx Parameter Pattern    */
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
#endif /* BSW_CANTP_CFG_FDSUPPORT == BSW_USE */
    uint8   u1_PciOffset;       /* Offset to N_PCI address */
    uint8   u1_Ret;             /* Return value            */
    uint8   u1_AddressFormat;   /* Address Format          */

    u1_AddressFormat = ptTxNSduCfgTbl->u1AddressFormat;
    u1_PciOffset = bsw_cantp_cmn_u1PciOffSetTbl[u1_AddressFormat];

    u1_Ret = BSW_CANTP_u1PCI_FF;

#if( BSW_CANTP_CFG_FDSUPPORT == BSW_USE )
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
    u1_TxNPduLength = ptTxNSduCfgTbl->u1TxNPduLength;
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
    u1_TxParamPtn = ptTxNSduCfgTbl->u1TxParamPtn;
    u1_TxNPduLength = bsw_cantp_stTxNSduParamTbl[u1_TxParamPtn].u1TxNPduLength;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
    if( u1_TxNPduLength > BSW_CANTP_u1CAN_DL_08 )
    {   /* TX_DL = 12,16,20,24,32,48,64 */
        if( u4TxNSduLength <= ( (uint32)u1_TxNPduLength  - ( (uint32)u1_PciOffset + (uint32)BSW_CANTP_u1PCI_SIZE_SF_ES ) ) )
        {   /* SF(CAN_DL <=8) or SF(CAN_DL >8) */
            u1_Ret = BSW_CANTP_u1PCI_SF;
        }
    }
    else
#endif /* BSW_CANTP_CFG_FDSUPPORT == BSW_USE */
    {   /* TX_DL = 8 */
        if( u4TxNSduLength <= ( (uint32)BSW_CANTP_u1CAN_DL_08 - ( (uint32)u1_PciOffset + (uint32)BSW_CANTP_u1PCI_SIZE_SF ) ) )
        {   /* SF(CAN_DL <=8) */
            u1_Ret = BSW_CANTP_u1PCI_SF;
        }
    }

    return u1_Ret;
}


/****************************************************************************/
/* Function Name | bsw_cantp_tx_TimeoutNAs                                  */
/* Description   | Recovery from N_As timeout                               */
/* Preconditions | None                                                     */
/* Parameters    | ptTxNSduCfgTbl : pointer to TxNSdu configuration         */
/*               | ptSenderStatTbl : pointer to sender status info          */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static void
bsw_cantp_tx_TimeoutNAs( BswConst Bsw_CanTp_TxNSduCfgType * ptTxNSduCfgTbl, Bsw_CanTp_st_SenderStatType * ptSenderStatTbl )
{
    Bsw_CanTp_st_ProcStatType  u1_SenderStat;  /* Sender Processing Status */
    uint8                      u1_IsTimeout;   /* Timeout flag             */
    PduIdType                  u2_PduId;       /* PduId                    */
    uint16                     u2_CanIf_PduId; /* CanIf PduId              */

    u1_IsTimeout = (uint8)BSW_CANTP_FALSE;
#if( BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE )
    u2_PduId     = (PduIdType)ptSenderStatTbl->u2SenderNSduId;
#else
    u2_PduId     = (PduIdType)ptTxNSduCfgTbl->u2PduR_TxConfId;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */

    /* Protection of state transition by NAs timeout */
    /********************************************/
    /*******  Start of exclusive section  *******/

    u1_SenderStat = ptSenderStatTbl->u1SenderStat;
    if( ( u1_SenderStat == BSW_CANTP_ST_u1STS_SF_TX )
    ||  ( u1_SenderStat == BSW_CANTP_ST_u1STS_FF_TX )
    ||  ( u1_SenderStat == BSW_CANTP_ST_u1STS_CF_TX ) )
    {   /* There is no Task interference */

        u1_IsTimeout = (uint8)BSW_CANTP_TRUE;
        bsw_cantp_tx_SenderToIdle( ptSenderStatTbl );
    }

    /*******   End of exclusive section   *******/
    /********************************************/

    if( u1_IsTimeout == (uint8)BSW_CANTP_TRUE )
    {
        u2_CanIf_PduId = ptTxNSduCfgTbl->u2CanIf_PduId;
        bsw_cantp_snd_AbortSend( u2_CanIf_PduId );
        PduR_CanTpTxConfirmation( u2_PduId, (Std_ReturnType)E_NOT_OK );
    }

    return;
}


/****************************************************************************/
/* Function Name | bsw_cantp_tx_TimeoutNBs                                  */
/* Description   | Recovery from N_Bs timeout                               */
/* Preconditions | None                                                     */
/* Parameters    | ptTxNSduCfgTbl : pointer to TxNSdu configuration         */
/*               | ptSenderStatTbl : pointer to sender status info          */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static void
bsw_cantp_tx_TimeoutNBs( BswConst Bsw_CanTp_TxNSduCfgType * ptTxNSduCfgTbl, Bsw_CanTp_st_SenderStatType * ptSenderStatTbl )
{
    uint8      u1_IsTimeout;   /* Timeout flag */
    PduIdType  u2_PduId;       /* PduId        */

    u1_IsTimeout = (uint8)BSW_CANTP_FALSE;
#if( BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE )
    u2_PduId     = (PduIdType)ptSenderStatTbl->u2SenderNSduId;
#else
    u2_PduId     = (PduIdType)ptTxNSduCfgTbl->u2PduR_TxConfId;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */

    /* Protection of state transition by NBs timeout */
    /********************************************/
    /*******  Start of exclusive section  *******/

    if( ptSenderStatTbl->u1SenderStat == BSW_CANTP_ST_u1STS_FC_RX )
    {   /* There is no Task interference */

        u1_IsTimeout = (uint8)BSW_CANTP_TRUE;
        bsw_cantp_tx_SenderToIdle( ptSenderStatTbl );
    }

    /*******   End of exclusive section   *******/
    /********************************************/

    if( u1_IsTimeout == (uint8)BSW_CANTP_TRUE )
    {
        PduR_CanTpTxConfirmation( u2_PduId, (Std_ReturnType)E_NOT_OK );
    }

    return;
}


/****************************************************************************/
/* Function Name | bsw_cantp_tx_TimeoutNCs                                  */
/* Description   | Recovery from N_Cs timeout                               */
/* Preconditions | None                                                     */
/* Parameters    | ptTxNSduCfgTbl  : pointer to TxNSdu configuration        */
/*               | ptSenderStatTbl : pointer to sender status info          */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static void
bsw_cantp_tx_TimeoutNCs( BswConst Bsw_CanTp_TxNSduCfgType * ptTxNSduCfgTbl, Bsw_CanTp_st_SenderStatType * ptSenderStatTbl )
{
    uint8      u1_IsTimeout;   /* Timeout flag */
    PduIdType  u2_PduId;       /* PduId        */

    u1_IsTimeout = (uint8)BSW_CANTP_FALSE;
#if( BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE )
    u2_PduId     = (PduIdType)ptSenderStatTbl->u2SenderNSduId;
#else
    u2_PduId     = (PduIdType)ptTxNSduCfgTbl->u2PduR_TxConfId;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */

    /* Protection of state transition by NCs timeout */
    /********************************************/
    /*******  Start of exclusive section  *******/

    if( ptSenderStatTbl->u1SenderStat == BSW_CANTP_ST_u1STS_CF_WAIT_CS )
    {   /* There is no Task interference */

        u1_IsTimeout = (uint8)BSW_CANTP_TRUE;
        bsw_cantp_tx_SenderToIdle( ptSenderStatTbl );
    }

    /*******   End of exclusive section   *******/
    /********************************************/

    if( u1_IsTimeout == (uint8)BSW_CANTP_TRUE )
    {
        PduR_CanTpTxConfirmation( u2_PduId, (Std_ReturnType)E_NOT_OK );
    }

    return;
}


/****************************************************************************/
/* Function Name | bsw_cantp_tx_TimeoutSTmin                                */
/* Description   | CF transmission preparations by STmin timeout            */
/* Preconditions | None                                                     */
/* Parameters    | ptTxNSduCfgTbl  : pointer to TxNSdu configuration        */
/*               | ptSenderStatTbl : pointer to sender status info          */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static void
bsw_cantp_tx_TimeoutSTmin( BswConst Bsw_CanTp_TxNSduCfgType * ptTxNSduCfgTbl, Bsw_CanTp_st_SenderStatType * ptSenderStatTbl )
{
    uint16  u2_CfTxTOCycle;         /* MainFunction cycle count for CF Tx timeout */
    uint16  u2_SenderSTminCycle;    /* MainFunction cycle count for Sender STmin  */
    uint16  u2_SenderCycle;         /* MainFunction cycle count for N_Cs timeout  */

    /* Calculation of Remaining time to CF Tx time-out                                          */
    /*   [Remaining time] = [CF Tx timeout value(config)] + ( 2 * MainFunction period ) - STmin */
    /*                                                                                          */
    /*   Note: "2 * MainFunction period" is countermeasure value of scheduling jitter.          */

    /*--------------------------------------------------------------------------------------------------*/
    /* Time                    | Event                                                                  */
    /*-------------------------+-------------------+----------------------------------------------------*/
    /* 0                       | CF TxConfirmation | N_As timer end & CF Tx time-out/STmin timer start  */
    /* :                       | :                 | :                                                  */
    /* :                       | :                 | STmin timeout(real)                                */
    /* n * MainFunction Period | MainFunction      | STmin timeout(software timer)                      */
    /* :                       | :                 | :                                                  */
    /* :                       | :                 | CT Tx timeout(real)                                */
    /* m * MainFunction Period | MainFunction      | CT Tx timeout(software timer)                      */
    /*--------------------------------------------------------------------------------------------------*/
    u2_SenderCycle = (uint16)0U;
    u2_CfTxTOCycle = BSW_CANTP_u2MAIN_CYCLE_DOUBLE + bsw_cantp_u2CfTxTimeout;
    u2_SenderSTminCycle = (uint16)(ptSenderStatTbl->u1SenderSTminCycle);
    if( u2_CfTxTOCycle >= u2_SenderSTminCycle )
    {
        u2_SenderCycle = u2_CfTxTOCycle - u2_SenderSTminCycle;
    }

    /* Protection of state transition by STmin timeout */
    /********************************************/
    /*******  Start of exclusive section  *******/

    if( ptSenderStatTbl->u1SenderStat == BSW_CANTP_ST_u1STS_CF_WIT_STMIN )
    {   /* There is no Task interference */

        ptSenderStatTbl->u1SenderStat  = BSW_CANTP_ST_u1STS_CF_WAIT_CS;
        ptSenderStatTbl->u2SenderCycle = u2_SenderCycle;
    }

    /*******   End of exclusive section   *******/
    /********************************************/

    return;
}


/****************************************************************************/
/* Function Name | bsw_cantp_tx_TerminateTxAbend                            */
/* Description   | Termination of the transmission abnormal                 */
/* Preconditions | None                                                     */
/* Parameters    | ptTxNSduCfgTbl       : pointer to Target TxNSdu          */
/*               |                      : configuration                     */
/*               | ptSenderStatTbl      : pointer to sender status info     */
/*               | u1ExpectedSenderStat : Expected Sender Processing Status */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static void
bsw_cantp_tx_TerminateTxAbend( BswConst Bsw_CanTp_TxNSduCfgType * ptTxNSduCfgTbl, Bsw_CanTp_st_SenderStatType * ptSenderStatTbl, Bsw_CanTp_st_ProcStatType u1ExpectedSenderStat )
{
    uint8      u1_FailConfFlg;     /* Fail confirmation flag */
    PduIdType  u2_PduId;           /* PduId                  */

    u1_FailConfFlg = (uint8)BSW_CANTP_FALSE;
#if( BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE )
    u2_PduId       = (PduIdType)ptSenderStatTbl->u2SenderNSduId;
#else
    u2_PduId       = (PduIdType)ptTxNSduCfgTbl->u2PduR_TxConfId;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */

    /* Task interference check */
    /********************************************/
    /*******  Start of exclusive section  *******/

    if( ptSenderStatTbl->u1SenderStat == u1ExpectedSenderStat )
    {   /* There is no Task interference */
        u1_FailConfFlg = (uint8)BSW_CANTP_TRUE;
        bsw_cantp_tx_SenderToIdle( ptSenderStatTbl );
    }

    /*******   End of exclusive section   *******/
    /********************************************/

    /*-------------------*/
    /* fail confirmation */
    /*-------------------*/
    if( u1_FailConfFlg == (uint8)BSW_CANTP_TRUE )
    {
        PduR_CanTpTxConfirmation( u2_PduId, (Std_ReturnType)E_NOT_OK );
    }

    return;
}


#include <cs/bsw_cs_system_memmap_post.h>

#endif /* BSW_BSWM_CS_FUNC_CANTP == BSW_USE */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/09/25                                             */
/*  v1-1-0          :2019/02/22                                             */
/*  v1-2-0          :2020/02/17                                             */
/*  v2-0-0          :2021/09/06                                             */
/*  v3-0-0          :2024/11/05                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
