/* Dem_Control_IUMPR_c(v5-3-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_IUMPR/CODE                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#if ( DEM_IUMPR_SUPPORT == STD_ON )

#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_CmnLib_Control_AsyncReq.h"
#include "../../../inc/Dem_CmnLib_AsyncReqTable.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_Pm_Control_IUMPR.h"
#include "../../../inc/Dem_Pm_IUMPR.h"
#include "../../../usr/Dem_SavedZone_Callout.h"
#include "Dem_Control_local.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_CTL_IUMPR_CYC_COUNTER_MIN                       ((Dem_u16_IUMPRCycleCounterType)0x0000U)
#define DEM_CTL_IUMPR_CONDITIONID_SHIFT_BIT                 ((uint8)0x08U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

static FUNC( void, DEM_CODE ) Dem_Control_GenIUMPRDenCondQueParam
(
    VAR( Dem_IumprDenomCondIdType, AUTOMATIC )      ConditionId,
    VAR( Dem_IumprDenomCondStatusType, AUTOMATIC )  ConditionStatus,
    P2VAR( uint16, AUTOMATIC, AUTOMATIC )           QueuingParamPtr
);

static FUNC( void, DEM_CODE ) Dem_Control_DecIUMPRDenCondQueParam
(
    VAR( uint16, AUTOMATIC )                                    QueuingParam,
    P2VAR( Dem_IumprDenomCondIdType, AUTOMATIC, AUTOMATIC )     ConditionIdPtr,
    P2VAR( Dem_IumprDenomCondStatusType, AUTOMATIC, AUTOMATIC ) ConditionStatusPtr
);


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

static VAR( Dem_u16_IUMPRCycleCounterType, DEM_VAR_NO_INIT )   Dem_CtlCalculateIUMPRCycleCounter;
static VAR( boolean, DEM_VAR_NO_INIT )  Dem_CtlCalculateIUMPRComplete;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_Control_GetInfoTypeValue                             */
/* Description   | Service is used for requesting IUMPR data according to   */
/*               | InfoType 0x08.                                           */
/* Preconditions | none                                                     */
/* Parameters    | [out] IumprdataPtr :                                     */
/*               |         Buffer containing the contents of InfoType .     */
/*               |         The buffer is provided by the Dcm.               */
/*               | [inout] BuffSizePtr :                                    */
/*               |          Buffer containing the number of data elements   */
/*               |          (as defined in ISO-15031-5) and contents of     */
/*               |          InfoType 0x08.                                  */
/*               |          The buffer is provided by the Dcm.              */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Operation was successful.            */
/*               |        DEM_IRT_NG : Operation failed.                    */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetInfoTypeValue
(
    P2VAR( uint8 , AUTOMATIC, DEM_APPL_DATA )   IumprdataPtr,
    P2VAR( uint8 , AUTOMATIC, AUTOMATIC )       BuffSizePtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        retVal = Dem_IUMPR_GetInfoTypeValue( IumprdataPtr, BuffSizePtr );
    }
    else
    {
        retVal = Dem_IUMPR_GetInitInfoTypeValue( IumprdataPtr, BuffSizePtr );
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Control_GetIUMPRDenCondition                         */
/* Description   | In order to communicate the status of the (additional)   */
/*               | denominator conditions among the OBD relevant ECUs, the  */
/*               | API is used to retrieve the condition status from the    */
/*               | Dem of the ECU where the conditions are computed.        */
/* Preconditions | none                                                     */
/* Parameters    | [in] ConditionId :                                       */
/*               |          Identification of a IUMPR denominator           */
/*               |          condition ID.                                   */
/*               | [out] ConditionStatusPtr :                               */
/*               |          Status of the IUMPR denominator condition.      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Operation was successful.            */
/*               |        DEM_IRT_NG : Operation failed.                    */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetIUMPRDenCondition
(
    VAR( Dem_IumprDenomCondIdType, AUTOMATIC )                  ConditionId,
    P2VAR( Dem_IumprDenomCondStatusType, AUTOMATIC, AUTOMATIC ) ConditionStatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;

    retVal = DEM_IRT_NG;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        retVal = Dem_IUMPR_GetIUMPRDenCondition( ConditionId, ConditionStatusPtr );
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_GetIUMPRGeneralDenominator                           */
/* Description   | Get general denominator for IUMPR.                       */
/* Preconditions | none                                                     */
/* Parameters    | [out] GeneralDenominatorPtr : General Denominator.       */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Operation was successful.            */
/*               |        DEM_IRT_NG : Operation failed.                    */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetIUMPRGeneralDenominator
(
    P2VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC, AUTOMATIC )   GeneralDenominatorPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )     checkStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )     retVal;

    retVal = DEM_IRT_NG;
    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        Dem_IUMPR_GetGeneralDenominator( GeneralDenominatorPtr );
        retVal = DEM_IRT_OK;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Control_GetIUMPRIGCycleCounter                       */
