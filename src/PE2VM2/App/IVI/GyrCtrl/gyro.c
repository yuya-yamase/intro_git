/* メインタスクコードに移管するまでの仮置き */

/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Gyro/G-sensor for 26CDC Models                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GYRO_C_MAJOR                            (1)
#define GYRO_C_MINOR                            (0)
#define GYRO_C_PATCH                            (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "gyro.h"

/* App */
#include "Mcu_I2c_Ctrl_private.h"
#include "Mcu_Sys_Pwr_Gyr.h"
#include "x_spi_ivi_sub1_power.h"
#include "x_spi_ivi_sub1_version.h"
/* BSW */
#include "Dio.h"
/* LIB */
#include "memfill_u1.h"
#include "memcpy_u1.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((GYRO_C_MAJOR != GYRO_H_MAJOR) || \
     (GYRO_C_MINOR != GYRO_H_MINOR) || \
     (GYRO_C_PATCH != GYRO_H_PATCH))
#error "gyro.c and gyro.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* ジャイロ処理結果 */
#define GYRO_RET_NG                             (0U)
#define GYRO_RET_OK                             (1U)
#define GYRO_RET_INPROC                         (2U)    /* 処理実施中 */
#define GYRO_RET_IICERR                         (3U)    /* I2Cエラー */

/* 演算用マクロ */
#define GYRO_SFT_BYTE1                          ( 8U)   /* 1byteシフト */
#define GYRO_SFT_BYTE2                          (16U)   /* 1byteシフト */
#define GYRO_SFT_BYTE3                          (24U)   /* 1byteシフト */
#define GYRO_POS_0                              ( 0U)   /* 配列要素：0 */
#define GYRO_POS_1                              ( 1U)   /* 配列要素：1 */
#define GYRO_POS_2                              ( 2U)   /* 配列要素：2 */
#define GYRO_POS_3                              ( 3U)   /* 配列要素：3 */

/* ジャイロモード */
#define GYRO_DEV_MODE_NORMAL                    (0U)
#define GYRO_DEV_MODE_SUSPEND                   (1U)

/* ジャイロシーケンス制御ID */
#define GYRO_SEQ_MAX                            (4U)    /* シーケンス最大数 */
#define GYRO_SEQ_IDLE                           (0U)    /* 0:アイドルシーケンス */
#define GYRO_SEQ_STAUP1                         (1U)    /* 1:起動(1)シーケンス */
#define GYRO_SEQ_STAUP2                         (2U)    /* 2:起動(2)シーケンス */
#define GYRO_SEQ_SHUTDOWN1                      (3U)    /* 3:終了(1)シーケンス */

/* サブシーケンス 状態通知 */
#define GYRO_RET_NG                             (0U)    /* NG */
#define GYRO_RET_OK                             (1U)    /* OK */
#define GYRO_RET_INPROC                         (2U)    /* 実行中 */
#define GYRO_RET_IICERR                         (3U)    /* I2Cエラー 予備設計 */

/* Gセンサ値 データ換算用マクロ */
#define GYRO_CLC_ACC_BDR                        (0x8000U)   /* プラスとマイナスの境界値 */
#define GYRO_CLC_ACC_U2TOS2                     (32767U)    /* U2データをS2変換で使用する演算値 */
#define GYRO_CLC_ACC_COMPLEMENT                 (1U)        /* 補数計算用マクロ */
#define GYRO_DAT_ACC_XYZ_MAX                    (0x7FFFU)   /* Gセンサ XYZ軸 MAX値(HEX：7FFF) */
#define GYRO_DAT_ACC_XYZ_MIN                    (0x8000U)   /* Gセンサ XYZ軸 MIN値(HEX：8000) */
#define GYRO_DAT_ACC_X_DIF                      (0x0800U)   /* Gセンサ X側の差分値 */
#define GYRO_DAT_ACC_Y_DIF                      (0x0800U)   /* Gセンサ Y側の差分値 */
#define GYRO_DAT_ACC_Z_DIF                      (0x0400U)   /* Gセンサ Z側の差分値 */

/* Self Test エラー上限回数 */
#define GYRO_CNT_SELFTEST_RTRY_MAX              (3U)        /* 規定値：3回(i,j) */

/* Config File設定 データバッファサイズ */
#define GYRO_SIZ_VERSION                        (14U)       /* 14byte(GCONFIG_V**_**) */
#define GYRO_SIZ_BUF                            ( 4U)       /* 4byte */

/* Config File設定 シグネチャ読出し演算 */
#define GYRO_CLC_ADR1                           (1U)
#define GYRO_CLC_ADR2                           (2U)
#define GYRO_CLC_ADR3                           (3U)
#define GYRO_CLC_ADR4                           (4U)
#define GYRO_CLC_ADR5                           (5U)
#define GYRO_CLC_ADR6                           (6U)
#define GYRO_CLC_ADR7                           (7U)

/* Config File設定 比較用文字定義 G_CONFIG */
#define GYRO_FNTOKEN_G                          (0x47)
#define GYRO_FNTOKEN__                          (0x2D)
#define GYRO_FNTOKEN_C                          (0x43)
#define GYRO_FNTOKEN_O                          (0x4F)
#define GYRO_FNTOKEN_N                          (0x4E)
#define GYRO_FNTOKEN_F                          (0x46)
#define GYRO_FNTOKEN_I                          (0x49)
/*  #define GYRO_FNTOKEN_G                          (0x47) */

/* Config File設定 ファイル書込み情報 */
#define GYRO_CFG_NON                            (0x00)      /* データなし */
#define GYRO_CFG_EXIST                          (0x01)      /* データあり */
#define GYRO_CFG_MAXSIZ                         (0x78D0U)   /* Configファイル最大サイズ MAX：0x78D0 (30928byte = 3,2000byte(mot最大) - 48byte(Configヘッダ) - 1024byte(reserved領域)) */
#define GYRO_CFG_WRISIZ                         (32U)       /* configファイル書込み 毎回のサイズ */
#define GYRO_CFG_MAXRTRY                        (3U)        /* configファイル書込み 最大回数 */

/* Config File設定 データ配置アドレス */
#define GYRO_ADR_VERSION                        (0x00000010)
#define GYRO_ADR_OFFSET                         (0x00000020)
#define GYRO_ADR_DATSIZ                         (0x00000024)

/* 起動(2) ジャイロモード 読み出し期待値 */
#define GYRO_DAT_GYROMODE_SUSPEND               (0x80U)     /* suspend mode */

/* 終了(1) Mode Change (Gyro) Read実行上限回数 */
#define GYRO_CNT_SHUTDN1_RTRY_MAX               (3U)        /* 規定値：3回(k(5_1)) */

/* 入力パラメータ設定(2) GセンサRead回数(k(5_2)) */
#define GYRO_CNT_PARASET_ACC_READ               (100U)      /* G値安定を判断のための周期を決めるカウンタ(t20×K(5_2)間の100ms間隔で監視） */

/* 入力パラメータ設定(2) 差分確認の試行回数(k(5_3)) */
#define GYRO_CNT_PARASET_ACC_VERI               (600U)      /* タイムアウトを決めるカウンタ(t20×K(5_2)×K(5_3) 60秒でタイムアウト） */

/* 入力パラメータ設定(2) 軸情報有効個数50個未満チェック */
#define GYRO_CNT_PARASET_ACC_READERR            (50U)

/* 入力パラメータ設定(2) G値安定の閾値(変動幅) */
#define GYRO_CNT_PARASET_ACC_FIX_STAB           (1229U)     /* 0.075g未満であれば安定と判断 */

/* レジスタ処理Step */
#define GYRO_WRISTEP_SETUP_GYR                  (1U)    /* Setup Sensor (Gyro) レジスタ書込み回数 */
#define GYRO_WRISTEP_TEST_COMSET_GYR            (1U)    /* SelfTest(Gyro) 実施コマンド レジスタ書込み回数 */
#define GYRO_WRISTEP_WDG_GYR                    (1U)    /* Set Watchdog Timer (Gyro) レジスタ書込み回数 */
#define GYRO_WRISTEP_MODE_ON_GYR                (1U)    /* Mode Change (Gyro) ON suspend mode ⇒ normal mode レジスタ書込み回数 */
#define GYRO_WRISTEP_MODE_OFF_GYR               (1U)    /* Mode Change (Gyro) OFF normal mode ⇒ suspend mode レジスタ書込み回数 */
#define GYRO_WRISTEP_SETUP_SEN1_ACC             (1U)    /* Setup Sensor (Gセンサ1) レジスタ書込み回数 */
#define GYRO_WRISTEP_SETUP_SEN1_BW_ACC          (1U)    /* Setup Sensor (Gセンサ1)Bandwidth設定 レジスタ書込み回数 */
#define GYRO_WRISTEP_SETUP_SEN2_ACC             (1U)    /* Setup Sensor (Gセンサ2) レジスタ書込み回数 */
#define GYRO_WRISTEP_WDG_ACC                    (1U)    /* Set Watchdog Timer (Gセンサ) レジスタ書込み回数 */
#define GYRO_WRISTEP_MODE_ON_ACC                (1U)    /* Mode Change (Gセンサ) ON suspend mode ⇒ normal mode レジスタ書込み回数 */
#define GYRO_WRISTEP_MODE_OFF_ACC               (1U)    /* Mode Change (Gセンサ) OFF normal mode ⇒ suspend mode レジスタ書込み回数 */
#define GYRO_WRISTEP_SELFTEST_ACC_PLS           (1U)    /* Gセンサセルフテスト(+側) レジスタ書込み回数 */
#define GYRO_WRISTEP_SELFTEST_ACC_MNS           (1U)    /* Gセンサセルフテスト(-側) レジスタ書込み回数 */
#define GYRO_WRISTEP_SELFTEST_ACC_DISABLE       (1U)    /* Gセンサセルフテスト(disable)設定テーブル レジスタ書込み回数 */
#define GYRO_WRISTEP_PWRCONF_ON                 (1U)    /* Gセンサ省電力モード(suspend mode ⇒ normal mode) レジスタ書込み回数 */
#define GYRO_WRISTEP_PWRCONF_OFF                (1U)    /* 予備設計 Gセンサ省電力モード(normal mode ⇒ suspend mode) レジスタ書込み回数 */
#define GYRO_WRISTEP_INTCONF_ON                 (1U)    /* Config-file初期化有効(書込みenable) レジスタ書込み回数 */
#define GYRO_WRISTEP_INTCONF_OFF                (1U)    /* 予備設計 Config-file初期化有効(configファイル書込み後センサ機能有効) レジスタ書込み回数 */
#define GYRO_WRISTEP_SOFTRESET                  (1U)    /* ユーザーによるセンサのソフトリセット レジスタ書込み回数 */
#define GYRO_WRISTEP_INT_ANYMOT_TH              (3U)    /* Gセンサ衝撃検知用設定_INT_ANYMOT_TH レジスタ書込み回数 */
#define GYRO_WRISTEP_INT_ANYMOT_EN              (3U)    /* Gセンサ衝撃検知用設定_INT_ANYMOT_EN レジスタ書込み回数 */
#define GYRO_WRISTEP_INT_OTH                    (1U)    /* Gセンサ衝撃検知用設定(その他) レジスタ書込み回数 */
#define GYRO_WRISTEP_INPRM_SEN1_BW_ACC          (1U)    /* 入力パラメータ設定(2)向けSetup Sensor (Gセンサ1)Bandwidth設定 レジスタ書込み回数 */
#define GYRO_WRISTEP_CFG_OFST1                  (1U)    /* ConfigFile送信AddressOffset1 レジスタ書込み回数 */
#define GYRO_WRISTEP_CFG_OFST2                  (1U)    /* ConfigFile送信AddressOffset2 レジスタ書込み回数 */
#define GYRO_WRISTEP_CFG_DATA                   (1U)    /* ConfigFile送信Data レジスタ書込み回数 */

/* レジスタ操作用マクロ */
#define GYRO_SHIFT_8                            (8U)    /* ビットシフト：8byte */
#define GYRO_WRIPOS_0                           (0U)    /* 書込みバッファ位置：0要素目 */
#define GYRO_WRIPOS_1                           (1U)    /* 書込みバッファ位置：1要素目 */
#define GYRO_WRIPOS_2                           (2U)    /* 書込みバッファ位置：2要素目 */
#define GYRO_READPOS_1                          (1U)    /* 読出しバッファ位置：1要素目 */
#define GYRO_READPOS_2                          (2U)    /* 読出しバッファ位置：2要素目 */
#define GYRO_READPOS_3                          (3U)    /* 読出しバッファ位置：3要素目 */
#define GYRO_READPOS_4                          (4U)    /* 読出しバッファ位置：4要素目 */
#define GYRO_READPOS_5                          (5U)    /* 読出しバッファ位置：5要素目 */
#define GYRO_READPOS_6                          (6U)    /* 読出しバッファ位置：6要素目 */
#define GYRO_READDAT_BIT0                       (0x01U) /* 読出しデータマスク：Bit0 */
#define GYRO_READDAT_BIT1                       (0x02U) /* 読出しデータマスク：Bit1 */
#define GYRO_READDAT_BIT2                       (0x04U) /* 読出しデータマスク：Bit2 */
#define GYRO_READDAT_BIT3                       (0x08U) /* 読出しデータマスク：Bit3 */
#define GYRO_READDAT_BIT4                       (0x10U) /* 読出しデータマスク：Bit4 */
#define GYRO_READDAT_BIT5                       (0x20U) /* 読出しデータマスク：Bit5 */
#define GYRO_READDAT_BIT6                       (0x40U) /* 読出しデータマスク：Bit6 */
#define GYRO_READDAT_BIT7                       (0x80U) /* 読出しデータマスク：Bit7 */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* DIO */
#define GYRO_DIO_LOW                            (STD_LOW)
#define GYRO_DIO_HIGH                           (STD_HIGH)
/* DIO READ */
#define dl_GYRO_DIO_READ_SENSOR_ON()            (Dio_ReadChannel((Dio_ChannelType)DIO_ID_PORT8_CH7))
#define dl_GYRO_DIO_READ_BUDET()                (Dio_ReadChannel((Dio_ChannelType)DIO_ID_PORT0_CH4))
#define dl_GYRO_DIO_READ_V33PERI()              (Dio_ReadChannel((Dio_ChannelType)DIO_ID_PORT10_CH2))
/* DIO WRITE */
#define dl_GYRO_DIO_WRITE_SENSOR_ON_L()         (Dio_WriteChannel((Dio_ChannelType)DIO_ID_PORT8_CH7, (Dio_LevelType)GYRO_DIO_LOW))
#define dl_GYRO_DIO_WRITE_SENSOR_ON_H()         (Dio_WriteChannel((Dio_ChannelType)DIO_ID_PORT8_CH7, (Dio_LevelType)GYRO_DIO_HIGH))

/* シーケンス管理No. */
/* シーケンス実行No 起動(1) */
#define GYRO_SEQ_STAUP1_1                       (GYRO_SEQ_IDLE_STA      )   /* Wait t1 (+B瞬断時のセンサ電源OFF待ち) */
#define GYRO_SEQ_STAUP1_2                       (GYRO_SEQ_IDLE_STA +  1U)   /* SENSOR-ON端子 Lo→Hi (GPIO端子処理) */
#define GYRO_SEQ_STAUP1_3                       (GYRO_SEQ_IDLE_STA +  2U)   /* Wati t3 (SENSOR-ON High → I2Cアクセス可能までの時間) */
#define GYRO_SEQ_STAUP1_4                       (GYRO_SEQ_IDLE_STA +  3U)   /* Set Watchdog Timer (Gyro) */
#define GYRO_SEQ_STAUP1_5                       (GYRO_SEQ_IDLE_STA +  4U)   /* Set Watchdog Timer (Gセンサ) */
#define GYRO_SEQ_STAUP1_6                       (GYRO_SEQ_IDLE_STA +  5U)   /* Mode Change (Gセンサ) ON suspend mode ⇒ normal mode */
#define GYRO_SEQ_STAUP1_7                       (GYRO_SEQ_IDLE_STA +  6U)   /* Wait t11 (デバイス仕様 > 50ms (Gセンサのモード切替後wait時間)) */
#define GYRO_SEQ_STAUP1_8                       (GYRO_SEQ_IDLE_STA +  7U)   /* Setup Sensor (Gyro) */
#define GYRO_SEQ_STAUP1_9                       (GYRO_SEQ_IDLE_STA +  8U)   /* Self-Test (Gyro) */
#define GYRO_SEQ_STAUP1_10                      (GYRO_SEQ_IDLE_STA +  9U)   /* Setup Sensor (Gyro) */
#define GYRO_SEQ_STAUP1_11                      (GYRO_SEQ_IDLE_STA + 10U)   /* Setup Sensor (Gセンサ2) */
#define GYRO_SEQ_STAUP1_12                      (GYRO_SEQ_IDLE_STA + 11U)   /* Self-Test (Gセンサ) */
#define GYRO_SEQ_STAUP1_13                      (GYRO_SEQ_IDLE_STA + 12U)   /* To 【upload config】 */
#define GYRO_SEQ_STAUP1_14                      (GYRO_SEQ_IDLE_STA + 13U)   /* To【Set Interrupt】 */
#define GYRO_SEQ_STAUP1_15                      (GYRO_SEQ_IDLE_STA + 14U)   /* Set Watchdog Timer (Gセンサ) */
#define GYRO_SEQ_STAUP1_16                      (GYRO_SEQ_IDLE_STA + 15U)   /* Setup Sensor (Gセンサ1) */
#define GYRO_SEQ_STAUP1_17                      (GYRO_SEQ_IDLE_STA + 16U)   /* Mode Change (Gyro) OFF normal mode ⇒ suspend mode */
#define GYRO_SEQ_STAUP1_18                      (GYRO_SEQ_IDLE_STA + 17U)   /* Wati t21 (Gyroモード切替後のwait時間) */

/* シーケンス実行No Self-Test (Gyro) */
#define GYRO_SEQ_SELFTEST_GYRO_1                (GYRO_SEQ_IDLE_STA      )   /* 【write】0x3C */
#define GYRO_SEQ_SELFTEST_GYRO_2                (GYRO_SEQ_IDLE_STA +  1U)   /* 【wait】t12 */
#define GYRO_SEQ_SELFTEST_GYRO_3                (GYRO_SEQ_IDLE_STA +  2U)   /* 【read】0x3C */
#define GYRO_SEQ_SELFTEST_GYRO_4                (GYRO_SEQ_IDLE_STA +  3U)   /* SelfTest完了判定 */

/* シーケンス実行No Self-Test (Gセンサ) */
#define GYRO_SEQ_SELFTEST_ACC_1                 (GYRO_SEQ_IDLE_STA      )   /* wait t13 */
#define GYRO_SEQ_SELFTEST_ACC_2                 (GYRO_SEQ_IDLE_STA +  1U)   /* write 0x6D （＋側） */
#define GYRO_SEQ_SELFTEST_ACC_3                 (GYRO_SEQ_IDLE_STA +  2U)   /* wait t14 */
#define GYRO_SEQ_SELFTEST_ACC_4                 (GYRO_SEQ_IDLE_STA +  3U)   /* Read data (Gセンサ +),データ換算 */
#define GYRO_SEQ_SELFTEST_ACC_5                 (GYRO_SEQ_IDLE_STA +  4U)   /* write 0x6D （-側） */
#define GYRO_SEQ_SELFTEST_ACC_6                 (GYRO_SEQ_IDLE_STA +  5U)   /* wait t14 */
#define GYRO_SEQ_SELFTEST_ACC_7                 (GYRO_SEQ_IDLE_STA +  6U)   /* Read data (Gセンサ -),データ換算 */
#define GYRO_SEQ_SELFTEST_ACC_8                 (GYRO_SEQ_IDLE_STA +  7U)   /* write 0x6D （disable） */
#define GYRO_SEQ_SELFTEST_ACC_9                 (GYRO_SEQ_IDLE_STA +  8U)   /* wait t14 */
#define GYRO_SEQ_SELFTEST_ACC_10                (GYRO_SEQ_IDLE_STA +  9U)   /* テスト結果判定 */

/* シーケンス実行No upload config */
#define GYRO_SEQ_UPCONF_1                       (GYRO_SEQ_IDLE_STA      )   /* Configファイル読出し,INIT Check NGカウント初期化 */
#define GYRO_SEQ_UPCONF_2                       (GYRO_SEQ_IDLE_STA +  1U)   /* softreset (Gセンサ) */
#define GYRO_SEQ_UPCONF_3                       (GYRO_SEQ_IDLE_STA +  2U)   /* wait t15 */
#define GYRO_SEQ_UPCONF_4                       (GYRO_SEQ_IDLE_STA +  3U)   /* change mode ACC suspend(ADS:0x7D) */
#define GYRO_SEQ_UPCONF_5                       (GYRO_SEQ_IDLE_STA +  4U)   /* wait t10 */
#define GYRO_SEQ_UPCONF_6                       (GYRO_SEQ_IDLE_STA +  5U)   /* change mode ACC normal(ADS:0x7C) */
#define GYRO_SEQ_UPCONF_7                       (GYRO_SEQ_IDLE_STA +  6U)   /* wait t15 */
#define GYRO_SEQ_UPCONF_8                       (GYRO_SEQ_IDLE_STA +  7U)   /* Set INT_CTRL write ADS:0x59 val:0x00 */
#define GYRO_SEQ_UPCONF_9                       (GYRO_SEQ_IDLE_STA +  8U)   /* wait t15 */
#define GYRO_SEQ_UPCONF_10                      (GYRO_SEQ_IDLE_STA +  9U)   /* upload config file via I2C write 0x5B */
#define GYRO_SEQ_UPCONF_11                      (GYRO_SEQ_IDLE_STA + 10U)   /* upload config file via I2C write 0x5C */
#define GYRO_SEQ_UPCONF_12                      (GYRO_SEQ_IDLE_STA + 11U)   /* upload config file via I2C write 0x5E */
#define GYRO_SEQ_UPCONF_13                      (GYRO_SEQ_IDLE_STA + 12U)   /* Set INT_CTRL write ADS:0x59 val:0x01 */
#define GYRO_SEQ_UPCONF_14                      (GYRO_SEQ_IDLE_STA + 13U)   /* wait t15 */
#define GYRO_SEQ_UPCONF_15                      (GYRO_SEQ_IDLE_STA + 14U)   /* read 0x2A */
#define GYRO_SEQ_UPCONF_16                      (GYRO_SEQ_IDLE_STA + 15U)   /* change mode ACC normal */
#define GYRO_SEQ_UPCONF_17                      (GYRO_SEQ_IDLE_STA + 16U)   /* wait t15 */

/* シーケンス実行No Set Interrupt */
#define GYRO_SEQ_INTSET_1                       (GYRO_SEQ_IDLE_STA      )   /* INT_ANYMOT_TH */
#define GYRO_SEQ_INTSET_2                       (GYRO_SEQ_IDLE_STA +  1U)   /* INT_ANYMOT_EN */
#define GYRO_SEQ_INTSET_3                       (GYRO_SEQ_IDLE_STA +  2U)   /* INT2_IO_CONF,INT_LATCH,INT2_MAP */

