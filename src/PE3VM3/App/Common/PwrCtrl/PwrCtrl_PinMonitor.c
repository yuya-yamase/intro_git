/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  PWRCTRL PINMONITOR                                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "PwrCtrl_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* 車両信号ポーリング状態定義 */
#define PWRCTRL_PINMONITOR_STS_STOP                (0x00U)    /* ポーリング停止中 */
#define PWRCTRL_PINMONITOR_POLL_STS_CYC            (0x01U)    /* ポーリング定期 */

/* 同一論理取得回数カウント処理 */
#define PWRCTRL_PINMONITOR_SAME_CNT_INI            (0x01U)    /* 同一論理取得カウンタ初期値 */
#define PWRCTRL_PINMONITOR_PORT_LEVEL_INIT         (0xFFU)    /* DIOレベル初期値 */
#define PWRCTRL_PINMONITOR_TMNL_STS_NON            (0xFFU)    /* 端子状態_不定値 */

/* 時間計測用 */
#define PWRCTRL_PINMONITOR_SAMPLING_TASK_5ms       (0U)       /* 監視周期(5ms) */
#define PWRCTRL_PINMONITOR_SAMPLING_TASK_10ms      (1U)       /* 監視周期(10ms) */
#define PWRCTRL_PINMONITOR_SAMPLING_CNT_INI        (0U)       /* ポーリングタイマカウンタ初期値 */
#define PWRCTRL_PINMONITOR_TRIGGER_TIME_CMPLT      (0U)       /* ポーリング開始待ち時間満了 */

/* ループカウンタ初期値 */
#define PWRCTRL_PINMONITOR_INITVAL                 (0U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* 外部信号ステータステーブル */
typedef struct{
    Dio_ChannelType u2_DioChannelId;                     /* DIOチャネルID */
    U1              u1_CycTim;                           /* 定周期時間 */
    U1              u1_SameCntNum;                       /* 同一論理判定確定回数 */
    U1              u1_StrTim;                           /* ポーリング開始待ち時間 */
    U1              (* fp_u1_ObserveStartInfo)(void);    /* 監視開始条件 */
} ST_PWRCTRL_PINMONITOR_STS;

