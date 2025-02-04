/* Dem_DataMng_RecDt_TSFFList_c(v5-5-0)                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Dem_DataMng_RecDt_FFList_c/CODE                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_DataCtl_TSFFD.h"
#include "../../../inc/Dem_Rc_DataMng.h"
#include "../../../inc/Dem_Utl.h"
#include "../../../inc/Dem_Rc_RecMngCmn.h"
#include "../../../inc/Dem_Rc_RecMngCmn_Table.h"
#include "Dem_DataMng_local.h"


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
/* Function Name | Dem_DataMngC_GetFR_TSFFListIndex                         */
/* Description   | Get FreezeFrame index.                                   */
/* Preconditions |                                                          */
/* Parameters    | [in] FaultIndex :                                        */
/*               | [in] TimeSeriesFreezeFrameRecordClassRefIndex :          */
/*               |       index of Dem_FaultRecordList[FaultIndex].TimeSeriesFreezeFrameListIndex[].  */
/*               | [out] TSFFListIndexPtr :                                 */
/*               |       TSFF List index.                                   */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetFR_TSFFListIndex
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) TimeSeriesFreezeFrameRecordClassRefIndex,
    P2VAR( Dem_u16_TSFFListIndexType, AUTOMATIC, AUTOMATIC ) TSFFListIndexPtr
)
{
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsfflRecordClassNumPerDTCMaxNum;

    failRecordNum = Dem_FailRecordNum;
    tsfflRecordClassNumPerDTCMaxNum = Dem_TSFFRecordClassNumPerDTCMaxNum;

    retVal = DEM_IRT_NG;
    if( FaultIndex < failRecordNum )                                                        /* [GUD:if]FaultIndex */
    {
        if ( TimeSeriesFreezeFrameRecordClassRefIndex < tsfflRecordClassNumPerDTCMaxNum )   /* [GUD:if]TimeSeriesFreezeFrameRecordClassRefIndex */
        {
            *TSFFListIndexPtr = Dem_FaultRecordList[FaultIndex].TimeSeriesFreezeFrameListIndex[TimeSeriesFreezeFrameRecordClassRefIndex];   /* [GUD]FaultIndex *//* [GUD]TimeSeriesFreezeFrameRecordClassRefIndex */
            retVal = DEM_IRT_OK;
        }
    }
    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_DataMng_InitTSFFListRecordData                       */
/* Description   | Initializes the specified freeze frame list record.      */
/* Preconditions |                                                          */
/* Parameters    | [out] FaultRecordPtr :                                   */
/*               |           &Dem_TmpEventMemoryEntry.FreezeFrameListRecord */
/*               |           &Dem_TmpDisabledRecord.FreezeFrameListRecord   */
/*               |           AUTOMATIC                                      */
/*               |        The specified freeze frame list record to initia- */
/*               |        lize.                                             */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMng_InitTSFFListRecordData
(
    P2VAR( Dem_u16_TSFFListIndexType, AUTOMATIC, DEM_VAR_NO_INIT ) TimeSeriesFreezeFrameListIndexArrayPtr
)
{
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsFFListIndex;
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsffRecordClassNumPerDTCMaxNum;

    tsffRecordClassNumPerDTCMaxNum = Dem_TSFFRecordClassNumPerDTCMaxNum;

    /* The time-series freeze frame record list index. */
    for( tsFFListIndex = (Dem_u08_TSFFListPerDTCIndexType)0U ; tsFFListIndex < tsffRecordClassNumPerDTCMaxNum; tsFFListIndex++ )    /* [GUD:for]tsFFListIndex */
    {
        TimeSeriesFreezeFrameListIndexArrayPtr[tsFFListIndex] = DEM_INVALID_VACANT_TSFFLIST_INDEX;                                  /* [GUD]tsFFListIndex */
    }
    return ;
}


/****************************************************************************/
/* Function Name | Dem_DataMng_InitSpecificTSFFListRecordData               */
/* Description   | Initializes specified RTSFFListIndex of the fault record */
/* Preconditions |                                                          */
/* Parameters    | [in]  FaultIndex :                                       */
/*               |        The fault index.                                  */
/* Parameters    | [in]  TSFFListIndex :                                    */
/*               |        The specified TimeSeriesFreezeFrameListIndex      */
/*               |        of fault record to initialize.                    */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMng_InitSpecificTSFFListRecordData
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,                    /* [PRMCHK:CALLER] */
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) TSFFListIndex         /* [PRMCHK:CALLER] */
)
{
    Dem_FaultRecordList[FaultIndex].TimeSeriesFreezeFrameListIndex[TSFFListIndex] = DEM_INVALID_VACANT_TSFFLIST_INDEX;  /* [GUDCHK:CALLER]FaultIndex *//* [GUDCHK:CALLER]TSFFListIndex */

    return;
}


