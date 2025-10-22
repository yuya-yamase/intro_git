/* メインタスクコードに移管するまでの仮置き */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "gvif3tx.h"
#include "gpt_drv_frt.h"
#include "Dio.h"
#include "Dio_Symbols.h"
#include "Mcu_I2c_Ctrl_private.h"
#include "Mcu_Sys_Pwr_GvifSndr.h"

#include "pictic.h"
#include "x_spi_ivi_sub1_power.h"
#include "x_spi_ivi_sub1_hdmi.h"
#include "memcpy_u1.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Port */
#define MCU_PORT_GVIF_CDISP_RST         (DIO_ID_PORT17_CH4)     /* /GVIF-TX(C-DISP)-RST */
/* FRT */
#define MCU_FRT_1MS                     (1000 * GPT_FRT_1US)

/* カウンタ最大値 */
#define MCU_SYS_COUNTTIME_FIN           (0xFFFFFFFFU)

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
#define MCU_STEP_GVIF3TX_HDCP_17        (17U)   /* 100-4-5.(C-Disp) HDCP認証フロー[4/7] Wait t7 */
#define MCU_STEP_GVIF3TX_HDCP_18        (18U)   /* 100-4-5.(C-Disp) HDCP認証フロー[5/7] HDCPモニタ1 Read */
#define MCU_STEP_GVIF3TX_HDCP_19        (19U)   /* 100-4-5.(C-Disp) HDCP認証フロー[5/7] HDCP暗号化状態確認判定～初期化終了orエラー回数により分岐 */
#define MCU_STEP_GVIF3TX_HDCP_20        (20U)   /* 100-4-5.(C-Disp) HDCP認証フロー[5/7] Bank切り替え（Bank8）～F点へ遷移 */
#define MCU_STEP_GVIF3TX_HDCP_21        (21U)   /* 100-4-5.(C-Disp) HDCP認証フロー[6/7] D点～出力映像に合わせてSiP側で映像MUTE */
#define MCU_STEP_GVIF3TX_HDCP_22        (22U)   /* 100-4-5.(C-Disp) HDCP認証フロー[6/7] 100-4-6.HDCP認証停止フロー */
#define MCU_STEP_GVIF3TX_HDCP_23        (23U)   /* 100-4-5.(C-Disp) HDCP認証フロー[6/7] エラー回数により処理の分岐 */
#define MCU_STEP_GVIF3TX_HDCP_24        (24U)   /* 100-4-5.(C-Disp) HDCP認証フロー[6/7] Bank切り替え（Bank0） */
#define MCU_STEP_GVIF3TX_HDCP_25        (25U)   /* 100-4-5.(C-Disp) HDCP認証フロー[7/7] H点～Bank切り替え（Bank4） */
#define MCU_STEP_GVIF3TX_HDCP_26        (26U)   /* 100-4-5.(C-Disp) HDCP認証フロー[7/7] eDP用レジスタ設定 100-5-5.Hot Plug Detect */
#define MCU_STEP_GVIF3TX_HDCP_27        (27U)   /* 100-4-5.(C-Disp) HDCP認証フロー[7/7] Bank切り替え（Bank8） */
#define MCU_STEP_GVIF3TX_HDCP_28        (28U)   /* 100-4-5.(C-Disp) HDCP認証フロー[7/7] I点～HDCPTXイベントモニタRead */
#define MCU_STEP_GVIF3TX_HDCP_29        (29U)   /* 100-4-5.(C-Disp) HDCP認証フロー[7/7] HDCPTXイベントモニタ判定～次状態へ遷移 */
#define MCU_STEP_GVIF3TX_HDCP_FIN       (30U)

#define MCU_WRINUM_GVIF3TX_HDCP_1       (8U)    /* 100-4-5.(C-Disp) HDCP認証フロー[1/7] Bank切り替え（Bank4）～[2/7] HDCPTX Connect 1 設定 レジスタ書込み回数 */
#define MCU_WRINUM_GVIF3TX_HDCP_2       (1U)    /* 100-4-5.(C-Disp) HDCP認証フロー[2/7] C点～HDCP認証コマンド発行（HDCP_AUTH_REQコマンド発行） レジスタ書込み回数 */
#define MCU_WRINUM_GVIF3TX_HDCP_3       (1U)    /* 100-4-5.(C-Disp) HDCP認証フロー[3/7] K点～イベントクリア レジスタ書込み回数 */
#define MCU_WRINUM_GVIF3TX_HDCP_4       (4U)    /* 100-4-5.(C-Disp) HDCP認証フロー[4/7] F点～Bank切り替え（Bank4） レジスタ書込み回数 */
#define MCU_WRINUM_GVIF3TX_HDCP_HPD     (3U)    /* 100-4-5.(C-Disp) HDCP認証フロー[4/7] eDP用レジスタ設定 100-5-5.Hot Plug Detect レジスタ書込み回数 */
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

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* フリーランタイマ */
/* 起動からGVIFリンク確立までの時間計測 */
uint32          Mcu_frt_stamp_gvif3tx[GPT_FRT_USELPSD_NUM_PARAM];
/* HDCP認証待ちタイマ */
U4              u4_gp_Frt_HDCP[GPT_FRT_USELPSD_NUM_PARAM];

/* デバイス起動用カウンタ */
static uint32   Mcu_Polling_GvifTxRst;

/* GVIF送信制御仕様 */
       uint8    Mcu_OnStep_GVIF3TX_OVRALL;      /* 100-4-1.(C-Disp) 全体フロー 仮置き中はexternするためstaticなし */
static uint8    Mcu_OnStep_GVIF3TX_eDPSET;      /* 100-4-3.eDP設定フロー */
static uint8    Mcu_OnStep_GVIF3TX_OUTSET;      /* 100-4-4.出力設定フロー */
static U2       Mcu_OnStep_GVIF3TX_HDCP;        /* 100-4-5.HDCP認証フロー */
static uint32   Mcu_OnStep_GVIF3TX_AckTime;     /* GVIF3TX 書込み/読込みから応答までの時間計測 */
static U4       u4_g_Gvif_LinkTimer;            /* GVIF3TX Wati処理用タイマ */

static uint16   Mcu_RegStep_GVIF3TX;            /* GVIF3TX レジスタ書込み位置指定 */

/* レジスタアクセス */
static uint16   Mcu_RegSet_BetWaitTime;         /* レジスタアクセス間Waitタイマ */

/* HDCP認証開始トリガ */
static U1       u1_g_HDCP_Act_Hook;
/* 100-4-5.(C-Disp) HDCP認証フロー HDCP認証待機状態エラー回数カウンタ */
static U1       u1_g_HDCP_ErrCnt_AuthWait;
/* 100-4-5.(C-Disp) HDCP認証フロー 非暗号化エラー回数カウンタ */
static U1       u1_g_HDCP_ErrCnt_Encrypt;
/* 100-4-5.(C-Disp) HDCP認証フロー D点処理分岐用エラー回数 */
static U1       u1_g_HDCP_ErrCnt_PointD;

/* Misc Type 39h：HDMI 05h：C-Disp_HDCP認証応答 */
static U1       u1_gp_HDCP_Act[MCU_MISC_HDCP_ACT];

/* 100-4-5.(C-Disp) HDCP認証フロー ループ用デバイスカウンタ */
static U1       u1_g_HDCP_Dev_Cnt;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void     Mcu_Dev_Pwron_GvifTx_Polling_Rst( void );
static uint8    Mcu_Dev_Pwron_TimChk( uint32 mcu_tim_cnt, const uint32 mcu_tim_fim);
static void     Mcu_Dev_Pwron_GvifTx_OverAll_Flow( void );

