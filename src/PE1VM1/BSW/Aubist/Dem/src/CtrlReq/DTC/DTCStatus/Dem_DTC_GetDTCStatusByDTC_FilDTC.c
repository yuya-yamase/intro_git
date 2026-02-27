/* Dem_DTC_GetDTCStatusByDTC_FilDTC_c(v5-7-0)                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DTC_GetDTCStatusByDTC_FilDTC/CODE                     */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem/Dem_Common.h>
#include "../../../../cfg/Dem_Cfg.h"
#include "../../../../cfg/Dem_Data_Cfg.h"
#include "../../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../../inc/Dem_CmnLib_DTC_DTCStatus.h"
#include "../../../../inc/Dem_CmnLib_DTC_FilDTC.h"
#include "../../../../inc/Dem_Pm_DataAvl.h"
#include "../../../../inc/Dem_Pm_DTC.h"
#include "../../../../inc/Dem_Pm_Ind.h"
#include "../../../../inc/Dem_Rc_DataMng.h"

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

#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_FILDTC_SUPPORT == STD_ON )
static FUNC( Dem_UdsStatusByteType, DEM_CODE ) Dem_DTC_CnvRtvlDTCStatusFromMergedDTCStatus
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) MergeOfDTCStatus
);
static FUNC( Dem_DTCSeverityType, DEM_CODE ) Dem_DTC_GetTargetDTCClassFromMergedDTCClass
(
    VAR( Dem_DTCSeverityType, AUTOMATIC ) MergeOfDTCClass
);
#endif  /* ( DEM_COMBINEDEVENT_ONRETRIEVAL_FILDTC_SUPPORT == STD_ON )   */
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_GetDTCStatusByDTCAndSeverity_ByTargetEvent
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) TargetEventStrgIndex,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusMask,
    VAR( boolean, AUTOMATIC ) FilterWithSeverity,
    VAR( Dem_DTCSeverityType, AUTOMATIC ) DTCSeverityMask,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr,
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, AUTOMATIC ) DTCSeverityPtr
);
static FUNC( Dem_UdsStatusByteType, DEM_CODE ) Dem_DTC_GetTargetDTCStatusWithWIRStatus
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) TargetEventStrgIndex
);
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_CheckAndGetTargetDTCSeverityBySeverityMask
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) TargetEventStrgIndex,
    VAR( boolean, AUTOMATIC ) FilterWithSeverity,
    VAR( Dem_DTCSeverityType, AUTOMATIC ) DTCSeverityMask,
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, AUTOMATIC ) DTCSeverityPtr
);
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_CheckAndGetTargetDTCStatusByDTCStatusMask
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) TargetEventStrgIndex,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusMask,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
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
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_FILDTC_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DTC_GetDTCStatusByDTCAndSeverity                     */
/* Description   | Gets the UDS DTC status byte corresponding to specified  */
/*               |  event ID.                                               */
/* Preconditions | The specified event index corresponding to the event ID  */
/*               |  has been already retrieved.                             */
/* Parameters    | [in] TargetEventStrgIndex :                              */
/*               |        The event index corresponding to the event ID.    */
/*               | [in] DTCStatusMask :                                     */
/*               |        DTCStatusMask.                                    */
/*               | [in] FilterWithSeverity :                                */
/*               |        FilterWithSeverity.                               */
/*               | [in] DTCSeverityMask :                                   */
/*               |        Severity mask.                                    */
/*               | [out] DTCStatusPtr :                                     */
/*               |        The UDS DTC status byte which has been retrieved- */
/*               |        .                                                 */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : The UDS DTC status byte retrieving - */
/*               |        is successful.                                    */
/*               |        DEM_IRT_NG : The UDS DTC status byte retrieving - */
/*               |        is failed.                                        */
/* Notes         | WIRStatus is merge in this function.                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.based on Dem_DTC_GetDTCStatusByDTC.          */
/*   v5-7-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_GetDTCStatusByDTCAndSeverity
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) TargetEventStrgIndex,              /* [PRMCHK:CALLER] */
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusMask,
    VAR( boolean, AUTOMATIC ) FilterWithSeverity,
    VAR( Dem_DTCSeverityType, AUTOMATIC ) DTCSeverityMask,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr,
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, AUTOMATIC ) DTCSeverityPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retValMergeDTC;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCheckDTCStatusMask;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCheckDTCSeverityMask;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) tempStatusOfDTC;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndexNum;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndexCnt;
    VAR( Dem_DTCSeverityType, AUTOMATIC ) dtcClassByEventStrgIndex;
    VAR( Dem_DTCSeverityType, AUTOMATIC ) dtcClassAtDTCAll;
    VAR( Dem_DTCSeverityType, AUTOMATIC ) dtcClassAtDTCTgt;
    VAR( boolean, AUTOMATIC ) eventAvailableDef;
    VAR( boolean, AUTOMATIC ) retDTCClearTarget;

    /* Set initial value. */
    retVal = DEM_IRT_NG;

    /* set target event. */
    eventStrgIndex      =   TargetEventStrgIndex;                                       /* [GUDCHK:CALLER]TargetEventStrgIndex */

    /* get num of event index in DTC group. */
    eventStrgIndexNum = Dem_CmbEvt_NumOfEventStrgIndex_InDTCGrp( eventStrgIndex );      /* [GUDCHK:CALLER]TargetEventStrgIndex */

    if ( eventStrgIndexNum == (Dem_u16_EventStrgIndexType)1U )
    {
        /*  get DTCStatus and DTCClass by eventStrgIndex.       */
        retVal  =   Dem_DTC_GetDTCStatusByDTCAndSeverity_ByTargetEvent( eventStrgIndex, DTCStatusMask, FilterWithSeverity, DTCSeverityMask, &statusOfDTC, &dtcClassAtDTCTgt );
    }
    else
    {
        retValMergeDTC  = DEM_IRT_NG;

        statusOfDTC  = DEM_DTCSTATUS_BYTE_ALL_OFF;

        dtcClassAtDTCAll    =   DEM_SEVERITY_NO_SEVERITY;
        dtcClassAtDTCTgt    =   DEM_SEVERITY_NO_SEVERITY;

        /*  get clearDTC target or not.     */
        retDTCClearTarget = Dem_DTC_JudgeDTCClearTarget( eventStrgIndex );                  /* [GUDCHK:CALLER]TargetEventStrgIndex */

        for( eventStrgIndexCnt = ( Dem_u16_EventStrgIndexType )0U; eventStrgIndexCnt < eventStrgIndexNum; eventStrgIndexCnt++ )
        {
            /* Check available status. */
            eventAvailableDef = Dem_DataAvl_GetEvtAvl_InEvtStrgGrp( eventStrgIndex );                                       /* [GUDCHK:CALLER]TargetEventStrgIndex */
            if( eventAvailableDef == (boolean)TRUE )
            {
                /*----------------------------------*/
                /*  Check and Get Severity.         */
                /*----------------------------------*/
                retCheckDTCSeverityMask  = Dem_DTC_CheckAndGetTargetDTCSeverityBySeverityMask( eventStrgIndex, FilterWithSeverity, DTCSeverityMask, &dtcClassByEventStrgIndex );    /* [GUDCHK:CALLER]TargetEventStrgIndex */

                if ( retCheckDTCSeverityMask == DEM_IRT_OK )
                {
                    /*----------------------------------------------*/
                    /*  SeverityMask is OK.                         */
                    /*----------------------------------------------*/
                    /*  Get statusOfDTC.                            */
                    /*----------------------------------------------*/
                    if( retDTCClearTarget == (boolean)FALSE )
                    {
                        /*--------------------------------------*/
                        /*  get target statusOfDTC.             */
                        /*--------------------------------------*/
                        tempStatusOfDTC   =   Dem_DTC_GetTargetDTCStatusWithWIRStatus( eventStrgIndex );
                    }
                    else
                    {
                        /*--------------------------------------*/
                        /*  get default statusOfDTC.            */
                        /*--------------------------------------*/
                        tempStatusOfDTC =   DEM_DTCSTATUS_BYTE_DEFAULT;
                    }

                    /* Merge StatusOfDTC */
                    statusOfDTC    = ( statusOfDTC    | tempStatusOfDTC );

                    dtcClassAtDTCAll  = ( dtcClassAtDTCAll  | dtcClassByEventStrgIndex );

                    retValMergeDTC = DEM_IRT_OK;
                }
            }

            /* get next event index. */
            eventStrgIndex = Dem_CmbEvt_GetNextEventStrgIndex_InDTCGrp( eventStrgIndex );       /* [GUDCHK:CALLER]TargetEventStrgIndex */
        }

        /* Checks the result of retrieving the event record. */
        if( retValMergeDTC == DEM_IRT_OK )
        {
            /* Retrieving the event record is successful. */

            /*  convert DTCStatus from merged status.   */
            statusOfDTC         =   Dem_DTC_CnvRtvlDTCStatusFromMergedDTCStatus( statusOfDTC );

            /*  get DTCClass from merged DTCClass.      */
            dtcClassAtDTCTgt    =   Dem_DTC_GetTargetDTCClassFromMergedDTCClass( dtcClassAtDTCAll );

            /*----------------------------------------------*/
            /*  Check and Get DTCStatusMask.                */
            /*----------------------------------------------*/
            retCheckDTCStatusMask   =   Dem_DTC_CheckAndGetTargetDTCStatusByDTCStatusMask( eventStrgIndex, DTCStatusMask, &statusOfDTC );

            if ( retCheckDTCStatusMask == DEM_IRT_OK )
            {
                /*----------------------------------*/
                /*  DTCStatusMask is OK.            */
                /*----------------------------------*/
                retVal  =   DEM_IRT_OK;
            }
        }
        else
        {
            statusOfDTC = DEM_DTCSTATUS_BYTE_DEFAULT;
        }
    }
    /* Stores StatusOfDTC of the event memory entry of temporary area to the specified parameter. */
    *DTCStatusPtr    = statusOfDTC;
    *DTCSeverityPtr  = dtcClassAtDTCTgt;

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DTC_CnvRtvlDTCStatusFromMergedDTCStatus              */
/* Description   | get DTCStatus from merged status.                        */
/* Preconditions |                                                          */
/* Parameters    | [in] MergeOfDTCStatus : merged DTCStatus.                */
/*               |                                                          */
/* Return Value  | Dem_UdsStatusByteType  :   convert DTCStatus.            */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-7-0      | new created.                                             */
/****************************************************************************/
static FUNC( Dem_UdsStatusByteType, DEM_CODE ) Dem_DTC_CnvRtvlDTCStatusFromMergedDTCStatus
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) MergeOfDTCStatus
)
{
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC;

    statusOfDTC =   MergeOfDTCStatus;

    /* Bit4 is set as below. */
    /* (Event[1].bit4 OR Event[2].bit4 OR ... OR  Event[n].bit4) AND NOT(Event[1].bit5 OR Event[2].bit5 OR ... OR  Event[n].bit5) */
    /* So Check Bit5. Bit5 is on, set Bit4 to 0. */
    if( ( statusOfDTC & DEM_UDS_STATUS_TFSLC ) == DEM_UDS_STATUS_TFSLC )
    {
        statusOfDTC = ( statusOfDTC & ~DEM_UDS_STATUS_TNCSLC );
    }

    /* Bit6 is set as below. */
    /* (Event[1].bit6 OR Event[2].bit6 OR ... OR  Event[n].bit6) AND NOT(Event[1].bit1 OR Event[2].bit1 OR ... OR  Event[n].bit1) */
    /* So Check Bit1. Bit1 is on, set Bit6 to 0. */
    if( ( statusOfDTC & DEM_UDS_STATUS_TFTOC ) == DEM_UDS_STATUS_TFTOC )
    {
        statusOfDTC = ( statusOfDTC & ~DEM_UDS_STATUS_TNCTOC );
    }

    return statusOfDTC;
}


