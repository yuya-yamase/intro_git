/* Dem_Similar_EventeEntry_c(v5-3-0)                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Similar_EventeEntry/CODE                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Pm_Similar.h"
#include "../../../inc/Dem_Rc_SimilarMng.h"
#include "../../../inc/Dem_Rc_RecMngCmn.h"
#include "../../../inc/Dem_Rc_RecMngCmn_Table.h"
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

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* Saved temporary area of event memory entry                               */
/****************************************************************************/
VAR( Dem_TmpSimilarEventMemoryEntryType, DEM_VAR_NO_INIT ) Dem_TmpSimilarEventMemoryEntry;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_Similar_SaveEventMemoryEntryToTmp                    */
/* Description   | Saves an event memory entry by event index to            */
/*               |  temporary area.                                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Similar_SaveEventMemoryEntryToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) similarStrgIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;

    retCnvId    =   Dem_CfgInfoPm_CnvEventStrgIndexToSimilarStrgIndex( EventStrgIndex, &similarStrgIndex );
    if ( retCnvId == DEM_IRT_OK )
    {
        /*  similarStrgIndex : value range check in Dem_CfgInfoPm_CnvEventStrgIndexToSimilarStrgIndex().        */
        (void)Dem_SimilarMng_GetSimilarRecordList( similarStrgIndex, &Dem_TmpSimilarEventMemoryEntry.SimilarRecord ); /* no return check required */
    }
    return;
}

/****************************************************************************/
/* Function Name | Dem_Similar_UpdateEventMemoryEntryFromTmp                */
/* Description   | Update an event memory entry to temporary area.          */
/* Preconditions | Dem_TmpSimilarEventMemoryEntry.ResultOfComparingSimilar- */
/*               | Records must be set before the this function is called.  */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] ConsistencyIdUpdateFlg  :                           */
/*               | [in] ConsistencyId  :                                    */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Similar_UpdateEventMemoryEntryFromTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( boolean, AUTOMATIC ) ConsistencyIdUpdateFlg,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId
)
{
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) similarStrgIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;

    retCnvId    =   Dem_CfgInfoPm_CnvEventStrgIndexToSimilarStrgIndex( EventStrgIndex, &similarStrgIndex );
    if ( retCnvId == DEM_IRT_OK )
    {
        if( Dem_TmpSimilarEventMemoryEntry.ResultOfComparingSimilarRecords == DEM_IRT_NG)
        {
            /* Similar record has an update */
            if( ConsistencyIdUpdateFlg == (boolean)TRUE )
            {
                /* execute Dem_SimilarMng_SetConsistencyId().                                                      */
                /* Call Dem_Similar_SetConsistencyId() to avoid QAC indication of Dem_Similar_SetConsistencyId().  */
                Dem_Similar_SetConsistencyId( EventStrgIndex, ConsistencyId );
            }
            Dem_SimilarMng_SetSimilarRecordList( similarStrgIndex, &Dem_TmpSimilarEventMemoryEntry.SimilarRecord );
        }
        else
        {
            /* Similar record has no update */
            /* If the condition to update consistencyId is met, update only consistencyId*/
            if( ConsistencyIdUpdateFlg == (boolean)TRUE )
            {
                /* execute Dem_SimilarMng_SetConsistencyId().                                                      */
                /* Call Dem_Similar_SetConsistencyId() to avoid QAC indication of Dem_Similar_SetConsistencyId().  */
                Dem_Similar_SetConsistencyId( EventStrgIndex, ConsistencyId );
            }

            /* Exceedance counter is not included in the comparison(ResultOfComparingSimilarRecords), it also updates in the comparison NG */
            Dem_SimilarMng_SetExceedanceCounter( similarStrgIndex, Dem_TmpSimilarEventMemoryEntry.SimilarRecord.ExceedanceCounter );
        }
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dem_Similar_ClearSimilarRecord                           */
/* Description   | Clear the similar record.                                */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Similar_ClearSimilarRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) similarStrgIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;

    retCnvId    =   Dem_CfgInfoPm_CnvEventStrgIndexToSimilarStrgIndex( EventStrgIndex, &similarStrgIndex );
    if ( retCnvId == DEM_IRT_OK )
    {
        Dem_SimilarMng_ClearSimilarRecordList( similarStrgIndex );
    }
    return;
}


/****************************************************************************/
/* Function Name | Dem_Similar_SetConsistencyId                             */
/* Description   | set consistencyId                                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] ConsistencyId  :                                    */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Similar_SetConsistencyId
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId
)
{
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) similarStrgIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;

    /*  convert id.     */
    retCnvId    =   Dem_CfgInfoPm_CnvEventStrgIndexToSimilarStrgIndex( EventStrgIndex, &similarStrgIndex );

    if ( retCnvId == DEM_IRT_OK )
    {
        Dem_SimilarMng_SetConsistencyId( similarStrgIndex, ConsistencyId );
    }

    return;
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
/****************************************************************************/

/**** End of File ***********************************************************/
