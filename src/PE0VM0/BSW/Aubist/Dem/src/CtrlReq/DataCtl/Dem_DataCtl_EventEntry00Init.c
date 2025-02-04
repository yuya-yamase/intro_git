/* Dem_DataCtl_EventEntry00Init_c(v5-5-0)                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_EventEntry00Init/CODE                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_DataCtl_TSFFD.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Utl.h"
#include "Dem_DataCtl_local.h"
#include "Dem_DataCtl_EventEntry_local.h"

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

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Data_InitObdFreezeFrameRecordList
( void );
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */

static FUNC( void, DEM_CODE ) Dem_Data_InitFreezeFrameRecordList
( void );

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Data_InitObdFaultRecOverwritten
( void );
#endif /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */

static FUNC( void, DEM_CODE ) Dem_Data_InitFaultRecOverwritten
( void );

#if ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Data_InitCopyFaultRecOverwritten
( void );
#endif /* ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON ) */

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Data_InitFaultRecordTSFFRemove
( void );
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON ) */
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */

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
/* Function Name | Dem_Data_InitTmpEventMemoryEntry                         */
/* Description   | Initializes event memory entry of temporary area.        */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_InitTmpEventMemoryEntry
( void )
{
    /* Initializes the event record. */
    Dem_DataMngC_InitEventCtlRecordData( &Dem_TmpEventMemoryEntry.EventRecord );
    /* Initializes the fault record. */
    Dem_DataMngC_InitFaultCtlRecordData( &Dem_TmpEventMemoryEntry.FaultRecord );

#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /* [FuncSw] */
    /* Initializes the freeze frame record list for OBD. */
    Dem_Data_InitObdFreezeFrameRecordList();
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */

    /* Initializes the freeze frame record list for non-OBD. */
    Dem_Data_InitFreezeFrameRecordList();

    /* Initializes the event memory record list. */
    Dem_DataMngC_InitEvtMemRecData( &Dem_TmpEventMemoryEntry.EventMemoryRecordList );

    /* Initializes the event index. */
    Dem_TmpEventMemoryEntry.EventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;

    /* Initializes the trigger of event. */
    Dem_TmpEventMemoryEntry.Trigger = DEM_VALID_TRIGGER_NONE;

    /* Initializes the number of event memory entries before being updated. */
    Dem_TmpEventMemoryEntry.BeforeNumberOfEventMemoryEntries = DEM_NUMOFEVTMEMENT_INITIAL;
    Dem_TmpEventMemoryEntry.BeforeNumberOfConfirmedDTCs      = DEM_NUMOFEVTMEMENT_INITIAL;
    Dem_TmpEventMemoryEntry.BeforeNumberOfObdMILDTCs         = DEM_NUMOFEVTMEMENT_INITIAL;

    /* Initializes the result of retrieving of registering fault location. */
    Dem_TmpEventMemoryEntry.ResultOfGetFaultRegistLocation          = DEM_IRT_NG;
    Dem_TmpEventMemoryEntry.ResultOfGetConfirmedFaultRegistLocation = DEM_IRT_NG;
    Dem_TmpEventMemoryEntry.ResultOfGetMILFaultRegistLocation       = DEM_IRT_NG;

    /* Initializes the result of comparing each records with no differences. */
    Dem_TmpEventMemoryEntry.ResultOfComparingEventRecords  = DEM_IRT_OK;
    Dem_TmpEventMemoryEntry.ResultOfComparingFaultRecords  = DEM_IRT_OK;

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )    /* [FuncSw] */
    Dem_Data_InitFaultRecordOverwrite();
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */

    return ;
}

/****************************************************************************/
/* Function Name | Dem_Data_InitObdFreezeFrameRecordList                    */
/* Description   | Initializes freeze frame record list for OBD and result  */
/*               | of comparing these records.                              */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Data_InitObdFreezeFrameRecordList
( void )
{
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) freezeFrameRecordIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) obdFFRClassPerDTCMaxNum;

    obdFFRClassPerDTCMaxNum = Dem_OBDFFRClassPerDTCMaxNum;

    /* Initializes the OBD freeze frame record list. */
    for( freezeFrameRecordIndex = (Dem_u08_FFListIndexType)0U; freezeFrameRecordIndex < obdFFRClassPerDTCMaxNum; freezeFrameRecordIndex++ ) /* [GUD:for]freezeFrameRecordIndex */
    {
        /* Initializes the specific OBD freeze frame record. */
        Dem_DataMngC_InitObdFreezeFrameRecordData( &Dem_TmpEventMemoryEntry.ObdFreezeFrameRecordList[freezeFrameRecordIndex] );             /* [GUD]freezeFrameRecordIndex */

        /* Initializes the result of comparing freeze frame records with no differences. */
        Dem_TmpEventMemoryEntry.ResultOfComparingObdFFRecords[freezeFrameRecordIndex] = DEM_IRT_OK;                                         /* [GUD]freezeFrameRecordIndex */
    }

    return;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */

/****************************************************************************/
/* Function Name | Dem_Data_InitFreezeFrameRecordList                       */
/* Description   | Initializes freeze frame record list for non-OBD and re- */
/*               | sult of comparing these records.                         */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_InitFreezeFrameRecordList
( void )
{
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) freezeFrameRecordIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonOBDFFRClassPerDTCMaxNum;

    nonOBDFFRClassPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;

    for( freezeFrameRecordIndex = (Dem_u08_FFListIndexType)0U; freezeFrameRecordIndex < nonOBDFFRClassPerDTCMaxNum; freezeFrameRecordIndex++ )  /* [GUD:for]freezeFrameRecordIndex */
    {
        /* Initializes the specific freeze frame record. */
        Dem_DataMngC_InitFreezeFrameRecordData( &Dem_TmpEventMemoryEntry.FreezeFrameRecordList[freezeFrameRecordIndex] );                       /* [GUD]freezeFrameRecordIndex */

        /* Initializes the result of comparing freeze frame records with no differences. */
        Dem_TmpEventMemoryEntry.ResultOfComparingFFRecords[freezeFrameRecordIndex] = DEM_IRT_OK;                                                /* [GUD]freezeFrameRecordIndex */
    }

    return;
}

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_InitFaultRecordOverwrite                        */
/* Description   | Initializes fault record which to overwrite.             */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_InitFaultRecordOverwrite
( void )
{
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /* [FuncSw] */
    Dem_Data_InitObdFaultRecOverwritten();
#endif /* ( DEM_OBDFFD_SUPPORT == STD_ON )         */

    Dem_Data_InitFaultRecOverwritten();

#if ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON )
    Dem_Data_InitCopyFaultRecOverwritten();
#endif  /* ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON ) */

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )   /* [FuncSw] */
    Dem_Data_InitFaultRecordTSFFRemove();
#endif  /* (DEM_TSFF_PM_SUPPORT == STD_ON)         */

    Dem_EventDisplacement.EventStrgIndexOfFaultRecordOverwritten = DEM_EVENTSTRGINDEX_INVALID;
    Dem_EventDisplacement.DTCStatusAtFaultRecordOverwritten = DEM_DTCSTATUS_BYTE_DEFAULT;
    Dem_EventDisplacement.DTCStatusForFaultRecordOverwrite = DEM_DTCSTATUS_BYTE_DEFAULT;
    Dem_EventDisplacement.NextFaultOccurrenceOrder = DEM_FAIL_OCCURRENCE_NUM_INVALID;

#if ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )   /* [FuncSw] */
    Dem_EventDisplacement.NextConfirmedFaultOccurrenceOrder = DEM_FAIL_OCCURRENCE_NUM_INVALID;
#endif  /* ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )        */

#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )     /* [FuncSw] */
    Dem_EventDisplacement.NextMILFaultOccurrenceOrder = DEM_FAIL_OCCURRENCE_NUM_INVALID;
