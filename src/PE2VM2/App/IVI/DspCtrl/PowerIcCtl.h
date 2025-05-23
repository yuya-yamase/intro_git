/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
#ifndef POWERICCTL_H
#define POWERICCTL_H
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"

#include "Dio.h"
#include "Iohw_adc.h"
#include "Mcu_I2c_Ctrl_private.h"
#include "PictCtl.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Register Access Data */
#define POWERIC_I2C_SLAVEADR_WR                     (0xDEU)
#define POWERIC_I2C_SLAVEADR_RD                     (0xDFU)
#define POWERIC_I2C_RWC_BYTE1                       (1U)
#define POWERIC_I2C_RWC_BYTE2                       (2U)
#define POWERIC_I2C_RWC_BYTE3                       (3U)
#define POWERIC_I2C_RWC_BYTE6                       (6U)
#define POWERIC_I2C_RWC_BYTE7                       (7U)
#define POWERIC_I2C_RWC_BYTE9                       (9U)

/* Register Bit Mask */
#define POWERIC_REG_MASK_BIT_0                      (0x01U)
#define POWERIC_REG_MASK_BIT_1                      (0x02U)
#define POWERIC_REG_MASK_BIT_2                      (0x04U)
#define POWERIC_REG_MASK_BIT_3                      (0x08U)
#define POWERIC_REG_MASK_BIT_4                      (0x10U)
#define POWERIC_REG_MASK_BIT_5                      (0x20U)
#define POWERIC_REG_MASK_BIT_6                      (0x40U)
#define POWERIC_REG_MASK_BIT_7                      (0x80U)

#define POWERIC_I2C_PID_MASK                        (0x0FFC0000U)
#define POWERIC_I2C_PID_INVALID                     (0x10000000U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define POWERIC_IO_STS_LOW                          (0U)
#define POWERIC_IO_STS_HIGH                         (1U)

#define POWERIC_SOFTMUTE_STS_OFF                    (0U)
#define POWERIC_SOFTMUTE_STS_ON                     (1U)

#define POWERIC_POWER_STATE_APP_OFF                 (PICT_NOREDUN_STATE_APPOFF)
#define POWERIC_POWER_STATE_APP_ON                  (PICT_NOREDUN_STATE_APPON)

#define POWERIC_SPEAKER_TYPE_2SPK                   (0U)    /* 暫定 車パラI/F展開後に見直し */
#define POWERIC_SPEAKER_TYPE_4SPK                   (1U)    /* 暫定 車パラI/F展開後に見直し */

#define u1_POWERIC_I2C_CTRL_REGSET(u, v, w, x, y, z)    (Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_POWER, (u), (v), (U1)GP_I2C_MA_SLA_4_POWER, (w), (x), (y), (z)))
#define u1_POWERIC_I2C_CTRL_REGREAD(w, x, y, z)         (Mcu_Dev_I2c_Ctrl_RegRead((U1)MCU_I2C_ACK_POWER, (w), (U1)GP_I2C_MA_SLA_4_POWER, (x), (y), (z), (U1)MCU_I2C_WAIT_NON))

#define u1_POWERIC_GET_POWER_STATE()                (u1_g_PictCtl_StartSts())
#define u1_POWERIC_GET_V33_PERI_ON()                (Dio_ReadChannel(DIO_ID_PORT10_CH2))
#define u1_POWERIC_GET_P_ON()                       (Dio_ReadChannel(DIO_ID_PORT11_CH6))
#define u1_POWERIC_GET_PIC_CURRENT_DET(x)           (u1_g_IoHwAdcRead(ADC_CH_PIC_CUR, (x)))
//#define u1_POWERIC_GET_SPEAKER_TYPE()               (u1_g_SpeakerType())     /* 暫定 車パラI/F展開後に見直し */

#define u1_POWERIC_SET_PM_SYS_MUTE_L()              (Dio_WriteChannel(DIO_ID_PORT20_CH8, (Dio_LevelType)POWERIC_IO_STS_LOW))
#define u1_POWERIC_SET_PM_SYS_MUTE_H()              (Dio_WriteChannel(DIO_ID_PORT20_CH8, (Dio_LevelType)POWERIC_IO_STS_HIGH))
#define u1_POWERIC_SET_P_ON_L()                     (Dio_WriteChannel(DIO_ID_PORT11_CH6, (Dio_LevelType)POWERIC_IO_STS_LOW))
#define u1_POWERIC_SET_PIC_POFF_L()                 (Dio_WriteChannel(DIO_ID_PORT11_CH7, (Dio_LevelType)POWERIC_IO_STS_LOW))

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U1                          u1_offset_nml;      /* Power-IC SPK Offset Normal Count */
    U1                          u1_vccshrt_nml;     /* Power-IC SPK Vcc-Short Normal Count */
    U1                          u1_gndshrt_nml;     /* Power-IC SPK Gnd-Short Normal Count */
    U1                          u1_offset_fail;     /* Power-IC SPK Offset Fail Count */
    U1                          u1_vccshrt_fail;    /* Power-IC SPK Vcc-Short Fail Count */
    U1                          u1_gndshrt_fail;    /* Power-IC SPK Gnd-Short Fail Count */
}ST_POWERIC_DIAGCYC_READCNT;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void    vd_g_PowerIc_BonInit(void);
void    vd_g_PowerIc_WkupInit(void);
void    vd_g_PowerIc_Routine(void);
void    vd_g_PowerIc_TrunOnDiag_Req(void);
void    vd_g_PowerIc_SoftMuteSet(const U1 u1_a_softmute_sts);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif      /* POWERICCTL_H */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  PowerIcCtl.c                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/