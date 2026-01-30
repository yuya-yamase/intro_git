/* Dem_Pm_Ind_h(v5-5-0)                                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/


/****************************************************************************/
/* Object Name  | Dem/Pm_Ind/HEADER                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_PM_IND_H
#define DEM_PM_IND_H

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
/* Function Prototypes - PreInit section                                    */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>

FUNC( void, DEM_CODE_TRUST ) Dem_Ind_PreInit_WIRStatus   /*  PreInit section     */
( void );

#define DEM_STOP_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------*/
/*  Dem_Ind_WIRStatus.c     */
/*--------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Ind_SetWIRStatus
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( boolean, AUTOMATIC ) WIRStatus
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Ind_GetWIRStatus
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) WIRStatusPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Ind_GetWIRStatusByDTC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) WIRStatusPtr
);

FUNC( void, DEM_CODE ) Dem_Ind_ClearWIRStatus
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);

FUNC( Dem_IndicatorStatusType, DEM_CODE ) Dem_Ind_GetIndicatorStatusByWIRStatusAndEventStrgIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_IndicatorStatusType, AUTOMATIC, AUTOMATIC ) IndicatorStatusPtr
);
FUNC( Dem_IndicatorStatusType, DEM_CODE ) Dem_Ind_GetIndicatorStatusByWIRStatus
( void );

/*--------------------------*/
/*  Dem_Ind_MIL.c           */
/*--------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Ind_GetMILStatus
(
    P2VAR( Dem_IndicatorStatusType, AUTOMATIC, AUTOMATIC ) IndicatorStatusPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Ind_GetMILStatusByEventStrgIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_IndicatorStatusType, AUTOMATIC, AUTOMATIC ) IndicatorStatusPtr
);

/*--------------------------*/
/*  Dem_Ind_MIL.c           */
/*--------------------------*/
#if ( DEM_USER_DEFINED_INDICATOR_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Ind_GetUserDefinedIndicator_Primary
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_IndicatorStatusType, AUTOMATIC, AUTOMATIC ) IndicatorStatusPtr
);
#endif  /* ( DEM_USER_DEFINED_INDICATOR_SUPPORT == STD_ON )     */


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
/****************************************************************************/

/**** End of File ***********************************************************/
