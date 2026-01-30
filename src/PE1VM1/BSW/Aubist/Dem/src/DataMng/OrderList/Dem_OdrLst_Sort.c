/* Dem_OdrLst_Sort_c(v5-7-0)                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/OdrLst_Sort/CODE                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../../../inc/Dem_Rc_DataMng.h"
#include "Dem_OdrLst_local.h"

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

static FUNC( void, DEM_CODE ) Dem_OdrLst_SwapFaultOrderListData
(
    P2VAR( Dem_FaultRegistType, AUTOMATIC, DEM_VAR_NO_INIT ) OriginDataPtr,
    P2VAR( Dem_FaultRegistType, AUTOMATIC, DEM_VAR_NO_INIT ) DestDataPtr
);
static FUNC( void, DEM_CODE ) Dem_OdrLst_DownHeap
(
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) IndexOfRoot,
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) LastIndexOfList,
    P2VAR( Dem_FaultRegistType, AUTOMATIC, DEM_VAR_NO_INIT ) DataPtr
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

VAR( Dem_FaultRegistType, DEM_VAR_NO_INIT ) Dem_OdrLst_TmpFaultOrderList[DEM_FAIL_RECORD_NUM];

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_OdrLst_SortFaultOrderList                            */
/* Description   | Failure occurrence order list sort processing            */
/* Preconditions |                                                          */
/* Parameters    | [in] NumOfFaultOrderItemsToSort :                        */
/*               |                                                          */
/*               | [in/out] DataPtr :                                       */
/*               |                  &Dem_DataMng_FaultOrderList[x]          */
/*               |                  &Dem_DataMng_ConfirmedFaultOrderList[x] */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_OdrLst_SortFaultOrderList
(
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) NumOfFaultOrderItemsToSort,
    P2VAR( Dem_FaultRegistType, AUTOMATIC, DEM_VAR_NO_INIT ) DataPtr
)
{
    /* Variable declaration */
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) lastIndexOfList;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) indexOfLastRootNode;
    VAR( Dem_s16_OrderIndexType, AUTOMATIC ) rootNodeIndex;

    if( NumOfFaultOrderItemsToSort > (Dem_u08_OrderIndexType)1U )
    {
        lastIndexOfList = NumOfFaultOrderItemsToSort - (Dem_u08_OrderIndexType)1U;
        indexOfLastRootNode = (Dem_u08_OrderIndexType)( lastIndexOfList - (Dem_u08_OrderIndexType)1U ) >> (Dem_u08_OrderIndexType)1U;

        /* Makes heap */
        for( rootNodeIndex = (Dem_s16_OrderIndexType)indexOfLastRootNode; rootNodeIndex >= (Dem_s16_OrderIndexType)0; rootNodeIndex-- )
        {
            /* Down heap */
            Dem_OdrLst_DownHeap( (Dem_u08_OrderIndexType)rootNodeIndex, lastIndexOfList, &DataPtr[0] ); /* [ARYCHK] DEM_FAIL_RECORD_NUM/1/0 */
        }

        /* Sorts heap */
        for( ; lastIndexOfList > (Dem_u08_OrderIndexType)0U; lastIndexOfList-- )
        {
            /* Swaps occurrence order list data */
            Dem_OdrLst_SwapFaultOrderListData( &DataPtr[0], &DataPtr[lastIndexOfList] ); /* [ARYCHK] DEM_FAIL_RECORD_NUM/1/0 *//* [ARYCHK] DEM_FAIL_RECORD_NUM/1/lastIndexOfList */

            /* Down heap */
            Dem_OdrLst_DownHeap( (Dem_u08_OrderIndexType)0U, ( lastIndexOfList - (Dem_u08_OrderIndexType)1U ), &DataPtr[0] ); /* [ARYCHK] DEM_FAIL_RECORD_NUM/1/0 */
        }
    }
    else
    {
        /* If a input parameter NumOfFaultOrderItemsToSort is 0 or 1, there is no node to compare. */
        /* Therefore, no processing. */
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_OdrLst_SwapFaultOrderListData                        */
/* Description   | Fault occurrence order table data interchange processin- */
/*               | g                                                        */
/* Preconditions |                                                          */
/* Parameters    | [in/out] OriginDataPtr :                                 */
/*               |                  &Dem_DataMng_FaultOrderList[0]          */
/*               |                  &Dem_DataMng_ConfirmedFaultOrderList[0] */
/*               | [in/out] DestDataPtr :                                   */
/*               |                  &Dem_DataMng_FaultOrderList[0]          */
/*               |                  &Dem_DataMng_ConfirmedFaultOrderList[0] */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_OdrLst_SwapFaultOrderListData
(
    P2VAR( Dem_FaultRegistType, AUTOMATIC, DEM_VAR_NO_INIT ) OriginDataPtr,
    P2VAR( Dem_FaultRegistType, AUTOMATIC, DEM_VAR_NO_INIT ) DestDataPtr
)
{
    /* Variable declaration */
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndexTmp;
    VAR( Dem_u16_OccrOrderType, AUTOMATIC ) occurrenceOrderTmp;

    /* Data evacuation */
    occurrenceOrderTmp = OriginDataPtr->OccurrenceOrder;
    faultIndexTmp  = OriginDataPtr->FaultIndex;

    /* Data replacement */
    OriginDataPtr->OccurrenceOrder = DestDataPtr->OccurrenceOrder;
    OriginDataPtr->FaultIndex  = DestDataPtr->FaultIndex;

    /* Data update */
    DestDataPtr->OccurrenceOrder = occurrenceOrderTmp;
    DestDataPtr->FaultIndex  = faultIndexTmp;

    return;
}


/****************************************************************************/
/* Function Name | Dem_OdrLst_DownHeap                                      */
/* Description   | Down heap process for failure occurrence list            */
/* Preconditions |                                                          */
/* Parameters    | [in] IndexOfRoot :                                       */
/*               |                                                          */
/*               | [in] LastIndexOfList :                                   */
/*               |                                                          */
/*               | [in/out] DataPtr :                                       */
/*               |                  &Dem_DataMng_FaultOrderList[0]          */
/*               |                  &Dem_DataMng_ConfirmedFaultOrderList[0] */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_OdrLst_DownHeap
(
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) IndexOfRoot,
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) LastIndexOfList,
    P2VAR( Dem_FaultRegistType, AUTOMATIC, DEM_VAR_NO_INIT ) DataPtr
)
{
    /* Variable declaration */
    VAR( boolean, AUTOMATIC ) breakLoop;
    VAR( Dem_u16_OrderSortIndexType, AUTOMATIC ) rootNodeIndex;
    VAR( Dem_u16_OrderSortIndexType, AUTOMATIC ) leftChildNodeIndex;
    VAR( Dem_u16_OrderSortIndexType, AUTOMATIC ) rightChildNodeIndex;
    VAR( Dem_u16_OrderSortIndexType, AUTOMATIC ) maxChildNodeIndex;
    VAR( Dem_FaultRegistType, AUTOMATIC ) originalRootNode;

    /* Saves the original root node. */
    rootNodeIndex = (Dem_u16_OrderSortIndexType)IndexOfRoot;
    originalRootNode.FaultIndex      = DataPtr[rootNodeIndex].FaultIndex; /* [ARYCHK] DEM_FAIL_RECORD_NUM/1/rootNodeIndex */
    originalRootNode.OccurrenceOrder = DataPtr[rootNodeIndex].OccurrenceOrder; /* [ARYCHK] DEM_FAIL_RECORD_NUM/1/rootNodeIndex */

    breakLoop = (boolean)FALSE;

    while( breakLoop == (boolean)FALSE )
    {
        /* Calculates the left child node's index. */
        leftChildNodeIndex = (Dem_u16_OrderSortIndexType)( rootNodeIndex << (Dem_u16_OrderSortIndexType)1U ) + (Dem_u16_OrderSortIndexType)1U;

        /* Checks the presence of child nodes. */
        if( leftChildNodeIndex > (Dem_u16_OrderSortIndexType)LastIndexOfList )
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
            if( leftChildNodeIndex != (Dem_u16_OrderSortIndexType)LastIndexOfList )
            {
                /* There is the right child node, so calculates the right child node' index. */
                rightChildNodeIndex = leftChildNodeIndex + (Dem_u16_OrderSortIndexType)1U;

                /* Compares the left child node's occurrence order with the right child node's one. */
                if( DataPtr[leftChildNodeIndex].OccurrenceOrder < DataPtr[rightChildNodeIndex].OccurrenceOrder ) /* [ARYCHK] DEM_FAIL_RECORD_NUM/1/leftChildNodeIndex *//* [ARYCHK] DEM_FAIL_RECORD_NUM/1/rightChildNodeIndex */
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
            if( originalRootNode.OccurrenceOrder < DataPtr[maxChildNodeIndex].OccurrenceOrder ) /* [ARYCHK] DEM_FAIL_RECORD_NUM/1/maxChildNodeIndex */
            {
                /* The max child node's occurrence order is greater than the root node's one, so stores the max child node to the root. */
                DataPtr[rootNodeIndex].FaultIndex      = DataPtr[maxChildNodeIndex].FaultIndex; /* [ARYCHK] DEM_FAIL_RECORD_NUM/1/rootNodeIndex *//* [ARYCHK] DEM_FAIL_RECORD_NUM/1/maxChildNodeIndex */
                DataPtr[rootNodeIndex].OccurrenceOrder = DataPtr[maxChildNodeIndex].OccurrenceOrder; /* [ARYCHK] DEM_FAIL_RECORD_NUM/1/rootNodeIndex *//* [ARYCHK] DEM_FAIL_RECORD_NUM/1/maxChildNodeIndex */

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
    DataPtr[rootNodeIndex].FaultIndex      = originalRootNode.FaultIndex; /* [ARYCHK] DEM_FAIL_RECORD_NUM/1/rootNodeIndex */
    DataPtr[rootNodeIndex].OccurrenceOrder = originalRootNode.OccurrenceOrder; /* [ARYCHK] DEM_FAIL_RECORD_NUM/1/rootNodeIndex */

    return;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-05-29                                              */
/*  v4-0-0         :2020-03-19                                              */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
