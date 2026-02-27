/* Dem_DTRMng_c(v5-7-0)                                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DTRMng/CODE                                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

#if ( DEM_DTR_SUPPORT == STD_ON )
#include "../../../cfg/Dem_Cfg.h"
#include "../../../cfg/Dem_NvM_Cfg.h"
#include "../../../inc/Dem_Rc_RecMngCmn.h"
#include "../../../inc/Dem_Rc_RecMngCmn_Table.h"
#include "../../../inc/Dem_Rc_ClrInfoMng.h"

#include "../../../cfg/Dem_Dtr_Cfg.h"
#include "../../../inc/Dem_Rc_DTRMng.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_DTR_CTL_FACTORY_DEFAULT            ((Dem_DTRControlType) DEM_NVBLOCK_FACTORY_VALUE )
#define DEM_DTR_DTRVALUESTORE_FACTORY_DEFAULT  ((Dem_u16_DTRValueStoreType) 0xFFFFU )

#if ( DEM_DTR_RAWDATASTORAGE_SUPPORT == STD_ON )
#define DEM_DTR_DTRVALUERAW_FACTORY_DEFAULT    ((Dem_s32_DTRValueRawType) -1 )
#endif  /* ( DEM_DTR_RAWDATASTORAGE_SUPPORT == STD_ON ) */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( DEM_DTR_RAWDATASTORAGE_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_DTRMng_InitRawData
(
    VAR( Dem_u16_DTRIndexType, AUTOMATIC ) DtrIndex
);
#endif /* DEM_DTR_RAWDATASTORAGE_SUPPORT -STD_ON- */
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
static FUNC( void, DEM_CODE ) Dem_DTRMng_InitMirrorRecord
( void );

#if ( DEM_DTR_RECORD_PADDING_EXIST == STD_ON )
static FUNC( void, DEM_CODE ) Dem_DTRMng_InitPadding
(
    P2VAR( Dem_DtrRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) DtrRecordPtr
);
#endif /* DEM_DTR_RECORD_PADDING_EXIST -STD_ON- */
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT ) Dem_DTRNvMStatus[DEM_DTR_RECORD_NUM];
VAR( Dem_DtrRecordType, DEM_VAR_NO_INIT ) Dem_TmpDTRMirror;
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

static VAR( Dem_u16_DTRIndexType, DEM_VAR_NO_INIT ) Dem_DtrIndexForVerify;


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#define DEM_START_SEC_VAR_SAVED_ZONE
#include <Dem_MemMap.h>

VAR( Dem_DtrRecordType,        DEM_VAR_SAVED_ZONE ) Dem_DtrRecord[DEM_DTR_RECORD_NUM];

#define DEM_STOP_SEC_VAR_SAVED_ZONE
#include <Dem_MemMap.h>


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>
/****************************************************************************/
/* Function Name | Dem_DTRMng_Init                                          */
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
FUNC( void, DEM_CODE ) Dem_DTRMng_Init
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex     /* MISRA DEVIATION */
)
{
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    /* [FuncSw] */
    Dem_DTRMng_InitMirrorRecord();
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */
    Dem_DtrIndexForVerify = (Dem_u16_DTRIndexType)0U;

    return;
}

