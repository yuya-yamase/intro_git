/* Dem_UdmFFDMng_c(v5-7-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UdmFFDMng/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../cfg/Dem_UserDefMem_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Rc_RecMngCmn.h"
#include "../../../inc/Dem_Rc_RecMngCmn_Table.h"
#include "../../../inc/Dem_Rc_UdmMng.h"
#include "../../../inc/Dem_Utl.h"
#include "../../../inc/Dem_Rc_UdmMng_rc.h"
#include "../../../inc/Dem_Rc_UdmMngTable.h"
#include "../../../inc/Dem_Rc_UdmFFRecordTable.h"
#include "../../../inc/Dem_Rc_UdmFaultRecordTable.h"
#include "Dem_UdmFreezeFrame.h"
#include "Dem_UdmMng_local.h"
#include "Dem_UdmMng_GetRecordData.h"

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )

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

static FUNC( void, DEM_CODE ) Dem_UdmFFDMng_ClearRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) UdmFreezeFrameIndex
);

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
static FUNC( void, DEM_CODE ) Dem_UdmFFDMng_InitMirrorMemory
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex
);
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */
static FUNC( void, DEM_CODE ) Dem_UdmFFDMng_CheckConsistencyOneRecordData
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) UdmStartFreezeFrameIndex,
    P2VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC, AUTOMATIC ) UdmFreezeFrameStoredCntPtr,
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) LatestCidForOtherRecordPtr
);
static FUNC( void, DEM_CODE ) Dem_UdmFFDMng_CheckConsistencyWithOtherFFDRecord
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) UdmStartFreezeFrameIndex,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) LatestCidForOtherRecord
);
static FUNC( void, DEM_CODE ) Dem_UdmFFDMng_GetFFDConsistencyInfo
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) UdmFreezeFrameIndex,
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) FirstBlockCIdPtr,
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) LastBlockCIdPtr,
    P2VAR( Dem_u16_UdmEventIndexType, AUTOMATIC, AUTOMATIC ) FirstBlockUdmEventIndexPtr,
    P2VAR( Dem_u16_UdmEventIndexType, AUTOMATIC, AUTOMATIC ) LastBlockUdmEventIndexPtr
);
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFFDMng_CheckConsistency
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) UdmFreezeFrameIndex
);
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFFDMng_VerifyChecksum
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) UdmFreezeFrameIndex
);

#if ( DEM_FF_CHECKSUM_SUPPORT == STD_ON )
static FUNC( Dem_u16_FFCheckSumType, DEM_CODE ) Dem_UdmFFDMng_GetChecksum
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) UdmFreezeFrameIndex
);
#endif /* ( DEM_FF_CHECKSUM_SUPPORT == STD_ON ) */

static FUNC_P2VAR( uint8, DEM_VAR_SAVED_ZONE, DEM_CODE ) Dem_UdmFFDMng_GetFreezeFrameRecordDataPtr
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) UdmFreezeFrameIndex
);

static FUNC( void, DEM_CODE ) Dem_UdmFFDMng_GetOlderFreezeFrameInfo
(
    VAR( Dem_u32_UdmOccurrenceOrderType, AUTOMATIC ) TargetOccurrenceOrder,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) TargetFreezeFrameRecordIndex,
    P2VAR( Dem_UdmNextFreezeFrameType, AUTOMATIC, AUTOMATIC ) OldestUdmNextFreezeFrameInfoPtr
);

static FUNC( void, DEM_CODE ) Dem_UdmFFDMng_GetNewerFreezeFrameInfo
(
    VAR( Dem_u32_UdmOccurrenceOrderType, AUTOMATIC ) TargetOccurrenceOrder,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) TargetCidUdmFreezeFrameRecords,
    P2VAR( Dem_UdmNextFreezeFrameType, AUTOMATIC, AUTOMATIC ) NewestUdmNextFreezeFrameInfoPtr
);

static FUNC( Dem_u08_NumOfTSFFType, DEM_CODE ) Dem_UdmFFDMng_GetCheckedOffsetOfTSFFListIndex
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) OffsetOfTSFFListIndex
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

VAR( Dem_UdmFreezeFrameRecordMngType, DEM_VAR_NO_INIT ) Dem_TmpVerifyUdmFreezeFrameRecord[DEM_UDM_MAX_NUMBER_FF_PER_DTC];

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>


/****************************************************************************/
/* Function Name | Dem_UdmFFDMng_GetFFDRecordNum                            */
/* Description   | Gets number of freeze frame records from the udm FFD re- */
/*               | cordlist corresponding to the specified memory kind ind- */
/*               | ex.(for UdmDem_DataCtl subunit)                          */
/* Preconditions | The specified UdmGroupKindIndex shall be within the      */
/*               | range of the Dem_UserDefinedMemoryTable[].               */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/* Return Value  | Dem_u16_UdmFFDIndexType                                  */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u16_UdmFFDIndexType, DEM_CODE ) Dem_UdmFFDMng_GetFFDRecordNum
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex
)
{
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) udmFFDRecordNum;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;

    udmFFDRecordNum =   (Dem_u16_UdmFFDIndexType)0U;
    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;
    if( UdmGroupKindIndex < userDefinedMemoryNum )                                              /* [GUD:if]UdmGroupKindIndex */
    {
        udmFFDRecordNum = Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDRecordNum;     /* [GUD]UdmGroupKindIndex */
    }
    return udmFFDRecordNum;
}


/****************************************************************************/
/* Function Name | Dem_UdmFFDMngC_InitFreezeFrameRecordData                 */
/* Description   | Initializes the specified freeze frame record.           */
/* Preconditions |                                                          */
/* Parameters    | [out] FreezeFrameRecordPtr :                             */
/*               |        The specified freeze frame record to initialize.  */
/*               |         &Dem_TmpEventMemoryEntry.FreezeFrameRecordList[] */
/*               |         AUTOMATIC                                        */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmFFDMngC_InitFreezeFrameRecordData
(
    P2VAR( Dem_UdmFreezeFrameRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) FreezeFrameRecordPtr
)
{
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) ffdMaxLength;

    /* Sets initial value to the specified freeze frame record. */

    /* The fault index */
    FreezeFrameRecordPtr->UdmEventIndex = DEM_UDMEVENTINDEX_INVALID;

    /* The occurrence order */
    FreezeFrameRecordPtr->OccurrenceOrder = DEM_UDMOCCURRENCEORDER_INITIAL;

    /* The occurrence order */
    FreezeFrameRecordPtr->CidUdmFreezeFrameRecords = DEM_CONSISTENCY_INITIAL;

    /* Offset of the time-series freeze frame list record's index */
    FreezeFrameRecordPtr->OffsetOfTSFFListIndex = DEM_NUMOFTSFF_INVALID;

    /* The record status */
    FreezeFrameRecordPtr->RecordStatus = DEM_FFD_NOT_STORED;

    /* The data for freeze frame. */
    ffdMaxLength = Dem_UdmFFDMaxLength;
    Dem_UtlMem_SetMemory( &FreezeFrameRecordPtr->Data[0], DEM_FFD_INITIAL, ffdMaxLength );/* [ARYCHK] DEM_UDMFFD_MAX_LENGTH / 1 / 0 */

    return ;
}

/****************************************************************************/
/* Function Name | Dem_UdmFFDMng_InitRecord                                 */
/* Description   | Initialize udm freeze frame data area.                   */
/*               |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmGroupKindIndex                                   */
/*               |        Index of user defined memory table                */
/*               | [in] UdmFreezeFrameIndex :                               */
/*               |        The UdmFreezeFrame index corresponding to the sp- */
/*               |        ecific UdmFreezeFrame record.                     */
/* Return Value  | void                                                     */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmFFDMng_InitRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) UdmFreezeFrameIndex
)
{
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) udmFFDRecordNum;

    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;

    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;
    if( UdmGroupKindIndex < userDefinedMemoryNum )                                              /* [GUD:if]UdmGroupKindIndex */
    {
        udmFFDRecordNum = Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDRecordNum;     /* [GUD]UdmGroupKindIndex */

        /* Checks the range of the specified index.*/
        if( UdmFreezeFrameIndex < udmFFDRecordNum )
        {
            /* Sets the initial value to the fault index and the record status of the specified freeze frame record. */
            Dem_UdmFFDMng_ClearRecord( UdmGroupKindIndex, UdmFreezeFrameIndex );
        }
        else
        {
            /* No process */
        }
    }
    return;
}

/****************************************************************************/
/* Function Name | Dem_UdmFFDMng_ClearStoredRecord                          */
/* Description   | Initializes the udm fault index and the record status of */
/*               |  the specified record of udm freeze frame record list.   */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmGroupKindIndex                                   */
/*               |        Index of user defined memory table                */
/*               | [in] UdmFreezeFrameIndex :                               */
/*               |        The UdmFreezeFrame index corresponding to the sp- */
/*               |        ecific UdmFreezeFrame record.                     */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFFDMng_ClearStoredRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) UdmFreezeFrameIndex
)
{
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) freezeFrameRecordDataPtr;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_FFStoredStatusType, AUTOMATIC ) recordStatus;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posRecordStatus;

    retVal = DEM_IRT_NG;

    freezeFrameRecordDataPtr = Dem_UdmFFDMng_GetFreezeFrameRecordDataPtr( UdmGroupKindIndex, UdmFreezeFrameIndex ); /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/UdmFreezeFrameIndex/freezeFrameRecordDataPtr */
    if( freezeFrameRecordDataPtr != NULL_PTR )                                              /* [GUD:if]freezeFrameRecordDataPtr */
    {
        posRecordStatus = Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex].RecordStatus;   /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posRecordStatus */

        /*  check available data of Dem_UdmFreezeFrameDataPosTable[]    */
        if ( posRecordStatus != DEM_FFDSTOREDINDEX_INVALID )
        {
            recordStatus = freezeFrameRecordDataPtr[posRecordStatus];                       /* [GUD]freezeFrameRecordDataPtr *//* [GUD]posRecordStatus *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posRecordStatus */
            if( recordStatus == DEM_FFD_STORED )
            {
                retVal = DEM_IRT_OK;
            }
        }
        Dem_UdmFFDMng_ClearRecord( UdmGroupKindIndex, UdmFreezeFrameIndex );                /* [GUD]UdmGroupKindIndex */

    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_UdmFFDMng_ClearRecord                                */
