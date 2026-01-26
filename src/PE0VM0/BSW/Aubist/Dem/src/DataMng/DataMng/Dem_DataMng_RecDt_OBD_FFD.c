/* Dem_DataMng_RecDt_OBD_FFD_c(v5-5-0)                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Dem_DataMng_RecDt_OBD_FFD_c/CODE                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_Rc_DataMng.h"
#include "../../../inc/Dem_Utl.h"
#include "../../../inc/Dem_Rc_RecMngCmn.h"
#include "../../../inc/Dem_Rc_RecMngCmn_Table.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "MisfireMng/Dem_MisfireMng_local.h"
#include "Dem_DataMng_local.h"
#include "Dem_DataMng_FreezeFrame.h"
#include "Dem_DataMng_GetRecordData.h"

#if ( DEM_OBDFFD_SUPPORT == STD_ON )

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#if ( DEM_OBDFFD_RECNUMF0_SUPPORT == STD_ON )
#define DEM_OBDFFDMNG_UDS_FFDRECORD_NUM       ( (Dem_u08_FFListIndexType)2U )
#endif  /* ( DEM_OBDFFD_RECNUMF0_SUPPORT == STD_ON )    */

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
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMng_ClearObdFreezeFrameRecord
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) ObdFreezeFrameIndex
);
#if ( DEM_OBDFFD_RECNUMF0_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_ObdFFDMng_CheckConsistencyOneRecordData
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_u08_RecMngMtxStsType, AUTOMATIC, AUTOMATIC ) BeforeNvmStatusPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ConsistencyIdUpdateFlgPtr/* MISRA DEVIATION */
);
static FUNC( void, DEM_CODE ) Dem_ObdFFDMng_CheckConsistencyOBDonUDSRecordData
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_u08_RecMngMtxStsType, AUTOMATIC, AUTOMATIC ) BeforeNvmStatusPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ConsistencyIdUpdateFlgPtr/* MISRA DEVIATION */
);
#endif /* DEM_OBDFFD_RECNUMF0_SUPPORT -STD_ON- */

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
static FUNC( void, DEM_CODE ) Dem_ObdFFDMng_InitMirrorMemory
( void );
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ObdFFDMng_CheckConsistency
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) ObdFreezeFrameIndex
);

static FUNC( void, DEM_CODE ) Dem_ObdFFDMng_GetFFDConsistencyInfo
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) ObdFreezeFrameIndex,
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) FirstBlockCIdPtr,
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) LastBlockCIdPtr,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) FirstBlockEventStrgIndexPtr,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) LastBlockEventStrgIndexPtr
);

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ObdFFDMng_VerifyChecksum
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) ObdFreezeFrameIndex
);
#if ( DEM_FF_CHECKSUM_SUPPORT == STD_ON )
static FUNC( Dem_u16_FFCheckSumType, DEM_CODE ) Dem_ObdFFDMng_GetChecksum
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) ObdFreezeFrameIndex
);
#endif /* ( DEM_FF_CHECKSUM_SUPPORT == STD_ON ) */

static FUNC( Dem_u08_ConsistencyIdType, DEM_CODE ) Dem_ObdFFDMng_GetFFDConsystencyId
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) ObdFreezeFrameIndex
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT ) Dem_ObdFFDNvMStatus[DEM_OBD_FFD_RECORD_LIST_NUM];
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/*  if DEM_NVM_SYNC_PROCESS_ENABLE is STD_OFF, these valiables are set but never used.  */
VAR( Dem_ObdFreezeFrameRecordType, DEM_VAR_NO_INIT ) Dem_TmpObdFFDMirror;
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#define DEM_START_SEC_VAR_SAVED_ZONE
#include <Dem_MemMap.h>

VAR(Dem_ObdFreezeFrameRecordType, DEM_VAR_SAVED_ZONE ) Dem_ObdFreezeFrameRecordList[DEM_OBD_FFD_RECORD_LIST_NUM];