/****************************************************************************/
/* Function Name | Dem_DTRMng_Shutdown                                      */
/* Description   | Initialize savedzone process of DTR.                     */
/* Preconditions |                                                          */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/*               | [in] InitType :                                          */
/*               |          Initialize savedzone type                       */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DTRMng_InitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType      /* MISRA DEVIATION */
)
{
    VAR( Dem_u16_DTRIndexType, AUTOMATIC ) dtrIndex;
    VAR( Dem_u16_DTRIndexType, AUTOMATIC ) dtrNum;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindDTR;

    dtrNum = Dem_DtrNum;
    recMngCmnKindDTR = Dem_RecMngCmnKindDTR;

    for( dtrIndex = (Dem_u16_DTRIndexType)0U; dtrIndex < dtrNum; dtrIndex++ )       /* [GUD:if]dtrIndex */
    {
#if ( DEM_DTR_RAWDATASTORAGE_SUPPORT == STD_ON )    /* [FuncSw] */
        Dem_DTRMng_InitRawData( dtrIndex );
#endif /* DEM_DTR_RAWDATASTORAGE_SUPPORT -STD_ON- */
        Dem_DtrRecord[dtrIndex].TestResult = DEM_DTR_DTRVALUESTORE_FACTORY_DEFAULT;     /* [GUD]dtrIndex */
        Dem_DtrRecord[dtrIndex].LowerLimit = DEM_DTR_DTRVALUESTORE_FACTORY_DEFAULT;     /* [GUD]dtrIndex */
        Dem_DtrRecord[dtrIndex].UpperLimit = DEM_DTR_DTRVALUESTORE_FACTORY_DEFAULT;     /* [GUD]dtrIndex */
        Dem_DtrRecord[dtrIndex].CtrlVal = DEM_DTR_CTL_FACTORY_DEFAULT;                  /* [GUD]dtrIndex */
        Dem_DtrRecord[dtrIndex].ClearID = DEM_CLRINFO_RECORD_INITIAL;                   /* [GUD]dtrIndex */

        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindDTR, (Dem_u16_RecordIndexType)dtrIndex );     /* [GUD]dtrIndex */
    }

    return;
}

#if ( DEM_DTR_RAWDATASTORAGE_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_DTRMng_SetDTRRecordData                              */
/* Description   | Set DTR Record Data.                                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTRId :                                             */
/*               | [in] DtrDataPtr :                                        */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DTRMng_SetDTRRecordData
(
    VAR( Dem_u16_DTRIndexType, AUTOMATIC ) DTRId,
    P2CONST( Dem_DtrDataType, AUTOMATIC, AUTOMATIC ) DtrDataPtr
)
{
    VAR( Dem_u16_DTRIndexType, AUTOMATIC ) dtrNum;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindDTR;

    dtrNum = Dem_DtrNum;

    if( DTRId < dtrNum )                                                /* [GUD:if]DTRId */
    {
        /* Enter exclusive area */
        SchM_Enter_Dem_DTR();

        /* Set DtrRecord data */
        Dem_DtrRecord[DTRId].TestResult = DtrDataPtr->TestResult;       /* [GUD]DTRId */
        Dem_DtrRecord[DTRId].LowerLimit = DtrDataPtr->LowerLimit;       /* [GUD]DTRId */
        Dem_DtrRecord[DTRId].UpperLimit = DtrDataPtr->UpperLimit;       /* [GUD]DTRId */
        Dem_DtrRecord[DTRId].CtrlVal = DtrDataPtr->CtrlVal;             /* [GUD]DTRId */
        Dem_DtrRecord[DTRId].ClearID = Dem_ClrInfoMng_GetObdClearID();  /* [GUD]DTRId */

        /* Exit exclusive area */
        SchM_Exit_Dem_DTR();

        /* Change status */
        recMngCmnKindDTR = Dem_RecMngCmnKindDTR;
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindDTR, (Dem_u16_RecordIndexType)DTRId );    /* [GUD]DTRId */
    }

    return;
}
#endif  /* ( DEM_DTR_RAWDATASTORAGE_SUPPORT == STD_OFF )    */
#if ( DEM_DTR_RAWDATASTORAGE_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DTRMng_SetDTRRecordData                              */
/* Description   | Set DTR Record Data.                                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTRId :                                             */
/*               | [in] DtrDataPtr :                                        */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DTRMng_SetDTRRecordData
(
    VAR( Dem_u16_DTRIndexType, AUTOMATIC ) DTRId,
    P2CONST( Dem_DtrDataType, AUTOMATIC, AUTOMATIC ) DtrDataPtr
)
{
    VAR( Dem_u16_DTRIndexType, AUTOMATIC ) dtrNum;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindDTR;

    dtrNum = Dem_DtrNum;

    if( DTRId < dtrNum )                                                /* [GUD:if]DTRId */
    {
        /* Enter exclusive area */
        SchM_Enter_Dem_DTR();

        /* Set DtrRecord data */
        Dem_DtrRecord[DTRId].TestResult = DtrDataPtr->TestResult;           /* [GUD]DTRId */
        Dem_DtrRecord[DTRId].LowerLimit = DtrDataPtr->LowerLimit;           /* [GUD]DTRId */
        Dem_DtrRecord[DTRId].UpperLimit = DtrDataPtr->UpperLimit;           /* [GUD]DTRId */
        Dem_DtrRecord[DTRId].CtrlVal = DtrDataPtr->CtrlVal;                 /* [GUD]DTRId */

        Dem_DtrRecord[DTRId].RawTestResult = DtrDataPtr->RawTestResult;     /* [GUD]DTRId */
        Dem_DtrRecord[DTRId].RawLowerLimit = DtrDataPtr->RawLowerLimit;     /* [GUD]DTRId */
        Dem_DtrRecord[DTRId].RawUpperLimit = DtrDataPtr->RawUpperLimit;     /* [GUD]DTRId */

        Dem_DtrRecord[DTRId].ClearID = Dem_ClrInfoMng_GetObdClearID();      /* [GUD]DTRId */

        /* Exit exclusive area */
        SchM_Exit_Dem_DTR();

        /* Change status */
        recMngCmnKindDTR = Dem_RecMngCmnKindDTR;
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindDTR, (Dem_u16_RecordIndexType)DTRId );    /* [GUD]DTRId */
    }

    return;
}
#endif  /* ( DEM_DTR_RAWDATASTORAGE_SUPPORT == STD_ON ) */

