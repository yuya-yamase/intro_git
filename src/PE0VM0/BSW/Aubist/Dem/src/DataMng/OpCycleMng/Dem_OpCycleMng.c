/* Dem_OpCycleMng_c(v5-5-0)                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/OpCycleMng/CODE                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../../../cfg/Dem_Cfg.h"

#if ( DEM_CYCLEQUALIFIED_SUPPORT == STD_ON )

#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_OpCycle_Cfg.h"
#include "../../../inc/Dem_Rc_ClrInfoMng.h"
#include "../../../inc/Dem_Rc_OpCycleMng.h"
#include "../../../inc/Dem_Rc_RecMngCmn.h"
#include "../../../inc/Dem_Rc_RecMngCmn_Table.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
static FUNC( void, DEM_CODE ) Dem_OpCycleMng_InitOperationCycleMirror
( void );
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )   */
static FUNC( void, DEM_CODE ) Dem_OpCycleMng_ClearInfoVerify
( void );

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
static FUNC( void, DEM_CODE ) Dem_OpCycleMng_InitRecordData
(
    P2VAR( Dem_OpCycleRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) OpCycleRecordPtr
);
static FUNC( void, DEM_CODE ) Dem_OpCycleMng_InitPadding
(
    P2VAR( Dem_OpCycleRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) OpCycleRecordPtr
);
static FUNC( void, DEM_CODE ) Dem_OpCycleMng_GetRecordData
(
    P2VAR( Dem_OpCycleRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) OpCycleRecordPtr
);
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT )                    Dem_OpCycleNvMStatus;
VAR( Dem_OpCycleRecordType, DEM_VAR_NO_INIT )    Dem_OpCycleRecordMirror;
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#define DEM_START_SEC_VAR_SAVED_ZONE
#include <Dem_MemMap.h>

VAR( Dem_OpCycleRecordType, DEM_VAR_SAVED_ZONE )        Dem_OpCycleRecord;

#define DEM_STOP_SEC_VAR_SAVED_ZONE
#include <Dem_MemMap.h>


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_OpCycleMng_Init                                      */
/* Description   | Init process of Dem_OpCycleMng unit.                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_OpCycleMng_Init
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex     /* MISRA DEVIATION */
)
{
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    /* [FuncSw] */
    Dem_OpCycleMng_InitOperationCycleMirror();
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )   */
    return ;
}

/****************************************************************************/
/* Function Name | Dem_OpCycleMng_InitSavedZone                             */
/* Description   | Initialize savedzone process of Dem_OpCycleMng unit.     */
/* Preconditions | none                                                     */
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
FUNC( void, DEM_CODE ) Dem_OpCycleMng_InitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType      /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_CycleQualifiedIndexType, AUTOMATIC ) cycleQualifiedNum;
    VAR( Dem_u08_CycleQualifiedIndexType, AUTOMATIC ) cycleQualifiedIndex;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindOpCycle;

    cycleQualifiedNum = Dem_OperationCycleRecordStateNum;

    Dem_OpCycleRecord.ClearID = DEM_CLRINFO_RECORD_INITIAL;
    Dem_OpCycleRecord.PFCClearConditionCheckStatus    =   DEM_PFC_CLEARCONDCHKSTATUS_ENABLE;

    for( cycleQualifiedIndex = (Dem_u08_CycleQualifiedIndexType)0U; cycleQualifiedIndex < cycleQualifiedNum; cycleQualifiedIndex++ )    /* [GUD:for]cycleQualifiedIndex */
    {
        Dem_OpCycleRecord.CycleState[cycleQualifiedIndex] = DEM_CYCLE_NOTIFY_INITIAL;       /* [GUD]cycleQualifiedIndex */
    }

    recMngCmnKindOpCycle = Dem_RecMngCmnKindOpCycle;
    Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindOpCycle, ( Dem_u16_RecordIndexType )0U );

    return ;
}

