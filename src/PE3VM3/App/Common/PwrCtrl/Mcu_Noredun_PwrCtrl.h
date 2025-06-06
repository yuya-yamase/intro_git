/* Mcu_NoRedun_PwrCtrl                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO TECHNO CORPORATION                                       */
/****************************************************************************/

/****************************************************************************/
/* Object Name | Mcu_NoRedun_PwrCtrl/HEADER                                 */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/
#ifndef MCU_NOREDUN_PWRCTRL_H
#define MCU_NOREDUN_PWRCTRL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "Mcu_PwrCtrl_Port.h"

/*--------------------------------------------------------------------------*/
/*  Literal Definitions                                                     */
/*--------------------------------------------------------------------------*/

/* 非冗長電源ON/OFF ウェイトタイム設定 */
/* 待ち時間はMINを設定 "-"であれば中間値(TYP)を指定 */
#define     MCU_WAIT_BETWEEN_TIME           (10U    / MCU_SYS_TASK_TIME )

#define     MCU_WAIT_MBPWR_TIME             (0U                         )
#define     MCU_WAIT_GVIF_TX_MBWK_TIME      (5U     / MCU_SYS_TASK_TIME )
#define     MCU_WAIT_GVIF_TX_MBWK_OFF_TIME  (0U)
#define     MCU_WAIT_MBPWR_OFF_TIME         (5U  / MCU_SYS_TASK_TIME )

#define     MCU_WAIT_DISP_TIME              (0U                         )
#define     MCU_WAIT_GVIF_TX_DSPWK_TIME     (5U     / MCU_SYS_TASK_TIME )
#define     MCU_WAIT_GVIF_TX_DSPWK_OFF_TIME (0U                         )
#define     MCU_WAIT_DISP_OFF_TIME          (5U  / MCU_SYS_TASK_TIME )

#define     MCU_WAIT_HUB_PWRON_TIME         (0U                         )
#define     MCU_WAIT_HUB_WAKE_TIME          (15U    / MCU_SYS_TASK_TIME )
#define     MCU_WAIT_HUB_WAKE_OFF_TIME      (0U                         )
#define     MCU_WAIT_HUB_PWROFF_TIME        (5U / MCU_SYS_TASK_TIME )

/* 待機時間測定完了判定 */
#define     MCU_NOREDUN_WAIT_TIME_FIN       (0xFFFFU)

/* 起動終了シーケンスの実行状態管理 */
#define     MCU_NOREDUN_STEP1               (1U)
#define     MCU_NOREDUN_STEP2               (2U)
#define     MCU_NOREDUN_STEP3               (3U)
#define     MCU_NOREDUN_STEP4               (4U)
#define     MCU_NOREDUN_STEP_OK             (5U)

/* 現在車両電源ステート管理用ステータス */
#define     MCU_NOREDUN_STATE_NUM           (4U)    /* 総数 */
#define     MCU_NOREDUN_STATE_OFF           (0U)    /* OFF */
#define     MCU_NOREDUN_STATE_PARK          (1U)    /* 駐車中起動 */
#define     MCU_NOREDUN_STATE_APPOFF        (2U)    /* 見た目オフ起動 */
#define     MCU_NOREDUN_STATE_APPON         (3U)    /* 見た目オン起動 */

/* 実行中のONシーケンス管理 */
#define     MCU_NOREDUN_ONSEQ_NON           (0U)    /* 実行中のONシーケンスなし */
#define     MCU_NOREDUN_ONSEQ_METBB         (1U)    /* Meter+BB Display ONシーケンス */
#define     MCU_NOREDUN_ONSEQ_CNTDSP        (2U)    /* CenterDisplay Display ONシーケンス */
#define     MCU_NOREDUN_ONSEQ_DSRC          (3U)    /* DSRC(HUB) ONシーケンス */

/* 非冗長電源シーケンスON/OFFトリガ */
#define     MCU_NOREDUN_PWR_NUM             (3U)    /* 総数 */
#define     MCU_NOREDUN_PWR_NON             (0U)    /* 処理なし */
#define     MCU_NOREDUN_PWR_OFF             (1U)    /* OFFシーケンス実施 */
#define     MCU_NOREDUN_PWR_ON              (2U)    /* ONシーケンス実施 */

/* Centralからの非冗長電源ON/OFF要求トリガ */
#define     MCU_NOREDUN_CENTRAL_OFF         (0U)
#define     MCU_NOREDUN_CENTRAL_ON          (1U)

/* デバイスOFF制御実施状況管理マクロ */
#define     PWROFF_USB_BIT                  (0x0001U)
#define     PWROFF_PICTIC_BIT               (0x0002U)
#define     PWROFF_GVIFRX_BIT               (0x0004U)
#define     PWROFF_GVIFTX_BIT               (0x0008U)
#define     PWROFF_MIC_BIT                  (0x0010U)
#define     PWROFF_ANT_BIT                  (0x0020U)
#define     PWROFF_SOUNDMUTE_BIT            (0x0040U)
#define     PWROFF_MOST_BIT                 (0x0080U)
#define     PWROFF_POWERIC_BIT              (0x0100U)
#define     PWROFF_XMTUNER_BIT              (0x0200U)
#define     PWROFF_GNSS_BIT                 (0x0400U)
#define     PWROFF_CONP_BIT                 (0x07FFU)

/*--------------------------------------------------------------------------*/
/*  Function Prototypes                                                     */
/*--------------------------------------------------------------------------*/
void    Mcu_NoRedun_PwrCtrl_Init( void );
void    Mcu_NoRedun_PwrCtrl_MainFunction( void );

void    Mcu_Noredun_PwrOn_Start( void );              /* 非冗長電源ON要求 */
void    Mcu_Noredun_PwrOff_Start( void );             /* 非冗長電源OFF要求 */
uint8   Mcu_Noredun_PwrOn_GetSts( void );             /* 非冗長電源ONシーケンス状態問い合わせ */
uint8   Mcu_Noredun_PwrOff_GetSts( void );            /* 非冗長電源OFFシーケンス状態問い合わせ */

/*--------------------------------------------------------------------------*/
/*  Constant Externs                                                        */
/*--------------------------------------------------------------------------*/
/* SYS系デバイス終了状態 */
extern  uint16  Mcu_Dev_Pwroff_Sts;
extern  uint8   Mcu_Pwr_Sts;

#endif /* MCU_NOREDUN_PWRCTRL_H */
/**** End of File ***********************************************************/
