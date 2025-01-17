/* Dem_Ind_MI_GetMIStatus_WWH_c(v5-5-0)                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Ind_MI_GetMIStatus_WWH/CODE                           */
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
#include "../../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../../inc/Dem_CmnLib_Control.h"
#include "../../../../inc/Dem_Pm_Ind.h"
#include "../../../../inc/Dem_Pm_Ind_MI.h"
#include "../../../../inc/Dem_Rc_DataMng.h"
#include "../../../../inc/Dem_Pm_DataCtl_OBD.h"
#include "Dem_Ind_MI_local.h"

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

static FUNC( Dem_IndicatorStatusType, DEM_CODE ) Dem_IndMI_GetMIStatusForClassA
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);

static FUNC( Dem_IndicatorStatusType, DEM_CODE ) Dem_IndMI_GetMIStatusForClassB1
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);

static FUNC( Dem_IndicatorStatusType, DEM_CODE ) Dem_IndMI_GetMIStatusForClassB2
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);

static FUNC( Dem_IndicatorStatusType, DEM_CODE ) Dem_IndMI_GetMIStatusForClassC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
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
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_IndMI_GetMILStatus                                   */
/* Description   | Get MIL Status .                                         */
/* Preconditions | none                                                     */
/* Parameters    | [out] IndicatorStatusPtr                                 */
/*               |        Pointer to data for set Indicator Status.         */
/*               |        This pointer is pointing to                       */
/*               |        Dem_GetIndicatorStatus 2nd parameter.             */
/*               |          DEM_INDICATOR_OFF        : Indicator Off        */
/*               |          DEM_INDICATOR_CONTINUOUS : Indicator On         */
/*               |          DEM_INDICATOR_SHORT      : Indicator Short      */
/*               |          DEM_INDICATOR_ON_DEMAND  : Indicator On-Demand  */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Success.                             */
/*               |        DEM_IRT_NG : Failed.                              */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IndMI_GetMILStatus
(
    P2VAR( Dem_IndicatorStatusType, AUTOMATIC, AUTOMATIC ) IndicatorStatusPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( boolean, AUTOMATIC ) OrderExistFlag;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) orderListIndex;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_IndicatorStatusType, AUTOMATIC ) indicatorStatus;
    VAR( Dem_IndicatorStatusType, AUTOMATIC ) returnIndicatorStatus;


    failRecordNum = (Dem_u08_OrderIndexType)Dem_FailRecordNum;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;
    returnIndicatorStatus = DEM_INDICATOR_OFF;

    for( orderListIndex = (Dem_u08_OrderIndexType)0U; orderListIndex < failRecordNum; orderListIndex++ )
    {
        eventStrgIndex  = DEM_EVENTSTRGINDEX_INVALID;
        statusOfDTC = DEM_DTCSTATUS_BYTE_ALL_OFF;
        Dem_Data_GetConfirmedOrderEventStrgIndex( orderListIndex, &eventStrgIndex, &faultIndex, &statusOfDTC, &OrderExistFlag );

        if( OrderExistFlag != (boolean)FALSE )
        {
            if( eventStrgIndex < eventStorageNum )      /* [GUD:if]eventStrgIndex */
            {
                (void)Dem_IndMI_GetMILStatusByEventStrgIndex( eventStrgIndex, &indicatorStatus ); /* no return check required *//* [GUD]eventStrgIndex */
                switch ( indicatorStatus )
                {
                    case DEM_INDICATOR_CONTINUOUS:
                        returnIndicatorStatus = DEM_INDICATOR_CONTINUOUS;
                        break;
                    case DEM_INDICATOR_SHORT:
                        if ( ( returnIndicatorStatus == DEM_INDICATOR_OFF ) || ( returnIndicatorStatus == DEM_INDICATOR_ON_DEMAND ) )
                        {
                            returnIndicatorStatus = DEM_INDICATOR_SHORT;
                        }
                        break;
                    case DEM_INDICATOR_ON_DEMAND:
                        if ( returnIndicatorStatus == DEM_INDICATOR_OFF )
                        {
                            returnIndicatorStatus = DEM_INDICATOR_ON_DEMAND;
                        }
                        break;
                    default:
                        /* No Process */
                        break;
                }

                if ( returnIndicatorStatus == DEM_INDICATOR_CONTINUOUS )
                {
                    break;
                }
            }
        }
    }

    *IndicatorStatusPtr = returnIndicatorStatus;
    return DEM_IRT_OK;
}

