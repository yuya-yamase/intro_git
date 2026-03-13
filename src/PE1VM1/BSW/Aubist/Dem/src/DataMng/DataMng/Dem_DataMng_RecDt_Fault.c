/* Dem_DataMng_RecDt_Fault_c(v5-9-0)                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataMng_RecDt_Fault/CODE                              */
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
#include "Dem_DataMng_local.h"
#include "Dem_DataMng_GetRecordData.h"

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
static FUNC( void, DEM_CODE ) Dem_DataMng_InitObdRecordNumberIndexData
(
    P2VAR( Dem_u08_FFDIndexType, AUTOMATIC, DEM_VAR_NO_INIT ) ObdRecordNumberIndexArrayPtr
);
static FUNC( void, DEM_CODE ) Dem_DataMng_InitObdRecordNumberIndex
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex
);
static FUNC( void, DEM_CODE ) Dem_DataMng_GetObdRecordNumberIndex_Ctl
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_u08_FFDIndexType, AUTOMATIC, DEM_VAR_NO_INIT ) ObdRecordNumberIndexArrayPtr
);
static FUNC( void, DEM_CODE ) Dem_DataMng_SetObdRecordNumberIndex_Ctl
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) SrcFaultRecordPtr
);

#endif  /*   ( DEM_OBDFFD_SUPPORT == STD_ON )      */

static FUNC( void, DEM_CODE ) Dem_DataMng_InitRecordNumberIndexData
(
    P2VAR( Dem_u08_FFDIndexType, AUTOMATIC, DEM_VAR_NO_INIT ) RecordNumberIndexArrayPtr
);

static FUNC( void, DEM_CODE ) Dem_DataMng_InitFaultRecord_Ctl
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex
);

static FUNC( void, DEM_CODE ) Dem_DataMng_InitRecordNumberIndex
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex
);

static FUNC( void, DEM_CODE ) Dem_DataMng_GetFaultRecord_Ctl
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) DestFaultRecordPtr
);

static FUNC( void, DEM_CODE ) Dem_DataMng_GetRecordNumberIndexCtl
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_u08_FFDIndexType, AUTOMATIC, DEM_VAR_NO_INIT ) RecordNumberIndexArrayPtr
);

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
static FUNC( void, DEM_CODE ) Dem_DataMng_GetFaultRecord_MM
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) DestFaultRecordPtr
);
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

static FUNC( void, DEM_CODE ) Dem_DataMng_SetFaultRecord_Ctl
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) SrcFaultRecordPtr
);


static FUNC( void, DEM_CODE ) Dem_DataMng_SetRecordNumberIndex_Ctl
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) SrcFaultRecordPtr
);

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMng_CmpWithFaultRecord
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) CheckFaultRecordPtr
);

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMng_CmpWithRecordNumberIndex
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) CheckFaultRecordPtr
);

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMng_CmpWithObdRecordNumberIndex
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) CheckFaultRecordPtr
);
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMng_CmpWithNonObdRecordNumberIndex
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) CheckFaultRecordPtr
);

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
#if ( DEM_FAULT_RECORD_PADDING_EXIST == STD_ON )
static FUNC( void, DEM_CODE ) Dem_FaultMng_InitFRData_Padding
(
    P2VAR( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) FaultRecordPtr
);
#endif  /* ( DEM_FAULT_RECORD_PADDING_EXIST == STD_ON ) */

static FUNC( void, DEM_CODE ) Dem_FaultMng_InitMirrorMemory
( void );

#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT ) Dem_FaultNvMStatus[DEM_FAIL_RECORD_LIST_NUM];
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/*  if DEM_NVM_SYNC_PROCESS_ENABLE is STD_OFF, these valiables are set but never used.  */
VAR( Dem_FaultRecordType, DEM_VAR_NO_INIT ) Dem_TmpFaultMirror;
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#define DEM_START_SEC_VAR_SAVED_ZONE
#include <Dem_MemMap.h>

VAR( Dem_FaultRecordType, DEM_VAR_SAVED_ZONE ) Dem_FaultRecordList[DEM_FAIL_RECORD_LIST_NUM];

#define DEM_STOP_SEC_VAR_SAVED_ZONE
#include <Dem_MemMap.h>


/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_DataMngC_GetFaultRecord                              */
/* Description   | Gets the data body of the fault record from the fault r- */
/*               | ecord list corresponding to the specified fault index. - */
/*               | (for Dem_DataCtl subunit)                                */
/* Preconditions | The specified fault index be within the range of the fa- */
/*               | ult record list.                                         */
/* Parameters    | [in] FaultIndex :                                        */
/*               |        The fault index corresponding to the specific fa- */
/*               |        ult record.                                       */
/*               | [out] FaultRecordPtr :                                   */
/*               |        The pointer of the fault record corresponding to  */
/*               |         the specified fault index.                       */
/*               |                    &Dem_TmpDisabledRecord.FaultRecord    */
/*               |                    &Dem_TmpEventMemoryEntry.FaultRecord  */
/*               |                    AUTOMATIC                             */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:DEM_IRT_OK] FaultIndex                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetFaultRecord
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) FaultRecordPtr
)
{
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;
    failRecordNum = Dem_FailRecordNum;

    if( FaultIndex < failRecordNum )                                            /* [GUD:if] FaultIndex */
    {
        Dem_DataMng_GetFaultRecord_Ctl( FaultIndex, FaultRecordPtr );
        retVal = DEM_IRT_OK;
    }
    else
    {
        /* No process */
    }

    return retVal;
}

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataMngC_GetFaultRecordAddress                       */
/* Description   | get FaultRecord address.                                 */
/*               |                                                          */
/* Preconditions | The specified fault index be within the range of the fa- */
/*               | ult record list.                                         */
/* Parameters    | [in] FaultIndex :                                        */
/*               |        The fault index corresponding to the specific fa- */
/*               |        ult record.                                       */
/*               | [out] FaultRecordPtrCtlPtr :                             */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/*               |                                                          */
/* Notes         | This function must be used from Dem_MainFunction context.*/
/*               |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetFaultRecordAddress
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_FaultRecordPtrForCtlType, AUTOMATIC, AUTOMATIC ) FaultRecordPtrCtlPtr
)
{
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;
    failRecordNum = Dem_FailRecordNum;

    if( FaultIndex < failRecordNum )                                            /* [GUD:if] FaultIndex */
    {
        ( FaultRecordPtrCtlPtr->FaultRecordPtr )   =   &Dem_FaultRecordList[FaultIndex];    /* [GUD] FaultIndex */
        retVal = DEM_IRT_OK;
    }
    else
    {
        /* No process */
    }

    return retVal;
}
#endif  /*   ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )   */

#if ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON )
/*****************************************************************************/
/* Function Name | Dem_DataMngC_GetFaultRecordAddress_MaxNumOfFFRTrigger     */
/* Description   | get FaultRecord address.                                  */
/*               |                                                           */
/* Preconditions | The specified fault index be within the range of the fa-  */
/*               | ult record list.                                          */
/* Parameters    | [in] FaultIndex :                                         */
/*               |        The fault index corresponding to the specific fa-  */
/*               |        ult record.                                        */
/*               | [out] FaultRecordPtrCtlPtr :                              */
/*               |                                                           */
/* Return Value  | Dem_u08_InternalReturnType                                */
/*               |        DEM_IRT_OK :                                       */
/*               |        DEM_IRT_NG :                                       */
/*               |                                                           */
/* Notes         | This function must be used from Dem_MainFunction context. */
/*               |                                                           */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetFaultRecordAddress_MaxNumOfFFRTrigger
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_FaultRecordPtrForCtlType, AUTOMATIC, AUTOMATIC ) FaultRecordPtrCtlPtr
)
{
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;
    failRecordNum = Dem_FailRecordNum;

    if( FaultIndex < failRecordNum )                                            /* [GUD:if] FaultIndex */
    {
        ( FaultRecordPtrCtlPtr->FaultRecordPtr )   =   &Dem_FaultRecordList[FaultIndex];    /* [GUD] FaultIndex */
        retVal = DEM_IRT_OK;
    }
    else
    {
        /* No process */
    }

    return retVal;
}
#endif /* ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON ) */

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataMngC_GetFaultRecordAddress_TSFF                  */
/* Description   | get FaultRecord address.                                 */
/*               |                                                          */
/* Preconditions | The specified fault index be within the range of the fa- */
/*               | ult record list.                                         */
/* Parameters    | [in] FaultIndex :                                        */
/*               |        The fault index corresponding to the specific fa- */
/*               |        ult record.                                       */
/*               | [out] FaultRecordPtrCtlPtr :                             */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/*               |                                                          */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetFaultRecordAddress_TSFF
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_FaultRecordPtrForCtlType, AUTOMATIC, AUTOMATIC ) FaultRecordPtrCtlPtr
)
{
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;
    failRecordNum = Dem_FailRecordNum;

    if( FaultIndex < failRecordNum )                                            /* [GUD:if] FaultIndex */
    {
        ( FaultRecordPtrCtlPtr->FaultRecordPtr )   =   &Dem_FaultRecordList[FaultIndex];    /* [GUD] FaultIndex */
        retVal = DEM_IRT_OK;
    }
    else
    {
        /* No process */
    }

    return retVal;
}
#endif  /*   ( DEM_TSFF_PM_SUPPORT == STD_ON )   */

/****************************************************************************/
/* Function Name | Dem_DataMngC_GetFR_EventStrgIndex                        */
/* Description   | Gets the event index of the fault record list correspon- */
/*               | ding to the specified fault index.                       */
/* Preconditions | The specified fault index be within the range of the fa- */
/*               | ult record list.                                         */
/* Parameters    | [in] FaultIndex :                                        */
/*               |        The fault index corresponding to the specific fa- */
/*               |        ult record.                                       */
/*               | [out] EventStrgIndexPtr :                                */
/*               |        The pointer of the event index.                   */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:DEM_IRT_OK] FaultIndex                          */
/* VariableGuard | [GUD:RET:DEM_IRT_OK] EventStrgIndexPtr                   */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetFR_EventStrgIndex
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;
    failRecordNum = Dem_FailRecordNum;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    if( FaultIndex < failRecordNum )                                            /* [GUD:if] FaultIndex */
    {
        eventStrgIndex  =   Dem_FaultRecordList[FaultIndex].EventStrgIndex;     /* [GUD] FaultIndex */
        if( eventStrgIndex < eventStorageNum )                                  /* [GUD:if]eventStrgIndex */
        {
            *EventStrgIndexPtr = eventStrgIndex;
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
/* Function Name | Dem_DataMngC_GetNumberOfDTCsToStoreFreezeFrame           */
/* Description   | Get Number of DTCs to Store FreezeFrameRecord            */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | uint8                                                    */
/*               | NumberOfDTCsToStoreFreezeFrame :                         */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( uint8, DEM_CODE ) Dem_DataMngC_GetNumberOfDTCsToStoreFreezeFrame
(
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) AllObdDTCFreezeFlagPtr
)
{
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) loopfailRecordIndex;
    P2VAR( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) tmpFaultRecordPtr;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;

#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    VAR( uint8, AUTOMATIC ) numberOfObdDTCsToStoreFreezeFrame;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) obdFFRClassIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) obdFFRClassPerDTCMaxNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) obdFFDRecordNum;
    VAR( boolean, AUTOMATIC ) obdDTCFlag;
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */

    VAR( uint8, AUTOMATIC ) numberOfDTCsToStoreFreezeFrame;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonObdFFRClassIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonObdFFRClassPerDTCMaxNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) nonObdFFDRecordNum;

    failRecordNum = Dem_FailRecordNum;
    numberOfDTCsToStoreFreezeFrame = (uint8)0U;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;
    nonObdFFRClassPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;
    nonObdFFDRecordNum = Dem_NonObdFFDRecordNum;

#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    numberOfObdDTCsToStoreFreezeFrame = (uint8)0U;
    obdFFRClassPerDTCMaxNum = Dem_CfgInfoPm_GetOBDFFRClassPerDTCMaxNum();
    obdFFDRecordNum = Dem_CfgInfoPm_GetObdFFDRecordNum();
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */

    for ( loopfailRecordIndex = (Dem_u08_FaultIndexType)0U; loopfailRecordIndex < failRecordNum; loopfailRecordIndex++ )    /* [GUD:for] loopfailRecordIndex */
    {
        tmpFaultRecordPtr = &Dem_FaultRecordList[loopfailRecordIndex];                                                      /* [GUD] loopfailRecordIndex */

        if ( tmpFaultRecordPtr->EventStrgIndex < eventStorageNum )                                                          /* [GUD:if] tmpFaultRecordPtr->EventStrgIndex */
        {
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
            obdDTCFlag = Dem_CfgInfoPm_CheckEventKindOfOBD_InEvtStrgGrp( tmpFaultRecordPtr->EventStrgIndex );
            for ( obdFFRClassIndex = (Dem_u08_FFListIndexType)0U; obdFFRClassIndex < obdFFRClassPerDTCMaxNum; obdFFRClassIndex++ )  /* [GUD:for] obdFFRClassIndex */
            {
                if ( tmpFaultRecordPtr->ObdRecordNumberIndex[ obdFFRClassIndex ] < obdFFDRecordNum )                                /* [GUD] obdFFRClassIndex *//* [ARYCHK] DEM_OBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / obdFFRClassIndex */
                {
                    numberOfDTCsToStoreFreezeFrame = numberOfDTCsToStoreFreezeFrame + (uint8)1U;
                    numberOfObdDTCsToStoreFreezeFrame = numberOfObdDTCsToStoreFreezeFrame + (uint8)1U;
                    break;
                }
            }
            if ( obdFFRClassIndex >= obdFFRClassPerDTCMaxNum )
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
            {
                for ( nonObdFFRClassIndex = (Dem_u08_FFListIndexType)0U; nonObdFFRClassIndex < nonObdFFRClassPerDTCMaxNum; nonObdFFRClassIndex++ )  /* [GUD:for] nonObdFFRClassIndex */
                {
                    if ( tmpFaultRecordPtr->RecordNumberIndex[ nonObdFFRClassIndex ] < nonObdFFDRecordNum )                         /* [GUD] nonObdFFRClassIndex *//* [ARYCHK] DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / nonObdFFRClassIndex */
                    {
                        numberOfDTCsToStoreFreezeFrame = numberOfDTCsToStoreFreezeFrame + (uint8)1U;
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
                        if ( obdDTCFlag == (boolean)TRUE )
                        {
                            numberOfObdDTCsToStoreFreezeFrame = numberOfObdDTCsToStoreFreezeFrame + (uint8)1U;
                        }
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
                        break;
                    }
                }
            }
        }
    }

