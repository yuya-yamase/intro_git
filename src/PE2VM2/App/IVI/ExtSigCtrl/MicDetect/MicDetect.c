/* 0.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Mic Power Control & Detection Specification (26CDC)                                                                              */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MIC_DETECT_C_MAJOR                      (0)
#define MIC_DETECT_C_MINOR                      (0)
#define MIC_DETECT_C_PATCH                      (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "MicDetect_cfg_private.h"

#include "Dio.h"
#include "Dio_Symbols.h"
#include "iohw_adc_sh.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((MIC_DETECT_C_MAJOR != MIC_DETECT_H_MAJOR) || \
     (MIC_DETECT_C_MINOR != MIC_DETECT_H_MINOR) || \
     (MIC_DETECT_C_PATCH != MIC_DETECT_H_PATCH))
#error "MicDetect.c and MicDetect.h : source and header files are inconsistent!"
#endif

#if ((MIC_DETECT_C_MAJOR != MIC_DETECT_PRIVATE_H_MAJOR) || \
     (MIC_DETECT_C_MINOR != MIC_DETECT_PRIVATE_H_MINOR) || \
     (MIC_DETECT_C_PATCH != MIC_DETECT_PRIVATE_H_PATCH))
#error "MicDetect.c and MicDetect_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* トリガテーブルサイズ */
#define MICDETECT_TRGTBL_MICON                  (MICDETECT_KIND_NUM)

/* トリガタイマ有効フラグ論理 */
#define MICDETECT_TRG_TIM_OFF                   (0x00U)         /* トリガタイマOFF */
#define MICDETECT_TRG_TIM_ON                    (0x01U)         /* トリガタイマON */

/* トリガ条件 */
#define MICDETECT_TRG_OFF                       (0x00U)         /* トリガ条件OFF */
#define MICDETECT_TRG_ON                        (0x01U)         /* トリガ条件ON */

/* トリガ論理 */
#define MICDETECT_TRG_BIT_OFF                   (0x00U)         /* トリガBit OFF */
#define MICDETECT_TRG_BIT_ON                    (0x01U)         /* トリガBit ON */

/* 同一論理取得回数カウント処理 */
#define MICDETECT_SAME_CNT_INIT                 (0x01U)         /* 同一論理取得カウント初期値   */

/* 車両信号ポーリング状態定義 */
#define MICDETECT_POLL_STS_STOP                 (0x00U)         /* ポーリング停止中     */
#define MICDETECT_POLL_STS_STR_WAIT             (0x01U)         /* ポーリング開始待ち   */
#define MICDETECT_POLL_STS_CYC                  (0x02U)         /* ポーリング定期       */

/* 端子状態判定 */
#define MICDETECT_TMNL_STS_NON                  (0x00U)         /* 端子状態_未確定  */
#define MICDETECT_TMNL_STS_OFF                  (0x01U)         /* 端子状態_未接続  */
#define MICDETECT_TMNL_STS_ON                   (0x02U)         /* 端子状態_接続    */
#define MICDETECT_TMNL_STS_PWRFAULT             (0x03U)         /* 端子状態_天絡    */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* ポーリングステータス */
typedef struct {
    U1      u1_poll_sts;                       /* ポーリング状態 */
    U1      u1_poll_timcnt;                    /* ポーリングタイマカウンタ */
    U1      u1_poll_trg;                       /* ポーリング開始トリガ */
    U1      u1_poll_nowsts;                    /* ポーリング端子現在状態 */
    U1      u1_poll_sndsts;                    /* ポーリング端子送信状態 */
    U1      u1_poll_samecnt;                   /* ポーリング端子同一状態カウンタ */
} ST_MICDETECT_POLL_STS;

/* トリガタイマテーブル */
typedef struct {
    U1      u1_trgtim_flg;                     /* トリガタイマ有効フラグ */
    U1      u1_trgtim_cnt;                     /* トリガタイマカウント */
    U1      u1_trgtbl_cnt;                     /* トリガテーブルカウント */
} ST_MICDETECT_TRG_TIM_STS;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* 前回タスクのMIC-ON端子状態 */
static U1                                       u1_s_micdetect_micon_pre;

