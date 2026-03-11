/************************************************************************************************/
/* file Name        : VIS_Can.h                                                                 */
/* contents         : CAN module header                                                         */
/* maker            : NCOS                                                                      */
/* change history   :                                                                           */
/* ---------------------------------------------------------------------------------------------*/
/* ver   | Comments                                                                             */
/* ---------------------------------------------------------------------------------------------*/
/* v1.00 | New created                                                                          */
/************************************************************************************************/

#ifndef VIS_CAN_H
#define VIS_CAN_H
/* ----------------------------------------------------------------------------------------------------------- */
#include "VIS.h"
/* ----------------------------------------------------------------------------------------------------------- */
/* 絶対時刻 */
#define VIS_CAN_UTC_RX_NBYTE                    ((U1)8U)            /* CAN受信：RSE1G20バイト数 */
#define VIS_CAN_UTC_RX_YEAR                     ((U1)2U)            /* CAN受信：年格納領域 */
#define VIS_CAN_UTC_RX_MONTH                    ((U1)3U)            /* CAN受信：月格納領域 */
#define VIS_CAN_UTC_RX_DAY                      ((U1)4U)            /* CAN受信：日格納領域 */
#define VIS_CAN_UTC_RX_HOUR                     ((U1)5U)            /* CAN受信：時格納領域 */
#define VIS_CAN_UTC_RX_MIN                      ((U1)6U)            /* CAN受信：分格納領域 */
#define VIS_CAN_UTC_RX_SEC                      ((U1)7U)            /* CAN受信：秒格納領域 */
#define VIS_CAN_UTC_YEARMIN                     ((U1)0x00U)         /* UTC時刻情報年最小値 */
#define VIS_CAN_UTC_MONTMIN                     ((U1)0x01U)         /* UTC時刻情報月最小値 */
#define VIS_CAN_UTC_DAYMIN                      ((U1)0x01U)         /* UTC時刻情報日最小値 */
#define VIS_CAN_UTC_HOURMIN                     ((U1)0x00U)         /* UTC時刻情報時最小値 */
#define VIS_CAN_UTC_MINMIN                      ((U1)0x00U)         /* UTC時刻情報分最小値 */
#define VIS_CAN_UTC_SECMIN                      ((U1)0x00U)         /* UTC時刻情報秒最小値 */
#define VIS_CAN_UTC_YEARMAX                     ((U1)0x99U)         /* UTC時刻情報年最大値 */
#define VIS_CAN_UTC_MONTMAX                     ((U1)0x12U)         /* UTC時刻情報月最大値 */
#define VIS_CAN_UTC_DAYMAX                      ((U1)0x31U)         /* UTC時刻情報日最大値 */
#define VIS_CAN_UTC_HOURMAX                     ((U1)0x23U)         /* UTC時刻情報時最大値 */
#define VIS_CAN_UTC_MINMAX                      ((U1)0x59U)         /* UTC時刻情報分最大値 */
#define VIS_CAN_UTC_SECMAX                      ((U1)0x59U)         /* UTC時刻情報秒最大値 */
#define VIS_CAN_UTC_DECIMALMAX                  ((U1)9U)            /* BCDフォーマット最大値 */
#define VIS_CAN_UTC_FAIL                        ((U1)0xFFU)         /* UTC時刻情報Fail値 */
#define VIS_CAN_UTC_SHIFT_4BIT                  ((U1)4U)            /* ビットシフト：4bit */

/* オドメータ */
#define VIS_CAN_ODO_RX_NBYTE                    ((U1)8U)            /* CAN受信：MET1S02バイト数 */
#define VIS_CAN_ODO_RX_UNIT                     ((U1)3U)            /* CAN受信：オド単位格納領域 */
#define VIS_CAN_ODO_RX_POS1                     ((U1)4U)            /* CAN受信：オドメータ情報格納領域(1Byte目) */
#define VIS_CAN_ODO_RX_POS2                     ((U1)5U)            /* CAN受信：オドメータ情報格納領域(2Byte目) */
#define VIS_CAN_ODO_RX_POS3                     ((U1)6U)            /* CAN受信：オドメータ情報格納領域(3Byte目) */
#define VIS_CAN_ODO_RX_POS4                     ((U1)7U)            /* CAN受信：オドメータ情報格納領域(4Byte目) */
#define VIS_CAN_ODO_UNITMASK                    ((U1)0x30U)         /* CAN受信：オド単位取得マスク値 */
#define VIS_CAN_ODO_UNIT_INVALID                ((U1)0U)            /* オド単位異常 */
#define VIS_CAN_ODO_UNIT_KM                     ((U1)1U)            /* オド単位Km */
#define VIS_CAN_ODO_UNIT_MILE                   ((U1)2U)            /* オド単位Mile */
#define VIS_CAN_ODO_UNIT_NON                    ((U1)3U)            /* オド単位情報なし */
#define VIS_CAN_ODO_LSB                         ((U4)10U)           /* LSB変換(1km→0.1km) */
#define VIS_CAN_ODO_MILE_TO_KM                  ((U4)1609U)         /* Mile→km変換値(1mile = 1.609km) */
#define VIS_CAN_ODO_MILE_LSB                    ((U4)100U)          /* LSB変換(1m→0.1km) */
#define VIS_CAN_ODO_MAX                         ((U4)999999U)       /* オドメータ情報最大値 */
#define VIS_CAN_ODO_FAIL                        ((U4)0x00000000U)   /* オドメータ情報Fail値 */

