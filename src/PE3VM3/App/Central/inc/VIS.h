/* -------------------------------------------------------------------------- */
/* file name    :    VIS.h                                                    */
/* -------------------------------------------------------------------------- */
#ifndef VIS_H
#define VIS_H
/* -------------------------------------------------------------------------- */
#include "Std_Types.h"
#include "aip_common.h"
#include "VIS_Stub.h"
/* -------------------------------------------------------------------------- */
/* 定期送信初期値（MCU⇒SAIL） */
#define VIS_UTC_INIT                                        (U1)(0xFFU)     /* UTC時刻情報 */
#define VIS_ODO_INIT                                        (U1)(0x00U)     /* オドメータ情報 */
#define VIS_TRIP_INIT                                       (U1)(0xFFU)     /* Tripカウンタ情報 */
#define VIS_SPD_INIT                                        (U1)(0xFFU)     /* 車速情報 */
#define VIS_RDYSTS_INIT                                     (U1)(0x00U)     /* 電動システム起動状態 */
#define VIS_BAT_INIT                                        (U1)(0x00U)     /* ECU電源電圧 */

#define VIS_BASICSTATE_PARKING                              (U1)(0x00U)     /* 駐車中 */
#define VIS_BASICSTATE_RIDING                               (U1)(0x01U)     /* 乗車中 */
#define VIS_BASICSTATE_POWERON_NORMAL                       (U1)(0x02U)     /* PowerON通常 */
#define VIS_BASICSTATE_POWERON_EMERGENCY                    (U1)(0x03U)     /* PowerON緊急停止 */
#define VIS_BASICSTATE_PARKING_HIGHVOL                      (U1)(0x04U)     /* 駐車中高圧起動 */
#define VIS_BASICSTATE_PARKING_HIGHVOLHEATCOND              (U1)(0x05U)     /* 駐車中高圧温調起動 */
#define VIS_BASICSTATE_CHECKING                             (U1)(0x10U)     /* 判定中 */
#define VIS_SPECIALSTATE_NOTSET                             (U1)(0x00U)     /* 設定なし */
#define VIS_SPECIALSTATE_PRE_DELIVERY                       (U1)(0x01U)     /* 輸送中一部OFF */
#define VIS_SPECIALSTATE_OTA                                (U1)(0x02U)     /* OTA */
#define VIS_SPECIALSTATE_WIRED_REPRO                        (U1)(0x03U)     /* 有線リプロ */
#define VIS_SPECIALSTATE_EMERGENCY_STOP                     (U1)(0x04U)     /* 縮退走行 */
#define VIS_SPECIALSTATE_POWEROFF_ALL                       (U1)(0x05U)     /* 電源ALL OFF */

#define VIS_NORMAL_USERDRIVEN                               (U1)(0x00U)     /* 異常なし(手動運転中) */
#define VIS_NORMAL_ADSUPPORT_NOTPOSSIBLE                    (U1)(0x01U)     /* 異常なし(高度運転支援実施不可) */
#define VIS_NORMAL_ADSUPPORT_INPROGRESS                     (U1)(0x02U)     /* 異常なし(高度運転支援実施中) */
#define VIS_EDS_DCDCFAILED_SYSTEMDRIVE                      (U1)(0x0AU)     /* 縮退走行中(DCDC側異常_システム駆動) */
#define VIS_EDS_DCDCFAILED_USERDRIVE                        (U1)(0x0BU)     /* 縮退走行中(DCDC側異常_ユーザー駆動) */
#define VIS_EDS_DCDCFAILED_STOP                             (U1)(0x0CU)     /* 縮退走行中(DCDC側異常_駆動力停止) */
#define VIS_EDS_LIBFAILED_SYSTEMDRIVE                       (U1)(0x14U)     /* 縮退走行中(補機LiB側異常_システム駆動) */
#define VIS_EDS_LIBFAILED_USERDRIVE                         (U1)(0x15U)     /* 縮退走行中(補機LiB側異常_ユーザー駆動) */
#define VIS_EDS_LIBFAILED_STOP                              (U1)(0x16U)     /* 縮退走行中(補機LiB側異常_駆動力停止) */

#define VIS_VIN_MAX_NM                                      (U1)(17U)       /* VIN情報要素数 */
#define VIS_VIN_INIT_VAL                                    (U1)(0x3FU)     /* VIN初期値 */
#define VIS_NORESPONSE                                      (U1)(0x00U)     /* CAN受信状態：未受信 */
#define VIS_COMMUNICATION_ERROR                             (U1)(0x01U)     /* CAN受信状態：途絶 */
#define VIS_UNDEFINED_VALUE                                 (U1)(0x02U)     /* CAN受信状態：未定義値 */
#define VIS_COMMUNICATION_OK                                (U1)(0x03U)     /* CAN受信状態：正常受信 */
#define VIS_INTERNAL_ERROR                                  (U1)(0xFFU)     /* 内部エラー */

/* ★VISデバッグ用フラグ */
#define VIS_DEBUG_FLG   (TRUE)
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
U1 u1_g_VISPwrGetTransFlg (U1 * const u1_a_TRANSFLG);
U1 u1_g_VISPwrGetEthChPwr (void);

#if (VIS_DEBUG_FLG == TRUE)
/* ★SAILに実装 */
U1 u1_g_VISCanUTCGetData(ST_VIS_UTC * const st_ap_utc);
U1 u1_g_VISCanOdoGetData(U4 * const u4_a_ODO);
U1 u1_g_VISCanSpdGetData(U1 * const u1_a_SPD);
U1 u1_g_VISCanEPwrCtrlSysRdystsGetData(U1 * const u1_a_EPWRCTRLSYSRDYSTS);
U1 u1_g_VISPwrBatVoltGet(void);
#endif
/* -------------------------------------------------------------------------- */
#endif/*VIS_H*/
