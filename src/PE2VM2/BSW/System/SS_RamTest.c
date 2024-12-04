/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_RamTest.c
 * [Module]			RamTest
 * [Function]		RamTest
 * [Notes]			None
 ****************************************************************************/

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <SS_TYPE.h>
#include <SS_Internal.h>

#include <SS_MemmapSdaDisableB_Env.h>
#include <SS_MemmapProtect_Env.h>

#include <SS_RamTest_RamAreaTop0Data.h>
#include <SS_RamTest_RamAreaBottom0Data.h>
#if (SS_USE_CORE_COUNT >= 2u)
#include <SS_RamTest_RamAreaTop1Data.h>
#include <SS_RamTest_RamAreaBottom1Data.h>
#endif /* (SS_USE_CORE_COUNT >= 2u) */
#if (SS_USE_CORE_COUNT >= 3u)
#include <SS_RamTest_RamAreaTop2Data.h>
#include <SS_RamTest_RamAreaBottom2Data.h>
#endif /* (SS_USE_CORE_COUNT >= 3u) */
#if (SS_USE_CORE_COUNT >= 4u)
#include <SS_RamTest_RamAreaTop3Data.h>
#include <SS_RamTest_RamAreaBottom3Data.h>
#endif /* (SS_USE_CORE_COUNT >= 4u) */
#include <SS_MemmapSdaDisableE_Env.h>

#include <SS_MemmapSdaSelectB_Env.h>
#include <SS_CpuCore.h>
#include <SS_RamTest.h>
#include <SS_Error.h>
#include <SS_Memory.h>

/*----------------------------------------------------------------------------
 *		Structures
 *--------------------------------------------------------------------------*/
typedef struct SS_ST_AddrBusChkInstanceType
{
    uint32 *const ptRamAreaTopAddr;    /* Topアドレス */
    uint32 *const ptRamAreaBottomAddr; /* Bottomアドレス */
} SS_AddrBusChkInstanceType;

/*----------------------------------------------------------------------------
 *		Constant Variables
 *--------------------------------------------------------------------------*/
#if (SS_USE_ADDRBUSCHECK == STD_ON)
static const SS_AddrBusChkInstanceType SS_RamTest_stAddrBusChkIns[SS_USE_CORE_COUNT] = {
    {&SS_AddrBusChk_u4RamAreaTop_0, &SS_AddrBusChk_u4RamAreaBottom_0}
#if (SS_USE_CORE_COUNT >= 2u)
    ,
    {&SS_AddrBusChk_u4RamAreaTop_1, &SS_AddrBusChk_u4RamAreaBottom_1}
#endif /* (SS_USE_CORE_COUNT >= 2u) */
#if (SS_USE_CORE_COUNT >= 3u)
    ,
    {&SS_AddrBusChk_u4RamAreaTop_2, &SS_AddrBusChk_u4RamAreaBottom_2}
#endif /* (SS_USE_CORE_COUNT >= 3u) */
#if (SS_USE_CORE_COUNT >= 4u)
    ,
    {&SS_AddrBusChk_u4RamAreaTop_3, &SS_AddrBusChk_u4RamAreaBottom_3}
#endif /* (SS_USE_CORE_COUNT >= 4u) */
};
#endif /* (SS_USE_ADDRBUSCHECK == STD_ON) */

#include <SS_MemmapSdaSelectE_Env.h>
/*----------------------------------------------------------------------------
 *		Symbols
 *--------------------------------------------------------------------------*/
#define SS_RAMTEST_u4ADDRBUSCHECKCODE (0xA55AA55AUL)

/*----------------------------------------------------------------------------
 *		Codes
 *--------------------------------------------------------------------------*/

/**---------------------------------------------------------------------------
 * [Format]		Std_ReturnType SS_RamTest_execImm(const SS_RamTest_OrderType * pt_AreaTbl)
 * [Function]	Immediate Ram test
 * [Arguments]	pt_AreaTbl 						: Ram test tabel pointer
 * [Return]		E_OK							: Argument is OK
 *				E_NOT_OK						: Argument is error
 * [Notes]		None
 *--------------------------------------------------------------------------*/
Std_ReturnType SS_RamTest_execImm(const SS_RamTest_OrderType *pt_AreaTbl)
{
    Std_ReturnType u1_Result;
    uint32 *       pt_StartAddr;
    uint32 *       pt_EndAddr;
    uint32         u4_Size;

    u1_Result = E_NOT_OK;

    /* Nullポインタチェック */
    if (pt_AreaTbl != NULL_PTR)
    {

        u4_Size = pt_AreaTbl->u4_Size; /* テストサイズ取得 */
        if (0UL != u4_Size)
        {
            /* テスト領域先頭アドレス取得 */
            pt_StartAddr = pt_AreaTbl->ptStartAddr;
            /* テスト領域ラップアラウンドチェック */
            pt_EndAddr = &(pt_StartAddr[(u4_Size - 1UL) / 4UL]);

            if ((pt_StartAddr <= pt_EndAddr))
            {
                SS_Memory_writeScan(pt_StartAddr, u4_Size);
                u1_Result = E_OK;
            }
        }
        else
        {
            u1_Result = E_OK;
        }
    }
    return (u1_Result);
}

