/* Mcu_Cfg_c */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | RH850/U2Ax/Mcu/Cfg/CODE                                     */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Mcu.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#pragma ghs section rosdata = ".C_MCU"

/* MCU Clock Common Configuration Table */
static const Mcu_ClockCommonConfigType MCU_CFG_CLOCKCOMMON_DATA =
{
    20U,
    STD_ON
};

/* MCU Clock Information Configuration Table */
static const Mcu_ClockInfoConfigType MCU_CFG_CLOCKINFO_DATA[] =
{
    {
        MCU_CLOCKTYPE_CLK_CPU,
        400U
    }
};

/* MCU Clock Setting Configuration Table */
static const Mcu_ClockSettingConfigType MCU_CFG_CLOCKSETTING_DATA =
{
    1U,
    &MCU_CFG_CLOCKINFO_DATA[0]
};

/* MCU Reset Setting Configuration Table */
static const Mcu_ResetSettingConfigType MCU_CFG_RESETSETTING_DATA =
{
    MCU_RESETTYPE_SW
};

/* MCU Configuration Table */
const Mcu_ConfigType MCU_CFG_DATA =
{
    &MCU_CFG_CLOCKCOMMON_DATA,
    &MCU_CFG_CLOCKSETTING_DATA,
    &MCU_CFG_RESETSETTING_DATA
};

/* [Device Individuality Config] MCU Device Clock Information Configuration Table */
static const Mcu_DevClockInfoConfigType MCU_DEVCFG_DEVCLOCKINFO_DATA[] =
{
    {
        MCU_DEVCLOCKTYPE_CLK_RLIN,
        MCU_SRCCLKTYPE_CLK_RLIN_CLK_HSB,
        MCU_CLKDIVTYPE_CLK_RLIN_DIV_1
    },
    {
        MCU_DEVCLOCKTYPE_CLK_ADC,
        MCU_SRCCLKTYPE_CLK_ADC_CLK_LSB2,
        MCU_CLKDIVTYPE_CLK_ADC_DIV_1
    },
    {
        MCU_DEVCLOCKTYPE_CLK_MSPI,
        MCU_SRCCLKTYPE_CLK_MSPI_CLK_HSB,
        MCU_CLKDIVTYPE_CLK_MSPI_DIV_1
    },
    {
        MCU_DEVCLOCKTYPE_CLK_WDT,
        MCU_SRCCLKTYPE_CLK_WDT_CLK_HSIOSC640,
        MCU_CLKDIVTYPE_CLK_WDT_DIV_1
    },
    {
        MCU_DEVCLOCKTYPE_CLKA_WDT,
        MCU_SRCCLKTYPE_CLKA_WDT_CLK_LSIOSC128,
        MCU_CLKDIVTYPE_CLKA_WDT_DIV_1
    },
    {
        MCU_DEVCLOCKTYPE_CLKA_TAUJ,
        MCU_SRCCLKTYPE_CLKA_TAUJ_CLK_HSIOSC20,
        MCU_CLKDIVTYPE_CLKA_TAUJ_DIV_1
    },
    {
        MCU_DEVCLOCKTYPE_CLKA_RTCA,
        MCU_SRCCLKTYPE_CLKA_RTCA_CLK_LSIOSC,
        MCU_CLKDIVTYPE_CLKA_RTCA_DIV_1
    },
    {
        MCU_DEVCLOCKTYPE_CLKA_ADC,
        MCU_SRCCLKTYPE_CLKA_ADC_CLK_HSIOSC20,
        MCU_CLKDIVTYPE_CLKA_ADC_DIV_1
    },
    {
        MCU_DEVCLOCKTYPE_EXTCLK0O,
        MCU_SRCCLKTYPE_EXTCLKO_CLK_HSIOSC20,
        MCU_CLKDIVTYPE_EXTCLKO_DISABLE
    },
    {
        MCU_DEVCLOCKTYPE_EXTCLK1O,
        MCU_SRCCLKTYPE_EXTCLKO_CLK_HSB,
        MCU_CLKDIVTYPE_EXTCLKO_DISABLE
    }
};

/* [Device Individuality Config] MCU Device Clock Setting Configuration Table */
static const Mcu_DevClockSettingConfigType MCU_DEVCFG_DEVCLOCKSETTING_DATA =
{
    10U,
    &MCU_DEVCFG_DEVCLOCKINFO_DATA[0]
};

/* [Device Individuality Config] MCU Device Individuality Configuration Table */
const Mcu_DevConfigType MCU_DEVCFG_DATA =
{
    &MCU_DEVCFG_DEVCLOCKSETTING_DATA
};

#pragma ghs section rosdata = default


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/04/30 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

