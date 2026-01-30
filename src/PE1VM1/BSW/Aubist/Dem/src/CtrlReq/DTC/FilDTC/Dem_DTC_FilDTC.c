/* Dem_DTC_FilDTC_c(v5-9-0)                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/


/****************************************************************************/
/* Object Name  | Dem/DTC_FilDTC/CODE                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../../cfg/Dem_Cfg.h"
#include "../../../../cfg/Dem_Data_Cfg.h"
#include "../../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../../inc/Dem_CmnLib_Control.h"
#include "../../../../inc/Dem_CmnLib_DTC_DTCStatus.h"
#include "../../../../inc/Dem_CmnLib_DTC_FilDTC.h"
#include "../../../../inc/Dem_Pm_DataCtl.h"
#include "../../../../inc/Dem_Pm_DTC.h"
#include "../../../../inc/Dem_Pm_Misfire.h"
#include "../../../../inc/Dem_Pm_DataAvl.h"
#include "../Dem_DTC_PFC.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_DTC_FILDTC_SEARCHINDEX_INITIAL       ((Dem_u08_OrderIndexType)0U)
#define DEM_DTC_FILDTC_SEARCHEVENTSTRGINDEX_INITIAL  ((Dem_u16_EventStrgIndexType)0U)
#define DEM_DTC_FILDTC_SEARCHEVENTCOUNT_INITIAL  ((Dem_u16_FilDTCSearchNumType)0U)

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

static FUNC( boolean, DEM_CODE ) Dem_DTC_JudgeExecSearchFilter
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_DTCKindType, AUTOMATIC ) DTCKind,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

static VAR( Dem_u16_FilDTCSearchNumType, DEM_VAR_NO_INIT )  Dem_EventSearchCnt;
static VAR( Dem_u16_EventStrgIndexType, DEM_VAR_NO_INIT )  Dem_FilteredDTCSearchEventStrgIndex;
#if ( DEM_OBD_SUPPORT == STD_ON )
static VAR( Dem_u08_OrderIndexType, DEM_VAR_NO_INIT )  Dem_FilteredDTCSearchIndex;
#endif  /* ( DEM_OBD_SUPPORT == STD_ON )    */


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_DTC_SetFilteredDTC                                   */
/* Description   | The function set the DTC filter.                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCFilterPtr :                                      */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DTC_SetFilteredDTC
(
    P2CONST( Dem_SetDTCFilterType, AUTOMATIC, AUTOMATIC ) DTCFilterPtr
)
{
#if ( DEM_OBD_SUPPORT == STD_ON )   /*  [FuncSw]    */
    Dem_FilteredDTCSearchIndex = DEM_DTC_FILDTC_SEARCHINDEX_INITIAL;
#endif  /* ( DEM_OBD_SUPPORT == STD_ON )            */
    Dem_FilteredDTCSearchEventStrgIndex = DEM_DTC_FILDTC_SEARCHEVENTSTRGINDEX_INITIAL;
    Dem_EventSearchCnt = DEM_DTC_FILDTC_SEARCHEVENTCOUNT_INITIAL;


    /*--------------------------------------------------------------------------*/
    /* Need to get exclusive [SchM_Enter_Dem_EventMemory].                      */
    /* These are the reasons why this function needs to get exclusive.          */
    /*  - This function call [DataMng] function directory.                      */
    /*  - This function called from SW-C/Dcm context.                           */
    /*  Waits to finish the exclusive section in the Dem_MainFunction context.  */
    SchM_Enter_Dem_EventMemory();    /* waits completion of updating Diag record data by Dem_MainFunction.      */
    SchM_Exit_Dem_EventMemory();
    /*--------------------------------------------------------------------------*/

    if( DTCFilterPtr->DTCOrigin == DEM_DTC_ORIGIN_PRIMARY_MEMORY )
    {
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
        /* prepare misfire filtering for SID19-42(UDS Format) / SID03,07(EDS format) */
        Dem_Misfire_SetFilteredDTC( DTCFilterPtr->DTCStatusMask, DTCFilterPtr->DTCKind, DTCFilterPtr->DTCFormat );
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */
    }
    else if( DTCFilterPtr->DTCOrigin == DEM_DTC_ORIGIN_PERMANENT_MEMORY )
    {
#if ( DEM_PFC_OUTPUT_DEMINTERNALPFC_TODCM_SUPPORT == STD_ON )  /*  [FuncSw]    */
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
        Dem_Misfire_SetFilteredDTCForPFC();
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */
#endif  /*   ( DEM_PFC_OUTPUT_DEMINTERNALPFC_TODCM_SUPPORT == STD_ON )         */
    }
    else
    {
        /*  no process.             */
    }

    return ;
}

