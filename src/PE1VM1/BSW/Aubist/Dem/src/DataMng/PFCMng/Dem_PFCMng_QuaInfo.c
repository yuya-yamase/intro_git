/* Dem_PFCMng_Qualinfo_c(v5-5-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/PFCMng_Qualinfo/CODE                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../cfg/Dem_Data_Cfg.h"
#include "../../../cfg/Dem_NvM_Cfg.h"
#include "../../../inc/Dem_Rc_PFCMng.h"
#include "../../../inc/Dem_Rc_ClrInfoMng.h"
#include "../../../inc/Dem_Rc_RecMngCmn.h"
#include "../../../inc/Dem_Rc_RecMngCmn_Table.h"

#if ( DEM_PFC_SUPPORT == STD_ON )

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
static FUNC( void, DEM_CODE ) Dem_PFCMng_QuaInfo_InitMirrorMemory
( void );
#endif  /*  ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )   */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/*  if DEM_NVM_SYNC_PROCESS_ENABLE is STD_OFF, these valiables are set but never used.  */
VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT ) Dem_PFCQuaInfoNvMStatus[DEM_PFC_RECORD_NUM];
VAR( Dem_PFCQuaInfoRecordType, DEM_VAR_NO_INIT ) Dem_TmpPFCQuaInfoMirror;
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#define DEM_START_SEC_VAR_SAVED_ZONE
#include <Dem_MemMap.h>

VAR( Dem_PFCQuaInfoRecordType, DEM_VAR_SAVED_ZONE ) Dem_PFCQuaInfoRecord[DEM_PFC_RECORD_NUM];

#define DEM_STOP_SEC_VAR_SAVED_ZONE
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_PFCMng_QuaInfo_Init                                  */
/* Description   | Init process of PFC Qualified info.                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PFCMng_QuaInfo_Init
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex     /* MISRA DEVIATION */
)
{
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    /* [FuncSw] */
    Dem_PFCMng_QuaInfo_InitMirrorMemory();
#endif  /*  ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )   */
    return;
}

/****************************************************************************/
/* Function Name | Dem_PFCMng_QuaInfo_InitSavedZone                         */
/* Description   | Initialize savedzone process of PFC Qualified data.      */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/*               | [in] InitType :                                          */
/*               |          Initialize savedzone type                       */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PFCMng_QuaInfo_InitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType      /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) pfcIndex;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) pfcRecordNum;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindPFCQuaInfo;

    recMngCmnKindPFCQuaInfo = Dem_RecMngCmnKindPFCQuaInfo;
    pfcRecordNum = Dem_PFCRecordNum;
    for( pfcIndex = (Dem_u08_PFCIndexType)0U; pfcIndex < pfcRecordNum; pfcIndex++ )         /* [GUD:for]pfcIndex */
    {
        Dem_PFCMng_QuaInfo_SetDtcValue( pfcIndex, DEM_PFC_DTCVALUE_INITIAL );                               /* [GUD]pfcIndex */
        Dem_PFCMng_QuaInfo_SetCycleQualifiedInfo( pfcIndex, DEM_PFC_QUALIFIEDINFO_INITIAL );                /* [GUD]pfcIndex */
        Dem_PFCMng_QuaInfo_SetClearID( pfcIndex, DEM_CLRINFO_RECORD_INITIAL );                              /* [GUD]pfcIndex */
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindPFCQuaInfo, ( Dem_u16_RecordIndexType )pfcIndex );    /* [GUD]pfcIndex */
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_PFCMng_QuaInfo_DataVerify                            */
/* Description   | Verifies PFC data.                                       */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |          DEM_IRT_OK      : DataVerify completed.         */
/*               |          DEM_IRT_PENDING : Continue DataVerify.          */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PFCMng_QuaInfo_DataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex     /* MISRA DEVIATION */
)
{
    return DEM_IRT_OK;
}


