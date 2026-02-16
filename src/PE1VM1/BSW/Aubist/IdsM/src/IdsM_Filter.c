/* IdsM_Filter_c_v2-0-2                                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name | IdsM/Filter/CODE                                           */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <IdsM.h>
#include <SchM_IdsM.h>
#include "../inc/IdsM_Cfg_Fixed.h"
#include "../inc/IdsM_General.h"
#include "../inc/IdsM_Filter.h"
#include "../inc/IdsM_InterSEv.h"
#include "../inc/IdsM_Sink.h"
#include "../inc/IdsM_Context.h"
#include "../inc/IdsM_Std.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#if (( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON ) || ( IDSM_CFG_USE_FIL_THRESHOLD == STD_ON ) || ( IDSM_CFG_USE_FIL_RATELMT == STD_ON ) || ( IDSM_CFG_USE_FIL_TRAFFICLMT == STD_ON ))
#define IDSM_INTERVAL_END   ((uint32)0UL)
#endif /* (( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON ) || ( IDSM_CFG_USE_FIL_THRESHOLD == STD_ON ) || ( IDSM_CFG_USE_FIL_RATELMT == STD_ON ) || ( IDSM_CFG_USE_FIL_TRAFFICLMT == STD_ON )) */
#if ( IDSM_CFG_USE_FIL_NTH == STD_ON )
#define IDSM_NTH_INITIALIZE ((uint16)0x01U)
#endif /* ( IDSM_CFG_USE_FIL_NTH == STD_ON ) */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#if (( IDSM_CFG_USE_FIL_RATELMT == STD_ON ) || ( IDSM_CFG_USE_FIL_TRAFFICLMT == STD_ON ))
#if (( IDSM_CFG_USE_INTSEV_EVEBUFFUL == STD_ON ) || ( IDSM_CFG_USE_INTSEV_CTXBUFFUL == STD_ON ) || ( IDSM_CFG_USE_INTSEV_TRAFFICLMIT == STD_ON ))
static FUNC(boolean, IDSM_CODE) IdsM_Filter_JudgeIntSEv
(
    VAR(uint16, AUTOMATIC) u2Index
);
#endif /* (( IDSM_CFG_USE_INTSEV_EVEBUFFUL == STD_ON ) || ( IDSM_CFG_USE_INTSEV_CTXBUFFUL == STD_ON ) || ( IDSM_CFG_USE_INTSEV_TRAFFICLMIT == STD_ON )) */
#endif /* (( IDSM_CFG_USE_FIL_RATELMT == STD_ON ) || ( IDSM_CFG_USE_FIL_TRAFFICLMT == STD_ON )) */
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

#define IDSM_START_SEC_VAR_NO_INIT
#include <IdsM_MemMap.h>

#if ( IDSM_CFG_USE_FIL_BLKSTATE == STD_ON )
static VAR(volatile IdsM_Filters_BlockStateType, IDSM_VAR_NO_INIT) IdsM_Filter_udBlockState;
#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
static VAR(volatile uint16, IDSM_VAR_NO_INIT) IdsM_Filter_udBlockStateRed;
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */
static VAR(IdsM_Filters_BlockStateType, IDSM_VAR_NO_INIT) IdsM_Filter_udBlockStateWork;
#endif /* ( IDSM_CFG_USE_FIL_BLKSTATE == STD_ON ) */
#if ( IDSM_CFG_USE_FIL_RATELMT == STD_ON )
static VAR(volatile uint16, IDSM_VAR_NO_INIT) IdsM_Filter_u2QsevNum;
static VAR(volatile uint32, IDSM_VAR_NO_INIT) IdsM_Filter_u4QsevTime;
#endif /* ( IDSM_CFG_USE_FIL_RATELMT == STD_ON ) */
#if ( IDSM_CFG_USE_FIL_TRAFFICLMT == STD_ON )
static VAR(volatile uint16, IDSM_VAR_NO_INIT) IdsM_Filter_u2TrafficBytes;
static VAR(volatile uint32, IDSM_VAR_NO_INIT) IdsM_Filter_u4TrafficTime;
#endif /* ( IDSM_CFG_USE_FIL_TRAFFICLMT == STD_ON ) */

#define IDSM_STOP_SEC_VAR_NO_INIT
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
/* Function Name | IdsM_Filter_Init                                         */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_Filter_Init
(
    void
)
{
#if ( ( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON ) || ( IDSM_CFG_USE_FIL_THRESHOLD == STD_ON ) || ( IDSM_CFG_USE_FIL_NTH == STD_ON ) )
    uint16 u2_Index;

#if ( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON )
    for( u2_Index = 0U; u2_Index < IdsM_Cfg_AggreFilTmpAcss.u2ConfigNum; u2_Index++ )
    {
        IdsM_Cfg_AggreFilTmpAcss.ptTmp[u2_Index].u2Count = 0U;
    }
#endif /* ( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON ) */

#if ( IDSM_CFG_USE_FIL_THRESHOLD == STD_ON )
    for( u2_Index = 0U; u2_Index < IdsM_Cfg_ThreFilTmpAcss.u2ConfigNum; u2_Index++ )
    {
        IdsM_Cfg_ThreFilTmpAcss.ptTmp[u2_Index].u2EveThreCount = 0U;
    }
#endif /* ( IDSM_CFG_USE_FIL_THRESHOLD == STD_ON ) */

#if ( IDSM_CFG_USE_FIL_NTH == STD_ON )
    for( u2_Index = 0U; u2_Index < IdsM_Cfg_NthFilTmpAcss.u2ConfigNum; u2_Index++ )
    {
        IdsM_Cfg_NthFilTmpAcss.ptTmp[u2_Index].u2NthFilSEvCnt = IdsM_Cfg_FilterChainAcss.ptConfig[u2_Index].stEveNthFil.u2NthParam - IDSM_NTH_INITIALIZE;
    }
#endif /* ( IDSM_CFG_USE_FIL_NTH == STD_ON ) */

#if ( ( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON ) || ( IDSM_CFG_USE_FIL_THRESHOLD == STD_ON ) )
    for( u2_Index = 0U; u2_Index < IdsM_Cfg_FilChainTmpAcss.u2ConfigNum; u2_Index++ )
    {
#if ( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON )
        IdsM_Cfg_FilChainTmpAcss.ptTmp[u2_Index].u4AggreFilTimeCnt = 0UL;
#endif /* ( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON ) */
#if ( IDSM_CFG_USE_FIL_THRESHOLD == STD_ON )
        IdsM_Cfg_FilChainTmpAcss.ptTmp[u2_Index].u4ThresholdFilTimeCnt = 0UL;
#endif /* ( IDSM_CFG_USE_FIL_THRESHOLD == STD_ON ) */
    }
#endif /* ( ( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON ) || ( IDSM_CFG_USE_FIL_THRESHOLD == STD_ON ) ) */
#endif /* ( ( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON ) || ( IDSM_CFG_USE_FIL_THRESHOLD == STD_ON ) || ( IDSM_CFG_USE_FIL_NTH == STD_ON ) ) */

#if ( IDSM_CFG_USE_FIL_BLKSTATE == STD_ON )
    IdsM_Filter_udBlockState = 0U;
#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
    IdsM_Filter_udBlockStateRed = IDSM_RED_INIT_U2;
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */
#endif /* ( IDSM_CFG_USE_FIL_BLKSTATE == STD_ON ) */
#if ( IDSM_CFG_USE_FIL_RATELMT == STD_ON )
    IdsM_Filter_u2QsevNum = 0U;
    IdsM_Filter_u4QsevTime = 0UL;
#endif /* ( IDSM_CFG_USE_FIL_RATELMT == STD_ON ) */
#if ( IDSM_CFG_USE_FIL_TRAFFICLMT == STD_ON )
    IdsM_Filter_u2TrafficBytes = 0U;
    IdsM_Filter_u4TrafficTime = 0UL;
#endif /* ( IDSM_CFG_USE_FIL_TRAFFICLMT == STD_ON ) */

    return ;
}

