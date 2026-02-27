/* Dem_DataCtl_InfoFFD_c(v5-9-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_InfoFFD/CODE                                  */
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
#include "../../../inc/Dem_CmnLib_DataCtl.h"
#include "../../../inc/Dem_CmnLib_DataCtl_FFDOutputJudge.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Pm_DataCtl_OBD.h"

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
/* Function Name | Dem_Data_CheckSupportedFreezeFrameRecordNumber           */
/* Description   | check support record number.                             */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] RecordNumber :                                      */
/*               | [in] FreezeFrameDataType :                               */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Retrieving the freeze frame data wa- */
/*               |        s successful.                                     */
/*               |        DEM_IRT_NG : Retrieving the freeze frame data wa- */
/*               |        s failed.                                         */
/*               |        DEM_IRT_WRONG_RECORD_NUMBER : The wrong record n- */
/*               |        umber was passed.                                 */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_Data_GetEventFreezeFrameData.  */
/*   v5-8-0      | no branch changed.                                       */
/*   v5-9-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_CheckSupportedFreezeFrameRecordNumber
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    VAR( Dem_u08_FreezeFrameDataType, AUTOMATIC ) FreezeFrameDataType      /* MISRA DEVIATION */
)
{
    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA ) freezeFrameRecNumClassPtr;

    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) freezeFrameClassRef;
    VAR( Dem_u16_FFRecNumClassIndexType, AUTOMATIC ) freezeframeRecNumClassRef;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;

    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFFRClass;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) freezeFrameRecordClassIndex;
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) freezeFrameRecordTrigger;

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )  /*  [FuncSw]    */
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsFFRecClassRefIndex;
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) startingRecordNumber;
    VAR( boolean, AUTOMATIC ) judgeBeforeTSFFDFlag;
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON )           */

    eventStorageNum     =   Dem_PrimaryMemEventStorageNum;
    freezeFrameClassRef         =   DEM_FFCLASSINDEX_INVALID;
    freezeframeRecNumClassRef   =   DEM_FFRECNUMCLASSINDEX_INVALID;
    freezeFrameRecordTrigger = DEM_TRIGGER_ON_NONE;

    if( EventStrgIndex < eventStorageNum )                                                                  /* [GUD:if]EventStrgIndex */
    {
#if ( DEM_OBDFFD_SUPPORT == STD_ON )   /*  [FuncSw]    */
        if ( FreezeFrameDataType == DEM_FFD_TYPE_OBDFFD )
        {
            /*  FreezeFrameDataType == DEM_FFD_TYPE_OBDFFD          */
            /*  Checks the FreezeFrameClass table list Index of the held DTCAttribute table. */
            Dem_CfgInfoPm_GetOBDFreezeFrameAndRecNumClass( EventStrgIndex, &freezeFrameClassRef, &freezeframeRecNumClassRef );  /* [GUD:OUT:Not DEM_FFCLASSINDEX_INVALID] obdFreezeFrameClassRef *//* [GUD:OUT:Not DEM_FFRECNUMCLASSINDEX_INVALID] obdFreezeframeRecNumClassRef */
        }
        else
#endif  /*   ( DEM_OBDFFD_SUPPORT == STD_ON )          */
        {
            /* Checks the reference of freeze frame class. */
            Dem_CfgInfoPm_GetFreezeFrameAndRecNumClass( EventStrgIndex, &freezeFrameClassRef, &freezeframeRecNumClassRef );     /* [GUD:OUT:Not DEM_FFCLASSINDEX_INVALID] freezeFrameClassRef *//* [GUD:OUT:Not DEM_FFRECNUMCLASSINDEX_INVALID] freezeframeRecNumClassRef */
        }

        if( freezeFrameClassRef == DEM_FFCLASSINDEX_INVALID )                                                                   /* [GUD:if] freezeFrameClassRef */
        {
            /* Sets the return value to DEM_IRT_WRONG_RECORDNUMBER(Incorrect record number). */
            retVal = DEM_IRT_WRONG_RECORDNUMBER;
        }
        /* Checks the FreezeFrameRecNumClass table list Index of the held DTCAttribute table. */
        else if( freezeframeRecNumClassRef == DEM_FFRECNUMCLASSINDEX_INVALID )                                                  /* [GUD:if] freezeframeRecNumClassRef */
        {
            /* Sets the return value to DEM_IRT_WRONG_RECORDNUMBER(Incorrect record number). */
            retVal = DEM_IRT_WRONG_RECORDNUMBER;
        }
        else
        {
            /* Holds the FreezeFrameClass table pointed to by the FreezeFrameClass table list Index of the held DTCAttribute table. */
            freezeFrameRecNumClassPtr = &Dem_FreezeFrameRecNumClassTable[freezeframeRecNumClassRef];                            /* [GUD]freezeframeRecNumClassRef */

            freezeFrameRecordClassIndex = 0U;

            /* Specify the FreezeFrameRecNumClass table and the specified record number,                 */
            /* the FreezeFrameRecordClass table storage area, and the FreezeFrameRecordClass table index */
            /* Call FreezeFrameRecordClass table acquisition processing.                                 */

            resultOfGetFFRClass = Dem_Data_GetFreezeFrameRecordClassByRecordNumber( DEM_CALLER_DCM, freezeFrameRecNumClassPtr, RecordNumber, &freezeFrameRecordClassIndex, &freezeFrameRecordTrigger );     /* [GUD:RET:DEM_IRT_OK] freezeFrameRecordClassIndex */

            /* Checks FreezeFrameRecordClass table acquisition result. */
            if( resultOfGetFFRClass == DEM_IRT_OK )
            {
                retVal  =   DEM_IRT_OK;
            }
            else
            {
                retVal = DEM_IRT_WRONG_RECORDNUMBER;

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )  /*  [FuncSw]    */
                if ( FreezeFrameDataType != DEM_FFD_TYPE_OBDFFD )
                {
                    startingRecordNumber = (Dem_u08_FFRecordNumberType)0U;
                    tsFFRecClassRefIndex = Dem_TSFFRecordClassNumPerDTCMaxNum;
                    freezeFrameClassRef = DEM_FFCLASSINDEX_INVALID;
                    judgeBeforeTSFFDFlag = (boolean)FALSE;

                    /* As not have been retrieved the freeze frame record class, tries to retrieve time-series freeze frame data. */
                    retVal = Dem_Data_GetTSFFDInfoByEventAndRecNum( EventStrgIndex, RecordNumber, &startingRecordNumber, &tsFFRecClassRefIndex, &freezeFrameClassRef, &freezeFrameRecordTrigger, &judgeBeforeTSFFDFlag ); /* [GUD]EventStrgIndex *//* [GUD:RET:DEM_IRT_OK] freezeFrameClassRef */
                }
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON )           */
            }
        }
    }
    else
    {
        retVal = DEM_IRT_NG;
    }

    /* Returns with the result. */
    return retVal;
}

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_GetTSFFDInfoByEventAndRecNum                    */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |                                                          */
/*               | [in] RecordNumber :                                      */
/*               |                                                          */
/*               | [out] StartingRecordNumberPtr :                          */
/*               |                                                          */
/*               | [out] TimeSeriesFreezeFrameRecordClassRefIndexPtr :      */
/*               |                                                          */
/*               | [out] FreezeFrameClassRefPtr :                           */
/*               |                                                          */
/*               | [out] FreezeFrameRecordTriggerPtr :                      */
/*               |                                                          */
/*               | [out] JudgeBeforeTSFFDFlagPtr :                          */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_WRONG_RECORDNUMBER :                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:DEM_IRT_OK] FreezeFrameClassRefPtr              */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetTSFFDInfoByEventAndRecNum
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC ) StartingRecordNumberPtr,
    P2VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC, AUTOMATIC ) TimeSeriesFreezeFrameRecordClassRefIndexPtr,
    P2VAR( Dem_u16_FFClassIndexType, AUTOMATIC, AUTOMATIC ) FreezeFrameClassRefPtr,
    P2VAR( Dem_u08_StorageTriggerType, AUTOMATIC, AUTOMATIC ) FreezeFrameRecordTriggerPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) JudgeBeforeTSFFDFlagPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsFFRecClassRefIndex;
    VAR( Dem_u08_TSFFClassIndexType, AUTOMATIC ) tsFFClassRef;
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) startingRecordNumber;
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) endingRecordNumber;
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) judgeBeforeRecordNumber;
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) tsFFRecClassRef;
    VAR( Dem_u16_SmpTSFFCPerTSFFIndexType, AUTOMATIC ) samplingFFClassRef;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsffRecordClassNumPerDTCMaxNum;
    P2CONST( AB_83_ConstV Dem_DTCAttributeType, AUTOMATIC, DEM_CONFIG_DATA ) dtcAttributePtr;

    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) numberOfBeforeTriggeredRecord;
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) numberOfAfterTriggeredRecord;

    retVal = DEM_IRT_WRONG_RECORDNUMBER;
    tsffRecordClassNumPerDTCMaxNum = Dem_TSFFRecordClassNumPerDTCMaxNum;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    if( EventStrgIndex < eventStorageNum )                                                                  /* [GUD:if]EventStrgIndex */
    {
        dtcAttributePtr =   Dem_CfgInfoPm_GetDTCAttrTablePtr_TSFF( EventStrgIndex );    /* [GUD:RET:Not NULL_PTR]dtcAttributePtr */

        if ( dtcAttributePtr != NULL_PTR )                                              /* [GUD:if]dtcAttributePtr */
        {
            for( tsFFRecClassRefIndex = (Dem_u08_TSFFListPerDTCIndexType)0U; tsFFRecClassRefIndex < tsffRecordClassNumPerDTCMaxNum; tsFFRecClassRefIndex++ )    /* [GUD:for]tsFFRecClassRefIndex */
            {
                tsFFRecClassRef = dtcAttributePtr->DemTimeSeriesFreezeFrameRecordClassRef[tsFFRecClassRefIndex];                                                /* [GUD]dtcAttributePtr *//* [GUD]tsFFRecClassRefIndex *//* [ARYCHK] DEM_TSFF_RECORD_CLASS_NUM_PER_DTC_MAX_NUM / 1 / tsFFRecClassRefIndex */

                if( tsFFRecClassRef != DEM_TSFF_RECORD_CLASS_REF_INVALID )                                                                                      /* [GUD:if]tsFFRecClassRef */
                {
                    tsFFClassRef = Dem_TSFFRecordClassTable[tsFFRecClassRef].DemTimeSeriesFreezeFrameClassRef;                                                  /* [GUD]tsFFRecClassRef *//* [GUD:CFG:IF_GUARDED: tsFFRecClassRef ]tsFFClassRef */

                    startingRecordNumber = Dem_TSFFRecordClassTable[tsFFRecClassRef].DemStartingRecordNumber;                                                   /* [GUD]tsFFRecClassRef */

                    numberOfBeforeTriggeredRecord   =   (Dem_u08_FFRecordNumberType)Dem_TSFFClassTable[tsFFClassRef].DemNumberOfBeforeTriggeredRecord;          /* [GUD]tsFFClassRef */
                    numberOfAfterTriggeredRecord    =   (Dem_u08_FFRecordNumberType)Dem_TSFFClassTable[tsFFClassRef].DemNumberOfAfterTriggeredRecord;           /* [GUD]tsFFClassRef */
                    endingRecordNumber = ( ( startingRecordNumber + numberOfBeforeTriggeredRecord ) + numberOfAfterTriggeredRecord ) - (Dem_u08_FFRecordNumberType)1U;

                    if( RecordNumber >= startingRecordNumber )
                    {
                        if( RecordNumber <= endingRecordNumber )
                        {
                            samplingFFClassRef = Dem_TSFFRecordClassTable[tsFFRecClassRef].DemSamplingFreezeFrameClassRef;                                      /* [GUD]tsFFRecClassRef *//* [GUD:CFG:IF_GUARDED: tsFFRecClassRef ]samplingFFClassRef */

                            *StartingRecordNumberPtr = startingRecordNumber;

                            *TimeSeriesFreezeFrameRecordClassRefIndexPtr = tsFFRecClassRefIndex;

                            *FreezeFrameClassRefPtr = Dem_TSFFClassTable[tsFFClassRef].Dem_SamplingFreezeFrameClass[samplingFFClassRef].DemFreezeFrameClassRef; /* [GUD]tsFFClassRef *//* [GUD]samplingFFClassRef *//* [GUD:CFG:IF_GUARDED: tsFFClassRef,samplingFFClassRef ] *FreezeFrameClassRefPtr */

                            *FreezeFrameRecordTriggerPtr = Dem_TSFFRecordClassTable[tsFFRecClassRef].DemTimeSeriesFreezeFrameTrigger;                           /* [GUD]tsFFRecClassRef */

                            judgeBeforeRecordNumber = startingRecordNumber + Dem_TSFFClassTable[tsFFClassRef].DemNumberOfBeforeTriggeredRecord;                 /* [GUD]tsFFClassRef */
                            if( RecordNumber < judgeBeforeRecordNumber )
                            {
                                *JudgeBeforeTSFFDFlagPtr = (boolean)TRUE;
                            }
                            else
                            {
                                *JudgeBeforeTSFFDFlagPtr = (boolean)FALSE;
                            }

                            retVal = DEM_IRT_OK;

                            break;
                        }
                    }
                }
            }
        }
    }

    return retVal;
}
#endif  /* (DEM_TSFF_PM_SUPPORT == STD_ON) */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
