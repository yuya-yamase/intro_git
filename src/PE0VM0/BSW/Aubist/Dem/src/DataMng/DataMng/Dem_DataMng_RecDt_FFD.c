/* Dem_DataMng_RecDt_FFD_c(v5-10-0)                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Dem_DataMng_RecDt_FFD_c/CODE                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Rc_DataMng.h"
#include "../../../inc/Dem_Utl.h"
#include "../../../inc/Dem_Rc_RecMngCmn.h"
#include "../../../inc/Dem_Rc_RecMngCmn_Table.h"
#include "MisfireMng/Dem_MisfireMng_local.h"
#include "Dem_DataMng_local.h"
#include "Dem_DataMng_FreezeFrame.h"
#include "Dem_DataMng_GetRecordData.h"

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

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMng_ClearFreezeFrameRecord
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) FreezeFrameIndex
);
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
static FUNC( void, DEM_CODE ) Dem_FFDMng_InitMirrorMemory
( void );
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_FFDMng_CheckConsistency
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) FreezeFrameIndex
);

static FUNC( void, DEM_CODE ) Dem_FFDMng_GetFFDConsistencyInfo
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) FreezeFrameIndex,
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) FirstBlockCIdPtr,
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) LastBlockCIdPtr,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) FirstBlockEventStrgIndexPtr,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) LastBlockEventStrgIndexPtr
);


static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_FFDMng_VerifyChecksum
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) FreezeFrameIndex
);
#if ( DEM_FF_CHECKSUM_SUPPORT == STD_ON )
static FUNC( Dem_u16_FFCheckSumType, DEM_CODE ) Dem_FFDMng_GetChecksum
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) FreezeFrameIndex
);
#endif /* ( DEM_FF_CHECKSUM_SUPPORT == STD_ON ) */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT ) Dem_FFDNvMStatus[DEM_FFD_RECORD_LIST_NUM];
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/*  if DEM_NVM_SYNC_PROCESS_ENABLE is STD_OFF, these valiables are set but never used.  */
VAR( Dem_FreezeFrameRecordType, DEM_VAR_NO_INIT ) Dem_TmpFFDMirror;
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#define DEM_START_SEC_VAR_SAVED_ZONE
#include <Dem_MemMap.h>

VAR(Dem_FreezeFrameRecordType, DEM_VAR_SAVED_ZONE ) Dem_FreezeFrameRecordList[DEM_FFD_RECORD_LIST_NUM];

#define DEM_STOP_SEC_VAR_SAVED_ZONE
#include <Dem_MemMap.h>


