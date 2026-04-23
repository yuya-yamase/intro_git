/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "GyroDevCtl.h"

/* App */
#include "x_spi_ivi_sub1_power.h"
#include "x_spi_ivi_sub1_version.h"
/* LIB */
#include "memfill_u1.h"
#include "memcpy_u1.h"

#include "rim_ctl.h"
#include "rim_ctl_cfg.h"


/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Gyro processing results */
#define GYRO_RET_NG                             (0U)
#define GYRO_RET_OK                             (1U)
#define GYRO_RET_INPROC                         (2U)    /* Processing in progress */
#define GYRO_RET_IICERR                         (3U)    /* I2C error */

/* Macros for calculations */
#define GYRO_SFT_BYTE1                          ( 8U)   /* 1-byte shift */
#define GYRO_SFT_BYTE2                          (16U)   /* 2-byte shift */
#define GYRO_SFT_BYTE3                          (24U)   /* 3-byte shift */
#define GYRO_POS_0                              ( 0U)   /* Array index: 0 */
#define GYRO_POS_1                              ( 1U)   /* Array index: 1 */
#define GYRO_POS_2                              ( 2U)   /* Array index: 2 */
#define GYRO_POS_3                              ( 3U)   /* Array index: 3 */

/* Gyro mode */
#define GYRO_DEV_MODE_NORMAL                    (0U)
#define GYRO_DEV_MODE_SUSPEND                   (1U)

/* Gyro sequence control ID */
#define GYRO_SEQ_MAX                            (4U)    /* Max number of sequences */
#define GYRO_SEQ_IDLE                           (0U)    /* 0: Idle sequence */
#define GYRO_SEQ_STAUP1                         (1U)    /* 1: Startup (1) sequence */
#define GYRO_SEQ_STAUP2                         (2U)    /* 2: Startup (2) sequence */
#define GYRO_SEQ_SHUTDOWN1                      (3U)    /* 3: Shutdown (1) sequence */

/* Sub-sequence status notification */
#define GYRO_RET_NG                             (0U)    /* NG */
#define GYRO_RET_OK                             (1U)    /* OK */
#define GYRO_RET_INPROC                         (2U)    /* In progress */
#define GYRO_RET_IICERR                         (3U)    /* I2C error (preliminary design) */

/* G-sensor value conversion macros */
#define GYRO_CLC_ACC_BDR                        (0x8000U)   /* Boundary between positive and negative */
#define GYRO_CLC_ACC_U2TOS2                     (32767U)    /* Operand used for U2-to-S2 conversion */
#define GYRO_CLC_ACC_COMPLEMENT                 (1U)        /* Macro for complement calculation */
#define GYRO_DAT_ACC_XYZ_MAX                    (0x7FFFU)   /* G-sensor XYZ axis max value (HEX: 7FFF) */
#define GYRO_DAT_ACC_XYZ_MIN                    (0x8000U)   /* G-sensor XYZ axis min value (HEX: 8000) */
#define GYRO_DAT_ACC_X_DIF                      (0x0800U)   /* G-sensor X-axis difference value */
#define GYRO_DAT_ACC_Y_DIF                      (0x0800U)   /* G-sensor Y-axis difference value */
#define GYRO_DAT_ACC_Z_DIF                      (0x0400U)   /* G-sensor Z-axis difference value */

/* Self-test error retry limit */
#define GYRO_CNT_SELFTEST_RTRY_MAX              (3U)        /* Specified value: 3 times (i, j) */

/* Config file setting: data buffer size */
#define GYRO_SIZ_VERSION                        (14U)       /* 14 bytes (GCONFIG_V**_**) */
#define GYRO_SIZ_BUF                            ( 4U)       /* 4 bytes */

/* Config file setting: signature read calculation */
#define GYRO_CLC_ADR1                           (1U)
#define GYRO_CLC_ADR2                           (2U)
#define GYRO_CLC_ADR3                           (3U)
#define GYRO_CLC_ADR4                           (4U)
#define GYRO_CLC_ADR5                           (5U)
#define GYRO_CLC_ADR6                           (6U)
#define GYRO_CLC_ADR7                           (7U)

/* Config file setting: comparison character definitions for "G_CONFIG" */
#define GYRO_FNTOKEN_G                          (0x47)
#define GYRO_FNTOKEN__                          (0x2D)
#define GYRO_FNTOKEN_C                          (0x43)
#define GYRO_FNTOKEN_O                          (0x4F)
#define GYRO_FNTOKEN_N                          (0x4E)
#define GYRO_FNTOKEN_F                          (0x46)
#define GYRO_FNTOKEN_I                          (0x49)
/*  #define GYRO_FNTOKEN_G                       (0x47) */

/* Config file setting: file write information */
#define GYRO_CFG_NON                            (0x00)      /* No data */
#define GYRO_CFG_EXIST                          (0x01)      /* Data exists */
#define GYRO_CFG_MAXSIZ                         (0x78D0U)   /* Max config file size:MAX: 0x78D0 (30928 bytes)= 32000 bytes (max for mot) - 48 bytes (config header) - 1024 bytes (reserved area) */
#define GYRO_CFG_WRISIZ                         (32U)       /* Write size per config file operation */
#define GYRO_CFG_MAXRTRY                        (3U)        /* Max number of write retries */

/* Config file setting: data layout addresses */
#define GYRO_ADR_VERSION                        (0x00000010)
#define GYRO_ADR_OFFSET                         (0x00000020)
#define GYRO_ADR_DATSIZ                         (0x00000024)

/* Startup (2): expected value when reading gyro mode */
#define GYRO_DAT_GYROMODE_SUSPEND               (0x80U)     /* Suspend mode */

/* Shutdown (1): Mode Change (Gyro) Read retry limit */
#define GYRO_CNT_SHUTDN1_RTRY_MAX               (3U)        /* Specified value: 3 times (k(5_1)) */

/* Input parameter setting (2): number of G-sensor reads (k(5_2)) */
#define GYRO_CNT_PARASET_ACC_READ               (100U)      /* Counter to determine the monitoring period for judging G-value stability
                                                            (monitor at 100 ms intervals during t20 × K(5_2)) */

/* Input parameter setting (2): number of attempts for difference verification (k(5_3)) */
#define GYRO_CNT_PARASET_ACC_VERI               (600U)      /* Counter to determine timeout
                                                            (timeout after t20 × K(5_2) × K(5_3), i.e., 60 seconds) */

/* Input parameter setting (2): check for fewer than 50 valid axis information samples */
#define GYRO_CNT_PARASET_ACC_READERR            (50U)

/* Input parameter setting (2): threshold (variation range) for G-value stability */
#define GYRO_CNT_PARASET_ACC_FIX_STAB           (1229U)     /* Consider stable if less than 0.075g */


/* Register operation steps */
#define GYRO_WRISTEP_SETUP_GYR                  (1U)    /* Setup Sensor (Gyro): number of register writes */
#define GYRO_WRISTEP_TEST_COMSET_GYR            (1U)    /* Self-test (Gyro) command: number of register writes */
#define GYRO_WRISTEP_WDG_GYR                    (1U)    /* Set Watchdog Timer (Gyro): number of register writes */
#define GYRO_WRISTEP_MODE_ON_GYR                (1U)    /* Mode Change (Gyro) ON: suspend mode => normal mode, number of register writes */
#define GYRO_WRISTEP_MODE_OFF_GYR               (1U)    /* Mode Change (Gyro) OFF: normal mode => suspend mode, number of register writes */
#define GYRO_WRISTEP_SETUP_SEN1_ACC             (1U)    /* Setup Sensor (Accelerometer 1): number of register writes */
#define GYRO_WRISTEP_SETUP_SEN1_BW_ACC          (1U)    /* Setup Sensor (Accelerometer 1): bandwidth setting, number of register writes */
#define GYRO_WRISTEP_SETUP_SEN2_ACC             (1U)    /* Setup Sensor (Accelerometer 2): number of register writes */
#define GYRO_WRISTEP_WDG_ACC                    (1U)    /* Set Watchdog Timer (Accelerometer): number of register writes */
#define GYRO_WRISTEP_MODE_ON_ACC                (1U)    /* Mode Change (Accelerometer) ON: suspend mode => normal mode, number of register writes */
#define GYRO_WRISTEP_MODE_OFF_ACC               (1U)    /* Mode Change (Accelerometer) OFF: normal mode => suspend mode, number of register writes */
#define GYRO_WRISTEP_SELFTEST_ACC_PLS           (1U)    /* Accelerometer self-test (positive): number of register writes */
#define GYRO_WRISTEP_SELFTEST_ACC_MNS           (1U)    /* Accelerometer self-test (negative): number of register writes */
#define GYRO_WRISTEP_SELFTEST_ACC_DISABLE       (1U)    /* Accelerometer self-test (disable) setting table: number of register writes */
#define GYRO_WRISTEP_PWRCONF_ON                 (1U)    /* Accelerometer low-power mode (suspend mode => normal mode): number of register writes */
#define GYRO_WRISTEP_PWRCONF_OFF                (1U)    /* Preliminary design: accelerometer low-power mode (normal mode => suspend mode): number of register writes */
#define GYRO_WRISTEP_INTCONF_ON                 (1U)    /* Enable config-file initialization (write enable): number of register writes */
#define GYRO_WRISTEP_INTCONF_OFF                (1U)    /* Preliminary design: enable config-file initialization (enable sensor function after config file write): number of register writes */
#define GYRO_WRISTEP_SOFTRESET                  (1U)    /* Sensor soft reset by user: number of register writes */
#define GYRO_WRISTEP_INT_ANYMOT_TH              (3U)    /* Accelerometer impact detection setting INT_ANYMOT_TH: number of register writes */
#define GYRO_WRISTEP_INT_ANYMOT_EN              (3U)    /* Accelerometer impact detection setting INT_ANYMOT_EN: number of register writes */
#define GYRO_WRISTEP_INT_OTH                    (1U)    /* Accelerometer impact detection setting (others): number of register writes */
#define GYRO_WRISTEP_INPRM_SEN1_BW_ACC          (1U)    /* For input parameter setting (2): Setup Sensor (Accelerometer 1) bandwidth setting, number of register writes */
#define GYRO_WRISTEP_CFG_OFST1                  (1U)    /* Config file transfer: AddressOffset1, number of register writes */
#define GYRO_WRISTEP_CFG_OFST2                  (1U)    /* Config file transfer: AddressOffset2, number of register writes */
#define GYRO_WRISTEP_CFG_DATA                   (1U)    /* Config file transfer: Data, number of register writes */

/* Macros for register operations */
#define GYRO_SHIFT_8                            (8U)    /* Bit shift: 8 bytes */
#define GYRO_WRIPOS_0                           (0U)    /* Write buffer position: element 0 */
#define GYRO_WRIPOS_1                           (1U)    /* Write buffer position: element 1 */
#define GYRO_WRIPOS_2                           (2U)    /* Write buffer position: element 2 */
#define GYRO_READPOS_1                          (1U)    /* Read buffer position: element 1 */
#define GYRO_READPOS_2                          (2U)    /* Read buffer position: element 2 */
#define GYRO_READPOS_3                          (3U)    /* Read buffer position: element 3 */
#define GYRO_READPOS_4                          (4U)    /* Read buffer position: element 4 */
#define GYRO_READPOS_5                          (5U)    /* Read buffer position: element 5 */
#define GYRO_READPOS_6                          (6U)    /* Read buffer position: element 6 */
#define GYRO_READDAT_BIT0                       (0x01U) /* Read data mask: Bit0 */
#define GYRO_READDAT_BIT1                       (0x02U) /* Read data mask: Bit1 */
#define GYRO_READDAT_BIT2                       (0x04U) /* Read data mask: Bit2 */
#define GYRO_READDAT_BIT3                       (0x08U) /* Read data mask: Bit3 */
#define GYRO_READDAT_BIT4                       (0x10U) /* Read data mask: Bit4 */
#define GYRO_READDAT_BIT5                       (0x20U) /* Read data mask: Bit5 */
#define GYRO_READDAT_BIT6                       (0x40U) /* Read data mask: Bit6 */
#define GYRO_READDAT_BIT7                       (0x80U) /* Read data mask: Bit7 */

#define GYRO_ST_FAIL_TGT_GYRO                   (1U)    /* Diagnosis record (DTC) storage cause: Gyro */
#define GYRO_ST_FAIL_TGT_ACC                    (2U)    /* Diagnosis record (DTC) storage cause: Accelerometer */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GYRODEV_TASK_TIME                   (1U)

#define GYRODEV_SEQ_IDLE                    (0U)
#define GYRODEV_SEQ_CYC                     (1U)
#define GYRODEV_SEQ_BKUP                    (2U)

#define GYRODEV_CYCCHK_STEP0                (0U)
#define GYRODEV_CYCCHK_STEP1                (1U)
#define GYRODEV_CYCCHK_STEP2                (2U)
#define GYRODEV_CYCCHK_STEP3                (3U)
#define GYRODEV_CYCCHK_STEP4                (4U)
#define GYRODEV_CYCCHK_STEP5                (5U)

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
#define GYRODEV_GSENSDATA_RD_WRINUM         (4U)

/* DIO */
#define GYRO_DIO_LOW                            (STD_LOW)
#define GYRO_DIO_HIGH                           (STD_HIGH)
/* DIO READ */
#define dl_GYRO_DIO_READ_SENSOR_ON()            (Dio_ReadChannel((Dio_ChannelType)DIO_ID_PORT8_CH7))
#define dl_GYRO_DIO_READ_BUDET()                (Dio_ReadChannel((Dio_ChannelType)DIO_ID_PORT0_CH4))
#define dl_GYRO_DIO_READ_V33PERI()              (Dio_ReadChannel((Dio_ChannelType)DIO_ID_PORT10_CH2))
/* DIO WRITE */
#define dl_GYRO_DIO_WRITE_SENSOR_ON_L()         (Dio_WriteChannel((Dio_ChannelType)DIO_ID_PORT8_CH7, (Dio_LevelType)GYRO_DIO_LOW))
#define dl_GYRO_DIO_WRITE_SENSOR_ON_H()         (Dio_WriteChannel((Dio_ChannelType)DIO_ID_PORT8_CH7, (Dio_LevelType)GYRO_DIO_HIGH))


/* Sequence management No. */
/* Sequence execution No. Startup (1) */
#define GYRO_SEQ_STAUP1_1                       (GYRO_SEQ_IDLE_STA      )   /* Wait t1 (wait for sensor power OFF when +B momentarily drops) */
#define GYRO_SEQ_STAUP1_2                       (GYRO_SEQ_IDLE_STA +  1U)   /* SENSOR-ON pin Lo->Hi (GPIO handling) */
#define GYRO_SEQ_STAUP1_3                       (GYRO_SEQ_IDLE_STA +  2U)   /* Wait t3 (time from SENSOR-ON High until I2C access is possible) */
#define GYRO_SEQ_STAUP1_4                       (GYRO_SEQ_IDLE_STA +  3U)   /* Set Watchdog Timer (Gyro) */
#define GYRO_SEQ_STAUP1_5                       (GYRO_SEQ_IDLE_STA +  4U)   /* Set Watchdog Timer (Accelerometer) */
#define GYRO_SEQ_STAUP1_6                       (GYRO_SEQ_IDLE_STA +  5U)   /* Mode Change (Accelerometer) ON: suspend mode => normal mode */
#define GYRO_SEQ_STAUP1_7                       (GYRO_SEQ_IDLE_STA +  6U)   /* Wait t11 (device spec: >50 ms; wait after accelerometer mode change) */
#define GYRO_SEQ_STAUP1_8                       (GYRO_SEQ_IDLE_STA +  7U)   /* Setup Sensor (Gyro) */
#define GYRO_SEQ_STAUP1_9                       (GYRO_SEQ_IDLE_STA +  8U)   /* Self-Test (Gyro) */
#define GYRO_SEQ_STAUP1_10                      (GYRO_SEQ_IDLE_STA +  9U)   /* Setup Sensor (Gyro) */
#define GYRO_SEQ_STAUP1_11                      (GYRO_SEQ_IDLE_STA + 10U)   /* Setup Sensor (Accelerometer 2) */
#define GYRO_SEQ_STAUP1_12                      (GYRO_SEQ_IDLE_STA + 11U)   /* Self-Test (Accelerometer) */
#define GYRO_SEQ_STAUP1_13                      (GYRO_SEQ_IDLE_STA + 12U)   /* To [upload config] */
#define GYRO_SEQ_STAUP1_14                      (GYRO_SEQ_IDLE_STA + 13U)   /* To [Set Interrupt] */
#define GYRO_SEQ_STAUP1_15                      (GYRO_SEQ_IDLE_STA + 14U)   /* Set Watchdog Timer (Accelerometer) */
#define GYRO_SEQ_STAUP1_16                      (GYRO_SEQ_IDLE_STA + 15U)   /* Setup Sensor (Accelerometer 1) */
#define GYRO_SEQ_STAUP1_17                      (GYRO_SEQ_IDLE_STA + 16U)   /* Mode Change (Gyro) OFF: normal mode => suspend mode */
#define GYRO_SEQ_STAUP1_18                      (GYRO_SEQ_IDLE_STA + 17U)   /* Wait t21 (wait time after gyro mode change) */

/* Sequence execution No. Self-Test (Gyro) */
#define GYRO_SEQ_SELFTEST_GYRO_1                (GYRO_SEQ_IDLE_STA      )   /* [write] 0x3C */
#define GYRO_SEQ_SELFTEST_GYRO_2                (GYRO_SEQ_IDLE_STA +  1U)   /* [wait] t12 */
#define GYRO_SEQ_SELFTEST_GYRO_3                (GYRO_SEQ_IDLE_STA +  2U)   /* [read] 0x3C */
#define GYRO_SEQ_SELFTEST_GYRO_4                (GYRO_SEQ_IDLE_STA +  3U)   /* Check self-test completion */

/* Sequence execution No. Self-Test (Accelerometer) */
#define GYRO_SEQ_SELFTEST_ACC_1                 (GYRO_SEQ_IDLE_STA      )   /* wait t13 */
#define GYRO_SEQ_SELFTEST_ACC_2                 (GYRO_SEQ_IDLE_STA +  1U)   /* write 0x6D (positive) */
#define GYRO_SEQ_SELFTEST_ACC_3                 (GYRO_SEQ_IDLE_STA +  2U)   /* wait t14 */
#define GYRO_SEQ_SELFTEST_ACC_4                 (GYRO_SEQ_IDLE_STA +  3U)   /* Read data (Accel +), convert data */
#define GYRO_SEQ_SELFTEST_ACC_5                 (GYRO_SEQ_IDLE_STA +  4U)   /* write 0x6D (negative) */
#define GYRO_SEQ_SELFTEST_ACC_6                 (GYRO_SEQ_IDLE_STA +  5U)   /* wait t14 */
#define GYRO_SEQ_SELFTEST_ACC_7                 (GYRO_SEQ_IDLE_STA +  6U)   /* Read data (Accel -), convert data */
#define GYRO_SEQ_SELFTEST_ACC_8                 (GYRO_SEQ_IDLE_STA +  7U)   /* write 0x6D (disable) */
#define GYRO_SEQ_SELFTEST_ACC_9                 (GYRO_SEQ_IDLE_STA +  8U)   /* wait t14 */
#define GYRO_SEQ_SELFTEST_ACC_10                (GYRO_SEQ_IDLE_STA +  9U)   /* Determine test result */

/* Sequence execution No. upload config */
#define GYRO_SEQ_UPCONF_1                       (GYRO_SEQ_IDLE_STA      )   /* Read config file; initialize INIT-check NG count */
#define GYRO_SEQ_UPCONF_2                       (GYRO_SEQ_IDLE_STA +  1U)   /* Soft reset (Accelerometer) */
#define GYRO_SEQ_UPCONF_3                       (GYRO_SEQ_IDLE_STA +  2U)   /* wait t15 */
#define GYRO_SEQ_UPCONF_4                       (GYRO_SEQ_IDLE_STA +  3U)   /* Change ACC mode to suspend (ADS: 0x7D) */
#define GYRO_SEQ_UPCONF_5                       (GYRO_SEQ_IDLE_STA +  4U)   /* wait t10 */
#define GYRO_SEQ_UPCONF_6                       (GYRO_SEQ_IDLE_STA +  5U)   /* Change ACC mode to normal (ADS: 0x7C) */
#define GYRO_SEQ_UPCONF_7                       (GYRO_SEQ_IDLE_STA +  6U)   /* wait t15 */
#define GYRO_SEQ_UPCONF_8                       (GYRO_SEQ_IDLE_STA +  7U)   /* Set INT_CTRL: write ADS 0x59, val 0x00 */
#define GYRO_SEQ_UPCONF_9                       (GYRO_SEQ_IDLE_STA +  8U)   /* wait t15 */
#define GYRO_SEQ_UPCONF_10                      (GYRO_SEQ_IDLE_STA +  9U)   /* Upload config file via I2C: write 0x5B */
#define GYRO_SEQ_UPCONF_11                      (GYRO_SEQ_IDLE_STA + 10U)   /* Upload config file via I2C: write 0x5C */
#define GYRO_SEQ_UPCONF_12                      (GYRO_SEQ_IDLE_STA + 11U)   /* Upload config file via I2C: write 0x5E */
#define GYRO_SEQ_UPCONF_13                      (GYRO_SEQ_IDLE_STA + 12U)   /* Set INT_CTRL: write ADS 0x59, val 0x01 */
#define GYRO_SEQ_UPCONF_14                      (GYRO_SEQ_IDLE_STA + 13U)   /* wait t15 */
#define GYRO_SEQ_UPCONF_15                      (GYRO_SEQ_IDLE_STA + 14U)   /* read 0x2A */
#define GYRO_SEQ_UPCONF_16                      (GYRO_SEQ_IDLE_STA + 15U)   /* Change ACC mode to normal */
#define GYRO_SEQ_UPCONF_17                      (GYRO_SEQ_IDLE_STA + 16U)   /* wait t15 */

/* Sequence execution No. Set Interrupt */
#define GYRO_SEQ_INTSET_1                       (GYRO_SEQ_IDLE_STA      )   /* INT_ANYMOT_TH */
#define GYRO_SEQ_INTSET_2                       (GYRO_SEQ_IDLE_STA +  1U)   /* INT_ANYMOT_EN */
#define GYRO_SEQ_INTSET_3                       (GYRO_SEQ_IDLE_STA +  2U)   /* INT2_IO_CONF, INT_LATCH, INT2_MAP */

/* Sequence execution No. Startup (2) */
#define GYRO_SEQ_STAUP2_1                       (GYRO_SEQ_IDLE_STA      )   /* Write 0xA8 to accelerometer register 0x40 */
#define GYRO_SEQ_STAUP2_2                       (GYRO_SEQ_IDLE_STA +  1U)   /* Mode Change (Gyro) Read */
#define GYRO_SEQ_STAUP2_3                       (GYRO_SEQ_IDLE_STA +  2U)   /* Check mode (Gyro) */
#define GYRO_SEQ_STAUP2_4                       (GYRO_SEQ_IDLE_STA +  3U)   /* Wait t10 (wait time when gyro sensor is in suspend mode) */
#define GYRO_SEQ_STAUP2_5                       (GYRO_SEQ_IDLE_STA +  4U)   /* Mode Change (Gyro) ON: suspend mode => normal mode */
#define GYRO_SEQ_STAUP2_6                       (GYRO_SEQ_IDLE_STA +  5U)   /* Wait t21 (wait time after gyro mode change) */

/* Sequence execution No. Shutdown (1) */
#define GYRO_SEQ_SHUTDN1_1                      (GYRO_SEQ_IDLE_STA      )   /* SENSOR-ON pin == Hi ? */
#define GYRO_SEQ_SHUTDN1_2                      (GYRO_SEQ_IDLE_STA +  1U)   /* Mode Change (Gyro) OFF: normal mode => suspend mode */
#define GYRO_SEQ_SHUTDN1_3                      (GYRO_SEQ_IDLE_STA +  2U)   /* Wait t21 */
#define GYRO_SEQ_SHUTDN1_4                      (GYRO_SEQ_IDLE_STA +  3U)   /* Mode Change (Gyro) Read */
#define GYRO_SEQ_SHUTDN1_5                      (GYRO_SEQ_IDLE_STA +  4U)   /* Read data == 0x80 ? */
#define GYRO_SEQ_SHUTDN1_6                      (GYRO_SEQ_IDLE_STA +  5U)   /* Wait t18 */
#define GYRO_SEQ_SHUTDN1_7                      (GYRO_SEQ_IDLE_STA +  6U)   /* Counter >= k(5-1) times? */
#define GYRO_SEQ_SHUTDN1_8                      (GYRO_SEQ_IDLE_STA +  7U)   /* Wait t10 */
#define GYRO_SEQ_SHUTDN1_9                      (GYRO_SEQ_IDLE_STA +  8U)   /* 5.2.6 Input parameter setting (2) */

/* Sequence execution No. Input parameter setting (2) */
#define GYRO_SEQ_PARASET2_1                     (GYRO_SEQ_IDLE_STA      )   /* Is the retained value for impact detection enable set to output ON? */
#define GYRO_SEQ_PARASET2_2                     (GYRO_SEQ_IDLE_STA +  1U)   /* Write 0xAC to accelerometer register 0x40 */
#define GYRO_SEQ_PARASET2_3                     (GYRO_SEQ_IDLE_STA +  2U)   /* Wait t19; clear counters k(5_2) and k(5_3) */
#define GYRO_SEQ_PARASET2_4                     (GYRO_SEQ_IDLE_STA +  3U)   /* Clear MAX and MIN values */
#define GYRO_SEQ_PARASET2_5                     (GYRO_SEQ_IDLE_STA +  4U)   /* Detect V33-PERI-ON */
#define GYRO_SEQ_PARASET2_6                     (GYRO_SEQ_IDLE_STA +  5U)   /* Read accelerometer registers 0x12 to 0x17 */
#define GYRO_SEQ_PARASET2_7                     (GYRO_SEQ_IDLE_STA +  6U)   /* Update accelerometer MAX/MIN */
#define GYRO_SEQ_PARASET2_8                     (GYRO_SEQ_IDLE_STA +  7U)   /* Wait t20; check number of accelerometer reads (k(5_2)) */
#define GYRO_SEQ_PARASET2_9                     (GYRO_SEQ_IDLE_STA +  8U)   /* Difference check |MAX-MIN|; check number of attempts (k(5_3)) */
#define GYRO_SEQ_PARASET2_10                    (GYRO_SEQ_IDLE_STA +  9U)   /* Write the settings retained by "Input parameter retention" */
/* Wait time settings */

/* T1  SENSOR-ON OFF->ON time (includes sensor power-OFF wait time when +B momentarily drops): 30 ms to 50 ms */
#define GYRO_WAIT_T1                            ( 40U   / GYRO_TASK_TIME)
/* T3  Time from SENSOR-ON High until I2C access is possible */
#define GYRO_WAIT_T3                            (210U   / GYRO_TASK_TIME)
/* T11 Wait time after accelerometer mode change */
#define GYRO_WAIT_T11                           ( 60U   / GYRO_TASK_TIME)
/* T12 Self-test (Gyro) execution time (device spec > 50 ms) */
#define GYRO_WAIT_T12                           ( 60U   / GYRO_TASK_TIME)
/* T13 Self-test (Accelerometer) wait time (device spec > 2 ms) */
#define GYRO_WAIT_T13                           (  5U   / GYRO_TASK_TIME)
/* T14 Self-test (Accelerometer) execution time (device spec > 50 ms) */
#define GYRO_WAIT_T14                           ( 60U   / GYRO_TASK_TIME)
/* T15 Wait time specified by the device specification (device spec: min 150 ms) */
#define GYRO_WAIT_T15                           (170U   / GYRO_TASK_TIME)
/* T18 Defined based on the IC function watchdog period: 2 ms / 10 ms / 20 ms */
#define GYRO_WAIT_T18                           ( 10U   / GYRO_TASK_TIME)
/* T21 Wait time after gyro mode change (device spec 200 ms) */
#define GYRO_WAIT_T21                           (210U   / GYRO_TASK_TIME)

#define GYRODEV_GSENSBKUP_STEP0             (0U)
#define GYRODEV_GSENSBKUP_STEP1             (1U)
#define GYRODEV_ACK_MAX                     (8U)
#define GYRO_I2C_PID_MASK                        (0x0FFFFFFFU)
#define GYRO_I2C_PID_INVALID                     (0xFFFFFFFFU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Gyro control management buffer */
typedef struct {
    U1  u1_mod;         /* GYRO control mode */
    U1  u1_event;       /* Event */
    U1  u1_dev_mode;    /* GYRO device mode */
} ST_GYRO_CTL_MNG;

/* Gyro sequence management buffer */
typedef struct {
    U1      u1_no;          /* Sequence mode */
    U1      u1_step;        /* Sequence step */
    U1      u1_subtype;     /* Sequence sub-step */
} ST_GYRO_SEQMNG;

/* Sequence processing table */
typedef void (*FP_GYRO_SRQ_FUNC)(void);     /* Event address */

/* Gyro state transition table */
typedef void (*FP_GYRO_EVNT_HNDL)(void);    /* GYRO state event handler */

/* Accelerometer received data buffer */
typedef struct {
    S2      s2_x;   /* Acceleration data (X-axis) */
    S2      s2_y;   /* Acceleration data (Y-axis) */
    S2      s2_z;   /* Acceleration data (Z-axis) */
} ST_GYRO_ACC_XYZ;

typedef struct {
    U1              u1_acc_x_lsb;
    U1              u1_acc_x_msb;
    U1              u1_acc_y_lsb;
    U1              u1_acc_y_msb;
    U1              u1_acc_z_lsb;
    U1              u1_acc_z_msb;
    ST_GYRO_ACC_XYZ st_acc_xyz;
} ST_GYRO_ACCTEST;

typedef struct gyro {
    ST_GYRO_ACC_XYZ st_min;         /* Acceleration axis data (MIN) */
    ST_GYRO_ACC_XYZ st_max;         /* Acceleration axis data (MAX) */
    ST_GYRO_ACCTEST st_calc;        /* Acceleration axis data (temporary for calculations) */
    U1              u1_updatecnt;   /* Number of axis data updates */
    U1              u1_errlog_sts;  /* Diagnostic record (DTC) logging flag */
} ST_GYRO_ACC;

/* Accelerometer data info structure */
typedef struct {
    U4              u4_datsiz;      /* Total size of vehicle parameter data */
    U4              u4_strtadr;     /* Start address of the data section */
} ST_GYRO_DATAINFO;

typedef struct {
    U1              u1_upload_cnt;  /* Total number of config file writes */
    U1              u1_upload_idx;  /* Counter of completed config file writes */
    U4              u4_upload_addr; /* Start address of the data section to be written for the config file */
} ST_GYRO_CFGMNG;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1 u1_s_gyrodev_state;                                   /* Gyro Device State *//*  +B-ON保持が必要 */

static U1 u1_s_gyrodev_cycchk_sts;                              /* Cycle Check Function Status *//*  +B-ON保持が必要 */
static U4 u4_s_gyrodev_cycchk_timer;                            /* Gyro Device Cycle Check Poling Timer *//*  +B-ON保持が必要 */
static U2 u2_s_gyrodev_gyro_max_err_cnt;                        /* Gyro Device GYRO Register MAX Freeze Error Counter *//*  +B-ON保持が必要 */
static U2 u2_s_gyrodev_gyro_min_err_cnt;                        /* Gyro Device GYRO Register MIN Freeze Error Counter *//*  +B-ON保持が必要 */
static U1 u1_s_gyrodev_gyro_rst_cnt;                            /* Gyro Device GYRO Read Reset Counter *//*  +B-ON保持が必要 */
static U2 u2_s_gyrodev_gsens_max_err_cnt;                       /* Gyro Device G-Sensor Register MAX Freeze Error Counter *//*  +B-ON保持が必要 */
static U2 u2_s_gyrodev_gsens_min_err_cnt;                       /* Gyro Device G-Sensor Register MIN Freeze Error Counter *//*  +B-ON保持が必要 */
static U1 u1_s_gyrodev_gsens_rst_cnt;                           /* Gyro Device G-Sensor Read Reset Counter *//*  +B-ON保持が必要 */

static U2 u2_s_gyrodev_regstep;                                 /* Gyro Device Register Request Step */
static U4 u4_s_gyrodev_i2c_ack_wait_time;                       /* Gyro Device I2C Request Ack Wait Timer */
static U2 u2_s_gyrodev_reg_btwn_time;                           /* Gyro Device Access Register Between Timer */

static U1 u1_s_gyrodev_gyro_read_complete_flag;                 /* Gyro Device Gyro Register Read Complete Flag */
static U1 u1_s_gyrodev_gsens_read_complete_flag;                /* Gyro Device G-Sensor Register Read Complete Flag */

static ST_XSPI_IVI_GYRO_SENSOR_DATA st_gyrodev_readdata;        /* Gyro Device Read Data */
static U1 u1_s_gyrodev_pre_appon_sts;                           /* Previous APP-ON Status */

static U1 u1_s_gyrodev_gyro_dtcrec_a_flag;                      /* Gyro Device Gyro Register Read Data Check DTC Record(A) Flag */
static U1 u1_s_gyrodev_gsens_dtcrec_a_flag;                     /* Gyro Device G-Sensor Register Read Data Check DTC Record(A) Flag */

static U1 u1_s_gyrodev_notifcondset_sts;                        /* "[API]G-Sensor INT Signal Notification Condition" Function Status */
static U1 u1_s_gyrodev_oscmd_notifcond_rcv_flag;                /* "[API]G-Sensor INT Signal Notification Condition" Setting Request Receive Flag */
static U1 u1_s_gyrodev_oscmd_notifcond_bak_flag;                /* "[API]G-Sensor INT Signal Notification Condition" Setting Request Backup Flag */
static ST_GYRODEV_NOTIFCOND_SETDATA st_gyrodev_notifcond_setreq;    /* "[API]G-Sensor INT Signal Notification Condition" Setting Request Data */
static ST_GYRODEV_NOTIFCOND_SETDATA st_gyrodev_notifcond_setbak;    /* "[API]G-Sensor INT Signal Notification Condition" Setting Request Backup Data *//*  +B-ON保持が必要 */
static U1 u1_s_gyrodev_oscmd_notifcond_read_flag;               /* "[API]G-Sensor INT Signal Notification Condition" Reading Request Receive Flag */
static ST_XSPI_IVI_GYRO_INT_DATA st_gyrodev_notifcond_readreq;  /* "[API]G-Sensor INT Signal Notification Condition" Readting Request Data */

static U1 u1_s_gyrodev_ctrloutset_sts;                          /* "[API]G-Sensor INT Signal Output Control" Function Status */
static U1 u1_s_gyrodev_oscmd_outctl_rcv_flag;                   /* "[API]G-Sensor INT Signal Output Control" Setting Request Receive Flag */
static U1 u1_s_gyrodev_oscmd_outctl_bak_flag;                   /* "[API]G-Sensor INT Signal Output Control" Setting Request Backup Flag */
static ST_GYRODEV_CTRLOUT_SETDATA st_gyrodev_ctrlout_setreq;    /* "[API]G-Sensor INT Signal Output Control" Setting Request Data */
static ST_GYRODEV_CTRLOUT_SETDATA st_gyrodev_ctrlout_setbak;    /* "[API]G-Sensor INT Signal Output Control" Setting Request Backup Data *//*  +B-ON保持が必要 */

/* Gyro control management buffer */
static ST_GYRO_CTL_MNG      st_s_gyro_ctrl;

/* Sequence management buffer */
static ST_GYRO_SEQMNG       st_s_gyro_seqmng;

/* V33-Peri-ON state */
static Dio_LevelType        dl_s_gyro_v33perion_sts;

/* V33 OFF flag */
static U1                   u1_s_gyro_v33OffFlg;

/* BuDET state */
static Dio_LevelType        dl_s_gyro_budet_sts;

/* System OFF flag */
static U1                   u1_s_gyro_sysoffflg;

/* Self-test error count l(6_1) */
static U1                   u1_s_errcnt_l;

/* Self-test error count j(6_1) */
static U1                   u1_s_errcnt_j;  /* preliminary design */

/* Self-test (accelerometer) positive-side data */
static ST_GYRO_ACCTEST      st_s_gyro_accdat_pls;

