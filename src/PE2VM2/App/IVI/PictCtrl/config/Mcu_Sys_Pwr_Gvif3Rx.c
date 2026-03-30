/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "Mcu_Sys_Pwr_Gvif3Rx.h"
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_BANK0[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_RMTACC_SET5[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xE8U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_PIN_SET1[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x97U,    /* Write Address */
    (U1)0x20U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_PIN_SET2[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x98U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_GPIO1[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xECU,    /* Write Address */
    (U1)0x30U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_GPIO4[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xEEU,    /* Write Address */
    (U1)0x06U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_RX0_SET1[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x80U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_RX0_SET2[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x83U,    /* Write Address */
    (U1)0x16U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_TX0_SET1[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x60U,    /* Write Address */
    (U1)0x12U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD0_2_INIT[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x9FU,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD0_1[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x9EU,    /* Write Address */
    (U1)0x11U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD0_3[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA2U,    /* Write Address */
    (U1)0x38U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD1_2_INIT[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA8U,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD1_1[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA7U,    /* Write Address */
    (U1)0x11U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD1_3[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xABU,    /* Write Address */
    (U1)0x08U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_BANK2[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_RX1_SET1_DIS[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x80U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_RX1_SET2[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x83U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD2_2_INIT[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x9FU,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD2_1[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x9EU,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD2_3[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA2U,    /* Write Address */
    (U1)0x18U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD3_2_INIT[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA8U,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD3_1[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA7U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD3_3[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xABU,    /* Write Address */
    (U1)0x28U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_BANK3[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_RX2_SET1[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x71U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_RX3_SET1[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x80U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD4_2_INIT[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA8U,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD4_1[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA7U,    /* Write Address */
    (U1)0x59U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD4_3[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xABU,    /* Write Address */
    (U1)0x44U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD5_2_INIT[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xB1U,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD5_1[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xB0U,    /* Write Address */
    (U1)0x59U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD5_3[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xB4U,    /* Write Address */
    (U1)0x54U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD6_1[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xB9U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD7_1[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC2U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_BANK1[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX0_0_SET16[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x5DU,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX0_1_SET16[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x5DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX1_2_SET16[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x5DU,    /* Write Address */
    (U1)0x32U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX1_3_SET16[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD_COMMON2[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x9CU,    /* Write Address */
    (U1)0xCCU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_PLL0_SET4[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x66U,    /* Write Address */
    (U1)0x09U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_PLL0_SET3[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x65U,    /* Write Address */
    (U1)0x20U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_PLL0_SET1[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x61U,    /* Write Address */
    (U1)0x80U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_PLL0_SET2[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x62U,    /* Write Address */
    (U1)0x76U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_PLL0_SET5[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x63U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_PLL0_SET6[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x5FU,    /* Write Address */
    (U1)0x57U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_PLL0_SET7[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x60U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX0_0_SET2[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x4EU,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX0_0_SET3[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x4FU,    /* Write Address */
    (U1)0x1AU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX0_0_SET6[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x52U,    /* Write Address */
    (U1)0x1AU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX0_0_SET5[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x51U,    /* Write Address */
    (U1)0x08U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX0_0_SET10[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x56U,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX0_0_SET7[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x53U,    /* Write Address */
    (U1)0x06U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX0_0_SET8[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x54U,    /* Write Address */
    (U1)0x17U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX0_0_SET11[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x57U,    /* Write Address */
    (U1)0x1AU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX0_0_SET14[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x5AU,    /* Write Address */
    (U1)0x16U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX0_0_SET1[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x4DU,    /* Write Address */
    (U1)0x14U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX0_0_SET12[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x58U,    /* Write Address */
    (U1)0x1AU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_RX0_SET9[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x86U,    /* Write Address */
    (U1)0x40U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_RX1_SET9[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xE9U,    /* Write Address */
    (U1)0xFBU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX0_1_SET2[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x4EU,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX0_1_SET3[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x4FU,    /* Write Address */
    (U1)0x1AU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX0_1_SET6[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x52U,    /* Write Address */
    (U1)0x1AU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX0_1_SET5[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x51U,    /* Write Address */
    (U1)0x08U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX0_1_SET10[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x56U,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX0_1_SET7[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x53U,    /* Write Address */
    (U1)0x06U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX0_1_SET8[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x54U,    /* Write Address */
    (U1)0x17U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX0_1_SET11[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x57U,    /* Write Address */
    (U1)0x1AU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX0_1_SET14[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x5AU,    /* Write Address */
    (U1)0x16U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_PLL1_SET4[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x4AU,    /* Write Address */
    (U1)0x08U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_PLL1_SET3[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x49U,    /* Write Address */
    (U1)0x20U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_PLL1_SET1[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x80U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_PLL1_SET2[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x46U,    /* Write Address */
    (U1)0xB2U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_PLL1_SET5[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x47U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_PLL1_SET6[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x19U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_PLL1_SET7[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x44U,    /* Write Address */
    (U1)0x99U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX1_2_SET2[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x4EU,    /* Write Address */
    (U1)0x07U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX1_2_SET3[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x4FU,    /* Write Address */
    (U1)0x25U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX1_2_SET6[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x52U,    /* Write Address */
    (U1)0x25U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX1_2_SET5[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x51U,    /* Write Address */
    (U1)0x0FU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX1_2_SET10[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x56U,    /* Write Address */
    (U1)0x06U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX1_2_SET7[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x53U,    /* Write Address */
    (U1)0x08U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX1_2_SET8[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x54U,    /* Write Address */
    (U1)0x21U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX1_2_SET11[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x57U,    /* Write Address */
    (U1)0x25U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX1_2_SET14[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x5AU,    /* Write Address */
    (U1)0x20U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX1_2_SET1[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x4DU,    /* Write Address */
    (U1)0x14U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX1_2_SET12[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x58U,    /* Write Address */
    (U1)0x1AU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX1_3_SET2[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x60U,    /* Write Address */
    (U1)0x07U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX1_3_SET3[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x61U,    /* Write Address */
    (U1)0x25U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX1_3_SET6[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x64U,    /* Write Address */
    (U1)0x25U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX1_3_SET5[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x63U,    /* Write Address */
    (U1)0x0FU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX1_3_SET10[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x68U,    /* Write Address */
    (U1)0x06U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX1_3_SET7[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x65U,    /* Write Address */
    (U1)0x08U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX1_3_SET8[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x66U,    /* Write Address */
    (U1)0x21U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX1_3_SET11[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x69U,    /* Write Address */
    (U1)0x25U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX1_3_SET14[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6CU,    /* Write Address */
    (U1)0x20U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_RX0_SET0[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x80U,    /* Write Address */
    (U1)0x0BU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_GPIO3_INIT[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF0U,    /* Write Address */
    (U1)0x30U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_RX1_SET1_ENA[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x80U,    /* Write Address */
    (U1)0x0BU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD0_2_CAMNON[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x9FU,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD1_2_CAMNON[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA8U,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD2_2_CAMNON[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x9FU,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD3_2_CAMNON[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA8U,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD4_2_CAMNON[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA8U,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD5_2_CAMNON[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xB1U,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_GPIO3_CAMNON[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF0U,    /* Write Address */
    (U1)0x30U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_ERRCLR_SET[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2EU,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_ERRCLE_RLS[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD0_2_DOMCON[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x9FU,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD1_2_DOMCON[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA8U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD2_2_DOMCON[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x9FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD3_2_DOMCON[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA8U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD4_2_DOMCON[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA8U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD5_2_DOMCON[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xB1U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIF3RX_GPIO3_DOMCON[MCU_SYS_PWR_GVIF3RX_REG_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF0U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIF3RX_REG_INIT[MCU_SYS_PWR_GVIF3RX_REG_INIT_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_BANK0[0],
        (U4)0x20040003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_RMTACC_SET5[0],
        (U4)0x20080003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_PIN_SET1[0],
        (U4)0x200C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_PIN_SET2[0],
        (U4)0x20100003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_GPIO1[0],
        (U4)0x20140003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_GPIO4[0],
        (U4)0x20180003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_RX0_SET1[0],
        (U4)0x201C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_RX0_SET2[0],
        (U4)0x20200003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_TX0_SET1[0],
        (U4)0x20240003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD0_2_INIT[0],
        (U4)0x20280003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD0_1[0],
        (U4)0x202C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD0_3[0],
        (U4)0x20300003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD1_2_INIT[0],
        (U4)0x20340003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD1_1[0],
        (U4)0x20380003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD1_3[0],
        (U4)0x203C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_BANK2[0],
        (U4)0x20400003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_RX1_SET1_DIS[0],
        (U4)0x20440003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_RX1_SET2[0],
        (U4)0x20480003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD2_2_INIT[0],
        (U4)0x204C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD2_1[0],
        (U4)0x20500003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD2_3[0],
        (U4)0x20540003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD3_2_INIT[0],
        (U4)0x20580003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD3_1[0],
        (U4)0x205C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD3_3[0],
        (U4)0x20600003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_BANK3[0],
        (U4)0x20640003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_RX2_SET1[0],
        (U4)0x20680003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_RX3_SET1[0],
        (U4)0x206C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD4_2_INIT[0],
        (U4)0x20700003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD4_1[0],
        (U4)0x20740003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD4_3[0],
        (U4)0x20780003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD5_2_INIT[0],
        (U4)0x207C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD5_1[0],
        (U4)0x20800003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD5_3[0],
        (U4)0x20840003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD6_1[0],
        (U4)0x20880003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD7_1[0],
        (U4)0x208C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_BANK1[0],
        (U4)0x20900003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX0_0_SET16[0],
        (U4)0x21C40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_BANK2[0],
        (U4)0x21C80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX0_1_SET16[0],
        (U4)0x20940003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_BANK3[0],
        (U4)0x20980003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX1_2_SET16[0],
        (U4)0x21CC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX1_3_SET16[0],
        (U4)0x209C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_BANK0[0],
        (U4)0x20A00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD_COMMON2[0],
        (U4)0x20A40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_BANK1[0],
        (U4)0x20A80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_PLL0_SET4[0],
        (U4)0x20AC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_PLL0_SET3[0],
        (U4)0x20B00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_PLL0_SET1[0],
        (U4)0x20B40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_PLL0_SET2[0],
        (U4)0x20B80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_PLL0_SET5[0],
        (U4)0x20BC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_PLL0_SET6[0],
        (U4)0x20C00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_PLL0_SET7[0],
        (U4)0x20C40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX0_0_SET2[0],
        (U4)0x20C80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX0_0_SET3[0],
        (U4)0x20CC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX0_0_SET6[0],
        (U4)0x20D00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX0_0_SET5[0],
        (U4)0x20D40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX0_0_SET10[0],
        (U4)0x20D80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX0_0_SET7[0],
        (U4)0x20DC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX0_0_SET8[0],
        (U4)0x20E00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX0_0_SET11[0],
        (U4)0x20E40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX0_0_SET14[0],
        (U4)0x20E80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX0_0_SET1[0],
        (U4)0x20EC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX0_0_SET12[0],
        (U4)0x20F00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_RX0_SET9[0],
        (U4)0x20F40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_BANK2[0],
        (U4)0x20F80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_RX1_SET9[0],
        (U4)0x21D00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX0_1_SET2[0],
        (U4)0x21D40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX0_1_SET3[0],
        (U4)0x21D80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX0_1_SET6[0],
        (U4)0x21DC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX0_1_SET5[0],
        (U4)0x21E00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX0_1_SET10[0],
        (U4)0x21E40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX0_1_SET7[0],
        (U4)0x21E80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX0_1_SET8[0],
        (U4)0x21EC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX0_1_SET11[0],
        (U4)0x21F00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX0_1_SET14[0],
        (U4)0x20FC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_BANK3[0],
        (U4)0x21000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_PLL1_SET4[0],
        (U4)0x21040003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_PLL1_SET3[0],
        (U4)0x21080003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_PLL1_SET1[0],
        (U4)0x210C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_PLL1_SET2[0],
        (U4)0x21100003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_PLL1_SET5[0],
        (U4)0x21140003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_PLL1_SET6[0],
        (U4)0x21180003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_PLL1_SET7[0],
        (U4)0x211C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX1_2_SET2[0],
        (U4)0x21200003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX1_2_SET3[0],
        (U4)0x21240003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX1_2_SET6[0],
        (U4)0x21280003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX1_2_SET5[0],
        (U4)0x212C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX1_2_SET10[0],
        (U4)0x21300003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX1_2_SET7[0],
        (U4)0x21340003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX1_2_SET8[0],
        (U4)0x21380003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX1_2_SET11[0],
        (U4)0x213C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX1_2_SET14[0],
        (U4)0x21400003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX1_2_SET1[0],
        (U4)0x21440003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX1_2_SET12[0],
        (U4)0x21F40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX1_3_SET2[0],
        (U4)0x21F80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX1_3_SET3[0],
        (U4)0x21FC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX1_3_SET6[0],
        (U4)0x22000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX1_3_SET5[0],
        (U4)0x22040003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX1_3_SET10[0],
        (U4)0x22080003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX1_3_SET7[0],
        (U4)0x220C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX1_3_SET8[0],
        (U4)0x22100003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX1_3_SET11[0],
        (U4)0x22140003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_MIPITX1_3_SET14[0],
        (U4)0x21480003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_BANK0[0],
        (U4)0x214C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_RX0_SET0[0],
        (U4)0x21500003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_GPIO3_INIT[0],
        (U4)0x21540003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_BANK2[0],
        (U4)0x21580003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_RX1_SET1_ENA[0],
        (U4)0x215C0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIF3RX_REG_CAMNON[MCU_SYS_PWR_GVIF3RX_REG_CAMKIND_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_BANK0[0],
        (U4)0x21600003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD_COMMON2[0],
        (U4)0x21640003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD0_2_CAMNON[0],
        (U4)0x21680003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD1_2_CAMNON[0],
        (U4)0x216C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_BANK2[0],
        (U4)0x21700003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD2_2_CAMNON[0],
        (U4)0x21740003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD3_2_CAMNON[0],
        (U4)0x21780003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_BANK3[0],
        (U4)0x217C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD4_2_CAMNON[0],
        (U4)0x21800003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD5_2_CAMNON[0],
        (U4)0x21840003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_BANK0[0],
        (U4)0x21880003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_GPIO3_CAMNON[0],
        (U4)0x218C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_ERRCLR_SET[0],
        (U4)0x21900003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_ERRCLE_RLS[0],
        (U4)0x21940003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIF3RX_REG_DOMCON[MCU_SYS_PWR_GVIF3RX_REG_CAMKIND_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_BANK0[0],
        (U4)0x21980003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD_COMMON2[0],
        (U4)0x219C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD0_2_DOMCON[0],
        (U4)0x21A00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD1_2_DOMCON[0],
        (U4)0x21A40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_BANK2[0],
        (U4)0x21A80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD2_2_DOMCON[0],
        (U4)0x21AC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD3_2_DOMCON[0],
        (U4)0x21B00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_BANK3[0],
        (U4)0x21B40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD4_2_DOMCON[0],
        (U4)0x21B80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_UNLD5_2_DOMCON[0],
        (U4)0x21BC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_BANK0[0],
        (U4)0x21C00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_GPIO3_DOMCON[0],
        (U4)0x21C40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_ERRCLR_SET[0],
        (U4)0x21C80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIF3RX_ERRCLE_RLS[0],
        (U4)0x21CC0003U
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  0.0.0    12/06/2024  TN       New.                                                                                               */
/*                                                                                                                                   */
/*  * TN   = Tatsuya Niimi, KSE                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/