#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    if ( numberOfObdDTCsToStoreFreezeFrame == numberOfDTCsToStoreFreezeFrame )
    {
        *AllObdDTCFreezeFlagPtr = (boolean)TRUE;
    }
    else
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */
    {
        *AllObdDTCFreezeFlagPtr = (boolean)FALSE;
    }
    return numberOfDTCsToStoreFreezeFrame;
}


#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataMngC_GetFR_EventStrgIndex_ObdRecordNumberIndex   */
/* Description   | Gets the event index and the record number index of the  */
/*               | fault record list corresponding to the specified fault   */
/*               | index.                                                   */
/* Preconditions | The specified fault index be within the range of the fa- */
/*               | ult record list.                                         */
/* Parameters    | [in] FaultIndex :                                        */
/*               |        The fault index corresponding to the specific fa- */
/*               |        ult record.                                       */
/*               | [out] EventStrgIndexPtr :                                */
/*               |        The pointer of the event index.                   */
/*               | [out] ObdRecordNumberIndexPtr :                          */
/*               |        The pointer of the OBD record number index.       */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetFR_EventStrgIndex_ObdRecordNumberIndex
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr,
    P2VAR( Dem_u08_FFDIndexType, AUTOMATIC, AUTOMATIC ) ObdRecordNumberIndexPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) ffrCnt;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) obdFFRClassNumPerDTCMaxNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;
    failRecordNum = Dem_FailRecordNum;
    obdFFRClassNumPerDTCMaxNum = Dem_CfgInfoPm_GetOBDFFRClassPerDTCMaxNum();
    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    if( FaultIndex < failRecordNum )                                            /* [GUD:if] FaultIndex */
    {
        eventStrgIndex  =   Dem_FaultRecordList[FaultIndex].EventStrgIndex;     /* [GUD] FaultIndex */

        if( eventStrgIndex < eventStorageNum )                                  /* [GUD:if]eventStrgIndex */
        {
            *EventStrgIndexPtr = eventStrgIndex;
            for( ffrCnt = (Dem_u08_FFListIndexType)0U; ffrCnt < obdFFRClassNumPerDTCMaxNum; ffrCnt++ )  /* [GUD:for]ffrCnt */
            {
                ObdRecordNumberIndexPtr[ffrCnt] = Dem_FaultRecordList[FaultIndex].ObdRecordNumberIndex[ffrCnt]; /* [GUD]ffrCnt *//* [GUD]FaultIndex *//* [ARYCHK] DEM_OBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / ffrCnt */
            }
            retVal = DEM_IRT_OK;
        }
    }
    else
    {
        /* No process */
    }

    return retVal;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */


/****************************************************************************/
/* Function Name | Dem_DataMngC_GetFR_EventStrgIndex_RecordNumberIndex      */
/* Description   | Gets the event index and the record number index of the  */
/*               | fault record list corresponding to the specified fault   */
/*               | index.                                                   */
/* Preconditions | The specified fault index be within the range of the fa- */
/*               | ult record list.                                         */
/* Parameters    | [in] FaultIndex :                                        */
/*               |        The fault index corresponding to the specific fa- */
/*               |        ult record.                                       */
/*               | [out] EventStrgIndexPtr :                                */
/*               |        The pointer of the event index.                   */
/*               | [out] RecordNumberIndexPtr :                             */
/*               |        The pointer of the record number index.           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:DEM_IRT_OK] EventStrgIndexPtr                   */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetFR_EventStrgIndex_RecordNumberIndex
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr,
    P2VAR( Dem_u08_FFDIndexType, AUTOMATIC, AUTOMATIC ) RecordNumberIndexPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) ffrCnt;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonOBDFFRClassNumPerDTCMaxNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;
    failRecordNum = Dem_FailRecordNum;
    nonOBDFFRClassNumPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    if( FaultIndex < failRecordNum )                                            /* [GUD:if] FaultIndex */
    {
        eventStrgIndex  =   Dem_FaultRecordList[FaultIndex].EventStrgIndex;     /* [GUD] FaultIndex */

        if( eventStrgIndex < eventStorageNum )                                  /* [GUD:if]eventStrgIndex */
        {
            *EventStrgIndexPtr = eventStrgIndex;
            for( ffrCnt = (Dem_u08_FFListIndexType)0U; ffrCnt < nonOBDFFRClassNumPerDTCMaxNum; ffrCnt++ )   /* [GUD:for]ffrCnt */
            {
                RecordNumberIndexPtr[ffrCnt] = Dem_FaultRecordList[FaultIndex].RecordNumberIndex[ffrCnt];   /* [GUD]ffrCnt *//* [GUD]FaultIndex *//* [ARYCHK] DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / ffrCnt */
            }
            retVal = DEM_IRT_OK;
        }
    }
    else
    {
        /* No process */
    }

    return retVal;
}
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */


#if ( DEM_OBDFFD_SUPPORT == STD_ON )
#if ( DEM_OBDONEDS_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataMngC_GetFR_CheckExistOBDFFD                      */
/* Description   | whether FaultRecord has OBDFFD or not.                   */
/* Preconditions |                                                          */
/* Parameters    | [in] FaultIndex :                                        */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : FaultRecord has OBDFFD.                   */
/*               |        FALSE : FaultRecord has no OBDFFD.                */
/*               |                (or parameter error.)                     */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_DataMngC_GetFR_CheckExistOBDFFD
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex
)
{
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) ffrCnt;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) obdFFRClassNumPerDTCMaxNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) obdffdIndex;
    VAR( boolean, AUTOMATIC ) existDataFlag;

    existDataFlag = (boolean)FALSE;
    failRecordNum = Dem_FailRecordNum;
    obdFFRClassNumPerDTCMaxNum = Dem_CfgInfoPm_GetOBDFFRClassPerDTCMaxNum();

    if( FaultIndex < failRecordNum )                                            /* [GUD:if] FaultIndex */
    {
        for( ffrCnt = (Dem_u08_FFListIndexType)0U; ffrCnt < obdFFRClassNumPerDTCMaxNum; ffrCnt++ )  /* [GUD:for]ffrCnt */
        {
            obdffdIndex =   Dem_FaultRecordList[FaultIndex].ObdRecordNumberIndex[ffrCnt];           /* [GUD]ffrCnt */
            if( obdffdIndex != DEM_FFRECINDEX_INITIAL )
            {
                existDataFlag = (boolean)TRUE;
                break;
            }
        }
    }
    return existDataFlag;
}
#endif  /*   ( DEM_OBDONEDS_SUPPORT == STD_ON )     */
#if ( DEM_OBDONUDS_SUPPORT == STD_ON )
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataMngC_GetFR_CheckExistOBDFFD                      */
/* Description   | whether FaultRecord has OBDFFD or not.                   */
/* Preconditions |                                                          */
/* Parameters    | [in] FaultIndex :                                        */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : FaultRecord has OBDFFD.                   */
/*               |        FALSE : FaultRecord has no OBDFFD.                */
/*               |                (or parameter error.)                     */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | new created.based on Dem_DataMngC_GetFR_CheckExistOBDFFD( DEM_OBDONEDS_SUPPORT == STD_ON ). */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_DataMngC_GetFR_CheckExistOBDFFD
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex
)
{
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) ffrCnt;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) obdFFRClassNumPerDTCMaxNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) obdffdIndex;
    VAR( boolean, AUTOMATIC ) existDataFlag_1;
    VAR( boolean, AUTOMATIC ) existDataFlag_ALL;

    existDataFlag_1   = (boolean)FALSE;
    existDataFlag_ALL = (boolean)FALSE;

    failRecordNum = Dem_FailRecordNum;
    obdFFRClassNumPerDTCMaxNum = Dem_CfgInfoPm_GetOBDFFRClassPerDTCMaxNum();

    if( FaultIndex < failRecordNum )                                            /* [GUD:if] FaultIndex */
    {
        for( ffrCnt = (Dem_u08_FFListIndexType)0U; ffrCnt < obdFFRClassNumPerDTCMaxNum; ffrCnt++ )  /* [GUD:for]ffrCnt */
        {
            obdffdIndex =   Dem_FaultRecordList[FaultIndex].ObdRecordNumberIndex[ffrCnt];           /* [GUD]ffrCnt */
            if( obdffdIndex != DEM_FFRECINDEX_INITIAL )
            {
                if ( existDataFlag_1 == (boolean)FALSE )
                {
                    /*  1st OBD frezeframe. */
                    existDataFlag_1 = (boolean)TRUE;
                }
                else
                {
                    /*  2nd OBD frezeframe. that's all. */
                    existDataFlag_ALL = (boolean)TRUE;
                    break;
                }
            }
        }
    }
    return existDataFlag_ALL;
}
#endif  /*   ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )     */
#endif  /*   ( DEM_OBDONUDS_SUPPORT == STD_ON )     */

/****************************************************************************/
/* Function Name | Dem_DataMngC_GetFR_ObdFreezeFrameIndex                   */
/* Description   | Get ObdFreezeFrame index.                                */
/* Preconditions |                                                          */
/* Parameters    | [in] FaultIndex :                                        */
/*               | [in] FreezeFrameRecordClassIndex :                       */
/*               |       index of Dem_FaultRecordList[FaultIndex].ObdRecordNumberIndex[].   */
/*               | [out] ObdFreezeFrameIndexPtr :                           */
/*               |       ObdFreezeFrame index..                             */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetFR_ObdFreezeFrameIndex
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassIndex,
    P2VAR( Dem_u08_FFDIndexType, AUTOMATIC, AUTOMATIC ) ObdFreezeFrameIndexPtr
)
{
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) obdFFRClassNumPerDTCMaxNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;
    failRecordNum = Dem_FailRecordNum;
    obdFFRClassNumPerDTCMaxNum = Dem_CfgInfoPm_GetOBDFFRClassPerDTCMaxNum();

    if( FaultIndex < failRecordNum )                                            /* [GUD:if] FaultIndex */
    {
        if ( FreezeFrameRecordClassIndex < obdFFRClassNumPerDTCMaxNum )         /* [GUD:if]FreezeFrameRecordClassIndex */
        {
            *ObdFreezeFrameIndexPtr = Dem_FaultRecordList[FaultIndex].ObdRecordNumberIndex[FreezeFrameRecordClassIndex];    /* [GUD] FaultIndex *//* [GUD] FreezeFrameRecordClassIndex */
            retVal = DEM_IRT_OK;
        }
    }
    return retVal;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */


/****************************************************************************/
/* Function Name | Dem_DataMngC_GetFR_FreezeFrameIndex                      */
/* Description   | Get FreezeFrame index.                                   */
/* Preconditions |                                                          */
/* Parameters    | [in] FaultIndex :                                        */
/*               | [in] FreezeFrameRecordClassIndex :                       */
/*               |       index of Dem_FaultRecordList[FaultIndex].RecordNumberIndex[].  */
/*               | [out] FreezeFrameIndexPtr :                              */
/*               |       FreezeFrame index..                                */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetFR_FreezeFrameIndex
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassIndex,
    P2VAR( Dem_u08_FFDIndexType, AUTOMATIC, AUTOMATIC ) FreezeFrameIndexPtr
)
{
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonOBDFFRClassNumPerDTCMaxNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;
    failRecordNum = Dem_FailRecordNum;
    nonOBDFFRClassNumPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;

    if( FaultIndex < failRecordNum )                                            /* [GUD:if] FaultIndex */
    {
        if ( FreezeFrameRecordClassIndex < nonOBDFFRClassNumPerDTCMaxNum )      /* [GUD:if]FreezeFrameRecordClassIndex */
        {
            *FreezeFrameIndexPtr = Dem_FaultRecordList[FaultIndex].RecordNumberIndex[FreezeFrameRecordClassIndex];  /* [GUD] FaultIndex *//* [GUD] FreezeFrameRecordClassIndex */
            retVal = DEM_IRT_OK;
        }
    }
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DataMngC_GetFR_AgingCounter                          */
/* Description   | Gets the aging counter of the fault record list corresp- */
/*               | onding to the specified fault index.                     */
/* Preconditions | The specified fault index be within the range of the fa- */
/*               | ult record list.                                         */
/* Parameters    | [in] FaultIndex :                                        */
/*               |        The fault index corresponding to the specific fa- */
/*               |        ult record.                                       */
/*               | [out] AgingCounterPtr :                                  */
/*               |        The pointer of the aging counter.                 */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetFR_AgingCounter
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_u08_AgingCounterType, AUTOMATIC, AUTOMATIC ) AgingCounterPtr
)
{
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;
    failRecordNum = Dem_FailRecordNum;

    if( FaultIndex < failRecordNum )                                            /* [GUD:if] FaultIndex */
    {
        *AgingCounterPtr = Dem_FaultRecordList[FaultIndex].AgingCounter;        /* [GUD] FaultIndex */
        retVal = DEM_IRT_OK;
    }

    return retVal;
}

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataMngC_GetFR_AgingTime                             */
/* Description   | Gets the aging counter of the fault record list corresp- */
/*               | onding to the specified fault index.                     */
/* Preconditions | The specified fault index be within the range of the fa- */
/*               | ult record list.                                         */
/* Parameters    | [in] FaultIndex :                                        */
/*               |        The fault index corresponding to the specific fa- */
/*               |        ult record.                                       */
/*               | [out] AgingTimePtr :                                     */
/*               |        The pointer of the aging time.                    */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | new created. based on Dem_DataMngC_GetFR_AgingCounter.   */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetFR_AgingTime
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_u16_WWHOBDTimeAgingCounterType, AUTOMATIC, AUTOMATIC ) AgingTimePtr
)
{
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;
    failRecordNum = Dem_FailRecordNum;

    if( FaultIndex < failRecordNum )                                            /* [GUD:if] FaultIndex */
    {
        *AgingTimePtr = Dem_FaultRecordList[FaultIndex].TimeAgingCounter;        /* [GUD] FaultIndex */
        retVal = DEM_IRT_OK;
    }

    return retVal;
}
#endif  /* ( DEM_WWH_OBD_SUPPORT == STD_ON )    */