/****************************************************************************/
/* Function Name | Dem_DTC_GetTargetDTCClassFromMergedDTCClass              */
/* Description   | get target DTCClass from merged class.                   */
/* Preconditions |                                                          */
/* Parameters    | [in] MergeOfDTCClass : merged DTCClass.                  */
/*               |                                                          */
/* Return Value  | Dem_DTCSeverityType  :   target DTCClass.                */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-7-0      | new created.                                             */
/****************************************************************************/
static FUNC( Dem_DTCSeverityType, DEM_CODE ) Dem_DTC_GetTargetDTCClassFromMergedDTCClass
(
    VAR( Dem_DTCSeverityType, AUTOMATIC ) MergeOfDTCClass
)
{
    VAR( Dem_DTCSeverityType, AUTOMATIC ) dtcClassAtDTCTgt;

    dtcClassAtDTCTgt    =   DEM_SEVERITY_NO_SEVERITY;

    /*------------------------------------------*/
    /*  DTCClass priority   :                   */
    /*      DEM_DTC_CLASS_1(0x02)               */
    /*      > DEM_DTC_CLASS_2(0x04)             */
    /*      > DEM_DTC_CLASS_3(0x08)             */
    /*      > DEM_DTC_CLASS_4(0x10)             */
    /*      > DEM_DTC_CLASS_0(0x01)             */
    /*      > DEM_SEVERITY_NO_SEVERITY(0x00)    */
    /*------------------------------------------*/
    if (( MergeOfDTCClass & DEM_DTC_CLASS_1 ) == DEM_DTC_CLASS_1 )
    {
        dtcClassAtDTCTgt    =   DEM_DTC_CLASS_1;
    }
    else if (( MergeOfDTCClass & DEM_DTC_CLASS_2 ) == DEM_DTC_CLASS_2 )
    {
        dtcClassAtDTCTgt    =   DEM_DTC_CLASS_2;
    }
    else if (( MergeOfDTCClass & DEM_DTC_CLASS_3 ) == DEM_DTC_CLASS_3 )
    {
        dtcClassAtDTCTgt    =   DEM_DTC_CLASS_3;
    }
    else if (( MergeOfDTCClass & DEM_DTC_CLASS_4 ) == DEM_DTC_CLASS_4 )
    {
        dtcClassAtDTCTgt    =   DEM_DTC_CLASS_4;
    }
    else if (( MergeOfDTCClass & DEM_DTC_CLASS_0 ) == DEM_DTC_CLASS_0 )
    {
        dtcClassAtDTCTgt    =   DEM_DTC_CLASS_0;
    }
    else
    {
        /*  DEM_SEVERITY_NO_SEVERITY        */
    }
    return dtcClassAtDTCTgt;
}

