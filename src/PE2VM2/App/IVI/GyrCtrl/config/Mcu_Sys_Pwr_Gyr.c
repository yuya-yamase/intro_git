/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "Mcu_Sys_Pwr_Gyr.h"
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
const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_BW[MCU_SYS_PWR_GYR_TX_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_GRY_WR,    /* Slave Address */
    (U1)0x10U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_RANGE[MCU_SYS_PWR_GYR_TX_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_GRY_WR,    /* Slave Address */
    (U1)0x0FU,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_TEST[MCU_SYS_PWR_GYR_TX_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_GRY_WR,    /* Slave Address */
    (U1)0x3CU,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_TEST_RD[MCU_SYS_PWR_GYR_TX_RDREGADR_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_GRY_WR,    /* Slave Address */
    (U1)0x3CU     /* Write Address */
};

U1 u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_READ[MCU_SYS_PWR_GYR_TX_RDSADR_NUM];

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_WDG[MCU_SYS_PWR_GYR_TX_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_GRY_WR,    /* Slave Address */
    (U1)0x34U,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_MODE_NML[MCU_SYS_PWR_GYR_TX_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_GRY_WR,    /* Slave Address */
    (U1)0x11U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_MODE_SPD[MCU_SYS_PWR_GYR_TX_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_GRY_WR,    /* Slave Address */
    (U1)0x11U,    /* Write Address */
    (U1)0x80U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_MODE_RD[MCU_SYS_PWR_GYR_TX_RDREGADR_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_GRY_WR,    /* Slave Address */
    (U1)0x11U     /* Write Address */
};

U1 u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_MODE_READ[MCU_SYS_PWR_GYR_TX_RDSADR_NUM];

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_SEN1_BW[MCU_SYS_PWR_GYR_TX_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_ACC_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0xA8U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_SEN1_RANGE[MCU_SYS_PWR_GYR_TX_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_ACC_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_SEN2_BW[MCU_SYS_PWR_GYR_TX_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_ACC_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0xACU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_SEN2_RANGE[MCU_SYS_PWR_GYR_TX_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_ACC_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_WDG[MCU_SYS_PWR_GYR_TX_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_ACC_WR,    /* Slave Address */
    (U1)0x70U,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_MODE_NML[MCU_SYS_PWR_GYR_TX_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_ACC_WR,    /* Slave Address */
    (U1)0x7DU,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_MODE_SPD[MCU_SYS_PWR_GYR_TX_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_ACC_WR,    /* Slave Address */
    (U1)0x7DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_PLSTEST[MCU_SYS_PWR_GYR_TX_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_ACC_WR,    /* Slave Address */
    (U1)0x6DU,    /* Write Address */
    (U1)0x0DU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_MNSTEST[MCU_SYS_PWR_GYR_TX_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_ACC_WR,    /* Slave Address */
    (U1)0x6DU,    /* Write Address */
    (U1)0x09U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_DISTEST[MCU_SYS_PWR_GYR_TX_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_ACC_WR,    /* Slave Address */
    (U1)0x6DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_XYZ[MCU_SYS_PWR_GYR_TX_RDREGADR_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_ACC_WR,    /* Slave Address */
    (U1)0x12U     /* Write Address */
};

U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_READ_XYZ[MCU_SYS_PWR_GYR_RDTBL_XYZ_NUM];

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_TEMP[MCU_SYS_PWR_GYR_TX_RDREGADR_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_ACC_WR,    /* Slave Address */
    (U1)0x22U     /* Write Address */
};

U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_READ_TEMP[MCU_SYS_PWR_GYR_TX_RDSADR_NUM];

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_PWRCONF_ON[MCU_SYS_PWR_GYR_TX_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_ACC_WR,    /* Slave Address */
    (U1)0x7CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_PWRCONF_OFF[MCU_SYS_PWR_GYR_TX_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_ACC_WR,    /* Slave Address */
    (U1)0x7CU,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INTCONF_ON[MCU_SYS_PWR_GYR_TX_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_ACC_WR,    /* Slave Address */
    (U1)0x59U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INTCONF_OFF[MCU_SYS_PWR_GYR_TX_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_ACC_WR,    /* Slave Address */
    (U1)0x59U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INTCONF_RD[MCU_SYS_PWR_GYR_TX_RDREGADR_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_ACC_WR,    /* Slave Address */
    (U1)0x2AU     /* Write Address */
};

U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INTCONF_DT[MCU_SYS_PWR_GYR_TX_RDSADR_NUM];

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_SOFTRESE[MCU_SYS_PWR_GYR_TX_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_ACC_WR,    /* Slave Address */
    (U1)0x7EU,    /* Write Address */
    (U1)0xB6U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INT_ANYMOT_TH_LSB[MCU_SYS_PWR_GYR_TX_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_ACC_WR,    /* Slave Address */
    (U1)0x5BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INT_ANYMOT_TH_MSB[MCU_SYS_PWR_GYR_TX_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_ACC_WR,    /* Slave Address */
    (U1)0x5CU,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INT_ANYMOT_TH_DAT[MCU_SYS_PWR_GYR_TX_BURSTDAT_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_ACC_WR,
    (U1)0x5EU,    /* Write Address   */
    (U1)0xFFU,    /* Write Data 0x5E */
    (U1)0x03U     /* Write Data 0x5F */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INT_ANYMOT_EN_LSB[MCU_SYS_PWR_GYR_TX_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_ACC_WR,    /* Slave Address */
    (U1)0x5BU,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INT_ANYMOT_EN_MSB[MCU_SYS_PWR_GYR_TX_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_ACC_WR,    /* Slave Address */
    (U1)0x5CU,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INT_ANYMOT_EN_DAT[MCU_SYS_PWR_GYR_TX_BURSTDAT_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_ACC_WR,
    (U1)0x5EU,    /* Write Address   */
    (U1)0x01U,    /* Write Data 0x5E */
    (U1)0xE0U     /* Write Data 0x5F */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INT2_IO_CONF[MCU_SYS_PWR_GYR_TX_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_ACC_WR,    /* Slave Address */
    (U1)0x54U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INT_LATCH[MCU_SYS_PWR_GYR_TX_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_ACC_WR,    /* Slave Address */
    (U1)0x55U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INT2_MAP[MCU_SYS_PWR_GYR_TX_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_ACC_WR,    /* Slave Address */
    (U1)0x57U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_CFG1[MCU_SYS_PWR_GYR_TX_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_ACC_WR,    /* Slave Address */
    (U1)0x5BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_CFG2[MCU_SYS_PWR_GYR_TX_TXDAT_NUM];

U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_DATA[MCU_SYS_PWR_GYR_TX_CFGDATA_NUM];

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_SEN1_BW_INPRM[MCU_SYS_PWR_GYR_TX_TXDAT_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_ACC_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0xACU     /* Write Data */
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_GYR_SETUP[MCU_SYS_PWR_GYR_SETUPTBL_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_BW[0],
        (U4)0x60040003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_RANGE[0],
        (U4)0x60080003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_GYR_TEST[MCU_SYS_PWR_GYR_WRTBL_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_TEST[0],
        (U4)0x600C0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_GYR_TEST_RD[MCU_SYS_PWR_GYR_RDTBL_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_TEST_RD[0],
        (U4)0x60100002U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_READ[0],
        (U4)0x60140002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_GYR_WDG[MCU_SYS_PWR_GYR_WRTBL_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_WDG[0],
        (U4)0x60180003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_GYR_MODE_ON[MCU_SYS_PWR_GYR_WRTBL_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_MODE_NML[0],
        (U4)0x601C0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_GYR_MODE_OFF[MCU_SYS_PWR_GYR_WRTBL_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_MODE_SPD[0],
        (U4)0x60200003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_GYR_MODE_RD[MCU_SYS_PWR_GYR_RDTBL_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_MODE_RD[0],
        (U4)0x60240002U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_MODE_READ[0],
        (U4)0x60280002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_ACC_SEN1_SETUP[MCU_SYS_PWR_GYR_SETUPTBL_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_SEN1_BW[0],
        (U4)0x702C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_SEN1_RANGE[0],
        (U4)0x70300003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_ACC_SEN2_SETUP[MCU_SYS_PWR_GYR_SETUPTBL_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_SEN2_BW[0],
        (U4)0x70340003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_SEN2_RANGE[0],
        (U4)0x70380003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_ACC_WDG[MCU_SYS_PWR_GYR_WRTBL_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_WDG[0],
        (U4)0x703C0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_ACC_MODE_ON[MCU_SYS_PWR_GYR_WRTBL_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_MODE_NML[0],
        (U4)0x70400003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_ACC_MODE_OFF[MCU_SYS_PWR_GYR_WRTBL_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_MODE_SPD[0],
        (U4)0x70440003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_ACC_PLSTEST[MCU_SYS_PWR_GYR_WRTBL_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_PLSTEST[0],
        (U4)0x70480003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_ACC_MNSTEST[MCU_SYS_PWR_GYR_WRTBL_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_MNSTEST[0],
        (U4)0x704C0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_ACC_DISTEST[MCU_SYS_PWR_GYR_WRTBL_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_DISTEST[0],
        (U4)0x70500003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_GYR_XYZ[MCU_SYS_PWR_GYR_RDTBL_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_XYZ[0],
        (U4)0x70540002U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_READ_XYZ[0],
        (U4)0x70580007U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_GYR_TEMP[MCU_SYS_PWR_GYR_RDTBL_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_TEMP[0],
        (U4)0x705C0002U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_READ_TEMP[0],
        (U4)0x70600003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_ACC_PWRCONF_ON[MCU_SYS_PWR_GYR_WRTBL_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_PWRCONF_ON[0],
        (U4)0x70640003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_ACC_PWRCONF_OFF[MCU_SYS_PWR_GYR_WRTBL_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_PWRCONF_OFF[0],
        (U4)0x70680003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_ACC_INTCONF_ON[MCU_SYS_PWR_GYR_WRTBL_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INTCONF_ON[0],
        (U4)0x706C0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_ACC_INTCONF_OFF[MCU_SYS_PWR_GYR_WRTBL_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INTCONF_OFF[0],
        (U4)0x70700003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_ACC_INTCONF_READ[MCU_SYS_PWR_GYR_RDTBL_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INTCONF_RD[0],
        (U4)0x70740002U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INTCONF_DT[0],
        (U4)0x70780002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_ACC_SOFTRESET[MCU_SYS_PWR_GYR_WRTBL_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_SOFTRESE[0],
        (U4)0x707C0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_INTSET_ANYMOT_TH[MCU_SYS_PWR_GYR_INTTBL_ANYMOT_NUM] = {
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

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_INTSET_ANYMOT_EN[MCU_SYS_PWR_GYR_INTTBL_ANYMOT_NUM] = {
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

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_INTSET_OTH[MCU_SYS_PWR_GYR_INTTBL_OTH_NUM] = {
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

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_ACC_SEN1_BW_INPRM[MCU_SYS_PWR_GYR_WRTBL_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_SEN1_BW_INPRM[0],
        (U4)0x70A40003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_ACC_CFG1[MCU_SYS_PWR_GYR_WRTBL_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_CFG1[0],
        (U4)0x70A80003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_ACC_CFG2[MCU_SYS_PWR_GYR_WRTBL_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_CFG2[0],
        (U4)0x70AC0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_ACC_DATA[MCU_SYS_PWR_GYR_WRTBL_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_DATA[0],
        (U4)0x70B00022U
    }
};

/*===================================================================================================================================*/
/* void            vd_g_GyroSysPwrInit(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_GyroSysPwrInit(void)
{
    U4  mcu_cnt;
    
    mcu_cnt = (U4)0U;

    /*  データリード用テーブル初期化 */
    u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_READ[0] = (U1)MCU_SYS_PWR_GYR_SADR_GRY_RD;    /* Slave Address */
    u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_READ[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_MODE_READ[0] = (U1)MCU_SYS_PWR_GYR_SADR_GRY_RD;    /* Slave Address */
    u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_MODE_READ[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル(BurstRead)初期化 */
    u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_READ_XYZ[0] = (U1)MCU_SYS_PWR_GYR_SADR_ACC_RD;    /* Slave Address */
    for(mcu_cnt = (U4)1U; mcu_cnt < (U4)7U; mcu_cnt++) {
        u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_READ_XYZ[mcu_cnt] = (U1)0U;    /* 読出しデータ初期値 */
    }

    /*  データリード用テーブル(BurstRead)初期化 */
    u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_READ_TEMP[0] = (U1)MCU_SYS_PWR_GYR_SADR_ACC_RD;    /* Slave Address */
    for(mcu_cnt = (U4)1U; mcu_cnt < (U4)3U; mcu_cnt++) {
        u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_READ_TEMP[mcu_cnt] = (U1)0U;    /* 読出しデータ初期値 */
    }

    /*  データリード用テーブル初期化 */
    u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INTCONF_DT[0] = (U1)MCU_SYS_PWR_GYR_SADR_ACC_RD;    /* Slave Address */
    u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_INTCONF_DT[1] = (U1)0U;    /* 読出しデータ初期値 */

    /* address offset設定テーブル② 書込み用テーブル(Data可変)初期化 */
    u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_CFG2[0] = (U1)MCU_SYS_PWR_GYR_SADR_ACC_WR;    /* Slave Address */
    u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_CFG2[1] = (U1)0x5CU;    /* Write Address */
    u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_CFG2[2] = (U1)0U;    /* Write Data初期値(定期処理内で更新) */

    /* コンフィグファイルの書き込みデータ 書込み用テーブル(Data可変)初期化 */
    u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_DATA[0] = (U1)MCU_SYS_PWR_GYR_SADR_ACC_WR;    /* Slave Address */
    u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_DATA[1] = (U1)0x5EU;    /* Write Address */
    for(mcu_cnt = (U4)2U; mcu_cnt < (U4)34U; mcu_cnt++) {
        u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_DATA[mcu_cnt] = (U1)0U;    /* Write Data初期値(定期処理内で更新) */
    }
}

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
