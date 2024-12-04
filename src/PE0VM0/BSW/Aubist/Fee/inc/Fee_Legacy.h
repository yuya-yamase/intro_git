/* Fee_Legacy.h v2-0-0                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/LEGACY/HEADER                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef FEE_LEGACY_H
#define FEE_LEGACY_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Fee_Ext.h>
#include "Fee_Mpu_Dev_Const.h"

#include "Fee_Common.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* API関連 */
/* 共通戻り値 */
#define FEE_REQUEST_ACCEPT              ((uint8)0x00U)     /* 要求成功 */
#define FEE_REQUEST_DECLINE             ((uint8)0x01U)     /* 要求拒否 */
#define FEE_REQUEST_IRBLD_CNFM_NOT_OK   ((uint8)0x02U)     /* A confirmation result for intentional rebuilding is not OK. */

/* データFlash動作状態取得要求 */
/* 戻り値 */
#define FEE_IDLING                  ((uint8)0x00U)      /* 待機中 */
#define FEE_WRITING                 ((uint8)0x01U)      /* 書込み中 */
#define FEE_ID_READING              ((uint8)0x02U)      /* ID指定読出し中 */
#define FEE_REBUILDING              ((uint8)0x06U)      /* データ再編中 */
#define FEE_FLS_ERROR               ((uint8)0x08U)      /* FLS異常 */
#define FEE_DFC_ERROR               ((uint8)0x10U)      /* DFC異常動作中 */

/* Hook関連 */
/* 共通処理成否 */
#define FEE_RSP_OK                  ((uint8)0x00U)     /* 処理成功 */
#define FEE_RSP_NG                  ((uint8)0x80U)     /* 処理失敗 */
#define FEE_RSP_NG_DTF_CTRL         ((uint8)0x7FU)     /* データFlashコントローラ異常 */
#define FEE_RSP_TIMEOUT             ((uint8)0xFFU)     /* タイムアウト */
#define FEE_RSP_GARBLED_RAM         ((uint8)0x77U)     /* A garbled RAM was detected. */

/* データ書込み応答Hook */
#define FEE_RSP_NG_INITIALIZE       ((uint8)0x01U)     /* 書込み成功・対象ブロックなし */
#define FEE_RSP_NG_WRITE_DATA       ((uint8)0x81U)     /* 書込み失敗 */
#define FEE_RSP_NG_NODATA           ((uint8)0x82U)     /* 書込み失敗・対象ブロックなし */

/* データ読出し応答Hook（ID指定読出し） */
#define FEE_RSP_NODATA              ((uint8)0x83U)     /* 該当データなし */
#define FEE_RSP_UNUSED              ((uint8)0x84U)     /* ブロック未使用 */

/* 定期処理の呼び出しタイミング */
#define FEE_CALL_TIMING_PERIODIC        (0U)    /* 定期間隔での呼び出し */
#define FEE_CALL_TIMING_NOT_PERIODIC    (1U)    /* 不定期間隔での呼び出し  */

/* 修復種別 */
#define FEE_RSP_RESTORE_KIND_RECOVER        (0U)    /* 大セクタ：エリア異常、小セクタ：復帰      */
#define FEE_RSP_RESTORE_KIND_RESTORE        (1U)    /* 小セクタ：修復（二重化データの不整合修復） */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

/* API */
/* データ書込み要求 */
FUNC(uint8, FEE_CODE) Fee_Legacy_WriteData( uint16 data_id, P2CONST(uint8, AUTOMATIC, TYPEDEF) data_address, uint8 No );
/* データ読出し要求（ID指定読出し） */
FUNC(uint8, FEE_CODE) Fee_Legacy_ReadData( uint16 data_id, uint8 No, P2VAR( uint8, AUTOMATIC, FEE_APPL_DATA ) DataBufferPtr );
/* データFlashドライバ初期化要求（リセット時） */
FUNC(void, FEE_CODE) Fee_Legacy_PwonInit( void );
/* データFlashドライバ強制初期化 */
FUNC(void, FEE_CODE) Fee_Legacy_Abort( void );
/* データFlash動作状態取得要求 */
FUNC(uint8, FEE_CODE) Fee_Legacy_GetStatus( void );
/* データFlash定期処理 */
FUNC(void, FEE_CODE) Fee_Legacy_PeriodicFunc( void );

/* データFlash不定期処理 */
FUNC(void, FEE_CODE) Fee_Legacy_NonPeriodicFunc( void );

/* データ長取得 */
FUNC(Std_ReturnType, FEE_CODE) Fee_Legacy_GetDataLength( uint16 data_id, P2VAR(uint16, AUTOMATIC, TYPEDEF) DataLength);

/* Hook */
/* データ書込み応答Hook */
FUNC(void, FEE_CODE) Fee_Write_Rsp_Hook(
    uint8   result,
    uint16  data_id,
    uint8   No
);
/* データ読出し応答Hook（ID指定読出し） */
FUNC(void, FEE_CODE) Fee_Read_Rsp_Hook(
    uint8   result,
    uint16  data_id,
    uint8   No
);

/* データ再編要求 */    
FUNC(uint8, FEE_CODE) Fee_Legacy_Rebuild( uint8 No );  

FUNC( Fee_ExtFreeSpaceReturnType, FEE_CODE )
Fee_Legacy_GetFreeSpace(
    uint8  AreaNo,
    uint16 LimitSearchMngArea,
    uint32 LimitSearchDataArea,
    P2VAR( Fee_ExtFreeSpaceInfoType, AUTOMATIC, TYPEDEF ) FreeSpaceInfoPtr
);

/* データ再編応答Hook */    
FUNC(void, FEE_CODE) Fee_Rebuild_Rsp_Hook( uint8 result, uint8 No );    

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* FEE_LEGACY_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  1-1-0          :2019/08/27                                              */
/*  2-0-0          :2022/08/24                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
