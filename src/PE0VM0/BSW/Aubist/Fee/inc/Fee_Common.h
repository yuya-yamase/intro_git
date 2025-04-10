/* Fee_Common.h v2-0-0                                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/COMMON/HEADER                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef FEE_COMMON_H
#define FEE_COMMON_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
/* DTFEE 型定義ヘッダファイル */
#include <Mscd_Common.h>
#include "Fee_Mpu_Const.h"
#include "Fee_Mpu_Dev_Const.h"
#include "../cfg/Fee_Cfg_Internal_Ext.h"
#include "Fee_Mpu_Const_Ext.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define FEE_NUM_OF_BITS_IN_1BYTE    (8U)
#define FEE_NUM_OF_BITS_IN_2BYTE    (16U)
#define FEE_NUM_OF_BITS_IN_3BYTE    (24U)

#define FEE_NUM_OF_BYTE_IN_UINT16   (2U)
#define FEE_NUM_OF_BYTE_IN_UINT32   (4U)

/* データ長 */
#define FEE_LENGTH_00           (0U)
#define FEE_LENGTH_02           (2U)
#define FEE_LENGTH_04           (4U)
#define FEE_LENGTH_06           (6U)
#define FEE_LENGTH_08           (8U)
#define FEE_LENGTH_16           (16U)
#define FEE_LENGTH_32           (32U)
#define FEE_LENGTH_64           (64U)

#define FEE_LENGTH_UNDEF        (0U)
#define FEE_LENGTH_INVALID      (0U)

/* For checking redundancy data */
#define FEE_MIRROR_CHECK_UINT8  (0xFFU)
#define FEE_MIRROR_CHECK_UINT16 (0xFFFFU)
#define FEE_MIRROR_CHECK_UINT32 (0xFFFFFFFFU)


#define FEE_ASBSDATASETNUM     (2U)
#define FEE_ASBSDATAKINDNUM    (4U)

#define FEE_CWRITE_MAX         (6U) /* The max number of acceptable write requests at MNGDFC.                              */
                                    /* The max case is to fix all block status of one sector.                              */
                                    /* Block status which need to fix are 3 status, "used", "transferring", and "using".   */
                                    /* And each status is redundancy data using 2 words.                                   */

#define FEE_DATA_LENGTH_MAX    (32768U)     /* The maximum length in writing data.                                                      */
                                            /* Essentially, FEE is able to accept range of uint16 in AUTOSAR.                           */
                                            /* However, FEE limit the valid range for the following reasons.                            */
                                            /*     1. It may overflow because FEE adds some value to the data length.                   */
                                            /*     2. The developer guarantees only a smaller range than the max of uint16.             */

#if (FEE_DATA_FLASH_ECC_FIX_SIZE == FEE_BYTE_NUM_04)

#define FEE_AREASTATUSLEN       ((uint8)8U)     /* (4 * 2)[byte] */
#define FEE_BLOCKSTATUSLEN      ((uint8)24U)        /* (4 * 6)[byte] */
#define FEE_STARTRECORDPOS      ((uint8)32U)        /* FEE_AREASTATUSLEN + FEE_BLOCKSTATUSLEN */

#define FEE_RECORDMNGINFOLEN    (12U)                   /* The length of one record management information area. */
#define FEE_WRITECHECKPOS       (4U)                    /* The write check position in a record. */
#define FEE_DATASTATUSPOS       (8U)                    /* The data status position in a record. */

#elif (FEE_DATA_FLASH_ECC_FIX_SIZE == FEE_BYTE_NUM_08)

#if (FEE_DATA_FLASH_READ_SIZE == FEE_BYTE_NUM_08)

#define FEE_AREASTATUSLEN       ((uint8)16U)        /* 書き込み単位（2重化) (8 * 2)[byte] */
#define FEE_BLOCKSTATUSLEN      ((uint8)48U)        /* (書き込み単位 * プロックステータスサイズ)（2重化） ((8 * 3 ) * 2 )[byte] */

#define FEE_RECORDMNGINFOLEN    (24U)                   /* The length of one record management information area. */
#define FEE_WRITECHECKPOS       (8U)                    /* The write check position in a record. */
#define FEE_DATASTATUSPOS       (16U)                   /* The data status position in a record. */

#elif (FEE_DATA_FLASH_READ_SIZE == FEE_BYTE_NUM_16)

#define FEE_AREASTATUSLEN       ((uint8)32U)        /* 読み出しバッファ単位（2重化) (16 * 2)[byte] */
#define FEE_BLOCKSTATUSLEN      ((uint8)96U)        /* (読み出しバッファ単位 * プロックステータスサイズ)（2重化） ((16 * 3 ) * 2 )[byte] */

#else
#error "This read unit size isn't supported"
#endif /*FEE_READ_UNIT_SIZE*/

#define FEE_STARTRECORDPOS      ((uint8)(FEE_AREASTATUSLEN + FEE_BLOCKSTATUSLEN))   /* FEE_AREASTATUSLEN + FEE_BLOCKSTATUSLEN */

