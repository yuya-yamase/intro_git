/* Dem_DataCtl_OBD_InfoOrder_c(v5-9-0)                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_OBD_InfoOrder/CODE                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../cfg/Dem_Data_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_CmnLib_DataAvl.h"
#include "../../../inc/Dem_CmnLib_DTC_FilDTC.h"
#include "../../../inc/Dem_Pm_DataAvl.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Pm_DataCtl_OBD.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_Pm_DTC.h"
#include "../../../inc/Dem_Rc_OdrLst.h"
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

#if ( DEM_OBD_SUPPORT == STD_ON )
static FUNC( boolean, DEM_CODE ) Dem_Data_GetTargetOfFilteredDTC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus,              /* MISRA DEVIATION */
    P2CONST( Dem_SetDTCFilterType, AUTOMATIC, AUTOMATIC ) DTCFilterPtr,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr,
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, AUTOMATIC ) DTCSeverityPtr
);
#endif  /* ( DEM_OBD_SUPPORT == STD_ON )    */


#if ( DEM_PID_SUPPORT == STD_ON )
#if ( DEM_WWH_OBD_SUPPORT == STD_OFF )
#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )
static FUNC( boolean, DEM_CODE ) Dem_Data_CheckCountableConfirmedDTC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) EndOfSearchOrderListIndex
);
#endif  /*  ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )     */
#endif  /* ( DEM_WWH_OBD_SUPPORT == STD_OFF )   */
#endif  /* ( DEM_PID_SUPPORT == STD_ON )    */

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

#if ( DEM_OBD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_GetFilteredObdDTC                               */
/* Description   | Gets the next filtered OBD DTC and its DTC status.       */
/* Preconditions | Dem_DTC_SetDTCFilter being executed.                     */
/* Parameters    | [in/out] FaultSearchIndexPtr :                           */
/*               |        Search Index                                      */
/*               | [in] DTCFilterPtr :                                      */
/*               |        DTC Filter                                        */
/*               | [out] FilterdEventStrgIndexPtr :                         */
/*               |        Filtered Event Index                              */
/*               | [out] DTCValuePtr :                                      */
/*               |        DTC Value                                         */
/*               | [out] DTCStatusPtr :                                     */
/*               |        Status Of DTC                                     */
/*               | [out] DTCSeverityPtr :                                   */
/*               |        Severity Of DTC                                   */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Returned next filtered element       */
/*               |        DEM_IRT_NO_MATCHING_ELEMENT : No further element  */
/*               |         (matching the filter criteria) found             */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetFilteredObdDTC
(
    P2VAR( Dem_u08_OrderIndexType, AUTOMATIC, AUTOMATIC ) FaultSearchIndexPtr,
    P2CONST( Dem_SetDTCFilterType, AUTOMATIC, AUTOMATIC ) DTCFilterPtr,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) FilterdEventStrgIndexPtr,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr,
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, AUTOMATIC ) DTCSeverityPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) OrderExistFlag;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) faultSearchIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( boolean, AUTOMATIC ) breakFlg;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) failRecordNum;
    VAR( boolean, AUTOMATIC ) eventOBDKind;
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) eventMisfireKind;
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;

    retVal = DEM_IRT_NO_MATCHING_ELEMENT;
    breakFlg = (boolean)FALSE;
    failRecordNum = (Dem_u08_OrderIndexType)Dem_FailRecordNum;
    eventStorageNum = Dem_CfgInfoPm_GetMaxNumberOfOBDEvent(); /*  event index check  : range of OBD event(may include nonOBD event).  */

#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_FILDTC_SUPPORT == STD_ON )  /*  [FuncSw]    */
    if ( *FaultSearchIndexPtr == ( Dem_u08_OrderIndexType )0U )
    {
        Dem_CmbEvt_StartOfCheckOutputFilteredDTC();
    }
#endif  /*  ( DEM_COMBINEDEVENT_ONRETRIEVAL_FILDTC_SUPPORT == STD_ON )     */

    for( faultSearchIndex = *FaultSearchIndexPtr; faultSearchIndex < failRecordNum; faultSearchIndex++ )
    {
        if( DTCFilterPtr->DTCStatusMask == DEM_UDS_STATUS_PDTC )
        {
            Dem_Data_GetPendingOrderEventStrgIndex( faultSearchIndex, &eventStrgIndex, &faultIndex, &statusOfDTC, &OrderExistFlag );
        }
        else
        {
            /* DEM_UDS_STATUS_CDTC */
            Dem_Data_GetConfirmedOrderEventStrgIndex( faultSearchIndex, &eventStrgIndex, &faultIndex, &statusOfDTC, &OrderExistFlag );
        }

        if( OrderExistFlag == (boolean)TRUE )
        {
            if( eventStrgIndex < eventStorageNum )                                                                  /* [GUD:if]eventStrgIndex */
            {
                eventOBDKind    =   Dem_CfgInfoPm_CheckEventKindOfOBD_InEvtStrgGrp( eventStrgIndex );   /* [GUD]eventStrgIndex */
                if( eventOBDKind == (boolean)TRUE ) /*  OBD     */
                {
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                    /*------------------------------------------*/
                    /*  exclude misfire event.                  */
                    /*  because search in caller already.       */
                    /*------------------------------------------*/
                    eventMisfireKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( eventStrgIndex );
                    if( eventMisfireKind == (boolean)FALSE )
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */
                    {
                        breakFlg    =   Dem_Data_GetTargetOfFilteredDTC( eventStrgIndex, statusOfDTC, DTCFilterPtr, DTCValuePtr, DTCStatusPtr, DTCSeverityPtr );    /* [GUD]eventStrgIndex */
                        if ( breakFlg == (boolean)TRUE )
                        {
                            *FilterdEventStrgIndexPtr   = eventStrgIndex;
                            retVal                      = DEM_IRT_OK;
                        }
                    }
                }
            }
        }

        if( breakFlg == (boolean)TRUE )
        {
            break;
        }
    }

    if( breakFlg == (boolean)TRUE )
    {
        faultSearchIndex = faultSearchIndex + (Dem_u08_OrderIndexType)1U;
    }

    *FaultSearchIndexPtr = faultSearchIndex;

    return retVal;
}

#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_FILDTC_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_Data_GetTargetOfFilteredDTC                          */
/* Description   | Gets target FilteredDTC.                                 */
/* Preconditions | Dem_DTC_SetDTCFilter being executed.                     */
/* Parameters    | [in] EventStrgIndex  :                                   */
/*               | [in] DTCStatus       :                                   */
/*               | [in] DTCFilterPtr    :                                   */
/*               | [out] DTCValuePtr    :  DTC                              */
/*               | [out] DTCStatusPtr   :  Status Of DTC                    */
/*               | [out] DTCSeverityPtr :  Severity Of DTC                  */
/* Return Value  | boolean                                                  */
/*               |        TRUE   : output target.                           */
/*               |        FALSE  : not output target.                       */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_Data_GetTargetOfFilteredDTC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,                /* [PRMCHK:CALLER] */
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus,
    P2CONST( Dem_SetDTCFilterType, AUTOMATIC, AUTOMATIC ) DTCFilterPtr,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr,
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, AUTOMATIC ) DTCSeverityPtr
)
{
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) udsDTCValue;
#if ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )    /*  [FuncSw]    */
    VAR( Dem_u16_ObdDTCValueType, AUTOMATIC ) obdDTCValue;
