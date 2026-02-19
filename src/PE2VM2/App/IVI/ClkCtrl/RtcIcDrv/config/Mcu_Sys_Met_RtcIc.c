/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "rtime.h"
#include "date.h"
#include "RtcIc_drv_if.h"
#include "Mcu_Sys_Met_RtcIc.h"
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RTCIC_I2C_SLAVEADR                       (0U)
#define RTCIC_I2C_REGADR                         (1U)

#define RTCIC_I2C_WRITE_DATA0                    (2U)
#define RTCIC_I2C_WRITE_DATA1                    (3U)
#define RTCIC_I2C_WRITE_DATA2                    (4U)
#define RTCIC_I2C_WRITE_DATA3                    (5U)
#define RTCIC_I2C_WRITE_DATA4                    (6U)
#define RTCIC_I2C_WRITE_DATA5                    (7U)
#define RTCIC_I2C_WRITE_DATA6                    (8U)
#define RTCIC_I2C_WRITE_DATA7                    (9U)

#define RTCIC_I2C_READ_DATA0                     (1U)
#define RTCIC_I2C_READ_DATA1                     (2U)
#define RTCIC_I2C_READ_DATA2                     (3U)
#define RTCIC_I2C_READ_DATA3                     (4U)
#define RTCIC_I2C_READ_DATA4                     (5U)
#define RTCIC_I2C_READ_DATA5                     (6U)
#define RTCIC_I2C_READ_DATA6                     (7U)
#define RTCIC_I2C_READ_DATA7                     (8U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RTCIC_HHMMSS_BIT_SE                      (0x0000007fU)
#define RTCIC_HHMMSS_BIT_MI                      (0x0000007fU)
#define RTCIC_HHMMSS_BIT_HR                      (0x0000003fU)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RTCIC_YEAR_BASE                          (2000U)
#define RTCIC_YEAR_CENTURY                       (100U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RTCIC_EXTENSION_REG_MASK                 (0xFFU)
#define RTCIC_FLAG_REG_MASK                      (0x03U)
#define RTCIC_CONTROL_REG_MASK                   (0xF9U)
#define RTCIC_BACKUP_FUNC_MASK                   (0x0FU)
#define RTCIC_RAM_DATANUM                        (6U)

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
static U1       u1_s_Mcu_Sys_Met_RtcIc_Memcmp(const U1 *u1_ap_data1, const U1 *u1_ap_data2, const U1 u1_a_size);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U1 u1_sp_MCU_SYS_MET_RTCIC_SETREG_CLK_PDU1[MCU_SYS_MET_RTCIC_RWC_BYTE5] = {
    (U1)MCU_SYS_MET_RTCIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0DU,    /* Write Address */
    (U1)0x08U,    /* Write Data */
    (U1)0x00U,    /* Write Data */
    (U1)0x40U     /* Write Data */
};

U1 u1_sp_MCU_SYS_MET_RTCIC_SETREG_CLK_PDU2[MCU_SYS_MET_RTCIC_RWC_BYTE9];

