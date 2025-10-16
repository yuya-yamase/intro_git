/* bsw_bswm_can_status_c_v3-0-0                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/BSWM/CAN/STATUS/CODE                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>
#include "../inc/bsw_bswm_can_MemMap.h"
#include <ComStack_Types.h>

#include <bswm_cs/bsw_bswm_cs.h>
#include <comm/bsw_comm.h>
#include "../../ComM/inc/bsw_comm_config.h"
#include "../../BswM_CS/inc/bsw_bswm_cs_config.h"
#if ( BSW_BSWM_CS_FUNC_BSWMCAN == BSW_USE )

#include <bswm_can/bsw_bswm_can.h>
#include <comm/bsw_comm_ecumbswm.h>
#include <cannm/bsw_cannm.h>
#include <cansm/bsw_cansm.h>
#include <canif/bsw_canif.h>
#include <Can.h>
#include <vcan/bsw_vcan.h>
#include <cantrcv/bsw_cantrcv.h>
#include "../inc/bsw_bswm_can_config.h"
#include "../inc/bsw_bswm_can_status.h"
#include "../inc/bsw_bswm_can_ctrl.h"
#include "../inc/bsw_bswm_can_connector.h"

#if ( BSW_BSWM_CS_FUNC_J1939TP == BSW_USE )
#include <j1939tp/bsw_j1939tp.h>
#endif

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
/* Function Name | bsw_bswm_can_st_Init                                     */
/* Description   | Initialize CAN                                           */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | Supported API : BswM_Can_Init                            */
/****************************************************************************/
void
bsw_bswm_can_st_Init( void )
{
    bsw_bswm_can_ctrl_Init();

    CanTrcv_Init( NULL_PTR );
#if ( BSW_BSWM_CS_FUNC_CANDRV == BSW_USE )
    Can_Init( (BswU1)0U );
#endif
#if ( BSW_BSWM_CS_FUNC_VCAN == BSW_USE )
    VCan_Init( (BswU1)0U );
#endif
    CanIf_Init( NULL_PTR );
    bsw_bswm_can_ctrl_EdgeInit();
    CanNm_Init( NULL_PTR );
    CanSM_Init( NULL_PTR );
#if ( BSW_BSWM_CS_FUNC_CANTP == BSW_USE )
    bsw_bswm_can_CanTpInit();
#endif
#if ( BSW_BSWM_CS_FUNC_J1939TP == BSW_USE )
    J1939Tp_Init(NULL_PTR);
#endif
}

/****************************************************************************/
/* Function Name | bsw_bswm_can_st_PrepareDeInit                            */
/* Description   | CAN Prepare for shutdown                                 */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | Supported API : BswM_Can_PrepareDeInit                   */
/****************************************************************************/
void
bsw_bswm_can_st_PrepareDeInit( void )
{
    BswU1 u1Ch;
    BswU1 u1ChNum;

    bsw_bswm_can_ctrl_EdgeDeInit();

    u1ChNum = bsw_bswm_can_ctrl_u1ChNum;
    for( u1Ch = (BswU1)0U; u1Ch < u1ChNum; u1Ch++)
    {
        /* No need to check the return value since it does not affect subsequent processing */
        (void)CanIf_SetControllerMode( u1Ch, (CanIf_ControllerModeType)CANIF_CS_STOPPED ); /* MISRA DEVIATION: no return check required */
    }
    CanIf_DeInit();
    CanNm_DeInit();
    CanSM_DeInit();
#if ( BSW_BSWM_CS_FUNC_CANTP == BSW_USE )
    bsw_bswm_can_CanTpShutdown();
#endif
#if ( BSW_BSWM_CS_FUNC_J1939TP == BSW_USE )
    J1939Tp_Shutdown();
#endif
}

/****************************************************************************/
/* Function Name | bsw_bswm_can_st_DeInit                                   */
/* Description   | CAN Shutdown                                             */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | Supported API : BswM_Can_DeInit                          */
/****************************************************************************/
void
bsw_bswm_can_st_DeInit( void )
{
    bsw_bswm_can_ctrl_EdgeDeInit();
#if ( BSW_BSWM_CS_FUNC_CANDRV == BSW_USE )
    Can_Shutdown();
#endif
#if ( BSW_BSWM_CS_FUNC_VCAN == BSW_USE )
    VCan_Shutdown();
#endif
    CanTrcv_DeInit();
    CanIf_DeInit();
    CanNm_DeInit();
    CanSM_DeInit();
#if ( BSW_BSWM_CS_FUNC_CANTP == BSW_USE )
    bsw_bswm_can_CanTpShutdown();
#endif
#if ( BSW_BSWM_CS_FUNC_J1939TP == BSW_USE )
    J1939Tp_Shutdown();
#endif
}