/* Self-test (accelerometer) negative-side data */
static ST_GYRO_ACCTEST      st_s_gyro_accdat_mns;

/* Config file write management */
static ST_GYRO_CFGMNG       st_s_gyro_cfgmng;

/* Config file upload retry count */
static U1                   u1_s_gyro_uploadcfg_rtrycnt;

/* Shutdown flow (1) retry counter */
static U1                   u1_s_cnt_shutdn;

/* Input parameter setting (2): accelerometer read count counter (k(5_2)) */
static U1                   u1_s_cnt_g_read;

/* Input parameter setting (2): difference check attempt counter (k(5_3)) */
static U2                   u2_s_cnt_diff_verif;

/* Input parameter setting (2): accelerometer sensor data (axis information) */
static ST_GYRO_ACC          st_s_gyro_accdat;

/* Timer for wait time within flows */
static U4                   u4_s_gyro_linktim;

/* Measure time from I2C write/read to response */
static U4                   u4_s_gyro_acktime;

static U1                   u1_s_gyrodev_gsensbkup_flg;
static U1                   u1_s_gyrodev_gsensbkup_done_flg;

static U1 u1_s_i2c_exe_flag[GYRODEV_ACK_MAX];
static U4 u4_s_i2c_pid[GYRODEV_ACK_MAX];

static U1 u1_s_gyrodev_gsensbkup_sts;
static U1 u1_s_v33_event_pending = (U1)0xFF; /* 無効値 */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/**************************外部端子入力監視************************/
static U1       u1_s_GyroBuDetHiCheck(void);
static void     vd_s_GyroBuDetHi(void);
static void     vd_s_GyroV33PeriOnCheck(void);

/**************************状態遷移管理***************************/
static void     vd_s_GyroDevCtlMngModSet(const U1 u1_a_MODE);
static void     vd_s_GyroDevUnInitTskStup(void);
static void     vd_s_GyroDevComErrTskStup(void);
static void     vd_s_GyroDevStup1CompV33PeriOnOn(void);
static void     vd_s_GyroDevNormV33PeriOnOn(void);
static void     vd_s_GyroDevErrV33PeriOnOn(void);
static void     vd_s_GyroDevNormV33PeriOnOff(void);
static void     vd_s_GyroDevComSysOffWait(void);
static void     vd_s_GyroDevComSysOffProc(void);
static void     vd_s_GyroDevErrSysOff(void);
static void     vd_s_GyroDevStup1ProSeqComp(void);
static void     vd_s_GyroDevStup2ProSeqComp(void);
static void     vd_s_GyroDevShtdn1ProSeqComp(void);
static void     vd_s_GyroDevStup1ProErr(void);
static void     vd_s_GyroDevStup2ProErr(void);
static void     vd_s_GyroDevComDtcErr(void);
static void     vd_s_GyroDevShutDn1ProErr(void);
static void     vd_s_GyroDevComRst(void);

/**************************シーケンス管理*************************/
static void     vd_s_GyroDevSeqCtl(void);
static void     vd_s_GyroDevSeqSet(const U1 u1_a_SEQNO);
static void     vd_s_GyroDevSeqIdle(void);
static void     vd_s_GyroDevSeqStaUp1(void);
static U1       u1_s_GyroDevSeqGyrSelfTest(void);
static U1       u1_s_GyroDevSeqAccSelfTest(void);
static void     vd_s_GyroDevSeqSelfTestErr(const U1 u1_a_fail_tgt);
static U1       u1_s_GyroDevSeqAccCfgUpload(void);
static U1       u1_s_GyroGetDatInfo(ST_GYRO_DATAINFO * st_a_datainfo);
static U1       u1_s_GyroGetStsChk(void);
static U1       u1_s_GyroDevSeqAccIntSet(void);
static void     vd_s_GyroDevSeqStaUp2(void);
static void     vd_s_GyroDevSeqGyrShutDn1(void);
static U1       u1_s_GyroDevParamSet2(void);
static void     vd_s_GyroDevAccDataClear(void);
static void     vd_s_GyroDevAccMinMaxUpdate(void);
static U1       u1_s_GyroDevAccMinMaxCheck(void);

/**************************共通関数*************************/
static void     vd_s_GyroSysPwrInit(void);
static void     vd_s_GyroDevMemset(void * vdp_a_dst, const U1 u1_a_DATA, U4 u4_a_size);
static void     vd_s_GyroDevForceEnd(void);
static U1       u1_s_GyroDevTimCheck(const U4 u4_a_SRC, const U4 u4_a_TRGT);
static U1       u1_s_GyroDevCtlMngModGet(void);
static void     vd_s_GyroDevEventGo(const U1 u1_a_EVENT);

static void vd_s_GyroDev_CycChk(void);
static void vd_s_GyroDev_GyroDtcChk(const U2 u2_a_x_data, const U2 u2_a_y_data, const U2 u2_a_z_data);
static void vd_s_GyroDev_GSensDtcChk(const U2 u2_a_x_data, const U2 u2_a_y_data, const U2 u2_a_z_data);
static U1 u1_s_GyroDev_GSensNotifCondFunc(const U1 u1_a_type);
static U1 u1_s_GyroDev_GSensCtrlOutFunc(const U1 u1_a_type);
static void vd_s_GyroDev_Memset(void * vdp_a_dst, const U1 u1_a_data, U4 u4_a_size);
static void vd_s_GyroDev_AppChk(void);
static U1 u1_s_GyroDev_ParamBackup(void);
static U1 u1_s_GyroDev_ShockDetEnHoldChk(void);

static U1 u1_s_Gyro_I2cWriteMgrFunc(const U1 u1_a_ack, const U2 u2_a_wri_max, const U1 i2c_sla, const ST_REG_WRI_REQ * stp_a_wrireq, const ST_GP_I2C_MA_REQ * stp_a_setreg);
static U1 u1_s_Gyro_I2cReadMgrFunc(const U1 u1_a_ack, const U1 i2c_sla, const ST_GP_I2C_MA_REQ *stp_a_setreg, const U1 waitmode);
static U1 u1_s_GyroI2cIsBusy(void);
static void vd_s_GyroI2cAbort(U1 u1_a_ack);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* シーケンス処理テーブル */
static const FP_GYRO_SRQ_FUNC   fp_sp_gyro_Seq[GYRO_SEQ_MAX] = {
    { vd_s_GyroDevSeqIdle       },  /* アイドルシーケンス           */
    { vd_s_GyroDevSeqStaUp1     },  /* GYRO起動(1)処理シーケンス    */
    { vd_s_GyroDevSeqStaUp2     },  /* GYRO起動(2)処理シーケンス    */
    { vd_s_GyroDevSeqGyrShutDn1 }   /* GYRO終了(1)処理シーケンス    */
};

/* ジャイロ状態遷移テーブル */
static const FP_GYRO_EVNT_HNDL  fp_sp2_GYRO_EVENT_HANDLER[GYRO_MODE_MAX][GYRO_EVENT_MAX] =
{
    /* Taks ON                      V33-Peri-ON OFF->ON                 V33-Peri-ON ON->OFF             System OFF                  Sequence Fin                    Startup Anomaly             DTC Anomaly             Fin Anomaly                 Reset               BUDET_HI          BUDET_LO                                         */
    { vd_s_GyroDevUnInitTskStup,    vdp_PTR_NA,                         vdp_PTR_NA,                     vdp_PTR_NA,                 vdp_PTR_NA,                     vdp_PTR_NA,                 vdp_PTR_NA,             vdp_PTR_NA,                 vdp_PTR_NA,         vd_s_GyroBuDetHi, vd_s_GyroDevUnInitTskStup },  /* 未初期化         */
    { vd_s_GyroDevComErrTskStup,    vdp_PTR_NA,                         vdp_PTR_NA,                     vd_s_GyroDevComSysOffWait,  vd_s_GyroDevStup1ProSeqComp,    vd_s_GyroDevStup1ProErr,    vdp_PTR_NA,             vdp_PTR_NA,                 vd_s_GyroDevComRst, vd_s_GyroBuDetHi, vdp_PTR_NA                },  /* 起動(1)実施中    */
    { vdp_PTR_NA,                   vd_s_GyroDevStup1CompV33PeriOnOn,   vdp_PTR_NA,                     vd_s_GyroDevComSysOffProc,  vdp_PTR_NA,                     vdp_PTR_NA,                 vdp_PTR_NA,             vdp_PTR_NA,                 vdp_PTR_NA,         vd_s_GyroBuDetHi, vdp_PTR_NA                },  /* 起動(1)実施完了  */
    { vd_s_GyroDevComErrTskStup,    vdp_PTR_NA,                         vdp_PTR_NA,                     vd_s_GyroDevComSysOffWait,  vd_s_GyroDevStup2ProSeqComp,    vd_s_GyroDevStup2ProErr,    vdp_PTR_NA,             vdp_PTR_NA,                 vdp_PTR_NA,         vd_s_GyroBuDetHi, vdp_PTR_NA                },  /* 起動(2)実施中    */
    { vd_s_GyroDevComErrTskStup,    vd_s_GyroDevNormV33PeriOnOn,        vd_s_GyroDevNormV33PeriOnOff,   vd_s_GyroDevComSysOffWait,  vdp_PTR_NA,                     vdp_PTR_NA,                 vd_s_GyroDevComDtcErr,  vdp_PTR_NA,                 vd_s_GyroDevComRst, vd_s_GyroBuDetHi, vdp_PTR_NA                },  /* 通常動作中       */
    { vd_s_GyroDevComErrTskStup,    vdp_PTR_NA,                         vdp_PTR_NA,                     vd_s_GyroDevComSysOffWait,  vd_s_GyroDevShtdn1ProSeqComp,   vdp_PTR_NA,                 vdp_PTR_NA,             vd_s_GyroDevShutDn1ProErr,  vdp_PTR_NA,         vd_s_GyroBuDetHi, vdp_PTR_NA                },  /* 終了(1)実施中    */
    { vd_s_GyroDevComErrTskStup,    vd_s_GyroDevErrV33PeriOnOn,         vdp_PTR_NA,                     vd_s_GyroDevErrSysOff,      vdp_PTR_NA,                     vdp_PTR_NA,                 vdp_PTR_NA,             vdp_PTR_NA,                 vdp_PTR_NA,         vd_s_GyroBuDetHi, vdp_PTR_NA                }   /* 異常停止中       */
};

/* I2C書き込み管理用テーブル */
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_SETUP_GYR[GYRO_WRISTEP_SETUP_GYR] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         2,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_TEST_COMSET_GYR[GYRO_WRISTEP_TEST_COMSET_GYR] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_WDG_GYR[GYRO_WRISTEP_WDG_GYR] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_MODE_ON_GYR[GYRO_WRISTEP_MODE_ON_GYR] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_MODE_OFF_GYR[GYRO_WRISTEP_MODE_OFF_GYR] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_SETUP_SEN1_ACC[GYRO_WRISTEP_SETUP_SEN1_ACC] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         2,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_SETUP_SEN1_BW_ACC[GYRO_WRISTEP_SETUP_SEN1_BW_ACC] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_SETUP_SEN2_ACC[GYRO_WRISTEP_SETUP_SEN2_ACC] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         2,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_WDG_ACC[GYRO_WRISTEP_WDG_ACC] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_MODE_ON_ACC[GYRO_WRISTEP_MODE_ON_ACC] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_MODE_OFF_ACC[GYRO_WRISTEP_MODE_OFF_ACC] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_SELFTEST_ACC_PLS[GYRO_WRISTEP_SELFTEST_ACC_PLS] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_SELFTEST_ACC_MNS[GYRO_WRISTEP_SELFTEST_ACC_MNS] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_SELFTEST_ACC_DISABLE[GYRO_WRISTEP_SELFTEST_ACC_DISABLE] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_PWRCONF_ON[GYRO_WRISTEP_PWRCONF_ON] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_PWRCONF_OFF[GYRO_WRISTEP_PWRCONF_OFF] = {    /* preliminary design */
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_INTCONF_ON[GYRO_WRISTEP_INTCONF_ON] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_INTCONF_OFF[GYRO_WRISTEP_INTCONF_OFF] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_SOFTRESET[GYRO_WRISTEP_SOFTRESET] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_INT_ANYMOT_TH[GYRO_WRISTEP_INT_ANYMOT_TH] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0},
    {        1,         1,         0},
    {        2,         1,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_INT_ANYMOT_EN[GYRO_WRISTEP_INT_ANYMOT_EN] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0},
    {        1,         1,         0},
    {        2,         1,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_INT_OTH[GYRO_WRISTEP_INT_OTH] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         3,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_INPRM_SEN1_BW_ACC[GYRO_WRISTEP_INPRM_SEN1_BW_ACC] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_CFG_OFST1[GYRO_WRISTEP_CFG_OFST1] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_CFG_OFST2[GYRO_WRISTEP_CFG_OFST2] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};
static const ST_REG_WRI_REQ     st_sp_GYRO_WRISTEP_CFG_DATA[GYRO_WRISTEP_CFG_DATA] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};

