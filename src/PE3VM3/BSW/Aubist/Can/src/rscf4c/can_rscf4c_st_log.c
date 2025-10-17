/* can_rscf4c_st_log_c_v3-0-0                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN/RSCF4C/ST/LOGICAL/CODE                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <can/common/can_cm_log.h>
#include <can/common/can_syscfg_ext.h>

#include <Can.h>
#include <CanIf_Cbk.h>
#include "../../cfg/common/can_cv_cfg.h"
#include "../../cfg/rscf4c/can_rscf4c_cfg_ext.h"
#include "../../cfg/rscf4c/can_rscf4c_cfg.h"

#include <can/common/can_cv_can.h>
#include <can/common/can_cv_cbk.h>
#include <can/common/can_memmap.h>
#include <can/rscf4c/can_rscf4c.h>

#if (CAN_CFG_CAN == CAN_USE)
#include <can/rscf4c/can_rscf4c_tb_log.h>
#include <can/rscf4c/can_rscf4c_tx.h>
#include <can/rscf4c/can_rscf4c_fs.h>
#include <can/rscf4c/can_rscf4c_st.h>


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
uint16 Can_st_u2ControllerStatus[ CAN_CFG_CONTROLLERNUM_MAX ];


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Can_Init                                                 */
/* Description   | Can Module Initialization                                */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 CanConfigSet                                       */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
void
Can_Init( uint8 CanConfigSet )
{
    uint8  u1Controller;
    uint8  u1ControllerNumMax;
    uint8  u1InitRegRet;

    u1ControllerNumMax = Can_tb_u1ControllerNumMax;
    for ( u1Controller = (uint8)0U; u1Controller < u1ControllerNumMax; u1Controller++ )
    {
        Can_st_u2ControllerStatus[ u1Controller ] = (uint16)CAN_ST_CTRL_UNINIT;
    }

    Can_tx_Init();

    Can_fs_Init();

    /* Register initialization process */
    u1InitRegRet = Can_st_InitReg();

    if ( u1InitRegRet == (uint8)CAN_PROC_OK )
    {
        for ( u1Controller = (uint8)0U; u1Controller < u1ControllerNumMax; u1Controller++ )
        {
            if ( Can_tb_stControllerCfgTbl[ u1Controller ].u1ControllerActivation == (uint8)CAN_TRUE )
            {
                Can_st_u2ControllerStatus[ u1Controller ] = (uint16)CAN_ST_CTRL_INIT;
            }
        }
    }
}


/****************************************************************************/
/* Function Name | Can_InitController                                       */
/* Description   | Can Controller Initialization                            */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 Controller                                         */
/*               | uint8 CanControllerBaudrateConfigSet                     */
/* Return Value  | Can_ReturnType                                           */
/*               |   CAN_OK                                                 */
/*               |   CAN_NOT_OK                                             */
/*               |   CAN_BUSY                                               */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
Can_ReturnType
Can_InitController( uint8 Controller, uint8 CanControllerBaudrateConfigSet )
{
    uint16  u2ControllerStatus;
    uint8   u1Ret;
    uint8   u1ModeChgRet;
    uint8   u1ChkParam;

    u1Ret = (uint8)CAN_NOT_OK;

    u2ControllerStatus = Can_st_u2ControllerStatus[ Controller ];
    if ( u2ControllerStatus == (uint16)CAN_ST_CTRL_INIT )
    {
        /* Register setting process */
        u1ModeChgRet = Can_st_SetControl( Controller );
        if ( u1ModeChgRet == (uint8)CAN_PROC_OK )
        {
            /* Communication parameter check process */
            u1ChkParam = Can_fs_ChkParameter( Controller );
            if ( u1ChkParam == (uint8)CAN_NONE )
            {
                Can_fs_ClearBusOffStatus( Controller );

                Can_st_SetConfigMbox( Controller );

                Can_st_u2ControllerStatus[ Controller ] = (uint16)CAN_ST_CTRL_STOPPED;

                u1Ret = (uint8)CAN_OK;
            }
        }
        else    /* u1ModeChgRet == (uint8)CAN_PROC_BUSY */
        {
            u1Ret = (uint8)CAN_BUSY;
        }
    }
    else if ( u2ControllerStatus == (uint16)CAN_ST_CTRL_STOPPED )
    {
        /* Retry preparation process for register sticking check */
        Can_fs_PrepChkRegRetry( Controller );
        u1Ret = (uint8)CAN_OK;
    }
    else /* MISRA DEVIATION: no process */
    {
        /* Respond CAN_NOT_OK when called in a state other than the above */
    }

    return (u1Ret);
}


