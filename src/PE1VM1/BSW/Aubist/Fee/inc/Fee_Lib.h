/* Fee_Lib.h v2-0-0                                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/LIB/HEADER                                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef FEE_LIB_H
#define FEE_LIB_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "Fee_Mpu_Const.h"
#include <Fls.h>
#include <Mscd_Common.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define FEE_DUMMY_AREA_NO_FOR_LWPOS     (0U)    /* 最終書き込み位置初期化時のダミーエリア番号 */

/* 設定処理種別 */
#define FEE_LWPREAD         ((uint8)0x00U)      /* 設定処理種別：ID指定読出しor空き領域確認 */
#define FEE_LWPWRITE        ((uint8)0x01U)      /* 設定処理種別：書込みor再編 */
#define FEE_LWPKIND_INIT    ((uint8)0xFFU)      /* 設定処理種別初期値 */

#define FEE_LIB_EQUAL       ((uint8)0x00U)
#define FEE_LIB_UNEQUAL     ((uint8)0x01U)

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

FUNC( Std_ReturnType, FEE_CODE )
Fee_Lib_CheckCpuDtfData( void );

FUNC( void, FEE_CODE )
Fee_Lib_SetCpuDtfDataSub( void );

FUNC( uint8, FEE_CODE )
Fee_Lib_CompareMemory(
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) Data1,
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) Data2,
    uint32                               Length
);

FUNC( void, FEE_CODE )
Fee_Lib_CopyMemory(
    P2VAR( uint8, AUTOMATIC, TYPEDEF )   DstData,
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) SrcData,
    uint32                               Length
);

#if ( MSCD_FREESPACE_USE == STD_ON )
FUNC( Std_ReturnType, FEE_CODE )
Fee_Lib_GetLastWritePosLite(
    uint8 AreaNo,
    uint8 CurrentJobKind,
    P2VAR( Fee_LwpInfType, AUTOMATIC, TYPEDEF ) DstLastWritePos
);

FUNC( void, FEE_CODE )
Fee_Lib_SetLastWritePosLite(
    uint8 AreaNo,
    P2CONST( Fee_LwpInfType, AUTOMATIC, TYPEDEF ) SrcLastWritePos
);
#endif /*( MSCD_FREESPACE_USE == STD_ON )*/

/* データフラッシュのアドレス値の変換　絶対アドレス⇔相対アドレス */
FUNC(uint32, FEE_CODE) Fee_ConvAddr_AbsToBaseRelative( uint32 u4_absolute_address );
FUNC(uint32, FEE_CODE) Fee_ConvAddr_AbsToSectorTopRelative( uint32 u4_absolute_address );
FUNC(uint32, FEE_CODE) Fee_ConvAddr_RelativeToAbsolute( uint32 u4_relative_address );

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

#define FEE_START_SEC_CONST_32
#include <Fee_MemMap.h>

/* 全体としてのコンフィグレーション項目 */
/* 書込みHardware待ち時間閾値 */
extern CONST(AB_83_ConstV uint32, FEE_CONST) Fee_HwLmtWriteTime;

/* エリア・ブロックステータスデータアドレス */
extern CONST(AB_83_ConstV uint8, FEE_CONST) Fee_ASBSDataTBL[FEE_ASBSDATASETNUM][FEE_ASBSDATAKINDNUM];

#define FEE_STOP_SEC_CONST_32
#include <Fee_MemMap.h>

#endif /* FEE_LIB_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  1-1-0          :2019/08/23                                              */
/*  2-0-0          :2022/08/24                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