static const U1                 u1_sp_GYRO_CONFIG[] = {
    0x47, 0x2D, 0x43, 0x4F, 0x4E, 0x46, 0x49, 0x47, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x47, 0x43, 0x4F, 0x4E, 0x46, 0x49, 0x47, 0x5F, 0x56, 0x30, 0x31, 0x2D, 0x37, 0x31, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xC8, 0x2E, 0x00, 0x2E, 0x80, 0x2E, 0x71, 0x01, 0xC8, 0x2E, 0x00, 0x2E, 0xC8, 0x2E, 0x00, 0x2E,
    0x80, 0x2E, 0x36, 0x01, 0x80, 0x2E, 0xB6, 0x00, 0x80, 0x2E, 0x95, 0x00, 0x80, 0x2E, 0xB7, 0x00,
    0x50, 0x39, 0x21, 0x2E, 0xB0, 0xF0, 0x10, 0x30, 0x21, 0x2E, 0x16, 0xF0, 0x80, 0x2E, 0xFC, 0x00,
    0x31, 0x50, 0x41, 0x30, 0x01, 0x42, 0x3C, 0x80, 0x00, 0x2E, 0x01, 0x40, 0x01, 0x42, 0x21, 0x2E,
    0xFF, 0xAF, 0xB8, 0x2E, 0x02, 0x00, 0x04, 0x00, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9D, 0xA7,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0xFD, 0x2D, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9A, 0x01,
    0x34, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0x50, 0xF7, 0x7F, 0x00, 0x2E,
    0x0F, 0x2E, 0x43, 0xF0, 0xF8, 0xBF, 0xFF, 0xBB, 0xC0, 0xB3, 0x11, 0x2F, 0xE6, 0x7F, 0xD5, 0x7F,
    0xC4, 0x7F, 0xB3, 0x7F, 0xA2, 0x7F, 0x91, 0x7F, 0x80, 0x7F, 0x7B, 0x7F, 0x98, 0x2E, 0x44, 0xB2,
    0x80, 0x6F, 0x91, 0x6F, 0xA2, 0x6F, 0xB3, 0x6F, 0xC4, 0x6F, 0xD5, 0x6F, 0xE6, 0x6F, 0x7B, 0x6F,
    0x47, 0x30, 0x2F, 0x2E, 0xB8, 0xF0, 0xF7, 0x6F, 0x70, 0x5F, 0xC8, 0x2E, 0xC8, 0x2E, 0x60, 0x50,
    0xD1, 0x7F, 0xE2, 0x7F, 0xC7, 0x7F, 0xF6, 0x7F, 0xB0, 0x7F, 0x36, 0x30, 0x03, 0x2E, 0x01, 0xF0,
    0x9E, 0xBC, 0x21, 0x54, 0x9E, 0xBB, 0xBF, 0x82, 0xB7, 0x05, 0x80, 0x40, 0x43, 0x8E, 0x41, 0x40,
    0x08, 0xBC, 0x41, 0x0A, 0x1F, 0x50, 0x4E, 0x10, 0x11, 0x42, 0xAB, 0x7F, 0x00, 0x2E, 0xE2, 0x41,
    0xC1, 0x41, 0x28, 0xBD, 0x51, 0x0A, 0x4E, 0x10, 0x11, 0x42, 0xC3, 0x8F, 0x11, 0x30, 0xE2, 0x41,
    0xC7, 0x41, 0x28, 0xBD, 0x97, 0x0A, 0x96, 0x10, 0x02, 0x42, 0x23, 0x2E, 0x26, 0x00, 0x98, 0x2E,
    0xFA, 0x01, 0x00, 0xB2, 0x01, 0x2F, 0x98, 0x2E, 0x00, 0xB0, 0x00, 0x31, 0x21, 0x2E, 0xB8, 0xF0,
    0xF6, 0x6F, 0xAB, 0x6F, 0xD1, 0x6F, 0xE2, 0x6F, 0xC7, 0x6F, 0xB0, 0x6F, 0xA0, 0x5F, 0xC8, 0x2E,
    0x40, 0x30, 0xC0, 0x2E, 0x21, 0x2E, 0xBA, 0xF0, 0x00, 0x31, 0xC0, 0x2E, 0x21, 0x2E, 0xBA, 0xF0,
    0x10, 0x30, 0xC0, 0x2E, 0x21, 0x2E, 0xBB, 0xF0, 0x1A, 0x24, 0x30, 0x00, 0x80, 0x2E, 0x94, 0x01,
    0xAA, 0x00, 0x05, 0xE0, 0x00, 0x00, 0x00, 0x0C, 0xE8, 0x73, 0x04, 0x00, 0x00, 0x02, 0x00, 0x01,
    0x00, 0x00, 0x30, 0x0A, 0x80, 0x00, 0xAA, 0x00, 0x05, 0xE0, 0x47, 0x00, 0x88, 0x00, 0x28, 0x00,
    0x89, 0xF0, 0x2B, 0x00, 0x80, 0x00, 0x39, 0xF0, 0x03, 0x01, 0x06, 0x01, 0x0B, 0x01, 0x09, 0x01,
    0x59, 0xF0, 0xC0, 0x00, 0xB1, 0xF0, 0x00, 0x40, 0xAF, 0x00, 0xFF, 0x00, 0xFF, 0xB7, 0x00, 0x02,
    0x00, 0xB0, 0x05, 0x80, 0x54, 0x00, 0x5C, 0x00, 0x5A, 0x00, 0x52, 0xF0, 0x6D, 0x00, 0x32, 0xF0,
    0x66, 0x00, 0x28, 0xF0, 0x72, 0x00, 0x75, 0x00, 0x75, 0x00, 0x7D, 0x00, 0x00, 0x10, 0x7F, 0x00,
    0x00, 0x0C, 0x22, 0x00, 0x8B, 0x00, 0x81, 0x00, 0x9A, 0x01, 0x88, 0x00, 0x60, 0x50, 0xF6, 0x7F,
    0xEB, 0x7F, 0xD0, 0x7F, 0xC5, 0x7F, 0xB7, 0x7F, 0x98, 0x2E, 0xFA, 0x01, 0x00, 0x90, 0xA4, 0x7F,
    0x03, 0x2F, 0x25, 0x50, 0x21, 0x2E, 0xBC, 0xF0, 0x21, 0x2D, 0x01, 0x2E, 0x01, 0xF0, 0x0E, 0xBC,
    0x27, 0x5A, 0x0E, 0xB8, 0x36, 0x30, 0x30, 0x04, 0x46, 0x41, 0x7F, 0x89, 0x03, 0x8B, 0x04, 0x41,
    0x68, 0xBF, 0xB4, 0x0B, 0x23, 0x58, 0xB0, 0x11, 0x16, 0x43, 0x00, 0x2E, 0x67, 0x41, 0x46, 0x41,
    0xF8, 0xBF, 0xBE, 0x0B, 0xB0, 0x11, 0x43, 0x8F, 0x16, 0x43, 0x15, 0x30, 0xE6, 0x41, 0xC7, 0x41,
    0x68, 0xBF, 0xB7, 0x0B, 0x30, 0x10, 0x00, 0x43, 0x2B, 0x2E, 0x27, 0x00, 0x25, 0x50, 0x21, 0x2E,
    0xB8, 0xF0, 0xF6, 0x6F, 0xEB, 0x6F, 0xD0, 0x6F, 0xB7, 0x6F, 0xA4, 0x6F, 0xC5, 0x6F, 0xA0, 0x5F,
    0xC8, 0x2E, 0x90, 0x50, 0xF7, 0x7F, 0x17, 0x30, 0x2F, 0x2E, 0x5F, 0xF0, 0xE6, 0x7F, 0x00, 0x2E,
    0x0D, 0x2E, 0xB9, 0xF0, 0xB7, 0x09, 0x80, 0xB3, 0x10, 0x2F, 0xD5, 0x7F, 0xC4, 0x7F, 0xB3, 0x7F,
    0xA2, 0x7F, 0x91, 0x7F, 0x80, 0x7F, 0x7B, 0x7F, 0x98, 0x2E, 0x5B, 0xB1, 0x80, 0x6F, 0x91, 0x6F,
    0xA2, 0x6F, 0xB3, 0x6F, 0xC4, 0x6F, 0xD5, 0x6F, 0x7B, 0x6F, 0x17, 0x30, 0x2F, 0x2E, 0xB9, 0xF0,
    0xE6, 0x6F, 0xF7, 0x6F, 0x70, 0x5F, 0xC8, 0x2E, 0x10, 0x50, 0x98, 0x2E, 0x72, 0xB0, 0x20, 0x26,
    0x98, 0x2E, 0xF0, 0x00, 0x98, 0x2E, 0xF8, 0x00, 0x98, 0x2E, 0xF4, 0x00, 0x2B, 0x50, 0x21, 0x2E,
    0x92, 0x00, 0x29, 0x52, 0x23, 0x2E, 0x91, 0x00, 0x2D, 0x50, 0x98, 0x2E, 0x9C, 0xB3, 0x2F, 0x50,
    0x98, 0x2E, 0x96, 0xB4, 0x31, 0x50, 0x11, 0x30, 0x01, 0x42, 0x3F, 0x80, 0xF0, 0x7F, 0x98, 0x2E,
    0x0A, 0xB0, 0xF1, 0x6F, 0x00, 0x2E, 0x00, 0x2E, 0xD0, 0x2E, 0x01, 0x2E, 0x26, 0x00, 0x00, 0xB2,
    0x14, 0x2F, 0x02, 0x30, 0x1F, 0x50, 0xF1, 0x7F, 0x25, 0x2E, 0x26, 0x00, 0x98, 0x2E, 0x8D, 0xB5,
    0x1F, 0x50, 0x98, 0x2E, 0xC2, 0xB0, 0x98, 0x2E, 0x4B, 0xB3, 0x1F, 0x50, 0x98, 0x2E, 0x9F, 0xB3,
    0x1F, 0x52, 0x98, 0x2E, 0x99, 0xB4, 0x21, 0x2E, 0x2E, 0x00, 0xF1, 0x6F, 0x01, 0x2E, 0x27, 0x00,
    0x00, 0xB2, 0x0B, 0x2F, 0x02, 0x30, 0x23, 0x50, 0xF1, 0x7F, 0x25, 0x2E, 0x27, 0x00, 0x98, 0x2E,
    0x8D, 0xB5, 0x98, 0x2E, 0x9F, 0xB2, 0x21, 0x2E, 0x4F, 0x00, 0xF1, 0x6F, 0x05, 0x2E, 0x4F, 0x00,
    0x23, 0xBD, 0x01, 0x2E, 0x2E, 0x00, 0x46, 0x86, 0x10, 0x0A, 0x40, 0x42, 0xF3, 0x7F, 0x98, 0x2E,
    0x0A, 0xB0, 0x05, 0x54, 0xF0, 0x6F, 0x03, 0x2E, 0x90, 0x00, 0x2D, 0xBD, 0x2D, 0xB9, 0x01, 0x42,
    0x0B, 0x30, 0x3A, 0x82, 0x80, 0x90, 0x37, 0x2E, 0x90, 0x00, 0xBB, 0x2F, 0x10, 0x30, 0x21, 0x2E,
    0x5F, 0xF0, 0xB8, 0x2D, 0x01, 0x2E, 0x91, 0x00, 0x01, 0x80, 0xC0, 0x2E, 0x00, 0x40, 0x0F, 0xB8,
    0x35, 0x50, 0x33, 0x52, 0x02, 0x40, 0x51, 0x0A, 0x01, 0x42, 0x09, 0x80, 0x25, 0x52, 0xC0, 0x2E,
    0x01, 0x42, 0x00, 0x2E, 0x01, 0x2E, 0x55, 0xF0, 0xC0, 0x2E, 0x21, 0x2E, 0x55, 0xF0, 0x30, 0x50,
    0x00, 0x30, 0x37, 0x56, 0x05, 0x30, 0x05, 0x2C, 0xFB, 0x7F, 0x3E, 0xBE, 0xD2, 0xBA, 0xB2, 0xB9,
    0x6C, 0x0B, 0x53, 0x0E, 0xF9, 0x2F, 0x53, 0x1A, 0x01, 0x2F, 0x4D, 0x0E, 0xF5, 0x2F, 0xD2, 0x7F,
    0x04, 0x30, 0x1F, 0x2C, 0xE1, 0x7F, 0xC5, 0x01, 0xA3, 0x03, 0x72, 0x0E, 0x03, 0x2F, 0x72, 0x1A,
    0x0F, 0x2F, 0x79, 0x0F, 0x0D, 0x2F, 0xE1, 0x6F, 0x4F, 0x04, 0x5F, 0xB9, 0xB1, 0xBF, 0xFA, 0x0B,
    0xD2, 0x6F, 0x96, 0x06, 0xB1, 0x25, 0x51, 0xBF, 0xEB, 0x7F, 0x06, 0x00, 0xB2, 0x25, 0x27, 0x03,
    0xDB, 0x7F, 0xCF, 0xBF, 0x3E, 0xBF, 0x01, 0xB8, 0xD2, 0xBA, 0x41, 0xBA, 0xB2, 0xB9, 0x07, 0x0A,
    0x6E, 0x0B, 0xC0, 0x90, 0xDF, 0x2F, 0x40, 0x91, 0xDD, 0x2F, 0xFB, 0x6F, 0xD0, 0x5F, 0xB8, 0x2E,
    0x10, 0x50, 0xFB, 0x7F, 0x21, 0x25, 0x98, 0x2E, 0x53, 0xB0, 0xFB, 0x6F, 0x21, 0x25, 0xF0, 0x5F,
    0x10, 0x25, 0x80, 0x2E, 0x0F, 0xB0, 0x83, 0x86, 0x01, 0x30, 0x00, 0x30, 0x94, 0x40, 0x24, 0x18,
    0x06, 0x00, 0x53, 0x0E, 0x4F, 0x02, 0xF9, 0x2F, 0xB8, 0x2E, 0x03, 0x30, 0x15, 0x40, 0xD9, 0x04,
    0x2B, 0x0E, 0x1D, 0x23, 0x29, 0x0F, 0x15, 0x40, 0x0C, 0x23, 0x2B, 0x0E, 0x9D, 0x23, 0x29, 0x0F,
    0x4E, 0x23, 0x00, 0x40, 0x03, 0x0E, 0xD8, 0x22, 0x01, 0x0F, 0x94, 0x42, 0x4B, 0x22, 0x95, 0x42,
    0x81, 0x42, 0xB8, 0x2E, 0x35, 0x50, 0x41, 0x30, 0x02, 0x40, 0x51, 0x0A, 0x01, 0x42, 0x18, 0x82,
    0x39, 0x50, 0x60, 0x42, 0x70, 0x3C, 0x3B, 0x54, 0x42, 0x42, 0x69, 0x82, 0x82, 0x32, 0x43, 0x40,
    0x18, 0x08, 0x02, 0x0A, 0x40, 0x42, 0x42, 0x80, 0x02, 0x3F, 0x01, 0x40, 0x10, 0x50, 0x4A, 0x08,
    0xFB, 0x7F, 0x11, 0x42, 0x0B, 0x31, 0x0B, 0x42, 0x3E, 0x80, 0xF1, 0x30, 0x01, 0x42, 0x00, 0x2E,
    0x01, 0x2E, 0x40, 0xF0, 0x1F, 0x90, 0x20, 0x2F, 0x03, 0x30, 0x3F, 0x50, 0x3D, 0x54, 0xF4, 0x34,
    0x06, 0x30, 0x43, 0x52, 0xF5, 0x32, 0x1D, 0x1A, 0xE3, 0x22, 0x18, 0x1A, 0x41, 0x58, 0xE3, 0x22,
    0x04, 0x30, 0xD5, 0x40, 0xB5, 0x0D, 0xE1, 0xBE, 0x6F, 0xBB, 0x80, 0x91, 0xA9, 0x0D, 0x01, 0x89,
    0xB5, 0x23, 0x10, 0xA1, 0xF7, 0x2F, 0xDA, 0x0E, 0xF4, 0x34, 0xEB, 0x2F, 0x01, 0x2E, 0x2F, 0x00,
    0x70, 0x1A, 0x00, 0x30, 0x21, 0x30, 0x02, 0x2C, 0x08, 0x22, 0x30, 0x30, 0x00, 0xB2, 0x06, 0x2F,
    0x21, 0x2E, 0x59, 0xF0, 0x98, 0x2E, 0x0A, 0xB0, 0x00, 0x2E, 0x00, 0x2E, 0xD0, 0x2E, 0xFB, 0x6F,
    0xF0, 0x5F, 0xB8, 0x2E, 0x03, 0x58, 0x01, 0x5A, 0x42, 0xBD, 0xAF, 0xB9, 0xC1, 0xBC, 0x54, 0xBF,
    0x1F, 0xB9, 0xEF, 0xBB, 0xCF, 0xB8, 0x9A, 0x0B, 0x10, 0x50, 0xC0, 0xB3, 0xB1, 0x0B, 0x76, 0x2F,
    0x80, 0xB3, 0x74, 0x2F, 0x0F, 0x2E, 0x50, 0x00, 0x01, 0x8C, 0xC0, 0xB3, 0x5C, 0x2F, 0xC3, 0xBF,
    0xC0, 0xB2, 0xD5, 0xBE, 0x55, 0xBA, 0xF3, 0xB9, 0x05, 0x30, 0x07, 0x30, 0x09, 0x2F, 0xF0, 0x7F,
    0x00, 0x2E, 0x00, 0x40, 0x0F, 0x2E, 0x53, 0x00, 0x07, 0x04, 0x00, 0xA8, 0xE8, 0x05, 0xC7, 0x23,
    0xF0, 0x6F, 0x80, 0xB2, 0x02, 0x30, 0x09, 0x2F, 0xF7, 0x7F, 0x00, 0x2E, 0x82, 0x41, 0x0F, 0x2E,
    0x54, 0x00, 0x97, 0x04, 0x80, 0xA8, 0xEA, 0x05, 0x97, 0x22, 0xF7, 0x6F, 0x40, 0xB2, 0x09, 0x2F,
    0x02, 0x82, 0x00, 0x2E, 0x41, 0x40, 0x0B, 0x2E, 0x55, 0x00, 0x4D, 0x04, 0x05, 0x30, 0x40, 0xA8,
    0x69, 0x05, 0x4D, 0x23, 0x7C, 0x0F, 0x11, 0x30, 0x17, 0x30, 0x05, 0x2F, 0x54, 0x0F, 0x03, 0x2F,
    0x6C, 0x0F, 0x17, 0x30, 0x00, 0x2F, 0x07, 0x30, 0xC0, 0x91, 0x02, 0x30, 0x0B, 0x2F, 0x03, 0x2E,
    0x52, 0x00, 0x41, 0x82, 0x25, 0x2E, 0x51, 0x00, 0xCB, 0x0E, 0x23, 0x2E, 0x52, 0x00, 0x0D, 0x2F,
    0x25, 0x2E, 0x56, 0x00, 0x0B, 0x2D, 0x09, 0x2E, 0x51, 0x00, 0x21, 0x29, 0x25, 0x2E, 0x52, 0x00,
    0xE3, 0x0E, 0x29, 0x2E, 0x51, 0x00, 0x01, 0x2F, 0x23, 0x2E, 0x56, 0x00, 0x03, 0x2E, 0x56, 0x00,
    0x40, 0xB2, 0x21, 0x2F, 0x00, 0x40, 0x21, 0x2E, 0x53, 0x00, 0x45, 0x50, 0x91, 0x41, 0x11, 0x42,
    0x00, 0x2E, 0x81, 0x41, 0x01, 0x42, 0x18, 0x2D, 0x11, 0x30, 0x23, 0x2E, 0x50, 0x00, 0x00, 0x40,
    0x21, 0x2E, 0x53, 0x00, 0x45, 0x50, 0x91, 0x41, 0x11, 0x42, 0x01, 0x30, 0x82, 0x41, 0x02, 0x42,
    0x23, 0x2E, 0x51, 0x00, 0x23, 0x2E, 0x52, 0x00, 0x23, 0x2E, 0x56, 0x00, 0x05, 0x2D, 0x00, 0x30,
    0x21, 0x2E, 0x50, 0x00, 0x21, 0x2E, 0x56, 0x00, 0x01, 0x2E, 0x56, 0x00, 0x00, 0x90, 0x20, 0x30,
    0x02, 0x2F, 0x21, 0x2E, 0x5F, 0xF0, 0x05, 0x2D, 0x03, 0x2E, 0x90, 0x00, 0x08, 0x0A, 0x21, 0x2E,
    0x90, 0x00, 0xF0, 0x5F, 0xB8, 0x2E, 0x30, 0x50, 0xFB, 0x7F, 0x98, 0x2E, 0x84, 0xB2, 0x47, 0x58,
    0x00, 0x2E, 0x10, 0x43, 0x01, 0x43, 0x3A, 0x8B, 0x98, 0x2E, 0xE5, 0xB1, 0x00, 0x2E, 0x41, 0x41,
    0x40, 0xB2, 0x43, 0x2F, 0x04, 0x83, 0x01, 0x2E, 0x5C, 0x00, 0x42, 0x40, 0x77, 0x82, 0x02, 0x04,
    0x00, 0xAC, 0x40, 0x42, 0x01, 0x2F, 0x21, 0x2E, 0x58, 0x00, 0x50, 0x40, 0x52, 0x40, 0x02, 0x0F,
    0x02, 0x30, 0x01, 0x2F, 0x00, 0xAC, 0x01, 0x2F, 0x25, 0x2E, 0x58, 0x00, 0x7E, 0x88, 0x06, 0x85,
    0x85, 0x86, 0xC5, 0x80, 0x41, 0x40, 0x04, 0x41, 0x4C, 0x04, 0x05, 0x8A, 0x82, 0x40, 0xC3, 0x40,
    0x04, 0x40, 0xE5, 0x7F, 0xD1, 0x7F, 0x98, 0x2E, 0xB1, 0xB1, 0xE5, 0x6F, 0x72, 0x83, 0x45, 0x84,
    0x85, 0x86, 0xC5, 0x8C, 0xC4, 0x40, 0x83, 0x40, 0x42, 0x40, 0xD1, 0x6F, 0x40, 0x43, 0xE6, 0x7F,
    0x98, 0x2E, 0xB1, 0xB1, 0xE2, 0x6F, 0xD1, 0x6F, 0x80, 0x42, 0xB2, 0x84, 0x85, 0x86, 0xC5, 0x88,
    0x05, 0x81, 0x82, 0x40, 0xC3, 0x40, 0x04, 0x41, 0xE0, 0x7F, 0x98, 0x2E, 0xB1, 0xB1, 0xE1, 0x6F,
    0x16, 0x30, 0x40, 0x42, 0x98, 0x2E, 0x2D, 0xB2, 0x2D, 0x2E, 0x5E, 0xF0, 0xFB, 0x6F, 0xD0, 0x5F,
    0xB8, 0x2E, 0x01, 0x2E, 0x5B, 0x00, 0x20, 0x50, 0x30, 0x8A, 0xF5, 0x7F, 0x17, 0x30, 0xF8, 0x15,
    0x05, 0x31, 0x89, 0x17, 0x8F, 0x0F, 0x68, 0x05, 0xE3, 0x7F, 0x10, 0x2F, 0x40, 0xA4, 0x0C, 0x2F,
    0xDA, 0x04, 0x19, 0x18, 0x00, 0xB2, 0x07, 0x2F, 0x10, 0xA0, 0x02, 0x2F, 0xF1, 0x6F, 0x04, 0x2C,
    0xB9, 0x11, 0x70, 0x12, 0xFD, 0x14, 0x8B, 0x0B, 0x96, 0x00, 0x15, 0x2C, 0x02, 0x25, 0xA3, 0x04,
    0xCF, 0x16, 0x4F, 0x04, 0xF3, 0x06, 0x0A, 0x17, 0x51, 0x18, 0xE1, 0x18, 0x00, 0xB2, 0xDA, 0x18,
    0x07, 0x2F, 0x10, 0xA0, 0x02, 0x2F, 0xF2, 0x6F, 0x04, 0x2C, 0xBA, 0x11, 0xB0, 0x12, 0x7D, 0x14,
    0x91, 0x0B, 0xE2, 0x6F, 0x16, 0x00, 0xE0, 0x5F, 0xB8, 0x2E, 0x05, 0x50, 0x0D, 0xBC, 0x0D, 0xB8,
    0x10, 0x50, 0xF0, 0x7F, 0x00, 0x2E, 0xF0, 0x6F, 0x03, 0x2E, 0x57, 0x00, 0x08, 0x1A, 0x3A, 0x2F,
    0xF1, 0x6F, 0x43, 0xB2, 0x23, 0x2E, 0x57, 0x00, 0x49, 0x50, 0x2D, 0x2F, 0x42, 0xB2, 0x23, 0x2F,
    0x41, 0xB2, 0x19, 0x2F, 0x44, 0xB2, 0x0F, 0x2F, 0x45, 0xB2, 0x05, 0x2F, 0x01, 0x30, 0x11, 0x42,
    0x01, 0x42, 0x3E, 0x80, 0x28, 0x2C, 0x01, 0x42, 0x71, 0x31, 0x11, 0x42, 0x52, 0x30, 0x3E, 0x82,
    0x02, 0x42, 0x23, 0x32, 0x20, 0x2C, 0x43, 0x42, 0xE1, 0x32, 0x11, 0x42, 0x62, 0x30, 0x3E, 0x82,
    0x02, 0x42, 0x63, 0x34, 0x18, 0x2C, 0x43, 0x42, 0x31, 0x37, 0x11, 0x42, 0x62, 0x30, 0x3E, 0x82,
    0x02, 0x42, 0x63, 0x34, 0x10, 0x2C, 0x43, 0x42, 0x01, 0x32, 0x11, 0x42, 0x52, 0x30, 0x3E, 0x82,
    0x02, 0x42, 0x23, 0x32, 0x08, 0x2C, 0x43, 0x42, 0x61, 0x31, 0x11, 0x42, 0x41, 0x30, 0x01, 0x42,
    0x3E, 0x80, 0x11, 0x31, 0x01, 0x42, 0xF0, 0x5F, 0xB8, 0x2E, 0x4D, 0x52, 0x3B, 0x50, 0x54, 0x40,
    0x4B, 0x54, 0xE0, 0x08, 0x83, 0x42, 0x81, 0x86, 0x52, 0x40, 0x48, 0xBA, 0x50, 0x09, 0xD4, 0x42,
    0xC5, 0x42, 0xC2, 0x86, 0x41, 0x40, 0x08, 0x08, 0xD0, 0x42, 0x98, 0xB8, 0xC1, 0x42, 0xA8, 0xB8,
    0xFE, 0x80, 0xC0, 0x2E, 0x01, 0x42, 0x00, 0x2E, 0x51, 0x52, 0x10, 0x50, 0x52, 0x40, 0xFB, 0x7F,
    0x44, 0x80, 0x4B, 0x40, 0x12, 0x42, 0x0B, 0x42, 0x37, 0x80, 0x05, 0x82, 0x0B, 0x40, 0x4B, 0x42,
    0x7C, 0x80, 0x05, 0x82, 0x0B, 0x40, 0x4B, 0x42, 0x7C, 0x80, 0x05, 0x82, 0x00, 0x40, 0x40, 0x42,
    0x77, 0x80, 0x00, 0x2E, 0x11, 0x40, 0x04, 0x84, 0x0B, 0x40, 0x91, 0x42, 0xB7, 0x80, 0x05, 0x82,
    0x00, 0x40, 0x40, 0x42, 0x7C, 0x80, 0x8B, 0x42, 0x05, 0x82, 0x0B, 0x40, 0x4B, 0x42, 0x7C, 0x80,
    0x05, 0x82, 0x00, 0x40, 0x40, 0x42, 0x7C, 0x8C, 0x98, 0x2E, 0x84, 0xB2, 0x4F, 0x54, 0x90, 0x43,
    0x81, 0x43, 0xBC, 0x83, 0x95, 0x40, 0x93, 0x40, 0x90, 0x40, 0x94, 0x40, 0x38, 0xBF, 0x93, 0x40,
    0x48, 0xBE, 0x75, 0x0B, 0x82, 0x40, 0x20, 0x0A, 0x55, 0x42, 0x28, 0xBD, 0x50, 0x42, 0x13, 0x0A,
    0xFB, 0x6F, 0xC0, 0x2E, 0x40, 0x42, 0xF0, 0x5F, 0x53, 0x52, 0x00, 0x2E, 0x64, 0x40, 0x62, 0x40,
    0x40, 0x40, 0x00, 0x90, 0xA8, 0xB8, 0xA8, 0xBD, 0x61, 0x0A, 0x18, 0x0A, 0x0E, 0x2F, 0x0B, 0x2E,
    0x27, 0xF0, 0x40, 0x91, 0x06, 0x2F, 0x05, 0x2E, 0x28, 0xF0, 0x62, 0x1A, 0x61, 0x22, 0xC0, 0x2E,
    0xF2, 0x3F, 0x10, 0x22, 0x55, 0x1A, 0x3B, 0x58, 0x9C, 0x0A, 0x10, 0x22, 0xB8, 0x2E, 0x03, 0x2E,
    0x91, 0x00, 0x41, 0x80, 0xA0, 0x50, 0x00, 0x40, 0x2A, 0x25, 0xB6, 0x84, 0x83, 0xBD, 0xBF, 0xB9,
    0x02, 0xBE, 0x83, 0x42, 0x4F, 0xBA, 0x81, 0xBE, 0xF2, 0x7F, 0x5F, 0xB9, 0x8F, 0xB9, 0x74, 0x7F,
    0xEB, 0x7F, 0xC0, 0xB2, 0x82, 0x7F, 0x0B, 0x30, 0x7F, 0x2F, 0x62, 0x6F, 0x80, 0x90, 0x05, 0x2F,
    0x72, 0x6F, 0x80, 0x90, 0x02, 0x2F, 0x82, 0x6F, 0x80, 0xB2, 0x76, 0x2F, 0x05, 0x2E, 0x70, 0x00,
    0x80, 0x90, 0x08, 0x2F, 0x55, 0x54, 0x03, 0x30, 0x59, 0x58, 0x15, 0x30, 0x93, 0x42, 0x54, 0x0E,
    0xFC, 0x2F, 0x2B, 0x2E, 0x70, 0x00, 0x42, 0x40, 0xDB, 0x7F, 0x0B, 0x30, 0x42, 0x82, 0x21, 0xBD,
    0x04, 0xBC, 0x84, 0xB9, 0xCB, 0x7F, 0x21, 0xB9, 0x41, 0x40, 0x0B, 0x30, 0xB2, 0x7F, 0x94, 0xBC,
    0x57, 0x50, 0x55, 0x58, 0xAB, 0x7F, 0x94, 0xB8, 0x93, 0x04, 0x23, 0x5A, 0xF3, 0x6F, 0x00, 0x2E,
    0xD6, 0x40, 0xF3, 0x7F, 0x80, 0x91, 0x03, 0x30, 0x02, 0x2F, 0x00, 0x2E, 0x44, 0x2C, 0x03, 0x43,
    0x46, 0x41, 0x80, 0xA9, 0xDE, 0x05, 0xB7, 0x23, 0x07, 0x41, 0xC0, 0xB3, 0x2D, 0x2F, 0x47, 0x41,
    0xC0, 0xA1, 0x17, 0x30, 0xFB, 0x22, 0xF2, 0x0E, 0x0B, 0x40, 0x02, 0x2F, 0x6B, 0x25, 0x33, 0x1A,
    0x02, 0x2F, 0x03, 0x30, 0x30, 0x2C, 0x03, 0x43, 0x03, 0x41, 0xDF, 0x28, 0x03, 0x43, 0xD9, 0x0E,
    0x29, 0x2F, 0xA3, 0x6F, 0xC0, 0x90, 0x26, 0x2F, 0xD5, 0x7F, 0x13, 0x30, 0xC6, 0x6F, 0x94, 0x7F,
    0x5B, 0x25, 0x1E, 0x15, 0xD3, 0xBE, 0xA4, 0x7F, 0x2C, 0x0B, 0x55, 0x5A, 0xAE, 0x01, 0x59, 0x5E,
    0x0B, 0x30, 0x2E, 0x1A, 0x00, 0x2F, 0x4B, 0x43, 0x41, 0x8B, 0x29, 0x2E, 0x71, 0x00, 0x6F, 0x0E,
    0xF7, 0x2F, 0xD5, 0x6F, 0x94, 0x6F, 0x0F, 0x2C, 0xD3, 0x7F, 0xB3, 0x6F, 0xF3, 0x0E, 0x0A, 0x2F,
    0x13, 0x30, 0x03, 0x43, 0x03, 0x30, 0x46, 0x41, 0x80, 0xA1, 0x02, 0x2F, 0x00, 0x2E, 0x03, 0x2C,
    0x03, 0x42, 0x13, 0x30, 0x03, 0x42, 0x41, 0x8B, 0xC3, 0x6F, 0xC1, 0x86, 0x01, 0x89, 0x01, 0x80,
    0xC3, 0xA2, 0xC3, 0x7F, 0xAA, 0x2F, 0x00, 0x2E, 0x03, 0x2D, 0xDB, 0x7F, 0x37, 0x2E, 0x70, 0x00,
    0xD1, 0x6F, 0x40, 0x90, 0x40, 0x30, 0x02, 0x2F, 0x21, 0x2E, 0x5F, 0xF0, 0x05, 0x2D, 0x03, 0x2E,
    0x90, 0x00, 0x08, 0x0A, 0x21, 0x2E, 0x90, 0x00, 0xEB, 0x6F, 0xF1, 0x30, 0x01, 0x2E, 0x71, 0x00,
    0xC0, 0x2E, 0x60, 0x5F, 0x01, 0x08, 0x03, 0x2E, 0x92, 0x00, 0x41, 0x80, 0x40, 0x50, 0x00, 0x40,
    0x03, 0xBD, 0x2F, 0xB9, 0x80, 0xB2, 0xFB, 0x7F, 0x35, 0x2F, 0x05, 0x2E, 0x78, 0x00, 0x80, 0x90,
    0x05, 0x2F, 0x03, 0x30, 0x12, 0x30, 0x25, 0x2E, 0x78, 0x00, 0x27, 0x2E, 0x79, 0x00, 0x42, 0x86,
    0x42, 0x40, 0xC1, 0x40, 0xA1, 0xBD, 0x04, 0xBD, 0x24, 0xB9, 0xE2, 0x7F, 0x94, 0xBC, 0x14, 0xB8,
    0xC0, 0x7F, 0xB1, 0xB9, 0x1F, 0x52, 0xD3, 0x7F, 0x98, 0x2E, 0x48, 0xB0, 0xE1, 0x6F, 0xD2, 0x6F,
    0x51, 0x28, 0x41, 0x0F, 0x11, 0x30, 0x0C, 0x2F, 0x42, 0x0E, 0x07, 0x2E, 0x79, 0x00, 0x19, 0x28,
    0x04, 0x2F, 0xC0, 0xA6, 0x08, 0x2F, 0x21, 0x2E, 0x79, 0x00, 0x06, 0x2D, 0x21, 0x2E, 0x79, 0x00,
    0x03, 0x2D, 0x00, 0x30, 0x21, 0x2E, 0x79, 0x00, 0x05, 0x2E, 0x79, 0x00, 0xC0, 0x6F, 0x50, 0x0F,
    0x00, 0x30, 0x04, 0x2C, 0x08, 0x22, 0x00, 0x30, 0x21, 0x2E, 0x78, 0x00, 0x00, 0x90, 0x80, 0x30,
    0x02, 0x2F, 0x21, 0x2E, 0x5F, 0xF0, 0x05, 0x2D, 0x03, 0x2E, 0x90, 0x00, 0x08, 0x0A, 0x21, 0x2E,
    0x90, 0x00, 0xFB, 0x6F, 0xC0, 0x5F, 0xB8, 0x2E, 0xC0, 0x2E, 0x21, 0x2E, 0x93, 0x00, 0x03, 0x2E,
    0x93, 0x00, 0x55, 0x40, 0x44, 0x40, 0x42, 0xBD, 0xAF, 0xB9, 0xC1, 0xBC, 0x54, 0xBF, 0x1F, 0xB9,
    0xEF, 0xBB, 0xCF, 0xB8, 0x9A, 0x0B, 0x10, 0x50, 0xC0, 0xB3, 0xB1, 0x0B, 0x5B, 0x2F, 0x80, 0xB3,
    0x59, 0x2F, 0x0F, 0x2E, 0x7A, 0x00, 0x01, 0x8C, 0xC0, 0xB3, 0x45, 0x2F, 0xC3, 0xBF, 0xC0, 0xB2,
    0xD5, 0xBE, 0x55, 0xBA, 0xF3, 0xB9, 0x07, 0x30, 0x05, 0x30, 0x09, 0x2F, 0xF0, 0x7F, 0x00, 0x2E,
    0x00, 0x40, 0x0B, 0x2E, 0x7C, 0x00, 0x05, 0x04, 0x00, 0xA8, 0x78, 0x05, 0x45, 0x23, 0xF0, 0x6F,
    0x80, 0xB2, 0x07, 0x2F, 0x82, 0x41, 0x0F, 0x2E, 0x7D, 0x00, 0x97, 0x04, 0x07, 0x30, 0x80, 0xA8,
    0xFA, 0x05, 0xD7, 0x23, 0x40, 0xB2, 0x01, 0x30, 0x02, 0x30, 0x0A, 0x2F, 0x02, 0x84, 0xF7, 0x7F,
    0x00, 0x2E, 0x82, 0x40, 0x0F, 0x2E, 0x7E, 0x00, 0x97, 0x04, 0x80, 0xA8, 0xCA, 0x05, 0x97, 0x22,
    0xF7, 0x6F, 0xEC, 0x0F, 0x03, 0x2F, 0xFC, 0x0F, 0x01, 0x2F, 0x54, 0x0E, 0x02, 0x2F, 0x23, 0x2E,
    0x7B, 0x00, 0x08, 0x2D, 0x09, 0x2E, 0x7B, 0x00, 0x12, 0x30, 0x22, 0x29, 0x63, 0x0F, 0x29, 0x2E,
    0x7B, 0x00, 0x51, 0x22, 0x00, 0x40, 0x21, 0x2E, 0x7C, 0x00, 0x5B, 0x50, 0x92, 0x41, 0x12, 0x42,
    0x00, 0x2E, 0x82, 0x41, 0x13, 0x2C, 0x02, 0x42, 0x11, 0x30, 0x23, 0x2E, 0x7A, 0x00, 0x00, 0x40,
    0x21, 0x2E, 0x7C, 0x00, 0x5B, 0x50, 0x91, 0x41, 0x11, 0x42, 0x01, 0x30, 0x82, 0x41, 0x02, 0x42,
    0x23, 0x2E, 0x7B, 0x00, 0x03, 0x2D, 0x01, 0x30, 0x23, 0x2E, 0x7A, 0x00, 0x40, 0x90, 0x00, 0x32,
    0x02, 0x2F, 0x21, 0x2E, 0x5F, 0xF0, 0x05, 0x2D, 0x03, 0x2E, 0x90, 0x00, 0x08, 0x0A, 0x21, 0x2E,
    0x90, 0x00, 0xF0, 0x5F, 0xB8, 0x2E, 0x01, 0x25, 0x20, 0x50, 0xE0, 0x7F, 0xFB, 0x7F, 0x20, 0x25,
    0x5D, 0x52, 0x98, 0x2E, 0x5D, 0xB0, 0xE1, 0x6F, 0x44, 0x80, 0x3E, 0x84, 0x00, 0x40, 0xA3, 0x40,
    0xA4, 0x40, 0x24, 0x18, 0x85, 0x40, 0x46, 0x25, 0xB7, 0x25, 0x2D, 0x18, 0x83, 0x84, 0x34, 0x01,
    0x5B, 0x25, 0x7D, 0x03, 0x1B, 0x18, 0xCA, 0xB9, 0xD6, 0xBE, 0xEB, 0x0A, 0x82, 0x40, 0x57, 0x25,
    0x56, 0x18, 0x04, 0xBC, 0xEA, 0x18, 0x98, 0x00, 0x46, 0xBE, 0x57, 0x0E, 0x0E, 0x2F, 0x57, 0x1A,
    0x01, 0x2F, 0x66, 0x0E, 0x0A, 0x2F, 0xB8, 0x00, 0x53, 0x0E, 0x00, 0x30, 0x07, 0x2F, 0x53, 0x1A,
    0x01, 0x2F, 0x74, 0x0E, 0x03, 0x2F, 0x45, 0x80, 0x02, 0x2C, 0x00, 0x40, 0x10, 0x30, 0xFB, 0x6F,
    0xE0, 0x5F, 0xB8, 0x2E, 0x41, 0xB2, 0x01, 0x2F, 0x00, 0x2E, 0x02, 0x2D, 0x23, 0x2C, 0x00, 0x30,
    0x42, 0xB2, 0x01, 0x2F, 0x43, 0x90, 0x36, 0x2F, 0x42, 0x25, 0x7E, 0x82, 0x15, 0x41, 0xD7, 0x40,
    0x10, 0x41, 0xD6, 0x40, 0xEF, 0x05, 0x46, 0x05, 0x00, 0x30, 0x04, 0x41, 0xC0, 0xA9, 0x87, 0x05,
    0xC3, 0x40, 0xBE, 0x23, 0xE3, 0x04, 0x40, 0xA9, 0x05, 0x05, 0x2C, 0x23, 0x5F, 0x5E, 0x79, 0x01,
    0xC0, 0xA8, 0x43, 0x04, 0x45, 0x41, 0x59, 0x22, 0x75, 0x0F, 0x1A, 0x2F, 0x65, 0x0F, 0x18, 0x2F,
    0x4D, 0x0F, 0x16, 0x2F, 0x93, 0x40, 0xC0, 0xA8, 0x03, 0x05, 0x91, 0x40, 0xDC, 0x22, 0x40, 0xA8,
    0x01, 0x05, 0x82, 0x40, 0x4C, 0x22, 0x80, 0xA8, 0x02, 0x05, 0x94, 0x22, 0x61, 0x58, 0x5C, 0x0F,
    0x05, 0x2F, 0x61, 0x56, 0x4B, 0x0F, 0x02, 0x2F, 0x61, 0x52, 0xD1, 0x0E, 0x05, 0x2F, 0x10, 0x30,
    0xB8, 0x2E, 0x10, 0x30, 0xB8, 0x2E, 0x00, 0x30, 0xB8, 0x2E, 0xB8, 0x2E, 0xC0, 0x2E, 0x21, 0x2E,
    0x94, 0x00, 0x07, 0x2E, 0x94, 0x00, 0xC0, 0x40, 0x0F, 0xBD, 0x70, 0x50, 0x2F, 0xB9, 0xF1, 0x7F,
    0x80, 0xB2, 0xEB, 0x7F, 0x90, 0x2E, 0x85, 0xB5, 0x52, 0x40, 0xC1, 0x88, 0x8A, 0xBE, 0xDE, 0xB9,
    0xD1, 0x7F, 0x8C, 0xBC, 0x07, 0x41, 0xC3, 0x7F, 0x9E, 0xB9, 0x63, 0x58, 0x23, 0x01, 0x84, 0xBD,
    0x75, 0xBF, 0x01, 0x30, 0xBA, 0xBB, 0xB2, 0x7F, 0x80, 0xA8, 0x4A, 0x05, 0xE5, 0xB9, 0x95, 0x22,
    0x04, 0x41, 0xA7, 0x7F, 0x22, 0x2A, 0x53, 0x05, 0x8E, 0x16, 0x17, 0x30, 0x97, 0x08, 0xB2, 0x01,
    0xB6, 0x25, 0x25, 0x2A, 0xD2, 0x6F, 0x72, 0x25, 0x5B, 0x25, 0xD2, 0x41, 0xD1, 0xB6, 0xEB, 0x28,
    0x97, 0x7F, 0x4A, 0x05, 0x80, 0xA8, 0xC7, 0x41, 0x55, 0x23, 0xC0, 0xA9, 0x4F, 0x04, 0x79, 0x22,
    0xCE, 0x17, 0x14, 0x30, 0xFC, 0x09, 0xF7, 0x01, 0x0E, 0xBF, 0xF1, 0xB7, 0x6F, 0xBB, 0x01, 0x2E,
    0x87, 0x00, 0xAF, 0x0F, 0x03, 0x2F, 0xB4, 0x6F, 0x00, 0xAD, 0x14, 0x30, 0x1E, 0x2F, 0xAF, 0x0F,
    0x02, 0x2F, 0xB7, 0x6F, 0xC0, 0xA1, 0x15, 0x2F, 0xAB, 0x0E, 0x01, 0x2F, 0x80, 0xA0, 0x0C, 0x2F,
    0xAB, 0x0E, 0x33, 0x30, 0x01, 0x2F, 0x80, 0xAC, 0x03, 0x2F, 0x83, 0x08, 0x25, 0x2E, 0x88, 0x00,
    0x10, 0x2D, 0x02, 0x30, 0x25, 0x2E, 0x88, 0x00, 0x0C, 0x2D, 0x22, 0x30, 0x25, 0x2E, 0x88, 0x00,
    0x08, 0x2C, 0x33, 0x30, 0x33, 0x30, 0x27, 0x2E, 0x88, 0x00, 0x03, 0x2D, 0x29, 0x2E, 0x88, 0x00,
    0x33, 0x30, 0x80, 0xB3, 0xF2, 0x6F, 0x11, 0x2F, 0x69, 0x5A, 0x4D, 0x0F, 0x03, 0x2F, 0x82, 0xB8,
    0x23, 0x2E, 0x89, 0x00, 0x0B, 0x2D, 0x82, 0x82, 0x00, 0x2E, 0x41, 0x40, 0x40, 0xAC, 0x02, 0x2F,
    0x29, 0x2E, 0x89, 0x00, 0x03, 0x2D, 0x01, 0x30, 0x23, 0x2E, 0x89, 0x00, 0x03, 0x2E, 0x88, 0x00,
    0x4B, 0x08, 0x09, 0x2E, 0x89, 0x00, 0xC2, 0xBD, 0x0B, 0x0B, 0x04, 0x1A, 0x29, 0x2E, 0x8A, 0x00,
    0x90, 0x6F, 0x05, 0x30, 0x39, 0x2F, 0xC1, 0x6F, 0x40, 0xA6, 0x36, 0x2F, 0xC1, 0x6F, 0x43, 0x90,
    0x03, 0x30, 0x0F, 0x2F, 0x0F, 0x2E, 0x8F, 0x00, 0x15, 0x30, 0xBD, 0x29, 0x0F, 0x2E, 0x8E, 0x00,
    0x3C, 0x1A, 0x2D, 0x2E, 0x8F, 0x00, 0x01, 0x2F, 0x27, 0x2E, 0x8F, 0x00, 0x09, 0x2E, 0x8F, 0x00,
    0x05, 0xA3, 0x6B, 0x23, 0x40, 0x91, 0x06, 0x2F, 0x65, 0x56, 0x98, 0x2E, 0x52, 0xB4, 0x50, 0x25,
    0xF2, 0x6F, 0x90, 0x6F, 0x03, 0x30, 0x40, 0x91, 0x17, 0x2F, 0x67, 0x52, 0x82, 0x40, 0x52, 0x42,
    0x00, 0x2E, 0xD4, 0x6F, 0xA2, 0x6F, 0x04, 0x41, 0x54, 0x42, 0x00, 0x2E, 0x00, 0x40, 0x50, 0x42,
    0x52, 0x42, 0x43, 0x42, 0x7C, 0x82, 0xF1, 0x7F, 0x98, 0x2E, 0x1B, 0xB4, 0xF2, 0x6F, 0x85, 0x84,
    0x01, 0xB2, 0x11, 0x30, 0x03, 0x30, 0x80, 0x42, 0x4B, 0x23, 0x03, 0x2E, 0x8A, 0x00, 0x23, 0x2E,
    0x8E, 0x00, 0x92, 0x6F, 0xBE, 0x84, 0x41, 0x91, 0x03, 0x2E, 0x87, 0x00, 0x01, 0x2F, 0x23, 0x2E,
    0x8A, 0x00, 0x01, 0x2E, 0x8A, 0x00, 0x41, 0x1A, 0x01, 0x31, 0x02, 0x2F, 0x23, 0x2E, 0x5F, 0xF0,
    0x05, 0x2D, 0x01, 0x2E, 0x90, 0x00, 0x41, 0x0A, 0x23, 0x2E, 0x90, 0x00, 0x65, 0x52, 0x90, 0x40,
    0x50, 0x42, 0x00, 0x2E, 0x90, 0x40, 0x50, 0x42, 0x00, 0x2E, 0x82, 0x40, 0x42, 0x42, 0x00, 0x2E,
    0x05, 0x2E, 0x8A, 0x00, 0x25, 0x2E, 0x87, 0x00, 0x03, 0x2D, 0x02, 0x31, 0x25, 0x2E, 0x5F, 0xF0,
    0xEB, 0x6F, 0x90, 0x5F, 0x01, 0x2E, 0x8A, 0x00, 0xB8, 0x2E, 0x60, 0x50, 0x03, 0x2E, 0x0E, 0x01,
    0xE0, 0x7F, 0xF1, 0x7F, 0xDB, 0x7F, 0x30, 0x30, 0x6B, 0x54, 0x0A, 0x1A, 0x28, 0x2F, 0x1A, 0x25,
    0x7A, 0x82, 0x00, 0x30, 0x43, 0x30, 0x32, 0x30, 0x05, 0x30, 0x04, 0x30, 0xF6, 0x6F, 0xF2, 0x09,
    0xFC, 0x13, 0xC2, 0xAB, 0xB3, 0x09, 0xEF, 0x23, 0x80, 0xB3, 0xE6, 0x6F, 0xB7, 0x01, 0x00, 0x2E,
    0x8B, 0x41, 0x4B, 0x42, 0x03, 0x2F, 0x46, 0x40, 0x86, 0x17, 0x81, 0x8D, 0x46, 0x42, 0x41, 0x8B,
    0x23, 0xBD, 0xB3, 0xBD, 0x03, 0x89, 0x41, 0x82, 0x07, 0x0C, 0x43, 0xA3, 0xE6, 0x2F, 0xE1, 0x6F,
    0xA2, 0x6F, 0x52, 0x42, 0x00, 0x2E, 0xB2, 0x6F, 0x52, 0x42, 0x00, 0x2E, 0xC2, 0x6F, 0x42, 0x42,
    0x03, 0xB2, 0x06, 0x2F, 0x01, 0x2E, 0x59, 0xF0, 0x01, 0x32, 0x01, 0x0A, 0x21, 0x2E, 0x59, 0xF0,
    0x06, 0x2D, 0x01, 0x2E, 0x59, 0xF0, 0xF1, 0x3D, 0x01, 0x08, 0x21, 0x2E, 0x59, 0xF0, 0xDB, 0x6F,
    0xA0, 0x5F, 0xB8, 0x2E, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00,
    0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00, 0x80, 0x2E, 0x18, 0x00
};

static const U1 *   u1p_s_GYROINFO_TOP_ADR  = u1_sp_GYRO_CONFIG;



static const U4 GYRODEV_CYCCHK_POLING = (U4)(10U / GYRODEV_TASK_TIME);         /* Gyro Device Poling Check Time t6 : 10ms */

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

static const ST_REG_WRI_REQ GYRODEV_GSENSDATA_RD[GYRODEV_GSENSDATA_RD_WRINUM] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0},
    {        1,         1,         0},
    {        2,         1,         0},
    {        3,         1,         0}
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_BW[GYRODEV_I2C_RWC_BYTE3] = {
    (U1)GYRODEV_GYRO_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x10U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_RANGE[GYRODEV_I2C_RWC_BYTE3] = {
    (U1)GYRODEV_GYRO_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0FU,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_TEST[GYRODEV_I2C_RWC_BYTE3] = {
    (U1)GYRODEV_GYRO_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3CU,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_TEST_RD[GYRODEV_I2C_RWC_BYTE2] = {
    (U1)GYRODEV_GYRO_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3CU     /* Write Address */
};

U1 u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_READ[GYRODEV_I2C_RWC_BYTE2];

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_WDG[GYRODEV_I2C_RWC_BYTE3] = {
    (U1)GYRODEV_GYRO_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x34U,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_MODE_NML[GYRODEV_I2C_RWC_BYTE3] = {
    (U1)GYRODEV_GYRO_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x11U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_MODE_SPD[GYRODEV_I2C_RWC_BYTE3] = {
    (U1)GYRODEV_GYRO_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x11U,    /* Write Address */
    (U1)0x80U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_MODE_RD[GYRODEV_I2C_RWC_BYTE2] = {
    (U1)GYRODEV_GYRO_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x11U     /* Write Address */
};

U1 u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_MODE_READ[GYRODEV_I2C_RWC_BYTE2];

const U1 u1_sp_GYRODEV_GYRODATA_RD_PDU1[GYRODEV_I2C_RWC_BYTE2] = {
    (U1)GYRODEV_GYRO_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x02U     /* Write Address */
};

U1 u1_sp_GYRODEV_GYRODATA_RD_PDU2[GYRODEV_I2C_RWC_BYTE8];

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_SEN1_BW[GYRODEV_I2C_RWC_BYTE3] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0xA8U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_SEN1_RANGE[GYRODEV_I2C_RWC_BYTE3] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_SEN2_BW[GYRODEV_I2C_RWC_BYTE3] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0xACU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_SEN2_RANGE[GYRODEV_I2C_RWC_BYTE3] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_WDG[GYRODEV_I2C_RWC_BYTE3] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x70U,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_MODE_NML[GYRODEV_I2C_RWC_BYTE3] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7DU,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_MODE_SPD[GYRODEV_I2C_RWC_BYTE3] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_PLSTEST[GYRODEV_I2C_RWC_BYTE3] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6DU,    /* Write Address */
    (U1)0x0DU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_MNSTEST[GYRODEV_I2C_RWC_BYTE3] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6DU,    /* Write Address */
    (U1)0x09U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_DISTEST[GYRODEV_I2C_RWC_BYTE3] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_XYZ[GYRODEV_I2C_RWC_BYTE2] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x12U     /* Write Address */
};

U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_READ_XYZ[GYRODEV_I2C_RWC_BYTE7];

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_TEMP[GYRODEV_I2C_RWC_BYTE2] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x22U     /* Write Address */
};

U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_READ_TEMP[GYRODEV_I2C_RWC_BYTE2];

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_PWRCONF_ON[GYRODEV_I2C_RWC_BYTE3] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_PWRCONF_OFF[GYRODEV_I2C_RWC_BYTE3] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7CU,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INTCONF_ON[GYRODEV_I2C_RWC_BYTE3] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x59U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INTCONF_OFF[GYRODEV_I2C_RWC_BYTE3] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x59U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INTCONF_RD[GYRODEV_I2C_RWC_BYTE2] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2AU     /* Write Address */
};

U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INTCONF_DT[GYRODEV_I2C_RWC_BYTE2];

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_SOFTRESE[GYRODEV_I2C_RWC_BYTE3] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7EU,    /* Write Address */
    (U1)0xB6U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INT_ANYMOT_TH_LSB[GYRODEV_I2C_RWC_BYTE3] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x5BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INT_ANYMOT_TH_MSB[GYRODEV_I2C_RWC_BYTE3] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x5CU,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INT_ANYMOT_TH_DAT[GYRODEV_I2C_RWC_BYTE4] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,
    (U1)0x5EU,    /* Write Address   */
    (U1)0xFFU,    /* Write Data 0x5E */
    (U1)0x03U     /* Write Data 0x5F */
};


const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INT_ANYMOT_EN_LSB[GYRODEV_I2C_RWC_BYTE3] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x5BU,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INT_ANYMOT_EN_MSB[GYRODEV_I2C_RWC_BYTE3] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x5CU,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INT_ANYMOT_EN_DAT[GYRODEV_I2C_RWC_BYTE4] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,
    (U1)0x5EU,    /* Write Address   */
    (U1)0x01U,    /* Write Data 0x5E */
    (U1)0xE0U     /* Write Data 0x5F */
};


const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INT2_IO_CONF[GYRODEV_I2C_RWC_BYTE3] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x54U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INT_LATCH[GYRODEV_I2C_RWC_BYTE3] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x55U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INT2_MAP[GYRODEV_I2C_RWC_BYTE3] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x57U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_SEN1_BW_INPRM[GYRODEV_I2C_RWC_BYTE3] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0xACU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_CFG1[GYRODEV_I2C_RWC_BYTE3] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x5BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_CFG2[GYRODEV_I2C_RWC_BYTE3];

U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_DATA[GYRODEV_I2C_RWC_BYTE34];

const U1 u1_sp_GYRODEV_GSENSDATA_RD_PDU1[GYRODEV_I2C_RWC_BYTE2] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x12U     /* Write Address */
};

U1 u1_sp_GYRODEV_GSENSDATA_RD_PDU2[GYRODEV_I2C_RWC_BYTE7];

