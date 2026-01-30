/* Dem_DataCtl_DisableDTCInfo_c(v5-7-0)                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_DisableDTCInfo/CODE                           */
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
#include "../../../inc/Dem_Pm_DTC.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Pm_DataCtl_OBD.h"
#include "../../../inc/Dem_Pm_Misfire.h"

#include "Dem_DataCtl_local.h"

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

static FUNC( boolean, DEM_CODE ) Dem_Data_GetFFDIndexListStOfDisabledRecord
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_FaultRecordPartsFFDIndexListStType, AUTOMATIC, DEM_VAR_NO_INIT ) FFDIndexListStPtr
);

static FUNC( void, DEM_CODE ) Dem_Data_SaveAllRecordNumber
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNumber,
    P2VAR( Dem_FaultRecordPartsFFDIndexListStType, AUTOMATIC, DEM_VAR_NO_INIT ) FFDIndexListStPtr
);

#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Data_SaveAllRecordNumberForFilteredRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNumber
);
#endif  /*   ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )    */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* Saved temporary area of update prohibition record                        */
/****************************************************************************/
static VAR( Dem_TmpDisabledRecordType, DEM_VAR_NO_INIT ) Dem_TmpDisabledRecord;


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>


/****************************************************************************/
/* Function Name | Dem_Data_SaveDisabledRecord                              */
/* Description   | Saves a disabled record specified by the event index to  */
/*               |  temporary area.                                         */
/* Preconditions | The specified event index corresponding to the DTC has - */
/*               | been already retrieved.                                  */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific DT- */
/*               |        C value.                                          */
/*               | [in] MisfireCylinderNumber :                             */
/*               |        == DEM_MISFIRE_CYL_NUM_INVALID : no misfire event.*/
/*               |        != DEM_MISFIRE_CYL_NUM_INVALID : misfire event.   */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | refactor function.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_SaveDisabledRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,                    /* [PRMCHK:CALLER] */
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNumber
)
{
    VAR( boolean, AUTOMATIC ) existRecordData;
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )   /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) existRecordDataPair;
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )          */

    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;

    /* Initialize updating prohibition record of temporary RAM area. */
    Dem_Data_ClearDisabledRecord();

    /*------------------------------------------*/
    /*  store main latch eventstrgindex.        */
    /*------------------------------------------*/
    Dem_TmpDisabledRecord.EventStrgIndex        =   EventStrgIndex;                             /* [GUDCHK:CALLER]EventStrgIndex */

    /*  check target DTC is under clearDTC.     */
    Dem_TmpDisabledRecord.UnderClearDTC   =   Dem_DTC_JudgeDTCClearTarget( EventStrgIndex );

    if ( Dem_TmpDisabledRecord.UnderClearDTC == (boolean)FALSE )
    {
        /*--------------------------------------*/
        /*  it's not clear now.                 */
        /*--------------------------------------*/

        /*------------------------------------------*/
        /*  latch current statusOfDTC.              */
        /*------------------------------------------*/
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]   */
        if ( MisfireCylinderNumber != DEM_MISFIRE_CYL_NUM_INVALID )
        {
            /*  get cylinder DTC status.            */
            Dem_TmpDisabledRecord.StatusOfDTC = Dem_Misfire_GetCylinderDTCStatus( MisfireCylinderNumber );
        }
        else
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )          */
        {
            /* Get the event record corresponding to the specified event index. */
            (void)Dem_DTC_GetDTCStatusByDTC( EventStrgIndex, &Dem_TmpDisabledRecord.StatusOfDTC ); /* no return check required */

            /*  statusOfDTC : convert latched data                          */
            /*  Translate the DTCStatus that got for the outside output.    */
            (void)Dem_DTC_TranslateDTCStatusForOutputByDTC( EventStrgIndex, &Dem_TmpDisabledRecord.StatusOfDTC );    /* no return check required */
        }

        /*------------------------------------------*/
        /*  latch current freezeframe recordindex.  */
        /*------------------------------------------*/
        /* Checks the result of retrieving the event record. */
        /* Checks whether the fault index is valid. */
        (void)Dem_DataMngC_GetER_FaultIndex( EventStrgIndex, &faultIndex ); /* no return check required */      /* [GUD:RET:DEM_IRT_OK] EventStrgIndex */

        /* The fault index is valid. */
        /* Gets the fault record corresponding to the specific fault index. */
        existRecordData = Dem_Data_GetFFDIndexListStOfDisabledRecord( faultIndex, &Dem_TmpDisabledRecord.FFDIndexListSt );

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )   /*  [FuncSw]    */
        if ( MisfireCylinderNumber != DEM_MISFIRE_CYL_NUM_INVALID )
        {
            /*-----------------------------------------------------------*/
            /*  latch misfire cylinder value at enable pair event.       */
            /*-----------------------------------------------------------*/
            existRecordDataPair =   Dem_DataCtl_SaveTmpDisabledRecordPairEvent( EventStrgIndex );
            if ( existRecordDataPair == (boolean)TRUE )
            {
                existRecordData =   (boolean)TRUE;
            }
        }
