/* Dem_OdrLst_Confirmed_c(v5-5-0)                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Dem_OdrLst_Confirmed/CODE                             */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#if ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )
#include "../../../inc/Dem_Rc_DataMng.h"
#include "../../../inc/Dem_Rc_OdrLst.h"
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

static FUNC( void, DEM_CODE ) Dem_OdrLst_Confirmed_CheckLastOccurrenceOrder
( void );

static FUNC( Dem_u08_OrderIndexType, DEM_CODE ) Dem_OdrLst_Confirmed_BringValidDataToTopEdge
(
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) StartIndex,
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) MaxOfFaultOrderItems
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>
/* Fault order list */
static VAR( Dem_FaultOrderType, DEM_VAR_NO_INIT ) Dem_OdrLst_Confirmed_OrderList[DEM_FAIL_RECORD_NUM];

/* Fault occurrence sequence number */
static VAR( Dem_u16_OccrOrderType, DEM_VAR_NO_INIT ) Dem_OdrLst_Confirmed_NextOccurrenceOrder;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/*==========================================================================*/
/*  Function for USE confirmed order list.                                  */
/*==========================================================================*/

/****************************************************************************/
/* Function Name | Dem_OdrLst_Confirmed_GetOccrOrderValue                   */
/* Description   | confirmed record Registration position Index informatio- */
/*               | n acquisition processing                                 */
/* Preconditions | The confirned occurrence order list has been generated.  */
/* Parameters    | [in] OrderListIndex :                                    */
/*               |                                                          */
/*               | [out] OccurrenceOrderPtr :                               */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_PARAM_DATA :                              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_OdrLst_Confirmed_GetOccrOrderValue
(
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) OrderListIndex,
    P2VAR( Dem_u16_OccrOrderType, AUTOMATIC, AUTOMATIC ) OccurrenceOrderPtr
)
{
    /* Variable declaration */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;


    /* Verifies the validity of the parameter OrderListIndex. */
    if( OrderListIndex != Dem_EventMemoryRecordList.NumberOfConfirmedDTCs )
    {
        /* Sets the return value to the parameter error. */
        retVal = DEM_IRT_PARAM_DATA;
    }
    else
    {
        retVal = DEM_IRT_OK;
    }

    if( retVal == DEM_IRT_OK )
    {
        if( Dem_OdrLst_Confirmed_NextOccurrenceOrder > DEM_FAIL_OCCURRENCE_NUM_LIMIT )
        {
            /* Sets the return value to the parameter error. */
            retVal = DEM_IRT_PARAM_DATA;
        }
        else
        {
            /* Registration record position information setting */

            /* Order of occurrence */
            *OccurrenceOrderPtr = Dem_OdrLst_Confirmed_NextOccurrenceOrder;
        }
    }
    else
    {
        /* No process */
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_OdrLst_Confirmed_RegistComplete                      */
/* Description   | Notification of confirmed record registration completion.*/
/* Preconditions |                                                          */
/* Parameters    | [in] FaultIndex :                                        */
/*               |                                                          */
/*               | [in] OrderListIndex :                                    */
/*               |                                                          */
/*               | [in] OccurrenceOrder :                                   */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_OdrLst_Confirmed_RegistComplete
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) OrderListIndex,
    VAR( Dem_u16_OccrOrderType, AUTOMATIC ) OccurrenceOrder
)
{
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) failRecordNum;

    failRecordNum = (Dem_u08_OrderIndexType)Dem_FailRecordNum;

    /* Fault registration is successful */
    /* Index value is within range */
    if( OrderListIndex < failRecordNum  )                                               /* [GUD:if]OrderListIndex */
    {
        /* The occurrence sequence number of the fault record is correct */
        if( OccurrenceOrder ==  Dem_OdrLst_Confirmed_NextOccurrenceOrder )
        {
            /* Failure data registration in the occurrence order list */
            Dem_OdrLst_Confirmed_OrderList[OrderListIndex].FaultIndex = FaultIndex;     /* [GUD]OrderListIndex */

            /* Update occurrence order */
            Dem_OdrLst_Confirmed_NextOccurrenceOrder = Dem_OdrLst_Confirmed_NextOccurrenceOrder + (Dem_u16_OccrOrderType)1U;
        }
    }

    return ;
}