/* シーケンス実行No 起動(2) */
#define GYRO_SEQ_STAUP2_1                       (GYRO_SEQ_IDLE_STA      )     /* Gセンサ 0x40に0xA8をWrite */
#define GYRO_SEQ_STAUP2_2                       (GYRO_SEQ_IDLE_STA +  1U)     /* Mode Change (Gyro) Read */
#define GYRO_SEQ_STAUP2_3                       (GYRO_SEQ_IDLE_STA +  2U)     /* Mode (Gyro) チェック */
#define GYRO_SEQ_STAUP2_4                       (GYRO_SEQ_IDLE_STA +  3U)     /* Wait t10 (Gyroセンサsuspend mode時のwait time) */
#define GYRO_SEQ_STAUP2_5                       (GYRO_SEQ_IDLE_STA +  4U)     /* Mode Change (Gyro) ON suspend mode ⇒ normal mode */
#define GYRO_SEQ_STAUP2_6                       (GYRO_SEQ_IDLE_STA +  5U)     /* Wait t21 (Gyroモード切替後のwait時間) */

/* シーケンス実行No 終了(1) */
#define GYRO_SEQ_SHUTDN1_1                      (GYRO_SEQ_IDLE_STA      )     /* SENSOR-ON端子= Hi ? */
#define GYRO_SEQ_SHUTDN1_2                      (GYRO_SEQ_IDLE_STA +  1U)     /* Mode Change (Gyro) OFF normal mode ⇒ suspend mode */
#define GYRO_SEQ_SHUTDN1_3                      (GYRO_SEQ_IDLE_STA +  2U)     /* Wait t21 */
#define GYRO_SEQ_SHUTDN1_4                      (GYRO_SEQ_IDLE_STA +  3U)     /* Mode Change (Gyro) Read */
#define GYRO_SEQ_SHUTDN1_5                      (GYRO_SEQ_IDLE_STA +  4U)     /* Read Data = 0x80 ? */
#define GYRO_SEQ_SHUTDN1_6                      (GYRO_SEQ_IDLE_STA +  5U)     /* Wait t18 */
#define GYRO_SEQ_SHUTDN1_7                      (GYRO_SEQ_IDLE_STA +  6U)     /* カウンタ≧ k(5-1)回？ */
#define GYRO_SEQ_SHUTDN1_8                      (GYRO_SEQ_IDLE_STA +  7U)     /* Wait t10 */
#define GYRO_SEQ_SHUTDN1_9                      (GYRO_SEQ_IDLE_STA +  8U)     /* 5.2.6 入力パラメータ設定(2) */

/* シーケンス実行No 入力パラメータ設定(2) */
#define GYRO_SEQ_PARASET2_1                     (GYRO_SEQ_IDLE_STA      )     /* 衝撃検知有効の保持値が出力ＯＮか？ */
#define GYRO_SEQ_PARASET2_2                     (GYRO_SEQ_IDLE_STA +  1U)     /* Gセンサ0x40に0xACをWrite */
#define GYRO_SEQ_PARASET2_3                     (GYRO_SEQ_IDLE_STA +  2U)     /* wait t19,カウンタk(5_2)、k(5_3) クリア */
#define GYRO_SEQ_PARASET2_4                     (GYRO_SEQ_IDLE_STA +  3U)     /* MAX値、MIN値クリア */
#define GYRO_SEQ_PARASET2_5                     (GYRO_SEQ_IDLE_STA +  4U)     /* V33-PERI-ON検知 */
#define GYRO_SEQ_PARASET2_6                     (GYRO_SEQ_IDLE_STA +  5U)     /* Gセンサ0x12～0x17をRead */
#define GYRO_SEQ_PARASET2_7                     (GYRO_SEQ_IDLE_STA +  6U)     /* GセンサMAX,MIN更新 */
#define GYRO_SEQ_PARASET2_8                     (GYRO_SEQ_IDLE_STA +  7U)     /* wait t20,GセンサRead回数(k(5_2))チェック */
#define GYRO_SEQ_PARASET2_9                     (GYRO_SEQ_IDLE_STA +  8U)     /* 差分確認|MAX-MIN|処理,差分確認の試行回数(k(5_3))チェック */
#define GYRO_SEQ_PARASET2_10                    (GYRO_SEQ_IDLE_STA +  9U)     /* "入力パラメータ保持" で保持していた設定を書込み */

/* 待機時間設定 */
/* T1  SENSOR-ON OFF→ON時間(+B瞬断時のセンサ電源OFF待機時間含む) 30ms--50ms */
#define GYRO_WAIT_T1                            ( 40U   / GYRO_TASK_TIME)
/* T3  SENSOR-ON High → I2Cアクセス可能までの時間 */
#define GYRO_WAIT_T3                            (210U   / GYRO_TASK_TIME)
/* T11 Gセンサのモード切替後wait時間 */
#define GYRO_WAIT_T11                           ( 60U   / GYRO_TASK_TIME)
/* T12 Selftest(Gyro)実行時間 （デバイス仕様 ＞ 50ms） */
#define GYRO_WAIT_T12                           ( 60U   / GYRO_TASK_TIME)
/* T13 Selftest(Gｾﾝｻ)待機時間 （デバイス仕様 ＞ 2ms） */
#define GYRO_WAIT_T13                           (  5U   / GYRO_TASK_TIME)
/* T14 Selftest(Gｾﾝｻ)実行時間 （デバイス仕様 ＞ 50ms） */
#define GYRO_WAIT_T14                           ( 60U   / GYRO_TASK_TIME)
/* T15 デバイス仕様規定の wait 時間 (デバイス仕様：min 150ms) */
#define GYRO_WAIT_T15                           (170U   / GYRO_TASK_TIME)
/* T18 IC機能のWatchdog期間から規定。 2ms-10ms-20ms */
#define GYRO_WAIT_T18                           ( 10U   / GYRO_TASK_TIME)
/* T21 Gyroモード切替後のwait時間 (デバイス仕様 200ms) */
#define GYRO_WAIT_T21                           (210U   / GYRO_TASK_TIME)

/* I2C Read/Write */
#define GYRO_I2C_WRITE_GYRO(u,v,w,x,y,z)        (Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_GYRO, (u), (v), (U1)GP_I2C_MA_SLA_6_GYRO, (w), (x), (y), (z)))
#define GYRO_I2C_READ_GYRO(w,x,y,z)             (Mcu_Dev_I2c_Ctrl_RegRead((U1)MCU_I2C_ACK_GYRO, (w), (U1)GP_I2C_MA_SLA_6_GYRO, (x), (y), (z), (U1)MCU_I2C_WAIT_NON))
#define GYRO_I2C_WRITE_ACC(u,v,w,x,y,z)         (Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_G_MONI, (u), (v), (U1)GP_I2C_MA_SLA_7_G_MONI, (w), (x), (y), (z)))
#define GYRO_I2C_READ_ACC(w,x,y,z)              (Mcu_Dev_I2c_Ctrl_RegRead((U1)MCU_I2C_ACK_G_MONI, (w), (U1)GP_I2C_MA_SLA_7_G_MONI, (x), (y), (z), (U1)MCU_I2C_WAIT_NON))

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* ジャイロ制御管理バッファ */
typedef struct {
    U1      u1_mod;         /* GYRO制御モード */
    U1      u1_event;       /* イベント */
    U1      u1_dev_mode;    /* GYROデバイスモード */
}ST_GYRO_CTL_MNG;

/* ジャイロシーケンス管理バッファ */
typedef struct{
    U1      u1_no;          /* シーケンスモード */
    U1      u1_step;        /* シーケンスステップ */
    U1      u1_subtype;     /* シーケンスサブステップ */
}ST_GYRO_SEQMNG;

/* シーケンス処理テーブル */
typedef void (*FP_GYRO_SRQ_FUNC)(void);     /* イベントアドレス */

/* ジャイロ状態遷移テーブル */
typedef void (*FP_GYRO_EVNT_HNDL)(void);    /* GYRO状態イベント処理ハンドラ */

/* Gセンサ受信データバッファ */
typedef struct {
    S2      s2_x;   /* 加速度データ(X軸) */
    S2      s2_y;   /* 加速度データ(Y軸) */
    S2      s2_z;   /* 加速度データ(Z軸) */
}ST_GYRO_ACC_XYZ;

typedef struct {
    U1                  u1_acc_x_lsb;
    U1                  u1_acc_x_msb;
    U1                  u1_acc_y_lsb;
    U1                  u1_acc_y_msb;
    U1                  u1_acc_z_lsb;
    U1                  u1_acc_z_msb;
    ST_GYRO_ACC_XYZ     st_acc_xyz;
}ST_GYRO_ACCTEST;

typedef struct gyro
{
    ST_GYRO_ACC_XYZ     st_min;         /* 加速度軸情報(MIN) */
    ST_GYRO_ACC_XYZ     st_max;         /* 加速度軸情報(MAX) */
    ST_GYRO_ACCTEST     st_calc;        /* 加速度軸情報(一時演算用) */
    U1                  u1_updatecnt;   /* 軸情報更新個数 */
    U1                  u1_errlog_sts;  /* ダイレコ記録有無フラグ */
}ST_GYRO_ACC;

/* Gセンサデータインフォ構造体 */
typedef struct
{
    U4                  u4_datsiz;      /* 車パラデータの全体サイズ */
    U4                  u4_strtadr;     /* データ部の先頭アドレス */
}ST_GYRO_DATAINFO;

typedef struct
{
    U1                  u1_upload_cnt;  /* configファイル書込み総回数 */
    U1                  u1_upload_idx;  /* configファイル書込み済回数カウンタ */
    U4                  u4_upload_addr; /* configファイル書込みデータ部の先頭アドレス */
}ST_GYRO_CFGMNG;


/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* ジャイロ制御管理バッファ */
static ST_GYRO_CTL_MNG      st_s_gyro_ctrl;
/* シーケンス管理バッファ */
static ST_GYRO_SEQMNG       st_s_gyro_seqmng;

/* V33-Peri-ON状態 */
static Dio_LevelType        dl_s_gyro_v33perion_sts;
/* V33オフフラグ */
static U1                   u1_s_gyro_v33OffFlg;

/* システムオフフラグ */
static U1                   u1_s_gyro_sysoffflg;

/* Self Test エラーカウント l(6_1) */
static U1                   u1_s_errcnt_l;
/* Self Test エラーカウント j(6_1) */
static U1                   u1_s_errcnt_j;  /* preliminary design */

/* SelfTest(Gセンサ) +側データ */
static ST_GYRO_ACCTEST      st_s_gyro_accdat_pls;
/* SelfTest(Gセンサ) -側データ */
static ST_GYRO_ACCTEST      st_s_gyro_accdat_mns;

/* configファイル書込み管理 */
static ST_GYRO_CFGMNG       st_s_gyro_cfgmng;

/* Configファイル設定retry回数 */
static U1                   u1_s_gyro_uploadcfg_rtrycnt;

/* 終了フロー(1) リトライカウンタ */
static U1                   u1_s_cnt_shutdn;

/* 入力パラメータ設定(2) GセンサRead回数カウンタ(k(5_2)) */
static U1                   u1_s_cnt_g_read;

/* 入力パラメータ設定(2) 差分確認の試行回数カウンタ(k(5_3)) */
static U2                   u2_s_cnt_diff_verif;

/* 入力パラメータ設定(2) 加速度センサデータ(軸情報) */
static ST_GYRO_ACC          st_s_gyro_accdat;

/* フロー内待機時間用タイマ */
static U4                   u4_s_gyro_linktim;

/* I2C書込み/読込みから応答までの時間計測 */
static U4                   u4_s_gyro_acktime;
/* I2C書込み/読込み位置指定 */
static U2                   u2_s_gyro_regstep;
/* I2C書込み/読込みアクセス間Waitタイマ */
static U2                   u2_s_gyro_i2cwaittim;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/**************************外部端子入力監視************************/
static void     vd_s_GyroBuDetHiCheck(void);
static void     vd_s_GyroBuDetHi(void);
static void     vd_s_GyroV33PeriOnCheck(void);

/**************************状態遷移管理***************************/
static void     vd_s_GyroDevCtlMngModSet(const U1 u1_a_MODE);
static void     vd_s_GyroDevUnInitTskStup(void);
static void     vd_s_GyroDevComErrTskStup(void);
static void     vd_s_GyroDevStup1CompV33PeriOnOn(void);
static void     vd_s_GyroDevNormV33PeriOnOn(void);
static void     vd_s_GyroDevErrV33PeriOnOn(void);
static void     vd_s_GyroDevNormV33PeriOnOff(void);
static void     vd_s_GyroDevComSysOffWait(void);
static void     vd_s_GyroDevComSysOffProc(void);
static void     vd_s_GyroDevErrSysOff(void);
static void     vd_s_GyroDevStup1ProSeqComp(void);
static void     vd_s_GyroDevStup2ProSeqComp(void);
static void     vd_s_GyroDevShtdn1ProSeqComp(void);
static void     vd_s_GyroDevStup1ProErr(void);
static void     vd_s_GyroDevStup2ProErr(void);
static void     vd_s_GyroDevComDtcErr(void);
static void     vd_s_GyroDevShutDn1ProErr(void);
static void     vd_s_GyroDevComRst(void);

/**************************シーケンス管理*************************/
static void     vd_s_GyroDevSeqCtl(void);
static void     vd_s_GyroDevSeqSet(const U1 u1_a_SEQNO);
static void     vd_s_GyroDevSeqIdle(void);
static void     vd_s_GyroDevSeqStaUp1(void);
static U1       u1_s_GyroDevSeqGyrSelfTest(void);
static U1       u1_s_GyroDevSeqAccSelfTest(void);
static void     vd_s_GyroDevSeqSelfTestErr(void);
static U1       u1_s_GyroDevSeqAccCfgUpload(void);
static U1       u1_s_GyroGetDatInfo(ST_GYRO_DATAINFO * st_a_datainfo);
static U1       u1_s_GyroGetStsChk(void);
static U1       u1_s_GyroDevSeqAccIntSet(void);
static void     vd_s_GyroDevSeqStaUp2(void);
static void     vd_s_GyroDevSeqGyrShutDn1(void);
static U1       u1_s_GyroDevParamSet2(void);
static void     vd_s_GyroDevAccDataClear(void);
static void     vd_s_GyroDevAccMinMaxUpdate(void);
static U1       u1_s_GyroDevAccMinMaxCheck(void);

/**************************共通関数*************************/
static void     vd_s_GyroDevMemset(void * vdp_a_dst, const U1 u1_a_DATA, U4 u4_a_size);
static void     vd_s_GyroDevForceEnd(void);
static U1       u1_s_GyroDevTimCheck(const U4 u4_a_SRC, const U4 u4_a_TRGT);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* シーケンス処理テーブル */
static const FP_GYRO_SRQ_FUNC   fp_sp_gyro_Seq[GYRO_SEQ_MAX] = {
    { vd_s_GyroDevSeqIdle       },  /* アイドルシーケンス           */
    { vd_s_GyroDevSeqStaUp1     },  /* GYRO起動(1)処理シーケンス    */
    { vd_s_GyroDevSeqStaUp2     },  /* GYRO起動(2)処理シーケンス    */
    { vd_s_GyroDevSeqGyrShutDn1 }   /* GYRO終了(1)処理シーケンス    */
};

/* ジャイロ状態遷移テーブル */
static const FP_GYRO_EVNT_HNDL  fp_sp2_GYRO_EVENT_HANDLER[GYRO_MODE_MAX][GYRO_EVENT_MAX] = 
{
    /* Taks ON                      V33-Peri-ON OFF->ON                 V33-Peri-ON ON->OFF             System OFF                  Sequence Fin                    Startup Anomaly             DTC Anomaly             Fin Anomaly                 Reset                                       */
    { vd_s_GyroDevUnInitTskStup,    vdp_PTR_NA,                         vdp_PTR_NA,                     vdp_PTR_NA,                 vdp_PTR_NA,                     vdp_PTR_NA,                 vdp_PTR_NA,             vdp_PTR_NA,                 vdp_PTR_NA,         },  /* 未初期化         */
    { vd_s_GyroDevComErrTskStup,    vdp_PTR_NA,                         vdp_PTR_NA,                     vd_s_GyroDevComSysOffWait,  vd_s_GyroDevStup1ProSeqComp,    vd_s_GyroDevStup1ProErr,    vdp_PTR_NA,             vdp_PTR_NA,                 vd_s_GyroDevComRst, },  /* 起動(1)実施中    */
    { vdp_PTR_NA,                   vd_s_GyroDevStup1CompV33PeriOnOn,   vdp_PTR_NA,                     vd_s_GyroDevComSysOffProc,  vdp_PTR_NA,                     vdp_PTR_NA,                 vdp_PTR_NA,             vdp_PTR_NA,                 vdp_PTR_NA,         },  /* 起動(1)実施完了  */
    { vd_s_GyroDevComErrTskStup,    vdp_PTR_NA,                         vdp_PTR_NA,                     vd_s_GyroDevComSysOffWait,  vd_s_GyroDevStup2ProSeqComp,    vd_s_GyroDevStup2ProErr,    vdp_PTR_NA,             vdp_PTR_NA,                 vdp_PTR_NA,         },  /* 起動(2)実施中    */
    { vd_s_GyroDevComErrTskStup,    vd_s_GyroDevNormV33PeriOnOn,        vd_s_GyroDevNormV33PeriOnOff,   vd_s_GyroDevComSysOffWait,  vdp_PTR_NA,                     vdp_PTR_NA,                 vd_s_GyroDevComDtcErr,  vdp_PTR_NA,                 vd_s_GyroDevComRst, },  /* 通常動作中       */
    { vd_s_GyroDevComErrTskStup,    vdp_PTR_NA,                         vdp_PTR_NA,                     vd_s_GyroDevComSysOffWait,  vd_s_GyroDevShtdn1ProSeqComp,   vdp_PTR_NA,                 vdp_PTR_NA,             vd_s_GyroDevShutDn1ProErr,  vdp_PTR_NA,         },  /* 終了(1)実施中    */
    { vd_s_GyroDevComErrTskStup,    vd_s_GyroDevErrV33PeriOnOn,         vdp_PTR_NA,                     vd_s_GyroDevErrSysOff,      vdp_PTR_NA,                     vdp_PTR_NA,                 vdp_PTR_NA,             vdp_PTR_NA,                 vdp_PTR_NA,         }   /* 異常停止中       */
};

/* I2C書き込み管理用テーブル */
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_SETUP_GYR[GYRO_WRISTEP_SETUP_GYR] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         2,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_TEST_COMSET_GYR[GYRO_WRISTEP_TEST_COMSET_GYR] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_WDG_GYR[GYRO_WRISTEP_WDG_GYR] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_MODE_ON_GYR[GYRO_WRISTEP_MODE_ON_GYR] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_MODE_OFF_GYR[GYRO_WRISTEP_MODE_OFF_GYR] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_SETUP_SEN1_ACC[GYRO_WRISTEP_SETUP_SEN1_ACC] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         2,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_SETUP_SEN1_BW_ACC[GYRO_WRISTEP_SETUP_SEN1_BW_ACC] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_SETUP_SEN2_ACC[GYRO_WRISTEP_SETUP_SEN2_ACC] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         2,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_WDG_ACC[GYRO_WRISTEP_WDG_ACC] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_MODE_ON_ACC[GYRO_WRISTEP_MODE_ON_ACC] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_MODE_OFF_ACC[GYRO_WRISTEP_MODE_OFF_ACC] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_SELFTEST_ACC_PLS[GYRO_WRISTEP_SELFTEST_ACC_PLS] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_SELFTEST_ACC_MNS[GYRO_WRISTEP_SELFTEST_ACC_MNS] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_SELFTEST_ACC_DISABLE[GYRO_WRISTEP_SELFTEST_ACC_DISABLE] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_PWRCONF_ON[GYRO_WRISTEP_PWRCONF_ON] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_PWRCONF_OFF[GYRO_WRISTEP_PWRCONF_OFF] = {    /* preliminary design */
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_INTCONF_ON[GYRO_WRISTEP_INTCONF_ON] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_INTCONF_OFF[GYRO_WRISTEP_INTCONF_OFF] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_SOFTRESET[GYRO_WRISTEP_SOFTRESET] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_INT_ANYMOT_TH[GYRO_WRISTEP_INT_ANYMOT_TH] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0},
    {        1,         1,         0},
    {        2,         1,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_INT_ANYMOT_EN[GYRO_WRISTEP_INT_ANYMOT_EN] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0},
    {        1,         1,         0},
    {        2,         1,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_INT_OTH[GYRO_WRISTEP_INT_OTH] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         3,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_INPRM_SEN1_BW_ACC[GYRO_WRISTEP_INPRM_SEN1_BW_ACC] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_CFG_OFST1[GYRO_WRISTEP_CFG_OFST1] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_CFG_OFST2[GYRO_WRISTEP_CFG_OFST2] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_CFG_DATA[GYRO_WRISTEP_CFG_DATA] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};

