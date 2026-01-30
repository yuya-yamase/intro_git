/* Dem_DTC_PFC_UpdateOrder_c(v5-5-0)                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DTC_PFC_UpdateOrder/CODE                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#if ( DEM_PFC_SUPPORT == STD_ON )
#include "../../../../inc/Dem_Pm_DataCtl.h"
#include "../../../../inc/Dem_Pm_DataCtl_OBD.h"
#include "../../../../inc/Dem_Rc_DataMng.h"
#include "Dem_DTC_PFC_local.h"

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
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE_TRUST          /*  PreInit section                     */
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_CODE_TRUST           /*  PreInit section                     */
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_DTC_GetUpdateOrderCount                              */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_OrderIndexType                                   */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_OrderIndexType, DEM_CODE ) Dem_DTC_GetUpdateOrderMaxCount
( void )
{
    VAR( Dem_EventMemoryRecordType, AUTOMATIC ) eventMemoryRecord;

    Dem_DataMngC_GetEventMemoryRecord( &eventMemoryRecord );

    return eventMemoryRecord.NumberOfConfirmedDTCs;
}

/****************************************************************************/
/* Function Name | Dem_DTC_GetUpdateOrderEventStrgIndex                     */
/* Description   | Get EventStrgIndex from Confirmed OrderTable.            */
/* Preconditions | none                                                     */
/* Parameters    | [in] ConfirmedOrderListIndex                             */
/*               |        0 - 255 : Number of ConfirmedOrderIndex           */
/*               | [out] EventStrgIndexPtr :                                */
/*               |        The event index which has been retrieved.         */
/*               |        This pointer is pointing to                       */
/*               |        Automatic area.                                   */
/*               |        DEM_EVENTSTRGINDEX_INVALID : event is not available. */
/*               | [out] FaultIndexPtr :                                    */
/*               | [out] StatusOfDTCPtr :                                   */
/*               |        StatusOfDTC value.                                */
/*               |        This pointer is pointing to                       */
/*               |        Automatic area.                                   */
/*               | [out] OrderExistPtr :                                    */
/*               |  TRUE  : Confirmed Event exists.                         */
/*               |  FALSE : Confirmed Event does not exists.                */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DTC_GetUpdateOrderEventStrgIndex
(
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) OrderListIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr,
    P2VAR( Dem_u08_FaultIndexType, AUTOMATIC, AUTOMATIC ) FaultIndexPtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) StatusOfDTCPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) OrderExistPtr
)
{
    Dem_Data_GetConfirmedOrderEventStrgIndex( OrderListIndex, EventStrgIndexPtr, FaultIndexPtr, StatusOfDTCPtr, OrderExistPtr );
    return ;
}
#endif  /* ( DEM_PFC_ORDER_MIL_SUPPORT == STD_OFF ) */


#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DTC_GetUpdateOrderCount                              */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_OrderIndexType                                   */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_OrderIndexType, DEM_CODE ) Dem_DTC_GetUpdateOrderMaxCount
( void )
{
    VAR( Dem_EventMemoryRecordType, AUTOMATIC ) eventMemoryRecord;

    Dem_DataMngC_GetEventMemoryRecord( &eventMemoryRecord );

    return eventMemoryRecord.NumberOfObdMILDTCs;
}


/****************************************************************************/
/* Function Name | Dem_DTC_GetUpdateOrderEventStrgIndex                     */
/* Description   | Get EventStrgIndex from Confirmed OrderTable.            */
/* Preconditions | none                                                     */
/* Parameters    | [in] ConfirmedOrderListIndex                             */
/*               |        0 - 255 : Number of ConfirmedOrderIndex           */
/*               | [out] EventStrgIndexPtr :                                */
/*               |        The event index which has been retrieved.         */
/*               |        This pointer is pointing to                       */
/*               |        Automatic area.                                   */
/*               |        DEM_EVENTSTRGINDEX_INVALID : event is not available. */
/*               | [out] FaultIndexPtr :                                    */
/*               | [out] StatusOfDTCPtr :                                   */
/*               |        StatusOfDTC value.                                */
/*               |        This pointer is pointing to                       */
/*               |        Automatic area.                                   */
/*               | [out] OrderExistPtr :                                    */
/*               |  TRUE  : Confirmed Event exists.                         */
/*               |  FALSE : Confirmed Event does not exists.                */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DTC_GetUpdateOrderEventStrgIndex
(
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) OrderListIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr,
    P2VAR( Dem_u08_FaultIndexType, AUTOMATIC, AUTOMATIC ) FaultIndexPtr,    /* MISRA DEVIATION */
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) StatusOfDTCPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) OrderExistPtr
)
{
    Dem_Data_GetMILOrderEventStrgIndex( OrderListIndex, EventStrgIndexPtr, StatusOfDTCPtr, OrderExistPtr );
    return ;
}

#endif  /* ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON ) */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_PFC_SUPPORT == STD_ON )    */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
