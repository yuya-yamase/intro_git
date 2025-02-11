/* 0.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  CarSpdPls                                                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "CarSpdPls.h"
#include "x_spi_ivi_sub1_system.h"
#include "x_spi_ivi_sub2.h"
#include "Dio.h"
#include "gpt_drv_d16.h"
#include "memcpy_u4.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define CARSPDPLS_CHCNT_MAX         (0xFFFFU)   /* チャネルカウントの最大値  */
 
#define CARSPDPLS_OVF_BIT           (0x0001U)   /* オーバーフローフラグ抽出  */
#define CARSPDPLS_OVF_CNT_MAX       (0xFFU)     /* オーバーフローカウント最大値 */

#define CARSPDPLS_PLS_CHK_MIN       (0U)            /* パルス確定回数最小値  */
#define CARSPDPLS_PLS_CHK_MAX       (32U)       /* パルス確定回数最大値  */

#define CARSPDPLS_CNTCLK_FRQ        (0x00U)     /* 39.0625kHz    */

#define CARSPDPLS_PLS_STP_CNT       (0x00FFFFFFU)   /* 平均算出時に車速0km/hをこの値に置き換えて計算する     */

#define CARSPDPLS_AVE_FACT_MAX      (0x06U)     /* 平均値算出用要素取得最大数    */

#define CARSPDPLS_TIM_CNT           (0x00U)     /* タイマカウントをカウント  */
#define CARSPDPLS_TIM_RST           (0x01U)     /* タイマカウントをリセット  */

#define CARSPDPLS_UP_CNT            (0x00U)     /* アップカウントタイマ  */
#define CARSPDPLS_DOWN_CNT          (0x01U)     /* ダウンカウントタイマ  */

#define CARSPDPLS_TIM_CNT_AVE       (0x00U)     /* 平均値タイマカウント      */
#define CARSPDPLS_TIM_CNT_STP       (0x01U)     /* 停車判定タイマカウント    */
#define CARSPDPLS_TIM_CNT_SNDDAT    (0x02U)     /* データ通知タイマカウント  */
#define CARSPDPLS_TIM_CNT_LIFDAT    (0x03U)     /* 生涯スピード更新タイマカウント    */
#define CARSPDPLS_TIM_CNT_NUM       (0x04U)     /* タイマカウント数          */

#define CARSPDPLS_AVE_CHK_TIM       (0x14U)     /* 平均値チェック20(×2ms=40ms)  */
#define CARSPDPLS_PLS_STP_CHK_TIM   (0x02EEU)   /* 停車判定時間750(×2ms=1500ms) */
#define CARSPDPLS_SND_DAT_TIM       (0x32U)     /* データ通知時間50(×2ms=100ms) */
#define CARSPDPLS_SET_LIFDAT_TIM    (0x05U)     /* 生涯スピード更新時間10(5×2ms=10ms) */

#define CARSPDPLS_AVE_CHK_OFF       (0x00U)     /* 車速平均値計算フラグOFF       */
#define CARSPDPLS_AVE_CHK_ON        (0x01U)     /* 車速平均値計算フラグON        */

#define CARSPDPLS_FLG_INI           (0x01U)
#define CARSPDPLS_FLG_JDG           (2U)

#define CARSPDPLS_WAIT_PLSCHK       (100U)      /* パルス検知待ち時間 100ms */
#define CARSPDPLS_NOCLR             (0x00U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define CARSPDPLS_PORT_V33_PERI     (DIO_ID_PORT10_CH2)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* レジスタリード */
typedef struct {
    U2  u2_cdr;         /* チャネルデータ       */
    U1  u1_ovf;         /* オーバーフローフラグ */
    U2  u2_cnt;         /* チャネルカウンタ     */
} ST_CARSPDPLS_DAT;

/* タイマカウントステータステーブル */
typedef struct {
    U2  u2_timmax;      /* タイマカウント最大値  */
    U1  u1_updwn;       /* カウント種別          */
} ST_CARSPDPLS_TIM_CNT;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  U1 u1_s_carspdpls_ovfcnt;                               /* オーバーフローフラグカウンタ */
static  U2 u2_s_carspdpls_oldchcnt4ms;                          /* チャネルカウンタ前回値保持   */
static  U1 u1_s_carspdpls_plscnt;                               /* パルス確定回数カウンタ       */
static  U4 u4_s_carspdpls_plsdata[CARSPDPLS_PLS_CHK_MAX];       /* 確定パルス保持変数           */
static  U4 u4_s_carspdpls_lastpls;                              /* 最新保持値記録               */
static  U1 u1_s_carspdpls_avefactnum;                           /* 平均値算出用要素取得数       */
static  U4 u4_s_carspdpls_aveplsdata[CARSPDPLS_AVE_FACT_MAX];   /* 平均算出用確定パルス保持変数 */
static  U1 u1_s_carspdpls_avechkflg;                            /* 平均車速算出フラグ           */

