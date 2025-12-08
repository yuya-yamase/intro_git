/* CodeFls_Cfg_c */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | RH850/U2Ax/CodeFls/Cfg/CODE                                 */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <CodeFls.h>


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
#pragma ghs section rosdata = ".C_CODEFLS"

/* [Device Individuality Config] CODEFLS Information Configuration Table */
static const CodeFls_DevCodeFlsInfoConfigType CODEFLS_DEVCFG_CODEFLSINFO_DATA[] =
{
    {
        0x00000000UL,
        0x00400000UL
    },
    {
        0x00400000UL,
        0x00400000UL
    },
    {
        0x02000000UL,
        0x00400000UL
    },
    {
        0x02400000UL,
        0x00400000UL
    }
};

/* [Device Individuality Config] CODEFLS Setting Configuration Table */
static const CodeFls_DevCodeFlsSettingConfigType CODEFLS_DEVCFG_CODEFLSSETTING_DATA =
{
    4U,
    &CODEFLS_DEVCFG_CODEFLSINFO_DATA[0]
};

/* [Device Individuality Config] CODEFLS Authentication ID Information Configuration Table */
static const CodeFls_DevAuthIdInfoConfigType CODEFLS_DEVCFG_AUTHIDINFO_DATA[] =
{
    {
        CODEFLS_CUSTOMERID_A,
        {
            0xFFU,0xFFU,0xFFU,0xFFU,
            0xFFU,0xFFU,0xFFU,0xFFU,
            0xFFU,0xFFU,0xFFU,0xFFU,
            0xFFU,0xFFU,0xFFU,0xFFU,
            0xFFU,0xFFU,0xFFU,0xFFU,
            0xFFU,0xFFU,0xFFU,0xFFU,
            0xFFU,0xFFU,0xFFU,0xFFU,
            0xFFU,0xFFU,0xFFU,0xFFU
        }
    },
    {
        CODEFLS_CUSTOMERID_B,
        {
            0xFFU,0xFFU,0xFFU,0xFFU,
            0xFFU,0xFFU,0xFFU,0xFFU,
            0xFFU,0xFFU,0xFFU,0xFFU,
            0xFFU,0xFFU,0xFFU,0xFFU,
            0xFFU,0xFFU,0xFFU,0xFFU,
            0xFFU,0xFFU,0xFFU,0xFFU,
            0xFFU,0xFFU,0xFFU,0xFFU,
            0xFFU,0xFFU,0xFFU,0xFFU
        }
    },
    {
        CODEFLS_CUSTOMERID_C,
        {
            0xFFU,0xFFU,0xFFU,0xFFU,
            0xFFU,0xFFU,0xFFU,0xFFU,
            0xFFU,0xFFU,0xFFU,0xFFU,
            0xFFU,0xFFU,0xFFU,0xFFU,
            0xFFU,0xFFU,0xFFU,0xFFU,
            0xFFU,0xFFU,0xFFU,0xFFU,
            0xFFU,0xFFU,0xFFU,0xFFU,
            0xFFU,0xFFU,0xFFU,0xFFU
        }
    }
};

/* [Device Individuality Config] CODEFLS Authentication ID Configuration Table */
static const CodeFls_DevAuthIdSettingConfigType CODEFLS_DEVCFG_AUTHID_DATA =
{
    3U,
    &CODEFLS_DEVCFG_AUTHIDINFO_DATA[0]
};

/* [Device Individuality Config] CODEFLS Product Setting Configuration Table */
static const CodeFls_DevProductSettingConfigType CODEFLS_DEVCFG_PRODUCT_DATA =
{
    CODEFLS_PRODUCT_U2A16
};

/* [Device Individuality Config] CODEFLS Valid Area Permit Table */
static const CodeFls_DevValidAreaPermitType CODEFLS_DEVCFG_VALIDAREA_PERMIT_DATA =
{
    STD_ON
};

/* [Device Individuality Config] CODEFLS Device Individuality Configuration Table */
const CodeFls_DevConfigType CODEFLS_DEVCFG_DATA =
{
    &CODEFLS_DEVCFG_CODEFLSSETTING_DATA,
    &CODEFLS_DEVCFG_AUTHID_DATA,
    &CODEFLS_DEVCFG_PRODUCT_DATA,
    &CODEFLS_DEVCFG_VALIDAREA_PERMIT_DATA
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
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/
/**** End of File *************************************************************/