#else
#error "This unit size isn't supported"
#endif

#if (FEE_WC_DIVIDE_WRITE==STD_ON)
#define FEE_HALFWORD_WRITE_USE  (STD_ON)

#else
#define FEE_HALFWORD_WRITE_USE  (STD_OFF)
#endif

#if ( FEE_DATA_FLASH_BLANK_VAL_TYPE == FEE_DATA_FLASH_BLANK_VAL_TYPE_FF )
#define FEE_DATA_FLASH_BLANK_VAL_UINT1      (0xFFU)
#define FEE_DATA_FLASH_BLANK_VAL_UINT2      (0xFFFFU)
#define FEE_DATA_FLASH_BLANK_VAL_UINT4      (0xFFFFFFFFUL)
#define FEE_DATA_FLASH_IVTBLA_VAL_UINT1     (0x00U)
#define FEE_DATA_FLASH_IVTBLA_VAL_UINT2     (0x0000U)
#define FEE_DATA_FLASH_IVTBLA_VAL_UINT4     (0x00000000UL)

#define FEE_DATA_FLASH_DS_VAL_UINT1_UPPER   (0x11U)
#define FEE_DATA_FLASH_DS_VAL_UINT1_LOWER   (0x00U)

#elif ( FEE_DATA_FLASH_BLANK_VAL_TYPE == FEE_DATA_FLASH_BLANK_VAL_TYPE_00 )
#define FEE_DATA_FLASH_BLANK_VAL_UINT1      (0x00U)
#define FEE_DATA_FLASH_BLANK_VAL_UINT2      (0x0000U)
#define FEE_DATA_FLASH_BLANK_VAL_UINT4      (0x00000000UL)
#define FEE_DATA_FLASH_IVTBLA_VAL_UINT1     (0xFFU)
#define FEE_DATA_FLASH_IVTBLA_VAL_UINT2     (0xFFFFU)
#define FEE_DATA_FLASH_IVTBLA_VAL_UINT4     (0xFFFFFFFFUL)

#define FEE_DATA_FLASH_DS_VAL_UINT1_UPPER   (0xEEU)
#define FEE_DATA_FLASH_DS_VAL_UINT1_LOWER   (0xFFU)

#else /* FEE_DATA_FLASH_BLANK_VAL_TYPE */
#error "The type that the value of data flash in a state of erase is not supported."
#endif /* FEE_DATA_FLASH_BLANK_VAL_TYPE */

/* ブロック番号無効値 */
#define FEE_BLOCKNUM_INVALID        ((uint8)0xFFU)


/* 戻り値共通定義 */
#define FEE_STATUS_OK           ((uint32)0x00000000UL)      /* 正常 */
#define FEE_STATUS_NG           ((uint32)0x00000001UL)      /* 異常 */
#define FEE_STATUS_EXIT         ((uint32)0x00000002UL)      /* 継続処理不可 */
#define FEE_STATUS_DONE         ((uint32)0x00000003UL)      /* 処理完了 */
#define FEE_STATUS_CONT         ((uint32)0x00000004UL)      /* 継続処理可 */
#define FEE_STATUS_BUSY         ((uint32)0x00000005UL)      /* 処理中 */
#define FEE_STATUS_INVALID      ((uint32)0x00000006UL)      /* 無効データあり */
#define FEE_STATUS_NODATA       ((uint32)0x00000007UL)      /* ブロック未使用/データなし */

/* ブロックステータス種別 */
/* 並び順には意味があるため、定義値を変更する場合には、注意すること！ */
/* ブロックステータスデータ確定遷移先判定テーブル（Fee_FixBSJudgeTBL）に影響！ */
/* ブロックステータス判定関数（FEE_JudgeBlockStatus）に影響 */
#define FEE_BS_AREA         ((uint8)0x00U)      /* エリアステータス */
#define FEE_BS_USING        ((uint8)0x01U)      /* 使用中 */
#define FEE_BS_MOVE         ((uint8)0x02U)      /* 転送中 */
#define FEE_BS_USED         ((uint8)0x03U)      /* 使用済 */
#define FEE_BS_UNUSED       ((uint8)0x04U)      /* 未使用 */
#define FEE_BS_ILLEGAL      ((uint8)0x05U)      /* 不正 */
#define FEE_BS_MAX          ((uint8)0x06U)      /* ブロックステータス種別ガード */
#define FEE_BS_INVALID      ((uint8)0xFFU)      /* 無効値 */

/* ブロックステータス確定処理種別 */
#define FEE_BSFIXKIND_NONFIX        (0x00U)     /* 確定必要なし */
#define FEE_BSFIXKIND_FIX1ST        (0x10U)     /* 1個目確定必要あり */
#define FEE_BSFIXKIND_FIX2ND        (0x20U)     /* 2個目確定必要あり */
#define FEE_BSFIXKIND_FIXALL        (0x30U)     /* 両方確定必要あり */

