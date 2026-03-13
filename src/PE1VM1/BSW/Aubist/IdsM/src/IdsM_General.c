/* IdsM_General_c_v2-0-3                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name | IdsM/General/CODE                                          */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <IdsM.h>
#include <IdsM_Cbk.h>
#include <SchM_IdsM.h>
#include "../inc/IdsM_Cfg_Fixed.h"
#include "../inc/IdsM_General.h"
#include "../inc/IdsM_Event.h"
#include "../inc/IdsM_Filter.h"
#include "../inc/IdsM_Context.h"
#include "../inc/IdsM_Sink.h"
#include "../inc/IdsM_InterSEv.h"
#include "../inc/IdsM_Std.h"

#if ( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR )
#include <Rte_StbM_Type.h>
#endif  /* IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR */

#include "../usr/IdsM_Connector.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define IDSM_TIMESTAMP_SOURCE_MASK  ((uint64)0x7FFFFFFFFFFFFFFF)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define IDSM_START_SEC_CODE
#include <IdsM_MemMap.h>

#if ( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR )||( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_CUSTOM )
static FUNC(void, IDSM_CODE) IdsM_General_SetTimestamp
(
    P2VAR(IdsM_TimestampType, AUTOMATIC, AUTOMATIC) ptTimestamp,
    P2VAR(IdsM_TimestampType, AUTOMATIC, AUTOMATIC) ptSEvTimestamp,
    P2VAR(boolean, AUTOMATIC, AUTOMATIC) ptGetTimeFlag
);
#endif /* ( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR )||( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_CUSTOM ) */

static FUNC(void, IDSM_CODE) IdsM_General_SetSEv
(
    VAR(IdsM_SecurityEventIdType, AUTOMATIC) udSecurityEventId,
    VAR(IdsM_TimestampType, AUTOMATIC) udTimestamp,
    VAR(uint16, AUTOMATIC) u2Count,
    P2CONST(uint8, AUTOMATIC, IDSM_APPL_CONST) ptContextData,
    VAR(uint16, AUTOMATIC) u2CtxDataSize
);

static FUNC(void, IDSM_CODE) IdsM_General_NotificationError
(
    IdsM_StatusType udIdsMStatus
);

#define IDSM_STOP_SEC_CODE
#include <IdsM_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define IDSM_START_SEC_VAR_CLEARED_WAKEUP
#include <IdsM_MemMap.h>

static VAR(volatile IdsM_StatusType, IDSM_VAR_CLEARED_WAKEUP) IdsM_General_udStatus;

#define IDSM_STOP_SEC_VAR_CLEARED_WAKEUP
#include <IdsM_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define IDSM_START_SEC_CODE
#include <IdsM_MemMap.h>

/****************************************************************************/
/* Function Name | IdsM_Init                                                */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | configPtr : not use                                      */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_Init
(
    P2CONST(IdsM_ConfigType, AUTOMATIC, IDSM_APPL_CONST) configPtr
)
{
    IdsM_StatusType ud_IdsMStatus = IdsM_General_udStatus;
    
    if( ud_IdsMStatus == IDSM_S_UNINIT )
    {
        IdsM_Event_Init();
#if ( IDSM_CFG_USE_CTXDATA == STD_ON )
        IdsM_Context_Init();
#endif /* ( IDSM_CFG_USE_CTXDATA == STD_ON ) */
        IdsM_Filter_Init();
        IdsM_InterSEv_Init();
        IdsM_Sink_Init();

        IdsM_General_udStatus = IDSM_S_INIT;
    }

    return ;
}

/****************************************************************************/
/* Function Name | IdsM_Ab_DeInit                                           */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_Ab_DeInit
(
    void
)
{
    SchM_Enter_IdsM_State();
    IdsM_General_udStatus = IDSM_S_UNINIT;
    SchM_Exit_IdsM_State();

    return ;
}

/****************************************************************************/
/* Function Name | IdsM_GetVersionInfo                                      */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | versionInfo                                              */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_GetVersionInfo
(
    P2VAR(Std_VersionInfoType, AUTOMATIC, IDSM_APPL_DATA) versionInfo
)
{
    boolean b_versionInfoApi = IdsM_Cfg_bVersionInfoApi;

    if( b_versionInfoApi == (boolean)TRUE )
    {
        if( versionInfo != NULL_PTR )
        {
            versionInfo->vendorID         = (uint16)IDSM_VENDOR_ID;
            versionInfo->moduleID         = (uint16)IDSM_MODULE_ID;
            versionInfo->sw_major_version = (uint8)IDSM_SW_MAJOR_VERSION;
            versionInfo->sw_minor_version = (uint8)IDSM_SW_MINOR_VERSION;
            versionInfo->sw_patch_version = (uint8)IDSM_SW_PATCH_VERSION;
        }
    }

    return ;
}