static  U2 u2_s_carspdpls_timcnt[CARSPDPLS_TIM_CNT_NUM];        /* タイマカウント保持配列       */

static  U1 u1_s_carspdpls_flg1ms_t_2ms;
static  U1 u1_s_carspdpls_flg2ms_t_4ms;                         /* 2回に1回実行フラグ           */
static  U2 u2_s_carspdpls_oldchcnt2ms;                          /* チャネルカウンタ前回値保持   */

static  U2 u2_s_carspdpls_10mslifplsdat;                        /* 10msの生涯パルス情報         */
static  U1 u1_s_carspdpls_carspdchkflg;                         /* 車速パルス検知開始フラグ     */

static  U1 u1_s_carspdpls_carspdchkcnt;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void    vd_g_CarSpdPls_Rcv_Cyc(void);
static void    vd_s_CarSpdPls_SndDataCal(U2 u2_a_IPTPLSCNT, U1 u1_a_CAL);
static void    vd_s_CarSpdPls_LifPlsDataCal(U1 u1_a_CAL);
static void    vd_s_CarSpdPls_StopChk(void);
static void    vd_s_CarSpdPls_AveDataChk(void);
static void    vd_s_CarSpdPls_SetData(void);
static void    vd_s_CarSpdPls_Rcv_AveSendData(void);
static void    vd_s_CarSpdPls_TimCntCtl(U1 u1_a_TIMECNTID, U1 u1_a_KIND);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_CARSPDPLS_TIM_CNT st_sp_CARSPDPLS_TIMCNT[CARSPDPLS_TIM_CNT_NUM]= {
    {(U2)CARSPDPLS_AVE_CHK_TIM,     (U1)CARSPDPLS_UP_CNT  },
    {(U2)CARSPDPLS_PLS_STP_CHK_TIM, (U1)CARSPDPLS_UP_CNT  },
    {(U2)CARSPDPLS_SND_DAT_TIM,     (U1)CARSPDPLS_UP_CNT  },
    {(U2)CARSPDPLS_SET_LIFDAT_TIM,  (U1)CARSPDPLS_UP_CNT  }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_CarSpdPls_Init(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_CarSpdPls_Init(void)
{
    U1 u1_t_cnt;
    
    for(u1_t_cnt = (U1)0U; u1_t_cnt < (U1)CARSPDPLS_TIM_CNT_NUM; u1_t_cnt++){
        u2_s_carspdpls_timcnt[u1_t_cnt] = (U2)0x0000U;
    }
    u1_s_carspdpls_ovfcnt = (U1)0x00U;              /* オーバーフローフラグカウンタ */
    u2_s_carspdpls_oldchcnt4ms = (U2)CARSPDPLS_CHCNT_MAX;   /* チャネルカウンタ前回値保持変数 */
    u2_s_carspdpls_oldchcnt2ms = (U2)CARSPDPLS_CHCNT_MAX;   /* チャネルカウンタ前回値保持変数 */
    u1_s_carspdpls_plscnt = (U1)0x00U;              /* パルス確定回数カウンタ */
    u1_s_carspdpls_avefactnum = (U1)0x00U;          /* 平均値算出用要素取得数カウンタ */
    u4_s_carspdpls_lastpls = (U4)CARSPDPLS_PLS_STP_CYC; /* 最新保持値記録 */
    u1_s_carspdpls_avechkflg = (U1)CARSPDPLS_AVE_CHK_OFF;       /* 平均車速パルス算出フラグ */
    u1_s_carspdpls_flg1ms_t_2ms = (U1)CARSPDPLS_FLG_INI;
    u1_s_carspdpls_flg2ms_t_4ms = (U1)CARSPDPLS_FLG_INI;
    
    for(u1_t_cnt = (U1)0U; u1_t_cnt < (U1)CARSPDPLS_PLS_CHK_MAX; u1_t_cnt++){
        u4_s_carspdpls_plsdata[u1_t_cnt] = (U2)0x0000U;
    }
    
    for(u1_t_cnt = (U1)0U; u1_t_cnt < (U1)CARSPDPLS_AVE_FACT_MAX; u1_t_cnt++){
        u4_s_carspdpls_aveplsdata[u1_t_cnt] = (U2)0x0000U;
    }
    u2_s_carspdpls_10mslifplsdat = 0x00U;
    u1_s_carspdpls_carspdchkcnt = (U1)0x00U;
    /* 車速パルス検知開始フラグOFF */
    u1_s_carspdpls_carspdchkflg = (U1)FALSE;
}

/*===================================================================================================================================*/
/*  void    vd_g_CarSpdPls_MainTask(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_CarSpdPls_MainTask(void)
{
    static const U2     u2_sp_CARSPDPLS_OPEN_TAUD_START[GPT_D16_START_NUM_CFG] = {
        (U2)GPT_D16_START_CTRL_ELVL_RI | (U2)GPT_D16_START_CTRL_BIT_TRG_ST,
        (U2)GPT_D16_PERI_MAX
    };
    U1 u1_t_v33ferri;

    u1_t_v33ferri= (U1)Dio_ReadChannel(CARSPDPLS_PORT_V33_PERI);
    
    if((u1_s_carspdpls_carspdchkflg == (U1)TRUE) && (u1_t_v33ferri == (U1)FALSE)){
        /* 車速パルス検知開始フラグOFF */
        u1_s_carspdpls_carspdchkflg = (U1)FALSE;
        vd_g_Gpt_D16Stop((U1)GPT_D16_UN_0_CH_14);
        vd_g_Gpt_D16Stop((U1)GPT_D16_UN_0_CH_15);
    }
    
    if((u1_s_carspdpls_carspdchkflg == (U1)FALSE) && (u1_t_v33ferri == (U1)TRUE)){
        u1_s_carspdpls_carspdchkcnt++; 
    }
    
    if((u1_s_carspdpls_carspdchkflg == (U1)FALSE) && (u1_s_carspdpls_carspdchkcnt > (U1)CARSPDPLS_WAIT_PLSCHK)){
        vd_g_CarSpdPls_Init();
        /* 車速パルス検知開始フラグON */
        u1_s_carspdpls_carspdchkflg = (U1)TRUE;
        vd_g_Gpt_D16Start((U1)GPT_D16_UN_0_CH_14, &u2_sp_CARSPDPLS_OPEN_TAUD_START[0]);
        vd_g_Gpt_D16Start((U1)GPT_D16_UN_0_CH_15, &u2_sp_CARSPDPLS_OPEN_TAUD_START[0]);
    }
    
    if(u1_s_carspdpls_flg1ms_t_2ms >= (U1)CARSPDPLS_FLG_JDG){
        if(u1_s_carspdpls_carspdchkflg == (U1)TRUE){
            vd_g_CarSpdPls_Rcv_Cyc();
        }
        u1_s_carspdpls_flg1ms_t_2ms = (U1)CARSPDPLS_FLG_INI;
    }
    else{
        u1_s_carspdpls_flg1ms_t_2ms++;
    }
}