/* 車速 */
#define VIS_CAN_SPD_MAX                         ((U2)0x00FFU)       /* 車速最大値 */
#define VIS_CAN_SPD_LSB                         ((U2)100U)          /* LSB変換(0.01km/h→1km/h) */
#define VIS_CAN_SPD_FAIL                        ((U1)0xFFU)         /* 車速Fail値 */

/* 電動システム起動状態 */
#define VIS_CAN_E_PWRCTRLSYS_RDYSTS_OFF         ((U1)0x00U)         /* 電動システム起動状態(消灯) */
#define VIS_CAN_E_PWRCTRLSYS_RDYSTS_ON          ((U1)0x01U)         /* 電動システム起動状態(点灯) */
#define VIS_CAN_DRDYSTS_NON                     ((U1)0x00U)         /* "Ready"インジケータ表示状態:消灯       */
#define VIS_CAN_DRDYSTS_BLINK                   ((U1)0x01U)         /* "Ready"インジケータ表示状態:点滅 (2Hz) */
#define VIS_CAN_DRDYSTS_LIGHT                   ((U1)0x02U)         /* "Ready"インジケータ表示状態:点灯       */
#define VIS_CAN_DRDYSTS_UNDEFINED               ((U1)0x03U)         /* "Ready"インジケータ表示状態:未定義     */

/* VINデータ */
#define VIS_CAN_VIN_RX_NBYTE                    ((U1)32U)           /* CAN受信：ENG1S51バイト数 */
#define VIS_CAN_VIN0_NM                         ((U1)0U)            /* VIN情報(要素0)  */
#define VIS_CAN_VIN1_NM                         ((U1)1U)            /* VIN情報(要素1)  */
#define VIS_CAN_VIN2_NM                         ((U1)2U)            /* VIN情報(要素2)  */
#define VIS_CAN_VIN3_NM                         ((U1)3U)            /* VIN情報(要素3)  */
#define VIS_CAN_VIN4_NM                         ((U1)4U)            /* VIN情報(要素4)  */
#define VIS_CAN_VIN5_NM                         ((U1)5U)            /* VIN情報(要素5)  */
#define VIS_CAN_VIN6_NM                         ((U1)6U)            /* VIN情報(要素6)  */
#define VIS_CAN_VIN7_NM                         ((U1)7U)            /* VIN情報(要素7)  */
#define VIS_CAN_VIN8_NM                         ((U1)8U)            /* VIN情報(要素8)  */
#define VIS_CAN_VIN9_NM                         ((U1)9U)            /* VIN情報(要素9)  */
#define VIS_CAN_VIN10_NM                        ((U1)10U)           /* VIN情報(要素10) */
#define VIS_CAN_VIN11_NM                        ((U1)11U)           /* VIN情報(要素11) */
#define VIS_CAN_VIN12_NM                        ((U1)12U)           /* VIN情報(要素12) */
#define VIS_CAN_VIN13_NM                        ((U1)13U)           /* VIN情報(要素13) */
#define VIS_CAN_VIN14_NM                        ((U1)14U)           /* VIN情報(要素14) */
#define VIS_CAN_VIN15_NM                        ((U1)15U)           /* VIN情報(要素15) */
#define VIS_CAN_VIN16_NM                        ((U1)16U)           /* VIN情報(要素16) */