static const U1                 u1_sp_GYRO_CONFIG[] = {
    0x47, 0x2D, 0x43, 0x4F, 0x4E, 0x46, 0x49, 0x47, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x47, 0x43, 0x4F, 0x4E, 0x46, 0x49, 0x47, 0x5F, 0x56, 0x30, 0x31, 0x2D, 0x37, 0x31, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xC8, 0x2E, 0x00, 0x2E, 0x80, 0x2E, 0x71, 0x01, 0xC8, 0x2E, 0x00, 0x2E, 0xC8, 0x2E, 0x00, 0x2E,
    0x80, 0x2E, 0x36, 0x01, 0x80, 0x2E, 0xB6, 0x00, 0x80, 0x2E, 0x95, 0x00, 0x80, 0x2E, 0xB7, 0x00,
    0x50, 0x39, 0x21, 0x2E, 0xB0, 0xF0, 0x10, 0x30, 0x21, 0x2E, 0x16, 0xF0, 0x80, 0x2E, 0xFC, 0x00,
    0x31, 0x50, 0x41, 0x30, 0x01, 0x42, 0x3C, 0x80, 0x00, 0x2E, 0x01, 0x40, 0x01, 0x42, 0x21, 0x2E,
    0xFF, 0xAF, 0xB8, 0x2E, 0x02, 0x00, 0x04, 0x00, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9D, 0xA7,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0xFD, 0x2D, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9A, 0x01,
    0x34, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0x50, 0xF7, 0x7F, 0x00, 0x2E,
    0x0F, 0x2E, 0x43, 0xF0, 0xF8, 0xBF, 0xFF, 0xBB, 0xC0, 0xB3, 0x11, 0x2F, 0xE6, 0x7F, 0xD5, 0x7F,
    0xC4, 0x7F, 0xB3, 0x7F, 0xA2, 0x7F, 0x91, 0x7F, 0x80, 0x7F, 0x7B, 0x7F, 0x98, 0x2E, 0x44, 0xB2,
    0x80, 0x6F, 0x91, 0x6F, 0xA2, 0x6F, 0xB3, 0x6F, 0xC4, 0x6F, 0xD5, 0x6F, 0xE6, 0x6F, 0x7B, 0x6F,
    0x47, 0x30, 0x2F, 0x2E, 0xB8, 0xF0, 0xF7, 0x6F, 0x70, 0x5F, 0xC8, 0x2E, 0xC8, 0x2E, 0x60, 0x50,
    0xD1, 0x7F, 0xE2, 0x7F, 0xC7, 0x7F, 0xF6, 0x7F, 0xB0, 0x7F, 0x36, 0x30, 0x03, 0x2E, 0x01, 0xF0,
    0x9E, 0xBC, 0x21, 0x54, 0x9E, 0xBB, 0xBF, 0x82, 0xB7, 0x05, 0x80, 0x40, 0x43, 0x8E, 0x41, 0x40,
    0x08, 0xBC, 0x41, 0x0A, 0x1F, 0x50, 0x4E, 0x10, 0x11, 0x42, 0xAB, 0x7F, 0x00, 0x2E, 0xE2, 0x41,
    0xC1, 0x41, 0x28, 0xBD, 0x51, 0x0A, 0x4E, 0x10, 0x11, 0x42, 0xC3, 0x8F, 0x11, 0x30, 0xE2, 0x41,
    0xC7, 0x41, 0x28, 0xBD, 0x97, 0x0A, 0x96, 0x10, 0x02, 0x42, 0x23, 0x2E, 0x26, 0x00, 0x98, 0x2E,
    0xFA, 0x01, 0x00, 0xB2, 0x01, 0x2F, 0x98, 0x2E, 0x00, 0xB0, 0x00, 0x31, 0x21, 0x2E, 0xB8, 0xF0,
    0xF6, 0x6F, 0xAB, 0x6F, 0xD1, 0x6F, 0xE2, 0x6F, 0xC7, 0x6F, 0xB0, 0x6F, 0xA0, 0x5F, 0xC8, 0x2E,
    0x40, 0x30, 0xC0, 0x2E, 0x21, 0x2E, 0xBA, 0xF0, 0x00, 0x31, 0xC0, 0x2E, 0x21, 0x2E, 0xBA, 0xF0,
    0x10, 0x30, 0xC0, 0x2E, 0x21, 0x2E, 0xBB, 0xF0, 0x1A, 0x24, 0x30, 0x00, 0x80, 0x2E, 0x94, 0x01,
    0xAA, 0x00, 0x05, 0xE0, 0x00, 0x00, 0x00, 0x0C, 0xE8, 0x73, 0x04, 0x00, 0x00, 0x02, 0x00, 0x01,
    0x00, 0x00, 0x30, 0x0A, 0x80, 0x00, 0xAA, 0x00, 0x05, 0xE0, 0x47, 0x00, 0x88, 0x00, 0x28, 0x00,
    0x89, 0xF0, 0x2B, 0x00, 0x80, 0x00, 0x39, 0xF0, 0x03, 0x01, 0x06, 0x01, 0x0B, 0x01, 0x09, 0x01,
    0x59, 0xF0, 0xC0, 0x00, 0xB1, 0xF0, 0x00, 0x40, 0xAF, 0x00, 0xFF, 0x00, 0xFF, 0xB7, 0x00, 0x02,
    0x00, 0xB0, 0x05, 0x80, 0x54, 0x00, 0x5C, 0x00, 0x5A, 0x00, 0x52, 0xF0, 0x6D, 0x00, 0x32, 0xF0,
    0x66, 0x00, 0x28, 0xF0, 0x72, 0x00, 0x75, 0x00, 0x75, 0x00, 0x7D, 0x00, 0x00, 0x10, 0x7F, 0x00,
    0x00, 0x0C, 0x22, 0x00, 0x8B, 0x00, 0x81, 0x00, 0x9A, 0x01, 0x88, 0x00, 0x60, 0x50, 0xF6, 0x7F,
    0xEB, 0x7F, 0xD0, 0x7F, 0xC5, 0x7F, 0xB7, 0x7F, 0x98, 0x2E, 0xFA, 0x01, 0x00, 0x90, 0xA4, 0x7F,
    0x03, 0x2F, 0x25, 0x50, 0x21, 0x2E, 0xBC, 0xF0, 0x21, 0x2D, 0x01, 0x2E, 0x01, 0xF0, 0x0E, 0xBC,
    0x27, 0x5A, 0x0E, 0xB8, 0x36, 0x30, 0x30, 0x04, 0x46, 0x41, 0x7F, 0x89, 0x03, 0x8B, 0x04, 0x41,
    0x68, 0xBF, 0xB4, 0x0B, 0x23, 0x58, 0xB0, 0x11, 0x16, 0x43, 0x00, 0x2E, 0x67, 0x41, 0x46, 0x41,
    0xF8, 0xBF, 0xBE, 0x0B, 0xB0, 0x11, 0x43, 0x8F, 0x16, 0x43, 0x15, 0x30, 0xE6, 0x41, 0xC7, 0x41,
    0x68, 0xBF, 0xB7, 0x0B, 0x30, 0x10, 0x00, 0x43, 0x2B, 0x2E, 0x27, 0x00, 0x25, 0x50, 0x21, 0x2E,
    0xB8, 0xF0, 0xF6, 0x6F, 0xEB, 0x6F, 0xD0, 0x6F, 0xB7, 0x6F, 0xA4, 0x6F, 0xC5, 0x6F, 0xA0, 0x5F,
    0xC8, 0x2E, 0x90, 0x50, 0xF7, 0x7F, 0x17, 0x30, 0x2F, 0x2E, 0x5F, 0xF0, 0xE6, 0x7F, 0x00, 0x2E,
    0x0D, 0x2E, 0xB9, 0xF0, 0xB7, 0x09, 0x80, 0xB3, 0x10, 0x2F, 0xD5, 0x7F, 0xC4, 0x7F, 0xB3, 0x7F,
    0xA2, 0x7F, 0x91, 0x7F, 0x80, 0x7F, 0x7B, 0x7F, 0x98, 0x2E, 0x5B, 0xB1, 0x80, 0x6F, 0x91, 0x6F,
    0xA2, 0x6F, 0xB3, 0x6F, 0xC4, 0x6F, 0xD5, 0x6F, 0x7B, 0x6F, 0x17, 0x30, 0x2F, 0x2E, 0xB9, 0xF0,
    0xE6, 0x6F, 0xF7, 0x6F, 0x70, 0x5F, 0xC8, 0x2E, 0x10, 0x50, 0x98, 0x2E, 0x72, 0xB0, 0x20, 0x26,
    0x98, 0x2E, 0xF0, 0x00, 0x98, 0x2E, 0xF8, 0x00, 0x98, 0x2E, 0xF4, 0x00, 0x2B, 0x50, 0x21, 0x2E,
    0x92, 0x00, 0x29, 0x52, 0x23, 0x2E, 0x91, 0x00, 0x2D, 0x50, 0x98, 0x2E, 0x9C, 0xB3, 0x2F, 0x50,
    0x98, 0x2E, 0x96, 0xB4, 0x31, 0x50, 0x11, 0x30, 0x01, 0x42, 0x3F, 0x80, 0xF0, 0x7F, 0x98, 0x2E,
    0x0A, 0xB0, 0xF1, 0x6F, 0x00, 0x2E, 0x00, 0x2E, 0xD0, 0x2E, 0x01, 0x2E, 0x26, 0x00, 0x00, 0xB2,
    0x14, 0x2F, 0x02, 0x30, 0x1F, 0x50, 0xF1, 0x7F, 0x25, 0x2E, 0x26, 0x00, 0x98, 0x2E, 0x8D, 0xB5,
    0x1F, 0x50, 0x98, 0x2E, 0xC2, 0xB0, 0x98, 0x2E, 0x4B, 0xB3, 0x1F, 0x50, 0x98, 0x2E, 0x9F, 0xB3,
    0x1F, 0x52, 0x98, 0x2E, 0x99, 0xB4, 0x21, 0x2E, 0x2E, 0x00, 0xF1, 0x6F, 0x01, 0x2E, 0x27, 0x00,
    0x00, 0xB2, 0x0B, 0x2F, 0x02, 0x30, 0x23, 0x50, 0xF1, 0x7F, 0x25, 0x2E, 0x27, 0x00, 0x98, 0x2E,
    0x8D, 0xB5, 0x98, 0x2E, 0x9F, 0xB2, 0x21, 0x2E, 0x4F, 0x00, 0xF1, 0x6F, 0x05, 0x2E, 0x4F, 0x00,
    0x23, 0xBD, 0x01, 0x2E, 0x2E, 0x00, 0x46, 0x86, 0x10, 0x0A, 0x40, 0x42, 0xF3, 0x7F, 0x98, 0x2E,
    0x0A, 0xB0, 0x05, 0x54, 0xF0, 0x6F, 0x03, 0x2E, 0x90, 0x00, 0x2D, 0xBD, 0x2D, 0xB9, 0x01, 0x42,
    0x0B, 0x30, 0x3A, 0x82, 0x80, 0x90, 0x37, 0x2E, 0x90, 0x00, 0xBB, 0x2F, 0x10, 0x30, 0x21, 0x2E,
    0x5F, 0xF0, 0xB8, 0x2D, 0x01, 0x2E, 0x91, 0x00, 0x01, 0x80, 0xC0, 0x2E, 0x00, 0x40, 0x0F, 0xB8,
    0x35, 0x50, 0x33, 0x52, 0x02, 0x40, 0x51, 0x0A, 0x01, 0x42, 0x09, 0x80, 0x25, 0x52, 0xC0, 0x2E,
    0x01, 0x42, 0x00, 0x2E, 0x01, 0x2E, 0x55, 0xF0, 0xC0, 0x2E, 0x21, 0x2E, 0x55, 0xF0, 0x30, 0x50,
    0x00, 0x30, 0x37, 0x56, 0x05, 0x30, 0x05, 0x2C, 0xFB, 0x7F, 0x3E, 0xBE, 0xD2, 0xBA, 0xB2, 0xB9,
    0x6C, 0x0B, 0x53, 0x0E, 0xF9, 0x2F, 0x53, 0x1A, 0x01, 0x2F, 0x4D, 0x0E, 0xF5, 0x2F, 0xD2, 0x7F,
    0x04, 0x30, 0x1F, 0x2C, 0xE1, 0x7F, 0xC5, 0x01, 0xA3, 0x03, 0x72, 0x0E, 0x03, 0x2F, 0x72, 0x1A,
    0x0F, 0x2F, 0x79, 0x0F, 0x0D, 0x2F, 0xE1, 0x6F, 0x4F, 0x04, 0x5F, 0xB9, 0xB1, 0xBF, 0xFA, 0x0B,
    0xD2, 0x6F, 0x96, 0x06, 0xB1, 0x25, 0x51, 0xBF, 0xEB, 0x7F, 0x06, 0x00, 0xB2, 0x25, 0x27, 0x03,
    0xDB, 0x7F, 0xCF, 0xBF, 0x3E, 0xBF, 0x01, 0xB8, 0xD2, 0xBA, 0x41, 0xBA, 0xB2, 0xB9, 0x07, 0x0A,
    0x6E, 0x0B, 0xC0, 0x90, 0xDF, 0x2F, 0x40, 0x91, 0xDD, 0x2F, 0xFB, 0x6F, 0xD0, 0x5F, 0xB8, 0x2E,
    0x10, 0x50, 0xFB, 0x7F, 0x21, 0x25, 0x98, 0x2E, 0x53, 0xB0, 0xFB, 0x6F, 0x21, 0x25, 0xF0, 0x5F,
    0x10, 0x25, 0x80, 0x2E, 0x0F, 0xB0, 0x83, 0x86, 0x01, 0x30, 0x00, 0x30, 0x94, 0x40, 0x24, 0x18,
    0x06, 0x00, 0x53, 0x0E, 0x4F, 0x02, 0xF9, 0x2F, 0xB8, 0x2E, 0x03, 0x30, 0x15, 0x40, 0xD9, 0x04,
    0x2B, 0x0E, 0x1D, 0x23, 0x29, 0x0F, 0x15, 0x40, 0x0C, 0x23, 0x2B, 0x0E, 0x9D, 0x23, 0x29, 0x0F,
    0x4E, 0x23, 0x00, 0x40, 0x03, 0x0E, 0xD8, 0x22, 0x01, 0x0F, 0x94, 0x42, 0x4B, 0x22, 0x95, 0x42,
    0x81, 0x42, 0xB8, 0x2E, 0x35, 0x50, 0x41, 0x30, 0x02, 0x40, 0x51, 0x0A, 0x01, 0x42, 0x18, 0x82,
    0x39, 0x50, 0x60, 0x42, 0x70, 0x3C, 0x3B, 0x54, 0x42, 0x42, 0x69, 0x82, 0x82, 0x32, 0x43, 0x40,
    0x18, 0x08, 0x02, 0x0A, 0x40, 0x42, 0x42, 0x80, 0x02, 0x3F, 0x01, 0x40, 0x10, 0x50, 0x4A, 0x08,
    0xFB, 0x7F, 0x11, 0x42, 0x0B, 0x31, 0x0B, 0x42, 0x3E, 0x80, 0xF1, 0x30, 0x01, 0x42, 0x00, 0x2E,
    0x01, 0x2E, 0x40, 0xF0, 0x1F, 0x90, 0x20, 0x2F, 0x03, 0x30, 0x3F, 0x50, 0x3D, 0x54, 0xF4, 0x34,
    0x06, 0x30, 0x43, 0x52, 0xF5, 0x32, 0x1D, 0x1A, 0xE3, 0x22, 0x18, 0x1A, 0x41, 0x58, 0xE3, 0x22,
    0x04, 0x30, 0xD5, 0x40, 0xB5, 0x0D, 0xE1, 0xBE, 0x6F, 0xBB, 0x80, 0x91, 0xA9, 0x0D, 0x01, 0x89,
    0xB5, 0x23, 0x10, 0xA1, 0xF7, 0x2F, 0xDA, 0x0E, 0xF4, 0x34, 0xEB, 0x2F, 0x01, 0x2E, 0x2F, 0x00,
    0x70, 0x1A, 0x00, 0x30, 0x21, 0x30, 0x02, 0x2C, 0x08, 0x22, 0x30, 0x30, 0x00, 0xB2, 0x06, 0x2F,
    0x21, 0x2E, 0x59, 0xF0, 0x98, 0x2E, 0x0A, 0xB0, 0x00, 0x2E, 0x00, 0x2E, 0xD0, 0x2E, 0xFB, 0x6F,
    0xF0, 0x5F, 0xB8, 0x2E, 0x03, 0x58, 0x01, 0x5A, 0x42, 0xBD, 0xAF, 0xB9, 0xC1, 0xBC, 0x54, 0xBF,
    0x1F, 0xB9, 0xEF, 0xBB, 0xCF, 0xB8, 0x9A, 0x0B, 0x10, 0x50, 0xC0, 0xB3, 0xB1, 0x0B, 0x76, 0x2F,
    0x80, 0xB3, 0x74, 0x2F, 0x0F, 0x2E, 0x50, 0x00, 0x01, 0x8C, 0xC0, 0xB3, 0x5C, 0x2F, 0xC3, 0xBF,
    0xC0, 0xB2, 0xD5, 0xBE, 0x55, 0xBA, 0xF3, 0xB9, 0x05, 0x30, 0x07, 0x30, 0x09, 0x2F, 0xF0, 0x7F,
    0x00, 0x2E, 0x00, 0x40, 0x0F, 0x2E, 0x53, 0x00, 0x07, 0x04, 0x00, 0xA8, 0xE8, 0x05, 0xC7, 0x23,
    0xF0, 0x6F, 0x80, 0xB2, 0x02, 0x30, 0x09, 0x2F, 0xF7, 0x7F, 0x00, 0x2E, 0x82, 0x41, 0x0F, 0x2E,
    0x54, 0x00, 0x97, 0x04, 0x80, 0xA8, 0xEA, 0x05, 0x97, 0x22, 0xF7, 0x6F, 0x40, 0xB2, 0x09, 0x2F,
    0x02, 0x82, 0x00, 0x2E, 0x41, 0x40, 0x0B, 0x2E, 0x55, 0x00, 0x4D, 0x04, 0x05, 0x30, 0x40, 0xA8,
    0x69, 0x05, 0x4D, 0x23, 0x7C, 0x0F, 0x11, 0x30, 0x17, 0x30, 0x05, 0x2F, 0x54, 0x0F, 0x03, 0x2F,
    0x6C, 0x0F, 0x17, 0x30, 0x00, 0x2F, 0x07, 0x30, 0xC0, 0x91, 0x02, 0x30, 0x0B, 0x2F, 0x03, 0x2E,
    0x52, 0x00, 0x41, 0x82, 0x25, 0x2E, 0x51, 0x00, 0xCB, 0x0E, 0x23, 0x2E, 0x52, 0x00, 0x0D, 0x2F,
    0x25, 0x2E, 0x56, 0x00, 0x0B, 0x2D, 0x09, 0x2E, 0x51, 0x00, 0x21, 0x29, 0x25, 0x2E, 0x52, 0x00,
    0xE3, 0x0E, 0x29, 0x2E, 0x51, 0x00, 0x01, 0x2F, 0x23, 0x2E, 0x56, 0x00, 0x03, 0x2E, 0x56, 0x00,
    0x40, 0xB2, 0x21, 0x2F, 0x00, 0x40, 0x21, 0x2E, 0x53, 0x00, 0x45, 0x50, 0x91, 0x41, 0x11, 0x42,
    0x00, 0x2E, 0x81, 0x41, 0x01, 0x42, 0x18, 0x2D, 0x11, 0x30, 0x23, 0x2E, 0x50, 0x00, 0x00, 0x40,
    0x21, 0x2E, 0x53, 0x00, 0x45, 0x50, 0x91, 0x41, 0x11, 0x42, 0x01, 0x30, 0x82, 0x41, 0x02, 0x42,
    0x23, 0x2E, 0x51, 0x00, 0x23, 0x2E, 0x52, 0x00, 0x23, 0x2E, 0x56, 0x00, 0x05, 0x2D, 0x00, 0x30,
    0x21, 0x2E, 0x50, 0x00, 0x21, 0x2E, 0x56, 0x00, 0x01, 0x2E, 0x56, 0x00, 0x00, 0x90, 0x20, 0x30,
    0x02, 0x2F, 0x21, 0x2E, 0x5F, 0xF0, 0x05, 0x2D, 0x03, 0x2E, 0x90, 0x00, 0x08, 0x0A, 0x21, 0x2E,
    0x90, 0x00, 0xF0, 0x5F, 0xB8, 0x2E, 0x30, 0x50, 0xFB, 0x7F, 0x98, 0x2E, 0x84, 0xB2, 0x47, 0x58,
    0x00, 0x2E, 0x10, 0x43, 0x01, 0x43, 0x3A, 0x8B, 0x98, 0x2E, 0xE5, 0xB1, 0x00, 0x2E, 0x41, 0x41,
    0x40, 0xB2, 0x43, 0x2F, 0x04, 0x83, 0x01, 0x2E, 0x5C, 0x00, 0x42, 0x40, 0x77, 0x82, 0x02, 0x04,
    0x00, 0xAC, 0x40, 0x42, 0x01, 0x2F, 0x21, 0x2E, 0x58, 0x00, 0x50, 0x40, 0x52, 0x40, 0x02, 0x0F,
    0x02, 0x30, 0x01, 0x2F, 0x00, 0xAC, 0x01, 0x2F, 0x25, 0x2E, 0x58, 0x00, 0x7E, 0x88, 0x06, 0x85,
    0x85, 0x86, 0xC5, 0x80, 0x41, 0x40, 0x04, 0x41, 0x4C, 0x04, 0x05, 0x8A, 0x82, 0x40, 0xC3, 0x40,
    0x04, 0x40, 0xE5, 0x7F, 0xD1, 0x7F, 0x98, 0x2E, 0xB1, 0xB1, 0xE5, 0x6F, 0x72, 0x83, 0x45, 0x84,
    0x85, 0x86, 0xC5, 0x8C, 0xC4, 0x40, 0x83, 0x40, 0x42, 0x40, 0xD1, 0x6F, 0x40, 0x43, 0xE6, 0x7F,
    0x98, 0x2E, 0xB1, 0xB1, 0xE2, 0x6F, 0xD1, 0x6F, 0x80, 0x42, 0xB2, 0x84, 0x85, 0x86, 0xC5, 0x88,
    0x05, 0x81, 0x82, 0x40, 0xC3, 0x40, 0x04, 0x41, 0xE0, 0x7F, 0x98, 0x2E, 0xB1, 0xB1, 0xE1, 0x6F,
    0x16, 0x30, 0x40, 0x42, 0x98, 0x2E, 0x2D, 0xB2, 0x2D, 0x2E, 0x5E, 0xF0, 0xFB, 0x6F, 0xD0, 0x5F,
    0xB8, 0x2E, 0x01, 0x2E, 0x5B, 0x00, 0x20, 0x50, 0x30, 0x8A, 0xF5, 0x7F, 0x17, 0x30, 0xF8, 0x15,
    0x05, 0x31, 0x89, 0x17, 0x8F, 0x0F, 0x68, 0x05, 0xE3, 0x7F, 0x10, 0x2F, 0x40, 0xA4, 0x0C, 0x2F,
    0xDA, 0x04, 0x19, 0x18, 0x00, 0xB2, 0x07, 0x2F, 0x10, 0xA0, 0x02, 0x2F, 0xF1, 0x6F, 0x04, 0x2C,
    0xB9, 0x11, 0x70, 0x12, 0xFD, 0x14, 0x8B, 0x0B, 0x96, 0x00, 0x15, 0x2C, 0x02, 0x25, 0xA3, 0x04,
    0xCF, 0x16, 0x4F, 0x04, 0xF3, 0x06, 0x0A, 0x17, 0x51, 0x18, 0xE1, 0x18, 0x00, 0xB2, 0xDA, 0x18,
    0x07, 0x2F, 0x10, 0xA0, 0x02, 0x2F, 0xF2, 0x6F, 0x04, 0x2C, 0xBA, 0x11, 0xB0, 0x12, 0x7D, 0x14,
    0x91, 0x0B, 0xE2, 0x6F, 0x16, 0x00, 0xE0, 0x5F, 0xB8, 0x2E, 0x05, 0x50, 0x0D, 0xBC, 0x0D, 0xB8,
    0x10, 0x50, 0xF0, 0x7F, 0x00, 0x2E, 0xF0, 0x6F, 0x03, 0x2E, 0x57, 0x00, 0x08, 0x1A, 0x3A, 0x2F,
    0xF1, 0x6F, 0x43, 0xB2, 0x23, 0x2E, 0x57, 0x00, 0x49, 0x50, 0x2D, 0x2F, 0x42, 0xB2, 0x23, 0x2F,
    0x41, 0xB2, 0x19, 0x2F, 0x44, 0xB2, 0x0F, 0x2F, 0x45, 0xB2, 0x05, 0x2F, 0x01, 0x30, 0x11, 0x42,
    0x01, 0x42, 0x3E, 0x80, 0x28, 0x2C, 0x01, 0x42, 0x71, 0x31, 0x11, 0x42, 0x52, 0x30, 0x3E, 0x82,
    0x02, 0x42, 0x23, 0x32, 0x20, 0x2C, 0x43, 0x42, 0xE1, 0x32, 0x11, 0x42, 0x62, 0x30, 0x3E, 0x82,
    0x02, 0x42, 0x63, 0x34, 0x18, 0x2C, 0x43, 0x42, 0x31, 0x37, 0x11, 0x42, 0x62, 0x30, 0x3E, 0x82,
    0x02, 0x42, 0x63, 0x34, 0x10, 0x2C, 0x43, 0x42, 0x01, 0x32, 0x11, 0x42, 0x52, 0x30, 0x3E, 0x82,
    0x02, 0x42, 0x23, 0x32, 0x08, 0x2C, 0x43, 0x42, 0x61, 0x31, 0x11, 0x42, 0x41, 0x30, 0x01, 0x42,
    0x3E, 0x80, 0x11, 0x31, 0x01, 0x42, 0xF0, 0x5F, 0xB8, 0x2E, 0x4D, 0x52, 0x3B, 0x50, 0x54, 0x40,
    0x4B, 0x54, 0xE0, 0x08, 0x83, 0x42, 0x81, 0x86, 0x52, 0x40, 0x48, 0xBA, 0x50, 0x09, 0xD4, 0x42,
    0xC5, 0x42, 0xC2, 0x86, 0x41, 0x40, 0x08, 0x08, 0xD0, 0x42, 0x98, 0xB8, 0xC1, 0x42, 0xA8, 0xB8,
    0xFE, 0x80, 0xC0, 0x2E, 0x01, 0x42, 0x00, 0x2E, 0x51, 0x52, 0x10, 0x50, 0x52, 0x40, 0xFB, 0x7F,
    0x44, 0x80, 0x4B, 0x40, 0x12, 0x42, 0x0B, 0x42, 0x37, 0x80, 0x05, 0x82, 0x0B, 0x40, 0x4B, 0x42,
    0x7C, 0x80, 0x05, 0x82, 0x0B, 0x40, 0x4B, 0x42, 0x7C, 0x80, 0x05, 0x82, 0x00, 0x40, 0x40, 0x42,
    0x77, 0x80, 0x00, 0x2E, 0x11, 0x40, 0x04, 0x84, 0x0B, 0x40, 0x91, 0x42, 0xB7, 0x80, 0x05, 0x82,
    0x00, 0x40, 0x40, 0x42, 0x7C, 0x80, 0x8B, 0x42, 0x05, 0x82, 0x0B, 0x40, 0x4B, 0x42, 0x7C, 0x80,
    0x05, 0x82, 0x00, 0x40, 0x40, 0x42, 0x7C, 0x8C, 0x98, 0x2E, 0x84, 0xB2, 0x4F, 0x54, 0x90, 0x43,
    0x81, 0x43, 0xBC, 0x83, 0x95, 0x40, 0x93, 0x40, 0x90, 0x40, 0x94, 0x40, 0x38, 0xBF, 0x93, 0x40,
    0x48, 0xBE, 0x75, 0x0B, 0x82, 0x40, 0x20, 0x0A, 0x55, 0x42, 0x28, 0xBD, 0x50, 0x42, 0x13, 0x0A,
    0xFB, 0x6F, 0xC0, 0x2E, 0x40, 0x42, 0xF0, 0x5F, 0x53, 0x52, 0x00, 0x2E, 0x64, 0x40, 0x62, 0x40,
    0x40, 0x40, 0x00, 0x90, 0xA8, 0xB8, 0xA8, 0xBD, 0x61, 0x0A, 0x18, 0x0A, 0x0E, 0x2F, 0x0B, 0x2E,
    0x27, 0xF0, 0x40, 0x91, 0x06, 0x2F, 0x05, 0x2E, 0x28, 0xF0, 0x62, 0x1A, 0x61, 0x22, 0xC0, 0x2E,
    0xF2, 0x3F, 0x10, 0x22, 0x55, 0x1A, 0x3B, 0x58, 0x9C, 0x0A, 0x10, 0x22, 0xB8, 0x2E, 0x03, 0x2E,
    0x91, 0x00, 0x41, 0x80, 0xA0, 0x50, 0x00, 0x40, 0x2A, 0x25, 0xB6, 0x84, 0x83, 0xBD, 0xBF, 0xB9,
    0x02, 0xBE, 0x83, 0x42, 0x4F, 0xBA, 0x81, 0xBE, 0xF2, 0x7F, 0x5F, 0xB9, 0x8F, 0xB9, 0x74, 0x7F,
    0xEB, 0x7F, 0xC0, 0xB2, 0x82, 0x7F, 0x0B, 0x30, 0x7F, 0x2F, 0x62, 0x6F, 0x80, 0x90, 0x05, 0x2F,
    0x72, 0x6F, 0x80, 0x90, 0x02, 0x2F, 0x82, 0x6F, 0x80, 0xB2, 0x76, 0x2F, 0x05, 0x2E, 0x70, 0x00,
    0x80, 0x90, 0x08, 0x2F, 0x55, 0x54, 0x03, 0x30, 0x59, 0x58, 0x15, 0x30, 0x93, 0x42, 0x54, 0x0E,
    0xFC, 0x2F, 0x2B, 0x2E, 0x70, 0x00, 0x42, 0x40, 0xDB, 0x7F, 0x0B, 0x30, 0x42, 0x82, 0x21, 0xBD,
    0x04, 0xBC, 0x84, 0xB9, 0xCB, 0x7F, 0x21, 0xB9, 0x41, 0x40, 0x0B, 0x30, 0xB2, 0x7F, 0x94, 0xBC,
    0x57, 0x50, 0x55, 0x58, 0xAB, 0x7F, 0x94, 0xB8, 0x93, 0x04, 0x23, 0x5A, 0xF3, 0x6F, 0x00, 0x2E,
    0xD6, 0x40, 0xF3, 0x7F, 0x80, 0x91, 0x03, 0x30, 0x02, 0x2F, 0x00, 0x2E, 0x44, 0x2C, 0x03, 0x43,
    0x46, 0x41, 0x80, 0xA9, 0xDE, 0x05, 0xB7, 0x23, 0x07, 0x41, 0xC0, 0xB3, 0x2D, 0x2F, 0x47, 0x41,
    0xC0, 0xA1, 0x17, 0x30, 0xFB, 0x22, 0xF2, 0x0E, 0x0B, 0x40, 0x02, 0x2F, 0x6B, 0x25, 0x33, 0x1A,
    0x02, 0x2F, 0x03, 0x30, 0x30, 0x2C, 0x03, 0x43, 0x03, 0x41, 0xDF, 0x28, 0x03, 0x43, 0xD9, 0x0E,
    0x29, 0x2F, 0xA3, 0x6F, 0xC0, 0x90, 0x26, 0x2F, 0xD5, 0x7F, 0x13, 0x30, 0xC6, 0x6F, 0x94, 0x7F,
    0x5B, 0x25, 0x1E, 0x15, 0xD3, 0xBE, 0xA4, 0x7F, 0x2C, 0x0B, 0x55, 0x5A, 0xAE, 0x01, 0x59, 0x5E,
    0x0B, 0x30, 0x2E, 0x1A, 0x00, 0x2F, 0x4B, 0x43, 0x41, 0x8B, 0x29, 0x2E, 0x71, 0x00, 0x6F, 0x0E,
    0xF7, 0x2F, 0xD5, 0x6F, 0x94, 0x6F, 0x0F, 0x2C, 0xD3, 0x7F, 0xB3, 0x6F, 0xF3, 0x0E, 0x0A, 0x2F,
    0x13, 0x30, 0x03, 0x43, 0x03, 0x30, 0x46, 0x41, 0x80, 0xA1, 0x02, 0x2F, 0x00, 0x2E, 0x03, 0x2C,
    0x03, 0x42, 0x13, 0x30, 0x03, 0x42, 0x41, 0x8B, 0xC3, 0x6F, 0xC1, 0x86, 0x01, 0x89, 0x01, 0x80,
    0xC3, 0xA2, 0xC3, 0x7F, 0xAA, 0x2F, 0x00, 0x2E, 0x03, 0x2D, 0xDB, 0x7F, 0x37, 0x2E, 0x70, 0x00,
    0xD1, 0x6F, 0x40, 0x90, 0x40, 0x30, 0x02, 0x2F, 0x21, 0x2E, 0x5F, 0xF0, 0x05, 0x2D, 0x03, 0x2E,
    0x90, 0x00, 0x08, 0x0A, 0x21, 0x2E, 0x90, 0x00, 0xEB, 0x6F, 0xF1, 0x30, 0x01, 0x2E, 0x71, 0x00,
    0xC0, 0x2E, 0x60, 0x5F, 0x01, 0x08, 0x03, 0x2E, 0x92, 0x00, 0x41, 0x80, 0x40, 0x50, 0x00, 0x40,
    0x03, 0xBD, 0x2F, 0xB9, 0x80, 0xB2, 0xFB, 0x7F, 0x35, 0x2F, 0x05, 0x2E, 0x78, 0x00, 0x80, 0x90,
    0x05, 0x2F, 0x03, 0x30, 0x12, 0x30, 0x25, 0x2E, 0x78, 0x00, 0x27, 0x2E, 0x79, 0x00, 0x42, 0x86,
    0x42, 0x40, 0xC1, 0x40, 0xA1, 0xBD, 0x04, 0xBD, 0x24, 0xB9, 0xE2, 0x7F, 0x94, 0xBC, 0x14, 0xB8,
    0xC0, 0x7F, 0xB1, 0xB9, 0x1F, 0x52, 0xD3, 0x7F, 0x98, 0x2E, 0x48, 0xB0, 0xE1, 0x6F, 0xD2, 0x6F,
    0x51, 0x28, 0x41, 0x0F, 0x11, 0x30, 0x0C, 0x2F, 0x42, 0x0E, 0x07, 0x2E, 0x79, 0x00, 0x19, 0x28,
    0x04, 0x2F, 0xC0, 0xA6, 0x08, 0x2F, 0x21, 0x2E, 0x79, 0x00, 0x06, 0x2D, 0x21, 0x2E, 0x79, 0x00,
    0x03, 0x2D, 0x00, 0x30, 0x21, 0x2E, 0x79, 0x00, 0x05, 0x2E, 0x79, 0x00, 0xC0, 0x6F, 0x50, 0x0F,
    0x00, 0x30, 0x04, 0x2C, 0x08, 0x22, 0x00, 0x30, 0x21, 0x2E, 0x78, 0x00, 0x00, 0x90, 0x80, 0x30,
    0x02, 0x2F, 0x21, 0x2E, 0x5F, 0xF0, 0x05, 0x2D, 0x03, 0x2E, 0x90, 0x00, 0x08, 0x0A, 0x21, 0x2E,
    0x90, 0x00, 0xFB, 0x6F, 0xC0, 0x5F, 0xB8, 0x2E, 0xC0, 0x2E, 0x21, 0x2E, 0x93, 0x00, 0x03, 0x2E,
    0x93, 0x00, 0x55, 0x40, 0x44, 0x40, 0x42, 0xBD, 0xAF, 0xB9, 0xC1, 0xBC, 0x54, 0xBF, 0x1F, 0xB9,
    0xEF, 0xBB, 0xCF, 0xB8, 0x9A, 0x0B, 0x10, 0x50, 0xC0, 0xB3, 0xB1, 0x0B, 0x5B, 0x2F, 0x80, 0xB3,
    0x59, 0x2F, 0x0F, 0x2E, 0x7A, 0x00, 0x01, 0x8C, 0xC0, 0xB3, 0x45, 0x2F, 0xC3, 0xBF, 0xC0, 0xB2,
    0xD5, 0xBE, 0x55, 0xBA, 0xF3, 0xB9, 0x07, 0x30, 0x05, 0x30, 0x09, 0x2F, 0xF0, 0x7F, 0x00, 0x2E,
    0x00, 0x40, 0x0B, 0x2E, 0x7C, 0x00, 0x05, 0x04, 0x00, 0xA8, 0x78, 0x05, 0x45, 0x23, 0xF0, 0x6F,
    0x80, 0xB2, 0x07, 0x2F, 0x82, 0x41, 0x0F, 0x2E, 0x7D, 0x00, 0x97, 0x04, 0x07, 0x30, 0x80, 0xA8,
    0xFA, 0x05, 0xD7, 0x23, 0x40, 0xB2, 0x01, 0x30, 0x02, 0x30, 0x0A, 0x2F, 0x02, 0x84, 0xF7, 0x7F,
    0x00, 0x2E, 0x82, 0x40, 0x0F, 0x2E, 0x7E, 0x00, 0x97, 0x04, 0x80, 0xA8, 0xCA, 0x05, 0x97, 0x22,
    0xF7, 0x6F, 0xEC, 0x0F, 0x03, 0x2F, 0xFC, 0x0F, 0x01, 0x2F, 0x54, 0x0E, 0x02, 0x2F, 0x23, 0x2E,
    0x7B, 0x00, 0x08, 0x2D, 0x09, 0x2E, 0x7B, 0x00, 0x12, 0x30, 0x22, 0x29, 0x63, 0x0F, 0x29, 0x2E,
    0x7B, 0x00, 0x51, 0x22, 0x00, 0x40, 0x21, 0x2E, 0x7C, 0x00, 0x5B, 0x50, 0x92, 0x41, 0x12, 0x42,
    0x00, 0x2E, 0x82, 0x41, 0x13, 0x2C, 0x02, 0x42, 0x11, 0x30, 0x23, 0x2E, 0x7A, 0x00, 0x00, 0x40,
    0x21, 0x2E, 0x7C, 0x00, 0x5B, 0x50, 0x91, 0x41, 0x11, 0x42, 0x01, 0x30, 0x82, 0x41, 0x02, 0x42,
    0x23, 0x2E, 0x7B, 0x00, 0x03, 0x2D, 0x01, 0x30, 0x23, 0x2E, 0x7A, 0x00, 0x40, 0x90, 0x00, 0x32,
    0x02, 0x2F, 0x21, 0x2E, 0x5F, 0xF0, 0x05, 0x2D, 0x03, 0x2E, 0x90, 0x00, 0x08, 0x0A, 0x21, 0x2E,
    0x90, 0x00, 0xF0, 0x5F, 0xB8, 0x2E, 0x01, 0x25, 0x20, 0x50, 0xE0, 0x7F, 0xFB, 0x7F, 0x20, 0x25,
    0x5D, 0x52, 0x98, 0x2E, 0x5D, 0xB0, 0xE1, 0x6F, 0x44, 0x80, 0x3E, 0x84, 0x00, 0x40, 0xA3, 0x40,
    0xA4, 0x40, 0x24, 0x18, 0x85, 0x40, 0x46, 0x25, 0xB7, 0x25, 0x2D, 0x18, 0x83, 0x84, 0x34, 0x01,
    0x5B, 0x25, 0x7D, 0x03, 0x1B, 0x18, 0xCA, 0xB9, 0xD6, 0xBE, 0xEB, 0x0A, 0x82, 0x40, 0x57, 0x25,
    0x56, 0x18, 0x04, 0xBC, 0xEA, 0x18, 0x98, 0x00, 0x46, 0xBE, 0x57, 0x0E, 0x0E, 0x2F, 0x57, 0x1A,
    0x01, 0x2F, 0x66, 0x0E, 0x0A, 0x2F, 0xB8, 0x00, 0x53, 0x0E, 0x00, 0x30, 0x07, 0x2F, 0x53, 0x1A,
    0x01, 0x2F, 0x74, 0x0E, 0x03, 0x2F, 0x45, 0x80, 0x02, 0x2C, 0x00, 0x40, 0x10, 0x30, 0xFB, 0x6F,
    0xE0, 0x5F, 0xB8, 0x2E, 0x41, 0xB2, 0x01, 0x2F, 0x00, 0x2E, 0x02, 0x2D, 0x23, 0x2C, 0x00, 0x30,
    0x42, 0xB2, 0x01, 0x2F, 0x43, 0x90, 0x36, 0x2F, 0x42, 0x25, 0x7E, 0x82, 0x15, 0x41, 0xD7, 0x40,
    0x10, 0x41, 0xD6, 0x40, 0xEF, 0x05, 0x46, 0x05, 0x00, 0x30, 0x04, 0x41, 0xC0, 0xA9, 0x87, 0x05,
    0xC3, 0x40, 0xBE, 0x23, 0xE3, 0x04, 0x40, 0xA9, 0x05, 0x05, 0x2C, 0x23, 0x5F, 0x5E, 0x79, 0x01,
    0xC0, 0xA8, 0x43, 0x04, 0x45, 0x41, 0x59, 0x22, 0x75, 0x0F, 0x1A, 0x2F, 0x65, 0x0F, 0x18, 0x2F,
    0x4D, 0x0F, 0x16, 0x2F, 0x93, 0x40, 0xC0, 0xA8, 0x03, 0x05, 0x91, 0x40, 0xDC, 0x22, 0x40, 0xA8,
    0x01, 0x05, 0x82, 0x40, 0x4C, 0x22, 0x80, 0xA8, 0x02, 0x05, 0x94, 0x22, 0x61, 0x58, 0x5C, 0x0F,
    0x05, 0x2F, 0x61, 0x56, 0x4B, 0x0F, 0x02, 0x2F, 0x61, 0x52, 0xD1, 0x0E, 0x05, 0x2F, 0x10, 0x30,
    0xB8, 0x2E, 0x10, 0x30, 0xB8, 0x2E, 0x00, 0x30, 0xB8, 0x2E, 0xB8, 0x2E, 0xC0, 0x2E, 0x21, 0x2E,
    0x94, 0x00, 0x07, 0x2E, 0x94, 0x00, 0xC0, 0x40, 0x0F, 0xBD, 0x70, 0x50, 0x2F, 0xB9, 0xF1, 0x7F,
    0x80, 0xB2, 0xEB, 0x7F, 0x90, 0x2E, 0x85, 0xB5, 0x52, 0x40, 0xC1, 0x88, 0x8A, 0xBE, 0xDE, 0xB9,
    0xD1, 0x7F, 0x8C, 0xBC, 0x07, 0x41, 0xC3, 0x7F, 0x9E, 0xB9, 0x63, 0x58, 0x23, 0x01, 0x84, 0xBD,
    0x75, 0xBF, 0x01, 0x30, 0xBA, 0xBB, 0xB2, 0x7F, 0x80, 0xA8, 0x4A, 0x05, 0xE5, 0xB9, 0x95, 0x22,
    0x04, 0x41, 0xA7, 0x7F, 0x22, 0x2A, 0x53, 0x05, 0x8E, 0x16, 0x17, 0x30, 0x97, 0x08, 0xB2, 0x01,
    0xB6, 0x25, 0x25, 0x2A, 0xD2, 0x6F, 0x72, 0x25, 0x5B, 0x25, 0xD2, 0x41, 0xD1, 0xB6, 0xEB, 0x28,
    0x97, 0x7F, 0x4A, 0x05, 0x80, 0xA8, 0xC7, 0x41, 0x55, 0x23, 0xC0, 0xA9, 0x4F, 0x04, 0x79, 0x22,
    0xCE, 0x17, 0x14, 0x30, 0xFC, 0x09, 0xF7, 0x01, 0x0E, 0xBF, 0xF1, 0xB7, 0x6F, 0xBB, 0x01, 0x2E,
    0x87, 0x00, 0xAF, 0x0F, 0x03, 0x2F, 0xB4, 0x6F, 0x00, 0xAD, 0x14, 0x30, 0x1E, 0x2F, 0xAF, 0x0F,
    0x02, 0x2F, 0xB7, 0x6F, 0xC0, 0xA1, 0x15, 0x2F, 0xAB, 0x0E, 0x01, 0x2F, 0x80, 0xA0, 0x0C, 0x2F,
    0xAB, 0x0E, 0x33, 0x30, 0x01, 0x2F, 0x80, 0xAC, 0x03, 0x2F, 0x83, 0x08, 0x25, 0x2E, 0x88, 0x00,
    0x10, 0x2D, 0x02, 0x30, 0x25, 0x2E, 0x88, 0x00, 0x0C, 0x2D, 0x22, 0x30, 0x25, 0x2E, 0x88, 0x00,
    0x08, 0x2C, 0x33, 0x30, 0x33, 0x30, 0x27, 0x2E, 0x88, 0x00, 0x03, 0x2D, 0x29, 0x2E, 0x88, 0x00,
    0x33, 0x30, 0x80, 0xB3, 0xF2, 0x6F, 0x11, 0x2F, 0x69, 0x5A, 0x4D, 0x0F, 0x03, 0x2F, 0x82, 0xB8,
    0x23, 0x2E, 0x89, 0x00, 0x0B, 0x2D, 0x82, 0x82, 0x00, 0x2E, 0x41, 0x40, 0x40, 0xAC, 0x02, 0x2F,
    0x29, 0x2E, 0x89, 0x00, 0x03, 0x2D, 0x01, 0x30, 0x23, 0x2E, 0x89, 0x00, 0x03, 0x2E, 0x88, 0x00,
    0x4B, 0x08, 0x09, 0x2E, 0x89, 0x00, 0xC2, 0xBD, 0x0B, 0x0B, 0x04, 0x1A, 0x29, 0x2E, 0x8A, 0x00,
    0x90, 0x6F, 0x05, 0x30, 0x39, 0x2F, 0xC1, 0x6F, 0x40, 0xA6, 0x36, 0x2F, 0xC1, 0x6F, 0x43, 0x90,
    0x03, 0x30, 0x0F, 0x2F, 0x0F, 0x2E, 0x8F, 0x00, 0x15, 0x30, 0xBD, 0x29, 0x0F, 0x2E, 0x8E, 0x00,
    0x3C, 0x1A, 0x2D, 0x2E, 0x8F, 0x00, 0x01, 0x2F, 0x27, 0x2E, 0x8F, 0x00, 0x09, 0x2E, 0x8F, 0x00,
    0x05, 0xA3, 0x6B, 0x23, 0x40, 0x91, 0x06, 0x2F, 0x65, 0x56, 0x98, 0x2E, 0x52, 0xB4, 0x50, 0x25,
    0xF2, 0x6F, 0x90, 0x6F, 0x03, 0x30, 0x40, 0x91, 0x17, 0x2F, 0x67, 0x52, 0x82, 0x40, 0x52, 0x42,
    0x00, 0x2E, 0xD4, 0x6F, 0xA2, 0x6F, 0x04, 0x41, 0x54, 0x42, 0x00, 0x2E, 0x00, 0x40, 0x50, 0x42,
    0x52, 0x42, 0x43, 0x42, 0x7C, 0x82, 0xF1, 0x7F, 0x98, 0x2E, 0x1B, 0xB4, 0xF2, 0x6F, 0x85, 0x84,
    0x01, 0xB2, 0x11, 0x30, 0x03, 0x30, 0x80, 0x42, 0x4B, 0x23, 0x03, 0x2E, 0x8A, 0x00, 0x23, 0x2E,
    0x8E, 0x00, 0x92, 0x6F, 0xBE, 0x84, 0x41, 0x91, 0x03, 0x2E, 0x87, 0x00, 0x01, 0x2F, 0x23, 0x2E,
    0x8A, 0x00, 0x01, 0x2E, 0x8A, 0x00, 0x41, 0x1A, 0x01, 0x31, 0x02, 0x2F, 0x23, 0x2E, 0x5F, 0xF0,
    0x05, 0x2D, 0x01, 0x2E, 0x90, 0x00, 0x41, 0x0A, 0x23, 0x2E, 0x90, 0x00, 0x65, 0x52, 0x90, 0x40,
    0x50, 0x42, 0x00, 0x2E, 0x90, 0x40, 0x50, 0x42, 0x00, 0x2E, 0x82, 0x40, 0x42, 0x42, 0x00, 0x2E,
    0x05, 0x2E, 0x8A, 0x00, 0x25, 0x2E, 0x87, 0x00, 0x03, 0x2D, 0x02, 0x31, 0x25, 0x2E, 0x5F, 0xF0,
    0xEB, 0x6F, 0x90, 0x5F, 0x01, 0x2E, 0x8A, 0x00, 0xB8, 0x2E, 0x60, 0x50, 0x03, 0x2E, 0x0E, 0x01,
    0xE0, 0x7F, 0xF1, 0x7F, 0xDB, 0x7F, 0x30, 0x30, 0x6B, 0x54, 0x0A, 0x1A, 0x28, 0x2F, 0x1A, 0x25,
    0x7A, 0x82, 0x00, 0x30, 0x43, 0x30, 0x32, 0x30, 0x05, 0x30, 0x04, 0x30, 0xF6, 0x6F, 0xF2, 0x09,
    0xFC, 0x13, 0xC2, 0xAB, 0xB3, 0x09, 0xEF, 0x23, 0x80, 0xB3, 0xE6, 0x6F, 0xB7, 0x01, 0x00, 0x2E,
    0x8B, 0x41, 0x4B, 0x42, 0x03, 0x2F, 0x46, 0x40, 0x86, 0x17, 0x81, 0x8D, 0x46, 0x42, 0x41, 0x8B,
    0x23, 0xBD, 0xB3, 0xBD, 0x03, 0x89, 0x41, 0x82, 0x07, 0x0C, 0x43, 0xA3, 0xE6, 0x2F, 0xE1, 0x6F,
    0xA2, 0x6F, 0x52, 0x42, 0x00, 0x2E, 0xB2, 0x6F, 0x52, 0x42, 0x00, 0x2E, 0xC2, 0x6F, 0x42, 0x42,
    0x03, 0xB2, 0x06, 0x2F, 0x01, 0x2E, 0x59, 0xF0, 0x01, 0x32, 0x01, 0x0A, 0x21, 0x2E, 0x59, 0xF0,
    0x06, 0x2D, 0x01, 0x2E, 0x59, 0xF0, 0xF1, 0x3D, 0x01, 0x08, 0x21, 0x2E, 0x59, 0xF0, 0xDB, 0x6F,
    0xA0, 0x5F, 0xB8, 0x2E, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00
};