/* write BlockStatus place */
#define FEE_BSWRITE_NOTWRITE        (0x00U)     /* do not need to write */
#define FEE_BSWRITE_MAIN            (0x01U)     /* write main */
#define FEE_BSWRITE_SUB             (0x02U)     /* write sub */
#define FEE_BSWRITE_ALL             (0x03U)     /* write both main and sub */

/* ２重化データ種別 */
#define FEE_DUPLIDATA_1ST       ((uint32)0x00000000UL)      /* 1個目のデータ */
#define FEE_DUPLIDATA_2ND       ((uint32)0x00000001UL)      /* 2個目のデータ */

/* ブロックステータスデータ判定結果 */
/* 並び順には意味があるため、定義値を変更する場合には、注意すること！ */
/* ブロックステータス判定テーブル（Fee_JudgeBSTBL）に影響！ */
#define FEE_BSDATA_ERASE            (0x00U)     /* 消去状態 */
#define FEE_BSDATA_VALID            (0x01U)     /* 0x55AA55AA */
#define FEE_BSDATA_OTHER            (0x02U)     /* 上記以外 */

/* 初期化モード */
#define FEE_INIT_ALL            ((uint8)0x00U)      /* 全エリア */
#define FEE_INIT_ONE            ((uint8)0x01U)      /* 指定エリア */

/* フラグ共通定義 */
#define FEE_FLAG_OFF        ((uint8)0x00U)      /* フラグOFF */
#define FEE_FLAG_ON         ((uint8)0x01U)      /* フラグON */

/* Flag value for continuity writing */
#define FEE_CWFLG_NONE          (0x0000U)           /* Initialize value */
#define FEE_CWFLG_VOLMINCHK     ((uint16)0x0008U)   /* Check voltage */
#define FEE_CWFLG_ERRSTOP       ((uint16)0x0004U)   /* Stop DFC error occured*/
#define FEE_CWFLG_DFCERRCHK     ((uint16)0x0002U)   /* Check DFC error */
#define FEE_CWFLG_VRFYERRCHK    ((uint16)0x0001U)   /* Check verify error */

#if ( FEE_HALFWORD_WRITE_USE == STD_ON ) 
#define FEE_DATA_FLASH_HALF_WRITE_SIZE  (FEE_DATA_FLASH_ECC_FIX_SIZE/2U)
#define FEE_CWOFFSET_HALFWORD           (FEE_DATA_FLASH_HALF_WRITE_SIZE)           /* Write Address Offset Halfword */
#endif /* FEE_HALFWORD_WRITE_USE */ 
#define FEE_CWOFFSET_INVALID            (0xFFFFU)                                  /* Write Address Offset Invalid */
#define FEE_CWOFFSET_ZERO               (0U)                                       /* Write Address Offset Zero */


/* タイマ共通定義 */
#define FEE_TM_INVALID  ((uint32)0xFFFFFFFFUL)      /* タイマ無効値 */

/* レコード関連 */
#define FEE_XFLAGDAT_PHYSICAL_IMAGE           (0x66U)

#define FEE_DATAAREA_REC_TAIL_OFFSET        ( FEE_DFLASH_FORMAT_XFLAG_SIZE ) /* The position of a data area record. */

#define FEE_RECORD_FORMAT_OFFSET_ID           (0U)                  /* Offset from beginning of buffer record（number of bytes）： ID        */
#define FEE_RECORD_FORMAT_OFFSET_DATAADDR     (2U)                  /* Data address position */

#if (FEE_ENDIAN == FEE_ENDIAN_BIG)
#define FEE_RECORD_FORMAT_OFFSET_ID_MSBYTE          (0U)    /* Offset from beginning of buffer record（number of bytes）： ID most significant byte */
#define FEE_RECORD_FORMAT_OFFSET_ID_LSBYTE          (1U)    /* Offset from beginning of buffer record（number of bytes）： ID least significant byte */
#define FEE_RECORD_FORMAT_OFFSET_DATAADDR_MSBYTE    (2U)    /* Offset from beginning of buffer record（number of bytes）： DATA ADDR most significant byte */
#define FEE_RECORD_FORMAT_OFFSET_DATAADDR_LSBYTE    (3U)    /* Offset from beginning of buffer record（number of bytes）： DATA ADDR least significant byte */
#define FEE_RECORD_FORMAT_OFFSET_CS_MSBYTE_INDEX_0  (FEE_DFLASH_ONE_TIME_WRITE_SIZE - FEE_RECORD_SIZE_CHECKSUM)              /* Offset from beginning of buffer record（number of bytes）： CS 1st byte */
#define FEE_RECORD_FORMAT_OFFSET_CS_MSBYTE_INDEX_1  ( ( FEE_DFLASH_ONE_TIME_WRITE_SIZE - FEE_RECORD_SIZE_CHECKSUM ) + 1U)    /* Offset from beginning of buffer record（number of bytes）： CS 2nd byte */
#define FEE_RECORD_FORMAT_OFFSET_CS_MSBYTE_INDEX_2  ( ( FEE_DFLASH_ONE_TIME_WRITE_SIZE - FEE_RECORD_SIZE_CHECKSUM ) + 2U)    /* Offset from beginning of buffer record（number of bytes）： CS 3rd byte */
#define FEE_RECORD_FORMAT_OFFSET_CS_MSBYTE_INDEX_3  ( ( FEE_DFLASH_ONE_TIME_WRITE_SIZE - FEE_RECORD_SIZE_CHECKSUM ) + 3U)    /* Offset from beginning of buffer record（number of bytes）： CS 4th byte */

