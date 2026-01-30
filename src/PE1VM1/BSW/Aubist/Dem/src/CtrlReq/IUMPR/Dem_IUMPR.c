/* Dem_IUMPR_c(v5-10-0)                                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/IUMPR/CODE                                            */
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
#include "../../../inc/Dem_Pm_IUMPR.h"
#include "../../../inc/Dem_Rc_IUMPRMng.h"
#include "../../../usr/Dem_IUMPR_Callout.h"
#include "../../../usr/Dem_IUMPR_FiM_Connector.h"
#include "../../../inc/Dem_CmnLib_OpCycle.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../cfg/Dem_OpCycle_Cfg.h"
#include "Dem_IUMPR_local.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IUMPR_CheckDenConditionId
(
    VAR( Dem_IumprDenomCondIdType, AUTOMATIC ) ConditionId
);

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IUMPR_CheckDenConditionStatus
(
    VAR( Dem_IumprDenomCondStatusType, AUTOMATIC )  ConditionStatus
);

static FUNC( void, DEM_CODE ) Dem_IUMPR_UpdateIGCycleCounter
( void );

static FUNC( void, DEM_CODE ) Dem_IUMPR_UpdateGenDenominator
(
    P2VAR( Dem_IumprDenomCondStatusType, AUTOMATIC, AUTOMATIC ) GenDenomCondStatusPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC )                      GenDenomFidPermissionPtr
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#if ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )
static VAR( Dem_IumprDenomCondStatusType, DEM_VAR_NO_INIT ) Dem_GenDenCondState;
static VAR( boolean, DEM_VAR_NO_INIT )                      Dem_GenDenFidPermission;
#endif  /* ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )            */

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
FUNC( void, DEM_CODE ) Dem_IUMPR_Init
( void )
{
#if ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )   /*  [FuncSw]    */
    Dem_IUMPR_Ratio_Init();

    Dem_GenDenCondState     = DEM_IUMPR_DEN_STATUS_NOT_REACHED;
    Dem_GenDenFidPermission = (boolean)FALSE;
#endif  /* ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )            */

    return;
}

/****************************************************************************/
/* Function Name | Dem_IUMPR_ClearIUMPRCondition                            */
/* Description   | Clear IUMPR condition.                                   */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]IUMPR                                            */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IUMPR_ClearIUMPRCondition
( void )
{
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC )      opcycleIdxIGCycleCounter;

    Dem_IUMPRMng_ClearCondition();      /*[UpdRec]IUMPR */

    opcycleIdxIGCycleCounter = Dem_ConfDemOperationCycleIGCycleCounter;
    Dem_OpCycle_SetCycleStartNoticeFlag( opcycleIdxIGCycleCounter, DEM_CYCLE_NOTIFY_END );

    return;
}


/****************************************************************************/
/* Function Name | Dem_IUMPR_GetIUMPRDenCondition                           */
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
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IUMPR_GetIUMPRDenCondition
(
    VAR( Dem_IumprDenomCondIdType, AUTOMATIC ) ConditionId,
    P2VAR( Dem_IumprDenomCondStatusType, AUTOMATIC, AUTOMATIC ) ConditionStatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )                     retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )                     retCheckCondId;
    VAR( Std_ReturnType, AUTOMATIC )            retGetPermission;
    VAR( boolean, AUTOMATIC )                   permission;
    VAR( Dem_FiM_FunctionIdType, AUTOMATIC )    demOBDGeneralDenominatorFIdRef;
    VAR( Dem_FiM_FunctionIdType, AUTOMATIC )    fiMFidDummy;

    retVal = DEM_IRT_NG;

    retCheckCondId = Dem_IUMPR_CheckDenConditionId( ConditionId );
    if (retCheckCondId == DEM_IRT_OK)
    {
        if( ConditionId == DEM_IUMPR_GENERAL_DENOMINATOR )
        {
            Dem_IUMPRMng_GetIUMPRDenCondition( ConditionId, ConditionStatusPtr );
            if( *ConditionStatusPtr == DEM_IUMPR_DEN_STATUS_NOT_REACHED )
            {
                demOBDGeneralDenominatorFIdRef  = Dem_OBDGeneralDenominatorFIdRef;
                fiMFidDummy                     = Dem_FiMFId_Dummy;
                if( demOBDGeneralDenominatorFIdRef != fiMFidDummy )
                {
                    permission          = (boolean)FALSE;
                    retGetPermission    = Dem_FiM_GetFunctionPermission( demOBDGeneralDenominatorFIdRef, &permission );
                    if( retGetPermission != (Std_ReturnType)E_OK )
                    {
                        permission      = (boolean)FALSE;
                    }
                    if( permission == (boolean)FALSE )
                    {
                        *ConditionStatusPtr = DEM_IUMPR_DEN_STATUS_INHIBITED;
                    }
                }
            }
        }
        else
        {
            /* if( ConditionId == DEM_IUMPR_DEN_COND_COLDSTART ) */
            /* if( ConditionId == DEM_IUMPR_DEN_COND_EVAP ) */
            /* if( ConditionId == DEM_IUMPR_DEN_COND_500MI ) */
            Dem_IUMPRMng_GetIUMPRDenCondition( ConditionId, ConditionStatusPtr );
        }

        retVal = DEM_IRT_OK;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_IUMPR_GetGeneralDenominator                          */
/* Description   | Get general denominator for IUMPR.                       */
/* Preconditions | none                                                     */
/* Parameters    | [out] GeneralDenominatorPtr : General Denominator.       */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IUMPR_GetGeneralDenominator
(
    P2VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC, AUTOMATIC )   GeneralDenominatorPtr
)
{

    Dem_IUMPRMng_GetGeneralDenominator( GeneralDenominatorPtr );

    return;
}


