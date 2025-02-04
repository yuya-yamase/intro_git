/* Dem_Pm_EDR_h(v5-3-0)                                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/


/****************************************************************************/
/* Object Name  | Dem/Pm_EDR/HEADER                                         */
/*--------------------------------------------------------------------------*/
/* Notes |                                                                  */
/****************************************************************************/

#ifndef DEM_PM_EDR_H
#define DEM_PM_EDR_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

FUNC( Dem_u08_EDRNumberSupBmpIndexType, DEM_CODE ) Dem_EDR_SearchEDRSupportRecNumPos
(
    VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC ) ExtendedDataNumber
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_EDR_SetEDRNumberFilter
(
    VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC ) ExtendedDataNumber
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_EDR_GetNextEDRNumFilteredDTC
(
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
);

FUNC( boolean, DEM_CODE ) Dem_EDR_CheckExtendedDataNumberSupportByRange
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CONST
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_CONST
#include <Dem_MemMap.h>

#endif /* DEM_PM_EDR_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
