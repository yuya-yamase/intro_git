/* can_cv_c_v2-2-2                                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN/CV/CODE                                               */
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

#if (CAN_CFG_IP0 == CAN_IP_RSC)
#include "../../cfg/rsc/can_rsc_cfg_ext.h"
#include "../../cfg/rsc/can_rsc_cfg.h"

#elif (CAN_CFG_IP0 == CAN_IP_RSCF2)
#include "../../cfg/rscf2/can_rscf2_cfg_ext.h"
#include "../../cfg/rscf2/can_rscf2_cfg.h"

#elif (CAN_CFG_IP0 == CAN_IP_RSCF3)
#include "../../cfg/rscf3/can_rscf3_cfg_ext.h"
#include "../../cfg/rscf3/can_rscf3_cfg.h"

#elif (CAN_CFG_IP0 == CAN_IP_RSCF3C)
#include "../../cfg/rscf3c/can_rscf3c_cfg_ext.h"
#include "../../cfg/rscf3c/can_rscf3c_cfg.h"

#elif (CAN_CFG_IP0 == CAN_IP_RSCF4)
#include "../../cfg/rscf4/can_rscf4_cfg_ext.h"
#include "../../cfg/rscf4/can_rscf4_cfg.h"

#elif (CAN_CFG_IP0 == CAN_IP_RSCF4C)
#include "../../cfg/rscf4c/can_rscf4c_cfg_ext.h"
#include "../../cfg/rscf4c/can_rscf4c_cfg.h"

#elif (CAN_CFG_IP0 == CAN_IP_RSCF41)
#include "../../cfg/rscf41/can_rscf41_cfg_ext.h"
#include "../../cfg/rscf41/can_rscf41_cfg.h"

#else /* ((CAN_CFG_IP0 != CAN_IP_RSC) && (CAN_CFG_IP0 != CAN_IP_RSCF2) && (CAN_CFG_IP0 != CAN_IP_RSCF3) && (CAN_CFG_IP0 != CAN_IP_RSCF3C) && (CAN_CFG_IP0 != CAN_IP_RSCF4) && (CAN_CFG_IP0 != CAN_IP_RSCF4C) && (CAN_CFG_IP0 != CAN_IP_RSCF41)) */
#include "../../cfg/rscf41c/can_rscf41c_cfg_ext.h"
#include "../../cfg/rscf41c/can_rscf41c_cfg.h"
#endif /* (CAN_CFG_IP0) */

#include <can/common/can_cv_can.h>
#include <can/common/can_cv_cbk.h>
#include <can/common/can_memmap.h>

#if (CAN_CFG_CV == CAN_USE)
#include <can/common/can_cv.h>


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
    Can_cv_ip0_stFuncTbl.Init( CanConfigSet );
#ifdef CAN_TEST_JGXSTACK
    Can_IP0_Init( CanConfigSet );
#endif /* CAN_TEST_JGXSTACK */
    Can_cv_ip1_stFuncTbl.Init( CanConfigSet );
#ifdef CAN_TEST_JGXSTACK
    Can_IP1_Init( CanConfigSet );
