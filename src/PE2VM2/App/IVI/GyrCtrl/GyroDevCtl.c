/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "GyroDevCtl.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GYRODEV_TASK_TIME                   (1U)

#define GYRODEV_SEQ_IDLE                    (0U)
#define GYRODEV_SEQ_CYC                     (1U)

#define GYRODEV_CYCCHK_STEP0                (0U)
#define GYRODEV_CYCCHK_STEP1                (1U)
#define GYRODEV_CYCCHK_STEP2                (2U)
#define GYRODEV_CYCCHK_STEP3                (3U)
#define GYRODEV_CYCCHK_STEP4                (4U)
#define GYRODEV_CYCCHK_STEP5                (5U)
#define GYRODEV_CYCCHK_STEP6                (6U)
#define GYRODEV_CYCCHK_STEP7                (7U)
#define GYRODEV_CYCCHK_STEP8                (8U)
#define GYRODEV_CYCCHK_STEP9                (9U)
#define GYRODEV_CYCCHK_STEP10               (10U)

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
#define GYRODEV_GSENS_NOTIFCONDFUNC_SETREQ  (0U)        /* '[API]LsdrvGsnsIntSetCond' SiP -> MCU Setting Request */
#define GYRODEV_GSENS_NOTIFCONDFUNC_BACKUP  (1U)        /* '[API]LsdrvGsnsIntSetCond' Power ON -> OFF Event Setting */
#define GYRODEV_GSENS_NOTIFCONDFUNC_READREQ (2U)        /* '[API]LsdrvGsnsIntSetCond' SiP -> MCU Reading Request */
#define GYRODEV_GSENS_CTRLOUTFUNC_SETREQ    (0U)        /* '[API]LsdrvGsnsIntCtrlOutput' SiP -> MCU Setting Request */
#define GYRODEV_GSENS_CTRLOUTFUNC_BACKUP    (1U)        /* '[API]LsdrvGsnsIntCtrlOutput' Power ON -> OFF Event Setting */

#define GYRODEV_NOTIFCONDSET_STEP0          (0U)
#define GYRODEV_NOTIFCONDSET_STEP1          (1U)
#define GYRODEV_NOTIFCONDSET_STEP2          (2U)
#define GYRODEV_NOTIFCONDSET_STEP3          (3U)
#define GYRODEV_NOTIFCONDSET_STEP4          (4U)
#define GYRODEV_NOTIFCONDSET_STEP5          (5U)
#define GYRODEV_NOTIFCONDSET_STEP6          (6U)
#define GYRODEV_NOTIFCONDSET_STEP7          (7U)
#define GYRODEV_NOTIFCONDSET_STEP8          (8U)
#define GYRODEV_NOTIFCONDSET_STEP9          (9U)
#define GYRODEV_NOTIFCONDSET_STEP10         (10U)
#define GYRODEV_NOTIFCONDSET_STEP11         (11U)
#define GYRODEV_NOTIFCONDSET_STEP12         (12U)
#define GYRODEV_NOTIFCONDSET_STEP13         (13U)

#define GYRODEV_GSENS_NOTIFCOND_REQ_INI     (0xFFU)     /* "[API]G-Sensor INT Signal Notification Condition" Result Initial Value */
#define GYRODEV_GSENS_NOTIFCOND_SET_OK      (0U)        /* "[API]G-Sensor INT Signal Notification Condition" Setting OK */
#define GYRODEV_GSENS_NOTIFCOND_SET_NG      (1U)        /* "[API]G-Sensor INT Signal Notification Condition" Setting NG */
#define GYRODEV_GSENS_NOTIFCOND_READ_OK     (0U)        /* "[API]G-Sensor INT Signal Notification Condition" Reading OK */
#define GYRODEV_GSENS_NOTIFCOND_READ_NG     (1U)        /* "[API]G-Sensor INT Signal Notification Condition" Reading NG */
#define GYRODEV_GSENS_INT_THD_LSB_MASK      (0xFFU)     /* G-Sensor INT_ANYMOT_TH Register anymot_th LSB Mask Value */
#define GYRODEV_GSENS_INT_THD_MSB_MASK      (0x07U)     /* G-Sensor INT_ANYMOT_TH Register anymot_th MSB Mask Value */
#define GYRODEV_GSENS_INT_THD_MAX           (100U)      /* "[API]G-Sensor INT Signal Notification Condition" Threshold Request Max Value */
#define GYRODEV_GSENS_INT_THD_RESO          (2047U)     /* G-Sensor anymot_th Resolution(2048 - 1) */
#define GYRODEV_GSENS_INT_THD_MULT          (100U)      /* "[API]G-Sensor INT Signal Notification Condition" Threshold Request Multiple Value */
#define GYRODEV_GSENS_INT_AXIS_LSB_MASK     (0x00U)     /* G-Sensor INT_ANYMOT_TH Register en_x/y/z LSB Mask Value */
#define GYRODEV_GSENS_INT_AXIS_MSB_MASK     (0xE0U)     /* G-Sensor INT_ANYMOT_TH Register en_x/y/z MSB Mask Value */
#define GYRODEV_GSENS_INT_AXIS_ACT          (1U)        /* "[API]G-Sensor INT Signal Notification Condition" Axis Request Active Value */
#define GYRODEV_GSENS_INT_LVL_MASK          (0x02U)     /* G-Sensor INT2_IO_CONF Register int2_lvl Mask Value */
#define GYRODEV_GSENS_INT_LVL_ACT_HI        (0U)        /* "[API]G-Sensor INT Signal Notification Condition" Active Request Active High Value */
#define GYRODEV_GSENS_INT_LVL_ACT_LOW       (1U)        /* "[API]G-Sensor INT Signal Notification Condition" Active Request Active Low Value */

#define GYRODEV_CTRLOUTSET_STEP0            (0U)
#define GYRODEV_CTRLOUTSET_STEP1            (1U)
#define GYRODEV_CTRLOUTSET_STEP2            (2U)
#define GYRODEV_CTRLOUTSET_STEP3            (3U)
#define GYRODEV_CTRLOUTSET_STEP4            (4U)
#define GYRODEV_CTRLOUTSET_STEP5            (5U)
#define GYRODEV_CTRLOUTSET_STEP6            (6U)
#define GYRODEV_CTRLOUTSET_STEP7            (7U)
#define GYRODEV_CTRLOUTSET_STEP8            (8U)
#define GYRODEV_CTRLOUTSET_STEP9            (9U)
#define GYRODEV_CTRLOUTSET_STEP10           (10U)
#define GYRODEV_CTRLOUTSET_STEP11           (11U)
#define GYRODEV_CTRLOUTSET_STEP12           (12U)
#define GYRODEV_CTRLOUTSET_STEP13           (13U)
#define GYRODEV_CTRLOUTSET_STEP14           (14U)
#define GYRODEV_CTRLOUTSET_STEP15           (15U)

#define GYRODEV_GSENS_OUTCTRL_REQ_INI       (0xFFU)     /* "[API]G-Sensor INT Signal Output Control" Result Initial Value */
#define GYRODEV_GSENS_OUTCTRL_SET_OK        (0U)        /* "[API]G-Sensor INT Signal Output Control" Setting OK */
#define GYRODEV_GSENS_OUTCTRL_SET_NG        (1U)        /* "[API]G-Sensor INT Signal Output Control" Setting NG */
#define GYRODEV_GSENS_INT_EN_LSB_MASK       (0x00U)     /* G-Sensor INT_ANYMOT_TH Register anymot_en LSB Mask Value */
#define GYRODEV_GSENS_INT_EN_MSB_MASK       (0x08U)     /* G-Sensor INT_ANYMOT_TH Register anymot_en MSB Mask Value */
#define GYRODEV_GSENS_INT_EN_ON             (0U)        /* "[API]G-Sensor INT Signal Output Control" Type Request On Value */
#define GYRODEV_GSENS_INT_EN_OFF            (1U)        /* "[API]G-Sensor INT Signal Output Control" Type Request Off Value */
#define GYRODEV_GSENS_INT_EN_RST            (2U)        /* "[API]G-Sensor INT Signal Output Control" Type Request Reset Value */
#define GYRODEV_GSENS_INT_OUT_MASK          (0x08U)     /* G-Sensor INT2_IO_CONF Register int2_out Mask Value */
#define GYRODEV_GSENS_INT_STBY_ON           (0U)        /* "[API]G-Sensor INT Signal Output Control" Standby Request ON Value */
#define GYRODEV_GSENS_INT_STBY_OFF          (1U)        /* "[API]G-Sensor INT Signal Output Control" Standby Request OFF Value */

#define GYRODEV_INT_ANYMOT_TH_SET1_WRINUM   (1U)
#define GYRODEV_INT_ANYMOT_TH_SET2_WRINUM   (1U)
#define GYRODEV_INT_ANYMOT_EN_SET1_WRINUM   (1U)
#define GYRODEV_INT_ANYMOT_EN_SET2_WRINUM   (1U)
#define GYRODEV_INT2_IO_CONF_SET_WRINUM     (1U)
#define GYRODEV_INTAPI_OUTPUTON_SET_WRINUM  (1U)
#define GYRODEV_INTAPI_OUTPUTOFF_SET_WRINUM (1U)
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

static ST_XSPI_IVI_GYRO_SENSOR_DATA st_gyrodev_readdata;        /* Gyro Device Read Data */
static U1 u1_s_gyrodev_pre_appon_sts;                           /* Previous APP-ON Status */

static U1 u1_s_gyrodev_dtcrec_a_flag;                           /* Gyro Device Read Data Check DTC Record(A) Flag */

static U1 u1_s_gyrodev_notifcondset_sts;                        /* "[API]G-Sensor INT Signal Notification Condition" Function Status */
static U1 u1_s_gyrodev_oscmd_notifcond_rcv_flag;                /* "[API]G-Sensor INT Signal Notification Condition" Setting Request Receive Flag */
static U1 u1_s_gyrodev_oscmd_notifcond_bak_flag;                /* "[API]G-Sensor INT Signal Notification Condition" Setting Request Backup Flag */
static ST_GYRODEV_NOTIFCOND_SETDATA st_gyrodev_notifcond_setreq;    /* "[API]G-Sensor INT Signal Notification Condition" Setting Request Data */
static ST_GYRODEV_NOTIFCOND_SETDATA st_gyrodev_notifcond_setbak;    /* "[API]G-Sensor INT Signal Notification Condition" Setting Request Backup Data *//* 暫定 +B-ON保持が必要 */
static U1 u1_s_gyrodev_oscmd_notifcond_read_flag;               /* "[API]G-Sensor INT Signal Notification Condition" Reading Request Receive Flag */
static ST_XSPI_IVI_GYRO_INT_DATA st_gyrodev_notifcond_readreq;  /* "[API]G-Sensor INT Signal Notification Condition" Readting Request Data */

