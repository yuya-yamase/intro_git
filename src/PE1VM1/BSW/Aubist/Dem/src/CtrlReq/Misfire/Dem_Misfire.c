/* Dem_Misfire_c(v5-9-0)                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Misfire/CODE                                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
#include "../../../inc/Dem_Pm_DataAvl.h"
#include "../../../inc/Dem_Pm_DTC.h"
#include "../../../inc/Dem_Pm_DTC_PFC.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Pm_DataCtl_OBD.h"
#include "../../../inc/Dem_Rc_DataMng.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_Rc_MisfireMng.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_DTC_DTCStatus.h"
#include "../../../usr/Dem_Misfire_NotifyCylinderStatus_Callout.h"
#include "Dem_Misfire_local.h"
#include "Dem_Misfire_EventEntry_local.h"

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

static FUNC( void, DEM_CODE ) Dem_Misfire_GetMisfireExcessConterThreshold
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u08_MisfExceedanceCounterType, AUTOMATIC, AUTOMATIC )  ExcessCntThresholdPtr
);

#if ( DEM_OBDONUDS_SUPPORT == STD_ON )
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Misfire_UpdatePairObdFFDInfo
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) MisfireObdFFDCylIndex,
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) FFDCyl
);
#endif /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON ) */
#endif /* ( DEM_OBDONUDS_SUPPORT == STD_ON ) */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>
static VAR( Dem_UdsStatusByteType, DEM_VAR_NO_INIT ) Dem_LatchCylDTCStatus[DEM_MISFIRE_CYLINDER_AND_RM_NUM];

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
static VAR( boolean, DEM_VAR_NO_INIT ) Dem_PendingStoreOfEmission;
#endif  /*   ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )     */

/*  reflesh RAM.        */
static VAR( volatile boolean, DEM_VAR_NO_INIT ) Dem_ExceedanceUsedOfEmission;

#if ( DEM_OBDONUDS_SUPPORT == STD_ON )
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
static VAR( boolean, DEM_VAR_NO_INIT ) Dem_Misf_ObdRecordNumberIndexSyncStatus;
#endif /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON ) */
#endif /* ( DEM_OBDONUDS_SUPPORT == STD_ON ) */

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* External Functions(PreInit section)                                      */
/****************************************************************************/
#define DEM_START_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_Misfire_PreInit                                      */
/* Description   | Pre-initialize data.                                     */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | PreInit  are an opportunity to start.                    */
/****************************************************************************/
FUNC( void, DEM_CODE_TRUST ) Dem_Misfire_PreInit        /*  PreInit section     */
( void )
{
    Dem_ExceedanceUsedOfEmission = Dem_MisfireExceedanceUsedEmission;
    return;
}

#define DEM_STOP_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_Misfire_Init                                         */
/* Description   | Initialize data.                                         */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_Init
( void )
{
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
    Dem_PendingStoreOfEmission = (boolean)FALSE;
#endif  /*   ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON ) */
    return;
}

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Misfire_Init_AfterRecordCheckComplete                */
/* Description   | Initialize data. after record checked.                   */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_Init_AfterRecordCheckComplete
( void )
{
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) extendStatusOfDTC2;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) misfireEmissionEventStrgIndex;

    /*  get emission misfire event status   */
    misfireEmissionEventStrgIndex = Dem_CfgInfoPm_GetEventStrgIndex_MisfireEmission();
    extendStatusOfDTC2 = DEM_DTCSTATUSEX2_BYTE_ALL_OFF;

    /*  get extend statusOfDTC2.            */
    (void)Dem_DataMngC_GetER_ExtendDTCStatus2( misfireEmissionEventStrgIndex, &extendStatusOfDTC2 );   /* no return check required */

    /*  check DEM_DTCSTATUSEX2_STATUS_MISF_PENDINGOFEMISSION bit.   */
    if (( extendStatusOfDTC2 & DEM_DTCSTATUSEX2_STATUS_MISF_PENDINGOFEMISSION ) == DEM_DTCSTATUSEX2_STATUS_MISF_PENDINGOFEMISSION )
    {
        Dem_PendingStoreOfEmission = (boolean)TRUE;
    }
    else
    {
        Dem_PendingStoreOfEmission = (boolean)FALSE;
    }

    return;
}
#endif  /*   ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON ) */

