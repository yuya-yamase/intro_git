/* Dem_Pm_DataOeo_h(v5-5-0)                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Pm_DataOeo/HEADER                                     */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_PM_DATAOEO_H
#define DEM_PM_DATAOEO_H


/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../cfg/Dem_Cfg.h"


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )

#if ( DEM_OBD_SUPPORT == STD_ON )
typedef uint8                 Dem_u08_OBDOverwritePossibilityType;
#define DEM_OBDOVW_OVERWRITE_POSSIBLE               ((Dem_u08_OBDOverwritePossibilityType)0x00U)
#define DEM_OBDOVW_OVERWRITE_IMPOSSIBLE_BY_OBDFFD   ((Dem_u08_OBDOverwritePossibilityType)0x01U)
#define DEM_OBDOVW_OVERWRITE_IMPOSSIBLE_BY_MIL      ((Dem_u08_OBDOverwritePossibilityType)0x02U)
#endif  /* ( DEM_OBD_SUPPORT == STD_ON )        */
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )    */

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

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
#if ( DEM_OBD_SUPPORT == STD_ON )
FUNC( Dem_u08_OBDOverwritePossibilityType, DEM_CODE ) Dem_DcOeo_CheckOBDEventOverwritePossibility
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex
);
#endif  /* ( DEM_OBD_SUPPORT == STD_ON )        */

#if ( DEM_OBDONEDS_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_DcOeo_SetEdsOBDFFDTarget
( void );
#endif  /* ( DEM_OBDONEDS_SUPPORT == STD_ON )    */

#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )    */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif /* DEM_DATAOEO_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-03-19                                              */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