#endif  /*   ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )           */

    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retChkSeverity;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retStatusMask;
    VAR( Dem_DTCSeverityType, AUTOMATIC ) severity;
    VAR( boolean, AUTOMATIC ) retValidateDTC;
    VAR( boolean, AUTOMATIC ) getTarget;

    getTarget   =   (boolean)FALSE;

    severity     =   Dem_CfgInfoPm_GetDTCSeverityClass( EventStrgIndex );       /* [GUDCHK:CALLER]EventStrgIndex */

    if( DTCFilterPtr->FilterWithSeverity == (boolean)TRUE )
    {
        /* check DTC severity for SID19-42 */
        retChkSeverity = Dem_DTC_CheckDTCSeverityForFilter( DTCFilterPtr->DTCSeverityMask, &severity );
    }
    else
    {
        retChkSeverity = DEM_IRT_OK;
    }

    if ( retChkSeverity == DEM_IRT_OK )
    {
        if( DTCFilterPtr->DTCFormat == DEM_DTC_FORMAT_UDS )
        {
            /* set argument for SID19-42 */
            /* validate UDS DTC */
            udsDTCValue     = Dem_CfgInfoPm_GetUdsDTCValue( EventStrgIndex );   /* [GUDCHK:CALLER]EventStrgIndex */
            retValidateDTC  = Dem_DataAvl_ValidateDTC( udsDTCValue );
            if( retValidateDTC == (boolean)TRUE )
            {
                /* translate DTCStatus */
                *DTCStatusPtr   =   DTCStatus;
                (void)Dem_DTC_TranslateDTCStatusForOutputByDTC( EventStrgIndex, DTCStatusPtr ); /* no return check required */

                *DTCStatusPtr   =   Dem_DTC_CnvDTCStatus_PmAvailabilityMask( *DTCStatusPtr );

                retStatusMask   =   Dem_DTC_CheckDTCStatusForFilter( DTCFilterPtr->DTCStatusMask, *DTCStatusPtr );
                if ( retStatusMask == DEM_IRT_OK )
                {
                    *DTCValuePtr    =  udsDTCValue;
                    *DTCSeverityPtr =   severity;

                    getTarget = (boolean)TRUE;
                }
            }
        }
#if ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )    /*  [FuncSw]    */
        else if ( DTCFilterPtr->DTCFormat == DEM_DTC_FORMAT_OBD )
        {
            /* set argument for SID03,SID07 */
            /* eventOBDKind is TRUE, because filtered event is OBD */
            obdDTCValue         =   Dem_CfgInfoPm_GetObdDTCValue( EventStrgIndex ); /* [GUDCHK:CALLER]EventStrgIndex */
            *DTCValuePtr        =   (Dem_u32_DTCValueType)obdDTCValue;
            *DTCStatusPtr       =   DTCStatus;
            *DTCSeverityPtr     =   severity;

            getTarget = (boolean)TRUE;
        }
#endif  /*   ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )           */
        else
        {
            /*  no match format.        */
        }
    }
    return getTarget;
}
#endif  /* ( DEM_COMBINEDEVENT_ONRETRIEVAL_FILDTC_SUPPORT == STD_OFF ) */

#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_FILDTC_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_GetTargetOfFilteredDTC                          */
/* Description   | Gets target FilteredDTC.                                 */
/* Preconditions | Dem_DTC_SetDTCFilter being executed.                     */
/* Parameters    | [in] EventStrgIndex  :                                   */
/*               | [in] DTCStatus       :                                   */
/*               | [in] DTCFilterPtr    :                                   */
/*               | [out] DTCValuePtr    :  DTC                              */
/*               | [out] DTCStatusPtr   :  Status Of DTC                    */
/*               | [out] DTCSeverityPtr :  Severity Of DTC                  */
/* Return Value  | boolean                                                  */
/*               |        TRUE   : output target.                           */
/*               |        FALSE  : not output target.                       */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/*   v5-7-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_Data_GetTargetOfFilteredDTC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,                /* [PRMCHK:CALLER] */
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus,              /* MISRA DEVIATION */
    P2CONST( Dem_SetDTCFilterType, AUTOMATIC, AUTOMATIC ) DTCFilterPtr,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr,
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, AUTOMATIC ) DTCSeverityPtr
)
{
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) udsDTCValue;
#if ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )    /*  [FuncSw]    */
    VAR( Dem_u16_ObdDTCValueType, AUTOMATIC ) obdDTCValue;
#endif  /*   ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )           */

    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retOutput;
    VAR( boolean, AUTOMATIC ) retOutputDTC;
    VAR( boolean, AUTOMATIC ) retValidateDTC;
    VAR( boolean, AUTOMATIC ) getTarget;

    getTarget   =   (boolean)FALSE;

    if( DTCFilterPtr->DTCFormat == DEM_DTC_FORMAT_UDS )
    {
        /* set argument for SID19-42 */
        /* validate UDS DTC */
        udsDTCValue     = Dem_CfgInfoPm_GetUdsDTCValue( EventStrgIndex );                       /* [GUDCHK:CALLER]EventStrgIndex */
        retValidateDTC  = Dem_DataAvl_ValidateDTC( udsDTCValue );
        if( retValidateDTC == (boolean)TRUE )
        {
            /*  judge output DTC info.          */
            retOutputDTC = Dem_CmbEvt_CheckOutputFilteredUdsDTC( EventStrgIndex, udsDTCValue ); /* [GUDCHK:CALLER]EventStrgIndex */
            if( retOutputDTC == (boolean)TRUE )
            {
                /*  get merged statusOfDTC. with checking filter DTCSeverityMask.   */
                /*  Merge WIRStatus is in Dem_DTC_GetDTCStatusByDTCAndSeverity().   */
                retOutput   =   Dem_DTC_GetDTCStatusByDTCAndSeverity( EventStrgIndex, DTCFilterPtr->DTCStatusMask, DTCFilterPtr->FilterWithSeverity, DTCFilterPtr->DTCSeverityMask, DTCStatusPtr, DTCSeverityPtr );    /* no return check required *//* [GUDCHK:CALLER]EventStrgIndex */
                if ( retOutput == DEM_IRT_OK )
                {
                    *DTCValuePtr    =   udsDTCValue;
                    getTarget       =   (boolean)TRUE;
                }
            }
        }
    }