/****************************************************************************/
/* Function Name | Dem_Misfire_JudgeDTCClearTarget                          */
/* Description   | judge clearDTC target.                                   */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : ClearDTC target.                          */
/*               |        FALSE : not ClearDTC target.                      */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_Misfire_JudgeDTCClearTarget
( void )
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) misfireEmissionEventStrgIndex;
    VAR( boolean, AUTOMATIC ) retDTCClearTarget;

    /* DTC is misfire */
    misfireEmissionEventStrgIndex   = Dem_CfgInfoPm_GetEventStrgIndex_MisfireEmission();
    retDTCClearTarget = Dem_DTC_JudgeDTCClearTarget( misfireEmissionEventStrgIndex );

    return retDTCClearTarget;
}

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
#if ( DEM_WWH_OBD_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_Misfire_GetIndStatusByEventStrgIndex_CAT                 */
/* Description   |  Gets the misfire indicator status by Event              */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        Event index.                                      */
/*               | [out] IndicatorStatusPtr :                               */
/*               |        Pointer to data for set Indicator Status.         */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | rename from Dem_Misfire_GetIndStatusByEventStrgIndex(v5-3-0). */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE )  Dem_Misfire_GetIndStatusByEventStrgIndex_CAT
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_IndicatorStatusType, AUTOMATIC, AUTOMATIC ) IndicatorStatusPtr
)
{
    VAR( boolean, AUTOMATIC ) blinkingState;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC;
    VAR( boolean, AUTOMATIC ) retCheckWIRBit;

    *IndicatorStatusPtr = DEM_INDICATOR_OFF;

    statusOfDTC = DEM_DTCSTATUS_BYTE_ALL_OFF;
    (void)Dem_DataMngC_GetER_StatusOfDTC( EventStrgIndex, &statusOfDTC );       /* no return check required */
    if( (statusOfDTC & DEM_UDS_STATUS_WIR) == DEM_UDS_STATUS_WIR )  /*  statusOfDTC : bit7  */
    {
        *IndicatorStatusPtr = DEM_INDICATOR_CONTINUOUS;
    }

    /*  misfire CAT event.      */
    blinkingState = Dem_Misfire_GetMILBlinkingStatus_CAT( statusOfDTC );
    if( blinkingState == (boolean)TRUE )
    {
        if( *IndicatorStatusPtr == DEM_INDICATOR_CONTINUOUS )
        {
            *IndicatorStatusPtr = DEM_INDICATOR_BLINK_CONT;
        }
        else
        {
            retCheckWIRBit = Dem_Misfire_CheckWIRBitAtIndicatorBlinking_CAT( statusOfDTC );
            if ( retCheckWIRBit == (boolean)TRUE )
            {
                *IndicatorStatusPtr = DEM_INDICATOR_BLINK_CONT;
            }
            else
            {
                *IndicatorStatusPtr = DEM_INDICATOR_BLINKING;
            }
        }
    }

    return ;
}
#endif  /* ( DEM_WWH_OBD_SUPPORT == STD_OFF )   */

