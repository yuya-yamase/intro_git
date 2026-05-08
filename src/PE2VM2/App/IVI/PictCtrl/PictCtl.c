/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Gvif3Ex                                                                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "PictCtl.h"

#include "Dio.h"
#include "oxcan.h"
#include "CXD4984ERCtl.h"
#include "x_spi_ivi_sub1_camera.h"
#include "x_spi_ivi_sub1_power.h"
#include "ML86294Ctl.h"
#include "PictMuteCtl.h"
#include "SysEcDrc.h"
#include "PictLogCtl.h"
#include "PwrCtl.h"
#include "veh_opemd.h"
#include "ivdsh.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* シーケンス要求状態定義 */
#define PICT_SEQREQ_IDL                                 (0U)        /* シーケンス要求無し           */
#define PICT_SEQREQ_WAI                                 (1U)        /* シーケンス要求有り(実行待ち) */


#define PICT_SEQ_ML_CAMONCHG                            (0U)        /* カメラへ切替                 */
#define PICT_SEQ_ML_CAMOFFCHG                           (1U)        /* カメラ以外へ切替             */
#define PICT_SEQ_ML_CAMSYNCNG                           (2U)        /* カメラカメラ同期正常->異常   */
#define PICT_SEQ_ML_CAMSYNCOK                           (3U)        /* カメラカメラ同期異常->正常   */
#define PICT_SEQ_ML_IDLE                                (4U)        /* アイドル                     */
#define PICT_SEQ_ML_NUM                                 (5U)

#define PICT_SEQ_INI                                    (0U)

/* カメラへ切替シーケンスStep定義 */
#define PICT_SEQ_ML_CAMON_STEP0                         (0U)
#define PICT_SEQ_ML_CAMON_STEP1                         (1U)
#define PICT_SEQ_ML_CAMON_STEP2                         (2U)
#define PICT_SEQ_ML_CAMON_STEP3                         (3U)
#define PICT_SEQ_ML_CAMON_STEP4                         (4U)
#define PICT_SEQ_ML_CAMON_STEP5                         (5U)
#define PICT_SEQ_ML_CAMON_STEP6                         (6U)
#define PICT_SEQ_ML_CAMON_STEP7                         (7U)
#define PICT_SEQ_ML_CAMON_STEP8                         (8U)
#define PICT_SEQ_ML_CAMON_STEP9                         (9U)

/* カメラ以外へ切替シーケンスStep定義 */
#define PICT_SEQ_ML_CAMOFF_STEP0                        (0U)
#define PICT_SEQ_ML_CAMOFF_STEP1                        (1U)
#define PICT_SEQ_ML_CAMOFF_STEP2                        (2U)
#define PICT_SEQ_ML_CAMOFF_STEP3                        (3U)
#define PICT_SEQ_ML_CAMOFF_STEP4                        (4U)
#define PICT_SEQ_ML_CAMOFF_STEP5                        (5U)
#define PICT_SEQ_ML_CAMOFF_STEP6                        (6U)
#define PICT_SEQ_ML_CAMOFF_STEP7                        (7U)
#define PICT_SEQ_ML_CAMOFF_STEP8                        (8U)
#define PICT_SEQ_ML_CAMOFF_STEP9                        (9U)

/* カメラ同期正常→異常シーケンスStep定義 */
#define PICT_SEQ_ML_CAMSYNCNG_STEP0                     (0U)

/* カメラ同期異常時シーケンスStep定義 */
#define PICT_SEQ_CAMONSYNCNG_STEP0                      (0U)
#define PICT_SEQ_CAMONSYNCNG_STEP1                      (1U)
#define PICT_SEQ_CAMONSYNCNG_STEP2                      (2U)

/* カメラ同期異常→正常シーケンスStep定義 */
#define PICT_SEQ_ML_CAMSYNCOK_STEP0                     (0U)
#define PICT_SEQ_ML_CAMSYNCOK_STEP1                     (1U)
#define PICT_SEQ_ML_CAMSYNCOK_STEP2                     (2U)
#define PICT_SEQ_ML_CAMSYNCOK_STEP3                     (3U)
#define PICT_SEQ_ML_CAMSYNCOK_STEP4                     (4U)
#define PICT_SEQ_ML_CAMSYNCOK_STEP5                     (5U)

/* カメラ同期判定シーケンスStep定義 */
#define PICT_SEQ_CAMSYNCCHK_STEP0                        (0U)
#define PICT_SEQ_CAMSYNCCHK_STEP1                        (1U)

/* Sip異常時シーケンスStep定義 */
#define PICT_SEQ_SIPERRCHK_STEP0                        (0U)
#define PICT_SEQ_SIPERRCHK_STEP1                        (1U)
#define PICT_SEQ_SIPERRCHK_STEP_FIN                     (2U)
#define PICT_SEQ_SIPERRCHK_STEP_NON                     (3U)

/* VM Reset Step */
#define PICT_SEQ_VMRESETCHK_STEP0                       (0U)
#define PICT_SEQ_VMRESETCHK_STEP1                       (1U)
#define PICT_SEQ_VMRESETCHK_STEP_FIN                    (2U)

/*--- ポーリング管理 ---*/
#define PICT_POLLPORT_NONDECI                           (0xFFU)     /* ポーリング未確定 */
#define PICT_POLLPORT_CNTINIT                           (0x00U)     /* カウント初期値 */

/*-- ポーリング動作状態  --*/
#define PICT_POLLSTS_STOP                               (0U)        /* ポーリング停止中     */
#define PICT_POLLSTS_START_WAIT                         (1U)        /* ポーリング開始待ち   */
#define PICT_POLLSTS_CYC                                (2U)        /* ポーリング定期       */

/* 種別 */      
#define PICT_POLLPORT_HIACTIVE                          (1U)        /* 正論理 */
#define PICT_POLLPORT_LOACTIVE                          (2U)        /* 負論理 */

/* トリガータイプ */            
#define PICT_POLLTRG_OFF                                (0x00U)     /* OFF */
#define PICT_POLLTRG_AUDIOON                            (0x01U)     /* BIT0: AUDIO-ON */
#define PICT_POLLTRG_MMSTBY                             (0x02U)     /* BIT1: /MM-STBY */
#define PICT_POLLTRG_LOWPOWERON                         (0x04U)     /* BIT2: LOW-POWER-ON */

#define PICT_POLLFACT_NUM                               (3U)
#define PICT_POLLFACT_AUDIO                             (0U)
#define PICT_POLLFACT_MMSTBY                            (1U)
#define PICT_POLLFACT_LOWPOWERON                        (2U)

/* ポーリング番号 */        
#define PICT_POLLNO_DISPREQGPIO0                        (0U)        /* DISP-REQ-GPIO0 */
#define PICT_POLLNO_CAMCAPSTBY                          (1U)        /* MIPI(BEYE)キャプチャ */
#define PICT_POLLNO_CAMCAPSTBY2                         (2U)        /* MIPI(BEYE)カメラ */
#define PICT_POLLNO_CAMCAPSTBY3                         (3U)        /* MIPI(FEYE)キャプチャ */

/* ポーリング番号最大数 */
#define PICT_POLLNO_MAX                                 (8U)

#define PICT_CNT_INI                                    (0U)
#define PICT_SAME_FIRST                                 (1U)

#define PICT_SAMECNT_INI                                (0U)
#define PICT_SAMECNT_FIRST                              (1U)
    
#define PICT_TIM_TOUT                                   (0x0000U)   /* タイムアウト */
#define PICT_TIM_STOP                                   (0xFFFFU)   /* タイマ停止 */

/* タイマID */
#define PICT_TIMID_ML_PRC_T1                            (0U)    /* MLプロセス間タイマT1                                         */
#define PICT_TIMID_ML_PRC_T2                            (1U)    /* MLプロセス間タイマT2                                         */
#define PICT_TIMID_ML_CAM_MODE1_ERR_CHKCYC              (2U)    /* メインマイコンのCAMERA-MODE1=Hi検知異常検出待ちタイマ        */
#define PICT_TIMID_ML_T_SIP_NOTIF_OUT                   (3U)    /* T_SIP_NOTIF_OUT待ちタイマ                                    */
#define PICT_TIMID_ML_CAMSYNC_CHKSTA                    (4U)    /* カメラ同期検知開始待ちタイマ                                 */
#define PICT_TIMID_ML_CAMSYNC_CHKCYC                    (5U)    /* カメラ同期検知周期タイマ                                     */
#define PICT_TIMID_ML_DIAGSYNC_CHKCYC                   (6U)    /* ダイアグ専用同期検知周期タイマ                               */
#define PICT_TIMID_CAM_KIND_DISC_STA_WAIT               (7U)    /* カメラシステム種別判別開始待ちタイマ起動(1000ms)             */
#define PICT_TIMID_CAMKIND_SENDCYC                      (8U)    /* カメラ種別判別通知定期送信タイマ                             */
#define PICT_TIMID_CAMSYNCPATHINFO_SENDCYC              (9U)    /* 同期検知・経路情報通知?定期送信タイマ                        */
#define PICT_TIMID_MAVTYPE_TIMEOUT                      (10U)   /* MAVTYPE 3Cycle(3000ms) TimeOut                               */
#define PICT_TIMID_BCC1S05_TIMEOUT                      (11U)   /* BCC1S05 TimeOut                                              */
#define PICT_TIMID_CANSIGNAL_GETCYC                     (12U)   /* CAN Signal Get Cycle                                         */
#define PICT_TIMID_MAX                                  (13U)   /* タイマＩＤ ＭＡＸ数                                          */

/* 仕様値のMIN値を使用する場合は、設定値+1msが必要 */
#define PICT_TIMER_CORRECTION_1MS                       (1U)
#define PICT_TIMER_ML_CAM_MODE_H_MAIN_CHKERR_CHKCYC     (40U)
#define PICT_TIMER_ML_T_SIP_NOTIF_OUT                   (1850U + PICT_TIMER_CORRECTION_1MS)
#define PICT_TIMER_ML_CAMCHG_FIX_DET_WAIT               (275U + PICT_TIMER_CORRECTION_1MS)
#define PICT_TIMER_ML_CAMCHG_MUTE_OFF_WAIT              (20U + PICT_TIMER_CORRECTION_1MS)
#define PICT_TIMER_ML_CAMCHG_FIX_DET_WAIT2              (25U + PICT_TIMER_CORRECTION_1MS)
#define PICT_TIMER_ML_CAMCHG_T_CAM_OUT                  (375U + PICT_TIMER_CORRECTION_1MS)
#define PICT_TIMER_ML_CAMCHG_T_CAM_OUT2                 (375U + PICT_TIMER_CORRECTION_1MS)
#define PICT_TIMER_ML_CAMCHG_FIX_DET_END_WAIT           (40U + PICT_TIMER_CORRECTION_1MS)
#define PICT_TIMER_ML_CAMSYNC_CHKSTA_WAIT               (1500U + PICT_TIMER_CORRECTION_1MS)
#define PICT_TIMER_ML_CAMSYNC_CHKCYC                    (20U)
#define PICT_TIMER_ML_T_SYNC_LP_WAIT                    (5U)
#define PICT_TIMER_ML_AISMUTE_OFF_WAIT_T0               (100U)
#define PICT_TIMER_ML_AISMUTE_OFF_WAIT_T1               (50U + PICT_TIMER_CORRECTION_1MS)
#define PICT_TIMER_ML_AISMUTE_OFF_WAIT_T2               (250U)
#define PICT_TIMER_TABCMD_SENDCYC                       (3000U)
#define PICT_TIMER_CAM_KIND_DISC_STA                    (1000U)
#define PICT_TIMER_MAVTYPE_TIMEOUT                      (3000U)
#define PICT_TIMER_BCC1S05_TIMEOUT                      (3000U)
#define PICT_TIMER_CANSIGNAL_GETCYC                     (100U)

#define PICT_CAN_CAM_CNTMAX                             (3U)    /* カメラ種別確定回数 */

/* カメラ種別 */
#define PICT_CAN_CAM_KIND_UNFIX                         (0x00U) /* 未確定 */
#define PICT_CAN_CAM_KIND_PVM                           (0x01U) /* PVM */
#define PICT_CAN_CAM_KIND_MTM                           (0x03U) /* MTM */
#define PICT_CAN_CAM_KIND_SIM                           (0x04U) /* SIM */
#define PICT_CAN_CAM_KIND_BGM                           (0x05U) /* BGM */
#define PICT_CAN_CAM_KIND_SBGM                          (0x06U) /* SBGM */
#define PICT_CAN_CAM_KIND_PVM_METER                     (0x07U) /* PVM(w/METER) */
#define PICT_CAN_CAM_KIND_MTM_METER                     (0x08U) /* MTM(w/METER) */
#define PICT_CAN_CAM_KIND_NONE                          (0x09U) /* 無し */
#define PICT_CAN_CAM_KIND_NORX                          (0xFFU)

/* カメラ切替状態 */
#define PICT_CAMCHG_STS_OFF                             (0U)    /* カメラ以外 */
#define PICT_CAMCHG_STS_OFF_GO                          (1U)    /* カメラ以外切替中 */
#define PICT_CAMCHG_STS_NORMAL_GO                       (2U)    /* カメラ通常経路切替中 */
#define PICT_CAMCHG_STS_NORMAL                          (3U)    /* カメラ通常経路中 */
#define PICT_CAMCHG_STS_BPASS_GO                        (4U)    /* カメラバイパス経路切替中 */
#define PICT_CAMCHG_STS_BPASS                           (5U)    /* カメラバイパス経路中 */

#define PICT_CAMON_TO_NORMAL                            (0U)    /* カメラ通常経路へ */
#define PICT_CAMON_TO_BPASS                             (1U)    /* カメラバイパス経路へ */

#define PICT_CAMOFF_FORM_NORMAL                         (0U)    /* カメラ通常経路から */
#define PICT_CAMOFF_FORM_BPASS                          (1U)    /* カメラバイパス経路から */
#define PICT_CAMOFF_FORM_SYNCNG                         (2U)    /* カメラ同期異常から */

/* 画質モード通知(カメラ以外)受ける状態 */
#define PICT_RCV_NOCAMQUAL_NONE                         (0U)    /* 未確定 */
#define PICT_RCV_NOCAMQUAL_TOUT                         (1U)    /* 受信タイムアウト */
#define PICT_RCV_NOCAMQUAL_STOP                         (2U)    /* 受信停止 */
#define PICT_RCV_NOCAMQUAL_END                          (3U)    /* 受信済 */

/* カメラ切替経路 */
#define PICT_CAM_PATH_NOCHG                             (0x00U) /* 変更経路無し */
#define PICT_CAM_PATH_NORM                              (0x01U) /* カメラ通常経路 */
#define PICT_CAM_PATH_BPASS                             (0x02U) /* カメラバイパス経路 */
#define PICT_CAM_PATH_CAMMODEFAIL                       (0x04U) /* カメラバイパス経路(カメラモード検知異常時) */
#define PICT_CAM_PATH_SIPERR                            (0x08U) /* カメラバイパス経路(SiP異常検知時) */
#define PICT_CAM_PATH_FALSEPOSITIVE                     (0x10U) /* カメラ通常経路(SiP異常エッジ誤検知時) */
#define PICT_CAM_PATH_VMRESET                           (0x20U) /* カメラバイパス経路(VMリセット時) */

/* カメラ同期判定用 */
#define PICT_SYNC_LOOPCNT                               (8U)    /* カメラ同期判定LOOP回数 */
#define PICT_SYNC_CHKCNTL1                              (1U)    /* カメラ同期異常判定L1 */
#define PICT_SYNC_CHKCNTL2                              (8U)    /* カメラ同期異常判定L2 */

/* MIPI 出力設定要求 */
#define PICT_MIPI_OUT_NON                               (0x00U) /* MIPI出力設定要求：無し            */
#define PICT_MIPI_OUT_HS                                (0x01U) /* MIPI出力設定要求：HS              */
#define PICT_MIPI_OUT_LP11                              (0x02U) /* MIPI出力設定要求：LP-11           */
#define PICT_MIPI_OUT_VMRESET                           (0x04U) /* MIPI出力設定要求：LP-11(VM RESET) */

/* メインマイコンのCAMERA-MODE1=Hi 検知異常判定 */
#define PICT_CAM_MODE_H_MAIN_CHKERR_CNT_L1              (12U)   /* メインマイコンのCAMERA-MODE1=Hi 検知異常の判定用カウント数 */

/* ダイアグモード       */
#define PICT_DIAG_MOD_OFF                               (0U)    /* ダイアグモードOFF        */
#define PICT_DIAG_MOD_ON                                (1U)    /* ダイアグモードON         */
#define PICT_DIAG_MOD_CAMON                             (2U)    /* カメラダイアグモードON   */

#define PICT_CAM_SYNC_NG                                (0x00U) /* 同期無し         */
#define PICT_CAM_SYNC_OK                                (0x01U) /* 同期あり         */
#define PICT_CAM_SYNC_UNSET                             (0xFFU) /* 未確定・無効     */

#define PICT_BEYE_MIPI_LP11                             (0U)    /* LP-11 出力           */
#define PICT_BEYE_MIPI_HS                               (1U)    /* HS出力(LP-11 解除)   */

#define PICT_CAM_PATH_FORPASS                           (0U)    /* カメラ強制パス表示中 */
#define PICT_CAM_PATH_LV                                (1U)    /* LV映像出力中 */

#define PICT_CAM_FEYE_MIPI_OFF                          (0U)    /* MIPI出力 OFF         */
#define PICT_CAM_FEYE_MIPI_ON                           (1U)    /* MIPI出力 ON          */

/* メーターカメラサイズ */
#define     PICT_METER_CAM_SIZE_UNFIX                   (0U)    /* 未確定 */
/* 検知状態 */
#define PICT_CAM_DET_UNFIX                              (0x00U) /* 未確定       */
#define PICT_CAM_DET_OFF                                (0x01U) /* OFF          */
#define PICT_CAM_DET_ON                                 (0x02U) /* ON           */

#define PICT_TOUT_MUTEOFF                               (0U)
#define PICT_TOUT_MUTEON                                (1U)
#define PICT_TOUT_MUTEOFF_WAIT                          (2U)

#define PICT_PORT_AUDIO_ON                              (DIO_ID_APORT5_CH0)
#define PICT_PORT_LOW_POWER_ON                          (DIO_ID_PORT10_CH5)
#define PICT_PORT_MM_STBY_N                             (DIO_ID_PORT10_CH11)
#define PICT_PORT_DISP_REQ_GPIO0                        (DIO_ID_PORT2_CH2)
#define PICT_PORT_CAMERA_CAP_STBY1                      (DIO_ID_PORT11_CH12)
#define PICT_PORT_CAMERA_CAP_STBY2                      (DIO_ID_PORT11_CH15)
#define PICT_PORT_CAMERA_CAP_STBY3                      (DIO_ID_PORT21_CH6)
#define PICT_PORT_PMA_PS_HOLD                           (DIO_ID_PORT3_CH1)
#define PICT_PORT_PM_PSAIL_ERR_N                        (DIO_ID_PORT8_CH4)
#define PICT_PORT_V_IC_RST                              (DIO_ID_PORT3_CH3)
#define PICT_PORT_CAMERA_MODE1                          (DIO_ID_PORT20_CH14)
#define PICT_PORT_MIPI_MUTE                             (DIO_ID_PORT24_CH8)
#define PICT_PORT_PM_V_MUTE                             (DIO_ID_PORT24_CH9)
#define PICT_PORT_V_IC_STATUS                           (DIO_ID_PORT3_CH2)
#define PICT_PORT_GVIF_CAM_RST                          (DIO_ID_PORT10_CH6)
#define PICT_PORT_MM_OFF_REQ                            (DIO_ID_PORT17_CH2)

#define PICT_TIMEOUTCNT_INIT                            (U1_MAX)
#define PICT_TIMEOUTCNT_START                           (0U)
#define PICT_MIPITIMECNT_OFFOUT                         (40U)   /* 40ms */
#define PICT_MIPITIMECNT_OFFOUT2                        (3U)    /* 3ms  */
#define PICT_MIPITIMECNT_OFFOUT3                        (40U)   /* 40ms */

#define PICT_SIP_ERR_OFF                                (0U)
#define PICT_SIP_ERR_ON                                 (1U)

#define PICT_SIP_ERR_NON                                (0U)
#define PICT_SIP_ERR_AUTO                               (1U)
#define PICT_SIP_ERR_MCU                                (2U)

#define PICT_SIPERR_FACTNUM                             (7U)
#define PICT_SIPERR_PMRESIN                             (0U)
#define PICT_SIPERR_PMICFAST                            (1U)
#define PICT_SIPERR_OTA_ACT                             (2U)
#define PICT_SIPERR_PMPSAIL_POL                         (3U)
#define PICT_SIPERR_PMPSAIL_RAW                         (4U)
#define PICT_SIPERR_PMAPSHOLD_POL                       (5U)
#define PICT_SIPERR_PMAPSHOLD_RAW                       (6U)

#define PICT_SIPERRMUTE_NON                             (0U)
#define PICT_SIPERRMUTE_OTA                             (1U)
#define PICT_SIPERRMUTE_MCU                             (2U)

#define PICT_SIPERRREQ_NON                              (0U)
#define PICT_SIPERRREQ_SOC_ERR                          (1U)
#define PICT_SIPERRREQ_PMIC_ERR                         (2U)

#define PICT_SIPERRREQ_OTA_ACT                          (1U)

#define PICT_MONIENSTS_NUM                              (2U)
#define PICT_MONIENSTS_PMPSAILERRN                      (0U)
#define PICT_MONIENSTS_PMAPSHOLD                        (1U)

#define PICT_MONI_DISABLE                               (0U)
#define PICT_MONI_ENABLE                                (1U)
#define PICT_MONI_DETECT                                (2U)

#define PICT_VM_1WORD                                   (1U)

#define PICT_MASK_1BYTE                                 (0x000000FFU)
#define PICT_MASK_2BYTE                                 (0x0000FF00U)
#define PICT_MASK_3BYTE                                 (0x00FF0000U)
#define PICT_MASK_4BYTE                                 (0xFF000000U)

#define PICT_SHIF_1BYTE                                 (8U)
#define PICT_SHIF_2BYTE                                 (16U)
#define PICT_SHIF_3BYTE                                 (24U)

#define PICT_CD_SIZE_TBLNUM                             (16U)

/* カメラ有効領域 */
#define PICT_CD_SIZE_INVALID                            (0x00U) /* 無効値 */
#define PICT_CD_SIZE_1920X1080_140IN                    (0x01U) /* 1920 x 1080 14in   */
#define PICT_CD_SIZE_1920X954_140IN                     (0x02U) /* 1920 x 954  14in   */
#define PICT_CD_SIZE_1696X954_140IN                     (0x03U) /* 1696 x 954  14in   */
#define PICT_CD_SIZE_1920X900_140IN                     (0x04U) /* 1920 x 900  14in   */
#define PICT_CD_SIZE_1920X954_129IN                     (0x05U) /* 1920 x 954  12.9in */
#define PICT_CD_SIZE_1696X954_129IN                     (0x06U) /* 1696 x 954  12.9in */
#define PICT_CD_SIZE_1920X720_123IN                     (0x07U) /* 1920 x 720  12.3in */
#define PICT_CD_SIZE_1280X720_123IN                     (0x08U) /* 1280 x 720  12.3in */
#define PICT_CD_SIZE_1280X720_105IN                     (0x09U) /* 1280 x 720  10.5in */
#define PICT_CD_SIZE_1280X621_105IN                     (0x0AU) /* 1280 x 621  10.5in */
#define PICT_CD_SIZE_1104X621_105IN                     (0x0BU) /* 1104 x 621  10.5in */
#define PICT_CD_SIZE_1280X846_98IN                      (0x0CU) /* 1280 x 846  9.8in  */
#define PICT_CD_SIZE_1280X720_8IN                       (0x0DU) /* 1280 x 720  8in    */
#define PICT_CD_SIZE_1920X954_156IN                     (0x0EU) /* 1920 x 954  15.6in */

/* 車パラ固定値(暫定) */
#define PICT_SIZE_156IN                                 (0U)
#define PICT_SIZE_140IN                                 (1U)
#define PICT_SIZE_129IN                                 (2U)
#define PICT_SIZE_123IN                                 (3U)
#define PICT_SIZE_105IN                                 (4U)
#define PICT_SIZE_80IN                                  (5U)

#define PICT_AIS_KIND_NOMAL                             (0U)
#define PICT_AIS_KIND_HEACON                            (1U)
#define PICT_AIS_KIND_HCNDIAL                           (2U)

#define PICT_VEHOPE_STS_INI                             (0x0000U)
#define PICT_VEHOPE_STS_POWERON                         (0x007EU)
#define PICT_VEHOPE_STS_POWERON_STOP                    (0x007AU)

#define PICT_TIM_BDB1S08_FAILTIM                        (10000U / OXCAN_MAIN_TICK)

#define PICT_STRG_WHL_MAX                               (3U)

#define PICT_RESETREQ_OFF                               (0U)
#define PICT_RESETREQ_ON                                (1U)

#define PICT_RM_DISP_OFF                                (0U)
#define PICT_RM_DISP_ON                                 (1U)

#define PICT_MM_RESET_OFF                               (0U)
#define PICT_MM_RESET_ON                                (1U)

#define PICT_PATH_NOCHG                                 (0U)
#define PICT_PATH_CHG                                   (1U)

#define PICT_VMRESET_NON                                (0U)
#define PICT_VMRESET_REQ                                (1U)
#define PICT_VMRESET_BPASS                              (2U)

#define PICT_SOCRESET_NON                               (0U)
#define PICT_SOCRESET_REQ                               (1U)

#define PICT_CDCRESET_NON                               (0U)
#define PICT_CDCRESET_REQ                               (1U)
#define PICT_CDCRESET_EXE                               (2U)

#define PICT_DRCID_BPASS_SET                            (SYSECDRC_DREC_ID_1)
#define PICT_DRCID_T_SIP_NOTIF_OUT                      (SYSECDRC_DREC_ID_2)
#define PICT_DRCID_POWERON                              (SYSECDRC_DREC_ID_4)
#define PICT_DRCID_GPIO0_EDG                            (SYSECDRC_DREC_ID_5)
#define PICT_DRCID_MUTE                                 (SYSECDRC_DREC_ID_6)
#define PICT_DRCID_CD_SIZE                              (SYSECDRC_DREC_ID_7)

#define PICT_DRCID_PATH_CAMON                           (0x01U)
#define PICT_DRCID_PATH_CAMOFF                          (0x02U)
#define PICT_DRCID_PATH_SYNCOK                          (0x03U)
#define PICT_DRCID_PATH_SYNCNG                          (0x04U)
#define PICT_DRCID_PATH_STBY2                           (0x05U)
#define PICT_DRCID_PATH_CAMFAIL                         (0x06U)
#define PICT_DRCID_PATH_SIPERR                          (0x07U)
#define PICT_DRCID_PATH_VMRESET                         (0x08U)

#define PICT_DRCID_PATH_NORMAL                          (0x01U)
#define PICT_DRCID_PATH_BPASS                           (0x02U)

#define PICT_DRCID_TOUT_NORMAL                          (0x01U)
#define PICT_DRCID_TOUT_BPASS                           (0x02U)
#define PICT_DRCID_TOUT_SYNCNG                          (0x03U)

#define PICT_DRCID_GPIO0_HI                             (0x01U)
#define PICT_DRCID_GPIO0_LO                             (0x02U)

#define PICT_DRCID_MUTE_ALL                             (0x01U)
#define PICT_DRCID_MUTE_NOAIS                           (0x02U)

#define PICT_DRCID_MUTE_OFF                             (0x01U)
#define PICT_DRCID_MUTE_ON                              (0x02U)

#define PICT_MUTEONREQ_ALLOFF                           (0x00U)
#define PICT_MUTEONREQ_NOAIS                            (0x01U)
#define PICT_MUTEOFFREQ_ALLOFF                          (0x02U)
#define PICT_MUTEOFFREQ_NOAIS                           (0x03U)

#define PICT_MUTEFLG_OFF                                (0x00U)
#define PICT_MUTEFLG_ALL                                (0x01U)
#define PICT_MUTEFLG_NOAIS                              (0x02U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct {
    U1 u1_SeqNo;    /* シーケンスNo         */
    U1 u1_PrcNo;    /* プロセスNo           */
} ST_PICT_SEQMNG;   /* シーケンス管理構造体 */

typedef struct {
    void (*func)(void);     /* シーケンス処理関数                */
} ST_PICT_SEQLST;           /* 映像制御シーケンスリスト定義      */

typedef struct {
    U1 u1_timid;                /* タイマID                         */
    void (*func)(void);     /* 通常タイマタイムアウト処理関数   */
} ST_PICT_TIMENT;           /* 映像制御通常タイマリスト定義     */

typedef struct {
    U1  u1_PortCnfSts;          /* 確定ポート状態 */
    U1  u1_PortPreSts;          /* 前回ポーリング検知ポート状態 */
    U2  u2_PollStartWaitTimCnt; /* 開始待ちタイムカウント */
    U1  u1_PollCycTimCnt;       /* 定周期タイムカウント */
    U1  u1_PollSameCnt;         /* 同一論理確定回数 */
    U1  u1_PollSts;             /* 制御状態: PICT_POLLSTS_STOP       ポーリング停止中 */
                                /*           PICT_POLLSTS_START_WAIT ポーリング開始待ち */
                                /*           PICT_POLLSTS_CYC        ポーリング定期 */
} ST_PICT_POLLSTS;

typedef struct {
    U1  (*pfnChk)(void);        /* チェック関数アドレス */
    void    (*pfnChg)(U1 u1_a_sts); /* 結果送信関数アドレス */
    U2  u2_StartWaitTim;            /* 開始待ちタイム(トリガー後 ms経過) */
    U1  u1_CycTim;              /* 定周期時間:検知間隔 */
    U1  u1_SameCntNum;          /* 同一論理判定確定回数 */
    U1  u1_Kind;                    /* 種別 (正論理 or 負論理 or データ) */
    U1  u1_CtlTrg;              /* 制御トリガー */
} ST_PICT_POLLMNG;

typedef struct {
    U1 u1_CamKindDiscEn;        /* カメラシステム種別判別フラグ                 */
    U1 u1_LastCamKind;          /* ラストカメラシステム種別                     */
    U1 u1_CamKindCnt;           /* カメラシステム種別判別カウント               */
    U1 u1_LastCenterCamSiz; /* ラストセンターカメラサイズ                   */
    U1 u1_CenterCamSizCnt;      /* センターカメラサイズ判別カウント             */
} ST_PICT_CAMDISC;          /* 映像制御カメラ種別判別定義       */

typedef struct {
    U1 u1_stasts;                   /* IG状態                                           */
    U1 u1_RcvQualModeFlg;           /* 画質モード通知受け取ったフラグ                   */
    U1 u1_RcvCamQualModeFlg;        /* 画質モード通知(カメラ)受け取ったフラグ           */
    U1 u1_RcvNoCamQualModeFlg;      /* 画質モード通知(カメラ以外)受け取ったフラグ       */
    U1 u1_RcvQualModeDate;          /* 画質モード通知受信情報                           */
    U1 u1_CamCapStbySts;            /* /CAMERA-CAP-STBY検知状態                         */
    U1 u1_CamCapStbyPreSts;         /* /CAMERA-CAP-STBY前回検知状態                     */
    U1 u1_CamCapStby2Sts;           /* /CAMERA-CAP-STBY2検知状態                        */
    U1 u1_CamCapStby2PreSts;        /* /CAMERA-CAP-STBY2前回検知状態                    */
    U1 u1_CamCapStby3Sts;           /* /CAMERA-CAP-STBY3検知状態                        */
    U1 u1_CamCapStby3PreSts;        /* /CAMERA-CAP-STBY3前回検知状態                    */
    U1 u1_MainMipiSetEndFlg;        /* MIPI設定完了フラグ                               */
    U1 u1_MainMipiSetEndSts;        /* MIPI設定完了状態                                 */
    U1 u1_DispReqGpio0rawSts;       /* DISP-REQ-GPIO0検知状態                           */
    U1 u1_DispReqGpio0Sts;          /* DISP-REQ-GPIO0検知状態                           */
    U1 u1_DispReqGpio0PreSts;       /* DISP-REQ-GPIO0前回検知状態                       */
    U1 u1_CamChgSts;                /* カメラ切替状態                                   */
    U1 u1_CamChgOnType;             /* カメラ以外からカメラ状態(バイパス/通常)へ切替    */
    U1 u1_CamChgOffType;            /* カメラ状態(バイパス/通常)からカメラ以外へ切替    */
    U1 u1_DiagMode;                 /* ダイアグモード                                   */
    U1 u1_CamKindConverd;           /* カメラ種別(ADAS/変換BOX)                         */
    U1 u1_GvifCamKindConverd;       /* カメラ種別(ドメコン有/ドメコンなし)              */
    U1 u1_CamSyncOKSeqRunFlg;       /* カメラカメラ同期異常→正常シーケンス未完了フラグ */
    ST_PICT_CAMDISC st_CamDisc;     /* カメラ種別判別管理関連情報                       */
    U1 u1_pmapshold_raw_sts;        /* PMA_PS_HOLD(RAW)検知状態                         */
    U1 u1_pmapshold_pol_sts;        /* PMA_PS_HOLD(POLLING)検知状態                     */
    U1 u1_pmpsholderr_raw_sts;      /* PM_PSAIL_ERR_N(RAW)検知状態                      */
    U1 u1_pmpsholderr_pol_sts;      /* PM_PSAIL_ERR_N(POLLING)検知状態                  */
} ST_PICT_STSMNG;                   /* 映像制御状態管理構造体                           */

 typedef struct {
    U1  u1_CamModeHMainChkErrCnt_N1;    /* メインマイコンのCAMERA-MODE1=Hi 検知異常監視用N1 */
    U1  u1_SyncChkLoopCnt;          /* 同期異常判定のループ回数                 */
    U1  u1_SyncChkSyncCnt;         /* 同期異常判定の同期信号あり回数           */
    U1  u1_SyncChkRlt;              /* 同期異常判定の結果(正常・異常)           */
} ST_ML_CTL; 