#endif  /*   ( DEM_COMBINEDEVENT_ONRETRIEVAL_FILDTC_SUPPORT == STD_ON )     */

#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_FILDTC_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_DTC_GetDTCStatusByDTCAndSeverity                     */
/* Description   | Gets the UDS DTC status byte corresponding to specified  */
/*               |  event ID.                                               */
/* Preconditions | The specified event index corresponding to the event ID  */
/*               |  has been already retrieved.                             */
/* Parameters    | [in] TargetEventStrgIndex :                              */
/*               |        The event index corresponding to the event ID.    */
/*               | [in] DTCStatusMask :                                     */
/*               |        DTCStatusMask.                                    */
/*               | [in] FilterWithSeverity :                                */
/*               |        FilterWithSeverity.                               */
/*               | [in] DTCSeverityMask :                                   */
/*               |        Severity mask.                                    */
/*               | [out] DTCStatusPtr :                                     */
/*               |        The DTC status byte which has been retrieved.     */
/*               | [out] DTCSeverityPtr :                                   */
/*               |        Severity information.                             */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : The UDS DTC status byte retrieving - */
/*               |        is successful.                                    */
/*               |        DEM_IRT_NG : The UDS DTC status byte retrieving - */
/*               |        is failed.                                        */
/* Notes         | WIRStatus is merge in this function.                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-7-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_GetDTCStatusByDTCAndSeverity
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) TargetEventStrgIndex,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusMask,
    VAR( boolean, AUTOMATIC ) FilterWithSeverity,
    VAR( Dem_DTCSeverityType, AUTOMATIC ) DTCSeverityMask,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr,
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, AUTOMATIC ) DTCSeverityPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal  =   Dem_DTC_GetDTCStatusByDTCAndSeverity_ByTargetEvent( TargetEventStrgIndex, DTCStatusMask, FilterWithSeverity, DTCSeverityMask, DTCStatusPtr, DTCSeverityPtr );

    return retVal;
}
#endif  /*   ( DEM_COMBINEDEVENT_ONRETRIEVAL_FILDTC_SUPPORT == STD_OFF )     */