/****************************************************************************/
/* Function Name | Dem_Misfire_CheckWIRBitAtIndicatorBlinking_CAT           */
/* Description   | Check the WIR bit status is continuous                   */
/* Preconditions |                                                          */
/* Parameters    | [in] CatStatusOfDTC :                                    */
/*               |      StatusOfDTC of CAT                                  */
/* Return Value  | boolean                                                  */
/*               |        TRUE :  WIRBit is continuous.                     */
/*               |        FALSE : WIRBit is not continuous.                 */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | rename from Dem_Misfire_CheckWIRBitAtIndicatorBlinking(v5-3-0). */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_Misfire_CheckWIRBitAtIndicatorBlinking_CAT
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) CatStatusOfDTC
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) misfireEmissionEventStrgIndex;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) emissionStatusOfDTC;
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) setWIRBitAtIndicatorBlinkingCat;
    VAR( boolean, AUTOMATIC ) setWIRBitAtIndicatorBlinkingEmission;
    VAR( Dem_u08_MisfireKindBitType, AUTOMATIC ) availableMisfireKind;

    retVal = (boolean)FALSE;

    availableMisfireKind    =   Dem_DataAvl_GetMisfireCylDTCAvailable();

    setWIRBitAtIndicatorBlinkingCat     = Dem_SetWIRBitAtIndicatorBlinkingCat;
    setWIRBitAtIndicatorBlinkingEmission = Dem_SetWIRBitAtIndicatorBlinkingEmission;

    if (( availableMisfireKind & DEM_MISFIRE_KINDBIT_CAT ) == DEM_MISFIRE_KINDBIT_CAT )
    {
        if( setWIRBitAtIndicatorBlinkingCat == (boolean)TRUE )
        {
            /* If mil of CAT is blinking, bit2 is standing and it is not checked */
            if( (CatStatusOfDTC & DEM_UDS_STATUS_CDTC) == DEM_UDS_STATUS_CDTC ) /*  statusOfDTC : bit3  */
            {
                retVal = (boolean)TRUE;
            }
        }
    }

    if (( availableMisfireKind & DEM_MISFIRE_KINDBIT_EMISSION ) == DEM_MISFIRE_KINDBIT_EMISSION )
    {
        if( retVal == (boolean)FALSE )
        {
            if( setWIRBitAtIndicatorBlinkingEmission == (boolean)TRUE )
            {
                misfireEmissionEventStrgIndex = Dem_CfgInfoPm_GetEventStrgIndex_MisfireEmission();
                (void)Dem_DataMngC_GetER_StatusOfDTC( misfireEmissionEventStrgIndex, &emissionStatusOfDTC );       /* no return check required */

                /* If mil of CAT is blinking, bit2 is standing and it is not checked */
                if( (emissionStatusOfDTC & DEM_UDS_STATUS_CDTC) == DEM_UDS_STATUS_CDTC )    /*  statusOfDTC : bit3  */
                {
                    retVal = (boolean)TRUE;
                }
            }
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Misfire_MergeWIRBitAtIndicatorBlinking_CAT           */
/* Description   | Merge WIRStatus bit at Indicator Blinking                */
/* Preconditions |                                                          */
/* Parameters    | [in] OldDTCStatus :                                      */
/*               |      Old StatusOfDTC                                     */
/*               | [out] NewDTCStatusPtr :                                  */
/*               |      New StatusOfDTC                                     */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | rename from Dem_Misfire_MergeWIRBitAtIndicatorBlinking(v5-3-0). */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_MergeWIRBitAtIndicatorBlinking_CAT
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) OldDTCStatus,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) NewDTCStatusPtr
)
{
    VAR( boolean, AUTOMATIC ) retCheckWIRBit;
    VAR( boolean, AUTOMATIC ) blinkingState;

    *NewDTCStatusPtr = OldDTCStatus;

    if( (OldDTCStatus & DEM_UDS_STATUS_WIR) != DEM_UDS_STATUS_WIR )     /*  statusOfDTC : bit7  */
    {
        blinkingState = Dem_Misfire_GetMILBlinkingStatus_CAT( OldDTCStatus );
        if( blinkingState == (boolean)TRUE )
        {
            retCheckWIRBit = Dem_Misfire_CheckWIRBitAtIndicatorBlinking_CAT( OldDTCStatus );
            if( retCheckWIRBit == (boolean)TRUE )
            {
                (*NewDTCStatusPtr) = ( OldDTCStatus | (Dem_UdsStatusByteType)DEM_UDS_STATUS_WIR );    /*  statusOfDTC : bit7  */
            }
        }
    }

    return;
}
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )   */

/****************************************************************************/
/* Function Name | Dem_Misfire_CheckReachedExcessCntThresholdFromTmp        */
/* Description   | ExcessCounterThreshold exceeded judgment of the          */
/*               | temporary area.                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Misfire_CheckReachedExcessCntThresholdFromTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_MisfExceedanceCounterType, AUTOMATIC ) excessCntThreshold;
    VAR( Dem_u08_MisfExceedanceCounterType, AUTOMATIC ) excessCounter;

    retVal = DEM_IRT_NG;

    Dem_Misfire_GetExceedanceCounterToTmp( EventStrgIndex, &excessCounter );

    Dem_Misfire_GetMisfireExcessConterThreshold( EventStrgIndex, &excessCntThreshold );

    if ( excessCounter < excessCntThreshold )
    {
        excessCounter++;
        Dem_Misfire_SetExceedanceCounterToTmp( EventStrgIndex, excessCounter );
    }

    if( excessCounter >= excessCntThreshold )
    {
        retVal = DEM_IRT_OK;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Misfire_UpdateCylinderInfo                           */