/* バックアップデータ管理用 */
typedef struct {
    U1 u1_CamKind;                  /* MAVTYPE  */
    U1 u1_CenterCamSiz;             /* R_CROP_0 */
    U1 u1_handle;                   /* STRG_WHL */
}ST_PICT_BACKUP_MNG_INF;

typedef struct {
    U1  byCamSyncSts;                   /* デジタルカメラ(MIPI)映像入力同期検出 */
    U1  byMipiStsBEye;                  /* 映像IC MIPI(BEYE)        */
    U1  byCamPath;                      /* カメラ強制パス状態       */
    U1  byMipiStsFEye;                  /* 映像IC MIPI(FEYE)        */
} CamSyncPathInfoNty_Msg;


typedef struct {
    U1  u1_CamKind;                 /* カメラ種別               */
    U1  u1_CenterCamSiz;            /* センターカメラサイズ     */
    U1  u1_MeterCamSiz;             /* メーターカメラサイズ     */
    U1  u1_DispReqGpio0Sts;         /* DISP-REQ-GPIO0検知状態   */
    U1  u1_MetReqGpio1Sts;          /* MET-REQ-GPIO1検知状態    */
    U1  u1_SyncChkRlt;              /* 同期異常判定の前回結果(正常・異常)       */
    U1  u1_CamPath;                 /* カメラ強制パス前回状態 */
    U1  u1_MlMipiSts;               /* メインマイコンへのカメラ映像出力前回状態 */
    U1  u1_VideoOutSts;
    U1  u1_vicstastssig;
} ST_PICT_SEND_DATA;

typedef struct {
    U1  u1_now;
    U1  u1_pre;
} ST_PICT_SIPERR_STS;

typedef struct {
    U1  u1_size;
    U1  u1_ais;
    U1  u1_camkind;
    U1  u1_cdsize_sig;
} ST_PICT_CNTDSP_STS;

typedef struct {
    U1  u1_normal;
    U1  u1_bypass;
} ST_PICT_PATH_REQ_STS;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static ST_PICT_SEQMNG   bfg_Pict_SeqMlMng;                      /* MLシーケンス管理バッファ             */
static ST_PICT_POLLSTS  bfg_Pict_PollSts[PICT_POLLNO_MAX];  /* ポーリングステータス管理バッファ */
static ST_PICT_STSMNG   bfg_Pict_StsMng;                        /* 状態管理バッファ     */
static ST_ML_CTL        bfg_Ml_Ctl;       /* ML 管理用バッファ   */
static U1               bfg_Pict_ReqMlSts[PICT_SEQ_ML_NUM];         /* MLシーケンス要求管理バッファ         */
static U2               bfg_Pict_TimMng[PICT_TIMID_MAX];        /* タイマ管理バッファ           */
static ST_PICT_BACKUP_MNG_INF st_sp_Pict_BackUpInf;
static ST_PICT_SEND_DATA      st_sp_send;
static ST_PICT_SIPERR_STS     st_sp_siperr_sts[PICT_SIPERR_FACTNUM];
static ST_PICT_PATH_REQ_STS   st_sp_pict_path_req_sts;
static U1    u1_s_pict_pollstartfhkflg;             /* ポーリング開始待ちチェックフラグ */
static U1    u1_s_pict_siperr;
static U1    u1_s_pict_siperr_old;
static U1    u1_s_pict_siperr_edg_flg;
static U1    u1_s_pict_pmspsh;
static U1    u1_s_pict_vicrset;
static U1    u1_s_pict_apponflg;
static U1    u1_s_pict_syncstarteflg;
static U1    u1_s_pict_poll_act[PICT_POLLFACT_NUM];
static U1    u1_s_pict_mliniflg;
static U1    u1_s_pict_mlcmp_old;
static U1    u1_s_pict_vicstasts;
static U1    u1_s_pict_camoff_muteoff_flg;
static U1    u1_s_pict_camsynccyc_flg;
static U1    u1_s_pict_camsynccyc_step;
static U1    u1_s_pict_camsyncng_step;
static U1    u1_s_pict_vmresetchk_step;
static U1    u1_s_pict_siperrchk_step;
static U1    u1_s_pict_campass_chg_flg;
static U1    u1_s_pict_mipi_chg_flg;
static U1    u1_s_pict_icreset_sts;
static U1    u1_s_pict_camsyncinfo;
static U1    u1_s_pict_regwrite_req;
static U1    u1_s_pict_regwrite_sts;
static U1    u1_s_pict_cd_size;
static U1    u1_s_pict_cammodelog_flg;
static U1    u1_s_pict_vmrsttimeoutcnt;
static U1    u1_s_pict_mipitimeoutcnt;
static U1    u1_s_pict_mipitimeout_jdgval;
static U1    u1_s_pict_siperrfailsafe_flg;
static U1    u1_s_pict_pwrnext_req;
static U1    u1_s_pict_falsepositive_jdgreq;
static U1    u1_s_pict_siperrmute_flg;
static U1    u1_s_pict_siperrmute_req;
static U1    u1_s_pict_siperrmoni_ensts[PICT_MONIENSTS_NUM];
static U1    u1_s_pict_dispsize;
static U1    u1_s_pict_mvdisp_exsit;
static U1    u1_s_pict_heacon;
static U1    u1_s_pict_reset_req;
static U1    u1_s_pict_mm_reset;
static U4    u4_s_pict_power_sts;
static U1    u1_s_pict_vmreset_bpass;
static U1    u1_s_pict_socreset_req;
static U1    u1_s_pict_cdcreset_req;
static U1    u1_s_pict_mutelog_flg;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void vd_s_PictCtl_PollMngInit(void);
static void vd_s_PictCtl_SeqMng(void);
static void vd_s_PictCtl_SetMlSeqReq(U1 u1_a_SeqNo);
static void vd_s_PictCtl_CnclMlSeqReq(U1 u1_a_SeqNo);
static void vd_s_PictCtl_TimMng(void);
static void vd_s_PictCtl_ClrMlSeqInf(void);
static void vd_s_PictCtl_SetTim(U1 u1_a_Id, U2 u2_a_Tim);
static void vd_s_PictCtl_ClrTim(U1 u1_a_Id);
static void vd_s_PictCtl_StsMng(void);
static void vd_s_PictCtl_IgStsChk(void);
static void vd_s_PictCtl_CamCapStbyStsChk(void);
static void vd_s_PictCtl_CamCapStby2StsChk(void);
static void vd_s_PictCtl_CamCapStby3StsChk(void);
static void vd_s_PictCtl_DispReqGpio0StsChk(void);
static void vd_s_PictCtl_MipiOutUpDate(void);
static void vd_s_PictCtl_MipiChg(void);
static void vd_s_PictCtl_CamPathUpDate(void);
static void vd_s_PictCtl_CamPathChg(void);
static void vd_s_PictCtl_CamChgUpDate(void);
static void vd_s_PictCtl_CamChgOn2Off(void);
static void vd_s_PictCtl_MlSeqCamOnChg(void);
static void vd_s_PictCtl_CamChgOffTypeSet(void);
static void vd_s_PictCtl_MainMipiSetEndStsUpDate(void);
static void vd_s_PictCtl_MlSeqCamOffChg(void);
static void vd_s_PictCtl_MlSeqCamSyncNg(void);
static U1   u1_s_PictCtl_MlSeqCamSyncNg(void);
static void vd_s_PictCtl_MlSeqCamSyncOk(void);
static void vd_s_PictCtl_MlSeqIdle(void);
static void vd_s_PictCtl_PollStsInit(U1 u1_a_PortNo);
static U1   u1_s_PictCtl_PollStartChk(void);
static void vd_s_PictCtl_PollMngStart(U1 u1_a_CtlTrg);
static void vd_s_PictCtl_PollMngStop(U1 u1_a_TrgFlg);
static void vd_s_PictCtl_PollMng(void);
static void vd_s_PictCtl_PollPort(void);
static void vd_s_PictCtl_PollStsChk(void);
static void vd_s_PictCtl_DispReqGpio0Chg(U1 u1_a_Sts);
static void vd_s_PictCtl_DispReqGpio0AppChk(void);
static U1   u1_s_PictCtl_DispReqGpio0Chk(void);
static void vd_s_PictCtl_CamCapStbyChg(U1 u1_a_Sts);
static U1   u1_s_PictCtl_CamCapStbyChk(void);
static void vd_s_PictCtl_CamCapStby2Chg(U1 u1_a_Sts);
static U1   u1_s_PictCtl_CamCapStby2Chk(void);
static void vd_s_PictCtl_CamCapStby3Chg(U1 u1_a_Sts);
static U1   u1_s_PictCtl_CamCapStby3Chk(void);
static void vd_s_PictCtl_PmsPsHoldRawChg(U1 u1_a_STS);
static void vd_s_PictCtl_PmsPsHoldPollChg(U1 u1_a_STS);
static U1   u1_s_PictCtl_PmsPsHoldChk(void);
static void vd_s_PictCtl_PmPsailErrnRawChg(U1 u1_a_STS);
static void vd_s_PictCtl_PmPsailErrnPollChg(U1 u1_a_STS);
static U1   u1_s_PictCtl_PmPsailErrnChk(void);
static void vd_s_PictCtl_TSocNotifTout(void);
static void vd_s_PictCtl_CamSyncChkStaTout(void);
static void vd_s_PictCtl_CamSyncChkSta(void);
static void vd_s_PictCtl_CamSyncChkStop(void);
static void vd_s_PictCtl_CamSyncCycChk(void);
static void vd_s_PictCtl_CamSyncJdg(void);
static void vd_s_PictCtl_VmResetChk(void);
static void vd_s_PictCtl_SiPErrChk(void);
static U1   u1_s_PictCtl_SiPErrstsChk(U1* u1p_a_fact);
static void vd_s_PictCtl_SiPErrGetSts(void);
static void vd_s_PictCtl_SiPErrReadReq(void);
static void vd_s_PictCtl_SiPErrReadMoni(void);
static U1   u1_s_PictCtl_AutoSiPOffChk(void);
static U1   u1_s_PictCtl_AutoSiPOffjdg(const U1 u1_a_ENSTS, const U1 u1_a_POL_PRE, const U1 u1_a_POL_NOW, const U1 u1_a_RAW_PRE, const U1 u1_a_RAW_NOW);
static U1   u1_s_PictCtl_McuSiPOffChk(void);
static void vd_s_PictCtl_SiPErrMute(const U1 u1_a_FACT);
static void vd_s_PictCtl_SipErrVIcRstChk(void);
static void vd_s_PictCtl_FalsePositiveChk(void);
static void vd_s_PictCtl_SiPErrClearChk(void);
static void vd_s_PictCtl_PmsPsHoldstsChk(void);
static void vd_s_PictCtl_VIcRstChk(void);
static void vd_s_PictCtl_CycChkStart(void);
static void vd_s_PictCtl_MLIniChk(void);
static void vd_s_PictCtl_CamModeHMainChkErrCycChk(void);
static void vd_s_PictCtl_CamSyncPathInfoNtyChk(void);
static void vd_s_PictCtl_CamSyncPathInfoNtySnd(void);
static void vd_s_PictCtl_CamKindDiscSta(void);
static U1   u1_s_PictCtl_CamKindjdg(void);
static void vd_s_PictCtl_MavtypeTimeout(void);
static U1   u1_s_PictCtl_CamKindValidChk(U1 u1_a_CamKind);
static void vd_s_PictCtl_CamKindConverdUpDate(void);
static void vd_s_PictCtl_GvifCamKindConverdUpDate(void);
static U1   u1_s_PictCtl_CenterCamSizjdg(void);
static U1   u1_s_PictCtl_CenterCamSizValidChk(U1 u1_a_CenterCamSiz);
static void vd_s_PictCtl_Bkup_Write(void);
static void vd_s_PictCtl_CamKindNtyChk(void);
static void vd_s_PictCtl_CamKindNtySnd(void);
static void vd_s_PictCtl_CamOffMuteOff(void);
static void vd_s_PictCtl_CamAreaChk(void);
static void vd_s_PictCtl_CanInputChk(void);
static void vd_s_PictCtl_StrgwhlChk(void);
static void vd_s_PictCtl_StrgwhlUpdate(const U1 u1_a_HANDLE);
static void vd_s_PictCtl_Bcc1s05Timeout(void);
static void vd_s_PictCtl_MmresetSndChk(void);
static void vd_s_PictCtl_MutelogChk(const U1 u1_a_KIND);