/****************************************************************************/
/* Function Name | Dem_DTRMng_GetNumTIDsOfOBDMID                            */
/* Description   | Set Tid Number.                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTRIdIndex :                                        */
/*               | [in] DemDtrTidNum :                                      */
/* Return Value  | Dem_u08_DTRTidIndexType :                                */
/*               |       Possible output Tid Number                         */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_DTRTidIndexType, DEM_CODE ) Dem_DTRMng_GetNumTIDsOfOBDMID
(
    VAR( Dem_u16_DTRIndexType, AUTOMATIC ) DTRIdIndex,
    VAR( Dem_u08_DTRTidIndexType, AUTOMATIC ) DemDtrTidNum
)
{
    VAR( Dem_u08_DTRTidIndexType, AUTOMATIC ) tidNum;
    VAR( Dem_u08_DTRTidIndexType, AUTOMATIC ) dtrTidNum;
    VAR( Dem_u16_DTRIndexType, AUTOMATIC ) dtrId;

    tidNum = (Dem_u08_DTRTidIndexType)0U;

    /* Enter exclusive area */
    SchM_Enter_Dem_DTR();

    for( dtrTidNum = (Dem_u08_DTRTidIndexType)0; dtrTidNum < DemDtrTidNum; dtrTidNum++ )        /* [GUD:for]dtrTidNum */
    {
        dtrId = DTRIdIndex + (Dem_u16_DTRIndexType)dtrTidNum;

        if( Dem_DtrRecord[dtrId].CtrlVal != DEM_DTR_CTL_INVISIBLE )                             /* [GUD]dtrTidNum */
        {
            /* Count TID Number */
            tidNum = tidNum + (Dem_u08_DTRTidIndexType)1U;
        }
    }

    /* Exit exclusive area */
    SchM_Exit_Dem_DTR();

    return tidNum;
}