#define DEM_STOP_SEC_VAR_SAVED_ZONE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_DataMngC_GetObdFFR_MngInfo                           */
/* Description   | Gets FaultIndex of the OBD FreezeFrame record from the   */
/*               | OBD FreezeFrame record list corresponding to the specif- */
/*               | ied OBD FreezeFrame index. (for Dem_DataCtl subunit)     */
/* Preconditions | The specified OBD FreezeFrame index be within the range  */
/*               | of the OBD FreezeFrame record list.                      */
/* Parameters    | [in] ObdFreezeFrameIndex :                               */
/*               |        The OBD FreezeFrame index corresponding to the s- */
/*               |        pecific OBD FreezeFrame record.                   */
/*               | [out] ObdFreezeFrameRecordPtr :                          */
/*               |         &Dem_TmpEventMemoryEntry.ObdFreezeFrameRecord    */
/*               |         AUTOMATIC                                        */
/*               |        The pointer of the OBD FreezeFrame record corres- */
/*               |        ponding to the specified OBD FreezeFrame index.   */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetObdFFR_MngInfo
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) ObdFreezeFrameIndex,
    P2VAR( Dem_ObdFreezeFrameRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) ObdFreezeFrameRecordPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstEventStrgIndexUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstEventStrgIndexLower;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) obdFFDRecordNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;
    obdFFDRecordNum = Dem_ObdFFDRecordNum;

    if( ObdFreezeFrameIndex < obdFFDRecordNum )                                                     /* [GUD:if]ObdFreezeFrameIndex */
    {
        posFirstEventStrgIndexUpper = Dem_ObdFreezeFrameDataPosTable.FirstEventStrgIndexUpper;      /* [GUD:CFG]posFirstEventStrgIndexUpper */
        posFirstEventStrgIndexLower = Dem_ObdFreezeFrameDataPosTable.FirstEventStrgIndexLower;      /* [GUD:CFG]posFirstEventStrgIndexLower */
        /* Gets EventIndex from storage format. */
        eventStrgIndex = (Dem_u16_EventStrgIndexType)Dem_UtlMem_ConvertByteData( Dem_ObdFreezeFrameRecordList[ObdFreezeFrameIndex].Data[posFirstEventStrgIndexUpper], Dem_ObdFreezeFrameRecordList[ObdFreezeFrameIndex].Data[posFirstEventStrgIndexLower] );    /* [GUD]ObdFreezeFrameIndex *//* [GUD]posFirstEventStrgIndexUpper *//* [GUD]posFirstEventStrgIndexLower */
        ObdFreezeFrameRecordPtr->EventStrgIndex = eventStrgIndex;

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
/* Function Name | Dem_DataMngC_GetObdFreezeFrameRecord                     */
/* Description   | Gets the data body of the OBD FreezeFrame record from t- */
/*               | he OBD FreezeFrame record list corresponding to the spe- */
/*               | cified OBD FreezeFrame index. (for Dem_DataCtl subunit)  */
/* Preconditions | The specified OBD FreezeFrame index be within the range  */
/*               | of the OBD FreezeFrame record list.                      */
/* Parameters    | [in] ObdFreezeFrameIndex :                               */
/*               |        The OBD FreezeFrame index corresponding to the s- */
/*               |        pecific OBD FreezeFrame record.                   */
/*               | [out] ObdFreezeFrameRecordPtr :                          */
/*               |        The pointer of the OBD FreezeFrame record from D- */
/*               |        ataMng corresponding to the specified OBD Freeze- */
/*               |        Frame index.                                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetObdFreezeFrameRecord
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) ObdFreezeFrameIndex,
    P2VAR( Dem_FreezeFrameRecordMngType, AUTOMATIC, AUTOMATIC ) ObdFreezeFrameRecordPtr
)
{
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstCid;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstEventStrgIndexUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstEventStrgIndexLower;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posRecordStatus;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posDataStart;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) obdFFDRecordNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;
    obdFFDRecordNum = Dem_ObdFFDRecordNum;

    if( ObdFreezeFrameIndex < obdFFDRecordNum )                                                     /* [GUD:if]ObdFreezeFrameIndex */
    {
        posFirstCid = Dem_ObdFreezeFrameDataPosTable.FirstCID;                                      /* [GUD:CFG]posFirstCid */
        posFirstEventStrgIndexUpper = Dem_ObdFreezeFrameDataPosTable.FirstEventStrgIndexUpper;      /* [GUD:CFG]posFirstEventStrgIndexUpper */
        posFirstEventStrgIndexLower = Dem_ObdFreezeFrameDataPosTable.FirstEventStrgIndexLower;      /* [GUD:CFG]posFirstEventStrgIndexLower */
        posRecordStatus = Dem_ObdFreezeFrameDataPosTable.RecordStatus;                              /* [GUD:CFG]posRecordStatus */
        posDataStart = Dem_ObdFreezeFrameDataPosTable.DataStart;                                    /* [GUD:CFG]posDataStart */

        ObdFreezeFrameRecordPtr->ConsistencyId = Dem_ObdFreezeFrameRecordList[ObdFreezeFrameIndex].Data[posFirstCid];       /* [GUD]ObdFreezeFrameIndex *//* [GUD]posFirstCid */
        eventStrgIndex = (Dem_u16_EventStrgIndexType)Dem_UtlMem_ConvertByteData( Dem_ObdFreezeFrameRecordList[ObdFreezeFrameIndex].Data[posFirstEventStrgIndexUpper], Dem_ObdFreezeFrameRecordList[ObdFreezeFrameIndex].Data[posFirstEventStrgIndexLower] );    /* [GUD]ObdFreezeFrameIndex *//* [GUD]posFirstEventStrgIndexUpper *//* [GUD]posFirstEventStrgIndexLower */
        ObdFreezeFrameRecordPtr->EventStrgIndex = eventStrgIndex;
        ObdFreezeFrameRecordPtr->RecordStatus = Dem_ObdFreezeFrameRecordList[ObdFreezeFrameIndex].Data[posRecordStatus];    /* [GUD]ObdFreezeFrameIndex *//* [GUD]posRecordStatus */
        ObdFreezeFrameRecordPtr->DataPtr = &Dem_ObdFreezeFrameRecordList[ObdFreezeFrameIndex].Data[posDataStart];           /* [GUD]ObdFreezeFrameIndex *//* [GUD]posDataStart */

        retVal = DEM_IRT_OK;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_DataMngC_SetObdFreezeFrameRecord                     */
/* Description   | Sets the data body of the OBD FreezeFrame record to the  */
/*               | OBD FreezeFrame record list corresponding to the specif- */
/*               | ied OBD FreezeFrame index. (for Dem_DataCtl subunit)     */
/* Preconditions | The specified OBD FreezeFrame index be within the range  */
/*               | of the OBD FreezeFrame record list.                      */
/* Parameters    | [in] ObdFreezeFrameIndex :                               */
/*               |        The OBD FreezeFrame index corresponding to the s- */
/*               |        pecific OBD FreezeFrame record.                   */
/*               | [in] ObdFreezeFrameRecordPtr :                           */
/*               |         &Dem_TmpEventMemoryEntry.ObdFreezeFrameRecord    */
/*               |         AUTOMATIC                                        */
/*               |        The pointer of the OBD FreezeFrame record corres- */
/*               |        ponding to the specified OBD FreezeFrame index.   */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_SetObdFreezeFrameRecord
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) ObdFreezeFrameIndex,
    P2CONST( Dem_ObdFreezeFrameRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) ObdFreezeFrameRecordPtr
)
{
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) obdFFDRecordNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) consistencyId;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) obdFFRMaxLength;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindObdFFD;

    retVal = DEM_IRT_NG;
    obdFFDRecordNum = Dem_ObdFFDRecordNum;

    if( ObdFreezeFrameIndex < obdFFDRecordNum )                                                 /* [GUD:if]ObdFreezeFrameIndex */
    {
        consistencyId = Dem_ObdFFDMng_GetFFDConsystencyId( ObdFreezeFrameIndex );

        consistencyId = Dem_UtlCid_CalcConsistencyId( consistencyId );

        obdFFRMaxLength = Dem_ObdFFRMaxLength;

        /* Sets the captured OBD freeze frame data record and the index of fault to storage format. */
        Dem_DataMng_SetCapturedFreezeFrame( &Dem_ObdFreezeFrameDataPosTable, consistencyId, ObdFreezeFrameRecordPtr->EventStrgIndex, ObdFreezeFrameRecordPtr->RecordStatus, ObdFreezeFrameRecordPtr->Data, obdFFRMaxLength, Dem_ObdFreezeFrameRecordList[ObdFreezeFrameIndex].Data );   /* [GUD]ObdFreezeFrameIndex */
        /* Change Dem_ObdFFDNvMStatus */
        recMngCmnKindObdFFD = Dem_RecMngCmnKindObdFFD;
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindObdFFD, ( Dem_u16_RecordIndexType )ObdFreezeFrameIndex );
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
/* Function Name | Dem_DataMngC_ClearObdFreezeFrameRecord                   */
/* Description   | Initialize OBD freeze frame data area.                   */
/*               |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] ObdFreezeFrameIndex :                               */
/*               |        The OBD FreezeFrame index corresponding to the s- */
/*               |        pecific OBD FreezeFrame record.                   */
/* Return Value  | Dem_u08_InternalReturnType                               */
/* Notes         | none.                                                    */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_ClearObdFreezeFrameRecord
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) ObdFreezeFrameIndex
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    /* Because the range of the specified index is checked in the function "Dem_DataMng_ClearObdFreezeFrameRecord", not check it in here. */
    retVal = Dem_DataMng_ClearObdFreezeFrameRecord( ObdFreezeFrameIndex );

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_DataMngC_InitObdFreezeFrameRecordData                */
/* Description   | Initializes the specified OBD freeze frame record.       */
/* Preconditions |                                                          */
/* Parameters    | [out] ObdFreezeFrameRecordPtr :                          */
/*               |        The specified OBD freeze frame record to initial- */
/*               |        ize.                                              */
/*               |         &Dem_TmpEventMemoryEntry.ObdFreezeFrameRecord    */
/*               |         AUTOMATIC                                        */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMngC_InitObdFreezeFrameRecordData
(
    P2VAR( Dem_ObdFreezeFrameRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) ObdFreezeFrameRecordPtr
)
{
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) obdFFRMaxLength;

    /* Sets initial value to the specified freeze frame record. */

    /* The event index */
    ObdFreezeFrameRecordPtr->EventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;

    /* The record status */
    ObdFreezeFrameRecordPtr->RecordStatus = DEM_FFD_NOT_STORED;

    /* The data for OBD freeze frame. */
    obdFFRMaxLength = Dem_ObdFFRMaxLength;
    Dem_UtlMem_SetMemory( &ObdFreezeFrameRecordPtr->Data[0], DEM_FFD_INITIAL, obdFFRMaxLength );

    return ;
}


