/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
#ifndef MCU_SYS_PWR_GVIFSNDR_H
#define MCU_SYS_PWR_GVIFSNDR_H
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "gpi2c_ma.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR                      (0x48U)
#define MCU_SYS_PWR_GVIFSNDR_SLAVEADR_RD                      (0x49U)
#define MCU_SYS_PWR_GVIFSNDR_RWC_BYTE1                        (1U)
#define MCU_SYS_PWR_GVIFSNDR_RWC_BYTE2                        (2U)
#define MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3                        (3U)
#define MCU_SYS_PWR_GVIFSNDR_RWC_BYTE6                        (6U)
#define MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8                        (8U)
#define MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_NUM                  (22U)
#define MCU_SYS_PWR_GVIFSNDR_EDPSET1_NUM                      (3U)
#define MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_NUM                   (690U)
#define MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_NUM                  (156U)
#define MCU_SYS_PWR_GVIFSNDR_EDPSET2_NUM                      (1U)
#define MCU_SYS_PWR_GVIFSNDR_EDPSET3_NUM                      (3U)
#define MCU_SYS_PWR_GVIFSNDR_EDPSET_HPD_NUM                   (6U)
#define MCU_SYS_PWR_GVIFSNDR_OUTSET3_NUM                      (1U)
#define MCU_SYS_PWR_GVIFSNDR_OUTSET1_NUM                      (1U)
#define MCU_SYS_PWR_GVIFSNDR_OUTSET_GVIF3TX0_ACTIVATED_RD_NUM (2U)
#define MCU_SYS_PWR_GVIFSNDR_OUTSET2_NUM                      (5U)
#define MCU_SYS_PWR_GVIFSNDR_HDCP1_NUM                        (9U)
#define MCU_SYS_PWR_GVIFSNDR_HDCP2_NUM                        (1U)
#define MCU_SYS_PWR_GVIFSNDR_HDCP3_NUM                        (1U)
#define MCU_SYS_PWR_GVIFSNDR_HDCP4_NUM                        (4U)
#define MCU_SYS_PWR_GVIFSNDR_HDCP5_NUM                        (1U)
#define MCU_SYS_PWR_GVIFSNDR_HDCP6_NUM                        (1U)
#define MCU_SYS_PWR_GVIFSNDR_HDCPTX_STATUS_RD_NUM             (2U)
#define MCU_SYS_PWR_GVIFSNDR_HDCPTX_EVENT_RD_NUM              (2U)
#define MCU_SYS_PWR_GVIFSNDR_HDCP7_NUM                        (3U)
#define MCU_SYS_PWR_GVIFSNDR_HDCPTX_DEVS_CASCADE_RD_NUM       (2U)
#define MCU_SYS_PWR_GVIFSNDR_HDCPTX_DEV_ID_RD_NUM             (10U)
#define MCU_SYS_PWR_GVIFSNDR_ENCRYPT_NUM                      (1U)
#define MCU_SYS_PWR_GVIFSNDR_HDCP8_NUM                        (1U)
#define MCU_SYS_PWR_GVIFSNDR_HDCPTX_ENC_RD_NUM                (2U)
#define MCU_SYS_PWR_GVIFSNDR_HDCPSTOP_NUM                     (4U)
#define MCU_SYS_PWR_GVIFSNDR_GVIF3TX0_ACT_RD_NUM              (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void Mcu_Sys_Pwr_GvifSndr_Init( void );

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET1[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET2[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET3[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_HPD[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET3[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET1[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET_GVIF3TX0_ACTIVATED_RD[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET2[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GVIFSNDR_HDCP1[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GVIFSNDR_HDCP2[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_STATUS_RD[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_EVENT_RD[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GVIFSNDR_HDCP3[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_DEVS_CASCADE_RD[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_DEV_ID_RD[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GVIFSNDR_HDCP4[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GVIFSNDR_HDCP_HPD[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_ENC_RD[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GVIFSNDR_HDCP5[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GVIFSNDR_HDCPSTOP[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GVIFSNDR_HDCP6[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GVIFSNDR_GVIF3TX0_ACT_RD[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GVIFSNDR_HDCP7[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GVIFSNDR_HDCP8[];

#endif      /* MCU_SYS_PWR_GVIFSNDR_H */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  Mcu_Sys_Pwr_GvifSndr.c                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
