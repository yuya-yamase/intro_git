/* Dem_OccrDTCMng_c(v5-7-0)                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Dem_OccrDTCMng_c/CODE                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#if ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON )
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../cfg/Dem_NvM_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
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

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
static FUNC( void, DEM_CODE ) Dem_OccrDTCMng_InitPadding
(
    P2VAR( Dem_OccrDTCRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) OccrDTCRecordPtr
);
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT ) Dem_OccrDTCNvMStatus;
VAR( Dem_OccrDTCRecordType, DEM_VAR_NO_INIT ) Dem_TmpOccrDTCMirror;
#endif /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON ) */


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#define DEM_START_SEC_VAR_SAVED_ZONE
#include <Dem_MemMap.h>

VAR( Dem_OccrDTCRecordType, DEM_VAR_SAVED_ZONE ) Dem_OccrDTCRecord;

#define DEM_STOP_SEC_VAR_SAVED_ZONE
#include <Dem_MemMap.h>


/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_OccrDTCMng_Init                                      */
/* Description   | initialize function.                                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_OccrDTCMng_Init
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex     /* MISRA DEVIATION */
)
{
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    /* [FuncSw] */
    Dem_OccrDTCMng_InitMirrorMemory_RecordData( &Dem_TmpOccrDTCMirror );
    Dem_OccrDTCMng_InitPadding( &Dem_TmpOccrDTCMirror );

#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )   */
    return;
}


/****************************************************************************/
/* Function Name | Dem_OccrDTCMng_InitSavedZone                             */
/* Description   | Initialize savedzone process of OccrDTC.                 */
/* Preconditions |                                                          */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/*               | [in] InitType :                                          */
/*               |          Initialize savedzone type                       */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_OccrDTCMng_InitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType      /* MISRA DEVIATION */
)
{
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindOccrDTC;

    Dem_OccrDTCMng_InitSavedZone_RecordData( &Dem_OccrDTCRecord );

    recMngCmnKindOccrDTC = Dem_RecMngCmnKindOccrDTC;
    Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindOccrDTC, ( Dem_u16_RecordIndexType )0U );

    return;
}


/****************************************************************************/
/* Function Name | Dem_OccrDTCMng_DataVerify                                */
/* Description   | Data confirmation start demand.                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |          DEM_IRT_OK      : DataVerify completed.         */
/*               |          DEM_IRT_PENDING : Continue DataVerify.          */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_OccrDTCMng_DataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex     /* MISRA DEVIATION */
)
{
    /* Data Verify is carried out Dem_OccrDTCMng_DataVerify_AfterRecordCheckComplete() */
    return DEM_IRT_OK;
}

/****************************************************************************/
/* Function Name | Dem_OccrDTCMng_GetMostRecentConfirmedData                */
/* Description   | Get the Most Recent Confirmed Data.                      */
/* Preconditions | none                                                     */
/* Parameters    | void                                                     */
/* Return Value  | Dem_u16_EventStrgIndexType                               */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u16_EventStrgIndexType, DEM_CODE ) Dem_OccrDTCMng_GetMostRecentConfirmedData
( void )
{
    return Dem_OccrDTCRecord.ConfirmedEventStrgIndex;
}

/****************************************************************************/
/* SAVED_ZONE Functions                                                     */
/****************************************************************************/

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_OccrDTCMng_SetRecordMirror                           */
/* Description   | Copy to the Mirror Memory.                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/*               | [in/out] BlockMirrorPtr :                                */
/*               |        Nonvolatile synchronous data information.         */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_OccrDTCMng_SetRecordMirror
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
)
{
    Dem_OccrDTCMng_SetRecordMirror_RecordData( &Dem_OccrDTCRecord, &Dem_TmpOccrDTCMirror );

    BlockMirrorPtr->MirrorPtr = &Dem_TmpOccrDTCMirror;

    return;
}


/****************************************************************************/
/* Function Name | Dem_OccrDTCMng_InitPadding                               */
/* Description   | Initializes the occrDTC record padding data.             */
/* Preconditions | none                                                     */
/* Parameters    | [out] OccrDTCRecordPtr    :                              */
/*               |       The pointer of the occrDTC record.                 */
/*               |       &Dem_OccrDTCRecord -DEM_VAR_SAVED_ZONE-            */
/*               |       &Dem_TmpOccrDTCMirror -DEM_VAR_NO_INIT-            */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_OccrDTCMng_InitPadding
(
    P2VAR( Dem_OccrDTCRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) OccrDTCRecordPtr
)
{
    VAR( Dem_u16_PaddingIndexType, AUTOMATIC ) occrDTCRecordBlockPaddingSize;
    VAR( Dem_u16_PaddingIndexType, AUTOMATIC ) paddingIndex;

    occrDTCRecordBlockPaddingSize = Dem_OccrDTCRecordBlockPaddingSize;

    for( paddingIndex = (Dem_u16_PaddingIndexType)0U; paddingIndex < occrDTCRecordBlockPaddingSize; paddingIndex++ )    /* [GUD:for]paddingIndex */
    {
        OccrDTCRecordPtr->Reserve[paddingIndex] = (uint8)0U;    /* [GUD]paddingIndex *//* [ARYCHK] DEM_OCCRDTC_RECORD_PADDINGSIZE_TO_BLOCKSIZE / 1 / paddingIndex */
    }
    return ;
}

/****************************************************************************/
/* Function Name | Dem_OccrDTCMng_GetEventIdFromRecordData                  */
/* Description   | get event id from record data                            */
/* Preconditions | none                                                     */
/* Parameters    | [in]  RecordFieldIndex :                                 */
/*               | [in]  RecordIndex :                                      */
/*               | [out] EventIdPtr  :                                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_OccrDTCMng_GetEventIdFromRecordData
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex,      /* MISRA DEVIATION */
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr   /* MISRA DEVIATION */
)
{
    /*  this record has no event id.        */
    return DEM_IRT_NG;
}
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