#if ( DEM_PFC_OUTPUT_DEMINTERNALPFC_TODCM_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DTC_SearchFilteredPFC                                */
/* Description   | Gets the next filtered DTC and its DTC status.           */
/* Preconditions | Dem_DTC_SetDTCFilter being executed.                     */
/* Parameters    | [in] DTCFilterPtr :                                      */
/*               | [out] DTCValuePtr :                                      */
/*               |        Receives the DTC value in respective format of t- */
/*               |        he filter returned by this function.If the retur- */
/*               |        n value of the function is other than DEM_FILTER- */
/*               |        ED_OK this parameter does not contain valid data. */
/*               | [out] DTCStatusPtr :                                     */
/*               |        This parameter receives the status information o- */
/*               |        f the requested DTC.If the return value of the f- */
/*               |        unction call is other than DEM_STATUS_OK this pa- */
/*               |        rameter does not contain valid data.0x00...0xFF - */
/*               |        match DTCStatusMask as defined in ISO14229-1.     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Returned next filtered element       */
/*               |        DEM_IRT_NO_MATCHING_ELEMENT : No further element  */
/*               |         (matching the filter criteria) found             */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-8-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_SearchFilteredPFC
(
    P2CONST( Dem_SetDTCFilterType, AUTOMATIC, AUTOMATIC ) DTCFilterPtr,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) filteredEventStrgIndex; /* variable for commonization */
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) filteredDTCSearchIndexforPfc;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetMisfirePFC;
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )          */

    /*--------------------------------------------------------------------------*/
    /* Need to get exclusive [SchM_Enter_Dem_EventMemory].                      */
    /* These are the reasons why this function needs to get exclusive.          */
    /*  - This function call [DataMng] function directory.                      */
    /*  - This function called from SW-C/Dcm context.                           */
    /*  Waits to finish the exclusive section in the Dem_MainFunction context.  */
    SchM_Enter_Dem_EventMemory();    /* waits completion of updating Diag record data by Dem_MainFunction.      */
    SchM_Exit_Dem_EventMemory();
    /*--------------------------------------------------------------------------*/
    /* search DTC of PFC for SID0A, SID19-55 */
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    retGetMisfirePFC = Dem_Misfire_GetFilteredPFC( DTCFilterPtr->DTCFormat, DTCValuePtr, DTCStatusPtr );
    if( retGetMisfirePFC != DEM_IRT_NO_MATCHING_ELEMENT )
    {
        retVal = DEM_IRT_OK;
    }
    else
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )          */
    {
        filteredDTCSearchIndexforPfc = ( Dem_u08_PFCIndexType )Dem_FilteredDTCSearchIndex;
        retVal = Dem_DTC_GetFilteredPFC( DTCFilterPtr->DTCFormat, &filteredDTCSearchIndexforPfc, &filteredEventStrgIndex, DTCValuePtr, DTCStatusPtr );
        Dem_FilteredDTCSearchIndex = ( Dem_u08_OrderIndexType )filteredDTCSearchIndexforPfc;
    }

    if( retVal == DEM_IRT_OK )
    {
        /*------------------------------------------*/
        /*  convert to output statusOfDTC.          */
        /*------------------------------------------*/
        (*DTCStatusPtr) =   Dem_DTC_CnvDTCStatus_PmAvailabilityMask( (*DTCStatusPtr) );
    }

    return retVal;
}
#endif /* ( DEM_PFC_OUTPUT_DEMINTERNALPFC_TODCM_SUPPORT == STD_ON ) */

