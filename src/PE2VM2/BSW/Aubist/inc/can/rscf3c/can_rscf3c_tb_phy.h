/* can_rscf3c_tb_phy_h_m10700_v2-2-0                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN/RSCF3C/TB/PHYSICAL/HEADER                             */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     CAN_RSCF3C_TB_PHY_H
#define     CAN_RSCF3C_TB_PHY_H


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* 受信マスク値テーブル要素数 */
#define CAN_TB_RXMKTBLSIZE              ( CAN_CFG_FILTER_MASK_NUM + 2U )

/* MB.DATAアクセス用配列サイズ */
#define CAN_TB_MB_DATA_ARYSIZE          ( 16U )                 /* MB.DATA配列サイズ(64byte用) */

/* 送受信データ関連レジスタ型 予約領域 */
#define CAN_TB_MB_REG_RSV               ( 13U )                 /* 予約領域 004C-007F(4byte * 13) */

/* 受信ルール数 */
#define CAN_TB_MAX_NUMBER_OF_RX_RULE \
    ( CAN_CFG_HRHNUM_0 + CAN_CFG_HRHNUM_1 + CAN_CFG_HRHNUM_2 + CAN_CFG_HRHNUM_3 \
    + CAN_CFG_HRHNUM_4 + CAN_CFG_HRHNUM_5 + CAN_CFG_HRHNUM_6 + CAN_CFG_HRHNUM_7 )

/* 受信ルール設定値テーブル要素数 */
#define CAN_TB_RXRULESETTBLSIZE         ( CAN_TB_MAX_NUMBER_OF_RX_RULE + 1U )


/*-------------------------------------------------*/
/* CmNCFGレジスタ設定値                            */
/*  macro  : CAN_TB_u4CmNCFG( ptn )                */
/*  param1 : CAN_CFG_CONTROLLER_BAUDRATE_# 設定値  */
/*-------------------------------------------------*/
/* 通信設定                    */
/* Phase Seg 2 */
#define CAN_TB_PSG2_125K_2M_PTN1            (  4UL )
#define CAN_TB_PSG2_125K_2P5M_PTN1          (  5UL )
#define CAN_TB_PSG2_250K_4M_PTN1            (  4UL )
#define CAN_TB_PSG2_250K_4M_PTN2            (  2UL )
#define CAN_TB_PSG2_250K_5M_PTN1            (  5UL )
#define CAN_TB_PSG2_250K_5M_PTN2            (  3UL )
#define CAN_TB_PSG2_500K_8M_PTN1            (  3UL )
#define CAN_TB_PSG2_500K_8M_PTN2            (  3UL )
#define CAN_TB_PSG2_500K_8M_PTN3            (  4UL )
#define CAN_TB_PSG2_500K_8M_PTN4            (  4UL )
#define CAN_TB_PSG2_500K_8M_PTN5            (  2UL )
#define CAN_TB_PSG2_500K_10M_PTN1           (  5UL )
#define CAN_TB_PSG2_500K_10M_PTN2           (  4UL )
#define CAN_TB_PSG2_500K_10M_PTN3           (  4UL )
#define CAN_TB_PSG2_500K_10M_PTN4           (  3UL )
#define CAN_TB_PSG2_500K_10M_PTN5           (  3UL )
#define CAN_TB_PSG2_500K_20M_PTN1           (  8UL )
#define CAN_TB_PSG2_500K_32M_PTN1           ( 12UL )
#define CAN_TB_PSG2_500K_40M_PTN1           ( 16UL )
#define CAN_TB_PSG2_500K_40M_PTN2           ( 16UL )
#define CAN_TB_PSG2_500K_80M_PTN1           ( 32UL )

/* Prop Seg + Phase Seg1 */
#define CAN_TB_PRP_PSG1_125K_2M_PTN1        (  11UL )
#define CAN_TB_PRP_PSG1_125K_2P5M_PTN1      (  14UL )
#define CAN_TB_PRP_PSG1_250K_4M_PTN1        (  11UL )
#define CAN_TB_PRP_PSG1_250K_4M_PTN2        (  13UL )
#define CAN_TB_PRP_PSG1_250K_5M_PTN1        (  14UL )
#define CAN_TB_PRP_PSG1_250K_5M_PTN2        (  16UL )
#define CAN_TB_PRP_PSG1_500K_8M_PTN1        (  12UL )
#define CAN_TB_PRP_PSG1_500K_8M_PTN2        (  12UL )
#define CAN_TB_PRP_PSG1_500K_8M_PTN3        (  11UL )
#define CAN_TB_PRP_PSG1_500K_8M_PTN4        (  11UL )
#define CAN_TB_PRP_PSG1_500K_8M_PTN5        (  13UL )
#define CAN_TB_PRP_PSG1_500K_10M_PTN1       (  14UL )
#define CAN_TB_PRP_PSG1_500K_10M_PTN2       (  15UL )
#define CAN_TB_PRP_PSG1_500K_10M_PTN3       (  15UL )
#define CAN_TB_PRP_PSG1_500K_10M_PTN4       (  16UL )
#define CAN_TB_PRP_PSG1_500K_10M_PTN5       (  16UL )
#define CAN_TB_PRP_PSG1_500K_20M_PTN1       (  31UL )
#define CAN_TB_PRP_PSG1_500K_32M_PTN1       (  51UL )
#define CAN_TB_PRP_PSG1_500K_40M_PTN1       (  63UL )
#define CAN_TB_PRP_PSG1_500K_40M_PTN2       (  63UL )
#define CAN_TB_PRP_PSG1_500K_80M_PTN1       ( 127UL )

/* SJW */
#define CAN_TB_SJW_125K_2M_PTN1             (  4UL )
#define CAN_TB_SJW_125K_2P5M_PTN1           (  4UL )
#define CAN_TB_SJW_250K_4M_PTN1             (  4UL )
#define CAN_TB_SJW_250K_4M_PTN2             (  1UL )
#define CAN_TB_SJW_250K_5M_PTN1             (  4UL )
#define CAN_TB_SJW_250K_5M_PTN2             (  1UL )
#define CAN_TB_SJW_500K_8M_PTN1             (  2UL )
#define CAN_TB_SJW_500K_8M_PTN2             (  3UL )
#define CAN_TB_SJW_500K_8M_PTN3             (  2UL )
#define CAN_TB_SJW_500K_8M_PTN4             (  4UL )
#define CAN_TB_SJW_500K_8M_PTN5             (  1UL )
#define CAN_TB_SJW_500K_10M_PTN1            (  2UL )
#define CAN_TB_SJW_500K_10M_PTN2            (  3UL )
#define CAN_TB_SJW_500K_10M_PTN3            (  4UL )
#define CAN_TB_SJW_500K_10M_PTN4            (  2UL )
#define CAN_TB_SJW_500K_10M_PTN5            (  1UL )
#define CAN_TB_SJW_500K_20M_PTN1            (  5UL )
#define CAN_TB_SJW_500K_32M_PTN1            (  7UL )
#define CAN_TB_SJW_500K_40M_PTN1            (  8UL )
#define CAN_TB_SJW_500K_40M_PTN2            ( 16UL )
#define CAN_TB_SJW_500K_80M_PTN1            ( 32UL )

