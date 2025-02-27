/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_RamTest_RamAreaBottom1Data.h
 * [Module]			RamTest_RamAreaBottom1Data
 * [Function]		RamTest_RamAreaBottom1Data
 * [Notes]			None
 ****************************************************************************/

#ifndef SS_RAMTEST_RAMAREABOTTOM1DATA_H
#define SS_RAMTEST_RAMAREABOTTOM1DATA_H

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <SS_Internal.h>

/*----------------------------------------------------------------------------
 *		Externs
 *--------------------------------------------------------------------------*/
#if (SS_USE_ADDRBUSCHECK == STD_ON)
#if (SS_USE_CORE_COUNT >= 2u)
extern uint32 SS_AddrBusChk_u4RamAreaBottom_1;
#endif /* (SS_USE_CORE_COUNT >= 2u) */
#endif /* (SS_USE_ADDRBUSCHECK == STD_ON) */

#endif /* SS_RAMTEST_RAMAREABOTTOM1DATA_H */