/****************************************************************************/
/* Function Name | Dem_DTRMng_GetDTRRecordData                              */
/* Description   | Get DTR record.                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTRId :                                             */
/*               | [out] DtrDataPtr :                                       */
/* Return Value  | Dem_u08_InternalReturnType :                             */
/*               |       DEM_IRT_OK : success                               */
/*               |       DEM_IRT_NG : failed                                */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:DEM_IRT_OK] DTRId                               */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTRMng_GetDTRRecordData
(
    VAR( Dem_u16_DTRIndexType, AUTOMATIC ) DTRId,
    P2VAR( Dem_DtrDataType, AUTOMATIC, AUTOMATIC ) DtrDataPtr
)
{
    VAR( Dem_u16_DTRIndexType, AUTOMATIC ) dtrNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    dtrNum = Dem_DtrNum;
    retVal = DEM_IRT_NG;

    if( DTRId < dtrNum )                                                                        /* [GUD:if]DTRId */
    {
        /* Enter exclusive area */
        SchM_Enter_Dem_DTR();

        if( Dem_DtrRecord[DTRId].CtrlVal == DEM_DTR_CTL_NORMAL )                                /* [GUD]DTRId */
        {
            /* Set DTR Data for output data */
            DtrDataPtr->TestResult = Dem_DtrRecord[DTRId].TestResult;                           /* [GUD]DTRId */
            DtrDataPtr->LowerLimit = Dem_DtrRecord[DTRId].LowerLimit;                           /* [GUD]DTRId */
            DtrDataPtr->UpperLimit = Dem_DtrRecord[DTRId].UpperLimit;                           /* [GUD]DTRId */
            DtrDataPtr->CtrlVal = Dem_DtrRecord[DTRId].CtrlVal;                                 /* [GUD]DTRId */

            retVal = DEM_IRT_OK;
        }
        else if( Dem_DtrRecord[DTRId].CtrlVal == DEM_DTR_CTL_RESET )                            /* [GUD]DTRId */
        {
            /* Set DTR Data for output data */
            DtrDataPtr->TestResult = (Dem_u16_DTRValueStoreType)0U;
            DtrDataPtr->LowerLimit = (Dem_u16_DTRValueStoreType)0U;
            DtrDataPtr->UpperLimit = (Dem_u16_DTRValueStoreType)0U;
            DtrDataPtr->CtrlVal = DEM_DTR_CTL_RESET;

            retVal = DEM_IRT_OK;
        }
        else
        {
            /* No process */
        }
        /* Exit exclusive area */
        SchM_Exit_Dem_DTR();
    }

    return retVal;
}

#if ( DEM_DTR_RAWDATASTORAGE_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DTRMng_GetDTR                                        */
/* Description   | Get DTR record for SWC.                                  */
/* Preconditions | none                                                     */
/* Parameters    | [in]  DTRId      :                                       */
/*               | [out] DtrDataPtr :                                       */
/* Return Value  | Dem_u08_InternalReturnType :                             */
/*               |       DEM_IRT_OK : success                               */
/*               |       DEM_IRT_NG : failed                                */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTRMng_GetDTR
(
    VAR( Dem_u16_DTRIndexType, AUTOMATIC ) DTRId,
    P2VAR(Dem_DtrDataType, AUTOMATIC, AUTOMATIC) DtrDataPtr
)
{
    VAR( Dem_u16_DTRIndexType, AUTOMATIC ) dtrNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    dtrNum = Dem_DtrNum;
    retVal = DEM_IRT_NG;

    if( DTRId < dtrNum )                                                    /* [GUD:if]DTRId */
    {
        /* Enter exclusive area */
        SchM_Enter_Dem_DTR();

        DtrDataPtr->TestResult = Dem_DtrRecord[DTRId].TestResult;               /* [GUD]DTRId */
        DtrDataPtr->LowerLimit = Dem_DtrRecord[DTRId].LowerLimit;               /* [GUD]DTRId */
        DtrDataPtr->UpperLimit = Dem_DtrRecord[DTRId].UpperLimit;               /* [GUD]DTRId */
        DtrDataPtr->CtrlVal    = Dem_DtrRecord[DTRId].CtrlVal;                  /* [GUD]DTRId */

        DtrDataPtr->RawTestResult = Dem_DtrRecord[DTRId].RawTestResult;         /* [GUD]DTRId */
        DtrDataPtr->RawLowerLimit = Dem_DtrRecord[DTRId].RawLowerLimit;         /* [GUD]DTRId */
        DtrDataPtr->RawUpperLimit = Dem_DtrRecord[DTRId].RawUpperLimit;         /* [GUD]DTRId */

        /* Exit exclusive area */
        SchM_Exit_Dem_DTR();

        retVal = DEM_IRT_OK;
    }

    return retVal;
}
#endif  /* ( DEM_DTR_RAWDATASTORAGE_SUPPORT == STD_ON ) */