#if ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )    /*  [FuncSw]    */
    else if ( DTCFilterPtr->DTCFormat == DEM_DTC_FORMAT_OBD )
    {
        /* set argument for SID03,SID07 */
        /* eventOBDKind is TRUE, because filtered event is OBD */
        obdDTCValue         =   Dem_CfgInfoPm_GetObdDTCValue( EventStrgIndex );                         /* [GUDCHK:CALLER]EventStrgIndex */
        retOutputDTC        =   Dem_CmbEvt_CheckOutputFilteredObdDTC( EventStrgIndex, obdDTCValue );    /* [GUDCHK:CALLER]EventStrgIndex */
        if( retOutputDTC == (boolean)TRUE )
        {
            *DTCValuePtr        =   (Dem_u32_DTCValueType)obdDTCValue;
            *DTCStatusPtr       =   DTCStatus;
            *DTCSeverityPtr     =   Dem_CfgInfoPm_GetDTCSeverityClass( EventStrgIndex );                /* [GUDCHK:CALLER]EventStrgIndex */

            /*  no check DTCSeverityMask.       */
            getTarget           =   (boolean)TRUE;
        }
    }
#endif  /*   ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )           */
    else
    {
        /*  no match format.        */
    }

    return getTarget;
}
#endif  /* ( DEM_COMBINEDEVENT_ONRETRIEVAL_FILDTC_SUPPORT == STD_ON )  */

#endif  /* ( DEM_OBD_SUPPORT == STD_ON )    */

#if ( DEM_PID_SUPPORT == STD_ON )
#if ( DEM_WWH_OBD_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_Data_GetNumberOfOBDDTCByDTCStatus_forPIDDataA        */
/* Description   | Get Number of OBD DTC by DTC status.                     */
/* Preconditions | none                                                     */
/* Parameters    | [out] NumberOfConfirmedPtr                               */
/*               |        0 - 255 : Number of Confirmed OBDDTC              */
/*               | [out] NumberOfMILPtr                                     */
/*               |        0 - 255 : Number of WIRbit is ON OBDDTC           */
/* Return Value  | None.                                                    */
/*               |                                                          */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | rename from Dem_Data_GetNumberOfOBDDTCByDTCStatus(v5-3-0).*/
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_GetNumberOfOBDDTCByDTCStatus_forPIDDataA
(
    P2VAR( Dem_u16_EventNumType, AUTOMATIC, AUTOMATIC ) NumberOfConfirmedPtr,
    P2VAR( Dem_u16_EventNumType, AUTOMATIC, AUTOMATIC ) NumberOfMILPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( boolean, AUTOMATIC ) OrderExistFlag;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) numberOfConfirmedDTC;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) numberOfMILOnDTC;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) orderListIndex;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) failRecordNum;
    VAR( boolean, AUTOMATIC ) eventOBDKind;
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) eventMisfireKind;
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( boolean, AUTOMATIC ) isMILIndicator;
#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )  /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) retOutput;
#endif  /*  ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )     */

    /*  count start                 */
    numberOfConfirmedDTC = (Dem_u08_OrderIndexType)0U;
    numberOfMILOnDTC     = (Dem_u08_OrderIndexType)0U;
    failRecordNum = (Dem_u08_OrderIndexType)Dem_FailRecordNum;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    for( orderListIndex = (Dem_u08_OrderIndexType)0U; orderListIndex < failRecordNum; orderListIndex++ )
    {
        eventStrgIndex  = DEM_EVENTSTRGINDEX_INVALID;
        statusOfDTC = DEM_DTCSTATUS_BYTE_ALL_OFF;
        Dem_Data_GetConfirmedOrderEventStrgIndex( orderListIndex, &eventStrgIndex, &faultIndex, &statusOfDTC, &OrderExistFlag );

        if( OrderExistFlag != (boolean)FALSE )
        {
            if( eventStrgIndex < eventStorageNum )                                                                  /* [GUD:if]eventStrgIndex */
            {
                eventOBDKind    =   Dem_CfgInfoPm_CheckEventKindOfOBD_InEvtStrgGrp( eventStrgIndex );               /* [GUD]eventStrgIndex */
                if( eventOBDKind == (boolean)TRUE ) /*  OBD     */
                {
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                    eventMisfireKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( eventStrgIndex );        /* [GUD]eventStrgIndex */
                    if( eventMisfireKind == (boolean)FALSE )
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */
                    {
                        /*  normal event.(no misfire)   */
                        /*  Confirmed DTC           */
                        if( ( statusOfDTC & DEM_UDS_STATUS_CDTC ) != DEM_DTCSTATUS_BYTE_ALL_OFF )
                        {
#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )  /*  [FuncSw]    */
                            retOutput   =   Dem_Data_CheckCountableConfirmedDTC( eventStrgIndex, orderListIndex );  /* [GUD]eventStrgIndex */
                            if ( retOutput == (boolean)TRUE )
#endif  /*  ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )     */
                            {
                                numberOfConfirmedDTC = numberOfConfirmedDTC + (Dem_u08_OrderIndexType)1U;
                            }
                        }
                        else
                        {
                            /* No Process. */
                        }

                        /*  bit7 : ON ?             */
                        if( ( statusOfDTC & DEM_UDS_STATUS_WIR ) != DEM_DTCSTATUS_BYTE_ALL_OFF )
                        {
                            /*  check Indicator type.   */
                            isMILIndicator  =   Dem_CfgInfoPm_ChkDTCCls_HasMILInd( eventStrgIndex );                /* [GUD]eventStrgIndex */
                            if( isMILIndicator == (boolean)TRUE )
                            {
                                /*  WIRbit ON DTC       */
                                numberOfMILOnDTC = numberOfMILOnDTC + (Dem_u08_OrderIndexType)1U;
                            }
                        }
                    }
                }
            }
        }
    }
    /*  Number of Confirmed.        */
    *NumberOfConfirmedPtr = numberOfConfirmedDTC;

    /*  Number of WIRbit is ON.     */
    *NumberOfMILPtr = numberOfMILOnDTC;

    return ;
}
#endif  /* ( DEM_WWH_OBD_SUPPORT == STD_OFF )   */
#endif  /* ( DEM_PID_SUPPORT == STD_ON )    */

