/* Dem_PreFFDMng_c(v5-8-0)                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/PreFFDMng/CODE                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../cfg/Dem_NvM_Cfg.h"

#if ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Pm_DataAvl.h"
#include "../../../inc/Dem_Rc_ClrInfoMng.h"
#include "../../../inc/Dem_Rc_RecMngCmn.h"
#include "../../../inc/Dem_Rc_PreFFDMng.h"
#include "../../../inc/Dem_Rc_RecMngCmn.h"
#include "../../../inc/Dem_Rc_RecMngCmn_Table.h"
#include "../../../inc/Dem_Utl.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_PFM_EVENTSTRGINDEX_SHIFT                              ( (uint8)0x08U )
#define DEM_PFM_EVENTSTRGINDEX_MASK            ( (Dem_u16_EventStrgIndexType)0x00FFU )

#if ( DEM_FF_CHECKSUM_SUPPORT == STD_ON )

#define DEM_PFM_CHECKSUM_STORE_SHIFT                          ( (uint8)0x08U )
#define DEM_PFM_CHECKSUM_STORE_MASK        ( (Dem_u16_FFCheckSumType)0x00FFU )

#endif  /* ( DEM_FF_CHECKSUM_SUPPORT == STD_ON) */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
static FUNC( void, DEM_CODE ) Dem_PreFFDMng_InitMirrorRecord
( void );
#endif  /*  ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )   */
static FUNC( void, DEM_CODE ) Dem_PreFFDMng_UpdateConsistencyId
(
    VAR( Dem_u08_PreFFDIndexType, AUTOMATIC ) PreFFRecordIndex
);
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PreFFDMng_CheckConsistencyOfPreFFDRecord
(
    VAR( Dem_u08_PreFFDIndexType, AUTOMATIC ) PreFFRecordIndex
);

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PreFFDMng_SelectClearId
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) ObdClearId,
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) NonObdClearId,
    P2VAR( Dem_u08_ClearIdType, AUTOMATIC, AUTOMATIC ) SelectedClearIdPtr
);

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
static FUNC( void, DEM_CODE ) Dem_PreFFDMng_SetEventStrgIndexToMirror
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

static FUNC( void, DEM_CODE ) Dem_PreFFDMng_SetEventStrgIndexToPreFFRecord
(
    VAR( Dem_u08_PreFFDIndexType, AUTOMATIC ) PreFFRecordIndex,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);

static FUNC( void, DEM_CODE ) Dem_PreFFDMng_DivideEventStrgIndexToUpperAndLower
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) EventStrgIndexUpperPtr,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) EventStrgIndexLowerPtr
);

static FUNC( Dem_u16_EventStrgIndexType, DEM_CODE ) Dem_PreFFDMng_GetEventStrgIndexFromPreFFRecord
(
    VAR( Dem_u08_PreFFDIndexType, AUTOMATIC ) PreFFRecordIndex
);

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PreFFDMng_CheckEventAvailable
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);

static FUNC( void, DEM_CODE ) Dem_PreFFDMng_GetFFDConsistencyInfo
(
    VAR( Dem_u08_PreFFDIndexType, AUTOMATIC ) PreFFRecordIndex,
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) FirstBlockCIdPtr,
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) LastBlockCIdPtr,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) FirstBlockEventStrgIndexPtr,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) LastBlockEventStrgIndexPtr
);
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PreFFDMng_VerifyChecksum
(
    VAR( Dem_u08_PreFFDIndexType, AUTOMATIC ) PreFFRecordIndex
);
#if ( DEM_FF_CHECKSUM_SUPPORT == STD_ON )
static FUNC( Dem_u16_FFCheckSumType, DEM_CODE ) Dem_PreFFDMng_GetChecksum
(
    VAR( Dem_u08_PreFFDIndexType, AUTOMATIC ) PreFFRecordIndex
);
#endif /* ( DEM_FF_CHECKSUM_SUPPORT == STD_ON ) */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT ) Dem_PreFFDNvMStatus[DEM_PREFF_RECORD_LIST_NUM];
VAR( Dem_PreFFRecordType, DEM_VAR_NO_INIT ) Dem_TmpPreFFDMirror;
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

static VAR( Dem_u08_PreFFDIndexType, DEM_VAR_NO_INIT ) Dem_PreFFDIndexForVerify;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#define DEM_START_SEC_VAR_SAVED_ZONE
#include <Dem_MemMap.h>

VAR( Dem_PreFFRecordType,      DEM_VAR_SAVED_ZONE ) Dem_PrestoreFreezeFrameRecordList[DEM_PREFF_RECORD_LIST_NUM];

#define DEM_STOP_SEC_VAR_SAVED_ZONE
#include <Dem_MemMap.h>


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_PreFFDMng_Init                                       */
/* Description   | initialize function.                                     */
/* Preconditions |                                                          */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PreFFDMng_Init
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex     /* MISRA DEVIATION */
)
{
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    /* [FuncSw] */
    /*  initialize mirror memory area.      */
    Dem_PreFFDMng_InitMirrorRecord();
#endif  /*  ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )   */
    Dem_PreFFDIndexForVerify = (Dem_u08_PreFFDIndexType)0U;

    return;
}