/****************************************************************************/
/* Function Name | Dem_IndMI_GetMILStatusByEventStrgIndex                   */
/* Description   | Get MIL Status by Event.                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        Event index.                                      */
/* Parameters    | [out] IndicatorStatusPtr                                 */
/*               |          DEM_INDICATOR_OFF        : Indicator Off        */
/*               |          DEM_INDICATOR_CONTINUOUS : Indicator On         */
/*               |          DEM_INDICATOR_SHORT      : Indicator Short      */
/*               |          DEM_INDICATOR_ON_DEMAND  : Indicator On-Demand  */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Success.                             */
/*               |        DEM_IRT_NG : Failed.                              */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IndMI_GetMILStatusByEventStrgIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,            /* [PRMCHK:CALLER] */
    P2VAR( Dem_IndicatorStatusType, AUTOMATIC, AUTOMATIC ) IndicatorStatusPtr
)
{
    VAR( Dem_DTCSeverityType, AUTOMATIC ) dtcClass;
    VAR( boolean, AUTOMATIC ) isMILIndicator;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    isMILIndicator = Dem_CfgInfoPm_ChkDTCCls_HasMILInd( EventStrgIndex );   /* [GUDCHK:CALLER]EventStrgIndex */
    if ( isMILIndicator == (boolean)TRUE )
    {
        dtcClass = Dem_CfgInfoPm_GetDTCSeverityClass( EventStrgIndex ); /* always (EventStrgIndex < Dem_PrimaryMemEventStorageNum) *//* [GUDCHK:CALLER]EventStrgIndex */
        switch ( dtcClass )
        {
            case DEM_DTC_CLASS_1:   /* Class A */
                *IndicatorStatusPtr = Dem_IndMI_GetMIStatusForClassA( EventStrgIndex );
                break;

            case DEM_DTC_CLASS_2:   /* Class B1 */
                *IndicatorStatusPtr = Dem_IndMI_GetMIStatusForClassB1( EventStrgIndex );
                break;

            case DEM_DTC_CLASS_3:   /* Class B2 */
                *IndicatorStatusPtr = Dem_IndMI_GetMIStatusForClassB2( EventStrgIndex );
                break;

            case DEM_DTC_CLASS_4:   /* Class C */
                *IndicatorStatusPtr = Dem_IndMI_GetMIStatusForClassC( EventStrgIndex );
                break;

            default:    /* Other */
                *IndicatorStatusPtr = DEM_INDICATOR_OFF;
                break;
        }
        retVal = DEM_IRT_OK;
    }
    else
    {
        *IndicatorStatusPtr = DEM_INDICATOR_OFF;
        retVal = DEM_IRT_NG;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_IndMI_IsContMIorShortMI_ByEventStrgIndex             */
/* Description   | Get MIL Status by Event.                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        Event index.                                      */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : Continuous-MI or Short-MI.                */
/*               |        FALSE : Other MI Status.                          */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_IndMI_IsContMIorShortMI_ByEventStrgIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex         /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_DTCSeverityType, AUTOMATIC ) dtcClass;
    VAR( boolean, AUTOMATIC ) isMILIndicator;
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) extendStatusOfDTC;
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) extendStatusOfDTC2;

    retVal = (boolean)FALSE;
    isMILIndicator = Dem_CfgInfoPm_ChkDTCCls_HasMILInd( EventStrgIndex );   /* [GUDCHK:CALLER]EventStrgIndex */

    if ( isMILIndicator == (boolean)TRUE )
    {
        dtcClass = Dem_CfgInfoPm_GetDTCSeverityClass( EventStrgIndex ); /* always (EventStrgIndex < Dem_PrimaryMemEventStorageNum) */

        switch ( dtcClass )
        {
            case DEM_DTC_CLASS_1:   /* Class A */
                (void)Dem_DataMngC_GetER_ExtendDTCStatus( EventStrgIndex, &extendStatusOfDTC );  /* no return check required */
                if ( ( extendStatusOfDTC & DEM_DTCSTATUSEX_STATUS_INDICATOR ) == DEM_DTCSTATUSEX_STATUS_INDICATOR )
                {
                    retVal = (boolean)TRUE;
                }
                break;

            case DEM_DTC_CLASS_2:   /* Class B1 */
                (void)Dem_DataMngC_GetER_ExtendDTCStatus2( EventStrgIndex, &extendStatusOfDTC2 );  /* no return check required */
                if ( ( extendStatusOfDTC2 & DEM_DTCSTATUSEX2_STATUS_INDICATOR_AT_CYCLESTART ) == DEM_DTCSTATUSEX2_STATUS_INDICATOR_AT_CYCLESTART )
                {
                    retVal = (boolean)TRUE;
                }
                break;

            case DEM_DTC_CLASS_3:   /* Class B2 */
                (void)Dem_DataMngC_GetER_ExtendDTCStatus2( EventStrgIndex, &extendStatusOfDTC2 );  /* no return check required */
                if ( ( extendStatusOfDTC2 & DEM_DTCSTATUSEX2_STATUS_INDICATOR_AT_CYCLESTART ) == DEM_DTCSTATUSEX2_STATUS_INDICATOR_AT_CYCLESTART )
                {
                    retVal = (boolean)TRUE;
                }
                break;

            case DEM_DTC_CLASS_4:   /* Class C */
                break;

            default:    /* No Class */
                break;
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_IndMI_GetMIStatusForClassA                           */
/* Description   | Get MIL Status by Class A Event.                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        Event index.                                      */
/* Return Value  | Dem_IndicatorStatusType                                  */
/*               |          DEM_INDICATOR_OFF        : Indicator Off        */
/*               |          DEM_INDICATOR_CONTINUOUS : Indicator On         */
/*               |          DEM_INDICATOR_SHORT      : Indicator Short      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( Dem_IndicatorStatusType, DEM_CODE ) Dem_IndMI_GetMIStatusForClassA
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) extendStatusOfDTC;
    VAR( Dem_u08_HealingCounterType, AUTOMATIC ) healingCounter;
    VAR( Dem_IndicatorStatusType, AUTOMATIC ) indicatorStatus;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetHealingCounter;

    (void)Dem_DataMngC_GetER_ExtendDTCStatus( EventStrgIndex, &extendStatusOfDTC );  /* no return check required */
    if ( ( extendStatusOfDTC & DEM_DTCSTATUSEX_STATUS_INDICATOR ) == DEM_DTCSTATUSEX_STATUS_INDICATOR )
    {
        (void)Dem_DataMngC_GetER_FaultIndex( EventStrgIndex,&faultIndex );  /* no return check required */
        retGetHealingCounter = Dem_DataMngC_GetFR_HealingCounter( faultIndex, &healingCounter );
        if ( retGetHealingCounter == DEM_IRT_OK )
        {
            if ( healingCounter > (Dem_u08_HealingCounterType)0U )
            {
                indicatorStatus = DEM_INDICATOR_SHORT;
            }
            else
            {
                if ( ( ( extendStatusOfDTC & DEM_DTCSTATUSEX_STATUS_TFTOC_IN_HEALINGCYCLE ) == DEM_DTCSTATUSEX_BYTE_ALL_OFF ) &&
                     ( ( extendStatusOfDTC & DEM_DTCSTATUSEX_STATUS_TNCTOC_IN_HEALINGCYCLE ) == DEM_DTCSTATUSEX_BYTE_ALL_OFF ) )
                {
                    indicatorStatus = DEM_INDICATOR_SHORT;
                }
                else
                {
                    indicatorStatus = DEM_INDICATOR_CONTINUOUS;
                }
            }
        }
        else
        {
            indicatorStatus = DEM_INDICATOR_OFF;
        }
    }
    else
    {
        indicatorStatus = DEM_INDICATOR_OFF;
    }
    return indicatorStatus;
}

/****************************************************************************/
/* Function Name | Dem_IndMI_GetMIStatusForClassB1                          */
/* Description   | Get MIL Status by Class B1 Event.                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        Event index.                                      */
/* Return Value  | Dem_IndicatorStatusType                                  */
/*               |          DEM_INDICATOR_OFF        : Indicator Off        */
/*               |          DEM_INDICATOR_CONTINUOUS : Indicator On         */
/*               |          DEM_INDICATOR_SHORT      : Indicator Short      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( Dem_IndicatorStatusType, DEM_CODE ) Dem_IndMI_GetMIStatusForClassB1
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC;
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) extendStatusOfDTC;
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) extendStatusOfDTC2;
    VAR( Dem_u32_B1CounterType, AUTOMATIC ) b1Counter;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )    getB1CounterResult;
    VAR( Dem_u32_B1CounterType, AUTOMATIC ) b1CounterThreshold;
    VAR( Dem_IndicatorStatusType, AUTOMATIC ) indicatorStatus;

    (void)Dem_DataMngC_GetER_StatusOfDTC( EventStrgIndex, &statusOfDTC );  /* no return check required */
    (void)Dem_DataMngC_GetER_ExtendDTCStatus2( EventStrgIndex, &extendStatusOfDTC2 );  /* no return check required */

    getB1CounterResult = Dem_IndMI_GetB1CounterByEventStrgIndex_By3Minutes( EventStrgIndex, &b1Counter );
    b1CounterThreshold = Dem_CfgInfoPm_GetB1CounterThreshold();

    if ( getB1CounterResult == DEM_IRT_OK )
    {
        if ( ( b1Counter >= b1CounterThreshold ) && 
              ( ( statusOfDTC & DEM_UDS_STATUS_CDTC ) == DEM_UDS_STATUS_CDTC ) &&
              ( ( statusOfDTC & DEM_UDS_STATUS_PDTC ) == DEM_UDS_STATUS_PDTC ) )
        {
            if ( ( extendStatusOfDTC2 & DEM_DTCSTATUSEX2_STATUS_INDICATOR_AT_CYCLESTART ) != DEM_DTCSTATUSEX2_STATUS_INDICATOR_AT_CYCLESTART )
            {
                indicatorStatus = DEM_INDICATOR_CONTINUOUS;
            }
            else
            {
                (void)Dem_DataMngC_GetER_ExtendDTCStatus( EventStrgIndex, &extendStatusOfDTC );  /* no return check required */

                if ( ( ( extendStatusOfDTC & DEM_DTCSTATUSEX_STATUS_TFTOC_IN_HEALINGCYCLE ) == DEM_DTCSTATUSEX_BYTE_ALL_OFF ) &&
                     ( ( extendStatusOfDTC & DEM_DTCSTATUSEX_STATUS_TNCTOC_IN_HEALINGCYCLE ) == DEM_DTCSTATUSEX_BYTE_ALL_OFF ) )
                {
                    indicatorStatus = DEM_INDICATOR_SHORT;
                }
                else
                {
                    indicatorStatus = DEM_INDICATOR_CONTINUOUS;
                }
            }
        }
        else
        {
            if ( ( extendStatusOfDTC2 & DEM_DTCSTATUSEX2_STATUS_INDICATOR_AT_CYCLESTART ) == DEM_DTCSTATUSEX2_STATUS_INDICATOR_AT_CYCLESTART )
            {
                indicatorStatus = DEM_INDICATOR_SHORT;
            }
            else
            {
                indicatorStatus = DEM_INDICATOR_OFF;
            }
        }
    }
    else
    {
        if ( ( extendStatusOfDTC2 & DEM_DTCSTATUSEX2_STATUS_INDICATOR_AT_CYCLESTART ) == DEM_DTCSTATUSEX2_STATUS_INDICATOR_AT_CYCLESTART )
        {
            indicatorStatus = DEM_INDICATOR_SHORT;
        }
        else
        {
            indicatorStatus = DEM_INDICATOR_OFF;
        }
    }

    return indicatorStatus;
}