static uint8    Mcu_Dev_Pwron_GvifTx_IniSet( void );
static uint8    Mcu_Dev_Pwron_GvifTx_eDPSet( void );
static uint8    Mcu_Dev_Pwron_GvifTx_OutSet( void );
static U1       u1_s_GvifTx_Pwrno_HDCP( void );

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*****************************************************************************
  Function      : gvif3tx_Init
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void    gvif3tx_Init( void )
{
    U4  u4_t_cnt;

    /* フリーランタイマ用配列初期化 */
    for(u4_t_cnt = 0; u4_t_cnt < (U4)GPT_FRT_USELPSD_NUM_PARAM; u4_t_cnt++){
        Mcu_frt_stamp_gvif3tx[u4_t_cnt] = 0;
        u4_gp_Frt_HDCP[u4_t_cnt] = 0;
    }

    /* Init時のフリーランタイマ取得 */
    Mcu_frt_stamp_gvif3tx[GPT_FRT_USELPSD_BASE] = u4_g_Gpt_FrtGetUsElapsed(vdp_PTR_NA);

    Mcu_Polling_GvifTxRst       = (uint32)0U;

    Mcu_OnStep_GVIF3TX_OVRALL   = (uint8)MCU_STEP_GVIF3TX_OVERALL_1;
    Mcu_OnStep_GVIF3TX_eDPSET   = (uint8)MCU_STEP_GVIF3TX_eDPSET_1;
    Mcu_OnStep_GVIF3TX_OUTSET   = (uint8)MCU_STEP_GVIF3TX_OUTSET_1;
    Mcu_OnStep_GVIF3TX_HDCP     = (U2)MCU_STEP_GVIF3TX_HDCP_01;
    u4_g_Gvif_LinkTimer         = (U4)0U;
    Mcu_OnStep_GVIF3TX_AckTime  = (uint32)0U;
    Mcu_RegStep_GVIF3TX         = (uint16)0U;

    Mcu_RegSet_BetWaitTime      = (uint16)0xFFFFU;

    u1_g_HDCP_Act_Hook          = (U1)FALSE;
    u1_g_HDCP_ErrCnt_AuthWait   = (U1)0U;
    u1_g_HDCP_ErrCnt_Encrypt    = (U1)0U;
    u1_g_HDCP_ErrCnt_PointD     = (U1)0U;

    /* Misc Type 39h：HDMI 05h：C-Disp_HDCP認証応答配列初期化 */
    u1_gp_HDCP_Act[MCU_HDCP_SUBTYPE]    = (U1)0x05U;    /* 05h：C-Disp_HDCP認証応答 */
    u1_gp_HDCP_Act[MCU_HDCP_RSLT]       = (U1)0x01U;    /* 01h：認証失敗 */
    for(u4_t_cnt = (U4)MCU_HDCP_MAX_DEVS_EXCEEDED; u4_t_cnt < (U4)MCU_MISC_HDCP_ACT; u4_t_cnt++){
        u1_gp_HDCP_Act[u4_t_cnt] = (U1)0U;
    }

    u1_g_HDCP_Dev_Cnt           = (U1)0U;

    Mcu_Sys_Pwr_GvifSndr_Init();
}

/*****************************************************************************
  Function      : gvif3tx_main
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void    gvif3tx_main( void )
{
    /* [(C-Disp)制御フロー]シートの「定期監視フロー」前まで */
    static const uint32  MCU_PWRON_TIME_GVIFTX  =   (uint16)(55U / MCU_GVIFTX_TASK_TIME);    /* min:55ms 11タスク経過後を設定 */

    uint8   mcu_time_chk;

    /* Wait t3 監視処理 */
    Mcu_Dev_Pwron_GvifTx_Polling_Rst();

    mcu_time_chk    =   Mcu_Dev_Pwron_TimChk(Mcu_Polling_GvifTxRst, MCU_PWRON_TIME_GVIFTX);

    if(mcu_time_chk ==  (uint8)TRUE){
        Mcu_Dev_Pwron_GvifTx_OverAll_Flow();
    }
}

/*===================================================================================================================================*/
/* void            vd_g_Gvif3txSeqCtl(const U1 u1_a_MODE)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_Gvif3txSeqCtl(const U1 u1_a_MODE)
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
        Mcu_OnStep_GVIF3TX_eDPSET   = (U1)MCU_STEP_GVIF3TX_eDPSET_1;
        /* fall through */
    case (U1)MCU_STEP_GVIF3TX_OVERALL_3:
        /* 出力設定用初期化処理 */
        Mcu_OnStep_GVIF3TX_OUTSET   = (U1)MCU_STEP_GVIF3TX_OUTSET_1;
        /* fall through */
    case (U1)MCU_STEP_GVIF3TX_OVERALL_4:
        /* HDCP認証用初期化処理 */
        Mcu_OnStep_GVIF3TX_HDCP     = (U2)MCU_STEP_GVIF3TX_HDCP_01;
        u1_g_HDCP_Act_Hook          = (U1)FALSE;
        u1_g_HDCP_ErrCnt_AuthWait   = (U1)0U;
        u1_g_HDCP_ErrCnt_Encrypt    = (U1)0U;
        u1_g_HDCP_ErrCnt_PointD     = (U1)0U;
        u1_g_HDCP_Dev_Cnt           = (U1)0U;

        /* Misc Type 39h：HDMI 05h：C-Disp_HDCP認証応答配列初期化 */
        u1_gp_HDCP_Act[MCU_HDCP_SUBTYPE]    = (U1)0x05U;    /* 05h：C-Disp_HDCP認証応答 */
        u1_gp_HDCP_Act[MCU_HDCP_RSLT]       = (U1)0x01U;    /* 01h：認証失敗 */
        for(u4_t_cnt = (U4)MCU_HDCP_MAX_DEVS_EXCEEDED; u4_t_cnt < (U4)MCU_MISC_HDCP_ACT; u4_t_cnt++){
            u1_gp_HDCP_Act[u4_t_cnt] = (U1)0U;
        }

        /* 全モード共通処理 */
        Mcu_OnStep_GVIF3TX_OVRALL   = u1_a_MODE;
        u4_g_Gvif_LinkTimer         = (U4)0U;
        Mcu_OnStep_GVIF3TX_AckTime  = (U4)0U;
        Mcu_RegStep_GVIF3TX         = (U2)0U;
        Mcu_RegSet_BetWaitTime      = (U2)0xFFFFU;
        Mcu_Sys_Pwr_GvifSndr_Init();
        break;
    default:
        /* do nothing */
        break;
    }
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_GvifTx_Polling_Rst
  Description   : 
  param[in/out] : 
  return        : -
  Note          : /GVIF-TX(C-DISP)-RST=Hi 監視
