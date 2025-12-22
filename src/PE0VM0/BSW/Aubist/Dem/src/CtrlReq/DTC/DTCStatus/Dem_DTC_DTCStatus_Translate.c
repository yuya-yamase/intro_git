/* Dem_DTC_DTCStatus_Translate_c(v5-9-0)                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/


/****************************************************************************/
/* Object Name  | Dem/DTC_DTCStatus_Translate/CODE                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../../cfg/Dem_Cfg.h"
#include "../../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../../inc/Dem_CmnLib_DTC_DTCStatus.h"
#include "../../../../inc/Dem_CmnLib_DTC_User.h"
#include "../../../../inc/Dem_Pm_DataAvl.h"
#include "../../../../inc/Dem_Pm_DTC.h"
#include "../../../../inc/Dem_Pm_Misfire.h"
#include "../../../../inc/Dem_Pm_Ind.h"

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

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_MergeWIRStatusBit
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
);
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_MergeWIRStatusBitByDTC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
);
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_MergeOneSetOfWIRStatusBit
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatus1Ptr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatus2Ptr
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

/****************************************************************************/
/* Function Name | Dem_DTC_TranslateDTCstatusAfterUpdate                    */
/* Description   | Translation processing after the DTC status update.      */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        Index corresponding to the event.                 */
/*               | [in/out] OldDTCStatusPtr :                               */
/*               |        DTC status before the event registration (it sto- */
/*               |        res a value after the translation processing for  */
/*               |         Out)                                             */
/*               | [in/out] NewDTCStatusPtr :                               */
/*               |        DTC status after the event registration (it stor- */
/*               |        es a value after the translation processing for - */
/*               |        Out)                                              */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-9-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DTC_TranslateDTCStatusAfterUpdate
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) OldDTCStatusPtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) NewDTCStatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retMergeDTC;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetEvent;
    VAR( Std_ReturnType, AUTOMATIC ) resultOfCallOut;
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( Dem_EventKindType, AUTOMATIC ) eventKind;
#endif  /*   ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )         */

    if ( *OldDTCStatusPtr != *NewDTCStatusPtr )
    {
        retGetEvent     = DEM_IRT_NG;
        resultOfCallOut = E_NOT_OK;
        eventId         = ((Dem_EventIdType)0x0000U);

        eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( EventCtrlIndex );                    /* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */

        /* Merge WIRStatus bit into bit7 of old and new DTCStatus. */
        retMergeDTC = Dem_DTC_MergeOneSetOfWIRStatusBit( eventStrgIndex, OldDTCStatusPtr, NewDTCStatusPtr );

        if( retMergeDTC == DEM_IRT_OK )
        {
            /* Gets EventId. */
            retGetEvent = Dem_CfgInfoPm_CnvEventCtrlIndexToEventId( EventCtrlIndex, &eventId );                         /* [GUD:RET:DEM_IRT_OK]EventCtrlIndex */

            if( retGetEvent == DEM_IRT_OK )
            {
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                eventKind = Dem_CfgInfoPm_GetEventKindOfMisfire_InEvtStrgGrp( eventStrgIndex );                     /* [GUD:RET:Not DEM_EVTKIND_TYPE_NON_OBD_EVENT] EventStrgIndex  */
                if( ( eventKind & DEM_EVTKIND_TYPE_MISFIRE_CAT_EVENT ) == DEM_EVTKIND_TYPE_MISFIRE_CAT_EVENT )
                {
                    Dem_Misfire_MergeWIRBitAtIndicatorBlinking_CAT( (*OldDTCStatusPtr), OldDTCStatusPtr );
                    Dem_Misfire_MergeWIRBitAtIndicatorBlinking_CAT( (*NewDTCStatusPtr), NewDTCStatusPtr );
                }
#endif  /*   ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )         */

                /* Converts statusOfDTC into the format of the user definition. */
                (void)Dem_DTC_TranslateStatusOfDTCToUserDefinedFormat( eventId, (*OldDTCStatusPtr), OldDTCStatusPtr, &resultOfCallOut );   /* no return check required */

                (void)Dem_DTC_TranslateStatusOfDTCToUserDefinedFormat( eventId, (*NewDTCStatusPtr), NewDTCStatusPtr, &resultOfCallOut );   /* no return check required */

            }
        }

        if( retGetEvent != DEM_IRT_OK )
        {
            /* Output a fixation value */
            (*OldDTCStatusPtr) = DEM_DTCSTATUS_BYTE_DEFAULT;
            (*NewDTCStatusPtr) = DEM_DTCSTATUS_BYTE_DEFAULT;
        }
    }
    return ;
}


