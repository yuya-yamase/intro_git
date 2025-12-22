/* Dem_DataCtl_FilteredRecord_RtvlOn_c(v5-7-0)                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_FilteredRecord_RtvlOn/CODE                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../cfg/Dem_Misfire_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_DataAvl.h"
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_Pm_DataAvl.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_Pm_DTC.h"

#include "Dem_DataCtl_local.h"

#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )
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

static FUNC( Dem_u16_FFRecNumStoredIndexType, DEM_CODE ) Dem_Data_GetNextRecordNumberIndex
(
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) FFRecNumStoredIndex,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber
);

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_DuplicateCheckOfGetFilteredRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) FFRecNumStoredIndex,
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNum
);

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
/* Function Name | Dem_Data_GetFilteredRecordSub                            */
/* Description   | Gets the filtered freeze frame record.                   */
/* Preconditions |                                                          */
/* Parameters    | [in] FaultIndex :                                        */
/*               |        The index corresponding to the specified and nex- */
/*               |        t fault record.                                   */
/*               | [in] EventStrgIndex :                                    */
/*               |                                                          */
/*               | [in] DTCValue :                                          */
/*               |                                                          */
/*               | [in/out] FilteredRecordSearchInfoPtr :               */
/*               |        Pointer to Dem_FilteredRecordSearchInfo.          */
/*               | [out] DTCValuePtr :                                      */
/*               |        The DTC value retrieved.                          */
/*               | [out] RecordNumberPtr :                                  */
/*               |        The record number retrieved.                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Retrieving the filtered record was - */
/*               |        successful.                                       */
/*               |        DEM_IRT_NODATAAVAILABLE : Available data were n - */
/*               |        ot provided.                                      */
/*               |        DEM_IRT_NG : Retrieving the filtered record was - */
/*               |        failed.                                           */
/*               |        DEM_IRT_PENDING :                                 */
/*               |                                                          */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | new created.                                             */
/*   v5-7-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetFilteredRecordSub
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,    /* MISRA DEVIATION */
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    P2VAR( Dem_FilteredRecordSearchInfoType, AUTOMATIC, DEM_VAR_NO_INIT ) FilteredRecordSearchInfoPtr,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC ) RecordNumberPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) ffRecNumStoredIndex;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfDuplicateCheck;
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) tmpRecordNumberMaxNum;
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )   /*  [FuncSw]    */
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) maxMisfireCylinderNum;
#endif  /*  ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  */

    /* DTC value is valid. */
    ffRecNumStoredIndex = FilteredRecordSearchInfoPtr->FFRecNumStoredIndex;
    misfireCylinderNum = FilteredRecordSearchInfoPtr->MisfireCylinderNum;
    resultOfDuplicateCheck = Dem_Data_DuplicateCheckOfGetFilteredRecord( EventStrgIndex, DTCValue, ffRecNumStoredIndex, misfireCylinderNum );

    if ( resultOfDuplicateCheck == DEM_IRT_OK )
    {
        tmpRecordNumberMaxNum = Dem_TotalNumOfRecNumPerDTC;

        if ( ffRecNumStoredIndex < tmpRecordNumberMaxNum ) /* [GUD:if] ffRecNumStoredIndex */
        {
            if ( ffRecNumStoredIndex == (Dem_u16_FFRecNumStoredIndexType)0U )
            {
                Dem_Data_MakeTmpRecordNumberByDTC( EventStrgIndex, misfireCylinderNum );
            }
            if ( Dem_TmpRecordNumberByDTC[ffRecNumStoredIndex].RecordNumber != DEM_FFRECNUM_INVALID ) /* [GUD] ffRecNumStoredIndex */
            {
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )   /*  [FuncSw]    */
                if ( misfireCylinderNum != DEM_MISFIRE_CYL_NUM_INVALID )
                {
                    *DTCValuePtr = Dem_CfgInfoPm_GetUdsDTCByMisfireCylinderNumber( misfireCylinderNum );
                }
                else
#endif  /*  ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  */
                {
                    *DTCValuePtr = DTCValue;
                }
                *RecordNumberPtr = Dem_TmpRecordNumberByDTC[ffRecNumStoredIndex].RecordNumber;  /* [GUD] ffRecNumStoredIndex */
                ffRecNumStoredIndex = Dem_Data_GetNextRecordNumberIndex( ffRecNumStoredIndex, *RecordNumberPtr );
                retVal = DEM_IRT_OK;
            }
            else
            {
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )   /*  [FuncSw]    */
                if ( misfireCylinderNum != DEM_MISFIRE_CYL_NUM_INVALID )
                {
                    maxMisfireCylinderNum  =   Dem_MisfireCylinderNum;
                    misfireCylinderNum = misfireCylinderNum + (Dem_MisfireCylinderNumberType)1U;

                    if ( misfireCylinderNum < maxMisfireCylinderNum )
                    {
                        ffRecNumStoredIndex = (Dem_u16_FFRecNumStoredIndexType)0U;
                        retVal = DEM_IRT_PENDING;
                    }
                    else
                    {
                        retVal = DEM_IRT_NODATAAVAILABLE;
                    }
                }
                else
#endif  /*  ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  */
                {
                    retVal = DEM_IRT_NODATAAVAILABLE;
                }
            }
        }
        else
        {
            retVal = DEM_IRT_NODATAAVAILABLE;
        }
    }
    else
    {
        retVal = DEM_IRT_NODATAAVAILABLE;
    }

    FilteredRecordSearchInfoPtr->MisfireCylinderNum = misfireCylinderNum;
    FilteredRecordSearchInfoPtr->FFRecNumStoredIndex = ffRecNumStoredIndex;

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Data_GetNextRecordNumberIndex                        */
/* Description   | Return the next FFRecNumStoredIndex.                     */
/* Preconditions |                                                          */
/* Parameters    | [in] FFRecNumStoredIndex :                               */
/*               |        Search start index.                               */
/*               | [in] RecordNumber :                                      */
/*               |        The record number corresponding to the specified  */
/* Return Value  | Dem_u16_FFRecNumStoredIndexType                          */
/*               |        Next FFRecNumStoredIndex.                         */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | new created.                                             */
/****************************************************************************/
static FUNC( Dem_u16_FFRecNumStoredIndexType, DEM_CODE ) Dem_Data_GetNextRecordNumberIndex
(
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) FFRecNumStoredIndex,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber
)
{
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) nextRecordNumberIndex;
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) tmpRecordNumberMaxNum;
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) searchStartIndex;

    tmpRecordNumberMaxNum = Dem_TotalNumOfRecNumPerDTC;
    nextRecordNumberIndex = Dem_TotalNumOfRecNumPerDTC;

    for( searchStartIndex = FFRecNumStoredIndex; searchStartIndex < tmpRecordNumberMaxNum; searchStartIndex++ )     /* [GUD:for] searchStartIndex */
    {
        if( RecordNumber < Dem_TmpRecordNumberByDTC[searchStartIndex].RecordNumber )    /* [GUD] searchStartIndex */
        {
            nextRecordNumberIndex = searchStartIndex;
            break;
        }
    }

    return nextRecordNumberIndex;
}

