/* Dem_If_IUMPR_c(v5-10-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/If_IUMPR/CODE                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#if ( DEM_IUMPR_SUPPORT == STD_ON )

#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_Pm_Control_IUMPR.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"

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

/****************************************************************************/
/* Function Name | Dem_GetIUMPRDenCondition                                 */
/* Description   | In order to communicate the status of the (additional)   */
/*               | denominator conditions among the OBD relevant ECUs, the  */
/*               | API is used to retrieve the condition status from the    */
/*               | Dem of the ECU where the conditions are computed.        */
/* Preconditions | none                                                     */
/* Parameters    | [in] ConditionId :                                       */
/*               |          Identification of a IUMPR denominator           */
/*               |          condition ID.                                   */
/*               | [out] ConditionStatus :                                  */
/*               |          Status of the IUMPR denominator condition.      */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK     : Operation was successful.              */
/*               |        E_NOT_OK : Operation failed.                      */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetIUMPRDenCondition
(
    VAR( Dem_IumprDenomCondIdType, AUTOMATIC ) ConditionId,
    P2VAR( Dem_IumprDenomCondStatusType, AUTOMATIC, DEM_APPL_DATA ) ConditionStatus
)
{
    VAR( Std_ReturnType, AUTOMATIC )                retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )                         retGetDenCond;
    VAR( Dem_IumprDenomCondStatusType, AUTOMATIC )  wkConditionStatus;

    retVal = E_NOT_OK;

    if( ConditionStatus != NULL_PTR )
    {
        wkConditionStatus       =   (Dem_IumprDenomCondStatusType)0U;
        retGetDenCond = Dem_Control_GetIUMPRDenCondition( ConditionId, &wkConditionStatus );
        if( retGetDenCond == DEM_IRT_OK )
        {
            *ConditionStatus    = wkConditionStatus;
            retVal              = E_OK;
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_SetIUMPRDenCondition                                 */
/* Description   | In order to communicate the status of the (additional)   */
/*               | denominator conditions among the OBD relevant ECUs, the  */
/*               | API is used to forward the condition status to a Dem of  */
/*               | a particular ECU.                                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] ConditionId :                                       */
/*               |          Identification of a IUMPR denominator           */
/*               |          condition ID.                                   */
/*               | [in] ConditionStatus :                                   */
/*               |          Status of the IUMPR denominator condition.      */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK     : Operation was successful.              */
/*               |        E_NOT_OK : Operation failed.                      */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_SetIUMPRDenCondition
(
    VAR( Dem_IumprDenomCondIdType, AUTOMATIC )  ConditionId,
    VAR( Dem_IumprDenomCondStatusType, AUTOMATIC ) ConditionStatus
)
{
    VAR( Std_ReturnType, AUTOMATIC )    retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )             retSetDenCond;

    retVal = E_NOT_OK;

    retSetDenCond = Dem_Control_SetIUMPRDenCondition( ConditionId, ConditionStatus );
    if( retSetDenCond == DEM_IRT_OK )
    {
        retVal = E_OK;
    }

    return retVal;
}

#if ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_RepIUMPRDenRelease                                   */
/* Description   | Service is used to release a denominator of a specific   */
/*               | monitor.                                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] RatioID :                                           */
/*               |          Ratio Identifier reporting that specific        */
/*               |          denominator is released                         */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK     : Operation was successful.              */
/*               |        E_NOT_OK : Operation failed.                      */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_RepIUMPRDenRelease
(
    VAR( Dem_RatioIdType, AUTOMATIC ) RatioID
)
{
    VAR( Std_ReturnType, AUTOMATIC )    retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )             retRepDenRel;

    retVal = E_NOT_OK;

    retRepDenRel = Dem_Control_RepIUMPRDenRelease( RatioID );
    if( retRepDenRel == DEM_IRT_OK )
    {
        retVal = E_OK;
    }
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_RepIUMPRFaultDetect                                  */
/* Description   | Service for reporting that faults are possibly found     */
/*               | because all conditions are fullfilled.                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] RatioID :                                           */
/*               |          Ratio Identifier reporting that a respective    */
/*               |          monitor could have found a fault                */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK     : Operation was successful.              */
/*               |        E_NOT_OK : Operation failed.                      */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_RepIUMPRFaultDetect
(
    VAR( Dem_RatioIdType, AUTOMATIC ) RatioID
)
{
    VAR( Std_ReturnType, AUTOMATIC )    retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )             retRepFltDet;

    retVal = E_NOT_OK;

    retRepFltDet = Dem_Control_RepIUMPRFaultDetect( RatioID );
    if( retRepFltDet == DEM_IRT_OK )
    {
        retVal = E_OK;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_GetIUMPRDataByRatioId                                */
/* Description   | Get numerator and denominator for IUMPR.                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] RatioID :                                           */
/*               |          Ratio Identifier reporting that a respective    */
/*               |          monitor could have found a fault.               */
/*               | [out] NumeratorPtr   : Numerator.                        */
/*               | [out] DenominatorPtr : Denominator.                      */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK     : Operation was successful.              */
/*               |        E_NOT_OK : Operation failed.                      */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetIUMPRDataByRatioId
(
    VAR( Dem_RatioIdType, AUTOMATIC )           RatioID,
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA )   NumeratorPtr,
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA )   DenominatorPtr
)
{
    VAR( Std_ReturnType, AUTOMATIC )    retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )             retGetIumprData;
    VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC )            wkNumerator;
    VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC )            wkDenominator;

    retVal = E_NOT_OK;

    if( NumeratorPtr == NULL_PTR )
    {
        /* No Process */
    }
    else if( DenominatorPtr == NULL_PTR )
    {
        /* No Process */
    }
    else
    {
        wkNumerator     =   (Dem_u16_IUMPRCycleCounterType)0U;
        wkDenominator   =   (Dem_u16_IUMPRCycleCounterType)0U;
        retGetIumprData = Dem_Control_GetIUMPRDataByRatioId( (Dem_RatioIdType)RatioID, &wkNumerator, &wkDenominator );
        if( retGetIumprData == DEM_IRT_OK )
        {
            *NumeratorPtr   = (uint16)wkNumerator;
            *DenominatorPtr = (uint16)wkDenominator;
            retVal          = E_OK;
        }
    }
    return retVal;
}
#endif  /*   ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )      */

