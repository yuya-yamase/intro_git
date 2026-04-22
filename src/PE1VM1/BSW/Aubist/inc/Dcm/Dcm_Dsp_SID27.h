/* Dcm_Dsp_SID27_h(v5-6-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID27/HEADER                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_DSP_SID27_H
#define DCM_DSP_SID27_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../../Dcm/Dsp/cfg/Dcm_Dsp_SID27_Cfg.h"
#include <Dcm.h>
#if ( DCM_SUPPORT_SID27 == STD_ON )


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

FUNC( void, DCM_CODE ) Dcm_Dsp_SID27_Init
(
    void
);
FUNC( void, DCM_CODE ) Dcm_Dsp_SID27_Refresh
(
    void
);
FUNC( void, DCM_CODE ) Dcm_Dsp_SID27_GetSeedCbk
(
    const uint8 u1EventId
);
FUNC( void, DCM_CODE ) Dcm_Dsp_SID27_CompareKeyCbk
(
    const uint8 u1EventId
);
#if ( DCM_SEC_PECULIAR_TYPE_RED == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsp_SID27_ReadConfCbk
(
    const uint8 u1EventId
);
#endif /* DCM_SEC_PECULIAR_TYPE_RED == STD_ON */
#if ( ( DCM_SEC_PECULIAR_TYPE_WHITE == STD_ON ) || ( DCM_SEC_PECULIAR_TYPE_RED == STD_ON ) || ( DCM_SEC_PECULIAR_TYPE_BLUE == STD_ON ) || ( DCM_SEC_PECULIAR_TYPE_GREEN == STD_ON ) )
FUNC( void, DCM_CODE ) Dcm_Dsp_SID27_DelayTimerCbk
(
    const uint8 u1TimerId
);
#endif /* DCM_SEC_PECULIAR_TYPE_WHITE == STD_ON || DCM_SEC_PECULIAR_TYPE_RED == STD_ON || DCM_SEC_PECULIAR_TYPE_BLUE == STD_ON || DCM_SEC_PECULIAR_TYPE_BLUE == STD_ON */
FUNC( void, DCM_CODE ) Dcm_Dsp_SID27_ClearReqSt
(
    const Dcm_NegativeResponseCodeType u1ErrorCode
);
FUNC(void, DCM_CODE) Dcm_Dsp_SID27_ClearSeed
(
    const Dcm_SesCtrlType u1SesCtrlTypeOld,
    const Dcm_SesCtrlType u1SesCtrlTypeNew
);
#if ( DCM_SEC_PECULIAR_TYPE_GREEN == STD_ON )
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID27_GetSecDelayTimerFactor
(
    const Dcm_SecLevelType u1SecLevel,
    P2VAR( boolean, AUTOMATIC, DCM_APPL_DATA ) ptDelayTimerActive,
    P2VAR( Dcm_DelayTimerFactorType, AUTOMATIC, DCM_APPL_DATA ) ptDelayTimerFactor
);
#endif /* DCM_SEC_PECULIAR_TYPE_GREEN == STD_ON */
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID27_RequestSeed
(
    const uint8 u1SubFncId,
    const Dcm_OpStatusType u1OpStatus,
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
);
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID27_SendKey
(
    const uint8 u1SubFncId,
    const Dcm_OpStatusType u1OpStatus,
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
);
#if ( ( DCM_SEC_PECULIAR_TYPE_WHITE == STD_ON ) || ( DCM_SEC_PECULIAR_TYPE_RED == STD_ON ) || ( DCM_SEC_PECULIAR_TYPE_BLUE == STD_ON ) )
/* for NvM */
FUNC( void, DCM_CODE) Dcm_Dsp_SID27_SetDataStorage2Mirror
(
    const uint16 u2BlockIdx
);
FUNC( void, DCM_CODE) Dcm_Dsp_SID27_SetDataMirror2Storage
(
    const uint16 u2BlockIdx
);
FUNC( void, DCM_CODE) Dcm_Dsp_SID27_ReadConfirmation
(
    const uint16 u2BlockIdx,
    const uint8  u1Result
);
#endif /* DCM_SEC_PECULIAR_TYPE_WHITE == STD_ON || DCM_SEC_PECULIAR_TYPE_RED == STD_ON || DCM_SEC_PECULIAR_TYPE_BLUE == STD_ON */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

#define DCM_STOP_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST
#include <Dcm_MemMap.h>

#define DCM_STOP_SEC_CONST
#include <Dcm_MemMap.h>

#endif /* DCM_SUPPORT_SID27 == STD_ON */
#endif /* DCM_DSP_SID27_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-6-0         :2024-02-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/


