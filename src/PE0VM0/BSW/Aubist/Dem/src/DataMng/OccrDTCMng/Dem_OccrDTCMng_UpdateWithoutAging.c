/* Dem_OccrDTCMng_UpdateWithoutAging_c(v5-5-0)                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Dem_OccrDTCMng_UpdateWithoutAging_c/CODE              */
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
#include "../../../cfg/Dem_NvM_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Pm_DataAvl.h"
#include "../../../inc/Dem_Rc_ClrInfoMng.h"
#include "../../../inc/Dem_Rc_RecMngCmn.h"
#include "../../../inc/Dem_Rc_OccrDTCMng.h"
#include "../../../inc/Dem_Rc_RecMngCmn_Table.h"
#include "Dem_OccrDTCMng_local.h"

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

static FUNC( boolean, DEM_CODE ) Dem_OccrDTCMng_ClearMostRecentConfirmedData_NotAvailable
( void );

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#define DEM_START_SEC_VAR_SAVED_ZONE
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_VAR_SAVED_ZONE
#include <Dem_MemMap.h>


/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_OccrDTCMng_DataVerify_AfterRecordCheckComplete       */
/* Description   | Data confirmation start demand.                          */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |          DEM_IRT_OK      : DataVerify completed.         */
/*               |          DEM_IRT_PENDING : Continue DataVerify.          */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_OccrDTCMng_DataVerify_AfterRecordCheckComplete
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) LastConfirmedEventStrgIndex    /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) clrInfoNvmReadResult;
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) clrInfoRecValue;
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) clrInfoObdRecValue;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindOccrDTC;
    VAR( boolean, AUTOMATIC ) updateFlag;

    recMngCmnKindOccrDTC = Dem_RecMngCmnKindOccrDTC;

    clrInfoNvmReadResult = Dem_ClrInfoMng_GetNvmReadResult();
    clrInfoRecValue      = Dem_ClrInfoMng_GetClearID();
    clrInfoObdRecValue   = Dem_ClrInfoMng_GetObdClearID();

    /* Check ClrInfo Recored */
    if( clrInfoNvmReadResult == DEM_IRT_OK )
    {
        /*  only update SAVED_ZONE. no update NvM.      */
        if( Dem_OccrDTCRecord.ClearID != clrInfoRecValue )
        {
            (void)Dem_OccrDTCMng_ClearMostRecentConfirmedData_AllDTC(); /* no return check required */
        }
        else if( Dem_OccrDTCRecord.ObdClearID != clrInfoObdRecValue )
        {
            (void)Dem_OccrDTCMng_ClearMostRecentConfirmedData_ObdDTC(); /* no return check required */
        }
        else
        {
            /* No Process */
        }
    }
    else
    {
        Dem_OccrDTCRecord.ConfirmedEventStrgIndex        = DEM_EVENTSTRGINDEX_INVALID;
        Dem_OccrDTCRecord.ConfirmedNonOBDEventStrgIndex  = DEM_EVENTSTRGINDEX_INVALID;
        Dem_OccrDTCRecord.ClearID    = clrInfoRecValue;
        Dem_OccrDTCRecord.ObdClearID = clrInfoObdRecValue;

        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindOccrDTC, ( Dem_u16_RecordIndexType )0U );
    }

    /*  Check data of confirmed.                    */
    /*  if SAVED_ZONE area updated, update NvM.     */
    updateFlag  =   Dem_OccrDTCMng_ClearMostRecentConfirmedData_NotAvailable();
    if ( updateFlag == (boolean)TRUE )
    {
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindOccrDTC, ( Dem_u16_RecordIndexType )0U );
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dem_OccrDTCMng_UpdateRecord                              */
/* Description   | Set the Most Recent Confirmed Data.                      */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | Set argument to OccrDTC Record.                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_OccrDTCMng_UpdateRecord
( void )
{
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindOccrDTC;

    recMngCmnKindOccrDTC = Dem_RecMngCmnKindOccrDTC;

    Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindOccrDTC, ( Dem_u16_RecordIndexType )0U );

    return;
}


