/* Dem_DataCtl_InfoFFD_Sort_c(v5-7-0)                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Dem_DataCtl_InfoFFD_Sort/CODE                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_CmnLib_DataCtl.h"

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

static FUNC( void, DEM_CODE ) Dem_DataCtl_DownHeapSaveRecordNumber
(
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) IndexOfRoot,
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) LastIndexOfList,
    P2VAR( Dem_TmpRecordNumberByDTCType, AUTOMATIC, DEM_VAR_NO_INIT ) DataPtr
);

static FUNC( void, DEM_CODE ) Dem_DataCtl_SwapSaveRecordNumber
(
    P2VAR( Dem_TmpRecordNumberByDTCType, AUTOMATIC, DEM_VAR_NO_INIT ) OriginDataPtr,
    P2VAR( Dem_TmpRecordNumberByDTCType, AUTOMATIC, DEM_VAR_NO_INIT ) DestDataPtr
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
/* Function Name | Dem_Data_SortSaveRecordNumber                            */
/* Description   | Stored RecordNumber sort processing.                     */
/* Preconditions |                                                          */
/* Parameters    | [in] NumberOfSaveRecord :                                */
/*               | [in] DataPtr :                                           */
/*               |                  &Dem_TmpRecordNumberByDTC[x]            */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_SortSaveRecordNumber
(
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) NumberOfSaveRecord,
    P2VAR( Dem_TmpRecordNumberByDTCType, AUTOMATIC, DEM_VAR_NO_INIT ) DataPtr
)
{
    /* Variable declaration */
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) lastIndexOfList;
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) indexOfLastRootNode;
    VAR( Dem_s32_FFRecNumStoredIndexType, AUTOMATIC ) rootNodeIndex;

    if( NumberOfSaveRecord > (Dem_u16_FFRecNumStoredIndexType)1U )
    {
        lastIndexOfList = NumberOfSaveRecord - (Dem_u16_FFRecNumStoredIndexType)1U;
        indexOfLastRootNode = (Dem_u16_FFRecNumStoredIndexType)( lastIndexOfList - (Dem_u16_FFRecNumStoredIndexType)1U ) >> (Dem_u16_FFRecNumStoredIndexType)1U;

        /* Makes heap */
        for( rootNodeIndex = (Dem_s32_FFRecNumStoredIndexType)indexOfLastRootNode; rootNodeIndex >= (Dem_s32_FFRecNumStoredIndexType)0; rootNodeIndex-- )
        {
            /* Down heap */
            Dem_DataCtl_DownHeapSaveRecordNumber( (Dem_u16_FFRecNumStoredIndexType)rootNodeIndex, lastIndexOfList, &DataPtr[0] );/* [ARYCHK] DEM_TOTAL_NUM_OF_RECNUM_PER_DTC / 1 / 0 */
        }
        /* Sorts heap */
        for( ; lastIndexOfList > (Dem_u16_FFRecNumStoredIndexType)0U; lastIndexOfList-- )
        {
            /* Swaps occurrence order list data */
            Dem_DataCtl_SwapSaveRecordNumber( &DataPtr[0], &DataPtr[lastIndexOfList] );/* [ARYCHK] DEM_TOTAL_NUM_OF_RECNUM_PER_DTC / 1 / 0 *//* [ARYCHK] DEM_TOTAL_NUM_OF_RECNUM_PER_DTC / 1 / lastIndexOfList */

            /* Down heap */
            Dem_DataCtl_DownHeapSaveRecordNumber( (Dem_u16_FFRecNumStoredIndexType)0U, ( lastIndexOfList - (Dem_u16_FFRecNumStoredIndexType)1U ), &DataPtr[0] );/* [ARYCHK] DEM_TOTAL_NUM_OF_RECNUM_PER_DTC / 1 / 0 */
        }
    }
    else
    {
        /* If a input parameter NumOfRecordNumberToSort is 0 or 1, there is no node to compare. */
        /* Therefore, no processing. */
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_DataCtl_DownHeapSaveRecordNumber                     */
/* Description   | Down heap process for stored RecordNumber.               */
/* Preconditions |                                                          */
/* Parameters    | [in] IndexOfRoot :                                       */
/*               | [in] LastIndexOfList :                                   */
/*               | [in] DataPtr :                                           */
/*               |                  &Dem_TmpRecordNumberByDTC[x]            */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_DataCtl_DownHeapSaveRecordNumber
(
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) IndexOfRoot,
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) LastIndexOfList,
    P2VAR( Dem_TmpRecordNumberByDTCType, AUTOMATIC, DEM_VAR_NO_INIT ) DataPtr
)
{
    /* Variable declaration */
    VAR( boolean, AUTOMATIC )                               breakLoop;
    VAR( Dem_u32_FFRecNumStoredSortIndexType, AUTOMATIC )   rootNodeIndex;
    VAR( Dem_u32_FFRecNumStoredSortIndexType, AUTOMATIC )   leftChildNodeIndex;
    VAR( Dem_u32_FFRecNumStoredSortIndexType, AUTOMATIC )   rightChildNodeIndex;
    VAR( Dem_u32_FFRecNumStoredSortIndexType, AUTOMATIC )   maxChildNodeIndex;
    VAR( Dem_TmpRecordNumberByDTCType, AUTOMATIC )          originalRootNode;

    /* Saves the original root node. */
    rootNodeIndex                           = (Dem_u32_FFRecNumStoredSortIndexType)IndexOfRoot;
    originalRootNode.EventStrgIndex         = DataPtr[rootNodeIndex].EventStrgIndex;/* [ARYCHK] DEM_TOTAL_NUM_OF_RECNUM_PER_DTC / 1 / rootNodeIndex */
    originalRootNode.RecordNumber           = DataPtr[rootNodeIndex].RecordNumber;/* [ARYCHK] DEM_TOTAL_NUM_OF_RECNUM_PER_DTC / 1 / rootNodeIndex */
    originalRootNode.FreezeFrameDataIndex   = DataPtr[rootNodeIndex].FreezeFrameDataIndex;/* [ARYCHK] DEM_TOTAL_NUM_OF_RECNUM_PER_DTC / 1 / rootNodeIndex */
    originalRootNode.FreezeFrameDataType    = DataPtr[rootNodeIndex].FreezeFrameDataType;/* [ARYCHK] DEM_TOTAL_NUM_OF_RECNUM_PER_DTC / 1 / rootNodeIndex */

    breakLoop = (boolean)FALSE;

    while( breakLoop == (boolean)FALSE )
    {
        /* Calculates the left child node's index. */
        leftChildNodeIndex = (Dem_u32_FFRecNumStoredSortIndexType)( rootNodeIndex << 1U ) + (Dem_u32_FFRecNumStoredSortIndexType)1U;    /*  no wrap around      */

        /* Checks the presence of child nodes. */
        if( leftChildNodeIndex > (Dem_u32_FFRecNumStoredSortIndexType)LastIndexOfList )
        {
            /* There are no more child nodes, so exits the loop. */
            breakLoop = (boolean)TRUE;
        }
        else
        {
            /* There are child nodes, so chooses the node which has greater value. */

            /* At first saves the left child node's index to the max's one. */
            maxChildNodeIndex = leftChildNodeIndex;

            /* Checks the presence of the right child nodes. */
            if( leftChildNodeIndex != (Dem_u32_FFRecNumStoredSortIndexType)LastIndexOfList )
            {
                /* There is the right child node, so calculates the right child node' index. */
                rightChildNodeIndex = leftChildNodeIndex + (Dem_u32_FFRecNumStoredSortIndexType)1U;     /*  no wrap around      */

                /* Compares the left child node's occurrence order with the right child node's one. */
                if( DataPtr[leftChildNodeIndex].RecordNumber < DataPtr[rightChildNodeIndex].RecordNumber )/* [ARYCHK] DEM_TOTAL_NUM_OF_RECNUM_PER_DTC / 1 / leftChildNodeIndex *//* [ARYCHK] DEM_TOTAL_NUM_OF_RECNUM_PER_DTC / 1 / rightChildNodeIndex */
                {
                    /* In case the right child node's occurrence order is greater than the left's one. */

                    /* Saves the right child node's index to max child node's one. */
                    maxChildNodeIndex = rightChildNodeIndex;
                }
                else
                {
                    /* The left child node becomes the max child node, so no process. */
                }
            }
            else
            {
                /* There is the left child node but no right, so no process. */
            }

            /* Compares the root node's occurrence order of with the max child node's one. */
            if( originalRootNode.RecordNumber < DataPtr[maxChildNodeIndex].RecordNumber )/* [ARYCHK] DEM_TOTAL_NUM_OF_RECNUM_PER_DTC / 1 / maxChildNodeIndex */
            {
                /* The max child node's occurrence order is greater than the root node's one, so stores the max child node to the root. */
                DataPtr[rootNodeIndex].FreezeFrameDataIndex    = DataPtr[maxChildNodeIndex].FreezeFrameDataIndex;/* [ARYCHK] DEM_TOTAL_NUM_OF_RECNUM_PER_DTC / 1 / rootNodeIndex *//* [ARYCHK] DEM_TOTAL_NUM_OF_RECNUM_PER_DTC / 1 / maxChildNodeIndex */
                DataPtr[rootNodeIndex].EventStrgIndex          = DataPtr[maxChildNodeIndex].EventStrgIndex;/* [ARYCHK] DEM_TOTAL_NUM_OF_RECNUM_PER_DTC / 1 / rootNodeIndex *//* [ARYCHK] DEM_TOTAL_NUM_OF_RECNUM_PER_DTC / 1 / maxChildNodeIndex */
                DataPtr[rootNodeIndex].RecordNumber            = DataPtr[maxChildNodeIndex].RecordNumber;/* [ARYCHK] DEM_TOTAL_NUM_OF_RECNUM_PER_DTC / 1 / rootNodeIndex *//* [ARYCHK] DEM_TOTAL_NUM_OF_RECNUM_PER_DTC / 1 / maxChildNodeIndex */
                DataPtr[rootNodeIndex].FreezeFrameDataType     = DataPtr[maxChildNodeIndex].FreezeFrameDataType;/* [ARYCHK] DEM_TOTAL_NUM_OF_RECNUM_PER_DTC / 1 / rootNodeIndex *//* [ARYCHK] DEM_TOTAL_NUM_OF_RECNUM_PER_DTC / 1 / maxChildNodeIndex */

                /* Sets the max child node's index to the root's one. */
                rootNodeIndex = maxChildNodeIndex;
            }
            else
            {
                /* In case the root's occurrence order is not smaller than or is not equal to the max child node's one. */
                /* Goes out from the loop. */
                breakLoop = (boolean)TRUE;
            }
        }
    }

    /* Stores the saved original node to the root. */
    DataPtr[rootNodeIndex].EventStrgIndex          = originalRootNode.EventStrgIndex;/* [ARYCHK] DEM_TOTAL_NUM_OF_RECNUM_PER_DTC / 1 / rootNodeIndex */
    DataPtr[rootNodeIndex].RecordNumber            = originalRootNode.RecordNumber;/* [ARYCHK] DEM_TOTAL_NUM_OF_RECNUM_PER_DTC / 1 / rootNodeIndex */
    DataPtr[rootNodeIndex].FreezeFrameDataIndex    = originalRootNode.FreezeFrameDataIndex;/* [ARYCHK] DEM_TOTAL_NUM_OF_RECNUM_PER_DTC / 1 / rootNodeIndex */
    DataPtr[rootNodeIndex].FreezeFrameDataType     = originalRootNode.FreezeFrameDataType;/* [ARYCHK] DEM_TOTAL_NUM_OF_RECNUM_PER_DTC / 1 / rootNodeIndex */

    return;
}