/****************************************************************************/
/* Function Name | Dem_PreFFDMng_InitSavedZone                              */
/* Description   | Initialize savedzone process of prestore FFD.            */
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
FUNC( void, DEM_CODE ) Dem_PreFFDMng_InitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
   VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType      /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_PreFFDIndexType, AUTOMATIC ) preFFRecordListNum;
    VAR( Dem_u08_PreFFDIndexType, AUTOMATIC ) preFFRecordIndex;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) preFFStoredFormatSize;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindPreFF;

    preFFRecordListNum = Dem_PreFFRecordListNum;
    preFFStoredFormatSize = Dem_PreFFStoredFormatSize;
    recMngCmnKindPreFF = Dem_RecMngCmnKindPreFF;

    /* Sets initial value to the specified prestore freeze frame record. */
    /*  Dem_PrestoreFreezeFrameRecordList[preFFRecordIndex].Data[FirstEventStrgIndex] : DEM_EVENTSTRGINDEX_INVALID(same value as DEM_FFD_INITIAL.)  */
    /*  Dem_PrestoreFreezeFrameRecordList[preFFRecordIndex].Data[LastEventStrgIndex]  : DEM_EVENTSTRGINDEX_INVALID(same value as DEM_FFD_INITIAL.)  */
    /*  Dem_PrestoreFreezeFrameRecordList[preFFRecordIndex].Data[posClearID] : DEM_CLRINFO_RECORD_INITIAL(same value as DEM_FFD_INITIAL.)   */
    for( preFFRecordIndex = (Dem_u08_PreFFDIndexType)0U; preFFRecordIndex < preFFRecordListNum ; preFFRecordIndex++ )   /* [GUD:for]preFFRecordIndex */
    {
        Dem_UtlMem_SetMemory( &Dem_PrestoreFreezeFrameRecordList[preFFRecordIndex].Data[0], DEM_FFD_INITIAL, preFFStoredFormatSize );   /* [GUD]preFFRecordIndex */
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindPreFF, (Dem_u16_RecordIndexType)preFFRecordIndex );                               /* [GUD]preFFRecordIndex */
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_PreFFDMng_DataVerify                                 */
/* Description   | verify record data.                                      */
/* Preconditions |                                                          */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |          DEM_IRT_OK      : DataVerify completed.         */
/*               |          DEM_IRT_PENDING : Continue DataVerify.          */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PreFFDMng_DataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex     /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_PreFFDIndexType, AUTOMATIC ) preFFRecordListNum;
    VAR( Dem_u08_PreFFDIndexType, AUTOMATIC ) preFFRecordIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) nvmReadResult;
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) obdClearId;
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) nonObdClearId;
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) clearId;
    VAR( boolean, AUTOMATIC ) clearAllowed;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posClearID;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindPreFF;
    VAR( boolean, AUTOMATIC ) setEventStrgIndexNvmWriteFlg;
    VAR( Dem_u08_PreFFDIndexType,AUTOMATIC ) verifyLoopNumByCycle;
    VAR( Dem_u08_PreFFDIndexType,AUTOMATIC ) loopCount;
    VAR( Dem_u08_InternalReturnType,AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) chkEventResult;
    VAR( Dem_u08_InternalReturnType,AUTOMATIC ) retSelectClrIdResult;
    VAR( Dem_u08_InternalReturnType,AUTOMATIC ) retChkConsistencyResult;

    preFFRecordListNum = Dem_PreFFRecordListNum;
    posClearID = Dem_PreFreezeFrameDataPosTable.ClearID;        /* [GUD:CFG]posClearID */
    recMngCmnKindPreFF = Dem_RecMngCmnKindPreFF;
    verifyLoopNumByCycle = Dem_PreFFRecordNumForVerifyByCycle;
    loopCount = ( Dem_u08_PreFFDIndexType )0U;
    retVal = DEM_IRT_OK;

    nvmReadResult = Dem_ClrInfoMng_GetNvmReadResult();
    obdClearId = Dem_ClrInfoMng_GetObdClearID();
    nonObdClearId = Dem_ClrInfoMng_GetClearID();

    if( nvmReadResult == DEM_IRT_OK )
    {
        for( preFFRecordIndex = Dem_PreFFDIndexForVerify; preFFRecordIndex < preFFRecordListNum ; preFFRecordIndex++ )  /* [GUD:for]preFFRecordIndex */
        {
            if( loopCount < verifyLoopNumByCycle )
            {
                setEventStrgIndexNvmWriteFlg = (boolean)FALSE;
                eventStrgIndex = Dem_PreFFDMng_GetEventStrgIndexFromPreFFRecord( preFFRecordIndex );                    /* [GUD]preFFRecordIndex */
                clearId = DEM_CLRINFO_RECORD_INITIAL;

                retSelectClrIdResult = Dem_PreFFDMng_SelectClearId( eventStrgIndex, obdClearId, nonObdClearId, &clearId );
                if( retSelectClrIdResult == DEM_IRT_OK )
                {
                    if( Dem_PrestoreFreezeFrameRecordList[preFFRecordIndex].Data[posClearID] == clearId )               /* [GUD]preFFRecordIndex *//* [GUD]posClearID */
                    {
                        chkEventResult = Dem_PreFFDMng_CheckEventAvailable( eventStrgIndex );
                        if( chkEventResult == DEM_IRT_OK )
                        {
                            retChkConsistencyResult = Dem_PreFFDMng_CheckConsistencyOfPreFFDRecord( preFFRecordIndex ); /* [GUD]preFFRecordIndex */
                            if( retChkConsistencyResult == DEM_IRT_NG )
                            {
                                setEventStrgIndexNvmWriteFlg = (boolean)TRUE;
                            }
                        }
                        else
                        {
                            setEventStrgIndexNvmWriteFlg = (boolean)TRUE;
                        }
                    }
                    else
                    {
                        clearAllowed = Dem_CfgInfoPm_ClearAllowed_InEvtStrgGrp( eventStrgIndex );
                        if( clearAllowed == (boolean)TRUE )
                        {
                            Dem_PrestoreFreezeFrameRecordList[preFFRecordIndex].Data[posClearID] = clearId;                 /* [GUD]preFFRecordIndex *//* [GUD]posClearID */
                            Dem_PreFFDMng_SetEventStrgIndexToPreFFRecord( preFFRecordIndex, DEM_EVENTSTRGINDEX_INVALID );   /* [GUD]preFFRecordIndex */
                        }
                        else
                        {
                            retChkConsistencyResult = Dem_PreFFDMng_CheckConsistencyOfPreFFDRecord( preFFRecordIndex );     /* [GUD]preFFRecordIndex */
                            if( retChkConsistencyResult == DEM_IRT_NG )
                            {
                                setEventStrgIndexNvmWriteFlg = (boolean)TRUE;
                            }
                        }
                    }
                }
                else
                {
                    if( eventStrgIndex != DEM_EVENTSTRGINDEX_INVALID )
                    {
                        setEventStrgIndexNvmWriteFlg = (boolean)TRUE;
                    }
                }

                if( setEventStrgIndexNvmWriteFlg == (boolean)TRUE )
                {
                    Dem_PreFFDMng_SetEventStrgIndexToPreFFRecord( preFFRecordIndex, DEM_EVENTSTRGINDEX_INVALID );           /* [GUD]preFFRecordIndex */
                    Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindPreFF, (Dem_u16_RecordIndexType)preFFRecordIndex );       /* [GUD]preFFRecordIndex */
                }

                loopCount = loopCount + (Dem_u08_PreFFDIndexType)1U;
            }
            else
            {
                Dem_PreFFDIndexForVerify = preFFRecordIndex;
                retVal = DEM_IRT_PENDING;
                break;
            }
        }
    }
    else
    {
        for( preFFRecordIndex = Dem_PreFFDIndexForVerify; preFFRecordIndex < preFFRecordListNum ; preFFRecordIndex++ )      /* [GUD:for]preFFRecordIndex */
        {
            if( loopCount < verifyLoopNumByCycle )
            {
                setEventStrgIndexNvmWriteFlg = (boolean)FALSE;
                eventStrgIndex = Dem_PreFFDMng_GetEventStrgIndexFromPreFFRecord( preFFRecordIndex );                        /* [GUD]preFFRecordIndex */
                clearId = DEM_CLRINFO_RECORD_INITIAL;

                retSelectClrIdResult = Dem_PreFFDMng_SelectClearId( eventStrgIndex, obdClearId, nonObdClearId, &clearId );
                if( retSelectClrIdResult == DEM_IRT_OK )
                {
                    chkEventResult = Dem_PreFFDMng_CheckEventAvailable( eventStrgIndex );
                    if( chkEventResult == DEM_IRT_OK )
                    {
                        clearAllowed = Dem_CfgInfoPm_ClearAllowedByConfig_InEvtStrgGrp( eventStrgIndex );
                        if( clearAllowed == (boolean)TRUE )
                        {
                            setEventStrgIndexNvmWriteFlg = (boolean)TRUE;
                            Dem_PrestoreFreezeFrameRecordList[preFFRecordIndex].Data[posClearID] = clearId;                 /* [GUD]preFFRecordIndex *//* [GUD]posClearID */
                        }
                        else
                        {
                            retChkConsistencyResult = Dem_PreFFDMng_CheckConsistencyOfPreFFDRecord( preFFRecordIndex );
                            if( retChkConsistencyResult == DEM_IRT_NG )
                            {
                                setEventStrgIndexNvmWriteFlg = (boolean)TRUE;
                            }
                        }
                    }
                    else
                    {
                        setEventStrgIndexNvmWriteFlg = (boolean)TRUE;
                    }
                }
                else
                {
                    setEventStrgIndexNvmWriteFlg = (boolean)TRUE;
                }

                if( setEventStrgIndexNvmWriteFlg == (boolean)TRUE )
                {
                    Dem_PreFFDMng_SetEventStrgIndexToPreFFRecord( preFFRecordIndex, DEM_EVENTSTRGINDEX_INVALID );       /* [GUD]preFFRecordIndex */
                    Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindPreFF, (Dem_u16_RecordIndexType)preFFRecordIndex );   /* [GUD]preFFRecordIndex */
                }

                loopCount = loopCount + (Dem_u08_PreFFDIndexType)1U;
            }
            else
            {
                Dem_PreFFDIndexForVerify = preFFRecordIndex;
                retVal = DEM_IRT_PENDING;
                break;
            }
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_PreFFDMng_InitFreezeFrameRecord                      */
/* Description   | Initializes PrestoreFreezeFrameRecordMng.                */
/* Preconditions | none                                                     */
/* Parameters    | [out] PreFFRecordMngPtr :                                */
/*               |        The pointer of PrestoreFreezeFrameRecordMng.      */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PreFFDMng_InitFreezeFrameRecord
(
    P2VAR( Dem_PreFFRecordMngType, AUTOMATIC, AUTOMATIC ) PreFFRecordMngPtr
)
{
    PreFFRecordMngPtr->EventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
    PreFFRecordMngPtr->DataPtr = NULL_PTR;

    return;
}

/****************************************************************************/
/* Function Name | Dem_PreFFDMng_GetFreezeFrameRecord                       */
/* Description   | Gets PrestoreFreezeFrameRecord.                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] PreFFRecordIndex :                                  */
/*               |        The index for Dem_PrestoreFreezeFrameRecordList.  */
/*               | [out] PreFFRecordMngPtr :                                */
/*               |        The EventStrgIndex and the starting point of data for */
/*               |        PrestoreFreezeFrameRecord  which to be pointed by */
/*               |        the specified PreFFRecordIndex.                   */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |       DEM_IRT_OK : Getting was succeded.                 */
/*               |       DEM_IRT_NG : Getting was failed.                   */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PreFFDMng_GetFreezeFrameRecord
(
    VAR( Dem_u08_PreFFDIndexType, AUTOMATIC ) PreFFRecordIndex,
    P2VAR( Dem_PreFFRecordMngType, AUTOMATIC, AUTOMATIC ) PreFFRecordMngPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_PreFFDIndexType, AUTOMATIC ) preFFRecordListNum;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posDataStart;

    retVal = DEM_IRT_NG;
    preFFRecordListNum = Dem_PreFFRecordListNum;

    if( PreFFRecordIndex < preFFRecordListNum )     /* [GUD:if]PreFFRecordIndex */
    {
        posDataStart = Dem_PreFreezeFrameDataPosTable.DataStart;    /* [GUD:CFG]posDataStart */

        PreFFRecordMngPtr->EventStrgIndex = Dem_PreFFDMng_GetEventStrgIndexFromPreFFRecord( PreFFRecordIndex ); /* [GUD]PreFFRecordIndex */
        PreFFRecordMngPtr->DataPtr = &Dem_PrestoreFreezeFrameRecordList[PreFFRecordIndex].Data[posDataStart];   /* [GUD]PreFFRecordIndex *//* [GUD]posDataStart */
        retVal = DEM_IRT_OK;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_PreFFDMng_SetEventStrgIndex                          */
/* Description   | Sets EventStrgIndex to PrestoreFreezeFrameRecord.        */
/* Preconditions | none                                                     */
/* Parameters    | [in] PreFFRecordIndex :                                  */
/*               |        The index for Dem_PrestoreFreezeFrameRecordList.  */
/*               | [out] EventStrgIndex :                                       */
/*               |        The EventStrgIndex to set PrestoreFreezeFrameRecord   */
/*               |        which to be pointed by the specified PreFFRecord- */
/*               |        Index.                                            */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PreFFDMng_SetEventStrgIndex
(
    VAR( Dem_u08_PreFFDIndexType, AUTOMATIC ) PreFFRecordIndex,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u08_PreFFDIndexType, AUTOMATIC ) preFFRecordListNum;

    preFFRecordListNum = Dem_PreFFRecordListNum;

    if( PreFFRecordIndex < preFFRecordListNum )     /* [GUD:if]PreFFRecordIndex */
    {
        Dem_PreFFDMng_SetEventStrgIndexToPreFFRecord( PreFFRecordIndex, EventStrgIndex );       /* [GUD]PreFFRecordIndex */
    }

    return ;
}

#if ( DEM_FF_CHECKSUM_SUPPORT == STD_ON)
/****************************************************************************/
/* Function Name | Dem_PreFFDMng_SetChecksum                                */
/* Description   | Sets checksum for PreFFD.                                */
/* Preconditions |                                                          */
/* Parameters    | [in] PreFFRecordIndex :                                  */
/*               |        The index for Dem_PrestoreFreezeFrameRecordList.  */
/* Return Value  | void                                                     */
/* Notes         | The specified PreFFRecordIndex guarantees the range.     */
/*               | May be called within the exclusive section "PrestoreFre- */
/*               | ezeFrame".                                               */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PreFFDMng_SetChecksum
(
    VAR( Dem_u08_PreFFDIndexType, AUTOMATIC ) PreFFRecordIndex              /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posDataStart;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posChecksumUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posChecksumLower;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) preFFDMaxLength;
    VAR( Dem_u16_FFCheckSumType, AUTOMATIC ) chksum;

    posDataStart = Dem_PreFreezeFrameDataPosTable.DataStart;            /* [GUD:CFG]posDataStart */
    posChecksumUpper = Dem_PreFreezeFrameDataPosTable.ChecksumUpper;    /* [GUD:CFG]posChecksumUpper */
    posChecksumLower = Dem_PreFreezeFrameDataPosTable.ChecksumLower;    /* [GUD:CFG]posChecksumLower */
    preFFDMaxLength = Dem_PreFFDMaxLength;

    chksum = Dem_UtlMem_Checksum( &Dem_PrestoreFreezeFrameRecordList[PreFFRecordIndex].Data[posDataStart], preFFDMaxLength );       /* [GUDCHK:CALLER]PreFFRecordIndex *//* [GUD]posDataStart */

    Dem_PrestoreFreezeFrameRecordList[PreFFRecordIndex].Data[posChecksumUpper] = (uint8)( chksum >> DEM_PFM_CHECKSUM_STORE_SHIFT ); /* [GUDCHK:CALLER]PreFFRecordIndex *//* [GUD]posChecksumUpper */
    Dem_PrestoreFreezeFrameRecordList[PreFFRecordIndex].Data[posChecksumLower] = (uint8)( chksum & DEM_PFM_CHECKSUM_STORE_MASK );   /* [GUDCHK:CALLER]PreFFRecordIndex *//* [GUD]posChecksumLower */

    return;
}
#endif  /* ( DEM_FF_CHECKSUM_SUPPORT == STD_ON) */