#endif  /*  ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )          */
    }
    else
    {
        /*  no data. OK.    */

        /*--------------------------------------*/
        /*  latch default statusOfDTC.          */
        /*--------------------------------------*/
        Dem_TmpDisabledRecord.StatusOfDTC   =   DEM_DTCSTATUS_BYTE_DEFAULT;

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]   */
        if ( MisfireCylinderNumber != DEM_MISFIRE_CYL_NUM_INVALID )
        {
            /*  no process at misfire event.    */
        }
        else
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )          */
        {
            Dem_DTC_TranslateDTCStatusForOutput_NoMergeWIRBit( EventStrgIndex, &Dem_TmpDisabledRecord.StatusOfDTC );
        }

        /*  exist record data.          */
        existRecordData =   (boolean)FALSE;
    }

    /*  initialize recordnumber temporary area. */
    Dem_Data_InitSaveTmpRecordNumber();

    /* Checks record data exist.                */
    if( existRecordData == (boolean)TRUE )
    {
        /*--------------------------------------*/
        /*  save record number.                 */
        /*--------------------------------------*/
        Dem_Data_SaveAllRecordNumber( EventStrgIndex, MisfireCylinderNumber, &Dem_TmpDisabledRecord.FFDIndexListSt );   /* [GUDCHK:CALLER]EventStrgIndex */
    }

    return ;
}


#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_MakeTmpRecordNumberByDTC                        */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific DT- */
/*               |        C value.                                          */
/*               | [in] MisfireCylinderNumber :                             */
/*               |        == DEM_MISFIRE_CYL_NUM_INVALID : no misfire event.*/
/*               |        != DEM_MISFIRE_CYL_NUM_INVALID : misfire event.   */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         | from SID19-03(OnRetrieval) only.                         */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | new created. based on Dem_Data_SaveDisabledRecord        */
/*   v5-7-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_MakeTmpRecordNumberByDTC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,                    /* [PRMCHK:CALLER] */
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNumber
)
{
    /* Initialize updating prohibition record of temporary RAM area. */
    Dem_Data_ClearDisabledRecord();

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )   /*  [FuncSw]    */
    if ( MisfireCylinderNumber != DEM_MISFIRE_CYL_NUM_INVALID )
    {
        /*-----------------------------------------------------------*/
        /*  latch misfire cylinder value at enable pair event.       */
        /*-----------------------------------------------------------*/
        (void)Dem_DataCtl_SaveTmpDisabledRecordPairEvent( EventStrgIndex ); /* no return check required */
    }
#endif  /*  ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  */

    /*  initialize recordnumber temporary area. */
    Dem_Data_InitSaveTmpRecordNumberForFilteredRecord();

    /*--------------------------------------*/
    /*  save record number.                 */
    /*--------------------------------------*/
    Dem_Data_SaveAllRecordNumberForFilteredRecord( EventStrgIndex, MisfireCylinderNumber );   /* [GUDCHK:CALLER]EventStrgIndex */

    return;
}