/****************************************************************************/
/* Function Name | Dem_DataMng_ClearObdFreezeFrameRecord                    */
/* Description   | Initializes the fault index and the record status of the */
/*               | specified record of OBD freeze frame record list.        */
/* Preconditions |                                                          */
/* Parameters    | [in] ObdFreezeFrameIndex :                               */
/*               |        The OBD FreezeFrame index corresponding to the s- */
/*               |        pecific OBD FreezeFrame record.                   */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMng_ClearObdFreezeFrameRecord
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) ObdFreezeFrameIndex
)
{
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstEventStrgIndexUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstEventStrgIndexLower;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posLastEventStrgIndexUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posLastEventStrgIndexLower;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posRecordStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) obdFFDRecordNum;
    VAR( uint8, AUTOMATIC ) eventStrgIndexUpper;
    VAR( uint8, AUTOMATIC ) eventStrgIndexLower;

    retVal = DEM_IRT_OK;
    obdFFDRecordNum = Dem_ObdFFDRecordNum;

    /* Checks the range of the specified index.*/
    if( ObdFreezeFrameIndex < obdFFDRecordNum )                                                     /* [GUD:if]ObdFreezeFrameIndex */
    {
        posFirstEventStrgIndexUpper = Dem_ObdFreezeFrameDataPosTable.FirstEventStrgIndexUpper;      /* [GUD:CFG]posFirstEventStrgIndexUpper */
        posFirstEventStrgIndexLower = Dem_ObdFreezeFrameDataPosTable.FirstEventStrgIndexLower;      /* [GUD:CFG]posFirstEventStrgIndexLower */
        posLastEventStrgIndexUpper = Dem_ObdFreezeFrameDataPosTable.LastEventStrgIndexUpper;        /* [GUD:CFG]posLastEventStrgIndexUpper */
        posLastEventStrgIndexLower = Dem_ObdFreezeFrameDataPosTable.LastEventStrgIndexLower;        /* [GUD:CFG]posLastEventStrgIndexLower */
        posRecordStatus = Dem_ObdFreezeFrameDataPosTable.RecordStatus;                              /* [GUD:CFG]posRecordStatus */

        /* Sets the initial value to the event index of the specified OBD freeze frame record. */
        Dem_UtlMem_SplitByteData( (uint16)DEM_EVENTSTRGINDEX_INVALID, &eventStrgIndexUpper, &eventStrgIndexLower );
        Dem_ObdFreezeFrameRecordList[ObdFreezeFrameIndex].Data[posFirstEventStrgIndexUpper] = eventStrgIndexUpper;  /* [GUD]ObdFreezeFrameIndex *//* [GUD]posFirstEventStrgIndexUpper */
        Dem_ObdFreezeFrameRecordList[ObdFreezeFrameIndex].Data[posFirstEventStrgIndexLower] = eventStrgIndexLower;  /* [GUD]ObdFreezeFrameIndex *//* [GUD]posFirstEventStrgIndexLower */
        Dem_ObdFreezeFrameRecordList[ObdFreezeFrameIndex].Data[posLastEventStrgIndexUpper] = eventStrgIndexUpper;   /* [GUD]ObdFreezeFrameIndex *//* [GUD]posLastEventStrgIndexUpper */
        Dem_ObdFreezeFrameRecordList[ObdFreezeFrameIndex].Data[posLastEventStrgIndexLower] = eventStrgIndexLower;   /* [GUD]ObdFreezeFrameIndex *//* [GUD]posLastEventStrgIndexLower */

        /* Sets "not stored" to the record status of the specified OBD freeze frame record. */
        Dem_ObdFreezeFrameRecordList[ObdFreezeFrameIndex].Data[posRecordStatus] = DEM_FFD_NOT_STORED;               /* [GUD]ObdFreezeFrameIndex *//* [GUD]posRecordStatus */
    }
    else
    {
        retVal = DEM_IRT_NG;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_ObdFFDMng_Init                                       */
/* Description   | Init process of OBD FFD.                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_ObdFFDMng_Init
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex     /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) freezeFrameIndex;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) obdFFDRecordNum;

    obdFFDRecordNum = Dem_ObdFFDRecordNum;

    for( freezeFrameIndex = (Dem_u08_FFDIndexType)0U; freezeFrameIndex < obdFFDRecordNum; freezeFrameIndex++ )      /* [GUD:for]freezeFrameIndex */
    {
        Dem_ObdFFDNvMStatus[ freezeFrameIndex ] = DEM_RECMNGCMN_NVM_STS_NOT_VERIFIED;                               /* [GUD]freezeFrameIndex */
    }

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    /* [FuncSw] */
    Dem_ObdFFDMng_InitMirrorMemory();
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

    return;
}

