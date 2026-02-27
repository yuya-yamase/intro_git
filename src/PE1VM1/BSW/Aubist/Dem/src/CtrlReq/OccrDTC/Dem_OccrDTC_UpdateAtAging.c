/* Dem_OccrDTC_c(v5-9-0)                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/OccrDTC/CODE                                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#if ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON )
#if ( DEM_DTC_OCCURRENCE_TIME_UPDATEATAGING_SUPPORT == STD_ON )

#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_DTC_DTCStatus.h"
#include "../../../inc/Dem_Pm_DataAvl.h"
#include "../../../inc/Dem_Pm_OccrDTC.h"
#include "../../../inc/Dem_Rc_OccrDTCMng.h"
#include "../../../inc/Dem_Rc_OdrLst.h"

#include "Dem_OccrDTC_local.h"

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

static FUNC( void, DEM_CODE ) Dem_OccrDTC_ClearLatchedData
( void );
static FUNC( Dem_u16_EventStrgIndexType, DEM_CODE ) Dem_OccrDTC_GetLastConfirmedEvent
( void );

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

static VAR( Dem_u08_DemBooleanType, DEM_VAR_NO_INIT ) Dem_OccrDTCUpdateFlg;
static VAR( Dem_u16_EventStrgIndexType, DEM_VAR_NO_INIT ) Dem_TmpOccrDTCEventStrgIndex;
static VAR( Dem_UdsStatusByteType, DEM_VAR_NO_INIT ) Dem_TmpOccrDTCOldDTCStatus;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>



/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_OccrDTC_Init                                         */
/* Description   | initialize function.                                     */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_OccrDTC_Init
( void )
{
    Dem_OccrDTC_ClearLatchedData();

    return;
}

/****************************************************************************/
/* Function Name | Dem_OccrDTC_Init_AfterOrderListGenerateComplete          */
/* Description   | Data confirmation start demand.                          */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_OccrDTC_Init_AfterOrderListGenerateComplete
( void )
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) lastConfirmedEventStrgIndex;

    lastConfirmedEventStrgIndex = Dem_OccrDTC_GetLastConfirmedEvent();

    Dem_OccrDTCMng_DataVerify_AfterRecordCheckComplete( lastConfirmedEventStrgIndex );

    return;
}