/****************************************************************************/
/* Function Name | IdsM_MainFunction                                        */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_MainFunction
(
    void
)
{
    uint16 u2_EveBuffNum;
    uint16 u2_EveBuffIndex;
    IdsMEventBuffType st_EveBuffData;
#if ( IDSM_CFG_USE_INTSEV_EVEBUFFUL == STD_ON )
    IdsMEventBuffType st_EveBuffFullData;
#endif /* ( IDSM_CFG_USE_INTSEV_EVEBUFFUL == STD_ON ) */
#if ( IDSM_CFG_USE_INTSEV_CTXBUFFUL == STD_ON )
    IdsMEventBuffType st_CtxBuffFullData;
#endif /* ( IDSM_CFG_USE_INTSEV_CTXBUFFUL == STD_ON ) */
#if ( IDSM_CFG_USE_INTSEV_TRAFFICLMIT == STD_ON )
    IdsMEventBuffType st_TrafcLmtData;
#endif /* ( IDSM_CFG_USE_INTSEV_TRAFFICLMIT == STD_ON ) */
    uint16 u2_AggreFilBuffIndex;
#if ( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR )||( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_CUSTOM )
    IdsM_TimestampType ud_Timestamp = IDSM_INVALID_TIMESTAMP;
    boolean b_GetTimeFlag = FALSE;
#endif /* ( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR )||( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_CUSTOM ) */
#if ( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON )
    uint16 u2_AggreTmpRef;
    IdsMAggreFilTmpType st_AggreTmpData;
    Std_ReturnType ud_Ret;
#endif /* ( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON ) */
#if ( IDSM_CFG_USE_FIL_THRESHOLD == STD_ON )
    uint16 u2_ThresholdTmpRef;
#endif /* ( IDSM_CFG_USE_FIL_THRESHOLD == STD_ON ) */
    IdsM_StatusType ud_IdsMStatus;

    SchM_Enter_IdsM_State();
    ud_IdsMStatus = IdsM_General_udStatus;

#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
    if( ( ud_IdsMStatus != IDSM_S_UNINIT ) &&
        ( ud_IdsMStatus != IDSM_S_INIT ) )
    {
        IdsM_General_udStatus = IDSM_S_RAMERROR;
        ud_IdsMStatus         = IDSM_S_RAMERROR;
    }
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */
    SchM_Exit_IdsM_State();

    IdsM_General_NotificationError(ud_IdsMStatus);

    if( ud_IdsMStatus == IDSM_S_INIT )
    {
        IdsM_Filter_UpdateCount();

        SchM_Enter_IdsM_General();

#if ( IDSM_CFG_USE_FIL_BLKSTATE == STD_ON )
        IdsM_Filter_BlockStateCpy();
#endif /* ( IDSM_CFG_USE_FIL_BLKSTATE == STD_ON ) */


#if ( IDSM_CFG_USE_INTSEV_EVEBUFFUL == STD_ON )
        IdsM_Std_EventBuffCopy(&st_EveBuffFullData, &IdsM_Cfg_InterBuff_EveBuffFull);
        IdsM_InterSEv_ClearBuff( &IdsM_Cfg_InterBuff_EveBuffFull );
#endif /* ( IDSM_CFG_USE_INTSEV_EVEBUFFUL == STD_ON ) */

#if ( IDSM_CFG_USE_INTSEV_CTXBUFFUL == STD_ON )
        IdsM_Std_EventBuffCopy(&st_CtxBuffFullData, &IdsM_Cfg_InterBuff_CtxBuffFull);
        IdsM_InterSEv_ClearBuff( &IdsM_Cfg_InterBuff_CtxBuffFull );
#endif /* ( IDSM_CFG_USE_INTSEV_CTXBUFFUL == STD_ON ) */

#if ( IDSM_CFG_USE_INTSEV_TRAFFICLMIT == STD_ON )
        IdsM_Std_EventBuffCopy(&st_TrafcLmtData, &IdsM_Cfg_InterBuff_TrafficLimit);
        IdsM_InterSEv_ClearBuff( &IdsM_Cfg_InterBuff_TrafficLimit );
#endif /* ( IDSM_CFG_USE_INTSEV_TRAFFICLMIT == STD_ON ) */

        u2_EveBuffNum = IdsM_Event_GetSEvNum();

        SchM_Exit_IdsM_General();

#if ( IDSM_CFG_USE_INTSEV_EVEBUFFUL == STD_ON )
        if( st_EveBuffFullData.u2Count != (uint16)0U )
        {
#if ( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR )||( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_CUSTOM )
            IdsM_General_SetTimestamp( &ud_Timestamp,
                                       &st_EveBuffFullData.udTimestamp,
                                       &b_GetTimeFlag );
#endif /* ( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR )||( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_CUSTOM ) */
            IdsM_Filter_MainProcess( st_EveBuffFullData.udSEvId,
                                     &st_EveBuffFullData,
                                     IDSM_START_BLOCKSTATE );
        }
#endif /* ( IDSM_CFG_USE_INTSEV_EVEBUFFUL == STD_ON ) */

#if ( IDSM_CFG_USE_INTSEV_CTXBUFFUL == STD_ON )
        if( st_CtxBuffFullData.u2Count != (uint16)0U )
        {
#if ( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR )||( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_CUSTOM )
            IdsM_General_SetTimestamp( &ud_Timestamp,
                                       &st_CtxBuffFullData.udTimestamp,
                                       &b_GetTimeFlag );
#endif /* ( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR )||( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_CUSTOM ) */
            IdsM_Filter_MainProcess( st_CtxBuffFullData.udSEvId,
                                     &st_CtxBuffFullData,
                                     IDSM_START_BLOCKSTATE );
        }
#endif /* ( IDSM_CFG_USE_INTSEV_CTXBUFFUL == STD_ON ) */

#if ( IDSM_CFG_USE_INTSEV_TRAFFICLMIT == STD_ON )
        if( st_TrafcLmtData.u2Count != (uint16)0U )
        {
#if ( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR )||( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_CUSTOM )
            IdsM_General_SetTimestamp( &ud_Timestamp,
                                       &st_TrafcLmtData.udTimestamp,
                                       &b_GetTimeFlag );
#endif /* ( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR )||( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_CUSTOM ) */
            IdsM_Filter_MainProcess( st_TrafcLmtData.udSEvId,
                                     &st_TrafcLmtData,
                                     IDSM_START_BLOCKSTATE );
        }
#endif /* ( IDSM_CFG_USE_INTSEV_TRAFFICLMIT == STD_ON ) */


        for( u2_EveBuffIndex = 0U; u2_EveBuffIndex < u2_EveBuffNum; u2_EveBuffIndex++ )
        {
            IdsM_Event_GetSEvInfo( &st_EveBuffData );

#if ( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR )||( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_CUSTOM )
            IdsM_General_SetTimestamp( &ud_Timestamp,
                                       &st_EveBuffData.udTimestamp,
                                       &b_GetTimeFlag );
#endif /* ( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR )||( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_CUSTOM ) */

            IdsM_Filter_MainProcess( st_EveBuffData.udSEvId,
                                     &st_EveBuffData,
                                     IDSM_START_BLOCKSTATE );
        }
        SchM_Enter_IdsM_General();
        IdsM_Event_ClearBuff( u2_EveBuffNum );
        SchM_Exit_IdsM_General();

        for( u2_AggreFilBuffIndex = 0U; u2_AggreFilBuffIndex < IdsM_Cfg_EventAcss.u2ConfigNum; u2_AggreFilBuffIndex++ )
        {
#if ( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON )
            u2_AggreTmpRef = IdsM_Cfg_EventAcss.ptConfig[u2_AggreFilBuffIndex].u2AggreFilDataRef;

            if( u2_AggreTmpRef != IDSM_INVALID_INDEX )
            {
                ud_Ret = IdsM_Filter_AggreCheckPeriod( u2_AggreFilBuffIndex );

                if( ( ud_Ret == (Std_ReturnType)E_OK ) &&
                    ( IdsM_Cfg_AggreFilTmpAcss.ptTmp[u2_AggreTmpRef].u2Count != (uint16)0U ) )
                {
                    IdsM_Filter_GetAggreTmpData( u2_AggreTmpRef, &st_AggreTmpData );
                    st_EveBuffData.udSEvId = u2_AggreFilBuffIndex;
                    st_EveBuffData.u2Count = st_AggreTmpData.u2Count;
#if ( IDSM_CFG_USE_TIMESTAMP != IDSM_TS_OPT_NONE )
                    st_EveBuffData.udTimestamp = st_AggreTmpData.udTimestamp;
#endif /* ( IDSM_CFG_USE_TIMESTAMP != IDSM_TS_OPT_NONE ) */
#if ( IDSM_CFG_USE_CTXDATA == STD_ON )
                    st_EveBuffData.u2CtxDataSize = st_AggreTmpData.u2CtxDataSize;
                    st_EveBuffData.u2Dummy = 0U;
                    st_EveBuffData.u2TableIndex = st_AggreTmpData.u2TableIndex;
                    st_EveBuffData.u2RecordIndex = st_AggreTmpData.u2RecordIndex;
#endif /* ( IDSM_CFG_USE_CTXDATA == STD_ON ) */

                    IdsM_Filter_MainProcess( st_EveBuffData.udSEvId,
                                             &st_EveBuffData,
                                             IDSM_START_THRESHOLD );

                    IdsM_Filter_AggreClearBuff( u2_AggreFilBuffIndex );
                }
            }
#endif /* ( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON ) */
#if ( IDSM_CFG_USE_FIL_THRESHOLD == STD_ON )
            u2_ThresholdTmpRef = IdsM_Cfg_EventAcss.ptConfig[u2_AggreFilBuffIndex].u2ThreFilDataRef;

            if( u2_ThresholdTmpRef != IDSM_INVALID_INDEX )
            {
                IdsM_Filter_ThresholdClearBuff( u2_AggreFilBuffIndex );
            }
#endif /* ( IDSM_CFG_USE_FIL_THRESHOLD == STD_ON ) */
        }
#if ( IDSM_CFG_USE_FIL_RATELMT == STD_ON )
        IdsM_Filter_EventRateClearNum();
#endif /* ( IDSM_CFG_USE_FIL_RATELMT == STD_ON ) */
#if ( IDSM_CFG_USE_FIL_TRAFFICLMT == STD_ON )
        IdsM_Filter_TrafficClearBytes();
#endif /* ( IDSM_CFG_USE_FIL_TRAFFICLMT == STD_ON ) */
    }

    return;
}

