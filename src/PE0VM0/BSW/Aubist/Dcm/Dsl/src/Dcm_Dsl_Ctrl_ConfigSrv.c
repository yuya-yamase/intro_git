/* Dcm_Dsl_Ctrl_ConfigSrv_c(v5-3-0)                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
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
#include "../../Dsl/inc/Dcm_Dsl_Ctrl_local.h"

#include "../../Dsl/inc/Dcm_Dsl_Main.h"

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
/* Function Name | Dcm_Dsl_Ctrl_ConvPMIdxToPrtclRxIdx                       */
/* Description   | Convert a PduMapIndex into                               */
/*               | u2RowIndex/u2ConnectionIndex/u2ProtocolRxIndex.          */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2RxPduMapIndex      : PduMapIndex Value            */
/*               | [out] ptRowIndex          : u2RowIndex                   */
/*               | [out] ptConnectionIndex   : u2ConnectionIndex            */
/*               | [out] ptProtocolRxIndex   : u2ProtocolRxIndex            */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_ConvPMIdxToPrtclRxIdx
(
    const uint16 u2RxPduMapIndex,
    P2VAR( uint16, AUTOMATIC, DCM_APPL_DATA ) ptRowIndex,
    P2VAR( uint16, AUTOMATIC, DCM_APPL_DATA ) ptConnectionIndex,
    P2VAR( uint16, AUTOMATIC, DCM_APPL_DATA ) ptProtocolRxIndex
)
{

    *ptRowIndex        = Dcm_Dsl_PduIdMapTable[u2RxPduMapIndex].u2RowIndex;
    *ptConnectionIndex = Dcm_Dsl_PduIdMapTable[u2RxPduMapIndex].u2ConnectionIndex;
    *ptProtocolRxIndex = Dcm_Dsl_PduIdMapTable[u2RxPduMapIndex].u2ProtocolRxIndex;

    return;

}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_ConvPMIdxToCnctIdx                          */
/* Description   | Convert a PduMapIndex into u2RowIndex/u2ConnectionIndex. */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2RxPduMapIndex      : PduMapIndex Value            */
/*               | [out] ptRowIndex          : u2RowIndex                   */
/*               | [out] ptConnectionIndex   : u2ConnectionIndex            */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_ConvPMIdxToCnctIdx
(
    const uint16 u2RxPduMapIndex,
    P2VAR( uint16, AUTOMATIC, DCM_APPL_DATA ) ptRowIndex,
    P2VAR( uint16, AUTOMATIC, DCM_APPL_DATA ) ptConnectionIndex
)
{

    *ptRowIndex        = Dcm_Dsl_PduIdMapTable[u2RxPduMapIndex].u2RowIndex;
    *ptConnectionIndex = Dcm_Dsl_PduIdMapTable[u2RxPduMapIndex].u2ConnectionIndex;

    return;

}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_ConvPMIdxToClientIdx                        */
/* Description   | Convert a PduMapIndex into u2ClientIndex.                */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2RxPduMapIndex   : PduMapIndex Value               */
/* Return Value  | uint16                                                   */
/*               |        ClientIndex                                       */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( uint16, DCM_CODE ) Dcm_Dsl_Ctrl_ConvPMIdxToClientIdx
(
    const uint16 u2PduMapIndex
)
{
    return Dcm_Dsl_PduIdMapTable[u2PduMapIndex].u2ClientIndex;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_GetComMChannel                              */
/* Description   | This function gets ComMChannel.                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2RxPduMapIndex      : PduMapIndex Value            */
/* Return Value  | uint8                                                    */
/*               |       0x00-0xFF : NetworkId(ComMChannelId)               */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( uint8, DCM_CODE ) Dcm_Dsl_Ctrl_GetComMChannel
(
    const uint16 u2RxPduMapIndex
)
{
    uint16  u2_RowIndex;
    uint16  u2_ConnectionIndex;

    Dcm_Dsl_Ctrl_ConvPMIdxToCnctIdx(u2RxPduMapIndex, &u2_RowIndex, &u2_ConnectionIndex);
    return Dcm_Dsl_stRow[u2_RowIndex].ptConnection[u2_ConnectionIndex].ptMainConnection->u1ProtocolComMChannel;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_GetConnectionPriority                       */
/* Description   | This function gets ConnectionPriority.                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2RxPduMapIndex      : PduMapIndex Value            */
/* Return Value  | uint8                                                    */
/*               |       0x00-0xFF : Connection Priority (0x00 :High)       */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( uint8, DCM_CODE ) Dcm_Dsl_Ctrl_GetConnectionPriority
(
    const uint16 u2RxPduMapIndex
)
{
    uint16  u2_RowIndex;
    uint16  u2_ConnectionIndex;

    Dcm_Dsl_Ctrl_ConvPMIdxToCnctIdx(u2RxPduMapIndex, &u2_RowIndex, &u2_ConnectionIndex);
    return Dcm_Dsl_stRow[u2_RowIndex].ptConnection[u2_ConnectionIndex].ptMainConnection[0].u1ConnectionPriority;

}


/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_GetConnectionGroup                          */
/* Description   | This function gets Connection Group.                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2RxPduMapIndex      : PduMapIndex Value            */
/* Return Value  | uint16                                                   */
/*               |       0x0000-0x001E : Connection Group                   */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( uint16, DCM_CODE ) Dcm_Dsl_Ctrl_GetConnectionGroup
(
    const uint16 u2RxPduMapIndex
)
{
    uint16  u2_RowIndex;
    uint16  u2_ConnectionIndex;

    Dcm_Dsl_Ctrl_ConvPMIdxToCnctIdx(u2RxPduMapIndex, &u2_RowIndex, &u2_ConnectionIndex);
    return Dcm_Dsl_stRow[u2_RowIndex].ptConnection[u2_ConnectionIndex].ptMainConnection[0].u2ConnectionGroup;

}

#if( DCM_DSL_ROE_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_GetDataIndParam                             */
/* Description   | This function gets the parameters of DataInd.            */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex       : PduMapIndex Value             */
/*               | [out] ptReqType          : Request address type          */
/*               | [out] ptPduId            : PduId                         */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_GetDataIndParam
(
    const uint16 u2PduMapIndex,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA )     ptReqType,
    P2VAR( PduIdType, AUTOMATIC, DCM_APPL_DATA ) ptPduId
)
{
    uint16   u2_RowIndex;
    uint16   u2_ConnectionIndex;
    uint16   u2_ProtocolRxIndex;

    Dcm_Dsl_Ctrl_ConvPMIdxToPrtclRxIdx(u2PduMapIndex, &u2_RowIndex, &u2_ConnectionIndex, &u2_ProtocolRxIndex);

    *ptReqType = Dcm_Dsl_stRow[u2_RowIndex].ptConnection[u2_ConnectionIndex].ptMainConnection[0].ptProtocolRx[u2_ProtocolRxIndex].u1AddrType;
    *ptPduId   = Dcm_Dsl_PduIdMapTable[u2PduMapIndex].RxPduId;

    return;
}
#endif /* DCM_DSL_ROE_ENABLE == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_IsNoResPduID                                */
/* Description   | Check PduId that is prohibited Response.                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/* Return Value  | boolean                                                  */
/*               |       TRUE : Response prohibition                        */
/*               |      FALSE : Response permission                         */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_IsNoResPduID
(
    const uint16 u2PduMapIndex
)
{
    boolean b_Result;
    uint16  u2_RowIndex;
    uint16  u2_ConnectionIndex;
    uint16  u2_ProtocolRxIndex;
    boolean b_ExtSuppressRspMsg;
    uint8   u1_AddrType;

    b_Result = (boolean)FALSE;

    Dcm_Dsl_Ctrl_ConvPMIdxToPrtclRxIdx(u2PduMapIndex, &u2_RowIndex, &u2_ConnectionIndex, &u2_ProtocolRxIndex);
    b_ExtSuppressRspMsg = Dcm_Dsl_stRow[u2_RowIndex].ptConnection[u2_ConnectionIndex].ptMainConnection[0].ptProtocolRx[u2_ProtocolRxIndex].bExtSuppressRspMsg;

    if( b_ExtSuppressRspMsg == (boolean)TRUE )
    {
        u1_AddrType = Dcm_Dsl_stRow[u2_RowIndex].ptConnection[u2_ConnectionIndex].ptMainConnection[0].ptProtocolRx[u2_ProtocolRxIndex].u1AddrType;
        if( u1_AddrType == DCM_DSL_ADDINFO_FUNC )
        {
            b_Result = (boolean)TRUE;
        }
    }

    return b_Result;

}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_GetPduIdMapIndexByConnectionId              */
/* Description   | This function gets PduMapIndex from the connection ID    */
/* Preconditions | none                                                     */
/* Parameters    | [In]  u2ConnectionId     : Connection ID(ClientIndex)    */
/* Return Value  | uint16                                                   */
/*               |      Index of PduIdMap                                   */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( uint16, DCM_CODE ) Dcm_Dsl_Ctrl_GetPduIdMapIndexByConnectionId
(
    const uint16 u2ConnectionId
)
{
    uint16  u2_Result;
    uint16  u2_ConnectionIdMax;

    u2_ConnectionIdMax = Dcm_Dsl_u2ClientNum;
    u2_Result          = DCM_DSL_INVALID_U2_DATA;

    if( u2ConnectionId < u2_ConnectionIdMax )
    {
        u2_Result = Dcm_Dsl_ConnectionIdMapTable[u2ConnectionId];
    }

    return u2_Result;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_IsFunctionalAddressingMsg                   */
/* Description   | This function determines whether it is a functional      */
/*               | address message.                                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/* Return Value  | boolean                                                  */
/*               |        TRUE       : Keep-Alive Message                   */
/*               |        FALSE      : not Keep-Alive Message               */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_IsFunctionalAddressingMsg
(
    const uint16 u2PduMapIndex
)
{
    uint16            u2_RowIndex;
    uint16            u2_ConnectionIndex;
    uint16            u2_ProtocolRxIndex;
    uint8             u1_Addrtype;
    boolean           b_Result;

    b_Result = (boolean)FALSE;

    Dcm_Dsl_Ctrl_ConvPMIdxToPrtclRxIdx(u2PduMapIndex, &u2_RowIndex, &u2_ConnectionIndex, &u2_ProtocolRxIndex);
    u1_Addrtype = Dcm_Dsl_stRow[u2_RowIndex].ptConnection[u2_ConnectionIndex].ptMainConnection[0].ptProtocolRx[u2_ProtocolRxIndex].u1AddrType;
    if( u1_Addrtype == DCM_DSL_ADDINFO_FUNC )
    {
        b_Result = (boolean)TRUE;
    }

    return b_Result;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_GetRxBufSize                                */
/* Description   | This function gets the size of the receive resource      */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex    : PduMapIndex Value                */
/* Return Value  | AB_83_DcmPduLengthType                                   */
/*               |       8U~PduLengthmax : RxBuffer Maximum Size            */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( AB_83_DcmPduLengthType, DCM_CODE ) Dcm_Dsl_Ctrl_GetRxBufSize
(
    const uint16 u2PduMapIndex
)
{
    return (AB_83_DcmPduLengthType)Dcm_Dsl_stRxBufferTable[u2PduMapIndex].u4RxBufSize;
}

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-2-0         :2020-10-28                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2022-08-30                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