/* ポーリングステータス */
typedef struct {
    Dio_LevelType   u1_PollTmnlPreCnc;      /* ポーリング端子前回レベル */
    U1              u1_PollSts;             /* ポーリング状態 */
    U1              u1_PollTimCnt;          /* ポーリングタイマカウンタ */
    U1              u1_PollTmnlSts;         /* ポーリング端子状態 */
    U1              u1_PollSameCnt;         /* ポーリング端子同一状態カウンタ */
    U1              u1_PollTrgTimCnt;       /* ポーリング開始トリガタイマカウンタ */
} ST_PWRCTRL_PINMONITOR_POLL_STS;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static ST_PWRCTRL_PINMONITOR_POLL_STS st_PwrCtrl_PinMonitor_PollSts[PWRCTRL_CFG_PRIVATE_KIND_NUM];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void vd_s_PwrCtrlPinMonitorTrgTimCtrl(const U1 u1_a_Kind);
static void vd_s_PwrCtrlPinMonitorPoll(const U1 u1_a_Kind);
static void vd_s_PwrCtrlPinMonitorCyc(const U1 u1_a_Kind);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_PWRCTRL_PINMONITOR_STS st_PwrCtrl_PinMonitor_Sts[PWRCTRL_CFG_PRIVATE_KIND_NUM]
= {
    /* AOSS_SLP_ENTRY_EXIT */
    {
        (U2)DIO_ID_PORT17_CH0,                                             /* DIOチャネルID */
        (U1)PWRCTRL_PINMONITOR_SAMPLING_TASK_5ms,                          /* サンプリング周期 */
        (U1)PWRCTRL_CFG_PRIVATE_AOSS_SLEEP_ENTRY_EXIT_JUDGECOUNT,          /* 同一論理判定確定回数 */
        (U1)PWRCTRL_CFG_PRIVATE_AOSS_SLEEP_ENTRY_EXIT_WAITTIME,            /* ポーリング開始待ち時間 */
        u1_g_PwrCtrlWakeUpInfo,                                            /* MCU初期化処理、またはウェイクアップ処理完了状態判定 */
    },
    /* POFF_COMPLETE_N */
    {
        (U2)DIO_ID_PORT8_CH6,                                              /* DIOチャネルID */
        (U1)PWRCTRL_PINMONITOR_SAMPLING_TASK_5ms,                          /* サンプリング周期 */
        (U1)PWRCTRL_CFG_PRIVATE_POFF_COMPLETE_N_JUDGECOUNT,                /* 同一論理判定確定回数 */
        (U1)PWRCTRL_CFG_PRIVATE_POFF_COMPLETE_N_WAITTIME,                  /* ポーリング開始待ち時間 */
        u1_g_PwrCtrlSipLowPowerOnInfo,                                     /* LowPowerOn状態判定 */
    },
    /* PMA_PS_HOLD */
    {
        (U2)DIO_ID_PORT3_CH1,                                              /* DIOチャネルID */
        (U1)PWRCTRL_PINMONITOR_SAMPLING_TASK_5ms,                          /* サンプリング周期 */
        (U1)PWRCTRL_CFG_PRIVATE_PMA_PS_HOLD_JUDGECOUNT,                    /* 同一論理判定確定回数 */
        (U1)PWRCTRL_CFG_PRIVATE_PMA_PS_HOLD_WAITTIME,                      /* ポーリング開始待ち時間 */
        u1_g_PwrCtrlSipLowPowerOnInfo,                                     /* LowPowerOn状態判定 */
    },
    /* SOC_RESOUT_N */
    {
        (U2)DIO_ID_PORT8_CH3,                                              /* DIOチャネルID */
        (U1)PWRCTRL_PINMONITOR_SAMPLING_TASK_5ms,                          /* サンプリング周期 */
        (U1)PWRCTRL_CFG_PRIVATE_SOC_RESOUT_N_JUDGECOUNT,                   /* 同一論理判定確定回数 */
        (U1)PWRCTRL_CFG_PRIVATE_SOC_RESOUT_N_WAITTIME,                     /* ポーリング開始待ち時間 */
        u1_g_PwrCtrlSipLowPowerOnInfo,                                     /* LowPowerOn状態判定 */
    },
    /* SAIL_RESOUT_N */
    {
        (U2)DIO_ID_PORT8_CH8,                                              /* DIOチャネルID */
        (U1)PWRCTRL_PINMONITOR_SAMPLING_TASK_5ms,                          /* サンプリング周期 */
        (U1)PWRCTRL_CFG_PRIVATE_SAIL_RESOUT_N_JUDGECOUNT,                  /* 同一論理判定確定回数 */
        (U1)PWRCTRL_CFG_PRIVATE_SAIL_RESOUT_N_WAITTIME,                    /* ポーリング開始待ち時間 */
        u1_g_PwrCtrlSipLowPowerOnInfo,                                     /* LowPowerOn状態判定 */
    },
    /* MM_STBY_N */
    {
        (U2)DIO_ID_PORT10_CH11,                                            /* DIOチャネルID */
        (U1)PWRCTRL_PINMONITOR_SAMPLING_TASK_5ms,                          /* サンプリング周期 */
        (U1)PWRCTRL_CFG_PRIVATE_MM_STBY_N_JUDGECOUNT,                      /* 同一論理判定確定回数 */
        (U1)PWRCTRL_CFG_PRIVATE_MM_STBY_N_WAITTIME,                        /* ポーリング開始待ち時間 */
        u1_g_PwrCtrlSipLowPowerOnInfo,                                     /* LowPowerOn状態判定 */
    },
    /* BOOT */
    {
        (U2)DIO_ID_PORT0_CH2,                                              /* DIOチャネルID */
        (U1)PWRCTRL_PINMONITOR_SAMPLING_TASK_5ms,                          /* サンプリング周期 */
        (U1)PWRCTRL_CFG_PRIVATE_BOOT_JUDGECOUNT,                           /* 同一論理判定確定回数 */
        (U1)PWRCTRL_CFG_PRIVATE_BOOT_WAITTIME,                             /* ポーリング開始待ち時間 */
        u1_g_PwrCtrlWakeUpInfo,                                            /* MCU初期化処理、またはウェイクアップ処理完了状態判定 */
    },
    /* BU_DET */
    {
        (U2)DIO_ID_PORT0_CH4,                                              /* DIOチャネルID */
        (U1)PWRCTRL_PINMONITOR_SAMPLING_TASK_5ms,                          /* サンプリング周期 */
        (U1)PWRCTRL_CFG_PRIVATE_BU_DET_JUDGECOUNT,                         /* 同一論理判定確定回数 */
        (U1)PWRCTRL_CFG_PRIVATE_BU_DET_WAITTIME,                           /* ポーリング開始待ち時間 */
        u1_g_PwrCtrlWakeUpInfo,                                            /* MCU初期化処理、またはウェイクアップ処理完了状態判定 */
    },
    /* DBG_FAIL_OFF */
    {
        (U2)DIO_ID_PORT20_CH7,                                             /* DIOチャネルID */
        (U1)PWRCTRL_PINMONITOR_SAMPLING_TASK_10ms,                         /* サンプリング周期 */
        (U1)PWRCTRL_CFG_PRIVATE_DBG_FAIL_OFF_JUDGECOUNT,                   /* 同一論理判定確定回数 */
        (U1)PWRCTRL_CFG_PRIVATE_DBG_FAIL_OFF_WAITTIME,                     /* ポーリング開始待ち時間 */
        u1_g_PwrCtrlWakeUpInfo,                                            /* MCU初期化処理、またはウェイクアップ処理完了状態判定 */
    },
    /* SAIL-ERR1 */
    {
        (U2)DIO_ID_PORT6_CH2,                                              /* DIOチャネルID */
        (U1)PWRCTRL_PINMONITOR_SAMPLING_TASK_5ms,                          /* サンプリング周期 */
        (U1)PWRCTRL_CFG_PRIVATE_SAIL_ERR1_JUDGECOUNT,                      /* 同一論理判定確定回数 */
        (U1)PWRCTRL_CFG_PRIVATE_SAIL_ERR1_WAITTIME,                        /* ポーリング開始待ち時間 */
        u1_g_PwrCtrlSipLowPowerOnInfo,                                     /* LowPowerOn状態判定 */
    },
    /* SAIL-ERR2 */
    {
        (U2)DIO_ID_PORT6_CH4,                                              /* DIOチャネルID */
        (U1)PWRCTRL_PINMONITOR_SAMPLING_TASK_5ms,                          /* サンプリング周期 */
        (U1)PWRCTRL_CFG_PRIVATE_SAIL_ERR2_JUDGECOUNT,                      /* 同一論理判定確定回数 */
        (U1)PWRCTRL_CFG_PRIVATE_SAIL_ERR2_WAITTIME,                        /* ポーリング開始待ち時間 */
        u1_g_PwrCtrlSipLowPowerOnInfo,                                     /* LowPowerOn状態判定 */
    },
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/**************************************************************************************************************************************
  Function      : u1_g_PwrCtrl_PinMonitor_GetPinInfo
  Description   : 端子情報の判定結果通知処理
  param[in/out] : [in ] const U1 u1_a_PinID PINの種類
  return        : U1 u1_t_ret PINの端子状態判定結果
  Note          : none
**************************************************************************************************************************************/
U1 u1_g_PwrCtrl_PinMonitor_GetPinInfo(const U1 u1_a_PinID)
{
    U1 u1_t_ret;

    if ((u1_a_PinID < (U1)PWRCTRL_CFG_PRIVATE_KIND_NUM) &&
        ((st_PwrCtrl_PinMonitor_PollSts[u1_a_PinID].u1_PollTmnlSts == (U1)STD_HIGH) ||
         (st_PwrCtrl_PinMonitor_PollSts[u1_a_PinID].u1_PollTmnlSts == (U1)STD_LOW) ||
         (st_PwrCtrl_PinMonitor_PollSts[u1_a_PinID].u1_PollTmnlSts == (U1)PWRCTRL_PINMONITOR_TMNL_STS_NON))) {
            u1_t_ret = st_PwrCtrl_PinMonitor_PollSts[u1_a_PinID].u1_PollTmnlSts;
    } else {
        u1_t_ret = (U1)PWRCTRL_PINMONITOR_TMNL_STS_NON;
    }

    return(u1_t_ret);

}

/**************************************************************************************************************************************
  Function      : vd_g_PwrCtrlPinMonitorInit
  Description   : 7-1.内部端子モニタ制御の初期化処理
  param[in/out] : none
  return        : none
  Note          : none
**************************************************************************************************************************************/
void vd_g_PwrCtrlPinMonitorInit(void)
{
    U1 u1_t_Kind;

    for (u1_t_Kind = (U1)PWRCTRL_PINMONITOR_INITVAL; u1_t_Kind < (U1)PWRCTRL_CFG_PRIVATE_KIND_NUM; u1_t_Kind++) {
        st_PwrCtrl_PinMonitor_PollSts[u1_t_Kind].u1_PollTmnlPreCnc = (U1)PWRCTRL_PINMONITOR_PORT_LEVEL_INIT;
        st_PwrCtrl_PinMonitor_PollSts[u1_t_Kind].u1_PollSts = (U1)PWRCTRL_PINMONITOR_STS_STOP;
        st_PwrCtrl_PinMonitor_PollSts[u1_t_Kind].u1_PollTimCnt = (U1)PWRCTRL_PINMONITOR_SAMPLING_CNT_INI;
        st_PwrCtrl_PinMonitor_PollSts[u1_t_Kind].u1_PollTmnlSts = (U1)PWRCTRL_PINMONITOR_TMNL_STS_NON;
        st_PwrCtrl_PinMonitor_PollSts[u1_t_Kind].u1_PollSameCnt = (U1)PWRCTRL_PINMONITOR_SAME_CNT_INI;
        st_PwrCtrl_PinMonitor_PollSts[u1_t_Kind].u1_PollTrgTimCnt = st_PwrCtrl_PinMonitor_Sts[u1_t_Kind].u1_StrTim;
    }

    return;
}

/**************************************************************************************************************************************
  Function      : vd_g_PwrCtrlPinMonitorMainFunc
  Description   : 7-1.内部端子モニタ制御の定期処理
  param[in/out] : none
  return        : none
  Note          : none
**************************************************************************************************************************************/
void vd_g_PwrCtrlPinMonitorMainFunc(void)
{
    U1 u1_t_Kind;
    U1 u1_t_ObserveStart;
    
    for (u1_t_Kind = (U1)PWRCTRL_PINMONITOR_INITVAL; u1_t_Kind < (U1)PWRCTRL_CFG_PRIVATE_KIND_NUM; u1_t_Kind++) {
        u1_t_ObserveStart = (*(st_PwrCtrl_PinMonitor_Sts[u1_t_Kind].fp_u1_ObserveStartInfo))();
            if (u1_t_ObserveStart == (U1)TRUE) {
                /* Wait時間計測  */
                vd_s_PwrCtrlPinMonitorTrgTimCtrl(u1_t_Kind);
                    if (st_PwrCtrl_PinMonitor_PollSts[u1_t_Kind].u1_PollSts == (U1)PWRCTRL_PINMONITOR_POLL_STS_CYC) {
                        /* ポーリング処理 */
                        vd_s_PwrCtrlPinMonitorPoll(u1_t_Kind);
                    } else {
                        /* Wait時間経過待ち */
                        st_PwrCtrl_PinMonitor_PollSts[u1_t_Kind].u1_PollSameCnt = (U1)PWRCTRL_PINMONITOR_SAME_CNT_INI;
                    }
            } else {
                st_PwrCtrl_PinMonitor_PollSts[u1_t_Kind].u1_PollTmnlPreCnc = (U1)PWRCTRL_PINMONITOR_PORT_LEVEL_INIT;
                st_PwrCtrl_PinMonitor_PollSts[u1_t_Kind].u1_PollSts = (U1)PWRCTRL_PINMONITOR_STS_STOP;
                st_PwrCtrl_PinMonitor_PollSts[u1_t_Kind].u1_PollTimCnt = (U1)PWRCTRL_PINMONITOR_SAMPLING_CNT_INI;
                st_PwrCtrl_PinMonitor_PollSts[u1_t_Kind].u1_PollTmnlSts = (U1)PWRCTRL_PINMONITOR_TMNL_STS_NON;
                st_PwrCtrl_PinMonitor_PollSts[u1_t_Kind].u1_PollSameCnt = (U1)PWRCTRL_PINMONITOR_SAME_CNT_INI;
                st_PwrCtrl_PinMonitor_PollSts[u1_t_Kind].u1_PollTrgTimCnt = (U1)st_PwrCtrl_PinMonitor_Sts[u1_t_Kind].u1_StrTim;
            }
    }

    return;
}

/**************************************************************************************************************************************
  Function      : vd_s_PwrCtrlPinMonitorTrgTimCtrl
  Description   : 7-1.内部端子モニタ制御 監視開始時のtWAIT待ち処理
  param[in/out] : [in ] const U1 u1_a_Kind PINの種類
  return        : none
  Note          : none
**************************************************************************************************************************************/
static void vd_s_PwrCtrlPinMonitorTrgTimCtrl(const U1 u1_a_Kind)
{
        if (st_PwrCtrl_PinMonitor_PollSts[u1_a_Kind].u1_PollTrgTimCnt <= (U1)PWRCTRL_PINMONITOR_TRIGGER_TIME_CMPLT) {
            st_PwrCtrl_PinMonitor_PollSts[u1_a_Kind].u1_PollSts = (U1)PWRCTRL_PINMONITOR_POLL_STS_CYC;
        } else {
            st_PwrCtrl_PinMonitor_PollSts[u1_a_Kind].u1_PollTrgTimCnt--;
        }

        return;
}

/**************************************************************************************************************************************
  Function      : vd_s_PwrCtrlPinMonitorPoll
  Description   : 7-1.内部端子モニタ制御 ポーリング周期計測処理
  param[in/out] : [in ] const U1 u1_a_Kind PINの種類
  return        : none
  Note          : none
**************************************************************************************************************************************/
static void vd_s_PwrCtrlPinMonitorPoll(const U1 u1_a_Kind)
{
        if (st_PwrCtrl_PinMonitor_PollSts[u1_a_Kind].u1_PollTimCnt <= (U1)PWRCTRL_PINMONITOR_SAMPLING_CNT_INI) {
                vd_s_PwrCtrlPinMonitorCyc(u1_a_Kind);
                st_PwrCtrl_PinMonitor_PollSts[u1_a_Kind].u1_PollTimCnt = st_PwrCtrl_PinMonitor_Sts[u1_a_Kind].u1_CycTim;
        } else {
                st_PwrCtrl_PinMonitor_PollSts[u1_a_Kind].u1_PollTimCnt--;
        }

        return;
}

/**************************************************************************************************************************************
  Function      : vd_s_PwrCtrlPinMonitorCyc
  Description   : 7-1.内部端子モニタ制御 PIN状態判定処理
  param[in/out] : [in ] const U1 u1_a_Kind PINの種類
  return        : none
  Note          : none
**************************************************************************************************************************************/
static void vd_s_PwrCtrlPinMonitorCyc(const U1 u1_a_Kind)
{
        Dio_LevelType u1_t_NowCnc;

        u1_t_NowCnc = Dio_ReadChannel(st_PwrCtrl_PinMonitor_Sts[u1_a_Kind].u2_DioChannelId);

        if (u1_t_NowCnc == st_PwrCtrl_PinMonitor_PollSts[u1_a_Kind].u1_PollTmnlPreCnc) {
                if (st_PwrCtrl_PinMonitor_PollSts[u1_a_Kind].u1_PollSameCnt < st_PwrCtrl_PinMonitor_Sts[u1_a_Kind].u1_SameCntNum) {
                        st_PwrCtrl_PinMonitor_PollSts[u1_a_Kind].u1_PollSameCnt++;
                }
        } else {
                st_PwrCtrl_PinMonitor_PollSts[u1_a_Kind].u1_PollSameCnt = (U1)PWRCTRL_PINMONITOR_SAME_CNT_INI;
        }

        if (st_PwrCtrl_PinMonitor_PollSts[u1_a_Kind].u1_PollSameCnt >= st_PwrCtrl_PinMonitor_Sts[u1_a_Kind].u1_SameCntNum) {
                st_PwrCtrl_PinMonitor_PollSts[u1_a_Kind].u1_PollTmnlSts = u1_t_NowCnc;
        }

        st_PwrCtrl_PinMonitor_PollSts[u1_a_Kind].u1_PollTmnlPreCnc = u1_t_NowCnc;

        return;

}

/**** End of File ********************************************************************************************************************/
