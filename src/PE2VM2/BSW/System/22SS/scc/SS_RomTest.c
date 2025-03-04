/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_RomTest.c
 * [Module]			RomTest
 * [Function]		RomTest
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

#include <SS_MemmapSdaDisableE_Env.h>

#include <SS_MemmapSdaSelectB_Env.h>
#include <SS_RomTest.h>
#include <SS_Error.h>

/*----------------------------------------------------------------------------
 *		Symbols
 *--------------------------------------------------------------------------*/
#define SS_ROMTEST_u4CHECKVALUE (0xFFFFFFFFUL)

#define SS_ROMTEST_u4BUFFSIZE_16BYTE (4UL)
#define SS_ROMTEST_u4BUFFCHKPATTERN1 (0xAA55AA55UL)
#define SS_ROMTEST_u4BUFFCHKPATTERN2 (0x55AA55AAUL)

/*----------------------------------------------------------------------------
 *		Prototypes
 *--------------------------------------------------------------------------*/
static uint32 SS_RomTest_execSumCalcSub(uint32 *pt_StartAddr, uint32 u4_Size, uint32 u4_PreviousSum);

/*----------------------------------------------------------------------------
 *		Constant Variables
 *--------------------------------------------------------------------------*/
#if (SS_USE_ROMBUFFCHECK == STD_ON)
#pragma alignvar(16)
static const uint32 SS_RomTest_BufChkTable1[SS_ROMTEST_u4BUFFSIZE_16BYTE] = {
    SS_ROMTEST_u4BUFFCHKPATTERN1,
    SS_ROMTEST_u4BUFFCHKPATTERN1,
    SS_ROMTEST_u4BUFFCHKPATTERN1,
    SS_ROMTEST_u4BUFFCHKPATTERN1};
static const uint32 SS_RomTest_BufChkTable2[SS_ROMTEST_u4BUFFSIZE_16BYTE] = {
    SS_ROMTEST_u4BUFFCHKPATTERN2,
    SS_ROMTEST_u4BUFFCHKPATTERN2,
    SS_ROMTEST_u4BUFFCHKPATTERN2,
    SS_ROMTEST_u4BUFFCHKPATTERN2};
#endif /* (SS_USE_ROMBUFFCHECK == STD_ON) */

#include <SS_MemmapSdaSelectE_Env.h>

/*----------------------------------------------------------------------------
 *		Codes
 *--------------------------------------------------------------------------*/
/**--------------------------------------------------------------------------
 * [Format]		Std_ReturnType SS_RomTest_execImm(const SS_RomTest_OrderType * pt_AreaTbl)
 * [Function]	Immediate Rom test
 * [Arguments]	pt_AreaTbl						: Rom test tabel pointer
 * [Return]		E_OK							: Argument is OK, RamTest is OK
 *				E_NOT_OK						: Argument is error, RamTest is error
 * [Notes]		None
 *--------------------------------------------------------------------------*/
Std_ReturnType SS_RomTest_execImm(const SS_RomTest_OrderType *pt_AreaTbl)
{
    Std_ReturnType u1_Result;
    uint32 *       pt_StartAddr;
    uint32 *       pt_EndAddr;
    uint32         u4_CheckSum;
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
                u4_CheckSum = SS_RomTest_execSumCalcSub(pt_StartAddr, u4_Size, 0UL);
                /* RomSum値チェック */
                if (u4_CheckSum == SS_ROMTEST_u4CHECKVALUE)
                {
                    u1_Result = E_OK;
                }
            }
        }
        else
        {
            u1_Result = E_OK;
        }
    }

    return (u1_Result);
}

/**--------------------------------------------------------------------------
 * [Format]		Std_ReturnType SS_RomTest_execCyc(const SS_RomTest_OrderType * pt_AreaTbl)
 * [Function]	Cyclic Rom test
 * [Arguments]	pt_AreaTbl						: Rom test tabel pointer
 * [Return]		E_OK							: Argument is OK, RamTest is OK
 *				E_NOT_OK						: Argument is error, RamTest is error
 * [Notes]		各領域のテスト開始前にユーザーワークRAMのテスト済みサイズとSum値を0クリアしてから本APIをコールすること
 *--------------------------------------------------------------------------*/
