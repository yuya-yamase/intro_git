/* Dem_OccrDTC_UpdateWithoutAging_c(v5-9-0)                                 */
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
#if ( DEM_DTC_OCCURRENCE_TIME_UPDATEATAGING_SUPPORT == STD_OFF )
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


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

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
    /*  no process.     */
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
    Dem_OccrDTCMng_DataVerify_AfterRecordCheckComplete( DEM_EVENTSTRGINDEX_INVALID );

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
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) dtcValue;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) currentEventStrgIndex;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) changeBit;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) triggerBit;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) chekDTC;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) newDTCStatusOverwritten;
    VAR( boolean, AUTOMATIC ) updateFlag;

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

        updateFlag  =   (boolean)FALSE;

        /* Check DTC configured */
        chekDTC = Dem_DataAvl_GetUDSDTCByEventStrgIndex( EventStrgIndex, &dtcValue );   /* [GUD:RET:DEM_IRT_OK] EventStrgIndex */
        if( chekDTC == DEM_IRT_OK )
        {
            /* Check the changed bit */
            changeBit = (Dem_UdsStatusByteType)( oldDTCStatusTmp ^ newDTCStatusTmp );

            /* Get bit changed from 0 to 1 */
            triggerBit = (Dem_UdsStatusByteType)( changeBit & newDTCStatusTmp );

            /* confirmed */
            if( (Dem_UdsStatusByteType)( triggerBit & DEM_UDS_STATUS_CDTC ) == DEM_UDS_STATUS_CDTC )
            {
                /* Set occurrence time record */
                Dem_OccrDTCMng_SetMostRecentConfirmedDataAtSetEvent( EventStrgIndex );                      /* [GUD]EventStrgIndex */

                /* Notify DCM */
                Dem_OccrDTC_NotifyDTCStatusChanged( EventStrgIndex, oldDTCStatusTmp, newDTCStatusTmp );     /* [GUD]EventStrgIndex */

                updateFlag  =   (boolean)TRUE;
            }
        }

        if ( updateFlag == (boolean)FALSE )
        {
            if( FaultRecordOverwriteFlag == (boolean)TRUE )
            {
                /*  overwrite.      */
                currentEventStrgIndex  =   Dem_OccrDTCMng_GetMostRecentConfirmedData();
                if ( EventStrgIndexOfFaultRecordOverwritten == currentEventStrgIndex )
                {
                    /*  get statusOfDTC.                        */
                    (void)Dem_DataMngC_GetER_StatusOfDTC( EventStrgIndexOfFaultRecordOverwritten, &newDTCStatusOverwritten );    /* no return check required */

                    /*  clear of most recentry event.           */
                    Dem_OccrDTC_UpdateOccrDTCRecord_InitializeEventStatus( EventStrgIndexOfFaultRecordOverwritten, OldDTCStatusOverwritten, newDTCStatusOverwritten );
                }
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
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_OccrDTC_LatchOccrDTCRecord_ClearDTC
( void )
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) oldDTCStatus;

    /* Get occurrence time record */
    eventStrgIndex  =   Dem_OccrDTCMng_GetMostRecentConfirmedData();
    oldDTCStatus    =   DEM_DTCSTATUS_BYTE_DEFAULT;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;
    if ( eventStrgIndex < eventStorageNum )                                                                 /* [GUD:if]eventStrgIndex */
    {
        (void)Dem_DataMngC_GetER_StatusOfDTC( eventStrgIndex, &oldDTCStatus );  /* no return check required */
    }
    Dem_TmpOccrDTCEventStrgIndex    =   eventStrgIndex;
    Dem_TmpOccrDTCOldDTCStatus      =   oldDTCStatus;

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
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup,
    VAR( Dem_u08_ClearCompleteType, AUTOMATIC ) ClearResult
)
{
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) newDTCStatus;
    VAR( boolean, AUTOMATIC ) updateFlag;

    if(( ClearResult == DEM_CLEARCOMPLETE_OK ) || ( ClearResult == DEM_CLEARCOMPLETE_SWCERROR ))
    {
        /*  clearDTC success.           */
        if( DTCGroup == DEM_DTC_GROUP_EMISSION_REL_DTCS )
        {
            updateFlag  =   Dem_OccrDTCMng_ClearMostRecentConfirmedData_ObdDTC();
        }
        else
        {
            updateFlag  =   Dem_OccrDTCMng_ClearMostRecentConfirmedData_AllDTC();
        }

        if ( updateFlag == (boolean)TRUE )
        {
            /*  get statusOfDTC.                        */
            (void)Dem_DataMngC_GetER_StatusOfDTC( Dem_TmpOccrDTCEventStrgIndex, &newDTCStatus );    /* no return check required */

            /* Notify DCM */
            Dem_OccrDTC_NotifyDTCStatusChanged( Dem_TmpOccrDTCEventStrgIndex, Dem_TmpOccrDTCOldDTCStatus, newDTCStatus );

            /*  update record.                          */
            Dem_OccrDTCMng_UpdateRecord();
        }
    }
    else
    {
        /*  error occurred at clearDTC.(DEM_CLEARCOMPLETE_NVMERROR)   */
        /*  no update information.                              */
    }

    Dem_TmpOccrDTCEventStrgIndex    =   DEM_EVENTSTRGINDEX_INVALID;
    Dem_TmpOccrDTCOldDTCStatus      =   DEM_DTCSTATUS_BYTE_DEFAULT;

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
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) OldDTCStatus,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) NewDTCStatus
)
{
    VAR( boolean, AUTOMATIC ) updateMostRecentryFlag;

    /*  clear target event.             */
    updateMostRecentryFlag  =   Dem_OccrDTCMng_ClearMostRecentConfirmedData_EventStrgIndex( EventStrgIndex );

    if ( updateMostRecentryFlag == (boolean)TRUE )
    {
        /* Notify DCM */
        Dem_OccrDTC_NotifyDTCStatusChanged( EventStrgIndex, OldDTCStatus, NewDTCStatus );
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dem_OccrDTC_LatchOccrDTCRecord                           */
/* Description   | Latch OccrDTC                                            */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_OccrDTC_LatchOccrDTCRecord
( void )
{
    /*  no process.     */
    return;
}

/****************************************************************************/
/* Function Name | Dem_OccrDTC_UpdateOccrDTCRecord                          */
/* Description   | Set and judge OccrDTC to notify DCM                      */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_OccrDTC_UpdateOccrDTCRecord
( void )
{
    /*  no process.     */
    return;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_DTC_OCCURRENCE_TIME_UPDATEATAGING_SUPPORT == STD_OFF )     */
#endif /* ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