/*===================================================================================================================================*/
/*  static void    vd_g_CarSpdPls_Rcv_Cyc(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_g_CarSpdPls_Rcv_Cyc(void)
{
    ST_CARSPDPLS_DAT stRData;
    U1 u1_t_ovf;
    U1 u1_t_cnt;    /* ループ用カウンタ */
    U1 u1_t_cal4ms; /* カウント値計算用 */
    U2 u2_t_cal4ms; /* カウント値計算用 */
    U1 u1_t_cal2ms; /* カウント値計算用 */
    U2 u2_t_cal2ms; /* カウント値計算用 */

    stRData.u2_cdr = u2_g_Gpt_D16GetTimeCaptured((U1)GPT_D16_UN_0_CH_14, vdp_PTR_NA);
    u1_t_ovf       = u1_g_Gpt_D16IRQst((U1)GPT_D16_UN_0_CH_14, (U1)CARSPDPLS_NOCLR);
    stRData.u1_ovf = u1_t_ovf & (U1)GPT_D16_IRQST_BIT_OVF;
    stRData.u2_cnt = u2_g_Gpt_D16GetTimeElapsed(GPT_D16_UN_0_CH_15, vdp_PTR_NA);
    
    /* オーバーフローフラグがONなら */
    if(stRData.u1_ovf != (U1)0x00U){
        /* 通知するパルス数の最大値を超える場合はカウントしない */
        if(u1_s_carspdpls_ovfcnt < (U1)CARSPDPLS_OVF_CNT_MAX){
            u1_s_carspdpls_ovfcnt++;
        }
    	(void)u1_g_Gpt_D16IRQst((U1)GPT_D16_UN_0_CH_14, (U1)GPT_D16_IRQST_BIT_OVF);
    }
    
    /*======================================================================*/
    /*  車速パルスの計算処理                                                */
    /*======================================================================*/
    if(u1_s_carspdpls_flg2ms_t_4ms >= (U1)CARSPDPLS_FLG_JDG){
        /* 車速パルス計算要否 */
        /* チャネルカウンタ変化なし */
        if(u2_s_carspdpls_oldchcnt4ms == stRData.u2_cnt){
            /* 車両停止判定処理 */
            vd_s_CarSpdPls_StopChk();
            /* チャネルカウンタ減少 */
        }
        else if(u2_s_carspdpls_oldchcnt4ms > stRData.u2_cnt){
            u2_t_cal4ms = u2_s_carspdpls_oldchcnt4ms - stRData.u2_cnt;
            if (u2_t_cal4ms >= (U2)CARSPDPLS_PLS_CHK_MAX){
                u1_t_cal4ms = (U1)CARSPDPLS_PLS_CHK_MAX;
            }
            else{
                u1_t_cal4ms = (U1)u2_t_cal4ms;
            }
            vd_s_CarSpdPls_SndDataCal(stRData.u2_cdr,u1_t_cal4ms);
            /* チャネルカウンタ減少(リセットあり) */
        }
        else if(u2_s_carspdpls_oldchcnt4ms < stRData.u2_cnt){
            /* INTTAUDnIm 発生前に検出される有効エッジ数= TAUDnCDRm ＋ 1 */
            /* カウント0からカウントMAX(CARSPDPLS_CHCNT_MAX)に遷移する際のカウントも含めるため、+1とする */
            u2_t_cal4ms = (((U2)CARSPDPLS_CHCNT_MAX - stRData.u2_cnt) + u2_s_carspdpls_oldchcnt4ms) + (U2)1U;
            if(u2_t_cal4ms >= (U4)CARSPDPLS_PLS_CHK_MAX){
                u1_t_cal4ms = (U1)CARSPDPLS_PLS_CHK_MAX;
            } 
            else{
                u1_t_cal4ms = (U1)u2_t_cal4ms;
            }
            vd_s_CarSpdPls_SndDataCal(stRData.u2_cdr,u1_t_cal4ms);
        }
        else{
            /* 上記以外は処理なし */
        }
        /* 前回値更新 */
        u2_s_carspdpls_oldchcnt4ms = stRData.u2_cnt;
    
        u1_s_carspdpls_flg2ms_t_4ms = (U1)CARSPDPLS_FLG_INI;
    }
    else{
        u1_s_carspdpls_flg2ms_t_4ms++;
    }
    
    /*======================================================================*/
    /*  生涯パルス計算処理                                                  */
    /*======================================================================*/
    /* 生涯パルス計算要否 */
    /* チャネルカウンタ減少 */
    if(u2_s_carspdpls_oldchcnt2ms > stRData.u2_cnt){
        u2_t_cal2ms = u2_s_carspdpls_oldchcnt2ms - stRData.u2_cnt;
        if(u2_t_cal2ms >= (U2)CARSPDPLS_PLS_CHK_MAX){
            u1_t_cal2ms = (U1)CARSPDPLS_PLS_CHK_MAX;
        }
        else{
            u1_t_cal2ms = (U1)u2_t_cal2ms;
        }
        vd_s_CarSpdPls_LifPlsDataCal(u1_t_cal2ms);
    /* チャネルカウンタ減少(リセットあり) */
    }
    else if(u2_s_carspdpls_oldchcnt2ms < stRData.u2_cnt){
        /* INTTAUDnIm 発生前に検出される有効エッジ数= TAUDnCDRm ＋ 1 */
        /* カウント0からカウントMAX(CARSPDPLS_CHCNT_MAX)に遷移する際のカウントも含めるため、+1とする */
        u2_t_cal2ms = (((U2)CARSPDPLS_CHCNT_MAX - stRData.u2_cnt) + u2_s_carspdpls_oldchcnt2ms) + (U2)1U;
        if(u2_t_cal2ms >= (U4)CARSPDPLS_PLS_CHK_MAX){
            u1_t_cal2ms = (U1)CARSPDPLS_PLS_CHK_MAX;
        }
        else{
            u1_t_cal2ms = (U1)u2_t_cal2ms;
        }
        vd_s_CarSpdPls_LifPlsDataCal(u1_t_cal2ms);
    }
    else{
        u1_t_cal2ms = (U1)CARSPDPLS_PLS_CHK_MIN;
        vd_s_CarSpdPls_LifPlsDataCal(u1_t_cal2ms);
    }
    /* 前回値更新 */
    u2_s_carspdpls_oldchcnt2ms = stRData.u2_cnt;

    /* 平均値算出用処理 */
    /* 平均値算出用データ取得タイミングになったら */
    if (st_sp_CARSPDPLS_TIMCNT[CARSPDPLS_TIM_CNT_AVE].u2_timmax <= u2_s_carspdpls_timcnt[CARSPDPLS_TIM_CNT_AVE]) {
        vd_s_CarSpdPls_AveDataChk();
    }
    
    /* データ送信処理 */
    /* データ送信タイミングになったら */
    if (st_sp_CARSPDPLS_TIMCNT[CARSPDPLS_TIM_CNT_SNDDAT].u2_timmax <= u2_s_carspdpls_timcnt[CARSPDPLS_TIM_CNT_SNDDAT]) {
        vd_s_CarSpdPls_SetData();
    }

    /* カウンタを動作 */
    for(u1_t_cnt = (U1)0U; u1_t_cnt < (U1)CARSPDPLS_TIM_CNT_NUM; u1_t_cnt++){
        vd_s_CarSpdPls_TimCntCtl(u1_t_cnt, (U1)CARSPDPLS_TIM_CNT);
    }
}