/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_DataMngC_GetFFR_MngInfo                              */
/* Description   | Gets FaultIndex of the FreezeFrame record from the Free- */
/*               | zeFrame record list corresponding to the specified Free- */
/*               | zeFrame index. (for Dem_DataCtl subunit)                 */
/* Preconditions | The specified FreezeFrame index be within the range of - */
/*               | the FreezeFrame record list.                             */
/* Parameters    | [in] FreezeFrameIndex :                                  */
/*               |        The FreezeFrame index corresponding to the speci- */
/*               |        fic FreezeFrame record.                           */
/*               | [out] FreezeFrameRecordPtr :                             */
/*               |         &Dem_TmpEventMemoryEntry.FreezeFrameRecordList[] */
/*               |         AUTOMATIC                                        */
/*               |        The pointer of the FreezeFrame record correspond- */
/*               |        ing to the specified FreezeFrame index.           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetFFR_MngInfo
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) FreezeFrameIndex,
    P2VAR( Dem_FreezeFrameRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) FreezeFrameRecordPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstEventStrgIndexUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstEventStrgIndexLower;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) nonObdFFDRecordNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;
    nonObdFFDRecordNum = Dem_NonObdFFDRecordNum;

    if( FreezeFrameIndex < nonObdFFDRecordNum )                                                     /* [GUD:if]FreezeFrameIndex */
    {
        posFirstEventStrgIndexUpper = Dem_NonObdFreezeFrameDataPosTable.FirstEventStrgIndexUpper;   /* [GUD:CFG]posFirstEventStrgIndexUpper */
        posFirstEventStrgIndexLower = Dem_NonObdFreezeFrameDataPosTable.FirstEventStrgIndexLower;   /* [GUD:CFG]posFirstEventStrgIndexLower */
        /* Gets EventIndex from storage format. */
        eventStrgIndex = (Dem_u16_EventStrgIndexType)Dem_UtlMem_ConvertByteData( Dem_FreezeFrameRecordList[FreezeFrameIndex].Data[posFirstEventStrgIndexUpper], Dem_FreezeFrameRecordList[FreezeFrameIndex].Data[posFirstEventStrgIndexLower] );    /* [GUD]FreezeFrameIndex *//* [GUD]posFirstEventStrgIndexUpper *//* [GUD]posFirstEventStrgIndexLower */
        FreezeFrameRecordPtr->EventStrgIndex = eventStrgIndex;

        /* Sets the return value to OK, cause the illegal value will not be returned. */
        retVal = DEM_IRT_OK;
    }
    else
    {
        /* No process */
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_DataMngC_GetFreezeFrameRecord                        */
/* Description   | Gets the data body of the FreezeFrame record from the F- */
/*               | reezeFrame record list corresponding to the specified F- */
/*               | reezeFrame index. (for Dem_DataCtl subunit)              */
/* Preconditions | The specified FreezeFrame index be within the range of - */
/*               | the FreezeFrame record list.                             */
/* Parameters    | [in] FreezeFrameIndex :                                  */
/*               |        The FreezeFrame index corresponding to the speci- */
/*               |        fic FreezeFrame record.                           */
/*               | [out] FreezeFrameRecordPtr :                             */
/*               |        The pointer of the FreezeFrame record from DataM- */
/*               |        ng corresponding to the specified FreezeFrame in- */
/*               |        dex.                                              */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetFreezeFrameRecord
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) FreezeFrameIndex,
    P2VAR( Dem_FreezeFrameRecordMngType, AUTOMATIC, AUTOMATIC ) FreezeFrameRecordPtr
)
{
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstCid;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstEventStrgIndexUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstEventStrgIndexLower;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posRecordStatus;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posDataStart;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) nonObdFFDRecordNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;
    nonObdFFDRecordNum = Dem_NonObdFFDRecordNum;

    if( FreezeFrameIndex < nonObdFFDRecordNum )                                                     /* [GUD:if]FreezeFrameIndex */
    {
        posFirstCid = Dem_NonObdFreezeFrameDataPosTable.FirstCID;                                   /* [GUD:CFG]posFirstCid */
        posFirstEventStrgIndexUpper = Dem_NonObdFreezeFrameDataPosTable.FirstEventStrgIndexUpper;   /* [GUD:CFG]posFirstEventStrgIndexUpper */
        posFirstEventStrgIndexLower = Dem_NonObdFreezeFrameDataPosTable.FirstEventStrgIndexLower;   /* [GUD:CFG]posFirstEventStrgIndexLower */
        posRecordStatus = Dem_NonObdFreezeFrameDataPosTable.RecordStatus;                           /* [GUD:CFG]posRecordStatus */
        posDataStart = Dem_NonObdFreezeFrameDataPosTable.DataStart;                                 /* [GUD:CFG]posDataStart */

        FreezeFrameRecordPtr->ConsistencyId = Dem_FreezeFrameRecordList[FreezeFrameIndex].Data[posFirstCid];    /* [GUD]FreezeFrameIndex *//* [GUD]posFirstCid */
        eventStrgIndex = (Dem_u16_EventStrgIndexType)Dem_UtlMem_ConvertByteData( Dem_FreezeFrameRecordList[FreezeFrameIndex].Data[posFirstEventStrgIndexUpper], Dem_FreezeFrameRecordList[FreezeFrameIndex].Data[posFirstEventStrgIndexLower] );    /* [GUD]FreezeFrameIndex *//* [GUD]posFirstEventStrgIndexUpper *//* [GUD]posFirstEventStrgIndexLower */
        FreezeFrameRecordPtr->EventStrgIndex = eventStrgIndex;
        FreezeFrameRecordPtr->RecordStatus = Dem_FreezeFrameRecordList[FreezeFrameIndex].Data[posRecordStatus]; /* [GUD]FreezeFrameIndex *//* [GUD]posRecordStatus */
        FreezeFrameRecordPtr->DataPtr = &Dem_FreezeFrameRecordList[FreezeFrameIndex].Data[posDataStart];        /* [GUD]FreezeFrameIndex *//* [GUD]posDataStart */

        retVal = DEM_IRT_OK;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_DataMngC_SetFreezeFrameRecord                        */
/* Description   | Sets the data body of the FreezeFrame record to the Fre- */
/*               | ezeFrame record list corresponding to the specified Fre- */
/*               | ezeFrame index. (for Dem_DataCtl subunit)                */
/* Preconditions | The specified FreezeFrame index be within the range of - */
/*               | the FreezeFrame record list.                             */
/* Parameters    | [in] FreezeFrameIndex :                                  */
/*               |        The FreezeFrame index corresponding to the speci- */
/*               |        fic FreezeFrame record.                           */
/*               | [in] FreezeFrameRecordPtr :                              */
/*               |         &Dem_TmpEventMemoryEntry.FreezeFrameRecordList[] */
/*               |         AUTOMATIC                                        */
/*               |        The pointer of the FreezeFrame record correspond- */
/*               |        ing to the specified FreezeFrame index.           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_SetFreezeFrameRecord
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) FreezeFrameIndex,
    P2CONST( Dem_FreezeFrameRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) FreezeFrameRecordPtr
)
{
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) nonObdFFDRecordNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) consistencyId;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) ffrMaxLength;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindFFD;

    retVal = DEM_IRT_NG;
    nonObdFFDRecordNum = Dem_NonObdFFDRecordNum;

    if( FreezeFrameIndex < nonObdFFDRecordNum )                                                 /* [GUD:if]FreezeFrameIndex */
    {
        consistencyId = Dem_FFDMng_GetFFDConsystencyId( FreezeFrameIndex );

        consistencyId = Dem_UtlCid_CalcConsistencyId( consistencyId );

        ffrMaxLength = Dem_FFRMaxLength;

        /* Sets the captured freeze frame data record and the index of fault to storage format. */
#ifndef DEM_SIT_RANGE_CHECK
        Dem_DataMng_SetCapturedFreezeFrame( &Dem_NonObdFreezeFrameDataPosTable, consistencyId, FreezeFrameRecordPtr->EventStrgIndex, FreezeFrameRecordPtr->RecordStatus, FreezeFrameRecordPtr->Data, ffrMaxLength, Dem_FreezeFrameRecordList[FreezeFrameIndex].Data );  /* [GUD]FreezeFrameIndex */
#else   /* DEM_SIT_RANGE_CHECK */
        Dem_DataMng_SetCapturedFreezeFrame( DEM_FREEZE_FRAME_DATA_STORED_FORMAT_SIZE, &Dem_NonObdFreezeFrameDataPosTable, consistencyId, FreezeFrameRecordPtr->EventStrgIndex, FreezeFrameRecordPtr->RecordStatus, FreezeFrameRecordPtr->Data, ffrMaxLength, Dem_FreezeFrameRecordList[FreezeFrameIndex].Data );  /* [GUD]FreezeFrameIndex */
#endif  /* DEM_SIT_RANGE_CHECK */
        /* Change Dem_FFDNvMStatus */
        recMngCmnKindFFD = Dem_RecMngCmnKindFFD;
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindFFD, ( Dem_u16_RecordIndexType )FreezeFrameIndex );
        /* Sets the return value to OK, cause the illegal value will not be returned. */
        retVal = DEM_IRT_OK;
    }
    else
    {
        /* No process */
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_DataMngC_ClearFreezeFrameRecord                      */
/* Description   | Initialize freeze frame data area.                       */
/*               |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] FreezeFrameIndex :                                  */
/*               |        The FreezeFrame index corresponding to the speci- */
/*               |        fic FreezeFrame record.                           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/* Notes         | none.                                                    */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_ClearFreezeFrameRecord
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) FreezeFrameIndex
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    /* Because the range of the specified index is checked in the function "Dem_DataMng_ClearFreezeFrameRecord", not check it in here. */
    retVal = Dem_DataMng_ClearFreezeFrameRecord( FreezeFrameIndex );

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_DataMngC_InitFreezeFrameRecordData                   */
/* Description   | Initializes the specified freeze frame record.           */
/* Preconditions |                                                          */
/* Parameters    | [out] FreezeFrameRecordPtr :                             */
/*               |        The specified freeze frame record to initialize.  */
/*               |         &Dem_TmpEventMemoryEntry.FreezeFrameRecordList[] */
/*               |         AUTOMATIC                                        */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMngC_InitFreezeFrameRecordData
(
    P2VAR( Dem_FreezeFrameRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) FreezeFrameRecordPtr
)
{
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) ffrMaxLength;
    /* Sets initial value to the specified freeze frame record. */

    /* The event index */
    FreezeFrameRecordPtr->EventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;

    /* The record status */
    FreezeFrameRecordPtr->RecordStatus = DEM_FFD_NOT_STORED;

    /* The data for freeze frame. */
    ffrMaxLength = Dem_FFRMaxLength;
    Dem_UtlMem_SetMemory( &FreezeFrameRecordPtr->Data[0], DEM_FFD_INITIAL, ffrMaxLength ); /* [ARYCHK] DEM_FFR_MAX_LENGTH/1/0 */

    return ;
}


