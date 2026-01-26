/* Dem_AltIUMPR_c(v5-5-0)                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/AltIUMPR/CODE                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#if ( DEM_ALTIUMPR_SUPPORT == STD_ON )
#include <Dem/Dem_Common.h>
#include <Dem/Dem_InternalDataElement.h>
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Pm_DataAvl.h"
#include "../../../inc/Dem_Pm_AltIUMPR.h"
#include "../../../inc/Dem_Rc_DataMng.h"
#include "../../../inc/Dem_Rc_AltIUMPRMng.h"
#include "../../../inc/Dem_Rc_IUMPRMng.h"
#include "../../../usr/Dem_IUMPR_Callout.h"

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../cfg/Dem_Misfire_Cfg.h"
#endif  /*  ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )          */

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_ALTIUMPR_RECORD_SIZE            ((Dem_u16_EDRRecordSizeType)2U)
#define DEM_ALTIUMPR_BUF_OFFSET_NUMERATOR   ((Dem_u16_EDRRecordSizeType)0U)
#define DEM_ALTIUMPR_BUF_OFFSET_RATIO       ((Dem_u16_EDRRecordSizeType)1U)

#define DEM_ALTIUMPR_RECORD_VAL_INVALID     ((uint8)0xFFU)

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

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_AltIUMPR_GetCurrentMonitorActivityData
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC )        CurrentNumeratorPtr,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC )        CurrentDenominatorPtr
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

static VAR( boolean, DEM_VAR_NO_INIT ) Dem_AltIUMPR_MADKeepIncFlag;
static VAR( boolean, DEM_VAR_NO_INIT ) Dem_AltIUMPR_MANKeepIncFlag;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>


/****************************************************************************/
/* Function Name | Dem_AltIUMPR_ReadDenominator                             */
/* Description   | Read Alternative IUMPR Denominator                       */
/* Preconditions | none                                                     */
/* Parameters    | [out] DenominatorPtr :  Alternative IUMPR Denominator    */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_AltIUMPR_ReadDenominator
(
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DenominatorPtr
)
{
    Dem_AltIUMPRMng_GetDenominator( DenominatorPtr );

    return;
}