/****************************************************************************/
/* Function Name | Dem_OccrDTCMng_SetMostRecentConfirmedDataAtSetEvent      */
/* Description   | Set the Most Recent Confirmed Data.                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/* Return Value  | void                                                     */
/* Notes         | Set argument to OccrDTC Record.                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | rename from Dem_OccrDTCMng_SetMostRecentConfirmedData(v5-3-0).*/
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_OccrDTCMng_SetMostRecentConfirmedDataAtSetEvent
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindOccrDTC;
    VAR( boolean, AUTOMATIC ) eventOBDKind;

    if( Dem_OccrDTCRecord.ConfirmedEventStrgIndex != EventStrgIndex )
    {
        Dem_OccrDTCRecord.ConfirmedEventStrgIndex = EventStrgIndex;
        Dem_OccrDTCRecord.ObdClearID              = Dem_ClrInfoMng_GetObdClearID();
        Dem_OccrDTCRecord.ClearID                 = Dem_ClrInfoMng_GetClearID();

        /*  Get event kind of OBD.      */
        eventOBDKind    =   Dem_CfgInfoPm_CheckEventKindOfOBD_InEvtStrgGrp( EventStrgIndex );
        if( eventOBDKind != (boolean)TRUE ) /*  nonOBD      */
        {
            Dem_OccrDTCRecord.ConfirmedNonOBDEventStrgIndex = EventStrgIndex;
        }

        recMngCmnKindOccrDTC = Dem_RecMngCmnKindOccrDTC;
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindOccrDTC, ( Dem_u16_RecordIndexType )0U );
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_OccrDTCMng_ClearMostRecentConfirmedData_EventStrgIndex*/
/* Description   | Clear All DTC                                            */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | boolean                                                  */
/*               |          TRUE    : update most recentry data.            */
/*               |          FALSE   : no update most recentry data.         */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_OccrDTCMng_ClearMostRecentConfirmedData_EventStrgIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindOccrDTC;
    VAR( boolean, AUTOMATIC ) updateFlag;
    VAR( boolean, AUTOMATIC ) updateMostRecentryFlag;

    updateFlag                  =   (boolean)FALSE;
    updateMostRecentryFlag      =   (boolean)FALSE;

    if ( EventStrgIndex == Dem_OccrDTCRecord.ConfirmedEventStrgIndex )
    {
        /*  clear event.                        */
        Dem_OccrDTCRecord.ConfirmedEventStrgIndex       = DEM_EVENTSTRGINDEX_INVALID;
        Dem_OccrDTCRecord.ConfirmedNonOBDEventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
        updateFlag              =   (boolean)TRUE;
        updateMostRecentryFlag  =   (boolean)TRUE;
    }
    else
    {
        /*  nonOBD data ?                           */
        if ( EventStrgIndex == Dem_OccrDTCRecord.ConfirmedNonOBDEventStrgIndex )
        {
            Dem_OccrDTCRecord.ConfirmedNonOBDEventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
            updateFlag              =   (boolean)TRUE;
        }
    }

    if ( updateFlag == (boolean)TRUE )
    {
        Dem_OccrDTCRecord.ClearID                           = Dem_ClrInfoMng_GetClearID();
        Dem_OccrDTCRecord.ObdClearID                        = Dem_ClrInfoMng_GetObdClearID();
        recMngCmnKindOccrDTC = Dem_RecMngCmnKindOccrDTC;

        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindOccrDTC, ( Dem_u16_RecordIndexType )0U );

    }
    return updateMostRecentryFlag;
}