/* Description   | Initializes the udm fault index and the record status of */
/*               |  the specified record of udm freeze frame record list.   */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmGroupKindIndex                                   */
/*               |        Index of user defined memory table                */
/*               | [in] UdmFreezeFrameIndex :                               */
/*               |        The UdmFreezeFrame index corresponding to the sp- */
/*               |        ecific UdmFreezeFrame record.                     */
/*               |                                                          */
/* Return Value  | -                                                        */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmFFDMng_ClearRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) UdmFreezeFrameIndex
)
{
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) freezeFrameRecordDataPtr;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstUdmEventIndexUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstUdmEventIndexLower;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posLastUdmEventIndexUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posLastUdmEventIndexLower;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posOffsetOfTSFFListIndex;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posRecordStatus;
    VAR( uint8, AUTOMATIC ) udmEventIndexUpper;
    VAR( uint8, AUTOMATIC ) udmEventIndexLower;

    freezeFrameRecordDataPtr = Dem_UdmFFDMng_GetFreezeFrameRecordDataPtr( UdmGroupKindIndex, UdmFreezeFrameIndex ); /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/UdmFreezeFrameIndex/freezeFrameRecordDataPtr */
    if ( freezeFrameRecordDataPtr != NULL_PTR )                                             /* [GUD:if]freezeFrameRecordDataPtr */
    {
        posFirstUdmEventIndexUpper = Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex].FirstUdmEventIndexUpper;     /* [GUD]udmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:udmGroupKindIndex]posFirstUdmEventIndexUpper */
        posFirstUdmEventIndexLower = Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex].FirstUdmEventIndexLower;     /* [GUD]udmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:udmGroupKindIndex]posFirstUdmEventIndexLower */
        posLastUdmEventIndexUpper = Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex].LastUdmEventIndexUpper;       /* [GUD]udmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:udmGroupKindIndex]posLastUdmEventIndexUpper  */
        posLastUdmEventIndexLower = Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex].LastUdmEventIndexLower;       /* [GUD]udmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:udmGroupKindIndex]posLastUdmEventIndexLower  */
        posOffsetOfTSFFListIndex = Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex].OffsetOfTSFFListIndex;         /* [GUD]udmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:udmGroupKindIndex]posOffsetOfTSFFListIndex */
        posRecordStatus = Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex].RecordStatus;                           /* [GUD]udmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:udmGroupKindIndex]posRecordStatus */

        /*  check available data of Dem_UdmFreezeFrameDataPosTable[]    */
        if ( posRecordStatus != DEM_FFDSTOREDINDEX_INVALID )
        {
            /* Sets the initial value to the event index of the specified freeze frame record. */
            Dem_UtlMem_SplitByteData( (uint16)DEM_UDMEVENTINDEX_INVALID, &udmEventIndexUpper, &udmEventIndexLower );
            freezeFrameRecordDataPtr[posFirstUdmEventIndexUpper] = udmEventIndexUpper;              /* [GUD]freezeFrameRecordDataPtr *//* [GUD]posFirstUdmEventIndexUpper *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posFirstUdmEventIndexUpper */
            freezeFrameRecordDataPtr[posFirstUdmEventIndexLower] = udmEventIndexLower;              /* [GUD]freezeFrameRecordDataPtr *//* [GUD]posFirstUdmEventIndexLower *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posFirstUdmEventIndexLower */
            freezeFrameRecordDataPtr[posLastUdmEventIndexUpper] = udmEventIndexUpper;               /* [GUD]freezeFrameRecordDataPtr *//* [GUD]posLastUdmEventIndexUpper  *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posLastUdmEventIndexUpper */
            freezeFrameRecordDataPtr[posLastUdmEventIndexLower] = udmEventIndexLower;               /* [GUD]freezeFrameRecordDataPtr *//* [GUD]posLastUdmEventIndexLower  *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posLastUdmEventIndexLower */

            /* Sets initial value to the offset of time-series freeze frame list record's index of the specified freeze frame record. */
            freezeFrameRecordDataPtr[posOffsetOfTSFFListIndex] = (uint8)DEM_NUMOFTSFF_INVALID;      /* [GUD]freezeFrameRecordDataPtr *//* [GUD]posOffsetOfTSFFListIndex *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posOffsetOfTSFFListIndex */

            /* Sets "not stored" to the record status of the specified freeze frame record. */
            freezeFrameRecordDataPtr[posRecordStatus] = (uint8)DEM_FFD_NOT_STORED;                  /* [GUD]freezeFrameRecordDataPtr *//* [GUD]posRecordStatus *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posRecordStatus */
        }
        /* Remains occurrence order and cid for udm freeze frame records */
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dem_UdmFFDMng_Init                                       */
/* Description   | Init process of Udm FFD.                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmFFDMng_Init
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
)
{
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) udmFreezeFrameIndex;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) udmFFDRecordNum;

    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;
    udmGroupKindIndex    = ( Dem_u16_UdmDemMemKindIndexType )RecordFieldIndex;

    if( udmGroupKindIndex < userDefinedMemoryNum )                              /* [GUD;if]udmGroupKindIndex */
    {
        udmFFDRecordNum = Dem_UdmFreezeFrameRecordTable[udmGroupKindIndex].DemFFDRecordNum;                                             /* [GUD]udmGroupKindIndex */
        for( udmFreezeFrameIndex = (Dem_u16_UdmFFDIndexType)0U; udmFreezeFrameIndex < udmFFDRecordNum; udmFreezeFrameIndex++ )          /* [GUD:for]udmFreezeFrameIndex */
        {
            Dem_UdmFFDNvMStatus[ udmGroupKindIndex ].DemUdmFFDNvMStatusPtr[ udmFreezeFrameIndex ] = DEM_RECMNGCMN_NVM_STS_NOT_VERIFIED; /* [GUD]udmGroupKindIndex *//* [GUD]udmFreezeFrameIndex *//* [ARYCHK] udmFFDRecordNum / 1 / udmFreezeFrameIndex *//* [ARYDESC] The registered data size of Dem_UdmFFDNvMStatus[ udmGroupKindIndex ].DemUdmFFDNvMStatusPtr is the same as Dem_UdmFreezeFrameRecordTable[udmGroupKindIndex].DemFFDRecordNum */
        }
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    /* [FuncSw] */
        Dem_UdmFFDMng_InitMirrorMemory( udmGroupKindIndex );                    /* [GUD]udmGroupKindIndex */
#endif  /*   ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )  */
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_UdmFFDMng_InitSavedZone                              */
/* Description   | Initialize savedzone process of udm FFD.                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/*               | [in] InitType :                                          */
/*               |          Initialize savedzone type                       */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmFFDMng_InitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType      /* MISRA DEVIATION */
)
{
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) freezeFrameRecordDataPtr;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) udmFreezeFrameIndex;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) udmFFDRecordNum;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) udmFfdStorageFormatsize;

    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;
    udmGroupKindIndex    = ( Dem_u16_UdmDemMemKindIndexType )RecordFieldIndex;

    if( udmGroupKindIndex < userDefinedMemoryNum )  /* [GUD:if]udmGroupKindIndex */
    {
        udmFFDRecordNum = Dem_UdmFreezeFrameRecordTable[udmGroupKindIndex].DemFFDRecordNum;                                     /* [GUD]udmGroupKindIndex */
        udmFfdStorageFormatsize = Dem_UdmFreezeFrameRecordTable[udmGroupKindIndex].DemFFDStoredFormatSize;                      /* [GUD]udmGroupKindIndex */

        for( udmFreezeFrameIndex = (Dem_u16_UdmFFDIndexType)0U; udmFreezeFrameIndex < udmFFDRecordNum; udmFreezeFrameIndex++ )  /* [GUD:for]udmFreezeFrameIndex */
        {
            freezeFrameRecordDataPtr = Dem_UdmFFDMng_GetFreezeFrameRecordDataPtr( udmGroupKindIndex, udmFreezeFrameIndex ); /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/UdmFreezeFrameIndex/freezeFrameRecordDataPtr */
            if( freezeFrameRecordDataPtr != NULL_PTR )                                                                      /* [GUD:if]freezeFrameRecordDataPtr */
            {
                Dem_UtlMem_SetMemory( &freezeFrameRecordDataPtr[0], DEM_FFD_INITIAL, udmFfdStorageFormatsize );             /* [GUD]freezeFrameRecordDataPtr *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[udmGroupKindIndex].DemFFDStoredFormatSize / 1 / 0 */
            }

        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_UdmFFDMng_DataVerify                                 */
/* Description   | Verifies Udm FFD data.                                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |          DEM_IRT_OK      : DataVerify completed.         */
/*               |          DEM_IRT_PENDING : Continue DataVerify.          */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFFDMng_DataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex     /* MISRA DEVIATION */
)
{
    /* No Process */
    return DEM_IRT_OK;
}

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_UdmFFDMng_SetRecordMirror                            */
/* Description   | Set to the Mirror Memory.                                */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/*               | [in/out] BlockMirrorPtr :                                */
/*               |        Nonvolatile synchronous data information.         */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmFFDMng_SetRecordMirror
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
)
{
    P2CONST( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) freezeFrameRecordDataPtr;
    P2VAR( uint8, AUTOMATIC, DEM_VAR_NO_INIT ) tmpUdmFFDMirrorDataPtr;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) udmFfdStorageFormatsize;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) udmFfdDataIndex;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) udmFFDRecordNum;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;


    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;
    udmGroupKindIndex    = ( Dem_u16_UdmDemMemKindIndexType )RecordFieldIndex;

    if( udmGroupKindIndex < userDefinedMemoryNum )  /* [GUD:if]udmGroupKindIndex */
    {
        udmFFDRecordNum = Dem_UdmFreezeFrameRecordTable[udmGroupKindIndex].DemFFDRecordNum; /* [GUD]udmGroupKindIndex */
        udmFfdStorageFormatsize = Dem_UdmFreezeFrameRecordTable[ udmGroupKindIndex ].DemFFDStoredFormatSize;    /* [GUD]udmGroupKindIndex */

        if( BlockMirrorPtr->RecordDataOffset == (Dem_u16_RecordDataSizeType)0U )
        {
            if( BlockMirrorPtr->RecordIndex < udmFFDRecordNum ) /* [GUD:if]BlockMirrorPtr->RecordIndex */
            {
                tmpUdmFFDMirrorDataPtr = Dem_UdmFreezeFrameRecordNvMTable[udmGroupKindIndex].DemTmpUdmFFDMirrorDataPtr; /* [GUD]udmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:udmGroupKindIndex]tmpUdmFFDMirrorDataPtr */
                freezeFrameRecordDataPtr = ( P2CONST( uint8, TYPEDEF, DEM_VAR_SAVED_ZONE ) )Dem_UdmFFDMng_GetFreezeFrameRecordDataPtr( udmGroupKindIndex, BlockMirrorPtr->RecordIndex );

                if ( freezeFrameRecordDataPtr != NULL_PTR )     /* [GUD:if]freezeFrameRecordDataPtr */
                {
                    /* copy data to mirror area. */
                    Dem_UtlMem_CopyMemory( &tmpUdmFFDMirrorDataPtr[0], &(freezeFrameRecordDataPtr[0]), udmFfdStorageFormatsize );   /* [GUD]tmpUdmFFDMirrorDataPtr *//* [GUD]freezeFrameRecordDataPtr *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[udmGroupKindIndex].DemFFDStoredFormatSize / 1 / 0 *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[udmGroupKindIndex].DemFFDStoredFormatSize / 1 / 0 *//* [ARYDESC] The registered data size of Dem_UdmFreezeFrameRecordNvMTable[udmGroupKindIndex].DemTmpUdmFFDMirrorDataPtr is the same as Dem_UdmFreezeFrameRecordTable[udmGroupKindIndex].DemFFDStoredFormatSize */
                }
            }
        }

        udmFfdDataIndex = Dem_UdmFreezeFrameRecordNvMTable[udmGroupKindIndex].DemUdmFFDRecordNvBlockSize * BlockMirrorPtr->RecordDataOffset;    /* [GUD]udmGroupKindIndex */
        if( udmFfdDataIndex < udmFfdStorageFormatsize )
        {
            BlockMirrorPtr->MirrorPtr = &(Dem_UdmFreezeFrameRecordNvMTable[udmGroupKindIndex].DemTmpUdmFFDMirrorDataPtr[ udmFfdDataIndex ]);    /* [GUD]udmGroupKindIndex */    /* [GUD]udmFfdDataIndex *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[udmGroupKindIndex].DemFFDStoredFormatSize / 1 / udmFfdDataIndex *//* [ARYDESC] The registered data size of Dem_UdmFreezeFrameRecordNvMTable[udmGroupKindIndex].DemTmpUdmFFDMirrorDataPtr is the same as Dem_UdmFreezeFrameRecordTable[udmGroupKindIndex].DemFFDStoredFormatSize */
        }
    }

    return;
}

#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

