/* Mscd_Suspend_Internal.c v1-0-0                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | MSCD/SUSPEND/INTERNAL/CODE                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Mscd.h>
#include <Mscd_Common.h>

#include "../inc/Mscd_Suspend_Internal.h"
#include "../usr/Mscd_Suspend_UserHook.h"

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
#define MSCD_START_SEC_VAR_NO_INIT_32
#include <Mscd_MemMap.h>

#if( MSCD_SUSPEND_USE == STD_ON )

/*   MSCD_SUSPEND_MS_RUN      */
/*   MSCD_SUSPEND_MS_SUSPEND  */
VAR(uint8, MSCD_VAR_NO_INIT) Mscd_Suspend_u1SuspendMsOpeState;

#endif /*( MSCD_SUSPEND_USE == STD_ON )*/

#define MSCD_STOP_SEC_VAR_NO_INIT_32
#include <Mscd_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define MSCD_START_SEC_CODE
#include <Mscd_MemMap.h>

/****************************************************************************/
/* Function Name | Mscd_Suspend_UpdateUserOpeState                          */
/* Description   | Update MS operating status                               */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | uint8                                                    */
/*               |      MSCD_SUSPEND_MS_RUN     : run                       */
/*               |      MSCD_SUSPEND_MS_SUSPEND : Stop                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint8, MSCD_CODE)
Mscd_Suspend_UpdateUserOpeState( void )
{
#if( MSCD_SUSPEND_USE == STD_ON )

    /* The first argument of Mscd _ Suspend _ GetOpenStateHook is for future expansion, currently fixed at 0 */
    Std_ReturnType u1State = Mscd_Suspend_GetOpeStateHook( 0U );

    /* Update MS operating status to match user-specified operating permission status */
    if( u1State == (Std_ReturnType)E_OK ) /* Put MS in working state if user specifies operating permission */
    {
        /* Forced stop/restart procedure when resuming from a stopped state */
        if( Mscd_Suspend_u1SuspendMsOpeState != MSCD_SUSPEND_MS_RUN )
        {
            NvM_ExtEnable();
        }
        Mscd_Suspend_u1SuspendMsOpeState = MSCD_SUSPEND_MS_RUN;
    }
    else /* Put MS in a suspended state if user specifies no action */
    {
        Mscd_Suspend_u1SuspendMsOpeState = MSCD_SUSPEND_MS_SUSPEND;
    }

    return( Mscd_Suspend_u1SuspendMsOpeState );
#else /* MSCD_SUSPEND_USE == STD_ON */
    return( MSCD_SUSPEND_MS_RUN );
#endif /* MSCD_SUSPEND_USE == STD_ON */
}

#define MSCD_STOP_SEC_CODE
#include <Mscd_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
