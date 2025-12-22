/* Dem_UdmDataCtl_DisableDTCInfo_c(v5-9-0)                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UdmDataCtl_DisableDTCInfo/CODE                        */
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
#include "../../../inc/Dem_Udm_Data.h"
#include "../../../inc/Dem_Rc_UdmMng.h"

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
#include "../../../inc/Dem_Rc_UdmMngTable.h"
#include "Dem_UdmDataCtl_local.h"
#include "Dem_UdmDataCtl_InfoTSFFD.h"


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/* Update prohibition Record */
typedef struct {
    Dem_UdmEventRecordForCtlType        EventRecord;
    Dem_UdmFaultRecordType              FaultRecord;
    Dem_u16_UdmEventIndexType           UdmEventIndex;
    Dem_u16_UdmDemMemKindIndexType            UdmGroupKindIndex;
} Dem_UdmTmpDisabledRecordType;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

static FUNC( void, DEM_CODE ) Dem_UdmData_InitTmpDisabledRecord
( void );

static FUNC( boolean, DEM_CODE ) Dem_UdmData_CheckConsistencyOfFFRecord
(
    P2CONST( Dem_UdmTmpRecordNumberByDTCType, AUTOMATIC, DEM_VAR_NO_INIT ) UdmTmpRecordNumberByDTCPtr,
    P2VAR( Dem_UdmFreezeFrameRecordMngType, AUTOMATIC, AUTOMATIC ) UdmFreezeFrameRecordPtr
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

static VAR( Dem_UdmTmpDisabledRecordType, DEM_VAR_NO_INIT ) Dem_UdmTmpDisabledRecord;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>


/****************************************************************************/
/* Function Name | Dem_UdmData_SaveDisabledRecord                           */
/* Description   | Saves a disabled record specified by the event index to  */
/*               |  temporary area.                                         */
/* Preconditions | The specified event index corresponding to the DTC has - */
/*               | been already retrieved.                                  */
/* Parameters    | [in] EventIndex :                                        */
/*               |        The event index corresponding to the specific DT- */
/*               |        C value.                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Saving the disabled record was succ- */
/*               |        essful.                                           */
/*               |        DEM_IRT_NG : Saving the disabled record was fail- */
/*               |        ed.                                               */
/*               |        DEM_IRT_WRONG_CONDITION : The event memory entry  */
/*               |         usage status in the temporary RAM area is not a- */
/*               |        ppropriate.                                       */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-9-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_SaveDisabledRecord
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex       /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetEventRec;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFaultRec;
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) numberOfSaveRecord;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInfoTableIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;

    /* Initializes the return value to OK. */
    retVal = DEM_IRT_OK;

    /* Set the num of udm group. */
    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;

    /* Initialize updating prohibition record of temporary RAM area. */
    Dem_UdmData_InitTmpDisabledRecord();

    /* Sets the event index specified in the EventIndex of the update prohibition record of the temporary RAM area. */
    Dem_UdmTmpDisabledRecord.UdmEventIndex = UdmEventIndex;

    /* Get udm group index. */
    udmInfoTableIndex = Dem_CfgInfoUdm_GetMemoryDestination( UdmEventIndex );       /* [GUDCHK:CALLER]UdmEventIndex *//* [GUD:RET:IF_GUARDED: UdmEventIndex ]udmInfoTableIndex */
    Dem_UdmTmpDisabledRecord.UdmGroupKindIndex = Dem_CfgInfoUdm_GetUserDefinedMemoryGroupKindIndexByEventIndex( udmInfoTableIndex, UdmEventIndex );

    if( Dem_UdmTmpDisabledRecord.UdmGroupKindIndex < userDefinedMemoryNum )         /* [GUD:if]Dem_UdmTmpDisabledRecord.UdmGroupKindIndex */
    {
#ifndef JGXSTACK
        /* Starts exclusion. */
        Dem_UdmExcFncTable[Dem_UdmTmpDisabledRecord.UdmGroupKindIndex].ExclusiveEnterFnc(); /* [GUD]Dem_UdmTmpDisabledRecord.UdmGroupKindIndex */
#else   /* JGXSTACK */
        Dem_UdmExcEnterFnc_ForStack();
#endif  /* JGXSTACK */

        /* Get the event record corresponding to the specified event index. */
        resultOfGetEventRec = Dem_UdmEventMngC_GetRecord( UdmEventIndex, &Dem_UdmTmpDisabledRecord.EventRecord );

        /* Checks the result of retrieving the event record. */
        if( resultOfGetEventRec == DEM_IRT_OK ) /* [GUD:RET:DEM_IRT_OK]Dem_UdmTmpDisabledRecord.EventRecord */
        {
            /* Checks whether the fault index is valid. */
            if( Dem_UdmTmpDisabledRecord.EventRecord.UdmFaultIndex != DEM_UDMFAULTINDEX_INITIAL )
            {
                /* The fault index is valid. */

                /* Gets the fault record corresponding to the specific fault index. */
                 resultOfGetFaultRec = Dem_UdmFaultMngC_GetRecord( Dem_UdmTmpDisabledRecord.UdmGroupKindIndex, Dem_UdmTmpDisabledRecord.EventRecord.UdmFaultIndex, &Dem_UdmTmpDisabledRecord.FaultRecord ); /* [GUD]Dem_UdmTmpDisabledRecord.UdmGroupKindIndex */

                /* Checks the result of retrieving the fault record. */
                if( resultOfGetFaultRec != DEM_IRT_OK )
                {
                    /* Retrieving the fault record was failed. */

                    /* Sets the return value to NG. */
                    retVal = DEM_IRT_NG;
                }
                else
                {
                    /* No process */
                }
            }
            else
            {
                /* No process */
            }
        }
        else
        {
            /* Sets the return value to NG. */
            retVal = DEM_IRT_NG;
        }

#ifndef JGXSTACK
        /* Finishes exclusion. */
        Dem_UdmExcFncTable[Dem_UdmTmpDisabledRecord.UdmGroupKindIndex].ExclusiveExitFnc();  /* [GUD]Dem_UdmTmpDisabledRecord.UdmGroupKindIndex */
#else   /* JGXSTACK */
        Dem_UdmExcExitFnc_ForStack();
#endif  /* JGXSTACK */

        /* Checks the return value. */
        if( retVal == DEM_IRT_OK )
        {
            Dem_UdmData_InitSaveTmpRecordNumber();

            numberOfSaveRecord = (Dem_u16_FFRecNumStoredIndexType)0U;

            Dem_UdmData_SaveRecordNumberByDTC( UdmEventIndex, &Dem_UdmTmpDisabledRecord.FaultRecord, &numberOfSaveRecord  );

            Dem_UdmData_SortSaveRecordNumber( numberOfSaveRecord, &Dem_UdmTmpRecordNumberByDTC[0] );

#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )  /*  [FuncSw]    */
            Dem_UdmData_InitTSFFRecordNumber();

            Dem_UdmData_SaveTSFFRecordNumber( Dem_UdmTmpDisabledRecord.UdmGroupKindIndex, UdmEventIndex, &Dem_UdmTmpDisabledRecord.FaultRecord );
#endif  /*   ( DEM_TSFF_UDM_SUPPORT == STD_ON )         */
        }
    }
    else
    {
        /* Sets the return value to NG. */
        retVal = DEM_IRT_NG;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_UdmData_ClearDisabledRecord                          */
/* Description   | Clears the disabled record of temporary area.            */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmData_ClearDisabledRecord
( void )
{
    /* Update prohibition record initialization processing */
    Dem_UdmData_InitTmpDisabledRecord();

    return ;
}


/****************************************************************************/
/* Function Name | Dem_UdmData_GetDTCStatusOfDisabledRecord                 */
/* Description   | Gets the UDS DTC status byte from the disabled record o- */
/*               | f temporary area.                                        */
/* Preconditions |                                                          */
/* Parameters    | [out] DTCStatusPtr :                                     */
/*               |        The UDS DTC status byte which has been retrieved  */
/*               |         from the disabled record of temporary area.      */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmData_GetDTCStatusOfDisabledRecord
(
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    /* Stores UDS DTC status byte from the disabled record of temporary area. */
    *DTCStatusPtr = Dem_UdmTmpDisabledRecord.EventRecord.StatusOfDTC;

    return;
}


/****************************************************************************/
/* Function Name | Dem_UdmData_CheckAndGetConsistentFFRecord                */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmTmpRecordNumberByDTCPtr :                        */
/*               |                                                          */
/*               | [out] UdmFreezeFrameRecordPtr :                          */
/*               |                                                          */
/* Return Value  | boolean                                                  */
/*               |      FALSE : The occurrence order is not match.          */
/*               |      TRUE  : The occurrence order is matched.            */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-9-0      | no object changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_UdmData_CheckAndGetConsistentFFRecord
(
    P2CONST( Dem_UdmTmpRecordNumberByDTCType, AUTOMATIC, DEM_VAR_NO_INIT ) UdmTmpRecordNumberByDTCPtr,
    P2VAR( Dem_UdmFreezeFrameRecordMngType, AUTOMATIC, AUTOMATIC ) UdmFreezeFrameRecordPtr
)
{
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFaultIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFaultRec;
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) udmFaultIndex;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) startUdmFreezeFrameRecordIndex;
    VAR( Dem_u16_UdmFFDIndexType , AUTOMATIC ) udmFFRIndexLimit;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) udmFreezeFrameRecordIndex;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) maxNumberFreezeFrameRecords;
    VAR( Dem_UdmFaultRecordType, AUTOMATIC ) udmFaultRecord;

    retVal = (boolean)FALSE;
    udmFaultIndex = DEM_UDMFAULTINDEX_INITIAL;
    resultOfGetFaultRec = DEM_IRT_NG;

    resultOfGetFaultIndex = Dem_UdmEventMngC_GetER_FaultIndex( Dem_UdmTmpDisabledRecord.UdmEventIndex, &udmFaultIndex );    /* [GUD:RET:DEM_IRT_OK] UdmEventIndex */
    if( resultOfGetFaultIndex == DEM_IRT_OK )
    {
        if( udmFaultIndex != DEM_UDMFAULTINDEX_INITIAL )
        {
            resultOfGetFaultRec = Dem_UdmFaultMngC_GetRecord( Dem_UdmTmpDisabledRecord.UdmGroupKindIndex, udmFaultIndex, &udmFaultRecord );
        }
        else
        {
            /* No process */
        }
    }
    else
    {
        /* No process */
    }

    if( resultOfGetFaultRec == DEM_IRT_OK )
    {
        maxNumberFreezeFrameRecords = Dem_CfgInfoUdm_GetMaxNumberFreezeFrameRecords( Dem_UdmTmpDisabledRecord.UdmEventIndex );

        startUdmFreezeFrameRecordIndex = Dem_UdmTmpDisabledRecord.FaultRecord.RecordNumberIndex;
        if ( startUdmFreezeFrameRecordIndex != DEM_UDMFFRECINDEX_INITIAL )
        {
            if( startUdmFreezeFrameRecordIndex == udmFaultRecord.RecordNumberIndex )
            {
                udmFFRIndexLimit = startUdmFreezeFrameRecordIndex + maxNumberFreezeFrameRecords;
                for( udmFreezeFrameRecordIndex = startUdmFreezeFrameRecordIndex; udmFreezeFrameRecordIndex < udmFFRIndexLimit; udmFreezeFrameRecordIndex++ )
                {
                    if( UdmTmpRecordNumberByDTCPtr->FreezeFrameDataIndex == udmFreezeFrameRecordIndex )
                    {
                        retVal = Dem_UdmData_CheckConsistencyOfFFRecord( UdmTmpRecordNumberByDTCPtr, UdmFreezeFrameRecordPtr );
                        if( retVal == (boolean)TRUE )
                        {
                            break;
                        }
                    }
                    else
                    {
                        /* No process */
                    }
                }
            }
        }
    }
    else
    {
        /* No process */
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_UdmData_GetAllRecordNumber                           */
/* Description   | get all record number.                                   */
/* Preconditions |                                                          */
/* Parameters    | [out] RecordNumBufferPtr :                               */
/*               |        the buffer, to which the freeze frame data recor- */
/*               |        d shall be written to                             */
/*               | [in/out] RecordNumPtr :                                  */
/*               |        the actual number of written data bytes           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Size successfully returned           */
/*               |        DEM_IRT_WRONG_BUFFERSIZE : provided buffer size - */
/*               |        to small                                          */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-7-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_GetAllRecordNumber
(
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, DEM_APPL_DATA ) RecordNumBufferPtr,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) RecordNumPtr
)
{
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC )    maxNumberFreezeFrameRecords;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( uint8, AUTOMATIC ) recordNumCnt;
#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )   /*  [FuncSw]    */
    VAR( uint8, AUTOMATIC ) recordTSFFNumCnt;
