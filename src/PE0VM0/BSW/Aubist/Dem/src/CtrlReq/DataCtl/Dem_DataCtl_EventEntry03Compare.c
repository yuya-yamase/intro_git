/* Dem_DataCtl_EventEntry03Compare_c(v5-5-0)                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_EventEntry03Compare/CODE                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_Pm_Similar.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Rc_DataMng.h"
#include "../../../inc/Dem_Utl.h"
#include "Dem_DataCtl_EventEntry_local.h"

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

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_Data_CompareEventMemoryEntryToTmp                    */
/* Description   | Compares the event memory entry to temporary area corre- */
/*               | sponding to the event index of temporary area.           */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_CompareEventMemoryEntryToTmp
( void )
{
    /* Compares the event memory entry corresponding to the saved event index to the temporary area. */

    Dem_Data_CompareEventRecordToTmp();

    Dem_Data_CompareFaultRecordToTmp();

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    Dem_Misfire_CompareMisfireInfoToTmp( Dem_TmpEventMemoryEntry.EventStrgIndex );
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    Dem_Similar_CompareSimilarInfoToTmp( Dem_TmpEventMemoryEntry.EventStrgIndex );
#endif  /*   ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )         */
    return ;
}


/****************************************************************************/
/* Function Name | Dem_Data_CompareEventRecordToTmp                         */
/* Description   | Compares the event record corresponding to the temoprary */
/*               | event meomry entry.                                      */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_CompareEventRecordToTmp
( void )
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    if( Dem_TmpEventMemoryEntry.EventStrgIndex < eventStorageNum )
    {
        /* compare with record data. */
        Dem_TmpEventMemoryEntry.ResultOfComparingEventRecords = Dem_DataMngC_CompareEventRecord( Dem_TmpEventMemoryEntry.EventStrgIndex, &Dem_TmpEventMemoryEntry.EventRecord );    /* [GUD]&Dem_TmpEventMemoryEntry.EventRecord */
    }
    else
    {
        Dem_TmpEventMemoryEntry.ResultOfComparingEventRecords = DEM_IRT_OK;
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_Data_CompareFaultRecordToTmp                         */
/* Description   | Compares the fault record corresponding to the temoprary */
/*               | event meomry entry.                                      */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_CompareFaultRecordToTmp
( void )
{
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;

    failRecordNum = Dem_FailRecordNum;

    if( Dem_TmpEventMemoryEntry.EventRecord.FaultIndex < failRecordNum )
    {
        /* compare with record data. */
        Dem_TmpEventMemoryEntry.ResultOfComparingFaultRecords = Dem_DataMngC_CompareFaultRecord( Dem_TmpEventMemoryEntry.EventRecord.FaultIndex, &Dem_TmpEventMemoryEntry.FaultRecord );    /* [GUD]&Dem_TmpEventMemoryEntry.FaultRecord */
    }
    else
    {
        Dem_TmpEventMemoryEntry.ResultOfComparingFaultRecords = DEM_IRT_OK;
    }

    return;
}


#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_SetResultOfCmpObdFFRecordToTmp                  */
/* Description   | Set the comparison result of OBD freeze frame record in- */
/*               | temoprary                                                */
/*               |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] ObdFreezeFrameRecordIndex :                         */
/*               |                                                          */
/*               | [in] Result:                                             */
/*               |        DEM_IRT_OK                                        */
/*               |        DEM_IRT_NG                                        */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_SetResultOfCmpObdFFRecordToTmp
(
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) ObdFreezeFrameRecordIndex,        /* [PRMCHK:CALLER] */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) Result
)
{
    Dem_TmpEventMemoryEntry.ResultOfComparingObdFFRecords[ObdFreezeFrameRecordIndex] = Result;  /* [GUDCHK:CALLER]ObdFreezeFrameRecordIndex */

    return;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */


/****************************************************************************/
/* Function Name | Dem_Data_SetResultOfCmpFFRecordToTmp                     */
/* Description   | Set the comparison result of freeze frame record in-     */
/*               | temoprary                                                */
/*               |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] FreezeFrameRecordIndex :                            */
/*               |                                                          */
/*               | [in] Result:                                             */
/*               |        DEM_IRT_OK                                        */
/*               |        DEM_IRT_NG                                        */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_SetResultOfCmpFFRecordToTmp
(
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordIndex,       /* [PRMCHK:CALLER] */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) Result
)
{
    Dem_TmpEventMemoryEntry.ResultOfComparingFFRecords[FreezeFrameRecordIndex] = Result;        /* [GUDCHK:CALLER]FreezeFrameRecordIndex */

    return;
}