/*===================================================================================================================================*/
/*  static void    vd_s_CarSpdPls_SndDataCal(U2 u2_a_IPTPLSCNT, U1 u1_a_CAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_CarSpdPls_SndDataCal(U2 u2_a_IPTPLSCNT, U1 u1_a_CAL)
{
    U1 u1_t_cnt;
    U4 u4_t_caldat; /* 計算値一時格納 */
    

    u4_t_caldat = ((U4)u2_a_IPTPLSCNT + ((U4)u1_s_carspdpls_ovfcnt * (U4)0xFFFFU) + (U4)1);
    
    /* 進んだチャネルカウント分同じデータを取得する */
    for(u1_t_cnt = (U1)0U; u1_t_cnt < u1_a_CAL; u1_t_cnt++){
        /* オーバーフロー保護 */
        if(u1_s_carspdpls_plscnt<(U1)CARSPDPLS_PLS_CHK_MAX){
            u4_s_carspdpls_plsdata[u1_s_carspdpls_plscnt] = u4_t_caldat;
            u1_s_carspdpls_plscnt++;
        }
        else{
            break;
        }
    }
    u4_s_carspdpls_lastpls = u4_t_caldat;

    /* オーバーフローカウンタリセット */
    u1_s_carspdpls_ovfcnt = (U1)0x00U;
    /* 停車判定カウンタリセットリセット */
    vd_s_CarSpdPls_TimCntCtl((U1)CARSPDPLS_TIM_CNT_STP, (U1)CARSPDPLS_TIM_RST);
}