static const U1 *   u1p_s_GYROINFO_TOP_ADR  = u1_sp_GYRO_CONFIG;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* void            vd_g_GyroInit(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_GyroInit(void)
{
    /* I2C書込み/読出し用バッファクリア */
    vd_g_GyroSysPwrInit();

    /* 制御管理バッファ初期化 */
    st_s_gyro_ctrl.u1_mod       = (U1)GYRO_MODE_MAX;
    st_s_gyro_ctrl.u1_event     = (U1)GYRO_EVENT_MAX;
    st_s_gyro_ctrl.u1_dev_mode  = (U1)GYRO_DEV_MODE_SUSPEND;

    /* 各種カウンタクリア */
    u1_s_errcnt_l               = (U1)0U;
    u1_s_errcnt_j               = (U1)0U;
    u1_s_cnt_shutdn             = (U1)0U;
    u1_s_cnt_g_read             = (U1)0U;
    u2_s_cnt_diff_verif         = (U2)0U;
    u1_s_gyro_uploadcfg_rtrycnt = (U1)0U;

    /* その他バッファを初期化 */
    dl_s_gyro_v33perion_sts     = (Dio_LevelType)GYRO_DIO_LOW;
    u1_s_gyro_v33OffFlg         = (U1)FALSE;
    u1_s_gyro_sysoffflg         = (U1)FALSE;
    u2_s_gyro_regstep           = (U2)0U;
    vd_s_GyroDevMemset(&st_s_gyro_accdat_pls, (U1)0U, (U4)sizeof(st_s_gyro_accdat_pls));
    vd_s_GyroDevMemset(&st_s_gyro_accdat_mns, (U1)0U, (U4)sizeof(st_s_gyro_accdat_mns));
    vd_s_GyroDevMemset(&st_s_gyro_cfgmng,     (U1)0U, (U4)sizeof(st_s_gyro_cfgmng));
    vd_s_GyroDevMemset(&st_s_gyro_accdat,     (U1)0U, (U4)sizeof(st_s_gyro_accdat));

    /* すべてのタイマを初期化 */
    u4_s_gyro_acktime           = (U4)0U;
    u4_s_gyro_linktim           = (U4)0U;
    u2_s_gyro_i2cwaittim        = (U2)0xFFFFU;

    /* シーケンス管理バッファー初期化 */
    vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);

    /* ジャイロ状態を初期化 */
    vd_s_GyroDevCtlMngModSet((U1)GYRO_MODE_UNINIT);

    /* ジャイロ状態管理の イベント・ハンドラを呼び出し */
    vd_g_GyroDevEventGo((U1)GYRO_EVENT_TASKSTUP);
}

