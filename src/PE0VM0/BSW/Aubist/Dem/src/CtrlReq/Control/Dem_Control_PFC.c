/* Dem_Control_PFC_c(v5-5-0)                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_PFC/CODE                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_AsyncReq.h"
#include "../../../inc/Dem_CmnLib_AsyncReqTable.h"
#include "../../../inc/Dem_CmnLib_Control_AsyncReq.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_CmnLib_DataAvl.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_Pm_Control_OBD.h"
#include "../../../inc/Dem_Pm_DTC_PFC.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "Dem_Control_local.h"

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

#if ( DEM_PFC_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Control_GetPermanentUDSDTC                           */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [out] PermanentDTCBufferPtr :                            */
/*               |        PemanetDTC                                        */
/*               | [out] PermanentDTCNumPtr :                               */
/*               |        PermanentDTC Num                                  */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Successful.                          */
/*               |        DEM_IRT_NG : Failure.                             */
/*               |                     matching the filter criteria - found */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_Control_GetPermanentOBDDTC.    */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetPermanentUDSDTC
(
    P2VAR( uint32, AUTOMATIC, DEM_APPL_DATA ) PermanentDTCBufferPtr,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) PermanentDTCNumPtr
)
{
    VAR( Dem_u32_DTCValueType, AUTOMATIC )    permanentDTC;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )     retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )     internalRetVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )     checkStatus;
    VAR( uint8, AUTOMATIC )     permanentDTCNum;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC )     pfcSearchIndex;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC )     pfcRecordNum;
    VAR( boolean, AUTOMATIC ) resultValidateDTC;
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( uint8, AUTOMATIC )     permanentDTCMisfireNum;
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )           */

    retVal = DEM_IRT_NG;
    permanentDTCNum = (uint8)0U;
    pfcRecordNum = Dem_PFCRecordNum;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        SchM_Enter_Dem_PermanentMemory();   /* waits completion of updating Diag record data by Dem_MainFunction.      */
        SchM_Exit_Dem_PermanentMemory();

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
        permanentDTCMisfireNum  =   (uint8)0U;
        Dem_Misfire_GetPermanentUDSDTC( &PermanentDTCBufferPtr[0], &permanentDTCMisfireNum );
        permanentDTCNum         =   permanentDTCMisfireNum;                                                 /* [GUD:SPC]permanentDTCNum */
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )           */

        for( pfcSearchIndex = (Dem_u08_PFCIndexType)0U; pfcSearchIndex < pfcRecordNum; pfcSearchIndex++ )   /* [GUD:if]pfcSearchIndex */
        {
            internalRetVal = Dem_DTC_GetPermanentDTC( pfcSearchIndex, DEM_DTC_FORMAT_UDS, &permanentDTC );
            /* Convert return value */
            if( internalRetVal == DEM_IRT_OK )
            {
                resultValidateDTC   =   Dem_DataAvl_ValidateDTC( permanentDTC );
                if ( resultValidateDTC == (boolean)TRUE )
                {
                    PermanentDTCBufferPtr[permanentDTCNum] = (uint32)permanentDTC;      /* [GUD]pfcSearchIndex *//* [GUD:SPC:IF_GUARDED: pfcSearchIndex ]permanentDTCNum */
                    permanentDTCNum = permanentDTCNum + (uint8)1U;
                }
            }
            else
            {
                /* No Process */
            }

        }
        retVal = DEM_IRT_OK;
    }

    *PermanentDTCNumPtr = permanentDTCNum;

    return retVal;

}