/****************************************************************************/
/* Function Name | Dem_IUMPR_GetIGCycleCounter                              */
/* Description   | Get IG cycle counter for IUMPR.                          */
/* Preconditions | none                                                     */
/* Parameters    | [out] IGCycleCounterPtr : IG cycle counter.              */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IUMPR_GetIGCycleCounter
(
    P2VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC, AUTOMATIC )   IGCycleCounterPtr
)
{

    Dem_IUMPRMng_GetIGCycleCounter( IGCycleCounterPtr );

    return;
}


/****************************************************************************/
/* Function Name | Dem_IUMPR_GetInitInfoTypeValue                           */
/* Description   | Service is used for requesting IUMPR data according to   */
/*               | InfoType 0x08 or 0x0B.                                   */
/* Preconditions | none                                                     */
/* Parameters    | [out] IumprdataPtr :                                     */
/*               |          Buffer containing the contents of               */
/*               |          InfoType 0x08 or 0x0B.                          */
/*               |          The buffer is provided by the Dcm.              */
/*               | [inout] BuffSizePtr :                                    */
/*               |          Buffer containing the number of data elements   */
/*               |          (as defined in ISO-15031-5) and contents of     */
/*               |          InfoType 0x0B.                                  */
/*               |          The buffer is provided by the Dcm.              */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Operation was successful.            */
/*               |        DEM_IRT_NG : Operation failed.                    */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-7-0      | no object changed.                                       */
/*   v5-10-0     | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IUMPR_GetInitInfoTypeValue
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA )        IumprdataPtr,
    P2VAR( uint8 , AUTOMATIC, AUTOMATIC )           BuffSizePtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )    retVal;
    VAR( Dem_u08_IUMPRGroupIndexType, AUTOMATIC )   groupIndex;
    VAR( uint8, AUTOMATIC )                         dataPos;
    VAR( Dem_u08_IUMPRGroupIndexType, AUTOMATIC )   reqIumprGroupNum;
    VAR( uint8, AUTOMATIC )                         dataSize;
    VAR( Dem_u08_IUMPRNODIValueType, AUTOMATIC )        nodiValue;
    VAR( Dem_u08_IUMPRGroupIndexType, AUTOMATIC )       nodiGroupNum;
    VAR( Dem_u08_IUMPRNODIOutputSizeType, AUTOMATIC )   nodiOutputSize;

    retVal              = DEM_IRT_NG;

    Dem_CfgInfoPm_GetNODIInfo( &nodiValue, &nodiGroupNum, &nodiOutputSize );

    dataSize            = nodiOutputSize + DEM_IUMPR_NODI_SIZE;

    if( *BuffSizePtr >= dataSize )
    {
        reqIumprGroupNum                    = nodiGroupNum;

        IumprdataPtr[DEM_IUMPR_POS0]        = nodiValue;                /* [ARYCHK] *BuffSizePtr/1/DEM_IUMPR_POS0 */
        IumprdataPtr[DEM_IUMPR_POS1]        = DEM_IUMPR_DATA_INITVALUE; /* [ARYCHK] *BuffSizePtr/1/DEM_IUMPR_POS1 */
        IumprdataPtr[DEM_IUMPR_POS2]        = DEM_IUMPR_DATA_INITVALUE; /* [ARYCHK] *BuffSizePtr/1/DEM_IUMPR_POS2 */

        IumprdataPtr[DEM_IUMPR_POS3]        = DEM_IUMPR_DATA_INITVALUE; /* [ARYCHK] *BuffSizePtr/1/DEM_IUMPR_POS3 */
        IumprdataPtr[DEM_IUMPR_POS4]        = DEM_IUMPR_DATA_INITVALUE; /* [ARYCHK] *BuffSizePtr/1/DEM_IUMPR_POS4 */

        for( groupIndex = (Dem_u08_IUMPRGroupIndexType)0U; groupIndex < reqIumprGroupNum; groupIndex++ )
        {
            dataPos = groupIndex * DEM_IUMPR_RATIO_DATA_SIZE;
            IumprdataPtr[dataPos + DEM_IUMPR_POS5] = DEM_IUMPR_DATA_INITVALUE;/* [ARYCHK] *BuffSizePtr/1/dataPos+DEM_IUMPR_POS5 */
            IumprdataPtr[dataPos + DEM_IUMPR_POS6] = DEM_IUMPR_DATA_INITVALUE;/* [ARYCHK] *BuffSizePtr/1/dataPos+DEM_IUMPR_POS6 */
            IumprdataPtr[dataPos + DEM_IUMPR_POS7] = DEM_IUMPR_DATA_INITVALUE;/* [ARYCHK] *BuffSizePtr/1/dataPos+DEM_IUMPR_POS7 */
            IumprdataPtr[dataPos + DEM_IUMPR_POS8] = DEM_IUMPR_DATA_INITVALUE;/* [ARYCHK] *BuffSizePtr/1/dataPos+DEM_IUMPR_POS8 */
        }
        *BuffSizePtr    = dataSize;
        retVal          = DEM_IRT_OK;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_IUMPR_GetInfoTypeValue                               */