/* 車両信号ポーリングステータス格納配列 */
static ST_MICDETECT_POLL_STS                    st_sp_MicDetect_PollSts[MICDETECT_KIND_NUM];
/* トリガステータス格納配列 */
static ST_MICDETECT_TRG_TIM_STS                 st_sp_MicDetect_TrgTim[MICDETECT_TRG_NUM];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void     vd_s_MicDetect_Rcv_MicOnSts(const U1 u1_a_PORT);
static void     vd_s_MicDetect_PollTrgSet(const U1 u1_a_BYFACT, const U1 u1_a_KIND, const U1 u1_a_BYSTS);
static void     vd_s_MicDetect_PollStrChk(const U1 u1_a_KIND);
static void     vs_s_MicDetect_PollEndChk(const U1 u1_a_KIND);
static void     vd_s_MicDetect_Poll( void );
static void     vd_s_MicDetect_GetSts( void );
static void     vd_s_MicDetect_TrgTim( void );
static void     vd_s_MicDetect_TrgTimCtl(const ST_MICDETECT_TRG_CNT_STS * u1_a_TRGSTS, const U1 u1_a_TRGID);
static U1       u1_s_MicDetect_StsGet(const U1 u1_a_KIND, U1 * u1_ap_sts);
static void     vd_s_MicDetect_DatSnd(const U1 u1_a_KIND);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_MICDETECT_TRG_CNT_STS                  st_gp_MICDETECT_TRGCNT[MICDETECT_TRGTBL_MICON] = {
    {MICDETECT_KIND_MIC1,   (U1)0U},    /* MIC1 */
    {MICDETECT_KIND_MIC2,   (U1)0U},    /* MIC2 */
    {MICDETECT_KIND_MIC3,   (U1)0U},    /* MIC3 */
    {MICDETECT_KIND_MIC4,   (U1)0U}     /* MIC4 */
};

