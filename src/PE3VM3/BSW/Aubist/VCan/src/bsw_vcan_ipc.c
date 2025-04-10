/* bsw_vcan_ipc_c_v3-0-0                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/VCAN/IPC/SRC/CODE                                     */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>
#include "../inc/bsw_vcan_MemMap.h"
#include <ComStack_Types.h>

#include <bswm_cs/bsw_bswm_cs.h>
#include <comm/bsw_comm.h>
#include <canif/bsw_canif.h>
#include <vcan/bsw_vcan.h>
#include "../../ComM/inc/bsw_comm_config.h"
#include "../../BswM_CS/inc/bsw_bswm_cs_config.h"
#include "../../CanIf/inc/bsw_canif_config.h"
#include "../cfg/VCan_Cfg.h"
#include "../inc/bsw_vcan_config.h"

#if ( BSW_BSWM_CS_FUNC_VCAN == BSW_USE )
#if ( BSW_VCAN_IPC_FUNC == BSW_USE )
#include <Can.h>
#include <bsw_ipc.h>

#include "../inc/bsw_vcan_st.h"
#include "../inc/bsw_vcan_rx.h"
#include "../inc/bsw_vcan_ipc.h"

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
/* Function Name | bsw_vcan_ipc_InitNode                                    */
/* Description   | Initialize IPC Node                                      */
/* Preconditions | None                                                     */
/* Parameters    | BswU1 u1VController         : Virtual Controller ID      */
/* Return Value  | None                                                     */
/* Notes         | Supported API : -                                        */
/****************************************************************************/
void
bsw_vcan_ipc_InitNode( BswU1 u1VController )
{
    Bsw_Ipc_VBusIdType     u1TmpBusId;             /* Bus ID                */
    Bsw_Ipc_VNodeIdType    u1OwnNodeId;            /* Node ID               */

    u1TmpBusId   = bsw_vcan_u1IpcVirtualCtrlBus[ u1VController ];
    u1OwnNodeId  = (Bsw_Ipc_VNodeIdType)bsw_vcan_tx_u4VirtualCtrlToNode[ u1VController ];

    (void)bsw_ipc_InitNode( u1TmpBusId, u1OwnNodeId );  /* MISRA DEVIATION: no return check required */
}

/****************************************************************************/
/* Function Name | bsw_vcan_ipc_StartNode                                   */
/* Description   | Start Communication IPC Node                             */
/* Preconditions | None                                                     */
/* Parameters    | BswU1 u1VController         : Virtual Controller ID      */
/* Return Value  | None                                                     */
/* Notes         | Supported API : -                                        */
/****************************************************************************/
void
bsw_vcan_ipc_StartNode( BswU1 u1VController )
{
    Bsw_Ipc_VBusIdType     u1TmpBusId;             /* Bus ID                */
    Bsw_Ipc_VNodeIdType    u1OwnNodeId;            /* Node ID               */

    u1TmpBusId   = bsw_vcan_u1IpcVirtualCtrlBus[ u1VController ];
    u1OwnNodeId  = (Bsw_Ipc_VNodeIdType)bsw_vcan_tx_u4VirtualCtrlToNode[ u1VController ];

    bsw_ipc_StartNode( u1TmpBusId, u1OwnNodeId );
}