/****************************************************************************/
/* Function Name | Dem_DataMng_InitTSFFListRecord                           */
/* Description   | Initializes the specified freeze frame list record.      */
/* Preconditions |                                                          */
/* Parameters    | [in] FaultIndex :                                        */
/*               |        The FreezeFrameList index corresponding to the s- */
/*               |        pecific FreezeFrameList record.                   */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMng_InitTSFFListRecord
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex                     /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsFFListIndex;
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsffRecordClassNumPerDTCMaxNum;

    tsffRecordClassNumPerDTCMaxNum = Dem_TSFFRecordClassNumPerDTCMaxNum;

    /* The time-series freeze frame record list index. */
    for( tsFFListIndex = (Dem_u08_TSFFListPerDTCIndexType)0U ; tsFFListIndex < tsffRecordClassNumPerDTCMaxNum; tsFFListIndex++ )        /* [GUD:for]tsFFListIndex */
    {
        Dem_FaultRecordList[FaultIndex].TimeSeriesFreezeFrameListIndex[tsFFListIndex] = DEM_INVALID_VACANT_TSFFLIST_INDEX;              /* [GUDCHK:CALLER]FaultIndex *//* [GUD]tsFFListIndex */
    }
    return ;
}

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataMngC_InitTimeSeriesFreezeFrameListIndexFFROverwritten */
/* Description   | Initializes the specified freeze frame list record.      */
/* Preconditions |                                                          */
/* Parameters    | [in] FaultIndex :                                        */
/*               |        The FreezeFrameList index corresponding to the s- */
/*               |        pecific FreezeFrameList record.                   */
/*               | [in] TimeSeriesFreezeFrameListIndex :                    */
/*               |        The time freeze frame record list index which to- */
/*               |        be overwritten of the fault record corresponding  */
/*               |        to the specified FaultIndex.                      */
/*               | [out] EventStrgIndexPtr :                                */
/*               |        The Event record index corresponding to the       */
/*               |        specified FaultIndex.                             */
/*               | [out] ConsistencyIdPtr :                                 */
/*               |        Updated ConsistencyID                             */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMngC_InitTimeSeriesFreezeFrameListIndexFFROverwritten
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TimeSeriesFreezeFrameListIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr,
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) ConsistencyIdPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsffrIndex;
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsffRecordClassNumPerDTCMaxNum;
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) consistencyId;

    failRecordNum = Dem_FailRecordNum;
    tsffRecordClassNumPerDTCMaxNum = Dem_TSFFRecordClassNumPerDTCMaxNum;

    if( FaultIndex < failRecordNum )                                                        /* [GUD:if]FaultIndex */
    {
        for( tsffrIndex = (Dem_u08_TSFFListPerDTCIndexType)0U; tsffrIndex < tsffRecordClassNumPerDTCMaxNum; tsffrIndex++ )          /* [GUD:for]tsffrIndex */
        {
            if( TimeSeriesFreezeFrameListIndex == Dem_FaultRecordList[FaultIndex].TimeSeriesFreezeFrameListIndex[tsffrIndex] )      /* [GUD]FaultIndex *//* [GUD]tsffrIndex */
            {
                Dem_FaultRecordList[FaultIndex].TimeSeriesFreezeFrameListIndex[tsffrIndex] = DEM_INVALID_VACANT_TSFFLIST_INDEX;     /* [GUD]FaultIndex *//* [GUD]tsffrIndex */
                Dem_DataMng_UpdateFaultRecordConsistencyId_Displacement( FaultIndex, &consistencyId );                              /* [GUD]FaultIndex */

                eventStrgIndex = Dem_FaultRecordList[FaultIndex].EventStrgIndex;                                                    /* [GUD]FaultIndex */
                Dem_DataMng_SetEventRecordConsistencyId( eventStrgIndex, consistencyId );

                *EventStrgIndexPtr = eventStrgIndex;
                *ConsistencyIdPtr  = consistencyId;

                break;
            }
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_DataMngC_InitTimeSeriesFreezeFrameListIndexRemoveNonObdFreeze */
/* Description   | Initializes the specified freeze frame list record.      */
/* Preconditions |                                                          */
/* Parameters    | [in] FaultIndex :                                        */
/*               |        The FreezeFrameList index corresponding to the s- */
/*               |        pecific FreezeFrameList record.                   */
/* Return Value  | boolean                                                  */
/*               |    TRUE : TSFF exist                                     */
/*               |   FALSE : TSFF doesn't exist                             */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_DataMngC_InitTimeSeriesFreezeFrameListIndexRemoveNonObdFreeze
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex
)
{
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsffrIndex;
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsffRecordClassNumPerDTCMaxNum;
    VAR( boolean, AUTOMATIC ) retVal;

    failRecordNum = Dem_FailRecordNum;
    tsffRecordClassNumPerDTCMaxNum = Dem_TSFFRecordClassNumPerDTCMaxNum;
    retVal = (boolean)FALSE;

    if( FaultIndex < failRecordNum )                                                        /* [GUD:if]FaultIndex */
    {
        for( tsffrIndex = (Dem_u08_TSFFListPerDTCIndexType)0U; tsffrIndex < tsffRecordClassNumPerDTCMaxNum; tsffrIndex++ )          /* [GUD:for]tsffrIndex */
        {
            if ( Dem_FaultRecordList[FaultIndex].TimeSeriesFreezeFrameListIndex[tsffrIndex] != DEM_INVALID_VACANT_TSFFLIST_INDEX )  /* [GUD]FaultIndex *//* [GUD]tsffrIndex */
            {
                Dem_FaultRecordList[FaultIndex].TimeSeriesFreezeFrameListIndex[tsffrIndex] = DEM_INVALID_VACANT_TSFFLIST_INDEX;     /* [GUD]FaultIndex *//* [GUD]tsffrIndex */
                retVal = (boolean)TRUE;
            }
        }
    }

    return retVal;
}



#endif /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */

/****************************************************************************/
/* Function Name | Dem_DataMngC_GetFreezeFrameListRecord                    */
/* Description   | Get TSFF List record data.                               */
/* Preconditions | The specified FreezeFrameList index be within the range  */
/*               |  of the FreezeFrameList record list.                     */
/* Parameters    | [in] FaultIndex :                                        */
/*               |        The FreezeFrameList index corresponding to the s- */
/*               |        pecific FreezeFrameList record.                   */
/*               | [out] TimeSeriesFreezeFrameListIndexArrayPtr :           */
/*               |        The pointer of the FreezeFrameList record corres- */
/*               |        ponding to the specified FreezeFrameList index.   */
/*               |          &Dem_TmpDisabledRecord.FreezeFrameListRecord    */
/*               |          &Dem_TmpEventMemoryEntry.FreezeFrameListRecord  */
/*               |          AUTOMATIC                                       */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMng_GetTSFFListRecord_Ctl
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,                    /* [PRMCHK:CALLER] */
    P2VAR( Dem_u16_TSFFListIndexType, AUTOMATIC, DEM_VAR_NO_INIT ) TimeSeriesFreezeFrameListIndexArrayPtr
)
{
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsfflCnt;
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsfflRecordClassNumPerDTCMaxNum;

    tsfflRecordClassNumPerDTCMaxNum = Dem_TSFFRecordClassNumPerDTCMaxNum;

    for( tsfflCnt = (Dem_u08_TSFFListPerDTCIndexType)0U; tsfflCnt < tsfflRecordClassNumPerDTCMaxNum; tsfflCnt++ )                       /* [GUD:for]tsfflCnt */
    {
        TimeSeriesFreezeFrameListIndexArrayPtr[tsfflCnt] = Dem_FaultRecordList[FaultIndex].TimeSeriesFreezeFrameListIndex[tsfflCnt];    /* [GUD]tsffrIndex *//* [GUDCHK:CALLER]FaultIndex */
    }
    return ;
}


