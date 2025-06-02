/* PwrCtrl_NoRedun                                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO TECHNO CORPORATION                                       */
/****************************************************************************/

/****************************************************************************/
/* Object Name | PwrCtrl_NoRedun/HEADER                                     */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/
#ifndef PWRCTRL_NOREDUN_H
#define PWRCTRL_NOREDUN_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/*  Literal Definitions                                                     */
/*--------------------------------------------------------------------------*/

/* 非冗長電源状態 */
#define PWRCTRL_NOREDUN_STS_NON         (0U)    /* 制御要求なし */
#define PWRCTRL_NOREDUN_STS_OFF         (1U)    /* OFF制御要求 */
#define PWRCTRL_NOREDUN_STS_ON          (2U)    /* ON制御要求 */

/* 非冗長電源ON/OFF ウェイトタイム設定 */
/* 待ち時間はMINを設定 "-"であれば中間値(TYP)を指定 */
#define PWRCTRL_NOREDUN_WAIT_TIME_INIT              (0U)

#define PWRCTRL_NOREDUN_WAIT_BETWEEN_TIME           (10U    / PWRCTRL_CFG_TASK_TIME )

#define PWRCTRL_NOREDUN_WAIT_MBPWR_TIME             (0U)
#define PWRCTRL_NOREDUN_WAIT_GVIF_TX_MBWK_TIME      (5U     / PWRCTRL_CFG_TASK_TIME )
#define PWRCTRL_NOREDUN_WAIT_GVIF_TX_MBWK_OFF_TIME  (0U)
#define PWRCTRL_NOREDUN_WAIT_MBPWR_OFF_TIME         (5U  / PWRCTRL_CFG_TASK_TIME )
               
#define PWRCTRL_NOREDUN_WAIT_DISP_TIME              (0U)
#define PWRCTRL_NOREDUN_WAIT_GVIF_TX_DSPWK_TIME     (5U     / PWRCTRL_CFG_TASK_TIME )
#define PWRCTRL_NOREDUN_WAIT_GVIF_TX_DSPWK_OFF_TIME (0U                         )
#define PWRCTRL_NOREDUN_WAIT_DISP_OFF_TIME          (5U  / PWRCTRL_CFG_TASK_TIME )
               
#define PWRCTRL_NOREDUN_WAIT_HUB_PWRON_TIME         (0U)
#define PWRCTRL_NOREDUN_WAIT_HUB_WAKE_TIME          (15U    / PWRCTRL_CFG_TASK_TIME )
#define PWRCTRL_NOREDUN_WAIT_HUB_WAKE_OFF_TIME      (0U)
#define PWRCTRL_NOREDUN_WAIT_HUB_PWROFF_TIME        (5U / PWRCTRL_CFG_TASK_TIME )

/* 待機時間測定完了判定 */
#define PWRCTRL_NOREDUN_WAIT_TIME_FIN   (0xFFFFU)

/* 現在車両電源ステート判定用ビットシフト */
#define PWRCTRL_NOREDUN_BITSFT1         (1U)
#define PWRCTRL_NOREDUN_BITSFT2         (2U)
#define PWRCTRL_NOREDUN_BITSFT3         (3U)
#define PWRCTRL_NOREDUN_BITSFT4         (4U)
#define PWRCTRL_NOREDUN_BITSFT5         (5U)
#define PWRCTRL_NOREDUN_BITSFT6         (6U)
#define PWRCTRL_NOREDUN_BITSFT7         (7U)

