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
#define RTCIC_DRV_INITIAL_REQ_OFF                (0U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RTCIC_DRV_TIMEOUT                        (1U)
#define RTCIC_DRV_TIMEWAIT                       (0U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RTCIC_DRV_PHASE_INITWAIT                 (0U)
#define RTCIC_DRV_PHASE_VLFBIT_CHECK             (1U)
#define RTCIC_DRV_PHASE_RTCLK_START              (2U)
#define RTCIC_DRV_PHASE_RTCLK_READ               (3U)
#define RTCIC_DRV_PHASE_RTCLK_READWAIT           (4U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RTCIC_DRV_STATE_NORMAL                  (0U)
#define RTCIC_DRV_STATE_ABNORMAL                (1U)
#define RTCIC_DRV_STATE_EXECUTION               (2U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RTCIC_DRV_DAT_SEC_REGISTA                (0x00U)                        /* 00秒                                              */
#define RTCIC_DRV_DAT_MIN_REGISTA                (0x00U)                        /* 00分                                              */
#define RTCIC_DRV_DAT_HOUR_REGISTA               (0x01U)                        /* 01時                                              */

#define RTCIC_DRV_FLAG_REGISTA_VLF               (0x02U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RTCIC_DRV_COMNO_NON                      (0U)                           /* 要求なし                                          */
#define RTCIC_DRV_COMNO_CLK_SET                  (1U)                           /* 時計IC 設定                                       */
#define RTCIC_DRV_COMNO_VLFBIT_READ              (2U)                           /* VLF bit 読み込み                                  */
#define RTCIC_DRV_COMNO_CLK_READ                 (3U)                           /* 時刻 読み込み                                     */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RTCIC_I2C_STATE_STOP                     (0)
#define RTCIC_I2C_STATE_EXECUTION                (1)
#define RTCIC_I2C_STATE_NORMAL                   (2)
#define RTCIC_I2C_STATE_ABNORMAL                 (3)
#define RTCIC_I2C_STATE_RETRY                    (4)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RA8900_DRV_POS_READDATA_FIRST            (3U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RTCIC_DEV_IC_NONINITIAL                  (0U)
#define RTCIC_DEV_IC_NORMAL                      (1U)
#define RTCIC_DEV_IC_I2C_ERROR                   (2U)
#define RTCIC_DEV_IC_RESET                       (3U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MCU_SYS_COUNTTIME_FIN           (0xFFFFFFFFU)
#define MCU_WRINUM_RTCIC_TIME_SET       (1U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RTCIC_HHMMSS_BIT_SE                      (0x0000007fU)
#define RTCIC_HHMMSS_BIT_MI                      (0x0000007fU)
#define RTCIC_HHMMSS_BIT_HR                      (0x0000003fU)

#define RTCIC_HHMMSS_LSB_SE                      (0U)
#define RTCIC_HHMMSS_LSB_MI                      (8U)
#define RTCIC_HHMMSS_LSB_HR                      (16U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_rtcic_drv_real_time;
static U4      u4_s_rtcic_drv_initial_wait;
static U4      u4_s_rtcic_drv_vlfread_wait;
static U4      u4_s_rtcic_drv_cycle_time;

static U1      u1_s_rtcic_drv_rt_set_req;
static U1      u1_s_rtcic_drv_proc_phase;
static U1      u1_s_rtcic_drv_state;

static U1      u1_s_RtcIc_i2c_comstate;
static U1      u1_s_RtcIc_i2c_type;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
static uint16  Mcu_RegStep_RtcIc;               /* RTC-IC レジスタ書込み位置指定 */
static uint32  Mcu_OnStep_RtcIc_AckTime;        /* PTC-IC 書込み/読込みから応答までの時間計測 */

/* レジスタアクセス */
static uint16   Mcu_RegSet_BetWaitTime_Stub;    /* レジスタアクセス間Waitタイマ スタブ */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1      u1_s_RtcIc_InitialWait(void);
static U1      u1_s_RtcIc_VlfbitCheck(void);
static U1      u1_s_RtcIc_RtclkStart(void);
static U1      u1_s_RtcIc_RtclkRead(void);
static U1      u1_s_RtcIc_RtclkReadWait(void);

static void    vd_s_RtcIc_I2cComControl(void);
static U1      u1_s_RtcIc_I2cStateCheck(void);


