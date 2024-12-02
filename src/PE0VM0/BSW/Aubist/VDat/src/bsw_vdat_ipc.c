/* bsw_vdat_ipc_c_v2-1-0                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/VDAT/IPC/CODE                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>
#include "../inc/bsw_vdat_MemMap.h"

#include <bsw_vdat.h>
#include "../cfg/VDat_Cfg.h"
#include "../inc/bsw_vdat_config.h"

#if ( BSW_VDAT_CFG_FUNC_VDAT == BSW_VDAT_USE )
#if ( BSW_VDAT_IPC_FUNC == BSW_VDAT_USE )

#include "../inc/bsw_vdat_trx.h"
#include "../inc/bsw_vdat_ipc.h"

#include <bsw_ipc.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

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
/* Function Name | bsw_vdat_ipc_InitNode                                    */
/* Description   | Node Initialize of Inter-Processor Communication Module  */
/* Preconditions | Caller : VDat  Timing : User initialization              */
/* Parameters    | u1ConnectionId   : Connection ID                         */
/*               | u1NodeId         : Node ID                               */
/* Return Value  | Result                                                   */
/*               |   BSW_VDAT_OK               : Successed                  */
/*               |   BSW_VDAT_NOT_OK           : Failed                     */
/* Notes         | None                                                     */
/****************************************************************************/
Bsw_VDat_ReturnType
bsw_vdat_ipc_InitNode( BswU1 u1ConnectionId, BswU1 u1NodeId )
{
    Bsw_Ipc_VBusIdType      u1BusId;
    BswConst BswU4          *ptQueueId;
    Bsw_Ipc_VNodeIdType     u1IpcNode;
    Bsw_Ipc_ReturnType      u1IpcRet;
    Bsw_VDat_ReturnType     u1Ret;

    u1BusId   = bsw_vdat_trx_u1IpcBusId[ u1ConnectionId ];
    ptQueueId = bsw_vdat_trx_u4QueueIDTbl[ u1ConnectionId ];
    u1IpcNode = (Bsw_Ipc_VNodeIdType)ptQueueId[ u1NodeId ];
    u1IpcRet  = bsw_ipc_InitNode( u1BusId, u1IpcNode );
    u1Ret     = (Bsw_VDat_ReturnType)BSW_VDAT_OK;
    if( u1IpcRet != (Bsw_Ipc_ReturnType)BSW_IPC_INIT_OK )
    {
        u1Ret = (Bsw_VDat_ReturnType)BSW_VDAT_NOT_OK;
    }

    return u1Ret;
}

/****************************************************************************/
/* Function Name | bsw_vdat_ipc_StartNode                                   */
/* Description   | Start of Inter-Processor Communication Module            */
/* Preconditions | Caller : VDat  Timing : User initialization              */
/* Parameters    | u1ConnectionId   : Connection ID                         */
/*               | u1NodeId         : Node ID                               */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_vdat_ipc_StartNode( BswU1 u1ConnectionId, BswU1 u1NodeId )
{
    Bsw_Ipc_VBusIdType      u1BusId;
    BswConst BswU4          *ptQueueId;
    Bsw_Ipc_VNodeIdType     u1IpcNode;

    u1BusId   = bsw_vdat_trx_u1IpcBusId[ u1ConnectionId ];
    ptQueueId = bsw_vdat_trx_u4QueueIDTbl[ u1ConnectionId ];
    u1IpcNode = (Bsw_Ipc_VNodeIdType)ptQueueId[ u1NodeId ];
    bsw_ipc_StartNode( u1BusId, u1IpcNode );
}