/*===================================================================================================================================*/
/*  static void    vd_s_CarSpdPls_LifPlsDataCal(U1 u1_a_CAL)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_CarSpdPls_LifPlsDataCal(U1 u1_a_CAL)
{
    u2_s_carspdpls_10mslifplsdat = (U2)(((U4)u2_s_carspdpls_10mslifplsdat + (U4)u1_a_CAL) & (U4)0xFFFFU);

    /* データ更新タイミングになったら */
    if(st_sp_CARSPDPLS_TIMCNT[CARSPDPLS_TIM_CNT_LIFDAT].u2_timmax <= u2_s_carspdpls_timcnt[CARSPDPLS_TIM_CNT_LIFDAT]){
        vd_g_XspiIviSub2PulseNumDataPut(u2_s_carspdpls_10mslifplsdat);
        u2_s_carspdpls_10mslifplsdat = (U2)0U;
        vd_s_CarSpdPls_TimCntCtl((U1)CARSPDPLS_TIM_CNT_LIFDAT, (U1)CARSPDPLS_TIM_RST);  /* データ更新タイマカウンタリセット */
    }
}

/*===================================================================================================================================*/
/*  static void    vd_s_CarSpdPls_StopChk(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_CarSpdPls_StopChk(void)
{
    /* 停車判定処理 */
    if(u1_s_carspdpls_plscnt < (U1)CARSPDPLS_PLS_CHK_MAX){
        /* 車速パルス未更新時間カウンタが判定値(375*4ms=1500ms)を超えたら */
        if(st_sp_CARSPDPLS_TIMCNT[CARSPDPLS_TIM_CNT_STP].u2_timmax <= u2_s_carspdpls_timcnt[CARSPDPLS_TIM_CNT_STP]){
            /* 最新保持値を0km/hの値で更新 */
            u4_s_carspdpls_lastpls = (U4)CARSPDPLS_PLS_STP_CYC;
        }
    }
}

