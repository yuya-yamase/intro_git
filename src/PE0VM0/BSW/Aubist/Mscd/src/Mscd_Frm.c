/* Mscd_Frm.c v2-0-0                                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | MSCD/FRM/CODE                                             */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Mscd.h>
#include <Mscd_Sec.h>
#include <Mscd_Common.h>
#include <Mscd_Cbk.h>

#include <Fee_Ext.h>

#include "../inc/Mscd_Frm.h"
#include "../inc/Mscd_Frm_Internal.h"
#include "../usr/Mscd_SecHook.h"

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

#if( MSCD_FRM_USE == STD_ON )

static VAR(uint8, MSCD_VAR_NO_INIT) Mscd_Frm_NvMExclusiveLock;
static VAR(uint8, MSCD_VAR_NO_INIT) Mscd_Frm_FeeExclusiveLock;
static VAR(uint8, MSCD_VAR_NO_INIT) Mscd_Frm_Event;
static VAR(uint8, MSCD_VAR_NO_INIT) Mscd_Frm_SuspendStatus;
static VAR(uint8, MSCD_VAR_NO_INIT) Mscd_Frm_SuspendStatusMirror;
static VAR(uint8, MSCD_VAR_NO_INIT) Mscd_Frm_ResultHookStatus;
static VAR(uint8, MSCD_VAR_NO_INIT) Mscd_Frm_ResultHookEvent;
static VAR(uint8, MSCD_VAR_NO_INIT) Mscd_Frm_ResultHookResult;

#endif

#define MSCD_STOP_SEC_VAR_NO_INIT_32
#include <Mscd_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define MSCD_START_SEC_CODE
#include <Mscd_MemMap.h>

/****************************************************************************/
/* Function Name | Mscd_Frm_SuspendFlashAccess                              */
/* Description   | Service to suspend flash access.                         */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MSCD_CODE ) Mscd_Frm_SuspendFlashAccess( void )
{
#if( MSCD_FRM_USE == STD_ON )
    if ((Mscd_Frm_NvMExclusiveLock == (uint8)MSCD_FRM_EXCLUSIVE_LOCK)
    ||  (Mscd_Frm_FeeExclusiveLock == (uint8)MSCD_FRM_EXCLUSIVE_LOCK))
    {
        Mscd_Frm_Event = MSCD_FRM_REQUEST_EVT_SUSPEND;
        Mscd_Frm_SuspendFlashAccessHook(MSCD_FRM_SUSPEND_WAIT);
    }
    else
    {
        Mscd_Frm_ActSuspendFlashAccess();
    }
#endif
    return;
}

/****************************************************************************/
/* Function Name | Mscd_Frm_ResumeFlashAccess                               */
/* Description   | Service to resume flash access.                          */
/* Preconditions | None                                                     */
/* Parameters    | u1Result                                                 */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MSCD_CODE ) Mscd_Frm_ResumeFlashAccess( uint8 u1Result )
{
#if( MSCD_FRM_USE == STD_ON )
    Mscd_Frm_ActResumeFlashAccess();
#endif
    return;
}

/****************************************************************************/
/* Function Name | Mscd_Frm_CancelSuspendFlashAccess                        */
/* Description   | Service to cancel to suspend.                            */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MSCD_CODE ) Mscd_Frm_CancelSuspendFlashAccess( void )
{
#if( MSCD_FRM_USE == STD_ON )
    Mscd_Frm_ActCancelSuspendFlashAccess();
#endif
    return;
}

/****************************************************************************/
/* Function Name | Mscd_Frm_Init                                            */
/* Description   | Service to init Frm unit.                                */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MSCD_CODE ) Mscd_Frm_Init( void )
{
#if( MSCD_FRM_USE == STD_ON )
    Mscd_Frm_NvMExclusiveLock       = MSCD_FRM_EXCLUSIVE_UNLOCK;
    Mscd_Frm_FeeExclusiveLock       = MSCD_FRM_EXCLUSIVE_UNLOCK;
    Mscd_Frm_Event               = MSCD_FRM_REQUEST_EVT_NONE;
    Mscd_Frm_ResultHookStatus    = MSCD_FRM_RESULTHOOK_ENABLED;
    Mscd_Frm_ResultHookEvent     = MSCD_FRM_REQUEST_EVT_NONE;
    Mscd_Frm_ResultHookResult    = MSCD_FRM_RESULT_NONE;
    Mscd_Frm_UpdateSuspendStatus(MSCD_FRM_NO_REQUEST);
#endif
    return;
}