/* Description   | Service is used for requesting IUMPR data according to   */
/*               | InfoType 0x08 or 0x0B.                                   */
/* Preconditions | none                                                     */
/* Parameters    | [out] IumprdataPtr :                                     */
/*               |          Buffer containing the contents of               */
/*               |          InfoType 0x08 or 0x0B.                          */
/*               |          The buffer is provided by the Dcm.              */
/*               | [inout] BuffSizePtr :                                    */
/*               |          Buffer containing the number of data elements   */
/*               |          (as defined in ISO-15031-5) and contents of     */
/*               |          InfoType 0x0B.                                  */
/*               |          The buffer is provided by the Dcm.              */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Operation was successful.            */
/*               |        DEM_IRT_NG : Operation failed.                    */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-7-0      | no object changed.                                       */
/*   v5-10-0     | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IUMPR_GetInfoTypeValue
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA )        IumprdataPtr,
    P2VAR( uint8 , AUTOMATIC, AUTOMATIC )           BuffSizePtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )    retVal;
    VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC )                        genDeno;
    VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC )                        igCycCtr;
    VAR( uint8, AUTOMATIC )                         dataSize;
    VAR( Dem_u08_IUMPRNODIValueType, AUTOMATIC )        nodiValue;
    VAR( Dem_u08_IUMPRGroupIndexType, AUTOMATIC )       nodiGroupNum;
    VAR( Dem_u08_IUMPRNODIOutputSizeType, AUTOMATIC )   nodiOutputSize;

    genDeno             = DEM_IUMPR_COUNTER_INITVALUE;
    igCycCtr            = DEM_IUMPR_COUNTER_INITVALUE;
    retVal              = DEM_IRT_NG;

    Dem_CfgInfoPm_GetNODIInfo( &nodiValue, &nodiGroupNum, &nodiOutputSize );

    dataSize            = nodiOutputSize + DEM_IUMPR_NODI_SIZE;

    if( *BuffSizePtr >= dataSize )
    {
        IumprdataPtr[DEM_IUMPR_POS0]        = nodiValue;                                    /* [ARYCHK] *BuffSizePtr/1/DEM_IUMPR_POS0 */

        Dem_IUMPRMng_GetGeneralDenominator(&genDeno);
        IumprdataPtr[DEM_IUMPR_POS1]        = (uint8)(genDeno >> DEM_IUMPR_COUNTER_SHIFT);  /* [ARYCHK] *BuffSizePtr/1/DEM_IUMPR_POS1 */
        IumprdataPtr[DEM_IUMPR_POS2]        = (uint8)(genDeno);                             /* [ARYCHK] *BuffSizePtr/1/DEM_IUMPR_POS2 */

        Dem_IUMPRMng_GetIGCycleCounter(&igCycCtr);
        IumprdataPtr[DEM_IUMPR_POS3]        = (uint8)(igCycCtr >> DEM_IUMPR_COUNTER_SHIFT); /* [ARYCHK] *BuffSizePtr/1/DEM_IUMPR_POS3 */
        IumprdataPtr[DEM_IUMPR_POS4]        = (uint8)(igCycCtr);                            /* [ARYCHK] *BuffSizePtr/1/DEM_IUMPR_POS4 */

