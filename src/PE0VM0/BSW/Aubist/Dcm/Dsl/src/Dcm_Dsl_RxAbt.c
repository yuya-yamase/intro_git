/* Dcm_Dsl_RxAbt_c(v5-10-0)                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsl_RxAbt/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../../Dsl/inc/Dcm_Dsl_RxAbt.h"
#include "../../Dsl/inc/Dcm_Dsl_CommHandling.h"
#include "../../Dsl/inc/Dcm_Dsl_Ctrl_local.h"
#include "../../Dsl/inc/Dcm_Dsl_Main.h"
#include <Dcm/Dcm_Main_EvtDistr.h>
#include <Dcm/Dcm_Dsl_Ctrl.h>
#include <Dcm/Dcm_Main_TmrSrv.h>
#include <SchM_Dcm.h>
#include "../../Dsl/inc/Dcm_Dsl_RxMsg.h"
/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSL_INVALIDPDUID        (PduIdType)0xFFFF  /* Invalid value for PduId */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

static FUNC(uint8, DCM_CODE) Dcm_Dsl_RxAbt_GetPrioCompResult
(
    const uint16 u2ReqPduIdMapIndex,
    const uint16 u2ActivePduIdMapIndex
);

static FUNC(boolean, DCM_CODE) Dcm_Dsl_RxAbt_ArbitrateSORCore
(
    const uint16 u2PduIdMapIndex,
    const uint8 u1ReqKind
);

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

#define DCM_STOP_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST
#include <Dcm_MemMap.h>


#define DCM_STOP_SEC_CONST
#include <Dcm_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>


