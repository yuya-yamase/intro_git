/* Dem_UdmDataCtl_InfoFFD_Sort_c(v5-7-0)                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Dem_UdmDataCtl_InfoFFD_Sort/CODE                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
#include "Dem_UdmDataCtl_local.h"

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

static FUNC( void, DEM_CODE ) Dem_UdmDataCtl_DownHeapSaveRecordNumber
(
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) IndexOfRoot,
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) LastIndexOfList,
    P2VAR( Dem_UdmTmpRecordNumberByDTCType, AUTOMATIC, DEM_VAR_NO_INIT ) DataPtr
);

static FUNC( void, DEM_CODE ) Dem_UdmDataCtl_SwapSaveRecordNumber
(
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( Dem_UdmTmpRecordNumberByDTCType, AUTOMATIC, DEM_VAR_NO_INIT ) OriginDataPtr,
    P2VAR( Dem_UdmTmpRecordNumberByDTCType, AUTOMATIC, DEM_VAR_NO_INIT ) DestDataPtr
);

static FUNC( Dem_u08_FFRecordNumberType, DEM_CODE ) Dem_UdmDataCtl_CalculateRecordNumber
(
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) LastIndexOfList
);

static FUNC( void, DEM_CODE ) Dem_UdmDataCtl_CopyTmpRecordNumberByDTCWithoutRecordNumber
(
    P2VAR( Dem_UdmTmpRecordNumberByDTCType, AUTOMATIC, DEM_VAR_NO_INIT ) DestTmpRecNumByDTCPtr,
    P2VAR( Dem_UdmTmpRecordNumberByDTCType, AUTOMATIC , DEM_VAR_NO_INIT ) SrcTmpRecNumByDTCPtr
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
/* Function Name | Dem_UdmData_SortSaveRecordNumber                         */
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
FUNC( void, DEM_CODE ) Dem_UdmData_SortSaveRecordNumber
(
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) NumberOfSaveRecord,
    P2VAR( Dem_UdmTmpRecordNumberByDTCType, AUTOMATIC, DEM_VAR_NO_INIT ) DataPtr
)
{
    /* Variable declaration */
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) recordNumber;
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
            Dem_UdmDataCtl_DownHeapSaveRecordNumber( (Dem_u16_FFRecNumStoredIndexType)rootNodeIndex, lastIndexOfList, &DataPtr[0] );/* [ARYCHK] DEM_UDM_MAX_NUMBER_FF_PER_DTC / 1 / 0 */
        }
        /* Sorts heap */
        for( ; lastIndexOfList > (Dem_u16_FFRecNumStoredIndexType)0U; lastIndexOfList-- )
        {
            /* Swaps occurrence order list data */
            recordNumber = Dem_UdmDataCtl_CalculateRecordNumber( lastIndexOfList );
            Dem_UdmDataCtl_SwapSaveRecordNumber( recordNumber, &DataPtr[0], &DataPtr[lastIndexOfList] );/* [ARYCHK] DEM_UDM_MAX_NUMBER_FF_PER_DTC / 1 / 0 *//* [ARYCHK] DEM_UDM_MAX_NUMBER_FF_PER_DTC / 1 / lastIndexOfList */

            /* Down heap */
            Dem_UdmDataCtl_DownHeapSaveRecordNumber( (Dem_u16_FFRecNumStoredIndexType)0U, ( lastIndexOfList - (Dem_u16_FFRecNumStoredIndexType)1U ), &DataPtr[0] );/* [ARYCHK] DEM_UDM_MAX_NUMBER_FF_PER_DTC / 1 / 0 */

            /* Sets record number for the oldeset item. */
            recordNumber = Dem_UdmDataCtl_CalculateRecordNumber( lastIndexOfList - (Dem_u16_FFRecNumStoredIndexType)1U );
            DataPtr[0].RecordNumber = recordNumber;/* [ARYCHK] DEM_UDM_MAX_NUMBER_FF_PER_DTC / 1 / 0 */
        }
    }
    else
    {
        /* If a input parameter NumOfRecordNumberToSort is 0 or 1, there is no node to compare. */

        if( NumberOfSaveRecord == (Dem_u16_FFRecNumStoredIndexType)1U )
        {
            /* Sets record number for the oldeset item. */
            recordNumber = Dem_UdmDataCtl_CalculateRecordNumber( (Dem_u16_FFRecNumStoredIndexType)0U );
            DataPtr[0].RecordNumber = recordNumber;/* [ARYCHK] DEM_UDM_MAX_NUMBER_FF_PER_DTC / 1 / 0 */
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_UdmDataCtl_DownHeapSaveRecordNumber                  */
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
static FUNC( void, DEM_CODE ) Dem_UdmDataCtl_DownHeapSaveRecordNumber
(
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) IndexOfRoot,
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) LastIndexOfList,
    P2VAR( Dem_UdmTmpRecordNumberByDTCType, AUTOMATIC, DEM_VAR_NO_INIT ) DataPtr
)
{
    /* Variable declaration */
    VAR( boolean, AUTOMATIC )                               breakLoop;
    VAR( Dem_u32_FFRecNumStoredSortIndexType, AUTOMATIC )   rootNodeIndex;
    VAR( Dem_u32_FFRecNumStoredSortIndexType, AUTOMATIC )   leftChildNodeIndex;
    VAR( Dem_u32_FFRecNumStoredSortIndexType, AUTOMATIC )   rightChildNodeIndex;
    VAR( Dem_u32_FFRecNumStoredSortIndexType, AUTOMATIC )   maxChildNodeIndex;
    VAR( Dem_UdmTmpRecordNumberByDTCType, AUTOMATIC )          originalRootNode;

    /* Saves the original root node. */
    rootNodeIndex                           = (Dem_u32_FFRecNumStoredSortIndexType)IndexOfRoot;
    Dem_UdmDataCtl_CopyTmpRecordNumberByDTCWithoutRecordNumber( &originalRootNode, &DataPtr[rootNodeIndex] );/* [ARYCHK] DEM_UDM_MAX_NUMBER_FF_PER_DTC / 1 / rootNodeIndex */
    originalRootNode.RecordNumber           = DataPtr[rootNodeIndex].RecordNumber;/* [ARYCHK] DEM_UDM_MAX_NUMBER_FF_PER_DTC / 1 / rootNodeIndex */

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
                if( DataPtr[leftChildNodeIndex].OccurrenceOrder > DataPtr[rightChildNodeIndex].OccurrenceOrder )/* [ARYCHK] DEM_UDM_MAX_NUMBER_FF_PER_DTC / 1 / leftChildNodeIndex *//* [ARYCHK] DEM_UDM_MAX_NUMBER_FF_PER_DTC / 1 / rightChildNodeIndex */
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
            if( originalRootNode.OccurrenceOrder > DataPtr[maxChildNodeIndex].OccurrenceOrder )/* [ARYCHK] DEM_UDM_MAX_NUMBER_FF_PER_DTC / 1 / maxChildNodeIndex */
            {
                /* The max child node's occurrence order is greater than the root node's one, so stores the max child node to the root. */
                Dem_UdmDataCtl_CopyTmpRecordNumberByDTCWithoutRecordNumber( &DataPtr[rootNodeIndex], &DataPtr[maxChildNodeIndex] );/* [ARYCHK] DEM_UDM_MAX_NUMBER_FF_PER_DTC / 1 / rootNodeIndex *//* [ARYCHK] DEM_UDM_MAX_NUMBER_FF_PER_DTC / 1 / maxChildNodeIndex */
                DataPtr[rootNodeIndex].RecordNumber            = DataPtr[maxChildNodeIndex].RecordNumber;/* [ARYCHK] DEM_UDM_MAX_NUMBER_FF_PER_DTC / 1 / rootNodeIndex *//* [ARYCHK] DEM_UDM_MAX_NUMBER_FF_PER_DTC / 1 / maxChildNodeIndex */

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
    Dem_UdmDataCtl_CopyTmpRecordNumberByDTCWithoutRecordNumber( &DataPtr[rootNodeIndex], &originalRootNode );/* [ARYCHK] DEM_UDM_MAX_NUMBER_FF_PER_DTC / 1 / rootNodeIndex */
    DataPtr[rootNodeIndex].RecordNumber            = originalRootNode.RecordNumber;/* [ARYCHK] DEM_UDM_MAX_NUMBER_FF_PER_DTC / 1 / rootNodeIndex */

    return;
}

/****************************************************************************/
/* Function Name | Dem_UdmDataCtl_SwapSaveRecordNumber                      */
/* Description   | Stored RecordNumber data interchange processing.         */
/* Preconditions |                                                          */
/* Parameters    | [in] RecordNumber :                                      */
/*               | [in] OriginDataPtr :                                     */
/*               | [out] DestDataPtr :                                      */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmDataCtl_SwapSaveRecordNumber
(
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( Dem_UdmTmpRecordNumberByDTCType, AUTOMATIC, DEM_VAR_NO_INIT ) OriginDataPtr,
    P2VAR( Dem_UdmTmpRecordNumberByDTCType, AUTOMATIC, DEM_VAR_NO_INIT ) DestDataPtr
)
{
    /* Variable declaration */
    VAR( Dem_UdmTmpRecordNumberByDTCType, AUTOMATIC )  tmpRecordNumberByDTCTmp;

    /* Data evacuation */
    Dem_UdmDataCtl_CopyTmpRecordNumberByDTCWithoutRecordNumber( &tmpRecordNumberByDTCTmp, OriginDataPtr );

    /* Data replacement */
    Dem_UdmDataCtl_CopyTmpRecordNumberByDTCWithoutRecordNumber( OriginDataPtr, DestDataPtr );

    /* Data update */
    Dem_UdmDataCtl_CopyTmpRecordNumberByDTCWithoutRecordNumber( DestDataPtr, &tmpRecordNumberByDTCTmp );
    DestDataPtr->RecordNumber          = RecordNumber;

    return;
}

/****************************************************************************/
/* Function Name | Dem_UdmDataCtl_CalculateRecordNumber                     */
/* Description   | Calculates RecordNumber.                                 */
/* Preconditions |                                                          */
/* Parameters    | [in] LastIndexOfList :                                   */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( Dem_u08_FFRecordNumberType, DEM_CODE ) Dem_UdmDataCtl_CalculateRecordNumber
(
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) LastIndexOfList
)
{
    /* Variable declaration */
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) recordNumber;

    recordNumber = (Dem_u08_FFRecordNumberType)LastIndexOfList;
    recordNumber = recordNumber + (Dem_u08_FFRecordNumberType)1U;

    return recordNumber;
}

