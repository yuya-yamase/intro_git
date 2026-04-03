/* Dcm_Dsl_Ctrl_PrtSrv_c(v5-8-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsl_Ctrl/CODE                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsl_Ctrl.h>
#include "../../Dsl/inc/Dcm_Dsl_Main.h"
#include "../../Dsl/inc/Dcm_Dsl_Ctrl_local.h"
#include "../../Dsl/inc/Dcm_Dsl_CommHandling.h"
#include "../../Dsl/inc/Dcm_Dsl_RxMsg.h"
#include "../../Dsl/inc/Dcm_Dsl_Main.h"

#include <SchM_Dcm.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>


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
/* Function Name | Dcm_GetActiveProtocol                                    */
/* Description   | This function returns the active protocol name           */
/*               | except for OBD Protocol.                                 */
/* Preconditions | none                                                     */
/* Parameters    | [out] ActiveProtocolType   : Active ProtocolId           */
/*               | [out] ConnectionId         : Active ConnectionId         */
/*               | [out] TesterSourceAddress  : RxTesterSource Address      */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : this value is always returned.             */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_GetActiveProtocol
(
    P2VAR( Dcm_ProtocolType, AUTOMATIC, DCM_APPL_DATA ) ActiveProtocolType,
    P2VAR( uint16, AUTOMATIC, DCM_APPL_DATA ) ConnectionId,
    P2VAR( uint16, AUTOMATIC, DCM_APPL_DATA ) TesterSourceAddress
)
{
    boolean        b_InteractiveClient;
    Std_ReturnType u1_RetVal;
    uint16         u2_PduMapIndex;
    uint16         u2_RowIndex;
    uint16         u2_ConnectionIndex;

    u1_RetVal           = E_OK;
    u2_PduMapIndex      = Dcm_Dsl_Ctrl_GetPduMapIndex();
    b_InteractiveClient = Dcm_Dsl_Ctrl_IsInteractiveClient(u2_PduMapIndex);
    Dcm_Dsl_Ctrl_ConvPMIdxToCnctIdx(u2_PduMapIndex, &u2_RowIndex, &u2_ConnectionIndex);

    if( b_InteractiveClient == (boolean)FALSE )
    {
        if( ActiveProtocolType != NULL_PTR )
        {
            *ActiveProtocolType = DCM_NO_ACTIVE_PROTOCOL;
        }

        if( ConnectionId != NULL_PTR )
        {
            *ConnectionId = DCM_DSL_INVALID_U2_DATA;
        }

        if( TesterSourceAddress != NULL_PTR )
        {
            *TesterSourceAddress = DCM_DSL_INVALID_U2_DATA;
        }
    }
    else
    {
        if( ActiveProtocolType != NULL_PTR )
        {
            if( Dcm_Dsl_PduIdMapTable[u2_PduMapIndex].u1ProtocolGroup == DCM_DSL_OBD_PROTOCOL )
            {
                *ActiveProtocolType = DCM_NO_ACTIVE_PROTOCOL;
            }
            else
            {
                *ActiveProtocolType = Dcm_Dsl_stRow[u2_RowIndex].u1ID;
            }
        }

        if( ConnectionId != NULL_PTR )
        {
            *ConnectionId = Dcm_Dsl_stRow[u2_RowIndex].ptConnection[u2_ConnectionIndex].ptMainConnection->u2ConnectionId;
        }

        if( TesterSourceAddress != NULL_PTR )
        {
            *TesterSourceAddress = Dcm_Dsl_stRow[u2_RowIndex].ptConnection[u2_ConnectionIndex].ptMainConnection->u2ProtocolRxTesterSourceAddr;
        }
    }

    return u1_RetVal;

}

