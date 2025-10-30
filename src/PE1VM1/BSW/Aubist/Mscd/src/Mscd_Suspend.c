/* Mscd_Suspend.c v2-0-0                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | MSCD/SUSPEND/CODE                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Mscd.h>
#include <NvM_Mscd.h>

#include <Mscd_Common.h>
#include <Mscd_Cbk.h>
#include <Mscd_Sec.h>
#include "../inc/Mscd_Suspend.h"
#include "../inc/Mscd_Frm.h"

#include "../inc/Mscd_Suspend_Internal.h"

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
#define MSCD_START_SEC_CODE
#include <Mscd_MemMap.h>

/******************************************************************************/
/* Function Name | Mscd_Suspend_Init (MS Action State Initialization)         */
/* Description   | Initialize MS operating state                              */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, MSCD_CODE)
Mscd_Suspend_Init( void )
{
#if( MSCD_SUSPEND_USE == STD_ON )
    Mscd_Suspend_u1SuspendMsOpeState = MSCD_SUSPEND_MS_RUN;
#endif /* MSCD_SUSPEND_USE == STD_ON */
    return;
}

/****************************************************************************/
/* Function Name | Mscd_Suspend_GetUserSuspendState                         */
/* Description   | Service to get user suspend state                        */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | uint8                                                    */
/*               |           MSCD_SUSPEND_MS_RUN                            */
/*               |           MSCD_SUSPEND_MS_SUSPEND                        */
/* Notes         |                                                          */
/****************************************************************************/
FUNC(uint8, MSCD_CODE)
Mscd_Suspend_GetUserSuspendState( void )
{
#if( MSCD_SUSPEND_USE == STD_ON )
    return ( Mscd_Suspend_u1SuspendMsOpeState );
#else
    return ( MSCD_SUSPEND_MS_RUN );
#endif /* MSCD_SUSPEND_USE == STD_ON */
}

/****************************************************************************/
/* Function Name | Mscd_Suspend_UpdateOpeState                              */
/* Description   | Service to update Ms Status.                             */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | uint8                                                    */
/*               |           MSCD_SUSPEND_MS_RUN                            */
/*               |           MSCD_SUSPEND_MS_SUSPEND                        */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint8, MSCD_CODE)
Mscd_Suspend_UpdateOpeState( void )
{
    uint8 u1Return;
    uint8 u1FrmStatus;
    
    u1FrmStatus = Mscd_Frm_GetSuspendStatus();
    u1Return = Mscd_Suspend_UpdateUserOpeState();
    if ( u1FrmStatus != (uint8)MSCD_FRM_NO_REQUEST )
    {
        u1Return = MSCD_SUSPEND_MS_SUSPEND;
    }

    return ( u1Return );
}

#if( MSCD_SUSPEND_USE == STD_ON )
/****************************************************************************/
/* Function Name | Mscd_Suspend_ReqUpdateOpeState (MS motion state update request) */
/* Description   | Update MS operating status during this I/F call          */
/* Preconditions |                                                          */
/* Parameters    | u1MemoryIdentifier: memory medium ID                     */
/*               |             * For future expansion. Currently fixed at 0 */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, MSCD_CODE)
Mscd_Suspend_ReqUpdateOpeState( uint8 u1MemoryIdentifier )
{
    (void)Mscd_Suspend_UpdateOpeState();   /* Ignore return value */

    return;
}
#endif /* MSCD_SUSPEND_USE == STD_ON */

#if( MSCD_SUSPEND_USE == STD_ON )
/****************************************************************************/
/* Function Name | Mscd_Suspend_ReqAbort (MS Driver Forced Stop)            */
/* Description   | Force the driver to stop processing                      */
/* Preconditions |                                                          */
/* Parameters    | u1MemoryIdentifier : memory medium ID                    */
/*               |             * For future expansion. Currently fixed at 0 */
/* Return Value  | Std_ReturnType                                           */
/*               |          E_OK        : Request accepted                  */
/*               |          E_NOT_OK    : Request not accepted              */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, MSCD_CODE)
Mscd_Suspend_ReqAbort( uint8 u1MemoryIdentifier )
{
    Std_ReturnType u1Result;

    u1Result = E_NOT_OK;

    /* Abort driver only when MS is stopped */
    if( Mscd_Suspend_u1SuspendMsOpeState != MSCD_SUSPEND_MS_RUN )
    {
        NvM_ExtDisable();
        u1Result = E_OK;
    }
    return( u1Result );
}
#endif /* MSCD_SUSPEND_USE == STD_ON */

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define MSCD_STOP_SEC_CODE
#include <Mscd_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  2-0-0          :2022/07/15                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