/****************************************************************************/
/* Function Name | Dem_DataMng_ClearFreezeFrameRecord                       */
/* Description   | Initializes the fault index and the record status of the */
/*               | specified record of freeze frame record list.            */
/* Preconditions |                                                          */
/* Parameters    | [in] FreezeFrameIndex :                                  */
/*               |        The FreezeFrame index corresponding to the speci- */
/*               |        fic FreezeFrame record.                           */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-10-0     | no branch changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMng_ClearFreezeFrameRecord
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) FreezeFrameIndex
)
{
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstEventStrgIndexUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstEventStrgIndexLower;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posLastEventStrgIndexUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posLastEventStrgIndexLower;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posRecordStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) nonObdFFDRecordNum;
    VAR( uint8, AUTOMATIC ) eventStrgIndexUpper;
    VAR( uint8, AUTOMATIC ) eventStrgIndexLower;

    retVal = DEM_IRT_OK;
    nonObdFFDRecordNum = Dem_NonObdFFDRecordNum;

    /* Checks the range of the specified index.*/
    if( FreezeFrameIndex < nonObdFFDRecordNum )                                                     /* [GUD:if]FreezeFrameIndex */
    {
        posFirstEventStrgIndexUpper = Dem_NonObdFreezeFrameDataPosTable.FirstEventStrgIndexUpper;   /* [GUD:CFG]posFirstEventStrgIndexUpper */
        posFirstEventStrgIndexLower = Dem_NonObdFreezeFrameDataPosTable.FirstEventStrgIndexLower;   /* [GUD:CFG]posFirstEventStrgIndexLower */
        posLastEventStrgIndexUpper = Dem_NonObdFreezeFrameDataPosTable.LastEventStrgIndexUpper;     /* [GUD:CFG]posLastEventStrgIndexUpper */
        posLastEventStrgIndexLower = Dem_NonObdFreezeFrameDataPosTable.LastEventStrgIndexLower;     /* [GUD:CFG]posLastEventStrgIndexLower */
        posRecordStatus = Dem_NonObdFreezeFrameDataPosTable.RecordStatus;                           /* [GUD:CFG]posRecordStatus */

        /* Sets "not stored" to the record status of the specified freeze frame record. */
        Dem_FreezeFrameRecordList[FreezeFrameIndex].Data[posRecordStatus] = DEM_FFD_NOT_STORED;                 /* [GUD]FreezeFrameIndex *//* [GUD]posRecordStatus */

        /* Sets the initial value to the event index of the specified freeze frame record. */
        Dem_UtlMem_SplitByteData( (uint16)DEM_EVENTSTRGINDEX_INVALID, &eventStrgIndexUpper, &eventStrgIndexLower );
        Dem_FreezeFrameRecordList[FreezeFrameIndex].Data[posFirstEventStrgIndexUpper] = eventStrgIndexUpper;    /* [GUD]FreezeFrameIndex *//* [GUD]posFirstEventStrgIndexUpper */
        Dem_FreezeFrameRecordList[FreezeFrameIndex].Data[posFirstEventStrgIndexLower] = eventStrgIndexLower;    /* [GUD]FreezeFrameIndex *//* [GUD]posFirstEventStrgIndexLower */
        Dem_FreezeFrameRecordList[FreezeFrameIndex].Data[posLastEventStrgIndexUpper] = eventStrgIndexUpper;     /* [GUD]FreezeFrameIndex *//* [GUD]posLastEventStrgIndexUpper */
        Dem_FreezeFrameRecordList[FreezeFrameIndex].Data[posLastEventStrgIndexLower] = eventStrgIndexLower;     /* [GUD]FreezeFrameIndex *//* [GUD]posLastEventStrgIndexLower */
    }
    else
    {
        retVal = DEM_IRT_NG;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_FFDMng_Init                                          */
/* Description   | Init process of FFD.                                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_FFDMng_Init
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex     /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) freezeFrameIndex;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) nonObdFFDRecordNum;

    nonObdFFDRecordNum = Dem_NonObdFFDRecordNum;

    for( freezeFrameIndex = (Dem_u08_FFDIndexType)0U; freezeFrameIndex < nonObdFFDRecordNum; freezeFrameIndex++ )   /* [GUD:for]freezeFrameIndex */
    {
        Dem_FFDNvMStatus[ freezeFrameIndex ] = DEM_RECMNGCMN_NVM_STS_NOT_VERIFIED;  /* [GUD]freezeFrameIndex */
    }

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    /* [FuncSw] */
    Dem_FFDMng_InitMirrorMemory();
#endif  /*   ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )  */

    return;
}

