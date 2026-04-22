/* Dem_Calibration_Cfg_c(v5-3-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DEM/Calibration_Cfg/CODE                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "Dem_Calibration_Cfg.h"


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


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CONST_CONFIG
#include <Dem_MemMap.h>

CONST( AB_83_ConstV Dem_EventIdType                       ,DEM_CONFIG_DATA ) Dem_EventCtrlIndexToEventIdTable[ DEM_PRIMEM_EVENT_NUM ] =
{
    DemConf_DemEventParameter_DemEventDTC_P1100,
    DemConf_DemEventParameter_DemEventDTC_U0827,
    DemConf_DemEventParameter_DemEventDTC_C0597,
    DemConf_DemEventParameter_DemEventDTC_C05D6,
    DemConf_DemEventParameter_DemEventDTC_U0832,
    DemConf_DemEventParameter_DemEventDTC_C0559,
    DemConf_DemEventParameter_DemEventDTC_U0851,
    DemConf_DemEventParameter_DemEventDTC_U1809,
    DemConf_DemEventParameter_DemEventDTC_U170D,
    DemConf_DemEventParameter_DemEventDTC_U0843,
    DemConf_DemEventParameter_DemEventDTC_U0845,
    DemConf_DemEventParameter_DemEventDTC_U085C,
    DemConf_DemEventParameter_DemEventDTC_U1802,
    DemConf_DemEventParameter_DemEventDTC_U0822,
    DemConf_DemEventParameter_DemEventDTC_U1706,
    DemConf_DemEventParameter_DemEventDTC_U1807,
    DemConf_DemEventParameter_DemEventDTC_B1510,
    DemConf_DemEventParameter_DemEventDTC_B1511,
    DemConf_DemEventParameter_DemEventDTC_B1518,
    DemConf_DemEventParameter_DemEventDTC_B1519,
    DemConf_DemEventParameter_DemEventDTC_B151A
};

CONST( AB_83_ConstV Dem_EventIdType                       ,DEM_CONFIG_DATA ) Dem_UdmEventIndexToEventIdTable[ DEM_USRDEFMEM_TOTAL_EVENT_NUM ] =
{
    DemConf_DemEventParameter_DemEventDTC_B2E01,
    DemConf_DemEventParameter_DemEventDTC_B2E02,
    DemConf_DemEventParameter_DemEventDTC_B2E03,
    DemConf_DemEventParameter_DemEventDTC_B2E04,
    DemConf_DemEventParameter_DemEventDTC_B2E05,
    DemConf_DemEventParameter_DemEventDTC_B2E06,
    DemConf_DemEventParameter_DemEventDTC_B2E07,
    DemConf_DemEventParameter_DemEventDTC_B2E08,
    DemConf_DemEventParameter_DemEventDTC_B2E12,
    DemConf_DemEventParameter_DemEventDTC_B2E15,
    DemConf_DemEventParameter_DemEventDTC_B2E22,
    DemConf_DemEventParameter_DemEventDTC_B2E23,
    DemConf_DemEventParameter_DemEventDTC_B2E24,
    DemConf_DemEventParameter_DemEventDTC_B2E25,
    DemConf_DemEventParameter_DemEventDTC_B2E26,
    DemConf_DemEventParameter_DemEventDTC_B2E27,
    DemConf_DemEventParameter_DemEventDTC_B2E28,
    DemConf_DemEventParameter_DemEventDTC_B2E29,
    DemConf_DemEventParameter_DemEventDTC_B2E30,
    DemConf_DemEventParameter_DemEventDTC_B2E20,
    DemConf_DemEventParameter_DemEventDTC_U2A00,
    DemConf_DemEventParameter_DemEventDTC_U2A01,
    DemConf_DemEventParameter_DemEventDTC_U2A16,
    DemConf_DemEventParameter_DemEventDTC_U2A17,
    DemConf_DemEventParameter_DemEventDTC_U2A13,
    DemConf_DemEventParameter_DemEventDTC_U2A12,
    DemConf_DemEventParameter_DemEventDTC_U2303,
    DemConf_DemEventParameter_DemEventDTC_U2302,
    DemConf_DemEventParameter_DemEventDTC_U13A0,
    DemConf_DemEventParameter_DemEventDTC_U2300,
    DemConf_DemEventParameter_DemEventDTC_U2301
};

CONST( AB_83_ConstV Dem_u16_EventCtrlIndexType                ,DEM_CONFIG_DATA ) Dem_EventParameterIndexOrderTable[ DEM_TOTAL_EVENT_NUM ] =
{
    0x0000U,        /* DemConf_DemEventParameter_DemEventDTC_P1100 */
    0x0001U,        /* DemConf_DemEventParameter_DemEventDTC_U0827 */
    0x0002U,        /* DemConf_DemEventParameter_DemEventDTC_C0597 */
    0x0003U,        /* DemConf_DemEventParameter_DemEventDTC_C05D6 */
    0x0004U,        /* DemConf_DemEventParameter_DemEventDTC_U0832 */
    0x0005U,        /* DemConf_DemEventParameter_DemEventDTC_C0559 */
    0x0006U,        /* DemConf_DemEventParameter_DemEventDTC_U0851 */
    0x0007U,        /* DemConf_DemEventParameter_DemEventDTC_U1809 */
    0x0008U,        /* DemConf_DemEventParameter_DemEventDTC_U170D */
    0x0009U,        /* DemConf_DemEventParameter_DemEventDTC_U0843 */
    0x000AU,        /* DemConf_DemEventParameter_DemEventDTC_U0845 */
    0x000BU,        /* DemConf_DemEventParameter_DemEventDTC_U085C */
    0x000CU,        /* DemConf_DemEventParameter_DemEventDTC_U1802 */
    0x000DU,        /* DemConf_DemEventParameter_DemEventDTC_U0822 */
    0x000EU,        /* DemConf_DemEventParameter_DemEventDTC_U1706 */
    0x000FU,        /* DemConf_DemEventParameter_DemEventDTC_U1807 */
    0x0010U,        /* DemConf_DemEventParameter_DemEventDTC_B1510 */
    0x0011U,        /* DemConf_DemEventParameter_DemEventDTC_B1511 */
    0x0012U,        /* DemConf_DemEventParameter_DemEventDTC_B1518 */
    0x0013U,        /* DemConf_DemEventParameter_DemEventDTC_B1519 */
    0x0014U,        /* DemConf_DemEventParameter_DemEventDTC_B151A */
    0x8014U,        /* DemConf_DemEventParameter_DemEventDTC_U2A00 */
    0x8015U,        /* DemConf_DemEventParameter_DemEventDTC_U2A01 */
    0x8016U,        /* DemConf_DemEventParameter_DemEventDTC_U2A16 */
    0x8017U,        /* DemConf_DemEventParameter_DemEventDTC_U2A17 */
    0x8019U,        /* DemConf_DemEventParameter_DemEventDTC_U2A12 */
    0x8018U,        /* DemConf_DemEventParameter_DemEventDTC_U2A13 */
    0x801AU,        /* DemConf_DemEventParameter_DemEventDTC_U2303 */
    0x801BU,        /* DemConf_DemEventParameter_DemEventDTC_U2302 */
    0x801CU,        /* DemConf_DemEventParameter_DemEventDTC_U13A0 */
    0x801DU,        /* DemConf_DemEventParameter_DemEventDTC_U2300 */
    0x801EU,        /* DemConf_DemEventParameter_DemEventDTC_U2301 */
    0x8000U,        /* DemConf_DemEventParameter_DemEventDTC_B2E01 */
    0x8001U,        /* DemConf_DemEventParameter_DemEventDTC_B2E02 */
    0x8002U,        /* DemConf_DemEventParameter_DemEventDTC_B2E03 */
    0x8003U,        /* DemConf_DemEventParameter_DemEventDTC_B2E04 */
    0x8004U,        /* DemConf_DemEventParameter_DemEventDTC_B2E05 */
    0x8005U,        /* DemConf_DemEventParameter_DemEventDTC_B2E06 */
    0x8006U,        /* DemConf_DemEventParameter_DemEventDTC_B2E07 */
    0x8007U,        /* DemConf_DemEventParameter_DemEventDTC_B2E08 */
    0x8008U,        /* DemConf_DemEventParameter_DemEventDTC_B2E12 */
    0x8009U,        /* DemConf_DemEventParameter_DemEventDTC_B2E15 */
    0x8013U,        /* DemConf_DemEventParameter_DemEventDTC_B2E20 */
    0x800AU,        /* DemConf_DemEventParameter_DemEventDTC_B2E22 */
    0x800BU,        /* DemConf_DemEventParameter_DemEventDTC_B2E23 */
    0x800CU,        /* DemConf_DemEventParameter_DemEventDTC_B2E24 */
    0x800DU,        /* DemConf_DemEventParameter_DemEventDTC_B2E25 */
    0x800EU,        /* DemConf_DemEventParameter_DemEventDTC_B2E26 */
    0x800FU,        /* DemConf_DemEventParameter_DemEventDTC_B2E27 */
    0x8010U,        /* DemConf_DemEventParameter_DemEventDTC_B2E28 */
    0x8011U,        /* DemConf_DemEventParameter_DemEventDTC_B2E29 */
    0x8012U         /* DemConf_DemEventParameter_DemEventDTC_B2E30 */
};

#define DEM_STOP_SEC_CONST_CONFIG
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