/****************************************************************************/
/* Function Name | bsw_vcan_ipc_Receive                                     */
/* Description   | IPC receiving processing                                 */
/* Preconditions | None                                                     */
/* Parameters    | BswU1 u1VBusId              : Virtual bus ID             */
/*               | BswU4 u4RxVNodeId           : Receive virtual node ID    */
/*               | BswU4 u4TxVNodeId           : Transmit virtual node ID   */
/*               | BswU4 *ptData               : Receive data               */
/*               | BswU4* u4RxMsgLength        : Receive data length        */
/* Return Value  | BswU1                       : Receive result             */
/*               |   BSW_VCAN_u1OK             : Receive success            */
/*               |   BSW_VCAN_u1NG             : Receive failure            */
/*               |   BSW_VCAN_u1OVERWRITE_OCCURS  : Overwrite Occurs        */
/* Notes         | Supported API : -                                        */
/****************************************************************************/
BswU1
bsw_vcan_ipc_Receive( BswU1 u1VBusId, BswU4 u4RxVNodeId, BswU4 u4TxVNodeId, BswU4 *ptData, BswU4* u4RxMsgLength )
{
    BswU1                   u1Ret;
    Bsw_Ipc_ReturnType      u1IpcRet;
    Bsw_Ipc_VNodeIdType     u1TmpRxVNodeId;
    Bsw_Ipc_VNodeIdType     u1TmpTxVNodeId;

    u1TmpRxVNodeId = (Bsw_Ipc_VNodeIdType)u4RxVNodeId;
    u1TmpTxVNodeId = (Bsw_Ipc_VNodeIdType)u4TxVNodeId;
    u1IpcRet = bsw_ipc_Receive( (Bsw_Ipc_VBusIdType)u1VBusId, ptData, BSW_VCAN_u4MSGBUF_BYTESIZE, u4RxMsgLength, u1TmpRxVNodeId, u1TmpTxVNodeId );
    if( u1IpcRet == (Bsw_Ipc_ReturnType)BSW_IPC_RECEIVE_OVERWRITE )
    {
        u1IpcRet = bsw_ipc_Receive( (Bsw_Ipc_VBusIdType)u1VBusId, ptData, BSW_VCAN_u4MSGBUF_BYTESIZE, u4RxMsgLength, u1TmpRxVNodeId, u1TmpTxVNodeId );
    }

    if( u1IpcRet == (Bsw_Ipc_ReturnType)BSW_IPC_RECEIVE_OK )
    {
        u1Ret = BSW_VCAN_u1OK;
    }
    else if( u1IpcRet == (Bsw_Ipc_ReturnType)BSW_IPC_RECEIVE_OVERWRITE )
    {
        u1Ret = BSW_VCAN_u1OVERWRITE_OCCURS;
    }
    else
    {
        u1Ret = BSW_VCAN_u1NG;
    }

    return( u1Ret );
}

/****************************************************************************/
/* Function Name | bsw_vcan_ipc_Transmit                                    */
/* Description   | IPC transmission processing                              */
/* Preconditions | None                                                     */
/* Parameters    | BswU1 u1VBusId              : Virtual bus ID             */
/*               | BswU4 u4TxVNodeId           : Transmit virtual node ID   */
/*               | BswU4 *ptData               : Transmit data              */
/*               | BswU4 u4TxMsgLength         : Transmission data length   */
/* Return Value  | BswU1          Result of transmission request            */
/*               |   BSW_VCAN_u1OK             : Request accepted           */
/*               |   BSW_VCAN_u1NG             : Request not accepted       */
/* Notes         | Supported API : -                                        */
/****************************************************************************/
BswU1
bsw_vcan_ipc_Transmit( BswU1 u1VBusId, BswU4 u4TxVNodeId, BswU4 *ptData, BswU4 u4TxMsgLength )
{
    BswU1                   u1Ret;
    Bsw_Ipc_ReturnType      u1IpcRet;
    Bsw_Ipc_VNodeIdType     u1TmpTxVNodeId;

    u1TmpTxVNodeId = (Bsw_Ipc_VNodeIdType)u4TxVNodeId;
    u1IpcRet = bsw_ipc_Transmit( (Bsw_Ipc_VBusIdType)u1VBusId, ptData, u4TxMsgLength, u1TmpTxVNodeId );
    u1Ret = BSW_VCAN_u1OK;
    if( u1IpcRet != (Bsw_Ipc_ReturnType)BSW_IPC_TRANSMIT_OK )
    {
        u1Ret = BSW_VCAN_u1NG;
    }

    return( u1Ret);
}

/****************************************************************************/
/* Function Name | bsw_vcan_ipc_DeInitNode                                  */
/* Description   | Shutdown IPC Node                                        */
/* Preconditions | None                                                     */
/* Parameters    | BswU1 u1VController         : Virtual Controller ID      */
/* Return Value  | None                                                     */
/* Notes         | Supported API : -                                        */
/****************************************************************************/
void
bsw_vcan_ipc_DeInitNode( BswU1 u1VController )
{
    Bsw_Ipc_VBusIdType     u1TmpBusId;             /* Bus ID                */
    Bsw_Ipc_VNodeIdType    u1OwnNodeId;            /* Node ID               */

    u1TmpBusId   = bsw_vcan_u1IpcVirtualCtrlBus[ u1VController ];
    u1OwnNodeId  = (Bsw_Ipc_VNodeIdType)bsw_vcan_tx_u4VirtualCtrlToNode[ u1VController ];

    bsw_ipc_DeInitNode( u1TmpBusId, u1OwnNodeId );
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#endif /* (BSW_VCAN_IPC_FUNC == BSW_USE) */
#endif /* (BSW_BSWM_CS_FUNC_VCAN == BSW_USE) */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2022/04/05                                             */
/*  v2-1-0          :2022/05/24                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
