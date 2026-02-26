/* Dem_Control_NotifyAvailable_c(v5-3-0)                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_NotifyAvailable/CODE                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#if ( DEM_EVENT_AVAILABILITY_FIM_REPORT == STD_ON )
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_Pm_MonSts.h"
#include "../../../inc/Dem_CmnLib_Control_AsyncReq.h"


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
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_Control_NotifyEventAvailable                         */
/* Description   | Asynchronous processing function of SetEventAvailable.   */
/* Preconditions | none                                                     */
/* Parameters    | [in] Index       : Event identifier.                     */
/*               | [in] Status      : Available status of the event.        */
/*               | [in] DataBuffPtr :                                       */
/* Return Value  | Dem_u08_AsyncExecReturnType                              */
/*               |       : See the description of the return value of       */
/*               |         "DemAsyncReqFncPTR" in Dem_CmnLib_Control_AsyncReq.h.   */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_Control_NotifyEventAvailable
(
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr    /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_AsyncExecReturnType, AUTOMATIC ) retVal;

    /* Set return value. */
    /* Fault record is not updated, No need re-generate orderlist, Continue asynchronous processing. */
    retVal = ( DEM_ASYNCRET_NOUPD_FR | DEM_ASYNCRET_NONEED_REGEN_ODR | DEM_ASYNCRET_CONTINUE_ASYNC_PROC );

    Dem_MonSts_NotifyEventAvailable( (Dem_u16_EventCtrlIndexType)Index, (boolean)Status );

    return retVal;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_EVENT_AVAILABILITY_FIM_REPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
