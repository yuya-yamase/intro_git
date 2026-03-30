/* Dcm_Dsl_RxMsg_c(v5-10-0)                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsl_RxMsg/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../../Dsl/inc/Dcm_Dsl_RxMsg.h"
#include "../../Dsl/inc/Dcm_Dsl_RxAbt.h"
#include "../../Dsl/inc/Dcm_Dsl_CommHandling.h"
#include "../../Dsl/inc/Dcm_Dsl_Ctrl_local.h"
#include "../../Dsl/inc/Dcm_Dsl_Main.h"
#include "../../Dsl/usr/Dcm_Dsl_RxMsg_Connector.h"
#include <Dcm/Dcm_Main_EvtDistr.h>
#include <Dcm/Dcm_Dsl_Ctrl.h>
#include <Dcm/Dcm_Main_Common.h>
#include <Dcm/Dcm_Main_TmrSrv.h>
#include <SchM_Dcm.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSL_RXMSG_COPY_1ST_BYTE         ((uint8)0x00U)
#define DCM_DSL_RXMSG_COPY_2ND_BYTE         ((uint8)0x01U)
#define DCM_DSL_RXMSG_COPY_SIZE             ((uint8)0x02U)

#define DCM_DSL_RX_ST_IDLE                  ((uint8)0x11U)
#define DCM_DSL_RX_ST_KAL                   ((uint8)0x12U)
#define DCM_DSL_RX_ST_PSEUDOKAL             ((uint8)0x13U)
#define DCM_DSL_RX_ST_RECEIVE               ((uint8)0x21U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_Dsl_RxMsg_StartOfReceptionCore
(
    const PduIdType uvId,
    P2CONST(AB_83_DcmPduInfoType , AUTOMATIC, DCM_APPL_DATA) ptInfo,
    P2VAR(AB_83_DcmPduLengthType, AUTOMATIC, DCM_APPL_DATA) ptBufferSizePtr
);

static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_Dsl_RxMsg_CopyRxDataCore
(
    const PduIdType uvId,
    P2CONST(AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA) ptInfo,
    P2VAR(AB_83_DcmPduLengthType, AUTOMATIC, DCM_APPL_DATA) ptBufferSizePtr
);

static FUNC( void, DCM_CODE ) Dcm_Dsl_RxMsg_CopyData
(
    const uint16 u2PduIdMapIndex,
    P2CONST(AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA) ptInfo,
    P2VAR(AB_83_DcmPduLengthType, AUTOMATIC, DCM_APPL_DATA) ptBufferSizePtr,
    P2VAR(Dcm_Dsl_RxResInfoType, AUTOMATIC, DCM_APPL_DATA) ptBufferInfo
);

static FUNC(boolean, DCM_CODE ) Dcm_Dsl_RxMsg_IsParallelRx
(void);


#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

static VAR(volatile boolean, DCM_VAR_NO_INIT) Dcm_Dsl_bCancelRxFlag;
static VAR(volatile uint8, DCM_VAR_NO_INIT) Dcm_Dsl_u1RxState[DCM_DSL_PDUID_NUM];

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
/* Function Name | Dcm_StartOfReception                                     */
/* Description   | This function is called at the start of receiving.       */
/* Preconditions | none                                                     */
/* Parameters    | [in] id              : PduId(Rx)                         */
/*               | [in] info            : RxData information                */
/*               | [in] TpSduLength     : Total Length from PduR            */
/*               | [out] bufferSizePtr  : The length that Dcm can receive   */
/*               |                                                          */
/* Return Value  | BufReq_ReturnType                                        */
/*               |     BUFREQ_OK        : Connection has been accepted      */
/*               |     BUFREQ_E_NOT_OK  : Connection has been rejected      */
/*               |     BUFREQ_E_OVFL    : No buffer of the required length  */
/*               |                        can be provided                   */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(BufReq_ReturnType, DCM_CODE) Dcm_StartOfReception
(
    PduIdType id,
    P2CONST(PduInfoType, AUTOMATIC, DCM_APPL_DATA) info,
    PduLengthType TpSduLength,
    P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) bufferSizePtr
)
{
    P2CONST(AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA) pt_Info;
    AB_83_DcmPduInfoType    st_Info;
    AB_83_DcmPduLengthType  u4_bufferSizePtr;
    BufReq_ReturnType       u1_RetVal;

    st_Info.SduLength  = (AB_83_DcmPduLengthType)TpSduLength;
    if( info != NULL_PTR )
    {
        st_Info.SduDataPtr = info->SduDataPtr;
    }
    else
    {
        st_Info.SduDataPtr = NULL_PTR;
    }
    pt_Info = &st_Info;

    u1_RetVal = Dcm_Dsl_RxMsg_StartOfReceptionCore(id, pt_Info, &u4_bufferSizePtr);
    if( u1_RetVal == (BufReq_ReturnType)BUFREQ_OK )
    {
        if( bufferSizePtr != NULL_PTR )
        {
            *bufferSizePtr = (PduLengthType)u4_bufferSizePtr;
        }
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_StartOfReception32                                   */
/* Description   | This function is called at the start of receiving.       */
/* Preconditions | none                                                     */
/* Parameters    | [in] id              : PduId(Rx)                         */
/*               | [in] info            : RxData information                */
/*               | [in] TpSduLength     : Total Length from PduR            */
/*               | [out] bufferSizePtr  : The length that Dcm can receive   */
/*               |                                                          */
/* Return Value  | BufReq_ReturnType                                        */
/*               |     BUFREQ_OK        : Connection has been accepted      */
/*               |     BUFREQ_E_NOT_OK  : Connection has been rejected      */
/*               |     BUFREQ_E_OVFL    : No buffer of the required length  */
/*               |                        can be provided                   */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(BufReq_ReturnType, DCM_CODE) Dcm_StartOfReception32
(
    PduIdType id,
    P2CONST(AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA) info,
    AB_83_DcmPduLengthType TpSduLength,
    P2VAR(AB_83_DcmPduLengthType, AUTOMATIC, DCM_APPL_DATA) bufferSizePtr
)
{
    P2CONST(AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA) pt_Info;
    AB_83_DcmPduInfoType    st_Info;
    AB_83_DcmPduLengthType  u4_bufferSizePtr;
    BufReq_ReturnType       u1_RetVal;

    st_Info.SduLength  = TpSduLength;
    if( info != NULL_PTR )
    {
        st_Info.SduDataPtr = info->SduDataPtr;
    }
    else
    {
        st_Info.SduDataPtr = NULL_PTR;
    }
    pt_Info = &st_Info;

    u1_RetVal = Dcm_Dsl_RxMsg_StartOfReceptionCore(id, pt_Info, &u4_bufferSizePtr);
    if( u1_RetVal == (BufReq_ReturnType)BUFREQ_OK )
    {
        if( bufferSizePtr != NULL_PTR )
        {
            *bufferSizePtr = u4_bufferSizePtr;
        }
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_CopyRxData                                           */
/* Description   | This function is called to provide the received data.    */
/*               | the message.                                             */
/* Preconditions | none                                                     */
/* Parameters    | [in] id                : PduId(Rx)                       */
/*               | [in] info              : Received data information       */
/*               | [in/out] bufferSizePtr : Available receive buffer after  */
/*               |                          data has been copied(Length).   */
/*               |                                                          */
/* Return Value  | BufReq_ReturnType                                        */
/*               |     BUFREQ_OK       : Data copied successfully           */
/*               |     BUFREQ_E_NOT_OK : Data was not copied because an     */
/*               |                       error occurred                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(BufReq_ReturnType, DCM_CODE) Dcm_CopyRxData
(
    PduIdType id,
    P2CONST(PduInfoType, AUTOMATIC, DCM_APPL_DATA) info,
    P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) bufferSizePtr
)
{
    BufReq_ReturnType       u1_RetVal;
    AB_83_DcmPduInfoType    st_InfoCore;
    AB_83_DcmPduLengthType  u4_bufferSizePtr;
    P2CONST(AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA) pt_Info;

    if( info != NULL_PTR )
    {
        st_InfoCore.SduDataPtr = info->SduDataPtr;
        st_InfoCore.SduLength  = info->SduLength;
        pt_Info                = &st_InfoCore;
    }
    else
    {
        pt_Info = NULL_PTR;
    }

    u1_RetVal = Dcm_Dsl_RxMsg_CopyRxDataCore(id, pt_Info, &u4_bufferSizePtr);
    if( u1_RetVal == (BufReq_ReturnType)BUFREQ_OK )
    {
        if( bufferSizePtr != NULL_PTR )
        {
            *bufferSizePtr = (PduLengthType)u4_bufferSizePtr;
        }
    }
    else
    {
        /* none */
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_CopyRxData32                                         */
/* Description   | This function is called to provide the received data.    */
/*               | the message.                                             */
/* Preconditions | none                                                     */
/* Parameters    | [in] id                : PduId(Rx)                       */
/*               | [in] info              : Received data information       */
/*               | [in/out] bufferSizePtr : Available receive buffer after  */
/*               |                          data has been copied(Length).   */
/*               |                                                          */
/* Return Value  | BufReq_ReturnType                                        */
/*               |     BUFREQ_OK       : Data copied successfully           */
/*               |     BUFREQ_E_NOT_OK : Data was not copied because an     */
/*               |                       error occurred                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(BufReq_ReturnType, DCM_CODE) Dcm_CopyRxData32
(
    PduIdType id,
    P2CONST(AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA) info,
    P2VAR(AB_83_DcmPduLengthType, AUTOMATIC, DCM_APPL_DATA) bufferSizePtr
)
{
    BufReq_ReturnType u1_RetVal;
    AB_83_DcmPduLengthType u4_bufferSizePtr;

    u1_RetVal = Dcm_Dsl_RxMsg_CopyRxDataCore(id, info, &u4_bufferSizePtr);
    if( u1_RetVal == (BufReq_ReturnType)BUFREQ_OK )
    {
        if( bufferSizePtr != NULL_PTR )
        {
            *bufferSizePtr = u4_bufferSizePtr;
        }
    }
    else
    {
        /* none */
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_TpRxIndication                                       */
/* Description   | Called after an I-PDU has been received.                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] id     : PduId(Rx)                                  */
/*               | [in] result : Results on whether the transmission was    */
/*               |               successful                                 */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_TpRxIndication
(
    PduIdType id,
    Std_ReturnType result
)
{
    uint32 u4_RxFailSafe;
    uint16 u2_PdurCount;
    uint16 u2_RxPduId;
    uint16 u2_PduIdNum;
    uint8  u1_RxState;
    boolean b_DslComEnable;
    boolean b_ParallelRx;

    u2_PduIdNum = Dcm_Dsl_u2PduIdNum;

    for( u2_PdurCount = (uint16)0 ; u2_PdurCount < u2_PduIdNum ; u2_PdurCount++ )
    {
        u2_RxPduId = Dcm_Dsl_PduIdMapTable[u2_PdurCount].RxPduId;
        if( id == u2_RxPduId )
        {
            break;
        }
        else
        {
            /* none */
        }
    }

    if( u2_PdurCount < u2_PduIdNum )
    {
        u1_RxState = Dcm_Dsl_u1RxState[u2_PdurCount];
        if( ( u1_RxState == DCM_DSL_RX_ST_KAL )
         || ( u1_RxState == DCM_DSL_RX_ST_PSEUDOKAL )
         || ( u1_RxState == DCM_DSL_RX_ST_RECEIVE ) )
        {
            Dcm_Main_TmrSrv_StopTimer(DCM_M_TMRID_RXFSTIMER);
            b_DslComEnable = Dcm_Dsl_CmHdl_IsComEnable(u2_PdurCount, DCM_DSL_COMTYPE_RECEIVE);
            if( b_DslComEnable == (boolean)TRUE )
            {
                if( result == (Std_ReturnType)E_OK )
                {
                    Dcm_Dsl_u1RxState[u2_PdurCount] = DCM_DSL_RX_ST_IDLE;

                    if( u1_RxState == DCM_DSL_RX_ST_KAL )
                    {
                        Dcm_Dsl_RxAbt_ProcKeepAliveReq(u2_PdurCount);
                    }
                    else if( u1_RxState == DCM_DSL_RX_ST_PSEUDOKAL )
                    {
                        Dcm_Dsl_RxAbt_ArbitrateRxIndPseudoKAL(u2_PdurCount);
                    }
                    else
                    {
                        Dcm_Dsl_RxAbt_ArbitrateRxInd(u2_PdurCount);
                    }

                    b_ParallelRx = Dcm_Dsl_RxMsg_IsParallelRx();
                    if( b_ParallelRx == (boolean)TRUE )
                    {
                        u4_RxFailSafe = Dcm_Dsl_stGeneral[0].u4FailSafeTimeout;
                        Dcm_Main_TmrSrv_StartTimer(DCM_M_TMRID_RXFSTIMER, u4_RxFailSafe);
                    }
                }
                else
                {
                    Dcm_Dsl_u1RxState[u2_PdurCount] = DCM_DSL_RX_ST_IDLE;
                    Dcm_Dsl_RxAbt_RxErrNotification(u2_PdurCount);
                    b_ParallelRx = Dcm_Dsl_RxMsg_IsParallelRx();
                    if( b_ParallelRx == (boolean)TRUE )
                    {
                        u4_RxFailSafe = Dcm_Dsl_stGeneral[0].u4FailSafeTimeout;
                        Dcm_Main_TmrSrv_StartTimer(DCM_M_TMRID_RXFSTIMER, u4_RxFailSafe);
                    }
                }
            }
            else
            {

               Dcm_Dsl_u1RxState[u2_PdurCount] = DCM_DSL_RX_ST_IDLE;
               Dcm_Dsl_RxAbt_RxErrNotification(u2_PdurCount);
               b_ParallelRx = Dcm_Dsl_RxMsg_IsParallelRx();
               if( b_ParallelRx == (boolean)TRUE )
               {
                   u4_RxFailSafe = Dcm_Dsl_stGeneral[0].u4FailSafeTimeout;
                   Dcm_Main_TmrSrv_StartTimer(DCM_M_TMRID_RXFSTIMER, u4_RxFailSafe);
               }
            }
        }
        else
        {
            /* none */
        }
    }
    else
    {
        /* none */
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_RxMsg_Init                                       */
/* Description   | This function initializes receive management data.       */
/*               |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  |                                                          */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_RxMsg_Init
(void)
{
    uint16 u2_PduIDNum_Cnt;
    uint16 u2_PduIdNum;

    u2_PduIdNum = Dcm_Dsl_u2PduIdNum;

    for( u2_PduIDNum_Cnt = (uint16)0U ; u2_PduIDNum_Cnt < u2_PduIdNum ; u2_PduIDNum_Cnt++ )
    {
        Dcm_Dsl_u1RxState[u2_PduIDNum_Cnt] = DCM_DSL_RX_ST_IDLE;
    }
    Dcm_Dsl_bCancelRxFlag             = (boolean)FALSE;

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_RxFailSafeTOCbk                                  */
/* Description   | This function is a failsafe timeout process.             */
/*               |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1TimerId : DCM_M_TMRID_RXFSTIMER                   */
/* Return Value  |                                                          */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_RxFailSafeTOCbk
(
    const uint8 u1TimerId /* MISRA DEVIATION */
)
{
    uint16 u2_PduIDNum_Cnt;
    uint16 u2_RowIndex;
    uint16 u2_ConnectionIndex;
    uint16 u2_ProtocolRxIndex;
    uint16 u2_CancelId;
    uint16 u2_PduIdNum;
    boolean b_CancelUsed;

    u2_PduIdNum = Dcm_Dsl_u2PduIdNum;

    Dcm_Dsl_bCancelRxFlag = (boolean)TRUE;
    for( u2_PduIDNum_Cnt = (uint16)0U ; u2_PduIDNum_Cnt < u2_PduIdNum ; u2_PduIDNum_Cnt++ )
    {
        if( (Dcm_Dsl_u1RxState[u2_PduIDNum_Cnt] == DCM_DSL_RX_ST_KAL)
         || (Dcm_Dsl_u1RxState[u2_PduIDNum_Cnt] == DCM_DSL_RX_ST_PSEUDOKAL)
         || (Dcm_Dsl_u1RxState[u2_PduIDNum_Cnt] == DCM_DSL_RX_ST_RECEIVE) )
        {
            b_CancelUsed = Dcm_Dsl_stRow[Dcm_Dsl_PduIdMapTable[u2_PduIDNum_Cnt].u2RowIndex].bCommunicationCancelUsed;
            if( b_CancelUsed == (boolean)TRUE )
            {
                Dcm_Dsl_Ctrl_ConvPMIdxToPrtclRxIdx(u2_PduIDNum_Cnt, &u2_RowIndex, &u2_ConnectionIndex, &u2_ProtocolRxIndex);
                u2_CancelId = Dcm_Dsl_stRow[u2_RowIndex].ptConnection[u2_ConnectionIndex].ptMainConnection[0].ptProtocolRx[u2_ProtocolRxIndex].RxPdu;
                /* Return value ignoring */
                (void)Dcm_Dsl_Cnct_CancelReceive(u2_CancelId);
            }
            Dcm_Dsl_u1RxState[u2_PduIDNum_Cnt] = DCM_DSL_RX_ST_IDLE;
            Dcm_Dsl_RxAbt_RxErrNotification(u2_PduIDNum_Cnt);
        }
        else
        {
            Dcm_Dsl_u1RxState[u2_PduIDNum_Cnt] = DCM_DSL_RX_ST_IDLE;
        }
    }
    Dcm_Dsl_bCancelRxFlag = (boolean)FALSE;

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_CancelReceiveCbk                                 */
/* Description   | This function is a failsafe timeout process.             */
/*               |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1EventId : DCM_M_EVTID_DSL_CANCELRECEIVE           */
/* Return Value  |                                                          */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_CancelReceiveCbk
(
    const uint8 u1EventId /* MISRA DEVIATION */
)
{
    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_RxMsg_IsReceivingClient                          */
/* Description   | This function checks if the specified client is          */
/*               | receiving.                                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2RxPduMapIndex : PduMapIndex Value                 */
/* Return Value  | boolean                                                  */
/*               |      TRUE:   Receiving                                   */
/*               |      FALSE:  Idle                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_Dsl_RxMsg_IsReceivingClient
(
    const uint16 u2PduIdMapIndex
)
{
    boolean b_RetVal;
    uint16 u2_PduIDNum_Cnt;
    uint16 u2_PduIdNum;
    uint16 u2_ActiveGroup;
    uint16 u2_ReqGroup;

    u2_PduIdNum    = Dcm_Dsl_u2PduIdNum;
    b_RetVal       = (boolean)FALSE;
    u2_ActiveGroup = Dcm_Dsl_Ctrl_GetConnectionGroup(u2PduIdMapIndex);

    for( u2_PduIDNum_Cnt = (uint16)0U ; u2_PduIDNum_Cnt < u2_PduIdNum ; u2_PduIDNum_Cnt++ )
    {
        u2_ReqGroup = Dcm_Dsl_Ctrl_GetConnectionGroup(u2_PduIDNum_Cnt);
        if( u2_ActiveGroup == u2_ReqGroup )
        {
            if( Dcm_Dsl_u1RxState[u2_PduIDNum_Cnt] != DCM_DSL_RX_ST_IDLE )
            {
                b_RetVal = (boolean)TRUE;
                break;
            }
        }
    }

    return b_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_RxMsg_IsReceivingDiag                            */
/* Description   | This function checks whether all PduIds are receiving.   */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | boolean                                                  */
/*               |      TRUE:   Receiving                                   */
/*               |      FALSE:  Idle                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_Dsl_RxMsg_IsReceivingDiag
(void)
{
    boolean b_RetVal;
    uint16 u2_PduIDNum_Cnt;
    uint16 u2_PduIdNum;

    u2_PduIdNum = Dcm_Dsl_u2PduIdNum;

    b_RetVal = (boolean)FALSE;
    for( u2_PduIDNum_Cnt = (uint16)0U ; u2_PduIDNum_Cnt < u2_PduIdNum ; u2_PduIDNum_Cnt++ )
    {
        if( Dcm_Dsl_u1RxState[u2_PduIDNum_Cnt] != DCM_DSL_RX_ST_IDLE )
        {
            b_RetVal = (boolean)TRUE;
            break;
        }
    }

    return b_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_RxMsg_Refresh                                    */
/* Description   | This function refresh RxMsg Status.                      */
/* Preconditions | The user must exclude this access data.                  */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_RxMsg_Refresh
(void)
{
    P2VAR(volatile boolean, AUTOMATIC, DCM_APPL_DATA) pt_CancelRxFlag;
    P2VAR(volatile uint8, AUTOMATIC, DCM_APPL_DATA)   pt_RxState;
    uint16  u2_PduIDNum_Cnt;
    uint16 u2_PduIdNumMax;
    uint8   u1_RxState;
    boolean b_CancelRxFlag;

    u2_PduIdNumMax = Dcm_Dsl_u2PduIdNum;

    for( u2_PduIDNum_Cnt = (uint16)0U; u2_PduIDNum_Cnt < u2_PduIdNumMax; u2_PduIDNum_Cnt++ )
    {
        pt_RxState  = &Dcm_Dsl_u1RxState[u2_PduIDNum_Cnt];
        u1_RxState  = *pt_RxState;
        *pt_RxState = u1_RxState;
    }

    pt_CancelRxFlag  = &Dcm_Dsl_bCancelRxFlag;
    b_CancelRxFlag   = *pt_CancelRxFlag;
    *pt_CancelRxFlag = b_CancelRxFlag;
    return ;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Dcm_Dsl_RxMsg_StartOfReceptionCore                       */
/* Description   | This function is called at the start of receiving.       */
/* Preconditions | none                                                     */
/* Parameters    | [in] uvId              : PduId(Rx)                       */
/*               | [in] ptInfo            : RxData information              */
/*               | [out] ptBufferSizePtr  : The length that Dcm can receive */
/*               |                                                          */
/* Return Value  | BufReq_ReturnType                                        */
/*               |     BUFREQ_OK        : Connection has been accepted      */
/*               |     BUFREQ_E_NOT_OK  : Connection has been rejected      */
/*               |     BUFREQ_E_OVFL    : No buffer of the required length  */
/*               |                        can be provided                   */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_Dsl_RxMsg_StartOfReceptionCore
(
    const PduIdType uvId,
    P2CONST(AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA) ptInfo,
    P2VAR(AB_83_DcmPduLengthType, AUTOMATIC, DCM_APPL_DATA) ptBufferSizePtr
)
{
    AB_83_DcmPduLengthType u4_RxBufSize;
    BufReq_ReturnType u1_RetVal;
    uint32  u4_RxFailSafe;
    uint16  u2_PdurCount;
    uint16  u2_PduIdNum;
    uint8   u1_ReqKind;
    PduIdType u2_RxPduId;
    Std_ReturnType u1_MallocResult;
    boolean b_OverwriteSOR;
    boolean b_DslComEnable;
    boolean b_KeepAliveMsg;
    boolean b_RxAbtResult;
    boolean b_CancelRxFlag;

    u2_PduIdNum = Dcm_Dsl_u2PduIdNum;
    u1_RetVal   = BUFREQ_E_NOT_OK;

    for( u2_PdurCount = (uint16)0 ; u2_PdurCount < u2_PduIdNum ; u2_PdurCount++ )
    {
        u2_RxPduId = Dcm_Dsl_PduIdMapTable[u2_PdurCount].RxPduId;
        if( uvId == u2_RxPduId )
        {
            break;
        }
    }

    if( u2_PdurCount < u2_PduIdNum )
    {
        b_DslComEnable = Dcm_Dsl_CmHdl_IsComEnable(u2_PdurCount, DCM_DSL_COMTYPE_RECEIVE);
        if( b_DslComEnable == (boolean)TRUE )
        {
            b_CancelRxFlag = Dcm_Dsl_bCancelRxFlag;
            if( b_CancelRxFlag == (boolean)FALSE )
            {
                if( ptInfo->SduLength == (AB_83_DcmPduLengthType)0 )
                {
                    u4_RxBufSize = Dcm_Dsl_Ctrl_GetRxBufSize(u2_PdurCount);
                    *ptBufferSizePtr = u4_RxBufSize;
                }
                else
                {
                    u4_RxBufSize = Dcm_Dsl_Ctrl_GetRxBufSize(u2_PdurCount);
                    if( ptInfo->SduLength <= u4_RxBufSize )
                    {
                        u1_ReqKind  = DCM_DSL_RX_REQ_OTHER;
                        if( Dcm_Dsl_u1RxState[u2_PdurCount] == DCM_DSL_RX_ST_IDLE )
                        {
                            b_OverwriteSOR = FALSE; /* before */
                        }
                        else
                        {
                            if( Dcm_Dsl_u1RxState[u2_PdurCount] == DCM_DSL_RX_ST_RECEIVE )
                            {
                                u1_ReqKind = DCM_DSL_RX_REQ_NORMAL;
                            }
                            b_OverwriteSOR = TRUE; /* after */
                        }

                        b_RxAbtResult = Dcm_Dsl_RxAbt_ArbitrateSOR(u2_PdurCount, ptInfo, b_OverwriteSOR, &u1_ReqKind);
                        if( b_RxAbtResult == (boolean)TRUE )
                        {
                            u1_MallocResult = Dcm_Dsl_RxAbt_GetRxResource(u2_PdurCount);
                            if( u1_MallocResult == (Std_ReturnType)E_OK )
                            {
                                if( u1_ReqKind == DCM_DSL_RX_REQ_NORMAL )
                                {
                                    Dcm_Dsl_u1RxState[u2_PdurCount] = DCM_DSL_RX_ST_RECEIVE;
                                    b_KeepAliveMsg = (boolean)FALSE;
                                }
                                else
                                {
                                    if( u1_ReqKind == DCM_DSL_RX_REQ_KAL )
                                    {
                                        Dcm_Dsl_u1RxState[u2_PdurCount] = DCM_DSL_RX_ST_KAL;
                                    }
                                    else
                                    {
                                        Dcm_Dsl_u1RxState[u2_PdurCount] = DCM_DSL_RX_ST_PSEUDOKAL;
                                    }
                                    b_KeepAliveMsg = (boolean)TRUE;
                                }
                                Dcm_Dsl_RxAbt_StartOfReception(u2_PdurCount, b_KeepAliveMsg);

                                *ptBufferSizePtr = u4_RxBufSize;
                                u1_RetVal = (BufReq_ReturnType)BUFREQ_OK;
                                u4_RxFailSafe = Dcm_Dsl_stGeneral[0].u4FailSafeTimeout;
                                Dcm_Main_TmrSrv_StartTimer(DCM_M_TMRID_RXFSTIMER, u4_RxFailSafe);
                            }
                            else
                            {
                                /* memory allocation error */
                                u1_RetVal = (BufReq_ReturnType)BUFREQ_E_OVFL;
                            }
                        }
                    }
                    else
                    {
                        u1_RetVal = (BufReq_ReturnType)BUFREQ_E_OVFL;
                    }
                }
            }
        }
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_RxMsg_CopyRxDataCore                             */
/* Description   | This function is called to provide the received data.    */
/*               | the message.                                             */
/* Preconditions | none                                                     */
/* Parameters    | [in] uvId               : PduId(Rx)                      */
/*               | [in] ptInfo             : Received data information      */
/*               | [in/out] ptBufferSizePtr: Available receive buffer after */
/*               |                          data has been copied(Length).   */
/*               |                                                          */
/* Return Value  | BufReq_ReturnType                                        */
/*               |     BUFREQ_OK       : Data copied successfully           */
/*               |     BUFREQ_E_NOT_OK : Data was not copied because an     */
/*               |                       error occurred                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_Dsl_RxMsg_CopyRxDataCore
(
    const PduIdType uvId,
    P2CONST(AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA) ptInfo,
    P2VAR(AB_83_DcmPduLengthType, AUTOMATIC, DCM_APPL_DATA) ptBufferSizePtr
)
{
    Dcm_Dsl_RxResInfoType st_BufferInfo;
    uint32 u4_RxFailSafe;
    uint16  u2_PdurCount;
    uint16  u2_RxPduId;
    uint16  u2_PduIdNum;
    uint8   u1_RxState;
    BufReq_ReturnType u1_RetVal;
    boolean b_DslComEnable;
    boolean b_ParallelRx;
    boolean b_Error;

    u2_PduIdNum = Dcm_Dsl_u2PduIdNum;
    b_Error     = (boolean)FALSE;
    u1_RetVal   = BUFREQ_E_NOT_OK;

    for( u2_PdurCount = (uint16)0 ; u2_PdurCount < u2_PduIdNum ; u2_PdurCount++ )
    {
        u2_RxPduId = Dcm_Dsl_PduIdMapTable[u2_PdurCount].RxPduId;
        if( uvId == u2_RxPduId )
        {
            break;
        }
        else
        {
            /* none */
        }
    }

    if( u2_PdurCount < u2_PduIdNum )
    {
        u1_RxState = Dcm_Dsl_u1RxState[u2_PdurCount];
        if( ( u1_RxState == DCM_DSL_RX_ST_KAL )
         || ( u1_RxState == DCM_DSL_RX_ST_PSEUDOKAL )
         || ( u1_RxState == DCM_DSL_RX_ST_RECEIVE ) )
        {
            Dcm_Main_TmrSrv_StopTimer(DCM_M_TMRID_RXFSTIMER);
            b_DslComEnable = Dcm_Dsl_CmHdl_IsComEnable(u2_PdurCount, DCM_DSL_COMTYPE_RECEIVE);
            if( b_DslComEnable == (boolean)TRUE )
            {
                if( ptInfo != NULL_PTR )
                {
                    if( ptInfo->SduLength == (AB_83_DcmPduLengthType)0 )
                    {
                        if( ( u1_RxState == DCM_DSL_RX_ST_KAL )
                         || ( u1_RxState == DCM_DSL_RX_ST_PSEUDOKAL ) )
                        {
                            Dcm_Dsl_RxAbt_GetCurKALResource(u2_PdurCount, &st_BufferInfo);
                        }
                        else
                        {
                            Dcm_Dsl_RxAbt_GetCurRxResource(u2_PdurCount, &st_BufferInfo);
                        }
                        u1_RetVal = BUFREQ_OK;
                        *ptBufferSizePtr = (AB_83_DcmPduLengthType)*(st_BufferInfo.ptRxSduLengthRmd);
                        u4_RxFailSafe = Dcm_Dsl_stGeneral[0].u4FailSafeTimeout;
                        Dcm_Main_TmrSrv_StartTimer(DCM_M_TMRID_RXFSTIMER, u4_RxFailSafe);
                    }
                    else
                    {
                        if( ptInfo->SduDataPtr != NULL_PTR )
                        {
                            if( ( u1_RxState == DCM_DSL_RX_ST_KAL )
                             || ( u1_RxState == DCM_DSL_RX_ST_PSEUDOKAL ) )
                            {
                                Dcm_Dsl_RxAbt_GetCurKALResource(u2_PdurCount, &st_BufferInfo);
                            }
                            else
                            {
                                Dcm_Dsl_RxAbt_GetCurRxResource(u2_PdurCount, &st_BufferInfo);
                            }

                            if( ptInfo->SduLength <= (AB_83_DcmPduLengthType)*(st_BufferInfo.ptRxSduLengthRmd) )
                            {
                                u1_RetVal = BUFREQ_OK;
                                Dcm_Dsl_RxMsg_CopyData(u2_PdurCount, ptInfo, ptBufferSizePtr, &st_BufferInfo);
                                u4_RxFailSafe = Dcm_Dsl_stGeneral[0].u4FailSafeTimeout;
                                Dcm_Main_TmrSrv_StartTimer(DCM_M_TMRID_RXFSTIMER, u4_RxFailSafe);
                            }
                            else
                            {
                                b_Error = (boolean)TRUE;
                            }
                        }
                        else
                        {
                            b_Error = (boolean)TRUE;
                        }
                    }
                }
                else
                {
                    b_Error = (boolean)TRUE;
                }
            }
            else
            {
                b_Error = (boolean)TRUE;
            }

            if( b_Error == (boolean)TRUE )
            {
                Dcm_Dsl_u1RxState[u2_PdurCount] = DCM_DSL_RX_ST_IDLE;
                Dcm_Dsl_RxAbt_RxErrNotification(u2_PdurCount);
                b_ParallelRx = Dcm_Dsl_RxMsg_IsParallelRx();
                if( b_ParallelRx == (boolean)TRUE )
                {
                    u4_RxFailSafe = Dcm_Dsl_stGeneral[0].u4FailSafeTimeout;
                    Dcm_Main_TmrSrv_StartTimer(DCM_M_TMRID_RXFSTIMER, u4_RxFailSafe);
                }
            }
        }
        else
        {
            /* none */
        }
    }
    else
    {
        /* none */
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_RxMsg_CopyData                                   */
/* Description   | Copy Received data in Rx Buffer.                         */
/* Preconditions | ptBufferInfo != NULL_PTR                                 */
/* Parameters    | [in] u2RxPduMapIndex : PduMapIndex Value                 */
/*               | [out] ptRxInfo       : Received data information         */
/*               | [out] ptBufferSizePtr  : Remain receive buffer length    */
/*               | [in,out] ptBufferInfo  : RxBuffer Info                   */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsl_RxMsg_CopyData
(
    const uint16 u2PduIdMapIndex,
    P2CONST(AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA) ptInfo,
    P2VAR(AB_83_DcmPduLengthType, AUTOMATIC, DCM_APPL_DATA) ptBufferSizePtr,
    P2VAR(Dcm_Dsl_RxResInfoType, AUTOMATIC, DCM_APPL_DATA) ptBufferInfo
)
{
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pt_SduDataPtr;
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pt_DstPtr;
    AB_83_DcmPduLengthType uv_SduLength;
    AB_83_DcmPduLengthType uv_CopySize;


    pt_SduDataPtr   = ptInfo->SduDataPtr;
    pt_DstPtr       = ptBufferInfo->ptRxPduInfo->SduDataPtr;
    uv_SduLength    = ptInfo->SduLength;
    uv_CopySize     = uv_SduLength;

    while( uv_CopySize >= (PduLengthType)DCM_DSL_RXMSG_COPY_SIZE )
    {
        /* Copy Data 1st byte */
        (pt_DstPtr[DCM_DSL_RXMSG_COPY_1ST_BYTE])    = (pt_SduDataPtr[DCM_DSL_RXMSG_COPY_1ST_BYTE]);
        /* Copy Data 2nd byte */
        (pt_DstPtr[DCM_DSL_RXMSG_COPY_2ND_BYTE])    = (pt_SduDataPtr[DCM_DSL_RXMSG_COPY_2ND_BYTE]);
        /* Update DstPtr */
        (pt_DstPtr)                                 = &pt_DstPtr[DCM_DSL_RXMSG_COPY_SIZE];
        /* Update SduDataPtr */
        (pt_SduDataPtr)                             = &pt_SduDataPtr[DCM_DSL_RXMSG_COPY_SIZE];
        /* Update Remain CopySize */
        uv_CopySize                                 -= DCM_DSL_RXMSG_COPY_SIZE;
    }
    if( uv_CopySize > (AB_83_DcmPduLengthType)0 )
    {
        /* Processing when there was a rest for 1 byte */
        /* Copy Data Index_0 */
        (pt_DstPtr[DCM_DSL_RXMSG_COPY_1ST_BYTE])    = (pt_SduDataPtr[DCM_DSL_RXMSG_COPY_1ST_BYTE]);
        /* Update DstPtr */
        (pt_DstPtr)                                 = &pt_DstPtr[DCM_DSL_RXMSG_COPY_2ND_BYTE];
    }

    ptBufferInfo->ptRxPduInfo->SduDataPtr           = pt_DstPtr;
    ptBufferInfo->ptRxPduInfo->SduLength            = ptBufferInfo->ptRxPduInfo->SduLength + uv_SduLength;    /* no wrap around */
    *(ptBufferInfo->ptRxSduLengthRmd)               = *(ptBufferInfo->ptRxSduLengthRmd) - uv_SduLength;    /* no wrap around */


    if( ptBufferSizePtr != NULL_PTR )
    {
        *ptBufferSizePtr                            = *(ptBufferInfo->ptRxSduLengthRmd);
    }

    return ;

}


/****************************************************************************/
/* Function Name | Dcm_Dsl_RxMsg_IsParallelRx                               */
/* Description   | This function judge whether or not parallel receive      */
/*               | is in progress.                                          */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | boolean                                                  */
/*               |     TRUE  : Parallel receive in progress                 */
/*               |     FALSE : No receive                                   */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(boolean, DCM_CODE ) Dcm_Dsl_RxMsg_IsParallelRx
(void)
{
    boolean b_RetVal;
    uint16 u2_PdurCount;
    uint16 u2_PduIdNum;

    u2_PduIdNum = Dcm_Dsl_u2PduIdNum;
    b_RetVal    = (boolean)FALSE;

    for( u2_PdurCount = (uint16)0 ; u2_PdurCount < u2_PduIdNum ; u2_PdurCount++ )
    {
        if( Dcm_Dsl_u1RxState[u2_PdurCount] != DCM_DSL_RX_ST_IDLE )
        {
            b_RetVal = (boolean)TRUE;
            break;
        }
        else
        {
            /* none */
        }
    }
    return b_RetVal;
}

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v3-0-0         :2019-07-29                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2022-12-23                                              */
/*  v5-10-0        :2025-08-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
