/* Dem_Pm_Control_WWHOBD_h(v5-5-0)                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Pm_Control_WWHOBD/HEADER                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_PM_CONTROL_WWHOBD_H
#define DEM_PM_CONTROL_WWHOBD_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../cfg/Dem_Cfg.h"

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )

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

FUNC( void, DEM_CODE ) Dem_Control_InitIndMI
( void );
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetMILAtShortMI
(
    VAR( boolean, AUTOMATIC ) MILStatus
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetB1Counter
(
    P2VAR( Dem_u32_B1CounterType, AUTOMATIC, AUTOMATIC ) B1CounterPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetB1CounterByEventId
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( Dem_u16_B1CounterOutputType, AUTOMATIC, AUTOMATIC ) B1CounterPtr
);
FUNC( void, DEM_CODE ) Dem_Control_UpdateB1CounterProcess
( void );


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_WWH_OBD_SUPPORT == STD_ON )    */
#endif /* DEM_PM_CONTROL_WWHOBD_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