/****************************************************************************/
/* Function Name | Dem_OpCycleMng_DataVerify                                */
/* Description   | Change the uninitialized data to the value of            */
/*               | DEM_CYCLE_NOTIFY_END before starting processing.         */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |          DEM_IRT_OK      : DataVerify completed.         */
/*               |          DEM_IRT_PENDING : Continue DataVerify.          */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_OpCycleMng_DataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex     /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_CycleQualifiedIndexType, AUTOMATIC ) cycleQualifiedNum;
    VAR( Dem_u08_CycleQualifiedIndexType, AUTOMATIC ) cycleQualifiedIndex;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindOpCycle;
    VAR( boolean, AUTOMATIC ) setNvMWriteFlg;

    setNvMWriteFlg = (boolean)FALSE;
    cycleQualifiedNum = Dem_OperationCycleRecordStateNum;

    Dem_OpCycleMng_ClearInfoVerify();

    for( cycleQualifiedIndex = (Dem_u08_CycleQualifiedIndexType)0U; cycleQualifiedIndex < cycleQualifiedNum; cycleQualifiedIndex++ )    /* [GUD:for]cycleQualifiedIndex */
    {
        if( Dem_OpCycleRecord.CycleState[cycleQualifiedIndex] != DEM_CYCLE_NOTIFY_START )       /* [GUD]cycleQualifiedIndex */
        {
            if( Dem_OpCycleRecord.CycleState[cycleQualifiedIndex] != DEM_CYCLE_NOTIFY_END )     /* [GUD]cycleQualifiedIndex */
            {
                Dem_OpCycleRecord.CycleState[cycleQualifiedIndex] = DEM_CYCLE_NOTIFY_END;       /* [GUD]cycleQualifiedIndex */
                setNvMWriteFlg = (boolean)TRUE;
            }
        }
    }
    if ( Dem_OpCycleRecord.PFCClearConditionCheckStatus != DEM_PFC_CLEARCONDCHKSTATUS_DISABLE )
    {
        if ( Dem_OpCycleRecord.PFCClearConditionCheckStatus != DEM_PFC_CLEARCONDCHKSTATUS_ENABLE )
        {
            Dem_OpCycleRecord.PFCClearConditionCheckStatus    =   DEM_PFC_CLEARCONDCHKSTATUS_ENABLE;
            setNvMWriteFlg = (boolean)TRUE;
        }
    }


    if( setNvMWriteFlg == (boolean)TRUE )
    {
        recMngCmnKindOpCycle = Dem_RecMngCmnKindOpCycle;
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindOpCycle, ( Dem_u16_RecordIndexType )0U );
    }

    return DEM_IRT_OK;
}

/****************************************************************************/
/* Function Name | Dem_OpCycleMng_SetCycleState                             */
/* Description   | Sets operation cycle state by operation cycle index.     */
/* Preconditions | none                                                     */
/* Parameters    | [in] CycleQualifiedIndex : cycle qualified index.        */
/*               | [in] CycleState : Operation cycle state.                 */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_OpCycleMng_SetCycleState
(
    VAR( Dem_u08_CycleQualifiedIndexType, AUTOMATIC ) CycleQualifiedIndex,
    VAR( Dem_OperationCycleStateType, AUTOMATIC ) CycleState
)
{
    VAR( Dem_u08_CycleQualifiedIndexType, AUTOMATIC ) cycleQualifiedNum;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindOpCycle;

    cycleQualifiedNum = Dem_OperationCycleRecordStateNum;

    if( CycleQualifiedIndex < cycleQualifiedNum )                               /* [GUD:if]CycleQualifiedIndex */
    {
        if( Dem_OpCycleRecord.CycleState[CycleQualifiedIndex] != CycleState )   /* [GUD]CycleQualifiedIndex */
        {
            Dem_OpCycleRecord.ClearID = Dem_ClrInfoMng_GetObdClearID();
            recMngCmnKindOpCycle = Dem_RecMngCmnKindOpCycle;
            Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindOpCycle, ( Dem_u16_RecordIndexType )0U );
        }

        Dem_OpCycleRecord.CycleState[CycleQualifiedIndex] = CycleState;         /* [GUD]CycleQualifiedIndex */
    }

    return ;
}