/*===================================================================================================================================*/
/*  static void    vd_s_CarSpdPls_AveDataChk(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_CarSpdPls_AveDataChk(void)
{
    /* オーバーフロー保護 */
    if(u1_s_carspdpls_avefactnum < (U1)CARSPDPLS_AVE_FACT_MAX){
        /* 平均算出用パルスカウント取得 */
        /* 車速パルス0km/hの場合のみ、相当カウント数に置き換えて平均値を計算する */
        if(u4_s_carspdpls_lastpls == (U4)CARSPDPLS_PLS_STP_CYC){
            u4_s_carspdpls_aveplsdata[u1_s_carspdpls_avefactnum] = (U4)CARSPDPLS_PLS_STP_CNT;
        }
        else{
            u4_s_carspdpls_aveplsdata[u1_s_carspdpls_avefactnum] = u4_s_carspdpls_lastpls;
            u1_s_carspdpls_avechkflg = (U1)CARSPDPLS_AVE_CHK_ON;    /* 車速パルス平均値計算フラグをON */
        }
        u1_s_carspdpls_avefactnum++;
        if(u1_s_carspdpls_avefactnum >= (U1)CARSPDPLS_AVE_FACT_MAX){
            vd_s_CarSpdPls_Rcv_AveSendData();
        }
    }
    else{
        /* 制御上入ってこないはずだが、万が一入った場合に正常復帰するためにカウンタを初期化する */
        u1_s_carspdpls_avefactnum = (U1)0x00U;
    }
    
    vd_s_CarSpdPls_TimCntCtl((U1)CARSPDPLS_TIM_CNT_AVE, (U1)CARSPDPLS_TIM_RST);
}

/*===================================================================================================================================*/
/*  static void    vd_s_CarSpdPls_SetData(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_CarSpdPls_SetData(void)
{
    U1 u1_t_cnt;
    ST_XSPI_IVI_PULSE_WID_DATA st_t_data;
    
    vd_g_MemcpyU4(&st_t_data.u4_pulse_width[0],&u4_s_carspdpls_plsdata[0],(U4)CARSPDPLS_PLS_CHK_MAX);
    st_t_data.u1_clock_freq = (U1)CARSPDPLS_CNTCLK_FRQ;
	st_t_data.u4_pulse_count = (U4)u1_s_carspdpls_plscnt;
    
    vd_g_XspiIviSub2PulseWidDataPut(st_t_data);

    for(u1_t_cnt = (U1)0U; u1_t_cnt < (U1)CARSPDPLS_PLS_CHK_MAX; u1_t_cnt++){
        u4_s_carspdpls_plsdata[u1_t_cnt] = (U2)0x0000U;
    }
    u1_s_carspdpls_plscnt = (U1)0x00U;

    vd_s_CarSpdPls_TimCntCtl((U1)CARSPDPLS_TIM_CNT_SNDDAT, (U1)CARSPDPLS_TIM_RST);  /* データ送信タイマカウンタリセット */
}