/*===================================================================================================================================*/
/* void            vd_g_GyroMainTask(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_GyroMainTask(void)
{
    /* Bu-DET HI監視 */
    //vd_s_GyroBuDetHiCheck();      /* temporary */

    /* V33-Peri-ON状態チェック */
    vd_s_GyroV33PeriOnCheck();

    /* シーケンス実行処理 */
    vd_s_GyroDevSeqCtl();
}

/**************************↓外部端子入力監視(START)↓************************/
/*===================================================================================================================================*/
/* void            vd_s_GyroBuDetHiCheck(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroBuDetHiCheck(void)
{
    Dio_LevelType   dl_t_port;  /* Pin読み出し値 */

    dl_t_port = dl_GYRO_DIO_READ_BUDET();

    if(dl_t_port == (Dio_LevelType)GYRO_DIO_HIGH){
        vd_s_GyroBuDetHi();
    }
    else{
        /* do nothing */
    }
}

/*===================================================================================================================================*/
/* void            vd_s_GyroBuDetHi(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroBuDetHi(void)
{
    /* ジャイロ強制終了処理 */
    vd_s_GyroDevForceEnd();

    /* ジャイロ状態を初期化 */
    vd_s_GyroDevCtlMngModSet((U1)GYRO_MODE_UNINIT);
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroV33PeriOnCheck(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroV33PeriOnCheck(void)
{
    Dio_LevelType   dl_t_sts;

    /* V33-Peri-ON端子状態取得処理 */
    dl_t_sts    = dl_GYRO_DIO_READ_V33PERI();

    /* V33-Peri-ON端子状態変化処理 */
    if(dl_t_sts != dl_s_gyro_v33perion_sts){
        if(dl_t_sts == (Dio_LevelType)GYRO_DIO_HIGH){
            /* V33-Peri-ON OFF->ON処理 */

        }
        else{
            /* V33-Peri-ON ON->OFF処理 */
            /* 起動中にV33-PERI-ON H→Lイベント発生フラグON */
            u1_s_gyro_v33OffFlg = (U1)TRUE;
        }
    }

    /* V33-Peri-ON端子イベント処理 */
    if(dl_t_sts == (Dio_LevelType)GYRO_DIO_HIGH){
        /* ジャイロ状態管理の イベント・ハンドラを呼び出し */
        vd_g_GyroDevEventGo((U1)GYRO_EVENT_V33PERION_ON);
    }
    else{
        /* ジャイロ状態管理の イベント・ハンドラを呼び出し */
        vd_g_GyroDevEventGo((U1)GYRO_EVENT_V33PERION_OFF);
    }
}

/**************************↑外部端子入力監視(END)↑***************************/

/**************************↓状態遷移管理(START)↓***************************/
/*===================================================================================================================================*/
/* static void     vd_s_GyroDevCtlMngModSet(const U1 u1_a_MODE)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevCtlMngModSet(const U1 u1_a_MODE)
{
    if( (u1_a_MODE < (U1)GYRO_MODE_MAX) &&
        (st_s_gyro_ctrl.u1_mod != u1_a_MODE)){
        
        st_s_gyro_ctrl.u1_mod = u1_a_MODE;
    }
}

/*===================================================================================================================================*/
/* static U1       u1_g_GyroDevCtlMngModGet(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_GyroDevCtlMngModGet(void)
{
    /* ジャイロ状態を戻す */
    return(st_s_gyro_ctrl.u1_mod);
}