/****************************************************************************/
/* Function Name | Dcm_GetRxPduID                                           */
/* Description   | Get a Received PduID.                                    */
/* Preconditions | none                                                     */
/* Parameters    | [out]ptRxPduId : Received PduID.                         */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : this value is always returned.             */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_GetRxPduID
(
    P2VAR( uint16, AUTOMATIC, DCM_APPL_DATA ) ptRxPduId
)
{
    boolean        b_InteractiveClient;
    Std_ReturnType u1_RetVal;
    uint16         u2_PduMapIndex;

    u1_RetVal           = E_OK;
    u2_PduMapIndex      = Dcm_Dsl_Ctrl_GetPduMapIndex();
    b_InteractiveClient = Dcm_Dsl_Ctrl_IsInteractiveClient(u2_PduMapIndex);

    if( ptRxPduId != NULL_PTR )
    {
        if( b_InteractiveClient == (boolean)FALSE )
        {
            *ptRxPduId = DCM_DSL_INVALID_U2_DATA;
        }
        else
        {
            *ptRxPduId = Dcm_Dsl_PduIdMapTable[u2_PduMapIndex].RxPduId;
        }
    }

    return u1_RetVal;
}

#if( DCM_ULDL_SERVICE_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsl_GetRxBufSize                                     */
/* Description   | This function acquires the receiving resource assigned   */
/*               | to the specified ID.                                     */
/* Preconditions | none                                                     */
/* Parameters    | [In]  u2RxPduId  : RxPduId                               */
/* Return Value  | Dcm_MsgLenType                                           */
/*               |   0x000008U-0xFFFFFFFFU : Success. RxBuffer Size         */
/*               |   0x000000U             : Failure.                       */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dcm_MsgLenType, DCM_CODE ) Dcm_Dsl_GetRxBufSize
(
    const PduIdType u2RxPduId
)
{
    Dcm_MsgLenType         u4_Result;
    uint16                 u2_PdurCount;
    uint16                 u2_PduIdNum;

    u2_PduIdNum = Dcm_Dsl_u2PduIdNum;
    u4_Result   = (Dcm_MsgLenType)0U;

    for( u2_PdurCount = (uint16)0U; u2_PdurCount < u2_PduIdNum; u2_PdurCount++ )
    {
        if( Dcm_Dsl_PduIdMapTable[u2_PdurCount].RxPduId == u2RxPduId )
        {
            break;
        }
    }

    if( u2_PdurCount < u2_PduIdNum )
    {
        u4_Result = (Dcm_MsgLenType)Dcm_Dsl_stRxBufferTable[u2_PdurCount].u4RxBufSize;
    }

    return u4_Result;
}

#endif /* DCM_ULDL_SERVICE_USE == STD_ON */