/****************************************************************************/
/* Function Name | Dem_PreFFDMng_SetUpdateRequest                           */
/* Description   | set record data and start NvM update.                    */
/* Preconditions |                                                          */
/* Parameters    | [in] PreFFRecordIndex :                                  */
/*               |        The index for Dem_PrestoreFreezeFrameRecordList.  */
/* Return Value  | void                                                     */
/* Notes         | The specified PreFFRecordIndex guarantees the range.     */
/*               | May be called within the exclusive section "PrestoreFre- */
/*               | ezeFrame".                                               */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PreFFDMng_SetUpdateRequest
(
    VAR( Dem_u08_PreFFDIndexType, AUTOMATIC ) PreFFRecordIndex              /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) selectResult;
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) obdClearId;
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) nonObdClearId;
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) clearId;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posClearID;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindPreFF;

    obdClearId = Dem_ClrInfoMng_GetObdClearID();
    nonObdClearId = Dem_ClrInfoMng_GetClearID();
    clearId = DEM_CLRINFO_RECORD_INITIAL;

    eventStrgIndex = Dem_PreFFDMng_GetEventStrgIndexFromPreFFRecord( PreFFRecordIndex );

    selectResult = Dem_PreFFDMng_SelectClearId( eventStrgIndex, obdClearId, nonObdClearId, &clearId );
    if( selectResult == DEM_IRT_OK )
    {
        posClearID = Dem_PreFreezeFrameDataPosTable.ClearID;            /* [GUD:CFG]posClearID */

        Dem_PrestoreFreezeFrameRecordList[PreFFRecordIndex].Data[posClearID] = clearId; /* [GUDCHK:CALLER]PreFFRecordIndex *//* [GUD]posClearID */
        Dem_PreFFDMng_UpdateConsistencyId( PreFFRecordIndex );                          /* [GUDCHK:CALLER]PreFFRecordIndex */

        /*  start of record update to NvM.      */
        recMngCmnKindPreFF = Dem_RecMngCmnKindPreFF;
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindPreFF, (Dem_u16_RecordIndexType)PreFFRecordIndex );   /* [GUDCHK:CALLER]PreFFRecordIndex */
    }

    return;
}

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_PreFFDMng_SetRecordMirror                            */
/* Description   | Set the Writing RamData.                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/*               | [in/out] BlockMirrorPtr :                                */
/*               |        Nonvolatile synchronous data information.         */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PreFFDMng_SetRecordMirror
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
)
{
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) preFFRecordListNum;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) preFFStoredFormatSize;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) preFFDDataIndex;
    VAR( Dem_u08_PreFFDIndexType, AUTOMATIC ) preFFRecordIndex;

    preFFStoredFormatSize = Dem_PreFFStoredFormatSize;

    if( BlockMirrorPtr->RecordDataOffset == (Dem_u16_RecordDataSizeType)0U )
    {
        preFFRecordListNum = (Dem_u16_RecordIndexType)Dem_PreFFRecordListNum;
        if( BlockMirrorPtr->RecordIndex < preFFRecordListNum )                          /* [GUD:if]BlockMirrorPtr->RecordIndex */
        {
            preFFRecordIndex = (Dem_u08_PreFFDIndexType)BlockMirrorPtr->RecordIndex;    /* [GUD]preFFRecordIndex */

            /* copy data to mirror area. */
            Dem_UtlMem_CopyMemory( &Dem_TmpPreFFDMirror.Data[0], &(Dem_PrestoreFreezeFrameRecordList[preFFRecordIndex].Data[0]), preFFStoredFormatSize );   /* [GUD]preFFRecordIndex */
        }
    }

    preFFDDataIndex = Dem_PreFFDRecordNvBlockSize * BlockMirrorPtr->RecordDataOffset;
    if( preFFDDataIndex < preFFStoredFormatSize )                                   /* [GUD:if]preFFDDataIndex */
    {
        BlockMirrorPtr->MirrorPtr = &Dem_TmpPreFFDMirror.Data[ preFFDDataIndex ];   /* [GUD]preFFRecordIndex */
    }

    return;
}

