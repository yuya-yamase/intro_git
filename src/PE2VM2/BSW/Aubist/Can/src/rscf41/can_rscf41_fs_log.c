/* can_rscf41_fs_log_c_v2-2-1                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN/RSCF41/FS/LOGICAL/CODE                                */
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
#include "../../cfg/rscf41/can_rscf41_cfg_ext.h"
#include "../../cfg/rscf41/can_rscf41_cfg.h"

#include <can/common/can_cv_can.h>
#include <can/common/can_cv_cbk.h>

#if (CAN_CFG_CAN == CAN_USE)
#include <can/rscf41/can_rscf41.h>
#include <can/rscf41/can_rscf41_cm_phy.h>
#include <can/common/can_memmap.h>
#include <can/rscf41/can_rscf41_tb_log.h>
#include <can/rscf41/can_rscf41_st.h>
#include <can/rscf41/can_rscf41_fs.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define CAN_FS_MASK_LOWERBYTE           (0x00FFU)

#define CAN_FS_BITSHIFT_8               (8U)

#define CAN_FS_REGCHK_HIST_NONE         (0x5AU)
#if (CAN_CFG_CHKSTKREG_RESP == CAN_RESP_OPT_NOT_OK)
#define CAN_FS_REGCHK_HIST_OPT_NOT_BUSY (0xA5U)
#endif /* (CAN_CFG_CHKSTKREG_RESP == CAN_RESP_OPT_NOT_OK) */
#define CAN_FS_REGCHK_HIST_OK           (0x96U)
#if (CAN_CFG_CHKSTKREG_RESP == CAN_RESP_OPT_NOT_OK)
#define CAN_FS_REGCHK_HIST_OPT_NOT_OK   (0x69U)
#endif /* (CAN_CFG_CHKSTKREG_RESP == CAN_RESP_OPT_NOT_OK) */
#define CAN_FS_REGCHK_HIST_NG           (0x3CU)

#define CAN_FS_BUSOFF_NONE              (0x3CU)
#define CAN_FS_BUSOFF_EXIST             (0x5AU)


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
static uint8   Can_fs_CheckRamU2( uint16 u2Value );


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
static uint8 Can_fs_u1BusOffStatus[ CAN_CFG_CONTROLLERNUM_MAX ];
static uint8 Can_fs_u1RegChkWaitCnt[ CAN_CFG_CONTROLLERNUM_MAX ];
static uint8 Can_fs_u1RegChkHist[ CAN_CFG_CONTROLLERNUM_MAX ];


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Can_fs_Init                                              */
/* Description   | Fail Safe Function Initialization                        */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
void
Can_fs_Init( void )
{
    uint8  u1Controller;
    uint8  u1ControllerNumMax;

    /* RAM initialization process */
    u1ControllerNumMax = Can_tb_u1ControllerNumMax;
    for ( u1Controller = (uint8)0U; u1Controller < u1ControllerNumMax; u1Controller++ )
    {
        Can_fs_u1BusOffStatus[ u1Controller ]  = (uint8)CAN_FS_BUSOFF_NONE;
        Can_fs_u1RegChkWaitCnt[ u1Controller ] = (uint8)0U;
        Can_fs_u1RegChkHist[ u1Controller ]    = (uint8)CAN_FS_REGCHK_HIST_NONE;
    }
}


/****************************************************************************/
/* Function Name | Can_fs_ClearBusOffStatus                                 */
/* Description   | Bus Off Occurrence Information Clear                     */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
void
Can_fs_ClearBusOffStatus( uint8 u1Controller )
{
    Can_fs_u1BusOffStatus[ u1Controller ] = (uint8)CAN_FS_BUSOFF_NONE;
}


