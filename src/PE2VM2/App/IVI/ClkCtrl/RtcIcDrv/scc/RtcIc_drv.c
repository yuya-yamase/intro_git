/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Rtc Ic (Epson RA8900) Driver                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RTCIC_DRV_C_MAJOR                        (1U)
#define RTCIC_DRV_C_MINOR                        (0U)
#define RTCIC_DRV_C_PATCH                        (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "RtcIc_drv_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((RTCIC_DRV_C_MAJOR != RTCIC_DRV_H_MAJOR) || \
     (RTCIC_DRV_C_MINOR != RTCIC_DRV_H_MINOR) || \
     (RTCIC_DRV_C_PATCH != RTCIC_DRV_H_PATCH))
#error "RtcIc_drv.c and RtcIc_drv.h : source and header files are inconsistent!"
#endif

#if ((RTCIC_DRV_C_MAJOR != RTCIC_DRV_CFG_H_MAJOR) || \
     (RTCIC_DRV_C_MINOR != RTCIC_DRV_CFG_H_MINOR) || \
     (RTCIC_DRV_C_PATCH != RTCIC_DRV_CFG_H_PATCH))
#error "RtcIc_drv.c and RtcIc_drv_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RTCIC_DRV_INITIAL_REQ_ON                 (1U)
#define RTCIC_DRV_DAYSET_REQ_ON                  (2U)
#define RTCIC_DRV_INITIAL_REQ_OFF                (0U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RTCIC_DRV_TIMEOUT                        (1U)
#define RTCIC_DRV_TIMEWAIT                       (0U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RTCIC_DRV_PHASE_INITWAIT                 (0U)
#define RTCIC_DRV_PHASE_VLFBIT_CHECK             (1U)
#define RTCIC_DRV_PHASE_RTCLK_START              (2U)
#define RTCIC_DRV_PHASE_RTCLK_DAYSET             (3U)
#define RTCIC_DRV_PHASE_RTCLK_READ               (4U)
#define RTCIC_DRV_PHASE_RTCLK_READWAIT           (5U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RTCIC_DRV_STATE_NORMAL                   (0U)
#define RTCIC_DRV_STATE_ABNORMAL                 (1U)
#define RTCIC_DRV_STATE_EXECUTION                (2U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RTCIC_DRV_DAT_SEC_REGISTA                (0x00U)                        /* 00秒                                              */
#define RTCIC_DRV_DAT_MIN_REGISTA                (0x00U)                        /* 00分                                              */
#define RTCIC_DRV_DAT_HOUR_REGISTA               (0x00U)                        /* 00時                                              */

#define RTCIC_DRV_FLAG_REGISTA_VLF               (0x02U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RTCIC_DRV_COMNO_NON                      (0U)                           /* 要求なし                                          */
#define RTCIC_DRV_COMNO_CLK_SET                  (1U)                           /* 時計IC 設定                                       */
#define RTCIC_DRV_COMNO_DAY_SET                  (2U)                           /* カレンダ 設定                                     */
#define RTCIC_DRV_COMNO_VLFBIT_READ              (3U)                           /* VLF bit 読み出し                                  */
#define RTCIC_DRV_COMNO_CLK_READ                 (4U)                           /* 時刻 読み出し                                     */
#define RTCIC_DRV_COMNO_CONTREG_READ             (5U)                           /* 制御レジスタ読み出し                              */
#define RTCIC_DRV_COMNO_BACKUP_READ              (6U)                           /* バックアップ設定読み出し                          */
#define RTCIC_DRV_COMNO_RAM_READ                 (7U)                           /* RAM領域読み出し                                   */
#define RTCIC_DRV_COMNO_VFLBIT_SET               (8U)                           /* VLF bit クリア                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RTCIC_DRV_SUBPHASE_GRPCLK                (0x10U)
#define RTCIC_DRV_SUBPHASE_CLKWRITE              (0x10U)
#define RTCIC_DRV_SUBPHASE_CLK                   (0x11U)
#define RTCIC_DRV_SUBPHASE_CONTREG               (0x12U)
#define RTCIC_DRV_SUBPHASE_BACKUP                (0x13U)
#define RTCIC_DRV_SUBPHASE_RAM                   (0x14U)
#define RTCIC_DRV_SUBPHASE_VLFCLS                (0x15U)

#define RTCIC_DRV_SUBPHASE_GRPDAY                (0x20U)
#define RTCIC_DRV_SUBPHASE_DAYWRITE              (0x20U)
#define RTCIC_DRV_SUBPHASE_READ                  (0x21U)

#define RTCIC_DRV_SUBPHASE_GRPREAD               (0x30U)
#define RTCIC_DRV_SUBPHASE_READ_FIRST            (0x30U)
#define RTCIC_DRV_SUBPHASE_READ_SECOND           (0x31U)

#define RTCIC_DRV_SUBPHASE_END                   (0xFFU)
#define RTCIC_DRV_SUBPHASE_GRPMASK               (0xF0U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RTCIC_DRV_TIME_NOREAD                    (0U)
#define RTCIC_DRV_TIME_READ                      (1U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RTCIC_I2C_STATE_STOP                     (0U)
#define RTCIC_I2C_STATE_EXECUTION                (1U)
#define RTCIC_I2C_STATE_NORMAL                   (2U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RTCIC_DEV_IC_NONINITIAL                  (0U)
#define RTCIC_DEV_IC_NORMAL                      (1U)
#define RTCIC_DEV_IC_I2C_ERROR                   (2U)
#define RTCIC_DEV_IC_RESET                       (3U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RTCIC_OFFSET_2000DAYCUNT                 (730485U)                              /* [days] Jan-1st-2000  */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MCU_SYS_COUNTTIME_FIN                    (0xFFFFFFFFU)
#define MCU_WRINUM_RTCIC_TIME_SET                (1U)
#define MCU_WRINUM_RTCIC_DAY_SET                 (1U)
#define MCU_WRINUM_RTCIC_VLF_SET                 (1U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RTCIC_DRV_BASE_CYCLE                     (10U)
#define RTCIC_DRV_INITIALWAIT_TIME               (3500U/RTCIC_DRV_BASE_CYCLE)
#define RTCIC_DRV_READCYCLE_TIME                 (500U/RTCIC_DRV_BASE_CYCLE)
#define RTCIC_DRV_IC2ERROR_TIME                  (2000U/RTCIC_DRV_BASE_CYCLE)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_rtcic_drv_real_time            __attribute__((section(".bss_BACK")));
static U4      u4_s_rtcic_drv_daycnt               __attribute__((section(".bss_BACK")));
static U1      u1_s_rtcic_drv_state                __attribute__((section(".bss_BACK")));