/****************************************************************************/
/* Function Name | Dem_OccrDTCMng_ClearMostRecentConfirmedData_AllDTC       */
/* Description   | Clear All DTC                                            */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | boolean                                                  */
/*               |          TRUE    : update data.                          */
/*               |          FALSE   : no update data.                       */
/* Notes         | update NvM is not execute this function.                 */
/*               | after this function called, caller call Dem_OccrDTCMng_UpdateRecord().   */
/*               | at Dem_OccrDTCMng_UpdateRecord(), update NvM.            */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_OccrDTCMng_ClearMostRecentConfirmedData_AllDTC
( void )
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( boolean, AUTOMATIC ) clearAllowedFlag;
    VAR( boolean, AUTOMATIC ) clearAllowedFlag_nonOBD;
    VAR( boolean, AUTOMATIC ) updateFlag;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;
    clearAllowedFlag            =   (boolean)FALSE;
    clearAllowedFlag_nonOBD     =   (boolean)FALSE;
    updateFlag                  =   (boolean)FALSE;

    /*----------------------------------------------*/
    /*  check most recentry data.                   */
    /*----------------------------------------------*/
    if ( Dem_OccrDTCRecord.ConfirmedEventStrgIndex < eventStorageNum )
    {
        clearAllowedFlag        =   Dem_CfgInfoPm_ClearAllowed_InEvtStrgGrp( Dem_OccrDTCRecord.ConfirmedEventStrgIndex );
    }
    /*----------------------------------------------*/
    /*  check most recentry nonOBD data.            */
    /*----------------------------------------------*/
    if ( Dem_OccrDTCRecord.ConfirmedNonOBDEventStrgIndex < eventStorageNum )
    {
        clearAllowedFlag_nonOBD =   Dem_CfgInfoPm_ClearAllowed_InEvtStrgGrp( Dem_OccrDTCRecord.ConfirmedNonOBDEventStrgIndex );
    }

    if ( clearAllowedFlag == (boolean)TRUE )
    {
        /*----------------------------------------------*/
        /*  most recentry data is clear allowed data.   */
        /*----------------------------------------------*/
        /*  clear most recentry data.       */
        Dem_OccrDTCRecord.ConfirmedEventStrgIndex       = DEM_EVENTSTRGINDEX_INVALID;
        Dem_OccrDTCRecord.ConfirmedNonOBDEventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
        updateFlag  =   (boolean)TRUE;
    }
    else
    {
        /*----------------------------------------------*/
        /*  most recentry data isn't clear allowed data.*/
        /*----------------------------------------------*/
        if ( clearAllowedFlag_nonOBD == (boolean)TRUE )
        {
            /*  clear most recentry nonOBD data.        */
            Dem_OccrDTCRecord.ConfirmedNonOBDEventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
            updateFlag  =   (boolean)TRUE;
        }
    }

    /*  update ClearId.     */
    Dem_OccrDTCRecord.ClearID = Dem_ClrInfoMng_GetClearID();
    Dem_OccrDTCRecord.ObdClearID = Dem_ClrInfoMng_GetObdClearID();

    return updateFlag;
}


/****************************************************************************/
/* Function Name | Dem_OccrDTCMng_ClearMostRecentConfirmedData_ObdDTC       */
/* Description   | Clear OBD DTC                                            */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | boolean                                                  */
/*               |          TRUE    : update data.                          */
/*               |          FALSE   : no update data.                       */
/* Notes         | update NvM is not execute this function.                 */
/*               | after this function called, caller call Dem_OccrDTCMng_UpdateRecord().   */
/*               | at Dem_OccrDTCMng_UpdateRecord(), update NvM.            */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_OccrDTCMng_ClearMostRecentConfirmedData_ObdDTC
( void )
{
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) dtcValue;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) getEventResult_nonOBD;
    VAR( boolean, AUTOMATIC ) eventOBDKind;
    VAR( boolean, AUTOMATIC ) clearAllowedFlag;
    VAR( boolean, AUTOMATIC ) updateFlag;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;
    clearAllowedFlag            =   (boolean)FALSE;
    updateFlag                  =   (boolean)FALSE;

    /*----------------------------------------------*/
    /*  check most recentry data.                   */
    /*----------------------------------------------*/
    if ( Dem_OccrDTCRecord.ConfirmedEventStrgIndex < eventStorageNum )
    {
        eventOBDKind            =   Dem_CfgInfoPm_CheckEventKindOfOBD_InEvtStrgGrp( Dem_OccrDTCRecord.ConfirmedEventStrgIndex );
        if ( eventOBDKind == (boolean)TRUE )
        {
            clearAllowedFlag    =   Dem_CfgInfoPm_ClearAllowed_InEvtStrgGrp( Dem_OccrDTCRecord.ConfirmedEventStrgIndex );
        }
    }

    if ( clearAllowedFlag == (boolean)TRUE )
    {
        /*----------------------------------------------*/
        /*  check most recentry nonOBD data.            */
        /*----------------------------------------------*/
        getEventResult_nonOBD   =   Dem_DataAvl_GetUDSDTCByEventStrgIndex( Dem_OccrDTCRecord.ConfirmedNonOBDEventStrgIndex, &dtcValue );    /* [GUD:RET:DEM_IRT_OK] Dem_OccrDTCRecord.ConfirmedNonOBDEventStrgIndex */

        /*----------------------------------------------*/
        /*  most recentry data is clear allowed data.   */
        /*----------------------------------------------*/
        /*  clear most recentry data.           */
        if ( getEventResult_nonOBD == DEM_IRT_OK )
        {
            /*  update data from nonOBD data.       */
            Dem_OccrDTCRecord.ConfirmedEventStrgIndex       = Dem_OccrDTCRecord.ConfirmedNonOBDEventStrgIndex;
        }
        else
        {
            /*  clear all most recentry data .      */
            Dem_OccrDTCRecord.ConfirmedEventStrgIndex       = DEM_EVENTSTRGINDEX_INVALID;
            Dem_OccrDTCRecord.ConfirmedNonOBDEventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
        }
        updateFlag  =   (boolean)TRUE;
    }

    /*  update ClearId.     */
    Dem_OccrDTCRecord.ObdClearID = Dem_ClrInfoMng_GetObdClearID();

    return updateFlag;
}


