/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "PowerIcCtl.h"

#include "poweric.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define POWERIC_TASK_TIME                   (1U)

#define POWERIC_SEQ_IDLE                    (0U)
#define POWERIC_SEQ_CYC                     (1U)
#define POWERIC_SEQ_FAIL_SAFE               (2U)

#define POWERIC_SPEAKER_IDX_NUM             (4U)            /* Power-IC Maximum Number of Speaker Installations */
#define POWERIC_SPEAKER_IDX_FL              (0U)            /* Power-IC Speaker FL Index */
#define POWERIC_SPEAKER_IDX_FR              (1U)            /* Power-IC Speaker FR Index */
#define POWERIC_SPEAKER_IDX_RL              (2U)            /* Power-IC Speaker RL Index */
#define POWERIC_SPEAKER_IDX_RR              (3U)            /* Power-IC Speaker RR Index */

#define POWERIC_OVERCUR_THD_VAL_BEF_AMPON   (0x0F3U)        /* Power-IC Overcurrent Threshold Value Before AmpOn Setting */
#define POWERIC_OVERCUR_THD_VAL_AFT_AMPON   (0x7E9U)        /* Power-IC Overcurrent Threshold Value After AmpOn Setting */
#define POWERIC_OVERCUR_CNT                 (5U)            /* Power-IC Overcurrent Detection Count */

#define POWERIC_DIAG_JUGE_STS_NML           (0U)            /* Power-IC Diag Register Judge Status : Normal */
#define POWERIC_DIAG_JUGE_STS_FAIL          (1U)            /* Power-IC Diag Register Judge Status : Fail */

#define POWERIC_DIAG_FAIL_THD_VAL_TURNON    (0x27U)         /* Power-IC Diag Fail Threshold Value For TurnOn */
#define POWERIC_DIAG_FAIL_THD_VAL_CYCLIC    (0x23U)         /* Power-IC Diag Fail Threshold Value For Cyclic */

#define POWERIC_TURNONDIAG_STEP0            (0U)
#define POWERIC_TURNONDIAG_STEP1            (1U)
#define POWERIC_TURNONDIAG_STEP2            (2U)
#define POWERIC_TURNONDIAG_STEP3            (3U)
#define POWERIC_TURNONDIAG_STEP4            (4U)
#define POWERIC_TURNONDIAG_STEP5            (5U)
#define POWERIC_TURNONDIAG_STEP6            (6U)
#define POWERIC_TURNONDIAG_STEP7            (7U)
#define POWERIC_TURNONDIAG_STEP8            (8U)
#define POWERIC_TURNONDIAG_STEP9            (9U)
#define POWERIC_TURNONDIAG_STEP10           (10U)

#define POWERIC_TURNONDIAG_MUTE_MASK        (0x18U)         /* Power-IC IB2 Register MUTE Setting Bit MasK */
#define POWERIC_TURNONDIAG_INVALID_CNT      (3U)            /* Power-IC Turn On Diag DB0[0x90].D6 Invaild Count */
#define POWERIC_TURNONDIAG_DREC_OFFSET      (1U)            /* Power-IC Turn On Diag Drec Factor Speaker Output Offset Fail */
#define POWERIC_TURNONDIAG_DREC_OPEN_FL     (2U)            /* Power-IC Turn On Diag Drec Factor FL Speaker Open */
#define POWERIC_TURNONDIAG_DREC_OPEN_FR     (3U)            /* Power-IC Turn On Diag Drec Factor FR Speaker Open */
#define POWERIC_TURNONDIAG_DREC_OPEN_RL     (4U)            /* Power-IC Turn On Diag Drec Factor RL Speaker Open */
#define POWERIC_TURNONDIAG_DREC_OPEN_RR     (5U)            /* Power-IC Turn On Diag Drec Factor RR Speaker Open */
#define POWERIC_TURNONDIAG_DREC_SHORT       (6U)            /* Power-IC Turn On Diag Drec Factor Speaker Short */

#define POWERIC_DIAGCYC_STSCONF_CNT         (5U)            /* Power-IC Diag Cycle Diag State Confirmation Count */

#define POWERIC_TEMPCYC_VCCFAIL_VAL         (0x50U)         /* Power-IC Temp Cycle Check Vcc Fail Value */

#define POWERIC_FAILSAFE_STEP0              (0U)
#define POWERIC_FAILSAFE_STEP1              (1U)

#define POWERIC_FAILSAFE_FACT_NUM           (5U)
#define POWERIC_FAILSAFE_FACT_OVERCUR       (0U)            /* Power-IC Fail Safe Factor Overcurrent */
#define POWERIC_FAILSAFE_FACT_I2CFAIL       (1U)            /* Power-IC Fail Safe Factor I2C Access Fail */
#define POWERIC_FAILSAFE_FACT_DIAG_OFFSET   (2U)            /* Power-IC Fail Safe Factor Speaker Output Offset Fail */
#define POWERIC_FAILSAFE_FACT_DIAG_SHORT    (3U)            /* Power-IC Fail Safe Factor Speaker Short */
#define POWERIC_FAILSAFE_FACT_HIGHTEMP      (4U)            /* Power-IC Fail Safe Factor High Temperature */

#define POWERIC_I2CFAIL_DEVICESTOP_CNT      (5U)            /* Power-IC I2c Fail Device Stop Count */

#define POWERIC_SOFTMUTESET_STEP0           (0U)
#define POWERIC_SOFTMUTESET_STEP1           (1U)

#define POWERIC_TURNON_MUTE_SET_WRINUM      (1U)
#define POWERIC_TURNON_DIAGMODE_SET_WRINUM  (1U)
#define POWERIC_TURNON_AMPONOFF_SET_WRINUM  (1U)
#define POWERIC_SOFTMUTE_SET_WRINUM         (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1 u1_s_poweric_state;                                   /* Power-IC State */ /* 暫定 +Bon保持 */

static U2 u2_s_poweric_v33_peri_on_wait_timer;                  /* Power-IC V33-PERI-ON = High Wait Timer */
static U2 u2_s_poweric_overcurchk_timer;                        /* Power-IC Overcurrent Check Poling Timer */
static U2 u2_s_poweric_i2ccycchk_timer;                         /* Power-IC I2C Cycle Check Poling Timer */

static U2 u2_s_poweric_regstep;                                 /* Power-IC Register Request Step */
static U4 u4_s_poweric_i2c_ack_wait_time;                       /* Power-IC I2C Request Ack Wait Timer */
static U2 u2_s_poweric_reg_btwn_time;                           /* Power-IC Access Register Between Timer */

static U1 u1_s_poweric_diag_req_flag;                           /* Power-IC Diag Request Flag */
static U1 u1_s_poweric_overcurchk_flag;                         /* Power-IC Overcurrent Check Flag */
static U1 u1_s_poweric_overcurchk_stop_flag;                    /* Power-IC Overcurrent Check Stop_Flag */
static U1 u1_s_poweric_i2ccycchk_stop_flag;                     /* Power-IC I2c Cycle Check Stop Flag */
static U1 u1_s_poweric_v33_peri_on_high_flag;                   /* Power-IC V33-PERI-ON = High Flag */
static U1 u1_s_poweric_pre_v33_peri_on_sts;                     /* Power-IC Previous V33-PERI-ON Port Status */
static U1 u1_s_poweric_pre_p_on_sts;                            /* Power-IC Previous P-ON Port Status */

static U1 u1_s_poweric_overcur_cnt;                             /* Power-IC Overcurrent Counter */

static U1 u1_s_poweric_turnondiag_sts;                          /* Power-IC Turn On Diag Function Status */
static U1 u1_s_poweric_turnondiag_softmute_on_flag;             /* Power-IC Turn On Diag Soft Mute On Flag */
static U2 u2_s_poweric_turnon_wait_timer;                       /* Power-IC Turn On Diag Wait Timer */
static U1 u1_s_poweric_turnon_offset_invalid_cnt;               /* Power-IC Turn On Diag DB0[0x90].D6 Invaild Counter */
static U1 u1_s_poweric_turnon_diag_execution_flag;              /* Power-IC Turn On Diag Execution Flag */
static U2 u2_s_poweric_turnon_diag_execution_timer;             /* Power-IC Turn On Diag Execution Timeout Timer */

static U1 u1_s_poweric_i2c_regaccess_exe_flag;                  /* Power-IC I2c Register Access Excuting Flag */
static U4 u4_s_poweric_i2c_regaccess_pid;                       /* Power-IC I2c Register Accessing pid */

static U1 u1_s_poweric_softmuteset_sts;                         /* Power-IC Soft Mute Setting Function Status */
static U1 u1_s_poweric_softmute_set_flag;                       /* Power-IC Soft Mute Setting Flag */
static U1 u1_s_poweric_softmute_on_flag;                        /* Power-IC Soft Mute On Flag */
static U1 u1_s_poweric_softmute_reqsts;                         /* Power-IC Soft Mute Request Status */

static ST_POWERIC_DIAGCYC_READCNT st_poweric_diagcyc_readcnt[POWERIC_SPEAKER_IDX_NUM];  /* Power-IC Diag Cycle Check Register Read Status Counter */
static U1 u1_s_poweric_diagcyc_offset_nrml_recflag;             /* Power-IC Diag Cycle Check Offset DTC Status Normal Record Flag */
static U1 u1_s_poweric_diagcyc_short_nrml_recflag;              /* Power-IC Diag Cycle Check Short DTC Status Normal Record Flag */

static U1 u1_s_poweric_i2c_error_cnt;                           /* Power-IC I2C Error Counter */

static U1 u1_s_poweric_failsafe_sts;                            /* Power-IC Fail Safe Function Status */ /* 暫定 +Bon保持 */
static U1 u1_s_poweric_fail_safe_fact;                          /* Power-IC Fail Safe Factor */ /* 暫定 +Bon保持 */
static U2 u2_s_poweric_failsafe_wait_timer;                     /* Power-IC Fail Safe Wait Timer */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1 u1_s_PowerIc_TimChk(const U2 u2_a_tim_cnt, const U2 u2_a_wait_tim);
static void vd_s_PowerIc_CycChk(void);
static void vd_s_PowerIc_OverCurrentChk(void);
static void vd_s_PowerIc_TurnOnDiagFunc(void);
static U1   u1_s_PowerIc_I2cReadFunc(void);
static void vd_s_PowerIc_DiagCycChk(void);
static void vd_s_PowerIc_DiagCycStsCnt(const U1 u1_a_reg_data, const U1 u1_a_spk_idx);
static void vd_s_PowerIc_TempCycChk(void);
static void vd_s_PowerIc_FailSafeFunc(void);
static U1   u1_s_PowerIc_DiagOffsetJdg(const U1 u1_a_reg_data);
static U1   u1_s_PowerIc_DiagOpenJdg(const U1 u1_a_reg_data);
static U1   u1_s_PowerIc_DiagVccShrtJdg(const U1 u1_a_reg_data);
static U1   u1_s_PowerIc_DiagGndShrtJdg(const U1 u1_a_reg_data);
static U1 u1_s_PowerIc_I2cSetMgrFunc(const U2 u2_a_wri_max, const ST_REG_WRI_REQ * stp_a_wrireq, const ST_GP_I2C_MA_REQ * stp_a_setreg);
static U1 u1_s_PowerIc_I2cReadMgrFunc(const ST_GP_I2C_MA_REQ * stp_a_setreg);
static void vd_s_PowerIc_SoftMuteSetFunc(void);
static void vd_s_PowerIc_Memset(void * vdp_a_dst, const U1 u1_a_data, U4 u4_a_size);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U2 POWERIC_V33PERION_H_WAITTIME = (U2)(30U / POWERIC_TASK_TIME);       /* Power-IC V33-PERI-ON = High Wait Time t1 : 30ms */
static const U2 POWERIC_OVERCURRENTCHK_POLING = (U2)(10U / POWERIC_TASK_TIME);      /* Power-IC Overcurrent Check Poling Time t2 : 10ms */
static const U2 POWERIC_I2CCYCCHK_POLING = (U2)(30U / POWERIC_TASK_TIME);           /* Power-IC I2C Cycle Check Poling Time : 30ms */

static const U2 POWERIC_WAITTIME_50MS = (U2)(50U / POWERIC_TASK_TIME);              /* Power-IC Wait Time : 50ms */
static const U2 POWERIC_WAITTIME_60MS = (U2)(60U / POWERIC_TASK_TIME);              /* Power-IC Wait Time : 60ms */
static const U2 POWERIC_WAITTIME_100MS = (U2)(100U / POWERIC_TASK_TIME);            /* Power-IC Wait Time : 100ms */
static const U2 POWERIC_WAITTIME_300MS = (U2)(300U / POWERIC_TASK_TIME);            /* Power-IC Wait Time : 300ms */
static const U2 POWERIC_WAITTIME_3000MS = (U2)(3000U / POWERIC_TASK_TIME);          /* Power-IC Diag Execution Time : 3000ms */