/****************************************************************************/
/* Function Name | Dem_FFDMng_InitSavedZone                                 */
/* Description   | Initialize savedzone process of FFD.                     */
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
FUNC( void, DEM_CODE ) Dem_FFDMng_InitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType      /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) freezeFrameIndex;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) nonObdFFDRecordNum;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) ffdStoredFormatSize;

    nonObdFFDRecordNum = Dem_NonObdFFDRecordNum;
    ffdStoredFormatSize = Dem_FreezeFrameDataStoredFormatSize;

    for( freezeFrameIndex = (Dem_u08_FFDIndexType)0U; freezeFrameIndex < nonObdFFDRecordNum; freezeFrameIndex++ )   /* [GUD:for]freezeFrameIndex */
    {
        Dem_UtlMem_SetMemory( &Dem_FreezeFrameRecordList[freezeFrameIndex].Data[0], DEM_FFD_INITIAL, ffdStoredFormatSize ); /* [GUD]freezeFrameIndex */
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_FFDMng_DataVerify                                    */
/* Description   | Verifies FFD data.                                       */
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
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_FFDMng_DataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex     /* MISRA DEVIATION */
)
{
    /* No Process */
    return DEM_IRT_OK;
}

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_FFDMng_SetRecordMirror                               */
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
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_FFDMng_SetRecordMirror
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
)
{
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) ffdStorageFormatsize;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) ffdDataIndex;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) nonObdFFDRecordNum;

    ffdStorageFormatsize = Dem_FreezeFrameDataStoredFormatSize;
    nonObdFFDRecordNum = Dem_NonObdFFDRecordNum;

    if( BlockMirrorPtr->RecordDataOffset == (Dem_u16_RecordDataSizeType)0U )
    {
        if( BlockMirrorPtr->RecordIndex < nonObdFFDRecordNum )      /* [GUD:if]BlockMirrorPtr->RecordIndex */
        {
            /* copy data to mirror area. */
            Dem_UtlMem_CopyMemory( &Dem_TmpFFDMirror.Data[0], &(Dem_FreezeFrameRecordList[BlockMirrorPtr->RecordIndex].Data[0]), ffdStorageFormatsize );    /* [GUD]BlockMirrorPtr->RecordIndex */
        }
    }

    ffdDataIndex = Dem_FFDRecordNvBlockSize * BlockMirrorPtr->RecordDataOffset;
    if( ffdDataIndex < ffdStorageFormatsize )                               /* [GUD:if]ffdDataIndex */
    {
        BlockMirrorPtr->MirrorPtr = &Dem_TmpFFDMirror.Data[ ffdDataIndex ]; /* [GUD]ffdDataIndex */
    }

    return;
}

#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

