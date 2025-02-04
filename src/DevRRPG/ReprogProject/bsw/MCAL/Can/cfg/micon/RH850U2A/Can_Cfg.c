/* Can_Cfg_c */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | RH850/U2Ax/Can/Cfg/CODE                                     */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Can.h>


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
#pragma ghs section rosdata = ".C_CAN"

/* CAN Controller Setting Configuration Table */
static const Can_ControllerSettingConfigType CAN_CFG_CONTROLLERSETTING_DATA[] =
{
    {
        STD_OFF,
        0U,
        1U
    },
    {
        STD_OFF,
        0U,
        1U
    },
    {
        STD_OFF,
        0U,
        1U
    },
    {
        STD_OFF,
        0U,
        1U
    },
    {
        STD_OFF,
        0U,
        1U
    },
    {
        STD_ON,
        0U,
        1U
    },
    {
        STD_OFF,
        0U,
        1U
    },
    {
        STD_OFF,
        0U,
        1U
    },
    {
        STD_OFF,
        0U,
        1U
    },
    {
        STD_OFF,
        0U,
        1U
    },
    {
        STD_OFF,
        0U,
        1U
    },
    {
        STD_OFF,
        0U,
        1U
    },
    {
        STD_OFF,
        0U,
        1U
    },
    {
        STD_OFF,
        0U,
        1U
    },
    {
        STD_OFF,
        0U,
        1U
    },
    {
        STD_OFF,
        0U,
        1U
    }
};

/* CAN Controller Baudrate Setting Configuration Table */
static const Can_ControllerBaudRateSettingConfigType CAN_CFG_CONTROLLER_BAUDRATESETTING_DATA[] =
{
    {
        500U,
        47U,
        16U,
        16U,
        16U,
        1U
    }
};

/* CAN Hardware Object Configuration Table */
static const Can_HardwareObjConfigType CAN_CFG_HARDWARE_OBJECT_DATA[CAN_HARDWAREOBJ_NUM] =
{
    {
        CAN_RX,
        5U,
        0U,
        0x18DA17E0UL,             /* ^^^ */
        CAN_FD_ID_EXTEND
    },
    {
        CAN_RX,
        5U,
        1U,
        0x18DBEFE0UL,             /* ^^^ */
        CAN_FD_ID_EXTEND
    },
    {
        CAN_TX,
        5U,
        2U,
        0x18DAE017UL,             /* ^^^ */
        CAN_FD_ID_EXTEND
    },
    {
        CAN_TX,                   /* ^^^ */
        5U,                       /* ^^^ */
        3U,                       /* ^^^ */
        0x18DAE017UL,             /* ^^^ */
        CAN_ID_EXTEND             /* ^^^ */
    },
    {
        CAN_NOUSE,
        0U,
        0U,
        0UL,
        0U
    },
    {
        CAN_NOUSE,
        0U,
        0U,
        0UL,
        0U
    },
    {
        CAN_NOUSE,
        0U,
        0U,
        0UL,
        0U
    },
    {
        CAN_NOUSE,
        0U,
        0U,
        0UL,
        0U
    },
    {
        CAN_NOUSE,
        0U,
        0U,
        0UL,
        0U
    },
    {
        CAN_NOUSE,
        0U,
        0U,
        0UL,
        0U
    },
    {
        CAN_NOUSE,
        0U,
        0U,
        0UL,
        0U
    },
    {
        CAN_NOUSE,
        0U,
        0U,
        0UL,
        0U
    },
    {
        CAN_NOUSE,
        0U,
        0U,
        0UL,
        0U
    },
    {
        CAN_NOUSE,
        0U,
        0U,
        0UL,
        0U
    },
    {
        CAN_NOUSE,
        0U,
        0U,
        0UL,
        0U
    },
    {
        CAN_NOUSE,
        0U,
        0U,
        0UL,
        0U
    }
};

/* CAN Controller Configuration Table */
static const Can_ControllerConfigType CAN_CFG_CONTROLLER_DATA =
{
    16U,
    &CAN_CFG_CONTROLLERSETTING_DATA[0]
};

/* CAN Controller Baudrate Configuration Table */
static const Can_ControllerBaudRateConfigType CAN_CFG_CONTROLLER_BAUDRATE_DATA =
{
    1U,
    &CAN_CFG_CONTROLLER_BAUDRATESETTING_DATA[0]
};

/* CAN Configuration Table */
const Can_ConfigType CAN_CFG_DATA =
{
    &CAN_CFG_CONTROLLER_DATA,
    &CAN_CFG_CONTROLLER_BAUDRATE_DATA,
    &CAN_CFG_HARDWARE_OBJECT_DATA[0]
};

/* [Device Individuality Config] CAN Controller Baudrate Setting Configuration Table [DataBitRate] */
static const Can_ControllerBaudRateSettingConfigType CAN_DEVCFG_CONTROLLER_BAUDRATESETTING_DATA[] =
{
    {
        2000U,
        7U,
        6U,
        6U,
        6U,
        1U
    }
};

/* [Device Individuality Config] CAN Product Setting Configuration Table */
static const Can_DevProductSettingConfigType CAN_DEVCFG_PRODUCT_DATA =
{
    CAN_PRODUCT_U2A16_516PIN
};

/* [Device Individuality Config] CAN Device Individuality Configuration Table */
const Can_DevConfigType CAN_DEVCFG_DATA =
{
    &CAN_DEVCFG_CONTROLLER_BAUDRATESETTING_DATA[0],
    &CAN_DEVCFG_PRODUCT_DATA
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
/*  v1.00       :2022/05/31 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