static U1 u1_s_gyrodev_ctrloutset_sts;                          /* "[API]G-Sensor INT Signal Output Control" Function Status */
static U1 u1_s_gyrodev_oscmd_outctl_rcv_flag;                   /* "[API]G-Sensor INT Signal Output Control" Setting Request Receive Flag */
static U1 u1_s_gyrodev_oscmd_outctl_bak_flag;                   /* "[API]G-Sensor INT Signal Output Control" Setting Request Backup Flag */
static ST_GYRODEV_CTRLOUT_SETDATA st_gyrodev_ctrlout_setreq;    /* "[API]G-Sensor INT Signal Output Control" Setting Request Data */
static ST_GYRODEV_CTRLOUT_SETDATA st_gyrodev_ctrlout_setbak;    /* "[API]G-Sensor INT Signal Output Control" Setting Request Backup Data *//* 暫定 +B-ON保持が必要 */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1 u1_s_GyroDev_TimChk(const U2 u2_a_tim_cnt, const U2 u2_a_wait_tim);
static void vd_s_vd_g_GyroDev_CycChk(void);
static void vd_s_GyroDev_GyroDtcChk(const U2 u2_a_x_data, const U2 u2_a_y_data, const U2 u2_a_z_data);
static void vd_s_GyroDev_GSensDtcChk(const U2 u2_a_x_data, const U2 u2_a_y_data, const U2 u2_a_z_data);
static U1 u1_s_GyroDev_GSensNotifCondFunc(const U1 u1_a_type);
static U1 u1_s_GyroDev_GSensCtrlOutFunc(const U1 u1_a_type);
static void vd_s_GyroDev_Memset(void * vdp_a_dst, const U1 u1_a_data, U4 u4_a_size);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U2 GYRODEV_CYCCHK_POLING = (U2)(10U / GYRODEV_TASK_TIME);         /* Gyro Device Poling Check Time t6 : 10ms */

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

static const ST_REG_WRI_REQ GYRODEV_INT_ANYMOT_TH_SET1[GYRODEV_INT_ANYMOT_TH_SET1_WRINUM] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         2,         0}
};

static const ST_REG_WRI_REQ GYRODEV_INT_ANYMOT_TH_SET2[GYRODEV_INT_ANYMOT_TH_SET2_WRINUM] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         3,         0}
};

static const ST_REG_WRI_REQ GYRODEV_INT_ANYMOT_EN_SET1[GYRODEV_INT_ANYMOT_EN_SET1_WRINUM] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         2,         0}
};

static const ST_REG_WRI_REQ GYRODEV_INT_ANYMOT_EN_SET2[GYRODEV_INT_ANYMOT_EN_SET2_WRINUM] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         3,         0}
};

static const ST_REG_WRI_REQ GYRODEV_INT2_IO_CONF_SET[GYRODEV_INT2_IO_CONF_SET_WRINUM] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};

static const ST_REG_WRI_REQ GYRODEV_INTAPI_OUTPUTON_SET[GYRODEV_INTAPI_OUTPUTON_SET_WRINUM] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};

static const ST_REG_WRI_REQ GYRODEV_INTAPI_OUTPUTOFF_SET[GYRODEV_INTAPI_OUTPUTOFF_SET_WRINUM] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};

const U1 u1_sp_GYRODEV_GYRODATA_RD_PDU1[GYRODEV_I2C_RWC_BYTE2] = {
    (U1)GYRODEV_GYRO_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x02U     /* Write Address */
};

U1 u1_sp_GYRODEV_GYRODATA_RD_PDU2[GYRODEV_I2C_RWC_BYTE8];

const U1 u1_sp_GYRODEV_GSENSDATA_RD_PDU1[GYRODEV_I2C_RWC_BYTE2] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x12U     /* Write Address */
};

U1 u1_sp_GYRODEV_GSENSDATA_RD_PDU2[GYRODEV_I2C_RWC_BYTE7];

const U1 u1_sp_GYRODEV_GSENSDATA_RD2_PDU1[GYRODEV_I2C_RWC_BYTE2] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x22U     /* Read Address 1 */

};

U1 u1_sp_GYRODEV_GSENSDATA_RD2_PDU2[GYRODEV_I2C_RWC_BYTE3];

const U1 u1_sp_GYRODEV_INT2_IO_CONF_RD_PDU1[GYRODEV_I2C_RWC_BYTE2] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x54U     /* Write Address */
};

U1 u1_sp_GYRODEV_INT2_IO_CONF_RD_PDU2[GYRODEV_I2C_RWC_BYTE2];

U1 u1_sp_GYRODEV_INT2_IO_CONF_SET_PDU1[GYRODEV_I2C_RWC_BYTE3];

const U1 u1_sp_GYRODEV_INTAPI_OUTPUTRST_RD_PDU1[GYRODEV_I2C_RWC_BYTE2] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1CU     /* Write Address */
};

U1 u1_sp_GYRODEV_INTAPI_OUTPUTRST_RD_PDU2[GYRODEV_I2C_RWC_BYTE2];

const U1 u1_sp_GYRODEV_INT_ANYMOT_TH_SET1_PDU1[GYRODEV_I2C_RWC_BYTE3] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x5BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_GYRODEV_INT_ANYMOT_TH_SET1_PDU2[GYRODEV_I2C_RWC_BYTE3] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x5CU,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_GYRODEV_INT_ANYMOT_RD_PDU1[GYRODEV_I2C_RWC_BYTE3] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x5EU     /* Write Address */
};

U1 u1_sp_GYRODEV_INT_ANYMOT_RD_PDU2[GYRODEV_I2C_RWC_BYTE4];

U1 u1_sp_GYRODEV_INT_ANYMOT_SET_PDU1[GYRODEV_I2C_RWC_BYTE4];

const U1 u1_sp_GYRODEV_INT_ANYMOT_EN_SET1_PDU1[GYRODEV_I2C_RWC_BYTE3] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x5BU,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_GYRODEV_INT_ANYMOT_EN_SET1_PDU2[GYRODEV_I2C_RWC_BYTE3] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x5CU,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_GYRODEV_INTAPI_OUTPUTON_SET_PDU1[GYRODEV_I2C_RWC_BYTE3] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x57U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_GYRODEV_INTAPI_OUTPUTOFF_SET_PDU1[GYRODEV_I2C_RWC_BYTE3] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x57U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

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