/****************************************************************************/
/* Function Name | Dem_DTRMng_ClearDTRRecordData                            */
/* Description   | Clear DTR record.                                        */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DTRMng_ClearDTRRecordData
( void )
{
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) clearID;
    VAR( Dem_u16_DTRIndexType, AUTOMATIC ) dtrIndex;
    VAR( Dem_u16_DTRIndexType, AUTOMATIC ) dtrNum;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindDTR;

    clearID = Dem_ClrInfoMng_GetObdClearID();
    dtrNum = Dem_DtrNum;
    recMngCmnKindDTR = Dem_RecMngCmnKindDTR;

    for( dtrIndex = (Dem_u16_DTRIndexType)0U; dtrIndex < dtrNum; dtrIndex++ )       /* [GUD:for]dtrIndex */
    {
        if( Dem_DtrRecord[dtrIndex].CtrlVal != DEM_DTR_CTL_INVISIBLE )              /* [GUD]dtrIndex */
        {
            /* Enter exclusive area */
            SchM_Enter_Dem_DTR();

            /* Clear DTR data */
            Dem_DtrRecord[dtrIndex].CtrlVal = DEM_DTR_CTL_RESET;                    /* [GUD]dtrIndex */
            Dem_DtrRecord[dtrIndex].ClearID = clearID;                              /* [GUD]dtrIndex */

            /* Exit exclusive area */
            SchM_Exit_Dem_DTR();

            /* Change status */
            Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindDTR, (Dem_u16_RecordIndexType)dtrIndex );     /* [GUD]dtrIndex */
        }
    }
    return;
}

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DTRMng_SetRecordMirror                               */
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
FUNC( void, DEM_CODE ) Dem_DTRMng_SetRecordMirror
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
)
{
    VAR( Dem_u16_DTRIndexType, AUTOMATIC ) dtrNum;
    dtrNum = Dem_DtrNum;

    if( (Dem_u16_DTRIndexType)(BlockMirrorPtr->RecordIndex) < dtrNum )          /* [GUD:if]BlockMirrorPtr->RecordIndex */
    {
        /* Set Mirror */
#if ( DEM_DTR_RAWDATASTORAGE_SUPPORT == STD_ON )    /*  [FuncSw]    */
        Dem_TmpDTRMirror.RawTestResult = Dem_DtrRecord[BlockMirrorPtr->RecordIndex].RawTestResult;      /* [GUD]BlockMirrorPtr->RecordIndex */
        Dem_TmpDTRMirror.RawLowerLimit = Dem_DtrRecord[BlockMirrorPtr->RecordIndex].RawLowerLimit;      /* [GUD]BlockMirrorPtr->RecordIndex */
        Dem_TmpDTRMirror.RawUpperLimit = Dem_DtrRecord[BlockMirrorPtr->RecordIndex].RawUpperLimit;      /* [GUD]BlockMirrorPtr->RecordIndex */
#endif  /* ( DEM_DTR_RAWDATASTORAGE_SUPPORT == STD_ON )             */
        Dem_TmpDTRMirror.TestResult = Dem_DtrRecord[BlockMirrorPtr->RecordIndex].TestResult;            /* [GUD]BlockMirrorPtr->RecordIndex */
        Dem_TmpDTRMirror.LowerLimit = Dem_DtrRecord[BlockMirrorPtr->RecordIndex].LowerLimit;            /* [GUD]BlockMirrorPtr->RecordIndex */
        Dem_TmpDTRMirror.UpperLimit = Dem_DtrRecord[BlockMirrorPtr->RecordIndex].UpperLimit;            /* [GUD]BlockMirrorPtr->RecordIndex */
        Dem_TmpDTRMirror.CtrlVal = Dem_DtrRecord[BlockMirrorPtr->RecordIndex].CtrlVal;                  /* [GUD]BlockMirrorPtr->RecordIndex */
        Dem_TmpDTRMirror.ClearID = Dem_DtrRecord[BlockMirrorPtr->RecordIndex].ClearID;                  /* [GUD]BlockMirrorPtr->RecordIndex */
    }

    BlockMirrorPtr->MirrorPtr = &Dem_TmpDTRMirror;

    return;

}
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

