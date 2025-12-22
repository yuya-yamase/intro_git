/* Dem_DataCtl_GetTSFFD_local_c(v5-5-0)                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_GetTSFFD_local/CODE                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_Rc_DataMng.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_CmnLib_DataCtl_FFDOutputJudge.h"
#include "../../../inc/Dem_CmnLib_DataCtl_TSFFD.h"
#include "../../../inc/Dem_Utl.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "Dem_DataCtl_local.h"

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
/* Internal Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>


#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_GetTSFFRecord                                   */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |                                                          */
/*               | [in] TimeSeriesFreezeFrameRecordClassRefIndex :          */
/*               |                                                          */
/*               | [in] OffsetOfIndex :                                     */
/*               |                                                          */
/*               | [out] TimeSeriesFreezeFrameRecordPtr :                   */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetTSFFRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) TimeSeriesFreezeFrameRecordClassRefIndex,
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) OffsetOfIndex,
    P2VAR( Dem_FreezeFrameRecordMngType, AUTOMATIC, AUTOMATIC ) TimeSeriesFreezeFrameRecordPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFaultIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFaultRec;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetTSFFRec;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsffRecordClassNumPerDTCMaxNum;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListIndex;

    retVal = DEM_IRT_NG;
    tsffRecordClassNumPerDTCMaxNum = Dem_TSFFRecordClassNumPerDTCMaxNum;

    if( TimeSeriesFreezeFrameRecordClassRefIndex >= tsffRecordClassNumPerDTCMaxNum )            /* [GUD:if]TimeSeriesFreezeFrameRecordClassRefIndex */
    {
        /* No process */
    }
    else
    {
        resultOfGetFaultRec = DEM_IRT_NG;

        SchM_Enter_Dem_EventMemory();

        faultIndex = DEM_FAULTINDEX_INITIAL;

        resultOfGetFaultIndex = Dem_DataMngC_GetER_FaultIndex( EventStrgIndex, &faultIndex );               /* [GUD:RET:DEM_IRT_OK] EventStrgIndex */

        if( resultOfGetFaultIndex == DEM_IRT_OK )
        {
            if( faultIndex != DEM_FAULTINDEX_INITIAL )                                                                                              /* [GUD:if]faultIndex */
            {
                resultOfGetFaultRec = Dem_DataMngC_GetFR_TSFFListIndex( faultIndex, TimeSeriesFreezeFrameRecordClassRefIndex, &tsFFListIndex );     /* [GUD]faultIndex *//* [GUD]TimeSeriesFreezeFrameRecordClassRefIndex */
            }
            else
            {
                /* No process */
            }
        }
        else
        {
            /* No process */
        }
        if( resultOfGetFaultRec == DEM_IRT_OK )
        {
            resultOfGetTSFFRec = Dem_Data_GetTSFFRecordFromTSFFList( tsFFListIndex, OffsetOfIndex, TimeSeriesFreezeFrameRecordPtr );

            if( resultOfGetTSFFRec == DEM_IRT_OK )
            {
                retVal = DEM_IRT_OK;
            }
            else
            {
                /* No process */
            }
        }
        else
        {
            /* No process */
        }

        SchM_Exit_Dem_EventMemory();
    }

    return retVal;
}
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON ) */


#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_GetTSFFRecordFromTSFFList                       */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] TimeSeriesFreezeFrameRecordClassRefIndex :          */
/*               |                                                          */
/*               | [in] OffsetOfIndex :                                     */
/*               |                                                          */
/*               | [out] TimeSeriesFreezeFrameRecordPtr :                   */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetTSFFRecordFromTSFFList
(
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TimeSeriesFreezeFrameListIndex,
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) OffsetOfIndex,
    P2VAR( Dem_FreezeFrameRecordMngType, AUTOMATIC, AUTOMATIC ) TimeSeriesFreezeFrameRecordPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetTSFFRec;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) tsFFRecIndex;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsffTotalDTCNum;

    retVal = DEM_IRT_NG;
    tsffTotalDTCNum = Dem_TSFFTotalDTCNum;
    failRecordNum = Dem_FailRecordNum;

    if( TimeSeriesFreezeFrameListIndex < tsffTotalDTCNum )                                                                      /* [GUD:if]TimeSeriesFreezeFrameListIndex */
    {
        if( Dem_TimeSeriesFreezeFrameListRecordList[TimeSeriesFreezeFrameListIndex].FaultIndex < failRecordNum )                /* [GUD]TimeSeriesFreezeFrameListIndex */
        {
            tsFFRecIndex = ( Dem_TimeSeriesFreezeFrameTable[TimeSeriesFreezeFrameListIndex].DemStartIndex + OffsetOfIndex );    /* [GUD]TimeSeriesFreezeFrameListIndex */

            if( tsFFRecIndex <= Dem_TimeSeriesFreezeFrameTable[TimeSeriesFreezeFrameListIndex].DemEndIndex )                    /* [GUD]TimeSeriesFreezeFrameListIndex *//* [GUD:if]tsFFRecIndex */
            {
                resultOfGetTSFFRec = Dem_DataMngC_GetTimeSeriesFreezeFrameRecord( tsFFRecIndex, TimeSeriesFreezeFrameRecordPtr );

                if( resultOfGetTSFFRec == DEM_IRT_OK )
                {
                    retVal = DEM_IRT_OK;
                }
                else
                {
                    /* No process */
                }
            }
            else
            {
                /* No process */
            }
        }
        else
        {
            /* No process */
        }
    }
    else
    {
        /* No process */
    }


    return retVal;
}
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON ) */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v3-0-0         :2019-07-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