#if ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON )
#if ( DEM_DTC_OCCURRENCE_TIME_UPDATEATAGING_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_OdrLst_Confirmed_GetLastOccurrenceOrder              */
/* Description   | Get the order of ConfirmedDTC.                           */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/*               |                                                          */
/* Return Value  | Dem_u08_OrderIndexType                                   */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_OrderIndexType, DEM_CODE ) Dem_OdrLst_Confirmed_GetLastOccurrenceOrder
( void )
{
    /* Variable declaration */
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) orderListIndex;

    failRecordNum = Dem_FailRecordNum;

    orderListIndex = DEM_ORDERINDEX_INVALID;

    /* Failure registration number acquisition */
    if( Dem_EventMemoryRecordList.NumberOfConfirmedDTCs <= failRecordNum )
    {
        if( Dem_EventMemoryRecordList.NumberOfConfirmedDTCs > (Dem_u08_OrderIndexType)0U )
        {
            orderListIndex = Dem_EventMemoryRecordList.NumberOfConfirmedDTCs - (Dem_u08_OrderIndexType)1U;
        }
    }

    return orderListIndex;

}
#endif  /* ( DEM_DTC_OCCURRENCE_TIME_UPDATEATAGING_SUPPORT == STD_ON )  */
#endif /* ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON ) */

#if ( DEM_ORDERTYPE_CONFIRMED_ORDERLIST_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_OdrLst_Confirmed_GetFaultIndexByOrder                */
/* Description   | Confirmed occurrence order list data acquisition proces- */
/*               | sing                                                     */
/* Preconditions | The confirmed occurrence order list has been generated.  */
/* Parameters    | [in] OrderListIndex :                                    */
/*               |                                                          */
/*               | [out] FaultIndexPtr :                                    */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NO_MATCHING_ELEMENT :                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_OdrLst_Confirmed_GetFaultIndexByOrder
(
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) OrderListIndex,
    P2VAR( Dem_u08_FaultIndexType, AUTOMATIC, AUTOMATIC ) FaultIndexPtr
)
{
    /* Variable declaration */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC  )  retVal;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;

    /* Variable initialization */
    retVal = DEM_IRT_OK;

    failRecordNum = Dem_FailRecordNum;

    /* Index value is within range */
    if( OrderListIndex < failRecordNum )                                                /* [GUD:if]OrderListIndex */
    {
        faultIndex = Dem_OdrLst_Confirmed_OrderList[OrderListIndex].FaultIndex;         /* [GUD]OrderListIndex */

        if( faultIndex < failRecordNum )                                                /* [GUD:if]faultIndex */
        {
            /* When there is fault registration information */
            if( Dem_FaultRecordList[faultIndex].ConfirmedOccurrenceOrder !=  DEM_FAIL_OCCURRENCE_NUM_INVALID )      /* [GUD]faultIndex */
            {
                /* Index information setting */
                *FaultIndexPtr = faultIndex;
            }
            else
            {
                /* Invalid Index setting */
                *FaultIndexPtr = DEM_FAULTINDEX_INITIAL;

                /* Sets the return value to DEM_IRT_NO_MATCHING_ELEMENT, No effective data */
                retVal = DEM_IRT_NO_MATCHING_ELEMENT;
            }
        }
        else
        {
            /* Invalid Index setting */
            *FaultIndexPtr = DEM_FAULTINDEX_INITIAL;

            /* Sets the return value to DEM_IRT_NO_MATCHING_ELEMENT, No effective data */
            retVal = DEM_IRT_NO_MATCHING_ELEMENT;
        }
    }
    /* Index value is out of range */
    else
    {
        /* Invalid Index setting */
        *FaultIndexPtr = DEM_FAULTINDEX_INITIAL;

        /* Sets the return value to DEM_IRT_NO_MATCHING_ELEMENT, No effective data */
        retVal = DEM_IRT_NO_MATCHING_ELEMENT;
    }

    return retVal;

}
#endif  /* ( DEM_ORDERTYPE_CONFIRMED_ORDERLIST_USE == STD_ON )  */

