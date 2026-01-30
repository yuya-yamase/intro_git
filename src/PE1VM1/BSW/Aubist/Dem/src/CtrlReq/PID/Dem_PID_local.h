/* Dem_PID_local_h(v5-7-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/PID/HEADER                                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_PID_LOCAL_H
#define DEM_PID_LOCAL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#if ( DEM_PID_READINESS_SUPPORT == STD_ON )

#define DEM_PID_CALC_PID01_TYPEB     ((Dem_u08_ReadinessDataPositionIndexType)0U)
#define DEM_PID_CALC_PID41_TYPEB     ((Dem_u08_ReadinessDataPositionIndexType)2U)
#define DEM_PID_CALC_PID41_TYPECD    ((Dem_u08_ReadinessDataPositionIndexType)3U)
#define DEM_PID_CALC_PIDF501_TYPEB   ((Dem_u08_ReadinessDataPositionIndexType)4U)
#endif  /* ( DEM_PID_READINESS_SUPPORT == STD_ON )    */

#if ( DEM_PID_SUPPORT == STD_ON )

#define DEM_PID_POS0 ((uint8)0U)
#define DEM_PID_POS1 ((uint8)1U)
#define DEM_PID_POS2 ((uint8)2U)
#define DEM_PID_POS3 ((uint8)3U)
#define DEM_PID_POS4 ((uint8)4U)
#define DEM_PID_POS5 ((uint8)5U)

#endif  /* ( DEM_PID_SUPPORT == STD_ON )    */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/*------------------------------*/
/*  Dem_PID_Readiness           */
/*------------------------------*/
#if ( DEM_PID_READINESS_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_PID_ReadReadinessDataOfPID01AndPIDF501
(
    VAR( Dem_u08_ReadinessKindType, AUTOMATIC ) ReadinessCaller,
    VAR( Dem_u08_ReadinessKindType, AUTOMATIC ) ReadinessDataKind,
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) ReadinessDataPtr
);
FUNC( void, DEM_CODE ) Dem_PID_ReadReadinessDataOfPID41
(
    VAR( Dem_u08_ReadinessKindType, AUTOMATIC ) ReadinessCaller,
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID41value
);

FUNC( void, DEM_CODE ) Dem_PID_SetInitFixedValue
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PIDvalue
);
FUNC( void, DEM_CODE ) Dem_PID_SetEngType
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PIDvalue
);

FUNC( void, DEM_CODE ) Dem_PID_SetInitFixedValueOfPIDF501
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PIDvalue
);
FUNC( void, DEM_CODE ) Dem_PID_ClearAllEventDisable
( void );

#if ( DEM_CALIBRATION_BY_CALLOUT_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_PID_CalcInitReadinessBaseSupportAndCompleteData
(
#ifndef DEM_SIT_RANGE_CHECK
#else   /* DEM_SIT_RANGE_CHECK */
    VAR( uint8, AUTOMATIC ) ReadinessDataSize,
#endif  /* DEM_SIT_RANGE_CHECK */
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) ReadinessDataPtr,
    VAR( Dem_u08_ReadinessDataPositionIndexType, AUTOMATIC )    CalcType
);
#endif  /* ( DEM_CALIBRATION_BY_CALLOUT_SUPPORT == STD_ON ) */

FUNC( void, DEM_CODE ) Dem_PID_GetInitDataOfReadinessBaseSupportAndComplete
(
    VAR( Dem_u08_ReadinessKindType, AUTOMATIC ) ReadinessDataKind,
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) ReadinessDataPtr
);

FUNC( void, DEM_CODE ) Dem_PID_InitReadReadinessData
(
    VAR( Dem_u08_ReadinessKindType, AUTOMATIC ) ReadinessCaller,
    VAR( Dem_u08_ReadinessKindType, AUTOMATIC ) ReadinessDataKind,
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) ReadinessDataPtr
);

#endif  /* ( DEM_PID_READINESS_SUPPORT == STD_ON )    */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* DEM_PID_LOCAL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