#if ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DTC_SearchFilteredEdsDTC_byOrderList                 */
/* Description   | Gets the next filtered DTC and its DTC status.           */
/* Preconditions | Dem_DTC_SetDTCFilter being executed.                     */
/* Parameters    | [in] DTCFilterPtr :                                      */
/*               | [out] DTCValuePtr :                                      */
/*               |        Receives the DTC value in respective format of t- */
/*               |        he filter returned by this function.If the retur- */
/*               |        n value of the function is other than DEM_FILTER- */
/*               |        ED_OK this parameter does not contain valid data. */
/*               | [out] DTCStatusPtr :                                     */
/*               |        This parameter receives the status information o- */
/*               |        f the requested DTC.If the return value of the f- */
/*               |        unction call is other than DEM_STATUS_OK this pa- */
/*               |        rameter does not contain valid data.0x00...0xFF - */
/*               |        match DTCStatusMask as defined in ISO14229-1.     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Returned next filtered element       */
/*               |        DEM_IRT_NO_MATCHING_ELEMENT : No further element  */
/*               |         (matching the filter criteria) found             */
/*               |        DEM_IRT_PENDING : The requested value is calcula- */
/*               |        ted asynchronously and currently not available. - */
/*               |        The caller can retry later.Only used by asynchro- */
/*               |        nous interfaces.                                  */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | rename from Dem_DTC_SearchFilteredDTC(v5-3-0).           */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_SearchFilteredEdsDTC_byOrderList
(
    P2CONST( Dem_SetDTCFilterType, AUTOMATIC, AUTOMATIC ) DTCFilterPtr,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    VAR( Dem_DTCSeverityType, AUTOMATIC ) dtcSeverity; /* variable for commonization */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) filteredDTCSearchIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) filteredEventStrgIndex; /* variable for commonization */
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetMisfireDTC;
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */

    /*--------------------------------------------------------------------------*/
    /* Need to get exclusive [SchM_Enter_Dem_EventMemory].                      */
    /* These are the reasons why this function needs to get exclusive.          */
    /*  - This function call [DataMng] function directory.                      */
    /*  - This function called from SW-C/Dcm context.                           */
    /*  Waits to finish the exclusive section in the Dem_MainFunction context.  */
    SchM_Enter_Dem_EventMemory();    /* waits completion of updating Diag record data by Dem_MainFunction.      */
    SchM_Exit_Dem_EventMemory();
    /*--------------------------------------------------------------------------*/

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    /* search DTC for SID03,07 */
    retGetMisfireDTC = Dem_Misfire_GetFilteredEdsDTC( DTCValuePtr );
    if( retGetMisfireDTC != DEM_IRT_NO_MATCHING_ELEMENT )
    {
        retVal = DEM_IRT_OK;
    }
    else
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */
    {
        filteredDTCSearchIndex = Dem_FilteredDTCSearchIndex;
        retVal = Dem_Data_GetFilteredObdDTC( &filteredDTCSearchIndex, DTCFilterPtr, &filteredEventStrgIndex, DTCValuePtr, DTCStatusPtr, &dtcSeverity );
        Dem_FilteredDTCSearchIndex = filteredDTCSearchIndex;
    }

    return retVal;
}
#endif  /* ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )              */