/****************************************************************************/
/* Function Name | Dem_UdmFFDMng_Verified                                   */
/* Description   | Make Udm  FFD verified.                                  */
/* Preconditions | [in] UdmEventIndex : Udm Event index.                    */
/*               | [in] UdmFaultIndex : Udm Fault index.                    */
/*               | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmFFDMng_Verified
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex,
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex
)
{
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) udmStartFreezeFrameIndex;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) udmFreezeFrameStoredCnt;
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) latestCidForOtherRecord;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindUdmFault;

    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;

    if( UdmGroupKindIndex < userDefinedMemoryNum )                                          /* [GUD:if]UdmGroupKindIndex */
    {
        Dem_UdmFaultMngM_GetFreezeFrameIndex( UdmGroupKindIndex, UdmFaultIndex, &udmStartFreezeFrameIndex );        /* [GUD]UdmGroupKindIndex */

        if( udmStartFreezeFrameIndex != DEM_UDMFFRECINDEX_INITIAL )
        {
            udmFreezeFrameStoredCnt = (Dem_u16_UdmFFDIndexType)0U;
            Dem_UdmFFDMng_CheckConsistencyOneRecordData( UdmEventIndex, UdmGroupKindIndex, udmStartFreezeFrameIndex, &udmFreezeFrameStoredCnt, &latestCidForOtherRecord );  /* [GUD]UdmGroupKindIndex */

            if( udmFreezeFrameStoredCnt > (Dem_u16_UdmFFDIndexType)0U )
            {
                Dem_UdmFFDMng_CheckConsistencyWithOtherFFDRecord( UdmEventIndex, UdmGroupKindIndex, udmStartFreezeFrameIndex, latestCidForOtherRecord );                    /* [GUD]UdmGroupKindIndex */
            }
            else
            {
                Dem_UdmFaultMng_InitSpecificRecordNumberIndex( UdmGroupKindIndex, UdmFaultIndex );                      /* [GUD]UdmGroupKindIndex */
                recMngCmnKindUdmFault = Dem_UdmFaultNvMStatus[ UdmGroupKindIndex ].DemRecMngCmnKindUdmFault;            /* [GUD]UdmGroupKindIndex */
                Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindUdmFault, ( Dem_u16_RecordIndexType )UdmFaultIndex );
            }
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_UdmFFDMng_CheckConsistencyOneRecordData              */
/* Description   | verify One Udm FFD record.                               */
/* Preconditions | [in] UdmEventIndex : Udm Event index.                    */
/*               | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/*               | [in] UdmStartFreezeFrameIndex :                          */
/*               |        Udm Start freeze frame index                      */
/*               | [out] UdmFreezeFrameStoredCntPtr :                       */
/*               |        number of Udm Freeze Frame                        */
/*               | [out] LatestCidForOtherRecordPtr :                       */
/*               |        consistency id with other record                  */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmFFDMng_CheckConsistencyOneRecordData
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,                 /* [PRMCHK:CALLER] */
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) UdmStartFreezeFrameIndex,
    P2VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC, AUTOMATIC ) UdmFreezeFrameStoredCntPtr,
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) LatestCidForOtherRecordPtr
)
{
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) maxNumberUdmFreezeFrame;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) udmFFDRecordNum;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) udmFreezeFrameCnt;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) udmFreezeFrameIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFFRec;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVerifyRecord;
    VAR( Dem_u32_UdmOccurrenceOrderType, AUTOMATIC ) occurrenceOrder;
    VAR( Dem_u32_UdmOccurrenceOrderType, AUTOMATIC ) minOccurrenceOrder;
    VAR( Dem_u32_UdmOccurrenceOrderType, AUTOMATIC ) minOccurrenceOrderMSBInvert;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) latestUdmFreezeFrameCnt;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) latestUdmFreezeFrameCntMSBInvert;
    VAR( boolean, AUTOMATIC ) existZeroValueOfOccurrenceOrder;

    maxNumberUdmFreezeFrame = Dem_CfgInfoUdm_GetMaxNumberFreezeFrameRecords( UdmEventIndex );
    udmFFDRecordNum = Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDRecordNum;         /* [GUDCHK:CALLER]UdmGroupKindIndex */

    *UdmFreezeFrameStoredCntPtr = (Dem_u16_UdmFFDIndexType)0U;

    minOccurrenceOrder = DEM_UDMOCCURRENCEORDER_INITIAL;
    minOccurrenceOrderMSBInvert = DEM_UDMOCCURRENCEORDER_INITIAL;
    existZeroValueOfOccurrenceOrder = (boolean)FALSE;
    latestUdmFreezeFrameCnt = (Dem_u16_UdmFFDIndexType)0U;
    latestUdmFreezeFrameCntMSBInvert = (Dem_u16_UdmFFDIndexType)0U;

    for( udmFreezeFrameCnt = (Dem_u16_UdmFFDIndexType)0U; udmFreezeFrameCnt < maxNumberUdmFreezeFrame; udmFreezeFrameCnt++ )        /* [GUD:for]udmFreezeFrameCnt */
    {
        udmFreezeFrameIndex = UdmStartFreezeFrameIndex + udmFreezeFrameCnt;
        if( udmFreezeFrameIndex < udmFFDRecordNum )                                                                                 /* [GUD:if]udmFreezeFrameIndex */
        {
            resultOfGetFFRec = Dem_UdmFFDMng_GetFreezeFrameRecord( UdmGroupKindIndex, udmFreezeFrameIndex, &Dem_TmpVerifyUdmFreezeFrameRecord[udmFreezeFrameCnt] );     /* [GUDCHK:CALLER]UdmGroupKindIndex */
            if( resultOfGetFFRec == DEM_IRT_OK )
            {
                if( Dem_TmpVerifyUdmFreezeFrameRecord[udmFreezeFrameCnt].RecordStatus == DEM_FFD_STORED  )                          /* [GUD]udmFreezeFrameCnt */
                {
                    retVerifyRecord = Dem_UdmFFDMng_CheckConsistency( UdmGroupKindIndex, UdmEventIndex, udmFreezeFrameIndex );      /* [GUDCHK:CALLER]UdmGroupKindIndex */

                    if( retVerifyRecord == DEM_IRT_OK )
                    {
                        *UdmFreezeFrameStoredCntPtr = *UdmFreezeFrameStoredCntPtr + (Dem_u16_UdmFFDIndexType)1U;
                        occurrenceOrder = Dem_TmpVerifyUdmFreezeFrameRecord[udmFreezeFrameCnt].OccurrenceOrder;                     /* [GUD]udmFreezeFrameCnt */

                        if( occurrenceOrder <= minOccurrenceOrder )
                        {
                            minOccurrenceOrder = occurrenceOrder;
                            latestUdmFreezeFrameCnt = udmFreezeFrameCnt;                                                            /* [GUD]latestUdmFreezeFrameCnt( == udmFreezeFrameCnt) */
                        }

                        if( occurrenceOrder == (Dem_u32_UdmOccurrenceOrderType)0U )
                        {
                            existZeroValueOfOccurrenceOrder = (boolean)TRUE;
                        }

                        occurrenceOrder = occurrenceOrder ^ DEM_UDM_OCCURRENCEORDER_MSB;
                        if( occurrenceOrder <= minOccurrenceOrderMSBInvert )
                        {
                            minOccurrenceOrderMSBInvert = occurrenceOrder;
                            latestUdmFreezeFrameCntMSBInvert = udmFreezeFrameCnt;                                                   /* [GUD]latestUdmFreezeFrameCntMSBInvert( == udmFreezeFrameCnt) */
                        }
                    }
                    else
                    {
                        Dem_TmpVerifyUdmFreezeFrameRecord[udmFreezeFrameCnt].RecordStatus = DEM_FFD_NOT_STORED;                     /* [GUD]udmFreezeFrameCnt */
                    }
                }
            }
        }
    }

    if( *UdmFreezeFrameStoredCntPtr > (Dem_u16_UdmFFDIndexType)0U )
    {
        if( existZeroValueOfOccurrenceOrder == (boolean)FALSE )
        {
            *LatestCidForOtherRecordPtr = Dem_TmpVerifyUdmFreezeFrameRecord[latestUdmFreezeFrameCnt].CidUdmFreezeFrameRecords;          /* [GUD]latestUdmFreezeFrameCnt */
        }
        else
        {
            *LatestCidForOtherRecordPtr = Dem_TmpVerifyUdmFreezeFrameRecord[latestUdmFreezeFrameCntMSBInvert].CidUdmFreezeFrameRecords; /* [GUD]latestUdmFreezeFrameCntMSBInvert */
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_UdmFFDMng_CheckConsistencyWithOtherFFDRecord         */
/* Description   | verify consistency with other Udm FFD record.            */
/* Preconditions | [in] UdmFaultIndex : Udm Fault index.                    */
/*               | [in] UdmFaultRecordPtr : Udm Fault record.               */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmFFDMng_CheckConsistencyWithOtherFFDRecord
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,     /* [PRMCHK:CALLER] */
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) UdmStartFreezeFrameIndex,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) LatestCidForOtherRecord
)
{
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) maxNumberUdmFreezeFrame;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) udmFFDRecordNum;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) udmFreezeFrameCnt;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) udmFreezeFrameIndex;

    maxNumberUdmFreezeFrame = Dem_CfgInfoUdm_GetMaxNumberFreezeFrameRecords( UdmEventIndex );
    udmFFDRecordNum = Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDRecordNum;             /* [GUDCHK:CALLER]UdmGroupKindIndex */

    for( udmFreezeFrameCnt = (Dem_u16_UdmFFDIndexType)0U; udmFreezeFrameCnt < maxNumberUdmFreezeFrame; udmFreezeFrameCnt++ )    /* [GUD:for]udmFreezeFrameCnt */
    {
        udmFreezeFrameIndex = UdmStartFreezeFrameIndex + udmFreezeFrameCnt;
        if( udmFreezeFrameIndex < udmFFDRecordNum )                                                                             /* [GUD:if]udmFreezeFrameIndex */
        {
            if( Dem_TmpVerifyUdmFreezeFrameRecord[udmFreezeFrameCnt].RecordStatus == DEM_FFD_STORED )                           /* [GUD]udmFreezeFrameCnt */
            {
                if( LatestCidForOtherRecord == Dem_TmpVerifyUdmFreezeFrameRecord[udmFreezeFrameCnt].CidUdmFreezeFrameRecords )  /* [GUD]udmFreezeFrameCnt */
                {
                    Dem_UdmFFDNvMStatus[ UdmGroupKindIndex ].DemUdmFFDNvMStatusPtr[ udmFreezeFrameIndex ] = DEM_RECMNGCMN_NVM_STS_NON_TARGET;   /* [GUDCHK:CALLER]UdmGroupKindIndex *//* [GUD:if]udmFreezeFrameIndex *//* [ARYCHK] udmFFDRecordNum / 1 / udmFreezeFrameIndex *//* [ARYDESC] The registered data size of Dem_UdmFFDNvMStatus[ udmGroupKindIndex ].DemUdmFFDNvMStatusPtr is the same as Dem_UdmFreezeFrameRecordTable[udmGroupKindIndex].DemFFDRecordNum */
                }
                else
                {
                    Dem_TmpVerifyUdmFreezeFrameRecord[udmFreezeFrameCnt].RecordStatus = DEM_FFD_NOT_STORED;                     /* [GUD]udmFreezeFrameCnt */
                }
            }
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_UdmFFDMng_ClearAllNotVerifiedRecord                  */
/* Description   | Clear not verrified record.                              */
/* Preconditions |                                                          */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/*               | [in/out] ClearRecordIndexPtr :                           */
/*               |          target record index                             */
/*               | [in/out] RestOfProcessableNumPtr :                       */
/*               |          rest number of Processable Record               */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |          DEM_IRT_OK      : Completed.                    */
/*               |          DEM_IRT_PENDING : Continue.                     */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFFDMng_ClearAllNotVerifiedRecord
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    P2VAR( Dem_u16_RecordIndexType, AUTOMATIC, AUTOMATIC ) ClearRecordIndexPtr,
    P2VAR( Dem_u32_TotalRecordNumType, AUTOMATIC, AUTOMATIC ) RestOfProcessableNumPtr
)
{
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) udmFreezeFrameIndex;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) udmFFDRecordNum;
    VAR( Dem_u32_TotalRecordNumType, AUTOMATIC ) loopCount;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    loopCount = (Dem_u16_UdmFFDIndexType)0U;
    retVal = DEM_IRT_OK;

    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;
    udmGroupKindIndex = ( Dem_u16_UdmDemMemKindIndexType)RecordFieldIndex;

    if( udmGroupKindIndex < userDefinedMemoryNum )              /* [GUD:if]udmGroupKindIndex */
    {
        udmFFDRecordNum = Dem_UdmFreezeFrameRecordTable[udmGroupKindIndex].DemFFDRecordNum;                                                             /* [GUD]udmGroupKindIndex */
        for( udmFreezeFrameIndex = (Dem_u16_UdmFFDIndexType)( *ClearRecordIndexPtr ); udmFreezeFrameIndex < udmFFDRecordNum; udmFreezeFrameIndex++ )    /* [GUD:for]udmFreezeFrameIndex */
        {
            if( loopCount < *RestOfProcessableNumPtr )
            {
                if( Dem_UdmFFDNvMStatus[ udmGroupKindIndex ].DemUdmFFDNvMStatusPtr[ udmFreezeFrameIndex ] == DEM_RECMNGCMN_NVM_STS_NOT_VERIFIED )       /* [GUD]udmGroupKindIndex *//* [GUD]udmFreezeFrameIndex *//* [ARYCHK] udmFFDRecordNum / 1 / udmFreezeFrameIndex *//* [ARYDESC] The registered data size of Dem_UdmFFDNvMStatus[ udmGroupKindIndex ].DemUdmFFDNvMStatusPtr is the same as Dem_UdmFreezeFrameRecordTable[udmGroupKindIndex].DemFFDRecordNum */
                {
                    Dem_UdmFFDMng_InitRecord( udmGroupKindIndex, udmFreezeFrameIndex );
                    Dem_UdmFFDNvMStatus[ udmGroupKindIndex ].DemUdmFFDNvMStatusPtr[ udmFreezeFrameIndex ] = DEM_RECMNGCMN_NVM_STS_NON_TARGET;           /* [GUD]udmGroupKindIndex *//* [GUD]udmFreezeFrameIndex *//* [ARYCHK] udmFFDRecordNum / 1 / udmFreezeFrameIndex *//* [ARYDESC] The registered data size of Dem_UdmFFDNvMStatus[ udmGroupKindIndex ].DemUdmFFDNvMStatusPtr is the same as Dem_UdmFreezeFrameRecordTable[udmGroupKindIndex].DemFFDRecordNum */
                }
                loopCount = loopCount + (Dem_u32_TotalRecordNumType)1U;
            }
            else
            {
                *ClearRecordIndexPtr = (Dem_u16_RecordIndexType)udmFreezeFrameIndex;
                retVal = DEM_IRT_PENDING;
                break;
            }
        }

        if( udmFreezeFrameIndex >= udmFFDRecordNum )
        {
            *RestOfProcessableNumPtr = ( *RestOfProcessableNumPtr ) - loopCount;  /* no wrap around */
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_UdmFFDMng_GetNumOfStoredUdmFFD                       */
/* Description   | Get the number of stored Udm FFD.                        */
/* Preconditions |                                                          */
/* Parameters    | UdmEventMemoryRecordListPtr                              */
/* Return Value  | void                                                     */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmFFDMng_GetNumOfStoredUdmFFD
(
    P2VAR( Dem_UdmEventMemoryRecordType, AUTOMATIC, DEM_VAR_NO_INIT )  UdmEventMemoryRecordListPtr
)
{
    P2CONST( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) freezeFrameRecordDataPtr;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) udmFreezeFrameIndex;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) udmFFDRecordNum;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posRecordStatus;

    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;

    for( udmGroupKindIndex = (Dem_u16_UdmDemMemKindIndexType)0U; udmGroupKindIndex < userDefinedMemoryNum; udmGroupKindIndex++ )    /* [GUD:for]udmGroupKindIndex */
    {
        posRecordStatus = Dem_UdmFreezeFrameDataPosTable[udmGroupKindIndex].RecordStatus;   /* [GUD]udmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:udmGroupKindIndex]posRecordStatus */

        /*  check available data of Dem_UdmFreezeFrameDataPosTable[]    */
        if ( posRecordStatus != DEM_FFDSTOREDINDEX_INVALID )
        {
            udmFFDRecordNum = Dem_UdmFreezeFrameRecordTable[udmGroupKindIndex].DemFFDRecordNum;                                     /* [GUD]udmGroupKindIndex */

            for( udmFreezeFrameIndex = (Dem_u16_UdmFFDIndexType)0U; udmFreezeFrameIndex < udmFFDRecordNum; udmFreezeFrameIndex++ )
            {
                freezeFrameRecordDataPtr = ( P2CONST( uint8, TYPEDEF, DEM_VAR_SAVED_ZONE ) )Dem_UdmFFDMng_GetFreezeFrameRecordDataPtr( udmGroupKindIndex, udmFreezeFrameIndex );    /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/UdmFreezeFrameIndex/freezeFrameRecordDataPtr */
                if( freezeFrameRecordDataPtr != NULL_PTR )                                              /* [GUD:if]freezeFrameRecordDataPtr */
                {
                    if( freezeFrameRecordDataPtr[posRecordStatus] == DEM_FFD_STORED )                   /* [GUD]freezeFrameRecordDataPtr *//* [GUD]posRecordStatus *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[udmGroupKindIndex].DemFFDStoredFormatSize / 1 / posRecordStatus */
                    {
                        UdmEventMemoryRecordListPtr[udmGroupKindIndex].NumberOfFreezeFrameRecords = UdmEventMemoryRecordListPtr[udmGroupKindIndex].NumberOfFreezeFrameRecords + (Dem_u16_UdmFFDIndexType)1U;    /* [GUD]udmGroupKindIndex *//* [ARYCHK] DEM_USER_DEFINED_MEMORY_NUM / 1 / udmGroupKindIndex *//* [ARYCHK] DEM_USER_DEFINED_MEMORY_NUM / 1 / udmGroupKindIndex */
                    }
                }
            }
        }
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dem_UdmFFDMng_CheckConsistency                           */
/* Description   | check consistency of FFD record                          */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmGroupKindIndex                                   */
/*               |        Index of user defined memory table                */
/*               | [in] UdmEventIndex : The event index                     */
/*               | [in] UdmFreezeFrameIndex : The udm freeze frame index.   */
/* Return Value  | Dem_u08_InternalReturnType :                             */
/*               |       DEM_IRT_OK  : This FFDRecord is consistency.       */
/*               |       DEM_IRT_NG  : This FFDRecord is inconsistency.     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFFDMng_CheckConsistency
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,     /* [PRMCHK:CALLER] */
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) UdmFreezeFrameIndex
)
{
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) firstBlockUdmEventIndex;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) lastBlockUdmEventIndex;
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) firstBlockCId;
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) lastBlockCId;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;

    firstBlockUdmEventIndex =   DEM_UDMEVENTINDEX_INVALID;
    lastBlockUdmEventIndex  =   DEM_UDMEVENTINDEX_INVALID;
    firstBlockCId   =   DEM_CONSISTENCY_INITIAL;
    lastBlockCId    =   DEM_CONSISTENCY_INITIAL;

    Dem_UdmFFDMng_GetFFDConsistencyInfo( UdmGroupKindIndex, UdmFreezeFrameIndex, &firstBlockCId, &lastBlockCId, &firstBlockUdmEventIndex, &lastBlockUdmEventIndex );    /* [GUDCHK:CALLER]UdmGroupKindIndex *//* [GUDCHK:CALLER]UdmFreezeFrameIndex */

    if( UdmEventIndex == firstBlockUdmEventIndex )
    {
        if( firstBlockUdmEventIndex == lastBlockUdmEventIndex )
        {
            if( firstBlockCId == lastBlockCId )
            {
                retVal = Dem_UdmFFDMng_VerifyChecksum( UdmGroupKindIndex, UdmFreezeFrameIndex );        /* [GUDCHK:CALLER]UdmGroupKindIndex */
            }
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_DataMng_GetFFDConsistencyInfo                        */
/* Description   | check consistency of FFD record                          */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmGroupKindIndex                                   */
/*               |        Index of user defined memory table                */
/*               | [in] UdmFreezeFrameIndex :                               */
/*               |        The FreezeFrame index                             */
/*               | [out] FirstBlockCIdPtr :                                 */
/*               |        The pointer of ConsistencyId of first block       */
/*               | [out] FirstBlockCIdPtr :                                 */
/*               |        The pointer of ConsistencyId of last block        */
/*               | [out] FirstBlockUdmEventIndexPtr :                      */
/*               |        The pointer of UdmEventIndex of first block      */
/*               | [out] LastBlockUdmEventIndexPtr :                       */
/*               |        The pointer of UdmEventIndex of last block       */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmFFDMng_GetFFDConsistencyInfo
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) UdmFreezeFrameIndex,
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) FirstBlockCIdPtr,
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) LastBlockCIdPtr,
    P2VAR( Dem_u16_UdmEventIndexType, AUTOMATIC, AUTOMATIC ) FirstBlockUdmEventIndexPtr,
    P2VAR( Dem_u16_UdmEventIndexType, AUTOMATIC, AUTOMATIC ) LastBlockUdmEventIndexPtr
)
{
    P2CONST( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) freezeFrameRecordDataPtr;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstCid;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posLastCid;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) firstUdmEventIndex;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) lastUdmEventIndex;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstUdmEventIndexUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstUdmEventIndexLower;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posLastUdmEventIndexUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posLastUdmEventIndexLower;

    freezeFrameRecordDataPtr = ( P2CONST( uint8, TYPEDEF, DEM_VAR_SAVED_ZONE ) )Dem_UdmFFDMng_GetFreezeFrameRecordDataPtr( UdmGroupKindIndex, UdmFreezeFrameIndex );    /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/UdmFreezeFrameIndex/freezeFrameRecordDataPtr */
    if ( freezeFrameRecordDataPtr != NULL_PTR )                                             /* [GUD:if]freezeFrameRecordDataPtr */
    {
        posFirstCid = Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex].FirstCID;                                       /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posFirstCid */
        posLastCid = Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex].LastCID;                                         /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posLastCid */
        posFirstUdmEventIndexUpper = Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex].FirstUdmEventIndexUpper;         /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posFirstUdmEventIndexUpper */
        posFirstUdmEventIndexLower = Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex].FirstUdmEventIndexLower;         /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posFirstUdmEventIndexLower */
        posLastUdmEventIndexUpper = Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex].LastUdmEventIndexUpper;           /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posLastUdmEventIndexUpper  */
        posLastUdmEventIndexLower = Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex].LastUdmEventIndexLower;           /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posLastUdmEventIndexLower  */

        /*  check available data of Dem_UdmFreezeFrameDataPosTable[]    */
        if ( posFirstCid != DEM_FFDSTOREDINDEX_INVALID )
        {
            *FirstBlockCIdPtr = (Dem_u08_ConsistencyIdType)freezeFrameRecordDataPtr[posFirstCid];                       /* [GUD]freezeFrameRecordDataPtr *//* [GUD]posFirstCid *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posFirstCid */
            *LastBlockCIdPtr = (Dem_u08_ConsistencyIdType)freezeFrameRecordDataPtr[posLastCid];                         /* [GUD]freezeFrameRecordDataPtr *//* [GUD]posLastCid *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posLastCid */

            firstUdmEventIndex = (Dem_u16_UdmEventIndexType)Dem_UtlMem_ConvertByteData( freezeFrameRecordDataPtr[posFirstUdmEventIndexUpper], freezeFrameRecordDataPtr[posFirstUdmEventIndexLower] );   /* [GUD]freezeFrameRecordDataPtr *//* [GUD]posFirstUdmEventIndexUpper *//* [GUD]posFirstUdmEventIndexLower *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posFirstUdmEventIndexUpper *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posFirstUdmEventIndexLower */
            *FirstBlockUdmEventIndexPtr = firstUdmEventIndex;
            lastUdmEventIndex = (Dem_u16_UdmEventIndexType)Dem_UtlMem_ConvertByteData( freezeFrameRecordDataPtr[posLastUdmEventIndexUpper], freezeFrameRecordDataPtr[posLastUdmEventIndexLower] );      /* [GUD]freezeFrameRecordDataPtr *//* [GUD]posLastUdmEventIndexUpper *//* [GUD]posLastUdmEventIndexLower *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posLastUdmEventIndexUpper *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posLastUdmEventIndexLower */
            *LastBlockUdmEventIndexPtr = lastUdmEventIndex;
        }
        else
        {
            *FirstBlockCIdPtr = DEM_CONSISTENCY_INITIAL;
            *LastBlockCIdPtr  = DEM_CONSISTENCY_INITIAL;
            *FirstBlockUdmEventIndexPtr = DEM_UDMEVENTINDEX_INVALID;
            *LastBlockUdmEventIndexPtr  = DEM_UDMEVENTINDEX_INVALID;
        }
    }
    else
    {
        *FirstBlockCIdPtr = DEM_CONSISTENCY_INITIAL;
        *LastBlockCIdPtr  = DEM_CONSISTENCY_INITIAL;
        *FirstBlockUdmEventIndexPtr = DEM_UDMEVENTINDEX_INVALID;
        *LastBlockUdmEventIndexPtr  = DEM_UDMEVENTINDEX_INVALID;
    }
    return;
}