#if ( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON )
/****************************************************************************/
/* Function Name | IdsM_Filter_GetAggreTmpData                              */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index                                                  */
/*               | ptData                                                   */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_Filter_GetAggreTmpData
(
    VAR(uint16, AUTOMATIC) u2Index,
    P2VAR(IdsMAggreFilTmpType, AUTOMATIC, AUTOMATIC) ptData
)
{
#if ( IDSM_CFG_USE_TIMESTAMP != IDSM_TS_OPT_NONE )
    ptData->udTimestamp = IdsM_Cfg_AggreFilTmpAcss.ptTmp[u2Index].udTimestamp;
#endif /* ( IDSM_CFG_USE_TIMESTAMP != IDSM_TS_OPT_NONE ) */
    ptData->u2Count = IdsM_Cfg_AggreFilTmpAcss.ptTmp[u2Index].u2Count;
#if ( IDSM_CFG_USE_CTXDATA == STD_ON )
    ptData->u2CtxDataSize = IdsM_Cfg_AggreFilTmpAcss.ptTmp[u2Index].u2CtxDataSize;
    ptData->u2TableIndex = IdsM_Cfg_AggreFilTmpAcss.ptTmp[u2Index].u2TableIndex;
    ptData->u2RecordIndex = IdsM_Cfg_AggreFilTmpAcss.ptTmp[u2Index].u2RecordIndex;
#else
    ptData->u2Dummy = 0U;
#endif /* ( IDSM_CFG_USE_CTXDATA == STD_ON ) */

    return ;
}
#endif /* ( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON ) */

/****************************************************************************/
/* Function Name | IdsM_Filter_UpdateCount                                  */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_Filter_UpdateCount
(
    void
)
{
#if ( ( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON ) || ( IDSM_CFG_USE_FIL_THRESHOLD == STD_ON ) || ( IDSM_CFG_USE_FIL_RATELMT == STD_ON ) || ( IDSM_CFG_USE_FIL_TRAFFICLMT == STD_ON ) )
    uint32 u4_TimerCnt;
#if ( ( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON ) || ( IDSM_CFG_USE_FIL_THRESHOLD == STD_ON ) )
    uint16 u2_Index;

    for( u2_Index = 0U; u2_Index < IdsM_Cfg_FilChainTmpAcss.u2ConfigNum; u2_Index++ )
    {
#if ( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON )
        u4_TimerCnt = IdsM_Cfg_FilChainTmpAcss.ptTmp[u2_Index].u4AggreFilTimeCnt;

        u4_TimerCnt++;

        if( u4_TimerCnt >=
            IdsM_Cfg_FilterChainAcss.ptConfig[u2_Index].stEveAggreFil.u4AggreTimeInterval )
        {
            u4_TimerCnt = IDSM_INTERVAL_END;
        }

        IdsM_Cfg_FilChainTmpAcss.ptTmp[u2_Index].u4AggreFilTimeCnt = u4_TimerCnt;

#endif /* ( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON ) */
#if ( IDSM_CFG_USE_FIL_THRESHOLD == STD_ON )
        u4_TimerCnt = IdsM_Cfg_FilChainTmpAcss.ptTmp[u2_Index].u4ThresholdFilTimeCnt;

        u4_TimerCnt++;

        if( u4_TimerCnt >=
            IdsM_Cfg_FilterChainAcss.ptConfig[u2_Index].stEveThreFil.u4EventThresholdTimeInterval )
        {
            u4_TimerCnt = IDSM_INTERVAL_END;
        }

        IdsM_Cfg_FilChainTmpAcss.ptTmp[u2_Index].u4ThresholdFilTimeCnt = u4_TimerCnt;

#endif /* ( IDSM_CFG_USE_FIL_THRESHOLD == STD_ON ) */
    }
#endif /* ( ( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON ) || ( IDSM_CFG_USE_FIL_THRESHOLD == STD_ON ) ) */
#if ( IDSM_CFG_USE_FIL_RATELMT == STD_ON )

        u4_TimerCnt = IdsM_Filter_u4QsevTime;

        u4_TimerCnt++;

        if( u4_TimerCnt >= IdsM_Cfg_FilEveRateLimit.u4RateLimitTimeInterval )
        {
            u4_TimerCnt = IDSM_INTERVAL_END;
        }

        IdsM_Filter_u4QsevTime = u4_TimerCnt;

#endif /* ( IDSM_CFG_USE_FIL_RATELMT == STD_ON ) */
#if ( IDSM_CFG_USE_FIL_TRAFFICLMT == STD_ON )

        u4_TimerCnt = IdsM_Filter_u4TrafficTime;

        u4_TimerCnt++;

        if( u4_TimerCnt >= IdsM_Cfg_FilTrafficLimit.u4TrafficLimitTimeInterval )
        {
            u4_TimerCnt = IDSM_INTERVAL_END;
        }

        IdsM_Filter_u4TrafficTime = u4_TimerCnt;

#endif /* ( IDSM_CFG_USE_FIL_TRAFFICLMT == STD_ON ) */
#endif /* ( ( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON ) || ( IDSM_CFG_USE_FIL_THRESHOLD == STD_ON ) || ( IDSM_CFG_USE_FIL_RATELMT == STD_ON ) ) */

    return ;
}