static const ST_REG_WRI_REQ POWERIC_TURNON_MUTE_SET[POWERIC_TURNON_MUTE_SET_WRINUM] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};

static const ST_REG_WRI_REQ POWERIC_TURNON_DIAGMODE_SET[POWERIC_TURNON_DIAGMODE_SET_WRINUM] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};

static const ST_REG_WRI_REQ POWERIC_TURNON_AMPONOFF_SET[POWERIC_TURNON_AMPONOFF_SET_WRINUM] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};

static const ST_REG_WRI_REQ POWERIC_SOFTMUTE_SET[POWERIC_SOFTMUTE_SET_WRINUM] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};

const U1 u1_sp_POWERIC_CYCLE_DATA_RD_PDU1[POWERIC_I2C_RWC_BYTE2] = {
    (U1)POWERIC_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x90U     /* Write Address */
};

U1 u1_sp_POWERIC_CYCLE_DATA_RD_PDU2[POWERIC_I2C_RWC_BYTE9];

const U1 u1_sp_POWERIC_TURNON_DATA_RD1_PDU1[POWERIC_I2C_RWC_BYTE2] = {
    (U1)POWERIC_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x82U     /* Write Address */
};

U1 u1_sp_POWERIC_TURNON_DATA_RD1_PDU2[POWERIC_I2C_RWC_BYTE7];

U1 u1_sp_POWERIC_TURNON_MUTE_SET_PDU1[POWERIC_I2C_RWC_BYTE3];

U1 u1_sp_POWERIC_TURNON_DIAGMODE_SET_PDU1[POWERIC_I2C_RWC_BYTE3];

U1 u1_sp_POWERIC_TURNON_AMPONOFF_SET_PDU1[POWERIC_I2C_RWC_BYTE3];

const U1 u1_sp_POWERIC_TURNON_DATA_RD2_PDU1[POWERIC_I2C_RWC_BYTE2] = {
    (U1)POWERIC_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x90U     /* Write Address */
};

U1 u1_sp_POWERIC_TURNON_DATA_RD2_PDU2[POWERIC_I2C_RWC_BYTE2];

const U1 u1_sp_POWERIC_TURNON_DATA_RD3_PDU1[POWERIC_I2C_RWC_BYTE2] = {
    (U1)POWERIC_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x90U     /* Write Address */
};

U1 u1_sp_POWERIC_TURNON_DATA_RD3_PDU2[POWERIC_I2C_RWC_BYTE6];

const U1 u1_sp_POWERIC_SOFTMUTE_RD_PDU1[POWERIC_I2C_RWC_BYTE2] = {
    (U1)POWERIC_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x82U     /* Write Address */
};

U1 u1_sp_POWERIC_SOFTMUTE_RD_PDU2[POWERIC_I2C_RWC_BYTE2];

U1 u1_sp_POWERIC_SOFTMUTE_SET_PDU1[POWERIC_I2C_RWC_BYTE3];

const ST_GP_I2C_MA_REQ st_sp_POWERIC_CYCLE_DATA_RD_TBL[2] = {
    {
        (U1 *)&u1_sp_POWERIC_CYCLE_DATA_RD_PDU1[0],
        (U4)0x40000002U
    },
    {
        (U1 *)&u1_sp_POWERIC_CYCLE_DATA_RD_PDU2[0],
        (U4)0x40040009U
    }
};

const ST_GP_I2C_MA_REQ st_sp_POWERIC_TURNON_DATA_RD1_TBL[2] = {
    {
        (U1 *)&u1_sp_POWERIC_TURNON_DATA_RD1_PDU1[0],
        (U4)0x40080002U
    },
    {
        (U1 *)&u1_sp_POWERIC_TURNON_DATA_RD1_PDU2[0],
        (U4)0x400C0007U
    }
};