#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_PFCMng_QuaInfo_CopyToMirrorMemory                    */
/* Description   | Copy to the Mirror Memory.                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/*               | [in/out] BlockMirrorPtr :                                */
/*               |        Nonvolatile synchronous data information.         */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PFCMng_QuaInfo_CopyToMirrorMemory
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
)
{
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) pfcRecordNum;

    pfcRecordNum = Dem_PFCRecordNum;

    if( BlockMirrorPtr->RecordIndex < pfcRecordNum )    /* [GUD:if]BlockMirrorPtr->RecordIndex */
    {
        /* Set Permanent Memory record */
        Dem_TmpPFCQuaInfoMirror.DtcValue                = Dem_PFCQuaInfoRecord[BlockMirrorPtr->RecordIndex].DtcValue;           /* [GUD]BlockMirrorPtr->RecordIndex */
        Dem_TmpPFCQuaInfoMirror.ClearID                 = Dem_PFCQuaInfoRecord[BlockMirrorPtr->RecordIndex].ClearID;            /* [GUD]BlockMirrorPtr->RecordIndex */
        Dem_TmpPFCQuaInfoMirror.CycleQualifiedInfo      = Dem_PFCQuaInfoRecord[BlockMirrorPtr->RecordIndex].CycleQualifiedInfo; /* [GUD]BlockMirrorPtr->RecordIndex */
    }
    BlockMirrorPtr->MirrorPtr = &Dem_TmpPFCQuaInfoMirror;

    return;
}
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

/****************************************************************************/
/* Function Name | Dem_PFCMng_QuaInfo_GetDtcValue                           */
/* Description   | Get DTC Value for PFC Qualified info.                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] PFCRecordIndex    :                                 */
/*               |        Permanent memory record index.                    */
/*               | [out] DtcValuePtr :                                      */
/*               |        Pointer to data for set DtcValuePtr.              */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PFCMng_QuaInfo_GetDtcValue
(
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) PFCRecordIndex,              /* [PRMCHK:CALLER] */
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DtcValuePtr
)
{
    *DtcValuePtr = Dem_PFCQuaInfoRecord[PFCRecordIndex].DtcValue;       /* [GUDCHK:CALLER]PFCRecordIndex */

    return;
}


/****************************************************************************/
/* Function Name | Dem_PFCMng_QuaInfo_SetDtcValue                           */
/* Description   | Set DTC Value for PFC Qualified info.                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] PFCRecordIndex    :                                 */
/*               |        Permanent memory record index.                    */
/*               | [in] DtcValue          :                                 */
/*               |        DTC Value.                                        */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PFCMng_QuaInfo_SetDtcValue
(
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) PFCRecordIndex,          /* [PRMCHK:CALLER] */
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DtcValue
)
{
    Dem_PFCQuaInfoRecord[PFCRecordIndex].DtcValue = DtcValue;       /* [GUDCHK:CALLER]PFCRecordIndex */

    return;
}


/****************************************************************************/
/* Function Name | Dem_PFCMng_QuaInfo_GetClearID                            */
/* Description   | Get Clear ID for PFC Qualified info.                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] PFCRecordIndex    :                                 */
/*               |        Permanent memory record index.                    */
/*               | [out] ClearIDPtr       :                                 */
/*               |        Pointer to data for set DtcValuePtr.              */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PFCMng_QuaInfo_GetClearID
(
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) PFCRecordIndex,          /* [PRMCHK:CALLER] */
    P2VAR( Dem_u08_ClearIdType, AUTOMATIC, AUTOMATIC ) ClearIDPtr
)
{
    *ClearIDPtr = Dem_PFCQuaInfoRecord[PFCRecordIndex].ClearID;     /* [GUDCHK:CALLER]PFCRecordIndex */

    return;
}