/* Description   | Update the cylinder infomation.                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] EventQualification :                                */
/*               | [in] DTCStatus :                                         */
/*               | [in] MisfireCylinder :                                   */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_UpdateCylinderInfo
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_EventQualificationType, AUTOMATIC ) EventQualification,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus,
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) MisfireCylinder
)
{
    VAR( boolean, AUTOMATIC ) misfireEventKind;

    misfireEventKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );
    if( misfireEventKind == (boolean)TRUE )
    {
        if( EventQualification == DEM_EVENT_QUALIFICATION_PASSED )
        {
            Dem_Misfire_ClearFailedCylToTmp( EventStrgIndex );
        }
        else if( EventQualification == DEM_EVENT_QUALIFICATION_FAILED )
        {
            Dem_Misfire_UpdateFailedCylToTmp( EventStrgIndex, MisfireCylinder);

            /* Bit2:ON */
            if( ( DTCStatus & DEM_UDS_STATUS_PDTC ) == DEM_UDS_STATUS_PDTC )    /*  statusOfDTC : bit2  */
            {
                Dem_Misfire_UpdatePendingCylinderToTmp( EventStrgIndex, MisfireCylinder );
            }
            /* Bit3:ON */
            if( ( DTCStatus & DEM_UDS_STATUS_CDTC ) == DEM_UDS_STATUS_CDTC )    /*  statusOfDTC : bit3  */
            {
                Dem_Misfire_UpdateConfirmedCylinderToTmp( EventStrgIndex, MisfireCylinder);
            }
#if ( DEM_PFC_SUPPORT == STD_ON )   /*  [FuncSw]    */
            /* Bit7:ON */
            if( ( DTCStatus & DEM_UDS_STATUS_WIR ) == DEM_UDS_STATUS_WIR )      /*  statusOfDTC : bit7  */
            {
                /* AccumPermanentCyl */
                Dem_Misfire_UpdateAccumPermanentCylToTmp( MisfireCylinder );
            }
#endif  /*   ( DEM_PFC_SUPPORT == STD_ON )          */

        }
        else
        {
            /*  no process      */
        }
    }
    return;
}

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Misfire_GetPendingStoreOfEmission                    */
/* Description   | Get the PendingStoreOfEmission.                          */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | boolean                                                  */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_Misfire_GetPendingStoreOfEmission
( void )
{
    VAR( Dem_u08_MisfireKindBitType, AUTOMATIC ) availableMisfireKind;
    VAR( boolean, AUTOMATIC ) pendingStoreOfEmission;

    pendingStoreOfEmission  =   Dem_PendingStoreOfEmission;

    availableMisfireKind    =   Dem_DataAvl_GetMisfireCylDTCAvailable();
    if( ( availableMisfireKind & DEM_MISFIRE_KINDBIT_EMISSION ) == (Dem_u08_MisfireKindBitType)0U )
    {
        /*  misfire emission is unavailable.        */
        pendingStoreOfEmission  =   (boolean)FALSE;
    }

    return pendingStoreOfEmission;
}

/****************************************************************************/
/* Function Name | Dem_Misfire_SetPendingStoreOfEmission                    */
/* Description   | Set the PendingStoreOfEmission.                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] PendingStoreOfEmission :                            */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_SetPendingStoreOfEmission
(
    VAR( boolean, AUTOMATIC ) PendingStoreOfEmission
)
{
    Dem_PendingStoreOfEmission  =   PendingStoreOfEmission;

    return;
}
#endif  /*   ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )     */

/****************************************************************************/
/* Function Name | Dem_Misfire_LatchCylinderStatus                          */
/* Description   | Latch cylinder DTCStatus.                                */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_LatchCylinderStatus
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( boolean, AUTOMATIC ) misfireEventKind;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderNum;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderCnt;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) tmpDTCStatus;

    misfireCylinderNum = Dem_MisfireCylinderNum;

    misfireEventKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );
    if( misfireEventKind == (boolean)TRUE )
    {
        for( misfireCylinderCnt = (Dem_MisfireCylinderNumberType)0U; misfireCylinderCnt < misfireCylinderNum; misfireCylinderCnt++ )    /* [GUD:for]misfireCylinderCnt */
        {
            tmpDTCStatus = Dem_Misfire_GetCylinderDTCStatus( misfireCylinderCnt );

            /*------------------------------------------*/
            /*  convert to output statusOfDTC.          */
            /*------------------------------------------*/
            Dem_LatchCylDTCStatus[misfireCylinderCnt] = Dem_DTC_CnvDTCStatus_ForOutput( tmpDTCStatus );     /* [GUD]misfireCylinderCnt */
        }
    }
    return;
}

