/* Dem_Similar_local_c(v5-7-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Similar_local/CODE                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../usr/Dem_SimilarCondition_Callout.h"
#include "Dem_Similar_local.h"
#include "Dem_Similar_EventEntry_local.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>



/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_Similar_CheckConditionForPassed                      */
/* Description   | Check similar condition at passed.                       */
/* Preconditions | none                                                     */
/* Parameters    | [in] SimilarConditionPtr :                               */
/* Return Value  | Dem_u08_InternalReturnType                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Similar_CheckConditionForPassed
(
    P2CONST( Dem_SimilarConditionValueType, AUTOMATIC, AUTOMATIC ) SimilarConditionPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) retJudgeSimilarCondition;
    VAR( Dem_SimilarConditionValueType, AUTOMATIC ) oldSimilarConditionValue[DEM_SIMILARTYPE_MAX_NUM];

    retVal = DEM_IRT_NG;

    Dem_Similar_GetConditionStoredListToTmp( &oldSimilarConditionValue[0] );/* [ARYCHK] DEM_SIMILARTYPE_MAX_NUM / 1 / 0 */

    retJudgeSimilarCondition = Dem_JudgeSimilarCondition( &oldSimilarConditionValue[0] ,SimilarConditionPtr );/* [ARYCHK] DEM_SIMILARTYPE_MAX_NUM / 1 / 0 */
    if( retJudgeSimilarCondition == (boolean)TRUE )
    {
        retVal = DEM_IRT_OK;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Similar_CheckConditionForFailed                      */
/* Description   | Check similar condition at failed.                       */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] SimilarConditionPtr :                               */
/* Return Value  | Dem_u08_InternalReturnType                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Similar_CheckConditionForFailed
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2CONST( Dem_SimilarConditionValueType, AUTOMATIC, AUTOMATIC ) SimilarConditionPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) retJudgeSimilarCondition;
    VAR( Dem_SimilarConditionValueType, AUTOMATIC ) oldSimilarConditionValue[DEM_SIMILARTYPE_MAX_NUM];
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) similarStrgIndex;

    retVal = DEM_IRT_NG;

    retCnvId    =   Dem_CfgInfoPm_CnvEventStrgIndexToSimilarStrgIndex( EventStrgIndex, &similarStrgIndex );     /* [GUD:RET:DEM_IRT_OK] similarStrgIndex */
    if ( retCnvId == DEM_IRT_OK )
    {
        /*  similarStrgIndex : value range check in Dem_CfgInfoPm_CnvEventStrgIndexToSimilarStrgIndex().        */
        if( Dem_SimilarClassRefTable[ similarStrgIndex ].DemUseSimilarCondToConfirmed == (boolean)TRUE )        /* [GUD]similarStrgIndex */
        {
            Dem_Similar_GetConditionStoredListToTmp( &oldSimilarConditionValue[0] );/* [ARYCHK] DEM_SIMILARTYPE_MAX_NUM / 1 / 0 */

            retJudgeSimilarCondition = Dem_JudgeSimilarCondition( &oldSimilarConditionValue[0] ,SimilarConditionPtr );/* [ARYCHK] DEM_SIMILARTYPE_MAX_NUM / 1 / 0 */
            if( retJudgeSimilarCondition == (boolean)TRUE )
            {
                retVal = DEM_IRT_OK;
            }
        }
        else
        {
            retVal = DEM_IRT_OK;
        }
    }

    return retVal;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/



#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
