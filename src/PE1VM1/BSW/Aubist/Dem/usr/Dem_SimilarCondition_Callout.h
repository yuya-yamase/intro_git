/* Dem_SimilarCondition_Callout_h(v5-5-0)                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/SimilarCondition_Callout/HEADER                       */
/*--------------------------------------------------------------------------*/
/* Notes |                                                                  */
/****************************************************************************/

#ifndef DEM_SIMILARCONDITION_CALLOUT_H
#define DEM_SIMILARCONDITION_CALLOUT_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../cfg/Dem_Cfg.h"

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )
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
#define DEM_START_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>

FUNC( boolean, DEM_CODE_CALLOUT ) Dem_JudgeSimilarCondition
(
    P2CONST( Dem_SimilarConditionValueType, AUTOMATIC, AUTOMATIC ) OldConditionPtr,
    P2CONST( Dem_SimilarConditionValueType, AUTOMATIC, AUTOMATIC ) NewConditionPtr
);

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

#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )    */

#endif /* DEM_SIMILARCONDITION_CALLOUT_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-03-19                                              */
/*  v5-0-0         :2021-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