/****************************************************************************/
/* Function Name | IdsM_Filter_MainProcess                                  */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index                                                  */
/*               | ptData                                                   */
/*               | u1FilChainStIndex                                        */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_Filter_MainProcess
(
    VAR(uint16, AUTOMATIC) u2Index,
    P2CONST(IdsMEventBuffType, AUTOMATIC, AUTOMATIC) ptData,
    VAR(uint8, AUTOMATIC) u1FilChainStIndex
)
{
#if (( IDSM_CFG_USE_FIL_RATELMT == STD_ON ) || ( IDSM_CFG_USE_FIL_TRAFFICLMT == STD_ON ) || (IDSM_CFG_USE_FILTERCHAIN == STD_ON) )
    IdsM_FilterResultType             ud_FilRet = IDSM_FILTER_RES_ADOPT;
#endif /* (( IDSM_CFG_USE_FIL_RATELMT == STD_ON ) || ( IDSM_CFG_USE_FIL_TRAFFICLMT == STD_ON ) || (IDSM_CFG_USE_FILTERCHAIN == STD_ON) ) */
    IdsMFilterFuncParamType           st_FuncPrm;
    Std_ReturnType                    ud_SinkRet;

#if (( IDSM_CFG_USE_FIL_RATELMT == STD_ON ) || ( IDSM_CFG_USE_FIL_TRAFFICLMT == STD_ON ))
#if (( IDSM_CFG_USE_INTSEV_EVEBUFFUL == STD_ON ) || ( IDSM_CFG_USE_INTSEV_CTXBUFFUL == STD_ON ) || ( IDSM_CFG_USE_INTSEV_TRAFFICLMIT == STD_ON ))
    boolean                           b_IntSEvFlag;
#endif /* (( IDSM_CFG_USE_INTSEV_EVEBUFFUL == STD_ON ) || ( IDSM_CFG_USE_INTSEV_CTXBUFFUL == STD_ON ) || ( IDSM_CFG_USE_INTSEV_TRAFFICLMIT == STD_ON )) */
#endif /* (( IDSM_CFG_USE_FIL_RATELMT == STD_ON ) || ( IDSM_CFG_USE_FIL_TRAFFICLMT == STD_ON )) */

#if ( IDSM_CFG_USE_INTSEV_TRAFFICLMIT == STD_ON )
    uint16                            u2_TrafficIntSEvId = (uint16)IdsM_Cfg_udTrafficExceedId;
#endif /* ( IDSM_CFG_USE_INTSEV_TRAFFICLMIT == STD_ON ) */

#if ( IDSM_CFG_USE_FILTERCHAIN == STD_ON )
    uint16                            u2_FilterChainRef;
    IdsM_Filters_ReportingModeType    ud_ReportMode;
    uint16                            u2_TableIndex = IDSM_INVALID_INDEX;
    uint16                            u2_RecordIndex = IDSM_INVALID_INDEX;
    uint16                            u2_Lpc;
#elif (( IDSM_CFG_USE_FIL_RATELMT == STD_ON ) || ( IDSM_CFG_USE_FIL_TRAFFICLMT == STD_ON ))
    uint16                            u2_TableIndex = IDSM_INVALID_INDEX;
    uint16                            u2_RecordIndex = IDSM_INVALID_INDEX;
    uint16                            u2_Lpc;
#endif

#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
    if( u2Index < IdsM_Cfg_EventAcss.u2ConfigNum )
    {
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */
        IdsM_Std_EventBuffCopy(&st_FuncPrm.stSEvData, ptData);
#if (( IDSM_CFG_USE_FILTERCHAIN == STD_ON ) || ( IDSM_CFG_USE_FIL_RATELMT == STD_ON ) || ( IDSM_CFG_USE_FIL_TRAFFICLMT == STD_ON ))
        st_FuncPrm.u2Index = u2Index;
#endif /* (( IDSM_CFG_USE_FILTERCHAIN == STD_ON ) || ( IDSM_CFG_USE_FIL_RATELMT == STD_ON ) || ( IDSM_CFG_USE_FIL_TRAFFICLMT == STD_ON )) */

#if ( IDSM_CFG_USE_FILTERCHAIN == STD_ON )

        u2_FilterChainRef = IdsM_Cfg_EventAcss.ptConfig[u2Index].u2FilterChainRef;

        if( u2_FilterChainRef != IDSM_INVALID_INDEX )
        {
            ud_ReportMode = IdsM_Filter_ReportingMode( u2Index );

            if( ( ud_ReportMode != IDSM_REPORTING_MODE_BRIEF_BYPASSING_FILTERS ) && ( ud_ReportMode != IDSM_REPORTING_MODE_DETAILED_BYPASSING_FILTERS ) )
            {
                for( u2_Lpc = u1FilChainStIndex; u2_Lpc < (uint16)IDSM_FILTER_CHAINS; u2_Lpc++ )
                {
                    if( IdsM_Cfg_FilChainFuncTblAcss.ptConfig[u2_FilterChainRef].ptFunc[u2_Lpc] != NULL_PTR )
                    {
                        ud_FilRet = IdsM_Cfg_FilChainFuncTblAcss.ptConfig[u2_FilterChainRef].ptFunc[u2_Lpc]( &st_FuncPrm,
                                                                                                              &u2_TableIndex,
                                                                                                              &u2_RecordIndex );
                        if( ud_FilRet == IDSM_FILTER_RES_DEST )
                        {
                            break;
                        }
                    }
                }
            }
        }
#endif /* ( IDSM_CFG_USE_FILTERCHAIN == STD_ON ) */

#if (( IDSM_CFG_USE_FIL_RATELMT == STD_ON ) || ( IDSM_CFG_USE_FIL_TRAFFICLMT == STD_ON ))
#if (( IDSM_CFG_USE_INTSEV_EVEBUFFUL == STD_ON ) || ( IDSM_CFG_USE_INTSEV_CTXBUFFUL == STD_ON ) || ( IDSM_CFG_USE_INTSEV_TRAFFICLMIT == STD_ON ))
        b_IntSEvFlag = IdsM_Filter_JudgeIntSEv( u2Index );
#endif /* (( IDSM_CFG_USE_INTSEV_EVEBUFFUL == STD_ON ) || ( IDSM_CFG_USE_INTSEV_CTXBUFFUL == STD_ON ) || ( IDSM_CFG_USE_INTSEV_TRAFFICLMIT == STD_ON )) */
#if (( IDSM_CFG_USE_FILTERCHAIN == STD_ON ) && (( IDSM_CFG_USE_INTSEV_EVEBUFFUL == STD_ON ) || ( IDSM_CFG_USE_INTSEV_CTXBUFFUL == STD_ON ) || ( IDSM_CFG_USE_INTSEV_TRAFFICLMIT == STD_ON )))
        if( ( ud_FilRet != IDSM_FILTER_RES_DEST ) && ( b_IntSEvFlag == (boolean)FALSE) )
        {
#elif (( IDSM_CFG_USE_INTSEV_EVEBUFFUL == STD_ON ) || ( IDSM_CFG_USE_INTSEV_CTXBUFFUL == STD_ON ) || ( IDSM_CFG_USE_INTSEV_TRAFFICLMIT == STD_ON ))
        if ( b_IntSEvFlag == (boolean)FALSE )
        {
#elif ( IDSM_CFG_USE_FILTERCHAIN == STD_ON )
        if( ud_FilRet != IDSM_FILTER_RES_DEST )
        {
#endif
            for( u2_Lpc = 0U; u2_Lpc < (uint16)IDSM_GLOBAL_RATEFILS; u2_Lpc++ )
            {
                if( IdsM_Cfg_GlobalRateFilFuncTbl.ptFunc[u2_Lpc] != NULL_PTR )
                {
                    ud_FilRet = IdsM_Cfg_GlobalRateFilFuncTbl.ptFunc[u2_Lpc]( &st_FuncPrm,
                                                                               &u2_TableIndex,
                                                                               &u2_RecordIndex );
                    if( ud_FilRet == IDSM_FILTER_RES_DEST )
                    {
#if ( IDSM_CFG_USE_INTSEV_TRAFFICLMIT == STD_ON )
                        if( u2_Lpc == IDSM_START_TRAFFICLIMIT )
                        {
                            IdsM_InterSEv_SetBuff( u2_TrafficIntSEvId, &IdsM_Cfg_InterBuff_TrafficLimit );
                        }
#endif /* ( IDSM_CFG_USE_INTSEV_TRAFFICLMIT == STD_ON ) */
                        break;
                    }
                }
            }
#if ( (IDSM_CFG_USE_FILTERCHAIN == STD_ON) || ( IDSM_CFG_USE_INTSEV_EVEBUFFUL == STD_ON ) || ( IDSM_CFG_USE_INTSEV_CTXBUFFUL == STD_ON ) || ( IDSM_CFG_USE_INTSEV_TRAFFICLMIT == STD_ON ) )
        }
#endif /* ( (IDSM_CFG_USE_FILTERCHAIN == STD_ON) || ( IDSM_CFG_USE_INTSEV_EVEBUFFUL == STD_ON ) || ( IDSM_CFG_USE_INTSEV_CTXBUFFUL == STD_ON ) || ( IDSM_CFG_USE_INTSEV_TRAFFICLMIT == STD_ON ) ) */
#endif /* (( IDSM_CFG_USE_FIL_RATELMT == STD_ON ) || ( IDSM_CFG_USE_FIL_TRAFFICLMT == STD_ON )) */


#if ((IDSM_CFG_USE_FILTERCHAIN == STD_ON) || ( IDSM_CFG_USE_FIL_RATELMT == STD_ON ) || ( IDSM_CFG_USE_FIL_TRAFFICLMT == STD_ON ) )
        if( ud_FilRet != IDSM_FILTER_RES_DEST )
        {
#endif /* ((IDSM_CFG_USE_FILTERCHAIN == STD_ON) || ( IDSM_CFG_USE_FIL_RATELMT == STD_ON ) || ( IDSM_CFG_USE_FIL_TRAFFICLMT == STD_ON ) ) */
            SchM_Enter_IdsM_General();
            ud_SinkRet = IdsM_Sink_SetBuff( &st_FuncPrm.stSEvData );
            SchM_Exit_IdsM_General();

            if( ud_SinkRet != (Std_ReturnType)E_OK )
            {
                IdsM_Sink_QSEvBuffFullNotify( &st_FuncPrm.stSEvData );
                
#if ( IDSM_CFG_USE_CTXDATA == STD_ON )
                if( st_FuncPrm.stSEvData.u2TableIndex != IDSM_INVALID_INDEX )
                {
                    SchM_Enter_IdsM_General();
                    IdsM_Context_ClearBuff( st_FuncPrm.stSEvData.u2TableIndex, st_FuncPrm.stSEvData.u2RecordIndex );
                    SchM_Exit_IdsM_General();
                }
#endif /* ( IDSM_CFG_USE_CTXDATA == STD_ON ) */
            }
#if ((IDSM_CFG_USE_FILTERCHAIN == STD_ON) || ( IDSM_CFG_USE_FIL_RATELMT == STD_ON ) || ( IDSM_CFG_USE_FIL_TRAFFICLMT == STD_ON ) )
        }
        else
        {
#if ( IDSM_CFG_USE_CTXDATA == STD_ON )
            if( u2_TableIndex != IDSM_INVALID_INDEX )
            {
                SchM_Enter_IdsM_General();
                IdsM_Context_ClearBuff( u2_TableIndex, u2_RecordIndex );
                SchM_Exit_IdsM_General();
            }
#endif /* ( IDSM_CFG_USE_CTXDATA == STD_ON ) */
        }
#endif /* ((IDSM_CFG_USE_FILTERCHAIN == STD_ON) || ( IDSM_CFG_USE_FIL_RATELMT == STD_ON ) || ( IDSM_CFG_USE_FIL_TRAFFICLMT == STD_ON ) ) */

#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
    }
    else
    {
#if ( IDSM_CFG_USE_CTXDATA == STD_ON )
        if( ptData->u2TableIndex != IDSM_INVALID_INDEX )
        {
            SchM_Enter_IdsM_General();
            IdsM_Context_ClearBuff( ptData->u2TableIndex, ptData->u2RecordIndex );
            SchM_Exit_IdsM_General();
        }
#endif /* ( IDSM_CFG_USE_CTXDATA == STD_ON ) */
    }
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */

    return ;
}

/****************************************************************************/
/* Function Name | IdsM_Filter_ReportingMode                                */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index                                                  */
/* Return Value  | IdsM_Filters_ReportingModeType                           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(IdsM_Filters_ReportingModeType, IDSM_CODE) IdsM_Filter_ReportingMode
(
    VAR(uint16, AUTOMATIC) u2Index
)
{
    return IdsM_Cfg_EventAcss.ptConfig[u2Index].udReportModeFilter;
}
#if ( IDSM_CFG_USE_FIL_BLKSTATE == STD_ON )
/****************************************************************************/
/* Function Name | IdsM_Filter_SetBlockState                                */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | udBlockState                                             */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_Filter_SetBlockState
(
    VAR(IdsM_Filters_BlockStateType, AUTOMATIC) udBlockState
)
{
    IdsM_Filter_udBlockState = udBlockState;
#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
    IdsM_Filter_udBlockStateRed = (uint16)(~udBlockState);
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */

    return ;
}

/****************************************************************************/
/* Function Name | IdsM_Filter_BlockState                                   */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | ptFilFuncParam                                           */
/*               | ptTableIndex                                             */
/*               | ptRecordIndex                                            */
/* Return Value  | IdsM_FilterResultType                                    */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(IdsM_FilterResultType, IDSM_CODE) IdsM_Filter_BlockState
(
    P2CONST(IdsMFilterFuncParamType, AUTOMATIC,IDSM_APPL_CONST) ptFilFuncParam,
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) ptTableIndex,
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) ptRecordIndex
)
{
    IdsM_FilterResultType ud_FilRet = IDSM_FILTER_RES_ADOPT;
    uint16 u2_FilChain_Index;
    IdsM_Filters_BlockStateType ud_BlockState;

    u2_FilChain_Index = IdsM_Cfg_EventAcss.ptConfig[ptFilFuncParam->u2Index].u2FilterChainRef;
    ud_BlockState = (IdsM_Filters_BlockStateType)IdsM_Cfg_FilterChainAcss.ptConfig[u2_FilChain_Index].stBlkStateFil.u2BlkStateRef;

    if( ( ud_BlockState & IdsM_Filter_udBlockStateWork ) != (IdsM_Filters_BlockStateType)0U )
    {
        ud_FilRet = IDSM_FILTER_RES_DEST;
#if ( IDSM_CFG_USE_CTXDATA == STD_ON )
        *ptTableIndex = ptFilFuncParam->stSEvData.u2TableIndex;
        *ptRecordIndex = ptFilFuncParam->stSEvData.u2RecordIndex;
#endif /* ( IDSM_CFG_USE_CTXDATA == STD_ON ) */
    }

    return ud_FilRet ;
}

