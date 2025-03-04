/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_WdgM.h
 * [Module]			WdgM
 * [Function]		WdgM
 * [Notes]			None
 ****************************************************************************/

#ifndef SS_WDGM_H
#define SS_WDGM_H

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>

/*----------------------------------------------------------------------------
 *		Structures
 *--------------------------------------------------------------------------*/
typedef struct SS_ST_WdgM_RomAreaType
{
    const uint8  u1_CheckPointID; /* チェックポイントID設定 */
    const uint32 u4_MinTime;      /* MIN時間判定設定値 */
    const uint32 u4_MaxTime;      /* MAX時間判定設定値 */
} SS_WdgM_RomAreaType;

typedef struct SS_ST_WdgM_RamAreaType
{
    uint32 u4_ClockTime;       /* チェックポイントID通過時刻 */
    uint8  u1_ProcessErrorCnt; /* 順序エラーカウンタ */
    uint8  u1_MinTimeErrorCnt; /* MIN時間エラーカウンタ */
    uint8  u1_MaxTimeErrorCnt; /* MAX時間エラーカウンタ */
    uint8  u1_PreCheckPoint;   /* 通過チェックポイントID */
} SS_WdgM_RamAreaType;

typedef struct SS_ST_WdgM_RomAreaOrderType
{
    SS_WdgM_RomAreaType *      pt_RomAreaTbl; /* ROMエリアテーブルポインタ */
    SS_WdgM_RamAreaType *const pt_RamAreaTbl; /* ワークRAMテーブルポインタ */
} SS_WdgM_OrderType;

/*----------------------------------------------------------------------------
 *		Symbols
 *--------------------------------------------------------------------------*/
#define SS_u1WDGM_CHECKPOINT_TERMINATE ((uint8)0xFFU) /* チェックポイントの終端 */

/*----------------------------------------------------------------------------
 *		Prototypes
 *--------------------------------------------------------------------------*/
Std_ReturnType SS_WdgM_init(const SS_WdgM_OrderType *pt_OrderTbl);
Std_ReturnType SS_WdgM_checkPointReached(const SS_WdgM_OrderType *pt_OrderTbl, uint8 u1_CheckPointId);
Std_ReturnType SS_WdgM_timeoutCheck(const SS_WdgM_OrderType *pt_OrderTbl);
#endif /* SS_WDGM_H */
