/* Dem_Pm_DTC_PFC_h(v5-6-0)                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Pm_DTC_PFC/HEADER                                     */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef DEM_PM_DTC_PFC_H
#define DEM_PM_DTC_PFC_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../cfg/Dem_Cfg.h"

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

#if ( DEM_PFC_SUPPORT == STD_ON )
FUNC( void, DEM_CODE_TRUST ) Dem_DTC_PreInitPFCRecordStatus       /*  PreInit section     */
( void );
#endif  /*  ( DEM_PFC_SUPPORT == STD_ON )   */

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

#if ( DEM_PFC_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_DTC_InitForPFC
( void );
FUNC( void, DEM_CODE ) Dem_PFC_RefreshRAM
( void );

FUNC( void, DEM_CODE ) Dem_DTC_SetPFCCycleQualified
( void );

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_GetPermanentDTC
(
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) PFCSearchIndex,
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) PermanentDTCPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_GetClearPFCCycleQualified
(
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) PFCRecordIndex,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) PassedCycleQualifiedPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) DrivingConditionQualifiedPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) PFCCycleQualifiedPtr
);
FUNC( boolean, DEM_CODE ) Dem_DTC_GetEventStrgIndexInPFCRecord
(
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) PFCRecordIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr
);

#if ( DEM_PFC_RECORD_SUPPRESSION_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_DTC_SetPFCUpdateDisable
( void );
FUNC( void, DEM_CODE ) Dem_DTC_SetPFCUpdateEnable
( void );
#endif /* DEM_PFC_RECORD_SUPPRESSION_SUPPORT -STD_ON- */


/*------------------------------------------*/
/*  Interface of access PFC data.           */
/*------------------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_SavePermanentMemoryEntryToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
FUNC( void, DEM_CODE ) Dem_DTC_UpdatePermanentMemoryEntryToTmp
( void );

#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_DTC_UpdateSpecificPermanentMemoryEntryToTmp
( void );
#endif  /* ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )             */

FUNC( void, DEM_CODE ) Dem_DTC_UpdatePFC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    CONSTP2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) OldDTCStatusStPtr,
    CONSTP2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) NewDTCStatusStPtr,
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) MisfireCylinder
);

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_DTC_UpdatePFCFromB1Counter
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC) EventStrgIndex
);
#endif  /* ( DEM_WWH_OBD_SUPPORT == STD_ON )    */

FUNC( void, DEM_CODE ) Dem_DTC_ClearPFCClearCondition
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);

FUNC( void, DEM_CODE ) Dem_DTC_SetPFCClearDisable
(
    VAR( boolean, AUTOMATIC ) IsClearDisable
);

FUNC( void, DEM_CODE ) Dem_DTC_ClearPFC
(
    CONSTP2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) OldDTCStatusStPtr,
    CONSTP2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) NewDTCStatusStPtr
);

FUNC( void, DEM_CODE ) Dem_DTC_ClearPFCByCycleStart
(
    CONSTP2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) OldDTCStatusStPtr,
    CONSTP2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) NewDTCStatusStPtr
);

FUNC( void, DEM_CODE ) Dem_DTC_UpdatePFCRecord
( void );

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_CheckAvailableAndMILStatusByEventStrgIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);

FUNC( void, DEM_CODE ) Dem_DTC_ClearAllPFC
( void );

#endif  /*   ( DEM_PFC_SUPPORT == STD_ON )  */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif /* DEM_PM_DTC_PFC_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2019-03-27                                              */
/*  v3-0-0         :2019-07-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

