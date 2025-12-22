/* Dem_UdmTSFFDMng_c(v5-8-0)                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UdmTSFFDMng/CODE                                      */
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
#include "../../../inc/Dem_Rc_UdmTSFFRecordTable.h"
#include "../../../inc/Dem_Rc_UdmFFRecordTable.h"
#include "../../../inc/Dem_Rc_UdmFaultRecordTable.h"
#include "Dem_UdmFreezeFrame.h"
#include "Dem_UdmMng_local.h"
#include "Dem_UdmMng_GetRecordData.h"

#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )

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
static FUNC( void, DEM_CODE ) Dem_UdmTSFFDMng_InitMirrorMemory
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex
);
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */
static FUNC( void, DEM_CODE ) Dem_UdmTSFFDMng_VerifiedRecord
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TSFFListIndex,
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) NumOfBeforeTriggeredRecord,
    P2CONST( Dem_UdmFreezeFrameRecordMngType, AUTOMATIC, DEM_VAR_NO_INIT  ) FreezeFrameRecordPtr,
    P2VAR( Dem_u16_TSFFDIndexType, AUTOMATIC, AUTOMATIC ) TSFreezeFrameStoredCntPtr
);
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmTSFFDMng_VerifiedBeforeTSFFD
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TSFFListIndex,
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) NumOfBeforeTriggeredRecord,
    P2CONST( Dem_UdmFreezeFrameRecordMngType, AUTOMATIC, DEM_VAR_NO_INIT  ) FreezeFrameRecordPtr,
    P2VAR( Dem_u16_TSFFDIndexType, AUTOMATIC, AUTOMATIC ) TSFreezeFrameStoredCntPtr
);
static FUNC( void, DEM_CODE ) Dem_UdmTSFFDMng_VerifiedAfterTSFFD
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TSFFListIndex,
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) NumOfBeforeTriggeredRecord,
    P2CONST( Dem_UdmFreezeFrameRecordMngType, AUTOMATIC, DEM_VAR_NO_INIT  ) FreezeFrameRecordPtr,
    P2VAR( Dem_u16_TSFFDIndexType, AUTOMATIC, AUTOMATIC ) TSFreezeFrameStoredCntPtr
);
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmTSFFDMng_CheckConsistency
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex,
    P2CONST( Dem_UdmFreezeFrameRecordMngType, AUTOMATIC, AUTOMATIC ) UdmTSFFRecordPtr,
    P2CONST( Dem_UdmFreezeFrameRecordMngType, AUTOMATIC, DEM_VAR_NO_INIT ) FreezeFrameRecordPtr
);
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmTSFFDMng_CheckConsistencyOneRecordData
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex
);
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmTSFFDMng_VerifyChecksum
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex
);
#if ( DEM_FF_CHECKSUM_SUPPORT == STD_ON )
static FUNC( Dem_u16_FFCheckSumType, DEM_CODE ) Dem_UdmTSFFDMng_GetChecksum
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex
);
#endif  /* ( DEM_FF_CHECKSUM_SUPPORT == STD_ON )    */
static FUNC( void, DEM_CODE ) Dem_UdmTSFFDMng_GetFFDConsistencyInfo
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex,
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) FirstBlockCIdPtr,
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) LastBlockCIdPtr,
    P2VAR( Dem_u16_UdmEventIndexType, AUTOMATIC, AUTOMATIC ) FirstBlockUdmEventIndexPtr,
    P2VAR( Dem_u16_UdmEventIndexType, AUTOMATIC, AUTOMATIC ) LastBlockUdmEventIndexPtr
);
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmTSFFDMng_CheckConsistencyWithTriggerFFDRecord
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex,
    P2CONST( Dem_UdmFreezeFrameRecordMngType, AUTOMATIC, AUTOMATIC ) UdmTSFFRecordPtr,
    P2CONST( Dem_UdmFreezeFrameRecordMngType, AUTOMATIC, DEM_VAR_NO_INIT ) FreezeFrameRecordPtr
);
static FUNC( void, DEM_CODE ) Dem_UdmTSFFDMng_GetEventIndex
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex,
    P2VAR( Dem_u16_UdmEventIndexType, AUTOMATIC, AUTOMATIC ) FirstBlockUdmEventIndexPtr
);
static FUNC_P2VAR( uint8, DEM_VAR_SAVED_ZONE, DEM_CODE ) Dem_UdmTSFFDMng_GetTimeSeriesFreezeFrameRecordDataPtr
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) UdmTimeSeriesFreezeFrameIndex
);

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
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_UdmTSFFDMng_Init                                     */
/* Description   | Init process of Udm TSFFD.                               */
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
FUNC( void, DEM_CODE ) Dem_UdmTSFFDMng_Init
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
)
{
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) udmTsffIndex;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) udmTsffTotalTimeseriesFFRecordNum;

    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;
    udmGroupKindIndex    = ( Dem_u16_UdmDemMemKindIndexType )RecordFieldIndex;

    if( udmGroupKindIndex < userDefinedMemoryNum )                                          /* [GUD:if]UdmGroupKindIndex */
    {
        udmTsffTotalTimeseriesFFRecordNum = Dem_UdmTimeSeriesFreezeFrameRecordTable[udmGroupKindIndex].DemFFDRecordNum; /* [GUD]udmGroupKindIndex */
        for( udmTsffIndex = (Dem_u16_TSFFDIndexType)0U; udmTsffIndex < udmTsffTotalTimeseriesFFRecordNum; udmTsffIndex++ )
        {
            Dem_UdmTSFFDNvMStatus[ udmGroupKindIndex ].DemUdmTSFFDNvMStatusPtr[ udmTsffIndex ] = DEM_RECMNGCMN_NVM_STS_NOT_VERIFIED;    /* [GUD]udmGroupKindIndex */    /* [GUD]udmTsffIndex *//* [ARYCHK] udmTsffTotalTimeseriesFFRecordNum / 1 / udmTsffIndex *//* [ARYDESC] The registered data size of Dem_UdmTSFFDNvMStatus[ UdmGroupKindIndex ].DemUdmTSFFDNvMStatusPtr is the same as Dem_UdmTimeSeriesFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDRecordNum */
        }
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    /* [FuncSw] */
        Dem_UdmTSFFDMng_InitMirrorMemory( udmGroupKindIndex );
#endif  /*   ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )  */
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_UdmTSFFDMng_InitSavedZone                            */
/* Description   | Initialize savedzone process of udm TSFFD.               */
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
FUNC( void, DEM_CODE ) Dem_UdmTSFFDMng_InitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType      /* MISRA DEVIATION */
)
{
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) udmTSFFRecordDataPtr;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) udmTsffIndex;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) udmTsffTotalTimeseriesFFRecordNum;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) udmTsffdStorageFormatsize;

    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;
    udmGroupKindIndex    = ( Dem_u16_UdmDemMemKindIndexType )RecordFieldIndex;

    if( udmGroupKindIndex < userDefinedMemoryNum )                                          /* [GUD:if]UdmGroupKindIndex */
    {
        udmTsffTotalTimeseriesFFRecordNum = Dem_UdmTimeSeriesFreezeFrameRecordTable[udmGroupKindIndex].DemFFDRecordNum; /* [GUD]udmGroupKindIndex */
        udmTsffdStorageFormatsize = Dem_UdmTimeSeriesFreezeFrameRecordTable[udmGroupKindIndex].DemFFDStoredFormatSize;  /* [GUD]udmGroupKindIndex */

        for( udmTsffIndex = (Dem_u16_TSFFDIndexType)0U; udmTsffIndex < udmTsffTotalTimeseriesFFRecordNum; udmTsffIndex++ )  /* [GUD:for]udmTsffIndex */
        {
            udmTSFFRecordDataPtr = Dem_UdmTSFFDMng_GetTimeSeriesFreezeFrameRecordDataPtr( udmGroupKindIndex, udmTsffIndex );    /* [GUD:RET:Not NULL_PTR] udmGroupKindIndex/udmTsffIndex/udmTSFFRecordDataPtr */
            if( udmTSFFRecordDataPtr != NULL_PTR )                                                              /* [GUD:if]udmTSFFRecordDataPtr */
            {
                Dem_UtlMem_SetMemory( &udmTSFFRecordDataPtr[0], DEM_FFD_INITIAL, udmTsffdStorageFormatsize );   /* [GUD]udmTSFFRecordDataPtr *//* [ARYCHK] udmTsffdStorageFormatsize / 1 / 0 */
            }

        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_UdmTSFFDMng_Verified                                 */
/* Description   | Verifies Udm TSFFD data.                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmEventIndex : Udm Event index.                    */
/*               | [in] UdmFaultIndex : Udm Fault index                     */
/*               | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmTSFFDMng_Verified
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex,
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex
)
{
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) startTSFFListIndex;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListIndex;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) udmTSFreezeFrameStoredCnt;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) tmpUdmTSFreezeFrameStoredCnt;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) maxNumberUdmFreezeFrame;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) udmStartFreezeFrameIndex;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) udmFreezeFrameIndex;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) udmFreezeFrameCnt;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) udmFFDRecordNum;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsffTotalDTCNum;
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) tsFFRecClassRef;
    VAR( Dem_u08_TSFFClassIndexType, AUTOMATIC ) tsFFClassRef;
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) numberOfBeforeTriggeredRecord;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindUdmFault;

    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;
    if( UdmGroupKindIndex < userDefinedMemoryNum )                                                      /* [GUD:if]UdmGroupKindIndex */
    {
        Dem_UdmFaultMngM_GetTSFFListIndex( UdmGroupKindIndex, UdmFaultIndex, &startTSFFListIndex );     /* [GUD]UdmGroupKindIndex */

        if( startTSFFListIndex != DEM_TSFFLISTINDEX_INVALID )
        {
            tsFFRecClassRef = Dem_CfgInfoUdm_GetTimeSeriesFreezeFrameRecordClassRef( UdmEventIndex );   /* [GUD:RET:Not DEM_TSFF_RECORD_CLASS_REF_INVALID ] UdmEventIndex/tsFFRecClassRef */
            if( tsFFRecClassRef != DEM_TSFF_RECORD_CLASS_REF_INVALID )
            {
                tsFFClassRef = Dem_TSFFRecordClassTable[tsFFRecClassRef].DemTimeSeriesFreezeFrameClassRef;              /* [GUD]tsFFRecClassRef *//* [GUD:CFG:IF_GUARDED:tsFFRecClassRef]tsFFClassRef */
                numberOfBeforeTriggeredRecord = Dem_TSFFClassTable[tsFFClassRef].DemNumberOfBeforeTriggeredRecord;      /* [GUD]tsFFClassRef */

                maxNumberUdmFreezeFrame = Dem_CfgInfoUdm_GetMaxNumberFreezeFrameRecords( UdmEventIndex );               /* [GUD]UdmEventIndex *//* [GUD:RET:IF_GUARDED:UdmEventIndex] maxNumberUdmFreezeFrame */
                udmFFDRecordNum = Dem_UdmFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDRecordNum;                     /* [GUD]UdmGroupKindIndex */
                udmTSFreezeFrameStoredCnt = (Dem_u16_TSFFDIndexType)0U;
                Dem_UdmFaultMngM_GetFreezeFrameIndex( UdmGroupKindIndex, UdmFaultIndex, &udmStartFreezeFrameIndex );    /* [GUD]UdmGroupKindIndex */

                if ( udmStartFreezeFrameIndex != DEM_UDMFFRECINDEX_INITIAL )
                {
                    for( udmFreezeFrameCnt = (Dem_u16_UdmFFDIndexType)0U; udmFreezeFrameCnt < maxNumberUdmFreezeFrame; udmFreezeFrameCnt++ )    /* [GUD:for]udmFreezeFrameCnt */
                    {
                        udmFreezeFrameIndex = udmStartFreezeFrameIndex + udmFreezeFrameCnt;
                        if( udmFreezeFrameIndex < udmFFDRecordNum )
                        {
                            if( Dem_TmpVerifyUdmFreezeFrameRecord[udmFreezeFrameCnt].RecordStatus == DEM_FFD_STORED  )                                  /* [GUD]udmFreezeFrameCnt */
                            {
                                tsffTotalDTCNum = Dem_TSFFTotalDTCNum;
                                if( Dem_TmpVerifyUdmFreezeFrameRecord[udmFreezeFrameCnt].OffsetOfTSFFListIndex != DEM_NUMOFTSFF_INVALID )               /* [GUD]udmFreezeFrameCnt */
                                {
                                    tsFFListIndex = startTSFFListIndex + Dem_TmpVerifyUdmFreezeFrameRecord[udmFreezeFrameCnt].OffsetOfTSFFListIndex;    /* [GUD]udmFreezeFrameCnt */
                                    tmpUdmTSFreezeFrameStoredCnt = udmTSFreezeFrameStoredCnt;

                                    if( tsFFListIndex < tsffTotalDTCNum )                                                                               /* [GUD:if]tsFFListIndex */
                                    {
                                        Dem_UdmTSFFDMng_VerifiedRecord( UdmEventIndex, UdmGroupKindIndex, tsFFListIndex, numberOfBeforeTriggeredRecord, &Dem_TmpVerifyUdmFreezeFrameRecord[udmFreezeFrameCnt], &udmTSFreezeFrameStoredCnt );    /* [GUD]UdmGroupKindIndex *//* [GUD]tsFFListIndex *//* [GUD]udmFreezeFrameCnt */
                                    }

                                    /* Initialize the offset of TSFFListIndex, if there is no valid TSFFD */
                                    if( tmpUdmTSFreezeFrameStoredCnt == udmTSFreezeFrameStoredCnt )
                                    {
                                        Dem_UdmFFDMng_InitOffsetOfTSFFListIndex( UdmGroupKindIndex, udmFreezeFrameIndex );  /* [GUD]UdmGroupKindIndex */
                                    }
                                }
                            }
                        }
                    }
                }

                if( udmTSFreezeFrameStoredCnt == (Dem_u16_TSFFDIndexType)0U )
                {
                    Dem_UdmFaultMng_InitTSFFListIndex( UdmGroupKindIndex, UdmFaultIndex );                          /* [GUD]UdmGroupKindIndex */
                    recMngCmnKindUdmFault = Dem_UdmFaultNvMStatus[ UdmGroupKindIndex ].DemRecMngCmnKindUdmFault;    /* [GUD]UdmGroupKindIndex */
                    Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindUdmFault, ( Dem_u16_RecordIndexType )UdmFaultIndex );
                }
            }
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_UdmTSFFDMng_VerifiedRecord                           */
/* Description   | Verifies Udm TSFFD data.                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmEventIndex : Udm Event index.                    */
/*               | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/*               | [in] TSFFListIndex : TsffList index                      */
/*               | [in] NumOfBeforeTriggeredRecord :                        */
/*               |        Number of before time series freeze frame.        */
/*               | [out] FreezeFrameRecordPtr :                             */
/*               |        temporary area pointer of Udm FreezeFrameRecord   */
/*               | [out] TSFreezeFrameStoredCntPtr :                        */
/*               |        Counter of valid time series freeze frame data    */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmTSFFDMng_VerifiedRecord
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,     /* [PRMCHK:CALLER] */
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TSFFListIndex,              /* [PRMCHK:CALLER] */
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) NumOfBeforeTriggeredRecord,
    P2CONST( Dem_UdmFreezeFrameRecordMngType, AUTOMATIC, DEM_VAR_NO_INIT  ) FreezeFrameRecordPtr,
    P2VAR( Dem_u16_TSFFDIndexType, AUTOMATIC, AUTOMATIC ) TSFreezeFrameStoredCntPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVerifyBeforeTSFFD;

    retVerifyBeforeTSFFD = Dem_UdmTSFFDMng_VerifiedBeforeTSFFD( UdmEventIndex, UdmGroupKindIndex, TSFFListIndex, NumOfBeforeTriggeredRecord, FreezeFrameRecordPtr, TSFreezeFrameStoredCntPtr ); /* [GUDCHK:CALLER]UdmGroupKindIndex *//* [GUDCHK:CALLER]TSFFListIndex */

    if( retVerifyBeforeTSFFD == DEM_IRT_OK )
    {
        Dem_UdmTSFFDMng_VerifiedAfterTSFFD( UdmEventIndex, UdmGroupKindIndex, TSFFListIndex, NumOfBeforeTriggeredRecord, FreezeFrameRecordPtr, TSFreezeFrameStoredCntPtr ); /* [GUDCHK:CALLER]UdmGroupKindIndex *//* [GUDCHK:CALLER]TSFFListIndex */
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_UdmTSFFDMng_VerifiedBeforeTSFFD                      */
/* Description   | Verifies Udm before TSFFD data.                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmEventIndex : Udm Event index.                    */
/*               | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/*               | [in] TSFFListIndex : TSFFList index                      */
/*               | [in] NumOfBeforeTriggeredRecord :                        */
/*               |        Number of before time series freeze frame.        */
/*               | [out] FreezeFrameRecordPtr :                             */
/*               |        temporary area pointer of Udm FreezeFrameRecord   */
/*               | [out] TSFreezeFrameStoredCntPtr :                        */
/*               |        Counter of valid time series freeze frame data    */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/*   v5-8-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmTSFFDMng_VerifiedBeforeTSFFD
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,     /* [PRMCHK:CALLER] */
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TSFFListIndex,              /* [PRMCHK:CALLER] */
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) NumOfBeforeTriggeredRecord,
    P2CONST( Dem_UdmFreezeFrameRecordMngType, AUTOMATIC, DEM_VAR_NO_INIT  ) FreezeFrameRecordPtr,
    P2VAR( Dem_u16_TSFFDIndexType, AUTOMATIC, AUTOMATIC ) TSFreezeFrameStoredCntPtr
)
{
    VAR( Dem_UdmFreezeFrameRecordMngType, AUTOMATIC ) udmTSFFRecord;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) tsFFRecStartIndex;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) beforeTSFFRecEndIndex;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) tsFFRecIndex;
    VAR( boolean, AUTOMATIC ) existStoredTSFFDFlg;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) verifyNGIndex;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) beforeTSFFStoredCnt;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetTSFFD;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVerifyRecord;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_OK;

    if( NumOfBeforeTriggeredRecord > (Dem_u08_NumOfTSFFType)0U )
    {
        tsFFRecStartIndex = Dem_TimeSeriesFreezeFrameTable[TSFFListIndex].DemStartIndex;                /* [GUDCHK:CALLER]TSFFListIndex */
        beforeTSFFRecEndIndex = ( tsFFRecStartIndex + NumOfBeforeTriggeredRecord ) - (Dem_u16_TSFFDIndexType)1U;

        verifyNGIndex = DEM_TSFFDINDEX_INVALID;
        existStoredTSFFDFlg = (boolean)FALSE;
        beforeTSFFStoredCnt = *TSFreezeFrameStoredCntPtr;

        for( tsFFRecIndex = tsFFRecStartIndex; tsFFRecIndex <= beforeTSFFRecEndIndex; tsFFRecIndex++ )                          /* [GUD:for]tsFFRecIndex */
        {
            retGetTSFFD = Dem_UdmTSFFDMng_GetTimeSeriesFreezeFrameRecord( UdmGroupKindIndex, tsFFRecIndex, &udmTSFFRecord );    /* [GUDCHK:CALLER]UdmGroupKindIndex */
            if( retGetTSFFD == DEM_IRT_OK )
            {
                if( udmTSFFRecord.RecordStatus == DEM_FFD_STORED )
                {
                    retVerifyRecord = Dem_UdmTSFFDMng_CheckConsistency( UdmEventIndex, UdmGroupKindIndex, tsFFRecIndex, &udmTSFFRecord, FreezeFrameRecordPtr ); /* [GUDCHK:CALLER]UdmGroupKindIndex */
                    if( retVerifyRecord == DEM_IRT_OK )
                    {
                        existStoredTSFFDFlg = (boolean)TRUE;
                        *TSFreezeFrameStoredCntPtr = *TSFreezeFrameStoredCntPtr + (Dem_u16_TSFFDIndexType)1U;
                        Dem_UdmTSFFDNvMStatus[ UdmGroupKindIndex ].DemUdmTSFFDNvMStatusPtr[ tsFFRecIndex ] = DEM_RECMNGCMN_NVM_STS_NON_TARGET;      /* [GUDCHK:CALLER]UdmGroupKindIndex *//* [GUD]tsFFRecIndex *//* [ARYCHK] Dem_UdmTimeSeriesFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDRecordNum / 1 / tsFFRecIndex *//* [ARYDESC] The registered data size of Dem_UdmTSFFDNvMStatus[ UdmGroupKindIndex ].DemUdmTSFFDNvMStatusPtr is the same as Dem_UdmTimeSeriesFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDRecordNum */
                    }
                    else
                    {
                        verifyNGIndex = tsFFRecIndex;
                    }
                }
                else
                {
                    if( existStoredTSFFDFlg == (boolean)TRUE )
                    {
                        verifyNGIndex = tsFFRecIndex;
                    }
                }

                if( verifyNGIndex != DEM_TSFFDINDEX_INVALID )
                {
                    retVal = DEM_IRT_NG;
                    break;
                }
            }
        }

        if( retVal == DEM_IRT_NG )
        {
            /* revert before TSFFD NvMstatus to not verified status */
            for( tsFFRecIndex = tsFFRecStartIndex; tsFFRecIndex < verifyNGIndex; tsFFRecIndex++ )                                           /* [GUD:for]tsFFRecIndex */
            {
                Dem_UdmTSFFDNvMStatus[ UdmGroupKindIndex ].DemUdmTSFFDNvMStatusPtr[ tsFFRecIndex ] = DEM_RECMNGCMN_NVM_STS_NOT_VERIFIED;    /* [GUDCHK:CALLER]UdmGroupKindIndex *//* [GUD]tsFFRecIndex *//* [ARYCHK] Dem_UdmTimeSeriesFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDRecordNum / 1 / tsFFRecIndex */
            }
            /* revert counter of freese frame */
            *TSFreezeFrameStoredCntPtr = beforeTSFFStoredCnt;
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_UdmTSFFDMng_VerifiedAfterTSFFD                       */
/* Description   | Verifies Udm after TSFFD data.                           */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmEventIndex : Udm Event index.                    */
/*               | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/*               | [in] TSFFListIndex : TSFFList index                      */
/*               | [in] NumOfBeforeTriggeredRecord :                        */
/*               |        Number of before time series freeze frame.        */
/*               | [out] FreezeFrameRecordPtr :                             */
/*               |        temporary area pointer of Udm FreezeFrameRecord   */
/*               | [out] TSFreezeFrameStoredCntPtr :                        */
/*               |        Counter of valid time series freeze frame data    */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmTSFFDMng_VerifiedAfterTSFFD
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,     /* [PRMCHK:CALLER] */
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TSFFListIndex,              /* [PRMCHK:CALLER] */
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) NumOfBeforeTriggeredRecord,
    P2CONST( Dem_UdmFreezeFrameRecordMngType, AUTOMATIC, DEM_VAR_NO_INIT  ) FreezeFrameRecordPtr,
    P2VAR( Dem_u16_TSFFDIndexType, AUTOMATIC, AUTOMATIC ) TSFreezeFrameStoredCntPtr
)
{
    VAR( Dem_UdmFreezeFrameRecordMngType, AUTOMATIC ) udmTSFFRecord;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) afterTSFFRecStartIndex;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) tsFFRecEndIndex;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) tsFFRecIndex;
    VAR( boolean, AUTOMATIC ) loopEndFlg;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetTSFFD;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVerifyRecord;

    afterTSFFRecStartIndex = Dem_TimeSeriesFreezeFrameTable[TSFFListIndex].DemStartIndex + NumOfBeforeTriggeredRecord;      /* [GUDCHK:CALLER]TSFFListIndex */
    tsFFRecEndIndex = Dem_TimeSeriesFreezeFrameTable[TSFFListIndex].DemEndIndex;                                            /* [GUDCHK:CALLER]TSFFListIndex */

    loopEndFlg = (boolean)FALSE;

    for( tsFFRecIndex = afterTSFFRecStartIndex; tsFFRecIndex <= tsFFRecEndIndex; tsFFRecIndex++ )                           /* [GUD:for]tsFFRecIndex */
    {
        retGetTSFFD = Dem_UdmTSFFDMng_GetTimeSeriesFreezeFrameRecord( UdmGroupKindIndex, tsFFRecIndex, &udmTSFFRecord );    /* [GUDCHK:CALLER]UdmGroupKindIndex *//* [GUD]tsFFRecIndex */
        if( retGetTSFFD == DEM_IRT_OK )
        {
            if( udmTSFFRecord.RecordStatus == DEM_FFD_STORED )
            {
                retVerifyRecord = Dem_UdmTSFFDMng_CheckConsistency( UdmEventIndex, UdmGroupKindIndex, tsFFRecIndex, &udmTSFFRecord, FreezeFrameRecordPtr ); /* [GUDCHK:CALLER]UdmGroupKindIndex *//* [GUD]tsFFRecIndex */
                if( retVerifyRecord == DEM_IRT_OK )
                {
                    *TSFreezeFrameStoredCntPtr = *TSFreezeFrameStoredCntPtr + (Dem_u16_TSFFDIndexType)1U;
                    Dem_UdmTSFFDNvMStatus[ UdmGroupKindIndex ].DemUdmTSFFDNvMStatusPtr[ tsFFRecIndex ] = DEM_RECMNGCMN_NVM_STS_NON_TARGET;  /* [GUDCHK:CALLER]UdmGroupKindIndex *//* [GUD]tsFFRecIndex *//* [ARYCHK] Dem_UdmTimeSeriesFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDRecordNum / 1 / tsFFRecIndex *//* [ARYDESC] The registered data size of Dem_UdmTSFFDNvMStatus[ UdmGroupKindIndex ].DemUdmTSFFDNvMStatusPtr is the same as Dem_UdmTimeSeriesFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDRecordNum */
                }
                else
                {
                    loopEndFlg = (boolean)TRUE;
                }
            }
            else
            {
                loopEndFlg = (boolean)TRUE;
            }

            if( loopEndFlg == (boolean)TRUE  )
            {
                break;
            }
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_UdmTSFFDMng_CheckConsistency                         */
/* Description   | Verifies Udm TSFFD data.                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmEventIndex : Udm Event index.                    */
/*               | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/*               | [in] TimeSeriesFreezeFrameIndex :                        */
/*               |        The Time series freeze frame record index         */
/*               | [out] UdmTSFFRecordPtr :                                 */
/*               |        temporary area pointer of Time series freeze      */
/*               |        frame record Record                               */
/*               | [out] FreezeFrameRecordPtr :                             */
/*               |        temporary area pointer of Udm FreezeFrameRecord   */
/* Return Value  | Dem_u08_InternalReturnType :                             */
/*               |       DEM_IRT_OK  : This FFDRecord is consistency.       */
/*               |       DEM_IRT_NG  : This FFDRecord is inconsistency.     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-8-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmTSFFDMng_CheckConsistency
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,         /* [PRMCHK:CALLER] */
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex,
    P2CONST( Dem_UdmFreezeFrameRecordMngType, AUTOMATIC, AUTOMATIC ) UdmTSFFRecordPtr,
    P2CONST( Dem_UdmFreezeFrameRecordMngType, AUTOMATIC, DEM_VAR_NO_INIT ) FreezeFrameRecordPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCheckOneRecord;

    retVal = DEM_IRT_NG;

    retCheckOneRecord = Dem_UdmTSFFDMng_CheckConsistencyOneRecordData( UdmGroupKindIndex, TimeSeriesFreezeFrameIndex ); /* [GUDCHK:CALLER]UdmGroupKindIndex */

    if( retCheckOneRecord == DEM_IRT_OK )
    {
        retVal = Dem_UdmTSFFDMng_CheckConsistencyWithTriggerFFDRecord( UdmEventIndex, UdmGroupKindIndex, TimeSeriesFreezeFrameIndex, UdmTSFFRecordPtr, FreezeFrameRecordPtr );  /* [GUDCHK:CALLER]UdmGroupKindIndex */
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_UdmTSFFDMng_CheckConsistencyOneRecordData            */
/* Description   | Verifies Udm TSFFD data.                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/*               | [in] TimeSeriesFreezeFrameIndex :                        */
/*               |        The Time series freeze frame record index         */
/* Return Value  | Dem_u08_InternalReturnType :                             */
/*               |       DEM_IRT_OK  : This FFDRecord is consistency.       */
/*               |       DEM_IRT_NG  : This FFDRecord is inconsistency.     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmTSFFDMng_CheckConsistencyOneRecordData
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,     /* [PRMCHK:CALLER] */
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex
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

    Dem_UdmTSFFDMng_GetFFDConsistencyInfo( UdmGroupKindIndex, TimeSeriesFreezeFrameIndex, &firstBlockCId, &lastBlockCId, &firstBlockUdmEventIndex, &lastBlockUdmEventIndex );   /* [GUDCHK:CALLER]UdmGroupKindIndex */

    if( firstBlockUdmEventIndex == lastBlockUdmEventIndex )
    {
        if( firstBlockCId == lastBlockCId )
        {
            retVal = Dem_UdmTSFFDMng_VerifyChecksum( UdmGroupKindIndex, TimeSeriesFreezeFrameIndex );   /* [GUDCHK:CALLER]UdmGroupKindIndex */
        }
    }

    return retVal;
}


#if ( DEM_FF_CHECKSUM_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_UdmTSFFDMng_VerifyChecksum                           */
/* Description   | verify checksum of UdmTSFFD record                       */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmGroupKindIndex                                   */
/*               |        Index of user defined memory table                */
/*               | [in] TimeSeriesFreezeFrameIndex :                        */
/*                        The Time series freeze frame record index         */
/* Return Value  | Dem_u08_InternalReturnType :                             */
/*               |       DEM_IRT_OK  : This checksum is consistency.        */
/*               |       DEM_IRT_NG  : This checksum is inconsistency.      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmTSFFDMng_VerifyChecksum
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex
)
{
    P2CONST( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) udmTSFFRecordDataPtr;
    VAR( Dem_u16_FFCheckSumType, AUTOMATIC ) registeredChecksum;
    VAR( Dem_u16_FFCheckSumType, AUTOMATIC ) calculatedChecksum;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) tsFFDMaxLength;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posDataStart;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;
    udmTSFFRecordDataPtr = ( P2CONST( uint8, TYPEDEF, DEM_VAR_SAVED_ZONE ) )Dem_UdmTSFFDMng_GetTimeSeriesFreezeFrameRecordDataPtr( UdmGroupKindIndex, TimeSeriesFreezeFrameIndex ); /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/TimeSeriesFreezeFrameIndex/udmTSFFRecordDataPtr */
    if( udmTSFFRecordDataPtr != NULL_PTR )                                          /* [GUD:if]udmTSFFRecordDataPtr */
    {
        tsFFDMaxLength = Dem_UdmTimeSeriesFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDMaxLength;    /* [GUD]UdmGroupKindIndex */
        posDataStart = Dem_UdmTimeSeriesFreezeFrameDataPosTable[UdmGroupKindIndex].DataStart;           /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posDataStart */

        /*  check available data of Dem_UdmTimeSeriesFreezeFrameDataPosTable[]    */
        if ( posDataStart != DEM_FFDSTOREDINDEX_INVALID )
        {
            registeredChecksum = Dem_UdmTSFFDMng_GetChecksum( UdmGroupKindIndex, TimeSeriesFreezeFrameIndex );      /* [GUD]UdmGroupKindIndex */
            calculatedChecksum = Dem_UtlMem_Checksum( &udmTSFFRecordDataPtr[posDataStart], tsFFDMaxLength );        /* [GUD]udmTSFFRecordDataPtr *//* [GUD]posDataStart *//* [ARYCHK] Dem_UdmTimeSeriesFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posDataStart */

            if( registeredChecksum == calculatedChecksum )
            {
                retVal = DEM_IRT_OK;
            }
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_UdmTSFFDMng_GetChecksum                              */
/* Description   | get checksum in FFD record                               */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmGroupKindIndex                                   */
/*               |        Index of user defined memory table                */
/*               | [in] TimeSeriesFreezeFrameIndex :                        */
/*                        The Time series freeze frame record index         */
/* Return Value  | uin16 :                                                  */
/*               |       The checksum value                                 */
/*               |       DEM_IRT_NG  : This checksum is inconsistency.      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u16_FFCheckSumType, DEM_CODE ) Dem_UdmTSFFDMng_GetChecksum
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex
)
{
    P2CONST( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) udmTSFFRecordDataPtr;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posChecksumUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posChecksumLower;
    VAR( uint8, AUTOMATIC ) checksumUpper;
    VAR( uint8, AUTOMATIC ) checksumLower;
    VAR( Dem_u16_FFCheckSumType, AUTOMATIC ) checksum;

    checksum    =   (Dem_u16_FFCheckSumType)0U;

    udmTSFFRecordDataPtr = ( P2CONST( uint8, TYPEDEF, DEM_VAR_SAVED_ZONE ) )Dem_UdmTSFFDMng_GetTimeSeriesFreezeFrameRecordDataPtr( UdmGroupKindIndex, TimeSeriesFreezeFrameIndex ); /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/TimeSeriesFreezeFrameIndex/udmTSFFRecordDataPtr */

    if( udmTSFFRecordDataPtr != NULL_PTR )                                                  /* [GUD:if]udmTSFFRecordDataPtr */
    {
        posChecksumUpper = Dem_UdmTimeSeriesFreezeFrameDataPosTable[UdmGroupKindIndex].ChecksumUpper;   /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posChecksumUpper */
        posChecksumLower = Dem_UdmTimeSeriesFreezeFrameDataPosTable[UdmGroupKindIndex].ChecksumLower;   /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posChecksumLower */

        /*  check available data of Dem_UdmTimeSeriesFreezeFrameDataPosTable[]    */
        if ( posChecksumUpper != DEM_FFDSTOREDINDEX_INVALID )
        {
            checksumUpper = (uint8)udmTSFFRecordDataPtr[posChecksumUpper];                  /* [GUD]udmTSFFRecordDataPtr *//* [GUD]posChecksumUpper *//* [ARYCHK] Dem_UdmTimeSeriesFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posChecksumUpper */
            checksumLower = (uint8)udmTSFFRecordDataPtr[posChecksumLower];                  /* [GUD]udmTSFFRecordDataPtr *//* [GUD]posChecksumLower *//* [ARYCHK] Dem_UdmTimeSeriesFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posChecksumLower */

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
/*               | [in] TimeSeriesFreezeFrameIndex :                        */
/*                        The Time series freeze frame record index         */
/* Return Value  | Dem_u08_InternalReturnType :                             */
/*               |       DEM_IRT_OK  : This checksum is consistency.        */
/*               |       DEM_IRT_NG  : This checksum is inconsistency.      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmTSFFDMng_VerifyChecksum
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,            /* MISRA DEVIATION */
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex            /* MISRA DEVIATION */
)
{
    return DEM_IRT_OK;
}
#endif /* ( DEM_FF_CHECKSUM_SUPPORT == STD_OFF ) */


/****************************************************************************/
/* Function Name | Dem_DataMng_GetFFDConsistencyInfo                        */
/* Description   | check consistency of FFD record                          */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmGroupKindIndex                                   */
/*               | [in] TimeSeriesFreezeFrameIndex :                        */
/*                        The Udm Time series freeze frame record index     */
/*               | [out] FirstBlockCIdPtr :                                 */
/*               |        The pointer of ConsistencyId of first block       */
/*               | [out] FirstBlockCIdPtr :                                 */
/*               |        The pointer of ConsistencyId of last block        */
/*               | [out] FirstBlockUdmEventIndexPtr :                       */
/*               |        The pointer of UdmEventIndex of first block       */
/*               | [out] LastBlockUdmEventIndexPtr :                        */
/*               |        The pointer of UdmEventIndex of last block        */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmTSFFDMng_GetFFDConsistencyInfo
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex,
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) FirstBlockCIdPtr,
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) LastBlockCIdPtr,
    P2VAR( Dem_u16_UdmEventIndexType, AUTOMATIC, AUTOMATIC ) FirstBlockUdmEventIndexPtr,
    P2VAR( Dem_u16_UdmEventIndexType, AUTOMATIC, AUTOMATIC ) LastBlockUdmEventIndexPtr
)
{
    P2CONST( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) udmTSFFRecordDataPtr;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstCid;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posLastCid;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) firstUdmEventIndex;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) lastUdmEventIndex;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstUdmEventIndexUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstUdmEventIndexLower;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posLastUdmEventIndexUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posLastUdmEventIndexLower;

    udmTSFFRecordDataPtr = ( P2CONST( uint8, TYPEDEF, DEM_VAR_SAVED_ZONE ) )Dem_UdmTSFFDMng_GetTimeSeriesFreezeFrameRecordDataPtr( UdmGroupKindIndex, TimeSeriesFreezeFrameIndex ); /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/TimeSeriesFreezeFrameIndex/udmTSFFRecordDataPtr */

    if ( udmTSFFRecordDataPtr != NULL_PTR )                                         /* [GUD:if]udmTSFFRecordDataPtr */
    {
        posFirstCid = Dem_UdmTimeSeriesFreezeFrameDataPosTable[UdmGroupKindIndex].FirstCID;                                 /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posFirstCid */
        posLastCid = Dem_UdmTimeSeriesFreezeFrameDataPosTable[UdmGroupKindIndex].LastCID;                                   /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posLastCid  */
        posFirstUdmEventIndexUpper = Dem_UdmTimeSeriesFreezeFrameDataPosTable[UdmGroupKindIndex].FirstUdmEventIndexUpper;   /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posFirstUdmEventIndexUpper */
        posFirstUdmEventIndexLower = Dem_UdmTimeSeriesFreezeFrameDataPosTable[UdmGroupKindIndex].FirstUdmEventIndexLower;   /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posFirstUdmEventIndexLower */
        posLastUdmEventIndexUpper = Dem_UdmTimeSeriesFreezeFrameDataPosTable[UdmGroupKindIndex].LastUdmEventIndexUpper;     /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posLastUdmEventIndexUpper  */
        posLastUdmEventIndexLower = Dem_UdmTimeSeriesFreezeFrameDataPosTable[UdmGroupKindIndex].LastUdmEventIndexLower;     /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posLastUdmEventIndexLower  */

        /*  check available data of Dem_UdmTimeSeriesFreezeFrameDataPosTable[]    */
        if ( posFirstCid != DEM_FFDSTOREDINDEX_INVALID )
        {
            *FirstBlockCIdPtr = (Dem_u08_ConsistencyIdType)udmTSFFRecordDataPtr[posFirstCid];           /* [GUD]udmTSFFRecordDataPtr *//* [GUD]posFirstCid *//* [ARYCHK] Dem_UdmTimeSeriesFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posFirstCid */
            *LastBlockCIdPtr = (Dem_u08_ConsistencyIdType)udmTSFFRecordDataPtr[posLastCid];             /* [GUD]udmTSFFRecordDataPtr *//* [GUD]posLastCid *//* [ARYCHK] Dem_UdmTimeSeriesFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posLastCid */
            firstUdmEventIndex = (Dem_u16_UdmEventIndexType)Dem_UtlMem_ConvertByteData( udmTSFFRecordDataPtr[posFirstUdmEventIndexUpper], udmTSFFRecordDataPtr[posFirstUdmEventIndexLower] );   /* [GUD]udmTSFFRecordDataPtr *//* [GUD]posFirstUdmEventIndexUpper *//* [GUD]posFirstUdmEventIndexLower *//* [ARYCHK] Dem_UdmTimeSeriesFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posFirstUdmEventIndexUpper *//* [ARYCHK] Dem_UdmTimeSeriesFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posFirstUdmEventIndexLower */
            *FirstBlockUdmEventIndexPtr = firstUdmEventIndex;
            lastUdmEventIndex = (Dem_u16_UdmEventIndexType)Dem_UtlMem_ConvertByteData( udmTSFFRecordDataPtr[posLastUdmEventIndexUpper], udmTSFFRecordDataPtr[posLastUdmEventIndexLower] );  /* [GUD]udmTSFFRecordDataPtr *//* [GUD]posLastUdmEventIndexUpper *//* [GUD]posLastUdmEventIndexLower *//* [ARYCHK] Dem_UdmTimeSeriesFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posLastUdmEventIndexUpper *//* [ARYCHK] Dem_UdmTimeSeriesFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posLastUdmEventIndexLower */
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


/****************************************************************************/
/* Function Name | Dem_UdmTSFFDMng_CheckConsistencyWithTriggerFFDRecord     */
/* Description   | Verifies Udm TSFFD data.                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmEventIndex : Udm Event index.                    */
/*               | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/*               | [in] TimeSeriesFreezeFrameIndex : TsffList index         */
/*               | [out] UdmTSFFRecordPtr :                                 */
/*               |        temporary area pointer of Time series freeze      */
/*               |        frame record Record                               */
/*               | [out] FreezeFrameRecordPtr :                             */
/*               |        temporary area pointer of Udm FreezeFrameRecord   */
/* Return Value  | Dem_u08_InternalReturnType :                             */
/*               |       DEM_IRT_OK  : This FFDRecord is consistency.       */
/*               |       DEM_IRT_NG  : This FFDRecord is inconsistency.     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-8-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmTSFFDMng_CheckConsistencyWithTriggerFFDRecord
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,                     /* [PRMCHK:CALLER] */
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex,
    P2CONST( Dem_UdmFreezeFrameRecordMngType, AUTOMATIC, AUTOMATIC ) UdmTSFFRecordPtr,
    P2CONST( Dem_UdmFreezeFrameRecordMngType, AUTOMATIC, DEM_VAR_NO_INIT ) FreezeFrameRecordPtr
)
{
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) firstBlockUdmEventIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;

    Dem_UdmTSFFDMng_GetEventIndex( UdmGroupKindIndex, TimeSeriesFreezeFrameIndex, &firstBlockUdmEventIndex );   /* [GUDCHK:CALLER]UdmGroupKindIndex */

    if( firstBlockUdmEventIndex == UdmEventIndex )
    {
        if( UdmTSFFRecordPtr->OccurrenceOrder == FreezeFrameRecordPtr->OccurrenceOrder )
        {
            if( UdmTSFFRecordPtr->CidUdmFreezeFrameRecords == FreezeFrameRecordPtr->CidUdmFreezeFrameRecords )
            {
                retVal = DEM_IRT_OK;
            }
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_UdmTSFFDMng_GetEventIndex                            */
/* Description   | get event index of TSFFD record                          */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmGroupKindIndex                                   */
/*               |        Index of user defined memory table                */
/*               | [in] TimeSeriesFreezeFrameIndex :                        */
/*                        The Time series freeze frame record index         */
/*               | [out] FirstBlockUdmEventIndexPtr :                       */
/*               |        The pointer of UdmEventIndex of first block       */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmTSFFDMng_GetEventIndex
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex,
    P2VAR( Dem_u16_UdmEventIndexType, AUTOMATIC, AUTOMATIC ) FirstBlockUdmEventIndexPtr
)
{
    P2CONST( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) udmTSFFRecordDataPtr;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) firstUdmEventIndex;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstUdmEventIndexUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstUdmEventIndexLower;

    udmTSFFRecordDataPtr = ( P2CONST( uint8, TYPEDEF, DEM_VAR_SAVED_ZONE ) )Dem_UdmTSFFDMng_GetTimeSeriesFreezeFrameRecordDataPtr( UdmGroupKindIndex, TimeSeriesFreezeFrameIndex ); /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/TimeSeriesFreezeFrameIndex/udmTSFFRecordDataPtr */
    if ( udmTSFFRecordDataPtr != NULL_PTR )                                         /* [GUD:if]udmTSFFRecordDataPtr */
    {
        posFirstUdmEventIndexUpper = Dem_UdmTimeSeriesFreezeFrameDataPosTable[UdmGroupKindIndex].FirstUdmEventIndexUpper;   /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posFirstUdmEventIndexUpper */
        posFirstUdmEventIndexLower = Dem_UdmTimeSeriesFreezeFrameDataPosTable[UdmGroupKindIndex].FirstUdmEventIndexLower;   /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posFirstUdmEventIndexLower */

        /*  check available data of Dem_UdmTimeSeriesFreezeFrameDataPosTable[]    */
        if ( posFirstUdmEventIndexUpper != DEM_FFDSTOREDINDEX_INVALID )
        {
            firstUdmEventIndex = (Dem_u16_UdmEventIndexType)Dem_UtlMem_ConvertByteData( udmTSFFRecordDataPtr[posFirstUdmEventIndexUpper], udmTSFFRecordDataPtr[posFirstUdmEventIndexLower] );   /* [GUD]udmTSFFRecordDataPtr *//* [GUD]posFirstUdmEventIndexUpper *//* [GUD]posFirstUdmEventIndexLower *//* [ARYCHK] Dem_UdmTimeSeriesFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posFirstUdmEventIndexUpper *//* [ARYCHK] Dem_UdmTimeSeriesFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posFirstUdmEventIndexLower */
            *FirstBlockUdmEventIndexPtr = firstUdmEventIndex;
        }
        else
        {
            *FirstBlockUdmEventIndexPtr = DEM_UDMEVENTINDEX_INVALID;
        }
    }
    else
    {
        *FirstBlockUdmEventIndexPtr = DEM_UDMEVENTINDEX_INVALID;
    }
    return;
}


#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_UdmTSFFDMng_SetRecordMirror                          */
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
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmTSFFDMng_SetRecordMirror
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
)
{
    P2CONST( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) udmTSFFRecordDataPtr;
    P2VAR( uint8, AUTOMATIC, DEM_VAR_NO_INIT ) tmpUdmTSFFDMirrorDataPtr;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) udmTsffdStorageFormatsize;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) udmTsffdDataIndex;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) udmTsffTotalTimeseriesFFRecordNum;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;

    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;
    udmGroupKindIndex    = ( Dem_u16_UdmDemMemKindIndexType )RecordFieldIndex;

    if( udmGroupKindIndex < userDefinedMemoryNum )                                          /* [GUD:if]UdmGroupKindIndex */
    {
        udmTsffTotalTimeseriesFFRecordNum = Dem_UdmTimeSeriesFreezeFrameRecordTable[udmGroupKindIndex].DemFFDRecordNum;     /* [GUD]udmGroupKindIndex */
        udmTsffdStorageFormatsize = Dem_UdmTimeSeriesFreezeFrameRecordTable[ udmGroupKindIndex ].DemFFDStoredFormatSize;    /* [GUD]udmGroupKindIndex */

        if( BlockMirrorPtr->RecordDataOffset == (Dem_u16_RecordDataSizeType)0U )
        {
            if( BlockMirrorPtr->RecordIndex < udmTsffTotalTimeseriesFFRecordNum )
            {
                tmpUdmTSFFDMirrorDataPtr = Dem_UdmTSFFRecordNvMTable[udmGroupKindIndex].DemTmpUdmTSFFDMirrorDataPtr;        /* [GUD]udmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:udmGroupKindIndex]tmpUdmTSFFDMirrorDataPtr */
                udmTSFFRecordDataPtr = ( P2CONST( uint8, TYPEDEF, DEM_VAR_SAVED_ZONE ) )Dem_UdmTSFFDMng_GetTimeSeriesFreezeFrameRecordDataPtr( udmGroupKindIndex, BlockMirrorPtr->RecordIndex );    /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/TimeSeriesFreezeFrameIndex/udmTSFFRecordDataPtr */

                if( udmTSFFRecordDataPtr != NULL_PTR )                                          /* [GUD:if]udmTSFFRecordDataPtr */
                {
                    /* copy data to mirror area. */
                    Dem_UtlMem_CopyMemory( &tmpUdmTSFFDMirrorDataPtr[0], &(udmTSFFRecordDataPtr[0]), udmTsffdStorageFormatsize );   /* [GUD]tmpUdmTSFFDMirrorDataPtr *//* [GUD]udmTSFFRecordDataPtr *//* [ARYCHK] udmTsffdStorageFormatsize / 1 / 0 *//* [ARYDESC] The registered data size of Dem_UdmTSFFRecordNvMTable[UdmGroupKindIndex].DemTmpUdmTSFFDMirrorDataPtr is the same as Dem_UdmTimeSeriesFreezeFrameRecordTable[ UdmGroupKindIndex ].DemFFDStoredFormatSize *//* [ARYCHK] udmTsffdStorageFormatsize / 1 / 0 */
                }
            }
        }

        udmTsffdDataIndex = Dem_UdmTSFFRecordNvMTable[udmGroupKindIndex].DemUdmTSFFDRecordNvBlockSize * BlockMirrorPtr->RecordDataOffset;   /* [GUD]udmGroupKindIndex */
        if( udmTsffdDataIndex < udmTsffdStorageFormatsize )
        {
            BlockMirrorPtr->MirrorPtr = &(Dem_UdmTSFFRecordNvMTable[udmGroupKindIndex].DemTmpUdmTSFFDMirrorDataPtr[ udmTsffdDataIndex ]);   /* [GUD]udmGroupKindIndex */    /* [GUD]udmTsffdDataIndex *//* [ARYCHK] udmTsffdStorageFormatsize / 1 / udmTsffdDataIndex *//* [ARYDESC] The registered data size of Dem_UdmTSFFRecordNvMTable[UdmGroupKindIndex].DemTmpUdmTSFFDMirrorDataPtr is the same as Dem_UdmTimeSeriesFreezeFrameRecordTable[ UdmGroupKindIndex ].DemFFDStoredFormatSize */
        }
    }

    return;
}