/****************************************************************************/
/* Function Name | Dem_DTRMng_DataVerify                                    */
/* Description   | Verify DTR record.                                       */
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
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTRMng_DataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex     /* MISRA DEVIATION */
)
{
    VAR( Dem_u16_DTRIndexType, AUTOMATIC ) dtrIndex;
    VAR( Dem_u16_DTRIndexType, AUTOMATIC ) dtrNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) clrIdRead;
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) clrId;
    VAR( Dem_u16_DTRIndexType,AUTOMATIC ) verifyLoopNumByCycle;
    VAR( Dem_u16_DTRIndexType,AUTOMATIC ) loopCount;
    VAR( Dem_u08_InternalReturnType,AUTOMATIC ) retVal;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindDTR;

    dtrNum = Dem_DtrNum;
    verifyLoopNumByCycle = Dem_DtrRecordNumForVerifyByCycle;
    loopCount = (Dem_u16_DTRIndexType)0U;
    recMngCmnKindDTR = Dem_RecMngCmnKindDTR;
    retVal = DEM_IRT_OK;

    /* Read result about clearID */
    clrIdRead = Dem_ClrInfoMng_GetNvmReadResult();

    if( clrIdRead == DEM_IRT_OK )
    {
        clrId = Dem_ClrInfoMng_GetObdClearID();

        for( dtrIndex = Dem_DtrIndexForVerify; dtrIndex < dtrNum; dtrIndex++ )          /* [GUD:for]dtrIndex */
        {
            if( loopCount < verifyLoopNumByCycle )
            {
                if( Dem_DtrRecord[dtrIndex].CtrlVal != DEM_DTR_CTL_FACTORY_DEFAULT )    /* [GUD]dtrIndex */
                {
                    if( Dem_DtrRecord[dtrIndex].ClearID != clrId )                      /* [GUD]dtrIndex */
                    {
                        Dem_DtrRecord[dtrIndex].CtrlVal = DEM_DTR_CTL_RESET;            /* [GUD]dtrIndex */
                        Dem_DtrRecord[dtrIndex].ClearID = clrId;                        /* [GUD]dtrIndex */
                    }
                }
                else
                {
                    Dem_DtrRecord[dtrIndex].CtrlVal = DEM_DTR_CTL_RESET;                /* [GUD]dtrIndex */
                    Dem_DtrRecord[dtrIndex].ClearID = clrId;                            /* [GUD]dtrIndex */
                    Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindDTR, (Dem_u16_RecordIndexType)dtrIndex ); /* [GUD]dtrIndex */
                }

                loopCount = loopCount + (Dem_u16_DTRIndexType)1U;
            }
            else
            {
                Dem_DtrIndexForVerify = dtrIndex;
                retVal = DEM_IRT_PENDING;
                break;
            }
        }
    }
    else
    {
        for( dtrIndex = Dem_DtrIndexForVerify; dtrIndex < dtrNum; dtrIndex++ )          /* [GUD:for]dtrIndex */
        {
            if( loopCount < verifyLoopNumByCycle )
            {
                Dem_DtrRecord[dtrIndex].CtrlVal = DEM_DTR_CTL_RESET;                    /* [GUD]dtrIndex */
                Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindDTR, (Dem_u16_RecordIndexType)dtrIndex );

                loopCount = loopCount + (Dem_u16_DTRIndexType)1U;
            }
            else
            {
                Dem_DtrIndexForVerify = dtrIndex;
                retVal = DEM_IRT_PENDING;
                break;
            }
        }
    }

    return retVal;
}


