/* can_cv_ip1_c_v3-0-0                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN/CV/IP1/CODE                                           */
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

#if (CAN_CFG_IP1 == CAN_IP_RSC)
#include "../../cfg/rsc/can_rsc_cfg_ext.h"
#include "../../cfg/rsc/can_rsc_cfg.h"

#elif (CAN_CFG_IP1 == CAN_IP_RSCF2)
#include "../../cfg/rscf2/can_rscf2_cfg_ext.h"
#include "../../cfg/rscf2/can_rscf2_cfg.h"

#elif (CAN_CFG_IP1 == CAN_IP_RSCF3)
#include "../../cfg/rscf3/can_rscf3_cfg_ext.h"
#include "../../cfg/rscf3/can_rscf3_cfg.h"

#elif (CAN_CFG_IP1 == CAN_IP_RSCF3C)
#include "../../cfg/rscf3c/can_rscf3c_cfg_ext.h"
#include "../../cfg/rscf3c/can_rscf3c_cfg.h"

#elif (CAN_CFG_IP1 == CAN_IP_RSCF4)
#include "../../cfg/rscf4/can_rscf4_cfg_ext.h"
#include "../../cfg/rscf4/can_rscf4_cfg.h"

#elif (CAN_CFG_IP1 == CAN_IP_RSCF4C)
#include "../../cfg/rscf4c/can_rscf4c_cfg_ext.h"
#include "../../cfg/rscf4c/can_rscf4c_cfg.h"

#elif (CAN_CFG_IP1 == CAN_IP_RSCF41)
#include "../../cfg/rscf41/can_rscf41_cfg_ext.h"
#include "../../cfg/rscf41/can_rscf41_cfg.h"

#else /* ((CAN_CFG_IP1 != CAN_IP_RSC) && (CAN_CFG_IP1 != CAN_IP_RSCF2) && (CAN_CFG_IP1 != CAN_IP_RSCF3) && (CAN_CFG_IP1 != CAN_IP_RSCF3C) && (CAN_CFG_IP1 != CAN_IP_RSCF4) && (CAN_CFG_IP1 != CAN_IP_RSCF4C) && (CAN_CFG_IP1 != CAN_IP_RSCF41)) */
#include "../../cfg/rscf41c/can_rscf41c_cfg_ext.h"
#include "../../cfg/rscf41c/can_rscf41c_cfg.h"
#endif /* (CAN_CFG_IP1) */

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
CanConst uint16 Can_cv_ip1_u2HrhNum = (uint16)CAN_CV_HRHNUM;

CanConst CanCvFuncTbType Can_cv_ip1_stFuncTbl = 
{
    &Can_IP1_Init
   ,&Can_IP1_InitController
   ,&Can_IP1_SetControllerMode
   ,&Can_IP1_MainFunction_Mode
   ,&Can_IP1_Shutdown
   ,&Can_IP1_ResetController
   ,&Can_IP1_CheckStopCompletion
   ,&Can_IP1_GetControllerStatus
#if(CAN_CFG_TRANSMIT == CAN_USE)
   ,&Can_IP1_Write
   ,&Can_IP1_MainFunction_Write
   ,&Can_IP1_AbortSend
#else /* (CAN_CFG_TRANSMIT != CAN_USE) */
   ,&Can_Write_Dummy
   ,&Can_MainFunction_Write_Dummy
   ,&Can_AbortSend_Dummy
#endif /* (CAN_CFG_TRANSMIT) */
   ,&Can_IP1_MainFunction_Read
   ,&Can_IP1_MainFunction_BusOff
   ,&Can_IP1_CheckStuckRegister
   ,&Can_IP1_RefreshRegister
   ,&Can_IP1_MainFunction_Fail
   ,&Can_IP1_GetErrorStatus
   ,&Can_IP1_EdgeInit
   ,&Can_IP1_EdgeEnableDetect
   ,&Can_IP1_EdgeDisableDetect
   ,&Can_IP1_EdgeClearStatus
   ,&Can_IP1_EdgeGetStatus
};


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Can_cv_IP1_CntrlMdInd                                    */
/* Description   | Controller State Transition Completion Notification      */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8                    Controller                      */
/*               | CanIf_ControllerModeType ControllerMode                  */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
void
Can_cv_IP1_CntrlMdInd( uint8 Controller, CanIf_ControllerModeType ControllerMode )
{
    uint8 u1PhysCh;

    u1PhysCh = Controller + (uint8)CAN_CV_IP0_CONTROLLERNUM_MAX;
    CanIf_ControllerModeIndication( u1PhysCh, ControllerMode );
}


/****************************************************************************/
/* Function Name | Can_cv_IP1_TxConfirmation                                */
/* Description   | Transmission Completion Notification                     */
/* Preconditions | See Design Documents                                     */
/* Parameters    | PduIdType  CanTxPduId                                    */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if (CAN_CFG_TRANSMIT == CAN_USE)
void
Can_cv_IP1_TxConfirmation( PduIdType CanTxPduId )
{
    CanIf_TxConfirmation( CanTxPduId );
}
#endif /* (CAN_CFG_TRANSMIT == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_cv_IP1_RxIndication                                  */
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
Can_cv_IP1_RxIndication( Can_HwHandleType Hrh, Can_IdType CanId, uint8 CanDlc, CanConstR uint8 CanSduPtr[] )
{
    uint16  u2Hrh;

    u2Hrh = Hrh + Can_cv_ip0_u2HrhNum;
    CanIf_RxIndication( u2Hrh, CanId, CanDlc, CanSduPtr );
}
#endif /* (CAN_CFG_RECEIVE == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_cv_IP1_ControllerBusOff                              */
/* Description   | Bus Off Occurrence Notification                          */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8                    Controller                      */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
void
Can_cv_IP1_ControllerBusOff( uint8 Controller )
{
    uint8 u1PhysCh;

    u1PhysCh = Controller + (uint8)CAN_CV_IP0_CONTROLLERNUM_MAX;
    CanIf_ControllerBusOff( u1PhysCh );
}


/****************************************************************************/
/* Function Name | Can_cv_IP1_ControllerFail                                */
/* Description   | MPU Fail Occurrence Notification                         */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8                    Controller                      */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
void
Can_cv_IP1_ControllerFail( uint8 Controller )
{
    uint8 u1PhysCh;

    u1PhysCh = Controller + (uint8)CAN_CV_IP0_CONTROLLERNUM_MAX;
    CanIf_ControllerFail( u1PhysCh );
}


#endif /* (CAN_CFG_CV == CAN_USE) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2017/02/22                                              */
/*  v2-0-1         :2017/04/24                                              */
/*  v2-1-0         :2017/08/31                                              */
/*  v2-2-0         :2021/12/15                                              */
/*  v2-2-1         :2022/03/16                                              */
/*  v3-0-0         :2025/02/13                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