/****************************************************************************/
/* Function Name | IdsM_Filter_BlockCpy                                     */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_Filter_BlockStateCpy
(
    void
)
{
    IdsM_Filters_BlockStateType ud_BlockState = IdsM_Filter_udBlockState;
#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
    uint16 ud_BlockStateRed = IdsM_Filter_udBlockStateRed;
    
    if ( ud_BlockState == (uint16)(~ud_BlockStateRed) ) 
    {
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */
        IdsM_Filter_udBlockStateWork = ud_BlockState;
#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
    }
    else
    {
        IdsM_Filter_udBlockStateWork = 0U;
        IdsM_General_SetRamError();
    }
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */

    return ;
}

#endif /* ( IDSM_CFG_USE_FIL_BLKSTATE == STD_ON ) */
#if ( IDSM_CFG_USE_FIL_NTH == STD_ON )
/****************************************************************************/
/* Function Name | IdsM_Filter_ForwardEveryNth                              */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | ptFilFuncParam                                           */
/*               | ptTableIndex                                             */
/*               | ptRecordIndex                                            */
/* Return Value  | IdsM_FilterResultType                                    */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(IdsM_FilterResultType, IDSM_CODE) IdsM_Filter_ForwardEveryNth
(
    P2CONST(IdsMFilterFuncParamType, AUTOMATIC,IDSM_APPL_CONST) ptFilFuncParam,
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) ptTableIndex,
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) ptRecordIndex
)
{
    IdsM_FilterResultType ud_FilRet = IDSM_FILTER_RES_ADOPT;
    uint16 u2_NthFilCnt;
    uint16 u2_NthRef_Index;
    uint16 u2_FilChain_Index;

    u2_NthRef_Index = IdsM_Cfg_EventAcss.ptConfig[ptFilFuncParam->u2Index].u2NthFilDataRef;
    u2_NthFilCnt = IdsM_Cfg_NthFilTmpAcss.ptTmp[u2_NthRef_Index].u2NthFilSEvCnt;
    u2_FilChain_Index = IdsM_Cfg_EventAcss.ptConfig[ptFilFuncParam->u2Index].u2FilterChainRef;

    u2_NthFilCnt++;

    if( u2_NthFilCnt >= IdsM_Cfg_FilterChainAcss.ptConfig[u2_FilChain_Index].stEveNthFil.u2NthParam )
    {
        u2_NthFilCnt = (uint16)0U;
    }
    else
    {
        ud_FilRet = IDSM_FILTER_RES_DEST;
#if ( IDSM_CFG_USE_CTXDATA == STD_ON )
        *ptTableIndex = ptFilFuncParam->stSEvData.u2TableIndex;
        *ptRecordIndex = ptFilFuncParam->stSEvData.u2RecordIndex;
#endif /* ( IDSM_CFG_USE_CTXDATA == STD_ON ) */
    }

    IdsM_Cfg_NthFilTmpAcss.ptTmp[u2_NthRef_Index].u2NthFilSEvCnt = u2_NthFilCnt;

    return ud_FilRet ;
}