/****************************************************************************/
/* Function Name | Dem_DTC_SearchFilteredDTCAndSeverity                     */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCFilterPtr :                                      */
/*               | [out] DTCValuePtr :                                      */
/*               |                                                          */
/*               | [out] DTCStatusPtr :                                     */
/*               |                                                          */
/*               | [out] DTCSeverityPtr :                                   */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | This function called only DEM_DTC_FORMAT_UDS DTCFormat.  */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_SearchFilteredDTCAndSeverity    /* MISRA DEVIATION */
(
    P2CONST( Dem_SetDTCFilterType, AUTOMATIC, AUTOMATIC ) DTCFilterPtr,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr,
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, AUTOMATIC ) DTCSeverityPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) searchEventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) filteredDTCSearchEventStrgIndex;
    VAR( Dem_u16_FilDTCSearchNumType, AUTOMATIC ) searchLoopNumByCycle;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) loopMaxNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetDTCAndStatus;
    VAR( boolean, AUTOMATIC ) loopEndFlag;
    VAR( boolean, AUTOMATIC ) execSearchFlag;

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetMisfireDTC;
    VAR( boolean, AUTOMATIC ) execMisfireFlag;
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )          */

    /*--------------------------------------------------------------------------*/
    /* Need to get exclusive [SchM_Enter_Dem_EventMemory].                      */
    /* These are the reasons why this function needs to get exclusive.          */
    /*  - This function call [DataMng] function directory.                      */
    /*  - This function called from SW-C/Dcm context.                           */
    /*  Waits to finish the exclusive section in the Dem_MainFunction context.  */
    SchM_Enter_Dem_EventMemory();    /* waits completion of updating Diag record data by Dem_MainFunction.      */
    SchM_Exit_Dem_EventMemory();
    /*--------------------------------------------------------------------------*/

    retVal = DEM_IRT_NO_MATCHING_ELEMENT;

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    execMisfireFlag     = (boolean)FALSE;
    retGetMisfireDTC    = DEM_IRT_NO_MATCHING_ELEMENT;

    if ( Dem_FilteredDTCSearchEventStrgIndex == DEM_DTC_FILDTC_SEARCHEVENTSTRGINDEX_INITIAL )
    {
        if( DTCFilterPtr->FilterWithSeverity == (boolean)TRUE )
        {
            /* check DTC severity for SID19-42 */
            /* misfire DTC supports only DTCClass1 */
            if( ( DTCFilterPtr->DTCSeverityMask & DEM_DTC_CLASS_1 ) == DEM_DTC_CLASS_1 )
            {
                execMisfireFlag = (boolean)TRUE;
            }
        }
        else
        {
            /* search DTC severity for SID19-02,0A */
            execMisfireFlag = (boolean)TRUE;
        }

        if( execMisfireFlag == (boolean)TRUE )
        {
            /*  convert to output statusOfDTC is execute in Dem_Misfire_GetFilteredUdsDTCAndSeverity().          */
            retGetMisfireDTC = Dem_Misfire_GetFilteredUdsDTCAndSeverity( DTCFilterPtr->DTCStatusMask, DTCValuePtr, DTCStatusPtr, DTCSeverityPtr );
        }

        if ( retGetMisfireDTC == DEM_IRT_NO_MATCHING_ELEMENT )
        {
            /*  next search : normal events.            */
            Dem_FilteredDTCSearchEventStrgIndex = Dem_CfgInfoPm_GetNextEventStrgIndexAfterEventStrgIndexOfMisfire();
        }
    }

    if( retGetMisfireDTC != DEM_IRT_NO_MATCHING_ELEMENT )
    {
        retVal = DEM_IRT_OK;
    }
    else
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )          */
    {
        if( DTCFilterPtr->DTCKind == DEM_DTC_KIND_ALL_DTCS )
        {
            loopMaxNum = Dem_PrimaryMemEventStorageNum;
        }
        else
        {
            loopMaxNum = Dem_CfgInfoPm_GetMaxNumberOfOBDEvent();
        }
        searchLoopNumByCycle = Dem_FilDTCSearchLoopNumByCycle;
        loopEndFlag = (boolean)FALSE;
        filteredDTCSearchEventStrgIndex = Dem_FilteredDTCSearchEventStrgIndex;

        for( searchEventStrgIndex = filteredDTCSearchEventStrgIndex; searchEventStrgIndex < loopMaxNum; searchEventStrgIndex++ )
        {
            /* return pending, if search count exceed configuration value*/
            if( Dem_EventSearchCnt < searchLoopNumByCycle )
            {
                execSearchFlag  =   Dem_DTC_JudgeExecSearchFilter( searchEventStrgIndex, DTCFilterPtr->DTCKind, DTCFilterPtr->DTCOrigin );

                if ( execSearchFlag == (boolean)TRUE )
                {
                    /*----------------------------------*/
                    /*  get statusOfDTC and DTC         */
                    /*----------------------------------*/
                    retGetDTCAndStatus  =   Dem_DTC_GetDTCStatusAndUdsDTC_forFilDTC( searchEventStrgIndex, DTCFilterPtr->DTCStatusMask, DTCFilterPtr->FilterWithSeverity, DTCFilterPtr->DTCSeverityMask, DTCValuePtr, DTCStatusPtr, DTCSeverityPtr );
                    if ( retGetDTCAndStatus == DEM_IRT_OK )
                    {
                        /* update next search index */
                        Dem_FilteredDTCSearchEventStrgIndex = searchEventStrgIndex + (Dem_u16_EventStrgIndexType)1U;
                        retVal = DEM_IRT_OK;
                        loopEndFlag = (boolean)TRUE;

                        /*======================================================*/
                        /*  No reset of Dem_EventSearchCnt this timing.         */
                        /*  next call of this function, only return pending.    */
                        /*  Dem_EventSearchCnt is reset at return of pending.   */
                        /*======================================================*/

                    }
                }
                Dem_EventSearchCnt++;
            }
            else
            {
                /* update next search index */
                Dem_FilteredDTCSearchEventStrgIndex = searchEventStrgIndex;
                /* reset search counter for return pending */
                Dem_EventSearchCnt = DEM_DTC_FILDTC_SEARCHEVENTCOUNT_INITIAL;
                retVal = DEM_IRT_PENDING;
                loopEndFlag = (boolean)TRUE;
            }

            if( loopEndFlag == (boolean)TRUE )
            {
                break;
            }
        }

        if( loopEndFlag != (boolean)TRUE )
        {
            Dem_FilteredDTCSearchEventStrgIndex = loopMaxNum;
        }
    }

    return retVal;
}