#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_PreFFDMng_InitMirrorRecord                           */
/* Description   | Initializes the Mirror Memory.                           */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_PreFFDMng_InitMirrorRecord
( void )
{
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posClearID;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) preFFStoredFormatSize;

    /*  initialize mirror memory area.              */
    preFFStoredFormatSize = Dem_PreFFStoredFormatSize;
    Dem_UtlMem_SetMemory( &Dem_TmpPreFFDMirror.Data[0], DEM_FFD_INITIAL, preFFStoredFormatSize );

    posClearID = Dem_PreFreezeFrameDataPosTable.ClearID;                /* [GUD:CFG]posClearID */

    Dem_PreFFDMng_SetEventStrgIndexToMirror( DEM_EVENTSTRGINDEX_INVALID );
    Dem_TmpPreFFDMirror.Data[posClearID] = DEM_CLRINFO_RECORD_INITIAL;  /* [GUD]posClearID */

    return;

}
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */


/****************************************************************************/
/* Function Name | Dem_PreFFDMng_UpdateConsistencyId                        */
/* Description   | Decriment and sets the consistency Id of PreFFDRecord    */
/*               | to the PreFFDRecord corresponding to the                 */
/*               | specified PreFFDRecord index.                            */
/* Preconditions | none                                                     */
/*               |                                                          */
/* Parameters    | [in] PreFFRecordIndex :                                  */
/*               |        The index for Dem_PrestoreFreezeFrameRecordList.  */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_PreFFDMng_UpdateConsistencyId
(
    VAR( Dem_u08_PreFFDIndexType, AUTOMATIC ) PreFFRecordIndex              /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) firstBlockCid;
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) updatedCid;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstCid;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posLastCid;

    posFirstCid = Dem_PreFreezeFrameDataPosTable.FirstCID;  /* [GUD:CFG]posFirstCid */
    posLastCid = Dem_PreFreezeFrameDataPosTable.LastCID;    /* [GUD:CFG]posLastCid */

    firstBlockCid = (Dem_u08_ConsistencyIdType)Dem_PrestoreFreezeFrameRecordList[PreFFRecordIndex].Data[posFirstCid];   /* [GUDCHK:CALLER]PreFFRecordIndex *//* [GUD]posFirstCid */

    updatedCid = Dem_UtlCid_CalcConsistencyId( firstBlockCid );

    Dem_PrestoreFreezeFrameRecordList[PreFFRecordIndex].Data[posFirstCid] = updatedCid; /* [GUDCHK:CALLER]PreFFRecordIndex *//* [GUD]posFirstCid */
    Dem_PrestoreFreezeFrameRecordList[PreFFRecordIndex].Data[posLastCid] = updatedCid;  /* [GUDCHK:CALLER]PreFFRecordIndex *//* [GUD]posLastCid */

    return;
}