#endif /* CAN_TEST_JGXSTACK */
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
    uint8                       u1CanIPCh;
    uint8                       u1Ret;

    if ( Controller < (uint8)CAN_CV_IP0_CONTROLLERNUM_MAX )
    {
        /* CAN IP0 */
        u1CanIPCh = Controller;
        u1Ret     = Can_cv_ip0_stFuncTbl.InitController( u1CanIPCh, CanControllerBaudrateConfigSet );
#ifdef CAN_TEST_JGXSTACK
        u1Ret     = Can_IP0_InitController( u1CanIPCh, CanControllerBaudrateConfigSet );
#endif /* CAN_TEST_JGXSTACK */
    }
    else
    {
        /* CAN IP1 */
        u1CanIPCh = Controller - (uint8)CAN_CV_IP0_CONTROLLERNUM_MAX;
        u1Ret     = Can_cv_ip1_stFuncTbl.InitController( u1CanIPCh, CanControllerBaudrateConfigSet );
#ifdef CAN_TEST_JGXSTACK
        u1Ret     = Can_IP1_InitController( u1CanIPCh, CanControllerBaudrateConfigSet );
#endif /* CAN_TEST_JGXSTACK */
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
    uint8                       u1CanIPCh;
    uint8                       u1Ret;

    if ( Controller < (uint8)CAN_CV_IP0_CONTROLLERNUM_MAX )
    {
        /* CAN IP0 */
        u1CanIPCh = Controller;
        u1Ret     = Can_cv_ip0_stFuncTbl.SetControllerMode( u1CanIPCh, Transition );
#ifdef CAN_TEST_JGXSTACK
        u1Ret     = Can_IP0_SetControllerMode( u1CanIPCh, Transition );
#endif /* CAN_TEST_JGXSTACK */
    }
    else
    {
        /* CAN IP1 */
        u1CanIPCh = Controller - (uint8)CAN_CV_IP0_CONTROLLERNUM_MAX;
        u1Ret     = Can_cv_ip1_stFuncTbl.SetControllerMode( u1CanIPCh, Transition );
#ifdef CAN_TEST_JGXSTACK
        u1Ret     = Can_IP1_SetControllerMode( u1CanIPCh, Transition );
#endif /* CAN_TEST_JGXSTACK */
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
    Can_cv_ip0_stFuncTbl.MainFunction_Mode();
#ifdef CAN_TEST_JGXSTACK
    Can_IP0_MainFunction_Mode();
#endif /* CAN_TEST_JGXSTACK */
    Can_cv_ip1_stFuncTbl.MainFunction_Mode();
#ifdef CAN_TEST_JGXSTACK
    Can_IP1_MainFunction_Mode();
#endif /* CAN_TEST_JGXSTACK */
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
    Can_cv_ip0_stFuncTbl.Shutdown();
#ifdef CAN_TEST_JGXSTACK
    Can_IP0_Shutdown();
#endif /* CAN_TEST_JGXSTACK */
    Can_cv_ip1_stFuncTbl.Shutdown();
#ifdef CAN_TEST_JGXSTACK
    Can_IP1_Shutdown();
#endif /* CAN_TEST_JGXSTACK */
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
    uint8                       u1CanIPCh;

    if ( Controller < (uint8)CAN_CV_IP0_CONTROLLERNUM_MAX )
    {
        /* CAN IP0 */
        u1CanIPCh = Controller;
        Can_cv_ip0_stFuncTbl.ResetController( u1CanIPCh, CanControllerBaudrateConfigSet );
#ifdef CAN_TEST_JGXSTACK
        Can_IP0_ResetController( u1CanIPCh, CanControllerBaudrateConfigSet );
#endif /* CAN_TEST_JGXSTACK */
    }
    else
    {
        /* CAN IP1 */
        u1CanIPCh = Controller - (uint8)CAN_CV_IP0_CONTROLLERNUM_MAX;
        Can_cv_ip1_stFuncTbl.ResetController( u1CanIPCh, CanControllerBaudrateConfigSet );
#ifdef CAN_TEST_JGXSTACK
        Can_IP1_ResetController( u1CanIPCh, CanControllerBaudrateConfigSet );
#endif /* CAN_TEST_JGXSTACK */
    }
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
    uint8                       u1CanIPCh;
    uint8                       u1Ret;

    if ( Controller < (uint8)CAN_CV_IP0_CONTROLLERNUM_MAX )
    {
        /* CAN IP0 */
        u1CanIPCh = Controller;
        u1Ret     = Can_cv_ip0_stFuncTbl.CheckStopCompletion( u1CanIPCh );
#ifdef CAN_TEST_JGXSTACK
        u1Ret     = Can_IP0_CheckStopCompletion( u1CanIPCh );
#endif /* CAN_TEST_JGXSTACK */
    }
    else
    {
        /* CAN IP1 */
        u1CanIPCh = Controller - (uint8)CAN_CV_IP0_CONTROLLERNUM_MAX;
        u1Ret     = Can_cv_ip1_stFuncTbl.CheckStopCompletion( u1CanIPCh );
#ifdef CAN_TEST_JGXSTACK
        u1Ret     = Can_IP1_CheckStopCompletion( u1CanIPCh );
#endif /* CAN_TEST_JGXSTACK */
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
    uint8                       u1Ret;
    uint8                       u1CanIPCh;

    if ( Controller < (uint8)CAN_CV_IP0_CONTROLLERNUM_MAX )
    {
        /* CAN IP0 */
        u1CanIPCh = Controller;
        u1Ret     = Can_cv_ip0_stFuncTbl.GetControllerStatus( u1CanIPCh );
#ifdef CAN_TEST_JGXSTACK
        u1Ret     = Can_IP0_GetControllerStatus( u1CanIPCh );
#endif /* CAN_TEST_JGXSTACK */
    }
    else
    {
        /* CAN IP1 */
        u1CanIPCh = Controller - (uint8)CAN_CV_IP0_CONTROLLERNUM_MAX;
        u1Ret     = Can_cv_ip1_stFuncTbl.GetControllerStatus( u1CanIPCh );
#ifdef CAN_TEST_JGXSTACK
        u1Ret     = Can_IP1_GetControllerStatus( u1CanIPCh );
#endif /* CAN_TEST_JGXSTACK */
    }

    return (u1Ret);
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
    Can_cv_ip0_stFuncTbl.MainFunction_BusOff();
#ifdef CAN_TEST_JGXSTACK
    Can_IP0_MainFunction_BusOff();
#endif /* CAN_TEST_JGXSTACK */
    Can_cv_ip1_stFuncTbl.MainFunction_BusOff();
#ifdef CAN_TEST_JGXSTACK
    Can_IP1_MainFunction_BusOff();
#endif /* CAN_TEST_JGXSTACK */
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
    uint8                       u1CanIPCh;
    uint8                       u1Ret;

    if ( Controller < (uint8)CAN_CV_IP0_CONTROLLERNUM_MAX )
    {
        /* CAN IP0 */
        u1CanIPCh = Controller;
        u1Ret     = Can_cv_ip0_stFuncTbl.CheckStuckRegister( u1CanIPCh );
#ifdef CAN_TEST_JGXSTACK
        u1Ret     = Can_IP0_CheckStuckRegister( u1CanIPCh );
#endif /* CAN_TEST_JGXSTACK */
    }
    else
    {
        /* CAN IP1 */
        u1CanIPCh = Controller - (uint8)CAN_CV_IP0_CONTROLLERNUM_MAX;
        u1Ret     = Can_cv_ip1_stFuncTbl.CheckStuckRegister( u1CanIPCh );
#ifdef CAN_TEST_JGXSTACK
        u1Ret     = Can_IP1_CheckStuckRegister( u1CanIPCh );
#endif /* CAN_TEST_JGXSTACK */
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
    if ( Controller < (uint8)CAN_CV_IP0_CONTROLLERNUM_MAX )
    {
        /* CAN IP0 */
        Can_cv_ip0_stFuncTbl.RefreshRegister( Controller );
#ifdef CAN_TEST_JGXSTACK
        Can_IP0_RefreshRegister( Controller );
#endif /* CAN_TEST_JGXSTACK */
    }
    else
    {
        /* CAN IP1 */
        Can_cv_ip1_stFuncTbl.RefreshRegister( Controller );
#ifdef CAN_TEST_JGXSTACK
        Can_IP1_RefreshRegister( Controller );
#endif /* CAN_TEST_JGXSTACK */
    }
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
    Can_cv_ip0_stFuncTbl.MainFunction_Fail();
#ifdef CAN_TEST_JGXSTACK
    Can_IP0_MainFunction_Fail();
#endif /* CAN_TEST_JGXSTACK */
    Can_cv_ip1_stFuncTbl.MainFunction_Fail();
#ifdef CAN_TEST_JGXSTACK
    Can_IP1_MainFunction_Fail();
#endif /* CAN_TEST_JGXSTACK */
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
    uint8                       u1CanIPCh;
    uint8                       u1Ret;

    if ( Controller < (uint8)CAN_CV_IP0_CONTROLLERNUM_MAX )
    {
        /* CAN IP0 */
        u1CanIPCh = Controller;
        u1Ret     = Can_cv_ip0_stFuncTbl.GetErrorStatus( u1CanIPCh );
#ifdef CAN_TEST_JGXSTACK
        u1Ret     = Can_IP0_GetErrorStatus( u1CanIPCh );
#endif /* CAN_TEST_JGXSTACK */
    }
    else
    {
        /* CAN IP1 */
        u1CanIPCh = Controller - (uint8)CAN_CV_IP0_CONTROLLERNUM_MAX;
        u1Ret     = Can_cv_ip1_stFuncTbl.GetErrorStatus( u1CanIPCh );
#ifdef CAN_TEST_JGXSTACK
        u1Ret     = Can_IP1_GetErrorStatus( u1CanIPCh );
#endif /* CAN_TEST_JGXSTACK */
    }

    return (u1Ret);
}


/****************************************************************************/
/* Function Name | Can_MainFunction_Read                                    */
/* Description   | Reception Periodic Process                               */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
void
Can_MainFunction_Read( void )
{
    Can_cv_ip0_stFuncTbl.MainFunction_Read();
#ifdef CAN_TEST_JGXSTACK
    Can_IP0_MainFunction_Read();
#endif /* CAN_TEST_JGXSTACK */
    Can_cv_ip1_stFuncTbl.MainFunction_Read();
#ifdef CAN_TEST_JGXSTACK
    Can_IP1_MainFunction_Read();
#endif /* CAN_TEST_JGXSTACK */
}


/****************************************************************************/
/* Function Name | Can_Write                                                */
/* Description   | Transmission Request                                     */
/* Preconditions | See Design Documents                                     */
/* Parameters    | Can_HwHandleType Hth                                     */
/*               | CanConstR Can_PduType* PduInfo                           */
/*               |   PduIdType  swPduHandle                                 */
/*               |   uint8      length                                      */
/*               |   Can_IdType id                                          */
/*               |   uint8*     sdu                                         */
/* Return Value  | Can_ReturnType                                           */
/*               |   CAN_OK                                                 */
/*               |   CAN_NOT_OK                                             */
/*               |   CAN_BUSY                                               */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
Can_ReturnType
Can_Write( Can_HwHandleType Hth, CanConstR Can_PduType* PduInfo )
{
    uint16                      u2ip0_HohNum;
    uint16                      u2ip1_HrhNum;
    uint16                      u2Hth;
    uint8                       u1Ret;

    u2ip0_HohNum = Can_cv_ip0_u2HohNum;
    u2ip1_HrhNum = Can_cv_ip1_u2HrhNum;
    if ( Hth < ( u2ip0_HohNum + u2ip1_HrhNum ) )
    {
        /* CAN IP0 */
        u2Hth = Hth - u2ip1_HrhNum;
        u1Ret = Can_cv_ip0_stFuncTbl.Write( u2Hth, PduInfo );
#ifdef CAN_TEST_JGXSTACK
        u1Ret = Can_IP0_Write( u2Hth, PduInfo );
        u1Ret = Can_Write_Dummy( u2Hth, PduInfo );
#endif /* CAN_TEST_JGXSTACK */
    }
    else
    {
        /* CAN IP1 */
        u2Hth = Hth - u2ip0_HohNum;
        u1Ret = Can_cv_ip1_stFuncTbl.Write( u2Hth, PduInfo );
#ifdef CAN_TEST_JGXSTACK
        u1Ret = Can_IP1_Write( u2Hth, PduInfo );
        u1Ret = Can_Write_Dummy( u2Hth, PduInfo );
#endif /* CAN_TEST_JGXSTACK */
    }

    return (u1Ret);
}


/****************************************************************************/
/* Function Name | Can_MainFunction_Write                                   */
/* Description   | Transmission Periodic Process                            */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
void
Can_MainFunction_Write( void )
{
    Can_cv_ip0_stFuncTbl.MainFunction_Write();
#ifdef CAN_TEST_JGXSTACK
    Can_IP0_MainFunction_Write();
    Can_MainFunction_Write_Dummy();
#endif /* CAN_TEST_JGXSTACK */
    Can_cv_ip1_stFuncTbl.MainFunction_Write();
#ifdef CAN_TEST_JGXSTACK
    Can_IP1_MainFunction_Write();
    Can_MainFunction_Write_Dummy();
#endif /* CAN_TEST_JGXSTACK */
}


/****************************************************************************/
/* Function Name | Can_AbortSend                                            */
/* Description   | Transmission Abort Request                               */
/* Preconditions | See Design Documents                                     */
/* Parameters    | Can_HwHandleType Hth                                     */
/* Return Value  | Can_ReturnType                                           */
/*               |   CAN_OK                                                 */
/*               |   CAN_NOT_OK                                             */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
Can_ReturnType
Can_AbortSend( Can_HwHandleType Hth )
{
    uint16                      u2ip0_HohNum;
    uint16                      u2ip1_HrhNum;
    uint16                      u2Hth;
    uint8                       u1Ret;

    u2ip0_HohNum = Can_cv_ip0_u2HohNum;
    u2ip1_HrhNum = Can_cv_ip1_u2HrhNum;
    if ( Hth < ( u2ip0_HohNum + u2ip1_HrhNum ) )
    {
        /* CAN IP0 */
        u2Hth = Hth - u2ip1_HrhNum;
        u1Ret = Can_cv_ip0_stFuncTbl.AbortSend( u2Hth );
#ifdef CAN_TEST_JGXSTACK
        u1Ret = Can_IP0_AbortSend( u2Hth );
        u1Ret = Can_AbortSend_Dummy( u2Hth );
#endif /* CAN_TEST_JGXSTACK */
    }
    else
    {
        /* CAN IP1 */
        u2Hth = Hth - u2ip0_HohNum;
        u1Ret = Can_cv_ip1_stFuncTbl.AbortSend( u2Hth );
#ifdef CAN_TEST_JGXSTACK
        u1Ret = Can_IP1_AbortSend( u2Hth );
        u1Ret = Can_AbortSend_Dummy( u2Hth );
#endif /* CAN_TEST_JGXSTACK */
    }

    return (u1Ret);
}


/****************************************************************************/
/* Function Name | Can_EdgeInit                                             */
/* Description   | Edge Detection Initialization                            */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 Controller                                         */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
void
Can_EdgeInit( uint8 Controller )
{
    if ( Controller < (uint8)CAN_CV_IP0_CONTROLLERNUM_MAX )
    {
        /* CAN IP0 */
        Can_cv_ip0_stFuncTbl.EdgeInit( Controller );
#ifdef CAN_TEST_JGXSTACK
        Can_IP0_EdgeInit( Controller );
#endif /* CAN_TEST_JGXSTACK */
    }
    else
    {
        /* CAN IP1 */
        Can_cv_ip1_stFuncTbl.EdgeInit( Controller );
#ifdef CAN_TEST_JGXSTACK
        Can_IP1_EdgeInit( Controller );
#endif /* CAN_TEST_JGXSTACK */
    }
}


/****************************************************************************/
/* Function Name | Can_EdgeEnableDetect                                     */
/* Description   | Edge Detection Enable                                    */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 Controller                                         */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
void
Can_EdgeEnableDetect( uint8 Controller )
{
    if ( Controller < (uint8)CAN_CV_IP0_CONTROLLERNUM_MAX )
    {
        /* CAN IP0 */
        Can_cv_ip0_stFuncTbl.EdgeEnableDetect( Controller );
#ifdef CAN_TEST_JGXSTACK
        Can_IP0_EdgeEnableDetect( Controller );
#endif /* CAN_TEST_JGXSTACK */
    }
    else
    {
        /* CAN IP1 */
        Can_cv_ip1_stFuncTbl.EdgeEnableDetect( Controller );
#ifdef CAN_TEST_JGXSTACK
        Can_IP1_EdgeEnableDetect( Controller );
#endif /* CAN_TEST_JGXSTACK */
    }
}


/****************************************************************************/
/* Function Name | Can_EdgeDisableDetect                                    */
/* Description   | Edge Detection Disable                                   */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 Controller                                         */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
void
Can_EdgeDisableDetect( uint8 Controller )
{
    if ( Controller < (uint8)CAN_CV_IP0_CONTROLLERNUM_MAX )
    {
        /* CAN IP0 */
        Can_cv_ip0_stFuncTbl.EdgeDisableDetect( Controller );
#ifdef CAN_TEST_JGXSTACK
        Can_IP0_EdgeDisableDetect( Controller );
#endif /* CAN_TEST_JGXSTACK */
    }
    else
    {
        /* CAN IP1 */
        Can_cv_ip1_stFuncTbl.EdgeDisableDetect( Controller );
#ifdef CAN_TEST_JGXSTACK
        Can_IP1_EdgeDisableDetect( Controller );
#endif /* CAN_TEST_JGXSTACK */
    }
}


/****************************************************************************/
/* Function Name | Can_EdgeClearStatus                                      */
/* Description   | Edge Detection History Clear                             */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 Controller                                         */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
void
Can_EdgeClearStatus( uint8 Controller )
{
    if ( Controller < (uint8)CAN_CV_IP0_CONTROLLERNUM_MAX )
    {
        /* CAN IP0 */
        Can_cv_ip0_stFuncTbl.EdgeClearStatus( Controller );
#ifdef CAN_TEST_JGXSTACK
        Can_IP0_EdgeClearStatus( Controller );
#endif /* CAN_TEST_JGXSTACK */
    }
    else
    {
        /* CAN IP1 */
        Can_cv_ip1_stFuncTbl.EdgeClearStatus( Controller );
#ifdef CAN_TEST_JGXSTACK
        Can_IP1_EdgeClearStatus( Controller );
#endif /* CAN_TEST_JGXSTACK */
    }
}


/****************************************************************************/
/* Function Name | Can_EdgeGetStatus                                        */
/* Description   | Edge Detection History Get                               */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 Controller                                         */
/* Return Value  | Can_ReturnType                                           */
/*               |   CAN_OK                                                 */
/*               |   CAN_NOT_OK                                             */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
Can_ReturnType
Can_EdgeGetStatus( uint8 Controller )
{
    uint8                       u1Ret;

    if ( Controller < (uint8)CAN_CV_IP0_CONTROLLERNUM_MAX )
    {
        /* CAN IP0 */
        u1Ret = Can_cv_ip0_stFuncTbl.EdgeGetStatus( Controller );
#ifdef CAN_TEST_JGXSTACK
        u1Ret = Can_IP0_EdgeGetStatus( Controller );
#endif /* CAN_TEST_JGXSTACK */
    }
    else
    {
        /* CAN IP1 */
        u1Ret = Can_cv_ip1_stFuncTbl.EdgeGetStatus( Controller );
#ifdef CAN_TEST_JGXSTACK
        u1Ret = Can_IP1_EdgeGetStatus( Controller );
#endif /* CAN_TEST_JGXSTACK */
    }

    return (u1Ret);
}


/****************************************************************************/
/* Function Name | Can_Write_Dummy                                          */
/* Description   | Transmission Request Dummy                               */
/* Preconditions | See Design Documents                                     */
/* Parameters    | Can_HwHandleType Hth                                     */
/*               | CanConstR Can_PduType* PduInfo                           */
/*               |   PduIdType  swPduHandle                                 */
/*               |   uint8      length                                      */
/*               |   Can_IdType id                                          */
/*               |   uint8*     sdu                                         */
/* Return Value  | Can_ReturnType                                           */
/*               |   CAN_NOT_OK                                             */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
Can_ReturnType
Can_Write_Dummy( Can_HwHandleType Hth, CanConstR Can_PduType* PduInfo )
{
    /* No process due to dummy function */
    return ((uint8)CAN_NOT_OK);
}


/****************************************************************************/
/* Function Name | Can_MainFunction_Write_Dummy                             */
/* Description   | Transmission Periodic Process Dummy                      */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
void
Can_MainFunction_Write_Dummy( void )
{
    /* No process due to dummy function */
    ;
}


/****************************************************************************/
/* Function Name | Can_AbortSend_Dummy                                      */
/* Description   | Transmission Abort Request Dummy                         */
/* Preconditions | See Design Documents                                     */
/* Parameters    | Can_HwHandleType Hth                                     */
/* Return Value  | Can_ReturnType                                           */
/*               |   CAN_NOT_OK                                             */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
Can_ReturnType
Can_AbortSend_Dummy( Can_HwHandleType Hth )
{
    /* No process due to dummy function */
    return ((uint8)CAN_NOT_OK);
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


#endif /* (CAN_CFG_CV == CAN_USE) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2017/02/22                                              */
/*  v2-0-1         :2017/04/24                                              */
/*  v2-1-0         :2017/08/31                                              */
/*  v2-2-0         :2021/12/21                                              */
/*  v2-2-1         :2022/03/16                                              */
/*  v2-2-2         :2023/05/10                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