#if ( DEM_INDICATOR_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataMngC_GetFR_HealingCounter                        */
/* Description   | Gets the healing counter of the fault record list corre- */
/*               | sponding to the specified fault index.                   */
/* Preconditions | The specified fault index be within the range of the fa- */
/*               | ult record list.                                         */
/* Parameters    | [in] FaultIndex :                                        */
/*               |        The fault index corresponding to the specific fa- */
/*               |        ult record.                                       */
/*               | [out] HealingCounterPtr :                                */
/*               |        The pointer of the aging counter.                 */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_DataMngC_GetFR_AgingCounter.   */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetFR_HealingCounter
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_u08_HealingCounterType, AUTOMATIC, AUTOMATIC ) HealingCounterPtr
)
{
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;
    failRecordNum = Dem_FailRecordNum;

    if( FaultIndex < failRecordNum )                                            /* [GUD:if] FaultIndex */
    {
        *HealingCounterPtr = Dem_FaultRecordList[FaultIndex].HealingCounter;    /* [GUD] FaultIndex */
        retVal = DEM_IRT_OK;
    }

    return retVal;
}
#endif  /* ( DEM_INDICATOR_USE == STD_ON )  */

#if ( DEM_EVENT_DISPLACEMENT_BY_DTCSTATUS_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataMngC_GetFR_ConfirmedOccurrenceOrder              */
/* Description   | Gets the confirmed occurrence order of the fault record  */
/*               | list corresponding to the specified fault index.         */
/* Preconditions | The specified fault index be within the range of the fa- */
/*               | ult record list.                                         */
/* Parameters    | [in] FaultIndex :                                        */
/*               |        The fault index corresponding to the specific fa- */
/*               |        ult record.                                       */
/*               | [out] ConfirmedOccurrenceOrderPtr :                      */
/*               |        The pointer of the confirmed occurrence order.    */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetFR_ConfirmedOccurrenceOrder
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_u16_OccrOrderType, AUTOMATIC, AUTOMATIC ) ConfirmedOccurrenceOrderPtr
)
{
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;
    failRecordNum = Dem_FailRecordNum;

    if( FaultIndex < failRecordNum )                                            /* [GUD:if] FaultIndex */
    {
        *ConfirmedOccurrenceOrderPtr = Dem_FaultRecordList[FaultIndex].ConfirmedOccurrenceOrder;    /* [GUD] FaultIndex */
        retVal = DEM_IRT_OK;
    }

    return retVal;
}
#endif  /* ( DEM_EVENT_DISPLACEMENT_BY_DTCSTATUS_SUPPORT == STD_ON )    */
#if ( DEM_EVENT_DISPLACEMENT_BY_DTCSTATUS_SUPPORT == STD_OFF )
#if ( DEM_OBDONEDS_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataMngC_GetFR_ConfirmedOccurrenceOrder              */
/* Description   | Gets the confirmed occurrence order of the fault record  */
/*               | list corresponding to the specified fault index.         */
/* Preconditions | The specified fault index be within the range of the fa- */
/*               | ult record list.                                         */
/* Parameters    | [in] FaultIndex :                                        */
/*               |        The fault index corresponding to the specific fa- */
/*               |        ult record.                                       */
/*               | [out] ConfirmedOccurrenceOrderPtr :                      */
/*               |        The pointer of the confirmed occurrence order.    */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.based on Dem_DataMngC_GetFR_ConfirmedOccurrenceOrder.*/
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetFR_ConfirmedOccurrenceOrder
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_u16_OccrOrderType, AUTOMATIC, AUTOMATIC ) ConfirmedOccurrenceOrderPtr
)
{
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;
    failRecordNum = Dem_FailRecordNum;

    if( FaultIndex < failRecordNum )                                            /* [GUD:if] FaultIndex */
    {
        *ConfirmedOccurrenceOrderPtr = Dem_FaultRecordList[FaultIndex].ConfirmedOccurrenceOrder;    /* [GUD] FaultIndex */
        retVal = DEM_IRT_OK;
    }

    return retVal;
}
#endif  /* ( DEM_OBDONEDS_SUPPORT == STD_ON )    */
#endif  /* ( DEM_EVENT_DISPLACEMENT_BY_DTCSTATUS_SUPPORT == STD_OFF )    */

#if ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataMngC_ConfirmedOccurrenceOrder                    */
/* Description   | Gets the confirmed occurrence order of the fault record  */
/*               | list corresponding to the specified fault index.         */
/* Preconditions | The specified fault index be within the range of the fa- */
/*               | ult record list.                                         */
/* Parameters    | [in] FaultIndex :                                        */
/*               |        The fault index corresponding to the specific fa- */
/*               |        ult record.                                       */
/* Return Value  | Dem_u16_OccrOrderType                                    */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u16_OccrOrderType, DEM_CODE ) Dem_DataMngC_ConfirmedOccurrenceOrder
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_OccrOrderType, AUTOMATIC ) retConfirmedOccurrenceOrder;

    retConfirmedOccurrenceOrder = Dem_FaultRecordList[FaultIndex].ConfirmedOccurrenceOrder;    /* [GUDCHK:CALLER]FaultIndex */

    return retConfirmedOccurrenceOrder;
}
#endif  /* ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT== STD_ON )   */

/****************************************************************************/
/* Function Name | Dem_DataMngC_GetFR_FFDIndexListSt                        */
/* Description   | Get frezeframe record index list in fault record.        */
/* Preconditions |                                                          */
/* Parameters    | [in] FaultIndex :                                        */
/*               |        The fault index corresponding to the specific fa- */
/*               |        ult record.                                       */
/*               | [out] FFDIndexListStPtr :                                */
/*               |        The pointer of frezeframe record index list.      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetFR_FFDIndexListSt
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_FaultRecordPartsFFDIndexListStType, AUTOMATIC, AUTOMATIC ) FFDIndexListStPtr
)
{
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;
    failRecordNum = Dem_FailRecordNum;

    if( FaultIndex < failRecordNum )                                            /* [GUD:if] FaultIndex */
    {
        /*  get FFList data.       */
        Dem_DataMng_GetRecordNumberIndexCtl( FaultIndex, &( FFDIndexListStPtr->RecordNumberIndex[0] ) );/* [ARYCHK] DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / 0 */

#if ( DEM_OBDFFD_SUPPORT == STD_ON )   /*  [FuncSw]    */
        /*  get OBD FFList data.       */
        Dem_DataMng_GetObdRecordNumberIndex_Ctl( FaultIndex, &( FFDIndexListStPtr->ObdRecordNumberIndex[0] ) );/* [ARYCHK] DEM_OBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / 0 */
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )            */

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )   /*  [FuncSw]    */
        /*  get TSFFList data.     */
        Dem_DataMng_GetTSFFListRecord_Ctl( FaultIndex, &( FFDIndexListStPtr->TimeSeriesFreezeFrameListIndex[0] ) );/* [ARYCHK] DEM_TSFF_RECORD_CLASS_NUM_PER_DTC_MAX_NUM / 1 / 0 */
#endif  /*   ( DEM_TSFF_PM_SUPPORT == STD_ON )         */
        retVal = DEM_IRT_OK;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_DataMngC_SetFaultRecord                              */
/* Description   | Sets the data body of the fault record to the fault rec- */
/*               | ord list corresponding to the specified fault index. (f- */
/*               | or Dem_DataCtl subunit)                                  */
/* Preconditions | The specified fault index be within the range of the fa- */
/*               | ult record list.                                         */
/* Parameters    | [in] FaultIndex :                                        */
/*               |        The fault index corresponding to the specific fa- */
/*               |        ult record.                                       */
/*               | [in] FaultRecordPtr :                                    */
/*               |                     &Dem_TmpEventMemoryEntry.FaultRecord */
/*               |        The pointer of the fault record corresponding to  */
/*               |         the specified fault index.                       */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_SetFaultRecord
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) FaultRecordPtr
)
{
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindFault;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;
    failRecordNum = Dem_FailRecordNum;

    if( FaultIndex < failRecordNum )                                            /* [GUD:if] FaultIndex */
    {
        Dem_DataMng_SetFaultRecord_Ctl( FaultIndex, FaultRecordPtr );
        /* Change Fault NvMStatus */
        recMngCmnKindFault = Dem_RecMngCmnKindFault;
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindFault, ( Dem_u16_RecordIndexType )FaultIndex );
        retVal = DEM_IRT_OK;
    }
    else
    {
        /* No process */
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_DataMngC_SetFaultRecord_WithUpdateConsistencyID      */
/* Description   | Sets the data body and update consistencyId of the fault */
/*               | record to the fault record list corresponding to the sp- */
/*               | ecified fault index. (for Dem_DataCtl subunit)           */
/* Preconditions | The specified fault index be within the range of the fa- */
/*               | ult record list.                                         */
/* Parameters    | [in] FaultIndex :                                        */
/*               |        The fault index corresponding to the specific fa- */
/*               |        ult record.                                       */
/*               | [in] FaultRecordPtr :                                    */
/*               |                     &Dem_TmpEventMemoryEntry.FaultRecord */
/*               |        The pointer of the fault record corresponding to  */
/*               | [out] ConsistencyId :                                    */
/*               |        updated consistencyId                             */
/*               |         the specified fault index.                       */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMngC_SetFaultRecord_WithUpdateConsistencyID
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) FaultRecordPtr,
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) ConsistencyIdPtr
)
{
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) consistencyId;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindFault;

    failRecordNum = Dem_FailRecordNum;

    if( FaultIndex < failRecordNum )                                                    /* [GUD:if] FaultIndex */
    {
        Dem_DataMng_SetFaultRecord_Ctl( FaultIndex, FaultRecordPtr );

        /* update consistencyId*/
        consistencyId = Dem_FaultRecordList[FaultIndex].ConsistencyCounterForFault;     /* [GUD] FaultIndex */

        consistencyId = Dem_UtlCid_CalcConsistencyId( consistencyId );

        Dem_FaultRecordList[FaultIndex].ConsistencyCounterForFault = consistencyId;     /* [GUD] FaultIndex */

        *ConsistencyIdPtr = consistencyId;

        /* Change Fault NvMStatus */
        recMngCmnKindFault = Dem_RecMngCmnKindFault;
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindFault, ( Dem_u16_RecordIndexType )FaultIndex );
    }
    else
    {
        /* No process */
    }

    return;
}


#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataMngC_SetFR_MILOccurrenceOrder_WithUpdateConsistencyID      */
/* Description   | set data to fault record(update with eventrecord).       */
/* Preconditions | The specified fault index be within the range of the fa- */
/*               | ult record list.                                         */
/* Parameters    | [in] FaultIndex :                                        */
/*               |        The fault index corresponding to the specific fa- */
/*               |        ult record.                                       */
/*               | [in] MILOccurrenceOrder :                                */
/*               | [out] ConsistencyId :                                    */
/*               |        updated consistencyId                             */
/*               |         the specified fault index.                       */
/* Return Value  | none                                                     */
/* Notes         | The caller calls this function after checking the record data difference.    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_DataMngC_SetFaultRecord_WithUpdateConsistencyID.   */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMngC_SetFR_MILOccurrenceOrder_WithUpdateConsistencyID
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    VAR( Dem_u16_OccrOrderType, AUTOMATIC ) MILOccurrenceOrder,
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) ConsistencyIdPtr
)
{
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) consistencyId;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindFault;

    failRecordNum = Dem_FailRecordNum;

    if( FaultIndex < failRecordNum )        /* [GUD:if]FaultIndex */
    {
        Dem_FaultRecordList[FaultIndex].MILOccurrenceOrder       = MILOccurrenceOrder;      /* [GUD:if]FaultIndex */

        /* update consistencyId*/
        consistencyId = Dem_FaultRecordList[FaultIndex].ConsistencyCounterForFault;         /* [GUD:if]FaultIndex */

        consistencyId = Dem_UtlCid_CalcConsistencyId( consistencyId );

        Dem_FaultRecordList[FaultIndex].ConsistencyCounterForFault = consistencyId;         /* [GUD:if]FaultIndex */

        *ConsistencyIdPtr = consistencyId;

        /* Change Fault NvMStatus */
        recMngCmnKindFault = Dem_RecMngCmnKindFault;
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindFault, ( Dem_u16_RecordIndexType )FaultIndex );

    }

    return ;
}
#endif  /* ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )  */
#endif  /* ( DEM_WWH_OBD_SUPPORT == STD_ON )    */


/****************************************************************************/
/* Function Name | Dem_DataMngC_ClearFaultRecord                            */
/* Description   | Sets the data body of the fault record to the fault rec- */
/*               | ord list corresponding to the specified fault index. (f- */
/*               | or Dem_DataCtl subunit)                                  */
/* Preconditions | The specified fault index be within the range of the fa- */
/*               | ult record list.                                         */
/* Parameters    | [in] FaultIndex :                                        */
/*               |        The fault index corresponding to the specific fa- */
/*               |        ult record.                                       */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_ClearFaultRecord
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex
)
{
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindFault;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;
    failRecordNum = Dem_FailRecordNum;

    if( FaultIndex < failRecordNum )                                            /* [GUD:if] FaultIndex */
    {
        Dem_DataMng_InitFaultRecord_Ctl( FaultIndex );                          /* [GUD] FaultIndex */

        recMngCmnKindFault = Dem_RecMngCmnKindFault;
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindFault, ( Dem_u16_RecordIndexType )FaultIndex );   /* [GUD]FaultIndex */

        retVal = DEM_IRT_OK;
    }
    else
    {
        /* No process */
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_DataMngC_CompareFaultRecord                          */
/* Description   | Compare record data : Fault record.                      */
/* Preconditions |                                                          */
/* Parameters    | [in] FaultIndex :                                        */
/*               | [in] CheckFaultRecordPtr :                               */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK  : same.                               */
/*               |        DEM_IRT_NG  : different.                          */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_CompareFaultRecord
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,                            /* [PRMCHK:CALLER] */
    P2CONST( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) CheckFaultRecordPtr  /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;
    failRecordNum = Dem_FailRecordNum;

    if( FaultIndex < failRecordNum )                                            /* [GUD:if] FaultIndex */
    {
        retVal = Dem_DataMng_CmpWithFaultRecord( FaultIndex, CheckFaultRecordPtr );     /* [GUD]FaultIndex *//* [GUDCHK:CALLER]CheckFaultRecordPtr */
    }
    else
    {
        /* No process */
    }
    return retVal;
}