/****************************************************************************/
/* Function Name | Dem_OccrDTC_SetEvent                                     */
/* Description   | Sets event For OccrDTC                                   */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventStrgIndex   :                                 */
/*               | [in]  EventStrgIndexOfFaultRecordOverwritten :           */
/*               | [in]  OldDTCStatus :                                     */
/*               | [in]  NewDTCStatus :                                     */
/*               | [in]  OldDTCStatusOverwritten :                          */
/*               | [in]  FaultRecordOverwriteFlag :                         */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-9-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_OccrDTC_SetEvent
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndexOfFaultRecordOverwritten,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) OldDTCStatus,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) NewDTCStatus,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) OldDTCStatusOverwritten,
    VAR( boolean, AUTOMATIC ) FaultRecordOverwriteFlag
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) lastConfirmedEventStrgIndex;
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) dtcValue;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) changeBit;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) triggerBit;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) chekDTC;

    VAR( Dem_UdsStatusByteType, AUTOMATIC ) oldDTCStatusTmp;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) newDTCStatusTmp;

    if ( OldDTCStatus != NewDTCStatus )
    {
        dtcValue = (Dem_u32_DTCValueType)0U;

        oldDTCStatusTmp =   OldDTCStatus;
        newDTCStatusTmp =   NewDTCStatus;

        /*------------------------------------------*/
        /*  convert to output statusOfDTC.          */
        /*------------------------------------------*/
        Dem_DTC_CnvUpdateDTCStatus_ForOutput( &oldDTCStatusTmp, &newDTCStatusTmp );

        /* Check DTC configured */
        chekDTC = Dem_DataAvl_GetUDSDTCByEventStrgIndex( EventStrgIndex, &dtcValue );   /* [GUD:RET:DEM_IRT_OK] EventStrgIndex */
        if( chekDTC == DEM_IRT_OK )
        {
            /* Check the changed bit */
            changeBit = (Dem_UdsStatusByteType)( oldDTCStatusTmp ^ newDTCStatusTmp );

            /* Get bit changed from 0 to 1 */
            triggerBit = (Dem_UdsStatusByteType)( changeBit & newDTCStatusTmp );

            /* Get occurrence time record */
            eventStrgIndex = Dem_OccrDTCMng_GetMostRecentConfirmedData();
            lastConfirmedEventStrgIndex = Dem_OccrDTC_GetLastConfirmedEvent();

            /* overwritten */
            if( FaultRecordOverwriteFlag == (boolean)TRUE )
            {
                /* not confirmed */
                if( (Dem_UdsStatusByteType)( triggerBit & DEM_UDS_STATUS_CDTC ) != DEM_UDS_STATUS_CDTC )
                {
                    /* Latch data for Dcm notification */
                    Dem_TmpOccrDTCEventStrgIndex = EventStrgIndexOfFaultRecordOverwritten;
                    Dem_TmpOccrDTCOldDTCStatus = OldDTCStatusOverwritten;
                    Dem_OccrDTCUpdateFlg = DEM_BOOLEAN_TRUE;
                }
                else
                {
                    /* confirmed */
                    if( eventStrgIndex != EventStrgIndex )
                    {
                        /* Set occurrence time record */
                        Dem_OccrDTCMng_SetMostRecentConfirmedData( EventStrgIndex, DEM_UPDNVM_UPD_NVM_RAMDIFF );    /* [GUD]EventStrgIndex */

                        /* Notify DCM */
                        Dem_OccrDTC_NotifyDTCStatusChanged( EventStrgIndex, oldDTCStatusTmp, newDTCStatusTmp );     /* [GUD]EventStrgIndex */

                        /* Clear latch data */
                        Dem_OccrDTC_ClearLatchedData();
                    }
                }
            }
            else
            {
                /* not overwritten and confirmed */
                if( (Dem_UdsStatusByteType)( triggerBit & DEM_UDS_STATUS_CDTC ) == DEM_UDS_STATUS_CDTC )
                {
                    if( eventStrgIndex != EventStrgIndex )
                    {
                        if( EventStrgIndex == lastConfirmedEventStrgIndex )
                        {
                            /* Set occurrence time record */
                            Dem_OccrDTCMng_SetMostRecentConfirmedData( EventStrgIndex, DEM_UPDNVM_UPD_NVM_RAMDIFF );    /* [GUD]EventStrgIndex */

                            /* Notify DCM */
                            Dem_OccrDTC_NotifyDTCStatusChanged( EventStrgIndex, oldDTCStatusTmp, newDTCStatusTmp );     /* [GUD]EventStrgIndex */

                            /* Clear latch data */
                            Dem_OccrDTC_ClearLatchedData();
                        }
                    }
                }
            }
        }
        else
        {
            /* DTC is not configured and overwritten */
            if( FaultRecordOverwriteFlag == (boolean)TRUE )
            {
                /* Latch data for Dcm notification */
                Dem_TmpOccrDTCEventStrgIndex = EventStrgIndexOfFaultRecordOverwritten;
                Dem_TmpOccrDTCOldDTCStatus = OldDTCStatusOverwritten;
                Dem_OccrDTCUpdateFlg = DEM_BOOLEAN_TRUE;
            }
        }
    }
    return;
}

/****************************************************************************/
/* Function Name | Dem_OccrDTC_LatchOccrDTCRecord_ClearDTC                  */
/* Description   | Latch OccrDTC                                            */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_OccrDTC_LatchOccrDTCRecord_ClearDTC
( void )
{
    Dem_OccrDTC_LatchOccrDTCRecord();
    return;
}

