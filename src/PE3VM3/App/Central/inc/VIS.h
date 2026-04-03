/************************************************************************************************/
/* file Name        : VIS.h                                                                     */
/* contents         : External header                                                           */
/* maker            : NCOS                                                                      */
/* change history   :                                                                           */
/* ---------------------------------------------------------------------------------------------*/
/* ver   | Comments                                                                             */
/* ---------------------------------------------------------------------------------------------*/
/* v1.00 | New created                                                                          */
/************************************************************************************************/

#ifndef VIS_H
#define VIS_H
/* -------------------------------------------------------------------------- */
#include "Std_Types.h"
#include "aip_common.h"
/* -------------------------------------------------------------------------- */
#define VIS_UTC_INIT                                        ((U1)0xFFU)     /* UTC時刻情報初期値 */
#define VIS_ODO_INIT                                        ((U1)0x00U)     /* オドメータ情報初期値 */
#define VIS_TRIP_INIT                                       ((U1)0xFFU)     /* Tripカウンタ情報初期値 */
#define VIS_CAN_TRIP_FAIL                                   ((U2)0xFFFFU)   /* TripカウンタFail値 */
#define VIS_CAN_TRIP_ASYNC                                  ((U1)0x00U)     /* Tripカウンタ非同期 */
#define VIS_CAN_TRIP_SYNC                                   ((U1)0x01U)     /* Tripカウンタ同期 */
#define VIS_SPD_INIT                                        ((U1)0xFFU)     /* 車速情報初期値 */
#define VIS_RDYSTS_INIT                                     ((U1)0x00U)     /* 電動システム起動状態初期値 */
#define VIS_BAT_INIT                                        ((U1)0x00U)     /* ECU電源電圧初期値 */

#define VIS_BASICSTATE_PARKING                              ((U1)0x00U)     /* 駐車中 */
#define VIS_BASICSTATE_RIDING                               ((U1)0x01U)     /* 乗車中 */
#define VIS_BASICSTATE_POWERON_NORMAL                       ((U1)0x02U)     /* PowerON通常 */
#define VIS_BASICSTATE_POWERON_EMERGENCY                    ((U1)0x03U)     /* PowerON緊急停止 */
#define VIS_BASICSTATE_PARKING_HIGHVOL                      ((U1)0x04U)     /* 駐車中高圧起動 */
#define VIS_BASICSTATE_PARKING_HIGHVOLHEATCOND              ((U1)0x05U)     /* 駐車中高圧温調起動 */
#define VIS_BASICSTATE_CHECKING                             ((U1)0x10U)     /* 判定中 */
#define VIS_SPECIALSTATE_NOTSET                             ((U1)0x00U)     /* 設定なし */
#define VIS_SPECIALSTATE_PRE_DELIVERY                       ((U1)0x01U)     /* 輸送中一部OFF */
#define VIS_SPECIALSTATE_OTA                                ((U1)0x02U)     /* OTA */
#define VIS_SPECIALSTATE_WIRED_REPRO                        ((U1)0x03U)     /* 有線リプロ */
#define VIS_SPECIALSTATE_EMERGENCY_STOP                     ((U1)0x04U)     /* 縮退走行 */
#define VIS_SPECIALSTATE_POWEROFF_ALL                       ((U1)0x05U)     /* 電源ALL OFF */
#define VIS_SPECIALSTATE_SERVICE_LLC                        ((U1)0x06U)     /* WP注排水 */

#define VIS_NORMAL_USERDRIVEN                               ((U1)0x00U)     /* 電源異常初期値：異常なし(手動運転中) */

#define VIS_SOCRST_NORESPONSE                               ((U1)0x00U)     /* SoCリセット起動要因：未受信 */
#define VIS_SOCRST_NORMAL                                   ((U1)0x01U)     /* SoCリセット起動要因：通常起動 */
#define VIS_SOCRST_ABNORMAL                                 ((U1)0x02U)     /* SoCリセット起動要因：強制リセット起動 */
#define VIS_SOCRST_FAIL                                     ((U1)0xFFU)     /* SoCリセット起動要因：異常値 */

#define VIS_VIN_MAX_NM                                      ((U1)17U)       /* VIN情報要素数 */
#define VIS_VIN_INIT_VAL                                    ((U1)0x3FU)     /* VIN初期値 */
#define VIS_NORESPONSE                                      ((U1)0x00U)     /* CAN受信状態：未受信 */
#define VIS_COMMUNICATION_ERROR                             ((U1)0x01U)     /* CAN受信状態：途絶 */
#define VIS_UNDEFINED_VALUE                                 ((U1)0x02U)     /* CAN受信状態：未定義値 */
#define VIS_COMMUNICATION_OK                                ((U1)0x03U)     /* CAN受信状態：正常受信 */
#define VIS_INTERNAL_ERROR                                  ((U1)0xFFU)     /* 内部エラー */

/* -------------------------------------------------------------------------- */
/* UTC時刻 */
typedef struct {
    U1          u1_year;        /* 年 */
    U1          u1_month;       /* 月 */
    U1          u1_day;         /* 日 */
    U1          u1_hour;        /* 時 */
    U1          u1_minute;      /* 分 */
    U1          u1_second;      /* 秒 */
} ST_VIS_UTC;

/* -------------------------------------------------------------------------- */
void vd_g_VISInit(void);
void vd_g_VISMidCycle(void);
/* -------------------------------------------------------------------------- */
U1 u1_g_VISPwrGetBasicState (U1 * const u1_a_BASICSTATE);
U1 u1_g_VISPwrGetSpecialState (U1 * const u1_a_SPECIALSTATE);
U1 u1_g_VISPwrGetEthChPwr (void);
U1 u1_g_VISPwrGetApofrq (void);
void vd_g_VISPwrSocRstNotify (U1 const u1_a_SOCRST_TYPE);
/* -------------------------------------------------------------------------- */
#endif/*VIS_H*/