/****************************************************************************/
/* Function Name | Dem_UdmDataCtl_CopyTmpRecordNumberByDTCWithoutRecordNumber*/
/* Description   | copy Dem_UdmTmpRecordNumberByDTCType area.               */
/* Preconditions |                                                          */
/* Parameters    | [out] DestTmpRecNumByDTCPtr :                            */
/* Parameters    | [in] SrcTmpRecNumByDTCPtr :                              */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmDataCtl_CopyTmpRecordNumberByDTCWithoutRecordNumber
(
    P2VAR( Dem_UdmTmpRecordNumberByDTCType, AUTOMATIC, DEM_VAR_NO_INIT ) DestTmpRecNumByDTCPtr,
    P2VAR( Dem_UdmTmpRecordNumberByDTCType, AUTOMATIC , DEM_VAR_NO_INIT ) SrcTmpRecNumByDTCPtr
)
{
    DestTmpRecNumByDTCPtr->OccurrenceOrder                  = SrcTmpRecNumByDTCPtr->OccurrenceOrder;
    DestTmpRecNumByDTCPtr->RecordStatus                     = SrcTmpRecNumByDTCPtr->RecordStatus;
    DestTmpRecNumByDTCPtr->FreezeFrameDataIndex             = SrcTmpRecNumByDTCPtr->FreezeFrameDataIndex;
    DestTmpRecNumByDTCPtr->FreezeFrameDataType              = SrcTmpRecNumByDTCPtr->FreezeFrameDataType;
    DestTmpRecNumByDTCPtr->TimeSeriesFreezeFrameListIndex   = SrcTmpRecNumByDTCPtr->TimeSeriesFreezeFrameListIndex;
    DestTmpRecNumByDTCPtr->CidUdmFreezeFrameRecords         = SrcTmpRecNumByDTCPtr->CidUdmFreezeFrameRecords;

    return ;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )      */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