/****************************************************************************/
/* Function Name | Dem_Data_GetFFDIndexListStOfDisabledRecord               */
/* Description   | Saves record number.                                     */
/* Preconditions |                                                          */
/* Parameters    | [in] FaultIndex :                                        */
/*               |        The fault index corresponding to the specific fa- */
/*               |        ult record.                                       */
/*               | [out] FFDIndexListStPtr :                                */
/*               |        The pointer of frezeframe record index list.      */
/* Return Value  | boolean                                                  */
/*               |        TRUE :                                            */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_Data_GetFFDIndexListStOfDisabledRecord
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_FaultRecordPartsFFDIndexListStType, AUTOMATIC, DEM_VAR_NO_INIT ) FFDIndexListStPtr
)
{
    VAR( boolean, AUTOMATIC ) resultOfGetFaultRec;

    (void)Dem_DataMngC_GetFR_FFDIndexListSt( FaultIndex, FFDIndexListStPtr );   /* no return check required */
    resultOfGetFaultRec = (boolean)TRUE;   /* Always returns OK. */

    return resultOfGetFaultRec;
}
#endif  /*   ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )    */

#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_Data_GetFFDIndexListStOfDisabledRecord               */
/* Description   | Saves record number.                                     */
/* Preconditions |                                                          */
/* Parameters    | [in] FaultIndex :                                        */
/*               |        The fault index corresponding to the specific fa- */
/*               |        ult record.                                       */
/*               | [out] FFDIndexListStPtr :                                */
/*               |        The pointer of frezeframe record index list.      */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : exist Fault record.                       */
/*               |        FALSE : not exist FAult record.                   */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_Data_GetFFDIndexListStOfDisabledRecord
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_FaultRecordPartsFFDIndexListStType, AUTOMATIC, DEM_VAR_NO_INIT ) FFDIndexListStPtr
)
{
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFaultRec;

    retVal  =   (boolean)FALSE;
    resultOfGetFaultRec = Dem_DataMngC_GetFR_FFDIndexListSt( FaultIndex, FFDIndexListStPtr );
    if ( resultOfGetFaultRec == DEM_IRT_OK )
    {
        retVal  =   (boolean)TRUE;
    }

    return retVal;
}
#endif  /*   ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_OFF )   */


/****************************************************************************/
/* Function Name | Dem_Data_SaveAllRecordNumber                             */
/* Description   | Saves record number.                                     */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific DT- */
/*               |        C value.                                          */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_SaveAllRecordNumber
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,                    /* [PRMCHK:CALLER] */
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNumber,
    P2VAR( Dem_FaultRecordPartsFFDIndexListStType, AUTOMATIC, DEM_VAR_NO_INIT ) FFDIndexListStPtr
)
{
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) numberOfSaveRecord;

    numberOfSaveRecord = (Dem_u16_FFRecNumStoredIndexType)0U;

#if ( DEM_OBDFFD_SUPPORT == STD_ON )   /*  [FuncSw]    */
    Dem_Data_SaveObdRecordNumberByDTC( EventStrgIndex, MisfireCylinderNumber, FFDIndexListStPtr, &numberOfSaveRecord );     /* [GUDCHK:CALLER]EventStrgIndex */
#endif  /*   ( DEM_OBDFFD_SUPPORT == STD_ON )          */

    Dem_Data_SaveRecordNumberByDTC( EventStrgIndex, MisfireCylinderNumber, FFDIndexListStPtr, &numberOfSaveRecord );        /* [GUDCHK:CALLER]EventStrgIndex */

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )   /*  [FuncSw]    */
    Dem_Data_SaveTSFFRecordNumberByDTC( EventStrgIndex, MisfireCylinderNumber, FFDIndexListStPtr, &numberOfSaveRecord );    /* [GUDCHK:CALLER]EventStrgIndex */
#endif  /*   ( DEM_TSFF_PM_SUPPORT == STD_ON )         */

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )   /*  [FuncSw]    */
    Dem_DataCtl_SaveRecordNumberByPairEvent( MisfireCylinderNumber, &numberOfSaveRecord );
#endif  /*  ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )          */

    Dem_Data_SortTmpRecordNumber( numberOfSaveRecord );

    return ;
}

