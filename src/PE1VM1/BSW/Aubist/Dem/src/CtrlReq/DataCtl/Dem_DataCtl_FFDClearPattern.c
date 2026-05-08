/* Dem_DataCtl_FFDClearPattern_c(v5-10-0)                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_FFDClearPattern/CODE                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "Dem_DataCtl_FFDClearPatternTable.h"
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

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
static FUNC( boolean, DEM_CODE ) Dem_DataCtl_GetClearTarget_OBDFFD
(
    VAR( Dem_u08_FaultRecoveryIndexType, AUTOMATIC ) RecoveryMode,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus,
    P2VAR( Dem_FFListRecordForClrType, AUTOMATIC, AUTOMATIC ) ClearFFListRecordPtr
);
#endif  /*   ( DEM_OBDFFD_SUPPORT == STD_ON )       */

static FUNC( boolean, DEM_CODE ) Dem_DataCtl_GetClearTarget_NonOBDFFD
(
    VAR( Dem_u08_FaultRecoveryIndexType, AUTOMATIC ) RecoveryMode,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus,
    P2VAR( Dem_FFListRecordForClrType, AUTOMATIC, AUTOMATIC ) ClearFFListRecordPtr
);

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
static FUNC( boolean, DEM_CODE ) Dem_DataCtl_GetClearTarget_TSFFD
(
    VAR( Dem_u08_FaultRecoveryIndexType, AUTOMATIC ) RecoveryMode,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus,
    P2VAR( Dem_FFListRecordForClrType, AUTOMATIC, AUTOMATIC ) ClearFFListRecordPtr
);
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON )   */

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
static FUNC( boolean, DEM_CODE ) Dem_DataCtl_GetExecClearOBDFFD
(
    VAR( Dem_u08_FaultRecoveryIndexType, AUTOMATIC ) RecoveryMode,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger
);
#endif  /*   ( DEM_OBDFFD_SUPPORT == STD_ON )       */
static FUNC( boolean, DEM_CODE ) Dem_DataCtl_GetExecClearNonOBDFFD
(
    VAR( Dem_u08_FaultRecoveryIndexType, AUTOMATIC ) RecoveryMode,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger
);

static FUNC( Dem_u08_ClearPtnAtDTCStatusType, DEM_CODE ) Dem_DataCtl_GetClearPatternBit
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
);
static FUNC( Dem_u08_FFDTriggerIndexType, DEM_CODE ) Dem_DataCtl_GetFFDTriggerIndex
(
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger
);
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
static FUNC( Dem_u08_StorageTriggerType, DEM_CODE ) Dem_DataCtl_GetFFDRecordTrigger
(
    VAR( Dem_u08_FFDTriggerIndexType, AUTOMATIC ) FFDTriggerIdx
);
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )     */


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
/* Function Name | Dem_DataCtl_GetClearTargetFaultRecord                    */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] RecoveryMode :                                      */
/*               | [in] DTCStatus :                                         */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : clear FaultRecord                         */
/*               |                if all FFD record index cleared.          */
/*               |        FALSE : not clear FaultRecord.                    */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_DataCtl_GetClearTargetFaultRecord
(
    VAR( Dem_u08_FaultRecoveryIndexType, AUTOMATIC ) RecoveryMode,      /* [PRMCHK:CALLER] */
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
)
{
    VAR( Dem_u08_ClearPtnAtDTCStatusType, AUTOMATIC ) clearPtnBit;
    VAR( Dem_u08_ClearPtnAtDTCStatusType, AUTOMATIC ) clearFault;
    VAR( boolean, AUTOMATIC ) clearFaultFlag;

    clearFaultFlag  =   (boolean)FALSE;

    clearPtnBit =   Dem_DataCtl_GetClearPatternBit( DTCStatus );
    clearFault  =   Dem_FaultClearPattenTable[ RecoveryMode ];      /* [GUDCHK:CALLER]RecoveryMode */

    if ( ( clearFault & clearPtnBit ) == clearPtnBit )
    {
        clearFaultFlag  =   (boolean)TRUE;
    }

    return clearFaultFlag;
}