const U1 u1_sp_GYRODEV_GSENSDATA_RD_PDU3[GYRODEV_I2C_RWC_BYTE2] = {
    (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x22U     /* Write Address */
};

U1 u1_sp_GYRODEV_GSENSDATA_RD_PDU4[GYRODEV_I2C_RWC_BYTE3];

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

const U1 u1_sp_GYRODEV_INT_ANYMOT_RD_PDU1[GYRODEV_I2C_RWC_BYTE2] = {
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

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_GYR_SETUP[2] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_BW[0],
        (U4)0x60040003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_RANGE[0],
        (U4)0x60080003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_GYR_TEST[1] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_TEST[0],
        (U4)0x600C0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_GYR_TEST_RD[2] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_TEST_RD[0],
        (U4)0x60100002U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_READ[0],
        (U4)0x60140002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_GYR_WDG[1] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_WDG[0],
        (U4)0x60180003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_GYR_MODE_ON[1] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_MODE_NML[0],
        (U4)0x601C0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_GYR_MODE_OFF[1] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_MODE_SPD[0],
        (U4)0x60200003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_GYR_MODE_RD[2] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_MODE_RD[0],
        (U4)0x60240002U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_MODE_READ[0],
        (U4)0x60280002U
    }
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

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_ACC_SEN1_SETUP[2] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_SEN1_BW[0],
        (U4)0x702C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_SEN1_RANGE[0],
        (U4)0x70300003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_ACC_SEN2_SETUP[2] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_SEN2_BW[0],
        (U4)0x70340003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_SEN2_RANGE[0],
        (U4)0x70380003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_ACC_WDG[1] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_WDG[0],
        (U4)0x703C0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_ACC_MODE_ON[1] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_MODE_NML[0],
        (U4)0x70400003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_ACC_MODE_OFF[1] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_MODE_SPD[0],
        (U4)0x70440003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_ACC_PLSTEST[1] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_PLSTEST[0],
        (U4)0x70480003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_ACC_MNSTEST[1] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_MNSTEST[0],
        (U4)0x704C0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_ACC_DISTEST[1] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_DISTEST[0],
        (U4)0x70500003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_GYR_XYZ[2] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_XYZ[0],
        (U4)0x70540002U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_READ_XYZ[0],
        (U4)0x70580007U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_GYR_TEMP[2] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_TEMP[0],
        (U4)0x705C0002U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_READ_TEMP[0],
        (U4)0x70600003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_ACC_PWRCONF_ON[1] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_PWRCONF_ON[0],
        (U4)0x70640003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_ACC_PWRCONF_OFF[1] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_PWRCONF_OFF[0],
        (U4)0x70680003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_ACC_INTCONF_ON[1] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INTCONF_ON[0],
        (U4)0x706C0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_ACC_INTCONF_OFF[1] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INTCONF_OFF[0],
        (U4)0x70700003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_ACC_INTCONF_READ[2] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INTCONF_RD[0],
        (U4)0x70740002U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INTCONF_DT[0],
        (U4)0x70780002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_ACC_SOFTRESET[1] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_SOFTRESE[0],
        (U4)0x707C0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_INTSET_ANYMOT_TH[3] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INT_ANYMOT_TH_LSB[0],
        (U4)0x70800003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INT_ANYMOT_TH_MSB[0],
        (U4)0x70840003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INT_ANYMOT_TH_DAT[0],
        (U4)0x70880004U
    },
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_INTSET_ANYMOT_EN[3] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INT_ANYMOT_EN_LSB[0],
        (U4)0x708C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INT_ANYMOT_EN_MSB[0],
        (U4)0x70900003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INT_ANYMOT_EN_DAT[0],
        (U4)0x70940004U
    },
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_INTSET_OTH[3] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INT2_IO_CONF[0],
        (U4)0x70980003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INT_LATCH[0],
        (U4)0x709C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INT2_MAP[0],
        (U4)0x70A00003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_ACC_SEN1_BW_INPRM[1] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_SEN1_BW_INPRM[0],
        (U4)0x70A40003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_ACC_CFG1[1] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_CFG1[0],
        (U4)0x70A80003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_ACC_CFG2[1] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_CFG2[0],
        (U4)0x70AC0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_ACC_DATA[1] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_DATA[0],
        (U4)0x70B00022U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GYRODEV_GSENSDATA_RD_TBL[4] = {
    {
        (U1 *)&u1_sp_GYRODEV_GSENSDATA_RD_PDU1[0],
        (U4)0x70040002U
    },
    {
        (U1 *)&u1_sp_GYRODEV_GSENSDATA_RD_PDU2[0],
        (U4)0x70080007U
    },
    {
        (U1 *)&u1_sp_GYRODEV_GSENSDATA_RD_PDU3[0],
        (U4)0x700C0002U
    },
    {
        (U1 *)&u1_sp_GYRODEV_GSENSDATA_RD_PDU4[0],
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
/* void            vd_g_GyroDev_BonInit(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_GyroDev_BonInit(void)
{
    /* I2C書込み/読出し用バッファクリア */
    vd_s_GyroSysPwrInit();

    /* 制御管理バッファ初期化 */
    st_s_gyro_ctrl.u1_mod       = (U1)GYRO_MODE_MAX;
    st_s_gyro_ctrl.u1_event     = (U1)GYRO_EVENT_MAX;
    st_s_gyro_ctrl.u1_dev_mode  = (U1)GYRO_DEV_MODE_SUSPEND;

    /* 各種カウンタクリア */
    u1_s_errcnt_l               = (U1)0U;
    u1_s_errcnt_j               = (U1)0U;
    u1_s_cnt_shutdn             = (U1)0U;
    u1_s_cnt_g_read             = (U1)0U;
    u2_s_cnt_diff_verif         = (U2)0U;
    u1_s_gyro_uploadcfg_rtrycnt = (U1)0U;

    /* その他バッファを初期化 */
    dl_s_gyro_v33perion_sts     = (Dio_LevelType)GYRO_DIO_LOW;
    u1_s_gyro_v33OffFlg         = (U1)FALSE;
    dl_s_gyro_budet_sts         = (Dio_LevelType)GYRO_DIO_LOW;
    u1_s_gyro_sysoffflg         = (U1)FALSE;
    vd_s_GyroDevMemset(&st_s_gyro_accdat_pls, (U1)0U, (U4)sizeof(st_s_gyro_accdat_pls));
    vd_s_GyroDevMemset(&st_s_gyro_accdat_mns, (U1)0U, (U4)sizeof(st_s_gyro_accdat_mns));
    vd_s_GyroDevMemset(&st_s_gyro_cfgmng,     (U1)0U, (U4)sizeof(st_s_gyro_cfgmng));
    vd_s_GyroDevMemset(&st_s_gyro_accdat,     (U1)0U, (U4)sizeof(st_s_gyro_accdat));
    u1_s_gyrodev_gsensbkup_flg = (U1)FALSE;
    u1_s_gyrodev_gsensbkup_done_flg = (U1)FALSE;

    /* すべてのタイマを初期化 */
    u4_s_gyro_acktime           = (U4)0U;
    u4_s_gyro_linktim           = (U4)0U;

    /* シーケンス管理バッファー初期化 */
    vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);

    /* ジャイロ状態を初期化 */
    vd_s_GyroDevCtlMngModSet((U1)GYRO_MODE_UNINIT);

    /* ジャイロ状態管理の イベント・ハンドラを呼び出し */
    vd_s_GyroDevEventGo((U1)GYRO_EVENT_TASKSTUP);


    u1_s_gyrodev_state = (U1)GYRODEV_SEQ_IDLE;
    vd_g_Rim_WriteU1((U2)RIMID_U1_GYRO_STS, u1_s_gyrodev_state);


    u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP0;
    vd_g_Rim_WriteU1((U2)RIMID_U1_GYRO_CYCCHK_STS, u1_s_gyrodev_cycchk_sts);
    u4_s_gyrodev_cycchk_timer = (U4)0;
    vd_g_Rim_WriteU4((U2)RIMID_U4_GYRO_CYCCHK_TIMER, u4_s_gyrodev_cycchk_timer);
    u2_s_gyrodev_gyro_max_err_cnt = (U2)0;
    vd_g_Rim_WriteU2((U2)RIMID_U2_GYRO_MAX_ERR, u2_s_gyrodev_gyro_max_err_cnt);
    u2_s_gyrodev_gyro_min_err_cnt = (U2)0;
    vd_g_Rim_WriteU2((U2)RIMID_U2_GYRO_MIN_ERR, u2_s_gyrodev_gyro_min_err_cnt);
    u1_s_gyrodev_gyro_rst_cnt = (U1)0;
    vd_g_Rim_WriteU1((U2)RIMID_U1_GYRO_RST, u1_s_gyrodev_gyro_rst_cnt);
    u2_s_gyrodev_gsens_max_err_cnt = (U2)0;
    vd_g_Rim_WriteU2((U2)RIMID_U2_GSENS_MAX_ERR, u2_s_gyrodev_gsens_max_err_cnt);
    u2_s_gyrodev_gsens_min_err_cnt = (U2)0;
    vd_g_Rim_WriteU2((U2)RIMID_U2_GSENS_MIN_ERR, u2_s_gyrodev_gsens_min_err_cnt);
    u1_s_gyrodev_gsens_rst_cnt = (U1)0;
    vd_g_Rim_WriteU1((U2)RIMID_U1_GSENS_RST, u1_s_gyrodev_gsens_rst_cnt);

    u2_s_gyrodev_regstep = (U2)0;
    u4_s_gyrodev_i2c_ack_wait_time = (U4)0;
    u2_s_gyrodev_reg_btwn_time = (U2)0xFFFFU;

    u1_s_gyrodev_gyro_read_complete_flag = (U1)FALSE;
    u1_s_gyrodev_gsens_read_complete_flag = (U1)FALSE;

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

    u1_s_gyrodev_gyro_dtcrec_a_flag = (U1)FALSE;
    u1_s_gyrodev_gsens_dtcrec_a_flag = (U1)FALSE;

    u1_s_gyrodev_notifcondset_sts = (U1)GYRODEV_NOTIFCONDSET_STEP0;
    u1_s_gyrodev_oscmd_notifcond_rcv_flag = (U1)FALSE;
    u1_s_gyrodev_oscmd_notifcond_bak_flag = (U1)FALSE;
    vd_s_GyroDev_Memset(&st_gyrodev_notifcond_setreq, (U1)0U, sizeof(st_gyrodev_notifcond_setreq));
    vd_s_GyroDev_Memset(&st_gyrodev_notifcond_setbak, (U1)0U, sizeof(st_gyrodev_notifcond_setbak));
    vd_g_Rim_WriteOther((U2)RIMID_OTR_GYRODEV_NOTIFCOND,sizeof(st_gyrodev_notifcond_setbak), (const U1 *)(const void *)&st_gyrodev_notifcond_setbak);
    u1_s_gyrodev_oscmd_notifcond_read_flag = (U1)FALSE;
    vd_s_GyroDev_Memset(&st_gyrodev_notifcond_readreq, (U1)0U, sizeof(st_gyrodev_notifcond_readreq));

    u1_s_gyrodev_ctrloutset_sts = (U1)GYRODEV_CTRLOUTSET_STEP0;
    u1_s_gyrodev_oscmd_outctl_rcv_flag = (U1)FALSE;
    u1_s_gyrodev_oscmd_outctl_bak_flag = (U1)FALSE;
    vd_s_GyroDev_Memset(&st_gyrodev_ctrlout_setreq, (U1)0U, sizeof(st_gyrodev_ctrlout_setreq));
    vd_s_GyroDev_Memset(&st_gyrodev_ctrlout_setbak, (U1)0U, sizeof(st_gyrodev_ctrlout_setbak));
    vd_g_Rim_WriteOther((U2)RIMID_OTR_GYRODEV_CTRLOUT, sizeof(st_gyrodev_ctrlout_setbak), (const U1 *)(const void *)&st_gyrodev_ctrlout_setbak);

}