/****************************************************************************/
/* Function Name | Dem_OccrDTCMng_ClearMostRecentConfirmedData_ObdDTC       */
/* Description   | Clear OBD DTC                                            */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | boolean                                                  */
/*               |          TRUE    : update data.                          */
/*               |          FALSE   : no update data.                       */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_OccrDTCMng_ClearMostRecentConfirmedData_NotAvailable
( void )
{
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) dtcValue;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) getEventResult;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) getEventResult_nonOBD;
    VAR( boolean, AUTOMATIC ) eventOBDKind;
    VAR( boolean, AUTOMATIC ) updateFlag;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;
    updateFlag                  =   (boolean)FALSE;

    /*------------------------------*/
    /*  nonOBD data area            */
    /*------------------------------*/
    if ( Dem_OccrDTCRecord.ConfirmedNonOBDEventStrgIndex < eventStorageNum )
    {
        getEventResult_nonOBD   =   Dem_DataAvl_GetUDSDTCByEventStrgIndex( Dem_OccrDTCRecord.ConfirmedNonOBDEventStrgIndex, &dtcValue );    /* [GUD:RET:DEM_IRT_OK] Dem_OccrDTCRecord.ConfirmedNonOBDEventStrgIndex */
        if ( getEventResult_nonOBD != DEM_IRT_OK )
        {
            Dem_OccrDTCRecord.ConfirmedNonOBDEventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
            updateFlag  =   (boolean)TRUE;
        }
    }
    else
    {
        if ( Dem_OccrDTCRecord.ConfirmedNonOBDEventStrgIndex != DEM_EVENTSTRGINDEX_INVALID )
        {
            updateFlag  =   (boolean)TRUE;
        }
        Dem_OccrDTCRecord.ConfirmedNonOBDEventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
    }

    /*------------------------------*/
    /*  most recentry data area     */
    /*------------------------------*/
    if ( Dem_OccrDTCRecord.ConfirmedEventStrgIndex < eventStorageNum )
    {
        getEventResult              =   Dem_DataAvl_GetUDSDTCByEventStrgIndex( Dem_OccrDTCRecord.ConfirmedEventStrgIndex, &dtcValue );  /* [GUD:RET:DEM_IRT_OK] Dem_OccrDTCRecord.ConfirmedEventStrgIndex */

        if ( getEventResult != DEM_IRT_OK )
        {
            Dem_OccrDTCRecord.ConfirmedEventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
            Dem_OccrDTCRecord.ConfirmedNonOBDEventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
            updateFlag  =   (boolean)TRUE;
        }
        else
        {
            eventOBDKind                =   Dem_CfgInfoPm_CheckEventKindOfOBD_InEvtStrgGrp( Dem_OccrDTCRecord.ConfirmedEventStrgIndex );
            if( eventOBDKind != (boolean)TRUE ) /*  nonOBD      */
            {
                if ( Dem_OccrDTCRecord.ConfirmedEventStrgIndex != Dem_OccrDTCRecord.ConfirmedNonOBDEventStrgIndex )
                {
                    /*  update new nonOBD data.                 */
                    Dem_OccrDTCRecord.ConfirmedNonOBDEventStrgIndex =   Dem_OccrDTCRecord.ConfirmedEventStrgIndex;
                    updateFlag  =   (boolean)TRUE;
                }
            }
        }
    }
    else
    {
        if ( Dem_OccrDTCRecord.ConfirmedEventStrgIndex != DEM_EVENTSTRGINDEX_INVALID )
        {
            updateFlag  =   (boolean)TRUE;
        }
        if ( Dem_OccrDTCRecord.ConfirmedNonOBDEventStrgIndex != DEM_EVENTSTRGINDEX_INVALID )
        {
            updateFlag  =   (boolean)TRUE;
        }
        Dem_OccrDTCRecord.ConfirmedEventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
        Dem_OccrDTCRecord.ConfirmedNonOBDEventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
    }

    return updateFlag;
}

