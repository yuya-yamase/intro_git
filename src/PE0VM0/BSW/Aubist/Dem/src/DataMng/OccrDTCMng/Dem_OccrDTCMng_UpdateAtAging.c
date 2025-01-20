/* Dem_OccrDTCMng_UpdateAtAging_c(v5-5-0)                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Dem_OccrDTCMng_UpdateAtAging_c/CODE                   */
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
#include "../../../cfg/Dem_NvM_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Rc_ClrInfoMng.h"
#include "../../../inc/Dem_Rc_RecMngCmn.h"
#include "../../../inc/Dem_Rc_OccrDTCMng.h"
#include "../../../inc/Dem_Rc_OdrLst.h"
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
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_OccrDTCMng_DataVerify_AfterRecordCheckComplete
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) LastConfirmedEventStrgIndex
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) clrInfoNvmReadResult;
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) clrInfoObdRecValue;

    clrInfoNvmReadResult = Dem_ClrInfoMng_GetNvmReadResult();
    clrInfoObdRecValue   = Dem_ClrInfoMng_GetObdClearID();

    /* Check ClrInfo Recored */
    if( clrInfoNvmReadResult == DEM_IRT_OK )
    {
        if( Dem_OccrDTCRecord.ObdClearID != clrInfoObdRecValue )
        {
            eventStrgIndex = Dem_OccrDTCMng_GetMostRecentConfirmedData();
            if( eventStrgIndex != LastConfirmedEventStrgIndex )
            {
                Dem_OccrDTCMng_SetMostRecentConfirmedData( LastConfirmedEventStrgIndex, DEM_UPDNVM_UPD_RAMONLY );
            }
        }
    }
    else
    {
        eventStrgIndex = Dem_OccrDTCMng_GetMostRecentConfirmedData();
        if( eventStrgIndex != LastConfirmedEventStrgIndex )
        {
            Dem_OccrDTCMng_SetMostRecentConfirmedData( LastConfirmedEventStrgIndex, DEM_UPDNVM_UPD_NVM_FORCE );
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_OccrDTCMng_SetMostRecentConfirmedData                */
/* Description   | Set the Most Recent Confirmed Data.                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/* Parameters    | [in] UpdateNvMMode : DEM_UPDNVM_UPD_RAMONLY              */
/*               |                      DEM_UPDNVM_UPD_NVM_RAMDIFF          */
/*               |                      DEM_UPDNVM_UPD_NVM_FORCE            */
/* Return Value  | void                                                     */
/* Notes         | Set argument to OccrDTC Record.                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_OccrDTCMng_SetMostRecentConfirmedData
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_UpdNvMType, AUTOMATIC ) UpdateNvMMode
)
{
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindOccrDTC;
    VAR( boolean, AUTOMATIC ) updateNvM;

    updateNvM   =   (boolean)FALSE;
    if ( UpdateNvMMode == DEM_UPDNVM_UPD_NVM_RAMDIFF )
    {
        if( Dem_OccrDTCRecord.ConfirmedEventStrgIndex != EventStrgIndex )
        {
            updateNvM   =   (boolean)TRUE;
        }
    }
    else if ( UpdateNvMMode == DEM_UPDNVM_UPD_NVM_FORCE )
    {
        updateNvM   =   (boolean)TRUE;
    }
    else
    {
        /*  no NvM update.      */
    }

    /*  update RAM.             */
    Dem_OccrDTCRecord.ConfirmedEventStrgIndex = EventStrgIndex;
    Dem_OccrDTCRecord.ObdClearID              = Dem_ClrInfoMng_GetObdClearID();

    /*  update NvM.             */
    if ( updateNvM == (boolean)TRUE )
    {
        recMngCmnKindOccrDTC = Dem_RecMngCmnKindOccrDTC;

        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindOccrDTC, ( Dem_u16_RecordIndexType )0U );
    }

    return;
}

/****************************************************************************/
/* NvM Functions                                                            */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dem_OccrDTCMng_InitSavedZone_RecordData                  */
/* Description   | Initialize savedzone process of OccrDTC.                 */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_OccrDTCMng_InitSavedZone_RecordData
(
    P2VAR( Dem_OccrDTCRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) OccrDTCRecordPtr
)
{
    OccrDTCRecordPtr->ConfirmedEventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;

    OccrDTCRecordPtr->ObdClearID = DEM_CLRINFO_RECORD_INITIAL;

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
    OccrDTCRecordMirrorPtr->ConfirmedEventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
    OccrDTCRecordMirrorPtr->ObdClearID              = DEM_CLRINFO_RECORD_INITIAL;

    return;
}
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_DTC_OCCURRENCE_TIME_UPDATEATAGING_SUPPORT == STD_ON )  */
#endif /* ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