/****************************************************************************/
/* Function Name | Dem_FFDMng_Verified                                      */
/* Description   | Make non OBD FFD verified.                               */
/* Preconditions |                                                          */
/* Parameters    | [in] FaultIndex : The fault index                        */
/*               | [in] FaultRecordPtr : Fault record.                      */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-9-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_FFDMng_Verified
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,            /* [PRMCHK:CALLER] */
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ConsistencyIdUpdateFlgPtr        /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) freezeFrameRecordIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonOBDFFRClassPerDTCMaxNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) nonObdFFDRecordNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) freezeFrameIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVerifyRecord;
    VAR( boolean, AUTOMATIC ) faultRecordClearFlg;
    VAR( boolean, AUTOMATIC ) setNvMWriteFlg;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindFault;

    nonOBDFFRClassPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;
    nonObdFFDRecordNum = Dem_NonObdFFDRecordNum;
    setNvMWriteFlg = (boolean)FALSE;

    for( freezeFrameRecordIndex = (Dem_u08_FFListIndexType)0U; freezeFrameRecordIndex < nonOBDFFRClassPerDTCMaxNum; freezeFrameRecordIndex++ )  /* [GUD:for]freezeFrameRecordIndex */
    {
        faultRecordClearFlg = (boolean)FALSE;
        freezeFrameIndex = DEM_FFRECINDEX_INITIAL;
        (void)Dem_DataMngC_GetFR_FreezeFrameIndex( FaultIndex, freezeFrameRecordIndex, &freezeFrameIndex );   /* no return check required */
        if( freezeFrameIndex < nonObdFFDRecordNum )                                             /* [GUD:if]freezeFrameIndex */
        {
            retVerifyRecord = Dem_FFDMng_CheckConsistency( EventStrgIndex, freezeFrameIndex );  /* [GUDCHK:CALLER]EventStrgIndex *//* [GUD]freezeFrameIndex */

            if( retVerifyRecord == DEM_IRT_OK )
            {
                Dem_FFDNvMStatus[ freezeFrameIndex ] = DEM_RECMNGCMN_NVM_STS_NON_TARGET;        /* [GUD]freezeFrameIndex */
            }
            else
            {
                faultRecordClearFlg = (boolean)TRUE;
            }
        }
        else
        {
            if( freezeFrameIndex != DEM_FFRECINDEX_INITIAL )
            {
                faultRecordClearFlg = (boolean)TRUE;
            }
        }

        if( faultRecordClearFlg == (boolean)TRUE )
        {
            Dem_DataMng_InitSpecificRecordNumberIndex( FaultIndex, freezeFrameRecordIndex );    /* [GUD]freezeFrameRecordIndex */
            setNvMWriteFlg = (boolean)TRUE;
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
            Dem_MisfireMng_UpdateFFDInfoByInitRecordNumberIndex( EventStrgIndex, freezeFrameRecordIndex, ConsistencyIdUpdateFlgPtr );   /* [GUDCHK:CALLER]EventStrgIndex *//* [GUD]freezeFrameRecordIndex */
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */
        }
    }

    if( setNvMWriteFlg == (boolean)TRUE )
    {
        recMngCmnKindFault = Dem_RecMngCmnKindFault;
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindFault, ( Dem_u16_RecordIndexType )FaultIndex );
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_FFDMng_ClearAllNotVerifiedRecord                     */
/* Description   | Clear not verrified record.                              */
/* Preconditions |                                                          */
/* Parameters    | [in/out] ClearRecordIndexPtr :                           */
/*               |          target record index                             */
/*               | [in/out] RestOfProcessableNumPtr :                       */
/*               |          rest number of Processable Record               */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |          DEM_IRT_OK      : Completed.                    */
/*               |          DEM_IRT_PENDING : Continue.                     */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_FFDMng_ClearAllNotVerifiedRecord
(
    P2VAR( Dem_u16_RecordIndexType, AUTOMATIC, AUTOMATIC ) ClearRecordIndexPtr,
    P2VAR( Dem_u32_TotalRecordNumType, AUTOMATIC, AUTOMATIC ) RestOfProcessableNumPtr
)
{
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) freezeFrameIndex;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) nonObdFFDRecordNum;
    VAR( Dem_u32_TotalRecordNumType, AUTOMATIC ) loopCount;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    nonObdFFDRecordNum = Dem_NonObdFFDRecordNum;
    loopCount = (Dem_u32_TotalRecordNumType)0U;
    retVal = DEM_IRT_OK;

    for( freezeFrameIndex = (Dem_u08_FFDIndexType)( *ClearRecordIndexPtr ); freezeFrameIndex < nonObdFFDRecordNum; freezeFrameIndex++ ) /* [GUD:for]freezeFrameIndex */
    {
        if( loopCount < *RestOfProcessableNumPtr )
        {
            if( Dem_FFDNvMStatus[ freezeFrameIndex ] == DEM_RECMNGCMN_NVM_STS_NOT_VERIFIED )                    /* [GUD]freezeFrameIndex */
            {
                (void)Dem_DataMng_ClearFreezeFrameRecord( freezeFrameIndex );   /* no return check required */  /* [GUD]freezeFrameIndex */
                Dem_FFDNvMStatus[ freezeFrameIndex ] = DEM_RECMNGCMN_NVM_STS_NON_TARGET;                        /* [GUD]freezeFrameIndex */
            }
            loopCount = loopCount + (Dem_u32_TotalRecordNumType)1U;
        }
        else
        {
            *ClearRecordIndexPtr = (Dem_u16_RecordIndexType)freezeFrameIndex;
            retVal = DEM_IRT_PENDING;
            break;
        }
    }

    if( freezeFrameIndex >= nonObdFFDRecordNum )
    {
        *RestOfProcessableNumPtr = ( *RestOfProcessableNumPtr ) - loopCount;  /* no wrap around */
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_FFDMng_GetNumOfStoredNonObdFFD                       */
/* Description   | Get the number of stored Non OBD FFD.                    */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_FFDIndexType                                     */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_FFDIndexType, DEM_CODE ) Dem_FFDMng_GetNumOfStoredNonObdFFD
( void )
{
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) retNonObdFFDNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) freezeFrameIndex;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) nonObdFFDRecordNum;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posRecordStatus;

    retNonObdFFDNum = 0U;
    nonObdFFDRecordNum = Dem_NonObdFFDRecordNum;
    posRecordStatus = Dem_NonObdFreezeFrameDataPosTable.RecordStatus;                                               /* [GUD:CFG]posRecordStatus */

    for( freezeFrameIndex = (Dem_u08_FFDIndexType)0U; freezeFrameIndex < nonObdFFDRecordNum; freezeFrameIndex++ )   /* [GUD:for]freezeFrameIndex */
    {
        if( Dem_FreezeFrameRecordList[freezeFrameIndex].Data[posRecordStatus] == DEM_FFD_STORED )                   /* [GUD]freezeFrameIndex *//* [GUD]posRecordStatus */
        {
            retNonObdFFDNum = retNonObdFFDNum + (Dem_u08_OrderIndexType)1U;
        }
    }

    return retNonObdFFDNum;
}

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_FFDMng_CheckToExistTriggerFFD                        */
/* Description   | check to exsist trigger FFD                              */
/* Preconditions |                                                          */
/* Parameters    | [in] targetTrigger :                                     */
/*               |        The target trigger                                */
/*               | [in] dtcAttributePtr :                                   */
/*               |        pointer of DemDTCAttributes                       */
/*               | [out] FreezeFrameIndexPtr :                              */
/*               |        pointer of trigger freeze frame index             */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |          DEM_IRT_OK : Exist trigger FFD.                 */
/*               |          DEM_IRT_NG : Not Exist trigger FFD.             */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/*   v5-9-0      | branch changed.                                          */
/*   v5-10-0     | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_FFDMng_CheckToExistTriggerFFD
(
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) TargetTrigger,
    P2CONST( AB_83_ConstV Dem_DTCAttributeType, AUTOMATIC, DEM_CONFIG_DATA ) DtcAttributePtr,   /* [PRMCHK:CALLER] */
    P2CONST( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) FaultRecordPtr,
    P2VAR( Dem_u08_FFDIndexType, AUTOMATIC, AUTOMATIC ) FreezeFrameIndexPtr
)
{
    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA ) freezeFrameRecNumClassPtr;
    VAR( Dem_u16_FFRecNumClassIndexType, AUTOMATIC ) freezeframeRecNumClassRef;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) freezeFrameRecordIndex;
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC ) freezeFrameRecordClassIndex;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) freezeFrameIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonOBDFFRClassPerDTCMaxNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) nonObdFFDRecordNum;
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) trigger;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC )        freezeFrameRecordNumber;
    VAR( boolean, AUTOMATIC )                           freezeFrameRecordToDcm;

    nonOBDFFRClassPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;
    nonObdFFDRecordNum = Dem_NonObdFFDRecordNum;
    retVal = DEM_IRT_NG;

    freezeframeRecNumClassRef = DtcAttributePtr->DemFreezeFrameRecNumClassRef;                          /* [GUDCHK:CALLER]DtcAttributePtr *//* [GUD:CFG:IF_GUARDED: DtcAttributePtr ]freezeframeRecNumClassRef */
    freezeFrameRecNumClassPtr = &Dem_FreezeFrameRecNumClassTable[freezeframeRecNumClassRef];            /* [GUDCHK:CALLER]DtcAttributePtr */

    for( freezeFrameRecordIndex = (Dem_u08_FFListIndexType)0U; freezeFrameRecordIndex < nonOBDFFRClassPerDTCMaxNum; freezeFrameRecordIndex++ )  /* [GUD:for]freezeFrameRecordIndex */
    {
        freezeFrameIndex = FaultRecordPtr->RecordNumberIndex[freezeFrameRecordIndex];                                           /* [GUD]freezeFrameRecordIndex *//* [ARYCHK] DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / freezeFrameRecordIndex */
        if( freezeFrameIndex < nonObdFFDRecordNum )                                                                             /* [GUD:if]freezeFrameIndex */
        {
            freezeFrameRecordClassIndex = freezeFrameRecNumClassPtr->DemFreezeFrameRecordClassRef[freezeFrameRecordIndex];      /* [GUD]freezeFrameRecordIndex *//* [GUD:CFG:IF_GUARDED: freezeFrameRecordIndex ]freezeFrameRecordClassIndex *//* [ARYCHK] DEM_FF_RECORD_CLASS_REF_MAX_NUM / 1 / freezeFrameRecordIndex */

            Dem_CfgInfoPm_GetFreezeFrameRecordInfo_forOutput( freezeFrameRecordClassIndex, &freezeFrameRecordNumber, &trigger, &freezeFrameRecordToDcm );   /* [GUD] freezeFrameRecordClassIndex */

            if( TargetTrigger == trigger )
            {
                if ( freezeFrameRecordToDcm == (boolean)TRUE )
                {
                    *FreezeFrameIndexPtr = freezeFrameIndex;
                    retVal = DEM_IRT_OK;
                    break;
                }
            }
        }
    }

    return retVal;
}
#endif  /* (DEM_TSFF_PM_SUPPORT    STD_ON) */