/****************************************************************************/
/* Function Name | Dem_DTC_GetDTCStatusByDTCAndSeverity_ByTargetEvent       */
/* Description   | Gets the UDS DTC status byte corresponding to specified  */
/*               |  event ID.                                               */
/* Preconditions | The specified event index corresponding to the event ID  */
/*               |  has been already retrieved.                             */
/* Parameters    | [in] TargetEventStrgIndex :                              */
/*               |        The event index corresponding to the event ID.    */
/*               | [in] DTCStatusMask :                                     */
/*               |        DTCStatusMask.                                    */
/*               | [in] FilterWithSeverity :                                */
/*               |        FilterWithSeverity.                               */
/*               | [in] DTCSeverityMask :                                   */
/*               |        Severity mask.                                    */
/*               | [out] DTCStatusPtr :                                     */
/*               |        The DTC status byte which has been retrieved.     */
/*               | [out] DTCSeverityPtr :                                   */
/*               |        Severity information.                             */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : The UDS DTC status byte retrieving - */
/*               |        is successful.                                    */
/*               |        DEM_IRT_NG : The UDS DTC status byte retrieving - */
/*               |        is failed.                                        */
/* Notes         | WIRStatus is merge in this function.                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.based on Dem_DTC_GetDTCStatusByDTC.          */
/*   v5-7-0      | rename from Dem_DTC_GetDTCStatusByDTCAndSeverity(at DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_OFF). */
/*   v5-7-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_GetDTCStatusByDTCAndSeverity_ByTargetEvent
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) TargetEventStrgIndex,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusMask,
    VAR( boolean, AUTOMATIC ) FilterWithSeverity,
    VAR( Dem_DTCSeverityType, AUTOMATIC ) DTCSeverityMask,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr,
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, AUTOMATIC ) DTCSeverityPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCheckDTCStatusMask;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCheckDTCSeverityMask;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC;
    VAR( Dem_DTCSeverityType, AUTOMATIC ) dtcClassAtDTCTgt;
    VAR( boolean, AUTOMATIC ) eventAvailableDef;
    VAR( boolean, AUTOMATIC ) retDTCClearTarget;

    retVal = DEM_IRT_NG;
    dtcClassAtDTCTgt    =   DEM_SEVERITY_NO_SEVERITY;

    /*  check event available.      */
    eventAvailableDef = Dem_DataAvl_GetEvtAvl_InEvtStrgGrp( TargetEventStrgIndex );
    if( eventAvailableDef == (boolean)TRUE )
    {
        /*----------------------------------*/
        /*  Check and Get Severity.         */
        /*----------------------------------*/
        retCheckDTCSeverityMask  =   Dem_DTC_CheckAndGetTargetDTCSeverityBySeverityMask( TargetEventStrgIndex, FilterWithSeverity, DTCSeverityMask, &dtcClassAtDTCTgt );
        if ( retCheckDTCSeverityMask == DEM_IRT_OK )
        {
            /*----------------------------------------------*/
            /*  SeverityMask is OK.                         */
            /*----------------------------------------------*/
            /*  Get statusOfDTC.                            */
            /*----------------------------------------------*/
            /*  get clearDTC target or not.     */
            retDTCClearTarget = Dem_DTC_JudgeDTCClearTarget( TargetEventStrgIndex );    /* [GUDCHK:CALLER]TargetEventStrgIndex */

            if( retDTCClearTarget == (boolean)FALSE )
            {
                /*--------------------------------------*/
                /*  get target statusOfDTC.             */
                /*--------------------------------------*/
                statusOfDTC     =   Dem_DTC_GetTargetDTCStatusWithWIRStatus( TargetEventStrgIndex );
            }
            else
            {
                /*--------------------------------------*/
                /*  get default statusOfDTC.            */
                /*--------------------------------------*/
                statusOfDTC     =   DEM_DTCSTATUS_BYTE_DEFAULT;
            }

            /*----------------------------------------------*/
            /*  Check and Get DTCStatusMask.                */
            /*----------------------------------------------*/
            retCheckDTCStatusMask   =   Dem_DTC_CheckAndGetTargetDTCStatusByDTCStatusMask( TargetEventStrgIndex, DTCStatusMask, &statusOfDTC );

            if ( retCheckDTCStatusMask == DEM_IRT_OK )
            {
                /*----------------------------------*/
                /*  DTCStatusMask is OK.            */
                /*----------------------------------*/
                retVal  =   DEM_IRT_OK;
            }
        }
    }

    if( retVal != DEM_IRT_OK )
    {
        statusOfDTC         = DEM_DTCSTATUS_BYTE_DEFAULT;
        dtcClassAtDTCTgt    = DEM_SEVERITY_NO_SEVERITY;
    }

    *DTCStatusPtr    = statusOfDTC;
    *DTCSeverityPtr  = dtcClassAtDTCTgt;

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DTC_GetTargetDTCStatusWithWIRStatus                  */
/* Description   | Get statusOfDTC with WIR status.                         */
/* Preconditions | The specified event index corresponding to the event ID  */
/*               |  has been already retrieved.                             */
/* Parameters    | [in] TargetEventStrgIndex :                              */
/*               |        The event index corresponding to the event ID.    */
/*               |                                                          */
/* Return Value  | Dem_UdsStatusByteType                                    */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-7-0      | new created.                                             */
/****************************************************************************/
static FUNC( Dem_UdsStatusByteType, DEM_CODE ) Dem_DTC_GetTargetDTCStatusWithWIRStatus
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) TargetEventStrgIndex
)
{
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC;
    VAR( boolean, AUTOMATIC ) wirStatus;

    /*----------------------------------*/
    /*  get statusOfDTC.                */
    /*----------------------------------*/
    (void)Dem_DataMngC_GetER_StatusOfDTC( TargetEventStrgIndex, &statusOfDTC );   /* no return check required */   /* [GUDCHK:CALLER]TargetEventStrgIndex */

    wirStatus   =   (boolean)FALSE;
    (void)Dem_Ind_GetWIRStatus( TargetEventStrgIndex, &wirStatus );                   /* no return check required */
    if ( wirStatus == (boolean)TRUE )
    {
        /*  set bit7.                    */
        statusOfDTC = Dem_DTC_SetWIRStatusBit( statusOfDTC );
    }
    return statusOfDTC;
}

