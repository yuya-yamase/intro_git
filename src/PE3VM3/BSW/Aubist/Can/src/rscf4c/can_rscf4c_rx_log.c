/* can_rscf4c_rx_log_c_v2-2-0                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN/RSCF4C/RX/LOGICAL/CODE                                */
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
#include <can/rscf4c/can_rscf4c_st.h>
#include <can/rscf4c/can_rscf4c_rx.h>


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
#if (CAN_CFG_RECEIVE == CAN_USE)
    uint16  u2ControllerStatus;
    uint8   u1Controller;
    uint8   u1ControllerNumMax;

    u1ControllerNumMax = Can_tb_u1ControllerNumMax;
    for ( u1Controller = (uint8)0U; u1Controller < u1ControllerNumMax; u1Controller++ )
    {
        u2ControllerStatus = Can_st_u2ControllerStatus[ u1Controller ];
        if ( u2ControllerStatus == (uint16)CAN_ST_CTRL_STARTED )
        {
            /* Reception completion confirmation process */
            (void)Can_rx_ChkRxFinMbox( u1Controller, (uint8)CAN_POLLING ); /* MISRA DEVIATION: no return check required */
        }
    }
#endif /* (CAN_CFG_RECEIVE == CAN_USE) */
}


/****************************************************************************/
/* Function Name | Can_rx_RxIndMbox                                         */
/* Description   | MBOX Reception Completion Notification                   */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/*               | uint8 u1Mbox                                             */
/*               | CanConstR CanMsgType* ptMsg                              */
/*               |   uint8* ptData                                          */
/*               |   uint32 u4Id                                            */
/*               |   uint8  u1Length                                        */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if (CAN_CFG_RECEIVE == CAN_USE)
void
Can_rx_RxIndMbox( uint8 u1Controller, uint8 u1Mbox, CanConstR CanMsgType* ptMsg )
{
    CanConst CanTbHohMbAllocType *  ptHohMbAlloc;
    uint8 *                         ptCanSdu;
    uint32                          u4IdVal;
    uint16                          u2Hoh;
    uint16                          u2HrhOfs;
    uint8                           u1HrhMbOfs;
    uint8                           u1DataLength;
#if (CAN_CFG_USER_RX_HOOK == CAN_USE)
    uint8                           u1URxIndResult;
#endif /* (CAN_CFG_USER_RX_HOOK == CAN_USE) */

    ptHohMbAlloc = &( Can_tb_stHohMbAlloc[ u1Controller ] );
    u2HrhOfs     = ptHohMbAlloc->u2HrhOffset;
    u1HrhMbOfs   = ptHohMbAlloc->u1HrhMbOffset;

    u2Hoh = ( ( (uint16)u1Mbox - (uint16)u1HrhMbOfs ) + u2HrhOfs );

#if (CAN_CFG_USER_RX_HOOK == CAN_USE)
    /* Notification of reception completion for user */
    u1URxIndResult = Can_URxIndication( u1Controller, u1Mbox, ptMsg );
    if ( u1URxIndResult == (uint8)CAN_PROC_OK )
#endif /* (CAN_CFG_USER_RX_HOOK == CAN_USE) */
    {
        /* Notification of reception completion for CANIF */
        ptCanSdu     = ptMsg->ptData;
        u4IdVal      = ptMsg->u4Id;
        u1DataLength = ptMsg->u1Length;
        CanIf_RxIndication( u2Hoh, u4IdVal, u1DataLength, ptCanSdu );
    }
}
#endif /* (CAN_CFG_RECEIVE == CAN_USE) */


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


#endif /* (CAN_CFG_CAN == CAN_USE) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-2-0         :2021/12/14                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