/****************************************************************************/
/* Function Name | Dem_PreFFDMng_CheckConsistencyOfPreFFDRecord             */
/* Description   | Checks consistency of PreFFDRecord corresponding to the  */
/*               | PreFFD record index.                                     */
/* Preconditions | [in]PreFFRecordIndex :                                   */
/*               |        The index for Dem_PrestoreFreezeFrameRecord.      */
/* Return Value  | Dem_u08_InternalReturnType :                             */
/*               |       DEM_IRT_OK  : This PreFFDRecord is consistency.    */
/*               |       DEM_IRT_NG  : This PreFFDRecord is inconsistency.  */
/* Notes         | none                                                     */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PreFFDMng_CheckConsistencyOfPreFFDRecord
(
    VAR( Dem_u08_PreFFDIndexType, AUTOMATIC ) PreFFRecordIndex
)
{
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) firstBlockCId;
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) lastBlockCId;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) firstBlockEventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) lastBlockEventStrgIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;

    Dem_PreFFDMng_GetFFDConsistencyInfo( PreFFRecordIndex, &firstBlockCId, &lastBlockCId, &firstBlockEventStrgIndex, &lastBlockEventStrgIndex );

    if( firstBlockEventStrgIndex == lastBlockEventStrgIndex )
    {
        if( firstBlockCId == lastBlockCId )
        {
            retVal = Dem_PreFFDMng_VerifyChecksum( PreFFRecordIndex );
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_PreFFDMng_GetFFDConsistencyInfo                      */
/* Description   | check consistency of OBD FFD record                      */
/* Preconditions |                                                          */
/* Parameters    | [in] PreFFRecordIndex :                                  */
/*               |        The index for Dem_PrestoreFreezeFrameRecord       */
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
static FUNC( void, DEM_CODE ) Dem_PreFFDMng_GetFFDConsistencyInfo
(
    VAR( Dem_u08_PreFFDIndexType, AUTOMATIC ) PreFFRecordIndex,                 /* [PRMCHK:CALLER] */
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) FirstBlockCIdPtr,
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) LastBlockCIdPtr,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) FirstBlockEventStrgIndexPtr,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) LastBlockEventStrgIndexPtr
)
{
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstCid;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posLastCid;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstEventStrgIndexUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstEventStrgIndexLower;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posLastEventStrgIndexUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posLastEventStrgIndexLower;


    posFirstCid = Dem_PreFreezeFrameDataPosTable.FirstCID;                                      /* [GUD:CFG]posFirstCid */
    posLastCid = Dem_PreFreezeFrameDataPosTable.LastCID;                                        /* [GUD:CFG]posLastCid */
    posFirstEventStrgIndexUpper = Dem_PreFreezeFrameDataPosTable.FirstEventStrgIndexUpper;      /* [GUD:CFG]posFirstEventStrgIndexUpper */
    posFirstEventStrgIndexLower = Dem_PreFreezeFrameDataPosTable.FirstEventStrgIndexLower;      /* [GUD:CFG]posFirstEventStrgIndexLower */
    posLastEventStrgIndexUpper = Dem_PreFreezeFrameDataPosTable.LastEventStrgIndexUpper;        /* [GUD:CFG]posLastEventStrgIndexUpper  */
    posLastEventStrgIndexLower = Dem_PreFreezeFrameDataPosTable.LastEventStrgIndexLower;        /* [GUD:CFG]posLastEventStrgIndexLower  */

    *FirstBlockCIdPtr = (Dem_u08_ConsistencyIdType)Dem_PrestoreFreezeFrameRecordList[PreFFRecordIndex].Data[posFirstCid];       /* [GUDCHK:CALLER]PreFFRecordIndex *//* [GUD]posFirstCid */
    *LastBlockCIdPtr = (Dem_u08_ConsistencyIdType)Dem_PrestoreFreezeFrameRecordList[PreFFRecordIndex].Data[posLastCid];         /* [GUDCHK:CALLER]PreFFRecordIndex *//* [GUD]posLastCid */
    *FirstBlockEventStrgIndexPtr = (Dem_u16_EventStrgIndexType)( (Dem_u16_EventStrgIndexType)Dem_PrestoreFreezeFrameRecordList[PreFFRecordIndex].Data[posFirstEventStrgIndexUpper] << DEM_PFM_EVENTSTRGINDEX_SHIFT );   /* [GUDCHK:CALLER]PreFFRecordIndex *//* [GUD]posFirstEventStrgIndexUpper */
    *FirstBlockEventStrgIndexPtr |= (Dem_u16_EventStrgIndexType)Dem_PrestoreFreezeFrameRecordList[PreFFRecordIndex].Data[posFirstEventStrgIndexLower];                                                                  /* [GUDCHK:CALLER]PreFFRecordIndex *//* [GUD]posFirstEventStrgIndexLower */
    *LastBlockEventStrgIndexPtr = (Dem_u16_EventStrgIndexType)( (Dem_u16_EventStrgIndexType)Dem_PrestoreFreezeFrameRecordList[PreFFRecordIndex].Data[posLastEventStrgIndexUpper] << DEM_PFM_EVENTSTRGINDEX_SHIFT );     /* [GUDCHK:CALLER]PreFFRecordIndex *//* [GUD]posLastEventStrgIndexUpper  */
    *LastBlockEventStrgIndexPtr |= (Dem_u16_EventStrgIndexType)Dem_PrestoreFreezeFrameRecordList[PreFFRecordIndex].Data[posLastEventStrgIndexLower];                                                                    /* [GUDCHK:CALLER]PreFFRecordIndex *//* [GUD]posLastEventStrgIndexLower  */

    return;
}