#if ( DEM_PID_CALC_DEMINTERNALPID_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_GetOBDDTCActiveStatus_CDTCAndMIL_forCalcPID     */
/* Description   | Get ActiveStatus : CDTC and MIL.                         */
/* Preconditions | none                                                     */
/* Parameters    | [out] IsActiveCDTCPtr                                    */
/*               |          TRUE    :   active.                             */
/*               |          FALSE   :   not active.                         */
/*               |          NULL_PTR : correct.( ignore with this function )*/
/*               | [out] IsActiveMILPtr                                     */
/*               |          TRUE    :   active.                             */
/*               |          FALSE   :   not active.                         */
/*               |          NULL_PTR : correct.( ignore with this function )*/
/* Return Value  | None.                                                    */
/*               |                                                          */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_Data_GetNumberOfOBDDTCByDTCStatus_forPIDDataA. */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_GetOBDDTCActiveStatus_CDTCAndMIL_forCalcPID
(
    P2VAR( boolean, AUTOMATIC, AUTOMATIC )  IsActiveCDTCPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC )  IsActiveMILPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( boolean, AUTOMATIC ) OrderExistFlag;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC;

    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) orderListIndex;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( boolean, AUTOMATIC ) eventOBDKind;
    VAR( boolean, AUTOMATIC ) isMILIndicator;
    VAR( boolean, AUTOMATIC ) isActiveCDTC;
    VAR( boolean, AUTOMATIC ) isActiveMIL;
    VAR( boolean, AUTOMATIC ) searchCompleteCDTC;
    VAR( boolean, AUTOMATIC ) searchCompleteMIL;

    isActiveCDTC    = (boolean)FALSE;
    isActiveMIL     = (boolean)FALSE;

    searchCompleteCDTC      = (boolean)FALSE;
    searchCompleteMIL       = (boolean)FALSE;

    /*  check search or not.        */
    if ( IsActiveCDTCPtr == NULL_PTR )
    {
        /*  no search.      */
        searchCompleteCDTC      = (boolean)TRUE;
    }
    if ( IsActiveMILPtr == NULL_PTR )
    {
        /*  no search.      */
        searchCompleteMIL       = (boolean)TRUE;
    }

    /*  count start                 */
    failRecordNum = (Dem_u08_OrderIndexType)Dem_FailRecordNum;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    for( orderListIndex = (Dem_u08_OrderIndexType)0U; orderListIndex < failRecordNum; orderListIndex++ )
    {
        eventStrgIndex  = DEM_EVENTSTRGINDEX_INVALID;
        statusOfDTC = DEM_DTCSTATUS_BYTE_ALL_OFF;
        Dem_Data_GetConfirmedOrderEventStrgIndex( orderListIndex, &eventStrgIndex, &faultIndex, &statusOfDTC, &OrderExistFlag );

        if( OrderExistFlag != (boolean)FALSE )
        {
            if( eventStrgIndex < eventStorageNum )                                                                  /* [GUD:if]eventStrgIndex */
            {
                eventOBDKind    =   Dem_CfgInfoPm_CheckEventKindOfOBD_InEvtStrgGrp( eventStrgIndex );   /* [GUD]eventStrgIndex */
                if( eventOBDKind == (boolean)TRUE ) /*  OBD     */
                {
                    /*  Confirmed DTC           */
                    if ( searchCompleteCDTC == (boolean)FALSE )
                    {
                        if( ( statusOfDTC & DEM_UDS_STATUS_CDTC ) == DEM_UDS_STATUS_CDTC )
                        {
                            isActiveCDTC            = (boolean)TRUE;
                            searchCompleteCDTC      = (boolean)TRUE;
                        }
                    }

                    if ( searchCompleteMIL == (boolean)FALSE )
                    {
                        /*  check MIL status.   */
                        /*  bit7 : ON ?             */
                        if( ( statusOfDTC & DEM_UDS_STATUS_WIR ) == DEM_UDS_STATUS_WIR )
                        {
                            /*  check Indicator type.   */
                            isMILIndicator  =   Dem_CfgInfoPm_ChkDTCCls_HasMILInd( eventStrgIndex );    /* [GUD]eventStrgIndex */
                            if( isMILIndicator == (boolean)TRUE )
                            {
                                isActiveMIL             = (boolean)TRUE;
                                searchCompleteMIL       = (boolean)TRUE;
                            }
                        }
                    }
                }
            }
        }

        if(( searchCompleteCDTC == (boolean)TRUE ) && ( searchCompleteMIL == (boolean)TRUE ))
        {
            /*  search completed.       */
            break;
        }
    }

    /*  ActiveStatus of Confirmed.          */
    if( IsActiveCDTCPtr != NULL_PTR )
    {
        *IsActiveCDTCPtr = isActiveCDTC;
    }

    /*  ActiveStatus of MIL.                */
    if( IsActiveMILPtr != NULL_PTR )
    {
        *IsActiveMILPtr = isActiveMIL;
    }
    return ;
}
#endif  /* ( DEM_PID_CALC_DEMINTERNALPID_SUPPORT == STD_ON )    */

#if ( DEM_OBD_SUPPORT == STD_ON )
#if ( DEM_WWH_OBD_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_Data_GetMILStatus_NormalEvent                        */
/* Description   | Get MIL status. without Misfire event.                   */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : MIL ON.                                   */
/*               |        FALSE  : MIL OFF.                                 */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_Data_GetNumberOfOBDDTCByDTCStatus_forPIDDataA.*/
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_Data_GetMILStatus_NormalEvent
( void )
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( boolean, AUTOMATIC ) OrderExistFlag;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) orderListIndex;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) failRecordNum;
    VAR( boolean, AUTOMATIC ) eventOBDKind;
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) eventMisfireKind;
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( boolean, AUTOMATIC ) isMILIndicator;
    VAR( boolean, AUTOMATIC ) milStatus;

    /*  count start                 */
    milStatus     = (boolean)FALSE;

    failRecordNum = (Dem_u08_OrderIndexType)Dem_FailRecordNum;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    for( orderListIndex = (Dem_u08_OrderIndexType)0U; orderListIndex < failRecordNum; orderListIndex++ )
    {
        eventStrgIndex  = DEM_EVENTSTRGINDEX_INVALID;
        statusOfDTC = DEM_DTCSTATUS_BYTE_ALL_OFF;
        Dem_Data_GetConfirmedOrderEventStrgIndex( orderListIndex, &eventStrgIndex, &faultIndex, &statusOfDTC, &OrderExistFlag );

        if( OrderExistFlag != (boolean)FALSE )
        {
            if( eventStrgIndex < eventStorageNum )                                                              /* [GUD:if]eventStrgIndex */
            {
                eventOBDKind    =   Dem_CfgInfoPm_CheckEventKindOfOBD_InEvtStrgGrp( eventStrgIndex );           /* [GUD]eventStrgIndex */
                if( eventOBDKind == (boolean)TRUE ) /*  OBD     */
                {
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                    eventMisfireKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( eventStrgIndex );    /* [GUD]eventStrgIndex */
                    if( eventMisfireKind == (boolean)FALSE )
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */
                    {
                        /*  bit7 : ON ?             */
                        if( ( statusOfDTC & DEM_UDS_STATUS_WIR ) != DEM_DTCSTATUS_BYTE_ALL_OFF )
                        {
                            /*  check Indicator type.   */
                            isMILIndicator  =   Dem_CfgInfoPm_GetIsMILIndicator( eventStrgIndex );              /* [GUD]eventStrgIndex */
                            if( isMILIndicator == (boolean)TRUE )
                            {
                                /*  WIRbit ON DTC       */
                                milStatus     = (boolean)TRUE;
                                break;      /*  end of loop.        */
                            }
                        }
                    }
                }
            }
        }
    }
    return milStatus;
}
#endif  /* ( DEM_WWH_OBD_SUPPORT == STD_OFF )       */
#endif  /* ( DEM_OBD_SUPPORT == STD_OFF )       */

