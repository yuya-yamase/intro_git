/* Dem_PBcfg_c(v5-5-0)                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
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
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE ),                /* DemConf_DemEventParameter_DemEventDTC_U0100 */
    ( DEM_PB_EVTATTR_OBD_NONOBD | DEM_PB_EVTATTR_AVAILABLE_DISABLE )                 /* DemConf_DemEventParameter_DemEventDTC_B1500 */
};

#define DEM_STOP_SEC_CONST_PBCONFIG_DIRECTLY_EVENTPARAMETERATTRIBUTE
#include <Dem_MemMap.h>

#define DEM_START_SEC_CONST_PBCONFIG_DIRECTLY_FAILURECYCLECOUNTERTHRESHOLD
#include <Dem_MemMap.h>

CONST( AB_83_ConstV Dem_FailureCycleCounterThresholdType ,DEM_CONST_PBCONFIG_DIRECTLY_FAILURECYCLECOUNTERTHRESHOLD ) Dem_PB_FailureCycleCounterThreshold[ DEM_TOTAL_EVENT_NUM ] =
{
    1U,             /* DemConf_DemEventParameter_DemEventDTC_U0100 */
    1U              /* DemConf_DemEventParameter_DemEventDTC_B1500 */
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
/*  Framework          :v2-0-3-z0003                                        */
/*  BSW plug-in        :v5-5-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
