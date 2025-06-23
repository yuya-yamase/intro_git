/* ----------------------------------------------------------------------------------------------------------- */
/* file name    :   VIS_CAN.h                                                                                  */
/* ----------------------------------------------------------------------------------------------------------- */
#ifndef VIS_CAN_H
#define VIS_CAN_H
/* ----------------------------------------------------------------------------------------------------------- */
#include "VIS.h"
/* ----------------------------------------------------------------------------------------------------------- */
/* 絶対時刻 */
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
#define VIS_CAN_UTC_FAIL                        ((U1)0xFFU)         /* UTC時刻情報Fail値 */

/* オドメータ */
#define VIS_CAN_ODO_UNIT_INVALID                ((U1)0U)            /* オド単位異常 */
#define VIS_CAN_ODO_UNIT_KM                     ((U1)1U)            /* オド単位Km */
#define VIS_CAN_ODO_UNIT_MILE                   ((U1)2U)            /* オド単位Mile */
#define VIS_CAN_ODO_UNIT_NON                    ((U1)3U)            /* オド単位情報なし */
#define VIS_CAN_ODO_LSB                         (10U)               /* LSB変換(1km→0.1km) */
#define VIS_CAN_ODO_MILE_TO_KM                  (161U)              /* Mile→km変換値 */
#define VIS_CAN_ODO_MAX                         (9999990U)          /* オドメータ情報最大値(LSB0.1km) */
#define VIS_CAN_ODO_MASK                        (0x000000FFU)       /* オドメータ情報マスク値 */
#define VIS_CAN_ODO_FAIL                        (0x00000000U)       /* オドメータ情報Fail値 */

/* 時間情報 */
#define VIS_CAN_TRIP_MASK                       ((U2)0x00FF)        /* Tripカウンタ情報マスク値 */
#define VIS_CAN_TRIP_FAIL                       ((U2)0xFFFFU)       /* TripカウンタFail値 */

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
#define VIS_CAN_TRANSREQ_DATA_RECEIVEVAL        ((U1)0U)            /* チップ間通信：受信値格納領域 */
#define VIS_CAN_TRANSREQ_DATA_RETURNVAL         ((U1)1U)            /* チップ間通信：受信状態格納領域 */
#define VIS_CAN_TRANSREQ_VINDATA_RETURNVAL      ((U1)17U)           /* チップ間通信：VIN受信状態格納領域 */
#define VIS_CAN_TRANSREQ_DATA_LENGTH_2          ((U2)2U)            /* チップ間通信：データ長(2byte) */
#define VIS_CAN_TRANSREQ_DATA_LENGTH_18         ((U2)18U)           /* チップ間通信：データ長(18byte) */

#define VIS_CAN_COM_IPDUST_OK                   ((U1)0U)            /* CANメッセージ受信状態：正常受信 */
/* ----------------------------------------------------------------------------------------------------------- */
void vd_g_VISCanInit(void);
void vd_g_VISCanMidCyc(void);
/* ----------------------------------------------------------------------------------------------------------- */

#endif/*VIS_CAN_H*/
