/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_RomTest.h
 * [Module]			RomTest
 * [Function]		RomTest
 * [Notes]			None
 ****************************************************************************/

#ifndef SS_ROMTEST_H
#define SS_ROMTEST_H

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <SS_Internal.h>

/*----------------------------------------------------------------------------
 *		Structures
 *--------------------------------------------------------------------------*/
typedef struct SS_ST_RomTest_RamAreaType
{
    uint32 u4Size; /* テスト済みサイズ */
    uint32 u4Sum;  /* Sum値 */
} SS_RomTest_RamAreaType;

typedef struct SS_ST_RomTest_RomAreaType
{
    uint32 *const                 ptStartAddr;  /* テスト開始アドレス */
    const uint32                  u4_Size;      /* テストサイズ       */
    const uint32                  u4_SplitSize; /* テスト分割サイズ   */
    SS_RomTest_RamAreaType *const pt_WorkRam;   /* ワークRAMポインタ  */
} SS_RomTest_OrderType;

/*----------------------------------------------------------------------------
 *		Symbols
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *		Prototypes
 *--------------------------------------------------------------------------*/
Std_ReturnType SS_RomTest_execImm(const SS_RomTest_OrderType *pt_AreaTbl);
Std_ReturnType SS_RomTest_execCyc(const SS_RomTest_OrderType *pt_AreaTbl);
#if (SS_USE_ROMBUFFCHECK == STD_ON)
void SS_RomTest_execBuffChk(void);
#endif

#endif /* SS_ROMTEST_H */