#if ( DEM_DTR_RAWDATASTORAGE_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DTRMng_IntRawData                                    */
/* Description   | Initialize DTR raw data.                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] DtrIndex :                                          */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_DTRMng_InitRawData
(
    VAR( Dem_u16_DTRIndexType, AUTOMATIC ) DtrIndex         /* [PRMCHK:CALLER] */
)
{
        Dem_DtrRecord[DtrIndex].RawTestResult = DEM_DTR_DTRVALUERAW_FACTORY_DEFAULT;            /* [GUDCHK:CALLER]DtrIndex */
        Dem_DtrRecord[DtrIndex].RawLowerLimit = DEM_DTR_DTRVALUERAW_FACTORY_DEFAULT;            /* [GUDCHK:CALLER]DtrIndex */
        Dem_DtrRecord[DtrIndex].RawUpperLimit = DEM_DTR_DTRVALUERAW_FACTORY_DEFAULT;            /* [GUDCHK:CALLER]DtrIndex */

        return;
}
#endif /* DEM_DTR_RAWDATASTORAGE_SUPPORT -STD_ON- */

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DTRMng_InitMirrorRecord                              */
/* Description   | Initializes the Mirror Memory of DTR record.             */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_DTRMng_InitMirrorRecord
( void )
{
    /* Initializes the mirror memory. */
#if ( DEM_DTR_RAWDATASTORAGE_SUPPORT == STD_ON )    /*  [FuncSw]    */
    Dem_TmpDTRMirror.RawTestResult = (Dem_s32_DTRValueRawType)0;
    Dem_TmpDTRMirror.RawLowerLimit = (Dem_s32_DTRValueRawType)0;
    Dem_TmpDTRMirror.RawUpperLimit = (Dem_s32_DTRValueRawType)0;
#endif /* DEM_DTR_RAWDATASTORAGE_SUPPORT -STD_ON- */

    Dem_TmpDTRMirror.TestResult = (Dem_u16_DTRValueStoreType)0U;
    Dem_TmpDTRMirror.LowerLimit = (Dem_u16_DTRValueStoreType)0U;
    Dem_TmpDTRMirror.UpperLimit = (Dem_u16_DTRValueStoreType)0U;
    Dem_TmpDTRMirror.CtrlVal = DEM_DTR_CTL_NORMAL;
    Dem_TmpDTRMirror.ClearID = DEM_CLRINFO_RECORD_INITIAL;

#if ( DEM_DTR_RECORD_PADDING_EXIST == STD_ON )    /* [FuncSw] */
    /*  initialize padding area.        */
    Dem_DTRMng_InitPadding( &Dem_TmpDTRMirror );
#endif /* DEM_DTR_RECORD_PADDING_EXIST -STD_ON- */

    return;

}
#if ( DEM_DTR_RECORD_PADDING_EXIST == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DTRMng_InitPadding                                   */
/* Description   | Initializes the record padding data.                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] DtrRecordPtr    :                                   */
/*               |       The pointer of the record.                         */
/*               |          &Dem_DtrRecord -DEM_VAR_SAVED_ZONE-             */
/*               |          &Dem_TmpDTRMirror -DEM_VAR_NO_INIT-             */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_DTRMng_InitPadding
(
    P2VAR( Dem_DtrRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) DtrRecordPtr
)
{
    VAR( Dem_u16_PaddingIndexType, AUTOMATIC ) paddingSize;
    VAR( Dem_u16_PaddingIndexType, AUTOMATIC ) paddingIndex;

    paddingSize = Dem_DtrRecordBlockPaddingSize;

    for( paddingIndex = (Dem_u16_PaddingIndexType)0U; paddingIndex < paddingSize; paddingIndex++ )          /* [GUD:for]paddingIndex */
    {
        DtrRecordPtr->Reserve[paddingIndex] = (uint8)0U;            /* [GUD]paddingIndex *//* [ARYCHK] DEM_DTR_RECORD_PADDINGSIZE_TO_BLOCKSIZE/1 / paddingIndex */
    }
    return ;
}
#endif /* DEM_DTR_RECORD_PADDING_EXIST -STD_ON- */

#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DTRMng_GetEventIdFromRecordData                      */
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
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTRMng_GetEventIdFromRecordData
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

#endif  /* ( DEM_DTR_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
