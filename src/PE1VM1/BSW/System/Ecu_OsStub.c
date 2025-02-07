/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		Ecu_OsStub.c
 * [Module]			Os Stub
 * [Function]		Os Stub
 * [Notes]			None
 ****************************************************************************/

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <SS.h>
#include <Os.h>
#include "Dma.h"

#include <Ecu_Memmap_SdaDisableB_env.h>
#include <Ecu_Memmap.h>
#include <Ecu_Int.h>


#include <Ecu_Memmap_SdaDisableE_env.h>
/*----------------------------------------------------------------------------
 *		Defines
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *      Prototypes
 *--------------------------------------------------------------------------*/
ISR(OS_SYSTEM_COUNTER_ISR0);

/*----------------------------------------------------------------------------
 *		Codes
 *--------------------------------------------------------------------------*/
/**---------------------------------------------------------------------------
 * [Format]		ISR(OS_SYSTEM_COUNTER_ISR0)
 * [Function]	
 * [Arguments]	None
 * [Return]		None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(OS_SYSTEM_COUNTER_ISR0)
{
    (void)IncrementCounter((CounterType)OS_SYSTEM_COUNTER0); /* call System Counter ISR */
    return;
}

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
