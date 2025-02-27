/*
    Copyright (C) 2016 By eSOL Co.,Ltd. Tokyo, Japan

    This software is protected by the law and the agreement concerning
    a Japanese country copyright method, an international agreement,
    and other intellectual property right and may be used and copied
    only in accordance with the terms of such license and with the inclusion
    of the above copyright notice.

    This software or any other copies thereof may not be provided
    or otherwise made available to any other person.  No title to
    and ownership of the software is hereby transferred.

    The information in this software is subject to change without
    notice and should not be construed as a commitment by eSOL Co.,Ltd.
*/

/****************************************************************************
[sample_mcos_userhook.c] - MCOS user hook (sample)
****************************************************************************/

#include "mcos/mcos.h"
#include "mcos/mcos_ds.cfg"
#include "mcos/mcos_ds.h"

#include "Std_Types.h"
#include "SS.h"
#include "OS.h"
#include "Ecu_Int.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"

void mcos_ds_userhook_ar_target_exit(void)
{
    /* to be implemented by user */
    ;
}

void mcos_ds_userhook_enter_isr(mcos_id_t iid)
{
    /* to be implemented by user */
    (void)iid;
    ;
}

void mcos_ds_userhook_enter_exc(void)
{
    /* to be implemented by user */
    ;
}
void mcos_ds_userhook_enter_idle(void)
{
    /* to be implemented by user */
    ;
}
void mcos_ds_userhook_leave_idle(mcos_id_t tid)
{
    /* to be implemented by user */
    (void)tid;
    ;
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_CALLOUT_CODE
#include <Os_MemMap.h>

#if (AR_OS_USE_PROTECTIONHOOK == STD_ON)
/**---------------------------------------------------------------------------
 * [Format]		ProtectionReturnType ProtectionHook(StatusType FatalError)
 * [Function]	The protection hook is always called if a serious error
 *				occurs. E.g. exceeding the worst case execution time or
 *				violating against the memory protection.
 * [Arguments]	FatalError: The error which caused the call to
 *				the protection hook
 *				adr: "0" is stored if parameter FatalError is E_OS_STACKFAULT
 *				or the value of "the status save register when acknowledging
 *				FE-level-interrupt (FEPC)" when a protection violation was 
 *				detected if FatalError is E_OS_PROTECTION_MEMORY.
 * [Return]		ProtectionReturnType:The return value defines the action
 *				the OS shall take after the protection hook.
 * [Notes]		None
 *--------------------------------------------------------------------------*/
ProtectionReturnType ProtectionHook(StatusType FatalError)
{
    Ecu_Int_performReset();

    return (PRO_IGNORE);
}
#endif /* AR_OS_USE_PROTECTIONHOOK */

#if (AR_OS_USE_ERRORHOOK == STD_ON)
/**---------------------------------------------------------------------------
 * [Format]		void ErrorHook(StatusType Error)
 * [Function]	This hook routine is called by the operating system
 *				at the end of a system service which returns StatusType
 *				not equal E_OK.
 *				It is called before returning to the task level.
 *				This hook routine is called when an alarm expires and
 *				an error is detected during task activation or event setting.
 * [Arguments]	Error: error occurred
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
void ErrorHook(StatusType Error)
{
    if (Error != (StatusType)E_OS_LIMIT)
    {
        
        Ecu_Int_performReset();
    }
    

    return;
}
#endif /* (AR_OS_USE_ERRORHOOK == STD_ON) */

#if (AR_OS_USE_SHUTDOWNHOOK == STD_ON)
/**---------------------------------------------------------------------------
 * [Format]		void ShutdownHook(StatusType Error)
 * [Function]	This hook routine is called by the operating system when
 *				the OS service ShutdownOS has been called.
 *				This routine is called during the operating system shut down.
 * [Arguments]	Error: error occurred
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
void ShutdownHook(StatusType Error)
{

    Ecu_Int_performReset();

    return;
}
#endif /* (AR_OS_USE_SHUTDOWNHOOK == STD_ON) */

#if (AR_OS_USE_STARTUPHOOK == STD_ON)
void StartupHook(void)
{
    return;
}
#endif /* (AR_OS_USE_STARTUPHOOK == STD_ON) */

#if (AR_OS_USE_POSTTASKHOOK == STD_ON)
void PostTaskHook(void)
{
    return;
}
#endif /* (AR_OS_USE_POSTTASKHOOK == STD_ON) */

#if (AR_OS_USE_PRETASKHOOK == STD_ON)
void PreTaskHook(void)
{
    return;
}
#endif /* (AR_OS_USE_PRETASKHOOK == STD_ON) */

#define OS_STOP_SEC_CALLOUT_CODE
#include <Os_MemMap.h>