/****************************************************************************/
/* Function Name | Can_MainFunction_BusOff                                  */
/* Description   | Bus Off Periodic Process                                 */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
void
Can_MainFunction_BusOff( void )
{
    CanConst CanTbControllerConfigType *    ptCtrCfgTbl;
    uint16                                  u2ControllerStatus;
    uint8                                   u1Controller;
    uint8                                   u1ControllerNumMax;

    u1ControllerNumMax = Can_tb_u1ControllerNumMax;
    for ( u1Controller = (uint8)0U; u1Controller < u1ControllerNumMax; u1Controller++ )
    {
        ptCtrCfgTbl = &(Can_tb_stControllerCfgTbl[ u1Controller ]);
        if (( ptCtrCfgTbl->u1ControllerActivation == (uint8)CAN_TRUE )
        &&  ( ptCtrCfgTbl->u1ControllerUse        == (uint8)CAN_USE ) )
        {
            if ( Can_tb_stControllerCfgTbl[ u1Controller ].u1BusoffRecovery == (uint8)CAN_MANUAL )
            {
                /* Bus off occurrence information acquisition process */
                if ( Can_tb_stControllerCfgTbl[ u1Controller ].u1BusoffProcessing == (uint8)CAN_POLLING )
                {
                    u2ControllerStatus = Can_st_u2ControllerStatus[ u1Controller ];
                    if (( u2ControllerStatus == (uint16)CAN_ST_CTRL_STARTED )
                    ||  ( u2ControllerStatus == (uint16)CAN_ST_CTRL_TO_STARTED )
                    ||  ( u2ControllerStatus == (uint16)CAN_ST_CTRL_TO_STOPPED_NML ))
                    {
                        (void)Can_fs_ChkBusOff( u1Controller ); /* MISRA DEVIATION: no return check required */
                    }
                }

                /* Bus off occurrence information check process */
                if ( Can_fs_u1BusOffStatus[ u1Controller ] != (uint8)CAN_FS_BUSOFF_NONE )
                {
                    Can_fs_u1BusOffStatus[ u1Controller ] = (uint8)CAN_FS_BUSOFF_NONE;

                    Can_st_ControllerStop( u1Controller );

                    CanIf_ControllerBusOff( u1Controller );
                }
            }
            else
            {
                u2ControllerStatus = Can_st_u2ControllerStatus[ u1Controller ];
                if (( u2ControllerStatus == (uint16)CAN_ST_CTRL_STARTED )
                ||  ( u2ControllerStatus == (uint16)CAN_ST_CTRL_TO_STARTED ))
                {
                    /* Automatic recovery process from bus off */
                    Can_fs_BusOffRecovery( u1Controller );
                }
            }
        }
    }
}


/****************************************************************************/
/* Function Name | Can_fs_BusOffInd                                         */
/* Description   | Controller Bus Off Detection Notification                */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
void
Can_fs_BusOffInd( uint8 u1Controller )
{
    Can_fs_u1BusOffStatus[ u1Controller ] = (uint8)CAN_FS_BUSOFF_EXIST;
}