/****************************************************************************/
/* Function Name | Dem_ObdFFDMng_InitSavedZone                              */
/* Description   | Initialize savedzone process of OBD FFD.                 */
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
FUNC( void, DEM_CODE ) Dem_ObdFFDMng_InitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType      /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) freezeFrameIndex;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) obdFFDRecordNum;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) obdFFDStorageFormatsize;

    obdFFDRecordNum = Dem_ObdFFDRecordNum;
    obdFFDStorageFormatsize = Dem_ObdFreezeFrameDataStoredFormatSize;

    for( freezeFrameIndex = (Dem_u08_FFDIndexType)0U; freezeFrameIndex < obdFFDRecordNum; freezeFrameIndex++ )                      /* [GUD:for]freezeFrameIndex */
    {
        Dem_UtlMem_SetMemory( &Dem_ObdFreezeFrameRecordList[freezeFrameIndex].Data[0], DEM_FFD_INITIAL, obdFFDStorageFormatsize );  /* [GUD]freezeFrameIndex */
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_ObdFFDMng_DataVerify                                 */
/* Description   | Verifies OBD FFD data.                                   */
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
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ObdFFDMng_DataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex     /* MISRA DEVIATION */
)
{
    /* No Process */
    return DEM_IRT_OK;
}

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_ObdFFDMng_SetRecordMirror                            */
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
FUNC( void, DEM_CODE ) Dem_ObdFFDMng_SetRecordMirror
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
)
{
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) obdFFDStorageFormatsize;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) obdFFDDataIndex;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) obdFFDRecordNum;

    obdFFDStorageFormatsize = Dem_ObdFreezeFrameDataStoredFormatSize;
    obdFFDRecordNum = Dem_ObdFFDRecordNum;

    if( BlockMirrorPtr->RecordDataOffset == (Dem_u16_RecordDataSizeType)0U )
    {
        if( BlockMirrorPtr->RecordIndex < obdFFDRecordNum )                 /* [GUD:if]BlockMirrorPtr->RecordIndex */
        {
            /* copy data to mirror area. */
            Dem_UtlMem_CopyMemory( &(Dem_TmpObdFFDMirror.Data[0]), &(Dem_ObdFreezeFrameRecordList[BlockMirrorPtr->RecordIndex].Data[0]), obdFFDStorageFormatsize ); /* [GUD]BlockMirrorPtr->RecordIndex */
        }
    }

    obdFFDDataIndex = Dem_ObdFFDRecordNvBlockSize * BlockMirrorPtr->RecordDataOffset;
    if( obdFFDDataIndex < obdFFDStorageFormatsize )                                 /* [GUD:if]obdFFDDataIndex */
    {
        BlockMirrorPtr->MirrorPtr = &Dem_TmpObdFFDMirror.Data[ obdFFDDataIndex ];   /* [GUD]obdFFDDataIndex */
    }

    return;
}
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

