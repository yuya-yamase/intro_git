/* Dem_OpCycle_Cfg_h(v5-5-0)                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DEM/OpCycle_Cfg/HEADER                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_OPCYCLE_CFG_H
#define DEM_OPCYCLE_CFG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "Dem_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_OPERATION_CYCLE_CONFIGURE_NUM     ((Dem_u08_OpCycleIndexType)1U)     /* Number of DemOperationCycle */
#define DEM_OPERATION_CYCLE_STARTID_RESTART   ((Dem_u08_OpCycleIndexType)0U)     /* Start of Restat OperationCycle Id value. */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct {
    Dem_u08_OpCycleKindType       DemOperationCycleTypeMember;
    boolean     DemOperationCycleAutostart;
} Dem_OperationCycleClassType;

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

extern CONST( AB_83_ConstV Dem_OperationCycleClassType     ,DEM_CONFIG_DATA )  Dem_OperationCycleTable[DEM_OPERATION_CYCLE_CONFIGURE_NUM];

extern CONST( AB_83_ConstV Dem_u08_OpCycleIndexType        ,DEM_CONFIG_DATA )  Dem_OperationCycleConfigureNum;
extern CONST( AB_83_ConstV Dem_u08_OpCycleIndexType        ,DEM_CONFIG_DATA )  Dem_StartOfRestartOperationCycleId;

extern CONST( AB_83_ConstV Dem_u08_CycleQualifiedIndexType ,DEM_CONFIG_DATA )  Dem_ConfDemOperationCycleObdDcy;
extern CONST( AB_83_ConstV Dem_u08_CycleQualifiedIndexType ,DEM_CONFIG_DATA )  Dem_ConfDemOperationCycleWarmUp;

#define DEM_STOP_SEC_CONST_CONFIG
#include <Dem_MemMap.h>

#endif /* DEM_OPCYCLE_CFG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-5-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