/* 車両電源ステート次回状態判定 */
#define PWRCTRL_NOREDUN_CHKSTS_APPON_UNCON      (0x40U) /* 見た目：オン ステート：状態未定 */
#define PWRCTRL_NOREDUN_CHKSTS_APPON_PARK       (0x20U) /* 見た目：オン ステート：駐車中 */
#define PWRCTRL_NOREDUN_CHKSTS_APPON_RIDE       (0x33U) /* 見た目：オン ステート：乗車中 */
#define PWRCTRL_NOREDUN_CHKSTS_APPON_PONEMG     (0x37U) /* 見た目：オン ステート：PowerON緊急停止 */
#define PWRCTRL_NOREDUN_CHKSTS_APPON_PON        (0x3FU) /* 見た目：オン ステート：PowerON通常 */
#define PWRCTRL_NOREDUN_CHKSTS_APPON_HVOL       (0x22U) /* 見た目：オン ステート：駐車中 高圧起動 */
#define PWRCTRL_NOREDUN_CHKSTS_APPON_HVOLHCOND  (0x23U) /* 見た目：オン ステート：駐車中 高圧・温調起動 */
#define PWRCTRL_NOREDUN_CHKSTS_APPOFF_UNCON     (0xC0U) /* 見た目：オフ ステート：状態未定 */
#define PWRCTRL_NOREDUN_CHKSTS_APPOFF_PARK      (0xA0U) /* 見た目：オフ ステート：駐車中 */
#define PWRCTRL_NOREDUN_CHKSTS_APPOFF_RIDE      (0xB3U) /* 見た目：オフ ステート：乗車中 */
#define PWRCTRL_NOREDUN_CHKSTS_APPOFF_PONEMG    (0xB7U) /* 見た目：オフ ステート：PowerON緊急停止 */
#define PWRCTRL_NOREDUN_CHKSTS_APPOFF_PON       (0xBFU) /* 見た目：オフ ステート：PowerON通常 */
#define PWRCTRL_NOREDUN_CHKSTS_APPOFF_HVOL      (0xA2U) /* 見た目：オフ ステート：駐車中 高圧起動 */
#define PWRCTRL_NOREDUN_CHKSTS_APPOFF_HVOLHCOND (0xA3U) /* 見た目：オフ ステート：駐車中 高圧・温調起動 */

/* 現在車両電源ステート管理用ステータス */
#define PWRCTRL_NOREDUN_STATE_NUM       (4U)    /* 総数 */
#define PWRCTRL_NOREDUN_STATE_OFF       (0U)    /* OFF */
#define PWRCTRL_NOREDUN_STATE_PARK      (1U)    /* 駐車中起動 */
#define PWRCTRL_NOREDUN_STATE_APPOFF    (2U)    /* 見た目オフ起動 */
#define PWRCTRL_NOREDUN_STATE_APPON     (3U)    /* 見た目オン起動 */

/* 実行中のONシーケンス管理 */
#define PWRCTRL_NOREDUN_ONSEQ_NON       (0U)    /* 実行中のONシーケンスなし */
#define PWRCTRL_NOREDUN_ONSEQ_METBB     (1U)    /* Meter+BB Display ONシーケンス */
#define PWRCTRL_NOREDUN_ONSEQ_CNTDSP    (2U)    /* CenterDisplay Display ONシーケンス */
#define PWRCTRL_NOREDUN_ONSEQ_DSRC      (3U)    /* DSRC(HUB) ONシーケンス */

/* 非冗長電源ON/OFF制御トリガ */
#define PWRCTRL_NOREDUN_PWR_NON         (0U)    /* 制御なし */
#define PWRCTRL_NOREDUN_PWR_OFF         (1U)    /* OFF制御実施 */
#define PWRCTRL_NOREDUN_PWR_ON          (2U)    /* ON制御実施 */

/* デバイスOFF制御実施状況管理マクロ */
#define PWROFF_USB_BIT                  (0x0001U)
#define PWROFF_PICTIC_BIT               (0x0002U)
#define PWROFF_GVIFRX_BIT               (0x0004U)
#define PWROFF_GVIFTX_BIT               (0x0008U)
#define PWROFF_MIC_BIT                  (0x0010U)
#define PWROFF_ANT_BIT                  (0x0020U)
#define PWROFF_SOUNDMUTE_BIT            (0x0040U)
#define PWROFF_MOST_BIT                 (0x0080U)
#define PWROFF_POWERIC_BIT              (0x0100U)
#define PWROFF_XMTUNER_BIT              (0x0200U)
#define PWROFF_GNSS_BIT                 (0x0400U)
#define PWROFF_CONP_BIT                 (0x07FFU)

/*--------------------------------------------------------------------------*/
/*  Function Prototypes                                                     */
/*--------------------------------------------------------------------------*/
void vd_g_PwrCtrlNoRedunInit( void );
void vd_g_PwrCtrlNoRedunMainFunction( void );

void vd_g_PwrCtrlNoRedunPwrOnStart( void );       /* 非冗長電源ON要求 */
void vd_g_PwrCtrlNoRedunPwrOffStart( void );      /* 非冗長電源OFF要求 */
U1 u1_g_PwrCtrlNoRedunGetSts( void );             /* 非冗長電源ONシーケンス状態問い合わせ */

/*--------------------------------------------------------------------------*/
/*  Constant Externs                                                        */
/*--------------------------------------------------------------------------*/
/* SYS系デバイス終了状態 */
extern  U2 Mcu_Dev_Pwroff_Sts;
extern  U1 u1_g_PwrCtrl_NoRedun_Pwr_Sts;

#endif /* PWRCTRL_NOREDUN_H */
/**** End of File ***********************************************************/