/****************************************************************************/
/* Function Name | Dem_DataMng_SetTSFFListRecord_Ctl                        */
/* Description   | Set TSFF List record data.                               */
/* Preconditions | The specified FreezeFrameList index be within the range  */
/*               |  of the FreezeFrameList record list.                     */
/* Parameters    | [in] FaultIndex :                                        */
/*               |        The FreezeFrameList index corresponding to the s- */
/*               |        pecific FreezeFrameList record.                   */
/*               | [out] SrcFaultRecordPtr :                                */
/*               |        The pointer of the FreezeFrameList record corres- */
/*               |        ponding to the specified FreezeFrameList index.   */
/*               |        (for Dem_DataCtl subunit)                         */
/*               |           &Dem_TmpEventMemoryEntry.FaultRecord           */
/*               |           AUTOMATIC                                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMng_SetTSFFListRecord_Ctl
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,                    /* [PRMCHK:CALLER] */
    P2CONST( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) SrcFaultRecordPtr
)
{
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsfflCnt;
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsfflRecordClassNumPerDTCMaxNum;

    tsfflRecordClassNumPerDTCMaxNum = Dem_TSFFRecordClassNumPerDTCMaxNum;

    for( tsfflCnt = (Dem_u08_TSFFListPerDTCIndexType)0U; tsfflCnt < tsfflRecordClassNumPerDTCMaxNum; tsfflCnt++ )                                   /* [GUD:for]tsfflCnt */
    {
        Dem_FaultRecordList[FaultIndex].TimeSeriesFreezeFrameListIndex[tsfflCnt] = SrcFaultRecordPtr->TimeSeriesFreezeFrameListIndex[tsfflCnt];     /* [GUDCHK:CALLER]FaultIndex *//* [GUD]tsfflCnt */
    }
    return ;
}