#if ( DEM_OBDFFD_RECNUMF0_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_ObdFFDMng_Verified                                   */
/* Description   | Make OBD FFD verified.                                   */
/* Preconditions |                                                          */
/*               | [in] FaultRecordPtr : Fault record.                      */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_ObdFFDMng_Verified
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ConsistencyIdUpdateFlgPtr/* MISRA DEVIATION */
)
{
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) obdFreezeFrameClassRef;
    VAR( Dem_u16_FFRecNumClassIndexType, AUTOMATIC ) obdFreezeframeRecNumClassRef;
    VAR( boolean, AUTOMATIC ) refObdFreezeFrameClass;
    VAR( Dem_u08_RecMngMtxStsType, AUTOMATIC ) beforeNvmStatus[DEM_OBDFFDMNG_UDS_FFDRECORD_NUM];
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) freezeFrameRecordIndex;

    refObdFreezeFrameClass = (boolean)FALSE;

    /* Checks the reference of freeze frame class. */
    Dem_CfgInfoPm_GetOBDFreezeFrameAndRecNumClassForClear( EventStrgIndex, &obdFreezeFrameClassRef, &obdFreezeframeRecNumClassRef );    /* [GUD:OUT:Not DEM_FFCLASSINDEX_INVALID] obdFreezeFrameClassRef *//* [GUD:OUT:Not DEM_FFRECNUMCLASSINDEX_INVALID] obdFreezeframeRecNumClassRef */

    if( obdFreezeFrameClassRef != DEM_FFCLASSINDEX_INVALID )                                                                            /* [GUD:if] obdFreezeFrameClassRef */
    {
        /* Checks the reference of freeze frame record number class. */
        if( obdFreezeframeRecNumClassRef != DEM_FFRECNUMCLASSINDEX_INVALID )                                                            /* [GUD:if] obdFreezeframeRecNumClassRef */
        {
            refObdFreezeFrameClass = (boolean)TRUE;
        }
    }

    if( refObdFreezeFrameClass == (boolean)TRUE )
    {
        for( freezeFrameRecordIndex = (Dem_u08_FFListIndexType)0U; freezeFrameRecordIndex < DEM_OBDFFDMNG_UDS_FFDRECORD_NUM; freezeFrameRecordIndex++ )     /* [GUD:for] freezeFrameRecordIndex */
        {
            /* initialize */
            beforeNvmStatus[ freezeFrameRecordIndex ] = DEM_RECMNGCMN_NVM_STS_NON_TARGET;                                                                   /* [GUD] freezeFrameRecordIndex */
        }

        Dem_ObdFFDMng_CheckConsistencyOneRecordData( EventStrgIndex, FaultIndex, &beforeNvmStatus[0], ConsistencyIdUpdateFlgPtr );

        Dem_ObdFFDMng_CheckConsistencyOBDonUDSRecordData( EventStrgIndex, FaultIndex, &beforeNvmStatus[0], ConsistencyIdUpdateFlgPtr );

    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_ObdFFDMng_CheckConsistencyOneRecordData              */
/* Description   | verify one of the OBD FFD record.                        */
/* Preconditions |                                                          */
/*               | [in] FaultRecordPtr : Fault record.                      */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_ObdFFDMng_CheckConsistencyOneRecordData
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_u08_RecMngMtxStsType, AUTOMATIC, AUTOMATIC ) BeforeNvmStatusPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ConsistencyIdUpdateFlgPtr/* MISRA DEVIATION */
)
{
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) freezeFrameRecordIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) obdFFRClassPerDTCMaxNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) obdFFDRecordNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) obdFreezeFrameIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVerifyRecord;
    VAR( boolean, AUTOMATIC ) eventOBDKind;
    VAR( boolean, AUTOMATIC ) faultRecordClearFlg;
    VAR( boolean, AUTOMATIC ) setNvMWriteFlg;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindFault;

    obdFFRClassPerDTCMaxNum = Dem_OBDFFRClassPerDTCMaxNum;
    obdFFDRecordNum = Dem_ObdFFDRecordNum;
    setNvMWriteFlg = (boolean)FALSE;

    eventOBDKind = Dem_CfgInfoPm_CheckEventKindOfOBD_InEvtStrgGrp( EventStrgIndex );

    for( freezeFrameRecordIndex = (Dem_u08_FFListIndexType)0U; freezeFrameRecordIndex < obdFFRClassPerDTCMaxNum; freezeFrameRecordIndex++ )     /* [GUD:for]freezeFrameRecordIndex */
    {
        faultRecordClearFlg = (boolean)FALSE;
        obdFreezeFrameIndex = DEM_FAULTINDEX_INITIAL;
        (void)Dem_DataMngC_GetFR_ObdFreezeFrameIndex( FaultIndex, freezeFrameRecordIndex, &obdFreezeFrameIndex );    /* no return check required */     /* [GUD]freezeFrameRecordIndex */
        if( obdFreezeFrameIndex < obdFFDRecordNum )                                                                                                     /* [GUD:if]obdFreezeFrameIndex */
        {
            if( eventOBDKind == (boolean)TRUE )
            {
                BeforeNvmStatusPtr[ freezeFrameRecordIndex ] = Dem_ObdFFDNvMStatus[ obdFreezeFrameIndex ];                                                  /* [GUD]freezeFrameRecordIndex *//* [GUD]obdFreezeFrameIndex */

                retVerifyRecord = Dem_ObdFFDMng_CheckConsistency( EventStrgIndex, obdFreezeFrameIndex );                                                    /* [GUD]obdFreezeFrameIndex */
                if( retVerifyRecord == DEM_IRT_OK )
                {
                    Dem_ObdFFDNvMStatus[ obdFreezeFrameIndex ] = DEM_RECMNGCMN_NVM_STS_NON_TARGET;                                                          /* [GUD]obdFreezeFrameIndex */

                }
                else
                {
                    faultRecordClearFlg = (boolean)TRUE;
                }
            }
            else
            {
                faultRecordClearFlg = (boolean)TRUE;
            }
        }
        else
        {
            if( obdFreezeFrameIndex != DEM_FFRECINDEX_INITIAL )
            {
                faultRecordClearFlg = (boolean)TRUE;
            }
        }

        if( faultRecordClearFlg == (boolean)TRUE )
        {
            Dem_DataMng_InitSpecificObdRecordNumberIndex( FaultIndex, freezeFrameRecordIndex );
            setNvMWriteFlg = (boolean)TRUE;

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
            Dem_MisfireMng_UpdateObdFFDInfoByInitRecordNumberIndex( EventStrgIndex, freezeFrameRecordIndex, ConsistencyIdUpdateFlgPtr );
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
/* Function Name | Dem_ObdFFDMng_CheckConsistencyOBDonUDSRecordData         */
/* Description   | verify one of the OBD FFD record.                        */
/* Preconditions |                                                          */
/*               | [in] FaultRecordPtr : Fault record.                      */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_ObdFFDMng_CheckConsistencyOBDonUDSRecordData
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,    /* MISRA DEVIATION */
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_u08_RecMngMtxStsType, AUTOMATIC, AUTOMATIC ) BeforeNvmStatusPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ConsistencyIdUpdateFlgPtr/* MISRA DEVIATION */
)
{
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) freezeFrameRecordIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) initFreezeFrameRecordIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) obdFFRClassPerDTCMaxNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) obdFFDRecordNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) obdFreezeFrameIndex;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) initObdFreezeFrameIndex;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindFault;

    obdFFRClassPerDTCMaxNum = Dem_OBDFFRClassPerDTCMaxNum;
    obdFFDRecordNum = Dem_ObdFFDRecordNum;

    /* verify to exist first FFD and latest FFD */
    for( freezeFrameRecordIndex = (Dem_u08_FFListIndexType)0U; freezeFrameRecordIndex < obdFFRClassPerDTCMaxNum; freezeFrameRecordIndex++ )                     /* [GUD:for]freezeFrameRecordIndex */
    {
        (void)Dem_DataMngC_GetFR_ObdFreezeFrameIndex( FaultIndex, freezeFrameRecordIndex, &obdFreezeFrameIndex );    /* no return check required */
        if( obdFreezeFrameIndex >= obdFFDRecordNum )
        {
            for( initFreezeFrameRecordIndex = (Dem_u08_FFListIndexType)0U; initFreezeFrameRecordIndex < obdFFRClassPerDTCMaxNum; initFreezeFrameRecordIndex++ ) /* [GUD:for]initFreezeFrameRecordIndex */
            {
                initObdFreezeFrameIndex = DEM_FAULTINDEX_INITIAL;
                (void)Dem_DataMngC_GetFR_ObdFreezeFrameIndex( FaultIndex, initFreezeFrameRecordIndex, &initObdFreezeFrameIndex );    /* no return check required */

                /* Clear ObdRecordNumberIndex of FaultRecord(Saved Zone area) */
                Dem_DataMng_InitSpecificObdRecordNumberIndex( FaultIndex, initFreezeFrameRecordIndex );

                /* revert Dem_ObdFFDNvMStatus to not verified for clear FFD */
                if( initObdFreezeFrameIndex < obdFFDRecordNum )                                                             /* [GUD:if]initObdFreezeFrameIndex */
                {
                    if( Dem_ObdFFDNvMStatus[ initObdFreezeFrameIndex ] == DEM_RECMNGCMN_NVM_STS_NON_TARGET )                /* [GUD]initObdFreezeFrameIndex */
                    {
                        if( BeforeNvmStatusPtr[ initFreezeFrameRecordIndex ] == DEM_RECMNGCMN_NVM_STS_NOT_VERIFIED )        /* [GUD]initFreezeFrameRecordIndex */
                        {
                            Dem_ObdFFDNvMStatus[ initObdFreezeFrameIndex ] = DEM_RECMNGCMN_NVM_STS_NOT_VERIFIED;            /* [GUD]initObdFreezeFrameIndex */
                        }
                    }
                }
            }
            recMngCmnKindFault = Dem_RecMngCmnKindFault;
            Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindFault, ( Dem_u16_RecordIndexType )FaultIndex );

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
            Dem_MisfireMng_UpdateObdFFDInfoByInitRecordNumberIndex( EventStrgIndex, freezeFrameRecordIndex, ConsistencyIdUpdateFlgPtr );
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */

            break;
        }
    }

    return;
}
#endif /* DEM_OBDFFD_RECNUMF0_SUPPORT -STD_ON- */