/****************************************************************************/
/* Function Name | IdsM_SetSecurityEventWithTimestampCountContextData       */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | securityEventId                                          */
/*               | timestamp                                                */
/*               | count                                                    */
/*               | contextData                                              */
/*               | contextDataSize                                          */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_SetSecurityEventWithTimestampCountContextData
(
    VAR(IdsM_SecurityEventIdType, AUTOMATIC) securityEventId,
    VAR(IdsM_TimestampType, AUTOMATIC) timestamp,
    VAR(uint16, AUTOMATIC) count,
    P2CONST(uint8, AUTOMATIC, IDSM_APPL_CONST) contextData,
    VAR(uint16, AUTOMATIC) contextDataSize
)
{
    IdsM_SecurityEventIdType ud_InternalId = (IdsM_SecurityEventIdType)IdsM_Cfg_EventAcss.u2ConfigNum;
    uint16 u2_CtxDataBuffMaxSize = IdsM_Cfg_u2CtxDataBuffMaxSize;
    IdsM_TimestampType ud_Timestamp = timestamp;
    CONST(IdsM_ParamErrCalloutType, AUTOMATIC) pt_ParamErrCallout = IdsM_Cfg_ptParamErrCalloutFunc;
    IdsM_Ab_ErrorStatusType ud_ParamError = IDSM_AB_E_NONE;
    IdsM_StatusType ud_IdsMStatus;

    SchM_Enter_IdsM_State();
    ud_IdsMStatus = IdsM_General_udStatus;
    SchM_Exit_IdsM_State();

    if( ud_IdsMStatus == IDSM_S_INIT )
    {
        if( ( securityEventId >= ud_InternalId )
         || ( count == (uint16)0U ) )
        {
            ud_ParamError = IDSM_AB_E_PARAM_INVALID;
        }
        else if( ( contextData == NULL_PTR )
              && ( contextDataSize != (uint16)0U ) )
        {
            ud_ParamError = IDSM_AB_E_PARAM_POINTER;
        }
        else if( contextDataSize > u2_CtxDataBuffMaxSize )
        {
            ud_ParamError = IDSM_AB_E_PARAM_LENGTH;
        }
        else
        {
            ud_Timestamp &= IDSM_TIMESTAMP_SOURCE_MASK;

            IdsM_General_SetSEv( securityEventId,
                                 ud_Timestamp,
                                 count,
                                 contextData,
                                 contextDataSize );
        }

        if( ud_ParamError != IDSM_AB_E_NONE )
        {
            if( pt_ParamErrCallout != NULL_PTR )
            {
                pt_ParamErrCallout( securityEventId, ud_ParamError );
            }
        }
    }
    return ;
}