/*===================================================================================================================================*/
/* static void     vd_g_GyroDevEventGo(const U1 u1_a_EVENT)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_GyroDevEventGo(const U1 u1_a_EVENT)
{
    U1                  u1_t_mode;
    FP_GYRO_EVNT_HNDL   fp_t_handler;

    /* ジャイロモードを取得 */
    u1_t_mode   = u1_g_GyroDevCtlMngModGet();

    /* モードとイベントの範囲確認 */
    if((u1_t_mode < (U1)GYRO_MODE_MAX) && (u1_a_EVENT < (U1)GYRO_EVENT_MAX)){
        st_s_gyro_ctrl.u1_event = u1_a_EVENT;
        fp_t_handler            = fp_sp2_GYRO_EVENT_HANDLER[u1_t_mode][u1_a_EVENT];

        if(fp_t_handler != vdp_PTR_NA){
            fp_t_handler();
        }
        else{
            /* do nothing */
        }
    }
    else{
        /* do nothing */
    }
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroDevUnInitTskStup(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevUnInitTskStup(void)
{
    /* 未初期化状態・タスク起動 */

    /* GYRO状態: 起動(1)実施中へ遷移する */
    vd_s_GyroDevCtlMngModSet((U1)GYRO_MODE_STUP1_PRO);

    /* GYROシーケンス: 起動(1)を起動 */
    vd_s_GyroDevSeqSet((U1)GYRO_SEQ_STAUP1);
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroDevComErrTskStup(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevComErrTskStup(void)
{
    /* エラー状態・タスク起動 */

    /* GYRO状態: 起動(1)実施中へ遷移する */
    vd_s_GyroDevCtlMngModSet((U1)GYRO_MODE_STUP1_PRO);

    /* GYROシーケンス: 起動(1)を起動 */
    vd_s_GyroDevSeqSet((U1)GYRO_SEQ_STAUP1);
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroDevStup1CompV33PeriOnOn(void)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevStup1CompV33PeriOnOn(void)
{
    /* 起動(1)実施完了状態・V33-Peri-ON OFF->ON */

    /* 起動中にV33-PERI-ON H→Lイベント発生フラグクリア */
    u1_s_gyro_v33OffFlg = (U1)FALSE;

    /* GYRO状態: 起動(2)実施中へ遷移する */
    vd_s_GyroDevCtlMngModSet((U1)GYRO_MODE_STUP2_PRO);

    /* GYROシーケンス: 起動(2)を起動 */
    vd_s_GyroDevSeqSet((U1)GYRO_SEQ_STAUP2);
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroDevNormV33PeriOnOn(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevNormV33PeriOnOn(void)
{
    /* 通常動作中状態・V33-Peri-ON OFF->ON */

    /* 起動中にV33-PERI-ON H→Lイベント発生フラグクリア */
    u1_s_gyro_v33OffFlg = (U1)FALSE;
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroDevErrV33PeriOnOn(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevErrV33PeriOnOn(void)
{
    /* 異常停止中状態・V33-Peri-ON OFF->ON */

    /* V33-Peri-ON OFF->ON時のみ実行 */
    if(u1_s_gyro_v33OffFlg == (U1)TRUE){
        /* GYRO状態: 起動(1)実施中へ遷移する */
        vd_s_GyroDevCtlMngModSet((U1)GYRO_MODE_STUP1_PRO);

        /* GYROシーケンス: 起動(1)を起動 */
        vd_s_GyroDevSeqSet((U1)GYRO_SEQ_STAUP1);

        /* 起動中にV33-PERI-ON H→Lイベント発生フラグクリア */
        u1_s_gyro_v33OffFlg = (U1)FALSE;
    }
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroDevNormV33PeriOnOff(void)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevNormV33PeriOnOff(void)
{
    /* 通常動作中状態・V33-Peri-ON ON->OFF */

    /* GYRO状態: 終了(1)実施中へ遷移する */
    vd_s_GyroDevCtlMngModSet((U1)GYRO_MODE_SHTDN1_PRO);
    
    /* GYROシーケンス: 終了(1)を起動 */
    vd_s_GyroDevSeqSet((U1)GYRO_SEQ_SHUTDOWN1);
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroDevComSysOffWait(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevComSysOffWait(void)
{
    /* 共通状態・システムオフ(待つ) */

    /* システムオフフラグを設定 */
    u1_s_gyro_sysoffflg = (U1)TRUE;
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroDevComSysOffProc(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevComSysOffProc(void)
{
    /* 共通状態・システムオフ(実施) */

    /* タスク状態通知(シャットダウン処理完了) */
    /* 予備設計のため処理なし */
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroDevErrSysOff(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevErrSysOff(void)
{
    /* 異常停止中状態・ステムオフ */

    /* GYRO状態: 未初期化へ遷移する */
    vd_s_GyroDevCtlMngModSet((U1)GYRO_MODE_UNINIT);

    /* タスク状態通知(シャットダウン処理完了) */
    /* 予備設計のため処理なし */
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroDevStup1ProSeqComp(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevStup1ProSeqComp(void)
{
    /* 起動(1)実施中・シーケンス完了 */

    /* GYRO状態: 起動(1)実施完了へ遷移する */
    vd_s_GyroDevCtlMngModSet((U1)GYRO_MODE_STUP1_COMP);

    /* システムOFFフラグをチェック */
    if(u1_s_gyro_sysoffflg == (U1)TRUE){
        /* タスク状態通知(シャットダウン処理完了) */
        /* 予備設計のため処理なし */
    }
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroDevStup2ProSeqComp(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevStup2ProSeqComp(void)
{
    /* 起動(2)実施中・シーケンス完了 */

    /* 初期化完了通知 */
    vd_g_XspiIviSub1PowerDevInitCmpApp((U1)XSPI_IVI_POWER_GYRO_INI);

    /* GYRO状態: 通常動作中へ遷移する */
    vd_s_GyroDevCtlMngModSet((U1)GYRO_MODE_NORM);
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroDevShtdn1ProSeqComp(void)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevShtdn1ProSeqComp(void)
{
    /* 終了(1)実施中・シーケンス完了 */

    /* GYRO状態: 起動(1)実施完了へ遷移する */
    vd_s_GyroDevCtlMngModSet((U1)GYRO_MODE_STUP1_COMP);

    /* システムOFFフラグをチェック */
    if(u1_s_gyro_sysoffflg == (U1)TRUE){
        /* タスク状態通知(シャットダウン処理完了) */
        /* 予備設計のため処理なし */
    }
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroDevStup1ProErr(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevStup1ProErr(void)
{
    /* 起動(1)実施中・異常検知 */

    /* GYRO強制終了処理 */
    vd_s_GyroDevForceEnd();

    /* システムOFFフラグをチェック */
    if(u1_s_gyro_sysoffflg == (U1)TRUE){
        /* GYRO状態: 未初期化へ遷移する */
        vd_s_GyroDevCtlMngModSet((U1)GYRO_MODE_UNINIT);

        /* タスク状態通知(シャットダウン処理完了) */
        /* 予備設計のため処理なし */
    }
    else{
        /* GYRO状態: 異常停止中へ遷移する */
        vd_s_GyroDevCtlMngModSet((U1)GYRO_MODE_ERR);
    }
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroDevStup2ProErr(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevStup2ProErr(void)
{
    /* 起動(2)実施中・異常検知 */

    /* システムOFFフラグをチェック */
    if(u1_s_gyro_sysoffflg == (U1)TRUE){
        /* GYRO強制終了処理 */
        vd_s_GyroDevForceEnd();

        /* GYRO状態: 未初期化へ遷移する */
        vd_s_GyroDevCtlMngModSet((U1)GYRO_MODE_UNINIT);

        /* タスク状態通知(シャットダウン処理完了) */
        /* 予備設計のため処理なし */
    }
    else{
        /* GYRO状態: 起動(1)実施中へ遷移する */
        vd_s_GyroDevCtlMngModSet((U1)GYRO_MODE_STUP1_PRO);

        /* GYROシーケンス: 起動(1)を起動 */
        vd_s_GyroDevSeqSet((U1)GYRO_SEQ_STAUP1);
    }
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroDevComDtcErr(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevComDtcErr(void)
{
    /* 共通状態・DTC異常検知 */

    /* GYRO強制終了処理 */
    vd_s_GyroDevForceEnd();

    /* エラーカウントをクリア */
    /* ToDo：DTCなので別部分で実装 */

    /* システムOFFフラグをチェック */
    if(u1_s_gyro_sysoffflg == (U1)TRUE){
        /* GYRO状態: 未初期化へ遷移する */
        vd_s_GyroDevCtlMngModSet((U1)GYRO_MODE_UNINIT);

        /* タスク状態通知(シャットダウン処理完了) */
        /* 予備設計のため処理なし */
    }
    else{
        /* GYRO状態: 異常停止中へ遷移する */
        vd_s_GyroDevCtlMngModSet((U1)GYRO_MODE_ERR);
    }
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroDevShutDn1ProErr(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevShutDn1ProErr(void)
{
    /* 終了(1)実施中・異常検知 */

    /* GYRO強制終了処理 */
    vd_s_GyroDevForceEnd();

    /* システムOFFフラグをチェック */
    if(u1_s_gyro_sysoffflg == (U1)TRUE){
        /* GYRO状態: 未初期化へ遷移する */
        vd_s_GyroDevCtlMngModSet((U1)GYRO_MODE_UNINIT);

        /* タスク状態通知(シャットダウン処理完了) */
        /* 予備設計のため処理なし */
    }
    else{
        /* GYRO状態: 異常停止中へ遷移する */
        vd_s_GyroDevCtlMngModSet((U1)GYRO_MODE_ERR);
    }
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroDevComRst(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevComRst(void)
{
    /* 共通状態・リトライ処理 */

    /* GYRO強制終了処理 */
    vd_s_GyroDevForceEnd();

    /* GYRO状態: 起動(1)実施中へ遷移する */
    vd_s_GyroDevCtlMngModSet((U1)GYRO_MODE_STUP1_PRO);

    /* GYROシーケンス: 起動(1)を起動 */
    vd_s_GyroDevSeqSet((U1)GYRO_SEQ_STAUP1);
}
/**************************↑状態遷移管理(END)↑*****************************/

/**************************↓シーケンス管理(START)↓*************************/
/*===================================================================================================================================*/
/* static void     vd_s_GyroDevSeqCtl(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevSeqCtl(void)
{
    FP_GYRO_SRQ_FUNC    fp_t_func;

    /* パラメータチェック */
    if(st_s_gyro_seqmng.u1_no >= (U1)GYRO_SEQ_MAX){
        /* 実行対象シーケンス異常 */
        st_s_gyro_seqmng.u1_no          = (U1)GYRO_SEQ_IDLE;
        st_s_gyro_seqmng.u1_step        = (U1)GYRO_SEQ_IDLE_STA;
        st_s_gyro_seqmng.u1_subtype     = (U1)GYRO_SEQ_IDLE_STA;
    }

    /* シーケンス実行処理 */
    fp_t_func   = fp_sp_gyro_Seq[st_s_gyro_seqmng.u1_no];
    if(fp_t_func != vdp_PTR_NA){
        fp_t_func();
    }
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroDevSeqSet(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevSeqSet(const U1 u1_a_SEQNO)
{
    if(u1_a_SEQNO < (U1)GYRO_SEQ_MAX){
        st_s_gyro_seqmng.u1_no          = u1_a_SEQNO;
        st_s_gyro_seqmng.u1_step        = (U1)GYRO_SEQ_IDLE_STA;
        st_s_gyro_seqmng.u1_subtype     = (U1)GYRO_SEQ_IDLE_STA;
    }
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroDevSeqIdle(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevSeqIdle(void)
{
    /* アイドルシーケンス */
    /* do nothing */
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroDevSeqStaUp1(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevSeqStaUp1(void)
{
    /* GYRO起動(1)シーケンス */

    U1      u1_t_sts;       /* I2C,サブ関数処理状況チェック */
    U1      u1_t_timchk;    /* 経過時間判定 */

    u1_t_sts    = (U1)FALSE;
    u1_t_timchk = (U1)FALSE;

    /* Ackタイムアウト用カウンタインクリメント */
    if(u4_s_gyro_acktime < (U4)U4_MAX){
        u4_s_gyro_acktime++;
    }

    switch (st_s_gyro_seqmng.u1_step)
    {
    case (U1)GYRO_SEQ_STAUP1_1:
        /* Wati t1 */
        u1_t_timchk = u1_s_GyroDevTimCheck(u4_s_gyro_linktim, (U4)GYRO_WAIT_T1);
        if(u1_t_timchk  == (U1)TRUE){
            /* Wati t1完了 次のシーケンスへ */
            u4_s_gyro_linktim           = (U4)0U;
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_STAUP1_2;
        }
        else{
            u4_s_gyro_linktim++;
        }
        break;

    case (U1)GYRO_SEQ_STAUP1_2:
        /* SENSOR-ON端子 Lo→Hi */
        dl_GYRO_DIO_WRITE_SENSOR_ON_H();
        /* GYROモードをNorma1に設定する */
        st_s_gyro_ctrl.u1_dev_mode  = (U1)GYRO_DEV_MODE_NORMAL;
        /* 次のシーケンスへ */
        st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_STAUP1_3;
        break;

    case (U1)GYRO_SEQ_STAUP1_3:
        /* Wati t3 */
        u1_t_timchk = u1_s_GyroDevTimCheck(u4_s_gyro_linktim, (U4)GYRO_WAIT_T3);
        if(u1_t_timchk  == (U1)TRUE){
            /* Wati t3完了 次のシーケンスへ */
            u4_s_gyro_linktim           = (U4)0U;
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_STAUP1_4;
        }
        else{
            u4_s_gyro_linktim++;
        }
        break;

    case (U1)GYRO_SEQ_STAUP1_4:
        u1_t_sts    = GYRO_I2C_WRITE_GYRO(&u2_s_gyro_regstep, (U2)GYRO_WRISTEP_WDG_GYR, st_sp_GYRO_WRISTEP_WDG_GYR,
                                            &u4_s_gyro_acktime, st_sp_MCU_SYS_PWR_GYR_REG_GYR_WDG, &u2_s_gyro_i2cwaittim);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_STAUP1_5;
        }
        break;

    case (U1)GYRO_SEQ_STAUP1_5:
        u1_t_sts    = GYRO_I2C_WRITE_ACC(&u2_s_gyro_regstep, (U2)GYRO_WRISTEP_WDG_ACC, st_sp_GYRO_WRISTEP_WDG_ACC,
                                            &u4_s_gyro_acktime, st_sp_MCU_SYS_PWR_GYR_REG_ACC_WDG, &u2_s_gyro_i2cwaittim);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_STAUP1_6;
        }
        break;

    case (U1)GYRO_SEQ_STAUP1_6:
        /* Wati t10(1ms待機)は本caseに到達した時点で満たしていると判断するためwait処理は実施しない */
        u1_t_sts    = GYRO_I2C_WRITE_ACC(&u2_s_gyro_regstep, (U2)GYRO_WRISTEP_MODE_ON_ACC, st_sp_GYRO_WRISTEP_MODE_ON_ACC,
                                            &u4_s_gyro_acktime, st_sp_MCU_SYS_PWR_GYR_REG_ACC_MODE_ON, &u2_s_gyro_i2cwaittim);
        if(u1_t_sts == (U1)TRUE){
            /*  */
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_STAUP1_7;
        }
        break;

    case (U1)GYRO_SEQ_STAUP1_7:
        /* Wati t11 */
        u1_t_timchk = u1_s_GyroDevTimCheck(u4_s_gyro_linktim, (U4)GYRO_WAIT_T11);
        if(u1_t_timchk  == (U1)TRUE){
            /* Wati t11完了 次のシーケンスへ */
            u4_s_gyro_linktim           = (U4)0U;
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_STAUP1_8;
        }
        else{
            u4_s_gyro_linktim++;
        }
        break;

    case (U1)GYRO_SEQ_STAUP1_8:
        u1_t_sts    = GYRO_I2C_WRITE_GYRO(&u2_s_gyro_regstep, (U2)GYRO_WRISTEP_SETUP_GYR, st_sp_GYRO_WRISTEP_SETUP_GYR,
                                            &u4_s_gyro_acktime, st_sp_MCU_SYS_PWR_GYR_REG_GYR_SETUP, &u2_s_gyro_i2cwaittim);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_STAUP1_9;
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_SELFTEST_GYRO_1;
        }
        break;

    case (U1)GYRO_SEQ_STAUP1_9:
        u1_t_sts    = u1_s_GyroDevSeqGyrSelfTest();

        if(u1_t_sts == (U1)GYRO_RET_OK){
            /* テスト結果OK 次のシーケンスへ */
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_STAUP1_10;
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_IDLE_STA;
        }
        else if(u1_t_sts == (U1)GYRO_RET_IICERR){
            /* I2C失敗によるコマンドスキップ時のフェール処理 */
            /* 予備設計のため処理なし 遷移することはないがした場合はフェール処理を実施 */
            /* ToDo：I2C失敗時処理導入の検討 */

            vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);
            vd_s_GyroDevSeqSelfTestErr();
        }
        else if(u1_t_sts == (U1)GYRO_RET_NG){
            /* テスト結果NG フェール処理 */
            /* 起動フロー(1)を終了、シーケンスアイドルに設定 */
            vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);
            /* Self Test 失敗処理 */
            vd_s_GyroDevSeqSelfTestErr();
        }
        else{
            /* Self Test (Gyro)実施中 */
            /* do nothign */
        }
        break;

    case (U1)GYRO_SEQ_STAUP1_10:
        u1_t_sts    = GYRO_I2C_WRITE_GYRO(&u2_s_gyro_regstep, (U2)GYRO_WRISTEP_SETUP_GYR, st_sp_GYRO_WRISTEP_SETUP_GYR,
                                            &u4_s_gyro_acktime, st_sp_MCU_SYS_PWR_GYR_REG_GYR_SETUP, &u2_s_gyro_i2cwaittim);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_STAUP1_11;
        }
        break;

    case (U1)GYRO_SEQ_STAUP1_11:
        u1_t_sts    = GYRO_I2C_WRITE_ACC(&u2_s_gyro_regstep, (U2)GYRO_WRISTEP_SETUP_SEN2_ACC, st_sp_GYRO_WRISTEP_SETUP_SEN2_ACC,
                                            &u4_s_gyro_acktime, st_sp_MCU_SYS_PWR_GYR_REG_ACC_SEN2_SETUP, &u2_s_gyro_i2cwaittim);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_STAUP1_12;
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_SELFTEST_ACC_1;
        }
        break;

    case (U1)GYRO_SEQ_STAUP1_12:
        u1_t_sts    = u1_s_GyroDevSeqAccSelfTest();

        if(u1_t_sts == (U1)GYRO_RET_OK){
            /* テスト結果OK 次のシーケンスへ */
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_STAUP1_13;
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_UPCONF_1;
        }
        else if(u1_t_sts == (U1)GYRO_RET_IICERR){
            /* I2C失敗によるコマンドスキップ時のフェール処理 */
            /* 予備設計のため処理なし 遷移することはないがした場合はフェール処理を実施 */
            /* ToDo：I2C失敗時処理導入の検討 */

            vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);
            vd_s_GyroDevSeqSelfTestErr();
        }
        else if(u1_t_sts == (U1)GYRO_RET_NG){
            /* テスト結果NG フェール処理 */
            /* 起動フロー(1)を終了、シーケンスアイドルに設定 */
            vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);
            /* Self Test 失敗処理 */
            vd_s_GyroDevSeqSelfTestErr();
        }
        else{
            /* Self Test (Gセンサ)実施中 */
            /* do nothign */
        }
        break;

    case (U1)GYRO_SEQ_STAUP1_13:
        u1_t_sts    = u1_s_GyroDevSeqAccCfgUpload();

        if(u1_t_sts == (U1)GYRO_RET_OK){
            /* 実施結果OK 次のシーケンスへ */
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_STAUP1_14;
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_INTSET_1;
        }
        else if(u1_t_sts == (U1)GYRO_RET_IICERR){
            /* I2C失敗によるコマンドスキップ時のフェール処理 */
            /* 予備設計のため処理なし 遷移することはないがした場合はフェール処理を実施 */
            /* ToDo：I2C失敗時処理導入の検討 */

            vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);
            vd_g_GyroDevEventGo((U1)GYRO_EVENT_STUP_ERR);
        }
        else if(u1_t_sts == (U1)GYRO_RET_NG){
            /* 実施結果NG */
            /* ダイレコ記録 */
            /* ToDo：ダイレコ記録用IFを刺す */
            /* 起動フロー(1)を終了、シーケンスアイドルに設定 */
            vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);
            /* GYRO状態管理の イベント・ハンドラを呼び出し */
            vd_g_GyroDevEventGo((U1)GYRO_EVENT_STUP_ERR);
        }
        else{
            /* upload config待ち */
            /* do nothign */
        }
        break;

    case (U1)GYRO_SEQ_STAUP1_14:
        u1_t_sts    = u1_s_GyroDevSeqAccIntSet();

        if(u1_t_sts == (U1)GYRO_RET_OK){
            /* 実施結果OK 次のシーケンスへ */
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_STAUP1_15;
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_IDLE_STA;
        }
        else if(u1_t_sts == (U1)GYRO_RET_IICERR){
            /* I2C失敗によるコマンドスキップ時のフェール処理 */
            /* 予備設計のため処理なし 遷移することはないがした場合はフェール処理を実施 */
            /* ToDo：I2C失敗時処理導入の検討 */

            vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);
            vd_g_GyroDevEventGo((U1)GYRO_EVENT_STUP_ERR);
        }
        else{
            /* Set Interrupt待ち */
            /* do nothign */
        }
        break;

    case (U1)GYRO_SEQ_STAUP1_15:
        u1_t_sts    = GYRO_I2C_WRITE_ACC(&u2_s_gyro_regstep, (U2)GYRO_WRISTEP_WDG_ACC, st_sp_GYRO_WRISTEP_WDG_ACC,
                                            &u4_s_gyro_acktime, st_sp_MCU_SYS_PWR_GYR_REG_ACC_WDG, &u2_s_gyro_i2cwaittim);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_STAUP1_16;
        }
        break;

    case (U1)GYRO_SEQ_STAUP1_16:
        u1_t_sts    = GYRO_I2C_WRITE_ACC(&u2_s_gyro_regstep, (U2)GYRO_WRISTEP_SETUP_SEN1_ACC, st_sp_GYRO_WRISTEP_SETUP_SEN1_ACC,
                                            &u4_s_gyro_acktime, st_sp_MCU_SYS_PWR_GYR_REG_ACC_SEN1_SETUP, &u2_s_gyro_i2cwaittim);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_STAUP1_17;
        }
        break;

    case (U1)GYRO_SEQ_STAUP1_17:
        u1_t_sts    = GYRO_I2C_WRITE_GYRO(&u2_s_gyro_regstep, (U2)GYRO_WRISTEP_MODE_OFF_GYR, st_sp_GYRO_WRISTEP_MODE_OFF_GYR,
                                            &u4_s_gyro_acktime, st_sp_MCU_SYS_PWR_GYR_REG_GYR_MODE_OFF, &u2_s_gyro_i2cwaittim);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_STAUP1_18;
        }
        break;

    case (U1)GYRO_SEQ_STAUP1_18:
        /* Wati t21 */
        u1_t_timchk = u1_s_GyroDevTimCheck(u4_s_gyro_linktim, (U4)GYRO_WAIT_T21);
        if(u1_t_timchk  == (U1)TRUE){
            /* Wati t21完了 */
            u4_s_gyro_linktim           = (U4)0U;

            /* GyroモードをSuspendに変更する */
            st_s_gyro_ctrl.u1_dev_mode  = (U1)GYRO_DEV_MODE_SUSPEND;

            /* Selt-Test異常エラーカウント クリア */ 
            u1_s_errcnt_l   = (U1)0U;
            u1_s_errcnt_j   = (U1)0U;

            /* シーケンスアイドルに設定 */
            vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);

            /* GYRO状態管理の イベント・ハンドラを呼び出し */
            vd_g_GyroDevEventGo((U1)GYRO_EVENT_SEQ_COMP);
        }
        else{
            u4_s_gyro_linktim++;
        }
        break;

    default:
        /* シーケンスアイドルに設定 */
        break;
    }
}

/*===================================================================================================================================*/
/* static U1       u1_s_GyroDevSeqGyrSelfTest(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_GyroDevSeqGyrSelfTest(void)
{
    /* Self-Test (Gyro) */

    U1      u1_t_ret;       /* シーケンス完了通知 */
    U1      u1_t_sts;       /* I2C,サブ関数処理状況チェック */
    U1      u1_t_timchk;    /* 経過時間判定 */
    U1      u1_t_read;      /* レジスタ読出し値 */

    u1_t_ret    = (U1)GYRO_RET_INPROC;
    u1_t_sts    = (U1)FALSE;
    u1_t_timchk = (U1)FALSE;
    u1_t_read   = (U1)0x00U;

    switch (st_s_gyro_seqmng.u1_subtype)
    {
    case (U1)GYRO_SEQ_SELFTEST_GYRO_1:
        /* 【write】0x3C */
        u1_t_sts    = GYRO_I2C_WRITE_GYRO(&u2_s_gyro_regstep, (U2)GYRO_WRISTEP_TEST_COMSET_GYR, st_sp_GYRO_WRISTEP_TEST_COMSET_GYR,
                                            &u4_s_gyro_acktime, st_sp_MCU_SYS_PWR_GYR_REG_GYR_TEST, &u2_s_gyro_i2cwaittim);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_SELFTEST_GYRO_2;
        }
        break;
    
    case (U1)GYRO_SEQ_SELFTEST_GYRO_2:
        /* 【wait】t12 */
        u1_t_timchk = u1_s_GyroDevTimCheck(u4_s_gyro_linktim, (U4)GYRO_WAIT_T12);
        if(u1_t_timchk  == (U1)TRUE){
            /* Wati t12完了 次のシーケンスへ */
            u4_s_gyro_linktim           = (U4)0U;
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_SELFTEST_GYRO_3;
        }
        else{
            u4_s_gyro_linktim++;
        }
        break;

    case (U1)GYRO_SEQ_SELFTEST_GYRO_3:
        /* 【read】0x3C */
        u1_t_sts    = GYRO_I2C_READ_GYRO(&u2_s_gyro_regstep, &u4_s_gyro_acktime, st_sp_MCU_SYS_PWR_GYR_REG_GYR_TEST_RD, &u2_s_gyro_i2cwaittim);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_SELFTEST_GYRO_4;
        }
        break;
    
    case (U1)GYRO_SEQ_SELFTEST_GYRO_4:
        /* SelfTest完了判定 */
        u1_t_read   = st_sp_MCU_SYS_PWR_GYR_REG_GYR_TEST_RD[GYRO_READPOS_1].u1p_pdu[GYRO_READPOS_1];

        if(((u1_t_read & (U1)GYRO_READDAT_BIT1) == (U1)GYRO_READDAT_BIT1)   &&
           ((u1_t_read & (U1)GYRO_READDAT_BIT2) != (U1)GYRO_READDAT_BIT2)   ){
            /* Test Result = OK */
            u1_t_ret    = (U1)GYRO_RET_OK;
        }
        else{
            /* Test Result = Failure */
            u1_t_ret    = (U1)GYRO_RET_NG;
        }
        break;
    
    default:
        /* アイドルシーケンスに設定 */
        vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);
        break;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/* static U1       u1_s_GyroDevSeqAccSelfTest(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_GyroDevSeqAccSelfTest(void)
{
    /* Self-Test (Acc) */

    U1      u1_t_ret;                           /* シーケンス完了通知 */
    U1      u1_t_sts;                           /* I2C,サブ関数処理状況チェック */
    U1      u1_t_timchk;                        /* 経過時間判定 */
    S2      s2_t_data_buf_x;                    /* X軸 換算データ演算用バッファ */
    S2      s2_t_data_buf_y;                    /* Y軸 換算データ演算用バッファ */
    S2      s2_t_data_buf_z;                    /* Z軸 換算データ演算用バッファ */

    u1_t_ret    = (U1)GYRO_RET_INPROC;
    u1_t_sts    = (U1)FALSE;
    u1_t_timchk = (U1)FALSE;

    switch (st_s_gyro_seqmng.u1_subtype)
    {
    case (U1)GYRO_SEQ_SELFTEST_ACC_1:
        /* 【wait】t12 */
        u1_t_timchk = u1_s_GyroDevTimCheck(u4_s_gyro_linktim, (U4)GYRO_WAIT_T13);
        if(u1_t_timchk  == (U1)TRUE){
            /* Wati t11完了 次のシーケンスへ */
            u4_s_gyro_linktim           = (U4)0U;
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_SELFTEST_ACC_2;
        }
        else{
            u4_s_gyro_linktim++;
        }
        break;
    
    case (U1)GYRO_SEQ_SELFTEST_ACC_2:
        /* write 0x6D （＋側） */
        u1_t_sts    = GYRO_I2C_WRITE_ACC(&u2_s_gyro_regstep, (U2)GYRO_WRISTEP_SELFTEST_ACC_PLS, st_sp_GYRO_WRISTEP_SELFTEST_ACC_PLS,
                                            &u4_s_gyro_acktime, st_sp_MCU_SYS_PWR_GYR_REG_ACC_PLSTEST, &u2_s_gyro_i2cwaittim);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_SELFTEST_ACC_3;
        }
        break;

    case (U1)GYRO_SEQ_SELFTEST_ACC_3:
        /* 【wait】t14 */
        u1_t_timchk = u1_s_GyroDevTimCheck(u4_s_gyro_linktim, (U4)GYRO_WAIT_T14);
        if(u1_t_timchk  == (U1)TRUE){
            /* Wati t11完了 次のシーケンスへ */
            u4_s_gyro_linktim           = (U4)0U;
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_SELFTEST_ACC_4;
        }
        else{
            u4_s_gyro_linktim++;
        }
        break;

    case (U1)GYRO_SEQ_SELFTEST_ACC_4:
        /* Read data (Gセンサ +) */
        u1_t_sts    = GYRO_I2C_READ_ACC(&u2_s_gyro_regstep, &u4_s_gyro_acktime, st_sp_MCU_SYS_PWR_GYR_REG_GYR_XYZ, &u2_s_gyro_i2cwaittim);
        if(u1_t_sts == (U1)TRUE){
            /* データ保持（+側） */
            st_s_gyro_accdat_pls.u1_acc_x_lsb       = st_sp_MCU_SYS_PWR_GYR_REG_GYR_XYZ[GYRO_READPOS_1].u1p_pdu[GYRO_READPOS_1];
            st_s_gyro_accdat_pls.u1_acc_x_msb       = st_sp_MCU_SYS_PWR_GYR_REG_GYR_XYZ[GYRO_READPOS_1].u1p_pdu[GYRO_READPOS_2];
            st_s_gyro_accdat_pls.u1_acc_y_lsb       = st_sp_MCU_SYS_PWR_GYR_REG_GYR_XYZ[GYRO_READPOS_1].u1p_pdu[GYRO_READPOS_3];
            st_s_gyro_accdat_pls.u1_acc_y_msb       = st_sp_MCU_SYS_PWR_GYR_REG_GYR_XYZ[GYRO_READPOS_1].u1p_pdu[GYRO_READPOS_4];
            st_s_gyro_accdat_pls.u1_acc_z_lsb       = st_sp_MCU_SYS_PWR_GYR_REG_GYR_XYZ[GYRO_READPOS_1].u1p_pdu[GYRO_READPOS_5];
            st_s_gyro_accdat_pls.u1_acc_z_msb       = st_sp_MCU_SYS_PWR_GYR_REG_GYR_XYZ[GYRO_READPOS_1].u1p_pdu[GYRO_READPOS_6];

            /* データ換算 */
            st_s_gyro_accdat_pls.st_acc_xyz.s2_x    = (U2)(((U2)st_s_gyro_accdat_pls.u1_acc_x_msb << (U2)GYRO_SHIFT_8) | (U2)st_s_gyro_accdat_pls.u1_acc_x_lsb);
            st_s_gyro_accdat_pls.st_acc_xyz.s2_y    = (U2)(((U2)st_s_gyro_accdat_pls.u1_acc_y_msb << (U2)GYRO_SHIFT_8) | (U2)st_s_gyro_accdat_pls.u1_acc_y_lsb);
            st_s_gyro_accdat_pls.st_acc_xyz.s2_z    = (U2)(((U2)st_s_gyro_accdat_pls.u1_acc_z_msb << (U2)GYRO_SHIFT_8) | (U2)st_s_gyro_accdat_pls.u1_acc_z_lsb);

            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_SELFTEST_ACC_5;
        }
        break;

    case (U1)GYRO_SEQ_SELFTEST_ACC_5:
        /* write 0x6D （-側） */
        u1_t_sts    = GYRO_I2C_WRITE_ACC(&u2_s_gyro_regstep, (U2)GYRO_WRISTEP_SELFTEST_ACC_MNS, st_sp_GYRO_WRISTEP_SELFTEST_ACC_MNS,
                                            &u4_s_gyro_acktime, st_sp_MCU_SYS_PWR_GYR_REG_ACC_MNSTEST, &u2_s_gyro_i2cwaittim);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_SELFTEST_ACC_6;
        }
        break;

    case (U1)GYRO_SEQ_SELFTEST_ACC_6:
        /* wait t14 */
        u1_t_timchk = u1_s_GyroDevTimCheck(u4_s_gyro_linktim, (U4)GYRO_WAIT_T14);
        if(u1_t_timchk  == (U1)TRUE){
            /* Wati t11完了 次のシーケンスへ */
            u4_s_gyro_linktim           = (U4)0U;
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_SELFTEST_ACC_7;
        }
        else{
            u4_s_gyro_linktim++;
        }
        break;

    case (U1)GYRO_SEQ_SELFTEST_ACC_7:
        /* Read data (Gセンサ -) */
        u1_t_sts    = GYRO_I2C_READ_ACC(&u2_s_gyro_regstep, &u4_s_gyro_acktime, st_sp_MCU_SYS_PWR_GYR_REG_GYR_XYZ, &u2_s_gyro_i2cwaittim);
        if(u1_t_sts == (U1)TRUE){
            /* データ保持（-側） */
            st_s_gyro_accdat_mns.u1_acc_x_lsb       = st_sp_MCU_SYS_PWR_GYR_REG_GYR_XYZ[GYRO_READPOS_1].u1p_pdu[GYRO_READPOS_1];
            st_s_gyro_accdat_mns.u1_acc_x_msb       = st_sp_MCU_SYS_PWR_GYR_REG_GYR_XYZ[GYRO_READPOS_1].u1p_pdu[GYRO_READPOS_2];
            st_s_gyro_accdat_mns.u1_acc_y_lsb       = st_sp_MCU_SYS_PWR_GYR_REG_GYR_XYZ[GYRO_READPOS_1].u1p_pdu[GYRO_READPOS_3];
            st_s_gyro_accdat_mns.u1_acc_y_msb       = st_sp_MCU_SYS_PWR_GYR_REG_GYR_XYZ[GYRO_READPOS_1].u1p_pdu[GYRO_READPOS_4];
            st_s_gyro_accdat_mns.u1_acc_z_lsb       = st_sp_MCU_SYS_PWR_GYR_REG_GYR_XYZ[GYRO_READPOS_1].u1p_pdu[GYRO_READPOS_5];
            st_s_gyro_accdat_mns.u1_acc_z_msb       = st_sp_MCU_SYS_PWR_GYR_REG_GYR_XYZ[GYRO_READPOS_1].u1p_pdu[GYRO_READPOS_6];

            /* データ換算 */
            st_s_gyro_accdat_mns.st_acc_xyz.s2_x    = (U2)(((U2)st_s_gyro_accdat_mns.u1_acc_x_msb << (U2)GYRO_SHIFT_8) | (U2)st_s_gyro_accdat_mns.u1_acc_x_lsb);
            st_s_gyro_accdat_mns.st_acc_xyz.s2_y    = (U2)(((U2)st_s_gyro_accdat_mns.u1_acc_y_msb << (U2)GYRO_SHIFT_8) | (U2)st_s_gyro_accdat_mns.u1_acc_y_lsb);
            st_s_gyro_accdat_mns.st_acc_xyz.s2_z    = (U2)(((U2)st_s_gyro_accdat_mns.u1_acc_z_msb << (U2)GYRO_SHIFT_8) | (U2)st_s_gyro_accdat_mns.u1_acc_z_lsb);

            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_SELFTEST_ACC_8;
        }
        break;

    case (U1)GYRO_SEQ_SELFTEST_ACC_8:
        /* write 0x6D （disable） */
        u1_t_sts    = GYRO_I2C_WRITE_ACC(&u2_s_gyro_regstep, (U2)GYRO_WRISTEP_SELFTEST_ACC_DISABLE, st_sp_GYRO_WRISTEP_SELFTEST_ACC_DISABLE,
                                            &u4_s_gyro_acktime, st_sp_MCU_SYS_PWR_GYR_REG_ACC_DISTEST, &u2_s_gyro_i2cwaittim);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_SELFTEST_ACC_9;
        }
        break;

    case (U1)GYRO_SEQ_SELFTEST_ACC_9:
        /* wait t14 */
        u1_t_timchk = u1_s_GyroDevTimCheck(u4_s_gyro_linktim, (U4)GYRO_WAIT_T14);
        if(u1_t_timchk  == (U1)TRUE){
            /* Wati t11完了 次のシーケンスへ */
            u4_s_gyro_linktim           = (U4)0U;
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_SELFTEST_ACC_10;
        }
        else{
            u4_s_gyro_linktim++;
        }
        break;

    case (U1)GYRO_SEQ_SELFTEST_ACC_10:
        /* テスト結果判定 */
        s2_t_data_buf_x = (S2)GYRO_DAT_ACC_XYZ_MAX - (S2)GYRO_DAT_ACC_X_DIF;
        s2_t_data_buf_y = (S2)GYRO_DAT_ACC_XYZ_MAX - (S2)GYRO_DAT_ACC_Y_DIF;
        s2_t_data_buf_z = (S2)GYRO_DAT_ACC_XYZ_MAX - (S2)GYRO_DAT_ACC_Z_DIF;

        if((st_s_gyro_accdat_mns.st_acc_xyz.s2_x <= s2_t_data_buf_x)  &&   /* X軸 オーバーフローチェック */
           (st_s_gyro_accdat_mns.st_acc_xyz.s2_y <= s2_t_data_buf_y)  &&   /* Y軸 オーバーフローチェック */
           (st_s_gyro_accdat_mns.st_acc_xyz.s2_z <= s2_t_data_buf_z)  ){   /* Z軸 オーバーフローチェック */

            /* 比較用データ作成 */
            s2_t_data_buf_x = st_s_gyro_accdat_mns.st_acc_xyz.s2_x + (S2)GYRO_DAT_ACC_X_DIF;
            s2_t_data_buf_y = st_s_gyro_accdat_mns.st_acc_xyz.s2_y + (S2)GYRO_DAT_ACC_Y_DIF;
            s2_t_data_buf_z = st_s_gyro_accdat_mns.st_acc_xyz.s2_z + (S2)GYRO_DAT_ACC_Z_DIF;

            if((st_s_gyro_accdat_pls.st_acc_xyz.s2_x >= s2_t_data_buf_x)  &&   /* X軸 Gセンサ（＋）― Gセンサ（－）≧th_dif ? */
               (st_s_gyro_accdat_pls.st_acc_xyz.s2_y >= s2_t_data_buf_y)  &&   /* Y軸 Gセンサ（＋）― Gセンサ（－）≧th_dif ? */
               (st_s_gyro_accdat_pls.st_acc_xyz.s2_z >= s2_t_data_buf_z)  ){   /* Z軸 Gセンサ（＋）― Gセンサ（－）≧th_dif ? */
                /* Test Result = OK */
                u1_t_ret    = (U1)GYRO_RET_OK;
            }
            else{
                /* Test Result = Failure */
                u1_t_ret    = (U1)GYRO_RET_NG;
            }
        }
        else{
            /* Test Result = Failure */
            u1_t_ret    = (U1)GYRO_RET_NG;
        }
        break;

    default:
        /* アイドルシーケンスに設定 */
        vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);
        break;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroDevSeqSelfTestErr(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevSeqSelfTestErr(void)
{
    /* Self-Testエラーカウントl(6_1)をチェック	 */
    if(u1_s_errcnt_l < (U1)GYRO_CNT_SELFTEST_RTRY_MAX){
        /* エラーカウントを累積 */
        u1_s_errcnt_l++;

        /* GYRO状態管理の イベント・ハンドラを呼び出し */
        vd_g_GyroDevEventGo(GYRO_EVENT_DEV_RST);
    }
    else{
        /* エラーカウントl(6_1)、j(6_1)をクリア */
        u1_s_errcnt_l   = (U1)0U;
        u1_s_errcnt_j   = (U1)0U;

        /* ダイレコ記録 */
        /* ToDo：必要に応じてダイレコ記憶IF挿入 */

        /* GYRO状態管理の イベント・ハンドラを呼び出し */
        vd_g_GyroDevEventGo((U1)GYRO_EVENT_STUP_ERR);
    }
}

/*===================================================================================================================================*/
/* static U1       u1_s_GyroDevSeqAccCfgUpload(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_GyroDevSeqAccCfgUpload(void)
{
    ST_GYRO_DATAINFO    st_t_datainfo;
    U1                  u1_t_ret;       /* シーケンス完了通知 */
    U1                  u1_t_sts;       /* I2C,サブ関数処理状況チェック */
    U1                  u1_t_timchk;    /* 経過時間判定 */
    U1                  u1_t_read;      /* レジスタ読出し値 */
    U4                  u4_t_offset;    /* 書込み位置オフセット */
    U1 *                u1p_t_addr;     /* 書込み位置アドレス */

    vd_s_GyroDevMemset(&st_t_datainfo, (U1)0U, (U4)sizeof(st_t_datainfo));
    u1_t_ret    = (U1)GYRO_RET_INPROC;
    u1_t_sts    = (U1)FALSE;
    u1_t_timchk = (U1)FALSE;
    u1_t_read   = (U1)0x00U;
    
    switch (st_s_gyro_seqmng.u1_subtype)
    {
    case GYRO_SEQ_UPCONF_1:
        /* GセンサデータInfo読込 */
        st_s_gyro_cfgmng.u1_upload_cnt  = (U1)0U;
        st_s_gyro_cfgmng.u1_upload_idx  = (U1)0U;
        st_s_gyro_cfgmng.u4_upload_addr = (U4)0U;
        u1_t_sts    = u1_s_GyroGetDatInfo(&st_t_datainfo);
        if(u1_t_sts != (U1)GYRO_RET_OK){
            /* Config読出し失敗 ダイレコ記録して終了 */
            /* ToDo：ダイレコIF挿入 */
            u1_t_ret    = (U1)GYRO_RET_OK;
        }
        else{
            if(st_t_datainfo.u4_datsiz > (U4)GYRO_CFG_MAXSIZ){
                /* Configサイズ異常 ダイレコ記録して終了 */
                /* ToDo：ダイレコIF挿入 */
                u1_t_ret    = (U1)GYRO_RET_OK;
            }
            else{
                /* 読込データ先頭アドレス&書込み回数取得 */
                st_s_gyro_cfgmng.u4_upload_addr = st_t_datainfo.u4_strtadr;
                st_s_gyro_cfgmng.u1_upload_cnt  = (U1)((st_t_datainfo.u4_datsiz / (U4)GYRO_CFG_WRISIZ) & (U4)0x000000FFU);
                u1_t_ret                        = (U1)GYRO_RET_INPROC;
            }
        }
        /* INIT Check NGカウント初期化 */
        u1_s_gyro_uploadcfg_rtrycnt = (U1)0U;
        st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_UPCONF_2;
        break;
    
    case (U1)GYRO_SEQ_UPCONF_2:
        /* softreset (Gセンサ) */
        u1_t_sts    = GYRO_I2C_WRITE_ACC(&u2_s_gyro_regstep, (U2)GYRO_WRISTEP_SOFTRESET, st_sp_GYRO_WRISTEP_SOFTRESET,
                                            &u4_s_gyro_acktime, st_sp_MCU_SYS_PWR_GYR_REG_ACC_SOFTRESET, &u2_s_gyro_i2cwaittim);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_UPCONF_3;
        }
        break;

    case (U1)GYRO_SEQ_UPCONF_3:
        /* 【wait】t15 */
        u1_t_timchk = u1_s_GyroDevTimCheck(u4_s_gyro_linktim, (U4)GYRO_WAIT_T15);
        if(u1_t_timchk  == (U1)TRUE){
            /* Wati t15完了 次のシーケンスへ */
            u4_s_gyro_linktim           = (U4)0U;
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_UPCONF_4;
        }
        else{
            u4_s_gyro_linktim++;
        }
        break;

    case (U1)GYRO_SEQ_UPCONF_4:
        /* change mode ACC suspend(ADS:0x7D */
        u1_t_sts    = GYRO_I2C_WRITE_ACC(&u2_s_gyro_regstep, (U2)GYRO_WRISTEP_MODE_OFF_ACC, st_sp_GYRO_WRISTEP_MODE_OFF_ACC,
                                            &u4_s_gyro_acktime, st_sp_MCU_SYS_PWR_GYR_REG_ACC_MODE_OFF, &u2_s_gyro_i2cwaittim);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_UPCONF_5;
        }
        break;

    case (U1)GYRO_SEQ_UPCONF_5:
        /* Wati t10(1ms待機)は本caseに到達した時点で満たしていると判断するためwait処理は実施しない */
        /* 次のシーケンスへ */
        st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_UPCONF_6;
        break;

    case (U1)GYRO_SEQ_UPCONF_6:
        /* change mode ACC normal(ADS:0x7C) */
        u1_t_sts    = GYRO_I2C_WRITE_ACC(&u2_s_gyro_regstep, (U2)GYRO_WRISTEP_PWRCONF_ON, st_sp_GYRO_WRISTEP_PWRCONF_ON,
                                            &u4_s_gyro_acktime, st_sp_MCU_SYS_PWR_GYR_REG_ACC_PWRCONF_ON, &u2_s_gyro_i2cwaittim);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_UPCONF_7;
        }
        break;

    case (U1)GYRO_SEQ_UPCONF_7:
        /* 【wait】t15 */
        u1_t_timchk = u1_s_GyroDevTimCheck(u4_s_gyro_linktim, (U4)GYRO_WAIT_T15);
        if(u1_t_timchk  == (U1)TRUE){
            /* Wati t15完了 次のシーケンスへ */
            u4_s_gyro_linktim           = (U4)0U;
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_UPCONF_8;
        }
        else{
            u4_s_gyro_linktim++;
        }
        break;

    case (U1)GYRO_SEQ_UPCONF_8:
        /* Set INT_CTRL write ADS:0x59 val:0x00 */
        u1_t_sts    = GYRO_I2C_WRITE_ACC(&u2_s_gyro_regstep, (U2)GYRO_WRISTEP_INTCONF_ON, st_sp_GYRO_WRISTEP_INTCONF_ON,
                                            &u4_s_gyro_acktime, st_sp_MCU_SYS_PWR_GYR_REG_ACC_INTCONF_ON, &u2_s_gyro_i2cwaittim);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_UPCONF_9;
        }
        break;

    case (U1)GYRO_SEQ_UPCONF_9:
        /* 【wait】t15 */
        u1_t_timchk = u1_s_GyroDevTimCheck(u4_s_gyro_linktim, (U4)GYRO_WAIT_T15);
        if(u1_t_timchk  == (U1)TRUE){
            /* Wati t15完了 次のシーケンスへ */
            u4_s_gyro_linktim           = (U4)0U;
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_UPCONF_10;
        }
        else{
            u4_s_gyro_linktim++;
        }
        break;

    case (U1)GYRO_SEQ_UPCONF_10:
        /* upload config file via I2C write 0x5B */
        u1_t_sts    = GYRO_I2C_WRITE_ACC(&u2_s_gyro_regstep, (U2)GYRO_WRISTEP_CFG_OFST1, st_sp_GYRO_WRISTEP_CFG_OFST1,
                                            &u4_s_gyro_acktime, st_sp_MCU_SYS_PWR_GYR_REG_ACC_CFG1, &u2_s_gyro_i2cwaittim);
        if(u1_t_sts == (U1)GYRO_RET_OK){
            /* 次書込みデータ作成 */
            st_sp_MCU_SYS_PWR_GYR_REG_ACC_CFG2[GYRO_WRIPOS_0].u1p_pdu[GYRO_WRIPOS_2]    = st_s_gyro_cfgmng.u1_upload_idx;
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_UPCONF_11;
        } 
        break;

    case (U1)GYRO_SEQ_UPCONF_11:
        /* upload config file via I2C write 0x5C */
        u1_t_sts    = GYRO_I2C_WRITE_ACC(&u2_s_gyro_regstep, (U2)GYRO_WRISTEP_CFG_OFST2, st_sp_GYRO_WRISTEP_CFG_OFST2,
                                            &u4_s_gyro_acktime, st_sp_MCU_SYS_PWR_GYR_REG_ACC_CFG2, &u2_s_gyro_i2cwaittim);
        if(u1_t_sts == (U1)GYRO_RET_OK){
            /* 次書込みデータ作成 */
            u4_t_offset     = (U4)(st_s_gyro_cfgmng.u1_upload_idx * (U1)GYRO_CFG_WRISIZ);
            u1p_t_addr      = (U1 *)(st_s_gyro_cfgmng.u4_upload_addr + u4_t_offset);
            vd_g_MemcpyU1(&st_sp_MCU_SYS_PWR_GYR_REG_ACC_DATA[GYRO_WRIPOS_0].u1p_pdu[GYRO_WRIPOS_2], u1p_t_addr, (U4)GYRO_CFG_WRISIZ);
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_UPCONF_12;
        } 
        break;

    case (U1)GYRO_SEQ_UPCONF_12:
        /* upload config file via I2C write 0x5E */
        u1_t_sts    = GYRO_I2C_WRITE_ACC(&u2_s_gyro_regstep, (U2)GYRO_WRISTEP_CFG_DATA, st_sp_GYRO_WRISTEP_CFG_DATA,
                                            &u4_s_gyro_acktime, st_sp_MCU_SYS_PWR_GYR_REG_ACC_DATA, &u2_s_gyro_i2cwaittim);
        if(u1_t_sts == (U1)GYRO_RET_OK){
            /* インデックスインクリメント */
            st_s_gyro_cfgmng.u1_upload_idx++;
            /* 完了判定 */
            if(st_s_gyro_cfgmng.u1_upload_idx >= st_s_gyro_cfgmng.u1_upload_cnt){
                /* アップロード完了 次のシーケンスへ */
                st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_UPCONF_13;
            }
            else{
                /* アップロードシーケンスを再実行 */
                st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_UPCONF_10;
            }
        } 
        break;
    case (U1)GYRO_SEQ_UPCONF_13:
        /* Set INT_CTRL write ADS:0x59 val:0x01 */
        u1_t_sts    = GYRO_I2C_WRITE_ACC(&u2_s_gyro_regstep, (U2)GYRO_WRISTEP_INTCONF_OFF, st_sp_GYRO_WRISTEP_INTCONF_OFF,
                                            &u4_s_gyro_acktime, st_sp_MCU_SYS_PWR_GYR_REG_ACC_INTCONF_OFF, &u2_s_gyro_i2cwaittim);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_UPCONF_14;
        }
        break;

    case (U1)GYRO_SEQ_UPCONF_14:
        /* 【wait】t15 */
        u1_t_timchk = u1_s_GyroDevTimCheck(u4_s_gyro_linktim, (U4)GYRO_WAIT_T15);
        if(u1_t_timchk  == (U1)TRUE){
            /* Wati t15完了 次のシーケンスへ */
            u4_s_gyro_linktim           = (U4)0U;
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_UPCONF_15;
        }
        else{
            u4_s_gyro_linktim++;
        }
        break;

    case (U1)GYRO_SEQ_UPCONF_15:
        /* read 0x2A */
        u1_t_sts    = GYRO_I2C_READ_ACC(&u2_s_gyro_regstep, &u4_s_gyro_acktime, st_sp_MCU_SYS_PWR_GYR_REG_ACC_INTCONF_READ, &u2_s_gyro_i2cwaittim);
        if(u1_t_sts == (U1)TRUE){
            /* INIT Check */
            u1_t_read   = st_sp_MCU_SYS_PWR_GYR_REG_ACC_INTCONF_READ[GYRO_READPOS_1].u1p_pdu[GYRO_READPOS_1];

            if(u1_t_read ==(U1)GYRO_READDAT_BIT0){
                /* 次のシーケンスへ */
                st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_UPCONF_16;
            }
            else{
                if(u1_s_gyro_uploadcfg_rtrycnt > (U1)GYRO_CFG_MAXRTRY){
                    /* Config File 設定失敗として終了 */
                    u1_t_ret    = (U1)GYRO_RET_NG;
                }
                else{
                    u1_s_gyro_uploadcfg_rtrycnt++;
                    /* シーケンス再実行 */
                    st_s_gyro_seqmng.u1_subtype     = (U1)GYRO_SEQ_UPCONF_2;
                    st_s_gyro_cfgmng.u1_upload_idx  = (U1)0U;
                }
            }
        }
        else{
            /* do nothing */
        }
        break;

    case (U1)GYRO_SEQ_UPCONF_16:
        /* change mode ACC normal */
        u1_t_sts    = GYRO_I2C_WRITE_ACC(&u2_s_gyro_regstep, (U2)GYRO_WRISTEP_MODE_ON_ACC, st_sp_GYRO_WRISTEP_MODE_ON_ACC,
                                            &u4_s_gyro_acktime, st_sp_MCU_SYS_PWR_GYR_REG_ACC_MODE_ON, &u2_s_gyro_i2cwaittim);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_UPCONF_17;
        }
        break;

    case (U1)GYRO_SEQ_UPCONF_17:
        /* 【wait】t15 */
        u1_t_timchk = u1_s_GyroDevTimCheck(u4_s_gyro_linktim, (U4)GYRO_WAIT_T15);
        if(u1_t_timchk  == (U1)TRUE){
            /* Wati t15完了 シーケンス終了 */
            u4_s_gyro_linktim   = (U4)0U;
            u1_t_ret            = (U1)GYRO_RET_OK;
        }
        else{
            u4_s_gyro_linktim++;
        }
        break;

    default:
        /* アイドルシーケンスに設定 */
        vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);
        break;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/* static U1       u1_s_GyroDevSeqAccIntSet(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_GyroGetDatInfo(ST_GYRO_DATAINFO * st_a_datainfo)
{
    U1      u1_t_ret;
    U1      u1_t_sts;
    U1 *    u1p_t_version;
    U1 *    u1p_t_datsiz;
    U1 *    u1p_t_stradr;
    U1      u1_tp_version[GYRO_SIZ_VERSION];
    U1      u1_tp_datsiz[GYRO_SIZ_BUF];
    U1      u1_tp_stradr[GYRO_SIZ_BUF];
    U4      u4_t_clc_datsiz;
    U4      u4_t_clc_stradr;

    u1_t_ret        = (U1)GYRO_RET_NG;
    u1_t_sts        = (U1)GYRO_RET_NG;
    u4_t_clc_datsiz = (U4)0x00000000U;
    u4_t_clc_stradr = (U4)0x00000000U;

    if(st_a_datainfo != vdp_PTR_NA){
        u1_t_sts = u1_s_GyroGetStsChk();
        if(u1_t_sts == (U1)GYRO_CFG_EXIST){
            u1p_t_version   = (U1 *)u1p_s_GYROINFO_TOP_ADR + (U1)GYRO_ADR_VERSION;
            u1p_t_datsiz    = (U1 *)u1p_s_GYROINFO_TOP_ADR + (U1)GYRO_ADR_DATSIZ;
            u1p_t_stradr    = (U1 *)u1p_s_GYROINFO_TOP_ADR + (U1)GYRO_ADR_OFFSET;

            /* ConfigFileはリトルエンディアンのため、エンディアン変換せずに型を変換 */
            vd_g_MemcpyU1(u1_tp_version, u1p_t_version, sizeof(u1_tp_version));
            vd_g_MemcpyU1(u1_tp_datsiz, u1p_t_datsiz, sizeof(u1_tp_datsiz));
            vd_g_MemcpyU1(u1_tp_stradr, u1p_t_stradr, sizeof(u1_tp_stradr));

            u4_t_clc_datsiz |=  (U4)(u1_tp_datsiz[GYRO_POS_0] << (U1)GYRO_SFT_BYTE3);
            u4_t_clc_datsiz |=  (U4)(u1_tp_datsiz[GYRO_POS_1] << (U1)GYRO_SFT_BYTE2);
            u4_t_clc_datsiz |=  (U4)(u1_tp_datsiz[GYRO_POS_2] << (U1)GYRO_SFT_BYTE1);
            u4_t_clc_datsiz |=  (U4)(u1_tp_datsiz[GYRO_POS_3]);

            u4_t_clc_stradr |=  (U4)(u1_tp_stradr[GYRO_POS_0] << (U1)GYRO_SFT_BYTE3);
            u4_t_clc_stradr |=  (U4)(u1_tp_stradr[GYRO_POS_1] << (U1)GYRO_SFT_BYTE2);
            u4_t_clc_stradr |=  (U4)(u1_tp_stradr[GYRO_POS_2] << (U1)GYRO_SFT_BYTE1);
            u4_t_clc_stradr |=  (U4)(u1_tp_stradr[GYRO_POS_3]);

            /* 200.102_02h：MCUバージョン応答 */
            vd_g_XspiIviSub1VersionGsenPut(u1_tp_version);

            /* サイズ、読込開始アドレスを設定 */
            st_a_datainfo->u4_datsiz    = u4_t_clc_datsiz;
            st_a_datainfo->u4_strtadr   = (U4)u1p_s_GYROINFO_TOP_ADR + u4_t_clc_stradr;
            u1_t_ret                    = (U1)GYRO_RET_OK;
        }
        else{
            /* Configファイル読出し不可 */
            u1_t_ret    = (U1)GYRO_RET_NG;
        }
    }
    else{
        u1_t_ret    = (U1)GYRO_RET_NG;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/* static U1       u1_s_GyroGetStsChk(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_GyroGetStsChk(void)
{
    U1  u1_t_ret;

    /* シグネチャによるマイコンへの書込み有無確認 */
    if( (u1_REG_READ(*(u1p_s_GYROINFO_TOP_ADR                           ))  == (U1)GYRO_FNTOKEN_G) &&
        (u1_REG_READ(*(u1p_s_GYROINFO_TOP_ADR  +   (U1)GYRO_CLC_ADR1    ))  == (U1)GYRO_FNTOKEN__) &&
        (u1_REG_READ(*(u1p_s_GYROINFO_TOP_ADR  +   (U1)GYRO_CLC_ADR2    ))  == (U1)GYRO_FNTOKEN_C) &&
        (u1_REG_READ(*(u1p_s_GYROINFO_TOP_ADR  +   (U1)GYRO_CLC_ADR3    ))  == (U1)GYRO_FNTOKEN_O) &&
        (u1_REG_READ(*(u1p_s_GYROINFO_TOP_ADR  +   (U1)GYRO_CLC_ADR4    ))  == (U1)GYRO_FNTOKEN_N) &&
        (u1_REG_READ(*(u1p_s_GYROINFO_TOP_ADR  +   (U1)GYRO_CLC_ADR5    ))  == (U1)GYRO_FNTOKEN_F) &&
        (u1_REG_READ(*(u1p_s_GYROINFO_TOP_ADR  +   (U1)GYRO_CLC_ADR6    ))  == (U1)GYRO_FNTOKEN_I) &&
        (u1_REG_READ(*(u1p_s_GYROINFO_TOP_ADR  +   (U1)GYRO_CLC_ADR7    ))  == (U1)GYRO_FNTOKEN_G) ){

        u1_t_ret    = (U1)GYRO_CFG_EXIST;
    }
    else{
        u1_t_ret    = (U1)GYRO_CFG_NON;
    }

    return(u1_t_ret);
}
/*===================================================================================================================================*/
/* static U1       u1_s_GyroDevSeqAccIntSet(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_GyroDevSeqAccIntSet(void)
{
    U1      u1_t_ret;       /* シーケンス完了通知 */
    U1      u1_t_sts;       /* I2C,サブ関数処理状況チェック */

    u1_t_ret    = (U1)GYRO_RET_INPROC;
    u1_t_sts    = (U1)FALSE;

    switch (st_s_gyro_seqmng.u1_subtype)
    {
    case GYRO_SEQ_INTSET_1:
        /* INT_ANYMOT_TH */
        u1_t_sts    = GYRO_I2C_WRITE_ACC(&u2_s_gyro_regstep, (U2)GYRO_WRISTEP_INT_ANYMOT_TH, st_sp_GYRO_WRISTEP_INT_ANYMOT_TH,
                                            &u4_s_gyro_acktime, st_sp_MCU_SYS_PWR_GYR_REG_INTSET_ANYMOT_TH, &u2_s_gyro_i2cwaittim);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_INTSET_2;
        }
        break;
    case GYRO_SEQ_INTSET_2:
        /* INT_ANYMOT_EN */
        u1_t_sts    = GYRO_I2C_WRITE_ACC(&u2_s_gyro_regstep, (U2)GYRO_WRISTEP_INT_ANYMOT_EN, st_sp_GYRO_WRISTEP_INT_ANYMOT_EN,
                                            &u4_s_gyro_acktime, st_sp_MCU_SYS_PWR_GYR_REG_INTSET_ANYMOT_EN, &u2_s_gyro_i2cwaittim);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_INTSET_3;
        }
        break;
    case GYRO_SEQ_INTSET_3:
        /* INT_ANYMOT_TH */
        u1_t_sts    = GYRO_I2C_WRITE_ACC(&u2_s_gyro_regstep, (U2)GYRO_WRISTEP_INT_OTH, st_sp_GYRO_WRISTEP_INT_OTH,
                                            &u4_s_gyro_acktime, st_sp_MCU_SYS_PWR_GYR_REG_INTSET_OTH, &u2_s_gyro_i2cwaittim);
        if(u1_t_sts == (U1)TRUE){
            /* 全書込み完了 */
            u1_t_ret    = (U1)GYRO_RET_OK;
        }
        break;
    
    default:
        /* アイドルシーケンスに設定 */
        vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);
        break;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static void     vd_s_GyroDevSeqStaUp2(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevSeqStaUp2(void)
{
    /* GYRO起動(2)シーケンス */
    U1      u1_t_sts;       /* I2C,サブ関数処理状況チェック */
    U1      u1_t_timchk;    /* 経過時間判定 */

    u1_t_sts    = (U1)FALSE;
    u1_t_timchk = (U1)FALSE;

    /* Ackタイムアウト用カウンタインクリメント */
    if(u4_s_gyro_acktime < (U4)U4_MAX){
        u4_s_gyro_acktime++;
    }
    
    switch (st_s_gyro_seqmng.u1_step)
    {
    case (U1)GYRO_SEQ_STAUP2_1:
        u1_t_sts    = GYRO_I2C_WRITE_ACC(&u2_s_gyro_regstep, (U2)GYRO_WRISTEP_SETUP_SEN1_BW_ACC, st_sp_GYRO_WRISTEP_SETUP_SEN1_BW_ACC,
                                            &u4_s_gyro_acktime, st_sp_MCU_SYS_PWR_GYR_REG_ACC_SEN1_SETUP, &u2_s_gyro_i2cwaittim);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_STAUP2_2;
        }
        break;
    
    case (U1)GYRO_SEQ_STAUP2_2:
        u1_t_sts    = GYRO_I2C_READ_GYRO(&u2_s_gyro_regstep, &u4_s_gyro_acktime, st_sp_MCU_SYS_PWR_GYR_REG_GYR_MODE_RD, &u2_s_gyro_i2cwaittim);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_step = (U1)GYRO_SEQ_STAUP2_3;
        }
        break;

    case (U1)GYRO_SEQ_STAUP2_3:
        if(st_sp_MCU_SYS_PWR_GYR_REG_GYR_MODE_RD[GYRO_READPOS_1].u1p_pdu[GYRO_READPOS_1] == (U1)GYRO_DAT_GYROMODE_SUSPEND){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_step = (U1)GYRO_SEQ_STAUP2_4;
        }
        else{
            /* この時点でGyro=ONだと起動フロー(1)を通っていない可能性がある為、フェールとして起動フロー(1)へ遷移 */
            vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);
            vd_g_GyroDevEventGo((U1)GYRO_EVENT_STUP_ERR);
        }
        break;

    case (U1)GYRO_SEQ_STAUP2_4:
        /* Wati t10(1ms待機)は本caseに到達した時点で満たしていると判断するためwait処理は実施しない */
        /* 次のシーケンスへ */
        st_s_gyro_seqmng.u1_step = (U1)GYRO_SEQ_STAUP2_5;
        break;

    case (U1)GYRO_SEQ_STAUP2_5:
        u1_t_sts    = GYRO_I2C_WRITE_GYRO(&u2_s_gyro_regstep, (U2)GYRO_WRISTEP_MODE_ON_GYR, st_sp_GYRO_WRISTEP_MODE_ON_GYR,
                                            &u4_s_gyro_acktime, st_sp_MCU_SYS_PWR_GYR_REG_GYR_MODE_ON, &u2_s_gyro_i2cwaittim);
        if(u1_t_sts == (U1)TRUE){
            /* GYROモードをNorma1に設定する */
            st_s_gyro_ctrl.u1_dev_mode  = (U1)GYRO_DEV_MODE_NORMAL;

            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_STAUP2_6;
        }
        break;

    case (U1)GYRO_SEQ_STAUP2_6:
        /* Wati t21 */
        u1_t_timchk = u1_s_GyroDevTimCheck(u4_s_gyro_linktim, (U4)GYRO_WAIT_T21);
        if(u1_t_timchk  == (U1)TRUE){
            /* Wati t21完了 */
            u4_s_gyro_linktim   = (U4)0U;

            /* シーケンスアイドルに設定 */
            vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);

            /* GYRO状態管理の イベント・ハンドラを呼び出し */
            vd_g_GyroDevEventGo((U1)GYRO_EVENT_SEQ_COMP);
        }
        else{
            u4_s_gyro_linktim++;
        }
        break;

    default:
        /* シーケンスアイドルに設定 */
        vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);
        break;
    }
}

/*===================================================================================================================================*/
/*  static void     vd_s_GyroDevSeqGyrShutDn1(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevSeqGyrShutDn1(void)
{
    /* GYRO終了(1)処理シーケンス */

    U1              u1_t_sts;       /* I2C,サブ関数処理状況チェック */
    U1              u1_t_timchk;    /* 経過時間判定 */
    Dio_LevelType   dl_t_sts;       /* ポート読出し値 */

    u1_t_sts    = (U1)FALSE;
    u1_t_timchk = (U1)FALSE;
    dl_t_sts    = (Dio_LevelType)GYRO_DIO_LOW;

    /* Ackタイムアウト用カウンタインクリメント */
    if(u4_s_gyro_acktime < (U4)U4_MAX){
        u4_s_gyro_acktime++;
    }
    
    switch (st_s_gyro_seqmng.u1_step)
    {
    case (U1)GYRO_SEQ_SHUTDN1_1:
        /* SENSOR-ON端子状態取得処理 */
        dl_t_sts    = dl_GYRO_DIO_READ_SENSOR_ON();

        if(dl_t_sts == (Dio_LevelType)GYRO_DIO_LOW){
            /* フェール動作によりSENSOR-ON=Lo (センサ電源OFF) になっている */
            /* シーケンスアイドルに設定*/
            vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);
            /* SENSOR_ON異常なので終了フロー(1)を終了 */
            vd_g_GyroDevEventGo((U1)GYRO_EVENT_SHTDN_ERR);
        }
        else{
            /* カウンタクリア */
            u1_s_cnt_shutdn             = (U1)0U;
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_SHUTDN1_2;
        }
        break;

    case (U1)GYRO_SEQ_SHUTDN1_2:
        u1_t_sts    = GYRO_I2C_WRITE_GYRO(&u2_s_gyro_regstep, (U2)GYRO_WRISTEP_MODE_OFF_GYR, st_sp_GYRO_WRISTEP_MODE_OFF_GYR,
                                            &u4_s_gyro_acktime, st_sp_MCU_SYS_PWR_GYR_REG_GYR_MODE_OFF, &u2_s_gyro_i2cwaittim);
        if(u1_t_sts == (U1)TRUE){
            /* GYROモードをSuspendに設定する */
            st_s_gyro_ctrl.u1_dev_mode  = (U1)GYRO_DEV_MODE_NORMAL;
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_SHUTDN1_3;
        }
        break;

    case (U1)GYRO_SEQ_SHUTDN1_3:
        /* Wati t21 */
        u1_t_timchk = u1_s_GyroDevTimCheck(u4_s_gyro_linktim, (U4)GYRO_WAIT_T21);
        if(u1_t_timchk  == (U1)TRUE){
            /* Wati t21完了 次のシーケンスへ */
            u4_s_gyro_linktim           = (U4)0U;
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_SHUTDN1_4;
        }
        else{
            u4_s_gyro_linktim++;
        }
        break;

    case (U1)GYRO_SEQ_SHUTDN1_4:
        u1_t_sts    = GYRO_I2C_READ_GYRO(&u2_s_gyro_regstep, &u4_s_gyro_acktime, st_sp_MCU_SYS_PWR_GYR_REG_GYR_MODE_RD, &u2_s_gyro_i2cwaittim);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_step = (U1)GYRO_SEQ_SHUTDN1_5;
        }
        break;

    case (U1)GYRO_SEQ_SHUTDN1_5:
        if(st_sp_MCU_SYS_PWR_GYR_REG_GYR_MODE_RD[GYRO_READPOS_1].u1p_pdu[GYRO_READPOS_1] == (U1)GYRO_DAT_GYROMODE_SUSPEND){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_SHUTDN1_8;
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_PARASET2_1;
        }
        else{
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_step = (U1)GYRO_SEQ_SHUTDN1_6;
        }
        break;

    case (U1)GYRO_SEQ_SHUTDN1_6:
        /* Wati t18 */
        u1_t_timchk = u1_s_GyroDevTimCheck(u4_s_gyro_linktim, (U4)GYRO_WAIT_T18);
        if(u1_t_timchk  == (U1)TRUE){
            /* Wati t11完了 次のシーケンスへ */
            u4_s_gyro_linktim           = (U4)0U;
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_SHUTDN1_7;
        }
        else{
            u4_s_gyro_linktim++;
        }
        break;

    case (U1)GYRO_SEQ_SHUTDN1_7:
        if(u1_s_cnt_shutdn >= (U1)GYRO_CNT_SHUTDN1_RTRY_MAX){
            /* カウンタクリア */
            u1_s_cnt_shutdn             = (U1)0U;

            /* ダイレコ記録 */

            /* シーケンスアイドルに設定 */
            vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);

            /* リトライ回数オーバーなので終了フロー(1)を終了 */
            vd_g_GyroDevEventGo((U1)GYRO_EVENT_SHTDN_ERR);
        }
        else{
            /* カウンタ+1 */
            u1_s_cnt_shutdn++;

            /* 次のシーケンスへ(ModeChange(Gyro)OFFに戻る) */
            st_s_gyro_seqmng.u1_step = (U1)GYRO_SEQ_SHUTDN1_2;
        }
        break;

    case (U1)GYRO_SEQ_SHUTDN1_8:
        /* Wati t10(1ms待機)は本caseに到達した時点で満たしていると判断するためwait処理は実施しない */
        /* 次のシーケンスへ */
        st_s_gyro_seqmng.u1_step = (U1)GYRO_SEQ_SHUTDN1_9;
        break;

    case (U1)GYRO_SEQ_SHUTDN1_9:
        u1_t_sts    = u1_s_GyroDevParamSet2();
        if(u1_t_sts == (U1)GYRO_RET_OK){
            /* シーケンスアイドルに設定 */
            vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);

            /* 確認成功なので終了フロー(1)を終了 */
            vd_g_GyroDevEventGo((U1)GYRO_EVENT_SEQ_COMP);
        }
        break;
    
    default:
        /* シーケンスアイドルに設定 */
        vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);
        break;
    }
}