#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataMngM_GetFaultRecord                              */
/* Description   | Gets the data body and the consistency counter of the f- */
/*               | ault record from the fault record list corresponding to  */
/*               |  the specified fault index.                              */
/* Preconditions | The specified fault index be within the range of the fa- */
/*               | ult record list.                                         */
/* Parameters    | [in] FaultIndex :                                        */
/*               |        The fault index corresponding to the specific fa- */
/*               |        ult record.                                       */
/*               | [out] FaultRecordPtr :                                   */
/*               |        The pointer of the fault record corresponding to  */
/*               |         the specified fault index.                       */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngM_GetFaultRecord
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr
)
{
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;
    failRecordNum = Dem_FailRecordNum;

    if( FaultIndex < failRecordNum )                                            /* [GUD:if] FaultIndex */
    {
        Dem_DataMng_GetFaultRecord_Ctl( FaultIndex, FaultRecordPtr );
        Dem_DataMng_GetFaultRecord_MM( FaultIndex, FaultRecordPtr );
        retVal = DEM_IRT_OK;
    }
    else
    {
        /* No process */
    }

    return retVal;
}
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */


/****************************************************************************/
/* Function Name | Dem_DataMngC_InitFaultCtlRecordData                      */
/* Description   | Initializes the specified fault record.                  */
/* Preconditions |                                                          */
/* Parameters    | [out] FaultRecordPtr :                                   */
/*               |                  &Dem_TmpEventMemoryEntry.FaultRecord    */
/*               |                  &Dem_TmpDisabledRecord.FaultRecord      */
/*               |                  AUTOMATIC                               */
/*               |        The specified fault record to initialize.         */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMngC_InitFaultCtlRecordData
(
    P2VAR( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) FaultRecordPtr
)
{
    /* Sets initial value to the specified fault record. */

    /* The event index. */
    FaultRecordPtr->EventStrgIndex           = DEM_EVENTSTRGINDEX_INVALID;

    FaultRecordPtr->OccurrenceOrder          = DEM_FAIL_OCCURRENCE_NUM_INVALID;

    FaultRecordPtr->ConfirmedOccurrenceOrder = DEM_FAIL_OCCURRENCE_NUM_INVALID;
    FaultRecordPtr->MILOccurrenceOrder       = DEM_FAIL_OCCURRENCE_NUM_INVALID;
    FaultRecordPtr->AgingCounter             = DEM_AGING_COUNT_INITIAL_VALUE;
#if ( DEM_WWH_OBD_SUPPORT == STD_ON ) /* [FuncSw] */
    FaultRecordPtr->TimeAgingCounter         = DEM_TIME_AGING_COUNT_INITIAL_VALUE;
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */
    FaultRecordPtr->HealingCounter           = DEM_HEALING_COUNT_INITIAL_VALUE;

#if ( DEM_OBDFFD_SUPPORT == STD_ON )   /*  [FuncSw]    */
    /* Initialize OBD FFList. */
    Dem_DataMng_InitObdRecordNumberIndexData( &FaultRecordPtr->ObdRecordNumberIndex[0] );/* [ARYCHK] DEM_OBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / 0 */
#endif  /*   ( DEM_OBDFFD_SUPPORT == STD_ON )          */

    /* Initialize FFList. */
    Dem_DataMng_InitRecordNumberIndexData( &FaultRecordPtr->RecordNumberIndex[0] );/* [ARYCHK] DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / 0 */

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )   /*  [FuncSw]    */
    /* Initialize TSFFList. */
    Dem_DataMng_InitTSFFListRecordData( &FaultRecordPtr->TimeSeriesFreezeFrameListIndex[0] );/* [ARYCHK] DEM_TSFF_RECORD_CLASS_NUM_PER_DTC_MAX_NUM / 1 / 0 */
#endif  /*   ( DEM_TSFF_PM_SUPPORT == STD_ON )         */

    return ;
}

/****************************************************************************/
/* Function Name | Dem_DataMngC_CopyFaultRecord                             */
/* Description   | copy fault record data.                                  */
/* Preconditions | -                                                        */
/* Parameters    | [out] DestFaultRecordPtr :                               */
/*               | [in]  SrcFaultRecordPtr :                                */
/* Return Value  | none.                                                    */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-7-0      | new created.                                             */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMngC_CopyFaultRecord
(
    P2VAR( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) DestFaultRecordPtr,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) SrcFaultRecordPtr
)
{
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) ffrCnt;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonOBDFFRClassNumPerDTCMaxNum;
#if ( DEM_OBDFFD_SUPPORT == STD_ON )   /*  [FuncSw]    */
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) obdFFRClassNumPerDTCMaxNum;
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )            */
#if ( DEM_TSFF_PM_SUPPORT == STD_ON )   /*  [FuncSw]    */
    /*  get TSFFList data.     */
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsfflCnt;
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsfflRecordClassNumPerDTCMaxNum;
#endif  /*   ( DEM_TSFF_PM_SUPPORT == STD_ON )         */

    /*  get fault data.        */
    DestFaultRecordPtr->EventStrgIndex             = SrcFaultRecordPtr->EventStrgIndex;
    DestFaultRecordPtr->OccurrenceOrder            = SrcFaultRecordPtr->OccurrenceOrder;
    DestFaultRecordPtr->ConfirmedOccurrenceOrder   = SrcFaultRecordPtr->ConfirmedOccurrenceOrder;
    DestFaultRecordPtr->MILOccurrenceOrder         = SrcFaultRecordPtr->MILOccurrenceOrder;
    DestFaultRecordPtr->AgingCounter               = SrcFaultRecordPtr->AgingCounter;
#if ( DEM_WWH_OBD_SUPPORT == STD_ON ) /* [FuncSw] */
    DestFaultRecordPtr->TimeAgingCounter           = SrcFaultRecordPtr->TimeAgingCounter;
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */
    DestFaultRecordPtr->HealingCounter             = SrcFaultRecordPtr->HealingCounter;
    DestFaultRecordPtr->ConsistencyCounterForFault = SrcFaultRecordPtr->ConsistencyCounterForFault;

#if ( DEM_OBDFFD_SUPPORT == STD_ON )   /*  [FuncSw]    */
    /*  get OBD FFList data.       */
    obdFFRClassNumPerDTCMaxNum = Dem_CfgInfoPm_GetOBDFFRClassPerDTCMaxNum();
    for( ffrCnt = (Dem_u08_FFListIndexType)0U; ffrCnt < obdFFRClassNumPerDTCMaxNum; ffrCnt++ )                  /* [GUD:for]ffrCnt */
    {
        DestFaultRecordPtr->ObdRecordNumberIndex[ffrCnt] = SrcFaultRecordPtr->ObdRecordNumberIndex[ffrCnt];    /* [GUD]ffrCnt *//* [ARYCHK] DEM_OBD_FFR_CLASS_PER_DTC_MAX_NUM /1/ffrCnt *//* [ARYCHK] DEM_OBD_FFR_CLASS_PER_DTC_MAX_NUM /1/ffrCnt */
    }
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )            */

    /*  get FFList data.       */
    nonOBDFFRClassNumPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;
    for( ffrCnt = (Dem_u08_FFListIndexType)0U; ffrCnt < nonOBDFFRClassNumPerDTCMaxNum; ffrCnt++ )          /* [GUD:for]ffrCnt */
    {
        DestFaultRecordPtr->RecordNumberIndex[ffrCnt] = SrcFaultRecordPtr->RecordNumberIndex[ffrCnt];      /* [GUD]ffrCnt *//* [ARYCHK] DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM /1/ffrCnt *//* [ARYCHK] DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM /1/ffrCnt */
    }


#if ( DEM_TSFF_PM_SUPPORT == STD_ON )   /*  [FuncSw]    */
    /*  get TSFFList data.     */
    tsfflRecordClassNumPerDTCMaxNum = Dem_TSFFRecordClassNumPerDTCMaxNum;
    for( tsfflCnt = (Dem_u08_TSFFListPerDTCIndexType)0U; tsfflCnt < tsfflRecordClassNumPerDTCMaxNum; tsfflCnt++ )                       /* [GUD:for]tsfflCnt */
    {
        DestFaultRecordPtr->TimeSeriesFreezeFrameListIndex[tsfflCnt] = SrcFaultRecordPtr->TimeSeriesFreezeFrameListIndex[tsfflCnt];    /* [GUD]tsffrIndex *//* [ARYCHK] DEM_TSFF_RECORD_CLASS_NUM_PER_DTC_MAX_NUM /1/ tsfflCnt *//* [ARYCHK] DEM_TSFF_RECORD_CLASS_NUM_PER_DTC_MAX_NUM /1/ tsfflCnt */
    }
#endif  /*   ( DEM_TSFF_PM_SUPPORT == STD_ON )         */

    return ;
}


/****************************************************************************/
/* Function Name | Dem_DataMngC_GetFR_FFDIndexListSt                        */
/* Description   | Get frezeframe record index list in fault record.        */
/* Preconditions |                                                          */
/* Parameters    | [in] FaultIndex :                                        */
/*               |        The fault index corresponding to the specific fa- */
/*               |        ult record.                                       */
/*               | [out] FFDIndexListStPtr :                                */
/*               |        The pointer of frezeframe record index list.      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMngC_InitFR_FFDIndexListStData
(
    P2VAR( Dem_FaultRecordPartsFFDIndexListStType, AUTOMATIC, AUTOMATIC ) FFDIndexListStPtr
)
{
    /*  get FFList data.       */
    Dem_DataMng_InitRecordNumberIndexData( &( FFDIndexListStPtr->RecordNumberIndex[0] ) );/* [ARYCHK] DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / 0 */

#if ( DEM_OBDFFD_SUPPORT == STD_ON )   /*  [FuncSw]    */
    /*  get OBD FFList data.       */
    Dem_DataMng_InitObdRecordNumberIndexData( &( FFDIndexListStPtr->ObdRecordNumberIndex[0] ) );/* [ARYCHK] DEM_OBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / 0 */
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )            */

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )   /*  [FuncSw]    */
    /*  get TSFFList data.     */
    Dem_DataMng_InitTSFFListRecordData( &( FFDIndexListStPtr->TimeSeriesFreezeFrameListIndex[0] ) );/* [ARYCHK] DEM_TSFF_RECORD_CLASS_NUM_PER_DTC_MAX_NUM / 1 / 0 */
#endif  /*   ( DEM_TSFF_PM_SUPPORT == STD_ON )         */

    return ;
}
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
#if ( DEM_OBDONUDS_SUPPORT == STD_ON )
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataMngC_CopyFR_AllObdRecordNumberIndex              */
/* Description   | copy ObdRecordNumberIndex[] between fault records.       */
/* Preconditions |                                                          */
/* Parameters    | [in]  FaultIndexDest : fault record index(copy dest.)    */
/*               | [in]  FaultIndexSrc : fault record index(copy src.)      */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMngC_CopyFR_AllObdRecordNumberIndex
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndexDest,
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndexSrc
)
{
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindFault;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) ffrCnt;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) obdFFRClassNumPerDTCMaxNum;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;

    failRecordNum = Dem_FailRecordNum;

    if (( FaultIndexDest < failRecordNum ) && ( FaultIndexSrc < failRecordNum ))    /* [GUD:if] FaultIndexDest *//* [GUD:if] FaultIndexSrc */
    {
        obdFFRClassNumPerDTCMaxNum = Dem_CfgInfoPm_GetOBDFFRClassPerDTCMaxNum();

        /* copy OBDFFD index list. */
        for( ffrCnt = (Dem_u08_FFListIndexType)0U; ffrCnt < obdFFRClassNumPerDTCMaxNum; ffrCnt++ )  /* [GUD:for] ffrCnt */
        {
            Dem_FaultRecordList[FaultIndexDest].ObdRecordNumberIndex[ffrCnt] = Dem_FaultRecordList[FaultIndexSrc].ObdRecordNumberIndex[ffrCnt];    /* [GUD]FaultIndexDest *//* [GUD]FaultIndexSrc *//* [GUD]ffrCnt */
        }

        recMngCmnKindFault = Dem_RecMngCmnKindFault;
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindFault, ( Dem_u16_RecordIndexType )FaultIndexDest );
    }
    return;
}

/****************************************************************************/
/* Function Name | Dem_DataMngC_CompareFR_ObdRecordNumberIndex              */
/* Description   | vompare ObdRecordNumberIndex[] between fault records.    */
/* Preconditions |                                                          */
/* Parameters    | [in]  FaultIndexDest : fault record index(copy dest.)    */
/*               | [in]  FaultIndexSrc : fault record index(copy src.)      */
/* Return Value  | boolean                                                  */
/*               |              TRUE  : same.                               */
/*               |              FALSE : different.                          */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | new created.                                             */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_DataMngC_CompareFR_ObdRecordNumberIndex
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndexDest,
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndexSrc
)
{
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) ffrCnt;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) obdFFRClassNumPerDTCMaxNum;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( boolean, AUTOMATIC ) compareResult;

    failRecordNum   =   Dem_FailRecordNum;

    compareResult   =   (boolean)FALSE;
    if (( FaultIndexDest < failRecordNum ) && ( FaultIndexSrc < failRecordNum ))    /* [GUD:if] FaultIndexDest *//* [GUD:if] FaultIndexSrc */
    {
        compareResult   =   (boolean)TRUE;
        obdFFRClassNumPerDTCMaxNum = Dem_CfgInfoPm_GetOBDFFRClassPerDTCMaxNum();

        /* copy OBDFFD index list. */
        for( ffrCnt = (Dem_u08_FFListIndexType)0U; ffrCnt < obdFFRClassNumPerDTCMaxNum; ffrCnt++ )  /* [GUD:for] ffrCnt */
        {
            if ( Dem_FaultRecordList[FaultIndexDest].ObdRecordNumberIndex[ffrCnt] != Dem_FaultRecordList[FaultIndexSrc].ObdRecordNumberIndex[ffrCnt] )    /* [GUD]FaultIndexDest *//* [GUD]FaultIndexSrc *//* [GUD]ffrCnt */
            {
                compareResult   =   (boolean)FALSE;
                break;
            }
        }
    }
    return compareResult;
}
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )   */
#endif  /* ( DEM_OBDONUDS_SUPPORT == STD_ON )               */