/****************************************************************************/
/* Function Name | Can_SetControllerMode                                    */
/* Description   | Can Controller Mode Set                                  */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 Controller                                         */
/*               | Can_StateTransitionType Transition                       */
/* Return Value  | Can_ReturnType                                           */
/*               |   CAN_OK                                                 */
/*               |   CAN_NOT_OK                                             */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
Can_ReturnType
Can_SetControllerMode( uint8 Controller, Can_StateTransitionType Transition )
{
    uint16  u2ControllerStatus;
    uint8   u1ModeChgRet;
    uint8   u1Ret;

    u1Ret = (uint8)CAN_NOT_OK;

    if ( Transition == (uint8)CAN_T_START )
    {
        /* Communication start process */
        u2ControllerStatus = Can_st_u2ControllerStatus[ Controller ];
        if (( u2ControllerStatus == (uint16)CAN_ST_CTRL_STOPPED )
        ||  ( u2ControllerStatus == (uint16)CAN_ST_CTRL_TO_STOPPED_NML )
        ||  ( u2ControllerStatus == (uint16)CAN_ST_CTRL_TO_STOPPED_RST ))
        {
            Can_st_u2ControllerStatus[ Controller ] = (uint16)CAN_ST_CTRL_TO_STARTED;

            Can_fs_ClearBusOffStatus( Controller );

            u1ModeChgRet = Can_st_Start( Controller );
            if ( u1ModeChgRet == (uint8)CAN_PROC_OK )
            {
                Can_st_u2ControllerStatus[ Controller ] = (uint16)CAN_ST_CTRL_STARTED;

                CanIf_ControllerModeIndication( Controller, (uint8)CANIF_CS_STARTED );
            }

            u1Ret = (uint8)CAN_OK;
        }
    }
    else if ( Transition == (uint8)CAN_T_STOP )
    {
        /* Communication stop process */
        u2ControllerStatus = Can_st_u2ControllerStatus[ Controller ];
        if (( u2ControllerStatus == (uint16)CAN_ST_CTRL_TO_STARTED )
        ||  ( u2ControllerStatus == (uint16)CAN_ST_CTRL_STARTED ))
        {
            Can_st_u2ControllerStatus[ Controller ] = (uint16)CAN_ST_CTRL_TO_STOPPED_NML;

            if ( Can_tb_stControllerCfgTbl[ Controller ].u1BusoffRecovery == (uint8)CAN_MANUAL )
            {
                if ( Can_tb_stControllerCfgTbl[ Controller ].u1BusoffProcessing == (uint8)CAN_POLLING )
                {
                    (void)Can_fs_ChkBusOff( Controller ); /* MISRA DEVIATION: no return check required */
                }
            }

            u1ModeChgRet = Can_st_Stop( Controller );
            if ( u1ModeChgRet == (uint8)CAN_PROC_OK )
            {
                Can_st_u2ControllerStatus[ Controller ] = (uint16)CAN_ST_CTRL_STOPPED;

                CanIf_ControllerModeIndication( Controller, (uint8)CANIF_CS_STOPPED );
            }

            u1Ret = (uint8)CAN_OK;
        }
        else if (( u2ControllerStatus == (uint16)CAN_ST_CTRL_STOPPED )
             ||  ( u2ControllerStatus == (uint16)CAN_ST_CTRL_TO_STOPPED_NML )
             ||  ( u2ControllerStatus == (uint16)CAN_ST_CTRL_TO_STOPPED_RST ))
        {
            u1Ret = (uint8)CAN_OK;
        }
        else /* MISRA DEVIATION: no process */
        {
            /* Respond CAN_NOT_OK when called in a state other than the above */
        }
    }
    else /* MISRA DEVIATION: no process */
    {
        /* When a state other than CAN_T_START and CAN_T_STOP is requested, CAN_NOT_OK is returned. */
    }
    return (u1Ret);
}


