/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_CpuCore.h
 * [Module]			CPU
 * [Function]		Management of CPU resources
 * [Notes]			None
 ****************************************************************************/

#ifndef SS_CPUCORE_H
#define SS_CPUCORE_H

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#if !defined(__LANGUAGE_ASM__)
#include <Std_Types.h>
#endif
#include <SS_Internal.h>

#if !defined(__LANGUAGE_ASM__)
/*-----------------------------------------------------------------------------
 *		Types
 *-----------------------------------------------------------------------------*/
typedef uint32 SS_CoreIdType;

/*----------------------------------------------------------------------------
 *		Prototypes
 *--------------------------------------------------------------------------*/
/* Disable or enable interrupts */
#if (SS_USE_LWH == SS_LWH_NONE)
void SS_CpuCore_syncp(void);
#endif

void SS_CpuCore_performReset(void);
#if (SS_USE_LWH == SS_LWH_NONE)
void SS_CpuCore_clearResetFactor(void);
#else
#define SS_CpuCore_clearResetFactor()
#endif

#endif /* !defined(__LANGUAGE_ASM__) */
/*----------------------------------------------------------------------------
 *		Symbols
 *--------------------------------------------------------------------------*/
#define SS_CPUCORE_u4MASTERCORE (0UL)
#define SS_CPUCORE_u4SLAVECORE1 (1UL)
#define SS_CPUCORE_u4SLAVECORE2 (2UL)
#define SS_CPUCORE_u4SLAVECORE3 (3UL)

#if !defined(__LANGUAGE_ASM__)

/* シングルコアではsnoozeする必要がないため、空マクロで定義する。 */
#define SS_CpuCore_snooze()
/* コンパイルスイッチ"SS_USE_CORE_COUNT"の可読性向上のためのマクロ */
#if (SS_USE_CORE_COUNT >= 2u)
SS_CoreIdType SS_CpuCore_getCoreID(void);

#define SS_CpuCore_entryMasterSection()          \
    {                                            \
        SS_CoreIdType u4CoreId;                  \
        u4CoreId = SS_CpuCore_getCoreID();       \
        if (u4CoreId == SS_CPUCORE_u4MASTERCORE) \
        {

#define SS_CpuCore_exitMasterSection() \
    }                                  \
    }
#else // (SS_USE_CORE_COUNT >= 2u)
#define SS_CpuCore_getCoreID() (SS_CPUCORE_u4MASTERCORE)

#define SS_CpuCore_entryMasterSection()
#define SS_CpuCore_exitMasterSection()

#endif // (SS_USE_CORE_COUNT >= 2u)

#define SS_CpuCore_refresh()

#else /* !defined(__LANGUAGE_ASM__) */
#if (SS_USE_CORE_COUNT >= 2u)
.globl _SS_CpuCore_getCoreID
#endif
#endif /* !defined(__LANGUAGE_ASM__) */

#endif /* SS_CPUCORE_H */
