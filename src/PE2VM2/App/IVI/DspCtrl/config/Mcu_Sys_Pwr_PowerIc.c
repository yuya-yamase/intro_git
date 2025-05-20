/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "Mcu_Sys_Pwr_PowerIc.h"
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
const U1 u1_sp_MCU_SYS_PWR_POWERIC_SETREG_INIT_PDU1[MCU_SYS_PWR_POWERIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_POWERIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x80U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_POWERIC_SETREG_INIT_PDU2[MCU_SYS_PWR_POWERIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_POWERIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x81U,    /* Write Address */
    (U1)0xD0U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_POWERIC_SETREG_INIT_PDU3[MCU_SYS_PWR_POWERIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_POWERIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x82U,    /* Write Address */
    (U1)0xA0U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_POWERIC_SETREG_INIT_PDU4[MCU_SYS_PWR_POWERIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_POWERIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x83U,    /* Write Address */
    (U1)0x83U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_POWERIC_SETREG_INIT_PDU5[MCU_SYS_PWR_POWERIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_POWERIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x84U,    /* Write Address */
    (U1)0x40U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_POWERIC_SETREG_INIT_PDU6[MCU_SYS_PWR_POWERIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_POWERIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x85U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_POWERIC_SETREG_INIT_PDU7[MCU_SYS_PWR_POWERIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_POWERIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x86U,    /* Write Address */
    (U1)0x60U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_POWERIC_SETREG_INIT_PDU8[MCU_SYS_PWR_POWERIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_POWERIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x87U,    /* Write Address */
    (U1)0x1EU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_POWERIC_SETREG_AMP_ON_PDU1[MCU_SYS_PWR_POWERIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_POWERIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x87U,    /* Write Address */
    (U1)0x1FU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_POWERIC_SETREG_DIAG_ON_PDU1[MCU_SYS_PWR_POWERIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_POWERIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x84U,    /* Write Address */
    (U1)0x41U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_POWERIC_SETREG_MUTE_OFF_PDU1[MCU_SYS_PWR_POWERIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_POWERIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x82U,    /* Write Address */
    (U1)0xB8U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_POWERIC_SETREG_MUTE_RD_PDU1[MCU_SYS_PWR_POWERIC_RWC_BYTE2] = {
    (U1)MCU_SYS_PWR_POWERIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x82U     /* Write Address */
};

U1 u1_sp_MCU_SYS_PWR_POWERIC_SETREG_MUTE_RD_PDU2[MCU_SYS_PWR_POWERIC_RWC_BYTE2];

U1 u1_sp_MCU_SYS_PWR_POWERIC_SETREG_MUTE_ON_PDU1[MCU_SYS_PWR_POWERIC_RWC_BYTE3];

const U1 u1_sp_MCU_SYS_PWR_POWERIC_SETREG_AMP_RD_PDU1[MCU_SYS_PWR_POWERIC_RWC_BYTE2] = {
    (U1)MCU_SYS_PWR_POWERIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x87U     /* Write Address */
};

U1 u1_sp_MCU_SYS_PWR_POWERIC_SETREG_AMP_RD_PDU2[MCU_SYS_PWR_POWERIC_RWC_BYTE2];

U1 u1_sp_MCU_SYS_PWR_POWERIC_SETREG_AMP_OFF_PDU1[MCU_SYS_PWR_POWERIC_RWC_BYTE3];


const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_POWERIC_SETREG_INIT[MCU_SYS_PWR_POWERIC_SETREG_INIT_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_POWERIC_SETREG_INIT_PDU1[0],
        (U4)0x40040003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_POWERIC_SETREG_INIT_PDU2[0],
        (U4)0x40080003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_POWERIC_SETREG_INIT_PDU3[0],
        (U4)0x400C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_POWERIC_SETREG_INIT_PDU4[0],
        (U4)0x40100003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_POWERIC_SETREG_INIT_PDU5[0],
        (U4)0x40140003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_POWERIC_SETREG_INIT_PDU6[0],
        (U4)0x40180003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_POWERIC_SETREG_INIT_PDU7[0],
        (U4)0x401C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_POWERIC_SETREG_INIT_PDU8[0],
        (U4)0x40200003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_POWERIC_SETREG_AMP_ON[MCU_SYS_PWR_POWERIC_SETREG_AMP_ON_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_POWERIC_SETREG_AMP_ON_PDU1[0],
        (U4)0x40240003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_POWERIC_SETREG_DIAG_ON[MCU_SYS_PWR_POWERIC_SETREG_DIAG_ON_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_POWERIC_SETREG_DIAG_ON_PDU1[0],
        (U4)0x40280003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_POWERIC_SETREG_MUTE_OFF[MCU_SYS_PWR_POWERIC_SETREG_MUTE_OFF_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_POWERIC_SETREG_MUTE_OFF_PDU1[0],
        (U4)0x402C0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_POWERIC_SETREG_MUTE_RD[MCU_SYS_PWR_POWERIC_SETREG_MUTE_RD_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_POWERIC_SETREG_MUTE_RD_PDU1[0],
        (U4)0x40300002U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_POWERIC_SETREG_MUTE_RD_PDU2[0],
        (U4)0x40340002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_POWERIC_SETREG_MUTE_ON[MCU_SYS_PWR_POWERIC_SETREG_MUTE_ON_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_POWERIC_SETREG_MUTE_ON_PDU1[0],
        (U4)0x40380003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_POWERIC_SETREG_AMP_RD[MCU_SYS_PWR_POWERIC_SETREG_AMP_RD_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_POWERIC_SETREG_AMP_RD_PDU1[0],
        (U4)0x403C0002U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_POWERIC_SETREG_AMP_RD_PDU2[0],
        (U4)0x40400002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_POWERIC_SETREG_AMP_OFF[MCU_SYS_PWR_POWERIC_SETREG_AMP_OFF_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_POWERIC_SETREG_AMP_OFF_PDU1[0],
        (U4)0x40440003U
    }
};



/*****************************************************************************
  Function      : Mcu_Sys_Pwr_PowerIc_Init
  Description   : 初期化関数
  param[in/out] : none
  return        : none
  Note          : 読出し用バッファの初期化,固定値ではない書込み用バッファの初期化
*****************************************************************************/
void Mcu_Sys_Pwr_PowerIc_Init( void )
{
    /* MUTE設定Readテーブル データリード用テーブル初期化 */
    u1_sp_MCU_SYS_PWR_POWERIC_SETREG_MUTE_RD_PDU2[0] = (U1)MCU_SYS_PWR_POWERIC_SLAVEADR_RD;    /* Slave Address */
    u1_sp_MCU_SYS_PWR_POWERIC_SETREG_MUTE_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /* MUTE設定テーブル 書込み用テーブル(Data可変)初期化 */
    u1_sp_MCU_SYS_PWR_POWERIC_SETREG_MUTE_ON_PDU1[0] = (U1)MCU_SYS_PWR_POWERIC_SLAVEADR_WR;    /* Slave Address */
    u1_sp_MCU_SYS_PWR_POWERIC_SETREG_MUTE_ON_PDU1[1] = (U1)0x82U;    /* Write Address */
    u1_sp_MCU_SYS_PWR_POWERIC_SETREG_MUTE_ON_PDU1[2] = (U1)0U;    /* Write Data初期値 */

    /* Amp設定Readテーブル データリード用テーブル初期化 */
    u1_sp_MCU_SYS_PWR_POWERIC_SETREG_AMP_RD_PDU2[0] = (U1)MCU_SYS_PWR_POWERIC_SLAVEADR_RD;    /* Slave Address */
    u1_sp_MCU_SYS_PWR_POWERIC_SETREG_AMP_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /* Amp off設定テーブル 書込み用テーブル(Data可変)初期化 */
    u1_sp_MCU_SYS_PWR_POWERIC_SETREG_AMP_OFF_PDU1[0] = (U1)MCU_SYS_PWR_POWERIC_SLAVEADR_WR;    /* Slave Address */
    u1_sp_MCU_SYS_PWR_POWERIC_SETREG_AMP_OFF_PDU1[1] = (U1)0x87U;    /* Write Address */
    u1_sp_MCU_SYS_PWR_POWERIC_SETREG_AMP_OFF_PDU1[2] = (U1)0U;    /* Write Data初期値 */
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