/****************************************************************************/
/* Function Name | Dem_DataCtl_GetClearTargetFFRecord                       */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] RecoveryMode :                                      */
/*               | [in] EventStrgIndex :                                    */
/*               | [in] DTCStatus :                                         */
/*               | [out] ClearFFListRecordPtr                               */
/* Return Value  | boolean                                                  */
/*               |        TRUE  :   it's will be update FFD record index    */
/*               |                  in FaultRecord for clear.               */
/*               |        FALSE : not update FFD record index.              */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_DataCtl_GetClearTargetFFRecord
(
    VAR( Dem_u08_FaultRecoveryIndexType, AUTOMATIC ) RecoveryMode,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,        /* [PRMCHK:CALLER] */
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus,
    P2VAR( Dem_FFListRecordForClrType, AUTOMATIC, AUTOMATIC ) ClearFFListRecordPtr
)
{
    VAR( boolean, AUTOMATIC ) updateFFDRecInfo;
    VAR( boolean, AUTOMATIC ) updateFFDRecInfoAtFFD;

    updateFFDRecInfo = (boolean)FALSE;

#if ( DEM_OBDFFD_SUPPORT == STD_ON )   /* [FuncSw] */
    updateFFDRecInfoAtFFD = Dem_DataCtl_GetClearTarget_OBDFFD( RecoveryMode, EventStrgIndex, DTCStatus, ClearFFListRecordPtr );     /* [GUDCHK:CALLER]EventStrgIndex */
    if( updateFFDRecInfoAtFFD == (boolean)TRUE )
    {
        updateFFDRecInfo = (boolean)TRUE;
    }
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )         */

    updateFFDRecInfoAtFFD = Dem_DataCtl_GetClearTarget_NonOBDFFD( RecoveryMode, EventStrgIndex, DTCStatus, ClearFFListRecordPtr );  /* [GUDCHK:CALLER]EventStrgIndex */
    if( updateFFDRecInfoAtFFD == (boolean)TRUE )
    {
        updateFFDRecInfo = (boolean)TRUE;
    }

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )    /* [FuncSw] */
    updateFFDRecInfoAtFFD = Dem_DataCtl_GetClearTarget_TSFFD( RecoveryMode, EventStrgIndex, DTCStatus, ClearFFListRecordPtr );      /* [GUDCHK:CALLER]EventStrgIndex */
    if( updateFFDRecInfoAtFFD == (boolean)TRUE )
    {
        updateFFDRecInfo = (boolean)TRUE;
    }
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON )   */

    return updateFFDRecInfo;
}

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataCtl_ClearTargetMisfCylinderFFD                   */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] RecoveryMode :                                      */
/*               | [in] EventStrgIndex :                                    */
/*               | [in] DTCStatus :                                         */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataCtl_ClearTargetMisfCylinderFFD
(
    VAR( Dem_u08_FaultRecoveryIndexType, AUTOMATIC ) RecoveryMode,      /* [PRMCHK:CALLER] */
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
)
{
    VAR( Dem_u08_FFDTriggerIndexType, AUTOMATIC ) ffdTriggerIdx;
    VAR( Dem_u08_ClearPtnAtDTCStatusType, AUTOMATIC ) clearPtnBit;
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    VAR( Dem_u08_ClearPtnAtDTCStatusType, AUTOMATIC ) clearOBDFFD;
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
    VAR( Dem_u08_ClearPtnAtDTCStatusType, AUTOMATIC ) clearFFD;
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) freezeFrameRecordTrigger;

    clearPtnBit                 =   Dem_DataCtl_GetClearPatternBit( DTCStatus );
    for ( ffdTriggerIdx = (Dem_u08_FFDTriggerIndexType)0U; ffdTriggerIdx < DEM_FFDTRIGGER_IDX_MAX; ffdTriggerIdx++ )        /* [GUD:for]ffdTriggerIdx */
    {
        freezeFrameRecordTrigger    =   Dem_DataCtl_GetFFDRecordTrigger( ffdTriggerIdx );                                   /* [GUD]ffdTriggerIdx */

#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
        clearOBDFFD     =   Dem_FFDClearPatten_OBDFFD_Table[ ffdTriggerIdx ].RecoveryTypeArray[ RecoveryMode ];             /* [GUD]ffdTriggerIdx *//* [GUDCHK:CALLER]RecoveryMode */
        if ( ( clearOBDFFD & clearPtnBit ) == clearPtnBit )
        {
            Dem_Misfire_ClearDataRelatedObdFFD( EventStrgIndex, freezeFrameRecordTrigger );
        }
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */

        clearFFD        =   Dem_FFDClearPatten_NonOBDFFD_Table[ ffdTriggerIdx ].RecoveryTypeArray[ RecoveryMode ];          /* [GUD]ffdTriggerIdx *//* [GUDCHK:CALLER]RecoveryMode */
        if ( ( clearFFD & clearPtnBit ) == clearPtnBit )
        {
            Dem_Misfire_ClearDataRelatedFFD( EventStrgIndex, freezeFrameRecordTrigger );
        }
    }

    return ;
}
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )     */