#ifndef DEM_SIT_RANGE_CHECK
        Dem_IUMPR_Ratio_GetInfoTypeValue( IumprdataPtr, nodiGroupNum );
#else   /* DEM_SIT_RANGE_CHECK */
        Dem_IUMPR_Ratio_GetInfoTypeValue( *BuffSizePtr, IumprdataPtr, nodiGroupNum );
#endif  /* DEM_SIT_RANGE_CHECK */

        *BuffSizePtr    = dataSize;
        retVal          = DEM_IRT_OK;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Control_UpdateIUMPRProcess                           */
/* Description   | Processes IUMPR updating.                                */
/* Preconditions | none                                                     */
/* Parameters    | [in]  FirstTime :                                        */
/*               |         TRUE: First start of the process in a period.    */
/*               | [out] ProcessCompletePtr :                               */
/*               |         TRUE: UpdateProcess is completed.                */
/* Return Value  | void                                                     */
/* Notes         | This function is in Dem_MainFunction process.            */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]IUMPR                                            */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IUMPR_UpdateIUMPRProcess
(
    VAR( boolean, AUTOMATIC )              FirstTime,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ProcessCompletePtr   /* MISRA DEVIATION */
)
{
    VAR( Dem_IumprDenomCondStatusType, AUTOMATIC )  genDenCondState;
    VAR( boolean, AUTOMATIC )                       genDenFidPermission;

    if( FirstTime == (boolean)TRUE )
    {
        Dem_IUMPR_UpdateIGCycleCounter();   /*[UpdRec]IUMPR */

        genDenFidPermission         = (boolean)FALSE;

        Dem_IUMPR_UpdateGenDenominator( &genDenCondState, &genDenFidPermission );   /*[UpdRec]IUMPR */

#if ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )   /*  [FuncSw]    */
        Dem_GenDenCondState         = genDenCondState;
        Dem_GenDenFidPermission     = genDenFidPermission;
#endif  /* ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )            */
    }

#if ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )   /*  [FuncSw]    */
    Dem_IUMPR_UpdateRatioCounter( FirstTime, Dem_GenDenCondState, Dem_GenDenFidPermission, ProcessCompletePtr );    /*[UpdRec]IUMPR */
#endif  /* ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )            */

    return;

}