#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */


/****************************************************************************/
/* Function Name | Dem_UdmTSFFDMng_DataVerify                               */
/* Description   | Verifies Udm TSFFD data.                                 */
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
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmTSFFDMng_DataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex     /* MISRA DEVIATION */
)
{
    /* No Process */
    return DEM_IRT_OK;
}


/****************************************************************************/
/* Function Name | Dem_UdmTSFFDMng_ClearAllNotVerifiedRecord                */
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
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmTSFFDMng_ClearAllNotVerifiedRecord
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    P2VAR( Dem_u16_RecordIndexType, AUTOMATIC, AUTOMATIC ) ClearRecordIndexPtr,
    P2VAR( Dem_u32_TotalRecordNumType, AUTOMATIC, AUTOMATIC ) RestOfProcessableNumPtr
)
{
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) udmTsffIndex;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) udmTsffTotalTimeseriesFFRecordNum;
    VAR( Dem_u32_TotalRecordNumType, AUTOMATIC ) loopCount;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    loopCount = (Dem_u16_TSFFDIndexType)0U;
    retVal = DEM_IRT_OK;

    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;
    udmGroupKindIndex = ( Dem_u16_UdmDemMemKindIndexType)RecordFieldIndex;

    if( udmGroupKindIndex < userDefinedMemoryNum )                                          /* [GUD:if]UdmGroupKindIndex */
    {
        udmTsffTotalTimeseriesFFRecordNum = Dem_UdmTimeSeriesFreezeFrameRecordTable[udmGroupKindIndex].DemFFDRecordNum; /* [GUD]udmGroupKindIndex */
        for( udmTsffIndex = (Dem_u16_TSFFDIndexType)( *ClearRecordIndexPtr ); udmTsffIndex < udmTsffTotalTimeseriesFFRecordNum; udmTsffIndex++ )
        {
            if( loopCount < *RestOfProcessableNumPtr )
            {
                if( Dem_UdmTSFFDNvMStatus[ udmGroupKindIndex ].DemUdmTSFFDNvMStatusPtr[ udmTsffIndex ] == DEM_RECMNGCMN_NVM_STS_NOT_VERIFIED )  /* [GUD]udmGroupKindIndex *//* [GUD]udmTsffIndex *//* [ARYCHK] udmTsffTotalTimeseriesFFRecordNum / 1 / udmTsffIndex *//* [ARYDESC] The registered data size of Dem_UdmTSFFDNvMStatus[ udmGroupKindIndex ].DemUdmTSFFDNvMStatusPtr is the same as Dem_UdmTimeSeriesFreezeFrameRecordTable[udmGroupKindIndex].DemFFDRecordNum */
                {
                    (void)Dem_UdmTSFFDMng_ClearTimeSeriesFreezeFrameRecord( udmGroupKindIndex, udmTsffIndex );   /* no return check required */ /* [GUD]udmGroupKindIndex */

                    Dem_UdmTSFFDNvMStatus[ udmGroupKindIndex ].DemUdmTSFFDNvMStatusPtr[ udmTsffIndex ] = DEM_RECMNGCMN_NVM_STS_NON_TARGET;      /* [GUD]udmGroupKindIndex *//* [GUD]udmTsffIndex *//* [ARYCHK] udmTsffTotalTimeseriesFFRecordNum / 1 / udmTsffIndex *//* [ARYDESC] The registered data size of Dem_UdmTSFFDNvMStatus[ udmGroupKindIndex ].DemUdmTSFFDNvMStatusPtr is the same as Dem_UdmTimeSeriesFreezeFrameRecordTable[udmGroupKindIndex].DemFFDRecordNum */
                }
                loopCount = loopCount + (Dem_u32_TotalRecordNumType)1U;
            }
            else
            {
                *ClearRecordIndexPtr = (Dem_u16_RecordIndexType)udmTsffIndex;
                retVal = DEM_IRT_PENDING;
                break;
            }
        }

        if( udmTsffIndex >= udmTsffTotalTimeseriesFFRecordNum )
        {
            *RestOfProcessableNumPtr = ( *RestOfProcessableNumPtr ) - loopCount;  /* no wrap around */
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_UdmTSFFDMng_SetBeforeTimeSeriesFreezeFrameRecord     */
/* Description   | Set the captured FreezeFrame data, fault occurrence ind- */
/*               | ex, and storage status of the time series FreezeFrame r- */
/*               | ecord specified in the time series FreezeFrame record l- */
/*               | ist corresponding to the designated time series FreezeF- */
/*               | rame index.(for Dem_DataCtl subunit)                     */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        User defined memory table Index.                  */
/*               | [in] UdmFreezeFrameIndex :                               */
/*               |        Trigger FreezeFrame Index.                        */
/*               | [in] TimeSeriesFreezeFrameIndex :                        */
/*               |        Time Series FreezeFrame Index.                    */
/*               | [in] UdmEventIndex :                                     */
/*               |        The event index corresponding to the specific fa- */
/*               |        ult record.                                       */
/*               | [in] ConsistencyId :                                     */
/*               |        The Consistency ID.                               */
/*               | [in] SamplingFreezeFrameRecordPtr :                      */
/*               |        Sampling FreezeFrame Record pointer.              */
/*               |             &Dem_SamplingFreezeFrameRecordList           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmTSFFDMng_SetBeforeTimeSeriesFreezeFrameRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) UdmFreezeFrameIndex,
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex,
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId,
    P2CONST( uint8, AUTOMATIC, DEM_VAR_NO_INIT ) SamplingFreezeFrameRecordDataStartPtr
)
{
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) udmTSFFRecordDataPtr;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetFreezeFrameRecord;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindUdmTSFFD;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) tsffRecordNum;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) tsFFDMaxLength;
    VAR( Dem_UdmFreezeFrameRecordMngType, AUTOMATIC ) udmFreezeFrameRecord;
    VAR( Dem_UdmFFRMngInfoType, AUTOMATIC ) udmFFRMngInfo;


    retVal = DEM_IRT_NG;
    udmTSFFRecordDataPtr = Dem_UdmTSFFDMng_GetTimeSeriesFreezeFrameRecordDataPtr( UdmGroupKindIndex, TimeSeriesFreezeFrameIndex );  /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/TimeSeriesFreezeFrameIndex/udmTSFFRecordDataPtr */

    if( udmTSFFRecordDataPtr != NULL_PTR )                                          /* [GUD:if]udmTSFFRecordDataPtr */
    {
        tsffRecordNum = Dem_UdmTimeSeriesFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDRecordNum;             /* [GUD]UdmGroupKindIndex */

        if( TimeSeriesFreezeFrameIndex < tsffRecordNum )
        {
            retGetFreezeFrameRecord = Dem_UdmFFDMng_GetFreezeFrameRecord( UdmGroupKindIndex, UdmFreezeFrameIndex, &udmFreezeFrameRecord );  /* [GUD]UdmGroupKindIndex */
            if( retGetFreezeFrameRecord == DEM_IRT_OK )
            {
                tsFFDMaxLength = Dem_UdmTimeSeriesFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDMaxLength;    /* [GUD]UdmGroupKindIndex */

                udmFFRMngInfo.UdmEventIndex = UdmEventIndex;
                udmFFRMngInfo.CidUdmFreezeFrameRecords = udmFreezeFrameRecord.CidUdmFreezeFrameRecords;
                udmFFRMngInfo.OccurrenceOrder = udmFreezeFrameRecord.OccurrenceOrder;
                udmFFRMngInfo.RecordStatus = DEM_FFD_NOT_STORED;
                udmFFRMngInfo.OffsetOfTSFFListIndex = DEM_NUMOFTSFF_INVALID;

                /* Dealing with the writing of TSFFD outside the exclusive section */
                /* In the case of before TSFFD, save in not stored state to be temporary */
#ifndef DEM_SIT_RANGE_CHECK
                Dem_UdmFFDMng_SetCapturedFreezeFrame( &Dem_UdmTimeSeriesFreezeFrameDataPosTable[UdmGroupKindIndex], ConsistencyId, &udmFFRMngInfo, SamplingFreezeFrameRecordDataStartPtr, tsFFDMaxLength, udmTSFFRecordDataPtr );   /* [GUD]udmTSFFRecordDataPtr */ /* [GUD]UdmGroupKindIndex */
#else   /* DEM_SIT_RANGE_CHECK */
                Dem_UdmFFDMng_SetCapturedFreezeFrame( (Dem_UdmTimeSeriesFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize), &Dem_UdmTimeSeriesFreezeFrameDataPosTable[UdmGroupKindIndex], ConsistencyId, &udmFFRMngInfo, SamplingFreezeFrameRecordDataStartPtr, tsFFDMaxLength, udmTSFFRecordDataPtr );   /* [GUD]udmTSFFRecordDataPtr */ /* [GUD]UdmGroupKindIndex */
#endif  /* DEM_SIT_RANGE_CHECK */
                /* Change Dem_TSFFDNvMStatus */
                recMngCmnKindUdmTSFFD = Dem_UdmTSFFDNvMStatus[ UdmGroupKindIndex ].DemRecMngCmnKindUdmTSFFD;    /* [GUD]UdmGroupKindIndex */
                Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindUdmTSFFD, ( Dem_u16_RecordIndexType )TimeSeriesFreezeFrameIndex );
                retVal = DEM_IRT_OK;
            }
        }
        else
        {
            /* No process */
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_UdmTSFFDMng_SetAfterTimeSeriesFreezeFrameRecord      */
/* Description   | Set the captured FreezeFrame data, fault occurrence ind- */
/*               | ex, and storage status of the time series FreezeFrame r- */
/*               | ecord specified in the time series FreezeFrame record l- */
/*               | ist corresponding to the designated time series FreezeF- */
/*               | rame index.(for Dem_DataCtl subunit)                     */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        User defined memory table Index.                  */
/*               | [in] UdmFreezeFrameIndex :                               */
/*               |        Trigger FreezeFrame Index.                        */
/*               | [in] TimeSeriesFreezeFrameIndex :                        */
/*               |        Time Series FreezeFrame Index.                    */
/*               | [in] UdmEventIndex :                                     */
/*               |        The event index corresponding to the specific fa- */
/*               |        ult record.                                       */
/*               | [in] ConsistencyId :                                     */
/*               |        The Consistency ID.                               */
/*               | [in] SamplingRecordStatus :                              */
/*               |        The record status of the sampling freeze frame r- */
/*               |        ecord.                                            */
/*               | [in] SamplingFreezeFrameRecordDataStartPtr :             */
/*               |        The pointer of data start of the sampling freeze  */
/*               |        frame record.                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmTSFFDMng_SetAfterTimeSeriesFreezeFrameRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) UdmFreezeFrameIndex,
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex,
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId,
    VAR( Dem_u08_FFStoredStatusType, AUTOMATIC ) SamplingRecordStatus,
    P2CONST( uint8, AUTOMATIC, DEM_VAR_NO_INIT ) SamplingFreezeFrameRecordDataStartPtr
)
{
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) udmTSFFRecordDataPtr;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetFFtRec;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindUdmTSFFD;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) tsffRecordNum;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) tsFFDMaxLength;
    VAR( Dem_UdmFreezeFrameRecordMngType, AUTOMATIC ) udmFreezeFrameRecord;
    VAR( Dem_UdmFFRMngInfoType, AUTOMATIC ) udmFFRMngInfo;

    retVal = DEM_IRT_NG;
    udmTSFFRecordDataPtr = Dem_UdmTSFFDMng_GetTimeSeriesFreezeFrameRecordDataPtr( UdmGroupKindIndex, TimeSeriesFreezeFrameIndex );  /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/TimeSeriesFreezeFrameIndex/udmTSFFRecordDataPtr */

    if( udmTSFFRecordDataPtr != NULL_PTR )                                          /* [GUD:if]udmTSFFRecordDataPtr */
    {
        tsffRecordNum = Dem_UdmTimeSeriesFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDRecordNum;             /* [GUD]UdmGroupKindIndex */

        if( TimeSeriesFreezeFrameIndex < tsffRecordNum )
        {
            retGetFFtRec = Dem_UdmFFDMng_GetFreezeFrameRecord( UdmGroupKindIndex, UdmFreezeFrameIndex, &udmFreezeFrameRecord ); /* [GUD]UdmGroupKindIndex */
            if( retGetFFtRec == DEM_IRT_OK )
            {
                tsFFDMaxLength = Dem_UdmTimeSeriesFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDMaxLength;    /* [GUD]UdmGroupKindIndex */

                udmFFRMngInfo.UdmEventIndex = UdmEventIndex;
                udmFFRMngInfo.CidUdmFreezeFrameRecords = udmFreezeFrameRecord.CidUdmFreezeFrameRecords;
                udmFFRMngInfo.OccurrenceOrder = udmFreezeFrameRecord.OccurrenceOrder;
                udmFFRMngInfo.RecordStatus = SamplingRecordStatus;
                udmFFRMngInfo.OffsetOfTSFFListIndex = DEM_NUMOFTSFF_INVALID;

#ifndef DEM_SIT_RANGE_CHECK
                Dem_UdmFFDMng_SetCapturedFreezeFrame( &Dem_UdmTimeSeriesFreezeFrameDataPosTable[UdmGroupKindIndex], ConsistencyId, &udmFFRMngInfo, SamplingFreezeFrameRecordDataStartPtr, tsFFDMaxLength, udmTSFFRecordDataPtr );   /* [GUD]udmTSFFRecordDataPtr */ /* [GUD]UdmGroupKindIndex */
#else   /* DEM_SIT_RANGE_CHECK */
                Dem_UdmFFDMng_SetCapturedFreezeFrame( (Dem_UdmTimeSeriesFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize), &Dem_UdmTimeSeriesFreezeFrameDataPosTable[UdmGroupKindIndex], ConsistencyId, &udmFFRMngInfo, SamplingFreezeFrameRecordDataStartPtr, tsFFDMaxLength, udmTSFFRecordDataPtr );   /* [GUD]udmTSFFRecordDataPtr */ /* [GUD]UdmGroupKindIndex */
#endif  /* DEM_SIT_RANGE_CHECK */
                /* Change Dem_TSFFDNvMStatus */
                recMngCmnKindUdmTSFFD = Dem_UdmTSFFDNvMStatus[ UdmGroupKindIndex ].DemRecMngCmnKindUdmTSFFD;    /* [GUD]UdmGroupKindIndex */
                Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindUdmTSFFD, ( Dem_u16_RecordIndexType )TimeSeriesFreezeFrameIndex );
                retVal = DEM_IRT_OK;
            }
        }
        else
        {
            /* No process */
        }
    }

    return retVal;
}

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_UdmTSFFDMng_GetFFR_MngInfo                           */
/* Description   | Gets UdmFaultIndex of the FreezeFrame record from the F- */
/*               | reezeFrame record list corresponding to the specified F- */
/*               | reezeFrame index. (for Dem_DataCtl subunit)              */
/* Preconditions | The specified FreezeFrame index be within the range of - */
/*               | the FreezeFrame record list.                             */
/* Parameters    | [in] UdmGroupKindIndex                                   */
/*               |        Index of user defined memory table                */
/*               | [in] TimeSeriesFreezeFrameIndex :                        */
/*               |        The Time Series FreezeFrame index corresponding   */
/*               |        to the specific Time Series FreezeFrame record.   */
/*               | [out] TimeSeriesFreezeFrameRecordPtr :                   */
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
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmTSFFDMng_GetFFR_MngInfo
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex,
    P2VAR( Dem_UdmFreezeFrameRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) TimeSeriesFreezeFrameRecordPtr
)
{
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) udmTSFFRecordDataPtr;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndex;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstUdmEventIndexUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstUdmEventIndexLower;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posCidUdmFreezeFrameRecords;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posRecordStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;

    udmTSFFRecordDataPtr = Dem_UdmTSFFDMng_GetTimeSeriesFreezeFrameRecordDataPtr( UdmGroupKindIndex, TimeSeriesFreezeFrameIndex );  /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/TimeSeriesFreezeFrameIndex/udmTSFFRecordDataPtr */
    if( udmTSFFRecordDataPtr != NULL_PTR )                                          /* [GUD:if]udmTSFFRecordDataPtr */
    {
        posFirstUdmEventIndexUpper = Dem_UdmTimeSeriesFreezeFrameDataPosTable[UdmGroupKindIndex].FirstUdmEventIndexUpper;   /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posFirstUdmEventIndexUpper  */
        posFirstUdmEventIndexLower = Dem_UdmTimeSeriesFreezeFrameDataPosTable[UdmGroupKindIndex].FirstUdmEventIndexLower;   /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posFirstUdmEventIndexLower  */
        posCidUdmFreezeFrameRecords = Dem_UdmTimeSeriesFreezeFrameDataPosTable[UdmGroupKindIndex].CidUdmFreezeFrameRecords; /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posCidUdmFreezeFrameRecords */
        posRecordStatus = Dem_UdmTimeSeriesFreezeFrameDataPosTable[UdmGroupKindIndex].RecordStatus;                         /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posRecordStatus */

        /*  check available data of Dem_UdmTimeSeriesFreezeFrameDataPosTable[]    */
        if ( posRecordStatus != DEM_FFDSTOREDINDEX_INVALID )
        {
            udmEventIndex = (Dem_u16_UdmEventIndexType)Dem_UtlMem_ConvertByteData( udmTSFFRecordDataPtr[posFirstUdmEventIndexUpper], udmTSFFRecordDataPtr[posFirstUdmEventIndexLower] );    /* [GUD]udmTSFFRecordDataPtr *//* [GUD]posFirstUdmEventIndexUpper *//* [GUD]posFirstUdmEventIndexLower *//* [ARYCHK] Dem_UdmTimeSeriesFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posFirstUdmEventIndexUpper *//* [ARYCHK] Dem_UdmTimeSeriesFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posFirstUdmEventIndexLower */
            TimeSeriesFreezeFrameRecordPtr->UdmEventIndex = udmEventIndex;
#ifndef DEM_SIT_RANGE_CHECK
            TimeSeriesFreezeFrameRecordPtr->OccurrenceOrder = Dem_UdmFFDMng_AssembleOccurrenceOrder( &Dem_UdmTimeSeriesFreezeFrameDataPosTable[UdmGroupKindIndex], udmTSFFRecordDataPtr );  /* [GUD]udmTSFFRecordDataPtr *//* [GUD]UdmGroupKindIndex */
#else   /* DEM_SIT_RANGE_CHECK */
            TimeSeriesFreezeFrameRecordPtr->OccurrenceOrder = Dem_UdmFFDMng_AssembleOccurrenceOrder( (Dem_UdmTimeSeriesFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize), &Dem_UdmTimeSeriesFreezeFrameDataPosTable[UdmGroupKindIndex], udmTSFFRecordDataPtr );  /* [GUD]udmTSFFRecordDataPtr *//* [GUD]UdmGroupKindIndex */
#endif  /* DEM_SIT_RANGE_CHECK */
            TimeSeriesFreezeFrameRecordPtr->CidUdmFreezeFrameRecords = udmTSFFRecordDataPtr[posCidUdmFreezeFrameRecords];   /* [GUD]udmTSFFRecordDataPtr *//* [GUD]posCidUdmFreezeFrameRecords *//* [ARYCHK] Dem_UdmTimeSeriesFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posCidUdmFreezeFrameRecords */
            TimeSeriesFreezeFrameRecordPtr->RecordStatus = udmTSFFRecordDataPtr[posRecordStatus];                           /* [GUD]udmTSFFRecordDataPtr *//* [GUD]posRecordStatus *//* [ARYCHK] Dem_UdmTimeSeriesFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posRecordStatus */

            retVal = DEM_IRT_OK;
        }
    }

    return retVal;
}
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */


/****************************************************************************/
/* Function Name | Dem_UdmTSFFDMng_GetTimeSeriesFreezeFrameRecord           */
/* Description   | Gets the data body of the Time Series FreezeFrame record */
/*               | from the Time Series FreezeFrame record list correspond- */
/*               | ing to the specified UdmKind index and Time Series Free- */
/*               | zeFrame index. (for Dem_DataCtl subunit)                 */
/* Preconditions | The specified UdmKind index and Time Series FreezeFrame  */
/*               | index be within the range of the Time Series FreezeFrame */
/*               | record list.                                             */
/* Parameters    | [in] UdmGroupKindIndex                                   */
/*               |        Index of user defined memory table                */
/*               | [in] TimeSeriesFreezeFrameIndex :                        */
/*               |        The Time Series FreezeFrame index corresponding   */
/*               |        to the specific Time Series FreezeFrame record.   */
/*               | [out] TimeSeriesFreezeFrameRecordPtr :                   */
/*               |        The pointer of the Time Series FreezeFrame record */
/*               |        from DataMng corresponding to the specified Time  */
/*               |        Series FreezeFrame index.                         */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_FFStoredStatusType, DEM_CODE ) Dem_UdmTSFFDMng_GetTimeSeriesFreezeFrameRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex,
    P2VAR( Dem_UdmFreezeFrameRecordMngType, AUTOMATIC, AUTOMATIC ) TimeSeriesFreezeFrameRecordPtr
)
{
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) udmTSFFRecordDataPtr;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posCidUdmFreezeFrameRecords;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posRecordStatus;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posDataStart;

    retVal = DEM_IRT_NG;

    udmTSFFRecordDataPtr = Dem_UdmTSFFDMng_GetTimeSeriesFreezeFrameRecordDataPtr( UdmGroupKindIndex, TimeSeriesFreezeFrameIndex );  /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/TimeSeriesFreezeFrameIndex/udmTSFFRecordDataPtr */
    if( udmTSFFRecordDataPtr != NULL_PTR )                                          /* [GUD:if]udmTSFFRecordDataPtr */
    {
        posCidUdmFreezeFrameRecords = Dem_UdmTimeSeriesFreezeFrameDataPosTable[UdmGroupKindIndex].CidUdmFreezeFrameRecords; /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posCidUdmFreezeFrameRecords */
        posRecordStatus = Dem_UdmTimeSeriesFreezeFrameDataPosTable[UdmGroupKindIndex].RecordStatus;                         /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posRecordStatus */
        posDataStart = Dem_UdmTimeSeriesFreezeFrameDataPosTable[UdmGroupKindIndex].DataStart;                               /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posDataStart */

        /*  check available data of Dem_UdmTimeSeriesFreezeFrameDataPosTable[]    */
        if ( posRecordStatus != DEM_FFDSTOREDINDEX_INVALID )
        {
#ifndef DEM_SIT_RANGE_CHECK
            TimeSeriesFreezeFrameRecordPtr->OccurrenceOrder = Dem_UdmFFDMng_AssembleOccurrenceOrder( &Dem_UdmTimeSeriesFreezeFrameDataPosTable[UdmGroupKindIndex], udmTSFFRecordDataPtr );  /* [GUD]udmTSFFRecordDataPtr */ /* [GUD]UdmGroupKindIndex */
#else   /* DEM_SIT_RANGE_CHECK */
            TimeSeriesFreezeFrameRecordPtr->OccurrenceOrder = Dem_UdmFFDMng_AssembleOccurrenceOrder( (Dem_UdmTimeSeriesFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize), &Dem_UdmTimeSeriesFreezeFrameDataPosTable[UdmGroupKindIndex], udmTSFFRecordDataPtr );  /* [GUD]udmTSFFRecordDataPtr */ /* [GUD]UdmGroupKindIndex */
#endif  /* DEM_SIT_RANGE_CHECK */
            TimeSeriesFreezeFrameRecordPtr->CidUdmFreezeFrameRecords = udmTSFFRecordDataPtr[posCidUdmFreezeFrameRecords];   /* [GUD]udmTSFFRecordDataPtr *//* [GUD]posCidUdmFreezeFrameRecords *//* [ARYCHK] Dem_UdmTimeSeriesFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posCidUdmFreezeFrameRecords */
            TimeSeriesFreezeFrameRecordPtr->OffsetOfTSFFListIndex = DEM_NUMOFTSFF_INVALID;
            TimeSeriesFreezeFrameRecordPtr->RecordStatus = udmTSFFRecordDataPtr[posRecordStatus];                           /* [GUD]udmTSFFRecordDataPtr *//* [GUD]posRecordStatus *//* [ARYCHK] Dem_UdmTimeSeriesFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posRecordStatus */
            TimeSeriesFreezeFrameRecordPtr->DataPtr = &udmTSFFRecordDataPtr[posDataStart];                                  /* [GUD]udmTSFFRecordDataPtr *//* [GUD]posDataStart *//* [ARYCHK] Dem_UdmTimeSeriesFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posDataStart */

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
/* Function Name | Dem_UdmTSFFDMng_SetRecordStatus                          */
/* Description   | Set the storage status to stored from the FreezeFrame r- */
/*               | ecord list data corresponding to the designated before - */
/*               | time series FreezeFrame index.                           */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        User defined memory table Index.                  */
/*               | [in] TimeSeriesFreezeFrameIndex :                        */
/*               |        Time Series FreezeFrame Index.                    */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmTSFFDMng_SetRecordStatus
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex
)
{
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) udmTSFFRecordDataPtr;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posRecordStatus;

    udmTSFFRecordDataPtr = Dem_UdmTSFFDMng_GetTimeSeriesFreezeFrameRecordDataPtr( UdmGroupKindIndex, TimeSeriesFreezeFrameIndex );  /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/TimeSeriesFreezeFrameIndex/udmTSFFRecordDataPtr */
    if( udmTSFFRecordDataPtr != NULL_PTR )                                          /* [GUD:if]udmTSFFRecordDataPtr */
    {
        posRecordStatus = Dem_UdmTimeSeriesFreezeFrameDataPosTable[UdmGroupKindIndex].RecordStatus; /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posRecordStatus */
        /*  check available data of Dem_UdmTimeSeriesFreezeFrameDataPosTable[]    */
        if ( posRecordStatus != DEM_FFDSTOREDINDEX_INVALID )
        {
            udmTSFFRecordDataPtr[posRecordStatus] = DEM_FFD_STORED;                 /* [GUD]udmTSFFRecordDataPtr *//* [GUD]posRecordStatus *//* [ARYCHK] Dem_UdmTimeSeriesFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posRecordStatus */
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_UdmTSFFDMng_GetRecordStatus                          */
/* Description   | Get the storage status from the FreezeFrame record list- */
/*               |  data corresponding to the designated time series Freez- */
/*               | eFrame index.                                            */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        User defined memory table Index.                  */
/*               | [in] TimeSeriesFreezeFrameIndex :                        */
/*               |        Time Series FreezeFrame Index.                    */
/* Return Value  | Dem_u08_FFStoredStatusType                               */
/*               |        DEM_FFD_NOT_STORED : Not Stored                   */
/*               |        DEM_FFD_STORED     : Stored                       */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_FFStoredStatusType, DEM_CODE ) Dem_UdmTSFFDMng_GetRecordStatus
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex
)
{
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) udmTSFFRecordDataPtr;
    VAR( Dem_u08_FFStoredStatusType, AUTOMATIC ) recordStatus;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posRecordStatus;

    recordStatus = DEM_FFD_NOT_STORED;

    udmTSFFRecordDataPtr = Dem_UdmTSFFDMng_GetTimeSeriesFreezeFrameRecordDataPtr( UdmGroupKindIndex, TimeSeriesFreezeFrameIndex );  /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/TimeSeriesFreezeFrameIndex/udmTSFFRecordDataPtr */
    if( udmTSFFRecordDataPtr != NULL_PTR )                                          /* [GUD:if]udmTSFFRecordDataPtr */
    {
        posRecordStatus = Dem_UdmTimeSeriesFreezeFrameDataPosTable[UdmGroupKindIndex].RecordStatus; /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posRecordStatus */
        /*  check available data of Dem_UdmTimeSeriesFreezeFrameDataPosTable[]    */
        if ( posRecordStatus != DEM_FFDSTOREDINDEX_INVALID )
        {
            recordStatus = udmTSFFRecordDataPtr[posRecordStatus];                   /* [GUD]udmTSFFRecordDataPtr *//* [GUD]posRecordStatus *//* [ARYCHK] Dem_UdmTimeSeriesFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posRecordStatus */
        }
    }
    else
    {
        /* No process */
    }
    return recordStatus;
}


