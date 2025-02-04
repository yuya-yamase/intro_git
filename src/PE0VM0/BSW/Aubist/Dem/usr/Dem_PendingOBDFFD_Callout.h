/* Dem_PendingOBDFFD_Callout_h(v5-5-0)                                      */
/****************************************************************************/
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/PendingOBDFFD_Callout/HEADER                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_PENDINGOBDFFD_CALLOUT_H
#define DEM_PENDINGOBDFFD_CALLOUT_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#if ( DEM_OBDFFD_SUPPORT == STD_ON )

#include <Dem/Dem_Common.h>
#include "../cfg/Dem_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>

FUNC( boolean, DEM_CODE_CALLOUT ) Dem_JudgePendingOBDFFDUpdateAtConfirmedTrigger
( void );

#if ( DEM_CALIBRATION_BY_CALLOUT_SUPPORT == STD_ON )
FUNC( boolean, DEM_CODE_CALLOUT ) Dem_JudgeOutputPendingOBDFFDWithoutCDTC
( void );
#endif  /* ( DEM_CALIBRATION_BY_CALLOUT_SUPPORT == STD_ON ) */

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

#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )   */

#endif  /* DEM_PENDINGOBDFFD_CALLOUT_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
