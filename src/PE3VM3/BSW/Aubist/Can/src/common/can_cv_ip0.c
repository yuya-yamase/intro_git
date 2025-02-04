/* can_cv_ip0_c_v2-2-1                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN/CV/IP0/CODE                                           */
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
#define CAN_CV_HRHNUM \
   (  CAN_CFG_HRHNUM_0 \
    + CAN_CFG_HRHNUM_1 \
    + CAN_CFG_HRHNUM_2 \
    + CAN_CFG_HRHNUM_3 \
    + CAN_CFG_HRHNUM_4 \
    + CAN_CFG_HRHNUM_5 \
    + CAN_CFG_HRHNUM_6 \
    + CAN_CFG_HRHNUM_7 )

#define CAN_CV_HTHNUM \
   (  CAN_CFG_HTHNUM_0 \
    + CAN_CFG_HTHNUM_1 \
    + CAN_CFG_HTHNUM_2 \
    + CAN_CFG_HTHNUM_3 \
    + CAN_CFG_HTHNUM_4 \
    + CAN_CFG_HTHNUM_5 \
    + CAN_CFG_HTHNUM_6 \
    + CAN_CFG_HTHNUM_7 )

#define CAN_CV_HOHNUM                   ( CAN_CV_HRHNUM + CAN_CV_HTHNUM )


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
CanConst uint16 Can_cv_ip0_u2HrhNum = (uint16)CAN_CV_HRHNUM;
CanConst uint16 Can_cv_ip0_u2HohNum = (uint16)CAN_CV_HOHNUM;

CanConst CanCvFuncTbType Can_cv_ip0_stFuncTbl = 
{
    &Can_IP0_Init
   ,&Can_IP0_InitController
   ,&Can_IP0_SetControllerMode
   ,&Can_IP0_MainFunction_Mode
   ,&Can_IP0_Shutdown
   ,&Can_IP0_ResetController
   ,&Can_IP0_CheckStopCompletion
   ,&Can_IP0_GetControllerStatus
#if(CAN_CFG_TRANSMIT == CAN_USE)
   ,&Can_IP0_Write
   ,&Can_IP0_MainFunction_Write
   ,&Can_IP0_AbortSend
#else /* (CAN_CFG_TRANSMIT != CAN_USE) */
   ,&Can_Write_Dummy
   ,&Can_MainFunction_Write_Dummy
   ,&Can_AbortSend_Dummy
#endif /* (CAN_CFG_TRANSMIT) */
   ,&Can_IP0_MainFunction_Read
   ,&Can_IP0_MainFunction_BusOff
   ,&Can_IP0_CheckStuckRegister
   ,&Can_IP0_RefreshRegister
   ,&Can_IP0_MainFunction_Fail
   ,&Can_IP0_GetErrorStatus
   ,&Can_IP0_EdgeInit
   ,&Can_IP0_EdgeEnableDetect
   ,&Can_IP0_EdgeDisableDetect
   ,&Can_IP0_EdgeClearStatus
   ,&Can_IP0_EdgeGetStatus
};


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Can_cv_IP0_CntrlMdInd                                    */
/* Description   | Controller State Transition Completion Notification      */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8                    Controller                      */
/*               | CanIf_ControllerModeType ControllerMode                  */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
void
Can_cv_IP0_CntrlMdInd( uint8 Controller, CanIf_ControllerModeType ControllerMode )
{
    CanIf_ControllerModeIndication( Controller, ControllerMode );
}


/****************************************************************************/
/* Function Name | Can_cv_IP0_TxConfirmation                                */
/* Description   | Transmission Completion Notification                     */
/* Preconditions | See Design Documents                                     */
/* Parameters    | PduIdType  CanTxPduId                                    */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if (CAN_CFG_TRANSMIT == CAN_USE)
void
Can_cv_IP0_TxConfirmation( PduIdType CanTxPduId )
{
    CanIf_TxConfirmation( CanTxPduId );
}
#endif /* (CAN_CFG_TRANSMIT == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_cv_IP0_RxIndication                                  */
/* Description   | Reception Completion Notification                        */
/* Preconditions | See Design Documents                                     */
/* Parameters    | Can_HwHandleType Hrh                                     */
/*               | Can_IdType       CanId                                   */
/*               | uint8            CanDlc                                  */
/*               | CanConstR uint8  CanSduPtr[]                             */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if (CAN_CFG_RECEIVE == CAN_USE)
void
Can_cv_IP0_RxIndication( Can_HwHandleType Hrh, Can_IdType CanId, uint8 CanDlc, CanConstR uint8 CanSduPtr[] )
{
    CanIf_RxIndication( Hrh, CanId, CanDlc, CanSduPtr );
}
#endif /* (CAN_CFG_RECEIVE == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_cv_IP0_ControllerBusOff                              */
/* Description   | Bus Off Occurrence Notification                          */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8                    Controller                      */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
void
Can_cv_IP0_ControllerBusOff( uint8 Controller )
{
    CanIf_ControllerBusOff( Controller );
}


/****************************************************************************/
/* Function Name | Can_cv_IP0_ControllerFail                                */
/* Description   | MPU Fail Occurrence Notification                         */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8                    Controller                      */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
void
Can_cv_IP0_ControllerFail( uint8 Controller )
{
    CanIf_ControllerFail( Controller );
}


#endif /* (CAN_CFG_CV == CAN_USE) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2017/02/22                                              */
/*  v2-0-1         :2017/04/24                                              */
/*  v2-1-0         :2017/08/31                                              */
/*  v2-2-0         :2021/12/24                                              */
/*  v2-2-1         :2022/03/16                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