/****************************************************************************/
/* Function Name | Can_MainFunction_Mode                                    */
/* Description   | Mode Confirmation Periodic Process                       */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
void
Can_MainFunction_Mode( void )
{
    uint16  u2ControllerStatus;
    uint8   u1Controller;
    uint8   u1ControllerNumMax;
    uint8   u1ModeChgRet;

    u1ControllerNumMax = Can_tb_u1ControllerNumMax;
    for ( u1Controller = (uint8)0U; u1Controller < u1ControllerNumMax; u1Controller++ )
    {
        u2ControllerStatus = Can_st_u2ControllerStatus[ u1Controller ];
        if ( u2ControllerStatus == (uint16)CAN_ST_CTRL_TO_STARTED )
        {
            /* Communication start check process */
            u1ModeChgRet = Can_st_ChkStart( u1Controller );
            if ( u1ModeChgRet == (uint8)CAN_PROC_OK )
            {
                Can_st_u2ControllerStatus[ u1Controller ] = (uint16)CAN_ST_CTRL_STARTED;

                CanIf_ControllerModeIndication( u1Controller, (uint8)CANIF_CS_STARTED );
            }
        }
        else if ( u2ControllerStatus == (uint16)CAN_ST_CTRL_TO_STOPPED_NML )
        {
            if ( Can_tb_stControllerCfgTbl[ u1Controller ].u1BusoffRecovery == (uint8)CAN_MANUAL )
            {
                (void)Can_fs_ChkBusOff( u1Controller ); /* MISRA DEVIATION: no return check required */
            }

            /* Communication stop check process */
            u1ModeChgRet = Can_st_ChkStop( u1Controller );
            if ( u1ModeChgRet == (uint8)CAN_PROC_OK )
            {
                Can_st_u2ControllerStatus[ u1Controller ] = (uint16)CAN_ST_CTRL_STOPPED;

                CanIf_ControllerModeIndication( u1Controller, (uint8)CANIF_CS_STOPPED );
            }
        }
        else if ( u2ControllerStatus == (uint16)CAN_ST_CTRL_TO_STOPPED_RST )
        {
            /* Reinitialization check process */
            u1ModeChgRet = Can_st_ChkReset( u1Controller );
            if ( u1ModeChgRet == (uint8)CAN_PROC_OK )
            {
                Can_fs_ClearBusOffStatus( u1Controller );

                Can_st_SetConfigMbox( u1Controller );

                Can_st_u2ControllerStatus[ u1Controller ] = (uint16)CAN_ST_CTRL_STOPPED;
            }
        }
        else /* MISRA DEVIATION: no process */
        {
            /* Do nothing except waiting for communication start, communication stop, and reinitialization. */
        }
    }
}