/****************************************************************************/
/* Function Name | Mscd_Frm_NvMExclusiveLockBegin                           */
/* Description   | Service to notify NvM exclusive lock section begin.      */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MSCD_CODE ) Mscd_Frm_NvMExclusiveLockBegin( void )
{
#if( MSCD_FRM_USE == STD_ON )
    Mscd_Frm_PreExclusiveLock();
    Mscd_Frm_NvMExclusiveLock = MSCD_FRM_EXCLUSIVE_LOCK;
#endif
    return;
}

/****************************************************************************/
/* Function Name | Mscd_Frm_NvMExclusiveLockEnd                             */
/* Description   | Service to notify NvM exclusive lock section end.        */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MSCD_CODE ) Mscd_Frm_NvMExclusiveLockEnd( void )
{
#if( MSCD_FRM_USE == STD_ON )
    Mscd_Frm_NvMExclusiveLock = MSCD_FRM_EXCLUSIVE_UNLOCK;
    Mscd_Frm_PostExclusiveUnLock();
#endif
    return;
}

/****************************************************************************/
/* Function Name | Mscd_Frm_GetSuspendStatus                                */
/* Description   | Service to get suspend status.                           */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8 , MSCD_CODE ) Mscd_Frm_GetSuspendStatus( void )
{
#if( MSCD_FRM_USE == STD_ON )
    Std_ReturnType u1Defect;
    
    u1Defect = Mscd_Frm_CheckSuspendStatus();
    
    if (u1Defect != (Std_ReturnType)E_OK)
    {
        /* RAM Refresh */
        Mscd_Frm_UpdateSuspendStatus(MSCD_FRM_NO_REQUEST);
    }
    return ( Mscd_Frm_SuspendStatus );
#else
    return ( MSCD_FRM_NO_REQUEST );
#endif
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#if( MSCD_FRM_USE == STD_ON )
/****************************************************************************/
/* Function Name | Mscd_Frm_ActSuspendFlashAccess                           */
/* Description   | Service to suspend flash access.                         */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MSCD_CODE ) Mscd_Frm_ActSuspendFlashAccess( void )
{
    Fee_ExtJobResultType u1SuspendResult;
    
    if (Mscd_Frm_SuspendStatus == (uint8)MSCD_FRM_NO_REQUEST)
    {
        /* An interrupt can be generated within Suspend. */
        /* Disable Interrupts because there is no assumption that an interrupt will occur. */
        Mscd_Frm_PreSuspendFlashAccess();
        u1SuspendResult = Fee_ExtSuspend();
        switch ( u1SuspendResult )
        {
            case MSCD_FRM_RSP_OK :
                Mscd_Frm_UpdateSuspendStatus(MSCD_FRM_SUSPENDING);
                Mscd_Frm_SuspendFlashAccessHook(MSCD_FRM_SUSPEND_WAIT);
                break;
                
            case MSCD_FRM_RSP_OK_SUSPENDED :
                Mscd_Frm_UpdateSuspendStatus(MSCD_FRM_SUSPENDED);
                Mscd_Frm_SuspendFlashAccessHook(MSCD_FRM_SUSPEND_OK);
                break;
                
            case MSCD_FRM_RSP_NG_USED_HSM :
            case MSCD_FRM_RSP_NG_SUSPEND :
            case MSCD_FRM_RSP_NG_INTERNAL :
            default :
                Mscd_Frm_UpdateSuspendStatus(MSCD_FRM_NO_REQUEST);
                Mscd_Frm_SuspendFlashAccessHook(MSCD_FRM_SUSPEND_HARD_ERROR);
                break;
        }
        Mscd_Frm_PostSuspendFlashAccess();
    }
    else
    {
        Mscd_Frm_SuspendFlashAccessHook(MSCD_FRM_SUSPEND_DENIED);
    }
    
    return;
}
#endif

#if( MSCD_FRM_USE == STD_ON )
/****************************************************************************/
/* Function Name | Mscd_Frm_SubSuspendResultHook                            */
/* Description   | Service to nortify suspending flash access OK.           */
/* Preconditions | None                                                     */
/* Parameters    | u1Result                                                 */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MSCD_CODE ) Mscd_Frm_SubSuspendResultHook( uint8 u1Result )
{
    switch ( u1Result )
    {
        case MSCD_FRM_RESULT_OK :
            Mscd_Frm_ActSuspendResultHook();
            break;
            
        case MSCD_FRM_RESULT_NG_REQ_CANCELED :
            /* do nothing */
            break;
            
        case MSCD_FRM_RESULT_NG_USED_HSM :
        case MSCD_FRM_RESULT_NG_HW_BUSY :
        case MSCD_FRM_RESULT_NG_SUSPEND :
        case MSCD_FRM_RESULT_NG_INTERNAL :
        default :
            Mscd_Frm_ActErrorSuspendResultHook();
            break;
    }
    return;
}
#endif

