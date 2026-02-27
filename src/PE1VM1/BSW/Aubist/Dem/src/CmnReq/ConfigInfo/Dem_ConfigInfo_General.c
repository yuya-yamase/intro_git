/* Dem_ConfigInfo_General_c(v5-10-0)                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/ConfigInfo_General/CODE                               */
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
#include "../../../usr/Dem_PendingOBDFFD_Callout.h"

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

static FUNC( boolean, DEM_CODE ) Dem_CfgInfo_CheckTriggerCommon
(
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) TargetTrigger,
    VAR( Dem_u08_FFValidTriggerType, AUTOMATIC ) TriggerFromCaller
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
/* Function Name | Dem_CfgInfo_GetTranslationType                           */
/* Description   | Gets the supported DTC formats of the ECU.               */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_DTCTranslationFormatType                             */
/*               |        DEM_DTC_TRANSLATION_ISO14229_1 : ISO14229-1 DTC - */
/*               |        format                                            */
/* Notes         | The following return values are currently unsupported.   */
/*               |        DEM_DTC_TRANSLATION_ISO15031_6 : ISO15031-6 DTC - */
/*               |        format/SAE J2012-DA_DTCFormat_00 DTCFormat        */
/*               |        DEM_DTC_TRANSLATION_SAEJ1939_73 : SAEJ1939-73 DT- */
/*               |        C format                                          */
/*               |        DEM_DTC_TRANSLATION_ISO11992_4 : ISO11992-4 DTC - */
/*               |        format                                            */
/*               |        DEM_DTC_TRANSLATION_J2012DA_FORMAT_04 : SAE_J201- */
/*               |        2-DA_DTCFormat_04 DTC format                      */
/****************************************************************************/
FUNC( Dem_DTCTranslationFormatType, DEM_CODE ) Dem_CfgInfo_GetTranslationType
( void )
{
    VAR( Dem_DTCTranslationFormatType, AUTOMATIC ) retVal;

    /* Sets the return value to the value of DemTypeOfDTCSupported. */
    retVal = Dem_TypeOfDTCSupported;

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_CfgInfo_JudgeAgingRequire                            */
/* Description   | Judge Aging Require or not.                              */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCStatusStPtr : statusOfDTC.                       */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Aging is Required.                   */
/*               |        DEM_IRT_NG : Aging is not Required.               */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfo_JudgeAgingRequire
(
    CONSTP2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) DTCStatusStPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) agingRequiresNotFailedCycle;
    VAR( boolean, AUTOMATIC ) agingRequiresTestedCycle;

    agingRequiresNotFailedCycle =   Dem_AgingRequiresNotFailedCycle;

    /*  initialize : Aging is required.     */
    retVal  =   DEM_IRT_OK;

    /*  check config : DemAgingRequiresNotFailedCycle   */
    if ( agingRequiresNotFailedCycle == (boolean)TRUE )
    {
        /*  check PendingDTC bit status.                */
        /*  if PendingDTC is ON, Aging is not required. */
        if (( DTCStatusStPtr->DTCStatus & DEM_UDS_STATUS_PDTC ) == DEM_UDS_STATUS_PDTC )
        {
                /*  Aging is not required.      */
                retVal = DEM_IRT_NG;
        }
    }

    /*  check config : DemAgingRequiresTestedCycle   */
    agingRequiresTestedCycle =   Dem_AgingRequiresTestedCycle;
    if ( agingRequiresTestedCycle == (boolean)TRUE )
    {
        /*  check TestNotCompletedThisOperationCycle bit status.                */
        /*  if TestNotCompletedThisOperationCycle is ON, Aging is not required. */
        if (( DTCStatusStPtr->ExtendDTCStatus & DEM_DTCSTATUSEX_STATUS_TNCTOC_IN_AGINGCYCLE ) == DEM_DTCSTATUSEX_STATUS_TNCTOC_IN_AGINGCYCLE )
        {
            /*  Aging is not required.      */
            retVal = DEM_IRT_NG;
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfo_CheckTrigger                                 */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in/out] TriggerKind : The target trigger classification */
/*               |        that this function checks.                        */
/*               | [in] TriggerFromCaller : The trigger from caller.        */
/*               |                                                          */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : The trigger is included.                  */
/*               |        FALSE : The trigger is not included.              */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-10-0     | new created.                                             */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CfgInfo_CheckTrigger
(
    P2VAR( Dem_u08_StorageTriggerType, AUTOMATIC, AUTOMATIC ) TargetTriggerPtr,
    VAR( Dem_u08_FFValidTriggerType, AUTOMATIC ) TriggerFromCaller
)
{
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) freezeFrameRecordTrigger;

#if ( DEM_FFD_RECORDUPDATE_AT_TESTFAILED_SUPPORT == STD_ON )    /* [ FuncSw ] */
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) freezeFrameRecordUpdateTrigger;
#endif  /* ( DEM_FFD_RECORDUPDATE_AT_TESTFAILED_SUPPORT == STD_ON )             */

    /*--------------------------------------*/
    /*  mask update trigger.                */
    /*--------------------------------------*/
    freezeFrameRecordTrigger        =   (*TargetTriggerPtr) & DEM_TRIGGER_ON_TRIGGERTYPE_MASK;

    /*----------------------------------------------*/
    /*  check trigger type and occurred trigger.    */
    /*----------------------------------------------*/
    retVal  =   Dem_CfgInfo_CheckTriggerCommon( freezeFrameRecordTrigger, TriggerFromCaller );

