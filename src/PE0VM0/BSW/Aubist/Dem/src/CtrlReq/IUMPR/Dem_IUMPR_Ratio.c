/* Dem_IUMPR_Ratio_c(v5-5-0)                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/IUMPR_Ratio/CODE                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#if ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )

#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Pm_DataAvl.h"
#include "../../../inc/Dem_Pm_IUMPR.h"
#include "../../../inc/Dem_Rc_IUMPRMng.h"
#include "../../../usr/Dem_IUMPR_Callout.h"
#include "../../../usr/Dem_IUMPR_FiM_Connector.h"
#include "Dem_IUMPR_local.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_CALC_RATIO_ID_INDEX_INITIAL         ((Dem_u16_RatioIndexType)0x0000U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

static FUNC( void, DEM_CODE ) Dem_IUMPR_GetComponentRatio
(
    VAR( Dem_u08_IUMPRGroupIndexType, AUTOMATIC)    GroupIndex,
    P2VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC, AUTOMATIC )           NumeratorPtr,
    P2VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC, AUTOMATIC )           DenominatorPtr
);

static FUNC( boolean, DEM_CODE ) Dem_IUMPR_JudgeDenCondEst
(
    VAR( Dem_u08_IUMPRDenGroupType, AUTOMATIC )     DenGroup,
    VAR( Dem_u08_IUMPRRatioCondType, AUTOMATIC )                         Condition,
    VAR( boolean, AUTOMATIC )                       GenDenFidPermission,
    VAR( boolean, AUTOMATIC )                       RatioFidPermission
);

static FUNC( boolean, DEM_CODE ) Dem_IUMPR_GetNotificationParam
(
    VAR( boolean, AUTOMATIC )                           AddRatioNume,
    VAR( boolean, AUTOMATIC )                           AddRatioDen,
    P2VAR( Dem_IumprDataType, AUTOMATIC, AUTOMATIC )    IumprDataTypePtr
);

static FUNC( void, DEM_CODE ) Dem_IUMPR_UpdateHistCondition
(
    VAR( Dem_IumprDenomCondStatusType, AUTOMATIC )  GenDenomCondStatus,
    P2VAR( Dem_u08_IUMPRRatioCondType, AUTOMATIC, AUTOMATIC )            ConditionPtr
);

static FUNC( void, DEM_CODE ) Dem_IUMPR_UpdateRatioInfomation
(
    VAR( Dem_RatioIdType, AUTOMATIC )               RatioId,
    VAR( Dem_IumprDenomCondStatusType, AUTOMATIC )  GenDenomCondStatus,
    VAR( boolean, AUTOMATIC )                       GenDenomFidPermission
);

static FUNC( void, DEM_CODE ) Dem_IUMPR_UpdateRatioCondition
(
    VAR( Dem_u08_IUMPRDenGroupType, AUTOMATIC )     DenGroup,
    VAR( Dem_IumprDenomCondStatusType, AUTOMATIC )  GenDenomCondStatus,
    P2VAR( Dem_u08_IUMPRRatioCondType, AUTOMATIC, AUTOMATIC )            RatioConditionPtr
);

static FUNC( void, DEM_CODE ) Dem_IUMPR_UpdateDenEstRatioCond
(
    VAR( Dem_IumprDenomCondIdType, AUTOMATIC )      ConditionId,
    P2VAR( Dem_u08_IUMPRRatioCondType, AUTOMATIC, AUTOMATIC )            RatioConditionPtr
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

static VAR( Dem_RatioIdType, DEM_VAR_NO_INIT )              Dem_NextCalcRatioId;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_IUMPR_Init                                           */
/* Description   | Inits Dem_Iumpr.                                         */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IUMPR_Ratio_Init
( void )
{
    Dem_NextCalcRatioId     = DEM_CALC_RATIO_ID_INDEX_INITIAL;

    return;
}


