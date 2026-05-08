/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "CXD4937Ctl.h"

#include "Dio.h"
#include "gpi2c_ma.h"
#include "Mcu_I2c_Ctrl_private.h"
#include "gpt_drv_frt.h"
#include "Dio.h"
#include "Dio_Symbols.h"

#include "ML86294Ctl.h"
#include "x_spi_ivi_sub1_power.h"
#include "x_spi_ivi_sub1_hdmi.h"
#include "memcpy_u1.h"
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GVIFSENDER_TASK_TIME                (1U)

#define GVIFSENDER_SEQ_IDLE                 (0U)
#define GVIFSENDER_SEQ_CYC                  (1U)
#define GVIFSENDER_SEQ_DEVRST               (2U)
#define GVIFSENDER_SEQ_LINKCHK              (3U)

#define GVIFSNDR_CYCCHK_STEP0               (0U)
#define GVIFSNDR_CYCCHK_STEP1               (1U)
#define GVIFSNDR_CYCCHK_STEP2               (2U)
#define GVIFSNDR_CYCCHK_STEP3               (3U)
#define GVIFSNDR_CYCCHK_STEP4               (4U)
#define GVIFSNDR_CYCCHK_STEP5               (5U)
#define GVIFSNDR_CYCCHK_STEP6               (6U)
#define GVIFSNDR_CYCCHK_STEP7               (7U)
#define GVIFSNDR_CYCCHK_STEP8               (8U)
#define GVIFSNDR_CYCCHK_STEP9               (9U)
#define GVIFSNDR_CYCCHK_STEP10              (10U)
#define GVIFSNDR_CYCCHK_STEP11              (11U)
#define GVIFSNDR_CYCCHK_STEP12              (12U)
#define GVIFSNDR_CYCCHK_STEP13              (13U)
#define GVIFSNDR_CYCCHK_STEP14              (14U)
#define GVIFSNDR_CYCCHK_STEP15              (15U)
#define GVIFSNDR_CYCCHK_STEP16              (16U)
#define GVIFSNDR_CYCCHK_STEP17              (17U)
#define GVIFSNDR_CYCCHK_STEP18              (18U)
#define GVIFSNDR_CYCCHK_STEP19              (19U)
#define GVIFSNDR_CYCCHK_STEP20              (20U)
#define GVIFSNDR_CYCCHK_STEP21              (21U)
#define GVIFSNDR_CYCCHK_STEP22              (22U)
#define GVIFSNDR_CYCCHK_STEP23              (23U)
#define GVIFSNDR_CYCCHK_STEP24              (24U)
#define GVIFSNDR_CYCCHK_STEP25              (25U)
#define GVIFSNDR_CYCCHK_STEP26              (26U)
#define GVIFSNDR_CYCCHK_STEP27              (27U)
#define GVIFSNDR_CYCCHK_STEP28              (28U)

#define CXD4937_BANKSET_WRINUM              (1U)
#define CXD4937_GVIFSNDRHDCPSTOP_WRINUM     (4U)
#define CXD4957_GVIFSNDRERRCLEAR_SET_WRINUM (1U)
#define CXD4937_GVIFSNDREDPERR_SET1_WRINUM  (2U)
#define CXD4937_GVIFSNDREDPERR_SET2_WRINUM  (1U)

#define GVIFSENDER_DEVRST_STEP0             (0U)
#define GVIFSENDER_DEVRST_STEP1             (1U)

#define GVIFSENDER_LINKCHK_STEP0            (0U)
#define GVIFSENDER_LINKCHK_STEP1            (1U)
#define GVIFSENDER_LINKCHK_STEP2            (2U)
#define GVIFSENDER_LINKCHK_STEP3            (3U)
#define GVIFSENDER_LINKCHK_STEP4            (4U)

/* Port */
#define MCU_PORT_GVIF_CDISP_RST         (DIO_ID_PORT17_CH4)     /* /GVIF-TX(C-DISP)-RST */
#define GVIF3TX_PORT_CDISP_WAKE         (DIO_ID_PORT2_CH0)      /* GVIF-TX(C-DISP)-WAKE */
/* FRT */
#define MCU_FRT_1MS                     (1000U * GPT_FRT_1US)

/* シフト演算 */
#define MCU_SFT_7                       (7U)

/* GVIF3送信制御仕様 */
#define MCU_STEP_GVIF3TX_eDPSET_1       (1U)    /* 100-4-3.eDP設定フロー START~eDPポート設定 */
#define MCU_STEP_GVIF3TX_eDPSET_2       (2U)    /* 100-4-3.eDP設定フロー eDP用レジスタ設定 10-5-3 レシーバ */
#define MCU_STEP_GVIF3TX_eDPSET_3       (3U)    /* 100-4-3.eDP設定フロー eDP用レジスタ設定 10-5-3 DPCD */
#define MCU_STEP_GVIF3TX_eDPSET_4       (4U)    /* 100-4-3.eDP設定フロー EDID選択設定 */
#define MCU_STEP_GVIF3TX_eDPSET_5       (5U)    /* 100-4-3.eDP設定フロー Bank切り替え（Bank0）~Bank切り替え（Bank4） */
#define MCU_STEP_GVIF3TX_eDPSET_6       (6U)    /* 100-4-3.eDP設定フロー eDP用レジスタ設定 10-5-5 Hot Plug Detect */
#define MCU_STEP_GVIF3TX_eDPSET_FIN     (7U)

#define MCU_WRINUM_GVIF3TX_INISET       (11U)   /* 100-4-2.初期設定フロー レジスタ書込み回数 */
#define MCU_WRINUM_GVIF3TX_eDPSET_1     (2U)    /* 100-4-3.eDP設定フロー START～eDPポート設定 レジスタ書込み回数 */
#define MCU_WRINUM_GVIF3TX_eDPSET_2     (115U)  /* 100-4-3.eDP設定フロー eDP用レジスタ設定 10-5-3 レシーバ レジスタ書込み回数 */
#define MCU_WRINUM_GVIF3TX_eDPSET_3     (26U)   /* 100-4-3.eDP設定フロー eDP用レジスタ設定 10-5-3 DPCD レジスタ書込み回数 */
#define MCU_WRINUM_GVIF3TX_eDPSET_4     (1U)    /* 100-4-3.eDP設定フロー EDID選択設定 レジスタ書込み回数 */
#define MCU_WRINUM_GVIF3TX_eDPSET_5     (3U)    /* 100-4-3.eDP設定フロー Bank切り替え（Bank0）~Bank切り替え（Bank4） レジスタ書込み回数 */
#define MCU_WRINUM_GVIF3TX_eDPSET_6     (3U)    /* 100-4-3.eDP設定フロー eDP用レジスタ設定 10-5-5 Hot Plug Detect レジスタ書込み回数 */

#define MCU_STEP_GVIF3TX_OUTSET_1       (1U)    /* 100-4-4.出力設定フロー Bank切り替え（Bank0） */
#define MCU_STEP_GVIF3TX_OUTSET_2       (2U)    /* 100-4-4.出力設定フロー A点～GVIF3出力ON設定 */
#define MCU_STEP_GVIF3TX_OUTSET_3       (3U)    /* 100-4-4.出力設定フロー Wati t4 */
#define MCU_STEP_GVIF3TX_OUTSET_4       (4U)    /* 100-4-4.出力設定フロー GVIF3リンク確立確認 レジスタRead */
#define MCU_STEP_GVIF3TX_OUTSET_5       (5U)    /* 100-4-4.出力設定フロー リンク確立判定 */
#define MCU_STEP_GVIF3TX_OUTSET_6       (6U)    /* 100-4-4.出力設定フロー Bank切り替え（Bank7）～エラークリア解除設定 */
#define MCU_STEP_GVIF3TX_OUTSET_STP     (7U)
#define MCU_STEP_GVIF3TX_OUTSET_FIN     (8U)

#define MCU_WRINUM_GVIF3TX_OUTSET_1     (1U)    /* 100-4-4.出力設定フロー A点～Wati t4 レジスタ書込み回数 */
#define MCU_WRINUM_GVIF3TX_OUTSET_2     (4U)    /* 100-4-4.出力設定フロー Bank切り替え（Bank7）～エラークリア解除設定 レジスタ書込み回数 */
#define MCU_WRINUM_GVIF3TX_OUTSET_3     (1U)    /* 100-4-4.出力設定フロー Bank切り替え（Bank0） レジスタ書込み回数 */

#define MCU_STEP_GVIF3TX_HDCP_01        (1U)    /* 100-4-5.(C-Disp) HDCP認証フロー[1/7] B点～バックチャネルGPIO1確認 */
#define MCU_STEP_GVIF3TX_HDCP_02        (2U)    /* 100-4-5.(C-Disp) HDCP認証フロー[1/7] Wait t4 */
#define MCU_STEP_GVIF3TX_HDCP_03        (3U)    /* 100-4-5.(C-Disp) HDCP認証フロー[1/7][6/7] GVIF3リンク確立確認レジスタRead */
#define MCU_STEP_GVIF3TX_HDCP_04        (4U)    /* 100-4-5.(C-Disp) HDCP認証フロー[1/7][6/7] リンク確立完了判定処理～次状態へ遷移 */
#define MCU_STEP_GVIF3TX_HDCP_05        (5U)    /* 100-4-5.(C-Disp) HDCP認証フロー[1/7] Bank切り替え（Bank4）～[2/7] HDCPTX Connect 1 設定 */
#define MCU_STEP_GVIF3TX_HDCP_06        (6U)    /* 100-4-5.(C-Disp) HDCP認証フロー[2/7] C点～HDCP認証コマンド発行（HDCP_AUTH_REQコマンド発行） */
#define MCU_STEP_GVIF3TX_HDCP_07        (7U)    /* 100-4-5.(C-Disp) HDCP認証フロー[2/7] HDCPTXステータスモニタRead */
#define MCU_STEP_GVIF3TX_HDCP_08        (8U)    /* 100-4-5.(C-Disp) HDCP認証フロー[2/7] HDCP認証処理状態確認判定～次状態へ遷移 */
#define MCU_STEP_GVIF3TX_HDCP_09        (9U)    /* 100-4-5.(C-Disp) HDCP認証フロー[3/7] HDCP認証待ちタイマースタート */
#define MCU_STEP_GVIF3TX_HDCP_10        (10U)   /* 100-4-5.(C-Disp) HDCP認証フロー[3/7] E点～HDCPTXイベントモニタRead */
#define MCU_STEP_GVIF3TX_HDCP_11        (11U)   /* 100-4-5.(C-Disp) HDCP認証フロー[3/7] HDCP認証待ちタイマー,HDCPTXイベントモニタ判定～次状態へ遷移, */
#define MCU_STEP_GVIF3TX_HDCP_12        (12U)   /* 100-4-5.(C-Disp) HDCP認証フロー[3/7] K点～イベントクリア */
#define MCU_STEP_GVIF3TX_HDCP_13        (13U)   /* 100-4-5.(C-Disp) HDCP認証フロー[3/7] デバイス数の確認～接続段数の確認 */
#define MCU_STEP_GVIF3TX_HDCP_14        (14U)   /* 100-4-5.(C-Disp) HDCP認証フロー[4/7] Receiver ID取得 */
#define MCU_STEP_GVIF3TX_HDCP_15        (15U)   /* 100-4-5.(C-Disp) HDCP認証フロー[4/7] F点～Bank切り替え（Bank4） */
#define MCU_STEP_GVIF3TX_HDCP_16        (16U)   /* 100-4-5.(C-Disp) HDCP認証フロー[4/7] eDP用レジスタ設定 100-5-5.Hot Plug Detect */
#define MCU_STEP_GVIF3TX_HDCP_17        (17U)   /* 100-4-5.(C-Disp) HDCP認証フロー[5/7] Bank切り替え（Bank0） */
#define MCU_STEP_GVIF3TX_HDCP_18        (18U)   /* 100-4-5.(C-Disp) HDCP認証フロー[5/7] Wait t7 */
#define MCU_STEP_GVIF3TX_HDCP_19        (19U)   /* 100-4-5.(C-Disp) HDCP認証フロー[5/7] 映像信号入力確認 レジスタRead */
#define MCU_STEP_GVIF3TX_HDCP_20        (20U)   /* 100-4-5.(C-Disp) HDCP認証フロー[5/7] Readデータ判定 */
#define MCU_STEP_GVIF3TX_HDCP_21        (21U)   /* 100-4-5.(C-Disp) HDCP認証フロー[5/7] Bank切り替え（Bank4） */
#define MCU_STEP_GVIF3TX_HDCP_22        (22U)   /* 100-4-5.(C-Disp) HDCP認証フロー[5/7] HDCPモニタ1 Read */
#define MCU_STEP_GVIF3TX_HDCP_23        (23U)   /* 100-4-5.(C-Disp) HDCP認証フロー[5/7] HDCP暗号化状態確認判定～初期化終了orエラー回数により分岐 */
#define MCU_STEP_GVIF3TX_HDCP_24        (24U)   /* 100-4-5.(C-Disp) HDCP認証フロー[5/7] Bank切り替え（Bank8）～F点へ遷移 */
#define MCU_STEP_GVIF3TX_HDCP_25        (25U)   /* 100-4-5.(C-Disp) HDCP認証フロー[6/7] D点～出力映像に合わせてSiP側で映像MUTE */
#define MCU_STEP_GVIF3TX_HDCP_26        (26U)   /* 100-4-5.(C-Disp) HDCP認証フロー[6/7] 100-4-6.HDCP認証停止フロー */
#define MCU_STEP_GVIF3TX_HDCP_27        (27U)   /* 100-4-5.(C-Disp) HDCP認証フロー[6/7] エラー回数により処理の分岐 */
#define MCU_STEP_GVIF3TX_HDCP_28        (28U)   /* 100-4-5.(C-Disp) HDCP認証フロー[6/7] Bank切り替え（Bank0） */
#define MCU_STEP_GVIF3TX_HDCP_29        (29U)   /* 100-4-5.(C-Disp) HDCP認証フロー[7/7] H点～Bank切り替え（Bank4） */
#define MCU_STEP_GVIF3TX_HDCP_30        (30U)   /* 100-4-5.(C-Disp) HDCP認証フロー[7/7] eDP用レジスタ設定 100-5-5.Hot Plug Detect */
#define MCU_STEP_GVIF3TX_HDCP_31        (31U)   /* 100-4-5.(C-Disp) HDCP認証フロー[7/7] Bank切り替え（Bank8） */
#define MCU_STEP_GVIF3TX_HDCP_32        (32U)   /* 100-4-5.(C-Disp) HDCP認証フロー[7/7] I点～HDCPTXイベントモニタRead */
#define MCU_STEP_GVIF3TX_HDCP_33        (33U)   /* 100-4-5.(C-Disp) HDCP認証フロー[7/7] HDCPTXイベントモニタ判定～次状態へ遷移 */
#define MCU_STEP_GVIF3TX_HDCP_FIN       (34U)

#define MCU_WRINUM_GVIF3TX_HDCP_1       (8U)    /* 100-4-5.(C-Disp) HDCP認証フロー[1/7] Bank切り替え（Bank4）～[2/7] HDCPTX Connect 1 設定 レジスタ書込み回数 */
#define MCU_WRINUM_GVIF3TX_HDCP_2       (1U)    /* 100-4-5.(C-Disp) HDCP認証フロー[2/7] C点～HDCP認証コマンド発行（HDCP_AUTH_REQコマンド発行） レジスタ書込み回数 */
#define MCU_WRINUM_GVIF3TX_HDCP_3       (1U)    /* 100-4-5.(C-Disp) HDCP認証フロー[3/7] K点～イベントクリア レジスタ書込み回数 */
#define MCU_WRINUM_GVIF3TX_HDCP_4       (4U)    /* 100-4-5.(C-Disp) HDCP認証フロー[4/7] F点～Bank切り替え（Bank4） レジスタ書込み回数 */
#define MCU_WRINUM_GVIF3TX_HDCP_HPD     (3U)    /* 100-4-5.(C-Disp) HDCP認証フロー[4/7] eDP用レジスタ設定 100-5-5.Hot Plug Detect レジスタ書込み回数 */
#define MCU_WRINUM_GVIF3TX_HDCP_BANK0   (1U)    /* 100-4-5.(C-Disp) HDCP認証フロー[5/7] Bank切り替え（Bank0） */
#define MCU_WRINUM_GVIF3TX_HDCP_BANK4   (1U)    /* 100-4-5.(C-Disp) HDCP認証フロー[5/7] Bank切り替え（Bank4） */
#define MCU_WRINUM_GVIF3TX_HDCP_5       (1U)    /* 100-4-5.(C-Disp) HDCP認証フロー[5/7] Bank切り替え（Bank8）～F点へ遷移 レジスタ書込み回数 */
#define MCU_WRINUM_GVIF3TX_HDCP_STOP    (4U)    /* 100-4-5.(C-Disp) HDCP認証フロー[6/7] 100-4-6.HDCP認証停止フロー レジスタ書込み回数 */
#define MCU_WRINUM_GVIF3TX_HDCP_6       (1U)    /* 100-4-5.(C-Disp) HDCP認証フロー[6/7] Bank切り替え（Bank0） レジスタ書込み回数 */
#define MCU_WRINUM_GVIF3TX_HDCP_7       (2U)    /* 100-4-5.(C-Disp) HDCP認証フロー[7/7] Bank切り替え（Bank0）～Bank切り替え（Bank4） レジスタ書込み回数 */
#define MCU_WRINUM_GVIF3TX_HDCP_8       (1U)    /* 100-4-5.(C-Disp) HDCP認証フロー[7/7] Bank切り替え（Bank8） レジスタ書込み回数 */

#define MCU_GVIF_LNK_TIMEOUT            (5000U * MCU_FRT_1MS)   /* 起動からGVIFリンク確立までの時間要件 5000ms */
#define MCU_HDCP_TIMEOUT                (300U * MCU_FRT_1MS)    /* HDCP認証待ちタイマー 300ms */

#define MCU_DIO_LOW                     (0U)
#define MCU_DIO_HIGH                    (1U)

#define MCU_MISC_HDCP_ACT               (166U)  /* Misc Type 39h：HDMI 05h：C-Disp_HDCP認証応答 */
#define MCU_HDCP_SUBTYPE                (0U)    /* Misc Type 39h：HDMI 05h：C-Disp_HDCP認証応答 SubType */
#define MCU_HDCP_RSLT                   (1U)    /* Misc Type 39h：HDMI 05h：C-Disp_HDCP認証応答 認証結果 */
#define MCU_HDCP_MAX_DEVS_EXCEEDED      (2U)    /* Misc Type 39h：HDMI 05h：C-Disp_HDCP認証応答 HDCPTX_MAX_DEVS_EXCEEDED */
#define MCU_HDCP_HDCPTX_DEVICE_COUNT    (3U)    /* Misc Type 39h：HDMI 05h：C-Disp_HDCP認証応答 HDCPTX_DEVICE_COUNT */
#define MCU_HDCP_MAX_CASCADE_EXCEEDED   (4U)    /* Misc Type 39h：HDMI 05h：C-Disp_HDCP認証応答 DCPTX_MAX_CASCADE_EXCEEDED */
#define MCU_HDCP_HDCPTX_DEPTH           (5U)    /* Misc Type 39h：HDMI 05h：C-Disp_HDCP認証応答 HDCPTX_DEPTH */
#define MCU_HDCP_RCVID                  (6U)    /* Misc Type 39h：HDMI 05h：C-Disp_HDCP認証応答 Receiver ID格納開始位置 */

#define CXD4937_DPTNS_DREC_CNT_MAX      (3U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1 u1_s_gvifsnd_state;                           /* GVIF Sender State */

static U2 u2_s_gvifsnd_regstep;                         /* GVIF Sender Register Request Step */
static U4 u4_s_gvifsnd_i2c_ack_wait_time;               /* GVIF Sender I2C Request Ack Wait Timer */
static U2 u2_s_gvifsnd_reg_btwn_time;                   /* GVIF Sender Access Register Between Timer */

static U1 u1_s_gvifsnd_cycchk_sts;                      /* GVIF Sender Cycle Check Process Status */
static U2 u2_s_gvifsnd_cycchk_timer;                    /* GVIF Sender Cycle Check Poling Timer */

static U1 u1_s_gvifsnd_devrst_sts;                      /* GVIF Sender Device Reset Status */
static U2 u2_s_gvifsnd_devrst_timer;                    /* GVIF Sender Device Reset Wait Timer */
static U1 u1_s_gvifsnd_devrst_drec_cnt;                 /* GVIF Sender Device Reset Drec Counter */

static U1 u1_s_gvifsnd_linkchk_sts;                     /* GVIF Sender Link Check Status */
static U2 u2_s_gvifsnd_linkchk_timer;                   /* GVIF Sender Link Check Wait Timer */
static U1 u1_s_gvifsnd_linkchk_err_cnt;                 /* GVIF Sender Link Check Error Counter */

static U1 u1_s_gvifsnd_edperr1_pre_sts;                 /* GVIF Sender eDP Input LANE0/1 Error Previous Status */
static U1 u1_s_gvifsnd_edperr1_drec_cnt;                /* GVIF Sender eDP Input LANE0/1 Error Drec Counter */
static U1 u1_s_gvifsnd_edperr2_pre_sts;                 /* GVIF Sender eDP Input LANE2/3 Error Previous Status */
static U1 u1_s_gvifsnd_edperr2_drec_cnt;                /* GVIF Sender eDP Input LANE2/3 Error Drec Counter */
static U1 u1_s_gvifsnd_edperr3_pre_sts;                 /* GVIF Sender eDP Input Skew Adjustment Error Previous Status */
static U1 u1_s_gvifsnd_edperr3_drec_cnt;                /* GVIF Sender eDP Input Skew Adjustment Error Drec Counter */
static U1 u1_s_gvifsnd_videoerr_drec_cnt;               /* GVIF Sender Input Video Error Drec Counter */
static U1 u1_s_gvifsnd_loadererr_drec_cnt;              /* GVIF Sender Loader Error Drec Counter */
static U1 u1_s_gvifsnd_cncterr_drec_cnt;                /* GVIF Sender Connection Error Drec Counter */

static U1 u1_s_gvifsnd_linkerr_drec_cnt;                /* GVIF Sender Link Error Drec Counter */
static U1 u1_s_gvifsnd_linkerr_pre_sts;                 /* GVIF Sender Link Error Previous Status */