/****************************************************************************/
/* Function Name | Dem_DTC_CheckAndGetTargetDTCSeverityBySeverityMask       */
/* Description   | Get DTCClass by SeverityMask.                            */
/* Preconditions | The specified event index corresponding to the event ID  */
/*               |  has been already retrieved.                             */
/* Parameters    | [in] TargetEventStrgIndex :                              */
/*               |        The event index corresponding to the event ID.    */
/*               | [in] FilterWithSeverity :                                */
/*               |        FilterWithSeverity.                               */
/*               | [in] DTCSeverityMask :                                   */
/*               |        Severity mask.                                    */
/*               | [out] DTCSeverityPtr :                                   */
/*               |        Severity                                          */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : target of DTC by DTCSeverityMask.    */
/*               |        DEM_IRT_NG : no target of DTC.                    */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-7-0      | new created.                                             */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_CheckAndGetTargetDTCSeverityBySeverityMask
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) TargetEventStrgIndex,
    VAR( boolean, AUTOMATIC ) FilterWithSeverity,
    VAR( Dem_DTCSeverityType, AUTOMATIC ) DTCSeverityMask,
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, AUTOMATIC ) DTCSeverityPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCheckDTCSeverityMask;
    VAR( Dem_DTCSeverityType, AUTOMATIC ) severity;

    retVal = DEM_IRT_NG;

    /*----------------------------------*/
    /*  get severity                    */
    /*----------------------------------*/
    severity     =   Dem_CfgInfoPm_GetDTCSeverityClass( TargetEventStrgIndex );                               /* [GUDCHK:CALLER]TargetEventStrgIndex */

    if ( FilterWithSeverity == (boolean)TRUE )
    {
        /*  target DTC class or not.        */
        retCheckDTCSeverityMask =   Dem_DTC_CheckDTCSeverityForFilter( DTCSeverityMask, &severity );
        if( retCheckDTCSeverityMask == DEM_IRT_OK )
        {
            retVal = DEM_IRT_OK;
        }
    }
    else
    {
        retVal = DEM_IRT_OK;
    }

    if ( retVal != DEM_IRT_OK )
    {
        severity    =   DEM_SEVERITY_NO_SEVERITY;
    }

    *DTCSeverityPtr =   severity;

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DTC_CheckAndGetTargetDTCStatusByDTCStatusMask        */
/* Description   | Check statusOfDTC by DTCStatusMask.                      */
/* Preconditions | The specified event index corresponding to the event ID  */
/*               |  has been already retrieved.                             */
/* Parameters    | [in] TargetEventStrgIndex :                              */
/*               |        The event index corresponding to the event ID.    */
/*               | [in] DTCStatusMask :                                     */
/*               |        DTCStatusMask.                                    */
/*               | [in/out] DTCStatusPtr :                                  */
/*               |        The UDS DTC status byte which has been retrieved. */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : target of DTC by DTCStatusMask.      */
/*               |        DEM_IRT_NG : no target of DTC.                    */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-7-0      | new created.                                             */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_CheckAndGetTargetDTCStatusByDTCStatusMask
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) TargetEventStrgIndex,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusMask,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCheckDTCStatusMask;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC;

    /*  latch statusOfDTC.                      */
    statusOfDTC =   *DTCStatusPtr;

    /*------------------------------------------*/
    /*  convert to output statusOfDTC.          */
    /*------------------------------------------*/
    Dem_DTC_TranslateDTCStatusForOutput_NoMergeWIRBit( TargetEventStrgIndex, &statusOfDTC );      /* [GUD]EventStrgIndex */

    /*------------------------------------------*/
    /*  mask statusOfDTC by AvailabilityMask.   */
    /*------------------------------------------*/
    statusOfDTC             =   Dem_DTC_CnvDTCStatus_PmAvailabilityMask( statusOfDTC );

    /*  check DTCStatusMask             */
    retCheckDTCStatusMask   =   Dem_DTC_CheckDTCStatusForFilter( DTCStatusMask, statusOfDTC );

    /*  get statusOfDTC                 */
    *DTCStatusPtr   =   statusOfDTC;

    return retCheckDTCStatusMask;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