/****************************************************************************/
/* Function Name | Dem_IUMPR_UpdateEventRelatedNumerator                    */
/* Description   | Update Ratio Numerator condition Related EventId         */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventCtrlIndex: EventCtrlIndex.                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IUMPR_UpdateEventRelatedNumerator
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC )    EventCtrlIndex      /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_RatioIdType, AUTOMATIC )                       ratioId;
    VAR( Dem_u16_RatioIndexType, AUTOMATIC )                tableIndex;
    VAR( Dem_u16_RatioIndexType, AUTOMATIC )                ratioIdTableNum;
    VAR( Dem_u16_RatioIdListAdrIndexType, AUTOMATIC )       ratioIdListAdrIndex;
    VAR( Dem_u08_IUMPRRatioKindType, AUTOMATIC )                                 ratioIdKind;

    ratioIdTableNum     = Dem_RatioDataTable[ EventCtrlIndex ].TableNum;                /* [GUDCHK:CALLER]EventCtrlIndex *//* [GUD:CFG:IF_GUARDED: EventCtrlIndex ]ratioIdTableNum */
    ratioIdListAdrIndex = Dem_RatioDataTable[ EventCtrlIndex ].RatioIdListAdrTableIdx;  /* [GUDCHK:CALLER]EventCtrlIndex *//* [GUD:CFG:IF_GUARDED: EventCtrlIndex ]ratioIdListAdrIndex */

    for( tableIndex = (Dem_u16_RatioIndexType)0x00U; tableIndex < ratioIdTableNum; tableIndex++ )   /* [GUD:for]tableIndex */
    {
        ratioId     = Dem_RatioIdListAdrTable[ ratioIdListAdrIndex ].RatioIdListAdr[ tableIndex ];  /* [GUDCHK:CALLER]EventCtrlIndex *//* [GUD]tableIndex *//* [GUD:CFG:IF_GUARDED: EventCtrlIndex ]ratioId */
        ratioIdKind = Dem_RatioTable[ ratioId ].DemRatioKind;                                       /* [GUDCHK:CALLER]EventCtrlIndex *//* [GUD:CFG:IF_GUARDED: EventCtrlIndex ]ratioId */
        if( ratioIdKind == DEM_RATIO_OBSERVER )
        {
            Dem_IUMPRMng_SetRatioNumeAdditionCondition( ratioId );
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_IUMPR_GetDataByRatioId                               */
/* Description   | Get numerator and denominator for IUMPR.                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] RatioId :                                           */
/*               |          Ratio Identifier reporting that a respective    */
/*               |          monitor could have found a fault.               */
/*               | [out] NumeratorPtr   : Numerator.                        */
/*               | [out] DenominatorPtr : Denominator.                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Operation was successful.            */
/*               |        DEM_IRT_NG : Operation failed.                    */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IUMPR_GetDataByRatioId
(
    VAR( Dem_RatioIdType, AUTOMATIC )       RatioId,
    P2VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC, AUTOMATIC )   NumeratorPtr,
    P2VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC, AUTOMATIC )   DenominatorPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )                     retVal;
    VAR( Dem_u16_RatioIndexType, AUTOMATIC )    demRatioNum;
    VAR( boolean, AUTOMATIC )                   availableStatus;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC )    eventCtrlIndex;
    VAR( boolean, AUTOMATIC ) eventOBDKind;

    retVal = DEM_IRT_NG;
    demRatioNum = Dem_RatioNum;

    if( RatioId < demRatioNum )                                                 /* [GUD:if]RatioId */
    {
        eventCtrlIndex  = Dem_RatioTable[ RatioId ].DemDiagnosticEventRef;      /* [GUD]RatioId *//* [GUD:CFG:IF_GUARDED: RatioId ]eventCtrlIndex */

        availableStatus = Dem_DataAvl_GetEvtAvl( eventCtrlIndex );              /* [GUD]eventCtrlIndex */

        if( availableStatus == (boolean)TRUE )
        {
            /*  check OBD event or not.     */
            eventOBDKind    =   Dem_CfgInfoPm_CheckEventKindOfOBD_ByEvtCtrlIdx( eventCtrlIndex );           /* [GUD]eventCtrlIndex */
            if( eventOBDKind == (boolean)TRUE ) /*  OBD     */
            {
                retVal = Dem_IUMPRMng_GetRatioByRatioId( RatioId, NumeratorPtr, DenominatorPtr );           /* [GUD]RatioId *//* [GUD]eventCtrlIndex */
            }
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_IUMPR_GetEventIdByRatioId                            */
/* Description   | Get EventId for IUMPR.                                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] RatioID :                                           */
/*               |          Ratio Identifier reporting that a respective    */
/*               |          monitor could have found a fault.               */
/*               | [out] EventIdPtr   : EventId.                            */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Operation was successful.            */
/*               |        DEM_IRT_NG : Operation failed.                    */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_IUMPR_GetDataByRatioId.        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IUMPR_GetEventIdByRatioId
(
    VAR( Dem_RatioIdType, AUTOMATIC )               RatioId,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC )  EventIdPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )                     retVal;
    VAR( Dem_u16_RatioIndexType, AUTOMATIC )        demRatioNum;
    VAR( boolean, AUTOMATIC )                       availableStatus;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC )    eventCtrlIndex;
    VAR( Dem_EventIdType, AUTOMATIC )               eventId;
    VAR( boolean, AUTOMATIC ) eventOBDKind;

    retVal = DEM_IRT_NG;
    demRatioNum = Dem_RatioNum;

    if( RatioId < demRatioNum )                                             /* [GUD:if]RatioId */
    {
        eventCtrlIndex  = Dem_RatioTable[ RatioId ].DemDiagnosticEventRef;  /* [GUD]RatioId *//* [GUD:CFG:IF_GUARDED: RatioId ]eventCtrlIndex */

        availableStatus = Dem_DataAvl_GetEvtAvl( eventCtrlIndex );          /* [GUD]eventCtrlIndex */

        if( availableStatus == (boolean)TRUE )
        {
            /*  check OBD event or not.     */
            eventOBDKind    =   Dem_CfgInfoPm_CheckEventKindOfOBD_ByEvtCtrlIdx( eventCtrlIndex );   /* [GUD]eventCtrlIndex */
            if( eventOBDKind == (boolean)TRUE ) /*  OBD     */
            {
                eventId =   Dem_CfgInfoCmn_CnvEventCtrlIndexToEventId( eventCtrlIndex );            /* [GUD]eventCtrlIndex */
                if( eventId != DEM_EVENTID_INVALID )
                {
                    retVal = DEM_IRT_OK;
                    *EventIdPtr =   eventId;
                }
            }
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_IUMPR_GetRatioIdByEventId                            */
/* Description   | Get RatioId list by EventId.                             */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventCtrlIndex: EventCtrlIndex.                     */
/*               | [out] RatioIdBufferPtr :  RatioId list.                  */
/*               | [in/out] RatioIdNumPtr :  RatioId list number.           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Operation was successful.            */
/*               |        DEM_IRT_WRONG_BUFFERSIZE : buffer overflow.       */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_IUMPR_UpdateEventRelatedNumerator. */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IUMPR_GetRatioIdByEventId
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC )    EventCtrlIndex,     /* [PRMCHK:CALLER] */
    P2VAR( Dem_RatioIdType, AUTOMATIC, DEM_APPL_DATA ) RatioIdBufferPtr,
    P2VAR( Dem_RatioIdType, AUTOMATIC, AUTOMATIC ) RatioIdNumPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_RatioIdType, AUTOMATIC )                       ratioId;
    VAR( Dem_u16_RatioIndexType, AUTOMATIC )                tableIndex;
    VAR( Dem_u16_RatioIndexType, AUTOMATIC )                ratioIdTableNum;
    VAR( Dem_u16_RatioIndexType, AUTOMATIC )                ratioIdBuffIndex;
    VAR( Dem_u16_RatioIndexType, AUTOMATIC )                ratioIdBuffSize;
    VAR( Dem_u16_RatioIdListAdrIndexType, AUTOMATIC )       ratioIdListAdrIndex;

    ratioIdBuffIndex    =   (Dem_u16_RatioIndexType)0U;
    ratioIdBuffSize     =   *RatioIdNumPtr;

    if ( ratioIdBuffSize > (Dem_u16_RatioIndexType)0U )
    {
        retVal  =   DEM_IRT_OK;
        ratioIdTableNum     = Dem_RatioDataTable[ EventCtrlIndex ].TableNum;                /* [GUDCHK:CALLER]EventCtrlIndex *//* [GUD:CFG:IF_GUARDED: EventCtrlIndex ]ratioIdTableNum */
        ratioIdListAdrIndex = Dem_RatioDataTable[ EventCtrlIndex ].RatioIdListAdrTableIdx;  /* [GUDCHK:CALLER]EventCtrlIndex *//* [GUD:CFG:IF_GUARDED: EventCtrlIndex ]ratioIdListAdrIndex */

        for( tableIndex = (Dem_u16_RatioIndexType)0x00U; tableIndex < ratioIdTableNum; tableIndex++ )   /* [GUD:for]tableIndex */
        {
            ratioId     = Dem_RatioIdListAdrTable[ ratioIdListAdrIndex ].RatioIdListAdr[ tableIndex ];  /* [GUDCHK:CALLER]EventCtrlIndex *//* [GUD]tableIndex */

            /*  set data.       */
            if ( ratioIdBuffIndex < ratioIdBuffSize )                                       /* [GUD:if]ratioIdBuffIndex */
            {
                RatioIdBufferPtr[ ratioIdBuffIndex ]    =   ratioId;                        /* [GUD]ratioIdBuffIndex */
                ratioIdBuffIndex    =   ratioIdBuffIndex + (Dem_u16_RatioIndexType)1U;
            }
            else
            {
                /*  overflow.       */
                retVal  =   DEM_IRT_WRONG_BUFFERSIZE;
                break;
            }
        }
    }
    else
    {
        /*  overflow.(buffer size is 0.)        */
        retVal  =   DEM_IRT_WRONG_BUFFERSIZE;
    }

    /*  set ratioid count.  */
    *RatioIdNumPtr  =   ratioIdBuffIndex;

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_IUMPR_Ratio_GetInfoTypeValue                         */
/* Description   | Service is used for requesting IUMPR data according to   */
/*               | InfoType 0x08 or 0x0B.                                   */
/* Preconditions | none                                                     */
/* Parameters    | [out] IumprdataPtr :                                     */
/*               |          Buffer containing the contents of               */
/*               |          InfoType 0x08 or 0x0B.                          */
/*               |          The buffer is provided by the Dcm.              */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IUMPR_Ratio_GetInfoTypeValue
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA )        IumprdataPtr
)
{
    VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC )                        nume;
    VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC )                        deno;
    VAR( Dem_u08_IUMPRGroupIndexType, AUTOMATIC )   groupIndex;
    VAR( Dem_u08_IUMPRGroupIndexType, AUTOMATIC )   reqIumprGroupNum;
    VAR( uint8, AUTOMATIC )                         dataPos;

    reqIumprGroupNum                    = Dem_IUMPR_NODI_GroupNum;
    for ( groupIndex = (Dem_u08_IUMPRGroupIndexType)0U; groupIndex < reqIumprGroupNum; groupIndex++ )   /* [GUD:for]groupIndex */
    {
        Dem_IUMPR_GetComponentRatio( groupIndex, &nume, &deno );        /* [GUD]groupIndex */
        dataPos = groupIndex * DEM_IUMPR_RATIO_DATA_SIZE;
        IumprdataPtr[dataPos + DEM_IUMPR_POS5] = (uint8)(nume >> DEM_IUMPR_COUNTER_SHIFT);
        IumprdataPtr[dataPos + DEM_IUMPR_POS6] = (uint8)(nume);
        IumprdataPtr[dataPos + DEM_IUMPR_POS7] = (uint8)(deno >> DEM_IUMPR_COUNTER_SHIFT);
        IumprdataPtr[dataPos + DEM_IUMPR_POS8] = (uint8)(deno);
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dem_IUMPR_CheckFaultDetectCondition                      */
/* Description   | Service for reporting that faults are possibly found     */
/*               | because all conditions are fullfilled.                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] RatioId :                                           */
/*               |          Ratio Identifier reporting that a respective    */
/*               |          monitor could have found a fault                */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Operation was successful.            */
/*               |        DEM_IRT_NG : Operation failed.                    */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IUMPR_CheckFaultDetectCondition
(
    VAR( Dem_RatioIdType, AUTOMATIC ) RatioId
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )   retVal;
    VAR( Dem_u16_RatioIndexType, AUTOMATIC )    demRatioNum;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC )    eventCtrlIndex;
    VAR( boolean, AUTOMATIC )                   availableStatus;
    VAR( Dem_u08_IUMPRRatioKindType, AUTOMATIC )                     ratioKind;

    retVal                  = DEM_IRT_NG;
    demRatioNum             = Dem_RatioNum;

    if( RatioId < demRatioNum )                                                     /* [GUD:if]RatioId */
    {
        eventCtrlIndex      = Dem_RatioTable[ RatioId ].DemDiagnosticEventRef;      /* [GUD]RatioId *//* [GUD:CFG:IF_GUARDED: RatioId ]eventCtrlIndex */
        /* Gets event available status */
        availableStatus = Dem_DataAvl_GetEvtAvl( eventCtrlIndex );                  /* [GUD]eventCtrlIndex */
        if( availableStatus == (boolean)TRUE )
        {
            ratioKind   = Dem_RatioTable[ RatioId ].DemRatioKind;                   /* [GUD]RatioId */
            if( ratioKind == DEM_RATIO_API )
            {
                retVal      = DEM_IRT_OK;
            }
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_IUMPR_RepIUMPRFaultDetect                            */
/* Description   | Service for reporting that faults are possibly found     */
/*               | because all conditions are fullfilled.                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] RatioId :                                           */
/*               |          Ratio Identifier reporting that a respective    */
/*               |          monitor could have found a fault                */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IUMPR_RepIUMPRFaultDetect
(
    VAR( Dem_RatioIdType, AUTOMATIC ) RatioId
)
{

    Dem_IUMPRMng_SetRatioNumeAdditionCondition( RatioId );

    return;
}


/****************************************************************************/
/* Function Name | Dem_IUMPR_CheckLockReleaseCondition                      */
/* Description   | In order to communicate the status of the (additional)   */
/*               | denominator conditions among the OBD relevant ECUs, the  */
/*               | API is used to forward the condition status to a Dem of  */
/*               | a particular ECU.                                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] RatioId :                                           */
/*               |          Ratio Identifier reporting that a respective    */
/*               |          monitor could have found a fault                */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Operation was successful.            */
/*               |        DEM_IRT_NG : Operation failed.                    */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IUMPR_CheckLockReleaseCondition
(
    VAR( Dem_RatioIdType, AUTOMATIC ) RatioId
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )  retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )  checkDenGroup;
    VAR( Dem_u08_IUMPRDenGroupType, AUTOMATIC )   ratioDenGroup;
    VAR( Dem_u16_RatioIndexType, AUTOMATIC )    demRatioNum;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC )    eventCtrlIndex;
    VAR( boolean, AUTOMATIC )                   availableStatus;

    retVal                  = DEM_IRT_NG;
    checkDenGroup           = DEM_IRT_NG;
    demRatioNum             = Dem_RatioNum;

    if( RatioId < demRatioNum )                                         /* [GUD:if]RatioId */
    {
        ratioDenGroup   = Dem_RatioTable[ RatioId ].DemIUMPRDenGroup;   /* [GUD]RatioId */
        switch( ratioDenGroup )
        {
            case DEM_IUMPR_DEN_500MILL:
            case DEM_IUMPR_DEN_ONLY_PHYS_API:
            case DEM_IUMPR_DEN_PHYS_API:
                checkDenGroup   = DEM_IRT_OK;
                break;
            case DEM_IUMPR_DEN_COLDSTART:
            case DEM_IUMPR_DEN_EVAP:
            case DEM_IUMPR_DEN_NONE:
            default:
                /* No process */
                break;
        }
    }

    if( checkDenGroup == DEM_IRT_OK )
    {
        eventCtrlIndex      = Dem_RatioTable[ RatioId ].DemDiagnosticEventRef;  /* [GUD]RatioId *//* [GUD:CFG:IF_GUARDED: RatioId ]eventCtrlIndex */
        /* Gets event available status */
        availableStatus = Dem_DataAvl_GetEvtAvl( eventCtrlIndex );              /* [GUD]eventCtrlIndex */
        if( availableStatus == (boolean)TRUE )
        {
            retVal                  = DEM_IRT_OK;
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_IUMPR_UpdateDenUnlockCondition                       */
/* Description   | In order to communicate the status of the (additional)   */
/*               | denominator conditions among the OBD relevant ECUs, the  */
/*               | API is used to forward the condition status to a Dem of  */
/*               | a particular ECU.                                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] RatioId :                                           */
/*               |          Ratio Identifier reporting that a respective    */
/*               |          monitor could have found a fault                */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IUMPR_UpdateDenUnlockCondition
(
    VAR( Dem_RatioIdType, AUTOMATIC ) RatioId
)
{

    Dem_IUMPRMng_SetRatioDenUnlockCondition( RatioId );

    return;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dem_IUMPR_GetComponentRatio                              */
/* Description   | Get numerator and denominator for IUMPR.                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] GroupIndex :                                        */
/*               |          GroupIndex of IUMPRGroup for InfoType08 or 0B.  */
/*               | [out] NumeratorPtr   : Numerator.                        */
/*               | [out] DenominatorPtr : Denominator.                      */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_IUMPR_GetComponentRatio
(
    VAR( Dem_u08_IUMPRGroupIndexType, AUTOMATIC)    GroupIndex,                         /* [PRMCHK:CALLER] */
    P2VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC, AUTOMATIC )           NumeratorPtr,
    P2VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC, AUTOMATIC )           DenominatorPtr
)
{
    VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC )                    currentNumerator;
    VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC )                    currentDenominator;
    VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC )                    targetNumerator;
    VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC )                    targetDenominator;
    VAR( Dem_u16_RatioIndexType, AUTOMATIC )                    loopCount;
    VAR( Dem_u16_RatioIndexType, AUTOMATIC )                    ratioListNum;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC )    eventCtrlIndex;
    VAR( Dem_RatioIdType, AUTOMATIC )           ratioId;
    VAR( boolean, AUTOMATIC )                   availableStatus;
    VAR( boolean, AUTOMATIC )                   resultJudge;
