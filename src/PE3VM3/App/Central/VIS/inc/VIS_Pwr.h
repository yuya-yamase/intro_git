/* -------------------------------------------------------------------------- */
/* file name    :   VIS_Pwr.h                                                 */
/* -------------------------------------------------------------------------- */
#ifndef VIS_PWR_H
#define VIS_PWR_H
/* -------------------------------------------------------------------------- */
#include "VIS.h"
/* -------------------------------------------------------------------------- */
#define VIS_PWR_BAT_FAIL                        ((U1)0x00U)    /* +B電圧 Fail値      */
#define VIS_PWR_ADCNVCHK_OK                     ((U1)0x01U)    /* ADテーブル変換成功 */
#define VIS_PWR_ADCNVCHK_NOTOK                  ((U1)0x00U)    /* ADテーブル変換失敗 */
#define VIS_PWR_BMONITOR_WAITTIME               ((U1)20U)      /* ポーリング周期[100ms = 20 * 5ms] */

#define VIS_PWR_RCV_CHECKING                    ((U1)0x01U)
#define VIS_PWR_RCV_PARKING                     ((U1)0x02U)
#define VIS_PWR_RCV_RIDING                      ((U1)0x66U)
#define VIS_PWR_RCV_POWERON_NORMAL              ((U1)0x7EU)
#define VIS_PWR_RCV_POWERON_EMERGENCY           ((U1)0x76U)
#define VIS_PWR_RCV_PARKING_HIGHVOL             ((U1)0x22U)
#define VIS_PWR_RCV_PARKING_HIGHVOLHEATCOND     ((U1)0x62U)
#define VIS_PWR_RCV_UNDEFINED_VALUE             ((U1)0xFFU)
#define VIS_PWR_INIT                            ((U1)0x00U)
#define VIS_PWR_RCVCHK_VAL                      ((U1)0x01U)
#define VIS_PWR_SPECIALSTATE_INIT               ((U1)0xFFU)
#define VIS_PWR_BITSHIFT_1                      ((U1)1U)
#define VIS_PWR_BITSHIFT_2                      ((U1)2U)
#define VIS_PWR_BITSHIFT_3                      ((U1)3U)
#define VIS_PWR_BITSHIFT_4                      ((U1)4U)
#define VIS_PWR_BITSHIFT_5                      ((U1)5U)
#define VIS_PWR_BITSHIFT_6                      ((U1)6U)
#define VIS_PWR_JUDGE_PASSIVEON_TM              ((U2)600U)      /* 3s = 3000msec = 600 * 5ms */
#define VIS_PWR_JUDGE_CH_POWEROFF_TM            ((U2)6000U)     /* 30s = 30000msec = 6000 * 5ms */
#define VIS_PWR_TIMEOUTINIT                     ((U2)0U)
#define VIS_PWR_TRANSREQ_DATA_RECEIVEVAL        ((U1)0U)        /* チップ間通信：受信値格納領域 */
#define VIS_PWR_TRANSREQ_DATA_RETURNVAL         ((U1)1U)        /* チップ間通信：受信状態格納領域 */
#define VIS_PWR_TRANSREQ_DATA_LENGTH_1          ((U2)1U)        /* チップ間通信：データ長(1byte) */
#define VIS_PWR_TRANSREQ_DATA_LENGTH_2          ((U2)2U)        /* チップ間通信：データ長(2byte) */
#define VIS_PWR_TRANSREQ_DATA_LENGTH_18         ((U2)18U)       /* チップ間通信：データ長(18byte) */
#define VIS_PWR_COM_IPDUST_OK                   ((U1)0U)        /* CANメッセージ受信状態：正常受信 */
/* -------------------------------------------------------------------------- */
void vd_g_VISPwrInit(void);
void vd_g_VISPwrCyc(void);
/* -------------------------------------------------------------------------- */

#endif/*VIS_PWR_H*/