/****************************************************************************/
/* Function Name | Dem_OpCycleMng_GetCycleState                             */
/* Description   | Gets operation cycle state by operation cycle index.     */
/* Preconditions | none                                                     */
/* Parameters    | [in] CycleQualifiedIndex : cycle qualified index.        */
/* Return Value  | Dem_OperationCycleStateType                              */
/*               |    DEM_CYCLE_NOTIFY_START                                */
/*               |           : Operation cycle is notified.                 */
/*               |    DEM_CYCLE_NOTIFY_END                                  */
/*               |           : Operation cycle is not notified.             */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_OperationCycleStateType, DEM_CODE ) Dem_OpCycleMng_GetCycleState
(
    VAR( Dem_u08_CycleQualifiedIndexType, AUTOMATIC ) CycleQualifiedIndex
)
{
    VAR( Dem_u08_CycleQualifiedIndexType, AUTOMATIC ) cycleQualifiedNum;
    VAR( Dem_OperationCycleStateType, AUTOMATIC ) cycleState;

    cycleQualifiedNum = Dem_OperationCycleRecordStateNum;
    cycleState = DEM_CYCLE_NOTIFY_END;

    if( CycleQualifiedIndex < cycleQualifiedNum )           /* [GUD:if]CycleQualifiedIndex */
    {
        cycleState = Dem_OpCycleRecord.CycleState[CycleQualifiedIndex];     /* [GUD]CycleQualifiedIndex */
    }

    return cycleState;
}

#if ( DEM_PFC_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_OpCycleMng_SetPFCCycleClearConditionCheckStatus      */
/* Description   | Set PFCCycle ClearConditionCheck disable flag.           */
/* Preconditions | none                                                     */
/* Parameters    | [in] PFCClearConditionCheckStatus                        */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_OpCycleMng_SetPFCCycleClearConditionCheckStatus
(
    VAR( Dem_u08_PFCClearCondCheckStatusType, AUTOMATIC ) PFCClearConditionCheckStatus
)
{
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindOpCycle;

    if ( Dem_OpCycleRecord.PFCClearConditionCheckStatus != PFCClearConditionCheckStatus )
    {
        recMngCmnKindOpCycle = Dem_RecMngCmnKindOpCycle;
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindOpCycle, ( Dem_u16_RecordIndexType )0U );
    }
    Dem_OpCycleRecord.PFCClearConditionCheckStatus    =   PFCClearConditionCheckStatus;

    return ;
}

/****************************************************************************/
/* Function Name | Dem_OpCycleMng_GetPFCCycleClearConditionCheckStatus      */
/* Description   | Get PFCCycle ClearConditionCheck disable flag.           */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_PFCClearCondCheckStatusType                      */
/*               |    DEM_PFC_CLEARCONDCHKSTATUS_DISABLE   : check disable. */
/*               |    DEM_PFC_CLEARCONDCHKSTATUS_ENABLE    : check enable.  */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_PFCClearCondCheckStatusType, DEM_CODE ) Dem_OpCycleMng_GetPFCCycleClearConditionCheckStatus
( void )
{
    VAR( Dem_u08_PFCClearCondCheckStatusType, AUTOMATIC ) pfcClearConditionCheckStatus;

    pfcClearConditionCheckStatus   =   DEM_PFC_CLEARCONDCHKSTATUS_ENABLE;

    if ( Dem_OpCycleRecord.PFCClearConditionCheckStatus == DEM_PFC_CLEARCONDCHKSTATUS_DISABLE )
    {
        pfcClearConditionCheckStatus   =   DEM_PFC_CLEARCONDCHKSTATUS_DISABLE;
    }
    return pfcClearConditionCheckStatus;
}
#endif  /*  ( DEM_PFC_SUPPORT == STD_ON )   */

