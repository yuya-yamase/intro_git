/* Dem_OpCycle_Cfg_c(v5-5-0)                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DEM/OpCycle_Cfg/CODE                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include "../cfg/Dem_OpCycle_Cfg.h"


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
#define DEM_START_SEC_CONST_CONFIG
#include <Dem_MemMap.h>

CONST( AB_83_ConstV Dem_OperationCycleClassType     ,DEM_CONFIG_DATA )  Dem_OperationCycleTable[DEM_OPERATION_CYCLE_CONFIGURE_NUM] =
{
    /* DemOperationCycleType DemOperationCycleAutostart */
    {  DEM_OPCYC_OTHER, FALSE  }
};

CONST( AB_83_ConstV Dem_u08_OpCycleIndexType        ,DEM_CONFIG_DATA )  Dem_OperationCycleConfigureNum          = DEM_OPERATION_CYCLE_CONFIGURE_NUM;
CONST( AB_83_ConstV Dem_u08_OpCycleIndexType        ,DEM_CONFIG_DATA )  Dem_StartOfRestartOperationCycleId      = DEM_OPERATION_CYCLE_STARTID_RESTART;

CONST( AB_83_ConstV Dem_u08_CycleQualifiedIndexType ,DEM_CONFIG_DATA )  Dem_ConfDemOperationCycleObdDcy         = (Dem_u08_CycleQualifiedIndexType)DemConf_DemOperationCycle_OBD_DCY;
CONST( AB_83_ConstV Dem_u08_CycleQualifiedIndexType ,DEM_CONFIG_DATA )  Dem_ConfDemOperationCycleWarmUp         = (Dem_u08_CycleQualifiedIndexType)DemConf_DemOperationCycle_WARMUP;

#define DEM_STOP_SEC_CONST_CONFIG
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-2                                              */
/*  BSW plug-in        :v5-5-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
