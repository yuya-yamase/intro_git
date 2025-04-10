/* Dem_Ind_MI_B1Counter_WWH_c(v5-5-0)                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Ind_MI_B1Counter_WWH/CODE                             */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
#include "../../../../cfg/Dem_Cfg.h"
#include "../../../../cfg/Dem_WWHObd_Cfg.h"
#include "../../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../../inc/Dem_CmnLib_Control.h"
#include "../../../../inc/Dem_Pm_Ind.h"
#include "../../../../inc/Dem_Pm_Ind_MI.h"
#include "../../../../inc/Dem_Pm_DataAvl.h"
#include "../../../../inc/Dem_Rc_IndMIMng.h"
#include "../../../../inc/Dem_Rc_DataMng.h"
#include "../../../../inc/Dem_Pm_DTC_PFC.h"
#include "../../../../inc/Dem_Pm_DataCtl_OBD.h"
#include "../../../../inc/Dem_CmnLib_DataElement.h"
#include "../../../../inc/Dem_CmnLib_DTC_DTCStatus.h"
#include "Dem_Ind_MI_local.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

#define DEM_WWHOBD_CALCULATION_DATASIZE_TIMESESBY3MIN   ((uint8)1U)
#define DEM_WWHOBD_READDATAELEMENT_DATAPOS0             ((uint8)0U)
#define DEM_B1COUNTER_MAX                               ((Dem_u32_B1CounterType)0xFFFFFFFFU)

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

static FUNC( void, DEM_CODE ) Dem_IndMI_CalcB1Counter
(
    VAR( Dem_u32_B1CounterType, AUTOMATIC ) B1CounterCalc
);

static FUNC( void, DEM_CODE ) Dem_IndMI_B1CounterThresholdReached
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);

static FUNC( void, DEM_CODE ) Dem_IndMI_SetIndMIIndexToIndMIIndexList
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) IndMIIndex
);

static FUNC( void, DEM_CODE ) Dem_IndMI_ClearIndMIIndexFromIndMIIndexList
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IndMI_GetIndMIIndexFromIndMIIndexList
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u16_IndMIIndexType, AUTOMATIC, AUTOMATIC ) IndMIIndexPtr
);


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

static VAR( Dem_u16_IndMIIndexType, DEM_VAR_NO_INIT ) Dem_IndMI_EventStrgIndexToIndMIIndexList[ DEM_CLASS_B1_EVENTSTORAGE_NUM ];

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_IndMI_GetB1Counter                                   */
/* Description   | Get B1 Counter.                                          */
/* Preconditions | none                                                     */
/* Parameters    | [out] B1Counter      : B1Counter.                        */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IndMI_GetB1Counter
(
    P2VAR( Dem_u32_B1CounterType, AUTOMATIC, AUTOMATIC ) B1CounterPtr
)
{
    VAR( Dem_u32_B1CounterType, AUTOMATIC )         b1Counter;
    VAR( Dem_u32_B1CounterType, AUTOMATIC )         b1CounterCalc;
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) indMIIndex;
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) indMIMaxNumberOfClassB1Event;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndexRecord;
    VAR( boolean, AUTOMATIC ) availableStatus;

    b1CounterCalc   =   (Dem_u32_B1CounterType)0U;

    /*  get maximum value.          */
    indMIMaxNumberOfClassB1Event = Dem_WWHOBDMaxNumberOfClassB1Event;
    for ( indMIIndex = (Dem_u16_IndMIIndexType)0U; indMIIndex < indMIMaxNumberOfClassB1Event; indMIIndex++ )
    {
        (void)Dem_IndMIMng_GetB1Counter( indMIIndex, &eventStrgIndexRecord, &b1Counter ); /* no return check required */
        if ( eventStrgIndexRecord != DEM_EVENTSTRGINDEX_INVALID )
        {
            availableStatus = Dem_DataAvl_GetEvtAvl_InEvtStrgGrp( eventStrgIndexRecord );
            if ( availableStatus == (boolean)TRUE )
            {
                if ( b1CounterCalc < b1Counter )
                {
                    b1CounterCalc   =   b1Counter;
                }
            }
        }
    }

    /*  shift bit.  per 3 minutes => per 6 minutes.         */
    b1CounterCalc   =   b1CounterCalc >> ( Dem_u32_B1CounterType )1U;

    *B1CounterPtr   =   b1CounterCalc;

    return ;
}