/****************************************************************************/
/* Function Name | Dem_OccrDTC_UpdateOccrDTCRecord_ClearDTC                 */
/* Description   | Set and judge OccrDTC to notify DCM                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCGroup                                            */
/*               | [in] ClearResult                                         */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_OccrDTC_UpdateOccrDTCRecord_ClearDTC
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup,     /* MISRA DEVIATION */
    VAR( Dem_u08_ClearCompleteType, AUTOMATIC ) ClearResult
)
{
    if(( ClearResult == DEM_CLEARCOMPLETE_OK ) || ( ClearResult == DEM_CLEARCOMPLETE_SWCERROR ))
    {
        /*  clearDTC success.           */
        Dem_OccrDTC_UpdateOccrDTCRecord();
    }
    else
    {
        /*  error occurred at clearDTC.(DEM_CLEARCOMPLETE_NVMERROR)   */
        /*  only release latched information.                   */
        Dem_OccrDTC_ClearLatchedData();
    }
    return ;
}

/****************************************************************************/
/* Function Name | Dem_OccrDTC_UpdateOccrDTCRecord_InitializeEventStatus    */
/* Description   | Set and judge OccrDTC to notify DCM                      */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventStrgIndex   :                                 */
/*               | [in]  OldDTCStatus :                                     */
/*               | [in]  NewDTCStatus :                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_OccrDTC_UpdateOccrDTCRecord_InitializeEventStatus
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,    /* MISRA DEVIATION */
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) OldDTCStatus,           /* MISRA DEVIATION */
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) NewDTCStatus            /* MISRA DEVIATION */
)
{
    /*  no process          */
    return ;
}


/****************************************************************************/
/* Function Name | Dem_OccrDTC_LatchOccrDTCRecord                           */
/* Description   | Latch OccrDTC                                            */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_OccrDTC_LatchOccrDTCRecord
( void )
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) lastConfirmedEventStrgIndex;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) occrDTCStatusOfDTC;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;

    /* check already latched or not */
    if( Dem_OccrDTCUpdateFlg == DEM_BOOLEAN_FALSE )
    {
        /* Get last EventIndex registered Confirmed_Orderlist */
        eventStorageNum = Dem_PrimaryMemEventStorageNum;
        lastConfirmedEventStrgIndex = Dem_OccrDTC_GetLastConfirmedEvent();

        /* Check Index is valid or not */
        if( lastConfirmedEventStrgIndex < eventStorageNum )
        {
            /* Get StatusOfDTC of corresponding event */
            (void)Dem_DataMngC_GetER_StatusOfDTC( lastConfirmedEventStrgIndex, &occrDTCStatusOfDTC );    /* no return check required */

            /* Latch data for Dcm notification */
            Dem_TmpOccrDTCEventStrgIndex = lastConfirmedEventStrgIndex;
            Dem_TmpOccrDTCOldDTCStatus = occrDTCStatusOfDTC;
            Dem_OccrDTCUpdateFlg = DEM_BOOLEAN_TRUE;
        }
        else
        {
            /* Set invalid value */
            Dem_OccrDTC_ClearLatchedData();
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_OccrDTC_UpdateOccrDTCRecord                          */
/* Description   | Set and judge OccrDTC to notify DCM                      */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_OccrDTC_UpdateOccrDTCRecord
( void )
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) lastConfirmedEventStrgIndex;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) newDTCStatus;

    if( Dem_OccrDTCUpdateFlg == DEM_BOOLEAN_TRUE )
    {
        /* Get occurrence time record */
        eventStrgIndex = Dem_OccrDTCMng_GetMostRecentConfirmedData();
        /* Get last EventIndex registered Confirmed_Orderlist */
        lastConfirmedEventStrgIndex = Dem_OccrDTC_GetLastConfirmedEvent();
        if( lastConfirmedEventStrgIndex != Dem_TmpOccrDTCEventStrgIndex )
        {
            if( eventStrgIndex != lastConfirmedEventStrgIndex )
            {
                /* Set OccrDTC Record */
                Dem_OccrDTCMng_SetMostRecentConfirmedData( lastConfirmedEventStrgIndex, DEM_UPDNVM_UPD_NVM_RAMDIFF );
                (void)Dem_DataMngC_GetER_StatusOfDTC( Dem_TmpOccrDTCEventStrgIndex, &newDTCStatus );    /* no return check required */
                /* Notify Dcm */
                Dem_OccrDTC_NotifyDTCStatusChanged( Dem_TmpOccrDTCEventStrgIndex, Dem_TmpOccrDTCOldDTCStatus, newDTCStatus );
                /* Clear latch data */
                Dem_OccrDTC_ClearLatchedData();
            }
        }
        else
        {
            /* Clear latch data */
            Dem_OccrDTC_ClearLatchedData();
        }
    }

    return;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dem_OccrDTC_ClearLatchedData                             */
