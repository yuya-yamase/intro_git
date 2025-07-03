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
#define MCU_SYS_PWR_GYR_SADR_GRY_WR                     (0xD2U)
#define MCU_SYS_PWR_GYR_SADR_GRY_RD                     (0xD3U)
#define MCU_SYS_PWR_GYR_SADR_ACC_WR                     (0x32U)
#define MCU_SYS_PWR_GYR_SADR_ACC_RD                     (0x33U)
#define MCU_SYS_PWR_GYR_SETUPTBL_NUM                    (2U)
#define MCU_SYS_PWR_GYR_WRTBL_NUM                       (1U)
#define MCU_SYS_PWR_GYR_RDTBL_NUM                       (2U)
#define MCU_SYS_PWR_GYR_TX_TXDAT_NUM                    (3U)
#define MCU_SYS_PWR_GYR_TX_RDREGADR_NUM                 (2U)
#define MCU_SYS_PWR_GYR_TX_RDSADR_NUM                   (2U)
#define MCU_SYS_PWR_GYR_RDTBL_XYZ_NUM                   (7U)
#define MCU_SYS_PWR_GYR_TX_BURSTDAT_NUM                 (4U)
#define MCU_SYS_PWR_GYR_INTTBL_ANYMOT_NUM               (4U)
#define MCU_SYS_PWR_GYR_INTTBL_OTH_NUM                  (3U)
#define MCU_SYS_PWR_GYR_TX_CFGDATA_NUM                  (34U)

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
void            vd_g_GyroSysPwrInit(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern const ST_GP_I2C_MA_REQ       st_sp_MCU_SYS_PWR_GYR_REG_GYR_SETUP[];
extern const ST_GP_I2C_MA_REQ       st_sp_MCU_SYS_PWR_GYR_REG_GYR_TEST[];
extern const ST_GP_I2C_MA_REQ       st_sp_MCU_SYS_PWR_GYR_REG_GYR_TEST_RD[];
extern const ST_GP_I2C_MA_REQ       st_sp_MCU_SYS_PWR_GYR_REG_GYR_WDG[];
extern const ST_GP_I2C_MA_REQ       st_sp_MCU_SYS_PWR_GYR_REG_GYR_MODE_ON[];
extern const ST_GP_I2C_MA_REQ       st_sp_MCU_SYS_PWR_GYR_REG_GYR_MODE_OFF[];
extern const ST_GP_I2C_MA_REQ       st_sp_MCU_SYS_PWR_GYR_REG_GYR_MODE_RD[];
extern const ST_GP_I2C_MA_REQ       st_sp_MCU_SYS_PWR_GYR_REG_ACC_SEN1_SETUP[];
extern const ST_GP_I2C_MA_REQ       st_sp_MCU_SYS_PWR_GYR_REG_ACC_SEN2_SETUP[];
extern const ST_GP_I2C_MA_REQ       st_sp_MCU_SYS_PWR_GYR_REG_ACC_WDG[];
extern const ST_GP_I2C_MA_REQ       st_sp_MCU_SYS_PWR_GYR_REG_ACC_MODE_ON[];
extern const ST_GP_I2C_MA_REQ       st_sp_MCU_SYS_PWR_GYR_REG_ACC_MODE_OFF[];
extern const ST_GP_I2C_MA_REQ       st_sp_MCU_SYS_PWR_GYR_REG_ACC_PLSTEST[];
extern const ST_GP_I2C_MA_REQ       st_sp_MCU_SYS_PWR_GYR_REG_ACC_MNSTEST[];
extern const ST_GP_I2C_MA_REQ       st_sp_MCU_SYS_PWR_GYR_REG_ACC_DISTEST[];
extern const ST_GP_I2C_MA_REQ       st_sp_MCU_SYS_PWR_GYR_REG_GYR_XYZ[];
extern const ST_GP_I2C_MA_REQ       st_sp_MCU_SYS_PWR_GYR_REG_GYR_TEMP[];
extern const ST_GP_I2C_MA_REQ       st_sp_MCU_SYS_PWR_GYR_REG_ACC_PWRCONF_ON[]; 
extern const ST_GP_I2C_MA_REQ       st_sp_MCU_SYS_PWR_GYR_REG_ACC_PWRCONF_OFF[];
extern const ST_GP_I2C_MA_REQ       st_sp_MCU_SYS_PWR_GYR_REG_ACC_INTCONF_ON[];
extern const ST_GP_I2C_MA_REQ       st_sp_MCU_SYS_PWR_GYR_REG_ACC_INTCONF_OFF[];
extern const ST_GP_I2C_MA_REQ       st_sp_MCU_SYS_PWR_GYR_REG_ACC_INTCONF_READ[];
extern const ST_GP_I2C_MA_REQ       st_sp_MCU_SYS_PWR_GYR_REG_ACC_SOFTRESET[];
extern const ST_GP_I2C_MA_REQ       st_sp_MCU_SYS_PWR_GYR_REG_INTSET_ANYMOT_TH[];
extern const ST_GP_I2C_MA_REQ       st_sp_MCU_SYS_PWR_GYR_REG_INTSET_ANYMOT_EN[];
extern const ST_GP_I2C_MA_REQ       st_sp_MCU_SYS_PWR_GYR_REG_INTSET_OTH[];
extern const ST_GP_I2C_MA_REQ       st_sp_MCU_SYS_PWR_GYR_REG_ACC_SEN1_BW_INPRM[];
extern const ST_GP_I2C_MA_REQ       st_sp_MCU_SYS_PWR_GYR_REG_ACC_CFG1[];
extern const ST_GP_I2C_MA_REQ       st_sp_MCU_SYS_PWR_GYR_REG_ACC_CFG2[];
extern const ST_GP_I2C_MA_REQ       st_sp_MCU_SYS_PWR_GYR_REG_ACC_DATA[];

#endif      /* MCU_SYS_PWR_GYR_H */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  Mcu_Sys_Pwr_Gyr.c                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