/****************************************************************************/
/* Function Name | Dem_IndMI_GetB1CounterByEventStrgIndex_By6Minutes        */
/* Description   | Get B1 Counter(by 6min.) by EventStrgIndex.              */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventStrgIndex     : EventStrgIndex.               */
/*               | [out] B1Counter6MinPtr   : B1Counter.                    */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IndMI_GetB1CounterByEventStrgIndex_By6Minutes
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u16_B1CounterOutputType, AUTOMATIC, AUTOMATIC ) B1Counter6MinPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )    retVal;
    VAR( Dem_u32_B1CounterType, AUTOMATIC )         b1CounterCalc3Min;

    retVal  =   Dem_IndMI_GetB1CounterByEventStrgIndex_By3Minutes( EventStrgIndex, &b1CounterCalc3Min );

    if ( retVal == DEM_IRT_OK )
    {
        /*  shift bit.  per 3 minutes => per 6 minutes.         */
        b1CounterCalc3Min   =   b1CounterCalc3Min >> ( Dem_u32_B1CounterType )1U;
        if ( b1CounterCalc3Min > DEM_B1COUNTER_OUTPUT_MAX )
        {
            *B1Counter6MinPtr = ( Dem_u16_B1CounterOutputType )DEM_B1COUNTER_OUTPUT_MAX;
        }
        else
        {
            *B1Counter6MinPtr   =   ( Dem_u16_B1CounterOutputType )b1CounterCalc3Min;
        }
    }
    else
    {
        *B1Counter6MinPtr   =   ( Dem_u16_B1CounterOutputType )0U;
    }

    return ;
}

/****************************************************************************/
/* Function Name | Dem_IndMI_GetB1CounterByEventStrgIndex_By3Minutes        */
/* Description   | Get B1 Counter(by 3min.) by EventStrgIndex.              */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventStrgIndex     : EventStrgIndex.               */
/*               | [out] B1Counter3MinPtr   : B1Counter.                    */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : successful.                          */
/*               |        DEM_IRT_NG : failed.                              */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IndMI_GetB1CounterByEventStrgIndex_By3Minutes
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u32_B1CounterType, AUTOMATIC, AUTOMATIC ) B1Counter3MinPtr
)
{
    VAR( Dem_u32_B1CounterType, AUTOMATIC )         b1CounterCalc;
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC )        indMIIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC )    eventStrgIndexRecord; /* dummy parameter */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )    retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )    retGetIndMIIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )    retGetB1Counter;

    retVal          =   DEM_IRT_NG;
    b1CounterCalc   =   (Dem_u32_B1CounterType)0U;

    /*  get value.          */
    retGetIndMIIndex = Dem_IndMI_GetIndMIIndexFromIndMIIndexList( EventStrgIndex, &indMIIndex );
    if ( retGetIndMIIndex == DEM_IRT_OK )
    {
        retGetB1Counter = Dem_IndMIMng_GetB1Counter( indMIIndex, &eventStrgIndexRecord, &b1CounterCalc ); /* indMIIndex range check is implemented in this function. */

        if ( retGetB1Counter == DEM_IRT_OK )
        {
            *B1Counter3MinPtr   =   b1CounterCalc;
            retVal              =   DEM_IRT_OK;
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_IndMI_CheckB1CounterThresholdReached                 */
/* Description   | Check B1Counter value reached threshold.                 */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventStrgIndex : EventStrgIndex.                   */
/*               | [out] B1CounterThresholdReachedPtr                       */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : B1Counter exists.                    */
/*               |        DEM_IRT_NG : B1Counter doesn't exist.             */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IndMI_CheckB1CounterThresholdReached
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) B1CounterThresholdReachedPtr
)
{
    VAR( Dem_u32_B1CounterType, AUTOMATIC )  b1CounterThreshold;
    VAR( Dem_u32_B1CounterType, AUTOMATIC )  b1Counter;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) getB1Counter;
    VAR( boolean, AUTOMATIC ) b1CounterThresholdReached;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    b1CounterThresholdReached = (boolean)FALSE;
    retVal = DEM_IRT_NG;

    b1CounterThreshold = Dem_CfgInfoPm_GetB1CounterThreshold();
    getB1Counter = Dem_IndMI_GetB1CounterByEventStrgIndex_By3Minutes( EventStrgIndex, &b1Counter );

    if ( getB1Counter == DEM_IRT_OK )
    {
        if ( b1Counter >= b1CounterThreshold )
        {
            b1CounterThresholdReached = (boolean)TRUE;
        }
        retVal = DEM_IRT_OK;
    }

    *B1CounterThresholdReachedPtr = b1CounterThresholdReached;

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_IndMI_UpdateB1Counter                                */
/* Description   | calculate B1 counter.                                    */
/* Preconditions |                                                          */
/* Parameters    | none.                                                    */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IndMI_UpdateB1Counter
( void )
{
    VAR( Std_ReturnType, AUTOMATIC ) resultOfCallback;
    P2CONST( AB_83_ConstV Dem_DataElementClassType, AUTOMATIC, DEM_CONFIG_DATA ) dataElementClassPtr;
    VAR( Dem_u16_DataElementClassIndexType, AUTOMATIC ) dataElementClassIndex;
    VAR( Dem_u16_DataElementClassIndexType, AUTOMATIC ) elementClassTableNum;
    VAR( uint8, AUTOMATIC ) dataBuffer[DEM_WWHOBD_CALCULATION_DATASIZE_TIMESESBY3MIN];
    VAR( Dem_u32_B1CounterType, AUTOMATIC ) b1CounterCalc;
    VAR( boolean, AUTOMATIC ) execClearDTC;

    elementClassTableNum  = Dem_DataElementNum;
    dataElementClassIndex = Dem_WWHOBDTimeSinceEngineStartBy3min;

    execClearDTC = Dem_Control_CheckExecClearDTCProcess();
    if( execClearDTC == (boolean)FALSE )
    {
        if( dataElementClassIndex < elementClassTableNum )                                  /* [GUD:if]dataElementClassIndex */
        {
            dataElementClassPtr = &Dem_DataElementClassTable[dataElementClassIndex];        /* [GUD]dataElementClassIndex */
            resultOfCallback = Dem_DataElement_ReadData( dataElementClassPtr, dataBuffer , DEM_MONITORDATA_OTHER );
            if( resultOfCallback == (Std_ReturnType)E_OK )
            {
                b1CounterCalc = (Dem_u32_B1CounterType)dataBuffer[DEM_WWHOBD_READDATAELEMENT_DATAPOS0];
                if ( b1CounterCalc != (Dem_u32_B1CounterType)0x00000000 )
                {
                    Dem_IndMI_CalcB1Counter( b1CounterCalc );
                }
            }
            else
            {
                /* No process */
            }
        }
    }

    return ;
}