#elif (FEE_ENDIAN == FEE_ENDIAN_LITTLE)
#define FEE_RECORD_FORMAT_OFFSET_ID_MSBYTE          (1U)    /* Offset from beginning of buffer record（number of bytes）： ID most significant byte */
#define FEE_RECORD_FORMAT_OFFSET_ID_LSBYTE          (0U)    /* Offset from beginning of buffer record（number of bytes）： ID least significant byte */
#define FEE_RECORD_FORMAT_OFFSET_DATAADDR_MSBYTE    (3U)    /* Offset from beginning of buffer record（number of bytes）： DATA ADDR most significant byte */
#define FEE_RECORD_FORMAT_OFFSET_DATAADDR_LSBYTE    (2U)    /* Offset from beginning of buffer record（number of bytes）： DATA ADDR least significant byte */
#define FEE_RECORD_FORMAT_OFFSET_CS_MSBYTE_INDEX_0  ( ( FEE_DFLASH_ONE_TIME_WRITE_SIZE - FEE_RECORD_SIZE_CHECKSUM ) + 3U)    /* Offset from beginning of buffer record（number of bytes）： CS 1st byte */
#define FEE_RECORD_FORMAT_OFFSET_CS_MSBYTE_INDEX_1  ( ( FEE_DFLASH_ONE_TIME_WRITE_SIZE - FEE_RECORD_SIZE_CHECKSUM ) + 2U)    /* Offset from beginning of buffer record（number of bytes）： CS 2nd byte */
#define FEE_RECORD_FORMAT_OFFSET_CS_MSBYTE_INDEX_2  ( ( FEE_DFLASH_ONE_TIME_WRITE_SIZE - FEE_RECORD_SIZE_CHECKSUM ) + 1U)    /* Offset from beginning of buffer record（number of bytes）： CS 3rd byte */
#define FEE_RECORD_FORMAT_OFFSET_CS_MSBYTE_INDEX_3  (FEE_DFLASH_ONE_TIME_WRITE_SIZE - FEE_RECORD_SIZE_CHECKSUM)              /* Offset from beginning of buffer record（number of bytes）： CS 4th byte */

#else
/*"This endian isn't supported"*/
#endif

#define FEE_RECORD_SIZE_BLOCKNUM            (2U)    /* The size of block number. */
#define FEE_RECORD_SIZE_DATAADDR            (2U)    /* The size of data address. */
#define FEE_RECORD_SIZE_BLOCKNUM_DATAADDR   (FEE_RECORD_SIZE_BLOCKNUM + FEE_RECORD_SIZE_DATAADDR)
#define FEE_RECORD_SIZE_CHECKSUM            (4U)    /* The size of check sum. */

#define FEE_RECORD_PADDING_VAL              (0x00U)

#define FEE_CHECKSUM_UNLOCK_VAL             (0xC0000000U)

/* 共通 */
#define FEE_BIT0                    ((uint32)0x00000001U)           /* BIT0 */
#define FEE_UPPER4BIT               (0xF0U)                 /* 上位4bitマスク */
#define FEE_LOWER4BIT               (0x0FU)                 /* 下位4bitマスク */

/* アドレス無効値 */
#define FEE_ADDRESS_INVALID     ((uint32)0xFFFFFFFFU)

/* 動作状態 */
#define FEE_STATUSIDLE                  ((uint8)0x00U)      /* アイドル */
#define FEE_STATUSWRITE                 ((uint8)0x01U)      /* 書込み中 */
#define FEE_STATUSMOVE                  ((uint8)0x02U)      /* データ再編中 */
#define FEE_STATUSIDREAD                ((uint8)0x03U)      /* ID指定読出し中 */
#define FEE_STATUSMAX                   ((uint8)0x04U)      /* 状態ガード */

/* メイン状態 */
#define FEE_MSTATUSWBIDLE               ((uint8)0x10U)      /* 書込み中－アイドル */
#define FEE_MSTATUSWBSEL                ((uint8)0x11U)      /* 書込み中－ブロック選択中 */
#define FEE_MSTATUSWBMOVE               ((uint8)0x12U)      /* 書込み中－データ転送中 */
#define FEE_MSTATUSWBWRITE              ((uint8)0x13U)      /* 書込み中－レコード書込み中 */
#define FEE_MSTATUSRIDLE                ((uint8)0x30U)      /* ID指定読出し中－アイドル */
#define FEE_MSTATUSRBSRCH               ((uint8)0x31U)      /* ID指定読出し中－空き領域検索中 */
#define FEE_MSTATUSRPREPISRCH           ((uint8)0x32U)      /* ID指定読出し中－ID指定データ読出し準備中 */
#define FEE_MSTATUSRISRCH               ((uint8)0x33U)      /* ID指定読出し中－ID指定データ読出し中 */
#define FEE_MSTATUSINVALID              ((uint8)0xFFU)      /* 無効値 */