#endif  /*  ( DEM_TSFF_UDM_SUPPORT == STD_ON )          */

    /*  get max number of freezeframe.      */
    maxNumberFreezeFrameRecords = Dem_CfgInfoUdm_GetMaxNumberFreezeFrameRecords( Dem_UdmTmpDisabledRecord.UdmEventIndex );
    if ( maxNumberFreezeFrameRecords == ( Dem_u16_UdmFFDIndexType )0U )
    {
        retVal  =   DEM_IRT_WRONG_DTC;
    }
    else
    {
        recordNumCnt        =   (uint8)0U;

        /*------------------------------*/
        /*  trigger freeze frame        */
        /*------------------------------*/
        retVal  =   Dem_UdmData_GetAllFFRecordNumber( Dem_UdmTmpDisabledRecord.UdmEventIndex, RecordNumBufferPtr, (*RecordNumPtr), (uint8)0U, &recordNumCnt );

#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )   /*  [FuncSw]    */
        /*------------------------------*/
        /*  timeseries freeze frame     */
        /*------------------------------*/
        if ( retVal == DEM_IRT_OK )
        {
            recordTSFFNumCnt    =   (uint8)0U;
            retVal  =   Dem_UdmData_GetAllTSFFRecordNumber( RecordNumBufferPtr, (*RecordNumPtr), recordNumCnt, &recordTSFFNumCnt );

            if ( retVal == DEM_IRT_OK )
            {
                recordNumCnt    =   recordNumCnt + recordTSFFNumCnt;
            }
        }
#endif  /*  ( DEM_TSFF_UDM_SUPPORT == STD_ON )          */
        if ( retVal == DEM_IRT_OK )
        {
            *RecordNumPtr   =   recordNumCnt;
        }
    }
    return retVal;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dem_UdmData_InitTmpDisabledRecord                        */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmData_InitTmpDisabledRecord