#if ( DEM_FF_CHECKSUM_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_UdmFFDMng_VerifyChecksum                             */
/* Description   | verify checksum of UdmFFD record                         */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmGroupKindIndex                                   */
/*               |        Index of user defined memory table                */
/*               | [in] UdmFreezeFrameIndex : The freeze frame index        */
/* Return Value  | Dem_u08_InternalReturnType :                             */
/*               |       DEM_IRT_OK  : This checksum is consistency.        */
/*               |       DEM_IRT_NG  : This checksum is inconsistency.      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFFDMng_VerifyChecksum
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) UdmFreezeFrameIndex
)
{
    P2CONST( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) freezeFrameRecordDataPtr;
    VAR( Dem_u16_FFCheckSumType, AUTOMATIC ) registeredChecksum;
    VAR( Dem_u16_FFCheckSumType, AUTOMATIC ) calculatedChecksum;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) udmFFDMaxLength;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posDataStart;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;

    freezeFrameRecordDataPtr = ( P2CONST( uint8, TYPEDEF, DEM_VAR_SAVED_ZONE ) )Dem_UdmFFDMng_GetFreezeFrameRecordDataPtr( UdmGroupKindIndex, UdmFreezeFrameIndex );    /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/UdmFreezeFrameIndex/freezeFrameRecordDataPtr */
    if ( freezeFrameRecordDataPtr != NULL_PTR )                                             /* [GUD:if]freezeFrameRecordDataPtr */
    {
        udmFFDMaxLength = Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDMaxLength;                             /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]udmFFDMaxLength */
        posDataStart = Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex].DataStart;                                     /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posDataStart */

        /*  check available data of Dem_UdmFreezeFrameDataPosTable[]    */
        if ( posDataStart != DEM_FFDSTOREDINDEX_INVALID )
        {
            registeredChecksum = Dem_UdmFFDMng_GetChecksum( UdmGroupKindIndex, UdmFreezeFrameIndex );                   /* [GUD]UdmGroupKindIndex *//* [GUD]UdmFreezeFrameIndex */
            calculatedChecksum = Dem_UtlMem_Checksum( &freezeFrameRecordDataPtr[posDataStart], udmFFDMaxLength );       /* [GUD]freezeFrameRecordDataPtr *//* [GUD]posDataStart *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posDataStart */

            if( registeredChecksum == calculatedChecksum )
            {
                retVal = DEM_IRT_OK;
            }
        }
    }
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_UdmFFDMng_GetChecksum                                */
/* Description   | get checksum in FFD record                               */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmGroupKindIndex                                   */
/*               |        Index of user defined memory table                */
/*               | [in] UdmFreezeFrameIndex : The freeze frame index        */
/* Return Value  | uin16 :                                                  */
/*               |       The checksum value                                 */
/*               |       DEM_IRT_NG  : This checksum is inconsistency.      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u16_FFCheckSumType, DEM_CODE ) Dem_UdmFFDMng_GetChecksum
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) UdmFreezeFrameIndex
)
{
    P2CONST( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) freezeFrameRecordDataPtr;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posChecksumUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posChecksumLower;
    VAR( uint8, AUTOMATIC ) checksumUpper;
    VAR( uint8, AUTOMATIC ) checksumLower;
    VAR( Dem_u16_FFCheckSumType, AUTOMATIC ) checksum;

    checksum    =   (Dem_u16_FFCheckSumType)0U;

    freezeFrameRecordDataPtr = ( P2CONST( uint8, TYPEDEF, DEM_VAR_SAVED_ZONE ) )Dem_UdmFFDMng_GetFreezeFrameRecordDataPtr( UdmGroupKindIndex, UdmFreezeFrameIndex );    /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/UdmFreezeFrameIndex/freezeFrameRecordDataPtr */

    /*  check available data of Dem_UdmFreezeFrameDataPosTable[]    */
    if ( freezeFrameRecordDataPtr != NULL_PTR )                                             /* [GUD:if]freezeFrameRecordDataPtr */
    {
        posChecksumUpper = Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex].ChecksumUpper;         /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posChecksumUpper */
        posChecksumLower = Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex].ChecksumLower;         /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posChecksumLower */

        if ( posChecksumUpper != DEM_FFDSTOREDINDEX_INVALID )
        {
            checksumUpper = (uint8)freezeFrameRecordDataPtr[posChecksumUpper];                      /* [GUD]freezeFrameRecordDataPtr *//* [GUD]posChecksumUpper *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posChecksumUpper */
            checksumLower = (uint8)freezeFrameRecordDataPtr[posChecksumLower];                      /* [GUD]freezeFrameRecordDataPtr *//* [GUD]posChecksumLower *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posChecksumLower */

            checksum = (Dem_u16_FFCheckSumType)checksumUpper << DEM_UDMMNG_CHECKSUM_SHIFT;
            checksum |= (Dem_u16_FFCheckSumType)checksumLower;
        }
    }

    return checksum;
}

#endif /* ( DEM_FF_CHECKSUM_SUPPORT == STD_ON ) */

#if ( DEM_FF_CHECKSUM_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_UdmFFDMng_VerifyChecksum                             */
/* Description   | verify checksum of FFD record                            */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmGroupKindIndex                                   */
/*               |        Index of user defined memory table                */
/*               | [in] UdmFreezeFrameIndex : The freeze frame index        */
/* Return Value  | Dem_u08_InternalReturnType :                             */
/*               |       DEM_IRT_OK  : This checksum is consistency.        */
/*               |       DEM_IRT_NG  : This checksum is inconsistency.      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFFDMng_VerifyChecksum
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,      /* MISRA DEVIATION */
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) UdmFreezeFrameIndex            /* MISRA DEVIATION */
)
{
    return DEM_IRT_OK;
}
#endif /* ( DEM_FF_CHECKSUM_SUPPORT == STD_OFF ) */


/****************************************************************************/
/* Function Name | Dem_UdmFFDMng_GetFFDConsystencyId                        */
/* Description   | check consistency of FFD record                          */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmGroupKindIndex                                   */
/*               |        Index of user defined memory table                */
/*               | [in] UdmFreezeFrameIndex :                               */
/*               |        The FreezeFrame index                             */
/* Return Value  | Dem_u08_ConsistencyIdType                                */
/*               |        ConsistencyId                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_ConsistencyIdType, DEM_CODE ) Dem_UdmFFDMng_GetFFDConsystencyId
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) UdmFreezeFrameIndex
)
{
    P2CONST( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) freezeFrameRecordDataPtr;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstCid;
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) consistencyId;

    consistencyId   =   DEM_CONSISTENCY_INITIAL;

    freezeFrameRecordDataPtr = ( P2CONST( uint8, TYPEDEF, DEM_VAR_SAVED_ZONE ) )Dem_UdmFFDMng_GetFreezeFrameRecordDataPtr( UdmGroupKindIndex, UdmFreezeFrameIndex );    /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/UdmFreezeFrameIndex/freezeFrameRecordDataPtr */

    /*  check available data of Dem_UdmFreezeFrameDataPosTable[]    */
    if ( freezeFrameRecordDataPtr != NULL_PTR )                                             /* [GUD:if]freezeFrameRecordDataPtr */
    {
        posFirstCid     =   Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex].FirstCID;         /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posFirstCid */
        if ( posFirstCid != DEM_FFDSTOREDINDEX_INVALID )
        {
            consistencyId = (Dem_u08_ConsistencyIdType)freezeFrameRecordDataPtr[posFirstCid];   /* [GUD]freezeFrameRecordDataPtr *//* [GUD]posFirstCid *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posFirstCid */
        }
    }

    return consistencyId;
}


#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_UdmFFDMng_InitMirrorMemory                           */
/* Description   | Initialize the Mirror Memory.                            */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmFFDMng_InitMirrorMemory
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex      /* [PRMCHK:CALLER] */
)
{
    P2VAR( uint8, AUTOMATIC, DEM_VAR_NO_INIT ) tmpUdmFFDMirrorDataPtr;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) ffdStoredFormatSize;

    if( Dem_UdmFreezeFrameRecordNvMTable[UdmGroupKindIndex].DemTmpUdmFFDMirrorDataPtr != NULL_PTR )                 /* [GUDCHK:CALLER]UdmGroupKindIndex */
    {
        tmpUdmFFDMirrorDataPtr = Dem_UdmFreezeFrameRecordNvMTable[UdmGroupKindIndex].DemTmpUdmFFDMirrorDataPtr;     /* [GUDCHK:CALLER]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]tmpUdmFFDMirrorDataPtr */

        ffdStoredFormatSize = Dem_UdmFreezeFrameRecordTable[ UdmGroupKindIndex ].DemFFDStoredFormatSize;            /* [GUDCHK:CALLER]UdmGroupKindIndex */
        Dem_UtlMem_SetMemory( &tmpUdmFFDMirrorDataPtr[0], DEM_FFD_INITIAL, ffdStoredFormatSize );                   /* [GUDCHK:CALLER]UdmGroupKindIndex *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / 0 *//* [ARYDESC] The registered data size of Dem_UdmFreezeFrameRecordNvMTable[udmGroupKindIndex].DemTmpUdmFFDMirrorDataPtr is the same as Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize */
    }

    return;
}
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */


/****************************************************************************/
/* Function Name | Dem_UdmFFDMng_GetFFR_MngInfo                             */
/* Description   | Gets UdmFaultIndex of the FreezeFrame record from the F- */
/*               | reezeFrame record list corresponding to the specified F- */
/*               | reezeFrame index. (for Dem_DataCtl subunit)              */
/* Preconditions | The specified FreezeFrame index be within the range of - */
/*               | the FreezeFrame record list.                             */
/* Parameters    | [in] UdmGroupKindIndex                                   */
/*               |        Index of user defined memory table                */
/*               | [in] UdmFreezeFrameIndex :                               */
/*               |        The FreezeFrame index corresponding to the speci- */
/*               |        fic FreezeFrame record.                           */
/*               | [out] FreezeFrameRecordPtr :                             */
/*               |         &Dem_UdmTmpEventMemoryEntry.FreezeFrameRecord-   */
/*               |         List[]                                           */
/*               |         AUTOMATIC                                        */
/*               |        The pointer of the FreezeFrame record correspond- */
/*               |        ing to the specified FreezeFrame index.           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFFDMng_GetFFR_MngInfo
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) UdmFreezeFrameIndex,
    P2VAR( Dem_UdmFreezeFrameRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) FreezeFrameRecordPtr
)
{
    P2CONST( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) freezeFrameRecordDataPtr;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndex;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstUdmEventIndexUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstUdmEventIndexLower;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posCidUdmFreezeFrameRecords;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posOffsetOfTSFFListIndex;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posRecordStatus;

    retVal = DEM_IRT_NG;

    freezeFrameRecordDataPtr = ( P2CONST( uint8, TYPEDEF, DEM_VAR_SAVED_ZONE ) )Dem_UdmFFDMng_GetFreezeFrameRecordDataPtr( UdmGroupKindIndex, UdmFreezeFrameIndex );    /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/UdmFreezeFrameIndex/freezeFrameRecordDataPtr */
    if( freezeFrameRecordDataPtr != NULL_PTR )                                              /* [GUD:if]freezeFrameRecordDataPtr */
    {
        posFirstUdmEventIndexUpper = Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex].FirstUdmEventIndexUpper;     /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posFirstUdmEventIndexUpper  */
        posFirstUdmEventIndexLower = Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex].FirstUdmEventIndexLower;     /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posFirstUdmEventIndexLower  */
        posCidUdmFreezeFrameRecords = Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex].CidUdmFreezeFrameRecords;   /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posCidUdmFreezeFrameRecords */
        posOffsetOfTSFFListIndex = Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex].OffsetOfTSFFListIndex;         /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posOffsetOfTSFFListIndex */
        posRecordStatus = Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex].RecordStatus;                           /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posRecordStatus */

        /*  check available data of Dem_UdmFreezeFrameDataPosTable[]    */
        if ( posRecordStatus != DEM_FFDSTOREDINDEX_INVALID )
        {
            /* Gets UdmEventIndex from storage format. */
            udmEventIndex = (Dem_u16_UdmEventIndexType)Dem_UtlMem_ConvertByteData( freezeFrameRecordDataPtr[posFirstUdmEventIndexUpper], freezeFrameRecordDataPtr[posFirstUdmEventIndexLower] );    /* [GUD]freezeFrameRecordDataPtr *//* [GUD]posFirstUdmEventIndexUpper *//* [GUD]posFirstUdmEventIndexLower *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posFirstUdmEventIndexUpper *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posFirstUdmEventIndexLower */
            FreezeFrameRecordPtr->UdmEventIndex = udmEventIndex;

            /* Makes occurrence order from storage format. */
#ifndef DEM_SIT_RANGE_CHECK
            FreezeFrameRecordPtr->OccurrenceOrder = Dem_UdmFFDMng_AssembleOccurrenceOrder( &Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex], freezeFrameRecordDataPtr );  /* [GUD]UdmGroupKindIndex */
#else   /* DEM_SIT_RANGE_CHECK */
            FreezeFrameRecordPtr->OccurrenceOrder = Dem_UdmFFDMng_AssembleOccurrenceOrder( (Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize), &Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex], freezeFrameRecordDataPtr );  /* [GUD]UdmGroupKindIndex */
#endif  /* DEM_SIT_RANGE_CHECK */

            /* Gets CidUdmFreezeFrameRecords from storage format. */
            FreezeFrameRecordPtr->CidUdmFreezeFrameRecords = (Dem_u08_ConsistencyIdType)freezeFrameRecordDataPtr[posCidUdmFreezeFrameRecords];  /* [GUD]freezeFrameRecordDataPtr *//* [GUD]posCidUdmFreezeFrameRecords *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posCidUdmFreezeFrameRecords */

            /* Gets Offset of the time-series freeze frame list record's index from storage format. */
            FreezeFrameRecordPtr->OffsetOfTSFFListIndex = Dem_UdmFFDMng_GetCheckedOffsetOfTSFFListIndex( udmEventIndex, (Dem_u08_NumOfTSFFType)freezeFrameRecordDataPtr[posOffsetOfTSFFListIndex] );    /* [GUD]freezeFrameRecordDataPtr *//* [GUD]posOffsetOfTSFFListIndex *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posOffsetOfTSFFListIndex */

            /* Gets UdmFaultIndex from storage format. */
            FreezeFrameRecordPtr->RecordStatus = (Dem_u08_FFStoredStatusType)freezeFrameRecordDataPtr[posRecordStatus];             /* [GUD]freezeFrameRecordDataPtr *//* [GUD]posRecordStatus *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posRecordStatus */

            /* Sets the return value to OK, cause the illegal value will not be returned. */
            retVal = DEM_IRT_OK;
        }
    }
    else
    {
        /* No process */
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_UdmFFDMng_GetFreezeFrameRecord                       */
/* Description   | Gets the data body of the FreezeFrame record from the F- */
/*               | reezeFrame record list corresponding to the specified F- */
/*               | reezeFrame index. (for Dem_DataCtl subunit)              */
/* Preconditions | The specified FreezeFrame index be within the range of - */
/*               | the FreezeFrame record list.                             */
/* Parameters    | [in] UdmGroupKindIndex                                   */
/*               |        Index of user defined memory table                */
/*               | [in] UdmFreezeFrameIndex :                               */
/*               |        The FreezeFrame index corresponding to the speci- */
/*               |        fic FreezeFrame record.                           */
/*               | [out] FreezeFrameRecordPtr :                             */
/*               |        The pointer of the FreezeFrame record from DataM- */
/*               |        ng corresponding to the specified FreezeFrame in- */
/*               |        dex.                                              */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFFDMng_GetFreezeFrameRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) UdmFreezeFrameIndex,
    P2VAR( Dem_UdmFreezeFrameRecordMngType, AUTOMATIC, DEM_VAR_NO_INIT ) FreezeFrameRecordPtr
)
{
    P2CONST( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) freezeFrameRecordDataPtr;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndex;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstUdmEventIndexUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstUdmEventIndexLower;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posCidUdmFreezeFrameRecords;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posRecordStatus;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posOffsetOfTSFFListIndex;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posDataStart;

    retVal = DEM_IRT_NG;

    freezeFrameRecordDataPtr = ( P2CONST( uint8, TYPEDEF, DEM_VAR_SAVED_ZONE ) )Dem_UdmFFDMng_GetFreezeFrameRecordDataPtr( UdmGroupKindIndex, UdmFreezeFrameIndex );    /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/UdmFreezeFrameIndex/freezeFrameRecordDataPtr */
    if( freezeFrameRecordDataPtr != NULL_PTR )                                              /* [GUD:if]freezeFrameRecordDataPtr */
    {
        posFirstUdmEventIndexUpper = Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex].FirstUdmEventIndexUpper;     /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posFirstUdmEventIndexUpper  */
        posFirstUdmEventIndexLower = Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex].FirstUdmEventIndexLower;     /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posFirstUdmEventIndexLower  */
        posCidUdmFreezeFrameRecords = Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex].CidUdmFreezeFrameRecords;   /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posCidUdmFreezeFrameRecords */
        posRecordStatus = Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex].RecordStatus;                           /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posRecordStatus  */
        posOffsetOfTSFFListIndex = Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex].OffsetOfTSFFListIndex;         /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posOffsetOfTSFFListIndex  */
        posDataStart = Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex].DataStart;                                 /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posDataStart  */

        /*  check available data of Dem_UdmFreezeFrameDataPosTable[]    */
        if ( posRecordStatus != DEM_FFDSTOREDINDEX_INVALID )
        {
            udmEventIndex = (Dem_u16_UdmEventIndexType)Dem_UtlMem_ConvertByteData( freezeFrameRecordDataPtr[posFirstUdmEventIndexUpper], freezeFrameRecordDataPtr[posFirstUdmEventIndexLower] );    /* [GUD]freezeFrameRecordDataPtr *//* [GUD]posFirstUdmEventIndexUpper *//* [GUD]posFirstUdmEventIndexLower *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posFirstUdmEventIndexUpper *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posFirstUdmEventIndexLower */

#ifndef DEM_SIT_RANGE_CHECK
            FreezeFrameRecordPtr->OccurrenceOrder = Dem_UdmFFDMng_AssembleOccurrenceOrder( &Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex], freezeFrameRecordDataPtr );  /* [GUD]UdmGroupKindIndex *//* [GUD]freezeFrameRecordDataPtr */