/* サブ状態 */
#define FEE_SSTATUSWSIDLE               ((uint8)0x10U)      /* ブロック選択中－アイドル(未使用) */
#define FEE_SSTATUSWSFIX                ((uint8)0x11U)      /* ブロック選択中－ブロックステータスデータ確定中 */
#define FEE_SSTATUSWSUSG                ((uint8)0x12U)      /* ブロック選択中－使用中ブロック作成中 */
#define FEE_SSTATUSWSMOV                ((uint8)0x13U)      /* ブロック選択中－転送中ブロック作成中 */
#define FEE_SSTATUSWSWEMOV              ((uint8)0x14U)      /* ブロック選択中－再編終了設定中 */
#define FEE_SSTATUSWSALLU               ((uint8)0x15U)      /* ブロック選択中－エリア無効・使用済設定中 */
#define FEE_SSTATUSWSFAIL               ((uint8)0x16U)      /* ブロック選択中－使用済・故障設定中 */
#define FEE_SSTATUSWMIDLE               ((uint8)0x20U)      /* データ転送中－アイドル */
#define FEE_SSTATUSWMSRCHMPS            ((uint8)0x21U)      /* データ転送中－転送元最終データ位置検索中 */
#define FEE_SSTATUSWMPREPSRCHMDT        ((uint8)0x22U)      /* データ転送中－転送元データ検索準備中 */
#define FEE_SSTATUSWMSRCHMDT            ((uint8)0x23U)      /* データ転送中－転送元データ検索中 */
#define FEE_SSTATUSWMPREPSRCHSDT        ((uint8)0x24U)      /* データ転送中－転送先データ検索準備中 */
#define FEE_SSTATUSWMSRCHSDT            ((uint8)0x25U)      /* データ転送中－転送先データ検索中 */
#define FEE_SSTATUSWMWRITE              ((uint8)0x26U)      /* データ転送中－データ書き込み中 */
#define FEE_SSTATUSWWIDLE               ((uint8)0x30U)      /* レコード書込み中－アイドル */
#define FEE_SSTATUSWWSRCHPOSMNG         ((uint8)0x31U)      /* レコード書込み中－書込みレコード位置(管理情報)検索中 */
#define FEE_SSTATUSWWSTARTSRCHPOSDAT    ((uint8)0x32U)      /* レコード書込み中－書込みレコード位置(データ)検索開始 */
#define FEE_SSTATUSWWSRCHPOSDAT         ((uint8)0x33U)      /* レコード書込み中－書込みレコード位置(データ)検索中 */
#define FEE_SSTATUSWWPREPSRCHOLD        ((uint8)0x34U)      /* レコード書込み中－旧データ検索準備中 */
#define FEE_SSTATUSWWSRCHOLD            ((uint8)0x35U)      /* レコード書込み中－旧データ検索中 */
#define FEE_SSTATUSWWWRITE              ((uint8)0x36U)      /* レコード書込み中－データ書き込み中 */
#define FEE_SSTATUSINVALID              ((uint8)0xFFU)      /* 無効値 */

