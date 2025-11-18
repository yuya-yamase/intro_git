/* can_rscf4c_eg_log_c_v3-0-0                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN/RSCF4C/EG/LOGICAL/CODE                                */
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
#include <can/rscf4c/can_rscf4c_eg.h>


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
#if (CAN_CFG_SLEEP == CAN_USE)
    Can_UEdgeInit( Controller );
#endif /* (CAN_CFG_SLEEP == CAN_USE) */
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
#if (CAN_CFG_SLEEP == CAN_USE)
    Can_UEdgeEnableDetect( Controller );
#endif /* (CAN_CFG_SLEEP == CAN_USE) */
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
#if (CAN_CFG_SLEEP == CAN_USE)
    Can_UEdgeDisableDetect( Controller );
#endif /* (CAN_CFG_SLEEP == CAN_USE) */
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
#if (CAN_CFG_SLEEP == CAN_USE)
    Can_UEdgeClearStatus( Controller );
#endif /* (CAN_CFG_SLEEP == CAN_USE) */
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
#if (CAN_CFG_SLEEP == CAN_USE)
    uint8  u1Ret;

    u1Ret = Can_UEdgeGetStatus( Controller );
    return (u1Ret);
#else /* (CAN_CFG_SLEEP != CAN_USE) */
    return ((uint8)CAN_NOT_OK);
#endif /* (CAN_CFG_SLEEP) */
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


#endif /* (CAN_CFG_CAN == CAN_USE) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-2-0         :2021/12/14                                              */
/*  v3-0-0         :2025/02/13                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