#define VIS_CAN_RCV_CHK                         ((U1)0x01)          /* CAN受信値確認 */
#define VIS_CAN_RCV_PWRERRST_CHK                ((U1)0x1F)          /* CAN受信値確認(PWRERRST用) */
#define VIS_CAN_INIT_0                          ((U1)0x00U)         /* 変数初期化用 */
#define VIS_CAN_TRANSREQ_DATA_RECEIVEVAL        ((U1)0U)            /* チップ間通信：受信値格納領域 */
#define VIS_CAN_TRANSREQ_DATA_RETURNVAL         ((U1)1U)            /* チップ間通信：受信状態格納領域 */
#define VIS_CAN_TRANSREQ_VINDATA_RETURNVAL      ((U1)17U)           /* チップ間通信：VIN受信状態格納領域 */
#define VIS_CAN_TRANSREQ_DATA_YEAR              ((U1)0U)            /* チップ間通信：年情報格納領域 */
#define VIS_CAN_TRANSREQ_DATA_MONT              ((U1)1U)            /* チップ間通信：月情報格納領域 */
#define VIS_CAN_TRANSREQ_DATA_DAY               ((U1)2U)            /* チップ間通信：日情報格納領域 */
#define VIS_CAN_TRANSREQ_DATA_HOUR              ((U1)3U)            /* チップ間通信：時情報格納領域 */
#define VIS_CAN_TRANSREQ_DATA_MIN               ((U1)4U)            /* チップ間通信：分情報格納領域 */
#define VIS_CAN_TRANSREQ_DATA_SEC               ((U1)5U)            /* チップ間通信：秒情報格納領域 */
#define VIS_CAN_TRANSREQ_DATA_UTCNUM            ((U1)6U)            /* チップ間通信：UTC時刻情報要素数 */
#define VIS_CAN_TRANSREQ_DATA_ODOPOS1           ((U1)0U)            /* チップ間通信：1BYTE目格納領域 */
#define VIS_CAN_TRANSREQ_DATA_ODOPOS2           ((U1)1U)            /* チップ間通信：2BYTE目格納領域 */
#define VIS_CAN_TRANSREQ_DATA_ODOPOS3           ((U1)2U)            /* チップ間通信：3BYTE目格納領域 */
#define VIS_CAN_TRANSREQ_DATA_ODOPOS4           ((U1)3U)            /* チップ間通信：4BYTE目格納領域 */
#define VIS_CAN_TRANSREQ_DATA_ODONUM            ((U1)4U)            /* チップ間通信：オドメータ情報要素数 */
#define VIS_CAN_TRANSREQ_DATA_TRIPPOS1          ((U1)0U)            /* チップ間通信：TRIPカウンタ1BYTE目格納領域 */
#define VIS_CAN_TRANSREQ_DATA_TRIPPOS2          ((U1)1U)            /* チップ間通信：TRIPカウンタ2BYTE目格納領域 */
#define VIS_CAN_TRANSREQ_DATA_SYNC              ((U1)2U)            /* チップ間通信：マスタ同期情報格納領域 */
#define VIS_CAN_TRANSREQ_DATA_TRIPNUM           ((U1)3U)            /* チップ間通信：TRIPカウンタ情報要素数 */
#define VIS_CAN_TRANSREQ_DATA_LENGTH_1          ((U2)1U)            /* チップ間通信：データ長(1byte) */
#define VIS_CAN_TRANSREQ_DATA_LENGTH_2          ((U2)2U)            /* チップ間通信：データ長(2byte) */
#define VIS_CAN_TRANSREQ_DATA_LENGTH_18         ((U2)18U)           /* チップ間通信：データ長(18byte) */
#define VIS_CAN_SHIFT_4BIT                      ((U4)4U)            /* ビットシフト：4bit */
#define VIS_CAN_SHIFT_1BYTE                     ((U4)8U)            /* ビットシフト：1BYTE */
#define VIS_CAN_SHIFT_2BYTE                     ((U4)16U)           /* ビットシフト：2BYTE */
#define VIS_CAN_SHIFT_3BYTE                     ((U4)24U)           /* ビットシフト：3BYTE */
#define VIS_CAN_4BYTEMASK_1BYTE                 ((U4)0x000000FFU)
#define VIS_CAN_4BYTEMASK_2BYTE                 ((U4)0x0000FF00U)
#define VIS_CAN_4BYTEMASK_3BYTE                 ((U4)0x00FF0000U)
#define VIS_CAN_4BYTEMASK_4BYTE                 ((U4)0xFF000000U)
#define VIS_CAN_2BYTEMASK_LOW                   ((U2)0x00FFU)
#define VIS_CAN_2BYTEMASK_HIGH                  ((U2)0xFF00U)
#define VIS_CAN_1BYTEMASK_LOW                   ((U1)0x0FU)

#define VIS_CAN_COM_IPDUST_OK                   ((U1)0U)            /* CANメッセージ受信状態：正常受信 */
/* ----------------------------------------------------------------------------------------------------------- */
void vd_g_VISCanInit(void);
void vd_g_VISCanMidCyc(void);
/* ----------------------------------------------------------------------------------------------------------- */

#endif/*VIS_CAN_H*/