/*===================================================================================================================================*/
/*  static void    vd_s_CarSpdPls_Rcv_AveSendData(void)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_CarSpdPls_Rcv_AveSendData(void)
{
    U1 u1_t_cnt;
    U4 u4_t_avenum;
    ST_XSPI_IVI_SP_CNT_DATA st_t_data;

    u4_t_avenum = (U4)0x00000000U;
    /* 車速パルス平均値計算フラグを確認 */
    /* 平均値算出用データが0km/hのみの場合は平均値として0x000000(0km/h)を */
    /* 送信する必要があるので、処理を分ける必要がある */
    if(u1_s_carspdpls_avechkflg == (U1)CARSPDPLS_AVE_CHK_ON){
        /* 平均値算出 */
        for(u1_t_cnt=(U1)0x00; u1_t_cnt < u1_s_carspdpls_avefactnum; u1_t_cnt++){
            u4_t_avenum = (U4)(((uint64)u4_t_avenum + (uint64)u4_s_carspdpls_aveplsdata[u1_t_cnt]) & (uint64)U4_MAX);
        }
        u4_t_avenum /= u1_s_carspdpls_avefactnum;
    }
    else{
        /* 取得データがすべて0km/hなので、0x000000を送信する */
        u4_t_avenum = (U4)CARSPDPLS_PLS_STP_CYC;
    }
    
    st_t_data.u1_clock_freq = (U1)CARSPDPLS_CNTCLK_FRQ;
    st_t_data.u4_sp_count   = u4_t_avenum;
    
    vd_g_XspiIviSub1SpCntPut(st_t_data);                /* データ送信処理 */

    u1_s_carspdpls_avefactnum = (U1)0x00U;              /* 平均算出用要素数リセット */
    u1_s_carspdpls_avechkflg = (U1)CARSPDPLS_AVE_CHK_OFF;   /* 車速パルス平均値計算フラグをOFF */
    /* データ送信後に格納配列初期化 */
    for(u1_t_cnt = (U1)0U; u1_t_cnt < (U1)CARSPDPLS_AVE_FACT_MAX; u1_t_cnt++){
        u4_s_carspdpls_aveplsdata[u1_t_cnt] = (U2)0x0000U;
    }
}

/*===================================================================================================================================*/
/*  static void    vd_s_CarSpdPls_TimCntCtl(U1 u1_a_TIMECNTID, U1 u1_a_KIND)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_CarSpdPls_TimCntCtl(U1 u1_a_TIMECNTID, U1 u1_a_KIND)
{
    /* 操作種別がカウントなら */
    if(u1_a_KIND == (U1)CARSPDPLS_TIM_CNT){
        /* カウント種別がUPカウントなら */
        if(st_sp_CARSPDPLS_TIMCNT[u1_a_TIMECNTID].u1_updwn == (U1)CARSPDPLS_UP_CNT){
            /* 最大値を超えていなければ */
            if(u2_s_carspdpls_timcnt[u1_a_TIMECNTID] < st_sp_CARSPDPLS_TIMCNT[u1_a_TIMECNTID].u2_timmax){
                u2_s_carspdpls_timcnt[u1_a_TIMECNTID]++;
            }
        /* カウント種別がDOWNカウントなら */
        }
        else{
            /* 0でなければ */
            if(u2_s_carspdpls_timcnt[u1_a_TIMECNTID] > (U2)0x0000U){
                u2_s_carspdpls_timcnt[u1_a_TIMECNTID]--;
            }
        }
    /* 操作種別がリセットなら */
    }
    else{
        /* カウント種別がUPカウントなら */
        if(st_sp_CARSPDPLS_TIMCNT[u1_a_TIMECNTID].u1_updwn == (U1)CARSPDPLS_UP_CNT){
            u2_s_carspdpls_timcnt[u1_a_TIMECNTID] =(U2)0x0000U;
        /* カウント種別がDOWNカウントなら */
        }
        else{
            u2_s_carspdpls_timcnt[u1_a_TIMECNTID] = st_sp_CARSPDPLS_TIMCNT[u1_a_TIMECNTID].u2_timmax;
        }
    }
}

/*===================================================================================================================================*/
/*  U2     u2_g_CarSpdPls_LastPlsGet(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2     u2_g_CarSpdPls_LastPlsGet(void)
{
    return(u4_s_carspdpls_lastpls);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  0.0.0    02/07/2025  TN       New.                                                                                               */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*  * TN   = Tatsuya Niimi, KSE                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/