/*===================================================================================================================================*/
/* void            vd_g_GyroDev_WkupInit(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_GyroDev_WkupInit(void)
{
    U1 u1_t_rim_sts;
    U1 u1_t_rim_data;
    U2 u2_t_rim_data;
    U4 u4_t_rim_data;
    ST_GYRODEV_NOTIFCOND_SETDATA st_t_rim_notifcond_data;
    ST_GYRODEV_CTRLOUT_SETDATA   st_t_rim_ctrlout_data;

    /* I2C書込み/読出し用バッファクリア */
    vd_s_GyroSysPwrInit();

    /* 制御管理バッファ初期化 */
    st_s_gyro_ctrl.u1_mod       = (U1)GYRO_MODE_MAX;
    st_s_gyro_ctrl.u1_event     = (U1)GYRO_EVENT_MAX;
    st_s_gyro_ctrl.u1_dev_mode  = (U1)GYRO_DEV_MODE_SUSPEND;

    /* 各種カウンタクリア */
    u1_s_errcnt_l               = (U1)0U;
    u1_s_errcnt_j               = (U1)0U;
    u1_s_cnt_shutdn             = (U1)0U;
    u1_s_cnt_g_read             = (U1)0U;
    u2_s_cnt_diff_verif         = (U2)0U;
    u1_s_gyro_uploadcfg_rtrycnt = (U1)0U;

    /* その他バッファを初期化 */
    dl_s_gyro_v33perion_sts     = (Dio_LevelType)GYRO_DIO_LOW;
    u1_s_gyro_v33OffFlg         = (U1)FALSE;
    dl_s_gyro_budet_sts         = (Dio_LevelType)GYRO_DIO_LOW;
    u1_s_gyro_sysoffflg         = (U1)FALSE;
    vd_s_GyroDevMemset(&st_s_gyro_accdat_pls, (U1)0U, (U4)sizeof(st_s_gyro_accdat_pls));
    vd_s_GyroDevMemset(&st_s_gyro_accdat_mns, (U1)0U, (U4)sizeof(st_s_gyro_accdat_mns));
    vd_s_GyroDevMemset(&st_s_gyro_cfgmng,     (U1)0U, (U4)sizeof(st_s_gyro_cfgmng));
    vd_s_GyroDevMemset(&st_s_gyro_accdat,     (U1)0U, (U4)sizeof(st_s_gyro_accdat));
    u1_s_gyrodev_gsensbkup_flg = (U1)FALSE;
    u1_s_gyrodev_gsensbkup_done_flg = (U1)FALSE;

    /* すべてのタイマを初期化 */
    u4_s_gyro_acktime           = (U4)0U;
    u4_s_gyro_linktim           = (U4)0U;

    /* シーケンス管理バッファー初期化 */
    vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);

    /* ジャイロ状態を初期化 */
    vd_s_GyroDevCtlMngModSet((U1)GYRO_MODE_UNINIT);

    /* ジャイロ状態管理の イベント・ハンドラを呼び出し */
    vd_s_GyroDevEventGo((U1)GYRO_EVENT_TASKSTUP);


    u1_t_rim_data = (U1)0U;
    u1_t_rim_sts  = u1_g_Rim_ReadU1withStatus((U2)RIMID_U1_GYRO_STS, &u1_t_rim_data);
    if((u1_t_rim_sts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
        u1_s_gyrodev_state = u1_t_rim_data;
    }

    u1_t_rim_data = (U1)0U;
    u1_t_rim_sts  = u1_g_Rim_ReadU1withStatus((U2)RIMID_U1_GYRO_CYCCHK_STS, &u1_t_rim_data);
    if((u1_t_rim_sts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
        u1_s_gyrodev_cycchk_sts = u1_t_rim_data;
    }
    u4_t_rim_data = (U4)0U;
    u1_t_rim_sts  = u1_g_Rim_ReadU4withStatus((U2)RIMID_U4_GYRO_CYCCHK_TIMER, &u4_t_rim_data);
    if((u1_t_rim_sts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
        u4_s_gyrodev_cycchk_timer = u4_t_rim_data;
    }
    u2_t_rim_data = (U2)0U;
    u1_t_rim_sts  = u1_g_Rim_ReadU2withStatus((U2)RIMID_U2_GYRO_MAX_ERR, &u2_t_rim_data);
    if((u1_t_rim_sts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
        u2_s_gyrodev_gyro_max_err_cnt = u2_t_rim_data;
    }
    u2_t_rim_data = (U2)0U;
    u1_t_rim_sts  = u1_g_Rim_ReadU2withStatus((U2)RIMID_U2_GYRO_MIN_ERR, &u2_t_rim_data);
    if((u1_t_rim_sts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
        u2_s_gyrodev_gyro_min_err_cnt = u2_t_rim_data;
    }
    u1_t_rim_data = (U1)0U;
    u1_t_rim_sts  = u1_g_Rim_ReadU1withStatus((U2)RIMID_U1_GYRO_RST, &u1_t_rim_data);
    if((u1_t_rim_sts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
        u1_s_gyrodev_gyro_rst_cnt = u1_t_rim_data;
    }
    u2_t_rim_data = (U2)0U;
    u1_t_rim_sts  = u1_g_Rim_ReadU2withStatus((U2)RIMID_U2_GSENS_MAX_ERR, &u2_t_rim_data);
    if((u1_t_rim_sts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
        u2_s_gyrodev_gsens_max_err_cnt = u2_t_rim_data;
    }
    u2_t_rim_data = (U2)0U;
    u1_t_rim_sts  = u1_g_Rim_ReadU2withStatus((U2)RIMID_U2_GSENS_MIN_ERR, &u2_t_rim_data);
    if((u1_t_rim_sts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
        u2_s_gyrodev_gsens_min_err_cnt = u2_t_rim_data;
    }
    u1_t_rim_data = (U1)0U;
    u1_t_rim_sts  = u1_g_Rim_ReadU1withStatus((U2)RIMID_U1_GSENS_RST, &u1_t_rim_data);
    if((u1_t_rim_sts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
        u1_s_gyrodev_gsens_rst_cnt = u1_t_rim_data;
    }

    u2_s_gyrodev_regstep = (U2)0;
    u4_s_gyrodev_i2c_ack_wait_time = (U4)0;
    u2_s_gyrodev_reg_btwn_time = (U2)0xFFFFU;

    u1_s_gyrodev_gyro_read_complete_flag = (U1)FALSE;
    u1_s_gyrodev_gsens_read_complete_flag = (U1)FALSE;

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

    u1_s_gyrodev_gyro_dtcrec_a_flag = (U1)FALSE;
    u1_s_gyrodev_gsens_dtcrec_a_flag = (U1)FALSE;

    u1_s_gyrodev_notifcondset_sts = (U1)GYRODEV_NOTIFCONDSET_STEP0;
    u1_s_gyrodev_oscmd_notifcond_rcv_flag = (U1)FALSE;
    u1_s_gyrodev_oscmd_notifcond_bak_flag = (U1)FALSE;
    vd_s_GyroDev_Memset(&st_gyrodev_notifcond_setreq, (U1)0U, sizeof(st_gyrodev_notifcond_setreq));

    st_t_rim_notifcond_data.u1_threshold = 0U;
    st_t_rim_notifcond_data.u1_axis_x    = 0U;
    st_t_rim_notifcond_data.u1_axis_y    = 0U;
    st_t_rim_notifcond_data.u1_axis_z    = 0U;
    st_t_rim_notifcond_data.u1_active    = 0U;
    u1_t_rim_sts = u1_g_Rim_ReadOtherwithStatus((U2)RIMID_OTR_GYRODEV_NOTIFCOND, (U2)sizeof(ST_GYRODEV_NOTIFCOND_SETDATA), (U1 *)&st_t_rim_notifcond_data);
    if((u1_t_rim_sts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
        st_gyrodev_notifcond_setbak = st_t_rim_notifcond_data;
    }

    u1_s_gyrodev_oscmd_notifcond_read_flag = (U1)FALSE;
    vd_s_GyroDev_Memset(&st_gyrodev_notifcond_readreq, (U1)0U, sizeof(st_gyrodev_notifcond_readreq));

    u1_s_gyrodev_ctrloutset_sts = (U1)GYRODEV_CTRLOUTSET_STEP0;
    u1_s_gyrodev_oscmd_outctl_rcv_flag = (U1)FALSE;
    u1_s_gyrodev_oscmd_outctl_bak_flag = (U1)FALSE;
    vd_s_GyroDev_Memset(&st_gyrodev_ctrlout_setreq, (U1)0U, sizeof(st_gyrodev_ctrlout_setreq));

    st_t_rim_ctrlout_data.u1_type    = 0U;
    st_t_rim_ctrlout_data.u1_type_standby    = 0U;
    u1_t_rim_sts = u1_g_Rim_ReadOtherwithStatus((U2)RIMID_OTR_GYRODEV_CTRLOUT, (U2)sizeof(ST_GYRODEV_CTRLOUT_SETDATA), (U1 *)&st_t_rim_ctrlout_data);
    if((u1_t_rim_sts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
        st_gyrodev_ctrlout_setbak = st_t_rim_ctrlout_data;
    }
}

/*===================================================================================================================================*/
/* void            vd_s_GyroSysPwrInit(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void            vd_s_GyroSysPwrInit(void)
{
    U4  mcu_cnt;

    mcu_cnt = (U4)0U;
    /*  データリード用テーブル初期化 */
    u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_READ[0] = (U1)GYRODEV_GYRO_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_READ[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_MODE_READ[0] = (U1)GYRODEV_GYRO_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_MODE_READ[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル(BurstRead)初期化 */
    u1_sp_GYRODEV_GYRODATA_RD_PDU2[0] = (U1)GYRODEV_GYRO_I2C_SLAVEADR_RD;    /* Slave Address */
    for(mcu_cnt = (U4)1U; mcu_cnt < (U4)8U; mcu_cnt++) {
        u1_sp_GYRODEV_GYRODATA_RD_PDU2[mcu_cnt] = (U1)0U;    /* 読出しデータ初期値 */
    }

    /*  データリード用テーブル(BurstRead)初期化 */
    u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_READ_XYZ[0] = (U1)GYRODEV_GSENS_I2C_SLAVEADR_RD;    /* Slave Address */
    for(mcu_cnt = (U4)1U; mcu_cnt < (U4)7U; mcu_cnt++) {
        u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_READ_XYZ[mcu_cnt] = (U1)0U;    /* 読出しデータ初期値 */
    }

    /*  データリード用テーブル(BurstRead)初期化 */
    u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_READ_TEMP[0] = (U1)GYRODEV_GSENS_I2C_SLAVEADR_RD;    /* Slave Address */
    for(mcu_cnt = (U4)1U; mcu_cnt < (U4)3U; mcu_cnt++) {
        u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_READ_TEMP[mcu_cnt] = (U1)0U;    /* 読出しデータ初期値 */
    }

    /*  データリード用テーブル初期化 */
    u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INTCONF_DT[0] = (U1)GYRODEV_GSENS_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INTCONF_DT[1] = (U1)0U;    /* 読出しデータ初期値 */

    /* address offset設定テーブル② 書込み用テーブル(Data可変)初期化 */
    u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_CFG2[0] = (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_CFG2[1] = (U1)0x5CU;    /* Write Address */
    u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_CFG2[2] = (U1)0U;    /* Write Data初期値(定期処理内で更新) */

    /* コンフィグファイルの書き込みデータ 書込み用テーブル(Data可変)初期化 */
    u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_DATA[0] = (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_DATA[1] = (U1)0x5EU;    /* Write Address */
    for(mcu_cnt = (U4)2U; mcu_cnt < (U4)34U; mcu_cnt++) {
        u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_DATA[mcu_cnt] = (U1)0U;    /* Write Data初期値(定期処理内で更新) */
    }

    /*  データリード用テーブル(BurstRead)初期化 */
    u1_sp_GYRODEV_GSENSDATA_RD_PDU2[0] = (U1)GYRODEV_GSENS_I2C_SLAVEADR_RD;    /* Slave Address */
    for(mcu_cnt = (U4)1U; mcu_cnt < (U4)7U; mcu_cnt++) {
        u1_sp_GYRODEV_GSENSDATA_RD_PDU2[mcu_cnt] = (U1)0U;    /* 読出しデータ初期値 */
    }

    /*  データリード用テーブル(BurstRead)初期化 */
    u1_sp_GYRODEV_GSENSDATA_RD_PDU4[0] = (U1)GYRODEV_GSENS_I2C_SLAVEADR_RD;    /* Slave Address */
    for(mcu_cnt = (U4)1U; mcu_cnt < (U4)3U; mcu_cnt++) {
        u1_sp_GYRODEV_GSENSDATA_RD_PDU4[mcu_cnt] = (U1)0U;    /* 読出しデータ初期値 */
    }

    /*  データリード用テーブル初期化 */
    u1_sp_GYRODEV_INT2_IO_CONF_RD_PDU2[0] = (U1)GYRODEV_GSENS_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_GYRODEV_INT2_IO_CONF_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /* 7.6 Interrupt設定INT2_IO_CONFレジスタ(0x54)bin制御用設定 書込み用テーブル(Data可変)初期化 */
    u1_sp_GYRODEV_INT2_IO_CONF_SET_PDU1[0] = (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_GYRODEV_INT2_IO_CONF_SET_PDU1[1] = (U1)0x54U;    /* Write Address */
    u1_sp_GYRODEV_INT2_IO_CONF_SET_PDU1[2] = (U1)0U;    /* Write Data初期値(定期処理内で更新) */

    /*  データリード用テーブル初期化 */
    u1_sp_GYRODEV_INTAPI_OUTPUTRST_RD_PDU2[0] = (U1)GYRODEV_GSENS_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_GYRODEV_INTAPI_OUTPUTRST_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル(BurstRead)初期化 */
    u1_sp_GYRODEV_INT_ANYMOT_RD_PDU2[0] = (U1)GYRODEV_GSENS_I2C_SLAVEADR_RD;    /* Slave Address */
    for(mcu_cnt = (U4)1U; mcu_cnt < (U4)3U; mcu_cnt++) {
        u1_sp_GYRODEV_INT_ANYMOT_RD_PDU2[mcu_cnt] = (U1)0U;    /* 読出しデータ初期値 */
    }

    /*  書込み用テーブル(Data可変)初期化 */
    u1_sp_GYRODEV_INT_ANYMOT_SET_PDU1[0] = (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_GYRODEV_INT_ANYMOT_SET_PDU1[1] = (U1)0x5EU;    /* Write Address */
    for(mcu_cnt = (U4)2U; mcu_cnt < (U4)4U; mcu_cnt++) {
        u1_sp_GYRODEV_INT_ANYMOT_SET_PDU1[mcu_cnt] = (U1)0U;    /* Write Data初期値(定期処理内で更新) */
    }

    /*  書込み用テーブル(Data可変)初期化 */
    u1_sp_GYRODEV_INT_ANYMOT_SET_PDU1[0] = (U1)GYRODEV_GSENS_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_GYRODEV_INT_ANYMOT_SET_PDU1[1] = (U1)0x5EU;    /* Write Address */
    for(mcu_cnt = (U4)2U; mcu_cnt < (U4)4U; mcu_cnt++) {
        u1_sp_GYRODEV_INT_ANYMOT_SET_PDU1[mcu_cnt] = (U1)0U;    /* Write Data初期値(定期処理内で更新) */
    }

}

/*===================================================================================================================================*/
/* void            vd_g_GyroMainTask(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_GyroMainTask(void)
{
    Dio_LevelType   dl_t_sts;
    U1      u1_t_i2c_busy;

    /* Bu-DET HI監視 */
    dl_t_sts = u1_s_GyroBuDetHiCheck();
    if(dl_t_sts != (Dio_LevelType)GYRO_DIO_HIGH){

        /* V33-Peri-ON状態チェック */
        vd_s_GyroV33PeriOnCheck();

        /* I2Cが空いたらイベント反映 */
        u1_t_i2c_busy = u1_s_GyroI2cIsBusy();
        if((u1_s_v33_event_pending != (U1)0xFF) && (u1_t_i2c_busy == (U1)FALSE)){
            vd_s_GyroDevEventGo(u1_s_v33_event_pending);
            u1_s_v33_event_pending = (U1)0xFF;
        }

        /* シーケンス実行処理 */
        vd_s_GyroDevSeqCtl();
    }

}

/**************************↓外部端子入力監視(START)↓************************/
/*===================================================================================================================================*/
/* u1              u1_s_GyroBuDetHiCheck(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_GyroBuDetHiCheck(void)
{
    Dio_LevelType   dl_t_port;  /* Pin読み出し値 */

    dl_t_port = dl_GYRO_DIO_READ_BUDET();

    if((dl_t_port == (Dio_LevelType)GYRO_DIO_HIGH)  && (dl_s_gyro_budet_sts == (Dio_LevelType)GYRO_DIO_LOW)){
        vd_s_GyroDevEventGo((U1)GYRO_EVENT_BUDET_HI); /* LO->HI */
    }
    else if((dl_t_port == (Dio_LevelType)GYRO_DIO_LOW)  && (dl_s_gyro_budet_sts == (Dio_LevelType)GYRO_DIO_HIGH)){
        vd_s_GyroDevEventGo((U1)GYRO_EVENT_BUDET_LO); /* HI->LO */
    }
    else{
        /* do nothing */
    }
    dl_s_gyro_budet_sts = dl_t_port;

    return(dl_t_port);
}

/*===================================================================================================================================*/
/* void            vd_s_GyroBuDetHi(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroBuDetHi(void)
{
    /* ジャイロ強制終了処理 */
    vd_s_GyroDevForceEnd();

    /* シーケンス管理バッファー初期化 */
    vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);

    /* ジャイロ状態を初期化 */
    vd_s_GyroDevCtlMngModSet((U1)GYRO_MODE_UNINIT);

    /* GセンサRead回数(k(5_2))クリア */
    u1_s_cnt_g_read = (U1)0U;
    /* 差分確認回数(k(5_3))クリア */
    u2_s_cnt_diff_verif = (U2)0U;

    /* MAX,MINクリア */
    st_s_gyro_accdat.u1_errlog_sts = (U1)FALSE;
    vd_s_GyroDevAccDataClear();
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroV33PeriOnCheck(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroV33PeriOnCheck(void)
{
    Dio_LevelType   dl_t_sts;

    /* V33-Peri-ON端子状態取得処理 */
    dl_t_sts    = dl_GYRO_DIO_READ_V33PERI();

    /* V33-Peri-ON端子状態変化処理 */
    if(dl_t_sts != dl_s_gyro_v33perion_sts){
        if(dl_t_sts == (Dio_LevelType)GYRO_DIO_HIGH){
            /* V33-Peri-ON OFF->ON処理 */

        }
        else{
            /* V33-Peri-ON ON->OFF処理 */
            /* 起動中にV33-PERI-ON H→Lイベント発生フラグON */
            u1_s_gyro_v33OffFlg = (U1)TRUE;
        }
    }

    /* V33-Peri-ON端子イベント処理 */
    if(dl_t_sts == (Dio_LevelType)GYRO_DIO_HIGH){
        /* ジャイロ状態管理の イベント・ハンドラを呼び出し */
        u1_s_v33_event_pending = (U1)GYRO_EVENT_V33PERION_ON;
    }
    else{
        /* ジャイロ状態管理の イベント・ハンドラを呼び出し */
        u1_s_v33_event_pending = (U1)GYRO_EVENT_V33PERION_OFF;
    }
}

/**************************↑外部端子入力監視(END)↑***************************/

/**************************↓状態遷移管理(START)↓***************************/
/*===================================================================================================================================*/
/* static void     vd_s_GyroDevCtlMngModSet(const U1 u1_a_MODE)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevCtlMngModSet(const U1 u1_a_MODE)
{
    if( (u1_a_MODE < (U1)GYRO_MODE_MAX) &&
        (st_s_gyro_ctrl.u1_mod != u1_a_MODE)){

        st_s_gyro_ctrl.u1_mod = u1_a_MODE;
    }
}

/*===================================================================================================================================*/
/* static U1       u1_s_GyroDevCtlMngModGet(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1        u1_s_GyroDevCtlMngModGet(void)
{
    /* ジャイロ状態を戻す */
    return(st_s_gyro_ctrl.u1_mod);
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroDevEventGo(const U1 u1_a_EVENT)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void      vd_s_GyroDevEventGo(const U1 u1_a_EVENT)
{
    U1                  u1_t_mode;
    FP_GYRO_EVNT_HNDL   fp_t_handler;

    /* ジャイロモードを取得 */
    u1_t_mode   = u1_s_GyroDevCtlMngModGet();

    /* モードとイベントの範囲確認 */
    if((u1_t_mode < (U1)GYRO_MODE_MAX) && (u1_a_EVENT < (U1)GYRO_EVENT_MAX)){
        st_s_gyro_ctrl.u1_event = u1_a_EVENT;
        fp_t_handler            = fp_sp2_GYRO_EVENT_HANDLER[u1_t_mode][u1_a_EVENT];

        if(fp_t_handler != vdp_PTR_NA){
            fp_t_handler();
        }
        else{
            /* do nothing */
        }
    }
    else{
        /* do nothing */
    }
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroDevUnInitTskStup(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevUnInitTskStup(void)
{
    /* 未初期化状態・タスク起動 */

    /* GYRO状態: 起動(1)実施中へ遷移する */
    vd_s_GyroDevCtlMngModSet((U1)GYRO_MODE_STUP1_PRO);

    /* GYROシーケンス: 起動(1)を起動 */
    vd_s_GyroDevSeqSet((U1)GYRO_SEQ_STAUP1);
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroDevComErrTskStup(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevComErrTskStup(void)
{
    /* エラー状態・タスク起動 */

    /* GYRO状態: 起動(1)実施中へ遷移する */
    vd_s_GyroDevCtlMngModSet((U1)GYRO_MODE_STUP1_PRO);

    /* GYROシーケンス: 起動(1)を起動 */
    vd_s_GyroDevSeqSet((U1)GYRO_SEQ_STAUP1);
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroDevStup1CompV33PeriOnOn(void)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevStup1CompV33PeriOnOn(void)
{
    /* 起動(1)実施完了状態・V33-Peri-ON OFF->ON */

    /* 起動中にV33-PERI-ON H→Lイベント発生フラグクリア */
    u1_s_gyro_v33OffFlg = (U1)FALSE;

    /* GYRO状態: 起動(2)実施中へ遷移する */
    vd_s_GyroDevCtlMngModSet((U1)GYRO_MODE_STUP2_PRO);

    /* GYROシーケンス: 起動(2)を起動 */
    vd_s_GyroDevSeqSet((U1)GYRO_SEQ_STAUP2);
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroDevNormV33PeriOnOn(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevNormV33PeriOnOn(void)
{
    /* 通常動作中状態・V33-Peri-ON OFF->ON */

    /* 起動中にV33-PERI-ON H→Lイベント発生フラグクリア */
    u1_s_gyro_v33OffFlg = (U1)FALSE;
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroDevErrV33PeriOnOn(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevErrV33PeriOnOn(void)
{
    /* 異常停止中状態・V33-Peri-ON OFF->ON */

    /* V33-Peri-ON OFF->ON時のみ実行 */
    if(u1_s_gyro_v33OffFlg == (U1)TRUE){
        /* GYRO状態: 起動(1)実施中へ遷移する */
        vd_s_GyroDevCtlMngModSet((U1)GYRO_MODE_STUP1_PRO);

        /* GYROシーケンス: 起動(1)を起動 */
        vd_s_GyroDevSeqSet((U1)GYRO_SEQ_STAUP1);

        /* 起動中にV33-PERI-ON H→Lイベント発生フラグクリア */
        u1_s_gyro_v33OffFlg = (U1)FALSE;
    }
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroDevNormV33PeriOnOff(void)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevNormV33PeriOnOff(void)
{
    /* 通常動作中状態・V33-Peri-ON ON->OFF */

    /* GYRO状態: 終了(1)実施中へ遷移する */
    vd_s_GyroDevCtlMngModSet((U1)GYRO_MODE_SHTDN1_PRO);

    /* GYROシーケンス: 終了(1)を起動 */
    vd_s_GyroDevSeqSet((U1)GYRO_SEQ_SHUTDOWN1);
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroDevComSysOffWait(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevComSysOffWait(void)
{
    /* 共通状態・システムオフ(待つ) */

    /* システムオフフラグを設定 */
    u1_s_gyro_sysoffflg = (U1)TRUE;
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroDevComSysOffProc(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevComSysOffProc(void)
{
    /* 共通状態・システムオフ(実施) */

    /* タスク状態通知(シャットダウン処理完了) */
    /* 予備設計のため処理なし */
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroDevErrSysOff(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevErrSysOff(void)
{
    /* 異常停止中状態・ステムオフ */

    /* GYRO状態: 未初期化へ遷移する */
    vd_s_GyroDevCtlMngModSet((U1)GYRO_MODE_UNINIT);

    /* タスク状態通知(シャットダウン処理完了) */
    /* 予備設計のため処理なし */
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroDevStup1ProSeqComp(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevStup1ProSeqComp(void)
{
    /* 起動(1)実施中・シーケンス完了 */

    /* GYRO状態: 起動(1)実施完了へ遷移する */
    vd_s_GyroDevCtlMngModSet((U1)GYRO_MODE_STUP1_COMP);

    /* システムOFFフラグをチェック */
    if(u1_s_gyro_sysoffflg == (U1)TRUE){
        /* タスク状態通知(シャットダウン処理完了) */
        /* 予備設計のため処理なし */
    }
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroDevStup2ProSeqComp(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevStup2ProSeqComp(void)
{
    /* 起動(2)実施中・シーケンス完了 */

    /* 初期化完了通知 */
    vd_g_XspiIviSub1PowerDevInitCmpApp((U1)XSPI_IVI_POWER_GYRO_INI);

    /* GYRO状態: 通常動作中へ遷移する */
    vd_s_GyroDevCtlMngModSet((U1)GYRO_MODE_NORM);
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroDevShtdn1ProSeqComp(void)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevShtdn1ProSeqComp(void)
{
    /* 終了(1)実施中・シーケンス完了 */

    /* GYRO状態: 起動(1)実施完了へ遷移する */
    vd_s_GyroDevCtlMngModSet((U1)GYRO_MODE_STUP1_COMP);

    /* システムOFFフラグをチェック */
    if(u1_s_gyro_sysoffflg == (U1)TRUE){
        /* タスク状態通知(シャットダウン処理完了) */
        /* 予備設計のため処理なし */
    }
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroDevStup1ProErr(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevStup1ProErr(void)
{
    /* 起動(1)実施中・異常検知 */

    /* GYRO強制終了処理 */
    vd_s_GyroDevForceEnd();

    /* システムOFFフラグをチェック */
    if(u1_s_gyro_sysoffflg == (U1)TRUE){
        /* GYRO状態: 未初期化へ遷移する */
        vd_s_GyroDevCtlMngModSet((U1)GYRO_MODE_UNINIT);

        /* タスク状態通知(シャットダウン処理完了) */
        /* 予備設計のため処理なし */
    }
    else{
        /* GYRO状態: 異常停止中へ遷移する */
        vd_s_GyroDevCtlMngModSet((U1)GYRO_MODE_ERR);
    }
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroDevStup2ProErr(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevStup2ProErr(void)
{
    /* 起動(2)実施中・異常検知 */

    /* システムOFFフラグをチェック */
    if(u1_s_gyro_sysoffflg == (U1)TRUE){
        /* GYRO強制終了処理 */
        vd_s_GyroDevForceEnd();

        /* GYRO状態: 未初期化へ遷移する */
        vd_s_GyroDevCtlMngModSet((U1)GYRO_MODE_UNINIT);

        /* タスク状態通知(シャットダウン処理完了) */
        /* 予備設計のため処理なし */
    }
    else{
        /* GYRO状態: 起動(1)実施中へ遷移する */
        vd_s_GyroDevCtlMngModSet((U1)GYRO_MODE_STUP1_PRO);

        /* GYROシーケンス: 起動(1)を起動 */
        vd_s_GyroDevSeqSet((U1)GYRO_SEQ_STAUP1);
    }
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroDevComDtcErr(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevComDtcErr(void)
{
    /* 共通状態・DTC異常検知 */

    /* GYRO強制終了処理 */
    vd_s_GyroDevForceEnd();

    /* エラーカウントをクリア */
    /* ToDo：DTCなので別部分で実装 */

    /* システムOFFフラグをチェック */
    if(u1_s_gyro_sysoffflg == (U1)TRUE){
        /* GYRO状態: 未初期化へ遷移する */
        vd_s_GyroDevCtlMngModSet((U1)GYRO_MODE_UNINIT);

        /* タスク状態通知(シャットダウン処理完了) */
        /* 予備設計のため処理なし */
    }
    else{
        /* GYRO状態: 異常停止中へ遷移する */
        vd_s_GyroDevCtlMngModSet((U1)GYRO_MODE_ERR);
    }
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroDevShutDn1ProErr(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevShutDn1ProErr(void)
{
    /* 終了(1)実施中・異常検知 */

    /* GYRO強制終了処理 */
    vd_s_GyroDevForceEnd();

    /* システムOFFフラグをチェック */
    if(u1_s_gyro_sysoffflg == (U1)TRUE){
        /* GYRO状態: 未初期化へ遷移する */
        vd_s_GyroDevCtlMngModSet((U1)GYRO_MODE_UNINIT);

        /* タスク状態通知(シャットダウン処理完了) */
        /* 予備設計のため処理なし */
    }
    else{
        /* GYRO状態: 異常停止中へ遷移する */
        vd_s_GyroDevCtlMngModSet((U1)GYRO_MODE_ERR);
    }
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroDevComRst(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevComRst(void)
{
    /* 共通状態・リトライ処理 */

    /* GYRO強制終了処理 */
    vd_s_GyroDevForceEnd();

    /* GYRO状態: 起動(1)実施中へ遷移する */
    vd_s_GyroDevCtlMngModSet((U1)GYRO_MODE_STUP1_PRO);

    /* GYROシーケンス: 起動(1)を起動 */
    vd_s_GyroDevSeqSet((U1)GYRO_SEQ_STAUP1);
}
/**************************↑状態遷移管理(END)↑*****************************/

/**************************↓シーケンス管理(START)↓*************************/
/*===================================================================================================================================*/
/* static void     vd_s_GyroDevSeqCtl(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevSeqCtl(void)
{
    FP_GYRO_SRQ_FUNC    fp_t_func;

    /* パラメータチェック */
    if(st_s_gyro_seqmng.u1_no >= (U1)GYRO_SEQ_MAX){
        /* 実行対象シーケンス異常 */
        st_s_gyro_seqmng.u1_no          = (U1)GYRO_SEQ_IDLE;
        st_s_gyro_seqmng.u1_step        = (U1)GYRO_SEQ_IDLE_STA;
        st_s_gyro_seqmng.u1_subtype     = (U1)GYRO_SEQ_IDLE_STA;
    }

    /* シーケンス実行処理 */
    fp_t_func   = fp_sp_gyro_Seq[st_s_gyro_seqmng.u1_no];
    if(fp_t_func != vdp_PTR_NA){
        fp_t_func();
    }
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroDevSeqSet(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevSeqSet(const U1 u1_a_SEQNO)
{
    if(u1_a_SEQNO < (U1)GYRO_SEQ_MAX){
        st_s_gyro_seqmng.u1_no          = u1_a_SEQNO;
        st_s_gyro_seqmng.u1_step        = (U1)GYRO_SEQ_IDLE_STA;
        st_s_gyro_seqmng.u1_subtype     = (U1)GYRO_SEQ_IDLE_STA;
    }
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroDevSeqIdle(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevSeqIdle(void)
{
    /* アイドルシーケンス */
    /* do nothing */
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroDevSeqStaUp1(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevSeqStaUp1(void)
{
    /* GYRO起動(1)シーケンス */

    U1      u1_t_sts;       /* I2C,サブ関数処理状況チェック */
    U1      u1_t_timchk;    /* 経過時間判定 */

    u1_t_sts    = (U1)FALSE;
    u1_t_timchk = (U1)FALSE;

    /* Ackタイムアウト用カウンタインクリメント */
    if(u4_s_gyro_acktime < (U4)U4_MAX){
        u4_s_gyro_acktime++;
    }

    switch (st_s_gyro_seqmng.u1_step)
    {
    case (U1)GYRO_SEQ_STAUP1_1:
        /* Wati t1 */
        u1_t_timchk = u1_s_GyroDevTimCheck(u4_s_gyro_linktim, (U4)GYRO_WAIT_T1);
        if(u1_t_timchk  == (U1)TRUE){
            /* Wati t1完了 次のシーケンスへ */
            u4_s_gyro_linktim           = (U4)0U;
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_STAUP1_2;
        }
        else{
            if (u4_s_gyro_linktim < (U4)U4_MAX) {
                u4_s_gyro_linktim++;
            } else {
                u4_s_gyro_linktim = (U4)U4_MAX;
            }
        }
        break;

    case (U1)GYRO_SEQ_STAUP1_2:
        /* SENSOR-ON端子 Lo→Hi */
        dl_GYRO_DIO_WRITE_SENSOR_ON_H();
        /* GYROモードをNorma1に設定する */
        st_s_gyro_ctrl.u1_dev_mode  = (U1)GYRO_DEV_MODE_NORMAL;
        /* 次のシーケンスへ */
        st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_STAUP1_3;
        break;

    case (U1)GYRO_SEQ_STAUP1_3:
        /* Wati t3 */
        u1_t_timchk = u1_s_GyroDevTimCheck(u4_s_gyro_linktim, (U4)GYRO_WAIT_T3);
        if(u1_t_timchk  == (U1)TRUE){
            /* Wati t3完了 次のシーケンスへ */
            u4_s_gyro_linktim           = (U4)0U;
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_STAUP1_4;
        }
        else{
            if (u4_s_gyro_linktim < (U4)U4_MAX) {
                u4_s_gyro_linktim++;
            } else {
                u4_s_gyro_linktim = (U4)U4_MAX;
            }
        }
        break;

    case (U1)GYRO_SEQ_STAUP1_4:
        u1_t_sts    = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_GYRO,
                                                (U2)GYRO_WRISTEP_WDG_GYR,
                                                (U1)GP_I2C_MA_SLA_6_GYRO,
                                                st_sp_GYRO_WRISTEP_WDG_GYR,
                                                st_sp_MCU_SYS_PWR_GYR_REG_GYR_WDG);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_STAUP1_5;
        }
        break;

    case (U1)GYRO_SEQ_STAUP1_5:
        u1_t_sts    = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                (U2)GYRO_WRISTEP_WDG_ACC,
                                                (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                st_sp_GYRO_WRISTEP_WDG_ACC,
                                                st_sp_MCU_SYS_PWR_GYR_REG_ACC_WDG);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_STAUP1_6;
        }
        break;

    case (U1)GYRO_SEQ_STAUP1_6:
        /* Wati t10(1ms待機)は本caseに到達した時点で満たしていると判断するためwait処理は実施しない */
        u1_t_sts    = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                (U2)GYRO_WRISTEP_MODE_ON_ACC,
                                                (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                st_sp_GYRO_WRISTEP_MODE_ON_ACC,
                                                st_sp_MCU_SYS_PWR_GYR_REG_ACC_MODE_ON);
        if(u1_t_sts == (U1)TRUE){
            /*  */
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_STAUP1_7;
        }
        break;

    case (U1)GYRO_SEQ_STAUP1_7:
        /* Wati t11 */
        u1_t_timchk = u1_s_GyroDevTimCheck(u4_s_gyro_linktim, (U4)GYRO_WAIT_T11);
        if(u1_t_timchk  == (U1)TRUE){
            /* Wati t11完了 次のシーケンスへ */
            u4_s_gyro_linktim           = (U4)0U;
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_STAUP1_8;
        }
        else{
            if (u4_s_gyro_linktim < (U4)U4_MAX) {
                u4_s_gyro_linktim++;
            } else {
                u4_s_gyro_linktim = (U4)U4_MAX;
            }
        }
        break;

    case (U1)GYRO_SEQ_STAUP1_8:
        u1_t_sts    = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_GYRO,
                                                (U2)GYRO_WRISTEP_SETUP_GYR,
                                                (U1)GP_I2C_MA_SLA_6_GYRO,
                                                st_sp_GYRO_WRISTEP_SETUP_GYR,
                                                st_sp_MCU_SYS_PWR_GYR_REG_GYR_SETUP);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_STAUP1_9;
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_SELFTEST_GYRO_1;
        }
        break;

    case (U1)GYRO_SEQ_STAUP1_9:
        u1_t_sts    = u1_s_GyroDevSeqGyrSelfTest();

        if(u1_t_sts == (U1)GYRO_RET_OK){
            /* テスト結果OK 次のシーケンスへ */
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_STAUP1_10;
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_IDLE_STA;
        }
        else if(u1_t_sts == (U1)GYRO_RET_IICERR){
            /* I2C失敗によるコマンドスキップ時のフェール処理 */
            /* 予備設計のため処理なし 遷移することはないがした場合はフェール処理を実施 */
            /* ToDo：I2C失敗時処理導入の検討 */

            vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);
            vd_s_GyroDevSeqSelfTestErr((U1)GYRO_ST_FAIL_TGT_GYRO);
        }
        else if(u1_t_sts == (U1)GYRO_RET_NG){
            /* テスト結果NG フェール処理 */
            /* 起動フロー(1)を終了、シーケンスアイドルに設定 */
            vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);
            /* Self Test 失敗処理 */
            vd_s_GyroDevSeqSelfTestErr((U1)GYRO_ST_FAIL_TGT_GYRO);
        }
        else{
            /* Self Test (Gyro)実施中 */
            /* do nothign */
        }
        break;

    case (U1)GYRO_SEQ_STAUP1_10:
        u1_t_sts    = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_GYRO,
                                                (U2)GYRO_WRISTEP_SETUP_GYR,
                                                (U1)GP_I2C_MA_SLA_6_GYRO,
                                                st_sp_GYRO_WRISTEP_SETUP_GYR,
                                                st_sp_MCU_SYS_PWR_GYR_REG_GYR_SETUP);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_STAUP1_11;
        }
        break;

    case (U1)GYRO_SEQ_STAUP1_11:
        u1_t_sts    = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                (U2)GYRO_WRISTEP_SETUP_SEN2_ACC,
                                                (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                st_sp_GYRO_WRISTEP_SETUP_SEN2_ACC,
                                                st_sp_MCU_SYS_PWR_GYR_REG_ACC_SEN2_SETUP);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_STAUP1_12;
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_SELFTEST_ACC_1;
        }
        break;

    case (U1)GYRO_SEQ_STAUP1_12:
        u1_t_sts    = u1_s_GyroDevSeqAccSelfTest();

        if(u1_t_sts == (U1)GYRO_RET_OK){
            /* テスト結果OK 次のシーケンスへ */
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_STAUP1_13;
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_UPCONF_1;
        }
        else if(u1_t_sts == (U1)GYRO_RET_IICERR){
            /* I2C失敗によるコマンドスキップ時のフェール処理 */
            /* 予備設計のため処理なし 遷移することはないがした場合はフェール処理を実施 */
            /* ToDo：I2C失敗時処理導入の検討 */

            vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);
            vd_s_GyroDevSeqSelfTestErr((U1)GYRO_ST_FAIL_TGT_ACC);
        }
        else if(u1_t_sts == (U1)GYRO_RET_NG){
            /* テスト結果NG フェール処理 */
            /* 起動フロー(1)を終了、シーケンスアイドルに設定 */
            vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);
            /* Self Test 失敗処理 */
            vd_s_GyroDevSeqSelfTestErr((U1)GYRO_ST_FAIL_TGT_ACC);
        }
        else{
            /* Self Test (Gセンサ)実施中 */
            /* do nothign */
        }
        break;

    case (U1)GYRO_SEQ_STAUP1_13:
        u1_t_sts    = u1_s_GyroDevSeqAccCfgUpload();

        if(u1_t_sts == (U1)GYRO_RET_OK){
            /* 実施結果OK 次のシーケンスへ */
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_STAUP1_14;
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_INTSET_1;
        }
        else if(u1_t_sts == (U1)GYRO_RET_IICERR){
            /* I2C失敗によるコマンドスキップ時のフェール処理 */
            /* 予備設計のため処理なし 遷移することはないがした場合はフェール処理を実施 */
            /* ToDo：I2C失敗時処理導入の検討 */

            vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);
            vd_s_GyroDevEventGo((U1)GYRO_EVENT_STUP_ERR);
        }
        else if(u1_t_sts == (U1)GYRO_RET_NG){
            /* 実施結果NG */
            /* ダイレコ記録 */
            vd_g_SysEcDrc_Drec((U1)SYSECDRC_DREC_CAT_GYROACC, (U1)SYSECDRC_DREC_ID_6, (U1)0x00U, (U1)0x00U);
            /* 起動フロー(1)を終了、シーケンスアイドルに設定 */
            vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);
            /* GYRO状態管理の イベント・ハンドラを呼び出し */
            vd_s_GyroDevEventGo((U1)GYRO_EVENT_STUP_ERR);
        }
        else{
            /* upload config待ち */
            /* do nothign */
        }
        break;

    case (U1)GYRO_SEQ_STAUP1_14:
        u1_t_sts    = u1_s_GyroDevSeqAccIntSet();

        if(u1_t_sts == (U1)GYRO_RET_OK){
            /* 実施結果OK 次のシーケンスへ */
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_STAUP1_15;
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_IDLE_STA;
        }
        else if(u1_t_sts == (U1)GYRO_RET_IICERR){
            /* I2C失敗によるコマンドスキップ時のフェール処理 */
            /* 予備設計のため処理なし 遷移することはないがした場合はフェール処理を実施 */
            /* ToDo：I2C失敗時処理導入の検討 */

            vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);
            vd_s_GyroDevEventGo((U1)GYRO_EVENT_STUP_ERR);
        }
        else{
            /* Set Interrupt待ち */
            /* do nothign */
        }
        break;

    case (U1)GYRO_SEQ_STAUP1_15:
        u1_t_sts    = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                (U2)GYRO_WRISTEP_WDG_ACC,
                                                (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                st_sp_GYRO_WRISTEP_WDG_ACC,
                                                st_sp_MCU_SYS_PWR_GYR_REG_ACC_WDG);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_STAUP1_16;
        }
        break;

    case (U1)GYRO_SEQ_STAUP1_16:
        u1_t_sts    = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                (U2)GYRO_WRISTEP_SETUP_SEN1_ACC,
                                                (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                st_sp_GYRO_WRISTEP_SETUP_SEN1_ACC,
                                                st_sp_MCU_SYS_PWR_GYR_REG_ACC_SEN1_SETUP);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_STAUP1_17;
        }
        break;

    case (U1)GYRO_SEQ_STAUP1_17:
        u1_t_sts    = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_GYRO,
                                                (U2)GYRO_WRISTEP_MODE_OFF_GYR,
                                                (U1)GP_I2C_MA_SLA_6_GYRO,
                                                st_sp_GYRO_WRISTEP_MODE_OFF_GYR,
                                                st_sp_MCU_SYS_PWR_GYR_REG_GYR_MODE_OFF);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_STAUP1_18;
        }
        break;

    case (U1)GYRO_SEQ_STAUP1_18:
        /* Wati t21 */
        u1_t_timchk = u1_s_GyroDevTimCheck(u4_s_gyro_linktim, (U4)GYRO_WAIT_T21);
        if(u1_t_timchk  == (U1)TRUE){
            /* Wati t21完了 */
            u4_s_gyro_linktim           = (U4)0U;

            /* GyroモードをSuspendに変更する */
            st_s_gyro_ctrl.u1_dev_mode  = (U1)GYRO_DEV_MODE_SUSPEND;

            /* Selt-Test異常エラーカウント クリア */
            u1_s_errcnt_l   = (U1)0U;
            u1_s_errcnt_j   = (U1)0U;

            /* シーケンスアイドルに設定 */
            vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);

            /* GYRO状態管理の イベント・ハンドラを呼び出し */
            vd_s_GyroDevEventGo((U1)GYRO_EVENT_SEQ_COMP);
        }
        else{
            if (u4_s_gyro_linktim < (U4)U4_MAX) {
                u4_s_gyro_linktim++;
            } else {
                u4_s_gyro_linktim = (U4)U4_MAX;
            }
        }
        break;

    default:
        vd_s_GyroI2cAbort((U1)MCU_I2C_ACK_GYRO);
        vd_s_GyroI2cAbort((U1)MCU_I2C_ACK_G_MONI);
        /* シーケンスアイドルに設定 */
        break;
    }
}

/*===================================================================================================================================*/
/* static U1       u1_s_GyroDevSeqGyrSelfTest(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_GyroDevSeqGyrSelfTest(void)
{
    /* Self-Test (Gyro) */

    U1      u1_t_ret;       /* シーケンス完了通知 */
    U1      u1_t_sts;       /* I2C,サブ関数処理状況チェック */
    U1      u1_t_timchk;    /* 経過時間判定 */
    U1      u1_t_read;      /* レジスタ読出し値 */

    u1_t_ret    = (U1)GYRO_RET_INPROC;
    u1_t_sts    = (U1)FALSE;
    u1_t_timchk = (U1)FALSE;
    u1_t_read   = (U1)0x00U;

    switch (st_s_gyro_seqmng.u1_subtype)
    {
    case (U1)GYRO_SEQ_SELFTEST_GYRO_1:
        /* 【write】0x3C */
        u1_t_sts    = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_GYRO,
                                                (U2)GYRO_WRISTEP_TEST_COMSET_GYR,
                                                (U1)GP_I2C_MA_SLA_6_GYRO,
                                                st_sp_GYRO_WRISTEP_TEST_COMSET_GYR,
                                                st_sp_MCU_SYS_PWR_GYR_REG_GYR_TEST);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_SELFTEST_GYRO_2;
        }
        break;

    case (U1)GYRO_SEQ_SELFTEST_GYRO_2:
        /* 【wait】t12 */
        u1_t_timchk = u1_s_GyroDevTimCheck(u4_s_gyro_linktim, (U4)GYRO_WAIT_T12);
        if(u1_t_timchk  == (U1)TRUE){
            /* Wati t12完了 次のシーケンスへ */
            u4_s_gyro_linktim           = (U4)0U;
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_SELFTEST_GYRO_3;
        }
        else{
            if (u4_s_gyro_linktim < (U4)U4_MAX) {
                u4_s_gyro_linktim++;
            } else {
                u4_s_gyro_linktim = (U4)U4_MAX;
            }
        }
        break;

    case (U1)GYRO_SEQ_SELFTEST_GYRO_3:
        /* 【read】0x3C */
        u1_t_sts    = u1_s_Gyro_I2cReadMgrFunc((U1)MCU_I2C_ACK_GYRO,
                                               (U1)GP_I2C_MA_SLA_6_GYRO,
                                               st_sp_MCU_SYS_PWR_GYR_REG_GYR_TEST_RD,
                                               (U1)MCU_I2C_WAIT_NON);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_SELFTEST_GYRO_4;
        }
        break;

    case (U1)GYRO_SEQ_SELFTEST_GYRO_4:
        /* SelfTest完了判定 */
        u1_t_read   = st_sp_MCU_SYS_PWR_GYR_REG_GYR_TEST_RD[GYRO_READPOS_1].u1p_pdu[GYRO_READPOS_1];

        if(((u1_t_read & (U1)GYRO_READDAT_BIT1) == (U1)GYRO_READDAT_BIT1)   &&
           ((u1_t_read & (U1)GYRO_READDAT_BIT2) != (U1)GYRO_READDAT_BIT2)   ){
            /* Test Result = OK */
            u1_t_ret    = (U1)GYRO_RET_OK;
        }
        else{
            /* Test Result = Failure */
            u1_t_ret    = (U1)GYRO_RET_NG;
        }
        break;

    default:
        /* アイドルシーケンスに設定 */
        vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);
        vd_s_GyroI2cAbort((U1)MCU_I2C_ACK_GYRO);
        break;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/* static U1       u1_s_GyroDevSeqAccSelfTest(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_GyroDevSeqAccSelfTest(void)
{
    /* Self-Test (Acc) */

    U1      u1_t_ret;                           /* シーケンス完了通知 */
    U1      u1_t_sts;                           /* I2C,サブ関数処理状況チェック */
    U1      u1_t_timchk;                        /* 経過時間判定 */
    S2      s2_t_data_buf_x;                    /* X軸 換算データ演算用バッファ */
    S2      s2_t_data_buf_y;                    /* Y軸 換算データ演算用バッファ */
    S2      s2_t_data_buf_z;                    /* Z軸 換算データ演算用バッファ */
    U2      u2_t_data_x;
    U2      u2_t_data_y;
    U2      u2_t_data_z;

    u1_t_ret    = (U1)GYRO_RET_INPROC;
    u1_t_sts    = (U1)FALSE;
    u1_t_timchk = (U1)FALSE;

    switch (st_s_gyro_seqmng.u1_subtype)
    {
    case (U1)GYRO_SEQ_SELFTEST_ACC_1:
        /* 【wait】t12 */
        u1_t_timchk = u1_s_GyroDevTimCheck(u4_s_gyro_linktim, (U4)GYRO_WAIT_T13);
        if(u1_t_timchk  == (U1)TRUE){
            /* Wati t11完了 次のシーケンスへ */
            u4_s_gyro_linktim           = (U4)0U;
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_SELFTEST_ACC_2;
        }
        else{
            if (u4_s_gyro_linktim < (U4)U4_MAX) {
                u4_s_gyro_linktim++;
            } else {
                u4_s_gyro_linktim = (U4)U4_MAX;
            }
        }
        break;

    case (U1)GYRO_SEQ_SELFTEST_ACC_2:
        /* write 0x6D （＋側） */
        u1_t_sts    = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                (U2)GYRO_WRISTEP_SELFTEST_ACC_PLS,
                                                (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                st_sp_GYRO_WRISTEP_SELFTEST_ACC_PLS,
                                                st_sp_MCU_SYS_PWR_GYR_REG_ACC_PLSTEST);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_SELFTEST_ACC_3;
        }
        break;

    case (U1)GYRO_SEQ_SELFTEST_ACC_3:
        /* 【wait】t14 */
        u1_t_timchk = u1_s_GyroDevTimCheck(u4_s_gyro_linktim, (U4)GYRO_WAIT_T14);
        if(u1_t_timchk  == (U1)TRUE){
            /* Wati t11完了 次のシーケンスへ */
            u4_s_gyro_linktim           = (U4)0U;
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_SELFTEST_ACC_4;
        }
        else{
            if (u4_s_gyro_linktim < (U4)U4_MAX) {
                u4_s_gyro_linktim++;
            } else {
                u4_s_gyro_linktim = (U4)U4_MAX;
            }
        }
        break;

    case (U1)GYRO_SEQ_SELFTEST_ACC_4:
        /* Read data (Gセンサ +) */
        u1_t_sts    = u1_s_Gyro_I2cReadMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                               (U1)GP_I2C_MA_SLA_7_G_MONI,
                                               st_sp_MCU_SYS_PWR_GYR_REG_GYR_XYZ,
                                               (U1)MCU_I2C_WAIT_NON);
        if(u1_t_sts == (U1)TRUE){
            /* データ保持（+側） */
            st_s_gyro_accdat_pls.u1_acc_x_lsb       = st_sp_MCU_SYS_PWR_GYR_REG_GYR_XYZ[GYRO_READPOS_1].u1p_pdu[GYRO_READPOS_1];
            st_s_gyro_accdat_pls.u1_acc_x_msb       = st_sp_MCU_SYS_PWR_GYR_REG_GYR_XYZ[GYRO_READPOS_1].u1p_pdu[GYRO_READPOS_2];
            st_s_gyro_accdat_pls.u1_acc_y_lsb       = st_sp_MCU_SYS_PWR_GYR_REG_GYR_XYZ[GYRO_READPOS_1].u1p_pdu[GYRO_READPOS_3];
            st_s_gyro_accdat_pls.u1_acc_y_msb       = st_sp_MCU_SYS_PWR_GYR_REG_GYR_XYZ[GYRO_READPOS_1].u1p_pdu[GYRO_READPOS_4];
            st_s_gyro_accdat_pls.u1_acc_z_lsb       = st_sp_MCU_SYS_PWR_GYR_REG_GYR_XYZ[GYRO_READPOS_1].u1p_pdu[GYRO_READPOS_5];
            st_s_gyro_accdat_pls.u1_acc_z_msb       = st_sp_MCU_SYS_PWR_GYR_REG_GYR_XYZ[GYRO_READPOS_1].u1p_pdu[GYRO_READPOS_6];

            /* データ換算 */
            u2_t_data_x    = (U2)(((U2)st_s_gyro_accdat_pls.u1_acc_x_msb << (U2)GYRO_SHIFT_8) | (U2)st_s_gyro_accdat_pls.u1_acc_x_lsb);
            u2_t_data_y    = (U2)(((U2)st_s_gyro_accdat_pls.u1_acc_y_msb << (U2)GYRO_SHIFT_8) | (U2)st_s_gyro_accdat_pls.u1_acc_y_lsb);
            u2_t_data_z    = (U2)(((U2)st_s_gyro_accdat_pls.u1_acc_z_msb << (U2)GYRO_SHIFT_8) | (U2)st_s_gyro_accdat_pls.u1_acc_z_lsb);

            st_s_gyro_accdat_pls.st_acc_xyz.s2_x    = (S2)u2_t_data_x;
            st_s_gyro_accdat_pls.st_acc_xyz.s2_y    = (S2)u2_t_data_y;
            st_s_gyro_accdat_pls.st_acc_xyz.s2_z    = (S2)u2_t_data_z;

            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_SELFTEST_ACC_5;
        }
        break;

    case (U1)GYRO_SEQ_SELFTEST_ACC_5:
        /* write 0x6D （-側） */
        u1_t_sts    = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                (U2)GYRO_WRISTEP_SELFTEST_ACC_MNS,
                                                (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                st_sp_GYRO_WRISTEP_SELFTEST_ACC_MNS,
                                                st_sp_MCU_SYS_PWR_GYR_REG_ACC_MNSTEST);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_SELFTEST_ACC_6;
        }
        break;

    case (U1)GYRO_SEQ_SELFTEST_ACC_6:
        /* wait t14 */
        u1_t_timchk = u1_s_GyroDevTimCheck(u4_s_gyro_linktim, (U4)GYRO_WAIT_T14);
        if(u1_t_timchk  == (U1)TRUE){
            /* Wati t11完了 次のシーケンスへ */
            u4_s_gyro_linktim           = (U4)0U;
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_SELFTEST_ACC_7;
        }
        else{
            if (u4_s_gyro_linktim < (U4)U4_MAX) {
                u4_s_gyro_linktim++;
            } else {
                u4_s_gyro_linktim = (U4)U4_MAX;
            }
        }
        break;

    case (U1)GYRO_SEQ_SELFTEST_ACC_7:
        /* Read data (Gセンサ -) */
        u1_t_sts    = u1_s_Gyro_I2cReadMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                               (U1)GP_I2C_MA_SLA_7_G_MONI,
                                               st_sp_MCU_SYS_PWR_GYR_REG_GYR_XYZ,
                                               (U1)MCU_I2C_WAIT_NON);
        if(u1_t_sts == (U1)TRUE){
            /* データ保持（-側） */
            st_s_gyro_accdat_mns.u1_acc_x_lsb       = st_sp_MCU_SYS_PWR_GYR_REG_GYR_XYZ[GYRO_READPOS_1].u1p_pdu[GYRO_READPOS_1];
            st_s_gyro_accdat_mns.u1_acc_x_msb       = st_sp_MCU_SYS_PWR_GYR_REG_GYR_XYZ[GYRO_READPOS_1].u1p_pdu[GYRO_READPOS_2];
            st_s_gyro_accdat_mns.u1_acc_y_lsb       = st_sp_MCU_SYS_PWR_GYR_REG_GYR_XYZ[GYRO_READPOS_1].u1p_pdu[GYRO_READPOS_3];
            st_s_gyro_accdat_mns.u1_acc_y_msb       = st_sp_MCU_SYS_PWR_GYR_REG_GYR_XYZ[GYRO_READPOS_1].u1p_pdu[GYRO_READPOS_4];
            st_s_gyro_accdat_mns.u1_acc_z_lsb       = st_sp_MCU_SYS_PWR_GYR_REG_GYR_XYZ[GYRO_READPOS_1].u1p_pdu[GYRO_READPOS_5];
            st_s_gyro_accdat_mns.u1_acc_z_msb       = st_sp_MCU_SYS_PWR_GYR_REG_GYR_XYZ[GYRO_READPOS_1].u1p_pdu[GYRO_READPOS_6];

            /* データ換算 */
            u2_t_data_x    = (U2)(((U2)st_s_gyro_accdat_mns.u1_acc_x_msb << (U2)GYRO_SHIFT_8) | (U2)st_s_gyro_accdat_mns.u1_acc_x_lsb);
            u2_t_data_y    = (U2)(((U2)st_s_gyro_accdat_mns.u1_acc_y_msb << (U2)GYRO_SHIFT_8) | (U2)st_s_gyro_accdat_mns.u1_acc_y_lsb);
            u2_t_data_z    = (U2)(((U2)st_s_gyro_accdat_mns.u1_acc_z_msb << (U2)GYRO_SHIFT_8) | (U2)st_s_gyro_accdat_mns.u1_acc_z_lsb);

            st_s_gyro_accdat_mns.st_acc_xyz.s2_x    = (S2)u2_t_data_x;
            st_s_gyro_accdat_mns.st_acc_xyz.s2_y    = (S2)u2_t_data_y;
            st_s_gyro_accdat_mns.st_acc_xyz.s2_z    = (S2)u2_t_data_z;

            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_SELFTEST_ACC_8;
        }
        break;

    case (U1)GYRO_SEQ_SELFTEST_ACC_8:
        /* write 0x6D （disable） */
        u1_t_sts    = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                (U2)GYRO_WRISTEP_SELFTEST_ACC_DISABLE,
                                                (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                st_sp_GYRO_WRISTEP_SELFTEST_ACC_DISABLE,
                                                st_sp_MCU_SYS_PWR_GYR_REG_ACC_DISTEST);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_SELFTEST_ACC_9;
        }
        break;

    case (U1)GYRO_SEQ_SELFTEST_ACC_9:
        /* wait t14 */
        u1_t_timchk = u1_s_GyroDevTimCheck(u4_s_gyro_linktim, (U4)GYRO_WAIT_T14);
        if(u1_t_timchk  == (U1)TRUE){
            /* Wati t11完了 次のシーケンスへ */
            u4_s_gyro_linktim           = (U4)0U;
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_SELFTEST_ACC_10;
        }
        else{
            if (u4_s_gyro_linktim < (U4)U4_MAX) {
                u4_s_gyro_linktim++;
            } else {
                u4_s_gyro_linktim = (U4)U4_MAX;
            }
        }
        break;

    case (U1)GYRO_SEQ_SELFTEST_ACC_10:
        /* テスト結果判定 */
        s2_t_data_buf_x = (S2)GYRO_DAT_ACC_XYZ_MAX - (S2)GYRO_DAT_ACC_X_DIF;
        s2_t_data_buf_y = (S2)GYRO_DAT_ACC_XYZ_MAX - (S2)GYRO_DAT_ACC_Y_DIF;
        s2_t_data_buf_z = (S2)GYRO_DAT_ACC_XYZ_MAX - (S2)GYRO_DAT_ACC_Z_DIF;

        if((st_s_gyro_accdat_mns.st_acc_xyz.s2_x <= s2_t_data_buf_x)  &&   /* X軸 オーバーフローチェック */
           (st_s_gyro_accdat_mns.st_acc_xyz.s2_y <= s2_t_data_buf_y)  &&   /* Y軸 オーバーフローチェック */
           (st_s_gyro_accdat_mns.st_acc_xyz.s2_z <= s2_t_data_buf_z)  ){   /* Z軸 オーバーフローチェック */

            /* 比較用データ作成 */
            s2_t_data_buf_x = st_s_gyro_accdat_mns.st_acc_xyz.s2_x + (S2)GYRO_DAT_ACC_X_DIF;
            s2_t_data_buf_y = st_s_gyro_accdat_mns.st_acc_xyz.s2_y + (S2)GYRO_DAT_ACC_Y_DIF;
            s2_t_data_buf_z = st_s_gyro_accdat_mns.st_acc_xyz.s2_z + (S2)GYRO_DAT_ACC_Z_DIF;

            if((st_s_gyro_accdat_pls.st_acc_xyz.s2_x >= s2_t_data_buf_x)  &&   /* X軸 Gセンサ（＋）― Gセンサ（－）≧th_dif ? */
               (st_s_gyro_accdat_pls.st_acc_xyz.s2_y >= s2_t_data_buf_y)  &&   /* Y軸 Gセンサ（＋）― Gセンサ（－）≧th_dif ? */
               (st_s_gyro_accdat_pls.st_acc_xyz.s2_z >= s2_t_data_buf_z)  ){   /* Z軸 Gセンサ（＋）― Gセンサ（－）≧th_dif ? */
                /* Test Result = OK */
                u1_t_ret    = (U1)GYRO_RET_OK;
            }
            else{
                /* Test Result = Failure */
                u1_t_ret    = (U1)GYRO_RET_NG;
            }
        }
        else{
            /* Test Result = Failure */
            u1_t_ret    = (U1)GYRO_RET_NG;
        }
        break;

    default:
        /* アイドルシーケンスに設定 */
        vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);
        vd_s_GyroI2cAbort((U1)MCU_I2C_ACK_G_MONI);
        break;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroDevSeqSelfTestErr(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevSeqSelfTestErr(const U1 u1_a_fail_tgt)
{
    /* Self-Testエラーカウントl(6_1)をチェック	 */
    if(u1_s_errcnt_l < (U1)GYRO_CNT_SELFTEST_RTRY_MAX){
        /* エラーカウントを累積 */
        u1_s_errcnt_l++;

        /* GYRO状態管理の イベント・ハンドラを呼び出し */
        vd_s_GyroDevEventGo(GYRO_EVENT_DEV_RST);
    }
    else{
        /* エラーカウントl(6_1)、j(6_1)をクリア */
        u1_s_errcnt_l   = (U1)0U;
        u1_s_errcnt_j   = (U1)0U;

        /* ダイレコ記録 */
        vd_g_SysEcDrc_Drec((U1)SYSECDRC_DREC_CAT_GYROACC, (U1)SYSECDRC_DREC_ID_1, u1_a_fail_tgt, (U1)0x00U);

        /* GYRO状態管理の イベント・ハンドラを呼び出し */
        vd_s_GyroDevEventGo((U1)GYRO_EVENT_STUP_ERR);
    }
}

/*===================================================================================================================================*/
/* static U1       u1_s_GyroDevSeqAccCfgUpload(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_GyroDevSeqAccCfgUpload(void)
{
    ST_GYRO_DATAINFO    st_t_datainfo;
    U1                  u1_t_ret;       /* シーケンス完了通知 */
    U1                  u1_t_sts;       /* I2C,サブ関数処理状況チェック */
    U1                  u1_t_timchk;    /* 経過時間判定 */
    U1                  u1_t_read;      /* レジスタ読出し値 */
    U4                  u4_t_offset;    /* 書込み位置オフセット */
    U1 *                u1p_t_addr;     /* 書込み位置アドレス */

    vd_s_GyroDevMemset(&st_t_datainfo, (U1)0U, (U4)sizeof(st_t_datainfo));
    u1_t_ret    = (U1)GYRO_RET_INPROC;
    u1_t_sts    = (U1)FALSE;
    u1_t_timchk = (U1)FALSE;
    u1_t_read   = (U1)0x00U;

    switch (st_s_gyro_seqmng.u1_subtype)
    {
    case GYRO_SEQ_UPCONF_1:
        /* GセンサデータInfo読込 */
        st_s_gyro_cfgmng.u1_upload_cnt  = (U1)0U;
        st_s_gyro_cfgmng.u1_upload_idx  = (U1)0U;
        st_s_gyro_cfgmng.u4_upload_addr = (U4)0U;
        u1_t_sts    = u1_s_GyroGetDatInfo(&st_t_datainfo);
        if(u1_t_sts != (U1)GYRO_RET_OK){
            /* Config読出し失敗 ダイレコ記録して終了 */
            /* ToDo：ダイレコIF挿入 */
            u1_t_ret    = (U1)GYRO_RET_OK;
        }
        else{
            if(st_t_datainfo.u4_datsiz > (U4)GYRO_CFG_MAXSIZ){
                /* Configサイズ異常 ダイレコ記録して終了 */
                /* ToDo：ダイレコIF挿入 */
                u1_t_ret    = (U1)GYRO_RET_OK;
            }
            else{
                /* 読込データ先頭アドレス&書込み回数取得 */
                st_s_gyro_cfgmng.u4_upload_addr = st_t_datainfo.u4_strtadr;
                st_s_gyro_cfgmng.u1_upload_cnt  = (U1)((st_t_datainfo.u4_datsiz / (U4)GYRO_CFG_WRISIZ) & (U4)0x000000FFU);
                u1_t_ret                        = (U1)GYRO_RET_INPROC;
            }
        }
        /* INIT Check NGカウント初期化 */
        u1_s_gyro_uploadcfg_rtrycnt = (U1)0U;
        st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_UPCONF_2;
        break;

    case (U1)GYRO_SEQ_UPCONF_2:
        /* softreset (Gセンサ) */
        u1_t_sts    = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                (U2)GYRO_WRISTEP_SOFTRESET,
                                                (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                st_sp_GYRO_WRISTEP_SOFTRESET,
                                                st_sp_MCU_SYS_PWR_GYR_REG_ACC_SOFTRESET);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_UPCONF_3;
        }
        break;

    case (U1)GYRO_SEQ_UPCONF_3:
        /* 【wait】t15 */
        u1_t_timchk = u1_s_GyroDevTimCheck(u4_s_gyro_linktim, (U4)GYRO_WAIT_T15);
        if(u1_t_timchk  == (U1)TRUE){
            /* Wati t15完了 次のシーケンスへ */
            u4_s_gyro_linktim           = (U4)0U;
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_UPCONF_4;
        }
        else{
            if (u4_s_gyro_linktim < (U4)U4_MAX) {
                u4_s_gyro_linktim++;
            } else {
                u4_s_gyro_linktim = (U4)U4_MAX;
            }
        }
        break;

    case (U1)GYRO_SEQ_UPCONF_4:
        /* change mode ACC suspend(ADS:0x7D */
        u1_t_sts    = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                (U2)GYRO_WRISTEP_MODE_OFF_ACC,
                                                (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                st_sp_GYRO_WRISTEP_MODE_OFF_ACC,
                                                st_sp_MCU_SYS_PWR_GYR_REG_ACC_MODE_OFF);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_UPCONF_5;
        }
        break;

    case (U1)GYRO_SEQ_UPCONF_5:
        /* Wati t10(1ms待機)は本caseに到達した時点で満たしていると判断するためwait処理は実施しない */
        /* 次のシーケンスへ */
        st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_UPCONF_6;
        break;

    case (U1)GYRO_SEQ_UPCONF_6:
        /* change mode ACC normal(ADS:0x7C) */
        u1_t_sts    = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                (U2)GYRO_WRISTEP_PWRCONF_ON,
                                                (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                st_sp_GYRO_WRISTEP_PWRCONF_ON,
                                                st_sp_MCU_SYS_PWR_GYR_REG_ACC_PWRCONF_ON);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_UPCONF_7;
        }
        break;

    case (U1)GYRO_SEQ_UPCONF_7:
        /* 【wait】t15 */
        u1_t_timchk = u1_s_GyroDevTimCheck(u4_s_gyro_linktim, (U4)GYRO_WAIT_T15);
        if(u1_t_timchk  == (U1)TRUE){
            /* Wati t15完了 次のシーケンスへ */
            u4_s_gyro_linktim           = (U4)0U;
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_UPCONF_8;
        }
        else{
            if (u4_s_gyro_linktim < (U4)U4_MAX) {
                u4_s_gyro_linktim++;
            } else {
                u4_s_gyro_linktim = (U4)U4_MAX;
            }
        }
        break;

    case (U1)GYRO_SEQ_UPCONF_8:
        /* Set INT_CTRL write ADS:0x59 val:0x00 */
        u1_t_sts    = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                (U2)GYRO_WRISTEP_INTCONF_ON,
                                                (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                st_sp_GYRO_WRISTEP_INTCONF_ON,
                                                st_sp_MCU_SYS_PWR_GYR_REG_ACC_INTCONF_ON);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_UPCONF_9;
        }
        break;

    case (U1)GYRO_SEQ_UPCONF_9:
        /* 【wait】t15 */
        u1_t_timchk = u1_s_GyroDevTimCheck(u4_s_gyro_linktim, (U4)GYRO_WAIT_T15);
        if(u1_t_timchk  == (U1)TRUE){
            /* Wati t15完了 次のシーケンスへ */
            u4_s_gyro_linktim           = (U4)0U;
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_UPCONF_10;
        }
        else{
            if (u4_s_gyro_linktim < (U4)U4_MAX) {
                u4_s_gyro_linktim++;
            } else {
                u4_s_gyro_linktim = (U4)U4_MAX;
            }
        }
        break;

    case (U1)GYRO_SEQ_UPCONF_10:
        /* upload config file via I2C write 0x5B */
        u1_t_sts    = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                (U2)GYRO_WRISTEP_CFG_OFST1,
                                                (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                st_sp_GYRO_WRISTEP_CFG_OFST1,
                                                st_sp_MCU_SYS_PWR_GYR_REG_ACC_CFG1);
        if(u1_t_sts == (U1)GYRO_RET_OK){
            /* 次書込みデータ作成 */
            st_sp_MCU_SYS_PWR_GYR_REG_ACC_CFG2[GYRO_WRIPOS_0].u1p_pdu[GYRO_WRIPOS_2]    = st_s_gyro_cfgmng.u1_upload_idx;
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_UPCONF_11;
        }
        break;

    case (U1)GYRO_SEQ_UPCONF_11:
        /* upload config file via I2C write 0x5C */
        u1_t_sts    = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                (U2)GYRO_WRISTEP_CFG_OFST2,
                                                (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                st_sp_GYRO_WRISTEP_CFG_OFST2,
                                                st_sp_MCU_SYS_PWR_GYR_REG_ACC_CFG2);
        if(u1_t_sts == (U1)GYRO_RET_OK){
            /* 次書込みデータ作成 */
            if(((U4)GYRO_CFG_WRISIZ != (U4)0U) && ((U4)st_s_gyro_cfgmng.u1_upload_idx <= ((U4)U4_MAX / (U4)GYRO_CFG_WRISIZ))){
                u4_t_offset     = ((U4)st_s_gyro_cfgmng.u1_upload_idx * (U4)GYRO_CFG_WRISIZ);
            }
            else{
                u4_t_offset     = (U4)U4_MAX;
            }
            if(u4_t_offset<= ((U4)U4_MAX - (U4)st_s_gyro_cfgmng.u4_upload_addr)){
                u1p_t_addr      = (U1 *)(st_s_gyro_cfgmng.u4_upload_addr + u4_t_offset);
            }
            else{
                u1p_t_addr      = (U1 *)0;
            }
            vd_g_MemcpyU1(&st_sp_MCU_SYS_PWR_GYR_REG_ACC_DATA[GYRO_WRIPOS_0].u1p_pdu[GYRO_WRIPOS_2], u1p_t_addr, (U4)GYRO_CFG_WRISIZ);
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_UPCONF_12;
        }
        break;

    case (U1)GYRO_SEQ_UPCONF_12:
        /* upload config file via I2C write 0x5E */
        u1_t_sts    = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                (U2)GYRO_WRISTEP_CFG_DATA,
                                                (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                st_sp_GYRO_WRISTEP_CFG_DATA,
                                                st_sp_MCU_SYS_PWR_GYR_REG_ACC_DATA);
        if(u1_t_sts == (U1)GYRO_RET_OK){
            /* インデックスインクリメント */
            if (st_s_gyro_cfgmng.u1_upload_idx < U1_MAX) {
                st_s_gyro_cfgmng.u1_upload_idx++;
            } else {
                st_s_gyro_cfgmng.u1_upload_idx = U1_MAX;
            }
            /* 完了判定 */
            if(st_s_gyro_cfgmng.u1_upload_idx >= st_s_gyro_cfgmng.u1_upload_cnt){
                /* アップロード完了 次のシーケンスへ */
                st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_UPCONF_13;
            }
            else{
                /* アップロードシーケンスを再実行 */
                st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_UPCONF_10;
            }
        }
        break;
    case (U1)GYRO_SEQ_UPCONF_13:
        /* Set INT_CTRL write ADS:0x59 val:0x01 */
        u1_t_sts    = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                (U2)GYRO_WRISTEP_INTCONF_OFF,
                                                (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                st_sp_GYRO_WRISTEP_INTCONF_OFF,
                                                st_sp_MCU_SYS_PWR_GYR_REG_ACC_INTCONF_OFF);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_UPCONF_14;
        }
        break;

    case (U1)GYRO_SEQ_UPCONF_14:
        /* 【wait】t15 */
        u1_t_timchk = u1_s_GyroDevTimCheck(u4_s_gyro_linktim, (U4)GYRO_WAIT_T15);
        if(u1_t_timchk  == (U1)TRUE){
            /* Wati t15完了 次のシーケンスへ */
            u4_s_gyro_linktim           = (U4)0U;
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_UPCONF_15;
        }
        else{
            if (u4_s_gyro_linktim < (U4)U4_MAX) {
                u4_s_gyro_linktim++;
            } else {
                u4_s_gyro_linktim = (U4)U4_MAX;
            }
        }
        break;

    case (U1)GYRO_SEQ_UPCONF_15:
        /* read 0x2A */
        u1_t_sts    = u1_s_Gyro_I2cReadMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                               (U1)GP_I2C_MA_SLA_7_G_MONI,
                                               st_sp_MCU_SYS_PWR_GYR_REG_ACC_INTCONF_READ,
                                               (U1)MCU_I2C_WAIT_NON);
        if(u1_t_sts == (U1)TRUE){
            /* INIT Check */
            u1_t_read   = st_sp_MCU_SYS_PWR_GYR_REG_ACC_INTCONF_READ[GYRO_READPOS_1].u1p_pdu[GYRO_READPOS_1];

            if(u1_t_read ==(U1)GYRO_READDAT_BIT0){
                /* 次のシーケンスへ */
                st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_UPCONF_16;
            }
            else{
                if(u1_s_gyro_uploadcfg_rtrycnt > (U1)GYRO_CFG_MAXRTRY){
                    /* Config File 設定失敗として終了 */
                    u1_t_ret    = (U1)GYRO_RET_NG;
                }
                else{
                    if(u1_s_gyro_uploadcfg_rtrycnt < (U1)U1_MAX){
                        u1_s_gyro_uploadcfg_rtrycnt++;
                    }
                    else{
                        u1_s_gyro_uploadcfg_rtrycnt = (U1)U1_MAX;
                    }
                    /* シーケンス再実行 */
                    st_s_gyro_seqmng.u1_subtype     = (U1)GYRO_SEQ_UPCONF_2;
                    st_s_gyro_cfgmng.u1_upload_idx  = (U1)0U;
                }
            }
        }
        else{
            /* do nothing */
        }
        break;

    case (U1)GYRO_SEQ_UPCONF_16:
        /* change mode ACC normal */
        u1_t_sts    = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                (U2)GYRO_WRISTEP_MODE_ON_ACC,
                                                (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                st_sp_GYRO_WRISTEP_MODE_ON_ACC,
                                                st_sp_MCU_SYS_PWR_GYR_REG_ACC_MODE_ON);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_UPCONF_17;
        }
        break;

    case (U1)GYRO_SEQ_UPCONF_17:
        /* 【wait】t15 */
        u1_t_timchk = u1_s_GyroDevTimCheck(u4_s_gyro_linktim, (U4)GYRO_WAIT_T15);
        if(u1_t_timchk  == (U1)TRUE){
            /* Wati t15完了 シーケンス終了 */
            u4_s_gyro_linktim   = (U4)0U;
            u1_t_ret            = (U1)GYRO_RET_OK;
        }
        else{
            if (u4_s_gyro_linktim < (U4)U4_MAX) {
                u4_s_gyro_linktim++;
            } else {
                u4_s_gyro_linktim = (U4)U4_MAX;
            }
        }
        break;

    default:
        /* アイドルシーケンスに設定 */
        vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);
        vd_s_GyroI2cAbort((U1)MCU_I2C_ACK_G_MONI);
        break;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/* static U1       u1_s_GyroDevSeqAccIntSet(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_GyroGetDatInfo(ST_GYRO_DATAINFO * st_a_datainfo)
{
    U1      u1_t_ret;
    U1      u1_t_sts;
    const U1 *    u1p_t_version;
    const U1 *    u1p_t_datsiz;
    const U1 *    u1p_t_stradr;
    U1      u1_tp_version[GYRO_SIZ_VERSION];
    U1      u1_tp_datsiz[GYRO_SIZ_BUF];
    U1      u1_tp_stradr[GYRO_SIZ_BUF];
    U4      u4_t_clc_datsiz;
    U4      u4_t_clc_stradr;

    u1_t_ret        = (U1)GYRO_RET_NG;
    u1_t_sts        = (U1)GYRO_RET_NG;
    u4_t_clc_datsiz = (U4)0x00000000U;
    u4_t_clc_stradr = (U4)0x00000000U;

    if(st_a_datainfo != vdp_PTR_NA){
        u1_t_sts = u1_s_GyroGetStsChk();
        if(u1_t_sts == (U1)GYRO_CFG_EXIST){
            u1p_t_version   = &u1p_s_GYROINFO_TOP_ADR[GYRO_ADR_VERSION];
            u1p_t_datsiz    = &u1p_s_GYROINFO_TOP_ADR[GYRO_ADR_DATSIZ];
            u1p_t_stradr    = &u1p_s_GYROINFO_TOP_ADR[GYRO_ADR_OFFSET];

            /* ConfigFileはリトルエンディアンのため、エンディアン変換せずに型を変換 */
            vd_g_MemcpyU1(u1_tp_version, u1p_t_version, sizeof(u1_tp_version));
            vd_g_MemcpyU1(u1_tp_datsiz, u1p_t_datsiz, sizeof(u1_tp_datsiz));
            vd_g_MemcpyU1(u1_tp_stradr, u1p_t_stradr, sizeof(u1_tp_stradr));

            u4_t_clc_datsiz |=  (U4)u1_tp_datsiz[GYRO_POS_0] << (U4)GYRO_SFT_BYTE3;
            u4_t_clc_datsiz |=  (U4)u1_tp_datsiz[GYRO_POS_1] << (U4)GYRO_SFT_BYTE2;
            u4_t_clc_datsiz |=  (U4)u1_tp_datsiz[GYRO_POS_2] << (U4)GYRO_SFT_BYTE1;
            u4_t_clc_datsiz |=  (U4)(u1_tp_datsiz[GYRO_POS_3]);

            u4_t_clc_stradr |=  (U4)u1_tp_stradr[GYRO_POS_0] << (U4)GYRO_SFT_BYTE3;
            u4_t_clc_stradr |=  (U4)u1_tp_stradr[GYRO_POS_1] << (U4)GYRO_SFT_BYTE2;
            u4_t_clc_stradr |=  (U4)u1_tp_stradr[GYRO_POS_2] << (U4)GYRO_SFT_BYTE1;
            u4_t_clc_stradr |=  (U4)(u1_tp_stradr[GYRO_POS_3]);

            /* 200.102_02h：MCUバージョン応答 */
            vd_g_XspiIviSub1VersionGsenPut(u1_tp_version);

            /* サイズ、読込開始アドレスを設定 */
            st_a_datainfo->u4_datsiz    = u4_t_clc_datsiz;
            if(u4_t_clc_stradr <= ((U4)U4_MAX - (U4)u1p_s_GYROINFO_TOP_ADR)){
                st_a_datainfo->u4_strtadr   = (U4)u1p_s_GYROINFO_TOP_ADR + u4_t_clc_stradr;
            }
            else{
                st_a_datainfo->u4_strtadr   = (U4)U4_MAX;
            }
            u1_t_ret                    = (U1)GYRO_RET_OK;
        }
        else{
            /* Configファイル読出し不可 */
            u1_t_ret    = (U1)GYRO_RET_NG;
        }
    }
    else{
        u1_t_ret    = (U1)GYRO_RET_NG;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/* static U1       u1_s_GyroGetStsChk(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_GyroGetStsChk(void)
{
    U1  u1_t_ret;

    /* シグネチャによるマイコンへの書込み有無確認 */
    if( (u1_REG_READ(*(u1p_s_GYROINFO_TOP_ADR            ))  == (U1)GYRO_FNTOKEN_G) &&
        (u1_REG_READ(u1p_s_GYROINFO_TOP_ADR[GYRO_CLC_ADR1])  == (U1)GYRO_FNTOKEN__) &&
        (u1_REG_READ(u1p_s_GYROINFO_TOP_ADR[GYRO_CLC_ADR2])  == (U1)GYRO_FNTOKEN_C) &&
        (u1_REG_READ(u1p_s_GYROINFO_TOP_ADR[GYRO_CLC_ADR3])  == (U1)GYRO_FNTOKEN_O) &&
        (u1_REG_READ(u1p_s_GYROINFO_TOP_ADR[GYRO_CLC_ADR4])  == (U1)GYRO_FNTOKEN_N) &&
        (u1_REG_READ(u1p_s_GYROINFO_TOP_ADR[GYRO_CLC_ADR5])  == (U1)GYRO_FNTOKEN_F) &&
        (u1_REG_READ(u1p_s_GYROINFO_TOP_ADR[GYRO_CLC_ADR6])  == (U1)GYRO_FNTOKEN_I) &&
        (u1_REG_READ(u1p_s_GYROINFO_TOP_ADR[GYRO_CLC_ADR7])  == (U1)GYRO_FNTOKEN_G) ){

        u1_t_ret    = (U1)GYRO_CFG_EXIST;
    }
    else{
        u1_t_ret    = (U1)GYRO_CFG_NON;
    }

    return(u1_t_ret);
}
/*===================================================================================================================================*/
/* static U1       u1_s_GyroDevSeqAccIntSet(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_GyroDevSeqAccIntSet(void)
{
    U1      u1_t_ret;       /* シーケンス完了通知 */
    U1      u1_t_sts;       /* I2C,サブ関数処理状況チェック */

    u1_t_ret    = (U1)GYRO_RET_INPROC;
    u1_t_sts    = (U1)FALSE;

    switch (st_s_gyro_seqmng.u1_subtype)
    {
    case GYRO_SEQ_INTSET_1:
        /* INT_ANYMOT_TH */
        u1_t_sts    = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                (U2)GYRO_WRISTEP_INT_ANYMOT_TH,
                                                (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                st_sp_GYRO_WRISTEP_INT_ANYMOT_TH,
                                                st_sp_MCU_SYS_PWR_GYR_REG_INTSET_ANYMOT_TH);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_INTSET_2;
        }
        break;
    case GYRO_SEQ_INTSET_2:
        /* INT_ANYMOT_EN */
        u1_t_sts    = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                (U2)GYRO_WRISTEP_INT_ANYMOT_EN,
                                                (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                st_sp_GYRO_WRISTEP_INT_ANYMOT_EN,
                                                st_sp_MCU_SYS_PWR_GYR_REG_INTSET_ANYMOT_EN);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_INTSET_3;
        }
        break;
    case GYRO_SEQ_INTSET_3:
        /* INT_ANYMOT_TH */
        u1_t_sts    = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                (U2)GYRO_WRISTEP_INT_OTH,
                                                (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                st_sp_GYRO_WRISTEP_INT_OTH,
                                                st_sp_MCU_SYS_PWR_GYR_REG_INTSET_OTH);
        if(u1_t_sts == (U1)TRUE){
            /* 全書込み完了 */
            u1_t_ret    = (U1)GYRO_RET_OK;
        }
        break;

    default:
        /* アイドルシーケンスに設定 */
        vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);
        vd_s_GyroI2cAbort((U1)MCU_I2C_ACK_G_MONI);
        break;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static void     vd_s_GyroDevSeqStaUp2(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevSeqStaUp2(void)
{
    /* GYRO起動(2)シーケンス */
    U1      u1_t_sts;       /* I2C,サブ関数処理状況チェック */
    U1      u1_t_timchk;    /* 経過時間判定 */

    u1_t_sts    = (U1)FALSE;
    u1_t_timchk = (U1)FALSE;

    /* Ackタイムアウト用カウンタインクリメント */
    if(u4_s_gyro_acktime < (U4)U4_MAX){
        u4_s_gyro_acktime++;
    }

    switch (st_s_gyro_seqmng.u1_step)
    {
    case (U1)GYRO_SEQ_STAUP2_1:
        u1_t_sts    = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                (U2)GYRO_WRISTEP_SETUP_SEN1_BW_ACC,
                                                (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                st_sp_GYRO_WRISTEP_SETUP_SEN1_BW_ACC,
                                                st_sp_MCU_SYS_PWR_GYR_REG_ACC_SEN1_SETUP);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_STAUP2_2;
        }
        break;

    case (U1)GYRO_SEQ_STAUP2_2:
        u1_t_sts    = u1_s_Gyro_I2cReadMgrFunc((U1)MCU_I2C_ACK_GYRO,
                                               (U1)GP_I2C_MA_SLA_6_GYRO,
                                               st_sp_MCU_SYS_PWR_GYR_REG_GYR_MODE_RD,
                                               (U1)MCU_I2C_WAIT_NON);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_step = (U1)GYRO_SEQ_STAUP2_3;
        }
        break;

    case (U1)GYRO_SEQ_STAUP2_3:
        if(st_sp_MCU_SYS_PWR_GYR_REG_GYR_MODE_RD[GYRO_READPOS_1].u1p_pdu[GYRO_READPOS_1] == (U1)GYRO_DAT_GYROMODE_SUSPEND){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_step = (U1)GYRO_SEQ_STAUP2_4;
        }
        else{
            /* この時点でGyro=ONだと起動フロー(1)を通っていない可能性がある為、フェールとして起動フロー(1)へ遷移 */
            vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);
            vd_s_GyroDevEventGo((U1)GYRO_EVENT_STUP_ERR);
        }
        break;

    case (U1)GYRO_SEQ_STAUP2_4:
        /* Wati t10(1ms待機)は本caseに到達した時点で満たしていると判断するためwait処理は実施しない */
        /* 次のシーケンスへ */
        st_s_gyro_seqmng.u1_step = (U1)GYRO_SEQ_STAUP2_5;
        break;

    case (U1)GYRO_SEQ_STAUP2_5:
        u1_t_sts    = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_GYRO,
                                                (U2)GYRO_WRISTEP_MODE_ON_GYR,
                                                (U1)GP_I2C_MA_SLA_6_GYRO,
                                                st_sp_GYRO_WRISTEP_MODE_ON_GYR,
                                                st_sp_MCU_SYS_PWR_GYR_REG_GYR_MODE_ON);
        if(u1_t_sts == (U1)TRUE){
            /* GYROモードをNorma1に設定する */
            st_s_gyro_ctrl.u1_dev_mode  = (U1)GYRO_DEV_MODE_NORMAL;

            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_STAUP2_6;
        }
        break;

    case (U1)GYRO_SEQ_STAUP2_6:
        /* Wati t21 */
        u1_t_timchk = u1_s_GyroDevTimCheck(u4_s_gyro_linktim, (U4)GYRO_WAIT_T21);
        if(u1_t_timchk  == (U1)TRUE){
            /* Wati t21完了 */
            u4_s_gyro_linktim   = (U4)0U;

            /* シーケンスアイドルに設定 */
            vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);

            /* GYRO状態管理の イベント・ハンドラを呼び出し */
            vd_s_GyroDevEventGo((U1)GYRO_EVENT_SEQ_COMP);
        }
        else{
            if (u4_s_gyro_linktim < (U4)U4_MAX) {
                u4_s_gyro_linktim++;
            } else {
                u4_s_gyro_linktim = (U4)U4_MAX;
            }
        }
        break;

    default:
        /* シーケンスアイドルに設定 */
        vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);
        vd_s_GyroI2cAbort((U1)MCU_I2C_ACK_GYRO);
        vd_s_GyroI2cAbort((U1)MCU_I2C_ACK_G_MONI);
        break;
    }
}

/*===================================================================================================================================*/
/*  static void     vd_s_GyroDevSeqGyrShutDn1(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevSeqGyrShutDn1(void)
{
    /* GYRO終了(1)処理シーケンス */

    U1              u1_t_sts;       /* I2C,サブ関数処理状況チェック */
    U1              u1_t_timchk;    /* 経過時間判定 */
    Dio_LevelType   dl_t_sts;       /* ポート読出し値 */

    u1_t_sts    = (U1)FALSE;
    u1_t_timchk = (U1)FALSE;
    dl_t_sts    = (Dio_LevelType)GYRO_DIO_LOW;

    /* Ackタイムアウト用カウンタインクリメント */
    if(u4_s_gyro_acktime < (U4)U4_MAX){
        u4_s_gyro_acktime++;
    }

    switch (st_s_gyro_seqmng.u1_step)
    {
    case (U1)GYRO_SEQ_SHUTDN1_1:
        /* SENSOR-ON端子状態取得処理 */
        dl_t_sts    = dl_GYRO_DIO_READ_SENSOR_ON();

        if(dl_t_sts == (Dio_LevelType)GYRO_DIO_LOW){
            /* フェール動作によりSENSOR-ON=Lo (センサ電源OFF) になっている */
            /* Set to sequence idle. */
            vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);
            /* Exit because SENSOR_ON is abnormal; end exit flow (1). */
            vd_s_GyroDevEventGo((U1)GYRO_EVENT_SHTDN_ERR);
        }
        else{
            /* カウンタクリア */
            u1_s_cnt_shutdn             = (U1)0U;
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_SHUTDN1_2;
        }
        break;

    case (U1)GYRO_SEQ_SHUTDN1_2:
        u1_t_sts    = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_GYRO,
                                                (U2)GYRO_WRISTEP_MODE_OFF_GYR,
                                                (U1)GP_I2C_MA_SLA_6_GYRO,
                                                st_sp_GYRO_WRISTEP_MODE_OFF_GYR,
                                                st_sp_MCU_SYS_PWR_GYR_REG_GYR_MODE_OFF);
        if(u1_t_sts == (U1)TRUE){
            /* GYROモードをSuspendに設定する */
            st_s_gyro_ctrl.u1_dev_mode  = (U1)GYRO_DEV_MODE_NORMAL;
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_SHUTDN1_3;
        }
        break;

    case (U1)GYRO_SEQ_SHUTDN1_3:
        /* Wati t21 */
        u1_t_timchk = u1_s_GyroDevTimCheck(u4_s_gyro_linktim, (U4)GYRO_WAIT_T21);
        if(u1_t_timchk  == (U1)TRUE){
            /* Wati t21完了 次のシーケンスへ */
            u4_s_gyro_linktim           = (U4)0U;
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_SHUTDN1_4;
        }
        else{
            if (u4_s_gyro_linktim < (U4)U4_MAX) {
                u4_s_gyro_linktim++;
            } else {
                u4_s_gyro_linktim = (U4)U4_MAX;
            }
        }
        break;

    case (U1)GYRO_SEQ_SHUTDN1_4:
        u1_t_sts    = u1_s_Gyro_I2cReadMgrFunc((U1)MCU_I2C_ACK_GYRO,
                                               (U1)GP_I2C_MA_SLA_6_GYRO,
                                               st_sp_MCU_SYS_PWR_GYR_REG_GYR_MODE_RD,
                                               (U1)MCU_I2C_WAIT_NON);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_step = (U1)GYRO_SEQ_SHUTDN1_5;
        }
        break;

    case (U1)GYRO_SEQ_SHUTDN1_5:
        if(st_sp_MCU_SYS_PWR_GYR_REG_GYR_MODE_RD[GYRO_READPOS_1].u1p_pdu[GYRO_READPOS_1] == (U1)GYRO_DAT_GYROMODE_SUSPEND){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_SHUTDN1_8;
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_PARASET2_1;
        }
        else{
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_step = (U1)GYRO_SEQ_SHUTDN1_6;
        }
        break;

    case (U1)GYRO_SEQ_SHUTDN1_6:
        /* Wati t18 */
        u1_t_timchk = u1_s_GyroDevTimCheck(u4_s_gyro_linktim, (U4)GYRO_WAIT_T18);
        if(u1_t_timchk  == (U1)TRUE){
            /* Wati t11完了 次のシーケンスへ */
            u4_s_gyro_linktim           = (U4)0U;
            st_s_gyro_seqmng.u1_step    = (U1)GYRO_SEQ_SHUTDN1_7;
        }
        else{
            if (u4_s_gyro_linktim < (U4)U4_MAX) {
                u4_s_gyro_linktim++;
            } else {
                u4_s_gyro_linktim = (U4)U4_MAX;
            }
        }
        break;

    case (U1)GYRO_SEQ_SHUTDN1_7:
        if(u1_s_cnt_shutdn >= (U1)GYRO_CNT_SHUTDN1_RTRY_MAX){
            /* カウンタクリア */
            u1_s_cnt_shutdn             = (U1)0U;

            /* ダイレコ記録 */
            vd_g_SysEcDrc_Drec((U1)SYSECDRC_DREC_CAT_GYROACC, (U1)SYSECDRC_DREC_ID_7, (U1)0x00U, (U1)0x00U);

            /* シーケンスアイドルに設定 */
            vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);

            /* リトライ回数オーバーなので終了フロー(1)を終了 */
            vd_s_GyroDevEventGo((U1)GYRO_EVENT_SHTDN_ERR);
        }
        else{
            if(u1_s_cnt_shutdn < (U1)U1_MAX){
                /* カウンタ+1 */
                u1_s_cnt_shutdn++;
            }
            else{
                u1_s_cnt_shutdn = (U1)U1_MAX;
            }

            /* 次のシーケンスへ(ModeChange(Gyro)OFFに戻る) */
            st_s_gyro_seqmng.u1_step = (U1)GYRO_SEQ_SHUTDN1_2;
        }
        break;

    case (U1)GYRO_SEQ_SHUTDN1_8:
        /* Wati t10(1ms待機)は本caseに到達した時点で満たしていると判断するためwait処理は実施しない */
        /* 次のシーケンスへ */
        st_s_gyro_seqmng.u1_step = (U1)GYRO_SEQ_SHUTDN1_9;
        break;

    case (U1)GYRO_SEQ_SHUTDN1_9:
        u1_t_sts    = u1_s_GyroDevParamSet2();
        if(u1_t_sts == (U1)GYRO_RET_OK){
            /* シーケンスアイドルに設定 */
            vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);

            /* 確認成功なので終了フロー(1)を終了 */
            vd_s_GyroDevEventGo((U1)GYRO_EVENT_SEQ_COMP);
        }
        break;

    default:
        /* シーケンスアイドルに設定 */
        vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);
        vd_s_GyroI2cAbort((U1)MCU_I2C_ACK_GYRO);
        break;
    }
}

