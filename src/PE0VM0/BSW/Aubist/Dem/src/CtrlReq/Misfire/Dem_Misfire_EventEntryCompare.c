/* Dem_MisfireEventEntryCompare_c(v5-5-0)                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Misfire_EventEntryCompare/CODE                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_Rc_MisfireMng.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "Dem_Misfire_EventEntry_local.h"



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
static FUNC( void, DEM_CODE ) Dem_Misfire_CompareMisfireRecordToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex
);
static FUNC( void, DEM_CODE ) Dem_Misfire_CompareMisfireComRecordToTmp
( void );
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
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>


/****************************************************************************/
/* Function Name | Dem_Misfire_CompareMisfireInfoToTmp                      */
/* Description   | compare Misfire data.                                    */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event ID for retrieving.                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_CompareMisfireInfoToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;

    retCnvId = Dem_CfgInfoPm_CnvEventStrgIndexToMisfireStrgIndex( EventStrgIndex, &misfireIndex );  /* [GUD:RET:DEM_IRT_OK] misfireIndex */

    if( retCnvId == DEM_IRT_OK )
    {
        Dem_Misfire_CompareMisfireRecordToTmp( EventStrgIndex, misfireIndex );  /* [GUD]misfireIndex */
        Dem_Misfire_CompareMisfireComRecordToTmp();
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_Misfire_InitCompareResultMisfireRecord               */
/* Description   | initialize compared result of Misifire record.           */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_InitCompareResultMisfireRecord
( void )
{
    Dem_TmpMisfireEventMemoryEntry.ResultOfComparingMisfireRecords = DEM_IRT_OK;
    Dem_TmpMisfireEventMemoryEntry.ResultOfComparingPairMisfireRecords = DEM_IRT_OK;

    return;
}


/****************************************************************************/
/* Function Name | Dem_Misfire_InitCompareResultMisfireComRecord            */
/* Description   | initialize compared result of MisifireCom record.        */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_InitCompareResultMisfireComRecord
( void )
{
    Dem_TmpMisfireEventMemoryEntry.ResultOfComparingMisfireComRecords = DEM_IRT_OK;

    return;
}


/****************************************************************************/
/* Function Name | Dem_Misfire_GetCompareResult                             */
/* Description   | get compared result of Misfire record.                   */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event ID for retrieving.                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Misfire_GetCompareResult
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfCompare;
    VAR( Dem_EventKindType, AUTOMATIC ) eventKind;

    resultOfCompare = DEM_IRT_OK;

    eventKind = Dem_CfgInfoPm_GetEventKindOfSpecific_InEvtStrgGrp( EventStrgIndex );

    if(( eventKind & DEM_EVTKIND_TYPE_MISFIRE_EVENT ) == DEM_EVTKIND_TYPE_MISFIRE_EVENT )
    {
        if( Dem_TmpMisfireEventMemoryEntry.ResultOfComparingMisfireRecords != DEM_IRT_OK )
        {
            resultOfCompare = DEM_IRT_NG;
        }
        else
        {
            if( Dem_TmpMisfireEventMemoryEntry.ResultOfComparingMisfireComRecords != DEM_IRT_OK )
            {
                resultOfCompare = DEM_IRT_NG;
            }
        }
    }

    return resultOfCompare;
}


/****************************************************************************/
/* Function Name | Dem_Misfire_CompareMisfireRecordToTmp                    */
/* Description   | Compares the misfire record corresponding to the tempora-*/
/*               | ry event meomry entry.                                   */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Misfire_CompareMisfireRecordToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex     /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) misfirePairEventStrgIndex;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) pairMisfireIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultGetMisfirePairEvent;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;

    /* compare with target misfire event record data. */
    Dem_TmpMisfireEventMemoryEntry.ResultOfComparingMisfireRecords = Dem_MisfireMng_CompareMisfireRecord( MisfireIndex, &Dem_TmpMisfireEventMemoryEntry.MisfireRecord[MisfireIndex] );  /* [GUDCHK:CALLER]MisfireIndex */

    resultGetMisfirePairEvent= Dem_CfgInfoPm_GetMisfirePairEventStrgIndexByStrgIndex( EventStrgIndex, &misfirePairEventStrgIndex );

    if( resultGetMisfirePairEvent == DEM_IRT_OK )
    {
        retCnvId    =   Dem_CfgInfoPm_CnvEventStrgIndexToMisfireStrgIndex( misfirePairEventStrgIndex, &pairMisfireIndex );  /* [GUD:RET:DEM_IRT_OK] pairMisfireIndex */

        if( retCnvId == DEM_IRT_OK )
        {
            /* compare with pais misfire record data. */
            Dem_TmpMisfireEventMemoryEntry.ResultOfComparingPairMisfireRecords = Dem_MisfireMng_CompareMisfireRecord( pairMisfireIndex, &Dem_TmpMisfireEventMemoryEntry.MisfireRecord[pairMisfireIndex] );  /* [GUD]pairMisfireIndex */
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_Misfire_CompareMisfireComRecordToTmp                 */
/* Description   | Compares the misfire record corresponding to the tempora-*/
/*               | ry event meomry entry.                                   */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Misfire_CompareMisfireComRecordToTmp
( void )
{
    /* compare with record data. */
    Dem_TmpMisfireEventMemoryEntry.ResultOfComparingMisfireComRecords = Dem_MisfireMng_CompareMisfireComRecord( &Dem_TmpMisfireEventMemoryEntry.MisfireComRecord );

    return;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