#if ( DEM_CALIBRATION_BY_CALLOUT_SUPPORT == STD_ON )   /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC )                   outIUMPR;
#endif  /* ( DEM_CALIBRATION_BY_CALLOUT_SUPPORT == STD_ON )    */

    currentNumerator        = DEM_IUMPR_COUNTER_INITVALUE;
    currentDenominator      = DEM_IUMPR_COUNTER_INITVALUE;
    targetNumerator         = DEM_IUMPR_COUNTER_INITVALUE;
    targetDenominator       = DEM_IUMPR_COUNTER_INITVALUE;

    ratioListNum = Dem_IUMPRGroupTable[ GroupIndex ].TableNum;                              /* [GUDCHK:CALLER]GroupIndex */
    for( loopCount = (Dem_u16_RatioIndexType)0U; loopCount < ratioListNum; loopCount++ )    /* [GUD:for]loopCount */
    {
        ratioId     = Dem_IUMPRGroupTable[ GroupIndex ].RatioIdListAdr[ loopCount ];        /* [GUDCHK:CALLER]GroupIndex *//* [GUD]loopCount *//* [GUD:CFG:IF_GUARDED: GroupIndex/loopCount ]ratioId */
        eventCtrlIndex  = Dem_RatioTable[ ratioId ].DemDiagnosticEventRef;                  /* [GUDCHK:CALLER]GroupIndex *//* [GUD:CFG:IF_GUARDED: ratioId ]eventCtrlIndex */

        /* Gets event available status */
        availableStatus = Dem_DataAvl_GetEvtAvl( eventCtrlIndex );                          /* [GUDCHK:CALLER]GroupIndex */
        if( availableStatus == (boolean)TRUE )
        {
#if ( DEM_CALIBRATION_BY_CALLOUT_SUPPORT == STD_ON )   /*  [FuncSw]    */
            outIUMPR    =   Dem_CfgInfoPm_GetIUMPROutputNecessary( eventCtrlIndex );        /* [GUDCHK:CALLER]GroupIndex */
            if ( outIUMPR == (boolean)TRUE )
#endif  /* ( DEM_CALIBRATION_BY_CALLOUT_SUPPORT == STD_ON )    */
            {
                (void)Dem_IUMPRMng_GetRatioByRatioId( ratioId, &targetNumerator, &targetDenominator );  /* no return check required */
                resultJudge = Dem_IUMPR_JudgeMinThanCurrentRatio( currentNumerator, currentDenominator, targetNumerator, targetDenominator );
                if( resultJudge == (boolean)TRUE )
                {
                    currentNumerator    = targetNumerator;
                    currentDenominator  = targetDenominator;
                }
            }
        }
    }

    *NumeratorPtr       = currentNumerator;
    *DenominatorPtr     = currentDenominator;

    return;
}