/****************************************************************************/
/* SAVED_ZONE Functions                                                     */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dem_OccrDTCMng_InitSavedZone_RecordData                  */
/* Description   | Initialize savedzone process of OccrDTC.                 */
/* Preconditions |                                                          */
/* Parameters    | [in]  OccrDTCRecordPtr :                                 */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_OccrDTCMng_InitSavedZone_RecordData
(
    P2VAR( Dem_OccrDTCRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) OccrDTCRecordPtr
)
{
    OccrDTCRecordPtr->ConfirmedEventStrgIndex       = DEM_EVENTSTRGINDEX_INVALID;
    OccrDTCRecordPtr->ConfirmedNonOBDEventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
    OccrDTCRecordPtr->ClearID       = DEM_CLRINFO_RECORD_INITIAL;
    OccrDTCRecordPtr->ObdClearID    = DEM_CLRINFO_RECORD_INITIAL;

    return;
}

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_OccrDTCMng_SetRecordMirror_RecordData                */
/* Description   | Copy to the Mirror Memory.                               */
/* Preconditions | none                                                     */
/* Parameters    | [in]  OccrDTCRecordPtr :                                 */
/*               | [out] OccrDTCRecordMirrorPtr :                           */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_OccrDTCMng_SetRecordMirror_RecordData
(
    P2VAR( Dem_OccrDTCRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) OccrDTCRecordPtr,
    P2VAR( Dem_OccrDTCRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) OccrDTCRecordMirrorPtr
)
{
    OccrDTCRecordMirrorPtr->ConfirmedEventStrgIndex         = OccrDTCRecordPtr->ConfirmedEventStrgIndex;
    OccrDTCRecordMirrorPtr->ConfirmedNonOBDEventStrgIndex   = OccrDTCRecordPtr->ConfirmedNonOBDEventStrgIndex;
    OccrDTCRecordMirrorPtr->ClearID                         = OccrDTCRecordPtr->ClearID;
    OccrDTCRecordMirrorPtr->ObdClearID                      = OccrDTCRecordPtr->ObdClearID;

    return;
}

/****************************************************************************/
/* Function Name | Dem_OccrDTCMng_InitMirrorMemory_RecordData               */
/* Description   | Initialize the Mirror Memory.                            */
/* Preconditions | none                                                     */
/* Parameters    | [out] OccrDTCRecordMirrorPtr :                           */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_OccrDTCMng_InitMirrorMemory_RecordData
(
    P2VAR( Dem_OccrDTCRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) OccrDTCRecordMirrorPtr
)
{
    /* Initializes the temporary permanent memory. */
    OccrDTCRecordMirrorPtr->ConfirmedEventStrgIndex         = DEM_EVENTSTRGINDEX_INVALID;
    OccrDTCRecordMirrorPtr->ConfirmedNonOBDEventStrgIndex   = DEM_EVENTSTRGINDEX_INVALID;
    OccrDTCRecordMirrorPtr->ClearID                 = DEM_CLRINFO_RECORD_INITIAL;
    OccrDTCRecordMirrorPtr->ObdClearID              = DEM_CLRINFO_RECORD_INITIAL;

    return;
}
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /*   ( DEM_DTC_OCCURRENCE_TIME_UPDATEATAGING_SUPPORT == STD_OFF )   */
#endif /* ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