/*===================================================================================================================================*/
/*  static U1       u1_s_GyroDevParamSet2(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_GyroDevParamSet2(void)
{
    U1              u1_t_ret;       /* シーケンス完了通知 */
    U1              u1_t_sts;       /* I2C,サブ関数処理状況チェック */
    U1              u1_t_impact;    /* 衝撃検知有効_出力確認 */
    Dio_LevelType   dl_t_sts;       /* ポート読出し値 */
    U2              u2_t_data_x;
    U2              u2_t_data_y;
    U2              u2_t_data_z;

    u1_t_ret    = (U1)GYRO_RET_INPROC;
    u1_t_sts    = (U1)FALSE;
    u1_t_impact = (U1)FALSE;
    dl_t_sts    = (Dio_LevelType)GYRO_DIO_LOW;

    switch (st_s_gyro_seqmng.u1_subtype)
    {
    case GYRO_SEQ_PARASET2_1:
        u1_t_impact = u1_s_GyroDev_ShockDetEnHoldChk();
        if(u1_t_impact  == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_PARASET2_2;
        }
        else{
            /* Flag Set */
            u1_s_gyrodev_gsensbkup_flg = (U1)TRUE;
            u1_s_gyrodev_gsensbkup_done_flg = (U1)FALSE;
            /* パラメータバックアップ処理に遷移 */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_PARASET2_10;
        }
        break;

    case (U1)GYRO_SEQ_PARASET2_2:
        u1_t_sts    = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                (U2)GYRO_WRISTEP_INPRM_SEN1_BW_ACC,
                                                (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                st_sp_GYRO_WRISTEP_INPRM_SEN1_BW_ACC,
                                                st_sp_MCU_SYS_PWR_GYR_REG_ACC_SEN1_BW_INPRM);
        if(u1_t_sts == (U1)TRUE){
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_PARASET2_3;
        }
        break;

    case (U1)GYRO_SEQ_PARASET2_3:
        /* Wati t19(1ms待機)は本caseに到達した時点で満たしていると判断するためwait処理は実施しない */
        /* カウンタクリア */
        u1_s_cnt_g_read         = (U1)0U;
        u2_s_cnt_diff_verif     = (U2)0U;

        /* 次のシーケンスへ */
        st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_PARASET2_4;
        break;

    case (U1)GYRO_SEQ_PARASET2_4:
        if(u2_s_cnt_diff_verif < (U2)U2_MAX){
            /* k(5_3)インクリメント */
            u2_s_cnt_diff_verif++;
        }
        else{
            u2_s_cnt_diff_verif = (U2)U2_MAX;
        }

        /* MAX,MINクリア */
        vd_s_GyroDevAccDataClear();

        /* 次のシーケンスへ */
        st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_PARASET2_5;
        break;

    case (U1)GYRO_SEQ_PARASET2_5:
        dl_t_sts    = dl_GYRO_DIO_READ_V33PERI();

        if(dl_t_sts == (Dio_LevelType)GYRO_DIO_HIGH){
            /* 終了フロー(1)の実施条件未達のため「GYRO終了(1)処理正常完了」へ遷移 */
            /* シーケンスアイドルに設定 */
            vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);

            /* 終了フロー(1)を終了 */
            vd_s_GyroDevEventGo((U1)GYRO_EVENT_SEQ_COMP);
        }
        else{
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_PARASET2_6;
        }
        break;

    case (U1)GYRO_SEQ_PARASET2_6:
        /* Read data (Gセンサ) */
        u1_t_sts    = u1_s_Gyro_I2cReadMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                               (U1)GP_I2C_MA_SLA_7_G_MONI,
                                               st_sp_MCU_SYS_PWR_GYR_REG_GYR_XYZ,
                                               (U1)MCU_I2C_WAIT_NON);
        if(u1_t_sts == (U1)TRUE){
            st_s_gyro_accdat.st_calc.u1_acc_x_lsb       = st_sp_MCU_SYS_PWR_GYR_REG_GYR_XYZ[GYRO_READPOS_1].u1p_pdu[GYRO_READPOS_1];
            st_s_gyro_accdat.st_calc.u1_acc_x_msb       = st_sp_MCU_SYS_PWR_GYR_REG_GYR_XYZ[GYRO_READPOS_1].u1p_pdu[GYRO_READPOS_2];
            st_s_gyro_accdat.st_calc.u1_acc_y_lsb       = st_sp_MCU_SYS_PWR_GYR_REG_GYR_XYZ[GYRO_READPOS_1].u1p_pdu[GYRO_READPOS_3];
            st_s_gyro_accdat.st_calc.u1_acc_y_msb       = st_sp_MCU_SYS_PWR_GYR_REG_GYR_XYZ[GYRO_READPOS_1].u1p_pdu[GYRO_READPOS_4];
            st_s_gyro_accdat.st_calc.u1_acc_z_lsb       = st_sp_MCU_SYS_PWR_GYR_REG_GYR_XYZ[GYRO_READPOS_1].u1p_pdu[GYRO_READPOS_5];
            st_s_gyro_accdat.st_calc.u1_acc_z_msb       = st_sp_MCU_SYS_PWR_GYR_REG_GYR_XYZ[GYRO_READPOS_1].u1p_pdu[GYRO_READPOS_6];

            u2_t_data_x    = (U2)(((U2)st_s_gyro_accdat.st_calc.u1_acc_x_msb << (U2)GYRO_SHIFT_8) | (U2)st_s_gyro_accdat.st_calc.u1_acc_x_lsb);
            u2_t_data_y    = (U2)(((U2)st_s_gyro_accdat.st_calc.u1_acc_y_msb << (U2)GYRO_SHIFT_8) | (U2)st_s_gyro_accdat.st_calc.u1_acc_y_lsb);
            u2_t_data_z    = (U2)(((U2)st_s_gyro_accdat.st_calc.u1_acc_z_msb << (U2)GYRO_SHIFT_8) | (U2)st_s_gyro_accdat.st_calc.u1_acc_z_lsb);

            st_s_gyro_accdat.st_calc.st_acc_xyz.s2_x    = (S2)u2_t_data_x;
            st_s_gyro_accdat.st_calc.st_acc_xyz.s2_y    = (S2)u2_t_data_y;
            st_s_gyro_accdat.st_calc.st_acc_xyz.s2_z    = (S2)u2_t_data_z;


            if(u1_s_cnt_g_read < (U1)U1_MAX){
                /* GセンサRead回数(k(5_2))カウント */
                u1_s_cnt_g_read++;
            }
            else{
                u1_s_cnt_g_read = (U1)U1_MAX;
            }
            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_PARASET2_7;
        }
        break;

    case (U1)GYRO_SEQ_PARASET2_7:
        /* GセンサMAX,MIN更新 */
        vd_s_GyroDevAccMinMaxUpdate();

        /* 次のシーケンスへ */
        st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_PARASET2_8;
        break;

    case (U1)GYRO_SEQ_PARASET2_8:
        /* Wati t20(1ms待機)は本caseに到達した時点で満たしていると判断するためwait処理は実施しない */
        /* GセンサRead回数(k(5_2))が規定回数に到達したかチェック */
        if(u1_s_cnt_g_read > (U1)GYRO_CNT_PARASET_ACC_READ){
            /* GセンサRead回数(k(5_2))クリア */
            u1_s_cnt_g_read = (U1)0U;

            /* 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_PARASET2_9;
        }
        else{
            /* GセンサReadに遷移 */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_PARASET2_5;
        }
        break;

    case (U1)GYRO_SEQ_PARASET2_9:
        /* 差分確認|MAX-MIN|処理 */
        u1_t_sts = u1_s_GyroDevAccMinMaxCheck();

        /* 比較結果チェック */
        if(u1_t_sts != (U1)GYRO_RET_OK){
            /* 差分確認回数(k(5_3))チェック */
            if(u2_s_cnt_diff_verif < (U2)GYRO_CNT_PARASET_ACC_VERI){
                /* 規定回数未満のため再Read,比較に遷移 */
                st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_PARASET2_4;
            }
            else{
                /* 規定回数到達 入力パラメータ設定(2)終了 */
                u1_t_ret    = (U1)GYRO_RET_OK;
            }
        }
        else{
            u1_s_gyrodev_gsensbkup_flg = (U1)TRUE;
            u1_s_gyrodev_gsensbkup_done_flg = (U1)FALSE;
            /* 規定G値未満 次のシーケンスへ */
            st_s_gyro_seqmng.u1_subtype = (U1)GYRO_SEQ_PARASET2_10;
        }
        break;

    case (U1)GYRO_SEQ_PARASET2_10:
        /* "入力パラメータ保持" で保持していた設定を書込み */
        /* ToDo：IFの挿入 */
        if(u1_s_gyrodev_gsensbkup_done_flg == (U1)TRUE){
            /* 入力パラメータ設定(2)終了 */
            u1_t_ret    = (U1)GYRO_RET_OK;
        }
        break;

    default:
        /* シーケンスアイドルに設定 */
        vd_s_GyroDevSeqSet((U1)GYRO_SEQ_IDLE);
        vd_s_GyroI2cAbort((U1)MCU_I2C_ACK_G_MONI);
        break;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static void     vd_s_GyroDevAccDataClear(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevAccDataClear(void)
{
    /* MAX値、MIN値クリア処理 */

    U1  u1_t_errflg_bk;

    /* エラーログ退避 */
    u1_t_errflg_bk  = st_s_gyro_accdat.u1_errlog_sts;

    /* MAX値、MIN値クリア処理 */
    vd_s_GyroDevMemset(&st_s_gyro_accdat,     (U1)0U, (U4)sizeof(st_s_gyro_accdat));

    /* エラーログあった場合、フラグ保留 */
    if(u1_t_errflg_bk   == (U1)TRUE){
        st_s_gyro_accdat.u1_errlog_sts  = (U1)TRUE;
    }
    else{
        /* do nothing */
    }
}

/*===================================================================================================================================*/
/*  static void     vd_s_GyroDevAccMinMaxUpdate(void)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevAccMinMaxUpdate(void)
{
    /* X軸、Y軸、Z軸の取得データに対して、それぞれのMAX値とMIN値を更新する */

    if(st_s_gyro_accdat.u1_updatecnt == (U1)0U){
        /* 初回更新時は判定せずに更新する */
        st_s_gyro_accdat.st_max = st_s_gyro_accdat.st_calc.st_acc_xyz;
        st_s_gyro_accdat.st_min = st_s_gyro_accdat.st_calc.st_acc_xyz;
    }
    else{
        /* 初回更新移行 */
        /* X軸 */
        if(st_s_gyro_accdat.st_calc.st_acc_xyz.s2_x > st_s_gyro_accdat.st_max.s2_x){
            st_s_gyro_accdat.st_max.s2_x = st_s_gyro_accdat.st_calc.st_acc_xyz.s2_x;
        }
        else if(st_s_gyro_accdat.st_calc.st_acc_xyz.s2_x < st_s_gyro_accdat.st_min.s2_x){
            st_s_gyro_accdat.st_min.s2_x = st_s_gyro_accdat.st_calc.st_acc_xyz.s2_x;
        }
        else{
            /* do nothing */
        }

        /* Y軸 */
        if(st_s_gyro_accdat.st_calc.st_acc_xyz.s2_y > st_s_gyro_accdat.st_max.s2_y){
            st_s_gyro_accdat.st_max.s2_y = st_s_gyro_accdat.st_calc.st_acc_xyz.s2_y;
        }
        else if(st_s_gyro_accdat.st_calc.st_acc_xyz.s2_y < st_s_gyro_accdat.st_min.s2_y){
            st_s_gyro_accdat.st_min.s2_y = st_s_gyro_accdat.st_calc.st_acc_xyz.s2_y;
        }
        else{
            /* do nothing */
        }

        /* Z軸 */
        if(st_s_gyro_accdat.st_calc.st_acc_xyz.s2_z > st_s_gyro_accdat.st_max.s2_z){
            st_s_gyro_accdat.st_max.s2_z = st_s_gyro_accdat.st_calc.st_acc_xyz.s2_z;
        }
        else if(st_s_gyro_accdat.st_calc.st_acc_xyz.s2_z < st_s_gyro_accdat.st_min.s2_z){
            st_s_gyro_accdat.st_min.s2_z = st_s_gyro_accdat.st_calc.st_acc_xyz.s2_z;
        }
        else{
            /* do nothing */
        }
    }
    if(st_s_gyro_accdat.u1_updatecnt < (U1)U1_MAX){
        /* 更新回数インクリメント */
        st_s_gyro_accdat.u1_updatecnt++;
    }
    else{
        st_s_gyro_accdat.u1_updatecnt = (U1)U1_MAX;
    }
}