static U1 u1_s_gvifsnd_hpd_flag;                        /* GVIF Sender Hot Plug Detect Flag */


/* フリーランタイマ */
/* 起動からGVIFリンク確立までの時間計測 */
static U4 u4_g_gvifsnd_gvif3tx_linkup_frt_stamp[GPT_FRT_USELPSD_NUM_PARAM];
/* HDCP認証待ちタイマ */
static U4 u4_g_gvifsnd_hdcp_wait_frt_stamp[GPT_FRT_USELPSD_NUM_PARAM];

/* デバイス起動用カウンタ */
static U2 u2_s_gvifsnd_gvif3tx_devrst_poll_cnt;

/* GVIF送信制御仕様 */
       U1 u1_g_gvifsnd_gvif3tx_overall_step;      /* 100-4-1.(C-Disp) 全体フロー 仮置き中はexternするためstaticなし */
static U1 u1_s_gvifsnd_gvif3tx_edpset_step;      /* 100-4-3.eDP設定フロー */
static U1 u1_s_gvifsnd_gvif3tx_outset_step;      /* 100-4-4.出力設定フロー */
static U2 u2_s_gvifsnd_gvif3tx_hdcp_step;        /* 100-4-5.HDCP認証フロー */
static U4 u4_s_gvifsnd_i2c_ack_wait_time;     /* GVIF3TX 書込み/読込みから応答までの時間計測 */
static U2 u2_s_gvifsnd_gvif3tx_link_wait_time;            /* GVIF3TX Wati処理用タイマ */

/* HDCP認証開始トリガ */
static U1 u1_s_gvifsnd_hdcp_auth_start_trg;
/* 100-4-5.(C-Disp) HDCP認証フロー HDCP認証待機状態エラー回数カウンタ */
static U1 u1_s_gvifsnd_hdcp_authwait_err_cnt;
/* 100-4-5.(C-Disp) HDCP認証フロー 非暗号化エラー回数カウンタ */
static U1 u1_s_gvifsnd_hdcp_encrypt_err_cnt;
/* 100-4-5.(C-Disp) HDCP認証フロー D点処理分岐用エラー回数 */
static U1 u1_s_gvifsnd_hdcp_pointd_err_cnt;

/* Misc Type 39h：HDMI 05h：C-Disp_HDCP認証応答 */
static U1 u1_s_gvifsnd_hdcp_act_tbl[MCU_MISC_HDCP_ACT];

/* 100-4-5.(C-Disp) HDCP認証フロー ループ用デバイスカウンタ */
static U1 u1_s_gvifsnd_hdcp_dev_cnt;

static U1 u1_s_gvifsnd_dptns_err_drec_cnt;   /* GVIF Sender D-point Transition Error Drec Counter */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1 u1_s_Pict_GvifSndrTimChk(const U2 u2_a_tim_cnt, const U2 u2_a_wait_tim);
static void vd_s_Pict_GvifSndrCycChk(void);
static void vd_s_Pict_GvifSndrDevRst(void);
static void vd_s_Pict_GvifSndrGvifLinkChk(void);

static void vd_s_Gvif3txSeqCtl(const U1 u1_a_MODE);
static void vd_s_Pict_GvifSndrPollingRst(void);
static void vd_s_Pict_GvifSndrOverallFlow(void);

static U1 u1_s_Pict_GvifSndrIniSet(void);
static U1 u1_s_Pict_GvifSndrEdpSet(void);
static U1 u1_s_Pict_GvifSndrOutSet(void);
static U1 u1_s_Pict_GvifSndrHdcpAuth(void);
static void Mcu_Sys_Pwr_GvifSndr_Init(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_REG_WRI_REQ CXD4937_BANKSET[CXD4937_BANKSET_WRINUM] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};

static const ST_REG_WRI_REQ CXD4937_BANKSET_WAIT_7MS[CXD4937_BANKSET_WRINUM] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,        7U / GVIFSENDER_TASK_TIME}        /* 7ms wait */
};

static const ST_REG_WRI_REQ CXD4937_GVIFSNDRHDCPSTOP[CXD4937_GVIFSNDRHDCPSTOP_WRINUM] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,        7U / GVIFSENDER_TASK_TIME},       /* 7ms wait */
    {        1,         1,        7U / GVIFSENDER_TASK_TIME},       /* 7ms wait */
    {        2,         1,        20U / GVIFSENDER_TASK_TIME},      /* 20ms wait */
    {        3,         1,        7U / GVIFSENDER_TASK_TIME}        /* 7ms wait */
};

static const ST_REG_WRI_REQ CXD4957_GVIFSNDRERRCLEAR_SET[CXD4957_GVIFSNDRERRCLEAR_SET_WRINUM] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         2,         0}
};

static const ST_REG_WRI_REQ CXD4937_GVIFSNDREDPERR_SET1[CXD4937_GVIFSNDREDPERR_SET1_WRINUM] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         3,         0},
    {        3,         1,         0}
};

static const ST_REG_WRI_REQ CXD4937_GVIFSNDREDPERR_SET2[CXD4937_GVIFSNDREDPERR_SET2_WRINUM] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};