#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataCtl_GetClearTarget_OBDFFD                        */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] RecoveryMode :                                      */
/*               | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the event ID.    */
/*               | [in] DTCStatus :                                         */
/*               | [out] ClearFFListRecordPtr :                             */
/*               |        Clear information of FreezeFrameListRecord.       */
/* Return Value  | boolean                                                  */
/*               |        TRUE  :   it's will be update FFD record index    */
/*               |                  in FaultRecord for clear.               */
/*               |        FALSE : not update FFD record index.              */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/*   v5-8-0      | branch changed.                                          */
/*   v5-10-0     | no branch changed.                                       */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_DataCtl_GetClearTarget_OBDFFD
(
    VAR( Dem_u08_FaultRecoveryIndexType, AUTOMATIC ) RecoveryMode,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus,
    P2VAR( Dem_FFListRecordForClrType, AUTOMATIC, AUTOMATIC ) ClearFFListRecordPtr
)
{
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) obdFreezeFrameClassRef;
    VAR( Dem_u16_FFRecNumClassIndexType, AUTOMATIC ) obdFreezeframeRecNumClassRef;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) freezeFrameRecordClassRefIndex;
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC ) freezeFrameRecordClassIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) obdFFRClassPerDTCMaxNum;
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC ) ffrRecordClassConfigureNum;
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) ffRecordTrigger;
    VAR( boolean, AUTOMATIC ) clearFFDFlag;
    VAR( boolean, AUTOMATIC ) updateFFDRecInfo;
    VAR( boolean, AUTOMATIC ) chkIsFFD;

    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA ) freezeFrameRecNumClassPtr;

    /* Initializes the auto variable. */
    updateFFDRecInfo = (boolean)FALSE;
    chkIsFFD         = (boolean)TRUE;

    /* Checks the reference of freeze frame class. */
    Dem_CfgInfoPm_GetOBDFreezeFrameAndRecNumClassForClear( EventStrgIndex, &obdFreezeFrameClassRef, &obdFreezeframeRecNumClassRef );    /* [GUD:OUT:Not DEM_FFCLASSINDEX_INVALID] obdFreezeFrameClassRef *//* [GUD:OUT:Not DEM_FFRECNUMCLASSINDEX_INVALID] obdFreezeframeRecNumClassRef */
    Dem_CfgInfoPm_GetNumOfOBDFreezeFrameRecordClass( &ffrRecordClassConfigureNum, &obdFFRClassPerDTCMaxNum );

    if( obdFreezeFrameClassRef != DEM_FFCLASSINDEX_INVALID )                                                                    /* [GUD:if] obdFreezeFrameClassRef */
    {
        /* Checks the reference of freeze frame record number class. */
        if( obdFreezeframeRecNumClassRef != DEM_FFRECNUMCLASSINDEX_INVALID )                                                    /* [GUD:if] obdFreezeframeRecNumClassRef */
        {
            /* Holds the FreezeFrameRecNumClass table pointed to */
            /* by the FreezeFrameRecNumClass table list Index of the held DTCAttribute table. */
            freezeFrameRecNumClassPtr = &Dem_FreezeFrameRecNumClassTable[ obdFreezeframeRecNumClassRef ];                       /* [GUD] obdFreezeframeRecNumClassRef */

            for( freezeFrameRecordClassRefIndex = (Dem_u08_FFListIndexType)0U; freezeFrameRecordClassRefIndex < obdFFRClassPerDTCMaxNum; freezeFrameRecordClassRefIndex++ )     /* [GUD:for] freezeFrameRecordClassRefIndex */
            {
                /* Holds the DemFreezeFrameRecordIndex pointed to */
                /* by the DemFreezeFrameRecordClassRef Index of the held FreezeFrameRecNumClass table. */
                freezeFrameRecordClassIndex = freezeFrameRecNumClassPtr->DemFreezeFrameRecordClassRef[freezeFrameRecordClassRefIndex];          /* [GUD] freezeFrameRecordClassRefIndex *//* [ARYCHK] DEM_FF_RECORD_CLASS_REF_MAX_NUM / 1 / freezeFrameRecordClassRefIndex */
                if( freezeFrameRecordClassIndex < ffrRecordClassConfigureNum )                                                                  /* [GUD:if] freezeFrameRecordClassIndex */
                {
                    /* Holds the FreezeFrameRecordClass table pointed to by DemFreezeFrameRecordIndex. */
                    ffRecordTrigger =   Dem_CfgInfoPm_GetFreezeFrameRecordTriggerType( freezeFrameRecordClassIndex );                           /* [GUD] freezeFrameRecordClassIndex */

                    clearFFDFlag    =   Dem_DataCtl_GetExecClearOBDFFD( RecoveryMode, DTCStatus, ffRecordTrigger );
                    ClearFFListRecordPtr->ObdFFRClrFlg[freezeFrameRecordClassRefIndex] = clearFFDFlag;                                          /* [GUD] freezeFrameRecordClassRefIndex *//* [ARYCHK] DEM_OBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / freezeFrameRecordClassRefIndex */
                    if ( clearFFDFlag == (boolean)TRUE )
                    {
                        updateFFDRecInfo    =   (boolean)TRUE;
                    }
                }
                else
                {
                    ClearFFListRecordPtr->ObdFFRClrFlg[freezeFrameRecordClassRefIndex] = (boolean)FALSE;                                        /* [GUD] freezeFrameRecordClassRefIndex *//* [ARYCHK] DEM_OBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / freezeFrameRecordClassRefIndex */
                }
            }
        }
        else
        {
            /* DTC without DemFreezeFrameRecNumClass */
            chkIsFFD     = (boolean)FALSE;
        }
    }
    else
    {
        /* DTC without DemFreezeFrameClass */
        chkIsFFD     = (boolean)FALSE;
    }

    if ( chkIsFFD == (boolean)FALSE )
    {
        /*  all clear.      */
        for( freezeFrameRecordClassRefIndex = (Dem_u08_FFListIndexType)0U; freezeFrameRecordClassRefIndex < obdFFRClassPerDTCMaxNum; freezeFrameRecordClassRefIndex++ )     /* [GUD:for] freezeFrameRecordClassRefIndex */
        {
            ClearFFListRecordPtr->ObdFFRClrFlg[freezeFrameRecordClassRefIndex] = (boolean)FALSE;                                        /* [GUD] freezeFrameRecordClassRefIndex *//* [ARYCHK] DEM_OBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / freezeFrameRecordClassRefIndex */
        }
    }

    return updateFFDRecInfo;
}
#endif /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */

/****************************************************************************/
/* Function Name | Dem_DataCtl_GetClearTarget_NonOBDFFD                     */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] RecoveryMode :                                      */
/*               | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the event ID.    */
/*               | [in] DTCStatus :                                         */
/*               | [out] ClearFFListRecordPtr :                             */
/*               |        Clear information of FreezeFrameListRecord.       */
/* Return Value  | boolean                                                  */
/*               |        TRUE  :   it's will be update FFD record index    */
/*               |                  in FaultRecord for clear.               */
/*               |        FALSE : not update FFD record index.              */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/*   v5-8-0      | branch changed.                                          */
/*   v5-10-0     | no branch changed.                                       */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_DataCtl_GetClearTarget_NonOBDFFD
(
    VAR( Dem_u08_FaultRecoveryIndexType, AUTOMATIC ) RecoveryMode,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus,
    P2VAR( Dem_FFListRecordForClrType, AUTOMATIC, AUTOMATIC ) ClearFFListRecordPtr
)
{
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) freezeFrameClassRef;
    VAR( Dem_u16_FFRecNumClassIndexType, AUTOMATIC ) freezeframeRecNumClassRef;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) freezeFrameRecordClassRefIndex;
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC ) freezeFrameRecordClassIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonOBDFFRClassPerDTCMaxNum;
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC ) ffrRecordClassConfigureNum;
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) ffRecordTrigger;
    VAR( boolean, AUTOMATIC ) clearFFDFlag;
    VAR( boolean, AUTOMATIC ) updateFFDRecInfo;
    VAR( boolean, AUTOMATIC ) chkIsFFD;

    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA ) freezeFrameRecNumClassPtr;

    /* Initializes the auto variable. */
    updateFFDRecInfo = (boolean)FALSE;
    chkIsFFD         = (boolean)TRUE;

    /* Checks the reference of freeze frame class. */
    Dem_CfgInfoPm_GetFreezeFrameAndRecNumClass( EventStrgIndex, &freezeFrameClassRef, &freezeframeRecNumClassRef ); /* [GUD:OUT:Not DEM_FFCLASSINDEX_INVALID] freezeFrameClassRef *//* [GUD:OUT:Not DEM_FFRECNUMCLASSINDEX_INVALID] freezeframeRecNumClassRef */
    Dem_CfgInfoPm_GetNumOfFreezeFrameRecordClass( &ffrRecordClassConfigureNum, &nonOBDFFRClassPerDTCMaxNum );

    if( freezeFrameClassRef != DEM_FFCLASSINDEX_INVALID )                                                           /* [GUD:if] freezeFrameClassRef */
    {
        /* Checks the reference of freeze frame record number class. */
        if( freezeframeRecNumClassRef != DEM_FFRECNUMCLASSINDEX_INVALID )                                           /* [GUD:if] freezeframeRecNumClassRef */
        {
            /* Holds the FreezeFrameRecNumClass table pointed to */
            /* by the FreezeFrameRecNumClass table list Index of the held DTCAttribute table. */
            freezeFrameRecNumClassPtr = &Dem_FreezeFrameRecNumClassTable[freezeframeRecNumClassRef];                /* [GUD] freezeframeRecNumClassRef */

            for( freezeFrameRecordClassRefIndex = (Dem_u08_FFListIndexType)0U; freezeFrameRecordClassRefIndex < nonOBDFFRClassPerDTCMaxNum; freezeFrameRecordClassRefIndex++ )  /* [GUD:for] freezeFrameRecordClassRefIndex */
            {
                /* Holds the DemFreezeFrameRecordIndex pointed to */
                /* by the DemFreezeFrameRecordClassRef Index of the held FreezeFrameRecNumClass table. */
                freezeFrameRecordClassIndex = freezeFrameRecNumClassPtr->DemFreezeFrameRecordClassRef[freezeFrameRecordClassRefIndex];  /* [GUD] freezeFrameRecordClassRefIndex *//* [ARYCHK] DEM_FF_RECORD_CLASS_REF_MAX_NUM / 1 / freezeFrameRecordClassRefIndex */
                if( freezeFrameRecordClassIndex < ffrRecordClassConfigureNum )                                                          /* [GUD:if] freezeFrameRecordClassIndex */
                {
                    /* Holds the FreezeFrameRecordClass table pointed to by DemFreezeFrameRecordIndex. */
                    ffRecordTrigger =   Dem_CfgInfoPm_GetFreezeFrameRecordTriggerType( freezeFrameRecordClassIndex );                   /* [GUD] freezeFrameRecordClassIndex */

                    clearFFDFlag    =   Dem_DataCtl_GetExecClearNonOBDFFD( RecoveryMode, DTCStatus, ffRecordTrigger );
                    ClearFFListRecordPtr->FFRClrFlg[freezeFrameRecordClassRefIndex] = clearFFDFlag;                                     /* [GUD] freezeFrameRecordClassRefIndex *//* [ARYCHK] DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / freezeFrameRecordClassRefIndex */
                    if ( clearFFDFlag == (boolean)TRUE )
                    {
                        updateFFDRecInfo    =   (boolean)TRUE;
                    }
                }
                else
                {
                    ClearFFListRecordPtr->FFRClrFlg[freezeFrameRecordClassRefIndex] = (boolean)FALSE;                                   /* [GUD] freezeFrameRecordClassRefIndex *//* [ARYCHK] DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / freezeFrameRecordClassRefIndex */
                }
            }
        }
        else
        {
            /* DTC without DemFreezeFrameRecNumClass */
            chkIsFFD     = (boolean)FALSE;
        }
    }
    else
    {
        /* DTC without DemFreezeFrameClass */
        chkIsFFD     = (boolean)FALSE;
    }

    if ( chkIsFFD == (boolean)FALSE )
    {
        /*  all clear.      */
        for( freezeFrameRecordClassRefIndex = (Dem_u08_FFListIndexType)0U; freezeFrameRecordClassRefIndex < nonOBDFFRClassPerDTCMaxNum; freezeFrameRecordClassRefIndex++ )  /* [GUD:for] freezeFrameRecordClassRefIndex */
        {
            ClearFFListRecordPtr->FFRClrFlg[freezeFrameRecordClassRefIndex] = (boolean)FALSE;                                   /* [GUD] freezeFrameRecordClassRefIndex *//* [ARYCHK] DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / freezeFrameRecordClassRefIndex */
        }
    }

    return updateFFDRecInfo;
}

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataCtl_GetClearTarget_TSFFD                         */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] RecoveryMode :                                      */
/*               | [in] EventStrgIndex :                                    */
/*               | [in] DTCStatus :                                         */
/*               | [out] ClearFFListRecordPtr :                             */
/* Return Value  | boolean                                                  */
/*               |        TRUE  :   it's will be update FFD record index    */
/*               |                  in FaultRecord for clear.               */
/*               |        FALSE : not update FFD record index.              */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/*   v5-8-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_DataCtl_GetClearTarget_TSFFD
(
    VAR( Dem_u08_FaultRecoveryIndexType, AUTOMATIC ) RecoveryMode,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus,
    P2VAR( Dem_FFListRecordForClrType, AUTOMATIC, AUTOMATIC ) ClearFFListRecordPtr
)
{
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsFFRecClassRefIndex;
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsffRecordClassNumPerDTCMaxNum;
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) tsFFRecClassRef;
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) ffRecordTrigger;
    VAR( boolean, AUTOMATIC ) clearFFDFlag;
    VAR( boolean, AUTOMATIC ) updateFFDRecInfo;

    P2CONST( AB_83_ConstV Dem_DTCAttributeType, AUTOMATIC, DEM_CONFIG_DATA ) dtcAttributePtr;

    /* Initializes the auto variable. */
    updateFFDRecInfo = (boolean)FALSE;
    tsffRecordClassNumPerDTCMaxNum = Dem_TSFFRecordClassNumPerDTCMaxNum;

    /* The DTCAttribute table indicated by the DTCAttribute table list Index of the held DTC table is held. */
    dtcAttributePtr =   Dem_CfgInfoPm_GetDTCAttrTablePtr_TSFF( EventStrgIndex );    /* [GUD:RET:Not NULL_PTR]dtcAttributePtr */

    if ( dtcAttributePtr != NULL_PTR )                                              /* [GUD:if]dtcAttributePtr */
    {
        for( tsFFRecClassRefIndex = (Dem_u08_TSFFListPerDTCIndexType)0U; tsFFRecClassRefIndex < tsffRecordClassNumPerDTCMaxNum; tsFFRecClassRefIndex++ )    /* [GUD:for] tsFFRecClassRefIndex */
        {
            tsFFRecClassRef = dtcAttributePtr->DemTimeSeriesFreezeFrameRecordClassRef[tsFFRecClassRefIndex];                                                /* [GUD]dtcAttributePtr *//* [GUD] tsFFRecClassRefIndex *//* [ARYCHK] DEM_TSFF_RECORD_CLASS_NUM_PER_DTC_MAX_NUM / 1 / tsFFRecClassRefIndex */

            if( tsFFRecClassRef != DEM_TSFF_RECORD_CLASS_REF_INVALID )                                                                                      /* [GUD:if] tsFFRecClassRef */
            {
                ffRecordTrigger = Dem_TSFFRecordClassTable[tsFFRecClassRef].DemTimeSeriesFreezeFrameTrigger;                                                /* [GUD] tsFFRecClassRef */

                clearFFDFlag    =   Dem_DataCtl_GetExecClearNonOBDFFD( RecoveryMode, DTCStatus, ffRecordTrigger );
                ClearFFListRecordPtr->TSFFLClrFlg[tsFFRecClassRefIndex] = clearFFDFlag;                                                                     /* [GUD] tsFFRecClassRefIndex *//* [ARYCHK] DEM_TSFF_RECORD_CLASS_NUM_PER_DTC_MAX_NUM / 1 / tsFFRecClassRefIndex */
                if ( clearFFDFlag == (boolean)TRUE )
                {
                    updateFFDRecInfo    =   (boolean)TRUE;
                }
            }
            else
            {
                /* DTC without TimeSeriesFreezeFrameRecordClass */
                ClearFFListRecordPtr->TSFFLClrFlg[tsFFRecClassRefIndex] = (boolean)FALSE;                                                                   /* [GUD] tsFFRecClassRefIndex *//* [ARYCHK] DEM_TSFF_RECORD_CLASS_NUM_PER_DTC_MAX_NUM / 1 / tsFFRecClassRefIndex */
            }
        }
    }
    else
    {
        for( tsFFRecClassRefIndex = (Dem_u08_TSFFListPerDTCIndexType)0U; tsFFRecClassRefIndex < tsffRecordClassNumPerDTCMaxNum; tsFFRecClassRefIndex++ )    /* [GUD:for] tsFFRecClassRefIndex */
        {
            /* DTC without TimeSeriesFreezeFrameRecordClass */
            ClearFFListRecordPtr->TSFFLClrFlg[tsFFRecClassRefIndex] = (boolean)FALSE;                                                                   /* [GUD] tsFFRecClassRefIndex *//* [ARYCHK] DEM_TSFF_RECORD_CLASS_NUM_PER_DTC_MAX_NUM / 1 / tsFFRecClassRefIndex */
        }
    }
    return updateFFDRecInfo;
}
#endif  /*   ( DEM_TSFF_PM_SUPPORT == STD_ON )     */

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataCtl_GetExecClearOBDFFD                           */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] RecoveryMode :                                      */
/*               | [in] DTCStatus :                                         */
/*               | [in] FreezeFrameRecordTrigger :                          */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : clear FFD.                                */
/*               |        FALSE : not clear FFD.                            */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_DataCtl_GetExecClearOBDFFD
(
    VAR( Dem_u08_FaultRecoveryIndexType, AUTOMATIC ) RecoveryMode,      /* [PRMCHK:CALLER] */
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger
)
{
    VAR( Dem_u08_ClearPtnAtDTCStatusType, AUTOMATIC ) clearPtnBit;
    VAR( Dem_u08_ClearPtnAtDTCStatusType, AUTOMATIC ) clearFFD;
    VAR( Dem_u08_FFDTriggerIndexType, AUTOMATIC ) ffdTriggerIdx;
    VAR( boolean, AUTOMATIC ) clearFFDFlag;

    clearFFDFlag    =   (boolean)FALSE;

    ffdTriggerIdx   =   Dem_DataCtl_GetFFDTriggerIndex( FreezeFrameRecordTrigger );                             /* [GUD:RET:AllValue] ffdTriggerIdx */
    clearPtnBit     =   Dem_DataCtl_GetClearPatternBit( DTCStatus );                                            /* [GUD:RET:AllValue] clearPtnBit */
    clearFFD        =   Dem_FFDClearPatten_OBDFFD_Table[ ffdTriggerIdx ].RecoveryTypeArray[ RecoveryMode ];     /* [GUD] ffdTriggerIdx *//* [GUDCHK:CALLER]RecoveryMode */

    if ( ( clearFFD & clearPtnBit ) == clearPtnBit )
    {
        clearFFDFlag    =   (boolean)TRUE;
    }

    return clearFFDFlag;
}
#endif  /*   ( DEM_OBDFFD_SUPPORT == STD_ON )      */