/*===================================================================================================================================*/
/*  static U1       u1_s_GyroDevParamSet2(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_GyroDevParamSet2(void)
{
    U1              u1_t_ret;       /* シーケンス完了通知 */
    U1              u1_t_sts;       /* I2C,サブ関数処理状況チェック */
    U1              u1_t_impact;    /* 衝撃検知有効_出力確認 */
    Dio_LevelType   dl_t_sts;       /* ポート読出し値 */

    u1_t_ret    = (U1)GYRO_RET_INPROC;
    u1_t_sts    = (U1)FALSE;
    u1_t_impact = (U1)FALSE;
    dl_t_sts    = (Dio_LevelType)GYRO_DIO_LOW;

    switch (st_s_gyro_seqmng.u1_subtype)
    {
    case GYRO_SEQ_PARASET2_1:
        /* IF提供前なので常に"No(OFFあるいは保持値なしの場合)"で処理する */
        /* ToDo：IF置き換え */
        u1_t_impact = (U1)FALSE;
        if(u1_t_impact  == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_PARASET2_2;
        }
        else{
            /* パラメータバックアップ処理に遷移 */ 
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_PARASET2_10;
        }
        break;

    case (U1)GYRO_SEQ_PARASET2_2:
        u1_t_sts    = GYRO_I2C_WRITE_ACC(&u2_s_gyro_regstep, (U2)GYRO_WRISTEP_INPRM_SEN1_BW_ACC, st_sp_GYRO_WRISTEP_INPRM_SEN1_BW_ACC,
                                            &u4_s_gyro_acktime, st_sp_MCU_SYS_PWR_GYR_REG_ACC_SEN1_BW_INPRM, &u2_s_gyro_i2cwaittim);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_PARASET2_3;
        }
        break;

    case (U1)GYRO_SEQ_PARASET2_3:
        /* Wati t19(1ms待機)は本caseに到達した時点で満たしていると判断するためwait処理は実施しない */
        /* カウンタクリア */
        u1_s_cnt_g_read         = (U1)0U;
        u2_s_cnt_diff_verif     = (U2)0U;

        /* 次のシーケンスへ */
        st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_PARASET2_4;
        break;

    case (U1)GYRO_SEQ_PARASET2_4:
        /* k(5_3)インクリメント */
        u2_s_cnt_diff_verif++;

        /* MAX,MINクリア */
        vd_s_GyroDevAccDataClear();

        /* 次のシーケンスへ */
        st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_PARASET2_5;
        break;

    case (U1)GYRO_SEQ_PARASET2_5:
        dl_t_sts    = dl_GYRO_DIO_READ_V33PERI();

        if(dl_t_sts == (Dio_LevelType)GYRO_DIO_HIGH){
            /* 終了フロー(1)の実施条件未達のため「GYRO終了(1)処理正常完了」へ遷移 */
            /* シーケンスアイドルに設定 */
            vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);

            /* 終了フロー(1)を終了 */
            vd_g_GyroDevEventGo((U1)GYRO_EVENT_SEQ_COMP);
        }
        else{
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_PARASET2_6;
        }
        break;

    case (U1)GYRO_SEQ_PARASET2_6:
        /* Read data (Gセンサ) */
        u1_t_sts    = GYRO_I2C_READ_ACC(&u2_s_gyro_regstep, &u4_s_gyro_acktime, st_sp_MCU_SYS_PWR_GYR_REG_GYR_XYZ, &u2_s_gyro_i2cwaittim);
        if(u1_t_sts == (U1)TRUE){
            st_s_gyro_accdat.st_calc.u1_acc_x_lsb       = st_sp_MCU_SYS_PWR_GYR_REG_GYR_XYZ[GYRO_READPOS_1].u1p_pdu[GYRO_READPOS_1];
            st_s_gyro_accdat.st_calc.u1_acc_x_msb       = st_sp_MCU_SYS_PWR_GYR_REG_GYR_XYZ[GYRO_READPOS_1].u1p_pdu[GYRO_READPOS_2];
            st_s_gyro_accdat.st_calc.u1_acc_y_lsb       = st_sp_MCU_SYS_PWR_GYR_REG_GYR_XYZ[GYRO_READPOS_1].u1p_pdu[GYRO_READPOS_3];
            st_s_gyro_accdat.st_calc.u1_acc_y_msb       = st_sp_MCU_SYS_PWR_GYR_REG_GYR_XYZ[GYRO_READPOS_1].u1p_pdu[GYRO_READPOS_4];
            st_s_gyro_accdat.st_calc.u1_acc_z_lsb       = st_sp_MCU_SYS_PWR_GYR_REG_GYR_XYZ[GYRO_READPOS_1].u1p_pdu[GYRO_READPOS_5];
            st_s_gyro_accdat.st_calc.u1_acc_z_msb       = st_sp_MCU_SYS_PWR_GYR_REG_GYR_XYZ[GYRO_READPOS_1].u1p_pdu[GYRO_READPOS_6];

            st_s_gyro_accdat.st_calc.st_acc_xyz.s2_x    = (S2)(((U2)st_s_gyro_accdat.st_calc.u1_acc_x_msb << (U2)GYRO_SHIFT_8) | (U2)st_s_gyro_accdat.st_calc.u1_acc_x_lsb);
            st_s_gyro_accdat.st_calc.st_acc_xyz.s2_y    = (S2)(((U2)st_s_gyro_accdat.st_calc.u1_acc_y_msb << (U2)GYRO_SHIFT_8) | (U2)st_s_gyro_accdat.st_calc.u1_acc_y_lsb);
            st_s_gyro_accdat.st_calc.st_acc_xyz.s2_z    = (S2)(((U2)st_s_gyro_accdat.st_calc.u1_acc_z_msb << (U2)GYRO_SHIFT_8) | (U2)st_s_gyro_accdat.st_calc.u1_acc_z_lsb);

            /* GセンサRead回数(k(5_2))カウント */
            u1_s_cnt_g_read++;
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_PARASET2_7;
        }
        break;
    
    case (U1)GYRO_SEQ_PARASET2_7:
        /* GセンサMAX,MIN更新 */
        vd_s_GyroDevAccMinMaxUpdate();

        /* 次のシーケンスへ */
        st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_PARASET2_8;
        break;

    case (U1)GYRO_SEQ_PARASET2_8:
        /* Wati t20(1ms待機)は本caseに到達した時点で満たしていると判断するためwait処理は実施しない */
        /* GセンサRead回数(k(5_2))が規定回数に到達したかチェック */
        if(u1_s_cnt_g_read > (U1)GYRO_CNT_PARASET_ACC_READ){
            /* GセンサRead回数(k(5_2))クリア */
            u1_s_cnt_g_read = (U1)0U;

            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_PARASET2_9;
        }
        else{
            /* GセンサReadに遷移 */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_PARASET2_5;
        }
        break;

    case (U1)GYRO_SEQ_PARASET2_9:
        /* 差分確認|MAX-MIN|処理 */
        u1_t_sts = u1_s_GyroDevAccMinMaxCheck();

        /* 比較結果チェック */
        if(u1_t_sts != (U1)GYRO_RET_OK){
            /* 差分確認回数(k(5_3))チェック */
            if(u2_s_cnt_diff_verif < (U2)GYRO_CNT_PARASET_ACC_VERI){
                /* 規定回数未満のため再Read,比較に遷移 */
                st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_PARASET2_4;
            }
            else{
                /* 規定回数到達 入力パラメータ設定(2)終了 */
                u1_t_ret    = (U1)GYRO_RET_OK;
            }
        }
        else{
            /* 規定G値未満 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_PARASET2_10;
        }
        break;

    case (U1)GYRO_SEQ_PARASET2_10:
        /* "入力パラメータ保持" で保持していた設定を書込み */
        /* ToDo：IFの挿入 */
        /* 入力パラメータ設定(2)終了 */
        u1_t_ret    = (U1)GYRO_RET_OK;
        break;

    default:
        /* シーケンスアイドルに設定 */
        vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);
        break;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static void     vd_s_GyroDevAccDataClear(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevAccDataClear(void)
{
    /* MAX値、MIN値クリア処理 */

    U1  u1_t_errflg_bk;

    /* エラーログ退避 */
    u1_t_errflg_bk  = st_s_gyro_accdat.u1_errlog_sts;

    /* MAX値、MIN値クリア処理 */
    vd_s_GyroDevMemset(&st_s_gyro_accdat,     (U1)0U, (U4)sizeof(st_s_gyro_accdat));
    
    /* エラーログあった場合、フラグ保留 */
    if(u1_t_errflg_bk   == (U1)TRUE){
        st_s_gyro_accdat.u1_errlog_sts  = (U1)TRUE;
    }
    else{
        /* do nothing */
    }
}

/*===================================================================================================================================*/
/*  static void     vd_s_GyroDevAccMinMaxUpdate(void)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevAccMinMaxUpdate(void)
{
    /* X軸、Y軸、Z軸の取得データに対して、それぞれのMAX値とMIN値を更新する */

    if(st_s_gyro_accdat.u1_updatecnt == (U1)0U){
        /* 初回更新時は判定せずに更新する */
        st_s_gyro_accdat.st_max = st_s_gyro_accdat.st_calc.st_acc_xyz;
        st_s_gyro_accdat.st_min = st_s_gyro_accdat.st_calc.st_acc_xyz;
    }
    else{
        /* 初回更新移行 */
        /* X軸 */
        if(st_s_gyro_accdat.st_calc.st_acc_xyz.s2_x > st_s_gyro_accdat.st_max.s2_x){
            st_s_gyro_accdat.st_max.s2_x = st_s_gyro_accdat.st_calc.st_acc_xyz.s2_x;
        }
        else if(st_s_gyro_accdat.st_calc.st_acc_xyz.s2_x < st_s_gyro_accdat.st_min.s2_x){
            st_s_gyro_accdat.st_min.s2_x = st_s_gyro_accdat.st_calc.st_acc_xyz.s2_x;
        }
        else{
            /* do nothing */
        }

        /* Y軸 */
        if(st_s_gyro_accdat.st_calc.st_acc_xyz.s2_y > st_s_gyro_accdat.st_max.s2_y){
            st_s_gyro_accdat.st_max.s2_y = st_s_gyro_accdat.st_calc.st_acc_xyz.s2_y;
        }
        else if(st_s_gyro_accdat.st_calc.st_acc_xyz.s2_y < st_s_gyro_accdat.st_min.s2_y){
            st_s_gyro_accdat.st_min.s2_y = st_s_gyro_accdat.st_calc.st_acc_xyz.s2_y;
        }
        else{
            /* do nothing */
        }

        /* Z軸 */
        if(st_s_gyro_accdat.st_calc.st_acc_xyz.s2_z > st_s_gyro_accdat.st_max.s2_z){
            st_s_gyro_accdat.st_max.s2_z = st_s_gyro_accdat.st_calc.st_acc_xyz.s2_z;
        }
        else if(st_s_gyro_accdat.st_calc.st_acc_xyz.s2_z < st_s_gyro_accdat.st_min.s2_z){
            st_s_gyro_accdat.st_min.s2_z = st_s_gyro_accdat.st_calc.st_acc_xyz.s2_z;
        }
        else{
            /* do nothing */
        }
    }
    /* 更新回数インクリメント */
    st_s_gyro_accdat.u1_updatecnt++;
}


