/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_RamTest_RamAreaTop2Data.h
 * [Module]			RamTest_RamAreaTop2Data
 * [Function]		RamTest_RamAreaTop2Data
 * [Notes]			None
 ****************************************************************************/

#ifndef SS_RAMTEST_RAMAREATOP2DATA_H
#define SS_RAMTEST_RAMAREATOP2DATA_H

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <SS_Internal.h>

/*----------------------------------------------------------------------------
 *		Externs
 *--------------------------------------------------------------------------*/
#if (SS_USE_ADDRBUSCHECK == STD_ON)
#if (SS_USE_CORE_COUNT >= 3u)
extern uint32 SS_AddrBusChk_u4RamAreaTop_2;
#endif /* (SS_USE_CORE_COUNT >= 3u) */
#endif /* (SS_USE_ADDRBUSCHECK == STD_ON) */

#endif /* SS_RAMTEST_RAMAREATOP2DATA_H */