#if ( BSW_BSWM_CS_ECU_SLEEP == BSW_USE)
/****************************************************************************/
/* Function Name | bsw_bswm_can_st_Wakeup                                   */
/* Description   | CAN Wake-up initialization                               */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | Supported API : BswM_Can_Wakeup                          */
/****************************************************************************/
void
bsw_bswm_can_st_Wakeup( void )
{
    bsw_bswm_can_ctrl_Wakeup();

    CanTrcv_Init( NULL_PTR );
#if ( BSW_BSWM_CS_FUNC_CANDRV == BSW_USE )
    Can_Init( (BswU1)0U );
#endif
#if ( BSW_BSWM_CS_FUNC_VCAN == BSW_USE )
    VCan_Init( (BswU1)0U );
#endif
    CanIf_Init( NULL_PTR );
    bsw_bswm_can_ctrl_EdgeWakeup();
    CanNm_Wakeup( NULL_PTR );
    CanSM_Init( NULL_PTR );
#if ( BSW_BSWM_CS_FUNC_CANTP == BSW_USE )
    bsw_bswm_can_CanTpInit();
#endif
#if ( BSW_BSWM_CS_FUNC_J1939TP == BSW_USE )
    J1939Tp_Init(NULL_PTR);
#endif
}

/****************************************************************************/
/* Function Name | bsw_bswm_can_st_Sleep                                    */
/* Description   | CAN Sleep                                                */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | Supported API : BswM_Can_Sleep                           */
/****************************************************************************/
void
bsw_bswm_can_st_Sleep( void )
{
    bsw_bswm_can_ctrl_EdgeSleep();
#if ( BSW_BSWM_CS_FUNC_CANDRV == BSW_USE )
    Can_Shutdown();
#endif
#if ( BSW_BSWM_CS_FUNC_VCAN == BSW_USE )
    VCan_Shutdown();
#endif
    CanIf_DeInit();
    CanNm_Sleep();
    CanSM_DeInit();
#if ( BSW_BSWM_CS_FUNC_CANTP == BSW_USE )
    bsw_bswm_can_CanTpShutdown();
#endif
#if ( BSW_BSWM_CS_FUNC_J1939TP == BSW_USE )
    J1939Tp_Shutdown();
#endif
}

#endif /* ( BSW_BSWM_CS_ECU_SLEEP == BSW_USE) */

/****************************************************************************/
/* Function Name | bsw_bswm_can_st_Reset                                    */
/* Description   | CAN Reset                                                */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | Supported API : BswM_Can_Reset                           */
/****************************************************************************/
void
bsw_bswm_can_st_Reset( void )
{
    bsw_bswm_can_ctrl_ResetInit();

    CanTrcv_Init( NULL_PTR );
#if ( BSW_BSWM_CS_FUNC_CANDRV == BSW_USE )
    Can_Init( (BswU1)0U );
#endif
#if ( BSW_BSWM_CS_FUNC_VCAN == BSW_USE )
    VCan_Init( (BswU1)0U );
#endif
    CanIf_Init( NULL_PTR );
    bsw_bswm_can_ctrl_EdgeInit();
    CanNm_Init( NULL_PTR );
    CanSM_Init( NULL_PTR );
#if ( BSW_BSWM_CS_FUNC_CANTP == BSW_USE )
    bsw_bswm_can_CanTpInit();
#endif
#if ( BSW_BSWM_CS_FUNC_J1939TP == BSW_USE )
    J1939Tp_Init(NULL_PTR);
#endif

    bsw_bswm_can_ctrl_Reset();
}