#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_SaveAllRecordNumberForFilteredRecord            */
/* Description   | Saves record number.                                     */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific DT- */
/*               |        C value.                                          */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | new created. based on Dem_Data_SaveAllRecordNumber       */
/*   v5-7-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_SaveAllRecordNumberForFilteredRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,                    /* [PRMCHK:CALLER] */
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNumber
)
{
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) numberOfSaveRecord;

    numberOfSaveRecord = (Dem_u16_FFRecNumStoredIndexType)0U;

#if ( DEM_OBDFFD_SUPPORT == STD_ON )   /*  [FuncSw]    */
    Dem_Data_SaveObdRecordNumberByDTCForFilteredRecord( EventStrgIndex, MisfireCylinderNumber, &numberOfSaveRecord );     /* [GUDCHK:CALLER]EventStrgIndex */
#endif  /*   ( DEM_OBDFFD_SUPPORT == STD_ON )          */

    Dem_Data_SaveRecordNumberByDTCForFilteredRecord( EventStrgIndex, MisfireCylinderNumber, &numberOfSaveRecord );        /* [GUDCHK:CALLER]EventStrgIndex */

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )   /*  [FuncSw]    */
    Dem_Data_SaveTSFFRecordNumberByDTCForFilteredRecord( EventStrgIndex, MisfireCylinderNumber, &numberOfSaveRecord );    /* [GUDCHK:CALLER]EventStrgIndex */
#endif  /*   ( DEM_TSFF_PM_SUPPORT == STD_ON )         */

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )   /*  [FuncSw]    */
    Dem_DataCtl_SaveRecordNumberByPairEventForFilteredRecord( MisfireCylinderNumber, &numberOfSaveRecord );
#endif  /*  ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )          */

    Dem_Data_SortTmpRecordNumber( numberOfSaveRecord );

    return ;
}
#endif  /*   ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )    */

/****************************************************************************/
/* Function Name | Dem_Data_ClearDisabledRecord                             */
/* Description   | Clears the disabled record of temporary area.            */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | refactor function.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_ClearDisabledRecord
( void )
{
    /* Update prohibition record initialization processing */
    /* Initializes the event index. */

    Dem_TmpDisabledRecord.EventStrgIndex        =   DEM_EVENTSTRGINDEX_INVALID;

    Dem_TmpDisabledRecord.UnderClearDTC         =   (boolean)FALSE;
    Dem_TmpDisabledRecord.StatusOfDTC           =   DEM_DTCSTATUS_BYTE_DEFAULT;
    Dem_DataMngC_InitFR_FFDIndexListStData( &Dem_TmpDisabledRecord.FFDIndexListSt );

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )   /*  [FuncSw]    */
    Dem_DataCtl_ClearDisabledRecordPairEvent();
#endif  /*  ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )          */

    return ;
}


/****************************************************************************/
/* Function Name | Dem_Data_GetDTCStatusOfDisabledRecord                    */
/* Description   | Gets the UDS DTC status byte from the disabled record o- */
/*               | f temporary area.                                        */
/* Preconditions |                                                          */
/* Parameters    | [out] DTCStatusPtr :                                     */
/*               |        The UDS DTC status byte which has been retrieved  */
/*               |         from the disabled record of temporary area.      */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_UdsStatusByteType, DEM_CODE ) Dem_Data_GetDTCStatusOfDisabledRecord
( void )
{
    /* Stores UDS DTC status byte from the disabled record of temporary area. */

    return Dem_TmpDisabledRecord.StatusOfDTC;
}