/****************************************************************************/
/* Function Name | Dem_IndMI_ClearB1Counter                                 */
/* Description   | Clear B1 Counter.(Healing)                               */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventStrgIndex     : EventStrgIndex.               */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IndMI_ClearB1Counter
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex         /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) indMIIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetIndMIIndex;
    VAR( boolean, AUTOMATIC ) useB1Counter;

    useB1Counter = Dem_CfgInfoPm_ChkDTCCls_UseB1Counter( EventStrgIndex );  /* [GUDCHK:CALLER]EventStrgIndex */

    if ( useB1Counter == (boolean)TRUE )
    {
        retGetIndMIIndex = Dem_IndMI_GetIndMIIndexFromIndMIIndexList( EventStrgIndex, &indMIIndex );    /* [GUDCHK:CALLER]EventStrgIndex */
        if ( retGetIndMIIndex == DEM_IRT_OK )
        {
            /* Follow the order, clear IndMIIndexList -> clear B1CounterRecord */
            Dem_IndMI_ClearIndMIIndexFromIndMIIndexList( EventStrgIndex );          /* [GUDCHK:CALLER]EventStrgIndex */
            Dem_IndMIMng_ClearB1CounterRecord( indMIIndex ); /* indMIIndex range check is implemented in this function. */
        }
    }
    return;
}

/****************************************************************************/
/* Function Name | Dem_IndMI_HoldB1Counter                                  */
/* Description   | Hold B1 Counter.                                         */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventStrgIndex     : EventStrgIndex.               */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IndMI_HoldB1Counter
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex         /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u32_B1CounterType, AUTOMATIC )         b1CounterThreshold;
    VAR( Dem_u32_B1CounterType, AUTOMATIC )         b1Counter;
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC )        indMIIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC )    eventStrgIndexRecord; /* dummy parameter */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )    retGetIndMIIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )    retGetB1Counter;
    VAR( boolean, AUTOMATIC ) useB1Counter;

    useB1Counter = Dem_CfgInfoPm_ChkDTCCls_UseB1Counter( EventStrgIndex );  /* [GUDCHK:CALLER]EventStrgIndex */

    if ( useB1Counter == (boolean)TRUE )
    {
        b1CounterThreshold = Dem_CfgInfoPm_GetB1CounterThreshold();

        retGetIndMIIndex = Dem_IndMI_GetIndMIIndexFromIndMIIndexList( EventStrgIndex, &indMIIndex );    /* [GUDCHK:CALLER]EventStrgIndex */

        if ( retGetIndMIIndex == DEM_IRT_OK )
        {
            retGetB1Counter = Dem_IndMIMng_GetB1Counter( indMIIndex, &eventStrgIndexRecord, &b1Counter ); /* indMIIndex range check is implemented in this function. */

            if ( retGetB1Counter == DEM_IRT_OK )
            {
                if ( b1Counter >= b1CounterThreshold )
                {
                    Dem_IndMIMng_HoldB1Counter( indMIIndex );
                }
            }
        }
    }
    return;
}