/****************************************************************************/
/* Function Name | Dem_IUMPR_JudgeMinThanCurrentRatio                       */
/* Description   | Compare Ratio [para1/para2] > [para3/para4].             */
/* Preconditions | none                                                     */
/* Parameters    | [in] CurrentNumerator   : Current Numerator.             */
/*               | [in] CurrentDenominator : Current Denominator.           */
/*               | [in] TargetNumerator    : Target Numerator.              */
/*               | [in] TargetDenominator  : Target Denominator.            */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : Current >  Target .                       */
/*               |        FALSE : Current <= Target.                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_IUMPR_JudgeMinThanCurrentRatio
(
    VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC )    CurrentNumerator,
    VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC )    CurrentDenominator,
    VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC )    TargetNumerator,
    VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC )    TargetDenominator
)
{
    VAR( boolean, AUTOMATIC )   retVal;
    VAR( boolean, AUTOMATIC )   checkFlag;
    VAR( Dem_u32_IUMPRCycleCounterType, AUTOMATIC )    ratioA;
    VAR( Dem_u32_IUMPRCycleCounterType, AUTOMATIC )    ratioB;

    retVal = (boolean)FALSE;
    checkFlag = (boolean)TRUE;

    if( TargetNumerator == DEM_IUMPR_COUNTER_INITVALUE )
    {
        if( TargetDenominator == DEM_IUMPR_COUNTER_INITVALUE )
        {
            checkFlag = (boolean)FALSE;
        }
    }

    if( checkFlag == (boolean)TRUE )
    {
        if( CurrentNumerator == DEM_IUMPR_COUNTER_INITVALUE )
        {
            if( CurrentDenominator == DEM_IUMPR_COUNTER_INITVALUE )
            {
                retVal      = (boolean)TRUE;
                checkFlag   = (boolean)FALSE;
            }
        }
    }

    if( checkFlag == (boolean)TRUE )
    {
        ratioA = (Dem_u32_IUMPRCycleCounterType)CurrentNumerator * (Dem_u32_IUMPRCycleCounterType)TargetDenominator;      /*  no wrap around      */
        ratioB = (Dem_u32_IUMPRCycleCounterType)TargetNumerator * (Dem_u32_IUMPRCycleCounterType)CurrentDenominator;      /*  no wrap around      */

        if( ratioA > ratioB )
        {
            retVal = (boolean)TRUE;
        }
        else
        {
            if( ratioA == ratioB )
            {
                if( CurrentDenominator < TargetDenominator )
                {
                    retVal = (boolean)TRUE;
                }
                else
                {
                    if( CurrentDenominator == TargetDenominator )
                    {
                        if( CurrentNumerator > TargetNumerator )
                        {
                            retVal = (boolean)TRUE;
                        }
                    }
                }
            }
        }
    }

    return retVal;
}