/****************************************************************************/
/* Function Name | Dem_Data_GetIsUnderClearDTCOfDisabledRecord              */
/* Description   | under ClearDTC or not at DisableRecordUpdate.            */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | boolean                                                  */
/*               |          FALSE   :   not in ClearDTC.                    */
/*               |          TRUE    :   under ClearDTC.                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_Data_GetIsUnderClearDTCOfDisabledRecord
( void )
{
    return Dem_TmpDisabledRecord.UnderClearDTC;
}

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_GetTmpDisabledRecordObdFFRIndex                 */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] FreezeFrameRecordClassIndex :                       */
/* Return Value  | uint16                                                   */
/*               |        FreezeFrameRecordIndex :                          */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | refactor function.                                       */
/****************************************************************************/
FUNC( Dem_u08_FFDIndexType, DEM_CODE ) Dem_Data_GetTmpDisabledRecordObdFFRIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,/* MISRA DEVIATION */
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassIndex       /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) freezeFrameRecordIndex;
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )   /*  [FuncSw]   */
    VAR( Dem_EventKindType, AUTOMATIC ) eventKind;
#endif  /*  ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )          */

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )   /*  [FuncSw]   */
    eventKind       =   Dem_CfgInfoPm_GetEventKindOfSpecific_InEvtStrgGrp( EventStrgIndex );    /* [GUD]EventStrgIndex */
    if( ( eventKind & DEM_EVTKIND_TYPE_MISFIRE_EVENT ) == DEM_EVTKIND_TYPE_MISFIRE_EVENT )
    {
        freezeFrameRecordIndex  =   DEM_FFRECINDEX_INITIAL;

        if ( EventStrgIndex == Dem_TmpDisabledRecord.EventStrgIndex )
        {
            freezeFrameRecordIndex  =   Dem_TmpDisabledRecord.FFDIndexListSt.ObdRecordNumberIndex[FreezeFrameRecordClassIndex];     /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex */
        }
        else
        {
            /*  check pair eventstrgindex.      */
            Dem_DataCtl_GetTmpDisabledRecordObdFFRIndexAtPairEvent( EventStrgIndex, FreezeFrameRecordClassIndex, &freezeFrameRecordIndex );
        }
    }
    else
#endif  /*  ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )          */
    {
        freezeFrameRecordIndex  =   Dem_TmpDisabledRecord.FFDIndexListSt.ObdRecordNumberIndex[FreezeFrameRecordClassIndex];     /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex */
    }

    return freezeFrameRecordIndex;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */


/****************************************************************************/
/* Function Name | Dem_Data_GetTmpDisabledRecordFFRIndex                    */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] FreezeFrameRecordClassIndex :                       */
/* Return Value  | uint16                                                   */
/*               |        FreezeFrameRecordIndex :                          */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | refactor function.                                       */
/****************************************************************************/
FUNC( Dem_u08_FFDIndexType, DEM_CODE ) Dem_Data_GetTmpDisabledRecordFFRIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,/* MISRA DEVIATION */
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassIndex       /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) freezeFrameRecordIndex;
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )   /*  [FuncSw]   */
    VAR( Dem_EventKindType, AUTOMATIC ) eventKind;
#endif  /*  ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )          */

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )   /*  [FuncSw]   */
    eventKind       =   Dem_CfgInfoPm_GetEventKindOfSpecific_InEvtStrgGrp( EventStrgIndex );    /* [GUD]EventStrgIndex */
    if( ( eventKind & DEM_EVTKIND_TYPE_MISFIRE_EVENT ) == DEM_EVTKIND_TYPE_MISFIRE_EVENT )
    {
        freezeFrameRecordIndex  =   DEM_FFRECINDEX_INITIAL;

        if ( EventStrgIndex == Dem_TmpDisabledRecord.EventStrgIndex )
        {
            freezeFrameRecordIndex  =   Dem_TmpDisabledRecord.FFDIndexListSt.RecordNumberIndex[FreezeFrameRecordClassIndex];        /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex */
        }
        else
        {
            /*  check pair eventstrgindex.      */
            Dem_DataCtl_GetTmpDisabledRecordFFRIndexAtPairEvent( EventStrgIndex, FreezeFrameRecordClassIndex, &freezeFrameRecordIndex );
        }
    }
    else
#endif  /*  ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )          */
    {
        freezeFrameRecordIndex  =   Dem_TmpDisabledRecord.FFDIndexListSt.RecordNumberIndex[FreezeFrameRecordClassIndex];        /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex */
    }

    return freezeFrameRecordIndex;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-07-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