/****************************************************************************/
/* Function Name | Dcm_Dsl_RxAbt_ArbitrateSOR                               */
/* Description   | This function is receive arbitration for                 */
/*               | Dcm_StartOfReception.                                    */
/* Preconditions | ptInfo != NULL_PTR                                       */
/* Parameters    | [in]  u2PduIdMapIndex : Management number of PduId       */
/*               | [in]  ptInfo          : RxData information               */
/*               | [in]  bOverwriteSOR   : Received SOR overwrite           */
/*               | [in,out] ptReqKind    : Request kind                     */
/* Return Value  | boolean                                                  */
/*               |     TRUE  : Allow request                                */
/*               |     FALSE : Request NG                                   */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_Dsl_RxAbt_ArbitrateSOR
(
    const uint16 u2PduIdMapIndex,
    P2CONST(AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA) ptInfo,
    const boolean bOverwriteSOR,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptReqKind
)
{
    uint16          u2_RxPduId;
    Std_ReturnType  u1_Accept;
    boolean         b_RetVal;
    boolean         b_KeepAliveMsg;

    b_RetVal   = (boolean)FALSE;
    u2_RxPduId = Dcm_Dsl_PduIdMapTable[u2PduIdMapIndex].RxPduId;

    u1_Accept = Dcm_AcceptanceOfReception(u2_RxPduId);
    if( u1_Accept == (Std_ReturnType)E_OK )
    {
        if( bOverwriteSOR == (boolean)TRUE )
        {
            Dcm_Dsl_Ctrl_RedoOfReception(u2PduIdMapIndex, *ptReqKind);
        }

        /* Precondition : ptInfo != NULL_PTR */
        if( ptInfo->SduDataPtr == NULL_PTR )
        {
            /* Judgment of pseudo KAL message : length=2Byte && addrType=functional */
            if( ptInfo->SduLength == DCM_DSL_KEEPALIVE_LEN )
            {
                b_KeepAliveMsg = Dcm_Dsl_Ctrl_IsFunctionalAddressingMsg(u2PduIdMapIndex);
                if( b_KeepAliveMsg == (boolean)TRUE )
                {
                    *ptReqKind = DCM_DSL_RX_REQ_PSEUDOKAL;
                }
                else
                {
                    *ptReqKind = DCM_DSL_RX_REQ_NORMAL;
                }
            }
            else
            {
                *ptReqKind = DCM_DSL_RX_REQ_NORMAL;
            }
        }
        else
        {
            b_KeepAliveMsg = Dcm_Dsl_Ctrl_IsDirectKeepAliveMsg(u2PduIdMapIndex, ptInfo);
            if( b_KeepAliveMsg == (boolean)TRUE )
            {
                *ptReqKind = DCM_DSL_RX_REQ_KAL;
            }
            else
            {
                *ptReqKind = DCM_DSL_RX_REQ_NORMAL;
            }
        }
        b_RetVal = Dcm_Dsl_RxAbt_ArbitrateSORCore(u2PduIdMapIndex, *ptReqKind);
    }

    return b_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_RxAbt_StartOfReception                           */
/* Description   | This function performs processing at the time of         */
/*               | receiving start notification.                            */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduIdMapIndex : PduMapIndex Value                 */
/*               | [in] bKeepAliveMsg   : KAL(TRUE) or Not KAL(FALSE)       */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_RxAbt_StartOfReception
(
    const uint16 u2PduIdMapIndex,
    const boolean bKeepAliveMsg
)
{
    Dcm_Dsl_Ctrl_StartOfReception(u2PduIdMapIndex, bKeepAliveMsg);
    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_RxAbt_ArbitrateRxInd                             */
/* Description   | This function is receive arbitration for                 */
/*               | Dcm_TpRxIndication.                                      */
/* Preconditions | RxState == DCM_DSL_RX_ST_RECEIVE Only                    */
/* Parameters    | [in] u2PduIdMapIndex : Management number of PduId        */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_RxAbt_ArbitrateRxInd
(
    const uint16 u2PduIdMapIndex
)
{
    uint16         u2_ActivePduIdMapIndex;
    uint16         u2_ActiveRxPduId;
    uint16         u2_RxPduId;
    Std_ReturnType u1_ChgClientResult;
    Std_ReturnType u1_AllowBusyResp;
    uint8          u1_PriorityCompResult;
    boolean        b_SameClient;
    boolean        b_Processing;
    boolean        b_FirstCom;
    boolean        b_BusyResponce;
    boolean        b_ChangeClient;
    boolean        b_ActiveSession;

    b_ChangeClient = (boolean)FALSE;
    u2_RxPduId     = Dcm_Dsl_PduIdMapTable[u2PduIdMapIndex].RxPduId;

    b_FirstCom = Dcm_Dsl_Ctrl_IsFirstCommunication();
    if( b_FirstCom == (boolean)TRUE )
    {
        u2_ActiveRxPduId = (uint16)DCM_DSL_INVALIDPDUID;
        b_ChangeClient   = (boolean)TRUE;
    }
    else
    {
        b_SameClient = Dcm_Dsl_Ctrl_IsRecvInteractiveClient(u2PduIdMapIndex);
        if( b_SameClient == (boolean)TRUE )
        {
            Dcm_Dsl_Ctrl_Accept(u2PduIdMapIndex);
        }
        else
        {
            u2_ActivePduIdMapIndex = Dcm_Dsl_Ctrl_GetRxPduMapIndex();
            u1_PriorityCompResult  = Dcm_Dsl_RxAbt_GetPrioCompResult(u2PduIdMapIndex, u2_ActivePduIdMapIndex);
            if( u1_PriorityCompResult == DCM_DSL_PRIORITY_HIGH )
            {
                u2_ActiveRxPduId = Dcm_Dsl_PduIdMapTable[u2_ActivePduIdMapIndex].RxPduId;
                b_ChangeClient   = (boolean)TRUE;
            }
            else
            {
                b_BusyResponce = (boolean)FALSE;
                b_Processing   = Dcm_Dsl_Ctrl_IsBusyInteractiveClient();
                if( b_Processing == (boolean)TRUE )
                {
                    b_BusyResponce = (boolean)TRUE;
                }
                else
                {
                    b_ActiveSession = Dcm_Dsl_Ctrl_IsActiveSession();
                    if( b_ActiveSession == (boolean)FALSE )
                    {
                        u2_ActiveRxPduId = Dcm_Dsl_PduIdMapTable[u2_ActivePduIdMapIndex].RxPduId;
                        b_ChangeClient   = (boolean)TRUE;
                    }
                    else
                    {
                        b_BusyResponce = (boolean)TRUE;
                    }
                }

                if( b_BusyResponce == (boolean)TRUE )
                {
                    /* The processing order is set to eliminate dead code due to being fixed in the config. */
                    u1_AllowBusyResp = Dcm_BusyResponse(u2_RxPduId);
                    if( u1_AllowBusyResp == (Std_ReturnType)E_OK )
                    {
                        if( Dcm_Dsl_stDiagResp[0].bDiagRespOnSecondDeclinedRequest == (boolean)TRUE )
                        {
                            Dcm_Dsl_Ctrl_BusyTransmit(u2PduIdMapIndex, DCM_E_BUSYREPEATREQUEST);
                        }
                        else
                        {
                            Dcm_Dsl_Ctrl_RxErrNotification(u2PduIdMapIndex);
                        }
                    }
                    else
                    {
                        Dcm_Dsl_Ctrl_RxErrNotification(u2PduIdMapIndex);
                    }
                }
            }
        }
    }

    if( b_ChangeClient == (boolean)TRUE )
    {
        /* The processing order is set to eliminate dead code due to being fixed in the config. */
        u1_ChgClientResult = Dcm_ChangeClient(u2_ActiveRxPduId, u2_RxPduId);
        if( Dcm_Dsl_stCbkDCMRequestService[0].bClientChangeNotifUsed == (boolean)FALSE )
        {
            u1_ChgClientResult = (Std_ReturnType)E_OK;
        }

        if( u1_ChgClientResult == (Std_ReturnType)E_OK )
        {
            Dcm_Dsl_Ctrl_ChgInteractiveClient();
            Dcm_Dsl_Ctrl_Accept(u2PduIdMapIndex);
        }
        else if( u1_ChgClientResult == (Std_ReturnType)E_NOT_OK )
        {
            Dcm_Dsl_Ctrl_BusyTransmit( u2PduIdMapIndex, DCM_E_CONDITIONSNOTCORRECT );
        }
        else /* u1_ChgClientResult == (Std_ReturnType)E_REQUEST_NOT_ACCEPTED */
        {
            Dcm_Dsl_Ctrl_RxErrNotification(u2PduIdMapIndex);
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_RxAbt_ProcKeepAliveReq                           */
/* Description   | This function processes KAL                              */
/* Preconditions | RxState == DCM_DSL_RX_ST_KAL Only                        */
/* Parameters    | [in] u2PduIdMapIndex : Management number of PduId        */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_RxAbt_ProcKeepAliveReq
(
    const uint16 u2PduIdMapIndex
)
{
    Dcm_Dsl_Ctrl_ProcKeepAliveReq(u2PduIdMapIndex);
    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_RxAbt_ArbitrateRxIndPseudoKAL                    */
/* Description   | This function determines and arbitrates KAL              */
/* Preconditions | RxState == DCM_DSL_RX_ST_PSEUDOKAL Only                  */
/* Parameters    | [in] u2PduIdMapIndex : Management number of PduId        */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_RxAbt_ArbitrateRxIndPseudoKAL
(
    const uint16 u2PduIdMapIndex
)
{
    Dcm_Dsl_RxResInfoType  st_BufferInfo;
    AB_83_DcmPduInfoType   st_KALInfo;
    uint8                  u1_Cnt;
    boolean                b_KeepAliveMsg;
    boolean                b_ResourceInUse;
    boolean                b_DslActive;
    boolean                b_BusyServiceToRespondTo;

    st_KALInfo.SduDataPtr = NULL_PTR;
    st_KALInfo.SduLength  = (AB_83_DcmPduLengthType)0U;

    Dcm_Dsl_Ctrl_GetKALResource(u2PduIdMapIndex, &st_KALInfo);
    b_KeepAliveMsg = Dcm_Dsl_Ctrl_IsDirectKeepAliveMsg(u2PduIdMapIndex, &st_KALInfo);
    if( b_KeepAliveMsg == (boolean)TRUE )
    {
        Dcm_Dsl_RxAbt_ProcKeepAliveReq(u2PduIdMapIndex);
    }
    else
    {
        b_BusyServiceToRespondTo = Dcm_Dsl_Ctrl_IsBusyServiceToRespondTo(u2PduIdMapIndex);
        if( b_BusyServiceToRespondTo == (boolean)FALSE )
        {
            b_DslActive = Dcm_Dsl_Ctrl_IsActiveClient(u2PduIdMapIndex);
            if( b_DslActive == (boolean)FALSE )
            {
                b_ResourceInUse = Dcm_Dsl_Ctrl_IsResourceInUse(u2PduIdMapIndex);
                if( b_ResourceInUse == (boolean)FALSE )
                {
                    Dcm_Dsl_Ctrl_NotifyPseudoKALasNoKAL(u2PduIdMapIndex);
                    Dcm_Dsl_Ctrl_GetCurRxResource(u2PduIdMapIndex, &st_BufferInfo);

                    /* Since the size of the buffer is 8 bytes or more, 2 bytes can be copied. */
                    for( u1_Cnt = (uint8)0U; u1_Cnt < DCM_DSL_KEEPALIVE_LEN; u1_Cnt++ )
                    {
                        st_BufferInfo.ptRxPduInfo->SduDataPtr[u1_Cnt] = st_KALInfo.SduDataPtr[u1_Cnt];
                    }
                    st_BufferInfo.ptRxPduInfo->SduLength  = DCM_DSL_KEEPALIVE_LEN;
                    Dcm_Dsl_RxAbt_ArbitrateRxInd(u2PduIdMapIndex);
                }
                else
                {
                    Dcm_Dsl_Ctrl_RxErrNotification(u2PduIdMapIndex);
                }
            }
            else
            {
                Dcm_Dsl_Ctrl_RxErrNotification(u2PduIdMapIndex);
            }
        }
        else
        {
            Dcm_Dsl_Ctrl_RxErrNotification(u2PduIdMapIndex);
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_RxAbt_GetRxResource                              */
/* Description   | This function acquires the receiving resource assigned   */
/*               | to the specified ID.                                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex    : PduMapIndex Value                */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK                  : Success                        */
/*               |   E_NOT_OK              : Failure                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_RxAbt_GetRxResource
(
    const uint16 u2PduMapIndex
)
{
    return Dcm_Dsl_Ctrl_GetRxResource(u2PduMapIndex);
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_RxAbt_GetCurRxResource                           */
/* Description   | This function gets the current value of the receiving    */
/*               | resource.                                                */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               | [out] ptBufferInfo : RxBuffer Address/RxMsg Length       */
/*               |                      RxBuffer Remaining Size             */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_RxAbt_GetCurRxResource
(
    const uint16 u2PduMapIndex,
    P2VAR(Dcm_Dsl_RxResInfoType, AUTOMATIC, DCM_APPL_DATA) ptBufferInfo
)
{
    Dcm_Dsl_Ctrl_GetCurRxResource(u2PduMapIndex, ptBufferInfo);

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_RxAbt_GetCurKALResource                          */
/* Description   | This function gets the current value of the receiving    */
/*               | resource.                                                */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               | [out] ptBufferInfo : RxBuffer Address/RxMsg Length       */
/*               |                      RxBuffer Remaining Size             */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_RxAbt_GetCurKALResource
(
    const uint16 u2PduMapIndex,
    P2VAR(Dcm_Dsl_RxResInfoType, AUTOMATIC, DCM_APPL_DATA) ptBufferInfo
)
{
    Dcm_Dsl_Ctrl_GetCurKALResource(u2PduMapIndex, ptBufferInfo);

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_RxAbt_RxErrNotification                          */
/* Description   | This function performs processing at the time of         */
/*               | receiving error notification.                            */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/* Return Value  | none                                                     */
/* Notes         |  -                                                       */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_RxAbt_RxErrNotification
(
    const uint16 u2PduIdMapIndex
)
{
    Dcm_Dsl_Ctrl_RxErrNotification(u2PduIdMapIndex);

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_RxAbt_IsReceivingClient                          */
/* Description   | This function checks if the specified client is          */
/*               | receiving.                                               */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  |                                                          */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_Dsl_RxAbt_IsReceivingClient
(
    const uint16 u2PduIdMapIndex
)
{
    boolean b_RetVal;

    b_RetVal = Dcm_Dsl_RxMsg_IsReceivingClient(u2PduIdMapIndex);

    return b_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_RxAbt_IsReceivingDiag                            */
/* Description   | This function checks whether all PduIds are receiving.   */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | boolean                                                  */
/*               |      TRUE:   Receiving                                   */
/*               |      FALSE:  Idle                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_Dsl_RxAbt_IsReceivingDiag
(void)
{
    boolean b_RetVal;

    b_RetVal = Dcm_Dsl_RxMsg_IsReceivingDiag();

    return b_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_RxAbt_Init                                       */
/* Description   | This function initializes Dsl_RxAbt.                     */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_RxAbt_Init
(void)
{
    return;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Dcm_Dsl_RxAbt_ArbitrateSORCore                           */
/* Description   | This function is the core of SOR arbitration processing. */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduIdMapIndex : Management number of PduId        */
/*               | [in] u1ReqKind       : Request kind                      */
/* Return Value  | boolean                                                  */
/*               |     TRUE  : Allow request                                */
/*               |     FALSE : Request NG                                   */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_Dsl_RxAbt_ArbitrateSORCore
(
    const uint16 u2PduIdMapIndex,
    const uint8 u1ReqKind
)
{
#if( DCM_DSL_ARBT_TYPE1 == STD_OFF )
    uint16  u2_ActivePduIdMapIndex;
    uint8   u1_PriorityCompResult;
    boolean b_ActiveSession;
#endif /* DCM_DSL_ARBT_TYPE1 == STD_OFF */
    boolean b_DslActive;
    boolean b_ResourceInUse;
    boolean b_RetVal;
    boolean b_SameClient;
    boolean b_BusyServiceToRespondTo;

    b_RetVal = (boolean)FALSE;

    if( u1ReqKind != DCM_DSL_RX_REQ_NORMAL )
    {
        b_RetVal = (boolean)TRUE;
    }
    else
    {
        b_BusyServiceToRespondTo = Dcm_Dsl_Ctrl_IsBusyServiceToRespondTo(u2PduIdMapIndex);
        if( b_BusyServiceToRespondTo == (boolean)FALSE )
        {
            b_DslActive = Dcm_Dsl_Ctrl_IsActiveClient(u2PduIdMapIndex);
            if( b_DslActive == (boolean)FALSE )
            {
                b_ResourceInUse = Dcm_Dsl_Ctrl_IsResourceInUse(u2PduIdMapIndex);
                if( b_ResourceInUse == (boolean)FALSE )
                {
                    b_SameClient = Dcm_Dsl_Ctrl_IsRecvInteractiveClient(u2PduIdMapIndex);
                    if( b_SameClient == (boolean)TRUE )
                    {
                        b_RetVal = (boolean)TRUE;
                    }
                    else
                    {
#if( DCM_DSL_ARBT_TYPE1 == STD_ON )
                        b_RetVal = (boolean)TRUE;
#endif /* DCM_DSL_ARBT_TYPE1 == STD_ON */

#if( DCM_DSL_ARBT_TYPE1 == STD_OFF )
                        b_ActiveSession = Dcm_Dsl_Ctrl_IsActiveSession();
                        if( b_ActiveSession == (boolean)TRUE )
                        {
                            u2_ActivePduIdMapIndex = Dcm_Dsl_Ctrl_GetRxPduMapIndex();
                            u1_PriorityCompResult  = Dcm_Dsl_RxAbt_GetPrioCompResult(u2PduIdMapIndex, u2_ActivePduIdMapIndex);
                            if( u1_PriorityCompResult == DCM_DSL_PRIORITY_HIGH )
                            {
                                b_RetVal = (boolean)TRUE;
                            }
                        }
                        else
                        {
                            b_RetVal = (boolean)TRUE;
                        }
#endif /* DCM_DSL_ARBT_TYPE1 == STD_OFF */
                    }
                }
            }
        }
    }

    return b_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_RxAbt_GetPrioCompResult                          */
/* Description   | This function compares request id and active id client   */
/*               | priority.                                                */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2ReqPduIdMapIndex:                                 */
/*               |             Management number of request PduId           */
/*               | [in] u2ActivePduIdMapIndex:                              */
/*               |             Management number of active PduId            */
/* Return Value  | uint8                                                    */
/*               |     DCM_DSL_PRIORITY_HIGH : Request id has high priority */
/*               |     DCM_DSL_PRIORITY_EQUAL: Request id has Same priority */
/*               |     DCM_DSL_PRIORITY_LOW  : Request id has low priority  */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(uint8, DCM_CODE) Dcm_Dsl_RxAbt_GetPrioCompResult
(
    const uint16 u2ReqPduIdMapIndex,
    const uint16 u2ActivePduIdMapIndex
)
{
    uint8 u1_RetVal;
    uint8 u1_ReqClientPriority;
    uint8 u1_ActiveClientPriority;

    u1_ReqClientPriority    = Dcm_Dsl_Ctrl_GetConnectionPriority(u2ReqPduIdMapIndex);
    u1_ActiveClientPriority = Dcm_Dsl_Ctrl_GetConnectionPriority(u2ActivePduIdMapIndex);

    if( u1_ReqClientPriority < u1_ActiveClientPriority )
    {
        u1_RetVal = DCM_DSL_PRIORITY_HIGH;
    }
    else if( u1_ReqClientPriority == u1_ActiveClientPriority )
    {
        u1_RetVal = DCM_DSL_PRIORITY_EQUAL;
    }
    else /* u1_ReqClientPriority > u1_ActiveClientPriority */
    {
        u1_RetVal = DCM_DSL_PRIORITY_LOW;
    }

    return u1_RetVal;
}

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v3-0-0         :2019-05-29                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2022-12-23                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-10-0        :2025-08-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