/****************************************************************************/
/* Function Name | Dem_AltIUMPR_ReadMonitorActivityData                     */
/* Description   | Read Monitor Activity Data                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventCtrlIndex : Event index.                       */
/*               | [in] DTCValue                                            */
/*               | [in] GetExtendDataMode                                   */
/*               | [out] BufferPtr :                                        */
/*               |        This parameter contains a byte pointer that poin- */
/*               |        ts to the buffer, to which the extended data rec- */
/*               |        ord shall be written to. The format is raw hexad- */
/*               |        ecimal values and contains no header-information. */
/*               | [in/out] BufSizePtr :                                    */
/*               |        When the function is called this parameter conta- */
/*               |        ins the maximum number of data bytes that can be  */
/*               |         written to the buffer.The function returns the - */
/*               |        actual number of written data bytes in this para- */
/*               |        meter.                                            */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |       DEM_IRT_OK : success                               */
/*               |       DEM_IRT_WRONG_RECORDNUMBER : wrong recordnumber    */
/*               |       DEM_IRT_WRONG_BUFFERSIZE : buffer size overflow    */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_AltIUMPR_ReadMonitorActivityData
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,                /* MISRA DEVIATION */
    VAR( Dem_u08_GetExtendDataModeType, AUTOMATIC ) GetExtendDataMode,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) BufferPtr,
    P2VAR( Dem_u16_EDRRecordSizeType, AUTOMATIC, AUTOMATIC ) BufSizePtr
)
{
    VAR( boolean, AUTOMATIC ) isMILIndicator;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( uint8, AUTOMATIC ) getNumeratorAndRatio;
    VAR( uint8, AUTOMATIC ) storeNumerator;
    VAR( uint8, AUTOMATIC ) storeRatio;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexCnt;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexNum;

    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( Dem_EventKindType, AUTOMATIC ) eventKind;
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */

    retVal = DEM_IRT_WRONG_RECORDNUMBER;
    storeNumerator      =   DEM_ALTIUMPR_RECORD_VAL_INVALID;
    storeRatio          =   DEM_ALTIUMPR_RECORD_VAL_INVALID;


    if( (*BufSizePtr) < DEM_ALTIUMPR_RECORD_SIZE )
    {
        retVal = DEM_IRT_WRONG_BUFFERSIZE;
    }
    else
    {
        /*  primary event only.         */
        eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( EventCtrlIndex );    /* [GUDCHK:CALLER]EventCtrlIndex *//* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */

        isMILIndicator    =   Dem_CfgInfoPm_ChkDTCCls_HasMILInd( eventStrgIndex );                          /* [GUDCHK:CALLER]EventCtrlIndex */
        if( isMILIndicator == (boolean)TRUE ) /*  MIL     */
        {

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
            eventKind       =   Dem_CfgInfoPm_GetEventKindOfSpecific_InEvtStrgGrp( eventStrgIndex );        /* [GUDCHK:CALLER]EventCtrlIndex */

            if( ( eventKind & DEM_EVTKIND_TYPE_MISFIRE_EVENT ) == DEM_EVTKIND_TYPE_MISFIRE_EVENT )
            {
                getNumeratorAndRatio = Dem_AltIUMPR_ReadMonitorActivityDataForCylinder( DTCValue, &storeNumerator, &storeRatio );
                if( getNumeratorAndRatio == DEM_IRT_OK )
                {
                    retVal = DEM_IRT_OK;
                }
            }
            else
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */
            {
                if ( GetExtendDataMode == DEM_EDR_GETEDRMODE_DTC )
                {
                    /*------------------------------*/
                    /*  DTC group.                  */
                    /*------------------------------*/
                    /*  get minimum numerator record.           */
                    eventCtrlIndexNum   =   Dem_CmbEvt_NumOfEventCtrlIndex_InEvtStrgGrp( eventStrgIndex );  /* [GUDCHK:CALLER]EventCtrlIndex *//*  get EventCtrlIndex of EventStorageGroup max number  */
                    eventCtrlIndex      =   EventCtrlIndex;

                    for ( eventCtrlIndexCnt = ( Dem_u16_EventCtrlIndexType )0U; eventCtrlIndexCnt < eventCtrlIndexNum; eventCtrlIndexCnt++ )
                    {
                        getNumeratorAndRatio    =   Dem_AltIUMPR_GetCurrentMonitorActivityData( eventCtrlIndex, &storeNumerator, &storeRatio );
                        if ( getNumeratorAndRatio == DEM_IRT_OK )
                        {
                            retVal = DEM_IRT_OK;
                        }
                        /*  get next Index.         */
                        eventCtrlIndex  =   Dem_CmbEvt_GetNextEventCtrlIndex_InEvtStrgGrp( eventCtrlIndex );
                    }
                }
                else
                {
                    /*------------------------------*/
                    /*  event Id.                   */
                    /*------------------------------*/
                    retVal  =   Dem_AltIUMPR_GetCurrentMonitorActivityData( EventCtrlIndex, &storeNumerator, &storeRatio ); /* [GUDCHK:CALLER]EventCtrlIndex */
                }
            }
        }

        if ( retVal == DEM_IRT_OK )
        {
            BufferPtr[ DEM_ALTIUMPR_BUF_OFFSET_NUMERATOR ]  = storeNumerator;
            BufferPtr[ DEM_ALTIUMPR_BUF_OFFSET_RATIO ]      = storeRatio;
            (*BufSizePtr) = DEM_ALTIUMPR_RECORD_SIZE;
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_AltIUMPR_GetCurrentMonitorActivityData               */
/* Description   | Read DTC Based AltIUMPR                                  */
/* Preconditions | none                                                     */
/* Parameters    | [in]     EventCtrlIndex                                  */
/*               | [in/out]    CurrentNumeratorPtr                          */
/*               | [in/out]    CurrentDenominatorPtr                        */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |       DEM_IRT_OK : success                               */
/*               |       DEM_IRT_WRONG_RECORDNUMBER : wrong recordnumber    */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_AltIUMPR_GetCurrentMonitorActivityData
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC )        CurrentNumeratorPtr,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC )        CurrentDenominatorPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( uint8, AUTOMATIC ) getNumeratorAndRatio;
    VAR( uint8, AUTOMATIC ) numerator;
    VAR( uint8, AUTOMATIC ) ratio;

    VAR( uint8, AUTOMATIC ) storeNumerator;
    VAR( uint8, AUTOMATIC ) storeRatio;

    storeNumerator  =   *CurrentNumeratorPtr;
    storeRatio      =   *CurrentDenominatorPtr;

    retVal = DEM_IRT_WRONG_RECORDNUMBER;

    /*  get numerator and ratio.    */
    getNumeratorAndRatio = Dem_AltIUMPRMng_GetNumeratorAndRatio( EventCtrlIndex, &numerator, &ratio );
    if( getNumeratorAndRatio == DEM_IRT_OK )
    {
        if ( storeNumerator > numerator )
        {
            /*  get minimum numerator and ratio.        */
            storeNumerator  =   numerator;
            storeRatio      =   ratio;
            retVal = DEM_IRT_OK;
        }
        else if ( storeNumerator == numerator )
        {
            if ( storeRatio > ratio )
            {
                storeRatio      =   ratio;
                retVal = DEM_IRT_OK;
            }
        }
        else
        {
            /*  no process.     */
        }
    }
    *CurrentNumeratorPtr    =   storeNumerator;
    *CurrentDenominatorPtr  =   storeRatio;

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_AltIUMPRMng_SetTestCompleteThisCycle                 */
/* Description   | set SetTestCompleteThisCycle.                            */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventCtrlIndex : Event index.                       */
/*               | [in] TestCompleteThisCycle : TestCompleteThisCycle.      */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_AltIUMPR_SetTestCompleteThisCycle
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,            /* [PRMCHK:CALLER] */
    VAR( Dem_u08_AltIUMPRTestCompletedThisCycleType, AUTOMATIC ) TestCompleteThisCycle
)
{
    VAR( boolean, AUTOMATIC ) eventOBDKind;
    eventOBDKind    =   Dem_CfgInfoPm_CheckEventKindOfOBD_ByEvtCtrlIdx( EventCtrlIndex );   /* [GUDCHK:CALLER]EventCtrlIndex */
    if( eventOBDKind == (boolean)TRUE ) /*  OBD     */
    {
        Dem_AltIUMPRMng_SetTestCompleteThisCycle( EventCtrlIndex, TestCompleteThisCycle );  /* [GUDCHK:CALLER]EventCtrlIndex */
    }
    return ;
}