/****************************************************************************/
/* Function Name | IdsM_SetSecurityEventWithTimestampCount                  */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | securityEventId                                          */
/*               | timestamp                                                */
/*               | count                                                    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_SetSecurityEventWithTimestampCount
(
    VAR(IdsM_SecurityEventIdType, AUTOMATIC) securityEventId,
    VAR(IdsM_TimestampType, AUTOMATIC) timestamp,
    VAR(uint16, AUTOMATIC) count
)
{
    IdsM_SecurityEventIdType ud_InternalId = (IdsM_SecurityEventIdType)IdsM_Cfg_EventAcss.u2ConfigNum;
    IdsM_TimestampType ud_Timestamp = timestamp;
    CONST(IdsM_ParamErrCalloutType, AUTOMATIC) pt_ParamErrCallout = IdsM_Cfg_ptParamErrCalloutFunc;
    IdsM_StatusType ud_IdsMStatus;

    SchM_Enter_IdsM_State();
    ud_IdsMStatus = IdsM_General_udStatus;
    SchM_Exit_IdsM_State();

    if( ud_IdsMStatus == IDSM_S_INIT )
    {
        if( ( securityEventId >= ud_InternalId )
         || ( count == (uint16)0U ) )
        {
            if( pt_ParamErrCallout != NULL_PTR )
            {
                pt_ParamErrCallout( securityEventId, IDSM_AB_E_PARAM_INVALID );
            }
        }
        else
        {
            ud_Timestamp &= IDSM_TIMESTAMP_SOURCE_MASK;

            IdsM_General_SetSEv( securityEventId,
                                 ud_Timestamp,
                                 count,
                                 NULL_PTR,
                                 0U );
        }
    }
    return ;
}

/****************************************************************************/
/* Function Name | IdsM_SetSecurityEvent                                    */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | securityEventId                                          */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_SetSecurityEvent
(
    VAR(IdsM_SecurityEventIdType, AUTOMATIC) securityEventId
)
{
    IdsM_SecurityEventIdType ud_InternalId = (IdsM_SecurityEventIdType)IdsM_Cfg_EventAcss.u2ConfigNum;
    CONST(IdsM_ParamErrCalloutType, AUTOMATIC) pt_ParamErrCallout = IdsM_Cfg_ptParamErrCalloutFunc;
    IdsM_StatusType ud_IdsMStatus;

    SchM_Enter_IdsM_State();
    ud_IdsMStatus = IdsM_General_udStatus;
    SchM_Exit_IdsM_State();

    if( ud_IdsMStatus == IDSM_S_INIT )
    {
        if( securityEventId >= ud_InternalId )
        {
            if( pt_ParamErrCallout != NULL_PTR )
            {
                pt_ParamErrCallout( securityEventId, IDSM_AB_E_PARAM_INVALID );
            }
        }
        else
        {
            IdsM_General_SetSEv( securityEventId,
                                 IDSM_INVALID_TIMESTAMP,
                                 IDSM_NO_COUNT,
                                 NULL_PTR,
                                 0U );
        }
    }
    return ;
}