/****************************************************************************/
/* Function Name | Dem_Data_SetConsistencyIdUpdateFlg                       */
/* Description   | check whether consistencyID is update or not and set con-*/
/*               | sistencyID flag.                                         */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_SetConsistencyIdUpdateFlg
( void )
{

    VAR( boolean, AUTOMATIC ) isSetConsistencyId;
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) consistencyId;
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) consistencyIdOfEvent;
#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON ) /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) isSpecificEvent;
#endif  /* ( DEM_SPECIFIC_EVENT_SUPPORT == STD_OFF )  */
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfCmpRecordMisfire;
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )   */
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfCmpRecordSimilar;
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )   */

    if( Dem_TmpEventMemoryEntry.EventRecord.FaultIndex != DEM_FAULTINDEX_INITIAL )
    {
        isSetConsistencyId = (boolean)TRUE;

        if( Dem_TmpEventMemoryEntry.ResultOfComparingFaultRecords == DEM_IRT_OK )
        {
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
            resultOfCmpRecordMisfire = Dem_Misfire_GetCompareResult( Dem_TmpEventMemoryEntry.EventStrgIndex );
            if( resultOfCmpRecordMisfire == DEM_IRT_OK )
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )   */
            {
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                resultOfCmpRecordSimilar = Dem_Similar_GetCompareResult( Dem_TmpEventMemoryEntry.EventStrgIndex );
                if( resultOfCmpRecordSimilar == DEM_IRT_OK )
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )   */
                {
                    isSetConsistencyId = (boolean)FALSE;
                }
            }
        }

        if( isSetConsistencyId == (boolean)TRUE )
        {
            Dem_TmpEventMemoryEntry.ConsistencyIdUpdatedFlg = (boolean)TRUE;

            (void)Dem_DataMng_GetFaultRecordConsistencyId( Dem_TmpEventMemoryEntry.EventRecord.FaultIndex, &consistencyId ); /* no return check required */

            /* decrement consistency ID*/
            consistencyId = Dem_UtlCid_CalcConsistencyId( consistencyId );

            Dem_DataMng_GetEventRecordConsistencyId( Dem_TmpEventMemoryEntry.EventStrgIndex, &consistencyIdOfEvent );

            if( consistencyId == consistencyIdOfEvent )
            {
                /* decrement consistency ID*/
                consistencyId = Dem_UtlCid_CalcConsistencyId( consistencyId );
            }

            Dem_TmpEventMemoryEntry.ConsistencyId = consistencyId;
        }
    }
#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON ) /*  [FuncSw]    */
    else
    {
        isSetConsistencyId = (boolean)TRUE;
        isSpecificEvent =   Dem_CfgInfoPm_CheckEventKindOfSpecific_InEvtStrgGrp( Dem_TmpEventMemoryEntry.EventStrgIndex );

        if ( isSpecificEvent == (boolean)TRUE )
        {
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
            resultOfCmpRecordMisfire = Dem_Misfire_GetCompareResult( Dem_TmpEventMemoryEntry.EventStrgIndex );
            if( resultOfCmpRecordMisfire == DEM_IRT_OK )
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )   */
            {
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                resultOfCmpRecordSimilar = Dem_Similar_GetCompareResult( Dem_TmpEventMemoryEntry.EventStrgIndex );
                if( resultOfCmpRecordSimilar == DEM_IRT_OK )
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )   */
                {
                    /* No update connsistencyId, if event,misfire and similar record is not change. */
                    isSetConsistencyId = (boolean)FALSE;
                }
            }
        }
        else
        {
            /* No update consistencyId, if event is Similar or Misfire. */
            isSetConsistencyId = (boolean)FALSE;
        }

        if( isSetConsistencyId == (boolean)TRUE )
        {
            Dem_TmpEventMemoryEntry.ConsistencyIdUpdatedFlg = (boolean)TRUE;

            /* Gives the consistency ID of the Event record to each record, if Fault records are not have. */
            Dem_DataMng_GetEventRecordConsistencyId( Dem_TmpEventMemoryEntry.EventStrgIndex, &consistencyId );

            /* decrement consistency ID*/
            consistencyId = Dem_UtlCid_CalcConsistencyId( consistencyId );

            Dem_TmpEventMemoryEntry.ConsistencyId = consistencyId;
        }
    }
#endif  /* ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )  */

    return;
}


#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_GetConsistencyIdUpdateFlg                       */
/* Description   | Get the flag whether to update the consistency id.       */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_GetConsistencyIdUpdateFlg
(
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ConsistencyIdUpdFlgPtr,
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) ConsistencyIdPtr
)
{
    *ConsistencyIdUpdFlgPtr = Dem_TmpEventMemoryEntry.ConsistencyIdUpdatedFlg;
    *ConsistencyIdPtr =  Dem_TmpEventMemoryEntry.ConsistencyId;

    return;
}
#endif  /* ( DEM_SPECIFIC_EVENT_SUPPORT == STD_OFF )  */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-07-29                                              */
/*  v4-0-0         :2020-03-19                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