/****************************************************************************/
/* Function Name | Dem_AltIUMPR_IncNumeratorCounts                          */
/* Description   | Increment Numerator Counts                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventCtrlIndex : Event index.                       */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_AltIUMPR_IncNumeratorCounts
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex             /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_AltIUMPRTestCompletedThisCycleType, AUTOMATIC ) testCompleteThisCycle;
    VAR( boolean, AUTOMATIC ) eventOBDKind;

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_EventKindType, AUTOMATIC ) eventKind;
#endif  /*  ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )          */

    eventOBDKind    =   Dem_CfgInfoPm_CheckEventKindOfOBD_ByEvtCtrlIdx( EventCtrlIndex );   /* [GUDCHK:CALLER]EventCtrlIndex */
    if( eventOBDKind == (boolean)TRUE ) /*  OBD     */
    {
        if( Dem_AltIUMPR_MANKeepIncFlag == (boolean)FALSE )
        {
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
            eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( EventCtrlIndex );        /* [GUDCHK:CALLER]EventCtrlIndex *//* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */
            eventKind       =   Dem_CfgInfoPm_GetEventKindOfSpecific_InEvtStrgGrp( eventStrgIndex );

            if( ( eventKind & DEM_EVTKIND_TYPE_MISFIRE_EVENT ) == DEM_EVTKIND_TYPE_MISFIRE_EVENT )
            {
                Dem_AltIUMPR_IncNumeratorCountsForCylinder( eventStrgIndex );
            }
            else
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */
            {
                testCompleteThisCycle   =   DEM_ALTIUMPR_TCTOC_NOTTESTCOMPLETE;

                /*  get test completed.                 */
                retVal  =   Dem_AltIUMPRMng_GetTestCompleteThisCycle( EventCtrlIndex, &testCompleteThisCycle ); /* [GUDCHK:CALLER]EventCtrlIndex */
                if ( retVal == DEM_IRT_OK )
                {
                    if ( testCompleteThisCycle == DEM_ALTIUMPR_TCTOC_TESTCOMPLETE )
                    {
                        Dem_AltIUMPRMng_IncNumeratorCounts( EventCtrlIndex );   /* [GUDCHK:CALLER]EventCtrlIndex */
                    }
                }
            }
        }
    }
    return;
}