( void )
{
    Dem_UdmEventMngC_InitRecord( &Dem_UdmTmpDisabledRecord.EventRecord );
    Dem_UdmFaultMng_InitCtlRecordData( &Dem_UdmTmpDisabledRecord.FaultRecord );
    /* Initializes the event index. */
    Dem_UdmTmpDisabledRecord.UdmEventIndex = DEM_UDMEVENTINDEX_INVALID;
    /* Initializes the udm kind index. */
    Dem_UdmTmpDisabledRecord.UdmGroupKindIndex = DEM_UDMTABLEINDEX_INVALID;

    return ;
}


/****************************************************************************/
/* Function Name | Dem_UdmData_CheckConsistencyOfFFRecord                   */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmTmpRecordNumberByDTCPtr :                        */
/*               |                                                          */
/*               | [out] UdmFreezeFrameRecordPtr :                          */
/*               |                                                          */
/* Return Value  | boolean                                                  */
/*               |      FALSE : The UdmTmpRecordNumberByDTC is not match.   */
/*               |      TRUE  : The UdmTmpRecordNumberByDTC is matched.     */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_UdmData_CheckConsistencyOfFFRecord
(
    P2CONST( Dem_UdmTmpRecordNumberByDTCType, AUTOMATIC, DEM_VAR_NO_INIT ) UdmTmpRecordNumberByDTCPtr,
    P2VAR( Dem_UdmFreezeFrameRecordMngType, AUTOMATIC, AUTOMATIC ) UdmFreezeFrameRecordPtr
)
{
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFFRec;

    retVal = (boolean)FALSE;

    resultOfGetFFRec = Dem_UdmFFDMng_GetFreezeFrameRecord( Dem_UdmTmpDisabledRecord.UdmGroupKindIndex, UdmTmpRecordNumberByDTCPtr->FreezeFrameDataIndex, UdmFreezeFrameRecordPtr );
    if( resultOfGetFFRec == DEM_IRT_OK )
    {
        if( UdmTmpRecordNumberByDTCPtr->OccurrenceOrder == UdmFreezeFrameRecordPtr->OccurrenceOrder )
        {
            if( UdmTmpRecordNumberByDTCPtr->CidUdmFreezeFrameRecords == UdmFreezeFrameRecordPtr->CidUdmFreezeFrameRecords )
            {
                retVal = (boolean)TRUE;
            }
        }
    }

    return retVal;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )      */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