#if ( DEM_FF_CHECKSUM_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_PreFFDMng_VerifyChecksum                             */
/* Description   | verify checksum of PrestoreFreezeFrameRecord             */
/* Preconditions |                                                          */
/* Parameters    | [in] PreFFRecordIndex :                                  */
/*               |        The index for Dem_PrestoreFreezeFrameRecord       */
/* Return Value  | Dem_u08_InternalReturnType :                             */
/*               |       DEM_IRT_OK  : This checksum is consistency.        */
/*               |       DEM_IRT_NG  : This checksum is inconsistency.      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PreFFDMng_VerifyChecksum
(
    VAR( Dem_u08_PreFFDIndexType, AUTOMATIC ) PreFFRecordIndex              /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_FFCheckSumType, AUTOMATIC ) registeredChecksum;
    VAR( Dem_u16_FFCheckSumType, AUTOMATIC ) calculatedChecksum;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) preFFDMaxLength;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posDataStart;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    preFFDMaxLength = Dem_PreFFDMaxLength;
    posDataStart = Dem_PreFreezeFrameDataPosTable.DataStart;    /* [GUD:CFG]posDataStart */
    retVal = DEM_IRT_NG;

    registeredChecksum = Dem_PreFFDMng_GetChecksum( PreFFRecordIndex ); /* [GUDCHK:CALLER]PreFFRecordIndex */
    calculatedChecksum = Dem_UtlMem_Checksum( &Dem_PrestoreFreezeFrameRecordList[PreFFRecordIndex].Data[posDataStart], preFFDMaxLength );   /* [GUDCHK:CALLER]PreFFRecordIndex *//* [GUD]posDataStart */

    if( registeredChecksum == calculatedChecksum )
    {
        retVal = DEM_IRT_OK;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_PreFFDMng_GetChecksum                                */
/* Description   | get checksum in PrestoreFreezeFrameRecord                */
/* Preconditions |                                                          */
/* Parameters    | [in] PreFFRecordIndex :                                  */
/*               |        The index for Dem_PrestoreFreezeFrameRecord       */
/* Return Value  | uin16 :                                                  */
/*               |       The checksum value                                 */
/*               |       DEM_IRT_NG  : This checksum is inconsistency.      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u16_FFCheckSumType, DEM_CODE ) Dem_PreFFDMng_GetChecksum
(
    VAR( Dem_u08_PreFFDIndexType, AUTOMATIC ) PreFFRecordIndex              /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posChecksumUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posChecksumLower;
    VAR( uint8, AUTOMATIC ) checksumUpper;
    VAR( uint8, AUTOMATIC ) checksumLower;
    VAR( Dem_u16_FFCheckSumType, AUTOMATIC ) checksum;


    posChecksumUpper = Dem_PreFreezeFrameDataPosTable.ChecksumUpper;    /* [GUD:CFG]posChecksumUpper */
    posChecksumLower = Dem_PreFreezeFrameDataPosTable.ChecksumLower;    /* [GUD:CFG]posChecksumLower */

    checksumUpper = Dem_PrestoreFreezeFrameRecordList[PreFFRecordIndex].Data[posChecksumUpper]; /* [GUDCHK:CALLER]PreFFRecordIndex *//* [GUD]posChecksumUpper */
    checksumLower = Dem_PrestoreFreezeFrameRecordList[PreFFRecordIndex].Data[posChecksumLower]; /* [GUDCHK:CALLER]PreFFRecordIndex *//* [GUD]posChecksumLower */


    checksum = (Dem_u16_FFCheckSumType)checksumUpper << DEM_PFM_EVENTSTRGINDEX_SHIFT;
    checksum |= (Dem_u16_FFCheckSumType)checksumLower;

    return checksum;
}

#endif  /* ( DEM_FF_CHECKSUM_SUPPORT == STD_ON ) */

#if ( DEM_FF_CHECKSUM_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_PreFFDMng_VerifyChecksum                             */
/* Description   | verify checksum of PrestoreFreezeFrameRecord             */
/* Preconditions |                                                          */
/* Parameters    | [in] PreFFRecordIndex :                                  */
/*               |        The index for Dem_PrestoreFreezeFrameRecord       */
/* Return Value  | Dem_u08_InternalReturnType :                             */
/*               |       DEM_IRT_OK  : This checksum is consistency.        */
/*               |       DEM_IRT_NG  : This checksum is inconsistency.      */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PreFFDMng_VerifyChecksum
(
    VAR( Dem_u08_PreFFDIndexType, AUTOMATIC ) PreFFRecordIndex              /* MISRA DEVIATION */
)
{
    return DEM_IRT_OK;
}
#endif /* ( DEM_FF_CHECKSUM_SUPPORT == STD_OFF ) */