/* CANクロック周波数(KHz) */
/* ※ コーディング規約考慮 小数の使用を回避するためKHz値で保持 */
#define CAN_TB_CLK_FRQ_125K_2M_PTN1         (  2000UL )
#define CAN_TB_CLK_FRQ_125K_2P5M_PTN1       (  2500UL )
#define CAN_TB_CLK_FRQ_250K_4M_PTN1         (  4000UL )
#define CAN_TB_CLK_FRQ_250K_4M_PTN2         (  4000UL )
#define CAN_TB_CLK_FRQ_250K_5M_PTN1         (  5000UL )
#define CAN_TB_CLK_FRQ_250K_5M_PTN2         (  5000UL )
#define CAN_TB_CLK_FRQ_500K_8M_PTN1         (  8000UL )
#define CAN_TB_CLK_FRQ_500K_8M_PTN2         (  8000UL )
#define CAN_TB_CLK_FRQ_500K_8M_PTN3         (  8000UL )
#define CAN_TB_CLK_FRQ_500K_8M_PTN4         (  8000UL )
#define CAN_TB_CLK_FRQ_500K_8M_PTN5         (  8000UL )
#define CAN_TB_CLK_FRQ_500K_10M_PTN1        ( 10000UL )
#define CAN_TB_CLK_FRQ_500K_10M_PTN2        ( 10000UL )
#define CAN_TB_CLK_FRQ_500K_10M_PTN3        ( 10000UL )
#define CAN_TB_CLK_FRQ_500K_10M_PTN4        ( 10000UL )
#define CAN_TB_CLK_FRQ_500K_10M_PTN5        ( 10000UL )
#define CAN_TB_CLK_FRQ_500K_20M_PTN1        ( 20000UL )
#define CAN_TB_CLK_FRQ_500K_32M_PTN1        ( 32000UL )
#define CAN_TB_CLK_FRQ_500K_40M_PTN1        ( 40000UL )
#define CAN_TB_CLK_FRQ_500K_40M_PTN2        ( 40000UL )
#define CAN_TB_CLK_FRQ_500K_80M_PTN1        ( 80000UL )
#define CAN_TB_CLK_FRQ( ptn )               ( CAN_TB_CLK_FRQ_##ptn )

/* ボーレート計算用クロック(KHz) */
#define CAN_TB_CAN_CLK_KHZ                  ( (uint32)CAN_CFG_BAUDRATE_CLK * 1000UL )

/* ボーレートクロック生成可否チェック                                          */
/* ※ プリプロ処理でのみ使用する前提で剰余算利用                               */
/* ※ 当該マイコンにおけるCAN供給クロックから、CANクロック周波数が生成できるか */
/*    (割り切れるか)を応答する。                                               */
#define CAN_TB_BAUDRATE_DISABLE             ( 0U )
#define CAN_TB_BAUDRATE_ENABLE              ( 1U )
#define CAN_TB_CHK_BAUDRATE_CLK_ENABLE( ptn ) \
    ( ( ( CAN_TB_CAN_CLK_KHZ % CAN_TB_CLK_FRQ( ptn ) ) == 0UL ) ? CAN_TB_BAUDRATE_ENABLE : CAN_TB_BAUDRATE_DISABLE )

/* CmNCFG.NBRP[9:0] : fCAN[kHz] / CANクロック周波数[KHz] - 1 */
/* ※ プリプロ処理でのみ使用する前提で除算利用                                                */
/* ※ コンフィグ制約を設ける事で、割り切れないパターンはそもそも指定されないことを前提とする。*/
/*    ボーレートクロックが生成できない場合ダミー値 ALL 0を応答。                              */

/* コーディング規約対応のため、0-1の演算が発生しないように一度1以上の値を生成し、最後に1引く */
#define CAN_TB_u4CmNCFG_BRP_PLUS1( ptn ) \
    ( ( CAN_TB_CHK_BAUDRATE_CLK_ENABLE( ptn ) == CAN_TB_BAUDRATE_ENABLE ) ? (uint32)( CAN_TB_CAN_CLK_KHZ / CAN_TB_CLK_FRQ( ptn ) ) : 1UL )
#define CAN_TB_u4CmNCFG_BRP( ptn )          ( CAN_TB_u4CmNCFG_BRP_PLUS1( ptn ) - 1UL )

