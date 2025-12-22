/* Dem_SavedZone_Callout_h(v5-6-0)                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/SavedZone_Callout/HEADER                              */
/*--------------------------------------------------------------------------*/
/* Notes |                                                                  */
/****************************************************************************/

#ifndef DEM_SAVEDZONE_CALLOUT_H
#define DEM_SAVEDZONE_CALLOUT_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef uint8   Dem_SavedZoneInitializeType;                /* SavedZoneInitializeType */
/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_SZINITTYPE_NO_INITIALIZE                         ((Dem_SavedZoneInitializeType)0x00U)
#define DEM_SZINITTYPE_INITIALIZE_SAMEAS_CLEARDTC            ((Dem_SavedZoneInitializeType)0x01U)
#define DEM_SZINITTYPE_INITIALIZE_WITHOUT_PFC_AND_IUMPR      ((Dem_SavedZoneInitializeType)0x02U)
#define DEM_SZINITTYPE_INITIALIZE_WITHOUT_PFC                ((Dem_SavedZoneInitializeType)0x03U)
#define DEM_SZINITTYPE_INITIALIZE_ALL                        ((Dem_SavedZoneInitializeType)0x04U)

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>

FUNC( Dem_SavedZoneInitializeType, DEM_CODE_CALLOUT ) Dem_GetSavedZoneInitializeType
( void );
FUNC( void, DEM_CODE_CALLOUT ) Dem_NotifySavedZoneUpdate_Enter
( void );
FUNC( void, DEM_CODE_CALLOUT ) Dem_NotifySavedZoneUpdate_Exit
( void );

#if ( DEM_PFC_SUPPORT == STD_ON )
FUNC( void, DEM_CODE_CALLOUT ) Dem_NotifySavedZonePermanentUpdate_Enter
( void );
FUNC( void, DEM_CODE_CALLOUT ) Dem_NotifySavedZonePermanentUpdate_Exit
( void );
#endif  /* ( DEM_PFC_SUPPORT == STD_ON )        */

#if ( DEM_IUMPR_SUPPORT == STD_ON )
FUNC( void, DEM_CODE_CALLOUT ) Dem_NotifySavedZoneIUMPRUpdate_Enter
( void );
FUNC( void, DEM_CODE_CALLOUT ) Dem_NotifySavedZoneIUMPRUpdate_Exit
( void );
#endif  /* ( DEM_IUMPR_SUPPORT == STD_ON )        */

#define DEM_STOP_SEC_CODE_CALLOUT
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


#endif /* DEM_SAVEDZONE_CALLOUT_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-6-0         :2024-01-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
