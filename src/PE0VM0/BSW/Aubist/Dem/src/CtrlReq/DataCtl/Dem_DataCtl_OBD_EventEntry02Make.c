/* Dem_DataCtl_OBD_EventEntry02Make_c(v5-3-0)                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_OBD_EventEntry02Make/CODE                     */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )
#include "../../../cfg/Dem_Cfg.h"
#include "../../../cfg/Dem_Data_Cfg.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Pm_DataCtl_OBD.h"
#include "../../../inc/Dem_Rc_OdrLst.h"
#include "../../../inc/Dem_Utl.h"
#include "Dem_DataCtl_local.h"
#include "Dem_DataCtl_EventEntry_local.h"

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

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Data_SetNextMILFaultOccurrenceOrderToTmp
( void );
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */

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

#if ( DEM_INDICATOR_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_ClearMILOccurrenceOrderInfo                     */
/* Description   | Save MIL occurrence order information in a temporary ar- */
/*               | ea.                                                      */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | boolean                                                  */
/*               |        TRUE : Aging permission                           */
/*               |        FALSE : Aging prohibition                         */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_ClearMILOccurrenceOrderInfo
( void )
{
    Dem_TmpEventMemoryEntry.FaultRecord.MILOccurrenceOrder = DEM_FAIL_OCCURRENCE_NUM_INVALID;
    Dem_TmpEventMemoryEntry.EventMemoryRecordList.NumberOfObdMILDTCs = Dem_TmpEventMemoryEntry.EventMemoryRecordList.NumberOfObdMILDTCs - (Dem_u08_OrderIndexType)1U;
    Dem_TmpEventMemoryEntry.ResultOfGetMILFaultRegistLocation = DEM_IRT_NG;
    return;
}
#endif /* ( DEM_INDICATOR_USE == STD_ON )   */

/****************************************************************************/
/* Function Name | Dem_Data_SetNewMILOccurrenceToTmp                        */
/* Description   | Save to new primary area (temporary) before setting RAM  */
/*               | (For MIL Occurrence Fault)                               */
/* Preconditions |                                                          */
/* Parameters    | MILOccurFlag                                             */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_SetNewMILOccurrenceToTmp
(
    VAR( boolean, AUTOMATIC ) MILOccurFlag
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetting;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) orderListIndex;
    VAR( Dem_u16_OccrOrderType, AUTOMATIC ) milOccurrenceOrder;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) failRecordNum;

    if( MILOccurFlag == (boolean)TRUE )
    {
        retVal = DEM_IRT_NG;
        failRecordNum = (Dem_u08_OrderIndexType)Dem_FailRecordNum;

        if( Dem_TmpEventMemoryEntry.EventMemoryRecordList.NumberOfObdMILDTCs < failRecordNum )
        {
            orderListIndex = Dem_TmpEventMemoryEntry.EventMemoryRecordList.NumberOfObdMILDTCs;
            milOccurrenceOrder = DEM_FAIL_OCCURRENCE_NUM_INVALID;
            resultOfGetting = Dem_OdrLst_MIL_GetOccrOrderValue( orderListIndex, &milOccurrenceOrder );
            if( resultOfGetting == DEM_IRT_OK )
            {
                Dem_TmpEventMemoryEntry.FaultRecord.MILOccurrenceOrder = milOccurrenceOrder;
                Dem_TmpEventMemoryEntry.EventMemoryRecordList.NumberOfObdMILDTCs++;
                retVal = DEM_IRT_OK;
            }
            Dem_TmpEventMemoryEntry.ResultOfGetMILFaultRegistLocation = resultOfGetting;
        }
        else
        {
#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )    /* [FuncSw] */
            Dem_Data_SetNextMILFaultOccurrenceOrderToTmp();
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */
            retVal = DEM_IRT_OK;
        }
    }
    else
    {
        retVal = DEM_IRT_OK;
    }
    return retVal;
}

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_SetNextMILFaultOccurrenceOrder                  */
/* Description   | Gets next MIL fault occurrence order and retains.        */
/*               | overwrite.                                               */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_SetNextMILFaultOccurrenceOrderToTmp
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetNextOrder;
    VAR( Dem_u16_OccrOrderType, AUTOMATIC ) milOccurrenceOrder;

    /* Gets a MIL fault occurrencd order from MIL fault order list. */
    resultOfGetNextOrder = Dem_OdrLst_MIL_GetNextOccurrenceOrder( &milOccurrenceOrder );

    if( resultOfGetNextOrder == DEM_IRT_OK )
    {
        /* Retains the MIL fault occurrence order due to add one to next occurrence order when storing from temporary area to RAM, */
        Dem_EventDisplacement.NextMILFaultOccurrenceOrder = milOccurrenceOrder;

        /* Retains the MIL fault occurrence order to fault record of temporary area. */
        Dem_TmpEventMemoryEntry.FaultRecord.MILOccurrenceOrder = milOccurrenceOrder;
    }

    return;
}
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-07-29                                              */
/*  v3-0-1         :2019-10-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