/* サブサブ状態 */
#define FEE_SSSTATUSWSUIDLE             ((uint8)0x20U)      /* 使用中ブロック作成中－アイドル(未使用) */
#define FEE_SSSTATUSWSUWERSG            ((uint8)0x21U)      /* 使用中ブロック作成中－消去待ち */
#define FEE_SSSTATUSWSUWUSG             ((uint8)0x22U)      /* 使用中ブロック作成中－使用中設定待ち */
#define FEE_SSSTATUSWSUERSG             ((uint8)0x23U)      /* 使用中ブロック作成中－消去中 */
#define FEE_SSSTATUSWSUUSG              ((uint8)0x24U)      /* 使用中ブロック作成中－使用中設定中 */
#define FEE_SSSTATUSWSMIDLE             ((uint8)0x30U)      /* 転送中ブロック作成中－アイドル(未使用) */
#define FEE_SSSTATUSWSMWMOVE            ((uint8)0x31U)      /* 転送中ブロック作成中－転送中設定待ち */
#define FEE_SSSTATUSWSMWUSD             ((uint8)0x32U)      /* 転送中ブロック作成中－使用済設定待ち */
#define FEE_SSSTATUSWSMWERSG            ((uint8)0x33U)      /* 転送中ブロック作成中－消去待ち */
#define FEE_SSSTATUSWSMMOVE             ((uint8)0x34U)      /* 転送中ブロック作成中－転送中設定中 */
#define FEE_SSSTATUSWSMUSD              ((uint8)0x35U)      /* 転送中ブロック作成中－使用済設定中 */
#define FEE_SSSTATUSWSMERSG             ((uint8)0x36U)      /* 転送中ブロック作成中－消去中 */
#define FEE_SSSTATUSWSEIDLE             ((uint8)0x40U)      /* 再編終了設定中－アイドル */
#define FEE_SSSTATUSWSEUSG              ((uint8)0x41U)      /* 再編終了設定中－使用中設定中 */
#define FEE_SSSTATUSWSEUSD              ((uint8)0x42U)      /* 再編終了設定中－使用済設定中 */
#define FEE_SSSTATUSWSAIDLE             ((uint8)0x50U)      /* エリア無効・使用済設定中－アイドル */
#define FEE_SSSTATUSWSASET              ((uint8)0x51U)      /* エリア無効・使用済設定中－設定中 */
#define FEE_SSSTATUSWSFIDLE             ((uint8)0x60U)      /* 使用済・故障設定中－アイドル(未使用) */
#define FEE_SSSTATUSWSFWMUSD            ((uint8)0x61U)      /* 使用済・故障設定中－メインブロック使用済設定待ち */
#define FEE_SSSTATUSWSFWSUSD            ((uint8)0x62U)      /* 使用済・故障設定中－サブブロック使用済設定待ち */
#define FEE_SSSTATUSWSFWMF              ((uint8)0x63U)      /* 使用済・故障設定中－メインブロック故障設定待ち */
#define FEE_SSSTATUSWSFWSF              ((uint8)0x64U)      /* 使用済・故障設定中－サブブロック故障設定待ち */
#define FEE_SSSTATUSWSFSET              ((uint8)0x65U)      /* 使用済・故障設定中－設定中 */

#define FEE_SSSTATUSINVALID     ((uint8)0xFFU)      /* 無効値 */

/* バッファ初期化用データ */
#define FEE_INIDAT_UINT8                ((uint8)FEE_DATA_FLASH_BLANK_VAL_UINT1)
#define FEE_INIDAT_UINT32               ((uint32)FEE_DATA_FLASH_BLANK_VAL_UINT4)
#define FEE_INIDAT_UINT16               ((uint16)FEE_DATA_FLASH_BLANK_VAL_UINT2)

/* WC 書き込みデータ */
#if (FEE_ENDIAN == FEE_ENDIAN_BIG)
#define FEE_WCDAT_PHYSICAL_IMAGE_UPPER  ((uint8)0xAAU)
#define FEE_WCDAT_PHYSICAL_IMAGE_LOWER  ((uint8)0xAAU)

#elif (FEE_ENDIAN == FEE_ENDIAN_LITTLE)
#define FEE_WCDAT_PHYSICAL_IMAGE_UPPER  ((uint8)0xAAU)
#define FEE_WCDAT_PHYSICAL_IMAGE_LOWER  ((uint8)0xAAU)

#else
/*"This endian isn't supported"*/
#endif

/* DATA-STATUS書き込みデータ */
#if (FEE_ENDIAN == FEE_ENDIAN_BIG)
#define FEE_DSDAT_PHYSICAL_IMAGE_UPPER  ((uint8)FEE_DATA_FLASH_DS_VAL_UINT1_UPPER)
#define FEE_DSDAT_PHYSICAL_IMAGE_LOWER  ((uint8)FEE_DATA_FLASH_DS_VAL_UINT1_LOWER)

#elif (FEE_ENDIAN == FEE_ENDIAN_LITTLE)
#define FEE_DSDAT_PHYSICAL_IMAGE_UPPER ((uint8)FEE_DATA_FLASH_DS_VAL_UINT1_LOWER)
#define FEE_DSDAT_PHYSICAL_IMAGE_LOWER ((uint8)FEE_DATA_FLASH_DS_VAL_UINT1_UPPER)

#else
/*"This endian isn't supported"*/
#endif

/* BS初期ステータスデータ */
#if (FEE_ENDIAN == FEE_ENDIAN_BIG)
#define FEE_BSDAT_PHYSICAL_IMAGE_UPPER  ((uint8)0x55U)
#define FEE_BSDAT_PHYSICAL_IMAGE_LOWER  ((uint8)0xAAU)

#elif (FEE_ENDIAN == FEE_ENDIAN_LITTLE)
#define FEE_BSDAT_PHYSICAL_IMAGE_UPPER  ((uint8)0xAAU)
#define FEE_BSDAT_PHYSICAL_IMAGE_LOWER  ((uint8)0x55U)

#else
/*"This endian isn't supported"*/
#endif

#define FEE_DFLASH_FORMAT_BS_MAX_SIZE          (8U)
#define FEE_DFLASH_FORMAT_WC_MAX_SIZE          (8U)
#define FEE_DFLASH_FORMAT_DS_MAX_SIZE          (8U)
#define FEE_DFLASH_FORMAT_XFLAG_MAX_SIZE       (8U)