#if( MSCD_FRM_USE == STD_ON )
/****************************************************************************/
/* Function Name | Mscd_Frm_ActSuspendResultHook                            */
/* Description   | Service to nortify suspending flash access OK.           */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MSCD_CODE ) Mscd_Frm_ActSuspendResultHook( void )
{
    if (Mscd_Frm_SuspendStatus == (uint8)MSCD_FRM_SUSPENDING)
    {
        Mscd_Frm_UpdateSuspendStatus(MSCD_FRM_SUSPENDED);
        Mscd_Frm_SuspendFlashAccessHook(MSCD_FRM_SUSPEND_OK);
    }
    return;
}
#endif

#if( MSCD_FRM_USE == STD_ON )
/****************************************************************************/
/* Function Name | Mscd_Frm_ActErrorSuspendResultHook                       */
/* Description   | Service to nortify suspending flash access Error.        */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MSCD_CODE ) Mscd_Frm_ActErrorSuspendResultHook( void )
{
    if (Mscd_Frm_SuspendStatus == (uint8)MSCD_FRM_SUSPENDING)
    {
        Mscd_Frm_UpdateSuspendStatus(MSCD_FRM_NO_REQUEST);
        Mscd_Frm_SuspendFlashAccessHook(MSCD_FRM_SUSPEND_HARD_ERROR);
    }
    return;
}
#endif

#if( MSCD_FRM_USE == STD_ON )
/****************************************************************************/
/* Function Name | Mscd_Frm_ActResumeFlashAccess                            */
/* Description   | Service to resume flash access.                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MSCD_CODE ) Mscd_Frm_ActResumeFlashAccess( void )
{

    if (Mscd_Frm_SuspendStatus == (uint8)MSCD_FRM_SUSPENDED)
    {
        /* Normal case */
        (void)Fee_ExtResume();  /* Ignore return value */
        Mscd_Frm_UpdateSuspendStatus(MSCD_FRM_NO_REQUEST);
    }
    else
    {
        /* Fail case */
        Mscd_Frm_UpdateSuspendStatus(MSCD_FRM_NO_REQUEST);
    }
    return;
}
#endif

#if( MSCD_FRM_USE == STD_ON )
/****************************************************************************/
/* Function Name | Mscd_Frm_ActCancelSuspendFlashAccess                     */
/* Description   | Service to cancel to suspend flash access.               */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MSCD_CODE ) Mscd_Frm_ActCancelSuspendFlashAccess( void )
{
    if (Mscd_Frm_SuspendStatus == (uint8)MSCD_FRM_SUSPENDING)
    {
        /* Normal case */
        Fee_ExtCancelSuspend();
        Mscd_Frm_UpdateSuspendStatus(MSCD_FRM_NO_REQUEST);
    }
    else if (Mscd_Frm_SuspendStatus == (uint8)MSCD_FRM_SUSPENDED)
    {
        /* Normal case */
        (void)Fee_ExtResume();  /* Ignore return value */
        Mscd_Frm_UpdateSuspendStatus(MSCD_FRM_NO_REQUEST);
    }
    else
    {
        /* Fail case */
        Mscd_Frm_UpdateSuspendStatus(MSCD_FRM_NO_REQUEST);
    }
    return;
}
#endif

#if( MSCD_FRM_USE == STD_ON )
/****************************************************************************/
/* Function Name | Mscd_Frm_PreExclusiveLock                                */
/* Description   | Service to execute pre exclusive lock action.            */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MSCD_CODE ) Mscd_Frm_PreExclusiveLock( void )
{
    if  ((Mscd_Frm_NvMExclusiveLock == (uint8)MSCD_FRM_EXCLUSIVE_UNLOCK)
    &&   (Mscd_Frm_FeeExclusiveLock == (uint8)MSCD_FRM_EXCLUSIVE_UNLOCK))
    {
        Mscd_Frm_Event         = MSCD_FRM_REQUEST_EVT_NONE;
    }
}
#endif

