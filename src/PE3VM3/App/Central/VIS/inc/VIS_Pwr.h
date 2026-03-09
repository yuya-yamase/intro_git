/************************************************************************************************/
/* file Name        : VIS_Pwr.h                                                                 */
/* contents         : PWR module header                                                         */
/* maker            : NCOS                                                                      */
/* change history   :                                                                           */
/* ---------------------------------------------------------------------------------------------*/
/* ver   | Comments                                                                             */
/* ---------------------------------------------------------------------------------------------*/
/* v1.00 | New created                                                                          */
/************************************************************************************************/

#ifndef VIS_PWR_H
#define VIS_PWR_H
/* -------------------------------------------------------------------------- */
#include "VIS.h"
/* -------------------------------------------------------------------------- */
#define VIS_PWR_BAT_FAIL                        ((U1)0x00U)    /* +B電圧 Fail値      */
#define VIS_PWR_ADCNVCHK_OK                     ((U1)0x01U)    /* ADテーブル変換成功 */
#define VIS_PWR_ADCNVCHK_NOTOK                  ((U1)0x00U)    /* ADテーブル変換失敗 */
#define VIS_PWR_BMONI_POLLINGTIME               ((U1)100U)     /* ポーリング周期[100ms] */
#define VIS_PWR_TASK_CYCLE                      ((U1)5U)       /* タスク周期[5ms] */
#define VIS_PWR_BMONI_POLLINGCNT                (VIS_PWR_BMONI_POLLINGTIME / VIS_PWR_TASK_CYCLE)  /* ポーリングカウンタ[20 = 100 / 5ms] */
#define VIS_PWR_BMONI_POLLINGINIT               ((U1)0U)       /* ポーリングタイマ初期値 */

/* 車両電源ステート */
#define VIS_PWR_STATE_RX_MIN_POS                ((U1)0U)       /* CAN受信：BDC1S81メッセージ受信バッファ最小(先頭)位置 */
#define VIS_PWR_STATE_RX_NBYTE                  ((U1)32U)      /* CAN受信：BDC1S81バイト数 */
#define VIS_PWR_STATE_RX_BASICSTATE             ((U1)3U)       /* 車両電源ステート(基本ステート)格納領域 */
#define VIS_PWR_STATE_RX_SPECIALSTATE           ((U1)4U)       /* 車両電源ステート(特殊ステート)格納領域 */
#define VIS_PWR_STATE_RX_TRANSFLG               ((U1)5U)       /* 車両電源ステート(特殊ステート遷移中フラグ)格納領域 */
#define VIS_PWR_STATE_RX_APQFRQ                 ((U1)8U)       /* 車両電源ステート(見た目OFF制御要求)格納領域 */
#define VIS_PWR_RCV_CHECKING                    ((U1)0x01U)    /* 車両電源ステート値：状態未定 */
#define VIS_PWR_RCV_PARKING                     ((U1)0x02U)    /* 車両電源ステート値：駐車中 */
#define VIS_PWR_RCV_RIDING                      ((U1)0x66U)    /* 車両電源ステート値：乗車中 */
#define VIS_PWR_RCV_POWERON_NORMAL              ((U1)0x7EU)    /* 車両電源ステート値：PowerON通常 */
#define VIS_PWR_RCV_POWERON_EMERGENCY           ((U1)0x76U)    /* 車両電源ステート値：PowerON緊急停止 */
#define VIS_PWR_RCV_PARKING_HIGHVOL             ((U1)0x22U)    /* 車両電源ステート値：駐車中高圧起動 */
#define VIS_PWR_RCV_PARKING_HIGHVOLHEATCOND     ((U1)0x62U)    /* 車両電源ステート値：駐車中高圧・温調起動 */
#define VIS_PWR_RCV_UNDEFINED_VALUE             ((U1)0xFFU)    /* 車両電源ステート値：未定義値 */
#define VIS_PWR_INIT                            ((U1)0x00U)    /* データ初期値 */
#define VIS_PWR_RCVCHK_VAL                      ((U1)0x01U)    /* CAN受信値確認(最大値確認用) */
#define VIS_PWR_SPECIALSTATE_INIT               ((U1)0xFFU)    /* 車両電源ステート(特殊ステート)初期値 */
#define VIS_PWR_BITSHIFT_1                      ((U1)1U)       /* 1BIT SHIFT */
#define VIS_PWR_BITSHIFT_2                      ((U1)2U)       /* 2BIT SHIFT */
#define VIS_PWR_BITSHIFT_3                      ((U1)3U)       /* 3BIT SHIFT */
#define VIS_PWR_BITSHIFT_4                      ((U1)4U)       /* 4BIT SHIFT */
#define VIS_PWR_BITSHIFT_5                      ((U1)5U)       /* 5BIT SHIFT */
#define VIS_PWR_BITSHIFT_6                      ((U1)6U)       /* 6BIT SHIFT */
#define VIS_PWR_JUDGE_PASSIVEON_TM              ((U2)600U)     /* 3s = 3000msec = 600 * 5ms */
#define VIS_PWR_JUDGE_CH_POWEROFF_TM            ((U2)6000U)    /* 30s = 30000msec = 6000 * 5ms */
#define VIS_PWR_TIMEOUTINIT                     ((U2)0U)       /* 判定回数初期値 */

#define VIS_PWR_TRANSREQ_DATA_RECEIVEVAL        ((U1)0U)       /* チップ間通信：受信値格納領域 */
#define VIS_PWR_TRANSREQ_DATA_RETURNVAL         ((U1)1U)       /* チップ間通信：受信状態格納領域 */
#define VIS_PWR_TRANSREQ_DATA_LENGTH_1          ((U2)1U)       /* チップ間通信：データ長(1byte) */
#define VIS_PWR_TRANSREQ_DATA_LENGTH_2          ((U2)2U)       /* チップ間通信：データ長(2byte) */
#define VIS_PWR_TRANSREQ_LENGTH_INIT            ((U2)0x0000U)  /* チップ間通信：データ長初期化用 */
#define VIS_PWR_TRANSREQ_RCVCNT_INIT            (0x00000000U)  /* チップ間通信：受信カウンタ初期化用 */
#define VIS_PWR_COM_IPDUST_OK                   ((U1)0U)       /* CANメッセージ受信状態：正常受信 */

/* -------------------------------------------------------------------------- */
void vd_g_VISPwrInit(void);
void vd_g_VISPwrCyc(void);
/* -------------------------------------------------------------------------- */

#endif/*VIS_PWR_H*/
