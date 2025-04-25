/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
#ifndef GNSSCTL_H
#define GNSSCTL_H
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"

#include "Dio.h"
#include "Mcu_I2c_Ctrl_private.h"
#include "x_spi_ivi_sub2.h"
#include "CarSpdPls.h"
#include "PictCtl.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Register Access Data */
#define GYRODEV_GSENS_I2C_SLAVEADR_WR               (0x32U)
#define GYRODEV_GSENS_I2C_SLAVEADR_RD               (0x33U)
#define GYRODEV_GYRO_I2C_SLAVEADR_WR                (0xD2U)
#define GYRODEV_GYRO_I2C_SLAVEADR_RD                (0xD3U)
#define GYRODEV_I2C_RWC_BYTE1                       (1U)
#define GYRODEV_I2C_RWC_BYTE2                       (2U)
#define GYRODEV_I2C_RWC_BYTE3                       (3U)
#define GYRODEV_I2C_RWC_BYTE4                       (4U)
#define GYRODEV_I2C_RWC_BYTE7                       (7U)
#define GYRODEV_I2C_RWC_BYTE8                       (8U)

/* Register Bit Mask */
#define GYRODEV_REG_MASK_BIT_0                      (0x01U)
#define GYRODEV_REG_MASK_BIT_1                      (0x02U)
#define GYRODEV_REG_MASK_BIT_2                      (0x04U)
#define GYRODEV_REG_MASK_BIT_3                      (0x08U)
#define GYRODEV_REG_MASK_BIT_4                      (0x10U)
#define GYRODEV_REG_MASK_BIT_5                      (0x20U)
#define GYRODEV_REG_MASK_BIT_6                      (0x40U)
#define GYRODEV_REG_MASK_BIT_7                      (0x80U)

/* Register Bit Shift Data */
#define GYRODEV_REG_BIT_SHIFT_8                     (8U)

#define GYRODEV_GYRODTC_XYZ_MAX                     (0x7FFFU)
#define GYRODEV_GYRODTC_XYZ_MAX_ERRCNT_MAX          (6000U)
#define GYRODEV_GYRODTC_XYZ_MIN                     (0x8000U)
#define GYRODEV_GYRODTC_XYZ_MIN_ERRCNT_MAX          (6000U)
#define GYRODEV_GYRODTC_RSTCNT_MAX                  (3U)

#define GYRODEV_GSENSDTC_XYZ_MAX                    (0x7FFFU)
#define GYRODEV_GSENSDTC_XYZ_MAX_ERRCNT_MAX         (600U)
#define GYRODEV_GSENSDTC_XYZ_MIN                    (0x8000U)
#define GYRODEV_GSENSDTC_XYZ_MIN_ERRCNT_MAX         (600U)
#define GYRODEV_GSENSDTC_RSTCNT_MAX                 (3U)


/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GYRODEV_IO_STS_LOW                          (0U)
#define GYRODEV_IO_STS_HIGH                         (1U)

#define GYRODEV_READ_DATA_OK                        (0U)
#define GYRODEV_READ_DATA_NG                        (1U)

#define GYRODEV_APPOFF                              (PICT_NOREDUN_STATE_APPOFF)
#define GYRODEV_APPON                               (PICT_NOREDUN_STATE_APPON)

#define GYRODEV_LAST_PLS_STOP                       (CARSPDPLS_PLS_STP_CYC)
#define GYRODEV_LAST_PLS_8KM                        (CARSPDPLS_PLS_8KM_CYC)

#define u1_GYRODEV_GYRO_I2C_CTRL_REGSET(u, v, w, x, y, z)    (Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_GYRO, (u), (v), (U1)GP_I2C_MA_SLA_6_GYRO, (w), (x), (y), (z)))
#define u1_GYRODEV_GYRO_I2C_CTRL_REGREAD(w, x, y, z)         (Mcu_Dev_I2c_Ctrl_RegRead((U1)MCU_I2C_ACK_GYRO, (w), (U1)GP_I2C_MA_SLA_6_GYRO, (x), (y), (z), (U1)MCU_I2C_WAIT_NON))
#define u1_GYRODEV_GSENS_I2C_CTRL_REGSET(u, v, w, x, y, z)   (Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_G_MONI, (u), (v), (U1)GP_I2C_MA_SLA_7_G_MONI, (w), (x), (y), (z)))
#define u1_GYRODEV_GSENS_I2C_CTRL_REGREAD(w, x, y, z)        (Mcu_Dev_I2c_Ctrl_RegRead((U1)MCU_I2C_ACK_G_MONI, (w), (U1)GP_I2C_MA_SLA_7_G_MONI, (x), (y), (z), (U1)MCU_I2C_WAIT_NON))

#define u1_GYRODEV_GET_V33_PERI_ON()                (Dio_ReadChannel(DIO_ID_PORT10_CH2))
#define u1_GYRODEV_SET_SENSOR_ON_L()                (Dio_WriteChannel(DIO_ID_PORT8_CH7, (Dio_LevelType)GYRODEV_IO_STS_LOW))
#define u1_GYRODEV_SET_SENSOR_ON_H()                (Dio_WriteChannel(DIO_ID_PORT8_CH7, (Dio_LevelType)GYRODEV_IO_STS_HIGH))
#define u1_GYRODEV_GET_APP_ON()                     (u1_g_PictCtl_StartSts())
#define vd_GYRODEV_OSCMD_GYRO_DATA_NOTIF(x)         (vd_g_XspiIviSub2GyroDataPut(x))
#define u1_GYRODEV_GET_LAST_PLS()                   (u2_g_CarSpdPls_LastPlsGet())
#define vd_GYRODEV_NOTIFCONDSET_RESULT(x)           (vd_g_XspiIviSub2GyroIntSetSend(x))
#define vd_GYRODEV_NOTIFCONDREAD_RESULT(x)          (vd_g_XspiIviSub2GyroIntGetSend(x))
#define vd_GYRODEV_CTRLOUTSETSET_RESULT(x)          (vd_g_XspiIviSub2GyroIntOutSend(x))

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U1                          u1_threshold;
    U1                          u1_axis_x;
    U1                          u1_axis_y;
    U1                          u1_axis_z;
    U1                          u1_active;
}ST_GYRODEV_NOTIFCOND_SETDATA;

typedef struct{
    U1                          u1_type;
    U1                          u1_type_standby;
}ST_GYRODEV_CTRLOUT_SETDATA;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void    vd_g_GyroDev_BonInit(void);
void    vd_g_GyroDev_WkupInit(void);
void    vd_g_GyroDev_Routine(void);
void    vd_g_GyroDev_NotifCond_SetReq(ST_GYRODEV_NOTIFCOND_SETDATA st_a_oscmd_data);
void    vd_g_GyroDev_NotifCond_ReadReq(void);
void    vd_g_GyroDev_OutCtl_SetReq(ST_GYRODEV_CTRLOUT_SETDATA st_a_oscmd_data);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif      /* GNSSCTL_H */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  GNSSCtl.c                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/