/****************************************************************************/
/* Function Name | IdsM_SetSecurityEventWithContextData                     */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | securityEventId                                          */
/*               | contextData                                              */
/*               | contextDataSize                                          */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_SetSecurityEventWithContextData
(
    VAR(IdsM_SecurityEventIdType, AUTOMATIC) securityEventId,
    P2CONST(uint8, AUTOMATIC, IDSM_APPL_CONST) contextData,
    VAR(uint16, AUTOMATIC) contextDataSize
)
{
    IdsM_SecurityEventIdType ud_InternalId = (IdsM_SecurityEventIdType)IdsM_Cfg_EventAcss.u2ConfigNum;
    uint16 u2_CtxDataBuffMaxSize = IdsM_Cfg_u2CtxDataBuffMaxSize;
    CONST(IdsM_ParamErrCalloutType, AUTOMATIC) pt_ParamErrCallout = IdsM_Cfg_ptParamErrCalloutFunc;
    IdsM_Ab_ErrorStatusType ud_ParamError = IDSM_AB_E_NONE;
    IdsM_StatusType ud_IdsMStatus;

    SchM_Enter_IdsM_State();
    ud_IdsMStatus = IdsM_General_udStatus;
    SchM_Exit_IdsM_State();

    if( ud_IdsMStatus == IDSM_S_INIT )
    {
        if( securityEventId >= ud_InternalId )
        {
            ud_ParamError = IDSM_AB_E_PARAM_INVALID;
        }
        else if( ( contextData == NULL_PTR )
              && ( contextDataSize != (uint16)0U ) )
        {
            ud_ParamError = IDSM_AB_E_PARAM_POINTER;
        }
        else if( contextDataSize > u2_CtxDataBuffMaxSize )
        {
            ud_ParamError = IDSM_AB_E_PARAM_LENGTH;
        }
        else
        {
            IdsM_General_SetSEv( securityEventId,
                                 IDSM_INVALID_TIMESTAMP,
                                 IDSM_NO_COUNT,
                                 contextData,
                                 contextDataSize );
        }

        if( ud_ParamError != IDSM_AB_E_NONE )
        {
            if( pt_ParamErrCallout != NULL_PTR )
            {
                pt_ParamErrCallout( securityEventId, ud_ParamError );
            }
        }
    }
    return ;
}

/****************************************************************************/
/* Function Name | IdsM_SetSecurityEventWithCount                           */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | securityEventId                                          */
/*               | count                                                    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_SetSecurityEventWithCount
(
    VAR(IdsM_SecurityEventIdType, AUTOMATIC) securityEventId,
    VAR(uint16, AUTOMATIC) count
)
{
    IdsM_SecurityEventIdType ud_InternalId = (IdsM_SecurityEventIdType)IdsM_Cfg_EventAcss.u2ConfigNum;
    CONST(IdsM_ParamErrCalloutType, AUTOMATIC) pt_ParamErrCallout = IdsM_Cfg_ptParamErrCalloutFunc;
    IdsM_StatusType ud_IdsMStatus;

    SchM_Enter_IdsM_State();
    ud_IdsMStatus = IdsM_General_udStatus;
    SchM_Exit_IdsM_State();

    if( ud_IdsMStatus == IDSM_S_INIT )
    {
        if( ( securityEventId >= ud_InternalId )
         || ( count == (uint16)0U ) )
        {
            if( pt_ParamErrCallout != NULL_PTR )
            {
                pt_ParamErrCallout( securityEventId, IDSM_AB_E_PARAM_INVALID );
            }
        }
        else
        {
            IdsM_General_SetSEv( securityEventId,
                                 IDSM_INVALID_TIMESTAMP,
                                 count,
                                 NULL_PTR,
                                 0U );
        }
    }
    return ;
}

/****************************************************************************/
/* Function Name | IdsM_SetSecurityEventWithCountContextData                */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | securityEventId                                          */
/*               | count                                                    */
/*               | contextData                                              */
/*               | contextDataSize                                          */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_SetSecurityEventWithCountContextData
(
    VAR(IdsM_SecurityEventIdType, AUTOMATIC) securityEventId,
    VAR(uint16, AUTOMATIC) count,
    P2CONST(uint8, AUTOMATIC, IDSM_APPL_CONST) contextData,
    VAR(uint16, AUTOMATIC) contextDataSize
)
{
    IdsM_SecurityEventIdType ud_InternalId = (IdsM_SecurityEventIdType)IdsM_Cfg_EventAcss.u2ConfigNum;
    uint16 u2_CtxDataBuffMaxSize = IdsM_Cfg_u2CtxDataBuffMaxSize;
    CONST(IdsM_ParamErrCalloutType, AUTOMATIC) pt_ParamErrCallout = IdsM_Cfg_ptParamErrCalloutFunc;
    IdsM_Ab_ErrorStatusType ud_ParamError = IDSM_AB_E_NONE;
    IdsM_StatusType ud_IdsMStatus;

    SchM_Enter_IdsM_State();
    ud_IdsMStatus = IdsM_General_udStatus;
    SchM_Exit_IdsM_State();

    if( ud_IdsMStatus == IDSM_S_INIT )
    {
        if( ( securityEventId >= ud_InternalId )
         || ( count == (uint16)0U ) )
        {
            ud_ParamError = IDSM_AB_E_PARAM_INVALID;
        }
        else if( ( contextData == NULL_PTR )
              && ( contextDataSize != (uint16)0U ) )
        {
            ud_ParamError = IDSM_AB_E_PARAM_POINTER;
        }
        else if( contextDataSize > u2_CtxDataBuffMaxSize )
        {
            ud_ParamError = IDSM_AB_E_PARAM_LENGTH;
        }
        else
        {
            IdsM_General_SetSEv( securityEventId,
                                 IDSM_INVALID_TIMESTAMP,
                                 count,
                                 contextData,
                                 contextDataSize );
        }

        if( ud_ParamError != IDSM_AB_E_NONE )
        {
            if( pt_ParamErrCallout != NULL_PTR )
            {
                pt_ParamErrCallout( securityEventId, ud_ParamError );
            }
        }
    }
    return ;
}