/****************************************************************************/
/* Function Name | Dem_IndMI_UpdateB1CounterWhenClearDTC                    */
/* Description   | Hold B1 Counter and ContinuousExpFlag turns off.         */
/* Preconditions | none                                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IndMI_UpdateB1CounterWhenClearDTC
( void )
{
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) indMIIndex;
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) indMIMaxNumberOfClassB1Event;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) targetEventStrgIndex;
    VAR( Dem_u32_B1CounterType, AUTOMATIC )  b1CounterThreshold;
    VAR( Dem_u32_B1CounterType, AUTOMATIC )  b1Counter;
    VAR( boolean, AUTOMATIC ) clearAllowed;

    indMIMaxNumberOfClassB1Event = Dem_WWHOBDMaxNumberOfClassB1Event;

    b1CounterThreshold = Dem_CfgInfoPm_GetB1CounterThreshold();

    for ( indMIIndex = (Dem_u16_IndMIIndexType)0U; indMIIndex < indMIMaxNumberOfClassB1Event; indMIIndex++ )
    {
        (void)Dem_IndMIMng_GetB1Counter( indMIIndex, &targetEventStrgIndex, &b1Counter ); /* no return check required */
        if ( targetEventStrgIndex != DEM_EVENTSTRGINDEX_INVALID )
        {
            clearAllowed = Dem_CfgInfoPm_ClearAllowed_InEvtStrgGrp( targetEventStrgIndex );
            if ( clearAllowed == (boolean)TRUE )
            {
                if ( b1Counter >= b1CounterThreshold )
                {
                    Dem_IndMIMng_HoldB1Counter( indMIIndex );
                }
                else
                {
                    Dem_IndMIMng_UpdateClearId( indMIIndex );
                }
            }
        }
    }
    return;
}

/****************************************************************************/
/* Function Name | Dem_IndMI_B1CounterHealingProcess                        */
/* Description   | Update B1ClearCycleCounter.                              */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex                                      */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IndMI_B1CounterHealingProcess
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC )        indMIIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )    retGetIndMIIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )    retGetB1ClearCycleCounter;
    VAR( Dem_u08_B1ClearCycleCounterType, AUTOMATIC ) b1ClearCycleCounter;
    VAR( Dem_u08_HealingCounterType, AUTOMATIC ) healingCounterThreshold;

    retGetIndMIIndex = Dem_IndMI_GetIndMIIndexFromIndMIIndexList( EventStrgIndex, &indMIIndex );
    if ( retGetIndMIIndex == DEM_IRT_OK )
    {
        retGetB1ClearCycleCounter = Dem_IndMIMng_GetB1ClearCycleCounter( indMIIndex, &b1ClearCycleCounter ); /* indMIIndex range check is implemented in this function. */
        if ( retGetB1ClearCycleCounter == DEM_IRT_OK )
        {
            b1ClearCycleCounter = b1ClearCycleCounter + (Dem_u08_B1ClearCycleCounterType)1U;
            healingCounterThreshold = Dem_CfgInfoPm_GetHealingThreshold( EventStrgIndex ) - (Dem_u08_HealingCounterType)1U;

            if ( (Dem_u08_HealingCounterType)b1ClearCycleCounter >= healingCounterThreshold )
            {
                /* Follow the order, clear IndMIIndexList -> clear B1CounterRecord */
                Dem_IndMI_ClearIndMIIndexFromIndMIIndexList( EventStrgIndex );
                Dem_IndMIMng_ClearB1CounterRecord( indMIIndex );
            }
            else
            {
                Dem_IndMIMng_SetB1ClearCycleCounter( indMIIndex, b1ClearCycleCounter );
            }
        }
    }
    return;
}