const ST_GP_I2C_MA_REQ st_sp_POWERIC_TURNON_MUTE_SET_TBL[1] = {
    {
        (U1 *)&u1_sp_POWERIC_TURNON_MUTE_SET_PDU1[0],
        (U4)0x40100003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_POWERIC_TURNON_DIAGMODE_SET_TBL[1] = {
    {
        (U1 *)&u1_sp_POWERIC_TURNON_DIAGMODE_SET_PDU1[0],
        (U4)0x40140003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_POWERIC_TURNON_AMPONOFF_SET_TBL[1] = {
    {
        (U1 *)&u1_sp_POWERIC_TURNON_AMPONOFF_SET_PDU1[0],
        (U4)0x40180003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_POWERIC_TURNON_DATA_RD2_TBL[2] = {
    {
        (U1 *)&u1_sp_POWERIC_TURNON_DATA_RD2_PDU1[0],
        (U4)0x401C0002U
    },
    {
        (U1 *)&u1_sp_POWERIC_TURNON_DATA_RD2_PDU2[0],
        (U4)0x40200002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_POWERIC_TURNON_DATA_RD3_TBL[2] = {
    {
        (U1 *)&u1_sp_POWERIC_TURNON_DATA_RD3_PDU1[0],
        (U4)0x40240002U
    },
    {
        (U1 *)&u1_sp_POWERIC_TURNON_DATA_RD3_PDU2[0],
        (U4)0x40280006U
    }
};

const ST_GP_I2C_MA_REQ st_sp_POWERIC_SOFTMUTE_RD_TBL[2] = {
    {
        (U1 *)&u1_sp_POWERIC_SOFTMUTE_RD_PDU1[0],
        (U4)0x402C0002U
    },
    {
        (U1 *)&u1_sp_POWERIC_SOFTMUTE_RD_PDU2[0],
        (U4)0x40300002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_POWERIC_SOFTMUTE_SET_TBL[1] = {
    {
        (U1 *)&u1_sp_POWERIC_SOFTMUTE_SET_PDU1[0],
        (U4)0x40340003U
    }
};

/*===================================================================================================================================*/
/*  void    vd_g_PowerIc_BonInit(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_PowerIc_BonInit(void)
{
    U2 u2_t_cnt;

    u1_s_poweric_state = (U1)POWERIC_SEQ_IDLE;

    u2_s_poweric_v33_peri_on_wait_timer = (U2)0;
    u2_s_poweric_overcurchk_timer = (U2)0;
    u2_s_poweric_i2ccycchk_timer = (U2)0;

    u2_s_poweric_regstep = (U2)0;
    u4_s_poweric_i2c_ack_wait_time = (U4)0;
    u2_s_poweric_reg_btwn_time = (U2)0xFFFFU;

    u1_s_poweric_diag_req_flag = (U1)FALSE;
    u1_s_poweric_overcurchk_flag = (U1)FALSE;
    u1_s_poweric_overcurchk_stop_flag = (U1)FALSE;
    u1_s_poweric_i2ccycchk_stop_flag = (U1)FALSE;
    u1_s_poweric_v33_peri_on_high_flag = (U1)FALSE;
    u1_s_poweric_pre_v33_peri_on_sts = (U1)POWERIC_IO_STS_LOW;
    u1_s_poweric_pre_p_on_sts = (U1)POWERIC_IO_STS_LOW;

    u1_s_poweric_overcur_cnt = (U4)0;

    u1_s_poweric_turnondiag_sts = (U1)POWERIC_TURNONDIAG_STEP0;
    u1_s_poweric_turnondiag_softmute_on_flag = (U1)FALSE;
    u2_s_poweric_turnon_wait_timer = (U2)0;
    u1_s_poweric_turnon_offset_invalid_cnt = (U1)0;
    u1_s_poweric_turnon_diag_execution_flag = (U1)FALSE;
    u2_s_poweric_turnon_diag_execution_timer = (U2)0;

    u1_s_poweric_i2c_regaccess_exe_flag = (U1)FALSE;
    u4_s_poweric_i2c_regaccess_pid = (U4)POWERIC_I2C_PID_INVALID;

    u1_s_poweric_softmuteset_sts = (U1)POWERIC_SOFTMUTESET_STEP0;
    u1_s_poweric_softmute_set_flag = (U1)FALSE;
    u1_s_poweric_softmute_on_flag = (U1)FALSE;
    u1_s_poweric_softmute_reqsts = (U1)POWERIC_SOFTMUTE_STS_OFF;

    vd_s_PowerIc_Memset(&st_poweric_diagcyc_readcnt, (U1)0U, sizeof(st_poweric_diagcyc_readcnt));
    u1_s_poweric_diagcyc_offset_nrml_recflag = (U1)FALSE;
    u1_s_poweric_diagcyc_short_nrml_recflag = (U1)FALSE;

    u1_s_poweric_i2c_error_cnt = (U1)0;

    u1_s_poweric_failsafe_sts = (U1)POWERIC_FAILSAFE_STEP0;
    u1_s_poweric_fail_safe_fact = (U1)POWERIC_FAILSAFE_FACT_NUM;
    u2_s_poweric_failsafe_wait_timer = (U2)0;

    /*  データリード用テーブル(BurstRead)初期化 */
    u1_sp_POWERIC_CYCLE_DATA_RD_PDU2[0] = (U1)POWERIC_I2C_SLAVEADR_RD;    /* Slave Address */
    for(u2_t_cnt = (U2)1U; u2_t_cnt < (U2)POWERIC_I2C_RWC_BYTE9; u2_t_cnt++) {
        u1_sp_POWERIC_CYCLE_DATA_RD_PDU2[u2_t_cnt] = (U1)0U;    /* 読出しデータ初期値 */
    }

    /*  データリード用テーブル(BurstRead)初期化 */
    u1_sp_POWERIC_TURNON_DATA_RD1_PDU2[0] = (U1)POWERIC_I2C_SLAVEADR_RD;    /* Slave Address */
    for(u2_t_cnt = (U2)1U; u2_t_cnt < (U2)POWERIC_I2C_RWC_BYTE7; u2_t_cnt++) {
        u1_sp_POWERIC_TURNON_DATA_RD1_PDU2[u2_t_cnt] = (U1)0U;    /* 読出しデータ初期値 */
    }

    /* MUTE設定用 書込み用テーブル(Data可変)初期化 */
    u1_sp_POWERIC_TURNON_MUTE_SET_PDU1[0] = (U1)POWERIC_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_POWERIC_TURNON_MUTE_SET_PDU1[1] = (U1)0x82U;    /* Write Address */
    u1_sp_POWERIC_TURNON_MUTE_SET_PDU1[2] = (U1)0U;    /* Write Data初期値(定期処理内で更新) */

    /* Diagモード設定用 書込み用テーブル(Data可変)初期化 */
    u1_sp_POWERIC_TURNON_DIAGMODE_SET_PDU1[0] = (U1)POWERIC_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_POWERIC_TURNON_DIAGMODE_SET_PDU1[1] = (U1)0x84U;    /* Write Address */
    u1_sp_POWERIC_TURNON_DIAGMODE_SET_PDU1[2] = (U1)0U;    /* Write Data初期値(定期処理内で更新) */

    /* Amp ON/OFF設定用 書込み用テーブル(Data可変)初期化 */
    u1_sp_POWERIC_TURNON_AMPONOFF_SET_PDU1[0] = (U1)POWERIC_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_POWERIC_TURNON_AMPONOFF_SET_PDU1[1] = (U1)0x87U;    /* Write Address */
    u1_sp_POWERIC_TURNON_AMPONOFF_SET_PDU1[2] = (U1)0U;    /* Write Data初期値(定期処理内で更新) */

    /*  データリード用テーブル初期化 */
    u1_sp_POWERIC_TURNON_DATA_RD2_PDU2[0] = (U1)POWERIC_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_POWERIC_TURNON_DATA_RD2_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル(BurstRead)初期化 */
    u1_sp_POWERIC_TURNON_DATA_RD3_PDU2[0] = (U1)POWERIC_I2C_SLAVEADR_RD;    /* Slave Address */
    for(u2_t_cnt = (U2)1U; u2_t_cnt < (U2)POWERIC_I2C_RWC_BYTE6; u2_t_cnt++) {
        u1_sp_POWERIC_TURNON_DATA_RD3_PDU2[u2_t_cnt] = (U1)0U;    /* 読出しデータ初期値 */
    }

    /*  データリード用テーブル初期化 */
    u1_sp_POWERIC_SOFTMUTE_RD_PDU2[0] = (U1)POWERIC_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_POWERIC_SOFTMUTE_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /* MUTE設定用 書込み用テーブル(Data可変)初期化 */
    u1_sp_POWERIC_SOFTMUTE_SET_PDU1[0] = (U1)POWERIC_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_POWERIC_SOFTMUTE_SET_PDU1[1] = (U1)0x82U;    /* Write Address */
    u1_sp_POWERIC_SOFTMUTE_SET_PDU1[2] = (U1)0U;    /* Write Data初期値(定期処理内で更新) */
}

/*===================================================================================================================================*/
/*  void    vd_g_PowerIc_WkupInit(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_PowerIc_WkupInit(void)
{
    U2 u2_t_cnt;

    u2_s_poweric_v33_peri_on_wait_timer = (U2)0;
    u2_s_poweric_overcurchk_timer = (U2)0;
    u2_s_poweric_i2ccycchk_timer = (U2)0;

    u2_s_poweric_regstep = (U2)0;
    u4_s_poweric_i2c_ack_wait_time = (U4)0;
    u2_s_poweric_reg_btwn_time = (U2)0xFFFFU;

    u1_s_poweric_diag_req_flag = (U1)FALSE;
    u1_s_poweric_overcurchk_flag = (U1)FALSE;
    u1_s_poweric_overcurchk_stop_flag = (U1)FALSE;
    u1_s_poweric_i2ccycchk_stop_flag = (U1)FALSE;
    u1_s_poweric_v33_peri_on_high_flag = (U1)FALSE;
    u1_s_poweric_pre_v33_peri_on_sts = (U1)POWERIC_IO_STS_LOW;
    u1_s_poweric_pre_p_on_sts = (U1)POWERIC_IO_STS_LOW;

    u1_s_poweric_overcur_cnt = (U4)0;

    u1_s_poweric_turnondiag_sts = (U1)POWERIC_TURNONDIAG_STEP0;
    u1_s_poweric_turnondiag_softmute_on_flag = (U1)FALSE;
    u2_s_poweric_turnon_wait_timer = (U2)0;
    u1_s_poweric_turnon_offset_invalid_cnt = (U1)0;
    u1_s_poweric_turnon_diag_execution_flag = (U1)FALSE;
    u2_s_poweric_turnon_diag_execution_timer = (U2)0;

    u1_s_poweric_i2c_regaccess_exe_flag = (U1)FALSE;
    u4_s_poweric_i2c_regaccess_pid = (U4)POWERIC_I2C_PID_INVALID;

    u1_s_poweric_softmuteset_sts = (U1)POWERIC_SOFTMUTESET_STEP0;
    u1_s_poweric_softmute_set_flag = (U1)FALSE;
    u1_s_poweric_softmute_on_flag = (U1)FALSE;
    u1_s_poweric_softmute_reqsts = (U1)POWERIC_SOFTMUTE_STS_OFF;

    vd_s_PowerIc_Memset(&st_poweric_diagcyc_readcnt, (U1)0U, sizeof(st_poweric_diagcyc_readcnt));
    u1_s_poweric_diagcyc_offset_nrml_recflag = (U1)FALSE;
    u1_s_poweric_diagcyc_short_nrml_recflag = (U1)FALSE;

    u1_s_poweric_i2c_error_cnt = (U1)0;

    u2_s_poweric_failsafe_wait_timer = (U2)0;

    /*  データリード用テーブル(BurstRead)初期化 */
    u1_sp_POWERIC_CYCLE_DATA_RD_PDU2[0] = (U1)POWERIC_I2C_SLAVEADR_RD;    /* Slave Address */
    for(u2_t_cnt = (U2)1U; u2_t_cnt < (U2)POWERIC_I2C_RWC_BYTE9; u2_t_cnt++) {
        u1_sp_POWERIC_CYCLE_DATA_RD_PDU2[u2_t_cnt] = (U1)0U;    /* 読出しデータ初期値 */
    }

    /*  データリード用テーブル(BurstRead)初期化 */
    u1_sp_POWERIC_TURNON_DATA_RD1_PDU2[0] = (U1)POWERIC_I2C_SLAVEADR_RD;    /* Slave Address */
    for(u2_t_cnt = (U2)1U; u2_t_cnt < (U2)POWERIC_I2C_RWC_BYTE7; u2_t_cnt++) {
        u1_sp_POWERIC_TURNON_DATA_RD1_PDU2[u2_t_cnt] = (U1)0U;    /* 読出しデータ初期値 */
    }

    /* MUTE設定用 書込み用テーブル(Data可変)初期化 */
    u1_sp_POWERIC_TURNON_MUTE_SET_PDU1[0] = (U1)POWERIC_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_POWERIC_TURNON_MUTE_SET_PDU1[1] = (U1)0x82U;    /* Write Address */
    u1_sp_POWERIC_TURNON_MUTE_SET_PDU1[2] = (U1)0U;    /* Write Data初期値(定期処理内で更新) */

    /* Diagモード設定用 書込み用テーブル(Data可変)初期化 */
    u1_sp_POWERIC_TURNON_DIAGMODE_SET_PDU1[0] = (U1)POWERIC_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_POWERIC_TURNON_DIAGMODE_SET_PDU1[1] = (U1)0x84U;    /* Write Address */
    u1_sp_POWERIC_TURNON_DIAGMODE_SET_PDU1[2] = (U1)0U;    /* Write Data初期値(定期処理内で更新) */

    /* Amp ON/OFF設定用 書込み用テーブル(Data可変)初期化 */
    u1_sp_POWERIC_TURNON_AMPONOFF_SET_PDU1[0] = (U1)POWERIC_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_POWERIC_TURNON_AMPONOFF_SET_PDU1[1] = (U1)0x87U;    /* Write Address */
    u1_sp_POWERIC_TURNON_AMPONOFF_SET_PDU1[2] = (U1)0U;    /* Write Data初期値(定期処理内で更新) */

    /*  データリード用テーブル初期化 */
    u1_sp_POWERIC_TURNON_DATA_RD2_PDU2[0] = (U1)POWERIC_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_POWERIC_TURNON_DATA_RD2_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル(BurstRead)初期化 */
    u1_sp_POWERIC_TURNON_DATA_RD3_PDU2[0] = (U1)POWERIC_I2C_SLAVEADR_RD;    /* Slave Address */
    for(u2_t_cnt = (U2)1U; u2_t_cnt < (U2)POWERIC_I2C_RWC_BYTE6; u2_t_cnt++) {
        u1_sp_POWERIC_TURNON_DATA_RD3_PDU2[u2_t_cnt] = (U1)0U;    /* 読出しデータ初期値 */
    }

    /*  データリード用テーブル初期化 */
    u1_sp_POWERIC_SOFTMUTE_RD_PDU2[0] = (U1)POWERIC_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_POWERIC_SOFTMUTE_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /* MUTE設定用 書込み用テーブル(Data可変)初期化 */
    u1_sp_POWERIC_SOFTMUTE_SET_PDU1[0] = (U1)POWERIC_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_POWERIC_SOFTMUTE_SET_PDU1[1] = (U1)0x82U;    /* Write Address */
    u1_sp_POWERIC_SOFTMUTE_SET_PDU1[2] = (U1)0U;    /* Write Data初期値(定期処理内で更新) */
}

/*===================================================================================================================================*/
/*  void    vd_g_PowerIc_Routine(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_PowerIc_Routine(void)
{
    U1  u1_t_power_state;

    u1_t_power_state = u1_POWERIC_GET_POWER_STATE();

    switch (u1_s_poweric_state){
        case POWERIC_SEQ_IDLE:                                                      /* IDLE */
            /* Timer Clear */
            u2_s_poweric_overcurchk_timer = (U2)0;
            u2_s_poweric_i2ccycchk_timer = (U2)0;

            /* Power ON Check */
            if((u1_t_power_state == (U1)POWERIC_POWER_STATE_APP_OFF)
            || (u1_t_power_state == (U1)POWERIC_POWER_STATE_APP_ON)){           /* 暫定：見た目起動オフ or 見た目起動オン */
                /* State Update */
                u1_s_poweric_state = (U1)POWERIC_SEQ_CYC;
            }
            break;
        case POWERIC_SEQ_CYC:                                                       /* CYCLIC */
            vd_s_PowerIc_CycChk();
            break;
        case POWERIC_SEQ_FAIL_SAFE:                                                 /* FAIL_SAFE */
            vd_s_PowerIc_FailSafeFunc();
            break;
        default:                                                                    /* FAIL */
            vd_g_PowerIc_BonInit();
            break;
    }

    /* Ack Wait Timer Countr Increment */
    if(u4_s_poweric_i2c_ack_wait_time < (U4)U4_MAX){
        u4_s_poweric_i2c_ack_wait_time++;
    }
}

/*===================================================================================================================================*/
/*  U1    u1_s_PowerIc_TimChk(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u2_a_tim_cnt  :  Timer Count /  u2_a_wait_tim  :  Wait Time                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_PowerIc_TimChk(const U2 u2_a_tim_cnt, const U2 u2_a_wait_tim)
{
    U1  u1_t_ret;

    u1_t_ret = (U1)FALSE;
    if(u2_a_tim_cnt >= u2_a_wait_tim){
        u1_t_ret = (U1)TRUE;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  void    vd_s_PowerIc_CycChk(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PowerIc_CycChk(void)
{
    U1      u1_t_func_sts;                                          /* Function Status */
    U1      u1_t_time_chk_flg;
    U1      u1_t_v33_peri_on_sts;                                   /* V33-Peri-On Port Status */
    U1      u1_t_p_on_sts;                                          /* P-ON Port Status */

    if(u1_s_poweric_softmute_set_flag == (U1)TRUE){
        vd_s_PowerIc_SoftMuteSetFunc();
    }

    if((u1_s_poweric_diag_req_flag == (U1)TRUE)
    && (Mcu_OnStep_PowerIc_OVRALL == (U1)MCU_ONSTEP_P_IC_OVERALL_FIN)){
        vd_s_PowerIc_TurnOnDiagFunc();
    }

    u1_t_v33_peri_on_sts = u1_POWERIC_GET_V33_PERI_ON();
    if((u1_t_v33_peri_on_sts == (U1)POWERIC_IO_STS_HIGH)
    && (u1_s_poweric_pre_v33_peri_on_sts == (U1)POWERIC_IO_STS_LOW)){
        u1_s_poweric_v33_peri_on_high_flag = (U1)TRUE;
    }
    else if(u1_t_v33_peri_on_sts == (U1)POWERIC_IO_STS_LOW){
        u1_s_poweric_v33_peri_on_high_flag = (U1)FALSE;
    }
    else{
        /* Nothing */
    }

    if(u1_s_poweric_v33_peri_on_high_flag == (U1)TRUE){
        u1_t_time_chk_flg = u1_s_PowerIc_TimChk(u2_s_poweric_v33_peri_on_wait_timer, POWERIC_V33PERION_H_WAITTIME);
        if(u1_t_time_chk_flg == (U1)TRUE){
            u1_s_poweric_overcurchk_flag = (U1)TRUE;
        }
        else{
            if(u2_s_poweric_v33_peri_on_wait_timer < (U2)U2_MAX){
                u2_s_poweric_v33_peri_on_wait_timer++;
            }
        }
    }

    u1_t_p_on_sts = u1_POWERIC_GET_P_ON();
    if(u1_s_poweric_overcurchk_flag == (U1)TRUE){
        if((u1_t_p_on_sts == (U1)POWERIC_IO_STS_LOW)
        && (u1_s_poweric_pre_p_on_sts == (U1)POWERIC_IO_STS_HIGH)){
            u1_s_poweric_overcurchk_flag = (U1)FALSE;
            u1_s_poweric_v33_peri_on_high_flag = (U1)FALSE;
            u2_s_poweric_v33_peri_on_wait_timer = (U2)0;
        }
        else{
            if(u1_s_poweric_overcurchk_stop_flag == (U1)FALSE){
                u1_t_time_chk_flg = u1_s_PowerIc_TimChk(u2_s_poweric_overcurchk_timer, POWERIC_OVERCURRENTCHK_POLING);
                if(u1_t_time_chk_flg == (U1)TRUE){
                    /* Poling Timer Clear */
                    u2_s_poweric_overcurchk_timer = (U2)0;

                    vd_s_PowerIc_OverCurrentChk();
                }
            }
            else{
                /* Poling Timer Clear */
                u2_s_poweric_overcurchk_timer = (U2)0;
            }
        }
    }
    else{
        /* Poling Timer Clear */
        u2_s_poweric_overcurchk_timer = (U2)0;
    }

    if(u1_s_poweric_i2ccycchk_stop_flag == (U1)FALSE){
        u1_t_time_chk_flg = u1_s_PowerIc_TimChk(u2_s_poweric_i2ccycchk_timer, POWERIC_I2CCYCCHK_POLING);
        if(u1_t_time_chk_flg == (U1)TRUE){
            u1_t_func_sts = u1_s_PowerIc_I2cReadFunc();
            if(u1_t_func_sts == (U1)TRUE){
                /* Poling Timer Clear */
                u2_s_poweric_i2ccycchk_timer = (U2)0;

                vd_s_PowerIc_DiagCycChk();
                vd_s_PowerIc_TempCycChk();
            }
        }
    }
    else{
        /* Poling Timer Clear */
        u2_s_poweric_i2ccycchk_timer = (U2)0;
    }

    /* Previous State Update */
    u1_s_poweric_pre_v33_peri_on_sts = u1_t_v33_peri_on_sts;
    u1_s_poweric_pre_p_on_sts = u1_t_p_on_sts;

    /* Ack Wait Timer Countr Increment */
    if(u4_s_poweric_i2c_ack_wait_time < (U4)U4_MAX){
        u4_s_poweric_i2c_ack_wait_time++;
    }
    /* Poling Check Timer Countr Increment */
    if(u2_s_poweric_overcurchk_timer < (U2)U2_MAX){
        u2_s_poweric_overcurchk_timer++;
    }
    if(u2_s_poweric_i2ccycchk_timer < (U2)U2_MAX){
        u2_s_poweric_i2ccycchk_timer++;
    }
}

/*===================================================================================================================================*/
/*  void    vd_s_PowerIc_OverCurrentChk(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PowerIc_OverCurrentChk(void)
{
    U1  u1_t_read_adc_sts;                                                          /* Read A/D Change Status */
    U2  u2_t_pic_current_det_val;                                                   /* PIC-CURRENT-DET A/D Value */
    U2  u2_t_overcurrent_thd_val;                                                   /* Overcurrent Threshold Value */

    u2_t_pic_current_det_val = (U1)FALSE;

    u1_t_read_adc_sts = u1_POWERIC_GET_PIC_CURRENT_DET(&u2_t_pic_current_det_val);
    if(u1_t_read_adc_sts == (U1)TRUE){
        if(Mcu_OnStep_PowerIc_OVRALL <= (U1)POWERIC_ONSTEP_OVERALL_2){             /* Before Amp On Setting */
            u2_t_overcurrent_thd_val = (U2)POWERIC_OVERCUR_THD_VAL_BEF_AMPON;
        }
        else{                                                                       /* After Amp On Setting */
            u2_t_overcurrent_thd_val = (U2)POWERIC_OVERCUR_THD_VAL_AFT_AMPON;
        }
        if(u2_t_pic_current_det_val >= u2_t_overcurrent_thd_val){                   /* Overcurrent Detection */
            u1_s_poweric_overcur_cnt++;

            if(u1_s_poweric_overcur_cnt >= (U1)POWERIC_OVERCUR_CNT){
            /* --------------- Overcurrent Cycle Check Stop --------------- */
                u1_s_poweric_overcurchk_stop_flag = (U1)TRUE;
            /* --------------- I2C Cycle Check Stop --------------- */
                u1_s_poweric_i2ccycchk_stop_flag = (U1)TRUE;
                /* Fail Safe */
                u1_s_poweric_fail_safe_fact = (U1)POWERIC_FAILSAFE_FACT_OVERCUR;
                /* State Update */
                u1_s_poweric_state = (U1)POWERIC_SEQ_FAIL_SAFE;
            }
        }
        else{
            /* Counter Clear */
            u1_s_poweric_overcur_cnt = (U1)0;
        }
    }
}

/*===================================================================================================================================*/
/*  void    vd_s_PowerIc_TurnOnDiagFunc(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PowerIc_TurnOnDiagFunc(void)
{
    U1      u1_t_time_chk_flg;
    U1      u1_t_reg_req_sts;                                       /* Register Read/Write Request Status */
    U1      u1_t_read_reg_data;                                     /* Read Register Data */
    U1      u1_t_read_reg_bit;                                      /* Read Register Bit Data */
    U1      u1_t_ib2_reg_data;                                      /* IB2 Register Data */
    U1      u1_t_ib4_reg_data;                                      /* IB2 Register Data */
    U1      u1_t_ib7_reg_data;                                      /* IB2 Register Data */
    U1      u1_t_speaker_type;                                      /* Speaker Type */
    U1      u1_t_diag_jdg_sts;                                      /* Diag Read Judge Status */

    switch (u1_s_poweric_turnondiag_sts){
        case POWERIC_TURNONDIAG_STEP0:                              /* STEP0 */
        /* --------------- I2C Cycle Check Stop --------------- */
        u1_s_poweric_i2ccycchk_stop_flag = (U1)TRUE;
        /* --------------- IB2 - IB7 Register Read --------------- */
            /* Read Register */
            u1_t_reg_req_sts = u1_s_PowerIc_I2cReadMgrFunc(st_sp_POWERIC_TURNON_DATA_RD1_TBL);
            if(u1_t_reg_req_sts == (U1)TRUE){
                u1_t_ib2_reg_data = st_sp_POWERIC_TURNON_DATA_RD1_TBL[1].u1p_pdu[1];                /* IB2[0x82] */
                u1_t_ib4_reg_data = st_sp_POWERIC_TURNON_DATA_RD1_TBL[1].u1p_pdu[3];                /* IB4[0x84] */
                u1_t_ib7_reg_data = st_sp_POWERIC_TURNON_DATA_RD1_TBL[1].u1p_pdu[6];                /* IB7[0x87] */
                u1_t_ib2_reg_data &= ~(U1)POWERIC_TURNONDIAG_MUTE_MASK;                             /* IB2 bit[4:3] = 0b00 */
                u1_t_ib4_reg_data &= ~(U1)POWERIC_REG_MASK_BIT_0;                                   /* IB4 bit[0] = 0b0 */
                u1_t_ib7_reg_data &= ~(U1)POWERIC_REG_MASK_BIT_0;                                   /* IB7 bit[0] = 0b0 */
                st_sp_POWERIC_TURNON_MUTE_SET_TBL[0].u1p_pdu[2] = u1_t_ib2_reg_data;                /* IB2 Register Write Data Set */
                st_sp_POWERIC_TURNON_DIAGMODE_SET_TBL[0].u1p_pdu[2] = u1_t_ib4_reg_data;            /* IB4 Register Write Data Set */
                st_sp_POWERIC_TURNON_AMPONOFF_SET_TBL[0].u1p_pdu[2] = u1_t_ib7_reg_data;            /* IB7 Register Write Data Set */

                /* Next Process */
                u1_s_poweric_turnondiag_sts = (U1)POWERIC_TURNONDIAG_STEP1;
            }
            break;
        case POWERIC_TURNONDIAG_STEP1:                              /* STEP1 */
            if(u1_s_poweric_softmute_on_flag == (U1)FALSE){         /* BU-DET-H Soft Mute Off */
        /* --------------- MUTE ON Setting --------------- */
                /* Set Register */
                u1_t_reg_req_sts = u1_s_PowerIc_I2cSetMgrFunc((U2)POWERIC_TURNON_MUTE_SET_WRINUM,
                                                              POWERIC_TURNON_MUTE_SET,
                                                              st_sp_POWERIC_TURNON_MUTE_SET_TBL);
                if(u1_t_reg_req_sts == (U1)TRUE){
                    /* Soft Mute Flag On */
                    u1_s_poweric_turnondiag_softmute_on_flag =  (U1)TRUE;
                    /* Wait Timer Start */
                    u2_s_poweric_turnon_wait_timer = (U1)1;
                    /* Next Process */
                    u1_s_poweric_turnondiag_sts = (U1)POWERIC_TURNONDIAG_STEP2;
                }
            }
            else{                                                   /* BU-DET-H Soft Mute Off */
                /* Soft Mute Process Skip */
                /* Soft Mute Flag On */
                u1_s_poweric_turnondiag_softmute_on_flag =  (U1)TRUE;
                /* Wait Timer Start */
                u2_s_poweric_turnon_wait_timer = (U1)1;
                /* Next Process */
                u1_s_poweric_turnondiag_sts = (U1)POWERIC_TURNONDIAG_STEP2;
            }
            break;
        case POWERIC_TURNONDIAG_STEP2:                              /* STEP2 */
        /* --------------- Wait 100ms --------------- */
            u1_t_time_chk_flg = u1_s_PowerIc_TimChk(u2_s_poweric_turnon_wait_timer, POWERIC_WAITTIME_100MS);
            if(u1_t_time_chk_flg == (U1)TRUE){
        /* --------------- Amp OFF Setting --------------- */
                /* Set Register */
                u1_t_reg_req_sts = u1_s_PowerIc_I2cSetMgrFunc((U2)POWERIC_TURNON_AMPONOFF_SET_WRINUM,
                                                              POWERIC_TURNON_AMPONOFF_SET,
                                                              st_sp_POWERIC_TURNON_AMPONOFF_SET_TBL);
                if(u1_t_reg_req_sts == (U1)TRUE){
                    /* Wait Timer Clear */
                    u2_s_poweric_turnon_wait_timer = (U2)0;
                    /* Next Process */
                    u1_s_poweric_turnondiag_sts = (U1)POWERIC_TURNONDIAG_STEP3;
                }
            }
            else{
                if(u2_s_poweric_turnon_wait_timer < (U2)U2_MAX){
                    u2_s_poweric_turnon_wait_timer++;
                }
            }
            break;
        case POWERIC_TURNONDIAG_STEP3:                              /* STEP3 */
        /* --------------- Diag Mode OFF Setting --------------- */
            /* Set Register */
            u1_t_reg_req_sts = u1_s_PowerIc_I2cSetMgrFunc((U2)POWERIC_TURNON_DIAGMODE_SET_WRINUM,
                                                          POWERIC_TURNON_DIAGMODE_SET,
                                                          st_sp_POWERIC_TURNON_DIAGMODE_SET_TBL);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Wait Timer Start */
                u2_s_poweric_turnon_wait_timer = (U1)1;
                /* Next Process */
                u1_s_poweric_turnondiag_sts = (U1)POWERIC_TURNONDIAG_STEP4;
            }
            break;
        case POWERIC_TURNONDIAG_STEP4:                              /* STEP4 */
        /* --------------- Wait 100ms --------------- */
            u1_t_time_chk_flg = u1_s_PowerIc_TimChk(u2_s_poweric_turnon_wait_timer, POWERIC_WAITTIME_100MS);
            if(u1_t_time_chk_flg == (U1)TRUE){
        /* --------------- Diag Mode ON Setting --------------- */
                st_sp_POWERIC_TURNON_DIAGMODE_SET_TBL[0].u1p_pdu[2] |= (U1)POWERIC_REG_MASK_BIT_0;  /* IB4 Register Write Data Set IB4 bit[0] = 0b1 */
                /* Set Register */
                u1_t_reg_req_sts = u1_s_PowerIc_I2cSetMgrFunc((U2)POWERIC_TURNON_DIAGMODE_SET_WRINUM,
                                                              POWERIC_TURNON_DIAGMODE_SET,
                                                              st_sp_POWERIC_TURNON_DIAGMODE_SET_TBL);
                if(u1_t_reg_req_sts == (U1)TRUE){
                    /* Wait Timer Start */
                    u2_s_poweric_turnon_wait_timer = (U1)1;
                    /* Diag Excution Flag ON */
                    u1_s_poweric_turnon_diag_execution_flag = (U1)TRUE;
                    /* Diag Excution Timer Start */
                    u2_s_poweric_turnon_diag_execution_timer = (U1)1;
                    /* Next Process */
                    u1_s_poweric_turnondiag_sts = (U1)POWERIC_TURNONDIAG_STEP5;
                }
            }
            else{
                if(u2_s_poweric_turnon_wait_timer < (U2)U2_MAX){
                    u2_s_poweric_turnon_wait_timer++;
                }
            }
            break;
        case POWERIC_TURNONDIAG_STEP5:                              /* STEP5 */
        /* --------------- Wait 300ms --------------- */
            u1_t_time_chk_flg = u1_s_PowerIc_TimChk(u2_s_poweric_turnon_wait_timer, POWERIC_WAITTIME_300MS);
            if(u1_t_time_chk_flg == (U1)TRUE){
        /* --------------- DB0[0x90] Register Read --------------- */
                /* Read Register */
                u1_t_reg_req_sts = u1_s_PowerIc_I2cReadMgrFunc(st_sp_POWERIC_TURNON_DATA_RD2_TBL);
                if(u1_t_reg_req_sts == (U1)TRUE){
                    /* Wait Timer Clear */
                    u2_s_poweric_turnon_wait_timer = (U2)0;

                    u1_t_read_reg_data = st_sp_POWERIC_TURNON_DATA_RD2_TBL[1].u1p_pdu[1];               /* DB0[0x90] */
                    u1_t_read_reg_bit = u1_t_read_reg_data & (U1)POWERIC_REG_MASK_BIT_6;                /* DB0 bit[6] */
                    if(u1_t_read_reg_bit == (U1)POWERIC_REG_MASK_BIT_6){                                /* DB0 bit[6] = 0b1 */
                        /* Diag Excution Flag OFF */
                        u1_s_poweric_turnon_diag_execution_flag = (U1)FALSE;

                        u1_t_read_reg_bit = u1_t_read_reg_data & (U1)POWERIC_REG_MASK_BIT_5;            /* DB0 bit[5] */
                        if(u1_t_read_reg_bit == (U1)0){                                                 /* DB0 bit[5] = 0b0 */
                            /* Invalid Counter Clear */
                            u1_s_poweric_turnon_offset_invalid_cnt = (U1)0;
                            /* Next Process */
                            u1_s_poweric_turnondiag_sts = (U1)POWERIC_TURNONDIAG_STEP6;
                        }
                        else{
                            u1_s_poweric_turnon_offset_invalid_cnt++;
                            if(u1_s_poweric_turnon_offset_invalid_cnt >= (U1)POWERIC_TURNONDIAG_INVALID_CNT){
                                /* 暫定 ログ出力 */
                                /* Invalid Counter Clear */
                                u1_s_poweric_turnon_offset_invalid_cnt = (U1)0;
                                /* Next Process */
                                u1_s_poweric_turnondiag_sts = (U1)POWERIC_TURNONDIAG_STEP8;
                            }
                            else{
                                /* Next Process */
                                u1_s_poweric_turnondiag_sts = (U1)POWERIC_TURNONDIAG_STEP3;
                            }
                        }
                    }
                    else{
                        u1_t_time_chk_flg = u1_s_PowerIc_TimChk(u2_s_poweric_turnon_diag_execution_timer, POWERIC_WAITTIME_3000MS);
                        if(u1_t_time_chk_flg == (U1)TRUE){
                            /* 暫定 ログ出力 */
                            /* Diag Excution Flag OFF */
                            u1_s_poweric_turnon_diag_execution_flag = (U1)FALSE;
                            /* Next Process */
                            u1_s_poweric_turnondiag_sts = (U1)POWERIC_TURNONDIAG_STEP8;
                        }
                    }
                }
            }
            else{
                if(u2_s_poweric_turnon_wait_timer < (U2)U2_MAX){
                    u2_s_poweric_turnon_wait_timer++;
                }
            }

            /* Diag Excution Timer Count */
            if(u1_s_poweric_turnon_diag_execution_flag == (U1)TRUE){
                if(u2_s_poweric_turnon_diag_execution_timer < (U2)U2_MAX){
                    u2_s_poweric_turnon_diag_execution_timer++;
                }
            }
            else{
                /* Timer Clear */
                u2_s_poweric_turnon_diag_execution_timer = (U1)0;
            }
            break;
        case POWERIC_TURNONDIAG_STEP6:                              /* STEP6 */
        /* --------------- Diag Mode OFF Setting --------------- */
            st_sp_POWERIC_TURNON_DIAGMODE_SET_TBL[0].u1p_pdu[2] &= ~(U1)POWERIC_REG_MASK_BIT_0;     /* IB4 Register Write Data Set IB4 bit[0] = 0b0 */

            /* Set Register */
            u1_t_reg_req_sts = u1_s_PowerIc_I2cSetMgrFunc((U2)POWERIC_TURNON_DIAGMODE_SET_WRINUM,
                                                          POWERIC_TURNON_DIAGMODE_SET,
                                                          st_sp_POWERIC_TURNON_DIAGMODE_SET_TBL);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_poweric_turnondiag_sts = (U1)POWERIC_TURNONDIAG_STEP7;
            }
            break;
        case POWERIC_TURNONDIAG_STEP7:                              /* STEP7 */
        /* --------------- DB1 - DB4 Register Read --------------- */
            /* Read Register */
            u1_t_reg_req_sts = u1_s_PowerIc_I2cReadMgrFunc(st_sp_POWERIC_TURNON_DATA_RD3_TBL);
            if(u1_t_reg_req_sts == (U1)TRUE){
                u1_t_speaker_type = (U1)POWERIC_SPEAKER_TYPE_4SPK;     //u1_POWERIC_GET_SPEAKER_TYPE();    /* 暫定 車パラI/F展開後に見直し 4SPK固定とする */
                /* Offset Sts Judge */
                u1_t_diag_jdg_sts = u1_s_PowerIc_DiagOffsetJdg(st_sp_POWERIC_TURNON_DATA_RD3_TBL[1].u1p_pdu[1]);    /* FL */
                u1_t_diag_jdg_sts |= u1_s_PowerIc_DiagOffsetJdg(st_sp_POWERIC_TURNON_DATA_RD3_TBL[1].u1p_pdu[3]);   /* FR */
                if(u1_t_speaker_type == (U1)POWERIC_SPEAKER_TYPE_4SPK){
                    u1_t_diag_jdg_sts |= u1_s_PowerIc_DiagOffsetJdg(st_sp_POWERIC_TURNON_DATA_RD3_TBL[1].u1p_pdu[2]);   /* RL */
                    u1_t_diag_jdg_sts |= u1_s_PowerIc_DiagOffsetJdg(st_sp_POWERIC_TURNON_DATA_RD3_TBL[1].u1p_pdu[4]);   /* RR */
                }
                if(u1_t_diag_jdg_sts == (U1)POWERIC_DIAG_JUGE_STS_FAIL){
                    /* Offset Fail DTC Record */
                    vd_POWERIC_DTC_REQ((U1)DTCCTL_DTCID_PWR_SHCT_DC, (U1)POWERIC_DTC_STS_FAIL);
                    /* 暫定 SPK出力オフセット異常ログを残す */
                    vd_POWERIC_DREC_REQ((U1)SYSECDRC_DREC_ID_3, (U1)POWERIC_TURNONDIAG_DREC_OFFSET, (U1)0x00U);
                }

                /* Open Sts Judge */
                u1_t_diag_jdg_sts = u1_s_PowerIc_DiagOpenJdg(st_sp_POWERIC_TURNON_DATA_RD3_TBL[1].u1p_pdu[1]);      /* FL */
                if(u1_t_diag_jdg_sts == (U1)POWERIC_DIAG_JUGE_STS_FAIL){
                    /* FL Open Fail DTC Record */
                    vd_POWERIC_DTC_REQ((U1)DTCCTL_DTCID_PWR_UNCN_LF, (U1)POWERIC_DTC_STS_FAIL);
                    /* 暫定 SPK FLオープン異常ログを残す */
                    vd_POWERIC_DREC_REQ((U1)SYSECDRC_DREC_ID_3, (U1)POWERIC_TURNONDIAG_DREC_OPEN_FL, (U1)0x00U);
                }
                u1_t_diag_jdg_sts = u1_s_PowerIc_DiagOpenJdg(st_sp_POWERIC_TURNON_DATA_RD3_TBL[1].u1p_pdu[3]);      /* FR */
                if(u1_t_diag_jdg_sts == (U1)POWERIC_DIAG_JUGE_STS_FAIL){
                    /* FR Open Fail DTC Record */
                    vd_POWERIC_DTC_REQ((U1)DTCCTL_DTCID_PWR_UNCN_RF, (U1)POWERIC_DTC_STS_FAIL);
                    /* 暫定 SPK FRオープン異常ログを残す */
                    vd_POWERIC_DREC_REQ((U1)SYSECDRC_DREC_ID_3, (U1)POWERIC_TURNONDIAG_DREC_OPEN_FR, (U1)0x00U);
                }
                if(u1_t_speaker_type == (U1)POWERIC_SPEAKER_TYPE_4SPK){
                    u1_t_diag_jdg_sts = u1_s_PowerIc_DiagOpenJdg(st_sp_POWERIC_TURNON_DATA_RD3_TBL[1].u1p_pdu[2]);      /* RL */
                    if(u1_t_diag_jdg_sts == (U1)POWERIC_DIAG_JUGE_STS_FAIL){
                        /* RL Open Fail DTC Record */
                        vd_POWERIC_DTC_REQ((U1)DTCCTL_DTCID_PWR_UNCN_LBD, (U1)POWERIC_DTC_STS_FAIL);
                        /* 暫定 SPK RLオープン異常ログを残す */
                        vd_POWERIC_DREC_REQ((U1)SYSECDRC_DREC_ID_3, (U1)POWERIC_TURNONDIAG_DREC_OPEN_RL, (U1)0x00U);
                    }
                    u1_t_diag_jdg_sts = u1_s_PowerIc_DiagOpenJdg(st_sp_POWERIC_TURNON_DATA_RD3_TBL[1].u1p_pdu[4]);      /* RR */
                    if(u1_t_diag_jdg_sts == (U1)POWERIC_DIAG_JUGE_STS_FAIL){
                        /* RR Open Fail DTC Record */
                        vd_POWERIC_DTC_REQ((U1)DTCCTL_DTCID_PWR_UNCN_RBD, (U1)POWERIC_DTC_STS_FAIL);
                        /* 暫定 SPK RRオープン異常ログを残す */
                        vd_POWERIC_DREC_REQ((U1)SYSECDRC_DREC_ID_3, (U1)POWERIC_TURNONDIAG_DREC_OPEN_RR, (U1)0x00U);
                    }
                }

                /* Short Sts Judge */
                u1_t_diag_jdg_sts = u1_s_PowerIc_DiagVccShrtJdg(st_sp_POWERIC_TURNON_DATA_RD3_TBL[1].u1p_pdu[1]);   /* FL */
                u1_t_diag_jdg_sts |= u1_s_PowerIc_DiagVccShrtJdg(st_sp_POWERIC_TURNON_DATA_RD3_TBL[1].u1p_pdu[3]);  /* FR */
                u1_t_diag_jdg_sts |= u1_s_PowerIc_DiagGndShrtJdg(st_sp_POWERIC_TURNON_DATA_RD3_TBL[1].u1p_pdu[1]);  /* FL */
                u1_t_diag_jdg_sts |= u1_s_PowerIc_DiagGndShrtJdg(st_sp_POWERIC_TURNON_DATA_RD3_TBL[1].u1p_pdu[3]);  /* FR */
                if(u1_t_speaker_type == (U1)POWERIC_SPEAKER_TYPE_4SPK){
                    u1_t_diag_jdg_sts |= u1_s_PowerIc_DiagVccShrtJdg(st_sp_POWERIC_TURNON_DATA_RD3_TBL[1].u1p_pdu[2]);  /* RL */
                    u1_t_diag_jdg_sts |= u1_s_PowerIc_DiagVccShrtJdg(st_sp_POWERIC_TURNON_DATA_RD3_TBL[1].u1p_pdu[4]);  /* RR */
                    u1_t_diag_jdg_sts |= u1_s_PowerIc_DiagGndShrtJdg(st_sp_POWERIC_TURNON_DATA_RD3_TBL[1].u1p_pdu[2]);  /* RL */
                    u1_t_diag_jdg_sts |= u1_s_PowerIc_DiagGndShrtJdg(st_sp_POWERIC_TURNON_DATA_RD3_TBL[1].u1p_pdu[4]);  /* RR */
                }
                if(u1_t_diag_jdg_sts == (U1)POWERIC_DIAG_JUGE_STS_FAIL){
                    /* Short Fail DTC Record */
                    vd_POWERIC_DTC_REQ((U1)DTCCTL_DTCID_PWR_SHCT, (U1)POWERIC_DTC_STS_FAIL);
                    /* 暫定 SPK短絡異常ログを残す */
                    vd_POWERIC_DREC_REQ((U1)SYSECDRC_DREC_ID_3, (U1)POWERIC_TURNONDIAG_DREC_SHORT, (U1)0x00U);
                }

                /* Next Process */
                u1_s_poweric_turnondiag_sts = (U1)POWERIC_TURNONDIAG_STEP8;
            }
            break;
        case POWERIC_TURNONDIAG_STEP8:                              /* STEP8 */
        /* --------------- Amp ON Setting --------------- */
            st_sp_POWERIC_TURNON_AMPONOFF_SET_TBL[0].u1p_pdu[2] |= (U1)POWERIC_REG_MASK_BIT_0;  /* IB7 Register Write Data Set IB7 bit[0] = 0b1 */

            /* Set Register */
            u1_t_reg_req_sts = u1_s_PowerIc_I2cSetMgrFunc((U2)POWERIC_TURNON_AMPONOFF_SET_WRINUM,
                                                          POWERIC_TURNON_AMPONOFF_SET,
                                                          st_sp_POWERIC_TURNON_AMPONOFF_SET_TBL);
            if(u1_t_reg_req_sts == (U1)TRUE){
        /* --------------- I2C Cycle Check Start --------------- */
                u1_s_poweric_i2ccycchk_stop_flag = (U1)FALSE;
                /* Wait Timer Start */
                u2_s_poweric_turnon_wait_timer = (U1)1;
                /* Next Process */
                u1_s_poweric_turnondiag_sts = (U1)POWERIC_TURNONDIAG_STEP9;
            }
            break;
        case POWERIC_TURNONDIAG_STEP9:                              /* STEP4 */
        /* --------------- Wait 60ms --------------- */
            u1_t_time_chk_flg = u1_s_PowerIc_TimChk(u2_s_poweric_turnon_wait_timer, POWERIC_WAITTIME_60MS);
            if(u1_t_time_chk_flg == (U1)TRUE){
        /* --------------- Diag Mode ON Setting --------------- */
                st_sp_POWERIC_TURNON_DIAGMODE_SET_TBL[0].u1p_pdu[2] |= (U1)POWERIC_REG_MASK_BIT_0;  /* IB4 Register Write Data Set IB4 bit[0] = 0b1 */
                /* Set Register */
                u1_t_reg_req_sts = u1_s_PowerIc_I2cSetMgrFunc((U2)POWERIC_TURNON_DIAGMODE_SET_WRINUM,
                                                              POWERIC_TURNON_DIAGMODE_SET,
                                                              st_sp_POWERIC_TURNON_DIAGMODE_SET_TBL);
                if(u1_t_reg_req_sts == (U1)TRUE){
                    /* Wait Timer Clear */
                    u2_s_poweric_turnon_wait_timer = (U2)0;
                    /* Next Process */
                    u1_s_poweric_turnondiag_sts = (U1)POWERIC_TURNONDIAG_STEP10;
                }
            }
            else{
                if(u2_s_poweric_turnon_wait_timer < (U2)U2_MAX){
                    u2_s_poweric_turnon_wait_timer++;
                }
            }
            break;
        case POWERIC_TURNONDIAG_STEP10:                             /* STEP10 */
            if(u1_s_poweric_softmute_on_flag == (U1)FALSE){         /* BU-DET-H Soft Mute Off */
        /* --------------- MUTE OFF Setting --------------- */
                st_sp_POWERIC_TURNON_MUTE_SET_TBL[0].u1p_pdu[2] |= (U1)POWERIC_TURNONDIAG_MUTE_MASK;    /* IB2 Register Write Data Set IB2 bit[4:3] = 0b11 */

                /* Set Register */
                u1_t_reg_req_sts = u1_s_PowerIc_I2cSetMgrFunc((U2)POWERIC_TURNON_MUTE_SET_WRINUM,
                                                              POWERIC_TURNON_MUTE_SET,
                                                              st_sp_POWERIC_TURNON_MUTE_SET_TBL);
                if(u1_t_reg_req_sts == (U1)TRUE){
                    /* Soft Mute Flag Off */
                    u1_s_poweric_turnondiag_softmute_on_flag = (U1)FALSE;
                    /* Flag Clear */
                    u1_s_poweric_diag_req_flag = (U1)FALSE;
                    /* Process Reset */
                    u1_s_poweric_turnondiag_sts = (U1)POWERIC_TURNONDIAG_STEP0;
                }
            }
            else{                                                   /* BU-DET-H Soft Mute On */
                /* Soft Mute Process Skip */
                /* Soft Mute Flag Off */
                u1_s_poweric_turnondiag_softmute_on_flag = (U1)FALSE;
                /* Flag Clear */
                u1_s_poweric_diag_req_flag = (U1)FALSE;
                /* Process Reset */
                u1_s_poweric_turnondiag_sts = (U1)POWERIC_TURNONDIAG_STEP0;
            }
            break;
        default:                                                    /* FAIL */
            /* Process Reset */
            u1_s_poweric_turnondiag_sts = (U1)POWERIC_TURNONDIAG_STEP0;
            break;
    }
}

/*===================================================================================================================================*/
/*  U1    u1_s_PowerIc_I2cReadFunc(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1   u1_s_PowerIc_I2cReadFunc(void)
{
    U1      u1_t_ret;                                               /* Function Completion Status  */
    U1      u1_t_reg_req_sts;                                       /* Register Read/Write Request Status */

    u1_t_ret = (U1)FALSE;

    /* Read Register */
    u1_t_reg_req_sts = u1_s_PowerIc_I2cReadMgrFunc(st_sp_POWERIC_CYCLE_DATA_RD_TBL);
    if(u1_t_reg_req_sts == (U1)TRUE){
        /* Function Completion */
        u1_t_ret = (U1)TRUE;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  void    vd_s_PowerIc_DiagCycChk(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PowerIc_DiagCycChk(void)
{
    U1      u1_t_speaker_type;                                      /* Speaker Type */

    u1_t_speaker_type = (U1)POWERIC_SPEAKER_TYPE_4SPK;     //u1_POWERIC_GET_SPEAKER_TYPE();    /* 暫定 車パラI/F展開後に見直し 4SPK固定とする */
    /* FL Speaker Check */
    vd_s_PowerIc_DiagCycStsCnt(st_sp_POWERIC_CYCLE_DATA_RD_TBL[1].u1p_pdu[2], (U1)POWERIC_SPEAKER_IDX_FL);
    /* FR Speaker Check */
    vd_s_PowerIc_DiagCycStsCnt(st_sp_POWERIC_CYCLE_DATA_RD_TBL[1].u1p_pdu[4], (U1)POWERIC_SPEAKER_IDX_FR);

    if(u1_t_speaker_type == (U1)POWERIC_SPEAKER_TYPE_4SPK){
        /* RL Speaker Check */
        vd_s_PowerIc_DiagCycStsCnt(st_sp_POWERIC_CYCLE_DATA_RD_TBL[1].u1p_pdu[3], (U1)POWERIC_SPEAKER_IDX_RL);
        /* RR Speaker Check */
        vd_s_PowerIc_DiagCycStsCnt(st_sp_POWERIC_CYCLE_DATA_RD_TBL[1].u1p_pdu[5], (U1)POWERIC_SPEAKER_IDX_RR);
    }
    else{
        /* RL Speaker Count Clear */
        vd_s_PowerIc_Memset(&st_poweric_diagcyc_readcnt[POWERIC_SPEAKER_IDX_RL], (U1)0U, sizeof(st_poweric_diagcyc_readcnt[POWERIC_SPEAKER_IDX_RL]));
        /* RR Speaker Count Clear */
        vd_s_PowerIc_Memset(&st_poweric_diagcyc_readcnt[POWERIC_SPEAKER_IDX_RR], (U1)0U, sizeof(st_poweric_diagcyc_readcnt[POWERIC_SPEAKER_IDX_RR]));
        /* Normal Count Set */
        st_poweric_diagcyc_readcnt[POWERIC_SPEAKER_IDX_RL].u1_offset_nml = (U1)POWERIC_DIAGCYC_STSCONF_CNT;
        st_poweric_diagcyc_readcnt[POWERIC_SPEAKER_IDX_RL].u1_vccshrt_nml = (U1)POWERIC_DIAGCYC_STSCONF_CNT;
        st_poweric_diagcyc_readcnt[POWERIC_SPEAKER_IDX_RL].u1_gndshrt_nml = (U1)POWERIC_DIAGCYC_STSCONF_CNT;
        st_poweric_diagcyc_readcnt[POWERIC_SPEAKER_IDX_RR].u1_offset_nml = (U1)POWERIC_DIAGCYC_STSCONF_CNT;
        st_poweric_diagcyc_readcnt[POWERIC_SPEAKER_IDX_RR].u1_vccshrt_nml = (U1)POWERIC_DIAGCYC_STSCONF_CNT;
        st_poweric_diagcyc_readcnt[POWERIC_SPEAKER_IDX_RR].u1_gndshrt_nml = (U1)POWERIC_DIAGCYC_STSCONF_CNT;
    }

    if((st_poweric_diagcyc_readcnt[POWERIC_SPEAKER_IDX_FL].u1_offset_fail >= (U1)POWERIC_DIAGCYC_STSCONF_CNT)
    || (st_poweric_diagcyc_readcnt[POWERIC_SPEAKER_IDX_FR].u1_offset_fail >= (U1)POWERIC_DIAGCYC_STSCONF_CNT)
    || (st_poweric_diagcyc_readcnt[POWERIC_SPEAKER_IDX_RL].u1_offset_fail >= (U1)POWERIC_DIAGCYC_STSCONF_CNT)
    || (st_poweric_diagcyc_readcnt[POWERIC_SPEAKER_IDX_RR].u1_offset_fail >= (U1)POWERIC_DIAGCYC_STSCONF_CNT)){
    /* --------------- I2C Cycle Check Stop --------------- */
        u1_s_poweric_i2ccycchk_stop_flag = (U1)TRUE;
        /* Fail Safe */
        u1_s_poweric_fail_safe_fact = (U1)POWERIC_FAILSAFE_FACT_DIAG_OFFSET;
        /* State Update */
        u1_s_poweric_state = (U1)POWERIC_SEQ_FAIL_SAFE;
    }

    if((st_poweric_diagcyc_readcnt[POWERIC_SPEAKER_IDX_FL].u1_offset_nml >= (U1)POWERIC_DIAGCYC_STSCONF_CNT)
    && (st_poweric_diagcyc_readcnt[POWERIC_SPEAKER_IDX_FR].u1_offset_nml >= (U1)POWERIC_DIAGCYC_STSCONF_CNT)
    && (st_poweric_diagcyc_readcnt[POWERIC_SPEAKER_IDX_RL].u1_offset_nml >= (U1)POWERIC_DIAGCYC_STSCONF_CNT)
    && (st_poweric_diagcyc_readcnt[POWERIC_SPEAKER_IDX_RR].u1_offset_nml >= (U1)POWERIC_DIAGCYC_STSCONF_CNT)){
        if(u1_s_poweric_diagcyc_offset_nrml_recflag == (U1)FALSE){  /* First Time Only */
            /* Offset Normal DTC Record */
            vd_POWERIC_DTC_REQ((U1)DTCCTL_DTCID_PWR_SHCT_DC, (U1)POWERIC_DTC_STS_NORMAL);
            /* Flag Updata */
            u1_s_poweric_diagcyc_offset_nrml_recflag = (U1)TRUE;
        }
    }

    if((st_poweric_diagcyc_readcnt[POWERIC_SPEAKER_IDX_FL].u1_vccshrt_fail >= (U1)POWERIC_DIAGCYC_STSCONF_CNT)
    || (st_poweric_diagcyc_readcnt[POWERIC_SPEAKER_IDX_FR].u1_vccshrt_fail >= (U1)POWERIC_DIAGCYC_STSCONF_CNT)
    || (st_poweric_diagcyc_readcnt[POWERIC_SPEAKER_IDX_RL].u1_vccshrt_fail >= (U1)POWERIC_DIAGCYC_STSCONF_CNT)
    || (st_poweric_diagcyc_readcnt[POWERIC_SPEAKER_IDX_RR].u1_vccshrt_fail >= (U1)POWERIC_DIAGCYC_STSCONF_CNT)
    || (st_poweric_diagcyc_readcnt[POWERIC_SPEAKER_IDX_FL].u1_gndshrt_fail >= (U1)POWERIC_DIAGCYC_STSCONF_CNT)
    || (st_poweric_diagcyc_readcnt[POWERIC_SPEAKER_IDX_FR].u1_gndshrt_fail >= (U1)POWERIC_DIAGCYC_STSCONF_CNT)
    || (st_poweric_diagcyc_readcnt[POWERIC_SPEAKER_IDX_RL].u1_gndshrt_fail >= (U1)POWERIC_DIAGCYC_STSCONF_CNT)
    || (st_poweric_diagcyc_readcnt[POWERIC_SPEAKER_IDX_RR].u1_gndshrt_fail >= (U1)POWERIC_DIAGCYC_STSCONF_CNT)){
    /* --------------- I2C Cycle Check Stop --------------- */
        u1_s_poweric_i2ccycchk_stop_flag = (U1)TRUE;
        /* Fail Safe */
        u1_s_poweric_fail_safe_fact = (U1)POWERIC_FAILSAFE_FACT_DIAG_SHORT;
        /* State Update */
        u1_s_poweric_state = (U1)POWERIC_SEQ_FAIL_SAFE;
    }

    if((st_poweric_diagcyc_readcnt[POWERIC_SPEAKER_IDX_FL].u1_vccshrt_nml >= (U1)POWERIC_DIAGCYC_STSCONF_CNT)
    && (st_poweric_diagcyc_readcnt[POWERIC_SPEAKER_IDX_FR].u1_vccshrt_nml >= (U1)POWERIC_DIAGCYC_STSCONF_CNT)
    && (st_poweric_diagcyc_readcnt[POWERIC_SPEAKER_IDX_RL].u1_vccshrt_nml >= (U1)POWERIC_DIAGCYC_STSCONF_CNT)
    && (st_poweric_diagcyc_readcnt[POWERIC_SPEAKER_IDX_RR].u1_vccshrt_nml >= (U1)POWERIC_DIAGCYC_STSCONF_CNT)
    && (st_poweric_diagcyc_readcnt[POWERIC_SPEAKER_IDX_FL].u1_gndshrt_nml >= (U1)POWERIC_DIAGCYC_STSCONF_CNT)
    && (st_poweric_diagcyc_readcnt[POWERIC_SPEAKER_IDX_FR].u1_gndshrt_nml >= (U1)POWERIC_DIAGCYC_STSCONF_CNT)
    && (st_poweric_diagcyc_readcnt[POWERIC_SPEAKER_IDX_RL].u1_gndshrt_nml >= (U1)POWERIC_DIAGCYC_STSCONF_CNT)
    && (st_poweric_diagcyc_readcnt[POWERIC_SPEAKER_IDX_RR].u1_gndshrt_nml >= (U1)POWERIC_DIAGCYC_STSCONF_CNT)){
        if(u1_s_poweric_diagcyc_short_nrml_recflag == (U1)FALSE){  /* First Time Only */
            /* Short Normal DTC Record */
            vd_POWERIC_DTC_REQ((U1)DTCCTL_DTCID_PWR_SHCT, (U1)POWERIC_DTC_STS_NORMAL);
            /* Flag Updata */
            u1_s_poweric_diagcyc_short_nrml_recflag = (U1)TRUE;
        }
    }
}

/*===================================================================================================================================*/
/*  U1    vd_s_PowerIc_DiagCycStsCnt(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u2_a_reg_data  :  Register Read Data /  u1_a_spk_idx  :  Speaker Index                                           */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PowerIc_DiagCycStsCnt(const U1 u1_a_reg_data, const U1 u1_a_spk_idx)
{
    U1      u1_t_diagexe_sts;                                       /* DBx.D4 Read Status  */
    U1      u1_t_diag_jdg_sts;                                      /* Diag Read Judge Status */

    u1_t_diagexe_sts = u1_a_reg_data & (U1)POWERIC_REG_MASK_BIT_4;  /* DBx.D4 */
    if(u1_t_diagexe_sts == (U1)POWERIC_REG_MASK_BIT_4){             /* DBx.D4 = 0b1 */
        /* Offset Sts Judge */
        u1_t_diag_jdg_sts = u1_s_PowerIc_DiagOffsetJdg(u1_a_reg_data);      /* DBx.D5 */
        if(u1_t_diag_jdg_sts == (U1)POWERIC_DIAG_JUGE_STS_FAIL){    /* Fail */
            if(st_poweric_diagcyc_readcnt[u1_a_spk_idx].u1_offset_fail < (U1)U1_MAX){
                st_poweric_diagcyc_readcnt[u1_a_spk_idx].u1_offset_fail++;
            }
            st_poweric_diagcyc_readcnt[u1_a_spk_idx].u1_offset_nml = (U1)0;
        }
        else{
            if(st_poweric_diagcyc_readcnt[u1_a_spk_idx].u1_offset_nml < (U1)U1_MAX){
                st_poweric_diagcyc_readcnt[u1_a_spk_idx].u1_offset_nml++;
            }
            st_poweric_diagcyc_readcnt[u1_a_spk_idx].u1_offset_fail = (U1)0;
        }
       /* Vcc-Short Sts Judge */
        u1_t_diag_jdg_sts = u1_s_PowerIc_DiagVccShrtJdg(u1_a_reg_data); /* DBx.D1 */
        if(u1_t_diag_jdg_sts == (U1)POWERIC_DIAG_JUGE_STS_FAIL){    /* Fail */
            if(st_poweric_diagcyc_readcnt[u1_a_spk_idx].u1_vccshrt_fail < (U1)U1_MAX){
                st_poweric_diagcyc_readcnt[u1_a_spk_idx].u1_vccshrt_fail++;
            }
            st_poweric_diagcyc_readcnt[u1_a_spk_idx].u1_vccshrt_nml = (U1)0;
        }
        else{
            if(st_poweric_diagcyc_readcnt[u1_a_spk_idx].u1_vccshrt_nml < (U1)U1_MAX){
                st_poweric_diagcyc_readcnt[u1_a_spk_idx].u1_vccshrt_nml++;
            }
            st_poweric_diagcyc_readcnt[u1_a_spk_idx].u1_vccshrt_fail = (U1)0;
        }
        /* Gnd-Short Sts Judge */
        u1_t_diag_jdg_sts = u1_s_PowerIc_DiagGndShrtJdg(u1_a_reg_data); /* DBx.D0 */
        if(u1_t_diag_jdg_sts == (U1)POWERIC_DIAG_JUGE_STS_FAIL){    /* Fail */
            if(st_poweric_diagcyc_readcnt[u1_a_spk_idx].u1_gndshrt_fail < (U1)U1_MAX){
                st_poweric_diagcyc_readcnt[u1_a_spk_idx].u1_gndshrt_fail++;
            }
            st_poweric_diagcyc_readcnt[u1_a_spk_idx].u1_gndshrt_nml = (U1)0;
        }
        else{
            if(st_poweric_diagcyc_readcnt[u1_a_spk_idx].u1_gndshrt_nml < (U1)U1_MAX){
                st_poweric_diagcyc_readcnt[u1_a_spk_idx].u1_gndshrt_nml++;
            }
            st_poweric_diagcyc_readcnt[u1_a_spk_idx].u1_gndshrt_fail = (U1)0;
        }
    }
    else{
        if(st_poweric_diagcyc_readcnt[u1_a_spk_idx].u1_offset_nml < (U1)U1_MAX){
            st_poweric_diagcyc_readcnt[u1_a_spk_idx].u1_offset_nml++;
        }
        if(st_poweric_diagcyc_readcnt[u1_a_spk_idx].u1_vccshrt_nml < (U1)U1_MAX){
            st_poweric_diagcyc_readcnt[u1_a_spk_idx].u1_vccshrt_nml++;
        }
        if(st_poweric_diagcyc_readcnt[u1_a_spk_idx].u1_gndshrt_nml < (U1)U1_MAX){
            st_poweric_diagcyc_readcnt[u1_a_spk_idx].u1_gndshrt_nml++;
        }
    }

    /* Normal State Confirmation */
    if(st_poweric_diagcyc_readcnt[u1_a_spk_idx].u1_offset_nml >= (U1)POWERIC_DIAGCYC_STSCONF_CNT){
        st_poweric_diagcyc_readcnt[u1_a_spk_idx].u1_offset_fail = (U1)0;
    }
    if(st_poweric_diagcyc_readcnt[u1_a_spk_idx].u1_vccshrt_nml >= (U1)POWERIC_DIAGCYC_STSCONF_CNT){
        st_poweric_diagcyc_readcnt[u1_a_spk_idx].u1_vccshrt_fail = (U1)0;
    }
    if(st_poweric_diagcyc_readcnt[u1_a_spk_idx].u1_gndshrt_nml >= (U1)POWERIC_DIAGCYC_STSCONF_CNT){
        st_poweric_diagcyc_readcnt[u1_a_spk_idx].u1_gndshrt_fail = (U1)0;
    }
}

/*===================================================================================================================================*/
/*  void    vd_s_PowerIc_TempCycChk(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PowerIc_TempCycChk(void)
{
    U1      u1_t_tw2_sts;                                           /* DB6[0x96].D6 Read Status  */
    U1      u1_t_vcc_val;                                           /* DB7[0x97] Read Status  */

    u1_t_tw2_sts = st_sp_POWERIC_CYCLE_DATA_RD_TBL[1].u1p_pdu[6] & (U1)POWERIC_REG_MASK_BIT_6;
    u1_t_vcc_val = st_sp_POWERIC_CYCLE_DATA_RD_TBL[1].u1p_pdu[7];
    if((u1_t_tw2_sts == (U1)POWERIC_REG_MASK_BIT_6)                 /* DB6[0x96].D6 = 0b1 */
    && (u1_t_vcc_val == (U1)POWERIC_TEMPCYC_VCCFAIL_VAL)){          /* DB7[0x97] = 0x50 */
        /* Fail Safe */
        u1_s_poweric_fail_safe_fact = (U1)POWERIC_FAILSAFE_FACT_HIGHTEMP;
        /* State Update */
        u1_s_poweric_state = (U1)POWERIC_SEQ_FAIL_SAFE;
    }
}

/*===================================================================================================================================*/
/*  void    vd_s_PowerIc_FailSafeFunc(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PowerIc_FailSafeFunc(void)
{
    U1      u1_t_time_chk_flg;

    switch (u1_s_poweric_failsafe_sts){
        case POWERIC_FAILSAFE_STEP0:                                /* STEP0 */
        /* --------------- P-IC Hard Mute --------------- */
            u1_POWERIC_SET_PM_SYS_MUTE_H();

            /* Wait Timer Start */
            u2_s_poweric_failsafe_wait_timer = (U1)1;
            /* Next Process */
            u1_s_poweric_failsafe_sts = (U1)POWERIC_FAILSAFE_STEP1;
            break;
        case POWERIC_FAILSAFE_STEP1:                                /* STEP1 */
        /* --------------- Wait 50ms --------------- */
            u1_t_time_chk_flg = u1_s_PowerIc_TimChk(u2_s_poweric_failsafe_wait_timer, POWERIC_WAITTIME_50MS);
            if(u1_t_time_chk_flg == (U1)TRUE){
                /* Wait Timer Clear */
                u2_s_poweric_failsafe_wait_timer = (U2)0;
        /* --------------- P-IC Standby --------------- */
                u1_POWERIC_SET_P_ON_L();
        /* --------------- P-IC Power Off --------------- */
                u1_POWERIC_SET_PIC_POFF_L();
                if(u1_s_poweric_fail_safe_fact == (U1)POWERIC_FAILSAFE_FACT_OVERCUR){
                    /* 暫定 P-IC破壊ログを残す(DTF記憶) */
                    vd_POWERIC_DREC_REQ((U1)SYSECDRC_DREC_ID_1, (U1)0x00U, (U1)0x00U);
                }
                else if(u1_s_poweric_fail_safe_fact == (U1)POWERIC_FAILSAFE_FACT_DIAG_OFFSET){
                    /* Offset Fail DTC Record */
                    vd_POWERIC_DTC_REQ((U1)DTCCTL_DTCID_PWR_SHCT_DC, (U1)POWERIC_DTC_STS_FAIL);
                }
                else if(u1_s_poweric_fail_safe_fact == (U1)POWERIC_FAILSAFE_FACT_DIAG_SHORT){
                    /* Short Fail DTC Record */
                    vd_POWERIC_DTC_REQ((U1)DTCCTL_DTCID_PWR_SHCT, (U1)POWERIC_DTC_STS_FAIL);
                }
                else if(u1_s_poweric_fail_safe_fact == (U1)POWERIC_FAILSAFE_FACT_I2CFAIL){
                    /* 暫定 P-IC異常ログを残す */
                    vd_POWERIC_DREC_REQ((U1)SYSECDRC_DREC_ID_2, (U1)0x00U, (U1)0x00U);
                    if(u1_s_poweric_i2c_error_cnt < (U1)POWERIC_I2CFAIL_DEVICESTOP_CNT){
                /* --------------- P-IC Hard Mute Off --------------- */
                        u1_POWERIC_SET_PM_SYS_MUTE_L();
                        /* 暫定 5s待機後起動処理再実施 */
                    }
                }
                else{
                    /* Nothing */
                }
                /* State Update */
                u1_s_poweric_state = (U1)POWERIC_SEQ_IDLE;
                /* Process Reset */
                u1_s_poweric_failsafe_sts = (U1)POWERIC_FAILSAFE_STEP0;
            }
            else{
                if(u2_s_poweric_failsafe_wait_timer < (U2)U2_MAX){
                    u2_s_poweric_failsafe_wait_timer++;
                }
            }
            break;
        default:                                                    /* FAIL */
            /* Process Reset */
            u1_s_poweric_failsafe_sts = (U1)POWERIC_FAILSAFE_STEP0;
            break;
    }
}

