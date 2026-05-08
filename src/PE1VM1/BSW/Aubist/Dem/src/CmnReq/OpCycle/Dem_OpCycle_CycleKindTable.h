/* Dem_Dem_OpCycle_CycleKindTable_h(v5-5-0)                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/OpCycle_CycleKindTable/HEADER                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_OPCYCLE_CYCLEKINDTABLE_H
#define DEM_OPCYCLE_CYCLEKINDTABLE_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../../../inc/Dem_CmnLib_OpCycle.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CONST_CONFIG
#include <Dem_MemMap.h>

extern  CONST( AB_83_ConstV Dem_u08_OpcycUpdateFailureCycleType,        DEM_CONFIG_DATA ) Dem_OpCycleUpdateFailureCycleTable[ DEM_OPCYCKIND_CFGCYCLE_MAX ][ DEM_OPCYCKIND_THISCYCLE_MAX ];
extern  CONST( AB_83_ConstV Dem_u08_OpcycUpdateHealingAgingCycleType,   DEM_CONFIG_DATA ) Dem_OpCycleUpdateHealingAgingCycleTable[ DEM_OPCYCKIND_CFGCYCLE_MAX ][ DEM_OPCYCKIND_THISCYCLE_MAX ];


#define DEM_STOP_SEC_CONST_CONFIG
#include <Dem_MemMap.h>

#endif /* DEM_OPCYCLE_CYCLEKINDTABLE_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