#if( MSCD_FRM_USE == STD_ON )
/****************************************************************************/
/* Function Name | Mscd_Frm_PostExclusiveUnLock                             */
/* Description   | Service to execute post exclusive unlock action.         */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MSCD_CODE ) Mscd_Frm_PostExclusiveUnLock( void )
{
    if  ((Mscd_Frm_NvMExclusiveLock == (uint8)MSCD_FRM_EXCLUSIVE_UNLOCK)
    &&   (Mscd_Frm_FeeExclusiveLock == (uint8)MSCD_FRM_EXCLUSIVE_UNLOCK))
    {
        if (Mscd_Frm_Event == (uint8)MSCD_FRM_REQUEST_EVT_SUSPEND)
        {
            Mscd_Frm_ActSuspendFlashAccess();
        }
        Mscd_Frm_Event = MSCD_FRM_REQUEST_EVT_NONE;
    }
}
#endif

#if( MSCD_FRM_USE == STD_ON )
/****************************************************************************/
/* Function Name | Mscd_Frm_PreSuspendFlashAccess                           */
/* Description   | Service to execute pre suspend flash access action.      */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MSCD_CODE ) Mscd_Frm_PreSuspendFlashAccess( void )
{
    Mscd_Frm_ResultHookEvent  = MSCD_FRM_REQUEST_EVT_NONE;
    Mscd_Frm_ResultHookResult = MSCD_FRM_RESULT_NONE;
    Mscd_Frm_ResultHookStatus = MSCD_FRM_RESULTHOOK_DISABLED;
    return;
}
#endif

#if( MSCD_FRM_USE == STD_ON )
/****************************************************************************/
/* Function Name | Mscd_Frm_PostSuspendFlashAccess                          */
/* Description   | Service to execute Post suspend flash access action.     */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MSCD_CODE ) Mscd_Frm_PostSuspendFlashAccess( void )
{
    Mscd_Frm_ResultHookStatus = MSCD_FRM_RESULTHOOK_ENABLED;
    if (Mscd_Frm_ResultHookEvent == (uint8)MSCD_FRM_RESPONSE_EVT_SUSPEND)
    {
        Mscd_Frm_SubSuspendResultHook(Mscd_Frm_ResultHookResult);
    }
    Mscd_Frm_ResultHookEvent  = MSCD_FRM_REQUEST_EVT_NONE;
    Mscd_Frm_ResultHookResult = MSCD_FRM_RESULT_NONE;
    return;
}
#endif

#if( MSCD_FRM_USE == STD_ON )
/****************************************************************************/
/* Function Name | Mscd_Frm_UpdateSuspendStatus                             */
/* Description   | Service to update suspend status.                        */
/* Preconditions | None                                                     */
/* Parameters    | u1SuspendStatus                                          */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MSCD_CODE ) Mscd_Frm_UpdateSuspendStatus( uint8 u1SuspendStatus )
{
    Mscd_Frm_SuspendStatus       = u1SuspendStatus;
    Mscd_Frm_SuspendStatusMirror = u1SuspendStatus;
    return;
}
#endif

#if( MSCD_FRM_USE == STD_ON )
/****************************************************************************/
/* Function Name | Mscd_Frm_CheckSuspendStatus                              */
/* Description   | Service to check suspend status defect.                  */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | E_OK                                                     */
/*               | E_NOT_OK                                                 */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, MSCD_CODE ) Mscd_Frm_CheckSuspendStatus( void )
{
    Std_ReturnType u1Ret;
    uint8 u1StatusValue;
    uint8 u1StatusValueMirror;
    uint8 u1StatusValueReload;
    
    /* Prevent the code from optimization */
    P2VAR( volatile uint8, AUTOMATIC, MSCD_VAR_NO_INIT ) ptu1Status;
    P2VAR( volatile uint8, AUTOMATIC, MSCD_VAR_NO_INIT ) ptu1StatusMirror;
    ptu1Status       = &Mscd_Frm_SuspendStatus;
    ptu1StatusMirror = &Mscd_Frm_SuspendStatusMirror;
    
    /* Load RAM data in sequence */
    u1StatusValue       = *ptu1Status;
    u1StatusValueMirror = *ptu1StatusMirror;
    u1StatusValueReload = *ptu1Status;

    /* Check RAM gerbage or task interrupt */
    if ( u1StatusValue == u1StatusValueMirror )
    {
        u1Ret = E_OK;
    }
    else
    {
        /* Distingish RAM garbage from task interrupt */
        if ( u1StatusValue == u1StatusValueReload )
        {
            /* RAM garbage */
            u1Ret = E_NOT_OK;
        }
        else
        {
            /* task interrupt */
            u1Ret = E_OK;
        }
    }
    return ( u1Ret );
}
#endif

#define MSCD_STOP_SEC_CODE
#include <Mscd_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  2-0-0          :2022/07/15                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