/****************************************************************************/
/* Function Name | IdsM_BswM_StateChanged                                   */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | state                                                    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_BswM_StateChanged
(
    VAR(IdsM_Filters_BlockStateType, AUTOMATIC) state
)
{
    IdsM_StatusType ud_IdsMStatus;

    SchM_Enter_IdsM_State();
    ud_IdsMStatus = IdsM_General_udStatus;
    SchM_Exit_IdsM_State();

    if( ud_IdsMStatus == IDSM_S_INIT )
    {
#if ( IDSM_CFG_USE_FIL_BLKSTATE == STD_ON )
        SchM_Enter_IdsM_General();
        IdsM_Filter_SetBlockState( state );
        SchM_Exit_IdsM_General();
#endif /* ( IDSM_CFG_USE_FIL_BLKSTATE == STD_ON ) */
    }
    return ;
}

/****************************************************************************/
/* Function Name | IdsM_TxConfirmation                                      */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | TxPduId                                                  */
/*               | result                                                   */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_TxConfirmation
(
    VAR(PduIdType, AUTOMATIC) TxPduId,
    VAR(Std_ReturnType, AUTOMATIC) result
)
{
#if (IDSM_CFG_USE_IDSR == STD_ON)

    IdsM_StatusType ud_IdsMStatus;

    SchM_Enter_IdsM_State();
    ud_IdsMStatus = IdsM_General_udStatus;
    SchM_Exit_IdsM_State();
    if( ud_IdsMStatus == IDSM_S_INIT )
    {
        IdsM_Sink_IdsRTxConfirmation( TxPduId, result );
    }
#endif  /* IDSM_CFG_USE_IDSR == STD_ON */

    return ;
}

#if (IDSM_CFG_USE_IDSR == STD_ON)
/****************************************************************************/
/* Function Name | IdsM_Ab_MainFunctionTx                                   */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_Ab_MainFunctionTx
(
    void
)
{
    IdsM_StatusType ud_IdsMStatus;
    Std_ReturnType ud_ConfResult;

#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
    IdsM_Sink_DetectRamError();
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */

    SchM_Enter_IdsM_State();
    ud_IdsMStatus = IdsM_General_udStatus;
    SchM_Exit_IdsM_State();

    if( ud_IdsMStatus == IDSM_S_INIT )
    {
        ud_ConfResult = IdsM_Sink_IdsRTxConfirmationChk();
        
        if( ud_ConfResult == (Std_ReturnType)E_OK )
        {
            IdsM_Sink_IdsRTransmit();
        }
        
        IdsM_Sink_IdsRQSEvErrNotify();
    }

    return ;
}
#endif  /* IDSM_CFG_USE_IDSR == STD_ON */

#if (IDSM_CFG_USE_DEM == STD_ON)
/****************************************************************************/
/* Function Name | IdsM_Ab_MainFunctionDem                                  */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_Ab_MainFunctionDem
(
    void
)
{
    IdsM_StatusType ud_IdsMStatus;

    SchM_Enter_IdsM_State();
    ud_IdsMStatus = IdsM_General_udStatus;
    SchM_Exit_IdsM_State();

    if( ud_IdsMStatus == IDSM_S_INIT )
    {
        IdsM_Sink_DemTransmit();
        IdsM_Sink_DemQSEvErrNotify();
    }

    return ;
}