/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U2      u2_s_rtcic_drv_initial_wait;
static U1      u1_s_rtcic_drv_cycle_time;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1      u1_s_rtcic_drv_rt_set_req;
static U1      u1_s_rtcic_drv_rt_set_req_day;
static U1      u1_s_rtcic_drv_rt_set_req_exc;
static U1      u1_s_rtcic_drv_proc_phase;
static U1      u1_s_rtcic_drv_proc_subphase;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1      u1_s_rtcic_drv_time_read;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1      u1_s_rtcic_drv_i2c_comstate;
static U1      u1_s_rtcic_drv_i2c_type;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1      u1_s_rtcic_drv_i2c_timeout;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1      u1_s_rtcic_drv_vlfbit_bfr;
static U4      u4_s_rtcic_drv_real_time_bfr;
static U4      u4_s_rtcic_drv_daycnt_bfr;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static uint16  Mcu_RegStep_RtcIc;               /* RTC-IC レジスタ書込み位置指定 */
static uint32  Mcu_OnStep_RtcIc_AckTime;        /* PTC-IC 書込み/読込みから応答までの時間計測 */

/* レジスタアクセス */
static uint16  Mcu_RegSet_BetWaitTime_Stub;     /* レジスタアクセス間Waitタイマ スタブ */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1      u1_s_RtcIc_InitialWait(void);
static U1      u1_s_RtcIc_VlfbitCheck(void);
static U1      u1_s_RtcIc_RtclkStart(void);
static U1      u1_s_RtcIc_RtclkDayset(void);
static U1      u1_s_RtcIc_RtclkRead(void);
static U1      u1_s_RtcIc_RtclkReadWait(void);

