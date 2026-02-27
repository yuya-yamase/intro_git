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
    0x0014U         /* DemConf_DemEventParameter_DemEventDTC_B151A */
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
