/*
    Copyright (C) 2018 By eSOL Co.,Ltd. Tokyo, Japan

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
[Os_internal2.h] - Os module header
****************************************************************************/

#ifndef OS_INTERNAL2_H
#define OS_INTERNAL2_H

/*
 * followings use Configuration Information
 *
 */
#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)
#define AR_FNC(name) ar_fn_ ## name
#include "Os_internal2_2.h"
#if defined(AR_FUNC_OS_SERVICE)
#include "Os_internal2_3.h"
#else   /* defined(AR_FUNC_OS_SERVICE) */
#include "Os_internal2_1.h"
#endif  /* defined(AR_FUNC_OS_SERVICE) */
#else   /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */
#include "Os_internal2_1.h"
#endif  /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */


#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)
#define OS_START_SEC_CODE_SHARED
#include "Os_MemMap.h"

#else /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */
#define OS_START_SEC_CODE
#include "Os_MemMap.h"

#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */

extern void StartOS(AppModeType Mode);
extern StatusType GetTaskID(TaskRefType TaskID);
extern ApplicationType GetApplicationID(void);
extern ISRType GetISRID(void);
extern CoreIdType GetCoreID(void);
extern ApplicationType GetCurrentApplicationID(void);
extern void StartCore(CoreIdType CoreID, StatusType *p_status);
extern void StartNonAutosarCore(CoreIdType CoreID, StatusType *p_status);

#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)
#define OS_STOP_SEC_CODE_SHARED
#include "Os_MemMap.h"

#else /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */


#if (AR_OS_USE_ERRORHOOK == STD_ON)
extern void ErrorHook(StatusType Error);
#endif /* (AR_OS_USE_ERRORHOOK == STD_ON) */

#if (AR_OS_USE_PRETASKHOOK == STD_ON)
extern void PreTaskHook(void);
#endif /* (AR_OS_USE_PRETASKHOOK == STD_ON) */

#if (AR_OS_USE_POSTTASKHOOK == STD_ON)
extern void PostTaskHook(void);
#endif /* (AR_OS_USE_POSTTASKHOOK == STD_ON) */

#if (AR_OS_USE_STARTUPHOOK == STD_ON)
extern void StartupHook(void);
#endif /* (AR_OS_USE_STARTUPHOOK == STD_ON) */

#if (AR_OS_USE_SHUTDOWNHOOK == STD_ON)
extern void ShutdownHook(StatusType Error);
#endif /* (AR_OS_USE_SHUTDOWNHOOK == STD_ON) */

#if (AR_OS_USE_PROTECTIONHOOK == STD_ON)
extern ProtectionReturnType ProtectionHook(StatusType FatalError);
#endif /* (AR_OS_USE_PROTECTIONHOOK == STD_ON) */

#endif /* OS_INTERNAL2_H */