/****************************************************************************/
/* Function Name | Dem_IndMI_GetMIStatusForClassB2                          */
/* Description   | Get MIL Status by Class B2 Event.                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        Event index.                                      */
/* Return Value  | Dem_IndicatorStatusType                                  */
/*               |          DEM_INDICATOR_OFF        : Indicator Off        */
/*               |          DEM_INDICATOR_SHORT      : Indicator Short      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( Dem_IndicatorStatusType, DEM_CODE ) Dem_IndMI_GetMIStatusForClassB2
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) extendStatusOfDTC2;
    VAR( Dem_IndicatorStatusType, AUTOMATIC ) indicatorStatus;


    (void)Dem_DataMngC_GetER_ExtendDTCStatus2( EventStrgIndex, &extendStatusOfDTC2 );  /* no return check required */
    if ( ( extendStatusOfDTC2 & DEM_DTCSTATUSEX2_STATUS_INDICATOR_AT_CYCLESTART ) == DEM_DTCSTATUSEX2_STATUS_INDICATOR_AT_CYCLESTART )
    {
        indicatorStatus = DEM_INDICATOR_SHORT;
    }
    else
    {
        indicatorStatus = DEM_INDICATOR_OFF;
    }
    return indicatorStatus;
}

/****************************************************************************/
/* Function Name | Dem_IndMI_GetMIStatusForClassC                           */
/* Description   | Get MIL Status by Class C Event.                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        Event index.                                      */
/* Return Value  | Dem_IndicatorStatusType                                  */
/*               |          DEM_INDICATOR_OFF        : Indicator Off        */
/*               |          DEM_INDICATOR_ON_DEMAND  : Indicator On-Demand  */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( Dem_IndicatorStatusType, DEM_CODE ) Dem_IndMI_GetMIStatusForClassC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_IndicatorStatusType, AUTOMATIC ) indicatorStatus;
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) extendStatusOfDTC;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetStatusOfDTC;

    retGetStatusOfDTC = Dem_DataMngC_GetER_ExtendDTCStatus( EventStrgIndex, &extendStatusOfDTC );  /* no return check required */

    if ( retGetStatusOfDTC == DEM_IRT_OK )
    {
        if( ( extendStatusOfDTC & DEM_DTCSTATUSEX_STATUS_INDICATOR ) == DEM_DTCSTATUSEX_STATUS_INDICATOR )
        {
            indicatorStatus = DEM_INDICATOR_ON_DEMAND;
        }
        else
        {
            indicatorStatus = DEM_INDICATOR_OFF;
        }
    }
    else
    {
        indicatorStatus = DEM_INDICATOR_OFF;
    }
    return indicatorStatus;
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