#if ( DEM_OBDFFD_RECNUMF0_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_ObdFFDMng_Verified                                   */
/* Description   | Make OBD FFD verified.                                   */
/* Preconditions |                                                          */
/*               | [in] FaultRecordPtr : Fault record.                      */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_ObdFFDMng_Verified
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ConsistencyIdUpdateFlgPtr     /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) freezeFrameRecordIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) obdFFRClassPerDTCMaxNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) obdFFDRecordNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) obdFreezeFrameIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVerifyRecord;
    VAR( boolean, AUTOMATIC ) eventOBDKind;
    VAR( boolean, AUTOMATIC ) faultRecordClearFlg;
    VAR( boolean, AUTOMATIC ) setNvMWriteFlg;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindFault;

    obdFFRClassPerDTCMaxNum = Dem_OBDFFRClassPerDTCMaxNum;
    obdFFDRecordNum = Dem_ObdFFDRecordNum;
    setNvMWriteFlg = (boolean)FALSE;

    eventOBDKind = Dem_CfgInfoPm_CheckEventKindOfOBD_InEvtStrgGrp( EventStrgIndex );

    for( freezeFrameRecordIndex = (Dem_u08_FFListIndexType)0U; freezeFrameRecordIndex < obdFFRClassPerDTCMaxNum; freezeFrameRecordIndex++ ) /* [GUD:for]freezeFrameRecordIndex */
    {
        faultRecordClearFlg = (boolean)FALSE;
        obdFreezeFrameIndex = DEM_FAULTINDEX_INITIAL;
        (void)Dem_DataMngC_GetFR_ObdFreezeFrameIndex( FaultIndex, freezeFrameRecordIndex, &obdFreezeFrameIndex );    /* no return check required */
        if( obdFreezeFrameIndex < obdFFDRecordNum )                                                                     /* [GUD:if]obdFreezeFrameIndex */
        {
            if( eventOBDKind == (boolean)TRUE )
            {
                retVerifyRecord = Dem_ObdFFDMng_CheckConsistency( EventStrgIndex, obdFreezeFrameIndex );                /* [GUD]obdFreezeFrameIndex */
                if( retVerifyRecord == DEM_IRT_OK )
                {
                    Dem_ObdFFDNvMStatus[ obdFreezeFrameIndex ] = DEM_RECMNGCMN_NVM_STS_NON_TARGET;                      /* [GUD]obdFreezeFrameIndex */
                }
                else
                {
                    faultRecordClearFlg = (boolean)TRUE;
                }
            }
            else
            {
                faultRecordClearFlg = (boolean)TRUE;
            }
        }
        else
        {
            if( obdFreezeFrameIndex != DEM_FFRECINDEX_INITIAL )
            {
                faultRecordClearFlg = (boolean)TRUE;
            }
        }

        if( faultRecordClearFlg == (boolean)TRUE )
        {
            Dem_DataMng_InitSpecificObdRecordNumberIndex( FaultIndex, freezeFrameRecordIndex );
            setNvMWriteFlg = (boolean)TRUE;
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
            Dem_MisfireMng_UpdateObdFFDInfoByInitRecordNumberIndex( EventStrgIndex, freezeFrameRecordIndex, ConsistencyIdUpdateFlgPtr );
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
#endif /* DEM_OBDFFD_RECNUMF0_SUPPORT -STD_OFF- */


/****************************************************************************/
/* Function Name | Dem_ObdFFDMng_ClearAllNotVerifiedRecord                  */
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
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ObdFFDMng_ClearAllNotVerifiedRecord
(
    P2VAR( Dem_u16_RecordIndexType, AUTOMATIC, AUTOMATIC ) ClearRecordIndexPtr,
    P2VAR( Dem_u32_TotalRecordNumType, AUTOMATIC, AUTOMATIC ) RestOfProcessableNumPtr
)
{
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) freezeFrameIndex;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) obdFFDRecordNum;
    VAR( Dem_u32_TotalRecordNumType, AUTOMATIC ) loopCount;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    obdFFDRecordNum = Dem_ObdFFDRecordNum;
    loopCount = (Dem_u32_TotalRecordNumType)0U;
    retVal = DEM_IRT_OK;

    for( freezeFrameIndex = (Dem_u08_FFDIndexType)( *ClearRecordIndexPtr ); freezeFrameIndex < obdFFDRecordNum; freezeFrameIndex++ )    /* [GUD:for]freezeFrameIndex */
    {
        if( loopCount < *RestOfProcessableNumPtr )
        {
            if( Dem_ObdFFDNvMStatus[ freezeFrameIndex ] == DEM_RECMNGCMN_NVM_STS_NOT_VERIFIED )                         /* [GUD]freezeFrameIndex */
            {
                (void)Dem_DataMng_ClearObdFreezeFrameRecord( freezeFrameIndex );    /* no return check required */      /* [GUD]freezeFrameIndex */
                Dem_ObdFFDNvMStatus[ freezeFrameIndex ] = DEM_RECMNGCMN_NVM_STS_NON_TARGET;                             /* [GUD]freezeFrameIndex */
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

    if( freezeFrameIndex >= obdFFDRecordNum )
    {
        *RestOfProcessableNumPtr = ( *RestOfProcessableNumPtr ) - loopCount;  /* no wrap around */
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_ObdFFDMng_GetNumOfStoredObdFFD                       */
/* Description   | Get the number of stored OBD FFD.                        */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_FFDIndexType                                     */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_FFDIndexType, DEM_CODE ) Dem_ObdFFDMng_GetNumOfStoredObdFFD
( void )
{
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) retObdFFDNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) freezeFrameIndex;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) obdFFDRecordNum;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posRecordStatus;

    retObdFFDNum = 0U;
    obdFFDRecordNum = Dem_ObdFFDRecordNum;
    posRecordStatus = Dem_ObdFreezeFrameDataPosTable.RecordStatus;      /* [GUD:CFG]posRecordStatus */

    for( freezeFrameIndex = (Dem_u08_FFDIndexType)0U; freezeFrameIndex < obdFFDRecordNum; freezeFrameIndex++ )  /* [GUD:for]freezeFrameIndex */
    {
        if( Dem_ObdFreezeFrameRecordList[freezeFrameIndex].Data[posRecordStatus] == DEM_FFD_STORED )            /* [GUD]freezeFrameIndex *//* [GUD]posRecordStatus */
        {
            retObdFFDNum = retObdFFDNum + (Dem_u08_OrderIndexType)1U;
        }
    }

    return retObdFFDNum;
}


/****************************************************************************/
/* Function Name | Dem_ObdFFDMng_CheckConsistency                           */
/* Description   | check consistency of OBD FFD record                      */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex : The event index                    */
/*               | [in] ObdFreezeFrameIndex : The OBD freeze frame index    */
/* Return Value  | Dem_u08_InternalReturnType :                             */
/*               |       DEM_IRT_OK  : This FFDRecord is consistency.       */
/*               |       DEM_IRT_NG  : This FFDRecord is inconsistency.     */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ObdFFDMng_CheckConsistency
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) ObdFreezeFrameIndex
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) firstBlockEventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) lastBlockEventStrgIndex;
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) firstBlockCId;
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) lastBlockCId;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;

    Dem_ObdFFDMng_GetFFDConsistencyInfo( ObdFreezeFrameIndex, &firstBlockCId, &lastBlockCId, &firstBlockEventStrgIndex, &lastBlockEventStrgIndex );

    if( EventStrgIndex == firstBlockEventStrgIndex )
    {
        if( firstBlockEventStrgIndex == lastBlockEventStrgIndex )
        {
            if( firstBlockCId == lastBlockCId )
            {
                retVal = Dem_ObdFFDMng_VerifyChecksum( ObdFreezeFrameIndex );
            }
        }
    }

    return retVal;
}


