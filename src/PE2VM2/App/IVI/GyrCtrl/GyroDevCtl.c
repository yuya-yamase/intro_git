/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "GyroDevCtl.h"

#include "gyro.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GYRODEV_TASK_TIME        (1U)

#define GYRODEV_SEQ_IDLE         (0U)
#define GYRODEV_SEQ_CYC          (1U)
#define GYRODEV_SEQ_ERROR_RST    (2U)

#define GYRODEV_CYCCHK_STEP0     (0U)
#define GYRODEV_CYCCHK_STEP1     (1U)
#define GYRODEV_CYCCHK_STEP2     (2U)
#define GYRODEV_CYCCHK_STEP3     (3U)
#define GYRODEV_CYCCHK_STEP4     (4U)
#define GYRODEV_CYCCHK_STEP5     (5U)
#define GYRODEV_CYCCHK_STEP6     (6U)
#define GYRODEV_CYCCHK_STEP7     (7U)
#define GYRODEV_CYCCHK_STEP8     (8U)
#define GYRODEV_CYCCHK_STEP9     (9U)
#define GYRODEV_CYCCHK_STEP10    (10U)
#define GYRODEV_CYCCHK_STEP11    (11U)
#define GYRODEV_CYCCHK_STEP12    (12U)
#define GYRODEV_CYCCHK_STEP13    (13U)
#define GYRODEV_CYCCHK_STEP14    (14U)
#define GYRODEV_CYCCHK_STEP15    (15U)

#define GYRODEV_GYRO_RANGE_NUM              (5U)
#define GYRODEV_GSENS_RANGE_NUM             (4U)

#define GYRODEV_GYRO_RANGE_DATA             (0x04U)
#define GYRODEV_GYRO_TEMP_RESO              (500U)      /* Gyro Device Temperature Resolution 0.5[°C/LSB] */
#define GYRODEV_GYRO_XYZ_CENTER             (0U)        /* Gyro Device XYZ Center Value [0°/s] */
#define GYRODEV_GYRO_TEMP_CENTER            (24U)       /* Gyro Device Temperature Center Value [24°C] */

#define GYRODEV_GSENS_RANGE_DATA            (0x00U)
#define GYRODEV_GSENS_TEMP_RESO             (125U)      /* G-Sensor Device Temperature Resolution 0.125[°C/LSB] */
#define GYRODEV_GSENS_XYZ_CENTER            (0U)        /* G-Sensor Device XYZ Center Value [0g] */
#define GYRODEV_GSENS_TEMP_CENTER           (23U)       /* G-Sensor Device Temperature Center Value [23°C] */
#define GYRODEV_GSENS_TEMP_INVALID          (0x80U)     /* G-Sensor Device Temperature MSB Invalid Value */

#define GYRODEV_INTAPI_NOTIFCOND_SET_WRINUM (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1 u1_s_gyrodev_state;                                   /* Gyro Device State *//* 暫定 +B-ON保持が必要 */

static U1 u1_s_gyrodev_cycchk_sts;                              /* Cycle Check Function Status *//* 暫定 +B-ON保持が必要 */
static U2 u2_s_gyrodev_cycchk_timer;                            /* Gyro Device Cycle Check Poling Timer *//* 暫定 +B-ON保持が必要 */
static U2 u2_s_gyrodev_gyro_max_err_cnt;                        /* Gyro Device GYRO Register MAX Freeze Error Counter *//* 暫定 +B-ON保持が必要 */
static U2 u2_s_gyrodev_gyro_min_err_cnt;                        /* Gyro Device GYRO Register MIN Freeze Error Counter *//* 暫定 +B-ON保持が必要 */
static U1 u1_s_gyrodev_gyro_rst_cnt;                            /* Gyro Device GYRO Read Reset Counter *//* 暫定 +B-ON保持が必要 */
static U2 u2_s_gyrodev_gsens_max_err_cnt;                       /* Gyro Device G-Sensor Register MAX Freeze Error Counter *//* 暫定 +B-ON保持が必要 */
static U2 u2_s_gyrodev_gsens_min_err_cnt;                       /* Gyro Device G-Sensor Register MIN Freeze Error Counter *//* 暫定 +B-ON保持が必要 */
static U1 u1_s_gyrodev_gsens_rst_cnt;                           /* Gyro Device G-Sensor Read Reset Counter *//* 暫定 +B-ON保持が必要 */

static U2 u2_s_gyrodev_regstep;                                 /* Gyro Device Register Request Step */
static U4 u4_s_gyrodev_i2c_ack_wait_time;                       /* Gyro Device I2C Request Ack Wait Timer */
static U2 u2_s_gyrodev_reg_btwn_time;                           /* Gyro Device Access Register Between Timer */

static U1 u1_s_gyrodev_wkup_flag;                               /* Gyro Device Wake-Up Flag */
static ST_XSPI_IVI_GYRO_SENSOR_DATA st_gyrodev_readdata;        /* Gyro Device Read Data */
static U1 u1_s_gyrodev_pre_appon_sts;                           /* Previous APP-ON Status */
static U1 u1_s_gyrodev_inputprm_retain_flag;                    /* Gyro Device Input Parameter Setting Retain Flag */

static U1 u1_s_gyrodev_dtcrec_a_flag;                           /* Gyro Device Read Data Check DTC Record(A) Flag */
static U1 u1_s_gyrodev_dtcrec_b_flag;                           /* Gyro Device Read Data Check DTC Record(B) Flag */
static U1 u1_s_gyrodev_oscmd_notifcond_flag;                    /* "[API]G-Sensor INT Signal Notification Condition" Receive Flag */
static U1 u1_s_gyrodev_oscmd_outctl_flag;                       /* "[API]G-Sensor INT Signal Output Control" Receive Flag */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1 u1_s_GyroDev_TimChk(const U2 u2_a_tim_cnt, const U2 u2_a_wait_tim);
static void vd_s_vd_g_GyroDev_CycChk(void);
static void vd_s_GyroDev_GyroDtcChk(const U2 u2_a_x_data, const U2 u2_a_y_data, const U2 u2_a_z_data);
static void vd_s_GyroDev_GSensDtcChk(const U2 u2_a_x_data, const U2 u2_a_y_data, const U2 u2_a_z_data);
static void vd_s_GyroDev_Memset(void * vdp_a_dst, const U1 u1_a_data, U4 u4_a_size);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U2 u2_sp_GYRODEV_GYRO_RANGE_RESO_CONV_TBL[GYRODEV_GYRO_RANGE_NUM] = {
/*  軸・分解能             Range [°/s]   [LSB/°/s] */
    1638,               /* ±2000         16.38    */
    3277,               /* ±1000         32.77    */
    6554,               /* ±500          65.54    */
    13107,              /* ±250          131.07   */
    26214               /* ±125          262.14   */
};