/****************************************************************************/
/* Function Name | Dem_DataCtl_SwapSaveRecordNumber                         */
/* Description   | Stored RecordNumber data interchange processing.         */
/* Preconditions |                                                          */
/* Parameters    | [in] OriginDataPtr :                                     */
/*               | [in] DestDataPtr :                                       */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_DataCtl_SwapSaveRecordNumber
(
    P2VAR( Dem_TmpRecordNumberByDTCType, AUTOMATIC, DEM_VAR_NO_INIT ) OriginDataPtr,
    P2VAR( Dem_TmpRecordNumberByDTCType, AUTOMATIC, DEM_VAR_NO_INIT ) DestDataPtr
)
{
    /* Variable declaration */
    VAR( Dem_TmpRecordNumberByDTCType, AUTOMATIC )  tmpRecordNumberByDTCTmp;

    /* Data evacuation */
    tmpRecordNumberByDTCTmp.EventStrgIndex          = OriginDataPtr->EventStrgIndex;
    tmpRecordNumberByDTCTmp.RecordNumber            = OriginDataPtr->RecordNumber;
    tmpRecordNumberByDTCTmp.FreezeFrameDataIndex    = OriginDataPtr->FreezeFrameDataIndex;
    tmpRecordNumberByDTCTmp.FreezeFrameDataType     = OriginDataPtr->FreezeFrameDataType;

    /* Data replacement */
    OriginDataPtr->EventStrgIndex          = DestDataPtr->EventStrgIndex;
    OriginDataPtr->RecordNumber            = DestDataPtr->RecordNumber;
    OriginDataPtr->FreezeFrameDataIndex    = DestDataPtr->FreezeFrameDataIndex;
    OriginDataPtr->FreezeFrameDataType     = DestDataPtr->FreezeFrameDataType;

    /* Data update */
    DestDataPtr->EventStrgIndex        = tmpRecordNumberByDTCTmp.EventStrgIndex;
    DestDataPtr->RecordNumber          = tmpRecordNumberByDTCTmp.RecordNumber;
    DestDataPtr->FreezeFrameDataIndex  = tmpRecordNumberByDTCTmp.FreezeFrameDataIndex;
    DestDataPtr->FreezeFrameDataType   = tmpRecordNumberByDTCTmp.FreezeFrameDataType;

    return;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