/****************************************************************************/
/* Function Name | Can_CheckStuckRegister                                   */
/* Description   | Register Stuck Check                                     */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 Controller                                         */
/* Return Value  | Can_ReturnType                                           */
/*               |   CAN_OK                                                 */
/*               |   CAN_NOT_OK                                             */
/*               |   CAN_BUSY                                               */
/*               |   CAN_OPT_NOT_OK                                         */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
Can_ReturnType
Can_CheckStuckRegister( uint8 Controller )
{
    uint16  u2ControllerStatus;
    uint8   u1Ret;
    uint8   u1ChkResult;
    uint8   u1RegChkWaitCnt;
    uint8   u1RegChkHist;
    uint8   u1RegChkNum;

    u1Ret = (uint8)CAN_NOT_OK;

    u2ControllerStatus = Can_st_u2ControllerStatus[ Controller ];
    if ( u2ControllerStatus == (uint16)CAN_ST_CTRL_STOPPED )
    {
        u1RegChkHist = Can_fs_u1RegChkHist[ Controller ];
#if (CAN_CFG_CHKSTKREG_RESP == CAN_RESP_OPT_NOT_OK)
        if ( (u1RegChkHist == (uint8)CAN_FS_REGCHK_HIST_NONE) || (u1RegChkHist == (uint8)CAN_FS_REGCHK_HIST_OPT_NOT_BUSY) )
#else /* (CAN_CFG_CHKSTKREG_RESP != CAN_RESP_OPT_NOT_OK) */
        if ( u1RegChkHist == (uint8)CAN_FS_REGCHK_HIST_NONE )
#endif /* (CAN_CFG_CHKSTKREG_RESP) */
        {
            u1RegChkWaitCnt = Can_fs_u1RegChkWaitCnt[ Controller ];
            u1RegChkNum = Can_tb_u1RegChkNum;
            if ( u1RegChkWaitCnt < u1RegChkNum )
            {
                /* Register sticking check process */
                u1ChkResult = Can_fs_ChkReg( Controller, u1RegChkWaitCnt );
                if ( u1ChkResult == (uint8)CAN_FS_REGCHK_EXIST )
                {
                    Can_fs_u1RegChkHist[ Controller ] = (uint8)CAN_FS_REGCHK_HIST_NG;
                }
                else
                {
#if (CAN_CFG_CHKSTKREG_RESP == CAN_RESP_OPT_NOT_OK)
                    if ( u1ChkResult == (uint8)CAN_FS_REGCHK_OPT_EXIST )
                    {
                        Can_fs_u1RegChkHist[ Controller ] = (uint8)CAN_FS_REGCHK_HIST_OPT_NOT_BUSY;
                    }
#endif /* (CAN_CFG_CHKSTKREG_RESP == CAN_RESP_OPT_NOT_OK) */

                    u1RegChkWaitCnt++;
                    Can_fs_u1RegChkWaitCnt[ Controller ] = u1RegChkWaitCnt;

                    if ( u1RegChkWaitCnt < u1RegChkNum )
                    {
                        u1Ret = (uint8)CAN_BUSY;
                    }
                    else
                    {
                        Can_st_SetConfigMbox( Controller );

#if (CAN_CFG_CHKSTKREG_RESP == CAN_RESP_OPT_NOT_OK)
                        if ( Can_fs_u1RegChkHist[ Controller ] == (uint8)CAN_FS_REGCHK_HIST_OPT_NOT_BUSY )
                        {
                            Can_fs_u1RegChkHist[ Controller ] = (uint8)CAN_FS_REGCHK_HIST_OPT_NOT_OK;
                            u1Ret = (uint8)CAN_OPT_NOT_OK;
                        }
                        else
#endif /* (CAN_CFG_CHKSTKREG_RESP == CAN_RESP_OPT_NOT_OK) */
                        {
                            Can_fs_u1RegChkHist[ Controller ] = (uint8)CAN_FS_REGCHK_HIST_OK;
                            u1Ret = (uint8)CAN_OK;
                        }
                    }
                }
            }
        }
        else if ( u1RegChkHist == (uint8)CAN_FS_REGCHK_HIST_OK )
        {
            u1Ret = (uint8)CAN_OK;
        }
#if (CAN_CFG_CHKSTKREG_RESP == CAN_RESP_OPT_NOT_OK)
        else if ( u1RegChkHist == (uint8)CAN_FS_REGCHK_HIST_OPT_NOT_OK )
        {
            u1Ret = (uint8)CAN_OPT_NOT_OK;
        }
#endif /* (CAN_CFG_CHKSTKREG_RESP == CAN_RESP_OPT_NOT_OK) */
        else /* MISRA DEVIATION: no process */
        {
            /* If there is a failure history, or if there is an abnormal value due to garbled RAM, a failure is responded. */
        }
    }
    return (u1Ret);
}


/****************************************************************************/
/* Function Name | Can_RefreshRegister                                      */
/* Description   | Register Refresh                                         */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 Controller                                         */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
void
Can_RefreshRegister( uint8 Controller )
{
    Can_URefreshRegister( Controller );
}