const ST_GP_I2C_MA_REQ st_sp_GYRODEV_INT2_IO_CONF_RD_TBL[2] = {
    {
        (U1 *)&u1_sp_GYRODEV_INT2_IO_CONF_RD_PDU1[0],
        (U4)0x70140002U
    },
    {
        (U1 *)&u1_sp_GYRODEV_INT2_IO_CONF_RD_PDU2[0],
        (U4)0x70180002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GYRODEV_INT2_IO_CONF_SET_TBL[1] = {
    {
        (U1 *)&u1_sp_GYRODEV_INT2_IO_CONF_SET_PDU1[0],
        (U4)0x701C0003U
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

const ST_GP_I2C_MA_REQ st_sp_GYRODEV_INT_ANYMOT_TH_SET1_TBL[2] = {
    {
        (U1 *)&u1_sp_GYRODEV_INT_ANYMOT_TH_SET1_PDU1[0],
        (U4)0x70280003U
    },
    {
        (U1 *)&u1_sp_GYRODEV_INT_ANYMOT_TH_SET1_PDU2[0],
        (U4)0x702C0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GYRODEV_INT_ANYMOT_RD_TBL[2] = {
    {
        (U1 *)&u1_sp_GYRODEV_INT_ANYMOT_RD_PDU1[0],
        (U4)0x70300002U
    },
    {
        (U1 *)&u1_sp_GYRODEV_INT_ANYMOT_RD_PDU2[0],
        (U4)0x70340003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GYRODEV_INT_ANYMOT_TH_SET2_TBL[3] = {
    {
        (U1 *)&u1_sp_GYRODEV_INT_ANYMOT_TH_SET1_PDU1[0],
        (U4)0x70380003U
    },
    {
        (U1 *)&u1_sp_GYRODEV_INT_ANYMOT_TH_SET1_PDU2[0],
        (U4)0x703C0003U
    },
    {
        (U1 *)&u1_sp_GYRODEV_INT_ANYMOT_SET_PDU1[0],
        (U4)0x70400004U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GYRODEV_INT_ANYMOT_EN_SET1_TBL[2] = {
    {
        (U1 *)&u1_sp_GYRODEV_INT_ANYMOT_EN_SET1_PDU1[0],
        (U4)0x70440003U
    },
    {
        (U1 *)&u1_sp_GYRODEV_INT_ANYMOT_EN_SET1_PDU2[0],
        (U4)0x70480003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GYRODEV_INT_ANYMOT_EN_SET2_TBL[3] = {
    {
        (U1 *)&u1_sp_GYRODEV_INT_ANYMOT_EN_SET1_PDU1[0],
        (U4)0x704C0003U
    },
    {
        (U1 *)&u1_sp_GYRODEV_INT_ANYMOT_EN_SET1_PDU2[0],
        (U4)0x70500003U
    },
    {
        (U1 *)&u1_sp_GYRODEV_INT_ANYMOT_SET_PDU1[0],
        (U4)0x70540004U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GYRODEV_INTAPI_OUTPUTON_SET_TBL[1] = {
    {
        (U1 *)&u1_sp_GYRODEV_INTAPI_OUTPUTON_SET_PDU1[0],
        (U4)0x70580003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GYRODEV_INTAPI_OUTPUTOFF_SET_TBL[1] = {
    {
        (U1 *)&u1_sp_GYRODEV_INTAPI_OUTPUTOFF_SET_PDU1[0],
        (U4)0x705C0003U
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

    vd_s_GyroDev_Memset(&st_gyrodev_readdata, (U1)0U, sizeof(st_gyrodev_readdata));
    st_gyrodev_readdata.u1_gyro_x_data_sts = (U1)GYRODEV_READ_DATA_NG;
    st_gyrodev_readdata.u1_gyro_y_data_sts = (U1)GYRODEV_READ_DATA_NG;
    st_gyrodev_readdata.u1_gyro_z_data_sts = (U1)GYRODEV_READ_DATA_NG;
    st_gyrodev_readdata.u1_gyro_temp_data_sts = (U1)GYRODEV_READ_DATA_NG;
    st_gyrodev_readdata.u1_accl_x_data_sts = (U1)GYRODEV_READ_DATA_NG;
    st_gyrodev_readdata.u1_accl_y_data_sts = (U1)GYRODEV_READ_DATA_NG;
    st_gyrodev_readdata.u1_accl_z_data_sts = (U1)GYRODEV_READ_DATA_NG;
    st_gyrodev_readdata.u1_accl_temp_data_sts = (U1)GYRODEV_READ_DATA_NG;

    u1_s_gyrodev_pre_appon_sts = (U1)GYRODEV_APPOFF;

    u1_s_gyrodev_dtcrec_a_flag = (U1)FALSE;

    u1_s_gyrodev_notifcondset_sts = (U1)GYRODEV_NOTIFCONDSET_STEP0;
    u1_s_gyrodev_oscmd_notifcond_rcv_flag = (U1)FALSE;
    u1_s_gyrodev_oscmd_notifcond_bak_flag = (U1)FALSE;
    vd_s_GyroDev_Memset(&st_gyrodev_notifcond_setreq, (U1)0U, sizeof(st_gyrodev_notifcond_setreq));
    vd_s_GyroDev_Memset(&st_gyrodev_notifcond_setbak, (U1)0U, sizeof(st_gyrodev_notifcond_setbak));
    u1_s_gyrodev_oscmd_notifcond_read_flag = (U1)FALSE;
    vd_s_GyroDev_Memset(&st_gyrodev_notifcond_readreq, (U1)0U, sizeof(st_gyrodev_notifcond_readreq));

    u1_s_gyrodev_ctrloutset_sts = (U1)GYRODEV_CTRLOUTSET_STEP0;
    u1_s_gyrodev_oscmd_outctl_rcv_flag = (U1)FALSE;
    u1_s_gyrodev_oscmd_outctl_bak_flag = (U1)FALSE;
    vd_s_GyroDev_Memset(&st_gyrodev_ctrlout_setreq, (U1)0U, sizeof(st_gyrodev_ctrlout_setreq));
    vd_s_GyroDev_Memset(&st_gyrodev_ctrlout_setbak, (U1)0U, sizeof(st_gyrodev_ctrlout_setbak));

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
    u1_sp_GYRODEV_INT2_IO_CONF_RD_PDU2[0] = (U1)GYRODEV_GSENS_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_GYRODEV_INT2_IO_CONF_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /* INT2_IO_CONFレジスタ(0x54)bin制御用設定 書込み用テーブル(Data可変)初期化 */
    u1_sp_GYRODEV_INT2_IO_CONF_SET_PDU1[0] = (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_GYRODEV_INT2_IO_CONF_SET_PDU1[1] = (U1)0x54U;    /* Write Address */
    u1_sp_GYRODEV_INT2_IO_CONF_SET_PDU1[2] = (U1)0U;    /* Write Data初期値(定期処理内で更新) */

    /*  データリード用テーブル初期化 */
    u1_sp_GYRODEV_INTAPI_OUTPUTRST_RD_PDU2[0] = (U1)GYRODEV_GSENS_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_GYRODEV_INTAPI_OUTPUTRST_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル(BurstRead)初期化 */
    u1_sp_GYRODEV_INT_ANYMOT_RD_PDU2[0] = (U1)GYRODEV_GSENS_I2C_SLAVEADR_RD;    /* Slave Address */
    for(u2_t_cnt = (U2)1U; u2_t_cnt < (U2)GYRODEV_I2C_RWC_BYTE4; u2_t_cnt++) {
        u1_sp_GYRODEV_INT_ANYMOT_RD_PDU2[u2_t_cnt] = (U1)0U;    /* 読出しデータ初期値 */
    }

    /*  書込み用テーブル(Data可変)初期化 */
    u1_sp_GYRODEV_INT_ANYMOT_SET_PDU1[0] = (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_GYRODEV_INT_ANYMOT_SET_PDU1[1] = (U1)0x5EU;    /* Write Address */
    u1_sp_GYRODEV_INT_ANYMOT_SET_PDU1[2] = (U1)0U;    /* Write Data1初期値(定期処理内で更新) */
    u1_sp_GYRODEV_INT_ANYMOT_SET_PDU1[3] = (U1)0U;    /* Write Data2初期値(定期処理内で更新) */
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

    u2_s_gyrodev_regstep = (U2)0;
    u4_s_gyrodev_i2c_ack_wait_time = (U4)0;
    u2_s_gyrodev_reg_btwn_time = (U2)0xFFFFU;

    vd_s_GyroDev_Memset(&st_gyrodev_readdata, (U1)0U, sizeof(st_gyrodev_readdata));
    st_gyrodev_readdata.u1_gyro_x_data_sts = (U1)GYRODEV_READ_DATA_NG;
    st_gyrodev_readdata.u1_gyro_y_data_sts = (U1)GYRODEV_READ_DATA_NG;
    st_gyrodev_readdata.u1_gyro_z_data_sts = (U1)GYRODEV_READ_DATA_NG;
    st_gyrodev_readdata.u1_gyro_temp_data_sts = (U1)GYRODEV_READ_DATA_NG;
    st_gyrodev_readdata.u1_accl_x_data_sts = (U1)GYRODEV_READ_DATA_NG;
    st_gyrodev_readdata.u1_accl_y_data_sts = (U1)GYRODEV_READ_DATA_NG;
    st_gyrodev_readdata.u1_accl_z_data_sts = (U1)GYRODEV_READ_DATA_NG;
    st_gyrodev_readdata.u1_accl_temp_data_sts = (U1)GYRODEV_READ_DATA_NG;

    u1_s_gyrodev_pre_appon_sts = (U1)GYRODEV_APPOFF;

    u1_s_gyrodev_dtcrec_a_flag = (U1)FALSE;

    u1_s_gyrodev_notifcondset_sts = (U1)GYRODEV_NOTIFCONDSET_STEP0;
    u1_s_gyrodev_oscmd_notifcond_rcv_flag = (U1)FALSE;
    vd_s_GyroDev_Memset(&st_gyrodev_notifcond_setreq, (U1)0U, sizeof(st_gyrodev_notifcond_setreq));
    u1_s_gyrodev_oscmd_notifcond_read_flag = (U1)FALSE;
    vd_s_GyroDev_Memset(&st_gyrodev_notifcond_readreq, (U1)0U, sizeof(st_gyrodev_notifcond_readreq));

    u1_s_gyrodev_ctrloutset_sts = (U1)GYRODEV_CTRLOUTSET_STEP0;
    u1_s_gyrodev_oscmd_outctl_rcv_flag = (U1)FALSE;
    vd_s_GyroDev_Memset(&st_gyrodev_ctrlout_setreq, (U1)0U, sizeof(st_gyrodev_ctrlout_setreq));

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
    u1_sp_GYRODEV_INT2_IO_CONF_RD_PDU2[0] = (U1)GYRODEV_GSENS_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_GYRODEV_INT2_IO_CONF_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /* INT2_IO_CONFレジスタ(0x54)bin制御用設定 書込み用テーブル(Data可変)初期化 */
    u1_sp_GYRODEV_INT2_IO_CONF_SET_PDU1[0] = (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_GYRODEV_INT2_IO_CONF_SET_PDU1[1] = (U1)0x54U;    /* Write Address */
    u1_sp_GYRODEV_INT2_IO_CONF_SET_PDU1[2] = (U1)0U;    /* Write Data初期値(定期処理内で更新) */

    /*  データリード用テーブル初期化 */
    u1_sp_GYRODEV_INTAPI_OUTPUTRST_RD_PDU2[0] = (U1)GYRODEV_GSENS_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_GYRODEV_INTAPI_OUTPUTRST_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル(BurstRead)初期化 */
    u1_sp_GYRODEV_INT_ANYMOT_RD_PDU2[0] = (U1)GYRODEV_GSENS_I2C_SLAVEADR_RD;    /* Slave Address */
    for(u2_t_cnt = (U2)1U; u2_t_cnt < (U2)GYRODEV_I2C_RWC_BYTE4; u2_t_cnt++) {
        u1_sp_GYRODEV_INT_ANYMOT_RD_PDU2[u2_t_cnt] = (U1)0U;    /* 読出しデータ初期値 */
    }

    /*  書込み用テーブル(Data可変)初期化 */
    u1_sp_GYRODEV_INT_ANYMOT_SET_PDU1[0] = (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_GYRODEV_INT_ANYMOT_SET_PDU1[1] = (U1)0x5EU;    /* Write Address */
    u1_sp_GYRODEV_INT_ANYMOT_SET_PDU1[2] = (U1)0U;    /* Write Data1初期値(定期処理内で更新) */
    u1_sp_GYRODEV_INT_ANYMOT_SET_PDU1[3] = (U1)0U;    /* Write Data2初期値(定期処理内で更新) */
}

/*===================================================================================================================================*/
/*  void    vd_g_GyroDev_Routine(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GyroDev_Routine(void)
{
    U1  u1_t_modests;                                                               /* Gyro G-Sensor Power ON Maneger Mode Status */

    switch (u1_s_gyrodev_state){
        case GYRODEV_SEQ_IDLE:                                                      /* IDLE */
            /* Timer Clear */
            u2_s_gyrodev_cycchk_timer = (U2)0;

            /* Power ON Check */
            u1_t_modests = vd_GYRODEV_GET_MODESTS();
            if(u1_t_modests == (U1)GYRODEV_MODE_NORMAL){                            /* Mode : Normal */
                /* State Update */
                u1_s_gyrodev_state = (U1)GYRODEV_SEQ_CYC;
                /* Poling Check Start */
                u2_s_gyrodev_cycchk_timer = (U2)GYRODEV_CYCCHK_POLING;
            }
            break;
        case GYRODEV_SEQ_CYC:                                                       /* CYCLIC */
            vd_s_vd_g_GyroDev_CycChk();
            break;
        default:                                                                    /* FAIL */
            vd_g_GyroDev_BonInit();
            break;
    }

    /* Ack Wait Timer Countr Increment */
    if(u4_s_gyrodev_i2c_ack_wait_time < (U4)U4_MAX){
        u4_s_gyrodev_i2c_ack_wait_time++;
    }
    /* Poling Check Timer Countr Increment */
    if(u2_s_gyrodev_cycchk_timer < (U2)U2_MAX){
        u2_s_gyrodev_cycchk_timer++;
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
    U1      u1_t_func_sts;                                          /* Function Status */
    U1      u1_t_time_chk_flg;
    U1      u1_t_reg_req_sts;                                       /* Register Read/Write Request Status */
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

    u1_t_func_sts = (U1)FALSE;

    switch (u1_s_gyrodev_cycchk_sts){
        case GYRODEV_CYCCHK_STEP0:                                      /* STEP0 */
            u1_t_time_chk_flg = u1_s_GyroDev_TimChk(u2_s_gyrodev_cycchk_timer, GYRODEV_CYCCHK_POLING);
            if(u1_t_time_chk_flg == (U1)TRUE){
                /* Timer Clear */
                u2_s_gyrodev_cycchk_timer = (U2)0;
                /* Next Process */
                u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP1;
            }
            break;
        case GYRODEV_CYCCHK_STEP1:                                      /* STEP1 */
            u1_t_v33_peri_on_sts = u1_GYRODEV_GET_V33_PERI_ON();
            if(u1_t_v33_peri_on_sts == (U1)TRUE){
                /* Read Date Initialization */
                vd_s_GyroDev_Memset(&st_gyrodev_readdata, (U1)0U, sizeof(st_gyrodev_readdata));
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
                u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP7;
            }
            break;
        case GYRODEV_CYCCHK_STEP2:                                      /* STEP2 */
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
            u1_t_func_sts = u1_s_GyroDev_GSensNotifCondFunc((U1)GYRODEV_GSENS_NOTIFCONDFUNC_SETREQ);
            if(u1_t_func_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP6;
            }
            break;
        case GYRODEV_CYCCHK_STEP6:                                      /* STEP6 */
            u1_t_func_sts = u1_s_GyroDev_GSensCtrlOutFunc((U1)GYRODEV_GSENS_CTRLOUTFUNC_SETREQ);
            if(u1_t_func_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP7;
            }
            break;
        case GYRODEV_CYCCHK_STEP7:                                      /* STEP7 */
            u1_t_appon_sts = u1_GYRODEV_GET_APP_ON();
            if((u1_t_appon_sts == (U1)GYRODEV_APPOFF)
            && (u1_s_gyrodev_pre_appon_sts == (U1)GYRODEV_APPON)){
                /* Next Process */
                u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP8;
            }
            else{
                /* Process Reset */
                u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP10;
            }
            /* Previous State Update */
            u1_s_gyrodev_pre_appon_sts = u1_t_appon_sts;
            break;
        case GYRODEV_CYCCHK_STEP8:                                      /* STEP8 */
            u1_t_func_sts = u1_s_GyroDev_GSensNotifCondFunc((U1)GYRODEV_GSENS_NOTIFCONDFUNC_BACKUP);
            if(u1_t_func_sts == (U1)TRUE){
                /* Process Reset */
                u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP9;
            }
            break;
        case GYRODEV_CYCCHK_STEP9:                                      /* STEP9 */
            u1_t_func_sts = u1_s_GyroDev_GSensCtrlOutFunc((U1)GYRODEV_GSENS_CTRLOUTFUNC_BACKUP);
            if(u1_t_func_sts == (U1)TRUE){
                /* Process Reset */
                u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP10;
            }
            break;
        case GYRODEV_CYCCHK_STEP10:                                     /* STEP10 */
            u1_t_func_sts = u1_s_GyroDev_GSensNotifCondFunc((U1)GYRODEV_GSENS_NOTIFCONDFUNC_READREQ);
            if(u1_t_func_sts == (U1)TRUE){
                /* Process Reset */
                u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP0;
            }
            break;
        default:                                                        /* FAIL */
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

                vd_GYRODEV_DREC_REQ((U1)SYSECDRC_DREC_ID_4, (U1)0x00U, (U1)0x00U);

                /* Gyro Fail DTC Record */
                vd_GYRODEV_DTC_REQ((U1)DTCCTL_DTCID_GYR_ERR, (U1)GYRODEV_DTC_STS_FAIL);
                u1_s_gyrodev_dtcrec_a_flag = (U1)FALSE;

                if(u1_s_gyrodev_gyro_rst_cnt >= (U2)GYRODEV_GYRODTC_RSTCNT_MAX){    /* Reset Count >= n(6_3) */
                    /* Counter Clear */
                    u2_s_gyrodev_gyro_max_err_cnt = (U2)0;
                    u2_s_gyrodev_gyro_min_err_cnt = (U2)0;
                    u1_s_gyrodev_gyro_rst_cnt = (U1)0;
                    /* Event Set */
                    vd_GYRODEV_DEVICE_EVENT(GYRODEV_EVENT_DTC_ERR);
                    /* State Reset */
                    u1_s_gyrodev_state = (U1)GYRODEV_SEQ_IDLE;
                    /* Process Reset */
                    u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP0;
                }
                else{
                    u1_s_gyrodev_gyro_rst_cnt++;
                    /* Event Set */
                    vd_GYRODEV_DEVICE_EVENT(GYRODEV_EVENT_DEV_RST);
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
                /* Gyro Normal DTC Record */
                vd_GYRODEV_DTC_REQ((U1)DTCCTL_DTCID_GYR_ERR, (U1)GYRODEV_DTC_STS_NORMAL);
                u1_s_gyrodev_dtcrec_a_flag = (U1)TRUE;
            }
        }
    }
    else{
        /* Error Counter Clear */
        u2_s_gyrodev_gyro_max_err_cnt = (U2)0;
        u2_s_gyrodev_gyro_min_err_cnt = (U2)0;
        u1_s_gyrodev_gyro_rst_cnt = (U1)0;
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

            vd_GYRODEV_DREC_REQ((U1)SYSECDRC_DREC_ID_5, (U1)0x00U, (U1)0x00U);

            /* G Sonsor Fail DTC Record */
            vd_GYRODEV_DTC_REQ((U1)DTCCTL_DTCID_GSNS_ERR, (U1)GYRODEV_DTC_STS_FAIL);
            u1_s_gyrodev_dtcrec_a_flag = (U1)FALSE;

            if(u1_s_gyrodev_gsens_rst_cnt >= (U2)GYRODEV_GSENSDTC_RSTCNT_MAX){            /* Reset Count >= n(6_3) */
                /* Counter Clear */
                u2_s_gyrodev_gsens_max_err_cnt = (U2)0;
                u2_s_gyrodev_gsens_min_err_cnt = (U2)0;
                u1_s_gyrodev_gsens_rst_cnt = (U1)0;
                /* Event Set */
                vd_GYRODEV_DEVICE_EVENT(GYRODEV_EVENT_DTC_ERR);
                /* State Reset */
                u1_s_gyrodev_state = (U1)GYRODEV_SEQ_IDLE;
                /* Process Reset */
                u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP0;
            }
            else{
                u1_s_gyrodev_gsens_rst_cnt++;
                /* Event Set */
                vd_GYRODEV_DEVICE_EVENT(GYRODEV_EVENT_DEV_RST);
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
            /* G Sonsor Normal DTC Record */
            vd_GYRODEV_DTC_REQ((U1)DTCCTL_DTCID_GSNS_ERR, (U1)GYRODEV_DTC_STS_NORMAL);
            u1_s_gyrodev_dtcrec_a_flag = (U1)TRUE;
        }
    }
}

/*===================================================================================================================================*/
/*  U1    u1_s_GyroDev_GSensNotifCondFunc(const U1 u1_a_type)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_GyroDev_GSensNotifCondFunc(const U1 u1_a_type)
{
    U1      u1_t_ret;                                               /* Function Completion Status  */
    U1      u1_t_req_result;                                        /* SiP -> MCU Request Result */
    U1      u1_t_reg_req_sts;                                       /* Register Read/Write Request Status */
    U1      u1_t_gsens_int_anymot_th_lsb_data;                      /* G-Sensor INT_ANYMOT_TH Register LSB Data */
    U1      u1_t_gsens_int_anymot_th_msb_data;                      /* G-Sensor INT_ANYMOT_TH Register MSB Data */
    U1      u1_t_gsens_int_anymot_en_lsb_data;                      /* G-Sensor INT_ANYMOT_EN Register LSB Data */
    U1      u1_t_gsens_int_anymot_en_msb_data;                      /* G-Sensor INT_ANYMOT_EN Register MSB Data */
    U1      u1_t_gsens_int2_io_conf_data;                           /* G-Sensor INT2_IO_CONF Register Data */
    U4      u4_t_gsens_anymot_thd_calc_data;                        /* G-Sensor anymot_th Conversion Calculation Data */
    U1      u1_t_gsens_threshold_calc_data;                         /* G-Sensor Threshold Conversion Calculation Data */
    U1      u1_t_gsens_axis_read;                                   /* G-Sensor uc_axis x/y/z Reading Data */

    u1_t_ret = (U1)FALSE;
    u1_t_req_result = (U1)GYRODEV_GSENS_NOTIFCOND_REQ_INI;

    switch (u1_s_gyrodev_notifcondset_sts){
        case GYRODEV_NOTIFCONDSET_STEP0:                            /* STEP0 */
            if(u1_a_type == (U1)GYRODEV_GSENS_NOTIFCONDFUNC_SETREQ){                    /* SiP -> MCU Setting Request */
                if(u1_s_gyrodev_oscmd_notifcond_rcv_flag == (U1)TRUE){
                    /* Flag Clear */
                    u1_s_gyrodev_oscmd_notifcond_rcv_flag = (U1)FALSE;
                    /* Request Backup Check */
                    if(st_gyrodev_notifcond_setreq.u1_active == (U1)GYRODEV_GSENS_INT_LVL_ACT_HI){  /* uc_active = LSDRV_GSNS_INT_COND_ACTIVE_HIGH */
                        /* Backup Flag Set */
                        u1_s_gyrodev_oscmd_notifcond_bak_flag = (U1)TRUE;
                        /* Input Parameter Retention */
                        st_gyrodev_notifcond_setbak = st_gyrodev_notifcond_setreq;
                    }
                    /* Next Process */
                    u1_s_gyrodev_notifcondset_sts = (U1)GYRODEV_NOTIFCONDSET_STEP1;
                }
                else{
                    /* Function Completion */
                    u1_t_ret = (U1)TRUE;
                }
            }
            else if(u1_a_type == (U1)GYRODEV_GSENS_NOTIFCONDFUNC_BACKUP){               /* Power ON -> OFF Event Setting */
                if(u1_s_gyrodev_oscmd_notifcond_bak_flag == (U1)TRUE){
                    /* Backup Request Data Set */
                    st_gyrodev_notifcond_setreq = st_gyrodev_notifcond_setbak;
                    /* Next Process */
                    u1_s_gyrodev_notifcondset_sts = (U1)GYRODEV_NOTIFCONDSET_STEP1;
                }
                else{
                    /* Set uc_active = LSDRV_GSNS_INT_COND_ACTIVE_HIGH */
                    st_gyrodev_notifcond_setreq.u1_active = (U1)GYRODEV_GSENS_INT_LVL_ACT_HI;
                    /* Next Process */
                    u1_s_gyrodev_notifcondset_sts = (U1)GYRODEV_NOTIFCONDSET_STEP7;
                }
            }
            else if(u1_a_type == (U1)GYRODEV_GSENS_NOTIFCONDFUNC_READREQ){              /* SiP -> MCU Reading Request */
                if(u1_s_gyrodev_oscmd_notifcond_read_flag == (U1)TRUE){
                    /* Read Date Initialization */
                    vd_s_GyroDev_Memset(&st_gyrodev_notifcond_readreq, (U1)0U, sizeof(st_gyrodev_notifcond_readreq));
                    /* Flag Clear */
                    u1_s_gyrodev_oscmd_notifcond_read_flag = (U1)FALSE;
                    /* Next Process */
                    u1_s_gyrodev_notifcondset_sts = (U1)GYRODEV_NOTIFCONDSET_STEP9;
                }
                else{
                    /* Function Completion */
                    u1_t_ret = (U1)TRUE;
                }
            }
            else{                                                                       /* Fail */
                /* Nothing */
            }
            break;
        case GYRODEV_NOTIFCONDSET_STEP1:                            /* STEP1 */
        /* --------------- f_threshold Setting --------------- */
            /* Set Register G-Sensor */
            u1_t_reg_req_sts = u1_GYRODEV_GSENS_I2C_CTRL_REGSET(&u2_s_gyrodev_regstep, (U2)GYRODEV_INT_ANYMOT_TH_SET1_WRINUM,
                                                                GYRODEV_INT_ANYMOT_TH_SET1, &u4_s_gyrodev_i2c_ack_wait_time,
                                                                st_sp_GYRODEV_INT_ANYMOT_TH_SET1_TBL, &u2_s_gyrodev_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gyrodev_notifcondset_sts = (U1)GYRODEV_NOTIFCONDSET_STEP2;
            }
            break;
        case GYRODEV_NOTIFCONDSET_STEP2:                            /* STEP2 */
            /* Read Register G-Sensor */
            u1_t_reg_req_sts = u1_GYRODEV_GSENS_I2C_CTRL_REGREAD(&u2_s_gyrodev_regstep, &u4_s_gyrodev_i2c_ack_wait_time,
                                                                 st_sp_GYRODEV_INT_ANYMOT_RD_TBL, &u2_s_gyrodev_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                u1_t_gsens_int_anymot_th_lsb_data = st_sp_GYRODEV_INT_ANYMOT_RD_TBL[1].u1p_pdu[1];  /* INT_ANYMOT_TH bit[7:0] - Not used for Overwriting */
                u1_t_gsens_int_anymot_th_msb_data = st_sp_GYRODEV_INT_ANYMOT_RD_TBL[1].u1p_pdu[2];  /* INT_ANYMOT_TH bit[15:8] */
                u1_t_gsens_int_anymot_th_msb_data &= ~(U1)GYRODEV_GSENS_INT_THD_MSB_MASK;           /* INT_ANYMOT_TH bit[10:8] = 0b000 */
                u4_t_gsens_anymot_thd_calc_data = ((U4)st_gyrodev_notifcond_setreq.u1_threshold * (U4)GYRODEV_GSENS_INT_THD_RESO) / (U4)GYRODEV_GSENS_INT_THD_MULT;   /* Threshold Conversion */
                u1_t_gsens_int_anymot_th_lsb_data = (U1)(u4_t_gsens_anymot_thd_calc_data & (U4)GYRODEV_GSENS_INT_THD_LSB_MASK);  /* INT_ANYMOT_TH bit[7:0] */
                u1_t_gsens_int_anymot_th_msb_data |= (U1)(u4_t_gsens_anymot_thd_calc_data >> (U4)GYRODEV_REG_BIT_SHIFT_8) & (U1)GYRODEV_GSENS_INT_THD_MSB_MASK; /* INT_ANYMOT_TH bit[10:8] */
                st_sp_GYRODEV_INT_ANYMOT_TH_SET2_TBL[2].u1p_pdu[2] = u1_t_gsens_int_anymot_th_lsb_data;     /* Register Write Data(LSB) Set */
                st_sp_GYRODEV_INT_ANYMOT_TH_SET2_TBL[2].u1p_pdu[3] = u1_t_gsens_int_anymot_th_msb_data;     /* Register Write Data(MSB) Set */

                /* Next Process */
                u1_s_gyrodev_notifcondset_sts = (U1)GYRODEV_NOTIFCONDSET_STEP3;
            }
            break;
        case GYRODEV_NOTIFCONDSET_STEP3:                            /* STEP3 */
            /* Set Register G-Sensor */
            u1_t_reg_req_sts = u1_GYRODEV_GSENS_I2C_CTRL_REGSET(&u2_s_gyrodev_regstep, (U2)GYRODEV_INT_ANYMOT_TH_SET2_WRINUM,
                                                                GYRODEV_INT_ANYMOT_TH_SET2, &u4_s_gyrodev_i2c_ack_wait_time,
                                                                st_sp_GYRODEV_INT_ANYMOT_TH_SET2_TBL, &u2_s_gyrodev_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gyrodev_notifcondset_sts = (U1)GYRODEV_NOTIFCONDSET_STEP4;
            }
            break;
        case GYRODEV_NOTIFCONDSET_STEP4:                            /* STEP4 */
        /* --------------- uc_axis Setting --------------- */
            /* Set Register G-Sensor */
            u1_t_reg_req_sts = u1_GYRODEV_GSENS_I2C_CTRL_REGSET(&u2_s_gyrodev_regstep, (U2)GYRODEV_INT_ANYMOT_EN_SET1_WRINUM,
                                                                GYRODEV_INT_ANYMOT_EN_SET1, &u4_s_gyrodev_i2c_ack_wait_time,
                                                                st_sp_GYRODEV_INT_ANYMOT_EN_SET1_TBL, &u2_s_gyrodev_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gyrodev_notifcondset_sts = (U1)GYRODEV_NOTIFCONDSET_STEP5;
            }
            break;
        case GYRODEV_NOTIFCONDSET_STEP5:                            /* STEP5 */
            /* Read Register G-Sensor */
            u1_t_reg_req_sts = u1_GYRODEV_GSENS_I2C_CTRL_REGREAD(&u2_s_gyrodev_regstep, &u4_s_gyrodev_i2c_ack_wait_time,
                                                                 st_sp_GYRODEV_INT_ANYMOT_RD_TBL, &u2_s_gyrodev_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                u1_t_gsens_int_anymot_en_lsb_data = st_sp_GYRODEV_INT_ANYMOT_RD_TBL[1].u1p_pdu[1];  /* INT_ANYMOT_EN bit[7:0] */
                u1_t_gsens_int_anymot_en_msb_data = st_sp_GYRODEV_INT_ANYMOT_RD_TBL[1].u1p_pdu[2];  /* INT_ANYMOT_EN bit[15:8] */
                u1_t_gsens_int_anymot_en_msb_data &= ~(U1)GYRODEV_GSENS_INT_AXIS_MSB_MASK;          /* INT_ANYMOT_EN bit[15:13] = 0b000 */
                if(st_gyrodev_notifcond_setreq.u1_axis_x == (U1)GYRODEV_GSENS_INT_AXIS_ACT){
                    u1_t_gsens_int_anymot_en_msb_data |= (U1)GYRODEV_REG_MASK_BIT_5;                /* INT_ANYMOT_EN bit[13] = 0b1 */
                }
                if(st_gyrodev_notifcond_setreq.u1_axis_y == (U1)GYRODEV_GSENS_INT_AXIS_ACT){
                    u1_t_gsens_int_anymot_en_msb_data |= (U1)GYRODEV_REG_MASK_BIT_6;                /* INT_ANYMOT_EN bit[14] = 0b1 */
                }
                if(st_gyrodev_notifcond_setreq.u1_axis_z == (U1)GYRODEV_GSENS_INT_AXIS_ACT){
                    u1_t_gsens_int_anymot_en_msb_data |= (U1)GYRODEV_REG_MASK_BIT_7;                /* INT_ANYMOT_EN bit[15] = 0b1 */
                }
                st_sp_GYRODEV_INT_ANYMOT_EN_SET2_TBL[2].u1p_pdu[2] = u1_t_gsens_int_anymot_en_lsb_data;     /* Register Write Data(LSB) Set */
                st_sp_GYRODEV_INT_ANYMOT_EN_SET2_TBL[2].u1p_pdu[3] = u1_t_gsens_int_anymot_en_msb_data;     /* Register Write Data(LSB) Set */

                /* Next Process */
                u1_s_gyrodev_notifcondset_sts = (U1)GYRODEV_NOTIFCONDSET_STEP6;
            }
            break;
        case GYRODEV_NOTIFCONDSET_STEP6:                            /* STEP6 */
            /* Set Register G-Sensor */
            u1_t_reg_req_sts = u1_GYRODEV_GSENS_I2C_CTRL_REGSET(&u2_s_gyrodev_regstep, (U2)GYRODEV_INT_ANYMOT_EN_SET2_WRINUM,
                                                                GYRODEV_INT_ANYMOT_EN_SET2, &u4_s_gyrodev_i2c_ack_wait_time,
                                                                st_sp_GYRODEV_INT_ANYMOT_EN_SET2_TBL, &u2_s_gyrodev_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gyrodev_notifcondset_sts = (U1)GYRODEV_NOTIFCONDSET_STEP7;
            }
            break;
        case GYRODEV_NOTIFCONDSET_STEP7:                            /* STEP7 */
        /* --------------- uc_active Setting --------------- */
            /* Read Register G-Sensor */
            u1_t_reg_req_sts = u1_GYRODEV_GSENS_I2C_CTRL_REGREAD(&u2_s_gyrodev_regstep, &u4_s_gyrodev_i2c_ack_wait_time,
                                                                 st_sp_GYRODEV_INT2_IO_CONF_RD_TBL, &u2_s_gyrodev_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                u1_t_gsens_int2_io_conf_data = st_sp_GYRODEV_INT2_IO_CONF_RD_TBL[1].u1p_pdu[1];     /* INT2_IO_CONF bit[7:0] */
                if(st_gyrodev_notifcond_setreq.u1_active == (U1)GYRODEV_GSENS_INT_LVL_ACT_HI){      /* uc_active = LSDRV_GSNS_INT_COND_ACTIVE_HIGH */
                    u1_t_gsens_int2_io_conf_data |= (U1)GYRODEV_REG_MASK_BIT_1;                     /* INT2_IO_CONF bit[1] = 0b1 */
                }
                else if(st_gyrodev_notifcond_setreq.u1_active == (U1)GYRODEV_GSENS_INT_LVL_ACT_LOW){    /* uc_active = LSDRV_GSNS_INT_COND_ACTIVE_LOW */
                    u1_t_gsens_int2_io_conf_data &= ~(U1)GYRODEV_REG_MASK_BIT_1;                    /* INT2_IO_CONF bit[1] = 0b0 */
                }
                else{                                                                               /* uc_active = Invalid Value */
                    /* Nothing */
                }
                st_sp_GYRODEV_INT2_IO_CONF_SET_TBL[0].u1p_pdu[2] = u1_t_gsens_int2_io_conf_data;    /* Register Write Data Set */

                /* Next Process */
                u1_s_gyrodev_notifcondset_sts = (U1)GYRODEV_NOTIFCONDSET_STEP8;
            }
            break;
        case GYRODEV_NOTIFCONDSET_STEP8:                            /* STEP8 */
            /* Set Register G-Sensor */
            u1_t_reg_req_sts = u1_GYRODEV_GSENS_I2C_CTRL_REGSET(&u2_s_gyrodev_regstep, (U2)GYRODEV_INT2_IO_CONF_SET_WRINUM,
                                                                GYRODEV_INT2_IO_CONF_SET, &u4_s_gyrodev_i2c_ack_wait_time,
                                                                st_sp_GYRODEV_INT2_IO_CONF_SET_TBL, &u2_s_gyrodev_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Function Completion */
                u1_t_ret = (U1)TRUE;
                /* Setting Result OK */
                u1_t_req_result = (U1)GYRODEV_GSENS_NOTIFCOND_SET_OK;
                /* Process Reset */
                u1_s_gyrodev_notifcondset_sts = (U1)GYRODEV_NOTIFCONDSET_STEP0;
            }
            break;
        case GYRODEV_NOTIFCONDSET_STEP9:                            /* STEP9 */
        /* --------------- f_threshold Reading --------------- */
            /* Set Register G-Sensor */
            u1_t_reg_req_sts = u1_GYRODEV_GSENS_I2C_CTRL_REGSET(&u2_s_gyrodev_regstep, (U2)GYRODEV_INT_ANYMOT_TH_SET1_WRINUM,
                                                                GYRODEV_INT_ANYMOT_TH_SET1, &u4_s_gyrodev_i2c_ack_wait_time,
                                                                st_sp_GYRODEV_INT_ANYMOT_TH_SET1_TBL, &u2_s_gyrodev_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gyrodev_notifcondset_sts = (U1)GYRODEV_NOTIFCONDSET_STEP10;
            }
            break;
        case GYRODEV_NOTIFCONDSET_STEP10:                           /* STEP10 */
            /* Read Register G-Sensor */
            u1_t_reg_req_sts = u1_GYRODEV_GSENS_I2C_CTRL_REGREAD(&u2_s_gyrodev_regstep, &u4_s_gyrodev_i2c_ack_wait_time,
                                                                 st_sp_GYRODEV_INT_ANYMOT_RD_TBL, &u2_s_gyrodev_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                u1_t_gsens_int_anymot_th_lsb_data = st_sp_GYRODEV_INT_ANYMOT_RD_TBL[1].u1p_pdu[1];  /* INT_ANYMOT_TH bit[7:0] - Not used for Overwriting */
                u1_t_gsens_int_anymot_th_msb_data = st_sp_GYRODEV_INT_ANYMOT_RD_TBL[1].u1p_pdu[2];  /* INT_ANYMOT_TH bit[15:8] */
                u1_t_gsens_int_anymot_th_msb_data &= (U1)GYRODEV_GSENS_INT_THD_MSB_MASK;           /* INT_ANYMOT_TH bit[15:11] = 0b00000 */
                u4_t_gsens_anymot_thd_calc_data = ((U4)u1_t_gsens_int_anymot_th_msb_data  << (U4)GYRODEV_REG_BIT_SHIFT_8) | (U4)u1_t_gsens_int_anymot_th_lsb_data;  /* anymot_th Conversion */
                u1_t_gsens_threshold_calc_data = (U1)(((u4_t_gsens_anymot_thd_calc_data + (U4)1U) * (U4)GYRODEV_GSENS_INT_THD_MULT) / (U4)GYRODEV_GSENS_INT_THD_RESO);  /* anymot_th -> Threshold Conversion */
                st_gyrodev_notifcond_readreq.u1_threshold = u1_t_gsens_threshold_calc_data;

                /* Next Process */
                u1_s_gyrodev_notifcondset_sts = (U1)GYRODEV_NOTIFCONDSET_STEP11;
            }
            break;
        case GYRODEV_NOTIFCONDSET_STEP11:                           /* STEP11 */
        /* --------------- uc_axis Reading --------------- */
            /* Set Register G-Sensor */
            u1_t_reg_req_sts = u1_GYRODEV_GSENS_I2C_CTRL_REGSET(&u2_s_gyrodev_regstep, (U2)GYRODEV_INT_ANYMOT_EN_SET1_WRINUM,
                                                                GYRODEV_INT_ANYMOT_EN_SET1, &u4_s_gyrodev_i2c_ack_wait_time,
                                                                st_sp_GYRODEV_INT_ANYMOT_EN_SET1_TBL, &u2_s_gyrodev_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gyrodev_notifcondset_sts = (U1)GYRODEV_NOTIFCONDSET_STEP12;
            }
            break;
        case GYRODEV_NOTIFCONDSET_STEP12:                           /* STEP12 */
            /* Read Register G-Sensor */
            u1_t_reg_req_sts = u1_GYRODEV_GSENS_I2C_CTRL_REGREAD(&u2_s_gyrodev_regstep, &u4_s_gyrodev_i2c_ack_wait_time,
                                                                 st_sp_GYRODEV_INT_ANYMOT_RD_TBL, &u2_s_gyrodev_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                u1_t_gsens_int_anymot_en_msb_data = st_sp_GYRODEV_INT_ANYMOT_RD_TBL[1].u1p_pdu[2];  /* INT_ANYMOT_EN bit[15:8] */
                u1_t_gsens_axis_read = u1_t_gsens_int_anymot_en_msb_data & (U1)GYRODEV_REG_MASK_BIT_5;
                if(u1_t_gsens_axis_read == (U1)GYRODEV_REG_MASK_BIT_5){                             /* INT_ANYMOT_EN bit[13] = 0b1 */
                    st_gyrodev_notifcond_readreq.u1_gyro_int_x = (U1)GYRODEV_GSENS_INT_AXIS_ACT;
                }
                u1_t_gsens_axis_read = u1_t_gsens_int_anymot_en_msb_data & (U1)GYRODEV_REG_MASK_BIT_6;
                if(u1_t_gsens_axis_read == (U1)GYRODEV_REG_MASK_BIT_6){                             /* INT_ANYMOT_EN bit[14] = 0b1 */
                    st_gyrodev_notifcond_readreq.u1_gyro_int_y = (U1)GYRODEV_GSENS_INT_AXIS_ACT;
                }
                u1_t_gsens_axis_read = u1_t_gsens_int_anymot_en_msb_data & (U1)GYRODEV_REG_MASK_BIT_7;
                if(u1_t_gsens_axis_read == (U1)GYRODEV_REG_MASK_BIT_7){                             /* INT_ANYMOT_EN bit[15] = 0b1 */
                    st_gyrodev_notifcond_readreq.u1_gyro_int_z = (U1)GYRODEV_GSENS_INT_AXIS_ACT;
                }

                /* Next Process */
                u1_s_gyrodev_notifcondset_sts = (U1)GYRODEV_NOTIFCONDSET_STEP13;
            }
            break;
        case GYRODEV_NOTIFCONDSET_STEP13:                           /* STEP13 */
        /* --------------- uc_active Reading --------------- */
            /* Read Register G-Sensor */
            u1_t_reg_req_sts = u1_GYRODEV_GSENS_I2C_CTRL_REGREAD(&u2_s_gyrodev_regstep, &u4_s_gyrodev_i2c_ack_wait_time,
                                                                 st_sp_GYRODEV_INT2_IO_CONF_RD_TBL, &u2_s_gyrodev_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                u1_t_gsens_int2_io_conf_data = st_sp_GYRODEV_INT2_IO_CONF_RD_TBL[1].u1p_pdu[1];     /* INT2_IO_CONF bit[7:0] */
                u1_t_gsens_int2_io_conf_data &= (U1)GYRODEV_REG_MASK_BIT_1;
                if(u1_t_gsens_int2_io_conf_data == (U1)0U){                                         /* INT2_IO_CONF bit[1] = 0b0 */
                    st_gyrodev_notifcond_readreq.u1_gyro_int_active = (U1)GYRODEV_GSENS_INT_LVL_ACT_LOW;
                }

                /* Function Completion */
                u1_t_ret = (U1)TRUE;
                /* Reading Result OK */
                u1_t_req_result = (U1)GYRODEV_GSENS_NOTIFCOND_READ_OK;
                /* Process Reset */
                u1_s_gyrodev_notifcondset_sts = (U1)GYRODEV_NOTIFCONDSET_STEP0;
            }
            break;
        default:                                                    /* FAIL */
            /* Process Reset */
            u1_s_gyrodev_notifcondset_sts = (U1)GYRODEV_NOTIFCONDSET_STEP0;
            break;
    }

    if((u1_t_ret == (U1)TRUE)
    && (u1_t_req_result != (U1)GYRODEV_GSENS_NOTIFCOND_REQ_INI)){
        if(u1_a_type == (U1)GYRODEV_GSENS_NOTIFCONDFUNC_SETREQ){
            vd_GYRODEV_NOTIFCONDSET_RESULT(u1_t_req_result);
        }
        else if(u1_a_type == (U1)GYRODEV_GSENS_NOTIFCONDFUNC_READREQ){
            st_gyrodev_notifcond_readreq.u1_result = u1_t_req_result;
            vd_GYRODEV_NOTIFCONDREAD_RESULT(st_gyrodev_notifcond_readreq);
        }
        else{
            /* Nothing */
        }
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1    u1_s_GyroDev_GSensCtrlOutFunc(const U1 u1_a_type)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_GyroDev_GSensCtrlOutFunc(const U1 u1_a_type)
{
    U1      u1_t_ret;                                               /* Function Completion Status  */
    U1      u1_t_req_result;                                        /* SiP -> MCU Request Result */
    U1      u1_t_reg_req_sts;                                       /* Register Read/Write Request Status */
    U1      u1_t_gsens_int_anymot_th_lsb_data;                      /* G-Sensor INT_ANYMOT_TH Register LSB Data */
    U1      u1_t_gsens_int_anymot_th_msb_data;                      /* G-Sensor INT_ANYMOT_TH Register MSB Data */
    U1      u1_t_gsens_int2_io_conf_data;                           /* G-Sensor INT2_IO_CONF Register Data */

    u1_t_ret = (U1)FALSE;
    u1_t_req_result = (U1)GYRODEV_GSENS_OUTCTRL_REQ_INI;

    switch (u1_s_gyrodev_ctrloutset_sts){
        case GYRODEV_CTRLOUTSET_STEP0:                              /* STEP0 */
            if(u1_a_type == (U1)GYRODEV_GSENS_CTRLOUTFUNC_SETREQ){                      /* SiP -> MCU Request Setting */
                if(u1_s_gyrodev_oscmd_outctl_rcv_flag == (U1)TRUE){
                    /* Flag Clear */
                    u1_s_gyrodev_oscmd_outctl_rcv_flag = (U1)FALSE;
                    /* Backup Flag Set */
                    u1_s_gyrodev_oscmd_outctl_bak_flag = (U1)TRUE;
                    /* Input Parameter Retention */
                    st_gyrodev_ctrlout_setbak = st_gyrodev_ctrlout_setreq;
                    if(st_gyrodev_ctrlout_setreq.u1_type == (U1)GYRODEV_GSENS_INT_EN_ON){           /* uc_type = LSDRV_GSNS_INT_CTRL_OUTPUT_ON */
                        /* Next Process */
                        u1_s_gyrodev_ctrloutset_sts = (U1)GYRODEV_CTRLOUTSET_STEP1;
                    }
                    else if(st_gyrodev_ctrlout_setreq.u1_type == (U1)GYRODEV_GSENS_INT_EN_OFF){     /* uc_type = LSDRV_GSNS_INT_CTRL_OUTPUT_OFF */
                        /* Next Process */
                        u1_s_gyrodev_ctrloutset_sts = (U1)GYRODEV_CTRLOUTSET_STEP9;
                    }
                    else if(st_gyrodev_ctrlout_setreq.u1_type == (U1)GYRODEV_GSENS_INT_EN_RST){     /* uc_type = LSDRV_GSNS_INT_CTRL_OUTPUT_RESET */
                        /* Next Process */
                        u1_s_gyrodev_ctrloutset_sts = (U1)GYRODEV_CTRLOUTSET_STEP15;
                    }
                    else{                                                                           /* Fail */
                        /* Setting Result NG */
                        u1_t_req_result = (U1)GYRODEV_GSENS_OUTCTRL_SET_NG;
                        /* Function Completion */
                        u1_t_ret = (U1)TRUE;
                    }
                }
                else{
                    /* Function Completion */
                    u1_t_ret = (U1)TRUE;
                }
            }
            else if(u1_a_type == (U1)GYRODEV_GSENS_CTRLOUTFUNC_BACKUP){                 /* Power ON -> OFF Event Setting */
                if(u1_s_gyrodev_oscmd_outctl_bak_flag == (U1)TRUE){
                    if(st_gyrodev_ctrlout_setbak.u1_type_standby == (U1)GYRODEV_GSENS_INT_STBY_ON){
                        /* Next Process */
                        u1_s_gyrodev_ctrloutset_sts = (U1)GYRODEV_CTRLOUTSET_STEP1;
                    }
                    else if(st_gyrodev_ctrlout_setbak.u1_type_standby == (U1)GYRODEV_GSENS_INT_STBY_OFF){
                        /* Next Process */
                        u1_s_gyrodev_ctrloutset_sts = (U1)GYRODEV_CTRLOUTSET_STEP9;
                    }
                    else{
                        /* Function Completion */
                        u1_t_ret = (U1)TRUE;
                        /* Setting Result NG */
                        u1_t_req_result = (U1)GYRODEV_GSENS_OUTCTRL_SET_NG;
                    }
                }
                else{
                    /* Next Process */
                    u1_s_gyrodev_ctrloutset_sts = (U1)GYRODEV_CTRLOUTSET_STEP15;
                }
            }
            else{                                                                       /* Fail */
                /* Nothing */
            }
            break;
        case GYRODEV_CTRLOUTSET_STEP1:                              /* STEP1 */
        /* --------------- uc_type = LSDRV_GSNS_INT_CTRL_OUTPUT_ON --------------- */
            /* Read Register */
            u1_t_reg_req_sts = u1_GYRODEV_GSENS_I2C_CTRL_REGREAD(&u2_s_gyrodev_regstep, &u4_s_gyrodev_i2c_ack_wait_time,
                                                                 st_sp_GYRODEV_INTAPI_OUTPUTRST_RD_TBL, &u2_s_gyrodev_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Process Reset */
                u1_s_gyrodev_ctrloutset_sts = (U1)GYRODEV_CTRLOUTSET_STEP2;
            }
            break;
        case GYRODEV_CTRLOUTSET_STEP2:                              /* STEP2 */
            /* Set Register G-Sensor */
            u1_t_reg_req_sts = u1_GYRODEV_GSENS_I2C_CTRL_REGSET(&u2_s_gyrodev_regstep, (U2)GYRODEV_INT_ANYMOT_TH_SET1_WRINUM,
                                                                GYRODEV_INT_ANYMOT_TH_SET1, &u4_s_gyrodev_i2c_ack_wait_time,
                                                                st_sp_GYRODEV_INT_ANYMOT_TH_SET1_TBL, &u2_s_gyrodev_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gyrodev_ctrloutset_sts = (U1)GYRODEV_CTRLOUTSET_STEP3;
            }
            break;
        case GYRODEV_CTRLOUTSET_STEP3:                              /* STEP3 */
            /* Read Register G-Sensor */
            u1_t_reg_req_sts = u1_GYRODEV_GSENS_I2C_CTRL_REGREAD(&u2_s_gyrodev_regstep, &u4_s_gyrodev_i2c_ack_wait_time,
                                                                 st_sp_GYRODEV_INT_ANYMOT_RD_TBL, &u2_s_gyrodev_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                u1_t_gsens_int_anymot_th_lsb_data = st_sp_GYRODEV_INT_ANYMOT_RD_TBL[1].u1p_pdu[1];  /* INT_ANYMOT_TH bit[7:0] */
                u1_t_gsens_int_anymot_th_msb_data = st_sp_GYRODEV_INT_ANYMOT_RD_TBL[1].u1p_pdu[2];  /* INT_ANYMOT_TH bit[15:8] */
                u1_t_gsens_int_anymot_th_msb_data &= ~(U1)GYRODEV_REG_MASK_BIT_3;                   /* INT_ANYMOT_TH bit[11] = 0b0 */
                st_sp_GYRODEV_INT_ANYMOT_TH_SET2_TBL[2].u1p_pdu[2] = u1_t_gsens_int_anymot_th_lsb_data;     /* Register Write Data(LSB) Set */
                st_sp_GYRODEV_INT_ANYMOT_TH_SET2_TBL[2].u1p_pdu[3] = u1_t_gsens_int_anymot_th_msb_data;     /* Register Write Data(MSB) Set */

                /* Next Process */
                u1_s_gyrodev_ctrloutset_sts = (U1)GYRODEV_CTRLOUTSET_STEP4;
            }
            break;
        case GYRODEV_CTRLOUTSET_STEP4:                              /* STEP4 */
            /* Set Register G-Sensor */
            u1_t_reg_req_sts = u1_GYRODEV_GSENS_I2C_CTRL_REGSET(&u2_s_gyrodev_regstep, (U2)GYRODEV_INT_ANYMOT_TH_SET2_WRINUM,
                                                                GYRODEV_INT_ANYMOT_TH_SET2, &u4_s_gyrodev_i2c_ack_wait_time,
                                                                st_sp_GYRODEV_INT_ANYMOT_TH_SET2_TBL, &u2_s_gyrodev_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                st_sp_GYRODEV_INT_ANYMOT_TH_SET2_TBL[2].u1p_pdu[3] |= (U1)GYRODEV_REG_MASK_BIT_3;   /* INT_ANYMOT_TH bit[11] = 0b1 */

                /* Next Process */
                u1_s_gyrodev_ctrloutset_sts = (U1)GYRODEV_CTRLOUTSET_STEP5;
            }
            break;
        case GYRODEV_CTRLOUTSET_STEP5:                              /* STEP5 */
            /* Set Register G-Sensor */
            u1_t_reg_req_sts = u1_GYRODEV_GSENS_I2C_CTRL_REGSET(&u2_s_gyrodev_regstep, (U2)GYRODEV_INT_ANYMOT_TH_SET2_WRINUM,
                                                                GYRODEV_INT_ANYMOT_TH_SET2, &u4_s_gyrodev_i2c_ack_wait_time,
                                                                st_sp_GYRODEV_INT_ANYMOT_TH_SET2_TBL, &u2_s_gyrodev_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gyrodev_ctrloutset_sts = (U1)GYRODEV_CTRLOUTSET_STEP6;
            }
            break;
        case GYRODEV_CTRLOUTSET_STEP6:                              /* STEP6 */
            /* Set Register G-Sensor */
            u1_t_reg_req_sts = u1_GYRODEV_GSENS_I2C_CTRL_REGSET(&u2_s_gyrodev_regstep, (U2)GYRODEV_INTAPI_OUTPUTON_SET_WRINUM,
                                                                GYRODEV_INTAPI_OUTPUTON_SET, &u4_s_gyrodev_i2c_ack_wait_time,
                                                                st_sp_GYRODEV_INTAPI_OUTPUTON_SET_TBL, &u2_s_gyrodev_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gyrodev_ctrloutset_sts = (U1)GYRODEV_CTRLOUTSET_STEP7;
            }
            break;
        case GYRODEV_CTRLOUTSET_STEP7:                              /* STEP7 */
            /* Read Register G-Sensor */
            u1_t_reg_req_sts = u1_GYRODEV_GSENS_I2C_CTRL_REGREAD(&u2_s_gyrodev_regstep, &u4_s_gyrodev_i2c_ack_wait_time,
                                                                 st_sp_GYRODEV_INT2_IO_CONF_RD_TBL, &u2_s_gyrodev_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                u1_t_gsens_int2_io_conf_data = st_sp_GYRODEV_INT2_IO_CONF_RD_TBL[1].u1p_pdu[1];     /* INT2_IO_CONF bit[7:0] */
                u1_t_gsens_int2_io_conf_data |= (U1)GYRODEV_REG_MASK_BIT_3;                         /* INT2_IO_CONF bit[3] = 0b1 */
                st_sp_GYRODEV_INT2_IO_CONF_SET_TBL[0].u1p_pdu[2] = u1_t_gsens_int2_io_conf_data;    /* Register Write Data Set */
                /* Next Process */
                u1_s_gyrodev_ctrloutset_sts = (U1)GYRODEV_CTRLOUTSET_STEP8;
            }
            break;
        case GYRODEV_CTRLOUTSET_STEP8:                              /* STEP8 */
            /* Set Register G-Sensor */
            u1_t_reg_req_sts = u1_GYRODEV_GSENS_I2C_CTRL_REGSET(&u2_s_gyrodev_regstep, (U2)GYRODEV_INT2_IO_CONF_SET_WRINUM,
                                                                GYRODEV_INT2_IO_CONF_SET, &u4_s_gyrodev_i2c_ack_wait_time,
                                                                st_sp_GYRODEV_INT2_IO_CONF_SET_TBL, &u2_s_gyrodev_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Function Completion */
                u1_t_ret = (U1)TRUE;
                /* Setting Result OK */
                u1_t_req_result = (U1)GYRODEV_GSENS_OUTCTRL_SET_OK;
                /* Process Reset */
                u1_s_gyrodev_ctrloutset_sts = (U1)GYRODEV_CTRLOUTSET_STEP0;
            }
            break;
        case GYRODEV_CTRLOUTSET_STEP9:                              /* STEP9 */
        /* --------------- uc_type = LSDRV_GSNS_INT_CTRL_OUTPUT_OFF --------------- */
            /* Read Register G-Sensor */
            u1_t_reg_req_sts = u1_GYRODEV_GSENS_I2C_CTRL_REGREAD(&u2_s_gyrodev_regstep, &u4_s_gyrodev_i2c_ack_wait_time,
                                                                 st_sp_GYRODEV_INT2_IO_CONF_RD_TBL, &u2_s_gyrodev_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                u1_t_gsens_int2_io_conf_data = st_sp_GYRODEV_INT2_IO_CONF_RD_TBL[1].u1p_pdu[1];     /* INT2_IO_CONF bit[7:0] */
                u1_t_gsens_int2_io_conf_data &= ~(U1)GYRODEV_GSENS_INT_OUT_MASK;                    /* INT2_IO_CONF bit[3] = 0b0 */
                st_sp_GYRODEV_INT2_IO_CONF_SET_TBL[0].u1p_pdu[2] = u1_t_gsens_int2_io_conf_data;    /* Register Write Data Set */
                /* Next Process */
                u1_s_gyrodev_ctrloutset_sts = (U1)GYRODEV_CTRLOUTSET_STEP10;
            }
            break;
        case GYRODEV_CTRLOUTSET_STEP10:                             /* STEP10 */
            /* Set Register G-Sensor */
            u1_t_reg_req_sts = u1_GYRODEV_GSENS_I2C_CTRL_REGSET(&u2_s_gyrodev_regstep, (U2)GYRODEV_INT2_IO_CONF_SET_WRINUM,
                                                                GYRODEV_INT2_IO_CONF_SET, &u4_s_gyrodev_i2c_ack_wait_time,
                                                                st_sp_GYRODEV_INT2_IO_CONF_SET_TBL, &u2_s_gyrodev_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gyrodev_ctrloutset_sts = (U1)GYRODEV_CTRLOUTSET_STEP11;
            }
            break;
        case GYRODEV_CTRLOUTSET_STEP11:                             /* STEP11 */
            /* Set Register G-Sensor */
            u1_t_reg_req_sts = u1_GYRODEV_GSENS_I2C_CTRL_REGSET(&u2_s_gyrodev_regstep, (U2)GYRODEV_INT_ANYMOT_TH_SET1_WRINUM,
                                                                GYRODEV_INT_ANYMOT_TH_SET1, &u4_s_gyrodev_i2c_ack_wait_time,
                                                                st_sp_GYRODEV_INT_ANYMOT_TH_SET1_TBL, &u2_s_gyrodev_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gyrodev_ctrloutset_sts = (U1)GYRODEV_CTRLOUTSET_STEP12;
            }
            break;
        case GYRODEV_CTRLOUTSET_STEP12:                             /* STEP12 */
            /* Read Register G-Sensor */
            u1_t_reg_req_sts = u1_GYRODEV_GSENS_I2C_CTRL_REGREAD(&u2_s_gyrodev_regstep, &u4_s_gyrodev_i2c_ack_wait_time,
                                                                 st_sp_GYRODEV_INT_ANYMOT_RD_TBL, &u2_s_gyrodev_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                u1_t_gsens_int_anymot_th_lsb_data = st_sp_GYRODEV_INT_ANYMOT_RD_TBL[1].u1p_pdu[1];  /* INT_ANYMOT_TH bit[7:0] */
                u1_t_gsens_int_anymot_th_msb_data = st_sp_GYRODEV_INT_ANYMOT_RD_TBL[1].u1p_pdu[2];  /* INT_ANYMOT_TH bit[15:8] */
                u1_t_gsens_int_anymot_th_msb_data &= ~(U1)GYRODEV_GSENS_INT_EN_MSB_MASK;            /* INT_ANYMOT_TH bit[11] = 0b0 */
                st_sp_GYRODEV_INT_ANYMOT_TH_SET2_TBL[2].u1p_pdu[2] = u1_t_gsens_int_anymot_th_lsb_data;     /* Register Write Data(LSB) Set */
                st_sp_GYRODEV_INT_ANYMOT_TH_SET2_TBL[2].u1p_pdu[3] = u1_t_gsens_int_anymot_th_msb_data;     /* Register Write Data(MSB) Set */

                /* Next Process */
                u1_s_gyrodev_ctrloutset_sts = (U1)GYRODEV_CTRLOUTSET_STEP13;
            }
            break;
        case GYRODEV_CTRLOUTSET_STEP13:                             /* STEP13 */
            /* Set Register G-Sensor */
            u1_t_reg_req_sts = u1_GYRODEV_GSENS_I2C_CTRL_REGSET(&u2_s_gyrodev_regstep, (U2)GYRODEV_INT_ANYMOT_TH_SET2_WRINUM,
                                                                GYRODEV_INT_ANYMOT_TH_SET2, &u4_s_gyrodev_i2c_ack_wait_time,
                                                                st_sp_GYRODEV_INT_ANYMOT_TH_SET2_TBL, &u2_s_gyrodev_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gyrodev_ctrloutset_sts = (U1)GYRODEV_CTRLOUTSET_STEP14;
            }
            break;
        case GYRODEV_CTRLOUTSET_STEP14:                             /* STEP14 */
            /* Set Register G-Sensor */
            u1_t_reg_req_sts = u1_GYRODEV_GSENS_I2C_CTRL_REGSET(&u2_s_gyrodev_regstep, (U2)GYRODEV_INTAPI_OUTPUTOFF_SET_WRINUM,
                                                                GYRODEV_INTAPI_OUTPUTOFF_SET, &u4_s_gyrodev_i2c_ack_wait_time,
                                                                st_sp_GYRODEV_INTAPI_OUTPUTOFF_SET_TBL, &u2_s_gyrodev_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Function Completion */
                u1_t_ret = (U1)TRUE;
                /* Setting Result OK */
                u1_t_req_result = (U1)GYRODEV_GSENS_OUTCTRL_SET_OK;
                /* Process Reset */
                u1_s_gyrodev_ctrloutset_sts = (U1)GYRODEV_CTRLOUTSET_STEP0;
            }
            break;
        case GYRODEV_CTRLOUTSET_STEP15:                             /* STEP15 */
        /* --------------- uc_type = LSDRV_GSNS_INT_CTRL_OUTPUT_RESET --------------- */
            /* Read Register */
            u1_t_reg_req_sts = u1_GYRODEV_GSENS_I2C_CTRL_REGREAD(&u2_s_gyrodev_regstep, &u4_s_gyrodev_i2c_ack_wait_time,
                                                                 st_sp_GYRODEV_INTAPI_OUTPUTRST_RD_TBL, &u2_s_gyrodev_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Function Completion */
                u1_t_ret = (U1)TRUE;
                /* Setting Result OK */
                u1_t_req_result = (U1)GYRODEV_GSENS_OUTCTRL_SET_OK;
                /* Process Reset */
                u1_s_gyrodev_ctrloutset_sts = (U1)GYRODEV_CTRLOUTSET_STEP0;
            }
            break;
        default:                                                    /* FAIL */
            /* Process Reset */
            u1_s_gyrodev_ctrloutset_sts = (U1)GYRODEV_CTRLOUTSET_STEP0;
            break;
    }

    if((u1_t_ret == (U1)TRUE)
    && (u1_t_req_result != (U1)GYRODEV_GSENS_OUTCTRL_REQ_INI)){
        if(u1_a_type == (U1)GYRODEV_GSENS_CTRLOUTFUNC_SETREQ){
            vd_GYRODEV_CTRLOUTSETSET_RESULT(u1_t_req_result);
        }
    }


    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  void    vd_g_GyroDev_NotifCond_SetReq(ST_GYRODEV_NOTIFCOND_SETDATA st_a_oscmd_data)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GyroDev_NotifCond_SetReq(ST_GYRODEV_NOTIFCOND_SETDATA st_a_oscmd_data)
{
    u1_s_gyrodev_oscmd_notifcond_rcv_flag = (U1)TRUE;
    st_gyrodev_notifcond_setreq = st_a_oscmd_data;
}

/*===================================================================================================================================*/
/*  void    vd_g_GyroDev_NotifCond_ReadReq(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GyroDev_NotifCond_ReadReq(void)
{
    u1_s_gyrodev_oscmd_notifcond_read_flag = (U1)TRUE;
}

/*===================================================================================================================================*/
/*  void    vd_g_GyroDev_OutCtl_SetReq(ST_GYRODEV_CTRLOUT_SETDATA st_a_oscmd_data)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GyroDev_OutCtl_SetReq(ST_GYRODEV_CTRLOUT_SETDATA st_a_oscmd_data)
{
    u1_s_gyrodev_oscmd_outctl_rcv_flag = (U1)TRUE;
    st_gyrodev_ctrlout_setreq = st_a_oscmd_data;
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