/****************************************************************************/
/* Function Name | Dem_DataCtl_GetExecClearNonOBDFFD                        */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] RecoveryMode :                                      */
/*               | [in] DTCStatus :                                         */
/*               | [in] FreezeFrameRecordTrigger :                          */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : clear FFD.                                */
/*               |        FALSE : not clear FFD.                            */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_DataCtl_GetExecClearNonOBDFFD
(
    VAR( Dem_u08_FaultRecoveryIndexType, AUTOMATIC ) RecoveryMode,      /* [PRMCHK:CALLER] */
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger
)
{
    VAR( Dem_u08_ClearPtnAtDTCStatusType, AUTOMATIC ) clearPtnBit;
    VAR( Dem_u08_ClearPtnAtDTCStatusType, AUTOMATIC ) clearFFD;
    VAR( Dem_u08_FFDTriggerIndexType, AUTOMATIC ) ffdTriggerIdx;
    VAR( boolean, AUTOMATIC ) clearFFDFlag;

    clearFFDFlag    =   (boolean)FALSE;

    ffdTriggerIdx   =   Dem_DataCtl_GetFFDTriggerIndex( FreezeFrameRecordTrigger );                             /* [GUD:RET:AllValue] ffdTriggerIdx */
    clearPtnBit     =   Dem_DataCtl_GetClearPatternBit( DTCStatus );                                            /* [GUD:RET:AllValue] clearPtnBit */
    clearFFD        =   Dem_FFDClearPatten_NonOBDFFD_Table[ ffdTriggerIdx ].RecoveryTypeArray[ RecoveryMode ];  /* [GUD] ffdTriggerIdx *//* [GUDCHK:CALLER]RecoveryMode */

    if ( ( clearFFD & clearPtnBit ) == clearPtnBit )
    {
        clearFFDFlag    =   (boolean)TRUE;
    }

    return clearFFDFlag;
}