/****************************************************************************/
/* Function Name | Dem_GetIUMPRGeneralDenominator                           */
/* Description   | Get general denominator for IUMPR.                       */
/* Preconditions | none                                                     */
/* Parameters    | [out] GeneralDenominatorPtr : General Denominator.       */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK     : Operation was successful.              */
/*               |        E_NOT_OK : Operation failed.                      */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetIUMPRGeneralDenominator
(
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) GeneralDenominatorPtr
)
{
    VAR( Std_ReturnType, AUTOMATIC )    retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )             retGetVal;
    VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC )            wkGeneralDenominator;

    retVal = E_NOT_OK;

    if( GeneralDenominatorPtr != NULL_PTR )
    {
        wkGeneralDenominator    =   (Dem_u16_IUMPRCycleCounterType)0U;
        retGetVal   =   Dem_Control_GetIUMPRGeneralDenominator( &wkGeneralDenominator );
        if ( retGetVal == DEM_IRT_OK )
        {
            *GeneralDenominatorPtr  = (uint16)wkGeneralDenominator;
            retVal = E_OK;
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_GetIUMPRIGCycleCounter                               */
/* Description   | Get IG cycle counter for IUMPR.                          */
/* Preconditions | none                                                     */
/* Parameters    | [out] IGCycleCounterPtr : IG cycle counter.              */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK     : Operation was successful.              */
/*               |        E_NOT_OK : Operation failed.                      */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetIUMPRIGCycleCounter
(
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) IGCycleCounterPtr
)
{
    VAR( Std_ReturnType, AUTOMATIC )    retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )             retGetVal;
    VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC )            wkIGCycleCounter;

    retVal = E_NOT_OK;

    if( IGCycleCounterPtr != NULL_PTR )
    {
        wkIGCycleCounter    =   (Dem_u16_IUMPRCycleCounterType)0U;
        retGetVal   =   Dem_Control_GetIUMPRIGCycleCounter( &wkIGCycleCounter );
        if ( retGetVal == DEM_IRT_OK )
        {
            *IGCycleCounterPtr  = (uint16)wkIGCycleCounter;
            retVal              = E_OK;
        }
    }

    return retVal;
}