/****************************************************************************/
/* Function Name | Dem_FFDMng_GetFFDConsystencyId                           */
/* Description   | check consistency of FFD record                          */
/* Preconditions |                                                          */
/* Parameters    | [in] FreezeFrameIndex :                                  */
/*               |        The FreezeFrame index                             */
/* Return Value  | Dem_u08_ConsistencyIdType                                */
/*               |        ConsistencyId                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_ConsistencyIdType, DEM_CODE ) Dem_FFDMng_GetFFDConsystencyId
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) FreezeFrameIndex             /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstCid;
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) consistencyId;

    posFirstCid = Dem_NonObdFreezeFrameDataPosTable.FirstCID;                                                   /* [GUD:CFG]posFirstCid */

    consistencyId = (Dem_u08_ConsistencyIdType)Dem_FreezeFrameRecordList[FreezeFrameIndex].Data[posFirstCid];   /* [GUDCHK:CALLER]FreezeFrameIndex *//* [GUD]posFirstCid */

    return consistencyId;
}


/****************************************************************************/
/* Function Name | Dem_FFDMng_CheckConsistency                              */
/* Description   | check consistency of FFD record                          */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex : The event index                    */
/*               | [in] FreezeFrameIndex : The freeze frame index           */
/* Return Value  | Dem_u08_InternalReturnType :                             */
/*               |       DEM_IRT_OK  : This FFDRecord is consistency.       */
/*               |       DEM_IRT_NG  : This FFDRecord is inconsistency.     */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_FFDMng_CheckConsistency
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) FreezeFrameIndex             /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) firstBlockEventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) lastBlockEventStrgIndex;
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) firstBlockCId;
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) lastBlockCId;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;

    Dem_FFDMng_GetFFDConsistencyInfo( FreezeFrameIndex, &firstBlockCId, &lastBlockCId, &firstBlockEventStrgIndex, &lastBlockEventStrgIndex );   /* [GUDCHK:CALLER]FreezeFrameIndex */

    if( EventStrgIndex == firstBlockEventStrgIndex )
    {
        if( firstBlockEventStrgIndex == lastBlockEventStrgIndex )
        {
            if( firstBlockCId == lastBlockCId )
            {
                retVal = Dem_FFDMng_VerifyChecksum( FreezeFrameIndex );     /* [GUDCHK:CALLER]FreezeFrameIndex */
            }
        }
    }

    return retVal;
}