#if ( DEM_FF_CHECKSUM_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_ObdFFDMng_VerifyChecksum                             */
/* Description   | verify checksum of OBD FFD record                        */
/* Preconditions |                                                          */
/* Parameters    | [in] ObdFreezeFrameIndex : The freeze frame index        */
/* Return Value  | Dem_u08_InternalReturnType :                             */
/*               |       DEM_IRT_OK  : This checksum is consistency.        */
/*               |       DEM_IRT_NG  : This checksum is inconsistency.      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ObdFFDMng_VerifyChecksum
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) ObdFreezeFrameIndex          /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_FFCheckSumType, AUTOMATIC ) registeredChecksum;
    VAR( Dem_u16_FFCheckSumType, AUTOMATIC ) calculatedChecksum;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) obdFFRMaxLength;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posDataStart;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    obdFFRMaxLength = Dem_ObdFFRMaxLength;
    posDataStart = Dem_ObdFreezeFrameDataPosTable.DataStart;
    retVal = DEM_IRT_NG;

    registeredChecksum = Dem_ObdFFDMng_GetChecksum( ObdFreezeFrameIndex );
    calculatedChecksum = Dem_UtlMem_Checksum( &Dem_ObdFreezeFrameRecordList[ObdFreezeFrameIndex].Data[posDataStart], obdFFRMaxLength ); /* [GUDCHK:CALLER]ObdFreezeFrameIndex */

    if( registeredChecksum == calculatedChecksum )
    {
        retVal = DEM_IRT_OK;
    }

    return retVal;
} /* ( DEM_FF_CHECKSUM_SUPPORT == STD_ON ) */

/****************************************************************************/
/* Function Name | Dem_ObdFFDMng_GetChecksum                                */
/* Description   | get checksum in Obd FFD record                           */
/* Preconditions |                                                          */
/* Parameters    | [in] ObdFreezeFrameIndex : The freeze frame index        */
/* Return Value  | uin16 :                                                  */
/*               |       The checksum value                                 */
/*               |       DEM_IRT_NG  : This checksum is inconsistency.      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u16_FFCheckSumType, DEM_CODE ) Dem_ObdFFDMng_GetChecksum
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) ObdFreezeFrameIndex          /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posChecksumUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posChecksumLower;
    VAR( uint8, AUTOMATIC ) checksumUpper;
    VAR( uint8, AUTOMATIC ) checksumLower;
    VAR( Dem_u16_FFCheckSumType, AUTOMATIC ) checksum;

    posChecksumUpper = Dem_ObdFreezeFrameDataPosTable.ChecksumUpper;                            /* [GUD:CFG]posChecksumUpper */
    posChecksumLower = Dem_ObdFreezeFrameDataPosTable.ChecksumLower;                            /* [GUD:CFG]posChecksumLower */

    checksumUpper = Dem_ObdFreezeFrameRecordList[ObdFreezeFrameIndex].Data[posChecksumUpper];   /* [GUDCHK:CALLER]ObdFreezeFrameIndex *//* [GUD]posChecksumUpper */
    checksumLower = Dem_ObdFreezeFrameRecordList[ObdFreezeFrameIndex].Data[posChecksumLower];   /* [GUDCHK:CALLER]ObdFreezeFrameIndex *//* [GUD]posChecksumLower */

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
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ObdFFDMng_VerifyChecksum
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) ObdFreezeFrameIndex              /* MISRA DEVIATION */
)
{
    return DEM_IRT_OK;
}
#endif /* ( DEM_FF_CHECKSUM_SUPPORT == STD_OFF ) */


