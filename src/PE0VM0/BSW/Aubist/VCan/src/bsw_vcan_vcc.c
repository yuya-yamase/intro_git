/* bsw_vcan_vcc_c_v2-0-0                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/VCAN/VCC/SRC/CODE                                     */
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
#if ( BSW_VCAN_VCC_FUNC == BSW_USE )
#include <Can.h>
#include <ehvm.h>

#include "../inc/bsw_vcan_st.h"
#include "../inc/bsw_vcan_rx.h"
#include "../inc/bsw_vcan_vcc.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
static void bsw_vcan_vcc_ClearChannel( BswU1 u1VController );

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
/* Function Name | bsw_vcan_vcc_InitNode                                    */
/* Description   | Initialize VCC Node                                      */
/* Preconditions | None                                                     */
/* Parameters    | BswU1 u1VController         : Virtual Controller ID      */
/* Return Value  | None                                                     */
/* Notes         | Supported API : -                                        */
/****************************************************************************/
void
bsw_vcan_vcc_InitNode( BswU1 u1VController )
{
    bsw_vcan_vcc_ClearChannel( u1VController );
}

/****************************************************************************/
/* Function Name | bsw_vcan_vcc_StartNode                                   */
/* Description   | Start VCC Node                                           */
/* Preconditions | None                                                     */
/* Parameters    | BswU1 u1VController         : Virtual Controller ID      */
/* Return Value  | None                                                     */
/* Notes         | Supported API : -                                        */
/****************************************************************************/
void
bsw_vcan_vcc_StartNode( BswU1 u1VController )
{
    bsw_vcan_vcc_ClearChannel( u1VController );
}

/****************************************************************************/
/* Function Name | bsw_vcan_vcc_Receive                                     */
/* Description   | Process VCC reception                                    */
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
bsw_vcan_vcc_Receive( BswU1 u1VBusId, BswU4 u4RxVNodeId, BswU4 u4TxVNodeId, BswU4 *ptData, BswU4* u4RxMsgLength )
{
    BswU1               u1Ret;
    ehvm_std_return_t   u1VccRet;

    u1VccRet =  ehvm_vcc_receive( (ehvm_uint32_t)u4TxVNodeId, (ehvm_uint32_t*)ptData, BSW_VCAN_u4MSGBUF_BYTESIZE, (ehvm_uint32_t*)u4RxMsgLength );
    if( u1VccRet == (ehvm_std_return_t)E_EHVM_RECEIVE_OVERWRITE_OCCURS )
    {
        u1VccRet =  ehvm_vcc_receive( (ehvm_uint32_t)u4TxVNodeId, (ehvm_uint32_t*)ptData, BSW_VCAN_u4MSGBUF_BYTESIZE, (ehvm_uint32_t*)u4RxMsgLength );
    }

    if( u1VccRet == (ehvm_std_return_t)E_EHVM_OK )
    {
        u1Ret = BSW_VCAN_u1OK;
    }
    else if( u1VccRet == (ehvm_std_return_t)E_EHVM_RECEIVE_OVERWRITE_OCCURS )
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
/* Function Name | bsw_vcan_vcc_Transmit                                    */
/* Description   | Process VCC transmission                                 */
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
bsw_vcan_vcc_Transmit( BswU1 u1VBusId, BswU4 u4TxVNodeId, BswU4 *ptData, BswU4 u4TxMsgLength )
{
    BswU1               u1Ret;
    ehvm_std_return_t   u1VccRet;

    u1VccRet = ehvm_vcc_transmit( (ehvm_uint32_t)u4TxVNodeId, (ehvm_uint32_t*)ptData, (ehvm_uint32_t)u4TxMsgLength );

    u1Ret = BSW_VCAN_u1OK;
    if( u1VccRet != (ehvm_std_return_t)E_EHVM_OK )
    {
        u1Ret = BSW_VCAN_u1NG;
    }

    return( u1Ret );
}

/****************************************************************************/
/* Function Name | bsw_vcan_vcc_DeInitNode                                  */
/* Description   | Shutdown VCC Node                                        */
/* Preconditions | None                                                     */
/* Parameters    | BswU1 u1VController         : Virtual Controller ID      */
/* Return Value  | None                                                     */
/* Notes         | Supported API : -                                        */
/****************************************************************************/
void
bsw_vcan_vcc_DeInitNode( BswU1 u1VController )
{
    ;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | bsw_vcan_vcc_ClearChannel                                */
/* Description   | Clear VCC channel                                        */
/* Preconditions | None                                                     */
/* Parameters    | BswU1 u1VController         : Virtual Controller ID      */
/* Return Value  | None                                                     */
/* Notes         | Supported API : -                                        */
/****************************************************************************/
static void
bsw_vcan_vcc_ClearChannel( BswU1 u1VController )
{
    BswU1               u1RxNodeNum;                    /* Number of received nodes */
    BswU1               u1RxNode;                       /* Received node counter    */
    BswConst Bsw_VCan_RxNodeTblType  *ptRxNodeTbl;      /* Received node ID table   */
    BswConst Bsw_VCan_RxNodeTblType  *ptTmpRxNode;
    BswU4               u4TmpRxNodeId;                  /* Receive queue number */

    u1RxNodeNum   = bsw_vcan_rx_u1RxNodeNum[ u1VController ];
    ptRxNodeTbl   = bsw_vcan_rx_ptRxNodeIdTbl[ u1VController ];
    for( u1RxNode = (BswU1)0U; u1RxNode < u1RxNodeNum; u1RxNode++ )
    {
        /* VCC Buffer clear */
        ptTmpRxNode   = &ptRxNodeTbl[u1RxNode];
        u4TmpRxNodeId = ptTmpRxNode->u4RxNodeId;
        (void)ehvm_vcc_clear_channel( (ehvm_uint32_t)u4TmpRxNodeId );   /* MISRA DEVIATION: no return check required */
    }
}

#endif /* (BSW_VCAN_VCC_FUNC == BSW_USE) */
#endif /* (BSW_BSWM_CS_FUNC_VCAN == BSW_USE) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2022/04/04                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