/*===================================================================================================================================*/
/*  static U1       u1_s_GyroDevAccMinMaxCheck(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_GyroDevAccMinMaxCheck(void)
{
    U1      u1_t_ret;
    S4      s4_t_modval;

    u1_t_ret    = (U1)GYRO_RET_OK;  /* 差分確認成功 */
    s4_t_modval = (S4)0U;

    /* ダイレコ記録(1回だけ) */
    if((st_s_gyro_accdat.u1_updatecnt < (U1)GYRO_CNT_PARASET_ACC_READ)   &&
       (st_s_gyro_accdat.u1_errlog_sts == (U1)FALSE)){
        /* ToDo：ダイレコ記録用IFの挿入 */
        st_s_gyro_accdat.u1_errlog_sts = (U1)TRUE;
    }

    /* 軸情報有効個数50個未満チェック */
    if(st_s_gyro_accdat.u1_updatecnt < (U1)GYRO_CNT_PARASET_ACC_READERR){
        /* 軸情報有効個数50個未満の場合、エラーで戻る */
        u1_t_ret    = (U1)GYRO_RET_NG;
    }
    else{
        /* |MAX-MIN|をチェック処理 */
        /* X軸 */
        s4_t_modval = (S4)((S4)st_s_gyro_accdat.st_max.s2_x - (S4)st_s_gyro_accdat.st_min.s2_x);
        if(s4_t_modval >= (S4)GYRO_CNT_PARASET_ACC_FIX_STAB){
            /* 差分確認失敗 */
            u1_t_ret    = (U1)GYRO_RET_NG;
        }
        /* Y軸 */
        s4_t_modval = (S4)((S4)st_s_gyro_accdat.st_max.s2_y - (S4)st_s_gyro_accdat.st_min.s2_y);
        if(s4_t_modval >= (S4)GYRO_CNT_PARASET_ACC_FIX_STAB){
            /* 差分確認失敗 */
            u1_t_ret    = (U1)GYRO_RET_NG;
        }
        /* X軸 */
        s4_t_modval = (S4)((S4)st_s_gyro_accdat.st_max.s2_z - (S4)st_s_gyro_accdat.st_min.s2_z);
        if(s4_t_modval >= (S4)GYRO_CNT_PARASET_ACC_FIX_STAB){
            /* 差分確認失敗 */
            u1_t_ret    = (U1)GYRO_RET_NG;
        }
    }

    return(u1_t_ret);
}

/**************************↑シーケンス管理(END)↑***************************/

/**************************↓共通関数(START)↓*************************/
/*===================================================================================================================================*/
/*  static void     vd_s_GyroDevMemset(void * vdp_a_dst, const U1 u1_a_DATA, U4 u4_a_size)                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevMemset(void * vdp_a_dst, const U1 u1_a_DATA, U4 u4_a_size)
{
    U1 * u1p_udst;
    U4   u4_t_cnt;

    u1p_udst = (U1 *)vdp_a_dst;

    for(u4_t_cnt = (U4)0U; u4_t_cnt < u4_a_size; u4_t_cnt++){
        u1p_udst[u4_t_cnt] = u1_a_DATA;
    }
}

/*===================================================================================================================================*/
/* static void     vd_s_GyroDevForceEnd(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GyroDevForceEnd(void)
{
    /* SENSOR_ON LO処理 */
    dl_GYRO_DIO_WRITE_SENSOR_ON_L();

    /* ジャイロモードをSuspendに設定する */
    st_s_gyro_ctrl.u1_dev_mode  = (U1)GYRO_DEV_MODE_SUSPEND;
}

/*===================================================================================================================================*/
/* static U1       u1_s_GyroDevTimCheck(const U4 u4_a_SRC, const U4 u4_a_TRGT)                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_GyroDevTimCheck(const U4 u4_a_SRC, const U4 u4_a_TRGT)
{
    U1      u1_t_ret;

    u1_t_ret    = (U1)FALSE;

    if(u4_a_SRC >= u4_a_TRGT){
        u1_t_ret    = (U1)TRUE;
    }

    return(u1_t_ret);
}
/**************************↑共通関数(END)↑***************************/




/*===================================================================================================================================*/
/*  void    vd_g_GyroDev_Routine(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GyroDev_Routine(void)
{
    U1  u1_t_modests;                                                               /* Gyro G-Sensor Power ON Maneger Mode Status */
    U1  u1_t_backupsts;

    switch (u1_s_gyrodev_state){
        case GYRODEV_SEQ_IDLE:                                                      /* IDLE */
            /* Timer Clear */
            u4_s_gyrodev_cycchk_timer = (U4)0;
            vd_g_Rim_WriteU4((U2)RIMID_U4_GYRO_CYCCHK_TIMER, u4_s_gyrodev_cycchk_timer);

            /* Power ON Check */
            u1_t_modests = u1_s_GyroDevCtlMngModGet();
            if (u1_t_modests == (U1)GYRO_MODE_NORM){                                /* Mode : NORM        */
                /* State Update */
                u1_s_gyrodev_state = (U1)GYRODEV_SEQ_CYC;
                vd_g_Rim_WriteU1((U2)RIMID_U1_GYRO_STS, u1_s_gyrodev_state);
                /* Poling Check Start */
                u4_s_gyrodev_cycchk_timer = (U4)GYRODEV_CYCCHK_POLING;
                vd_g_Rim_WriteU4((U2)RIMID_U4_GYRO_CYCCHK_TIMER, u4_s_gyrodev_cycchk_timer);
            }
            break;
        case GYRODEV_SEQ_CYC:                                                       /* CYCLIC */
            vd_s_GyroDev_CycChk();
            if((u1_s_gyrodev_gsensbkup_flg == (U1)TRUE)
            && (u1_s_gyrodev_notifcondset_sts == GYRODEV_NOTIFCONDSET_STEP0)
            && (u1_s_gyrodev_ctrloutset_sts == GYRODEV_CTRLOUTSET_STEP0)){
                /* Flag Clear */
                u1_s_gyrodev_gsensbkup_flg = (U1)FALSE;
                /* State Update */
                u1_s_gyrodev_state = (U1)GYRODEV_SEQ_BKUP;
                vd_g_Rim_WriteU1((U2)RIMID_U1_GYRO_STS, u1_s_gyrodev_state);
            }
            break;
        case GYRODEV_SEQ_BKUP:                                                      /* BACKUP */
            u1_t_backupsts = u1_s_GyroDev_ParamBackup();
            if(u1_t_backupsts == (U1)TRUE){
                u1_s_gyrodev_gsensbkup_done_flg = (U1)TRUE;
                /* State Update */
                u1_s_gyrodev_state = (U1)GYRODEV_SEQ_CYC;
                vd_g_Rim_WriteU1((U2)RIMID_U1_GYRO_STS, u1_s_gyrodev_state);
            }
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
    if(u4_s_gyrodev_cycchk_timer < (U4)U4_MAX){
        u4_s_gyrodev_cycchk_timer++;
        vd_g_Rim_WriteU4((U2)RIMID_U4_GYRO_CYCCHK_TIMER, u4_s_gyrodev_cycchk_timer);
    }
}