/****************************************************************************/
/* Function Name | Dem_OdrLst_Confirmed_GetOrderByFaultIndex                */
/* Description   | Get the order of ConfirmedDTC.                           */
/* Preconditions | none                                                     */
/* Parameters    | [in] FaultIndex :                                        */
/*               |                                                          */
/*               | [out] OrderPtr :                                         */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_OdrLst_Confirmed_GetOrderByFaultIndex
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_u16_OccrOrderType, AUTOMATIC, AUTOMATIC ) OrderPtr
)
{
    /* Variable declaration */
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) listIndex;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;

    /* Variable initialization */
    *OrderPtr = DEM_FAIL_OCCURRENCE_NUM_INVALID;

    failRecordNum = Dem_FailRecordNum;

    for( listIndex = (Dem_u08_FaultIndexType)0U; listIndex < failRecordNum; listIndex++ )   /* [GUD:for]listIndex */
    {
        if( Dem_OdrLst_Confirmed_OrderList[listIndex].FaultIndex == FaultIndex )            /* [GUD]listIndex */
        {
            *OrderPtr = (Dem_u16_OccrOrderType)listIndex + (Dem_u16_OccrOrderType)1U;

            break;
        }
    }

    return;

}

#if ( DEM_CLEAR_EVENT_NOT_ALLOWED_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_OdrLst_Confirmed_ClearList                           */
/* Description   | Clear processing of confirmed occurrence order list data.*/
/* Preconditions | The confirmed occurrence order list has been generated.  */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_OdrLst_Confirmed_ClearList
( void )
{
    /* Variable declaration */
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) failRecordNum;

    failRecordNum = (Dem_u08_OrderIndexType)Dem_FailRecordNum;

    /* Check all failed record data */
    for( faultIndex = (Dem_u08_OrderIndexType)0U; faultIndex < failRecordNum; faultIndex++ )    /* [GUD:for]faultIndex */
    {
        /* Store failed record Index */
        Dem_OdrLst_Confirmed_OrderList[faultIndex].FaultIndex = DEM_FAULTINDEX_INITIAL;         /* [GUD]faultIndex */
    }

    /* Initial value setting */
    Dem_OdrLst_Confirmed_NextOccurrenceOrder   = DEM_FAIL_OCCURRENCE_NUM_INITIAL;
    Dem_EventMemoryRecordList.NumberOfConfirmedDTCs = DEM_NUMOFEVTMEMENT_INITIAL;
    return;
}
#endif  /* ( DEM_CLEAR_EVENT_NOT_ALLOWED_SUPPORT == STD_OFF ) */

/****************************************************************************/
/* Function Name | Dem_OdrLst_Confirmed_ExecSort                            */
/* Description   | Confirmed occurrence order list generation processing    */
/* Preconditions | Data consistent with persistent RAM is stored            */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_OdrLst_Confirmed_ExecSort
( void )
{
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) numOfOrderItemsToSort;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) failRecordNum;

    failRecordNum = (Dem_u08_OrderIndexType)Dem_FailRecordNum;

    Dem_EventMemoryRecordList.NumberOfConfirmedDTCs = DEM_NUMOFEVTMEMENT_INITIAL;

    /* Acquisition of Fault Record occurrence order information */
    numOfOrderItemsToSort = Dem_OdrLst_Confirmed_BringValidDataToTopEdge( (Dem_u08_OrderIndexType)0U, failRecordNum );

    Dem_EventMemoryRecordList.NumberOfConfirmedDTCs = numOfOrderItemsToSort;

    /* Order of occurrence list sort */
    Dem_OdrLst_SortFaultOrderList( numOfOrderItemsToSort, &Dem_OdrLst_TmpFaultOrderList[0] );

    /* Confirmation of occurrence order number */
    Dem_OdrLst_Confirmed_CheckLastOccurrenceOrder();
    return;
}