/****************************************************************************/
/* Function Name | Dem_PreFFDMng_SelectClearId                              */
/* Description   | Selects whether clear ID is OBD or non-OBD.              */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The index for Dem_EventRecordList.                */
/*               | [in] ObdClearId :                                        */
/*               |        The clear-ID for OBD.                             */
/*               | [in] NonObdClearId :                                     */
/*               |        The clear-ID for non-OBD.                         */
/*               | [out] SelectedClearIdPtr :                               */
/*               |        The selected clear-ID.                            */
/* Return Value  | Dem_u08_InternalReturnType :                             */
/*               |       DEM_IRT_OK  : The selection was succeeded.         */
/*               |       DEM_IRT_NG  : The selection was failed.            */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PreFFDMng_SelectClearId
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) ObdClearId,
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) NonObdClearId,
    P2VAR( Dem_u08_ClearIdType, AUTOMATIC, AUTOMATIC ) SelectedClearIdPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( boolean, AUTOMATIC ) eventOBDKind;

    retVal = DEM_IRT_NG;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    if( EventStrgIndex < eventStorageNum )                                                                  /* [GUD:if]EventStrgIndex */
    {
        eventOBDKind    =   Dem_CfgInfoPm_CheckEventKindOfOBD_InEvtStrgGrp( EventStrgIndex );
        if( eventOBDKind == (boolean)TRUE ) /*  OBD     */
        {
            (*SelectedClearIdPtr) = ObdClearId;
        }
        else
        {
            (*SelectedClearIdPtr) = NonObdClearId;
        }

        retVal = DEM_IRT_OK;
    }

    return retVal;
}

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_PreFFDMng_SetEventStrgIndexToMirror                  */
/* Description   | Sets the specified EventStrgIndex to mirror memory.      */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The index for Dem_EventRecordList.                */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_PreFFDMng_SetEventStrgIndexToMirror
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( uint8, AUTOMATIC ) eventStrgIndexUpper;
    VAR( uint8, AUTOMATIC ) eventStrgIndexLower;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstEventStrgIndexUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstEventStrgIndexLower;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posLastEventStrgIndexUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posLastEventStrgIndexLower;

    Dem_PreFFDMng_DivideEventStrgIndexToUpperAndLower( EventStrgIndex, &eventStrgIndexUpper, &eventStrgIndexLower );

    posFirstEventStrgIndexUpper = Dem_PreFreezeFrameDataPosTable.FirstEventStrgIndexUpper;  /* [GUD:CFG]posFirstEventStrgIndexUpper */
    posFirstEventStrgIndexLower = Dem_PreFreezeFrameDataPosTable.FirstEventStrgIndexLower;  /* [GUD:CFG]posFirstEventStrgIndexLower */
    posLastEventStrgIndexUpper = Dem_PreFreezeFrameDataPosTable.LastEventStrgIndexUpper;    /* [GUD:CFG]posLastEventStrgIndexUpper  */
    posLastEventStrgIndexLower = Dem_PreFreezeFrameDataPosTable.LastEventStrgIndexLower;    /* [GUD:CFG]posLastEventStrgIndexLower  */

    Dem_TmpPreFFDMirror.Data[posFirstEventStrgIndexUpper] = eventStrgIndexUpper;    /* [GUD]posFirstEventStrgIndexUpper */
    Dem_TmpPreFFDMirror.Data[posFirstEventStrgIndexLower] = eventStrgIndexLower;    /* [GUD]posFirstEventStrgIndexLower */
    Dem_TmpPreFFDMirror.Data[posLastEventStrgIndexUpper] = eventStrgIndexUpper;     /* [GUD]posLastEventStrgIndexUpper  */
    Dem_TmpPreFFDMirror.Data[posLastEventStrgIndexLower] = eventStrgIndexLower;     /* [GUD]posLastEventStrgIndexLower  */

    return;
}
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

/****************************************************************************/
/* Function Name | Dem_PreFFDMng_SetEventStrgIndexToPreFFRecord                 */
/* Description   | Sets the specified EventStrgIndex to Dem_PrestoreFreezeFram- */
/*               | eRecordList[] corresponding to the specified PreFFRecor- */
/*               | dIndex.                                                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] PreFFRecordIndex :                                  */
/*               |        The index for Dem_PrestoreFreezeFrameRecordList.  */
/*               | [in] EventStrgIndex :                                    */
/*               |        The index for Dem_EventRecordList.                */
/* Return Value  | void                                                     */
/* Notes         | The specified PreFFRecordIndex guarantees the range.     */
/*               | May be called within the exclusive section "PrestoreFre- */
/*               | ezeFrame".                                               */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_PreFFDMng_SetEventStrgIndexToPreFFRecord
(
    VAR( Dem_u08_PreFFDIndexType, AUTOMATIC ) PreFFRecordIndex,             /* [PRMCHK:CALLER] */
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( uint8, AUTOMATIC ) eventStrgIndexUpper;
    VAR( uint8, AUTOMATIC ) eventStrgIndexLower;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstEventStrgIndexUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstEventStrgIndexLower;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posLastEventStrgIndexUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posLastEventStrgIndexLower;

    Dem_PreFFDMng_DivideEventStrgIndexToUpperAndLower( EventStrgIndex, &eventStrgIndexUpper, &eventStrgIndexLower );

    posFirstEventStrgIndexUpper = Dem_PreFreezeFrameDataPosTable.FirstEventStrgIndexUpper;  /* [GUD:CFG]posFirstEventStrgIndexUpper */
    posFirstEventStrgIndexLower = Dem_PreFreezeFrameDataPosTable.FirstEventStrgIndexLower;  /* [GUD:CFG]posFirstEventStrgIndexLower */
    posLastEventStrgIndexUpper = Dem_PreFreezeFrameDataPosTable.LastEventStrgIndexUpper;    /* [GUD:CFG]posLastEventStrgIndexUpper  */
    posLastEventStrgIndexLower = Dem_PreFreezeFrameDataPosTable.LastEventStrgIndexLower;    /* [GUD:CFG]posLastEventStrgIndexLower  */

    Dem_PrestoreFreezeFrameRecordList[PreFFRecordIndex].Data[posFirstEventStrgIndexUpper] = eventStrgIndexUpper;    /* [GUDCHK:CALLER]PreFFRecordIndex *//* [GUD:CFG]posFirstEventStrgIndexUpper */
    Dem_PrestoreFreezeFrameRecordList[PreFFRecordIndex].Data[posFirstEventStrgIndexLower] = eventStrgIndexLower;    /* [GUDCHK:CALLER]PreFFRecordIndex *//* [GUD:CFG]posFirstEventStrgIndexLower */
    Dem_PrestoreFreezeFrameRecordList[PreFFRecordIndex].Data[posLastEventStrgIndexUpper] = eventStrgIndexUpper;     /* [GUDCHK:CALLER]PreFFRecordIndex *//* [GUD:CFG]posLastEventStrgIndexUpper  */
    Dem_PrestoreFreezeFrameRecordList[PreFFRecordIndex].Data[posLastEventStrgIndexLower] = eventStrgIndexLower;     /* [GUDCHK:CALLER]PreFFRecordIndex *//* [GUD:CFG]posLastEventStrgIndexLower  */

    return;
}