#if ( DEM_FF_CHECKSUM_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_FFDMng_VerifyChecksum                                */
/* Description   | verify checksum of FFD record                            */
/* Preconditions |                                                          */
/* Parameters    | [in] FreezeFrameIndex : The freeze frame index           */
/* Return Value  | Dem_u08_InternalReturnType :                             */
/*               |       DEM_IRT_OK  : This checksum is consistency.        */
/*               |       DEM_IRT_NG  : This checksum is inconsistency.      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_FFDMng_VerifyChecksum
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) FreezeFrameIndex         /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_FFCheckSumType, AUTOMATIC ) registeredChecksum;
    VAR( Dem_u16_FFCheckSumType, AUTOMATIC ) calculatedChecksum;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) ffrMaxLength;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posDataStart;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    ffrMaxLength = Dem_FFRMaxLength;
    posDataStart = Dem_NonObdFreezeFrameDataPosTable.DataStart;                                 /* [GUD:CFG]posDataStart */
    retVal = DEM_IRT_NG;

    registeredChecksum = Dem_FFDMng_GetChecksum( FreezeFrameIndex );                            /* [GUDCHK:CALLER]FreezeFrameIndex */
    calculatedChecksum = Dem_UtlMem_Checksum( &Dem_FreezeFrameRecordList[FreezeFrameIndex].Data[posDataStart], ffrMaxLength );  /* [GUDCHK:CALLER]FreezeFrameIndex *//* [GUD]posDataStart */

    if( registeredChecksum == calculatedChecksum )
    {
        retVal = DEM_IRT_OK;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_FFDMng_GetChecksum                                   */
/* Description   | get checksum in FFD record                               */
/* Preconditions |                                                          */
/* Parameters    | [in] FreezeFrameIndex : The freeze frame index           */
/* Return Value  | uin16 :                                                  */
/*               |       The checksum value                                 */
/*               |       DEM_IRT_NG  : This checksum is inconsistency.      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u16_FFCheckSumType, DEM_CODE ) Dem_FFDMng_GetChecksum
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) FreezeFrameIndex         /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posChecksumUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posChecksumLower;
    VAR( uint8, AUTOMATIC ) checksumUpper;
    VAR( uint8, AUTOMATIC ) checksumLower;
    VAR( Dem_u16_FFCheckSumType, AUTOMATIC ) checksum;

    posChecksumUpper = Dem_NonObdFreezeFrameDataPosTable.ChecksumUpper;                 /* [GUD:CFG]posChecksumUpper */
    posChecksumLower = Dem_NonObdFreezeFrameDataPosTable.ChecksumLower;                 /* [GUD:CFG]posChecksumLower */

    checksumUpper = Dem_FreezeFrameRecordList[FreezeFrameIndex].Data[posChecksumUpper]; /* [GUDCHK:CALLER]FreezeFrameIndex *//* [GUD]posChecksumUpper */
    checksumLower = Dem_FreezeFrameRecordList[FreezeFrameIndex].Data[posChecksumLower]; /* [GUDCHK:CALLER]FreezeFrameIndex *//* [GUD]posChecksumLower */

    checksum = (Dem_u16_FFCheckSumType)checksumUpper << DEM_DATAMNG_CHECKSUM_SHIFT;
    checksum |= (Dem_u16_FFCheckSumType)checksumLower;

    return checksum;
}

#endif /* ( DEM_FF_CHECKSUM_SUPPORT == STD_ON ) */

#if ( DEM_FF_CHECKSUM_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_FFDMng_VerifyChecksum                                */
/* Description   | verify checksum of FFD record                            */
/* Preconditions |                                                          */
/* Parameters    | [in] FreezeFrameIndex : The freeze frame index           */
/* Return Value  | Dem_u08_InternalReturnType :                             */
/*               |       DEM_IRT_OK  : This checksum is consistency.        */
/*               |       DEM_IRT_NG  : This checksum is inconsistency.      */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_FFDMng_VerifyChecksum
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) FreezeFrameIndex                /* MISRA DEVIATION */
)
{
    return DEM_IRT_OK;
}
#endif /* ( DEM_FF_CHECKSUM_SUPPORT == STD_OFF ) */