/* Because it is a function used only by SID28 */
#if( DCM_SUPPORT_SID28 == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsl_GetPduMapIndex                                   */
/* Description   | Call the function(Dcm_Dsl_Ctrl_GetPduMapIndex)           */
/*               | to get the Index of PduId for DSP.                       */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | uint16                                                   */
/*               |     0x0000U~0xFFFEU : Index of PduId for DSP             */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( uint16, DCM_CODE ) Dcm_Dsl_GetPduMapIndex
( void )
{
    uint16 u2_PduMapIndex;

    u2_PduMapIndex = Dcm_Dsl_Ctrl_GetPduMapIndex();

    return u2_PduMapIndex;

}
#endif /* DCM_SUPPORT_SID28 == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsl_SetComActive                                     */
/* Description   | This function activates the communication bus.           */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2ConnectionId : Connection ID(ClientIndex)         */
/*               | [in] bActive        : active state                       */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_SetComActive
(
    const uint16 u2ConnectionId,
    const boolean bActive
)
{
    uint16   u2_InteractiveClient;
    uint16   u2_PduMapIndex;
    uint16   u2_Cnt;
    uint16   u2_ClientNumMax;
    uint16   u2_ActivePduMapIndex;
    uint8    u1_RequestActive;
    uint8    u1_DslState;
    boolean  b_ActiveClient;

    if( u2ConnectionId == DCM_DSL_ALL_TARGETS )
    {
        u2_ClientNumMax      = Dcm_Dsl_u2ClientNum;
        u2_ActivePduMapIndex = Dcm_Dsl_Ctrl_GetPduMapIndex();
        u2_InteractiveClient = Dcm_Dsl_PduIdMapTable[u2_ActivePduMapIndex].u2ClientIndex;

        for( u2_Cnt = (uint16)0U; u2_Cnt < u2_ClientNumMax; u2_Cnt++ )
        {
            u2_PduMapIndex = Dcm_Dsl_ConnectionIdMapTable[u2_Cnt];

            u1_DslState = Dcm_Dsl_Ctrl_GetDslState(u2_PduMapIndex);
            if( ( u1_DslState == DCM_DSL_ST_IDLE )
             || ( u1_DslState == DCM_DSL_ST_RECEIVING ) )
            {
                if( u2_InteractiveClient == u2_Cnt )
                {
                    b_ActiveClient = (boolean)TRUE;
                }
                else
                {
                    b_ActiveClient= (boolean)FALSE;
                }
                /* Inactive Only */
                Dcm_Dsl_CmHdl_CallActive(u2_PduMapIndex, DCM_DSL_REQ_INACTIVE, b_ActiveClient);
            }
        }
    }
    else
    {
        u2_PduMapIndex = Dcm_Dsl_Ctrl_GetPduIdMapIndexByConnectionId(u2ConnectionId);
        if( u2_PduMapIndex != DCM_DSL_INVALID_U2_DATA )
        {
            if( bActive == (boolean)TRUE )
            {
                u1_RequestActive = DCM_DSL_REQ_ACTIVE;
            }
            else
            {
                u1_RequestActive = DCM_DSL_REQ_INACTIVE;
            }

            u1_DslState = Dcm_Dsl_Ctrl_GetDslState(u2_PduMapIndex);
            if( ( u1_DslState == DCM_DSL_ST_IDLE )
             || ( u1_DslState == DCM_DSL_ST_RECEIVING ) )
            {
                b_ActiveClient = Dcm_Dsl_Ctrl_IsInteractiveClient(u2_PduMapIndex);
                Dcm_Dsl_CmHdl_CallActive(u2_PduMapIndex, u1_RequestActive, b_ActiveClient);
            }
        }
    }

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_GetActiveProtocolGroup                           */
/* Description   | This function gets Protocol Group(OBD/NonOBD).           */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2ConnectionId   :  Connection ID(ClientIndex)      */
/* Return Value  | uint8                                                    */
/*               |        DCM_DSL_OBD_PROTOCOL : OBD Protocol.              */
/*               |        DCM_DSL_UDS_PROTOCOL : UDS Protocol.              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( uint8, DCM_CODE ) Dcm_Dsl_GetActiveProtocolGroup
(
    const uint16 u2ConnectionId
)
{
    uint16  u2_PduMapIndex;
    uint8   u1_Result;

    u1_Result = DCM_DSL_OBD_PROTOCOL;

    u2_PduMapIndex = Dcm_Dsl_Ctrl_GetPduIdMapIndexByConnectionId(u2ConnectionId);
    if( u2_PduMapIndex != DCM_DSL_INVALID_U2_DATA )
    {
        u1_Result = Dcm_Dsl_PduIdMapTable[u2_PduMapIndex].u1ProtocolGroup;
    }

    return u1_Result;
}

#if ( DCM_SUPPORT_SID10 == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsl_GetActiveProtocol                                */
/* Description   | This function returns the active protocol name           */
/*               | including OBD protocol.                                  */
/* Preconditions | none                                                     */
/* Parameters    | [out] ptActiveProtocolType   : Active ProtocolId         */
/*               | [out] ptConnectionId         : Active ConnectionId       */
/*               | [out] ptTesterSourceAddress  : RxTesterSource Address    */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_GetActiveProtocol
(
    P2VAR( Dcm_ProtocolType, AUTOMATIC, DCM_APPL_DATA ) ptActiveProtocolType,
    P2VAR( uint16, AUTOMATIC, DCM_APPL_DATA ) ptConnectionId,
    P2VAR( uint16, AUTOMATIC, DCM_APPL_DATA ) ptTesterSourceAddress
)
{
    uint16  u2_ConnectionIndex;
    uint16  u2_PduMapIndex;
    uint16  u2_RowIndex;
    boolean b_InteractiveClient;

    u2_PduMapIndex      = Dcm_Dsl_Ctrl_GetPduMapIndex();
    b_InteractiveClient = Dcm_Dsl_Ctrl_IsInteractiveClient(u2_PduMapIndex);
    Dcm_Dsl_Ctrl_ConvPMIdxToCnctIdx(u2_PduMapIndex, &u2_RowIndex, &u2_ConnectionIndex);

    if( b_InteractiveClient == (boolean)FALSE )
    {
        if( ptActiveProtocolType != NULL_PTR )
        {
            *ptActiveProtocolType = DCM_NO_ACTIVE_PROTOCOL;
        }

        if( ptConnectionId != NULL_PTR )
        {
            *ptConnectionId = DCM_DSL_INVALID_U2_DATA;
        }

        if( ptTesterSourceAddress != NULL_PTR )
        {
            *ptTesterSourceAddress = DCM_DSL_INVALID_U2_DATA;
        }
    }
    else
    {
        if( ptActiveProtocolType != NULL_PTR )
        {
            *ptActiveProtocolType = Dcm_Dsl_stRow[u2_RowIndex].u1ID;
        }

        if( ptConnectionId != NULL_PTR )
        {
            *ptConnectionId = Dcm_Dsl_stRow[u2_RowIndex].ptConnection[u2_ConnectionIndex].ptMainConnection[0].u2ConnectionId;
        }

        if( ptTesterSourceAddress != NULL_PTR )
        {
            *ptTesterSourceAddress = Dcm_Dsl_stRow[u2_RowIndex].ptConnection[u2_ConnectionIndex].ptMainConnection[0].u2ProtocolRxTesterSourceAddr;
        }
    }

    return ;
}
#endif /* DCM_SUPPORT_SID10 == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_SetActiveClient                                      */
/* Description   | This function set active client during a conversation.   */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2ConnectionId : Connection ID(ClientIndex)         */
/* Return Value  | Std_ReturnType                                           */
/*               |    E_OK : Sucessed                                       */
/*               |    E_NOT_OK : Failed                                     */
/*               |    E_REQUEST_NOT_ACCEPTED : Request Not Accepted         */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SetActiveClient
(
    const uint16 u2ConnectionId
)
{
    uint16         u2_PrePduMapIndex;
    uint16         u2_PostPduMapIndex;
    Std_ReturnType u1_RetVal;
    boolean        b_Active;
#if( DCM_AUTHENTICATION_USE == STD_ON )
    boolean        b_AuthTimeOut;
#endif /* DCM_AUTHENTICATION_USE == STD_ON */

    u1_RetVal      = E_NOT_OK;
    
    /* lock */
    SchM_Enter_Dcm_Dsl_Ctrl();
    
    u2_PrePduMapIndex = Dcm_Dsl_Ctrl_GetPduMapIndex();

    /* unlock */
    SchM_Exit_Dcm_Dsl_Ctrl();

    if( u2_PrePduMapIndex != DCM_DSL_INVALID_U2_DATA )
    {
        u2_PostPduMapIndex = Dcm_Dsl_Ctrl_GetPduIdMapIndexByConnectionId(u2ConnectionId);
        if( u2_PostPduMapIndex != DCM_DSL_INVALID_U2_DATA )
        {
            b_Active = Dcm_Dsl_Ctrl_IsActiveDiag();
            if( b_Active == (boolean)FALSE )
            {
                Dcm_Dsl_CmHdl_CallActive(u2_PrePduMapIndex, DCM_DSL_REQ_INACTIVE, (boolean)TRUE);

                /* lock */
                SchM_Enter_Dcm_Dsl_Ctrl();

                Dcm_Dsl_Ctrl_SetRxPduMapIndex(u2_PostPduMapIndex);
                Dcm_Dsl_Ctrl_SetPduMapIndex(u2_PostPduMapIndex);

                /* unlock */
                SchM_Exit_Dcm_Dsl_Ctrl();

                Dcm_Dsl_CmHdl_CallActive(u2_PostPduMapIndex, DCM_DSL_REQ_ACTIVE, (boolean)TRUE);

#if( DCM_AUTHENTICATION_USE == STD_ON )
                Dcm_Dsl_Ctrl_SetDeauthenticateAll();
                b_AuthTimeOut = Dcm_Dsl_bAuthTimeOut;
                if( b_AuthTimeOut == (boolean)TRUE )
                {
                    Dcm_Dsl_Ctrl_StopAuthAllTimers();
                }  
#endif /* DCM_AUTHENTICATION_USE == STD_ON */

                u1_RetVal = E_OK;
            }
            else
            {
                u1_RetVal = E_REQUEST_NOT_ACCEPTED;
            }
        }
    }

    return u1_RetVal;
}

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-05-29                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-6-0         :2024-02-27                                              */
/*  v5-8-0         :2024-10-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
