/* Dcm_Dsp_SID28_c(v5-0-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID28/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_SID28.h>
#if ( DCM_SUPPORT_SID28 == STD_ON )
#include "../../Dsp/usr/Dcm_Dsp_SID28_Connector.h"
#include <Dcm/Dcm_Dsp_Main.h>
#include "../../Dsp/inc/Dcm_Dsp_MsgMaker.h"
#include "../../Dsd/inc/Dcm_Dsd_ServiceMng.h"
#include "../../Dsl/inc/Dcm_Dsl_Main.h"
#include <Dcm/Dcm_Dsl_Ctrl.h>
#include <Dcm/Dcm_Main_EvtDistr.h>
#include <Dcm.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define     DCM_DSP_SID28_SID                   ((uint8)0x28U)

#define     DCM_DSP_SID28_REQLEN                ((uint8)1U)
#define     DCM_DSP_SID28_REQLEN_NODE           ((uint8)3U)

#define     DCM_DSP_SID28_SF_ERX_DTX_NODE       ((uint8)0x04U)
#define     DCM_DSP_SID28_SF_ERX_ETX_NODE       ((uint8)0x05U)
#define     DCM_DSP_SID28_SF_MAX                ((uint8)0x06U)

#define     DCM_DSP_SID28_REQDATA_COM           ((uint8)0U)
#define     DCM_DSP_SID28_REQDATA_NODE_H        ((uint8)1U)
#define     DCM_DSP_SID28_REQDATA_NODE_L        ((uint8)2U)

#define     DCM_DSP_SID28_CTRLMSG_MASK          ((uint8)0x0FU)
#define     DCM_DSP_SID28_CTRLMSG_NORM          ((uint8)0x01U)
#define     DCM_DSP_SID28_CTRLMSG_NM            ((uint8)0x02U)
#define     DCM_DSP_SID28_CTRLMSG_NORM_NM       ((uint8)0x03U)
#define     DCM_DSP_SID28_CTRLMSG_NUM           ((uint8)0x03U)

#define     DCM_DSP_SID28_CTRLSUB_MASK          ((uint8)0xF0U)
#define     DCM_DSP_SID28_CTRLSUB_SFT           ((uint8)4U)
#define     DCM_DSP_SID28_CTRLSUB_ALLCH         ((uint8)0x00U)
#define     DCM_DSP_SID28_CTRLSUB_RXCH          ((uint8)0x0FU)

#define     DCM_DSP_SID28_NODEID_SFT            ((uint8)8U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID28_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext,
    const uint8 u1SubFunction
);
static FUNC ( void, DCM_CODE ) Dcm_Dsp_SID28_CancelProc
( void );
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID28_ChkReqData
(
    const uint8 u1SubFunction,
    const uint8 u1CtrlMsg,
    const uint8 u1CtrlSubnet,
    const uint16 u2NodeId
);
static FUNC ( void, DCM_CODE ) Dcm_Dsp_SID28_SetComMode
(
    const uint8 u1SubFunction,
    const uint16 u2NodeId,
    const uint8 u1ComMChId,
    const Dcm_CommunicationModeType u1ComMode
);
static FUNC ( void, DCM_CODE ) Dcm_Dsp_SID28_SendPosRes
(
    const uint8 u1CtrlSubnet,
    const uint8 u1SubFunction,
    const uint16 u2NodeId,
    const Dcm_CommunicationModeType u1ComMode,
    const uint8 u1CheckPos
);
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID28_ChkCompComCtrl
(
    const uint8 u1SubFunction,
    const uint16 u2NodeId,
    const uint8 u1ComMChId,
    const Dcm_CommunicationModeType u1ComMode
);
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID28_SetSubnetComMode
(
    const uint8 u1CtrlSubnet,
    const uint8 u1SubFunction,
    const uint16 u2NodeId,
    const Dcm_CommunicationModeType u1ComMode
);

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

static VAR( uint8, DCM_VAR_NO_INIT ) Dcm_Dsp_SID28_u1SubFunction;
static VAR( uint8, DCM_VAR_NO_INIT ) Dcm_Dsp_SID28_u1ChIndex;
static VAR( PduIdType, DCM_VAR_NO_INIT ) Dcm_Dsp_SID28_u2RxPduId;
static VAR( boolean, DCM_VAR_NO_INIT ) Dcm_Dsp_SID28_bComCtrlFlag;
static VAR( uint8, DCM_VAR_NO_INIT ) Dcm_Dsp_SID28_ComType;
static VAR( uint16, DCM_VAR_NO_INIT ) Dcm_Dsp_SID28_NodeId;

#define DCM_STOP_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST
#include <Dcm_MemMap.h>
static CONST ( AB_83_ConstV Dcm_CommunicationModeType, DCM_CONST ) Dcm_Dsp_SID28_ComModeTbl[ DCM_DSP_SID28_SF_MAX ][ DCM_DSP_SID28_CTRLMSG_NUM ] =
{
    { DCM_ENABLE_RX_TX_NORM,         DCM_ENABLE_RX_TX_NM,         DCM_ENABLE_RX_TX_NORM_NM         },
    { DCM_ENABLE_RX_DISABLE_TX_NORM, DCM_ENABLE_RX_DISABLE_TX_NM, DCM_ENABLE_RX_DISABLE_TX_NORM_NM },
    { DCM_DISABLE_RX_ENABLE_TX_NORM, DCM_DISABLE_RX_ENABLE_TX_NM, DCM_DISABLE_RX_ENABLE_TX_NORM_NM },
    { DCM_DISABLE_RX_TX_NORMAL,      DCM_DISABLE_RX_TX_NM,        DCM_DISABLE_RX_TX_NORM_NM        },
    { DCM_ENABLE_RX_DISABLE_TX_NORM, DCM_ENABLE_RX_DISABLE_TX_NM, DCM_ENABLE_RX_DISABLE_TX_NORM_NM },
    { DCM_ENABLE_RX_TX_NORM,         DCM_ENABLE_RX_TX_NM,         DCM_ENABLE_RX_TX_NORM_NM         }
};

#define DCM_STOP_SEC_CONST
#include <Dcm_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID28                                            */
/* Description   | Request processing of SID 28                             */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1OpStatus     : Operation state                    */
/*               | [IN] ptMsgContext   : Message Context                    */
/*               | [IN] u1SubFunction  : Sub Function                       */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID28    /* MISRA DEVIATION */
(
    const Dcm_OpStatusType u1OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext,
    const uint8 u1SubFunction
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;

    if( u1OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SID28_InitialProc( ptMsgContext, u1SubFunction );
    }
    else if( u1OpStatus == (Dcm_OpStatusType)DCM_CANCEL )
    {
        Dcm_Dsp_SID28_CancelProc();
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID28_Init                                       */
/* Description   | SID 28 initialization                                    */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID28_Init    /* MISRA DEVIATION */
( void )
{
    Dcm_Dsp_SID28_bComCtrlFlag = (boolean)FALSE;
    Dcm_Dsp_SID28_u2RxPduId = (uint16)0U;

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID28_ResetComCtrl                               */
/* Description   | Reset the communication control                          */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1SesCtrlTypeOld     : Session before change        */
/*               | [IN] u1SesCtrlTypeNew     : Session after change         */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID28_ResetComCtrl    /* MISRA DEVIATION */
(
    const Dcm_SesCtrlType u1SesCtrlTypeOld,          /* MISRA DEVIATION */
    const Dcm_SesCtrlType u1SesCtrlTypeNew
)
{
    boolean b_ResetFlag;
    Std_ReturnType  u1_RetSupported;
    Dcm_CommunicationModeType u1_ComMode;
    uint8 u1_ComMChId;
    uint8 u1_ChLoop;

    if( Dcm_P_SID28_stComCtrl_Tbl.bChkSession == (boolean)TRUE )
    {
        b_ResetFlag = (boolean)FALSE;

        if( u1SesCtrlTypeNew == (uint8)DCM_DEFAULT_SESSION )
        {
            b_ResetFlag = (boolean)TRUE;
        }
        else
        {
            if( Dcm_Dsp_SID28_bComCtrlFlag == (boolean)TRUE )
            {
                u1_RetSupported = Dcm_Dsd_ChkServiceSupported( DCM_DSP_SID28_SID, Dcm_Dsp_SID28_u2RxPduId ,u1SesCtrlTypeNew );
                if( u1_RetSupported != (Std_ReturnType)E_OK )
                {
                    b_ResetFlag = (boolean)TRUE;
                }
            }
        }

        if( b_ResetFlag == (boolean)TRUE )
        {
            for( u1_ChLoop = (uint8)0U; u1_ChLoop < Dcm_P_SID28_stComCtrl_Tbl.u1AllChNum; u1_ChLoop++ )
            {
                /* Reset the communication control */
                if( Dcm_P_SID28_stComCtrl_Tbl.ptAllCh[u1_ChLoop].bUsed == (boolean)TRUE )
                {
                    u1_ComMChId = Dcm_P_SID28_stComCtrl_Tbl.ptAllCh[u1_ChLoop].u1ComMChannel;

                    u1_ComMode = Dcm_Dsp_SID28_Cnct_Mode_CCrl( u1_ComMChId );
                    if( u1_ComMode != (uint8)DCM_ENABLE_RX_TX_NORM_NM )
                    {
                        /* Set communication mode */
                        (void)Dcm_Dsp_SID28_Cnct_Switch_CCrl( u1_ComMChId, DCM_ENABLE_RX_TX_NORM_NM ); /* no return check required */
                        Dcm_Dsp_SID28_Cnct_BswMComMode( u1_ComMChId, DCM_ENABLE_RX_TX_NORM_NM );
                    }
                }
            }
        }
    }

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID28_Confirmation                               */
/* Description   | Complete SID28 request.                                  */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1IdContext     : Id Context                        */
/*               | [IN] u2ConnectionId  : Connection Id                     */
/*               | [IN] u1Status        : Status                            */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID28_Confirmation    /* MISRA DEVIATION */
(
    const Dcm_IdContextType u1IdContext,             /* MISRA DEVIATION */
    const uint16 u2ConnectionId,                     /* MISRA DEVIATION */
    const Dcm_ConfirmationStatusType u1Status
)
{
    uint8                     u1_CtrlTiming;
    uint8                     u1_CtrlMessage;
    uint8                     u1_CtrlSubnet;
    uint8                     u1_SubFunction;
    Dcm_CommunicationModeType u1_ComMode;
    uint16                    u2_NodeId;

    u1_SubFunction = Dcm_Dsp_SID28_u1SubFunction;

    if( u1Status == (Dcm_ConfirmationStatusType)DCM_RES_POS_OK )
    {
        u1_CtrlTiming = Dcm_Dsp_SID28_u1ComCtrlTiming;
        if( u1_CtrlTiming == DCM_P_COMCTRL_CNF )
        {
            if( u1_SubFunction < DCM_DSP_SID28_SF_MAX )
            {
                u1_CtrlMessage = Dcm_Dsp_SID28_ComType & DCM_DSP_SID28_CTRLMSG_MASK;
                if( ( u1_CtrlMessage == DCM_DSP_SID28_CTRLMSG_NORM ) ||
                    ( u1_CtrlMessage == DCM_DSP_SID28_CTRLMSG_NM ) ||
                    ( u1_CtrlMessage == DCM_DSP_SID28_CTRLMSG_NORM_NM ) )
                {
                    u1_CtrlSubnet = ( Dcm_Dsp_SID28_ComType & DCM_DSP_SID28_CTRLSUB_MASK ) >> DCM_DSP_SID28_CTRLSUB_SFT;

                    u2_NodeId = Dcm_Dsp_SID28_NodeId;
                    u1_ComMode = Dcm_Dsp_SID28_ComModeTbl[u1_SubFunction][u1_CtrlMessage - (uint8)1U];
                    Dcm_Dsp_SID28_SetSubnetComMode( u1_CtrlSubnet, u1_SubFunction, u2_NodeId, u1_ComMode );
                }
            }
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID28_Cbk                                        */
/* Description   | Call Back Function to Continue SID28 Processing          */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID28_Cbk    /* MISRA DEVIATION */
(
    const uint8 u1EventId                   /* MISRA DEVIATION */
)
{
    uint8   u1_CtrlMessage;
    uint8   u1_CtrlSubnet;
    uint8   u1_SubFunction;
    Dcm_CommunicationModeType u1_ComMode;
    uint16  u2_NodeId;

    u1_SubFunction = Dcm_Dsp_SID28_u1SubFunction;
    if( u1_SubFunction < DCM_DSP_SID28_SF_MAX )
    {
        u1_CtrlMessage = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID28_REQDATA_COM] & DCM_DSP_SID28_CTRLMSG_MASK;
        if( ( u1_CtrlMessage == DCM_DSP_SID28_CTRLMSG_NORM    ) ||
            ( u1_CtrlMessage == DCM_DSP_SID28_CTRLMSG_NM      ) ||
            ( u1_CtrlMessage == DCM_DSP_SID28_CTRLMSG_NORM_NM ) )
        {
            u1_CtrlSubnet  = ( Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID28_REQDATA_COM] & DCM_DSP_SID28_CTRLSUB_MASK ) >> DCM_DSP_SID28_CTRLSUB_SFT;
            if( ( u1_SubFunction == DCM_DSP_SID28_SF_ERX_DTX_NODE ) || ( u1_SubFunction == DCM_DSP_SID28_SF_ERX_ETX_NODE ) )
            {
                u2_NodeId =  (uint16)(((uint16)Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID28_REQDATA_NODE_H]) << DCM_DSP_SID28_NODEID_SFT )
                                    | ((uint16)Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID28_REQDATA_NODE_L]);
            }
            else
            {
                u2_NodeId = (uint16)0U;
            }

            u1_ComMode = Dcm_Dsp_SID28_ComModeTbl[u1_SubFunction][u1_CtrlMessage - (uint8)1U];

            Dcm_Dsp_SID28_SendPosRes( u1_CtrlSubnet, u1_SubFunction, u2_NodeId, u1_ComMode, Dcm_Dsp_SID28_u1ChIndex );
        }
    }

    return;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID28_InitialProc                                */
/* Description   | Initial process of SID 28 request                        */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext   : Message Context                    */
/*               | [IN] u1SubFunction  : Sub Function                       */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID28_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext,
    const uint8 u1SubFunction
)
{
    boolean b_NrcFlag;
    uint8   u1_ReqDataLen;
    uint8   u1_CtrlMessage;
    uint8   u1_CtrlSubnet;
    uint16  u2_NodeId;
    Std_ReturnType  u1_RetVal;
    Std_ReturnType  u1_RetCheck;
    Std_ReturnType  u1_RetCallOut;
    Dcm_NegativeResponseCodeType u1_ErrorCode;
    Dcm_CommunicationModeType u1_ComMode;
    uint8   u1_CtrlTiming;

    u1_RetVal = E_OK;
    u1_ErrorCode = (Dcm_NegativeResponseCodeType)0x00U;
    b_NrcFlag = (boolean)FALSE;

    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );

    /* Save message context */
    Dcm_Dsp_Main_stMsgContext = *ptMsgContext;
    Dcm_Dsp_SID28_u1SubFunction = u1SubFunction;

    if( ( u1SubFunction == DCM_DSP_SID28_SF_ERX_DTX_NODE ) || ( u1SubFunction == DCM_DSP_SID28_SF_ERX_ETX_NODE ) )
    {
        u1_ReqDataLen = DCM_DSP_SID28_REQLEN_NODE;
    }
    else
    {
        u1_ReqDataLen = DCM_DSP_SID28_REQLEN;
    }

    /* Check request message length */
    if( ptMsgContext->reqDataLen == u1_ReqDataLen )
    {
        Dcm_Dsp_SID28_ComType = ptMsgContext->reqData[DCM_DSP_SID28_REQDATA_COM];

        u1_CtrlMessage = ptMsgContext->reqData[DCM_DSP_SID28_REQDATA_COM] & DCM_DSP_SID28_CTRLMSG_MASK;
        u1_CtrlSubnet  = ( ptMsgContext->reqData[DCM_DSP_SID28_REQDATA_COM] & DCM_DSP_SID28_CTRLSUB_MASK ) >> DCM_DSP_SID28_CTRLSUB_SFT;
        if( ( u1SubFunction == DCM_DSP_SID28_SF_ERX_DTX_NODE ) || ( u1SubFunction == DCM_DSP_SID28_SF_ERX_ETX_NODE ) )
        {
            u2_NodeId =  (uint16)(((uint16)ptMsgContext->reqData[DCM_DSP_SID28_REQDATA_NODE_H]) << DCM_DSP_SID28_NODEID_SFT )
                                | ((uint16)ptMsgContext->reqData[DCM_DSP_SID28_REQDATA_NODE_L]);
        }
        else
        {
            u2_NodeId = (uint16)0U;
        }

        Dcm_Dsp_SID28_NodeId = u2_NodeId;

        /* Check request data */
        u1_RetCheck = Dcm_Dsp_SID28_ChkReqData( u1SubFunction, u1_CtrlMessage, u1_CtrlSubnet, u2_NodeId );
        if( u1_RetCheck == (Std_ReturnType)E_OK )
        {
            u1_RetCallOut = Dcm_Dsp_SID28_CheckComCtrl( u1SubFunction, ptMsgContext->reqData[DCM_DSP_SID28_REQDATA_COM], u2_NodeId, &u1_ErrorCode );

            if( u1_RetCallOut == (Std_ReturnType)E_OK )
            {
                Dcm_Dsp_SID28_u2RxPduId = ptMsgContext->dcmRxPduId;
                Dcm_Dsp_SID28_bComCtrlFlag = (boolean)TRUE;

                if( u1SubFunction < DCM_DSP_SID28_SF_MAX )
                {
                    u1_ComMode = Dcm_Dsp_SID28_ComModeTbl[u1SubFunction][u1_CtrlMessage - (uint8)1U];
                    u1_CtrlTiming = Dcm_Dsp_SID28_u1ComCtrlTiming;
                    if( u1_CtrlTiming == DCM_P_COMCTRL_IND )
                    {
                        Dcm_Dsp_SID28_SetSubnetComMode( u1_CtrlSubnet, u1SubFunction, u2_NodeId, u1_ComMode );
                        Dcm_Dsp_SID28_u1ChIndex = (uint8)0U;
                        Dcm_Dsp_SID28_SendPosRes( u1_CtrlSubnet, u1SubFunction, u2_NodeId, u1_ComMode, (uint8)0U );
                    }
                    else
                    {
                        /* Positive response */
                        Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
                    }
                }
            }
            else if( u1_RetCallOut == (Std_ReturnType)E_NOT_OK )
            {
                b_NrcFlag = (boolean)TRUE;
            }
            else
            {
                /* Rte unimplemented  */
            }
        }
        else
        {
            /* NRC0x31 */
            b_NrcFlag = (boolean)TRUE;
            u1_ErrorCode = DCM_E_REQUESTOUTOFRANGE;
        }
    }
    else
    {
        /* NRC0x13 */
        b_NrcFlag = (boolean)TRUE;
        u1_ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }

    if( b_NrcFlag == (boolean)TRUE )
    {
        /* Negative response */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_ErrorCode );
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID28_CancelProc                                 */
/* Description   | Cancel process of SID 28 request                         */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( void, DCM_CODE ) Dcm_Dsp_SID28_CancelProc
( void )
{

    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID28_COMPCOMCTRL, (boolean)FALSE ); /* no return check required */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID28_ChkReqData                                 */
/* Description   | Request message check                                    */
/* Preconditions | None                                                     */
/* Parameters    | [IN]  u1SubFunction  : Sub Function                      */
/*               | [IN]  u1CtrlMsg      : CommunicationType(0-1Bit)         */
/*               | [IN]  u1CtrlSubnet   : CommunicationType(4-7Bit)         */
/*               | [IN]  u2NodeId       : Node identification number        */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK               : Check OK                          */
/*               |   E_NOT_OK           : Check NG                          */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID28_ChkReqData
(
    const uint8 u1SubFunction,
    const uint8 u1CtrlMsg,
    const uint8 u1CtrlSubnet,
    const uint16 u2NodeId
)
{
    Std_ReturnType  u1_RetVal;
    boolean b_CtrlMsgFlag;
    boolean b_CtrlSubnetFlag;
    uint8 u1_ChLoop;
    uint16 u2_NodeLoop;

    u1_RetVal = E_NOT_OK;
    b_CtrlMsgFlag = (boolean)FALSE;
    b_CtrlSubnetFlag = (boolean)FALSE;

    /* Check communicationType 0-1bit */
    if( u1CtrlMsg == DCM_DSP_SID28_CTRLMSG_NORM )
    {
        if( Dcm_P_SID28_stComCtrl_Tbl.bNormalComMsgUsed == (boolean)TRUE )
        {
            b_CtrlMsgFlag = (boolean)TRUE;
        }
    }
    else if( u1CtrlMsg == DCM_DSP_SID28_CTRLMSG_NM )
    {
        if( Dcm_P_SID28_stComCtrl_Tbl.bNwMngComMsgUsed == (boolean)TRUE )
        {
            b_CtrlMsgFlag = (boolean)TRUE;
        }
    }
    else if( u1CtrlMsg == DCM_DSP_SID28_CTRLMSG_NORM_NM )
    {
        if( ( Dcm_P_SID28_stComCtrl_Tbl.bNormalComMsgUsed == (boolean)TRUE ) && ( Dcm_P_SID28_stComCtrl_Tbl.bNwMngComMsgUsed == (boolean)TRUE ) )
        {
            b_CtrlMsgFlag = (boolean)TRUE;
        }
    }
    else
    {
        /* No process */
    }

    if( b_CtrlMsgFlag == (boolean)TRUE )
    {
        /* Check communicationType 4-7bit */
        if( u1CtrlSubnet == DCM_DSP_SID28_CTRLSUB_ALLCH )
        {
            b_CtrlSubnetFlag = (boolean)TRUE;
        }
        else if( u1CtrlSubnet == DCM_DSP_SID28_CTRLSUB_RXCH )
        {
            if( Dcm_P_SID28_stComCtrl_Tbl.bRxChUsed == (boolean)TRUE )
            {
                b_CtrlSubnetFlag = (boolean)TRUE;
            }
        }
        else
        {
            for( u1_ChLoop = (uint8)0U; u1_ChLoop < Dcm_P_SID28_stComCtrl_Tbl.u1SpChNum; u1_ChLoop++ )
            {
                if( ( Dcm_P_SID28_stComCtrl_Tbl.ptSpCh[u1_ChLoop].u1SubnetNumber == u1CtrlSubnet ) &&
                    ( Dcm_P_SID28_stComCtrl_Tbl.ptSpCh[u1_ChLoop].bUsed == (boolean)TRUE ) )
                {
                    b_CtrlSubnetFlag = (boolean)TRUE;
                    break;
                }
            }
        }

        if( b_CtrlSubnetFlag == (boolean)TRUE )
        {
            /* Check nodeIdentificationNumber */
            if( ( u1SubFunction == DCM_DSP_SID28_SF_ERX_DTX_NODE ) || ( u1SubFunction == DCM_DSP_SID28_SF_ERX_ETX_NODE ) )
            {
                for( u2_NodeLoop = (uint16)0U; u2_NodeLoop < Dcm_P_SID28_stComCtrl_Tbl.u2SubNodeNum; u2_NodeLoop++ )
                {
                    if( ( Dcm_P_SID28_stComCtrl_Tbl.ptSubNode[u2_NodeLoop].u2SubNodeId == u2NodeId ) &&
                        ( Dcm_P_SID28_stComCtrl_Tbl.ptSubNode[u2_NodeLoop].bUsed == (boolean)TRUE ) )
                    {
                        u1_RetVal = E_OK;
                        break;
                    }
                }
            }
            else
            {
                u1_RetVal = E_OK;
            }
        }
    }


    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID28_SetComMode                                 */
/* Description   | Set communication mode                                   */
/* Preconditions | None                                                     */
/* Parameters    | [IN]  u1SubFunction  : Sub Function                      */
/*               | [IN]  u2NodeId       : Node identification number        */
/*               | [IN]  u1ComMChId     : ComM channel ID                   */
/*               | [IN]  u1ComMode      : Communication mode                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( void, DCM_CODE ) Dcm_Dsp_SID28_SetComMode
(
    const uint8 u1SubFunction,
    const uint16 u2NodeId,
    const uint8 u1ComMChId,
    const Dcm_CommunicationModeType u1ComMode
)
{
    boolean b_SetModeFlag;
    uint16 u2_NodeLoop;

    b_SetModeFlag = (boolean)FALSE;

    if( ( u1SubFunction == DCM_DSP_SID28_SF_ERX_DTX_NODE ) || ( u1SubFunction == DCM_DSP_SID28_SF_ERX_ETX_NODE ) )
    {
        /* NodeIdentificationNumber support check */
        for( u2_NodeLoop = (uint16)0U; u2_NodeLoop < Dcm_P_SID28_stComCtrl_Tbl.u2SubNodeNum; u2_NodeLoop++ )
        {
            if( ( Dcm_P_SID28_stComCtrl_Tbl.ptSubNode[u2_NodeLoop].u2SubNodeId == u2NodeId ) &&
                ( Dcm_P_SID28_stComCtrl_Tbl.ptSubNode[u2_NodeLoop].bUsed == (boolean)TRUE ) &&
                ( Dcm_P_SID28_stComCtrl_Tbl.ptSubNode[u2_NodeLoop].u1ComMChannel == u1ComMChId ) )
            {
                b_SetModeFlag = (boolean)TRUE;
                break;
            }
        }
    }
    else
    {
        b_SetModeFlag = (boolean)TRUE;
    }

    if( b_SetModeFlag == (boolean)TRUE )
    {
        /* Set communication mode */
        (void)Dcm_Dsp_SID28_Cnct_Switch_CCrl( u1ComMChId, u1ComMode ); /* no return check required */
        Dcm_Dsp_SID28_Cnct_BswMComMode( u1ComMChId, u1ComMode );
    }


    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID28_SendPosRes                                 */
/* Description   | Positive response of SID 28 request                      */
/* Preconditions | None                                                     */
/* Parameters    | [IN]  u1CtrlSubnet   : Subnet Type                       */
/*               | [IN]  u1SubFunction  : Sub Function                      */
/*               | [IN]  u2NodeId       : Node identification number        */
/*               | [IN]  u1ComMode      : Communication mode                */
/*               | [IN]  u1CheckPos     : Channel index                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( void, DCM_CODE ) Dcm_Dsp_SID28_SendPosRes
(
    const uint8 u1CtrlSubnet,
    const uint8 u1SubFunction,
    const uint16 u2NodeId,
    const Dcm_CommunicationModeType u1ComMode,
    const uint8 u1CheckPos
)
{
    boolean b_CompFlag;
    uint8   u1_ChLoop;
    uint8   u1_ComMChId;
    uint16  u2_PduIdMapIndex;
    uint16  u2_RowIndex;
    uint16  u2_ConnectionIndex;
    uint16  u2_PduIdNum;
    uint16  u2_RowNum;
    Std_ReturnType  u1_RetChkComp;

    b_CompFlag = (boolean)TRUE;
    u2_PduIdNum = Dcm_Dsl_u2PduIdNum;
    u2_RowNum = Dcm_Dsl_u2RowNum;
    if( u1CtrlSubnet == DCM_DSP_SID28_CTRLSUB_ALLCH )
    {
        /* Disable or Enable specified communicationType */
        for( u1_ChLoop = u1CheckPos; u1_ChLoop < Dcm_P_SID28_stComCtrl_Tbl.u1AllChNum; u1_ChLoop++ )
        {
            if( Dcm_P_SID28_stComCtrl_Tbl.ptAllCh[u1_ChLoop].bUsed == (boolean)TRUE )
            {
                u1_ComMChId = Dcm_P_SID28_stComCtrl_Tbl.ptAllCh[u1_ChLoop].u1ComMChannel;
                u1_RetChkComp = Dcm_Dsp_SID28_ChkCompComCtrl( u1SubFunction, u2NodeId, u1_ComMChId, u1ComMode );
                if( u1_RetChkComp == (Std_ReturnType)E_OK )
                {
                    /* No process */
                }
                else if( u1_RetChkComp == (Std_ReturnType)E_NOT_OK )
                {
                    b_CompFlag = (boolean)FALSE;
                }
                else
                {
                    b_CompFlag = (boolean)FALSE;
                    Dcm_Dsp_SID28_u1ChIndex = u1_ChLoop;
                    (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID28_COMPCOMCTRL ); /* no return check required */
                }

                if( b_CompFlag == (boolean)FALSE )
                {
                    break;
                }
            }
        }
    }
    else if( u1CtrlSubnet == DCM_DSP_SID28_CTRLSUB_RXCH )
    {
        /* Disable or Enable network which request is received on receiving node */
        u2_PduIdMapIndex = Dcm_Dsl_GetPduMapIndex();
        if( u2_PduIdMapIndex < u2_PduIdNum )
        {
            u2_RowIndex = Dcm_Dsl_PduIdMapTable[u2_PduIdMapIndex].u2RowIndex;
            if( u2_RowIndex < u2_RowNum )
            {
                u2_ConnectionIndex = Dcm_Dsl_PduIdMapTable[u2_PduIdMapIndex].u2ConnectionIndex;

                u1_ComMChId = Dcm_Dsl_stRow[u2_RowIndex].ptConnection[u2_ConnectionIndex].ptMainConnection->u1ProtocolComMChannel;

                u1_RetChkComp = Dcm_Dsp_SID28_ChkCompComCtrl( u1SubFunction, u2NodeId, u1_ComMChId, u1ComMode );
                if( u1_RetChkComp == (Std_ReturnType)E_OK )
                {
                    /* No process */
                }
                else if( u1_RetChkComp == (Std_ReturnType)E_NOT_OK )
                {
                    b_CompFlag = (boolean)FALSE;
                }
                else
                {
                    b_CompFlag = (boolean)FALSE;
                    (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID28_COMPCOMCTRL ); /* no return check required */
                }
            }
            else
            {
                b_CompFlag = (boolean)FALSE;
            }
        }
        else
        {
            b_CompFlag = (boolean)FALSE;
        }
    }
    else
    {
        /* Disable or Enable specific subnet identified by subnet number */
        for( u1_ChLoop = u1CheckPos; u1_ChLoop < Dcm_P_SID28_stComCtrl_Tbl.u1SpChNum; u1_ChLoop++ )
        {
            if( ( Dcm_P_SID28_stComCtrl_Tbl.ptSpCh[u1_ChLoop].u1SubnetNumber == u1CtrlSubnet ) &&
                ( Dcm_P_SID28_stComCtrl_Tbl.ptSpCh[u1_ChLoop].bUsed == (boolean)TRUE ) )
            {
                u1_ComMChId = Dcm_P_SID28_stComCtrl_Tbl.ptSpCh[u1_ChLoop].u1ComMChannel;
                u1_RetChkComp = Dcm_Dsp_SID28_ChkCompComCtrl( u1SubFunction, u2NodeId, u1_ComMChId, u1ComMode );
                if( u1_RetChkComp == (Std_ReturnType)E_OK )
                {
                    /* No process */
                }
                else if( u1_RetChkComp == (Std_ReturnType)E_NOT_OK )
                {
                    b_CompFlag = (boolean)FALSE;
                }
                else
                {
                    b_CompFlag = (boolean)FALSE;
                    Dcm_Dsp_SID28_u1ChIndex = u1_ChLoop;
                    (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID28_COMPCOMCTRL ); /* no return check required */
                }

                if( b_CompFlag == (boolean)FALSE )
                {
                    break;
                }
            }
        }
    }

    if( b_CompFlag == (boolean)TRUE )
    {
        /* Positive response */
        Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
    }

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID28_ChkCompComCtrl                             */
/* Description   | Confirm completion of communication control              */
/* Preconditions | None                                                     */
/* Parameters    | [IN]  u1SubFunction  : Sub Function                      */
/*               | [IN]  u2NodeId       : Node identification number        */
/*               | [IN]  u1ComMChId     : ComM channel ID                   */
/*               | [IN]  u1ComMode      : Communication mode                */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK             : Complete                            */
/*               |   E_NOT_OK         : Not complete                        */
/*               |   DCM_E_PENDING    : Not complete(Pending)               */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID28_ChkCompComCtrl
(
    const uint8 u1SubFunction,
    const uint16 u2NodeId,
    const uint8 u1ComMChId,
    const Dcm_CommunicationModeType u1ComMode
)
{
    Std_ReturnType  u1_RetVal;
    Std_ReturnType  u1_RetCallOut;
    boolean b_SetModeFlag;
    uint16 u2_NodeLoop;

    u1_RetVal = E_NOT_OK;
    b_SetModeFlag = (boolean)FALSE;

    if( ( u1SubFunction == DCM_DSP_SID28_SF_ERX_DTX_NODE ) || ( u1SubFunction == DCM_DSP_SID28_SF_ERX_ETX_NODE ) )
    {
        /* NodeIdentificationNumber support check */
        for( u2_NodeLoop = (uint16)0U; u2_NodeLoop < Dcm_P_SID28_stComCtrl_Tbl.u2SubNodeNum; u2_NodeLoop++ )
        {
            if( ( Dcm_P_SID28_stComCtrl_Tbl.ptSubNode[u2_NodeLoop].u2SubNodeId == u2NodeId ) &&
                ( Dcm_P_SID28_stComCtrl_Tbl.ptSubNode[u2_NodeLoop].bUsed == (boolean)TRUE ) &&
                ( Dcm_P_SID28_stComCtrl_Tbl.ptSubNode[u2_NodeLoop].u1ComMChannel == u1ComMChId ) )
            {
                b_SetModeFlag = (boolean)TRUE;
                break;
            }
        }
    }
    else
    {
        b_SetModeFlag = (boolean)TRUE;
    }

    if( b_SetModeFlag == (boolean)TRUE )
    {
        u1_RetCallOut = Dcm_Dsp_SID28_CompComCtrl( u1ComMChId, u1ComMode );
        if( u1_RetCallOut == (Std_ReturnType)E_OK )
        {
            u1_RetVal = E_OK;
        }
        else if( u1_RetCallOut == (Std_ReturnType)DCM_E_PENDING )
        {
            u1_RetVal = DCM_E_PENDING;
        }
        else
        {
            /* No process */
        }
    }
    else
    {
        u1_RetVal = E_OK;
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID28_SetSubnetComMode                           */
/* Description   | Call Dcm_Dsp_SID28_SetComMode depending on Subnet        */
/* Preconditions | None                                                     */
/* Parameters    | [IN]  u1CtrlSubnet   : Subnet Type                       */
/*               | [IN]  u1SubFunction  : Sub Function                      */
/*               | [IN]  u2NodeId       : Node identification number        */
/*               | [IN]  u1ComMode      : Communication mode                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID28_SetSubnetComMode
(
    const uint8 u1CtrlSubnet,
    const uint8 u1SubFunction,
    const uint16 u2NodeId,
    const Dcm_CommunicationModeType u1ComMode
)
{
    uint8                     u1_ChLoop;
    uint8                     u1_ComMChId;
    uint16                    u2_PduIdMapIndex;
    uint16                    u2_RowIndex;
    uint16                    u2_ConnectionIndex;
    uint16                    u2_PduIdNum;
    uint16                    u2_RowNum;

    u2_PduIdNum = Dcm_Dsl_u2PduIdNum;
    u2_RowNum = Dcm_Dsl_u2RowNum;

    if( u1CtrlSubnet == DCM_DSP_SID28_CTRLSUB_ALLCH )
    {
        /* Disable or Enable specified communicationType */
        for( u1_ChLoop = (uint8)0U; u1_ChLoop < Dcm_P_SID28_stComCtrl_Tbl.u1AllChNum; u1_ChLoop++ )
        {
            if( Dcm_P_SID28_stComCtrl_Tbl.ptAllCh[u1_ChLoop].bUsed == (boolean)TRUE )
            {
                u1_ComMChId = Dcm_P_SID28_stComCtrl_Tbl.ptAllCh[u1_ChLoop].u1ComMChannel;
                Dcm_Dsp_SID28_SetComMode( u1SubFunction, u2NodeId, u1_ComMChId, u1ComMode );
            }
        }
    }
    else if( u1CtrlSubnet == DCM_DSP_SID28_CTRLSUB_RXCH )
    {
        /* Disable or Enable network which request is received on receiving node */
        u2_PduIdMapIndex = Dcm_Dsl_GetPduMapIndex();
        if( u2_PduIdMapIndex < u2_PduIdNum )
        {
            u2_RowIndex = Dcm_Dsl_PduIdMapTable[u2_PduIdMapIndex].u2RowIndex;
            if( u2_RowIndex < u2_RowNum )
            {
                u2_ConnectionIndex = Dcm_Dsl_PduIdMapTable[u2_PduIdMapIndex].u2ConnectionIndex;

                u1_ComMChId = Dcm_Dsl_stRow[u2_RowIndex].ptConnection[u2_ConnectionIndex].ptMainConnection->u1ProtocolComMChannel;
                Dcm_Dsp_SID28_SetComMode( u1SubFunction, u2NodeId, u1_ComMChId, u1ComMode );
            }
        }
    }
    else
    {
        /* Disable or Enable specific subnet identified by subnet number */
        for( u1_ChLoop = (uint8)0U; u1_ChLoop < Dcm_P_SID28_stComCtrl_Tbl.u1SpChNum; u1_ChLoop++ )
        {
            if( ( Dcm_P_SID28_stComCtrl_Tbl.ptSpCh[u1_ChLoop].u1SubnetNumber == u1CtrlSubnet ) &&
                ( Dcm_P_SID28_stComCtrl_Tbl.ptSpCh[u1_ChLoop].bUsed == (boolean)TRUE ) )
            {
                u1_ComMChId = Dcm_P_SID28_stComCtrl_Tbl.ptSpCh[u1_ChLoop].u1ComMChannel;
                Dcm_Dsp_SID28_SetComMode( u1SubFunction, u2NodeId, u1_ComMChId, u1ComMode );
            }
        }
    }

    return;
}

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
#endif /* DCM_SUPPORT_SID28 == STD_ON */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-2-0         :2019-01-29                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
