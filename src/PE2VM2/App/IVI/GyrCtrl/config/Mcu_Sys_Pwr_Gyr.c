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
    (U1)0x3CU    /* Read Address */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_GYR_READ[MCU_SYS_PWR_GYR_TX_RDSADR_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_GRY_RD    /* Slave Address */
};

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

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_XLSB[MCU_SYS_PWR_GYR_TX_RDREGADR_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_ACC_WR,    /* Slave Address */
    (U1)0x12U    /* Read Address */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_READ[MCU_SYS_PWR_GYR_TX_RDSADR_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_ACC_RD    /* Slave Address */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_XMSB[MCU_SYS_PWR_GYR_TX_RDREGADR_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_ACC_WR,    /* Slave Address */
    (U1)0x13U    /* Read Address */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_YLSB[MCU_SYS_PWR_GYR_TX_RDREGADR_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_ACC_WR,    /* Slave Address */
    (U1)0x14U    /* Read Address */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_YMSB[MCU_SYS_PWR_GYR_TX_RDREGADR_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_ACC_WR,    /* Slave Address */
    (U1)0x15U    /* Read Address */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_ZLSB[MCU_SYS_PWR_GYR_TX_RDREGADR_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_ACC_WR,    /* Slave Address */
    (U1)0x16U    /* Read Address */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_ZMSB[MCU_SYS_PWR_GYR_TX_RDREGADR_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_ACC_WR,    /* Slave Address */
    (U1)0x17U    /* Read Address */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_TEMPLSB[MCU_SYS_PWR_GYR_TX_RDREGADR_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_ACC_WR,    /* Slave Address */
    (U1)0x22U    /* Read Address */
};

const U1 u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_TEMPMSB[MCU_SYS_PWR_GYR_TX_RDREGADR_NUM] = {
    (U1)MCU_SYS_PWR_GYR_SADR_ACC_WR,    /* Slave Address */
    (U1)0x23U    /* Read Address */
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

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_ACC_SEN1_SETUP[MCU_SYS_PWR_GYR_SETUPTBL_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_SEN1_BW[0],
        (U4)0x70240003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_SEN1_RANGE[0],
        (U4)0x70280003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_ACC_SEN2_SETUP[MCU_SYS_PWR_GYR_SETUPTBL_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_SEN2_BW[0],
        (U4)0x702C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_SEN2_RANGE[0],
        (U4)0x70300003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_ACC_WDG[MCU_SYS_PWR_GYR_WRTBL_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_WDG[0],
        (U4)0x70340003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_ACC_MODE_ON[MCU_SYS_PWR_GYR_WRTBL_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_MODE_NML[0],
        (U4)0x70380003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_ACC_MODE_OFF[MCU_SYS_PWR_GYR_WRTBL_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_MODE_SPD[0],
        (U4)0x703C0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_ACC_PLSTEST[MCU_SYS_PWR_GYR_WRTBL_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_PLSTEST[0],
        (U4)0x70400003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_ACC_MNSTEST[MCU_SYS_PWR_GYR_WRTBL_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_MNSTEST[0],
        (U4)0x70440003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_ACC_DISTEST[MCU_SYS_PWR_GYR_WRTBL_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_DISTEST[0],
        (U4)0x70480003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_GYR_XLSB[MCU_SYS_PWR_GYR_RDTBL_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_XLSB[0],
        (U4)0x704C0002U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_READ[0],
        (U4)0x70500002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_GYR_XMSB[MCU_SYS_PWR_GYR_RDTBL_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_XMSB[0],
        (U4)0x70540002U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_READ[0],
        (U4)0x70580002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_GYR_YLSB[MCU_SYS_PWR_GYR_RDTBL_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_YLSB[0],
        (U4)0x705C0002U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_READ[0],
        (U4)0x70600002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_GYR_YMSB[MCU_SYS_PWR_GYR_RDTBL_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_YMSB[0],
        (U4)0x70640002U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_READ[0],
        (U4)0x70680002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_GYR_ZLSB[MCU_SYS_PWR_GYR_RDTBL_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_ZLSB[0],
        (U4)0x706C0002U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_READ[0],
        (U4)0x70700002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_GYR_ZMSB[MCU_SYS_PWR_GYR_RDTBL_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_ZMSB[0],
        (U4)0x70740002U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_READ[0],
        (U4)0x70780002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_GYR_TEMPLSB[MCU_SYS_PWR_GYR_RDTBL_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_TEMPLSB[0],
        (U4)0x707C0002U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_READ[0],
        (U4)0x70800002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GYR_REG_GYR_TEMPMSB[MCU_SYS_PWR_GYR_RDTBL_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_TEMPMSB[0],
        (U4)0x70840002U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GYR_DAT_ACC_READ[0],
        (U4)0x70880002U
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