/****************************************************************************/
/* Function Name | Dem_Data_CompareFreezeFrameListRecord                    */
/* Description   | compare data.                                            */
/* Preconditions |                                                          */
/* Parameters    | [in] FaultIndex :                                        */
/*               | [in] CheckFaultRecordPtr :                               */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK  : same.                               */
/*               |        DEM_IRT_NG  : different.                          */
/*               |                                                          */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMng_CmpWithTSFFListRecord
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,                    /* [PRMCHK:CALLER] */
    P2CONST( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) CheckFaultRecordPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) indexOfTSFFList;
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsffRecordClassNumPerDTCMaxNum;
    P2VAR( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) faultRecordPtr;

    retVal = DEM_IRT_OK;
    faultRecordPtr = &Dem_FaultRecordList[FaultIndex];      /* [GUDCHK:CALLER]FaultIndex */

    tsffRecordClassNumPerDTCMaxNum = Dem_TSFFRecordClassNumPerDTCMaxNum;
    for( indexOfTSFFList = (Dem_u08_TSFFListPerDTCIndexType)0U ; indexOfTSFFList < tsffRecordClassNumPerDTCMaxNum; indexOfTSFFList++ )                  /* [GUD:for]indexOfTSFFList */
    {
        if( faultRecordPtr->TimeSeriesFreezeFrameListIndex[indexOfTSFFList] != CheckFaultRecordPtr->TimeSeriesFreezeFrameListIndex[indexOfTSFFList] )   /* [GUD]indexOfTSFFList */
        {
            break;
        }
        else
        {
            /* No Process */
        }
    }
    if( indexOfTSFFList < tsffRecordClassNumPerDTCMaxNum )
    {
        /* different. */
        retVal = DEM_IRT_NG;
    }
    else
    {
        /* No Process */
    }
    return retVal;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif  /* (DEM_TSFF_PM_SUPPORT    STD_ON) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