/****************************************************************************/
/* Function Name | Dem_DataMng_InitObdRecordNumberIndexData                 */
/* Description   | Initializes ObdRecordNumberIndex of the specified fault  */
/*               | record.                                                  */
/* Preconditions |                                                          */
/* Parameters    | [out] RecordNumberIndexArrayPtr :                        */
/*               |                  &Dem_TmpEventMemoryEntry.FaultRecord    */
/*               |                  &Dem_TmpDisabledRecord.FaultRecord      */
/*               |                  AUTOMATIC                               */
/*               |        The specified fault record to initialize.         */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_DataMng_InitObdRecordNumberIndexData
(
    P2VAR( Dem_u08_FFDIndexType, AUTOMATIC, DEM_VAR_NO_INIT ) ObdRecordNumberIndexArrayPtr
)
{
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) ffrCnt;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) obdFFRClassNumPerDTCMaxNum;

    obdFFRClassNumPerDTCMaxNum = Dem_CfgInfoPm_GetOBDFFRClassPerDTCMaxNum();

    /* Initialize OBD FFList. */
    for( ffrCnt = (Dem_u08_FFListIndexType)0U; ffrCnt < obdFFRClassNumPerDTCMaxNum; ffrCnt++ )  /* [GUD:for] ffrCnt */
    {
        ObdRecordNumberIndexArrayPtr[ffrCnt] = DEM_FFRECINDEX_INITIAL;                          /* [GUD] ffrCnt *//* [ARYCHK] DEM_OBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / ffrCnt */
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dem_DataMng_InitSpecificObdRecordNumberIndex             */
/* Description   | Initializes specified ObdRecordNumberIndex of the fault  */
/*               | record.                                                  */
/* Preconditions |                                                          */
/* Parameters    | [in]  FaultIndex :                                       */
/*               |        The fault index.                                  */
/* Parameters    | [in]  FreezeFrameListIndex :                             */
/*               |        The specified OBD record number index of fault    */
/*               |        record to initialize.                             */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMng_InitSpecificObdRecordNumberIndex
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,                    /* [PRMCHK:CALLER] */
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameListIndex          /* [PRMCHK:CALLER] */
)
{
    Dem_FaultRecordList[FaultIndex].ObdRecordNumberIndex[FreezeFrameListIndex] = DEM_FFRECINDEX_INITIAL;    /* [GUDCHK:CALLER]FaultIndex *//* [GUDCHK:CALLER]FreezeFrameListIndex */

    return;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */


/****************************************************************************/
/* Function Name | Dem_DataMng_InitRecordNumberIndexdData                   */
/* Description   | Initializes RecordNumberIndex pf the specified fault re- */
/*               | cord.                                                    */
/* Preconditions |                                                          */
/* Parameters    | [out] RecordNumberIndexArrayPtr :                        */
/*               |                  &Dem_TmpEventMemoryEntry.FaultRecord    */
/*               |                  &Dem_TmpDisabledRecord.FaultRecord      */
/*               |                  AUTOMATIC                               */
/*               |        The specified fault record to initialize.         */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_DataMng_InitRecordNumberIndexData
(
    P2VAR( Dem_u08_FFDIndexType, AUTOMATIC, DEM_VAR_NO_INIT ) RecordNumberIndexArrayPtr
)
{
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) ffrCnt;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonOBDFFRClassNumPerDTCMaxNum;

    nonOBDFFRClassNumPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;

    /* Initialize FFList. */
    for( ffrCnt = (Dem_u08_FFListIndexType)0U; ffrCnt < nonOBDFFRClassNumPerDTCMaxNum; ffrCnt++ )   /* [GUD:for] ffrCnt */
    {
        RecordNumberIndexArrayPtr[ffrCnt] = DEM_FFRECINDEX_INITIAL;                                 /* [GUD] ffrCnt *//* [ARYCHK] DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / ffrCnt */
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dem_DataMng_InitSpecificRecordNumberIndex                */
/* Description   | Initializes specified RecordNumberIndex of the fault     */
/*               | record.                                                  */
/* Preconditions |                                                          */
/* Parameters    | [in]  FaultIndex :                                       */
/*               |        The fault index.                                  */
/* Parameters    | [in]  FreezeFrameListIndex :                             */
/*               |        The specified  record number index of fault       */
/*               |        record to initialize.                             */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMng_InitSpecificRecordNumberIndex
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,                    /* [PRMCHK:CALLER] */
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameListIndex          /* [PRMCHK:CALLER] */
)
{
    Dem_FaultRecordList[FaultIndex].RecordNumberIndex[FreezeFrameListIndex] = DEM_FFRECINDEX_INITIAL;   /* [GUDCHK:CALLER]FaultIndex *//* [GUDCHK:CALLER]FreezeFrameListIndex */

    return;
}


#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataMng_UpdateFaultRecordConsistencyId_Displacement  */
/* Description   | Decriment and sets the consistency Id of the fault       */
/*               | record to the fault record list corresponding to the     */
/*               | specified fault index.                                   */
/* Preconditions | none                                                     */
/*               |                                                          */
/* Parameters    | [in] FaultIndex :                                        */
/*               |        The fault index corresponding to the specific fa- */
/*               |        ult record.                                       */
/*               | [out] ConsistencyId :                                    */
/*               |        updated consistencyId                             */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMng_UpdateFaultRecordConsistencyId_Displacement
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) ConsistencyIdPtr
)
{
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) consistencyId;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindFault;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;

    failRecordNum = Dem_FailRecordNum;

    if( FaultIndex < failRecordNum )                                                    /* [GUD:if] FaultIndex */
    {
        consistencyId = Dem_FaultRecordList[FaultIndex].ConsistencyCounterForFault;     /* [GUD] FaultIndex */

        consistencyId = Dem_UtlCid_CalcConsistencyId( consistencyId );

        Dem_FaultRecordList[FaultIndex].ConsistencyCounterForFault = consistencyId;     /* [GUD] FaultIndex */

        recMngCmnKindFault = Dem_RecMngCmnKindFault;
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindFault, ( Dem_u16_RecordIndexType )FaultIndex );

        *ConsistencyIdPtr = consistencyId;
    }
    else
    {
        *ConsistencyIdPtr = DEM_CONSISTENCY_INITIAL;
    }

    return;
}
#endif  /*   ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */


#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataMng_UpdateFaultRecordConsistencyId_Misfire       */
/* Description   | Decriment and sets the consistency Id of the fault       */
/*               | record to the fault record list corresponding to the     */
/*               | specified fault index.                                   */
/* Preconditions | none                                                     */
/*               |                                                          */
/* Parameters    | [in] FaultIndex :                                        */
/*               |        The fault index corresponding to the specific fa- */
/*               |        ult record.                                       */
/*               | [out] ConsistencyId :                                    */
/*               |        updated consistencyId                             */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMng_UpdateFaultRecordConsistencyId_Misfire
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) ConsistencyIdPtr
)
{
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) consistencyId;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindFault;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;

    failRecordNum = Dem_FailRecordNum;

    if( FaultIndex < failRecordNum )                                                    /* [GUD:if] FaultIndex */
    {
        consistencyId = Dem_FaultRecordList[FaultIndex].ConsistencyCounterForFault;     /* [GUD] FaultIndex */

        consistencyId = Dem_UtlCid_CalcConsistencyId( consistencyId );

        Dem_FaultRecordList[FaultIndex].ConsistencyCounterForFault = consistencyId;     /* [GUD] FaultIndex */

        recMngCmnKindFault = Dem_RecMngCmnKindFault;
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindFault, ( Dem_u16_RecordIndexType )FaultIndex );

        *ConsistencyIdPtr = consistencyId;
    }
    else
    {
        *ConsistencyIdPtr = DEM_CONSISTENCY_INITIAL;
    }

    return;
}
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )    */


/****************************************************************************/
/* Function Name | Dem_DataMng_SetFaultRecordConsistencyId                  */
/* Description   | Decriment and sets the consistency Id of the fault       */
/*               | record to the fault record list corresponding to the     */
/*               | specified fault index.                                   */
/* Preconditions | none                                                     */
/*               |                                                          */
/* Parameters    | [in] FaultIndex :                                        */
/*               |        The fault index corresponding to the specific fa- */
/*               |        ult record.                                       */
/*               | [in] ConsistencyId :                                     */
/*               |        updated consistencyId                             */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMng_SetFaultRecordConsistencyId
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId
)
{
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindFault;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;

    recMngCmnKindFault = Dem_RecMngCmnKindFault;
    failRecordNum = Dem_FailRecordNum;

    if( FaultIndex < failRecordNum )                                                            /* [GUD:if] FaultIndex */
    {
        Dem_FaultRecordList[FaultIndex].ConsistencyCounterForFault = ConsistencyId;             /* [GUD] FaultIndex */
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindFault, ( Dem_u16_RecordIndexType )FaultIndex );
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_DataMng_GetFaultRecordConsistencyId                  */
/* Description   | gets the consistency Id of the fault record              */
/* Preconditions | none                                                     */
/*               |                                                          */
/* Parameters    | [in] FaultIndex :                                        */
/*               |        The fault index corresponding to the specific fa- */
/*               |        ult record.                                       */
/*               | [out] ConsistencyIdPtr :                                 */
/*               |        consistencyId                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMng_GetFaultRecordConsistencyId
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) ConsistencyIdPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;

    failRecordNum = Dem_FailRecordNum;

    retVal = (boolean)FALSE;

    if( FaultIndex < failRecordNum )                                                        /* [GUD:if] FaultIndex */
    {
        *ConsistencyIdPtr = Dem_FaultRecordList[FaultIndex].ConsistencyCounterForFault;     /* [GUD] FaultIndex */
        retVal = (boolean)TRUE;
    }

    return retVal;
}


#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataMngC_InitObdRecordNumberIndexFFROverwritten      */
/* Description   | Initializes  the freeze frame list index of the fault r- */
/*               | ecord to the fault record list corresponding to the spe- */
/*               | cified fault index and OBD freeze frame record index.    */
/* Preconditions | The specified fault index be within the range of the fa- */
/*               | ult record list.                                         */
/*               | The specified freeze frame list index be within the ran- */
/*               | ge of the arry of ObdeRecordNumberIndex.                 */
/* Parameters    | [in] FaultIndex :                                        */
/*               |        The fault index corresponding to the specific fa- */
/*               |        ult record.                                       */
/*               | [in] FFRIndex :                                          */
/*               |        The freeze frame record index which to be overwr- */
/*               |        itten of the fault record corresponding to the s- */
/*               |        pecified FaultIndex.                              */
/*               | [out] EventStrgIndexPtr :                                */
/*               |        The Event record index corresponding to the       */
/*               |        specified FaultIndex.                             */
/*               | [out] ConsistencyIdPtr :                                 */
/*               |        Updated ConsistencyID                             */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMngC_InitObdRecordNumberIndexFFROverwritten
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) FFRIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr,
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) ConsistencyIdPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) ffListIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) obdFFRClassNumPerDTCMaxNum;
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) consistencyId;

    failRecordNum = Dem_FailRecordNum;
    obdFFRClassNumPerDTCMaxNum = Dem_CfgInfoPm_GetOBDFFRClassPerDTCMaxNum();

    if( FaultIndex < failRecordNum )                                            /* [GUD:if] FaultIndex */
    {
        for( ffListIndex = (Dem_u08_FFListIndexType)0U; ffListIndex < obdFFRClassNumPerDTCMaxNum; ffListIndex++ )   /* [GUD:for] ffListIndex */
        {
            if( FFRIndex == Dem_FaultRecordList[FaultIndex].ObdRecordNumberIndex[ffListIndex] )                     /* [GUD] FaultIndex *//* [GUD] ffListIndex */
            {
                Dem_FaultRecordList[FaultIndex].ObdRecordNumberIndex[ffListIndex] = DEM_FFRECINDEX_INITIAL;         /* [GUD] FaultIndex *//* [GUD] ffListIndex */
                Dem_DataMng_UpdateFaultRecordConsistencyId_Displacement( FaultIndex, &consistencyId );

                eventStrgIndex = Dem_FaultRecordList[FaultIndex].EventStrgIndex;                                    /* [GUD] FaultIndex */
                Dem_DataMng_SetEventRecordConsistencyId( eventStrgIndex, consistencyId );

                *EventStrgIndexPtr = eventStrgIndex;
                *ConsistencyIdPtr  = consistencyId;

                break;
            }
        }
    }

    return;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */


/****************************************************************************/
/* Function Name | Dem_DataMngC_InitRecordNumberIndexFFROverwritten         */
/* Description   | Initializes  the freeze frame list index of the fault r- */
/*               | ecord to the fault record list corresponding to the spe- */
/*               | cified fault index and freeze frame record index.        */
/* Preconditions | The specified fault index be within the range of the fa- */
/*               | ult record list.                                         */
/*               | The specified freeze frame list index be within the ran- */
/*               | ge of the arry of RecordNumberIndex.                     */
/* Parameters    | [in] FaultIndex :                                        */
/*               |        The fault index corresponding to the specific fa- */
/*               |        ult record.                                       */
/*               | [in] FFRIndex :                                          */
/*               |        The freeze frame record index which to be overwr- */
/*               |        itten of the fault record corresponding to the s- */
/*               |        pecified FaultIndex.                              */
/*               | [out] EventStrgIndexPtr :                                */
/*               |        The Event record index corresponding to the       */
/*               |        specified FaultIndex.                             */
/*               | [out] ConsistencyIdPtr :                                 */
/*               |        Updated ConsistencyID                             */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMngC_InitRecordNumberIndexFFROverwritten
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) FFRIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr,
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) ConsistencyIdPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) ffListIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonOBDFFRClassNumPerDTCMaxNum;
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) consistencyId;

    failRecordNum = Dem_FailRecordNum;
    nonOBDFFRClassNumPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;

    if( FaultIndex < failRecordNum )                                            /* [GUD:if] FaultIndex */
    {
        for( ffListIndex = (Dem_u08_FFListIndexType)0U; ffListIndex < nonOBDFFRClassNumPerDTCMaxNum; ffListIndex++  )   /* [GUD:for] ffListIndex */
        {
            if( FFRIndex == Dem_FaultRecordList[FaultIndex].RecordNumberIndex[ffListIndex] )                            /* [GUD] FaultIndex *//* [GUD] ffListIndex */
            {
                Dem_FaultRecordList[FaultIndex].RecordNumberIndex[ffListIndex] = DEM_FFRECINDEX_INITIAL;                /* [GUD] FaultIndex *//* [GUD] ffListIndex */
                Dem_DataMng_UpdateFaultRecordConsistencyId_Displacement( FaultIndex, &consistencyId );

                eventStrgIndex = Dem_FaultRecordList[FaultIndex].EventStrgIndex;                                        /* [GUD] FaultIndex */
                Dem_DataMng_SetEventRecordConsistencyId( eventStrgIndex, consistencyId );

                *EventStrgIndexPtr = eventStrgIndex;
                *ConsistencyIdPtr  = consistencyId;

                break;
            }
        }
    }

    return;
}
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */


/****************************************************************************/
/* Function Name | Dem_DataMng_InitFaultRecord_Ctl                          */
/* Description   | Initializes the specified fault record.                  */
/* Preconditions |                                                          */
/* Parameters    | [in] FaultIndex :                                        */
/*               |        The fault index corresponding to the specific fa- */
/*               |        ult record.                                       */
/* Return Value  | void                                                     */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_DataMng_InitFaultRecord_Ctl
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex                     /* [PRMCHK:CALLER] */
)
{
    /* Sets initial value to the specified fault record. */
    Dem_FaultRecordList[FaultIndex].EventStrgIndex           = DEM_EVENTSTRGINDEX_INVALID;                  /* [GUDCHK:CALLER]FaultIndex */
    Dem_FaultRecordList[FaultIndex].OccurrenceOrder          = DEM_FAIL_OCCURRENCE_NUM_INVALID;             /* [GUDCHK:CALLER]FaultIndex */
    Dem_FaultRecordList[FaultIndex].ConfirmedOccurrenceOrder = DEM_FAIL_OCCURRENCE_NUM_INVALID;             /* [GUDCHK:CALLER]FaultIndex */
    Dem_FaultRecordList[FaultIndex].MILOccurrenceOrder       = DEM_FAIL_OCCURRENCE_NUM_INVALID;             /* [GUDCHK:CALLER]FaultIndex */
    Dem_FaultRecordList[FaultIndex].AgingCounter             = DEM_AGING_COUNT_INITIAL_VALUE;               /* [GUDCHK:CALLER]FaultIndex */
#if ( DEM_WWH_OBD_SUPPORT == STD_ON ) /* [FuncSw] */
    Dem_FaultRecordList[FaultIndex].TimeAgingCounter         = DEM_TIME_AGING_COUNT_INITIAL_VALUE;          /* [GUDCHK:CALLER]FaultIndex */
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */
    Dem_FaultRecordList[FaultIndex].HealingCounter           = DEM_HEALING_COUNT_INITIAL_VALUE;             /* [GUDCHK:CALLER]FaultIndex */

#if ( DEM_OBDFFD_SUPPORT == STD_ON )   /*  [FuncSw]    */
    /* Initialize OBD FFList. */
    Dem_DataMng_InitObdRecordNumberIndex( FaultIndex );         /* [GUDCHK:CALLER]FaultIndex */
#endif  /*   ( DEM_OBDFFD_SUPPORT == STD_ON )          */

    /* Initialize FFList. */
    Dem_DataMng_InitRecordNumberIndex( FaultIndex );            /* [GUDCHK:CALLER]FaultIndex */

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )   /*  [FuncSw]    */
    /* Initialize TSFFList. */
    Dem_DataMng_InitTSFFListRecord( FaultIndex );               /* [GUDCHK:CALLER]FaultIndex */
#endif  /*   ( DEM_TSFF_PM_SUPPORT == STD_ON )         */

    return ;
}


/****************************************************************************/
/* Function Name | Dem_DataMng_InitObdRecordNumberIndex                     */
/* Description   | Initializes ObdRecordNumberIndex of the specified fault  */
/*               | record.                                                  */
/* Preconditions |                                                          */
/* Parameters    | [in] FaultIndex :                                        */
/*               |        The fault index corresponding to the specific fa- */
/*               |        ult record.                                       */
/* Return Value  | void                                                     */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_DataMng_InitObdRecordNumberIndex
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex                     /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) ffrCnt;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) obdFFRClassNumPerDTCMaxNum;

    obdFFRClassNumPerDTCMaxNum = Dem_OBDFFRClassPerDTCMaxNum;

    /* Initialize OBD FFList. */
    for( ffrCnt = (Dem_u08_FFListIndexType)0U; ffrCnt < obdFFRClassNumPerDTCMaxNum; ffrCnt++ )  /* [GUD:for]ffrCnt */
    {
        Dem_FaultRecordList[FaultIndex].ObdRecordNumberIndex[ffrCnt] = DEM_FFRECINDEX_INITIAL;  /* [GUDCHK:CALLER]FaultIndex *//* [GUD]ffrCnt */
    }

    return ;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */


/****************************************************************************/
/* Function Name | Dem_DataMng_InitRecordNumberIndex                        */
/* Description   | Initializes RecordNumberIndex of the specified fault re- */
/*               |  cord.                                                   */
/* Preconditions |                                                          */
/* Parameters    | [in] FaultIndex :                                        */
/*               |        The fault index corresponding to the specific fa- */
/*               |        ult record.                                       */
/* Return Value  | void                                                     */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_DataMng_InitRecordNumberIndex
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex                     /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) ffrCnt;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonOBDFFRClassNumPerDTCMaxNum;

    nonOBDFFRClassNumPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;

    /* Initialize FFList. */
    for( ffrCnt = (Dem_u08_FFListIndexType)0U; ffrCnt < nonOBDFFRClassNumPerDTCMaxNum; ffrCnt++ )   /* [GUD:for]ffrCnt */
    {
        Dem_FaultRecordList[FaultIndex].RecordNumberIndex[ffrCnt] = DEM_FFRECINDEX_INITIAL;         /* [GUDCHK:CALLER]FaultIndex *//* [GUD]ffrCnt */
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dem_DataMng_GetFaultRecord_Ctl                           */
/* Description   | Get fault record data. (for Control data)                */
/* Preconditions | The specified fault index be within the range of the fa- */
/*               | ult record list.                                         */
/* Parameters    | [in] FaultIndex :                                        */
/*               |        The fault index corresponding to the specific fa- */
/*               |        ult record.                                       */
/*               | [out] FaultRecordPtr :                                   */
/*               |        The pointer of the fault record corresponding to  */
/*               |         the specified fault index.                       */
/*               |                    &Dem_TmpDisabledRecord.FaultRecord    */
/*               |                    &Dem_TmpEventMemoryEntry.FaultRecord  */
/*               |                    AUTOMATIC                             */
/* Return Value  | none.                                                    */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_DataMng_GetFaultRecord_Ctl
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,                            /* [PRMCHK:CALLER] */
    P2VAR( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) DestFaultRecordPtr
)
{
    /*  get fault data.        */
    DestFaultRecordPtr->EventStrgIndex           = Dem_FaultRecordList[FaultIndex].EventStrgIndex;                  /* [GUDCHK:CALLER]FaultIndex */
    DestFaultRecordPtr->OccurrenceOrder          = Dem_FaultRecordList[FaultIndex].OccurrenceOrder;                 /* [GUDCHK:CALLER]FaultIndex */
    DestFaultRecordPtr->ConfirmedOccurrenceOrder = Dem_FaultRecordList[FaultIndex].ConfirmedOccurrenceOrder;        /* [GUDCHK:CALLER]FaultIndex */
    DestFaultRecordPtr->MILOccurrenceOrder       = Dem_FaultRecordList[FaultIndex].MILOccurrenceOrder;              /* [GUDCHK:CALLER]FaultIndex */
    DestFaultRecordPtr->AgingCounter             = Dem_FaultRecordList[FaultIndex].AgingCounter;                    /* [GUDCHK:CALLER]FaultIndex */
#if ( DEM_WWH_OBD_SUPPORT == STD_ON ) /* [FuncSw] */
    DestFaultRecordPtr->TimeAgingCounter         = Dem_FaultRecordList[FaultIndex].TimeAgingCounter;                /* [GUDCHK:CALLER]FaultIndex */
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */
    DestFaultRecordPtr->HealingCounter           = Dem_FaultRecordList[FaultIndex].HealingCounter;                  /* [GUDCHK:CALLER]FaultIndex */
    DestFaultRecordPtr->ConsistencyCounterForFault = Dem_FaultRecordList[FaultIndex].ConsistencyCounterForFault;    /* [GUDCHK:CALLER]FaultIndex */

#if ( DEM_OBDFFD_SUPPORT == STD_ON )   /*  [FuncSw]    */
    /*  get OBD FFList data.       */
    Dem_DataMng_GetObdRecordNumberIndex_Ctl( FaultIndex, &( DestFaultRecordPtr->ObdRecordNumberIndex[0] ) );        /* [GUDCHK:CALLER]FaultIndex *//* [ARYCHK] DEM_OBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / 0 */
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )            */

    /*  get FFList data.       */
    Dem_DataMng_GetRecordNumberIndexCtl( FaultIndex, &( DestFaultRecordPtr->RecordNumberIndex[0] ) );               /* [GUDCHK:CALLER]FaultIndex *//* [ARYCHK] DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / 0 */

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )   /*  [FuncSw]    */
    /*  get TSFFList data.     */
    Dem_DataMng_GetTSFFListRecord_Ctl( FaultIndex, &( DestFaultRecordPtr->TimeSeriesFreezeFrameListIndex[0] ) );    /* [GUDCHK:CALLER]FaultIndex *//* [ARYCHK] DEM_TSFF_RECORD_CLASS_NUM_PER_DTC_MAX_NUM / 1 / 0 */
#endif  /*   ( DEM_TSFF_PM_SUPPORT == STD_ON )         */

    return ;
}


/****************************************************************************/
/* Function Name | Dem_DataMng_GetObdRecordNumberIndex_Ctl                  */
/* Description   | Get ObdRecordNumberIndex of fault record data.           */
/*               | (for Control data)                                       */
/* Preconditions | The specified fault index be within the range of the fa- */
/*               | ult record list.                                         */
/* Parameters    | [in] FaultIndex :                                        */
/*               |        The fault index corresponding to the specific fa- */
/*               |        ult record.                                       */
/*               | [out] ObdRecordNumberIndexArrayPtr :                     */
/*               |        The pointer of the fault record corresponding to  */
/*               |         the specified fault index.                       */
/*               |                    &Dem_TmpDisabledRecord.FaultRecord    */
/*               |                    &Dem_TmpEventMemoryEntry.FaultRecord  */
/*               |                    AUTOMATIC                             */
/* Return Value  | none.                                                    */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_DataMng_GetObdRecordNumberIndex_Ctl
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,                                    /* [PRMCHK:CALLER] */
    P2VAR( Dem_u08_FFDIndexType, AUTOMATIC, DEM_VAR_NO_INIT ) ObdRecordNumberIndexArrayPtr
)
{
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) ffrCnt;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) obdFFRClassNumPerDTCMaxNum;

    obdFFRClassNumPerDTCMaxNum = Dem_CfgInfoPm_GetOBDFFRClassPerDTCMaxNum();

    /*  get OBD FFList data.       */
    for( ffrCnt = (Dem_u08_FFListIndexType)0U; ffrCnt < obdFFRClassNumPerDTCMaxNum; ffrCnt++ )                  /* [GUD:for]ffrCnt */
    {
        ObdRecordNumberIndexArrayPtr[ffrCnt] = Dem_FaultRecordList[FaultIndex].ObdRecordNumberIndex[ffrCnt];    /* [GUDCHK:CALLER]FaultIndex *//* [GUD]ffrCnt *//* [ARYCHK] DEM_OBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / ffrCnt */
    }

    return ;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */


/****************************************************************************/
/* Function Name | Dem_DataMng_GetRecordNumberIndexCtl                      */
/* Description   | Get RecordNumberIndex of fault record data.              */
/*               | (for Control data)                                       */
/* Preconditions | The specified fault index be within the range of the fa- */
/*               | ult record list.                                         */
/* Parameters    | [in] FaultIndex :                                        */
/*               |        The fault index corresponding to the specific fa- */
/*               |        ult record.                                       */
/*               | [out] RecordNumberIndexArrayPtr :                        */
/*               |        The pointer of the fault record corresponding to  */
/*               |         the specified fault index.                       */
/*               |                    &Dem_TmpDisabledRecord.FaultRecord    */
/*               |                    &Dem_TmpEventMemoryEntry.FaultRecord  */
/*               |                    AUTOMATIC                             */
/* Return Value  | none.                                                    */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_DataMng_GetRecordNumberIndexCtl
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,                                    /* [PRMCHK:CALLER] */
    P2VAR( Dem_u08_FFDIndexType, AUTOMATIC, DEM_VAR_NO_INIT ) RecordNumberIndexArrayPtr
)
{
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) ffrCnt;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonOBDFFRClassNumPerDTCMaxNum;

    nonOBDFFRClassNumPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;

    /*  get FFList data.       */
    for( ffrCnt = (Dem_u08_FFListIndexType)0U; ffrCnt < nonOBDFFRClassNumPerDTCMaxNum; ffrCnt++ )           /* [GUD:for]ffrCnt */
    {
        RecordNumberIndexArrayPtr[ffrCnt] = Dem_FaultRecordList[FaultIndex].RecordNumberIndex[ffrCnt];      /* [GUDCHK:CALLER]FaultIndex *//* [GUD]ffrCnt *//* [ARYCHK] DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / ffrCnt */
    }

    return ;
}


