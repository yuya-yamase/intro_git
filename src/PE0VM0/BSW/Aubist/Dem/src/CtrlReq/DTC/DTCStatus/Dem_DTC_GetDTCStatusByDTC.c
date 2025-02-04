/* Dem_DTC_GetDTCStatusByDTC_c(v5-5-0)                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DTC_GetDTCStatusByDTC/CODE                            */
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
#include "../../../../inc/Dem_Pm_DataAvl.h"
#include "../../../../inc/Dem_Pm_DTC.h"
#include "../../../../inc/Dem_Pm_Ind.h"
#include "../../../../inc/Dem_Pm_DataCtl.h"

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
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DTC_GetDTCStatusByDTC                                */
/* Description   | Gets the UDS DTC status byte corresponding to specified  */
/*               |  event ID.                                               */
/* Preconditions | The specified event index corresponding to the event ID  */
/*               |  has been already retrieved.                             */
/* Parameters    | [in] TargetEventStrgIndex :                              */
/*               |        The event index corresponding to the event ID.    */
/*               | [out] DTCStatusPtr :                                     */
/*               |        The UDS DTC status byte which has been retrieved- */
/*               |        .                                                 */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : The UDS DTC status byte retrieving - */
/*               |        is successful.                                    */
/*               |        DEM_IRT_NG : The UDS DTC status byte retrieving - */
/*               |        is failed.                                        */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_GetDTCStatusByDTC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) TargetEventStrgIndex,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) retStatusOfDTC;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) tempStatusOfDTC;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndexNum;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndexCnt;
    VAR( boolean, AUTOMATIC ) eventAvailableDef;

    /* Set initial value. */
    retVal = DEM_IRT_NG;

    /* set target event. */
    eventStrgIndex = TargetEventStrgIndex;
    /* get num of event index in DTC group. */
    eventStrgIndexNum = Dem_CmbEvt_NumOfEventStrgIndex_InDTCGrp( eventStrgIndex );

    if( eventStrgIndexNum == ( Dem_u16_EventStrgIndexType )1U )
    {
        /* Check available status. */
        eventAvailableDef = Dem_DataAvl_GetEvtAvl_InEvtStrgGrp( eventStrgIndex );
        if( eventAvailableDef == (boolean)TRUE )
        {
            /* Gets the status of DTC of the event record corresponding to the specified event index. */
            (void)Dem_DataMngC_GetER_StatusOfDTC( eventStrgIndex, &retStatusOfDTC );   /* no return check required */

            retVal = DEM_IRT_OK;
        }
        else
        {
            retStatusOfDTC = DEM_DTCSTATUS_BYTE_DEFAULT;
        }
    }
    else
    {
        retStatusOfDTC  = DEM_DTCSTATUS_BYTE_ALL_OFF;
        tempStatusOfDTC = DEM_DTCSTATUS_BYTE_ALL_OFF;
        for( eventStrgIndexCnt = ( Dem_u16_EventStrgIndexType )0U; eventStrgIndexCnt < eventStrgIndexNum; eventStrgIndexCnt++ )
        {
            /* Check available status. */
            eventAvailableDef = Dem_DataAvl_GetEvtAvl_InEvtStrgGrp( eventStrgIndex );
            if( eventAvailableDef == (boolean)TRUE )
            {
                /* Gets the status of DTC of the event record corresponding to the specified event index. */
                (void)Dem_DataMngC_GetER_StatusOfDTC( eventStrgIndex, &tempStatusOfDTC );   /* no return check required */

                /* Merge StatusOfDTC */
                retStatusOfDTC = ( retStatusOfDTC | tempStatusOfDTC );
                retVal = DEM_IRT_OK;
            }
            /* get next event index. */
            eventStrgIndex = Dem_CmbEvt_GetNextEventStrgIndex_InDTCGrp( eventStrgIndex );
        }

        /* Checks the result of retrieving the event record. */
        if( retVal == DEM_IRT_OK )
        {
            /* Retrieving the event record is successful. */

            /* Bit4 is set as below. */
            /* (Event[1].bit4 OR Event[2].bit4 OR ... OR  Event[n].bit4) AND NOT(Event[1].bit5 OR Event[2].bit5 OR ... OR  Event[n].bit5) */
            /* So Check Bit5. Bit5 is on, set Bit4 to 0. */
            if( ( retStatusOfDTC & DEM_UDS_STATUS_TFSLC ) == DEM_UDS_STATUS_TFSLC )
            {
                retStatusOfDTC = ( retStatusOfDTC & ~DEM_UDS_STATUS_TNCSLC );
            }

            /* Bit6 is set as below. */
            /* (Event[1].bit6 OR Event[2].bit6 OR ... OR  Event[n].bit6) AND NOT(Event[1].bit1 OR Event[2].bit1 OR ... OR  Event[n].bit1) */
            /* So Check Bit1. Bit1 is on, set Bit6 to 0. */
            if( ( retStatusOfDTC & DEM_UDS_STATUS_TFTOC ) == DEM_UDS_STATUS_TFTOC )
            {
                retStatusOfDTC = ( retStatusOfDTC & ~DEM_UDS_STATUS_TNCTOC );
            }
        }
        else
        {
            retStatusOfDTC = DEM_DTCSTATUS_BYTE_DEFAULT;
        }
    }

    /* Stores StatusOfDTC of the event memory entry of temporary area to the specified parameter. */
    *DTCStatusPtr = retStatusOfDTC;

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DTC_GetDTCStatusByDTCAndSeverity                     */
/* Description   | Gets the UDS DTC status byte corresponding to specified  */
/*               |  event ID.                                               */
/* Preconditions | The specified event index corresponding to the event ID  */
/*               |  has been already retrieved.                             */
/* Parameters    | [in] TargetEventStrgIndex :                              */
/*               |        The event index corresponding to the event ID.    */
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
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_GetDTCStatusByDTCAndSeverity
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) TargetEventStrgIndex,              /* [PRMCHK:CALLER] */
    VAR( boolean, AUTOMATIC ) FilterWithSeverity,
    VAR( Dem_DTCSeverityType, AUTOMATIC ) DTCSeverityMask,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr,
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, AUTOMATIC ) DTCSeverityPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) retStatusOfDTC;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) tempStatusOfDTC;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndexNum;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndexCnt;
    VAR( Dem_DTCSeverityType, AUTOMATIC ) dtcClassByEventStrgIndex;
    VAR( Dem_DTCSeverityType, AUTOMATIC ) dtcClassAtDTCAll;
    VAR( Dem_DTCSeverityType, AUTOMATIC ) dtcClassAtDTCTgt;
    VAR( Dem_DTCSeverityType, AUTOMATIC ) maskedSeverity;
    VAR( boolean, AUTOMATIC ) eventAvailableDef;
    VAR( boolean, AUTOMATIC ) mergeInfo;
    VAR( boolean, AUTOMATIC ) wirStatus;

    /* Set initial value. */
    retVal = DEM_IRT_NG;

    /* set target event. */
    eventStrgIndex      =   TargetEventStrgIndex;                                       /* [GUDCHK:CALLER]TargetEventStrgIndex */
    dtcClassAtDTCAll    =   DEM_SEVERITY_NO_SEVERITY;
    dtcClassAtDTCTgt    =   DEM_SEVERITY_NO_SEVERITY;

    /* get num of event index in DTC group. */
    eventStrgIndexNum = Dem_CmbEvt_NumOfEventStrgIndex_InDTCGrp( eventStrgIndex );      /* [GUDCHK:CALLER]TargetEventStrgIndex */

    if ( eventStrgIndexNum == (Dem_u16_EventStrgIndexType)1U )
    {
        /*  check event available.      */
        eventAvailableDef = Dem_DataAvl_GetEvtAvl_InEvtStrgGrp( eventStrgIndex );       /* [GUDCHK:CALLER]TargetEventStrgIndex */
        if( eventAvailableDef == (boolean)TRUE )
        {
            /*----------------------------------*/
            /*  get statusOfDTC.                */
            /*----------------------------------*/
            /* Gets the status of DTC of the event record corresponding to the specified event index. */
            (void)Dem_DataMngC_GetER_StatusOfDTC( eventStrgIndex, &retStatusOfDTC );   /* no return check required */   /* [GUDCHK:CALLER]TargetEventStrgIndex */

            wirStatus   =   (boolean)FALSE;
            (void)Dem_Ind_GetWIRStatus( eventStrgIndex, &wirStatus );                   /* no return check required */
            if ( wirStatus == (boolean)TRUE )
            {
                /*  set bit7.                    */
                retStatusOfDTC = Dem_DTC_SetWIRStatusBit( retStatusOfDTC );
            }

            /*----------------------------------*/
            /*  get severity                    */
            /*----------------------------------*/
            dtcClassAtDTCTgt     =   Dem_CfgInfoPm_GetDTCSeverityClass( eventStrgIndex );                               /* [GUDCHK:CALLER]TargetEventStrgIndex */

            if ( FilterWithSeverity == (boolean)TRUE )
            {
                /*  target DTC class or not.        */
                maskedSeverity = ( dtcClassAtDTCTgt & DTCSeverityMask & Dem_DtcSeverityAvailabilityMask );
                if( maskedSeverity != DEM_DTCSEVERITY_BYTE_ALL_OFF )
                {
                    retVal = DEM_IRT_OK;
                }
            }
            else
            {
                retVal = DEM_IRT_OK;
            }
        }
        else
        {
            retStatusOfDTC = DEM_DTCSTATUS_BYTE_DEFAULT;
        }
    }
    else
    {
        retStatusOfDTC  = DEM_DTCSTATUS_BYTE_ALL_OFF;
        tempStatusOfDTC = DEM_DTCSTATUS_BYTE_ALL_OFF;
        for( eventStrgIndexCnt = ( Dem_u16_EventStrgIndexType )0U; eventStrgIndexCnt < eventStrgIndexNum; eventStrgIndexCnt++ )
        {
            /* Check available status. */
            eventAvailableDef = Dem_DataAvl_GetEvtAvl_InEvtStrgGrp( eventStrgIndex );                                       /* [GUDCHK:CALLER]TargetEventStrgIndex */
            if( eventAvailableDef == (boolean)TRUE )
            {
                /* Gets the status of DTC of the event record corresponding to the specified event index. */
                (void)Dem_DataMngC_GetER_StatusOfDTC( eventStrgIndex, &tempStatusOfDTC );   /* no return check required */  /* [GUDCHK:CALLER]TargetEventStrgIndex */
                dtcClassByEventStrgIndex     =   Dem_CfgInfoPm_GetDTCSeverityClass( eventStrgIndex );                       /* [GUDCHK:CALLER]TargetEventStrgIndex */

                mergeInfo   =   (boolean)TRUE;
                if ( FilterWithSeverity == (boolean)TRUE )
                {
                    /*  target DTC class or not.        */
                    maskedSeverity = ( dtcClassByEventStrgIndex & DTCSeverityMask & Dem_DtcSeverityAvailabilityMask );

                    if( maskedSeverity == DEM_DTCSEVERITY_BYTE_ALL_OFF )
                    {
                        /*  no target DTC class.        */
                        mergeInfo   =   (boolean)FALSE;
                    }
                }

                if ( mergeInfo == (boolean)TRUE )
                {
                    /* Merge StatusOfDTC */
                    retStatusOfDTC    = ( retStatusOfDTC    | tempStatusOfDTC );

                    /*  merge WIR status.               */
                    wirStatus   =   (boolean)FALSE;
                    (void)Dem_Ind_GetWIRStatus( eventStrgIndex, &wirStatus );                   /* no return check required */
                    if ( wirStatus == (boolean)TRUE )
                    {
                        /*  set bit7.                    */
                        retStatusOfDTC = Dem_DTC_SetWIRStatusBit( retStatusOfDTC );
                    }

                    dtcClassAtDTCAll  = ( dtcClassAtDTCAll  | dtcClassByEventStrgIndex );

                    retVal = DEM_IRT_OK;
                }
            }

            /* get next event index. */
            eventStrgIndex = Dem_CmbEvt_GetNextEventStrgIndex_InDTCGrp( eventStrgIndex );       /* [GUDCHK:CALLER]TargetEventStrgIndex */
        }

        /* Checks the result of retrieving the event record. */
        if( retVal == DEM_IRT_OK )
        {
            /* Retrieving the event record is successful. */

            /* Bit4 is set as below. */
            /* (Event[1].bit4 OR Event[2].bit4 OR ... OR  Event[n].bit4) AND NOT(Event[1].bit5 OR Event[2].bit5 OR ... OR  Event[n].bit5) */
            /* So Check Bit5. Bit5 is on, set Bit4 to 0. */
            if( ( retStatusOfDTC & DEM_UDS_STATUS_TFSLC ) == DEM_UDS_STATUS_TFSLC )
            {
                retStatusOfDTC = ( retStatusOfDTC & ~DEM_UDS_STATUS_TNCSLC );
            }

            /* Bit6 is set as below. */
            /* (Event[1].bit6 OR Event[2].bit6 OR ... OR  Event[n].bit6) AND NOT(Event[1].bit1 OR Event[2].bit1 OR ... OR  Event[n].bit1) */
            /* So Check Bit1. Bit1 is on, set Bit6 to 0. */
            if( ( retStatusOfDTC & DEM_UDS_STATUS_TFTOC ) == DEM_UDS_STATUS_TFTOC )
            {
                retStatusOfDTC = ( retStatusOfDTC & ~DEM_UDS_STATUS_TNCTOC );
            }

            /*------------------------------------------*/
            /*  DTCClass priority   :                   */
            /*      DEM_DTC_CLASS_1(0x02)               */
            /*      > DEM_DTC_CLASS_2(0x04)             */
            /*      > DEM_DTC_CLASS_3(0x08)             */
            /*      > DEM_DTC_CLASS_4(0x10)             */
            /*      > DEM_DTC_CLASS_0(0x01)             */
            /*      > DEM_SEVERITY_NO_SEVERITY(0x00)    */
            /*------------------------------------------*/
            if (( dtcClassAtDTCAll & DEM_DTC_CLASS_1 ) == DEM_DTC_CLASS_1 )
            {
                dtcClassAtDTCTgt    =   DEM_DTC_CLASS_1;
            }
            else if (( dtcClassAtDTCAll & DEM_DTC_CLASS_2 ) == DEM_DTC_CLASS_2 )
            {
                dtcClassAtDTCTgt    =   DEM_DTC_CLASS_2;
            }
            else if (( dtcClassAtDTCAll & DEM_DTC_CLASS_3 ) == DEM_DTC_CLASS_3 )
            {
                dtcClassAtDTCTgt    =   DEM_DTC_CLASS_3;
            }
            else if (( dtcClassAtDTCAll & DEM_DTC_CLASS_4 ) == DEM_DTC_CLASS_4 )
            {
                dtcClassAtDTCTgt    =   DEM_DTC_CLASS_4;
            }
            else if (( dtcClassAtDTCAll & DEM_DTC_CLASS_0 ) == DEM_DTC_CLASS_0 )
            {
                dtcClassAtDTCTgt    =   DEM_DTC_CLASS_0;
            }
            else
            {
                /*  DEM_SEVERITY_NO_SEVERITY        */
            }
        }
        else
        {
            retStatusOfDTC = DEM_DTCSTATUS_BYTE_DEFAULT;
        }
    }
    /* Stores StatusOfDTC of the event memory entry of temporary area to the specified parameter. */
    *DTCStatusPtr    = retStatusOfDTC;
    *DTCSeverityPtr  = dtcClassAtDTCTgt;

    return retVal;
}