/****************************************************************************/
/* Function Name | Dem_DTC_TranslateDTCStatusForOutput                      */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |                                                          */
/*               | [in/out] DTCStatusPtr :                                  */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_TranslateDTCStatusForOutput
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultGetEvent;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultMergeWir;
    VAR( Std_ReturnType, AUTOMATIC ) resultOfCallOut;
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( Dem_EventKindType, AUTOMATIC ) eventKind;
#endif  /*   ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )         */

    retVal          = DEM_IRT_NG;
    resultOfCallOut = E_NOT_OK;
    eventId         = ((Dem_EventIdType)0x0000U);

    /* Merge WIRStatus bit into bit7 of DTCStatus */
    resultMergeWir = Dem_DTC_MergeWIRStatusBit( EventStrgIndex, DTCStatusPtr );

    if( resultMergeWir == DEM_IRT_OK )
    {
        /* Gets EventId */
        resultGetEvent = Dem_CfgInfoPm_CnvEventStrgIndexToEventId( EventStrgIndex, &eventId );

        if( resultGetEvent == DEM_IRT_OK )
        {
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
            eventKind = Dem_CfgInfoPm_GetEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );                 /* [GUD:RET:Not DEM_EVTKIND_TYPE_NON_OBD_EVENT] EventStrgIndex  */
            if( ( eventKind & DEM_EVTKIND_TYPE_MISFIRE_CAT_EVENT ) == DEM_EVTKIND_TYPE_MISFIRE_CAT_EVENT )
            {
                Dem_Misfire_MergeWIRBitAtIndicatorBlinking_CAT( (*DTCStatusPtr), DTCStatusPtr );
            }
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )           */

            /* Converts statusOfDTC into the format of the user definition. */
            (void)Dem_DTC_TranslateStatusOfDTCToUserDefinedFormat( eventId, (*DTCStatusPtr), DTCStatusPtr, &resultOfCallOut );   /* no return check required */

            /* Output old and new statusOfDTC except bits out of the support. */
            retVal = DEM_IRT_OK;
        }
    }

    if( retVal != DEM_IRT_OK )
    {
        /* Output a fixation value */
        (*DTCStatusPtr) = DEM_DTCSTATUS_BYTE_DEFAULT;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DTC_TranslateDTCStatusForOutputByDTC                 */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |                                                          */
/*               | [in/out] DTCStatusPtr :                                  */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/*               |                                                          */
/* Notes         | Misfire DTC is not call this function.                   */
/*               | so, No need to process in case of MisfireDTC.            */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.based on Dem_DTC_TranslateDTCStatusForOutput(). */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_TranslateDTCStatusForOutputByDTC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultGetEvent;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultMergeWir;
    VAR( Std_ReturnType, AUTOMATIC ) resultOfCallOut;
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;

    retVal          = DEM_IRT_NG;
    resultOfCallOut = E_NOT_OK;
    eventId         = ((Dem_EventIdType)0x0000U);

    /* Merge WIRStatus bit into bit7 of DTCStatus */
    resultMergeWir = Dem_DTC_MergeWIRStatusBitByDTC( EventStrgIndex, DTCStatusPtr );

    if( resultMergeWir == DEM_IRT_OK )
    {
        /* Gets EventId */
        resultGetEvent = Dem_CfgInfoPm_CnvEventStrgIndexToEventId( EventStrgIndex, &eventId );

        if( resultGetEvent == DEM_IRT_OK )
        {
            /* Converts statusOfDTC into the format of the user definition. */
            (void)Dem_DTC_TranslateStatusOfDTCToUserDefinedFormat( eventId, (*DTCStatusPtr), DTCStatusPtr, &resultOfCallOut );   /* no return check required */

            /* Output old and new statusOfDTC except bits out of the support. */
            retVal = DEM_IRT_OK;
        }
    }

    if( retVal != DEM_IRT_OK )
    {
        /* Output a fixation value */
        (*DTCStatusPtr) = DEM_DTCSTATUS_BYTE_DEFAULT;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DTC_TranslateDTCStatusForOutput_NoMergeWIRBit        */
/* Description   | Get the DTC status of the record disabled from update.   */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in/out] DTCStatusPtr :                                  */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Status of DTC is OK                  */
/*               |        DEM_IRT_NG : DTC failed                           */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DTC_TranslateDTCStatusForOutput_NoMergeWIRBit
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;
    VAR( Std_ReturnType, AUTOMATIC ) resultOfCallOut;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultGetEvent;

    eventId         = ((Dem_EventIdType)0x0000U);

    resultGetEvent  =   Dem_CfgInfoPm_CnvEventStrgIndexToEventId( EventStrgIndex, &eventId );
    if( resultGetEvent == DEM_IRT_OK )
    {
        (void)Dem_DTC_TranslateStatusOfDTCToUserDefinedFormat( eventId, ( *DTCStatusPtr ), DTCStatusPtr, &resultOfCallOut ); /* no return check required */
    }
    return ;
}