#if ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_GetIUMPRInfoTypeValue                                */
/* Description   | Service is used for requesting IUMPR data                */
/* Preconditions | none                                                     */
/* Parameters    | [out] IumprDataBufferPtr :                               */
/*               |          Buffer containing the contents.                 */
/*               | [out] IumprDataBufferSizePtr :                           */
/*               |          Buffer containing the number of data elements   */
/*               |          (as defined in ISO-15031-5)                     */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK     : Operation was successful.              */
/*               |        E_NOT_OK : Operation failed.                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_DcmGetInfoTypeValue08.         */
/*   v5-10-0     | no branch changed.                                       */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetIUMPRInfoTypeValue
(
    P2VAR( uint8 , AUTOMATIC, DEM_APPL_DATA )   IumprDataBufferPtr,
    P2VAR( uint8 , AUTOMATIC, DEM_APPL_DATA )   IumprDataBufferSizePtr
)
{
    VAR( Std_ReturnType, AUTOMATIC )                retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )    retInfoTypeValue;
    VAR( uint8, AUTOMATIC )                         dataSize;
    VAR( Dem_u08_IUMPRNODIValueType, AUTOMATIC )        nodiValue;
    VAR( Dem_u08_IUMPRGroupIndexType, AUTOMATIC )       nodiGroupNum;
    VAR( Dem_u08_IUMPRNODIOutputSizeType, AUTOMATIC )   nodiOutputSize;

    retVal = E_NOT_OK;

    if( IumprDataBufferPtr != NULL_PTR )
    {
        if( IumprDataBufferSizePtr != NULL_PTR )
        {
            Dem_CfgInfoPm_GetNODIInfo( &nodiValue, &nodiGroupNum, &nodiOutputSize );
            /*  set datasize and NODI size.     */
            dataSize                = nodiOutputSize + DEM_IUMPR_NODI_SIZE;
            retInfoTypeValue        = Dem_Control_GetInfoTypeValue( IumprDataBufferPtr, &dataSize );
            if( retInfoTypeValue == DEM_IRT_OK )
            {
                *IumprDataBufferSizePtr  = dataSize;
                retVal                   = E_OK;
            }
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_GetEventIdByRatioId                                  */
/* Description   | Get EventId for IUMPR.                                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] RatioID :                                           */
/*               |          Ratio Identifier reporting that a respective    */
/*               |          monitor could have found a fault.               */
/*               | [out] EventIdPtr   : EventId.                            */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK     : Operation was successful.              */
/*               |        E_NOT_OK : Operation failed.                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_GetIUMPRDataByRatioId.         */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetEventIdByRatioId
(
    VAR( Dem_RatioIdType, AUTOMATIC )                   RatioID,
    P2VAR( Dem_EventIdType, AUTOMATIC, DEM_APPL_DATA )  EventIdPtr
)
{
    VAR( Std_ReturnType, AUTOMATIC )    retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )             retGetIumprData;
    VAR( Dem_EventIdType, AUTOMATIC )   eventId;

    retVal = E_NOT_OK;

    if( EventIdPtr == NULL_PTR )
    {
        /* No Process */
    }
    else
    {
        eventId   =   DEM_EVENTID_INVALID;
        retGetIumprData = Dem_Control_GetEventIdByRatioId( RatioID, &eventId );
        if( retGetIumprData == DEM_IRT_OK )
        {
            *EventIdPtr   = eventId;
            retVal          = E_OK;
        }
    }
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_GetRatioIdByEventId                                  */
/* Description   | Get RatioId list by EventId.                             */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventID :                                           */
/*               |        Identification of an event by assigned EventId    */
/*               | [out] RatioIdBufferPtr :  RatioId list.                  */
/*               | [in/out] RatioIdNumPtr :  RatioId list number.           */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Operation was successful                   */
/*               |        E_NOT_OK : Operation failed                       */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_GetEventIdWithPendingDTC.      */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetRatioIdByEventId
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( Dem_RatioIdType, AUTOMATIC, DEM_APPL_DATA ) RatioIdBufferPtr,
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) RatioIdNumPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalRetVal;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( Dem_RatioIdType, AUTOMATIC ) ratioIdNum;

    retVal = E_NOT_OK;

    if( RatioIdBufferPtr == NULL_PTR )
    {
        /* No Process */
    }
    else if( RatioIdNumPtr == NULL_PTR )
    {
        /* No Process */
    }
    else
    {
        ratioIdNum      =   (Dem_RatioIdType)*RatioIdNumPtr;
        internalRetVal  =   Dem_Control_GetRatioIdByEventId( EventId, RatioIdBufferPtr, &ratioIdNum );
        *RatioIdNumPtr  =   (uint16)ratioIdNum;

        if( internalRetVal == DEM_IRT_OK )
        {
            retVal = E_OK;
        }
        else if( internalRetVal == DEM_IRT_WRONG_BUFFERSIZE )
        {
            retVal = DEM_BUFFER_TOO_SMALL;
        }
        else
        {
            /*  E_NOT_OK.   */
        }
    }
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_JudgeMinimumRatioThanCurrentRatio                    */
/* Description   | Compare Ratio [para1/para2] > [para3/para4].             */
/* Preconditions | none                                                     */
/* Parameters    | [in] CurrentNumerator   : Current Numerator.             */
/*               | [in] CurrentDenominator : Current Denominator.           */
/*               | [in] TargetNumerator    : Target Numerator.              */
/*               | [in] TargetDenominator  : Target Denominator.            */
/*               | [out] JudgeResultPtr   : result.                         */
/*               |        TRUE  : Current >  Target .                       */
/*               |        FALSE : Current <= Target.                        */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Operation was successful                   */
/*               |        E_NOT_OK : Operation failed                       */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_JudgeMinimumRatioThanCurrentRatio
(
    VAR( uint16, AUTOMATIC )    CurrentNumerator,
    VAR( uint16, AUTOMATIC )    CurrentDenominator,
    VAR( uint16, AUTOMATIC )    TargetNumerator,
    VAR( uint16, AUTOMATIC )    TargetDenominator,
    P2VAR( boolean, AUTOMATIC, DEM_APPL_DATA ) JudgeResultPtr
)
{
    VAR( Std_ReturnType, AUTOMATIC ) retVal;

    retVal = E_NOT_OK;

    if( JudgeResultPtr != NULL_PTR )
    {
        *JudgeResultPtr  =   Dem_Control_JudgeMinThanCurrentRatio( (Dem_u16_IUMPRCycleCounterType)CurrentNumerator, (Dem_u16_IUMPRCycleCounterType)CurrentDenominator, (Dem_u16_IUMPRCycleCounterType)TargetNumerator, (Dem_u16_IUMPRCycleCounterType)TargetDenominator );
        retVal = E_OK;
    }
    return retVal;
}

#endif  /*   ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )      */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>



#endif  /* ( DEM_IUMPR_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