#endif  /*   ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )     */

#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_DTC_GetDTCStatusByDTC                                */
/* Description   | Gets the UDS DTC status byte corresponding to specified  */
/*               |  event ID.                                               */
/* Preconditions | The specified event index corresponding to the event ID  */
/*               |  has been already retrieved.                             */
/* Parameters    | [in] TargetEventStrgIndex :                              */
/*               |        The event index corresponding to the event ID.    */
/*               | [out] DTCStatusPtr :                                     */
/*               |        The UDS DTC status byte which has been retrieved- */
/*               |        .                                                 */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : The UDS DTC status byte retrieving - */
/*               |        is successful.                                    */
/*               |        DEM_IRT_NG : The UDS DTC status byte retrieving - */
/*               |        is failed.                                        */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_GetDTCStatusByDTC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) TargetEventStrgIndex,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = Dem_DataMngC_GetER_StatusOfDTC( TargetEventStrgIndex, DTCStatusPtr );

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DTC_GetDTCStatusByDTCAndSeverity                     */
/* Description   | Gets the UDS DTC status byte corresponding to specified  */
/*               |  event ID.                                               */
/* Preconditions | The specified event index corresponding to the event ID  */
/*               |  has been already retrieved.                             */
/* Parameters    | [in] TargetEventStrgIndex :                              */
/*               |        The event index corresponding to the event ID.    */
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
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_GetDTCStatusByDTCAndSeverity
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) TargetEventStrgIndex,
    VAR( boolean, AUTOMATIC ) FilterWithSeverity,                       /* MISRA DEVIATION */
    VAR( Dem_DTCSeverityType, AUTOMATIC ) DTCSeverityMask,              /* MISRA DEVIATION */
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr,
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, AUTOMATIC ) DTCSeverityPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) eventAvailableDef;
    VAR( boolean, AUTOMATIC ) wirStatus;

    retVal = DEM_IRT_NG;

    /*  check event available.      */
    eventAvailableDef = Dem_DataAvl_GetEvtAvl_InEvtStrgGrp( TargetEventStrgIndex );
    if( eventAvailableDef == (boolean)TRUE )
    {
        /*----------------------------------*/
        /*  get statusOfDTC.                */
        /*----------------------------------*/
        (void)Dem_DataMngC_GetER_StatusOfDTC( TargetEventStrgIndex, DTCStatusPtr ); /* no return check required */

        wirStatus   =   (boolean)FALSE;
        (void)Dem_Ind_GetWIRStatus( TargetEventStrgIndex, &wirStatus );                 /* no return check required */
        if ( wirStatus == (boolean)TRUE )
        {
            /*  set bit7.                    */
            (*DTCStatusPtr) = Dem_DTC_SetWIRStatusBit( (*DTCStatusPtr) );
        }

        /*----------------------------------*/
        /*  get severity                    */
        /*----------------------------------*/
        *DTCSeverityPtr  = Dem_CfgInfoPm_GetDTCSeverityClass( TargetEventStrgIndex );
        retVal = DEM_IRT_OK;
    }
    else
    {
        *DTCStatusPtr    = DEM_DTCSTATUS_BYTE_DEFAULT;
        *DTCSeverityPtr  = DEM_SEVERITY_NO_SEVERITY;
    }
    return retVal;
}

#endif  /*   ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_OFF )     */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