/****************************************************************************/
/* Function Name | IdsM_Ab_DemReadCallback                                  */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | ptBuffer                                                 */
/*               | udMonitorData0                                           */
/* Return Value  | Std_ReturnType                                           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, IDSM_CODE) IdsM_Ab_DemReadCallback
(
    P2VAR(uint8, AUTOMATIC, IDSM_APPL_DATA) ptBuffer,
    VAR(Dem_MonitorDataType, AUTOMATIC) udMonitorData0
)
{
    IdsM_StatusType ud_IdsMStatus;
    Std_ReturnType ud_StdRet = E_NOT_OK;

    SchM_Enter_IdsM_State();
    ud_IdsMStatus = IdsM_General_udStatus;
    SchM_Exit_IdsM_State();

    if( ud_IdsMStatus == IDSM_S_INIT )
    {
        ud_StdRet = IdsM_Sink_DemReadCallback( ptBuffer );
    }

    return ud_StdRet;
}
#endif  /* IDSM_CFG_USE_DEM == STD_ON */

#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
/****************************************************************************/
/* Function Name | IdsM_General_SetRamError                                 */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_General_SetRamError
(
    void
)
{
    IdsM_StatusType ud_IdsMStatus;

    SchM_Enter_IdsM_State();
    ud_IdsMStatus = IdsM_General_udStatus;
    if( ud_IdsMStatus == IDSM_S_INIT )
    {
        IdsM_General_udStatus = IDSM_S_RAMERROR;
    }
    SchM_Exit_IdsM_State();

    return ;
}
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#if ( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR )||( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_CUSTOM )
/****************************************************************************/
/* Function Name | IdsM_General_SetTimestamp                                */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | ptTimestamp :                                            */
/*               | ptSEvTimestamp :                                         */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, IDSM_CODE) IdsM_General_SetTimestamp
(
    P2VAR(IdsM_TimestampType, AUTOMATIC, AUTOMATIC) ptTimestamp,
    P2VAR(IdsM_TimestampType, AUTOMATIC, AUTOMATIC) ptSEvTimestamp,
    P2VAR(boolean, AUTOMATIC, AUTOMATIC) ptGetTimeFlag
)
{
    Std_ReturnType ud_GetTimeRet;
#if ( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR )
    StbM_TimeStampType ud_StbMTimestamp;
#endif /* ( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR ) */


    if( *ptSEvTimestamp == IDSM_INVALID_TIMESTAMP )
    {
        if( *ptGetTimeFlag == (boolean)FALSE )
        {

#if ( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR )

            ud_GetTimeRet = IdsM_Connector_StbMGetCurrentTime( &ud_StbMTimestamp );

#else
            ud_GetTimeRet = IdsM_Connector_GetCurrentTime( ptTimestamp );
#endif /* ( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR ) */
            *ptGetTimeFlag = TRUE;

            if( ud_GetTimeRet == (Std_ReturnType)E_OK)
            {
#if ( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR )
                *ptTimestamp = ( ( ( IdsM_TimestampType )ud_StbMTimestamp.nanoseconds ) << IDSM_BIT_SHIFT_32 ) |
                                    ( ( IdsM_TimestampType )ud_StbMTimestamp.seconds );
#endif /* ( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR ) */

                *ptTimestamp &= IDSM_TIMESTAMP_SOURCE_MASK;
            }
            else
            {
                *ptTimestamp = IDSM_INVALID_TIMESTAMP;
            }
        }
        *ptSEvTimestamp = *ptTimestamp;
    }

    return ;
}

#endif /* ( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR )||( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_CUSTOM ) */