/****************************************************************************/
/* Function Name | bsw_bswm_can_st_MainFuncHiIn                             */
/* Description   | High-priority periodic processing - Input                */
/* Preconditions | When processing high-priority periodic process           */
/* Parameters    | NONE                                                     */
/* Return Value  | NONE                                                     */
/* Notes         | Supported API : BswM_Can_MainFunctionHighIn              */
/****************************************************************************/
void
bsw_bswm_can_st_MainFuncHiIn( void )
{
#if ( BSW_BSWM_CS_FUNC_CANTX == BSW_USE )
#if ( ( BSW_BSWM_CS_FUNC_CANDRV == BSW_USE ) && ( BSW_BSWM_CS_FUNC_CANTX_PHY == BSW_USE ) )
    Can_MainFunction_Write();
#endif
#if ( ( BSW_BSWM_CS_FUNC_VCAN == BSW_USE ) && ( BSW_BSWM_CS_FUNC_CANTX_VIR == BSW_USE ) )
    VCan_MainFunction_Write();
#endif
#endif
#if ( BSW_BSWM_CS_FUNC_CANRX == BSW_USE )
#if ( BSW_BSWM_CS_FUNC_CANDRV == BSW_USE )
    Can_MainFunction_Read();
#endif
#if ( BSW_BSWM_CS_FUNC_VCAN == BSW_USE )
    VCan_MainFunction_Read();
#endif
#endif
#if ( BSW_BSWM_CS_MSG_DELIVER == BSW_BSWM_CS_MSGDELIVER_HIGH )
    bsw_bswm_can_ctrl_CbkPreCtrlRx();

#if ( BSW_BSWM_CS_FUNC_CANTX == BSW_USE )
#if ( BSW_BSWM_CAN_FUNC_TXERR_NOTIFY == BSW_USE )
    CanIf_MainFunctionTxFail();
#endif
#endif

    CanIf_MainFunctionRx();
#endif
}

/****************************************************************************/
/* Function Name | bsw_bswm_can_st_MainFuncHiOut                            */
/* Description   | High-priority periodic processing - Output               */
/* Preconditions | When processing high-priority periodic process           */
/* Parameters    | NONE                                                     */
/* Return Value  | NONE                                                     */
/* Notes         | Supported API : BswM_Can_MainFunctionHighOut             */
/****************************************************************************/
void
bsw_bswm_can_st_MainFuncHiOut( void )
{
#if ( BSW_BSWM_CS_FUNC_CANTP == BSW_USE )
#if ( BSW_BSWM_CS_MSG_DELIVER == BSW_BSWM_CS_MSGDELIVER_HIGH )
    bsw_bswm_can_CanTpMainFunction();
#endif
#endif
    CanNm_MainFunctionHigh();
    bsw_bswm_can_ctrl_CbkPreCtrlTx();
#if ( BSW_BSWM_CS_FUNC_CANTX == BSW_USE )
    CanIf_MainFunctionTx();
#endif
}

/****************************************************************************/
/* Function Name | bsw_bswm_can_st_MainFuncMidIn                            */
/* Description   | Medium-priority input                                    */
/* Preconditions | When processing medium-priority periodic process         */
/* Parameters    | NONE                                                     */
/* Return Value  | NONE                                                     */
/* Notes         | Supported API : BswM_Can_MainFunctionMidIn               */
/****************************************************************************/
void
bsw_bswm_can_st_MainFuncMidIn( void )
{
    BswU1                    u1Ch;
    BswU1                    u1ChNum;
    BswU1                    u1Offset;
    BswU1                    u1Network;
    BswU1                    u1Edge;

#if ( BSW_BSWM_CS_MSG_DELIVER == BSW_BSWM_CS_MSGDELIVER_MIDDLE )
    bsw_bswm_can_ctrl_CbkPreCtrlRx();

#if ( BSW_BSWM_CS_FUNC_CANTX == BSW_USE )
#if ( BSW_BSWM_CAN_FUNC_TXERR_NOTIFY == BSW_USE )
    CanIf_MainFunctionTxFail();
#endif
#endif

    CanIf_MainFunctionRx();
#endif

    /* Edge detection */
    u1Offset = bsw_bswm_can_ctrl_u1ChOffset;
    u1ChNum = bsw_bswm_can_ctrl_u1ChNum;
    for( u1Ch = (BswU1)0U; u1Ch < u1ChNum; u1Ch++ )
    {
        /* Check other-node Aweke enable/disable */
        u1Edge = CanIf_EdgeGetStatus( u1Ch );
        if( u1Edge == (BswU1)CANIF_EDGE_EXIST )
        {
            u1Network = u1Ch + u1Offset;
            ComM_EcuM_WakeUpIndication( u1Network );
            bsw_bswm_can_st_CbkDetectEdge( u1Network );
        }
    }
}