/****************************************************************************/
/* Function Name | Dem_Data_GetFaultOrderEventStrgIndex                     */
/* Description   | Get EventStrgIndex from Fault OrderTable.                */
/* Preconditions | none                                                     */
/* Parameters    | [in] FaultOrderListIndex                                 */
/*               |        0 - 255 : Number of FaultOrderIndex               */
/*               | [out] EventStrgIndexPtr :                                */
/*               |        The event index which has been retrieved.         */
/*               |        This pointer is pointing to                       */
/*               |        Automatic area.                                   */
/*               |        DEM_EVENT_INDEX_INVALID : event is not available. */
/*               | [out] FaultIndexPtr :                                    */
/*               | [out] DTCStatusStPtr :                                   */
/*               |        This pointer is pointing to                       */
/*               |        Automatic area.                                   */
/*               |        StatusOfDTC value.                                */
/*               | [out] OrderExistPtr :                                    */
/*               |  TRUE  : Fault Event exists.                             */
/*               |  FALSE : Fault Event does not exists.                    */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         | if *OrderExistPtr value is TRUE and *EventStrgIndexPtr is*/
/*               | DEM_EVENT_INDEX_INVALID, Pending Event exists but that   */
/*               | event is not available.                                  */
/*               |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_GetFaultOrderEventStrgIndex
(
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) FaultOrderListIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr,
    P2VAR( Dem_u08_FaultIndexType, AUTOMATIC, AUTOMATIC ) FaultIndexPtr,
    P2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) DTCStatusStPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) OrderExistPtr
)
{
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) availableStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetFaultRegistOrderListData;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetEventStrgIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetStatusOfDTC;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_DTCStatusStType, AUTOMATIC ) dtcStatusSt;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( boolean, AUTOMATIC ) retDTCClerTarget;

    retVal = (boolean)FALSE;
    faultIndex  = DEM_FAULTINDEX_INVALID;
    eventStrgIndex  = DEM_EVENTSTRGINDEX_INVALID;
    dtcStatusSt.DTCStatus        = DEM_DTCSTATUS_BYTE_ALL_OFF;
    dtcStatusSt.ExtendDTCStatus  = DEM_DTCSTATUS_BYTE_ALL_OFF;
    dtcStatusSt.ExtendDTCStatus2 = DEM_DTCSTATUS_BYTE_ALL_OFF;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    /* Starts exclusion. */
    SchM_Enter_Dem_EventMemory();

    /*  Get FaultIndex from Comfirmed OrderList table.      */
    retGetFaultRegistOrderListData = Dem_OdrLst_Fault_GetFaultIndexByOrder( FaultOrderListIndex, &faultIndex );

    if( retGetFaultRegistOrderListData == DEM_IRT_OK )
    {
        /*  Confirmed Event exists.     */
        /*  return value is TRUE.       */
        retVal = (boolean)TRUE;

        /* Get EventStrgIndex of FaultRecord    */
        retGetEventStrgIndex = Dem_DataMngC_GetFR_EventStrgIndex( faultIndex, &eventStrgIndex );
        if( retGetEventStrgIndex == DEM_IRT_OK )
        {
            /*  check Event index.         */
            if( eventStrgIndex < eventStorageNum )                                                                  /* [GUD:if]eventStrgIndex */
            {
                retDTCClerTarget = Dem_DTC_JudgeDTCClearTarget( eventStrgIndex );
                if( retDTCClerTarget == (boolean)FALSE )
                {
                    /* Get StatusOfDTC of EventRecord   */
                    /*  eventStrgIndex range check is in Dem_DataMngC_GetEventRecord function.  */
                    retGetStatusOfDTC = Dem_DataMngC_GetER_DTCStatusSt( eventStrgIndex, &dtcStatusSt );
                }
                else
                {
                    retGetStatusOfDTC = DEM_IRT_NG;
                }

                if( retGetStatusOfDTC != DEM_IRT_OK )
                {
                    /*  eventStrgIndex is not available.    */
                    eventStrgIndex  = DEM_EVENTSTRGINDEX_INVALID;
                    dtcStatusSt.DTCStatus        = DEM_DTCSTATUS_BYTE_ALL_OFF;
                    dtcStatusSt.ExtendDTCStatus  = DEM_DTCSTATUS_BYTE_ALL_OFF;
                    dtcStatusSt.ExtendDTCStatus2 = DEM_DTCSTATUS_BYTE_ALL_OFF;
                }
            }
        }
    }

    /* Finishes exclusion. */
    SchM_Exit_Dem_EventMemory();

    /*  check Event index.         */
    if( eventStrgIndex < eventStorageNum )                                                                  /* [GUD:if]eventStrgIndex */
    {
        /*  check EventAvailable status.        */
        availableStatus = Dem_DataAvl_GetEvtAvl_InEvtStrgGrp( eventStrgIndex );
        if( availableStatus == (boolean)FALSE )
        {
            /*  eventStrgIndex is not available.    */
            eventStrgIndex  = DEM_EVENTSTRGINDEX_INVALID;
            dtcStatusSt.DTCStatus        = DEM_DTCSTATUS_BYTE_ALL_OFF;
            dtcStatusSt.ExtendDTCStatus  = DEM_DTCSTATUS_BYTE_ALL_OFF;
            dtcStatusSt.ExtendDTCStatus2 = DEM_DTCSTATUS_BYTE_ALL_OFF;
        }
    }
    /*  set EventStrgIndex          */
    *EventStrgIndexPtr  = eventStrgIndex;
    *FaultIndexPtr  = faultIndex;

    DTCStatusStPtr->DTCStatus           = dtcStatusSt.DTCStatus;
    DTCStatusStPtr->ExtendDTCStatus     = dtcStatusSt.ExtendDTCStatus;
    DTCStatusStPtr->ExtendDTCStatus2    = dtcStatusSt.ExtendDTCStatus2;

    *OrderExistPtr  = retVal;

    return ;
}