/****************************************************************************/
/* Function Name | Dem_IUMPR_CheckCondSettingParameter                      */
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
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IUMPR_CheckCondSettingParameter
(
    VAR( Dem_IumprDenomCondIdType, AUTOMATIC )      ConditionId,
    VAR( Dem_IumprDenomCondStatusType, AUTOMATIC )  ConditionStatus
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )     retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )     checkCondId;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )     checkCondSts;

    retVal              = DEM_IRT_NG;

    checkCondId         = Dem_IUMPR_CheckDenConditionId( ConditionId );
    if( checkCondId == DEM_IRT_OK )
    {
        checkCondSts    = Dem_IUMPR_CheckDenConditionStatus( ConditionStatus );
        if( checkCondSts == DEM_IRT_OK )
        {
            retVal      = DEM_IRT_OK;
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_IUMPR_SetIUMPRDenCondition                           */
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
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]IUMPR                                            */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IUMPR_SetIUMPRDenCondition
(
    VAR( Dem_IumprDenomCondIdType, AUTOMATIC )      ConditionId,
    VAR( Dem_IumprDenomCondStatusType, AUTOMATIC )  ConditionStatus
)
{

    Dem_IUMPRMng_SetIUMPRDenCondition( ConditionId, ConditionStatus );  /*[UpdRec]IUMPR */

    return;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dem_IUMPR_CheckDenConditionId                            */
/* Description   | In order to communicate the status of the (additional)   */
/*               | denominator conditions among the OBD relevant ECUs, the  */
/*               | API is used to retrieve the condition status from the    */
/*               | Dem of the ECU where the conditions are computed.        */
/* Preconditions | none                                                     */
/* Parameters    | [in] ConditionId :                                       */
/*               |          Identification of a IUMPR denominator           */
/*               |          condition ID.                                   */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Operation was successful.            */
/*               |        DEM_IRT_NG : Operation failed.                    */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IUMPR_CheckDenConditionId
(
    VAR( Dem_IumprDenomCondIdType, AUTOMATIC ) ConditionId
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )     retVal;

    retVal          = DEM_IRT_NG;

    switch( ConditionId )
    {
        case DEM_IUMPR_GENERAL_DENOMINATOR:
        case DEM_IUMPR_DEN_COND_COLDSTART:
        case DEM_IUMPR_DEN_COND_EVAP:
        case DEM_IUMPR_DEN_COND_500MI:
            retVal  = DEM_IRT_OK;
            break;
        default:
            /* No process */
            break;
    }
    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_IUMPR_CheckDenConditionStatus                        */
/* Description   | In order to communicate the status of the (additional)   */
/*               | denominator conditions among the OBD relevant ECUs, the  */
/*               | API is used to retrieve the condition status from the    */
/*               | Dem of the ECU where the conditions are computed.        */
/* Preconditions | none                                                     */
/* Parameters    | [in] ConditionId :                                       */
/*               |          Identification of a IUMPR denominator           */
/*               |          condition ID.                                   */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Operation was successful.            */
/*               |        DEM_IRT_NG : Operation failed.                    */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IUMPR_CheckDenConditionStatus
(
    VAR( Dem_IumprDenomCondStatusType, AUTOMATIC )  ConditionStatus
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )     retVal;

    retVal          = DEM_IRT_NG;

    switch( ConditionStatus )
    {
        case DEM_IUMPR_DEN_STATUS_REACHED:
            retVal  = DEM_IRT_OK;
            break;
        default:
            /* No process */
            break;
    }
    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_IUMPR_UpdateIGCycleCounter                           */
/* Description   | Processes IG Cycle counter updating.                     */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | This function is in Dem_MainFunction process.            */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]IUMPR                                            */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_IUMPR_UpdateIGCycleCounter
( void )
{
    VAR( boolean, AUTOMATIC )                       addedCondition;
    VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC  )                       igCycleCounter;
    VAR( Dem_OperationCycleStateType, AUTOMATIC )   operationCycleState;
    VAR( Std_ReturnType, AUTOMATIC )                retGetPermission;
    VAR( boolean, AUTOMATIC )                       fidPermission;
    VAR( Dem_FiM_FunctionIdType, AUTOMATIC )        fiMFidDummy;
    VAR( Dem_FiM_FunctionIdType, AUTOMATIC )        igCycleCounterFid;
    VAR( Dem_u08_CycleQualifiedIndexType, AUTOMATIC )      opcycleIdxIGCycleCounter;

    Dem_IUMPRMng_GetIGCycleInformation( &addedCondition, &igCycleCounter );

    if( addedCondition == (boolean)FALSE )
    {
        opcycleIdxIGCycleCounter = Dem_ConfDemOperationCycleIGCycleCounter;
        operationCycleState = Dem_OpCycle_GetCycleStartNoticeFlag( opcycleIdxIGCycleCounter );
        if( operationCycleState == DEM_CYCLE_NOTIFY_START )
        {
            fidPermission       = (boolean)TRUE;
            fiMFidDummy         = Dem_FiMFId_Dummy;
            igCycleCounterFid   = Dem_OBDIGCycleCounterFIdRef;

            if( igCycleCounterFid != fiMFidDummy )
            {
                retGetPermission    = Dem_FiM_GetFunctionPermission( igCycleCounterFid, &fidPermission );
                if( retGetPermission != (Std_ReturnType)E_OK )
                {
                    fidPermission   = (boolean)FALSE;
                }
            }

            if( fidPermission == (boolean)TRUE )
            {
                if( igCycleCounter == DEM_IUMPR_COUNTER_MAXVALUE )
                {
                    igCycleCounter = DEM_IUMPR_COUNTER_INITVALUE;
                }
                else
                {
                    igCycleCounter = igCycleCounter + (Dem_u16_IUMPRCycleCounterType)1U;
                }

                addedCondition = (boolean)TRUE;
                Dem_IUMPRMng_SetIGCycleInformation( addedCondition, igCycleCounter );   /*[UpdRec]IUMPR */

                Dem_IUMPR_NotifyIGCycleCounterUpdate();
            }
        }
    }

    return;

}