#else   /* DEM_SIT_RANGE_CHECK */
            FreezeFrameRecordPtr->OccurrenceOrder = Dem_UdmFFDMng_AssembleOccurrenceOrder( (Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize), &Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex], freezeFrameRecordDataPtr );  /* [GUD]UdmGroupKindIndex *//* [GUD]freezeFrameRecordDataPtr */
#endif  /* DEM_SIT_RANGE_CHECK */

            FreezeFrameRecordPtr->CidUdmFreezeFrameRecords = (Dem_u08_ConsistencyIdType)freezeFrameRecordDataPtr[posCidUdmFreezeFrameRecords];                              /* [GUD]freezeFrameRecordDataPtr *//* [GUD]posCidUdmFreezeFrameRecords *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posCidUdmFreezeFrameRecords */
            FreezeFrameRecordPtr->RecordStatus = (Dem_u08_FFStoredStatusType)freezeFrameRecordDataPtr[posRecordStatus];                                                     /* [GUD]freezeFrameRecordDataPtr *//* [GUD]posRecordStatus *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posRecordStatus */
            FreezeFrameRecordPtr->OffsetOfTSFFListIndex = Dem_UdmFFDMng_GetCheckedOffsetOfTSFFListIndex( udmEventIndex, (Dem_u08_NumOfTSFFType)freezeFrameRecordDataPtr[posOffsetOfTSFFListIndex] );    /* [GUD]freezeFrameRecordDataPtr *//* [GUD]posOffsetOfTSFFListIndex *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posOffsetOfTSFFListIndex */
            FreezeFrameRecordPtr->DataPtr = &freezeFrameRecordDataPtr[posDataStart];                /* [GUD]freezeFrameRecordDataPtr *//* [GUD]posDataStart *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posDataStart */

            retVal = DEM_IRT_OK;
        }
    }
    else
    {
        /* No process */
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_UdmFFDMng_GetMngInfo                                 */
/* Description   | Gets the data body of the FreezeFrame record from the F- */
/*               | reezeFrame record list corresponding to the specified F- */
/*               | reezeFrame index. (for Dem_DataCtl subunit)              */
/* Preconditions | The specified FreezeFrame index be within the range of - */
/*               | the FreezeFrame record list.                             */
/* Parameters    | [in] UdmGroupKindIndex                                   */
/*               |        Index of user defined memory table                */
/*               | [in] UdmFreezeFrameIndex :                               */
/*               |        The FreezeFrame index corresponding to the speci- */
/*               |        fic FreezeFrame record.                           */
/*               | [out] FFRMngInfoPtr :                                    */
/*               |        The pointer of the FreezeFrame record from DataM- */
/*               |        ng corresponding to the specified FreezeFrame in- */
/*               |        dex.                                              */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFFDMng_GetMngInfo
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) UdmFreezeFrameIndex,
    P2VAR( Dem_UdmFFRMngInfoType, AUTOMATIC, AUTOMATIC ) FFRMngInfoPtr
)
{
    P2CONST( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) freezeFrameRecordDataPtr;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndex;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstUdmEventIndexUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstUdmEventIndexLower;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posCidUdmFreezeFrameRecords;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posOffsetOfTSFFListIndex;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posRecordStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;

    freezeFrameRecordDataPtr = ( P2CONST( uint8, TYPEDEF, DEM_VAR_SAVED_ZONE ) )Dem_UdmFFDMng_GetFreezeFrameRecordDataPtr( UdmGroupKindIndex, UdmFreezeFrameIndex );    /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/UdmFreezeFrameIndex/freezeFrameRecordDataPtr */
    if( freezeFrameRecordDataPtr != NULL_PTR )                                                                      /* [GUD:if]freezeFrameRecordDataPtr */
    {
        posFirstUdmEventIndexUpper = Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex].FirstUdmEventIndexUpper;     /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posFirstUdmEventIndexUpper   */
        posFirstUdmEventIndexLower = Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex].FirstUdmEventIndexLower;     /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posFirstUdmEventIndexLower   */
        posCidUdmFreezeFrameRecords = Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex].CidUdmFreezeFrameRecords;   /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posCidUdmFreezeFrameRecords  */
        posOffsetOfTSFFListIndex = Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex].OffsetOfTSFFListIndex;         /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posOffsetOfTSFFListIndex  */
        posRecordStatus = Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex].RecordStatus;                           /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posRecordStatus  */

        /*  check available data of Dem_UdmFreezeFrameDataPosTable[]    */
        if ( posRecordStatus != DEM_FFDSTOREDINDEX_INVALID )
        {
            udmEventIndex = (Dem_u16_UdmEventIndexType)Dem_UtlMem_ConvertByteData( freezeFrameRecordDataPtr[posFirstUdmEventIndexUpper], freezeFrameRecordDataPtr[posFirstUdmEventIndexLower] );    /* [GUD]freezeFrameRecordDataPtr *//* [GUD]posFirstUdmEventIndexUpper *//* [GUD]posFirstUdmEventIndexLower *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posFirstUdmEventIndexUpper *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posFirstUdmEventIndexLower */
            FFRMngInfoPtr->UdmEventIndex = udmEventIndex;
#ifndef DEM_SIT_RANGE_CHECK
            FFRMngInfoPtr->OccurrenceOrder = Dem_UdmFFDMng_AssembleOccurrenceOrder( &Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex], freezeFrameRecordDataPtr );      /* [GUD]UdmGroupKindIndex *//* [GUD]freezeFrameRecordDataPtr */
#else   /* DEM_SIT_RANGE_CHECK */
            FFRMngInfoPtr->OccurrenceOrder = Dem_UdmFFDMng_AssembleOccurrenceOrder( (Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize), &Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex], freezeFrameRecordDataPtr );      /* [GUD]UdmGroupKindIndex *//* [GUD]freezeFrameRecordDataPtr */
#endif  /* DEM_SIT_RANGE_CHECK */
            FFRMngInfoPtr->CidUdmFreezeFrameRecords = (Dem_u08_ConsistencyIdType)freezeFrameRecordDataPtr[posCidUdmFreezeFrameRecords];                                                             /* [GUD]freezeFrameRecordDataPtr *//* [GUD]posCidUdmFreezeFrameRecords *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posCidUdmFreezeFrameRecords */
            FFRMngInfoPtr->OffsetOfTSFFListIndex = Dem_UdmFFDMng_GetCheckedOffsetOfTSFFListIndex( udmEventIndex, (Dem_u08_NumOfTSFFType)freezeFrameRecordDataPtr[posOffsetOfTSFFListIndex] );       /* [GUD]freezeFrameRecordDataPtr *//* [GUD]posOffsetOfTSFFListIndex *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posOffsetOfTSFFListIndex */
            FFRMngInfoPtr->RecordStatus = (Dem_u08_FFStoredStatusType)freezeFrameRecordDataPtr[posRecordStatus];        /* [GUD]freezeFrameRecordDataPtr *//* [GUD]posRecordStatus *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posRecordStatus */

            retVal = DEM_IRT_OK;
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_UdmFFDMng_GetFreezeFrameStartDataPtr                 */
/* Description   | Gets the data body of the FreezeFrame record from the F- */
/*               | reezeFrame record list corresponding to the specified F- */
/*               | reezeFrame index. (for Dem_DataCtl subunit)              */
/* Preconditions | The specified FreezeFrame index be within the range of - */
/*               | the FreezeFrame record list.                             */
/* Parameters    | [in] UdmGroupKindIndex                                   */
/*               |        Index of user defined memory table                */
/*               | [in] UdmFreezeFrameIndex :                               */
/*               |        The FreezeFrame index corresponding to the speci- */
/*               |        fic FreezeFrame record.                           */
/*               | [out] FreezeFrameRecordPtr :                             */
/*               |        The pointer of the FreezeFrame record from DataM- */
/*               |        ng corresponding to the specified FreezeFrame in- */
/*               |        dex.                                              */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC_P2VAR( uint8, DEM_VAR_SAVED_ZONE, DEM_CODE ) Dem_UdmFFDMng_GetFreezeFrameStartDataPtr
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) UdmFreezeFrameIndex
)
{
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) freezeFrameRecordDataPtr;
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) freezeFrameRecordStartDataPtr;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posDataStart;

    freezeFrameRecordStartDataPtr = NULL_PTR;

    freezeFrameRecordDataPtr = Dem_UdmFFDMng_GetFreezeFrameRecordDataPtr( UdmGroupKindIndex, UdmFreezeFrameIndex ); /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/UdmFreezeFrameIndex/freezeFrameRecordDataPtr */
    if( freezeFrameRecordDataPtr != NULL_PTR )                                              /* [GUD:if]freezeFrameRecordDataPtr */
    {
        posDataStart = Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex].DataStart;         /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posDataStart */
        /*  check available data of Dem_UdmFreezeFrameDataPosTable[]    */
        if ( posDataStart != DEM_FFDSTOREDINDEX_INVALID )
        {
            freezeFrameRecordStartDataPtr = &freezeFrameRecordDataPtr[posDataStart];        /* [GUD]freezeFrameRecordDataPtr *//* [GUD]posDataStart *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posDataStart */
        }
    }

    return freezeFrameRecordStartDataPtr;
}

/****************************************************************************/
/* Function Name | Dem_UdmFFDMng_SetFreezeFrameRecord                       */
/* Description   | Sets the data body of the FreezeFrame record to the Fre- */
/*               | ezeFrame record list corresponding to the specified Fre- */
/*               | ezeFrame index. (for Dem_DataCtl subunit)                */
/* Preconditions | The specified FreezeFrame index be within the range of - */
/*               | the FreezeFrame record list.                             */
/* Parameters    | [in] UdmGroupKindIndex                                   */
/*               |        Index of user defined memory table                */
/*               | [in] UdmFreezeFrameIndex :                               */
/*               |        The FreezeFrame index corresponding to the speci- */
/*               |        fic FreezeFrame record.                           */
/*               | [in] FreezeFrameRecordPtr :                              */
/*               |         &Dem_TmpEventMemoryEntry.FreezeFrameRecordList[] */
/*               |         AUTOMATIC                                        */
/*               |        The pointer of the FreezeFrame record correspond- */
/*               |        ing to the specified FreezeFrame index.           */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmFFDMng_SetFreezeFrameRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) UdmFreezeFrameIndex,
    P2CONST( Dem_UdmFreezeFrameRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) FreezeFrameRecordPtr
)
{
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) freezeFrameRecordDataPtr;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindUdmFFD;
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) consistencyId;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) udmFFDMaxLength;
    VAR( Dem_UdmFFRMngInfoType, AUTOMATIC ) udmFFRMngInfo;

    freezeFrameRecordDataPtr = Dem_UdmFFDMng_GetFreezeFrameRecordDataPtr( UdmGroupKindIndex, UdmFreezeFrameIndex ); /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/UdmFreezeFrameIndex/freezeFrameRecordDataPtr */
    if( freezeFrameRecordDataPtr != NULL_PTR )                                              /* [GUD:if]freezeFrameRecordDataPtr */
    {
        consistencyId = Dem_UdmFFDMng_GetFFDConsystencyId( UdmGroupKindIndex, UdmFreezeFrameIndex );    /* [GUD]UdmGroupKindIndex */

        consistencyId = Dem_UtlCid_CalcConsistencyId( consistencyId );

        udmFFDMaxLength = Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDMaxLength;             /* [GUD]UdmGroupKindIndex */

        udmFFRMngInfo.UdmEventIndex = FreezeFrameRecordPtr->UdmEventIndex;
        udmFFRMngInfo.CidUdmFreezeFrameRecords = FreezeFrameRecordPtr->CidUdmFreezeFrameRecords;
        udmFFRMngInfo.OccurrenceOrder = FreezeFrameRecordPtr->OccurrenceOrder;
        udmFFRMngInfo.OffsetOfTSFFListIndex = FreezeFrameRecordPtr->OffsetOfTSFFListIndex;
        udmFFRMngInfo.RecordStatus = FreezeFrameRecordPtr->RecordStatus;

        /* Sets the captured freeze frame data record and the index of fault to storage format. */
#ifndef DEM_SIT_RANGE_CHECK
        Dem_UdmFFDMng_SetCapturedFreezeFrame( &Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex], consistencyId, &udmFFRMngInfo, FreezeFrameRecordPtr->Data, udmFFDMaxLength, freezeFrameRecordDataPtr );   /* [GUD]UdmGroupKindIndex *//* [GUD]freezeFrameRecordDataPtr */
#else   /* DEM_SIT_RANGE_CHECK */
        Dem_UdmFFDMng_SetCapturedFreezeFrame( (Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize), &Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex], consistencyId, &udmFFRMngInfo, FreezeFrameRecordPtr->Data, udmFFDMaxLength, freezeFrameRecordDataPtr );   /* [GUD]UdmGroupKindIndex *//* [GUD]freezeFrameRecordDataPtr */
#endif  /* DEM_SIT_RANGE_CHECK */
        /* Change Dem_FFDNvMStatus */
        recMngCmnKindUdmFFD = Dem_UdmFFDNvMStatus[ UdmGroupKindIndex ].DemRecMngCmnKindUdmFFD;          /* [GUD]UdmGroupKindIndex */
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindUdmFFD, ( Dem_u16_RecordIndexType )UdmFreezeFrameIndex );
    }
    else
    {
        /* No process */
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_UdmFFDMng_SetMngInfo                                 */
/* Description   | Sets the data body of the FreezeFrame record to the Fre- */
/*               | ezeFrame record list corresponding to the specified Fre- */
/*               | ezeFrame index. (for Dem_DataCtl subunit)                */
/* Preconditions | The specified FreezeFrame index be within the range of - */
/*               | the FreezeFrame record list.                             */
/* Parameters    | [in] UdmGroupKindIndex                                   */
/*               |        Index of user defined memory table                */
/*               | [in] UdmFreezeFrameIndex :                               */
/*               |        The FreezeFrame index corresponding to the speci- */
/*               |        fic FreezeFrame record.                           */
/*               | [in] FFRMngInfoPtr :                                     */
/*               |         &Dem_TmpEventMemoryEntry.FreezeFrameRecordList[] */
/*               |         AUTOMATIC                                        */
/*               |        The pointer of the FreezeFrame record correspond- */
/*               |        ing to the specified FreezeFrame index.           */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmFFDMng_SetMngInfo
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) UdmFreezeFrameIndex,
    P2CONST( Dem_UdmFFRMngInfoType, AUTOMATIC, DEM_VAR_NO_INIT ) FFRMngInfoPtr
)
{
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) freezeFrameRecordDataPtr;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindUdmFFD;
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) consistencyId;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) udmFFDMaxLength;

    freezeFrameRecordDataPtr = Dem_UdmFFDMng_GetFreezeFrameRecordDataPtr( UdmGroupKindIndex, UdmFreezeFrameIndex ); /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/UdmFreezeFrameIndex/freezeFrameRecordDataPtr */
    if( freezeFrameRecordDataPtr != NULL_PTR )                                              /* [GUD:if]freezeFrameRecordDataPtr */
    {
        consistencyId = Dem_UdmFFDMng_GetFFDConsystencyId( UdmGroupKindIndex, UdmFreezeFrameIndex );    /* [GUD]UdmGroupKindIndex */

        consistencyId = Dem_UtlCid_CalcConsistencyId( consistencyId );

        udmFFDMaxLength = Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDMaxLength;             /* [GUD]UdmGroupKindIndex */

        /* Sets the captured freeze frame data record and the index of fault to storage format. */
#ifndef DEM_SIT_RANGE_CHECK
        Dem_UdmFFDMng_SetMngInfoToFreezeFrame( &Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex], consistencyId, FFRMngInfoPtr, freezeFrameRecordDataPtr, udmFFDMaxLength );  /* [GUD]UdmGroupKindIndex */