/* CmNCFG.NTSEG1[6:0] : Prop_Seg + Phase_Seg1 - 1 */
/* ※ コンフィグ制約を設ける事で、割り切れないパターンはそもそも指定されないことを前提とする。*/
/*    ボーレートクロックが生成できない場合ダミー値 ALL 0を応答。                              */
#define CAN_TB_u4CmNCFG_TSEG1( ptn ) \
    ( ( CAN_TB_CHK_BAUDRATE_CLK_ENABLE( ptn ) == CAN_TB_BAUDRATE_ENABLE ) ? (uint32)( (uint32)CAN_TB_PRP_PSG1_##ptn - 1UL ) : 0UL )

/* CmNCFG.NTSEG2[4:0] : Phase_Seg2 - 1 */
/* ※ コンフィグ制約を設ける事で、割り切れないパターンはそもそも指定されないことを前提とする。*/
/*    ボーレートクロックが生成できない場合ダミー値 ALL 0を応答。                              */
#define CAN_TB_u4CmNCFG_TSEG2( ptn ) \
    ( ( CAN_TB_CHK_BAUDRATE_CLK_ENABLE( ptn ) == CAN_TB_BAUDRATE_ENABLE ) ? (uint32)( (uint32)CAN_TB_PSG2_##ptn - 1UL ) : 0UL )

/* CmNCFG.NSJW[4:0]   : SJW - 1 */
/* ※ コンフィグ制約を設ける事で、割り切れないパターンはそもそも指定されないことを前提とする。*/
/*    ボーレートクロックが生成できない場合ダミー値 ALL 0を応答。                              */
#define CAN_TB_u4CmNCFG_SJW( ptn ) \
    ( ( CAN_TB_CHK_BAUDRATE_CLK_ENABLE( ptn )  == CAN_TB_BAUDRATE_ENABLE ) ? (uint32)( (uint32)CAN_TB_SJW_##ptn - 1UL ) : 0UL )

/* 各設定ビット位置 */
#define CAN_TB_CmNCFG_SFT_SJW               ( 11U )
#define CAN_TB_CmNCFG_SFT_TSEG2             ( 24U )
#define CAN_TB_CmNCFG_SFT_TSEG1             ( 16U )
#define CAN_TB_CmNCFG_SFT_BRP               (  0U )
/* 各設定ビットマスク */
#define CAN_TB_u4CmNCFG_BIT_SJW             ( 0x0000F800UL )
#define CAN_TB_u4CmNCFG_BIT_TSEG2           ( 0x1F000000UL )
#define CAN_TB_u4CmNCFG_BIT_TSEG1           ( 0x007F0000UL )
#define CAN_TB_u4CmNCFG_BIT_BRP             ( 0x000003FFUL )

/* CmNCFGレジスタ設定値算出                                   */
/*     CAN_TB_CAN_CLK_KHZ = 40000(40MHz)の場合                */
/*     クラシカルCANモード時                                  */
/*       0x033A0013 : CAN_TB_u4CmNCFG(125K_2M_PTN1)           */
/*       0x034D000F : CAN_TB_u4CmNCFG(125K_2P5M_PTN1)         */
/*       0x033A0009 : CAN_TB_u4CmNCFG(250K_4M_PTN1)           */
/*       0x001C0009 : CAN_TB_u4CmNCFG(250K_4M_PTN2)           */
/*       0x034D0007 : CAN_TB_u4CmNCFG(250K_5M_PTN1)           */
/*       0x002F0007 : CAN_TB_u4CmNCFG(250K_5M_PTN2)           */
/*       0x012B0004 : CAN_TB_u4CmNCFG(500K_8M_PTN1)           */
/*       0x022B0004 : CAN_TB_u4CmNCFG(500K_8M_PTN2)           */
/*       0x013A0004 : CAN_TB_u4CmNCFG(500K_8M_PTN3)           */
/*       0x033A0004 : CAN_TB_u4CmNCFG(500K_8M_PTN4)           */
/*       0x001C0004 : CAN_TB_u4CmNCFG(500K_8M_PTN5)           */
/*       0x014D0003 : CAN_TB_u4CmNCFG(500K_10M_PTN1)          */
/*       0x023E0003 : CAN_TB_u4CmNCFG(500K_10M_PTN2)          */
/*       0x033E0003 : CAN_TB_u4CmNCFG(500K_10M_PTN3)          */
/*       0x012F0003 : CAN_TB_u4CmNCFG(500K_10M_PTN4)          */
/*       0x002F0003 : CAN_TB_u4CmNCFG(500K_10M_PTN5)          */
/*       0xXXXXXXXX : CAN_TB_u4CmNCFG(500K_20M_PTN1) 使用禁止 */
/*       0xXXXXXXXX : CAN_TB_u4CmNCFG(500K_32M_PTN1) 使用禁止 */
/*       0xXXXXXXXX : CAN_TB_u4CmNCFG(500K_40M_PTN1) 使用禁止 */
/*       0xXXXXXXXX : CAN_TB_u4CmNCFG(500K_40M_PTN2) 使用禁止 */
/*       0xXXXXXXXX : CAN_TB_u4CmNCFG(500K_80M_PTN1) 使用禁止 */
/*     CAN FDモード時                                         */
/*       0x030A1813 : CAN_TB_u4CmNCFG(125K_2M_PTN1)           */
/*       0x040D180F : CAN_TB_u4CmNCFG(125K_2P5M_PTN1)         */
/*       0x030A1809 : CAN_TB_u4CmNCFG(250K_4M_PTN1)           */
/*       0x010C0009 : CAN_TB_u4CmNCFG(250K_4M_PTN2)           */
/*       0x040D1807 : CAN_TB_u4CmNCFG(250K_5M_PTN1)           */
/*       0x020F0007 : CAN_TB_u4CmNCFG(250K_5M_PTN2)           */
/*       0x020B0804 : CAN_TB_u4CmNCFG(500K_8M_PTN1)           */
/*       0x020B1004 : CAN_TB_u4CmNCFG(500K_8M_PTN2)           */
/*       0x030A0804 : CAN_TB_u4CmNCFG(500K_8M_PTN3)           */
/*       0x030A1804 : CAN_TB_u4CmNCFG(500K_8M_PTN4)           */
/*       0x010C0004 : CAN_TB_u4CmNCFG(500K_8M_PTN5)           */
/*       0x040D0803 : CAN_TB_u4CmNCFG(500K_10M_PTN1)          */
/*       0x030E1003 : CAN_TB_u4CmNCFG(500K_10M_PTN2)          */
/*       0x030E1803 : CAN_TB_u4CmNCFG(500K_10M_PTN3)          */
/*       0x020F0803 : CAN_TB_u4CmNCFG(500K_10M_PTN4)          */
/*       0x020F0003 : CAN_TB_u4CmNCFG(500K_10M_PTN5)          */
/*       0x071E2001 : CAN_TB_u4CmNCFG(500K_20M_PTN1)          */
/*       0xXXXXXXXX : CAN_TB_u4CmNCFG(500K_32M_PTN1) 使用禁止 */
/*       0x0F3E3800 : CAN_TB_u4CmNCFG(500K_40M_PTN1)          */
/*       0x0F3E7800 : CAN_TB_u4CmNCFG(500K_40M_PTN2)          */
/*       0xXXXXXXXX : CAN_TB_u4CmNCFG(500K_80M_PTN1) 使用禁止 */

#define CAN_TB_u4CmNCFG( ptn ) \
    ( (((uint32)CAN_TB_u4CmNCFG_BRP( ptn )   << CAN_TB_CmNCFG_SFT_BRP)   & CAN_TB_u4CmNCFG_BIT_BRP   ) \
    | (((uint32)CAN_TB_u4CmNCFG_TSEG1( ptn ) << CAN_TB_CmNCFG_SFT_TSEG1) & CAN_TB_u4CmNCFG_BIT_TSEG1 ) \
    | (((uint32)CAN_TB_u4CmNCFG_TSEG2( ptn ) << CAN_TB_CmNCFG_SFT_TSEG2) & CAN_TB_u4CmNCFG_BIT_TSEG2 ) \
    | (((uint32)CAN_TB_u4CmNCFG_SJW( ptn )   << CAN_TB_CmNCFG_SFT_SJW)   & CAN_TB_u4CmNCFG_BIT_SJW   ) )

#define CAN_TB_USER_BAUDRATE                ( 0xFFFFFFFFUL )
#define CAN_TB_125K_2M_PTN1                 ( CAN_TB_u4CmNCFG( 125K_2M_PTN1 ) )      /* ボーレート：125kbps_2M    ：パターン1 */
#define CAN_TB_125K_2P5M_PTN1               ( CAN_TB_u4CmNCFG( 125K_2P5M_PTN1 ) )    /* ボーレート：125kbps_2.5M  ：パターン1 */
#define CAN_TB_250K_4M_PTN1                 ( CAN_TB_u4CmNCFG( 250K_4M_PTN1 ) )      /* ボーレート：250kbps_4M    ：パターン1 */
#define CAN_TB_250K_4M_PTN2                 ( CAN_TB_u4CmNCFG( 250K_4M_PTN2 ) )      /* ボーレート：250kbps_4M    ：パターン2 */
#define CAN_TB_250K_5M_PTN1                 ( CAN_TB_u4CmNCFG( 250K_5M_PTN1 ) )      /* ボーレート：250kbps_5M    ：パターン1 */
#define CAN_TB_250K_5M_PTN2                 ( CAN_TB_u4CmNCFG( 250K_5M_PTN2 ) )      /* ボーレート：250kbps_5M    ：パターン2 */
#define CAN_TB_500K_8M_PTN1                 ( CAN_TB_u4CmNCFG( 500K_8M_PTN1 ) )      /* ボーレート：500kbps_8M    ：パターン1 */
#define CAN_TB_500K_8M_PTN2                 ( CAN_TB_u4CmNCFG( 500K_8M_PTN2 ) )      /* ボーレート：500kbps_8M    ：パターン2 */
#define CAN_TB_500K_8M_PTN3                 ( CAN_TB_u4CmNCFG( 500K_8M_PTN3 ) )      /* ボーレート：500kbps_8M    ：パターン3 */
#define CAN_TB_500K_8M_PTN4                 ( CAN_TB_u4CmNCFG( 500K_8M_PTN4 ) )      /* ボーレート：500kbps_8M    ：パターン4 */
#define CAN_TB_500K_8M_PTN5                 ( CAN_TB_u4CmNCFG( 500K_8M_PTN5 ) )      /* ボーレート：500kbps_8M    ：パターン5 */
#define CAN_TB_500K_10M_PTN1                ( CAN_TB_u4CmNCFG( 500K_10M_PTN1 ) )     /* ボーレート：500kbps_10M   ：パターン1 */
#define CAN_TB_500K_10M_PTN2                ( CAN_TB_u4CmNCFG( 500K_10M_PTN2 ) )     /* ボーレート：500kbps_10M   ：パターン2 */
#define CAN_TB_500K_10M_PTN3                ( CAN_TB_u4CmNCFG( 500K_10M_PTN3 ) )     /* ボーレート：500kbps_10M   ：パターン3 */
#define CAN_TB_500K_10M_PTN4                ( CAN_TB_u4CmNCFG( 500K_10M_PTN4 ) )     /* ボーレート：500kbps_10M   ：パターン4 */
#define CAN_TB_500K_10M_PTN5                ( CAN_TB_u4CmNCFG( 500K_10M_PTN5 ) )     /* ボーレート：500kbps_10M   ：パターン5 */
#define CAN_TB_500K_20M_PTN1                ( CAN_TB_u4CmNCFG( 500K_20M_PTN1 ) )     /* ボーレート：500kbps_20M   ：パターン1 */
#define CAN_TB_500K_32M_PTN1                ( CAN_TB_u4CmNCFG( 500K_32M_PTN1 ) )     /* ボーレート：500kbps_32M   ：パターン1 */
#define CAN_TB_500K_40M_PTN1                ( CAN_TB_u4CmNCFG( 500K_40M_PTN1 ) )     /* ボーレート：500kbps_40M   ：パターン1 */
#define CAN_TB_500K_40M_PTN2                ( CAN_TB_u4CmNCFG( 500K_40M_PTN2 ) )     /* ボーレート：500kbps_40M   ：パターン2 */
#define CAN_TB_500K_80M_PTN1                ( CAN_TB_u4CmNCFG( 500K_80M_PTN1 ) )     /* ボーレート：500kbps_80M   ：パターン1 */


/*--------------------------------------------------*/
/* CmDCFGレジスタ設定値(CANFDモード用)              */
/*  macro  : CAN_TB_u4CmDCFG( ptn )                 */
/*  param1 : CAN_CFG_CONTROLLER_DBAUDRATE_# 設定値  */
/*--------------------------------------------------*/
/* 通信設定 */
/* Phase Seg 2 */
#define CAN_TB_PSG2_2M_20M_PTN1             (  2UL )
#define CAN_TB_PSG2_2M_32M_PTN1             (  3UL )
#define CAN_TB_PSG2_2M_40M_PTN1             (  4UL )
#define CAN_TB_PSG2_2M_40M_PTN2             (  6UL )
#define CAN_TB_PSG2_2M_80M_PTN1             ( 12UL )

/* Prop Seg + Phase Seg1 */
#define CAN_TB_PRP_PSG1_2M_20M_PTN1         (  7UL )
#define CAN_TB_PRP_PSG1_2M_32M_PTN1         ( 12UL )
#define CAN_TB_PRP_PSG1_2M_40M_PTN1         ( 15UL )
#define CAN_TB_PRP_PSG1_2M_40M_PTN2         ( 13UL )
#define CAN_TB_PRP_PSG1_2M_80M_PTN1         ( 27UL )

/* SJW */
#define CAN_TB_SJW_2M_20M_PTN1              (  2UL )
#define CAN_TB_SJW_2M_32M_PTN1              (  2UL )
#define CAN_TB_SJW_2M_40M_PTN1              (  3UL )
#define CAN_TB_SJW_2M_40M_PTN2              (  6UL )
#define CAN_TB_SJW_2M_80M_PTN1              ( 12UL )

/* CANクロック周波数(KHz) */
/* ※ コーディング規約考慮 小数の使用を回避するためKHz値で保持 */
#define CAN_TB_CLK_FRQ_2M_20M_PTN1          ( 20000UL )
#define CAN_TB_CLK_FRQ_2M_32M_PTN1          ( 32000UL )
#define CAN_TB_CLK_FRQ_2M_40M_PTN1          ( 40000UL )
#define CAN_TB_CLK_FRQ_2M_40M_PTN2          ( 40000UL )
#define CAN_TB_CLK_FRQ_2M_80M_PTN1          ( 80000UL )

/* CmDCFG.DBRP[7:0]   : fCAN[kHz] / CANクロック周波数[KHz] - 1 */
/* ※ プリプロ処理でのみ使用する前提で除算利用                                                */
/* ※ コンフィグ制約を設ける事で、割り切れないパターンはそもそも指定されないことを前提とする。*/
/*    ボーレートクロックが生成できない場合ダミー値 ALL 0を応答。                              */

/* コーディング規約対応のため、0-1の演算が発生しないように一度1以上の値を生成し、最後に1引く */
#define CAN_TB_u4CmDCFG_DBRP_PLUS1( ptn ) \
    ( ( CAN_TB_CHK_BAUDRATE_CLK_ENABLE( ptn ) == CAN_TB_BAUDRATE_ENABLE ) ? (uint32)( CAN_TB_CAN_CLK_KHZ / CAN_TB_CLK_FRQ( ptn ) ) : 1UL )
#define CAN_TB_u4CmDCFG_DBRP( ptn )        ( CAN_TB_u4CmDCFG_DBRP_PLUS1( ptn ) - 1UL )

/* CmDCFG.DTSEG1[3:0] : Prop_Seg + Phase_Seg1 - 1 */
/* ※ コンフィグ制約を設ける事で、割り切れないパターンはそもそも指定されないことを前提とする。*/
/*    ボーレートクロックが生成できない場合ダミー値 ALL 0を応答。                              */
#define CAN_TB_u4CmDCFG_DTSEG1( ptn ) \
    ( ( CAN_TB_CHK_BAUDRATE_CLK_ENABLE( ptn ) == CAN_TB_BAUDRATE_ENABLE ) ? (uint32)( (uint32)CAN_TB_PRP_PSG1_##ptn - 1UL ) : 0UL )

/* CmDCFG.DTSEG2[2:0] : Phase_Seg2 - 1 */
/* ※ コンフィグ制約を設ける事で、割り切れないパターンはそもそも指定されないことを前提とする。*/
/*    ボーレートクロックが生成できない場合ダミー値 ALL 0を応答。                              */
#define CAN_TB_u4CmDCFG_DTSEG2( ptn ) \
    ( ( CAN_TB_CHK_BAUDRATE_CLK_ENABLE( ptn ) == CAN_TB_BAUDRATE_ENABLE ) ? (uint32)( (uint32)CAN_TB_PSG2_##ptn - 1UL ) : 0UL )

/* CmDCFG.DSJW[2:0]   : SJW - 1 */
/* ※ コンフィグ制約を設ける事で、割り切れないパターンはそもそも指定されないことを前提とする。*/
/*    ボーレートクロックが生成できない場合ダミー値 ALL 0を応答。                              */
#define CAN_TB_u4CmDCFG_DSJW( ptn ) \
    ( ( CAN_TB_CHK_BAUDRATE_CLK_ENABLE( ptn )  == CAN_TB_BAUDRATE_ENABLE ) ? (uint32)( (uint32)CAN_TB_SJW_##ptn - 1UL ) : 0UL )

/* 各設定ビット位置 */
#define CAN_TB_CmDCFG_SFT_DSJW              ( 24U )
#define CAN_TB_CmDCFG_SFT_DTSEG2            ( 20U )
#define CAN_TB_CmDCFG_SFT_DTSEG1            ( 16U )
#define CAN_TB_CmDCFG_SFT_DBRP              (  0U )
/* 各設定ビットマスク */
#define CAN_TB_u4CmDCFG_BIT_DSJW            ( 0x07000000UL )
#define CAN_TB_u4CmDCFG_BIT_DTSEG2          ( 0x00700000UL )
#define CAN_TB_u4CmDCFG_BIT_DTSEG1          ( 0x000F0000UL )
#define CAN_TB_u4CmDCFG_BIT_DBRP            ( 0x000000FFUL )

/* CmDCFGレジスタ設定値算出                                   */
/*     CAN_TB_CAN_CLK_KHZ = 40000(40MHz)の場合                */
/*       0x01160001 : CAN_TB_u4CmDCFG(2M_20M_PTN1)            */
/*       0xXXXXXXXX : CAN_TB_u4CmDCFG(2M_32M_PTN1)  使用禁止  */
/*       0x023E0000 : CAN_TB_u4CmDCFG(2M_40M_PTN1)            */
/*       0x055C0000 : CAN_TB_u4CmDCFG(2M_40M_PTN2)            */
/*       0xXXXXXXXX : CAN_TB_u4CmDCFG(2M_80M_PTN1)  使用禁止  */

#define CAN_TB_u4CmDCFG( ptn ) \
    ( (((uint32)CAN_TB_u4CmDCFG_DBRP( ptn )   << CAN_TB_CmDCFG_SFT_DBRP)   & CAN_TB_u4CmDCFG_BIT_DBRP   ) \
    | (((uint32)CAN_TB_u4CmDCFG_DTSEG1( ptn ) << CAN_TB_CmDCFG_SFT_DTSEG1) & CAN_TB_u4CmDCFG_BIT_DTSEG1 ) \
    | (((uint32)CAN_TB_u4CmDCFG_DTSEG2( ptn ) << CAN_TB_CmDCFG_SFT_DTSEG2) & CAN_TB_u4CmDCFG_BIT_DTSEG2 ) \
    | (((uint32)CAN_TB_u4CmDCFG_DSJW( ptn )   << CAN_TB_CmDCFG_SFT_DSJW)   & CAN_TB_u4CmDCFG_BIT_DSJW   ) )

#define CAN_TB_USER_DATABAUDRATE            ( 0xFFFFFFFFUL )
#define CAN_TB_DB_125K_2M_PTN1              ( CAN_TB_u4CmDCFG( 125K_2M_PTN1   ) )   /* ボーレート：125kbps_2M    ：パターン1 */
#define CAN_TB_DB_125K_2P5M_PTN1            ( CAN_TB_u4CmDCFG( 125K_2P5M_PTN1 ) )   /* ボーレート：125kbps_2.5M  ：パターン1 */
#define CAN_TB_DB_250K_4M_PTN1              ( CAN_TB_u4CmDCFG( 250K_4M_PTN1   ) )   /* ボーレート：250kbps_4M    ：パターン1 */
#define CAN_TB_DB_250K_4M_PTN2              ( CAN_TB_u4CmDCFG( 250K_4M_PTN2   ) )   /* ボーレート：250kbps_4M    ：パターン2 */
#define CAN_TB_DB_250K_5M_PTN1              ( CAN_TB_u4CmDCFG( 250K_5M_PTN1   ) )   /* ボーレート：250kbps_5M    ：パターン1 */
#define CAN_TB_DB_250K_5M_PTN2              ( CAN_TB_u4CmDCFG( 250K_5M_PTN2   ) )   /* ボーレート：250kbps_5M    ：パターン2 */
#define CAN_TB_DB_500K_8M_PTN1              ( CAN_TB_u4CmDCFG( 500K_8M_PTN1   ) )   /* ボーレート：500kbps_8M    ：パターン1 */
#define CAN_TB_DB_500K_8M_PTN2              ( CAN_TB_u4CmDCFG( 500K_8M_PTN2   ) )   /* ボーレート：500kbps_8M    ：パターン2 */
#define CAN_TB_DB_500K_8M_PTN3              ( CAN_TB_u4CmDCFG( 500K_8M_PTN3   ) )   /* ボーレート：500kbps_8M    ：パターン3 */
#define CAN_TB_DB_500K_8M_PTN4              ( CAN_TB_u4CmDCFG( 500K_8M_PTN4   ) )   /* ボーレート：500kbps_8M    ：パターン4 */
#define CAN_TB_DB_500K_8M_PTN5              ( CAN_TB_u4CmDCFG( 500K_8M_PTN5   ) )   /* ボーレート：500kbps_8M    ：パターン5 */
#define CAN_TB_DB_500K_10M_PTN1             ( CAN_TB_u4CmDCFG( 500K_10M_PTN1  ) )   /* ボーレート：500kbps_10M   ：パターン1 */
#define CAN_TB_DB_500K_10M_PTN2             ( CAN_TB_u4CmDCFG( 500K_10M_PTN2  ) )   /* ボーレート：500kbps_10M   ：パターン2 */
#define CAN_TB_DB_500K_10M_PTN3             ( CAN_TB_u4CmDCFG( 500K_10M_PTN3  ) )   /* ボーレート：500kbps_10M   ：パターン3 */
#define CAN_TB_DB_500K_10M_PTN4             ( CAN_TB_u4CmDCFG( 500K_10M_PTN4  ) )   /* ボーレート：500kbps_10M   ：パターン4 */
#define CAN_TB_DB_500K_10M_PTN5             ( CAN_TB_u4CmDCFG( 500K_10M_PTN5  ) )   /* ボーレート：500kbps_10M   ：パターン5 */
#define CAN_TB_DB_500K_20M_PTN1             ( CAN_TB_u4CmDCFG( 500K_20M_PTN1  ) )   /* ボーレート：500kbps_20M   ：パターン1 */
#define CAN_TB_DB_500K_32M_PTN1             ( CAN_TB_u4CmDCFG( 500K_32M_PTN1  ) )   /* ボーレート：500kbps_32M   ：パターン1 */
#define CAN_TB_DB_500K_40M_PTN1             ( CAN_TB_u4CmDCFG( 500K_40M_PTN1  ) )   /* ボーレート：500kbps_40M   ：パターン1 */
#define CAN_TB_DB_500K_40M_PTN2             ( CAN_TB_u4CmDCFG( 500K_40M_PTN2  ) )   /* ボーレート：500kbps_40M   ：パターン2 */
#define CAN_TB_DB_500K_80M_PTN1             ( CAN_TB_u4CmDCFG( 500K_80M_PTN1  ) )   /* ボーレート：500kbps_80M   ：パターン1 */
#define CAN_TB_DB_2M_20M_PTN1               ( CAN_TB_u4CmDCFG( 2M_20M_PTN1    ) )   /* ボーレート：2Mbps_20M     ：パターン1 */
#define CAN_TB_DB_2M_32M_PTN1               ( CAN_TB_u4CmDCFG( 2M_32M_PTN1    ) )   /* ボーレート：2Mbps_32M     ：パターン1 */
#define CAN_TB_DB_2M_40M_PTN1               ( CAN_TB_u4CmDCFG( 2M_40M_PTN1    ) )   /* ボーレート：2Mbps_40M     ：パターン1 */
#define CAN_TB_DB_2M_40M_PTN2               ( CAN_TB_u4CmDCFG( 2M_40M_PTN2    ) )   /* ボーレート：2Mbps_40M     ：パターン2 */
#define CAN_TB_DB_2M_80M_PTN1               ( CAN_TB_u4CmDCFG( 2M_80M_PTN1    ) )   /* ボーレート：2Mbps_80M     ：パターン1 */


/*--------------------------------------------------*/
/* CmFDCFG.TDCOビット設定値(CANFDモード用)          */
/*  macro  : CAN_TB_u4TDCO( ptn )                   */
/*  param1 : CAN_CFG_CONTROLLER_DBAUDRATE_# 設定値  */
/*--------------------------------------------------*/
#define CAN_TB_CMFDCFG_SFT_TDCO             ( 16U )             /* TDCO最下位ビット位置 */

/*   データボーレートのサンプリングポイントをfCANクロック時間で設定する                 */
/*   サンプリングポイント = ( SS + TSEG1 )[Tq] * データビットレート プリスケーラ分周比  */
/*                        = ( 1 + ( CmDCFG.DTSEG1設定値+1 ) ) * ( CmDCFG.DBRP設定値+1 ) */
/*   CmFDCFG.TDCO設定値   = サンプリングポイント - 1                                    */
#define CAN_TB_u4TDCO_VAL( ptn )            ( (uint32)( ( (uint32)( 1UL + ( CAN_TB_u4CmDCFG_DTSEG1( ptn ) + 1UL ) ) * ( CAN_TB_u4CmDCFG_DBRP( ptn ) + 1UL ) ) - 1UL ) )
#define CAN_TB_u4TDCO( ptn )                ( (uint32)( CAN_TB_u4TDCO_VAL(ptn) << CAN_TB_CMFDCFG_SFT_TDCO ) & CAN_u4CMFDCFG_TDCO_MSK )

#define CAN_TB_SSPOFFSET_NOUSE              ( 0x00000000UL )                        /* SSPオフセット値：未使用               */
#define CAN_TB_SSPOFFSET_2M_20M_PTN1        ( CAN_TB_u4TDCO( 2M_20M_PTN1 ) )        /* SSPオフセット値：2Mbps_20M：パターン1 */
#define CAN_TB_SSPOFFSET_2M_32M_PTN1        ( CAN_TB_u4TDCO( 2M_32M_PTN1 ) )        /* SSPオフセット値：2Mbps_32M：パターン1 */
#define CAN_TB_SSPOFFSET_2M_40M_PTN1        ( CAN_TB_u4TDCO( 2M_40M_PTN1 ) )        /* SSPオフセット値：2Mbps_40M：パターン1 */
#define CAN_TB_SSPOFFSET_2M_40M_PTN2        ( CAN_TB_u4TDCO( 2M_40M_PTN2 ) )        /* SSPオフセット値：2Mbps_40M：パターン2 */
#define CAN_TB_SSPOFFSET_2M_80M_PTN1        ( CAN_TB_u4TDCO( 2M_80M_PTN1 ) )        /* SSPオフセット値：2Mbps_80M：パターン1 */


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* コントローラ管理情報型 */
typedef struct
{
    uint16 u2RxRuleOffSetId;                                    /* 受信ルール設定テーブル・先頭インデックス                    */
    uint8  u1RxRuleUseNum;                                      /* 受信ルールの数                                              */
    uint8  u1CtrlAct;                                           /* コントローラ別制御対象/非対象                               */
    uint8  u1CtrlUse;                                           /* コントローラ別使用/未使用                                   */
    uint8  u1CtrlOpeMode;                                       /* コントローラ別CANモード                                     */
} CanTbCtrlInfoType;


/* MBOX要素数型 */
typedef struct
{
    uint8  u1TxMbNum;                                           /* コントローラ毎送信用MBOX数                                  */
} CanTbMbNumType;


/* 送信MBOX種別ビット情報型 */
typedef struct
{
    uint32 u4TxIntrBit;                                         /* 割り込み送信MBBit列                                         */
    uint32 u4TxPollBit;                                         /* ポーリング送信MBBit列                                       */
} CanTbTxMbBitType;


/* 受信ルール関連レジスタ型 */
typedef struct
{
    volatile uint32 u4GAFLIDj;                                  /* 0000      受信ルールIDレジスタ                              */
    volatile uint32 u4GAFLMj;                                   /* 0004      受信ルールマスクレジスタ                          */
    volatile uint32 u4GAFLP0j;                                  /* 0008      受信ルールポインタ0レジスタ                       */
    volatile uint32 u4GAFLP1j;                                  /* 000C      受信ルールポインタ1レジスタ                       */
} CanTbRegRxRuleType;


/* 受信バッファデータ関連レジスタ型 */
typedef struct
{
    volatile uint32 u4IDReg;                                    /* 0000      IDレジスタ                                        */
    volatile uint32 u4PTRReg;                                   /* 0004      ポインタレジスタ                                  */
    volatile uint32 u4FDSTSReg;                                 /* 0008      CAN FDステータスレジスタ                          */
    volatile uint32 u4DFReg[ CAN_TB_MB_DATA_ARYSIZE ];          /* 000C-004B データフィールドレジスタ(CAN-FDモード 64byte)     */
                                                                /* (クラシカルCANモードは8byteなので000C-0013のみ使用)         */
    volatile uint32 u4RegPad[ CAN_TB_MB_REG_RSV ];              /* 004C-007F Reserve                                           */
} CanTbRegCANRMType;


/* 受信FIFOバッファデータ関連レジスタ型 */
typedef struct
{
    volatile uint32 u4IDReg;                                    /* 0000      アクセスIDレジスタ                                */
    volatile uint32 u4PTRReg;                                   /* 0004      アクセスポインタレジスタ                          */
    volatile uint32 u4FDSTSReg;                                 /* 0008      CAN FDステータスレジスタ                          */
    volatile uint32 u4DFReg [ CAN_TB_MB_DATA_ARYSIZE ];         /* 000C-004B データフィールドレジスタ(CAN-FDモード 64byte)     */
                                                                /* (クラシカルCANモードは8byteなので000C-0013のみ使用)         */
    volatile uint32 u4RegPad[ CAN_TB_MB_REG_RSV ];              /* 004C-007F Reserve                                           */
} CanTbRegCANRFType;


/* 送信バッファデータ関連レジスタ型 */
typedef struct
{
    volatile uint32 u4IDReg;                                    /* 0000      IDレジスタ                                        */
    volatile uint32 u4PTRReg;                                   /* 0004      ポインタレジスタ                                  */
    volatile uint32 u4FDCTRReg;                                 /* 0008      CAN FDコンフィグレーションレジスタ                */
    volatile uint32 u4DFReg[ CAN_TB_MB_DATA_ARYSIZE ];          /* 000C-004B データフィールドレジスタ(CAN-FDモード 64byte)     */
                                                                /* (クラシカルCANモードは8byteなので000C-0013のみ使用)         */
    volatile uint32 u4RegPad[ CAN_TB_MB_REG_RSV ];              /* 004C-007F Reserve                                           */
} CanTbRegCANTMType;


/* 送受信FIFOバッファデータ関連レジスタ型 */
typedef struct
{
    volatile uint32 u4IDReg;                                    /* 0000      アクセスIDレジスタ                                */
    volatile uint32 u4PTRReg;                                   /* 0004      アクセスポインタレジスタ                          */
    volatile uint32 u4FDCSTSReg;                                /* 0008      CAN FDコンフィグレーション／ステータスレジスタ    */
    volatile uint32 u4DFReg [ CAN_TB_MB_DATA_ARYSIZE ];         /* 000C-004B データフィールドレジスタ(CAN-FDモード 64byte)     */
                                                                /* (クラシカルCANモードは8byteなので000C-0013のみ使用)         */
    volatile uint32 u4RegPad[ CAN_TB_MB_REG_RSV ];              /* 004C-007F Reserve                                           */
} CanTbRegCANCFType;


/* Pointer to Channel Control Registers Structure */
typedef struct
{
    volatile uint32 *                CanConst ptu4TMIECm;       /* 送信バッファ割り込みイネーブルコンフィグレーションレジスタm */
    volatile uint32 *                CanConst ptu4TMTRSTSm;     /* 送信バッファ送信要求ステータスレジスタm                     */
    volatile uint32 *                CanConst ptu4TMTARSTSm;    /* 送信バッファ送信アボート要求ステータスレジスタm             */
    volatile uint32 *                CanConst ptu4TMTCSTSm;     /* 送信バッファ送信完了ステータスレジスタm                     */
    volatile uint32 *                CanConst ptu4TMTASTSm;     /* 送信バッファ送信アボートステータスレジスタm                 */
    volatile uint32 *                CanConst ptu4CmNCFG;       /* チャネル通常ビットレートコンフィグレーションレジスタ        */
    volatile uint32 *                CanConst ptu4CmCTR;        /* チャネル制御レジスタ                                        */
    volatile uint32 *                CanConst ptu4CmSTS;        /* チャネルステータスレジスタ                                  */
    volatile uint32 *                CanConst ptu4CmERFL;       /* チャネルエラーフラグレジスタ                                */
    volatile uint32 *                CanConst ptu4CmDCFG;       /* チャネルデータビットレートコンフィグレーションレジスタ      */
    volatile uint32 *                CanConst ptu4CmFDCFG;      /* チャネルCAN FDコンフィグレーションレジスタ                  */
    volatile uint32 *                CanConst ptu4CmFDCTR;      /* チャネルCAN FD制御レジスタ                                  */
    volatile uint32 *                CanConst ptu4CmFDSTS;      /* チャネルCAN FDステータスレジスタ                            */
    volatile uint32 *                CanConst ptu4CmFDCRC;      /* チャネルCAN FD CRCレジスタ                                  */
    volatile uint32 *                CanConst ptu4TXQCCm;       /* 送信キューコンフィグレーション/制御レジスタm                */
    volatile uint32 *                CanConst ptu4TXQSTSm;      /* 送信キューステータスレジスタm                               */
    volatile uint32 *                CanConst ptu4TXQPCTRm;     /* 送信キューポインタ制御レジスタm                             */
    volatile uint32 *                CanConst ptu4THLCCm;       /* 送信履歴コンフィグレーション/制御レジスタm                  */
    volatile uint32 *                CanConst ptu4THLSTSm;      /* 送信履歴ステータスレジスタm                                 */
    volatile uint32 *                CanConst ptu4THLPCTRm;     /* 送信履歴ポインタ制御レジスタm                               */
    volatile uint32 *                CanConst ptu4CFSTSk;       /* 送受信FIFOバッファステータスレジスタ                        */
    volatile uint8  *                CanConst ptu1TMSTSp;       /* 送信バッファステータスレジスタ                              */
    volatile uint32 *                CanConst ptu4CFCCk;        /* 送受信FIFOバッファコンフィグレーション/制御レジスタ         */
    volatile uint32 *                CanConst ptu4CFPCTRk;      /* 送受信FIFOバッファポインタ制御レジスタ                      */
    volatile uint8  *                CanConst ptu1TMCp;         /* 送信バッファ制御レジスタ                                    */
    volatile CanTbRegCANCFType *     CanConst ptstCF;           /* 送受信FIFOバッファアクセスレジスタセット                    */
    volatile CanTbRegCANTMType *     CanConst ptstTM;           /* 送信バッファレジスタセット                                  */
    volatile uint32 *                CanConst ptu4THLACC0m;     /* 送信履歴アクセスレジスタ0m                                  */
    volatile uint32 *                CanConst ptu4THLACC1m;     /* 送信履歴アクセスレジスタ1m                                  */
} CanTbChRegType;


/* Pointer to Global Control Registers Structure */
typedef struct
{
    /* Can Registers */
    volatile uint32 *                CanConst ptu4GCFG;         /* グローバルコンフィグレーションレジスタ                      */
    volatile uint32 *                CanConst ptu4GCTR;         /* グローバル制御レジスタ                                      */
    volatile uint32 *                CanConst ptu4GSTS;         /* グローバルステータスレジスタ                                */
    volatile uint32 *                CanConst ptu4GERFL;        /* グローバルエラーフラグレジスタ                              */
    volatile uint32 *                CanConst ptu4GTSC;         /* グローバルタイムスタンプカウンタレジスタ                    */
    volatile uint32 *                CanConst ptu4GAFLECTR;     /* 受信ルールエントリ制御レジスタ                              */
    volatile uint32 *                CanConst ptu4GAFLCFG;      /* 受信ルールコンフィグレーションレジスタ                      */
    volatile uint32 *                CanConst ptu4RMNB;         /* 受信バッファナンバレジスタ                                  */
    volatile uint32 *                CanConst ptu4RMNDy;        /* 受信バッファ新データレジスタy                               */
    volatile uint32 *                CanConst ptu4RFCCx;        /* 受信FIFOバッファコンフィグレーション/制御レジスタx          */
    volatile uint32 *                CanConst ptu4RFSTSx;       /* 受信FIFOバッファステータスレジスタx                         */
    volatile uint32 *                CanConst ptu4RFPCTRx;      /* 受信FIFOバッファポインタ制御レジスタx                       */
    volatile uint32 *                CanConst ptu4FESTS;        /* FIFOエンプティステータスレジスタ                            */
    volatile uint32 *                CanConst ptu4FFSTS;        /* FIFOフルステータスレジスタ                                  */
    volatile uint32 *                CanConst ptu4FMSTS;        /* FIFOメッセージロストステータスレジスタ                      */
    volatile uint32 *                CanConst ptu4RFISTS;       /* 受信FIFOバッファ割り込みフラグステータスレジスタ            */
    volatile uint32 *                CanConst ptu4CFRISTS;      /* 送受信FIFOバッファ受信割り込みフラグステータスレジスタ      */
    volatile uint32 *                CanConst ptu4CFTISTS;      /* 送受信FIFOバッファ送信割り込みフラグステータスレジスタ      */
    volatile uint32 *                CanConst ptu4GTINTSTS;     /* グローバルTX割り込みステータスレジスタ                      */
    volatile uint32 *                CanConst ptu4GTSTCFG;      /* グローバルテストコンフィグレーションレジスタ                */
    volatile uint32 *                CanConst ptu4GTSTCTR;      /* グローバルテスト制御レジスタ                                */
    volatile uint32 *                CanConst ptu4GFDCFG;       /* グローバルFDコンフィグレーションレジスタ                    */
    volatile uint32 *                CanConst ptu4GLOCKK;       /* グローバルロックキーレジスタ                                */
    volatile uint32 *                CanConst ptu4CDTCT;        /* DMA許可レジスタ                                             */
    volatile uint32 *                CanConst ptu4CDTSTS;       /* DMAステータスレジスタ                                       */
    volatile CanTbRegRxRuleType *    CanConst ptstGAFL;         /* 受信ルールレジスタセット                                    */
    volatile CanTbRegCANRMType *     CanConst ptstRM;           /* 受信バッファレジスタセット                                  */
    volatile CanTbRegCANRFType *     CanConst ptstRF;           /* 受信FIFOバッファアクセスレジスタセット                      */
    volatile uint32 *                CanConst ptu4RPGACCr;      /* RAMテストページアクセスレジスタr                            */
} CanTbGlobalRegType;


/* レジスタ固着チェック分割情報型 */
typedef struct
{
    uint16 u2StChkStart;                                        /* レジスタ固着チェック開始ページ                              */
    uint16 u2StChkPage;                                         /* レジスタ固着チェックページ数                                */
} CanTbCheckStuckParaType;


/* 受信ルール設定値型 */
typedef struct
{
    uint32 u4GAFLIDjConf;                                       /* 受信ルールIDレジスタ設定値                                  */
    uint32 u4GAFLP0jConf;                                       /* 受信ルールポインタ0レジスタ設定値                           */
    uint32 u4GAFLP1jConf;                                       /* 受信ルールポインタ1レジスタ設定値                           */
    uint8  u1RxMaskRef;                                         /* 受信IDマスク番号                                            */
} CanTbRxRuleSettingType;


/* RSCANレジスタ設定値型 */
typedef struct
{
    uint32 u4CFCC0Conf;                                         /* 送受信FIFOバッファ0コンフィグレーションレジスタ設定値       */
    uint32 u4CFCC1Conf;                                         /* 送受信FIFOバッファ1コンフィグレーションレジスタ設定値       */
    uint32 u4CFCC2Conf;                                         /* 送受信FIFOバッファ2コンフィグレーションレジスタ設定値       */
    uint32 u4CmNCFGConf;                                        /* チャネル通常ビットレートコンフィグレーションレジスタ設定値  */
    uint32 u4CmCTRConf;                                         /* チャネル制御レジスタ設定値                                  */
    uint32 u4CFSTS0Conf;                                        /* 不正割り込み時用送受信FIFOバッファ0割り込みフラグクリア値   */
    uint32 u4CmDCFGConf;                                        /* チャネルデータビットレートコンフィグレーションレジスタ設定値*/
    uint32 u4CmFDCFGConf;                                       /* チャネルCAN FDコンフィグレーションレジスタ設定値            */
    uint32 u4TMFDCTRpConf;                                      /* 送信要求時用TMESIビット設定値                               */
} CanTbSetRSCANRegType;


/* ボーレート切り替えコンフィグ情報型 */
typedef struct
{
    uint32 u4Baudrate;                                          /* 公称ビットレート                                            */
    uint32 u4DataBaudrate;                                      /* データビットレート                                          */
    uint32 u4BaudrateInfo_1;                                    /* ボーレート情報1                                             */
    uint32 u4BaudrateInfo_2;                                    /* ボーレート情報2                                             */
    uint32 u4BaudrateInfo_3;                                    /* ボーレート情報3                                             */
} CanBaudrateSwtCfgType;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/* パイプライン同期 */
void Can_tb_SYNCP( void );


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
/* コントローラ使用情報テーブル */
extern CanConst CanTbCtrlInfoType Can_tb_stCtrlInfo[ CAN_CFG_CONTROLLERNUM_MAX ];

/* MBOX要素数テーブル */
extern CanConst CanTbMbNumType Can_tb_stMbNum[ CAN_CFG_CONTROLLERNUM_MAX ];

/* 送信MBOX種別ビット情報テーブル */
extern CanConst CanTbTxMbBitType Can_tb_stTxMbBit[ CAN_CFG_CONTROLLERNUM_MAX ];

/* 受信マスク値テーブル */
extern CanConst uint32 Can_tb_u4RxMask[ CAN_TB_RXMKTBLSIZE ];

/* レジスタ固着チェック分割情報テーブル */
extern CanConst CanTbCheckStuckParaType Can_tb_stCheckStuckPara[ CAN_CFG_CHKSTKREG_LIMIT ];

/* 受信ルール設定値テーブル */
extern CanConst CanTbRxRuleSettingType Can_tb_stRxRuleSetting[ CAN_TB_RXRULESETTBLSIZE ];

/* チャネル単位のレジスタアドレステーブル */
extern CanConst CanTbChRegType Can_tb_stChReg[ CAN_CFG_CONTROLLERNUM_MAX ];

/* グローバルレジスタアドレステーブル */
extern CanConst CanTbGlobalRegType  Can_tb_stGlobalReg;

/* RSCANレジスタ設定値テーブル */
extern CanConst CanTbSetRSCANRegType Can_tb_stSetRSCANReg[ CAN_CFG_CONTROLLERNUM_MAX ];

/* ビットレートスイッチ設定値テーブル */
extern CanConst uint8 Can_tb_u1BRSInitConf[ CAN_CFG_CONTROLLERNUM_MAX ];

/* ボーレート切り替えコンフィグ情報テーブル */
extern CanConst CanBaudrateSwtCfgType Can_stBaudrateSwtCfgTbl[ CAN_CFG_BRSCFGTBL_SIZE ];

/* ボーレート切り替えコンフィグ情報テーブルの要素数 */
extern CanConst uint8 Can_stBRSwtCfgTbl_ARYSIZE;

/* ボーレート切り替えコンフィグ情報テーブル参照ポインタ */
extern CanConst CanBaudrateSwtCfgType * CanConst Can_tb_ptBaudrateSwtCfgTbl;

/* ボーレート切り替えコンフィグ情報テーブルの要素数参照ポインタ */
extern CanConst uint8 * CanConst Can_tb_ptBRSwtCfgTbl_ARYSIZE;

/* CAN RAM初期化用カウンタ最大値 */
extern CanConst uint32 Can_tb_u4RAMInitCycleMax;

/* モード遷移完了待ちカウンタ値 */
extern CanConst uint16 Can_tb_u2CmodeRst2ComWaitCnt; /* チャネルリセットモードからチャネル通信モード       */
extern CanConst uint16 Can_tb_u2CmodeAny2RstWaitCnt; /* 任意のチャネルモードからチャネルリセットモード     */
extern CanConst uint16 Can_tb_u2GmodeAny2RstWaitCnt; /* 任意のグローバルモードからグローバルリセットモード */

/* 総コントローラ数 */
extern CanConst uint8 Can_tb_u1CtrlNum;

/* 受信ルール数 */
extern CanConst uint16 Can_tb_u2MaxNumRxRule;

/* 受信ルールページ数 */
extern CanConst uint8 Can_tb_u1RxRulePageNum;

/* レジスタ固着チェック対象最終ページ */
extern CanConst uint16 Can_tb_u2LastTestpage;

/* レジスタ固着チェック対象最終ページ 端数レジスタ数 */
extern CanConst uint8 Can_tb_u1LastTestpageRegNum;

/* 受信ルールコンフィグレーションレジスタ設定値 */
extern CanConst uint32 Can_tb_u4GAFLCFG0Conf;
extern CanConst uint32 Can_tb_u4GAFLCFG1Conf;

/* グローバルコンフィグレーションレジスタ設定値 */
extern CanConst uint32 Can_tb_u4GCFGConf;

/* グローバルFDコンフィグレーションレジスタ設定値 */
extern CanConst uint32 Can_tb_u4GFDCFGConf;

/* 受信用FIFO読み込み回数の最大値テーブル */
extern CanConst uint8 Can_tb_u1FifoReadSize[ CAN_CFG_CONTROLLERNUM_MAX ][ CAN_TRX_FIFO_FOR_RX ];


#endif  /* CAN_RSCF3C_TB_PHY_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-2-0         :2020/02/26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