*****************************************************************************/
static void    Mcu_Dev_Pwron_GvifTx_Polling_Rst( void )
{
    uint8   mcu_dio_ret;
    U4      u4_t_cnt;

    mcu_dio_ret =   Dio_ReadChannel(MCU_PORT_GVIF_CDISP_RST);

    if(mcu_dio_ret  ==  (uint8)STD_LOW){
        Mcu_Polling_GvifTxRst       = (uint32)0U;
        Mcu_OnStep_GVIF3TX_OVRALL   = (uint8)MCU_STEP_GVIF3TX_OVERALL_1;
        Mcu_OnStep_GVIF3TX_eDPSET   = (uint8)MCU_STEP_GVIF3TX_eDPSET_1;
        Mcu_OnStep_GVIF3TX_OUTSET   = (uint8)MCU_STEP_GVIF3TX_OUTSET_1;
        Mcu_OnStep_GVIF3TX_HDCP     = (U2)MCU_STEP_GVIF3TX_HDCP_01;
        u4_g_Gvif_LinkTimer         = (U4)0U;
        Mcu_OnStep_GVIF3TX_AckTime  = (uint32)0U;
        Mcu_RegStep_GVIF3TX         = (uint16)0U;
        Mcu_RegSet_BetWaitTime      = (uint16)0xFFFFU;
        u1_g_HDCP_Act_Hook          = (U1)FALSE;
        u1_g_HDCP_ErrCnt_AuthWait   = (U1)0U;
        u1_g_HDCP_ErrCnt_Encrypt    = (U1)0U;
        u1_g_HDCP_ErrCnt_PointD     = (U1)0U;
        u1_g_HDCP_Dev_Cnt           = (U1)0U;

        /* Misc Type 39h：HDMI 05h：C-Disp_HDCP認証応答配列初期化 */
        u1_gp_HDCP_Act[MCU_HDCP_SUBTYPE]    = (U1)0x05U;    /* 05h：C-Disp_HDCP認証応答 */
        u1_gp_HDCP_Act[MCU_HDCP_RSLT]       = (U1)0x01U;    /* 01h：認証失敗 */
        for(u4_t_cnt = (U4)MCU_HDCP_MAX_DEVS_EXCEEDED; u4_t_cnt < (U4)MCU_MISC_HDCP_ACT; u4_t_cnt++){
            u1_gp_HDCP_Act[u4_t_cnt] = (U1)0U;
        }

        Mcu_Sys_Pwr_GvifSndr_Init();
    }
    else if((mcu_dio_ret  ==  (uint8)STD_HIGH) &&
        (Mcu_Polling_GvifTxRst < (uint32)MCU_SYS_COUNTTIME_FIN)){
        Mcu_Polling_GvifTxRst++;
    }
    else{
        /* do nothing */
    }
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_TimChk
  Description   : 
  param[in/out] : 
  return        : -
  Note          : 
*****************************************************************************/
static uint8   Mcu_Dev_Pwron_TimChk( uint32 mcu_tim_cnt, const uint32 mcu_tim_fim)
{
    uint8   mcu_ret;
    mcu_ret =   (uint8)FALSE;

    if(mcu_tim_cnt >= mcu_tim_fim){
        mcu_ret =   (uint8)TRUE;
    }

    return(mcu_ret);
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_GvifTx_OverAll_Flow
  Description   : 
  param[in/out] : 
  return        : -
  Note          : GVIF送信機 100-4-1.(C-Disp) 全体フロー
*****************************************************************************/
static void    Mcu_Dev_Pwron_GvifTx_OverAll_Flow( void )
{
    uint8   mcu_rslt;

    /* Ackタイムアウト用カウンタインクリメント */
    if(Mcu_OnStep_GVIF3TX_AckTime < (uint32)MCU_SYS_COUNTTIME_FIN){
        Mcu_OnStep_GVIF3TX_AckTime++;
    }

    switch (Mcu_OnStep_GVIF3TX_OVRALL)
    {
    case MCU_STEP_GVIF3TX_OVERALL_1:
        /* 100-4-2.初期設定フロー */
        mcu_rslt = Mcu_Dev_Pwron_GvifTx_IniSet();

        if(mcu_rslt == (uint8)TRUE){
            Mcu_OnStep_GVIF3TX_OVRALL = MCU_STEP_GVIF3TX_OVERALL_2;
        }
        break;

    case MCU_STEP_GVIF3TX_OVERALL_2:
        /* 100-4-3.eDP設定フロー */
        mcu_rslt = Mcu_Dev_Pwron_GvifTx_eDPSet();

        if(mcu_rslt == (uint8)TRUE){
            Mcu_OnStep_GVIF3TX_OVRALL = MCU_STEP_GVIF3TX_OVERALL_3;
        }
        break;

    case MCU_STEP_GVIF3TX_OVERALL_3:
        /* 映像IC制御仕様の"別体センターディスプレイへの映像出力ON"完了まで待機 */
        if(Mcu_OnStep_EIZOIC_OVRALL == MCU_STEP_EIZOIC_OVERALL_FIN){
            /* 100-4-4.出力設定フロー */
            mcu_rslt = Mcu_Dev_Pwron_GvifTx_OutSet();

            if(mcu_rslt == (uint8)TRUE){
                Mcu_OnStep_GVIF3TX_OVRALL = MCU_STEP_GVIF3TX_OVERALL_FIN;
                vd_g_XspiIviSub1PowerDevInitCmpApp((U1)XSPI_IVI_POWER_GVIFSEND_INI);
            }
        }
        break;

    case MCU_STEP_GVIF3TX_OVERALL_4:
        /* 100-4-5.HDCP認証フロー */
        mcu_rslt = u1_s_GvifTx_Pwrno_HDCP();

        if(mcu_rslt == (uint8)TRUE){
            Mcu_OnStep_GVIF3TX_OVRALL = MCU_STEP_GVIF3TX_OVERALL_FIN;
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
  Function      : Mcu_Dev_Pwron_GvifTx_IniSet
  Description   : 
  param[in/out] : 
  return        : -
  Note          : GVIF送信機 100-4-2.初期設定フロー
*****************************************************************************/
static uint8   Mcu_Dev_Pwron_GvifTx_IniSet( void )
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
    uint8   mcu_return;     /* 戻り値：フロー完了通知 */

    mcu_return      = (uint8)FALSE;

    /* レジスタ書込み処理 */
    mcu_return = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_GVIF_TX, &Mcu_RegStep_GVIF3TX, (uint16)MCU_WRINUM_GVIF3TX_INISET, 
                                            (uint8)GP_I2C_MA_SLA_3_GVIF_TX, GVIFTX_INISET, &Mcu_OnStep_GVIF3TX_AckTime,
                                            st_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT, &Mcu_RegSet_BetWaitTime);

    return(mcu_return);
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_GvifTx_eDPSet
  Description   : 
  param[in/out] : 
  return        : -
  Note          : GVIF送信機 100-4-3.eDP設定フロー
*****************************************************************************/
static uint8   Mcu_Dev_Pwron_GvifTx_eDPSet( void )
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

    uint8   mcu_sts;        /* 書込み状況 */
    uint8   mcu_return;     /* 戻り値：フロー完了通知 */

    mcu_sts         = (uint8)FALSE;
    mcu_return      = (uint8)FALSE;

    switch (Mcu_OnStep_GVIF3TX_eDPSET)
    {
    case MCU_STEP_GVIF3TX_eDPSET_1:
        /* レジスタ書込み処理 */
        mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_GVIF_TX, &Mcu_RegStep_GVIF3TX, (uint16)MCU_WRINUM_GVIF3TX_eDPSET_1,
                                                (uint8)GP_I2C_MA_SLA_3_GVIF_TX, GVIFTX_eDFSET_1, &Mcu_OnStep_GVIF3TX_AckTime,
                                                st_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET1, &Mcu_RegSet_BetWaitTime);

        if(mcu_sts == (uint8)TRUE){
            /* 全書込み完了 次状態に遷移 */
            Mcu_OnStep_GVIF3TX_eDPSET = (uint8)MCU_STEP_GVIF3TX_eDPSET_2;
        }
        break;

    case MCU_STEP_GVIF3TX_eDPSET_2:
        /* レジスタ書込み処理 */
        mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_GVIF_TX, &Mcu_RegStep_GVIF3TX, (uint16)MCU_WRINUM_GVIF3TX_eDPSET_2,
                                                (uint8)GP_I2C_MA_SLA_3_GVIF_TX, GVIFTX_eDFSET_2, &Mcu_OnStep_GVIF3TX_AckTime,
                                                st_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC, &Mcu_RegSet_BetWaitTime);

        if(mcu_sts == (uint8)TRUE){
            /* 全書込み完了 次状態に遷移 */
            Mcu_OnStep_GVIF3TX_eDPSET = (uint8)MCU_STEP_GVIF3TX_eDPSET_3;
        }
        break;

    case MCU_STEP_GVIF3TX_eDPSET_3:
        /* レジスタ書込み処理 */
        mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_GVIF_TX, &Mcu_RegStep_GVIF3TX, (uint16)MCU_WRINUM_GVIF3TX_eDPSET_3,
                                                (uint8)GP_I2C_MA_SLA_3_GVIF_TX, GVIFTX_eDFSET_3, &Mcu_OnStep_GVIF3TX_AckTime,
                                                st_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD, &Mcu_RegSet_BetWaitTime);

        if(mcu_sts == (uint8)TRUE){
            /* 全書込み完了 次状態に遷移 */
            Mcu_OnStep_GVIF3TX_eDPSET = (uint8)MCU_STEP_GVIF3TX_eDPSET_4;
        }
        break;

    case MCU_STEP_GVIF3TX_eDPSET_4:
        /* レジスタ書込み処理 */
        mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_GVIF_TX, &Mcu_RegStep_GVIF3TX, (uint16)MCU_WRINUM_GVIF3TX_eDPSET_4,
                                                (uint8)GP_I2C_MA_SLA_3_GVIF_TX, GVIFTX_eDFSET_4, &Mcu_OnStep_GVIF3TX_AckTime,
                                                st_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET2, &Mcu_RegSet_BetWaitTime);

        if(mcu_sts == (uint8)TRUE){
            /* 全書込み完了 次状態に遷移 */
            Mcu_OnStep_GVIF3TX_eDPSET = (uint8)MCU_STEP_GVIF3TX_eDPSET_5;
        }
        break;

    case MCU_STEP_GVIF3TX_eDPSET_5:
        /* レジスタ書込み処理 */
        mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_GVIF_TX, &Mcu_RegStep_GVIF3TX, (uint16)MCU_WRINUM_GVIF3TX_eDPSET_5,
                                                (uint8)GP_I2C_MA_SLA_3_GVIF_TX, GVIFTX_eDFSET_5, &Mcu_OnStep_GVIF3TX_AckTime,
                                                st_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET3, &Mcu_RegSet_BetWaitTime);

        if(mcu_sts == (uint8)TRUE){
            /* 全書込み完了 次状態に遷移 */
            Mcu_OnStep_GVIF3TX_eDPSET = (uint8)MCU_STEP_GVIF3TX_eDPSET_6;
        }
        break;
    
    case MCU_STEP_GVIF3TX_eDPSET_6:
        /* レジスタ書込み処理 */
        mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_GVIF_TX, &Mcu_RegStep_GVIF3TX, (uint16)MCU_WRINUM_GVIF3TX_eDPSET_6,
                                                (uint8)GP_I2C_MA_SLA_3_GVIF_TX, GVIFTX_eDFSET_6, &Mcu_OnStep_GVIF3TX_AckTime,
                                                st_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_HPD, &Mcu_RegSet_BetWaitTime);

        if(mcu_sts == (uint8)TRUE){
            /* 全書込み完了 次状態に遷移 */
            Mcu_OnStep_GVIF3TX_eDPSET = (uint8)MCU_STEP_GVIF3TX_eDPSET_FIN;
            mcu_return                = (uint8)TRUE;
        }
        break;

    case MCU_STEP_GVIF3TX_eDPSET_FIN:
        mcu_return  = (uint8)TRUE;
        break;

    default:
        /* 異常時：本処理を最初からやり直す */
        Mcu_OnStep_GVIF3TX_eDPSET = (uint8)MCU_STEP_GVIF3TX_eDPSET_1;
        break;
    }

    return(mcu_return);
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_GvifTx_OutSet
  Description   : 
  param[in/out] : 
  return        : -
  Note          : GVIF送信機 100-4-4.出力設定フロー
