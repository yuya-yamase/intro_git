/* Mscd_Suspend_Internal.c v1-0-0                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
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
/* Function Name | Mscd_Suspend_UpdateUserOpeState                         */
/* Description   | MSの動作状態を更新する                                   */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | uint8                                                    */
/*               |           MSCD_SUSPEND_MS_RUN     : 動作                 */
/*               |           MSCD_SUSPEND_MS_SUSPEND : 停止                 */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint8, MSCD_CODE)
Mscd_Suspend_UpdateUserOpeState( void )
{
#if( MSCD_SUSPEND_USE == STD_ON )

    /* Mscd_Suspend_GetOpeStateHookの第1引数は将来拡張用であり、現在は0固定 */
    Std_ReturnType u1State = Mscd_Suspend_GetOpeStateHook( 0U );

    /* ユーザが指定した動作許可状態に合わせてMSの動作状態更新 */
    if( u1State == (Std_ReturnType)E_OK ) /* ユーザが動作許可を指定した場合、MSを動作状態にする */
    {
        /* 停止状態から再開する場合は強制停止・再開処置 */
        if( Mscd_Suspend_u1SuspendMsOpeState != MSCD_SUSPEND_MS_RUN )
        {
            NvM_ExtEnable();
        }
        Mscd_Suspend_u1SuspendMsOpeState = MSCD_SUSPEND_MS_RUN;
    }
    else /* ユーザが動作禁止を指定した場合、MSを停止状態にする */
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