#if ( DEM_FFD_RECORDUPDATE_AT_TESTFAILED_SUPPORT == STD_ON )    /* [ FuncSw ] */
    if ( retVal == (boolean)FALSE )
    {
        /*--------------------------------------*/
        /*  check update trigger.               */
        /*--------------------------------------*/
        freezeFrameRecordUpdateTrigger  =   (*TargetTriggerPtr) & DEM_TRIGGER_ON_UPDATETYPE_MASK;

        if( ( freezeFrameRecordUpdateTrigger & DEM_TRIGGER_ON_UPD_TEST_FAILED ) == DEM_TRIGGER_ON_UPD_TEST_FAILED )
        {
            /*  DEM_TRIGGER_ON_UPD_TEST_FAILED is only update trigger.      */
            if( freezeFrameRecordTrigger == DEM_TRIGGER_ON_CONFIRMED )
            {
                if( ( TriggerFromCaller & DEM_VALID_TRIGGER_TEST_FAILED_AT_CDTC ) == DEM_VALID_TRIGGER_TEST_FAILED_AT_CDTC )
                {
                    /* Sets the return value to TRUE. */
                    retVal = (boolean)TRUE;
                }
            }
            else
            {
                if( ( TriggerFromCaller & DEM_VALID_TRIGGER_TEST_FAILED ) == DEM_VALID_TRIGGER_TEST_FAILED )
                {
                    /* Sets the return value to TRUE. */
                    retVal = (boolean)TRUE;
                }
            }
        }
    }