/**---------------------------------------------------------------------------
 * [Format]		Std_ReturnType SS_RamTest_execCyc(const SS_RamTest_OrderType * pt_AreaTbl)
 * [Function]	Cyclic Ram test
 * [Arguments]	pt_AreaTbl 						: Ram test tabel pointer
 * [Return]		E_OK							: Argument is OK
 *				E_NOT_OK						: Argument is error
 * [Notes]		各領域のテスト開始前にユーザーワークRAMのテスト済みサイズを0クリアしてから本APIをコールすること
 *--------------------------------------------------------------------------*/
Std_ReturnType SS_RamTest_execCyc(const SS_RamTest_OrderType *pt_AreaTbl)
{
    Std_ReturnType u1_Result;
    uint32 *       pt_StartAddr;
    uint32 *       pt_EndAddr;
    uint32         u4_Size;
    uint32         u4_SplitSize;
    uint32         u4_CompletedSize;
    uint32 *       pt_TestStartAddr;
    uint32         u4_RemainingSize;

    u1_Result = E_NOT_OK;

    /* Nullポインタチェック */
    if ((pt_AreaTbl != NULL_PTR) && (pt_AreaTbl->pt_WorkRam != NULL_PTR))
    {

        u4_Size      = pt_AreaTbl->u4_Size;      /* テストサイズ取得 */
        u4_SplitSize = pt_AreaTbl->u4_SplitSize; /* 分割サイズ取得 */
        /* テストサイズあり 且つ、分割サイズあり? */
        if ((0UL != u4_Size) && (0UL != u4_SplitSize))
        {
            /* テスト済みサイズ取得 */
            u4_CompletedSize = *(pt_AreaTbl->pt_WorkRam);
            /* テスト領域先頭アドレス取得 */
            pt_StartAddr = pt_AreaTbl->ptStartAddr;
            /* テスト開始アドレスを計算 */
            pt_TestStartAddr = &pt_StartAddr[u4_CompletedSize / 4UL];

            /* テスト領域ラップアラウンドチェック */

            pt_EndAddr = &(pt_StartAddr[(u4_Size - 1UL) / 4UL]);
            if ((pt_StartAddr <= pt_EndAddr))
            {
                /* 残りのサイズ計算 */
                if (u4_Size >= u4_CompletedSize)
                {
                    u4_RemainingSize = u4_Size - u4_CompletedSize;
                }
                else
                {
                    u4_RemainingSize = 0UL;
                }

                /* 残サイズが分割サイズ以上? */
                if (u4_RemainingSize > u4_SplitSize)
                {
                    /* 分割サイズ分を実施して継続 */
                    SS_Memory_scan(pt_TestStartAddr, u4_SplitSize);
                    /* テスト済みサイズを記憶 */
                    if (SS_TYPE_u4MAX - *(pt_AreaTbl->pt_WorkRam) >= u4_SplitSize)
                    {
                        *pt_AreaTbl->pt_WorkRam += u4_SplitSize;
                    }
                }
                else
                {
                    /* 分割サイズ以下のテストを実施して終了 */
                    SS_Memory_scan(pt_TestStartAddr, u4_RemainingSize);
                    /* テスト済みサイズを0にしてテストを循環させる */
                    *pt_AreaTbl->pt_WorkRam = 0UL;
                }

                u1_Result = E_OK;
            }
        }
        else
        {
            u1_Result = E_OK;
        }
    }

    return (u1_Result);
}

/* ---------------------------------------------------------------------------
 * [Format]		void SS_RamTest_initAddrBusChk(void)
 * [Function]	Initialize top and bottom of ram area
 * [Arguments]	None
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
#if (SS_USE_ADDRBUSCHECK == STD_ON)
void SS_RamTest_initAddrBusChk(void)
{
    SS_CoreIdType                    u4_CoreId;
    const SS_AddrBusChkInstanceType *pt_AddrBusChkIns;

    u4_CoreId = SS_CpuCore_getCoreID();

    pt_AddrBusChkIns = &SS_RamTest_stAddrBusChkIns[u4_CoreId];

    *(pt_AddrBusChkIns->ptRamAreaTopAddr)    = SS_RAMTEST_u4ADDRBUSCHECKCODE;
    *(pt_AddrBusChkIns->ptRamAreaBottomAddr) = SS_RAMTEST_u4ADDRBUSCHECKCODE;

    return;
}
#endif /* (SS_USE_ADDRBUSCHECK == STD_ON) */

/**---------------------------------------------------------------------------
 * [Format]		void SS_RamTest_execAddrBusChk(void)
 * [Function]	Check top and bottom of ram area
 * [Arguments]	None
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
#if (SS_USE_ADDRBUSCHECK == STD_ON)
void SS_RamTest_execAddrBusChk(void)
{
    SS_CoreIdType                    u4_CoreId;
    const SS_AddrBusChkInstanceType *pt_AddrBusChkIns;

    u4_CoreId = SS_CpuCore_getCoreID();

    pt_AddrBusChkIns = &SS_RamTest_stAddrBusChkIns[u4_CoreId];

    if ((*(pt_AddrBusChkIns->ptRamAreaBottomAddr) != SS_RAMTEST_u4ADDRBUSCHECKCODE) ||
        (*(pt_AddrBusChkIns->ptRamAreaTopAddr) != SS_RAMTEST_u4ADDRBUSCHECKCODE))
    {
        SS_Error_notify(SS_ERROR_RAMTEST);
    }

    return;
}
#endif /* (SS_USE_ADDRBUSCHECK == STD_ON) */