/****************************************************************************/
/* Function Name | Dem_Misfire_JudgeCylinderStatus                          */
/* Description   | Judge cylinder DTCStatus.                                */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_JudgeCylinderStatus
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( boolean, AUTOMATIC ) misfireEventKind;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderNum;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderCnt;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) newCylDTCStatus;

    misfireCylinderNum = Dem_MisfireCylinderNum;

    misfireEventKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );
    if( misfireEventKind == (boolean)TRUE )
    {
        for( misfireCylinderCnt = (Dem_MisfireCylinderNumberType)0U; misfireCylinderCnt < misfireCylinderNum; misfireCylinderCnt++ )    /* [GUD:for]misfireCylinderCnt */
        {
            newCylDTCStatus = Dem_Misfire_GetCylinderDTCStatus( misfireCylinderCnt );

            /*------------------------------------------*/
            /*  convert to output statusOfDTC.          */
            /*------------------------------------------*/
            newCylDTCStatus = Dem_DTC_CnvDTCStatus_ForOutput( newCylDTCStatus );

            if( newCylDTCStatus != Dem_LatchCylDTCStatus[misfireCylinderCnt] )                                                          /* [GUD]misfireCylinderCnt */
            {
                /* Change cylinder DTCStatus */
                Dem_NotifyCylinderDTCStatusChanged( misfireCylinderCnt, Dem_LatchCylDTCStatus[misfireCylinderCnt], newCylDTCStatus );   /* [GUD]misfireCylinderCnt */
            }
        }
    }
    return;
}

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Misfire_UpdateObdFFDInfo                             */
/* Description   | Update the freeze frame data Infomation of misfire.      */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] FreezeFrameRecordTrigger :                          */
/*               | [in] MisfireCylinder :                                   */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-9-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_UpdateObdFFDInfo
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger,
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) MisfireCylinder
)
{
    VAR( boolean, AUTOMATIC ) misfireEventKind;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) getMisfireCylinder;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) retCylinder;
    VAR( Dem_u08_MisfireKindType, AUTOMATIC ) misfireType;
    VAR( Dem_u08_MisfireKindType, AUTOMATIC ) misfireKindOfFFD;
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndexNum;
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndex;

    misfireObdFFDCylIndexNum = Dem_MisfireObdFFDCylIndexNum;

    misfireEventKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );
    if( misfireEventKind == (boolean)TRUE )
    {
        misfireObdFFDCylIndex = Dem_CfgInfoPm_GetObdFFDCylIndexOfMisfire( FreezeFrameRecordTrigger );
        if( misfireObdFFDCylIndex < misfireObdFFDCylIndexNum )                                                  /* [GUD:if]misfireObdFFDCylIndex */
        {
            /* OBDFFDCyl */
            Dem_Misfire_GetObdFFDCylToTmp( EventStrgIndex, misfireObdFFDCylIndex, &getMisfireCylinder );        /* [GUD]misfireObdFFDCylIndex */
            if( getMisfireCylinder == DEM_MISFIRE_CYLINDER_NON )
            {
#if ( DEM_OBDONUDS_SUPPORT == STD_ON )              /*  [FuncSw]    */
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                retCylinder = DEM_MISFIRE_CYLINDER_NON;
                Dem_Misfire_GetPairObdFFDCylToTmp( EventStrgIndex, misfireObdFFDCylIndex, &retCylinder );       /* [GUD]misfireObdFFDCylIndex */
                if( retCylinder == DEM_MISFIRE_CYLINDER_NON  )
#endif /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )    */
#endif /* ( DEM_OBDONUDS_SUPPORT == STD_ON )                */
                {
                    retCylinder = Dem_Misfire_SetFFDAccumCylinder( EventStrgIndex, FreezeFrameRecordTrigger, MisfireCylinder );
                    retCylinder = Dem_CfgInfoPm_MergeMultipleCylinderBit( retCylinder );
                    retCylinder = Dem_CfgInfoPm_GetMisfireLowestCylinderBitFromCylBit( retCylinder );
                }
                Dem_Misfire_SetObdFFDCylToTmp( EventStrgIndex, misfireObdFFDCylIndex, retCylinder );            /* [GUD]misfireObdFFDCylIndex */

#if ( DEM_OBDONUDS_SUPPORT == STD_ON )              /*  [FuncSw]    */
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                Dem_Misfire_UpdatePairObdFFDInfo( EventStrgIndex, misfireObdFFDCylIndex, retCylinder );         /* [GUD]misfireObdFFDCylIndex */
#endif /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )    */
#endif /* ( DEM_OBDONUDS_SUPPORT == STD_ON )                */

                /* MisfireKindOfOBDFFD */
                Dem_Misfire_GetMisfireKindOfObdFFDToTmp( misfireObdFFDCylIndex, &misfireKindOfFFD );            /* [GUD]misfireObdFFDCylIndex */
                if( misfireKindOfFFD == DEM_MISFIRE_KIND_INVALID )
                {
                    misfireType =   Dem_CfgInfoPm_GetMisfireType_InEvtStrgGrp( EventStrgIndex );
                    Dem_Misfire_SetMisfireKindOfObdFFDToTmp( misfireObdFFDCylIndex, misfireType );              /* [GUD]misfireObdFFDCylIndex */
                }
            }
        }
    }

    return;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */

/****************************************************************************/
/* Function Name | Dem_Misfire_UpdateFFDInfo                                */
/* Description   | Update the freeze frame data Infomation of misfire.      */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] FreezeFrameRecordTrigger :                          */
/*               | [in] MisfireCylinder :                                   */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_UpdateFFDInfo
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger,
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) MisfireCylinder
)
{
    VAR( boolean, AUTOMATIC ) misfireEventKind;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) getMisfireCylinder;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) retCylinder;
    VAR( Dem_u08_MisfireKindType, AUTOMATIC ) misfireType;
    VAR( Dem_u08_MisfireKindType, AUTOMATIC ) misfireKindOfFFD;
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) misfireFFDCylIndexNum;
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) misfireFFDCylIndex;

    misfireFFDCylIndexNum = Dem_MisfireFFDCylIndexNum;

    misfireEventKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );
    if( misfireEventKind == (boolean)TRUE )
    {
        misfireFFDCylIndex = Dem_CfgInfoPm_GetFFDCylIndexOfMisfire( FreezeFrameRecordTrigger );
        if( misfireFFDCylIndex < misfireFFDCylIndexNum )                                                /* [GUD:if]misfireFFDCylIndex */
        {
            /* FFDCyl */
            Dem_Misfire_GetFFDCylToTmp( EventStrgIndex, misfireFFDCylIndex, &getMisfireCylinder );      /* [GUD]misfireFFDCylIndex */
            if( getMisfireCylinder == DEM_MISFIRE_CYLINDER_NON )
            {
                retCylinder = Dem_Misfire_SetFFDAccumCylinder( EventStrgIndex, FreezeFrameRecordTrigger, MisfireCylinder );
                retCylinder = Dem_CfgInfoPm_MergeMultipleCylinderBit( retCylinder );
                retCylinder = Dem_CfgInfoPm_GetMisfireLowestCylinderBitFromCylBit( retCylinder );
                Dem_Misfire_SetFFDCylToTmp( EventStrgIndex, misfireFFDCylIndex, retCylinder );          /* [GUD]misfireFFDCylIndex */

                /* MisfireKindOfFFD */
                Dem_Misfire_GetMisfireKindOfFFDToTmp( misfireFFDCylIndex, &misfireKindOfFFD );          /* [GUD]misfireFFDCylIndex */
                if( misfireKindOfFFD == DEM_MISFIRE_KIND_INVALID )
                {
                    misfireType =   Dem_CfgInfoPm_GetMisfireType_InEvtStrgGrp( EventStrgIndex );
                    Dem_Misfire_SetMisfireKindOfFFDToTmp( misfireFFDCylIndex, misfireType );            /* [GUD]misfireFFDCylIndex */
                }
            }
        }
    }

    return;
}

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Misfire_CheckConfirmedFaultOfCAT                     */
/* Description   | Check the confirmed fault of CAT.                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Misfire_CheckConfirmedFaultOfCAT
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_EventKindType, AUTOMATIC ) eventKind;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) pendingFault;

    retVal = DEM_IRT_NG;

    eventKind = Dem_CfgInfoPm_GetEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );                     /* [GUD:RET:Not DEM_EVTKIND_TYPE_NON_OBD_EVENT] EventStrgIndex  */
    if( ( eventKind & DEM_EVTKIND_TYPE_MISFIRE_CAT_EVENT ) == DEM_EVTKIND_TYPE_MISFIRE_CAT_EVENT )
    {
        /* In the case of CAT event Index */
        pendingFault = Dem_Misfire_GetPendingStoreOfEmission();
        if( pendingFault == (boolean)TRUE )
        {
            /* Pending failure of Emission */
            retVal = DEM_IRT_OK;
        }
    }

    return retVal;
}
#endif /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON ) */
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )   */

/****************************************************************************/
/* Function Name | Dem_Misfire_SetExceedanceUsedForMisfireEmission          */
/* Description   | Set exceedanceUsed status.                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] ExceedanceUsedStatus : ExceedanceUsed status.       */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_SetExceedanceUsedForMisfireEmission
(
    VAR( boolean, AUTOMATIC ) ExceedanceUsedStatus
)
{
    Dem_ExceedanceUsedOfEmission = ExceedanceUsedStatus;

    return;
}