#endif /* ( IDSM_CFG_USE_FIL_NTH == STD_ON ) */
#if ( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON )
/****************************************************************************/
/* Function Name | IdsM_Filter_AggreSetBuff                                 */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | ptFilFuncParam                                           */
/*               | ptTableIndex                                             */
/*               | ptRecordIndex                                            */
/* Return Value  | IdsM_FilterResultType                                    */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(IdsM_FilterResultType, IDSM_CODE) IdsM_Filter_AggreSetBuff
(
    P2CONST(IdsMFilterFuncParamType, AUTOMATIC,IDSM_APPL_CONST) ptFilFuncParam,
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) ptTableIndex,
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) ptRecordIndex
)
{
    IdsM_FilterResultType ud_FilRet = IDSM_FILTER_RES_DEST;
    uint16 u2_Count;
    uint16 u2_AggreTmpRef;
    uint16 u2_FilChain_Index;
    uint8 u1_CtxDataSrcSelector;

    u2_AggreTmpRef = IdsM_Cfg_EventAcss.ptConfig[ptFilFuncParam->u2Index].u2AggreFilDataRef;
    u2_FilChain_Index = IdsM_Cfg_EventAcss.ptConfig[ptFilFuncParam->u2Index].u2FilterChainRef;
    u1_CtxDataSrcSelector = IdsM_Cfg_FilterChainAcss.ptConfig[u2_FilChain_Index].stEveAggreFil.u1CtxDataSourceSelector;
    u2_Count = IdsM_Cfg_AggreFilTmpAcss.ptTmp[u2_AggreTmpRef].u2Count;

    if( u1_CtxDataSrcSelector == IDSM_FILTERS_CTX_USE_FIRST )
    {
        if( u2_Count == (uint16)0U )
        {

#if ( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR )||( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_CUSTOM )
            IdsM_Cfg_AggreFilTmpAcss.ptTmp[u2_AggreTmpRef].udTimestamp = ptFilFuncParam->stSEvData.udTimestamp;
#endif /* ( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR )||( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_CUSTOM ) */

#if ( IDSM_CFG_USE_CTXDATA == STD_ON )
            IdsM_Cfg_AggreFilTmpAcss.ptTmp[u2_AggreTmpRef].u2CtxDataSize = ptFilFuncParam->stSEvData.u2CtxDataSize;
            IdsM_Cfg_AggreFilTmpAcss.ptTmp[u2_AggreTmpRef].u2TableIndex = ptFilFuncParam->stSEvData.u2TableIndex;
            IdsM_Cfg_AggreFilTmpAcss.ptTmp[u2_AggreTmpRef].u2RecordIndex = ptFilFuncParam->stSEvData.u2RecordIndex;
        }
        else
        {
            *ptTableIndex = ptFilFuncParam->stSEvData.u2TableIndex;
            *ptRecordIndex = ptFilFuncParam->stSEvData.u2RecordIndex;
#endif /* ( IDSM_CFG_USE_CTXDATA == STD_ON ) */
        }
    }
    else
    {

#if ( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR )||( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_CUSTOM )
        IdsM_Cfg_AggreFilTmpAcss.ptTmp[u2_AggreTmpRef].udTimestamp = ptFilFuncParam->stSEvData.udTimestamp;
#endif /* ( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR )||( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_CUSTOM ) */

#if ( IDSM_CFG_USE_CTXDATA == STD_ON )
        IdsM_Cfg_AggreFilTmpAcss.ptTmp[u2_AggreTmpRef].u2CtxDataSize = ptFilFuncParam->stSEvData.u2CtxDataSize;

        if( u2_Count!= (uint16)0U )
        {
            *ptTableIndex = IdsM_Cfg_AggreFilTmpAcss.ptTmp[u2_AggreTmpRef].u2TableIndex;
            *ptRecordIndex = IdsM_Cfg_AggreFilTmpAcss.ptTmp[u2_AggreTmpRef].u2RecordIndex;
        }
        IdsM_Cfg_AggreFilTmpAcss.ptTmp[u2_AggreTmpRef].u2TableIndex = ptFilFuncParam->stSEvData.u2TableIndex;
        IdsM_Cfg_AggreFilTmpAcss.ptTmp[u2_AggreTmpRef].u2RecordIndex = ptFilFuncParam->stSEvData.u2RecordIndex;
#endif /* ( IDSM_CFG_USE_CTXDATA == STD_ON ) */
    }

    if( ( IDSM_UINT16_MAX - u2_Count ) >= ptFilFuncParam->stSEvData.u2Count )
    {
        u2_Count += ptFilFuncParam->stSEvData.u2Count;
        IdsM_Cfg_AggreFilTmpAcss.ptTmp[u2_AggreTmpRef].u2Count = u2_Count;
    }
    else
    {
        IdsM_Cfg_AggreFilTmpAcss.ptTmp[u2_AggreTmpRef].u2Count = IDSM_UINT16_MAX;
    }

    return ud_FilRet;
}