#endif  /* ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )          */

    return;
}

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_InitObdFaultRecOverwritten                      */
/* Description   | Initializes OBD fault record which to be overwritten.    */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_InitObdFaultRecOverwritten
( void )
{
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) indexOfRecordNumberIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) obdFFRClassPerDTCMaxNum;

    obdFFRClassPerDTCMaxNum = Dem_OBDFFRClassPerDTCMaxNum;

    for( indexOfRecordNumberIndex = (Dem_u08_FFListIndexType)0U; indexOfRecordNumberIndex < obdFFRClassPerDTCMaxNum; indexOfRecordNumberIndex++ )   /* [GUD:for]indexOfRecordNumberIndex */
    {
        Dem_EventDisplacement.ObdFaultRecordOverwritten[indexOfRecordNumberIndex].FaultIndex = DEM_FAULTINDEX_INITIAL;                              /* [GUD]indexOfRecordNumberIndex */
        Dem_EventDisplacement.ObdFaultRecordOverwritten[indexOfRecordNumberIndex].EventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;                      /* [GUD]indexOfRecordNumberIndex */
        Dem_EventDisplacement.ObdFaultRecordOverwritten[indexOfRecordNumberIndex].RecordNumberIndex = DEM_FFRECINDEX_INITIAL;                       /* [GUD]indexOfRecordNumberIndex */
    }

    return;
}
#endif /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_InitFaultRecOverwritten                         */
/* Description   | Initializes fault record which to be overwritten.        */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_InitFaultRecOverwritten
( void )
{
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) indexOfRecordNumberIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonOBDFFRClassPerDTCMaxNum;
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) indexOfTSFFListIndex;
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsffRecordClassNumPerDTCMaxNum;

    nonOBDFFRClassPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;
    tsffRecordClassNumPerDTCMaxNum = Dem_TSFFRecordClassNumPerDTCMaxNum;

    for( indexOfRecordNumberIndex = (Dem_u08_FFListIndexType)0U; indexOfRecordNumberIndex < nonOBDFFRClassPerDTCMaxNum; indexOfRecordNumberIndex++ )    /* [GUD:for]indexOfRecordNumberIndex */
    {
        Dem_EventDisplacement.FaultRecordOverwritten[indexOfRecordNumberIndex].FaultIndex = DEM_FAULTINDEX_INITIAL;                                     /* [GUD]indexOfRecordNumberIndex */
        Dem_EventDisplacement.FaultRecordOverwritten[indexOfRecordNumberIndex].EventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;                             /* [GUD]indexOfRecordNumberIndex */
        Dem_EventDisplacement.FaultRecordOverwritten[indexOfRecordNumberIndex].RecordNumberIndex = DEM_FFRECINDEX_INITIAL;                              /* [GUD]indexOfRecordNumberIndex */

        for( indexOfTSFFListIndex = (Dem_u08_TSFFListPerDTCIndexType)0U; indexOfTSFFListIndex < tsffRecordClassNumPerDTCMaxNum; indexOfTSFFListIndex++ )    /* [GUD:for]indexOfTSFFListIndex */
        {
            Dem_EventDisplacement.FaultRecordOverwritten[indexOfRecordNumberIndex].TimeSeriesFreezeFrameListIndex[indexOfTSFFListIndex] = DEM_INVALID_VACANT_TSFFLIST_INDEX;    /* [GUD]indexOfRecordNumberIndex *//* [GUD]indexOfTSFFListIndex */
        }
    }

    Dem_EventDisplacement.TSFFDeleteByFFROverwritten = (boolean)FALSE;

    return;
}
#endif  /* (DEM_TSFF_PM_SUPPORT == STD_ON ) */
#if ( DEM_TSFF_PM_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_Data_InitFaultRecOverwritten                         */
/* Description   | Initializes fault record which to be overwritten.        */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_InitFaultRecOverwritten
( void )
{
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) indexOfRecordNumberIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonOBDFFRClassPerDTCMaxNum;

    nonOBDFFRClassPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;

    for( indexOfRecordNumberIndex = (Dem_u08_FFListIndexType)0U; indexOfRecordNumberIndex < nonOBDFFRClassPerDTCMaxNum; indexOfRecordNumberIndex++ )    /* [GUD:for]indexOfRecordNumberIndex */
    {
        Dem_EventDisplacement.FaultRecordOverwritten[indexOfRecordNumberIndex].FaultIndex = DEM_FAULTINDEX_INITIAL;                                     /* [GUD]indexOfRecordNumberIndex */
        Dem_EventDisplacement.FaultRecordOverwritten[indexOfRecordNumberIndex].EventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;                             /* [GUD]indexOfRecordNumberIndex */
        Dem_EventDisplacement.FaultRecordOverwritten[indexOfRecordNumberIndex].RecordNumberIndex = DEM_FFRECINDEX_INITIAL;                              /* [GUD]indexOfRecordNumberIndex */
    }

    return;
}
#endif  /* (DEM_TSFF_PM_SUPPORT == STD_OFF) */

#if ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_InitCopyFaultRecOverwritten                     */
/* Description   | Initializes fault record which to be overwritten. (Copy) */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_Data_InitFaultRecOverwritten.  */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_InitCopyFaultRecOverwritten
( void )
{
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) indexOfRecordNumberIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonOBDFFRClassPerDTCMaxNum;

    nonOBDFFRClassPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;

    for( indexOfRecordNumberIndex = (Dem_u08_FFListIndexType)0U; indexOfRecordNumberIndex < nonOBDFFRClassPerDTCMaxNum; indexOfRecordNumberIndex++ )    /* [GUD:for]indexOfRecordNumberIndex */
    {
        Dem_Data_CopyEventDisplacement_FaultRecordOverwritten[indexOfRecordNumberIndex].FaultIndex = DEM_FAULTINDEX_INITIAL;                            /* [GUD]indexOfRecordNumberIndex */
        Dem_Data_CopyEventDisplacement_FaultRecordOverwritten[indexOfRecordNumberIndex].EventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;                    /* [GUD]indexOfRecordNumberIndex */
        Dem_Data_CopyEventDisplacement_FaultRecordOverwritten[indexOfRecordNumberIndex].RecordNumberIndex = DEM_FFRECINDEX_INITIAL;                     /* [GUD]indexOfRecordNumberIndex */
    }

    return;
}
#endif /* ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON ) */

/****************************************************************************/
/* Function Name | Dem_Data_InitFaultRecordTSFFRemove                       */
/* Description   | Initializes fault record which to remove time-series     */
/*               | freeze frame.                                            */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Data_InitFaultRecordTSFFRemove
( void )
{
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) indexOfTSFFListIndex;
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsffRecordClassNumPerDTCMaxNum;

    tsffRecordClassNumPerDTCMaxNum = Dem_TSFFRecordClassNumPerDTCMaxNum;

    for( indexOfTSFFListIndex = (Dem_u08_TSFFListPerDTCIndexType)0U; indexOfTSFFListIndex < tsffRecordClassNumPerDTCMaxNum; indexOfTSFFListIndex++ )    /* [GUD:for]indexOfTSFFListIndex */
    {
        Dem_EventDisplacement.FaultRecordTSFFRemove[indexOfTSFFListIndex] = DEM_INVALID_VACANT_TSFFLIST_INDEX;                                          /* [GUD]indexOfTSFFListIndex */
    }

    return;
}
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON ) */

#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-07-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