#define FEE_AREANUM_INVALID (0xFFU)         /* エリア番号無効値 */

#define FEE_SRCH_REMAIN_COUNT_ZERO  (0)     /* 検索処理可能回数0 */

/* 配列インデックス番号 */
#define FEE_ARRAY_INDEX_00  (0U)
#define FEE_ARRAY_INDEX_01  (1U)

#if (FEE_ENDIAN == FEE_ENDIAN_BIG)
#define FEE_UINT16_MSBYTE_INDEX_0  (0U)
#define FEE_UINT16_MSBYTE_INDEX_1  (1U)

#define FEE_UINT32_MSBYTE_INDEX_0  (0U)
#define FEE_UINT32_MSBYTE_INDEX_1  (1U)
#define FEE_UINT32_MSBYTE_INDEX_2  (2U)
#define FEE_UINT32_MSBYTE_INDEX_3  (3U)

#elif (FEE_ENDIAN == FEE_ENDIAN_LITTLE)
#define FEE_UINT16_MSBYTE_INDEX_0  (1U)
#define FEE_UINT16_MSBYTE_INDEX_1  (0U)

#define FEE_UINT32_MSBYTE_INDEX_0  (3U)
#define FEE_UINT32_MSBYTE_INDEX_1  (2U)
#define FEE_UINT32_MSBYTE_INDEX_2  (1U)
#define FEE_UINT32_MSBYTE_INDEX_3  (0U)

#else
/*"This endian isn't supported"*/
#endif

#define FEE_BLKSTARTADDRTBL Fee_Mpu_Cau4SectorTopAddresse
#define FEE_READ_UNIT_SIZE      FEE_DATA_FLASH_READ_SIZE

#define FEE_DFAI_RW_SIZE_MAX      (64U)


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* データFlash制御管理データ構造体 */
typedef struct {
    uint8   u1MngDFCStatus;                     /* データFlash制御状態 */
    uint8   u1CWriteIndex;                      /* 連続書込み用バッファのインデックス */
    uint8   u1CWriteNum;                        /* 連続書込みデータ数 */
    uint8   u1RetryFlag;                        /* Flag for retrying to write */
    uint16  u2CWriteDataLength[FEE_CWRITE_MAX]; /* WriteData Length */
    uint16  u2CWriteAddrOffset[FEE_CWRITE_MAX]; /* WriteAddr Offset */
    uint16  u2CWriteFlag[FEE_CWRITE_MAX];       /* 連続書込み用フラグ */
    uint32  u4CWriteAddrBuf[FEE_CWRITE_MAX];    /* 連続書込み用アドレスバッファ */
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) ptu1CWriteDataAddr[FEE_CWRITE_MAX];
} Fee_MngDfcInfType;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

/* 応答Hook呼び出し共通処理 */
FUNC(void, FEE_CODE) Fee_RspHook( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo);

/* データ書込み状態管理（ブロック管理機能あり） */
FUNC(uint32, FEE_CODE) Fee_BWriteMain( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );

/* ID指定データ読出し状態管理 */
FUNC(uint32, FEE_CODE) Fee_ReadMain( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );

/* データ転送状態管理 */
FUNC(uint32, FEE_CODE) Fee_MoveData( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );

FUNC( void, FEE_CODE )
Fee_Driver_Init( void );

FUNC( Std_ReturnType, FEE_CODE )
Fee_Driver_Cancel( void );

FUNC( void, FEE_CODE )
Fee_Driver_AbortDfc( void );

FUNC( void, FEE_CODE )
Fee_Driver_AsyncCancel( void );

FUNC( void, FEE_CODE )
Fee_Driver_AsyncAbort( void );

FUNC( boolean, FEE_CODE )
Fee_Driver_IsWaitingForCancel( void );

/* データFlash定期処理実行命令 */
FUNC(void, FEE_CODE) Fee_ExecPeriodic( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );

/* 使用エリア選択 */
FUNC(void, FEE_CODE) Fee_SelectUseArea( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );

/* 書込みブロック選択状態管理 */
FUNC(uint32, FEE_CODE) Fee_SelectWriteBlock( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );

FUNC(void, FEE_CODE) Fee_WriteBlockStatus(
    uint8 u1BlockNo,
    uint32 u4BSDataKind,
    uint8 u1WritePlace
);

/* 読出しブロック選択 */
FUNC(uint32, FEE_CODE) Fee_SelectReadBlock( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );

/* 使用中ブロックデータ初期化 */
FUNC(void, FEE_CODE) Fee_ClrUseBlockInfo( void );

FUNC( Std_ReturnType, FEE_CODE )
Fee_Block_CheckUseBlockInfo( void );

FUNC( void, FEE_CODE )
Fee_Block_SetUseBlockInfoSub( void );