/****************************************************************************/
/* Function Name | Dem_PFCMng_QuaInfo_SetClearID                            */
/* Description   | Set Clear ID for PFC Qualified info.                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] PFCRecordIndex    :                                 */
/*               |        Permanent memory record index.                    */
/*               | [in] ClearID           :                                 */
/*               |        Clear ID.                                         */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PFCMng_QuaInfo_SetClearID
(
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) PFCRecordIndex,          /* [PRMCHK:CALLER] */
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) ClearID
)
{
    Dem_PFCQuaInfoRecord[PFCRecordIndex].ClearID = ClearID;         /* [GUDCHK:CALLER]PFCRecordIndex */

    return;
}


/****************************************************************************/
/* Function Name | Dem_PFCMng_QuaInfo_GetCycleQualifiedInfo                 */
/* Description   | Get Clear ID for PFC Qualified info.                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] PFCRecordIndex            :                         */
/*               |        Permanent memory record index.                    */
/*               | [out] CycleQualifiedInfoPtr    :                         */
/*               |        Pointer to data for set CycleQualifiedInfoPtr.    */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PFCMng_QuaInfo_GetCycleQualifiedInfo
(
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) PFCRecordIndex,              /* [PRMCHK:CALLER] */
    P2VAR( Dem_u08_PFCCycQuaInfoType, AUTOMATIC, AUTOMATIC ) CycleQualifiedInfoPtr
)
{
    *CycleQualifiedInfoPtr = Dem_PFCQuaInfoRecord[PFCRecordIndex].CycleQualifiedInfo;   /* [GUDCHK:CALLER]PFCRecordIndex */

    return;
}


/****************************************************************************/
/* Function Name | Dem_PFCMng_QuaInfo_SetCycleQualifiedInfo                 */
/* Description   | Set CycleQualifiedInfo for PFC Qualified info.           */
/* Preconditions | none                                                     */
/* Parameters    | [in] PFCRecordIndex        :                             */
/*               |        Permanent memory record index.                    */
/*               | [in] CycleQualifiedInfo    :                             */
/*               |        CycleQualifiedInfo.                               */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PFCMng_QuaInfo_SetCycleQualifiedInfo
(
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) PFCRecordIndex,              /* [PRMCHK:CALLER] */
    VAR( Dem_u08_PFCCycQuaInfoType, AUTOMATIC ) CycleQualifiedInfo
)
{
    Dem_PFCQuaInfoRecord[PFCRecordIndex].CycleQualifiedInfo = CycleQualifiedInfo;       /* [GUDCHK:CALLER]PFCRecordIndex */

    return;
}


#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_PFCMng_QuaInfo_InitMirrorMemory                      */
/* Description   | Initialize the Mirror Memory.                            */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_PFCMng_QuaInfo_InitMirrorMemory
( void )
{
    VAR( Dem_u16_PaddingIndexType, AUTOMATIC ) paddingSize;
    VAR( Dem_u16_PaddingIndexType, AUTOMATIC ) paddingIndex;

    /* Initializes the temporary permanent memory. */
    Dem_TmpPFCQuaInfoMirror.DtcValue            = DEM_PFC_DTCVALUE_INITIAL;
    Dem_TmpPFCQuaInfoMirror.ClearID             = DEM_CLRINFO_RECORD_INITIAL;
    Dem_TmpPFCQuaInfoMirror.CycleQualifiedInfo  = DEM_PFC_QUALIFIEDINFO_INITIAL;

    paddingSize    = Dem_PFCQuaInfoRecordBlockPaddingSize;

    for( paddingIndex = (Dem_u16_PaddingIndexType)0U; paddingIndex < paddingSize; paddingIndex++ )  /* [GUD:for]paddingIndex */
    {
        Dem_TmpPFCQuaInfoMirror.Reserve[paddingIndex] = DEM_DTC_PFC_RESERVE_INITIAL_VALUE;      /* [GUD]paddingIndex */
    }

    return;
}
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_PFCMng_QuaInfo_GetEventIdFromRecordData              */
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
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PFCMng_QuaInfo_GetEventIdFromRecordData
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

#endif  /* ( DEM_PFC_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
