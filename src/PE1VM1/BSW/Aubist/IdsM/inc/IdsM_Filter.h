/* IdsM_Filter_h_v2-0-2                                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name | IdsM/Filter/HEADER                                         */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/

#ifndef IDSM_FILTER_H
#define IDSM_FILTER_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <IdsM_Filters_Types.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#if ( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON )
#define IDSM_FILTERS_CTX_USE_FIRST  ((uint8)0U)
#define IDSM_FILTERS_CTX_USE_LAST   ((uint8)1U)
#endif /* ( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON ) */

#define IDSM_FILTER_RES_DEST    ((IdsM_FilterResultType)0x00U)
#define IDSM_FILTER_RES_ADOPT   ((IdsM_FilterResultType)0x01U)
/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define IDSM_START_SEC_CODE
#include <IdsM_MemMap.h>

FUNC(void, IDSM_CODE) IdsM_Filter_Init
(
    void
);
#if ( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON )
FUNC(void, IDSM_CODE) IdsM_Filter_GetAggreTmpData 
(
    VAR(uint16, AUTOMATIC) u2Index,
    P2VAR(IdsMAggreFilTmpType, AUTOMATIC, AUTOMATIC) ptData
);
#endif /* ( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON ) */

FUNC(void, IDSM_CODE) IdsM_Filter_UpdateCount
(
    void
);

FUNC(void, IDSM_CODE) IdsM_Filter_MainProcess
(
    VAR(uint16, AUTOMATIC) u2Index,
    P2CONST(IdsMEventBuffType, AUTOMATIC, AUTOMATIC) ptData,
    VAR(uint8, AUTOMATIC) u1FilChainStIndex
);

FUNC(IdsM_Filters_ReportingModeType, IDSM_CODE) IdsM_Filter_ReportingMode
(
    VAR(uint16, AUTOMATIC) u2Index
);

#if ( IDSM_CFG_USE_FIL_BLKSTATE == STD_ON )
FUNC(void, IDSM_CODE) IdsM_Filter_SetBlockState
(
    VAR(IdsM_Filters_BlockStateType, AUTOMATIC) udBlockState
);

FUNC(IdsM_FilterResultType, IDSM_CODE) IdsM_Filter_BlockState
(
    P2CONST(IdsMFilterFuncParamType, AUTOMATIC,IDSM_APPL_CONST) ptFilFuncParam,
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) ptTableIndex,
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) ptRecordIndex
);

FUNC(void, IDSM_CODE) IdsM_Filter_BlockStateCpy
(
    void
);
#endif /* ( IDSM_CFG_USE_FIL_BLKSTATE == STD_ON ) */
#if ( IDSM_CFG_USE_FIL_NTH == STD_ON )
FUNC(IdsM_FilterResultType, IDSM_CODE) IdsM_Filter_ForwardEveryNth
(
    P2CONST(IdsMFilterFuncParamType, AUTOMATIC,IDSM_APPL_CONST) ptFilFuncParam,
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) ptTableIndex,
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) ptRecordIndex
);
#endif /* ( IDSM_CFG_USE_FIL_NTH == STD_ON ) */
#if ( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON )
FUNC(IdsM_FilterResultType, IDSM_CODE) IdsM_Filter_AggreSetBuff 
(
    P2CONST(IdsMFilterFuncParamType, AUTOMATIC,IDSM_APPL_CONST) ptFilFuncParam,
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) ptTableIndex,
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) ptRecordIndex
);

FUNC(Std_ReturnType, IDSM_CODE) IdsM_Filter_AggreCheckPeriod
(
    VAR(uint16, AUTOMATIC) u2Index
);

FUNC(void, IDSM_CODE) IdsM_Filter_AggreClearBuff 
(
    VAR(uint16, AUTOMATIC) u2Index
);
#endif /* ( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON ) */
#if ( IDSM_CFG_USE_FIL_THRESHOLD == STD_ON )
FUNC(IdsM_FilterResultType, IDSM_CODE) IdsM_Filter_EventThreshold 
(
    P2CONST(IdsMFilterFuncParamType, AUTOMATIC,IDSM_APPL_CONST) ptFilFuncParam,
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) ptTableIndex,
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) ptRecordIndex
);

FUNC(void, IDSM_CODE) IdsM_Filter_ThresholdClearBuff 
(
    VAR(uint16, AUTOMATIC) u2Index
);
#endif /* ( IDSM_CFG_USE_FIL_THRESHOLD == STD_ON ) */
#if ( IDSM_CFG_USE_FIL_RATELMT == STD_ON )
FUNC(IdsM_FilterResultType, IDSM_CODE) IdsM_Filter_EventRateLimitation 
(
    P2CONST(IdsMFilterFuncParamType, AUTOMATIC,IDSM_APPL_CONST) ptFilFuncParam,
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) ptTableIndex,
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) ptRecordIndex
);

FUNC(void, IDSM_CODE) IdsM_Filter_EventRateClearNum
(
    void
);
#endif /* ( IDSM_CFG_USE_FIL_RATELMT == STD_ON ) */
#if ( IDSM_CFG_USE_FIL_TRAFFICLMT == STD_ON )
FUNC(IdsM_FilterResultType, IDSM_CODE) IdsM_Filter_TrafficLimitation 
(
    P2CONST(IdsMFilterFuncParamType, AUTOMATIC,IDSM_APPL_CONST) ptFilFuncParam,
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) ptTableIndex,
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) ptRecordIndex
);

FUNC(void, IDSM_CODE) IdsM_Filter_TrafficClearBytes
(
    void
);
#endif /* ( IDSM_CFG_USE_FIL_TRAFFICLMT == STD_ON ) */

#define IDSM_STOP_SEC_CODE
#include <IdsM_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* IDSM_FILTER_H */

/****************************************************************************/
/* History                                                                  */
/*  Version    :Date                                                        */
/*  v2-0-0     :2022/11/30                                                  */
/*  v2-0-1     :2023/02/24                                                  */
/*  v2-0-2     :2023/04/10                                                  */
/****************************************************************************/

/**** End of File ***********************************************************/