*****************************************************************************/
static uint8   Mcu_Dev_Pwron_GvifTx_OutSet( void )
{
    /* GVIF3リンク確立確認ポーリング周期 t4 */
    static const uint32  MCU_PWRON_TIME_GVIFTX_POLING  = (50U / MCU_GVIFTX_TASK_TIME);    /* typ:50ms */
    /* リンク確立完了 確認用マスク */
    static const uint8   MCU_GVIF3TX0_ACTIVATED_MSK    = (0x01U);
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

    uint8   mcu_time_chk_poling;    /* wait t4監視 */
    uint8   mcu_sts;                /* 書込み状況 */
    uint8   mcu_return;             /* 戻り値：フロー完了通知 */
    uint32  mcu_frt_elpsd;
    uint8   mcu_reg_read;           /* レジスタ読出し値 */

    mcu_sts             = (uint8)FALSE;
    mcu_return          = (uint8)FALSE;
    mcu_time_chk_poling = (uint8)0U;
    mcu_frt_elpsd       = u4_g_Gpt_FrtGetUsElapsed(Mcu_frt_stamp_gvif3tx);
    mcu_reg_read        = (uint8)0U;

    switch (Mcu_OnStep_GVIF3TX_OUTSET)
    {
    case MCU_STEP_GVIF3TX_OUTSET_1:
        /* レジスタ書込み処理 */
        mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_GVIF_TX, &Mcu_RegStep_GVIF3TX, (uint16)MCU_WRINUM_GVIF3TX_OUTSET_3,
                                                (uint8)GP_I2C_MA_SLA_3_GVIF_TX, GVIFTX_OUTSET_3, &Mcu_OnStep_GVIF3TX_AckTime,
                                                st_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET3, &Mcu_RegSet_BetWaitTime);

        if(mcu_sts == (uint8)TRUE){
            /* 全書込み完了 次状態に遷移 */
            Mcu_OnStep_GVIF3TX_OUTSET = (uint8)MCU_STEP_GVIF3TX_OUTSET_2;
        }
        break;
    
    case MCU_STEP_GVIF3TX_OUTSET_2:
        /* レジスタ書込み処理 */
        /* ToDo：I2Cの説明次第で要変更 */
        mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_GVIF_TX, &Mcu_RegStep_GVIF3TX, (uint16)MCU_WRINUM_GVIF3TX_OUTSET_1,
                                                (uint8)GP_I2C_MA_SLA_3_GVIF_TX, GVIFTX_OUTSET_1, &Mcu_OnStep_GVIF3TX_AckTime,
                                                st_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET1, &Mcu_RegSet_BetWaitTime);
        if(mcu_sts == (uint8)TRUE){
            /* 全書込み完了したら次状態に遷移 */
            Mcu_OnStep_GVIF3TX_OUTSET = (uint8)MCU_STEP_GVIF3TX_OUTSET_3;
        }
        break;

    case MCU_STEP_GVIF3TX_OUTSET_3:
        mcu_time_chk_poling = Mcu_Dev_Pwron_TimChk(u4_g_Gvif_LinkTimer, MCU_PWRON_TIME_GVIFTX_POLING);
        if(mcu_time_chk_poling == (uint8)TRUE){
            /* Wati t4完了 次状態に遷移 */
            Mcu_OnStep_GVIF3TX_OUTSET = (uint8)MCU_STEP_GVIF3TX_OUTSET_4;
            u4_g_Gvif_LinkTimer       = (uint32)0U;
        }
        else{
            u4_g_Gvif_LinkTimer++;
        }
        break;

    case MCU_STEP_GVIF3TX_OUTSET_4:
        /* レジスタ読出し処理 */
        mcu_sts = Mcu_Dev_I2c_Ctrl_RegRead((uint8)MCU_I2C_ACK_GVIF_TX, &Mcu_RegStep_GVIF3TX, (uint8)GP_I2C_MA_SLA_3_GVIF_TX,
                                                &Mcu_OnStep_GVIF3TX_AckTime, st_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET_GVIF3TX0_ACTIVATED_RD, &Mcu_RegSet_BetWaitTime, (U1)MCU_I2C_WAIT_NON);

        if(mcu_sts == (uint8)TRUE){
            /* 全書込み完了 次状態に遷移 */
            Mcu_OnStep_GVIF3TX_OUTSET = (uint8)MCU_STEP_GVIF3TX_OUTSET_5;
        }
        break;

    case MCU_STEP_GVIF3TX_OUTSET_5:
        mcu_reg_read = st_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET_GVIF3TX0_ACTIVATED_RD[1].u1p_pdu[1];
        if((mcu_reg_read & (uint8)MCU_GVIF3TX0_ACTIVATED_MSK) != (uint8)0x01U){
            /* リンク確立未完了 */
            /* ToDo：ディスプレイ電源ONをXSPI？から取得する必要がある */
            if(mcu_frt_elpsd > (uint32)MCU_GVIF_LNK_TIMEOUT){
                /* GVIF3リンクエラー処理 */
                (void)Dio_WriteChannel(MCU_PORT_GVIF_CDISP_RST , MCU_DIO_LOW);/* デバイスリセット */
                /* ToDo：DTC記録 DISP(Center)通信途絶 コード：T.B.D */
                Mcu_OnStep_GVIF3TX_OUTSET = (uint8)MCU_STEP_GVIF3TX_OUTSET_STP;
                /* 初期化完了通知 */
                vd_g_XspiIviSub1PowerDevInitCmpApp((U1)XSPI_IVI_POWER_GVIFSEND_INI);
            }
            else{
                /* A点へ戻る */
                Mcu_OnStep_GVIF3TX_OUTSET = (uint8)MCU_STEP_GVIF3TX_OUTSET_2;
            }
        }
        else{
            /* 次状態に遷移 */
            Mcu_OnStep_GVIF3TX_OUTSET = (uint8)MCU_STEP_GVIF3TX_OUTSET_6;
        }
        break;

    case MCU_STEP_GVIF3TX_OUTSET_6:
        /* レジスタ書込み処理 */
        mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_GVIF_TX, &Mcu_RegStep_GVIF3TX, (uint16)MCU_WRINUM_GVIF3TX_OUTSET_2,
                                                (uint8)GP_I2C_MA_SLA_3_GVIF_TX, GVIFTX_OUTSET_2, &Mcu_OnStep_GVIF3TX_AckTime,
                                                st_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET2, &Mcu_RegSet_BetWaitTime);

        if(mcu_sts == (uint8)TRUE){
            /* 全書込み完了 次状態に遷移 */
            Mcu_OnStep_GVIF3TX_OUTSET   = (uint8)MCU_STEP_GVIF3TX_OUTSET_FIN;
            mcu_return                  = (uint8)TRUE;
        }
        break;

    case MCU_STEP_GVIF3TX_OUTSET_STP:
        /* 次回起動まで制御停止 */
        break;
    
    case MCU_STEP_GVIF3TX_OUTSET_FIN:
        mcu_return = (uint8)TRUE;
        break;

    default:
        /* 異常ステータスの場合は最初からやり直す */
        Mcu_OnStep_GVIF3TX_OUTSET = (uint8)MCU_STEP_GVIF3TX_OUTSET_1;
        break;
    }

    return(mcu_return);
}