/****************************************************************************/
/* Function Name | Can_Shutdown                                             */
/* Description   | Shutdown                                                 */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
void
Can_Shutdown( void )
{
    uint8  u1Controller;
    uint8  u1ControllerNumMax;

    Can_DI()
    u1ControllerNumMax = Can_tb_u1ControllerNumMax;
    for ( u1Controller = (uint8)0U; u1Controller < u1ControllerNumMax; u1Controller++ )
    {
        Can_st_u2ControllerStatus[ u1Controller ] = (uint16)CAN_ST_CTRL_UNINIT;
    }
    Can_EI()

    /* Shutdown process */
    Can_st_ShutdownReg();

    for ( u1Controller = (uint8)0U; u1Controller < u1ControllerNumMax; u1Controller++ )
    {
        Can_fs_ClearBusOffStatus( u1Controller );
    }
}


/****************************************************************************/
/* Function Name | Can_ResetController                                      */
/* Description   | Can Controller Reinitialization                          */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 Controller                                         */
/*               | uint8 CanControllerBaudrateConfigSet                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
void
Can_ResetController( uint8 Controller, uint8 CanControllerBaudrateConfigSet )
{
    uint8  u1Ret;

    Can_st_u2ControllerStatus[ Controller ] = (uint16)CAN_ST_CTRL_TO_STOPPED_RST;

    Can_tx_ClearTxInf( Controller );

    /* Reset process */
    u1Ret = Can_st_Reset( Controller );
    if ( u1Ret == (uint8)CAN_PROC_OK )
    {
        Can_st_SetConfigMbox( Controller );

        Can_st_u2ControllerStatus[ Controller ] = (uint16)CAN_ST_CTRL_STOPPED;
    }

    Can_fs_ClearBusOffStatus( Controller );
}


/****************************************************************************/
/* Function Name | Can_SetBaudrate                                          */
/* Description   | Baud Rate Set                                            */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 Controller                                         */
/*               | uint16 BaudRateConfigID                                  */
/* Return Value  | Can_ReturnType                                           */
/*               |   CAN_OK                                                 */
/*               |   CAN_NOT_OK                                             */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
Can_ReturnType
Can_SetBaudrate( uint8 Controller, uint16 BaudRateConfigID )
{
    uint8  u1BRChgRet;
    uint8  u1Ret;

    u1Ret = (uint8)CAN_NOT_OK;

    /* Baud rate setting process */
    u1BRChgRet = Can_st_SetBaudrate( Controller, BaudRateConfigID );
    if ( u1BRChgRet == (uint8)CAN_PROC_OK )
    {
        u1Ret = (uint8)CAN_OK;
    }

    return (u1Ret);
}


/****************************************************************************/
/* Function Name | Can_CheckStopCompletion                                  */
/* Description   | Communication Stop Completion Confirmation               */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 Controller                                         */
/* Return Value  | Can_ReturnType                                           */
/*               |   CAN_OK                                                 */
/*               |   CAN_NOT_OK                                             */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
Can_ReturnType
Can_CheckStopCompletion( uint8 Controller )
{
    uint16  u2ControllerStatus;
    uint8   u1Ret;

    u1Ret = (uint8)CAN_OK;

    u2ControllerStatus = Can_st_u2ControllerStatus[ Controller ];
    if (( u2ControllerStatus != (uint16)CAN_ST_CTRL_INIT    )
    &&  ( u2ControllerStatus != (uint16)CAN_ST_CTRL_STOPPED ))
    {
        u1Ret = (uint8)CAN_NOT_OK;
    }

    return (u1Ret);
}