/****************************************************************************/
/* Function Name | IdsM_Filter_AggreCheckPeriod                             */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index                                                  */
/* Return Value  | Std_ReturnType                                           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, IDSM_CODE) IdsM_Filter_AggreCheckPeriod
(
    VAR(uint16, AUTOMATIC) u2Index
)
{
    Std_ReturnType ud_StdRet = (Std_ReturnType)E_NOT_OK;
    uint16 u2_FilChain_Index;
    uint32 u4_AggreTimeInterval;

    u2_FilChain_Index = IdsM_Cfg_EventAcss.ptConfig[u2Index].u2FilterChainRef;
    u4_AggreTimeInterval = IdsM_Cfg_FilChainTmpAcss.ptTmp[u2_FilChain_Index].u4AggreFilTimeCnt;

    if( u4_AggreTimeInterval == IDSM_INTERVAL_END )
    {
        ud_StdRet = (Std_ReturnType)E_OK;
    }

    return ud_StdRet;
}

/****************************************************************************/
/* Function Name | IdsM_Filter_AggreClearBuff                               */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index                                                  */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_Filter_AggreClearBuff
(
    VAR(uint16, AUTOMATIC) u2Index
)
{
    uint16 u2_AggreTmpRef;

    u2_AggreTmpRef = IdsM_Cfg_EventAcss.ptConfig[u2Index].u2AggreFilDataRef;

    IdsM_Cfg_AggreFilTmpAcss.ptTmp[u2_AggreTmpRef].u2Count = 0U;

    return ;
}
#endif /* ( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON ) */
#if ( IDSM_CFG_USE_FIL_THRESHOLD == STD_ON )
/****************************************************************************/
/* Function Name | IdsM_Filter_EventThreshold                               */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | ptFilFuncParam                                           */
/*               | ptTableIndex                                             */
/*               | ptRecordIndex                                            */
/* Return Value  | IdsM_FilterResultType                                    */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(IdsM_FilterResultType, IDSM_CODE) IdsM_Filter_EventThreshold
(
    P2CONST(IdsMFilterFuncParamType, AUTOMATIC,IDSM_APPL_CONST) ptFilFuncParam,
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) ptTableIndex,
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) ptRecordIndex
)
{
    IdsM_FilterResultType ud_FilRet = IDSM_FILTER_RES_ADOPT;
    uint16 u2_ThresholdCount;
    uint16 u2_ThresholdTmpRef;
    uint16 u2_FilChain_Index;
    uint16 u2_ThresholdNumber;

    u2_ThresholdTmpRef = IdsM_Cfg_EventAcss.ptConfig[ptFilFuncParam->u2Index].u2ThreFilDataRef;
    u2_ThresholdCount = IdsM_Cfg_ThreFilTmpAcss.ptTmp[u2_ThresholdTmpRef].u2EveThreCount;
    u2_FilChain_Index = IdsM_Cfg_EventAcss.ptConfig[ptFilFuncParam->u2Index].u2FilterChainRef;
    u2_ThresholdNumber = IdsM_Cfg_FilterChainAcss.ptConfig[u2_FilChain_Index].stEveThreFil.u2EveThreNumber;

    if( ( IDSM_UINT16_MAX - u2_ThresholdCount ) >= ptFilFuncParam->stSEvData.u2Count )
    {
        u2_ThresholdCount = u2_ThresholdCount + ptFilFuncParam->stSEvData.u2Count;
        IdsM_Cfg_ThreFilTmpAcss.ptTmp[u2_ThresholdTmpRef].u2EveThreCount = u2_ThresholdCount;

        if( u2_ThresholdCount < u2_ThresholdNumber )
        {
            ud_FilRet = IDSM_FILTER_RES_DEST;
#if ( IDSM_CFG_USE_CTXDATA == STD_ON )
            *ptTableIndex = ptFilFuncParam->stSEvData.u2TableIndex;
            *ptRecordIndex = ptFilFuncParam->stSEvData.u2RecordIndex;
#endif /* ( IDSM_CFG_USE_CTXDATA == STD_ON ) */
        }
    }
    else
    {
        IdsM_Cfg_ThreFilTmpAcss.ptTmp[u2_ThresholdTmpRef].u2EveThreCount = IDSM_UINT16_MAX;
    }
    return ud_FilRet;
}