/****************************************************************************/
/* Function Name | Dem_IndMI_UpdateB1RecordBySetEvent                       */
/* Description   | Update B1Record By SetEvent                              */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStatus                                         */
/*               | [in] EventStrgIndex                                      */
/*               | [in] DTCStatus                                           */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IndMI_UpdateB1RecordBySetEvent
(
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,    /* [PRMCHK:CALLER] */
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
)
{
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC )        indMIIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )    retGetIndMIIndex;
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC )        emptyRecordIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )    retGetEmptyRecordIndex;
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC )        indMIMaxNumberOfClassB1Event;
    VAR( boolean, AUTOMATIC ) useB1Counter;

    indMIMaxNumberOfClassB1Event = Dem_WWHOBDMaxNumberOfClassB1Event;
    useB1Counter = Dem_CfgInfoPm_ChkDTCCls_UseB1Counter( EventStrgIndex );      /* [GUDCHK:CALLER]EventStrgIndex */

    if ( useB1Counter == (boolean)TRUE )
    {
        retGetIndMIIndex = Dem_IndMI_GetIndMIIndexFromIndMIIndexList( EventStrgIndex, &indMIIndex );    /* [GUDCHK:CALLER]EventStrgIndex */
        if ( retGetIndMIIndex == DEM_IRT_OK )
        {
            if ( indMIIndex < indMIMaxNumberOfClassB1Event )
            {
                if ( EventStatus == DEM_EVENT_STATUS_FAILED )
                {
                    Dem_IndMIMng_ClearB1ClearCycleCounter( indMIIndex );
                }
            }
            else
            {
                if ( ( ( DTCStatus & DEM_UDS_STATUS_CDTC ) == DEM_UDS_STATUS_CDTC ) &&
                     ( ( DTCStatus & DEM_UDS_STATUS_PDTC ) == DEM_UDS_STATUS_PDTC ) )
                {
                    retGetEmptyRecordIndex = Dem_IndMIMng_GetEmptyRecordIndex( &emptyRecordIndex );
                    if ( retGetEmptyRecordIndex == DEM_IRT_OK )
                    {
                        /* Follow the order, regist B1CounterRecord -> regist IndMIIndexList */
                        Dem_IndMIMng_RegistB1CounterRecord( emptyRecordIndex, EventStrgIndex );         /* [GUDCHK:CALLER]EventStrgIndex */
                        Dem_IndMI_SetIndMIIndexToIndMIIndexList( EventStrgIndex, emptyRecordIndex );    /* [GUDCHK:CALLER]EventStrgIndex */
                    }
                }
            }
        }
    }
    return;
}

/****************************************************************************/
/* Function Name | Dem_IndMI_GenerateEventStrgIndexToIndMIIndexList         */
/* Description   | Generate Dem_IndMI_EventStrgIndexToIndMIIndexList        */
/* Preconditions |                                                          */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IndMI_GenerateEventStrgIndexToIndMIIndexList
( void )
{
    VAR( Dem_u32_B1CounterType, AUTOMATIC )      b1Counter; /* dummy parameter */
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) classB1EventStorageNum;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) loopEventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) targetEventStrgIndex;
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) indMIIndex;
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) indMIMaxNumberOfClassB1Event;

    indMIMaxNumberOfClassB1Event = Dem_WWHOBDMaxNumberOfClassB1Event;
    classB1EventStorageNum = Dem_ClassB1EventStorageNum;

    /* Initialize Dem_IndMI_EventStrgIndexToIndMIIndexList[] */
    /* Initial value is DEM_INDMIINDEX_INVALID             */
    for ( loopEventStrgIndex = (Dem_u16_EventStrgIndexType)0U; loopEventStrgIndex < classB1EventStorageNum; loopEventStrgIndex++ )  /* [GUD:for]loopEventStrgIndex */
    {
        Dem_IndMI_EventStrgIndexToIndMIIndexList[loopEventStrgIndex] = DEM_INDMIINDEX_INVALID;                  /* [GUD]loopEventStrgIndex */
    }

    /* For EventStrgIndex which memorize B1Counter, set Dem_IndMI_EventStrgIndexToIndMIIndexList[ EventStrgIndex ] */
    for ( indMIIndex = (Dem_u16_IndMIIndexType)0U; indMIIndex < indMIMaxNumberOfClassB1Event; indMIIndex++ )
    {
        (void)Dem_IndMIMng_GetB1Counter( indMIIndex, &targetEventStrgIndex, &b1Counter ); /* no return check required */
        if ( targetEventStrgIndex < classB1EventStorageNum )                                                    /* [GUD:if]targetEventStrgIndex */
        {
            Dem_IndMI_EventStrgIndexToIndMIIndexList[targetEventStrgIndex] =  indMIIndex;                       /* [GUD]targetEventStrgIndex */
        }
    }
    return;
}