/****************************************************************************/
/* Function Name | Dem_UdmTSFFDMng_ClearTimeSeriesFreezeFrameRecord         */
/* Description   | Get the data body of the time series FreezeFrameList re- */
/*               | cord from the FreezeFrameList record list corresponding- */
/*               |  to the specified FreezeFrameList index.                 */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        User defined memory table Index.                  */
/*               | [in] TimeSeriesFreezeFrameIndex :                        */
/*               |        Time Series FreezeFrame Index.                    */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmTSFFDMng_ClearTimeSeriesFreezeFrameRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex
)
{
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) udmTSFFRecordDataPtr;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstUdmEventIndexUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstUdmEventIndexLower;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posLastUdmEventIndexUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posLastUdmEventIndexLower;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posRecordStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( uint8, AUTOMATIC ) udmEventIndexUpper;
    VAR( uint8, AUTOMATIC ) udmEventIndexLower;

    retVal = DEM_IRT_NG;

    udmTSFFRecordDataPtr = Dem_UdmTSFFDMng_GetTimeSeriesFreezeFrameRecordDataPtr( UdmGroupKindIndex, TimeSeriesFreezeFrameIndex );  /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/TimeSeriesFreezeFrameIndex/udmTSFFRecordDataPtr */
    if( udmTSFFRecordDataPtr != NULL_PTR )                                                          /* [GUD:if]udmTSFFRecordDataPtr */
    {
        posFirstUdmEventIndexUpper = Dem_UdmTimeSeriesFreezeFrameDataPosTable[UdmGroupKindIndex].FirstUdmEventIndexUpper;   /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posFirstUdmEventIndexUpper */
        posFirstUdmEventIndexLower = Dem_UdmTimeSeriesFreezeFrameDataPosTable[UdmGroupKindIndex].FirstUdmEventIndexLower;   /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posFirstUdmEventIndexLower */
        posLastUdmEventIndexUpper = Dem_UdmTimeSeriesFreezeFrameDataPosTable[UdmGroupKindIndex].LastUdmEventIndexUpper;     /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posLastUdmEventIndexUpper  */
        posLastUdmEventIndexLower = Dem_UdmTimeSeriesFreezeFrameDataPosTable[UdmGroupKindIndex].LastUdmEventIndexLower;     /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posLastUdmEventIndexLower  */
        posRecordStatus = Dem_UdmTimeSeriesFreezeFrameDataPosTable[UdmGroupKindIndex].RecordStatus;                         /* [GUD]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posRecordStatus */

        /*  check available data of Dem_UdmTimeSeriesFreezeFrameDataPosTable[]    */
        if ( posRecordStatus != DEM_FFDSTOREDINDEX_INVALID )
        {
            /* Sets the initial value to the event index of the specified time-series freeze frame record. */
            Dem_UtlMem_SplitByteData( (uint16)DEM_UDMEVENTINDEX_INVALID, &udmEventIndexUpper, &udmEventIndexLower );
            udmTSFFRecordDataPtr[posFirstUdmEventIndexUpper] = udmEventIndexUpper;      /* [GUD]udmTSFFRecordDataPtr *//* [GUD]posFirstUdmEventIndexUpper *//* [ARYCHK] Dem_UdmTimeSeriesFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posFirstUdmEventIndexUpper */
            udmTSFFRecordDataPtr[posFirstUdmEventIndexLower] = udmEventIndexLower;      /* [GUD]udmTSFFRecordDataPtr *//* [GUD]posFirstUdmEventIndexLower *//* [ARYCHK] Dem_UdmTimeSeriesFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posFirstUdmEventIndexLower */
            udmTSFFRecordDataPtr[posLastUdmEventIndexUpper] = udmEventIndexUpper;       /* [GUD]udmTSFFRecordDataPtr *//* [GUD]posLastUdmEventIndexUpper *//* [ARYCHK] Dem_UdmTimeSeriesFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posLastUdmEventIndexUpper */
            udmTSFFRecordDataPtr[posLastUdmEventIndexLower] = udmEventIndexLower;       /* [GUD]udmTSFFRecordDataPtr *//* [GUD]posLastUdmEventIndexLower *//* [ARYCHK] Dem_UdmTimeSeriesFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posLastUdmEventIndexLower */

            /* Sets "not stored" to the record status of the specified time-series freeze frame record. */
            udmTSFFRecordDataPtr[posRecordStatus] = (uint8)DEM_FFD_NOT_STORED;          /* [GUD]udmTSFFRecordDataPtr *//* [GUD]posRecordStatus *//* [ARYCHK] Dem_UdmTimeSeriesFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posRecordStatus */

            retVal = DEM_IRT_OK;
        }
    }

    return retVal;
}