#if ( DEM_OBD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_GetPendingOrderEventStrgIndex                   */
/* Description   | Get EventStrgIndex from Fault OrderTable.                */
/* Preconditions | none                                                     */
/* Parameters    | [in] FaultOrderListIndex                                 */
/*               |        0 - 255 : Number of FaultOrderIndex               */
/*               | [out] EventStrgIndexPtr :                                */
/*               |        The event index which has been retrieved.         */
/*               |        This pointer is pointing to                       */
/*               |        Automatic area.                                   */
/*               |        DEM_EVENTSTRGINDEX_INVALID : event is not available. */
/*               | [out] FaultIndexPtr :                                    */
/*               | [out] StatusOfDTCPtr :                                   */
/*               |        This pointer is pointing to                       */
/*               |        Automatic area.                                   */
/*               |        StatusOfDTC value.                                */
/*               | [out] OrderExistPtr :                                    */
/*               |  TRUE  : Pending Event exists.                           */
/*               |  FALSE : Pending Event does not exists.                  */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         | if *OrderExistPtr value is TRUE and *EventStrgIndexPtr is*/
/*               | DEM_EVENTSTRGINDEX_INVALID, Pending Event exists but that   */
/*               | event is not available.                                  */
/*               |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_GetPendingOrderEventStrgIndex
(
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) FaultOrderListIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr,
    P2VAR( Dem_u08_FaultIndexType, AUTOMATIC, AUTOMATIC ) FaultIndexPtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) StatusOfDTCPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) OrderExistPtr
)
{
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) availableStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetFaultRegistOrderListData;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetEventStrgIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetStatusOfDTC;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( boolean, AUTOMATIC ) retDTCClerTarget;

    retVal = (boolean)FALSE;
    faultIndex  = DEM_FAULTINDEX_INVALID;
    eventStrgIndex  = DEM_EVENTSTRGINDEX_INVALID;
    statusOfDTC = DEM_DTCSTATUS_BYTE_ALL_OFF;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    /* Starts exclusion. */
    SchM_Enter_Dem_EventMemory();

    /*  Get FaultIndex from Comfirmed OrderList table.      */
    retGetFaultRegistOrderListData = Dem_OdrLst_Fault_GetFaultIndexByOrder( FaultOrderListIndex, &faultIndex );

    if( retGetFaultRegistOrderListData == DEM_IRT_OK )
    {
        /*  Confirmed Event exists.     */
        /*  return value is TRUE.       */
        retVal = (boolean)TRUE;

        /* Get EventStrgIndex of FaultRecord    */
        retGetEventStrgIndex = Dem_DataMngC_GetFR_EventStrgIndex( faultIndex, &eventStrgIndex );
        if( retGetEventStrgIndex == DEM_IRT_OK )
        {
            if( eventStrgIndex < eventStorageNum )                                                                  /* [GUD:if]eventStrgIndex */
            {
                retDTCClerTarget = Dem_DTC_JudgeDTCClearTarget( eventStrgIndex );
                if( retDTCClerTarget == (boolean)FALSE )
                {
                    /* Get StatusOfDTC of EventRecord   */
                    /*  eventStrgIndex range check is in Dem_DataMngC_GetEventRecord function.  */
                    retGetStatusOfDTC = Dem_DataMngC_GetER_StatusOfDTC( eventStrgIndex, &statusOfDTC );
                }
                else
                {
                    retGetStatusOfDTC = DEM_IRT_NG;
                }

                if( retGetStatusOfDTC != DEM_IRT_OK )
                {
                    /*  eventStrgIndex is not available.    */
                    eventStrgIndex  = DEM_EVENTSTRGINDEX_INVALID;
                    statusOfDTC = DEM_DTCSTATUS_BYTE_ALL_OFF;
                }
            }
        }
        else
        {
            /* No Process.   */
        }
    }
    else
    {
        /*  Confirmed Event does not exists.        */
        /*  return value is FALSE.                  */
        /* No Process.   */
    }

    /* Finishes exclusion. */
    SchM_Exit_Dem_EventMemory();

    /*  check Event index.         */
    if( eventStrgIndex < eventStorageNum )                                                                  /* [GUD:if]eventStrgIndex */
    {
        /*  check EventAvailable status.        */
        availableStatus = Dem_DataAvl_GetEvtAvl_InEvtStrgGrp( eventStrgIndex );
        if( availableStatus == (boolean)FALSE )
        {
            /*  eventStrgIndex is not available.    */
            eventStrgIndex  = DEM_EVENTSTRGINDEX_INVALID;
            statusOfDTC = DEM_DTCSTATUS_BYTE_ALL_OFF;
        }
        else
        {
            /*  check Pending bit.              */
            if( ( statusOfDTC & DEM_UDS_STATUS_PDTC ) == DEM_DTCSTATUS_BYTE_ALL_OFF )
            {
                /*  PendingBit is OFF. It's not covered item.    */
                eventStrgIndex  = DEM_EVENTSTRGINDEX_INVALID;
                statusOfDTC = DEM_DTCSTATUS_BYTE_ALL_OFF;
            }
        }
    }
    else
    {
        /*  No process  */
    }
    /*  set EventStrgIndex          */
    *EventStrgIndexPtr  = eventStrgIndex;
    *FaultIndexPtr  =   faultIndex;
    *StatusOfDTCPtr = statusOfDTC;
    *OrderExistPtr  =   retVal;

    return ;
}
#endif  /* ( DEM_OBD_SUPPORT == STD_ON )    */

#if ( DEM_OBD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_GetConfirmedOrderEventStrgIndex                 */
/* Description   | Get EventStrgIndex from Confirmed OrderTable.            */
/* Preconditions | none                                                     */
/* Parameters    | [in] ConfirmedOrderListIndex                             */
/*               |        0 - 255 : Number of ConfirmedOrderIndex           */
/*               | [out] EventStrgIndexPtr :                                */
/*               |        The event index which has been retrieved.         */
/*               |        This pointer is pointing to                       */
/*               |        Automatic area.                                   */
/*               |        DEM_EVENTSTRGINDEX_INVALID : event is not available. */
/*               | [out] FaultIndexPtr :                                    */
/*               | [out] StatusOfDTCPtr :                                   */
/*               |        StatusOfDTC value.                                */
/*               |        This pointer is pointing to                       */
/*               |        Automatic area.                                   */
/*               | [out] OrderExistPtr :                                    */
/*               |  TRUE  : Confirmed Event exists.                         */
/*               |  FALSE : Confirmed Event does not exists.                */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         | if *OrderExistPtr value is TRUE and *EventStrgIndexPtr is*/
/*               | DEM_EVENTSTRGINDEX_INVALID, Confirmed Event exists but that */
/*               | event is not available.                                  */
/*               |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_GetConfirmedOrderEventStrgIndex
(
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) ConfirmedOrderListIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr,
    P2VAR( Dem_u08_FaultIndexType, AUTOMATIC, AUTOMATIC ) FaultIndexPtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) StatusOfDTCPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) OrderExistPtr
)
{
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) availableStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetFaultRegistOrderListData;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetEventStrgIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetStatusOfDTC;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( boolean, AUTOMATIC ) retDTCClerTarget;

    retVal = (boolean)FALSE;
    faultIndex  = DEM_FAULTINDEX_INVALID;
    eventStrgIndex  = DEM_EVENTSTRGINDEX_INVALID;
    statusOfDTC = DEM_DTCSTATUS_BYTE_ALL_OFF;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    /* Starts exclusion. */
    SchM_Enter_Dem_EventMemory();

    /*  Get FaultIndex from Comfirmed OrderList table.      */
    retGetFaultRegistOrderListData = Dem_OdrLst_Confirmed_GetFaultIndexByOrder( ConfirmedOrderListIndex, &faultIndex );

    if( retGetFaultRegistOrderListData == DEM_IRT_OK )
    {
        /*  Confirmed Event exists.     */
        /*  return value is TRUE.       */
        retVal = (boolean)TRUE;

        /* Get EventStrgIndex of FaultRecord    */
        retGetEventStrgIndex = Dem_DataMngC_GetFR_EventStrgIndex( faultIndex, &eventStrgIndex );
        if( retGetEventStrgIndex == DEM_IRT_OK )
        {
            if( eventStrgIndex < eventStorageNum )                                                                  /* [GUD:if]eventStrgIndex */
            {
                retDTCClerTarget = Dem_DTC_JudgeDTCClearTarget( eventStrgIndex );
                if( retDTCClerTarget == (boolean)FALSE )
                {
                    /* Get StatusOfDTC of EventRecord   */
                    /*  eventStrgIndex range check is in Dem_DataMngC_GetEventRecord function.  */
                    retGetStatusOfDTC = Dem_DataMngC_GetER_StatusOfDTC( eventStrgIndex, &statusOfDTC );
                }
                else
                {
                    retGetStatusOfDTC = DEM_IRT_NG;
                }

                if( retGetStatusOfDTC != DEM_IRT_OK )
                {
                    /*  eventStrgIndex is not available.    */
                    eventStrgIndex  = DEM_EVENTSTRGINDEX_INVALID;
                    statusOfDTC = DEM_DTCSTATUS_BYTE_ALL_OFF;
                }
            }
        }
        else
        {
            /* No Process.   */
        }
    }
    else
    {
        /*  Confirmed Event does not exists.        */
        /*  return value is FALSE.                  */
        /* No Process.   */
    }

    /* Finishes exclusion. */
    SchM_Exit_Dem_EventMemory();

    /*  check Event index.         */
    if( eventStrgIndex < eventStorageNum )                                                                  /* [GUD:if]eventStrgIndex */
    {
        /*  check EventAvailable status.        */
        availableStatus = Dem_DataAvl_GetEvtAvl_InEvtStrgGrp( eventStrgIndex );
        if( availableStatus == (boolean)FALSE )
        {
            /*  eventStrgIndex is not available.    */
            eventStrgIndex  = DEM_EVENTSTRGINDEX_INVALID;
            statusOfDTC = DEM_DTCSTATUS_BYTE_ALL_OFF;
        }
        else
        {
            /*  No process  */
        }
    }
    else
    {
        /*  No process  */
    }
    /*  set EventStrgIndex          */
    *EventStrgIndexPtr  =   eventStrgIndex;
    *FaultIndexPtr  =   faultIndex;
    *StatusOfDTCPtr =   statusOfDTC;
    *OrderExistPtr  =   retVal;
    return ;
}
#endif  /* ( DEM_OBD_SUPPORT == STD_ON )    */