/****************************************************************************/
/* Function Name | Dem_Data_DuplicateCheckOfGetFilteredRecord               */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex                                      */
/*               | [in] DTCValue                                            */
/*               | [in] FFRecNumStoredIndex                                 */
/*               | [in] MisfireCylinderNum                                  */
/* Return Value  | Dem_u08_InternalReturnType                               */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | new created.                                             */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_DuplicateCheckOfGetFilteredRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,            /* [PRMCHK:CALLER] */
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) FFRecNumStoredIndex,
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNum     /* MISRA DEVIATION */
)
{
    VAR( boolean, AUTOMATIC ) resultOfDuplicateCheck;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) /* [FuncSw] */
    VAR( boolean, AUTOMATIC ) misfireEventKind;
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) misfireDTCValue;
#endif /* DEM_MISFIRE_EVENT_CONFIGURED -STD_ON- */

    retVal = DEM_IRT_OK;

    if ( FFRecNumStoredIndex == (Dem_u16_FFRecNumStoredIndexType)0U )
    {
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) /* [FuncSw] */
        misfireEventKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );
        if ( misfireEventKind == (boolean)TRUE )
        {
            if ( MisfireCylinderNum == (Dem_MisfireCylinderNumberType)0U )
            {
                misfireDTCValue = Dem_CfgInfoPm_GetUdsDTCByMisfireCylinderNumber( MisfireCylinderNum );
                resultOfDuplicateCheck = Dem_CmbEvt_CheckOutputFilteredUdsDTC( EventStrgIndex, misfireDTCValue );
                if ( resultOfDuplicateCheck == (boolean)FALSE )
                {
                    retVal = DEM_IRT_NG;
                }
            }
        }
        else
#endif /* DEM_MISFIRE_EVENT_CONFIGURED -STD_ON- */
        {
            resultOfDuplicateCheck = Dem_CmbEvt_CheckOutputFilteredUdsDTC( EventStrgIndex, DTCValue );
            if ( resultOfDuplicateCheck == (boolean)FALSE )
            {
                retVal = DEM_IRT_NG;
            }
        }
    }

    return retVal;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /*  ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