#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_UdmTSFFDMng_InitMirrorMemory                         */
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
static FUNC( void, DEM_CODE ) Dem_UdmTSFFDMng_InitMirrorMemory
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex      /* [PRMCHK:CALLER] */
)
{
    P2VAR( uint8, AUTOMATIC, DEM_VAR_NO_INIT ) tmpUdmTSFFDMirrorDataPtr;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) ffdStoredFormatSize;

    if( Dem_UdmTSFFRecordNvMTable[UdmGroupKindIndex].DemTmpUdmTSFFDMirrorDataPtr != NULL_PTR )                      /* [GUDCHK:CALLER]UdmGroupKindIndex */
    {
        tmpUdmTSFFDMirrorDataPtr = Dem_UdmTSFFRecordNvMTable[UdmGroupKindIndex].DemTmpUdmTSFFDMirrorDataPtr;        /* [GUDCHK:CALLER]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]tmpUdmTSFFDMirrorDataPtr */

        ffdStoredFormatSize = Dem_UdmTimeSeriesFreezeFrameRecordTable[ UdmGroupKindIndex ].DemFFDStoredFormatSize;  /* [GUDCHK:CALLER]UdmGroupKindIndex */
        Dem_UtlMem_SetMemory( &tmpUdmTSFFDMirrorDataPtr[0], DEM_FFD_INITIAL, ffdStoredFormatSize );                 /* [GUDCHK:CALLER]UdmGroupKindIndex *//* [ARYCHK] ffdStoredFormatSize / 1 / 0 *//* [ARYDESC] The registered data size of Dem_UdmTSFFRecordNvMTable[UdmGroupKindIndex].DemTmpUdmTSFFDMirrorDataPtr is the same as Dem_UdmTimeSeriesFreezeFrameRecordTable[ UdmGroupKindIndex ].DemFFDStoredFormatSize */
    }

    return;
}
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */


/****************************************************************************/
/* Function Name | Dem_UdmTSFFDMng_GetTimeSeriesFreezeFrameRecordDataPtr    */
/* Description   | Calculates the pointer of the list of UdmTimeSeriesFree- */
/*               | zeFrame Record by the specified UdmGroupKindIndex and    */
/*               | UdmTimeSeriesFreezeFrameIndex.                           */
/* Preconditions | The specified UdmGroupKindIndex and UdmTimeSeriesFreeze- */
/*               | Frame Index shall be within the range of each maximul    */
/*               | size.                                                    */
/* Parameters    | [in] UdmGroupKindIndex                                   */
/*               |        Index of user defined memory table                */
/*               | [in] UdmTimeSeriesFreezeFrameIndex :                     */
/*               |        The TimeSeriesFreezeFrame index corresponding to- */
/*               |         the specific TimeSeriesFreezeFrame record.       */
/* Return Value  | uint8 *                                                  */
/*               |        NULL_PTR : The calculation was failed             */
/*               |        not NULL_PTR : The calculation was successful     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:Not NULL_PTR] ReturnValue                       */
/* VariableGuard | [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/UdmTimeSeriesFreezeFrameIndex */
/* VariableGuard | [GUD:RET:IF_GUARDED UdmGroupKindIndex/UdmTimeSeriesFreezeFrameIndex] ReturnValue */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC_P2VAR( uint8, DEM_VAR_SAVED_ZONE, DEM_CODE ) Dem_UdmTSFFDMng_GetTimeSeriesFreezeFrameRecordDataPtr
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) UdmTimeSeriesFreezeFrameIndex
)
{
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) udmTSFFRecordDataPtr;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) udmTsffTotalTimeseriesFFRecordNum;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) udmTsffdStoredFormatSize;
    VAR( uint32, AUTOMATIC ) udmTSFFDOffset;

    udmTSFFRecordDataPtr = NULL_PTR;

    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;
    if( UdmGroupKindIndex < userDefinedMemoryNum )                                                                          /* [GUD:if]UdmGroupKindIndex */
    {
        udmTsffTotalTimeseriesFFRecordNum = Dem_UdmTimeSeriesFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDRecordNum;     /* [GUD]UdmGroupKindIndex */
        if( UdmTimeSeriesFreezeFrameIndex < udmTsffTotalTimeseriesFFRecordNum )                                             /* [GUD:if]UdmTimeSeriesFreezeFrameIndex */
        {
            udmTSFFRecordDataPtr = Dem_UdmTimeSeriesFreezeFrameRecordTable[UdmGroupKindIndex].DemFreezeFrameRecordListStartDataPtr;     /* [GUD]UdmGroupKindIndex */
            udmTsffdStoredFormatSize = Dem_UdmTimeSeriesFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize;               /* [GUD]UdmGroupKindIndex */

            udmTSFFDOffset = (uint32)( (uint32)udmTsffdStoredFormatSize * (uint32)UdmTimeSeriesFreezeFrameIndex );  /* no wrap around *//* [GUD:CFG:IF_GUARDED UdmTimeSeriesFreezeFrameIndex ]udmTSFFDOffset */

            udmTSFFRecordDataPtr = &udmTSFFRecordDataPtr[udmTSFFDOffset];                                                   /* [GUD]udmTSFFDOffset *//* [ARYCHK] (udmTsffdStoredFormatSize*udmTsffTotalTimeseriesFFRecordNum) / 1 / udmTSFFDOffset */
        }
    }

    return udmTSFFRecordDataPtr;
}