#else   /* DEM_SIT_RANGE_CHECK */
        Dem_UdmFFDMng_SetMngInfoToFreezeFrame( (Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize), &Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex], consistencyId, FFRMngInfoPtr, freezeFrameRecordDataPtr, udmFFDMaxLength );  /* [GUD]UdmGroupKindIndex */
#endif  /* DEM_SIT_RANGE_CHECK */

        /* Change Dem_FFDNvMStatus */
        recMngCmnKindUdmFFD = Dem_UdmFFDNvMStatus[ UdmGroupKindIndex ].DemRecMngCmnKindUdmFFD;          /* [GUD]UdmGroupKindIndex */
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindUdmFFD, ( Dem_u16_RecordIndexType )UdmFreezeFrameIndex );
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_UdmFFDMng_GetFreezeFrameRecordDataPtr                */
/* Description   | Calculates the pointer of the list of UdmFreezeFrame Re- */
/*               | cord by the specified UdmGroupKindIndex and UdmFreezeFr- */
/*               | ameIndex.                                                */
/* Preconditions | The specified UdmGroupKindIndex and UdmFreezeFrameIndex  */
/*               | shall be within the range of each maximul size.          */
/* Parameters    | [in] UdmGroupKindIndex                                   */
/*               |        Index of user defined memory table                */
/*               | [in] UdmFreezeFrameIndex :                               */
/*               |        The FreezeFrame index corresponding to the speci- */
/*               |        fic FreezeFrame record.                           */
/* Return Value  | uint8 *                                                  */
/*               |        NULL_PTR : The calculation was failed             */
/*               |        not NULL_PTR : The calculation was successful     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:Not NULL_PTR] ReturnValue                       */
/* VariableGuard | [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/UdmFreezeFrameIndex */
/* VariableGuard | [GUD:RET:IF_GUARDED UdmGroupKindIndex/UdmFreezeFrameIndex] ReturnValue */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC_P2VAR( uint8, DEM_VAR_SAVED_ZONE, DEM_CODE ) Dem_UdmFFDMng_GetFreezeFrameRecordDataPtr
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) UdmFreezeFrameIndex
)
{
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) freezeFrameRecordDataPtr;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) udmFFDRecordNum;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) ffdStoredFormatSize;
    VAR( uint32, AUTOMATIC ) udmFFDOffset;

    freezeFrameRecordDataPtr = NULL_PTR;

    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;
    if( UdmGroupKindIndex < userDefinedMemoryNum )                                              /* [GUD:if]UdmGroupKindIndex */
    {
        udmFFDRecordNum = Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDRecordNum;     /* [GUD]UdmGroupKindIndex */
        if( UdmFreezeFrameIndex < udmFFDRecordNum )                                             /* [GUD:if]UdmFreezeFrameIndex */
        {
            freezeFrameRecordDataPtr = Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFreezeFrameRecordListStartDataPtr;   /* [GUD]UdmGroupKindIndex */
            ffdStoredFormatSize = Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize;                      /* [GUD]UdmGroupKindIndex */

            udmFFDOffset = (uint32)( (uint32)ffdStoredFormatSize * (uint32)UdmFreezeFrameIndex );   /* no wrap around *//* [GUD:CFG:IF_GUARDED UdmFreezeFrameIndex ]udmFFDOffset */

            freezeFrameRecordDataPtr = &freezeFrameRecordDataPtr[udmFFDOffset];                 /* [GUD]freezeFrameRecordDataPtr *//* [GUD]udmFFDOffset *//* [ARYCHK] (ffdStoredFormatSize*udmFFDRecordNum) / 1 / udmFFDOffset */
        }
    }

    return freezeFrameRecordDataPtr;
}


/****************************************************************************/
/* Function Name | Dem_UdmFFDMng_GetNextFreezeFrameInfo                     */
/* Description   | Gets the oldest freeze frame record index and the newst  */
/*               | occurrence order.                                        */
/* Preconditions | The specified UdmGroupKindIndex and StartFreezeFrameRec- */
/*               | ordIndex shall be within the range of each maximul size. */
/* Parameters    | [in] FaultOfTheFirstTime :                               */
/*               |        The flag for fault of the first time or not.      */
/*               | [in] UdmGroupKindIndex :                                 */
/*               |        Index of user defined memory table                */
/*               | [in] StartFreezeFrameRecordIndex :                       */
/*               |        The FreezeFrame index corresponding to the speci- */
/*               |        fic FreezeFrame record, which points to start se- */
/*               |        arching.                                          */
/*               | [in] MaxNumberFreezeFrameRecords :                       */
/*               |        The number of freeze frame record per DTC.        */
/*               | [out] Dem_UdmFreezeFrameRecordMngType :                  */
/*               |        The information of next udm reeze frame record.   */
/*               |        Including as follows.                             */
/*               |          FreezeFrameRecordIndex :                        */
/*               |           The index for udm reeze frame record list whi- */
/*               |           ch has the largest occurrence order.           */
/*               |          OccurrenceOrder :                               */
/*               |           The occurrence order for udm freeze frame rec- */
/*               |           ord  list which has the next occurrence order. */
/*               |          CidUdmFreezeFrameRecords :                      */
/*               |           The cid for udm freeze frame record list which */
/*               |           has the smallest occurrence order.             */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFFDMng_GetNextFreezeFrameInfo
(
    VAR( boolean, AUTOMATIC ) FaultOfTheFirstTime,
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) StartFreezeFrameRecordIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) MaxNumberFreezeFrameRecords,
    P2VAR( Dem_UdmNextFreezeFrameType, AUTOMATIC, AUTOMATIC ) UdmNextFreezeFrameInfoPtr
)
{
    P2CONST( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) freezeFrameRecordDataPtr;
    VAR( boolean , AUTOMATIC ) isOccurrenceOrderUnderflow;
    VAR( boolean , AUTOMATIC ) doGetNextFreezeFrameInfo;
    VAR( Dem_u08_InternalReturnType , AUTOMATIC ) retVal;
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) cidUdmFreezeFrameRecords;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posCidUdmFreezeFrameRecords;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posRecordStatus;
    VAR( Dem_u08_FFStoredStatusType, AUTOMATIC ) recordStatus;
    VAR( Dem_u16_UdmFFDIndexType , AUTOMATIC ) freezeFrameRecordIndex;
    VAR( Dem_u16_UdmFFDIndexType , AUTOMATIC ) freezeFrameRecordIndexLimit;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) ffdNotStoredFreezeFrameRecordIndex;
    VAR( Dem_u32_UdmOccurrenceOrderType , AUTOMATIC ) occurrenceOrder;

    VAR( Dem_UdmNextFreezeFrameType, AUTOMATIC ) oldestUdmNextFreezeFrameInfo;
    VAR( Dem_UdmNextFreezeFrameType, AUTOMATIC ) newestUdmNextFreezeFrameInfo;
    VAR( Dem_UdmNextFreezeFrameType, AUTOMATIC ) oldestUdmNextFreezeFrameInfoUnderflow;
    VAR( Dem_UdmNextFreezeFrameType, AUTOMATIC ) newestUdmNextFreezeFrameInfoUnderflow;

    retVal = DEM_IRT_NG;

    freezeFrameRecordDataPtr = ( P2CONST( uint8, TYPEDEF, DEM_VAR_SAVED_ZONE ) )Dem_UdmFFDMng_GetFreezeFrameRecordDataPtr( UdmGroupKindIndex, StartFreezeFrameRecordIndex );/* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/StartFreezeFrameRecordIndex/freezeFrameRecordDataPtr */
    if( freezeFrameRecordDataPtr != NULL_PTR )                                              /* [GUD:if]freezeFrameRecordDataPtr */
    {
        isOccurrenceOrderUnderflow = (boolean)FALSE;

#ifndef DEM_SIT_RANGE_CHECK
        occurrenceOrder = Dem_UdmFFDMng_AssembleOccurrenceOrder( &Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex], freezeFrameRecordDataPtr );    /* [GUD]UdmGroupKindIndex *//* [GUD]freezeFrameRecordDataPtr */
#else   /* DEM_SIT_RANGE_CHECK */
        occurrenceOrder = Dem_UdmFFDMng_AssembleOccurrenceOrder( (Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize), &Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex], freezeFrameRecordDataPtr );    /* [GUD]UdmGroupKindIndex *//* [GUD]freezeFrameRecordDataPtr */
#endif  /* DEM_SIT_RANGE_CHECK */
        if( occurrenceOrder == (Dem_u32_UdmOccurrenceOrderType)0U )
        {
            isOccurrenceOrderUnderflow = (boolean)TRUE;
        }
        oldestUdmNextFreezeFrameInfo.OccurrenceOrder = occurrenceOrder;
        newestUdmNextFreezeFrameInfo.OccurrenceOrder = occurrenceOrder;
        occurrenceOrder = occurrenceOrder ^ DEM_UDM_OCCURRENCEORDER_MSB;
        oldestUdmNextFreezeFrameInfoUnderflow.OccurrenceOrder = occurrenceOrder;
        newestUdmNextFreezeFrameInfoUnderflow.OccurrenceOrder = occurrenceOrder;

        posCidUdmFreezeFrameRecords = Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex].CidUdmFreezeFrameRecords;   /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posCidUdmFreezeFrameRecords */

        /*  check available data of Dem_UdmFreezeFrameDataPosTable[]    */
        if ( posCidUdmFreezeFrameRecords != DEM_FFDSTOREDINDEX_INVALID )
        {
            cidUdmFreezeFrameRecords = (Dem_u08_ConsistencyIdType)freezeFrameRecordDataPtr[posCidUdmFreezeFrameRecords];    /* [GUD]freezeFrameRecordDataPtr *//* [GUD]posCidUdmFreezeFrameRecords *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posCidUdmFreezeFrameRecords */
            newestUdmNextFreezeFrameInfo.CidUdmFreezeFrameRecords = cidUdmFreezeFrameRecords;
            newestUdmNextFreezeFrameInfoUnderflow.CidUdmFreezeFrameRecords = cidUdmFreezeFrameRecords;

            ffdNotStoredFreezeFrameRecordIndex = DEM_UDMFFRECINDEX_INITIAL;
            posRecordStatus = Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex].RecordStatus;                       /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posRecordStatus */
            recordStatus = (Dem_u08_FFStoredStatusType)freezeFrameRecordDataPtr[posRecordStatus];                   /* [GUD]freezeFrameRecordDataPtr *//* [GUD]posRecordStatus *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posRecordStatus */
            if( recordStatus == DEM_FFD_NOT_STORED )
            {
                ffdNotStoredFreezeFrameRecordIndex = StartFreezeFrameRecordIndex;
            }

            oldestUdmNextFreezeFrameInfo.FreezeFrameRecordIndex = StartFreezeFrameRecordIndex;
            oldestUdmNextFreezeFrameInfoUnderflow.FreezeFrameRecordIndex = StartFreezeFrameRecordIndex;

            freezeFrameRecordIndexLimit = StartFreezeFrameRecordIndex + MaxNumberFreezeFrameRecords;

            for ( freezeFrameRecordIndex = ( StartFreezeFrameRecordIndex + (Dem_u16_UdmFFDIndexType)1U ); freezeFrameRecordIndex < freezeFrameRecordIndexLimit; freezeFrameRecordIndex++ )
            {
                freezeFrameRecordDataPtr = ( P2CONST( uint8, TYPEDEF, DEM_VAR_SAVED_ZONE ) )Dem_UdmFFDMng_GetFreezeFrameRecordDataPtr( UdmGroupKindIndex, freezeFrameRecordIndex );     /* [GUD]UdmGroupKindIndex */
                if( freezeFrameRecordDataPtr != NULL_PTR )                                                  /* [GUD:if]freezeFrameRecordDataPtr */
                {
                    recordStatus = (Dem_u08_FFStoredStatusType)freezeFrameRecordDataPtr[posRecordStatus];   /* [GUD]freezeFrameRecordDataPtr *//* [GUD]posRecordStatus *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posRecordStatus */

                    if( ffdNotStoredFreezeFrameRecordIndex == DEM_UDMFFRECINDEX_INITIAL )
                    {
                        if( recordStatus == DEM_FFD_NOT_STORED )
                        {
                            ffdNotStoredFreezeFrameRecordIndex = freezeFrameRecordIndex;
                        }
                    }

                    if( FaultOfTheFirstTime == (boolean)TRUE )
                    {
                        doGetNextFreezeFrameInfo = (boolean)TRUE;
                    }
                    else if( recordStatus == DEM_FFD_STORED )
                    {
                        doGetNextFreezeFrameInfo = (boolean)TRUE;
                    }
                    else
                    {
                        doGetNextFreezeFrameInfo = (boolean)FALSE;
                    }

                    if( doGetNextFreezeFrameInfo == (boolean)TRUE )
                    {
                        cidUdmFreezeFrameRecords = (Dem_u08_ConsistencyIdType)freezeFrameRecordDataPtr[posCidUdmFreezeFrameRecords];    /* [GUD]freezeFrameRecordDataPtr *//* [GUD]posCidUdmFreezeFrameRecords *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posCidUdmFreezeFrameRecords */

#ifndef DEM_SIT_RANGE_CHECK
                        occurrenceOrder = Dem_UdmFFDMng_AssembleOccurrenceOrder( &Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex], freezeFrameRecordDataPtr );    /* [GUD]UdmGroupKindIndex *//* [GUD]freezeFrameRecordDataPtr */
#else   /* DEM_SIT_RANGE_CHECK */
                        occurrenceOrder = Dem_UdmFFDMng_AssembleOccurrenceOrder( (Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize), &Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex], freezeFrameRecordDataPtr );    /* [GUD]UdmGroupKindIndex *//* [GUD]freezeFrameRecordDataPtr */
#endif  /* DEM_SIT_RANGE_CHECK */
                        if( occurrenceOrder == (Dem_u32_UdmOccurrenceOrderType)0U )
                        {
                            isOccurrenceOrderUnderflow = (boolean)TRUE;
                        }

                        Dem_UdmFFDMng_GetOlderFreezeFrameInfo( occurrenceOrder, freezeFrameRecordIndex, &oldestUdmNextFreezeFrameInfo );
                        Dem_UdmFFDMng_GetNewerFreezeFrameInfo( occurrenceOrder, cidUdmFreezeFrameRecords, &newestUdmNextFreezeFrameInfo );

                        occurrenceOrder = occurrenceOrder ^ DEM_UDM_OCCURRENCEORDER_MSB;

                        Dem_UdmFFDMng_GetOlderFreezeFrameInfo( occurrenceOrder, freezeFrameRecordIndex, &oldestUdmNextFreezeFrameInfoUnderflow );
                        Dem_UdmFFDMng_GetNewerFreezeFrameInfo( occurrenceOrder, cidUdmFreezeFrameRecords, &newestUdmNextFreezeFrameInfoUnderflow );
                    }
                }
            }

            if( isOccurrenceOrderUnderflow == (boolean)FALSE )
            {
                if( ffdNotStoredFreezeFrameRecordIndex != DEM_UDMFFRECINDEX_INITIAL )
                {
                    UdmNextFreezeFrameInfoPtr->FreezeFrameRecordIndex = ffdNotStoredFreezeFrameRecordIndex;
                }
                else
                {
                    UdmNextFreezeFrameInfoPtr->FreezeFrameRecordIndex = oldestUdmNextFreezeFrameInfo.FreezeFrameRecordIndex;
                }

                if ( newestUdmNextFreezeFrameInfo.OccurrenceOrder > (Dem_u32_UdmOccurrenceOrderType)0U )
                {
                    UdmNextFreezeFrameInfoPtr->OccurrenceOrder = newestUdmNextFreezeFrameInfo.OccurrenceOrder - (Dem_u32_UdmOccurrenceOrderType)1U;/* no wrap around */
                }
                UdmNextFreezeFrameInfoPtr->CidUdmFreezeFrameRecords = newestUdmNextFreezeFrameInfo.CidUdmFreezeFrameRecords;
            }
            else
            {
                if( ffdNotStoredFreezeFrameRecordIndex != DEM_UDMFFRECINDEX_INITIAL )
                {
                    UdmNextFreezeFrameInfoPtr->FreezeFrameRecordIndex = ffdNotStoredFreezeFrameRecordIndex;
                }
                else
                {
                    UdmNextFreezeFrameInfoPtr->FreezeFrameRecordIndex = oldestUdmNextFreezeFrameInfoUnderflow.FreezeFrameRecordIndex;
                }

                newestUdmNextFreezeFrameInfoUnderflow.OccurrenceOrder = newestUdmNextFreezeFrameInfoUnderflow.OccurrenceOrder ^ DEM_UDM_OCCURRENCEORDER_MSB;
                if( newestUdmNextFreezeFrameInfoUnderflow.OccurrenceOrder == (Dem_u32_UdmOccurrenceOrderType)0U )
                {
                    /* If restorated newest occurrence order is zero, resets occurrence order to initial value. */
                    UdmNextFreezeFrameInfoPtr->OccurrenceOrder = DEM_UDMOCCURRENCEORDER_INITIAL - (Dem_u32_UdmOccurrenceOrderType)1U;/* no wrap around */
                }
                else
                {
                        /* If restorated newest occurrence order is not zero, down count occurrence order by one. */
                    UdmNextFreezeFrameInfoPtr->OccurrenceOrder = newestUdmNextFreezeFrameInfoUnderflow.OccurrenceOrder - (Dem_u32_UdmOccurrenceOrderType)1U;/* no wrap around */
                }

                UdmNextFreezeFrameInfoPtr->CidUdmFreezeFrameRecords = newestUdmNextFreezeFrameInfoUnderflow.CidUdmFreezeFrameRecords;
            }

            retVal = DEM_IRT_OK;
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_UdmFFDMng_GetOlderFreezeFrameInfo                    */
/* Description   | Gets older occurrence order and udm freeze frame record  */
/*               | index.                                                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] TargetOccurrenceOrder :                             */
/*               |        The occurrence order to compare.                  */
/*               | [in] TargetFreezeFrameRecordIndex :                      */
/*               |        The index for udm freeze frame record list.       */
/*               | [in/out] OldestUdmNextFreezeFrameInfoPtr :               */
/*               |        Including the largest occurrence order and the i- */
/*               |        ndex for udm reeze frame record list which has t- */
/*               |        he largest occurrence order.                      */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmFFDMng_GetOlderFreezeFrameInfo
(
    VAR( Dem_u32_UdmOccurrenceOrderType, AUTOMATIC ) TargetOccurrenceOrder,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) TargetFreezeFrameRecordIndex,
    P2VAR( Dem_UdmNextFreezeFrameType, AUTOMATIC, AUTOMATIC ) OldestUdmNextFreezeFrameInfoPtr
)
{
    if( OldestUdmNextFreezeFrameInfoPtr->OccurrenceOrder < TargetOccurrenceOrder )
    {
        /* If target occurrence order was older than oldest occurrence order, oldest occurrence order is replaced by target occurrence order  */
        OldestUdmNextFreezeFrameInfoPtr->OccurrenceOrder = TargetOccurrenceOrder;

        /* Memorizes the older information. */
        OldestUdmNextFreezeFrameInfoPtr->FreezeFrameRecordIndex = TargetFreezeFrameRecordIndex;
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_UdmFFDMng_GetNewerFreezeFrameInfo                    */
/* Description   | Gets newer occurrence order and cid for udm freeze frame */
/*               | records.                                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] TargetOccurrenceOrder :                             */
/*               |        The occurrence order to compare.                  */
/*               | [in] TargetCidUdmFreezeFrameRecords :                    */
/*               |        The consistency ID for udm freeze frame records.  */
/*               | [in/out] NewestUdmNextFreezeFrameInfoPtr :               */
/*               |        Including the smallest occurrence order and the   */
/*               |        cid for udm freeze frame record list which has t- */
/*               |        he smallest occurrence order.                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmFFDMng_GetNewerFreezeFrameInfo
(
    VAR( Dem_u32_UdmOccurrenceOrderType, AUTOMATIC ) TargetOccurrenceOrder,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) TargetCidUdmFreezeFrameRecords,
    P2VAR( Dem_UdmNextFreezeFrameType, AUTOMATIC, AUTOMATIC ) NewestUdmNextFreezeFrameInfoPtr
)
{
    if( NewestUdmNextFreezeFrameInfoPtr->OccurrenceOrder > TargetOccurrenceOrder )
    {
        /* If target occurrence order was newer than newest occurrence order, newest occurrence order is replaced by target occurrence order  */
        NewestUdmNextFreezeFrameInfoPtr->OccurrenceOrder = TargetOccurrenceOrder;

        /* Memorizes the newer information. */
        NewestUdmNextFreezeFrameInfoPtr->CidUdmFreezeFrameRecords = TargetCidUdmFreezeFrameRecords;
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_UdmFFDMng_GetRecordStatus                            */
/* Description   | Gets the record status of the specific udm freeze frame- */
/*               |  record.                                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        Index of user defined memory table                */
/*               | [in] UdmFreezeFrameRecordIndex :                         */
/*               |        The FreezeFrame index corresponding to the speci- */
/*               |        fic FreezeFrame record.                           */
/*               | [out] RecordStatusPtr :                                  */
/*               |        Record state of the freeze frame record.          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFFDMng_GetRecordStatus
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) UdmFreezeFrameRecordIndex,
    P2VAR( Dem_u08_FFStoredStatusType, AUTOMATIC, AUTOMATIC ) RecordStatusPtr
)
{
    P2CONST( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) freezeFrameRecordDataPtr;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posRecordStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;
    (*RecordStatusPtr) = DEM_FFD_NOT_STORED;
    freezeFrameRecordDataPtr = ( P2CONST( uint8, TYPEDEF, DEM_VAR_SAVED_ZONE ) )Dem_UdmFFDMng_GetFreezeFrameRecordDataPtr( UdmGroupKindIndex, UdmFreezeFrameRecordIndex );/* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/UdmFreezeFrameRecordIndex/freezeFrameRecordDataPtr */
    if( freezeFrameRecordDataPtr != NULL_PTR )                                                              /* [GUD:if]freezeFrameRecordDataPtr */
    {
        posRecordStatus = Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex].RecordStatus;                   /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posRecordStatus */
        /*  check available data of Dem_UdmFreezeFrameDataPosTable[]    */
        if ( posRecordStatus != DEM_FFDSTOREDINDEX_INVALID )
        {
            (*RecordStatusPtr) = (Dem_u08_FFStoredStatusType)freezeFrameRecordDataPtr[posRecordStatus];     /* [GUD]freezeFrameRecordDataPtr *//* [GUD]posRecordStatus *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posRecordStatus */
            retVal = DEM_IRT_OK;
        }
    }

    return retVal;
}

