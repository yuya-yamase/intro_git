/* Dem_IUMPR_Callout_h(v5-5-0)                                              */
/****************************************************************************/
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/IUMPR_Callout/HEADER                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_IUMPR_CALLOUT_H
#define DEM_IUMPR_CALLOUT_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#if ( DEM_IUMPR_SUPPORT == STD_ON )

#include <Dem/Dem_Common.h>
#include "../cfg/Dem_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>

#if ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )
FUNC( void, DEM_CODE_CALLOUT ) Dem_IUMPR_NotifyRatioUpdate
(
    VAR( Dem_RatioIdType, AUTOMATIC )   RatioID,
    VAR( Dem_IumprDataType, AUTOMATIC ) IumprDataType
);
#endif  /* ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )    */

#if ( DEM_ALTIUMPR_SUPPORT == STD_ON )
FUNC( void, DEM_CODE_CALLOUT ) Dem_JudgeAlternativeIUMPRPauseConditions
(
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) MADConditionPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) MANConditionPtr
);
#endif /* ( DEM_ALTIUMPR_SUPPORT == STD_ON ) */

FUNC( void, DEM_CODE_CALLOUT ) Dem_IUMPR_NotifyGeneralDenominatorUpdate
(void);
FUNC( void, DEM_CODE_CALLOUT ) Dem_IUMPR_NotifyIGCycleCounterUpdate
(void);

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

#endif  /* ( DEM_IUMPR_SUPPORT == STD_ON )    */

#endif  /* DEM_IUMPR_CALLOUT_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