/* Description   | initialize function.                                     */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_OccrDTC_ClearLatchedData
( void )
{
    Dem_OccrDTCUpdateFlg              = DEM_BOOLEAN_FALSE;
    Dem_TmpOccrDTCEventStrgIndex      = DEM_EVENTSTRGINDEX_INVALID;
    Dem_TmpOccrDTCOldDTCStatus        = DEM_DTCSTATUS_BYTE_ALL_OFF;

    return;
}

/****************************************************************************/
/* Function Name | Dem_OccrDTC_GetLastConfirmedEvent                        */
/* Description   | Get last confirmed event                                 */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u16_EventStrgIndexType :                             */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u16_EventStrgIndexType, DEM_CODE ) Dem_OccrDTC_GetLastConfirmedEvent
( void )
{
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) dtcValue;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) lastConfirmedEventStrgIndex;
    VAR( Dem_s16_OrderIndexType, AUTOMATIC ) orderListIndexSigned;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) orderListIndex;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetFaultRegistOrderListData;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) chekDTC;
    VAR( boolean, AUTOMATIC ) searchEnd;

    lastConfirmedEventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;

    /*  get last order index.       */
    orderListIndex = Dem_OdrLst_Confirmed_GetLastOccurrenceOrder();

    searchEnd   =   (boolean)FALSE;

    for( orderListIndexSigned = ( Dem_s16_OrderIndexType )orderListIndex; orderListIndexSigned >= ( Dem_s16_OrderIndexType )0U; orderListIndexSigned-- )
    {
        retGetFaultRegistOrderListData = Dem_OdrLst_Confirmed_GetFaultIndexByOrder( ( Dem_u08_OrderIndexType )orderListIndexSigned, &faultIndex );

        if( retGetFaultRegistOrderListData == DEM_IRT_OK )
        {
           /* Convert faultIndex into eventIndex */
            (void)Dem_DataMngC_GetFR_EventStrgIndex( faultIndex, &lastConfirmedEventStrgIndex );    /* no return check required */

            /*  get DTC value.          */
            chekDTC = Dem_DataAvl_GetUDSDTCByEventStrgIndex( lastConfirmedEventStrgIndex, &dtcValue );  /* [GUD:RET:DEM_IRT_OK] lastConfirmedEventStrgIndex */

            if( chekDTC == DEM_IRT_OK )
            {
                searchEnd   =   (boolean)TRUE;
            }
            else
            {
                lastConfirmedEventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
            }
        }
        else
        {
            lastConfirmedEventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
            searchEnd   =   (boolean)TRUE;
        }

        if ( searchEnd == (boolean)TRUE )
        {
            break;
        }
    }

    return lastConfirmedEventStrgIndex;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* ( DEM_DTC_OCCURRENCE_TIME_UPDATEATAGING_SUPPORT == STD_ON ) */
#endif /* ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