/****************************************************************************/
/* Function Name | Dem_OpCycleMng_ClearCycleState                           */
/* Description   | Clear operation cycle state.                             */
/* Preconditions | none                                                     */
/* Parameters    | [in] UpdateNvMMode : DEM_OPCYCMNG_UPD_RAM                */
/*               |                      DEM_OPCYCMNG_UPD_NVM_RAMDIFF        */
/*               |                      DEM_OPCYCMNG_UPD_NVM_FORCE          */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_OpCycleMng_ClearCycleState
(
    VAR( Dem_u08_UpdNvMType, AUTOMATIC ) UpdateNvMMode
)
{
    VAR( boolean, AUTOMATIC ) updateNvM;
    VAR( boolean, AUTOMATIC ) obdResetDrivingCycleQualifiedAtClearDTC;
    VAR( Dem_u08_CycleQualifiedIndexType, AUTOMATIC ) obdDcyIndex;
    VAR( Dem_u08_CycleQualifiedIndexType, AUTOMATIC ) warmUpCycleIndex;
    VAR( Dem_u08_CycleQualifiedIndexType, AUTOMATIC ) pfcCycleIndex;
#if ( DEM_OBD_MASTER_SUPPORT == STD_ON )   /*  [FuncSw]     */
    VAR( Dem_u08_CycleQualifiedIndexType, AUTOMATIC ) engine4000rpmOccurredIndex;
#endif  /*   ( DEM_OBD_MASTER_SUPPORT == STD_ON )           */
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindOpCycle;

    updateNvM = (boolean)FALSE;
    obdDcyIndex         = Dem_ConfDemOperationCycleObdDcy;              /* [GUD:CFG]obdDcyIndex */
    warmUpCycleIndex    = Dem_ConfDemOperationCycleWarmUp;              /* [GUD:CFG]warmUpCycleIndex */
    pfcCycleIndex       = Dem_ConfDemOperationCyclePFCCycle;            /* [GUD:CFG]pfcCycleIndex */
#if ( DEM_OBD_MASTER_SUPPORT == STD_ON )   /*  [FuncSw]     */
    engine4000rpmOccurredIndex  =   Dem_ConfDemOperationCycleEngine4000RPMOccurred;     /* [GUD:CFG]engine4000rpmOccurredIndex */

#endif  /*   ( DEM_OBD_MASTER_SUPPORT == STD_ON )           */

    obdResetDrivingCycleQualifiedAtClearDTC    =   Dem_OBDResetDrivingCycleQualifiedAtClearDTC;

    if( UpdateNvMMode == DEM_OPCYCMNG_UPD_NVM_RAMDIFF )
    {
#if ( DEM_OBD_MASTER_SUPPORT == STD_ON )   /*  [FuncSw]     */
        if ( Dem_OpCycleRecord.CycleState[engine4000rpmOccurredIndex] != DEM_CYCLE_NOTIFY_END )     /* [GUD]engine4000rpmOccurredIndex */
        {
            updateNvM  = (boolean)TRUE;
        }
        else
#endif  /*   ( DEM_OBD_MASTER_SUPPORT == STD_ON )           */
        if( ( Dem_OpCycleRecord.CycleState[warmUpCycleIndex] != DEM_CYCLE_NOTIFY_END ) ||           /* [GUD]warmUpCycleIndex */
            ( Dem_OpCycleRecord.CycleState[pfcCycleIndex]    != DEM_CYCLE_NOTIFY_END ) )            /* [GUD]pfcCycleIndex */
        {
            updateNvM  = (boolean)TRUE;
        }
        else
        {
            if ( obdResetDrivingCycleQualifiedAtClearDTC == (boolean)TRUE )
            {
                /*  clear data : obddcy     */
                if( Dem_OpCycleRecord.CycleState[obdDcyIndex] != DEM_CYCLE_NOTIFY_END )             /* [GUD]obdDcyIndex */
                {
                    updateNvM  = (boolean)TRUE;
                }
            }
        }
    }
    else if( UpdateNvMMode == DEM_OPCYCMNG_UPD_NVM_FORCE )
    {
        updateNvM  = (boolean)TRUE;
    }
    else
    {
        /* When UpdateNvMMode is DEM_OPCYCMNG_UPD_RAM */
        /* No Process */
    }

    Dem_OpCycleRecord.CycleState[warmUpCycleIndex]  = DEM_CYCLE_NOTIFY_END;                 /* [GUD]warmUpCycleIndex */
    Dem_OpCycleRecord.CycleState[pfcCycleIndex]     = DEM_CYCLE_NOTIFY_END;                 /* [GUD]pfcCycleIndex */
#if ( DEM_OBD_MASTER_SUPPORT == STD_ON )   /*  [FuncSw]     */
    Dem_OpCycleRecord.CycleState[engine4000rpmOccurredIndex]    = DEM_CYCLE_NOTIFY_END;     /* [GUD]engine4000rpmOccurredIndex */
#endif  /*   ( DEM_OBD_MASTER_SUPPORT == STD_ON )           */

    if ( obdResetDrivingCycleQualifiedAtClearDTC == (boolean)TRUE )
    {
        Dem_OpCycleRecord.CycleState[obdDcyIndex]     = DEM_CYCLE_NOTIFY_END;   /*  clear : obddcy      */  /* [GUD]obdDcyIndex */
    }

    Dem_OpCycleRecord.ClearID = Dem_ClrInfoMng_GetObdClearID();

    if( updateNvM == (boolean)TRUE )
    {
        recMngCmnKindOpCycle = Dem_RecMngCmnKindOpCycle;
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindOpCycle, (Dem_u16_RecordIndexType)0U );
    }

    return;
}

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_OpCycleMng_CopyOpCycleStatusToMirror                 */
/* Description   | Copy Dem_OperationCycleState in Dem_OpCycleMirror        */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/*               | [in/out] BlockMirrorPtr :                                */
/*               |        Nonvolatile synchronous data information.         */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_OpCycleMng_CopyOpCycleStatusToMirror
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
)
{
    Dem_OpCycleMng_GetRecordData( &Dem_OpCycleRecordMirror );
    BlockMirrorPtr->MirrorPtr = &Dem_OpCycleRecordMirror;

    return ;
}