const U1 u1_sp_MCU_SYS_MET_RTCIC_SETREG_CLK_PDU3[MCU_SYS_MET_RTCIC_RWC_BYTE8] = {
    (U1)MCU_SYS_MET_RTCIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x07U,    /* Write Address */
    (U1)0x00U,    /* Write Data */
    (U1)0x00U,    /* Write Data */
    (U1)0x00U,    /* Write Data */
    (U1)0x00U,    /* Write Data */
    (U1)0x00U,    /* Write Data */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_MET_RTCIC_SETREG_CLK_PDU4[MCU_SYS_MET_RTCIC_RWC_BYTE3] = {
    (U1)MCU_SYS_MET_RTCIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x18U,    /* Write Address */
    (U1)0x08U     /* Write Data */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1 u1_sp_MCU_SYS_MET_RTCIC_SETREG_DAYSET_PDU1[MCU_SYS_MET_RTCIC_RWC_BYTE6];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U1 u1_sp_MCU_SYS_MET_RTCIC_READREG_VLF_PDU1[MCU_SYS_MET_RTCIC_RWC_BYTE2] = {
    (U1)MCU_SYS_MET_RTCIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0EU                             /* Write Address */
};

U1 u1_sp_MCU_SYS_MET_RTCIC_READREG_VLF_PDU2[MCU_SYS_MET_RTCIC_RWC_BYTE2];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U1 u1_sp_MCU_SYS_MET_RTCIC_READREG_CLK_PDU1[MCU_SYS_MET_RTCIC_RWC_BYTE2] = {
    (U1)MCU_SYS_MET_RTCIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U                             /* Write Address */
};

U1 u1_sp_MCU_SYS_MET_RTCIC_READREG_CLK_PDU2[MCU_SYS_MET_RTCIC_RWC_BYTE8];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U1 u1_sp_MCU_SYS_MET_RTCIC_READREG_CONT_PDU1[MCU_SYS_MET_RTCIC_RWC_BYTE2] = {
    (U1)MCU_SYS_MET_RTCIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0DU                             /* Write Address */
};

U1 u1_sp_MCU_SYS_MET_RTCIC_READREG_CONT_PDU2[MCU_SYS_MET_RTCIC_RWC_BYTE4];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U1 u1_sp_MCU_SYS_MET_RTCIC_READREG_BACKUP_PDU1[MCU_SYS_MET_RTCIC_RWC_BYTE2] = {
    (U1)MCU_SYS_MET_RTCIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x18U                             /* Write Address */
};

U1 u1_sp_MCU_SYS_MET_RTCIC_READREG_BACKUP_PDU2[MCU_SYS_MET_RTCIC_RWC_BYTE2];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U1 u1_sp_MCU_SYS_MET_RTCIC_READREG_RAM_PDU1[MCU_SYS_MET_RTCIC_RWC_BYTE2] = {
    (U1)MCU_SYS_MET_RTCIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x07U                             /* Write Address */
};

U1 u1_sp_MCU_SYS_MET_RTCIC_READREG_RAM_PDU2[MCU_SYS_MET_RTCIC_RWC_BYTE7];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_MET_RTCIC_SETREG_CLK[MCU_SYS_MET_RTCIC_SETREG_CLK_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_MET_RTCIC_SETREG_CLK_PDU1[0],
        (U4)0x50040005U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_MET_RTCIC_SETREG_CLK_PDU2[0],
        (U4)0x50080009U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_MET_RTCIC_SETREG_CLK_PDU3[0],
        (U4)0x500C0008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_MET_RTCIC_SETREG_CLK_PDU4[0],
        (U4)0x50100003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_MET_RTCIC_SETREG_DAYSET[MCU_SYS_MET_RTCIC_SETREG_DAYSET_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_MET_RTCIC_SETREG_DAYSET_PDU1[0],
        (U4)0x50140006U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_MET_RTCIC_READREG_VLF[MCU_SYS_MET_RTCIC_READREG_VLF_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_MET_RTCIC_READREG_VLF_PDU1[0],
        (U4)0x50180002U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_MET_RTCIC_READREG_VLF_PDU2[0],
        (U4)0x501C0002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_MET_RTCIC_READREG_CLK[MCU_SYS_MET_RTCIC_READREG_CLK_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_MET_RTCIC_READREG_CLK_PDU1[0],
        (U4)0x50200002U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_MET_RTCIC_READREG_CLK_PDU2[0],
        (U4)0x50240008U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_MET_RTCIC_READREG_CONT[MCU_SYS_MET_RTCIC_READREG_CONT_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_MET_RTCIC_READREG_CONT_PDU1[0],
        (U4)0x50280002U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_MET_RTCIC_READREG_CONT_PDU2[0],
        (U4)0x502C0004U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_MET_RTCIC_READREG_BACKUP[MCU_SYS_MET_RTCIC_READREG_BACKUP_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_MET_RTCIC_READREG_BACKUP_PDU1[0],
        (U4)0x50300002U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_MET_RTCIC_READREG_BACKUP_PDU2[0],
        (U4)0x50340002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_MET_RTCIC_READREG_RAM[MCU_SYS_MET_RTCIC_READREG_RAM_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_MET_RTCIC_READREG_RAM_PDU1[0],
        (U4)0x50380002U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_MET_RTCIC_READREG_RAM_PDU2[0],
        (U4)0x503C0007U
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1             u1_sp_RTCIC_WEEK_TBL[7] = {
    (U1)0x01U, (U1)0x02U, (U1)0x04U, (U1)0x08U, (U1)0x10U, (U1)0x20U, (U1)0x40U
};

/*===================================================================================================================================*/
/*  void    Mcu_Sys_Met_CrtIc_Clk_Init(const U4 u4_a_HHMMSS_24H, const U4 u4_a_daycnt)                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    Mcu_Sys_Met_RtcIc_Clk_Init(const U4 u4_a_HHMMSS_24H, const U4 u4_a_daycnt)
{
    U4                 u4_t_se;
    U4                 u4_t_mi;
    U4                 u4_t_hr;

    U4                 u4_t_yymmddwk;
    U4                 u4_t_wk;
    U4                 u4_t_da;
    U4                 u4_t_mo;
    U4                 u4_t_yr;

    u4_t_se =  u4_a_HHMMSS_24H & (U4)RTCLK_HHMMSS_BIT_SE;
    u4_t_mi = (u4_a_HHMMSS_24H & (U4)RTCLK_HHMMSS_BIT_MI) >> RTCLK_HHMMSS_LSB_MI;
    u4_t_hr = (u4_a_HHMMSS_24H & (U4)RTCLK_HHMMSS_BIT_HR) >> RTCLK_HHMMSS_LSB_HR;

    u4_t_yymmddwk    = u4_g_DaycntToYymmddwk(u4_a_daycnt);
    u4_t_wk =  u4_t_yymmddwk & YYMMDDWK_BIT_WK;
    u4_t_da = (u4_t_yymmddwk & (U4)YYMMDDWK_BIT_DA) >> YYMMDDWK_LSB_DA;
    u4_t_mo = (u4_t_yymmddwk & (U4)YYMMDDWK_BIT_MO) >> YYMMDDWK_LSB_MO;
    u4_t_yr = (u4_t_yymmddwk & (U4)YYMMDDWK_BIT_YR) >> YYMMDDWK_LSB_YR;

    /*  書込み用テーブル(Data可変)初期化 */
    u1_sp_MCU_SYS_MET_RTCIC_SETREG_CLK_PDU2[RTCIC_I2C_SLAVEADR]    = (U1)MCU_SYS_MET_RTCIC_SLAVEADR_WR;     /* Slave Address */
    u1_sp_MCU_SYS_MET_RTCIC_SETREG_CLK_PDU2[RTCIC_I2C_REGADR]      = (U1)0x00U;                             /* Write Address */
    u1_sp_MCU_SYS_MET_RTCIC_SETREG_CLK_PDU2[RTCIC_I2C_WRITE_DATA0] = (U1)u4_t_se;                           /* Write Data    */
    u1_sp_MCU_SYS_MET_RTCIC_SETREG_CLK_PDU2[RTCIC_I2C_WRITE_DATA1] = (U1)u4_t_mi;                           /* Write Data    */
    u1_sp_MCU_SYS_MET_RTCIC_SETREG_CLK_PDU2[RTCIC_I2C_WRITE_DATA2] = (U1)u4_t_hr;                           /* Write Data    */
    u1_sp_MCU_SYS_MET_RTCIC_SETREG_CLK_PDU2[RTCIC_I2C_WRITE_DATA3] = u1_sp_RTCIC_WEEK_TBL[u4_t_wk];         /* Write Data    */
    u1_sp_MCU_SYS_MET_RTCIC_SETREG_CLK_PDU2[RTCIC_I2C_WRITE_DATA4] = (U1)u4_t_da;                           /* Write Data    */
    u1_sp_MCU_SYS_MET_RTCIC_SETREG_CLK_PDU2[RTCIC_I2C_WRITE_DATA5] = (U1)u4_t_mo;                           /* Write Data    */
    u1_sp_MCU_SYS_MET_RTCIC_SETREG_CLK_PDU2[RTCIC_I2C_WRITE_DATA6] = (U1)(u4_t_yr % (U4)RTCIC_YEAR_CENTURY);/* Write Data    */
}

/*===================================================================================================================================*/
/*  void    Mcu_Sys_Met_CrtIc_Vlf_Rd_Init(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    Mcu_Sys_Met_RtcIc_Vlf_Rd_Init(void)
{
    /*  データリード用テーブル初期化 */
    u1_sp_MCU_SYS_MET_RTCIC_READREG_VLF_PDU2[RTCIC_I2C_SLAVEADR]   = (U1)MCU_SYS_MET_RTCIC_SLAVEADR_RD;    /* Slave Address */
    u1_sp_MCU_SYS_MET_RTCIC_READREG_VLF_PDU2[RTCIC_I2C_READ_DATA0] = (U1)0U;    /* 読出しデータ初期値 */
}

/*===================================================================================================================================*/
/*  void    Mcu_Sys_Met_CrtIc_Vlf_Rd_Init(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      Mcu_Sys_Met_RtcIc_Vlf_Rd_Read(void)
{
    return(u1_sp_MCU_SYS_MET_RTCIC_READREG_VLF_PDU2[RTCIC_I2C_READ_DATA0]);
}

/*===================================================================================================================================*/
/*  void    Mcu_Sys_Met_CrtIc_Clk_Rd_Init(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    Mcu_Sys_Met_RtcIc_Clk_Rd_Init(void)
{
    /*  データリード用テーブル初期化 */
    u1_sp_MCU_SYS_MET_RTCIC_READREG_CLK_PDU2[RTCIC_I2C_SLAVEADR]   = (U1)MCU_SYS_MET_RTCIC_SLAVEADR_RD;    /* Slave Address */
    u1_sp_MCU_SYS_MET_RTCIC_READREG_CLK_PDU2[RTCIC_I2C_READ_DATA0] = (U1)0U;    /* 読出しデータ初期値 */
    u1_sp_MCU_SYS_MET_RTCIC_READREG_CLK_PDU2[RTCIC_I2C_READ_DATA1] = (U1)0U;    /* 読出しデータ初期値 */
    u1_sp_MCU_SYS_MET_RTCIC_READREG_CLK_PDU2[RTCIC_I2C_READ_DATA2] = (U1)0U;    /* 読出しデータ初期値 */

    u1_sp_MCU_SYS_MET_RTCIC_READREG_CLK_PDU2[RTCIC_I2C_READ_DATA3] = (U1)0U;    /* 読出しデータ初期値 */
    u1_sp_MCU_SYS_MET_RTCIC_READREG_CLK_PDU2[RTCIC_I2C_READ_DATA4] = (U1)0U;    /* 読出しデータ初期値 */
    u1_sp_MCU_SYS_MET_RTCIC_READREG_CLK_PDU2[RTCIC_I2C_READ_DATA5] = (U1)0U;    /* 読出しデータ初期値 */
    u1_sp_MCU_SYS_MET_RTCIC_READREG_CLK_PDU2[RTCIC_I2C_READ_DATA6] = (U1)0U;    /* 読出しデータ初期値 */
}

/*===================================================================================================================================*/
/*  void    Mcu_Sys_Met_RtcIc_Clk_Rd_Read(U4* u4_ap_HHMMSS_24H, U4* u4_ap_daycnt)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    Mcu_Sys_Met_RtcIc_Clk_Rd_Read(U4* u4_ap_HHMMSS_24H, U4* u4_ap_daycnt)
{
    U4                 u4_t_se;
    U4                 u4_t_mi;
    U4                 u4_t_hr;
    U4                 u4_t_da;
    U4                 u4_t_mo;
    U4                 u4_t_yr;
    U4                 u4_t_YYMMDD;

    u4_t_se = (U4)(u1_sp_MCU_SYS_MET_RTCIC_READREG_CLK_PDU2[RTCIC_I2C_READ_DATA0] & (U1)RTCIC_HHMMSS_BIT_SE);
    u4_t_mi = (U4)(u1_sp_MCU_SYS_MET_RTCIC_READREG_CLK_PDU2[RTCIC_I2C_READ_DATA1] & (U1)RTCIC_HHMMSS_BIT_MI);
    u4_t_hr = (U4)(u1_sp_MCU_SYS_MET_RTCIC_READREG_CLK_PDU2[RTCIC_I2C_READ_DATA2] & (U1)RTCIC_HHMMSS_BIT_HR);

    *u4_ap_HHMMSS_24H = (u4_t_hr << RTCLK_HHMMSS_LSB_HR) |
                        (u4_t_mi << RTCLK_HHMMSS_LSB_MI) |
                         u4_t_se;

    u4_t_da = (U4)u1_sp_MCU_SYS_MET_RTCIC_READREG_CLK_PDU2[RTCIC_I2C_READ_DATA4];
    u4_t_mo = (U4)u1_sp_MCU_SYS_MET_RTCIC_READREG_CLK_PDU2[RTCIC_I2C_READ_DATA5];
    u4_t_yr = (U4)u1_sp_MCU_SYS_MET_RTCIC_READREG_CLK_PDU2[RTCIC_I2C_READ_DATA6];
    u4_t_yr += (U4)RTCIC_YEAR_BASE;

    u4_t_YYMMDD  = u4_t_da << YYMMDDWK_LSB_DA;
    u4_t_YYMMDD += u4_t_mo << YYMMDDWK_LSB_MO;
    u4_t_YYMMDD += u4_t_yr << YYMMDDWK_LSB_YR;

    *u4_ap_daycnt = u4_g_YymmddToDaycnt(u4_t_YYMMDD);
}

/*===================================================================================================================================*/
/*  void    Mcu_Sys_Met_RtcIc_Day_Set(const U4 u4_a_daycnt)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    Mcu_Sys_Met_RtcIc_Day_Set(const U4 u4_a_daycnt)
{
    U4                 u4_t_yymmddwk;
    U4                 u4_t_wk;
    U4                 u4_t_da;
    U4                 u4_t_mo;
    U4                 u4_t_yr;

    u4_t_yymmddwk    = u4_g_DaycntToYymmddwk(u4_a_daycnt);
    u4_t_wk =  u4_t_yymmddwk & YYMMDDWK_BIT_WK;
    u4_t_da = (u4_t_yymmddwk & (U4)YYMMDDWK_BIT_DA) >> YYMMDDWK_LSB_DA;
    u4_t_mo = (u4_t_yymmddwk & (U4)YYMMDDWK_BIT_MO) >> YYMMDDWK_LSB_MO;
    u4_t_yr = (u4_t_yymmddwk & (U4)YYMMDDWK_BIT_YR) >> YYMMDDWK_LSB_YR;

    /*  書込み用テーブル(Data可変)初期化 */
    u1_sp_MCU_SYS_MET_RTCIC_SETREG_DAYSET_PDU1[RTCIC_I2C_SLAVEADR]    = (U1)MCU_SYS_MET_RTCIC_SLAVEADR_WR;     /* Slave Address */
    u1_sp_MCU_SYS_MET_RTCIC_SETREG_DAYSET_PDU1[RTCIC_I2C_REGADR]      = (U1)0x03U;                             /* Write Address */
    u1_sp_MCU_SYS_MET_RTCIC_SETREG_DAYSET_PDU1[RTCIC_I2C_WRITE_DATA0] = u1_sp_RTCIC_WEEK_TBL[u4_t_wk];         /* Write Data    */
    u1_sp_MCU_SYS_MET_RTCIC_SETREG_DAYSET_PDU1[RTCIC_I2C_WRITE_DATA1] = (U1)u4_t_da;                           /* Write Data    */
    u1_sp_MCU_SYS_MET_RTCIC_SETREG_DAYSET_PDU1[RTCIC_I2C_WRITE_DATA2] = (U1)u4_t_mo;                           /* Write Data    */
    u1_sp_MCU_SYS_MET_RTCIC_SETREG_DAYSET_PDU1[RTCIC_I2C_WRITE_DATA3] = (U1)(u4_t_yr % (U4)RTCIC_YEAR_CENTURY);/* Write Data    */
}

/*===================================================================================================================================*/
/*  void    Mcu_Sys_Met_CrtIc_ContReg_Rd_Init(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    Mcu_Sys_Met_RtcIc_ContReg_Rd_Init(void)
{
    /*  データリード用テーブル初期化 */
    u1_sp_MCU_SYS_MET_RTCIC_READREG_CONT_PDU2[RTCIC_I2C_SLAVEADR]   = (U1)MCU_SYS_MET_RTCIC_SLAVEADR_RD;    /* Slave Address */
    u1_sp_MCU_SYS_MET_RTCIC_READREG_CONT_PDU2[RTCIC_I2C_READ_DATA0] = (U1)0U;    /* 読出しデータ初期値 */
    u1_sp_MCU_SYS_MET_RTCIC_READREG_CONT_PDU2[RTCIC_I2C_READ_DATA1] = (U1)0U;    /* 読出しデータ初期値 */
    u1_sp_MCU_SYS_MET_RTCIC_READREG_CONT_PDU2[RTCIC_I2C_READ_DATA2] = (U1)0U;    /* 読出しデータ初期値 */
}

/*===================================================================================================================================*/
/*  void    Mcu_Sys_Met_CrtIc_Backup_Rd_Init(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    Mcu_Sys_Met_RtcIc_Backup_Rd_Init(void)
{
    /*  データリード用テーブル初期化 */
    u1_sp_MCU_SYS_MET_RTCIC_READREG_BACKUP_PDU2[RTCIC_I2C_SLAVEADR]   = (U1)MCU_SYS_MET_RTCIC_SLAVEADR_RD;    /* Slave Address */
    u1_sp_MCU_SYS_MET_RTCIC_READREG_BACKUP_PDU2[RTCIC_I2C_READ_DATA0] = (U1)0U;    /* 読出しデータ初期値 */
}

/*===================================================================================================================================*/
/*  void    Mcu_Sys_Met_CrtIc_Ran_Rd_Init(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    Mcu_Sys_Met_RtcIc_Ram_Rd_Init(void)
{
    /*  データリード用テーブル初期化 */
    u1_sp_MCU_SYS_MET_RTCIC_READREG_RAM_PDU2[RTCIC_I2C_SLAVEADR]   = (U1)MCU_SYS_MET_RTCIC_SLAVEADR_RD;    /* Slave Address */
    u1_sp_MCU_SYS_MET_RTCIC_READREG_RAM_PDU2[RTCIC_I2C_READ_DATA0] = (U1)0U;    /* 読出しデータ初期値 */
    u1_sp_MCU_SYS_MET_RTCIC_READREG_RAM_PDU2[RTCIC_I2C_READ_DATA1] = (U1)0U;    /* 読出しデータ初期値 */
    u1_sp_MCU_SYS_MET_RTCIC_READREG_RAM_PDU2[RTCIC_I2C_READ_DATA2] = (U1)0U;    /* 読出しデータ初期値 */
    u1_sp_MCU_SYS_MET_RTCIC_READREG_RAM_PDU2[RTCIC_I2C_READ_DATA3] = (U1)0U;    /* 読出しデータ初期値 */
    u1_sp_MCU_SYS_MET_RTCIC_READREG_RAM_PDU2[RTCIC_I2C_READ_DATA4] = (U1)0U;    /* 読出しデータ初期値 */
    u1_sp_MCU_SYS_MET_RTCIC_READREG_RAM_PDU2[RTCIC_I2C_READ_DATA5] = (U1)0U;    /* 読出しデータ初期値 */
}

/*===================================================================================================================================*/
/*  U1      Mcu_Sys_Met_CrtIc_ContReg_Rd_Cmp(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      Mcu_Sys_Met_RtcIc_ContReg_Rd_Cmp(void)
{
    U1      u1_t_ret;
    U1      u1_t_reg;

    u1_t_ret = (U1)TRUE;

    u1_t_reg  = u1_sp_MCU_SYS_MET_RTCIC_READREG_CONT_PDU2[RTCIC_I2C_READ_DATA0];
    u1_t_reg &= (U1)RTCIC_EXTENSION_REG_MASK;
    if (u1_sp_MCU_SYS_MET_RTCIC_SETREG_CLK_PDU1[RTCIC_I2C_WRITE_DATA0] != u1_t_reg) {
        u1_t_ret = (U1)FALSE;
    }

    u1_t_reg  = u1_sp_MCU_SYS_MET_RTCIC_READREG_CONT_PDU2[RTCIC_I2C_READ_DATA1];
    u1_t_reg &= (U1)RTCIC_FLAG_REG_MASK;
    if (u1_sp_MCU_SYS_MET_RTCIC_SETREG_CLK_PDU1[RTCIC_I2C_WRITE_DATA1] != u1_t_reg) {
        u1_t_ret = (U1)FALSE;
    }

    u1_t_reg  = u1_sp_MCU_SYS_MET_RTCIC_READREG_CONT_PDU2[RTCIC_I2C_READ_DATA2];
    u1_t_reg &= (U1)RTCIC_CONTROL_REG_MASK;
    if (u1_sp_MCU_SYS_MET_RTCIC_SETREG_CLK_PDU1[RTCIC_I2C_WRITE_DATA2] != u1_t_reg) {
        u1_t_ret = (U1)FALSE;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1      Mcu_Sys_Met_CrtIc_Backup_Rd_Cmp(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      Mcu_Sys_Met_RtcIc_Backup_Rd_Cmp(void)
{
    U1      u1_t_ret;
    U1      u1_t_backup;

    u1_t_ret = (U1)TRUE;

    u1_t_backup = u1_sp_MCU_SYS_MET_RTCIC_READREG_BACKUP_PDU2[RTCIC_I2C_READ_DATA0];
    u1_t_backup &= (U1)RTCIC_BACKUP_FUNC_MASK;
    if (u1_sp_MCU_SYS_MET_RTCIC_SETREG_CLK_PDU4[RTCIC_I2C_WRITE_DATA0] != u1_t_backup) {
        u1_t_ret = (U1)FALSE;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1      Mcu_Sys_Met_CrtIc_Ram_Rd_Cmp(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      Mcu_Sys_Met_RtcIc_Ram_Rd_Cmp(void)
{
    U1      u1_t_ret;

    u1_t_ret = u1_s_Mcu_Sys_Met_RtcIc_Memcmp(&u1_sp_MCU_SYS_MET_RTCIC_SETREG_CLK_PDU3[RTCIC_I2C_WRITE_DATA0],
                                             &u1_sp_MCU_SYS_MET_RTCIC_READREG_RAM_PDU2[RTCIC_I2C_READ_DATA0],
                                             (U1)RTCIC_RAM_DATANUM);

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1      u1_s_Mcu_Sys_Met_RtcIc_Memcmp(const U1 *u1_ap_data1, const U1 *u1_ap_data2, const U1 u1_a_size)                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_Mcu_Sys_Met_RtcIc_Memcmp(const U1 *u1_ap_data1, const U1 *u1_ap_data2, const U1 u1_a_size)
{
    U1                          u1_t_data_size;
    U1                          u1_t_ret;

    u1_t_ret = (U1)TRUE;

    for(u1_t_data_size = (U1)0U; u1_t_data_size < u1_a_size; u1_t_data_size++){
        if(u1_ap_data1[u1_t_data_size] != u1_ap_data2[u1_t_data_size]){
            u1_t_ret = (U1)FALSE;
            break;
        }
    }
    return(u1_t_ret);
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
/*  0.0.0    02/24/2025  SU       New.                                                                                               */
/*  0.9.0    07/22/2025  SU                                                                                                          */
/*                                                                                                                                   */
/*  * SU   = Shin Uchida , DT                                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