/****************************************************************************/
/* Function Name | Dem_IndMI_UpdateB1Record                                 */
/* Description   | Update B1Record.                                         */
/* Preconditions |                                                          */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IndMI_UpdateB1Record
( void )
{
    VAR( boolean, AUTOMATIC ) orderExistFlag;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) orderListIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) classB1EventStorageNum;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC;
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC )        indMIIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )    retGetIndMIIndex;
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) indMIMaxNumberOfClassB1Event;
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC )        searchStartIndex;
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC )        emptyRecordIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )    retGetEmptyRecordIndex;
    VAR( boolean, AUTOMATIC ) useB1Counter;
    VAR( boolean, AUTOMATIC ) loopEndFlg;

    indMIMaxNumberOfClassB1Event = Dem_WWHOBDMaxNumberOfClassB1Event;
    failRecordNum = (Dem_u08_OrderIndexType)Dem_FailRecordNum;
    classB1EventStorageNum = Dem_ClassB1EventStorageNum;
    loopEndFlg = (boolean)FALSE;
    searchStartIndex = (Dem_u16_IndMIIndexType)0U;

    for( orderListIndex = (Dem_u08_OrderIndexType)0U; orderListIndex < failRecordNum; orderListIndex++ )
    {
        eventStrgIndex  = DEM_EVENTSTRGINDEX_INVALID;
        statusOfDTC     = DEM_DTCSTATUS_BYTE_ALL_OFF;

        Dem_Data_GetConfirmedOrderEventStrgIndex( orderListIndex, &eventStrgIndex, &faultIndex, &statusOfDTC, &orderExistFlag );

        if( orderExistFlag == (boolean)TRUE )
        {
            if ( eventStrgIndex < classB1EventStorageNum )  /* [GUD:if]eventStrgIndex */
            {
                useB1Counter = Dem_CfgInfoPm_ChkDTCCls_UseB1Counter( eventStrgIndex );  /* [GUD]eventStrgIndex */
                if ( useB1Counter == (boolean)TRUE )
                {
                    retGetIndMIIndex = Dem_IndMI_GetIndMIIndexFromIndMIIndexList( eventStrgIndex, &indMIIndex );
                    if ( ( retGetIndMIIndex == DEM_IRT_OK ) &&
                         ( indMIIndex >= indMIMaxNumberOfClassB1Event ) )
                    {
                        if( ( ( statusOfDTC & DEM_UDS_STATUS_CDTC ) != DEM_DTCSTATUS_BYTE_ALL_OFF ) &&
                            ( ( statusOfDTC & DEM_UDS_STATUS_PDTC ) != DEM_DTCSTATUS_BYTE_ALL_OFF ) )
                        {
                            retGetEmptyRecordIndex = Dem_IndMIMng_GetNextEmptyRecordIndex( searchStartIndex, &emptyRecordIndex );
                            if ( retGetEmptyRecordIndex == DEM_IRT_OK )
                            {
                                /* Follow the order, regist B1CounterRecord -> regist IndMIIndexList */
                                Dem_IndMIMng_RegistB1CounterRecord( emptyRecordIndex, eventStrgIndex );
                                Dem_IndMI_SetIndMIIndexToIndMIIndexList( eventStrgIndex, emptyRecordIndex );
                                searchStartIndex = emptyRecordIndex + (Dem_u16_IndMIIndexType)1U;
                            }
                            else
                            {
                                /* no empty record. */
                                loopEndFlg = (boolean)TRUE;
                            }
                        }
                    }
                }
            }
        }
        else
        {
            loopEndFlg = (boolean)TRUE;
        }

        if ( loopEndFlg == (boolean)TRUE )
        {
            break;
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_IndMI_CalcB1Counter                                  */
/* Description   | calculate B1 counter.                                    */
/* Preconditions |                                                          */
/* Parameters    | [in]  B1CounterCalc : B1counter add value                */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_IndMI_CalcB1Counter
(
    VAR( Dem_u32_B1CounterType, AUTOMATIC ) B1CounterCalc
)
{
    VAR( Dem_u32_B1CounterType, AUTOMATIC )  b1Counter_old;
    VAR( Dem_u32_B1CounterType, AUTOMATIC )  b1Counter_new;
    VAR( Dem_u32_B1CounterType, AUTOMATIC )  b1CounterThreshold;
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) indMIIndex;
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) indMIMaxNumberOfClassB1Event;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndexRecord;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retResult;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retValDTC;
    VAR( boolean, AUTOMATIC ) availableStatus;

    indMIMaxNumberOfClassB1Event = Dem_WWHOBDMaxNumberOfClassB1Event;
    b1CounterThreshold = Dem_CfgInfoPm_GetB1CounterThreshold();

    for ( indMIIndex = (Dem_u16_IndMIIndexType)0U; indMIIndex < indMIMaxNumberOfClassB1Event; indMIIndex++ )
    {
        (void)Dem_IndMIMng_GetB1Counter( indMIIndex, &eventStrgIndexRecord, &b1Counter_old ); /* no return check required */
        if ( eventStrgIndexRecord != DEM_EVENTSTRGINDEX_INVALID )
        {
            availableStatus = Dem_DataAvl_GetEvtAvl_InEvtStrgGrp( eventStrgIndexRecord );
            if ( availableStatus == (boolean)TRUE )
            {
                retResult = Dem_DataMngC_GetER_FaultIndex( eventStrgIndexRecord, &faultIndex );
                if( retResult == DEM_IRT_OK )
                {
                    /* Target event exists in faultRecord */
                    retValDTC = Dem_DataMngC_GetER_StatusOfDTC( eventStrgIndexRecord, &statusOfDTC );
                    if( retValDTC == DEM_IRT_OK )
                    {
                        if ( ( ( statusOfDTC & DEM_UDS_STATUS_CDTC ) == DEM_UDS_STATUS_CDTC ) &&
                             ( ( statusOfDTC & DEM_UDS_STATUS_PDTC ) == DEM_UDS_STATUS_PDTC ) )
                        {
                            /* Confiemed & Active */
                            if ( b1Counter_old >= ( DEM_B1COUNTER_MAX - B1CounterCalc ) )
                            {
                                b1Counter_new = DEM_B1COUNTER_MAX;
                            }
                            else
                            {
                                b1Counter_new = b1Counter_old + B1CounterCalc; /* no wrap around */
                            }

                            (void)Dem_IndMIMng_SetB1Counter( indMIIndex, eventStrgIndexRecord, b1Counter_new ); /* no return check required */

                            if ( ( b1Counter_new >= b1CounterThreshold ) && ( b1Counter_old < b1CounterThreshold ) )
                            {
                                Dem_IndMI_B1CounterThresholdReached( eventStrgIndexRecord );
                            }
                        }
                    }
                }
            }
        }
    }
    return;
}


