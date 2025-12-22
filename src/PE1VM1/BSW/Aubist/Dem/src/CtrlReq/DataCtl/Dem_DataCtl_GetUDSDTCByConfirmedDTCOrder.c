/* Dem_DataCtl_GetUDSDTCByConfirmedDTCOrder_c(v5-10-0)                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_GetUDSDTCByConfirmedDTCOrder/CODE             */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#if ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )
#include <Dem/Dem_Common.h>

#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Pm_DataAvl.h"
#include "../../../inc/Dem_Rc_OdrLst.h"
#include "../../../inc/Dem_Rc_DataMng.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_DataAvl.h"
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

/****************************************************************************/
/* Function Name | Dem_Data_GetConfirmedUDSDTCAndOrder                      */
/* Description   | Get ConfirmedUDSDTC and ConfirmedOrder.                  */
/* Preconditions | none                                                     */
/* Parameters    | [in/out] ConfirmedOrderListIndexPtr                      */
/*               | [out] ConfirmedDTCPtr :                                  */
/*               | [out] ConfirmedOccurrenceOrderPtr :                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |      DEM_IRT_OK :                                        */
/*               |      DEM_IRT_NO_MATCHING_ELEMENT :                       */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | new created.                                             */
/*   v5-10-0     | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetConfirmedUDSDTCAndOrder
(
    P2VAR( Dem_u08_OrderIndexType, AUTOMATIC, AUTOMATIC ) ConfirmedOrderListIndexPtr,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) ConfirmedDTCPtr,
    P2VAR( Dem_u16_OccrOrderType, AUTOMATIC, AUTOMATIC ) ConfirmedOccurrenceOrderPtr
)
{
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) dtcValue;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) orderListIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetFaultRegistOrderListData;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( boolean, AUTOMATIC ) availableStatus;
    VAR( boolean, AUTOMATIC ) resultValidateDTC;
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) misfireEventKind;
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */

    retVal = DEM_IRT_NO_MATCHING_ELEMENT;

    failRecordNum = Dem_FailRecordNum;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    for( orderListIndex = *ConfirmedOrderListIndexPtr; orderListIndex < failRecordNum; orderListIndex++ )  /* [GUD:for]orderListIndex */
    {
        retGetFaultRegistOrderListData = Dem_OdrLst_Confirmed_GetFaultIndexByOrder( orderListIndex, &faultIndex );  /* [GUD:RET:DEM_IRT_OK]faultIndex */
        if( retGetFaultRegistOrderListData == DEM_IRT_OK )
        {
            (void)Dem_DataMngC_GetFR_EventStrgIndex( faultIndex, &eventStrgIndex );     /* no return check required */  /* [GUD]faultIndex */
            if( eventStrgIndex < eventStorageNum )      /* [GUD:if]eventStrgIndex */
            {
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                misfireEventKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( eventStrgIndex );
                if( misfireEventKind != (boolean)TRUE )
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */
                {
                    availableStatus = Dem_DataAvl_GetEvtAvl_InEvtStrgGrp( eventStrgIndex );
                    if( availableStatus == (boolean)TRUE )
                    {
                        dtcValue = Dem_CfgInfoPm_GetUdsDTCValue( eventStrgIndex );
                        resultValidateDTC = Dem_DataAvl_ValidateDTC( dtcValue );
                        if( resultValidateDTC == (boolean)TRUE )
                        {
                            *ConfirmedOrderListIndexPtr = orderListIndex;
                            *ConfirmedDTCPtr = dtcValue;
                            *ConfirmedOccurrenceOrderPtr = Dem_DataMngC_ConfirmedOccurrenceOrder( faultIndex ); /* [GUD]faultIndex */

                            retVal = DEM_IRT_OK;
                            break;
                        }
                    }
                }
            }
        }
    }

    return retVal;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT== STD_ON )   */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