/* Description   | Get IG cycle counter for IUMPR.                          */
/* Preconditions | none                                                     */
/* Parameters    | [out] IGCycleCounterPtr : IG cycle counter.              */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Operation was successful.            */
/*               |        DEM_IRT_NG : Operation failed.                    */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetIUMPRIGCycleCounter
(
    P2VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC, AUTOMATIC )   IGCycleCounterPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )     checkStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )     retVal;

    retVal = DEM_IRT_NG;
    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        Dem_IUMPR_GetIGCycleCounter( IGCycleCounterPtr );
        retVal = DEM_IRT_OK;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Control_SetIUMPRDenCondition                         */
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
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Operation was successful.            */
/*               |        DEM_IRT_NG : Operation failed.                    */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetIUMPRDenCondition
(
    VAR( Dem_IumprDenomCondIdType, AUTOMATIC )      ConditionId,
    VAR( Dem_IumprDenomCondStatusType, AUTOMATIC )  ConditionStatus
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )     retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )     checkStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )     checkCond;
    VAR( uint16, AUTOMATIC )    QueingParameter;

    retVal = DEM_IRT_NG;

    checkStatus = Dem_AsyncReq_JudgeReqCondition( DEM_ASYNCREQ_SET_IUMPR_DENCONDITION, DEM_ASYNCREQ_PARAM_INDEX_INVALID, DEM_ASYNCREQ_PARAM_STATUS_INVALID );
    if( checkStatus == DEM_IRT_OK )
    {
        checkCond = Dem_IUMPR_CheckCondSettingParameter( ConditionId, ConditionStatus );

        if( checkCond == DEM_IRT_OK )
        {
            Dem_Control_GenIUMPRDenCondQueParam( ConditionId, ConditionStatus, &QueingParameter );
            retVal = Dem_AsyncReq_Enqueue( DEM_ASYNCREQ_SET_IUMPR_DENCONDITION, QueingParameter, DEM_ASYNCREQ_PARAM_STATUS_INVALID );
        }
    }

    return retVal;
}



/****************************************************************************/
/****************************************************************************/


/****************************************************************************/
/* Function Name | Dem_Control_NotifyIUMPRDenCondition                      */
/* Description   | Asynchronous processing function of SetIUMPRDenCondition.*/
/* Preconditions | none                                                     */
/* Parameters    | [in] Index       : Condition Queuing Parameter.          */
/*               | [in] Status      :                                       */
/*               | [in] DataBuffPtr :                                       */
/* Return Value  | Dem_u08_AsyncExecReturnType                              */
/*               |       : See the description of the return value of       */
/*               |         "DemAsyncReqFncPTR" in Dem_CmnLib_Control_AsyncReq.h.   */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_Control_NotifyIUMPRDenCondition
(
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status,                     /* MISRA DEVIATION */
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr    /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_AsyncExecReturnType, AUTOMATIC ) retVal;
    VAR( Dem_IumprDenomCondIdType, AUTOMATIC ) ConditionId;
    VAR( Dem_IumprDenomCondStatusType, AUTOMATIC ) ConditionStatus;

    /* Set return value. */
    /* Fault record is not updated, No need re-generate orderlist, Continue asynchronous processing. */
    retVal = ( DEM_ASYNCRET_NOUPD_FR | DEM_ASYNCRET_NONEED_REGEN_ODR | DEM_ASYNCRET_CONTINUE_ASYNC_PROC );

    Dem_Control_DecIUMPRDenCondQueParam( Index, &ConditionId, &ConditionStatus );

    /*--------------------------------------*/
    /*  notify SAVED_ZONE update - start.   */
    Dem_NotifySavedZoneUpdate_Enter();      /*  notify start :  savedzone area will be update.  */
    /*--------------------------------------*/

    Dem_IUMPR_SetIUMPRDenCondition( ConditionId, ConditionStatus );

    /*--------------------------------------*/
    /*  notify SAVED_ZONE update - end.     */
    Dem_NotifySavedZoneUpdate_Exit();       /*  notify end :  savedzone area will be update.    */
    /*--------------------------------------*/

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Control_InitIUMPRInfo                                */
/* Description   | Initial IUMPR Information.                               */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_InitIUMPRInfo
(void)
{

    Dem_CtlCalculateIUMPRCycleCounter   = DEM_CTL_IUMPR_CYC_COUNTER_MIN;
    Dem_CtlCalculateIUMPRComplete       = (boolean)TRUE;

    return;
}