/****************************************************************************/
/* Function Name | Dem_IndMI_B1CounterThresholdReached                      */
/* Description   | Reached B1counter threshold process                      */
/* Preconditions |                                                          */
/* Parameters    | [in]  EventStrgIndex : EventStrgIndex.                   */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_IndMI_B1CounterThresholdReached
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{

    VAR( Dem_DTCStatusStType, AUTOMATIC ) oldDTCStatusSt;
    VAR( Dem_DTCStatusStType, AUTOMATIC ) newDTCStatusSt;
    VAR( boolean, AUTOMATIC ) updateMILOrder;
#if ( DEM_PFC_SUPPORT == STD_ON )  /*  [FuncSw]    */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retSavePFCTemp;
#endif /* ( DEM_PFC_SUPPORT == STD_ON ) */

    updateMILOrder = (boolean)FALSE;

    (void)Dem_DataMngC_GetER_DTCStatusSt( EventStrgIndex, &oldDTCStatusSt );  /* no return check required */

#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )     /*  [FuncSw]    */
    if ( ( oldDTCStatusSt.ExtendDTCStatus2 & DEM_DTCSTATUSEX2_STATUS_CONTINUOUS_MI_HISTORY ) != DEM_DTCSTATUSEX2_STATUS_CONTINUOUS_MI_HISTORY )
    {

        /* First transition to continuous-MI */
        /* Update : EventMemoryRecordList.NumberOfObdMILDTCs */
        /*        : FaultRecord.MILOccurrenceOrder           */
        /*        : Dem_OdrLst_MIL_OrderList                 */
        /*        : Dem_OdrLst_MIL_NextOccurrenceOrder       */
        updateMILOrder = (boolean)TRUE;
    }
#endif  /*   ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )    */

    /* Update DTCStatus */
    if ( ( ( oldDTCStatusSt.ExtendDTCStatus & DEM_DTCSTATUSEX_STATUS_TNCTOC_IN_HEALINGCYCLE ) == DEM_DTCSTATUSEX_STATUS_TNCTOC_IN_HEALINGCYCLE ) ||
         ( ( oldDTCStatusSt.ExtendDTCStatus & DEM_DTCSTATUSEX_STATUS_TFTOC_IN_HEALINGCYCLE ) == DEM_DTCSTATUSEX_STATUS_TFTOC_IN_HEALINGCYCLE ) )
    {
        newDTCStatusSt.DTCStatus     =   Dem_DTC_SetWIRStatusBit( oldDTCStatusSt.DTCStatus );
    }
    else
    {
        newDTCStatusSt.DTCStatus     =   oldDTCStatusSt.DTCStatus;
    }
    newDTCStatusSt.ExtendDTCStatus   =   oldDTCStatusSt.ExtendDTCStatus;
    newDTCStatusSt.ExtendDTCStatus2  =   Dem_DTC_ExDTC2_SetContinuousMIHistoryBit( oldDTCStatusSt.ExtendDTCStatus2 );

    Dem_IndMI_UpdateRecordWithMILInfo( EventStrgIndex, &newDTCStatusSt, updateMILOrder);

#if ( DEM_PFC_SUPPORT == STD_ON )  /*  [FuncSw]    */
    retSavePFCTemp = Dem_DTC_SavePermanentMemoryEntryToTmp( EventStrgIndex );
    if ( retSavePFCTemp == DEM_IRT_OK )
    {
        Dem_DTC_UpdatePFCFromB1Counter( EventStrgIndex );
        Dem_DTC_UpdatePermanentMemoryEntryToTmp();
    }
#endif /* ( DEM_PFC_SUPPORT == STD_ON ) */

    return ;
}

