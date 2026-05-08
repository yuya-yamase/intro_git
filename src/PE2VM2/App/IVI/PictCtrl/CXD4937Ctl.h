/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
#ifndef CXD4937CTL_H
#define CXD4937CTL_H
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"

#include "Dio.h"
#include "gpi2c_ma.h"
#include "Mcu_I2c_Ctrl_private.h"
#include "SysEcDrc.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Register Access Data */
#define CXD4937_I2C_SLAVEADR_WR                 (0x48U)
#define CXD4937_I2C_SLAVEADR_RD                 (0x49U)
#define CXD4937_I2C_RWC_BYTE1                   (1U)
#define CXD4937_I2C_RWC_BYTE2                   (2U)
#define CXD4937_I2C_RWC_BYTE3                   (3U)
#define CXD4937_I2C_RWC_BYTE6                   (6U)
#define CXD4937_I2C_RWC_BYTE8                   (8U)

/* Register Bit Mask */
#define PICT_CXD_REG_MASK_BIT_0                 (0x01U)
#define PICT_CXD_REG_MASK_BIT_1                 (0x02U)
#define PICT_CXD_REG_MASK_BIT_2                 (0x04U)
#define PICT_CXD_REG_MASK_BIT_3                 (0x08U)
#define PICT_CXD_REG_MASK_BIT_4                 (0x10U)
#define PICT_CXD_REG_MASK_BIT_5                 (0x20U)
#define PICT_CXD_REG_MASK_BIT_6                 (0x40U)
#define PICT_CXD_REG_MASK_BIT_7                 (0x80U)

/* Register Read Result */
#define PICT_CXD_REG_READ_NG                    (0U)
#define PICT_CXD_REG_READ_OK                    (1U)

#define PICT_GVIFSNDRDEVERR_NML                 (0x40U)
#define CXD4937_DEVERR_DREC_CNT_MAX             (3U)

#define PICT_GVIFSNDRGVIFLINK_NML               (0x00U)
#define PICT_GVIFSNDRGVIFLINK_CHK_CNT_MAX       (5U)

#define PICT_GVIFSNDREDPERR_1                   (0x77U)
#define PICT_GVIFSNDREDPERR_2                   (0x77U)
#define CXD4937_EDPERR_STS_NORMAL               (0x00U)
#define CXD4937_EDPERR_STS_ERROR                (0x01U)
#define CXD4937_EDPERR_STS_INIT                 (0xFFU)
#define CXD4937_EDPERR1_DREC_CNT_MAX            (3U)
#define CXD4937_EDPERR2_DREC_CNT_MAX            (3U)
#define CXD4937_EDPERR3_DREC_CNT_MAX            (3U)

#define PICT_GVIFSNDRLODERERR_NML               (0x00U)

#define CXD4937_VIDEOERR_DREC_CNT_MAX           (3U)
#define CXD4937_LOADERERR_DREC_CNT_MAX          (3U)
#define CXD4937_CNCTERR_DREC_CNT_MAX            (3U)

#define CXD4937_LINKERR_STS_NORMAL              (0x00U)
#define CXD4937_LINKERR_STS_ERROR               (0x01U)
#define CXD4937_LINKERR_STS_INIT                (0xFFU)
#define CXD4937_LINKERR_DREC_CNT_MAX            (3U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define PICT_CXD_IO_STS_LOW                     (0U)
#define PICT_CXD_IO_STS_HIGH                    (1U)

#define PICT_CXD_PWRON_COMP                     (MCU_STEP_GVIF3TX_OVERALL_FIN)

#define u1_PICT_CXD_I2C_CTRL_REGSET(u, v, w, x, y, z)    (Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_GVIF_TX, (u), (v), (U1)GP_I2C_MA_SLA_3_GVIF_TX, (w), (x), (y), (z)))
#define u1_PICT_CXD_I2C_CTRL_REGREAD_WAIT(w, x, y, z, wait)    (Mcu_Dev_I2c_Ctrl_RegRead((U1)MCU_I2C_ACK_GVIF_TX, (w), (U1)GP_I2C_MA_SLA_3_GVIF_TX, (x), (y), (z), (U1)(wait)))
#define u1_PICT_CXD_I2C_CTRL_REGREAD(w, x, y, z)               (u1_PICT_CXD_I2C_CTRL_REGREAD_WAIT((w), (x), (y), (z), (U1)MCU_I2C_WAIT_NON))

#define vd_CXD4937_DREC_REQ(x, y, z)            (vd_g_SysEcDrc_Drec((U1)SYSECDRC_DREC_CAT_GVIFTX, (x), (y), (z)))

#define vd_PICT_CXD_GVIF_TX_RST_L()             (Dio_WriteChannel(DIO_ID_PORT17_CH4, (Dio_LevelType)PICT_CXD_IO_STS_LOW))
#define vd_PICT_CXD_GVIF_TX_RST_H()             (Dio_WriteChannel(DIO_ID_PORT17_CH4, (Dio_LevelType)PICT_CXD_IO_STS_HIGH))


#define MCU_GVIFTX_TASK_TIME            (1U)    /* �����̎��Ԏw��(LSB:1ms) */

/* �t���[ */
#define MCU_STEP_GVIF3TX_OVERALL_1      (1U)    /* 100-4-2.�����ݒ�t���[ */
#define MCU_STEP_GVIF3TX_OVERALL_2      (2U)    /* 100-4-3.eDP�ݒ�t���[ */
#define MCU_STEP_GVIF3TX_OVERALL_3      (3U)    /* 100-4-4.�o�͐ݒ�t���[ */
#define MCU_STEP_GVIF3TX_OVERALL_4      (4U)    /* 100-4-5.HDCP�F�؃t���[ */
#define MCU_STEP_GVIF3TX_OVERALL_FIN    (5U)    /* 100-4-7.����Ď��t���[ */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void    vd_g_Pict_GvifSndrInit(void);
void    vd_g_Pict_GvifSndrRoutine(void);

void    vd_g_GvifTx_HADC_Act_Hook(void);
U1      u1_g_Pict_GvifSndrHdpSet(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern uint8    u1_g_gvifsnd_gvif3tx_overall_step;

#endif      /* CXD4937CTL_H */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  CXD4937Ctl.c                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/