/****************************************************************************/
/* Function Name | Dem_Control_UpdateIUMPRProcess                           */
/* Description   | Processes IUMPR updating.                                */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | This function is in Dem_MainFunction process.            */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_UpdateIUMPRProcess
(void)
{
    VAR( boolean, AUTOMATIC )   compUpdate;
    VAR( boolean, AUTOMATIC )   execUpdate;
    VAR( boolean, AUTOMATIC )   firstTime;
    VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC )    demIUMPRCalculateDivideCycleCount;

    Dem_CtlCalculateIUMPRCycleCounter = Dem_CtlCalculateIUMPRCycleCounter + (Dem_u16_IUMPRCycleCounterType)1U;
    execUpdate  = (boolean)FALSE;
    compUpdate  = (boolean)FALSE;
    firstTime   = (boolean)FALSE;

    demIUMPRCalculateDivideCycleCount   = Dem_IUMPRCalculateDivideCycleCount;
    if (Dem_CtlCalculateIUMPRCycleCounter >= demIUMPRCalculateDivideCycleCount )
    {
        Dem_CtlCalculateIUMPRCycleCounter   = DEM_CTL_IUMPR_CYC_COUNTER_MIN;
        execUpdate                          = (boolean)TRUE;
        firstTime                           = (boolean)TRUE;
    }
    if( Dem_CtlCalculateIUMPRComplete == (boolean)FALSE )
    {
        execUpdate                          = (boolean)TRUE;
    }

    if( execUpdate == (boolean)TRUE )
    {
        Dem_CtlCalculateIUMPRComplete       = (boolean)FALSE;

        /*--------------------------------------*/
        /*  notify SAVED_ZONE update - start.   */
        Dem_NotifySavedZoneUpdate_Enter();      /*  notify start :  savedzone area will be update.  */
        /*--------------------------------------*/

        Dem_IUMPR_UpdateIUMPRProcess( firstTime, &compUpdate );

        /*--------------------------------------*/
        /*  notify SAVED_ZONE update - end.     */
        Dem_NotifySavedZoneUpdate_Exit();       /*  notify end :  savedzone area will be update.    */
        /*--------------------------------------*/

        if( compUpdate == (boolean)TRUE )
        {
            Dem_CtlCalculateIUMPRComplete   = (boolean)TRUE;
        }
    }

    return;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dem_Control_GenIUMPRDenCondQueParam                      */
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
/*               | [out] QueuingParamPtr :                                  */
/*               |          Qeuing Parameter.                               */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_GenIUMPRDenCondQueParam
(
    VAR( Dem_IumprDenomCondIdType, AUTOMATIC )      ConditionId,
    VAR( Dem_IumprDenomCondStatusType, AUTOMATIC )  ConditionStatus,
    P2VAR( uint16, AUTOMATIC, AUTOMATIC )           QueuingParamPtr
)
{
    VAR( uint16, AUTOMATIC )                    condQueParam;

    condQueParam        = (uint16)( (uint16)ConditionId << DEM_CTL_IUMPR_CONDITIONID_SHIFT_BIT );
    condQueParam        = (uint16)( condQueParam | (uint16)ConditionStatus );
    *QueuingParamPtr    = condQueParam;

    return;
}


/****************************************************************************/
/* Function Name | Dem_Control_DecIUMPRDenCondQueParam                      */
/* Description   | In order to communicate the status of the (additional)   */
/*               | denominator conditions among the OBD relevant ECUs, the  */
/*               | API is used to forward the condition status to a Dem of  */
/*               | a particular ECU.                                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] ConditionQueuingParam :                             */
/*               |          Condition Queuing Parameter.                    */
/*               | [out] ConditionIdPtr :                                   */
/*               |          Identification of a IUMPR denominator           */
/*               |          condition ID.                                   */
/*               | [out] ConditionStatusPtr :                               */
/*               |          Status of the IUMPR denominator condition.      */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_DecIUMPRDenCondQueParam
(
    VAR( uint16, AUTOMATIC )                                    QueuingParam,
    P2VAR( Dem_IumprDenomCondIdType, AUTOMATIC, AUTOMATIC )     ConditionIdPtr,
    P2VAR( Dem_IumprDenomCondStatusType, AUTOMATIC, AUTOMATIC ) ConditionStatusPtr
)
{
    VAR( Dem_IumprDenomCondIdType, AUTOMATIC )                  decCondId;
    VAR( Dem_IumprDenomCondStatusType, AUTOMATIC )              decCondStatus;

    decCondStatus       = (Dem_IumprDenomCondStatusType)QueuingParam;
    decCondId           = (Dem_IumprDenomCondIdType)( QueuingParam >> DEM_CTL_IUMPR_CONDITIONID_SHIFT_BIT );

    *ConditionIdPtr     = decCondId;
    *ConditionStatusPtr = decCondStatus;

    return;
}


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
/****************************************************************************/

/**** End of File ***********************************************************/