#if ( MSCD_FREESPACE_USE == STD_ON )
FUNC( uint32, FEE_CODE )
Fee_Block_GetSectorInfo(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo,
    P2VAR( boolean,        AUTOMATIC, TYPEDEF         ) NeedsToFix
);
#endif /*( MSCD_FREESPACE_USE == STD_ON )*/

FUNC( void, FEE_CODE )
Fee_Record_Init( void );

FUNC( Std_ReturnType, FEE_CODE )
Fee_Record_CheckRAM( void );

FUNC( void, FEE_CODE )
Fee_Record_SetRAMSub( void );

/* 空き領域検索 */
FUNC(uint32, FEE_CODE) Fee_SrchFreeSpace( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );

/* レコード書込み状態管理 */
FUNC(uint32, FEE_CODE) Fee_WriteRecord( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );

FUNC( boolean, FEE_CODE )
Fee_Record_CheckWriteSpace(
    uint16 WriteDataLen,
    uint16 TargetSector,
    P2CONST( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo
);

FUNC( void, FEE_CODE )
Fee_Record_StateWtMvStart(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo
);

FUNC( uint32, FEE_CODE )
Fee_Record_StateWtMvExec(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo
);

FUNC( void, FEE_CODE )
Fee_Record_StateScRdStart( void );

FUNC( uint32, FEE_CODE )
Fee_Record_StateScRdExec(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo, 
    P2VAR( uint32,         AUTOMATIC, TYPEDEF )         DstSrchResult
);

FUNC( void, FEE_CODE )
Fee_Record_StateScMsStart( void );

FUNC( uint32, FEE_CODE )
Fee_Record_StateScMsExec(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo, 
    P2VAR( uint32,         AUTOMATIC, TYPEDEF )         DstSrchResult
);

FUNC( void, FEE_CODE )
Fee_Record_StateScMdStart( void );

FUNC( uint32, FEE_CODE )
Fee_Record_StateScMdExec(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo, 
    P2VAR( uint32,         AUTOMATIC, TYPEDEF )         DstSrchResult
);

FUNC( Std_ReturnType, FEE_CODE )
Fee_MngDfc_CheckRAM( void );

FUNC( void, FEE_CODE )
Fee_MngDfc_SetRAMSub( void );

/* 定期処理用データFlash制御管理 */
FUNC(uint32, FEE_CODE) Fee_MngDfcForPrd( void );

/* 連続書込み用バッファ追加処理 */
FUNC(void, FEE_CODE) Fee_AddCWriteBuf( uint32 u4Address, P2CONST(uint8, AUTOMATIC, TYPEDEF) ptu1Src, uint16 u2Length, uint16 u2OffSet, uint16 u2Flg );

/* 連続書込み開始処理 */
FUNC(void, FEE_CODE) Fee_StartCWrite( void );


/* 消去開始処理 */
FUNC(void, FEE_CODE) Fee_StartErase( uint8 u1BlockNo );

/* ブランクチェック開始処理 */
FUNC(void, FEE_CODE) Fee_StartBlankCheck( uint32 u4StartTailAddress, uint32 u4EndTopAddress );

/* 連続書込み用バッファ初期化処理 */
FUNC(void, FEE_CODE) Fee_ClearCWriteBuf( void );

/* データFlash制御結果取得処理 */
FUNC(uint32, FEE_CODE) Fee_GetMngDfcResult( P2VAR(uint32, AUTOMATIC, TYPEDEF) ptu4Address );

/* MHA[データFlash]管理データ初期化 */
FUNC(void, FEE_CODE) Fee_InitCpuDtfData( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );

/* データセット処理 */
FUNC(void, FEE_CODE) Fee_Lib_SetMemory( P2VAR(uint8, AUTOMATIC, TYPEDEF) DstPtr, uint8 Constant, uint32 Length );

/* 最終書込みレコード位置読出し処理 */
FUNC(uint32, FEE_CODE) Fee_RefLastWritePos( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );

/* 最終書込みレコード位置保存処理 */
FUNC(uint32, FEE_CODE) Fee_SetLastWritePos( P2CONST(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );

/* 最終書込みレコード位置初期化 */
FUNC(void, FEE_CODE) Fee_InitLastWritePos( uint8 u1AreaNum, uint8 u1Mode );

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

#define FEE_START_SEC_CONST_32
#include <Fee_MemMap.h>

extern CONST(uint8, FEE_CONST) Fee_FixWCData[FEE_DFLASH_FORMAT_WC_MAX_SIZE];
extern CONST(uint8, FEE_CONST) Fee_FixDSData[FEE_DFLASH_FORMAT_DS_MAX_SIZE];
extern CONST(uint8, FEE_CONST) Fee_FixBSData[FEE_DFLASH_FORMAT_BS_MAX_SIZE];
extern CONST(uint8, FEE_CONST) Fee_FixXFlagData[FEE_DFLASH_FORMAT_XFLAG_MAX_SIZE];

#define FEE_STOP_SEC_CONST_32
#include <Fee_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* FEE_COMMON_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  1-1-0          :2019/10/09                                              */
/*  2-0-0          :2022/08/24                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