/****************************************************************************/
/* Function Name | Dem_IUMPR_UpdateGenDenominator                           */
/* Description   | Update General Denominator                               */
/* Preconditions | none                                                     */
/* Parameters    | [out] GenDenomCondStatusPtr :                            */
/*               |         Condition Of General Denominator                 */
/*               | [out] GenDenomFidPermissionPtr :                         */
/*               |         Permission Status Of General Denominator         */
/* Return Value  | boolean                                                  */
/* Notes         | This function is in Dem_MainFunction process.            */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]IUMPR                                            */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_IUMPR_UpdateGenDenominator
(
    P2VAR( Dem_IumprDenomCondStatusType, AUTOMATIC, AUTOMATIC ) GenDenomCondStatusPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC )                      GenDenomFidPermissionPtr
)
{
    VAR( Dem_IumprDenomCondStatusType, AUTOMATIC )  genDenCondState;
    VAR( boolean, AUTOMATIC )                       genDenAdddedCondition;
    VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC  )                       genDenCounter;
    VAR( Dem_FiM_FunctionIdType, AUTOMATIC )        demOBDGeneralDenominatorFIdRef;
    VAR( Dem_FiM_FunctionIdType, AUTOMATIC )        fiMFidDummy;
    VAR( Std_ReturnType, AUTOMATIC )                retGetPermission;
    VAR( boolean, AUTOMATIC )                       genDenFidPermission;

    fiMFidDummy                     = Dem_FiMFId_Dummy;
    demOBDGeneralDenominatorFIdRef  = Dem_OBDGeneralDenominatorFIdRef;
    genDenFidPermission             = (boolean)FALSE;

    Dem_IUMPRMng_GetIUMPRDenCondition( DEM_IUMPR_GENERAL_DENOMINATOR, &genDenCondState );
    Dem_IUMPRMng_GetGenDenInformation( &genDenAdddedCondition, &genDenCounter );
    if( genDenAdddedCondition == (boolean)FALSE )
    {
        if( genDenCondState == DEM_IUMPR_DEN_STATUS_REACHED )
        {
            genDenFidPermission     = (boolean)TRUE;
            if( demOBDGeneralDenominatorFIdRef != fiMFidDummy )
            {
                retGetPermission    = Dem_FiM_GetFunctionPermission( demOBDGeneralDenominatorFIdRef, &genDenFidPermission );
                if( retGetPermission != (Std_ReturnType)E_OK )
                {
                    genDenFidPermission = (boolean)FALSE;
                }
            }

            if( genDenFidPermission == (boolean)TRUE )
            {
                if( genDenCounter == DEM_IUMPR_COUNTER_MAXVALUE )
                {
                    genDenCounter = DEM_IUMPR_COUNTER_INITVALUE;
                }
                else
                {
                    genDenCounter = genDenCounter + (Dem_u16_IUMPRCycleCounterType)1U;
                }

                genDenAdddedCondition   = (boolean)TRUE;
                Dem_IUMPRMng_SetGenDenInformation( genDenAdddedCondition, genDenCounter );  /*[UpdRec]IUMPR */

                Dem_IUMPR_NotifyGeneralDenominatorUpdate();
            }
        }
    }
    else
    {
        genDenFidPermission     = (boolean)TRUE;
    }
    *GenDenomCondStatusPtr      = genDenCondState;
    *GenDenomFidPermissionPtr   = genDenFidPermission;

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
/*  v5-6-0         :2024-01-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