/****************************************************************************/
/* Function Name | Dem_ObdFFDMng_GetFFDConsistencyInfo                      */
/* Description   | check consistency of OBD FFD record                      */
/* Preconditions |                                                          */
/* Parameters    | [in] ObdFreezeFrameIndex :                               */
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
static FUNC( void, DEM_CODE ) Dem_ObdFFDMng_GetFFDConsistencyInfo
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) ObdFreezeFrameIndex,             /* [PRMCHK:CALLER] */
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

    posFirstCid = Dem_ObdFreezeFrameDataPosTable.FirstCID;                                      /* [GUD:CFG]posFirstCid */
    posLastCid = Dem_ObdFreezeFrameDataPosTable.LastCID;                                        /* [GUD:CFG]posLastCid */
    posFirstEventStrgIndexUpper = Dem_ObdFreezeFrameDataPosTable.FirstEventStrgIndexUpper;      /* [GUD:CFG]posFirstEventStrgIndexUpper */
    posFirstEventStrgIndexLower = Dem_ObdFreezeFrameDataPosTable.FirstEventStrgIndexLower;      /* [GUD:CFG]posFirstEventStrgIndexLower */
    posLastEventStrgIndexUpper = Dem_ObdFreezeFrameDataPosTable.LastEventStrgIndexUpper;        /* [GUD:CFG]posLastEventStrgIndexUpper */
    posLastEventStrgIndexLower = Dem_ObdFreezeFrameDataPosTable.LastEventStrgIndexLower;        /* [GUD:CFG]posLastEventStrgIndexLower */

    *FirstBlockCIdPtr = (Dem_u08_ConsistencyIdType)Dem_ObdFreezeFrameRecordList[ObdFreezeFrameIndex].Data[posFirstCid];     /* [GUDCHK:CALLER]ObdFreezeFrameIndex *//* [GUD]posFirstCid */
    *LastBlockCIdPtr = (Dem_u08_ConsistencyIdType)Dem_ObdFreezeFrameRecordList[ObdFreezeFrameIndex].Data[posLastCid];       /* [GUDCHK:CALLER]ObdFreezeFrameIndex *//* [GUD]posLastCid */
    firstEventStrgIndex = (Dem_u16_EventStrgIndexType)Dem_UtlMem_ConvertByteData( Dem_ObdFreezeFrameRecordList[ObdFreezeFrameIndex].Data[posFirstEventStrgIndexUpper], Dem_ObdFreezeFrameRecordList[ObdFreezeFrameIndex].Data[posFirstEventStrgIndexLower] );   /* [GUDCHK:CALLER]ObdFreezeFrameIndex *//* [GUD]posFirstEventStrgIndexUpper *//* [GUD]posFirstEventStrgIndexLower */
    *FirstBlockEventStrgIndexPtr = firstEventStrgIndex;
    lastEventStrgIndex = (Dem_u16_EventStrgIndexType)Dem_UtlMem_ConvertByteData( Dem_ObdFreezeFrameRecordList[ObdFreezeFrameIndex].Data[posLastEventStrgIndexUpper], Dem_ObdFreezeFrameRecordList[ObdFreezeFrameIndex].Data[posLastEventStrgIndexLower] );      /* [GUDCHK:CALLER]ObdFreezeFrameIndex *//* [GUD]posLastEventStrgIndexUpper *//* [GUD]posLastEventStrgIndexLower */
    *LastBlockEventStrgIndexPtr = lastEventStrgIndex;

    return;
}


/****************************************************************************/
/* Function Name | Dem_ObdFFDMng_GetFFDConsystencyId                        */
/* Description   | check consistency of FFD record                          */
/* Preconditions |                                                          */
/* Parameters    | [in] ObdFreezeFrameIndex :                               */
/*               |        The FreezeFrame index                             */
/* Return Value  | Dem_u08_ConsistencyIdType                                */
/*               |        ConsistencyId                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_ConsistencyIdType, DEM_CODE ) Dem_ObdFFDMng_GetFFDConsystencyId
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) ObdFreezeFrameIndex          /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstCid;
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) consistencyId;

    posFirstCid = Dem_ObdFreezeFrameDataPosTable.FirstCID;                                                          /* [GUD:CFG]posFirstCid */

    consistencyId = (Dem_u08_ConsistencyIdType)Dem_ObdFreezeFrameRecordList[ObdFreezeFrameIndex].Data[posFirstCid]; /* [GUDCHK:CALLER]ObdFreezeFrameIndex *//* [GUD]posFirstCid */

    return consistencyId;
}


#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_ObdFFDMng_InitMirrorMemory                           */
/* Description   | Initialize the Mirror Memory.                            */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_ObdFFDMng_InitMirrorMemory
( void )
{
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) obdFFDStorageFormatsize;

    obdFFDStorageFormatsize = Dem_ObdFreezeFrameDataStoredFormatSize;
    Dem_UtlMem_SetMemory( &Dem_TmpObdFFDMirror.Data[0], DEM_FFD_INITIAL, obdFFDStorageFormatsize );

    return;
}
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_ObdFFDMng_GetEventIdFromRecordData                   */
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
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ObdFFDMng_GetEventIdFromRecordData
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

    retVal  =   Dem_DataMng_GetEventStrgIndexFromObdFFDRecord( freezeFrameIndex, &eventStrgIndex );
    if ( retVal == DEM_IRT_OK )
    {
        retVal  =   Dem_DataMng_GetEventIdFromEventStrgIndex( eventStrgIndex, EventIdPtr );
    }

    return retVal;
}
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
