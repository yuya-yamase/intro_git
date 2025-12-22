/* Dem_Pm_Ind_MI_h(v5-7-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/


/****************************************************************************/
/* Object Name  | Dem/Pm_Ind_MI/HEADER                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_PM_IND_MI_H
#define DEM_PM_IND_MI_H

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

/*----------------------------------*/
/*  Dem_Ind_MI_CtrlShortMI_WWH.c    */
/*----------------------------------*/
#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_IndMI_Init_AfterRecordCheckComplete
( void );
FUNC( void, DEM_CODE ) Dem_IndMI_Init_AfterOrderListGenerateComplete
( void );

FUNC( void, DEM_CODE ) Dem_IndMI_SetMILAtShortMI
(
    VAR( Dem_u08_DemBooleanType, AUTOMATIC ) MILStatus
);

FUNC( Dem_u08_DemBooleanType, DEM_CODE ) Dem_IndMI_GetMILAtShortMIFlg
( void );
#endif  /*   ( DEM_WWH_OBD_SUPPORT == STD_ON )      */

/*----------------------------------*/
/*  Dem_Ind_MI_B1Counter_WWH.c      */
/*----------------------------------*/
#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_IndMI_GetB1Counter
(
    P2VAR( Dem_u32_B1CounterType, AUTOMATIC, AUTOMATIC ) B1CounterPtr
);
FUNC( void, DEM_CODE ) Dem_IndMI_GetB1CounterByEventStrgIndex_By6Minutes
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u16_B1CounterOutputType, AUTOMATIC, AUTOMATIC ) B1Counter6MinPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IndMI_CheckB1CounterThresholdReached
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) B1CounterThresholdReachedPtr
);
FUNC( void, DEM_CODE ) Dem_IndMI_UpdateB1Counter
( void );

FUNC( void, DEM_CODE ) Dem_IndMI_ClearB1Counter
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);

FUNC( void, DEM_CODE ) Dem_IndMI_HoldB1Counter
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);

FUNC( void, DEM_CODE ) Dem_IndMI_UpdateB1CounterWhenClearDTC
( void );

FUNC( void, DEM_CODE ) Dem_IndMI_B1CounterHealingProcess
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);

FUNC( void, DEM_CODE ) Dem_IndMI_UpdateB1RecordBySetEvent
(
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
);

FUNC( void, DEM_CODE ) Dem_IndMI_GenerateEventStrgIndexToIndMIIndexList
( void );

FUNC( void, DEM_CODE ) Dem_IndMI_UpdateB1Record
( void );

#endif  /*   ( DEM_WWH_OBD_SUPPORT == STD_ON )      */

/*----------------------------------*/
/*  Dem_Ind_MI_GetMIStatus.c        */
/*----------------------------------*/
/*----------------------------------*/
/*  Dem_Ind_MI_GetMIStatus_WWH.c    */
/*----------------------------------*/
#if ( DEM_OBD_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IndMI_GetMILStatusByEventStrgIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_IndicatorStatusType, AUTOMATIC, AUTOMATIC ) IndicatorStatusPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IndMI_GetMILStatus
(
    P2VAR( Dem_IndicatorStatusType, AUTOMATIC, AUTOMATIC ) IndicatorStatusPtr
);
#endif  /* ( DEM_OBD_SUPPORT == STD_ON )    */

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
FUNC( boolean, DEM_CODE ) Dem_IndMI_IsContMIorShortMI_ByEventStrgIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
#endif  /*   ( DEM_WWH_OBD_SUPPORT == STD_ON )      */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* DEM_PM_IND_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