/****************************************************************************/
/* Function Name | Dem_AltIUMPR_IncDenominatorProccess                      */
/* Description   | Proccess for Increment Denominator                       */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_AltIUMPR_IncDenominatorProccess
( void )
{
    VAR( Dem_IumprDenomCondStatusType, AUTOMATIC ) conditionStatus;

    if( Dem_AltIUMPR_MADKeepIncFlag == (boolean)FALSE )
    {
        Dem_IUMPRMng_GetIUMPRDenCondition( DEM_IUMPR_GENERAL_DENOMINATOR, &conditionStatus );
        if( conditionStatus == DEM_IUMPR_DEN_STATUS_REACHED )
        {
            Dem_AltIUMPRMng_IncDenominatorProccess();
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_AltIUMPR_GetPendingAndMIL                            */
/* Description   | Proccess for Keep Denominator and Numerator              */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_AltIUMPR_GetPendingAndMIL
( void )
{
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultRecordNum;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retValDTC;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retValAble;
    VAR( boolean, AUTOMATIC ) isMILIndicator;
    VAR( boolean, AUTOMATIC ) eventOBDKind;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( boolean, AUTOMATIC ) pendingMILCheckFlag;
    VAR( boolean, AUTOMATIC ) keepFlag;
    VAR( boolean, AUTOMATIC ) madCondition;
    VAR( boolean, AUTOMATIC ) manCondition;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    Dem_AltIUMPR_MADKeepIncFlag  = (boolean)FALSE;
    Dem_AltIUMPR_MANKeepIncFlag  = (boolean)FALSE;
    keepFlag  = (boolean)FALSE;
    faultRecordNum = Dem_FailRecordNum;

    for( faultIndex = (Dem_u08_FaultIndexType)0U; faultIndex < faultRecordNum; faultIndex++ )
    {
        pendingMILCheckFlag =   (boolean)FALSE;

        retVal = Dem_DataMngC_GetFR_EventStrgIndex( faultIndex, &eventStrgIndex );
        if( retVal == DEM_IRT_OK )
        {
            if ( eventStrgIndex < eventStorageNum )                                                     /* [GUD:if]eventStrgIndex */
            {
                eventOBDKind    =   Dem_CfgInfoPm_CheckEventKindOfOBD_InEvtStrgGrp( eventStrgIndex );   /* [GUD]eventStrgIndex */
                if( eventOBDKind == (boolean)TRUE ) /*  OBD     */
                {
                    statusOfDTC = DEM_DTCSTATUS_BYTE_ALL_OFF;
                    retValDTC = Dem_DataMngC_GetER_StatusOfDTC( eventStrgIndex, &statusOfDTC );         /* [GUD]eventStrgIndex */
                    if( retValDTC == DEM_IRT_OK )
                    {
                        pendingMILCheckFlag =   (boolean)TRUE;
                    }
                }
            }
        }
        if ( pendingMILCheckFlag == (boolean)TRUE )
        {
            if( ( statusOfDTC & DEM_UDS_STATUS_PDTC ) == DEM_UDS_STATUS_PDTC )
            {
                retValAble = Dem_DataAvl_GetEvtAvl_InEvtStrgGrp( eventStrgIndex );              /* [GUD]eventStrgIndex */
                if( retValAble == (boolean)TRUE )
                {
                    isMILIndicator  =   Dem_CfgInfoPm_ChkDTCCls_HasMILInd( eventStrgIndex );    /* [GUD]eventStrgIndex */
                    if( isMILIndicator == (boolean)TRUE )
                    {
                        keepFlag = (boolean)TRUE;
                        break;
                    }
                }
            }
        }
    }

    if ( keepFlag == (boolean)TRUE )
    {
        Dem_AltIUMPR_MADKeepIncFlag  = (boolean)TRUE;
        Dem_AltIUMPR_MANKeepIncFlag  = (boolean)TRUE;
    }
    else
    {
        madCondition = (boolean)FALSE;
        manCondition = (boolean)FALSE;
        Dem_JudgeAlternativeIUMPRPauseConditions( &madCondition, &manCondition );
        if( madCondition == (boolean)TRUE )
        {
            Dem_AltIUMPR_MADKeepIncFlag = (boolean)TRUE;
        }
        if( manCondition == (boolean)TRUE )
        {
            Dem_AltIUMPR_MANKeepIncFlag = (boolean)TRUE;
        }
    }

    return;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* ( DEM_ALTIUMPR_SUPPORT == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
