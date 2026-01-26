/* Dem_PBcfg_h(v5-5-0)                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DEM/PBcfg/HEADER                                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_PBCFG_H
#define DEM_PBCFG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

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
#define DEM_START_SEC_CONST_PBCONFIG_DIRECTLY_EVENTPARAMETERATTRIBUTE
#include <Dem_MemMap.h>

extern CONST( AB_83_ConstV Dem_PB_EventAttributeType ,DEM_CONST_PBCONFIG_DIRECTLY_EVENTPARAMETERATTRIBUTE ) Dem_PB_EventParameterAttribute[ DEM_TOTAL_EVENT_NUM ];

#define DEM_STOP_SEC_CONST_PBCONFIG_DIRECTLY_EVENTPARAMETERATTRIBUTE
#include <Dem_MemMap.h>

#define DEM_START_SEC_CONST_PBCONFIG_DIRECTLY_FAILURECYCLECOUNTERTHRESHOLD
#include <Dem_MemMap.h>

extern CONST( AB_83_ConstV Dem_FailureCycleCounterThresholdType ,DEM_CONST_PBCONFIG_DIRECTLY_FAILURECYCLECOUNTERTHRESHOLD ) Dem_PB_FailureCycleCounterThreshold[ DEM_TOTAL_EVENT_NUM ];

#define DEM_STOP_SEC_CONST_PBCONFIG_DIRECTLY_FAILURECYCLECOUNTERTHRESHOLD
#include <Dem_MemMap.h>

#endif /* DEM_PBCFG_H */

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
/*  BSW plug-in        :v5-5-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