#if ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Control_GetPermanentOBDDTC                           */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [out] PermanentDTCBufferPtr :                            */
/*               |        PemanetDTC                                        */
/*               | [out] PermanentDTCNumPtr :                               */
/*               |        PermanentDTC Num                                  */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Successful.                          */
/*               |        DEM_IRT_NG : Failure.                             */
/*               |                     matching the filter criteria - found */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | rename from Dem_Control_GetPermanentDTC(v5-3-0).         */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetPermanentOBDDTC
(
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) PermanentDTCBufferPtr,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) PermanentDTCNumPtr
)
{
    VAR( Dem_u32_DTCValueType, AUTOMATIC )    permanentDTC;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )     retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )     internalRetVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )     checkStatus;
    VAR( uint8, AUTOMATIC )     permanentDTCNum;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC )     pfcSearchIndex;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC )     pfcRecordNum;
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( uint8, AUTOMATIC )     permanentDTCMisfireNum;
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )           */

    retVal = DEM_IRT_NG;
    permanentDTCNum = (uint8)0U;
    pfcRecordNum = Dem_PFCRecordNum;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        SchM_Enter_Dem_PermanentMemory();   /* waits completion of updating Diag record data by Dem_MainFunction.      */
        SchM_Exit_Dem_PermanentMemory();

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
        permanentDTCMisfireNum  =   (uint8)0U;
        Dem_Misfire_GetPermanentOBDDTC( &PermanentDTCBufferPtr[0], &permanentDTCMisfireNum );
        permanentDTCNum         =   permanentDTCMisfireNum;                         /* [GUD:SPC]permanentDTCNum */
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )           */

        for( pfcSearchIndex = (Dem_u08_PFCIndexType)0U; pfcSearchIndex < pfcRecordNum; pfcSearchIndex++ )   /* [GUD:if]pfcSearchIndex */
        {
            internalRetVal = Dem_DTC_GetPermanentDTC( pfcSearchIndex, DEM_DTC_FORMAT_OBD, &permanentDTC );
            /* Convert return value */
            if( internalRetVal == DEM_IRT_OK )
            {
                PermanentDTCBufferPtr[permanentDTCNum] = (uint16)permanentDTC;      /* [GUD]pfcSearchIndex *//* [GUD:SPC:IF_GUARDED: pfcSearchIndex ]permanentDTCNum */
                permanentDTCNum = permanentDTCNum + (uint8)1U;
            }
            else
            {
                /* No Process */
            }

        }
        retVal = DEM_IRT_OK;
    }

    *PermanentDTCNumPtr = permanentDTCNum;

    return retVal;

}
#endif  /*   ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )       */