/****************************************************************************/
/* Function Name | Dem_Misfire_GetExceedanceUsedForMisfireEmission          */
/* Description   | Set exceedanceUsed status.                               */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | boolean : ExceedanceUsed status.                         */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_Misfire_GetExceedanceUsedForMisfireEmission
( void )
{
    return Dem_ExceedanceUsedOfEmission;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dem_Misfire_GetMisfireExcessConterThreshold              */
/* Description   | Get the ExcessConterThreshold of misfire.                */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/* Parameters    | [out] ExcessCntThresholdPtr :                            */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Misfire_GetMisfireExcessConterThreshold
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u08_MisfExceedanceCounterType, AUTOMATIC, AUTOMATIC )  ExcessCntThresholdPtr
)
{
    VAR( Dem_EventKindType, AUTOMATIC ) eventKind;
    VAR( boolean, AUTOMATIC ) exceedanceUsedEmission;
    VAR( boolean, AUTOMATIC ) misfireExceedanceUsedCat;

    *ExcessCntThresholdPtr = DEM_MISFIRE_UNUSED_EXCESSCONTERTHRESHOLD; /* 1 */

    eventKind = Dem_CfgInfoPm_GetEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );                     /* [GUD:RET:Not DEM_EVTKIND_TYPE_NON_OBD_EVENT] EventStrgIndex  */
    if( ( eventKind & DEM_EVTKIND_TYPE_MISFIRE_EVENT ) == DEM_EVTKIND_TYPE_MISFIRE_EVENT )
    {
        if( ( eventKind & DEM_EVTKIND_TYPE_MISFIRE_CAT_EVENT ) == DEM_EVTKIND_TYPE_MISFIRE_CAT_EVENT )
        {
            /* MisfireEvent: CAT */
            misfireExceedanceUsedCat = Dem_MisfireExceedanceUsedCat;
            if( misfireExceedanceUsedCat == (boolean)TRUE )
            {
                *ExcessCntThresholdPtr = DEM_MISFIRE_CAT_EXCESSCONTERTHRESHOLD; /* 3 */
            }
        }
        else
        {
            /* MisfireEvent: Emission */
            exceedanceUsedEmission = Dem_ExceedanceUsedOfEmission;
            if( exceedanceUsedEmission == (boolean)TRUE )
            {
                *ExcessCntThresholdPtr = DEM_MISFIRE_EMISSION_EXCESSCONTERTHRESHOLD; /* 4 */
            }
        }
    }

    return;
}