/****************************************************************************/
/* Function Name | bsw_bswm_can_st_MainFuncMidCtrl                          */
/* Description   | Medium-priority control                                  */
/* Preconditions | When processing medium-priority periodic process         */
/* Parameters    | NONE                                                     */
/* Return Value  | NONE                                                     */
/* Notes         | Supported API : BswM_Can_MainFunctionMidCtrl             */
/****************************************************************************/
void
bsw_bswm_can_st_MainFuncMidCtrl( void )
{
#if ( BSW_BSWM_CS_FUNC_CANDRV == BSW_USE )
    Can_MainFunction_Mode();
    Can_MainFunction_BusOff();
    Can_MainFunction_Fail();
#endif
    CanIf_MainFunction();
    CanSM_MainFunction();
#if ( BSW_BSWM_CS_CHRSTCTRL_FUNC == BSW_USE )
    bsw_bswm_can_ctrl_RestartChReq();
#endif

    CanNm_MainFunction();
}

/****************************************************************************/
/* Function Name | bsw_bswm_can_st_MainFuncMidOut                           */
/* Description   | Medium-priority output                                   */
/* Preconditions | When processing medium-priority periodic process         */
/* Parameters    | NONE                                                     */
/* Return Value  | NONE                                                     */
/* Notes         | Supported API : BswM_Can_MainFunctionMidOut              */
/****************************************************************************/
void
bsw_bswm_can_st_MainFuncMidOut( void )
{
#if ( BSW_BSWM_CS_FUNC_CANTP == BSW_USE )
#if ( BSW_BSWM_CS_MSG_DELIVER == BSW_BSWM_CS_MSGDELIVER_MIDDLE )
    bsw_bswm_can_CanTpMainFunction();
#endif
#endif
}

/****************************************************************************/
/* Function Name | bsw_bswm_can_st_MainPreComRx                             */
/* Description   | Periodic processing - Pre Com Rx                         */
/* Preconditions | Before Com_MainFunctionRx is called                      */
/* Parameters    | NONE                                                     */
/* Return Value  | NONE                                                     */
/* Notes         | Supported API : BswM_Can_MainFunctionPreComRx            */
/****************************************************************************/
void
bsw_bswm_can_st_MainPreComRx( void )
{
#if ( BSW_BSWM_CS_FUNC_J1939TP == BSW_USE )
    J1939Tp_MainFunctionRx();
#endif
}

/****************************************************************************/
/* Function Name | bsw_bswm_can_st_MainPostComTx                            */
/* Description   | Periodic processing - Post Com Tx                        */
/* Preconditions | After Com_MainFunctionTx is called                       */
/* Parameters    | NONE                                                     */
/* Return Value  | NONE                                                     */
/* Notes         | Supported API : BswM_Can_MainFunctionPostComTx           */
/****************************************************************************/
void
bsw_bswm_can_st_MainPostComTx( void )
{
#if ( BSW_BSWM_CS_FUNC_J1939TP == BSW_USE )
    J1939Tp_MainFunctionTx();
#endif
}

#if ( BSW_BSWM_CS_ECU_FAIL == BSW_NOUSE )
/****************************************************************************/
/* Function Name | bsw_bswm_can_st_DetectFail                               */
/* Description   | Notify of failure detection                              */
/* Preconditions | When processing medium-priority periodic process         */
/* Parameters    | NONE                                                     */
/* Return Value  | NONE                                                     */
/* Notes         | Supported API : BswM_Can_DetectFail                      */
/****************************************************************************/
void
bsw_bswm_can_st_DetectFail( void )
{
    BswM_CS_DetectFail();
}
#endif

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#endif /* ( BSW_BSWM_CS_FUNC_BSWMCAN == BSW_USE ) */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/10/16                                             */
/*  v1-1-0          :2018/12/12                                             */
/*  v2-0-0          :2021/12/02                                             */
/*  v2-1-0          :2022/09/15                                             */
/*  v3-0-0          :2025/01/29                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