#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_UdmFFDMng_ClearAndSetOffsetOfTSFFListIndex           */
/* Description   | Clears and sets offset of the time-series freeze frame   */
/*               | list record's index.                                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        Index of user defined memory table                */
/*               | [in] UdmEventIndex : The event index                     */
/*               |        The index corresponding to the specific udm event */
/*               |        record.                                           */
/*               | [in] CurrentUdmFreezeFrameRecordIndex :                  */
/*               |        The current index corresponding to the specific   */
/*               |        udm FreezeFrame record.                           */
/*               | [in] StartUdmFreezeFrameRecordIndex :                    */
/*               |        The start index corresponding to the specific ud- */
/*               |        m FreezeFrame record.                             */
/*               | [in] OffsetOfTSFFListIndex :                             */
/*               |        Offset of the time-series freeze frame list reco- */
/*               |        rd's index.                                       */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmFFDMng_ClearAndSetOffsetOfTSFFListIndex
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) CurrentUdmFreezeFrameRecordIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) StartUdmFreezeFrameRecordIndex,
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) OffsetOfTSFFListIndex
)
{
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) freezeFrameRecordDataPtr;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) offsetOfTSFFListIndex;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindUdmFFD;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) loopCount;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) udmFreezeFrameRecordIndex;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) maxNumberFreezeFrameRecords;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posOffsetOfTSFFListIndex;

    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;
    if( UdmGroupKindIndex < userDefinedMemoryNum )                                                          /* [GUD:if]UdmGroupKindIndex */
    {
        posOffsetOfTSFFListIndex = Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex].OffsetOfTSFFListIndex; /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posOffsetOfTSFFListIndex */

        /*  check available data of Dem_UdmFreezeFrameDataPosTable[]    */
        if ( posOffsetOfTSFFListIndex != DEM_FFDSTOREDINDEX_INVALID )
        {
            /* Clears OffsetOfTSFFListIndex from the freeze frame record corresponding to the old udm freeze frame record index. */

            maxNumberFreezeFrameRecords = Dem_CfgInfoUdm_GetMaxNumberFreezeFrameRecords( UdmEventIndex );

            for( loopCount = (Dem_u16_UdmFFDIndexType)0U; loopCount < maxNumberFreezeFrameRecords; loopCount++ )
            {
                udmFreezeFrameRecordIndex = StartUdmFreezeFrameRecordIndex + loopCount;

                freezeFrameRecordDataPtr = Dem_UdmFFDMng_GetFreezeFrameRecordDataPtr( UdmGroupKindIndex, udmFreezeFrameRecordIndex );   /* [GUD]UdmGroupKindIndex */
                if( freezeFrameRecordDataPtr != NULL_PTR )                                                              /* [GUD:if]freezeFrameRecordDataPtr */
                {
                    offsetOfTSFFListIndex = (Dem_u08_NumOfTSFFType)freezeFrameRecordDataPtr[posOffsetOfTSFFListIndex];  /* [GUD]freezeFrameRecordDataPtr *//* [GUD]posOffsetOfTSFFListIndex *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posOffsetOfTSFFListIndex */
                    if( offsetOfTSFFListIndex == OffsetOfTSFFListIndex )
                    {
                        freezeFrameRecordDataPtr[posOffsetOfTSFFListIndex] = (uint8)DEM_NUMOFTSFF_INVALID;              /* [GUD]freezeFrameRecordDataPtr *//* [GUD]posOffsetOfTSFFListIndex *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posOffsetOfTSFFListIndex */

                        /* Change Dem_FFDNvMStatus */
                        recMngCmnKindUdmFFD = Dem_UdmFFDNvMStatus[ UdmGroupKindIndex ].DemRecMngCmnKindUdmFFD;                          /* [GUD]UdmGroupKindIndex */
                        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindUdmFFD, ( Dem_u16_RecordIndexType )udmFreezeFrameRecordIndex );
                        /* Sets the return value to OK, cause the illegal value will not be returned. */

                        break;
                    }
                }
            }

            /* Sets OffsetOfTSFFListIndex to the freeze frame record corresponding to the current udm freeze frame record index. */

            freezeFrameRecordDataPtr = Dem_UdmFFDMng_GetFreezeFrameRecordDataPtr( UdmGroupKindIndex, CurrentUdmFreezeFrameRecordIndex );    /* [GUD]UdmGroupKindIndex */
            if( freezeFrameRecordDataPtr != NULL_PTR )                                                  /* [GUD:if]freezeFrameRecordDataPtr */
            {
                freezeFrameRecordDataPtr[posOffsetOfTSFFListIndex] = (uint8)OffsetOfTSFFListIndex;      /* [GUD]freezeFrameRecordDataPtr *//* [GUD]posOffsetOfTSFFListIndex *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posOffsetOfTSFFListIndex */
                /* No need to change Dem_FFDNvMStatus, cause it has been set. */
            }
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_UdmFFDMng_InitOffsetOfTSFFListIndex                  */
/* Description   | Initialize the OffsetOfTSFFListIndex of the specific udm-*/
/*               | freeze frame record.                                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        Index of user defined memory table                */
/*               | [in] UdmFreezeFrameRecordIndex :                         */
/*               |        The FreezeFrame index corresponding to the speci- */
/*               |        fic FreezeFrame record.                           */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmFFDMng_InitOffsetOfTSFFListIndex
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) UdmFreezeFrameRecordIndex
)
{
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) freezeFrameRecordDataPtr;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posOffsetOfTSFFListIndex;

    freezeFrameRecordDataPtr = Dem_UdmFFDMng_GetFreezeFrameRecordDataPtr( UdmGroupKindIndex, UdmFreezeFrameRecordIndex ); /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/UdmFreezeFrameRecordIndex/freezeFrameRecordDataPtr */
    if( freezeFrameRecordDataPtr != NULL_PTR )                                                              /* [GUD:if]freezeFrameRecordDataPtr */
    {
        posOffsetOfTSFFListIndex = Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex].OffsetOfTSFFListIndex; /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posOffsetOfTSFFListIndex */
        /*  check available data of Dem_UdmFreezeFrameDataPosTable[]    */
        if ( posOffsetOfTSFFListIndex != DEM_FFDSTOREDINDEX_INVALID )
        {
            freezeFrameRecordDataPtr[posOffsetOfTSFFListIndex] = (uint8)DEM_NUMOFTSFF_INVALID;              /* [GUD]freezeFrameRecordDataPtr *//* [GUD]posOffsetOfTSFFListIndex *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posOffsetOfTSFFListIndex */
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_UdmFFDMng_GetLatestOffsetOfTSFFListIndex             */
/* Description   | Gets the OffsetOfTSFFListIndex which has the latest occ- */
/*               | urrence order from the udm freeze frame record list cor- */
/*               | responding to the specified udm freeze frame record sta- */
/*               | rt index.                                                */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        User defined memory table Index.                  */
/*               | [in] UdmEventIndex :                                     */
/*               |        The index corresponding to the specific udm event */
/*               |        record.                                           */
/*               | [in] StartFreezeFrameRecordIndex :                       */
/*               |        The start index corresponding to the specific udm */
/*               |        freeze frame record.                              */
/* Return Value  | Dem_u08_NumOfTSFFType                                    */
/*               |        the OffsetOfTSFFListIndex which has the latest o- */
/*               |        ccurrence order.                                  */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_NumOfTSFFType, DEM_CODE ) Dem_UdmFFDMng_GetLatestOffsetOfTSFFListIndex
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) StartFreezeFrameRecordIndex
)
{
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) freezeFrameRecordDataPtr;
    VAR( boolean, AUTOMATIC ) isOccurrenceOrderUnderflow;
    VAR( Dem_u08_FFStoredStatusType, AUTOMATIC ) recordStatus;
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) offsetOfTSFFListReturnIndex;
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) offsetOfTSFFListIndex;
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) offsetOfTSFFListLatestIndex;
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) offsetOfTSFFListLatestIndexUnderflow;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) maxNumberFreezeFrameRecords;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) countOfUdmFreezeFrameRecords;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) udmFreezeFrameRecordIndex;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posRecordStatus;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posOffsetOfTSFFListIndex;
    VAR( Dem_u32_UdmOccurrenceOrderType, AUTOMATIC ) baseOccurrenceOrder;
    VAR( Dem_u32_UdmOccurrenceOrderType, AUTOMATIC ) baseOccurrenceOrderUnderflow;
    VAR( Dem_u32_UdmOccurrenceOrderType, AUTOMATIC ) targetOccurrenceOrder;
    VAR( Dem_u32_UdmOccurrenceOrderType, AUTOMATIC ) targetOccurrenceOrderUnderflow;

    maxNumberFreezeFrameRecords = Dem_CfgInfoUdm_GetMaxNumberFreezeFrameRecords( UdmEventIndex );

    offsetOfTSFFListLatestIndex = DEM_NUMOFTSFF_INVALID;
    offsetOfTSFFListLatestIndexUnderflow = DEM_NUMOFTSFF_INVALID;

    isOccurrenceOrderUnderflow = (boolean)FALSE;
    baseOccurrenceOrder = DEM_UDMOCCURRENCEORDER_INITIAL;
    baseOccurrenceOrderUnderflow = ( DEM_UDMOCCURRENCEORDER_INITIAL ^ DEM_UDM_OCCURRENCEORDER_MSB );

    for( countOfUdmFreezeFrameRecords = (Dem_u16_UdmFFDIndexType)0U; countOfUdmFreezeFrameRecords < maxNumberFreezeFrameRecords; countOfUdmFreezeFrameRecords++ )
    {
        udmFreezeFrameRecordIndex = StartFreezeFrameRecordIndex + countOfUdmFreezeFrameRecords;

        freezeFrameRecordDataPtr = Dem_UdmFFDMng_GetFreezeFrameRecordDataPtr( UdmGroupKindIndex, udmFreezeFrameRecordIndex );   /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/UdmFreezeFrameIndex/freezeFrameRecordDataPtr */
        if( freezeFrameRecordDataPtr != NULL_PTR )                                                                  /* [GUD:if]freezeFrameRecordDataPtr */
        {
            posRecordStatus = Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex].RecordStatus;                       /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posRecordStatus */
            /*  check available data of Dem_UdmFreezeFrameDataPosTable[]    */
            if ( posRecordStatus != DEM_FFDSTOREDINDEX_INVALID )
            {
                recordStatus = (Dem_u08_FFStoredStatusType)freezeFrameRecordDataPtr[posRecordStatus];               /* [GUD]freezeFrameRecordDataPtr *//* [GUD]posRecordStatus *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posRecordStatus */
                if( recordStatus == DEM_FFD_STORED )
                {
                    posOffsetOfTSFFListIndex = Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex].OffsetOfTSFFListIndex;     /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posOffsetOfTSFFListIndex */
                    offsetOfTSFFListIndex = Dem_UdmFFDMng_GetCheckedOffsetOfTSFFListIndex( UdmEventIndex, (Dem_u08_NumOfTSFFType)freezeFrameRecordDataPtr[posOffsetOfTSFFListIndex] );  /* [GUD]freezeFrameRecordDataPtr *//* [GUD]posOffsetOfTSFFListIndex *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posOffsetOfTSFFListIndex */
                    if( offsetOfTSFFListIndex != DEM_NUMOFTSFF_INVALID )
                    {
#ifndef DEM_SIT_RANGE_CHECK
                        targetOccurrenceOrder = Dem_UdmFFDMng_AssembleOccurrenceOrder( &Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex], freezeFrameRecordDataPtr );  /* [GUD]UdmGroupKindIndex *//* [GUD]freezeFrameRecordDataPtr */
#else   /* DEM_SIT_RANGE_CHECK */
                        targetOccurrenceOrder = Dem_UdmFFDMng_AssembleOccurrenceOrder( (Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize), &Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex], freezeFrameRecordDataPtr );  /* [GUD]UdmGroupKindIndex *//* [GUD]freezeFrameRecordDataPtr */
#endif  /* DEM_SIT_RANGE_CHECK */
                        if( targetOccurrenceOrder != DEM_UDMOCCURRENCEORDER_INITIAL )
                        {
                            if( targetOccurrenceOrder == (Dem_u32_UdmOccurrenceOrderType)0U )
                            {
                                isOccurrenceOrderUnderflow = (boolean)TRUE;
                            }

                            if( baseOccurrenceOrder > targetOccurrenceOrder )
                            {
                                baseOccurrenceOrder = targetOccurrenceOrder;
                                offsetOfTSFFListLatestIndex = offsetOfTSFFListIndex;
                            }

                            targetOccurrenceOrderUnderflow = targetOccurrenceOrder ^ DEM_UDM_OCCURRENCEORDER_MSB;
                            if( baseOccurrenceOrderUnderflow > targetOccurrenceOrderUnderflow )
                            {
                                baseOccurrenceOrderUnderflow = targetOccurrenceOrderUnderflow;
                                offsetOfTSFFListLatestIndexUnderflow = offsetOfTSFFListIndex;
                            }
                        }
                    }
                }
            }
        }
    }

    if( isOccurrenceOrderUnderflow == (boolean)FALSE )
    {
        offsetOfTSFFListReturnIndex = offsetOfTSFFListLatestIndex;
    }
    else
    {
        offsetOfTSFFListReturnIndex = offsetOfTSFFListLatestIndexUnderflow;
    }

    return offsetOfTSFFListReturnIndex;
}