static const U2 u2_sp_GYRODEV_GSENS_RANGE_RESO_CONV_TBL[GYRODEV_GSENS_RANGE_NUM] = {
/*  軸・分解能             Range [g]      [LSB/g]  */
    16384,              /* ±2             16384   */
    8192,               /* ±4             8192    */
    4096,               /* ±8             4096    */
    2048                /* ±16            2048    */
};

const U1 u1_sp_GYRODEV_GYRODATA_RD_PDU1[GYRODEV_I2C_RWC_BYTE2] = {
    (U1)GYRODEV_GYRO_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x02U     /* Read Address 1 */

};

U1 u1_sp_GYRODEV_GYRODATA_RD_PDU2[8];

const U1 u1_sp_GYRODEV_GSENSDATA_RD_PDU1[GYRODEV_I2C_RWC_BYTE2] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x12U     /* Read Address 1 */

};

U1 u1_sp_GYRODEV_GSENSDATA_RD_PDU2[GYRODEV_I2C_RWC_BYTE7];

const U1 u1_sp_GYRODEV_GSENSDATA_RD2_PDU1[GYRODEV_I2C_RWC_BYTE2] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x22U     /* Read Address 1 */

};

U1 u1_sp_GYRODEV_GSENSDATA_RD2_PDU2[GYRODEV_I2C_RWC_BYTE3];

const U1 u1_sp_GYRODEV_INTAPI_NOTIFCOND_RD_PDU1[GYRODEV_I2C_RWC_BYTE2] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x54U     /* Write Address */
};

U1 u1_sp_GYRODEV_INTAPI_NOTIFCOND_RD_PDU2[GYRODEV_I2C_RWC_BYTE2];

U1 u1_sp_GYRODEV_INTAPI_NOTIFCOND_SET_PDU1[GYRODEV_I2C_RWC_BYTE2];

const U1 u1_sp_GYRODEV_INTAPI_OUTPUTRST_RD_PDU1[GYRODEV_I2C_RWC_BYTE2] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1CU     /* Write Address */
};

U1 u1_sp_GYRODEV_INTAPI_OUTPUTRST_RD_PDU2[GYRODEV_I2C_RWC_BYTE2];