/****************************************************************************/
/* Function Name | Can_GetControllerStatus                                  */
/* Description   | Can Controller Status Get                                */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 Controller                                         */
/* Return Value  | Can_CtrlStType                                           */
/*               |   CAN_CTRLST_NOT_OK                                      */
/*               |   CAN_CTRLST_UNINIT                                      */
/*               |   CAN_CTRLST_INIT                                        */
/*               |   CAN_CTRLST_STOPPED                                     */
/*               |   CAN_CTRLST_STARTED                                     */
/*               |   CAN_CTRLST_TO_STOPPED_NML                              */
/*               |   CAN_CTRLST_TO_STOPPED_RST                              */
/*               |   CAN_CTRLST_TO_STARTED                                  */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
Can_CtrlStType
Can_GetControllerStatus( uint8 Controller )
{
    uint16  u2ControllerStatus;
    uint8   u1Ret;

    u1Ret = (uint8)CAN_CTRLST_NOT_OK;

    u2ControllerStatus = Can_st_u2ControllerStatus[ Controller ];

    if ( u2ControllerStatus == (uint16)CAN_ST_CTRL_STOPPED )
    {
        u1Ret = (uint8)CAN_CTRLST_STOPPED;
    }
    else if ( u2ControllerStatus == (uint16)CAN_ST_CTRL_STARTED )
    {
        u1Ret = (uint8)CAN_CTRLST_STARTED;
    }
    else if ( u2ControllerStatus == (uint16)CAN_ST_CTRL_TO_STOPPED_NML )
    {
        u1Ret = (uint8)CAN_CTRLST_TO_STOPPED_NML;
    }
    else if ( u2ControllerStatus == (uint16)CAN_ST_CTRL_TO_STOPPED_RST )
    {
        u1Ret = (uint8)CAN_CTRLST_TO_STOPPED_RST;
    }
    else if ( u2ControllerStatus == (uint16)CAN_ST_CTRL_TO_STARTED )
    {
        u1Ret = (uint8)CAN_CTRLST_TO_STARTED;
    }
    else if ( u2ControllerStatus == (uint16)CAN_ST_CTRL_INIT )
    {
        u1Ret = (uint8)CAN_CTRLST_INIT;
    }
    else if ( u2ControllerStatus == (uint16)CAN_ST_CTRL_UNINIT )
    {
        u1Ret = (uint8)CAN_CTRLST_UNINIT;
    }
    else /* MISRA DEVIATION: no process */
    {
        /* Respond CAN_CTRLST_NOT_OK when the CAN controller state is garbled */
    }

    return (u1Ret);
}


/****************************************************************************/
/* Function Name | Can_st_ControllerStop                                    */
/* Description   | Controller Stop Instruction                              */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
void
Can_st_ControllerStop( uint8 u1Controller )
{
    uint8  u1ModeChgRet;

    Can_st_u2ControllerStatus[ u1Controller ] = (uint16)CAN_ST_CTRL_TO_STOPPED_NML;

    /* Communication stop process */
    u1ModeChgRet = Can_st_Stop( u1Controller );
    if ( u1ModeChgRet == (uint8)CAN_PROC_OK )
    {
        Can_st_u2ControllerStatus[ u1Controller ] = (uint16)CAN_ST_CTRL_STOPPED;
    }
}


/****************************************************************************/
/* Function Name | Can_st_StopInd                                           */
/* Description   | Controller Stop Notification                             */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
void
Can_st_StopInd( uint8 u1Controller )
{
    uint16  u2ControllerStatus;

    u2ControllerStatus = Can_st_u2ControllerStatus[ u1Controller ];
    if (( u2ControllerStatus == (uint16)CAN_ST_CTRL_STARTED )
    ||  ( u2ControllerStatus == (uint16)CAN_ST_CTRL_TO_STARTED )
    ||  ( u2ControllerStatus == (uint16)CAN_ST_CTRL_TO_STOPPED_NML )
    ||  ( u2ControllerStatus == (uint16)CAN_ST_CTRL_TO_STOPPED_RST ))
    {
        Can_st_u2ControllerStatus[ u1Controller ] = (uint16)CAN_ST_CTRL_STOPPED;
    }
}


/****************************************************************************/
/* Function Name | Can_st_PreStart                                          */
/* Description   | Controller Start Preprocess                              */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
void
Can_st_PreStart( uint8 u1Controller )
{
    Can_UPreStart( u1Controller );
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


#endif /* (CAN_CFG_CAN == CAN_USE) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-2-0         :2021/12/22                                              */
/*  v3-0-0         :2025/02/13                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
