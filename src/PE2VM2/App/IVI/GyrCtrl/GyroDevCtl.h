/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
#ifndef GYRODEVCTL_H
#define GYRODEVCTL_H
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"

#include "Dio.h"
#include "Mcu_I2c_Ctrl_private.h"
#include "x_spi_ivi_sub2.h"
#include "CarSpdPls.h"
#include "SysEcDrc.h"
#include "DtcCtl.h"
#include "PwrCtl.h"

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
#define GYRODEV_I2C_RWC_BYTE34                      (34U)

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
#define GYRO_TASK_TIME                          (1U)    /* 周期の時間指定(LSB:1ms) */

/* シーケンス実行No 共通 */
#define GYRO_SEQ_IDLE_STA                       (0U)    /* アイドルシーケンス実行No */

/* ジャイロ状態遷移モード */
#define GYRO_MODE_MAX                           (7U)    /* 状態最大数 */
#define GYRO_MODE_UNINIT                        (0U)    /* 0:未初期化 */
#define GYRO_MODE_STUP1_PRO                     (1U)    /* 1:起動(1)実施中 */
#define GYRO_MODE_STUP1_COMP                    (2U)    /* 2:起動(1)実施完了 */
#define GYRO_MODE_STUP2_PRO                     (3U)    /* 3:起動(2)実施中 */
#define GYRO_MODE_NORM                          (4U)    /* 4:通常動作中 */
#define GYRO_MODE_SHTDN1_PRO                    (5U)    /* 5:終了(1)実施中 */
#define GYRO_MODE_ERR                           (6U)    /* 6:異常停止中 */

/* ジャイロ状態遷移イベント */
#define GYRO_EVENT_MAX                          (11U)   /* イベント最大数 */
#define GYRO_EVENT_TASKSTUP                     (0U)    /* 0:タスク起動 */
#define GYRO_EVENT_V33PERION_ON                 (1U)    /* 1:V33-Peri-ON ON */
#define GYRO_EVENT_V33PERION_OFF                (2U)    /* 2:V33-Peri-ON OFF */
#define GYRO_EVENT_SYS_OFF                      (3U)    /* 3:システムオフ 予備設計 */
#define GYRO_EVENT_SEQ_COMP                     (4U)    /* 4:シーケンス完了 */
#define GYRO_EVENT_STUP_ERR                     (5U)    /* 5:起動異常検知 */
#define GYRO_EVENT_DTC_ERR                      (6U)    /* 6:DTC異常検知 */
#define GYRO_EVENT_SHTDN_ERR                    (7U)    /* 7:終了異常検知 */
#define GYRO_EVENT_DEV_RST                      (8U)    /* 8:リセット */
#define GYRO_EVENT_BUDET_HI                     (9U)    /* 9:BUDET LO -> HI */
#define GYRO_EVENT_BUDET_LO                     (10U)   /* 10:BUDET HI -> LO */

#define GYRODEV_READ_DATA_OK                        (0U)
#define GYRODEV_READ_DATA_NG                        (1U)

#define GYRODEV_APPOFF                              (POWER_MODE_STATE_APPOFF)
#define GYRODEV_APPON                               (POWER_MODE_STATE_APPON)

#define GYRODEV_LAST_PLS_STOP                       (CARSPDPLS_PLS_STP_CYC)
#define GYRODEV_LAST_PLS_8KM                        (CARSPDPLS_PLS_8KM_CYC)

#define GYRODEV_DTC_STS_FAIL                        (0U)
#define GYRODEV_DTC_STS_NORMAL                      (1U)

#define GYRODEV_MODE_NORMAL                         (GYRO_MODE_NORM)

#define GYRODEV_EVENT_DTC_ERR                       (GYRO_EVENT_DTC_ERR)
#define GYRODEV_EVENT_DEV_RST                       (GYRO_EVENT_DEV_RST)


#define GYRODEV_GYRO_I2C_CTRL_REGSET(s, t, u, v, w, x, y, z)    (Mcu_Dev_I2c_Ctrl_RegSet((s), (t), (u), (v), (w), (x), (y), (z)))
#define GYRODEV_GYRO_I2C_CTRL_REGREAD(t, u, v, w, x, y, z)         (Mcu_Dev_I2c_Ctrl_RegRead((t), (u), (v), (w), (x), (y), (z)))

#define vd_GYRODEV_DREC_REQ(x, y, z)                (vd_g_SysEcDrc_Drec((U1)SYSECDRC_DREC_CAT_GYROACC, (x), (y), (z)))
#define vd_GYRODEV_DTC_REQ(x, y)                    (vd_g_DtcCtl_SetDtcId((x), (y)))

#define u1_GYRODEV_GET_APP_ON()                     (u1_g_Power_ModeState())
#define vd_GYRODEV_OSCMD_GYRO_DATA_NOTIF(x)         (vd_g_XspiIviSub2GyroDataPut(x))
#define u2_GYRODEV_GET_LAST_PLS()                   (u2_g_CarSpdPls_LastPlsGet())
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
void    vd_g_GyroMainTask(void);

void    vd_g_GyroDev_BonInit(void);
void    vd_g_GyroDev_WkupInit(void);
void    vd_g_GyroDev_Routine(void);
void    vd_g_GyroDev_NotifCond_SetReq(ST_GYRODEV_NOTIFCOND_SETDATA st_a_oscmd_data);
void    vd_g_GyroDev_NotifCond_ReadReq(void);
void    vd_g_GyroDev_OutCtl_SetReq(ST_GYRODEV_CTRLOUT_SETDATA st_a_oscmd_data);


/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif      /* GYRODEVCTL_H */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  GyroDevCtl.c                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/