/****************************************************************************/
/* Function Name | Dem_Data_GetClearPatternBit                              */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] DTCStatus :                                         */
/* Return Value  | Dem_u08_ClearPtnAtDTCStatusType                          */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:AllValue] ReturnValue                           */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_ClearPtnAtDTCStatusType, DEM_CODE ) Dem_DataCtl_GetClearPatternBit
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
)
{
    VAR( Dem_u08_ClearPtnAtDTCStatusType, AUTOMATIC ) clearPtnBit;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) checkDTCStatus;

    checkDTCStatus  =   ( DTCStatus & ( DEM_UDS_STATUS_CDTC | DEM_UDS_STATUS_PDTC ));

    /*  statusOfDTC bit pattern         */
    if ( checkDTCStatus == ( DEM_UDS_STATUS_CDTC | DEM_UDS_STATUS_PDTC ) )
    {
        clearPtnBit =   DEM_CLRPTN_CLR_BOTHON;
    }
    else
    if ( checkDTCStatus == ( DEM_UDS_STATUS_CDTC ) )
    {
        clearPtnBit =   DEM_CLRPTN_CLR_CDTCON;
    }
    else
    if ( checkDTCStatus == ( DEM_UDS_STATUS_PDTC ) )
    {
        clearPtnBit =   DEM_CLRPTN_CLR_PDTCON;
    }
    else
    {
        clearPtnBit =   DEM_CLRPTN_CLR_BOTHOFF;
    }

    return clearPtnBit;
}

