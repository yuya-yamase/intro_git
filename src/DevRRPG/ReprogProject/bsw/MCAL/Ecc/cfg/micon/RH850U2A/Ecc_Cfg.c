/* Ecc_Cfg_c */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | RH850/U2Ax/Ecc/Cfg/CODE                                     */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Ecc.h>


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
#pragma ghs section rosdata = ".C_ECC"

/* ECC Setting Configuration Table [RPG Software Area] */
static const Ecc_SettingConfigType ECC_CFG_RPG_SETTING_DATA[] =
{
    {
        0x00000000UL,
        0x00004000UL,
        STD_ON,
        STD_OFF,
        STD_ON,
        STD_ON
    },
    {
        0x0000C000UL,
        0x00014000UL,
        STD_ON,
        STD_OFF,
        STD_ON,
        STD_ON
    },
    {
        0x08000000UL,
        0x00010000UL,
        STD_ON,
        STD_OFF,
        STD_ON,
        STD_ON
    }
};

/* ECC Setting Configuration Table [USR Software Area] */
static const Ecc_SettingConfigType ECC_CFG_USR_SETTING_DATA[] =
{
    {
        0x00004000UL,
        0x00000400UL,
        STD_ON,
        STD_OFF,
        STD_ON,
        STD_ON
    },
    {
        0x00008000UL,
        0x00000200UL,
        STD_ON,
        STD_OFF,
        STD_ON,
        STD_ON
    },
    {
        0x00020000UL,
        0x007E0000UL,
        STD_ON,
        STD_OFF,
        STD_ON,
        STD_ON
    }
};

/* ECC Target Area Configuration Table [RPG Software Area] */
static const Ecc_TargetAreaConfigType ECC_CFG_RPG_AREA_DATA =
{
    3U,
    &ECC_CFG_RPG_SETTING_DATA[0]
};

/* ECC Target Area Configuration Table [USR Software Area] */
static const Ecc_TargetAreaConfigType ECC_CFG_USR_AREA_DATA =
{
    3U,
    &ECC_CFG_USR_SETTING_DATA[0]
};

/* ECC Target Memory Configuration Table [ROM] */
static const Ecc_TargetMemoryConfigType ECC_CFG_ROM_DATA =
{
    &ECC_CFG_RPG_AREA_DATA,
    &ECC_CFG_USR_AREA_DATA
};

/* ECC Setting Configuration Table [RAM] */
static const Ecc_SettingConfigType ECC_CFG_RAM_SETTING_DATA[] =
{
    /* Local RAM */
    {
        0x00000000UL,
        0x00000000UL,
        STD_ON,
        STD_OFF,
        STD_ON,
        STD_ON
    },
    /* Cluster RAM */
    {
        0x00000000UL,
        0x00000000UL,
        STD_ON,
        STD_OFF,
        STD_ON,
        STD_ON
    }
};

/* ECC Target Area Configuration Table [RAM] */
static const Ecc_TargetAreaConfigType ECC_CFG_RAM_DATA =
{
    2U,
    &ECC_CFG_RAM_SETTING_DATA[0]
};

/* ECC Configuration Table */
const Ecc_ConfigType ECC_CFG_DATA =
{
    &ECC_CFG_ROM_DATA,
    &ECC_CFG_RAM_DATA
};

/* [Device Individuality Config] ECC Product Setting Configuration Table */
static const Ecc_DevProductSettingConfigType ECC_DEVCFG_PRODUCT_DATA =
{
    ECC_PRODUCT_U2A16
};

/* [Device Individuality Config] ECC Device Individuality Configuration Table */
const Ecc_DevConfigType ECC_DEVCFG_DATA =
{
    &ECC_DEVCFG_PRODUCT_DATA
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