#if ( DEM_OBD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DTC_SearchFilteredDTCAndSeverity_byOrderList         */
/* Description   | Gets the next filtered Fault ObdDTC and its severity     */
/* Preconditions | Dem_DTC_SetDTCFilter being executed.                     */
/* Parameters    | [in] DTCFilterPtr :                                      */
/*               | [out] DTCValuePtr :                                      */
/*               |        Receives the DTC value in respective format of t- */
/*               |        he filter returned by this function.If the retur- */
/*               |        n value of the function is other than DEM_FILTER- */
/*               |        ED_OK this parameter does not contain valid data. */
/*               | [out] DTCStatusPtr :                                     */
/*               |        This parameter receives the status information o- */
/*               |        f the requested DTC.If the return value of the f- */
/*               |        unction call is other than DEM_STATUS_OK this pa- */
/*               |        rameter does not contain valid data.0x00...0xFF - */
/*               |        match DTCStatusMask as defined in ISO14229-1.     */
/*               | [out] DTCSeverity :                                      */
/*               |        Receives the severity value returned by the func- */
/*               |        tion.If the return value of the function is othe- */
/*               |        r than DEM_FILTERED_OK this parameter does not c- */
/*               |        ontain valid data.                                */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Returned next filtered element       */
/*               |        DEM_IRT_NO_MATCHING_ELEMENT : No further element  */
/*               |         (matching the filter criteria) found             */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | rename from Dem_DTC_SearchFilteredFaultObdDTCAndSeverity(v5-3-0).           */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_SearchFilteredDTCAndSeverity_byOrderList
(
    P2CONST( Dem_SetDTCFilterType, AUTOMATIC, AUTOMATIC ) DTCFilterPtr,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr,
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, AUTOMATIC ) DTCSeverityPtr
)
{
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) filteredDTCSearchIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) filteredEventStrgIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetMisfireDTC;
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )          */

    /*--------------------------------------------------------------------------*/
    /* Need to get exclusive [SchM_Enter_Dem_EventMemory].                      */
    /* These are the reasons why this function needs to get exclusive.          */
    /*  - This function call [DataMng] function directory.                      */
    /*  - This function called from SW-C/Dcm context.                           */
    /*  Waits to finish the exclusive section in the Dem_MainFunction context.  */
    SchM_Enter_Dem_EventMemory();    /* waits completion of updating Diag record data by Dem_MainFunction.      */
    SchM_Exit_Dem_EventMemory();
    /*--------------------------------------------------------------------------*/

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    /* misfire DTC supports only DTCClass1 */
    if( ( DTCFilterPtr->DTCSeverityMask & DEM_DTC_CLASS_1 ) == DEM_DTC_CLASS_1 )
    {
        retGetMisfireDTC = Dem_Misfire_GetFilteredUdsDTCAndSeverity_AtEmiRelDTC( DTCValuePtr, DTCStatusPtr, DTCSeverityPtr );
    }
    else
    {
        retGetMisfireDTC = DEM_IRT_NO_MATCHING_ELEMENT;
    }

    if( retGetMisfireDTC != DEM_IRT_NO_MATCHING_ELEMENT )
    {
        retVal = DEM_IRT_OK;
    }
    else
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )          */
    {
        filteredDTCSearchIndex = Dem_FilteredDTCSearchIndex;
        retVal = Dem_Data_GetFilteredObdDTC( &filteredDTCSearchIndex, DTCFilterPtr, &filteredEventStrgIndex, DTCValuePtr, DTCStatusPtr, DTCSeverityPtr );
        Dem_FilteredDTCSearchIndex = filteredDTCSearchIndex;
    }
    return retVal;
}
#endif  /* ( DEM_OBD_SUPPORT == STD_ON )    */