/****************************************************************************/
/* Function Name | IdsM_General_SetSEv                                      */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | udSecurityEventId :                                      */
/*               | udTimestamp :                                            */
/*               | u2Count :                                                */
/*               | ptContextData :                                          */
/*               | u2CtxDataSize :                                          */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, IDSM_CODE) IdsM_General_SetSEv
(
    VAR(IdsM_SecurityEventIdType, AUTOMATIC) udSecurityEventId,
    VAR(IdsM_TimestampType, AUTOMATIC) udTimestamp,
    VAR(uint16, AUTOMATIC) u2Count,
    P2CONST(uint8, AUTOMATIC, IDSM_APPL_CONST) ptContextData,
    VAR(uint16, AUTOMATIC) u2CtxDataSize
)
{
    IdsMEventBuffType st_Data;
    IdsM_Filters_ReportingModeType ud_ReportRet;
    Std_ReturnType ud_EventRet;
#if ( ( IDSM_CFG_USE_CTXDATA == STD_ON ) && (IDSM_CFG_USE_INTSEV_CTXBUFFUL == STD_ON) )
    IdsM_SecurityEventIdType ud_CtxFullId = IdsM_Cfg_udCtxFullId;
#endif /* ( ( IDSM_CFG_USE_CTXDATA == STD_ON ) && (IDSM_CFG_USE_INTSEV_CTXBUFFUL == STD_ON) ) */
#if ( IDSM_CFG_USE_INTSEV_EVEBUFFUL == STD_ON )
    IdsM_SecurityEventIdType ud_EveFullId = IdsM_Cfg_udEveFullId;
#endif /* ( IDSM_CFG_USE_INTSEV_EVEBUFFUL == STD_ON ) */
#if ( IDSM_CFG_USE_CTXDATA == STD_ON )
    Std_ReturnType ud_ContextRet = (Std_ReturnType)E_NOT_OK;
#endif /* ( IDSM_CFG_USE_CTXDATA == STD_ON ) */

    st_Data.udSEvId = udSecurityEventId;
    st_Data.u2Count = u2Count;
#if ( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR )||( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_CUSTOM )
    st_Data.udTimestamp = udTimestamp;
#endif /* ( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR )||( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_CUSTOM ) */
#if ( IDSM_CFG_USE_CTXDATA == STD_ON )
    st_Data.u2CtxDataSize = u2CtxDataSize;
    st_Data.u2Dummy = 0U;
    st_Data.u2TableIndex  = IDSM_INVALID_INDEX;
    st_Data.u2RecordIndex = IDSM_INVALID_INDEX;
#endif /* ( IDSM_CFG_USE_CTXDATA == STD_ON ) */

    ud_ReportRet = IdsM_Filter_ReportingMode( udSecurityEventId );

    if( ud_ReportRet != IDSM_REPORTING_MODE_OFF )
    {
#if ( IDSM_CFG_USE_CTXDATA == STD_ON )
        if( ( ud_ReportRet == IDSM_REPORTING_MODE_BRIEF ) ||
            ( ud_ReportRet == IDSM_REPORTING_MODE_BRIEF_BYPASSING_FILTERS ) )
        {
            st_Data.u2CtxDataSize = 0U;
        }

        if( st_Data.u2CtxDataSize > (uint16)0U )
        {
            ud_ContextRet = IdsM_Context_SetBuff( ptContextData,
                                                  st_Data.u2CtxDataSize,
                                                  &st_Data.u2TableIndex,
                                                  &st_Data.u2RecordIndex );

            if( ud_ContextRet != (Std_ReturnType)E_OK )
            {
                st_Data.u2CtxDataSize = 0U;
#if ( IDSM_CFG_USE_INTSEV_CTXBUFFUL == STD_ON )
                SchM_Enter_IdsM_General();
                IdsM_InterSEv_SetBuff( ud_CtxFullId, &IdsM_Cfg_InterBuff_CtxBuffFull );
                SchM_Exit_IdsM_General();
#endif /* ( IDSM_CFG_USE_INTSEV_CTXBUFFUL == STD_ON ) */
            }
        }
#endif /* ( IDSM_CFG_USE_CTXDATA == STD_ON ) */

        SchM_Enter_IdsM_General();
        ud_EventRet = IdsM_Event_SetBuff( &st_Data );

        if( ud_EventRet != (Std_ReturnType)E_OK )
        {
#if ( IDSM_CFG_USE_CTXDATA == STD_ON )
            if( ud_ContextRet == (Std_ReturnType)E_OK )
            {
                IdsM_Context_ClearBuff( st_Data.u2TableIndex, st_Data.u2RecordIndex );
            }
#endif /* ( IDSM_CFG_USE_CTXDATA == STD_ON ) */
#if (  IDSM_CFG_USE_INTSEV_EVEBUFFUL == STD_ON )
            IdsM_InterSEv_SetBuff( ud_EveFullId, &IdsM_Cfg_InterBuff_EveBuffFull );
#endif /* (  IDSM_CFG_USE_INTSEV_EVEBUFFUL == STD_ON ) */
        }
        SchM_Exit_IdsM_General();
    }

    return ;
}

/****************************************************************************/
/* Function Name | IdsM_General_NotificationError                           */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | udIdsMStatus                                             */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, IDSM_CODE) IdsM_General_NotificationError
(
    IdsM_StatusType udIdsMStatus
)
{
    IdsM_Ab_ErrorStatusType ud_errorStatus;
    CONST(IdsM_RamErrCalloutType, AUTOMATIC) pt_RamErrCallout = IdsM_Cfg_ptRamErrCalloutFunc;
 
    if( udIdsMStatus == IDSM_S_UNINIT )
    {
        ud_errorStatus = IDSM_AB_E_NOT_INITIALIZED;
    }
#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
    else if( udIdsMStatus == IDSM_S_RAMERROR )
    {
        ud_errorStatus = IDSM_AB_E_RAM_CHECK_FAIL;
    }
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */
    else
    {
        ud_errorStatus = IDSM_AB_E_NONE;
    }

    if( ud_errorStatus != IDSM_AB_E_NONE )
    {
        if( pt_RamErrCallout != NULL_PTR )
        {
            pt_RamErrCallout( ud_errorStatus );
        }
    }

    return;
}

#define IDSM_STOP_SEC_CODE
#include <IdsM_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version    :Date                                                        */
/*  v2-0-0     :2022/11/30                                                  */
/*  v2-0-1     :2023/01/23                                                  */
/*  v2-0-2     :2023/02/24                                                  */
/*  v2-0-3     :2023/04/10                                                  */
/****************************************************************************/

/**** End of File ***********************************************************/