/*===================================================================================================================================*/
/*  void    vd_s_GyroDev_CycChk(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GyroDev_CycChk(void)
{
    U1             u1_t_func_sts;                                          /* Function Status */
    U1             u1_t_time_chk_flg;
    U1             u1_t_reg_req_sts;                                       /* Register Read/Write Request Status */
    Dio_LevelType  dl_t_sts;                                               /* V33-Peri-On Port Status */
    U1             u1_t_modests;                                           /* Gyro G-Sensor Power ON Maneger Mode Status */
    U1             u1_t_gyro_x_lsb_data;                                   /* Gyro Register X_LSB Data */
    U1             u1_t_gyro_x_msb_data;                                   /* Gyro Register X_MSB Data */
    U1             u1_t_gyro_y_lsb_data;                                   /* Gyro Register Y_LSB Data */
    U1             u1_t_gyro_y_msb_data;                                   /* Gyro Register Y_MSB Data */
    U1             u1_t_gyro_z_lsb_data;                                   /* Gyro Register Z_LSB Data */
    U1             u1_t_gyro_z_msb_data;                                   /* Gyro Register Z_MSB Data */
    U2             u2_t_gyro_x_data;                                       /* Gyro Register X_Data */
    U2             u2_t_gyro_y_data;                                       /* Gyro Register Y_Data */
    U2             u2_t_gyro_z_data;                                       /* Gyro Register Z_Data */
    U1             u1_t_gyro_xyz_range_data;                               /* Gyro Register XYZ Range Data */
    U1             u1_t_gsens_x_lsb_data;                                  /* G-Sensor Register X_LSB Data */
    U1             u1_t_gsens_x_msb_data;                                  /* G-Sensor Register X_MSB Data */
    U1             u1_t_gsens_y_lsb_data;                                  /* G-Sensor Register Y_LSB Data */
    U1             u1_t_gsens_y_msb_data;                                  /* G-Sensor Register Y_MSB Data */
    U1             u1_t_gsens_z_lsb_data;                                  /* G-Sensor Register Z_LSB Data */
    U1             u1_t_gsens_z_msb_data;                                  /* G-Sensor Register Z_MSB Data */
    U1             u1_t_gsens_temp_msb_data;                               /* G-Sensor Register Temperature MSB Data */
    U2             u2_t_gsens_x_data;                                      /* G-Sensor Register X Data */
    U2             u2_t_gsens_y_data;                                      /* G-Sensor Register Y Data */
    U2             u2_t_gsens_z_data;                                      /* G-Sensor Register Z Data */
    U1             u1_t_gsens_xyz_range_data;                              /* G-Sensor Register XYZ Range Data */

    u1_t_func_sts = (U1)FALSE;

    switch (u1_s_gyrodev_cycchk_sts){
        case GYRODEV_CYCCHK_STEP0:                                      /* STEP0 */
            u1_t_time_chk_flg = u1_s_GyroDevTimCheck(u4_s_gyrodev_cycchk_timer, GYRODEV_CYCCHK_POLING);
            if(u1_t_time_chk_flg == (U1)TRUE){
                u1_t_modests = u1_s_GyroDevCtlMngModGet();
                if(u1_t_modests == (U1)GYRO_MODE_NORM){
                    if((u1_s_gyrodev_gyro_read_complete_flag == (U1)FALSE)
                    && (u1_s_gyrodev_gsens_read_complete_flag == (U1)FALSE)){
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
                    }
                    if(u1_s_gyrodev_gyro_read_complete_flag == (U1)FALSE){
                        /* Read Register Gyro */
                        u1_t_reg_req_sts = u1_s_Gyro_I2cReadMgrFunc((U1)MCU_I2C_ACK_GYRO,
                                                                    (U1)GP_I2C_MA_SLA_6_GYRO,
                                                                    st_sp_GYRODEV_GYRODATA_RD_TBL,
                                                                    (U1)MCU_I2C_WAIT_NON);
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

                            u1_s_gyrodev_gyro_read_complete_flag = (U1)TRUE;
                        }
                    }
                    if(u1_s_gyrodev_gsens_read_complete_flag == (U1)FALSE){
                        /* Read Register G-Sensor */
                        u1_t_reg_req_sts = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                                     (U2)GYRODEV_GSENSDATA_RD_WRINUM,
                                                                     (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                                     GYRODEV_GSENSDATA_RD,
                                                                     st_sp_GYRODEV_GSENSDATA_RD_TBL);
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

                            u1_t_gsens_temp_msb_data = st_sp_GYRODEV_GSENSDATA_RD_TBL[3].u1p_pdu[1];

                            /* G-Sensor Read Data Create */
                            st_gyrodev_readdata.u1_accl_temp_data_down = st_sp_GYRODEV_GSENSDATA_RD_TBL[3].u1p_pdu[2];
                            st_gyrodev_readdata.u1_accl_temp_data_up = u1_t_gsens_temp_msb_data;

                            u1_t_gsens_xyz_range_data = (U1)GYRODEV_GSENS_RANGE_DATA;
                            if(u1_t_gsens_xyz_range_data < (U1)GYRODEV_GSENS_RANGE_NUM){
                                st_gyrodev_readdata.st_gyro_reso.u2_accel_xyz_reso = (U2)u2_sp_GYRODEV_GSENS_RANGE_RESO_CONV_TBL[u1_t_gsens_xyz_range_data];
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
                            u1_s_gyrodev_gsens_read_complete_flag = (U1)TRUE;
                        }
                    }
                    if((u1_s_gyrodev_gyro_read_complete_flag == (U1)TRUE)
                    && (u1_s_gyrodev_gsens_read_complete_flag == (U1)TRUE)){
                        /* Timer Clear */
                        if(u4_s_gyrodev_cycchk_timer >= (U4)GYRODEV_CYCCHK_POLING){
                            u4_s_gyrodev_cycchk_timer -= (U4)GYRODEV_CYCCHK_POLING;
                            vd_g_Rim_WriteU4((U2)RIMID_U4_GYRO_CYCCHK_TIMER, u4_s_gyrodev_cycchk_timer);
                        }
                        else{
                            u4_s_gyrodev_cycchk_timer = (U4)0;
                            vd_g_Rim_WriteU4((U2)RIMID_U4_GYRO_CYCCHK_TIMER, u4_s_gyrodev_cycchk_timer);
                        }
                        /* Read Data Notificaiton */
                        vd_GYRODEV_OSCMD_GYRO_DATA_NOTIF(st_gyrodev_readdata);
                        /* Execute only STEP0 of the function */
                        u1_t_func_sts = u1_s_GyroDev_GSensNotifCondFunc((U1)GYRODEV_GSENS_NOTIFCONDFUNC_SETREQ);
                        if(u1_t_func_sts == (U1)FALSE){
                            /* Next Process */
                            u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP1;
                            vd_g_Rim_WriteU1((U2)RIMID_U1_GYRO_CYCCHK_STS, u1_s_gyrodev_cycchk_sts);
                        }
                        else{
                            /* Execute only STEP0 of the function */
                            u1_t_func_sts = u1_s_GyroDev_GSensCtrlOutFunc((U1)GYRODEV_GSENS_CTRLOUTFUNC_SETREQ);
                            if(u1_t_func_sts == (U1)FALSE){
                                /* Next Process */
                                u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP2;
                                vd_g_Rim_WriteU1((U2)RIMID_U1_GYRO_CYCCHK_STS, u1_s_gyrodev_cycchk_sts);
                            }
                            else{
                                /* Next Process */
                                vd_s_GyroDev_AppChk();
                            }
                        }
                        /* Flag Clear */
                        u1_s_gyrodev_gyro_read_complete_flag = (U1)FALSE;
                        u1_s_gyrodev_gsens_read_complete_flag = (U1)FALSE;
                    }
                    /* Flag Clear */
                    u1_s_gyrodev_gsensbkup_flg = (U1)FALSE;
                }
                else{
                    /* Timer Clear */
                    u4_s_gyrodev_cycchk_timer = (U4)0;
                    vd_g_Rim_WriteU4((U2)RIMID_U4_GYRO_CYCCHK_TIMER, u4_s_gyrodev_cycchk_timer);
                }
            }
            break;
        case GYRODEV_CYCCHK_STEP1:                                      /* STEP1 */
            u1_t_func_sts = u1_s_GyroDev_GSensNotifCondFunc((U1)GYRODEV_GSENS_NOTIFCONDFUNC_SETREQ);
            if(u1_t_func_sts == (U1)TRUE){
                /* Execute only STEP0 of the function */
                u1_t_func_sts = u1_s_GyroDev_GSensCtrlOutFunc((U1)GYRODEV_GSENS_CTRLOUTFUNC_SETREQ);
                if(u1_t_func_sts == (U1)FALSE){
                    /* Next Process */
                    u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP2;
                    vd_g_Rim_WriteU1((U2)RIMID_U1_GYRO_CYCCHK_STS, u1_s_gyrodev_cycchk_sts);
                }
                else{
                    /* Next Process */
                    vd_s_GyroDev_AppChk();
                }
            }
            break;
        case GYRODEV_CYCCHK_STEP2:                                      /* STEP2 */
            u1_t_func_sts = u1_s_GyroDev_GSensCtrlOutFunc((U1)GYRODEV_GSENS_CTRLOUTFUNC_SETREQ);
            if(u1_t_func_sts == (U1)TRUE){
                /* Next Process */
                vd_s_GyroDev_AppChk();
            }
            break;
        case GYRODEV_CYCCHK_STEP3:                                      /* STEP3 */
            u1_t_func_sts = u1_s_GyroDev_GSensNotifCondFunc((U1)GYRODEV_GSENS_NOTIFCONDFUNC_BACKUP);
            if(u1_t_func_sts == (U1)TRUE){
                /* Execute only STEP0 of the function */
                u1_t_func_sts = u1_s_GyroDev_GSensCtrlOutFunc((U1)GYRODEV_GSENS_CTRLOUTFUNC_BACKUP);
                if(u1_t_func_sts == (U1)FALSE){
                    /* Next Process */
                    u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP4;
                    vd_g_Rim_WriteU1((U2)RIMID_U1_GYRO_CYCCHK_STS, u1_s_gyrodev_cycchk_sts);
                }
                else{
                    /* Next Process */
                    u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP5;
                    vd_g_Rim_WriteU1((U2)RIMID_U1_GYRO_CYCCHK_STS, u1_s_gyrodev_cycchk_sts);
                }
            }
            break;
        case GYRODEV_CYCCHK_STEP4:                                      /* STEP4 */
            u1_t_func_sts = u1_s_GyroDev_GSensCtrlOutFunc((U1)GYRODEV_GSENS_CTRLOUTFUNC_BACKUP);
            if(u1_t_func_sts == (U1)TRUE){
                /* Execute only STEP0 of the function */
                u1_t_func_sts = u1_s_GyroDev_GSensNotifCondFunc((U1)GYRODEV_GSENS_NOTIFCONDFUNC_READREQ);
                if(u1_t_func_sts == (U1)FALSE){
                    /* Next Process */
                    u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP5;
                    vd_g_Rim_WriteU1((U2)RIMID_U1_GYRO_CYCCHK_STS, u1_s_gyrodev_cycchk_sts);
                }
                else{
                    /* Next Process */
                    u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP0;
                    vd_g_Rim_WriteU1((U2)RIMID_U1_GYRO_CYCCHK_STS, u1_s_gyrodev_cycchk_sts);
                }
            }
            break;
        case GYRODEV_CYCCHK_STEP5:                                      /* STEP5 */
            u1_t_func_sts = u1_s_GyroDev_GSensNotifCondFunc((U1)GYRODEV_GSENS_NOTIFCONDFUNC_READREQ);
            if(u1_t_func_sts == (U1)TRUE){
                /* Process Reset */
                u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP0;
                vd_g_Rim_WriteU1((U2)RIMID_U1_GYRO_CYCCHK_STS, u1_s_gyrodev_cycchk_sts);
            }
            break;
        default:                                                        /* FAIL */
            /* State Reset */
            u1_s_gyrodev_state = (U1)GYRODEV_SEQ_IDLE;
            vd_g_Rim_WriteU1((U2)RIMID_U1_GYRO_STS, u1_s_gyrodev_state);
            /* Process Reset */
            u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP0;
            vd_g_Rim_WriteU1((U2)RIMID_U1_GYRO_CYCCHK_STS, u1_s_gyrodev_cycchk_sts);
            vd_s_GyroI2cAbort((U1)MCU_I2C_ACK_GYRO);
            vd_s_GyroI2cAbort((U1)MCU_I2C_ACK_G_MONI);
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
    U1      u1_t_error_flag;                                        /* Register Read Data Error Flag */
    U2      u2_t_last_pls;                                          /* Register Read/Write Request Status */

    u1_t_error_flag = (U1)FALSE;

    u2_t_last_pls = u2_GYRODEV_GET_LAST_PLS();
    if((u2_t_last_pls == (U2)GYRODEV_LAST_PLS_STOP)
    || (u2_t_last_pls > (U2)GYRODEV_LAST_PLS_8KM)){
        /* MAX Freeze Chek */
        if((u2_a_x_data == (U2)GYRODEV_GYRODTC_XYZ_MAX)
        || (u2_a_y_data == (U2)GYRODEV_GYRODTC_XYZ_MAX)
        || (u2_a_z_data == (U2)GYRODEV_GYRODTC_XYZ_MAX)){        /* MAX Freeze */
            u1_t_error_flag = (U1)TRUE;
            if(u2_s_gyrodev_gyro_max_err_cnt < (U2)GYRODEV_GYRODTC_XYZ_MAX_ERRCNT_MAX){    /* Error Count <= n(6_1) */
                u2_s_gyrodev_gyro_max_err_cnt++;
                vd_g_Rim_WriteU2((U2)RIMID_U2_GYRO_MAX_ERR, u2_s_gyrodev_gyro_max_err_cnt);
            }
        }
        /* MIN Freeze Chek */
        if((u2_a_x_data == (U2)GYRODEV_GYRODTC_XYZ_MIN)
        || (u2_a_y_data == (U2)GYRODEV_GYRODTC_XYZ_MIN)
        || (u2_a_z_data == (U2)GYRODEV_GYRODTC_XYZ_MIN)){        /* MIN Freeze */
            u1_t_error_flag = (U1)TRUE;
            if(u2_s_gyrodev_gyro_min_err_cnt < (U2)GYRODEV_GYRODTC_XYZ_MIN_ERRCNT_MAX){    /* Error Count <= n(6_2) */
                u2_s_gyrodev_gyro_min_err_cnt++;
                vd_g_Rim_WriteU2((U2)RIMID_U2_GYRO_MIN_ERR, u2_s_gyrodev_gyro_min_err_cnt);
            }
        }

        if(u1_t_error_flag == (U1)TRUE){                        /* Read Data Error */
            if((u2_s_gyrodev_gyro_max_err_cnt >= (U2)GYRODEV_GYRODTC_XYZ_MAX_ERRCNT_MAX)
            || (u2_s_gyrodev_gyro_min_err_cnt >= (U2)GYRODEV_GYRODTC_XYZ_MIN_ERRCNT_MAX)){
                /* Error Counter Clear */
                u2_s_gyrodev_gyro_max_err_cnt = (U2)0;
                vd_g_Rim_WriteU2((U2)RIMID_U2_GYRO_MAX_ERR, u2_s_gyrodev_gyro_max_err_cnt);
                u2_s_gyrodev_gyro_min_err_cnt = (U2)0;
                vd_g_Rim_WriteU2((U2)RIMID_U2_GYRO_MIN_ERR, u2_s_gyrodev_gyro_min_err_cnt);

                vd_GYRODEV_DREC_REQ((U1)SYSECDRC_DREC_ID_4, (U1)0x00U, (U1)0x00U);

                /* Gyro Fail DTC Record */
                vd_GYRODEV_DTC_REQ((U1)DTCCTL_DTCID_GYR_ERR, (U1)GYRODEV_DTC_STS_FAIL);
                u1_s_gyrodev_gyro_dtcrec_a_flag = (U1)FALSE;

                if(u1_s_gyrodev_gyro_rst_cnt >= (U2)GYRODEV_GYRODTC_RSTCNT_MAX){    /* Reset Count >= n(6_3) */
                    /* Counter Clear */
                    u2_s_gyrodev_gyro_max_err_cnt = (U2)0;
                    vd_g_Rim_WriteU2((U2)RIMID_U2_GYRO_MAX_ERR, u2_s_gyrodev_gyro_max_err_cnt);
                    u2_s_gyrodev_gyro_min_err_cnt = (U2)0;
                    vd_g_Rim_WriteU2((U2)RIMID_U2_GYRO_MIN_ERR, u2_s_gyrodev_gyro_min_err_cnt);
                    u1_s_gyrodev_gyro_rst_cnt = (U1)0;
                    vd_g_Rim_WriteU1((U2)RIMID_U1_GYRO_RST, u1_s_gyrodev_gyro_rst_cnt);
                    /* Event Set */
                    vd_s_GyroDevEventGo((U1)GYRODEV_EVENT_DTC_ERR);
                    /* State Reset */
                    u1_s_gyrodev_state = (U1)GYRODEV_SEQ_IDLE;
                    vd_g_Rim_WriteU1((U2)RIMID_U1_GYRO_STS, u1_s_gyrodev_state);
                    /* Process Reset */
                    u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP0;
                    vd_g_Rim_WriteU1((U2)RIMID_U1_GYRO_CYCCHK_STS, u1_s_gyrodev_cycchk_sts);

                }
                else{
                    if(u1_s_gyrodev_gyro_rst_cnt < (U1)U1_MAX){
                        u1_s_gyrodev_gyro_rst_cnt++;
                    }
                    else{
                        u1_s_gyrodev_gyro_rst_cnt = (U1)U1_MAX;
                    }
                    vd_g_Rim_WriteU1((U2)RIMID_U1_GYRO_RST, u1_s_gyrodev_gyro_rst_cnt);
                    /* Event Set */
                    vd_s_GyroDevEventGo((U1)GYRODEV_EVENT_DEV_RST);
                    /* State Reset */
                    u1_s_gyrodev_state = (U1)GYRODEV_SEQ_IDLE;
                    vd_g_Rim_WriteU1((U2)RIMID_U1_GYRO_STS, u1_s_gyrodev_state);

                    /* Process Reset */
                    u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP0;
                    vd_g_Rim_WriteU1((U2)RIMID_U1_GYRO_CYCCHK_STS, u1_s_gyrodev_cycchk_sts);
                }
            }
        }
        else{
            /* Error Counter Clear */
            u2_s_gyrodev_gyro_max_err_cnt = (U2)0;
            vd_g_Rim_WriteU2((U2)RIMID_U2_GYRO_MAX_ERR, u2_s_gyrodev_gyro_max_err_cnt);
            u2_s_gyrodev_gyro_min_err_cnt = (U2)0;
            vd_g_Rim_WriteU2((U2)RIMID_U2_GYRO_MIN_ERR, u2_s_gyrodev_gyro_min_err_cnt);
            u1_s_gyrodev_gyro_rst_cnt = (U1)0;
            vd_g_Rim_WriteU1((U2)RIMID_U1_GYRO_RST, u1_s_gyrodev_gyro_rst_cnt);

            /* DTC Record Check */
            if(u1_s_gyrodev_gyro_dtcrec_a_flag == (U1)FALSE){                       /* Initial Record or Error -> Normal */
                /* Gyro Normal DTC Record */
                vd_GYRODEV_DTC_REQ((U1)DTCCTL_DTCID_GYR_ERR, (U1)GYRODEV_DTC_STS_NORMAL);
                u1_s_gyrodev_gyro_dtcrec_a_flag = (U1)TRUE;
            }
        }
    }
    else{
        /* Error Counter Clear */
        u2_s_gyrodev_gyro_max_err_cnt = (U2)0;
        vd_g_Rim_WriteU2((U2)RIMID_U2_GYRO_MAX_ERR, u2_s_gyrodev_gyro_max_err_cnt);
        u2_s_gyrodev_gyro_min_err_cnt = (U2)0;
        vd_g_Rim_WriteU2((U2)RIMID_U2_GYRO_MIN_ERR, u2_s_gyrodev_gyro_min_err_cnt);
        u1_s_gyrodev_gyro_rst_cnt = (U1)0;
        vd_g_Rim_WriteU1((U2)RIMID_U1_GYRO_RST, u1_s_gyrodev_gyro_rst_cnt);
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
            vd_g_Rim_WriteU2((U2)RIMID_U2_GSENS_MAX_ERR, u2_s_gyrodev_gsens_max_err_cnt);
        }
    }
    /* MIN Freeze Chek */
    if((u2_a_x_data == (U2)GYRODEV_GSENSDTC_XYZ_MIN)
    || (u2_a_y_data == (U2)GYRODEV_GSENSDTC_XYZ_MIN)
    || (u2_a_z_data == (U2)GYRODEV_GSENSDTC_XYZ_MIN)){        /* MIN Freeze */
        u1_t_error_flag = (U1)TRUE;
        if(u2_s_gyrodev_gsens_min_err_cnt <= (U2)GYRODEV_GSENSDTC_XYZ_MIN_ERRCNT_MAX){    /* Error Count <= n(6_2) */
            u2_s_gyrodev_gsens_min_err_cnt++;
            vd_g_Rim_WriteU2((U2)RIMID_U2_GSENS_MIN_ERR, u2_s_gyrodev_gsens_min_err_cnt);
        }
    }

    if(u1_t_error_flag == (U1)TRUE){                        /* Read Data Error */
        if((u2_s_gyrodev_gsens_max_err_cnt > (U2)GYRODEV_GSENSDTC_XYZ_MAX_ERRCNT_MAX)
        || (u2_s_gyrodev_gsens_min_err_cnt > (U2)GYRODEV_GSENSDTC_XYZ_MIN_ERRCNT_MAX)){
            /* Error Counter Clear */
            u2_s_gyrodev_gsens_max_err_cnt = (U2)0;
            vd_g_Rim_WriteU2((U2)RIMID_U2_GSENS_MAX_ERR, u2_s_gyrodev_gsens_max_err_cnt);
            u2_s_gyrodev_gsens_min_err_cnt = (U2)0;
            vd_g_Rim_WriteU2((U2)RIMID_U2_GSENS_MIN_ERR, u2_s_gyrodev_gsens_min_err_cnt);

            vd_GYRODEV_DREC_REQ((U1)SYSECDRC_DREC_ID_5, (U1)0x00U, (U1)0x00U);

            /* G Sonsor Fail DTC Record */
            vd_GYRODEV_DTC_REQ((U1)DTCCTL_DTCID_GSNS_ERR, (U1)GYRODEV_DTC_STS_FAIL);
            u1_s_gyrodev_gsens_dtcrec_a_flag = (U1)FALSE;

            if(u1_s_gyrodev_gsens_rst_cnt >= (U2)GYRODEV_GSENSDTC_RSTCNT_MAX){            /* Reset Count >= n(6_3) */
                /* Counter Clear */
                u2_s_gyrodev_gsens_max_err_cnt = (U2)0;
                vd_g_Rim_WriteU2((U2)RIMID_U2_GSENS_MAX_ERR, u2_s_gyrodev_gsens_max_err_cnt);
                u2_s_gyrodev_gsens_min_err_cnt = (U2)0;
                vd_g_Rim_WriteU2((U2)RIMID_U2_GSENS_MIN_ERR, u2_s_gyrodev_gsens_min_err_cnt);
                u1_s_gyrodev_gsens_rst_cnt = (U1)0;
                vd_g_Rim_WriteU1((U2)RIMID_U1_GSENS_RST, u1_s_gyrodev_gsens_rst_cnt);
                /* Event Set */
                vd_s_GyroDevEventGo((U1)GYRODEV_EVENT_DTC_ERR);
                /* State Reset */
                u1_s_gyrodev_state = (U1)GYRODEV_SEQ_IDLE;
                vd_g_Rim_WriteU1((U2)RIMID_U1_GYRO_STS, u1_s_gyrodev_state);
                /* Process Reset */
                u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP0;
                vd_g_Rim_WriteU1((U2)RIMID_U1_GYRO_CYCCHK_STS, u1_s_gyrodev_cycchk_sts);
            }
            else{
                u1_s_gyrodev_gsens_rst_cnt++;
                vd_g_Rim_WriteU1((U2)RIMID_U1_GSENS_RST, u1_s_gyrodev_gsens_rst_cnt);
                /* Event Set */
                vd_s_GyroDevEventGo((U1)GYRODEV_EVENT_DEV_RST);
                /* State Reset */
                u1_s_gyrodev_state = (U1)GYRODEV_SEQ_IDLE;
                vd_g_Rim_WriteU1((U2)RIMID_U1_GYRO_STS, u1_s_gyrodev_state);
                /* Process Reset */
                u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP0;
                vd_g_Rim_WriteU1((U2)RIMID_U1_GYRO_CYCCHK_STS, u1_s_gyrodev_cycchk_sts);
            }
        }
    }
    else{
        /* Error Counter Clear */
        u2_s_gyrodev_gsens_max_err_cnt = (U2)0;
        vd_g_Rim_WriteU2((U2)RIMID_U2_GSENS_MAX_ERR, u2_s_gyrodev_gsens_max_err_cnt);
        u2_s_gyrodev_gsens_min_err_cnt = (U2)0;
        vd_g_Rim_WriteU2((U2)RIMID_U2_GSENS_MIN_ERR, u2_s_gyrodev_gsens_min_err_cnt);
        u1_s_gyrodev_gsens_rst_cnt = (U1)0;
        vd_g_Rim_WriteU1((U2)RIMID_U1_GSENS_RST, u1_s_gyrodev_gsens_rst_cnt);

        /* DTC Record Check */
        if(u1_s_gyrodev_gsens_dtcrec_a_flag == (U1)FALSE){                      /* Initial Record or Error -> Normal */
            /* G Sonsor Normal DTC Record */
            vd_GYRODEV_DTC_REQ((U1)DTCCTL_DTCID_GSNS_ERR, (U1)GYRODEV_DTC_STS_NORMAL);
            u1_s_gyrodev_gsens_dtcrec_a_flag = (U1)TRUE;
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
                        vd_g_Rim_WriteOther((U2)RIMID_OTR_GYRODEV_NOTIFCOND, sizeof(st_gyrodev_notifcond_setbak), (const U1 *)(const void *)&st_gyrodev_notifcond_setbak);
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
            u1_t_reg_req_sts = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                         (U2)GYRODEV_INT_ANYMOT_TH_SET1_WRINUM,
                                                         (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                         GYRODEV_INT_ANYMOT_TH_SET1,
                                                         st_sp_GYRODEV_INT_ANYMOT_TH_SET1_TBL);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gyrodev_notifcondset_sts = (U1)GYRODEV_NOTIFCONDSET_STEP2;
            }
            break;
        case GYRODEV_NOTIFCONDSET_STEP2:                            /* STEP2 */
            /* Read Register G-Sensor */
            u1_t_reg_req_sts = u1_s_Gyro_I2cReadMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                        (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                        st_sp_GYRODEV_INT_ANYMOT_RD_TBL,
                                                        (U1)MCU_I2C_WAIT_NON);
            if(u1_t_reg_req_sts == (U1)TRUE){
                u1_t_gsens_int_anymot_th_lsb_data = st_sp_GYRODEV_INT_ANYMOT_RD_TBL[1].u1p_pdu[1];  /* INT_ANYMOT_TH bit[7:0] - Not used for Overwriting */
                u1_t_gsens_int_anymot_th_msb_data = st_sp_GYRODEV_INT_ANYMOT_RD_TBL[1].u1p_pdu[2];  /* INT_ANYMOT_TH bit[15:8] */
                u1_t_gsens_int_anymot_th_msb_data = (U1)((U4)u1_t_gsens_int_anymot_th_msb_data & (U4)(~(U4)GYRODEV_GSENS_INT_THD_MSB_MASK));           /* INT_ANYMOT_TH bit[10:8] = 0b000 */
                if(((U4)GYRODEV_GSENS_INT_THD_RESO != (U4)0U) && ((U4)st_gyrodev_notifcond_setreq.u1_threshold <= ((U4)U4_MAX / (U4)GYRODEV_GSENS_INT_THD_RESO))){
                    u4_t_gsens_anymot_thd_calc_data = ((U4)st_gyrodev_notifcond_setreq.u1_threshold * (U4)GYRODEV_GSENS_INT_THD_RESO) / (U4)GYRODEV_GSENS_INT_THD_MULT;   /* Threshold Conversion */
                }
                else{
                    u4_t_gsens_anymot_thd_calc_data = (U4)U4_MAX;
                }
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
            u1_t_reg_req_sts = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                         (U2)GYRODEV_INT_ANYMOT_TH_SET2_WRINUM,
                                                         (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                         GYRODEV_INT_ANYMOT_TH_SET2,
                                                         st_sp_GYRODEV_INT_ANYMOT_TH_SET2_TBL);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gyrodev_notifcondset_sts = (U1)GYRODEV_NOTIFCONDSET_STEP4;
            }
            break;
        case GYRODEV_NOTIFCONDSET_STEP4:                            /* STEP4 */
        /* --------------- uc_axis Setting --------------- */
            /* Set Register G-Sensor */
            u1_t_reg_req_sts = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                         (U2)GYRODEV_INT_ANYMOT_EN_SET1_WRINUM,
                                                         (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                         GYRODEV_INT_ANYMOT_EN_SET1,
                                                         st_sp_GYRODEV_INT_ANYMOT_EN_SET1_TBL);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gyrodev_notifcondset_sts = (U1)GYRODEV_NOTIFCONDSET_STEP5;
            }
            break;
        case GYRODEV_NOTIFCONDSET_STEP5:                            /* STEP5 */
            /* Read Register G-Sensor */
            u1_t_reg_req_sts = u1_s_Gyro_I2cReadMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                        (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                        st_sp_GYRODEV_INT_ANYMOT_RD_TBL,
                                                        (U1)MCU_I2C_WAIT_NON);
            if(u1_t_reg_req_sts == (U1)TRUE){
                u1_t_gsens_int_anymot_en_lsb_data = st_sp_GYRODEV_INT_ANYMOT_RD_TBL[1].u1p_pdu[1];  /* INT_ANYMOT_EN bit[7:0] */
                u1_t_gsens_int_anymot_en_msb_data = st_sp_GYRODEV_INT_ANYMOT_RD_TBL[1].u1p_pdu[2];  /* INT_ANYMOT_EN bit[15:8] */
                u1_t_gsens_int_anymot_en_msb_data &= (U1)((U4)u1_t_gsens_int_anymot_en_msb_data & (U4)(~(U4)GYRODEV_GSENS_INT_AXIS_MSB_MASK));          /* INT_ANYMOT_EN bit[15:13] = 0b000 */
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
            u1_t_reg_req_sts = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                         (U2)GYRODEV_INT_ANYMOT_EN_SET2_WRINUM,
                                                         (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                         GYRODEV_INT_ANYMOT_EN_SET2,
                                                         st_sp_GYRODEV_INT_ANYMOT_EN_SET2_TBL);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gyrodev_notifcondset_sts = (U1)GYRODEV_NOTIFCONDSET_STEP7;
            }
            break;
        case GYRODEV_NOTIFCONDSET_STEP7:                            /* STEP7 */
        /* --------------- uc_active Setting --------------- */
            /* Read Register G-Sensor */
            u1_t_reg_req_sts = u1_s_Gyro_I2cReadMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                        (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                        st_sp_GYRODEV_INT2_IO_CONF_RD_TBL,
                                                        (U1)MCU_I2C_WAIT_NON);
            if(u1_t_reg_req_sts == (U1)TRUE){
                u1_t_gsens_int2_io_conf_data = st_sp_GYRODEV_INT2_IO_CONF_RD_TBL[1].u1p_pdu[1];     /* INT2_IO_CONF bit[7:0] */
                if(st_gyrodev_notifcond_setreq.u1_active == (U1)GYRODEV_GSENS_INT_LVL_ACT_HI){      /* uc_active = LSDRV_GSNS_INT_COND_ACTIVE_HIGH */
                    u1_t_gsens_int2_io_conf_data |= (U1)GYRODEV_REG_MASK_BIT_1;                     /* INT2_IO_CONF bit[1] = 0b1 */
                }
                else if(st_gyrodev_notifcond_setreq.u1_active == (U1)GYRODEV_GSENS_INT_LVL_ACT_LOW){    /* uc_active = LSDRV_GSNS_INT_COND_ACTIVE_LOW */
                    u1_t_gsens_int2_io_conf_data = (U1)((U4)u1_t_gsens_int2_io_conf_data & (U4)(~(U4)GYRODEV_REG_MASK_BIT_1));                    /* INT2_IO_CONF bit[1] = 0b0 */
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
            u1_t_reg_req_sts = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                         (U2)GYRODEV_INT2_IO_CONF_SET_WRINUM,
                                                         (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                         GYRODEV_INT2_IO_CONF_SET,
                                                         st_sp_GYRODEV_INT2_IO_CONF_SET_TBL);
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
            u1_t_reg_req_sts = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                         (U2)GYRODEV_INT_ANYMOT_TH_SET1_WRINUM,
                                                         (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                         GYRODEV_INT_ANYMOT_TH_SET1,
                                                         st_sp_GYRODEV_INT_ANYMOT_TH_SET1_TBL);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gyrodev_notifcondset_sts = (U1)GYRODEV_NOTIFCONDSET_STEP10;
            }
            break;
        case GYRODEV_NOTIFCONDSET_STEP10:                           /* STEP10 */
            /* Read Register G-Sensor */
            u1_t_reg_req_sts = u1_s_Gyro_I2cReadMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                        (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                        st_sp_GYRODEV_INT_ANYMOT_RD_TBL,
                                                        (U1)MCU_I2C_WAIT_NON);
            if(u1_t_reg_req_sts == (U1)TRUE){
                u1_t_gsens_int_anymot_th_lsb_data = st_sp_GYRODEV_INT_ANYMOT_RD_TBL[1].u1p_pdu[1];  /* INT_ANYMOT_TH bit[7:0] - Not used for Overwriting */
                u1_t_gsens_int_anymot_th_msb_data = st_sp_GYRODEV_INT_ANYMOT_RD_TBL[1].u1p_pdu[2];  /* INT_ANYMOT_TH bit[15:8] */
                u1_t_gsens_int_anymot_th_msb_data &= (U1)GYRODEV_GSENS_INT_THD_MSB_MASK;           /* INT_ANYMOT_TH bit[15:11] = 0b00000 */
                u4_t_gsens_anymot_thd_calc_data = ((U4)u1_t_gsens_int_anymot_th_msb_data  << (U4)GYRODEV_REG_BIT_SHIFT_8) | (U4)u1_t_gsens_int_anymot_th_lsb_data;  /* anymot_th Conversion */

                if(u4_t_gsens_anymot_thd_calc_data == (U4)U4_MAX){
                    u4_t_gsens_anymot_thd_calc_data = (U4)U4_MAX;
                }
                else{
                    u4_t_gsens_anymot_thd_calc_data = u4_t_gsens_anymot_thd_calc_data + (U4)1U;
                }
                if(((U4)GYRODEV_GSENS_INT_THD_MULT != (U4)0U) && ((U4)u4_t_gsens_anymot_thd_calc_data <= ((U4)U4_MAX / (U4)GYRODEV_GSENS_INT_THD_MULT))){
                    u1_t_gsens_threshold_calc_data = (U1)(((U4)u4_t_gsens_anymot_thd_calc_data * (U4)GYRODEV_GSENS_INT_THD_MULT) / (U4)GYRODEV_GSENS_INT_THD_RESO);   /* Threshold Conversion */
                }
                else{
                    u1_t_gsens_threshold_calc_data = (U1)U1_MAX;
                }

                st_gyrodev_notifcond_readreq.u1_threshold = u1_t_gsens_threshold_calc_data;

                /* Next Process */
                u1_s_gyrodev_notifcondset_sts = (U1)GYRODEV_NOTIFCONDSET_STEP11;
            }
            break;
        case GYRODEV_NOTIFCONDSET_STEP11:                           /* STEP11 */
        /* --------------- uc_axis Reading --------------- */
            /* Set Register G-Sensor */
            u1_t_reg_req_sts = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                         (U2)GYRODEV_INT_ANYMOT_EN_SET1_WRINUM,
                                                         (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                         GYRODEV_INT_ANYMOT_EN_SET1,
                                                         st_sp_GYRODEV_INT_ANYMOT_EN_SET1_TBL);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gyrodev_notifcondset_sts = (U1)GYRODEV_NOTIFCONDSET_STEP12;
            }
            break;
        case GYRODEV_NOTIFCONDSET_STEP12:                           /* STEP12 */
            /* Read Register G-Sensor */
            u1_t_reg_req_sts = u1_s_Gyro_I2cReadMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                        (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                        st_sp_GYRODEV_INT_ANYMOT_RD_TBL,
                                                        (U1)MCU_I2C_WAIT_NON);
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
            u1_t_reg_req_sts = u1_s_Gyro_I2cReadMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                        (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                        st_sp_GYRODEV_INT2_IO_CONF_RD_TBL,
                                                        (U1)MCU_I2C_WAIT_NON);
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
            vd_s_GyroI2cAbort((U1)MCU_I2C_ACK_G_MONI);
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
                    vd_g_Rim_WriteOther((U2)RIMID_OTR_GYRODEV_CTRLOUT, sizeof(st_gyrodev_ctrlout_setbak), (const U1 *)(const void *)&st_gyrodev_ctrlout_setbak);
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
            u1_t_reg_req_sts = u1_s_Gyro_I2cReadMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                        (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                        st_sp_GYRODEV_INTAPI_OUTPUTRST_RD_TBL,
                                                        (U1)MCU_I2C_WAIT_NON);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Process Reset */
                u1_s_gyrodev_ctrloutset_sts = (U1)GYRODEV_CTRLOUTSET_STEP2;
            }
            break;
        case GYRODEV_CTRLOUTSET_STEP2:                              /* STEP2 */
            /* Set Register G-Sensor */
            u1_t_reg_req_sts = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                         (U2)GYRODEV_INT_ANYMOT_TH_SET1_WRINUM,
                                                         (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                         GYRODEV_INT_ANYMOT_TH_SET1,
                                                         st_sp_GYRODEV_INT_ANYMOT_TH_SET1_TBL);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gyrodev_ctrloutset_sts = (U1)GYRODEV_CTRLOUTSET_STEP3;
            }
            break;
        case GYRODEV_CTRLOUTSET_STEP3:                              /* STEP3 */
            /* Read Register G-Sensor */
            u1_t_reg_req_sts = u1_s_Gyro_I2cReadMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                        (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                        st_sp_GYRODEV_INT_ANYMOT_RD_TBL,
                                                        (U1)MCU_I2C_WAIT_NON);
            if(u1_t_reg_req_sts == (U1)TRUE){
                u1_t_gsens_int_anymot_th_lsb_data = st_sp_GYRODEV_INT_ANYMOT_RD_TBL[1].u1p_pdu[1];  /* INT_ANYMOT_TH bit[7:0] */
                u1_t_gsens_int_anymot_th_msb_data = st_sp_GYRODEV_INT_ANYMOT_RD_TBL[1].u1p_pdu[2];  /* INT_ANYMOT_TH bit[15:8] */
                u1_t_gsens_int_anymot_th_msb_data = (U1)((U4)u1_t_gsens_int_anymot_th_msb_data & (U4)(~(U4)GYRODEV_REG_MASK_BIT_3)); /* INT_ANYMOT_TH bit[11] = 0b0 */
                st_sp_GYRODEV_INT_ANYMOT_TH_SET2_TBL[2].u1p_pdu[2] = u1_t_gsens_int_anymot_th_lsb_data;     /* Register Write Data(LSB) Set */
                st_sp_GYRODEV_INT_ANYMOT_TH_SET2_TBL[2].u1p_pdu[3] = u1_t_gsens_int_anymot_th_msb_data;     /* Register Write Data(MSB) Set */

                /* Next Process */
                u1_s_gyrodev_ctrloutset_sts = (U1)GYRODEV_CTRLOUTSET_STEP4;
            }
            break;
        case GYRODEV_CTRLOUTSET_STEP4:                              /* STEP4 */
            /* Set Register G-Sensor */
            u1_t_reg_req_sts = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                         (U2)GYRODEV_INT_ANYMOT_TH_SET2_WRINUM,
                                                         (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                         GYRODEV_INT_ANYMOT_TH_SET2,
                                                         st_sp_GYRODEV_INT_ANYMOT_TH_SET2_TBL);
            if(u1_t_reg_req_sts == (U1)TRUE){
                st_sp_GYRODEV_INT_ANYMOT_TH_SET2_TBL[2].u1p_pdu[3] |= (U1)GYRODEV_REG_MASK_BIT_3;   /* INT_ANYMOT_TH bit[11] = 0b1 */

                /* Next Process */
                u1_s_gyrodev_ctrloutset_sts = (U1)GYRODEV_CTRLOUTSET_STEP5;
            }
            break;
        case GYRODEV_CTRLOUTSET_STEP5:                              /* STEP5 */
            /* Set Register G-Sensor */
            u1_t_reg_req_sts = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                         (U2)GYRODEV_INT_ANYMOT_TH_SET2_WRINUM,
                                                         (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                         GYRODEV_INT_ANYMOT_TH_SET2,
                                                         st_sp_GYRODEV_INT_ANYMOT_TH_SET2_TBL);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gyrodev_ctrloutset_sts = (U1)GYRODEV_CTRLOUTSET_STEP6;
            }
            break;
        case GYRODEV_CTRLOUTSET_STEP6:                              /* STEP6 */
            /* Set Register G-Sensor */
            u1_t_reg_req_sts = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                         (U2)GYRODEV_INTAPI_OUTPUTON_SET_WRINUM,
                                                         (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                         GYRODEV_INTAPI_OUTPUTON_SET,
                                                         st_sp_GYRODEV_INTAPI_OUTPUTON_SET_TBL);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gyrodev_ctrloutset_sts = (U1)GYRODEV_CTRLOUTSET_STEP7;
            }
            break;
        case GYRODEV_CTRLOUTSET_STEP7:                              /* STEP7 */
            /* Read Register G-Sensor */
            u1_t_reg_req_sts = u1_s_Gyro_I2cReadMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                        (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                        st_sp_GYRODEV_INT2_IO_CONF_RD_TBL,
                                                        (U1)MCU_I2C_WAIT_NON);
            if(u1_t_reg_req_sts == (U1)TRUE){
                u1_t_gsens_int2_io_conf_data = st_sp_GYRODEV_INT2_IO_CONF_RD_TBL[1].u1p_pdu[1];     /* INT2_IO_CONF bit[7:0] */
                u1_t_gsens_int2_io_conf_data = (U1)((U4)u1_t_gsens_int2_io_conf_data | (U4)GYRODEV_REG_MASK_BIT_3); /* INT2_IO_CONF bit[3] = 0b1 */
                st_sp_GYRODEV_INT2_IO_CONF_SET_TBL[0].u1p_pdu[2] = u1_t_gsens_int2_io_conf_data;    /* Register Write Data Set */
                /* Next Process */
                u1_s_gyrodev_ctrloutset_sts = (U1)GYRODEV_CTRLOUTSET_STEP8;
            }
            break;
        case GYRODEV_CTRLOUTSET_STEP8:                              /* STEP8 */
            /* Set Register G-Sensor */
            u1_t_reg_req_sts = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                         (U2)GYRODEV_INT2_IO_CONF_SET_WRINUM,
                                                         (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                         GYRODEV_INT2_IO_CONF_SET,
                                                         st_sp_GYRODEV_INT2_IO_CONF_SET_TBL);
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
            u1_t_reg_req_sts = u1_s_Gyro_I2cReadMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                        (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                        st_sp_GYRODEV_INT2_IO_CONF_RD_TBL,
                                                        (U1)MCU_I2C_WAIT_NON);
            if(u1_t_reg_req_sts == (U1)TRUE){
                u1_t_gsens_int2_io_conf_data = st_sp_GYRODEV_INT2_IO_CONF_RD_TBL[1].u1p_pdu[1];     /* INT2_IO_CONF bit[7:0] */
                u1_t_gsens_int2_io_conf_data = (U1)((U4)u1_t_gsens_int2_io_conf_data & (U4)(~(U4)GYRODEV_GSENS_INT_OUT_MASK)); /* INT2_IO_CONF bit[3] = 0b0 */
                st_sp_GYRODEV_INT2_IO_CONF_SET_TBL[0].u1p_pdu[2] = u1_t_gsens_int2_io_conf_data;    /* Register Write Data Set */
                /* Next Process */
                u1_s_gyrodev_ctrloutset_sts = (U1)GYRODEV_CTRLOUTSET_STEP10;
            }
            break;
        case GYRODEV_CTRLOUTSET_STEP10:                             /* STEP10 */
            /* Set Register G-Sensor */
            u1_t_reg_req_sts = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                         (U2)GYRODEV_INT2_IO_CONF_SET_WRINUM,
                                                         (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                         GYRODEV_INT2_IO_CONF_SET,
                                                         st_sp_GYRODEV_INT2_IO_CONF_SET_TBL);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gyrodev_ctrloutset_sts = (U1)GYRODEV_CTRLOUTSET_STEP11;
            }
            break;
        case GYRODEV_CTRLOUTSET_STEP11:                             /* STEP11 */
            /* Set Register G-Sensor */
            u1_t_reg_req_sts = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                         (U2)GYRODEV_INT_ANYMOT_TH_SET1_WRINUM,
                                                         (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                         GYRODEV_INT_ANYMOT_TH_SET1,
                                                         st_sp_GYRODEV_INT_ANYMOT_TH_SET1_TBL);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gyrodev_ctrloutset_sts = (U1)GYRODEV_CTRLOUTSET_STEP12;
            }
            break;
        case GYRODEV_CTRLOUTSET_STEP12:                             /* STEP12 */
            /* Read Register G-Sensor */
            u1_t_reg_req_sts = u1_s_Gyro_I2cReadMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                        (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                        st_sp_GYRODEV_INT_ANYMOT_RD_TBL,
                                                        (U1)MCU_I2C_WAIT_NON);
            if(u1_t_reg_req_sts == (U1)TRUE){
                u1_t_gsens_int_anymot_th_lsb_data = st_sp_GYRODEV_INT_ANYMOT_RD_TBL[1].u1p_pdu[1];  /* INT_ANYMOT_TH bit[7:0] */
                u1_t_gsens_int_anymot_th_msb_data = st_sp_GYRODEV_INT_ANYMOT_RD_TBL[1].u1p_pdu[2];  /* INT_ANYMOT_TH bit[15:8] */
                u1_t_gsens_int_anymot_th_msb_data = (U1)((U4)u1_t_gsens_int_anymot_th_msb_data & (U4)(~(U4)GYRODEV_GSENS_INT_EN_MSB_MASK)); /* INT_ANYMOT_TH bit[11] = 0b0 */
                st_sp_GYRODEV_INT_ANYMOT_TH_SET2_TBL[2].u1p_pdu[2] = u1_t_gsens_int_anymot_th_lsb_data;     /* Register Write Data(LSB) Set */
                st_sp_GYRODEV_INT_ANYMOT_TH_SET2_TBL[2].u1p_pdu[3] = u1_t_gsens_int_anymot_th_msb_data;     /* Register Write Data(MSB) Set */

                /* Next Process */
                u1_s_gyrodev_ctrloutset_sts = (U1)GYRODEV_CTRLOUTSET_STEP13;
            }
            break;
        case GYRODEV_CTRLOUTSET_STEP13:                             /* STEP13 */
            /* Set Register G-Sensor */
            u1_t_reg_req_sts = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                         (U2)GYRODEV_INT_ANYMOT_TH_SET2_WRINUM,
                                                         (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                         GYRODEV_INT_ANYMOT_TH_SET2,
                                                         st_sp_GYRODEV_INT_ANYMOT_TH_SET2_TBL);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gyrodev_ctrloutset_sts = (U1)GYRODEV_CTRLOUTSET_STEP14;
            }
            break;
        case GYRODEV_CTRLOUTSET_STEP14:                             /* STEP14 */
            /* Set Register G-Sensor */
            u1_t_reg_req_sts = u1_s_Gyro_I2cWriteMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                         (U2)GYRODEV_INTAPI_OUTPUTOFF_SET_WRINUM,
                                                         (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                         GYRODEV_INTAPI_OUTPUTOFF_SET,
                                                         st_sp_GYRODEV_INTAPI_OUTPUTOFF_SET_TBL);
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
            u1_t_reg_req_sts = u1_s_Gyro_I2cReadMgrFunc((U1)MCU_I2C_ACK_G_MONI,
                                                        (U1)GP_I2C_MA_SLA_7_G_MONI,
                                                        st_sp_GYRODEV_INTAPI_OUTPUTRST_RD_TBL,
                                                        (U1)MCU_I2C_WAIT_NON);
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
            vd_s_GyroI2cAbort((U1)MCU_I2C_ACK_G_MONI);
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
    U4   u4_t_cnt;

    for(u4_t_cnt = (U4)0; u4_t_cnt < u4_a_size; u4_t_cnt++){
        u1p_udst[u4_t_cnt] = u1_a_data;
    }
}

/*===================================================================================================================================*/
/*  void    vd_s_GyroDev_AppChk(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_GyroDev_AppChk(void)
{
    U1      u1_t_appon_sts;                                         /* APP-ON Status */
    U1      u1_t_func_sts;                                          /* Function Status */

    u1_t_func_sts = (U1)FALSE;

    u1_t_appon_sts = u1_GYRODEV_GET_APP_ON();
    if((u1_t_appon_sts == (U1)GYRODEV_APPOFF)
    && (u1_s_gyrodev_pre_appon_sts == (U1)GYRODEV_APPON)){
        /* Execute only STEP0 of the function */
        u1_t_func_sts = u1_s_GyroDev_GSensNotifCondFunc((U1)GYRODEV_GSENS_NOTIFCONDFUNC_BACKUP);
        if(u1_t_func_sts == (U1)FALSE){
            /* Next Process */
            u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP3;
            vd_g_Rim_WriteU1((U2)RIMID_U1_GYRO_CYCCHK_STS, u1_s_gyrodev_cycchk_sts);
        }
        else{
            /* Next Process */
            u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP0;
            vd_g_Rim_WriteU1((U2)RIMID_U1_GYRO_CYCCHK_STS, u1_s_gyrodev_cycchk_sts);
        }
    }
    else{
        /* Execute only STEP0 of the function */
        u1_t_func_sts = u1_s_GyroDev_GSensNotifCondFunc((U1)GYRODEV_GSENS_NOTIFCONDFUNC_READREQ);
        if(u1_t_func_sts == (U1)FALSE){
            /* Next Process */
            u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP5;
            vd_g_Rim_WriteU1((U2)RIMID_U1_GYRO_CYCCHK_STS, u1_s_gyrodev_cycchk_sts);
        }
        else{
            /* Next Process */
            u1_s_gyrodev_cycchk_sts = (U1)GYRODEV_CYCCHK_STEP0;
            vd_g_Rim_WriteU1((U2)RIMID_U1_GYRO_CYCCHK_STS, u1_s_gyrodev_cycchk_sts);
        }
    }
    /* Previous State Update */
    u1_s_gyrodev_pre_appon_sts = u1_t_appon_sts;
}

/*===================================================================================================================================*/
/*  U1    u1_s_GyroDev_ParamBackup(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1  u1_s_GyroDev_ParamBackup(void)
{
    U1 u1_t_sts;
    U1 u1_t_return;

    u1_t_return = (U1)FALSE;

    switch (u1_s_gyrodev_gsensbkup_sts){
        case GYRODEV_GSENSBKUP_STEP0:
            u1_t_sts = u1_s_GyroDev_GSensNotifCondFunc((U1)GYRODEV_GSENS_NOTIFCONDFUNC_BACKUP);
            if (u1_t_sts == (U1)TRUE) {
                u1_s_gyrodev_gsensbkup_sts = GYRODEV_GSENSBKUP_STEP1;
            }
            break;
        case GYRODEV_GSENSBKUP_STEP1:
            u1_t_sts = u1_s_GyroDev_GSensCtrlOutFunc((U1)GYRODEV_GSENS_CTRLOUTFUNC_BACKUP);
            if (u1_t_sts == (U1)TRUE) {
                u1_s_gyrodev_gsensbkup_sts = GYRODEV_GSENSBKUP_STEP0;
                u1_t_return = (U1)TRUE;
            }
            break;
        default:
            u1_s_gyrodev_gsensbkup_sts = GYRODEV_GSENSBKUP_STEP0;
            vd_s_GyroI2cAbort((U1)MCU_I2C_ACK_G_MONI);
            break;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  U1    u1_s_GyroDev_ShockDetEnHoldChk(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_GyroDev_ShockDetEnHoldChk(void)
{
    U1 u1_t_return;

    u1_t_return = (U1)FALSE;

    if((u1_s_gyrodev_oscmd_outctl_bak_flag == (U1)TRUE)
    && (st_gyrodev_ctrlout_setbak.u1_type_standby == (U1)GYRODEV_GSENS_INT_STBY_ON)){
        u1_t_return = (U1)TRUE;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  U1    u1_s_Gyro_I2cWriteMgrFunc                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_Gyro_I2cWriteMgrFunc(const U1 u1_a_ack, const U2 u2_a_wri_max, const U1 i2c_sla, const ST_REG_WRI_REQ * stp_a_wrireq, const ST_GP_I2C_MA_REQ * stp_a_setreg)
{
    U1 u1_t_ret;
    U4 u4_t_pid;

    u1_t_ret = (U1)FALSE;
    u4_t_pid = stp_a_setreg->u4_cbf & GYRO_I2C_PID_MASK;
    if ((u1_s_i2c_exe_flag[u1_a_ack] == (U1)FALSE) || (u4_s_i2c_pid[u1_a_ack] == u4_t_pid)){
        u1_s_i2c_exe_flag[u1_a_ack] = (U1)TRUE;
        u4_s_i2c_pid[u1_a_ack] = u4_t_pid;

        U1 sts = GYRODEV_GYRO_I2C_CTRL_REGSET(u1_a_ack,
                                              &u2_s_gyrodev_regstep,
                                              (U2)u2_a_wri_max,
                                              (U1)i2c_sla,
                                              stp_a_wrireq,
                                              &u4_s_gyrodev_i2c_ack_wait_time,
                                              stp_a_setreg,
                                              &u2_s_gyrodev_reg_btwn_time);

        if (sts == (U1)TRUE) {
            u1_s_i2c_exe_flag[u1_a_ack] = (U1)FALSE;
            u4_s_i2c_pid[u1_a_ack] = (U4)GYRO_I2C_PID_INVALID;
            u1_t_ret = (U1)TRUE;
        }
    }
    return (u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1    u1_s_Gyro_I2cReadMgrFunc                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_Gyro_I2cReadMgrFunc(const U1 u1_a_ack, const U1 i2c_sla, const ST_GP_I2C_MA_REQ *stp_a_setreg, const U1 waitmode)
{
    U1 u1_t_ret;
    U4 u4_t_pid;

    u1_t_ret = (U1)FALSE;
    u4_t_pid = stp_a_setreg->u4_cbf & GYRO_I2C_PID_MASK;
    if ((u1_s_i2c_exe_flag[u1_a_ack] == (U1)FALSE) || (u4_s_i2c_pid[u1_a_ack] == u4_t_pid)){
        u1_s_i2c_exe_flag[u1_a_ack] = (U1)TRUE;
        u4_s_i2c_pid[u1_a_ack] = u4_t_pid;

        U1 sts = GYRODEV_GYRO_I2C_CTRL_REGREAD(u1_a_ack,
                                               &u2_s_gyrodev_regstep,
                                               i2c_sla,
                                               &u4_s_gyrodev_i2c_ack_wait_time,
                                               stp_a_setreg,
                                               &u2_s_gyrodev_reg_btwn_time,
                                               waitmode);

        if (sts == (U1)TRUE) {
            u1_s_i2c_exe_flag[u1_a_ack] = (U1)FALSE;
            u4_s_i2c_pid[u1_a_ack] = (U4)GYRO_I2C_PID_INVALID;
            u1_t_ret = (U1)TRUE;
        }
    }
    return (u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1    u1_s_GyroI2cIsBusy(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_GyroI2cIsBusy(void)
{
    U1 u1_t_ret;
    U1 u1_t_ack;
    u1_t_ret = (U1)FALSE;

    for (u1_t_ack = 0; u1_t_ack < GYRODEV_ACK_MAX; u1_t_ack++) {
        if (u1_s_i2c_exe_flag[u1_t_ack] == (U1)TRUE) {
            u1_t_ret = (U1)TRUE;
        }
    }
    return (u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1    u1_s_GyroI2cIsBusy(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GyroI2cAbort(U1 u1_a_ack)
{
    u1_s_i2c_exe_flag[u1_a_ack] = (U1)FALSE;
    u4_s_i2c_pid[u1_a_ack]      = (U4)GYRO_I2C_PID_INVALID;

    u2_s_gyrodev_regstep = (U2)0;
    u4_s_gyrodev_i2c_ack_wait_time = (U4)0;
}
