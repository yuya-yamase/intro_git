/* Dem_PBcfg_c(v5-5-0)                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DEM/PBcfg/CODE                                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include "Dem_PBcfg.h"

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
#define DEM_START_SEC_CONST_PBCONFIG_DIRECTLY_EVENTPARAMETERATTRIBUTE
#include <Dem_MemMap.h>

CONST( AB_83_ConstV Dem_PB_EventAttributeType ,DEM_CONST_PBCONFIG_DIRECTLY_EVENTPARAMETERATTRIBUTE ) Dem_PB_EventParameterAttribute[ DEM_TOTAL_EVENT_NUM ] =
{
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_P1100 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_U0827 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_C0597 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_C05D6 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_U0832 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_C0559 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_U0851 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_U1809 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_U170D */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_U0843 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_U0845 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_U085C */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_U1802 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_U0822 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_U1706 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_U1807 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_B1510 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_B1511 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_B1518 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_B1519 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_B151A */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_U2A00 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_U2A01 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_U2A16 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_U2A17 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_U2A12 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_U2A13 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_U2303 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_U2302 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_U13A0 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_U2300 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_U2301 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_B2E01 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_B2E02 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_B2E03 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_B2E04 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_B2E05 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_B2E06 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_B2E07 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_B2E08 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_B2E12 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_B2E15 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_B2E20 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_B2E22 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_B2E23 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_B2E24 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_B2E25 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_B2E26 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_B2E27 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_B2E28 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_B2E29 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE )                 /* DemConf_DemEventParameter_DemEventDTC_B2E30 */
};

#define DEM_STOP_SEC_CONST_PBCONFIG_DIRECTLY_EVENTPARAMETERATTRIBUTE
#include <Dem_MemMap.h>

#define DEM_START_SEC_CONST_PBCONFIG_DIRECTLY_FAILURECYCLECOUNTERTHRESHOLD
#include <Dem_MemMap.h>

CONST( AB_83_ConstV Dem_FailureCycleCounterThresholdType ,DEM_CONST_PBCONFIG_DIRECTLY_FAILURECYCLECOUNTERTHRESHOLD ) Dem_PB_FailureCycleCounterThreshold[ DEM_TOTAL_EVENT_NUM ] =
{
    1U,             /* DemConf_DemEventParameter_DemEventDTC_P1100 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_U0827 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_C0597 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_C05D6 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_U0832 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_C0559 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_U0851 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_U1809 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_U170D */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_U0843 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_U0845 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_U085C */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_U1802 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_U0822 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_U1706 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_U1807 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_B1510 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_B1511 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_B1518 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_B1519 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_B151A */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_U2A00 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_U2A01 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_U2A16 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_U2A17 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_U2A12 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_U2A13 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_U2303 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_U2302 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_U13A0 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_U2300 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_U2301 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_B2E01 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_B2E02 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_B2E03 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_B2E04 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_B2E05 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_B2E06 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_B2E07 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_B2E08 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_B2E12 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_B2E15 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_B2E20 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_B2E22 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_B2E23 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_B2E24 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_B2E25 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_B2E26 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_B2E27 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_B2E28 */
    1U,             /* DemConf_DemEventParameter_DemEventDTC_B2E29 */
    1U              /* DemConf_DemEventParameter_DemEventDTC_B2E30 */
};

#define DEM_STOP_SEC_CONST_PBCONFIG_DIRECTLY_FAILURECYCLECOUNTERTHRESHOLD
#include <Dem_MemMap.h>


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
