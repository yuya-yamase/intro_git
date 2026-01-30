/* Dem_DataCtl_OBD_OrderList_MIL_c(v5-3-0)                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_OBD_OrderList_MIL/CODE                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_Rc_OdrLst.h"
#include "Dem_DataCtl_local.h"

#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )

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
/* Function Name | Dem_Data_AllClearMILFaultOrderList                       */
/* Description   | Clear processing of MIL failure occurrence order         */
/*               | list data.                                               */
/* Preconditions | The MIL failure occurrence order list has been           */
/*               | generated.                                               */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_AllClearMILFaultOrderList
( void )
{
    /* Starts exclusion. */
    SchM_Enter_Dem_EventMemory();

    Dem_OdrLst_MIL_ClearList();

    /* Finishes exclusion. */
    SchM_Exit_Dem_EventMemory();

    return;
}
#endif  /* ( DEM_CLEAR_EVENT_NOT_ALLOWED_SUPPORT == STD_OFF ) */

/****************************************************************************/
/* Function Name | Dem_Data_GenerateMILFaultOrderList                       */
/* Description   | MIL Failure occurrence order list generation             */
/*               | processing.                                              */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_GenerateMILFaultOrderList
( void )
{
    Dem_OdrLst_MIL_ExecSort();

    /* Starts exclusion. */
    SchM_Enter_Dem_EventMemory();

    Dem_OdrLst_MIL_ApplySortedList();

    /* Finishes exclusion. */
    SchM_Exit_Dem_EventMemory();

    return;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON ) */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-07-29                                              */
/*  v3-0-1         :2019-10-29                                              */
/*  v4-0-0         :2020-03-19                                              */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