/****************************************************************************/
/* Function Name | Dem_OdrLst_Confirmed_ApplySortedList                     */
/* Description   | Stores confirmed fault occurrence order from temporary   */
/*               | fault order list.                                        */
/* Preconditions | Data consistent with persistent RAM is stored            */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_OdrLst_Confirmed_ApplySortedList
( void )
{
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) loopCount;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) failRecordNum;

    failRecordNum = (Dem_u08_OrderIndexType)Dem_FailRecordNum;

    for( loopCount = 0U; loopCount < failRecordNum; loopCount++ )   /* [GUD:for]loopCount */
    {
        Dem_OdrLst_Confirmed_OrderList[loopCount].FaultIndex = Dem_OdrLst_TmpFaultOrderList[loopCount].FaultIndex;  /* [GUD]loopCount */
    }

    return;
}


#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_OdrLst_Confirmed_GetNextOccurrenceOrder              */
/* Description   | Returns the next fault occurrence order.                 */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_OdrLst_Confirmed_GetNextOccurrenceOrder
(
    P2VAR( Dem_u16_OccrOrderType, AUTOMATIC, AUTOMATIC ) OccurrenceOrderPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC  )  retVal;

    if( Dem_OdrLst_Confirmed_NextOccurrenceOrder > DEM_FAIL_OCCURRENCE_NUM_LIMIT )
    {
        retVal = DEM_IRT_NG;
    }
    else
    {
        *OccurrenceOrderPtr = Dem_OdrLst_Confirmed_NextOccurrenceOrder;
        retVal = DEM_IRT_OK;
    }

    return retVal;

}


