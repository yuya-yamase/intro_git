/* Dem_Pm_DataAvl_h(v5-5-0)                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Pm_DataAvl/HEADER                                     */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_PM_DATAAVL_H
#define DEM_PM_DATAAVL_H


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

#if ( DEM_EVENT_AVAILABILITY_SUPPORT == STD_ON )
FUNC( void, DEM_CODE_TRUST ) Dem_DataAvl_PreInitForAvl_PriMem   /*  PreInit section     */
( void );
#endif  /* ( DEM_EVENT_AVAILABILITY_SUPPORT == STD_ON ) */

#define DEM_STOP_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/*------------------------------------------*/
/*  PrimaryMemory only                      */
/*------------------------------------------*/
#if ( DEM_EVENT_AVAILABILITY_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataAvl_SetEvtAvl
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( boolean, AUTOMATIC ) AvailableStatus
);
#endif  /* ( DEM_EVENT_AVAILABILITY_SUPPORT == STD_ON ) */

FUNC( boolean, DEM_CODE ) Dem_DataAvl_GetEvtAvl
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
);
FUNC( boolean, DEM_CODE ) Dem_DataAvl_GetEvtAvl_InEvtStrgGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataAvl_GetDTCByEventStrgIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataAvl_GetUDSDTCByEventStrgIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataAvl_GetOBDDTCByEventStrgIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataAvl_GetEventStrgIndexByDTC
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr,
    P2VAR( Dem_MisfireCylinderNumberType, AUTOMATIC, AUTOMATIC ) MisfireCylinderNumberPtr
);

/*------------------------------------------*/
/*  Dem_DataAvl_PriMem_Misfire.c            */
/*------------------------------------------*/
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
FUNC( Dem_u08_MisfireKindBitType, DEM_CODE ) Dem_DataAvl_GetMisfireCylDTCAvailable
( void );
FUNC( Dem_u08_MisfireKindBitType, DEM_CODE ) Dem_DataAvl_GetMisfireCylDTCAvailableAndEventStrgIndex
(
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr
);
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )   */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>



#endif /* DEM_PM_DATAAVL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