/****************************************************************************/
/* Function Name | Can_MainFunction_Fail                                    */
/* Description   | Fail Periodic Process                                    */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
void
Can_MainFunction_Fail( void )
{
    CanConst CanTbControllerConfigType *    ptCtrCfgTbl;
    uint16                                  u2ControllerStatus;
    uint8                                   u1Controller;
    uint8                                   u1ControllerNumMax;
    uint8                                   u1ChkRamResult;
    uint8                                   u1ChkMpuResult;

    u1ControllerNumMax = Can_tb_u1ControllerNumMax;
    for ( u1Controller = (uint8)0U; u1Controller < u1ControllerNumMax; u1Controller++ )
    {
        ptCtrCfgTbl = &(Can_tb_stControllerCfgTbl[ u1Controller ]);
        if (( ptCtrCfgTbl->u1ControllerActivation == (uint8)CAN_TRUE )
        &&  ( ptCtrCfgTbl->u1ControllerUse        == (uint8)CAN_USE ) )
        {
            /* Garbled check process of controller state */
            u2ControllerStatus = Can_st_u2ControllerStatus[ u1Controller ];
            u1ChkRamResult = Can_fs_CheckRamU2( u2ControllerStatus );

            /* MPU abnormality check process */
            u1ChkMpuResult = Can_fs_CheckMpu( u1Controller );

            if (( u1ChkRamResult != (uint8)CAN_PROC_OK )
            ||  ( u1ChkMpuResult != (uint8)CAN_NONE ))
            {
                Can_st_ControllerStop( u1Controller );

                CanIf_ControllerFail( u1Controller );

                break;
            }
        }
    }
}


/****************************************************************************/
/* Function Name | Can_GetErrorStatus                                       */
/* Description   | Error Status Get                                         */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 Controller                                         */
/* Return Value  | Can_ErrStType                                            */
/*               |   CAN_ERRST_NOT_OK                                       */
/*               |   CAN_ERRST_ERROR_ACTIVE                                 */
/*               |   CAN_ERRST_ERROR_PASSIVE                                */
/*               |   CAN_ERRST_BUS_OFF                                      */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
Can_ErrStType
Can_GetErrorStatus( uint8 Controller )
{
    uint16  u2ControllerStatus;
    uint8   u1Ret;

    u1Ret = (uint8)CAN_ERRST_NOT_OK;

    if ( Can_tb_stControllerCfgTbl[ Controller ].u1BusoffRecovery == (uint8)CAN_AUTO )
    {
        u2ControllerStatus = Can_st_u2ControllerStatus[ Controller ];
        if ( u2ControllerStatus == (uint16)CAN_ST_CTRL_STARTED )
        {
            /* Error status acquisition process */
            u1Ret = Can_fs_GetErrorStatus( Controller );
        }
    }

    return (u1Ret);
}


/****************************************************************************/
/* Function Name | Can_fs_PrepChkRegRetry                                   */
/* Description   | Register Stuck Check Retry Preparation Process           */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
void
Can_fs_PrepChkRegRetry( uint8 u1Controller )
{

    if( Can_fs_u1RegChkHist[ u1Controller ] != (uint8)CAN_FS_REGCHK_HIST_OK )
    {
        Can_fs_u1RegChkHist[ u1Controller ]    = (uint8)CAN_FS_REGCHK_HIST_NONE;
        Can_fs_u1RegChkWaitCnt[ u1Controller ] = (uint8)0U;
    }

    /* Retry preparation process for register sticking check */
    Can_fs_PhyPrepChkRegRetry( u1Controller );
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Can_fs_CheckRamU2                                        */
/* Description   | Unsigned 2byte RAM Garbled Check                         */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint16 u2Value                                           */
/* Return Value  | uint8                                                    */
/*               |   CAN_PROC_OK                                            */
/*               |   CAN_PROC_NG                                            */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
static uint8
Can_fs_CheckRamU2( uint16 u2Value )
{
    uint16  u2HiByte;
    uint16  u2LoByte;
    uint16  u2Sum;
    uint8   u1Ret;

    u1Ret = (uint8)CAN_PROC_OK;

    u2HiByte = (uint16)(u2Value >> CAN_FS_BITSHIFT_8);
    u2LoByte = u2Value  & (uint16)CAN_FS_MASK_LOWERBYTE;

    u2Sum = (uint16)(u2HiByte + u2LoByte);
    if ( u2Sum != (uint16)CAN_FS_MASK_LOWERBYTE )
    {
        u1Ret = (uint8)CAN_PROC_NG;
    }

    return (u1Ret);
}


#endif /* (CAN_CFG_CAN == CAN_USE) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-2-1         :2022/03/08                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