/****************************************************************************/
/* Function Name | Dem_FFDMng_GetFFDConsistencyInfo                         */
/* Description   | check consistency of FFD record                          */
/* Preconditions |                                                          */
/* Parameters    | [in] FreezeFrameIndex :                                  */
/*               |        The FreezeFrame index                             */
/*               | [out] FirstBlockCIdPtr :                                 */
/*               |        The pointer of ConsistencyId of first block       */
/*               | [out] LastBlockCIdPtr :                                  */
/*               |        The pointer of ConsistencyId of last block        */
/*               | [out] FirstBlockEventStrgIndexPtr :                      */
/*               |        The pointer of EventStrgIndex of first block      */
/*               | [out] LastBlockEventStrgIndexPtr :                       */
/*               |        The pointer of EventStrgIndex of last block       */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_FFDMng_GetFFDConsistencyInfo
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) FreezeFrameIndex,            /* [PRMCHK:CALLER] */
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) FirstBlockCIdPtr,
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) LastBlockCIdPtr,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) FirstBlockEventStrgIndexPtr,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) LastBlockEventStrgIndexPtr
)
{
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstCid;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posLastCid;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) firstEventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) lastEventStrgIndex;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstEventStrgIndexUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstEventStrgIndexLower;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posLastEventStrgIndexUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posLastEventStrgIndexLower;

    posFirstCid = Dem_NonObdFreezeFrameDataPosTable.FirstCID;                                   /* [GUD:CFG]posFirstCid */
    posLastCid = Dem_NonObdFreezeFrameDataPosTable.LastCID;                                     /* [GUD:CFG]posLastCid */
    posFirstEventStrgIndexUpper = Dem_NonObdFreezeFrameDataPosTable.FirstEventStrgIndexUpper;   /* [GUD:CFG]posFirstEventStrgIndexUpper */
    posFirstEventStrgIndexLower = Dem_NonObdFreezeFrameDataPosTable.FirstEventStrgIndexLower;   /* [GUD:CFG]posFirstEventStrgIndexLower */
    posLastEventStrgIndexUpper = Dem_NonObdFreezeFrameDataPosTable.LastEventStrgIndexUpper;     /* [GUD:CFG]posLastEventStrgIndexUpper */
    posLastEventStrgIndexLower = Dem_NonObdFreezeFrameDataPosTable.LastEventStrgIndexLower;     /* [GUD:CFG]posLastEventStrgIndexLower */

    *FirstBlockCIdPtr = (Dem_u08_ConsistencyIdType)Dem_FreezeFrameRecordList[FreezeFrameIndex].Data[posFirstCid];   /* [GUDCHK:CALLER]FreezeFrameIndex *//* [GUD]posFirstCid */
    *LastBlockCIdPtr = (Dem_u08_ConsistencyIdType)Dem_FreezeFrameRecordList[FreezeFrameIndex].Data[posLastCid];     /* [GUDCHK:CALLER]FreezeFrameIndex *//* [GUD]posLastCid */
    firstEventStrgIndex = (Dem_u16_EventStrgIndexType)Dem_UtlMem_ConvertByteData( Dem_FreezeFrameRecordList[FreezeFrameIndex].Data[posFirstEventStrgIndexUpper], Dem_FreezeFrameRecordList[FreezeFrameIndex].Data[posFirstEventStrgIndexLower] );   /* [GUDCHK:CALLER]FreezeFrameIndex *//* [GUD]posFirstEventStrgIndexUpper *//* [GUD]posFirstEventStrgIndexLower */
    *FirstBlockEventStrgIndexPtr = firstEventStrgIndex;
    lastEventStrgIndex = (Dem_u16_EventStrgIndexType)Dem_UtlMem_ConvertByteData( Dem_FreezeFrameRecordList[FreezeFrameIndex].Data[posLastEventStrgIndexUpper], Dem_FreezeFrameRecordList[FreezeFrameIndex].Data[posLastEventStrgIndexLower] );      /* [GUDCHK:CALLER]FreezeFrameIndex *//* [GUD]posLastEventStrgIndexUpper *//* [GUD]posLastEventStrgIndexLower */
    *LastBlockEventStrgIndexPtr = lastEventStrgIndex;

    return;
}

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_FFDMng_InitMirrorMemory                              */
/* Description   | Initialize the Mirror Memory.                            */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_FFDMng_InitMirrorMemory
( void )
{
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) ffdStoredFormatSize;

    ffdStoredFormatSize = Dem_FreezeFrameDataStoredFormatSize;
    Dem_UtlMem_SetMemory( &Dem_TmpFFDMirror.Data[0], DEM_FFD_INITIAL, ffdStoredFormatSize );

    return;
}
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_FFDMng_GetEventIdFromRecordData                      */
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
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_FFDMng_GetEventIdFromRecordData
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) freezeFrameIndex;

    eventStrgIndex      =   DEM_EVENTSTRGINDEX_INVALID;
    freezeFrameIndex    =   ( Dem_u08_FFDIndexType )RecordIndex;

    retVal  =   Dem_DataMng_GetEventStrgIndexFromFFDRecord( freezeFrameIndex, &eventStrgIndex );
    if ( retVal == DEM_IRT_OK )
    {
        retVal  =   Dem_DataMng_GetEventIdFromEventStrgIndex( eventStrgIndex, EventIdPtr );
    }

    return retVal;
}
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
