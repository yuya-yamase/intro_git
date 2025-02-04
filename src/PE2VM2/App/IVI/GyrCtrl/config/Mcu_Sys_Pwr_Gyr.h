/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
#ifndef MCU_SYS_PWR_GYR_H
#define MCU_SYS_PWR_GYR_H
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "gpi2c_ma.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MCU_SYS_PWR_GYR_SADR_GRY_WR                        (0xD2U)
#define MCU_SYS_PWR_GYR_SADR_GRY_RD                        (0xD3U)
#define MCU_SYS_PWR_GYR_SADR_ACC_WR                        (0x32U)
#define MCU_SYS_PWR_GYR_SADR_ACC_RD                        (0x33U)
#define MCU_SYS_PWR_GYR_SETUPTBL_NUM                       (2U)
#define MCU_SYS_PWR_GYR_WRTBL_NUM                          (1U)
#define MCU_SYS_PWR_GYR_RDTBL_NUM                          (2U)
#define MCU_SYS_PWR_GYR_TX_TXDAT_NUM                       (3U)
#define MCU_SYS_PWR_GYR_TX_RDREGADR_NUM                    (2U)
#define MCU_SYS_PWR_GYR_TX_RDSADR_NUM                      (1U)

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
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GYR_REG_GYR_SETUP[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GYR_REG_GYR_TEST[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GYR_REG_GYR_TEST_RD[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GYR_REG_GYR_WDG[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GYR_REG_GYR_MODE_ON[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GYR_REG_GYR_MODE_OFF[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GYR_REG_ACC_SEN1_SETUP[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GYR_REG_ACC_SEN2_SETUP[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GYR_REG_ACC_WDG[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GYR_REG_ACC_MODE_ON[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GYR_REG_ACC_MODE_OFF[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GYR_REG_ACC_PLSTEST[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GYR_REG_ACC_MNSTEST[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GYR_REG_ACC_DISTEST[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GYR_REG_GYR_XLSB[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GYR_REG_GYR_XMSB[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GYR_REG_GYR_YLSB[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GYR_REG_GYR_YMSB[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GYR_REG_GYR_ZLSB[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GYR_REG_GYR_ZMSB[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GYR_REG_GYR_TEMPLSB[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_PWR_GYR_REG_GYR_TEMPMSB[];


#endif      /* MCU_SYS_PWR_GYR_H */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  Mcu_Sys_Pwr_Gyr.c                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