/*===================================================================================================================================*/
/*  static U1       u1_s_GyroDevAccMinMaxCheck(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_GyroDevAccMinMaxCheck(void)
{
    U1      u1_t_ret;
    S4      s4_t_modval;

    u1_t_ret    = (U1)GYRO_RET_OK;  /* 差分確認成功 */
    s4_t_modval = (S4)0U;

    /* ダイレコ記録(1回だけ) */
    if((st_s_gyro_accdat.u1_updatecnt < (U1)GYRO_CNT_PARASET_ACC_READ)   &&
       (st_s_gyro_accdat.u1_errlog_sts == (U1)FALSE)){
        /* ToDo：ダイレコ記録用IFの挿入 */
        st_s_gyro_accdat.u1_errlog_sts = (U1)TRUE;
    }

    /* 軸情報有効個数50個未満チェック */
    if(st_s_gyro_accdat.u1_updatecnt < (U1)GYRO_CNT_PARASET_ACC_READERR){
        /* 軸情報有効個数50個未満の場合、エラーで戻る */
        u1_t_ret    = (U1)GYRO_RET_NG;
    }
    else{
        /* |MAX-MIN|をチェック処理 */
        /* X軸 */
        s4_t_modval = (S4)((S4)st_s_gyro_accdat.st_max.s2_x - (S4)st_s_gyro_accdat.st_min.s2_x);
        if(s4_t_modval >= (S4)GYRO_CNT_PARASET_ACC_FIX_STAB){
            /* 差分確認失敗 */
            u1_t_ret    = (U1)GYRO_RET_NG;
        }
        /* Y軸 */
        s4_t_modval = (S4)((S4)st_s_gyro_accdat.st_max.s2_y - (S4)st_s_gyro_accdat.st_min.s2_y);
        if(s4_t_modval >= (S4)GYRO_CNT_PARASET_ACC_FIX_STAB){
            /* 差分確認失敗 */
            u1_t_ret    = (U1)GYRO_RET_NG;
        }
        /* X軸 */
        s4_t_modval = (S4)((S4)st_s_gyro_accdat.st_max.s2_z - (S4)st_s_gyro_accdat.st_min.s2_z);
        if(s4_t_modval >= (S4)GYRO_CNT_PARASET_ACC_FIX_STAB){
            /* 差分確認失敗 */
            u1_t_ret    = (U1)GYRO_RET_NG;
        }
    }

    return(u1_t_ret);
}

/**************************↑シーケンス管理(END)↑***************************/

/**************************↓共通関数(START)↓*************************/
/*===================================================================================================================================*/
/*  static void     vd_s_GyroDevMemset(void * vdp_a_dst, const U1 u1_a_DATA, U4 u4_a_size)                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevMemset(void * vdp_a_dst, const U1 u1_a_DATA, U4 u4_a_size)
{
    U1 * u1p_udst;
    
    u1p_udst = (U1 *)vdp_a_dst;

    while ((U4)0U < u4_a_size){
        u4_a_size--;
        *u1p_udst = u1_a_DATA;
        u1p_udst++;
    }
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroDevForceEnd(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevForceEnd(void)
{
    /* SENSOR_ON LO処理 */
    dl_GYRO_DIO_WRITE_SENSOR_ON_L();

    /* ジャイロモードをSuspendに設定する */
    vd_s_GyroDevCtlMngModSet(GYRO_DEV_MODE_SUSPEND);
}

/*===================================================================================================================================*/
/* static U1       u1_s_GyroDevTimCheck(const U4 u4_a_SRC, const U4 u4_a_TRGT)                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_GyroDevTimCheck(const U4 u4_a_SRC, const U4 u4_a_TRGT)
{
    U1      u1_t_ret;

    u1_t_ret    = (U1)FALSE;

    if(u4_a_SRC > u4_a_TRGT){
        u1_t_ret    = (U1)TRUE;
    }

    return(u1_t_ret);
}
/**************************↑共通関数(END)↑***************************/



/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    05/21/2025  TN       New. Specification version 2.0 W/O 7.1,7.2                                                         */
/*                                                                                                                                   */
/*  * TN   = Tetsu Naruse, Denso Techno                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/
