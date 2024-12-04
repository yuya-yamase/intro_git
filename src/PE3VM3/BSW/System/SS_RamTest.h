/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_RamTest.h
 * [Module]			RamTest
 * [Function]		RamTest
 * [Notes]			None
 ****************************************************************************/

#ifndef SS_RAMTEST_H
#define SS_RAMTEST_H

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <SS_Internal.h>

/*----------------------------------------------------------------------------
 *		Structures
 *--------------------------------------------------------------------------*/

typedef uint32 SS_RamTest_RamAreaType; /* テスト済みサイズ */

typedef struct SS_ST_RamTest_RomAreaType
{
    uint32 *const                 ptStartAddr;  /* テスト開始アドレス */
    const uint32                  u4_Size;      /* テストサイズ       */
    const uint32                  u4_SplitSize; /* テスト分割サイズ   */
    SS_RamTest_RamAreaType *const pt_WorkRam;   /* ワークRAMポインタ  */
} SS_RamTest_OrderType;

/*----------------------------------------------------------------------------
 *		Symbols
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *		Prototypes
 *--------------------------------------------------------------------------*/
Std_ReturnType SS_RamTest_execImm(const SS_RamTest_OrderType *pt_AreaTbl);
Std_ReturnType SS_RamTest_execCyc(const SS_RamTest_OrderType *pt_AreaTbl);
#if (SS_USE_ADDRBUSCHECK == STD_ON)
void SS_RamTest_initAddrBusChk(void);
void SS_RamTest_execAddrBusChk(void);
#endif /* (SS_USE_ADDRBUSCHECK == STD_ON) */

#endif /* SS_RAMTEST_H */