#if ( DEM_OBDONUDS_SUPPORT == STD_ON )
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Misfire_UpdatePairObdFFDInfo                         */
/* Description   | Update the freeze frame data Infomation of misfire.      */
/* Preconditions | EventStrgIndex is misfire                                */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] MisfireObdFFDCylIndex :                             */
/*               | [in] FFDCyl :                                            */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | new created.                                             */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Misfire_UpdatePairObdFFDInfo
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) MisfireObdFFDCylIndex,  /* [PRMCHK:CALLER] */
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) FFDCyl
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) misfirePairEventStrgIndex;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) pairCylinder;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultGetMisfirePairEvent;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFaultIndex;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) pairFaultIndex;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) pairStatusOfDTC;

    resultGetMisfirePairEvent= Dem_CfgInfoPm_GetMisfirePairEventStrgIndexByStrgIndex( EventStrgIndex, &misfirePairEventStrgIndex );
    if( resultGetMisfirePairEvent == DEM_IRT_OK )
    {
        resultOfGetFaultIndex = Dem_DataMngC_GetER_FaultIndex( misfirePairEventStrgIndex, &pairFaultIndex );    /* [GUD:RET:DEM_IRT_OK] misfirePairEventStrgIndex */
        if( resultOfGetFaultIndex == DEM_IRT_OK )
        {
            failRecordNum = Dem_FailRecordNum;
            if( pairFaultIndex < failRecordNum )
            {
                pairStatusOfDTC = DEM_DTCSTATUS_BYTE_DEFAULT;
                (void)Dem_DataMngC_GetER_StatusOfDTC( misfirePairEventStrgIndex, &pairStatusOfDTC );    /* no return check required */
                if( (( pairStatusOfDTC & DEM_UDS_STATUS_PDTC ) == DEM_UDS_STATUS_PDTC ) || (( pairStatusOfDTC & DEM_UDS_STATUS_CDTC ) == DEM_UDS_STATUS_CDTC ) )
                {
                    Dem_Misfire_GetObdFFDCylToTmp( misfirePairEventStrgIndex, MisfireObdFFDCylIndex, &pairCylinder );        /* [GUDCHK:CALLER]MisfireObdFFDCylIndex */
                    if( pairCylinder == DEM_MISFIRE_CYLINDER_NON  )
                    {
                        Dem_Misfire_SetObdFFDCylToTmp( misfirePairEventStrgIndex, MisfireObdFFDCylIndex, FFDCyl );      /* [GUDCHK:CALLER]MisfireObdFFDCylIndex */

                        /*  Sync OBDFFD RecordIndex : between base and pair event.  */
                        Dem_Misfire_SetObdRecordNumberIndexSyncStatus( (boolean)TRUE );
                    }
                }
            }
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_Misfire_SetObdRecordNumberIndexSyncStatus            */
/* Description   | Set execute sync OBDFFD RecordNumberIndex or not.        */
/* Preconditions | none                                                     */
/* Parameters    | ObdRecordNumberIndexSyncStatus                           */
/*               |             TRUE  : Sync OBDFFD RecordNumberIndex.       */
/*               |             FALSE : not Sync OBDFFD RecordNumberIndex.   */
/* Return Value  | boolean                                                  */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_SetObdRecordNumberIndexSyncStatus
(
    VAR( boolean, AUTOMATIC ) ObdRecordNumberIndexSyncStatus
)
{
    Dem_Misf_ObdRecordNumberIndexSyncStatus   =   ObdRecordNumberIndexSyncStatus;
    return ;
}

/****************************************************************************/
/* Function Name | Dem_Misfire_GetObdRecordNumberIndexSyncStatus            */
/* Description   | Get execute sync OBDFFD RecordNumberIndex or not.        */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | boolean                                                  */
/*               |             TRUE  : Sync OBDFFD RecordNumberIndex.       */
/*               |             FALSE : not Sync OBDFFD RecordNumberIndex.   */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | new created.                                             */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_Misfire_GetObdRecordNumberIndexSyncStatus
( void )
{
    return Dem_Misf_ObdRecordNumberIndexSyncStatus;
}

#endif /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON ) */
#endif /* ( DEM_OBDONUDS_SUPPORT == STD_ON ) */

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Misfire_JudgeClearableObdFreezeFrame                 */
/* Description   | judge clearable OBDFFD at clear EventStrgIndex's record. */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex : event index.                       */
/* Return Value  | TRUE  : clearable OBDFFD.                                */
/*               | FALSE : not clearable OBDFFD.                            */
/*               |                                                          */
/* Notes         | at OBDonUDS :                                            */
/*               |      No Pair EventStrgIndex :                            */
/*               |        -> can clear OBDFFD .                             */
/*               |      The paired Event does not have a FaultRecord.       */
/*               |        -> can clear OBDFFD .                             */
/*               |      The paired Event have a FaultRecord.                */
/*               |        -> CANNOT clear OBDFFD.                           */
/*               |                                                          */
/*               | at OBDonEDS :                                            */
/*               |        -> can clear OBDFFD always.                       */
/*               |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | new created.                                             */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_Misfire_JudgeClearableObdFreezeFrame
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex     /* MISRA DEVIATION */
)
{
#if ( DEM_OBDONUDS_SUPPORT == STD_ON )  /*  [FuncSw]    */
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) misfirePairEventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultGetMisfirePairEvent;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndexPairEvent;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( boolean, AUTOMATIC ) misfireEventKind;
    VAR( boolean, AUTOMATIC ) existOBDFFD;
#endif  /* ( DEM_OBDONUDS_SUPPORT == STD_ON )               */

    VAR( boolean, AUTOMATIC ) clearableOBDFFD;

    clearableOBDFFD     =   (boolean)TRUE;          /*  clearable OBDFFD.   */

#if ( DEM_OBDONUDS_SUPPORT == STD_ON )  /*  [FuncSw]    */

    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    /*  check EventStrgIndex : Misfire event or not.    */
    if ( EventStrgIndex < eventStorageNum )                                                                 /* [GUD:if]EventStrgIndex */
    {
        misfireEventKind    =   Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );       /* [GUD]EventStrgIndex */
        if( misfireEventKind == (boolean)TRUE )
        {
            resultGetMisfirePairEvent= Dem_CfgInfoPm_GetMisfirePairEventStrgIndexByStrgIndex( EventStrgIndex, &misfirePairEventStrgIndex );     /* [GUD]EventStrgIndex */

            if( resultGetMisfirePairEvent == DEM_IRT_OK )
            {
                /*  Get pair event's fault record index.        */
                (void)Dem_DataMngC_GetER_FaultIndex( misfirePairEventStrgIndex, &faultIndexPairEvent );     /* no return check required */
                failRecordNum = Dem_FailRecordNum;

                if( faultIndexPairEvent < failRecordNum )
                {
                    /*  pair event's fault record is exist.                 */
                    /*  check exist OBDFFD.                                 */
                    existOBDFFD =   Dem_DataMngC_GetFR_CheckExistOBDFFD( faultIndexPairEvent );
                    if ( existOBDFFD == (boolean)TRUE )
                    {
                        /*  pair event has OBDFFD. no clear OBDFFD.         */
                        /*  ( because linked same OBD FreezeFrame between EventStrgIndex and PairEventStrgIndex.)       */
                        clearableOBDFFD =   (boolean)FALSE;         /*  not clearable OBDFFD.   */
                    }
                }
            }
        }
    }
#endif  /* ( DEM_OBDONUDS_SUPPORT == STD_ON )               */

    return clearableOBDFFD;
}
#endif  /*   ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON ) */
#endif  /*   ( DEM_OBDFFD_SUPPORT == STD_ON )               */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