/*===================================================================================================================================*/
/*  static U1       u1_s_GvifTx_Pwrno_HDCP( void )                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    GVIF送信機 100-4-5.HDCP認証フロー                                                                                 */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_GvifTx_Pwrno_HDCP( void )
{
    /* GVIF3リンク確立確認ポーリング周期 t4 */
    static const U4     u4_s_HDCP_WAITTIME_T4           = (U4)(50U / MCU_GVIFTX_TASK_TIME);    /* typ:50ms */
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
    static const U4     u4_s_HDCP_WAITTIME_T7           = (U4)(40U / MCU_GVIFTX_TASK_TIME);    /* min:40ms */
    /* HDCP暗号化状態確認 確認用マスク */
    static const U1     u1_s_HDCP_ENCRYPT_STS_MSK       = (U1)(0x01U);
    /* HDCP暗号化状態確認 処理分岐発生のエラー回数 */
    static const U1     u1_s_HDCP_ENCRYPT_ERR_NUM       = (U1)(4U);
    /* D点 処理分岐発生のエラー回数 */
    static const U1     u1_s_HDCP_POINT_D_ERR_NUM       = (U1)(4U);

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

    switch (Mcu_OnStep_GVIF3TX_HDCP)
    {
    case MCU_STEP_GVIF3TX_HDCP_01:
        if(u1_g_HDCP_Act_Hook == (U1)TRUE) {
            Mcu_OnStep_GVIF3TX_HDCP = (U2)MCU_STEP_GVIF3TX_HDCP_05;
        }
        else{
            Mcu_OnStep_GVIF3TX_HDCP = (U2)MCU_STEP_GVIF3TX_HDCP_02;
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_02:
        u1_t_timchk = Mcu_Dev_Pwron_TimChk(u4_g_Gvif_LinkTimer, u4_s_HDCP_WAITTIME_T4);
        if(u1_t_timchk == (U1)TRUE){
            /* Wati t4完了 次状態に遷移 */
            Mcu_OnStep_GVIF3TX_HDCP = (U2)MCU_STEP_GVIF3TX_HDCP_03;
            u4_g_Gvif_LinkTimer     = (U4)0U;
        }
        else{
            u4_g_Gvif_LinkTimer++;
        }
        break;
    
    case MCU_STEP_GVIF3TX_HDCP_03:
        /* レジスタ読出し処理 */
        u1_t_sts =  Mcu_Dev_I2c_Ctrl_RegRead((U1)MCU_I2C_ACK_GVIF_TX, &Mcu_RegStep_GVIF3TX, (U1)GP_I2C_MA_SLA_3_GVIF_TX,
                                                &Mcu_OnStep_GVIF3TX_AckTime, st_sp_MCU_SYS_PWR_GVIFSNDR_GVIF3TX0_ACT_RD, &Mcu_RegSet_BetWaitTime, (U1)MCU_I2C_WAIT_NON);

        if(u1_t_sts == (U1)TRUE) {
            /* 次状態に遷移 */
            Mcu_OnStep_GVIF3TX_HDCP = (U2)MCU_STEP_GVIF3TX_HDCP_04;
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_04:
        u1_t_rg_read = st_sp_MCU_SYS_PWR_GVIFSNDR_GVIF3TX0_ACT_RD[1].u1p_pdu[1];
        if((u1_t_rg_read & u1_s_GVIF3TX0_ACTIVATED_MSK) == u1_s_GVIF3TX0_ACTIVATED_MSK){
            /* リンク確立完了 */
            /* B点まで戻る */
            Mcu_OnStep_GVIF3TX_HDCP = (U2)MCU_STEP_GVIF3TX_HDCP_01;
        }
        else {
            /* リンク確立未完了 */
            /* HDCPフローリセット */
            Mcu_OnStep_GVIF3TX_HDCP     = (U2)MCU_STEP_GVIF3TX_HDCP_01;
            /* A点まで戻る */
            Mcu_OnStep_GVIF3TX_OUTSET   = (U1)MCU_STEP_GVIF3TX_OUTSET_2;
            Mcu_OnStep_GVIF3TX_OVRALL   = (U1)MCU_STEP_GVIF3TX_OVERALL_3;
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_05:
        /* レジスタ書込み処理 */
        u1_t_sts = Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_GVIF_TX, &Mcu_RegStep_GVIF3TX, (U2)MCU_WRINUM_GVIF3TX_HDCP_1,
                                                (U1)GP_I2C_MA_SLA_3_GVIF_TX, GVIFTX_HDCP_1, &Mcu_OnStep_GVIF3TX_AckTime,
                                                st_sp_MCU_SYS_PWR_GVIFSNDR_HDCP1, &Mcu_RegSet_BetWaitTime);

        if(u1_t_sts == (U1)TRUE){
            /* 全書込み完了 次状態に遷移 */
            Mcu_OnStep_GVIF3TX_HDCP = (U2)MCU_STEP_GVIF3TX_HDCP_06;
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_06:
        /* レジスタ書込み処理 */
        u1_t_sts = Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_GVIF_TX, &Mcu_RegStep_GVIF3TX, (U2)MCU_WRINUM_GVIF3TX_HDCP_2,
                                                (U1)GP_I2C_MA_SLA_3_GVIF_TX, GVIFTX_HDCP_2, &Mcu_OnStep_GVIF3TX_AckTime,
                                                st_sp_MCU_SYS_PWR_GVIFSNDR_HDCP2, &Mcu_RegSet_BetWaitTime);

        if(u1_t_sts == (U1)TRUE){
            /* 全書込み完了 次状態に遷移 */
            Mcu_OnStep_GVIF3TX_HDCP = (U2)MCU_STEP_GVIF3TX_HDCP_07;
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_07:
        /* レジスタ読出し処理 */
        u1_t_sts =  Mcu_Dev_I2c_Ctrl_RegRead((U1)MCU_I2C_ACK_GVIF_TX, &Mcu_RegStep_GVIF3TX, (U1)GP_I2C_MA_SLA_3_GVIF_TX,
                                                &Mcu_OnStep_GVIF3TX_AckTime, st_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_STATUS_RD, &Mcu_RegSet_BetWaitTime, (U1)MCU_I2C_WAIT_B89);

        if(u1_t_sts == (U1)TRUE) {
            /* 次状態に遷移 */
            Mcu_OnStep_GVIF3TX_HDCP = (U2)MCU_STEP_GVIF3TX_HDCP_08;
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_08:
        u1_t_rg_read = st_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_STATUS_RD[1].u1p_pdu[1];
        if((u1_t_rg_read & u1_s_HDCP_AUTH_MSK) == u1_s_HDCP_AUTH_MSK){
            /* エラー回数のクリア */
            u1_g_HDCP_ErrCnt_AuthWait   = (U1)0U;
            /* 次状態に遷移 */
            Mcu_OnStep_GVIF3TX_HDCP     = (U2)MCU_STEP_GVIF3TX_HDCP_09;
        }
        else{
            /* エラー回数の加算 */
            u1_g_HDCP_ErrCnt_AuthWait++;
            /* エラー回数により処理の分岐 */
            if(u1_g_HDCP_ErrCnt_AuthWait < u1_s_HDCP_ERR_NUM){
                /* エラー回数：1～3回：C点(HDCP認証コマンド発行)へ遷移 */
                Mcu_OnStep_GVIF3TX_HDCP = (U2)MCU_STEP_GVIF3TX_HDCP_06;
            }
            else{
                /* エラー回数：4回：D点(HDCP認証エラー処理)へ遷移 */
                Mcu_OnStep_GVIF3TX_HDCP = (U2)MCU_STEP_GVIF3TX_HDCP_21;
            }
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_09:
        /* HDCP認証待ちタイマースタート */
        u4_gp_Frt_HDCP[GPT_FRT_USELPSD_BASE] = u4_g_Gpt_FrtGetUsElapsed(vdp_PTR_NA);
        Mcu_OnStep_GVIF3TX_HDCP = (U2)MCU_STEP_GVIF3TX_HDCP_10;
        break;

    case MCU_STEP_GVIF3TX_HDCP_10:
        /* レジスタ読出し処理 */
        u1_t_sts =  Mcu_Dev_I2c_Ctrl_RegRead((U1)MCU_I2C_ACK_GVIF_TX, &Mcu_RegStep_GVIF3TX, (U1)GP_I2C_MA_SLA_3_GVIF_TX,
                                                &Mcu_OnStep_GVIF3TX_AckTime, st_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_EVENT_RD, &Mcu_RegSet_BetWaitTime, (U1)MCU_I2C_WAIT_B89);

        if(u1_t_sts == (U1)TRUE) {
            /* 次状態に遷移 */
            Mcu_OnStep_GVIF3TX_HDCP = (U2)MCU_STEP_GVIF3TX_HDCP_11;
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_11:
        u1_t_rg_read    = st_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_EVENT_RD[1].u1p_pdu[1];
        u4_t_frt_hdcp   = u4_g_Gpt_FrtGetUsElapsed(u4_gp_Frt_HDCP);

        /* HDCP認証待ちタイマー300ms経過？またはHDCPTXイベントモニタエラーあり（bit[7]=1）？ */
        if((u4_t_frt_hdcp > (U4)MCU_HDCP_TIMEOUT) || ((u1_t_rg_read & u1_s_HDCPTX_EVENT_ERR_MSK) == u1_s_HDCPTX_EVENT_ERR_MSK)){
            /* HDCP認証待ちタイマーリセット */
            for(u4_t_loopcont = 0; u4_t_loopcont < (U4)GPT_FRT_USELPSD_NUM_PARAM; u4_t_loopcont++){
                u4_gp_Frt_HDCP[u4_t_loopcont] = 0;
            }
            /* H点(HDCP認証待ち300msタイマー経過処理)へ遷移 */
            Mcu_OnStep_GVIF3TX_HDCP   = (U2)MCU_STEP_GVIF3TX_HDCP_25;
        }
        /* 認証完了＆リボケーションチェック準備完了(bit[7:0]=0x03）？ */
        else if((u1_t_rg_read & u1_s_HDCPTX_EVENT_RDY_MSK) == u1_s_HDCPTX_EVENT_RDY_MSK){
            /* HDCP認証待ちタイマーリセット */
            for(u4_t_loopcont = 0; u4_t_loopcont < (U4)GPT_FRT_USELPSD_NUM_PARAM; u4_t_loopcont++){
                u4_gp_Frt_HDCP[u4_t_loopcont] = 0;
            }
            /* 次状態に遷移 */
            Mcu_OnStep_GVIF3TX_HDCP   = (U2)MCU_STEP_GVIF3TX_HDCP_12;
        }
        else{
            /* E点(HDCPTXイベントモニタRead)に遷移 */
            Mcu_OnStep_GVIF3TX_HDCP   = (U2)MCU_STEP_GVIF3TX_HDCP_10;
        }
        break;
    
    case MCU_STEP_GVIF3TX_HDCP_12:
        /* レジスタ書込み処理 */
        u1_t_sts = Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_GVIF_TX, &Mcu_RegStep_GVIF3TX, (U2)MCU_WRINUM_GVIF3TX_HDCP_3,
                                                (U1)GP_I2C_MA_SLA_3_GVIF_TX, GVIFTX_HDCP_3, &Mcu_OnStep_GVIF3TX_AckTime,
                                                st_sp_MCU_SYS_PWR_GVIFSNDR_HDCP3, &Mcu_RegSet_BetWaitTime);

        if(u1_t_sts == (U1)TRUE){
            /* 全書込み完了 次状態に遷移 */
            Mcu_OnStep_GVIF3TX_HDCP   = (U2)MCU_STEP_GVIF3TX_HDCP_13;
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_13:
        /* レジスタ読出し処理 */
        u1_t_sts =  Mcu_Dev_I2c_Ctrl_RegRead((U1)MCU_I2C_ACK_GVIF_TX, &Mcu_RegStep_GVIF3TX, (U1)GP_I2C_MA_SLA_3_GVIF_TX,
                                                &Mcu_OnStep_GVIF3TX_AckTime, st_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_DEVS_CASCADE_RD, &Mcu_RegSet_BetWaitTime, (U1)MCU_I2C_WAIT_B89);

        if(u1_t_sts == (U1)TRUE) {
            /* デバイス数の取得 */
            u1_gp_HDCP_Act[MCU_HDCP_MAX_DEVS_EXCEEDED]      = (U1)((st_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_DEVS_CASCADE_RD[1].u1p_pdu[1] & u1_s_DEVS_EXCEEDED_MSK) >> (U1)MCU_SFT_7);
            if(u1_gp_HDCP_Act[MCU_HDCP_MAX_DEVS_EXCEEDED] != u1_s_DEVS_EXCEEDED_ERR_MSK){
                /* HDCPTX_MAX_DEVS_EXCEEDEDが異常(01h)ではない場合、デバイス数を設定。異常の場合は0を設定 */
                u1_gp_HDCP_Act[MCU_HDCP_HDCPTX_DEVICE_COUNT]    = (U1)(st_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_DEVS_CASCADE_RD[1].u1p_pdu[1] & u1_s_DEVICE_COUNT_MSK);
            }
            /* 接続段数の取得  */
            u1_gp_HDCP_Act[MCU_HDCP_MAX_CASCADE_EXCEEDED]   = (U1)((st_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_DEVS_CASCADE_RD[1].u1p_pdu[2] & u1_s_CASCADE_EXCEEDED_MSK) >> (U1)MCU_SFT_7);
            if(u1_gp_HDCP_Act[MCU_HDCP_MAX_CASCADE_EXCEEDED] != u1_s_CASCADE_EXCEEDED_ERR_MSK){
                /* DCPTX_MAX_CASCADE_EXCEEDEDが異常(01h)ではない場合、接続段数を設定。異常の場合は0を設定 */
                u1_gp_HDCP_Act[MCU_HDCP_HDCPTX_DEPTH]           = (U1)(st_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_DEVS_CASCADE_RD[1].u1p_pdu[2] & u1_s_DEPTH_MSK);
            }
            
            if(u1_gp_HDCP_Act[MCU_HDCP_HDCPTX_DEVICE_COUNT] > (U1)0U){
                /* デバイス数 > 0：Receiver ID取得処理実施 */
                Mcu_OnStep_GVIF3TX_HDCP = (U2)MCU_STEP_GVIF3TX_HDCP_14;
            }
            else{
                /* デバイス数 <= 0：Receiver ID取得処理を実施せず次処理へ遷移 */
                Mcu_OnStep_GVIF3TX_HDCP = (U2)MCU_STEP_GVIF3TX_HDCP_15;
            }
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_14:
        /* レジスタ読出し処理 */
        u1_t_sts =  Mcu_Dev_I2c_Ctrl_RegRead((U1)MCU_I2C_ACK_GVIF_TX, &Mcu_RegStep_GVIF3TX, (U1)GP_I2C_MA_SLA_3_GVIF_TX,
                                                &Mcu_OnStep_GVIF3TX_AckTime, st_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_DEV_ID_RD, &Mcu_RegSet_BetWaitTime, (U1)MCU_I2C_WAIT_B89);

        if(u1_t_sts == (U1)TRUE){
            /* Receiver ID格納 */
            u1_t_dev_num = (U1)(MCU_HDCP_RCVID + (u1_s_RCVID_NUM * u1_g_HDCP_Dev_Cnt));
            vd_g_MemcpyU1(&u1_gp_HDCP_Act[u1_t_dev_num], &st_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_DEV_ID_RD[1].u1p_pdu[1], (U4)u1_s_RCVID_NUM);

            u1_g_HDCP_Dev_Cnt++;
            if(u1_g_HDCP_Dev_Cnt > u1_gp_HDCP_Act[MCU_HDCP_HDCPTX_DEVICE_COUNT]){
                /* デバイス数の読み出し実施完了 次状態へ遷移 */
                u1_g_HDCP_Dev_Cnt       = (U1)0U;
                Mcu_OnStep_GVIF3TX_HDCP = (U2)MCU_STEP_GVIF3TX_HDCP_15;
            }
            else{
                /* 次読み出しアドレスの指定 */
                st_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_DEV_ID_RD[0].u1p_pdu[1] += u1_s_RCVID_NUM * u1_g_HDCP_Dev_Cnt;
            }
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_15:
        /* レジスタ書込み処理 */
        u1_t_sts = Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_GVIF_TX, &Mcu_RegStep_GVIF3TX, (U2)MCU_WRINUM_GVIF3TX_HDCP_4,
                                                (U1)GP_I2C_MA_SLA_3_GVIF_TX, GVIFTX_HDCP_4, &Mcu_OnStep_GVIF3TX_AckTime,
                                                st_sp_MCU_SYS_PWR_GVIFSNDR_HDCP4, &Mcu_RegSet_BetWaitTime);

        if(u1_t_sts == (U1)TRUE){
            /* 全書込み完了 次状態に遷移 */
            Mcu_OnStep_GVIF3TX_HDCP   = (U2)MCU_STEP_GVIF3TX_HDCP_17;
        }
        break;
#if 0
    case MCU_STEP_GVIF3TX_HDCP_16:
        /* レジスタ書込み処理 */
        u1_t_sts = Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_GVIF_TX, &Mcu_RegStep_GVIF3TX, (U2)MCU_WRINUM_GVIF3TX_HDCP_HPD,
                                                (U1)GP_I2C_MA_SLA_3_GVIF_TX, GVIFTX_HDCP_HPD, &Mcu_OnStep_GVIF3TX_AckTime,
                                                st_sp_MCU_SYS_PWR_GVIFSNDR_HDCP_HPD, &Mcu_RegSet_BetWaitTime);

        if(u1_t_sts == (U1)TRUE){
            /* 全書込み完了 次状態に遷移 */
            Mcu_OnStep_GVIF3TX_HDCP   = (U2)MCU_STEP_GVIF3TX_HDCP_17;
        }
        break;
#endif
    case MCU_STEP_GVIF3TX_HDCP_17:
        u1_t_timchk = Mcu_Dev_Pwron_TimChk(u4_g_Gvif_LinkTimer, u4_s_HDCP_WAITTIME_T7);
        if(u1_t_timchk == (U1)TRUE){
            /* Wati t7完了 次状態に遷移 */
            Mcu_OnStep_GVIF3TX_HDCP = (U2)MCU_STEP_GVIF3TX_HDCP_18;
            u4_g_Gvif_LinkTimer     = (U4)0U;
        }
        else{
            u4_g_Gvif_LinkTimer++;
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_18:
        /* レジスタ読出し処理 */
        u1_t_sts =  Mcu_Dev_I2c_Ctrl_RegRead((U1)MCU_I2C_ACK_GVIF_TX, &Mcu_RegStep_GVIF3TX, (U1)GP_I2C_MA_SLA_3_GVIF_TX,
                                                &Mcu_OnStep_GVIF3TX_AckTime, st_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_ENC_RD, &Mcu_RegSet_BetWaitTime, (U1)MCU_I2C_WAIT_NON);

        if(u1_t_sts == (U1)TRUE) {
            /* 次状態に遷移 */
            Mcu_OnStep_GVIF3TX_HDCP = (U2)MCU_STEP_GVIF3TX_HDCP_19;
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_19:
        u1_t_rg_read    = st_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_ENC_RD[1].u1p_pdu[1];

        if((u1_t_rg_read & u1_s_HDCP_ENCRYPT_STS_MSK) == u1_s_HDCP_ENCRYPT_STS_MSK){
            /* エラー回数のクリア */
            u1_g_HDCP_ErrCnt_Encrypt    = (U1)0U;
            /* 出力映像に合わせてSiP側で映像MUTE解除 */
            /* ToDo：出力映像に合わせてSiP側で映像MUTE */
            /* HDCP認証応答 */
            u1_gp_HDCP_Act[MCU_HDCP_RSLT]       = (U1)0x00U;    /* 00h：認証成功 */
            vd_g_XspiIviSub1Hdcp(u1_gp_HDCP_Act);
            /* 初期化完了通知 */
            vd_g_XspiIviSub1PowerDevInitCmpApp((U1)XSPI_IVI_POWER_GVIFSEND_INI);
            /* 次状態に遷移 */
            u1_t_return = (U1)TRUE;
            Mcu_OnStep_GVIF3TX_HDCP = (U2)MCU_STEP_GVIF3TX_HDCP_FIN;
        }
        else{
            /* エラー回数の加算 */
            u1_g_HDCP_ErrCnt_Encrypt++;
            /* エラー回数により処理の分岐 */
            if(u1_g_HDCP_ErrCnt_Encrypt < u1_s_HDCP_ENCRYPT_ERR_NUM){
                /* エラー回数：1～3回：Bank8切替後、F点へ遷移 */
                Mcu_OnStep_GVIF3TX_HDCP = (U2)MCU_STEP_GVIF3TX_HDCP_20;
            }
            else{
                /* エラー回数：4回：D点(HDCP認証エラー処理)へ遷移 */
                Mcu_OnStep_GVIF3TX_HDCP = (U2)MCU_STEP_GVIF3TX_HDCP_21;
            }
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_20:
        /* レジスタ書込み処理 */
        u1_t_sts = Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_GVIF_TX, &Mcu_RegStep_GVIF3TX, (U2)MCU_WRINUM_GVIF3TX_HDCP_5,
                                                (U1)GP_I2C_MA_SLA_3_GVIF_TX, GVIFTX_HDCP_5, &Mcu_OnStep_GVIF3TX_AckTime,
                                                st_sp_MCU_SYS_PWR_GVIFSNDR_HDCP5, &Mcu_RegSet_BetWaitTime);

        if(u1_t_sts == (U1)TRUE){
            /* 全書込み完了 次状態に遷移 */
            Mcu_OnStep_GVIF3TX_HDCP   = (U2)MCU_STEP_GVIF3TX_HDCP_15;
        }
        break;
        
    case MCU_STEP_GVIF3TX_HDCP_21:
        /* D点遷移回数カウンタのインクリメント */
        u1_g_HDCP_ErrCnt_PointD++;
        /* 出力映像に合わせてSiP側で映像MUTE */
        /* ToDo：出力映像に合わせてSiP側で映像MUTE */
        /* 次状態に遷移 */
        Mcu_OnStep_GVIF3TX_HDCP   = (U2)MCU_STEP_GVIF3TX_HDCP_22;
        break;

    case MCU_STEP_GVIF3TX_HDCP_22:
        /* レジスタ書込み処理 */
        u1_t_sts = Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_GVIF_TX, &Mcu_RegStep_GVIF3TX, (U2)MCU_WRINUM_GVIF3TX_HDCP_STOP,
                                                (U1)GP_I2C_MA_SLA_3_GVIF_TX, GVIFTX_HDCP_STOP, &Mcu_OnStep_GVIF3TX_AckTime,
                                                st_sp_MCU_SYS_PWR_GVIFSNDR_HDCPSTOP, &Mcu_RegSet_BetWaitTime);

        if(u1_t_sts == (U1)TRUE){
            /* 全書込み完了 次状態に遷移 */
            Mcu_OnStep_GVIF3TX_HDCP   = (U2)MCU_STEP_GVIF3TX_HDCP_23;
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_23:
        /* D点への遷移回数によって処理分岐 */
        if(u1_g_HDCP_ErrCnt_PointD < (U1)u1_s_HDCP_POINT_D_ERR_NUM){
            /* エラー回数：1～3回：GVIF3リンク確立確認へ遷移 */
            Mcu_OnStep_GVIF3TX_HDCP   = (U2)MCU_STEP_GVIF3TX_HDCP_24;
        }
        else{
            /* エラー回数：4回：ダイレコ保存後、定期監視フローに遷移 */
            /* D点への遷移回数初期化 */
            u1_g_HDCP_ErrCnt_PointD = (U1)0U;
            /* ToDo：ダイレコ保存処理 */
            /* HDCP認証応答 */
            u1_gp_HDCP_Act[MCU_HDCP_RSLT]       = (U1)0x01U;    /* 01h：認証失敗 */
            vd_g_XspiIviSub1Hdcp(u1_gp_HDCP_Act);
            /* 初期化完了通知 */
            vd_g_XspiIviSub1PowerDevInitCmpApp((U1)XSPI_IVI_POWER_GVIFSEND_INI);
            /* 次状態へ遷移 */
            u1_t_return = (U1)TRUE;
            Mcu_OnStep_GVIF3TX_HDCP = (U2)MCU_STEP_GVIF3TX_HDCP_FIN;
        }

    case MCU_STEP_GVIF3TX_HDCP_24:
        /* レジスタ書込み処理 */
        u1_t_sts = Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_GVIF_TX, &Mcu_RegStep_GVIF3TX, (U2)MCU_WRINUM_GVIF3TX_HDCP_6,
                                                (U1)GP_I2C_MA_SLA_3_GVIF_TX, GVIFTX_HDCP_6, &Mcu_OnStep_GVIF3TX_AckTime,
                                                st_sp_MCU_SYS_PWR_GVIFSNDR_HDCP6, &Mcu_RegSet_BetWaitTime);

        if(u1_t_sts == (U1)TRUE){
            /* 全書込み完了 次状態に遷移 */
            Mcu_OnStep_GVIF3TX_HDCP   = (U2)MCU_STEP_GVIF3TX_HDCP_03;
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_25:
        /* レジスタ書込み処理 */
        u1_t_sts = Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_GVIF_TX, &Mcu_RegStep_GVIF3TX, (U2)MCU_WRINUM_GVIF3TX_HDCP_7,
                                                (U1)GP_I2C_MA_SLA_3_GVIF_TX, GVIFTX_HDCP_7, &Mcu_OnStep_GVIF3TX_AckTime,
                                                st_sp_MCU_SYS_PWR_GVIFSNDR_HDCP7, &Mcu_RegSet_BetWaitTime);

        if(u1_t_sts == (U1)TRUE){
            /* 全書込み完了 次状態に遷移 */
            Mcu_OnStep_GVIF3TX_HDCP   = (U2)MCU_STEP_GVIF3TX_HDCP_26;
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_26:
        /* レジスタ書込み処理 */
        u1_t_sts = Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_GVIF_TX, &Mcu_RegStep_GVIF3TX, (U2)MCU_WRINUM_GVIF3TX_HDCP_HPD,
                                                (U1)GP_I2C_MA_SLA_3_GVIF_TX, GVIFTX_HDCP_HPD, &Mcu_OnStep_GVIF3TX_AckTime,
                                                st_sp_MCU_SYS_PWR_GVIFSNDR_HDCP_HPD, &Mcu_RegSet_BetWaitTime);

        if(u1_t_sts == (U1)TRUE){
            /* 全書込み完了 次状態に遷移 */
            Mcu_OnStep_GVIF3TX_HDCP   = (U2)MCU_STEP_GVIF3TX_HDCP_27;
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_27:
        /* レジスタ書込み処理 */
        u1_t_sts = Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_GVIF_TX, &Mcu_RegStep_GVIF3TX, (U2)MCU_WRINUM_GVIF3TX_HDCP_8,
                                                (U1)GP_I2C_MA_SLA_3_GVIF_TX, GVIFTX_HDCP_8, &Mcu_OnStep_GVIF3TX_AckTime,
                                                st_sp_MCU_SYS_PWR_GVIFSNDR_HDCP8, &Mcu_RegSet_BetWaitTime);

        if(u1_t_sts == (U1)TRUE){
            /* 全書込み完了 次状態に遷移 */
            Mcu_OnStep_GVIF3TX_HDCP   = (U2)MCU_STEP_GVIF3TX_HDCP_28;
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_28:
        /* レジスタ読出し処理 */
        u1_t_sts =  Mcu_Dev_I2c_Ctrl_RegRead((U1)MCU_I2C_ACK_GVIF_TX, &Mcu_RegStep_GVIF3TX, (U1)GP_I2C_MA_SLA_3_GVIF_TX,
                                                &Mcu_OnStep_GVIF3TX_AckTime, st_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_EVENT_RD, &Mcu_RegSet_BetWaitTime, (U1)MCU_I2C_WAIT_B89);

        if(u1_t_sts == (U1)TRUE) {
            /* 次状態に遷移 */
            Mcu_OnStep_GVIF3TX_HDCP = (U2)MCU_STEP_GVIF3TX_HDCP_29;
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_29:
        u1_t_rg_read    = st_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_EVENT_RD[1].u1p_pdu[1];

        if((u1_t_rg_read & u1_s_HDCPTX_EVENT_ERR_MSK) == u1_s_HDCPTX_EVENT_ERR_MSK){
            /* D点(HDCP認証エラー処理)へ遷移 */
            Mcu_OnStep_GVIF3TX_HDCP = (U2)MCU_STEP_GVIF3TX_HDCP_21;
        }
        else if((u1_t_rg_read & u1_s_HDCPTX_EVENT_RDY_MSK) == u1_s_HDCPTX_EVENT_RDY_MSK){
            /* K点(認証完了後の処理)へ遷移 */
            Mcu_OnStep_GVIF3TX_HDCP = (U2)MCU_STEP_GVIF3TX_HDCP_12;
        }
        else{
            /* I点(HDCPTXイベントモニタRead)に遷移 */
            Mcu_OnStep_GVIF3TX_HDCP = (U2)MCU_STEP_GVIF3TX_HDCP_28;
        }
        break;

    case MCU_STEP_GVIF3TX_HDCP_FIN:
        u1_t_return = (U1)TRUE;
        break;
    
    default:
        /* 異常ステータスの場合は最初からやり直す */
        Mcu_OnStep_GVIF3TX_HDCP = (U2)MCU_STEP_GVIF3TX_HDCP_01;
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
    u1_g_HDCP_Act_Hook = (U1)TRUE;
}