/****************************************************************************/
/* Function Name | IdsM_Filter_ThresholdClearBuff                           */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index                                                  */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_Filter_ThresholdClearBuff
(
    VAR(uint16, AUTOMATIC) u2Index
)
{
    uint16 u2_FilChain_Index;
    uint16 u2_ThresholdTmpRef;
    uint32 u4_ThresholdTimeInterval;

    u2_FilChain_Index = IdsM_Cfg_EventAcss.ptConfig[u2Index].u2FilterChainRef;
    u2_ThresholdTmpRef = IdsM_Cfg_EventAcss.ptConfig[u2Index].u2ThreFilDataRef;
    u4_ThresholdTimeInterval = IdsM_Cfg_FilChainTmpAcss.ptTmp[u2_FilChain_Index].u4ThresholdFilTimeCnt;

    if( u4_ThresholdTimeInterval == IDSM_INTERVAL_END )
    {
        IdsM_Cfg_ThreFilTmpAcss.ptTmp[u2_ThresholdTmpRef].u2EveThreCount = 0U;
    }
    return ;
}
#endif /* ( IDSM_CFG_USE_FIL_THRESHOLD == STD_ON ) */
#if ( IDSM_CFG_USE_FIL_RATELMT == STD_ON )
/****************************************************************************/
/* Function Name | IdsM_Filter_EventRateLimitation                          */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | ptFilFuncParam                                           */
/*               | ptTableIndex                                             */
/*               | ptRecordIndex                                            */
/* Return Value  | IdsM_FilterResultType                                    */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(IdsM_FilterResultType, IDSM_CODE) IdsM_Filter_EventRateLimitation
(
    P2CONST(IdsMFilterFuncParamType, AUTOMATIC,IDSM_APPL_CONST) ptFilFuncParam,
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) ptTableIndex,
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) ptRecordIndex
)
{
    IdsM_FilterResultType ud_FilRet = IDSM_FILTER_RES_ADOPT;
    uint16 u2_QsevNum = IdsM_Filter_u2QsevNum;

    if( u2_QsevNum < IdsM_Cfg_FilEveRateLimit.u2RateLimitMaxEve )
    {
        u2_QsevNum++;
        IdsM_Filter_u2QsevNum = u2_QsevNum;
    }
    else
    {
        ud_FilRet = IDSM_FILTER_RES_DEST;
#if ( IDSM_CFG_USE_CTXDATA == STD_ON )
        *ptTableIndex = ptFilFuncParam->stSEvData.u2TableIndex;
        *ptRecordIndex = ptFilFuncParam->stSEvData.u2RecordIndex;
#endif /* ( IDSM_CFG_USE_CTXDATA == STD_ON ) */
    }
    return ud_FilRet;
}
/****************************************************************************/
/* Function Name | IdsM_Filter_EventRateClearNum                            */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_Filter_EventRateClearNum
(
    void
)
{
    uint32 u4_QsevTime = IdsM_Filter_u4QsevTime;

    if( u4_QsevTime == IDSM_INTERVAL_END )
    {
        IdsM_Filter_u2QsevNum = 0U;
    }
    return ;
}
#endif /* ( IDSM_CFG_USE_FIL_RATELMT == STD_ON ) */
#if ( IDSM_CFG_USE_FIL_TRAFFICLMT == STD_ON )
/****************************************************************************/
/* Function Name | IdsM_Filter_TrafficLimitation                            */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | ptFilFuncParam                                           */
/*               | ptTableIndex                                             */
/*               | ptRecordIndex                                            */
/* Return Value  | IdsM_FilterResultType                                    */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(IdsM_FilterResultType, IDSM_CODE) IdsM_Filter_TrafficLimitation
(
    P2CONST(IdsMFilterFuncParamType, AUTOMATIC,IDSM_APPL_CONST) ptFilFuncParam,
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) ptTableIndex,
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) ptRecordIndex
)
{
    IdsM_FilterResultType ud_FilRet = IDSM_FILTER_RES_ADOPT;
    uint16 u2_AddBytes;
    uint16 u2_TrafficBytes = IdsM_Filter_u2TrafficBytes;

    IdsM_Sink_TxMsgSizeCalc( &ptFilFuncParam->stSEvData, &u2_AddBytes );

    if( ( IdsM_Cfg_FilTrafficLimit.u2TrafficLimitMaxByte - u2_TrafficBytes ) >= u2_AddBytes )
    {
        IdsM_Filter_u2TrafficBytes = u2_TrafficBytes + u2_AddBytes;
    }
    else
    {
        ud_FilRet = IDSM_FILTER_RES_DEST;
#if ( IDSM_CFG_USE_CTXDATA == STD_ON )
        *ptTableIndex = ptFilFuncParam->stSEvData.u2TableIndex;
        *ptRecordIndex = ptFilFuncParam->stSEvData.u2RecordIndex;
#endif /* ( IDSM_CFG_USE_CTXDATA == STD_ON ) */
    }
    return ud_FilRet;
}