const U1 u1_sp_CXD4957_GVIFSNDR_SETREG_INIT_PDU1[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_SETREG_INIT_PDU2[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x60U,    /* Write Address */
    (U1)0x76U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_SETREG_INIT_PDU3[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x75U,    /* Write Address */
    (U1)0x40U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_SETREG_INIT_PDU4[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x78U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_SETREG_INIT_PDU5[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x80U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_SETREG_INIT_PDU6[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x8EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_SETREG_INIT_PDU7[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x97U,    /* Write Address */
    (U1)0x80U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_SETREG_INIT_PDU8[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x98U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_SETREG_INIT_PDU9[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xB8U,    /* Write Address */
    (U1)0xA1U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_SETREG_INIT_PDU10[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xB9U,    /* Write Address */
    (U1)0xA0U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_SETREG_INIT_PDU11[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xECU,    /* Write Address */
    (U1)0x30U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_SETREG_INIT_PDU12[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xEEU,    /* Write Address */
    (U1)0x39U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_SETREG_INIT_PDU13[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_SETREG_INIT_PDU14[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x60U,    /* Write Address */
    (U1)0x12U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_SETREG_INIT_PDU15[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_SETREG_INIT_PDU16[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1AU,    /* Write Address */
    (U1)0x41U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_SETREG_INIT_PDU17[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1BU,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_SETREG_INIT_PDU18[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1CU,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_SETREG_INIT_PDU19[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x24U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_SETREG_INIT_PDU20[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2FU,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_SETREG_INIT_PDU21[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x07U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_SETREG_INIT_PDU22[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFBU,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_PDU1[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_PDU2[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_PDU3[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x49U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU1[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x00U,    /* Write Data 0x42 */
    (U1)0xFFU,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU2[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU3[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x01U,    /* Write Data 0x42 */
    (U1)0x55U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU4[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU5[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x02U,    /* Write Data 0x42 */
    (U1)0xAEU,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU6[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU7[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x04U,    /* Write Data 0x42 */
    (U1)0xFFU,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU8[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU9[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x05U,    /* Write Data 0x42 */
    (U1)0xFFU,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU10[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU11[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x06U,    /* Write Data 0x42 */
    (U1)0xFFU,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU12[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU13[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x20U,    /* Write Data 0x42 */
    (U1)0x09U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU14[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU15[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x21U,    /* Write Data 0x42 */
    (U1)0x11U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU16[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU17[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x28U,    /* Write Data 0x42 */
    (U1)0x03U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU18[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU19[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x2AU,    /* Write Data 0x42 */
    (U1)0x0DU,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU20[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU21[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x2BU,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU22[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU23[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x60U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU24[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU25[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0xA0U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU26[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU27[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0xA1U,    /* Write Data 0x42 */
    (U1)0x30U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU28[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU29[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0xA2U,    /* Write Data 0x42 */
    (U1)0x03U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU30[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU31[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0xA3U,    /* Write Data 0x42 */
    (U1)0x87U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU32[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU33[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x01U,    /* Write Data 0x41 */
    (U1)0x00U,    /* Write Data 0x42 */
    (U1)0x83U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU34[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU35[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x01U,    /* Write Data 0x41 */
    (U1)0x01U,    /* Write Data 0x42 */
    (U1)0x03U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU36[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU37[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x01U,    /* Write Data 0x41 */
    (U1)0x02U,    /* Write Data 0x42 */
    (U1)0x50U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU38[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU39[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x01U,    /* Write Data 0x41 */
    (U1)0x03U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU40[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU41[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x01U,    /* Write Data 0x41 */
    (U1)0x04U,    /* Write Data 0x42 */
    (U1)0x11U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU42[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU43[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x01U,    /* Write Data 0x41 */
    (U1)0x05U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU44[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU45[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x01U,    /* Write Data 0x41 */
    (U1)0x06U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU46[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU47[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x01U,    /* Write Data 0x41 */
    (U1)0x07U,    /* Write Data 0x42 */
    (U1)0x11U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU48[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU49[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x01U,    /* Write Data 0x41 */
    (U1)0x08U,    /* Write Data 0x42 */
    (U1)0x22U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU50[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU51[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x01U,    /* Write Data 0x41 */
    (U1)0x09U,    /* Write Data 0x42 */
    (U1)0x33U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU52[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU53[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x01U,    /* Write Data 0x41 */
    (U1)0x0AU,    /* Write Data 0x42 */
    (U1)0x44U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU54[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU55[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x01U,    /* Write Data 0x41 */
    (U1)0x0BU,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU56[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU57[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x01U,    /* Write Data 0x41 */
    (U1)0x0CU,    /* Write Data 0x42 */
    (U1)0x11U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU58[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU59[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x01U,    /* Write Data 0x41 */
    (U1)0x0DU,    /* Write Data 0x42 */
    (U1)0x22U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU60[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU61[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x01U,    /* Write Data 0x41 */
    (U1)0x0EU,    /* Write Data 0x42 */
    (U1)0x33U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU62[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU63[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x01U,    /* Write Data 0x41 */
    (U1)0x0FU,    /* Write Data 0x42 */
    (U1)0x44U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU64[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU65[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x00U,    /* Write Data 0x42 */
    (U1)0x05U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU66[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU67[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x01U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU68[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU69[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x02U,    /* Write Data 0x42 */
    (U1)0x04U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU70[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU71[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x04U,    /* Write Data 0x42 */
    (U1)0x03U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU72[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU73[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x05U,    /* Write Data 0x42 */
    (U1)0x03U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU74[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU75[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x06U,    /* Write Data 0x42 */
    (U1)0x03U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU76[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU77[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x07U,    /* Write Data 0x42 */
    (U1)0x03U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU78[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU79[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x10U,    /* Write Data 0x42 */
    (U1)0xD7U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU80[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU81[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x11U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU82[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU83[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x12U,    /* Write Data 0x42 */
    (U1)0xF2U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU84[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU85[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x13U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU86[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU87[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x14U,    /* Write Data 0x42 */
    (U1)0x0DU,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU88[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU89[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x15U,    /* Write Data 0x42 */
    (U1)0x01U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU90[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU91[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x16U,    /* Write Data 0x42 */
    (U1)0x43U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU92[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU93[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x17U,    /* Write Data 0x42 */
    (U1)0x01U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU94[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU95[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x18U,    /* Write Data 0x42 */
    (U1)0xAFU,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU96[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU97[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x19U,    /* Write Data 0x42 */
    (U1)0x01U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU98[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU99[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x1AU,    /* Write Data 0x42 */
    (U1)0x1BU,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU100[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU101[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x1BU,    /* Write Data 0x42 */
    (U1)0x02U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU102[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU103[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x1CU,    /* Write Data 0x42 */
    (U1)0x29U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU104[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU105[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x1DU,    /* Write Data 0x42 */
    (U1)0x03U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU106[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU107[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x1EU,    /* Write Data 0x42 */
    (U1)0x01U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU108[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU109[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x20U,    /* Write Data 0x42 */
    (U1)0x42U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU110[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU111[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x21U,    /* Write Data 0x42 */
    (U1)0xE0U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU112[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU113[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x22U,    /* Write Data 0x42 */
    (U1)0x53U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU114[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU115[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x23U,    /* Write Data 0x42 */
    (U1)0xE1U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU116[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU117[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x24U,    /* Write Data 0x42 */
    (U1)0x53U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU118[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU119[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x25U,    /* Write Data 0x42 */
    (U1)0xE2U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU120[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU121[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x26U,    /* Write Data 0x42 */
    (U1)0x53U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU122[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU123[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x27U,    /* Write Data 0x42 */
    (U1)0xE3U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU124[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU125[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x28U,    /* Write Data 0x42 */
    (U1)0x33U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU126[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU127[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x29U,    /* Write Data 0x42 */
    (U1)0xE4U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU128[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU129[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x2AU,    /* Write Data 0x42 */
    (U1)0x33U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU130[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU131[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x2BU,    /* Write Data 0x42 */
    (U1)0xE5U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU132[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU133[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x2CU,    /* Write Data 0x42 */
    (U1)0x30U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU134[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU135[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x2DU,    /* Write Data 0x42 */
    (U1)0xE8U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU136[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU137[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x34U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU138[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU139[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x35U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU140[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU141[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x40U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU142[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU143[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x41U,    /* Write Data 0x42 */
    (U1)0x0AU,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU144[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU145[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x42U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU146[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU147[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x43U,    /* Write Data 0x42 */
    (U1)0x0AU,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU148[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU149[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x44U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU150[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU151[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x45U,    /* Write Data 0x42 */
    (U1)0x0AU,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU152[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU153[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x46U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU154[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU155[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x47U,    /* Write Data 0x42 */
    (U1)0x0AU,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU156[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU157[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x48U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU158[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU159[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x49U,    /* Write Data 0x42 */
    (U1)0x0AU,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU160[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU161[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x60U,    /* Write Data 0x42 */
    (U1)0x32U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU162[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU163[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x61U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU164[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU165[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x62U,    /* Write Data 0x42 */
    (U1)0x78U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU166[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU167[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x63U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU168[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU169[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x64U,    /* Write Data 0x42 */
    (U1)0xF0U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU170[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU171[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x65U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU172[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU173[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x66U,    /* Write Data 0x42 */
    (U1)0xE0U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU174[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU175[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x67U,    /* Write Data 0x42 */
    (U1)0x01U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU176[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU177[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x68U,    /* Write Data 0x42 */
    (U1)0xDAU,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU178[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU179[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x69U,    /* Write Data 0x42 */
    (U1)0x02U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU180[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU181[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x6AU,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU182[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU183[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x6BU,    /* Write Data 0x42 */
    (U1)0x03U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU184[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU185[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x6CU,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU186[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU187[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x6DU,    /* Write Data 0x42 */
    (U1)0x03U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU188[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU189[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x70U,    /* Write Data 0x42 */
    (U1)0xA3U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU190[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU191[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x71U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU192[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU193[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x72U,    /* Write Data 0x42 */
    (U1)0x62U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU194[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU195[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x73U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU196[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU197[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x74U,    /* Write Data 0x42 */
    (U1)0x21U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU198[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU199[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x75U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU200[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU201[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x76U,    /* Write Data 0x42 */
    (U1)0x20U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU202[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU203[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x77U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU204[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU205[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x78U,    /* Write Data 0x42 */
    (U1)0x24U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU206[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU207[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x79U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU208[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU209[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0xB0U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU210[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU211[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0xC0U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU212[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU213[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0xC1U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU214[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU215[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0xC2U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU216[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU217[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0xC3U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU218[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU219[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0xC8U,    /* Write Data 0x42 */
    (U1)0x04U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU220[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU221[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0xC9U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x03U,    /* Write Data 0x43 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU222[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU223[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0xCAU,    /* Write Data 0x42 */
    (U1)0x02U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU224[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU225[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0xCBU,    /* Write Data 0x42 */
    (U1)0x04U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU226[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU227[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0xD0U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU228[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU229[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0xF0U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU230[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU1[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x00U,    /* Write Data 0x42 */
    (U1)0x14U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU2[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU3[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x01U,    /* Write Data 0x42 */
    (U1)0x14U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU4[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU5[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x02U,    /* Write Data 0x42 */
    (U1)0xC4U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU6[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU7[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x03U,    /* Write Data 0x42 */
    (U1)0x81U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU8[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU9[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x08U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU10[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU11[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x0AU,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU12[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU13[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x0CU,    /* Write Data 0x42 */
    (U1)0x10U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU14[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU15[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x0DU,    /* Write Data 0x42 */
    (U1)0x01U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU16[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU17[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x0EU,    /* Write Data 0x42 */
    (U1)0x01U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU18[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU19[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x10U,    /* Write Data 0x42 */
    (U1)0xA4U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU20[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU21[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x11U,    /* Write Data 0x42 */
    (U1)0x1FU,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU22[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU23[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x12U,    /* Write Data 0x42 */
    (U1)0x30U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU24[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU25[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x13U,    /* Write Data 0x42 */
    (U1)0x2AU,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU26[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU27[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x14U,    /* Write Data 0x42 */
    (U1)0x76U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU28[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU29[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x15U,    /* Write Data 0x42 */
    (U1)0x2FU,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU30[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU31[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x16U,    /* Write Data 0x42 */
    (U1)0xBCU,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU32[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU33[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x17U,    /* Write Data 0x42 */
    (U1)0x34U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU34[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU35[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x18U,    /* Write Data 0x42 */
    (U1)0x48U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU36[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU37[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x19U,    /* Write Data 0x42 */
    (U1)0x3FU,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU38[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU39[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x1AU,    /* Write Data 0x42 */
    (U1)0x60U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU40[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU41[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x1BU,    /* Write Data 0x42 */
    (U1)0x54U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU42[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU43[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x1CU,    /* Write Data 0x42 */
    (U1)0x78U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU44[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU45[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x1DU,    /* Write Data 0x42 */
    (U1)0x69U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU46[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU47[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x21U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU48[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU49[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x00U,    /* Write Data 0x42 */
    (U1)0x01U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU50[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU51[CXD4937_I2C_RWC_BYTE8] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x07U,    /* Write Data 0x41 */
    (U1)0x00U,    /* Write Data 0x42 */
    (U1)0x05U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU52[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET2_PDU1[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x47U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET3_PDU1[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET3_PDU2[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xB6U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET3_PDU3[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_HPD_PDU1[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_HPD_PDU2[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_HPD_PDU3[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_HPD_PDU4[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x51U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_HPD_PDU5[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_EDPSET_HPD_PDU6[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_OUTSET3_PDU1[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_OUTSET1_PDU1[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x60U,    /* Write Address */
    (U1)0x77U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_OUTSET_GVIF3TX0_ACTIVATED_RD_PDU1[CXD4937_I2C_RWC_BYTE2] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U     /* Write Address */
};

U1 u1_sp_CXD4957_GVIFSNDR_OUTSET_GVIF3TX0_ACTIVATED_RD_PDU2[CXD4937_I2C_RWC_BYTE2];

const U1 u1_sp_CXD4957_GVIFSNDR_OUTSET2_PDU1[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x07U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_OUTSET2_PDU2[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFBU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_OUTSET2_PDU3[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_OUTSET2_PDU4[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2EU,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_OUTSET2_PDU5[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_HDCP1_PDU1[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_HDCP1_PDU2[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_HDCP1_PDU3[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_HDCP1_PDU4[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x08U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_HDCP1_PDU5[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x08U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_HDCP1_PDU6[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_HDCP1_PDU7[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x06U,    /* Write Address */
    (U1)0x30U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_HDCP1_PDU8[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_HDCP1_PDU9[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x01U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_HDCP2_PDU1[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x12U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_HDCPTX_STATUS_RD_PDU1[CXD4937_I2C_RWC_BYTE2] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x10U     /* Write Address */
};

U1 u1_sp_CXD4957_GVIFSNDR_HDCPTX_STATUS_RD_PDU2[CXD4937_I2C_RWC_BYTE2];

const U1 u1_sp_CXD4957_GVIFSNDR_HDCPTX_EVENT_RD_PDU1[CXD4937_I2C_RWC_BYTE2] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x13U     /* Write Address */
};

U1 u1_sp_CXD4957_GVIFSNDR_HDCPTX_EVENT_RD_PDU2[CXD4937_I2C_RWC_BYTE2];

const U1 u1_sp_CXD4957_GVIFSNDR_HDCP3_PDU1[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x15U,    /* Write Address */
    (U1)0x83U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_HDCPTX_DEVS_CASCADE_RD_PDU1[CXD4937_I2C_RWC_BYTE2] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x20U     /* Write Address */
};

U1 u1_sp_CXD4957_GVIFSNDR_HDCPTX_DEVS_CASCADE_RD_PDU2[CXD4937_I2C_RWC_BYTE3];

U1 u1_sp_CXD4957_GVIFSNDR_HDCPTX_DEV_ID_RD_PDU1[CXD4937_I2C_RWC_BYTE2];

U1 u1_sp_CXD4957_GVIFSNDR_HDCPTX_DEV_ID_RD_PDU2[CXD4937_I2C_RWC_BYTE6];

const U1 u1_sp_CXD4957_GVIFSNDR_HDCP4_PDU1[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x12U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_HDCP4_PDU2[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_HDCP4_PDU3[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xB6U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_HDCP4_PDU4[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_HDCP_HPD_PDU1[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_HDCP_HPD_PDU2[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_HDCP_HPD_PDU3[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_HDCP_HPD_PDU4[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x51U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_HDCP_HPD_PDU5[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_HDCP_HPD_PDU6[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_HDCP_BANK0_PDU1[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_HDCP_VIDEOIN_RD_PDU1[CXD4937_I2C_RWC_BYTE2] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xE9U     /* Write Address */
};

U1 u1_sp_CXD4957_GVIFSNDR_HDCP_VIDEOIN_RD_PDU2[CXD4937_I2C_RWC_BYTE2];

const U1 u1_sp_CXD4957_GVIFSNDR_HDCP_BANK4_PDU1[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_HDCPTX_ENC_RD_PDU1[CXD4937_I2C_RWC_BYTE2] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x30U     /* Write Address */
};

U1 u1_sp_CXD4957_GVIFSNDR_HDCPTX_ENC_RD_PDU2[CXD4937_I2C_RWC_BYTE2];

const U1 u1_sp_CXD4957_GVIFSNDR_HDCP5_PDU1[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x08U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_HDCPSTOP_PDU1[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x08U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_HDCPSTOP_PDU2[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x15U,    /* Write Address */
    (U1)0x83U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_HDCPSTOP_PDU3[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x12U,    /* Write Address */
    (U1)0x11U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_HDCPSTOP_PDU4[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x12U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_HDCP6_PDU1[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_GVIF3TX0_ACT_RD_PDU1[CXD4937_I2C_RWC_BYTE2] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U     /* Write Address */
};

U1 u1_sp_CXD4957_GVIFSNDR_GVIF3TX0_ACT_RD_PDU2[CXD4937_I2C_RWC_BYTE2];

const U1 u1_sp_CXD4957_GVIFSNDR_HDCP7_PDU1[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_HDCP7_PDU2[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xB6U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_HDCP7_PDU3[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDR_HDCP8_PDU1[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x08U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDRBANK0_SET1[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDRDEVERR_RD_PDU1[CXD4937_I2C_RWC_BYTE2] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x75U     /* Write Address */
};

U1 u1_sp_CXD4957_GVIFSNDRDEVERR_RD_PDU2[CXD4937_I2C_RWC_BYTE2];

const U1 u1_sp_CXD4957_GVIFSNDRLINKERR_RD_PDU1[CXD4937_I2C_RWC_BYTE2] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x11U     /* Write Address */
};

U1 u1_sp_CXD4957_GVIFSNDRLINKERR_RD_PDU2[CXD4937_I2C_RWC_BYTE2];

const U1 u1_sp_CXD4957_GVIFSNDRERRCLEAR_SET1[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2EU,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDRERRCLEAR_SET2[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDRINPUTERR_RD_PDU1[CXD4937_I2C_RWC_BYTE2] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xE9U     /* Write Address */
};

U1 u1_sp_CXD4957_GVIFSNDRINPUTERR_RD_PDU2[CXD4937_I2C_RWC_BYTE2];

const U1 u1_sp_CXD4957_GVIFSNDRLODERERR_RD_PDU1[CXD4937_I2C_RWC_BYTE2] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x15U     /* Write Address */
};

U1 u1_sp_CXD4957_GVIFSNDRLODERERR_RD_PDU2[CXD4937_I2C_RWC_BYTE2];

const U1 u1_sp_CXD4957_GVIFSNDRCONNECTERR_RD_PDU1[CXD4937_I2C_RWC_BYTE2] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U     /* Write Address */
};

U1 u1_sp_CXD4957_GVIFSNDRCONNECTERR_RD_PDU2[CXD4937_I2C_RWC_BYTE2];

const U1 u1_sp_CXD4957_GVIFSNDRLINKCHK_RD_PDU1[CXD4937_I2C_RWC_BYTE2] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U     /* Write Address */
};

U1 u1_sp_CXD4957_GVIFSNDRLINKCHK_RD_PDU2[CXD4937_I2C_RWC_BYTE2];

const U1 u1_sp_CXD4937_GVIFSNDRBANK4_SET_PDU1[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_CXD4937_GVIFSNDREDPERR1_1_SET_PDU1[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_CXD4937_GVIFSNDREDPERR1_1_SET_PDU2[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_CXD4937_GVIFSNDREDPERR1_1_SET_PDU3[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_CXD4937_GVIFSNDREDPERR1_1_SET_PDU4[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_CXD4937_GVIFSNDREDPERR1_2_RD_PDU1[CXD4937_I2C_RWC_BYTE2] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x44U     /* Write Address */
};

U1 u1_sp_CXD4937_GVIFSNDREDPERR1_2_RD_PDU2[CXD4937_I2C_RWC_BYTE2];

const U1 u1_sp_CXD4937_GVIFSNDREDPERR1_3_SET_PDU1[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4937_GVIFSNDREDPERR2_1_SET_PDU1[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_CXD4937_GVIFSNDREDPERR2_1_SET_PDU2[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_CXD4937_GVIFSNDREDPERR2_1_SET_PDU3[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_CXD4937_GVIFSNDREDPERR2_1_SET_PDU4[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_CXD4937_GVIFSNDREDPERR2_2_RD_PDU1[CXD4937_I2C_RWC_BYTE2] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x44U     /* Write Address */
};

U1 u1_sp_CXD4937_GVIFSNDREDPERR2_2_RD_PDU2[CXD4937_I2C_RWC_BYTE2];

const U1 u1_sp_CXD4937_GVIFSNDREDPERR2_3_SET_PDU1[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4937_GVIFSNDREDPERR3_1_SET_PDU1[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_CXD4937_GVIFSNDREDPERR3_1_SET_PDU2[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_CXD4937_GVIFSNDREDPERR3_1_SET_PDU3[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_CXD4937_GVIFSNDREDPERR3_1_SET_PDU4[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_CXD4937_GVIFSNDREDPERR3_2_RD_PDU1[CXD4937_I2C_RWC_BYTE2] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x44U     /* Write Address */
};

U1 u1_sp_CXD4937_GVIFSNDREDPERR3_2_RD_PDU2[CXD4937_I2C_RWC_BYTE2];

const U1 u1_sp_CXD4937_GVIFSNDREDPERR3_3_SET_PDU1[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4937_GVIFSNDRHDCPSTOP_SET_PDU1[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x08U     /* Write Data */
};

const U1 u1_sp_CXD4937_GVIFSNDRHDCPSTOP_SET_PDU2[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x15U,    /* Write Address */
    (U1)0x83U     /* Write Data */
};

const U1 u1_sp_CXD4937_GVIFSNDRHDCPSTOP_SET_PDU3[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x12U,    /* Write Address */
    (U1)0x11U     /* Write Data */
};

const U1 u1_sp_CXD4937_GVIFSNDRHDCPSTOP_SET_PDU4[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x12U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDR_SETREG_INIT[22] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_SETREG_INIT_PDU1[0],
        (U4)0x30040003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_SETREG_INIT_PDU2[0],
        (U4)0x30080003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_SETREG_INIT_PDU3[0],
        (U4)0x300C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_SETREG_INIT_PDU4[0],
        (U4)0x30100003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_SETREG_INIT_PDU5[0],
        (U4)0x30140003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_SETREG_INIT_PDU6[0],
        (U4)0x30180003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_SETREG_INIT_PDU7[0],
        (U4)0x301C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_SETREG_INIT_PDU8[0],
        (U4)0x30200003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_SETREG_INIT_PDU9[0],
        (U4)0x30240003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_SETREG_INIT_PDU10[0],
        (U4)0x30280003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_SETREG_INIT_PDU11[0],
        (U4)0x302C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_SETREG_INIT_PDU12[0],
        (U4)0x30300003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_SETREG_INIT_PDU13[0],
        (U4)0x30340003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_SETREG_INIT_PDU14[0],
        (U4)0x30380003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_SETREG_INIT_PDU15[0],
        (U4)0x303C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_SETREG_INIT_PDU16[0],
        (U4)0x30400003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_SETREG_INIT_PDU17[0],
        (U4)0x30440003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_SETREG_INIT_PDU18[0],
        (U4)0x30480003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_SETREG_INIT_PDU19[0],
        (U4)0x304C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_SETREG_INIT_PDU20[0],
        (U4)0x30500003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_SETREG_INIT_PDU21[0],
        (U4)0x30540003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_SETREG_INIT_PDU22[0],
        (U4)0x30580003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDR_EDPSET1[3] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_PDU1[0],
        (U4)0x305C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_PDU2[0],
        (U4)0x30600003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_PDU3[0],
        (U4)0x30640003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDR_EDPSET_REC[230] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU1[0],
        (U4)0x30680008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU2[0],
        (U4)0x306C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU3[0],
        (U4)0x30700008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU4[0],
        (U4)0x30740003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU5[0],
        (U4)0x30780008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU6[0],
        (U4)0x307C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU7[0],
        (U4)0x30800008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU8[0],
        (U4)0x30840003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU9[0],
        (U4)0x30880008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU10[0],
        (U4)0x308C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU11[0],
        (U4)0x30900008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU12[0],
        (U4)0x30940003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU13[0],
        (U4)0x30980008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU14[0],
        (U4)0x309C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU15[0],
        (U4)0x30A00008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU16[0],
        (U4)0x30A40003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU17[0],
        (U4)0x30A80008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU18[0],
        (U4)0x30AC0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU19[0],
        (U4)0x30B00008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU20[0],
        (U4)0x30B40003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU21[0],
        (U4)0x30B80008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU22[0],
        (U4)0x30BC0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU23[0],
        (U4)0x30C00008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU24[0],
        (U4)0x30C40003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU25[0],
        (U4)0x30C80008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU26[0],
        (U4)0x30CC0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU27[0],
        (U4)0x30D00008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU28[0],
        (U4)0x30D40003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU29[0],
        (U4)0x30D80008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU30[0],
        (U4)0x30DC0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU31[0],
        (U4)0x30E00008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU32[0],
        (U4)0x30E40003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU33[0],
        (U4)0x30E80008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU34[0],
        (U4)0x30EC0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU35[0],
        (U4)0x30F00008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU36[0],
        (U4)0x30F40003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU37[0],
        (U4)0x30F80008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU38[0],
        (U4)0x30FC0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU39[0],
        (U4)0x31000008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU40[0],
        (U4)0x31040003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU41[0],
        (U4)0x31080008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU42[0],
        (U4)0x310C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU43[0],
        (U4)0x31100008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU44[0],
        (U4)0x31140003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU45[0],
        (U4)0x31180008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU46[0],
        (U4)0x311C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU47[0],
        (U4)0x31200008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU48[0],
        (U4)0x31240003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU49[0],
        (U4)0x31280008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU50[0],
        (U4)0x312C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU51[0],
        (U4)0x31300008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU52[0],
        (U4)0x31340003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU53[0],
        (U4)0x31380008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU54[0],
        (U4)0x313C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU55[0],
        (U4)0x31400008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU56[0],
        (U4)0x31440003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU57[0],
        (U4)0x31480008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU58[0],
        (U4)0x314C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU59[0],
        (U4)0x31500008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU60[0],
        (U4)0x31540003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU61[0],
        (U4)0x31580008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU62[0],
        (U4)0x315C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU63[0],
        (U4)0x31600008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU64[0],
        (U4)0x31640003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU65[0],
        (U4)0x31680008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU66[0],
        (U4)0x316C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU67[0],
        (U4)0x31700008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU68[0],
        (U4)0x31740003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU69[0],
        (U4)0x31780008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU70[0],
        (U4)0x317C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU71[0],
        (U4)0x31800008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU72[0],
        (U4)0x31840003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU73[0],
        (U4)0x31880008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU74[0],
        (U4)0x318C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU75[0],
        (U4)0x31900008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU76[0],
        (U4)0x31940003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU77[0],
        (U4)0x31980008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU78[0],
        (U4)0x319C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU79[0],
        (U4)0x31A00008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU80[0],
        (U4)0x31A40003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU81[0],
        (U4)0x31A80008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU82[0],
        (U4)0x31AC0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU83[0],
        (U4)0x31B00008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU84[0],
        (U4)0x31B40003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU85[0],
        (U4)0x31B80008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU86[0],
        (U4)0x31BC0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU87[0],
        (U4)0x31C00008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU88[0],
        (U4)0x31C40003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU89[0],
        (U4)0x31C80008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU90[0],
        (U4)0x31CC0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU91[0],
        (U4)0x31D00008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU92[0],
        (U4)0x31D40003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU93[0],
        (U4)0x31D80008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU94[0],
        (U4)0x31DC0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU95[0],
        (U4)0x31E00008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU96[0],
        (U4)0x31E40003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU97[0],
        (U4)0x31E80008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU98[0],
        (U4)0x31EC0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU99[0],
        (U4)0x31F00008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU100[0],
        (U4)0x31F40003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU101[0],
        (U4)0x31F80008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU102[0],
        (U4)0x31FC0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU103[0],
        (U4)0x32000008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU104[0],
        (U4)0x32040003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU105[0],
        (U4)0x32080008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU106[0],
        (U4)0x320C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU107[0],
        (U4)0x32100008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU108[0],
        (U4)0x32140003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU109[0],
        (U4)0x32180008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU110[0],
        (U4)0x321C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU111[0],
        (U4)0x32200008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU112[0],
        (U4)0x32240003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU113[0],
        (U4)0x32280008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU114[0],
        (U4)0x322C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU115[0],
        (U4)0x32300008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU116[0],
        (U4)0x32340003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU117[0],
        (U4)0x32380008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU118[0],
        (U4)0x323C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU119[0],
        (U4)0x32400008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU120[0],
        (U4)0x32440003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU121[0],
        (U4)0x32480008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU122[0],
        (U4)0x324C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU123[0],
        (U4)0x32500008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU124[0],
        (U4)0x32540003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU125[0],
        (U4)0x32580008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU126[0],
        (U4)0x325C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU127[0],
        (U4)0x32600008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU128[0],
        (U4)0x32640003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU129[0],
        (U4)0x32680008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU130[0],
        (U4)0x326C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU131[0],
        (U4)0x32700008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU132[0],
        (U4)0x32740003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU133[0],
        (U4)0x32780008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU134[0],
        (U4)0x327C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU135[0],
        (U4)0x32800008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU136[0],
        (U4)0x32840003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU137[0],
        (U4)0x32880008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU138[0],
        (U4)0x328C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU139[0],
        (U4)0x32900008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU140[0],
        (U4)0x32940003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU141[0],
        (U4)0x32980008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU142[0],
        (U4)0x329C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU143[0],
        (U4)0x32A00008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU144[0],
        (U4)0x32A40003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU145[0],
        (U4)0x32A80008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU146[0],
        (U4)0x32AC0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU147[0],
        (U4)0x32B00008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU148[0],
        (U4)0x32B40003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU149[0],
        (U4)0x32B80008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU150[0],
        (U4)0x32BC0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU151[0],
        (U4)0x32C00008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU152[0],
        (U4)0x32C40003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU153[0],
        (U4)0x32C80008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU154[0],
        (U4)0x32CC0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU155[0],
        (U4)0x32D00008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU156[0],
        (U4)0x32D40003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU157[0],
        (U4)0x32D80008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU158[0],
        (U4)0x32DC0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU159[0],
        (U4)0x32E00008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU160[0],
        (U4)0x32E40003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU161[0],
        (U4)0x32E80008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU162[0],
        (U4)0x32EC0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU163[0],
        (U4)0x32F00008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU164[0],
        (U4)0x32F40003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU165[0],
        (U4)0x32F80008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU166[0],
        (U4)0x32FC0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU167[0],
        (U4)0x33000008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU168[0],
        (U4)0x33040003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU169[0],
        (U4)0x33080008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU170[0],
        (U4)0x330C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU171[0],
        (U4)0x33100008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU172[0],
        (U4)0x33140003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU173[0],
        (U4)0x33180008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU174[0],
        (U4)0x331C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU175[0],
        (U4)0x33200008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU176[0],
        (U4)0x33240003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU177[0],
        (U4)0x33280008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU178[0],
        (U4)0x332C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU179[0],
        (U4)0x33300008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU180[0],
        (U4)0x33340003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU181[0],
        (U4)0x33380008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU182[0],
        (U4)0x333C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU183[0],
        (U4)0x33400008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU184[0],
        (U4)0x33440003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU185[0],
        (U4)0x33480008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU186[0],
        (U4)0x334C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU187[0],
        (U4)0x33500008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU188[0],
        (U4)0x33540003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU189[0],
        (U4)0x33580008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU190[0],
        (U4)0x335C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU191[0],
        (U4)0x33600008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU192[0],
        (U4)0x33640003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU193[0],
        (U4)0x33680008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU194[0],
        (U4)0x336C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU195[0],
        (U4)0x33700008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU196[0],
        (U4)0x33740003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU197[0],
        (U4)0x33780008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU198[0],
        (U4)0x337C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU199[0],
        (U4)0x33800008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU200[0],
        (U4)0x33840003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU201[0],
        (U4)0x33880008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU202[0],
        (U4)0x338C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU203[0],
        (U4)0x33900008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU204[0],
        (U4)0x33940003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU205[0],
        (U4)0x33980008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU206[0],
        (U4)0x339C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU207[0],
        (U4)0x33A00008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU208[0],
        (U4)0x33A40003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU209[0],
        (U4)0x33A80008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU210[0],
        (U4)0x33AC0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU211[0],
        (U4)0x33B00008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU212[0],
        (U4)0x33B40003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU213[0],
        (U4)0x33B80008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU214[0],
        (U4)0x33BC0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU215[0],
        (U4)0x33C00008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU216[0],
        (U4)0x33C40003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU217[0],
        (U4)0x33C80008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU218[0],
        (U4)0x33CC0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU219[0],
        (U4)0x33D00008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU220[0],
        (U4)0x33D40003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU221[0],
        (U4)0x33D80008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU222[0],
        (U4)0x33DC0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU223[0],
        (U4)0x33E00008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU224[0],
        (U4)0x33E40003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU225[0],
        (U4)0x33E80008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU226[0],
        (U4)0x33EC0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU227[0],
        (U4)0x33F00008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU228[0],
        (U4)0x33F40003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU229[0],
        (U4)0x33F80008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_REC_PDU230[0],
        (U4)0x33FC0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDR_EDPSET_DPCD[52] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU1[0],
        (U4)0x34000008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU2[0],
        (U4)0x34040003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU3[0],
        (U4)0x34080008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU4[0],
        (U4)0x340C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU5[0],
        (U4)0x34100008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU6[0],
        (U4)0x34140003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU7[0],
        (U4)0x34180008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU8[0],
        (U4)0x341C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU9[0],
        (U4)0x34200008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU10[0],
        (U4)0x34240003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU11[0],
        (U4)0x34280008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU12[0],
        (U4)0x342C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU13[0],
        (U4)0x34300008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU14[0],
        (U4)0x34340003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU15[0],
        (U4)0x34380008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU16[0],
        (U4)0x343C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU17[0],
        (U4)0x34400008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU18[0],
        (U4)0x34440003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU19[0],
        (U4)0x34480008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU20[0],
        (U4)0x344C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU21[0],
        (U4)0x34500008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU22[0],
        (U4)0x34540003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU23[0],
        (U4)0x34580008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU24[0],
        (U4)0x345C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU25[0],
        (U4)0x34600008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU26[0],
        (U4)0x34640003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU27[0],
        (U4)0x34680008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU28[0],
        (U4)0x346C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU29[0],
        (U4)0x34700008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU30[0],
        (U4)0x34740003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU31[0],
        (U4)0x34780008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU32[0],
        (U4)0x347C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU33[0],
        (U4)0x34800008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU34[0],
        (U4)0x34840003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU35[0],
        (U4)0x34880008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU36[0],
        (U4)0x348C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU37[0],
        (U4)0x34900008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU38[0],
        (U4)0x34940003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU39[0],
        (U4)0x34980008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU40[0],
        (U4)0x349C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU41[0],
        (U4)0x34A00008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU42[0],
        (U4)0x34A40003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU43[0],
        (U4)0x34A80008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU44[0],
        (U4)0x34AC0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU45[0],
        (U4)0x34B00008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU46[0],
        (U4)0x34B40003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU47[0],
        (U4)0x34B80008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU48[0],
        (U4)0x34BC0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU49[0],
        (U4)0x34C00008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU50[0],
        (U4)0x34C40003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU51[0],
        (U4)0x34C80008U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_DPCD_PDU52[0],
        (U4)0x34CC0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDR_EDPSET2[1] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET2_PDU1[0],
        (U4)0x34D00003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDR_EDPSET3[3] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET3_PDU1[0],
        (U4)0x34D40003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET3_PDU2[0],
        (U4)0x34D80003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET3_PDU3[0],
        (U4)0x34DC0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDR_EDPSET_HPD[6] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_HPD_PDU1[0],
        (U4)0x34E00003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_HPD_PDU2[0],
        (U4)0x34E40003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_HPD_PDU3[0],
        (U4)0x34E80003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_HPD_PDU4[0],
        (U4)0x34EC0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_HPD_PDU5[0],
        (U4)0x34F00003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_EDPSET_HPD_PDU6[0],
        (U4)0x34F40003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDR_OUTSET3[1] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_OUTSET3_PDU1[0],
        (U4)0x34F80003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDR_OUTSET1[1] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_OUTSET1_PDU1[0],
        (U4)0x34FC0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDR_OUTSET_GVIF3TX0_ACTIVATED_RD[2] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_OUTSET_GVIF3TX0_ACTIVATED_RD_PDU1[0],
        (U4)0x35000002U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_OUTSET_GVIF3TX0_ACTIVATED_RD_PDU2[0],
        (U4)0x35040002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDR_OUTSET2[5] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_OUTSET2_PDU1[0],
        (U4)0x35080003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_OUTSET2_PDU2[0],
        (U4)0x350C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_OUTSET2_PDU3[0],
        (U4)0x35100003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_OUTSET2_PDU4[0],
        (U4)0x35140003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_OUTSET2_PDU5[0],
        (U4)0x35180003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDR_HDCP1[9] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_HDCP1_PDU1[0],
        (U4)0x351C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_HDCP1_PDU2[0],
        (U4)0x35200003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_HDCP1_PDU3[0],
        (U4)0x35240003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_HDCP1_PDU4[0],
        (U4)0x35280003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_HDCP1_PDU5[0],
        (U4)0x352C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_HDCP1_PDU6[0],
        (U4)0x35300003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_HDCP1_PDU7[0],
        (U4)0x35340003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_HDCP1_PDU8[0],
        (U4)0x35380003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_HDCP1_PDU9[0],
        (U4)0x353C0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDR_HDCP2[1] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_HDCP2_PDU1[0],
        (U4)0x35400003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDR_HDCPTX_STATUS_RD[2] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_HDCPTX_STATUS_RD_PDU1[0],
        (U4)0x35440002U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_HDCPTX_STATUS_RD_PDU2[0],
        (U4)0x35480002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDR_HDCPTX_EVENT_RD[2] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_HDCPTX_EVENT_RD_PDU1[0],
        (U4)0x354C0002U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_HDCPTX_EVENT_RD_PDU2[0],
        (U4)0x35500002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDR_HDCP3[1] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_HDCP3_PDU1[0],
        (U4)0x35540003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDR_HDCPTX_DEVS_CASCADE_RD[2] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_HDCPTX_DEVS_CASCADE_RD_PDU1[0],
        (U4)0x35580002U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_HDCPTX_DEVS_CASCADE_RD_PDU2[0],
        (U4)0x355C0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDR_HDCPTX_DEV_ID_RD[2] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_HDCPTX_DEV_ID_RD_PDU1[0],
        (U4)0x35600002U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_HDCPTX_DEV_ID_RD_PDU2[0],
        (U4)0x35640006U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDR_HDCP4[4] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_HDCP4_PDU1[0],
        (U4)0x35680003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_HDCP4_PDU2[0],
        (U4)0x356C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_HDCP4_PDU3[0],
        (U4)0x35700003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_HDCP4_PDU4[0],
        (U4)0x35740003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDR_HDCP_HPD[6] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_HDCP_HPD_PDU1[0],
        (U4)0x35780003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_HDCP_HPD_PDU2[0],
        (U4)0x357C0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_HDCP_HPD_PDU3[0],
        (U4)0x35800003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_HDCP_HPD_PDU4[0],
        (U4)0x35840003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_HDCP_HPD_PDU5[0],
        (U4)0x35880003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_HDCP_HPD_PDU6[0],
        (U4)0x358C0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDR_HDCP_BANK0[1] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_HDCP_BANK0_PDU1[0],
        (U4)0x35900003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDR_HDCP_VIDEOIN_RD[2] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_HDCP_VIDEOIN_RD_PDU1[0],
        (U4)0x35940002U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_HDCP_VIDEOIN_RD_PDU2[0],
        (U4)0x35980002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDR_HDCP_BANK4[1] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_HDCP_BANK4_PDU1[0],
        (U4)0x359C0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDR_HDCPTX_ENC_RD[2] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_HDCPTX_ENC_RD_PDU1[0],
        (U4)0x35A00002U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_HDCPTX_ENC_RD_PDU2[0],
        (U4)0x35A40002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDR_HDCP5[1] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_HDCP5_PDU1[0],
        (U4)0x35A80003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDR_HDCPSTOP[4] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_HDCPSTOP_PDU1[0],
        (U4)0x35AC0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_HDCPSTOP_PDU2[0],
        (U4)0x35B00003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_HDCPSTOP_PDU3[0],
        (U4)0x35B40003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_HDCPSTOP_PDU4[0],
        (U4)0x35B80003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDR_HDCP6[1] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_HDCP6_PDU1[0],
        (U4)0x35BC0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDR_GVIF3TX0_ACT_RD[2] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_GVIF3TX0_ACT_RD_PDU1[0],
        (U4)0x35C00002U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_GVIF3TX0_ACT_RD_PDU2[0],
        (U4)0x35C40002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDR_HDCP7[3] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_HDCP7_PDU1[0],
        (U4)0x35C80003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_HDCP7_PDU2[0],
        (U4)0x35CC0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_HDCP7_PDU3[0],
        (U4)0x35D00003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDR_HDCP8[1] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDR_HDCP8_PDU1[0],
        (U4)0x35D40003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDRBANK0_TBL[1] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDRBANK0_SET1[0],
        (U4)0x35D80003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDRDEVERR_RD_TBL[2] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDRDEVERR_RD_PDU1[0],
        (U4)0x35DC0002U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDRDEVERR_RD_PDU2[0],
        (U4)0x35E00002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDRLINKERR_RD_TBL[2] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDRLINKERR_RD_PDU1[0],
        (U4)0x35E40002U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDRLINKERR_RD_PDU2[0],
        (U4)0x35E80002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDRERRCLEAR_TBL[2] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDRERRCLEAR_SET1[0],
        (U4)0x35EC0003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDRERRCLEAR_SET2[0],
        (U4)0x35F00003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDRINPUTERR_RD_TBL[2] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDRINPUTERR_RD_PDU1[0],
        (U4)0x35F40002U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDRINPUTERR_RD_PDU2[0],
        (U4)0x35F80002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDRLODERERR_RD_TBL[2] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDRLODERERR_RD_PDU1[0],
        (U4)0x35FC0002U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDRLODERERR_RD_PDU2[0],
        (U4)0x36000002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDRCONNECTERR_RD_TBL[2] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDRCONNECTERR_RD_PDU1[0],
        (U4)0x36040002U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDRCONNECTERR_RD_PDU2[0],
        (U4)0x36080002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDRLINKCHK_RD_TBL[2] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDRLINKCHK_RD_PDU1[0],
        (U4)0x360C0002U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDRLINKCHK_RD_PDU2[0],
        (U4)0x36100002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4937_GVIFSNDRBANK4_TBL[1] = {
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDRBANK4_SET_PDU1[0],
        (U4)0x36140003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4937_GVIFSNDREDPERR1_1_TBL[4] = {
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDREDPERR1_1_SET_PDU1[0],
        (U4)0x36180003U
    },
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDREDPERR1_1_SET_PDU2[0],
        (U4)0x361C0003U
    },
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDREDPERR1_1_SET_PDU3[0],
        (U4)0x36200003U
    },
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDREDPERR1_1_SET_PDU4[0],
        (U4)0x36240003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4937_GVIFSNDREDPERR1_2_TBL[2] = {
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDREDPERR1_2_RD_PDU1[0],
        (U4)0x36280002U
    },
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDREDPERR1_2_RD_PDU2[0],
        (U4)0x362C0002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4937_GVIFSNDREDPERR1_3_TBL[1] = {
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDREDPERR1_3_SET_PDU1[0],
        (U4)0x36300003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4937_GVIFSNDREDPERR2_1_TBL[4] = {
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDREDPERR2_1_SET_PDU1[0],
        (U4)0x36340003U
    },
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDREDPERR2_1_SET_PDU2[0],
        (U4)0x36380003U
    },
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDREDPERR2_1_SET_PDU3[0],
        (U4)0x363C0003U
    },
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDREDPERR2_1_SET_PDU4[0],
        (U4)0x36400003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4937_GVIFSNDREDPERR2_2_TBL[2] = {
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDREDPERR2_2_RD_PDU1[0],
        (U4)0x36440002U
    },
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDREDPERR2_2_RD_PDU2[0],
        (U4)0x36480002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4937_GVIFSNDREDPERR2_3_TBL[1] = {
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDREDPERR2_3_SET_PDU1[0],
        (U4)0x364C0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4937_GVIFSNDREDPERR3_1_TBL[4] = {
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDREDPERR3_1_SET_PDU1[0],
        (U4)0x36500003U
    },
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDREDPERR3_1_SET_PDU2[0],
        (U4)0x36540003U
    },
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDREDPERR3_1_SET_PDU3[0],
        (U4)0x36580003U
    },
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDREDPERR3_1_SET_PDU4[0],
        (U4)0x365C0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4937_GVIFSNDREDPERR3_2_TBL[2] = {
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDREDPERR3_2_RD_PDU1[0],
        (U4)0x36600002U
    },
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDREDPERR3_2_RD_PDU2[0],
        (U4)0x36640002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4937_GVIFSNDREDPERR3_3_TBL[1] = {
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDREDPERR3_3_SET_PDU1[0],
        (U4)0x36680003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4937_GVIFSNDRHDCPSTOP_TBL[4] = {
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDRHDCPSTOP_SET_PDU1[0],
        (U4)0x366C0003U
    },
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDRHDCPSTOP_SET_PDU2[0],
        (U4)0x36700003U
    },
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDRHDCPSTOP_SET_PDU3[0],
        (U4)0x36740003U
    },
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDRHDCPSTOP_SET_PDU4[0],
        (U4)0x36780003U
    }
};

/*===================================================================================================================================*/
/*  void    vd_g_Pict_GvifSndrInit(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Pict_GvifSndrInit(void)
{
    U4  u4_t_cnt;

    u1_s_gvifsnd_state = (U1)GVIFSENDER_SEQ_IDLE;

    u2_s_gvifsnd_regstep = (U2)0U;
    u4_s_gvifsnd_i2c_ack_wait_time = (U4)0U;
    u2_s_gvifsnd_reg_btwn_time = (U2)0xFFFFU;

    u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP0;
    u2_s_gvifsnd_cycchk_timer = (U2)0U;

    u1_s_gvifsnd_devrst_sts = (U1)GVIFSENDER_DEVRST_STEP0;
    u2_s_gvifsnd_devrst_timer = (U2)0U;
    u1_s_gvifsnd_devrst_drec_cnt = (U1)0U;

    u1_s_gvifsnd_linkchk_sts = (U1)GVIFSENDER_LINKCHK_STEP0;
    u2_s_gvifsnd_linkchk_timer = (U2)0U;
    u1_s_gvifsnd_linkchk_err_cnt = (U1)0U;
    u1_s_gvifsnd_edperr1_pre_sts = (U1)CXD4937_EDPERR_STS_INIT;
    u1_s_gvifsnd_edperr1_drec_cnt = (U1)0U;
    u1_s_gvifsnd_edperr2_pre_sts = (U1)CXD4937_EDPERR_STS_INIT;
    u1_s_gvifsnd_edperr2_drec_cnt = (U1)0U;
    u1_s_gvifsnd_edperr3_pre_sts = (U1)CXD4937_EDPERR_STS_INIT;
    u1_s_gvifsnd_edperr3_drec_cnt = (U1)0U;
    u1_s_gvifsnd_videoerr_drec_cnt = (U1)0U;
    u1_s_gvifsnd_loadererr_drec_cnt = (U1)0U;
    u1_s_gvifsnd_cncterr_drec_cnt = (U1)0U;
    u1_s_gvifsnd_linkerr_pre_sts = (U1)CXD4937_LINKERR_STS_INIT;
    u1_s_gvifsnd_linkerr_drec_cnt = (U1)0U;

    /* フリーランタイマ用配列初期化 */
    for(u4_t_cnt = 0; u4_t_cnt < (U4)GPT_FRT_USELPSD_NUM_PARAM; u4_t_cnt++){
        u4_g_gvifsnd_gvif3tx_linkup_frt_stamp[u4_t_cnt] = 0;
        u4_g_gvifsnd_hdcp_wait_frt_stamp[u4_t_cnt] = 0;
    }

    /* Init時のフリーランタイマ取得 */
    u4_g_gvifsnd_gvif3tx_linkup_frt_stamp[GPT_FRT_USELPSD_BASE] = u4_g_Gpt_FrtGetUsElapsed(vdp_PTR_NA);

    u2_s_gvifsnd_gvif3tx_devrst_poll_cnt       = (U2)0U;

    u1_g_gvifsnd_gvif3tx_overall_step   = (U1)MCU_STEP_GVIF3TX_OVERALL_1;
    u1_s_gvifsnd_gvif3tx_edpset_step   = (U1)MCU_STEP_GVIF3TX_eDPSET_1;
    u1_s_gvifsnd_gvif3tx_outset_step   = (U1)MCU_STEP_GVIF3TX_OUTSET_1;
    u2_s_gvifsnd_gvif3tx_hdcp_step     = (U2)MCU_STEP_GVIF3TX_HDCP_01;
    u2_s_gvifsnd_gvif3tx_link_wait_time         = (U2)0U;

    u1_s_gvifsnd_hdcp_auth_start_trg          = (U1)FALSE;
    u1_s_gvifsnd_hdcp_authwait_err_cnt   = (U1)0U;
    u1_s_gvifsnd_hdcp_encrypt_err_cnt    = (U1)0U;
    u1_s_gvifsnd_hdcp_pointd_err_cnt     = (U1)0U;

    /* Misc Type 39h：HDMI 05h：C-Disp_HDCP認証応答配列初期化 */
    u1_s_gvifsnd_hdcp_act_tbl[MCU_HDCP_SUBTYPE]    = (U1)0x05U;    /* 05h：C-Disp_HDCP認証応答 */
    u1_s_gvifsnd_hdcp_act_tbl[MCU_HDCP_RSLT]       = (U1)0x01U;    /* 01h：認証失敗 */
    for(u4_t_cnt = (U4)MCU_HDCP_MAX_DEVS_EXCEEDED; u4_t_cnt < (U4)MCU_MISC_HDCP_ACT; u4_t_cnt++){
        u1_s_gvifsnd_hdcp_act_tbl[u4_t_cnt] = (U1)0U;
    }

    u1_s_gvifsnd_hdcp_dev_cnt           = (U1)0U;
    u1_s_gvifsnd_dptns_err_drec_cnt = (U1)0U;

    u1_s_gvifsnd_hpd_flag = (U1)FALSE;

    Mcu_Sys_Pwr_GvifSndr_Init();

}

/*****************************************************************************
  Function      : Mcu_Sys_Pwr_GvifSndr_Init
  Description   : 初期化関数
  param[in/out] : none
  return        : none
  Note          : 読出し用バッファの初期化,固定値ではない書込み用バッファの初期化
*****************************************************************************/
static void Mcu_Sys_Pwr_GvifSndr_Init( void )
{
    U4 u4_t_cnt;

    /*  データリード用テーブル初期化 */
    u1_sp_CXD4957_GVIFSNDR_OUTSET_GVIF3TX0_ACTIVATED_RD_PDU2[0] = (U1)CXD4937_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_CXD4957_GVIFSNDR_OUTSET_GVIF3TX0_ACTIVATED_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_CXD4957_GVIFSNDR_HDCPTX_STATUS_RD_PDU2[0] = (U1)CXD4937_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_CXD4957_GVIFSNDR_HDCPTX_STATUS_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_CXD4957_GVIFSNDR_HDCPTX_EVENT_RD_PDU2[0] = (U1)CXD4937_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_CXD4957_GVIFSNDR_HDCPTX_EVENT_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル(BurstRead)初期化 */
    u1_sp_CXD4957_GVIFSNDR_HDCPTX_DEVS_CASCADE_RD_PDU2[0] = (U1)CXD4937_I2C_SLAVEADR_RD;    /* Slave Address */
    for(u4_t_cnt = (U4)1U; u4_t_cnt < (U4)3U; u4_t_cnt++) {
        u1_sp_CXD4957_GVIFSNDR_HDCPTX_DEVS_CASCADE_RD_PDU2[u4_t_cnt] = (U1)0U;    /* 読出しデータ初期値 */
    }

    /* Receiver ID取得 5Byte Read 書込み用テーブル(Write Address可変)初期化 */
    u1_sp_CXD4957_GVIFSNDR_HDCPTX_DEV_ID_RD_PDU1[0] = (U1)CXD4937_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_CXD4957_GVIFSNDR_HDCPTX_DEV_ID_RD_PDU1[1] = (U1)0x50U;    /* Write Address初期値(定期処理内で更新) */

    /*  データリード用テーブル(BurstRead)初期化 */
    u1_sp_CXD4957_GVIFSNDR_HDCPTX_DEV_ID_RD_PDU2[0] = (U1)CXD4937_I2C_SLAVEADR_RD;    /* Slave Address */
    for(u4_t_cnt = (U4)1U; u4_t_cnt < (U4)6U; u4_t_cnt++) {
        u1_sp_CXD4957_GVIFSNDR_HDCPTX_DEV_ID_RD_PDU2[u4_t_cnt] = (U1)0U;    /* 読出しデータ初期値 */
    }

    /*  データリード用テーブル初期化 */
    u1_sp_CXD4957_GVIFSNDR_HDCP_VIDEOIN_RD_PDU2[0] = (U1)CXD4937_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_CXD4957_GVIFSNDR_HDCP_VIDEOIN_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_CXD4957_GVIFSNDR_HDCPTX_ENC_RD_PDU2[0] = (U1)CXD4937_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_CXD4957_GVIFSNDR_HDCPTX_ENC_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_CXD4957_GVIFSNDR_GVIF3TX0_ACT_RD_PDU2[0] = (U1)CXD4937_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_CXD4957_GVIFSNDR_GVIF3TX0_ACT_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_CXD4957_GVIFSNDRDEVERR_RD_PDU2[0] = (U1)CXD4937_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_CXD4957_GVIFSNDRDEVERR_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_CXD4957_GVIFSNDRLINKERR_RD_PDU2[0] = (U1)CXD4937_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_CXD4957_GVIFSNDRLINKERR_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_CXD4957_GVIFSNDRINPUTERR_RD_PDU2[0] = (U1)CXD4937_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_CXD4957_GVIFSNDRINPUTERR_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_CXD4957_GVIFSNDRLODERERR_RD_PDU2[0] = (U1)CXD4937_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_CXD4957_GVIFSNDRLODERERR_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_CXD4957_GVIFSNDRCONNECTERR_RD_PDU2[0] = (U1)CXD4937_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_CXD4957_GVIFSNDRCONNECTERR_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_CXD4957_GVIFSNDRLINKCHK_RD_PDU2[0] = (U1)CXD4937_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_CXD4957_GVIFSNDRLINKCHK_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_CXD4937_GVIFSNDREDPERR1_2_RD_PDU2[0] = (U1)CXD4937_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_CXD4937_GVIFSNDREDPERR1_2_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_CXD4937_GVIFSNDREDPERR2_2_RD_PDU2[0] = (U1)CXD4937_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_CXD4937_GVIFSNDREDPERR2_2_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_CXD4937_GVIFSNDREDPERR3_2_RD_PDU2[0] = (U1)CXD4937_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_CXD4937_GVIFSNDREDPERR3_2_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */
}

/*===================================================================================================================================*/
/*  void    vd_g_Pict_GvifSndrRoutine(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Pict_GvifSndrRoutine(void)
{
    /* [(C-Disp)制御フロー]シートの「定期監視フロー」前まで */
    static const U2  MCU_PWRON_TIME_GVIFTX  =   (U2)(55U / MCU_GVIFTX_TASK_TIME);    /* min:55ms 11タスク経過後を設定 */

    U1   u1_u_time_chk;

    /* Ack Wait Timer Countr Increment */
    if(u4_s_gvifsnd_i2c_ack_wait_time < (U4)U4_MAX){        /* 暫定 I2Cアクセス時にカウンタクリアされるため定期では常にカウントアップする */
        u4_s_gvifsnd_i2c_ack_wait_time++;
    }

    /* Wait t3 監視処理 */
    vd_s_Pict_GvifSndrPollingRst();

    u1_u_time_chk    =   u1_s_Pict_GvifSndrTimChk(u2_s_gvifsnd_gvif3tx_devrst_poll_cnt, MCU_PWRON_TIME_GVIFTX);

    if(u1_u_time_chk ==  (U1)TRUE){
        vd_s_Pict_GvifSndrOverallFlow();
    }

    switch (u1_s_gvifsnd_state){
        case GVIFSENDER_SEQ_IDLE:                                       /* IDLE */
            /* Timer Clear */
            u2_s_gvifsnd_cycchk_timer = (U2)0;
            /* Power ON Check */
            if(u1_g_gvifsnd_gvif3tx_overall_step == (U1)PICT_CXD_PWRON_COMP){
                /* State Update */
                u1_s_gvifsnd_state = (U1)GVIFSENDER_SEQ_CYC;
                /* Timer Start */
                u2_s_gvifsnd_cycchk_timer++;
            }
            break;
        case GVIFSENDER_SEQ_CYC:                                        /* CYCLIC */
            /* GvifSender Cyc Check */
            vd_s_Pict_GvifSndrCycChk();
            break;
        case GVIFSENDER_SEQ_DEVRST:                                     /* DEVRST */
            /* GvifSender Device Reset Wait */
            vd_s_Pict_GvifSndrDevRst();
            break;
        case GVIFSENDER_SEQ_LINKCHK:                                    /* LINKCHK */
            /* GvifSender Link Check Wait */
            vd_s_Pict_GvifSndrGvifLinkChk();
            break;
        default:                                                        /* FAIL */
            /* State Reset */
            u1_s_gvifsnd_state = (U1)GVIFSENDER_SEQ_IDLE;
            /* Process Reset */
            u1_s_gvifsnd_devrst_sts = (U1)GVIFSENDER_DEVRST_STEP0;
            break;
    }
}

/*===================================================================================================================================*/
/*  U1    u1_s_Pict_GvifSndrTimChk(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u2_a_tim_cnt  :  Timer Count /  u2_a_wait_tim  :  Wait Time                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_Pict_GvifSndrTimChk(const U2 u2_a_tim_cnt, const U2 u2_a_wait_tim)
{
    U1  u1_t_ret;

    u1_t_ret = (U1)FALSE;
    if(u2_a_tim_cnt >= u2_a_wait_tim){
        u1_t_ret = (U1)TRUE;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  void    vd_g_Pict_GvifSndrCycChk(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Pict_GvifSndrCycChk(void)
{   /* 暫定　I/Fメモ 100-4-7 定期監視制御 */
    static const U2     GVIFSENDER_CYCCHK_POLING = (U2)(250U / GVIFSENDER_TASK_TIME);   /* t9 min:250ms */

    U1      u1_t_time_chk_flg;
    U1      u1_t_reg_req_sts;                                       /* Register Read/Write Request Status */
    U1      u1_t_reg_read_result;                                   /* Register Read Result */

    switch (u1_s_gvifsnd_cycchk_sts){
        case GVIFSNDR_CYCCHK_STEP0:                                       /* STEP0 */
            u1_t_time_chk_flg = u1_s_Pict_GvifSndrTimChk(u2_s_gvifsnd_cycchk_timer, GVIFSENDER_CYCCHK_POLING);
            if(u1_t_time_chk_flg == (U1)TRUE){
                /* Timer Clear */
                u2_s_gvifsnd_cycchk_timer = (U2)0;

                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP1;
            }
            else{
                u2_s_gvifsnd_cycchk_timer++;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP1:                                         /* STEP1 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)CXD4937_BANKSET_WRINUM,
                                                           CXD4937_BANKSET, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                           st_sp_CXD4957_GVIFSNDRBANK0_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP2;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP2:                                         /* STEP2 */
        /* ----------100-4-7 定期監視制御 デバイス異常検知---------- */
            /* Read Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGREAD(&u2_s_gvifsnd_regstep, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                           st_sp_CXD4957_GVIFSNDRDEVERR_RD_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP3;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP3:                                         /* STEP3 */
            u1_t_reg_read_result = st_sp_CXD4957_GVIFSNDRDEVERR_RD_TBL[1].u1p_pdu[1];
            if(u1_t_reg_read_result != (U1)PICT_GVIFSNDRDEVERR_NML){                   /* Device Error */
                /* State Update */
                u1_s_gvifsnd_state = (U1)GVIFSENDER_SEQ_DEVRST;
                /* Device Restart */
                vd_s_Pict_GvifSndrDevRst();
                /* Process Reset */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP0;
            }
            else {
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP4;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP4:                                         /* STEP4 */
        /* ----------100-4-7 定期監視制御 GVIF3リンク切れ検知---------- */
            /* Read Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGREAD(&u2_s_gvifsnd_regstep, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                           st_sp_CXD4957_GVIFSNDRLINKERR_RD_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                u1_t_reg_read_result = st_sp_CXD4957_GVIFSNDRLINKERR_RD_TBL[1].u1p_pdu[1];
                u1_t_reg_read_result &= (U1)PICT_CXD_REG_MASK_BIT_7;                        /* Get Link Error Result */
                if(u1_t_reg_read_result == (U1)PICT_GVIFSNDRGVIFLINK_NML){                  /* Link Normal */
                    u1_s_gvifsnd_linkerr_pre_sts = (U1)CXD4937_LINKERR_STS_NORMAL;
                    /* Next Process */
                    u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP8;
                }
                else{
                    if((u1_s_gvifsnd_linkerr_drec_cnt < (U1)CXD4937_LINKERR_DREC_CNT_MAX)       /* Drec Counter < 3 */
                    && ((u1_s_gvifsnd_linkerr_pre_sts == (U1)CXD4937_LINKERR_STS_INIT)           /* Initial Error */
                     || (u1_s_gvifsnd_linkerr_pre_sts == (U1)CXD4937_LINKERR_STS_NORMAL))){      /* Normal -> Error */
                        u1_s_gvifsnd_linkerr_drec_cnt++;
                        vd_CXD4937_DREC_REQ((U1)SYSECDRC_DREC_ID_10, u1_s_gvifsnd_linkerr_drec_cnt, (U1)0x00U);
                        u1_s_gvifsnd_linkerr_pre_sts = (U1)CXD4937_LINKERR_STS_ERROR;
                    }
                    /* Next Process */                                                      /* Link Error */
                    u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP5;
                }
            }
            break;
        case GVIFSNDR_CYCCHK_STEP5:                                         /* STEP5 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)CXD4937_GVIFSNDRHDCPSTOP_WRINUM,
                                                           CXD4937_GVIFSNDRHDCPSTOP, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                           st_sp_CXD4937_GVIFSNDRHDCPSTOP_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP6;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP6:                                         /* STEP6 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)CXD4937_BANKSET_WRINUM,
                                                           CXD4937_BANKSET_WAIT_7MS, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                           st_sp_CXD4957_GVIFSNDRBANK0_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP7;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP7:                                         /* STEP7 */
            /* State Update */
            u1_s_gvifsnd_state = (U1)GVIFSENDER_SEQ_LINKCHK;
            /* Error Count Clear */
            u1_s_gvifsnd_linkchk_err_cnt = (U1)0U;
            /* Link Error Check */
            vd_s_Pict_GvifSndrGvifLinkChk();
            /* Process Reset */
            u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP0;
            break;
        case GVIFSNDR_CYCCHK_STEP8:                                         /* STEP8 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)CXD4937_BANKSET_WRINUM,
                                                           CXD4937_BANKSET, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                           st_sp_CXD4937_GVIFSNDRBANK4_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP9;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP9:                                         /* STEP9 */
        /* ----------100-4-7 定期監視制御 eDP入力異常検知---------- */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)CXD4937_GVIFSNDREDPERR_SET1_WRINUM,
                                                           CXD4937_GVIFSNDREDPERR_SET1, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                           st_sp_CXD4937_GVIFSNDREDPERR1_1_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP10;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP10:                                        /* STEP10 */
            /* Read Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGREAD(&u2_s_gvifsnd_regstep, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                            st_sp_CXD4937_GVIFSNDREDPERR1_2_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP11;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP11:                                        /* STEP11 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)CXD4937_GVIFSNDREDPERR_SET2_WRINUM,
                                                           CXD4937_GVIFSNDREDPERR_SET2, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                           st_sp_CXD4937_GVIFSNDREDPERR1_3_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP12;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP12:                                        /* STEP12 */
            u1_t_reg_read_result = st_sp_CXD4937_GVIFSNDREDPERR1_2_TBL[1].u1p_pdu[1];
            u1_t_reg_read_result = u1_t_reg_read_result & (U1)PICT_GVIFSNDREDPERR_1;        /* Get eDP Input Error Result */
            if(u1_t_reg_read_result != (U1)PICT_GVIFSNDREDPERR_1){                          /* eDP Input Error */
                if((u1_s_gvifsnd_edperr1_drec_cnt < (U1)CXD4937_EDPERR1_DREC_CNT_MAX)       /* Drec Counter < 3 */
                && ((u1_s_gvifsnd_edperr1_pre_sts == (U1)CXD4937_EDPERR_STS_INIT)           /* Initial Error */
                 || (u1_s_gvifsnd_edperr1_pre_sts == (U1)CXD4937_EDPERR_STS_NORMAL))){      /* Normal -> Error */
                    u1_s_gvifsnd_edperr1_drec_cnt++;
                    vd_CXD4937_DREC_REQ((U1)SYSECDRC_DREC_ID_3, u1_s_gvifsnd_edperr1_drec_cnt, (U1)0x00U);
                    u1_s_gvifsnd_edperr1_pre_sts = (U1)CXD4937_EDPERR_STS_ERROR;
                }
            }
            else{
                u1_s_gvifsnd_edperr1_pre_sts = (U1)CXD4937_EDPERR_STS_NORMAL;
            }
            /* Next Process */
            u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP13;
            break;
        case GVIFSNDR_CYCCHK_STEP13:                                        /* STEP13 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)CXD4937_GVIFSNDREDPERR_SET1_WRINUM,
                                                           CXD4937_GVIFSNDREDPERR_SET1, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                           st_sp_CXD4937_GVIFSNDREDPERR2_1_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP14;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP14:                                        /* STEP14 */
            /* Read Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGREAD(&u2_s_gvifsnd_regstep, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                            st_sp_CXD4937_GVIFSNDREDPERR2_2_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP15;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP15:                                        /* STEP15 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)CXD4937_GVIFSNDREDPERR_SET2_WRINUM,
                                                           CXD4937_GVIFSNDREDPERR_SET2, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                           st_sp_CXD4937_GVIFSNDREDPERR2_3_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP16;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP16:                                        /* STEP16 */
            u1_t_reg_read_result = st_sp_CXD4937_GVIFSNDREDPERR2_2_TBL[1].u1p_pdu[1];
            u1_t_reg_read_result = u1_t_reg_read_result & (U1)PICT_GVIFSNDREDPERR_2;        /* Get eDP Input Error Result */
            if(u1_t_reg_read_result != (U1)PICT_GVIFSNDREDPERR_2){                          /* eDP Input Error */
                if((u1_s_gvifsnd_edperr2_drec_cnt < (U1)CXD4937_EDPERR2_DREC_CNT_MAX)       /* Drec Counter < 3 */
                && ((u1_s_gvifsnd_edperr2_pre_sts == (U1)CXD4937_EDPERR_STS_INIT)           /* Initial Error */
                 || (u1_s_gvifsnd_edperr2_pre_sts == (U1)CXD4937_EDPERR_STS_NORMAL))){      /* Normal -> Error */
                    u1_s_gvifsnd_edperr2_drec_cnt++;
                    vd_CXD4937_DREC_REQ((U1)SYSECDRC_DREC_ID_4, u1_s_gvifsnd_edperr2_drec_cnt, (U1)0x00U);
                    u1_s_gvifsnd_edperr2_pre_sts = (U1)CXD4937_EDPERR_STS_ERROR;
                }
            }
            else{
                u1_s_gvifsnd_edperr2_pre_sts = (U1)CXD4937_EDPERR_STS_NORMAL;
            }
            /* Next Process */
            u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP17;
            break;
        case GVIFSNDR_CYCCHK_STEP17:                                        /* STEP17 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)CXD4937_GVIFSNDREDPERR_SET1_WRINUM,
                                                           CXD4937_GVIFSNDREDPERR_SET1, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                           st_sp_CXD4937_GVIFSNDREDPERR3_1_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP18;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP18:                                        /* STEP18 */
            /* Read Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGREAD(&u2_s_gvifsnd_regstep, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                            st_sp_CXD4937_GVIFSNDREDPERR3_2_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP19;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP19:                                        /* STEP19 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)CXD4937_GVIFSNDREDPERR_SET2_WRINUM,
                                                           CXD4937_GVIFSNDREDPERR_SET2, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                           st_sp_CXD4937_GVIFSNDREDPERR3_3_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP20;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP20:                                        /* STEP20 */
            u1_t_reg_read_result = st_sp_CXD4937_GVIFSNDREDPERR3_2_TBL[1].u1p_pdu[1];
            u1_t_reg_read_result = u1_t_reg_read_result & (U1)PICT_CXD_REG_MASK_BIT_0;      /* Get eDP Input Error Result */
            if(u1_t_reg_read_result != (U1)PICT_CXD_REG_MASK_BIT_0){                        /* eDP Input Error */
                if((u1_s_gvifsnd_edperr3_drec_cnt < (U1)CXD4937_EDPERR3_DREC_CNT_MAX)       /* Drec Counter < 3 */
                && ((u1_s_gvifsnd_edperr3_pre_sts == (U1)CXD4937_EDPERR_STS_INIT)           /* Initial Error */
                 || (u1_s_gvifsnd_edperr3_pre_sts == (U1)CXD4937_EDPERR_STS_NORMAL))){      /* Normal -> Error */
                    u1_s_gvifsnd_edperr3_drec_cnt++;
                    vd_CXD4937_DREC_REQ((U1)SYSECDRC_DREC_ID_5, u1_s_gvifsnd_edperr3_drec_cnt, (U1)0x00U);
                    u1_s_gvifsnd_edperr3_pre_sts = (U1)CXD4937_EDPERR_STS_ERROR;
                }
            }
            else{
                u1_s_gvifsnd_edperr3_pre_sts = (U1)CXD4937_EDPERR_STS_NORMAL;
            }
            /* Next Process */
            u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP21;
            break;
        case GVIFSNDR_CYCCHK_STEP21:                                        /* STEP21 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)CXD4937_BANKSET_WRINUM,
                                                           CXD4937_BANKSET, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                           st_sp_CXD4957_GVIFSNDRBANK0_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP22;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP22:                                        /* STEP22 */
        /* ----------100-4-7 定期監視制御 入力映像異常検知---------- */
            /* Read Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGREAD(&u2_s_gvifsnd_regstep, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                            st_sp_CXD4957_GVIFSNDRINPUTERR_RD_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP23;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP23:                                        /* STEP23 */
            u1_t_reg_read_result = st_sp_CXD4957_GVIFSNDRINPUTERR_RD_TBL[1].u1p_pdu[1];
            u1_t_reg_read_result = u1_t_reg_read_result & (U1)PICT_CXD_REG_MASK_BIT_0;      /* Get Input Error Result */
            if(u1_t_reg_read_result != (U1)PICT_CXD_REG_MASK_BIT_0){                        /* Input Error */
                if(u1_s_gvifsnd_videoerr_drec_cnt < (U1)CXD4937_VIDEOERR_DREC_CNT_MAX){     /* Drec Counter < 3 */
                    u1_s_gvifsnd_videoerr_drec_cnt++;
                    vd_CXD4937_DREC_REQ((U1)SYSECDRC_DREC_ID_6, u1_s_gvifsnd_videoerr_drec_cnt, (U1)0x00U);
                }
            }
            /* Next Process */
            u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP24;
            break;
        case GVIFSNDR_CYCCHK_STEP24:                                        /* STEP24 */
        /* ----------100-4-7 定期監視制御 LOADER異常検知---------- */
            /* Read Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGREAD(&u2_s_gvifsnd_regstep, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                            st_sp_CXD4957_GVIFSNDRLODERERR_RD_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP25;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP25:                                        /* STEP25 */
            u1_t_reg_read_result = st_sp_CXD4957_GVIFSNDRLODERERR_RD_TBL[1].u1p_pdu[1];
            u1_t_reg_read_result = u1_t_reg_read_result & ((U1)PICT_CXD_REG_MASK_BIT_7 | (U1)PICT_CXD_REG_MASK_BIT_6);   /* Get Loader Error Result */
            if(u1_t_reg_read_result != (U1)PICT_GVIFSNDRLODERERR_NML){                      /* Loader Error */
                if(u1_s_gvifsnd_loadererr_drec_cnt < (U1)CXD4937_LOADERERR_DREC_CNT_MAX){   /* Drec Counter < 3 */
                    u1_s_gvifsnd_loadererr_drec_cnt++;
                    vd_CXD4937_DREC_REQ((U1)SYSECDRC_DREC_ID_7, u1_s_gvifsnd_loadererr_drec_cnt, u1_t_reg_read_result);
                }
            }
            /* Next Process */
            u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP26;
            break;
        case GVIFSNDR_CYCCHK_STEP26:                                        /* STEP26 */
        /* ----------100-4-7 定期監視制御 GVIF3接続異常検知---------- */
            /* Read Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGREAD(&u2_s_gvifsnd_regstep, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                            st_sp_CXD4957_GVIFSNDRCONNECTERR_RD_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP27;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP27:                                        /* STEP27 */
            u1_t_reg_read_result = st_sp_CXD4957_GVIFSNDRCONNECTERR_RD_TBL[1].u1p_pdu[1];
            u1_t_reg_read_result = u1_t_reg_read_result & (U1)PICT_CXD_REG_MASK_BIT_0;      /* Get Connect Error Result */
            if(u1_t_reg_read_result != (U1)PICT_CXD_REG_MASK_BIT_0){                        /* Connect Error */
                if(u1_s_gvifsnd_cncterr_drec_cnt < (U1)CXD4937_CNCTERR_DREC_CNT_MAX){       /* Drec Counter < 3 */
                    u1_s_gvifsnd_cncterr_drec_cnt++;
                    vd_CXD4937_DREC_REQ((U1)SYSECDRC_DREC_ID_8, u1_s_gvifsnd_cncterr_drec_cnt, (U1)0x00U);
                }
            }
            /* Next Process */
            u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP28;
            break;
        case GVIFSNDR_CYCCHK_STEP28:                                        /* STEP28 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)CXD4957_GVIFSNDRERRCLEAR_SET_WRINUM,
                                                           CXD4957_GVIFSNDRERRCLEAR_SET, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                           st_sp_CXD4957_GVIFSNDRERRCLEAR_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Process Reset */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP0;
            }
            break;
        default:                                                                /* FAIL */
            /* Process Reset */
            u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP0;
            break;
    }
}

/*===================================================================================================================================*/
/*  void    vd_s_Pict_GvifSndrDevRst(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Pict_GvifSndrDevRst(void)
{
    static const U2     GVIFSENDER_DEVRST_TIME = (U2)(10U / GVIFSENDER_TASK_TIME);  /* t10 min:10ms */

    U1  u1_t_rst_time_chk_flg;

    switch (u1_s_gvifsnd_devrst_sts){
        case GVIFSENDER_DEVRST_STEP0:                                       /* STEP0 */
            /* Timer Clear */
            u2_s_gvifsnd_devrst_timer = (U2)0;

            if(u1_s_gvifsnd_devrst_drec_cnt < (U1)CXD4937_DEVERR_DREC_CNT_MAX){     /* Drec Counter < 3 */
                u1_s_gvifsnd_devrst_drec_cnt++;
                vd_CXD4937_DREC_REQ((U1)SYSECDRC_DREC_ID_2, u1_s_gvifsnd_devrst_drec_cnt, (U1)0x00U);
            }

            /* GVIF-TC(C-DISP)-RST = L */
            vd_PICT_CXD_GVIF_TX_RST_L();
            /* Timer Start */
            u2_s_gvifsnd_devrst_timer++;
            /* Next Process */
            u1_s_gvifsnd_devrst_sts = (U1)GVIFSENDER_DEVRST_STEP1;
            break;
        case GVIFSENDER_DEVRST_STEP1:                                       /* STEP1 */
            u1_t_rst_time_chk_flg = u1_s_Pict_GvifSndrTimChk(u2_s_gvifsnd_devrst_timer, GVIFSENDER_DEVRST_TIME);
            if(u1_t_rst_time_chk_flg == (U1)TRUE){
                /* GVIF-TC(C-DISP)-RST = H */
                vd_PICT_CXD_GVIF_TX_RST_H();
                /* State Update */
                u1_s_gvifsnd_state = (U1)GVIFSENDER_SEQ_IDLE;
                /* Process Reset */
                u1_s_gvifsnd_devrst_sts = (U1)GVIFSENDER_DEVRST_STEP0;
            }
            else{
                u2_s_gvifsnd_devrst_timer++;
            }
            break;
        default:                                                                /* FAIL */
            /* State Reset */
            u1_s_gvifsnd_state = (U1)GVIFSENDER_SEQ_CYC;
            /* Process Reset */
            u1_s_gvifsnd_devrst_sts = (U1)GVIFSENDER_DEVRST_STEP0;
            break;
    }
}

/*===================================================================================================================================*/
/*  void    vd_s_Pict_GvifSndrGvifLinkChk(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Pict_GvifSndrGvifLinkChk(void)
{
    static const U2     GVIFSENDER_LINKCHK_WAIT_TIME = (U2)(500U / GVIFSENDER_TASK_TIME);  /* t11 min:500ms */

    U1      u1_t_gviflink_time_chk_flg;
    U1      u1_t_reg_req_sts;                                       /* Register Read/Write Request Status */
    U1      u1_t_reg_read_result;                                   /* Register Read Result */

    switch (u1_s_gvifsnd_linkchk_sts){
        case GVIFSENDER_LINKCHK_STEP0:                                                      /* STEP0 */
            /* Read Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGREAD(&u2_s_gvifsnd_regstep, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                           st_sp_CXD4957_GVIFSNDRLINKCHK_RD_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_linkchk_sts = (U1)GVIFSENDER_LINKCHK_STEP1;
            }
            break;
        case GVIFSENDER_LINKCHK_STEP1:                                                      /* STEP1 */
            u1_t_reg_read_result = st_sp_CXD4957_GVIFSNDRLINKCHK_RD_TBL[1].u1p_pdu[1];
            u1_t_reg_read_result = u1_t_reg_read_result & (U1)PICT_CXD_REG_MASK_BIT_0;          /* Get Link Check Result */
            if(u1_t_reg_read_result == (U1)PICT_CXD_REG_MASK_BIT_0){                            /* Link Check Error */
                /* Next Process */
                u1_s_gvifsnd_linkchk_sts = (U1)GVIFSENDER_LINKCHK_STEP2;
            }else{
                /* Error Count Increment */
                u1_s_gvifsnd_linkchk_err_cnt++;
                /* Next Process */
                u1_s_gvifsnd_linkchk_sts = (U1)GVIFSENDER_LINKCHK_STEP3;
            }
            break;
        case GVIFSENDER_LINKCHK_STEP2:                                                      /* STEP2 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)CXD4957_GVIFSNDRERRCLEAR_SET_WRINUM,
                                                           CXD4957_GVIFSNDRERRCLEAR_SET, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                           st_sp_CXD4957_GVIFSNDRERRCLEAR_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Return to HDCP Authentication Flow */
                vd_s_Gvif3txSeqCtl(MCU_STEP_GVIF3TX_OVERALL_4);
                /* State Reset */
                u1_s_gvifsnd_state = (U1)GVIFSENDER_SEQ_IDLE;
                /* Process Reset */
                u1_s_gvifsnd_linkchk_sts = (U1)GVIFSENDER_LINKCHK_STEP0;
            }
            break;
        case GVIFSENDER_LINKCHK_STEP3:                                                      /* STEP3 */
            if(u1_s_gvifsnd_linkchk_err_cnt >= (U1)PICT_GVIFSNDRGVIFLINK_CHK_CNT_MAX){
                /* State Reset */
                u1_s_gvifsnd_state = (U1)GVIFSENDER_SEQ_CYC;
                /* Process Reset */
                u1_s_gvifsnd_linkchk_sts = (U1)GVIFSENDER_LINKCHK_STEP0;
            }
            else {
                /* Timer Clear */
                u2_s_gvifsnd_linkchk_timer = (U2)0;
                /* Timer Start */
                u2_s_gvifsnd_linkchk_timer++;
                /* Next Process */
                u1_s_gvifsnd_linkchk_sts = (U1)GVIFSENDER_LINKCHK_STEP4;
            }
            break;
        case GVIFSENDER_LINKCHK_STEP4:                                                      /* STEP4 */
            u1_t_gviflink_time_chk_flg = u1_s_Pict_GvifSndrTimChk(u2_s_gvifsnd_linkchk_timer, GVIFSENDER_LINKCHK_WAIT_TIME);
            if(u1_t_gviflink_time_chk_flg == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_linkchk_sts = (U1)GVIFSENDER_LINKCHK_STEP0;
            }
            else{
                u2_s_gvifsnd_linkchk_timer++;
            }
            break;
        default:                                                                            /* FAIL */
            /* State Reset */
            u1_s_gvifsnd_state = (U1)GVIFSENDER_SEQ_CYC;
            /* Process Reset */
            u1_s_gvifsnd_linkchk_sts = (U1)GVIFSENDER_LINKCHK_STEP0;
            break;
    }
}

/*===================================================================================================================================*/
/* void            vd_s_Gvif3txSeqCtl(const U1 u1_a_MODE)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void            vd_s_Gvif3txSeqCtl(const U1 u1_a_MODE)
{
    U4  u4_t_cnt;

    switch (u1_a_MODE)
    {
    case (U1)MCU_STEP_GVIF3TX_OVERALL_1:
        /* 初期設定用初期化処理 */
        /* do nothing */
        /* fall through */
    case (U1)MCU_STEP_GVIF3TX_OVERALL_2:
        /* eDP設定用所為化処理 */
        u1_s_gvifsnd_gvif3tx_edpset_step   = (U1)MCU_STEP_GVIF3TX_eDPSET_1;
        /* fall through */
    case (U1)MCU_STEP_GVIF3TX_OVERALL_3:
        /* 出力設定用初期化処理 */
        u1_s_gvifsnd_gvif3tx_outset_step   = (U1)MCU_STEP_GVIF3TX_OUTSET_1;
        /* fall through */
    case (U1)MCU_STEP_GVIF3TX_OVERALL_4:
        /* HDCP認証用初期化処理 */
        u2_s_gvifsnd_gvif3tx_hdcp_step     = (U2)MCU_STEP_GVIF3TX_HDCP_01;

        u1_s_gvifsnd_hdcp_authwait_err_cnt   = (U1)0U;
        u1_s_gvifsnd_hdcp_encrypt_err_cnt    = (U1)0U;
        u1_s_gvifsnd_hdcp_pointd_err_cnt     = (U1)0U;
        u1_s_gvifsnd_hdcp_dev_cnt           = (U1)0U;

        /* Misc Type 39h：HDMI 05h：C-Disp_HDCP認証応答配列初期化 */
        u1_s_gvifsnd_hdcp_act_tbl[MCU_HDCP_SUBTYPE]    = (U1)0x05U;    /* 05h：C-Disp_HDCP認証応答 */
        u1_s_gvifsnd_hdcp_act_tbl[MCU_HDCP_RSLT]       = (U1)0x01U;    /* 01h：認証失敗 */
        for(u4_t_cnt = (U4)MCU_HDCP_MAX_DEVS_EXCEEDED; u4_t_cnt < (U4)MCU_MISC_HDCP_ACT; u4_t_cnt++){
            u1_s_gvifsnd_hdcp_act_tbl[u4_t_cnt] = (U1)0U;
        }

        /* 全モード共通処理 */
        u1_g_gvifsnd_gvif3tx_overall_step   = u1_a_MODE;
        u2_s_gvifsnd_gvif3tx_link_wait_time         = (U2)0U;
        u4_s_gvifsnd_i2c_ack_wait_time  = (U4)0U;
        u2_s_gvifsnd_regstep         = (U2)0U;
        u2_s_gvifsnd_reg_btwn_time      = (U2)0xFFFFU;
        Mcu_Sys_Pwr_GvifSndr_Init();
        break;
    default:
        /* do nothing */
        break;
    }
}

/*****************************************************************************
  Function      : vd_s_Pict_GvifSndrPollingRst
  Description   :
  param[in/out] :
  return        : -
  Note          : /GVIF-TX(C-DISP)-RST=Hi 監視
*****************************************************************************/
static void    vd_s_Pict_GvifSndrPollingRst( void )
{
    U1   u1_t_dio_ret;
    U4      u4_t_cnt;

    u1_t_dio_ret =   Dio_ReadChannel(MCU_PORT_GVIF_CDISP_RST);

    if(u1_t_dio_ret  ==  (U1)STD_LOW){
        u1_s_gvifsnd_state = (U1)GVIFSENDER_SEQ_IDLE;

        u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP0;
        u2_s_gvifsnd_cycchk_timer = (U2)0U;

        u1_s_gvifsnd_devrst_sts = (U1)GVIFSENDER_DEVRST_STEP0;
        u2_s_gvifsnd_devrst_timer = (U2)0U;

        u1_s_gvifsnd_linkchk_sts = (U1)GVIFSENDER_LINKCHK_STEP0;
        u2_s_gvifsnd_linkchk_timer = (U2)0U;

        u2_s_gvifsnd_gvif3tx_devrst_poll_cnt       = (U2)0U;
        u1_g_gvifsnd_gvif3tx_overall_step   = (U1)MCU_STEP_GVIF3TX_OVERALL_1;
        u1_s_gvifsnd_gvif3tx_edpset_step   = (U1)MCU_STEP_GVIF3TX_eDPSET_1;
        u1_s_gvifsnd_gvif3tx_outset_step   = (U1)MCU_STEP_GVIF3TX_OUTSET_1;
        u2_s_gvifsnd_gvif3tx_hdcp_step     = (U2)MCU_STEP_GVIF3TX_HDCP_01;
        u2_s_gvifsnd_gvif3tx_link_wait_time         = (U2)0U;
        u4_s_gvifsnd_i2c_ack_wait_time  = (U4)0U;
        u2_s_gvifsnd_regstep         = (U2)0U;
        u2_s_gvifsnd_reg_btwn_time      = (U2)0xFFFFU;
        u1_s_gvifsnd_hdcp_auth_start_trg          = (U1)FALSE;
        u1_s_gvifsnd_hdcp_authwait_err_cnt   = (U1)0U;
        u1_s_gvifsnd_hdcp_encrypt_err_cnt    = (U1)0U;
        u1_s_gvifsnd_hdcp_pointd_err_cnt     = (U1)0U;
        u1_s_gvifsnd_hdcp_dev_cnt           = (U1)0U;

        /* Misc Type 39h：HDMI 05h：C-Disp_HDCP認証応答配列初期化 */
        u1_s_gvifsnd_hdcp_act_tbl[MCU_HDCP_SUBTYPE]    = (U1)0x05U;    /* 05h：C-Disp_HDCP認証応答 */
        u1_s_gvifsnd_hdcp_act_tbl[MCU_HDCP_RSLT]       = (U1)0x01U;    /* 01h：認証失敗 */
        for(u4_t_cnt = (U4)MCU_HDCP_MAX_DEVS_EXCEEDED; u4_t_cnt < (U4)MCU_MISC_HDCP_ACT; u4_t_cnt++){
            u1_s_gvifsnd_hdcp_act_tbl[u4_t_cnt] = (U1)0U;
        }

        Mcu_Sys_Pwr_GvifSndr_Init();
    }
    else if((u1_t_dio_ret  ==  (U1)STD_HIGH) &&
        (u2_s_gvifsnd_gvif3tx_devrst_poll_cnt < (U2)U2_MAX)){
        u2_s_gvifsnd_gvif3tx_devrst_poll_cnt++;
    }
    else{
        /* do nothing */
    }
}

/*****************************************************************************
  Function      : vd_s_Pict_GvifSndrOverallFlow
  Description   :
  param[in/out] :
  return        : -
  Note          : GVIF送信機 100-4-1.(C-Disp) 全体フロー
*****************************************************************************/
static void    vd_s_Pict_GvifSndrOverallFlow( void )
{
    U1   u1_t_rslt;

    switch (u1_g_gvifsnd_gvif3tx_overall_step)
    {
    case MCU_STEP_GVIF3TX_OVERALL_1:
        /* 100-4-2.初期設定フロー */
        u1_t_rslt = u1_s_Pict_GvifSndrIniSet();

        if(u1_t_rslt == (U1)TRUE){
            u1_g_gvifsnd_gvif3tx_overall_step = MCU_STEP_GVIF3TX_OVERALL_2;
        }
        break;

    case MCU_STEP_GVIF3TX_OVERALL_2:
        /* 100-4-3.eDP設定フロー */
        u1_t_rslt = u1_s_Pict_GvifSndrEdpSet();

        if(u1_t_rslt == (U1)TRUE){
            u1_g_gvifsnd_gvif3tx_overall_step = MCU_STEP_GVIF3TX_OVERALL_3;
        }
        break;

    case MCU_STEP_GVIF3TX_OVERALL_3:
        /* 100-4-4.出力設定フロー */
        u1_t_rslt = u1_s_Pict_GvifSndrOutSet();

        if(u1_t_rslt == (U1)TRUE){
            u1_g_gvifsnd_gvif3tx_overall_step = MCU_STEP_GVIF3TX_OVERALL_4;
        }
        break;

    case MCU_STEP_GVIF3TX_OVERALL_4:
        /* 100-4-5.HDCP認証フロー */
        u1_t_rslt = u1_s_Pict_GvifSndrHdcpAuth();

        if(u1_t_rslt == (U1)TRUE){
            u1_g_gvifsnd_gvif3tx_overall_step = MCU_STEP_GVIF3TX_OVERALL_FIN;
        }
        break;

    case MCU_STEP_GVIF3TX_OVERALL_FIN:
        /* 100-4-7.定期監視フロー */
        /* do nothing */
        break;

    default:
        break;
    }
}

/*****************************************************************************
  Function      : u1_s_Pict_GvifSndrIniSet
  Description   :
  param[in/out] :
  return        : -
  Note          : GVIF送信機 100-4-2.初期設定フロー
*****************************************************************************/
static U1   u1_s_Pict_GvifSndrIniSet( void )
{
    static const ST_REG_WRI_REQ GVIFTX_INISET[MCU_WRINUM_GVIF3TX_INISET] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0},
        {        1,         4,         0},
        {        5,         4,         0},
        {        9,         3,         0},
        {       12,         1,         0},
        {       13,         1,         0},
        {       14,         1,         0},
        {       15,         4,         0},
        {       19,         1,         0},
        {       20,         1,         0},
        {       21,         1,         0}
    };
    U1   u1_t_return;     /* 戻り値：フロー完了通知 */

    u1_t_return      = (U1)FALSE;

    /* レジスタ書込み処理 */
    u1_t_return = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)MCU_WRINUM_GVIF3TX_INISET,
                                              GVIFTX_INISET, &u4_s_gvifsnd_i2c_ack_wait_time,
                                              st_sp_CXD4957_GVIFSNDR_SETREG_INIT, &u2_s_gvifsnd_reg_btwn_time);

    return(u1_t_return);
}

/*****************************************************************************
  Function      : u1_s_Pict_GvifSndrEdpSet
  Description   :
  param[in/out] :
  return        : -
  Note          : GVIF送信機 100-4-3.eDP設定フロー
*****************************************************************************/
static U1   u1_s_Pict_GvifSndrEdpSet( void )
{
    /* 100-4-3.eDP設定フロー START~eDPポート設定 */
    static const ST_REG_WRI_REQ GVIFTX_eDFSET_1[MCU_WRINUM_GVIF3TX_eDPSET_1] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0},
        {        1,         2,         0}
    };
    /* 100-4-3.eDP設定フロー eDP用レジスタ設定 10-5-3 レシーバ */
    static const ST_REG_WRI_REQ GVIFTX_eDFSET_2[MCU_WRINUM_GVIF3TX_eDPSET_2] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         2,         0},
        {        2,         2,         0},
        {        4,         2,         0},
        {        6,         2,         0},
        {        8,         2,         0},
        {       10,         2,         0},
        {       12,         2,         0},
        {       14,         2,         0},
        {       16,         2,         0},
        {       18,         2,         0},
        {       20,         2,         0},
        {       22,         2,         0},
        {       24,         2,         0},
        {       26,         2,         0},
        {       28,         2,         0},
        {       30,         2,         0},
        {       32,         2,         0},
        {       34,         2,         0},
        {       36,         2,         0},
        {       38,         2,         0},
        {       40,         2,         0},
        {       42,         2,         0},
        {       44,         2,         0},
        {       46,         2,         0},
        {       48,         2,         0},
        {       50,         2,         0},
        {       52,         2,         0},
        {       54,         2,         0},
        {       56,         2,         0},
        {       58,         2,         0},
        {       60,         2,         0},
        {       62,         2,         0},
        {       64,         2,         0},
        {       66,         2,         0},
        {       68,         2,         0},
        {       70,         2,         0},
        {       72,         2,         0},
        {       74,         2,         0},
        {       76,         2,         0},
        {       78,         2,         0},
        {       80,         2,         0},
        {       82,         2,         0},
        {       84,         2,         0},
        {       86,         2,         0},
        {       88,         2,         0},
        {       90,         2,         0},
        {       92,         2,         0},
        {       94,         2,         0},
        {       96,         2,         0},
        {       98,         2,         0},
        {      100,         2,         0},
        {      102,         2,         0},
        {      104,         2,         0},
        {      106,         2,         0},
        {      108,         2,         0},
        {      110,         2,         0},
        {      112,         2,         0},
        {      114,         2,         0},
        {      116,         2,         0},
        {      118,         2,         0},
        {      120,         2,         0},
        {      122,         2,         0},
        {      124,         2,         0},
        {      126,         2,         0},
        {      128,         2,         0},
        {      130,         2,         0},
        {      132,         2,         0},
        {      134,         2,         0},
        {      136,         2,         0},
        {      138,         2,         0},
        {      140,         2,         0},
        {      142,         2,         0},
        {      144,         2,         0},
        {      146,         2,         0},
        {      148,         2,         0},
        {      150,         2,         0},
        {      152,         2,         0},
        {      154,         2,         0},
        {      156,         2,         0},
        {      158,         2,         0},
        {      160,         2,         0},
        {      162,         2,         0},
        {      164,         2,         0},
        {      166,         2,         0},
        {      168,         2,         0},
        {      170,         2,         0},
        {      172,         2,         0},
        {      174,         2,         0},
        {      176,         2,         0},
        {      178,         2,         0},
        {      180,         2,         0},
        {      182,         2,         0},
        {      184,         2,         0},
        {      186,         2,         0},
        {      188,         2,         0},
        {      190,         2,         0},
        {      192,         2,         0},
        {      194,         2,         0},
        {      196,         2,         0},
        {      198,         2,         0},
        {      200,         2,         0},
        {      202,         2,         0},
        {      204,         2,         0},
        {      206,         2,         0},
        {      208,         2,         0},
        {      210,         2,         0},
        {      212,         2,         0},
        {      214,         2,         0},
        {      216,         2,         0},
        {      218,         2,         0},
        {      220,         2,         0},
        {      222,         2,         0},
        {      224,         2,         0},
        {      226,         2,         0},
        {      228,         2,         0}
    };
    /* 100-4-3.eDP設定フロー eDP用レジスタ設定 10-5-3 DPCD */
    static const ST_REG_WRI_REQ GVIFTX_eDFSET_3[MCU_WRINUM_GVIF3TX_eDPSET_3] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         2,         0},
        {        2,         2,         0},
        {        4,         2,         0},
        {        6,         2,         0},
        {        8,         2,         0},
        {       10,         2,         0},
        {       12,         2,         0},
        {       14,         2,         0},
        {       16,         2,         0},
        {       18,         2,         0},
        {       20,         2,         0},
        {       22,         2,         0},
        {       24,         2,         0},
        {       26,         2,         0},
        {       28,         2,         0},
        {       30,         2,         0},
        {       32,         2,         0},
        {       34,         2,         0},
        {       36,         2,         0},
        {       38,         2,         0},
        {       40,         2,         0},
        {       42,         2,         0},
        {       44,         2,         0},
        {       46,         2,         0},
        {       48,         2,         0},
        {       50,         2,         0}
    };
    /* 100-4-3.eDP設定フロー EDID選択設定 */
    static const ST_REG_WRI_REQ GVIFTX_eDFSET_4[MCU_WRINUM_GVIF3TX_eDPSET_4] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0}
    };
    /* 100-4-3.eDP設定フロー Bank切り替え（Bank0）~Bank切り替え（Bank4） */
    static const ST_REG_WRI_REQ GVIFTX_eDFSET_5[MCU_WRINUM_GVIF3TX_eDPSET_5] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0},
        {        1,         1,         0},
        {        2,         1,         0}
    };
    /* 100-4-3.eDP設定フロー eDP用レジスタ設定 10-5-5 Hot Plug Detect */
    static const ST_REG_WRI_REQ GVIFTX_eDFSET_6[MCU_WRINUM_GVIF3TX_eDPSET_6] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         4,         0},
        {        4,         1,         0},
        {        5,         1,         0}
    };

    U1   u1_t_sts;        /* 書込み状況 */
    U1   u1_t_return;     /* 戻り値：フロー完了通知 */

    u1_t_sts         = (U1)FALSE;
    u1_t_return      = (U1)FALSE;

    switch (u1_s_gvifsnd_gvif3tx_edpset_step)
    {
    case MCU_STEP_GVIF3TX_eDPSET_1:
        /* レジスタ書込み処理 */
        u1_t_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)MCU_WRINUM_GVIF3TX_eDPSET_1,
                                               GVIFTX_eDFSET_1, &u4_s_gvifsnd_i2c_ack_wait_time,
                                               st_sp_CXD4957_GVIFSNDR_EDPSET1, &u2_s_gvifsnd_reg_btwn_time);

        if(u1_t_sts == (U1)TRUE){
            /* 全書込み完了 次状態に遷移 */
            u1_s_gvifsnd_gvif3tx_edpset_step = (U1)MCU_STEP_GVIF3TX_eDPSET_2;
        }
        break;

    case MCU_STEP_GVIF3TX_eDPSET_2:
        /* レジスタ書込み処理 */
        u1_t_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)MCU_WRINUM_GVIF3TX_eDPSET_2,
                                               GVIFTX_eDFSET_2, &u4_s_gvifsnd_i2c_ack_wait_time,
                                               st_sp_CXD4957_GVIFSNDR_EDPSET_REC, &u2_s_gvifsnd_reg_btwn_time);

        if(u1_t_sts == (U1)TRUE){
            /* 全書込み完了 次状態に遷移 */
            u1_s_gvifsnd_gvif3tx_edpset_step = (U1)MCU_STEP_GVIF3TX_eDPSET_3;
        }
        break;

    case MCU_STEP_GVIF3TX_eDPSET_3:
        /* レジスタ書込み処理 */
        u1_t_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)MCU_WRINUM_GVIF3TX_eDPSET_3,
                                               GVIFTX_eDFSET_3, &u4_s_gvifsnd_i2c_ack_wait_time,
                                               st_sp_CXD4957_GVIFSNDR_EDPSET_DPCD, &u2_s_gvifsnd_reg_btwn_time);

        if(u1_t_sts == (U1)TRUE){
            /* 全書込み完了 次状態に遷移 */
            u1_s_gvifsnd_gvif3tx_edpset_step = (U1)MCU_STEP_GVIF3TX_eDPSET_4;
        }
        break;

    case MCU_STEP_GVIF3TX_eDPSET_4:
        /* レジスタ書込み処理 */
        u1_t_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)MCU_WRINUM_GVIF3TX_eDPSET_4,
                                               GVIFTX_eDFSET_4, &u4_s_gvifsnd_i2c_ack_wait_time,
                                               st_sp_CXD4957_GVIFSNDR_EDPSET2, &u2_s_gvifsnd_reg_btwn_time);

        if(u1_t_sts == (U1)TRUE){
            /* 全書込み完了 次状態に遷移 */
            u1_s_gvifsnd_gvif3tx_edpset_step = (U1)MCU_STEP_GVIF3TX_eDPSET_5;
        }
        break;

    case MCU_STEP_GVIF3TX_eDPSET_5:
        /* レジスタ書込み処理 */
        u1_t_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)MCU_WRINUM_GVIF3TX_eDPSET_5,
                                               GVIFTX_eDFSET_5, &u4_s_gvifsnd_i2c_ack_wait_time,
                                               st_sp_CXD4957_GVIFSNDR_EDPSET3, &u2_s_gvifsnd_reg_btwn_time);

        if(u1_t_sts == (U1)TRUE){
            /* 全書込み完了 次状態に遷移 */
            u1_s_gvifsnd_gvif3tx_edpset_step = (U1)MCU_STEP_GVIF3TX_eDPSET_6;
        }
        break;

    case MCU_STEP_GVIF3TX_eDPSET_6:
        /* レジスタ書込み処理 */
        u1_t_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)MCU_WRINUM_GVIF3TX_eDPSET_6,
                                               GVIFTX_eDFSET_6, &u4_s_gvifsnd_i2c_ack_wait_time,
                                               st_sp_CXD4957_GVIFSNDR_EDPSET_HPD, &u2_s_gvifsnd_reg_btwn_time);

        if(u1_t_sts == (U1)TRUE){
            /* 全書込み完了 次状態に遷移 */
            u1_s_gvifsnd_gvif3tx_edpset_step = (U1)MCU_STEP_GVIF3TX_eDPSET_FIN;
            u1_t_return                = (U1)TRUE;
        }
        break;

    case MCU_STEP_GVIF3TX_eDPSET_FIN:
        u1_t_return  = (U1)TRUE;
        break;

    default:
        /* 異常時：本処理を最初からやり直す */
        u1_s_gvifsnd_gvif3tx_edpset_step = (U1)MCU_STEP_GVIF3TX_eDPSET_1;
        break;
    }

    return(u1_t_return);
}

/*****************************************************************************
  Function      : u1_s_Pict_GvifSndrOutSet
  Description   :
  param[in/out] :
  return        : -
  Note          : GVIF送信機 100-4-4.出力設定フロー
*****************************************************************************/
static U1   u1_s_Pict_GvifSndrOutSet( void )
{
    /* GVIF3リンク確立確認ポーリング周期 t4 */
    static const U2  MCU_PWRON_TIME_GVIFTX_POLING  = (50U / MCU_GVIFTX_TASK_TIME);    /* typ:50ms */
    /* リンク確立完了 確認用マスク */
    static const U1   MCU_GVIF3TX0_ACTIVATED_MSK    = (0x01U);
    /* 100-4-4.出力設定フロー Bank切り替え（Bank0） */
    static const ST_REG_WRI_REQ GVIFTX_OUTSET_3[MCU_WRINUM_GVIF3TX_OUTSET_3] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0}
    };
    /* 100-4-4.出力設定フロー A点～Wati t4 */
    static const ST_REG_WRI_REQ GVIFTX_OUTSET_1[MCU_WRINUM_GVIF3TX_OUTSET_1] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0}
    };
    /* 100-4-4.出力設定フロー Bank切り替え（Bank7）～エラークリア解除設定 */
    static const ST_REG_WRI_REQ GVIFTX_OUTSET_2[MCU_WRINUM_GVIF3TX_OUTSET_2] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0},
        {        1,         1,         0},
        {        2,         1,         0},
        {        3,         2,         0}
    };

    U1   u1_u_time_chk_poling;    /* wait t4監視 */
    U1   u1_t_sts;                /* 書込み状況 */
    U1   u1_t_return;             /* 戻り値：フロー完了通知 */
    U4   u4_t_frt_elpsd;
    U1   u1_t_reg_read;           /* レジスタ読出し値 */
    U1   u1_t_dio_ret;            /* Port Status */

    u1_t_sts             = (U1)FALSE;
    u1_t_return          = (U1)FALSE;
    u1_u_time_chk_poling = (U1)0U;
    u4_t_frt_elpsd       = u4_g_Gpt_FrtGetUsElapsed(u4_g_gvifsnd_gvif3tx_linkup_frt_stamp);
    u1_t_reg_read        = (U1)0U;

    switch (u1_s_gvifsnd_gvif3tx_outset_step)
    {
    case MCU_STEP_GVIF3TX_OUTSET_1:
        /* レジスタ書込み処理 */
        u1_t_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)MCU_WRINUM_GVIF3TX_OUTSET_3,
                                               GVIFTX_OUTSET_3, &u4_s_gvifsnd_i2c_ack_wait_time,
                                               st_sp_CXD4957_GVIFSNDR_OUTSET3, &u2_s_gvifsnd_reg_btwn_time);

        if(u1_t_sts == (U1)TRUE){
            /* 全書込み完了 次状態に遷移 */
            u1_s_gvifsnd_gvif3tx_outset_step = (U1)MCU_STEP_GVIF3TX_OUTSET_2;
        }
        break;

    case MCU_STEP_GVIF3TX_OUTSET_2:
        /* レジスタ書込み処理 */
        /* ToDo：I2Cの説明次第で要変更 */
        u1_t_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)MCU_WRINUM_GVIF3TX_OUTSET_1,
                                               GVIFTX_OUTSET_1, &u4_s_gvifsnd_i2c_ack_wait_time,
                                               st_sp_CXD4957_GVIFSNDR_OUTSET1, &u2_s_gvifsnd_reg_btwn_time);
        if(u1_t_sts == (U1)TRUE){
            /* 全書込み完了したら次状態に遷移 */
            u1_s_gvifsnd_gvif3tx_outset_step = (U1)MCU_STEP_GVIF3TX_OUTSET_3;
        }
        break;

    case MCU_STEP_GVIF3TX_OUTSET_3:
        u1_u_time_chk_poling = u1_s_Pict_GvifSndrTimChk(u2_s_gvifsnd_gvif3tx_link_wait_time, MCU_PWRON_TIME_GVIFTX_POLING);
        if(u1_u_time_chk_poling == (U1)TRUE){
            /* Wati t4完了 次状態に遷移 */
            u1_s_gvifsnd_gvif3tx_outset_step = (U1)MCU_STEP_GVIF3TX_OUTSET_4;
            u2_s_gvifsnd_gvif3tx_link_wait_time       = (U2)0U;
        }
        else{
            u2_s_gvifsnd_gvif3tx_link_wait_time++;
        }
        break;

    case MCU_STEP_GVIF3TX_OUTSET_4:
        /* レジスタ読出し処理 */
        u1_t_sts = u1_PICT_CXD_I2C_CTRL_REGREAD(&u2_s_gvifsnd_regstep, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                st_sp_CXD4957_GVIFSNDR_OUTSET_GVIF3TX0_ACTIVATED_RD, &u2_s_gvifsnd_reg_btwn_time);

        if(u1_t_sts == (U1)TRUE){
            /* 全書込み完了 次状態に遷移 */
            u1_s_gvifsnd_gvif3tx_outset_step = (U1)MCU_STEP_GVIF3TX_OUTSET_5;
        }
        break;

    case MCU_STEP_GVIF3TX_OUTSET_5:
        u1_t_reg_read = st_sp_CXD4957_GVIFSNDR_OUTSET_GVIF3TX0_ACTIVATED_RD[1].u1p_pdu[1];
        if((u1_t_reg_read & (U1)MCU_GVIF3TX0_ACTIVATED_MSK) != (U1)0x01U){
            /* リンク確立未完了 */
            u1_t_dio_ret =   Dio_ReadChannel(GVIF3TX_PORT_CDISP_WAKE);  /* Get Display Status */

            if((u4_t_frt_elpsd > (U4)MCU_GVIF_LNK_TIMEOUT)
            && (u1_t_dio_ret == (Dio_LevelType)STD_HIGH)){
                /* GVIF3リンクエラー処理 */
                (void)Dio_WriteChannel(MCU_PORT_GVIF_CDISP_RST , MCU_DIO_LOW);/* デバイスリセット */
                /* ダイレコ保存 */
                vd_CXD4937_DREC_REQ((U1)SYSECDRC_DREC_ID_1, (U1)0x00U, (U1)0x00U);

                u1_s_gvifsnd_gvif3tx_outset_step = (U1)MCU_STEP_GVIF3TX_OUTSET_STP;
                /* 初期化完了通知 */
                vd_g_XspiIviSub1PowerDevInitCmpApp((U1)XSPI_IVI_POWER_GVIFSEND_INI);
            }
            else{
                /* A点へ戻る */
                u1_s_gvifsnd_gvif3tx_outset_step = (U1)MCU_STEP_GVIF3TX_OUTSET_2;
            }
        }
        else{
            /* 次状態に遷移 */
            u1_s_gvifsnd_gvif3tx_outset_step = (U1)MCU_STEP_GVIF3TX_OUTSET_6;
        }
        break;

    case MCU_STEP_GVIF3TX_OUTSET_6:
        /* レジスタ書込み処理 */
        u1_t_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)MCU_WRINUM_GVIF3TX_OUTSET_2,
                                               GVIFTX_OUTSET_2, &u4_s_gvifsnd_i2c_ack_wait_time,
                                               st_sp_CXD4957_GVIFSNDR_OUTSET2, &u2_s_gvifsnd_reg_btwn_time);

        if(u1_t_sts == (U1)TRUE){
            /* 全書込み完了 次状態に遷移 */
            u1_s_gvifsnd_gvif3tx_outset_step   = (U1)MCU_STEP_GVIF3TX_OUTSET_FIN;
            u1_t_return                  = (U1)TRUE;
        }
        break;

    case MCU_STEP_GVIF3TX_OUTSET_STP:
        /* 次回起動まで制御停止 */
        break;

    case MCU_STEP_GVIF3TX_OUTSET_FIN:
        u1_t_return = (U1)TRUE;
        break;

    default:
        /* 異常ステータスの場合は最初からやり直す */
        u1_s_gvifsnd_gvif3tx_outset_step = (U1)MCU_STEP_GVIF3TX_OUTSET_1;
        break;
    }

    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1       u1_s_Pict_GvifSndrHdcpAuth( void )                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    GVIF送信機 100-4-5.HDCP認証フロー                                                                                 */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_Pict_GvifSndrHdcpAuth( void )
{
    /* GVIF3リンク確立確認ポーリング周期 t4 */
    static const U2     u2_s_HDCP_WAITTIME_T4           = (U2)(50U / MCU_GVIFTX_TASK_TIME);    /* typ:50ms */
    /* GVIF3リンク確立確認 確認用マスク */
    static const U1     u1_s_GVIF3TX0_ACTIVATED_MSK     = (U1)(0x01U);
    /* HDCP認証処理状態確認 確認用マスク */
    static const U1     u1_s_HDCP_AUTH_MSK              = (U1)(0x08U);
    /* HDCP認証処理状態確認 処理分岐発生のエラー回数 */
    static const U1     u1_s_HDCP_ERR_NUM               = (U1)(4U);
    /* HDCPイベントモニタエラー 確認用マスク */
    static const U1     u1_s_HDCPTX_EVENT_ERR_MSK       = (U1)(0x80U);
    /* 認証完了＆リボケーションチェック準備完了 確認用マスク */
    static const U1     u1_s_HDCPTX_EVENT_RDY_MSK       = (U1)(0x03U);
    /* HDCPTX_MAX_DEVS_EXCEEDED 確認用マスク */
    static const U1     u1_s_DEVS_EXCEEDED_MSK          = (U1)(0x80U);
    /* HDCPTX_MAX_DEVS_EXCEEDED 異常判定用値 */
    static const U1     u1_s_DEVS_EXCEEDED_ERR_MSK      = (U1)(0x01U);
    /* HDCPTX_DEVICE_COUNT(デバイス総数) 確認用マスク */
    static const U1     u1_s_DEVICE_COUNT_MSK           = (U1)(0x1FU);
    /* DCPTX_MAX_CASCADE_EXCEEDED 確認用マスク */
    static const U1     u1_s_CASCADE_EXCEEDED_MSK       = (U1)(0x80U);
    /* DCPTX_MAX_CASCADE_EXCEEDED 異常判定用値 */
    static const U1     u1_s_CASCADE_EXCEEDED_ERR_MSK   = (U1)(0x01U);
    /* HDCPTX_DEPTH (接続段数) 確認用マスク */
    static const U1     u1_s_DEPTH_MSK                  = (U1)(0x07U);
    /* Receiver ID総数 */
    static const U1     u1_s_RCVID_NUM                  = (U1)(5U);
    /* 2フレーム時間待ち t7 */
    static const U2     u2_s_HDCP_WAITTIME_T7           = (U2)(40U / MCU_GVIFTX_TASK_TIME);    /* min:40ms */
    /* HDCP暗号化状態確認 確認用マスク */
    static const U1     u1_s_HDCP_ENCRYPT_STS_MSK       = (U1)(0x01U);
    /* HDCP暗号化状態確認 処理分岐発生のエラー回数 */
    static const U1     u1_s_HDCP_ENCRYPT_ERR_NUM       = (U1)(4U);
    /* D点 処理分岐発生のエラー回数 */
    static const U1     u1_s_HDCP_POINT_D_ERR_NUM       = (U1)(4U);
    /* HDCP暗号化状態確認 確認用マスク */
    static const U1     u1_s_HDCP_VIDEOIN_STS_MSK       = (U1)(0x01U);

    /* 100-4-5.(C-Disp) HDCP認証フロー[1/7] Bank切り替え（Bank4）～[2/7] HDCPTX Connect 1 設定 */
    static const ST_REG_WRI_REQ GVIFTX_HDCP_1[MCU_WRINUM_GVIF3TX_HDCP_1] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0},
        {        1,         2,         0},
        {        3,         1,         0},
        {        4,         1,         7U/MCU_GVIFTX_TASK_TIME},
        {        5,         1,         7U/MCU_GVIFTX_TASK_TIME},
        {        6,         1,         7U/MCU_GVIFTX_TASK_TIME},
        {        7,         1,         7U/MCU_GVIFTX_TASK_TIME},
        {        8,         1,         7U/MCU_GVIFTX_TASK_TIME}
    };
    /* 100-4-5.(C-Disp) HDCP認証フロー[2/7] C点～HDCP認証コマンド発行（HDCP_AUTH_REQコマンド発行） */
    static const ST_REG_WRI_REQ GVIFTX_HDCP_2[MCU_WRINUM_GVIF3TX_HDCP_2] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         7U/MCU_GVIFTX_TASK_TIME},
    };
    /* 100-4-5.(C-Disp) HDCP認証フロー[3/7] K点～イベントクリア */
    static const ST_REG_WRI_REQ GVIFTX_HDCP_3[MCU_WRINUM_GVIF3TX_HDCP_3] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         7U/MCU_GVIFTX_TASK_TIME},
    };
    /* 100-4-5.(C-Disp) HDCP認証フロー[4/7] F点～Bank切り替え（Bank4） */
    static const ST_REG_WRI_REQ GVIFTX_HDCP_4[MCU_WRINUM_GVIF3TX_HDCP_4] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         7U/MCU_GVIFTX_TASK_TIME},
        {        1,         1,         7U/MCU_GVIFTX_TASK_TIME},
        {        2,         1,         0},
        {        3,         1,         0}
    };
    /* 100-4-5.(C-Disp) HDCP認証フロー[4/7] eDP用レジスタ設定 100-5-5.Hot Plug Detect */
    static const ST_REG_WRI_REQ GVIFTX_HDCP_HPD[MCU_WRINUM_GVIF3TX_HDCP_HPD] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         4,         0},
        {        4,         1,         0},
        {        5,         1,         0}
    };
    /* 100-4-5.(C-Disp) HDCP認証フロー[5/7] Bank切り替え（Bank0） */
    static const ST_REG_WRI_REQ GVIFTX_HDCP_BANK0[MCU_WRINUM_GVIF3TX_HDCP_BANK0] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0}
    };
    /* 100-4-5.(C-Disp) HDCP認証フロー[5/7] Bank切り替え（Bank4） */
    static const ST_REG_WRI_REQ GVIFTX_HDCP_BANK4[MCU_WRINUM_GVIF3TX_HDCP_BANK4] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0}
    };
    /* 100-4-5.(C-Disp) HDCP認証フロー[5/7] Bank切り替え（Bank8）～F点へ遷移 */
    static const ST_REG_WRI_REQ GVIFTX_HDCP_5[MCU_WRINUM_GVIF3TX_HDCP_5] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0}
    };
    /* 100-4-5.(C-Disp) HDCP認証フロー[6/7] 100-4-6.HDCP認証停止フロー */
    static const ST_REG_WRI_REQ GVIFTX_HDCP_STOP[MCU_WRINUM_GVIF3TX_HDCP_STOP] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         7U/MCU_GVIFTX_TASK_TIME},
        {        1,         1,         7U/MCU_GVIFTX_TASK_TIME},
        {        2,         1,         20U/MCU_GVIFTX_TASK_TIME},
        {        3,         1,         7U/MCU_GVIFTX_TASK_TIME}
    };
    /* 100-4-5.(C-Disp) HDCP認証フロー[6/7] Bank切り替え（Bank0） */
    static const ST_REG_WRI_REQ GVIFTX_HDCP_6[MCU_WRINUM_GVIF3TX_HDCP_6] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         7U/MCU_GVIFTX_TASK_TIME}
    };
    /* 100-4-5.(C-Disp) HDCP認証フロー[7/7] Bank切り替え（Bank0）～Bank切り替え（Bank4） */
    static const ST_REG_WRI_REQ GVIFTX_HDCP_7[MCU_WRINUM_GVIF3TX_HDCP_7] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         7U/MCU_GVIFTX_TASK_TIME},
        {        1,         2,         0}
    };
    /* 100-4-5.(C-Disp) HDCP認証フロー[7/7] Bank切り替え（Bank8） */
    static const ST_REG_WRI_REQ GVIFTX_HDCP_8[MCU_WRINUM_GVIF3TX_HDCP_8] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0}
    };

    U1      u1_t_return;
    U1      u1_t_sts;
    U4      u4_t_loopcont;
    U1      u1_t_timchk;        /* wait t4監視 */
    U1      u1_t_rg_read;
    U4      u4_t_frt_hdcp;
    U1      u1_t_dev_num;       /* Receiver ID格納位置 */

    u1_t_return = (U1)FALSE;

    switch (u2_s_gvifsnd_gvif3tx_hdcp_step)
    {
    case MCU_STEP_GVIF3TX_HDCP_01:
        if(u1_s_gvifsnd_hdcp_auth_start_trg == (U1)TRUE) {
            u2_s_gvifsnd_gvif3tx_hdcp_step = (U2)MCU_STEP_GVIF3TX_HDCP_05;
        }
        else{
            u2_s_gvifsnd_gvif3tx_hdcp_step = (U2)MCU_STEP_GVIF3TX_HDCP_02;
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_02:
        u1_t_timchk = u1_s_Pict_GvifSndrTimChk(u2_s_gvifsnd_gvif3tx_link_wait_time, u2_s_HDCP_WAITTIME_T4);
        if(u1_t_timchk == (U1)TRUE){
            /* Wati t4完了 次状態に遷移 */
            u2_s_gvifsnd_gvif3tx_hdcp_step = (U2)MCU_STEP_GVIF3TX_HDCP_03;
            u2_s_gvifsnd_gvif3tx_link_wait_time     = (U2)0U;
        }
        else{
            u2_s_gvifsnd_gvif3tx_link_wait_time++;
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_03:
        /* レジスタ読出し処理 */
        u1_t_sts =  u1_PICT_CXD_I2C_CTRL_REGREAD(&u2_s_gvifsnd_regstep, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                 st_sp_CXD4957_GVIFSNDR_GVIF3TX0_ACT_RD, &u2_s_gvifsnd_reg_btwn_time);

        if(u1_t_sts == (U1)TRUE) {
            /* 次状態に遷移 */
            u2_s_gvifsnd_gvif3tx_hdcp_step = (U2)MCU_STEP_GVIF3TX_HDCP_04;
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_04:
        u1_t_rg_read = st_sp_CXD4957_GVIFSNDR_GVIF3TX0_ACT_RD[1].u1p_pdu[1];
        if((u1_t_rg_read & u1_s_GVIF3TX0_ACTIVATED_MSK) == u1_s_GVIF3TX0_ACTIVATED_MSK){
            /* リンク確立完了 */
            /* B点まで戻る */
            u2_s_gvifsnd_gvif3tx_hdcp_step = (U2)MCU_STEP_GVIF3TX_HDCP_01;
        }
        else {
            /* リンク確立未完了 */
            /* HDCPフローリセット */
            u2_s_gvifsnd_gvif3tx_hdcp_step     = (U2)MCU_STEP_GVIF3TX_HDCP_01;
            /* A点まで戻る */
            u1_s_gvifsnd_gvif3tx_outset_step   = (U1)MCU_STEP_GVIF3TX_OUTSET_2;
            u1_g_gvifsnd_gvif3tx_overall_step   = (U1)MCU_STEP_GVIF3TX_OVERALL_3;
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_05:
        /* レジスタ書込み処理 */
        u1_t_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)MCU_WRINUM_GVIF3TX_HDCP_1,
                                               GVIFTX_HDCP_1, &u4_s_gvifsnd_i2c_ack_wait_time,
                                               st_sp_CXD4957_GVIFSNDR_HDCP1, &u2_s_gvifsnd_reg_btwn_time);

        if(u1_t_sts == (U1)TRUE){
            /* 全書込み完了 次状態に遷移 */
            u2_s_gvifsnd_gvif3tx_hdcp_step = (U2)MCU_STEP_GVIF3TX_HDCP_06;
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_06:
        /* レジスタ書込み処理 */
        u1_t_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)MCU_WRINUM_GVIF3TX_HDCP_2,
                                               GVIFTX_HDCP_2, &u4_s_gvifsnd_i2c_ack_wait_time,
                                               st_sp_CXD4957_GVIFSNDR_HDCP2, &u2_s_gvifsnd_reg_btwn_time);

        if(u1_t_sts == (U1)TRUE){
            /* 全書込み完了 次状態に遷移 */
            u2_s_gvifsnd_gvif3tx_hdcp_step = (U2)MCU_STEP_GVIF3TX_HDCP_07;
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_07:
        /* レジスタ読出し処理 */
        u1_t_sts =  u1_PICT_CXD_I2C_CTRL_REGREAD_WAIT(&u2_s_gvifsnd_regstep, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                      st_sp_CXD4957_GVIFSNDR_HDCPTX_STATUS_RD, &u2_s_gvifsnd_reg_btwn_time, (U1)MCU_I2C_WAIT_B89);

        if(u1_t_sts == (U1)TRUE) {
            /* 次状態に遷移 */
            u2_s_gvifsnd_gvif3tx_hdcp_step = (U2)MCU_STEP_GVIF3TX_HDCP_08;
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_08:
        u1_t_rg_read = st_sp_CXD4957_GVIFSNDR_HDCPTX_STATUS_RD[1].u1p_pdu[1];
        if((u1_t_rg_read & u1_s_HDCP_AUTH_MSK) == u1_s_HDCP_AUTH_MSK){
            /* エラー回数のクリア */
            u1_s_gvifsnd_hdcp_authwait_err_cnt   = (U1)0U;
            /* 次状態に遷移 */
            u2_s_gvifsnd_gvif3tx_hdcp_step     = (U2)MCU_STEP_GVIF3TX_HDCP_09;
        }
        else{
            /* エラー回数の加算 */
            u1_s_gvifsnd_hdcp_authwait_err_cnt++;
            /* エラー回数により処理の分岐 */
            if(u1_s_gvifsnd_hdcp_authwait_err_cnt < u1_s_HDCP_ERR_NUM){
                /* エラー回数：1～3回：C点(HDCP認証コマンド発行)へ遷移 */
                u2_s_gvifsnd_gvif3tx_hdcp_step = (U2)MCU_STEP_GVIF3TX_HDCP_06;
            }
            else{
                /* エラー回数のクリア */
                u1_s_gvifsnd_hdcp_authwait_err_cnt   = (U1)0U;
                /* エラー回数：4回：D点(HDCP認証エラー処理)へ遷移 */
                u2_s_gvifsnd_gvif3tx_hdcp_step = (U2)MCU_STEP_GVIF3TX_HDCP_24;
            }
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_09:
        /* HDCP認証待ちタイマースタート */
        u4_g_gvifsnd_hdcp_wait_frt_stamp[GPT_FRT_USELPSD_BASE] = u4_g_Gpt_FrtGetUsElapsed(vdp_PTR_NA);
        u2_s_gvifsnd_gvif3tx_hdcp_step = (U2)MCU_STEP_GVIF3TX_HDCP_10;
        break;

    case MCU_STEP_GVIF3TX_HDCP_10:
        /* レジスタ読出し処理 */
        u1_t_sts =  u1_PICT_CXD_I2C_CTRL_REGREAD_WAIT(&u2_s_gvifsnd_regstep, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                      st_sp_CXD4957_GVIFSNDR_HDCPTX_EVENT_RD, &u2_s_gvifsnd_reg_btwn_time, (U1)MCU_I2C_WAIT_B89);

        if(u1_t_sts == (U1)TRUE) {
            /* 次状態に遷移 */
            u2_s_gvifsnd_gvif3tx_hdcp_step = (U2)MCU_STEP_GVIF3TX_HDCP_11;
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_11:
        u1_t_rg_read    = st_sp_CXD4957_GVIFSNDR_HDCPTX_EVENT_RD[1].u1p_pdu[1];
        u4_t_frt_hdcp   = u4_g_Gpt_FrtGetUsElapsed(u4_g_gvifsnd_hdcp_wait_frt_stamp);

        /* HDCP認証待ちタイマー300ms経過？またはHDCPTXイベントモニタエラーあり（bit[7]=1）？ */
        if((u4_t_frt_hdcp > (U4)MCU_HDCP_TIMEOUT) || ((u1_t_rg_read & u1_s_HDCPTX_EVENT_ERR_MSK) == u1_s_HDCPTX_EVENT_ERR_MSK)){
            /* HDCP認証待ちタイマーリセット */
            for(u4_t_loopcont = 0; u4_t_loopcont < (U4)GPT_FRT_USELPSD_NUM_PARAM; u4_t_loopcont++){
                u4_g_gvifsnd_hdcp_wait_frt_stamp[u4_t_loopcont] = 0;
            }
            /* H点(HDCP認証待ち300msタイマー経過処理)へ遷移 */
            u2_s_gvifsnd_gvif3tx_hdcp_step   = (U2)MCU_STEP_GVIF3TX_HDCP_28;
        }
        /* 認証完了＆リボケーションチェック準備完了(bit[7:0]=0x03）？ */
        else if((u1_t_rg_read & u1_s_HDCPTX_EVENT_RDY_MSK) == u1_s_HDCPTX_EVENT_RDY_MSK){
            /* HDCP認証待ちタイマーリセット */
            for(u4_t_loopcont = 0; u4_t_loopcont < (U4)GPT_FRT_USELPSD_NUM_PARAM; u4_t_loopcont++){
                u4_g_gvifsnd_hdcp_wait_frt_stamp[u4_t_loopcont] = 0;
            }
            /* 次状態に遷移 */
            u2_s_gvifsnd_gvif3tx_hdcp_step   = (U2)MCU_STEP_GVIF3TX_HDCP_12;
        }
        else{
            /* E点(HDCPTXイベントモニタRead)に遷移 */
            u2_s_gvifsnd_gvif3tx_hdcp_step   = (U2)MCU_STEP_GVIF3TX_HDCP_10;
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_12:
        /* レジスタ書込み処理 */
        u1_t_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)MCU_WRINUM_GVIF3TX_HDCP_3,
                                               GVIFTX_HDCP_3, &u4_s_gvifsnd_i2c_ack_wait_time,
                                               st_sp_CXD4957_GVIFSNDR_HDCP3, &u2_s_gvifsnd_reg_btwn_time);

        if(u1_t_sts == (U1)TRUE){
            /* 全書込み完了 次状態に遷移 */
            u2_s_gvifsnd_gvif3tx_hdcp_step   = (U2)MCU_STEP_GVIF3TX_HDCP_13;
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_13:
        /* レジスタ読出し処理 */
        u1_t_sts =  u1_PICT_CXD_I2C_CTRL_REGREAD_WAIT(&u2_s_gvifsnd_regstep, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                      st_sp_CXD4957_GVIFSNDR_HDCPTX_DEVS_CASCADE_RD, &u2_s_gvifsnd_reg_btwn_time, (U1)MCU_I2C_WAIT_B89);

        if(u1_t_sts == (U1)TRUE) {
            /* デバイス数の取得 */
            u1_s_gvifsnd_hdcp_act_tbl[MCU_HDCP_MAX_DEVS_EXCEEDED]      = (U1)((st_sp_CXD4957_GVIFSNDR_HDCPTX_DEVS_CASCADE_RD[1].u1p_pdu[1] & u1_s_DEVS_EXCEEDED_MSK) >> (U1)MCU_SFT_7);
            if(u1_s_gvifsnd_hdcp_act_tbl[MCU_HDCP_MAX_DEVS_EXCEEDED] != u1_s_DEVS_EXCEEDED_ERR_MSK){
                /* HDCPTX_MAX_DEVS_EXCEEDEDが異常(01h)ではない場合、デバイス数を設定。異常の場合は0を設定 */
                u1_s_gvifsnd_hdcp_act_tbl[MCU_HDCP_HDCPTX_DEVICE_COUNT]    = (U1)(st_sp_CXD4957_GVIFSNDR_HDCPTX_DEVS_CASCADE_RD[1].u1p_pdu[1] & u1_s_DEVICE_COUNT_MSK);
            }
            /* 接続段数の取得  */
            u1_s_gvifsnd_hdcp_act_tbl[MCU_HDCP_MAX_CASCADE_EXCEEDED]   = (U1)((st_sp_CXD4957_GVIFSNDR_HDCPTX_DEVS_CASCADE_RD[1].u1p_pdu[2] & u1_s_CASCADE_EXCEEDED_MSK) >> (U1)MCU_SFT_7);
            if(u1_s_gvifsnd_hdcp_act_tbl[MCU_HDCP_MAX_CASCADE_EXCEEDED] != u1_s_CASCADE_EXCEEDED_ERR_MSK){
                /* DCPTX_MAX_CASCADE_EXCEEDEDが異常(01h)ではない場合、接続段数を設定。異常の場合は0を設定 */
                u1_s_gvifsnd_hdcp_act_tbl[MCU_HDCP_HDCPTX_DEPTH]           = (U1)(st_sp_CXD4957_GVIFSNDR_HDCPTX_DEVS_CASCADE_RD[1].u1p_pdu[2] & u1_s_DEPTH_MSK);
            }

            if(u1_s_gvifsnd_hdcp_act_tbl[MCU_HDCP_HDCPTX_DEVICE_COUNT] > (U1)0U){
                /* デバイス数 > 0：Receiver ID取得処理実施 */
                u2_s_gvifsnd_gvif3tx_hdcp_step = (U2)MCU_STEP_GVIF3TX_HDCP_14;
            }
            else{
                /* デバイス数 <= 0：Receiver ID取得処理を実施せず次処理へ遷移 */
                u2_s_gvifsnd_gvif3tx_hdcp_step = (U2)MCU_STEP_GVIF3TX_HDCP_15;
            }
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_14:
        /* レジスタ読出し処理 */
        u1_t_sts =  u1_PICT_CXD_I2C_CTRL_REGREAD_WAIT(&u2_s_gvifsnd_regstep, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                      st_sp_CXD4957_GVIFSNDR_HDCPTX_DEV_ID_RD, &u2_s_gvifsnd_reg_btwn_time, (U1)MCU_I2C_WAIT_B89);

        if(u1_t_sts == (U1)TRUE){
            /* Receiver ID格納 */
            u1_t_dev_num = (U1)(MCU_HDCP_RCVID + (u1_s_RCVID_NUM * u1_s_gvifsnd_hdcp_dev_cnt));
            vd_g_MemcpyU1(&u1_s_gvifsnd_hdcp_act_tbl[u1_t_dev_num], &st_sp_CXD4957_GVIFSNDR_HDCPTX_DEV_ID_RD[1].u1p_pdu[1], (U4)u1_s_RCVID_NUM);

            u1_s_gvifsnd_hdcp_dev_cnt++;
            if(u1_s_gvifsnd_hdcp_dev_cnt > u1_s_gvifsnd_hdcp_act_tbl[MCU_HDCP_HDCPTX_DEVICE_COUNT]){
                /* デバイス数の読み出し実施完了 次状態へ遷移 */
                u1_s_gvifsnd_hdcp_dev_cnt       = (U1)0U;
                u2_s_gvifsnd_gvif3tx_hdcp_step = (U2)MCU_STEP_GVIF3TX_HDCP_15;
            }
            else{
                /* 次読み出しアドレスの指定 */
                st_sp_CXD4957_GVIFSNDR_HDCPTX_DEV_ID_RD[0].u1p_pdu[1] += u1_s_RCVID_NUM * u1_s_gvifsnd_hdcp_dev_cnt;
            }
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_15:
        /* レジスタ書込み処理 */
        u1_t_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)MCU_WRINUM_GVIF3TX_HDCP_4,
                                               GVIFTX_HDCP_4, &u4_s_gvifsnd_i2c_ack_wait_time,
                                               st_sp_CXD4957_GVIFSNDR_HDCP4, &u2_s_gvifsnd_reg_btwn_time);

        if(u1_t_sts == (U1)TRUE){
            /* 全書込み完了 次状態に遷移 */
            u2_s_gvifsnd_gvif3tx_hdcp_step   = (U2)MCU_STEP_GVIF3TX_HDCP_16;
        }
        break;
    case MCU_STEP_GVIF3TX_HDCP_16:
        /* レジスタ書込み処理 */
        u1_t_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)MCU_WRINUM_GVIF3TX_HDCP_HPD,
                                               GVIFTX_HDCP_HPD, &u4_s_gvifsnd_i2c_ack_wait_time,
                                               st_sp_CXD4957_GVIFSNDR_HDCP_HPD, &u2_s_gvifsnd_reg_btwn_time);

        if(u1_t_sts == (U1)TRUE){
            u1_s_gvifsnd_hpd_flag = (U1)TRUE;
            /* 全書込み完了 次状態に遷移 */
            u2_s_gvifsnd_gvif3tx_hdcp_step   = (U2)MCU_STEP_GVIF3TX_HDCP_17;
        }
        break;
    case MCU_STEP_GVIF3TX_HDCP_17:
        /* レジスタ読出し処理 */
        u1_t_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)MCU_WRINUM_GVIF3TX_HDCP_BANK0,
                                               GVIFTX_HDCP_BANK0, &u4_s_gvifsnd_i2c_ack_wait_time,
                                               st_sp_CXD4957_GVIFSNDR_HDCP_BANK0, &u2_s_gvifsnd_reg_btwn_time);

        if(u1_t_sts == (U1)TRUE) {
            /* 次状態に遷移 */
            u2_s_gvifsnd_gvif3tx_hdcp_step = (U2)MCU_STEP_GVIF3TX_HDCP_18;
        }
        break;
    case MCU_STEP_GVIF3TX_HDCP_18:
        u1_t_timchk = u1_s_Pict_GvifSndrTimChk(u2_s_gvifsnd_gvif3tx_link_wait_time, u2_s_HDCP_WAITTIME_T7);
        if(u1_t_timchk == (U1)TRUE){
            /* Wati t7完了 次状態に遷移 */
            u2_s_gvifsnd_gvif3tx_hdcp_step = (U2)MCU_STEP_GVIF3TX_HDCP_19;
            u2_s_gvifsnd_gvif3tx_link_wait_time     = (U2)0U;
        }
        else{
            u2_s_gvifsnd_gvif3tx_link_wait_time++;
        }
        break;

        case MCU_STEP_GVIF3TX_HDCP_19:
        /* レジスタ読出し処理 */
        u1_t_sts =  u1_PICT_CXD_I2C_CTRL_REGREAD(&u2_s_gvifsnd_regstep, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                 st_sp_CXD4957_GVIFSNDR_HDCP_VIDEOIN_RD, &u2_s_gvifsnd_reg_btwn_time);

        if(u1_t_sts == (U1)TRUE) {
            /* 次状態に遷移 */
            u2_s_gvifsnd_gvif3tx_hdcp_step = (U2)MCU_STEP_GVIF3TX_HDCP_20;
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_20:
        u1_t_rg_read    = st_sp_CXD4957_GVIFSNDR_HDCP_VIDEOIN_RD[1].u1p_pdu[1];

        if((u1_t_rg_read & u1_s_HDCP_VIDEOIN_STS_MSK) == u1_s_HDCP_VIDEOIN_STS_MSK){
            /* 次状態に遷移 */
            u2_s_gvifsnd_gvif3tx_hdcp_step = (U2)MCU_STEP_GVIF3TX_HDCP_21;
        }
        else{
            /* Wait t7 へ遷移 */
            u2_s_gvifsnd_gvif3tx_hdcp_step = (U2)MCU_STEP_GVIF3TX_HDCP_18;
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_21:
        /* レジスタ読出し処理 */
        u1_t_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)MCU_WRINUM_GVIF3TX_HDCP_BANK4,
                                               GVIFTX_HDCP_BANK4, &u4_s_gvifsnd_i2c_ack_wait_time,
                                               st_sp_CXD4957_GVIFSNDR_HDCP_BANK4, &u2_s_gvifsnd_reg_btwn_time);

        if(u1_t_sts == (U1)TRUE) {
            /* 次状態に遷移 */
            u2_s_gvifsnd_gvif3tx_hdcp_step = (U2)MCU_STEP_GVIF3TX_HDCP_22;
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_22:
        /* レジスタ読出し処理 */
        u1_t_sts =  u1_PICT_CXD_I2C_CTRL_REGREAD(&u2_s_gvifsnd_regstep, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                 st_sp_CXD4957_GVIFSNDR_HDCPTX_ENC_RD, &u2_s_gvifsnd_reg_btwn_time);

        if(u1_t_sts == (U1)TRUE) {
            /* 次状態に遷移 */
            u2_s_gvifsnd_gvif3tx_hdcp_step = (U2)MCU_STEP_GVIF3TX_HDCP_23;
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_23:
        u1_t_rg_read    = st_sp_CXD4957_GVIFSNDR_HDCPTX_ENC_RD[1].u1p_pdu[1];

        if((u1_t_rg_read & u1_s_HDCP_ENCRYPT_STS_MSK) == u1_s_HDCP_ENCRYPT_STS_MSK){
            /* エラー回数のクリア */
            u1_s_gvifsnd_hdcp_encrypt_err_cnt    = (U1)0U;
            /* 出力映像に合わせてSiP側で映像MUTE解除 */
            /* ToDo：出力映像に合わせてSiP側で映像MUTE */
            /* HDCP認証応答 */
            u1_s_gvifsnd_hdcp_act_tbl[MCU_HDCP_RSLT]       = (U1)0x00U;    /* 00h：認証成功 */
            vd_g_XspiIviSub1Hdcp(u1_s_gvifsnd_hdcp_act_tbl);
            /* 初期化完了通知 */
            vd_g_XspiIviSub1PowerDevInitCmpApp((U1)XSPI_IVI_POWER_GVIFSEND_INI);
            /* HDCP認証開始トリガクリア */
            u1_s_gvifsnd_hdcp_auth_start_trg          = (U1)FALSE;
            /* 次状態に遷移 */
            u1_t_return = (U1)TRUE;
            u2_s_gvifsnd_gvif3tx_hdcp_step = (U2)MCU_STEP_GVIF3TX_HDCP_FIN;
        }
        else{
            /* エラー回数の加算 */
            u1_s_gvifsnd_hdcp_encrypt_err_cnt++;
            /* エラー回数により処理の分岐 */
            if(u1_s_gvifsnd_hdcp_encrypt_err_cnt < u1_s_HDCP_ENCRYPT_ERR_NUM){
                /* エラー回数：1～3回：Bank8切替後、F点へ遷移 */
                u2_s_gvifsnd_gvif3tx_hdcp_step = (U2)MCU_STEP_GVIF3TX_HDCP_24;
            }
            else{
                /* エラー回数のクリア */
                u1_s_gvifsnd_hdcp_encrypt_err_cnt    = (U1)0U;
                /* エラー回数：4回：D点(HDCP認証エラー処理)へ遷移 */
                u2_s_gvifsnd_gvif3tx_hdcp_step = (U2)MCU_STEP_GVIF3TX_HDCP_25;
            }
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_24:
        /* レジスタ書込み処理 */
        u1_t_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)MCU_WRINUM_GVIF3TX_HDCP_5,
                                               GVIFTX_HDCP_5, &u4_s_gvifsnd_i2c_ack_wait_time,
                                               st_sp_CXD4957_GVIFSNDR_HDCP5, &u2_s_gvifsnd_reg_btwn_time);

        if(u1_t_sts == (U1)TRUE){
            /* 全書込み完了 次状態に遷移 */
            u2_s_gvifsnd_gvif3tx_hdcp_step   = (U2)MCU_STEP_GVIF3TX_HDCP_15;
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_25:
        /* D点遷移回数カウンタのインクリメント */
        u1_s_gvifsnd_hdcp_pointd_err_cnt++;
        /* 出力映像に合わせてSiP側で映像MUTE */
        /* ToDo：出力映像に合わせてSiP側で映像MUTE */
        /* 次状態に遷移 */
        u2_s_gvifsnd_gvif3tx_hdcp_step   = (U2)MCU_STEP_GVIF3TX_HDCP_25;
        break;

    case MCU_STEP_GVIF3TX_HDCP_26:
        /* レジスタ書込み処理 */
        u1_t_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)MCU_WRINUM_GVIF3TX_HDCP_STOP,
                                               GVIFTX_HDCP_STOP, &u4_s_gvifsnd_i2c_ack_wait_time,
                                               st_sp_CXD4957_GVIFSNDR_HDCPSTOP, &u2_s_gvifsnd_reg_btwn_time);

        if(u1_t_sts == (U1)TRUE){
            /* 全書込み完了 次状態に遷移 */
            u2_s_gvifsnd_gvif3tx_hdcp_step   = (U2)MCU_STEP_GVIF3TX_HDCP_27;
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_27:
        /* D点への遷移回数によって処理分岐 */
        if(u1_s_gvifsnd_hdcp_pointd_err_cnt < (U1)u1_s_HDCP_POINT_D_ERR_NUM){
            /* エラー回数：1～3回：GVIF3リンク確立確認へ遷移 */
            u2_s_gvifsnd_gvif3tx_hdcp_step   = (U2)MCU_STEP_GVIF3TX_HDCP_28;
        }
        else{
            /* エラー回数：4回：ダイレコ保存後、定期監視フローに遷移 */
            if(u1_s_gvifsnd_dptns_err_drec_cnt < (U1)CXD4937_DPTNS_DREC_CNT_MAX){       /* Drec Counter < 3 */
                vd_CXD4937_DREC_REQ((U1)SYSECDRC_DREC_ID_9, u1_s_gvifsnd_dptns_err_drec_cnt, (U1)0x00U);
            }
            /* D点への遷移回数初期化 */
            u1_s_gvifsnd_hdcp_pointd_err_cnt = (U1)0U;
            /* ToDo：ダイレコ保存処理 */
            /* HDCP認証応答 */
            u1_s_gvifsnd_hdcp_act_tbl[MCU_HDCP_RSLT]       = (U1)0x01U;    /* 01h：認証失敗 */
            vd_g_XspiIviSub1Hdcp(u1_s_gvifsnd_hdcp_act_tbl);
            /* 初期化完了通知 */
            vd_g_XspiIviSub1PowerDevInitCmpApp((U1)XSPI_IVI_POWER_GVIFSEND_INI);
            /* HDCP認証開始トリガクリア */
            u1_s_gvifsnd_hdcp_auth_start_trg          = (U1)FALSE;
            /* 次状態へ遷移 */
            u1_t_return = (U1)TRUE;
            u2_s_gvifsnd_gvif3tx_hdcp_step = (U2)MCU_STEP_GVIF3TX_HDCP_FIN;
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_28:
        /* レジスタ書込み処理 */
        u1_t_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)MCU_WRINUM_GVIF3TX_HDCP_6,
                                               GVIFTX_HDCP_6, &u4_s_gvifsnd_i2c_ack_wait_time,
                                               st_sp_CXD4957_GVIFSNDR_HDCP6, &u2_s_gvifsnd_reg_btwn_time);

        if(u1_t_sts == (U1)TRUE){
            /* 全書込み完了 次状態に遷移 */
            u2_s_gvifsnd_gvif3tx_hdcp_step   = (U2)MCU_STEP_GVIF3TX_HDCP_03;
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_29:
        /* レジスタ書込み処理 */
        u1_t_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)MCU_WRINUM_GVIF3TX_HDCP_7,
                                               GVIFTX_HDCP_7, &u4_s_gvifsnd_i2c_ack_wait_time,
                                               st_sp_CXD4957_GVIFSNDR_HDCP7, &u2_s_gvifsnd_reg_btwn_time);

        if(u1_t_sts == (U1)TRUE){
            /* 全書込み完了 次状態に遷移 */
            u2_s_gvifsnd_gvif3tx_hdcp_step   = (U2)MCU_STEP_GVIF3TX_HDCP_30;
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_30:
        /* レジスタ書込み処理 */
        u1_t_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)MCU_WRINUM_GVIF3TX_HDCP_HPD,
                                               GVIFTX_HDCP_HPD, &u4_s_gvifsnd_i2c_ack_wait_time,
                                               st_sp_CXD4957_GVIFSNDR_HDCP_HPD, &u2_s_gvifsnd_reg_btwn_time);

        if(u1_t_sts == (U1)TRUE){
            /* 全書込み完了 次状態に遷移 */
            u2_s_gvifsnd_gvif3tx_hdcp_step   = (U2)MCU_STEP_GVIF3TX_HDCP_31;
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_31:
        /* レジスタ書込み処理 */
        u1_t_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)MCU_WRINUM_GVIF3TX_HDCP_8,
                                               GVIFTX_HDCP_8, &u4_s_gvifsnd_i2c_ack_wait_time,
                                               st_sp_CXD4957_GVIFSNDR_HDCP8, &u2_s_gvifsnd_reg_btwn_time);

        if(u1_t_sts == (U1)TRUE){
            /* 全書込み完了 次状態に遷移 */
            u2_s_gvifsnd_gvif3tx_hdcp_step   = (U2)MCU_STEP_GVIF3TX_HDCP_32;
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_32:
        /* レジスタ読出し処理 */
        u1_t_sts =  u1_PICT_CXD_I2C_CTRL_REGREAD_WAIT(&u2_s_gvifsnd_regstep, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                      st_sp_CXD4957_GVIFSNDR_HDCPTX_EVENT_RD, &u2_s_gvifsnd_reg_btwn_time, (U1)MCU_I2C_WAIT_B89);

        if(u1_t_sts == (U1)TRUE) {
            /* 次状態に遷移 */
            u2_s_gvifsnd_gvif3tx_hdcp_step = (U2)MCU_STEP_GVIF3TX_HDCP_33;
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_33:
        u1_t_rg_read    = st_sp_CXD4957_GVIFSNDR_HDCPTX_EVENT_RD[1].u1p_pdu[1];

        if((u1_t_rg_read & u1_s_HDCPTX_EVENT_ERR_MSK) == u1_s_HDCPTX_EVENT_ERR_MSK){
            /* D点(HDCP認証エラー処理)へ遷移 */
            u2_s_gvifsnd_gvif3tx_hdcp_step = (U2)MCU_STEP_GVIF3TX_HDCP_25;
        }
        else if((u1_t_rg_read & u1_s_HDCPTX_EVENT_RDY_MSK) == u1_s_HDCPTX_EVENT_RDY_MSK){
            /* K点(認証完了後の処理)へ遷移 */
            u2_s_gvifsnd_gvif3tx_hdcp_step = (U2)MCU_STEP_GVIF3TX_HDCP_12;
        }
        else{
            /* I点(HDCPTXイベントモニタRead)に遷移 */
            u2_s_gvifsnd_gvif3tx_hdcp_step = (U2)MCU_STEP_GVIF3TX_HDCP_32;
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_FIN:
        u1_t_return = (U1)TRUE;
        break;

    default:
        /* 異常ステータスの場合は最初からやり直す */
        u2_s_gvifsnd_gvif3tx_hdcp_step = (U2)MCU_STEP_GVIF3TX_HDCP_01;
        break;
    }

    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  void            vd_g_GvifTx_HADC_Act_Hook( void )                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    HDCP認証開始トリガ                                                                                                */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_GvifTx_HADC_Act_Hook( void )
{
    u1_s_gvifsnd_hdcp_auth_start_trg = (U1)TRUE;
}

/*===================================================================================================================================*/
/*  void            vd_g_GvifTx_HADC_Act_Hook( void )                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    eDP用レジスタ設定                                                                                                 */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1 u1_g_Pict_GvifSndrHdpSet( void )
{
    return(u1_s_gvifsnd_hpd_flag);
}