const ST_MICDETECT_TRG_STS                      st_gp_MICDETECT_TRG[MICDETECT_TRG_NUM] = {
    {st_gp_MICDETECT_TRGCNT,    (U1)MICDETECT_TRG_MIC_ON_BIT,   (U1)MICDETECT_TRGTBL_MICON}
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void            vd_g_MicDetectInit(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    初期化処理                                                                                                        */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_MicDetectInit( void )
{
    U1  u1_t_loop;

    /* 前回タスクのMIC-ON端子状態 初期化 */
    u1_s_micdetect_micon_pre     = (U1)STD_LOW;

    /* 車両信号ポーリングステータス格納配列 初期化 */
    for(u1_t_loop = (U1)0U; u1_t_loop < (U1)MICDETECT_KIND_NUM; u1_t_loop++){
        st_sp_MicDetect_PollSts[u1_t_loop].u1_poll_sts      = (U1)MICDETECT_POLL_STS_STOP;
        st_sp_MicDetect_PollSts[u1_t_loop].u1_poll_timcnt   = (U1)0U;
        st_sp_MicDetect_PollSts[u1_t_loop].u1_poll_trg      = (U1)MICDETECT_TRG_INIT;
        st_sp_MicDetect_PollSts[u1_t_loop].u1_poll_nowsts   = (U1)MICDETECT_TMNL_STS_NON;
        st_sp_MicDetect_PollSts[u1_t_loop].u1_poll_sndsts   = (U1)MICDETECT_TMNL_STS_NON;
        st_sp_MicDetect_PollSts[u1_t_loop].u1_poll_samecnt  = (U1)MICDETECT_SAME_CNT_INIT;
    }

    /* トリガステータス格納配列 初期化 */
    for(u1_t_loop = (U1)0U; u1_t_loop < (U1)MICDETECT_KIND_NUM; u1_t_loop++){
        st_sp_MicDetect_TrgTim[u1_t_loop].u1_trgtim_flg     = (U1)0U;
        st_sp_MicDetect_TrgTim[u1_t_loop].u1_trgtim_cnt     = (U1)0U;
        st_sp_MicDetect_TrgTim[u1_t_loop].u1_trgtbl_cnt     = (U1)0U;
    }
}

/*===================================================================================================================================*/
/*  void            vd_g_MicDetectMainTask(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    定期処理                                                                                                          */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_MicDetectMainTask( void )
{
    vd_s_MicDetect_TrgTim();
    vd_s_MicDetect_Poll();
}

/*===================================================================================================================================*/
/*  static void     vd_s_MicDetect_Rcv_MicOnSts(const U1 u1_a_PORT)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    MIC-ON入力変化時処理                                                                                              */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_MicDetect_Rcv_MicOnSts(const U1 u1_a_PORT)
 {
    /* 受け取ったMIC-ON端子状態により判定 */
    if (u1_a_PORT == (U1)STD_HIGH) {
        /* ポーリングのトリガタイマを起動させる */
        st_sp_MicDetect_TrgTim[MICDETECT_TRG_MIC_ON].u1_trgtim_flg = MICDETECT_TRG_TIM_ON;
        st_sp_MicDetect_TrgTim[MICDETECT_TRG_MIC_ON].u1_trgtim_cnt = (U1)0x00;
        st_sp_MicDetect_TrgTim[MICDETECT_TRG_MIC_ON].u1_trgtbl_cnt = (U1)0x00;
        vd_s_MicDetect_TrgTim();
    } else {
        /* MIC-ON=Loのため終了処理 */
        /* MIC-DET */
        vd_s_MicDetect_PollTrgSet((U1)MICDETECT_TRG_MIC_ON_BIT, (U1)MICDETECT_KIND_MIC1, (U1)MICDETECT_TRG_BIT_OFF);
        vs_s_MicDetect_PollEndChk((U1)MICDETECT_KIND_MIC1);
        /* 未確定状態をSiPに送信 */
        vd_s_MicDetect_DatSnd((U1)MICDETECT_KIND_MIC1);

        /* MIC2-DET */
        vd_s_MicDetect_PollTrgSet((U1)MICDETECT_TRG_MIC_ON_BIT, (U1)MICDETECT_KIND_MIC2, (U1)MICDETECT_TRG_BIT_OFF);
        vs_s_MicDetect_PollEndChk((U1)MICDETECT_KIND_MIC2);
        /* 未確定状態をSiPに送信 */
        vd_s_MicDetect_DatSnd((U1)MICDETECT_KIND_MIC2);

        /* MIC3-DET */
        vd_s_MicDetect_PollTrgSet((U1)MICDETECT_TRG_MIC_ON_BIT, (U1)MICDETECT_KIND_MIC3, (U1)MICDETECT_TRG_BIT_OFF);
        vs_s_MicDetect_PollEndChk((U1)MICDETECT_KIND_MIC3);
        /* 未確定状態をSiPに送信 */
        vd_s_MicDetect_DatSnd((U1)MICDETECT_KIND_MIC3);

        /* MIC4-DET */
        vd_s_MicDetect_PollTrgSet((U1)MICDETECT_TRG_MIC_ON_BIT, (U1)MICDETECT_KIND_MIC4, (U1)MICDETECT_TRG_BIT_OFF);
        vs_s_MicDetect_PollEndChk((U1)MICDETECT_KIND_MIC4);
        /* 未確定状態をSiPに送信 */
        vd_s_MicDetect_DatSnd((U1)MICDETECT_KIND_MIC4);
    }
}

/*===================================================================================================================================*/
/*  static void     vd_s_MicDetect_PollTrgSet(const U1 u1_a_BYFACT, const U1 u1_a_KIND, const U1 u1_a_BYSTS)                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    車両信号制御トリガ更新                                                                                             */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_MicDetect_PollTrgSet(const U1 u1_a_BYFACT, const U1 u1_a_KIND, const U1 u1_a_BYSTS)
{
    /* トリガ状態を更新 */
    /* OFFに更新なら */
    if (MICDETECT_TRG_BIT_OFF == u1_a_BYSTS) {
        st_sp_MicDetect_PollSts[u1_a_KIND].u1_poll_trg &= (~u1_a_BYFACT);
    } else {
        st_sp_MicDetect_PollSts[u1_a_KIND].u1_poll_trg |= u1_a_BYFACT;
    }
}

/*===================================================================================================================================*/
/*  static void     vd_s_MicDetect_PollStrChk(const U1 u1_a_KIND)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    車両信号制御トリガ更新                                                                                             */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_MicDetect_PollStrChk(const U1 u1_a_KIND)
{
    U1      u1_t_trgflg;        /* トリガ条件成立フラグ */
    
    /* 入力開始要因の車両信号を起動 */
    /* 開始トリガの車両信号 */
    u1_t_trgflg = (U1)MICDETECT_TRG_OFF;    /* 一旦OFF */
    
    /* トリガがすべて成立したら */
    if ((st_sp_MicDetect_PollSts[u1_a_KIND].u1_poll_trg & st_gp_MICDETECT_STS[u1_a_KIND].u1_STRTRG) == st_gp_MICDETECT_STS[u1_a_KIND].u1_STRTRG) {
        u1_t_trgflg = (U1)MICDETECT_TRG_ON;
    } else {
        /* do nothing */
    }
    
    /* トリガ条件成立かつ対象信号がポーリング停止状態 */
    if ((u1_t_trgflg == (U1)MICDETECT_TRG_ON) && (st_sp_MicDetect_PollSts[u1_a_KIND].u1_poll_sts) == (U1)MICDETECT_POLL_STS_STOP) {
        /* 開始処理関数なし(開始処理なしで定期処理スタート)であれば */
        if (st_gp_MICDETECT_STS[u1_a_KIND].fp_vd_STADR == vdp_PTR_NA) {
            st_sp_MicDetect_PollSts[u1_a_KIND].u1_poll_sts      = (U1)MICDETECT_POLL_STS_CYC;                   /* ポーリング定期状態 */
            st_sp_MicDetect_PollSts[u1_a_KIND].u1_poll_timcnt   = st_gp_MICDETECT_STS[u1_a_KIND].u1_CYCTIM;     /* ポーリングカウンタ */
        } else {
            st_sp_MicDetect_PollSts[u1_a_KIND].u1_poll_sts      = (U1)MICDETECT_POLL_STS_STR_WAIT;              /* ポーリング開始待ち状態 */
            st_sp_MicDetect_PollSts[u1_a_KIND].u1_poll_timcnt   = st_gp_MICDETECT_STS[u1_a_KIND].u1_STRTIM;     /* ポーリングカウンタ */
        }
    } else {
        /* do nothing */
    }
}

/*===================================================================================================================================*/
/*  static void     vs_s_MicDetect_PollEndChk(const U1 u1_a_KIND)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    車両信号制御ポーリング処理終了判定処理                                                                               */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vs_s_MicDetect_PollEndChk(const U1 u1_a_KIND)
{
    U1  u1_t_byTrgFlg;  /* トリガ条件成立フラグ */

    /* 終了トリガの車両信号 */
    u1_t_byTrgFlg = (U1)MICDETECT_TRG_OFF;  /* 一旦OFF */

    if (st_gp_MICDETECT_STS[u1_a_KIND].u1_ENDTRG != (U1)MICDETECT_END_TRG_NON) {
        if ((st_sp_MicDetect_PollSts[u1_a_KIND].u1_poll_trg & st_gp_MICDETECT_STS[u1_a_KIND].u1_ENDTRG) != st_gp_MICDETECT_STS[u1_a_KIND].u1_ENDTRG) {
            u1_t_byTrgFlg = (U1)MICDETECT_TRG_ON;
        } else {
            /* do nothing */
        }
    } else {
        /* 終了トリガのない信号は処理なし */
    }

    /* トリガ条件成立かつ対象信号がポーリング停止状態以外なら */
    if ((u1_t_byTrgFlg == (U1)MICDETECT_TRG_ON) && (st_sp_MicDetect_PollSts[u1_a_KIND].u1_poll_sts != (U1)MICDETECT_POLL_STS_STOP)) {
        st_sp_MicDetect_PollSts[u1_a_KIND].u1_poll_sts = (U1)MICDETECT_POLL_STS_STOP;   /* ポーリング停止状態 */
        st_sp_MicDetect_PollSts[u1_a_KIND].u1_poll_timcnt = (U1)0x00U;                  /* ポーリングカウンタ */
        if (st_gp_MICDETECT_STS[u1_a_KIND].fp_vd_EDADR != vdp_PTR_NA) {
            (st_gp_MICDETECT_STS[u1_a_KIND].fp_vd_EDADR)(u1_a_KIND);                    /* 終了関数コール */
        } else {
            /* do nothing */
        }
    } else {
        /* 入力要因が起動要因でないため、処理なし */
    }
}

/*===================================================================================================================================*/
/*  void            vd_s_MicDetect_Poll(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    車両信号制御ポーリング処理                                                                                         */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_MicDetect_Poll( void )
{
    U1  u1_t_loop;              /* ループ処理用カウンタ */
    
    /* MIC-ON状態監視 */
    vd_s_MicDetect_GetSts();

    /* 車両信号分ループ */
    for (u1_t_loop = (U1)0; u1_t_loop < (U1)MICDETECT_KIND_NUM; u1_t_loop++) {
        /* 車両信号ポーリング状態をチェック */
        if (st_sp_MicDetect_PollSts[u1_t_loop].u1_poll_sts != (U1)MICDETECT_POLL_STS_STOP) {
            /* ポーリングタイマカウンタデクリメント */
            if (st_sp_MicDetect_PollSts[u1_t_loop].u1_poll_timcnt > (U1)0U) {/* マイナスガード */
                st_sp_MicDetect_PollSts[u1_t_loop].u1_poll_timcnt--;
            } else {
                /* ここは入らないはず */
            }
            /* 処理コールチェック */
            if (st_sp_MicDetect_PollSts[u1_t_loop].u1_poll_timcnt <= (U1)0U) {
                /* ポーリング定期状態 */
                if (st_sp_MicDetect_PollSts[u1_t_loop].u1_poll_sts == (U1)MICDETECT_POLL_STS_CYC) {
                    (st_gp_MICDETECT_STS[u1_t_loop].fp_vd_CYCADR)(u1_t_loop);
                /* ポーリング開始待ち状態 */
                } else if (st_sp_MicDetect_PollSts[u1_t_loop].u1_poll_sts == (U1)MICDETECT_POLL_STS_STR_WAIT) {
                    (st_gp_MICDETECT_STS[u1_t_loop].fp_vd_STADR)(u1_t_loop);
                } else {
                    /* ここは入らないはず */
                }
            }
        } else {
            /* 車両信号ポーリング停止中のため、処理をスキップ */
        }
    }
}

/*===================================================================================================================================*/
/*  void            vd_s_MicDetect_Poll(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    MIC-ON状態監視                                                                                                    */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_MicDetect_GetSts( void )
{
    U1  u1_t_mic_on;                /* MIC-ON端子状態 */

    /* MIC-ON端子状態取得 */
    u1_t_mic_on     = Dio_ReadChannel((U2)MICDETECT_PORT_MIC_ON);            

    if(u1_s_micdetect_micon_pre != u1_t_mic_on){

        /* 前回電源ステータス更新 */
        u1_s_micdetect_micon_pre = u1_t_mic_on;

        /* MIC-ON処理 */
        vd_s_MicDetect_Rcv_MicOnSts(u1_t_mic_on);
    }
    else{
        /* do nothing */;
    }
}

/*===================================================================================================================================*/
/*  static void     vd_s_MicDetect_TrgTim( void )                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    車両信号制御トリガタイマ管理処理                                                                                    */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_MicDetect_TrgTim( void )
{
    U1      u1_t_cnt;        /* ループ処理用カウンタ */
    
    /* トリガタイマ管理 */
    for (u1_t_cnt = (U1)0U; u1_t_cnt < MICDETECT_TRG_NUM; u1_t_cnt++) {
        if (st_sp_MicDetect_TrgTim[u1_t_cnt].u1_trgtim_flg == (U1)MICDETECT_TRG_TIM_ON) {
            vd_s_MicDetect_TrgTimCtl(st_gp_MICDETECT_TRG[u1_t_cnt].stp_MSGTBL, u1_t_cnt);
        } else {
            /* do nothing */
        }
    }
}

/*===================================================================================================================================*/
/*  static void     vd_s_MicDetect_TrgTimCtl(const ST_MICDETECT_TRG_CNT_STS * u1_a_TRGSTS, const U1 u1_a_TRGID)                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    車両信号制御トリガタイマ制御処理                                                                                    */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_MicDetect_TrgTimCtl(const ST_MICDETECT_TRG_CNT_STS * u1_a_TRGSTS, const U1 u1_a_TRGID)
{    
    /* トリガカウント管理テーブルが最後まで進むまでループする */
    while (st_sp_MicDetect_TrgTim[u1_a_TRGID].u1_trgtbl_cnt < st_gp_MICDETECT_TRG[u1_a_TRGID].u1_trgtbl_max) {
        /* トリガタイマカウントが設定値まで進んだら */
        if (st_sp_MicDetect_TrgTim[u1_a_TRGID].u1_trgtim_cnt >= u1_a_TRGSTS[st_sp_MicDetect_TrgTim[u1_a_TRGID].u1_trgtbl_cnt].u1_timcnt) {
            /* トリガ関数コール */
            vd_s_MicDetect_PollTrgSet(st_gp_MICDETECT_TRG[u1_a_TRGID].u1_trgbit,
                                        u1_a_TRGSTS[st_sp_MicDetect_TrgTim[u1_a_TRGID].u1_trgtbl_cnt].u1_trmnl_no, MICDETECT_TRG_BIT_ON);
            vd_s_MicDetect_PollStrChk(u1_a_TRGSTS[st_sp_MicDetect_TrgTim[u1_a_TRGID].u1_trgtbl_cnt].u1_trmnl_no);
            /* テーブルインクリメント */
            st_sp_MicDetect_TrgTim[u1_a_TRGID].u1_trgtbl_cnt++;
        } else {
            /* 成立したトリガタイマがないため、処理を抜ける */
            break;
        }
    }
    
    /* トリガカウント管理テーブルが最後まで進んだら */
    if (st_sp_MicDetect_TrgTim[u1_a_TRGID].u1_trgtbl_cnt >= st_gp_MICDETECT_TRG[u1_a_TRGID].u1_trgtbl_max) {
        /* トリガタイマ処理終了のため、変数リセット */
        st_sp_MicDetect_TrgTim[u1_a_TRGID].u1_trgtim_flg = (U1)MICDETECT_TRG_TIM_OFF;
        st_sp_MicDetect_TrgTim[u1_a_TRGID].u1_trgtim_cnt = (U1)0x00U;
        st_sp_MicDetect_TrgTim[u1_a_TRGID].u1_trgtbl_cnt = (U1)0x00U;
    } else {
        /* トリガタイマインクリメント */
        st_sp_MicDetect_TrgTim[u1_a_TRGID].u1_trgtim_cnt++;
    }
}

/*===================================================================================================================================*/
/*  void            vd_g_MicDetect_MicStr(const U1 u1_a_KIND)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    MIC接続検知開始処理                                                                                               */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_MicDetect_MicStr(const U1 u1_a_KIND)
{
    switch(u1_a_KIND){
        case MICDETECT_KIND_MIC1:
            /* ポーリング定期状態に遷移し、次回取得タイミングから制御開始 */
            st_sp_MicDetect_PollSts[MICDETECT_KIND_MIC1].u1_poll_sts = (U1)MICDETECT_POLL_STS_CYC;                              /* ポーリング定期状態 */
            st_sp_MicDetect_PollSts[MICDETECT_KIND_MIC1].u1_poll_timcnt = st_gp_MICDETECT_STS[MICDETECT_KIND_MIC1].u1_CYCTIM;   /* ポーリングカウンタ */
            break;

        case MICDETECT_KIND_MIC2:
            /* ポーリング定期状態に遷移し、次回取得タイミングから制御開始 */
            st_sp_MicDetect_PollSts[MICDETECT_KIND_MIC2].u1_poll_sts = (U1)MICDETECT_POLL_STS_CYC;                              /* ポーリング定期状態 */
            st_sp_MicDetect_PollSts[MICDETECT_KIND_MIC2].u1_poll_timcnt = st_gp_MICDETECT_STS[MICDETECT_KIND_MIC2].u1_CYCTIM;   /* ポーリングカウンタ */
            break;

        case MICDETECT_KIND_MIC3:
            /* ポーリング定期状態に遷移し、次回取得タイミングから制御開始 */
            st_sp_MicDetect_PollSts[MICDETECT_KIND_MIC3].u1_poll_sts = (U1)MICDETECT_POLL_STS_CYC;                              /* ポーリング定期状態 */
            st_sp_MicDetect_PollSts[MICDETECT_KIND_MIC3].u1_poll_timcnt = st_gp_MICDETECT_STS[MICDETECT_KIND_MIC3].u1_CYCTIM;   /* ポーリングカウンタ */
            break;

        case MICDETECT_KIND_MIC4:
            /* ポーリング定期状態に遷移し、次回取得タイミングから制御開始 */
            st_sp_MicDetect_PollSts[MICDETECT_KIND_MIC4].u1_poll_sts = (U1)MICDETECT_POLL_STS_CYC;                              /* ポーリング定期状態 */
            st_sp_MicDetect_PollSts[MICDETECT_KIND_MIC4].u1_poll_timcnt = st_gp_MICDETECT_STS[MICDETECT_KIND_MIC4].u1_CYCTIM;   /* ポーリングカウンタ */
            break;

        default:
            /* 範囲外は処理なしとする */
            break;
    }
}

/*===================================================================================================================================*/
/*  void            vd_g_MicDetect_Cyc(const U1 u1_a_KIND)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    車両信号制御_共通定周期制御                                                                                        */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_MicDetect_Cyc(const U1 u1_a_KIND)
{
    U1    u1_t_rslt;        /* 処理結果 */
    U1    u1_t_nowcnc;      /* 今回接続判定 */
    
    u1_t_nowcnc = (U1)MICDETECT_TMNL_STS_NON;
    u1_t_rslt   = u1_s_MicDetect_StsGet(u1_a_KIND, &u1_t_nowcnc);
    
    /* AD変換OKなら */
    if (u1_t_rslt == (U1)TRUE) {
        /* 接続論理変化確認 */
        if (u1_t_nowcnc == st_sp_MicDetect_PollSts[u1_a_KIND].u1_poll_nowsts) {
            /* 同一論理取得カウンタ */
            if (st_sp_MicDetect_PollSts[u1_a_KIND].u1_poll_samecnt < st_gp_MICDETECT_STS[u1_a_KIND].u1_SAME_CNT_NUM) {
                st_sp_MicDetect_PollSts[u1_a_KIND].u1_poll_samecnt++;
            } else {
                /* 論理検知回数に達しているのでカウンタインクリメントしない */
            }
        } else {
            st_sp_MicDetect_PollSts[u1_a_KIND].u1_poll_samecnt = MICDETECT_SAME_CNT_INIT;    /* 論理変化によりカウンタリセット */
        }

        /* グローバルに値格納 */
        st_sp_MicDetect_PollSts[u1_a_KIND].u1_poll_nowsts = u1_t_nowcnc;
        
        /* 状態通知要否確認 */
        if ((st_sp_MicDetect_PollSts[u1_a_KIND].u1_poll_samecnt >= st_gp_MICDETECT_STS[u1_a_KIND].u1_SAME_CNT_NUM) &&       /* 接続状態確定 */
              (st_sp_MicDetect_PollSts[u1_a_KIND].u1_poll_sndsts != st_sp_MicDetect_PollSts[u1_a_KIND].u1_poll_nowsts)) {   /* 前回送信状態と違う */
            st_sp_MicDetect_PollSts[u1_a_KIND].u1_poll_sndsts = st_sp_MicDetect_PollSts[u1_a_KIND].u1_poll_nowsts;
            vd_s_MicDetect_DatSnd(u1_a_KIND);
            if (st_gp_MICDETECT_STS[u1_a_KIND].fp_vd_CTLTMNLADR != vdp_PTR_NA) {
                (st_gp_MICDETECT_STS[u1_a_KIND].fp_vd_CTLTMNLADR)();        /* 端子制御関数コール      */
            } else {
                /* do nothing */
            }
         
        } else {
            /* do nothing */
        }
    } else {
        /* do nothing */
    }
    
    /* 次回ポーリングカウンタをセット */
    st_sp_MicDetect_PollSts[u1_a_KIND].u1_poll_timcnt = st_gp_MICDETECT_STS[u1_a_KIND].u1_CYCTIM;
    
    /* 関数終了 */
    return;
}

/*===================================================================================================================================*/
/*  void            vd_g_MicDetect_Cyc(static U1 u1_a_kind)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    車両信号制御_共通端子状態取得処理                                                                                   */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_MicDetect_StsGet(const U1 u1_a_KIND, U1 * u1_ap_sts)
{
    U1      u1_t_rslt;        /* 処理結果 */
    U2      u2_t_ad;          /* AD変換値一時格納 */

    u1_t_rslt   = (U1)FALSE;
    u2_t_ad     = (U2)0U;

    /*****************************************************************/
    /* 端子H/Lと論理ON/OFFの組み合わせは仕様で確認の上、設定すること */
    /*****************************************************************/
    switch(u1_a_KIND){
        case MICDETECT_KIND_MIC1:
            u1_t_rslt = u1_g_IoHwAdcRead((U1)MICDETECT_PORT_MIC_DET, &u2_t_ad);

            /* AD変換OKなら */
            if (u1_t_rslt == (U1)TRUE) {
                /* AD変換データを論理データに変換する */
                /* AD値が判定閾値内であれば接続あり */
                if (u2_t_ad > (U2)MICDETECT_AD_PWRFAULT) {
                    *u1_ap_sts = (U1)MICDETECT_TMNL_STS_PWRFAULT;
                } else if (u2_t_ad < (U2)MICDETECT_AD_BORDER) {
                    *u1_ap_sts = (U1)MICDETECT_TMNL_STS_OFF;
                } else {
                    *u1_ap_sts = (U1)MICDETECT_TMNL_STS_ON;
                }
            }
            break;

        case MICDETECT_KIND_MIC2:
            u1_t_rslt = u1_g_IoHwAdcRead((U1)MICDETECT_PORT_MIC2_DET, &u2_t_ad);

            /* AD変換OKなら */
            if (u1_t_rslt == (U1)TRUE) {
                /* AD変換データを論理データに変換する */
                /* AD値が判定閾値内であれば接続あり */
                if (u2_t_ad > (U2)MICDETECT_AD_PWRFAULT) {
                    *u1_ap_sts = (U1)MICDETECT_TMNL_STS_PWRFAULT;
                } else if (u2_t_ad < (U2)MICDETECT_AD_BORDER) {
                    *u1_ap_sts = (U1)MICDETECT_TMNL_STS_OFF;
                } else {
                    *u1_ap_sts = (U1)MICDETECT_TMNL_STS_ON;
                }
            }
            break;

        case MICDETECT_KIND_MIC3:
            u1_t_rslt = u1_g_IoHwAdcRead((U1)MICDETECT_PORT_MIC3_DET, &u2_t_ad);

            /* AD変換OKなら */
            if (u1_t_rslt == (U1)TRUE) {
                /* AD変換データを論理データに変換する */
                /* AD値が判定閾値内であれば接続あり */
                if (u2_t_ad > (U2)MICDETECT_AD_PWRFAULT) {
                    *u1_ap_sts = (U1)MICDETECT_TMNL_STS_PWRFAULT;
                } else if (u2_t_ad < (U2)MICDETECT_AD_BORDER) {
                    *u1_ap_sts = (U1)MICDETECT_TMNL_STS_OFF;
                } else {
                    *u1_ap_sts = (U1)MICDETECT_TMNL_STS_ON;
                }
            }
            break;

        case MICDETECT_KIND_MIC4:
            u1_t_rslt = u1_g_IoHwAdcRead((U1)MICDETECT_PORT_MIC4_DET, &u2_t_ad);

            /* AD変換OKなら */
            if (u1_t_rslt == (U1)TRUE) {
                /* AD変換データを論理データに変換する */
                /* AD値が判定閾値内であれば接続あり */
                if (u2_t_ad > (U2)MICDETECT_AD_PWRFAULT) {
                    *u1_ap_sts = (U1)MICDETECT_TMNL_STS_PWRFAULT;
                } else if (u2_t_ad < (U2)MICDETECT_AD_BORDER) {
                    *u1_ap_sts = (U1)MICDETECT_TMNL_STS_OFF;
                } else {
                    *u1_ap_sts = (U1)MICDETECT_TMNL_STS_ON;
                }
            }
            break;

        default:
            /* 範囲外は処理なしとする */
            u1_t_rslt = (U1)FALSE;
            break;
    }
    
    /* 関数終了 */
    return(u1_t_rslt);
}

/*===================================================================================================================================*/
/*  void            vd_g_MicDetect_MicEnd(const U1 u1_a_KIND)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    車両信号制御シャットダウン処理                                                                                      */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_MicDetect_MicEnd(const U1 u1_a_KIND)
{
    /* 保持値を初期化 */
    st_sp_MicDetect_PollSts[u1_a_KIND].u1_poll_nowsts   = (U1)MICDETECT_TMNL_STS_NON;   /* MIC接続状態 */
    st_sp_MicDetect_PollSts[u1_a_KIND].u1_poll_sndsts   = (U1)MICDETECT_TMNL_STS_NON;   /* MIC送信状態保持 */
    st_sp_MicDetect_PollSts[u1_a_KIND].u1_poll_samecnt  = (U1)0x00U;                    /* MIC同一状態カウンタ */
}

/*===================================================================================================================================*/
/*  static void     vd_s_MicDetect_DatSnd(const U1 u1_a_KIND)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    車両信号制御_データ送信処理                                                                                        */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_MicDetect_DatSnd(const U1 u1_a_KIND)
{
    if (st_gp_MICDETECT_STS[u1_a_KIND].fp_vd_SNDADR != vdp_PTR_NA) {
        (st_gp_MICDETECT_STS[u1_a_KIND].fp_vd_SNDADR)(u1_t_MICDETECT_CNVRT_ID[u1_a_KIND], st_sp_MicDetect_PollSts[u1_a_KIND].u1_poll_sndsts);
    } else {
        /* do nothing */
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
/*  0.0.0    02/21/2025  TN       New.                                                                                               */
/*                                                                                                                                   */
/*  * TN   = Tetsu Naruse, Denso Techno                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/
