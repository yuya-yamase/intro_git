/* Dem_SimilarCondition_Callout_c(v5-5-0)                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/SimilarCondition_Callout/CODE                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "Dem_SimilarCondition_Callout.h"

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

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_JudgeSimilarCondition                                */
/* Description   | Judge Similar condition.                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] OldConditionPtr : stored similar condition.         */
/*               | [in] NewConditionPtr : triggered similar condition.      */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : similar condition is established.         */
/*               |        FALSE : similar condition is not established.     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( boolean, DEM_CODE_CALLOUT ) Dem_JudgeSimilarCondition
(
    P2CONST( Dem_SimilarConditionValueType, AUTOMATIC, AUTOMATIC ) OldConditionPtr,
    P2CONST( Dem_SimilarConditionValueType, AUTOMATIC, AUTOMATIC ) NewConditionPtr
)
{
    return (boolean)TRUE;
}

#define DEM_STOP_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>

#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-03-19                                              */
/*  v5-0-0         :2021-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