#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataMng_GetFaultRecord_MM                            */
/* Description   | Get fault record data. (for MM data)                     */
/* Preconditions | The specified fault index be within the range of the fa- */
/*               | ult record list.                                         */
/* Parameters    | [in] FaultIndex :                                        */
/*               |        The fault index corresponding to the specific fa- */
/*               |        ult record.                                       */
/*               | [out] FaultRecordPtr :                                   */
/*               |        The pointer of the fault record corresponding to  */
/*               |         the specified fault index.                       */
/*               |                    &Dem_TmpDisabledRecord.FaultRecord    */
/*               |                    &Dem_TmpEventMemoryEntry.FaultRecord  */
/*               |                    AUTOMATIC                             */
/* Return Value  | none.                                                    */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_DataMng_GetFaultRecord_MM
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,                    /* [PRMCHK:CALLER] */
    P2VAR( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) DestFaultRecordPtr
)
{
    /*  copy CCid.              */
    DestFaultRecordPtr->ConsistencyCounterForFault = Dem_FaultRecordList[FaultIndex].ConsistencyCounterForFault;    /* [GUDCHK:CALLER]FaultIndex */

#if ( DEM_FAULT_RECORD_PADDING_EXIST == STD_ON )    /*  [FuncSw]    */
    /*  copy padding.           */
    Dem_DataMng_GetFR_PaddingRecord( FaultIndex, DestFaultRecordPtr );
#endif  /* ( DEM_FAULT_RECORD_PADDING_EXIST == STD_ON )             */

    return ;
}
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */


/****************************************************************************/
/* Function Name | Dem_DataMng_SetFaultRecord_Ctl                           */
/* Description   | Set fault record data. (for Control data)                */
/* Preconditions | The specified fault index be within the range of the fa- */
/*               | ult record list.                                         */
/* Parameters    | [in] FaultIndex :                                        */
/*               |        The fault index corresponding to the specific fa- */
/*               |        ult record.                                       */
/*               | [in] FaultRecordPtr :                                    */
/*               |                     &Dem_TmpEventMemoryEntry.FaultRecord */
/*               |        The pointer of the fault record corresponding to  */
/*               |         the specified fault index.                       */
/* Return Value  | none.                                                    */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_DataMng_SetFaultRecord_Ctl
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,                            /* [PRMCHK:CALLER] */
    P2CONST( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) SrcFaultRecordPtr
)
{
    /*  set fault data.        */
    Dem_FaultRecordList[FaultIndex].EventStrgIndex           = SrcFaultRecordPtr->EventStrgIndex;               /* [GUDCHK:CALLER]FaultIndex */
    Dem_FaultRecordList[FaultIndex].OccurrenceOrder          = SrcFaultRecordPtr->OccurrenceOrder;              /* [GUDCHK:CALLER]FaultIndex */
    Dem_FaultRecordList[FaultIndex].ConfirmedOccurrenceOrder = SrcFaultRecordPtr->ConfirmedOccurrenceOrder;     /* [GUDCHK:CALLER]FaultIndex */
    Dem_FaultRecordList[FaultIndex].MILOccurrenceOrder       = SrcFaultRecordPtr->MILOccurrenceOrder;           /* [GUDCHK:CALLER]FaultIndex */
    Dem_FaultRecordList[FaultIndex].AgingCounter             = SrcFaultRecordPtr->AgingCounter;                 /* [GUDCHK:CALLER]FaultIndex */
#if ( DEM_WWH_OBD_SUPPORT == STD_ON ) /* [FuncSw] */
    Dem_FaultRecordList[FaultIndex].TimeAgingCounter         = SrcFaultRecordPtr->TimeAgingCounter;             /* [GUDCHK:CALLER]FaultIndex */
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */
    Dem_FaultRecordList[FaultIndex].HealingCounter           = SrcFaultRecordPtr->HealingCounter;               /* [GUDCHK:CALLER]FaultIndex */

#if ( DEM_OBDFFD_SUPPORT == STD_ON )   /*  [FuncSw]    */
    /*  set OBD FFList data.       */
    Dem_DataMng_SetObdRecordNumberIndex_Ctl( FaultIndex, SrcFaultRecordPtr );               /* [GUDCHK:CALLER]FaultIndex */
#endif /*   ( DEM_OBDFFD_SUPPORT == STD_ON )           */

    /*  set FFList data.       */
    Dem_DataMng_SetRecordNumberIndex_Ctl( FaultIndex, SrcFaultRecordPtr );                  /* [GUDCHK:CALLER]FaultIndex */

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )   /*  [FuncSw]    */
    /*  set TSFFList data.     */
    Dem_DataMng_SetTSFFListRecord_Ctl( FaultIndex, SrcFaultRecordPtr );                     /* [GUDCHK:CALLER]FaultIndex */
#endif  /*   ( DEM_TSFF_PM_SUPPORT == STD_ON )         */

    return ;
}


/****************************************************************************/
/* Function Name | Dem_DataMng_SetObdRecordNumberIndex_Ctl                  */
/* Description   | Set ObdRecordNumberIndex offault record data.            */
/*               | (for Control data)                                       */
/* Preconditions | The specified fault index be within the range of the fa- */
/*               | ult record list.                                         */
/* Parameters    | [in] FaultIndex :                                        */
/*               |        The fault index corresponding to the specific fa- */
/*               |        ult record.                                       */
/*               | [in] FaultRecordPtr :                                    */
/*               |                     &Dem_TmpEventMemoryEntry.FaultRecord */
/*               |        The pointer of the fault record corresponding to  */
/*               |         the specified fault index.                       */
/* Return Value  | none.                                                    */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_DataMng_SetObdRecordNumberIndex_Ctl
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,                            /* [PRMCHK:CALLER] */
    P2CONST( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) SrcFaultRecordPtr
)
{
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) ffrCnt;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) obdFFRClassNumPerDTCMaxNum;

    obdFFRClassNumPerDTCMaxNum = Dem_CfgInfoPm_GetOBDFFRClassPerDTCMaxNum();

    /*  set OBD FFList data.       */
    for( ffrCnt = (Dem_u08_FFListIndexType)0U; ffrCnt < obdFFRClassNumPerDTCMaxNum; ffrCnt++ )                              /* [GUD:for]ffrCnt */
    {
        Dem_FaultRecordList[FaultIndex].ObdRecordNumberIndex[ffrCnt] = SrcFaultRecordPtr->ObdRecordNumberIndex[ffrCnt];     /* [GUDCHK:CALLER]FaultIndex *//* [GUD]ffrCnt *//* [ARYCHK] DEM_OBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / ffrCnt */
    }

    return ;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */


/****************************************************************************/
/* Function Name | Dem_DataMng_SetRecordNumberIndex_Ctl                     */
/* Description   | Set RecordNumberIndex of fault record data.              */
/*               | (for Control data)                                       */
/* Preconditions | The specified fault index be within the range of the fa- */
/*               | ult record list.                                         */
/* Parameters    | [in] FaultIndex :                                        */
/*               |        The fault index corresponding to the specific fa- */
/*               |        ult record.                                       */
/*               | [in] FaultRecordPtr :                                    */
/*               |                     &Dem_TmpEventMemoryEntry.FaultRecord */
/*               |        The pointer of the fault record corresponding to  */
/*               |         the specified fault index.                       */
/* Return Value  | none.                                                    */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_DataMng_SetRecordNumberIndex_Ctl
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,                            /* [PRMCHK:CALLER] */
    P2CONST( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) SrcFaultRecordPtr
)
{
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) ffrCnt;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonOBDFFRClassNumPerDTCMaxNum;

    nonOBDFFRClassNumPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;

    /*  set FFList data.       */
    for( ffrCnt = (Dem_u08_FFListIndexType)0U; ffrCnt < nonOBDFFRClassNumPerDTCMaxNum; ffrCnt++ )                           /* [GUD:for]ffrCnt */
    {
        Dem_FaultRecordList[FaultIndex].RecordNumberIndex[ffrCnt] = SrcFaultRecordPtr->RecordNumberIndex[ffrCnt];           /* [GUDCHK:CALLER]FaultIndex *//* [GUD]ffrCnt *//* [ARYCHK] DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / ffrCnt */
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dem_DataMng_CmpWithFaultRecord                           */
/* Description   | compare data.                                            */
/* Preconditions |                                                          */
/* Parameters    | [in] FaultIndex :                                        */
/*               | [in] CheckFaultRecordPtr :                               */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK  : same.                               */
/*               |        DEM_IRT_NG  : different.                          */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMng_CmpWithFaultRecord
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,                                /* [PRMCHK:CALLER] */
    P2CONST( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) CheckFaultRecordPtr      /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfComWithRecNumIndex;
    P2VAR( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) faultRecordPtr;

    faultRecordPtr = &Dem_FaultRecordList[FaultIndex];                                                  /* [GUDCHK:CALLER]FaultIndex *//* [GUD:CFG:IF_GUARDED: FaultIndex ]faultRecordPtr */

    if( faultRecordPtr->EventStrgIndex != CheckFaultRecordPtr->EventStrgIndex )                         /* [GUDCHK:CALLER]FaultIndex *//* [GUDCHK:CALLER]CheckFaultRecordPtr */
    {
        retVal = DEM_IRT_NG;
    }
    else if( faultRecordPtr->OccurrenceOrder != CheckFaultRecordPtr->OccurrenceOrder )                  /* [GUDCHK:CALLER]FaultIndex *//* [GUDCHK:CALLER]CheckFaultRecordPtr */
    {
        retVal = DEM_IRT_NG;
    }
    else if( faultRecordPtr->ConfirmedOccurrenceOrder != CheckFaultRecordPtr->ConfirmedOccurrenceOrder )    /* [GUDCHK:CALLER]FaultIndex *//* [GUDCHK:CALLER]CheckFaultRecordPtr */
    {
        retVal = DEM_IRT_NG;
    }
    else if( faultRecordPtr->MILOccurrenceOrder != CheckFaultRecordPtr->MILOccurrenceOrder )            /* [GUDCHK:CALLER]FaultIndex *//* [GUDCHK:CALLER]CheckFaultRecordPtr */
    {
        retVal = DEM_IRT_NG;
    }
    else if( faultRecordPtr->AgingCounter != CheckFaultRecordPtr->AgingCounter )                        /* [GUDCHK:CALLER]FaultIndex *//* [GUDCHK:CALLER]CheckFaultRecordPtr */
    {
        retVal = DEM_IRT_NG;
    }
#if ( DEM_WWH_OBD_SUPPORT == STD_ON ) /* [FuncSw] */
    else if( faultRecordPtr->TimeAgingCounter != CheckFaultRecordPtr->TimeAgingCounter )                /* [GUDCHK:CALLER]FaultIndex *//* [GUDCHK:CALLER]CheckFaultRecordPtr */
    {
        retVal = DEM_IRT_NG;
    }
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */
    else if( faultRecordPtr->HealingCounter != CheckFaultRecordPtr->HealingCounter )                    /* [GUDCHK:CALLER]FaultIndex *//* [GUDCHK:CALLER]CheckFaultRecordPtr */
    {
        retVal = DEM_IRT_NG;
    }
    else
    {
        resultOfComWithRecNumIndex = Dem_DataMng_CmpWithRecordNumberIndex( FaultIndex, CheckFaultRecordPtr );   /* [GUDCHK:CALLER]FaultIndex *//* [GUDCHK:CALLER]CheckFaultRecordPtr */
        if( resultOfComWithRecNumIndex == DEM_IRT_OK )
        {
            /* check TSFF list. */
            retVal = Dem_DataMng_CmpWithTSFFListRecord( FaultIndex, CheckFaultRecordPtr );                      /* [GUDCHK:CALLER]FaultIndex *//* [GUDCHK:CALLER]CheckFaultRecordPtr */
        }
        else
        {
            /* different. */
            retVal = DEM_IRT_NG;
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DataMng_CmpWithRecordNumberIndex                     */
/* Description   | Compere an array of RecordNumberIndex.                   */
/* Preconditions |                                                          */
/* Parameters    | [in] FaultIndex :                                        */
/*               | [in] CheckFaultRecordPtr :                               */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK  : same.                               */
/*               |        DEM_IRT_NG  : different.                          */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMng_CmpWithRecordNumberIndex
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,                            /* [PRMCHK:CALLER] */
    P2CONST( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) CheckFaultRecordPtr  /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfComWithObdRecNumIndex;
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfComWithNonObdRecNumIndex;

    /* different. */
    retVal = DEM_IRT_NG;

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
    resultOfComWithObdRecNumIndex = Dem_DataMng_CmpWithObdRecordNumberIndex( FaultIndex, CheckFaultRecordPtr );             /* [GUDCHK:CALLER]FaultIndex *//* [GUDCHK:CALLER]CheckFaultRecordPtr */
    if( resultOfComWithObdRecNumIndex == DEM_IRT_OK )
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */
    {
        resultOfComWithNonObdRecNumIndex = Dem_DataMng_CmpWithNonObdRecordNumberIndex( FaultIndex, CheckFaultRecordPtr );   /* [GUDCHK:CALLER]FaultIndex *//* [GUDCHK:CALLER]CheckFaultRecordPtr */
        if( resultOfComWithNonObdRecNumIndex == DEM_IRT_OK )
        {
            /* same. */
            retVal = DEM_IRT_OK;
        }
    }

    return retVal;
}

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataMng_CmpWithObdRecordNumberIndex                  */
/* Description   | Compere an array of RecordNumberIndex for OBD.           */
/* Preconditions |                                                          */
/* Parameters    | [in] FaultIndex :                                        */
/*               | [in] CheckFaultRecordPtr :                               */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK  : same.                               */
/*               |        DEM_IRT_NG  : different.                          */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMng_CmpWithObdRecordNumberIndex
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,                                /* [PRMCHK:CALLER] */
    P2CONST( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) CheckFaultRecordPtr      /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) indexOfRecNum;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) obdFFRClassNumPerDTCMaxNum;
    P2VAR( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) faultRecordPtr;

    retVal = DEM_IRT_OK;    /* same. */
    faultRecordPtr = &Dem_FaultRecordList[FaultIndex];              /* [GUDCHK:CALLER]FaultIndex *//* [GUD:CFG:IF_GUARDED: FaultIndex ]faultRecordPtr */
    obdFFRClassNumPerDTCMaxNum = Dem_CfgInfoPm_GetOBDFFRClassPerDTCMaxNum();

    /* check OBD freezeframe list. */
    for( indexOfRecNum = (Dem_u08_FFListIndexType)0U; indexOfRecNum < obdFFRClassNumPerDTCMaxNum; indexOfRecNum++ )             /* [GUD:for]indexOfRecNum */
    {
        if( faultRecordPtr->ObdRecordNumberIndex[indexOfRecNum] != CheckFaultRecordPtr->ObdRecordNumberIndex[indexOfRecNum] )   /* [GUDCHK:CALLER]FaultIndex *//* [GUDCHK:CALLER]CheckFaultRecordPtr *//* [GUD]indexOfRecNum *//* [ARYCHK] DEM_OBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / indexOfRecNum *//* [ARYCHK] DEM_OBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / indexOfRecNum */
        {
            break;
        }
    }

    if( indexOfRecNum < obdFFRClassNumPerDTCMaxNum )
    {
        /* different. */
        retVal = DEM_IRT_NG;
    }

    return retVal;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */

/****************************************************************************/
/* Function Name | Dem_DataMng_CmpWithNonObdRecordNumberIndex               */
/* Description   | Compere an array of RecordNumberIndex for non-OBD.       */
/* Preconditions |                                                          */
/* Parameters    | [in] FaultIndex :                                        */
/*               | [in] CheckFaultRecordPtr :                               */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK  : same.                               */
/*               |        DEM_IRT_NG  : different.                          */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMng_CmpWithNonObdRecordNumberIndex
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,                            /* [PRMCHK:CALLER] */
    P2CONST( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) CheckFaultRecordPtr  /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) indexOfRecNum;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonOBDFFRClassNumPerDTCMaxNum;
    P2VAR( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) faultRecordPtr;

    retVal = DEM_IRT_OK;    /* same. */
    faultRecordPtr = &Dem_FaultRecordList[FaultIndex];                  /* [GUDCHK:CALLER]FaultIndex *//* [GUD:CFG:IF_GUARDED: FaultIndex ]faultRecordPtr */
    nonOBDFFRClassNumPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;

    /* check freezeframe list. */
    for( indexOfRecNum = (Dem_u08_FFListIndexType)0U; indexOfRecNum < nonOBDFFRClassNumPerDTCMaxNum; indexOfRecNum++ )      /* [GUD:for]indexOfRecNum */
    {
        if( faultRecordPtr->RecordNumberIndex[indexOfRecNum] != CheckFaultRecordPtr->RecordNumberIndex[indexOfRecNum] )     /* [GUDCHK:CALLER]FaultIndex *//* [GUDCHK:CALLER]CheckFaultRecordPtr *//* [GUD]indexOfRecNum *//* [ARYCHK] DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / indexOfRecNum *//* [ARYCHK] DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / indexOfRecNum */
        {
            break;
        }
    }

    if( indexOfRecNum < nonOBDFFRClassNumPerDTCMaxNum )
    {
        /* different. */
        retVal = DEM_IRT_NG;
    }

    return retVal;
}

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
#if ( DEM_FAULT_RECORD_PADDING_EXIST == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataMng_GetFR_PaddingRecord                          */
/* Description   | Get FaultRecord padding data.                            */
/* Preconditions |                                                          */
/* Parameters    | [in] FaultIndex :                                        */
/*               |        The fault index corresponding to the specific fa- */
/*               |        ult record.                                       */
/*               | [out] FaultRecordPtr :                                   */
/*               |        The pointer of the fault record corresponding to  */
/*               |        the specified fault index.                        */
/*               |        (for Dem_DataCtl subunit)                         */
/* Return Value  | void                                                     */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMng_GetFR_PaddingRecord
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,                /* [PRMCHK:CALLER] */
    P2VAR( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr
)
{
    VAR( Dem_u16_PaddingIndexType, AUTOMATIC ) padidx;
    VAR( Dem_u16_PaddingIndexType, AUTOMATIC ) faultRecordBlockPaddingSize;

    faultRecordBlockPaddingSize = Dem_FaultRecordBlockPaddingSize;

    for( padidx = (Dem_u16_PaddingIndexType)0U; padidx < faultRecordBlockPaddingSize; padidx++ )        /* [GUD:for]padidx */
    {
        FaultRecordPtr->Reserve[padidx] = Dem_FaultRecordList[FaultIndex].Reserve[padidx];              /* [GUD]padidx *//* [GUDCHK:CALLER]FaultIndex *//* [ARYCHK] DEM_FAIL_RECORD_PADDINGSIZE_TO_BLOCKSIZE / 1 / padidx */
    }
    return ;
}

/****************************************************************************/
/* Function Name | Dem_FaultMng_InitFRData_Padding                          */
/* Description   | Initializes FaultRecord padding area.                    */
/* Preconditions |                                                          */
/* Parameters    | [out] FaultRecordPtr :                                   */
/*               |        The specified fault record to initialize.         */
/* Return Value  | void                                                     */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_FaultMng_InitFRData_Padding
(
    P2VAR( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) FaultRecordPtr
)
{
    VAR( Dem_u16_PaddingIndexType, AUTOMATIC ) padidx;
    VAR( Dem_u16_PaddingIndexType, AUTOMATIC ) faultRecordBlockPaddingSize;

    /*    initialize padding area    */
    faultRecordBlockPaddingSize = Dem_FaultRecordBlockPaddingSize;
    for( padidx = (Dem_u16_PaddingIndexType)0U; padidx < faultRecordBlockPaddingSize; padidx++ )        /* [GUD:for]padidx */
    {
        FaultRecordPtr->Reserve[padidx] = DEM_DATA_RESERVE_INITIAL_VALUE;                               /* [GUD]padidx *//* [ARYCHK] DEM_FAIL_RECORD_PADDINGSIZE_TO_BLOCKSIZE / 1 / padidx */
    }

    return;
}
#endif /*   ( DEM_FAULT_RECORD_PADDING_EXIST == STD_ON )  */
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */


/****************************************************************************/
/* Function Name | Dem_FaultMng_Init                                        */
/* Description   | Init process of Fault.                                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_FaultMng_Init
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex     /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;

    failRecordNum = Dem_FailRecordNum;

    for( faultIndex = (Dem_u08_FaultIndexType)0U; faultIndex < failRecordNum; faultIndex++ )        /* [GUD:for]faultIndex */
    {
        Dem_FaultNvMStatus[ faultIndex ] = DEM_RECMNGCMN_NVM_STS_NOT_VERIFIED;                      /* [GUD]faultIndex */
    }

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    /* [FuncSw] */
    Dem_FaultMng_InitMirrorMemory();
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

    return;
}

/****************************************************************************/
/* Function Name | Dem_FaultMng_InitSavedZone                               */
/* Description   | Initialize savedzone process of Fault.                   */
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
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_FaultMng_InitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType      /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;

    failRecordNum = Dem_FailRecordNum;

    for( faultIndex = (Dem_u08_FaultIndexType)0U; faultIndex < failRecordNum; faultIndex++ )            /* [GUD:for]faultIndex */
    {
    /* Sets factory default value to the specified fault record. */
        Dem_FaultRecordList[faultIndex].EventStrgIndex           = DEM_EVENTSTRGINDEX_INVALID;          /* [GUD]faultIndex */
        Dem_FaultRecordList[faultIndex].OccurrenceOrder          = DEM_FAIL_OCCURRENCE_NUM_INVALID;     /* [GUD]faultIndex */
        Dem_FaultRecordList[faultIndex].ConfirmedOccurrenceOrder = DEM_FAIL_OCCURRENCE_NUM_INVALID;     /* [GUD]faultIndex */
        Dem_FaultRecordList[faultIndex].MILOccurrenceOrder       = DEM_FAIL_OCCURRENCE_NUM_INVALID;     /* [GUD]faultIndex */
        Dem_FaultRecordList[faultIndex].AgingCounter             = DEM_AGING_COUNT_MAX_VALUE;           /* [GUD]faultIndex */
#if ( DEM_WWH_OBD_SUPPORT == STD_ON ) /* [FuncSw] */
        Dem_FaultRecordList[faultIndex].TimeAgingCounter         = DEM_TIME_AGING_COUNT_MAX_VALUE;      /* [GUD]faultIndex */
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */
        Dem_FaultRecordList[faultIndex].HealingCounter           = DEM_HEALING_COUNT_MAX_VALUE;         /* [GUD]faultIndex */
        Dem_FaultRecordList[faultIndex].ConsistencyCounterForFault = DEM_CONSISTENCY_INITIAL;           /* [GUD]faultIndex */

        /* Initialize FFList. */
        Dem_DataMng_InitRecordNumberIndex( faultIndex );                                                /* [GUD]faultIndex */

#if ( DEM_OBDFFD_SUPPORT == STD_ON )   /*  [FuncSw]    */
        /* Initialize OBD FFList. */
        Dem_DataMng_InitObdRecordNumberIndex( faultIndex );                                             /* [GUD]faultIndex */
#endif  /*   ( DEM_OBDFFD_SUPPORT == STD_ON )          */

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )   /*  [FuncSw]    */
        /* Initialize TSFFList. */
        Dem_DataMng_InitTSFFListRecord( faultIndex );                                                   /* [GUD]faultIndex */
#endif  /*   ( DEM_TSFF_PM_SUPPORT == STD_ON )         */

    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_FaultMng_DataVerify                                  */
/* Description   | Verifies Fault data.                                     */
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
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_FaultMng_DataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex     /* MISRA DEVIATION */
)
{
    /* No Process */
    return DEM_IRT_OK;
}

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_FaultMng_SetRecordMirror                             */
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
FUNC( void, DEM_CODE ) Dem_FaultMng_SetRecordMirror
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
)
{
    (void)Dem_DataMngM_GetFaultRecord( (Dem_u08_FaultIndexType)BlockMirrorPtr->RecordIndex, &Dem_TmpFaultMirror );  /* no return check required */

    BlockMirrorPtr->MirrorPtr = &Dem_TmpFaultMirror;

    return;
}
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

/****************************************************************************/
/* Function Name | Dem_FaultMng_ClearAllNotVerifiedRecord                   */
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
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_FaultMng_ClearAllNotVerifiedRecord
(
    P2VAR( Dem_u16_RecordIndexType, AUTOMATIC, AUTOMATIC ) ClearRecordIndexPtr,
    P2VAR( Dem_u32_TotalRecordNumType, AUTOMATIC, AUTOMATIC ) RestOfProcessableNumPtr
)
{
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u32_TotalRecordNumType, AUTOMATIC ) loopCount;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    failRecordNum = Dem_FailRecordNum;
    loopCount = (Dem_u32_TotalRecordNumType)0U;
    retVal = DEM_IRT_OK;

    for( faultIndex = (Dem_u08_FaultIndexType)( *ClearRecordIndexPtr ); faultIndex < failRecordNum; faultIndex++ )  /* [GUD:for]faultIndex */
    {
        if( loopCount < *RestOfProcessableNumPtr )
        {
            if( Dem_FaultNvMStatus[ faultIndex ] == DEM_RECMNGCMN_NVM_STS_NOT_VERIFIED )                            /* [GUD]faultIndex */
            {
                Dem_DataMng_InitFaultRecord_Ctl( faultIndex );
                Dem_FaultNvMStatus[ faultIndex ] = DEM_RECMNGCMN_NVM_STS_NON_TARGET;                                /* [GUD]faultIndex */
            }
            loopCount = loopCount + (Dem_u32_TotalRecordNumType)1U;
        }
        else
        {
            *ClearRecordIndexPtr = (Dem_u16_RecordIndexType)faultIndex;
            retVal = DEM_IRT_PENDING;
            break;
        }
    }

    if( faultIndex >= failRecordNum )
    {
        *RestOfProcessableNumPtr = (*RestOfProcessableNumPtr) - loopCount;  /* no wrap around */
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_FaultMng_GetNumOfStoredFault                         */
/* Description   | Get the number of stored Fault.                          */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_OrderIndexType                                   */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_OrderIndexType, DEM_CODE ) Dem_FaultMng_GetNumOfStoredFault
( void )
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) retFaultNum;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;

    retFaultNum = 0U;
    failRecordNum = Dem_FailRecordNum;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    for( faultIndex = (Dem_u08_FaultIndexType)0U; faultIndex < failRecordNum; faultIndex++ )            /* [GUD:for]faultIndex */
    {
        if( Dem_FaultRecordList[faultIndex].EventStrgIndex < eventStorageNum )                          /* [GUD]faultIndex */
        {
            retFaultNum = retFaultNum + (Dem_u08_OrderIndexType)1U;
        }
    }

    return retFaultNum;
}

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_FaultMng_InitMirrorMemory                            */
/* Description   | Initialize the Mirror Memory.                            */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_FaultMng_InitMirrorMemory
( void )
{

    Dem_DataMngC_InitFaultCtlRecordData( &Dem_TmpFaultMirror );
    Dem_TmpFaultMirror.ConsistencyCounterForFault = DEM_CONSISTENCY_INITIAL;

#if ( DEM_FAULT_RECORD_PADDING_EXIST == STD_ON )    /*  [FuncSw]    */
    Dem_FaultMng_InitFRData_Padding( &Dem_TmpFaultMirror );
#endif  /* ( DEM_FAULT_RECORD_PADDING_EXIST == STD_ON )             */

    return;
}
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_FaultMng_GetEventIdFromRecordData                    */
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
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_FaultMng_GetEventIdFromRecordData
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;

    eventStrgIndex      =   DEM_EVENTSTRGINDEX_INVALID;
    faultIndex          =   ( Dem_u08_FaultIndexType )RecordIndex;
    retVal  =   Dem_DataMng_GetEventStrgIndexFromFaultRecord( faultIndex, &eventStrgIndex );

    if ( retVal == DEM_IRT_OK )
    {
        retVal  =   Dem_DataMng_GetEventIdFromEventStrgIndex( eventStrgIndex, EventIdPtr );
    }

    return retVal;
}
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