/****************************************************************************/
/* Function Name | Dem_Control_GetClearPFCCycleQualified                    */
/* Description   | Gets PFC cycle qualified.                                */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               |        Identification of an event by assigned EventId.   */
/*               | [out] PassedCycleQualifiedPtr :                          */
/*               | [out] DrivingConditionQualifiedPtr :                     */
/*               | [out] PFCCycleQualifiedPtr :                             */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Operation was successful             */
/*               |        DEM_IRT_NG : Operation failed                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetClearPFCCycleQualified
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) PassedCycleQualifiedPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) DrivingConditionQualifiedPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) PFCCycleQualifiedPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndexPFCRecord;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC )     pfcSearchIndex;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC )     pfcRecordNum;

    VAR( boolean, AUTOMATIC )     pfcRecordAvailable;

    retVal = DEM_IRT_NG;
    eventCtrlIndex = DEM_EVENTCTRLINDEX_INVALID;
    pfcRecordNum = Dem_PFCRecordNum;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        /*  convert eventid to eventCtrlIndex.      */
        retTempVal = Dem_Control_GetEventCtrlIndexFromEventId( EventId, &eventCtrlIndex );          /* [GUD:RET:DEM_IRT_OK] eventCtrlIndex */
        if( retTempVal == DEM_IRT_OK )
        {
            /*  convert eventCtrlIndex to eventStrgIndex.       */
            eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( eventCtrlIndex );    /* [GUD]eventCtrlIndex *//* [GUD:RET:IF_GUARDED: EventCtrlIndex ] eventStrgIndex */

            SchM_Enter_Dem_PermanentMemory();   /* waits completion of updating Diag record data by Dem_MainFunction.      */
            SchM_Exit_Dem_PermanentMemory();

            /*  search eventStrgIndex from PFC record.      */
            for( pfcSearchIndex = (Dem_u08_PFCIndexType)0U; pfcSearchIndex < pfcRecordNum; pfcSearchIndex++ )   /* [GUD:for]pfcSearchIndex */
            {
                /*  get eventStrgIndex in PFC record.       */
                pfcRecordAvailable  =   Dem_DTC_GetEventStrgIndexInPFCRecord( pfcSearchIndex, &eventStrgIndexPFCRecord );   /* [GUD]pfcSearchIndex */
                if( pfcRecordAvailable == (boolean)TRUE )
                {
                    /*  available record.       */
                    if( eventStrgIndex == eventStrgIndexPFCRecord )
                    {
                        /*  get cycle qualified.        */
                        (void)Dem_DTC_GetClearPFCCycleQualified( pfcSearchIndex, PassedCycleQualifiedPtr, DrivingConditionQualifiedPtr, PFCCycleQualifiedPtr ); /* no return check required */
                        retVal = DEM_IRT_OK;
                        break;
                    }
                }
            }
        }
    }
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_CheckExistPermanentDTCByEventId              */
/* Description   | Gets PFC cycle qualified.                                */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               | [out] IsPermanentDTCPtr :                                */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Operation was successful             */
/*               |        DEM_IRT_NG : Operation failed                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.based on Dem_Control_GetClearPFCCycleQualified. */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_CheckExistPermanentDTCByEventId
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) IsPermanentDTCPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndexPFCRecord;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC )     pfcSearchIndex;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC )     pfcRecordNum;
    VAR( boolean, AUTOMATIC ) isPermanentDTC;
    VAR( boolean, AUTOMATIC ) eventOBDKind;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCheckResult;

    VAR( boolean, AUTOMATIC )     pfcRecordAvailable;

    retVal = DEM_IRT_NG;
    eventCtrlIndex = DEM_EVENTCTRLINDEX_INVALID;
    isPermanentDTC = (boolean)FALSE;

    pfcRecordNum = Dem_PFCRecordNum;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        /*  convert eventid to eventCtrlIndex.      */
        retTempVal = Dem_Control_GetEventCtrlIndexFromEventId( EventId, &eventCtrlIndex );          /* [GUD:RET:DEM_IRT_OK] eventCtrlIndex */
        if( retTempVal == DEM_IRT_OK )
        {
            /*  convert eventCtrlIndex to eventStrgIndex.       */
            eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( eventCtrlIndex );    /* [GUD]eventCtrlIndex *//* [GUD:RET:IF_GUARDED: EventCtrlIndex ] eventStrgIndex */

            /*  check OBD event or not.         */
            eventOBDKind    =   Dem_CfgInfoPm_CheckEventKindOfOBD_InEvtStrgGrp( eventStrgIndex );   /* [GUD:RET:TRUE] eventStrgIndex */
            if( eventOBDKind == (boolean)TRUE ) /*  OBD     */
            {
                /*  check available PFC target event or not.    */
                retCheckResult  =   Dem_DTC_CheckAvailableAndMILStatusByEventStrgIndex( eventStrgIndex );   /* [GUD]eventStrgIndex */
                if( retCheckResult == DEM_IRT_OK )
                {
                    SchM_Enter_Dem_PermanentMemory();   /* waits completion of updating Diag record data by Dem_MainFunction.      */
                    SchM_Exit_Dem_PermanentMemory();

                    /*  search eventStrgIndex from PFC record.      */
                    for( pfcSearchIndex = (Dem_u08_PFCIndexType)0U; pfcSearchIndex < pfcRecordNum; pfcSearchIndex++ )   /* [GUD:for]pfcSearchIndex */
                    {
                        /*  get eventStrgIndex in PFC record.       */
                        pfcRecordAvailable  =   Dem_DTC_GetEventStrgIndexInPFCRecord( pfcSearchIndex, &eventStrgIndexPFCRecord );   /* [GUD]pfcSearchIndex */
                        if( pfcRecordAvailable == (boolean)TRUE )
                        {
                            /*  available record.       */
                            if( eventStrgIndex == eventStrgIndexPFCRecord )
                            {
                                isPermanentDTC  =   (boolean)TRUE;
                                break;
                            }
                        }
                    }

                    *IsPermanentDTCPtr  =   isPermanentDTC;

                    retVal = DEM_IRT_OK;
                }
            }
        }
    }
    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Control_GetEventIdWithPermanentDTC                   */