/****************************************************************************/
/* Function Name | IdsM_Filter_TrafficClearBytes                            */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_Filter_TrafficClearBytes
(
    void
)
{
    uint32 u4_TrafficTime = IdsM_Filter_u4TrafficTime;

    if( u4_TrafficTime == IDSM_INTERVAL_END )
    {
        IdsM_Filter_u2TrafficBytes = 0U;
    }
    return ;
}
#endif /* ( IDSM_CFG_USE_FIL_TRAFFICLMT == STD_ON ) */

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#if (( IDSM_CFG_USE_FIL_RATELMT == STD_ON ) || ( IDSM_CFG_USE_FIL_TRAFFICLMT == STD_ON ))
#if (( IDSM_CFG_USE_INTSEV_EVEBUFFUL == STD_ON ) || ( IDSM_CFG_USE_INTSEV_CTXBUFFUL == STD_ON ) || ( IDSM_CFG_USE_INTSEV_TRAFFICLMIT == STD_ON ))
/****************************************************************************/
/* Function Name | IdsM_Filter_JudgeIntSEv                                  */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index :                                                */
/* Return Value  | boolean                                                  */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(boolean, IDSM_CODE) IdsM_Filter_JudgeIntSEv
(
    VAR(uint16, AUTOMATIC) u2Index
)
{
    boolean b_IntSEvFlag = FALSE;
    uint16  u2_IntSEvId;
#if ( IDSM_CFG_USE_INTSEV_EVEBUFFUL == STD_ON )
    u2_IntSEvId = (uint16)IdsM_Cfg_udEveFullId;
    if( u2Index == u2_IntSEvId )
    {
        b_IntSEvFlag = TRUE;
    }
#endif /* ( IDSM_CFG_USE_INTSEV_EVEBUFFUL == STD_ON ) */
#if ( IDSM_CFG_USE_INTSEV_CTXBUFFUL == STD_ON )
    u2_IntSEvId = (uint16)IdsM_Cfg_udCtxFullId;
    if( u2Index == u2_IntSEvId )
    {
        b_IntSEvFlag = TRUE;
    }
#endif /* ( IDSM_CFG_USE_INTSEV_CTXBUFFUL == STD_ON ) */
#if ( IDSM_CFG_USE_INTSEV_TRAFFICLMIT == STD_ON )
    u2_IntSEvId = (uint16)IdsM_Cfg_udTrafficExceedId;
    if( u2Index == u2_IntSEvId )
    {
        b_IntSEvFlag = TRUE;
    }
#endif /* ( IDSM_CFG_USE_INTSEV_TRAFFICLMIT == STD_ON ) */

    return b_IntSEvFlag;
}

#endif /* (( IDSM_CFG_USE_INTSEV_EVEBUFFUL == STD_ON ) || ( IDSM_CFG_USE_INTSEV_CTXBUFFUL == STD_ON ) || ( IDSM_CFG_USE_INTSEV_TRAFFICLMIT == STD_ON )) */
#endif /* (( IDSM_CFG_USE_FIL_RATELMT == STD_ON ) || ( IDSM_CFG_USE_FIL_TRAFFICLMT == STD_ON )) */

#define IDSM_STOP_SEC_CODE
#include <IdsM_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version    :Date                                                        */
/*  v2-0-0     :2022/11/30                                                  */
/*  v2-0-1     :2023/02/24                                                  */
/*  v2-0-2     :2023/04/10                                                  */
/****************************************************************************/

/**** End of File ***********************************************************/