/****************************************************************************/
/* Function Name | Dem_UdmFFDMng_GetFFRIndexByOffsetOfTSFFListIndex         */
/* Description   | Gets an index of udm freeze frame record which has the   */
/*               | specified OffsetOfTSFFListIndex.                         */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        User defined memory table Index.                  */
/*               | [in] UdmEventIndex :                                     */
/*               |        The index corresponding to the specific udm event */
/*               |        record.                                           */
/*               | [in] StartFreezeFrameRecordIndex :                       */
/*               |        The start index corresponding to the specific udm */
/*               |        freeze frame record.                              */
/*               | [in] OffsetOfTSFFListIndex :                             */
/*               |        The offset of time series freeze frame list reco- */
/*               |        rd index corresponding to the specific udm        */
/*               |        freeze frame record.                              */
/* Return Value  | Dem_u16_UdmFFDIndexType                                  */
/*               |        The index of udm freeze frame record which has t- */
/*               |        he specified OffsetOfTSFFListIndex.               */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u16_UdmFFDIndexType, DEM_CODE ) Dem_UdmFFDMng_GetFFRIndexByOffsetOfTSFFListIndex
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) StartFreezeFrameRecordIndex,
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) OffsetOfTSFFListIndex
)
{
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) freezeFrameRecordDataPtr;
    VAR( Dem_u08_FFStoredStatusType, AUTOMATIC ) recordStatus;
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) offsetOfTSFFListIndex;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) maxNumberFreezeFrameRecords;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) countOfUdmFreezeFrameRecords;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) udmFreezeFrameRecordIndex;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) udmFreezeFrameRecordReturnIndex;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posRecordStatus;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posOffsetOfTSFFListIndex;

    udmFreezeFrameRecordReturnIndex = DEM_UDMFFDINDEX_INVALID;

    maxNumberFreezeFrameRecords = Dem_CfgInfoUdm_GetMaxNumberFreezeFrameRecords( UdmEventIndex );

    for( countOfUdmFreezeFrameRecords = (Dem_u16_UdmFFDIndexType)0U; countOfUdmFreezeFrameRecords < maxNumberFreezeFrameRecords; countOfUdmFreezeFrameRecords++ )
    {
        udmFreezeFrameRecordIndex = StartFreezeFrameRecordIndex + countOfUdmFreezeFrameRecords;

        freezeFrameRecordDataPtr = Dem_UdmFFDMng_GetFreezeFrameRecordDataPtr( UdmGroupKindIndex, udmFreezeFrameRecordIndex );   /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/udmFreezeFrameRecordIndex/freezeFrameRecordDataPtr */
        if( freezeFrameRecordDataPtr != NULL_PTR )                                              /* [GUD:if]freezeFrameRecordDataPtr */
        {
            posRecordStatus = Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex].RecordStatus;   /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posRecordStatus */
            /*  check available data of Dem_UdmFreezeFrameDataPosTable[]    */
            if ( posRecordStatus != DEM_FFDSTOREDINDEX_INVALID )
            {
                recordStatus = (Dem_u08_FFStoredStatusType)freezeFrameRecordDataPtr[posRecordStatus];                       /* [GUD]freezeFrameRecordDataPtr *//* [GUD]posRecordStatus *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posRecordStatus */
                if( recordStatus == DEM_FFD_STORED )
                {
                    posOffsetOfTSFFListIndex = Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex].OffsetOfTSFFListIndex;     /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posOffsetOfTSFFListIndex */
                    offsetOfTSFFListIndex = Dem_UdmFFDMng_GetCheckedOffsetOfTSFFListIndex( UdmEventIndex, (Dem_u08_NumOfTSFFType)freezeFrameRecordDataPtr[posOffsetOfTSFFListIndex] );  /* [GUD]freezeFrameRecordDataPtr *//* [GUD]posOffsetOfTSFFListIndex *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posOffsetOfTSFFListIndex */
                    if( offsetOfTSFFListIndex != DEM_NUMOFTSFF_INVALID )
                    {
                        if( offsetOfTSFFListIndex == OffsetOfTSFFListIndex )
                        {
                            udmFreezeFrameRecordReturnIndex = udmFreezeFrameRecordIndex;
                            break;
                        }
                    }
                }
            }
        }
    }

    return udmFreezeFrameRecordReturnIndex;
}
#endif  /* ( DEM_TSFF_UDM_SUPPORT == STD_ON )   */

/****************************************************************************/
/* Function Name | Dem_UdmFFDMng_GetCheckedOffsetOfTSFFListIndex            */
/* Description   | Gets an index of udm freeze frame record which has the   */
/*               | specified OffsetOfTSFFListIndex.                         */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmEventIndex :                                     */
/*               |        The index corresponding to the specific udm event */
/*               |        record.                                           */
/*               | [in] OffsetOfTSFFListIndex :                             */
/*               |        The offset of time series freeze frame list reco- */
/*               |        rd index corresponding to the specific udm        */
/*               |        freeze frame record.                              */
/* Return Value  | Dem_u08_NumOfTSFFType                                    */
/*               |        The checked OffsetOfTSFFListIndex.                */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_NumOfTSFFType, DEM_CODE ) Dem_UdmFFDMng_GetCheckedOffsetOfTSFFListIndex
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,      /* MISRA DEVIATION */
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) OffsetOfTSFFListIndex   /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) checkedOffsetOfTSFFListIndex;

#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )  /*  [FuncSw]    */
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) numberOfTimeSeriesFreezeFramePerDTC;
    VAR( Dem_u08_TSFFClassIndexType, AUTOMATIC ) tsFFClassRef;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventConfigureNum;
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) tsFFRecClassRef;
#endif  /* ( DEM_TSFF_UDM_SUPPORT == STD_ON )           */

    checkedOffsetOfTSFFListIndex = DEM_NUMOFTSFF_INVALID;

#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )  /*  [FuncSw]    */
    udmEventConfigureNum = Dem_UdmEventConfigureNum;
    if( UdmEventIndex < udmEventConfigureNum  )                                                     /* [GUD:if]UdmEventIndex */
    {
        tsFFRecClassRef = Dem_CfgInfoUdm_GetTimeSeriesFreezeFrameRecordClassRef( UdmEventIndex );   /* [GUD]UdmEventIndex */
        if( tsFFRecClassRef != DEM_TSFF_RECORD_CLASS_REF_INVALID )                                  /* [GUD:if]tsFFRecClassRef */
        {
            tsFFClassRef = Dem_TSFFRecordClassTable[tsFFRecClassRef].DemTimeSeriesFreezeFrameClassRef;                      /* [GUD]tsFFRecClassRef *//* [GUD:CFG:IF_GUARDED:tsFFRecClassRef]tsFFClassRef */
            numberOfTimeSeriesFreezeFramePerDTC = Dem_TSFFClassTable[tsFFClassRef].DemNumberOfTimeSeriesFreezeFramePerDTC;  /* [GUD]tsFFClassRef */
            if( OffsetOfTSFFListIndex < numberOfTimeSeriesFreezeFramePerDTC )
            {
                checkedOffsetOfTSFFListIndex = OffsetOfTSFFListIndex;
            }
        }
    }
#endif  /* ( DEM_TSFF_UDM_SUPPORT == STD_ON )           */

    return checkedOffsetOfTSFFListIndex;
}


/****************************************************************************/
/* Function Name | Dem_UdmFFDMng_ClearFFDOtherThanTheFirstTime              */
/* Description   | Clears FFD other than the first time.                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        Index of user defined memory table                */
/*               | [in] UdmEventIndex : The event index                     */
/*               |        The index corresponding to the specific udm event */
/*               |        record.                                           */
/*               | [in] StartUdmFreezeFrameRecordIndex :                    */
/*               |        The start index corresponding to the specific ud- */
/*               |        m FreezeFrame record.                             */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_UdmFFDMng_ClearAndSetOffsetOfTSFFListIndex. */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmFFDMng_ClearFFDOtherThanTheFirstTime
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,     /* [PRMCHK:CALLER] */
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) StartUdmFreezeFrameRecordIndex
)
{
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) freezeFrameRecordDataPtr;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindUdmFFD;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) loopCount;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) udmFreezeFrameRecordIndex;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) maxNumberFreezeFrameRecords;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posRecordStatus;

    posRecordStatus = Dem_UdmFreezeFrameDataPosTable[UdmGroupKindIndex].RecordStatus;   /* [GUDCHK:CALLER]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posRecordStatus */

    /*  check available data of Dem_UdmFreezeFrameDataPosTable[]    */
    if ( posRecordStatus != DEM_FFDSTOREDINDEX_INVALID )
    {
        /* Clears FFD other than the first time. */

        maxNumberFreezeFrameRecords = Dem_CfgInfoUdm_GetMaxNumberFreezeFrameRecords( UdmEventIndex );

        for( loopCount = (Dem_u16_UdmFFDIndexType)1U; loopCount < maxNumberFreezeFrameRecords; loopCount++ )
        {
            udmFreezeFrameRecordIndex = StartUdmFreezeFrameRecordIndex + loopCount;

            freezeFrameRecordDataPtr = Dem_UdmFFDMng_GetFreezeFrameRecordDataPtr( UdmGroupKindIndex, udmFreezeFrameRecordIndex );   /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/UdmFreezeFrameIndex/freezeFrameRecordDataPtr */
            if( freezeFrameRecordDataPtr != NULL_PTR )                                              /* [GUD:if]freezeFrameRecordDataPtr */
            {
                /* Sets the RecordStatus to DEM_FFD_NOT_STORED even if the RecordStatus is DEM_FFD_STORED or DEM_FFD_NOT_STORED.  */
                freezeFrameRecordDataPtr[posRecordStatus] = (uint8)DEM_FFD_NOT_STORED;              /* [GUD]freezeFrameRecordDataPtr *//* [GUD]posRecordStatus *//* [ARYCHK] Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posRecordStatus */

                /* Change Dem_FFDNvMStatus */
                recMngCmnKindUdmFFD = Dem_UdmFFDNvMStatus[ UdmGroupKindIndex ].DemRecMngCmnKindUdmFFD;                              /* [GUD]UdmGroupKindIndex */
                Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindUdmFFD, ( Dem_u16_RecordIndexType )udmFreezeFrameRecordIndex );
                /* Sets the return value to OK, cause the illegal value will not be returned. */
            }
        }
    }

    return;
}


#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_UdmFFDMng_GetEventIdFromRecordData                   */
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
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFFDMng_GetEventIdFromRecordData
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
)
{
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndex;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) udmFreezeFrameIndex;
    VAR( Dem_u08_UserDefinedMemoryType, AUTOMATIC ) memType;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInfoTableIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;

    udmEventIndex       =   DEM_UDMEVENTINDEX_INVALID;
    udmFreezeFrameIndex =   ( Dem_u16_UdmFFDIndexType )RecordIndex;
    udmGroupKindIndex = ( Dem_u16_UdmDemMemKindIndexType )RecordFieldIndex;

    retVal  =   DEM_IRT_NG;
    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;
    if( udmGroupKindIndex < userDefinedMemoryNum )      /* [GUD:if]UdmGroupKindIndex */
    {
        /* Get udm info table index. */
        udmInfoTableIndex = Dem_CfgInfoUdm_GetDemUserDefinedMemoryInfoTableIndex( udmGroupKindIndex );                          /* [GUD]UdmGroupKindIndex */

        memType =   Dem_CfgInfoUdm_GetUserDefinedMemoryTypeByMemKind( udmInfoTableIndex );
        if ( memType == DEM_MEMORYTYPE_ASYNCEVENT )
        {
            retVal  =   Dem_UdmMng_GetUdmEventIndexFromUdmFFDRecord( udmGroupKindIndex, udmFreezeFrameIndex, &udmEventIndex );  /* [GUD]UdmGroupKindIndex */
        }
        else
        {
            /*  DEM_MEMORYTYPE_SYNCEVENT    */
#ifndef JGXSTACK
            Dem_UdmExcFncTable[udmGroupKindIndex].ExclusiveEnterFnc();  /* [GUD]UdmGroupKindIndex */
#else   /* JGXSTACK */
            Dem_UdmExcEnterFnc_ForStack();
#endif  /* JGXSTACK */

            retVal  =   Dem_UdmMng_GetUdmEventIndexFromUdmFFDRecord( udmGroupKindIndex, udmFreezeFrameIndex, &udmEventIndex );  /* [GUD]UdmGroupKindIndex */

#ifndef JGXSTACK
            Dem_UdmExcFncTable[udmGroupKindIndex].ExclusiveExitFnc();
#else   /* JGXSTACK */
            Dem_UdmExcExitFnc_ForStack();
#endif  /* JGXSTACK */
        }

        if ( retVal == DEM_IRT_OK )
        {
            retVal  =   Dem_UdmMng_GetEventIdFromUdmEventIndex( udmEventIndex, EventIdPtr );
        }
    }
    return retVal;
}
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
