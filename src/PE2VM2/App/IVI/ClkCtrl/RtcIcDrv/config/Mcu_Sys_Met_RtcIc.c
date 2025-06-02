/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "rtime.h"
#include "RtcIc_drv_if.h"
#include "Mcu_Sys_Met_RtcIc.h"
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

const U1 u1_sp_MCU_SYS_MET_RTCIC_SETREG_VLF_RD_PDU1[MCU_SYS_MET_RTCIC_RWC_BYTE2] = {
    (U1)MCU_SYS_MET_RTCIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0EU     /* Write Address */
};

U1 u1_sp_MCU_SYS_MET_RTCIC_SETREG_VLF_RD_PDU2[MCU_SYS_MET_RTCIC_RWC_BYTE2];

const U1 u1_sp_MCU_SYS_MET_RTCIC_SETREG_CLK_RD_PDU1[MCU_SYS_MET_RTCIC_RWC_BYTE2] = {
    (U1)MCU_SYS_MET_RTCIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U    /* Write Address */
};

U1 u1_sp_MCU_SYS_MET_RTCIC_SETREG_CLK_RD_PDU2[MCU_SYS_MET_RTCIC_RWC_BYTE4];

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

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_MET_RTCIC_SETREG_VLF_RD[MCU_SYS_MET_RTCIC_SETREG_VLF_RD_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_MET_RTCIC_SETREG_VLF_RD_PDU1[0],
        (U4)0x50140002U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_MET_RTCIC_SETREG_VLF_RD_PDU2[0],
        (U4)0x50180002U
    }
};
const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_MET_RTCIC_SETREG_CLK_RD[MCU_SYS_MET_RTCIC_SETREG_CLK_RD_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_MET_RTCIC_SETREG_CLK_RD_PDU1[0],
        (U4)0x501C0002U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_MET_RTCIC_SETREG_CLK_RD_PDU2[0],
        (U4)0x50200004U
    }
};

/*===================================================================================================================================*/
/*  void    Mcu_Sys_Met_CrtIc_Clk_Init(const U4 u4_a_settime)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    Mcu_Sys_Met_RtcIc_Clk_Init(const U4 u4_a_settime)
{
    U4                 u4_t_se;
    U4                 u4_t_mi;
    U4                 u4_t_hr;

    u4_t_se =  u4_a_settime & (U4)RTCLK_HHMMSS_BIT_SE;
    u4_t_mi = (u4_a_settime & (U4)RTCLK_HHMMSS_BIT_MI) >> RTCLK_HHMMSS_LSB_MI;
    u4_t_hr = (u4_a_settime & (U4)RTCLK_HHMMSS_BIT_HR) >> RTCLK_HHMMSS_LSB_HR;

    /*  書込み用テーブル(Data可変)初期化 */
    u1_sp_MCU_SYS_MET_RTCIC_SETREG_CLK_PDU2[0] = (U1)MCU_SYS_MET_RTCIC_SLAVEADR_WR;    /* Slave Address */
    u1_sp_MCU_SYS_MET_RTCIC_SETREG_CLK_PDU2[1] = (U1)0x00U;     /* Write Address */
    u1_sp_MCU_SYS_MET_RTCIC_SETREG_CLK_PDU2[2] = (U1)u4_t_se;   /* Write Data初期値 */
    u1_sp_MCU_SYS_MET_RTCIC_SETREG_CLK_PDU2[3] = (U1)u4_t_mi;   /* Write Data初期値 */
    u1_sp_MCU_SYS_MET_RTCIC_SETREG_CLK_PDU2[4] = (U1)u4_t_hr;   /* Write Data初期値 */
    u1_sp_MCU_SYS_MET_RTCIC_SETREG_CLK_PDU2[5] = (U1)0x08U;     /* Write Data初期値 */
    u1_sp_MCU_SYS_MET_RTCIC_SETREG_CLK_PDU2[6] = (U1)0x01U;     /* Write Data初期値 */
    u1_sp_MCU_SYS_MET_RTCIC_SETREG_CLK_PDU2[7] = (U1)0x01U;     /* Write Data初期値 */
    u1_sp_MCU_SYS_MET_RTCIC_SETREG_CLK_PDU2[8] = (U1)0x25U;     /* Write Data初期値 */
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
    u1_sp_MCU_SYS_MET_RTCIC_SETREG_VLF_RD_PDU2[0] = (U1)MCU_SYS_MET_RTCIC_SLAVEADR_RD;    /* Slave Address */
    u1_sp_MCU_SYS_MET_RTCIC_SETREG_VLF_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */
}

/*===================================================================================================================================*/
/*  void    Mcu_Sys_Met_CrtIc_Vlf_Rd_Init(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      Mcu_Sys_Met_RtcIc_Vlf_Rd_Read(void)
{
    return(u1_sp_MCU_SYS_MET_RTCIC_SETREG_VLF_RD_PDU2[1]);
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
    u1_sp_MCU_SYS_MET_RTCIC_SETREG_CLK_RD_PDU2[0] = (U1)MCU_SYS_MET_RTCIC_SLAVEADR_RD;    /* Slave Address */
    u1_sp_MCU_SYS_MET_RTCIC_SETREG_CLK_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */
    u1_sp_MCU_SYS_MET_RTCIC_SETREG_CLK_RD_PDU2[2] = (U1)0U;    /* 読出しデータ初期値 */
    u1_sp_MCU_SYS_MET_RTCIC_SETREG_CLK_RD_PDU2[3] = (U1)0U;    /* 読出しデータ初期値 */
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
/*                                                                                                                                   */
/*  * SU   = Shin Uchida , DT                                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