/* 暫定対応 */
static void vd_s_PictCtl_CdsizeChk(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_PICT_SEQLST tbl_Pict_MlCtlSeq[PICT_SEQ_ML_NUM] = {
    /* シーケンスの順序、数はデバイス制御シーケンスのenumテーブルと一致させること   */
    {   vd_s_PictCtl_MlSeqCamOnChg          },      /* PICT_SEQ_ML_CAMONCHG         カメラへ切替                        */
    {   vd_s_PictCtl_MlSeqCamOffChg         },      /* PICT_SEQ_ML_CAMOFFCHG        カメラ以外へ切替                    */
    {   vd_s_PictCtl_MlSeqCamSyncNg         },      /* PICT_SEQ_ML_CAMSYNCNG        カメラカメラ同期正常→異常          */
    {   vd_s_PictCtl_MlSeqCamSyncOk         },      /* PICT_SEQ_ML_CAMSYNCOK        カメラカメラ同期異常→正常          */
    {   vd_s_PictCtl_MlSeqIdle              }       /* PICT_SEQ_ML_IDLE             アイドル                            */
};

static const ST_PICT_TIMENT tbl_Pict_TimInf[] = {
    /*------------------------------------------------------------------*/
    /*  MLフェールセーフ 設定待ちタイマ                                 */
    /*------------------------------------------------------------------*/
    {   (U1)PICT_TIMID_ML_CAM_MODE1_ERR_CHKCYC,         vd_s_PictCtl_CamModeHMainChkErrCycChk        },
    {   (U1)PICT_TIMID_ML_T_SIP_NOTIF_OUT,              vd_s_PictCtl_TSocNotifTout                   },
    {   (U1)PICT_TIMID_ML_CAMSYNC_CHKSTA,               vd_s_PictCtl_CamSyncChkStaTout               },
    {   (U1)PICT_TIMID_ML_CAMSYNC_CHKCYC,               vd_s_PictCtl_CamSyncCycChk                   },

    /*------------------------------------------------------------------*/
    /*  GVIFB定周期フェールセーフチェック(250ms)                        */
    /*------------------------------------------------------------------*/
    {   (U1)PICT_TIMID_CAM_KIND_DISC_STA_WAIT,          vd_s_PictCtl_CamKindDiscSta             },
    {   (U1)PICT_TIMID_CAMKIND_SENDCYC,                 vd_s_PictCtl_CamKindNtySnd              },
    {   (U1)PICT_TIMID_CAMSYNCPATHINFO_SENDCYC,         vd_s_PictCtl_CamSyncPathInfoNtySnd      },
    {   (U1)PICT_TIMID_MAVTYPE_TIMEOUT,                 vd_s_PictCtl_MavtypeTimeout             },
    {   (U1)PICT_TIMID_BCC1S05_TIMEOUT,                 vd_s_PictCtl_Bcc1s05Timeout             },
    {   (U1)PICT_TIMID_CANSIGNAL_GETCYC,                vd_s_PictCtl_CanInputChk                }
};


static const ST_PICT_POLLMNG tb_Pict_PollMng[PICT_POLLNO_MAX]
= {
    /*-- No.00 -------------------------------------------------------------*/
    /*  DISP-REQ-GPIO0          AUDIO-ON Hから40msで開始, 1ms周期, 連続5回  */
    /*----------------------------------------------------------------------*/
    {
        u1_s_PictCtl_DispReqGpio0Chk,       /* チェック関数アドレス         */
        vd_s_PictCtl_DispReqGpio0Chg,       /* 結果送信関数アドレス         */
        (U2)40U,                            /* 開始時間(ms)                 */
        (U1)1U,                             /* 定周期時間:検知間隔(ms)      */
        (U1)5U,                             /* 判定確定回数                 */
        (U1)PICT_POLLPORT_HIACTIVE,         /* 種別 (正論理 or 負論理)      */
        (U1)PICT_POLLTRG_AUDIOON,           /* ポーリング開始終了トリガー   */
    },
    /*-- No.01 -------------------------------------------------------------*/
    /*  MIPI(BEYE)キャプチャ準備    /MM-STBY Hから0msで開始, 1ms周期, 連続1回  */
    /*----------------------------------------------------------------------*/
    {
        u1_s_PictCtl_CamCapStbyChk,         /* チェック関数アドレス         */
        vd_s_PictCtl_CamCapStbyChg,         /* 結果送信関数アドレス         */
        (U2)0U,                             /* 開始待ち時間(ms)             */
        (U1)1U,                             /* 定周期時間:検知間隔(ms)      */
        (U1)1U,                             /* 判定確定回数                 */
        (U1)PICT_POLLPORT_HIACTIVE,         /* 種別 (正論理 or 負論理)      */
        (U1)PICT_POLLTRG_MMSTBY,            /* ポーリングトリガー           */
    },
    /*-- No.02 -------------------------------------------------------------*/
    /*  MIPI(BEYE)カメラ出力可能    /MM-STBY Hから0msで開始, 1ms周期, 連続1回  */
    /*----------------------------------------------------------------------*/
    {
        u1_s_PictCtl_CamCapStby2Chk,        /* チェック関数アドレス         */
        vd_s_PictCtl_CamCapStby2Chg,        /* 結果送信関数アドレス         */
        (U2)0U,                             /* 開始待ち時間(ms)             */
        (U1)1U,                             /* 定周期時間:検知間隔(ms)      */
        (U1)1U,                             /* 判定確定回数                 */
        (U1)PICT_POLLPORT_HIACTIVE,         /* 種別 (正論理 or 負論理)      */
        (U1)PICT_POLLTRG_MMSTBY,            /* ポーリングトリガー           */
    },
    /*-- No.03 -------------------------------------------------------------*/
    /*  MIPI(FEYE)キャプチャ準備    /MM-STBY Hから0msで開始, 1ms周期, 連続1回  */
    /*----------------------------------------------------------------------*/
    {
        u1_s_PictCtl_CamCapStby3Chk,        /* チェック関数アドレス         */
        vd_s_PictCtl_CamCapStby3Chg,        /* 結果送信関数アドレス         */
        (U2)0U,                             /* 開始待ち時間(ms)             */
        (U1)1U,                             /* 定周期時間:検知間隔(ms)      */
        (U1)1U,                             /* 判定確定回数                 */
        (U1)PICT_POLLPORT_HIACTIVE,         /* 種別 (正論理 or 負論理)      */
        (U1)PICT_POLLTRG_MMSTBY,            /* ポーリングトリガー           */
    },
    /*-- No.04 -------------------------------------------------------------*/
    /*  PMA_PS_HOLD          LOW-POWER-ON Hから0msで開始, 5ms周期, 連続1回  */
    /*----------------------------------------------------------------------*/
    {
        u1_s_PictCtl_PmsPsHoldChk,          /* チェック関数アドレス         */
        vd_s_PictCtl_PmsPsHoldRawChg,       /* 結果送信関数アドレス         */
        (U2)0U,                             /* 開始時間(ms)                 */
        (U1)1U,                             /* 定周期時間:検知間隔(ms)      */
        (U1)1U,                             /* 判定確定回数                 */
        (U1)PICT_POLLPORT_HIACTIVE,         /* 種別 (正論理 or 負論理)      */
        (U1)PICT_POLLTRG_LOWPOWERON,        /* ポーリング開始終了トリガー   */
    },
    /*-- No.05 -------------------------------------------------------------*/
    /*  PMA_PS_HOLD          LOW-POWER-ON Hから0msで開始, 5ms周期, 連続3回  */
    /*----------------------------------------------------------------------*/
    {
        u1_s_PictCtl_PmsPsHoldChk,          /* チェック関数アドレス         */
        vd_s_PictCtl_PmsPsHoldPollChg,      /* 結果送信関数アドレス         */
        (U2)0U,                             /* 開始時間(ms)                 */
        (U1)5U,                             /* 定周期時間:検知間隔(ms)      */
        (U1)3U,                             /* 判定確定回数                 */
        (U1)PICT_POLLPORT_HIACTIVE,         /* 種別 (正論理 or 負論理)      */
        (U1)PICT_POLLTRG_LOWPOWERON,        /* ポーリング開始終了トリガー   */
    },
    /*-- No.06 -------------------------------------------------------------*/
    /*  PM_PSAIL_ERR_N       LOW-POWER-ON Hから0msで開始, 5ms周期, 連続1回  */
    /*----------------------------------------------------------------------*/
    {
        u1_s_PictCtl_PmPsailErrnChk,        /* チェック関数アドレス         */
        vd_s_PictCtl_PmPsailErrnRawChg,     /* 結果送信関数アドレス         */
        (U2)0U,                             /* 開始時間(ms)                 */
        (U1)1U,                             /* 定周期時間:検知間隔(ms)      */
        (U1)1U,                             /* 判定確定回数                 */
        (U1)PICT_POLLPORT_HIACTIVE,         /* 種別 (正論理 or 負論理)      */
        (U1)PICT_POLLTRG_LOWPOWERON,        /* ポーリング開始終了トリガー   */
    },
    /*-- No.07 -------------------------------------------------------------*/
    /* PM_PSAIL_ERR_N        LOW-POWER-ON Hから0msで開始, 5ms周期, 連続3回  */
    /*----------------------------------------------------------------------*/
    {
        u1_s_PictCtl_PmPsailErrnChk,        /* チェック関数アドレス         */
        vd_s_PictCtl_PmPsailErrnPollChg,    /* 結果送信関数アドレス         */
        (U2)0U,                             /* 開始時間(ms)                 */
        (U1)5U,                             /* 定周期時間:検知間隔(ms)      */
        (U1)3U,                             /* 判定確定回数                 */
        (U1)PICT_POLLPORT_HIACTIVE,         /* 種別 (正論理 or 負論理)      */
        (U1)PICT_POLLTRG_LOWPOWERON,        /* ポーリング開始終了トリガー   */
    }
};

static const ST_PICT_CNTDSP_STS st_sp_PICT_CDSIZE_TBL[PICT_CD_SIZE_TBLNUM] =
{
    {(U1)PICT_SIZE_156IN, (U1)PICT_AIS_KIND_HEACON,  (U1)PICT_GVIFIF_ADAS,   (U1)PICT_CD_SIZE_1920X954_156IN },
    {(U1)PICT_SIZE_140IN, (U1)PICT_AIS_KIND_NOMAL,   (U1)PICT_GVIFIF_ADAS,   (U1)PICT_CD_SIZE_1920X1080_140IN},
    {(U1)PICT_SIZE_140IN, (U1)PICT_AIS_KIND_NOMAL,   (U1)PICT_GVIFIF_CNVBOX, (U1)PICT_CD_SIZE_1920X1080_140IN},
    {(U1)PICT_SIZE_140IN, (U1)PICT_AIS_KIND_HEACON,  (U1)PICT_GVIFIF_ADAS,   (U1)PICT_CD_SIZE_1920X954_140IN },
    {(U1)PICT_SIZE_140IN, (U1)PICT_AIS_KIND_HEACON,  (U1)PICT_GVIFIF_CNVBOX, (U1)PICT_CD_SIZE_1696X954_140IN },
    {(U1)PICT_SIZE_140IN, (U1)PICT_AIS_KIND_HCNDIAL, (U1)PICT_GVIFIF_ADAS,   (U1)PICT_CD_SIZE_1920X900_140IN },
    {(U1)PICT_SIZE_129IN, (U1)PICT_AIS_KIND_HEACON,  (U1)PICT_GVIFIF_ADAS,   (U1)PICT_CD_SIZE_1920X954_129IN },
    {(U1)PICT_SIZE_129IN, (U1)PICT_AIS_KIND_HEACON,  (U1)PICT_GVIFIF_CNVBOX, (U1)PICT_CD_SIZE_1696X954_129IN },
    {(U1)PICT_SIZE_123IN, (U1)PICT_AIS_KIND_NOMAL,   (U1)PICT_GVIFIF_ADAS,   (U1)PICT_CD_SIZE_1920X720_123IN },
    {(U1)PICT_SIZE_123IN, (U1)PICT_AIS_KIND_NOMAL,   (U1)PICT_GVIFIF_CNVBOX, (U1)PICT_CD_SIZE_1280X720_123IN },
    {(U1)PICT_SIZE_105IN, (U1)PICT_AIS_KIND_NOMAL,   (U1)PICT_GVIFIF_ADAS,   (U1)PICT_CD_SIZE_1280X720_105IN },
    {(U1)PICT_SIZE_105IN, (U1)PICT_AIS_KIND_NOMAL,   (U1)PICT_GVIFIF_CNVBOX, (U1)PICT_CD_SIZE_1280X720_105IN },
    {(U1)PICT_SIZE_105IN, (U1)PICT_AIS_KIND_HEACON,  (U1)PICT_GVIFIF_ADAS,   (U1)PICT_CD_SIZE_1280X621_105IN },
    {(U1)PICT_SIZE_105IN, (U1)PICT_AIS_KIND_HEACON,  (U1)PICT_GVIFIF_CNVBOX, (U1)PICT_CD_SIZE_1104X621_105IN },
    {(U1)PICT_SIZE_80IN,  (U1)PICT_AIS_KIND_NOMAL,   (U1)PICT_GVIFIF_ADAS,   (U1)PICT_CD_SIZE_1280X720_8IN   },
    {(U1)PICT_SIZE_80IN,  (U1)PICT_AIS_KIND_NOMAL,   (U1)PICT_GVIFIF_CNVBOX, (U1)PICT_CD_SIZE_1280X720_8IN   }
};

static const U1 u1_sp_PICT_HANDLE_TBL[PICT_STRG_WHL_MAX] =
{
    (U1)PICT_HANDLE_RIGHT,
    (U1)PICT_HANDLE_LEFT,
    (U1)PICT_HANDLE_RIGHT
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void vd_g_PictCtl_Init(void)                                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_PictCtl_Init(void)
{
    U1 u1_t_trg;
    U1 u1_t_cnt;

/* ポーリング */
    vd_s_PictCtl_PollMngInit();

/* シーケンス */
    bfg_Pict_SeqMlMng.u1_SeqNo = (U1)PICT_SEQ_ML_IDLE; 
    bfg_Pict_SeqMlMng.u1_PrcNo = (U1)PICT_SEQ_INI;
    for(u1_t_cnt = (U1)0U; u1_t_cnt < (U1)PICT_SEQ_ML_NUM; u1_t_cnt++)
    {
        bfg_Pict_ReqMlSts[u1_t_cnt] = (U1)PICT_SEQREQ_IDL;
    }

/* 同期経路判定 */
    bfg_Ml_Ctl.u1_CamModeHMainChkErrCnt_N1 = (U1)PICT_CNT_INI;
    bfg_Ml_Ctl.u1_SyncChkLoopCnt = (U1)PICT_CNT_INI;
    bfg_Ml_Ctl.u1_SyncChkSyncCnt = (U1)PICT_CNT_INI;
    bfg_Ml_Ctl.u1_SyncChkRlt = (U1)PICT_CAM_SYNC_CHK_UNJDG;

    st_sp_Pict_BackUpInf.u1_CamKind = (U1)0U;      /* DTFバックアップ値を設定(暫定) */
    st_sp_Pict_BackUpInf.u1_CenterCamSiz= (U1)0U;  /* DTFバックアップ値を設定(暫定) */

    bfg_Pict_StsMng.u1_stasts = (U1)POWER_MODE_STATE_PARK;
    bfg_Pict_StsMng.u1_RcvQualModeFlg = (U1)FALSE;
    bfg_Pict_StsMng.u1_RcvCamQualModeFlg = (U1)FALSE;
    bfg_Pict_StsMng.u1_RcvNoCamQualModeFlg = (U1)PICT_RCV_NOCAMQUAL_NONE;
    bfg_Pict_StsMng.u1_RcvQualModeDate = (U1)0;
    bfg_Pict_StsMng.u1_CamCapStbySts = (U1)PICT_POLLPORT_UNFIX;
    bfg_Pict_StsMng.u1_CamCapStbyPreSts = (U1)PICT_POLLPORT_UNFIX;
    bfg_Pict_StsMng.u1_CamCapStby2Sts = (U1)PICT_POLLPORT_UNFIX;
    bfg_Pict_StsMng.u1_CamCapStby2PreSts = (U1)PICT_POLLPORT_UNFIX;
    bfg_Pict_StsMng.u1_CamCapStby3Sts = (U1)PICT_POLLPORT_UNFIX;
    bfg_Pict_StsMng.u1_CamCapStby3PreSts = (U1)PICT_POLLPORT_UNFIX;
    bfg_Pict_StsMng.u1_MainMipiSetEndFlg = (U1)FALSE;
    bfg_Pict_StsMng.u1_MainMipiSetEndSts = (U1)FALSE;
    bfg_Pict_StsMng.u1_DispReqGpio0rawSts = (U1)PICT_POLLPORT_UNFIX;
    bfg_Pict_StsMng.u1_DispReqGpio0Sts = (U1)PICT_POLLPORT_UNFIX;
    bfg_Pict_StsMng.u1_DispReqGpio0PreSts = (U1)PICT_POLLPORT_UNFIX;
    bfg_Pict_StsMng.u1_CamChgSts = (U1)PICT_CAMCHG_STS_OFF;
    bfg_Pict_StsMng.u1_CamChgOnType = (U1)PICT_CAMON_TO_NORMAL;
    bfg_Pict_StsMng.u1_CamChgOffType = (U1)PICT_CAMOFF_FORM_NORMAL;
    bfg_Pict_StsMng.u1_DiagMode = (U1)PICT_DIAG_MOD_OFF;
    bfg_Pict_StsMng.u1_CamKindConverd = (U1)PICT_GVIFIF_NONE;
    bfg_Pict_StsMng.u1_GvifCamKindConverd = (U1)PICT_KIND_CAM_NONE;
    vd_s_PictCtl_CamKindConverdUpDate();
    vd_s_PictCtl_GvifCamKindConverdUpDate();
    bfg_Pict_StsMng.u1_CamSyncOKSeqRunFlg = (U1)FALSE;
    bfg_Pict_StsMng.st_CamDisc.u1_CamKindDiscEn = (U1)FALSE;
    bfg_Pict_StsMng.st_CamDisc.u1_LastCamKind = st_sp_Pict_BackUpInf.u1_CamKind;
    bfg_Pict_StsMng.st_CamDisc.u1_CamKindCnt = (U1)PICT_SAMECNT_INI;
    bfg_Pict_StsMng.st_CamDisc.u1_LastCenterCamSiz = st_sp_Pict_BackUpInf.u1_CenterCamSiz;
    bfg_Pict_StsMng.st_CamDisc.u1_CenterCamSizCnt = (U1)PICT_SAMECNT_INI;
    bfg_Pict_StsMng.u1_pmapshold_raw_sts = (U1)PICT_POLLPORT_UNFIX;
    bfg_Pict_StsMng.u1_pmapshold_pol_sts = (U1)PICT_POLLPORT_UNFIX;
    bfg_Pict_StsMng.u1_pmpsholderr_raw_sts = (U1)PICT_POLLPORT_UNFIX;
    bfg_Pict_StsMng.u1_pmpsholderr_pol_sts = (U1)PICT_POLLPORT_UNFIX;

/* タイマカウンタ */
    for(u1_t_cnt = (U1)0U; u1_t_cnt < (U1)PICT_TIMID_MAX; u1_t_cnt++)
    {
        bfg_Pict_TimMng[u1_t_cnt] = (U2)PICT_TIM_STOP;
    }
    
    u1_t_trg = (U1)PICT_POLLTRG_AUDIOON | (U1)PICT_POLLTRG_MMSTBY;
    vd_s_PictCtl_PollMngStop(u1_t_trg);
    
    u1_s_pict_siperr = (U1)PICT_SIP_ERR_OFF;
    u1_s_pict_siperr_old = (U1)PICT_SIP_ERR_OFF;
    u1_s_pict_pmspsh = (U1)FALSE;
    u1_s_pict_vicrset = (U1)FALSE;
    u1_s_pict_apponflg = (U1)FALSE;
    u1_s_pict_syncstarteflg = (U1)FALSE;
    u1_s_pict_mliniflg = (U1)FALSE;
    u1_s_pict_mlcmp_old = (U1)FALSE;
    u1_s_pict_vicstasts = (U1)FALSE;
    u1_s_pict_camoff_muteoff_flg = (U1)PICT_TOUT_MUTEOFF;
    u1_s_pict_camsynccyc_flg = (U1)FALSE;
    u1_s_pict_camsynccyc_step = (U1)PICT_SEQ_CAMSYNCCHK_STEP0;
    u1_s_pict_camsyncng_step  = (U1)PICT_SEQ_CAMONSYNCNG_STEP0;
    u1_s_pict_vmresetchk_step = (U1)PICT_SEQ_VMRESETCHK_STEP_FIN;
    u1_s_pict_siperrchk_step = (U1)PICT_SEQ_SIPERRCHK_STEP_NON;
    u1_s_pict_campass_chg_flg = (U1)PICT_CAM_PATH_NOCHG;
    u1_s_pict_mipi_chg_flg = (U1)PICT_MIPI_OUT_NON;
    u1_s_pict_icreset_sts = (U1)FALSE;
    u1_s_pict_camsyncinfo = (U1)PICT_ML_MIPI_SYNC_OFF;
    u1_s_pict_regwrite_req = (U1)FALSE;
    u1_s_pict_regwrite_sts = (U1)PICT_ML_CAMAREASET_COMPLETED;
    u1_s_pict_cd_size = (U1)PICT_CD_SIZE_INVALID;
    u1_s_pict_cammodelog_flg = (U1)FALSE;
    u1_s_pict_vmrsttimeoutcnt = (U1)PICT_TIMEOUTCNT_INIT;
    u1_s_pict_mipitimeoutcnt = (U1)PICT_TIMEOUTCNT_INIT;
    u1_s_pict_mipitimeout_jdgval = (U1)PICT_MIPITIMECNT_OFFOUT2;
    u1_s_pict_siperrfailsafe_flg = (U1)PICT_SIP_ERR_OFF;
    u1_s_pict_pwrnext_req = (U1)FALSE;
    u1_s_pict_falsepositive_jdgreq = (U1)FALSE;
    u1_s_pict_siperrmute_flg = (U1)FALSE;
    u1_s_pict_siperrmute_req = (U1)PICT_SIPERRMUTE_NON;
    u1_s_pict_dispsize = (U1)PICT_SIZE_140IN; /* 車パラ対応までの暫定 */
    u1_s_pict_mvdisp_exsit = (U1)TRUE; /* 車パラ対応までの暫定 */
    u1_s_pict_heacon = (U1)PICT_AIS_KIND_HEACON; /* 車パラ対応までの暫定 */
    u1_s_pict_reset_req = (U1)PICT_RESETREQ_OFF;
    u1_s_pict_mm_reset = (U1)PICT_MM_RESET_OFF;
    u4_s_pict_power_sts = (U1)PICT_VEHOPE_STS_INI;
    
    st_sp_send.u1_CamKind = st_sp_Pict_BackUpInf.u1_CamKind;
    st_sp_send.u1_CenterCamSiz = st_sp_Pict_BackUpInf.u1_CenterCamSiz;
    st_sp_send.u1_MeterCamSiz = (U1)PICT_METER_CAM_SIZE_UNFIX;
    st_sp_send.u1_DispReqGpio0Sts = (U1)PICT_POLLPORT_UNFIX;
    st_sp_send.u1_MetReqGpio1Sts = (U1)PICT_CAM_DET_UNFIX;
    st_sp_send.u1_SyncChkRlt = PICT_CAM_SYNC_CHK_UNJDG;
    st_sp_send.u1_MlMipiSts = (U1)PICT_POLLPORT_UNFIX;
    st_sp_send.u1_CamPath = (U1)PICT_POLLPORT_UNFIX;
    st_sp_send.u1_VideoOutSts = (U1)GVIF3RX_MIPIOUTPUT_OFF;
    st_sp_send.u1_vicstastssig = (U1)FALSE;
    
    st_sp_pict_path_req_sts.u1_normal = (U1)PICT_PATH_NOCHG;
    st_sp_pict_path_req_sts.u1_bypass = (U1)PICT_PATH_NOCHG;
    u1_s_pict_vmreset_bpass = (U1)PICT_VMRESET_NON;
    u1_s_pict_socreset_req = (U1)PICT_SOCRESET_NON;
    u1_s_pict_cdcreset_req = (U1)PICT_CDCRESET_NON;
    u1_s_pict_mutelog_flg = (U1)PICT_MUTEFLG_OFF;
    
    for(u1_t_cnt = (U1)0U; u1_t_cnt < (U1)PICT_POLLFACT_NUM; u1_t_cnt++)
    {
        u1_s_pict_poll_act[u1_t_cnt] = (U1)FALSE;
    }
    
    for(u1_t_cnt = (U1)0U; u1_t_cnt < (U1)PICT_SIPERR_FACTNUM; u1_t_cnt++)
    {
        st_sp_siperr_sts[u1_t_cnt].u1_now = (U1)PICT_SIP_ERR_OFF;
        st_sp_siperr_sts[u1_t_cnt].u1_pre = (U1)PICT_SIP_ERR_OFF;
    }
    
    for(u1_t_cnt = (U1)0U; u1_t_cnt < (U1)PICT_MONIENSTS_NUM; u1_t_cnt++)
    {
        u1_s_pict_siperrmoni_ensts[u1_t_cnt] = (U1)PICT_MONI_DISABLE;
    }

    vd_s_PictCtl_CamKindNtySnd();
    vd_s_PictCtl_CamSyncPathInfoNtySnd();
    vd_s_PictCtl_SetTim((U1)PICT_TIMID_CANSIGNAL_GETCYC, (U2)PICT_TIMER_CANSIGNAL_GETCYC);
}

/*============================================================================
 * ポーリング管理機能初期化処理
 *----------------------------------------------------------------------------
 * モジュール名 : fc_PictCtl_PollMngInit
 * 機能         : ポーリング管理機能初期化処理
 * 処理内容     : ポーリング動作管理バッファ初期化を行う
* 入力(引数)    : なし
* 出力(戻値)    : なし
* 制限事項      :
* 作成者        : NOAH)馬孝康
* ---------------------------------------------------------------------------
* 変更履歴      : 2022.05.04 新規作成
* 変更者        : 
===========================================================================*/
static void vd_s_PictCtl_PollMngInit(void)
{
    U1 u1_t_PollNo;

    /* ポーリング状態初期化処理 */
    for (u1_t_PollNo = (U1)0U; u1_t_PollNo < (U1)PICT_POLLNO_MAX; u1_t_PollNo++) {
        vd_s_PictCtl_PollStsInit(u1_t_PollNo);
    }

    /* ポーリング開始待ちチェックフラグOFF */
    u1_s_pict_pollstartfhkflg = (U1)FALSE;
}

/*============================================================================
 * 映像制御タスクメイン
 *----------------------------------------------------------------------------
 * モジュール名 : tsk_Pict_Ctl
 * 機能         : 映像制御タスクのメイン処理
 * 処理内容     : 
 * 入力（引数） : 無し
 * 出力（戻値） : 無し
 * 制限事項     : 無し
 * 作成者       : NOAH)施 燕慧
 * ---------------------------------------------------------------------------
 * 変更履歴     : 2021.10.27 NOAH)施燕慧 新規作成
 *              : 
 ===========================================================================*/
void vd_g_PictCtl_MainTask(void)
{
    vd_s_PictCtl_PollMng();
    vd_s_PictCtl_TimMng();
    vd_s_PictCtl_StsMng();
    vd_s_PictCtl_SeqMng();
    vd_s_PictCtl_MipiChg();
    vd_s_PictCtl_CamPathChg();
    vd_s_PictCtl_CamSyncJdg();
    vd_s_PictCtl_CamOffMuteOff();
    vd_s_PictCtl_CamKindNtyChk();
    vd_s_PictCtl_CamSyncPathInfoNtyChk();
    vd_s_PictCtl_CamAreaChk();
}

/*===================================================================================================================================*/
/*  static void vd_s_PictCtl_SeqMng(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PictCtl_SeqMng(void)
{
    U1 u1_t_cnt;

    /*----------------------------------------------------------------------*/
    /* 要求シーケンスチェック                                               */
    /*----------------------------------------------------------------------*/
    if(bfg_Pict_SeqMlMng.u1_SeqNo == (U1)PICT_SEQ_ML_IDLE)
    {
        for (u1_t_cnt = (U1)0; u1_t_cnt < (U1)PICT_SEQ_ML_NUM; u1_t_cnt++)
        {
            /* 実行待ちSEQの優先度が高いほうから次回実行SEQを決定 */
            if(bfg_Pict_ReqMlSts[u1_t_cnt] == (U1)PICT_SEQREQ_WAI)
            {
                /* 次回実行SEQの取得結果を反映 */
                vd_s_PictCtl_ClrMlSeqInf();
                bfg_Pict_SeqMlMng.u1_SeqNo = u1_t_cnt;

                bfg_Pict_ReqMlSts[u1_t_cnt] = (U1)PICT_SEQREQ_IDL;
                break;
            }
        }
    }

    if(bfg_Pict_SeqMlMng.u1_SeqNo >= (U1)PICT_SEQ_ML_NUM)
    {
        /* 範囲外の場合、シーケンス情報クリアして、アイドルシーケンス実行 */
        vd_s_PictCtl_ClrMlSeqInf();
    }
    
    /*----------------------------------------------------------------------*/
    /* シーケンス実行                                                       */
    /*----------------------------------------------------------------------*/
    if(bfg_Pict_SeqMlMng.u1_SeqNo < (U1)PICT_SEQ_ML_NUM){
        if(tbl_Pict_MlCtlSeq[bfg_Pict_SeqMlMng.u1_SeqNo].func != NULL_PTR) {
            tbl_Pict_MlCtlSeq[bfg_Pict_SeqMlMng.u1_SeqNo].func();
        }
    }
}

/*============================================================================
 * MLシーケンス要求設定
 *----------------------------------------------------------------------------
 * モジュール名 : vd_s_PictCtl_SetMlSeqReq
 * 機能         : MLシーケンス要求設定処理
 * 処理内容     : ML要求を受けた制御シーケンスを予約する
 * 入力（引数） : U1 u1_SeqNo：要求シーケンスNo
 * 出力（戻値） : 無し
 * 制限事項     : ①実行中シーケンスを再要求した場合は実行中シーケンスを中断し
 *              :   同シーケンスの最初から再実行する
 *              : ②シーケンス要求時に別シーケンス実行中の場合は、
 *              :   シーケンスの予約だけを行い、実行中シーケンスを
 *              :   最後まで実行した後に、次の実行シーケンスを選択する。
 * 作成者       : NOAH)馬
 * ---------------------------------------------------------------------------
 * 変更履歴     : 2022.11.10 NOAH)馬      新規作成
 ===========================================================================*/
static void vd_s_PictCtl_SetMlSeqReq(U1 u1_a_SeqNo)
{
    if(u1_a_SeqNo < (U1)PICT_SEQ_ML_NUM)
    {
        /* 実行中のシーケンスと同じ要求が入った場合は   */
        /* シーケンスの先頭からやり直す                 */
        if(u1_a_SeqNo == bfg_Pict_SeqMlMng.u1_SeqNo)
        {
            bfg_Pict_SeqMlMng.u1_PrcNo = (U1)PICT_SEQ_INI;
        }
        else
        {
            /* 指定シーケンスの要求を立てる */
            bfg_Pict_ReqMlSts[u1_a_SeqNo] = (U1)PICT_SEQREQ_WAI;
        }
    }
}

/*============================================================================
 * MLシーケンス要求キャンセル
 *----------------------------------------------------------------------------
 * モジュール名 : vd_s_PictCtl_CnclMlSeqReq
 * 機能         : MLシーケンス要求キャンセル処理
 * 処理内容     : ML要求を受けた制御シーケンスをキャンセルする
 * 入力（引数） : U1 u1_SeqNo：キャンセル要求シーケンスNo
 * 出力（戻値） : 無し
 * 制限事項     : 無し
 * 作成者       : NOAH)馬
 * ---------------------------------------------------------------------------
 * 変更履歴     : 2022.11.10 NOAH)馬      新規作成
 ===========================================================================*/
static void vd_s_PictCtl_CnclMlSeqReq(U1 u1_a_SeqNo)
{
    if(u1_a_SeqNo < (U1)PICT_SEQ_ML_NUM)
    {
        /* 実行中のシーケンスと同じ要求が入った場合は、SEQ情報とプロセス間タイマをクリア */
        if(u1_a_SeqNo == bfg_Pict_SeqMlMng.u1_SeqNo)
        {
            /* SEQ情報クリア */
            vd_s_PictCtl_ClrMlSeqInf();
        }
        else
        {
            /* 指定シーケンスの要求をキャンセルする */
            bfg_Pict_ReqMlSts[u1_a_SeqNo] = (U1)PICT_SEQREQ_IDL;
        }
    }
}

/*============================================================================
 * MLシーケンス情報クリア
 *----------------------------------------------------------------------------
 * モジュール名 : fc_PictCtl_ClrMlSeqInf
 * 機能         : MLシーケンス情報クリア処理
 * 処理内容     : 実行中(実行完了含む)シーケンス情報をクリアする
 * 入力（引数） : 無し
 * 出力（戻値） : 無し
 * 制限事項     : 無し
 * 作成者       : NOAH)馬
 * ---------------------------------------------------------------------------
 * 変更履歴     : 2022.11.10 NOAH)馬      新規作成
 ===========================================================================*/
static void vd_s_PictCtl_ClrMlSeqInf(void)
{
    /* SEQ情報クリア */
    bfg_Pict_SeqMlMng.u1_SeqNo = (U1)PICT_SEQ_ML_IDLE;  /* シーケンス：アイドル */
    bfg_Pict_SeqMlMng.u1_PrcNo = (U1)PICT_SEQ_INI;      /* プロセスNo：0        */

    /* プロセス間タイマクリア */
    vd_s_PictCtl_ClrTim((U1)PICT_TIMID_ML_PRC_T1);
    vd_s_PictCtl_ClrTim((U1)PICT_TIMID_ML_PRC_T2);
}
/**********************************************************************************************************************************
タイマ管理
***********************************************************************************************************************************/

/*============================================================================
 * タイマ管理処理
 *----------------------------------------------------------------------------
 * モジュール名 : fc_PictCtl_TimMng
 * 機能         : タイマ管理処理
 * 処理内容     : 管理しているタイマを減算して、タイムアウト処理を行う
 * 入力（引数） : 無し
 * 出力（戻値） : 無し
 * 制限事項     : 無し
 * 作成者       : NOAH)施燕慧
 * -------------------------------------------------------------------------
 * 変更履歴     : 2021.10.27 NOAH)施燕慧 新規作成
 *              : 
 ===========================================================================*/
static void vd_s_PictCtl_TimMng(void)
{
    U1 u1_t_cnt;

    /* タイマを減算 */
    for(u1_t_cnt = (U1)0U; u1_t_cnt < (U1)PICT_TIMID_MAX; u1_t_cnt++)
    {
        /* 待ち時間が初期値の場合は減算しない */
        if((bfg_Pict_TimMng[u1_t_cnt] != (U2)PICT_TIM_STOP) && (bfg_Pict_TimMng[u1_t_cnt] != (U2)PICT_TIM_TOUT))
        {
            bfg_Pict_TimMng[u1_t_cnt]--; /* 待ち時間減算        */
        }
    }

    /*----------------------------------------------------------------------*/
    /*  タイムアウト処理登録あり場合、実行する                              */
    /*----------------------------------------------------------------------*/
    for(u1_t_cnt = (U1)0U; u1_t_cnt < sizeof(tbl_Pict_TimInf) / sizeof(tbl_Pict_TimInf[0]); u1_t_cnt++)
    {
        if((bfg_Pict_TimMng[tbl_Pict_TimInf[u1_t_cnt].u1_timid] == (U2)PICT_TIM_TOUT) &&
            (tbl_Pict_TimInf[u1_t_cnt].func != NULL_PTR))
        {
            /* タイマ停止 */
            vd_s_PictCtl_ClrTim(tbl_Pict_TimInf[u1_t_cnt].u1_timid);

            /* タイムアウト処理実行 */
            tbl_Pict_TimInf[u1_t_cnt].func();
        }
    }
}

/*============================================================================
 * タイマ設定処理
 *----------------------------------------------------------------------------
 * モジュール名 : fc_PictCtl_SetTim
 * 機能         : タイマ設定処理
 * 処理内容     : 指定されたタイマIDのタイマ値を指定された時間に設定する
 * 入力（引数） : U1 byId  ：設定するタイマID
 *              : WORD wTim  ：設定するWAIT時間[ms単位]
 * 出力（戻値） : 無し
 * 制限事項     : WORD型のため、WAIT時間は65,535msまでの設定とする事
 * 作成者       : NOAH)施燕慧
 * ---------------------------------------------------------------------------
 * 変更履歴     : 2021.10.27 NOAH)施燕慧 新規作成
 *              : 
 ===========================================================================*/
static void vd_s_PictCtl_SetTim(U1 u1_a_Id, U2 u2_a_Tim)
{
    if(u1_a_Id < (U1)PICT_TIMID_MAX) {
        /* タイマ設定 */
        bfg_Pict_TimMng[u1_a_Id] = u2_a_Tim;
    }
}
/*============================================================================
 * タイマ取得処理
 *----------------------------------------------------------------------------
 * モジュール名 : u2_s_PictCtl_GetTim
 * 機能         : タイマ取得処理
 * 処理内容     : 指定されたタイマIDのタイマ値を取得する
 * 入力（引数） : U1 byId  ：設定するタイマID
 * 出力（戻値） : WORD wTim  ：設定するWAIT時間[ms単位]
 * 制限事項     :
 * 作成者       : NOAH)施燕慧
 * ---------------------------------------------------------------------------
 * 変更履歴     : 2021.10.27 NOAH)施燕慧 新規作成
 *              :
 ===========================================================================*/
static U2 u2_s_PictCtl_GetTim(U1 u1_a_Id)
{
    U2 u2_t_Tim;
    
    u2_t_Tim = (U2)PICT_TIM_STOP;

    if(u1_a_Id < (U1)PICT_TIMID_MAX) {
        /* タイマ取得 */
        u2_t_Tim = bfg_Pict_TimMng[u1_a_Id];
    }
    return(u2_t_Tim);
}

/*============================================================================
 * タイマクリア処理
 *----------------------------------------------------------------------------
 * モジュール名 : vd_s_PictCtl_ClrTim
 * 機能         : タイマクリア処理
 * 処理内容     : 指定されたタイマIDのタイマ値を停止に設定する
 * 入力（引数） : U1 byId  ：設定するタイマID
 * 出力（戻値） : 無し
 * 制限事項     :
 * 作成者       : NOAH)施燕慧
 * ---------------------------------------------------------------------------
 * 変更履歴     : 2021.10.27 NOAH)施燕慧 新規作成
 *              : 
 ===========================================================================*/
static void vd_s_PictCtl_ClrTim(U1 u1_a_Id)
{
    if(u1_a_Id < (U1)PICT_TIMID_MAX) {
        /* 通常タイマクリア */
        bfg_Pict_TimMng[u1_a_Id] = (U2)PICT_TIM_STOP;
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_PictCtl_StsMng(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PictCtl_StsMng(void)
{
    vd_s_PictCtl_MLIniChk();
    
    /* 見た目オン起動状態チェック(暫定) */
    vd_s_PictCtl_IgStsChk();
    
    vd_s_PictCtl_PollStsChk();
    
    vd_s_PictCtl_VmResetChk();
    
    vd_s_PictCtl_SiPErrChk();
    
    /* DCAMERA-CAP-STBY2状態チェック */
    vd_s_PictCtl_CamCapStby2StsChk();

    /* CAMERA-CAP-STBY状態チェック */
    vd_s_PictCtl_CamCapStbyStsChk();

    /* CAMERA-CAP-STBY3状態チェック */
    vd_s_PictCtl_CamCapStby3StsChk();

    /* DISP-REQ-GPIO0状態チェック */
    vd_s_PictCtl_DispReqGpio0StsChk();
    
    
    vd_s_PictCtl_PmsPsHoldstsChk();
    
    vd_s_PictCtl_VIcRstChk();
}

/*===================================================================================================================================*/
/*  static void vd_s_PictCtl_IgStsChk(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PictCtl_IgStsChk(void)
{
    U1 u1_t_stasts;
    U2 u2_t_time;
    U1 u1_t_vicrset;
    U4 u4_t_power_sts;
    
    u1_t_stasts = u1_g_Power_ModeState(); /* 見た目オン起動状態 */
    
    if((u1_t_stasts == (U1)POWER_MODE_STATE_APPON) &&
       (bfg_Pict_StsMng.u1_stasts != (U1)POWER_MODE_STATE_APPON)){
        u2_t_time = u2_s_PictCtl_GetTim((U1)PICT_TIMID_ML_CAMSYNC_CHKSTA);
        u1_t_vicrset = (U1)Dio_ReadChannel(PICT_PORT_V_IC_RST);
        if(((u2_t_time == (U2)PICT_TIM_STOP) &&
            (u1_s_pict_syncstarteflg == (U1)FALSE)) &&
            (u1_t_vicrset == (U1)TRUE)){
            /* カメラ同期検知開始待ちタイマ起動(1500+1ms) */
            vd_s_PictCtl_SetTim((U1)PICT_TIMID_ML_CAMSYNC_CHKSTA, (U2)PICT_TIMER_ML_CAMSYNC_CHKSTA_WAIT);
        }
        vd_s_PictCtl_SetTim((U1)PICT_TIMID_CAM_KIND_DISC_STA_WAIT, (U2)PICT_TIMER_CAM_KIND_DISC_STA);
        u1_s_pict_apponflg = (U1)TRUE;
        
    }
    if((u1_t_stasts != (U1)POWER_MODE_STATE_APPON) &&
       (bfg_Pict_StsMng.u1_stasts == (U1)POWER_MODE_STATE_APPON)){
        /* カメラシステム種別判別フラグOFF */
        bfg_Pict_StsMng.st_CamDisc.u1_CamKindDiscEn = (U1)FALSE;
        /* MIPI設定完了フラグOFF */
        bfg_Pict_StsMng.u1_MainMipiSetEndFlg = (U1)FALSE;
    }
    
    u4_t_power_sts = u4_g_VehopemdMdfield();
    if((u4_t_power_sts != (U4)PICT_VEHOPE_STS_POWERON) &&
       (u4_t_power_sts != (U4)PICT_VEHOPE_STS_POWERON_STOP)){
        u2_t_time = u2_s_PictCtl_GetTim((U1)PICT_TIMID_MAVTYPE_TIMEOUT);
        if(u2_t_time != (U2)PICT_TIM_STOP){
            vd_s_PictCtl_ClrTim((U1)PICT_TIMID_MAVTYPE_TIMEOUT);
        }
        u2_t_time = u2_s_PictCtl_GetTim((U1)PICT_TIMID_BCC1S05_TIMEOUT);
        if(u2_t_time != (U2)PICT_TIM_STOP){
            vd_s_PictCtl_ClrTim((U1)PICT_TIMID_BCC1S05_TIMEOUT);
        }
    }
    else{
        u2_t_time = u2_s_PictCtl_GetTim((U1)PICT_TIMID_MAVTYPE_TIMEOUT);
        if(u2_t_time == (U2)PICT_TIM_STOP){
            vd_s_PictCtl_SetTim((U1)PICT_TIMID_MAVTYPE_TIMEOUT, (U2)PICT_TIMER_MAVTYPE_TIMEOUT);
        }
        u2_t_time = u2_s_PictCtl_GetTim((U1)PICT_TIMID_BCC1S05_TIMEOUT);
        if(u2_t_time == (U2)PICT_TIM_STOP){
            vd_s_PictCtl_SetTim((U1)PICT_TIMID_BCC1S05_TIMEOUT, (U2)PICT_TIMER_BCC1S05_TIMEOUT);
        }
    }
    
    if((u4_t_power_sts == (U4)PICT_VEHOPE_STS_POWERON) &&
       (u4_s_pict_power_sts != (U4)PICT_VEHOPE_STS_POWERON)){
        vd_g_SysEcDrc_Drec((U1)SYSECDRC_DREC_CAT_CAMCTL, (U1)PICT_DRCID_POWERON, 0x00U, (U1)0x00U);
        vd_g_PictLogCtl_LogReq((U1)PICTLOGCTL_POINT_POWER_ON);
    }
    
    u4_s_pict_power_sts = u4_t_power_sts;
    bfg_Pict_StsMng.u1_stasts = u1_t_stasts;
}


/*===================================================================================================================================*/
/*  static void  vd_s_PictCtl_CamCapStbyStsChk(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void  vd_s_PictCtl_CamCapStbyStsChk(void)
{
    /* CAMERA-CAP-STBY状態変化かをチャック */
    if(bfg_Pict_StsMng.u1_CamCapStbyPreSts != bfg_Pict_StsMng.u1_CamCapStbySts) {
        /* 前回値更新 */
        bfg_Pict_StsMng.u1_CamCapStbyPreSts = bfg_Pict_StsMng.u1_CamCapStbySts;
        vd_s_PictCtl_MipiOutUpDate();
        vd_s_PictCtl_MainMipiSetEndStsUpDate();
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_PictCtl_CamPathUpDate(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PictCtl_MipiOutUpDate(void)
{
    if(bfg_Pict_StsMng.u1_CamCapStbySts == (U1)PICT_POLLPORT_ON){
        u1_s_pict_mipi_chg_flg |= (U1)PICT_MIPI_OUT_HS;
    }
    else{
        u1_s_pict_mipi_chg_flg |= (U1)PICT_MIPI_OUT_LP11;
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_PictCtl_MipiChg(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PictCtl_MipiChg(void)
{
    static const U1 u1_s_PICT_MASK_HS = (U1)(PICT_MIPI_OUT_LP11 | PICT_MIPI_OUT_VMRESET);

    U1 u1_t_sts;
    U1 u1_t_hs_flg;
    U1 u1_t_lp11_flg;
    U1 u1_t_chk_fact;
    U1 u1_t_chk_req;

    u1_t_sts = (U1)FALSE;
    u1_t_chk_req = (U1)PICT_MIPI_OUT_NON;
    u1_t_hs_flg = u1_s_pict_mipi_chg_flg & (U1)PICT_MIPI_OUT_HS;
    u1_t_lp11_flg = u1_s_pict_mipi_chg_flg & u1_s_PICT_MASK_HS;
 
    if(u1_t_hs_flg == (U1)PICT_MIPI_OUT_HS){
        u1_t_sts = u1_g_Pict_MlMipiSetOn();
        if(u1_t_sts == (U1)TRUE){
            u1_s_pict_mipi_chg_flg &= ~(U1)PICT_MIPI_OUT_HS;
            u1_t_chk_req = (U1)PICT_MIPI_OUT_HS;
        }
    }
    
    if(u1_t_lp11_flg != (U1)0U){
        u1_t_sts = u1_g_Pict_MlMipiSetOff();
        if(u1_t_sts == (U1)TRUE){
            u1_t_chk_fact = u1_s_pict_mipi_chg_flg & (U1)PICT_MIPI_OUT_LP11;
            if(u1_t_chk_fact == (U1)PICT_MIPI_OUT_LP11){
                u1_t_chk_req = (U1)PICT_MIPI_OUT_LP11;
            }
            u1_s_pict_mipi_chg_flg &= ~u1_s_PICT_MASK_HS;
        }
    }
    if((u1_s_pict_mipi_chg_flg == (U1)PICT_MIPI_OUT_NON) && (u1_t_chk_req != (U1)PICT_MIPI_OUT_NON)){
        if(((bfg_Pict_StsMng.u1_CamCapStbySts == (U1)PICT_POLLPORT_ON) &&
            (u1_t_chk_req == (U1)PICT_MIPI_OUT_LP11)) ||
            ((bfg_Pict_StsMng.u1_CamCapStbySts == (U1)PICT_POLLPORT_OFF) &&
            (u1_t_chk_req == (U1)PICT_MIPI_OUT_HS))){
            vd_s_PictCtl_MipiOutUpDate();
        }
    }
}

/*===================================================================================================================================*/
/*  static void  vd_s_PictCtl_CamCapStby2StsChk(void)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void  vd_s_PictCtl_CamCapStby2StsChk(void)
{
    /* CAMERA-CAP-STBY2状態変化かをチャック */
    if(bfg_Pict_StsMng.u1_CamCapStby2PreSts != bfg_Pict_StsMng.u1_CamCapStby2Sts) {
        /* 前回値更新 */
        bfg_Pict_StsMng.u1_CamCapStby2PreSts = bfg_Pict_StsMng.u1_CamCapStby2Sts;

        /* カメラ切替経路更新 */
        vd_s_PictCtl_CamPathUpDate();

        vd_s_PictCtl_MainMipiSetEndStsUpDate();
    }
}

/*===================================================================================================================================*/
/*  static void  vd_s_PictCtl_CamCapStby3StsChk(void)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void  vd_s_PictCtl_CamCapStby3StsChk(void)
{
    /* CAMERA-CAP-STBY3状態変化かをチャック */
    if(bfg_Pict_StsMng.u1_CamCapStby3PreSts != bfg_Pict_StsMng.u1_CamCapStby3Sts) {
        /* 前回値更新 */
        bfg_Pict_StsMng.u1_CamCapStby3PreSts = bfg_Pict_StsMng.u1_CamCapStby3Sts;
        vd_g_Gvif3RxStby3StsSet(bfg_Pict_StsMng.u1_CamCapStby3Sts);
    }
}

/*===================================================================================================================================*/
/*  static void  vd_s_PictCtl_DispReqGpio0StsChk(void)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void  vd_s_PictCtl_DispReqGpio0StsChk(void)
{
    /* 検知結果は見た目オン起動から使用可(暫定) */
    vd_s_PictCtl_DispReqGpio0AppChk();
    /* DISP-REQ-GPIO0状態変化かをチャック */
    if(bfg_Pict_StsMng.u1_DispReqGpio0PreSts != bfg_Pict_StsMng.u1_DispReqGpio0Sts) {
        /* カメラ切替更新 */
        vd_s_PictCtl_CamChgUpDate();
        vd_s_PictCtl_MmresetSndChk();
        /* 前回値更新 */
        bfg_Pict_StsMng.u1_DispReqGpio0PreSts = bfg_Pict_StsMng.u1_DispReqGpio0Sts;
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_PictCtl_CamPathUpDate(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PictCtl_CamPathUpDate(void)
{
    /* カメラバイパス経路中/カメラバイパス経路切替中 */
    if((bfg_Pict_StsMng.u1_CamChgSts == (U1)PICT_CAMCHG_STS_BPASS) || (bfg_Pict_StsMng.u1_CamChgSts == (U1)PICT_CAMCHG_STS_BPASS_GO))
    {
        /* /CAMERA-CAP-STBY2=Hの場合 */
        if(((bfg_Pict_StsMng.u1_CamCapStby2Sts == (U1)PICT_POLLPORT_ON) &&
            (u1_s_pict_siperrfailsafe_flg == (U1)PICT_SIP_ERR_OFF)) &&
            ((u1_s_pict_vmreset_bpass != (U1)PICT_VMRESET_BPASS) &&
            (u1_s_pict_vmreset_bpass != (U1)PICT_VMRESET_REQ))){
            u1_s_pict_campass_chg_flg |= (U1)PICT_CAM_PATH_NORM;
        }
        
        if((bfg_Pict_StsMng.u1_CamCapStby2Sts == (U1)PICT_POLLPORT_OFF) &&
           (u1_s_pict_vmreset_bpass != (U1)PICT_VMRESET_REQ)){
            u1_s_pict_vmreset_bpass = (U1)PICT_VMRESET_NON;
        }
    }
    /* カメラ通常経路/通常経路切替中 */
    else if((bfg_Pict_StsMng.u1_CamChgSts == (U1)PICT_CAMCHG_STS_NORMAL) || (bfg_Pict_StsMng.u1_CamChgSts == (U1)PICT_CAMCHG_STS_NORMAL_GO))
    {
        /* CAMERA-CAP-STBY2=Lかつ同期異常判定正常の場合 */
        if((bfg_Pict_StsMng.u1_CamCapStby2Sts == (U1)PICT_POLLPORT_OFF) && (bfg_Ml_Ctl.u1_SyncChkRlt == (U1)PICT_CAM_SYNC_CHK_OK)) {
            u1_s_pict_campass_chg_flg |= (U1)PICT_CAM_PATH_BPASS;
        }
    }
    else
    {
        /* do nothing */
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_PictCtl_CamPathChg(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PictCtl_CamPathChg(void)
{
    static const U1 u1_s_PICT_MASK_BPASS = (U1)(PICT_CAM_PATH_BPASS | PICT_CAM_PATH_SIPERR | PICT_CAM_PATH_CAMMODEFAIL | PICT_CAM_PATH_VMRESET);
    static const U1 u1_s_PICT_MASK_NORM = (U1)(PICT_CAM_PATH_NORM | PICT_CAM_PATH_FALSEPOSITIVE);
    
    U1 u1_t_sts;
    U1 u1_t_norm_flg;
    U1 u1_t_falsepos_flg;
    U1 u1_t_bpass_flg;
    U1 u1_t_camfail_flg;
    U1 u1_t_siperr_flg;
    U1 u1_t_vmreset_flg;
    U1 u1_t_chk_req;

    u1_t_sts = (U1)FALSE;
    u1_t_chk_req = (U1)FALSE;
    
    u1_t_norm_flg = u1_s_pict_campass_chg_flg & (U1)PICT_CAM_PATH_NORM;
    u1_t_falsepos_flg = u1_s_pict_campass_chg_flg & (U1)PICT_CAM_PATH_FALSEPOSITIVE;
    u1_t_bpass_flg = u1_s_pict_campass_chg_flg & (U1)PICT_CAM_PATH_BPASS;
    u1_t_camfail_flg = u1_s_pict_campass_chg_flg & (U1)PICT_CAM_PATH_CAMMODEFAIL;
    u1_t_siperr_flg = u1_s_pict_campass_chg_flg & (U1)PICT_CAM_PATH_SIPERR;
    u1_t_vmreset_flg = u1_s_pict_campass_chg_flg & (U1)PICT_CAM_PATH_VMRESET;

    if((u1_t_falsepos_flg == (U1)PICT_CAM_PATH_FALSEPOSITIVE) ||
       ((u1_t_norm_flg == (U1)PICT_CAM_PATH_NORM) && 
        (bfg_Pict_SeqMlMng.u1_SeqNo == (U1)PICT_SEQ_ML_IDLE))){
        st_sp_pict_path_req_sts.u1_normal = (U1)PICT_PATH_CHG;
        u1_s_pict_cammodelog_flg = (U1)TRUE;
    }
    
    if((((u1_t_camfail_flg == (U1)PICT_CAM_PATH_CAMMODEFAIL) ||
         (u1_t_siperr_flg == (U1)PICT_CAM_PATH_SIPERR))  ||
         (u1_t_vmreset_flg == (U1)PICT_CAM_PATH_VMRESET))  ||
       ((u1_t_bpass_flg == (U1)PICT_CAM_PATH_BPASS) && 
        (bfg_Pict_SeqMlMng.u1_SeqNo == (U1)PICT_SEQ_ML_IDLE))){
        st_sp_pict_path_req_sts.u1_bypass = (U1)PICT_PATH_CHG;
    }
    
    if(st_sp_pict_path_req_sts.u1_normal == (U1)PICT_PATH_CHG){
        /* カメラ通常経路切替要求設定 */
        u1_t_sts = u1_g_Pict_MlCamPathSetNml();
        if(u1_t_sts == (U1)TRUE){
            if(u1_t_norm_flg == (U1)PICT_CAM_PATH_NORM){
                vd_g_SysEcDrc_Drec((U1)SYSECDRC_DREC_CAT_CAMCTL, (U1)PICT_DRCID_BPASS_SET, (U1)PICT_DRCID_PATH_STBY2, (U1)PICT_DRCID_PATH_NORMAL);
            }
            if(u1_t_falsepos_flg == (U1)PICT_CAM_PATH_FALSEPOSITIVE){
                vd_g_SysEcDrc_Drec((U1)SYSECDRC_DREC_CAT_CAMCTL, (U1)PICT_DRCID_BPASS_SET, (U1)PICT_DRCID_PATH_SIPERR, (U1)PICT_DRCID_PATH_NORMAL);
            }
            
            vd_g_PictLogCtl_LogReq((U1)PICTLOGCTL_POINT_NORMAL);
            bfg_Pict_StsMng.u1_CamChgSts = (U1)PICT_CAMCHG_STS_NORMAL;
            u1_s_pict_campass_chg_flg &= ~u1_s_PICT_MASK_NORM;
            u1_t_chk_req = (U1)TRUE;
            st_sp_pict_path_req_sts.u1_normal = (U1)PICT_PATH_NOCHG;
        }
    }

    if(st_sp_pict_path_req_sts.u1_bypass == (U1)PICT_PATH_CHG){
        /* カメラバイパス経路切替要求設定 */
        u1_t_sts = u1_g_Pict_MlCamPathSetByp();
        if(u1_t_sts == (U1)TRUE){
            if(u1_t_bpass_flg == (U1)PICT_CAM_PATH_BPASS){
                vd_g_SysEcDrc_Drec((U1)SYSECDRC_DREC_CAT_CAMCTL, (U1)PICT_DRCID_BPASS_SET, (U1)PICT_DRCID_PATH_STBY2, (U1)PICT_DRCID_PATH_BPASS);
                bfg_Pict_StsMng.u1_CamChgSts = (U1)PICT_CAMCHG_STS_BPASS;
                u1_t_chk_req = (U1)TRUE;
            }
            if(u1_t_siperr_flg == (U1)PICT_CAM_PATH_SIPERR){
                vd_g_SysEcDrc_Drec((U1)SYSECDRC_DREC_CAT_CAMCTL, (U1)PICT_DRCID_BPASS_SET, (U1)PICT_DRCID_PATH_SIPERR, (U1)PICT_DRCID_PATH_BPASS);
                bfg_Pict_StsMng.u1_CamChgSts = (U1)PICT_CAMCHG_STS_BPASS;
                u1_s_pict_falsepositive_jdgreq = (U1)TRUE;
            }
            if((u1_t_camfail_flg == (U1)PICT_CAM_PATH_CAMMODEFAIL) &&
               (u1_s_pict_cammodelog_flg == (U1)TRUE)){
                vd_g_SysEcDrc_Drec((U1)SYSECDRC_DREC_CAT_CAMCTL, (U1)PICT_DRCID_BPASS_SET, (U1)PICT_DRCID_PATH_CAMFAIL, (U1)PICT_DRCID_PATH_BPASS);
                u1_s_pict_cammodelog_flg = (U1)FALSE;
            }
            if(u1_t_vmreset_flg == (U1)PICT_CAM_PATH_VMRESET){
                vd_g_SysEcDrc_Drec((U1)SYSECDRC_DREC_CAT_CAMCTL, (U1)PICT_DRCID_BPASS_SET, (U1)PICT_DRCID_PATH_VMRESET, (U1)PICT_DRCID_PATH_BPASS);
                bfg_Pict_StsMng.u1_CamChgSts = (U1)PICT_CAMCHG_STS_BPASS;
                u1_s_pict_vmreset_bpass = (U1)PICT_VMRESET_BPASS;
            }
            
            vd_g_PictLogCtl_LogReq((U1)PICTLOGCTL_POINT_BPASS);
            u1_s_pict_campass_chg_flg &= ~u1_s_PICT_MASK_BPASS;
            st_sp_pict_path_req_sts.u1_bypass = (U1)PICT_PATH_NOCHG;
        }
    }
    
    if((u1_s_pict_campass_chg_flg == (U1)PICT_CAM_PATH_NOCHG) && (u1_t_chk_req == (U1)TRUE)){
        vd_s_PictCtl_CamPathUpDate();
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_PictCtl_CamChgUpDate(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PictCtl_CamChgUpDate(void)
{
    /* DISP-REQ-GPIO0 = Hの場合 */
    if(bfg_Pict_StsMng.u1_DispReqGpio0Sts == (U1)PICT_POLLPORT_ON){
        vd_g_SysEcDrc_Drec((U1)SYSECDRC_DREC_CAT_CAMCTL, (U1)PICT_DRCID_GPIO0_EDG, (U1)PICT_DRCID_GPIO0_HI, (U1)0x00U);
        vd_g_PictLogCtl_LogReq((U1)PICTLOGCTL_POINT_GPIO0_HI);
        Dio_WriteChannel(PICT_PORT_CAMERA_MODE1, (Dio_LevelType)TRUE);
        /* カメラ切替制御 */
        if(bfg_Pict_StsMng.u1_DiagMode != (U1)PICT_DIAG_MOD_OFF){
            /* カメラダイアグモード⇔カメラモード間の遷移は顧客仕様にて禁止されている */
            /* MMダイアグ画面中DISP-REQ-GPIO0=Hiであっても、カメラモードに遷移しない */
            /* 何もしない */
        }
        else
        {
            if(((bfg_Pict_StsMng.u1_CamChgSts == (U1)PICT_CAMCHG_STS_OFF)
                ||(bfg_Pict_StsMng.u1_CamChgSts == (U1)PICT_CAMCHG_STS_OFF_GO))){
                /* 画質モード通知(カメラ以外)受信停止 */
                bfg_Pict_StsMng.u1_RcvNoCamQualModeFlg = (U1)PICT_RCV_NOCAMQUAL_STOP;
                /*  T_SIP_NOTIF_OUT待ちタイマ停止 */
                vd_s_PictCtl_ClrTim((U1)PICT_TIMID_ML_T_SIP_NOTIF_OUT);
                /* カメラへ切替シーケンス要求 */
                vd_s_PictCtl_SetMlSeqReq((U1)PICT_SEQ_ML_CAMONCHG);
            }
            else {
                ;/* 何もしない */
            }
        }
    /* DISP-REQ-GPIO0 = Lの場合 */
    } else {
        if(bfg_Pict_StsMng.u1_DispReqGpio0PreSts != (U1)PICT_POLLPORT_UNFIX){
            vd_g_SysEcDrc_Drec((U1)SYSECDRC_DREC_CAT_CAMCTL, (U1)PICT_DRCID_GPIO0_EDG, (U1)PICT_DRCID_GPIO0_LO, (U1)0x00U);
            vd_g_PictLogCtl_LogReq((U1)PICTLOGCTL_POINT_GPIO0_LO);
        }
        Dio_WriteChannel(PICT_PORT_CAMERA_MODE1, (Dio_LevelType)FALSE);

        /* カメラ切替制御 */
        if(bfg_Pict_StsMng.u1_DiagMode != (U1)PICT_DIAG_MOD_OFF){
            /* カメラダイアグモード⇔カメラモード間の遷移は顧客仕様にて禁止されている */
            /* MMダイアグ画面中DISP-REQ-GPIO0=Loであっても、カメラモード以外に遷移しない */
            ;/* 何もしない */
        }
        else
        {
            /* カメラ表示以外,カメラ表示以外の切替中の場合 */
            if( (bfg_Pict_StsMng.u1_CamChgSts == (U1)PICT_CAMCHG_STS_OFF)
                 ||(bfg_Pict_StsMng.u1_CamChgSts == (U1)PICT_CAMCHG_STS_OFF_GO) ) {

                /* カメラへの切替未実施で、カメラへ切替 シーケンスキャンセルで終了 */
                vd_s_PictCtl_CnclMlSeqReq((U1)PICT_SEQ_ML_CAMONCHG);
            }
            /* カメラ表示中の場合 */
            else{
                /* カメラON⇒カメラOFFの処理 */
                vd_s_PictCtl_CamChgOn2Off();
            }
        } 
    }
}
/*===================================================================================================================================*/
/*  static void vd_s_PictCtl_CamChgOn2Off(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PictCtl_CamChgOn2Off(void)
{
    /* カメラカメラ同期異常→正常シーケンスキャンセル処理 */
    if((bfg_Pict_SeqMlMng.u1_SeqNo == (U1)PICT_SEQ_ML_CAMSYNCOK)){
        vd_s_PictCtl_CnclMlSeqReq((U1)PICT_SEQ_ML_CAMSYNCOK);
        /* カメラカメラ同期異常→正常シーケンス未完了フラグ:ON*/
        bfg_Pict_StsMng.u1_CamSyncOKSeqRunFlg = (U1)TRUE;
    }

    /* カメラ以外へ切替シーケンス要求 */
    vd_s_PictCtl_SetMlSeqReq((U1)PICT_SEQ_ML_CAMOFFCHG);
}



/*============================================================================
 * カメラ以外へ切替種別設定
 *----------------------------------------------------------------------------
 * モジュール名 : fc_PictCtl_CamChgOffTypeSet
 * 機能         : カメラ以外へ切替種別設定処理
 * 処理内容     : カメラ以外へ切替種別設定処理
 * 入力（引数） : 無し
 * 出力（戻値） : 無し
 * 制限事項     : 無し
 * 作成者       : NOAH)王 巧燕
 * ---------------------------------------------------------------------------
 * 変更履歴     : 2023/04/14 新規作成
 *              : 
 ===========================================================================*/
static void vd_s_PictCtl_CamChgOffTypeSet(void)
{
    /* カメラ同期異常 or 異常→正常移行中の場合、カメラ以外へ切替種別：カメラ同期異常から */
    if((bfg_Ml_Ctl.u1_SyncChkRlt == (U1)PICT_CAM_SYNC_CHK_NG)||(bfg_Pict_StsMng.u1_CamSyncOKSeqRunFlg == (U1)TRUE)){
        bfg_Pict_StsMng.u1_CamChgOffType = (U1)PICT_CAMOFF_FORM_SYNCNG;
        bfg_Pict_StsMng.u1_CamSyncOKSeqRunFlg = (U1)FALSE;
    }
    /*  /CAMERA-CAP-STBY2 = Hiの場合、カメラ以外へ切替種別：カメラ通常から */
    else if(bfg_Pict_StsMng.u1_CamCapStby2Sts == (U1)PICT_POLLPORT_ON){
        bfg_Pict_StsMng.u1_CamChgOffType = (U1)PICT_CAMOFF_FORM_NORMAL;
    }
    /*  /CAMERA-CAP-STBY2 = Loの場合、カメラ以外へ切替種別：カメラバイパスから */
    else {
        bfg_Pict_StsMng.u1_CamChgOffType = (U1)PICT_CAMOFF_FORM_BPASS;
    }
}

/*============================================================================
 * メインマイコンのMIPI設定完了状態更新
 *----------------------------------------------------------------------------
 * モジュール名 : fc_PictCtl_MainMipiSetEndStsUpDate
 * 機能         : メインマイコンのMIPI設定完了状態更新処理
 * 処理内容     : メインマイコンのMIPI設定完了状態更新処理
 * 入力（引数） : 無し
 * 出力（戻値） : 無し
 * 制限事項     : 無し
 * 作成者       : NOAH)王 巧燕
 * ---------------------------------------------------------------------------
 * 変更履歴     : 2023/04/14 新規作成
 *              : 
 ===========================================================================*/
static void vd_s_PictCtl_MainMipiSetEndStsUpDate(void)
{
    /* 同一IG-ON中にメインマイコン起動後MIPI設定完了フラグ設定 */
    if((bfg_Pict_StsMng.u1_CamCapStbySts == (U1)PICT_POLLPORT_ON)
      &&(bfg_Pict_StsMng.u1_CamCapStby2Sts == (U1)PICT_POLLPORT_ON)) {
        bfg_Pict_StsMng.u1_MainMipiSetEndSts = (U1)TRUE;
        if(bfg_Pict_StsMng.u1_stasts == (U1)POWER_MODE_STATE_APPON) {
            bfg_Pict_StsMng.u1_MainMipiSetEndFlg = (U1)TRUE;
        }
    }
    else {
        bfg_Pict_StsMng.u1_MainMipiSetEndSts = (U1)FALSE;
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_PictCtl_MlSeqCamOnChg(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PictCtl_MlSeqCamOnChg(void)
{
    U1 u1_t_mode;
    U2 u2_t_time;
    U1 u1_t_sts;

    u1_t_mode = (U1)FALSE;
    u2_t_time = (U2)0U;
    u1_t_sts = (U1)FALSE;
    
    switch (bfg_Pict_SeqMlMng.u1_PrcNo)
    {
        case PICT_SEQ_ML_CAMON_STEP0:
            u1_s_pict_cammodelog_flg = (U1)TRUE;
            if(u1_s_pict_syncstarteflg == (U1)FALSE){
                /* カメラ同期検知開始処理 */
                vd_s_PictCtl_CamSyncChkSta();
            }

            if(bfg_Pict_StsMng.u1_CamCapStby2Sts == (U1)PICT_POLLPORT_ON)
            {
                /* カメラ通常経路切替中設定 */
                bfg_Pict_StsMng.u1_CamChgSts = (U1)PICT_CAMCHG_STS_NORMAL_GO;
                bfg_Pict_StsMng.u1_CamChgOnType = (U1)PICT_CAMON_TO_NORMAL;

                /* カメラへ切替時固着検知有効化設定待ち (min275ms) */
                vd_s_PictCtl_SetTim((U1)PICT_TIMID_ML_PRC_T1, (U2)PICT_TIMER_ML_CAMCHG_FIX_DET_WAIT);
                bfg_Pict_SeqMlMng.u1_PrcNo = (U1)PICT_SEQ_ML_CAMON_STEP2;
            }
            else
            {
                /* カメラバイパス経路切替中設定 */
                bfg_Pict_StsMng.u1_CamChgSts = (U1)PICT_CAMCHG_STS_BPASS_GO;
                bfg_Pict_StsMng.u1_CamChgOnType = (U1)PICT_CAMON_TO_BPASS;
                bfg_Pict_SeqMlMng.u1_PrcNo = (U1)PICT_SEQ_ML_CAMON_STEP1;
            }
            break;

        case PICT_SEQ_ML_CAMON_STEP1:
                /* I2C MUTE ON設定 */
            u1_t_sts = u1_g_Pict_MlI2cMuteSetOn();
            if(u1_t_sts == (U1)TRUE){
                vd_g_SysEcDrc_Drec((U1)SYSECDRC_DREC_CAT_CAMCTL, (U1)PICT_DRCID_MUTE, (U1)PICT_DRCID_MUTE_ALL, (U1)PICT_DRCID_MUTE_ON);
                vd_s_PictCtl_MutelogChk((U1)PICT_MUTEONREQ_ALLOFF);
                bfg_Pict_SeqMlMng.u1_PrcNo = (U1)PICT_SEQ_ML_CAMON_STEP2;
            }
            break;

        case PICT_SEQ_ML_CAMON_STEP2:
            /* カメラ経路切替処理 */
             /*カメラ同期確定待ち */
            if(bfg_Ml_Ctl.u1_SyncChkRlt != (U1)PICT_CAM_SYNC_CHK_UNJDG) {
                if(bfg_Ml_Ctl.u1_SyncChkRlt == (U1)PICT_CAM_SYNC_CHK_NG) {
                    /*---同期信号異常時---*/
                    /* 同期正常→異常への移行処理はここに実施するので、 */
                    /* 同期正常→異常への移行シーケンスをキャンセル */
                    vd_s_PictCtl_CnclMlSeqReq((U1)PICT_SEQ_ML_CAMSYNCNG);
                    bfg_Pict_SeqMlMng.u1_PrcNo = (U1)PICT_SEQ_ML_CAMON_STEP3;
                } else {
                    /*---同期信号正常時---*/
                    if(bfg_Pict_StsMng.u1_CamChgOnType == (U1)PICT_CAMON_TO_BPASS) {
                        /*---バイパス経路への切替--*/
                        bfg_Pict_SeqMlMng.u1_PrcNo = (U1)PICT_SEQ_ML_CAMON_STEP4;
                    }
                    else{
                        bfg_Pict_SeqMlMng.u1_PrcNo = (U1)PICT_SEQ_ML_CAMON_STEP5;
                    }
                }
            }
            break;

        case PICT_SEQ_ML_CAMON_STEP3:
            /* 同期異常時シーケンスのレジスタ書き換えを実施 */
            u1_t_sts = u1_s_PictCtl_MlSeqCamSyncNg();
            if(u1_t_sts == (U1)TRUE){
                /* MUTE解除までの待ち時間無し */
                vd_s_PictCtl_SetTim((U1)PICT_TIMID_ML_PRC_T2, (U2)PICT_TIM_TOUT);
                bfg_Pict_SeqMlMng.u1_PrcNo = (U1)PICT_SEQ_ML_CAMON_STEP5;
            }
            break;

        case PICT_SEQ_ML_CAMON_STEP4:
            /* カメラバイパス経路切替 */
            u1_t_sts = u1_g_Pict_MlCamPathSetByp();
            if(u1_t_sts == (U1)TRUE){
                /* カメラへ切替時MUTE解除処理待ち (min20ms) */
                vd_s_PictCtl_SetTim((U1)PICT_TIMID_ML_PRC_T2, (U2)PICT_TIMER_ML_CAMCHG_MUTE_OFF_WAIT);
                vd_g_SysEcDrc_Drec((U1)SYSECDRC_DREC_CAT_CAMCTL, (U1)PICT_DRCID_BPASS_SET, (U1)PICT_DRCID_PATH_CAMON, (U1)PICT_DRCID_PATH_BPASS);
                vd_g_PictLogCtl_LogReq((U1)PICTLOGCTL_POINT_BPASS);
                bfg_Pict_SeqMlMng.u1_PrcNo = (U1)PICT_SEQ_ML_CAMON_STEP5;
            }
            break;

        case PICT_SEQ_ML_CAMON_STEP5:
            /* MUTE解除処理、バイパス経路へ切替時のみ実施 */
            if(bfg_Pict_StsMng.u1_CamChgOnType == (U1)PICT_CAMON_TO_NORMAL){
                /* 何にもしない */
                bfg_Pict_SeqMlMng.u1_PrcNo = (U1)PICT_SEQ_ML_CAMON_STEP7;
            }
            else{
                
                u2_t_time = u2_s_PictCtl_GetTim((U1)PICT_TIMID_ML_PRC_T2);
                if(u2_t_time == (U2)PICT_TIM_TOUT) {
                    bfg_Pict_SeqMlMng.u1_PrcNo = (U1)PICT_SEQ_ML_CAMON_STEP6;
                }
            }
            break;

        case PICT_SEQ_ML_CAMON_STEP6:
            /* I2C MUTE OFF設定 */
            u1_t_sts = u1_g_Pict_MlI2cMuteSetOff();
            if(u1_t_sts == (U1)TRUE){
                vd_g_SysEcDrc_Drec((U1)SYSECDRC_DREC_CAT_CAMCTL, (U1)PICT_DRCID_MUTE, (U1)PICT_DRCID_MUTE_ALL, (U1)PICT_DRCID_MUTE_OFF);
                vd_s_PictCtl_MutelogChk((U1)PICT_MUTEOFFREQ_ALLOFF);
                if(bfg_Ml_Ctl.u1_SyncChkRlt == (U1)PICT_CAM_SYNC_CHK_NG){
                   /* カメラ切替のPM-V-MUTE制御実施トリガ */
                    vd_g_PictMute_CamMuteReq((U1)FALSE);
                    u1_s_pict_camoff_muteoff_flg = (U1)PICT_TOUT_MUTEOFF;
                    /* アイドルシーケンスへ遷移 */
                    vd_s_PictCtl_ClrMlSeqInf();
                }
                else{
                   /* カメラへ切替時固着検知有効化設定待ち (min25ms) */
                   vd_s_PictCtl_SetTim((U1)PICT_TIMID_ML_PRC_T1, (U2)PICT_TIMER_ML_CAMCHG_FIX_DET_WAIT2);
                   bfg_Pict_SeqMlMng.u1_PrcNo = (U1)PICT_SEQ_ML_CAMON_STEP7;
                }
            }
             break;

        case PICT_SEQ_ML_CAMON_STEP7:
            u2_t_time = u2_s_PictCtl_GetTim((U1)PICT_TIMID_ML_PRC_T1);
            if(u2_t_time == (U2)PICT_TIM_TOUT) {
                /* 固着有効化設定 */
                /* カメラモード中、或いはカメラ同期正常以外設定しない */
                u1_t_mode = u1_g_PictCtl_CamStsGet();
                if((u1_t_mode == (U1)TRUE) &&
                   (bfg_Ml_Ctl.u1_SyncChkRlt == (U1)PICT_CAM_SYNC_CHK_OK)){
                    bfg_Pict_SeqMlMng.u1_PrcNo = (U1)PICT_SEQ_ML_CAMON_STEP8;
                }
                else{
                    bfg_Pict_SeqMlMng.u1_PrcNo = (U1)PICT_SEQ_ML_CAMON_STEP9;
                }
            }
            break;

        case PICT_SEQ_ML_CAMON_STEP8:
            /* 固着検知有効化 */
            u1_t_sts = u1_g_Pict_MlFrzChgSetOn();
            if(u1_t_sts == (U1)TRUE){
                bfg_Pict_SeqMlMng.u1_PrcNo = (U1)PICT_SEQ_ML_CAMON_STEP9;
            }
            break;
        
        case PICT_SEQ_ML_CAMON_STEP9:
            /* カメラ切替状態更新 */
            if(bfg_Pict_StsMng.u1_CamChgOnType == (U1)PICT_CAMON_TO_NORMAL){
                /* カメラ通常経路中設定 */
                bfg_Pict_StsMng.u1_CamChgSts = (U1)PICT_CAMCHG_STS_NORMAL;
            }
            else {
               /* カメラバイパス経路中設定 */
                bfg_Pict_StsMng.u1_CamChgSts = (U1)PICT_CAMCHG_STS_BPASS;
            }     
            /* カメラ切替のPM-V-MUTE制御実施トリガ */
            vd_g_PictMute_CamMuteReq((U1)FALSE);
            u1_s_pict_camoff_muteoff_flg = (U1)PICT_TOUT_MUTEOFF;

            /* アイドルシーケンスへ遷移 */
            vd_s_PictCtl_ClrMlSeqInf();
            break;
            

        default:
            /* アイドルシーケンスへ遷移 */
            vd_s_PictCtl_ClrMlSeqInf();
            break;
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_PictCtl_MlSeqCamOffChg(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PictCtl_MlSeqCamOffChg(void)
{
    U2 u2_t_time;
    U1 u1_t_sts;

    u2_t_time = (U2)0U;
    u1_t_sts = (U1)FALSE;

    switch (bfg_Pict_SeqMlMng.u1_PrcNo)
    {
        case PICT_SEQ_ML_CAMOFF_STEP0:
            /* カメラ以外切替中状態設定 */
            bfg_Pict_StsMng.u1_CamChgSts = (U1)PICT_CAMCHG_STS_OFF_GO;

            /* カメラ以外へ切替種別設定 */
            vd_s_PictCtl_CamChgOffTypeSet();

            /* 画質モード通知(カメラ)受け取ったフラグOFFにする */
            bfg_Pict_StsMng.u1_RcvCamQualModeFlg = (U1)FALSE;

            /* T_SIP_NOTIF_OUT待ちタイマ起動(1850ms+1ms) */
            if(bfg_Pict_StsMng.u1_RcvQualModeFlg == (U1)TRUE){
                vd_s_PictCtl_SetTim((U1)PICT_TIMID_ML_T_SIP_NOTIF_OUT, (U2)PICT_TIMER_ML_T_SIP_NOTIF_OUT);
                /* 画質モード通知(カメラ以外)受信未確定 */
                bfg_Pict_StsMng.u1_RcvNoCamQualModeFlg = (U1)PICT_RCV_NOCAMQUAL_NONE;
            }
            
            /* カメラ同期異常から */
            if(bfg_Pict_StsMng.u1_CamChgOffType == (U1)PICT_CAMOFF_FORM_SYNCNG){
                /* カメラ以外へ切替時DISP-REQ-GPIO0=Lo検知からヒーコン部以外MUTE解除まで最大時間(Min375ms)設定 */
                vd_s_PictCtl_SetTim((U1)PICT_TIMID_ML_PRC_T1, (U2)PICT_TIMER_ML_CAMCHG_T_CAM_OUT2);

                /* FIX_DET_END待ちタイマ起動 (0ms) */
                vd_s_PictCtl_SetTim((U1)PICT_TIMID_ML_PRC_T2, (U2)PICT_TIM_TOUT);
                bfg_Pict_SeqMlMng.u1_PrcNo = (U1)PICT_SEQ_ML_CAMOFF_STEP2;
            }
            /* カメラ通常経路から */
            else if(bfg_Pict_StsMng.u1_CamChgOffType == (U1)PICT_CAMOFF_FORM_NORMAL){
                /* FIX_DET_END待ちタイマ起動 (min40ms) */
                vd_s_PictCtl_SetTim((U1)PICT_TIMID_ML_PRC_T2, (U2)PICT_TIMER_ML_CAMCHG_FIX_DET_END_WAIT);
                bfg_Pict_SeqMlMng.u1_PrcNo = (U1)PICT_SEQ_ML_CAMOFF_STEP2;
            }
            /* カメラバイパス経路から */
            else {
                /* カメラ以外へ切替時DISP-REQ-GPIO0=Lo検知からMUTE解除まで最大時間(Min375ms)設定 */
                vd_s_PictCtl_SetTim((U1)PICT_TIMID_ML_PRC_T1, (U2)PICT_TIMER_ML_CAMCHG_T_CAM_OUT);
                bfg_Pict_SeqMlMng.u1_PrcNo = (U1)PICT_SEQ_ML_CAMOFF_STEP1;
            }
            break;

        case PICT_SEQ_ML_CAMOFF_STEP1:
                /* I2C MUTE ON設定 */
            u1_t_sts = u1_g_Pict_MlI2cMuteSetOn();
            if(u1_t_sts == (U1)TRUE){
                vd_g_SysEcDrc_Drec((U1)SYSECDRC_DREC_CAT_CAMCTL, (U1)PICT_DRCID_MUTE, (U1)PICT_DRCID_MUTE_ALL, (U1)PICT_DRCID_MUTE_ON);
                vd_s_PictCtl_MutelogChk((U1)PICT_MUTEONREQ_ALLOFF);
                /* FIX_DET_END待ちタイマ起動 (min40ms) */
                vd_s_PictCtl_SetTim((U1)PICT_TIMID_ML_PRC_T2, (U2)PICT_TIMER_ML_CAMCHG_FIX_DET_END_WAIT);
                bfg_Pict_SeqMlMng.u1_PrcNo = (U1)PICT_SEQ_ML_CAMOFF_STEP2;
            }
            break;

        case PICT_SEQ_ML_CAMOFF_STEP2:
            /* FIX_DET_END待ち */
            u2_t_time = u2_s_PictCtl_GetTim((U1)PICT_TIMID_ML_PRC_T2);
            if(u2_t_time == (U2)PICT_TIM_TOUT) {
                /* 画質モード通知受信済みの場合、T_SIP_NOTIF_OUTタイムアウト/停止 OR カメラ以外の画質モード通知を待ち */
                /* 画質モード通知未受信の場合、T_SIP_NOTIF_OUTタイムアウト/停止 OR カメラ以外の画質モード通知を待たない */
                if((bfg_Pict_StsMng.u1_RcvNoCamQualModeFlg != (U1)PICT_RCV_NOCAMQUAL_NONE) ||
                    (bfg_Pict_StsMng.u1_RcvQualModeFlg == (U1)FALSE)) {
                    /* T_SIP_NOTIF_OUTタイムアウトの場合、 MUTE制御投入 */
                    if(bfg_Pict_StsMng.u1_RcvNoCamQualModeFlg == (U1)PICT_RCV_NOCAMQUAL_TOUT) {
                        /* メインマイコン異常でのPM-V-MUTE制御実施トリガ */
                        vd_g_PictMute_CamMuteReq((U1)TRUE);
                        u1_s_pict_camoff_muteoff_flg = (U1)PICT_TOUT_MUTEON;
                    }
                    bfg_Pict_SeqMlMng.u1_PrcNo = (U1)PICT_SEQ_ML_CAMOFF_STEP3;
                }
            }
            break;

        case PICT_SEQ_ML_CAMOFF_STEP3:
            /* 固着検知無効化 */
            u1_t_sts = u1_g_Pict_MlFrzChgSetOff();
            if(u1_t_sts == (U1)TRUE){
                bfg_Pict_SeqMlMng.u1_PrcNo = (U1)PICT_SEQ_ML_CAMOFF_STEP4;
            }
            break;

        case PICT_SEQ_ML_CAMOFF_STEP4:
            /* カメラ通常経路切替 */
            u1_t_sts = u1_g_Pict_MlCamPathSetNml();
            if(u1_t_sts == (U1)TRUE){
                vd_g_SysEcDrc_Drec((U1)SYSECDRC_DREC_CAT_CAMCTL, (U1)PICT_DRCID_BPASS_SET, (U1)PICT_DRCID_PATH_CAMOFF, (U1)PICT_DRCID_PATH_NORMAL);
                vd_g_PictLogCtl_LogReq((U1)PICTLOGCTL_POINT_NORMAL);
                bfg_Pict_SeqMlMng.u1_PrcNo = (U1)PICT_SEQ_ML_CAMOFF_STEP5;
            }
            break;

        case PICT_SEQ_ML_CAMOFF_STEP5:
        /* カメラ同期異常から */
            if(bfg_Pict_StsMng.u1_CamChgOffType == (U1)PICT_CAMOFF_FORM_SYNCNG){
                u2_t_time = u2_s_PictCtl_GetTim((U1)PICT_TIMID_ML_PRC_T1);
                if(u2_t_time == (U2)PICT_TIM_TOUT) {
                    bfg_Pict_SeqMlMng.u1_PrcNo = (U1)PICT_SEQ_ML_CAMOFF_STEP6;
                }
            }
            /* カメラ通常経路から */
            else if(bfg_Pict_StsMng.u1_CamChgOffType == (U1)PICT_CAMOFF_FORM_NORMAL){
                if(u1_s_pict_camoff_muteoff_flg == (U1)PICT_TOUT_MUTEON){
                    vd_g_SysEcDrc_Drec((U1)SYSECDRC_DREC_CAT_CAMCTL, (U1)PICT_DRCID_T_SIP_NOTIF_OUT, (U1)PICT_DRCID_TOUT_NORMAL, (U1)0x00U);
                    u1_s_pict_camoff_muteoff_flg = (U1)PICT_TOUT_MUTEOFF_WAIT;
                }
                /* カメラ以外状態設定 */
                bfg_Pict_StsMng.u1_CamChgSts = (U1)PICT_CAMCHG_STS_OFF;

                /* アイドルシーケンスへ遷移 */
                vd_s_PictCtl_ClrMlSeqInf();
            }
            /* カメラバイパス経路から */
            else {
                if(u1_s_pict_camoff_muteoff_flg == (U1)PICT_TOUT_MUTEON) {
                    bfg_Pict_SeqMlMng.u1_PrcNo = (U1)PICT_SEQ_ML_CAMOFF_STEP7;
                } else {
                    bfg_Pict_SeqMlMng.u1_PrcNo = (U1)PICT_SEQ_ML_CAMOFF_STEP8;
                }
            }
            break;

        case PICT_SEQ_ML_CAMOFF_STEP6:
            /* 映像IC ヒーコン部以外のMUTE OFF */
            u1_t_sts = u1_g_Pict_MlNoAisMuteSetOff();
            if(u1_t_sts == (U1)TRUE){
                vd_g_SysEcDrc_Drec((U1)SYSECDRC_DREC_CAT_CAMCTL, (U1)PICT_DRCID_MUTE, (U1)PICT_DRCID_MUTE_NOAIS, (U1)PICT_DRCID_MUTE_OFF);
                vd_s_PictCtl_MutelogChk((U1)PICT_MUTEOFFREQ_NOAIS);
                if(u1_s_pict_camoff_muteoff_flg == (U1)PICT_TOUT_MUTEON){
                    vd_g_SysEcDrc_Drec((U1)SYSECDRC_DREC_CAT_CAMCTL, (U1)PICT_DRCID_T_SIP_NOTIF_OUT, (U1)PICT_DRCID_TOUT_SYNCNG, (U1)0x00U);
                    u1_s_pict_camoff_muteoff_flg = (U1)PICT_TOUT_MUTEOFF_WAIT;
                }
                /* カメラ以外状態設定 */
                bfg_Pict_StsMng.u1_CamChgSts = (U1)PICT_CAMCHG_STS_OFF;
                /* アイドルシーケンスへ遷移 */
                vd_s_PictCtl_ClrMlSeqInf();
            }
            break;

        case PICT_SEQ_ML_CAMOFF_STEP7:
                /* I2C MUTE OFF設定 */
            u1_t_sts = u1_g_Pict_MlI2cMuteSetOff();
            if(u1_t_sts == (U1)TRUE){
                vd_g_SysEcDrc_Drec((U1)SYSECDRC_DREC_CAT_CAMCTL, (U1)PICT_DRCID_MUTE, (U1)PICT_DRCID_MUTE_ALL, (U1)PICT_DRCID_MUTE_OFF);
                vd_s_PictCtl_MutelogChk((U1)PICT_MUTEOFFREQ_ALLOFF);
                vd_g_SysEcDrc_Drec((U1)SYSECDRC_DREC_CAT_CAMCTL, (U1)PICT_DRCID_T_SIP_NOTIF_OUT, (U1)PICT_DRCID_TOUT_BPASS, (U1)0x00U);
                u1_s_pict_camoff_muteoff_flg = (U1)PICT_TOUT_MUTEOFF_WAIT;
                bfg_Pict_StsMng.u1_CamChgSts = (U1)PICT_CAMCHG_STS_OFF;
                /* アイドルシーケンスへ遷移 */
                vd_s_PictCtl_ClrMlSeqInf();
            }
            break;

        case PICT_SEQ_ML_CAMOFF_STEP8:
            /* カメラ以外へ切替時DISP-REQ-GPIO0=Lo検知からMUTE解除まで最大時間経過 */
            u2_t_time = u2_s_PictCtl_GetTim((U1)PICT_TIMID_ML_PRC_T1);
            if(u2_t_time == (U2)PICT_TIM_TOUT) {
                bfg_Pict_SeqMlMng.u1_PrcNo = (U1)PICT_SEQ_ML_CAMOFF_STEP9;
            }
            break;

        case PICT_SEQ_ML_CAMOFF_STEP9:
                /* I2C MUTE OFF設定 */
            u1_t_sts = u1_g_Pict_MlI2cMuteSetOff();
            if(u1_t_sts == (U1)TRUE){
                vd_g_SysEcDrc_Drec((U1)SYSECDRC_DREC_CAT_CAMCTL, (U1)PICT_DRCID_MUTE, (U1)PICT_DRCID_MUTE_ALL, (U1)PICT_DRCID_MUTE_OFF);
                vd_s_PictCtl_MutelogChk((U1)PICT_MUTEOFFREQ_ALLOFF);
                /* カメラ以外状態設定 */
                bfg_Pict_StsMng.u1_CamChgSts = (U1)PICT_CAMCHG_STS_OFF;
                /* アイドルシーケンスへ遷移 */
                vd_s_PictCtl_ClrMlSeqInf();
            }
            break;

        default:
            /* アイドルシーケンスへ遷移 */
            vd_s_PictCtl_ClrMlSeqInf();
            break;
    }
}

/*===================================================================================================================================*/
/*  static void    vd_s_PictCtl_CamOffMuteOff(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PictCtl_CamOffMuteOff(void)
{
    if((u1_s_pict_camoff_muteoff_flg == (U1)PICT_TOUT_MUTEOFF_WAIT) &&
       (bfg_Pict_StsMng.u1_RcvNoCamQualModeFlg == (U1)PICT_RCV_NOCAMQUAL_END)){
         /* PM-V-MUTE制御実施トリガ */
         vd_g_PictMute_CamMuteReq((U1)FALSE);
         u1_s_pict_camoff_muteoff_flg = (U1)PICT_TOUT_MUTEOFF;
        }
}


/*===================================================================================================================================*/
/*  static U1 u1_s_PictCtl_MlSeqCamSyncNg(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_PictCtl_MlSeqCamSyncNg(void)
{
    U1 u1_t_sts;
    U1 u1_t_return;

    u1_t_sts = (U1)0;
    u1_t_return = (U1)FALSE;

    switch (u1_s_pict_camsyncng_step)
    {
        case PICT_SEQ_CAMONSYNCNG_STEP0:
            /* 固着検知の無効化設定 */
            u1_t_sts = u1_g_Pict_MlFrzChgSetOff();
            if(u1_t_sts == (U1)TRUE){
                u1_s_pict_camsyncng_step = (U1)PICT_SEQ_CAMONSYNCNG_STEP1;
            }
            break;

        case PICT_SEQ_CAMONSYNCNG_STEP1:
            /* カメラ通常経路切替 */
            u1_t_sts = u1_g_Pict_MlCamPathSetNml();
            if(u1_t_sts == (U1)TRUE){
                bfg_Pict_StsMng.u1_CamChgSts = (U1)PICT_CAMCHG_STS_NORMAL;
                vd_g_SysEcDrc_Drec((U1)SYSECDRC_DREC_CAT_CAMCTL, (U1)PICT_DRCID_BPASS_SET, (U1)PICT_DRCID_PATH_SYNCNG, (U1)PICT_DRCID_PATH_NORMAL);
                vd_g_PictLogCtl_LogReq((U1)PICTLOGCTL_POINT_NORMAL);
                u1_s_pict_camsyncng_step = (U1)PICT_SEQ_CAMONSYNCNG_STEP2;
            }
            break;

        case PICT_SEQ_CAMONSYNCNG_STEP2:
            u1_t_sts = u1_g_Pict_MlNoAisMuteSetOn();
            if(u1_t_sts == (U1)TRUE){
                vd_g_SysEcDrc_Drec((U1)SYSECDRC_DREC_CAT_CAMCTL, (U1)PICT_DRCID_MUTE, (U1)PICT_DRCID_MUTE_NOAIS, (U1)PICT_DRCID_MUTE_ON);
                vd_s_PictCtl_MutelogChk((U1)PICT_MUTEONREQ_NOAIS);
                u1_s_pict_camsyncng_step = (U1)PICT_SEQ_CAMONSYNCNG_STEP0;
                u1_t_return = (U1)TRUE;
            }
            break;

        default:
            u1_s_pict_camsyncng_step = (U1)PICT_SEQ_CAMONSYNCNG_STEP0;
            break;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static void vd_s_PictCtl_MlSeqCamSyncNg(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PictCtl_MlSeqCamSyncNg(void)
{
    U1 u1_t_sts;

    u1_t_sts = (U1)0;

    switch (bfg_Pict_SeqMlMng.u1_PrcNo)
    {
        case PICT_SEQ_ML_CAMSYNCNG_STEP0:
            u1_t_sts = u1_s_PictCtl_MlSeqCamSyncNg();
            if(u1_t_sts == (U1)TRUE){
                /* アイドルシーケンスへ遷移 */
                vd_s_PictCtl_ClrMlSeqInf();
            }
            break;

        default:
            /* アイドルシーケンスへ遷移 */
            vd_s_PictCtl_ClrMlSeqInf();
            break;
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_PictCtl_MlSeqCamSyncOk(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PictCtl_MlSeqCamSyncOk(void)
{
    U2 u2_t_time;
    U1 u1_t_sts;

    u2_t_time = (U2)0;
    u1_t_sts = (U1)0;

    switch (bfg_Pict_SeqMlMng.u1_PrcNo)
    {
        case PICT_SEQ_ML_CAMSYNCOK_STEP0:
            /* 「異常→正常判定へ移行」後、メインマイコンMIPI設定の待ち最大時間タイマ起動(max250ms) */
            vd_s_PictCtl_SetTim((U1)PICT_TIMID_ML_PRC_T1, (U2)PICT_TIMER_ML_AISMUTE_OFF_WAIT_T2);
            bfg_Pict_SeqMlMng.u1_PrcNo = (U1)PICT_SEQ_ML_CAMSYNCOK_STEP1;
            break;

        case PICT_SEQ_ML_CAMSYNCOK_STEP1:
            /* T_SYNC_LP周期待ちタイマ取得 */
            u2_t_time = u2_s_PictCtl_GetTim((U1)PICT_TIMID_ML_PRC_T2);
            if((u2_t_time == (U2)PICT_TIM_STOP) || (u2_t_time == (U2)PICT_TIM_TOUT)) {
                /* MIPI設定完了(/CAMERA-CAP-STBY 及び /CAMERA-CAP-STBY2共にHi状態)判断 */
                if(bfg_Pict_StsMng.u1_MainMipiSetEndSts == (U1)TRUE) {
                    /* メインマイコンMIPI設定の待ち最大時間のタイマ停止 */
                    vd_s_PictCtl_ClrTim((U1)PICT_TIMID_ML_PRC_T1);
                    /* ヒーコン部以外MUTE解除待ち (min100ms) */
                    vd_s_PictCtl_SetTim((U1)PICT_TIMID_ML_PRC_T2, (U2)PICT_TIMER_ML_AISMUTE_OFF_WAIT_T0);
                    bfg_Pict_SeqMlMng.u1_PrcNo = (U1)PICT_SEQ_ML_CAMSYNCOK_STEP3;
                }
                else{
                    /* 同一IG-ON中にメインマイコン起動後一度もMIPI設定完了になってない？ */
                    u2_t_time = u2_s_PictCtl_GetTim((U1)PICT_TIMID_ML_PRC_T1);
                    if((bfg_Pict_StsMng.u1_MainMipiSetEndFlg == (U1)FALSE) || (u2_t_time == (U2)PICT_TIM_TOUT)){
                        /* メインマイコンMIPI設定の待ち最大時間のタイマ停止 */
                        vd_s_PictCtl_ClrTim((U1)PICT_TIMID_ML_PRC_T1);
                        bfg_Pict_SeqMlMng.u1_PrcNo = (U1)PICT_SEQ_ML_CAMSYNCOK_STEP2;
                    } else {
                        /* ヒーコン部以外MUTE解除待ち (typ5ms) */
                        vd_s_PictCtl_SetTim((U1)PICT_TIMID_ML_PRC_T2, (U2)PICT_TIMER_ML_T_SYNC_LP_WAIT);
                    }
                }
             }
            break;

        case PICT_SEQ_ML_CAMSYNCOK_STEP2:
            /* カメラバイパス経路切替 */
            u1_t_sts = u1_g_Pict_MlCamPathSetByp();
            if(u1_t_sts == (U1)TRUE){
                bfg_Pict_StsMng.u1_CamChgSts = (U1)PICT_CAMCHG_STS_BPASS;
                vd_g_SysEcDrc_Drec((U1)SYSECDRC_DREC_CAT_CAMCTL, (U1)PICT_DRCID_BPASS_SET, (U1)PICT_DRCID_PATH_SYNCOK, (U1)PICT_DRCID_PATH_BPASS);
                vd_g_PictLogCtl_LogReq((U1)PICTLOGCTL_POINT_BPASS);
                /* ヒーコン部以外MUTE解除待ち (min50ms) */
                vd_s_PictCtl_SetTim((U1)PICT_TIMID_ML_PRC_T2, (U2)PICT_TIMER_ML_AISMUTE_OFF_WAIT_T1);
                bfg_Pict_SeqMlMng.u1_PrcNo = (U1)PICT_SEQ_ML_CAMSYNCOK_STEP3;
            }
            break;

        case PICT_SEQ_ML_CAMSYNCOK_STEP3:
            u2_t_time = u2_s_PictCtl_GetTim((U1)PICT_TIMID_ML_PRC_T2);
            if(u2_t_time == (U2)PICT_TIM_TOUT) {
                bfg_Pict_SeqMlMng.u1_PrcNo = (U1)PICT_SEQ_ML_CAMSYNCOK_STEP4;
            }
            break;

        case PICT_SEQ_ML_CAMSYNCOK_STEP4:
                /* 映像IC ヒーコン部以外のMUTE OFF */
            u1_t_sts = u1_g_Pict_MlNoAisMuteSetOff();
            if(u1_t_sts == (U1)TRUE){
                vd_g_SysEcDrc_Drec((U1)SYSECDRC_DREC_CAT_CAMCTL, (U1)PICT_DRCID_MUTE, (U1)PICT_DRCID_MUTE_NOAIS, (U1)PICT_DRCID_MUTE_OFF);
                vd_s_PictCtl_MutelogChk((U1)PICT_MUTEOFFREQ_NOAIS);
                bfg_Pict_SeqMlMng.u1_PrcNo = (U1)PICT_SEQ_ML_CAMSYNCOK_STEP5;
            }
            break;

        case PICT_SEQ_ML_CAMSYNCOK_STEP5:
                /* 固着検知有効化 */
            u1_t_sts = u1_g_Pict_MlFrzChgSetOn();
            if(u1_t_sts == (U1)TRUE){
                /* アイドルシーケンスへ遷移 */
                vd_s_PictCtl_ClrMlSeqInf();
            }
            break;

        default:
            /* アイドルシーケンスへ遷移 */
            vd_s_PictCtl_ClrMlSeqInf();
            break;
    }
}

/*============================================================================
 * MLアイドルシーケンス
 *----------------------------------------------------------------------------
 * モジュール名 : fc_PictCtl_MlSeqIdle
 * 機能         : MLアイドルシーケンス
 * 処理内容     : ML待ちに使用する
 * 入力(引数)   : 無し
 * 出力(戻値)   : 無し
 * 制限事項     : 無し
 * 作成者       : NOAH)馬
 * ---------------------------------------------------------------------------
 * 変更履歴     : 2022.11.10 NOAH)馬      新規作成
 *              :       
 ===========================================================================*/
static void vd_s_PictCtl_MlSeqIdle(void)
{
    /* 何もしない */
}

/*============================================================================
* ポーリング状態初期化処理
*----------------------------------------------------------------------------
* モジュール名  : fc_PictCtl_PollStsInit
* 機能          : ポーリング状態初期化処理
* 処理内容      : ポーリング状態初期化処理
* 入力(引数)    : BYTE byPort : ポート番号
* 出力(戻値)    : なし
* 制限事項      :
* 作成者        : NOAH)馬孝康
* ---------------------------------------------------------------------------
* 変更履歴      : 2022.05.04 新規作成
* 変更者        : 
===========================================================================*/
static void vd_s_PictCtl_PollStsInit(U1 u1_a_PortNo)
{
    /*----------------------------------------------------------------------*/
    /*  パラメータチェック                                                  */
    /*----------------------------------------------------------------------*/
    if(u1_a_PortNo < (U1)PICT_POLLNO_MAX)
    {
    /*----------------------------------------------------------------------*/
    /*  バッファ初期化                                                      */
    /*----------------------------------------------------------------------*/
        bfg_Pict_PollSts[u1_a_PortNo].u1_PortCnfSts = (U1)PICT_POLLPORT_NONDECI;
        bfg_Pict_PollSts[u1_a_PortNo].u1_PortPreSts = (U1)PICT_POLLPORT_NONDECI;
        bfg_Pict_PollSts[u1_a_PortNo].u2_PollStartWaitTimCnt = (U2)PICT_POLLPORT_CNTINIT;
        bfg_Pict_PollSts[u1_a_PortNo].u1_PollCycTimCnt = (U2)PICT_POLLPORT_CNTINIT;
        bfg_Pict_PollSts[u1_a_PortNo].u1_PollSameCnt = (U2)PICT_POLLPORT_CNTINIT;
        bfg_Pict_PollSts[u1_a_PortNo].u1_PollSts = (U1)PICT_POLLSTS_STOP;
    }
}

/*============================================================================
 * ポートポーリング開始チェック処理
 *----------------------------------------------------------------------------
 * モジュール名 : fc_PictCtl_PollStartChk
 * 機能         : ポートポーリング開始チェック処理
 * 処理内容     : ポートポーリング開始チェックを行う
 * 入力(引数)   : なし
 * 出力(戻値)   : BYTE byStartChkFlg:ポーリング開始チェック待ちフラグ
 * 制限事項     :
 * 作成者       : NOAH)馬孝康
 * ---------------------------------------------------------------------------
 * 変更履歴     : 2022.05.05  新規作成
 * 変更者       : 
 ===========================================================================*/
static U1 u1_s_PictCtl_PollStartChk(void)
{
    U1 u1_t_PollNo;
    U1 u1_t_StartChkFlg;
    
    u1_t_StartChkFlg = (U1)FALSE;

    /* ポーリング制御状態を判断 */
    for (u1_t_PollNo = (U1)0U; u1_t_PollNo < PICT_POLLNO_MAX; u1_t_PollNo++) {
        /* ポーリング開始待ち 中 */
        if(bfg_Pict_PollSts[u1_t_PollNo].u1_PollSts == (U1)PICT_POLLSTS_START_WAIT) {
            /* ポーリング開始待ち時間になっていない時、検知時間減算 */
            if(bfg_Pict_PollSts[u1_t_PollNo].u2_PollStartWaitTimCnt > (U2)0U) {
                bfg_Pict_PollSts[u1_t_PollNo].u2_PollStartWaitTimCnt--;
            }
            
            /* ポーリング開始待ち時間に達してる */
            if(bfg_Pict_PollSts[u1_t_PollNo].u2_PollStartWaitTimCnt <= (U2)0U) {
                /* ポーリング状態初期化処理 */
                vd_s_PictCtl_PollStsInit((U1)u1_t_PollNo);

                /* ポーリング定期処理に変更 */
                bfg_Pict_PollSts[u1_t_PollNo].u1_PollSts = (U1)PICT_POLLSTS_CYC;

                /* 定周期タイムカウント設定 */
                bfg_Pict_PollSts[u1_t_PollNo].u1_PollCycTimCnt = tb_Pict_PollMng[u1_t_PollNo].u1_CycTim;
            }
            else {
                /* 次回のポーリング開始待ちチェックが必要 */
                u1_t_StartChkFlg = (U1)TRUE;
            }
        }
    }

    /* 関数終了 */
    return(u1_t_StartChkFlg);
}

/*============================================================================
 * ポーリング管理機能開始処理
 *----------------------------------------------------------------------------
 * モジュール名 : fc_PictCtl_PollMngStart
 * 機能         : ポーリング管理機能開始処理
 * 処理内容     : ポーリング管理機能開始処理
 * 入力(引数)   : BYTE u1_CtlTrg : 制御トリガー
 * 出力(戻値)   : なし
 * 制限事項     :
 * 作成者       : NOAH)馬孝康
 * ---------------------------------------------------------------------------
 * 変更履歴     : 2022.05.04 新規作成
 * 変更者       :
 ===========================================================================*/
static void vd_s_PictCtl_PollMngStart(U1 u1_a_CtlTrg)
{
    U1 u1_t_PollNo;
    U1 u1_t_CtlTrg;

    /* 制御トリガーを判断 */
    for (u1_t_PollNo = (U1)0U; u1_t_PollNo < PICT_POLLNO_MAX; u1_t_PollNo++)
    {
        u1_t_CtlTrg = u1_a_CtlTrg & tb_Pict_PollMng[u1_t_PollNo].u1_CtlTrg;
        if(u1_t_CtlTrg != (U1)0U){
            /* ポーリング開始待ち */
            bfg_Pict_PollSts[u1_t_PollNo].u1_PollSts = (U1)PICT_POLLSTS_START_WAIT;
            /* ポーリングカウンタ */
            bfg_Pict_PollSts[u1_t_PollNo].u2_PollStartWaitTimCnt = tb_Pict_PollMng[u1_t_PollNo].u2_StartWaitTim;
            /* ポーリング開始待ちチェックフラグON */
            u1_s_pict_pollstartfhkflg = (U1)TRUE;
        }
    }
}

/*============================================================================
 * ポーリング管理機能停止処理
 *----------------------------------------------------------------------------
 * モジュール名 : fc_PictCtl_PollMngStop
 * 機能         : ポーリング停止処理
 * 処理内容     : ポーリング停止処理
 * 入力(引数)   : BYTE byTrgFlg : 停止要因(トリガータイプ)
 * 出力(戻値)   : なし
 * 制限事項     :
 * 作成者       : 2022.05.04 NOAH)馬孝康
 * ---------------------------------------------------------------------------
 * 変更履歴     : 2022.05.04 新規作成
 * 変更者       : 
 ===========================================================================*/
static void vd_s_PictCtl_PollMngStop(U1 u1_a_TrgFlg)
{
    U1 u1_t_PollNo;
    U1 u1_t_CtlTrg;

    /*------------------------------------------------------------------*/
    /* ポートポーリング停止チェック */
    /*------------------------------------------------------------------*/
    for (u1_t_PollNo = (U1)0U; u1_t_PollNo < (U1)PICT_POLLNO_MAX; u1_t_PollNo++)
    {
        /* 動作中で且つ停止タイミング */
        u1_t_CtlTrg = tb_Pict_PollMng[u1_t_PollNo].u1_CtlTrg & u1_a_TrgFlg;
        if((bfg_Pict_PollSts[u1_t_PollNo].u1_PollSts != (U1)PICT_POLLSTS_STOP) &&
            (u1_t_CtlTrg != (U1)0U))
        {
            /* ポーリング状態初期化処理 */
            vd_s_PictCtl_PollStsInit(u1_t_PollNo);

        }
    }
}
/*===================================================================================================================================*/
/*  static void vd_s_PictCtl_PollMng(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PictCtl_PollMng(void)
{
    
    /* ポーリング開始待ちチェック必要判断 */
    if(u1_s_pict_pollstartfhkflg == (U1)TRUE) {
        /* ポートポーリング開始チェック処理 */
        u1_s_pict_pollstartfhkflg = u1_s_PictCtl_PollStartChk();
    }

    /*-- ポートポーリング管理 --*/
    vd_s_PictCtl_PollPort();
}

/*===================================================================================================================================*/
/*  static void vd_s_PictCtl_PollPort(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PictCtl_PollPort(void)
{
    U1 u1_t_cnt; /* ループカウンタ */
    U1 u1_t_date; 
    
    u1_t_date = (U1)PICT_POLLPORT_NONDECI; /* ポーリング未確定設定 */

    /*----------------------------------------------------------------------*/
    /* 登録ポート全てチェック                                               */
    /*----------------------------------------------------------------------*/
    for(u1_t_cnt = (U1)0U; u1_t_cnt < (U1)PICT_POLLNO_MAX; u1_t_cnt++)
    {
        /* ポーリング動作中？ */
        if(bfg_Pict_PollSts[u1_t_cnt].u1_PollSts == (U1)PICT_POLLSTS_CYC) {
            /* 検知時間になっていない時、検知時間減算 */
            if(bfg_Pict_PollSts[u1_t_cnt].u1_PollCycTimCnt > (U1)0U) {
                bfg_Pict_PollSts[u1_t_cnt].u1_PollCycTimCnt--;
            }

            /* 検知時間になっているか? */
            if(bfg_Pict_PollSts[u1_t_cnt].u1_PollCycTimCnt <= (U1)0U) {

                /* チェック関数実行 ※ポーリング処理起動時、NULLでないことを保証 */
                u1_t_date = (tb_Pict_PollMng[u1_t_cnt].pfnChk)();

                /* 前回の値と一致するか? */
                if( bfg_Pict_PollSts[u1_t_cnt].u1_PortPreSts == u1_t_date) {
                    bfg_Pict_PollSts[u1_t_cnt].u1_PollSameCnt++;
                } else {
                    bfg_Pict_PollSts[u1_t_cnt].u1_PollSameCnt = (U1)PICT_SAME_FIRST;
                }

                /* 現在の値を前回の値に格納 */
                bfg_Pict_PollSts[u1_t_cnt].u1_PortPreSts = u1_t_date;

                /* 検知回数到達 */
                if( tb_Pict_PollMng[u1_t_cnt].u1_SameCntNum <= bfg_Pict_PollSts[u1_t_cnt].u1_PollSameCnt ) {
                    /* 状態変化時 */
                    if(bfg_Pict_PollSts[u1_t_cnt].u1_PortCnfSts != u1_t_date) {
                        /* ポート状態がHI連続確定でHIアクティブ論理の時 */
                        /* ポート状態がLO連続確定でLOWアクティブ論理の時 */
                        if( ((u1_t_date != (U1)FALSE) && (tb_Pict_PollMng[u1_t_cnt].u1_Kind == (U1)PICT_POLLPORT_HIACTIVE)) ||
                             ((u1_t_date == (U1)FALSE) && (tb_Pict_PollMng[u1_t_cnt].u1_Kind == (U1)PICT_POLLPORT_LOACTIVE)) ) {
                            /* 結果送信関数実行 ※ポーリング処理起動時、NULLでないことを保証 */
                            (tb_Pict_PollMng[u1_t_cnt].pfnChg)((U1)PICT_POLLPORT_ON);
                        }
                        /* ポート状態がHI連続確定でLOWアクティブ論理の時 or */
                        /* ポート状態がLOW連続確定でHIアクティブ論理の時 */
                        else if( ((u1_t_date != (U1)FALSE) && (tb_Pict_PollMng[u1_t_cnt].u1_Kind == (U1)PICT_POLLPORT_LOACTIVE)) ||
                                  ((u1_t_date == (U1)FALSE) && (tb_Pict_PollMng[u1_t_cnt].u1_Kind == (U1)PICT_POLLPORT_HIACTIVE)) ) {
                            /* 結果送信関数実行 ※ポーリング処理起動時、NULLでないことを保証 */
                            (tb_Pict_PollMng[u1_t_cnt].pfnChg)((U1)PICT_POLLPORT_OFF);
                        }
                        else {
                            /* 有り得ない、何もしない */
                        }
                        
                        /* 前回確定値を設定 */
                        bfg_Pict_PollSts[u1_t_cnt].u1_PortCnfSts = u1_t_date;
                    }
                    /* カウント回数クリア */
                    bfg_Pict_PollSts[u1_t_cnt].u1_PollSameCnt = (U1)PICT_POLLPORT_CNTINIT;
                }

                /* 次回検知時間設定 */
                bfg_Pict_PollSts[u1_t_cnt].u1_PollCycTimCnt = tb_Pict_PollMng[u1_t_cnt].u1_CycTim;
            }
        }
    }

    /* 関数終了 */
    return;
}

/*===================================================================================================================================*/
/*  static void vd_s_PictCtl_PollStsChk(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PictCtl_PollStsChk(void)
{
    U1 u1_t_audio_on;
    U1 u1_t_mmstby_n;
    U1 u1_t_lowpower_on;

    u1_t_audio_on= (U1)Dio_ReadChannel(PICT_PORT_AUDIO_ON);
    
    if((u1_t_audio_on == (U1)TRUE) && (u1_s_pict_poll_act[PICT_POLLFACT_AUDIO] == (U1)FALSE)){
        vd_s_PictCtl_PollMngStart((U1)PICT_POLLTRG_AUDIOON);
        u1_s_pict_poll_act[PICT_POLLFACT_AUDIO] = (U1)TRUE;
    }
    
    u1_t_mmstby_n = (U1)Dio_ReadChannel(PICT_PORT_MM_STBY_N);
    if(u1_t_mmstby_n == (U1)FALSE){
        if(u1_s_pict_poll_act[PICT_POLLFACT_MMSTBY] != (U1)FALSE){
            vd_s_PictCtl_PollMngStop((U1)PICT_POLLTRG_MMSTBY);
            u1_s_pict_poll_act[PICT_POLLFACT_MMSTBY] = (U1)FALSE;
        }
    }
    else{
        if(u1_s_pict_poll_act[PICT_POLLFACT_MMSTBY] != (U1)TRUE){
            vd_s_PictCtl_PollMngStart((U1)PICT_POLLTRG_MMSTBY);
            u1_s_pict_poll_act[PICT_POLLFACT_MMSTBY] = (U1)TRUE;
        }
    }
    
    u1_t_lowpower_on = (U1)Dio_ReadChannel(PICT_PORT_LOW_POWER_ON);
    if(u1_t_lowpower_on == (U1)FALSE){
        if(u1_s_pict_poll_act[PICT_POLLFACT_LOWPOWERON] != (U1)FALSE){
            vd_s_PictCtl_PollMngStop((U1)PICT_POLLTRG_LOWPOWERON);
            u1_s_pict_poll_act[PICT_POLLFACT_LOWPOWERON] = (U1)FALSE;
            bfg_Pict_StsMng.u1_pmapshold_raw_sts = (U1)PICT_POLLPORT_UNFIX;
            bfg_Pict_StsMng.u1_pmapshold_pol_sts = (U1)PICT_POLLPORT_UNFIX;
            bfg_Pict_StsMng.u1_pmpsholderr_raw_sts = (U1)PICT_POLLPORT_UNFIX;
            bfg_Pict_StsMng.u1_pmpsholderr_pol_sts = (U1)PICT_POLLPORT_UNFIX;
        }
    }
    else{
        if(u1_s_pict_poll_act[PICT_POLLFACT_LOWPOWERON] != (U1)TRUE){
            vd_s_PictCtl_PollMngStart((U1)PICT_POLLTRG_LOWPOWERON);
            u1_s_pict_poll_act[PICT_POLLFACT_LOWPOWERON] = (U1)TRUE;
        }
    }
}

/*============================================================================
 * DISP-REQ-GPIO0端子変化検知処理
 *----------------------------------------------------------------------------
 * モジュール名 : fc_PictCtl_DispReqGpio0Chg
 * 機能         : 端子変化検知処理
 * 処理内容     : 端子変化検知処理
 * 入力(引数)   : bySts: 端子変化検知状態
 * 出力(戻値)   : なし
 * 制限事項     :
 * 作成者       :  NOAH)馬孝康
 * ---------------------------------------------------------------------------
 * 変更履歴     : 2022.04.28 新規作成
 *              : 2024.02.26 NOAH)王 巧燕  DISP-REQ-GPIO0の検知処理の改善
 ===========================================================================*/
static void vd_s_PictCtl_DispReqGpio0Chg(U1 u1_a_Sts)
{
    bfg_Pict_StsMng.u1_DispReqGpio0rawSts = u1_a_Sts;
}

/*============================================================================
 * DISP-REQ-GPIO0端子変化検知処理
 *----------------------------------------------------------------------------
 * モジュール名 : fc_PictCtl_DispReqGpio0Chg
 * 機能         : 端子変化検知処理
 * 処理内容     : 端子変化検知処理
 * 入力(引数)   : bySts: 端子変化検知状態
 * 出力(戻値)   : なし
 * 制限事項     :
 * 作成者       :  NOAH)馬孝康
 * ---------------------------------------------------------------------------
 * 変更履歴     : 2022.04.28 新規作成
 *              : 2024.02.26 NOAH)王 巧燕  DISP-REQ-GPIO0の検知処理の改善
 ===========================================================================*/
static void vd_s_PictCtl_DispReqGpio0AppChk(void)
{
    if((u1_s_pict_apponflg == (U1)TRUE) &&
       (bfg_Pict_StsMng.u1_DispReqGpio0rawSts != (U1)PICT_POLLPORT_UNFIX)){
        bfg_Pict_StsMng.u1_DispReqGpio0Sts = bfg_Pict_StsMng.u1_DispReqGpio0rawSts;
    }
}
/*===================================================================================================================================*/
/*  static U1 u1_s_PictCtl_DispReqGpio0Chk(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_PictCtl_DispReqGpio0Chk(void)
{
    U1 u1_t_port;

    u1_t_port = (U1)Dio_ReadChannel(PICT_PORT_DISP_REQ_GPIO0);
    return(u1_t_port);
}

/*============================================================================
 * /CAMERA-CAP-STBY 端子変化検知処理
 *----------------------------------------------------------------------------
 * モジュール名 : fc_PictCtl_CamCapStbyChg
 * 機能         : /CAMERA-CAP-STBY 端子変化検知処理
 * 処理内容     : /CAMERA-CAP-STBY 端子変化検知処理
 * 入力(引数)   : bySts: 端子変化検知状態
 * 出力(戻値)   : なし
 * 制限事項     :
 * 作成者       :  NOAH)馬孝康
 * ---------------------------------------------------------------------------
 * 変更履歴     : 2022.04.28 新規作成
 * 変更履歴     : 2024.03.01 NOAH)張 彩霞  CAMERA-CAP-STBYの検知処理の改善
 ===========================================================================*/
static void vd_s_PictCtl_CamCapStbyChg(U1 u1_a_Sts)
{
    bfg_Pict_StsMng.u1_CamCapStbySts = u1_a_Sts;
}

/*===================================================================================================================================*/
/*  static U1 u1_s_PictCtl_CamCapStbyChk(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_PictCtl_CamCapStbyChk(void)
{
    U1 u1_t_port;

    u1_t_port = (U1)Dio_ReadChannel(PICT_PORT_CAMERA_CAP_STBY1);
    return(u1_t_port);
}

/*============================================================================
 * /CAMERA-CAP-STBY2 端子変化検知処理
 *----------------------------------------------------------------------------
 * モジュール名 : fc_PictCtl_CamCapStbyChk2Chg
 * 機能         : /CAMERA-CAP-STBY2 端子変化検知処理
 * 処理内容     : /CAMERA-CAP-STBY2 端子変化検知処理
 * 入力(引数)   : bySts: 端子変化検知状態
 * 出力(戻値)   : なし
 * 制限事項     :
 * 作成者       :  NOAH)馬孝康
 * ---------------------------------------------------------------------------
 * 変更履歴     : 2022.04.28 新規作成
 * 変更履歴     : 2024.03.01 NOAH)張 彩霞  CAMERA-CAP-STBY2の検知処理の改善
 ===========================================================================*/
static void vd_s_PictCtl_CamCapStby2Chg(U1 u1_a_Sts)
{
    bfg_Pict_StsMng.u1_CamCapStby2Sts = u1_a_Sts;
    
}

/*===================================================================================================================================*/
/*  static U1 u1_s_PictCtl_CamCapStby2Chk(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_PictCtl_CamCapStby2Chk(void)
{
    U1 u1_t_port;

    u1_t_port = (U1)Dio_ReadChannel(PICT_PORT_CAMERA_CAP_STBY2);
    return(u1_t_port);
}


/*============================================================================
 * /CAMERA-CAP-STBY3 端子変化検知処理
 *----------------------------------------------------------------------------
 * モジュール名 : fc_PictCtl_CamCapStby3Chg
 * 機能         : /CAMERA-CAP-STBY3 端子変化検知処理
 * 処理内容     : /CAMERA-CAP-STBY3 端子変化検知処理
 * 入力(引数)   : bySts: 端子変化検知状態
 * 出力(戻値)   : なし
 * 制限事項     :
 * 作成者       :  NOAH)馬孝康
 * ---------------------------------------------------------------------------
 * 変更履歴     : 2022.04.28 新規作成
 * 変更履歴     : 2024.03.01 NOAH)張 彩霞  CAMERA-CAP-STBY3の検知処理の改善
 ===========================================================================*/
static void vd_s_PictCtl_CamCapStby3Chg(U1 u1_a_Sts)
{
    bfg_Pict_StsMng.u1_CamCapStby3Sts = u1_a_Sts;
}

/*===================================================================================================================================*/
/*  static U1 u1_s_PictCtl_CamCapStby3Chk(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_PictCtl_CamCapStby3Chk(void)
{
    U1 u1_t_port;

    u1_t_port = (U1)Dio_ReadChannel(PICT_PORT_CAMERA_CAP_STBY3);
    return(u1_t_port);
}

/*===================================================================================================================================*/
/*  static U1 vd_s_PictCtl_PmsPsHoldRawChg(U1 u1_a_STS)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PictCtl_PmsPsHoldRawChg(U1 u1_a_STS)
{
    bfg_Pict_StsMng.u1_pmapshold_raw_sts = u1_a_STS;
}

/*===================================================================================================================================*/
/*  static U1 vd_s_PictCtl_PmsPsHoldPollChg(U1 u1_a_STS)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PictCtl_PmsPsHoldPollChg(U1 u1_a_STS)
{
    bfg_Pict_StsMng.u1_pmapshold_pol_sts = u1_a_STS;
}

/*===================================================================================================================================*/
/*  static U1 u1_s_PictCtl_PmsPsHoldChk(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_PictCtl_PmsPsHoldChk(void)
{
    U1 u1_t_port;

    u1_t_port = (U1)Dio_ReadChannel(PICT_PORT_PMA_PS_HOLD);
    return(u1_t_port);
}

/*===================================================================================================================================*/
/*  static U1 vd_s_PictCtl_PmPsailErrnRawChg(U1 u1_a_STS)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PictCtl_PmPsailErrnRawChg(U1 u1_a_STS)
{
    bfg_Pict_StsMng.u1_pmpsholderr_raw_sts = u1_a_STS;
}

/*===================================================================================================================================*/
/*  static U1 vd_s_PictCtl_PmPsailErrnPollChg(U1 u1_a_STS)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PictCtl_PmPsailErrnPollChg(U1 u1_a_STS)
{
    bfg_Pict_StsMng.u1_pmpsholderr_pol_sts = u1_a_STS;
}

/*===================================================================================================================================*/
/*  static U1 u1_s_PictCtl_PmPsailErrnChk(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_PictCtl_PmPsailErrnChk(void)
{
    U1 u1_t_port;

    u1_t_port = (U1)Dio_ReadChannel(PICT_PORT_PM_PSAIL_ERR_N);
    return(u1_t_port);
}

/*============================================================================
 * 画質モード通知(カメラ以外)の待ちタイマタイムアウト処理
 *----------------------------------------------------------------------------
 * モジュール名 : fc_Pict_MLTSocNotifTout
 * 機能         : 画質モード通知(カメラ以外)の待ちタイマタイムアウト処理
 * 処理内容     :
 * 入力（引数） : 無し
 * 出力（戻値） : 無し
 * 制限事項     :
 * 作成者       : NOAH)王 巧燕
 * ---------------------------------------------------------------------------
 * 変更履歴     : 2024.02.28 新規作成
 *              :
 ===========================================================================*/
static void vd_s_PictCtl_TSocNotifTout(void)
{
    /* 画質モード通知(カメラ以外)受信されない */
    bfg_Pict_StsMng.u1_RcvNoCamQualModeFlg = (U1)PICT_RCV_NOCAMQUAL_TOUT;

    /*  T_SIP_NOTIF_OUT待ちタイマ停止 */
    vd_s_PictCtl_ClrTim((U1)PICT_TIMID_ML_T_SIP_NOTIF_OUT);
}

/*============================================================================
 * カメラ同期検知開始待ちタイムアウト処理
 *----------------------------------------------------------------------------
 * モジュール名 : fc_Pict_MLCamSyncChkStaTout
 * 機能         : カメラ同期検知開始待ちタイムアウト処理
 * 処理内容     :
 * 入力（引数） : 無し
 * 出力（戻値） : 無し
 * 制限事項     :
 * 作成者       : NOAH)王 巧燕
 * ---------------------------------------------------------------------------
 * 変更履歴     : 2023.02.24 新規作成
 *              : 2023.03.22 NOAH)王 巧燕 カメラ同期検知対応
 ===========================================================================*/
static void vd_s_PictCtl_CamSyncChkStaTout(void)
{
    /* カメラ同期検知開始処理 */
    vd_s_PictCtl_CamSyncChkSta();
}

/*============================================================================
 * カメラ同期検知開始処理
 *----------------------------------------------------------------------------
 * モジュール名 : fc_Pict_MLCamSyncChkSta
 * 機能         : カメラ同期検知開始処理
 * 処理内容     :
 * 入力（引数） : 無し
 * 出力（戻値） : 無し
 * 制限事項     :
 * 作成者       : NOAH)王 巧燕
 * ---------------------------------------------------------------------------
 * 変更履歴     : 2023.02.24 新規作成
 *              : 2023.03.22 NOAH)王 巧燕 カメラ同期検知対応
 ===========================================================================*/
static void vd_s_PictCtl_CamSyncChkSta(void)
{
    U2  u2_t_time;

    u1_s_pict_syncstarteflg = (U1)TRUE;
    u2_t_time = u2_s_PictCtl_GetTim((U1)PICT_TIMID_ML_CAMSYNC_CHKCYC);
    if(u2_t_time == (U2)PICT_TIM_STOP)
    {
        /*  同期異常判定状態：未確定 */
        bfg_Ml_Ctl.u1_SyncChkRlt = (U1)PICT_CAM_SYNC_CHK_UNJDG;
        /* カメラ同期検知周期タイマ起動 */
        vd_s_PictCtl_SetTim((U1)PICT_TIMID_ML_CAMSYNC_CHKCYC, PICT_TIM_TOUT);
        bfg_Ml_Ctl.u1_SyncChkLoopCnt = (U1)PICT_CNT_INI;
        bfg_Ml_Ctl.u1_SyncChkSyncCnt = (U1)PICT_CNT_INI;
    }

}

/*============================================================================
 * カメラ同期検知終了処理
 *----------------------------------------------------------------------------
 * モジュール名 : fc_Pict_MLCamSyncChkSta
 * 機能         : カメラ同期検知開始処理
 * 処理内容     :
 * 入力（引数） : 無し
 * 出力（戻値） : 無し
 * 制限事項     :
 * 作成者       : NOAH)王 巧燕
 * ---------------------------------------------------------------------------
 * 変更履歴     : 2023.02.24 新規作成
 *              : 2023.03.22 NOAH)王 巧燕 カメラ同期検知対応
 ===========================================================================*/
static void vd_s_PictCtl_CamSyncChkStop(void)
{
    vd_s_PictCtl_ClrTim((U1)PICT_TIMID_ML_CAMSYNC_CHKCYC);
    u1_s_pict_syncstarteflg = FALSE;
    u1_s_pict_camsynccyc_flg = FALSE;
    u1_s_pict_camsynccyc_step = PICT_SEQ_CAMSYNCCHK_STEP0;
}

/*============================================================================
 * カメラ同期検知周期処理
 *----------------------------------------------------------------------------
 * モジュール名 : fc_Pict_MLCamSyncCycChk
 * 機能         : カメラ同期検知周期処理
 * 処理内容     :
 * 入力（引数） : 無し
 * 出力（戻値） : 無し
 * 制限事項     :
 * 作成者       : NOAH)王 巧燕
 * ---------------------------------------------------------------------------
 * 変更履歴     : 2023.03.22  新規作成
 *              :
 ===========================================================================*/
static void vd_s_PictCtl_CamSyncCycChk(void)
{
    /* タイマー再起動 */
    vd_s_PictCtl_SetTim((U1)PICT_TIMID_ML_CAMSYNC_CHKCYC, (U2)PICT_TIMER_ML_CAMSYNC_CHKCYC);
    
    u1_s_pict_camsynccyc_flg = (U1)TRUE;
}

/*===================================================================================================================================*/
/*  static void vd_s_PictCtl_CamSyncJdg(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PictCtl_CamSyncJdg(void)
{
    U1 u1_t_pre;
    U1 u1_t_mode;
    U1 u1_t_sts;

    u1_t_pre = (U1)PICT_CAM_SYNC_CHK_NG;
    u1_t_mode = (U1)FALSE;
    u1_t_sts = (U1)FALSE;
    
    if(u1_s_pict_camsynccyc_flg == (U1)TRUE){
        switch (u1_s_pict_camsynccyc_step)
        {
            case PICT_SEQ_CAMSYNCCHK_STEP0:
                if(u1_s_pict_syncstarteflg == (U1)TRUE){
                    u1_t_sts = u1_g_Pict_MlRegGet(&u1_s_pict_camsyncinfo);
                    if(u1_t_sts == (U1)TRUE){
                        u1_s_pict_camsynccyc_step = (U1)PICT_SEQ_CAMSYNCCHK_STEP1;
                    }
                }
                    break;

                case PICT_SEQ_CAMSYNCCHK_STEP1:
                    /* ループ回数をインクリメント */
                    if(bfg_Ml_Ctl.u1_SyncChkLoopCnt < (U1)U1_MAX){
                        bfg_Ml_Ctl.u1_SyncChkLoopCnt++;
                    }
                    if(u1_s_pict_camsyncinfo == (U1)PICT_ML_MIPI_SYNC_ON){
                        /* 同期信号あり回数をインクリメント */
                        bfg_Ml_Ctl.u1_SyncChkSyncCnt++;
                        }
                    if(bfg_Ml_Ctl.u1_SyncChkLoopCnt >= (U1)PICT_SYNC_LOOPCNT){
                        u1_t_pre = bfg_Ml_Ctl.u1_SyncChkRlt;
                        /* 前回同期判定状態が異常の場合 */
                        /* 同期信号がL2回あり場合、「正常」に判定 */
                        if(u1_t_pre == (U1)PICT_CAM_SYNC_CHK_NG){
                            if(bfg_Ml_Ctl.u1_SyncChkSyncCnt == (U1)PICT_SYNC_CHKCNTL2){
                                bfg_Ml_Ctl.u1_SyncChkRlt = (U1)PICT_CAM_SYNC_CHK_OK;

                                /* カメラモード中同期異常時の処理のみ実行する*/
                                u1_t_mode = u1_g_PictCtl_CamStsGet();
                                if(u1_t_mode == (U1)TRUE){
                                    /* カメラカメラ同期正常→異常シーケンス停止 */
                                    vd_s_PictCtl_CnclMlSeqReq((U1)PICT_SEQ_ML_CAMSYNCNG);
                                    /* カメラカメラ同期異常→正常シーケンス要求 */
                                    vd_s_PictCtl_SetMlSeqReq((U1)PICT_SEQ_ML_CAMSYNCOK);
                                }
                            }
                        }
                        /* 前回同期判定状態が正常・未確定の場合 */
                        /* 同期信号が一度もない場合、「異常」に判定 */
                        /* 同期信号がL1回以上場合、「正常」に判定 */
                        else{
                            if(bfg_Ml_Ctl.u1_SyncChkSyncCnt >= (U1)PICT_SYNC_CHKCNTL1){
                                bfg_Ml_Ctl.u1_SyncChkRlt = (U1)PICT_CAM_SYNC_CHK_OK;
                            }
                            else{
                                bfg_Ml_Ctl.u1_SyncChkRlt = (U1)PICT_CAM_SYNC_CHK_NG;
                                /* カメラモード中同期異常時の処理のみ実行する*/
                                u1_t_mode = u1_g_PictCtl_CamStsGet();
                                if(u1_t_mode == (U1)TRUE){
                                    /* カメラカメラ同期異常→正常シーケンス停止 */
                                    vd_s_PictCtl_CnclMlSeqReq((U1)PICT_SEQ_ML_CAMSYNCOK);
                                    /* カメラカメラ同期正常→異常シーケンス要求 */
                                    vd_s_PictCtl_SetMlSeqReq((U1)PICT_SEQ_ML_CAMSYNCNG);
                                }
                            }
                        }
                        /* ループ回数をクリア */
                        bfg_Ml_Ctl.u1_SyncChkLoopCnt = (U1)PICT_CNT_INI;
                        /* 同期信号あり回数をクリア */
                        bfg_Ml_Ctl.u1_SyncChkSyncCnt = (U1)PICT_CNT_INI;
                    }
                    u1_s_pict_camsynccyc_flg = (U1)FALSE;
                    u1_s_pict_camsynccyc_step = (U1)PICT_SEQ_CAMSYNCCHK_STEP0;
                    break;

                default:
                    u1_s_pict_camsynccyc_step = (U1)PICT_SEQ_CAMSYNCCHK_STEP0;
                    break;
        }
    }
}

/*============================================================================
 * カメラ状態取得処理
 *----------------------------------------------------------------------------
 * モジュール名 : u1_g_PictCtl_CamStsGet
 * 機能         : カメラ状態取得処理
 * 処理内容     : 
 * 入力（引数） : 
 * 出力（戻値） : 無し
 * 制限事項     : 無し
 * 作成者       : NOAH)王 巧燕
 * ---------------------------------------------------------------------------
 * 変更履歴     : 2023.2.20 新規作成
 ===========================================================================*/
U1 u1_g_PictCtl_CamStsGet(void)
{
    U1 u1_t_CamSts;
    
    u1_t_CamSts = (U1)FALSE;
    if(bfg_Pict_StsMng.u1_DiagMode == (U1)PICT_DIAG_MOD_OFF) {
        if((bfg_Pict_StsMng.u1_CamChgSts == (U1)PICT_CAMCHG_STS_OFF)
        ||(bfg_Pict_StsMng.u1_CamChgSts == (U1)PICT_CAMCHG_STS_OFF_GO)) {
            u1_t_CamSts = (U1)FALSE;
        }else {
            u1_t_CamSts = (U1)TRUE;
        }
    }
    else {
        u1_t_CamSts = (U1)FALSE;
    }
    
    return(u1_t_CamSts);
}

/*===================================================================================================================================*/
/*  U1 u1_g_PictCtl_GetCamDiagMode(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1 u1_g_PictCtl_GetCamDiagMode(void)
{
    return(bfg_Pict_StsMng.u1_DiagMode);
}

/*===================================================================================================================================*/
/*  static void vd_s_PictCtl_VmResetChk(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PictCtl_VmResetChk(void)
{
    U1 u1_t_vicrset;
    U1 u1_t_gvifrset;
    U1 u1_t_mode;
    U1 u1_t_sts;

    u1_t_vicrset = (U1)Dio_ReadChannel((U1)PICT_PORT_V_IC_RST);
    u1_t_gvifrset = (U1)Dio_ReadChannel((U1)PICT_PORT_GVIF_CAM_RST);
    u1_t_mode = u1_g_PictCtl_CamStsGet();
    u1_t_sts = (U1)FALSE;

    switch (u1_s_pict_vmresetchk_step)
    {
        case PICT_SEQ_VMRESETCHK_STEP0:
            u1_t_sts = u1_s_pict_mipi_chg_flg & (U1)PICT_MIPI_OUT_VMRESET;
            if(u1_t_sts != (U1)PICT_MIPI_OUT_VMRESET){
                if(u1_t_gvifrset == (U1)TRUE){
                    (void)u1_g_Gvif3SipFail();
                    u1_s_pict_vmresetchk_step = (U1)PICT_SEQ_VMRESETCHK_STEP1;
                }
                else{
                    u1_s_pict_vmrsttimeoutcnt = (U1)PICT_MIPITIMECNT_OFFOUT3;
                    u1_s_pict_vmresetchk_step = (U1)PICT_SEQ_VMRESETCHK_STEP_FIN;
                }
            }
            break;

        case PICT_SEQ_VMRESETCHK_STEP1:
            u1_t_sts = u1_g_Gvif3SipFail();
            if(u1_t_sts == (U1)TRUE){
                if(u1_s_pict_vmrsttimeoutcnt != (U1)PICT_TIMEOUTCNT_INIT){
                    u1_s_pict_vmrsttimeoutcnt = (U1)PICT_MIPITIMECNT_OFFOUT3;
                }
                u1_s_pict_vmresetchk_step = (U1)PICT_SEQ_VMRESETCHK_STEP_FIN;
            }
            break;

        case PICT_SEQ_VMRESETCHK_STEP_FIN:
            /* 何もしない */
            break;

        default:
            u1_s_pict_vmresetchk_step = (U1)PICT_SEQ_CAMSYNCCHK_STEP0;
            break;
    }
    if((u1_s_pict_vmrsttimeoutcnt >= (U1)PICT_MIPITIMECNT_OFFOUT3) &&
       (u1_s_pict_vmrsttimeoutcnt != (U1)PICT_TIMEOUTCNT_INIT)){
        if(u1_t_mode == (U1)FALSE){
            vd_g_PictMute_VmResetReq((U1)TRUE);
            vd_s_PictCtl_ClrTim((U1)PICT_TIMID_ML_T_SIP_NOTIF_OUT);
        }
        vd_g_XspiIviSub1PowerVMResetComp((U1)XSPI_IVI_POWER_RESET_COMP_CAMERA);
        if(u1_t_mode == (U1)TRUE){
            if(u1_t_vicrset == (U1)TRUE){
                /* カメラバイパス経路切替要求設定 */
                u1_s_pict_campass_chg_flg |= (U1)PICT_CAM_PATH_VMRESET;
                u1_s_pict_vmreset_bpass = (U1)PICT_VMRESET_REQ;
            }
        }
        u1_s_pict_vmrsttimeoutcnt = (U1)PICT_TIMEOUTCNT_INIT;

    }
    
    if(u1_s_pict_vmrsttimeoutcnt < (U1)PICT_TIMEOUTCNT_INIT){
        u1_s_pict_vmrsttimeoutcnt++;
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_PictCtl_SiPErrChk(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PictCtl_SiPErrChk(void)
{
    U1 u1_t_vicrset;
    U1 u1_t_gvifrset;
    U1 u1_t_sts;
    U1 u1_t_fact;
    U4 u4_t_comp;

    u1_t_vicrset = (U1)Dio_ReadChannel((U1)PICT_PORT_V_IC_RST);
    u1_t_gvifrset = (U1)Dio_ReadChannel((U1)PICT_PORT_GVIF_CAM_RST);
    u1_t_sts = (U1)FALSE;
    u1_t_fact = (U1)PICT_SIP_ERR_NON;
    u4_t_comp = (U4)FALSE;
    
    u1_s_pict_siperr = u1_s_PictCtl_SiPErrstsChk(&u1_t_fact);
    if((u1_s_pict_siperr == (U1)PICT_SIP_ERR_ON) && (u1_s_pict_siperr_old == (U1)PICT_SIP_ERR_OFF)){
        if(u1_s_pict_siperrfailsafe_flg == (U1)PICT_SIP_ERR_OFF){
            u1_s_pict_siperrchk_step = PICT_SEQ_SIPERRCHK_STEP0;
            u1_s_pict_siperrmute_flg = (U1)TRUE;
            u1_s_pict_siperrfailsafe_flg = (U1)PICT_SIP_ERR_ON;
            if(u1_t_fact == (U1)PICT_SIP_ERR_MCU){
                u1_s_pict_mipitimeout_jdgval = (U1)PICT_MIPITIMECNT_OFFOUT;
            }
            else{
                u1_s_pict_mipitimeout_jdgval = (U1)PICT_MIPITIMECNT_OFFOUT2;
            }
        }
        else if((u1_s_pict_siperrchk_step == (U1)PICT_SEQ_SIPERRCHK_STEP_FIN) && (u1_s_pict_mipitimeoutcnt == (U1)PICT_TIMEOUTCNT_INIT)){
            u1_s_pict_mipitimeoutcnt = u1_s_pict_mipitimeout_jdgval;
        }
        else{
            /* do nothing */
        }
    }
    switch (u1_s_pict_siperrchk_step)
    {
        case PICT_SEQ_SIPERRCHK_STEP0:
            if(u1_t_vicrset == (U1)TRUE){
                /* MIPI MUTE端子 Hi設定 */
                Dio_WriteChannel(PICT_PORT_MIPI_MUTE, (Dio_LevelType)TRUE);
            }
            if(u1_t_gvifrset == (U1)TRUE){
                /* MIPI出力ポートOFF設定 */
                (void)u1_g_Gvif3SipFail(); /* 暫定 */
                u1_s_pict_mipitimeoutcnt = (U1)PICT_TIMEOUTCNT_START;
                u1_s_pict_siperrchk_step = (U1)PICT_SEQ_SIPERRCHK_STEP1;
            }
            else{
                u1_s_pict_mipitimeoutcnt = u1_s_pict_mipitimeout_jdgval;
                u1_s_pict_siperrchk_step = (U1)PICT_SEQ_SIPERRCHK_STEP_FIN;
            }
            break;

        case PICT_SEQ_SIPERRCHK_STEP1:
                u1_t_sts = u1_g_Gvif3SipFail();
                if(u1_t_sts == (U1)TRUE){
                    if(u1_s_pict_mipitimeoutcnt != (U1)PICT_TIMEOUTCNT_INIT){
                        u1_s_pict_mipitimeoutcnt = u1_s_pict_mipitimeout_jdgval;
                    }
                    u1_s_pict_siperrchk_step = (U1)PICT_SEQ_SIPERRCHK_STEP_FIN;
                }
            break;

        case PICT_SEQ_SIPERRCHK_STEP_FIN:
        case PICT_SEQ_SIPERRCHK_STEP_NON:
            /* 何もしない */
            break;

        default:
            u1_s_pict_siperrchk_step = (U1)PICT_SEQ_CAMSYNCCHK_STEP0;
            break;
    }
    if((u1_s_pict_mipitimeoutcnt >= u1_s_pict_mipitimeout_jdgval) &&
       (u1_s_pict_mipitimeoutcnt != (U1)PICT_TIMEOUTCNT_INIT)){
        if(u1_s_pict_pwrnext_req == (U1)TRUE){
            u4_t_comp = (U4)TRUE;
            vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_VM2TO3_SIPERRCMP, &u4_t_comp, (U2)PICT_VM_1WORD);
            u1_s_pict_pwrnext_req = (U1)FALSE;
        }
        vd_s_PictCtl_SipErrVIcRstChk();
        if(u1_s_pict_cdcreset_req == (U1)PICT_CDCRESET_EXE){
            u1_s_pict_cdcreset_req = (U1)PICT_CDCRESET_NON;
            vd_g_XspiIviSub1PowerCDCResetComp((U1)XSPI_IVI_POWER_RESET_COMP_CAMERA);
        }
        u1_s_pict_mipitimeoutcnt = (U1)PICT_TIMEOUTCNT_INIT;
    }
    
    if(u1_s_pict_falsepositive_jdgreq == (U1)TRUE){
        vd_s_PictCtl_FalsePositiveChk();
    }
    
    vd_s_PictCtl_SiPErrClearChk();
    
    if(u1_s_pict_mipitimeoutcnt < (U1)PICT_TIMEOUTCNT_INIT){
        u1_s_pict_mipitimeoutcnt++;
    }
    
    u1_s_pict_siperr_old = u1_s_pict_siperr;
}

/*===================================================================================================================================*/
/*  static U1 u1_s_PictCtl_SiPErrstsChk(U1* u1p_a_fact)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_PictCtl_SiPErrstsChk(U1* u1p_a_fact)
{
    U1 u1_t_sts;
    U1 u1_t_req;
    U1 u1_t_fact;
    
    u1_t_sts  = (U1)PICT_SIP_ERR_OFF;
    u1_t_req  = (U1)PICT_SIP_ERR_OFF;
    u1_t_fact = (U1)PICT_SIP_ERR_NON;
    
    vd_s_PictCtl_SiPErrGetSts();
    
    u1_t_req = u1_s_PictCtl_AutoSiPOffChk();
    if(u1_t_req == (U1)PICT_SIP_ERR_ON){
        u1_t_sts = PICT_SIP_ERR_ON;
        u1_t_fact = (U1)PICT_SIP_ERR_AUTO;
    }
    
    u1_t_req = u1_s_PictCtl_McuSiPOffChk();
    if(u1_t_req == (U1)PICT_SIP_ERR_ON){
        u1_t_sts |= PICT_SIP_ERR_ON;
        u1_t_fact |= (U1)PICT_SIP_ERR_MCU;
    }
    
    *u1p_a_fact = u1_t_fact;
    
    return(u1_t_sts);
}

/*===================================================================================================================================*/
/*  static void vd_s_PictCtl_SiPErrGetSts(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PictCtl_SiPErrGetSts(void)
{
    st_sp_siperr_sts[PICT_SIPERR_PMRESIN].u1_pre = st_sp_siperr_sts[PICT_SIPERR_PMRESIN].u1_now;
    st_sp_siperr_sts[PICT_SIPERR_PMICFAST].u1_pre = st_sp_siperr_sts[PICT_SIPERR_PMICFAST].u1_now;
    st_sp_siperr_sts[PICT_SIPERR_OTA_ACT].u1_pre = st_sp_siperr_sts[PICT_SIPERR_OTA_ACT].u1_now;
    st_sp_siperr_sts[PICT_SIPERR_PMPSAIL_POL].u1_pre = st_sp_siperr_sts[PICT_SIPERR_PMPSAIL_POL].u1_now;
    st_sp_siperr_sts[PICT_SIPERR_PMPSAIL_RAW].u1_pre = st_sp_siperr_sts[PICT_SIPERR_PMPSAIL_RAW].u1_now;
    st_sp_siperr_sts[PICT_SIPERR_PMAPSHOLD_POL].u1_pre = st_sp_siperr_sts[PICT_SIPERR_PMAPSHOLD_POL].u1_now;
    st_sp_siperr_sts[PICT_SIPERR_PMAPSHOLD_RAW].u1_pre = st_sp_siperr_sts[PICT_SIPERR_PMAPSHOLD_RAW].u1_now;
    
    vd_s_PictCtl_SiPErrReadReq();
    vd_s_PictCtl_SiPErrReadMoni();
    
    if(bfg_Pict_StsMng.u1_pmpsholderr_pol_sts == (U1)PICT_POLLPORT_OFF){
        st_sp_siperr_sts[PICT_SIPERR_PMPSAIL_POL].u1_now = (U1)PICT_SIP_ERR_ON;
    }
    else{
        st_sp_siperr_sts[PICT_SIPERR_PMPSAIL_POL].u1_now = (U1)PICT_SIP_ERR_OFF;
    }
    if(bfg_Pict_StsMng.u1_pmpsholderr_raw_sts == (U1)PICT_POLLPORT_OFF){
        st_sp_siperr_sts[PICT_SIPERR_PMPSAIL_RAW].u1_now = (U1)PICT_SIP_ERR_ON;
    }
    else{
        st_sp_siperr_sts[PICT_SIPERR_PMPSAIL_RAW].u1_now = (U1)PICT_SIP_ERR_OFF;
    }
    if(bfg_Pict_StsMng.u1_pmapshold_pol_sts == (U1)PICT_POLLPORT_OFF){
        st_sp_siperr_sts[PICT_SIPERR_PMAPSHOLD_POL].u1_now = (U1)PICT_SIP_ERR_ON;
    }
    else{
        st_sp_siperr_sts[PICT_SIPERR_PMAPSHOLD_POL].u1_now = (U1)PICT_SIP_ERR_OFF;
    }
    if(bfg_Pict_StsMng.u1_pmapshold_raw_sts == (U1)PICT_POLLPORT_OFF){
        st_sp_siperr_sts[PICT_SIPERR_PMAPSHOLD_RAW].u1_now = (U1)PICT_SIP_ERR_ON;
    }
    else{
        st_sp_siperr_sts[PICT_SIPERR_PMAPSHOLD_RAW].u1_now = (U1)PICT_SIP_ERR_OFF;
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_PictCtl_SiPErrReadReq(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PictCtl_SiPErrReadReq(void)
{
    U4 u4_t_read;
    U1 u1_t_sts;
    U1 u1_t_req;

    u4_t_read = (U4)0U;
    u1_t_sts = (U1)0U;
    u1_t_sts = u1_g_iVDshReabyDid((U2)IVDSH_DID_REA_VM3TO2_SIPERR_INF, &u4_t_read, (U2)PICT_VM_1WORD);
    if(u1_t_sts != (U1)IVDSH_NO_REA){
        u1_t_req = (U1)(u4_t_read & (U4)PICT_MASK_1BYTE);
        if(u1_t_req == (U1)PICT_SIPERRREQ_SOC_ERR){
            st_sp_siperr_sts[PICT_SIPERR_PMICFAST].u1_now = (U1)PICT_SIP_ERR_ON;
        }
        else if(u1_t_req == (U1)PICT_SIPERRREQ_PMIC_ERR){
            st_sp_siperr_sts[PICT_SIPERR_PMRESIN].u1_now = (U1)PICT_SIP_ERR_ON;
        }
        else{
            st_sp_siperr_sts[PICT_SIPERR_PMRESIN].u1_now = (U1)PICT_SIP_ERR_OFF;
            st_sp_siperr_sts[PICT_SIPERR_PMICFAST].u1_now = (U1)PICT_SIP_ERR_OFF;
        }
    }
    
    u1_t_sts = u1_g_iVDshReabyDid((U2)IVDSH_DID_REA_VM3TO2_OTA_OFFSTS, &u4_t_read, (U2)PICT_VM_1WORD);
    if(u1_t_sts != (U1)IVDSH_NO_REA){
        u1_t_req = (U1)(u4_t_read & (U4)PICT_MASK_1BYTE);
        if(u1_t_req == (U1)PICT_SIPERRREQ_OTA_ACT){
            st_sp_siperr_sts[PICT_SIPERR_OTA_ACT].u1_now = (U1)PICT_SIP_ERR_ON;
        }
        else{
            st_sp_siperr_sts[PICT_SIPERR_OTA_ACT].u1_now = (U1)PICT_SIP_ERR_OFF;
        }
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_PictCtl_SiPErrReadMoni(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PictCtl_SiPErrReadMoni(void)
{
    U4 u4_t_read;
    U1 u1_t_sts;
    U1 u1_t_moni_pmpsail;
    U1 u1_t_moni_pmapshold;

    u4_t_read = (U4)0U;
    u1_t_sts = (U1)0U;
    u1_t_sts = u1_g_iVDshReabyDid((U2)IVDSH_DID_REA_VM3TO2_MONI_INF, &u4_t_read, (U2)PICT_VM_1WORD);
    
    if(u1_t_sts != (U1)IVDSH_NO_REA){
        u1_t_moni_pmpsail = (U1)(u4_t_read & (U4)PICT_MASK_1BYTE);
        if(u1_t_moni_pmpsail <= (U1)PICT_MONI_DETECT){
            u1_s_pict_siperrmoni_ensts[PICT_MONIENSTS_PMPSAILERRN] = u1_t_moni_pmpsail;
        }
        u1_t_moni_pmapshold = (U1)((u4_t_read & (U4)PICT_MASK_2BYTE) >> PICT_SHIF_1BYTE);
        if(u1_t_moni_pmapshold <= (U1)PICT_MONI_DETECT){
            u1_s_pict_siperrmoni_ensts[PICT_MONIENSTS_PMAPSHOLD] = u1_t_moni_pmapshold;
        }
    }
}

/*===================================================================================================================================*/
/*  static U1 u1_s_PictCtl_AutoSiPOffChk(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_PictCtl_AutoSiPOffChk(void)
{
    U1 u1_t_sts;
    U1 u1_t_enable;
    U1 u1_t_port;
    
    u1_t_sts = (U1)PICT_SIP_ERR_OFF;

    u1_t_sts |= u1_s_PictCtl_AutoSiPOffjdg(u1_s_pict_siperrmoni_ensts[PICT_MONIENSTS_PMPSAILERRN],
                                            st_sp_siperr_sts[PICT_SIPERR_PMPSAIL_POL].u1_pre, st_sp_siperr_sts[PICT_SIPERR_PMPSAIL_POL].u1_now,
                                            st_sp_siperr_sts[PICT_SIPERR_PMPSAIL_RAW].u1_pre, st_sp_siperr_sts[PICT_SIPERR_PMPSAIL_RAW].u1_now);
    
    u1_t_port = (U1)Dio_ReadChannel((U1)PICT_PORT_MM_OFF_REQ);
    if(u1_t_port == (U1)FALSE){
        u1_t_enable = u1_s_pict_siperrmoni_ensts[PICT_MONIENSTS_PMAPSHOLD];
    }
    else{
        u1_t_enable = (U1)PICT_MONI_DISABLE;
    }
    u1_t_sts |= u1_s_PictCtl_AutoSiPOffjdg(u1_t_enable,
                                            st_sp_siperr_sts[PICT_SIPERR_PMAPSHOLD_POL].u1_pre, st_sp_siperr_sts[PICT_SIPERR_PMAPSHOLD_POL].u1_now,
                                            st_sp_siperr_sts[PICT_SIPERR_PMAPSHOLD_RAW].u1_pre, st_sp_siperr_sts[PICT_SIPERR_PMAPSHOLD_RAW].u1_now);
    return(u1_t_sts);
}

/*===================================================================================================================================*/
/*  static U1 u1_s_PictCtl_AutoSiPOffjdg(const U1 u1_a_ENSTS, const U1 u1_a_POL_PRE, const U1 u1_a_POL_NOW,                          */
/*                                                            const U1 u1_a_RAW_PRE, const U1 u1_a_RAW_NOW)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_PictCtl_AutoSiPOffjdg(const U1 u1_a_ENSTS, const U1 u1_a_POL_PRE, const U1 u1_a_POL_NOW,
                                                          const U1 u1_a_RAW_PRE, const U1 u1_a_RAW_NOW)
{
    U1 u1_t_mode;
    U1 u1_t_sts;
    
    u1_t_mode = u1_g_PictCtl_CamStsGet();
    u1_t_sts = (U1)PICT_SIP_ERR_OFF;
    
    if(u1_a_ENSTS != (U1)PICT_MONI_DISABLE){
        if((u1_a_RAW_NOW == (U1)PICT_SIP_ERR_ON) && (u1_a_RAW_PRE == (U1)PICT_SIP_ERR_OFF)){
            u1_t_sts = (U1)PICT_SIP_ERR_ON;
            u1_s_pict_siperr_edg_flg = (U1)TRUE;
        }
        if((u1_a_POL_NOW == (U1)PICT_SIP_ERR_ON) && (u1_a_POL_PRE == (U1)PICT_SIP_ERR_OFF)){
            if((u1_t_mode == (U1)FALSE) && (u1_s_pict_siperrmute_req == (U1)PICT_SIPERRMUTE_NON)){
                vd_s_PictCtl_SiPErrMute((U1)PICT_SIPERRMUTE_MCU);
            }
            u1_t_sts = (U1)PICT_SIP_ERR_ON;
            u1_s_pict_siperr_edg_flg = (U1)FALSE;
        }
    }
    
    return(u1_t_sts);
}

/*===================================================================================================================================*/
/*  static U1 u1_s_PictCtl_McuSiPOffChk(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_PictCtl_McuSiPOffChk(void)
{
    U1 u1_t_mode;
    U1 u1_t_sts;
    
    u1_t_mode = u1_g_PictCtl_CamStsGet();
    u1_t_sts = (U1)PICT_SIP_ERR_OFF;
    
    if(((st_sp_siperr_sts[PICT_SIPERR_PMRESIN].u1_now == (U1)PICT_SIP_ERR_ON) &&
        (st_sp_siperr_sts[PICT_SIPERR_PMRESIN].u1_pre == (U1)PICT_SIP_ERR_OFF)) ||
       ((st_sp_siperr_sts[PICT_SIPERR_PMICFAST].u1_now == (U1)PICT_SIP_ERR_ON) &&
        (st_sp_siperr_sts[PICT_SIPERR_PMICFAST].u1_pre == (U1)PICT_SIP_ERR_OFF)) ||
       (u1_s_pict_socreset_req == (U1)PICT_SOCRESET_REQ)){
        if((u1_t_mode == (U1)FALSE) && (u1_s_pict_siperrmute_req == (U1)PICT_SIPERRMUTE_NON)){
            vd_s_PictCtl_SiPErrMute((U1)PICT_SIPERRMUTE_MCU);
        }
        u1_s_pict_pwrnext_req = (U1)TRUE;
        u1_t_sts = (U1)PICT_SIP_ERR_ON;
        u1_s_pict_siperr_edg_flg = (U1)FALSE;
        if(u1_s_pict_socreset_req == (U1)PICT_SOCRESET_REQ){
            u1_s_pict_socreset_req = (U1)PICT_SOCRESET_NON;
        }
    }
    
    if(((st_sp_siperr_sts[PICT_SIPERR_OTA_ACT].u1_now == (U1)PICT_SIP_ERR_ON) &&
        (st_sp_siperr_sts[PICT_SIPERR_OTA_ACT].u1_pre == (U1)PICT_SIP_ERR_OFF)) ||
       (u1_s_pict_cdcreset_req == (U1)PICT_CDCRESET_REQ)){
        if((u1_t_mode == (U1)FALSE) && (u1_s_pict_siperrmute_req == (U1)PICT_SIPERRMUTE_NON)){
            vd_s_PictCtl_SiPErrMute((U1)PICT_SIPERRMUTE_OTA);
        }
        u1_s_pict_pwrnext_req = (U1)TRUE;
        u1_t_sts = (U1)PICT_SIP_ERR_ON;
        u1_s_pict_siperr_edg_flg = (U1)FALSE;
        if(u1_s_pict_cdcreset_req == (U1)PICT_CDCRESET_REQ){
            u1_s_pict_cdcreset_req = (U1)PICT_CDCRESET_EXE;
        }
    }
    
    return(u1_t_sts);
}

/*===================================================================================================================================*/
/*  static void vd_s_PictCtl_SiPErrMute(const U1 u1_a_FACT)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PictCtl_SiPErrMute(const U1 u1_a_FACT)
{
    bfg_Pict_StsMng.u1_RcvNoCamQualModeFlg = (U1)PICT_RCV_NOCAMQUAL_STOP;
    vd_s_PictCtl_ClrTim((U1)PICT_TIMID_ML_T_SIP_NOTIF_OUT);
    u1_s_pict_siperrmute_req = u1_a_FACT;
}

/*===================================================================================================================================*/
/*  static void vd_s_PictCtl_SipErrVIcRstChk(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PictCtl_SipErrVIcRstChk(void)
{
    U1 u1_t_mode;
    U1 u1_t_vicrset;
    
    u1_t_mode = u1_g_PictCtl_CamStsGet();
    u1_t_vicrset = (U1)Dio_ReadChannel((U1)PICT_PORT_V_IC_RST);
    
    if(u1_t_vicrset == (U1)TRUE){
        if(u1_t_mode == (U1)TRUE){
            /* カメラバイパス経路切替要求設定 */
            u1_s_pict_campass_chg_flg |= (U1)PICT_CAM_PATH_SIPERR;
        }
        else{
            if(u1_s_pict_siperrmute_flg == (U1)TRUE){
                if(u1_s_pict_siperrmute_req == (U1)PICT_SIPERRMUTE_OTA){
                    vd_g_PictMute_CdcResetReq((U1)TRUE);
                }
                else{
                    vd_g_PictMute_SipResetReq((U1)TRUE);
                }
                u1_s_pict_siperrmute_flg = (U1)FALSE;
            }
            u1_s_pict_falsepositive_jdgreq = (U1)TRUE;
        }
    }
    else{
        u1_s_pict_falsepositive_jdgreq = (U1)TRUE;
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_PictCtl_FalsePositiveChk(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PictCtl_FalsePositiveChk(void)
{
    U1 u1_t_sts;
    U1 u1_t_mode;
    U1 u1_t_vicrset;

    u1_t_sts = (U1)FALSE;
    u1_t_mode = u1_g_PictCtl_CamStsGet();
    u1_t_vicrset = (U1)Dio_ReadChannel((U1)PICT_PORT_V_IC_RST);
    
    if(u1_s_pict_siperr_edg_flg == (U1)FALSE){
        u1_s_pict_falsepositive_jdgreq = (U1)FALSE;
    }
    else if((bfg_Pict_StsMng.u1_pmapshold_raw_sts == (U1)PICT_POLLPORT_ON) &&
            (bfg_Pict_StsMng.u1_pmapshold_pol_sts == (U1)PICT_POLLPORT_ON) &&
            (bfg_Pict_StsMng.u1_pmpsholderr_raw_sts == (U1)PICT_POLLPORT_ON) &&
            (bfg_Pict_StsMng.u1_pmpsholderr_pol_sts == (U1)PICT_POLLPORT_ON)){
        u1_t_sts = (U1)TRUE;
    }
    else{
        /* do nothing */
    }
    
    if(u1_t_sts == (U1)TRUE){ 
        if(bfg_Pict_StsMng.u1_pmapshold_raw_sts == (U1)PICT_POLLPORT_ON){
            /* エッジ検知有りポーリング検知無しで要求無しになった場合のMIPIMUTE端子と経路設定？が必要 */
            Dio_WriteChannel(PICT_PORT_MIPI_MUTE, (Dio_LevelType)FALSE);
            if(((u1_t_mode == (U1)TRUE) &&
                (u1_t_vicrset == (U1)TRUE)) &&
                (bfg_Pict_StsMng.u1_CamCapStby2Sts == (U1)PICT_POLLPORT_ON)){
                u1_s_pict_campass_chg_flg |= (U1)PICT_CAM_PATH_FALSEPOSITIVE;
            }
            u1_s_pict_falsepositive_jdgreq = (U1)FALSE;
        }
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_PictCtl_McuSiPOffChk(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PictCtl_SiPErrClearChk(void)
{
    U1 u1_t_bypass_flg;
    U4 u4_t_comp;
    
    u1_t_bypass_flg = u1_s_pict_campass_chg_flg & (U1)PICT_CAM_PATH_SIPERR;
    u4_t_comp = (U4)FALSE;
    
    if((st_sp_siperr_sts[PICT_SIPERR_PMRESIN].u1_now != (U1)PICT_SIP_ERR_ON) &&
       (st_sp_siperr_sts[PICT_SIPERR_PMICFAST].u1_now != (U1)PICT_SIP_ERR_ON) &&
       (st_sp_siperr_sts[PICT_SIPERR_OTA_ACT].u1_now != (U1)PICT_SIP_ERR_ON) &&
       (bfg_Pict_StsMng.u1_pmapshold_raw_sts != (U1)PICT_POLLPORT_OFF) &&
       (bfg_Pict_StsMng.u1_pmapshold_pol_sts != (U1)PICT_POLLPORT_OFF) &&
       (bfg_Pict_StsMng.u1_pmpsholderr_raw_sts != (U1)PICT_POLLPORT_OFF) &&
       (bfg_Pict_StsMng.u1_pmpsholderr_pol_sts != (U1)PICT_POLLPORT_OFF) &&
       (u1_s_pict_siperrchk_step == (U1)PICT_SEQ_SIPERRCHK_STEP_FIN) &&
       (u1_t_bypass_flg != (U1)PICT_CAM_PATH_SIPERR)){
        u1_s_pict_siperrfailsafe_flg = (U1)PICT_SIP_ERR_OFF;
        u1_s_pict_siperrmute_req = (U1)PICT_SIPERRMUTE_NON;
        u1_s_pict_siperrchk_step = (U1)PICT_SEQ_SIPERRCHK_STEP_NON;
        vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_VM2TO3_SIPERRCMP, &u4_t_comp, (U2)PICT_VM_1WORD);
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_PictCtl_PmsPsHoldstsChk(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PictCtl_PmsPsHoldstsChk(void)
{
    U1 u1_t_vicrset;
    U1 u1_t_pmspshold;
    
    u1_t_vicrset = (U1)Dio_ReadChannel(PICT_PORT_V_IC_RST);
    u1_t_pmspshold = bfg_Pict_StsMng.u1_pmapshold_raw_sts;
    
    if(u1_t_pmspshold != u1_s_pict_pmspsh){
        if(u1_t_pmspshold == (U1)PICT_POLLPORT_ON){
            /* MIPI MUTE端子 Lo設定 */
            Dio_WriteChannel(PICT_PORT_MIPI_MUTE, (Dio_LevelType)FALSE);
        }
        else{
            if(u1_t_vicrset == (U1)TRUE){
                /* MIPI MUTE端子 Hi設定 */
                Dio_WriteChannel(PICT_PORT_MIPI_MUTE, (Dio_LevelType)TRUE);
            }
        }
    }
    u1_s_pict_pmspsh = u1_t_pmspshold;
}

/*===================================================================================================================================*/
/*  static void vd_s_PictCtl_VIcRstChk(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PictCtl_VIcRstChk(void)
{
    U1 u1_t_vicrset;
    U1 u1_t_pmspshold;
    
    u1_t_vicrset = (U1)Dio_ReadChannel(PICT_PORT_V_IC_RST);
    u1_t_pmspshold = bfg_Pict_StsMng.u1_pmapshold_raw_sts;
    
    if(u1_t_vicrset != u1_s_pict_vicrset){
        if(u1_t_vicrset == (U1)TRUE){
            vd_s_PictCtl_CycChkStart();
            if(u1_t_pmspshold == (U1)PICT_POLLPORT_OFF){
                /* MIPI MUTE端子 Hi設定 */
                Dio_WriteChannel(PICT_PORT_MIPI_MUTE, (Dio_LevelType)TRUE);
            }
        }
        else{
            vd_s_PictCtl_CamSyncChkStop(); /* 同期判定停止 */
            /* MIPI MUTE端子 Lo設定 */
            Dio_WriteChannel(PICT_PORT_MIPI_MUTE, (Dio_LevelType)FALSE);
        }
    }
    u1_s_pict_vicrset = u1_t_vicrset;

}

/*===================================================================================================================================*/
/*  U1 u1_g_PictCtl_CamSyncSts(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1 u1_g_PictCtl_CamSyncSts(void)
{
    return(bfg_Ml_Ctl.u1_SyncChkRlt);
}

/*===================================================================================================================================*/
/*  static void vd_s_PictCtl_CycChkStart(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PictCtl_CycChkStart(void)
{
    U2 u2_t_tim;

    u2_t_tim = u2_s_PictCtl_GetTim((U1)PICT_TIMID_ML_CAMSYNC_CHKSTA);
    if(u1_s_pict_syncstarteflg == (U1)FALSE){
        if(bfg_Pict_StsMng.u1_DispReqGpio0Sts == (U1)PICT_POLLPORT_ON){
            vd_s_PictCtl_CamSyncChkSta();
        }
        else if((bfg_Pict_StsMng.u1_stasts == (U1)POWER_MODE_STATE_APPON) && (u2_t_tim == (U2)PICT_TIM_STOP)){
            vd_s_PictCtl_SetTim((U1)PICT_TIMID_ML_CAMSYNC_CHKSTA, (U2)PICT_TIMER_ML_CAMSYNC_CHKSTA_WAIT);
        }
        else{
            /* do nothing */
        }
    }
}

/*============================================================================
 * 映像IC起動処理完了チェック処理
 *----------------------------------------------------------------------------
 * モジュール名 : vd_s_PictCtl_MLIniChk
 * 機能         :
 * 処理内容     :
 * 入力（引数） : 無し
 * 出力（戻値） : 無し
 * 制限事項     :
 * 作成者       : NOAH)王 巧燕
 * ---------------------------------------------------------------------------
 * 変更履歴     : 2022.12.12 新規作成
                 2023.3.30 NOAH)王 巧燕
                 固着検知ビット監視とメインマイコンのCAMERA-MODE1=Hi検知異常
                 のフェールセーフ対応
 ===========================================================================*/
static void vd_s_PictCtl_MLIniChk(void)
{
    U1 u1_t_mlcmp;
    
    /* 映像IC起動処理完了状態取得(暫定) */
    if(Mcu_OnStep_EIZOIC_OVRALL == (uint8)MCU_STEP_EIZOIC_OVERALL_FIN){
        u1_t_mlcmp = (U1)TRUE;
    }
    else{
        u1_t_mlcmp = (U1)FALSE;
    }
    /* 映像IC起動処理完了時に処理を実施 */
    if((u1_s_pict_mlcmp_old == (U1)FALSE) && (u1_t_mlcmp == (U1)TRUE)){
        if(u1_s_pict_mliniflg == (U1)FALSE){
            /* メインマイコンのCAMERA-MODE1=Hi検知異常のフェールセーフタイマ起動(40ms) */
            vd_s_PictCtl_SetTim((U1)PICT_TIMID_ML_CAM_MODE1_ERR_CHKCYC, (U2)PICT_TIMER_ML_CAM_MODE_H_MAIN_CHKERR_CHKCYC);
            bfg_Ml_Ctl.u1_CamModeHMainChkErrCnt_N1 = (U1)PICT_CNT_INI;
            u1_s_pict_mliniflg = (U1)TRUE;
        }
    }
    u1_s_pict_mlcmp_old = u1_t_mlcmp;
}

/*============================================================================
 * メインマイコンのCAMERA-MODE1=Hi 検知異常のフェールセーフ処理
 *----------------------------------------------------------------------------
 * モジュール名 : fc_Pict_MLCamModeHMainChkErrCycChk
 * 機能         : メインマイコンのCAMERA-MODE1=Hi 検知異常のフェールセーフ処理
 * 処理内容     :
 * 入力（引数） : 無し
 * 出力（戻値） : 無し
 * 制限事項     :
 * 作成者       : NOAH)王 巧燕
 * ---------------------------------------------------------------------------
 * 変更履歴     : 2023.03.22 新規作成
 *               カメラ制御仕様(24MM)_6.0版対応
 ===========================================================================*/
static void vd_s_PictCtl_CamModeHMainChkErrCycChk(void)
{
    U1 u1_t_mode;

    /*メインマイコンのCAMERA-MODE1=Hi検知異常検出待ちタイマ再起動(40ms) */
    vd_s_PictCtl_SetTim((U1)PICT_TIMID_ML_CAM_MODE1_ERR_CHKCYC, (U1)PICT_TIMER_ML_CAM_MODE_H_MAIN_CHKERR_CHKCYC);

    /* カメラモード中 and               */
    /* カメラダイアグではない and       */
    /* MMダイアグではない and           */
    /* カメラ同期判定結果正常           */
    /* カメラ経路設定＝通常カメラ経路   */
    u1_t_mode = u1_g_PictCtl_CamStsGet();
    if((u1_t_mode == (U1)TRUE) &&
       (bfg_Pict_StsMng.u1_DiagMode == (U1)PICT_DIAG_MOD_OFF) &&
       (bfg_Pict_StsMng.u1_CamChgSts == (U1)PICT_CAMCHG_STS_NORMAL) &&
       (bfg_Ml_Ctl.u1_SyncChkRlt == (U1)PICT_CAM_SYNC_CHK_OK)){
        bfg_Ml_Ctl.u1_CamModeHMainChkErrCnt_N1++;
        if(bfg_Ml_Ctl.u1_CamModeHMainChkErrCnt_N1 >= (U1)PICT_CAM_MODE_H_MAIN_CHKERR_CNT_L1){
            /* 画質モード(カメラ)通知がない */
            if(bfg_Pict_StsMng.u1_RcvCamQualModeFlg == (U1)FALSE){
                /* 管理するカメラのパス設定は、カメラ通常経路を保持し強制的にカメラバイパス切替を行う */
                u1_s_pict_campass_chg_flg |= (U1)PICT_CAM_PATH_CAMMODEFAIL;
            }
            /* N1=0 */
            bfg_Ml_Ctl.u1_CamModeHMainChkErrCnt_N1 = (U1)PICT_CNT_INI;  
        }
     }else{
        /* N1=0 */
        bfg_Ml_Ctl.u1_CamModeHMainChkErrCnt_N1 = (U1)PICT_CNT_INI;
     }
}


/*============================================================================
 * 同期検知・経路情報通知(BEYE/FEYE) 送信チェック
 *----------------------------------------------------------------------------
 * モジュール名 : fc_PictCtl_CamSyncPathInfoNtyChk
 * 機能         : 同期検知・経路情報通知(BEYE/FEYE) 送信チェック
 * 処理内容     : 同期検知・経路情報通知(BEYE/FEYE) 送信チェック処理を行う
 * 入力(引数)   : 無し
 * 出力(戻値)   : 無し
 * 制限事項     : 無し
 * 作成者       : NOAH)王 巧燕
 * ---------------------------------------------------------------------------
 * 変更履歴     ：2023.03.28     NOAH)王巧燕 新規作成
 ===========================================================================*/
static void vd_s_PictCtl_CamSyncPathInfoNtyChk(void)
{
    U1 u1_t_reset_sts;
    U1 u1_t_mipi_sts;
    
    u1_s_pict_vicstasts= (U1)Dio_ReadChannel(PICT_PORT_V_IC_STATUS);
    u1_t_reset_sts = u1_g_Pict_MlDevRstGet();
    u1_t_mipi_sts = u1_g_Gvif3RxMipiOutputSts();
    
    /* 情報変更あるかチェック */
    if((st_sp_send.u1_SyncChkRlt != bfg_Ml_Ctl.u1_SyncChkRlt)
      ||(st_sp_send.u1_MlMipiSts != bfg_Pict_StsMng.u1_CamCapStbySts)
      ||(st_sp_send.u1_CamPath != bfg_Pict_StsMng.u1_CamCapStby2Sts)
      ||(st_sp_send.u1_VideoOutSts != u1_t_mipi_sts)
      ||(st_sp_send.u1_vicstastssig != u1_s_pict_vicstasts)
      ||(u1_s_pict_icreset_sts != u1_t_reset_sts))
      {
        u1_s_pict_icreset_sts = u1_t_reset_sts;
        st_sp_send.u1_VideoOutSts = u1_t_mipi_sts;
        /* 同期検知・経路情報通知 送信 */
        vd_s_PictCtl_CamSyncPathInfoNtySnd();

        /* 前回状態更新 */
        st_sp_send.u1_SyncChkRlt = bfg_Ml_Ctl.u1_SyncChkRlt;
        st_sp_send.u1_MlMipiSts = bfg_Pict_StsMng.u1_CamCapStbySts;
        st_sp_send.u1_CamPath = bfg_Pict_StsMng.u1_CamCapStby2Sts;
        st_sp_send.u1_vicstastssig = u1_s_pict_vicstasts;
      }


}

/*============================================================================
 * 同期検知・経路情報通知(BEYE/FEYE) 送信
 *----------------------------------------------------------------------------
 * モジュール名 : fc_PictCtl_CamSyncPathInfoNtySnd
 * 機能         : 同期検知・経路情報通知(BEYE/FEYE) 送信
 * 処理内容     : 同期検知・経路情報通知(BEYE/FEYE) 送信
 * 入力（引数） : 無し
 * 出力（戻値） : 無し
 * 制限事項     : 無し
 * 作成者       : NOAH)馬
 * ---------------------------------------------------------------------------
 * 変更履歴     : 2022.06.14  新規作成
 *              : 2023.03.29  王巧燕  カメラ同期判定処理対応
 *              : 
 ===========================================================================*/
static void vd_s_PictCtl_CamSyncPathInfoNtySnd(void)
{
    ST_XSPI_IVI_MISC_CAMERA_SYNC_PASS_DATA  st_t_send;

    /* デジタルカメラ(MIPI)映像入力同期情報設定 */ 
    if(u1_s_pict_icreset_sts == (U1)PICT_ML_DEVRST_ACT){
        st_t_send.u1_camera_sync = PICT_CAM_SYNC_NG;        /* 同期無し */
    } else if(bfg_Ml_Ctl.u1_SyncChkRlt == (U1)PICT_CAM_SYNC_CHK_OK){
        st_t_send.u1_camera_sync = PICT_CAM_SYNC_OK;        /* 同期あり */
    } else if(bfg_Ml_Ctl.u1_SyncChkRlt == (U1)PICT_CAM_SYNC_CHK_NG){
        st_t_send.u1_camera_sync = PICT_CAM_SYNC_NG;        /* 同期無し */
    } else {
        st_t_send.u1_camera_sync = PICT_CAM_SYNC_UNSET;     /* 未確定・無効 */
    }

    /* 映像IC MIPI(BEYE)出力情報設定 */
    if(bfg_Pict_StsMng.u1_CamCapStbySts == (U1)PICT_POLLPORT_ON){
        st_t_send.u1_camera_mipi_display = (U1)PICT_BEYE_MIPI_HS;       /* HS出力(LP-11 解除) */
    } else {
        st_t_send.u1_camera_mipi_display = (U1)PICT_BEYE_MIPI_LP11; /* LP-11 出力 */
    }

    /* カメラ強制パス状態情報設定 */
    if(bfg_Pict_StsMng.u1_CamCapStby2Sts == (U1)PICT_POLLPORT_ON) {
        st_t_send.u1_camera_pass = (U1)PICT_CAM_PATH_LV;        /* LV映像出力中 */
    } else {
        st_t_send.u1_camera_pass = (U1)PICT_CAM_PATH_FORPASS;   /* カメラ強制パス表示中 */
    }

    /* 映像IC MIPI(FEYE)出力情報設定 */
    if(st_sp_send.u1_VideoOutSts == (U1)GVIF3RX_MIPIOUTPUT_ON){
        st_t_send.u1_camera_mipi_rec = (U1)PICT_CAM_FEYE_MIPI_ON;   /* MIPI出力 ON */
    } else {
        st_t_send.u1_camera_mipi_rec = (U1)PICT_CAM_FEYE_MIPI_OFF;  /* MIPI出力 OFF */
    }

    /* V-IC-STATUS2出力情報設定 */
        st_t_send.u1_camera_vic_sts = u1_s_pict_vicstasts;

    /*************************************************/
    /*                 送信                          */
    /*************************************************/
    vd_g_XspiIviSub1CameraSyncPassDataSend(st_t_send);

    /* 同期検知・経路情報通知?定期送信タイマを再セット */
    vd_s_PictCtl_SetTim((U1)PICT_TIMID_CAMSYNCPATHINFO_SENDCYC, PICT_TIMER_TABCMD_SENDCYC);
}


/*============================================================================
 * カメラシステム種別判別開始待ちタイマアウトプロセス
 *----------------------------------------------------------------------------
 * モジュール名 : fc_PictCtl_CamKindDiscSta
 * 機能         : カメラシステム種別判別開始待ちタイマアウトプロセス
 * 処理内容     : カメラシステム種別判別開始待ちタイマアウトプロセス
 * 入力(引数)   : 
 * 出力(戻値)   : 
 * 制限事項     : 
 * 作成者       : NOAH)馬孝康
 * ---------------------------------------------------------------------------
 * 変更履歴     : 2022/11/09 新規作成
 *              :       
 ===========================================================================*/
static void vd_s_PictCtl_CamKindDiscSta(void)
{
    /* カメラシステム種別判別フラグON */
    bfg_Pict_StsMng.st_CamDisc.u1_CamKindDiscEn = (U1)TRUE;
    vd_s_PictCtl_CdsizeChk();
}

/*============================================================================
 * 画質モード受信パラメータチェック処理
 *----------------------------------------------------------------------------
 * モジュール名 : fc_PictCtl_DispQualPraChk
 * 機能         : 画質モード受信パラメータチェック処理
 * 処理内容     : 
 * 入力（引数） : ST_DISP_MODE* pstDispQuality : 画質モード構造体
 * 出力（戻値） : 
 * 制限事項     : 
 * 作成者       : NOAH)馬
 * ---------------------------------------------------------------------------
 * 変更履歴     :2022/09/08 新規作成
 *              :2024/05/21 POST21MM-40726 カメラダイアグ中にメインマイコンリセット要求受信してリセット後、MUTE解除できない対応
 *              :2024/05/28 NOAH)王 巧燕 MM24PRBL-795カメラダイアグ非表示後のセンターディスプレイ画質反映が遅い対応
 ===========================================================================*/
void vd_g_PictCtl_DispQualPraChk(U1 u1_a_MODE)
{   
    /* 画質モード通知受け取ったフラグON */
    bfg_Pict_StsMng.u1_RcvQualModeFlg = (U1)TRUE;
    if(u1_a_MODE != (U1)PICT_VIS_KIND_CAM){
        /* 画質モード通知(カメラ以外)受信済 */
        bfg_Pict_StsMng.u1_RcvNoCamQualModeFlg = (U1)PICT_RCV_NOCAMQUAL_END;
        /* T_SIP_NOTIF_OUT待ちタイマ停止 */
        vd_s_PictCtl_ClrTim((U1)PICT_TIMID_ML_T_SIP_NOTIF_OUT);
    }
    else {
        bfg_Pict_StsMng.u1_RcvCamQualModeFlg = (U1)TRUE;
    }
    bfg_Pict_StsMng.u1_RcvQualModeDate = u1_a_MODE;
}

/*============================================================================
 * CANBCC1S05受信処理
 *----------------------------------------------------------------------------
 * モジュール名 : fc_PictCtl_RcvBCC1S05
 * 機能         : BCC1S05受信処理
 * 処理内容     : 
 * 入力(引数)   : BYTE* pbyRcvDat : 受信CANデータ
 * 出力(戻値)   : 無し
 * 制限事項     : pbyRcvDatがNULLでないことは呼び出し元で保障
 * 作成者       : NOAH)王 巧燕
 * ---------------------------------------------------------------------------
 * 変更履歴     : 2023.10.11 NOAH)王 巧燕   新規作成 
 *              : 2023.11.26 NOAH)王 巧燕  [POST21MM-29528]MAVTYPEとR_CROP_0の保持条件変更対応 
 *              : 2024.06.04  NOAH)張彩霞 24MM_SystemSequence_カメラ機能_システム設計_2.1版変更対応
 ===========================================================================*/
void vd_g_PictCtl_RcvBCC1S05(void)
{
    U1 u1_t_caminfchgflg;
    U1 u1_t_CamKindConverd;

    /* カメラシステム種別判定許可判断 */
    if(bfg_Pict_StsMng.st_CamDisc.u1_CamKindDiscEn == (U1)TRUE){
        u1_t_caminfchgflg  = u1_s_PictCtl_CamKindjdg();
        u1_t_caminfchgflg |= u1_s_PictCtl_CenterCamSizjdg();
        /************************************************************************************************/
        /* カメラシステム種別・センターカメラサイズ変更後の処理                                         */
        /************************************************************************************************/
        if(u1_t_caminfchgflg == (U1)TRUE){
            u1_t_CamKindConverd = bfg_Pict_StsMng.u1_CamKindConverd;
            /* カメラシステム種別(ADAS/変換BOX)更新 */
            vd_s_PictCtl_CamKindConverdUpDate();
            if(u1_t_CamKindConverd != bfg_Pict_StsMng.u1_CamKindConverd){
                vd_s_PictCtl_CdsizeChk();
            }

            /* カメラシステム種別(ドメコン有/ドメコン無)更新 */
            vd_s_PictCtl_GvifCamKindConverdUpDate();

            /* 更新した値をバックアップする */
            vd_s_PictCtl_Bkup_Write();

            u1_s_pict_regwrite_req = (U1)TRUE;
        }
    }
    
    vd_s_PictCtl_MmresetSndChk();
    vd_s_PictCtl_SetTim((U1)PICT_TIMID_BCC1S05_TIMEOUT, (U2)PICT_TIMER_BCC1S05_TIMEOUT);
}

/*===================================================================================================================================*/
/*  static U1 u1_s_PictCtl_CamKindjdg(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_PictCtl_CamKindjdg(void)
{
    U1 u1_t_camkind;
    U1 u1_t_chgflg;
    U1 u1_t_chk;

    /************************************************************************************************/
    /* カメラシステム種別判定                                                                       */
    /************************************************************************************************/
    u1_t_camkind = (U1)0U;
    u1_t_chgflg = (U1)FALSE;
    Com_ReceiveSignal(ComConf_ComSignal_MAVTYPE, &u1_t_camkind); /* MAVTYPE信号取得 */

    /* カメラ種別は有効値かを判断 */
    u1_t_chk = u1_s_PictCtl_CamKindValidChk(u1_t_camkind);
    if(u1_t_chk == (U1)TRUE){
        if(bfg_Pict_StsMng.st_CamDisc.u1_LastCamKind == u1_t_camkind){
            if(bfg_Pict_StsMng.st_CamDisc.u1_CamKindCnt < (U1)PICT_CAN_CAM_CNTMAX) {
                bfg_Pict_StsMng.st_CamDisc.u1_CamKindCnt++;
            }
        }
        else{
            bfg_Pict_StsMng.st_CamDisc.u1_CamKindCnt = (U1)PICT_SAMECNT_FIRST;
        }
        /* ラストカメラシステム種別更新 */
        bfg_Pict_StsMng.st_CamDisc.u1_LastCamKind = u1_t_camkind;
        /* 3回連続受信したカメラ種別が一致の場合、カメラ種別確定 */
        if(bfg_Pict_StsMng.st_CamDisc.u1_CamKindCnt >= (U1)PICT_CAN_CAM_CNTMAX)
        {
            if(st_sp_Pict_BackUpInf.u1_CamKind != u1_t_camkind){
                st_sp_Pict_BackUpInf.u1_CamKind = u1_t_camkind;
                /*  カメラ種別変更フラグ：ON */
                u1_t_chgflg = (U1)TRUE;
            }
            bfg_Pict_StsMng.st_CamDisc.u1_CamKindCnt = (U1)PICT_SAMECNT_INI;
        }
    }

    vd_s_PictCtl_SetTim((U1)PICT_TIMID_MAVTYPE_TIMEOUT, (U2)PICT_TIMER_MAVTYPE_TIMEOUT);

    return(u1_t_chgflg);
}

/*===================================================================================================================================*/
/*  static void vd_s_PictCtl_MavtypeTimeout(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PictCtl_MavtypeTimeout(void)
{
    bfg_Pict_StsMng.st_CamDisc.u1_LastCamKind = (U1)PICT_CAN_CAM_KIND_NORX;
    bfg_Pict_StsMng.st_CamDisc.u1_CamKindCnt = (U1)PICT_SAMECNT_INI;
}

/*============================================================================
 * カメラシステム種別は有効値かを判断する処理
 *----------------------------------------------------------------------------
 * モジュール名 : fc_PictCtl_CamKindValidChk
 * 機能         : カメラシステム種別は有効値かを判断する
 * 処理内容     : カメラシステム種別は有効値かを判断する
 * 入力(引数)   : u1_CamKind:カメラシステム種別
 * 出力(戻値)   : byRlt:有効/無効
 * 制限事項     : 無し
 * 作成者       : NOAH)王巧燕
 * ---------------------------------------------------------------------------
 * 変更履歴     : 2023.11.21 NOAH)王巧燕 新規作成
 *              : 
 ===========================================================================*/
static U1 u1_s_PictCtl_CamKindValidChk(U1 u1_a_CamKind)
{
    U1 u1_t_valid;
    switch (u1_a_CamKind)
    {
        case PICT_CAN_CAM_KIND_PVM:
        case PICT_CAN_CAM_KIND_MTM:
        case PICT_CAN_CAM_KIND_SIM:
        case PICT_CAN_CAM_KIND_BGM:
        case PICT_CAN_CAM_KIND_SBGM:
        case PICT_CAN_CAM_KIND_PVM_METER:
        case PICT_CAN_CAM_KIND_MTM_METER:
        case PICT_CAN_CAM_KIND_NONE:
            u1_t_valid = (U1)TRUE;      /*有効値*/
            break;

        case PICT_CAN_CAM_KIND_UNFIX:
        default:
            u1_t_valid = (U1)FALSE;     /*無効値*/
            break;
    }
    return(u1_t_valid);
}
/*============================================================================
 * カメラ種別により、カメラシステム種別(ADAS/変換BOX)更新
 *----------------------------------------------------------------------------
 * モジュール名 : fc_PictCtl_CamKindConverdUpDate
 * 機能         : カメラシステム種別(ADAS/変換BOX)更新処理
 * 処理内容     : 
 * 入力（引数） : 無し
 * 出力（戻値） : 無し
 * 制限事項     : 無し
 * 作成者       : NOAH)王 巧燕
 * ---------------------------------------------------------------------------
 * 変更履歴     : 2023.7.11 新規作成
 *              : 映像IC（ML86306）制御仕様(24MM) 10.0版変更対応
 ===========================================================================*/
static void vd_s_PictCtl_CamKindConverdUpDate(void)
{
    switch (st_sp_Pict_BackUpInf.u1_CamKind)
    {
        case PICT_CAN_CAM_KIND_SBGM:
            bfg_Pict_StsMng.u1_CamKindConverd = (U1)PICT_GVIFIF_CNVBOX;
            break;
        case PICT_CAN_CAM_KIND_BGM:
        case PICT_CAN_CAM_KIND_SIM:
        case PICT_CAN_CAM_KIND_PVM:
        case PICT_CAN_CAM_KIND_MTM:
        case PICT_CAN_CAM_KIND_PVM_METER:
        case PICT_CAN_CAM_KIND_MTM_METER:
            bfg_Pict_StsMng.u1_CamKindConverd = (U1)PICT_GVIFIF_ADAS;
            break;

        case PICT_CAN_CAM_KIND_NONE:
            bfg_Pict_StsMng.u1_CamKindConverd = (U1)PICT_GVIFIF_NONE;
            break;
        
        default:
            /* 記憶値に従う */
            break;
    }
}


/*============================================================================
 * カメラシステム種別(ドメコン有/ドメコン無)更新
 *----------------------------------------------------------------------------
 * モジュール名 : fc_PictCtl_GvifCamKindConverdUpDate
 * 機能         : カメラシステム種別(ドメコン有/ドメコン無)更新処理
 * 処理内容     : カメラシステム種別(ドメコン有/ドメコン無)更新を行う
 * 入力(引数)   : 無し
 * 出力(戻値)   : byRlt
 * 制限事項     : 無し
 * 作成者       : NOAH)王巧燕
 * ---------------------------------------------------------------------------
 * 変更履歴     : 2023.09.12 NOAH)王巧燕 新規作成
 *              :
 ===========================================================================*/
static void vd_s_PictCtl_GvifCamKindConverdUpDate(void)
{
    switch (st_sp_Pict_BackUpInf.u1_CamKind)
    {
        case PICT_CAN_CAM_KIND_SBGM:
        bfg_Pict_StsMng.u1_GvifCamKindConverd = (U1)PICT_KIND_DOMECON_NONE;     /* ドメコン無 */
            break;
        case PICT_CAN_CAM_KIND_BGM:
        case PICT_CAN_CAM_KIND_SIM:
        case PICT_CAN_CAM_KIND_PVM:
        case PICT_CAN_CAM_KIND_MTM:
        case PICT_CAN_CAM_KIND_PVM_METER:
        case PICT_CAN_CAM_KIND_MTM_METER:
            bfg_Pict_StsMng.u1_GvifCamKindConverd = (U1)PICT_KIND_DOMECON_EXIST;        /* ドメコン有 */
            break;

        case PICT_CAN_CAM_KIND_NONE:
            bfg_Pict_StsMng.u1_GvifCamKindConverd = (U1)PICT_KIND_CAM_NONE;         /* カメラ無 */
            break;
        
        default:
            /* 記憶値に従う */
            break;
    }
}

/*===================================================================================================================================*/
/*  static U1 u1_s_PictCtl_CenterCamSizjdg(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_PictCtl_CenterCamSizjdg(void)
{
    U1 u1_t_centercamsiz;
    U1 u1_t_chgflg;
    U1 u1_t_chk;
    
    /************************************************************************************************/
    /* センターカメラサイズ判定                                                                     */
    /************************************************************************************************/
    u1_t_centercamsiz = (U1)0U;
    u1_t_chgflg = (U1)FALSE;
    Com_ReceiveSignal(ComConf_ComSignal_R_CROP_0, &u1_t_centercamsiz); /* R_CROP_0信号取得 */
    /* センターカメラサイズは有効値かを判断 */
    u1_t_chk = u1_s_PictCtl_CenterCamSizValidChk(u1_t_centercamsiz);
    if(u1_t_chk == (U1)TRUE){
        if(bfg_Pict_StsMng.st_CamDisc.u1_LastCenterCamSiz == u1_t_centercamsiz){
            if(bfg_Pict_StsMng.st_CamDisc.u1_CenterCamSizCnt < (U1)PICT_CAN_CAM_CNTMAX){
                bfg_Pict_StsMng.st_CamDisc.u1_CenterCamSizCnt++;
            }
        }
        else{
            bfg_Pict_StsMng.st_CamDisc.u1_CenterCamSizCnt = (U1)PICT_SAMECNT_FIRST;
        }

        /* ラストセンターカメラサイズ更新 */
        bfg_Pict_StsMng.st_CamDisc.u1_LastCenterCamSiz = u1_t_centercamsiz;
            /* 3回連続受信したセンターカメラサイズが一致の場合、センターカメラサイズ確定 */
        if(bfg_Pict_StsMng.st_CamDisc.u1_CenterCamSizCnt >= (U1)PICT_CAN_CAM_CNTMAX)
        {
            if(st_sp_Pict_BackUpInf.u1_CenterCamSiz != u1_t_centercamsiz){
                st_sp_Pict_BackUpInf.u1_CenterCamSiz = u1_t_centercamsiz;
                /*  センターカメラサイズ変更フラグ：ON */
                u1_t_chgflg = (U1)TRUE;
            }
            bfg_Pict_StsMng.st_CamDisc.u1_CenterCamSizCnt = (U1)PICT_SAMECNT_INI;
        }
    }
    return(u1_t_chgflg);
}

/*============================================================================
 * センターカメラサイズは有効値かを判断する処理
 *----------------------------------------------------------------------------
 * モジュール名 : fc_PictCtl_CenterCamSizValidChk
 * 機能         : センターカメラサイズは有効値かを判断する
 * 処理内容     : センターカメラサイズは有効値かを判断する
 * 入力(引数)   : u1_CenterCamSiz:センターカメラサイズ
 * 出力(戻値)   : byRlt：有効/無効
 * 制限事項     : 無し
 * 作成者       : NOAH)王巧燕
 * ---------------------------------------------------------------------------
 * 変更履歴     : 2023.11.21 NOAH)王巧燕 新規作成
 *              : 
 ===========================================================================*/
static U1 u1_s_PictCtl_CenterCamSizValidChk(U1 u1_a_CenterCamSiz)
{
    U1 u1_t_valid;
    switch (u1_a_CenterCamSiz)
    {
        case PICT_CAN_CAM_SIZE_1920X1080:
        case PICT_CAN_CAM_SIZE_1920X954:
        case PICT_CAN_CAM_SIZE_1920X900:
        case PICT_CAN_CAM_SIZE_1920X720:
        case PICT_CAN_CAM_SIZE_1280X846:
        case PICT_CAN_CAM_SIZE_1280X720:
        case PICT_CAN_CAM_SIZE_1280x621:
        case PICT_CAN_CAM_SIZE_1696X954:
        case PICT_CAN_CAM_SIZE_1104X621:
        case PICT_CAN_CAM_SIZE_1672x720:
        case PICT_CAN_CAM_SIZE_RESERVE1:
        case PICT_CAN_CAM_SIZE_RESERVE2:
        case PICT_CAN_CAM_SIZE_RESERVE3:
        case PICT_CAN_CAM_SIZE_RESERVE4:
        case PICT_CAN_CAM_SIZE_RESERVE5:
            u1_t_valid = (U1)TRUE;      /*有効値*/
            break;

        case PICT_CAN_CAM_SIZE_NONE:
        default:
            u1_t_valid = (U1)FALSE;     /*無効値*/
            break;
    }
    return(u1_t_valid);
}

/*============================================================================
 * データバックアップ処理
 *----------------------------------------------------------------------------
 * モジュール名 : fc_PictCtl_Bkup_Write
 * 機能         : データバックアップ処理
 * 処理内容     : データバックアップ処理
 * 入力（引数） : 無し
 * 出力（戻値） : 無し
 * 制限事項     : 無し
 * 作成者       : NOAH)王 巧燕
 * ---------------------------------------------------------------------------
 * 変更履歴     : 2023.10.25  新規作成
 * 変更者       : 
 *              : 
 ===========================================================================*/
static void vd_s_PictCtl_Bkup_Write(void)
{
    U1 u1_t_CamKind;
    U1 u1_t_CenterCamSiz;

    /* カメラシステム種別 */
    u1_t_CamKind = st_sp_Pict_BackUpInf.u1_CamKind;
    /* 表示用映像サイズ */
    u1_t_CenterCamSiz = st_sp_Pict_BackUpInf.u1_CenterCamSiz;

    /* DTFへ記憶要求(暫定) */
}

/*===================================================================================================================================*/
/*  static void vd_s_PictCtl_CamAreaChk(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PictCtl_CamAreaChk(void)
{
    if((u1_s_pict_regwrite_req == (U1)TRUE) || (u1_s_pict_regwrite_sts != (U1)PICT_ML_CAMAREASET_COMPLETED)){
        u1_s_pict_regwrite_sts = u1_g_Pict_MlCamAreaSet();
        if(u1_s_pict_regwrite_sts == (U1)PICT_ML_CAMAREASET_READY){
            u1_s_pict_regwrite_req = (U1)FALSE;
        }
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_PictCtl_CanInputChk(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PictCtl_CanInputChk(void)
{
    vd_s_PictCtl_StrgwhlChk();
    vd_s_PictCtl_SetTim((U1)PICT_TIMID_CANSIGNAL_GETCYC, (U2)PICT_TIMER_CANSIGNAL_GETCYC);
}

/*===================================================================================================================================*/
/*  static void vd_s_PictCtl_StrgwhlChk(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PictCtl_StrgwhlChk(void)
{
    U1 u1_t_sig;
    U1 u1_t_msgsts;
    U1 u1_t_handle;
    
    u1_t_sig = (U1)0U;
    u1_t_msgsts = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_BDB1S08_CH0,
                                    (U4)OXCAN_SYS_PNC_16 | (U4)OXCAN_SYS_PNC_40 | (U4)OXCAN_SYS_PNC_43 | (U4)OXCAN_SYS_PNC_44 | \
                                    (U4)OXCAN_SYS_PBA | (U4)OXCAN_SYS_ACC | (U4)OXCAN_SYS_IGR | (U4)OXCAN_SYS_IGP,
                                    (U2)PICT_TIM_BDB1S08_FAILTIM) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    if(u1_t_msgsts == (U1)0U){
        (void)Com_ReceiveSignal(ComConf_ComSignal_STRG_WHL, &u1_t_sig);
        if(u1_t_sig < (U1)PICT_STRG_WHL_MAX){
            u1_t_handle = u1_sp_PICT_HANDLE_TBL[u1_t_sig];
            vd_s_PictCtl_StrgwhlUpdate(u1_t_handle);
        }
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_PictCtl_StrgwhlUpdate(const U1 u1_a_HANDLE)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PictCtl_StrgwhlUpdate(const U1 u1_a_HANDLE)
{
    if(u1_a_HANDLE != st_sp_Pict_BackUpInf.u1_handle){
        if((u1_a_HANDLE == (U1)PICT_HANDLE_RIGHT) || (st_sp_Pict_BackUpInf.u1_handle !=(U1)PICT_HANDLE_UNKNOWN)){
            u1_s_pict_regwrite_req = (U1)TRUE;
        }
        st_sp_Pict_BackUpInf.u1_handle = u1_a_HANDLE;
    }
}

/*===================================================================================================================================*/
/*  U1 u1_g_PictCtl_CamSizeSts(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1 u1_g_PictCtl_CamSizeSts(void)
{
    return(st_sp_Pict_BackUpInf.u1_CenterCamSiz);
}

/*===================================================================================================================================*/
/*  U1 u1_g_PictCtl_CamKindSts(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1 u1_g_PictCtl_CamKindSts(void)
{
    return(bfg_Pict_StsMng.u1_CamKindConverd);
}

/*===================================================================================================================================*/
/*  U1 u1_g_PictCtl_GvifCamKindSts(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1 u1_g_PictCtl_GvifCamKindSts(void)
{
    return(bfg_Pict_StsMng.u1_GvifCamKindConverd);
}

/*===================================================================================================================================*/
/*  U1 u1_g_PictCtl_RcvQualModeRevFlgSts(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1 u1_g_PictCtl_RcvQualModeRevFlgSts(void)
{
    return(bfg_Pict_StsMng.u1_RcvQualModeFlg);
}

/*===================================================================================================================================*/
/*  U1 u1_g_PictCtl_RcvQualModeRevDate(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1 u1_g_PictCtl_RcvQualModeRevDate(void)
{
    return(bfg_Pict_StsMng.u1_RcvQualModeDate);
}

/*===================================================================================================================================*/
/*  U1 u1_g_PictCtl_handleSts(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1 u1_g_PictCtl_handleSts(void)
{
    U1 u1_t_return;
    
    u1_t_return = st_sp_Pict_BackUpInf.u1_handle;
    
    if((st_sp_Pict_BackUpInf.u1_handle != PICT_HANDLE_LEFT) &&
       (st_sp_Pict_BackUpInf.u1_handle != PICT_HANDLE_RIGHT)){
        u1_t_return = (U1)PICT_HANDLE_LEFT;
    }
    
    return(u1_t_return);
}

/*============================================================================
 * カメラ種別判別通知要求イベント処理
 *----------------------------------------------------------------------------
 * モジュール名 : fc_PictCtl_RcvTabPwCamKindReq
 * 機能         : カメラ種別判別通知要求イベント処理
 * 処理内容     : カメラ種別判別通知要求イベント処理
 * 入力(引数)   : 無し
 * 出力(戻値)   : 無し
 * 制限事項     : 無し
 * 作成者       : NOAH)馬孝康
 * ---------------------------------------------------------------------------
 * 変更履歴     : 2022.06.14 新規作成
 *              : 
 ===========================================================================*/
static void vd_s_PictCtl_CamKindNtyChk(void)
{
    /* 情報変更あるかチェック */
    if((st_sp_send.u1_CamKind != st_sp_Pict_BackUpInf.u1_CamKind)
      ||(st_sp_send.u1_CenterCamSiz != st_sp_Pict_BackUpInf.u1_CenterCamSiz)
      ||(st_sp_send.u1_DispReqGpio0Sts != bfg_Pict_StsMng.u1_DispReqGpio0Sts))
      {
        /* カメラ種別判別通知 送信 */
        vd_s_PictCtl_CamKindNtySnd();

        /* 前回状態更新 */
        st_sp_send.u1_CamKind = st_sp_Pict_BackUpInf.u1_CamKind;
        st_sp_send.u1_CenterCamSiz = st_sp_Pict_BackUpInf.u1_CenterCamSiz;
        st_sp_send.u1_DispReqGpio0Sts = bfg_Pict_StsMng.u1_DispReqGpio0Sts;
      }

}

/*============================================================================
 * カメラ種別判別通知 送信
 *----------------------------------------------------------------------------
 * モジュール名 : fc_PictCtl_CamKindNtySnd
 * 機能         : カメラ種別判別通知 送信
 * 処理内容     : カメラ種別判別通知 送信
 * 入力（引数） : 無し
 * 出力（戻値） : 無し
 * 制限事項     : 無し
 * 作成者       : NOAH)馬
 * ---------------------------------------------------------------------------
 * 変更履歴     : 2022.06.14  新規作成
 * 変更者       : 
 *              : 
 ===========================================================================*/
static void vd_s_PictCtl_CamKindNtySnd(void)
{
    ST_XSPI_IVI_MISC_CAMERA_DATA    st_t_send;

    /* カメラ種別設定 */
    st_t_send.u1_camera_type = st_sp_Pict_BackUpInf.u1_CamKind;

    /* センターカメラサイズ情報設定 */
    st_t_send.u1_center_camera_size = st_sp_Pict_BackUpInf.u1_CenterCamSiz;
    /* メータカメラサイズ情報設定   */
    st_t_send.u1_met_camera_size = (U1)PICT_METER_CAM_SIZE_UNFIX;

    /* DISP-REQ-GPIO0検知状態設定 */
    if(bfg_Pict_StsMng.u1_DispReqGpio0Sts == (U1)PICT_POLLPORT_ON) {
        st_t_send.u1_disp_gpio0 = (U1)PICT_CAM_DET_ON;
    } else if(bfg_Pict_StsMng.u1_DispReqGpio0Sts == (U1)PICT_POLLPORT_OFF) {
        st_t_send.u1_disp_gpio0 = (U1)PICT_CAM_DET_OFF;
    } else {        
        st_t_send.u1_disp_gpio0 = (U1)PICT_CAM_DET_UNFIX;
    }

    /* MET-REQ-GPIO1検知状態設定 */
    st_t_send.u1_met_gpio1 = (U1)PICT_CAM_DET_UNFIX;

    /*************************************************/
    /*                 送信                          */
    /*************************************************/
    vd_g_XspiIviSub1CameraDataSend(st_t_send);

    /* カメラ種別判別通知定期送信タイマを再セット */
    vd_s_PictCtl_SetTim((U1)PICT_TIMID_CAMKIND_SENDCYC, (U2)PICT_TIMER_TABCMD_SENDCYC);
}

/*===================================================================================================================================*/
/*  void vd_g_PictCtl_RcvDiagModInd(const U1 u1_a_MODE)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_PictCtl_RcvDiagModInd(const U1 u1_a_MODE)
{
    U1 u1_t_act_flg;
    U1 u1_t_cam_mode;

    u1_t_act_flg = (U1)TRUE;

    /* パラメータチェック */
    if(u1_a_MODE > PICT_DIAG_MOD_CAMON){
        u1_t_act_flg = (U1)FALSE;
    }

    /* ダイアグモード差分チェック */
    if(bfg_Pict_StsMng.u1_DiagMode == u1_a_MODE){
        u1_t_act_flg = (U1)FALSE;
    }

    u1_t_cam_mode = u1_g_PictCtl_CamStsGet();
    if((u1_t_cam_mode == (U1)TRUE)&&(u1_a_MODE == PICT_DIAG_MOD_CAMON)){
        /* カメラダイアグモード⇔カメラモード間の遷移は顧客仕様にて禁止されている */
        u1_t_act_flg = (U1)FALSE;
    }

    if(u1_t_act_flg == (U1)TRUE){
        /* カメラダイアグモードON */
        if((bfg_Pict_StsMng.u1_DiagMode != (U1)PICT_DIAG_MOD_CAMON) &&(u1_a_MODE == (U1)PICT_DIAG_MOD_CAMON)){
            /* カメラダイアグモード⇔カメラモード間の遷移が禁止されている */
            if(u1_t_cam_mode == (U1)FALSE){
                /* 画質モード通知(カメラ以外)受信停止 */
                bfg_Pict_StsMng.u1_RcvNoCamQualModeFlg = (U1)PICT_RCV_NOCAMQUAL_STOP;
                /*  T_SIP_NOTIF_OUT待ちタイマ停止 */
                vd_s_PictCtl_ClrTim((U1)PICT_TIMID_ML_T_SIP_NOTIF_OUT);
                /* カメラへ切替シーケンス要求 */
                vd_s_PictCtl_SetMlSeqReq((U1)PICT_SEQ_ML_CAMONCHG);
            }
        }
        /* カメラダイアグモードOFF(カメラダイアグモードON→ダイアグモードON) */
        else if((bfg_Pict_StsMng.u1_DiagMode == (U1)PICT_DIAG_MOD_CAMON) && (u1_a_MODE == (U1)PICT_DIAG_MOD_ON)){
            /* カメラON⇒カメラOFFの処理 */
            vd_s_PictCtl_CamChgOn2Off();
        }
        /* カメラダイアグモードOFF(カメラダイアグモードON→ダイアグモードOFF) */
        else if((bfg_Pict_StsMng.u1_DiagMode == (U1)PICT_DIAG_MOD_CAMON) && (u1_a_MODE == (U1)PICT_DIAG_MOD_OFF)){
            /* DISP-REQ-GPIO0=Hiの場合、カメラ以外へ切替シーケンス要求 */
            if(bfg_Pict_StsMng.u1_DispReqGpio0Sts == (U1)PICT_POLLPORT_ON){
                /* カメラへ切替シーケンス要求 */
                vd_s_PictCtl_SetMlSeqReq((U1)PICT_SEQ_ML_CAMONCHG);
            }
            else{
                /* カメラON⇒カメラOFFの処理 */
                vd_s_PictCtl_CamChgOn2Off();
            }
        }
        /* ダイアグモードOFF(ダイアグモードON→ダイアグモードOFF) */
        else if((bfg_Pict_StsMng.u1_DiagMode == (U1)PICT_DIAG_MOD_ON) && (u1_a_MODE == (U1)PICT_DIAG_MOD_OFF)){
            /* DISP-REQ-GPIO0=Hiの場合、カメラ以外へ切替シーケンス要求 */
            if (bfg_Pict_StsMng.u1_DispReqGpio0Sts == (U1)PICT_POLLPORT_ON){
                /* カメラへ切替シーケンス要求 */
                vd_s_PictCtl_SetMlSeqReq((U1)PICT_SEQ_ML_CAMONCHG);
            }
        }
        /* その他 */
        else{
            /* 何にもしない */
        }
        /* ダイアグモード更新 */
        bfg_Pict_StsMng.u1_DiagMode = u1_a_MODE;
    }
}

/*===================================================================================================================================*/
/*  static void    vd_s_PictCtl_CdsizeChk(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PictCtl_CdsizeChk(void)
{
    U1  u1_t_cnt;
    U1  u1_t_pre_sig;
    U1  u1_t_cdsize;
    
    u1_t_pre_sig = (U1)PICT_CD_SIZE_INVALID;
    u1_t_cdsize = (U1)PICT_CD_SIZE_INVALID;
    
    if(u1_s_pict_mvdisp_exsit == (U1)TRUE){/* 可動有り */
        if((u1_s_pict_dispsize == (U1)PICT_SIZE_140IN) &&
            (u1_s_pict_heacon == (U1)PICT_AIS_KIND_HEACON) &&
            (bfg_Pict_StsMng.u1_CamKindConverd == (U1)PICT_GVIFIF_ADAS)){/* 14inかつADC内臓かつヒーコン統合 */
            u1_t_cdsize = (U1)PICT_CD_SIZE_1920X954_140IN;
        }
        
    }
    else{/* 可動無し */
        for(u1_t_cnt = (U1)0U; u1_t_cnt < (U1)PICT_CD_SIZE_TBLNUM; u1_t_cnt++){
            if((u1_s_pict_dispsize == st_sp_PICT_CDSIZE_TBL[u1_t_cnt].u1_size) &&
                (u1_s_pict_heacon == st_sp_PICT_CDSIZE_TBL[u1_t_cnt].u1_ais) &&
                (bfg_Pict_StsMng.u1_CamKindConverd == st_sp_PICT_CDSIZE_TBL[u1_t_cnt].u1_camkind)){
                u1_t_cdsize = st_sp_PICT_CDSIZE_TBL[u1_t_cnt].u1_cdsize_sig;
                break;
            }
        }
    }
    u1_s_pict_cd_size = u1_t_cdsize;

    (void)Com_ReceiveSignal(ComConf_ComSignal_CD_SIZE , &u1_t_pre_sig);
    if(u1_t_pre_sig != u1_s_pict_cd_size){
        (void)Com_SendSignal(ComConf_ComSignal_CD_SIZE , &u1_s_pict_cd_size);
        Com_TriggerIPDUSend((PduIdType)MSG_AVN1S73_TXCH0);
        vd_g_SysEcDrc_Drec((U1)SYSECDRC_DREC_CAT_CAMCTL, (U1)PICT_DRCID_CD_SIZE, u1_s_pict_cd_size, (U1)0x00U);
        vd_g_PictLogCtl_LogReq((U1)PICTLOGCTL_POINT_CD_SIZE);
    }
}

/*===================================================================================================================================*/
/*  U1    u1_g_PictCtl_CdsizeSnd(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1 u1_g_PictCtl_CdsizeSnd(void)
{
    return(u1_s_pict_cd_size);
}

/*===================================================================================================================================*/
/*  void vd_g_PictCtl_VmResetReq(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_PictCtl_VmResetReq(void)
{
    U1 u1_t_vicrset;
    U1 u1_t_gvifrset;

    u1_t_vicrset = (U1)Dio_ReadChannel((U1)PICT_PORT_V_IC_RST);
    u1_t_gvifrset = (U1)Dio_ReadChannel((U1)PICT_PORT_GVIF_CAM_RST);
    
    if(bfg_Pict_StsMng.u1_DiagMode == (U1)PICT_DIAG_MOD_CAMON) {
        u1_s_pict_reset_req = (U1)PICT_RESETREQ_ON;
        vd_s_PictCtl_MmresetSndChk();
    }
    
    if(u1_t_vicrset == (U1)TRUE){
        u1_s_pict_mipi_chg_flg |= (U1)PICT_MIPI_OUT_VMRESET;
        u1_s_pict_vmresetchk_step = (U1)PICT_SEQ_VMRESETCHK_STEP0;
        u1_s_pict_vmrsttimeoutcnt = (U1)PICT_TIMEOUTCNT_START;
    }
    else if(u1_t_gvifrset == (U1)TRUE){
        (void)u1_g_Gvif3SipFail();
        u1_s_pict_vmresetchk_step = (U1)PICT_SEQ_VMRESETCHK_STEP1;
        u1_s_pict_vmrsttimeoutcnt = (U1)PICT_TIMEOUTCNT_START;
        
    }
    else{
        u1_s_pict_vmresetchk_step = (U1)PICT_SEQ_VMRESETCHK_STEP_FIN;
        u1_s_pict_vmrsttimeoutcnt = (U1)PICT_MIPITIMECNT_OFFOUT3;
    }
}

/*===================================================================================================================================*/
/*  void vd_g_PictCtl_SocResetReq(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_PictCtl_SocResetReq(void)
{
    if(bfg_Pict_StsMng.u1_DiagMode == (U1)PICT_DIAG_MOD_CAMON) {
        u1_s_pict_reset_req = (U1)PICT_RESETREQ_ON;
        vd_s_PictCtl_MmresetSndChk();
    }

    u1_s_pict_socreset_req = (U1)PICT_SOCRESET_REQ;

}

/*===================================================================================================================================*/
/*  void vd_g_PictCtl_CdcResetReq(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_PictCtl_CdcResetReq(void)
{
    U1  u1_t_mode;
    
    u1_t_mode   = u1_g_PictCtl_CamStsGet();
    if(u1_t_mode == (U1)FALSE){
        u1_s_pict_cdcreset_req = (U1)PICT_CDCRESET_REQ;
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_PictCtl_Bcc1s05Timeout(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PictCtl_Bcc1s05Timeout(void)
{
    u1_s_pict_reset_req = (U1)PICT_RESETREQ_OFF;
    vd_s_PictCtl_MmresetSndChk();
}

/*===================================================================================================================================*/
/*  static void    vd_s_PictCtl_PvmreqChk(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PictCtl_MmresetSndChk(void)
{
    U4  u4_t_power_sts;
    U1  u1_t_now_mmreset;
    U1  u1_t_pre_mmreset;
    U1  u1_t_rmdisp;
    
    u4_t_power_sts = u4_g_VehopemdMdfield();
    u1_t_now_mmreset = (U1)PICT_MM_RESET_OFF;
    u1_t_pre_mmreset = (U1)PICT_MM_RESET_OFF;
    u1_t_rmdisp = (U1)PICT_RM_DISP_OFF;
    
    (void)Com_ReceiveSignal(ComConf_ComSignal_RM_DISP, &u1_t_rmdisp);
    if((u1_t_rmdisp == (U1)PICT_RM_DISP_ON) && 
       (u1_s_pict_reset_req == (U1)PICT_RESETREQ_ON) &&
       ((bfg_Pict_StsMng.u1_DispReqGpio0Sts == (U1)PICT_POLLPORT_OFF))){
        u1_t_now_mmreset = (U1)PICT_MM_RESET_ON;
    }
    else{
        u1_t_now_mmreset = (U1)PICT_MM_RESET_OFF;
        u1_s_pict_reset_req = (U1)PICT_RESETREQ_OFF;
    }

    if((u4_t_power_sts == (U4)PICT_VEHOPE_STS_POWERON) ||
       (u4_t_power_sts == (U4)PICT_VEHOPE_STS_POWERON_STOP)){
        (void)Com_ReceiveSignal(ComConf_ComSignal_MM_RESET , &u1_t_pre_mmreset);
        if(u1_t_pre_mmreset != u1_t_now_mmreset){
            u1_s_pict_mm_reset = u1_t_now_mmreset;
            (void)Com_SendSignal(ComConf_ComSignal_MM_RESET , &u1_t_now_mmreset);
            Com_TriggerIPDUSend((PduIdType)MSG_AVN1S73_TXCH0);
        }
    }
}

/*===================================================================================================================================*/
/*  U1    u1_g_PictCtl_MmresetSnd(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1 u1_g_PictCtl_MmresetSnd(void)
{
    return(u1_s_pict_mm_reset);
}

/*===================================================================================================================================*/
/*  U1    u1_g_PictCtl_CdcRstCancelSts(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1 u1_g_PictCtl_CdcRstCancelSts(void)
{
    U1  u1_t_return;
    U1  u1_t_mode;
    
    u1_t_return = (U1)FALSE;
    u1_t_mode   = u1_g_PictCtl_CamStsGet();
    
    if((u1_t_mode == (U1)TRUE) ||
       (bfg_Pict_StsMng.u1_DiagMode == (U1)PICT_DIAG_MOD_CAMON)){
        u1_t_return = (U1)TRUE;
    }
    
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static void vd_s_PictCtl_MutelogChk(const U1 u1_a_KIND)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PictCtl_MutelogChk(const U1 u1_a_KIND)
{
    u1_s_pict_mutelog_flg &= (U1)(PICT_MUTEFLG_ALL | PICT_MUTEFLG_NOAIS);
    
    if(u1_a_KIND == (U1)PICT_MUTEOFFREQ_NOAIS){
        u1_s_pict_mutelog_flg &= ~(U1)PICT_MUTEFLG_NOAIS;
        if(u1_s_pict_mutelog_flg == (U1)PICT_MUTEFLG_OFF){
            vd_g_PictLogCtl_LogReq((U1)PICTLOGCTL_POINT_MUTE_OFF);
        }
    }
    else if(u1_a_KIND == (U1)PICT_MUTEOFFREQ_ALLOFF){
        u1_s_pict_mutelog_flg &= ~(U1)PICT_MUTEFLG_ALL;
        if(u1_s_pict_mutelog_flg == (U1)PICT_MUTEFLG_OFF){
            vd_g_PictLogCtl_LogReq((U1)PICTLOGCTL_POINT_MUTE_OFF);
        }
    }
    else if(u1_a_KIND == (U1)PICT_MUTEONREQ_NOAIS){
        if(u1_s_pict_mutelog_flg == (U1)PICT_MUTEFLG_OFF){
            vd_g_PictLogCtl_LogReq((U1)PICTLOGCTL_POINT_MUTE_ON);
        }
        u1_s_pict_mutelog_flg |= (U1)PICT_MUTEFLG_NOAIS;
    }
    else{
        if(u1_s_pict_mutelog_flg == (U1)PICT_MUTEFLG_OFF){
            vd_g_PictLogCtl_LogReq((U1)PICTLOGCTL_POINT_MUTE_ON);
        }
        u1_s_pict_mutelog_flg |= (U1)PICT_MUTEFLG_ALL;
    }
    
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  0.0.0    01/27/2025  TN       New.                                                                                               */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*  * TN   = Tatsuya Niimi, KSE                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/
