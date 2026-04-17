/* Dem_Pm_AltIUMPR_h(v5-3-0)                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Pm_AltIUMPR/HEADER                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef DEM_PM_ALTIUMPR_H
#define DEM_PM_ALTIUMPR_H

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
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/*----------------------------------*/
/*  Dem_AltIUMPR                    */
/*----------------------------------*/
#if ( DEM_ALTIUMPR_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_AltIUMPR_SetTestCompleteThisCycle
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_u08_AltIUMPRTestCompletedThisCycleType, AUTOMATIC ) TestCompleteThisCycle
);

FUNC( void, DEM_CODE ) Dem_AltIUMPR_ReadDenominator
(
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DenominatorPtr
);

FUNC( void, DEM_CODE ) Dem_AltIUMPR_IncDenominatorProccess
( void );

FUNC( void, DEM_CODE ) Dem_AltIUMPR_IncNumeratorCounts
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
);

FUNC( void, DEM_CODE ) Dem_AltIUMPR_GetPendingAndMIL
( void );

#endif  /* ( DEM_ALTIUMPR_SUPPORT == STD_ON )   */

/*----------------------------------*/
/*  Dem_AltIUMPR_Misfire            */
/*----------------------------------*/
#if ( DEM_ALTIUMPR_SUPPORT == STD_ON )
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_AltIUMPR_ReadMonitorActivityDataForCylinder
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) NumeratorPtr,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) RatioPtr
);

FUNC( void, DEM_CODE ) Dem_AltIUMPR_PrepareIncNumeratorCountsForCylinder
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);

FUNC( void, DEM_CODE ) Dem_AltIUMPR_IncNumeratorCountsForCylinder
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);

#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */
#endif  /* ( DEM_ALTIUMPR_SUPPORT == STD_ON )   */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* DEM_PM_ALTIUMPR_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