/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_REG_WRI_REQ RTCIC_TIME_SET[MCU_WRINUM_RTCIC_TIME_SET] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         4,         0}
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_RtcIc_MainInitial(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_RtcIc_MainInitial(void)
{
    u4_s_rtcic_drv_real_time = (U4)((RTCIC_DRV_DAT_HOUR_REGISTA << RTCIC_HHMMSS_LSB_HR) |
                                    (RTCIC_DRV_DAT_MIN_REGISTA << RTCIC_HHMMSS_LSB_MI) |
                                     RTCIC_DRV_DAT_SEC_REGISTA);

    u4_s_rtcic_drv_initial_wait = (U4)0;
    u4_s_rtcic_drv_vlfread_wait = (U4)0;
    u4_s_rtcic_drv_cycle_time   = (U4)0;

    u1_s_rtcic_drv_rt_set_req = (U1)RTCIC_DRV_INITIAL_REQ_ON;
    u1_s_rtcic_drv_proc_phase = (U1)RTCIC_DRV_PHASE_VLFBIT_CHECK;
    u1_s_rtcic_drv_state      = (U1)RTCIC_DEV_IC_NONINITIAL;

    u1_s_RtcIc_i2c_comstate = (U1)RTCIC_I2C_STATE_STOP;
    u1_s_RtcIc_i2c_type     = (U1)0;

    Mcu_RegStep_RtcIc           = (uint16)0U;
    Mcu_OnStep_RtcIc_AckTime    = (uint32)0U;
    Mcu_RegSet_BetWaitTime_Stub = (uint16)0xFFFFU;
}
/*===================================================================================================================================*/
/*  void    vd_g_RtcIc_MainTask(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_RtcIc_MainTask(void)
{
    U1                 u1_t_initwait;
    U1                 u1_t_state;

    u1_t_state = (U1)0U;

    vd_s_RtcIc_I2cComControl();

    u1_t_initwait = u1_s_RtcIc_InitialWait();

    if (u1_t_initwait == (U1)RTCIC_DRV_TIMEOUT) {
        switch (u1_s_rtcic_drv_proc_phase) {
            case RTCIC_DRV_PHASE_INITWAIT:
                u1_s_rtcic_drv_proc_phase = (U1)RTCIC_DRV_PHASE_RTCLK_START;
                break;

            case RTCIC_DRV_PHASE_VLFBIT_CHECK:
                u1_t_state = u1_s_RtcIc_VlfbitCheck();
                if (u1_t_state != RTCIC_DRV_STATE_EXECUTION) {
                    if (u1_t_state != RTCIC_DRV_STATE_NORMAL) {
                        u1_s_rtcic_drv_proc_phase = (U1)RTCIC_DRV_PHASE_INITWAIT;
                        u4_s_rtcic_drv_initial_wait = (U4)RTCIC_DRV_INITIALWAIT_TIME;
                        u1_s_rtcic_drv_rt_set_req = (U1)RTCIC_DRV_INITIAL_REQ_ON;
                    }
                    else {
                        if (u1_s_rtcic_drv_rt_set_req == (U1)RTCIC_DRV_INITIAL_REQ_ON) {
                            u1_s_rtcic_drv_proc_phase = (U1)RTCIC_DRV_PHASE_RTCLK_START;
                        }
                        else {
                            u1_s_rtcic_drv_proc_phase = (U1)RTCIC_DRV_PHASE_RTCLK_READ;
                        }
                    }
                }
                break;

            case RTCIC_DRV_PHASE_RTCLK_START:
                u1_t_state = u1_s_RtcIc_RtclkStart();
                if (u1_t_state != RTCIC_DRV_STATE_EXECUTION) {
                    if (u1_t_state != RTCIC_DRV_STATE_NORMAL) {
                        u1_s_rtcic_drv_proc_phase = (U1)RTCIC_DRV_PHASE_VLFBIT_CHECK;
                        u4_s_rtcic_drv_vlfread_wait = (U4)0;
                    }
                    else {
                        u1_s_rtcic_drv_proc_phase = (U1)RTCIC_DRV_PHASE_RTCLK_READWAIT;
                        u4_s_rtcic_drv_cycle_time = (U4)RTCIC_DRV_READCYCLE_TIME;
                        u1_s_rtcic_drv_rt_set_req = (U1)RTCIC_DRV_INITIAL_REQ_OFF;
                    }
                }
                break;

            case RTCIC_DRV_PHASE_RTCLK_READ:
                u1_t_state = u1_s_RtcIc_RtclkRead();
                if (u1_t_state != RTCIC_DRV_STATE_EXECUTION) {
                    if (u1_t_state != RTCIC_DRV_STATE_NORMAL) {
                        u1_s_rtcic_drv_proc_phase = (U1)RTCIC_DRV_PHASE_VLFBIT_CHECK;
                        u4_s_rtcic_drv_vlfread_wait = (U4)0;
                    }
                    else {
                        u1_s_rtcic_drv_proc_phase = (U1)RTCIC_DRV_PHASE_RTCLK_READWAIT;
                        u4_s_rtcic_drv_cycle_time = (U4)RTCIC_DRV_READCYCLE_TIME;
                    }
                }
                break;

            case RTCIC_DRV_PHASE_RTCLK_READWAIT:
                u1_t_state = u1_s_RtcIc_RtclkReadWait();
                if (u1_s_rtcic_drv_rt_set_req == (U1)RTCIC_DRV_INITIAL_REQ_ON) {
                    u1_s_rtcic_drv_proc_phase = (U1)RTCIC_DRV_PHASE_VLFBIT_CHECK;
                }
                else {
                    if (u1_t_state == (U1)RTCIC_DRV_TIMEOUT) {
                        u1_s_rtcic_drv_proc_phase = (U1)RTCIC_DRV_PHASE_VLFBIT_CHECK;
                    }
                }
                break;

            default:
                break;
        }
    }
}
/*===================================================================================================================================*/
/*  void    vd_s_RtcIc_I2cComControl(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_RtcIc_I2cComControl(void)
{
    uint8   mcu_sts;                /* 書込み状況 */

    mcu_sts             = (uint8)FALSE;

    /* Ackタイムアウト用カウンタインクリメント */
    if(Mcu_OnStep_RtcIc_AckTime < (uint32)MCU_SYS_COUNTTIME_FIN){
        Mcu_OnStep_RtcIc_AckTime++;
    }

    switch (u1_s_RtcIc_i2c_type){
        case RTCIC_DRV_COMNO_CLK_SET:
        /* レジスタ書込み処理 */
            mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet((uint8)MCU_I2C_ACK_RTC, &Mcu_RegStep_RtcIc, (uint16)MCU_WRINUM_RTCIC_TIME_SET,
                                              (uint8)GP_I2C_MA_SLA_5_RTC, RTCIC_TIME_SET, &Mcu_OnStep_RtcIc_AckTime,
                                              st_sp_MCU_SYS_MET_RTCIC_SETREG_CLK, &Mcu_RegSet_BetWaitTime_Stub);

            if(mcu_sts == (uint8)TRUE){
                /* 全書込み完了 待機状態に遷移 */
                u1_s_RtcIc_i2c_type = (U1)RTCIC_DRV_COMNO_NON;
                u1_s_RtcIc_i2c_comstate = (U1)RTCIC_I2C_STATE_NORMAL;
            }
            else {
                u1_s_RtcIc_i2c_comstate = (U1)RTCIC_I2C_STATE_EXECUTION;
            }
            break;

        case RTCIC_DRV_COMNO_VLFBIT_READ:
            /* レジスタ読出し処理 */
            mcu_sts = Mcu_Dev_I2c_Ctrl_RegRead((uint8)MCU_I2C_ACK_RTC, &Mcu_RegStep_RtcIc, (uint8)GP_I2C_MA_SLA_5_RTC,
                                                &Mcu_OnStep_RtcIc_AckTime, st_sp_MCU_SYS_MET_RTCIC_SETREG_VLF_RD, &Mcu_RegSet_BetWaitTime_Stub, (U1)MCU_I2C_WAIT_NON);

            if(mcu_sts == (uint8)TRUE){
                /* 読み込み完了 待機状態に遷移 */
                u1_s_RtcIc_i2c_type = (U1)RTCIC_DRV_COMNO_NON;
                u1_s_RtcIc_i2c_comstate = (U1)RTCIC_I2C_STATE_NORMAL;
            }
            else {
                u1_s_RtcIc_i2c_comstate = (U1)RTCIC_I2C_STATE_EXECUTION;
            }
            break;

        case RTCIC_DRV_COMNO_CLK_READ:
            /* レジスタ読出し処理 */
            mcu_sts = Mcu_Dev_I2c_Ctrl_RegRead((uint8)MCU_I2C_ACK_RTC, &Mcu_RegStep_RtcIc, (uint8)GP_I2C_MA_SLA_5_RTC,
                                                &Mcu_OnStep_RtcIc_AckTime, st_sp_MCU_SYS_MET_RTCIC_SETREG_CLK_RD, &Mcu_RegSet_BetWaitTime_Stub, (U1)MCU_I2C_WAIT_NON);

            if(mcu_sts == (uint8)TRUE){
                /* 読み込み完了 待機状態に遷移 */
                u1_s_RtcIc_i2c_type = (U1)RTCIC_DRV_COMNO_NON;
                u1_s_RtcIc_i2c_comstate = (U1)RTCIC_I2C_STATE_NORMAL;
            }
            else {
                u1_s_RtcIc_i2c_comstate = (U1)RTCIC_I2C_STATE_EXECUTION;
            }
            break;

        case RTCIC_DRV_COMNO_NON:
        default:
            break;
    }
}
/*===================================================================================================================================*/
/*  U1      u1_s_RtcIc_InitialWait(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_RtcIc_InitialWait(void)
{

    U1                 u1_t_stsbit;

    u1_t_stsbit = (U1)RTCIC_DRV_TIMEOUT;

    if (u4_s_rtcic_drv_initial_wait != (U4)0) {
        u4_s_rtcic_drv_initial_wait --;
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
            if (u4_s_rtcic_drv_vlfread_wait == (U4)0) {
                Mcu_Sys_Met_RtcIc_Vlf_Rd_Init();
                u1_s_RtcIc_i2c_type = (U1)RTCIC_DRV_COMNO_VLFBIT_READ;
            }
            else {
                u4_s_rtcic_drv_vlfread_wait--;
            }
            break;

        case RTCIC_I2C_STATE_NORMAL:
            u1_t_vlfbit = u1_sp_MCU_SYS_MET_RTCIC_SETREG_VLF_RD_PDU2[1];
            u1_t_vlfbit &= (U1)RTCIC_DRV_FLAG_REGISTA_VLF;
            if (u1_t_vlfbit == (U1)0) {
                u1_s_rtcic_drv_state = (U1)RTCIC_DEV_IC_NORMAL;
                u1_t_stsbit = (U1)RTCIC_DRV_STATE_NORMAL;
            }
            else {
                u1_s_rtcic_drv_state = (U1)RTCIC_DEV_IC_RESET;
                u1_t_stsbit = (U1)RTCIC_DRV_STATE_ABNORMAL;
            }
            u4_s_rtcic_drv_vlfread_wait = (U4)0;
            break;

        case RTCIC_I2C_STATE_ABNORMAL:
           u1_s_rtcic_drv_state = (U1)RTCIC_DEV_IC_I2C_ERROR;
           u4_s_rtcic_drv_vlfread_wait = (U4)RTCIC_DRV_VLFREADWAIT_TIME;
           break;

        default:
    	u4_s_rtcic_drv_vlfread_wait = (U1)0;
            break;
    }

    return(u1_t_stsbit);
}
/*===================================================================================================================================*/
/*  U1      u1_s_RtcIc_RtclkStart(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_RtcIc_RtclkStart(void)
{
    U1                 u1_t_state;
    U1                 u1_t_stsbit;

    u1_t_stsbit = (U1)RTCIC_DRV_STATE_EXECUTION;

    u1_t_state = u1_s_RtcIc_I2cStateCheck();

    switch(u1_t_state) {
        case RTCIC_I2C_STATE_STOP:
            Mcu_Sys_Met_RtcIc_Clk_Init(u4_s_rtcic_drv_real_time);
            u1_s_RtcIc_i2c_type = (U1)RTCIC_DRV_COMNO_CLK_SET;
            break;
        case RTCIC_I2C_STATE_NORMAL:
            u1_t_stsbit = (U1)RTCIC_DRV_STATE_NORMAL;
            break;

        case RTCIC_I2C_STATE_ABNORMAL:
           u1_s_rtcic_drv_state = (U1)RTCIC_DEV_IC_I2C_ERROR;
           u1_t_stsbit = (U1)RTCIC_DRV_STATE_ABNORMAL;
           break;

        default:
            break;
    }

    return(u1_t_stsbit);
}
/*===================================================================================================================================*/
/*  U1      u1_s_RtcIc_RtclkRead(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_RtcIc_RtclkRead(void)
{
    U1                 u1_t_state;
    U1                 u1_t_se;
    U1                 u1_t_mi;
    U1                 u1_t_hr;

    U1                 u1_t_stsbit;

    u1_t_stsbit = (U1)RTCIC_DRV_STATE_EXECUTION;

    u1_t_state = u1_s_RtcIc_I2cStateCheck();

    switch(u1_t_state) {
        case RTCIC_I2C_STATE_STOP:
            Mcu_Sys_Met_RtcIc_Clk_Rd_Init();
            u1_s_RtcIc_i2c_type = (U1)RTCIC_DRV_COMNO_CLK_READ;
            break;

        case RTCIC_I2C_STATE_NORMAL:
            u1_t_se = u1_sp_MCU_SYS_MET_RTCIC_SETREG_CLK_RD_PDU2[1] & (U1)RTCIC_HHMMSS_BIT_SE;
            u1_t_mi = u1_sp_MCU_SYS_MET_RTCIC_SETREG_CLK_RD_PDU2[2] & (U1)RTCIC_HHMMSS_BIT_MI;
            u1_t_hr = u1_sp_MCU_SYS_MET_RTCIC_SETREG_CLK_RD_PDU2[3] & (U1)RTCIC_HHMMSS_BIT_HR;

            u4_s_rtcic_drv_real_time = (U4)((u1_t_hr << RTCIC_HHMMSS_LSB_HR) |
                                            (u1_t_mi << RTCIC_HHMMSS_LSB_MI) |
                                             u1_t_se);
            u1_t_stsbit = (U1)RTCIC_DRV_STATE_NORMAL;
            break;

        case RTCIC_I2C_STATE_ABNORMAL:
            u1_t_stsbit = (U1)RTCIC_DRV_STATE_ABNORMAL;
            break;

        default:
            break;
    }

    return(u1_t_stsbit);
}
/*===================================================================================================================================*/
/*  U1      u1_s_RtcIc_RtclkReadWait(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_RtcIc_RtclkReadWait(void)
{

    U1                 u1_t_stsbit;

    u1_t_stsbit = (U1)RTCIC_DRV_TIMEOUT;

    if (u4_s_rtcic_drv_cycle_time != (U4)0) {
        u4_s_rtcic_drv_cycle_time--;
        u1_t_stsbit = (U1)RTCIC_DRV_TIMEWAIT;
    }

    return(u1_t_stsbit);
}
/*===================================================================================================================================*/
/*  U1      u1_s_RtcIc_I2cStateCheck(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_RtcIc_I2cStateCheck(void)
{
    U1                 u1_t_stsbit;

    u1_t_stsbit = u1_s_RtcIc_i2c_comstate;

    if (u1_t_stsbit == (U1)RTCIC_I2C_STATE_RETRY) {
        u1_t_stsbit = (U1)RTCIC_I2C_STATE_EXECUTION;
    }

    if ((u1_t_stsbit == (U1)RTCIC_I2C_STATE_NORMAL) ||
        (u1_t_stsbit == (U1)RTCIC_I2C_STATE_ABNORMAL)) {
        u1_s_RtcIc_i2c_comstate = (U1)RTCIC_I2C_STATE_STOP;
    }

    return(u1_t_stsbit);
}


/*===================================================================================================================================*/
/*  void    vd_g_RtcIc_RtclkRtartReq(const U4 u4_a_settime)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_RtcIc_RtclkRtartReq(const U4 u4_a_settime)
{
    u4_s_rtcic_drv_real_time = u4_a_settime;
    u1_s_rtcic_drv_rt_set_req = (U1)RTCIC_DRV_INITIAL_REQ_ON;
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
        case RTCIC_DEV_IC_NORMAL:
            u1_t_stsbit = (U1)RTCIC_RTC_NORMAL;
            break;
        case RTCIC_DEV_IC_I2C_ERROR:
            u1_t_stsbit = (U1)RTCIC_I2C_ERROR;
            break;
        case RTCIC_DEV_IC_NONINITIAL:
        case RTCIC_DEV_IC_RESET:
        default:
            u1_t_stsbit = (U1)RTCIC_RTC_INITIAL;
            break;
    }

    return(u1_t_stsbit);
}
/*===================================================================================================================================*/
/*  void    vd_g_RtcIc_RtclkProv(U4* u4_a_realtime)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_RtcIc_RtclkProv(U4* u4_a_realtime)
{
    *u4_a_realtime = u4_s_rtcic_drv_real_time;
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