#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_OpCycleMng_InitRecordData                            */
/* Description   | Initializes the operation cycle record data.             */
/* Preconditions | none                                                     */
/* Parameters    | [in] OpCycleRecordPtr    :                               */
/*               |       The pointer of the operation cycle record.         */
/*               |       &Dem_OpCycleRecord -DEM_VAR_SAVED_ZONE-            */
/*               |       &Dem_OpCycleRecordMirror -DEM_VAR_NO_INIT-         */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_OpCycleMng_InitRecordData
(
    P2VAR( Dem_OpCycleRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) OpCycleRecordPtr
)
{
    VAR( Dem_u08_CycleQualifiedIndexType, AUTOMATIC ) cycleQualifiedNum;
    VAR( Dem_u08_CycleQualifiedIndexType, AUTOMATIC ) cycleQualifiedIndex;

    cycleQualifiedNum = Dem_OperationCycleRecordStateNum;

    /* Init cycle state.        */
    for( cycleQualifiedIndex = (Dem_u08_CycleQualifiedIndexType)0U; cycleQualifiedIndex < cycleQualifiedNum; cycleQualifiedIndex++ )    /* [GUD:for]cycleQualifiedIndex */
    {
        OpCycleRecordPtr->CycleState[cycleQualifiedIndex] = DEM_CYCLE_NOTIFY_END;   /* [GUD]cycleQualifiedIndex */
    }

    /* Init clear identifier.   */
    OpCycleRecordPtr->ClearID = DEM_CLRINFO_RECORD_INITIAL;
    OpCycleRecordPtr->PFCClearConditionCheckStatus    =   DEM_PFC_CLEARCONDCHKSTATUS_ENABLE;

    /* Init padding area.       */
    Dem_OpCycleMng_InitPadding( OpCycleRecordPtr );

    return ;
}

/****************************************************************************/
/* Function Name | Dem_OpCycleMng_InitPadding                               */
/* Description   | Initializes the operation cycle record padding data.     */
/* Preconditions | none                                                     */
/* Parameters    | [in] OpCycleRecordPtr    :                               */
/*               |       The pointer of the operation cycle record.         */
/*               |       &Dem_OpCycleRecord -DEM_VAR_SAVED_ZONE-            */
/*               |       &Dem_OpCycleRecordMirror -DEM_VAR_NO_INIT-         */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_OpCycleMng_InitPadding
(
    P2VAR( Dem_OpCycleRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) OpCycleRecordPtr
)
{
    VAR( Dem_u16_PaddingIndexType, AUTOMATIC ) opCycleRecordBlockPaddingSize;
    VAR( Dem_u16_PaddingIndexType, AUTOMATIC ) paddingIndex;

    opCycleRecordBlockPaddingSize = Dem_OpCycleRecordBlockPaddingSize;

    for( paddingIndex = (Dem_u16_PaddingIndexType)0U; paddingIndex < opCycleRecordBlockPaddingSize; paddingIndex++ )    /* [GUD:for]paddingIndex */
    {
        OpCycleRecordPtr->Reserve[paddingIndex] = DEM_CYCLE_NOTIFY_END;     /* [GUD]paddingIndex */
    }
    return ;
}