/****************************************************************************/
/* Function Name | Dem_PreFFDMng_DivideEventStrgIndexToUpperAndLower            */
/* Description   | Divides the specified EventStrgIndex to upper-byte and lowe- */
/*               | r-byte.                                                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                        */
/*               |        The index for Dem_EventRecordList.                */
/*               | [out] EventStrgIndexUpperPtr :                               */
/*               |        Upper-byte of the specified EventStrgIndex.           */
/*               | [out] EventStrgIndexLowerPtr :                               */
/*               |        Lower-byte of the specified EventStrgIndex.           */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_PreFFDMng_DivideEventStrgIndexToUpperAndLower
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) EventStrgIndexUpperPtr,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) EventStrgIndexLowerPtr
)
{
    (*EventStrgIndexUpperPtr) = (uint8)( EventStrgIndex >> DEM_PFM_EVENTSTRGINDEX_SHIFT );
    (*EventStrgIndexLowerPtr) = (uint8)( EventStrgIndex & DEM_PFM_EVENTSTRGINDEX_MASK );

    return;
}

/****************************************************************************/
/* Function Name | Dem_PreFFDMng_GetEventStrgIndexFromPreFFRecord           */
/* Description   | Get an event index froom Dem_PrestoreFreezeFrameRecordL- */
/*               | ist[] corresponding to the specified PreFFRecordIndex.   */
/* Preconditions | none                                                     */
/* Parameters    | [in] PreFFRecordIndex :                                  */
/*               |        The index for Dem_PrestoreFreezeFrameRecordList.  */
/* Return Value  | Dem_u16_EventStrgIndexType :                                 */
/*               |       EventStrgIndex                                         */
/* Notes         | The specified PreFFRecordIndex guarantees the range.     */
/*               | May be called within the exclusive section "PrestoreFre- */
/*               | ezeFrame".                                               */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u16_EventStrgIndexType, DEM_CODE ) Dem_PreFFDMng_GetEventStrgIndexFromPreFFRecord
(
    VAR( Dem_u08_PreFFDIndexType, AUTOMATIC ) PreFFRecordIndex          /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posEventStrgIndexUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posEventStrgIndexLower;

    posEventStrgIndexUpper = Dem_PreFreezeFrameDataPosTable.FirstEventStrgIndexUpper;   /* [GUD:CFG]posFirstEventStrgIndexUpper */
    posEventStrgIndexLower = Dem_PreFreezeFrameDataPosTable.FirstEventStrgIndexLower;   /* [GUD:CFG]posFirstEventStrgIndexLower */

    eventStrgIndex = (Dem_u16_EventStrgIndexType)( (Dem_u16_EventStrgIndexType)Dem_PrestoreFreezeFrameRecordList[PreFFRecordIndex].Data[posEventStrgIndexUpper] << DEM_PFM_EVENTSTRGINDEX_SHIFT );  /* [GUDCHK:CALLER]PreFFRecordIndex *//* [GUD:CFG]posFirstEventStrgIndexUpper */
    eventStrgIndex |= (Dem_u16_EventStrgIndexType)Dem_PrestoreFreezeFrameRecordList[PreFFRecordIndex].Data[posEventStrgIndexLower]; /* [GUDCHK:CALLER]PreFFRecordIndex *//* [GUD:CFG]posFirstEventStrgIndexLower */

    return eventStrgIndex;
}


/****************************************************************************/
/* Function Name | Dem_PreFFDMng_CheckEventAvailable                        */
/* Description   | Check EventStrgIndex available                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                        */
/*               |        The EventStrgIndex                                    */
/* Return Value  | Dem_u08_InternalReturnType :                             */
/*               |       DEM_IRT_OK  : The event is enable.                 */
/*               |       DEM_IRT_NG  : The event is not enable.             */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PreFFDMng_CheckEventAvailable
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( boolean, AUTOMATIC ) availableStatus;
    VAR( boolean, AUTOMATIC ) ffPrestorageSupported;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;
    retVal = DEM_IRT_NG;

    if( EventStrgIndex < eventStorageNum )                                                                  /* [GUD:if]EventStrgIndex */
    {
        availableStatus = Dem_DataAvl_GetEvtAvl_InEvtStrgGrp( EventStrgIndex );
        if( availableStatus == (boolean)TRUE )
        {
            ffPrestorageSupported = Dem_CfgInfoPm_GetPreFFSupported_InEvtStrgGrp( EventStrgIndex );
            if( ffPrestorageSupported == (boolean)TRUE )
            {
                retVal = DEM_IRT_OK;
            }
        }
    }

    return retVal;
}

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_PreFFDMng_GetEventIdFromRecordData                   */
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
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PreFFDMng_GetEventIdFromRecordData
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u08_PreFFDIndexType, AUTOMATIC ) preFFRecordIndex;

    retVal  =   DEM_IRT_NG;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    preFFRecordIndex    =   ( Dem_u08_PreFFDIndexType )RecordIndex;

    /*------------------------------*/
    /*  enter exclusive area        */
    SchM_Enter_Dem_PrestoreFreezeFrame();
    {
        eventStrgIndex      =   Dem_PreFFDMng_GetEventStrgIndexFromPreFFRecord( preFFRecordIndex );
    }
    SchM_Exit_Dem_PrestoreFreezeFrame();
    /*  exit exclusive area         */
    /*------------------------------*/

    if ( eventStrgIndex < eventStorageNum )                                                                 /* [GUD:if]eventStrgIndex */
    {
        retVal  =   Dem_CfgInfoPm_CnvEventStrgIndexToEventId( eventStrgIndex, EventIdPtr );
    }

    return retVal;
}
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-8-0         :2024-10-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