/****************************************************************************/
/* Function Name | Dem_UdmTSFFDMng_ClearTSFFList                            */
/* Description   | Set the storage status to not stored of time series Fre- */
/*               | ezeFrame record corresponding to the indexes which spec- */
/*               | ified start and end.                                     */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        User defined memory table Index.                  */
/*               | [in] tsFFRecStartIndex :                                 */
/*               |        Time Series FreezeFrame record's start Index.     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmTSFFDMng_ClearTSFFList
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,     /* [PRMCHK:CALLER] */
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TSFFRecordStartIndex,
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TSFFRecordEndIndex
)
{
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) udmTSFFRecordDataPtr;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posRecordStatus;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) tsFFRecIndex;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindUdmTSFFD;

    posRecordStatus = Dem_UdmTimeSeriesFreezeFrameDataPosTable[UdmGroupKindIndex].RecordStatus;     /* [GUDCHK:CALLER]UdmGroupKindIndex *//* [GUD:CFG:IF_GUARDED:UdmGroupKindIndex]posRecordStatus */
    /*  check available data of Dem_UdmTimeSeriesFreezeFrameDataPosTable[]    */
    if ( posRecordStatus != DEM_FFDSTOREDINDEX_INVALID )
    {
        for( tsFFRecIndex = TSFFRecordStartIndex; tsFFRecIndex <= TSFFRecordEndIndex; tsFFRecIndex++ )
        {
            udmTSFFRecordDataPtr = Dem_UdmTSFFDMng_GetTimeSeriesFreezeFrameRecordDataPtr( UdmGroupKindIndex, tsFFRecIndex );    /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/tsFFRecIndex/udmTSFFRecordDataPtr */
            if( udmTSFFRecordDataPtr != NULL_PTR )                                          /* [GUD:if]udmTSFFRecordDataPtr */
            {
                udmTSFFRecordDataPtr[posRecordStatus] = (uint8)DEM_FFD_NOT_STORED;          /* [GUD]udmTSFFRecordDataPtr *//* [GUD]posRecordStatus *//* [ARYCHK] Dem_UdmTimeSeriesFreezeFrameRecordTable[UdmGroupKindIndex].DemFFDStoredFormatSize / 1 / posRecordStatus */

                /* Change Dem_FFDNvMStatus */
                recMngCmnKindUdmTSFFD = Dem_UdmTSFFDNvMStatus[ UdmGroupKindIndex ].DemRecMngCmnKindUdmTSFFD;        /* [GUD]UdmGroupKindIndex */
                Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindUdmTSFFD, ( Dem_u16_RecordIndexType )tsFFRecIndex );
                /* Sets the return value to OK, cause the illegal value will not be returned. */
            }
        }
    }

    return;
}

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_UdmTSFFDMng_GetEventIdFromRecordData                 */
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
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmTSFFDMng_GetEventIdFromRecordData
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndex;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) udmTimeSeriesFreezeFrameIndex;

    udmEventIndex       =   DEM_UDMEVENTINDEX_INVALID;
    udmTimeSeriesFreezeFrameIndex =   ( Dem_u16_UdmFFDIndexType )RecordIndex;

    /*  TSFFD is in only DEM_MEMORYTYPE_ASYNCEVENT memtype.             */
    /*  so , no exclusive area for DEM_MEMORYTYPE_SYNCEVENT memtype.    */

    retVal  =   Dem_UdmMng_GetUdmEventIndexFromUdmTSFFDRecord( ( Dem_u16_UdmDemMemKindIndexType )RecordFieldIndex, udmTimeSeriesFreezeFrameIndex, &udmEventIndex );
    if ( retVal == DEM_IRT_OK )
    {
        retVal  =   Dem_UdmMng_GetEventIdFromUdmEventIndex( udmEventIndex, EventIdPtr );
    }

    return retVal;
}
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* ( DEM_TSFF_UDM_SUPPORT == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