/****************************************************************************/
/* Function Name | Dem_IUMPR_UpdateRatioCounter                             */
/* Description   | Processes IUMPR updating.                                */
/* Preconditions | none                                                     */
/* Parameters    | [in]  FirstTime :                                        */
/*               |         TRUE: First start of the process in a period.    */
/*               | [in]  GenDenCondState :                                  */
/*               | [in]  GenDenFidPermission :                              */
/*               | [out] ProcessCompletePtr :                               */
/*               |         TRUE: UpdateProcess is completed.                */
/* Return Value  | void                                                     */
/* Notes         | This function is in Dem_MainFunction process.            */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IUMPR_UpdateRatioCounter
(
    VAR( boolean, AUTOMATIC )              FirstTime,
    VAR( Dem_IumprDenomCondStatusType, AUTOMATIC )  GenDenCondState,
    VAR( boolean, AUTOMATIC )                       GenDenFidPermission,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ProcessCompletePtr
)
{
    VAR( Dem_u16_RatioIndexType, AUTOMATIC )        demRatioNum;
    VAR( Dem_RatioIdType, AUTOMATIC )               ratioId;
    VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC )                        counterInCycle;
    VAR( Dem_u16_RatioIndexType, AUTOMATIC )        demIUMPRNumberOfRatioIdsPerCycle;

    demRatioNum             = Dem_RatioNum;
    *ProcessCompletePtr     = (boolean)FALSE;


    if( FirstTime == (boolean)TRUE )
    {
        /* Calculate General Denominator only for the first time. */
        Dem_NextCalcRatioId         = DEM_CALC_RATIO_ID_INDEX_INITIAL;
    }

    counterInCycle                      = DEM_IUMPR_COUNTER_INITVALUE;
    demIUMPRNumberOfRatioIdsPerCycle    = Dem_IUMPRNumberOfRatioIdsPerCycle;

    while( Dem_NextCalcRatioId < demRatioNum )
    {
        ratioId = Dem_NextCalcRatioId;

        Dem_IUMPR_UpdateRatioInfomation( ratioId, GenDenCondState, GenDenFidPermission );

        Dem_NextCalcRatioId = Dem_NextCalcRatioId + (Dem_RatioIdType)1U;
        counterInCycle = counterInCycle + (Dem_u16_IUMPRCycleCounterType)1U;
        if( counterInCycle >= demIUMPRNumberOfRatioIdsPerCycle )
        {
            break;
        }
    }

    if( Dem_NextCalcRatioId >= demRatioNum )
    {
        Dem_NextCalcRatioId     = DEM_CALC_RATIO_ID_INDEX_INITIAL;
        *ProcessCompletePtr     = (boolean)TRUE;
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_IUMPR_JudgeDenCondEst                                */
/* Description   | Judge Dennominator Condition Established                 */
/* Preconditions | none                                                     */
/* Parameters    | [in]  DenGroup :                                         */
/*               |         Denominator Group.                               */
/*               | [in]  Condition :                                        */
/*               |         Ratio Contidion Data.                            */
/*               | [in]  GenDenFidPermission :                              */
/*               |         FID Permission Of General Denominator.           */
/*               | [in]  RatioFidPermission :                               */
/*               |         FID Permission Of Ratio.                         */
/* Return Value  | boolean                                                  */
/* Notes         | This function is in Dem_MainFunction process.            */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_IUMPR_JudgeDenCondEst
(
    VAR( Dem_u08_IUMPRDenGroupType, AUTOMATIC )     DenGroup,
    VAR( Dem_u08_IUMPRRatioCondType, AUTOMATIC )                         Condition,
    VAR( boolean, AUTOMATIC )                       GenDenFidPermission,
    VAR( boolean, AUTOMATIC )                       RatioFidPermission
)
{
    VAR( boolean, AUTOMATIC )                       retVal;

    retVal = (boolean)FALSE;

    switch( DenGroup )
    {
        case DEM_IUMPR_DEN_500MILL :
            if( (Dem_u08_IUMPRRatioCondType)(Condition & DEM_IUMPRMNG_RTO_COND_HST_GDN) == DEM_IUMPRMNG_RTO_COND_HST_GDN )
            {
                if( GenDenFidPermission == (boolean)TRUE )
                {
                    if( (Dem_u08_IUMPRRatioCondType)(Condition & DEM_IUMPRMNG_RTO_COND_HST_500) == DEM_IUMPRMNG_RTO_COND_HST_500 )
                    {
                        if( RatioFidPermission == (boolean)TRUE )
                        {
                            retVal = (boolean)TRUE;
                        }
                    }
                }
            }
            break;
        case DEM_IUMPR_DEN_COLDSTART :
        case DEM_IUMPR_DEN_EVAP :
        case DEM_IUMPR_DEN_PHYS_API :
            if( GenDenFidPermission == (boolean)TRUE )
            {
                /* Since GenDenCondState is DEM_IUMPR_DEN_STATUS_REACHED ,      */
                /* the condition that GenDenFidPermission is TRUE is satisfied  */
                if( (Dem_u08_IUMPRRatioCondType)(Condition & DEM_IUMPRMNG_RTO_COND_DEN_EST) == DEM_IUMPRMNG_RTO_COND_DEN_EST )
                {
                    if( RatioFidPermission == (boolean)TRUE )
                    {
                        retVal = (boolean)TRUE;
                    }
                }
            }
            break;
        case DEM_IUMPR_DEN_NONE :
            if( GenDenFidPermission == (boolean)TRUE )
            {
                retVal = (boolean)TRUE;
            }
            break;
        case DEM_IUMPR_DEN_ONLY_PHYS_API :
            if( (Dem_u08_IUMPRRatioCondType)(Condition & DEM_IUMPRMNG_RTO_COND_DEN_EST) == DEM_IUMPRMNG_RTO_COND_DEN_EST )
            {
                if( RatioFidPermission == (boolean)TRUE )
                {
                    retVal = (boolean)TRUE;
                }
            }
            break;
        default :
            /* No process */
            break;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_IUMPR_GetNotificationParam                           */
/* Description   | Get SWC Notification Parameter.                          */
/* Preconditions | none                                                     */
/* Parameters    | [in]  AddRatioNume :                                     */
/*               |         Numerator Updating.                              */
/*               | [in]  AddRatioDen :                                      */
/*               |         Denominator Updating.                            */
/*               | [out] IumprDataTypePtr :                                 */
/*               |         Notification Parameter.                          */
/* Return Value  | boolean                                                  */
/* Notes         | This function is in Dem_MainFunction process.            */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_IUMPR_GetNotificationParam
(
    VAR( boolean, AUTOMATIC )                           AddRatioNume,
    VAR( boolean, AUTOMATIC )                           AddRatioDen,
    P2VAR( Dem_IumprDataType, AUTOMATIC, AUTOMATIC )    IumprDataTypePtr
)
{
    VAR( boolean, AUTOMATIC )                       retVal;

    retVal  = (boolean)FALSE;

    if( AddRatioNume == (boolean)TRUE )
    {
        if( AddRatioDen == (boolean)TRUE )
        {
            *IumprDataTypePtr   = DEM_IUMPR_DATA_DENOMINATOR_AND_NUMERATOR;
            retVal              = (boolean)TRUE;
        }
        else
        {
            *IumprDataTypePtr   = DEM_IUMPR_DATA_NUMERATOR;
            retVal              = (boolean)TRUE;
        }
    }
    else
    {
        if( AddRatioDen == (boolean)TRUE )
        {
            *IumprDataTypePtr   = DEM_IUMPR_DATA_DENOMINATOR;
            retVal              = (boolean)TRUE;
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_IUMPR_UpdateHistCondition                            */
/* Description   | Update History Condition.                                */
/* Preconditions | none                                                     */
/* Parameters    | [in] GenDenomCondStatus :                                */
/*               |         Condition Of General Denominator                 */
/*               | [inout] ConditionPtr :                                   */
/*               |         Condition Of RatioId.                            */
/* Return Value  | boolean                                                  */
/* Notes         | This function is in Dem_MainFunction process.            */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_IUMPR_UpdateHistCondition
(
    VAR( Dem_IumprDenomCondStatusType, AUTOMATIC )  GenDenomCondStatus,
    P2VAR( Dem_u08_IUMPRRatioCondType, AUTOMATIC, AUTOMATIC )            ConditionPtr
)
{
    VAR( Dem_u08_IUMPRRatioCondType, AUTOMATIC )                         ratioCondition;
    VAR( Dem_IumprDenomCondStatusType, AUTOMATIC )  mi500CondState;

    ratioCondition  = *ConditionPtr;

    /* history of general denominator established */
    if( (Dem_u08_IUMPRRatioCondType)(ratioCondition & DEM_IUMPRMNG_RTO_COND_HST_GDN) != DEM_IUMPRMNG_RTO_COND_HST_GDN )
    {
        if( GenDenomCondStatus == DEM_IUMPR_DEN_STATUS_REACHED )
        {
            ratioCondition = (Dem_u08_IUMPRRatioCondType)( ratioCondition | DEM_IUMPRMNG_RTO_COND_HST_GDN );
        }
    }

    /* history of 500mile status reached setting of Dem_SetIUMPRDenCondition */
    if( (Dem_u08_IUMPRRatioCondType)(ratioCondition & DEM_IUMPRMNG_RTO_COND_HST_500) != DEM_IUMPRMNG_RTO_COND_HST_500 )
    {
        /* Setting of Dem_SetIUMPRDenCondition */
        Dem_IUMPRMng_GetIUMPRDenCondition( DEM_IUMPR_DEN_COND_500MI, &mi500CondState );
        if( mi500CondState == DEM_IUMPR_DEN_STATUS_REACHED )
        {
            ratioCondition = (Dem_u08_IUMPRRatioCondType)( ratioCondition | DEM_IUMPRMNG_RTO_COND_HST_500 );
        }
        else
        {
        /* Setting of Dem_RepIUMPRDenRelease */
            if( (Dem_u08_IUMPRRatioCondType)(ratioCondition & DEM_IUMPRMNG_RTO_COND_DEN_EST) == DEM_IUMPRMNG_RTO_COND_DEN_EST )
            {
                ratioCondition = (Dem_u08_IUMPRRatioCondType)( ratioCondition | DEM_IUMPRMNG_RTO_COND_HST_500 );
            }
        }
    }

    *ConditionPtr   = ratioCondition;

    return;
}


/****************************************************************************/
/* Function Name | Dem_IUMPR_UpdateRatioInfomation                          */
/* Description   | Update Ratio Counter And Condition                       */
/* Preconditions | none                                                     */
/* Parameters    | [in] RatioId :                                           */
/*               | [in] GenDenomCondStatus :                                */
/*               |         Condition Of General Denominator                 */
/*               | [in] GenDenomFidPermission :                             */
/*               |         Permission Status Of General Denominator         */
/* Return Value  | boolean                                                  */
/* Notes         | This function is in Dem_MainFunction process.            */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_IUMPR_UpdateRatioInfomation
(
    VAR( Dem_RatioIdType, AUTOMATIC )               RatioId,
    VAR( Dem_IumprDenomCondStatusType, AUTOMATIC )  GenDenomCondStatus,
    VAR( boolean, AUTOMATIC )                       GenDenomFidPermission
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )                         retGetRatioInf;
    VAR( Dem_u08_IUMPRRatioCondType, AUTOMATIC )                         ratioCondition;
    VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC )                        ratioNumeCounter;
    VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC )                        ratioDenCounter;
    VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC )                        remainderDen;
    VAR( Dem_FiM_FunctionIdType, AUTOMATIC )        ratioFunctionIdRef;
    VAR( Std_ReturnType, AUTOMATIC )                retGetPermission;
    VAR( boolean, AUTOMATIC )                       ratioFidPermission;
    VAR( boolean, AUTOMATIC )                       addRatioDen;
    VAR( boolean, AUTOMATIC )                       addRatioNume;
    VAR( Dem_u08_IUMPRDenGroupType, AUTOMATIC )     ratioIUMPRDenGroup;
    VAR( boolean, AUTOMATIC )                       denEstablished;
    VAR( boolean, AUTOMATIC )                       ratioUpdNtfSup;
    VAR( boolean, AUTOMATIC )                       retGetNtyParam;
    VAR( Dem_IumprDataType, AUTOMATIC )             iumprDataType;
    VAR( Dem_FiM_FunctionIdType, AUTOMATIC )        fiMFidDummy;

    fiMFidDummy             = Dem_FiMFId_Dummy;

    retGetRatioInf = Dem_IUMPRMng_GetRatioInformation( RatioId, &ratioCondition, &ratioNumeCounter, &ratioDenCounter ); /* [GUD:RET:DEM_IRT_OK] RatioId */

    if( retGetRatioInf == DEM_IRT_OK )
    {
        addRatioDen         = (boolean)FALSE;
        addRatioNume        = (boolean)FALSE;

        ratioIUMPRDenGroup = Dem_RatioTable[ RatioId ].DemIUMPRDenGroup;                                /* [GUD]RatioId */
        /* Update Ratio Condition Data */
        Dem_IUMPR_UpdateRatioCondition( ratioIUMPRDenGroup, GenDenomCondStatus, &ratioCondition );

        ratioFidPermission = (boolean)TRUE;
        ratioFunctionIdRef = Dem_RatioTable[ RatioId ].DemFunctionIdRef;                                /* [GUD]RatioId */
        if( ratioFunctionIdRef != fiMFidDummy )
        {
            retGetPermission        = Dem_FiM_GetFunctionPermission( ratioFunctionIdRef, &ratioFidPermission );
            if( retGetPermission != (Std_ReturnType)E_OK )
            {
                ratioFidPermission  = (boolean)FALSE;
            }
        }

        if( (Dem_u08_IUMPRRatioCondType)(ratioCondition & DEM_IUMPRMNG_RTO_COND_DEN_ADD) != DEM_IUMPRMNG_RTO_COND_DEN_ADD )
        {
            denEstablished = Dem_IUMPR_JudgeDenCondEst( ratioIUMPRDenGroup, ratioCondition, GenDenomFidPermission, ratioFidPermission );
            /* calc Denominator */
            if( denEstablished == (boolean)TRUE )
            {
                if( ratioDenCounter != DEM_IUMPR_COUNTER_MAXVALUE )
                {
                    ratioDenCounter = ratioDenCounter + (uint16)1U;
                }
                else
                {
                    ratioDenCounter     = DEM_IUMPR_COUNTER_HALFVALUE;
                    ratioNumeCounter    = (uint16)( ratioNumeCounter >> DEM_IUMPR_COUNTER_HALFSHIFT );
                }
                addRatioDen     = (boolean)TRUE;
                ratioCondition  = (Dem_u08_IUMPRRatioCondType)(ratioCondition | DEM_IUMPRMNG_RTO_COND_DEN_ADD);
                if( ratioIUMPRDenGroup == DEM_IUMPR_DEN_500MILL )
                {
                    /* Clear history bit */
                    ratioCondition = (Dem_u08_IUMPRRatioCondType)( ratioCondition & (Dem_u08_IUMPRRatioCondType)~(DEM_IUMPRMNG_RTO_COND_HST_500) );
                    ratioCondition = (Dem_u08_IUMPRRatioCondType)( ratioCondition & (Dem_u08_IUMPRRatioCondType)~(DEM_IUMPRMNG_RTO_COND_HST_GDN) );
                }
            }
        }
        if( (Dem_u08_IUMPRRatioCondType)(ratioCondition & DEM_IUMPRMNG_RTO_COND_NUME_ADD) != DEM_IUMPRMNG_RTO_COND_NUME_ADD )
        {
            if( (Dem_u08_IUMPRRatioCondType)(ratioCondition & DEM_IUMPRMNG_RTO_COND_NUME_EST) == DEM_IUMPRMNG_RTO_COND_NUME_EST )
            {
                if( ratioFidPermission == (boolean)TRUE )
                {
                    if( ratioNumeCounter != DEM_IUMPR_COUNTER_MAXVALUE )
                    {
                        ratioNumeCounter = ratioNumeCounter + (uint16)1U;
                    }
                    else
                    {
                        ratioNumeCounter    = DEM_IUMPR_COUNTER_HALFVALUE;
                        remainderDen        = (Dem_u16_IUMPRCycleCounterType)( ratioDenCounter & DEM_IUMPR_REMAIN_DEVIDED_TWO );
                        ratioDenCounter     = (Dem_u16_IUMPRCycleCounterType)( ratioDenCounter >> DEM_IUMPR_COUNTER_HALFSHIFT );
                        ratioDenCounter     = ratioDenCounter + remainderDen;
                    }
                    addRatioNume        = (boolean)TRUE;
                    ratioCondition      = (Dem_u08_IUMPRRatioCondType)(ratioCondition | DEM_IUMPRMNG_RTO_COND_NUME_ADD);
                }
            }
        }
        ratioUpdNtfSup = Dem_RatioTable[ RatioId ].DemRatioUpdateNotificationSupport;                               /* [GUD]RatioId */
        if( ratioUpdNtfSup == (boolean)TRUE )
        {
            retGetNtyParam  = Dem_IUMPR_GetNotificationParam( addRatioNume, addRatioDen, &iumprDataType );
            if( retGetNtyParam == (boolean)TRUE )
            {
                Dem_IUMPR_NotifyRatioUpdate( RatioId, iumprDataType );                                              /* [GUD]RatioId */
            }
        }
        /* Update Data */
        Dem_IUMPRMng_SetRatioInformation( RatioId, ratioCondition, ratioNumeCounter, ratioDenCounter );             /* [GUD]RatioId */

    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_IUMPR_UpdateRatioCondition                           */
/* Description   | Update Ratio Condition                                   */
/* Preconditions | none                                                     */
/* Parameters    | [in ] DenGroup :                                         */
/*               |         IUMPRDenGroup                                    */
/*               | [in ] GenDenomCondStatus :                               */
/*               |         Condition Of General Denominator                 */
/*               | [inout] RatioConditionPtr :                              */
/*               |         Ratio Condition Datal Denominator                */
/* Return Value  | boolean                                                  */
/* Notes         | This function is in Dem_MainFunction process.            */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_IUMPR_UpdateRatioCondition
(
    VAR( Dem_u08_IUMPRDenGroupType, AUTOMATIC )     DenGroup,
    VAR( Dem_IumprDenomCondStatusType, AUTOMATIC )  GenDenomCondStatus,
    P2VAR( Dem_u08_IUMPRRatioCondType, AUTOMATIC, AUTOMATIC )            RatioConditionPtr
)
{

    if( DenGroup == DEM_IUMPR_DEN_500MILL )
    {
        Dem_IUMPR_UpdateHistCondition( GenDenomCondStatus, RatioConditionPtr );
    }
    else if( DenGroup == DEM_IUMPR_DEN_COLDSTART )
    {
        Dem_IUMPR_UpdateDenEstRatioCond( DEM_IUMPR_DEN_COND_COLDSTART, RatioConditionPtr );
    }
    else if( DenGroup == DEM_IUMPR_DEN_EVAP )
    {
        Dem_IUMPR_UpdateDenEstRatioCond( DEM_IUMPR_DEN_COND_EVAP, RatioConditionPtr );
    }
    else
    {
        /* No process */
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_IUMPR_UpdateDenEstRatioCond                          */
/* Description   | Update Denominator Established bit of Ratio Condition    */
/* Preconditions | none                                                     */
/* Parameters    | [in ] ConditionId :                                      */
/*               |         ConditionId                                      */
/*               | [inout] RatioConditionPtr :                              */
/*               |         Ratio Condition Datal Denominator                */
/* Return Value  | boolean                                                  */
/* Notes         | This function is in Dem_MainFunction process.            */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_IUMPR_UpdateDenEstRatioCond
(
    VAR( Dem_IumprDenomCondIdType, AUTOMATIC )      ConditionId,
    P2VAR( Dem_u08_IUMPRRatioCondType, AUTOMATIC, AUTOMATIC )            RatioConditionPtr
)
{
    VAR( Dem_u08_IUMPRRatioCondType, AUTOMATIC )                         ratioCondition;
    VAR( Dem_IumprDenomCondStatusType, AUTOMATIC )  condState;

    ratioCondition  = *RatioConditionPtr;

    /* Check whether it has been established in current cycle */
    if( (Dem_u08_IUMPRRatioCondType)(ratioCondition & DEM_IUMPRMNG_RTO_COND_DEN_EST) != DEM_IUMPRMNG_RTO_COND_DEN_EST )
    {
        /* Setting of Dem_SetIUMPRDenCondition */
        Dem_IUMPRMng_GetIUMPRDenCondition( ConditionId, &condState );
        if( condState == DEM_IUMPR_DEN_STATUS_REACHED )
        {
            ratioCondition = (Dem_u08_IUMPRRatioCondType)( ratioCondition | DEM_IUMPRMNG_RTO_COND_DEN_EST );
        }
    }

    *RatioConditionPtr  = ratioCondition;

    return;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif  /* ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