Std_ReturnType SS_RomTest_execCyc(const SS_RomTest_OrderType *pt_AreaTbl)
{
    Std_ReturnType          u1_Result;
    uint32 *                pt_StartAddr;
    uint32 *                pt_EndAddr;
    uint32                  u4_Size;
    uint32                  u4_SplitSize;
    uint32                  u4_CompletedSize;
    uint32 *                pt_TestStartAddr;
    uint32                  u4_RemainingSize;
    SS_RomTest_RamAreaType *pt_work;

    u1_Result = E_NOT_OK;

    /* Nullポインタチェック */
    if ((pt_AreaTbl != NULL_PTR) && (pt_AreaTbl->pt_WorkRam != NULL_PTR))
    {

        u4_Size      = pt_AreaTbl->u4_Size;      /* テストサイズ取得 */
        u4_SplitSize = pt_AreaTbl->u4_SplitSize; /* 分割サイズ取得 */

        if ((0UL != u4_Size) && (0UL != u4_SplitSize))
        {
            /* ユーザワークRAM取得 */
            pt_work = pt_AreaTbl->pt_WorkRam;
            /* テスト領域先頭アドレス取得 */
            pt_StartAddr = pt_AreaTbl->ptStartAddr;
            /* テスト済みサイズ取得 */
            u4_CompletedSize = pt_work->u4Size;
            /* テスト開始アドレスを計算 */
            pt_TestStartAddr = &(pt_StartAddr[u4_CompletedSize / 4UL]);

            /* テスト領域ラップアラウンドチェック */
            pt_EndAddr = &pt_StartAddr[(u4_Size - 1UL) / 4UL];
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
                    pt_work->u4Sum = SS_RomTest_execSumCalcSub(pt_TestStartAddr, u4_SplitSize, pt_work->u4Sum);
                    /* テスト済みサイズを記憶 */
                    if ((SS_TYPE_u4MAX - pt_work->u4Size) >= u4_SplitSize)
                    {
                        pt_work->u4Size += u4_SplitSize;
                    }
                    u1_Result = E_OK;
                    /* 残サイズが分割サイズ以下? */
                }
                else
                { /* テストサイズ0 または、分割サイズなし */
                    pt_work->u4Sum = SS_RomTest_execSumCalcSub(pt_TestStartAddr, u4_RemainingSize, pt_work->u4Sum);
                    /* ROMSUM値チェック */
                    if (pt_work->u4Sum == SS_ROMTEST_u4CHECKVALUE)
                    {
                        u1_Result = E_OK;
                    }
                    /* テスト済みサイズを0にしてテストを循環させる */
                    pt_work->u4Size = 0UL;
                    pt_work->u4Sum  = 0UL;
                }
            }
        }
        else
        {
            u1_Result = E_OK;
        }
    }

    return (u1_Result);
}

/**--------------------------------------------------------------------------
 * [Format]		void SS_RomTest_execBuffChk( void )
 * [Function]	Rom Buffer check
 * [Arguments]	None
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
#if (SS_USE_ROMBUFFCHECK == STD_ON)
void SS_RomTest_execBuffChk(void)
{
    uint32 u4_Size;
    uint32 u4_ReadBuff[SS_ROMTEST_u4BUFFSIZE_16BYTE];

    for (u4_Size = 0UL; u4_Size < SS_ROMTEST_u4BUFFSIZE_16BYTE; u4_Size++)
    {
        u4_ReadBuff[u4_Size] = SS_RomTest_BufChkTable1[u4_Size];
        
        
        if (u4_ReadBuff[u4_Size] != SS_ROMTEST_u4BUFFCHKPATTERN1)
        {
            SS_Error_notify(SS_ERROR_ROMTEST);
        }
    }

    for (u4_Size = 0UL; u4_Size < SS_ROMTEST_u4BUFFSIZE_16BYTE; u4_Size++)
    {
        u4_ReadBuff[u4_Size] = SS_RomTest_BufChkTable2[u4_Size];
        
        
        if (u4_ReadBuff[u4_Size] != SS_ROMTEST_u4BUFFCHKPATTERN2)
        {
            SS_Error_notify(SS_ERROR_ROMTEST);
        }
    }

    return;
}
#endif /* (SS_USE_ROMBUFFCHECK == STD_ON) */

/**--------------------------------------------------------------------------
 * [Format]		static uint32 SS_RomTest_execSumCalcSub
 *					(uint32 u4_StartAddr,uint32 u4_Size,uint32 u4_PreviousSum)
 * [Function]	Calculate ROM-sum value
 * [Arguments]	u4_StartAddr						: Start adress
 *				u4_Size								: Size
 *				u4_PreviousSum						: Previous sum
 * [Return]		u4_Sum								: Sum result
 * [Notes]		None
 *--------------------------------------------------------------------------*/
static uint32 SS_RomTest_execSumCalcSub(uint32 *pt_StartAddr, uint32 u4_Size, uint32 u4_PreviousSum)
{

    uint32 u4_Sum;
    uint32 u4_CurrentIndex;
    uint32 u4_EndIndex;

    u4_Sum          = u4_PreviousSum;
    u4_CurrentIndex = 0UL;
    u4_EndIndex     = u4_Size / 4UL;

    /* SUM値計算 */
    while (u4_EndIndex > u4_CurrentIndex)
    {
        if ((u4_EndIndex - u4_CurrentIndex) >= 8UL) /* EDET_INT30 */
        {
            u4_Sum += pt_StartAddr[u4_CurrentIndex];       /* EDET_INT30 */
            u4_Sum += pt_StartAddr[u4_CurrentIndex + 1UL]; /* EDET_INT30 */
            u4_Sum += pt_StartAddr[u4_CurrentIndex + 2UL]; /* EDET_INT30 */
            u4_Sum += pt_StartAddr[u4_CurrentIndex + 3UL]; /* EDET_INT30 */
            u4_Sum += pt_StartAddr[u4_CurrentIndex + 4UL]; /* EDET_INT30 */
            u4_Sum += pt_StartAddr[u4_CurrentIndex + 5UL]; /* EDET_INT30 */
            u4_Sum += pt_StartAddr[u4_CurrentIndex + 6UL]; /* EDET_INT30 */
            u4_Sum += pt_StartAddr[u4_CurrentIndex + 7UL]; /* EDET_INT30 */
            u4_CurrentIndex += 8UL;                        /* EDET_INT30 */
        }
        else
        {
            u4_Sum += pt_StartAddr[u4_CurrentIndex]; /* EDET_INT30 */
            u4_CurrentIndex += 1UL;
        }
    }

    return (u4_Sum);
}