/****************************************************************************/
/* Function Name | Dem_DataCtl_GetFFDTriggerIndex                           */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] FreezeFrameRecordTrigger :                          */
/* Return Value  | Dem_u08_FFDTriggerIndexType                              */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:AllValue] ReturnValue                           */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_FFDTriggerIndexType, DEM_CODE ) Dem_DataCtl_GetFFDTriggerIndex
(
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger
)
{
    VAR( Dem_u08_FFDTriggerIndexType, AUTOMATIC ) ffdTriggerIdx;


    /*  freezeframe trigger pattern     */
    if ( FreezeFrameRecordTrigger == DEM_TRIGGER_ON_CONFIRMED )
    {
        ffdTriggerIdx   =   DEM_FFDTRIGGER_IDX_CONFIRMED;
    }
    else
    if ( FreezeFrameRecordTrigger == DEM_TRIGGER_ON_PENDING )
    {
        ffdTriggerIdx   =   DEM_FFDTRIGGER_IDX_PENDING;
    }
    else
    if ( FreezeFrameRecordTrigger == DEM_TRIGGER_ON_TEST_FAILED_THIS_OPERATION_CYCLE )
    {
        ffdTriggerIdx   =   DEM_FFDTRIGGER_IDX_TFTOC;
    }
    else    /* ( FreezeFrameRecordTrigger == DEM_TRIGGER_ON_FDC_THRESHOLD ) */
    {
        ffdTriggerIdx   =   DEM_FFDTRIGGER_IDX_FDC_THRESHOLD;
    }

    return ffdTriggerIdx;
}

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataCtl_GetFFDRecordTrigger                          */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] FreezeFrameRecordTrigger :                          */
/* Return Value  | Dem_u08_FFDTriggerIndexType                              */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:AllValue] ReturnValue                           */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_StorageTriggerType, DEM_CODE ) Dem_DataCtl_GetFFDRecordTrigger
(
    VAR( Dem_u08_FFDTriggerIndexType, AUTOMATIC ) FFDTriggerIdx
)
{
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) freezeFrameRecordTrigger;

    /*  freezeframe trigger pattern     */
    if ( FFDTriggerIdx == DEM_FFDTRIGGER_IDX_CONFIRMED )
    {
        freezeFrameRecordTrigger    =   DEM_TRIGGER_ON_CONFIRMED;
    }
    else
    if ( FFDTriggerIdx == DEM_FFDTRIGGER_IDX_PENDING )
    {
        freezeFrameRecordTrigger    =   DEM_TRIGGER_ON_PENDING;
    }
    else
    if ( FFDTriggerIdx == DEM_FFDTRIGGER_IDX_TFTOC )
    {
        freezeFrameRecordTrigger    =   DEM_TRIGGER_ON_TEST_FAILED_THIS_OPERATION_CYCLE;
    }
    else    /* ( FFDTriggerIdx == DEM_FFDTRIGGER_IDX_FDC_THRESHOLD )    */
    {
        freezeFrameRecordTrigger    =   DEM_TRIGGER_ON_FDC_THRESHOLD;
    }

    return freezeFrameRecordTrigger;
}
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )     */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-07-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