/****************************************************************************/
/* Function Name | Dem_OdrLst_Confirmed_UpdateNextOccurrenceOrder           */
/* Description   | Adds one to the next fault occurrence order.             */
/* Preconditions |                                                          */
/* Parameters    | [in] NextFaultOccurrenceOrder :                          */
/*               |        The given next confirmed fault occurrence order   */
/* Return Value  | void                                                     */
/* Notes         | Call this function specified the next confirmed occurre- */
/*               | nce order gotten by Dem_DataMngC_GetNextConfirmedFaultO- */
/*               | ccurrenceOrder  function.                                */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_OdrLst_Confirmed_UpdateNextOccurrenceOrder
(
    VAR( Dem_u16_OccrOrderType, AUTOMATIC ) NextOccurrenceOrder
)
{
    if( NextOccurrenceOrder == Dem_OdrLst_Confirmed_NextOccurrenceOrder )
    {
        if( Dem_OdrLst_Confirmed_NextOccurrenceOrder < DEM_FAIL_OCCURRENCE_NUM_LIMIT )
        {
            Dem_OdrLst_Confirmed_NextOccurrenceOrder++;
        }
        else
        {
            Dem_OdrLst_Confirmed_NextOccurrenceOrder = DEM_FAIL_OCCURRENCE_NUM_INVALID;
        }
    }

    return;
}
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Dem_OdrLst_Confirmed_CheckLastOccurrenceOrder            */
/* Description   | Confirmation processing of the latest confirmed occurren */
/*               | ceorder.                                                 */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_OdrLst_Confirmed_CheckLastOccurrenceOrder
( void )
{
    /* Variable declaration */
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) orderListIndex;

    /* Failure registration number acquisition */
    if( Dem_EventMemoryRecordList.NumberOfConfirmedDTCs > (Dem_u08_OrderIndexType)0U )
    {
        orderListIndex = Dem_EventMemoryRecordList.NumberOfConfirmedDTCs - (Dem_u08_OrderIndexType)1U;      /* [GUDCHK:SETVAL]Dem_EventMemoryRecordList.NumberOfConfirmedDTCs *//* [GUD:IF_GUARDED Dem_EventMemoryRecordList.NumberOfConfirmedDTCs]orderListIndex */
        /* From the maximum value set the next order */
        Dem_OdrLst_Confirmed_NextOccurrenceOrder = Dem_OdrLst_TmpFaultOrderList[ orderListIndex ].OccurrenceOrder + (Dem_u16_OccrOrderType)1U;  /* [GUDCHK:SETVAL]Dem_EventMemoryRecordList.NumberOfConfirmedDTCs */
    }
    else
    {
        /* Initial value setting */
        Dem_OdrLst_Confirmed_NextOccurrenceOrder = DEM_FAIL_OCCURRENCE_NUM_INITIAL;
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_OdrLst_Confirmed_BringValidDataToTopEdge             */
/* Description   | Process of acquiring confirmed occurrence record inform- */
/*               | ation.                                                   */
/* Preconditions | Data consistent with confirmed record list is stored     */
/* Parameters    | [in] StartIndex :                                        */
/*               |                                                          */
/*               | [in] MaxOfFaultOrderItems :                              */
/*               |                                                          */
/* Return Value  | uint8                                                    */
/*               |        Number of items in the fault order list to sort.  */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_OrderIndexType, DEM_CODE ) Dem_OdrLst_Confirmed_BringValidDataToTopEdge
(
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) StartIndex,
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) MaxOfFaultOrderItems
)
{
    /* Variable declaration */
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) loopCount;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) numOfOrderItems;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) occurredIndex;
    VAR( Dem_s16_OrderIndexType, AUTOMATIC ) noOccurredIndex;
    VAR( Dem_s16_OrderIndexType, AUTOMATIC ) faultIndex;

    numOfOrderItems = (Dem_u08_OrderIndexType)0U;
    occurredIndex = StartIndex;                                                                                                             /* [GUD:logic]occurredIndex */
    noOccurredIndex = ( (Dem_s16_OrderIndexType)MaxOfFaultOrderItems + (Dem_s16_OrderIndexType)StartIndex ) - (Dem_s16_OrderIndexType)1;    /* [GUD:logic]noOccurredIndex */
    faultIndex = (Dem_s16_OrderIndexType)StartIndex + (Dem_s16_OrderIndexType)MaxOfFaultOrderItems;                                         /* [GUD:logic]faultIndex */

    /* Check all failed record data in descending order. */
    for( loopCount = (Dem_u08_OrderIndexType)0U; loopCount < MaxOfFaultOrderItems; loopCount++ )
    {
        faultIndex--;

        if( Dem_FaultRecordList[faultIndex].ConfirmedOccurrenceOrder == DEM_FAIL_OCCURRENCE_NUM_INVALID )   /* [GUD]faultIndex */
        {
            /* In case of the fault record that not occurred faults. */

            /* Stores the fault record information from bottom position in descending order. */
            Dem_OdrLst_TmpFaultOrderList[noOccurredIndex].FaultIndex      = DEM_FAULTINDEX_INITIAL;                                     /* [GUD]noOccurredIndex */
            Dem_OdrLst_TmpFaultOrderList[noOccurredIndex].OccurrenceOrder = Dem_FaultRecordList[faultIndex].ConfirmedOccurrenceOrder;   /* [GUD]noOccurredIndex *//* [GUD]faultIndex */

            noOccurredIndex--;
        }
        else
        {
            /* In case of the fault record that occurred faults. */

            /* Stores the fault record information from top position in ascending order. */
            Dem_OdrLst_TmpFaultOrderList[occurredIndex].FaultIndex      = (Dem_u08_FaultIndexType)faultIndex;                           /* [GUD]occurredIndex */
            Dem_OdrLst_TmpFaultOrderList[occurredIndex].OccurrenceOrder = Dem_FaultRecordList[faultIndex].ConfirmedOccurrenceOrder;     /* [GUD]occurredIndex *//* [GUD]faultIndex */

            occurredIndex = occurredIndex + (Dem_u08_OrderIndexType)1U;
            numOfOrderItems = numOfOrderItems + (Dem_u08_OrderIndexType)1U;
        }
    }

    return numOfOrderItems;
}
#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-07-29                                              */
/*  v3-0-1         :2019-10-29                                              */
/*  v4-0-0         :2020-03-19                                              */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