#endif  /* ( DEM_FFD_RECORDUPDATE_AT_TESTFAILED_SUPPORT == STD_ON )             */

    /*--------------------------------------*/
    /*  set trigger type.                   */
    /*--------------------------------------*/
    *TargetTriggerPtr   =   freezeFrameRecordTrigger;

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfo_CheckTriggerCommon                           */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] TriggerKind : The target trigger classification     */
/*               |        that this function checks.                        */
/*               | [in] TriggerFromCaller : The trigger from caller.        */
/*               |                                                          */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : The trigger is included.                  */
/*               |        FALSE : The trigger is not included.              */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-10-0     | rename from Dem_CfgInfo_CheckTrigger(v5-9-0).            */
/*   v5-10-0     | no object changed.                                       */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_CfgInfo_CheckTriggerCommon
(
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) TargetTrigger,
    VAR( Dem_u08_FFValidTriggerType, AUTOMATIC ) TriggerFromCaller
)
{
    VAR( boolean, AUTOMATIC ) retVal;

    /* Initializeds return value to FALSE. */
    retVal = (boolean)FALSE;

    /* Checks the specified TargetTrigger. */
    if( TargetTrigger == DEM_TRIGGER_ON_CONFIRMED )
    {
        /* Checks the DEM_VALID_TRIGGER_CONFIRMED bit of the specified caller's trigger is on. */
        if( ( TriggerFromCaller & DEM_VALID_TRIGGER_CONFIRMED ) == DEM_VALID_TRIGGER_CONFIRMED )
        {
            /* Sets the return value to TRUE. */
            retVal = (boolean)TRUE;
        }
    }
    else if( TargetTrigger == DEM_TRIGGER_ON_FDC_THRESHOLD )
    {
        /* Checks the DEM_VALID_TRIGGER_FDC_THRESHOLD bit of the specified caller's trigger is on. */
        if( ( TriggerFromCaller & DEM_VALID_TRIGGER_FDC_THRESHOLD ) == DEM_VALID_TRIGGER_FDC_THRESHOLD )
        {
            /* Sets the return value to TRUE. */
            retVal = (boolean)TRUE;
        }
    }
    else if( TargetTrigger == DEM_TRIGGER_ON_PENDING )
    {
        /* Checks the DEM_VALID_TRIGGER_PENDING bit of the specified caller's trigger is on. */
        if( ( TriggerFromCaller & DEM_VALID_TRIGGER_PENDING ) == DEM_VALID_TRIGGER_PENDING )
        {
            /* Sets the return value to TRUE. */
            retVal = (boolean)TRUE;
        }
    }
    else if( TargetTrigger == DEM_TRIGGER_ON_TEST_FAILED_THIS_OPERATION_CYCLE )
    {
        /* Checks the DEM_VALID_TRIGGER_TFTOC bit of the specified caller's trigger is on. */
        if( ( TriggerFromCaller & DEM_VALID_TRIGGER_TFTOC ) == DEM_VALID_TRIGGER_TFTOC )
        {
            /* Sets the return value to TRUE. */
            retVal = (boolean)TRUE;
        }
    }
    else
    {
        /* No Process */
    }

    return retVal;
}

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CfgInfo_CheckObdTrigger                              */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in/out] TriggerKind : The target trigger classification */
/*               |        that this function checks.                        */
/*               | [in] TriggerFromCaller : The trigger from caller.        */
/*               | [out] UpdatePendingFFDPtr : The flag if update PendingF- */
/*               |        FD  or not.                                       */
/*               |                                                          */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : The trigger is included.                  */
/*               |        FALSE : The trigger is not included.              */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-10-0     | branch changed.                                          */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CfgInfo_CheckObdTrigger
(
    P2VAR( Dem_u08_StorageTriggerType, AUTOMATIC, AUTOMATIC ) TargetTriggerPtr,
    VAR( Dem_u08_FFValidTriggerType, AUTOMATIC ) TriggerFromCaller,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) UpdatePendingFFDPtr
)
{
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) judgeUpdateObdPendingFFD;

    /* Initializes the update PendingFFD flag to FALSE */
    (*UpdatePendingFFDPtr) = (boolean)FALSE;

    /*--------------------------------------------------*/
    /*  check trigger update.                           */
    /*--------------------------------------------------*/
    retVal = Dem_CfgInfo_CheckTrigger( TargetTriggerPtr, TriggerFromCaller );

    if ( retVal == (boolean)FALSE )
    {
        /*----------------------------------------------*/
        /*  no update condition.                        */
        /*----------------------------------------------*/
        if( *TargetTriggerPtr == DEM_TRIGGER_ON_PENDING )
        {
            /* Checks the DEM_VALID_TRIGGER_CONFIRMED bit of the specified caller's trigger is on. */
            if( ( TriggerFromCaller & DEM_VALID_TRIGGER_CONFIRMED ) == DEM_VALID_TRIGGER_CONFIRMED )
            {
                judgeUpdateObdPendingFFD = Dem_JudgePendingOBDFFDUpdateAtConfirmedTrigger();
                if( judgeUpdateObdPendingFFD == (boolean)TRUE )
                {
                    /* Sets the return value to TRUE. */
                    retVal = (boolean)TRUE;
                    /* Sets the update PendingFFD flag to TRUE */
                    (*UpdatePendingFFDPtr) = (boolean)TRUE;
                }
            }
        }
    }
    return retVal;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