/****************************************************************************/
/* Function Name | bsw_vdat_ipc_Receive                                     */
/* Description   | Receive Inter-Processor Communication Frame              */
/* Preconditions | Caller : VDat  Timing : User receiving                   */
/* Parameters    | u1ConnectionId   : Connection ID                         */
/*               | u1NodeId         : Node ID                               */
/*               | ptData           : Data Pointer                          */
/*               | u4BufSize        : Buffer Size                           */
/*               | u4DataLength     : Data Length                           */
/* Return Value  | Result                                                   */
/*               |   BSW_VDAT_OK               : Successed                  */
/*               |   BSW_VDAT_NOT_OK           : Failed                     */
/*               |   BSW_VDAT_OVERWRITE_OCCURS : Overwrite Occurs           */
/* Notes         | None                                                     */
/****************************************************************************/
Bsw_VDat_ReturnType
bsw_vdat_ipc_Receive( BswU1 u1ConnectionId, BswU1 u1NodeId, BswU4 *ptData, BswU4 u4BufSize, BswU4 *u4DataLength )
{
    BswU1                   u1NodeCnt;
    BswU1                   u1NodeNum;
    Bsw_Ipc_VBusIdType      u1BusId;
    BswConst BswU4          *ptQueueId;
    Bsw_Ipc_VNodeIdType     u1IpcNode;
    Bsw_Ipc_VNodeIdType     u1IpcTxNode;
    Bsw_Ipc_ReturnType      u1IpcRet;
    Bsw_VDat_ReturnType     u1Ret;
    BswU1                   u1ContinueFlg;

    u1BusId   = bsw_vdat_trx_u1IpcBusId[ u1ConnectionId ];
    ptQueueId = bsw_vdat_trx_u4QueueIDTbl[ u1ConnectionId ];
    u1NodeNum = bsw_vdat_trx_u1NodeNum[ u1ConnectionId ];
    u1IpcNode = (Bsw_Ipc_VNodeIdType)ptQueueId[ u1NodeId ];
    u1Ret     = (Bsw_VDat_ReturnType)BSW_VDAT_NOT_OK;
    u1ContinueFlg = (BswU1)BSW_ON;
    for( u1NodeCnt = (BswU1)0U; u1NodeCnt < u1NodeNum; u1NodeCnt++ )
    {
        if( u1NodeCnt != u1NodeId )
        {
            u1IpcTxNode = (Bsw_Ipc_VNodeIdType)ptQueueId[ u1NodeCnt ];
            u1IpcRet = bsw_ipc_Receive( u1BusId, ptData, u4BufSize, u4DataLength, u1IpcNode, u1IpcTxNode );
            if( u1IpcRet == (Bsw_Ipc_ReturnType)BSW_IPC_RECEIVE_OK )
            {
                u1Ret = (Bsw_VDat_ReturnType)BSW_VDAT_OK;
                u1ContinueFlg = (BswU1)BSW_OFF;
            }
            else if( u1IpcRet == (Bsw_Ipc_ReturnType)BSW_IPC_RECEIVE_OVERWRITE )
            {
                u1Ret = (Bsw_VDat_ReturnType)BSW_VDAT_OVERWRITE_OCCURS;
            }
            else if( u1IpcRet == (Bsw_Ipc_ReturnType)BSW_IPC_RECEIVE_FAIL )
            {
                bsw_vdat_CbkDetectFail( u1ConnectionId, u1NodeId );
                u1Ret    = (Bsw_VDat_ReturnType)BSW_VDAT_NOT_OK;
                u1ContinueFlg = (BswU1)BSW_OFF;
            }
            else /* MISRA DEVIATION: no process */
            {
                ; /* no process(When data reception fails except when overwriting occurs and an error is detected) */
            }
            if( u1ContinueFlg == (BswU1)BSW_OFF )
            {
                break;
            }
        }
    }
    return u1Ret;
}

/****************************************************************************/
/* Function Name | bsw_vdat_ipc_Transmit                                    */
/* Description   | Transmit Inter-Processor Communication Frame             */
/* Preconditions | Caller : VDat  Timing : User sending                     */
/* Parameters    | u1ConnectionId   : Connection ID                         */
/*               | u1NodeId         : Node ID                               */
/*               | ptData           : Data Pointer                          */
/*               | u4DataLength     : Data Length                           */
/* Return Value  | Result                                                   */
/*               |   VDAT_OK        : Successed                             */
/*               |   VDAT_NOT_OK    : Failed                                */
/* Notes         | None                                                     */
/****************************************************************************/
Bsw_VDat_ReturnType
bsw_vdat_ipc_Transmit( BswU1 u1ConnectionId, BswU1 u1NodeId, BswU4 *ptData, BswU4 u4DataLength )
{
    Bsw_Ipc_VBusIdType      u1BusId;
    BswConst BswU4          *ptQueueId;
    Bsw_Ipc_VNodeIdType     u1IpcNode;
    Bsw_Ipc_ReturnType      u1IpcRet;
    Bsw_VDat_ReturnType     u1Ret;

    u1BusId     = bsw_vdat_trx_u1IpcBusId[ u1ConnectionId ];
    ptQueueId   = bsw_vdat_trx_u4QueueIDTbl[ u1ConnectionId ];
    u1IpcNode   = (Bsw_Ipc_VNodeIdType)ptQueueId[ u1NodeId ];
    u1IpcRet    = bsw_ipc_Transmit( u1BusId, ptData, u4DataLength, u1IpcNode );
    u1Ret       = (Bsw_VDat_ReturnType)BSW_VDAT_OK;
    if( u1IpcRet != (Bsw_Ipc_ReturnType)BSW_IPC_TRANSMIT_OK )
    {
        u1Ret = (Bsw_VDat_ReturnType)BSW_VDAT_NOT_OK;
        if( u1IpcRet == (Bsw_Ipc_ReturnType)BSW_IPC_TRANSMIT_FAIL )
        {
            bsw_vdat_CbkDetectFail( u1ConnectionId, u1NodeId );
        }
    }

    return u1Ret;
}

/****************************************************************************/
/* Function Name | bsw_vdat_ipc_DeInitNode                                  */
/* Description   | Node Shutdown of Inter-Processor Communication Module    */
/* Preconditions | Caller : VDat  Timing : User shutdown                    */
/* Parameters    | u1ConnectionId   : Connection ID                         */
/*               | u1NodeId         : Node ID                               */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_vdat_ipc_DeInitNode( BswU1 u1ConnectionId, BswU1 u1NodeId )
{
    Bsw_Ipc_VBusIdType      u1BusId;
    BswConst BswU4          *ptQueueId;
    Bsw_Ipc_VNodeIdType     u1IpcNode;

    u1BusId   = bsw_vdat_trx_u1IpcBusId[ u1ConnectionId ];
    ptQueueId = bsw_vdat_trx_u4QueueIDTbl[ u1ConnectionId ];
    u1IpcNode = (Bsw_Ipc_VNodeIdType)ptQueueId[ u1NodeId ];
    bsw_ipc_DeInitNode( u1BusId, u1IpcNode );
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#endif /* BSW_VDAT_IPC_FUNC == BSW_VDAT_USE */
#endif /* BSW_VDAT_CFG_FUNC_VDAT == BSW_VDAT_USE */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2022/04/06                                             */
/*  v2-1-0          :2022/09/28                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