/****************************************************************************/
/* Function Name | Dem_OpCycleMng_InitOperationCycleMirror                  */
/* Description   | Init operation cycle record mirror data.                 */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_OpCycleMng_InitOperationCycleMirror
( void )
{
    Dem_OpCycleMng_InitRecordData( &Dem_OpCycleRecordMirror );
    return ;
}

/****************************************************************************/
/* Function Name | Dem_OpCycleMng_GetRecordData                             */
/* Description   | Gets the operation cycle record data.                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] OpCycleRecordPtr    :                               */
/*               |       The pointer of the operation cycle record.         */
/*               |       &Dem_OpCycleRecordMirror -DEM_VAR_NO_INIT-         */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_OpCycleMng_GetRecordData
(
    P2VAR( Dem_OpCycleRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) OpCycleRecordPtr
)
{
    VAR( Dem_u08_CycleQualifiedIndexType, AUTOMATIC ) cycleQualifiedNum;
    VAR( Dem_u08_CycleQualifiedIndexType, AUTOMATIC ) cycleQualifiedIndex;
    VAR( Dem_u16_PaddingIndexType, AUTOMATIC ) opCycleRecordBlockPaddingSize;
    VAR( Dem_u16_PaddingIndexType, AUTOMATIC ) paddingIndex;

    cycleQualifiedNum = Dem_OperationCycleRecordStateNum;
    opCycleRecordBlockPaddingSize = Dem_OpCycleRecordBlockPaddingSize;

    /* Get cycle state.         */
    for( cycleQualifiedIndex = (Dem_u08_CycleQualifiedIndexType)0U; cycleQualifiedIndex < cycleQualifiedNum; cycleQualifiedIndex++ )    /* [GUD:for]cycleQualifiedIndex */
    {
        OpCycleRecordPtr->CycleState[cycleQualifiedIndex] = Dem_OpCycleRecord.CycleState[cycleQualifiedIndex];          /* [GUD]cycleQualifiedIndex */
    }

    /* Get clear identifier.    */
    OpCycleRecordPtr->ClearID = Dem_OpCycleRecord.ClearID;
    OpCycleRecordPtr->PFCClearConditionCheckStatus    =   Dem_OpCycleRecord.PFCClearConditionCheckStatus;

    /* Get padding area.        */
    for( paddingIndex = (Dem_u16_PaddingIndexType)0U; paddingIndex < opCycleRecordBlockPaddingSize; paddingIndex++ )    /* [GUD:for]paddingIndex */
    {
        OpCycleRecordPtr->Reserve[paddingIndex] = Dem_OpCycleRecord.Reserve[paddingIndex];                              /* [GUD]paddingIndex */
    }

    return ;
}

#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */


/****************************************************************************/
/* Function Name | Dem_OpCycleMng_ClearInfoVerify                           */
/* Description   | Verify the clear identifier data.                        */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_OpCycleMng_ClearInfoVerify
( void )
{
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) clearID;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = Dem_ClrInfoMng_GetNvmReadResult();
    if( retVal == DEM_IRT_NG )
    {
        Dem_OpCycleMng_ClearCycleState( DEM_OPCYCMNG_UPD_NVM_FORCE );
    }
    else
    {
        clearID = Dem_ClrInfoMng_GetObdClearID();
        if( clearID != Dem_OpCycleRecord.ClearID )
        {
            Dem_OpCycleMng_ClearCycleState( DEM_OPCYCMNG_UPD_RAM );
        }
        else
        {
            /* No Process */
        }
    }

    return ;
}

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_OpCycleMng_GetEventIdFromRecordData                  */
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
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_OpCycleMng_GetEventIdFromRecordData
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

#endif /* DEM_CYCLEQUALIFIED_SUPPORT -STD_ON- */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2019-03-27                                              */
/*  v3-0-0         :2019-07-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
