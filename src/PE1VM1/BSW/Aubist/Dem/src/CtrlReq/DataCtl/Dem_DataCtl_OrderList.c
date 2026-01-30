/* Dem_DataCtl_OrderList_c(v5-5-0)                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_OrderList/CODE                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_DataCtl_TSFFD.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Rc_OdrLst.h"
#include "Dem_DataCtl_local.h"
#include "Dem_DataCtl_TSFFD_local.h"

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

#if ( DEM_CLEAR_EVENT_NOT_ALLOWED_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_Data_AllClearFaultOrderList                          */
/* Description   | Clear processing of failure occurrence order list data.  */
/* Preconditions | The failure occurrence order list has been generated.    */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_AllClearFaultOrderList
( void )
{
#if ( DEM_TSFF_PM_SUPPORT == STD_ON )   /* [FuncSw] */
    VAR( Dem_u16_SmpRecMemIndexType, AUTOMATIC ) samplingFreezeFrameMemoryRef;
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON )   */

    /* Starts exclusion. */
    SchM_Enter_Dem_EventMemory();

    Dem_OdrLst_Fault_ClearList();

    /* Finishes exclusion. */
    SchM_Exit_Dem_EventMemory();

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )   /* [FuncSw] */
    /* Initializes time-series freeze frame related memory. */
    samplingFreezeFrameMemoryRef = Dem_SamplingFFRecordPrimaryMemory;
    Dem_Data_InitTSFFListRecordList( samplingFreezeFrameMemoryRef );
    Dem_Data_InitTSFFCtrlRecordList( samplingFreezeFrameMemoryRef );
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON )   */

    return;
}
#endif  /* ( DEM_CLEAR_EVENT_NOT_ALLOWED_SUPPORT == STD_OFF ) */

/****************************************************************************/
/* Function Name | Dem_Data_GenerateFaultOrderList                          */
/* Description   | Failure occurrence order list generation processing      */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_GenerateFaultOrderList
( void )
{
    Dem_OdrLst_Fault_ExecSort();

    /* Starts exclusion. */
    SchM_Enter_Dem_EventMemory();

    Dem_OdrLst_Fault_ApplySortedList();

    /* Finishes exclusion. */
    SchM_Exit_Dem_EventMemory();

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )   /* [FuncSw] */
    Dem_Data_GenerateTSFFLRecordList();
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON )   */

    return;
}

/****************************************************************************/
/* Function Name | Dem_Data_GetFaultIndexByOccurrenceOrder                  */
/* Description   | Gets FaultIndex from Occurrence Order.                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] OrderIndex :                                        */
/*               |        RecordNumber in search of FaultIndex.             */
/*               | [out] FaultIndexPtr :                                    */
/*               |        Next FaultIndex.                                  */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Retrieving FaultIndex is succesful.  */
/*               |        DEM_IRT_NO_MATCHING_ELEMENT : A further element - */
/*               |        is not found                                      */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetFaultIndexByOccurrenceOrder
(
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) OrderIndex,
    P2VAR( Dem_u08_FaultIndexType, AUTOMATIC, AUTOMATIC ) FaultIndexPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    SchM_Enter_Dem_EventMemory();

    /* Gets the fault index by fault occurrence order. */
    retVal = Dem_OdrLst_Fault_GetFaultIndexByOrder( OrderIndex, FaultIndexPtr );

    SchM_Exit_Dem_EventMemory();

    if( retVal == DEM_IRT_PARAM_DATA )
    {
        retVal = DEM_IRT_NO_MATCHING_ELEMENT;
    }
    else
    {
        /* No Process */
    }

    return retVal;
}


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