#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_GetMILOrderEventStrgIndex                       */
/* Description   | Get EventStrgIndex from MIL OrderTable.                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] MILOrderListIndex                                   */
/*               |        0 - 255 : Number of MILOrderIndex                 */
/*               | [out] EventStrgIndexPtr :                                */
/*               |        The event index which has been retrieved.         */
/*               |        This pointer is pointing to                       */
/*               |        Automatic area.                                   */
/*               |        DEM_EVENTSTRGINDEX_INVALID : event is not available. */
/*               | [out] StatusOfDTCPtr :                                   */
/*               |        StatusOfDTC value.                                */
/*               |        This pointer is pointing to                       */
/*               |        Automatic area.                                   */
/*               | [out] OrderExistPtr :                                    */
/*               |  TRUE  : MIL Event exists.                               */
/*               |  FALSE : MIL Event does not exists.                      */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         | if *OrderExistPtr value is TRUE and *EventStrgIndexPtr is*/
/*               | DEM_EVENTSTRGINDEX_INVALID, MIL Event exists but that       */
/*               | event is not available.                                  */
/*               |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_GetMILOrderEventStrgIndex
(
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) MILOrderListIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) StatusOfDTCPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) OrderExistPtr
)
{
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) availableStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetFaultRegistOrderListData;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetEventStrgIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetStatusOfDTC;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;

    retVal = (boolean)FALSE;
    faultIndex  = (Dem_u08_FaultIndexType)0U;
    eventStrgIndex  = DEM_EVENTSTRGINDEX_INVALID;
    statusOfDTC = DEM_DTCSTATUS_BYTE_ALL_OFF;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    /* Starts exclusion. */
    SchM_Enter_Dem_EventMemory();

    /*  Get FaultIndex from MIL OrderList table.      */
    retGetFaultRegistOrderListData = Dem_OdrLst_MIL_GetFaultIndexByOrder( MILOrderListIndex, &faultIndex );

    if( retGetFaultRegistOrderListData == DEM_IRT_OK )
    {
        /*  MIL Event exists. */
        /*  return value is TRUE.       */
        retVal = (boolean)TRUE;

        /* Get EventStrgIndex of FaultRecord    */
        retGetEventStrgIndex = Dem_DataMngC_GetFR_EventStrgIndex( faultIndex, &eventStrgIndex );
        if( retGetEventStrgIndex == DEM_IRT_OK )
        {
            /* Get StatusOfDTC of EventRecord   */
            /*  eventStrgIndex range check is in Dem_DataMngC_GetEventRecord function.  */
            retGetStatusOfDTC = Dem_DataMngC_GetER_StatusOfDTC( eventStrgIndex, &statusOfDTC );
            if( retGetStatusOfDTC != DEM_IRT_OK )
            {
                /*  eventStrgIndex is not available.    */
                eventStrgIndex  = DEM_EVENTSTRGINDEX_INVALID;
                statusOfDTC = DEM_DTCSTATUS_BYTE_ALL_OFF;
            }
        }
        else
        {
            /* No Process.   */
        }
    }
    else
    {
        /*  MIL Event does not exists. */
        /*  return value is FALSE. */
        /* No Process.   */
    }

    /* Finishes exclusion. */
    SchM_Exit_Dem_EventMemory();

    /*  check Event index.         */
    if( eventStrgIndex < eventStorageNum )                                                                  /* [GUD:if]eventStrgIndex */
    {
        /*  check EventAvailable status.        */
        availableStatus = Dem_DataAvl_GetEvtAvl_InEvtStrgGrp( eventStrgIndex );
        if( availableStatus == (boolean)FALSE )
        {
            /*  eventStrgIndex is not available.    */
            eventStrgIndex  = DEM_EVENTSTRGINDEX_INVALID;
            statusOfDTC = DEM_DTCSTATUS_BYTE_ALL_OFF;
        }
        else
        {
            /*  No process  */
        }
    }
    else
    {
        /*  No process  */
    }
    /*  set EventStrgIndex          */
    *EventStrgIndexPtr  = eventStrgIndex;
    *StatusOfDTCPtr = statusOfDTC;
    *OrderExistPtr   =   retVal;
    return ;
}
#endif /* (DEM_PFC_ORDER_MIL_SUPPORT == STD_ON ) */