/* Description   | Get eventId list.                                        */
/* Preconditions | none                                                     */
/* Parameters    | [out] EventIdBufferPtr :  EventId list.                  */
/*               | [out] EventIdNumPtr :  EventId list number.              */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Operation was successful             */
/*               |        DEM_IRT_NG : Operation failed                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.based on Dem_Control_GetClearPFCCycleQualified. */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetEventIdWithPermanentDTC
(
    P2VAR( Dem_EventIdType, AUTOMATIC, DEM_APPL_DATA ) EventIdBufferPtr,
    P2VAR( uint16, AUTOMATIC, AUTOMATIC ) EventIdNumPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndexPFCRecord;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC )     pfcSearchIndex;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC )     pfcRecordNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;
    VAR( Dem_EventIdType, AUTOMATIC ) eventIdCnt;

    VAR( boolean, AUTOMATIC )     pfcRecordAvailable;

    retVal = DEM_IRT_NG;

    eventIdCnt          =   (Dem_EventIdType)0U;

    pfcRecordNum = Dem_PFCRecordNum;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        SchM_Enter_Dem_PermanentMemory();   /* waits completion of updating Diag record data by Dem_MainFunction.      */
        SchM_Exit_Dem_PermanentMemory();

        /*  search eventStrgIndex from PFC record.      */
        for( pfcSearchIndex = (Dem_u08_PFCIndexType)0U; pfcSearchIndex < pfcRecordNum; pfcSearchIndex++ )   /* [GUD:for]pfcSearchIndex */
        {
            /*  get eventStrgIndex in PFC record.       */
            pfcRecordAvailable  =   Dem_DTC_GetEventStrgIndexInPFCRecord( pfcSearchIndex, &eventStrgIndexPFCRecord );   /* [GUD]pfcSearchIndex *//* [GUD:RET:TRUE] eventStrgIndexPFCRecord */
            if( pfcRecordAvailable == (boolean)TRUE )
            {
                /*  convert eventStrgIndexPFCRecord to eventId.     */
                retCnvId    =   Dem_CfgInfoPm_CnvEventStrgIndexToEventId( eventStrgIndexPFCRecord, &eventId );          /* [GUD]eventStrgIndexPFCRecord */
                if ( retCnvId == DEM_IRT_OK )
                {
                    /*  store data.     */
                    EventIdBufferPtr[ eventIdCnt ]  =   eventId;                        /* [GUD:SPC:IF_GUARDED: pfcSearchIndex ]eventIdCnt */
                    eventIdCnt  =   eventIdCnt + ( Dem_EventIdType )1U;
                }
            }
        }
        *EventIdNumPtr  =   eventIdCnt;
        retVal = DEM_IRT_OK;
    }
    return retVal;
}