/*===================================================================================================================================*/
/*  U1    u1_s_PowerIc_DiagOffsetJdg(const U1 u1_a_reg_data)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1   u1_s_PowerIc_DiagOffsetJdg(const U1 u1_a_reg_data)
{
    U1      u1_t_ret;                                               /* Diag Read Judge Status */
    U1      u1_t_offset_sts;                                        /* DBx.D5 Read Status  */

    u1_t_offset_sts = u1_a_reg_data & (U1)POWERIC_REG_MASK_BIT_5;   /* DBx.D5 */
    if(u1_t_offset_sts == (U1)POWERIC_REG_MASK_BIT_5){              /* DBx.D5 = 0b1 */
        u1_t_ret = (U1)POWERIC_DIAG_JUGE_STS_FAIL;
    }
    else{
        u1_t_ret = (U1)POWERIC_DIAG_JUGE_STS_NML;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1    u1_s_PowerIc_DiagOpenJdg(const U1 u1_a_reg_data)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1   u1_s_PowerIc_DiagOpenJdg(const U1 u1_a_reg_data)
{
    U1      u1_t_ret;                                               /* Diag Read Judge Status */
    U1      u1_t_open_sts;                                          /* DBx.D2 Read Status  */

    u1_t_open_sts = u1_a_reg_data & (U1)POWERIC_REG_MASK_BIT_2;     /* DBx.D2 */
    if(u1_t_open_sts == (U1)POWERIC_REG_MASK_BIT_2){                /* DBx.D2 = 0b1 */
        u1_t_ret = (U1)POWERIC_DIAG_JUGE_STS_FAIL;
    }
    else{
        u1_t_ret = (U1)POWERIC_DIAG_JUGE_STS_NML;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1    u1_s_PowerIc_DiagVccShrtJdg(const U1 u1_a_reg_data)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1   u1_s_PowerIc_DiagVccShrtJdg(const U1 u1_a_reg_data)
{
    U1      u1_t_ret;                                               /* Diag Read Judge Status */
    U1      u1_t_vcc_short_sts;                                     /* DBx.D1 Read Status  */

    u1_t_vcc_short_sts = u1_a_reg_data & (U1)POWERIC_REG_MASK_BIT_1;    /* DBx.D1 */
    if(u1_t_vcc_short_sts == (U1)POWERIC_REG_MASK_BIT_1){               /* DBx.D1 = 0b1 */
        u1_t_ret = (U1)POWERIC_DIAG_JUGE_STS_FAIL;
    }
    else{
        u1_t_ret = (U1)POWERIC_DIAG_JUGE_STS_NML;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1    u1_s_PowerIc_DiagGndShrtJdg(const U1 u1_a_reg_data)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1   u1_s_PowerIc_DiagGndShrtJdg(const U1 u1_a_reg_data)
{
    U1      u1_t_ret;                                               /* Diag Read Judge Status */
    U1      u1_t_gnd_short_sts;                                     /* DBx.D0 Read Status  */

    u1_t_gnd_short_sts = u1_a_reg_data & (U1)POWERIC_REG_MASK_BIT_0;    /* DBx.D0 */
    if(u1_t_gnd_short_sts == (U1)POWERIC_REG_MASK_BIT_0){               /* DBx.D0 = 0b1 */
        u1_t_ret = (U1)POWERIC_DIAG_JUGE_STS_FAIL;
    }
    else{
        u1_t_ret = (U1)POWERIC_DIAG_JUGE_STS_NML;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  void    vd_g_PowerIc_OutCtl_SetReq(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_PowerIc_TrunOnDiag_Req(void)
{
    u1_s_poweric_diag_req_flag = (U1)TRUE;
}

/*===================================================================================================================================*/
/*  U1    u1_s_PowerIc_I2cSetMgrFunc(const U2 u2_a_wri_max, const ST_REG_WRI_REQ * stp_a_wrireq,                                     */
/*                                   const ST_GP_I2C_MA_REQ * stp_a_setreg)                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_softmute_sts  :  Soft Mute Setting Status ON/OFF                                                            */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_PowerIc_I2cSetMgrFunc(const U2 u2_a_wri_max, const ST_REG_WRI_REQ * stp_a_wrireq, const ST_GP_I2C_MA_REQ * stp_a_setreg)
{
    U1      u1_t_ret;
    U4      u4_t_pid;                                               /* Register Access PID  */
    U1      u1_t_reg_req_sts;                                       /* Register Read/Write Request Status */

    u1_t_ret = (U1)FALSE;

    u4_t_pid = stp_a_setreg->u4_cbf & (U4)POWERIC_I2C_PID_MASK;
    if((u1_s_poweric_i2c_regaccess_exe_flag == (U1)FALSE)
    || (u4_t_pid == u4_s_poweric_i2c_regaccess_pid)){
        /* I2C Access Flag On */
        u1_s_poweric_i2c_regaccess_exe_flag = (U1)TRUE;
        /* I2C Accessing PID Updata */
        u4_s_poweric_i2c_regaccess_pid = u4_t_pid;
        /* Set Register */
        u1_t_reg_req_sts = u1_POWERIC_I2C_CTRL_REGSET(&u2_s_poweric_regstep, (U2)u2_a_wri_max,
                                                      stp_a_wrireq, &u4_s_poweric_i2c_ack_wait_time,
                                                      stp_a_setreg, &u2_s_poweric_reg_btwn_time);
        if(u1_t_reg_req_sts == (U1)TRUE){
            /* I2C Access Flag Off */
            u1_s_poweric_i2c_regaccess_exe_flag = (U1)FALSE;
            /* I2C Accessing PID Clear */
            u4_s_poweric_i2c_regaccess_pid = (U4)POWERIC_I2C_PID_INVALID;
            /* Function Completion */
            u1_t_ret = (U1)TRUE;
        }
    }

    /* 暫定 I2Cタイムアウト処理(PID保持値異常含む) */

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1    u1_s_PowerIc_I2cReadMgrFunc(const ST_GP_I2C_MA_REQ * stp_a_setreg)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_softmute_sts  :  Soft Mute Setting Status ON/OFF                                                            */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_PowerIc_I2cReadMgrFunc(const ST_GP_I2C_MA_REQ * stp_a_setreg)
{
    U1      u1_t_ret;
    U4      u4_t_pid;                                               /* Register Access PID  */
    U1      u1_t_reg_req_sts;                                       /* Register Read/Write Request Status */

    u1_t_ret = (U1)FALSE;

    u4_t_pid = stp_a_setreg->u4_cbf & (U4)POWERIC_I2C_PID_MASK;
    if((u1_s_poweric_i2c_regaccess_exe_flag == (U1)FALSE)
    || (u4_t_pid == u4_s_poweric_i2c_regaccess_pid)){
        /* I2C Access Flag On */
        u1_s_poweric_i2c_regaccess_exe_flag = (U1)TRUE;
        /* I2C Accessing PID Updata */
        u4_s_poweric_i2c_regaccess_pid = u4_t_pid;
        /* Read Register */
         u1_t_reg_req_sts = u1_POWERIC_I2C_CTRL_REGREAD(&u2_s_poweric_regstep, &u4_s_poweric_i2c_ack_wait_time,
                                                        stp_a_setreg, &u2_s_poweric_reg_btwn_time);
        if(u1_t_reg_req_sts == (U1)TRUE){
            /* I2C Access Flag Off */
            u1_s_poweric_i2c_regaccess_exe_flag = (U1)FALSE;
            /* I2C Accessing PID Clear */
            u4_s_poweric_i2c_regaccess_pid = (U4)POWERIC_I2C_PID_INVALID;
            /* Function Completion */
            u1_t_ret = (U1)TRUE;
        }
    }

    /* 暫定 I2Cタイムアウト処理(PID保持値異常含む) */

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  void    vd_s_PowerIc_TurnOnDiagFunc(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PowerIc_SoftMuteSetFunc(void)
{
    U1      u1_t_reg_req_sts;                                       /* Register Read/Write Request Status */
    U1      u1_t_ib2_reg_data;                                      /* IB2 Register Data */

    switch (u1_s_poweric_softmuteset_sts){
        case POWERIC_SOFTMUTESET_STEP0:                             /* STEP0 */
            if(u1_s_poweric_turnondiag_softmute_on_flag == (U1)FALSE){
                /* Read Register */
                u1_t_reg_req_sts = u1_s_PowerIc_I2cReadMgrFunc(st_sp_POWERIC_SOFTMUTE_RD_TBL);
                if(u1_t_reg_req_sts == (U1)TRUE){
                    if(u1_s_poweric_softmute_reqsts == (U1)POWERIC_SOFTMUTE_STS_ON){
                        /* Mute On Data Set */
                        u1_t_ib2_reg_data = st_sp_POWERIC_SOFTMUTE_RD_TBL[1].u1p_pdu[1];                    /* IB2[0x82] */
                        u1_t_ib2_reg_data &= ~(U1)POWERIC_TURNONDIAG_MUTE_MASK;                             /* IB2 bit[4:3] = 0b00 */
                        st_sp_POWERIC_SOFTMUTE_SET_TBL[0].u1p_pdu[2] = u1_t_ib2_reg_data;                   /* IB2 Register Write Data Set */
                        /* Next Process */
                        u1_s_poweric_softmuteset_sts = (U1)POWERIC_SOFTMUTESET_STEP1;
                    }
                    else if(u1_s_poweric_softmute_reqsts == (U1)POWERIC_SOFTMUTE_STS_OFF){
                        /* Mute Off Data Set */
                        u1_t_ib2_reg_data = st_sp_POWERIC_SOFTMUTE_RD_TBL[1].u1p_pdu[1];                    /* IB2[0x82] */
                        u1_t_ib2_reg_data |= (U1)POWERIC_TURNONDIAG_MUTE_MASK;                              /* IB2 bit[4:3] = 0b11 */
                        st_sp_POWERIC_SOFTMUTE_SET_TBL[0].u1p_pdu[2] = u1_t_ib2_reg_data;                   /* IB2 Register Write Data Set */
                        /* Next Process */
                        u1_s_poweric_softmuteset_sts = (U1)POWERIC_SOFTMUTESET_STEP1;
                    }
                    else{
                        /* Nothing */
                    }
                }
            }
            else{
                /* Soft Mute Set Flag Off */
                u1_s_poweric_softmute_set_flag = (U1)FALSE;
                if(u1_s_poweric_softmute_reqsts == (U1)POWERIC_SOFTMUTE_STS_ON){
                    /* Soft Mute Flag On */
                    u1_s_poweric_softmute_on_flag =  (U1)TRUE;
                }
                else if(u1_s_poweric_softmute_reqsts == (U1)POWERIC_SOFTMUTE_STS_OFF){
                    /* Soft Mute Flag Off */
                    u1_s_poweric_softmute_on_flag = (U1)FALSE;
                }
                else{
                    /* Nothing */
                }
            }
            break;
        case POWERIC_SOFTMUTESET_STEP1:                             /* STEP1 */
            /* Set Register */
            u1_t_reg_req_sts = u1_s_PowerIc_I2cSetMgrFunc((U2)POWERIC_SOFTMUTE_SET_WRINUM,
                                                          POWERIC_SOFTMUTE_SET,
                                                          st_sp_POWERIC_SOFTMUTE_SET_TBL);
            if(u1_t_reg_req_sts == (U1)TRUE){
                    if(u1_s_poweric_softmute_reqsts == (U1)POWERIC_SOFTMUTE_STS_ON){
                        /* Soft Mute Flag On */
                        u1_s_poweric_softmute_on_flag =  (U1)TRUE;
                    }
                    else if(u1_s_poweric_softmute_reqsts == (U1)POWERIC_SOFTMUTE_STS_OFF){
                        /* Soft Mute Flag Off */
                        u1_s_poweric_softmute_on_flag =  (U1)FALSE;
                    }
                    else{
                        /* Nothing */
                    }
                /* Soft Mute Set Flag Off */
                u1_s_poweric_softmute_set_flag = (U1)FALSE;
                /* Process Reset */
                u1_s_poweric_softmuteset_sts = (U1)POWERIC_SOFTMUTESET_STEP0;
            }
            break;
        default:                                                    /* FAIL */
            /* Process Reset */
            u1_s_poweric_softmuteset_sts = (U1)POWERIC_SOFTMUTESET_STEP0;
            break;
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_PowerIc_SoftMuteSet(const U1 u1_a_softmute_sts)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_softmute_sts  :  Soft Mute Setting Status ON/OFF                                                            */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_PowerIc_SoftMuteSet(const U1 u1_a_softmute_sts)
{
    /* Soft Mute Set Flag On */
    u1_s_poweric_softmute_set_flag = (U1)TRUE;
    /* Soft Mute Set Request Status Upadata */
    u1_s_poweric_softmute_reqsts = u1_a_softmute_sts;
}

/*===================================================================================================================================*/
/*  void    vd_s_PowerIc_Memset(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_PowerIc_Memset(void * vdp_a_dst, const U1 u1_a_data, U4 u4_a_size)
{
    U1 * u1p_udst = (U1 *)vdp_a_dst;
    while (0U < u4_a_size){
        u4_a_size--;
        *u1p_udst = u1_a_data;
        u1p_udst++;
    }
}
