/* CodeFls_Cfg_c                                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | RH850/U2Ax/CodeFls/Cfg/CODE                               */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include "../inc/CodeFls.h"


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define MEM_START_SEC_VAR_NO_INIT_32
#include <Mem_MemMap.h>

#define MEM_STOP_SEC_VAR_NO_INIT_32
#include <Mem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define MEM_START_SEC_CONST_CONFIG_32
#include <Mem_MemMap.h>

/* [Device Individuality Config] CODEFLS Information Configuration Table */
static CONST(AB_83_ConstV CodeFls_DevCodeFlsInfoConfigType, MEM_CONFIG_DATA) CODEFLS_DEVCFG_CODEFLSINFO_DATA[] =
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
static CONST(AB_83_ConstV CodeFls_DevCodeFlsSettingConfigType, MEM_CONFIG_DATA) CODEFLS_DEVCFG_CODEFLSSETTING_DATA =
{
    4U,
    &CODEFLS_DEVCFG_CODEFLSINFO_DATA[0]
};

/* [Device Individuality Config] CODEFLS Authentication ID Information Configuration Table */
static CONST(AB_83_ConstV CodeFls_DevAuthIdInfoConfigType, MEM_CONFIG_DATA) CODEFLS_DEVCFG_AUTHIDINFO_DATA[] =
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
static CONST(AB_83_ConstV CodeFls_DevAuthIdSettingConfigType, MEM_CONFIG_DATA) CODEFLS_DEVCFG_AUTHID_DATA =
{
    3U,
    &CODEFLS_DEVCFG_AUTHIDINFO_DATA[0]
};

/* [Device Individuality Config] CODEFLS Product Setting Configuration Table */
static CONST(AB_83_ConstV CodeFls_DevProductSettingConfigType, MEM_CONFIG_DATA) CODEFLS_DEVCFG_PRODUCT_DATA =
{
    CODEFLS_PRODUCT_U2A16,
    CODEFLS_CPU_CLOCK_400
};

/* [Device Individuality Config] CODEFLS Valid Area Permit Table */
static CONST(AB_83_ConstV CodeFls_DevValidAreaPermitType, MEM_CONFIG_DATA) CODEFLS_DEVCFG_VALIDAREA_PERMIT_DATA =
{
    STD_OFF
};

/* [Device Individuality Config] CODEFLS Device Individuality Configuration Table */
CONST(AB_83_ConstV CodeFls_DevConfigType, MEM_CONFIG_DATA) CODEFLS_DEVCFG_DATA =
{
    &CODEFLS_DEVCFG_CODEFLSSETTING_DATA,
    &CODEFLS_DEVCFG_AUTHID_DATA,
    &CODEFLS_DEVCFG_PRODUCT_DATA,
    &CODEFLS_DEVCFG_VALIDAREA_PERMIT_DATA
};

#define MEM_STOP_SEC_CONST_CONFIG_32
#include <Mem_MemMap.h>


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1.00          :2025/03/24                                              */
/*  v1.01          :2025/04/14                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