#if ( DEM_PFC_RECORD_SUPPRESSION_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Control_EnablePFCRecordUpdate                        */
/* Description   | PFC Record Suppression Cancellation Event.               */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_EnablePFCRecordUpdate
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;

    retVal = DEM_IRT_NG;

    retTempVal = Dem_AsyncReq_JudgeReqCondition( DEM_ASYNCREQ_PFC_RECORD_UPDATE, DEM_ASYNCREQ_PARAM_INDEX_INVALID, DEM_PFC_RECORD_UPDATE_ENABLE );
    if( retTempVal == DEM_IRT_OK )
    {
        retTempVal = Dem_AsyncReq_Enqueue( DEM_ASYNCREQ_PFC_RECORD_UPDATE, DEM_ASYNCREQ_PARAM_INDEX_INVALID, DEM_PFC_RECORD_UPDATE_ENABLE );
        if( retTempVal == DEM_IRT_OK )
        {
            retVal = DEM_IRT_OK;
        }
        else
        {
            /* When it can not be stored in the event queue */
            /* Receiving event is discarded because processing can not be done */
            /* No process */
        }
    }
    else
    {
        /* When the result of request condition judgment is not OK */
        /* No process */
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_DisablePFCRecordUpdate                       */
/* Description   | PFC Record Suppression Cancellation Event.               */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_DisablePFCRecordUpdate
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;

    retVal = DEM_IRT_NG;

    retTempVal = Dem_AsyncReq_JudgeReqCondition( DEM_ASYNCREQ_PFC_RECORD_UPDATE, DEM_ASYNCREQ_PARAM_INDEX_INVALID, DEM_PFC_RECORD_UPDATE_DISABLE );
    if( retTempVal == DEM_IRT_OK )
    {
        retTempVal = Dem_AsyncReq_Enqueue( DEM_ASYNCREQ_PFC_RECORD_UPDATE, DEM_ASYNCREQ_PARAM_INDEX_INVALID, DEM_PFC_RECORD_UPDATE_DISABLE );
        if( retTempVal == DEM_IRT_OK )
        {
            retVal = DEM_IRT_OK;
        }
        else
        {
            /* When it can not be stored in the event queue */
            /* Receiving event is discarded because processing can not be done */
            /* No process */
        }
    }
    else
    {
        /* When the result of request condition judgment is not OK */
        /* No process */
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_PFCRecordUpdateProcess                       */
/* Description   | Asynchronous processing function of EnablePFCRecord-     */
/*               | Update.                                                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] Index       :                                       */
/*               | [in] Status      :                                       */
/*               | [in] DataBuffPtr :                                       */
/* Return Value  | Dem_u08_AsyncExecReturnType                              */
/*               |       : See the description of the return value of       */
/*               |         "DemAsyncReqFncPTR" in Dem_CmnLib_Control_AsyncReq.h.   */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_Control_PFCRecordUpdateProcess
(
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,                     /* MISRA DEVIATION */
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr    /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_AsyncExecReturnType, AUTOMATIC ) retVal;

    /* Set return value. */
    /* Fault record is not updated, No need re-generate orderlist, Continue asynchronous processing. */
    retVal = ( DEM_ASYNCRET_NOUPD_FR | DEM_ASYNCRET_NONEED_REGEN_ODR | DEM_ASYNCRET_CONTINUE_ASYNC_PROC );

    if ( Status == DEM_PFC_RECORD_UPDATE_DISABLE )
    {
        Dem_DTC_SetPFCUpdateDisable();
    }
    else
    {
        Dem_DTC_SetPFCUpdateEnable();

        /*--------------------------------------*/
        /*  notify SAVED_ZONE update - start.   */
        Dem_NotifySavedZoneUpdate_Enter();      /*  notify start :  savedzone area will be update.  */
        /*--------------------------------------*/

        Dem_DTC_UpdatePFCRecord();

        /*--------------------------------------*/
        /*  notify SAVED_ZONE update - end.     */
        Dem_NotifySavedZoneUpdate_Exit();       /*  notify end :  savedzone area will be update.    */
        /*--------------------------------------*/
    }

    return retVal;
}
#endif /* DEM_PFC_RECORD_SUPPRESSION_SUPPORT -STD_ON- */

#endif /* DEM_PFC_SUPPORT -STD_ON- */

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2019-03-27                                              */
/*  v3-0-0         :2019-09-26                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