/****************************************************************************/
/* Function Name | Dem_IndMI_SetIndMIIndexToIndMIIndexList                  */
/* Description   | Set IndMIIndex                                           */
/*               | to Dem_IndMI_EventStrgIndexToIndMIIndexList              */
/* Preconditions |                                                          */
/* Parameters    | [in]  EventStrgIndex : EventStrgIndex.                   */
/*               | [in]  IndMIIndex     : IndMIIndex.                       */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_IndMI_SetIndMIIndexToIndMIIndexList
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) IndMIIndex
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) classB1EventStorageNum;

    classB1EventStorageNum = Dem_ClassB1EventStorageNum;

    if ( EventStrgIndex < classB1EventStorageNum )                              /* [GUD:if]EventStrgIndex */
    {
        Dem_IndMI_EventStrgIndexToIndMIIndexList[EventStrgIndex] = IndMIIndex;  /* [GUD]EventStrgIndex */
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_IndMI_ClearIndMIIndexFromIndMIIndexList              */
/* Description   | Clear IndMIIndex                                         */
/*               | from Dem_IndMI_EventStrgIndexToIndMIIndexList            */
/* Preconditions |                                                          */
/* Parameters    | [in]  EventStrgIndex : EventStrgIndex.                   */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_IndMI_ClearIndMIIndexFromIndMIIndexList
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) classB1EventStorageNum;

    classB1EventStorageNum = Dem_ClassB1EventStorageNum;

    if ( EventStrgIndex < classB1EventStorageNum )                                          /* [GUD:if]EventStrgIndex */
    {
        Dem_IndMI_EventStrgIndexToIndMIIndexList[EventStrgIndex] = DEM_INDMIINDEX_INVALID;  /* [GUD]EventStrgIndex */
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_IndMI_GetIndMIIndexFromIndMIIndexList                */
/* Description   | Get IndMIIndex                                           */
/*               | from Dem_IndMI_EventStrgIndexToIndMIIndexList            */
/* Preconditions |                                                          */
/* Parameters    | [in]  EventStrgIndex : EventStrgIndex.                   */
/*               | [out] IndMIIndexPtr  : IndMIIndex.                       */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |          DEM_IRT_OK : EventStrgIndex < ClassB1 event num */
/*               |          DEM_IRT_NG : other                              */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IndMI_GetIndMIIndexFromIndMIIndexList
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u16_IndMIIndexType, AUTOMATIC, AUTOMATIC ) IndMIIndexPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) classB1EventStorageNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    classB1EventStorageNum = Dem_ClassB1EventStorageNum;
    retVal = DEM_IRT_NG;

    if ( EventStrgIndex < classB1EventStorageNum )                                  /* [GUD:if]EventStrgIndex */
    {
        *IndMIIndexPtr = Dem_IndMI_EventStrgIndexToIndMIIndexList[EventStrgIndex];  /* [GUD]EventStrgIndex */
        retVal = DEM_IRT_OK;
    }
    else
    {
        *IndMIIndexPtr = DEM_INDMIINDEX_INVALID;
    }

    return retVal;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /*   ( DEM_WWH_OBD_SUPPORT == STD_ON )      */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