/****************************************************************************/
/* Function Name | Dem_DTC_MergeWIRStatusBit                                */
/* Description   | Merge WIRStatus bit into bit7 of the DTCstatus           */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        Index of Event.                                   */
/*               | [in/out] DTCStatusPtr :                                  */
/*               |        DTC status before and after the change.           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : DTC status operation finished norma- */
/*               |        lcy.                                              */
/*               |        DEM_IRT_NG : DTC status operation failed.         */
/* Notes         | -                                                        */
/****************************************************************************/
static  FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_MergeWIRStatusBit
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetWIR;
    VAR( boolean, AUTOMATIC ) wirStatus;

    /* Local variable initialization */
    wirStatus = (boolean)FALSE;

    /* Gets WIRStatus corresponding to EventStrgIndex. */
    resultOfGetWIR = Dem_Ind_GetWIRStatus( EventStrgIndex, &wirStatus );

    if( resultOfGetWIR == DEM_IRT_OK )
    {
        /* Getting WIRStatus succeeded. */
        retVal = DEM_IRT_OK;

        if( wirStatus == (boolean)TRUE )
        {
            /* WIRStatus is TRUE. */

            /* Sets bit7 of DTCStatus in TRUE. */
            (*DTCStatusPtr) = Dem_DTC_SetWIRStatusBit( (*DTCStatusPtr) );
        }
    }
    else
    {
        /* Getting WIRStatus failed. */

        /* Just return a return value. */
        retVal = resultOfGetWIR;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DTC_MergeWIRStatusBitByDTC                           */
/* Description   | Merge WIRStatus bit into bit7 of the DTCstatus           */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        Index of Event.                                   */
/*               | [in/out] DTCStatusPtr :                                  */
/*               |        DTC status before and after the change.           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : DTC status operation finished norma- */
/*               |        lcy.                                              */
/*               |        DEM_IRT_NG : DTC status operation failed.         */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.based on Dem_DTC_MergeWIRStatusBit().        */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_MergeWIRStatusBitByDTC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetWIR;
    VAR( boolean, AUTOMATIC ) wirStatus;

    retVal  =   DEM_IRT_NG;

    /* Local variable initialization */
    wirStatus = (boolean)FALSE;

    /* Gets WIRStatus corresponding to EventStrgIndex. */
    resultOfGetWIR = Dem_Ind_GetWIRStatusByDTC( EventStrgIndex, &wirStatus );

    if( resultOfGetWIR == DEM_IRT_OK )
    {
        /* Getting WIRStatus succeeded. */
        retVal = DEM_IRT_OK;

        if( wirStatus == (boolean)TRUE )
        {
            /* WIRStatus is TRUE. */

            /* Sets bit7 of DTCStatus in TRUE. */
            (*DTCStatusPtr) = Dem_DTC_SetWIRStatusBit( (*DTCStatusPtr) );
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DTC_MergeOneSetOfWIRStatusBit                        */
/* Description   | Merge WIRStatus bit into bit7 of one set of DTCstatus    */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        Index of Event.                                   */
/*               | [in/out] DTCStatus1Ptr :                                 */
/*               |        The first DTC status.                             */
/*               | [in/out] DTCStatus2Ptr :                                 */
/*               |        The second DTC status.                            */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : DTC status operation finished norma- */
/*               |        lcy.                                              */
/*               |        DEM_IRT_NG : DTC status operation failed.         */
/* Notes         | -                                                        */
/****************************************************************************/
static  FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_MergeOneSetOfWIRStatusBit
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatus1Ptr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatus2Ptr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetWIR;
    VAR( boolean, AUTOMATIC ) wirStatus;

    /* Local variable initialization */
    wirStatus = (boolean)FALSE;

    /* Gets WIRStatus corresponding to EventStrgIndex. */
    resultOfGetWIR = Dem_Ind_GetWIRStatus( EventStrgIndex, &wirStatus );

    if( resultOfGetWIR == DEM_IRT_OK )
    {
        /* Getting WIRStatus succeeded. */
        retVal = DEM_IRT_OK;

        if( wirStatus == (boolean)TRUE )
        {
            /* WIRStatus is TRUE. */

            /* Sets bit7 of DTCStatus in TRUE. */
            (*DTCStatus1Ptr) = Dem_DTC_SetWIRStatusBit( (*DTCStatus1Ptr) );
            (*DTCStatus2Ptr) = Dem_DTC_SetWIRStatusBit( (*DTCStatus2Ptr) );
        }
        else
        {
            /* WIRStatus is FALSE. */
            /* No process */
        }
    }
    else
    {
        /* Getting WIRStatus failed. */

        /* Just return a return value. */
        retVal = resultOfGetWIR;
    }

    return retVal;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