/****************************************************************************/
/* Function Name | Dem_DTC_JudgeExecSearchFilter                            */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |                                                          */
/*               | [in] DTCKind :                                           */
/*               |                                                          */
/*               | [in] DTCOrigin :                                         */
/*               |                                                          */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : search OK.                                */
/*               |        FALSE : search NG.                                */
/* Notes         |                                                          */
/*      EventAvailable is NOT checked in this function.                     */
/*      At merge of statusOfDTC for output, EventAvailable is checked.      */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_DTC_JudgeExecSearchFilter
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_DTCKindType, AUTOMATIC ) DTCKind,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin       /* MISRA DEVIATION */
)
{
    VAR( boolean, AUTOMATIC ) execSearchFlag;
    VAR( boolean, AUTOMATIC ) eventOBDKind;
#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_FILDTC_SUPPORT == STD_ON ) /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) bDelegate;
#endif  /*  ( DEM_COMBINEDEVENT_ONRETRIEVAL_FILDTC_SUPPORT == STD_ON )     */

    execSearchFlag  =   (boolean)TRUE;
    if( DTCKind == DEM_DTC_KIND_EMISSION_REL_DTCS )
    {
        /*  check OBD event or not.     */
        eventOBDKind    =   Dem_CfgInfoPm_CheckEventKindOfOBD_InEvtStrgGrp( EventStrgIndex );
        if( eventOBDKind != (boolean)TRUE ) /*  nonOBD      */
        {
            execSearchFlag  =   (boolean)FALSE; /*  search skip.    */
        }
    }

#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_FILDTC_SUPPORT == STD_ON ) /*  [FuncSw]    */
    if ( execSearchFlag == (boolean)TRUE )
    {
        /*-----------------------------------------------------------------*/
        /*  this is DEM_COMBINEDEVENT_ONRETRIEVAL_FILDTC_SUPPORT job.      */
        /*-----------------------------------------------------------------*/

        /*  check the event is delegate of DTC.                     */
        bDelegate    =   Dem_CmbEvt_CheckDelegateEventStrgIndex_InDTCGrp( EventStrgIndex );
        if( bDelegate != (boolean)TRUE )
        {
            execSearchFlag  =   (boolean)FALSE; /*  search skip.    */
        }
    }
#endif  /*  ( DEM_COMBINEDEVENT_ONRETRIEVAL_FILDTC_SUPPORT == STD_ON )     */

    return execSearchFlag;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v3-0-0         :2019-05-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
