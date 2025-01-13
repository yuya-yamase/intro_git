/* bsw_vdat_vcc_c_v3-0-0                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/VDAT/VCC/CODE                                         */
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
#if ( BSW_VDAT_VCC_FUNC == BSW_VDAT_USE )

#include "../inc/bsw_vdat_trx.h"
#include "../inc/bsw_vdat_vcc.h"

#include <ehvm.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
static void bsw_vdat_vcc_ClearChannel( BswU1 u1ConnectionId, BswU1 u1NodeId );

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
/* Function Name | bsw_vdat_vcc_InitNode                                    */
/* Description   | Node Initialize of Inter-Processor Communication Module  */
/* Preconditions | Caller : VDat  Timing : User initialization              */
/* Parameters    | u1ConnectionId   : Connection ID                         */
/*               | u1NodeId         : Node ID                               */
/* Return Value  | Result                                                   */
/*               |   BSW_VDAT_OK               : Successed                  */
/* Notes         | None                                                     */
/****************************************************************************/
Bsw_VDat_ReturnType
bsw_vdat_vcc_InitNode( BswU1 u1ConnectionId, BswU1 u1NodeId )
{
    bsw_vdat_vcc_ClearChannel( u1ConnectionId, u1NodeId );

    return (Bsw_VDat_ReturnType)BSW_VDAT_OK;
}

/****************************************************************************/
/* Function Name | bsw_vdat_vcc_StartNode                                   */
/* Description   | Start of Inter-Processor Communication Module            */
/* Preconditions | Caller : VDat  Timing : User initialization              */
/* Parameters    | u1ConnectionId   : Connection ID                         */
/*               | u1NodeId         : Node ID                               */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_vdat_vcc_StartNode( BswU1 u1ConnectionId, BswU1 u1NodeId )
{
    bsw_vdat_vcc_ClearChannel( u1ConnectionId, u1NodeId );
}

/****************************************************************************/
/* Function Name | bsw_vdat_vcc_Receive                                     */
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
bsw_vdat_vcc_Receive( BswU1 u1ConnectionId, BswU1 u1NodeId, BswU4 *ptData, BswU4 u4BufSize, BswU4 *u4DataLength )
{
    BswU1               u1NodeCnt;
    BswU1               u1NodeNum;
    BswConst BswU4      *ptQueueId;
    ehvm_uint32_t       u4VccId;
    ehvm_std_return_t   u1VccRet;
    Bsw_VDat_ReturnType u1Ret;

    u1NodeNum = bsw_vdat_trx_u1NodeNum[ u1ConnectionId ];
    ptQueueId = bsw_vdat_trx_u4QueueIDTbl[ u1ConnectionId ];
    u1Ret = (Bsw_VDat_ReturnType)BSW_VDAT_NOT_OK;
    for( u1NodeCnt = (BswU1)0U; u1NodeCnt < u1NodeNum; u1NodeCnt++ )
    {
        if( u1NodeCnt != u1NodeId )
        {
            u4VccId = (ehvm_uint32_t)ptQueueId[ u1NodeCnt ];
            u1VccRet = ehvm_vcc_receive( u4VccId, (ehvm_uint32_t*)ptData, (ehvm_uint32_t)u4BufSize, (ehvm_uint32_t*)u4DataLength );
            if( u1VccRet == (ehvm_std_return_t)E_EHVM_OK )
            {
                u1Ret = (Bsw_VDat_ReturnType)BSW_VDAT_OK;
                break;
            }
            else if( u1VccRet == (ehvm_std_return_t)E_EHVM_RECEIVE_OVERWRITE_OCCURS )
            {
                u1Ret = (Bsw_VDat_ReturnType)BSW_VDAT_OVERWRITE_OCCURS;
            }
            else /* MISRA DEVIATION: no process */
            {
                ; /* no process(When data reception fails except when overwriting occurs) */
            }
        }
    }
    return u1Ret;
}

/****************************************************************************/
/* Function Name | bsw_vdat_vcc_Transmit                                    */
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
bsw_vdat_vcc_Transmit( BswU1 u1ConnectionId, BswU1 u1NodeId, BswU4 *ptData, BswU4 u4DataLength )
{
    BswConst BswU4      *ptQueueId;
    ehvm_uint32_t       u4VccId;
    ehvm_std_return_t   u1VccRet;
    Bsw_VDat_ReturnType u1Ret;

    ptQueueId = bsw_vdat_trx_u4QueueIDTbl[ u1ConnectionId ];
    u4VccId = (ehvm_uint32_t)ptQueueId[ u1NodeId ];
    u1VccRet = ehvm_vcc_transmit( u4VccId, (ehvm_uint32_t*)ptData, (ehvm_uint32_t)u4DataLength );
    u1Ret = (Bsw_VDat_ReturnType)BSW_VDAT_OK;
    if( u1VccRet != (ehvm_std_return_t)E_EHVM_OK )
    {
        u1Ret = (Bsw_VDat_ReturnType)BSW_VDAT_NOT_OK;
    }

    return u1Ret;
}

/****************************************************************************/
/* Function Name | bsw_vdat_vcc_DeInitNode                                  */
/* Description   | Node Shutdown of Inter-Processor Communication Module    */
/* Preconditions | Caller : VDat  Timing : User shutdown                    */
/* Parameters    | u1ConnectionId   : Connection ID                         */
/*               | u1NodeId         : Node ID                               */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_vdat_vcc_DeInitNode( BswU1 u1ConnectionId, BswU1 u1NodeId )
{
    ;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | bsw_vdat_vcc_ClearChannel                                */
/* Description   | Clear VCC channel                                        */
/* Preconditions | Caller : VDat  Timing : User initialization              */
/* Parameters    | u1ConnectionId   : Connection ID                         */
/*               | u1NodeId         : Node ID                               */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static void
bsw_vdat_vcc_ClearChannel( BswU1 u1ConnectionId, BswU1 u1NodeId )
{
    BswU1               u1NodeCnt;
    BswU1               u1NodeNum;
    BswConst BswU4      *ptQueueId;
    ehvm_uint32_t       u4VccId;

    u1NodeNum = bsw_vdat_trx_u1NodeNum[ u1ConnectionId ];
    ptQueueId = bsw_vdat_trx_u4QueueIDTbl[ u1ConnectionId ];
    for( u1NodeCnt = (BswU1)0U; u1NodeCnt < u1NodeNum; u1NodeCnt++ )
    {
        if( u1NodeCnt != u1NodeId )
        {
            u4VccId = (ehvm_uint32_t)ptQueueId[ u1NodeCnt ];
            (void)ehvm_vcc_clear_channel( u4VccId );    /* MISRA DEVIATION: no return check required */
        }
    }
}

#endif /* BSW_VDAT_VCC_FUNC == BSW_VDAT_USE */
#endif /* BSW_VDAT_CFG_FUNC_VDAT == BSW_VDAT_USE */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2022/04/14                                             */
/*  v2-1-0          :2022/05/24                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