const ST_GP_I2C_MA_REQ st_sp_GYRODEV_GYRODATA_RD_TBL[2] = {
    {
        (U1 *)&u1_sp_GYRODEV_GYRODATA_RD_PDU1[0],
        (U4)0x60040002U
    },
    {
        (U1 *)&u1_sp_GYRODEV_GYRODATA_RD_PDU2[0],
        (U4)0x60080008U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GYRODEV_GSENSDATA_RD_TBL[2] = {
    {
        (U1 *)&u1_sp_GYRODEV_GSENSDATA_RD_PDU1[0],
        (U4)0x700C0002U
    },
    {
        (U1 *)&u1_sp_GYRODEV_GSENSDATA_RD_PDU2[0],
        (U4)0x70100007U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GYRODEV_GSENSDATA_RD_TBL2[2] = {
    {
        (U1 *)&u1_sp_GYRODEV_GSENSDATA_RD2_PDU1[0],
        (U4)0x700C0002U
    },
    {
        (U1 *)&u1_sp_GYRODEV_GSENSDATA_RD2_PDU2[0],
        (U4)0x70100003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GYRODEV_INTAPI_NOTIFCOND_RD_TBL[2] = {
    {
        (U1 *)&u1_sp_GYRODEV_INTAPI_NOTIFCOND_RD_PDU1[0],
        (U4)0x70140002U
    },
    {
        (U1 *)&u1_sp_GYRODEV_INTAPI_NOTIFCOND_RD_PDU2[0],
        (U4)0x70180002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GYRODEV_INTAPI_NOTIFCOND_SET_TBL[1] = {
    {
        (U1 *)&u1_sp_GYRODEV_INTAPI_NOTIFCOND_SET_PDU1[0],
        (U4)0x701C0002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GYRODEV_INTAPI_OUTPUTRST_RD_TBL[2] = {
    {
        (U1 *)&u1_sp_GYRODEV_INTAPI_OUTPUTRST_RD_PDU1[0],
        (U4)0x70200002U
    },
    {
        (U1 *)&u1_sp_GYRODEV_INTAPI_OUTPUTRST_RD_PDU2[0],
        (U4)0x70240002U
    }
};

/*===================================================================================================================================*/
/*  void    vd_g_GyroDev_BonInit(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GyroDev_BonInit(void)
{
    U2 u2_t_cnt;

    u1_s_gyrodev_state = (U1)GYRODEV_SEQ_IDLE;

    u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP0;
    u1_s_gyrodev_wkup_flag = (U1)FALSE;
    u2_s_gyrodev_cycchk_timer = (U2)0;
    u2_s_gyrodev_gyro_max_err_cnt = (U2)0;
    u2_s_gyrodev_gyro_min_err_cnt = (U2)0;
    u1_s_gyrodev_gyro_rst_cnt = (U1)0;
    u2_s_gyrodev_gsens_max_err_cnt = (U2)0;
    u2_s_gyrodev_gsens_min_err_cnt = (U2)0;
    u1_s_gyrodev_gsens_rst_cnt = (U1)0;

    u2_s_gyrodev_regstep = (U2)0;
    u4_s_gyrodev_i2c_ack_wait_time = (U4)0;
    u2_s_gyrodev_reg_btwn_time = (U2)0xFFFFU;

    vd_s_GyroDev_Memset(&st_gyrodev_readdata, 0U, sizeof(st_gyrodev_readdata));
    st_gyrodev_readdata.u1_gyro_x_data_sts = (U1)GYRODEV_READ_DATA_NG;
    st_gyrodev_readdata.u1_gyro_y_data_sts = (U1)GYRODEV_READ_DATA_NG;
    st_gyrodev_readdata.u1_gyro_z_data_sts = (U1)GYRODEV_READ_DATA_NG;
    st_gyrodev_readdata.u1_gyro_temp_data_sts = (U1)GYRODEV_READ_DATA_NG;
    st_gyrodev_readdata.u1_accl_x_data_sts = (U1)GYRODEV_READ_DATA_NG;
    st_gyrodev_readdata.u1_accl_y_data_sts = (U1)GYRODEV_READ_DATA_NG;
    st_gyrodev_readdata.u1_accl_z_data_sts = (U1)GYRODEV_READ_DATA_NG;
    st_gyrodev_readdata.u1_accl_temp_data_sts = (U1)GYRODEV_READ_DATA_NG;

    u1_s_gyrodev_pre_appon_sts = (U1)GYRODEV_APPOFF;
    u1_s_gyrodev_inputprm_retain_flag = (U1)FALSE;

    u1_s_gyrodev_dtcrec_a_flag = (U1)FALSE;
    u1_s_gyrodev_dtcrec_b_flag = (U1)FALSE;
    u1_s_gyrodev_oscmd_notifcond_flag = (U1)FALSE;
    u1_s_gyrodev_oscmd_outctl_flag = (U1)FALSE;

    /*  データリード用テーブル(BurstRead)初期化 */
    u1_sp_GYRODEV_GYRODATA_RD_PDU2[0] = (U1)GYRODEV_GYRO_I2C_SLAVEADR_RD;    /* Slave Address */
    for(u2_t_cnt = (U2)1U; u2_t_cnt < (U2)GYRODEV_I2C_RWC_BYTE8; u2_t_cnt++) {
        u1_sp_GYRODEV_GYRODATA_RD_PDU2[u2_t_cnt] = (U1)0U;    /* 読出しデータ初期値 */
    }

    /*  データリード用テーブル(BurstRead)初期化 */
    u1_sp_GYRODEV_GSENSDATA_RD_PDU2[0] = (U1)GYRODEV_GSENS_I2C_SLAVEADR_RD;    /* Slave Address */
    for(u2_t_cnt = (U2)1U; u2_t_cnt < (U2)GYRODEV_I2C_RWC_BYTE7; u2_t_cnt++) {
        u1_sp_GYRODEV_GSENSDATA_RD_PDU2[u2_t_cnt] = (U1)0U;    /* 読出しデータ初期値 */
    }

    /*  データリード用テーブル(BurstRead)初期化 */
    u1_sp_GYRODEV_GSENSDATA_RD2_PDU2[0] = (U1)GYRODEV_GSENS_I2C_SLAVEADR_RD;    /* Slave Address */
    for(u2_t_cnt = (U2)1U; u2_t_cnt < (U2)GYRODEV_I2C_RWC_BYTE3; u2_t_cnt++) {
        u1_sp_GYRODEV_GSENSDATA_RD2_PDU2[u2_t_cnt] = (U1)0U;    /* 読出しデータ初期値 */
    }

    /*  データリード用テーブル初期化 */
    u1_sp_GYRODEV_INTAPI_NOTIFCOND_RD_PDU2[0] = (U1)GYRODEV_GSENS_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_GYRODEV_INTAPI_NOTIFCOND_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /* 7.5 Interrupt API設定 項目：uc_active 書込み用テーブル(Write Address可変)初期化 */
    u1_sp_GYRODEV_INTAPI_NOTIFCOND_SET_PDU1[0] = (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_GYRODEV_INTAPI_NOTIFCOND_SET_PDU1[1] = (U1)0x54U;    /* Write Address初期値(定期処理内で更新) */

    /*  データリード用テーブル初期化 */
    u1_sp_GYRODEV_INTAPI_OUTPUTRST_RD_PDU2[0] = (U1)GYRODEV_GSENS_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_GYRODEV_INTAPI_OUTPUTRST_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */
}

/*===================================================================================================================================*/
/*  void    vd_g_GyroDev_WkupInit(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GyroDev_WkupInit(void)
{
    U2 u2_t_cnt;

    u1_s_gyrodev_wkup_flag = (U1)TRUE;

    u2_s_gyrodev_regstep = (U2)0;
    u4_s_gyrodev_i2c_ack_wait_time = (U4)0;
    u2_s_gyrodev_reg_btwn_time = (U2)0xFFFFU;

    vd_s_GyroDev_Memset(&st_gyrodev_readdata, 0U, sizeof(st_gyrodev_readdata));
    st_gyrodev_readdata.u1_gyro_x_data_sts = (U1)GYRODEV_READ_DATA_NG;
    st_gyrodev_readdata.u1_gyro_y_data_sts = (U1)GYRODEV_READ_DATA_NG;
    st_gyrodev_readdata.u1_gyro_z_data_sts = (U1)GYRODEV_READ_DATA_NG;
    st_gyrodev_readdata.u1_gyro_temp_data_sts = (U1)GYRODEV_READ_DATA_NG;
    st_gyrodev_readdata.u1_accl_x_data_sts = (U1)GYRODEV_READ_DATA_NG;
    st_gyrodev_readdata.u1_accl_y_data_sts = (U1)GYRODEV_READ_DATA_NG;
    st_gyrodev_readdata.u1_accl_z_data_sts = (U1)GYRODEV_READ_DATA_NG;
    st_gyrodev_readdata.u1_accl_temp_data_sts = (U1)GYRODEV_READ_DATA_NG;

    u1_s_gyrodev_pre_appon_sts = (U1)GYRODEV_APPOFF;
    u1_s_gyrodev_inputprm_retain_flag = (U1)FALSE;

    u1_s_gyrodev_dtcrec_a_flag = (U1)FALSE;
    u1_s_gyrodev_dtcrec_b_flag = (U1)FALSE;
    u1_s_gyrodev_oscmd_notifcond_flag = (U1)FALSE;
    u1_s_gyrodev_oscmd_outctl_flag = (U1)FALSE;

    /*  データリード用テーブル(BurstRead)初期化 */
    u1_sp_GYRODEV_GYRODATA_RD_PDU2[0] = (U1)GYRODEV_GYRO_I2C_SLAVEADR_RD;    /* Slave Address */
    for(u2_t_cnt = (U2)1U; u2_t_cnt < (U2)GYRODEV_I2C_RWC_BYTE8; u2_t_cnt++) {
        u1_sp_GYRODEV_GYRODATA_RD_PDU2[u2_t_cnt] = (U1)0U;    /* 読出しデータ初期値 */
    }

    /*  データリード用テーブル(BurstRead)初期化 */
    u1_sp_GYRODEV_GSENSDATA_RD_PDU2[0] = (U1)GYRODEV_GSENS_I2C_SLAVEADR_RD;    /* Slave Address */
    for(u2_t_cnt = (U2)1U; u2_t_cnt < (U2)GYRODEV_I2C_RWC_BYTE7; u2_t_cnt++) {
        u1_sp_GYRODEV_GSENSDATA_RD_PDU2[u2_t_cnt] = (U1)0U;    /* 読出しデータ初期値 */
    }

    /*  データリード用テーブル(BurstRead)初期化 */
    u1_sp_GYRODEV_GSENSDATA_RD2_PDU2[0] = (U1)GYRODEV_GSENS_I2C_SLAVEADR_RD;    /* Slave Address */
    for(u2_t_cnt = (U2)1U; u2_t_cnt < (U2)GYRODEV_I2C_RWC_BYTE3; u2_t_cnt++) {
        u1_sp_GYRODEV_GSENSDATA_RD2_PDU2[u2_t_cnt] = (U1)0U;    /* 読出しデータ初期値 */
    }

    /*  データリード用テーブル初期化 */
    u1_sp_GYRODEV_INTAPI_NOTIFCOND_RD_PDU2[0] = (U1)GYRODEV_GSENS_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_GYRODEV_INTAPI_NOTIFCOND_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /* 7.5 Interrupt API設定 項目：uc_active 書込み用テーブル(Write Address可変)初期化 */
    u1_sp_GYRODEV_INTAPI_NOTIFCOND_SET_PDU1[0] = (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_GYRODEV_INTAPI_NOTIFCOND_SET_PDU1[1] = (U1)0x54U;    /* Write Address初期値(定期処理内で更新) */

    /*  データリード用テーブル初期化 */
    u1_sp_GYRODEV_INTAPI_OUTPUTRST_RD_PDU2[0] = (U1)GYRODEV_GSENS_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_GYRODEV_INTAPI_OUTPUTRST_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */
}

/*===================================================================================================================================*/
/*  void    vd_g_GyroDev_Routine(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GyroDev_Routine(void)
{
    switch (u1_s_gyrodev_state){
        case GYRODEV_SEQ_IDLE:                                                     /* IDLE */
            /* Timer Clear */
            u2_s_gyrodev_cycchk_timer = (U2)0;

            /* Power ON Check */
            if(Mcu_OnStep_Gyro_2_OVRALL == (U1)MCU_STEP_GYRO2_OVERALL_FIN){
                /* State Update */
                u1_s_gyrodev_state = (U1)GYRODEV_SEQ_CYC;
                /* Poling Check Timer Start */
                u2_s_gyrodev_cycchk_timer++;
            }
            break;
        case GYRODEV_SEQ_CYC:                                                      /* CYCLIC */
            vd_s_vd_g_GyroDev_CycChk();
            break;
        case GYRODEV_SEQ_ERROR_RST:                                                /* ERROR_RST */
                if(u1_s_gyrodev_wkup_flag == (U1)TRUE){/* 暫定 サブマイコンスタンバイ解除がMCUスタンバイ解除のことでよいか確認する */
                    /* Reset Counter Clear */
                    u1_s_gyrodev_gyro_rst_cnt = (U1)0;
                    u1_s_gyrodev_gsens_rst_cnt = (U1)0;
                    /* SENSOR-ON = H *//* SENSOR-ON = L -> Hで起動フロー(1)開始 */
                    u1_GYRODEV_SET_SENSOR_ON_H();
                    /* State Reset */
                    u1_s_gyrodev_state = (U1)GYRODEV_SEQ_IDLE;
                    /* Process Reset */
                    u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP0;
                }
            break;
        default:                                                                /* FAIL */
            vd_g_GyroDev_BonInit();
            break;
    }
}

/*===================================================================================================================================*/
/*  U1    u1_s_GyroDev_TimChk(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u2_a_tim_cnt  :  Timer Count /  u2_a_wait_tim  :  Wait Time                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_GyroDev_TimChk(const U2 u2_a_tim_cnt, const U2 u2_a_wait_tim)
{
    U1  u1_t_ret;

    u1_t_ret = (U1)FALSE;
    if(u2_a_tim_cnt >= u2_a_wait_tim){
        u1_t_ret = (U1)TRUE;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  void    vd_s_vd_g_GyroDev_CycChk(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_vd_g_GyroDev_CycChk(void)
{
    static const U2 GYRODEV_CYCCHK_POLING = (U2)(10U / GYRODEV_TASK_TIME);         /* Gyro Device Poling Check Time : 10ms *//* 暫定 xspiの定期に合わせる */

    static const ST_REG_WRI_REQ GYRODEV_INTAPI_NOTIFCOND_SET[GYRODEV_INTAPI_NOTIFCOND_SET_WRINUM] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0}
    };

    U1      u1_t_time_chk_flg;
    U1      u1_t_reg_req_sts;                                       /* Register Read/Write Request Status */
    U1      u1_t_reg_read_result;                                   /* Register Read Result */
    U1      u1_t_v33_peri_on_sts;                                   /* V33-Peri-On Port Status */
    U1      u1_t_appon_sts;                                         /* APP-ON Status */
    U1      u1_t_gyro_x_lsb_data;                                   /* Gyro Register X_LSB Data */
    U1      u1_t_gyro_x_msb_data;                                   /* Gyro Register X_MSB Data */
    U1      u1_t_gyro_y_lsb_data;                                   /* Gyro Register Y_LSB Data */
    U1      u1_t_gyro_y_msb_data;                                   /* Gyro Register Y_MSB Data */
    U1      u1_t_gyro_z_lsb_data;                                   /* Gyro Register Z_LSB Data */
    U1      u1_t_gyro_z_msb_data;                                   /* Gyro Register Z_MSB Data */
    U2      u2_t_gyro_x_data;                                       /* Gyro Register X_Data */
    U2      u2_t_gyro_y_data;                                       /* Gyro Register Y_Data */
    U2      u2_t_gyro_z_data;                                       /* Gyro Register Z_Data */
    U1      u1_t_gyro_xyz_range_data;                               /* Gyro Register XYZ Range Data */
    U1      u1_t_gsens_x_lsb_data;                                  /* G-Sensor Register X_LSB Data */
    U1      u1_t_gsens_x_msb_data;                                  /* G-Sensor Register X_MSB Data */
    U1      u1_t_gsens_y_lsb_data;                                  /* G-Sensor Register Y_LSB Data */
    U1      u1_t_gsens_y_msb_data;                                  /* G-Sensor Register Y_MSB Data */
    U1      u1_t_gsens_z_lsb_data;                                  /* G-Sensor Register Z_LSB Data */
    U1      u1_t_gsens_z_msb_data;                                  /* G-Sensor Register Z_MSB Data */
    U1      u1_t_gsens_temp_msb_data;                               /* G-Sensor Register Temperature MSB Data */
    U2      u2_t_gsens_x_data;                                      /* G-Sensor Register X Data */
    U2      u2_t_gsens_y_data;                                      /* G-Sensor Register Y Data */
    U2      u2_t_gsens_z_data;                                      /* G-Sensor Register Z Data */
    U1      u1_t_gsens_xyz_range_data;                              /* G-Sensor Register XYZ Range Data */

    switch (u1_s_gyrodev_cycchk_sts){
        case GYRODEV_CYCCHK_STEP0:                                       /* STEP0 */
            u1_t_time_chk_flg = u1_s_GyroDev_TimChk(u2_s_gyrodev_cycchk_timer, GYRODEV_CYCCHK_POLING);
            if(u1_t_time_chk_flg == (U1)TRUE){
                /* Timer Clear */
                u2_s_gyrodev_cycchk_timer = (U2)0;
                /* Next Process */
                u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP1;
            }
            else{
                u2_s_gyrodev_cycchk_timer++;
            }
            break;
        case GYRODEV_CYCCHK_STEP1:                                       /* STEP1 */
            u1_t_v33_peri_on_sts = u1_GYRODEV_GET_V33_PERI_ON();
            if(u1_t_v33_peri_on_sts == (U1)TRUE){
                /* Read Date Initialization */
                vd_s_GyroDev_Memset(&st_gyrodev_readdata, 0U, sizeof(st_gyrodev_readdata));
                st_gyrodev_readdata.u1_gyro_x_data_sts = (U1)GYRODEV_READ_DATA_NG;
                st_gyrodev_readdata.u1_gyro_y_data_sts = (U1)GYRODEV_READ_DATA_NG;
                st_gyrodev_readdata.u1_gyro_z_data_sts = (U1)GYRODEV_READ_DATA_NG;
                st_gyrodev_readdata.u1_gyro_temp_data_sts = (U1)GYRODEV_READ_DATA_NG;
                st_gyrodev_readdata.u1_accl_x_data_sts = (U1)GYRODEV_READ_DATA_NG;
                st_gyrodev_readdata.u1_accl_y_data_sts = (U1)GYRODEV_READ_DATA_NG;
                st_gyrodev_readdata.u1_accl_z_data_sts = (U1)GYRODEV_READ_DATA_NG;
                st_gyrodev_readdata.u1_accl_temp_data_sts = (U1)GYRODEV_READ_DATA_NG;

                /* Next Process */
                u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP2;
            }
            else{
                /* Next Process */
                u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP11;
            }
            break;
        case GYRODEV_CYCCHK_STEP2:                                       /* STEP2 */
            /* Read Register Gyro */
            u1_t_reg_req_sts = u1_GYRODEV_GYRO_I2C_CTRL_REGREAD(&u2_s_gyrodev_regstep, &u4_s_gyrodev_i2c_ack_wait_time,
                                                                st_sp_GYRODEV_GYRODATA_RD_TBL, &u2_s_gyrodev_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                u1_t_gyro_x_lsb_data = st_sp_GYRODEV_GYRODATA_RD_TBL[1].u1p_pdu[1];
                u1_t_gyro_x_msb_data = st_sp_GYRODEV_GYRODATA_RD_TBL[1].u1p_pdu[2];
                u1_t_gyro_y_lsb_data = st_sp_GYRODEV_GYRODATA_RD_TBL[1].u1p_pdu[3];
                u1_t_gyro_y_msb_data = st_sp_GYRODEV_GYRODATA_RD_TBL[1].u1p_pdu[4];
                u1_t_gyro_z_lsb_data = st_sp_GYRODEV_GYRODATA_RD_TBL[1].u1p_pdu[5];
                u1_t_gyro_z_msb_data = st_sp_GYRODEV_GYRODATA_RD_TBL[1].u1p_pdu[6];

                /* Gyro Read Data Create */
                st_gyrodev_readdata.u1_gyro_x_data_down = u1_t_gyro_x_lsb_data;
                st_gyrodev_readdata.u1_gyro_x_data_up = u1_t_gyro_x_msb_data;
                st_gyrodev_readdata.u1_gyro_y_data_down = u1_t_gyro_y_lsb_data;
                st_gyrodev_readdata.u1_gyro_y_data_up = u1_t_gyro_y_msb_data;
                st_gyrodev_readdata.u1_gyro_z_data_down = u1_t_gyro_z_lsb_data;
                st_gyrodev_readdata.u1_gyro_z_data_up = u1_t_gyro_z_msb_data;
                st_gyrodev_readdata.u1_gyro_temp_data = st_sp_GYRODEV_GYRODATA_RD_TBL[1].u1p_pdu[7];

                u1_t_gyro_xyz_range_data = (U1)GYRODEV_GYRO_RANGE_DATA;
                if(u1_t_gyro_xyz_range_data < (U1)GYRODEV_GYRO_RANGE_NUM){
                    st_gyrodev_readdata.st_gyro_reso.u2_gyro_xyz_reso = (U2)u2_sp_GYRODEV_GYRO_RANGE_RESO_CONV_TBL[u1_t_gyro_xyz_range_data];
                }
                st_gyrodev_readdata.st_gyro_reso.u2_gyro_temp_reso = (U2)GYRODEV_GYRO_TEMP_RESO;
                st_gyrodev_readdata.st_gyro_reso.u1_gyro_xyz_center = (U1)GYRODEV_GYRO_XYZ_CENTER;
                st_gyrodev_readdata.st_gyro_reso.u1_gyro_temp_center = (U1)GYRODEV_GYRO_TEMP_CENTER;

                /* Gyro Read Data OK */
                st_gyrodev_readdata.u1_gyro_x_data_sts = (U1)GYRODEV_READ_DATA_OK;
                st_gyrodev_readdata.u1_gyro_y_data_sts = (U1)GYRODEV_READ_DATA_OK;
                st_gyrodev_readdata.u1_gyro_z_data_sts = (U1)GYRODEV_READ_DATA_OK;
                st_gyrodev_readdata.u1_gyro_temp_data_sts = (U1)GYRODEV_READ_DATA_OK;

                /* Gyro Fail Check */
                u2_t_gyro_x_data = (U2)(((U2)u1_t_gyro_x_msb_data << (U2)GYRODEV_REG_BIT_SHIFT_8) | (U2)u1_t_gyro_x_lsb_data);
                u2_t_gyro_y_data = (U2)(((U2)u1_t_gyro_y_msb_data << (U2)GYRODEV_REG_BIT_SHIFT_8) | (U2)u1_t_gyro_y_lsb_data);
                u2_t_gyro_z_data = (U2)(((U2)u1_t_gyro_z_msb_data << (U2)GYRODEV_REG_BIT_SHIFT_8) | (U2)u1_t_gyro_z_lsb_data);

                vd_s_GyroDev_GyroDtcChk(u2_t_gyro_x_data, u2_t_gyro_y_data, u2_t_gyro_z_data);

                /* Next Process */
                u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP3;
            }
            break;
        case GYRODEV_CYCCHK_STEP3:                                      /* STEP3 */
            /* Read Register G-Sensor */
            u1_t_reg_req_sts = u1_GYRODEV_GSENS_I2C_CTRL_REGREAD(&u2_s_gyrodev_regstep, &u4_s_gyrodev_i2c_ack_wait_time,
                                                                 st_sp_GYRODEV_GSENSDATA_RD_TBL, &u2_s_gyrodev_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                u1_t_gsens_x_lsb_data = st_sp_GYRODEV_GSENSDATA_RD_TBL[1].u1p_pdu[1];
                u1_t_gsens_x_msb_data = st_sp_GYRODEV_GSENSDATA_RD_TBL[1].u1p_pdu[2];
                u1_t_gsens_y_lsb_data = st_sp_GYRODEV_GSENSDATA_RD_TBL[1].u1p_pdu[3];
                u1_t_gsens_y_msb_data = st_sp_GYRODEV_GSENSDATA_RD_TBL[1].u1p_pdu[4];
                u1_t_gsens_z_lsb_data = st_sp_GYRODEV_GSENSDATA_RD_TBL[1].u1p_pdu[5];
                u1_t_gsens_z_msb_data = st_sp_GYRODEV_GSENSDATA_RD_TBL[1].u1p_pdu[6];

                /* G-Sensor Read Data Create */
                st_gyrodev_readdata.u1_accl_x_data_down = u1_t_gsens_x_lsb_data;
                st_gyrodev_readdata.u1_accl_x_data_up = u1_t_gsens_x_msb_data;
                st_gyrodev_readdata.u1_accl_y_data_down = u1_t_gsens_y_lsb_data;
                st_gyrodev_readdata.u1_accl_y_data_up = u1_t_gsens_y_msb_data;
                st_gyrodev_readdata.u1_accl_z_data_down = u1_t_gsens_z_lsb_data;
                st_gyrodev_readdata.u1_accl_z_data_up = u1_t_gsens_z_msb_data;

                /* G-Sensor Fail Check */
                u2_t_gsens_x_data = (U2)(((U2)u1_t_gsens_x_msb_data << (U2)GYRODEV_REG_BIT_SHIFT_8) | (U2)u1_t_gsens_x_lsb_data);
                u2_t_gsens_y_data = (U2)(((U2)u1_t_gsens_y_msb_data << (U2)GYRODEV_REG_BIT_SHIFT_8) | (U2)u1_t_gsens_y_lsb_data);
                u2_t_gsens_z_data = (U2)(((U2)u1_t_gsens_z_msb_data << (U2)GYRODEV_REG_BIT_SHIFT_8) | (U2)u1_t_gsens_z_lsb_data);

                vd_s_GyroDev_GSensDtcChk(u2_t_gsens_x_data, u2_t_gsens_y_data, u2_t_gsens_z_data);

                /* Next Process */
                u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP4;
            }
            break;
        case GYRODEV_CYCCHK_STEP4:                                       /* STEP4 */
            /* Read Register G-Sensor */
            u1_t_reg_req_sts = u1_GYRODEV_GSENS_I2C_CTRL_REGREAD(&u2_s_gyrodev_regstep, &u4_s_gyrodev_i2c_ack_wait_time,
                                                                st_sp_GYRODEV_GSENSDATA_RD_TBL2, &u2_s_gyrodev_reg_btwn_time);
            
            if(u1_t_reg_req_sts == (U1)TRUE){
                u1_t_gsens_temp_msb_data = st_sp_GYRODEV_GSENSDATA_RD_TBL2[1].u1p_pdu[1];

                /* G-Sensor Read Data Create */
                st_gyrodev_readdata.u1_accl_temp_data_down = st_sp_GYRODEV_GSENSDATA_RD_TBL2[1].u1p_pdu[2];
                st_gyrodev_readdata.u1_accl_temp_data_up = u1_t_gsens_temp_msb_data;

                u1_t_gsens_xyz_range_data = (U1)GYRODEV_GSENS_RANGE_DATA;
                if(u1_t_gsens_xyz_range_data < (U1)GYRODEV_GSENS_RANGE_NUM){
                    st_gyrodev_readdata.st_gyro_reso.u2_accel_xyz_reso = (U2)u2_sp_GYRODEV_GSENS_RANGE_RESO_CONV_TBL[u1_t_gyro_xyz_range_data];
                }
                st_gyrodev_readdata.st_gyro_reso.u2_accel_temp_reso = (U2)GYRODEV_GSENS_TEMP_RESO;
                st_gyrodev_readdata.st_gyro_reso.u1_accel_xyz_center = (U1)GYRODEV_GSENS_XYZ_CENTER;
                st_gyrodev_readdata.st_gyro_reso.u1_accel_temp_center = (U1)GYRODEV_GSENS_TEMP_CENTER;

                /* G-Sensor Read Data OK */
                st_gyrodev_readdata.u1_accl_x_data_sts = (U1)GYRODEV_READ_DATA_OK;
                st_gyrodev_readdata.u1_accl_y_data_sts = (U1)GYRODEV_READ_DATA_OK;
                st_gyrodev_readdata.u1_accl_z_data_sts = (U1)GYRODEV_READ_DATA_OK;
                if(u1_t_gsens_temp_msb_data != (U1)GYRODEV_GSENS_TEMP_INVALID){
                    st_gyrodev_readdata.u1_accl_temp_data_sts = (U1)GYRODEV_READ_DATA_OK;
                }

                /* Read Data Notificaiton */
                vd_GYRODEV_OSCMD_GYRO_DATA_NOTIF(st_gyrodev_readdata);

                /* Next Process */
                u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP5;
            }
            break;
        case GYRODEV_CYCCHK_STEP5:                                       /* STEP5 */
            if(u1_s_gyrodev_oscmd_notifcond_flag == (U1)TRUE){
                /* Flag Clear */
                u1_s_gyrodev_oscmd_notifcond_flag = (U1)FALSE;
                /* Next Process */
                u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP6;
            }
            else{
                /* Next Process */
                u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP7;
            }
            break;
        case GYRODEV_CYCCHK_STEP6:                                       /* STEP6 */
            /* 暫定 シス検では「[API]GセンサINT信号通知条件」のOS間通信コマンド未対応のため処理未実装 */
            /* ----------「[API]GセンサINT信号通知条件」通知あり時の処理---------- */
            /* Next Process */
            u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP7;
            break;
        case GYRODEV_CYCCHK_STEP7:                                       /* STEP7 */
            if(u1_s_gyrodev_oscmd_outctl_flag == (U1)TRUE){
                /* Flag Clear */
                u1_s_gyrodev_oscmd_outctl_flag = (U1)FALSE;
                /* Next Process */
                u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP8;
            }
            else{
                /* Next Process */
                u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP9;
            }
            break;
        case GYRODEV_CYCCHK_STEP8:                                       /* STEP8 */
            /* 暫定 シス検では「[API]GセンサINT信号出力制御」のOS間通信コマンド未対応のため処理未実装 */
            /* ----------「[API]GセンサINT信号出力制御」通知あり時の処理---------- */
            /* Next Process */
            u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP9;
            break;
        case GYRODEV_CYCCHK_STEP9:                                       /* STEP9 */
            u1_t_appon_sts = u1_GYRODEV_GET_APP_ON();
            if((u1_t_appon_sts == (U1)GYRODEV_APPOFF)
            && (u1_s_gyrodev_pre_appon_sts == (U1)GYRODEV_APPON)){
                if(u1_s_gyrodev_inputprm_retain_flag == (U1)TRUE){
                    /* Next Process */
                    u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP10;
                }
                else{
                    /* Next Process */
                    u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP11;
                }
            }
            else{
                /* Process Reset */
                u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP0;
            }
            /* Previous State Update */
            u1_s_gyrodev_pre_appon_sts = u1_t_appon_sts;
            break;
        case GYRODEV_CYCCHK_STEP10:                                       /* STEP10 */
            /* 暫定 シス検では「[API]設定」のOS間通信コマンド未対応のため「入力パラメータ保持」されないため処理未実装 */
            /* ----------「入力パラメータ保持」時のレジスタ設定処理---------- */
            /* Process Reset */
            u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP0;
            break;
        case GYRODEV_CYCCHK_STEP11:                                       /* STEP11 */
            /* Read Register */
            u1_t_reg_req_sts = u1_GYRODEV_GSENS_I2C_CTRL_REGREAD(&u2_s_gyrodev_regstep, &u4_s_gyrodev_i2c_ack_wait_time,
                                                                 st_sp_GYRODEV_INTAPI_NOTIFCOND_RD_TBL, &u2_s_gyrodev_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                u1_t_reg_read_result = st_sp_GYRODEV_INTAPI_NOTIFCOND_RD_TBL[1].u1p_pdu[1];
                u1_t_reg_read_result = u1_t_reg_read_result | (U1)GYRODEV_REG_MASK_BIT_1;   /* bit[1] = 1 */
                st_sp_GYRODEV_INTAPI_NOTIFCOND_RD_TBL[0].u1p_pdu[2] = u1_t_reg_read_result;   /* Register Write Data Set */
                /* Next Process */
                u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP12;
            }
            break;
        case GYRODEV_CYCCHK_STEP12:                                       /* STEP12 */
            /* Set Register */
            u1_t_reg_req_sts = u1_GYRODEV_GSENS_I2C_CTRL_REGSET(&u2_s_gyrodev_regstep, (U2)GYRODEV_INTAPI_NOTIFCOND_SET_WRINUM,
                                                                GYRODEV_INTAPI_NOTIFCOND_SET, &u4_s_gyrodev_i2c_ack_wait_time,
                                                                st_sp_GYRODEV_INTAPI_NOTIFCOND_SET_TBL, &u2_s_gyrodev_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP13;
            }
            break;
        case GYRODEV_CYCCHK_STEP13:                                       /* STEP13 */
            /* Read Register */
            u1_t_reg_req_sts = u1_GYRODEV_GSENS_I2C_CTRL_REGREAD(&u2_s_gyrodev_regstep, &u4_s_gyrodev_i2c_ack_wait_time,
                                                                 st_sp_GYRODEV_INTAPI_OUTPUTRST_RD_TBL, &u2_s_gyrodev_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Process Reset */
                u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP0;
            }
            break;
        default:                                                                /* FAIL */
            /* State Reset */
            u1_s_gyrodev_state = (U1)GYRODEV_SEQ_IDLE;
            /* Process Reset */
            u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP0;
            break;
    }
}

/*===================================================================================================================================*/
/*  void    vd_s_GyroDev_GyroDtcChk(const U2 u2_a_x_data, const U2 u2_a_y_data, const U2 u2_a_z_data)                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_GyroDev_GyroDtcChk(const U2 u2_a_x_data, const U2 u2_a_y_data, const U2 u2_a_z_data)
{
    U1      u1_t_error_flag;                                         /* Register Read Data Error Flag */
    U1      u1_t_last_pls;                                          /* Register Read/Write Request Status */

    u1_t_error_flag = (U1)FALSE;

    u1_t_last_pls = u1_GYRODEV_GET_LAST_PLS();
    if((u1_t_last_pls == (U1)GYRODEV_LAST_PLS_STOP)
    || (u1_t_last_pls > (U1)GYRODEV_LAST_PLS_8KM)){
        /* MAX Freeze Chek */
        if((u2_a_x_data == (U2)GYRODEV_GYRODTC_XYZ_MAX)
        || (u2_a_y_data == (U2)GYRODEV_GYRODTC_XYZ_MAX)
        || (u2_a_z_data == (U2)GYRODEV_GYRODTC_XYZ_MAX)){        /* MAX Freeze */
            u1_t_error_flag = (U1)TRUE;
            if(u2_s_gyrodev_gyro_max_err_cnt <= (U2)GYRODEV_GYRODTC_XYZ_MAX_ERRCNT_MAX){    /* Error Count <= n(6_1) */
                u2_s_gyrodev_gyro_max_err_cnt++;
            }
        }
        /* MIN Freeze Chek */
        if((u2_a_x_data == (U2)GYRODEV_GYRODTC_XYZ_MIN)
        || (u2_a_y_data == (U2)GYRODEV_GYRODTC_XYZ_MIN)
        || (u2_a_z_data == (U2)GYRODEV_GYRODTC_XYZ_MIN)){        /* MIN Freeze */
            u1_t_error_flag = (U1)TRUE;
            if(u2_s_gyrodev_gyro_min_err_cnt <= (U2)GYRODEV_GYRODTC_XYZ_MIN_ERRCNT_MAX){    /* Error Count <= n(6_2) */
                u2_s_gyrodev_gyro_min_err_cnt++;
            }
        }

        if(u1_t_error_flag == (U1)TRUE){                        /* Read Data Error */
            if((u2_s_gyrodev_gyro_max_err_cnt > (U2)GYRODEV_GYRODTC_XYZ_MAX_ERRCNT_MAX)
            || (u2_s_gyrodev_gyro_min_err_cnt > (U2)GYRODEV_GYRODTC_XYZ_MIN_ERRCNT_MAX)){
                /* Error Counter Clear */
                u2_s_gyrodev_gyro_max_err_cnt = (U2)0;
                u2_s_gyrodev_gyro_min_err_cnt = (U2)0;

                /* SENSOR-ON = L */
                u1_GYRODEV_SET_SENSOR_ON_L();

                /* ダイレコ保存 *//* 暫定 シス検ではダイレコ保存未対応 */

                /* DTC "B15AD96"記録(異常) *//* 暫定 DTC記憶はシス検では未対応 */
                u1_s_gyrodev_dtcrec_a_flag = (U1)FALSE;

                if(u1_s_gyrodev_gyro_rst_cnt >= (U2)GYRODEV_GYRODTC_RSTCNT_MAX){    /* Reset Count >= n(6_3) */
                    /* Flag Clear */
                    u1_s_gyrodev_wkup_flag = (U1)FALSE;
                    /* Set State */
                    u1_s_gyrodev_state = (U1)GYRODEV_SEQ_ERROR_RST;
                }
                else{
                    u1_s_gyrodev_gyro_rst_cnt++;
                    /* SENSOR-ON = H *//* SENSOR-ON = L -> Hで起動フロー(1)開始 */
                    u1_GYRODEV_SET_SENSOR_ON_H();
                    /* State Reset */
                    u1_s_gyrodev_state = (U1)GYRODEV_SEQ_IDLE;
                    /* Process Reset */
                    u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP0;
                }
            }
        }
        else{
            /* Error Counter Clear */
            u2_s_gyrodev_gyro_max_err_cnt = (U2)0;
            u2_s_gyrodev_gyro_min_err_cnt = (U2)0;
            u1_s_gyrodev_gyro_rst_cnt = (U1)0;

            /* DTC Record Check */
            if(u1_s_gyrodev_dtcrec_a_flag == (U1)FALSE){                       /* Initial Record or Error -> Normal */
                u1_s_gyrodev_dtcrec_a_flag = (U1)TRUE;
                /* DTC "B15AD96"記録(正常) *//* 暫定 DTC記憶はシス検では未対応 */
            }
        }
    }
    else{
        /* Error Counter Clear */
        u2_s_gyrodev_gyro_max_err_cnt = (U2)0;
        u2_s_gyrodev_gyro_min_err_cnt = (U2)0;
        u1_s_gyrodev_gyro_rst_cnt = (U1)0;

        /* DTC Record Check */
        if(u1_s_gyrodev_dtcrec_b_flag == (U1)FALSE){                       /* Initial Record */
            u1_s_gyrodev_dtcrec_b_flag = (U1)TRUE;
            /* DTC "B15AD96"記録(不定) *//* 暫定 DTC記憶はシス検では未対応 */
        }
    }
}

/*===================================================================================================================================*/
/*  void    vd_s_GyroDev_GSensDtcChk(const U2 u2_a_x_data, const U2 u2_a_y_data, const U2 u2_a_z_data)                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_GyroDev_GSensDtcChk(const U2 u2_a_x_data, const U2 u2_a_y_data, const U2 u2_a_z_data)
{
    U1      u1_t_error_flag;                                         /* Register Read Data Error Flag */

    u1_t_error_flag = (U1)FALSE;

    /* MAX Freeze Chek */
    if((u2_a_x_data == (U2)GYRODEV_GSENSDTC_XYZ_MAX)
    || (u2_a_y_data == (U2)GYRODEV_GSENSDTC_XYZ_MAX)
    || (u2_a_z_data == (U2)GYRODEV_GSENSDTC_XYZ_MAX)){        /* MAX Freeze */
        u1_t_error_flag = (U1)TRUE;
        if(u2_s_gyrodev_gsens_max_err_cnt <= (U2)GYRODEV_GSENSDTC_XYZ_MAX_ERRCNT_MAX){    /* Error Count <= n(6_1) */
            u2_s_gyrodev_gsens_max_err_cnt++;
        }
    }
    /* MIN Freeze Chek */
    if((u2_a_x_data == (U2)GYRODEV_GSENSDTC_XYZ_MIN)
    || (u2_a_y_data == (U2)GYRODEV_GSENSDTC_XYZ_MIN)
    || (u2_a_z_data == (U2)GYRODEV_GSENSDTC_XYZ_MIN)){        /* MIN Freeze */
        u1_t_error_flag = (U1)TRUE;
        if(u2_s_gyrodev_gsens_min_err_cnt <= (U2)GYRODEV_GSENSDTC_XYZ_MIN_ERRCNT_MAX){    /* Error Count <= n(6_2) */
            u2_s_gyrodev_gsens_min_err_cnt++;
        }
    }

    if(u1_t_error_flag == (U1)TRUE){                        /* Read Data Error */
        if((u2_s_gyrodev_gsens_max_err_cnt > (U2)GYRODEV_GSENSDTC_XYZ_MAX_ERRCNT_MAX)
        || (u2_s_gyrodev_gsens_min_err_cnt > (U2)GYRODEV_GSENSDTC_XYZ_MIN_ERRCNT_MAX)){
            /* Error Counter Clear */
            u2_s_gyrodev_gsens_max_err_cnt = (U2)0;
            u2_s_gyrodev_gsens_min_err_cnt = (U2)0;

            /* SENSOR-ON = L */
            u1_GYRODEV_SET_SENSOR_ON_L();

            /* ダイレコ保存 *//* 暫定 シス検ではダイレコ保存未対応 */

            /* DTC "B15AD96"記録(異常) *//* 暫定 DTC記憶はシス検では未対応 */
            u1_s_gyrodev_dtcrec_a_flag = (U1)FALSE;

            if(u1_s_gyrodev_gsens_rst_cnt >= (U2)GYRODEV_GSENSDTC_RSTCNT_MAX){    /* Reset Count >= n(6_3) */
                /* Flag Clear */
                u1_s_gyrodev_wkup_flag = (U1)FALSE;
                /* Set State */
                u1_s_gyrodev_state = (U1)GYRODEV_SEQ_ERROR_RST;
            }
            else{
                u1_s_gyrodev_gsens_rst_cnt++;
                /* SENSOR-ON = H *//* SENSOR-ON = L -> Hで起動フロー(1)開始 */
                u1_GYRODEV_SET_SENSOR_ON_H();
                /* State Reset */
                u1_s_gyrodev_state = (U1)GYRODEV_SEQ_IDLE;
                /* Process Reset */
                u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP0;
            }
        }
    }
    else{
        /* Error Counter Clear */
        u2_s_gyrodev_gsens_max_err_cnt = (U2)0;
        u2_s_gyrodev_gsens_min_err_cnt = (U2)0;
        u1_s_gyrodev_gsens_rst_cnt = (U1)0;

        /* DTC Record Check */
        if(u1_s_gyrodev_dtcrec_a_flag == (U1)FALSE){                       /* Initial Record or Error -> Normal */
            u1_s_gyrodev_dtcrec_a_flag = (U1)TRUE;
            /* DTC "B15AD96"記録(正常) *//* 暫定 DTC記憶はシス検では未対応 */
        }
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_GyroDev_NotifCond_Req(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GyroDev_NotifCond_Req(void)    /* 暫定 通知内容未定のため引数void */
{
    u1_s_gyrodev_oscmd_notifcond_flag = (U1)TRUE;
}

/*===================================================================================================================================*/
/*  void    vd_g_GyroDev_OutCtl_Req(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GyroDev_OutCtl_Req(void)    /* 暫定 通知内容未定のため引数void */
{
    u1_s_gyrodev_oscmd_outctl_flag = (U1)TRUE;
}

/*===================================================================================================================================*/
/*  void    vd_s_GyroDev_Memset(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GyroDev_Memset(void * vdp_a_dst, const U1 u1_a_data, U4 u4_a_size)
{
    U1 * u1p_udst = (U1 *)vdp_a_dst;
    while (0U < u4_a_size){
        u4_a_size--;
        *u1p_udst = u1_a_data;
        u1p_udst++;
    }
}