static void    vd_s_RtcIc_I2cComControl(void);
static void    vd_s_RtcIc_I2cErrCheck(void);
static U1      u1_s_RtcIc_I2cStateCheck(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_REG_WRI_REQ RTCIC_TIME_SET[MCU_WRINUM_RTCIC_TIME_SET] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        (U2)0U,         (U2)4U,         (U2)0U}
};
static const ST_REG_WRI_REQ RTCIC_DAY_SET[MCU_WRINUM_RTCIC_DAY_SET] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        (U2)0U,         (U2)1U,         (U2)0U}
};
static const ST_REG_WRI_REQ RTCIC_VLF_SET[MCU_WRINUM_RTCIC_VLF_SET] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        (U2)0U,         (U2)1U,         (U2)0U}
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_RtcIcBonInit(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_RtcIcBonInit(void)
{
    u4_s_rtcic_drv_real_time      = (U4)((RTCIC_DRV_DAT_HOUR_REGISTA << RTCLK_HHMMSS_LSB_HR) |
                                         (RTCIC_DRV_DAT_MIN_REGISTA << RTCLK_HHMMSS_LSB_MI) |
                                         RTCIC_DRV_DAT_SEC_REGISTA);
    u4_s_rtcic_drv_daycnt         = (U4)RTCIC_OFFSET_2000DAYCUNT;

    u2_s_rtcic_drv_initial_wait   = (U2)0U;
    u1_s_rtcic_drv_cycle_time     = (U1)0U;

    u1_s_rtcic_drv_i2c_comstate   = (U1)RTCIC_I2C_STATE_STOP;
    u1_s_rtcic_drv_i2c_type       = (U1)RTCIC_DRV_COMNO_NON;
    u1_s_rtcic_drv_i2c_timeout    = (U1)0U;

    u1_s_rtcic_drv_proc_phase     = (U1)RTCIC_DRV_PHASE_VLFBIT_CHECK;
    u1_s_rtcic_drv_proc_subphase  = (U1)RTCIC_DRV_SUBPHASE_END;
    u1_s_rtcic_drv_rt_set_req     = (U1)RTCIC_DRV_INITIAL_REQ_ON;
    u1_s_rtcic_drv_rt_set_req_day = (U1)RTCIC_DRV_INITIAL_REQ_OFF;
    u1_s_rtcic_drv_rt_set_req_exc = (U1)RTCIC_DRV_INITIAL_REQ_OFF;
    u1_s_rtcic_drv_state          = (U1)RTCIC_DEV_IC_NONINITIAL;
    u1_s_rtcic_drv_time_read      = (U1)RTCIC_DRV_TIME_NOREAD;

    u1_s_rtcic_drv_vlfbit_bfr     = (U1)U1_MAX;
    u4_s_rtcic_drv_real_time_bfr  = (U4)0U;
    u4_s_rtcic_drv_daycnt_bfr     = (U4)0U;

    Mcu_RegStep_RtcIc             = (uint16)0U;
    Mcu_OnStep_RtcIc_AckTime      = (uint32)0U;
    Mcu_RegSet_BetWaitTime_Stub   = (uint16)0xFFFFU;
}
/*===================================================================================================================================*/
/*  void    vd_g_RtcIcRstwkInit(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_RtcIcRstwkInit(void)
{
    u2_s_rtcic_drv_initial_wait   = (U2)0U;
    u1_s_rtcic_drv_cycle_time     = (U1)0U;

    u1_s_rtcic_drv_i2c_comstate   = (U1)RTCIC_I2C_STATE_STOP;
    u1_s_rtcic_drv_i2c_type       = (U1)RTCIC_DRV_COMNO_NON;
    u1_s_rtcic_drv_i2c_timeout    = (U1)0U;

    u1_s_rtcic_drv_proc_phase     = (U1)RTCIC_DRV_PHASE_VLFBIT_CHECK;
    u1_s_rtcic_drv_proc_subphase  = (U1)RTCIC_DRV_SUBPHASE_END;
    if (u1_s_rtcic_drv_state != (U1)RTCIC_DEV_IC_NONINITIAL) {
        u1_s_rtcic_drv_state      = (U1)RTCIC_DEV_IC_NORMAL;
        u1_s_rtcic_drv_rt_set_req = (U1)RTCIC_DRV_INITIAL_REQ_OFF;
    }
    else {
        u1_s_rtcic_drv_rt_set_req = (U1)RTCIC_DRV_INITIAL_REQ_ON;
    }
    u1_s_rtcic_drv_rt_set_req_day = (U1)RTCIC_DRV_INITIAL_REQ_OFF;
    u1_s_rtcic_drv_rt_set_req_exc = (U1)RTCIC_DRV_INITIAL_REQ_OFF;
    u1_s_rtcic_drv_time_read      = (U1)RTCIC_DRV_TIME_NOREAD;

    u1_s_rtcic_drv_vlfbit_bfr     = (U1)U1_MAX;
    u4_s_rtcic_drv_real_time_bfr  = (U4)0U;
    u4_s_rtcic_drv_daycnt_bfr     = (U4)0U;

    Mcu_RegStep_RtcIc             = (uint16)0U;
    Mcu_OnStep_RtcIc_AckTime      = (uint32)0U;
    Mcu_RegSet_BetWaitTime_Stub   = (uint16)0xFFFFU;
}
/*===================================================================================================================================*/
/*  void    vd_g_RtcIc_MainTask(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_RtcIc_MainTask(void)
{
    U1                 u1_t_initwait;
    U1                 u1_t_state;
    U1                 u1_t_grp;

    u1_t_state = (U1)0U;

    vd_s_RtcIc_I2cComControl();
    vd_s_RtcIc_I2cErrCheck();

    u1_t_initwait = u1_s_RtcIc_InitialWait();

    if (u1_t_initwait == (U1)RTCIC_DRV_TIMEOUT) {
        switch (u1_s_rtcic_drv_proc_phase) {
            case RTCIC_DRV_PHASE_INITWAIT:
                u1_s_rtcic_drv_proc_phase = (U1)RTCIC_DRV_PHASE_RTCLK_START;
                break;

            case RTCIC_DRV_PHASE_VLFBIT_CHECK:
                u1_t_state = u1_s_RtcIc_VlfbitCheck();
                if (u1_t_state != (U1)RTCIC_DRV_STATE_EXECUTION) {
                    if (u1_t_state != (U1)RTCIC_DRV_STATE_NORMAL) {
                        u1_s_rtcic_drv_proc_phase   = (U1)RTCIC_DRV_PHASE_INITWAIT;
                        u2_s_rtcic_drv_initial_wait = (U2)RTCIC_DRV_INITIALWAIT_TIME;
                        u1_s_rtcic_drv_rt_set_req   = (U1)RTCIC_DRV_INITIAL_REQ_ON;
                    }
                    else {
                        if (u1_s_rtcic_drv_rt_set_req == (U1)RTCIC_DRV_INITIAL_REQ_ON) {
                            u1_s_rtcic_drv_proc_phase = (U1)RTCIC_DRV_PHASE_RTCLK_START;
                        }
                        else if (u1_s_rtcic_drv_rt_set_req == (U1)RTCIC_DRV_DAYSET_REQ_ON) {
                            u1_s_rtcic_drv_proc_phase = (U1)RTCIC_DRV_PHASE_RTCLK_DAYSET;
                        }
                        else {
                            u1_s_rtcic_drv_proc_phase = (U1)RTCIC_DRV_PHASE_RTCLK_READ;
                        }
                    }
                }
                break;

            case RTCIC_DRV_PHASE_RTCLK_START:
                u1_t_state = u1_s_RtcIc_RtclkStart();
                if (u1_t_state == (U1)RTCIC_DRV_STATE_NORMAL) {
                    u1_s_rtcic_drv_proc_phase = (U1)RTCIC_DRV_PHASE_RTCLK_READWAIT;
                    u1_s_rtcic_drv_cycle_time = (U1)RTCIC_DRV_READCYCLE_TIME;
                }
                else if (u1_t_state == (U1)RTCIC_DRV_STATE_ABNORMAL) {
                    u1_s_rtcic_drv_proc_phase = (U1)RTCIC_DRV_PHASE_VLFBIT_CHECK;
                }
                else {
                    /* do nothing */
                }
                break;

            case RTCIC_DRV_PHASE_RTCLK_DAYSET:
                u1_t_state = u1_s_RtcIc_RtclkDayset();
                if (u1_t_state == (U1)RTCIC_DRV_STATE_NORMAL) {
                    u1_s_rtcic_drv_proc_phase = (U1)RTCIC_DRV_PHASE_RTCLK_READWAIT;
                }
                else if (u1_t_state == (U1)RTCIC_DRV_STATE_ABNORMAL) {
                    u1_s_rtcic_drv_proc_phase = (U1)RTCIC_DRV_PHASE_VLFBIT_CHECK;
                }
                else {
                    /* do nothing */
                }
                break;

            case RTCIC_DRV_PHASE_RTCLK_READ:
                u1_t_state = u1_s_RtcIc_RtclkRead();
                if (u1_t_state == (U1)RTCIC_DRV_STATE_NORMAL) {
                    u1_s_rtcic_drv_proc_phase = (U1)RTCIC_DRV_PHASE_RTCLK_READWAIT;
                    u1_s_rtcic_drv_cycle_time = (U1)RTCIC_DRV_READCYCLE_TIME;
                }
                break;

            case RTCIC_DRV_PHASE_RTCLK_READWAIT:
                u1_t_state = u1_s_RtcIc_RtclkReadWait();
                if ((u1_s_rtcic_drv_rt_set_req == (U1)RTCIC_DRV_INITIAL_REQ_ON) ||
                    (u1_s_rtcic_drv_rt_set_req == (U1)RTCIC_DRV_DAYSET_REQ_ON)) {
                    u1_s_rtcic_drv_proc_phase = (U1)RTCIC_DRV_PHASE_VLFBIT_CHECK;
                }
                else {
                    if (u1_t_state == (U1)RTCIC_DRV_TIMEOUT) {
                        u1_s_rtcic_drv_proc_phase = (U1)RTCIC_DRV_PHASE_VLFBIT_CHECK;
                    }
                }
                break;

            default:
                if (u1_s_rtcic_drv_i2c_type == (U1)RTCIC_DRV_COMNO_NON) {
                    u1_s_rtcic_drv_proc_phase = (U1)RTCIC_DRV_PHASE_VLFBIT_CHECK;
                    u1_t_grp = u1_s_rtcic_drv_proc_subphase & (U1)RTCIC_DRV_SUBPHASE_GRPMASK;
                    if (u1_t_grp == (U1)RTCIC_DRV_SUBPHASE_GRPCLK) {
                        u1_s_rtcic_drv_rt_set_req = (U1)RTCIC_DRV_INITIAL_REQ_ON;
                    }
                    else if (u1_t_grp == (U1)RTCIC_DRV_SUBPHASE_GRPDAY) {
                        u1_s_rtcic_drv_rt_set_req = (U1)RTCIC_DRV_DAYSET_REQ_ON;
                    }
                    else {
                        /* do nothing */
                    }
                }
                break;
        }
    }
}
/*===================================================================================================================================*/
/*  void    vd_s_RtcIc_I2cComControl(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_RtcIc_I2cComControl(void)
{
    uint8   mcu_sts;                /* 書込み状況 */

    /* Ackタイムアウト用カウンタインクリメント */
    if(Mcu_OnStep_RtcIc_AckTime < (uint32)MCU_SYS_COUNTTIME_FIN){
        Mcu_OnStep_RtcIc_AckTime++;
    }

    switch (u1_s_rtcic_drv_i2c_type){
        case RTCIC_DRV_COMNO_CLK_SET:
        /* レジスタ書込み処理 */
            mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_RTC, &Mcu_RegStep_RtcIc, (uint16)MCU_WRINUM_RTCIC_TIME_SET,
                                              (uint8)GP_I2C_MA_SLA_5_RTC, RTCIC_TIME_SET, &Mcu_OnStep_RtcIc_AckTime,
                                              st_sp_MCU_SYS_MET_RTCIC_SETREG_CLK, &Mcu_RegSet_BetWaitTime_Stub);
            break;

        case RTCIC_DRV_COMNO_DAY_SET:
        /* レジスタ書込み処理 */
            mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_RTC, &Mcu_RegStep_RtcIc, (uint16)MCU_WRINUM_RTCIC_DAY_SET,
                                              (uint8)GP_I2C_MA_SLA_5_RTC, RTCIC_DAY_SET, &Mcu_OnStep_RtcIc_AckTime,
                                              st_sp_MCU_SYS_MET_RTCIC_SETREG_DAYSET, &Mcu_RegSet_BetWaitTime_Stub);
            break;

        case RTCIC_DRV_COMNO_VLFBIT_READ:
            /* レジスタ読出し処理 */
            mcu_sts = Mcu_Dev_I2c_Ctrl_RegRead((uint8)MCU_I2C_ACK_RTC, &Mcu_RegStep_RtcIc, (uint8)GP_I2C_MA_SLA_5_RTC,
                                                &Mcu_OnStep_RtcIc_AckTime, st_sp_MCU_SYS_MET_RTCIC_READREG_VLF,
                                                &Mcu_RegSet_BetWaitTime_Stub, (U1)MCU_I2C_WAIT_NON);
            break;

        case RTCIC_DRV_COMNO_CLK_READ:
            /* レジスタ読出し処理 */
            mcu_sts = Mcu_Dev_I2c_Ctrl_RegRead((uint8)MCU_I2C_ACK_RTC, &Mcu_RegStep_RtcIc, (uint8)GP_I2C_MA_SLA_5_RTC,
                                                &Mcu_OnStep_RtcIc_AckTime, st_sp_MCU_SYS_MET_RTCIC_READREG_CLK,
                                                &Mcu_RegSet_BetWaitTime_Stub, (U1)MCU_I2C_WAIT_NON);
            break;

        case RTCIC_DRV_COMNO_CONTREG_READ:
            /* レジスタ読出し処理 */
            mcu_sts = Mcu_Dev_I2c_Ctrl_RegRead((uint8)MCU_I2C_ACK_RTC, &Mcu_RegStep_RtcIc, (uint8)GP_I2C_MA_SLA_5_RTC,
                                                &Mcu_OnStep_RtcIc_AckTime, st_sp_MCU_SYS_MET_RTCIC_READREG_CONT,
                                                &Mcu_RegSet_BetWaitTime_Stub, (U1)MCU_I2C_WAIT_NON);
            break;

        case RTCIC_DRV_COMNO_BACKUP_READ:
            /* レジスタ読出し処理 */
            mcu_sts = Mcu_Dev_I2c_Ctrl_RegRead((uint8)MCU_I2C_ACK_RTC, &Mcu_RegStep_RtcIc, (uint8)GP_I2C_MA_SLA_5_RTC,
                                                &Mcu_OnStep_RtcIc_AckTime, st_sp_MCU_SYS_MET_RTCIC_READREG_BACKUP,
                                                &Mcu_RegSet_BetWaitTime_Stub, (U1)MCU_I2C_WAIT_NON);
            break;

        case RTCIC_DRV_COMNO_RAM_READ:
            /* レジスタ読出し処理 */
            mcu_sts = Mcu_Dev_I2c_Ctrl_RegRead((uint8)MCU_I2C_ACK_RTC, &Mcu_RegStep_RtcIc, (uint8)GP_I2C_MA_SLA_5_RTC,
                                                &Mcu_OnStep_RtcIc_AckTime, st_sp_MCU_SYS_MET_RTCIC_READREG_RAM,
                                                &Mcu_RegSet_BetWaitTime_Stub, (U1)MCU_I2C_WAIT_NON);
            break;

        case RTCIC_DRV_COMNO_VFLBIT_SET:
        /* レジスタ書込み処理 */
            mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_RTC, &Mcu_RegStep_RtcIc, (uint16)MCU_WRINUM_RTCIC_VLF_SET,
                                              (uint8)GP_I2C_MA_SLA_5_RTC, RTCIC_VLF_SET, &Mcu_OnStep_RtcIc_AckTime,
                                              st_sp_MCU_SYS_MET_RTCIC_SETREG_VLF, &Mcu_RegSet_BetWaitTime_Stub);
            break;

        case RTCIC_DRV_COMNO_NON:
        default:
            u1_s_rtcic_drv_i2c_type     = (U1)RTCIC_DRV_COMNO_NON;
            u1_s_rtcic_drv_i2c_comstate = (U1)RTCIC_I2C_STATE_STOP;
            break;
    }
    if (u1_s_rtcic_drv_i2c_type != (U1)RTCIC_DRV_COMNO_NON) {
        if(mcu_sts == (uint8)TRUE){
            /* 全書込み完了 待機状態に遷移 */
            u1_s_rtcic_drv_i2c_type     = (U1)RTCIC_DRV_COMNO_NON;
            u1_s_rtcic_drv_i2c_comstate = (U1)RTCIC_I2C_STATE_NORMAL;
        }
        else {
            u1_s_rtcic_drv_i2c_comstate = (U1)RTCIC_I2C_STATE_EXECUTION;
        }
    }
}
/*===================================================================================================================================*/
/*  void    vd_s_RtcIc_I2cErrCheck(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_RtcIc_I2cErrCheck(void)
{
    if (u1_s_rtcic_drv_i2c_comstate == (U1)RTCIC_I2C_STATE_EXECUTION) {
        if (u1_s_rtcic_drv_i2c_timeout < (U1)RTCIC_DRV_IC2ERROR_TIME) {
            u1_s_rtcic_drv_i2c_timeout++;
        }
        else {
            if (u1_s_rtcic_drv_state == (U1)RTCIC_DEV_IC_NORMAL) {
                u1_s_rtcic_drv_state = (U1)RTCIC_DEV_IC_I2C_ERROR;
            }
        }
    }
    else {
        u1_s_rtcic_drv_i2c_timeout = (U1)0U;
        if (u1_s_rtcic_drv_state == (U1)RTCIC_DEV_IC_I2C_ERROR) {
            u1_s_rtcic_drv_state = (U1)RTCIC_DEV_IC_NORMAL;
        }
    }
}
/*===================================================================================================================================*/
/*  U1      u1_s_RtcIc_InitialWait(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_RtcIc_InitialWait(void)
{

    U1                 u1_t_stsbit;

    u1_t_stsbit = (U1)RTCIC_DRV_TIMEOUT;

    if (u2_s_rtcic_drv_initial_wait > (U2)RTCIC_DRV_INITIALWAIT_TIME) {
        u2_s_rtcic_drv_initial_wait = (U2)RTCIC_DRV_INITIALWAIT_TIME;
    }

    if (u2_s_rtcic_drv_initial_wait != (U2)0) {
        u2_s_rtcic_drv_initial_wait --;
        u1_t_stsbit = (U1)RTCIC_DRV_TIMEWAIT;
    }

    return(u1_t_stsbit);
}
/*===================================================================================================================================*/
/*  U1      u1_s_RtcIc_VlfbitCheck(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_RtcIc_VlfbitCheck(void)
{
    U1                 u1_t_state;
    U1                 u1_t_stsbit;
    U1                 u1_t_vlfbit;

    u1_t_stsbit = (U1)RTCIC_DRV_STATE_EXECUTION;

    u1_t_state = u1_s_RtcIc_I2cStateCheck();

    switch(u1_t_state) {
        case RTCIC_I2C_STATE_STOP:
            Mcu_Sys_Met_RtcIc_Vlf_Rd_Init();
            u1_s_rtcic_drv_i2c_type   = (U1)RTCIC_DRV_COMNO_VLFBIT_READ;
            u1_s_rtcic_drv_vlfbit_bfr = (U1)U1_MAX;
            break;

        case RTCIC_I2C_STATE_NORMAL:
            u1_t_vlfbit = Mcu_Sys_Met_RtcIc_Vlf_Rd_Read();
            u1_t_vlfbit &= (U1)RTCIC_DRV_FLAG_REGISTA_VLF;
            if (u1_s_rtcic_drv_vlfbit_bfr == u1_t_vlfbit) {
                if (u1_t_vlfbit != (U1)RTCIC_DRV_FLAG_REGISTA_VLF) {
                    u1_t_stsbit = (U1)RTCIC_DRV_STATE_NORMAL;
                }
                else {
                    if (u1_s_rtcic_drv_state != (U1)RTCIC_DEV_IC_NONINITIAL) {
                        u1_s_rtcic_drv_state = (U1)RTCIC_DEV_IC_RESET;
                    }
                    u1_t_stsbit = (U1)RTCIC_DRV_STATE_ABNORMAL;
                }
            }
            else {
                u1_s_rtcic_drv_vlfbit_bfr = u1_t_vlfbit;
                Mcu_Sys_Met_RtcIc_Vlf_Rd_Init();
                u1_s_rtcic_drv_i2c_type = (U1)RTCIC_DRV_COMNO_VLFBIT_READ;
            }
            break;

        default:
            break;
    }

    return(u1_t_stsbit);
}
/*===================================================================================================================================*/
/*  U1      u1_s_RtcIc_RtclkStart(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_RtcIc_RtclkStart(void)
{
    U4                 u4_t_real_time;
    U4                 u4_t_daycnt;
    U1                 u1_t_cmp;    
    U1                 u1_t_state;
    U1                 u1_t_stsbit;
    U1                 u1_t_phase_bak;

    u1_t_stsbit = (U1)RTCIC_DRV_STATE_EXECUTION;

    u1_t_state = u1_s_RtcIc_I2cStateCheck();

    switch(u1_t_state) {
        case RTCIC_I2C_STATE_STOP:
            Mcu_Sys_Met_RtcIc_Clk_Init(u4_s_rtcic_drv_real_time, u4_s_rtcic_drv_daycnt);
            u1_s_rtcic_drv_i2c_type       = (U1)RTCIC_DRV_COMNO_CLK_SET;
            u1_s_rtcic_drv_rt_set_req     = (U1)RTCIC_DRV_INITIAL_REQ_OFF;
            u1_s_rtcic_drv_proc_subphase  = (U1)RTCIC_DRV_SUBPHASE_CLKWRITE;
            u1_s_rtcic_drv_rt_set_req_exc = u1_s_rtcic_drv_rt_set_req_day;
            u1_s_rtcic_drv_rt_set_req_day = (U1)RTCIC_DRV_INITIAL_REQ_OFF;
            break;

        case RTCIC_I2C_STATE_NORMAL:
            if (u1_s_rtcic_drv_proc_subphase == (U1)RTCIC_DRV_SUBPHASE_CLKWRITE) {
                Mcu_Sys_Met_RtcIc_Clk_Rd_Init();
                u1_s_rtcic_drv_i2c_type      = (U1)RTCIC_DRV_COMNO_CLK_READ;
                u1_s_rtcic_drv_proc_subphase = (U1)RTCIC_DRV_SUBPHASE_CLK;
            }
            else {
                u1_t_phase_bak = u1_s_rtcic_drv_proc_subphase;
                switch(u1_s_rtcic_drv_proc_subphase) {
                    case RTCIC_DRV_SUBPHASE_CLK:
                        Mcu_Sys_Met_RtcIc_Clk_Rd_Read(&u4_t_real_time, &u4_t_daycnt);
                        if ((u4_s_rtcic_drv_real_time == u4_t_real_time) &&
                            (u4_s_rtcic_drv_daycnt    == u4_t_daycnt)) {
                            Mcu_Sys_Met_RtcIc_ContReg_Rd_Init();
                            u1_s_rtcic_drv_i2c_type      = (U1)RTCIC_DRV_COMNO_CONTREG_READ;
                            u1_s_rtcic_drv_proc_subphase = (U1)RTCIC_DRV_SUBPHASE_CONTREG;
                        }
                        break;

                    case RTCIC_DRV_SUBPHASE_CONTREG:
                        u1_t_cmp = Mcu_Sys_Met_RtcIc_ContReg_Rd_Cmp();
                        if (u1_t_cmp == (U1)TRUE) {
                            Mcu_Sys_Met_RtcIc_Backup_Rd_Init();
                            u1_s_rtcic_drv_i2c_type      = (U1)RTCIC_DRV_COMNO_BACKUP_READ;
                            u1_s_rtcic_drv_proc_subphase = (U1)RTCIC_DRV_SUBPHASE_BACKUP;
                        }
                        break;

                    case RTCIC_DRV_SUBPHASE_BACKUP:
                        u1_t_cmp = Mcu_Sys_Met_RtcIc_Backup_Rd_Cmp();
                        if (u1_t_cmp == (U1)TRUE) {
                            Mcu_Sys_Met_RtcIc_Ram_Rd_Init();
                            u1_s_rtcic_drv_i2c_type      = (U1)RTCIC_DRV_COMNO_RAM_READ;
                            u1_s_rtcic_drv_proc_subphase = (U1)RTCIC_DRV_SUBPHASE_RAM;
                        }
                        break;

                    case RTCIC_DRV_SUBPHASE_RAM:
                        u1_t_cmp = Mcu_Sys_Met_RtcIc_Ram_Rd_Cmp();
                        if (u1_t_cmp == (U1)TRUE) {
                            u1_s_rtcic_drv_i2c_type      = (U1)RTCIC_DRV_COMNO_VFLBIT_SET;
                            u1_s_rtcic_drv_proc_subphase = (U1)RTCIC_DRV_SUBPHASE_VLFCLS;
                        }
                        break;
                    case RTCIC_DRV_SUBPHASE_VLFCLS:
                        u1_s_rtcic_drv_state             = (U1)RTCIC_DEV_IC_NORMAL;
                        u1_t_stsbit                      = (U1)RTCIC_DRV_STATE_NORMAL;
                        u1_s_rtcic_drv_time_read         = (U1)RTCIC_DRV_TIME_READ;
                        u1_s_rtcic_drv_proc_subphase     = (U1)RTCIC_DRV_SUBPHASE_END;
                        u1_s_rtcic_drv_rt_set_req_exc    = (U1)RTCIC_DRV_INITIAL_REQ_OFF;
                        break;
                    default:
                        /* do nothing */
                        break;
                }
                if (u1_s_rtcic_drv_proc_subphase == u1_t_phase_bak) {
                    u1_s_rtcic_drv_rt_set_req = (U1)RTCIC_DRV_INITIAL_REQ_ON;
                    u1_t_stsbit = (U1)RTCIC_DRV_STATE_ABNORMAL;
                }
            }
            break;

        default:
            break;
    }

    return(u1_t_stsbit);
}
/*===================================================================================================================================*/
/*  U1      u1_s_RtcIc_RtclkDayset(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_RtcIc_RtclkDayset(void)
{
    U4                 u4_t_real_time;
    U4                 u4_t_daycnt;
    U1                 u1_t_state;
    U1                 u1_t_stsbit;

    u1_t_stsbit = (U1)RTCIC_DRV_STATE_EXECUTION;

    u1_t_state = u1_s_RtcIc_I2cStateCheck();

    switch(u1_t_state) {
        case RTCIC_I2C_STATE_STOP:
            Mcu_Sys_Met_RtcIc_Day_Set(u4_s_rtcic_drv_daycnt);
            u1_s_rtcic_drv_i2c_type      = (U1)RTCIC_DRV_COMNO_DAY_SET;
            u1_s_rtcic_drv_rt_set_req    = (U1)RTCIC_DRV_INITIAL_REQ_OFF;
            u1_s_rtcic_drv_proc_subphase = (U1)RTCIC_DRV_SUBPHASE_DAYWRITE;
            break;

        case RTCIC_I2C_STATE_NORMAL:
            if (u1_s_rtcic_drv_proc_subphase == (U1)RTCIC_DRV_SUBPHASE_DAYWRITE) {
                Mcu_Sys_Met_RtcIc_Clk_Rd_Init();
                u1_s_rtcic_drv_i2c_type      = (U1)RTCIC_DRV_COMNO_CLK_READ;
                u1_s_rtcic_drv_proc_subphase = (U1)RTCIC_DRV_SUBPHASE_READ;
            }
            else {
                Mcu_Sys_Met_RtcIc_Clk_Rd_Read(&u4_t_real_time, &u4_t_daycnt);
                if (u4_s_rtcic_drv_daycnt == u4_t_daycnt) {
                    u1_s_rtcic_drv_state         = (U1)RTCIC_DEV_IC_NORMAL;
                    u1_s_rtcic_drv_proc_subphase = (U1)RTCIC_DRV_SUBPHASE_END;
                    u1_t_stsbit                  = (U1)RTCIC_DRV_STATE_NORMAL;
                }
                else {
                    if (u1_s_rtcic_drv_rt_set_req != (U1)RTCIC_DRV_INITIAL_REQ_ON) {
                        u1_s_rtcic_drv_rt_set_req = (U1)RTCIC_DRV_DAYSET_REQ_ON;
                    }
                    u1_t_stsbit = (U1)RTCIC_DRV_STATE_ABNORMAL;
                }
            }
            break;

        default:
            break;
    }

    return(u1_t_stsbit);
}
/*===================================================================================================================================*/
/*  U1      u1_s_RtcIc_RtclkRead(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_RtcIc_RtclkRead(void)
{
    U1                 u1_t_state;
    U1                 u1_t_stsbit;
    U4                 u4_t_real_time;
    U4                 u4_t_daycnt;

    u1_t_stsbit = (U1)RTCIC_DRV_STATE_EXECUTION;

    u1_t_state = u1_s_RtcIc_I2cStateCheck();

    switch(u1_t_state) {
        case RTCIC_I2C_STATE_STOP:
            Mcu_Sys_Met_RtcIc_Clk_Rd_Init();
            u1_s_rtcic_drv_i2c_type      = (U1)RTCIC_DRV_COMNO_CLK_READ;
            u1_s_rtcic_drv_proc_subphase = (U1)RTCIC_DRV_SUBPHASE_READ_FIRST;
            break;

        case RTCIC_I2C_STATE_NORMAL:
            Mcu_Sys_Met_RtcIc_Clk_Rd_Read(&u4_t_real_time, &u4_t_daycnt);
            if (u1_s_rtcic_drv_proc_subphase == (U1)RTCIC_DRV_SUBPHASE_READ_SECOND) {
                if ((u4_s_rtcic_drv_real_time_bfr == u4_t_real_time) &&
                    (u4_s_rtcic_drv_daycnt_bfr == u4_t_daycnt)) {
                    if (u1_s_rtcic_drv_rt_set_req != (U1)RTCIC_DRV_INITIAL_REQ_ON) {
                        u4_s_rtcic_drv_real_time = u4_t_real_time;
                        if (u1_s_rtcic_drv_rt_set_req != (U1)RTCIC_DRV_DAYSET_REQ_ON) {
                            u4_s_rtcic_drv_daycnt = u4_t_daycnt;
                        }
                    }
                    u1_s_rtcic_drv_time_read = (U1)RTCIC_DRV_TIME_READ;
                }
                u1_s_rtcic_drv_state         = (U1)RTCIC_DEV_IC_NORMAL;
                u1_s_rtcic_drv_proc_subphase = (U1)RTCIC_DRV_SUBPHASE_END;
                u1_t_stsbit                  = (U1)RTCIC_DRV_STATE_NORMAL;
            }
            else {
                u4_s_rtcic_drv_real_time_bfr = u4_t_real_time;
                u4_s_rtcic_drv_daycnt_bfr    = u4_t_daycnt;
                Mcu_Sys_Met_RtcIc_Clk_Rd_Init();
                u1_s_rtcic_drv_i2c_type      = (U1)RTCIC_DRV_COMNO_CLK_READ;
                u1_s_rtcic_drv_proc_subphase = (U1)RTCIC_DRV_SUBPHASE_READ_SECOND;
            }
            break;

        default:
            break;
    }

    return(u1_t_stsbit);
}
/*===================================================================================================================================*/
/*  U1      u1_s_RtcIc_RtclkReadWait(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_RtcIc_RtclkReadWait(void)
{

    U1                 u1_t_stsbit;

    u1_t_stsbit = (U1)RTCIC_DRV_TIMEOUT;

    if (u1_s_rtcic_drv_cycle_time > (U1)RTCIC_DRV_READCYCLE_TIME) {
        u1_s_rtcic_drv_cycle_time = (U1)RTCIC_DRV_READCYCLE_TIME;
    }

    if (u1_s_rtcic_drv_cycle_time != (U1)0U) {
        u1_s_rtcic_drv_cycle_time--;
        u1_t_stsbit = (U1)RTCIC_DRV_TIMEWAIT;
    }

    return(u1_t_stsbit);
}
/*===================================================================================================================================*/
/*  U1      u1_s_RtcIc_I2cStateCheck(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_RtcIc_I2cStateCheck(void)
{
    U1                 u1_t_stsbit;

    u1_t_stsbit = u1_s_rtcic_drv_i2c_comstate;

    if (u1_t_stsbit == (U1)RTCIC_I2C_STATE_NORMAL) {
        u1_s_rtcic_drv_i2c_comstate = (U1)RTCIC_I2C_STATE_STOP;
    }

    return(u1_t_stsbit);
}


/*===================================================================================================================================*/
/*  void    vd_g_RtcIc_RtclkRtartReq(const U4 u4_a_settime, const U4 u4_a_daycnt)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_RtcIc_RtclkRtartReq(const U4 u4_a_settime, const U4 u4_a_daycnt)
{
    u4_s_rtcic_drv_real_time  = u4_a_settime;
    u4_s_rtcic_drv_daycnt     = u4_a_daycnt;
    if (u1_s_rtcic_drv_rt_set_req == (U1)RTCIC_DRV_DAYSET_REQ_ON) {
        u1_s_rtcic_drv_rt_set_req_day = (U1)RTCIC_DRV_DAYSET_REQ_ON;
    }
    u1_s_rtcic_drv_rt_set_req = (U1)RTCIC_DRV_INITIAL_REQ_ON;
}
/*===================================================================================================================================*/
/*  void    vd_g_RtcIc_RtclkDaySet(const U4 u4_a_daycnt)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_RtcIc_RtclkDaySet(const U4 u4_a_daycnt)
{
    u4_s_rtcic_drv_daycnt     = u4_a_daycnt;
    if (u1_s_rtcic_drv_rt_set_req != (U1)RTCIC_DRV_INITIAL_REQ_ON) {
        u1_s_rtcic_drv_rt_set_req     = (U1)RTCIC_DRV_DAYSET_REQ_ON;
    }
    else {
        u1_s_rtcic_drv_rt_set_req_day = (U1)RTCIC_DRV_DAYSET_REQ_ON;
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_RtcIc_RtclkStaProv(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_RtcIc_RtclkStaProv(void)
{
    U1                 u1_t_stsbit;

    switch(u1_s_rtcic_drv_state) {
        case RTCIC_DEV_IC_NONINITIAL:
            u1_t_stsbit = (U1)RTCLK_STSBIT_RTC_INITIAL;
            break;
        case RTCIC_DEV_IC_RESET:
            u1_t_stsbit = (U1)RTCLK_STSBIT_RTC_RESET;
            break;
        case RTCIC_DEV_IC_I2C_ERROR:
            u1_t_stsbit = (U1)RTCLK_STSBIT_I2C_ERROR;
            break;
        case RTCIC_DEV_IC_NORMAL:
            if (u1_s_rtcic_drv_time_read == (U1)RTCIC_DRV_TIME_READ) {
                u1_t_stsbit = (U1)RTCLK_STSBIT_RTC_RUN;
            }
            else {
                u1_t_stsbit = (U1)RTCLK_STSBIT_TIM_NOREAD;
            }
            break;
        default:
            u1_t_stsbit = (U1)RTCLK_STSBIT_I2C_ERROR;
            break;
    }

    if ((u1_s_rtcic_drv_rt_set_req == (U1)RTCIC_DRV_INITIAL_REQ_ON) ||
        (u1_s_rtcic_drv_proc_phase == (U1)RTCIC_DRV_PHASE_RTCLK_START)) {
        u1_t_stsbit |= (U1)RTCLK_STSBIT_CLKDAY_SET;
    }
    if ((u1_s_rtcic_drv_rt_set_req == (U1)RTCIC_DRV_DAYSET_REQ_ON) ||
        (u1_s_rtcic_drv_proc_phase == (U1)RTCIC_DRV_PHASE_RTCLK_DAYSET)) {
        u1_t_stsbit |= (U1)RTCLK_STSBIT_DAY_SET;
    }
    if ((u1_s_rtcic_drv_rt_set_req_day == (U1)RTCIC_DRV_DAYSET_REQ_ON) ||
        ((u1_s_rtcic_drv_rt_set_req_exc == (U1)RTCIC_DRV_DAYSET_REQ_ON) &&
         (u1_s_rtcic_drv_proc_phase     == (U1)RTCIC_DRV_PHASE_RTCLK_START))) {
        u1_t_stsbit |= (U1)RTCLK_STSBIT_DAY_SET;
    }

    return(u1_t_stsbit);
}
/*===================================================================================================================================*/
/*  void    vd_g_RtcIc_RtclkProv(U4* u4_a_realtime, U4* u4_a_daycnt)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_RtcIc_RtclkProv(U4* u4_a_realtime, U4* u4_a_daycnt)
{
    *u4_a_realtime = u4_s_rtcic_drv_real_time;
    *u4_a_daycnt   = u4_s_rtcic_drv_daycnt;
}
/*===================================================================================================================================*/
/*  U1      u1_g_RtcIcDrvShtdwnOk(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_RtcIcDrvShtdwnOk(void)
{
    U1                 u1_t_ok;

    u1_t_ok = (U1)TRUE;

    if (u1_s_rtcic_drv_i2c_timeout < (U1)RTCIC_DRV_IC2ERROR_TIME) {
        if ((u1_s_rtcic_drv_rt_set_req == (U1)RTCIC_DRV_INITIAL_REQ_ON) ||
            (u1_s_rtcic_drv_rt_set_req == (U1)RTCIC_DRV_DAYSET_REQ_ON)) {
            u1_t_ok = (U1)FALSE;
        }
        else if (u1_s_rtcic_drv_state == (U1)RTCIC_DEV_IC_NONINITIAL) {
            u1_t_ok = (U1)FALSE;
        }
        else if ((u1_s_rtcic_drv_proc_phase == (U1)RTCIC_DRV_PHASE_RTCLK_START) ||
                 (u1_s_rtcic_drv_proc_phase == (U1)RTCIC_DRV_PHASE_RTCLK_DAYSET)) {

            u1_t_ok = (U1)FALSE;
        }
        else {
            /* do nothing */
        }
    }

    return(u1_t_ok);

}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    24/ 1/2025  SU                                                                                                          */
/*                                                                                                                                   */
/*  * SU = Shin Uchida    , Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
