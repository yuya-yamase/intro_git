/*****************************************************************************
 *	Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_CpuCore.c
 * [Module]			CPU
 * [Function]		Management of CPU resources
 * [Notes]			None
 ****************************************************************************/

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <stdint.h>
#include <Std_Types.h>
#include <SS_TYPE.h>
#include <SS_Internal.h>

#include <SS_MemmapSdaDisableB_Env.h>
#include <SS_Memmap_Env.h>

#include <SS_MemmapSdaDisableE_Env.h>

#include <SS_MemmapSdaSelectB_Env.h>
#include <SS_Boot.h>
#include <SS_CpuCore.h>

#include <SS_MemmapSdaSelectE_Env.h>

/*----------------------------------------------------------------------------
 *		Symbols
 *--------------------------------------------------------------------------*/
#define REG_u4SWSRESA                (*(volatile uint32 *)((uintptr_t)0xFF98840CUL)) /* SWSRESA */
#define REG_u4RESKCPROT0             (*(volatile uint32 *)((uintptr_t)0xFF980F00UL)) /* RESKCPROT0 */
#define VAL_u4RESKCPROT0_KCE_ENABLE  (0xA5A5A501UL)
#define VAL_u4RESKCPROT0_KCE_DISABLE (0xA5A5A500UL)

#define VAL_u4SWSRESA_SYSTEM_RESET2 (0x00000001UL) /* R_SWRESET */

/*----------------------------------------------------------------------------
 *		Prototypes
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *		Codes
 *--------------------------------------------------------------------------*/

/**---------------------------------------------------------------------------
 * [Format]		void SS_CpuCore_clearResetFactor(void)
 * [Function]	Clear Reset factor register
 * [Arguments]	None
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
#if (SS_USE_LWH == SS_LWH_NONE)
void SS_CpuCore_clearResetFactor(void)
{
    
    SS_Boot_clearResetFactor();
    return;
}
#endif

/**---------------------------------------------------------------------------
 * [Format]		void SS_CpuCore_performReset(void)
 * [Function]	Reset micro controller unit
 * [Arguments]	None
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
void SS_CpuCore_performReset(void)
{
    while (1)
    {
#if (SS_USE_RESET == STD_ON)
        REG_u4RESKCPROT0 = VAL_u4RESKCPROT0_KCE_ENABLE;
        REG_u4SWSRESA    = VAL_u4SWSRESA_SYSTEM_RESET2;
        REG_u4RESKCPROT0 = VAL_u4RESKCPROT0_KCE_DISABLE;
#endif /* SS_USE_RESET == SS_RESET_ON */
    }
}