#if ( DEM_PID_SUPPORT == STD_ON )
#if ( DEM_WWH_OBD_SUPPORT == STD_OFF )
#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )
#if ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_CheckCountableConfirmedDTC                      */
/* Description   | Check countable DTC for not.                             */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex  :   EventStrgIndex.                 */
/* Parameters    | [in] EndOfSearchOrderListIndex                           */
/*               |        0 - 255 : Number of ConfirmedOrderIndex           */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : counting OK.                              */
/*               |        FALSE : counting NG.(already counted.)            */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_Data_CheckCountableConfirmedDTC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,            /* [PRMCHK:CALLER] */
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) EndOfSearchOrderListIndex
)
{
    VAR( Dem_u16_ObdDTCValueType, AUTOMATIC ) obdDTCValueTarget;
    VAR( Dem_u16_ObdDTCValueType, AUTOMATIC ) obdDTCValueOutput;

    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndexOutput;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) orderListIndex;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetOrderListData;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetEventStrgIndex;
    VAR( boolean, AUTOMATIC ) availableStatus;
    VAR( boolean, AUTOMATIC ) eventOBDKind;
    VAR( boolean, AUTOMATIC ) retVal;


    /*  get target DTC value.       */
    obdDTCValueTarget =   Dem_CfgInfoPm_GetObdDTCValue( EventStrgIndex );   /* [GUDCHK:CALLER]EventStrgIndex */

    /*  initialize : countable(TRUE).   */
    retVal = (boolean)TRUE;

    for( orderListIndex = (Dem_u08_OrderIndexType)0U; orderListIndex < EndOfSearchOrderListIndex; orderListIndex++ )
    {
        /*  Get FaultIndex from Comfirmed OrderList table.      */
        faultIndex  = DEM_FAULTINDEX_INVALID;
        retGetOrderListData = Dem_OdrLst_Confirmed_GetFaultIndexByOrder( orderListIndex, &faultIndex );

        if( retGetOrderListData == DEM_IRT_OK )
        {
            /* Get EventStrgIndex of FaultRecord    */
            eventStrgIndexOutput = DEM_EVENTSTRGINDEX_INVALID;
            retGetEventStrgIndex = Dem_DataMngC_GetFR_EventStrgIndex( faultIndex, &eventStrgIndexOutput );  /* [GUD:RET:DEM_IRT_OK] eventStrgIndexOutput */
            if( retGetEventStrgIndex == DEM_IRT_OK )
            {
                /*  eventStrgIndexOutput range is checked in Dem_DataMngC_GetFR_EventStrgIndex.     */

                eventOBDKind    =   Dem_CfgInfoPm_CheckEventKindOfOBD_InEvtStrgGrp( eventStrgIndexOutput ); /* [GUD]eventStrgIndexOutput */
                if( eventOBDKind == (boolean)TRUE ) /*  OBD     */
                {
                    /*  check EventAvailable status.        */
                    availableStatus = Dem_DataAvl_GetEvtAvl_InEvtStrgGrp( eventStrgIndexOutput );           /* [GUD]eventStrgIndexOutput */
                    if( availableStatus == (boolean)TRUE )
                    {
                        /*  get output DTC value.           */
                        obdDTCValueOutput =   Dem_CfgInfoPm_GetObdDTCValue( eventStrgIndexOutput );         /* [GUD]eventStrgIndexOutput */

                        if ( obdDTCValueTarget == obdDTCValueOutput )
                        {
                            /*  output already. not countable.          */
                            retVal = (boolean)FALSE;
                            break;
                        }
                    }
                }
            }
        }
    }
    return retVal;
}
#endif  /*   ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )                       */

#if ( DEM_OBDDTC_FORMAT_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_Data_CheckCountableConfirmedDTC                      */
/* Description   | Check countable DTC for not.                             */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex  :   EventStrgIndex.                 */
/* Parameters    | [in] EndOfSearchOrderListIndex                           */
/*               |        0 - 255 : Number of ConfirmedOrderIndex           */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : counting OK.                              */
/*               |        FALSE : counting NG.(already counted.)            */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_Data_CheckCountableConfirmedDTC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) EndOfSearchOrderListIndex
)
{
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) udsDTCValueTarget;
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) udsDTCValueOutput;

    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) numberOfEventStrgIndexInDTC;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndexOutput;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) orderListIndex;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetOrderListData;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetEventStrgIndex;
    VAR( boolean, AUTOMATIC ) availableStatus;
    VAR( boolean, AUTOMATIC ) eventOBDKind;
    VAR( boolean, AUTOMATIC ) retVal;

    /*  initialize : countable(TRUE).   */
    retVal = (boolean)TRUE;

    /*  check number of events that has same DTC.       */
    numberOfEventStrgIndexInDTC =   Dem_CmbEvt_NumOfEventStrgIndex_InDTCGrp( EventStrgIndex );

    if ( numberOfEventStrgIndexInDTC == (Dem_u16_EventStrgIndexType)0U )
    {
        retVal = (boolean)FALSE;
    }
    else if ( numberOfEventStrgIndexInDTC == (Dem_u16_EventStrgIndexType)1U )
    {
        /*  no process. return TRUE.    */
    }
    else
    {
        /*  get target DTC value.       */
        udsDTCValueTarget =   Dem_CfgInfoPm_GetUdsDTCValue( EventStrgIndex );   /* [GUDCHK:CALLER]EventStrgIndex */

        for( orderListIndex = (Dem_u08_OrderIndexType)0U; orderListIndex < EndOfSearchOrderListIndex; orderListIndex++ )
        {
            /*  Get FaultIndex from Comfirmed OrderList table.      */
            faultIndex  = DEM_FAULTINDEX_INVALID;
            retGetOrderListData = Dem_OdrLst_Confirmed_GetFaultIndexByOrder( orderListIndex, &faultIndex );

            if( retGetOrderListData == DEM_IRT_OK )
            {
                /* Get EventStrgIndex of FaultRecord    */
                eventStrgIndexOutput = DEM_EVENTSTRGINDEX_INVALID;
                retGetEventStrgIndex = Dem_DataMngC_GetFR_EventStrgIndex( faultIndex, &eventStrgIndexOutput );  /* [GUD:RET:DEM_IRT_OK] eventStrgIndexOutput */
                if( retGetEventStrgIndex == DEM_IRT_OK )
                {
                    /*  eventStrgIndexOutput range is checked in Dem_DataMngC_GetFR_EventStrgIndex.     */

                    eventOBDKind    =   Dem_CfgInfoPm_CheckEventKindOfOBD_InEvtStrgGrp( eventStrgIndexOutput );     /* [GUD]eventStrgIndexOutput */
                    if( eventOBDKind == (boolean)TRUE ) /*  OBD     */
                    {
                        /*  check EventAvailable status.        */
                        availableStatus = Dem_DataAvl_GetEvtAvl_InEvtStrgGrp( eventStrgIndexOutput );               /* [GUD]eventStrgIndexOutput */
                        if( availableStatus == (boolean)TRUE )
                        {
                            /*  get output DTC value.           */
                            udsDTCValueOutput =   Dem_CfgInfoPm_GetUdsDTCValue( eventStrgIndexOutput );             /* [GUD]eventStrgIndexOutput */

                            if ( udsDTCValueTarget == udsDTCValueOutput )
                            {
                                /*  output already. not countable.          */
                                retVal = (boolean)FALSE;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    return retVal;
}
#endif  /*   ( DEM_OBDDTC_FORMAT_SUPPORT == STD_OFF )                       */

#endif  /*  ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )     */
#endif  /* ( DEM_WWH_OBD_SUPPORT == STD_OFF )   */
#endif  /* ( DEM_PID_SUPPORT == STD_ON )    */

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
/*  v5-7-0         :2024-05-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
