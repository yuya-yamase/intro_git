/* Dcm_Dsp_SID86_c(v5-4-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID86/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_SID86.h>

#if ( DCM_SID86_ROE_USE == STD_ON )
#include "../../Dsp/usr/Dcm_Dsp_SID86_Connector.h"
#include "../../Dsp/cfg/Dcm_Dsp_SID86_Cfg.h"
#include "../../Dsp/inc/Dcm_Dsp_MsgMaker.h"
#if ( DCM_DSP_SID86_NVM_USE == STD_ON )
#include <Dcm/Dcm_Dsp_StorageMng.h>
#endif /* DCM_DSP_SID86_NVM_USE == STD_ON */
#include <Dcm/Dcm_Main_Common.h>
#include <Dcm/Dcm_Main_EvtDistr.h>
#include <Dcm/Dcm_Main_TmrSrv.h>
#include <Dcm/Dcm_Dsp_DidMng.h>
#include <Dcm/Dcm_Dsp_Main.h>
#include <Dcm/Dcm_Dsl_Ctrl.h>
#include <Dcm/Dcm_Dsd_SendMng.h>
#include "../../Dsd/inc/Dcm_Dsd_ServiceMng.h"
#endif /* DCM_SID86_ROE_USE == STD_ON */

#include <Rte_Dem_Type.h>
#include <Dcm_Dem.h>
#if ( DCM_SID86_ROE_USE == STD_ON )
#if ( DCM_DSP_SID86_NVM_USE == STD_ON )
#include <Dcm_NvM.h>
#endif /* DCM_DSP_SID86_NVM_USE == STD_ON */
#endif /* DCM_SID86_ROE_USE == STD_ON */

#include <Dem_Dcm.h>
#if ( DCM_SID86_ROE_USE == STD_ON )
#include <SchM_Dcm.h>
#endif /* DCM_SID86_ROE_USE == STD_ON */

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#if ( DCM_SID86_ROE_USE == STD_ON )

#define DCM_DSP_SID86_SF00 ( (uint8)0x00U )
#define DCM_DSP_SID86_SF01 ( (uint8)0x01U )
#define DCM_DSP_SID86_SF03 ( (uint8)0x03U )
#define DCM_DSP_SID86_SF05 ( (uint8)0x05U )
#define DCM_DSP_SID86_SF06 ( (uint8)0x06U )
#define DCM_DSP_SID86_SF07 ( (uint8)0x07U )
#define DCM_DSP_SID86_SF45 ( (uint8)0x45U )

#define DCM_DSP_SID86_SF00_IDX ( (uint8)0U )
#define DCM_DSP_SID86_SF01_IDX ( (uint8)1U )
#define DCM_DSP_SID86_SF03_IDX ( (uint8)2U )
#define DCM_DSP_SID86_SF05_IDX ( (uint8)3U )
#define DCM_DSP_SID86_SF06_IDX ( (uint8)4U )
#define DCM_DSP_SID86_SF07_IDX ( (uint8)5U )
#define DCM_DSP_SID86_SF40_IDX ( (uint8)6U )
#define DCM_DSP_SID86_SF41_IDX ( (uint8)7U )
#define DCM_DSP_SID86_SF43_IDX ( (uint8)8U )
#define DCM_DSP_SID86_SF45_IDX ( (uint8)9U )
#define DCM_DSP_SID86_SF46_IDX ( (uint8)10U )
#define DCM_DSP_SID86_SF47_IDX ( (uint8)11U )
#define DCM_DSP_SID86_SF_FUNCTBL_NUM ( (uint8)12U )

#define DCM_DSP_SID86_SUBFUNC_MASK              (  (uint8)0x7FU )
#define DCM_DSP_SID86_EVENTWINDOWTIME_LEN       ( (uint32)0x01U )
#define DCM_DSP_SID86_DTCSTATUSMASK_LEN         ( (uint32)0x01U )
#define DCM_DSP_SID86_DID_LEN                   ( (uint32)0x02U )
#define DCM_DSP_SID86_SID_LEN                   ( (uint32)0x01U )
#define DCM_DSP_SID86_NUMBEROFID_LEN            ( (uint32)0x01U )
#define DCM_DSP_SID86_COMP_LOGIC_LEN            ( (uint32)0x01U )
#define DCM_DSP_SID86_COMP_VALUE_LEN            ( (uint32)0x04U )
#define DCM_DSP_SID86_HYST_LEN                  ( (uint32)0x01U )
#define DCM_DSP_SID86_LOCAL_LEN                 ( (uint32)0x02U )
#define DCM_DSP_SID86_SF01_EVENTTYPE_LEN        ( DCM_DSP_SID86_DTCSTATUSMASK_LEN )
#define DCM_DSP_SID86_SF03_EVENTTYPE_LEN        ( DCM_DSP_SID86_DID_LEN )
#define DCM_DSP_SID86_SF05_EVENTTYPE_LEN        ( (uint32)0x00U )
#define DCM_DSP_SID86_SF07_EVENTTYPE_LEN        ( DCM_DSP_SID86_DID_LEN + DCM_DSP_SID86_COMP_LOGIC_LEN + DCM_DSP_SID86_COMP_VALUE_LEN + DCM_DSP_SID86_HYST_LEN + DCM_DSP_SID86_LOCAL_LEN )
#define DCM_DSP_SID86_SF45_EVENTTYPE_LEN        ( (uint32)0x00U )

/* Minimum Request Length per SubFunction  */
#define DCM_DSP_SID86_SF00_REQ_LEN              ( DCM_DSP_SID86_EVENTWINDOWTIME_LEN )
#define DCM_DSP_SID86_SF01_REQ_MIN_LEN          ( (uint32)( DCM_DSP_SID86_EVENTWINDOWTIME_LEN + DCM_DSP_SID86_DTCSTATUSMASK_LEN + DCM_DSP_SID86_SID_LEN ) )
#define DCM_DSP_SID86_SF03_REQ_MIN_LEN          ( (uint32)( DCM_DSP_SID86_EVENTWINDOWTIME_LEN + DCM_DSP_SID86_DID_LEN + DCM_DSP_SID86_SID_LEN ) )
#define DCM_DSP_SID86_SF05_REQ_LEN              ( DCM_DSP_SID86_EVENTWINDOWTIME_LEN )
#define DCM_DSP_SID86_SF06_REQ_LEN              ( DCM_DSP_SID86_EVENTWINDOWTIME_LEN )
#define DCM_DSP_SID86_SF07_REQ_MIN_LEN          ( (uint32)( DCM_DSP_SID86_EVENTWINDOWTIME_LEN + DCM_DSP_SID86_SF07_EVENTTYPE_LEN + DCM_DSP_SID86_SID_LEN ) )

#define DCM_DSP_SID86_SF40_REQ_LEN              ( DCM_DSP_SID86_EVENTWINDOWTIME_LEN )
#define DCM_DSP_SID86_SF41_REQ_MIN_LEN          ( (uint32)( DCM_DSP_SID86_EVENTWINDOWTIME_LEN + DCM_DSP_SID86_DTCSTATUSMASK_LEN + DCM_DSP_SID86_SID_LEN ) )
#define DCM_DSP_SID86_SF43_REQ_MIN_LEN          ( (uint32)( DCM_DSP_SID86_EVENTWINDOWTIME_LEN + DCM_DSP_SID86_DID_LEN + DCM_DSP_SID86_SID_LEN ) )
#define DCM_DSP_SID86_SF45_REQ_LEN              ( DCM_DSP_SID86_EVENTWINDOWTIME_LEN )
#define DCM_DSP_SID86_SF46_REQ_LEN              ( DCM_DSP_SID86_EVENTWINDOWTIME_LEN )
#define DCM_DSP_SID86_SF47_REQ_MIN_LEN          ( (uint32)( DCM_DSP_SID86_EVENTWINDOWTIME_LEN + DCM_DSP_SID86_SF07_EVENTTYPE_LEN + DCM_DSP_SID86_SID_LEN ) )

/* Offset of Parameter */
#define DCM_DSP_SID86_EVENTWINDOWTIME_OFFSET    ( (uint32)0x00U )
#define DCM_DSP_SID86_DTCSTATUSMASK_OFFSET      ( (uint32)( DCM_DSP_SID86_EVENTWINDOWTIME_OFFSET + DCM_DSP_SID86_EVENTWINDOWTIME_LEN ) )
#define DCM_DSP_SID86_SF01_SID_OFFSET           ( (uint32)( DCM_DSP_SID86_DTCSTATUSMASK_OFFSET + DCM_DSP_SID86_DTCSTATUSMASK_LEN ) )
#define DCM_DSP_SID86_SF03_DID_OFFSET           ( (uint32)( DCM_DSP_SID86_EVENTWINDOWTIME_OFFSET + DCM_DSP_SID86_EVENTWINDOWTIME_LEN ) )
#define DCM_DSP_SID86_SF03_SID_OFFSET           ( (uint32)( DCM_DSP_SID86_SF03_DID_OFFSET + DCM_DSP_SID86_DID_LEN ) )
#define DCM_DSP_SID86_SF07_DID_OFFSET           ( (uint32)( DCM_DSP_SID86_EVENTWINDOWTIME_OFFSET + DCM_DSP_SID86_EVENTWINDOWTIME_LEN ) )
#define DCM_DSP_SID86_SF07_COMP_LOGIC_OFFSET    ( (uint32)( DCM_DSP_SID86_SF07_DID_OFFSET + DCM_DSP_SID86_DID_LEN ) )
#define DCM_DSP_SID86_SF07_COMP_VALUE_OFFSET    ( (uint32)( DCM_DSP_SID86_SF07_COMP_LOGIC_OFFSET + DCM_DSP_SID86_COMP_LOGIC_LEN ) )
#define DCM_DSP_SID86_SF07_HYST_OFFSET          ( (uint32)( DCM_DSP_SID86_SF07_COMP_VALUE_OFFSET + DCM_DSP_SID86_COMP_VALUE_LEN ) )
#define DCM_DSP_SID86_SF07_LOCAL_OFFSET         ( (uint32)( DCM_DSP_SID86_SF07_HYST_OFFSET + DCM_DSP_SID86_HYST_LEN ) )
#define DCM_DSP_SID86_SF07_SID_OFFSET           ( (uint32)( DCM_DSP_SID86_SF07_LOCAL_OFFSET + DCM_DSP_SID86_LOCAL_LEN ) )
#define DCM_DSP_SID86_COMP_DID_OFFSET           ( (uint32)0x00U )
#define DCM_DSP_SID86_COMP_LOGIC_OFFSET         ( (uint32)( DCM_DSP_SID86_COMP_DID_OFFSET + DCM_DSP_SID86_DID_LEN ) )
#define DCM_DSP_SID86_COMP_VALUE_OFFSET         ( (uint32)( DCM_DSP_SID86_COMP_LOGIC_OFFSET + DCM_DSP_SID86_COMP_LOGIC_LEN ) )
#define DCM_DSP_SID86_COMP_HYST_OFFSET          ( (uint32)( DCM_DSP_SID86_COMP_VALUE_OFFSET + DCM_DSP_SID86_COMP_VALUE_LEN ) )
#define DCM_DSP_SID86_COMP_LOCAL_OFFSET         ( (uint32)( DCM_DSP_SID86_COMP_HYST_OFFSET + DCM_DSP_SID86_HYST_LEN ) )
/* Offset of Saved Data */
#define DCM_DSP_SID86_ETR_OFFSET_DTC                    ( (uint8)0U )
#define DCM_DSP_SID86_ETR_OFFSET_DID_HIGH               ( (uint8)0U )
#define DCM_DSP_SID86_ETR_OFFSET_DID_LOW                ( (uint8)1U )
#if ( DCM_DSP_SID86_NVM_USE == STD_ON )
#define DCM_DSP_SID86_STRTR_OFFSET_SID                  ( (uint8)0U )
#endif /* DCM_DSP_SID86_NVM_USE == STD_ON */
/* */
#define DCM_DSP_SID86_ROE_EVENTID_MIN                   ( (uint8)0x00U )
#define DCM_DSP_SID86_ROE_EVENTID_INVALID               ( (uint8)0xFFU )
/* Roe Event Status */
#define DCM_DSP_SID86_ROE_STS_CLEAR                     ( (uint8)1U )
#define DCM_DSP_SID86_ROE_STS_STOP                      ( (uint8)2U )
#define DCM_DSP_SID86_ROE_STS_START                     ( (uint8)3U )
#define DCM_DSP_SID86_ROE_STS_START_EVENT               ( (uint8)4U )
/* ReqType for Send Message */
#define DCM_DSP_SID86_REQ_PHYSICAL                      ( (uint8)0x00U )
/* Queue Over Intermediate Message */
#define DCM_DSP_SID86_POSRES_SID                        ( (uint8)0xC6U )
#define DCM_DSP_SID86_QOM_EVTYPE                        ( (uint8)0x01U )
#define DCM_DSP_SID86_QOM_NUMIDEV                       ( (uint8)0xFFU )
#define DCM_DSP_SID86_SID                               ( (uint8)0x86U )
#define DCM_DSP_SID86_POSRES_SID_LEN                    ( (uint8)0x01U )
#define DCM_DSP_SID86_QOM_EVTYPE_LEN                    ( (uint8)0x01U )
#define DCM_DSP_SID86_QOM_NUMIDEV_LEN                   ( (uint8)0x01U )
#define DCM_DSP_SID86_QOM_EVWINTIM_LEN                  ( (uint8)0x01U )
#define DCM_DSP_SID86_QOM_EVTYPREC_LEN                  ( (uint8)0x01U )
#define DCM_DSP_SID86_MES_OFFSET_00                     ( (uint8)0x00U )
#define DCM_DSP_SID86_MES_OFFSET_01                     ( (uint8)0x01U )
#define DCM_DSP_SID86_MES_OFFSET_02                     ( (uint8)0x02U )
#define DCM_DSP_SID86_MES_OFFSET_03                     ( (uint8)0x03U )
#define DCM_DSP_SID86_MES_OFFSET_04                     ( (uint8)0x04U )
#define DCM_DSP_SID86_MES_OFFSET_05                     ( (uint8)0x05U )
/* Check SID Support and POS Suppress */
#define DCM_DSP_SID86_CHK_SID_OFFSET                    ( (uint8)0x00U )
#define DCM_DSP_SID86_CHK_SUBFUNC_OFFSET                ( (uint8)0x01U )
#define DCM_DSP_SID86_CHK_SID22_SID                     ( (uint8)0x22U )
#define DCM_DSP_SID86_CHK_SID19_SID                     ( (uint8)0x19U )
#define DCM_DSP_SID86_CHK_SID19_SF0E                    ( (uint8)0x0EU )
#define DCM_DSP_SID86_POS_SUP_MASK                      ( (uint8)0x80U )

#define DCM_DSP_SID86_CONID_INVALID                     ( (uint16)0xFFFFU )
#define DCM_DSP_SID86_SUBFUNC_INVALID                   ( (uint8)0xFFU )
#define DCM_DSP_SID86_EVWIN_INVALID                     ( (uint8)0x00U )

#define DCM_DSP_SID86_SHIFT_BYTESIZE                    ( (uint8)8U )

#define DCM_DSP_SID86_LIST_START_POS                    ((uint8)0U)
#define DCM_DSP_SID86_LIST_START_CNT                    ((uint8)1U)
#define DCM_DSP_SID86_CONNID_LIST_NUM                   ((uint8)30U)

#define DCM_DSP_SID86_DTCEVENT_EXIST                    ((uint8)1U)

#endif /* DCM_SID86_ROE_USE == STD_ON */
/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
#if ( DCM_SID86_ROE_USE == STD_ON )

/* Structure to Roe */
typedef struct {
    uint16  u2ConnectionId;                                         /* ConnectionId                     */
    uint8   u1ServiceToRespondToRecord[DCM_DSP_SID86_SERVICETORESPONDTORECORD_MAX];
                                                                    /* ServiceToRespondToRecord         */
    uint8   u1EventTypeRecord[DCM_DSP_SID86_EVENTTYPERECORD_MAX];   /* EventTypeRecord                  */
    uint8   u1NumberOfIdentifiedEvents;                             /* NumberOfIdentifiedEvents         */
    uint8   u1Status;                                               /* Event Status                     */
    uint8   u1EventWindow;                                          /* Event Window Time                */
    uint8   u1ServiceToRespondToRecordLength;                       /* ServiceToRespondToRecordLength   */
    uint8   u1RcvSubFunc;                                           /* Sub Function                     */
    boolean bRoeStart;                                              /* Initial RoeRestart               */
    boolean bDefaultSesReactive;                                    /* DefaultSessionReactive           */
} Dcm_Dsp_SID86_EventLogicType;

typedef P2FUNC( Std_ReturnType, DCM_CODE, Dcm_Dsp_SID86_SF_Type )
(
    P2CONST( Dcm_MsgContextType, TYPEDEF, DCM_APPL_DATA ) ptMsgContext
);
















#endif /* DCM_SID86_ROE_USE == STD_ON */
/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>
#if ( DCM_SID86_ROE_USE == STD_ON )

/* */
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_Init_MsgContext
(
    void
);
/* */
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_Init_RoeEventTable
(
    void
);
/* */
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_InitElemOfRoeEventTable
(
    const   uint8                               u1RoeEventId
);
/* */
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_CheckServSupport
(
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA )  ptServToResp,
    const   uint32                              u4ServToRespToRecLen,
    const   PduIdType                           u2PduId
);
/* */
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_RegEvent_Sub01
(
    const   uint8                                           u1RoeEventId,
    const   uint16                                          u2ConnectionId,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);
/* */
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_RegEvent_Sub03
(
    const   uint8                                           u1RoeEventId,
    const   uint16                                          u2ConnectionId,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);
/* */
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_RegEvent_Sub07
(
    const   uint8                                           u1RoeEventId,
    const   uint16                                          u2ConnectionId,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);
/* */
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_StartAllEvents
(
    const   uint8                                                   u1SubFunc,
    const   uint16                                                  u2ConnectionId
);
/* */
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_ClearAllEvents
(
    void
);
/* */
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_ClearEvent
(
    const   uint8       u1RoeEventId
);
/* */
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_SendServToRespTo
(
    const   uint8       u1TargetRoeEventId
);
/* */
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_SetNextTriggerEvent
(
    void
);
/* */
static FUNC( uint8, DCM_CODE ) Dcm_Dsp_SID86_GetNextRoeEventId
(
    const   uint8       u1StartRoeEventId
);
/* */
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_StopAllEvents
(
    void
);
/* */
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_StopAllEventsSes
(
    const   boolean     bDefaultSesReAct
);
/* */
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_StopEvent
(
    const   uint8       u1RoeEventId
);
/* */
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_StopEventSes
(
    const   uint8       u1RoeEventId,
    const   boolean     bDefaultSesReAct
);
/* */
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_ReStartAllEvents
(
    void
);
/* */
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_StartEvent
(
    const   uint8       u1RoeEventId,
    const   boolean     bDefaultSesReactive,
    const   boolean     bRoeStart
);
/* */
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_StartEventSes
(
    const   uint8       u1RoeEventId
);
/* */
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub00_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);
#if ( DCM_DSP_SID86_NVM_USE == STD_ON )
/* */
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub00_CheckCondition
(
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
);
#endif /* DCM_DSP_SID86_NVM_USE == STD_ON */
/* */
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub40_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);
/* */
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub01_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);
/* */
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub01_CheckCondition
(
    const uint16                                                    u2ConnectionId,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA )         ptMsgContext,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA )                        ptRoeEventId,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
);
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub41_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);
/* */
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub03_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);
/* */
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub03_CheckCondition
(
    const   uint16                                                  u2ConnectionId,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA )         ptMsgContext,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA )                        ptRoeEventId,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
);
/* */
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub03_Check_RegCondition
(
    const   uint8                                                   u1RoeEventId,
    const   uint16                                                  u2ConnectionId,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
);
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub43_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);
/* */
static FUNC( uint16, DCM_CODE ) Dcm_Dsp_SID86_GetDid
(
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA )  ptDid
);
/* */
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub05_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);
/* */
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub05_CheckCondition
(
    const   uint16                                                  u2ConnectionId,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA )         ptMsgContext,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
);
/* */
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub45_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);
/* */
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub45_CheckCondition
(
    const   uint16                                                  u2ConnectionId,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA )         ptMsgContext,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
);
/* */
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub06_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);
/* */
#if ( DCM_DSP_SID86_NVM_USE == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub06_CheckCondition
(
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
);
#endif /* DCM_DSP_SID86_NVM_USE == STD_ON */
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub46_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);
/* */
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub07_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);
/* */
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub07_CheckCondition
(
    const   uint16                                                  u2ConnectionId,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA )         ptMsgContext,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA )                        ptRoeEventId,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
);
/* */
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub07_Check_RegCondition
(
    const   uint8                                                   u1RoeEventId,
    const   uint16                                                  u2ConnectionId,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
);
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub47_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);
/* */
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_CancelProc_OnlySetIdleFlag
(
    void
);
/* */
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_EditPosRes
(
    const uint8                                             u1SubFunc,
    P2VAR( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA )  ptMsgContext
);
/* */
static FUNC( uint8, DCM_CODE ) Dcm_Dsp_SID86_GetEventIdByDid
(
    const uint16                                            u2Did
);
/* */
static FUNC( boolean, DCM_CODE ) Dcm_Dsp_SID86_CheckStartEvent
(
    void
);
/* */
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_EditComparisonData
(
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA )              ptEventTypeRecord,
    P2VAR( Dcm_ComparisonValueType, AUTOMATIC, AUTOMATIC )  ptComparisonValue
);
/* */
static FUNC( uint8, DCM_CODE ) Dcm_Dsp_SID86_GenerateReceivedSubFunc
(
    const uint8                                            u1SubFunc,
    const uint8                                            u1SuppressPRM
);
/* */
#if ( DCM_DSP_SID86_NVM_USE == STD_ON )
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_Init_Storage
(
    void
);
#endif /* DCM_DSP_SID86_NVM_USE == STD_ON */
/* */
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_WriteStorage
(
    const uint8     u1RoeEventId
);
#if ( DCM_DSP_SID86_NVM_USE == STD_ON )
/* */
static FUNC( boolean, DCM_CODE ) Dcm_Dsp_SID86_GetReadStorageCompleteFlag
(
    void
);
/* */
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_SetErrorRoeEvent
(
    const uint8     u1RoeEventId
);
/* */
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_CheckEventTableData
(
    const uint8     u1RoeEventId
);
/* */
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_ClearElemOfRoeEventTable
(
    const uint8     u1RoeEventId
);
/* */
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_UpdateEventTableData
(
    const uint8     u1RoeEventId
);
#endif /* DCM_DSP_SID86_NVM_USE == STD_ON */

static FUNC( boolean, DCM_CODE ) Dcm_Dsp_SID86_IsUsedConnection
(
    const uint16        u2ConnectionId
);
/* */
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_MakeConnectionIdList
(
    const uint16                                u2ConnId,
    P2VAR( uint8,  AUTOMATIC, DCM_APPL_DATA )   ptListNum,
    P2VAR( uint16, AUTOMATIC, DCM_APPL_DATA )   ptConnIdList
);
/* */
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_MakeActConnectionIdList
(
    P2VAR( uint8,  AUTOMATIC, DCM_APPL_DATA )   ptListNum,
    P2VAR( uint16, AUTOMATIC, DCM_APPL_DATA )   ptConnIdList
);
/* */
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_SetComActive
(
    const uint8                                 u1ListNum,
    P2CONST( uint16, AUTOMATIC, DCM_APPL_DATA ) ptConnIdList,
    const boolean                               bActive
);

#endif /* DCM_SID86_ROE_USE == STD_ON */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

#if ( DCM_SID86_ROE_USE == STD_ON )

static VAR( Dcm_MsgContextType, DCM_VAR_NO_INIT ) Dcm_Dsp_SID86_stMsgContext;
static VAR( Dcm_Dsp_SID86_EventLogicType, DCM_VAR_NO_INIT )  Dcm_Dsp_SID86_stEventLogic[DCM_DSP_SID86_ROE_EVENT_NUM];
static VAR( uint16, DCM_VAR_NO_INIT )           Dcm_Dsp_SID86_u2ConnectionIdMirror[DCM_DSP_SID86_ROE_EVENT_NUM];
static VAR( uint16, DCM_VAR_NO_INIT )           Dcm_Dsp_SID86_u2StartRequestConnectionId;
static VAR( uint8,  DCM_VAR_NO_INIT )           Dcm_Dsp_SID86_u1ExecEventId;
static VAR( uint8,  DCM_VAR_NO_INIT )           Dcm_Dsp_SID86_u1NumChangeOfDataIdentfierEvents;
static VAR( uint8,  DCM_VAR_NO_INIT )           Dcm_Dsp_SID86_u1NumComparisionOfValueEvents;
static VAR( uint8,  DCM_VAR_NO_INIT )           Dcm_Dsp_SID86_u1NumberOfStoredDTCStatusChangedEvents;
static VAR( boolean, DCM_VAR_NO_INIT )          Dcm_Dsp_SID86_bProcessingIntermediateResponse;
static VAR( boolean, DCM_VAR_NO_INIT )          Dcm_Dsp_SID86_bWaitingForTransmission;

#if ( DCM_DSP_SID86_NVM_USE == STD_ON )
static VAR( boolean, DCM_VAR_NO_INIT )          Dcm_Dsp_SID86_bReadStorageCompleteFlag;
#endif /* DCM_DSP_SID86_NVM_USE == STD_ON */

#endif /* DCM_SID86_ROE_USE == STD_ON */

#define DCM_STOP_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

#define DCM_START_SEC_VAR_SAVED_ZONE
#include <Dcm_MemMap.h>

#if ( DCM_SID86_ROE_USE == STD_ON )
#if ( DCM_DSP_SID86_NVM_USE == STD_ON )

VAR( Dcm_Dsp_SID86_StorageEventLogicType, DCM_VAR_SAVED_ZONE )  Dcm_Dsp_SID86_stStorageEventLogic[DCM_DSP_SID86_ROE_BLOCKIDX_NUM];

#endif /* DCM_DSP_SID86_NVM_USE == STD_ON */
#endif /* DCM_SID86_ROE_USE == STD_ON */

#define DCM_STOP_SEC_VAR_SAVED_ZONE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST
#include <Dcm_MemMap.h>

#if ( DCM_SID86_ROE_USE == STD_ON )
static CONST(AB_83_ConstV Dcm_Dsp_SID86_SF_Type, DCM_CONST) Dcm_Dsp_SID86_SF_FuncTbl[ DCM_DSP_SID86_SF_FUNCTBL_NUM ] =
{
    &(Dcm_Dsp_SID86_Sub00_InitialProc),
    &(Dcm_Dsp_SID86_Sub01_InitialProc),
    &(Dcm_Dsp_SID86_Sub03_InitialProc),
    &(Dcm_Dsp_SID86_Sub05_InitialProc),
    &(Dcm_Dsp_SID86_Sub06_InitialProc),
    &(Dcm_Dsp_SID86_Sub07_InitialProc),
    &(Dcm_Dsp_SID86_Sub40_InitialProc),
    &(Dcm_Dsp_SID86_Sub41_InitialProc),
    &(Dcm_Dsp_SID86_Sub43_InitialProc),
    &(Dcm_Dsp_SID86_Sub45_InitialProc),
    &(Dcm_Dsp_SID86_Sub46_InitialProc),
    &(Dcm_Dsp_SID86_Sub47_InitialProc)

};
#endif /* DCM_SID86_ROE_USE == STD_ON */

#define DCM_STOP_SEC_CONST
#include <Dcm_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

#if ( DCM_SID86_ROE_USE == STD_ON )


#if ( DCM_SUPPORT_SID86_SUB00 == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_SID86_Sub00                                          */
/* Description   | Request processing of SID 86                             */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus       : Operation state                    */
/*               | [IN] pMsgContext    : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID86_Sub00    /* MISRA DEVIATION */
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
#ifndef JGXSTACK
        u1_RetVal = Dcm_Dsp_SID86_SF_FuncTbl[DCM_DSP_SID86_SF00_IDX]( pMsgContext );
#else  /* JGXSTACK */
        u1_RetVal = Dcm_Dsp_SID86_Sub00_InitialProc( pMsgContext );
#endif /* JGXSTACK */
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_CANCEL )
    {
        u1_RetVal = Dcm_Dsp_SID86_CancelProc_OnlySetIdleFlag();
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID86_SUB00 == STD_ON */

#if ( DCM_SUPPORT_SID86_SUB01 == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_SID86_Sub01                                          */
/* Description   | Request processing of SID 86                             */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus       : Operation state                    */
/*               | [IN] pMsgContext    : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID86_Sub01    /* MISRA DEVIATION */
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
#ifndef JGXSTACK
        u1_RetVal = Dcm_Dsp_SID86_SF_FuncTbl[DCM_DSP_SID86_SF01_IDX]( pMsgContext );
#else  /* JGXSTACK */
        u1_RetVal = Dcm_Dsp_SID86_Sub01_InitialProc( pMsgContext );
#endif /* JGXSTACK */
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_CANCEL )
    {
        u1_RetVal = Dcm_Dsp_SID86_CancelProc_OnlySetIdleFlag();
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID86_SUB01 == STD_ON */

#if ( DCM_SUPPORT_SID86_SUB03 == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_SID86_Sub03                                          */
/* Description   | Request processing of SID 86                             */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus       : Operation state                    */
/*               | [IN] pMsgContext    : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID86_Sub03    /* MISRA DEVIATION */
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
#ifndef JGXSTACK
        u1_RetVal = Dcm_Dsp_SID86_SF_FuncTbl[DCM_DSP_SID86_SF03_IDX]( pMsgContext );
#else  /* JGXSTACK */
        u1_RetVal = Dcm_Dsp_SID86_Sub03_InitialProc( pMsgContext );
#endif /* JGXSTACK */
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_CANCEL )
    {
        u1_RetVal = Dcm_Dsp_SID86_CancelProc_OnlySetIdleFlag();
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID86_SUB03 == STD_ON */

#if ( DCM_SUPPORT_SID86_SUB05 == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_SID86_Sub05                                          */
/* Description   | Request processing of SID 86                             */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus       : Operation state                    */
/*               | [IN] pMsgContext    : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID86_Sub05    /* MISRA DEVIATION */
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
#ifndef JGXSTACK
        u1_RetVal = Dcm_Dsp_SID86_SF_FuncTbl[DCM_DSP_SID86_SF05_IDX]( pMsgContext );
#else  /* JGXSTACK */
        u1_RetVal = Dcm_Dsp_SID86_Sub05_InitialProc( pMsgContext );
#endif /* JGXSTACK */
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_CANCEL )
    {
        u1_RetVal = Dcm_Dsp_SID86_CancelProc_OnlySetIdleFlag();
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID86_SUB05 == STD_ON */

#if ( DCM_SUPPORT_SID86_SUB06 == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_SID86_Sub06                                          */
/* Description   | Request processing of SID 86                             */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus       : Operation state                    */
/*               | [IN] pMsgContext    : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID86_Sub06    /* MISRA DEVIATION */
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
#ifndef JGXSTACK
        u1_RetVal = Dcm_Dsp_SID86_SF_FuncTbl[DCM_DSP_SID86_SF06_IDX]( pMsgContext );
#else  /* JGXSTACK */
        u1_RetVal = Dcm_Dsp_SID86_Sub06_InitialProc( pMsgContext );
#endif /* JGXSTACK */
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_CANCEL )
    {
        u1_RetVal = Dcm_Dsp_SID86_CancelProc_OnlySetIdleFlag();
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID86_SUB06 == STD_ON */

#if ( DCM_SUPPORT_SID86_SUB07 == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_SID86_Sub07                                          */
/* Description   | Request processing of SID 86                             */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus       : Operation state                    */
/*               | [IN] pMsgContext    : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID86_Sub07    /* MISRA DEVIATION */
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
#ifndef JGXSTACK
        u1_RetVal = Dcm_Dsp_SID86_SF_FuncTbl[DCM_DSP_SID86_SF07_IDX]( pMsgContext );
#else  /* JGXSTACK */
        u1_RetVal = Dcm_Dsp_SID86_Sub07_InitialProc( pMsgContext );
#endif /* JGXSTACK */
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_CANCEL )
    {
        u1_RetVal = Dcm_Dsp_SID86_CancelProc_OnlySetIdleFlag();
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID86_SUB07 == STD_ON */

#if ( DCM_SUPPORT_SID86_SUB40 == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_SID86_Sub40                                          */
/* Description   | Request processing of SID 86                             */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus       : Operation state                    */
/*               | [IN] pMsgContext    : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID86_Sub40    /* MISRA DEVIATION */
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
#ifndef JGXSTACK
        u1_RetVal = Dcm_Dsp_SID86_SF_FuncTbl[DCM_DSP_SID86_SF40_IDX]( pMsgContext );
#else  /* JGXSTACK */
        u1_RetVal = Dcm_Dsp_SID86_Sub40_InitialProc( pMsgContext );
#endif /* JGXSTACK */
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_CANCEL )
    {
        u1_RetVal = Dcm_Dsp_SID86_CancelProc_OnlySetIdleFlag();
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID86_SUB40 == STD_ON */
#if ( DCM_SUPPORT_SID86_SUB41 == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_SID86_Sub41                                          */
/* Description   | Request processing of SID 86                             */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus       : Operation state                    */
/*               | [IN] pMsgContext    : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID86_Sub41
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
#ifndef JGXSTACK
        u1_RetVal = Dcm_Dsp_SID86_SF_FuncTbl[DCM_DSP_SID86_SF41_IDX]( pMsgContext );
#else  /* JGXSTACK */
        u1_RetVal = Dcm_Dsp_SID86_Sub41_InitialProc( pMsgContext );
#endif /* JGXSTACK */
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_CANCEL )
    {
        u1_RetVal = Dcm_Dsp_SID86_CancelProc_OnlySetIdleFlag();
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID86_SUB41 == STD_ON */
#if ( DCM_SUPPORT_SID86_SUB43 == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_SID86_Sub43                                          */
/* Description   | Request processing of SID 86                             */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus       : Operation state                    */
/*               | [IN] pMsgContext    : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID86_Sub43
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
#ifndef JGXSTACK
        u1_RetVal = Dcm_Dsp_SID86_SF_FuncTbl[DCM_DSP_SID86_SF43_IDX]( pMsgContext );
#else  /* JGXSTACK */
        u1_RetVal = Dcm_Dsp_SID86_Sub43_InitialProc( pMsgContext );
#endif /* JGXSTACK */
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_CANCEL )
    {
        u1_RetVal = Dcm_Dsp_SID86_CancelProc_OnlySetIdleFlag();
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID86_SUB43 == STD_ON */
#if ( DCM_SUPPORT_SID86_SUB45 == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_SID86_Sub45                                          */
/* Description   | Request processing of SID 86                             */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus       : Operation state                    */
/*               | [IN] pMsgContext    : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID86_Sub45
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
#ifndef JGXSTACK
        u1_RetVal = Dcm_Dsp_SID86_SF_FuncTbl[DCM_DSP_SID86_SF45_IDX]( pMsgContext );
#else  /* JGXSTACK */
        u1_RetVal = Dcm_Dsp_SID86_Sub45_InitialProc( pMsgContext );
#endif /* JGXSTACK */
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_CANCEL )
    {
        u1_RetVal = Dcm_Dsp_SID86_CancelProc_OnlySetIdleFlag();
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID86_SUB45 == STD_ON */
#if ( DCM_SUPPORT_SID86_SUB46 == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_SID86_Sub46                                          */
/* Description   | Request processing of SID 86                             */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus       : Operation state                    */
/*               | [IN] pMsgContext    : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID86_Sub46
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
#ifndef JGXSTACK
        u1_RetVal = Dcm_Dsp_SID86_SF_FuncTbl[DCM_DSP_SID86_SF46_IDX]( pMsgContext );
#else  /* JGXSTACK */
        u1_RetVal = Dcm_Dsp_SID86_Sub46_InitialProc( pMsgContext );
#endif /* JGXSTACK */
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_CANCEL )
    {
        u1_RetVal = Dcm_Dsp_SID86_CancelProc_OnlySetIdleFlag();
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID86_SUB46 == STD_ON */
#if ( DCM_SUPPORT_SID86_SUB47 == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_SID86_Sub47                                          */
/* Description   | Request processing of SID 86                             */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus       : Operation state                    */
/*               | [IN] pMsgContext    : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID86_Sub47
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
#ifndef JGXSTACK
        u1_RetVal = Dcm_Dsp_SID86_SF_FuncTbl[DCM_DSP_SID86_SF47_IDX]( pMsgContext );
#else  /* JGXSTACK */
        u1_RetVal = Dcm_Dsp_SID86_Sub47_InitialProc( pMsgContext );
#endif /* JGXSTACK */
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_CANCEL )
    {
        u1_RetVal = Dcm_Dsp_SID86_CancelProc_OnlySetIdleFlag();
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID86_SUB47 == STD_ON */
/****************************************************************************/
/* Function Name | Dcm_DemTriggerOnDTCStatus                                */
/* Description   | It is notified in DTC change opportunity                 */
/* Preconditions | None                                                     */
/* Parameters    | [IN] DTC             : This is the DTC the change        */
/*               |                         trigger is assigned to.          */
/*               | [IN] DTCStatusOld    : DTC state before change           */
/*               | [IN] DTCStatusNew    : DTC state after change            */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK               : Processing normal                 */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_DemTriggerOnDTCStatus   /* MISRA DEVIATION */
(
    uint32 DTC,                                         /* MISRA DEVIATION  */
    Dem_UdsStatusByteType DTCStatusOld,                 /* MISRA DEVIATION  */
    Dem_UdsStatusByteType DTCStatusNew                  /* MISRA DEVIATION  */
)
{
    Std_ReturnType              u1_RetVal;
    uint8                       u1_Status;
    uint8                       u1_DTCStsMask;
    uint8                       u1_DTCStsChgEvId;
    uint8                       u1_NewSettingBit;
    uint8                       u1_ExecEventId;
    uint8                       u1_CurEventNum;
    uint8                       u1_MaxEventNum;
    uint8                       u1_RcvSubFunc;
    boolean                     b_Monitoring;
    boolean                     b_ProcInterResp;
    boolean                     b_UseQueueForDTCEv;

    u1_RetVal                   = E_OK;
    b_Monitoring                = (boolean)FALSE;
    u1_DTCStsChgEvId            = Dcm_Dsp_SID86_u1DTCStatusChangedEventId;

    /* lock */
    SchM_Enter_Dcm_Dsp_Roe();

    if( u1_DTCStsChgEvId != DCM_DSP_SID86_ROE_EVENTID_INVALID )
    {
        u1_Status               = Dcm_Dsp_SID86_stEventLogic[u1_DTCStsChgEvId].u1Status;
        if( u1_Status == DCM_DSP_SID86_ROE_STS_START )
        {
            b_Monitoring        = (boolean)TRUE;
            Dcm_Dsp_SID86_u1NumberOfStoredDTCStatusChangedEvents = (uint8)0U;
        }
        else
        {
            if( u1_Status == DCM_DSP_SID86_ROE_STS_START_EVENT )
            {
                b_Monitoring    = (boolean)TRUE;
            }
        }
    }
    
    /* RoeEvent for DTC is START or START_EVENT */
    if( b_Monitoring == (boolean)TRUE )
    {
        /* ((( DTCStatusOld ^ DTCStatusNew ) & DTCStatusNew ) & DTCStatusMask ) */
        u1_DTCStsMask       = Dcm_Dsp_SID86_stEventLogic[u1_DTCStsChgEvId].u1EventTypeRecord[DCM_DSP_SID86_ETR_OFFSET_DTC];
        /* Extract a bit set DTCStatusNew */
        u1_NewSettingBit    = (uint8)((( DTCStatusOld ^ DTCStatusNew ) & DTCStatusNew ));
        if( (uint8)( u1_DTCStsMask & u1_NewSettingBit) != (uint8)0U )
        {
            u1_ExecEventId      = Dcm_Dsp_SID86_u1ExecEventId;
            /* Dcm_Dsp_SID86_u1ExecEventId is INVALID */
            if( u1_ExecEventId == DCM_DSP_SID86_ROE_EVENTID_INVALID )
            {
                /* Call EvtDistr */
                (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID86_SERVTORESPTO ); /* no return check required */
                /* Update Dcm_Dsp_SID86_u1ExecEventId */
                Dcm_Dsp_SID86_u1ExecEventId = u1_DTCStsChgEvId;
            }
            /* Update RoeStatus to START_EVENT */
            Dcm_Dsp_SID86_stEventLogic[u1_DTCStsChgEvId].u1Status = DCM_DSP_SID86_ROE_STS_START_EVENT;
            
            b_UseQueueForDTCEv =  Dcm_Dsp_SID86_bUseQueueforDTCStatusChangedEvents;
            if( b_UseQueueForDTCEv == (boolean)TRUE )
            {
                /* CountUp DTCStatusChangedEvent Counter */
                u1_CurEventNum = Dcm_Dsp_SID86_u1NumberOfStoredDTCStatusChangedEvents;
                u1_MaxEventNum = Dcm_Dsp_SID86_u1MaxNumberOfStoredDTCStatusChangedEvents;
                if( u1_CurEventNum >= u1_MaxEventNum )
                {
                    u1_RcvSubFunc   = Dcm_Dsp_SID86_stEventLogic[u1_DTCStsChgEvId].u1RcvSubFunc;
                    /* confirm that suppressPosRspMsgIndicationBit does not exist */
                    if( u1_RcvSubFunc == (uint8)( u1_RcvSubFunc & DCM_DSP_SID86_SUBFUNC_MASK ) )
                    {
                        /* For Queue length(counter) over, do not count it up */
                        b_ProcInterResp = Dcm_Dsp_SID86_bProcessingIntermediateResponse;
                        if( b_ProcInterResp != (boolean)TRUE )
                        {
                            (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID86_RESPQUEOVER ); /* no return check required */
                            Dcm_Dsp_SID86_bProcessingIntermediateResponse = (boolean)TRUE;
                        }
                    }
                }
                else
                {
                    /* Count up */
                    u1_CurEventNum = (uint8)(u1_CurEventNum + (uint8)1U);
                    Dcm_Dsp_SID86_u1NumberOfStoredDTCStatusChangedEvents = u1_CurEventNum;
                }
            }
            else
            {
                Dcm_Dsp_SID86_u1NumberOfStoredDTCStatusChangedEvents = DCM_DSP_SID86_DTCEVENT_EXIST;
            }
        }
    }
    /* unlock */
    SchM_Exit_Dcm_Dsp_Roe();

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_TriggerOnEvent                                       */
/* Description   | Notify event outbreak of the user trigger                */
/* Preconditions | None                                                     */
/* Parameters    | [IN] RoeEventId     : RoeEvent ID                        */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   E_NOT_OK          : Processing abnormal                */
/* Notes         | RoeEventId is not event id for DTCStatusChange           */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_TriggerOnEvent      /* MISRA DEVIATION */
(
    uint8 RoeEventId
)
{
    Std_ReturnType              u1_RetVal;
    uint8                       u1_NumOfRoeEvent;
    uint8                       u1_Status;
    uint8                       u1_ExecEventId;
    boolean                     b_Monitoring;

    u1_RetVal           = E_OK;
    u1_NumOfRoeEvent    = Dcm_Dsp_SID86_u1NumOfRoeEvent;
    /* lock */
    SchM_Enter_Dcm_Dsp_Roe();
    u1_ExecEventId      = Dcm_Dsp_SID86_u1ExecEventId;
    /* unlock */
    SchM_Exit_Dcm_Dsp_Roe();
    b_Monitoring        = (boolean)FALSE;

    /* RoeEventId id Valid */
    if( RoeEventId < u1_NumOfRoeEvent )
    {
        /* RoeStatus of RoeEventId is START or START_EVENT   */
        u1_Status               = Dcm_Dsp_SID86_stEventLogic[RoeEventId].u1Status;
        if( u1_Status == DCM_DSP_SID86_ROE_STS_START )
        {
            b_Monitoring        = (boolean)TRUE;
        }
        else
        {
            if( u1_Status == DCM_DSP_SID86_ROE_STS_START_EVENT )
            {
                b_Monitoring    = (boolean)TRUE;
            }
        }
        if( b_Monitoring == (boolean)TRUE )
        {
            /* Dcm_Dsp_SID86_u1ExecEventId is Invalid */
            if( u1_ExecEventId == DCM_DSP_SID86_ROE_EVENTID_INVALID )
            {
                /* Call EvtDistr */
                (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID86_SERVTORESPTO ); /* no return check required */
                /* Update Dcm_Dsp_SID86_u1ExecEventId */
                Dcm_Dsp_SID86_u1ExecEventId                 = RoeEventId;
            }
            /* Update RoeSStatus to START_EVENT */
            Dcm_Dsp_SID86_stEventLogic[RoeEventId].u1Status = DCM_DSP_SID86_ROE_STS_START_EVENT;
        }
    }
    else
    {
        u1_RetVal       = E_NOT_OK;
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_GetRoeEventStatus                                    */
/* Description   | Get RoeEvent mode and setup subfunction                  */
/* Preconditions | None                                                     */
/* Parameters    | [IN] RoeEventId      : RoeEvent ID                       */
/*               | [OUT] ptMode         : RoeEvent mode                     */
/*               | [OUT] ptSetupSubFunc : Setup subfunction                 */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK               : Processing normal                 */
/*               |   E_NOT_OK           : Processing abnormal               */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_DSP_SID86_NVM_USE == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_GetRoeEventStatus
(
    uint8 u1RoeEventId,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptMode,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptSetupSubFunc
)
{
    Std_ReturnType  u1_RetVal;
    uint8           u1_NumOfRoeEvent;
    uint8           u1_RoeStatus;
    boolean         b_NvmReadComp;

    u1_RetVal     = E_NOT_OK;
    b_NvmReadComp = Dcm_Dsp_SID86_GetReadStorageCompleteFlag();

    if( b_NvmReadComp != (boolean)FALSE )
    {
        u1_NumOfRoeEvent = Dcm_Dsp_SID86_u1NumOfRoeEvent;
        /* RoeEventId is Valid */
        if( u1RoeEventId < u1_NumOfRoeEvent )
        {
            if( ptMode != NULL_PTR )
            {
                if( ptSetupSubFunc != NULL_PTR )
                {
                    u1_RoeStatus = Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1Status;
                    if( ( u1_RoeStatus == DCM_DSP_SID86_ROE_STS_START ) || ( u1_RoeStatus == DCM_DSP_SID86_ROE_STS_START_EVENT ) )
                    {
                        *ptMode = DCM_EVENT_STARTED;
                        *ptSetupSubFunc = Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1RcvSubFunc & DCM_DSP_SID86_SUBFUNC_MASK;
                    }
                    else if( u1_RoeStatus == DCM_DSP_SID86_ROE_STS_STOP )
                    {
                        *ptMode = DCM_EVENT_STOPPED;
                        *ptSetupSubFunc = Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1RcvSubFunc & DCM_DSP_SID86_SUBFUNC_MASK;
                    }
                    else
                    {
                        *ptMode = DCM_EVENT_CLEARED;
                        *ptSetupSubFunc = DCM_DSP_SID86_SUBFUNC_INVALID;
                    }

                    u1_RetVal = E_OK;
                }
            }
        }
    }

    return u1_RetVal;
}
#endif /* DCM_DSP_SID86_NVM_USE == STD_ON */
#if ( DCM_DSP_SID86_NVM_USE == STD_OFF )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_GetRoeEventStatus
(
    uint8 u1RoeEventId,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptMode,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptSetupSubFunc
)
{
    Std_ReturnType  u1_RetVal;
    uint8           u1_NumOfRoeEvent;
    uint8           u1_RoeStatus;

    u1_RetVal        = E_NOT_OK;
    u1_NumOfRoeEvent = Dcm_Dsp_SID86_u1NumOfRoeEvent;

    /* RoeEventId is Valid */
    if( u1RoeEventId < u1_NumOfRoeEvent )
    {
        if( ptMode != NULL_PTR )
        {
            if( ptSetupSubFunc != NULL_PTR )
            {
                u1_RoeStatus = Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1Status;
                if( ( u1_RoeStatus == DCM_DSP_SID86_ROE_STS_START ) || ( u1_RoeStatus == DCM_DSP_SID86_ROE_STS_START_EVENT ) )
                {
                    *ptMode = DCM_EVENT_STARTED;
                    *ptSetupSubFunc = Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1RcvSubFunc & DCM_DSP_SID86_SUBFUNC_MASK;
                }
                else if( u1_RoeStatus == DCM_DSP_SID86_ROE_STS_STOP )
                {
                    *ptMode = DCM_EVENT_STOPPED;
                    *ptSetupSubFunc = Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1RcvSubFunc & DCM_DSP_SID86_SUBFUNC_MASK;
                }
                else
                {
                    *ptMode = DCM_EVENT_CLEARED;
                    *ptSetupSubFunc = DCM_DSP_SID86_SUBFUNC_INVALID;
                }

                u1_RetVal = E_OK;
            }
        }
    }

    return u1_RetVal;
}
#endif /* DCM_DSP_SID86_NVM_USE == STD_OFF */
#endif /* DCM_SID86_ROE_USE == STD_ON */

#if ( DCM_SID86_ROE_USE == STD_OFF )

/****************************************************************************/
/* Function Name | Dcm_DemTriggerOnDTCStatus                                */
/* Description   | It is notified in DTC change opportunity                 */
/* Preconditions | None                                                     */
/* Parameters    | [IN] DTC             : This is the DTC the change        */
/*               |                         trigger is assigned to.          */
/*               | [IN] DTCStatusOld    : DTC state before change           */
/*               | [IN] DTCStatusNew    : DTC state after change            */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK               : Processing normal                 */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_DemTriggerOnDTCStatus   /* MISRA DEVIATION */
(
    uint32 DTC,                                         /* MISRA DEVIATION  */
    Dem_UdsStatusByteType DTCStatusOld,                 /* MISRA DEVIATION  */
    Dem_UdsStatusByteType DTCStatusNew                  /* MISRA DEVIATION  */
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_TriggerOnEvent                                       */
/* Description   | Notify event outbreak of the user trigger                */
/* Preconditions | None                                                     */
/* Parameters    | [IN] RoeEventId     : RoeEvent ID                        */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   E_NOT_OK          : Processing abnormal                */
/* Notes         | RoeEventId is not event id for DTCStatusChange           */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_TriggerOnEvent     /* MISRA DEVIATION  */
(
    uint8 RoeEventId                                    /* MISRA DEVIATION  */
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_GetRoeEventStatus                                    */
/* Description   | Get RoeEvent mode and setup subfunction                  */
/* Preconditions | None                                                     */
/* Parameters    | [IN] RoeEventId      : RoeEvent ID                       */
/*               | [OUT] ptMode         : RoeEvent mode                     */
/*               | [OUT] ptSetupSubFunc : Setup subfunction                 */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK               : Processing normal                 */
/*               |   E_NOT_OK           : Processing abnormal               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_GetRoeEventStatus
(
    uint8 u1RoeEventId,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptMode,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptSetupSubFunc
)
{
    Std_ReturnType  u1_RetVal;

    u1_RetVal = E_NOT_OK;

    return u1_RetVal;
}

#endif /* DCM_SID86_ROE_USE == STD_OFF */


#if ( DCM_SID86_ROE_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_Init                                       */
/* Description   | SID 86 initialization                                    */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_Init    /* MISRA DEVIATION */
(
    void
)
{
    /* startRequestConnectionId */
    Dcm_Dsp_SID86_u2StartRequestConnectionId                = DCM_DSP_SID86_CONID_INVALID;
    /* event ID that is carrying out processing */
    Dcm_Dsp_SID86_u1ExecEventId                             = DCM_DSP_SID86_ROE_EVENTID_INVALID;
    /* numChangeOfDataIdentfierEvents */
    Dcm_Dsp_SID86_u1NumChangeOfDataIdentfierEvents          = (uint8)0U;
    /* numComparisionOfValueEvents */
    Dcm_Dsp_SID86_u1NumComparisionOfValueEvents             = (uint8)0U;
    /* numberOfStoredDTCStatusChangedEvents */
    Dcm_Dsp_SID86_u1NumberOfStoredDTCStatusChangedEvents    = (uint8)0U;
    /* processing Intermediate Response */
    Dcm_Dsp_SID86_bProcessingIntermediateResponse           = (boolean)FALSE;
    /* bWaitingForTransmission */
    Dcm_Dsp_SID86_bWaitingForTransmission                   = (boolean)FALSE;

    /* Message Context for Intermediate Response */
    Dcm_Dsp_SID86_Init_MsgContext();
    /* Roe Event Table */
    Dcm_Dsp_SID86_Init_RoeEventTable();
#if ( DCM_DSP_SID86_NVM_USE == STD_ON )
    /* Data in conjunction with the storage */
    Dcm_Dsp_SID86_Init_Storage();
#endif /* DCM_DSP_SID86_NVM_USE == STD_ON */

    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_NotifySesCtrl                              */
/* Description   | This function is started at the time of session control. */
/*               | It perform the reconstruction handling of RoeEvent       */
/*               | state with the session control.                          */
/* Preconditions | None                                                     */
/* Parameters    | [IN]   u1SesCtrlTypeOld    : Old Session Ctrl Type       */
/*               | [IN]   u1SesCtrlTypeNew    : New Session Ctrl Type       */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_NotifySesCtrl       /* MISRA DEVIATION */
(
    const Dcm_SesCtrlType   u1SesCtrlTypeOld,
    const Dcm_SesCtrlType   u1SesCtrlTypeNew
)
{
    uint16                  u2_ConnIdList[DCM_DSP_SID86_CONNID_LIST_NUM] = {0};
    uint8                   u1_ListNum;
    uint8                   u1_RoeStopTransmissionSessionUpdate;
    boolean                 b_EventStart;

    u1_ListNum              = (uint8)0U;

    /* Make ConnectionID from EventLogicTable */
    Dcm_Dsp_SID86_MakeActConnectionIdList( &u1_ListNum, &u2_ConnIdList[DCM_DSP_SID86_LIST_START_POS] );
    if( u1_ListNum != (uint8)0U )
    {
        Dcm_Dsp_SID86_SetComActive( u1_ListNum, &u2_ConnIdList[DCM_DSP_SID86_LIST_START_POS], (boolean)FALSE );
    }

    if( u1SesCtrlTypeOld == DCM_DEFAULT_SESSION )
    {
        if( u1SesCtrlTypeNew == DCM_DEFAULT_SESSION )
        {
            /* DCM_DEFAULT_SESSION to DCM_DEFAULT_SESSION */
            /* DcmDspRoeStopTransmissionSessionUpdate set Type#1 */
            u1_RoeStopTransmissionSessionUpdate = Dcm_Dsp_SID86_u1RoeStopTransmissionSessionUpdate;
            if( u1_RoeStopTransmissionSessionUpdate == DCM_DSP_SID86_SESSION_UPDATE_ROE_RESTART )
            {
                /* AllStop-Restart */
                Dcm_Dsp_SID86_StopAllEventsSes( (boolean)TRUE );
                /* ReStart */
                Dcm_Dsp_SID86_ReStartAllEvents();
                /* SWC Indocation */
                b_EventStart = Dcm_Dsp_SID86_CheckStartEvent();
                if( b_EventStart == (boolean)TRUE )
                {
                    /* Exist RoeStart Status Event */
                    /* SWC Indication */
                    (void)Dcm_Dsp_SID86_IndicateRoeStatusChange();  /* no return check required */
                }
            }
            /* DcmDspRoeStopTransmissionSessionUpdate set Type#2 */
            if( u1_RoeStopTransmissionSessionUpdate == DCM_DSP_SID86_SESSION_UPDATE_ROE_STOP )
            {
                /* AllStop-notRestart */
                Dcm_Dsp_SID86_StopAllEventsSes( (boolean)FALSE );
            }
            else
            {
            /* DcmDspRoeStopTransmissionSessionUpdate set Type#3 */
                /* No process */
            }
        }
        else
        {
            /* DCM_DEFAULT_SESSION to non-DCM_DEFAULT_SESSION */
            /* AllStop-Restart */
            Dcm_Dsp_SID86_StopAllEventsSes( (boolean)TRUE );
        }
    }
    else
    {
        if( u1SesCtrlTypeNew == DCM_DEFAULT_SESSION )
        {
            /* non-DCM_DEFAULT_SESSION to DCM_DEFAULT_SESSION */
            /* AllStop-notRestart */
            Dcm_Dsp_SID86_StopAllEventsSes( (boolean)FALSE );
            /* ReStart */
            Dcm_Dsp_SID86_ReStartAllEvents();
            /* SWC Indocation */
            b_EventStart = Dcm_Dsp_SID86_CheckStartEvent();
            if( b_EventStart == (boolean)TRUE )
            {
                /* Exist RoeStart Status Event */
                /* SWC Indication */
                (void)Dcm_Dsp_SID86_IndicateRoeStatusChange();  /* no return check required */
            }
        }
        else
        {
            /* non-DCM_DEFAULT_SESSION to non-DCM_DEFAULT_SESSION */
            /* AllStop-notRestart */
            Dcm_Dsp_SID86_StopAllEventsSes( (boolean)FALSE );
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_TrigServToRespTo_Cbk                       */
/* Description   | Excute SendToRespondTo CallBack                          */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId      : Event ID                           */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_TrigServToRespTo_Cbk   /* MISRA DEVIATION  */
(
    const   uint8   u1EventId                           /* MISRA DEVIATION  */
)
{

    uint8       u1_TargetEventId;
    uint8       u1_ExecEventId;
    uint8       u1_DTCStsChgEvId;
    boolean     b_WaitForTrans;

    b_WaitForTrans  = Dcm_Dsp_SID86_bWaitingForTransmission;

    /* Not waiting forInterMessageTime  */
    if( b_WaitForTrans == (boolean)FALSE )
    {
        /* Update Dcm_Dsp_SID86_u1ExecEventId */
        Dcm_Dsp_SID86_SetNextTriggerEvent();
        /* Check updated Dcm_Dsp_SID86_u1ExecEventId */
        u1_ExecEventId = Dcm_Dsp_SID86_u1ExecEventId;
        if( u1_ExecEventId != DCM_DSP_SID86_ROE_EVENTID_INVALID )
        {
        /* Dcm_Dsp_SID86_u1ExecEventId is not Invalid */
            u1_TargetEventId = u1_ExecEventId;
            u1_DTCStsChgEvId = Dcm_Dsp_SID86_u1DTCStatusChangedEventId;
            if( u1_DTCStsChgEvId != DCM_DSP_SID86_ROE_EVENTID_INVALID )
            {
                /* When Event of DTCStatusChange is effective, check a state */
                if( Dcm_Dsp_SID86_stEventLogic[u1_DTCStsChgEvId].u1Status == DCM_DSP_SID86_ROE_STS_START_EVENT )
                {
                    /* Event of DTCStatusChange has priority over DidChange */
                    u1_TargetEventId = u1_DTCStsChgEvId;
                }
                else
                {
                    Dcm_Dsp_SID86_u1NumberOfStoredDTCStatusChangedEvents = (uint8)0U;
                }
            }
            /* SendServToRespTo() */
            Dcm_Dsp_SID86_SendServToRespTo( u1_TargetEventId );
        }
        else
        {
        /* Dcm_Dsp_SID86_u1ExecEventId is Invalid */
            /* No process */
        }
    }
    /* Wanting for InterMessageTime */
    else
    {
        /* Call EvtDistr */
        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID86_SERVTORESPTO ); /* no return check required */
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dcm_SID86_RespQueueOver_Cbk                              */
/* Description   | Excute Intermediate Response CallBack                    */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId      : Event ID                           */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_RespQueueOver_Cbk  /* MISRA DEVIATION  */
(
    const   uint8   u1EventId                           /* MISRA DEVIATION  */
)
{
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) pt_ResData;
    Dcm_MsgLenType      u4_MaxLen;
    Dcm_MsgLenType      u4_ResLen;
    uint16              u2_ConnectionId;
    uint8               u1_ServToRespToLen;
    uint8               u1_DTCStsChgEvId;
    uint8               u1_Cnt;
    uint8               u1_Status;
    Dcm_StatusType      u1_RetRoeSend;

    u4_MaxLen           = (uint32)0U;
    u1_DTCStsChgEvId    = Dcm_Dsp_SID86_u1DTCStatusChangedEventId;
    if( u1_DTCStsChgEvId != DCM_DSP_SID86_ROE_EVENTID_INVALID )
    {
        /* lock */
        SchM_Enter_Dcm_Dsp_Roe();
        u1_Status = Dcm_Dsp_SID86_stEventLogic[u1_DTCStsChgEvId].u1Status;
        /* unlock */
        SchM_Exit_Dcm_Dsp_Roe();
        if( ( u1_Status == DCM_DSP_SID86_ROE_STS_START ) || ( u1_Status == DCM_DSP_SID86_ROE_STS_START_EVENT ) )
        {
            u2_ConnectionId = Dcm_Dsp_SID86_stEventLogic[u1_DTCStsChgEvId].u2ConnectionId;
            pt_ResData      = Dcm_Dsl_GetRoeIntermediateRespBuf( u2_ConnectionId, &u4_MaxLen );
            if( pt_ResData != NULL_PTR )
            {
                u1_ServToRespToLen = Dcm_Dsp_SID86_stEventLogic[u1_DTCStsChgEvId].u1ServiceToRespondToRecordLength;
                u4_ResLen   = (uint32)( (uint32)DCM_DSP_SID86_POSRES_SID_LEN +
                                        (uint32)DCM_DSP_SID86_QOM_EVTYPE_LEN +
                                        (uint32)DCM_DSP_SID86_QOM_NUMIDEV_LEN +
                                        (uint32)DCM_DSP_SID86_QOM_EVWINTIM_LEN +
                                        (uint32)DCM_DSP_SID86_QOM_EVTYPREC_LEN +    /* no wrap around */
                                        (uint32)u1_ServToRespToLen );
                if( u4_ResLen <= u4_MaxLen )
                {
                    /* Edit Queue Over Message */
                    pt_ResData[DCM_DSP_SID86_MES_OFFSET_00]     = DCM_DSP_SID86_POSRES_SID;
                    pt_ResData[DCM_DSP_SID86_MES_OFFSET_01]     = DCM_DSP_SID86_QOM_EVTYPE;
                    pt_ResData[DCM_DSP_SID86_MES_OFFSET_02]     = DCM_DSP_SID86_QOM_NUMIDEV;
                    pt_ResData[DCM_DSP_SID86_MES_OFFSET_03]     = Dcm_Dsp_SID86_stEventLogic[u1_DTCStsChgEvId].u1EventWindow;
                    pt_ResData[DCM_DSP_SID86_MES_OFFSET_04]     = Dcm_Dsp_SID86_stEventLogic[u1_DTCStsChgEvId].u1EventTypeRecord[0];

                    for( u1_Cnt = (uint8)0U; u1_Cnt < u1_ServToRespToLen; u1_Cnt++ )
                    {
                        pt_ResData[(DCM_DSP_SID86_MES_OFFSET_05 + u1_Cnt)]  = Dcm_Dsp_SID86_stEventLogic[u1_DTCStsChgEvId].u1ServiceToRespondToRecord[u1_Cnt];
                    }
                    /* Edit Message Context */
                    Dcm_Dsp_SID86_stMsgContext.reqData              = NULL_PTR;
                    Dcm_Dsp_SID86_stMsgContext.reqDataLen           = (uint32)0U;
                    Dcm_Dsp_SID86_stMsgContext.resData              = pt_ResData;
                    Dcm_Dsp_SID86_stMsgContext.resDataLen           = u4_ResLen;
                    Dcm_Dsp_SID86_stMsgContext.resMaxDataLen        = u4_MaxLen;
                    Dcm_Dsp_SID86_stMsgContext.msgAddInfo.reqType   = DCM_DSP_SID86_REQ_PHYSICAL;
                    Dcm_Dsp_SID86_stMsgContext.msgAddInfo.suppressPosResponse
                                                                = STD_OFF;
                    Dcm_Dsp_SID86_stMsgContext.idContext            = DCM_DSP_SID86_SID;
                    Dcm_Dsp_SID86_stMsgContext.dcmRxPduId           = (uint8)0U;
                    /* Send Queue Over Message */
                    u1_RetRoeSend = Dcm_Dsd_RoeSendReq( &Dcm_Dsp_SID86_stMsgContext, u2_ConnectionId );
                    if( u1_RetRoeSend == (Dcm_StatusType)DCM_E_OK )
                    {
                        Dcm_Dsp_SID86_bProcessingIntermediateResponse = (boolean)FALSE;
                    }
                    else if( u1_RetRoeSend == (Dcm_StatusType)DCM_E_ROE_NOT_ACCEPTED )
                    {
                        /* Dsl is Busy. Re-call EvtDistr */
                        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID86_RESPQUEOVER ); /* no return check required */
                    }
                    else
                    {
                        Dcm_Dsp_SID86_bProcessingIntermediateResponse = (boolean)FALSE;
                    }
                }
            }
            else
            {
                /* Dsl is Busy. Re-call EvtDistr */
                (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID86_RESPQUEOVER ); /* no return check required */
            }
        }
        else
        {
            Dcm_Dsp_SID86_bProcessingIntermediateResponse = (boolean)FALSE;
        }
    }
    return ;
}


/****************************************************************************/
/* Function Name | Dcm_SID86_InterMessageTime_Cbk                           */
/* Description   | InterMessageTimer Time out CallBack                      */
/* Preconditions | None                                                     */
/* Parameters    | [in] u1TimerId : Timer ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_InterMessageTime_Cbk   /* MISRA DEVIATION  */
(
    const   uint8   u1TimerId                           /* MISRA DEVIATION  */
)
{
    /* Waiting for InterMessageTime TimeOut */
    Dcm_Dsp_SID86_bWaitingForTransmission = (boolean)FALSE;

    return ;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_ROEStatusCheck                             */
/* Description   | Roe Active Status Check                                  */
/* Preconditions | None                                                     */
/* Parameters    | [IN/OUT] ptActive : active Status                        */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_ROEStatusCheck     /* MISRA DEVIATION  */
(
    P2VAR( Dcm_ActiveStateType, AUTOMATIC, DCM_APPL_DATA )  ptActive
)
{
    boolean     b_Active;

    /* Combinationcheck by StartRequestConnectionId and StartEvent ,for Sleep NG by RAM destruction */
    if( Dcm_Dsp_SID86_u2StartRequestConnectionId != DCM_DSP_SID86_CONID_INVALID )
    {
        b_Active    = Dcm_Dsp_SID86_CheckStartEvent();

        if( b_Active == (boolean)TRUE )
        {
            *ptActive |= DCM_EXE_ROE;
        }
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_SetActiveResponse                          */
/* Description   | Set Communication Bus for Response on Event transmission */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1ServiceActiveStatus : each Service Active Status  */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_SetActiveResponse  /* MISRA DEVIATION  */
(
    const Dcm_ActiveStateType u1ServiceActiveStatus
)
{
    uint16    u2_ConnIdList[DCM_DSP_SID86_CONNID_LIST_NUM] = {0};
    uint8     u1_ListNum;
    
    u1_ListNum = (uint8)0U;
    
    if( DCM_EXE_ROE == (Dcm_ActiveStateType)(u1ServiceActiveStatus & DCM_EXE_ROE) )
    {
        /* Make ConnectionID from EventLogicTable */
        Dcm_Dsp_SID86_MakeActConnectionIdList( &u1_ListNum, &u2_ConnIdList[DCM_DSP_SID86_LIST_START_POS] );

        if( u1_ListNum != (uint8)0U )
        {
            Dcm_Dsp_SID86_SetComActive( u1_ListNum, &u2_ConnIdList[DCM_DSP_SID86_LIST_START_POS], (boolean)TRUE );
        }
        else
        {
            /* Inactive the communication bus for all clients */
            u2_ConnIdList[DCM_DSP_SID86_LIST_START_POS] = DCM_DSL_ALL_TARGETS;
            Dcm_Dsp_SID86_SetComActive( DCM_DSP_SID86_LIST_START_CNT, &u2_ConnIdList[DCM_DSP_SID86_LIST_START_POS], (boolean)FALSE );
        }
    }
    return;
}


#if ( DCM_DSP_SID86_NVM_USE == STD_ON )

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_SetDataStorage2Mirror                      */
/* Description   | Storage to Mirror                                        */
/* Preconditions | None                                                     */
/* Parameters    |  [in] u2BlockIdx : Block Index                           */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_SetDataStorage2Mirror                  /* MISRA DEVIATION  */
(
    const uint16 u2BlockIdx
)
{
    P2VAR( Dcm_Dsp_SID86_StorageEventLogicType, AUTOMATIC, DCM_VAR_SAVED_ZONE ) pt_StorageEvent;
    P2VAR( Dcm_Dsp_SID86_EventLogicType, AUTOMATIC, DCM_APPL_DATA ) pt_EventLogic;
    uint16              u2_BIdxStaRoe;
    uint16              u2_BIdxEndRoe;
    Std_ReturnType      u1_RetChgBlkIdx;
    uint8               u1_RoeEventId;
    uint8               u1_RoeBlockIdx;
    uint8               u1_NumOfRoeStorage;
    uint8               u1_Cnt;

    u1_NumOfRoeStorage  = Dcm_Dsp_SID86_u1NumOfStrageRoeEvent;

    u2_BIdxStaRoe       = Dcm_Dsp_StorageMng_u2BIdx_StaRoe;
    u2_BIdxEndRoe       = Dcm_Dsp_StorageMng_u2BIdx_EndRoe;

    if( u1_NumOfRoeStorage > (uint8)0x00U )
    {
        if( ( u2_BIdxStaRoe <= u2BlockIdx ) && ( u2BlockIdx <= u2_BIdxEndRoe ) )
        {
            /* Convert For RoeEventId */
            u1_RoeBlockIdx      = (uint8)( u2BlockIdx - u2_BIdxStaRoe );
            u1_RetChgBlkIdx     = Dcm_Dsp_SID86_ChangeRoeBlkIdx2EvtId( u1_RoeBlockIdx, &u1_RoeEventId );
            if( u1_RetChgBlkIdx == (Std_ReturnType)E_OK )
            {
                /* Get Dest */
                pt_EventLogic       = &Dcm_Dsp_SID86_stEventLogic[u1_RoeEventId]; 
                /* Get Src  */
                pt_StorageEvent     = &Dcm_Dsp_SID86_stStorageEventLogic[u1_RoeBlockIdx];

                /* Set Storage to Mirror */
                pt_EventLogic->u2ConnectionId       = pt_StorageEvent->u2ConnectionId;
                Dcm_Dsp_SID86_u2ConnectionIdMirror[u1_RoeEventId]
                                                    = pt_EventLogic->u2ConnectionId;
                for( u1_Cnt = (uint8)0U; u1_Cnt < DCM_DSP_SID86_SERVICETORESPONDTORECORD_MAX; u1_Cnt++ )
                {
                    pt_EventLogic->u1ServiceToRespondToRecord[u1_Cnt]
                                                    = pt_StorageEvent->u1ServiceToRespondToRecord[u1_Cnt];
                }
                for( u1_Cnt = (uint8)0U; u1_Cnt < DCM_DSP_SID86_EVENTTYPERECORD_MAX; u1_Cnt++ )
                {
                    pt_EventLogic->u1EventTypeRecord[u1_Cnt]
                                                    = pt_StorageEvent->u1EventTypeRecord[u1_Cnt];
                }
                pt_EventLogic->u1EventWindow        = pt_StorageEvent->u1EventWindowTime;
                pt_EventLogic->u1ServiceToRespondToRecordLength
                                                    = pt_StorageEvent->u1ServiceToRespondToRecordLength;
                pt_EventLogic->u1RcvSubFunc         = pt_StorageEvent->u1RcvSubFunc;
                pt_EventLogic->bRoeStart            = pt_StorageEvent->bRoeStart;
            }
        }
        else
        {
            /* No process */
        }
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_SetDataMirror2Storage                      */
/* Description   | Mirror to Storage                                        */
/* Preconditions | None                                                     */
/* Parameters    |  [in] u2BlockIdx : Block Index                           */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_SetDataMirror2Storage                  /* MISRA DEVIATION  */
(
    const uint16 u2BlockIdx
)
{
    P2VAR( Dcm_Dsp_SID86_StorageEventLogicType, AUTOMATIC, DCM_VAR_SAVED_ZONE ) pt_StorageEvent;
    P2VAR( Dcm_Dsp_SID86_EventLogicType, AUTOMATIC, DCM_APPL_DATA ) pt_EventLogic;
    uint16              u2_BIdxStaRoe;
    uint16              u2_BIdxEndRoe;
    uint16              u2_wkStartConId;
    uint16              u2_wkConId;
    uint16              u2_ConnId;
    uint16              u2_ConnIdMirror;
    Std_ReturnType      u1_RetChgBlkIdx;
    uint8               u1_RoeEventId;
    uint8               u1_RoeBlockIdx;
    uint8               u1_Cnt;

    u2_BIdxStaRoe       = Dcm_Dsp_StorageMng_u2BIdx_StaRoe;
    u2_BIdxEndRoe       = Dcm_Dsp_StorageMng_u2BIdx_EndRoe;

    if( ( u2_BIdxStaRoe <= u2BlockIdx ) && ( u2BlockIdx <= u2_BIdxEndRoe ) )
    {
        /* Convert For RoeEventId */
        u1_RoeBlockIdx      = (uint8)( u2BlockIdx - u2_BIdxStaRoe );
        u1_RetChgBlkIdx     = Dcm_Dsp_SID86_ChangeRoeBlkIdx2EvtId( u1_RoeBlockIdx, &u1_RoeEventId );
        if( u1_RetChgBlkIdx == (Std_ReturnType)E_OK )
        {
            /* Get Src  */
            pt_EventLogic       = &Dcm_Dsp_SID86_stEventLogic[u1_RoeEventId]; 
            /* Get Dest */
            pt_StorageEvent     = &Dcm_Dsp_SID86_stStorageEventLogic[u1_RoeBlockIdx];

            /* Set Mirror to Storage */
            u2_ConnId           = pt_EventLogic->u2ConnectionId;
            u2_ConnIdMirror     = Dcm_Dsp_SID86_u2ConnectionIdMirror[u1_RoeEventId];
            u2_wkConId          = u2_ConnId;
            if( u2_ConnId != u2_ConnIdMirror )
            {
                u2_wkConId                          = DCM_DSP_SID86_CONID_INVALID;
            }
            pt_StorageEvent->u2ConnectionId         = u2_wkConId;
            u2_wkStartConId                         = DCM_DSP_SID86_CONID_INVALID;
            /* lock */
            SchM_Enter_Dcm_Dsp_Roe();
            if( pt_EventLogic->u1Status != DCM_DSP_SID86_ROE_STS_CLEAR )
            {
                u2_wkStartConId                     = Dcm_Dsp_SID86_u2StartRequestConnectionId;
            }
            /* unlock */
            SchM_Exit_Dcm_Dsp_Roe();
            pt_StorageEvent->u2StartConnectionId    = u2_wkStartConId;
            for( u1_Cnt = (uint8)0U; u1_Cnt < DCM_DSP_SID86_SERVICETORESPONDTORECORD_MAX; u1_Cnt++ )
            {
                pt_StorageEvent->u1ServiceToRespondToRecord[u1_Cnt]
                                                    = pt_EventLogic->u1ServiceToRespondToRecord[u1_Cnt];
            }
            for( u1_Cnt = (uint8)0U; u1_Cnt < DCM_DSP_SID86_EVENTTYPERECORD_MAX; u1_Cnt++ )
            {
                pt_StorageEvent->u1EventTypeRecord[u1_Cnt]
                                                    = pt_EventLogic->u1EventTypeRecord[u1_Cnt];
            }
            pt_StorageEvent->u1EventWindowTime      = pt_EventLogic->u1EventWindow;
            pt_StorageEvent->u1ServiceToRespondToRecordLength
                                                    = pt_EventLogic->u1ServiceToRespondToRecordLength;
            pt_StorageEvent->u1RcvSubFunc           = pt_EventLogic->u1RcvSubFunc;
            pt_StorageEvent->bRoeStart              = pt_EventLogic->bRoeStart;
        }
    }
    else
    {
        /* No process */
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_ReadConfirmation                           */
/* Description   | Read Storage Confirmation                                */
/* Preconditions | None                                                     */
/* Parameters    |  [in] u2BlockIdx : Block Index                           */
/*               |  [in] u1Result : Read Storage Result                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_ReadConfirmation                       /* MISRA DEVIATION  */
(
    const uint16 u2BlockIdx,    /* MISRA DEVIATION */
    const uint8  u1Result
)
{
    Std_ReturnType      u1_RetChgBlkIdx;
    uint8               u1_RoeEventId;
    uint8               u1_RoeBlockIdx;
    uint8               u1_NumOfRoeStorage;

    u1_NumOfRoeStorage  = Dcm_Dsp_SID86_u1NumOfStrageRoeEvent;

    if( u1Result == (uint8)E_NOT_OK )
    {
        for( u1_RoeBlockIdx = (uint8)0U; u1_RoeBlockIdx < u1_NumOfRoeStorage; u1_RoeBlockIdx++ )
        {
            /* Convert For RoeEventId */
            u1_RetChgBlkIdx     = Dcm_Dsp_SID86_ChangeRoeBlkIdx2EvtId( u1_RoeBlockIdx, &u1_RoeEventId );
            if( u1_RetChgBlkIdx == (Std_ReturnType)E_OK )
            {
                Dcm_Dsp_SID86_SetErrorRoeEvent( u1_RoeEventId );
            }
        }
    }

    ( void )Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID86_READCOMP );      /* no return check required */

    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_AllReadCompleteCbk                         */
/* Description   | Callback function for  event delivery registration of    */
/*               | Dcm_Dsp_SID86_ReadConfirmation                           */
/* Preconditions | None                                                     */
/* Parameters    | [IN]  u1EventId        :Event ID                         */
/* Return Value  | void                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_AllReadCompleteCbk   /* MISRA DEVIATION  */
(
    const uint8     u1EventId   /* MISRA DEVIATION */
)
{
    Std_ReturnType                  u1_CheckData;
    Std_ReturnType                  u1_RetChgBlkIdx;
    uint8                           u1_NumOfRoeStorage;
    uint8                           u1_RoeBlockIdx;
    uint8                           u1_RoeEventId;
    boolean                         b_EventStart;

    u1_NumOfRoeStorage      = Dcm_Dsp_SID86_u1NumOfStrageRoeEvent;

    /* loop does only the number of ROE events for storage */
    for( u1_RoeBlockIdx = (uint8)0U; u1_RoeBlockIdx < u1_NumOfRoeStorage; u1_RoeBlockIdx++ )
    {
        /* Change RoeBlockIndex to RoeEventId */
        u1_RetChgBlkIdx = Dcm_Dsp_SID86_ChangeRoeBlkIdx2EvtId( u1_RoeBlockIdx, &u1_RoeEventId );
        if( u1_RetChgBlkIdx == (Std_ReturnType)E_OK )
        {
            /* Check Illegal Data */
            u1_CheckData    = Dcm_Dsp_SID86_CheckEventTableData( u1_RoeEventId );
            if( u1_CheckData == (Std_ReturnType)E_OK )
            {
                /* legal Data */
                /*   Update EventTable Data */
                Dcm_Dsp_SID86_UpdateEventTableData( u1_RoeEventId );
            }
            else
            {
                /* Illegal Data */
                /*   Storage Data Initialize */
                Dcm_Dsp_SID86_ClearElemOfRoeEventTable( u1_RoeEventId );
                Dcm_Dsp_SID86_WriteStorage( u1_RoeEventId );
            }
        }
    }
    /* Set Read Storage Completion */
    Dcm_Dsp_SID86_bReadStorageCompleteFlag      = (boolean)TRUE;
    /* SWC Indocation */
    b_EventStart = Dcm_Dsp_SID86_CheckStartEvent();
    if( b_EventStart == (boolean)TRUE )
    {
        /* Exist RoeStart Status Event */
        /* SWC Indication */
        (void)Dcm_Dsp_SID86_IndicateRoeStatusChange();  /* no return check required */
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_Refresh                                    */
/* Description   | SID86 Refresh processing                                 */
/* Preconditions | None                                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_Refresh             /* MISRA DEVIATION */
(
    void
)
{
    P2VAR(volatile boolean, AUTOMATIC, DCM_APPL_DATA) pt_ReadStorageCompleteFlag;
    P2VAR(volatile uint16, AUTOMATIC, DCM_APPL_DATA) pt_StartRequestConnectionId;
    uint16  u2_StartRequestConnectionId;
    boolean b_ReadStorageCompleteFlag;

    pt_ReadStorageCompleteFlag  = &Dcm_Dsp_SID86_bReadStorageCompleteFlag;
    b_ReadStorageCompleteFlag   = *pt_ReadStorageCompleteFlag;
    *pt_ReadStorageCompleteFlag = b_ReadStorageCompleteFlag ;

    pt_StartRequestConnectionId = &Dcm_Dsp_SID86_u2StartRequestConnectionId;
    u2_StartRequestConnectionId = *pt_StartRequestConnectionId;
    *pt_StartRequestConnectionId= u2_StartRequestConnectionId;

    return;
}

#endif /* DCM_DSP_SID86_NVM_USE == STD_ON */


#endif /* DCM_SID86_ROE_USE == STD_ON */

#if ( DCM_SID86_ROE_USE == STD_ON )
/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_Init_MsgContext                            */
/* Description   | Initialyze MsgContext                                    */
/* Preconditions | None                                                     */
/* Parameters    | Node                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_Init_MsgContext
(
    void
)
{
    Dcm_Dsp_SID86_stMsgContext.reqData              = NULL_PTR;
    Dcm_Dsp_SID86_stMsgContext.reqDataLen           = (uint32)0U;
    Dcm_Dsp_SID86_stMsgContext.resData              = NULL_PTR;
    Dcm_Dsp_SID86_stMsgContext.resDataLen           = (uint32)0U;
    Dcm_Dsp_SID86_stMsgContext.msgAddInfo.reqType   = DCM_DSP_SID86_REQ_PHYSICAL;
    Dcm_Dsp_SID86_stMsgContext.msgAddInfo.suppressPosResponse = STD_OFF;
    Dcm_Dsp_SID86_stMsgContext.resMaxDataLen        = (uint32)0U;
    Dcm_Dsp_SID86_stMsgContext.idContext            = (uint8)0U;
    Dcm_Dsp_SID86_stMsgContext.dcmRxPduId           = (uint16)0U;

    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_Init_RoeEventTable                         */
/* Description   | Initialyze RoeEventTable                                 */
/* Preconditions | None                                                     */
/* Parameters    | Node                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_Init_RoeEventTable
(
    void
)
{
    uint8               u1_NumOfRoeEvent;
    uint8               u1_EvCnt;

    u1_NumOfRoeEvent    = Dcm_Dsp_SID86_u1NumOfRoeEvent;
    for( u1_EvCnt = (uint8)0U; u1_EvCnt < u1_NumOfRoeEvent; u1_EvCnt++ )
    {
        Dcm_Dsp_SID86_InitElemOfRoeEventTable( u1_EvCnt );
    }
    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_InitElemOfRoeEventTable                    */
/* Description   | Initialyze Element of RoeEventTable                      */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1RoeEventId      : RoeEvent ID                     */
/* Return Value  | None                                                     */
/* Notes         | Guarantee that a value of u1RoeEventId is an effective   */
/*               |  value in the user of this function                      */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_InitElemOfRoeEventTable
(
    const   uint8                               u1RoeEventId
)
{
    uint8               u1_ParaCnt;

    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u2ConnectionId                     = DCM_DSP_SID86_CONID_INVALID;
    Dcm_Dsp_SID86_u2ConnectionIdMirror[u1RoeEventId]                            = Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u2ConnectionId;
    for( u1_ParaCnt = (uint8)0U; u1_ParaCnt < DCM_DSP_SID86_SERVICETORESPONDTORECORD_MAX; u1_ParaCnt++ )
    {
        Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1ServiceToRespondToRecord[u1_ParaCnt]
                                                                                = (uint8)0U;
    }
    for( u1_ParaCnt = (uint8)0U; u1_ParaCnt < DCM_DSP_SID86_EVENTTYPERECORD_MAX; u1_ParaCnt++ )
    {
        Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1EventTypeRecord[u1_ParaCnt]  = (uint8)0U;
    }
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1NumberOfIdentifiedEvents         = (uint8)0U;
    /* Provisional coping. SET CLREAR  */
    if( Dcm_Dsp_SID86_stRoeEvent[u1RoeEventId].u1InitEvStatus == DCM_DSP_SID86_ROE_STOPPED )
    {
        Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1Status                       = DCM_DSP_SID86_ROE_STS_STOP;
    }
    else
    {
        Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1Status                       = DCM_DSP_SID86_ROE_STS_CLEAR;
    }
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1EventWindow                      = DCM_DSP_SID86_EVWIN_INVALID;
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1ServiceToRespondToRecordLength   = (uint8)0U;
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1RcvSubFunc                       = DCM_DSP_SID86_SUBFUNC_INVALID;
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].bRoeStart                          = (boolean)FALSE;
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].bDefaultSesReactive                = (boolean)FALSE;

    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_CheckServSupport                           */
/* Description   | Check SID in ServiceToRespondTo                          */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptServToResp   : Top Address of ServToRespToRecord  */
/*               | [IN] u4ServToRespToRecLen : Length of ServToRespToRecord */
/*               | [IN] u2PduId        : PduId ID                           */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   E_NOT_OK          : Processing abnormal                */
/* Notes         | Guarantee data for 2Byte from top address                */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_CheckServSupport
(
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA )  ptServToResp,
    const   uint32                              u4ServToRespToRecLen,
    const   PduIdType                           u2PduId
)
{
    Std_ReturnType              u1_RetVal;
    Std_ReturnType              u1_RetSrvSup;
    Std_ReturnType              u1_CheckSID;
    uint8                       u1_SID;
    uint8                       u1_SubFunc;

    u1_RetVal           = (Std_ReturnType)E_NOT_OK;
    u1_CheckSID         = (Std_ReturnType)E_NOT_OK;
    u1_SID              = ptServToResp[DCM_DSP_SID86_CHK_SID_OFFSET];

    /* Check SID */
    if( u1_SID == DCM_DSP_SID86_CHK_SID22_SID )
    {
        u1_CheckSID     = (Std_ReturnType)E_OK;
    }
    else
    {
        if( u1_SID == DCM_DSP_SID86_CHK_SID19_SID )
        {
            if( u4ServToRespToRecLen > DCM_DSP_SID86_SID_LEN )
            {
                u1_SubFunc = (uint8)( ptServToResp[DCM_DSP_SID86_CHK_SUBFUNC_OFFSET] & DCM_DSP_SID86_SUBFUNC_MASK );
                if( u1_SubFunc == DCM_DSP_SID86_CHK_SID19_SF0E )
                {
                    u1_CheckSID = (Std_ReturnType)E_OK;
                }
            }
        }
    }

    if( u1_CheckSID == (Std_ReturnType)E_OK )
    {
        /* Check SID Support */
        u1_RetSrvSup    = Dcm_Dsd_ChkRoeServiceSupported( ptServToResp, u4ServToRespToRecLen, u2PduId );
        if( u1_RetSrvSup == (Std_ReturnType)E_OK )
        {
            u1_RetVal   = (Std_ReturnType)E_OK;
        }
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_RegEvent_Sub01                             */
/* Description   | Regist Eventtable for Subfunction01                      */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1RoeEventId   : RoeEvent ID                        */
/*               | [IN] u2ConnectionId : Connention ID                      */
/*               | [IN] pMsgContext    : Message Context                    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_RegEvent_Sub01
(
    const   uint8                                           u1RoeEventId,
    const   uint16                                          u2ConnectionId,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA )    pt_ReqData;
    uint16              u2_OldConnectionId;
    uint8               u1_ReqDataLen;
    uint8               u1_ServToRespToLen;
    uint8               u1_OldStatus;
    uint8               u1_EventWinTime;
    uint8               u1_RecSubFunc;
    uint8               u1_DTCStaMask;
    uint8               u1_Cnt;
    uint8               u1_ListNum;
    boolean             b_ConnectionUsed;

    u1_ReqDataLen       = (uint8)ptMsgContext->reqDataLen;
    u1_OldStatus        = Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1Status;
    u1_ServToRespToLen  = (uint8)( u1_ReqDataLen - ( DCM_DSP_SID86_EVENTWINDOWTIME_LEN + DCM_DSP_SID86_DTCSTATUSMASK_LEN ) );   /* no wrap around */
    pt_ReqData          = ptMsgContext->reqData;
    u1_EventWinTime     = pt_ReqData[DCM_DSP_SID86_EVENTWINDOWTIME_OFFSET];
    u1_RecSubFunc       = Dcm_Dsp_SID86_GenerateReceivedSubFunc( DCM_DSP_SID86_SF01, ptMsgContext->msgAddInfo.suppressPosResponse );
    u1_DTCStaMask       = pt_ReqData[DCM_DSP_SID86_DTCSTATUSMASK_OFFSET];
    u2_OldConnectionId  = Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u2ConnectionId;
    /* u2ConnectionId                       */
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u2ConnectionId             = u2ConnectionId;
    Dcm_Dsp_SID86_u2ConnectionIdMirror[u1RoeEventId]                    = Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u2ConnectionId;
    /* u1ServiceToRespondToRecord           */
    for( u1_Cnt = (uint8)0U; u1_Cnt < u1_ServToRespToLen; u1_Cnt++ )
    {
        Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1ServiceToRespondToRecord[u1_Cnt]
                                                                        = pt_ReqData[(DCM_DSP_SID86_SF01_SID_OFFSET + u1_Cnt)]; /* no wrap around */
    }
    /* u1EventTypeRecord(DTC)               */
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1EventTypeRecord[DCM_DSP_SID86_ETR_OFFSET_DTC]
                                                                        = u1_DTCStaMask;
    /* u1NumberOfIdentifiedEvents           */
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1NumberOfIdentifiedEvents = (uint8)0U;
    /* u1Status                             */
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1Status                   = DCM_DSP_SID86_ROE_STS_STOP;
    /* u1EventWindow                        */
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1EventWindow              = u1_EventWinTime;
    /* u1ServiceToRespondToRecordLength     */
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1ServiceToRespondToRecordLength
                                                                        = u1_ServToRespToLen;
    /* u1SubFunc                            */
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1RcvSubFunc               = u1_RecSubFunc;
    /* bRoeStart                            */
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].bRoeStart                  = (boolean)FALSE;
    /* bDefaultSesReactive                  */
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].bDefaultSesReactive        = (boolean)FALSE;

    /* Notification */
    if( u1_OldStatus != DCM_DSP_SID86_ROE_STS_STOP )
    {
        (void)Dcm_Dsp_SID86_Cnct_Sw_Roe( u1RoeEventId, DCM_EVENT_STOPPED );   /* no return check required */
        Dem_DcmControlDTCStatusChangedNotification( (boolean)FALSE );
        /* Stop judgment of the bus corresponding to the connection that a former state used at the time of ROE_START */
        if( ( u1_OldStatus == DCM_DSP_SID86_ROE_STS_START ) || ( u1_OldStatus == DCM_DSP_SID86_ROE_STS_START_EVENT ) )
        {
            b_ConnectionUsed = Dcm_Dsp_SID86_IsUsedConnection( u2_OldConnectionId );
            if( b_ConnectionUsed != (boolean)TRUE )
            {
                /* When a old ConnectionId overwritten is not used; of the bus is non-active, and carry it out */
                u1_ListNum = DCM_DSP_SID86_LIST_START_CNT;
                Dcm_Dsp_SID86_SetComActive( u1_ListNum, &u2_OldConnectionId, (boolean)FALSE );
            }
        }
    }
    /* Write Storage */
    Dcm_Dsp_SID86_WriteStorage( u1RoeEventId );

    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_RegEvent_Sub03                             */
/* Description   | Regist Eventtable for Subfunction03                      */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1RoeEventId   : RoeEvent ID                        */
/*               | [IN] u2ConnectionId : Connention ID                      */
/*               | [IN] pMsgContext    : Message Context                    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_RegEvent_Sub03
(
    const   uint8                                           u1RoeEventId,
    const   uint16                                          u2ConnectionId,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA )    pt_ReqData;
    uint16              u2_OldConnectionId;
    uint8               u1_ReqDataLen;
    uint8               u1_ServToRespToLen;
    uint8               u1_OldStatus;
    uint8               u1_OldSubFunc;
    uint8               u1_EventWinTime;
    uint8               u1_RecSubFunc;
    uint8               u1_Cnt;
    uint8               u1_ListNum;
    boolean             b_ConnectionUsed;

    u1_ReqDataLen       = (uint8)ptMsgContext->reqDataLen;
    u1_OldStatus        = Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1Status;
    u1_OldSubFunc       = (uint8)( Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1RcvSubFunc & DCM_DSP_SID86_SUBFUNC_MASK );
    u1_ServToRespToLen  = (uint8)( u1_ReqDataLen - ( DCM_DSP_SID86_EVENTWINDOWTIME_LEN + DCM_DSP_SID86_DID_LEN ) ); /* no wrap around */
    pt_ReqData          = ptMsgContext->reqData;
    u1_EventWinTime     = pt_ReqData[DCM_DSP_SID86_EVENTWINDOWTIME_OFFSET];
    u1_RecSubFunc       = Dcm_Dsp_SID86_GenerateReceivedSubFunc( DCM_DSP_SID86_SF03, ptMsgContext->msgAddInfo.suppressPosResponse );
    u2_OldConnectionId  = Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u2ConnectionId;
    /* u2ConnectionId                       */
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u2ConnectionId             = u2ConnectionId;
    Dcm_Dsp_SID86_u2ConnectionIdMirror[u1RoeEventId]                    = Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u2ConnectionId;
    /* u1ServiceToRespondToRecord           */
    for( u1_Cnt = (uint8)0U; u1_Cnt < u1_ServToRespToLen; u1_Cnt++ )
    {
        Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1ServiceToRespondToRecord[u1_Cnt]
                                                                        = pt_ReqData[(DCM_DSP_SID86_SF03_SID_OFFSET + u1_Cnt)]; /* no wrap around */
    }
    /* u1EventTypeRecord(DID)               */
    for( u1_Cnt = (uint8)0U; u1_Cnt < (uint8)DCM_DSP_SID86_DID_LEN; u1_Cnt++ )
    {
        Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1EventTypeRecord[u1_Cnt]
                                                                        = pt_ReqData[(DCM_DSP_SID86_SF03_DID_OFFSET + u1_Cnt)]; /* no wrap around */
    }
    /* u1NumberOfIdentifiedEvents           */
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1NumberOfIdentifiedEvents = (uint8)0U;
    /* u1Status                             */
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1Status                   = DCM_DSP_SID86_ROE_STS_STOP;
    /* u1EventWindow                        */
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1EventWindow              = u1_EventWinTime;
    /* u1ServiceToRespondToRecordLength     */
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1ServiceToRespondToRecordLength
                                                                        = u1_ServToRespToLen;
    /* u1SubFunc                            */
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1RcvSubFunc               = u1_RecSubFunc;
    /* bRoeStart                            */
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].bRoeStart                  = (boolean)FALSE;
    /* bDefaultSesReactive                  */
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].bDefaultSesReactive        = (boolean)FALSE;

    /* Calculate each event counter */
    if( u1_OldStatus == DCM_DSP_SID86_ROE_STS_CLEAR )
    {
        Dcm_Dsp_SID86_u1NumChangeOfDataIdentfierEvents = (uint8)(Dcm_Dsp_SID86_u1NumChangeOfDataIdentfierEvents + (uint8)1U);
    }
    else
    {
        if( u1_OldSubFunc == DCM_DSP_SID86_SF07 )
        {
            Dcm_Dsp_SID86_u1NumComparisionOfValueEvents = (uint8)(Dcm_Dsp_SID86_u1NumComparisionOfValueEvents - (uint8)1U);
            Dcm_Dsp_SID86_u1NumChangeOfDataIdentfierEvents = (uint8)(Dcm_Dsp_SID86_u1NumChangeOfDataIdentfierEvents + (uint8)1U);
        }
    }
    /* Notification */
    if( u1_OldStatus != DCM_DSP_SID86_ROE_STS_STOP )
    {
        (void)Dcm_Dsp_SID86_Cnct_Sw_Roe( u1RoeEventId, DCM_EVENT_STOPPED );    /* no return check required */
        /* Stop judgment of the bus corresponding to the connection that a former state used at the time of ROE_START */
        if( ( u1_OldStatus == DCM_DSP_SID86_ROE_STS_START ) || ( u1_OldStatus == DCM_DSP_SID86_ROE_STS_START_EVENT ) )
        {
            b_ConnectionUsed = Dcm_Dsp_SID86_IsUsedConnection( u2_OldConnectionId );
            if( b_ConnectionUsed != (boolean)TRUE )
            {
                /* When a old ConnectionId overwritten is not used; of the bus is non-active, and carry it out */
                u1_ListNum = DCM_DSP_SID86_LIST_START_CNT;
                Dcm_Dsp_SID86_SetComActive( u1_ListNum, &u2_OldConnectionId, (boolean)FALSE );
            }
        }
    }
    /* Write Storage */
    Dcm_Dsp_SID86_WriteStorage( u1RoeEventId );

    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_RegEvent_Sub07                             */
/* Description   | Regist Eventtable for Subfunction07                      */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1RoeEventId   : RoeEvent ID                        */
/*               | [IN] u2ConnectionId : Connention ID                      */
/*               | [IN] pMsgContext    : Message Context                    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_RegEvent_Sub07
(
    const   uint8                                           u1RoeEventId,
    const   uint16                                          u2ConnectionId,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA )    pt_ReqData;
    uint16              u2_OldConnectionId;
    uint8               u1_ReqDataLen;
    uint8               u1_ServToRespToLen;
    uint8               u1_OldStatus;
    uint8               u1_OldSubFunc;
    uint8               u1_EventWinTime;
    uint8               u1_RecSubFunc;
    uint8               u1_Cnt;
    uint8               u1_ListNum;
    boolean             b_ConnectionUsed;

    u1_ReqDataLen       = (uint8)ptMsgContext->reqDataLen;
    u1_OldStatus        = Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1Status;
    u1_OldSubFunc       = (uint8)( Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1RcvSubFunc & DCM_DSP_SID86_SUBFUNC_MASK );
    u1_ServToRespToLen  = (uint8)( u1_ReqDataLen - ( DCM_DSP_SID86_EVENTWINDOWTIME_LEN + DCM_DSP_SID86_SF07_EVENTTYPE_LEN ) );  /* no wrap around */
    pt_ReqData          = ptMsgContext->reqData;
    u1_EventWinTime     = pt_ReqData[DCM_DSP_SID86_EVENTWINDOWTIME_OFFSET];
    u1_RecSubFunc       = Dcm_Dsp_SID86_GenerateReceivedSubFunc( DCM_DSP_SID86_SF07, ptMsgContext->msgAddInfo.suppressPosResponse );
    u2_OldConnectionId  = Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u2ConnectionId;
    /* u2ConnectionId                       */
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u2ConnectionId             = u2ConnectionId;
    Dcm_Dsp_SID86_u2ConnectionIdMirror[u1RoeEventId]                    = Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u2ConnectionId;
    /* u1ServiceToRespondToRecord           */
    for( u1_Cnt = (uint8)0U; u1_Cnt < (uint8)u1_ServToRespToLen; u1_Cnt++ )
    {
        Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1ServiceToRespondToRecord[u1_Cnt]
                                                                        = pt_ReqData[(DCM_DSP_SID86_SF07_SID_OFFSET + u1_Cnt)]; /* no wrap around */
    }
    /* u1EventTypeRecord(ComparisonValue)   */
    for( u1_Cnt = (uint8)0U; u1_Cnt < (uint8)DCM_DSP_SID86_SF07_EVENTTYPE_LEN; u1_Cnt++ )
    {
        Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1EventTypeRecord[u1_Cnt]
                                                                        = pt_ReqData[(DCM_DSP_SID86_SF07_DID_OFFSET + u1_Cnt)]; /* no wrap around */
    }
    /* u1NumberOfIdentifiedEvents           */
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1NumberOfIdentifiedEvents = (uint8)0U;
    /* u1Status                             */
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1Status                   = DCM_DSP_SID86_ROE_STS_STOP;
    /* u1EventWindow                        */
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1EventWindow              = u1_EventWinTime;
    /* u1ServiceToRespondToRecordLength     */
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1ServiceToRespondToRecordLength
                                                                        = u1_ServToRespToLen;
    /* u1SubFunc                            */
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1RcvSubFunc               = u1_RecSubFunc;
    /* bRoeStart                            */
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].bRoeStart                  = (boolean)FALSE;
    /* bDefaultSesReactive                  */
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].bDefaultSesReactive        = (boolean)FALSE;

    /* Calculate each event counter */
    if( u1_OldStatus == DCM_DSP_SID86_ROE_STS_CLEAR )
    {
        Dcm_Dsp_SID86_u1NumComparisionOfValueEvents = (uint8)(Dcm_Dsp_SID86_u1NumComparisionOfValueEvents + (uint8)1U);
    }
    else
    {
        if( u1_OldSubFunc == DCM_DSP_SID86_SF03 )
        {
            Dcm_Dsp_SID86_u1NumChangeOfDataIdentfierEvents = (uint8)(Dcm_Dsp_SID86_u1NumChangeOfDataIdentfierEvents - (uint8)1U);
            Dcm_Dsp_SID86_u1NumComparisionOfValueEvents = (uint8)(Dcm_Dsp_SID86_u1NumComparisionOfValueEvents + (uint8)1U);
        }
    }
    /* Notification */
    if( u1_OldStatus != DCM_DSP_SID86_ROE_STS_STOP )
    {
        (void)Dcm_Dsp_SID86_Cnct_Sw_Roe( u1RoeEventId, DCM_EVENT_STOPPED );    /* no return check required */
        /* Stop judgment of the bus corresponding to the connection that a former state used at the time of ROE_START */
        if( ( u1_OldStatus == DCM_DSP_SID86_ROE_STS_START ) || ( u1_OldStatus == DCM_DSP_SID86_ROE_STS_START_EVENT ) )
        {
            b_ConnectionUsed = Dcm_Dsp_SID86_IsUsedConnection( u2_OldConnectionId );
            if( b_ConnectionUsed != (boolean)TRUE )
            {
                /* When a old ConnectionId overwritten is not used; of the bus is non-active, and carry it out */
                u1_ListNum = DCM_DSP_SID86_LIST_START_CNT;
                Dcm_Dsp_SID86_SetComActive( u1_ListNum, &u2_OldConnectionId, (boolean)FALSE );
            }
        }
    }
    /* Write Storage */
    Dcm_Dsp_SID86_WriteStorage( u1RoeEventId );

    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_StartAllEvents                             */
/* Description   | Re-Start All Event Activation                            */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1SubFunc      : SubFunction                        */
/*               | [IN] u2ConnectionId : Connention ID                      */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_StartAllEvents
(
    const   uint8    u1SubFunc,
    const   uint16   u2ConnectionId
)
{
    uint16              u2_InterMessageTime;
    Dcm_SesCtrlType     u1_SesCtrlType;
    uint8               u1_NumOfRoeEvent;
    uint8               u1_Status;
    uint8               u1_Cnt;
    uint8               u1_ServToRespToRecLen;
    uint8               u1_SetupEventWindow;
    boolean             b_WaitingForTrans;
    boolean             b_RoeStart;
    boolean             b_DefSesReactive;

    u1_NumOfRoeEvent        = Dcm_Dsp_SID86_u1NumOfRoeEvent;
    u1_SesCtrlType          = DCM_DEFAULT_SESSION;

    Dcm_Dsp_SID86_u2StartRequestConnectionId    = u2ConnectionId;
    b_DefSesReactive                            = (boolean)FALSE;
    ( void )Dcm_GetSesCtrlType( &u1_SesCtrlType );      /* no return check required */
    if( u1_SesCtrlType == DCM_DEFAULT_SESSION )
    {
        b_DefSesReactive                        = (boolean)TRUE;
    }
    for( u1_Cnt = (uint8)0U; u1_Cnt < u1_NumOfRoeEvent; u1_Cnt++ )
    {
        b_RoeStart                              = (boolean)FALSE;
        u1_SetupEventWindow = Dcm_Dsp_SID86_stEventLogic[u1_Cnt].u1EventWindow;
        if( u1_SetupEventWindow == DCM_DSP_SID86_ROE_EVENT_WINDOW_INFINITE )
        {
            if( u1SubFunc == DCM_DSP_SID86_SF45 )
            {
                b_RoeStart                      = (boolean)TRUE;
            }
        }
        u1_Status = Dcm_Dsp_SID86_stEventLogic[u1_Cnt].u1Status;
        if( u1_Status == DCM_DSP_SID86_ROE_STS_STOP )
        {
            /* check the event logic registration from a tool */
            /* When there is not event logic registration, it does not change in a start state */
            u1_ServToRespToRecLen = Dcm_Dsp_SID86_stEventLogic[u1_Cnt].u1ServiceToRespondToRecordLength;
            if( u1_ServToRespToRecLen != (uint8)0U )
            {
                Dcm_Dsp_SID86_StartEvent( u1_Cnt, b_DefSesReactive, b_RoeStart );
            }
        }
        else if( u1_Status == DCM_DSP_SID86_ROE_STS_START )
        {
                Dcm_Dsp_SID86_StartEvent( u1_Cnt, b_DefSesReactive, b_RoeStart );
        }
        else if( u1_Status == DCM_DSP_SID86_ROE_STS_START_EVENT )
        {
                Dcm_Dsp_SID86_StartEvent( u1_Cnt, b_DefSesReactive, b_RoeStart );
        }
        else
        {
            /* No process */
        }
    }
    b_WaitingForTrans = Dcm_Dsp_SID86_bWaitingForTransmission;
    if( b_WaitingForTrans != (boolean)FALSE )
    {
        u2_InterMessageTime = Dcm_Dsp_SID86_u2InterMessageTime;
        /* Dcm_Dsp_SID86_u2InterMessageTime is not Zero */
        if( u2_InterMessageTime != (uint16)0U )
        {
            Dcm_Main_TmrSrv_StartTimer( DCM_M_TMRID_SID86_INTERMESSAGE, (uint32)u2_InterMessageTime );
            Dcm_Dsp_SID86_bWaitingForTransmission   = (boolean)TRUE;
        }
        else
        {
            /* For data becoming the abnormal value, reset a value explicitly */
            Dcm_Dsp_SID86_bWaitingForTransmission   = (boolean)FALSE;
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_ClearAllEvents                             */
/* Description   | Clear All Event Activation for SubFunc06                 */
/* Preconditions | None                                                     */
/* Parameters    | Node                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_ClearAllEvents
(
    void
)
{
    uint16              u2_ConnIdList[DCM_DSP_SID86_CONNID_LIST_NUM] = {0};
    uint16              u2_ConnId;
    uint8               u1_ExecEventId;
    uint8               u1_NumOfRoeEvent;
    uint8               u1_Cnt;
    uint8               u1_ListNum;
    boolean             b_IntermediateResponse;
    boolean             b_WaitingForTrans;

    u1_NumOfRoeEvent        = Dcm_Dsp_SID86_u1NumOfRoeEvent;
    /* lock */
    SchM_Enter_Dcm_Dsp_Roe();
    u1_ExecEventId          = Dcm_Dsp_SID86_u1ExecEventId;
    /* unlock */
    SchM_Exit_Dcm_Dsp_Roe();
    u1_ListNum              = (uint8)0U;

    Dcm_Dsp_SID86_u2StartRequestConnectionId    = DCM_DSP_SID86_CONID_INVALID;

    /* Dcm_Dsp_SID86_u1NumOfRoeEvent is not Invalid */
    if( u1_ExecEventId != DCM_DSP_SID86_ROE_EVENTID_INVALID )
    {
        /* Call EvtDistr for Delete ROE_EVENT */
        (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID86_SERVTORESPTO, TRUE ); /* no return check required */
        Dcm_Dsp_SID86_u1ExecEventId = DCM_DSP_SID86_ROE_EVENTID_INVALID;
    }
    b_IntermediateResponse = Dcm_Dsp_SID86_bProcessingIntermediateResponse;
    if( b_IntermediateResponse != (boolean)FALSE )
    {
        /* Call EvtDistr for Delete ROE_QUEOVER */
        (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID86_RESPQUEOVER, TRUE ); /* no return check required */
        Dcm_Dsp_SID86_bProcessingIntermediateResponse = (boolean)FALSE;
    }
    b_WaitingForTrans = Dcm_Dsp_SID86_bWaitingForTransmission;
    if( b_WaitingForTrans == (boolean)TRUE )
    {
        Dcm_Main_TmrSrv_StopTimer( DCM_M_TMRID_SID86_INTERMESSAGE );
        Dcm_Dsp_SID86_bWaitingForTransmission = (boolean)FALSE;
    }

    Dcm_Dsp_SID86_u1NumChangeOfDataIdentfierEvents          = (uint8)0U;
    Dcm_Dsp_SID86_u1NumComparisionOfValueEvents             = (uint8)0U;
    Dcm_Dsp_SID86_u1NumberOfStoredDTCStatusChangedEvents    = (uint8)0U;

    for( u1_Cnt = (uint8)0U; u1_Cnt < u1_NumOfRoeEvent; u1_Cnt++ )
    {
        /* Clear all event entry data for clearResponseOnEvent request */
        u2_ConnId = Dcm_Dsp_SID86_stEventLogic[u1_Cnt].u2ConnectionId;
        Dcm_Dsp_SID86_MakeConnectionIdList( u2_ConnId, &u1_ListNum, &u2_ConnIdList[DCM_DSP_SID86_LIST_START_POS] );
        Dcm_Dsp_SID86_ClearEvent( u1_Cnt );
    }

    if( u1_ListNum != (uint8)0U )
    {
        /* SetComActive set FALSE */
        Dcm_Dsp_SID86_SetComActive( u1_ListNum, &u2_ConnIdList[DCM_DSP_SID86_LIST_START_POS], (boolean)FALSE );
    }

    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_ClearEvent                                 */
/* Description   | Clear Eventtable by Event ID                             */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1RoeEventId   : RoeEvent ID                        */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_ClearEvent
(
    const   uint8       u1RoeEventId
)
{
    uint8               u1_OldStatus;
    uint8               u1_Cnt;
    boolean             b_DTCStatusChangeEvent;

    u1_OldStatus        = Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1Status;

    /* u2ConnectionId                       */
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u2ConnectionId             = DCM_DSP_SID86_CONID_INVALID;
    Dcm_Dsp_SID86_u2ConnectionIdMirror[u1RoeEventId]                    = Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u2ConnectionId;
    /* u1ServiceToRespondToRecord           */
    for( u1_Cnt = (uint8)0U; u1_Cnt < DCM_DSP_SID86_SERVICETORESPONDTORECORD_MAX; u1_Cnt++ )
    {
        Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1ServiceToRespondToRecord[u1_Cnt]
                                                                        = (uint8)0U;
    }
    /* u1EventTypeRecord                    */
    for( u1_Cnt = (uint8)0U; u1_Cnt < (uint8)DCM_DSP_SID86_EVENTTYPERECORD_MAX; u1_Cnt++ )
    {
        Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1EventTypeRecord[u1_Cnt] = (uint8)0U;
    }
    /* u1NumberOfIdentifiedEvents           */
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1NumberOfIdentifiedEvents    = (uint8)0U;
    /* u1Status                             */
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1Status                      = DCM_DSP_SID86_ROE_STS_CLEAR;
    /* u1EventWindow                        */
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1EventWindow                 = DCM_DSP_SID86_EVWIN_INVALID;
    /* u1ServiceToRespondToRecordLength     */
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1ServiceToRespondToRecordLength
                                                                        = (uint8)0U;
    /* u1RcvSubFunc                         */
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1RcvSubFunc                  = DCM_DSP_SID86_SUBFUNC_INVALID;
    /* bRoeStart                            */
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].bRoeStart                     = (boolean)FALSE;
    /* bDefaultSesReactive                  */
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].bDefaultSesReactive           = (boolean)FALSE;

    /* Notification */
    if( u1_OldStatus != DCM_DSP_SID86_ROE_STS_CLEAR )
    {
        (void)Dcm_Dsp_SID86_Cnct_Sw_Roe( u1RoeEventId, DCM_EVENT_CLEARED );    /* no return check required */
        b_DTCStatusChangeEvent = Dcm_Dsp_SID86_IsDTCEvent( u1RoeEventId );
        if( b_DTCStatusChangeEvent == (boolean)TRUE )
        {
            Dem_DcmControlDTCStatusChangedNotification( (boolean)FALSE );
        }
    }
    /* Write Storage */
    Dcm_Dsp_SID86_WriteStorage( u1RoeEventId );

    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_SendServToRespTo                           */
/* Description   | Send ServiceToRespondTo Request                          */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1TargetRoeEventId      : Target RoeEvent ID        */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_SendServToRespTo
(
    const   uint8   u1TargetRoeEventId
)
{
    P2VAR( Dcm_MsgItemType, AUTOMATIC, DCM_APPL_DATA )    pt_Dcm_Msg;
    Dcm_MsgLenType      u4_MsgLen;
    uint16              u2_ConnectionId;
    uint16              u2_InterMessageTime;
    uint8               u1_DTCStsChgNum;
    uint8               u1_NextRoeEventId;
    Dcm_StatusType      u1_RetRespOnEvent;
    boolean             b_DTCEvent;

    pt_Dcm_Msg          = &(Dcm_Dsp_SID86_stEventLogic[u1TargetRoeEventId].u1ServiceToRespondToRecord[0]);
    u4_MsgLen           = Dcm_Dsp_SID86_stEventLogic[u1TargetRoeEventId].u1ServiceToRespondToRecordLength;
    u2_ConnectionId     = Dcm_Dsp_SID86_stEventLogic[u1TargetRoeEventId].u2ConnectionId;

    /* DslInternal_ResponseOnOneEvent */
    u1_RetRespOnEvent   = DslInternal_ResponseOnOneEvent( pt_Dcm_Msg, u4_MsgLen, u2_ConnectionId );
    if( u1_RetRespOnEvent == (Dcm_StatusType)DCM_E_OK )
    {
    /* DslInternal_ResponseOnOneEvent returns OK */
        u2_InterMessageTime = Dcm_Dsp_SID86_u2InterMessageTime;
        /* Dcm_Dsp_SID86_u2InterMessageTime is not Zero */
        if( u2_InterMessageTime != (uint16)0U )
        {
            Dcm_Main_TmrSrv_StartTimer( DCM_M_TMRID_SID86_INTERMESSAGE, (uint32)u2_InterMessageTime );
            Dcm_Dsp_SID86_bWaitingForTransmission   = (boolean)TRUE;
        }

        b_DTCEvent = Dcm_Dsp_SID86_IsDTCEvent( u1TargetRoeEventId );
        if( b_DTCEvent == (boolean)TRUE )
        {
            /* Event for DTCStatusChange */
            u1_DTCStsChgNum = Dcm_Dsp_SID86_u1NumberOfStoredDTCStatusChangedEvents;
            if( u1_DTCStsChgNum > (uint8)0U )
            {
                /* decrement counter of DTCStatusChangedEvent */
                u1_DTCStsChgNum = (uint8)(u1_DTCStsChgNum - (uint8)1U);
                Dcm_Dsp_SID86_u1NumberOfStoredDTCStatusChangedEvents = u1_DTCStsChgNum;
            }
            if( u1_DTCStsChgNum == (uint8)0U )
            {
                /* counter of DTCStatusChangedEvent is Zero */
                /* Update RoeStatus to START */
                Dcm_Dsp_SID86_stEventLogic[u1TargetRoeEventId].u1Status = DCM_DSP_SID86_ROE_STS_START;
                /* Update data in the next triggered event ID */
                Dcm_Dsp_SID86_SetNextTriggerEvent();
            }
        }
        else
        {
            /* Event for DidChange */
            /* Update RoeStatus to START */
            Dcm_Dsp_SID86_stEventLogic[u1TargetRoeEventId].u1Status = DCM_DSP_SID86_ROE_STS_START;
            /* Update data in the next triggered event ID */
            Dcm_Dsp_SID86_SetNextTriggerEvent();
        }
        u1_NextRoeEventId = Dcm_Dsp_SID86_u1ExecEventId;
        if( u1_NextRoeEventId != DCM_DSP_SID86_ROE_EVENTID_INVALID )
        {
            /* Next Event Triggered */
            (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID86_SERVTORESPTO ); /* no return check required */
        }
    }
    else
    {
    /* DslInternal_ResponseOnOneEvent returns DCM_E_ROE_NOT_ACCEPTED */
        /* Call EvtDistr for send ROE_EVENT */
        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID86_SERVTORESPTO ); /* no return check required */
    }

    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_SetNextTriggerEvent                        */
/* Description   | Set Next Triggered Event to Dcm_Dsp_SID86_u1ExecEventId  */
/* Preconditions | None                                                     */
/* Parameters    | Node                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_SetNextTriggerEvent
(
    void
)
{
    uint16              u2_ConnId;
    uint16              u2_ConnIdMirror;
    uint8               u1_Status;
    uint8               u1_Cnt;
    uint8               u1_ExecRoeEventId;
    uint8               u1_CurRoeEventId;
    uint8               u1_NextRoeEventId;
    uint8               u1_NumOfRoeEvent;
    boolean             b_UpdateExecRoeEventId;

    u1_NumOfRoeEvent        = Dcm_Dsp_SID86_u1NumOfRoeEvent;
    /* lock */
    SchM_Enter_Dcm_Dsp_Roe();
    u1_ExecRoeEventId       = Dcm_Dsp_SID86_u1ExecEventId;
    /* unlock */
    SchM_Exit_Dcm_Dsp_Roe();

    if( u1_ExecRoeEventId != DCM_DSP_SID86_ROE_EVENTID_INVALID )
    {
        if( u1_ExecRoeEventId < u1_NumOfRoeEvent )
        {
            u1_CurRoeEventId = u1_ExecRoeEventId;
        }
        else
        {
            u1_CurRoeEventId = (uint8)0U;
        }

        b_UpdateExecRoeEventId  = (boolean)FALSE;
        for( u1_Cnt = (uint8)0U; u1_Cnt < u1_NumOfRoeEvent; u1_Cnt++ )
        {
            u1_Status       = Dcm_Dsp_SID86_stEventLogic[u1_CurRoeEventId].u1Status;
            u2_ConnId       = Dcm_Dsp_SID86_stEventLogic[u1_CurRoeEventId].u2ConnectionId;
            u2_ConnIdMirror = Dcm_Dsp_SID86_u2ConnectionIdMirror[u1_CurRoeEventId];
            if( u1_Status == DCM_DSP_SID86_ROE_STS_START_EVENT )
            {
                if( u2_ConnId != DCM_DSP_SID86_CONID_INVALID )
                {
                    if( u2_ConnId == u2_ConnIdMirror )
                    {
                        Dcm_Dsp_SID86_u1ExecEventId = u1_CurRoeEventId;
                        b_UpdateExecRoeEventId = (boolean)TRUE;
                        break;
                    }
                }
            }
            u1_NextRoeEventId   = Dcm_Dsp_SID86_GetNextRoeEventId( u1_CurRoeEventId );
            u1_CurRoeEventId    = u1_NextRoeEventId;
        }
        if( b_UpdateExecRoeEventId != (boolean)TRUE )
        {
            Dcm_Dsp_SID86_u1ExecEventId = DCM_DSP_SID86_ROE_EVENTID_INVALID;
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_GetNextRoeEventId                          */
/* Description   | Get Next RoeEventId                                      */
/* Parameters    | [IN] u1StartRoeEventId : Search Start RoeEvent ID        */
/* Parameters    | Node                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( uint8, DCM_CODE ) Dcm_Dsp_SID86_GetNextRoeEventId
(
    const   uint8   u1StartRoeEventId
)
{
    uint8               u1_NextRoeEventId;
    uint8               u1_NumOfRoeEvent;

    u1_NumOfRoeEvent    = Dcm_Dsp_SID86_u1NumOfRoeEvent;
    u1_NextRoeEventId   = DCM_DSP_SID86_ROE_EVENTID_MIN;

    if( u1StartRoeEventId < u1_NumOfRoeEvent )
    {
        /* set next u1_NextRoeEventId (Increment) */
        u1_NextRoeEventId       = u1StartRoeEventId;
        u1_NextRoeEventId = (uint8)(u1_NextRoeEventId + (uint8)1U);
        if( u1_NextRoeEventId == u1_NumOfRoeEvent )
        {
            /* When it arrives at the maximum, set the minimum */
            u1_NextRoeEventId   = DCM_DSP_SID86_ROE_EVENTID_MIN;
        }
    }

    return u1_NextRoeEventId;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_StopAllEvents                              */
/* Description   | Stop All Event Activation                                */
/* Preconditions | None                                                     */
/* Parameters    | Node                                                     */
/* Return Value  | Node                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_StopAllEvents
(
    void
)
{
    uint16              u2_ConnIdList[DCM_DSP_SID86_CONNID_LIST_NUM] = {0};
    uint16              u2_ConnId;
    uint8               u1_ExecEventId;
    uint8               u1_NumOfRoeEvent;
    uint8               u1_Status;
    uint8               u1_Cnt;
    uint8               u1_ListNum;

    u1_NumOfRoeEvent        = Dcm_Dsp_SID86_u1NumOfRoeEvent;
    /* lock */
    SchM_Enter_Dcm_Dsp_Roe();
    u1_ExecEventId          = Dcm_Dsp_SID86_u1ExecEventId;
    /* unlock */
    SchM_Exit_Dcm_Dsp_Roe();
    u1_ListNum              = (uint8)0U;

    Dcm_Dsp_SID86_u2StartRequestConnectionId    = DCM_DSP_SID86_CONID_INVALID;
    /* Dcm_Dsp_SID86_u1ExecEventId is not Invalid */
    if( u1_ExecEventId != DCM_DSP_SID86_ROE_EVENTID_INVALID )
    {
        /* Call EvtDistr for Delete ROE_EVENT */
        (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID86_SERVTORESPTO, TRUE ); /* no return check required */
        Dcm_Dsp_SID86_u1ExecEventId = DCM_DSP_SID86_ROE_EVENTID_INVALID;
    }

    for( u1_Cnt = (uint8)0U; u1_Cnt < u1_NumOfRoeEvent; u1_Cnt++ )
    {
        u1_Status = Dcm_Dsp_SID86_stEventLogic[u1_Cnt].u1Status;
        if( u1_Status == DCM_DSP_SID86_ROE_STS_START_EVENT )
        {
            u2_ConnId   = Dcm_Dsp_SID86_stEventLogic[u1_Cnt].u2ConnectionId;
            Dcm_Dsp_SID86_MakeConnectionIdList( u2_ConnId, &u1_ListNum, &u2_ConnIdList[DCM_DSP_SID86_LIST_START_POS] );
            Dcm_Dsp_SID86_StopEvent( u1_Cnt );
        }
        else if( u1_Status == DCM_DSP_SID86_ROE_STS_START )
        {
            u2_ConnId   = Dcm_Dsp_SID86_stEventLogic[u1_Cnt].u2ConnectionId;
            Dcm_Dsp_SID86_MakeConnectionIdList( u2_ConnId, &u1_ListNum, &u2_ConnIdList[DCM_DSP_SID86_LIST_START_POS] );
            Dcm_Dsp_SID86_StopEvent( u1_Cnt );
        }
        else if( u1_Status == DCM_DSP_SID86_ROE_STS_STOP )
        {
            Dcm_Dsp_SID86_StopEvent( u1_Cnt );
        }
        else
        {
            /* No process */
        }
    }
    if( u1_ListNum != (uint8)0U )
    {
        /* SetComActive set FALSE */
        Dcm_Dsp_SID86_SetComActive( u1_ListNum, &u2_ConnIdList[DCM_DSP_SID86_LIST_START_POS], (boolean)FALSE );
    }

    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_StopAllEventsSes                           */
/* Description   | Stop All Event Activation                                */
/* Preconditions | None                                                     */
/* Parameters    | [IN] bDefaultSesReAct  : ReActive on Default Session     */
/* Return Value  | Node                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_StopAllEventsSes
(
    const   boolean   bDefaultSesReAct
)
{
    uint8               u1_ExecEventId;
    uint8               u1_NumOfRoeEvent;
    uint8               u1_Status;
    uint8               u1_Cnt;

    u1_NumOfRoeEvent        = Dcm_Dsp_SID86_u1NumOfRoeEvent;
    /* lock */
    SchM_Enter_Dcm_Dsp_Roe();
    u1_ExecEventId          = Dcm_Dsp_SID86_u1ExecEventId;
    /* unlock */
    SchM_Exit_Dcm_Dsp_Roe();

    /* Dcm_Dsp_SID86_u1ExecEventId is not Invalid */
    if( u1_ExecEventId != DCM_DSP_SID86_ROE_EVENTID_INVALID )
    {
        /* Call EvtDistr for Delete ROE_EVENT */
        (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID86_SERVTORESPTO, TRUE ); /* no return check required */
        Dcm_Dsp_SID86_u1ExecEventId = DCM_DSP_SID86_ROE_EVENTID_INVALID;
    }

    for( u1_Cnt = (uint8)0U; u1_Cnt < u1_NumOfRoeEvent; u1_Cnt++ )
    {
        u1_Status = Dcm_Dsp_SID86_stEventLogic[u1_Cnt].u1Status;
        if( u1_Status == DCM_DSP_SID86_ROE_STS_START_EVENT )
        {
            Dcm_Dsp_SID86_StopEventSes( u1_Cnt, bDefaultSesReAct );
        }
        else if( u1_Status == DCM_DSP_SID86_ROE_STS_START ) 
        {
            Dcm_Dsp_SID86_StopEventSes( u1_Cnt, bDefaultSesReAct );
        }
        else
        {
            /* No process */
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_StopEvent                                  */
/* Description   | Stop Appointed Event Activation                          */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1RoeEventId  : RoeEvent ID                         */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_StopEvent
(
    const   uint8   u1RoeEventId
)
{
    uint8           u1_OldStatus;
    boolean         b_DTCStatusChangeEvent;

    u1_OldStatus    = Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1Status;

    /* ConnectionId                         no change   */
    /* u1ServiceToRespondToRecord           no change   */
    /* u1EventTypeRecord                    no change   */
    /* u1NumberOfIdentifiedEvents           clear       */
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1NumberOfIdentifiedEvents    = (uint8)0U;
    /* u1Status                             change stop */
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1Status                      = DCM_DSP_SID86_ROE_STS_STOP;
    /* u1EventWindow                        no change   */
    /* u1ServiceToRespondToRecordLength     no change   */
    /* bRoeStart                            change      */
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].bRoeStart                     = (boolean)FALSE;
    /* bDefaultSesReactive                  change      */
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].bDefaultSesReactive           = (boolean)FALSE;
    
    /* Notification */
    if( u1_OldStatus != DCM_DSP_SID86_ROE_STS_STOP )
    {
        (void)Dcm_Dsp_SID86_Cnct_Sw_Roe( u1RoeEventId, DCM_EVENT_STOPPED );    /* no return check required */
        b_DTCStatusChangeEvent = Dcm_Dsp_SID86_IsDTCEvent( u1RoeEventId );
        if( b_DTCStatusChangeEvent == (boolean)TRUE )
        {
            Dem_DcmControlDTCStatusChangedNotification( (boolean)FALSE );
        }
    }
    /* Write Storage */
    Dcm_Dsp_SID86_WriteStorage( u1RoeEventId );

    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_StopEventSes                               */
/* Description   | Stop Appointed Event Activation                          */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1RoeEventId     : RoeEvent ID                      */
/*               | [IN] bDefaultSesReAct : ReActive on Default Session      */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_StopEventSes
(
    const   uint8   u1RoeEventId,
    const   boolean bDefaultSesReAct
)
{
    uint8           u1_OldStatus;
    boolean         b_DTCStatusChangeEvent;

    u1_OldStatus    = Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1Status;

    /* ConnectionId                         no change   */
    /* u1ServiceToRespondToRecord           no change   */
    /* u1EventTypeRecord                    no change   */
    /* u1NumberOfIdentifiedEvents           clear       */
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1NumberOfIdentifiedEvents    = (uint8)0U;
    /* u1Status                             change stop */
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1Status                      = DCM_DSP_SID86_ROE_STS_STOP;
    /* u1EventWindow                        no change   */
    /* u1ServiceToRespondToRecordLength     no change   */
    /* bRoeStart                            no change   */
    /* bDefaultSesReactive                  change      */
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].bDefaultSesReactive           = bDefaultSesReAct;
    
    /* Notification */
    if( u1_OldStatus != DCM_DSP_SID86_ROE_STS_STOP )
    {
        (void)Dcm_Dsp_SID86_Cnct_Sw_Roe( u1RoeEventId, DCM_EVENT_STOPPED );    /* no return check required */
        b_DTCStatusChangeEvent = Dcm_Dsp_SID86_IsDTCEvent( u1RoeEventId );
        if( b_DTCStatusChangeEvent == (boolean)TRUE )
        {
            Dem_DcmControlDTCStatusChangedNotification( (boolean)FALSE );
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_ReStartAllEvents                           */
/* Description   | Re-Start All Event Activation                            */
/* Preconditions | None                                                     */
/* Parameters    | Node                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_ReStartAllEvents
(
    void
)
{
    uint16              u2_InterMessageTime;
    uint8               u1_NumOfRoeEvent;
    uint8               u1_Status;
    uint8               u1_Cnt;
    boolean             b_DefaultSesReAct;
    boolean             b_WaitingForTrans;

    u1_NumOfRoeEvent        = Dcm_Dsp_SID86_u1NumOfRoeEvent;

    for( u1_Cnt = (uint8)0U; u1_Cnt < u1_NumOfRoeEvent; u1_Cnt++ )
    {
        u1_Status = Dcm_Dsp_SID86_stEventLogic[u1_Cnt].u1Status;
        if( u1_Status == DCM_DSP_SID86_ROE_STS_STOP )
        {
            b_DefaultSesReAct = Dcm_Dsp_SID86_stEventLogic[u1_Cnt].bDefaultSesReactive;
            if( b_DefaultSesReAct == (boolean)TRUE )
            {
                Dcm_Dsp_SID86_StartEventSes( u1_Cnt );
            }
        }
    }
    /* INTERMESSAGE timer and bWaitingForTransmission data set again */
    b_WaitingForTrans = Dcm_Dsp_SID86_bWaitingForTransmission;
    if( b_WaitingForTrans != (boolean)FALSE )
    {
        u2_InterMessageTime = Dcm_Dsp_SID86_u2InterMessageTime;
        /* Dcm_Dsp_SID86_u2InterMessageTime is not Zero */
        if( u2_InterMessageTime != (uint16)0U )
        {
            Dcm_Main_TmrSrv_StartTimer( DCM_M_TMRID_SID86_INTERMESSAGE, (uint32)u2_InterMessageTime );
            Dcm_Dsp_SID86_bWaitingForTransmission   = (boolean)TRUE;
        }
        else
        {
            /* For data becoming the abnormal value, reset a value explicitly */
            Dcm_Dsp_SID86_bWaitingForTransmission   = (boolean)FALSE;
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_StartEvent                                 */
/* Description   | Start Appointed Event Activation                         */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1RoeEventId     : RoeEvent ID                      */
/*               | [IN] bDefaultSesReAct : ReActive on Default Session      */
/*               | [IN] bRoeStart        : ReActive on ReStart              */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_StartEvent
(
    const   uint8       u1RoeEventId,
    const   boolean     bDefaultSesReactive,
    const   boolean     bRoeStart
)
{
    uint8           u1_OldStatus;
    boolean         b_DTCStatusChangeEvent;

    u1_OldStatus    = Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1Status;

    /* bRoeStart                            no change   */
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].bRoeStart                         = bRoeStart;
    /* bDefaultSesReactive                  change      */
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].bDefaultSesReactive               = bDefaultSesReactive;
    if( u1_OldStatus == DCM_DSP_SID86_ROE_STS_STOP )
    {
        /* ConnectionId                         no change   */
        /* u1ServiceToRespondToRecord           no change   */
        /* u1EventTypeRecord                    no change   */
        /* u1NumberOfIdentifiedEvents           clear       */
        Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1NumberOfIdentifiedEvents    = (uint8)0U;
        /* u1Status                             change stop */
        Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1Status                      = DCM_DSP_SID86_ROE_STS_START;
        /* u1EventWindow                        no change   */
        /* u1ServiceToRespondToRecordLength     no change   */

        (void)Dcm_Dsp_SID86_Cnct_Sw_Roe( u1RoeEventId, DCM_EVENT_STARTED );    /* no return check required */
        b_DTCStatusChangeEvent = Dcm_Dsp_SID86_IsDTCEvent( u1RoeEventId );
        if( b_DTCStatusChangeEvent == (boolean)TRUE )
        {
            Dem_DcmControlDTCStatusChangedNotification( (boolean)TRUE );
        }
    }
    /* Write Storage */
    Dcm_Dsp_SID86_WriteStorage( u1RoeEventId );

    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_StartEventSes                              */
/* Description   | Start Appointed Event Activation                         */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1RoeEventId     : RoeEvent ID                      */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_StartEventSes
(
    const   uint8   u1RoeEventId
)
{
    uint8           u1_OldStatus;
    boolean         b_DTCStatusChangeEvent;

    u1_OldStatus    = Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1Status;

    if( u1_OldStatus == DCM_DSP_SID86_ROE_STS_STOP )
    {
        /* ConnectionId                         no change   */
        /* u1ServiceToRespondToRecord           no change   */
        /* u1EventTypeRecord                    no change   */
        /* u1NumberOfIdentifiedEvents           clear       */
        Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1NumberOfIdentifiedEvents   = (uint8)0U;
        /* u1Status                             change stop */
        Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1Status                     = DCM_DSP_SID86_ROE_STS_START;
        /* u1EventWindow                        no change   */
        /* u1ServiceToRespondToRecordLength     no change   */
        /* bRoeStart                            no change   */
        /* bDefaultSesReactive                  change      */
        Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].bDefaultSesReactive          = (boolean)TRUE;

        (void)Dcm_Dsp_SID86_Cnct_Sw_Roe( u1RoeEventId, DCM_EVENT_STARTED );    /* no return check required */
        b_DTCStatusChangeEvent = Dcm_Dsp_SID86_IsDTCEvent( u1RoeEventId );
        if( b_DTCStatusChangeEvent == (boolean)TRUE )
        {
            Dem_DcmControlDTCStatusChangedNotification( (boolean)TRUE );
        }
    }
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_Sub00_InitialProc                          */
/* Description   | Initial process of SID86 Sub00 request                   */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext   : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_DSP_SID86_NVM_USE == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub00_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    Dcm_MsgContextType              st_Dcm_MsgContext;
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_RetCheckCondition;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;
    boolean                         b_SendNegResFlag;

    u1_RetVal               = (Std_ReturnType)E_OK;
    u1_ErrorCode            = (Dcm_NegativeResponseCodeType)0x00U;
    b_SendNegResFlag        = (boolean)FALSE;
    st_Dcm_MsgContext       = *ptMsgContext;

    /* Set Dcm_Dsp_Main_bIdleFlag in FALSE */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );

    /* Check Request Message Length */
    if( st_Dcm_MsgContext.reqDataLen == DCM_DSP_SID86_SF00_REQ_LEN )
    {
        /* Check Request Message Parameter - Skip */
        /* Check Condition of Acceptance */
        u1_RetCheckCondition = Dcm_Dsp_SID86_Sub00_CheckCondition( &u1_ErrorCode );
        if( u1_RetCheckCondition == (Std_ReturnType)E_OK )
        {
            /* Excute Request Message */
            Dcm_Dsp_SID86_StopAllEvents();
        }
        else
        {
            b_SendNegResFlag = (boolean)TRUE;
        }
    }
    else
    {
        /* NRC0x13 */
        b_SendNegResFlag = (boolean)TRUE;
        u1_ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }

    if( b_SendNegResFlag == (boolean)TRUE )
    {
        /* Negative response */
        Dcm_Dsp_MsgMaker_SendNegRes( &st_Dcm_MsgContext, u1_ErrorCode );
    }
    else
    {
        Dcm_Dsp_SID86_EditPosRes( DCM_DSP_SID86_SF00, &st_Dcm_MsgContext );
        Dcm_Dsp_MsgMaker_SendPosRes( &st_Dcm_MsgContext );
    }

    return u1_RetVal;
}
#endif /* DCM_DSP_SID86_NVM_USE == STD_ON */
#if ( DCM_DSP_SID86_NVM_USE == STD_OFF )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub00_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    Dcm_MsgContextType              st_Dcm_MsgContext;
    Std_ReturnType                  u1_RetVal;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;
    boolean                         b_SendNegResFlag;

    u1_RetVal               = (Std_ReturnType)E_OK;
    b_SendNegResFlag        = (boolean)FALSE;
    st_Dcm_MsgContext       = *ptMsgContext;

    /* Set Dcm_Dsp_Main_bIdleFlag in FALSE */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );

    /* Check Request Message Length */
    if( st_Dcm_MsgContext.reqDataLen == DCM_DSP_SID86_SF00_REQ_LEN )
    {
        /* Check Request Message Parameter - Skip */
        /* Check Condition of Acceptance - Skip */
        /* Excute Request Message */
         Dcm_Dsp_SID86_StopAllEvents();
    }
    else
    {
        /* NRC0x13 */
        b_SendNegResFlag = (boolean)TRUE;
        u1_ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }

    if( b_SendNegResFlag == (boolean)TRUE )
    {
        /* Negative response */
        Dcm_Dsp_MsgMaker_SendNegRes( &st_Dcm_MsgContext, u1_ErrorCode );
    }
    else
    {
        Dcm_Dsp_SID86_EditPosRes( DCM_DSP_SID86_SF00, &st_Dcm_MsgContext );
        Dcm_Dsp_MsgMaker_SendPosRes( &st_Dcm_MsgContext );
    }

    return u1_RetVal;
}
#endif /* DCM_DSP_SID86_NVM_USE == STD_OFF */


#if ( DCM_DSP_SID86_NVM_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_Sub00_CheckCondition                       */
/* Description   | Check condition process of SID86 Sub00 request           */
/* Preconditions | None                                                     */
/* Parameters    | [OUT] ptErrorCode    : Negative Response Code            */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   E_NOT_OK          : Processing not normal              */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub00_CheckCondition
(
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
)
{
    Std_ReturnType                  u1_RetVal;
    boolean                         b_NvmReadComp;

    u1_RetVal           = (Std_ReturnType)E_OK;
    *ptErrorCode        = (Dcm_NegativeResponseCodeType)0x00U;

    b_NvmReadComp = Dcm_Dsp_SID86_GetReadStorageCompleteFlag();
    if( b_NvmReadComp != (boolean)TRUE )
    {
        u1_RetVal       = (Std_ReturnType)E_NOT_OK;
        /* NRC = 0x22 */
        *ptErrorCode    = DCM_E_CONDITIONSNOTCORRECT;
    }

    return u1_RetVal;
}
#endif /* DCM_DSP_SID86_NVM_USE == STD_ON */


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_Sub40_InitialProc                          */
/* Description   | Initial process of SID86 Sub40 request                   */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext   : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub40_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    Dcm_MsgContextType              st_Dcm_MsgContext;
    Std_ReturnType                  u1_RetVal;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;

    u1_RetVal               = (Std_ReturnType)E_OK;
    st_Dcm_MsgContext       = *ptMsgContext;

    /* Set Dcm_Dsp_Main_bIdleFlag in FALSE */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );

    /* Check Request Message Length */
    if( st_Dcm_MsgContext.reqDataLen == DCM_DSP_SID86_SF40_REQ_LEN )
    {
        /* NRC0x31 : the storeEvent bit is set and a SubFunction different to startResponseOnEvent was requested */
        u1_ErrorCode = DCM_E_REQUESTOUTOFRANGE;
    }
    else
    {
        /* NRC0x13 */
        u1_ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }

    /* Negative response */
    Dcm_Dsp_MsgMaker_SendNegRes( &st_Dcm_MsgContext, u1_ErrorCode );

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_Sub01_InitialProc                          */
/* Description   | Initial process of SID86 Sub00 request                   */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext   : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub01_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    Dcm_MsgContextType              st_Dcm_MsgContext;
    uint16                          u2_ConnectionId;
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_RetCheckCondition;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;
    uint8                           u1_RoeEventId;
    boolean                         b_SendNegResFlag;

    u1_RetVal               = (Std_ReturnType)E_OK;
    u1_ErrorCode            = (Dcm_NegativeResponseCodeType)0x00U;
    b_SendNegResFlag        = (boolean)FALSE;
    st_Dcm_MsgContext       = *ptMsgContext;
    u2_ConnectionId         = (uint16)0U;
    u1_RoeEventId           = DCM_DSP_SID86_ROE_EVENTID_INVALID;

    /* Set Dcm_Dsp_Main_bIdleFlag in FALSE */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );

    /* Check Request Message Length */
    if( st_Dcm_MsgContext.reqDataLen >= DCM_DSP_SID86_SF01_REQ_MIN_LEN )
    {
        /* Get Connection Id */
        (void)Dcm_GetActiveProtocol( NULL_PTR, &u2_ConnectionId, NULL_PTR ); /* no return check required */

        u1_RetCheckCondition = Dcm_Dsp_SID86_Sub01_CheckCondition( u2_ConnectionId, &st_Dcm_MsgContext, &u1_RoeEventId, &u1_ErrorCode );
        if( u1_RetCheckCondition == (Std_ReturnType)E_OK )
        {
            /* Regist Event */
            Dcm_Dsp_SID86_RegEvent_Sub01( u1_RoeEventId, u2_ConnectionId, &st_Dcm_MsgContext );
        }
        else
        {
            b_SendNegResFlag = (boolean)TRUE;
        }
    }
    else
    {
        /* NRC0x13 */
        b_SendNegResFlag = (boolean)TRUE;
        u1_ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }

    if( b_SendNegResFlag == (boolean)TRUE )
    {
        /* Negative response */
        Dcm_Dsp_MsgMaker_SendNegRes( &st_Dcm_MsgContext, u1_ErrorCode );
    }
    else
    {
        Dcm_Dsp_SID86_EditPosRes( DCM_DSP_SID86_SF01, &st_Dcm_MsgContext );
        Dcm_Dsp_MsgMaker_SendPosRes( &st_Dcm_MsgContext );
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_Sub01_CheckCondition                       */
/* Description   | Check condition process of SID86 Sub01 request           */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u2ConnectionId : Connection ID                      */
/*               | [IN] ptMsgContext   : Message Context(send data info)    */
/*               | [OUT]ptRoeEventId   : RoeEvent ID                        */
/*               | [OUT]ptErrorCode    : Negative Response Code             */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   E_NOT_OK          : Processing not normal              */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_DSP_SID86_NVM_USE == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub01_CheckCondition
(
    const uint16                                                    u2ConnectionId,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA )         ptMsgContext,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA )                        ptRoeEventId,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
)
{
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA ) pt_EventTypeRecord;
    Dcm_MsgLenType                  u4_ServiceToRespondToRecordLen;
    uint16                          u2_RxPduId;
    uint8                           u1_EventWindowTime;
    uint8                           u1_RoeEventId;
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_RetChkSIDSupport;
    Std_ReturnType                  u1_RetRoeCond;
    Dcm_NegativeResponseCodeType    u1_Nrc;
    boolean                         b_SupportFlg;
    boolean                         b_EventStart;
    boolean                         b_NvmReadComp;

    u1_RetVal               = (Std_ReturnType)E_OK;
    u1_RetChkSIDSupport     = (Std_ReturnType)E_NOT_OK;
    u1_Nrc                  = DCM_E_GENERALREJECT;              /* 0x10 */
    u1_RoeEventId           = Dcm_Dsp_SID86_u1DTCStatusChangedEventId;
    *ptErrorCode            = (Dcm_NegativeResponseCodeType)0x00U;
    *ptRoeEventId           = DCM_DSP_SID86_ROE_EVENTID_INVALID;

    /* Check whether eventWindowTime exist or not in DcmDspRoeEventWindowTime */
    u1_EventWindowTime = ptMsgContext->reqData[DCM_DSP_SID86_EVENTWINDOWTIME_OFFSET];

    /* Check whether eventWindowTime exist or not in DcmDspRoeEventWindowTime */
    b_SupportFlg = Dcm_Dsp_SID86_IsSupportEventWindowTime( u1_EventWindowTime );
    if( b_SupportFlg == (boolean)TRUE )
    {
        if( u1_RoeEventId != DCM_DSP_SID86_ROE_EVENTID_INVALID )
        {
            /* Get ServiceToRespondToRecord length */
            u4_ServiceToRespondToRecordLen = ( ptMsgContext->reqDataLen - (Dcm_MsgLenType)DCM_DSP_SID86_EVENTWINDOWTIME_LEN - (Dcm_MsgLenType)DCM_DSP_SID86_DTCSTATUSMASK_LEN );    /* no wrap around */
            /* Check the limit of ServiceToRespondToRecord length */
            if( u4_ServiceToRespondToRecordLen <= Dcm_Dsp_SID86_stRoeEvent[u1_RoeEventId].u1ServToRespToRecLen )
            {
                /* Get PduId */
                u2_RxPduId = ptMsgContext->dcmRxPduId;
                u1_RetChkSIDSupport = Dcm_Dsp_SID86_CheckServSupport( &ptMsgContext->reqData[DCM_DSP_SID86_SF01_SID_OFFSET], u4_ServiceToRespondToRecordLen, u2_RxPduId );
            }
        }
    }

    /* Check ServiceToRespondToRecord) */
    if( u1_RetChkSIDSupport == (Std_ReturnType)E_OK )
    {
        pt_EventTypeRecord  = &ptMsgContext->reqData[DCM_DSP_SID86_DTCSTATUSMASK_OFFSET];
        u1_RetRoeCond       = Dcm_Dsp_SID86_CheckRoeCondition( DCM_DSP_SID86_SF01, u1_EventWindowTime, pt_EventTypeRecord, (uint8)DCM_DSP_SID86_SF01_EVENTTYPE_LEN, &u1_Nrc );

        if( u1_RetRoeCond == (Std_ReturnType)E_OK )
        {
            b_NvmReadComp = Dcm_Dsp_SID86_GetReadStorageCompleteFlag();
            if( b_NvmReadComp == (boolean)TRUE )
            {
                b_EventStart = Dcm_Dsp_SID86_CheckStartEvent();
                if( b_EventStart == (boolean)FALSE )
                {
                    /* E_OK has been already set in u1_RetVal */
                    *ptRoeEventId       = u1_RoeEventId;
                }
                else
                {
                    if( u2ConnectionId == Dcm_Dsp_SID86_u2StartRequestConnectionId )
                    {
                        /* E_OK has been already set in u1_RetVal */
                        *ptRoeEventId   = u1_RoeEventId;
                    }
                    else
                    {
                        u1_RetVal       = (Std_ReturnType)E_NOT_OK;
                        /* NRC = 0x22 */
                        *ptErrorCode    = DCM_E_CONDITIONSNOTCORRECT;
                    }
                }
            }
            else
            {
                u1_RetVal               = (Std_ReturnType)E_NOT_OK;
                /* NRC = 0x22 */
                *ptErrorCode            = DCM_E_CONDITIONSNOTCORRECT;
            }
        }
        else if( u1_RetRoeCond == (Std_ReturnType)E_NOT_OK )
        { 
            u1_RetVal                   = (Std_ReturnType)E_NOT_OK;
            *ptErrorCode                = u1_Nrc;
        }
        else
        {
            u1_RetVal                   = (Std_ReturnType)E_NOT_OK;
            /* NRC = 0x22 */
            *ptErrorCode                = DCM_E_CONDITIONSNOTCORRECT;
        }
    }
    else
    {
        u1_RetVal                       = (Std_ReturnType)E_NOT_OK;
        /* NRC = 0x31 */
        *ptErrorCode                    = DCM_E_REQUESTOUTOFRANGE;
    }

    return u1_RetVal;
}
#endif /* DCM_DSP_SID86_NVM_USE == STD_ON */
#if ( DCM_DSP_SID86_NVM_USE == STD_OFF )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub01_CheckCondition
(
    const uint16                                                    u2ConnectionId,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA )         ptMsgContext,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA )                        ptRoeEventId,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
)
{
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA ) pt_EventTypeRecord;
    Dcm_MsgLenType                  u4_ServiceToRespondToRecordLen;
    uint16                          u2_RxPduId;
    uint8                           u1_EventWindowTime;
    uint8                           u1_RoeEventId;
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_RetChkSIDSupport;
    Std_ReturnType                  u1_RetRoeCond;
    Dcm_NegativeResponseCodeType    u1_Nrc;
    boolean                         b_SupportFlg;
    boolean                         b_EventStart;

    u1_RetVal               = (Std_ReturnType)E_OK;
    u1_RetChkSIDSupport     = (Std_ReturnType)E_NOT_OK;
    u1_Nrc                  = DCM_E_GENERALREJECT;              /* 0x10 */
    u1_RoeEventId           = Dcm_Dsp_SID86_u1DTCStatusChangedEventId;
    *ptErrorCode            = (Dcm_NegativeResponseCodeType)0x00U;
    *ptRoeEventId           = DCM_DSP_SID86_ROE_EVENTID_INVALID;

    /* Check whether eventWindowTime exist or not in DcmDspRoeEventWindowTime */
    u1_EventWindowTime = ptMsgContext->reqData[DCM_DSP_SID86_EVENTWINDOWTIME_OFFSET];

    /* Check whether eventWindowTime exist or not in DcmDspRoeEventWindowTime */
    b_SupportFlg = Dcm_Dsp_SID86_IsSupportEventWindowTime( u1_EventWindowTime );
    if( b_SupportFlg == (boolean)TRUE )
    {
        if( u1_RoeEventId != DCM_DSP_SID86_ROE_EVENTID_INVALID )
        {
            /* Get ServiceToRespondToRecord length */
            u4_ServiceToRespondToRecordLen = ( ptMsgContext->reqDataLen - (Dcm_MsgLenType)DCM_DSP_SID86_EVENTWINDOWTIME_LEN - (Dcm_MsgLenType)DCM_DSP_SID86_DTCSTATUSMASK_LEN );    /* no wrap around */
            /* Check the limit of ServiceToRespondToRecord length */
            if( u4_ServiceToRespondToRecordLen <= Dcm_Dsp_SID86_stRoeEvent[u1_RoeEventId].u1ServToRespToRecLen )
            {
                /* Get PduId */
                u2_RxPduId = ptMsgContext->dcmRxPduId;
                u1_RetChkSIDSupport = Dcm_Dsp_SID86_CheckServSupport( &ptMsgContext->reqData[DCM_DSP_SID86_SF01_SID_OFFSET], u4_ServiceToRespondToRecordLen, u2_RxPduId );
            }
        }
    }

    /* Check ServiceToRespondToRecord) */
    if( u1_RetChkSIDSupport == (Std_ReturnType)E_OK )
    {
        pt_EventTypeRecord  = &ptMsgContext->reqData[DCM_DSP_SID86_DTCSTATUSMASK_OFFSET];
        u1_RetRoeCond       = Dcm_Dsp_SID86_CheckRoeCondition( DCM_DSP_SID86_SF01, u1_EventWindowTime, pt_EventTypeRecord, (uint8)DCM_DSP_SID86_SF01_EVENTTYPE_LEN, &u1_Nrc );

        if( u1_RetRoeCond == (Std_ReturnType)E_OK )
        {
            b_EventStart = Dcm_Dsp_SID86_CheckStartEvent();
            if( b_EventStart == (boolean)FALSE )
            {
                /* E_OK has been already set in u1_RetVal */
                *ptRoeEventId       = u1_RoeEventId;
            }
            else
            {
                if( u2ConnectionId == Dcm_Dsp_SID86_u2StartRequestConnectionId )
                {
                    /* E_OK has been already set in u1_RetVal */
                    *ptRoeEventId   = u1_RoeEventId;
                }
                else
                {
                    u1_RetVal       = (Std_ReturnType)E_NOT_OK;
                    /* NRC = 0x22 */
                    *ptErrorCode    = DCM_E_CONDITIONSNOTCORRECT;
                }
            }
        }
        else if( u1_RetRoeCond == (Std_ReturnType)E_NOT_OK )
        { 
            u1_RetVal               = (Std_ReturnType)E_NOT_OK;
            *ptErrorCode            = u1_Nrc;
        }
        else
        {
            u1_RetVal               = (Std_ReturnType)E_NOT_OK;
            /* NRC = 0x22 */
            *ptErrorCode            = DCM_E_CONDITIONSNOTCORRECT;
        }
    }
    else
    {
        u1_RetVal                   = (Std_ReturnType)E_NOT_OK;
        /* NRC = 0x31 */
        *ptErrorCode                = DCM_E_REQUESTOUTOFRANGE;
    }

    return u1_RetVal;
}
#endif /* DCM_DSP_SID86_NVM_USE == STD_OFF */
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_Sub41_InitialProc                          */
/* Description   | Initial process of SID86 Sub41 request                   */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext   : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub41_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    Dcm_MsgContextType              st_Dcm_MsgContext;
    Std_ReturnType                  u1_RetVal;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;

    u1_RetVal               = (Std_ReturnType)E_OK;
    st_Dcm_MsgContext       = *ptMsgContext;

    /* Set Dcm_Dsp_Main_bIdleFlag in FALSE */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );

    /* Check Request Message Length */
    if( st_Dcm_MsgContext.reqDataLen >= DCM_DSP_SID86_SF41_REQ_MIN_LEN )
    {
        /* NRC0x31 : the storeEvent bit is set and a SubFunction different to startResponseOnEvent was requested */
        u1_ErrorCode = DCM_E_REQUESTOUTOFRANGE;
    }
    else
    {
        /* NRC0x13 */
        u1_ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }

    /* Negative response */
    Dcm_Dsp_MsgMaker_SendNegRes( &st_Dcm_MsgContext, u1_ErrorCode );

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_Sub03_InitialProc                          */
/* Description   | Initial process of SID86 Sub03 request                   */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext   : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                                                     */
/*               | DCM_E_PENDING                                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub03_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    Dcm_MsgContextType              st_Dcm_MsgContext;
    uint16                          u2_ConnectionId;
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_RetCheckCondition;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;
    boolean                         b_SendNegResFlag;
    uint8                           u1_RoeEventId;

    u1_RetVal               = (Std_ReturnType)E_OK;
    u1_ErrorCode            = (Dcm_NegativeResponseCodeType)0x00U;
    b_SendNegResFlag        = (boolean)FALSE;
    st_Dcm_MsgContext       = *ptMsgContext;
    u2_ConnectionId         = (uint16)0U;
    u1_RoeEventId           = DCM_DSP_SID86_ROE_EVENTID_INVALID;

    /* Set Dcm_Dsp_Main_bIdleFlag in FALSE */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );

    /* Check Request Message Length */
    if( st_Dcm_MsgContext.reqDataLen >= DCM_DSP_SID86_SF03_REQ_MIN_LEN )
    {
        /* Get Connection Id */
        (void)Dcm_GetActiveProtocol( NULL_PTR, &u2_ConnectionId, NULL_PTR ); /* no return check required */

        u1_RetCheckCondition = Dcm_Dsp_SID86_Sub03_CheckCondition( u2_ConnectionId, &st_Dcm_MsgContext, &u1_RoeEventId, &u1_ErrorCode );
        if( u1_RetCheckCondition == (Std_ReturnType)E_OK )
        {
            /* Regist Event */
            Dcm_Dsp_SID86_RegEvent_Sub03( u1_RoeEventId, u2_ConnectionId, &st_Dcm_MsgContext );
        }
        else
        {
            b_SendNegResFlag = (boolean)TRUE;
        }
    }
    else
    {
        /* NRC0x13 */
        b_SendNegResFlag = (boolean)TRUE;
        u1_ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }

    if( b_SendNegResFlag == (boolean)TRUE )
    {
        /* Negative response */
        Dcm_Dsp_MsgMaker_SendNegRes( &st_Dcm_MsgContext, u1_ErrorCode );
    }
    else
    {
        Dcm_Dsp_SID86_EditPosRes( DCM_DSP_SID86_SF03, &st_Dcm_MsgContext );
        Dcm_Dsp_MsgMaker_SendPosRes( &st_Dcm_MsgContext );
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_Sub03_CheckCondition                       */
/* Description   | Check condition process of SID86 Sub03 request           */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u2ConnectionId : Connection ID                      */
/*               | [IN] ptMsgContext   : Message Context(send data info)    */
/*               | [OUT]ptRoeEventId   : RoeEvent ID                        */
/*               | [OUT]ptErrorCode    : Negative Response Code             */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_DSP_SID86_NVM_USE == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub03_CheckCondition
(
    const   uint16                                                  u2ConnectionId,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA )         ptMsgContext,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA )                        ptRoeEventId,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
)
{
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA ) pt_EventTypeRecord;
    Dcm_MsgLenType                  u4_ServiceToRespondToRecordLen;
    uint16                          u2_EvTypeDid;
    uint16                          u2_RxPduId;
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_CheckServSup;
    Std_ReturnType                  u1_RetRoeCond;
    Std_ReturnType                  u1_ChkRegCond;
    uint8                           u1_EventWindowTime;
    uint8                           u1_RoeEventId;
    Dcm_NegativeResponseCodeType    u1_Nrc;
    boolean                         b_SupportFlg;
    boolean                         b_NvmReadComp;

    u1_RetVal               = (Std_ReturnType)E_OK;
    u1_CheckServSup         = (Std_ReturnType)E_NOT_OK;
    u1_Nrc                  = DCM_E_GENERALREJECT;              /* 0x10 */
    *ptErrorCode            = (Dcm_NegativeResponseCodeType)0x00U;
    *ptRoeEventId           = DCM_DSP_SID86_ROE_EVENTID_INVALID;
    /* Get eventWindowTime */
    u1_EventWindowTime = ptMsgContext->reqData[DCM_DSP_SID86_EVENTWINDOWTIME_OFFSET];

    /* Check whether eventWindowTime exist or not in DcmDspRoeEventWindowTime */
    b_SupportFlg = Dcm_Dsp_SID86_IsSupportEventWindowTime( u1_EventWindowTime );
    if( b_SupportFlg == (boolean)TRUE )
    {
        /* Get DID */
        u2_EvTypeDid = Dcm_Dsp_SID86_GetDid( &ptMsgContext->reqData[DCM_DSP_SID86_SF03_DID_OFFSET] );
        /* Get RoeEventId */
        u1_RoeEventId = Dcm_Dsp_SID86_GetEventIdByDid( u2_EvTypeDid );
        if( u1_RoeEventId != DCM_DSP_SID86_ROE_EVENTID_INVALID )
        {
            /* Get ServiceToRespondToRecord length */
            u4_ServiceToRespondToRecordLen = ( ptMsgContext->reqDataLen - (Dcm_MsgLenType)DCM_DSP_SID86_EVENTWINDOWTIME_LEN - (Dcm_MsgLenType)DCM_DSP_SID86_DID_LEN );  /* no wrap around */
            /* Check the limit of ServiceToRespondToRecord length */
            if( u4_ServiceToRespondToRecordLen <= Dcm_Dsp_SID86_stRoeEvent[u1_RoeEventId].u1ServToRespToRecLen )
            {
                /* Get PduId */
                u2_RxPduId = ptMsgContext->dcmRxPduId;
                /* Check ServiceToRespondToRecord */
                u1_CheckServSup = Dcm_Dsp_SID86_CheckServSupport( &ptMsgContext->reqData[DCM_DSP_SID86_SF03_SID_OFFSET], u4_ServiceToRespondToRecordLen, u2_RxPduId );
            }
        }
    }

    if( u1_CheckServSup == (Std_ReturnType)E_OK )
    {
        pt_EventTypeRecord  = &ptMsgContext->reqData[DCM_DSP_SID86_SF03_DID_OFFSET];
        u1_RetRoeCond       = Dcm_Dsp_SID86_CheckRoeCondition( DCM_DSP_SID86_SF03, u1_EventWindowTime, pt_EventTypeRecord, (uint8)DCM_DSP_SID86_SF03_EVENTTYPE_LEN, &u1_Nrc );

        if( u1_RetRoeCond == (Std_ReturnType)E_OK )
        {
            b_NvmReadComp = Dcm_Dsp_SID86_GetReadStorageCompleteFlag();
            if( b_NvmReadComp == (boolean)TRUE )
            {
                u1_ChkRegCond   = Dcm_Dsp_SID86_Sub03_Check_RegCondition( u1_RoeEventId, u2ConnectionId, &u1_Nrc );
                if( u1_ChkRegCond == (Std_ReturnType)E_OK )
                {
                    /* E_OK has been already set in u1_RetVal */
                    *ptRoeEventId   = u1_RoeEventId;
                }
                else
                {
                    u1_RetVal       = (Std_ReturnType)E_NOT_OK;
                    *ptErrorCode    = u1_Nrc;
                }
            }
            else
            {
                u1_RetVal           = (Std_ReturnType)E_NOT_OK;
                /* NRC = 0x22 */
                *ptErrorCode        = DCM_E_CONDITIONSNOTCORRECT;
            }
        }
        else if( u1_RetRoeCond == (Std_ReturnType)E_NOT_OK )
        { 
            u1_RetVal               = (Std_ReturnType)E_NOT_OK;
            *ptErrorCode            = u1_Nrc;
        }
        else
        {
            u1_RetVal               = (Std_ReturnType)E_NOT_OK;
            /* NRC = 0x22 */
            *ptErrorCode            = DCM_E_CONDITIONSNOTCORRECT;
        }
    }
    else
    {
        u1_RetVal                   = (Std_ReturnType)E_NOT_OK;
        /* NRC = 0x31 */
        *ptErrorCode                = DCM_E_REQUESTOUTOFRANGE;
    }

    return u1_RetVal;
}
#endif /* DCM_DSP_SID86_NVM_USE == STD_ON */
#if ( DCM_DSP_SID86_NVM_USE == STD_OFF )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub03_CheckCondition
(
    const   uint16                                                  u2ConnectionId,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA )         ptMsgContext,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA )                        ptRoeEventId,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
)
{
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA ) pt_EventTypeRecord;
    Dcm_MsgLenType                  u4_ServiceToRespondToRecordLen;
    uint16                          u2_EvTypeDid;
    uint16                          u2_RxPduId;
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_CheckServSup;
    Std_ReturnType                  u1_RetRoeCond;
    Std_ReturnType                  u1_ChkRegCond;
    uint8                           u1_EventWindowTime;
    uint8                           u1_RoeEventId;
    Dcm_NegativeResponseCodeType    u1_Nrc;
    boolean                         b_SupportFlg;

    u1_RetVal               = (Std_ReturnType)E_OK;
    u1_CheckServSup         = (Std_ReturnType)E_NOT_OK;
    u1_Nrc                  = DCM_E_GENERALREJECT;              /* 0x10 */
    *ptErrorCode            = (Dcm_NegativeResponseCodeType)0x00U;
    *ptRoeEventId           = DCM_DSP_SID86_ROE_EVENTID_INVALID;
    /* Get eventWindowTime */
    u1_EventWindowTime = ptMsgContext->reqData[DCM_DSP_SID86_EVENTWINDOWTIME_OFFSET];

    /* Check whether eventWindowTime exist or not in DcmDspRoeEventWindowTime */
    b_SupportFlg = Dcm_Dsp_SID86_IsSupportEventWindowTime( u1_EventWindowTime );
    if( b_SupportFlg == (boolean)TRUE )
    {
        /* Get DID */
        u2_EvTypeDid = Dcm_Dsp_SID86_GetDid( &ptMsgContext->reqData[DCM_DSP_SID86_SF03_DID_OFFSET] );
        /* Get RoeEventId */
        u1_RoeEventId = Dcm_Dsp_SID86_GetEventIdByDid( u2_EvTypeDid );
        if( u1_RoeEventId != DCM_DSP_SID86_ROE_EVENTID_INVALID )
        {
            /* Get ServiceToRespondToRecord length */
            u4_ServiceToRespondToRecordLen = ( ptMsgContext->reqDataLen - (Dcm_MsgLenType)DCM_DSP_SID86_EVENTWINDOWTIME_LEN - (Dcm_MsgLenType)DCM_DSP_SID86_DID_LEN );  /* no wrap around */
            /* Check the limit of ServiceToRespondToRecord length */
            if( u4_ServiceToRespondToRecordLen <= Dcm_Dsp_SID86_stRoeEvent[u1_RoeEventId].u1ServToRespToRecLen )
            {
                /* Get PduId */
                u2_RxPduId = ptMsgContext->dcmRxPduId;
                /* Check ServiceToRespondToRecord */
                u1_CheckServSup = Dcm_Dsp_SID86_CheckServSupport( &ptMsgContext->reqData[DCM_DSP_SID86_SF03_SID_OFFSET], u4_ServiceToRespondToRecordLen, u2_RxPduId );
            }
        }
    }

    if( u1_CheckServSup == (Std_ReturnType)E_OK )
    {
        pt_EventTypeRecord  = &ptMsgContext->reqData[DCM_DSP_SID86_SF03_DID_OFFSET];
        u1_RetRoeCond       = Dcm_Dsp_SID86_CheckRoeCondition( DCM_DSP_SID86_SF03, u1_EventWindowTime, pt_EventTypeRecord, (uint8)DCM_DSP_SID86_SF03_EVENTTYPE_LEN, &u1_Nrc );

        if( u1_RetRoeCond == (Std_ReturnType)E_OK )
        {
            u1_ChkRegCond   = Dcm_Dsp_SID86_Sub03_Check_RegCondition( u1_RoeEventId, u2ConnectionId, &u1_Nrc );
            if( u1_ChkRegCond == (Std_ReturnType)E_OK )
            {
                /* E_OK has been already set in u1_RetVal */
                *ptRoeEventId   = u1_RoeEventId;
            }
            else
            {
                u1_RetVal       = (Std_ReturnType)E_NOT_OK;
                *ptErrorCode    = u1_Nrc;
            }
        }
        else if( u1_RetRoeCond == (Std_ReturnType)E_NOT_OK )
        {
            u1_RetVal           = (Std_ReturnType)E_NOT_OK;
            *ptErrorCode        = u1_Nrc;
        }
        else
        {
            u1_RetVal           = (Std_ReturnType)E_NOT_OK;
            /* NRC = 0x22 */
            *ptErrorCode        = DCM_E_CONDITIONSNOTCORRECT;
        }
    }
    else
    {
        u1_RetVal               = (Std_ReturnType)E_NOT_OK;
        /* NRC = 0x31 */
        *ptErrorCode            = DCM_E_REQUESTOUTOFRANGE;
    }

    return u1_RetVal;
}
#endif /* DCM_DSP_SID86_NVM_USE == STD_OFF */


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_Sub03_Check_RegCondition                   */
/* Description   | Check Event Registration Condition                       */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1RoeEventId   : RoeEvent ID                        */
/*               | [IN] u2ConnectionId : Connection ID                      */
/*               | [OUT]ptErrorCode    : Negative Response Code             */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK             : Check OK                              */
/*               | E_NOT_OK         : Check NG                              */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub03_Check_RegCondition
(
    const   uint8                                                   u1RoeEventId,
    const   uint16                                                  u2ConnectionId,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
)
{
    Std_ReturnType                  u1_RetVal;
    uint8                           u1_NumChgDidEv;
    uint8                           u1_MaxNumChgDidEv;
    boolean                         b_EventStart;

    u1_RetVal           = (Std_ReturnType)E_OK;
    u1_NumChgDidEv      = Dcm_Dsp_SID86_u1NumChangeOfDataIdentfierEvents;
    u1_MaxNumChgDidEv   = Dcm_Dsp_SID86_u1MaxNumChangeOfDataId;
    *ptErrorCode        = (Dcm_NegativeResponseCodeType)0x00U;

    if( u1_NumChgDidEv >= u1_MaxNumChgDidEv )
    {
        if( Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1Status == DCM_DSP_SID86_ROE_STS_CLEAR )
        {
            u1_RetVal           = (Std_ReturnType)E_NOT_OK;
            *ptErrorCode        = DCM_E_REQUESTOUTOFRANGE;
        }
    }
    if( u1_RetVal == (Std_ReturnType)E_OK )
    {
        b_EventStart = Dcm_Dsp_SID86_CheckStartEvent();
        if( b_EventStart == (boolean)TRUE )
        {
            if( u2ConnectionId != Dcm_Dsp_SID86_u2StartRequestConnectionId )
            {
                u1_RetVal       = (Std_ReturnType)E_NOT_OK;
                *ptErrorCode    = DCM_E_CONDITIONSNOTCORRECT;
            }
        }
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_Sub43_InitialProc                          */
/* Description   | Initial process of SID86 Sub43 request                   */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext   : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub43_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    Dcm_MsgContextType              st_Dcm_MsgContext;
    Std_ReturnType                  u1_RetVal;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;

    u1_RetVal               = (Std_ReturnType)E_OK;
    st_Dcm_MsgContext       = *ptMsgContext;

    /* Set Dcm_Dsp_Main_bIdleFlag in FALSE */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );

    /* Check Request Message Length */
    if( st_Dcm_MsgContext.reqDataLen >= DCM_DSP_SID86_SF43_REQ_MIN_LEN )
    {
        /* NRC0x31 : the storeEvent bit is set and a SubFunction different to startResponseOnEvent was requested */
        u1_ErrorCode = DCM_E_REQUESTOUTOFRANGE;
    }
    else
    {
        /* NRC0x13 */
        u1_ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }

    /* Negative response */
    Dcm_Dsp_MsgMaker_SendNegRes( &st_Dcm_MsgContext, u1_ErrorCode );

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_GetDid                                     */
/* Description   | Get DataIdentifier Number                                */
/* Preconditions | None                                                     */
/* Parameters    | [in] ptDid : Pointer Of Did HighByte                     */
/* Return Value  | uint16                                                   */
/*               |   dataIdentifier                                         */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( uint16, DCM_CODE ) Dcm_Dsp_SID86_GetDid
(
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA )  ptDid
)
{
    uint16                          u2_Did;
    uint8                           u1_DidHigh;
    uint8                           u1_DidLow;

    u1_DidHigh  = ptDid[DCM_DSP_SID86_ETR_OFFSET_DID_HIGH];
    u1_DidLow   = ptDid[DCM_DSP_SID86_ETR_OFFSET_DID_LOW];
    u2_Did      = (uint16)( (uint16)((uint16)u1_DidHigh << DCM_DSP_SID86_SHIFT_BYTESIZE ) | (uint16)u1_DidLow );

    return u2_Did;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_Sub05_InitialProc                          */
/* Description   | Initial process of SID86 Sub05 request                   */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext   : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub05_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    Dcm_MsgContextType              st_Dcm_MsgContext;
    uint16                          u2_ConnectionId;
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_RetCheckCondition;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;
    boolean                         b_SendNegResFlag;

    u1_RetVal               = (Std_ReturnType)E_OK;
    u1_ErrorCode            = (Dcm_NegativeResponseCodeType)0x00U;
    b_SendNegResFlag        = (boolean)FALSE;
    st_Dcm_MsgContext       = *ptMsgContext;
    u2_ConnectionId         = (uint16)0U;


    /* Set Dcm_Dsp_Main_bIdleFlag in FALSE */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );

    /* Check Request Message Length */
    if( st_Dcm_MsgContext.reqDataLen == DCM_DSP_SID86_SF05_REQ_LEN )
    {
        /* Get Connection Id */
        (void)Dcm_GetActiveProtocol( NULL_PTR, &u2_ConnectionId, NULL_PTR ); /* no return check required */

        /* Check Request Message Parameter - Skip */
        /* Check Condition of Acceptance */
        u1_RetCheckCondition = Dcm_Dsp_SID86_Sub05_CheckCondition( u2_ConnectionId, &st_Dcm_MsgContext, &u1_ErrorCode );
        if( u1_RetCheckCondition == (Std_ReturnType)E_OK )
        {
            /* Excute Request Message */
            Dcm_Dsp_SID86_StartAllEvents( DCM_DSP_SID86_SF05, u2_ConnectionId );
        }
        else
        {
            b_SendNegResFlag = (boolean)TRUE;
        }
    }
    else
    {
        /* NRC0x13 */
        b_SendNegResFlag = (boolean)TRUE;
        u1_ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }

    if( b_SendNegResFlag == (boolean)TRUE )
    {
        /* Negative response */
        Dcm_Dsp_MsgMaker_SendNegRes( &st_Dcm_MsgContext, u1_ErrorCode );
    }
    else
    {
        Dcm_Dsp_SID86_EditPosRes( DCM_DSP_SID86_SF05, &st_Dcm_MsgContext );
        Dcm_Dsp_MsgMaker_SendPosRes( &st_Dcm_MsgContext );
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_Sub05_CheckCondition                       */
/* Description   | Check condition process of SID86 Sub05 request           */
/* Preconditions | None                                                     */
/* Parameters    | [IN]  u2ConnectionId : Connection ID                     */
/*               | [IN]  ptMsgContext   : Message Context(send data info)   */
/*               | [OUT] ptErrorCode    : Negative Response Code            */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_DSP_SID86_NVM_USE == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub05_CheckCondition
(
    const   uint16                                                  u2ConnectionId,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA )         ptMsgContext,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
)
{
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA ) pt_EventTypeRecord;
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_RetRoeCond;
    uint8                           u1_EventWindowTime;
    Dcm_NegativeResponseCodeType    u1_Nrc;
    boolean                         b_NvmReadComp;
    boolean                         b_EventStart;

    u1_RetVal               = (Std_ReturnType)E_OK;
    u1_Nrc                  = DCM_E_GENERALREJECT;              /* 0x10 */
    *ptErrorCode            = (Dcm_NegativeResponseCodeType)0x00U;
    /* Get eventWindowTime */
    u1_EventWindowTime  = ptMsgContext->reqData[DCM_DSP_SID86_EVENTWINDOWTIME_OFFSET];
    pt_EventTypeRecord  = &ptMsgContext->reqData[DCM_DSP_SID86_EVENTWINDOWTIME_OFFSET + DCM_DSP_SID86_EVENTWINDOWTIME_LEN];
    u1_RetRoeCond       = Dcm_Dsp_SID86_CheckRoeCondition( DCM_DSP_SID86_SF05, u1_EventWindowTime, pt_EventTypeRecord, (uint8)DCM_DSP_SID86_SF05_EVENTTYPE_LEN, &u1_Nrc );

    if( u1_RetRoeCond == (Std_ReturnType)E_OK )
    {
        b_NvmReadComp = Dcm_Dsp_SID86_GetReadStorageCompleteFlag();
        if( b_NvmReadComp == (boolean)TRUE )
        {
            b_EventStart = Dcm_Dsp_SID86_CheckStartEvent();
            if( b_EventStart == (boolean)TRUE )
            {
                if( u2ConnectionId != Dcm_Dsp_SID86_u2StartRequestConnectionId )
                {
                    u1_RetVal       = (Std_ReturnType)E_NOT_OK;
                    *ptErrorCode    = DCM_E_CONDITIONSNOTCORRECT;
                }
            }
        }
        else
        {
            u1_RetVal       = (Std_ReturnType)E_NOT_OK;
            /* NRC = 0x22 */
            *ptErrorCode    = DCM_E_CONDITIONSNOTCORRECT;
        }
    }
    else if( u1_RetRoeCond == (Std_ReturnType)E_NOT_OK )
    {
        u1_RetVal           = (Std_ReturnType)E_NOT_OK;
        *ptErrorCode        = u1_Nrc;
    }
    else
    {
        u1_RetVal           = (Std_ReturnType)E_NOT_OK;
        /* NRC = 0x22 */
        *ptErrorCode        = DCM_E_CONDITIONSNOTCORRECT;
    }

    return u1_RetVal;
}
#endif /* DCM_DSP_SID86_NVM_USE == STD_ON */
#if ( DCM_DSP_SID86_NVM_USE == STD_OFF )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub05_CheckCondition
(
    const   uint16                                                  u2ConnectionId,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA )         ptMsgContext,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
)
{
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA ) pt_EventTypeRecord;
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_RetRoeCond;
    uint8                           u1_EventWindowTime;
    Dcm_NegativeResponseCodeType    u1_Nrc;
    boolean                         b_EventStart;

    u1_RetVal               = (Std_ReturnType)E_OK;
    u1_Nrc                  = DCM_E_GENERALREJECT;              /* 0x10 */
    *ptErrorCode            = (Dcm_NegativeResponseCodeType)0x00U;
    /* Get eventWindowTime */
    u1_EventWindowTime  = ptMsgContext->reqData[DCM_DSP_SID86_EVENTWINDOWTIME_OFFSET];
    pt_EventTypeRecord  = &ptMsgContext->reqData[DCM_DSP_SID86_EVENTWINDOWTIME_OFFSET + DCM_DSP_SID86_EVENTWINDOWTIME_LEN];
    u1_RetRoeCond       = Dcm_Dsp_SID86_CheckRoeCondition( DCM_DSP_SID86_SF05, u1_EventWindowTime, pt_EventTypeRecord, (uint8)DCM_DSP_SID86_SF05_EVENTTYPE_LEN, &u1_Nrc );

    if( u1_RetRoeCond == (Std_ReturnType)E_OK )
    {
        b_EventStart = Dcm_Dsp_SID86_CheckStartEvent();
        if( b_EventStart == (boolean)TRUE )
        {
            if( u2ConnectionId != Dcm_Dsp_SID86_u2StartRequestConnectionId )
            {
                u1_RetVal       = (Std_ReturnType)E_NOT_OK;
                *ptErrorCode    = DCM_E_CONDITIONSNOTCORRECT;
            }
        }
    }
    else if( u1_RetRoeCond == (Std_ReturnType)E_NOT_OK )
    {
        u1_RetVal           = (Std_ReturnType)E_NOT_OK;
        *ptErrorCode        = u1_Nrc;
    }
    else
    {
        u1_RetVal           = (Std_ReturnType)E_NOT_OK;
        /* NRC = 0x22 */
        *ptErrorCode        = DCM_E_CONDITIONSNOTCORRECT;
    }

    return u1_RetVal;
}
#endif /* DCM_DSP_SID86_NVM_USE == STD_OFF */


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_Sub45_InitialProc                          */
/* Description   | Initial process of SID86 Sub45 request                   */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext   : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub45_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    Dcm_MsgContextType              st_Dcm_MsgContext;
    uint16                          u2_ConnectionId;
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_RetCheckCondition;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;
    boolean                         b_SendNegResFlag;

    u1_RetVal               = (Std_ReturnType)E_OK;
    u1_ErrorCode            = (Dcm_NegativeResponseCodeType)0x00U;
    b_SendNegResFlag        = (boolean)FALSE;
    st_Dcm_MsgContext       = *ptMsgContext;
    u2_ConnectionId         = (uint16)0U;


    /* Set Dcm_Dsp_Main_bIdleFlag in FALSE */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );

    /* Check Request Message Length */
    if( st_Dcm_MsgContext.reqDataLen == DCM_DSP_SID86_SF45_REQ_LEN )
    {
        /* Get Connection Id */
        (void)Dcm_GetActiveProtocol( NULL_PTR, &u2_ConnectionId, NULL_PTR ); /* no return check required */

        /* Check Request Message Parameter - Skip */
        /* Check Condition of Acceptance - Skip */
        u1_RetCheckCondition = Dcm_Dsp_SID86_Sub45_CheckCondition( u2_ConnectionId, &st_Dcm_MsgContext, &u1_ErrorCode );
        if( u1_RetCheckCondition == (Std_ReturnType)E_OK )
        {
            /* Excute Request Message */
            Dcm_Dsp_SID86_StartAllEvents( DCM_DSP_SID86_SF45, u2_ConnectionId );
        }
        else
        {
            b_SendNegResFlag = (boolean)TRUE;
        }
    }
    else
    {
        /* NRC0x13 */
        b_SendNegResFlag = (boolean)TRUE;
        u1_ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }

    if( b_SendNegResFlag == (boolean)TRUE )
    {
        /* Negative response */
        Dcm_Dsp_MsgMaker_SendNegRes( &st_Dcm_MsgContext, u1_ErrorCode );
    }
    else
    {
        Dcm_Dsp_SID86_EditPosRes( DCM_DSP_SID86_SF45, &st_Dcm_MsgContext );
        Dcm_Dsp_MsgMaker_SendPosRes( &st_Dcm_MsgContext );
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_Sub45_CheckCondition                       */
/* Description   | Check condition process of SID86 Sub45 request           */
/* Preconditions | None                                                     */
/* Parameters    | [IN]  u2ConnectionId : Connection ID                     */
/*               | [IN]  ptMsgContext   : Message Context(send data info)   */
/*               | [OUT] ptErrorCode    : Negative Response Code            */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_DSP_SID86_NVM_USE == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub45_CheckCondition
(
    const   uint16                                                  u2ConnectionId,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA )         ptMsgContext,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
)
{
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA ) pt_EventTypeRecord;
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_RetRoeCond;
    Dcm_SesCtrlType                 u1_SesCtrlType;
    Dcm_NegativeResponseCodeType    u1_Nrc;
    uint8                           u1_EventWindowTime;
    boolean                         b_NvmReadComp;
    boolean                         b_EventStart;

    u1_RetVal               = (Std_ReturnType)E_OK;
    u1_Nrc                  = DCM_E_GENERALREJECT;              /* 0x10 */
    u1_SesCtrlType          = DCM_DEFAULT_SESSION;
    *ptErrorCode            = (Dcm_NegativeResponseCodeType)0x00U;
    /* Get eventWindowTime */
    u1_EventWindowTime  = ptMsgContext->reqData[DCM_DSP_SID86_EVENTWINDOWTIME_OFFSET];
    pt_EventTypeRecord  = &ptMsgContext->reqData[DCM_DSP_SID86_EVENTWINDOWTIME_OFFSET + DCM_DSP_SID86_EVENTWINDOWTIME_LEN];
    u1_RetRoeCond       = Dcm_Dsp_SID86_CheckRoeCondition( DCM_DSP_SID86_SF45, u1_EventWindowTime, pt_EventTypeRecord, (uint8)DCM_DSP_SID86_SF45_EVENTTYPE_LEN, &u1_Nrc );

    if( u1_RetRoeCond == (Std_ReturnType)E_OK )
    {
        b_NvmReadComp = Dcm_Dsp_SID86_GetReadStorageCompleteFlag();
        if( b_NvmReadComp == (boolean)TRUE )
        {
            b_EventStart = Dcm_Dsp_SID86_CheckStartEvent();
            if( b_EventStart == (boolean)TRUE )
            {
                if( u2ConnectionId != Dcm_Dsp_SID86_u2StartRequestConnectionId )
                {
                    u1_RetVal       = (Std_ReturnType)E_NOT_OK;
                    *ptErrorCode    = DCM_E_CONDITIONSNOTCORRECT;
                }
            }
            if( u1_RetVal == (Std_ReturnType)E_OK )
            {
                ( void )Dcm_GetSesCtrlType( &u1_SesCtrlType );      /* no return check required */
                if( u1_SesCtrlType == DCM_DEFAULT_SESSION )
                {
                    /* E_OK has been already set in u1_RetVal */
                    /* No process */
                }
                else
                {
                    u1_RetVal       = (Std_ReturnType)E_NOT_OK;
                    /* NRC = 0x31 */
                    *ptErrorCode    = DCM_E_REQUESTOUTOFRANGE;
                }
            }
        }
        else
        {
            u1_RetVal           = (Std_ReturnType)E_NOT_OK;
            /* NRC = 0x22 */
            *ptErrorCode        = DCM_E_CONDITIONSNOTCORRECT;
        }
    }
    else if( u1_RetRoeCond == (Std_ReturnType)E_NOT_OK )
    { 
        u1_RetVal               = (Std_ReturnType)E_NOT_OK;
        *ptErrorCode            = u1_Nrc;
    }
    else
    {
        u1_RetVal               = (Std_ReturnType)E_NOT_OK;
        /* NRC = 0x22 */
        *ptErrorCode            = DCM_E_CONDITIONSNOTCORRECT;
    }

    return u1_RetVal;
}
#endif /* DCM_DSP_SID86_NVM_USE == STD_ON */
#if ( DCM_DSP_SID86_NVM_USE == STD_OFF )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub45_CheckCondition
(
    const   uint16                                                  u2ConnectionId,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA )         ptMsgContext,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
)
{
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA ) pt_EventTypeRecord;
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_RetRoeCond;
    Dcm_SesCtrlType                 u1_SesCtrlType;
    Dcm_NegativeResponseCodeType    u1_Nrc;
    uint8                           u1_EventWindowTime;
    boolean                         b_EventStart;

    u1_RetVal               = (Std_ReturnType)E_OK;
    u1_Nrc                  = DCM_E_GENERALREJECT;              /* 0x10 */
    u1_SesCtrlType          = DCM_DEFAULT_SESSION;
    *ptErrorCode            = (Dcm_NegativeResponseCodeType)0x00U;
    /* Get eventWindowTime */
    u1_EventWindowTime  = ptMsgContext->reqData[DCM_DSP_SID86_EVENTWINDOWTIME_OFFSET];
    pt_EventTypeRecord  = &ptMsgContext->reqData[DCM_DSP_SID86_EVENTWINDOWTIME_OFFSET + DCM_DSP_SID86_EVENTWINDOWTIME_LEN];
    u1_RetRoeCond       = Dcm_Dsp_SID86_CheckRoeCondition( DCM_DSP_SID86_SF45, u1_EventWindowTime, pt_EventTypeRecord, (uint8)DCM_DSP_SID86_SF45_EVENTTYPE_LEN, &u1_Nrc );

    if( u1_RetRoeCond == (Std_ReturnType)E_OK )
    {
        b_EventStart = Dcm_Dsp_SID86_CheckStartEvent();
        if( b_EventStart == (boolean)TRUE )
        {
            if( u2ConnectionId != Dcm_Dsp_SID86_u2StartRequestConnectionId )
            {
                u1_RetVal       = (Std_ReturnType)E_NOT_OK;
                *ptErrorCode    = DCM_E_CONDITIONSNOTCORRECT;
            }
        }
        if( u1_RetVal == (Std_ReturnType)E_OK )
        {
            ( void )Dcm_GetSesCtrlType( &u1_SesCtrlType );      /* no return check required */
            if( u1_SesCtrlType == DCM_DEFAULT_SESSION )
            {
                /* E_OK has been already set in u1_RetVal */
                /* No process */
            }
            else
            {
                u1_RetVal       = (Std_ReturnType)E_NOT_OK;
                /* NRC = 0x31 */
                *ptErrorCode    = DCM_E_REQUESTOUTOFRANGE;
            }
        }
    }
    else if( u1_RetRoeCond == (Std_ReturnType)E_NOT_OK )
    {
        u1_RetVal           = (Std_ReturnType)E_NOT_OK;
        *ptErrorCode        = u1_Nrc;
    }
    else
    {
        u1_RetVal           = (Std_ReturnType)E_NOT_OK;
        /* NRC = 0x22 */
        *ptErrorCode        = DCM_E_CONDITIONSNOTCORRECT;
    }

    return u1_RetVal;
}
#endif /* DCM_DSP_SID86_NVM_USE == STD_OFF */


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_Sub06_InitialProc                          */
/* Description   | Initial process of SID86 Sub06 request                   */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext   : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_DSP_SID86_NVM_USE == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub06_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    Dcm_MsgContextType              st_Dcm_MsgContext;
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_RetCheckCondition;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;
    boolean                         b_SendNegResFlag;

    u1_RetVal               = (Std_ReturnType)E_OK;
    u1_ErrorCode            = (Dcm_NegativeResponseCodeType)0x00U;
    b_SendNegResFlag        = (boolean)FALSE;
    st_Dcm_MsgContext       = *ptMsgContext;

    /* Set Dcm_Dsp_Main_bIdleFlag in FALSE */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );

    /* Check Request Message Length */
    if( st_Dcm_MsgContext.reqDataLen == DCM_DSP_SID86_SF06_REQ_LEN )
    {
        /* Check Request Message Parameter - Skip */
        /* Check Condition of Acceptance */
        u1_RetCheckCondition = Dcm_Dsp_SID86_Sub06_CheckCondition( &u1_ErrorCode );
        if( u1_RetCheckCondition == (Std_ReturnType)E_OK )
        {
            /* Excute Request Message */
            Dcm_Dsp_SID86_ClearAllEvents();
        }
        else
        {
            b_SendNegResFlag = (boolean)TRUE;
        }
    }
    else
    {
        /* NRC0x13 */
        b_SendNegResFlag = (boolean)TRUE;
        u1_ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }

    if( b_SendNegResFlag == (boolean)TRUE )
    {
        /* Negative response */
        Dcm_Dsp_MsgMaker_SendNegRes( &st_Dcm_MsgContext, u1_ErrorCode );
    }
    else
    {
        Dcm_Dsp_SID86_EditPosRes( DCM_DSP_SID86_SF06, &st_Dcm_MsgContext );
        Dcm_Dsp_MsgMaker_SendPosRes( &st_Dcm_MsgContext );
    }

    return u1_RetVal;
}
#endif /* DCM_DSP_SID86_NVM_USE == STD_ON */
#if ( DCM_DSP_SID86_NVM_USE == STD_OFF )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub06_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    Dcm_MsgContextType              st_Dcm_MsgContext;
    Std_ReturnType                  u1_RetVal;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;
    boolean                         b_SendNegResFlag;

    u1_RetVal               = (Std_ReturnType)E_OK;
    b_SendNegResFlag        = (boolean)FALSE;
    st_Dcm_MsgContext       = *ptMsgContext;

    /* Set Dcm_Dsp_Main_bIdleFlag in FALSE */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );

    /* Check Request Message Length */
    if( st_Dcm_MsgContext.reqDataLen == DCM_DSP_SID86_SF06_REQ_LEN )
    {
        /* Check Request Message Parameter - Skip */
        /* Check Condition of Acceptance - Skip */
        /* Excute Request Message */
        Dcm_Dsp_SID86_ClearAllEvents();
    }
    else
    {
        /* NRC0x13 */
        b_SendNegResFlag = (boolean)TRUE;
        u1_ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }

    if( b_SendNegResFlag == (boolean)TRUE )
    {
        /* Negative response */
        Dcm_Dsp_MsgMaker_SendNegRes( &st_Dcm_MsgContext, u1_ErrorCode );
    }
    else
    {
        Dcm_Dsp_SID86_EditPosRes( DCM_DSP_SID86_SF06, &st_Dcm_MsgContext );
        Dcm_Dsp_MsgMaker_SendPosRes( &st_Dcm_MsgContext );
    }

    return u1_RetVal;
}
#endif /* DCM_DSP_SID86_NVM_USE == STD_OFF */


#if ( DCM_DSP_SID86_NVM_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_Sub06_CheckCondition                       */
/* Description   | Check condition process of SID86 Sub06 request           */
/* Preconditions | None                                                     */
/* Parameters    | [OUT] ptErrorCode    : Negative Response Code            */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   E_NOT_OK          : Processing not normal              */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub06_CheckCondition
(
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
)
{
    Std_ReturnType                      u1_RetVal;
    boolean                             b_NvmReadComp;

    u1_RetVal           = (Std_ReturnType)E_OK;
    *ptErrorCode        = (Dcm_NegativeResponseCodeType)0x00U;

    b_NvmReadComp = Dcm_Dsp_SID86_GetReadStorageCompleteFlag();
    if( b_NvmReadComp != (boolean)TRUE )
    {
        u1_RetVal       = (Std_ReturnType)E_NOT_OK;
        /* NRC = 0x22 */
        *ptErrorCode    = DCM_E_CONDITIONSNOTCORRECT;
    }

    return u1_RetVal;
}
#endif /* DCM_DSP_SID86_NVM_USE == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_Sub46_InitialProc                          */
/* Description   | Initial process of SID86 Sub46 request                   */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext   : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub46_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    Dcm_MsgContextType              st_Dcm_MsgContext;
    Std_ReturnType                  u1_RetVal;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;

    u1_RetVal               = (Std_ReturnType)E_OK;
    st_Dcm_MsgContext       = *ptMsgContext;

    /* Set Dcm_Dsp_Main_bIdleFlag in FALSE */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );

    /* Check Request Message Length */
    if( st_Dcm_MsgContext.reqDataLen == DCM_DSP_SID86_SF46_REQ_LEN )
    {
        /* NRC0x31 : the storeEvent bit is set and a SubFunction different to startResponseOnEvent was requested */
        u1_ErrorCode = DCM_E_REQUESTOUTOFRANGE;
    }
    else
    {
        /* NRC0x13 */
        u1_ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }

    /* Negative response */
    Dcm_Dsp_MsgMaker_SendNegRes( &st_Dcm_MsgContext, u1_ErrorCode );

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_Sub07_InitialProc                          */
/* Description   | Initial process of SID86 Sub07 request                   */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext   : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub07_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA )      pt_EventTypeRecord;
    Dcm_ComparisonValueType         st_Dcm_ComparisonValue;
    Dcm_MsgContextType              st_Dcm_MsgContext;
    uint16                          u2_ConnectionId;
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_RetCheckCondition;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;
    boolean                         b_SendNegResFlag;
    uint8                           u1_RoeEventId;

    u1_RetVal               = (Std_ReturnType)E_OK;
    u1_ErrorCode            = (Dcm_NegativeResponseCodeType)0x00U;
    b_SendNegResFlag        = (boolean)FALSE;
    st_Dcm_MsgContext       = *ptMsgContext;
    u2_ConnectionId         = (uint16)0U;
    u1_RoeEventId           = DCM_DSP_SID86_ROE_EVENTID_INVALID;

    /* Set Dcm_Dsp_Main_bIdleFlag in FALSE */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );

    /* Check Request Message Length */
    if( st_Dcm_MsgContext.reqDataLen >= DCM_DSP_SID86_SF07_REQ_MIN_LEN )
    {
        /* Get Connection Id */
        (void)Dcm_GetActiveProtocol( NULL_PTR, &u2_ConnectionId, NULL_PTR ); /* no return check required */

        u1_RetCheckCondition = Dcm_Dsp_SID86_Sub07_CheckCondition( u2_ConnectionId, &st_Dcm_MsgContext, &u1_RoeEventId, &u1_ErrorCode );
        if( u1_RetCheckCondition == (Std_ReturnType)E_OK )
        {
            /* Regist Event */
            Dcm_Dsp_SID86_RegEvent_Sub07( u1_RoeEventId, u2_ConnectionId, &st_Dcm_MsgContext );
            /* Edit Comparison Structure Data  */
            pt_EventTypeRecord  = &st_Dcm_MsgContext.reqData[DCM_DSP_SID86_SF07_DID_OFFSET];
            Dcm_Dsp_SID86_EditComparisonData( pt_EventTypeRecord, &st_Dcm_ComparisonValue );
            /* Call Callout Function SetComparisonOfValues */
            (void)Dcm_Dsp_SID86_SetComparisonOfValues( u1_RoeEventId, &st_Dcm_ComparisonValue ); /* no return check required */
        }
        else
        {
            b_SendNegResFlag = (boolean)TRUE;
        }
    }
    else
    {
        /* NRC0x13 */
        b_SendNegResFlag = (boolean)TRUE;
        u1_ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }

    if( b_SendNegResFlag == (boolean)TRUE )
    {
        /* Negative response */
        Dcm_Dsp_MsgMaker_SendNegRes( &st_Dcm_MsgContext, u1_ErrorCode );
    }
    else
    {
        Dcm_Dsp_SID86_EditPosRes( DCM_DSP_SID86_SF07, &st_Dcm_MsgContext );
        Dcm_Dsp_MsgMaker_SendPosRes( &st_Dcm_MsgContext );
    }

    return u1_RetVal;

}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_Sub07_CheckCondition                       */
/* Description   | Check condition process of SID86 Sub07 request           */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u2ConnectionId : Connection ID                      */
/*               | [IN] ptMsgContext   : Message Context(send data info)    */
/*               | [OUT]ptRoeEventId   : RoeEvent ID                        */
/*               | [OUT]ptErrorCode    : Negative Response Code             */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_DSP_SID86_NVM_USE == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub07_CheckCondition
(
    const   uint16                                                  u2ConnectionId,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA )         ptMsgContext,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA )                        ptRoeEventId,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
)
{
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA ) pt_EventTypeRecord;
    Dcm_MsgLenType                  u4_ServiceToRespondToRecordLen;
    uint16                          u2_EvTypeDid;
    uint16                          u2_RxPduId;
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_CheckServSup;
    Std_ReturnType                  u1_RetRoeCond;
    Std_ReturnType                  u1_RetRegCond;
    uint8                           u1_EventWindowTime;
    uint8                           u1_RoeEventId;
    Dcm_NegativeResponseCodeType    u1_Nrc;
    boolean                         b_SupportFlg;
    boolean                         b_NvmReadComp;

    u1_RetVal               = (Std_ReturnType)E_OK;
    u1_CheckServSup         = (Std_ReturnType)E_NOT_OK;
    u1_Nrc                  = DCM_E_GENERALREJECT;              /* 0x10 */
    *ptErrorCode            = (Dcm_NegativeResponseCodeType)0x00U;
    *ptRoeEventId           = DCM_DSP_SID86_ROE_EVENTID_INVALID;
    /* Get eventWindowTime */
    u1_EventWindowTime = ptMsgContext->reqData[DCM_DSP_SID86_EVENTWINDOWTIME_OFFSET];

    /* Check whether eventWindowTime exist or not in DcmDspRoeEventWindowTime */
    b_SupportFlg = Dcm_Dsp_SID86_IsSupportEventWindowTime( u1_EventWindowTime );
    if( b_SupportFlg == (boolean)TRUE )
    {
        /* Get DID */
        u2_EvTypeDid = Dcm_Dsp_SID86_GetDid( &ptMsgContext->reqData[DCM_DSP_SID86_SF07_DID_OFFSET] );
        /* Get RoeEventId */
        u1_RoeEventId = Dcm_Dsp_SID86_GetEventIdByDid( u2_EvTypeDid );
        if( u1_RoeEventId != DCM_DSP_SID86_ROE_EVENTID_INVALID )
        {
            /* Get ServiceToRespondToRecord length */
            u4_ServiceToRespondToRecordLen = ( ptMsgContext->reqDataLen - (Dcm_MsgLenType)DCM_DSP_SID86_EVENTWINDOWTIME_LEN - (Dcm_MsgLenType)DCM_DSP_SID86_SF07_EVENTTYPE_LEN );   /* no wrap around */
            /* Check the limit of ServiceToRespondToRecord length */
            if( u4_ServiceToRespondToRecordLen <= Dcm_Dsp_SID86_stRoeEvent[u1_RoeEventId].u1ServToRespToRecLen )
            {
                /* Get PduId */
                u2_RxPduId = ptMsgContext->dcmRxPduId;
                /* Check ServiceToRespondToRecord */
                u1_CheckServSup = Dcm_Dsp_SID86_CheckServSupport( &ptMsgContext->reqData[DCM_DSP_SID86_SF07_SID_OFFSET], u4_ServiceToRespondToRecordLen, u2_RxPduId );
            }
        }
    }

    if( u1_CheckServSup == (Std_ReturnType)E_OK )
    {
        pt_EventTypeRecord  = &ptMsgContext->reqData[DCM_DSP_SID86_SF07_DID_OFFSET];
        u1_RetRoeCond       = Dcm_Dsp_SID86_CheckRoeCondition( DCM_DSP_SID86_SF07, u1_EventWindowTime, pt_EventTypeRecord, (uint8)DCM_DSP_SID86_SF07_EVENTTYPE_LEN, &u1_Nrc );

        if( u1_RetRoeCond == (Std_ReturnType)E_OK )
        {
            b_NvmReadComp = Dcm_Dsp_SID86_GetReadStorageCompleteFlag();
            if( b_NvmReadComp == (boolean)TRUE )
            {
                u1_RetRegCond = Dcm_Dsp_SID86_Sub07_Check_RegCondition( u1_RoeEventId, u2ConnectionId, &u1_Nrc );
                if( u1_RetRegCond == (Std_ReturnType)E_OK )
                {
                    /* E_OK has been already set in u1_RetVal */
                    *ptRoeEventId   = u1_RoeEventId;
                }
                else
                {
                    u1_RetVal       = (Std_ReturnType)E_NOT_OK;
                    *ptErrorCode    = u1_Nrc;
                }
            }
            else
            {
                u1_RetVal           = (Std_ReturnType)E_NOT_OK;
                /* NRC = 0x22 */
                *ptErrorCode        = DCM_E_CONDITIONSNOTCORRECT;
            }
        }
        else if( u1_RetRoeCond == (Std_ReturnType)E_NOT_OK )
        { 
            u1_RetVal               = (Std_ReturnType)E_NOT_OK;
            *ptErrorCode            = u1_Nrc;
        }
        else
        {
            u1_RetVal               = (Std_ReturnType)E_NOT_OK;
            /* NRC = 0x22 */
            *ptErrorCode            = DCM_E_CONDITIONSNOTCORRECT;
        }
    }
    else
    {
        u1_RetVal                   = (Std_ReturnType)E_NOT_OK;
        /* NRC = 0x31 */
        *ptErrorCode                = DCM_E_REQUESTOUTOFRANGE;
    }

    return u1_RetVal;
}
#endif /* DCM_DSP_SID86_NVM_USE == STD_ON */
#if ( DCM_DSP_SID86_NVM_USE == STD_OFF )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub07_CheckCondition
(
    const   uint16                                                  u2ConnectionId,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA )         ptMsgContext,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA )                        ptRoeEventId,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
)
{
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA ) pt_EventTypeRecord;
    Dcm_MsgLenType                  u4_ServiceToRespondToRecordLen;
    uint16                          u2_EvTypeDid;
    uint16                          u2_RxPduId;
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_CheckServSup;
    Std_ReturnType                  u1_RetRoeCond;
    Std_ReturnType                  u1_RetRegCond;
    uint8                           u1_EventWindowTime;
    uint8                           u1_RoeEventId;
    Dcm_NegativeResponseCodeType    u1_Nrc;
    boolean                         b_SupportFlg;

    u1_RetVal               = (Std_ReturnType)E_OK;
    u1_CheckServSup         = (Std_ReturnType)E_NOT_OK;
    u1_Nrc                  = DCM_E_GENERALREJECT;              /* 0x10 */
    *ptErrorCode            = (Dcm_NegativeResponseCodeType)0x00U;
    *ptRoeEventId           = DCM_DSP_SID86_ROE_EVENTID_INVALID;
    /* Get eventWindowTime */
    u1_EventWindowTime = ptMsgContext->reqData[DCM_DSP_SID86_EVENTWINDOWTIME_OFFSET];

    /* Check whether eventWindowTime exist or not in DcmDspRoeEventWindowTime */
    b_SupportFlg = Dcm_Dsp_SID86_IsSupportEventWindowTime( u1_EventWindowTime );
    if( b_SupportFlg == (boolean)TRUE )
    {
        /* Get DID */
        u2_EvTypeDid = Dcm_Dsp_SID86_GetDid( &ptMsgContext->reqData[DCM_DSP_SID86_SF07_DID_OFFSET] );
        /* Get RoeEventId */
        u1_RoeEventId = Dcm_Dsp_SID86_GetEventIdByDid( u2_EvTypeDid );
        if( u1_RoeEventId != DCM_DSP_SID86_ROE_EVENTID_INVALID )
        {
            /* Get ServiceToRespondToRecord length */
            u4_ServiceToRespondToRecordLen = ( ptMsgContext->reqDataLen - (Dcm_MsgLenType)DCM_DSP_SID86_EVENTWINDOWTIME_LEN - (Dcm_MsgLenType)DCM_DSP_SID86_SF07_EVENTTYPE_LEN );   /* no wrap around */
            /* Check the limit of ServiceToRespondToRecord length */
            if( u4_ServiceToRespondToRecordLen <= Dcm_Dsp_SID86_stRoeEvent[u1_RoeEventId].u1ServToRespToRecLen )
            {
                /* Get PduId */
                u2_RxPduId = ptMsgContext->dcmRxPduId;
                /* Check ServiceToRespondToRecord */
                u1_CheckServSup = Dcm_Dsp_SID86_CheckServSupport( &ptMsgContext->reqData[DCM_DSP_SID86_SF07_SID_OFFSET], u4_ServiceToRespondToRecordLen, u2_RxPduId );
            }
        }
    }

    if( u1_CheckServSup == (Std_ReturnType)E_OK )
    {
        pt_EventTypeRecord  = &ptMsgContext->reqData[DCM_DSP_SID86_SF07_DID_OFFSET];
        u1_RetRoeCond       = Dcm_Dsp_SID86_CheckRoeCondition( DCM_DSP_SID86_SF07, u1_EventWindowTime, pt_EventTypeRecord, (uint8)DCM_DSP_SID86_SF07_EVENTTYPE_LEN, &u1_Nrc );

        if( u1_RetRoeCond == (Std_ReturnType)E_OK )
        {
            u1_RetRegCond = Dcm_Dsp_SID86_Sub07_Check_RegCondition( u1_RoeEventId, u2ConnectionId, &u1_Nrc );
            if( u1_RetRegCond == (Std_ReturnType)E_OK )
            {
                /* E_OK has been already set in u1_RetVal */
                *ptRoeEventId   = u1_RoeEventId;
            }
            else
            {
                u1_RetVal       = (Std_ReturnType)E_NOT_OK;
                *ptErrorCode    = u1_Nrc;
            }
        }
        else if( u1_RetRoeCond == (Std_ReturnType)E_NOT_OK )
        { 
            u1_RetVal           = (Std_ReturnType)E_NOT_OK;
            *ptErrorCode        = u1_Nrc;
        }
        else
        {
            u1_RetVal           = (Std_ReturnType)E_NOT_OK;
            /* NRC = 0x22 */
            *ptErrorCode        = DCM_E_CONDITIONSNOTCORRECT;
        }
    }
    else
    {
        u1_RetVal               = (Std_ReturnType)E_NOT_OK;
        /* NRC = 0x31 */
        *ptErrorCode            = DCM_E_REQUESTOUTOFRANGE;
    }

    return u1_RetVal;
}
#endif /* DCM_DSP_SID86_NVM_USE == STD_OFF */


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_Sub07_Check_RegCondition                   */
/* Description   | Check Event Registration Condition                       */
/* Preconditions | None                                                     */
/* Parameters    | [IN]  u1RoeEventId   : RoeEvent ID                       */
/*               | [IN]  u2ConnectionId : Connection ID                     */
/*               | [OUT] ptErrorCode    : Negative Response Code            */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK             : Check OK                              */
/*               | E_NOT_OK         : Check NG                              */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub07_Check_RegCondition
(
    const   uint8                                                   u1RoeEventId,
    const   uint16                                                  u2ConnectionId,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
)
{
    Std_ReturnType                  u1_RetVal;
    uint8                           u1_NumCmpValEv;
    uint8                           u1_MaxNumCmpValEv;
    boolean                         b_EventStart;

    u1_RetVal           = (Std_ReturnType)E_OK;
    u1_NumCmpValEv      = Dcm_Dsp_SID86_u1NumComparisionOfValueEvents;
    u1_MaxNumCmpValEv   = Dcm_Dsp_SID86_u1MaxNumComparisionOfValue;
    *ptErrorCode        = (Dcm_NegativeResponseCodeType)0x00U;

    if( u1_NumCmpValEv >= u1_MaxNumCmpValEv )
    {
        if( Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1Status == DCM_DSP_SID86_ROE_STS_CLEAR )
        {
            u1_RetVal           = (Std_ReturnType)E_NOT_OK;
            *ptErrorCode        = DCM_E_REQUESTOUTOFRANGE;
        }
    }
    if( u1_RetVal == (Std_ReturnType)E_OK )
    {
        b_EventStart = Dcm_Dsp_SID86_CheckStartEvent();
        if( b_EventStart == (boolean)TRUE )
        {
            if( u2ConnectionId != Dcm_Dsp_SID86_u2StartRequestConnectionId )
            {
                u1_RetVal       = (Std_ReturnType)E_NOT_OK;
                *ptErrorCode    = DCM_E_CONDITIONSNOTCORRECT;
            }
        }
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_Sub47_InitialProc                          */
/* Description   | Initial process of SID86 Sub47 request                   */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext   : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_Sub47_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    Dcm_MsgContextType              st_Dcm_MsgContext;
    Std_ReturnType                  u1_RetVal;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;

    u1_RetVal               = (Std_ReturnType)E_OK;
    st_Dcm_MsgContext       = *ptMsgContext;

    /* Set Dcm_Dsp_Main_bIdleFlag in FALSE */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );

    /* Check Request Message Length */
    if( st_Dcm_MsgContext.reqDataLen >= DCM_DSP_SID86_SF47_REQ_MIN_LEN )
    {
        /* NRC0x31 : the storeEvent bit is set and a SubFunction different to startResponseOnEvent was requested */
        u1_ErrorCode = DCM_E_REQUESTOUTOFRANGE;
    }
    else
    {
        /* NRC0x13 */
        u1_ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }

    /* Negative response */
    Dcm_Dsp_MsgMaker_SendNegRes( &st_Dcm_MsgContext, u1_ErrorCode );

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_CancelProc_OnlySetIdleFlag                 */
/* Description   | Cancel process of SID 86.                                */
/*               | This function only set IdleFlag to TRUE.                 */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_CancelProc_OnlySetIdleFlag
(
    void
)
{
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return E_OK;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_EditPosRes                                 */
/* Description   | Edit Positive Response                                   */
/* Preconditions | None                                                     */
/* Parameters    | [IN]     u1SubFunc     : SubFuncrionId                   */
/*               | [IN/OUT] ptMsgContext  : Message Context                 */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_EditPosRes
(
    const uint8                                             u1SubFunc,
    P2VAR( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA )   ptMsgContext
)
{
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) pt_ReqData;
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) pt_ResData;
    uint8               u1_ReqDataLen;
    uint8               u1_ServToRespToLen;
    uint8               u1_Cnt;

    pt_ReqData          = ptMsgContext->reqData;
    pt_ResData          = ptMsgContext->resData;
    pt_ResData[DCM_DSP_SID86_MES_OFFSET_00]     = (uint8)0U;
    pt_ResData[DCM_DSP_SID86_MES_OFFSET_01]     = pt_ReqData[DCM_DSP_SID86_EVENTWINDOWTIME_OFFSET];

    if( u1SubFunc == DCM_DSP_SID86_SF01 )
    {
        u1_ReqDataLen       = (uint8)ptMsgContext->reqDataLen;
        u1_ServToRespToLen  = (uint8)( u1_ReqDataLen - ( (uint32)DCM_DSP_SID86_EVENTWINDOWTIME_LEN + (uint32)DCM_DSP_SID86_DTCSTATUSMASK_LEN ) );   /* no wrap around */
        /* eventTypeRecord 1Byte */
        pt_ResData[DCM_DSP_SID86_MES_OFFSET_02] = pt_ReqData[DCM_DSP_SID86_DTCSTATUSMASK_OFFSET];
        /* serviceToRespondToRecord */
        for( u1_Cnt = (uint8)0U; u1_Cnt < u1_ServToRespToLen; u1_Cnt++ )
        {
            pt_ResData[(DCM_DSP_SID86_MES_OFFSET_02 + DCM_DSP_SID86_DTCSTATUSMASK_LEN + u1_Cnt)] = pt_ReqData[(DCM_DSP_SID86_SF01_SID_OFFSET + u1_Cnt)];    /* no wrap around */
        }
        ptMsgContext->resDataLen = (uint32)( (uint32)DCM_DSP_SID86_NUMBEROFID_LEN + (uint32)DCM_DSP_SID86_EVENTWINDOWTIME_LEN + (uint32)DCM_DSP_SID86_DTCSTATUSMASK_LEN + (uint32)u1_ServToRespToLen ); /* no wrap around */
    }
    else if( u1SubFunc == DCM_DSP_SID86_SF03 )
    {
        u1_ReqDataLen       = (uint8)ptMsgContext->reqDataLen;
        u1_ServToRespToLen  = (uint8)( u1_ReqDataLen - ( (uint32)DCM_DSP_SID86_EVENTWINDOWTIME_LEN + (uint32)DCM_DSP_SID86_DID_LEN ) ); /* no wrap around */
        /* eventTypeRecord 2Byte */
        for( u1_Cnt = (uint8)0U; u1_Cnt < (uint8)DCM_DSP_SID86_DID_LEN; u1_Cnt++ )
        {
            pt_ResData[(DCM_DSP_SID86_MES_OFFSET_02 + u1_Cnt)] = pt_ReqData[(DCM_DSP_SID86_SF03_DID_OFFSET + u1_Cnt)];  /* no wrap around */
        }
        /* serviceToRespondToRecord */
        for( u1_Cnt = (uint8)0U; u1_Cnt < u1_ServToRespToLen; u1_Cnt++ )
        {
            pt_ResData[(DCM_DSP_SID86_MES_OFFSET_02 + DCM_DSP_SID86_DID_LEN + u1_Cnt)] = pt_ReqData[(DCM_DSP_SID86_SF03_SID_OFFSET + u1_Cnt)];  /* no wrap around */
        }
        ptMsgContext->resDataLen = (uint32)( (uint32)DCM_DSP_SID86_NUMBEROFID_LEN + (uint32)DCM_DSP_SID86_EVENTWINDOWTIME_LEN + (uint32)DCM_DSP_SID86_DID_LEN + (uint32)u1_ServToRespToLen );   /* no wrap around */
    }
    else if( u1SubFunc == DCM_DSP_SID86_SF07 )
    {
        u1_ReqDataLen       = (uint8)ptMsgContext->reqDataLen;
        u1_ServToRespToLen  = (uint8)( u1_ReqDataLen - ( (uint32)DCM_DSP_SID86_EVENTWINDOWTIME_LEN + (uint32)DCM_DSP_SID86_SF07_EVENTTYPE_LEN ) );  /* no wrap around */
        /* eventTypeRecord 10Byte */
        for( u1_Cnt = (uint8)0U; u1_Cnt < (uint8)DCM_DSP_SID86_SF07_EVENTTYPE_LEN; u1_Cnt++ )
        {
            pt_ResData[(DCM_DSP_SID86_MES_OFFSET_02 + u1_Cnt)] = pt_ReqData[(DCM_DSP_SID86_SF07_DID_OFFSET + u1_Cnt)];  /* no wrap around */
        }
        /* serviceToRespondToRecord */
        for( u1_Cnt = (uint8)0U; u1_Cnt < u1_ServToRespToLen; u1_Cnt++ )
        {
            pt_ResData[(DCM_DSP_SID86_MES_OFFSET_02 + DCM_DSP_SID86_SF07_EVENTTYPE_LEN + u1_Cnt)] = pt_ReqData[(DCM_DSP_SID86_SF07_SID_OFFSET + u1_Cnt)];   /* no wrap around */
        }
        ptMsgContext->resDataLen = (uint32)( (uint32)DCM_DSP_SID86_NUMBEROFID_LEN + (uint32)DCM_DSP_SID86_EVENTWINDOWTIME_LEN + (uint32)DCM_DSP_SID86_SF07_EVENTTYPE_LEN + (uint32)u1_ServToRespToLen );    /* no wrap around */
    }
    else
    {
        ptMsgContext->resDataLen = (uint32)( (uint32)DCM_DSP_SID86_NUMBEROFID_LEN + (uint32)DCM_DSP_SID86_EVENTWINDOWTIME_LEN );
        /* eventTypeRecord None */
        /* serviceToRespondToRecord None */
    }

    return;

}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_GetEventIdByDid                            */
/* Description   | Get EventId for Did                                      */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u2Did          : DID                                */
/* Return Value  | uint8                                                    */
/*               |   DID                                                    */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( uint8, DCM_CODE ) Dcm_Dsp_SID86_GetEventIdByDid
(
    const uint16                                            u2Did
)
{
    uint8                       u1_NumOfRoeEvent;
    uint8                       u1_DTCStsChgEvId;
    uint8                       u1_RoeEventId;
    uint8                       u1_Cnt;

    u1_NumOfRoeEvent    = Dcm_Dsp_SID86_u1NumOfRoeEvent;
    u1_DTCStsChgEvId    = Dcm_Dsp_SID86_u1DTCStatusChangedEventId;
    u1_RoeEventId       = DCM_DSP_SID86_ROE_EVENTID_INVALID;
    
    for( u1_Cnt = (uint8)0U; u1_Cnt < u1_NumOfRoeEvent; u1_Cnt++ )
    {
        if( u2Did == Dcm_Dsp_SID86_stRoeEvent[u1_Cnt].u2EvProp )
        {
            if( u1_Cnt != u1_DTCStsChgEvId )
            {
                u1_RoeEventId = u1_Cnt;
                break;
            }
        }
    }

    return u1_RoeEventId;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_CheckStartEvent                            */
/* Description   | Check Startted Event                                     */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( boolean, DCM_CODE ) Dcm_Dsp_SID86_CheckStartEvent
(
    void
)
{
    uint8                       u1_NumOfRoeEvent;
    uint8                       u1_Cnt;
    boolean                     b_EventStart;

    u1_NumOfRoeEvent    = Dcm_Dsp_SID86_u1NumOfRoeEvent;
    b_EventStart        = (boolean)FALSE;
    
    /* lock */
    SchM_Enter_Dcm_Dsp_Roe();
    for( u1_Cnt = (uint8)0U; u1_Cnt < u1_NumOfRoeEvent; u1_Cnt++ )
    {
        if( Dcm_Dsp_SID86_stEventLogic[u1_Cnt].u1Status == DCM_DSP_SID86_ROE_STS_START )
        {
            b_EventStart        = (boolean)TRUE;
        }
        else if( Dcm_Dsp_SID86_stEventLogic[u1_Cnt].u1Status == DCM_DSP_SID86_ROE_STS_START_EVENT )
        {
            b_EventStart        = (boolean)TRUE;
        }
        else
        {
            /* No process */
        }
   }
    /* unlock */
    SchM_Exit_Dcm_Dsp_Roe();

    return b_EventStart;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_EditComparisonData                         */
/* Description   | Initial process of SID86 Sub07 request                   */
/* Preconditions | None                                                     */
/* Parameters    | [IN]  ptEventTypeRecord : EventTypeRecord                */
/*               | [OUT] ptComparisonValue : ComparisonValue Data           */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_EditComparisonData
(
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA )              ptEventTypeRecord,
    P2VAR( Dcm_ComparisonValueType, AUTOMATIC, AUTOMATIC )  ptComparisonValue
)
{
    uint32                          u4_EvTypeCompValue;
    uint16                          u2_EvTypeDid;
    uint16                          u2_EvTypeLocal;
    uint8                           u1_EvTypeCompLogic;
    uint8                           u1_EvTypeHyst;
    uint8                           u1_count;

    u2_EvTypeDid        = Dcm_Dsp_SID86_GetDid( &ptEventTypeRecord[DCM_DSP_SID86_COMP_DID_OFFSET] );
    u1_EvTypeCompLogic  = ptEventTypeRecord[DCM_DSP_SID86_COMP_LOGIC_OFFSET];
    u4_EvTypeCompValue  = (uint32)0U;
    for( u1_count = (uint8)0U; u1_count < (uint8)DCM_DSP_SID86_COMP_VALUE_LEN ; u1_count++ )
    {
        /*  Raw reference comparison value [uint8]                      */
        /*  +-------+                                                   */
        /*  |  CL1  | MSB  reqData[COMP_LOGIC_OFFSET]                   */
        /*  +-------+                                                   */
        /*  |  CL2  |      reqData[COMP_LOGIC_OFFSET+1]                 */
        /*  +-------+                                                   */
        /*  |  CL3  |      reqData[COMP_LOGIC_OFFSET+2]                 */
        /*  +-------+                                                   */
        /*  |  CL4  | LSB  reqData[COMP_LOGIC_OFFSET+3]                 */
        /*  +-------+                                                   */
        /*                                                              */
        /*  -> convert to uint32                                        */
        /*  uint32                                                      */
        /*  +-------+-------+-------+-------+                           */
        /*  |  CL1  |  CL2  |  CL3  |  CL4  |                           */
        /*  +-------+-------+-------+-------+                           */
        u4_EvTypeCompValue <<= DCM_DSP_SID86_SHIFT_BYTESIZE;
        u4_EvTypeCompValue += ptEventTypeRecord[DCM_DSP_SID86_COMP_VALUE_OFFSET + u1_count];    /* no wrap around */
    }
    u1_EvTypeHyst       = ptEventTypeRecord[DCM_DSP_SID86_COMP_HYST_OFFSET];
    u2_EvTypeLocal      = (uint16)0U;
    for( u1_count = (uint8)0U; u1_count < (uint8)DCM_DSP_SID86_LOCAL_LEN ; u1_count++ )
    {
        /*  Localization byte [uint8]                                   */
        /*  +-------+                                                   */
        /*  |  LC1  | MSB  reqData[COMP_LOCAL_OFFSET]                   */
        /*  +-------+                                                   */
        /*  |  LC2  | LSB  reqData[COMP_LOCAL_OFFSET+2]                 */
        /*  +-------+                                                   */
        /*                                                              */
        /*  -> convert to uint16                                        */
        /*  uint16                                                      */
        /*  +-------+-------+                                           */
        /*  |  LC1  |  LC2  |                                           */
        /*  +-------+-------+                                           */
        u2_EvTypeLocal <<= DCM_DSP_SID86_SHIFT_BYTESIZE;
        u2_EvTypeLocal += ptEventTypeRecord[DCM_DSP_SID86_COMP_LOCAL_OFFSET + u1_count];    /* no wrap around */
    }

    ptComparisonValue->u2DID                = u2_EvTypeDid;
    ptComparisonValue->u1ComparisonLogic    = u1_EvTypeCompLogic;
    ptComparisonValue->u4ComparisonValue    = u4_EvTypeCompValue;
    ptComparisonValue->u1Hysteresis         = u1_EvTypeHyst;
    ptComparisonValue->u2Localization       = u2_EvTypeLocal;

    return;

}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_GenerateReceivedSubFunc                    */
/* Description   | Generate SubFunction Data                                */
/* Preconditions | None                                                     */
/* Parameters    | [IN]  u1SubFunc      : SubFunction                       */
/*               | [IN]  u1SuppressPRM  : suppressPosResponseMessageInd     */
/* Return Value  | uint8                                                    */
/*               |                      : Received SubFunc Image            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( uint8, DCM_CODE ) Dcm_Dsp_SID86_GenerateReceivedSubFunc
(
    const uint8                                            u1SubFunc,
    const uint8                                            u1SuppressPRM
)
{
    uint8       u1_ReceivedSubFunc;

    u1_ReceivedSubFunc      = u1SubFunc;
    if( u1SuppressPRM == (uint8)STD_ON )
    {
        u1_ReceivedSubFunc  |= DCM_DSP_SID86_POS_SUP_MASK;
    }

    return u1_ReceivedSubFunc;
}


#if ( DCM_DSP_SID86_NVM_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_Init_Storage                               */
/* Description   | Init processing of SID86 Storage                         */
/* Preconditions | None                                                     */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_Init_Storage
(
    void
)
{
    /* Set to False to wait for NvM to reflect */
    Dcm_Dsp_SID86_bReadStorageCompleteFlag  = (boolean)FALSE;

    return ;
}
#endif /* DCM_DSP_SID86_NVM_USE == STD_ON */


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_WriteStorage                               */
/* Description   | Operate BlockIdx to use in StorageMng from RoeEventId,   */
/*               |  and require data write in StorageMng using BlockIdx.    */
/* Preconditions | None                                                     */
/* Parameters    | [in] u1RoeEventId : RoeEvent ID                          */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_DSP_SID86_NVM_USE == STD_ON )
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_WriteStorage
(
    const uint8     u1RoeEventId
)
{
    uint16              u2_BlockIdx;
    uint16              u2_BIdxStaRoe;
    Std_ReturnType      u1_RetChgEvId;
    uint8               u1_RoeBlockIdx;

    u2_BIdxStaRoe       = Dcm_Dsp_StorageMng_u2BIdx_StaRoe;
    u1_RoeBlockIdx      = DCM_DSP_SID86_ROE_BLOCKIDX_INVALID;

    u1_RetChgEvId   = Dcm_Dsp_SID86_ChangeEvtId2RoeBlkIdx( u1RoeEventId, &u1_RoeBlockIdx );
    if( u1_RetChgEvId == (Std_ReturnType)E_OK )
    {
        u2_BlockIdx = (uint16)( u2_BIdxStaRoe + (uint16)u1_RoeBlockIdx );
        (void)Dcm_Dsp_StorageMng_EnQueue( u2_BlockIdx );            /* no return check required */
    }

    return;
}
#endif /* DCM_DSP_SID86_NVM_USE == STD_ON */
#if ( DCM_DSP_SID86_NVM_USE == STD_OFF )
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_WriteStorage
(
    const uint8  u1RoeEventId      /* MISRA DEVIATION */
)
{
    /* no process */
    return ;
}
#endif /* DCM_DSP_SID86_NVM_USE == STD_OFF */


#if ( DCM_DSP_SID86_NVM_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_GetReadStorageCompleteFlag                 */
/* Description   | Get the ReadStorageCompleteFlag                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | boolean                                                  */
/*               | TRUE                                                     */
/*               | FALSE                                                    */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( boolean, DCM_CODE ) Dcm_Dsp_SID86_GetReadStorageCompleteFlag
(
    void
)
{
    return ( Dcm_Dsp_SID86_bReadStorageCompleteFlag );
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_SetErrorRoeEvent                           */
/* Description   | Set Error Data in RoeEventTable                          */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1RoeEventId     : RoeEvent ID                      */
/* Return Value  | void                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_SetErrorRoeEvent
(
    const uint8     u1RoeEventId
)
{
    /* Set Error Data for Dcm_Dsp_SID86_CheckEventTableData */
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1ServiceToRespondToRecord[0]      = DCM_DSP_SID86_CHK_SID22_SID;
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1ServiceToRespondToRecordLength   = (uint8)0U;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_CheckEventTableData                        */
/* Description   | Check Data in RoeEventTable                              */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1RoeEventId     : RoeEvent ID                      */
/* Return Value  | void                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_CheckEventTableData
(
    const uint8     u1RoeEventId
)
{
    uint32                      u4_ServToRespToRecLen;
    Std_ReturnType              u1_RetVal;
    Std_ReturnType              u1_CheckResult;
    uint8                       u1_SID;
    uint8                       u1_EventWindowTime;
    boolean                     b_RoeStart;
    boolean                     b_SupportFlg;

    u1_RetVal               = (Std_ReturnType)E_OK;
    u1_CheckResult          = (Std_ReturnType)E_OK;

    /* Check RoeEventTable */
    b_RoeStart  = Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].bRoeStart;
    if( b_RoeStart != (boolean)TRUE )
    {
        if( b_RoeStart != (boolean)FALSE )
        {
            u1_CheckResult  = (Std_ReturnType)E_NOT_OK;
        }
    }

    if( u1_CheckResult == (Std_ReturnType)E_OK )
    {
        /* Check ServiceToRespondToRecord */
        u1_SID                 = Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1ServiceToRespondToRecord[DCM_DSP_SID86_STRTR_OFFSET_SID];
        u4_ServToRespToRecLen  = Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1ServiceToRespondToRecordLength;
        if( u1_SID == (uint8)0U )
        {
            if( u4_ServToRespToRecLen != (uint32)0U )
            {
                u1_CheckResult          = (Std_ReturnType)E_NOT_OK;
            }
        }
        else
        {
            if( u4_ServToRespToRecLen == (uint32)0U )
            {
                u1_CheckResult          = (Std_ReturnType)E_NOT_OK;
            }
            else
            {
                if( u1_SID != DCM_DSP_SID86_CHK_SID22_SID )
                {
                    if( u1_SID != DCM_DSP_SID86_CHK_SID19_SID )
                    {
                        u1_CheckResult  = (Std_ReturnType)E_NOT_OK;
                    }
                }
            }
        }
    }

    if( u1_CheckResult == (Std_ReturnType)E_OK )
    {
        /* Check EventWindowTime */
        u1_EventWindowTime  = Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1EventWindow;
        if( u1_EventWindowTime != DCM_DSP_SID86_EVWIN_INVALID )
        {
            b_SupportFlg = Dcm_Dsp_SID86_IsSupportEventWindowTime( u1_EventWindowTime );
            if( b_SupportFlg != (boolean)TRUE )
            {
                u1_CheckResult  = (Std_ReturnType)E_NOT_OK;
            }
        }
    }

    if( u1_CheckResult != (Std_ReturnType)E_OK )
    {
        u1_RetVal   = (Std_ReturnType)E_NOT_OK;
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_ClearElemOfRoeEventTable                   */
/* Description   | Initialyze Element of RoeEventTable                      */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1RoeEventId      : RoeEvent ID                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_ClearElemOfRoeEventTable
(
    const uint8     u1RoeEventId
)
{
    uint8               u1_ParaCnt;

    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u2ConnectionId                     = DCM_DSP_SID86_CONID_INVALID;
    Dcm_Dsp_SID86_u2ConnectionIdMirror[u1RoeEventId]                            = Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u2ConnectionId;
    for( u1_ParaCnt = (uint8)0U; u1_ParaCnt < DCM_DSP_SID86_SERVICETORESPONDTORECORD_MAX; u1_ParaCnt++ )
    {
        Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1ServiceToRespondToRecord[u1_ParaCnt]
                                                                                = (uint8)0U;
    }
    for( u1_ParaCnt = (uint8)0U; u1_ParaCnt < DCM_DSP_SID86_EVENTTYPERECORD_MAX; u1_ParaCnt++ )
    {
        Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1EventTypeRecord[u1_ParaCnt]  = (uint8)0U;
    }
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1NumberOfIdentifiedEvents         = (uint8)0U;
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1Status                           = DCM_DSP_SID86_ROE_STS_CLEAR;
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1EventWindow                      = DCM_DSP_SID86_EVWIN_INVALID;
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1ServiceToRespondToRecordLength   = (uint8)0U;
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1RcvSubFunc                       = DCM_DSP_SID86_SUBFUNC_INVALID;
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].bRoeStart                          = (boolean)FALSE;
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].bDefaultSesReactive                = (boolean)FALSE;

    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_UpdateEventTableData                       */
/* Description   | Callback function for  event delivery registration of    */
/*               | Dcm_Dsp_SID86_ReadConfirmation                           */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1RoeEventId     : RoeEvent ID                      */
/* Return Value  | void                                                     */
/* Notes         | This function intends for the ROE event that succeeded   */
/*               | data by NvM                                              */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_UpdateEventTableData
(
    const uint8     u1RoeEventId
)
{
    Dcm_ComparisonValueType     st_Dcm_ComparisonValue;
    uint16                      u2_CurStartConId;
    uint16                      u2_SavedStartConId;
    uint8                       u1_NewStatus;
    uint8                       u1_RcvSubFunc;
    uint8                       u1_SubFunc;
    uint8                       u1_SrvToRespToRecLen;
    uint8                       u1_RoeBlkIdx;
    boolean                     b_RoeStart;
    boolean                     b_DefaultSesReactive;

    b_RoeStart                  = Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].bRoeStart;
    u1_SrvToRespToRecLen        = Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1ServiceToRespondToRecordLength;
    u1_RcvSubFunc               = Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1RcvSubFunc;
    u1_SubFunc                  = (uint8)( u1_RcvSubFunc & DCM_DSP_SID86_SUBFUNC_MASK );
    u1_NewStatus                = DCM_DSP_SID86_ROE_STS_CLEAR;
    b_DefaultSesReactive        = (boolean)FALSE;
    /* Determination of ROE event state */
    if( u1_SrvToRespToRecLen != (uint8)0U )
    {
        if( b_RoeStart == (boolean)TRUE )
        {
            /* Registered data exist, and order a start */
            u1_NewStatus            = DCM_DSP_SID86_ROE_STS_START;
            b_DefaultSesReactive    = (boolean)TRUE;
        }
        else
        {
            /* Registered data exist, but not order a start */
            u1_NewStatus            = DCM_DSP_SID86_ROE_STS_STOP;
        }
    }
    /* Update RoeEvent Status */
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1Status               = u1_NewStatus;
    Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].bDefaultSesReactive    = b_DefaultSesReactive;

    /* Perform Various Notices */
    if( u1_NewStatus == DCM_DSP_SID86_ROE_STS_STOP )
    {
        /* Change Mode to STOP */
        (void)Dcm_Dsp_SID86_Cnct_Sw_Roe( u1RoeEventId, DCM_EVENT_STOPPED );         /* no return check required */

        if( u1_SubFunc == DCM_DSP_SID86_SF07 )
        {
            /* SubFunc0x07 Call SWC Callout Function */
            /* Edit Comparison Structure Data  */
            Dcm_Dsp_SID86_EditComparisonData( &Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1EventTypeRecord[0], &st_Dcm_ComparisonValue );
            /* Call Callout Function SetComparisonOfValues */
            (void)Dcm_Dsp_SID86_SetComparisonOfValues( u1RoeEventId, &st_Dcm_ComparisonValue ); /* no return check required */
        }
    }
    else if( u1_NewStatus == DCM_DSP_SID86_ROE_STS_START )
    {
        (void)Dcm_Dsp_SID86_ChangeEvtId2RoeBlkIdx( u1RoeEventId, &u1_RoeBlkIdx );   /* no return check required */
        u2_SavedStartConId  = Dcm_Dsp_SID86_stStorageEventLogic[u1_RoeBlkIdx].u2StartConnectionId;
        u2_CurStartConId    = Dcm_Dsp_SID86_u2StartRequestConnectionId;
        if( u2_CurStartConId == DCM_DSP_SID86_CONID_INVALID )
        {
            if( u2_SavedStartConId != DCM_DSP_SID86_CONID_INVALID )
            {
                Dcm_Dsp_SID86_u2StartRequestConnectionId    = u2_SavedStartConId;
            }
        }

        if( u1_SubFunc == DCM_DSP_SID86_SF07 )
        {
            /* SubFunc0x07 Call SWC Callout Function */
            /* Edit Comparison Structure Data  */
            Dcm_Dsp_SID86_EditComparisonData( &Dcm_Dsp_SID86_stEventLogic[u1RoeEventId].u1EventTypeRecord[0], &st_Dcm_ComparisonValue );
            /* Call Callout Function SetComparisonOfValues */
            (void)Dcm_Dsp_SID86_SetComparisonOfValues( u1RoeEventId, &st_Dcm_ComparisonValue ); /* no return check required */
        }

        /* Change Mode to START */
        (void)Dcm_Dsp_SID86_Cnct_Sw_Roe( u1RoeEventId, DCM_EVENT_STARTED );         /* no return check required */

        if( u1_SubFunc == DCM_DSP_SID86_SF01 )
        {
            /* SubFunc0x01 Call DEM Function */
            Dem_DcmControlDTCStatusChangedNotification( (boolean)TRUE );
        }
    }
    else
    {
        /* Not Change Mode from a Clear State of the Default */
        /* No process */
    }

    /* Countup Registration Counter  */
    if( u1_SubFunc == DCM_DSP_SID86_SF03 )
    {
        Dcm_Dsp_SID86_u1NumChangeOfDataIdentfierEvents = (uint8)(Dcm_Dsp_SID86_u1NumChangeOfDataIdentfierEvents + (uint8)1U);
    }else if( u1_SubFunc == DCM_DSP_SID86_SF07 )
    {
        Dcm_Dsp_SID86_u1NumComparisionOfValueEvents = (uint8)(Dcm_Dsp_SID86_u1NumComparisionOfValueEvents + (uint8)1U);
    }
    else
    {
        /* No process */
    }

    return;
}
#endif /* DCM_DSP_SID86_NVM_USE == STD_ON */


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_IsUsedConnection                           */
/* Description   | Check an appointed connection is currently using in      */
/*               |   Started Event                                          */
/* Preconditions | None                                                     */
/* Parameters    | [IN]  u2ConnectionId : ConnectionId                      */
/* Return Value  | boolean                                                  */
/*               |    TRUE              : Used in Started Event             */
/*               |    FALSE             : Not Used in Started Event         */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( boolean, DCM_CODE ) Dcm_Dsp_SID86_IsUsedConnection
(
    const uint16        u2ConnectionId
)
{
    uint16              u2_ConnId;
    uint8               u1_NumOfRoeEvent;
    uint8               u1_EvCnt;
    uint8               u1_Status;
    boolean             b_ConnectionUsed;

    b_ConnectionUsed    = (boolean)FALSE;
    u1_NumOfRoeEvent    = Dcm_Dsp_SID86_u1NumOfRoeEvent;

    for( u1_EvCnt = (uint8)0U; u1_EvCnt < u1_NumOfRoeEvent; u1_EvCnt++ )
    {
        u1_Status       = Dcm_Dsp_SID86_stEventLogic[u1_EvCnt].u1Status;
        u2_ConnId       = Dcm_Dsp_SID86_stEventLogic[u1_EvCnt].u2ConnectionId;
        if( ( u1_Status == DCM_DSP_SID86_ROE_STS_START ) || ( u1_Status == DCM_DSP_SID86_ROE_STS_START_EVENT ) )
        {
            if( u2ConnectionId == u2_ConnId )
            {
                b_ConnectionUsed    = (boolean)TRUE;
                break;
            }
        }
    }

    return b_ConnectionUsed;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_MakeConnectionIdList                       */
/* Description   | Make a list of ConnectionId not to repeat                */
/* Preconditions | None                                                     */
/* Parameters    | [IN]  u2ConnId           : Target ConnectionID           */
/*               | [IN/OUT] ptListNum       : ConnectionID List Number      */
/*               | [IN/OUT] ptConnIdList    : ConnectionID List             */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_MakeConnectionIdList
(
    const uint16                                u2ConnId,
    P2VAR( uint8,  AUTOMATIC, DCM_APPL_DATA )   ptListNum,
    P2VAR( uint16, AUTOMATIC, DCM_APPL_DATA )   ptConnIdList
)
{
    uint8               u1_ListNum;
    uint8               u1_ListCnt;
    boolean             b_HitFlag;

    if( u2ConnId != DCM_DSP_SID86_CONID_INVALID )
    {
        u1_ListNum          = *ptListNum;
        if( u1_ListNum < DCM_DSP_SID86_CONNID_LIST_NUM )
        {
            if( u1_ListNum == (uint8)0U )
            {
                ptConnIdList[u1_ListNum]        = u2ConnId;
                u1_ListNum                      = DCM_DSP_SID86_LIST_START_CNT;
            }
            else
            {
                b_HitFlag   = (boolean)FALSE;
                for( u1_ListCnt = (uint8)0U; u1_ListCnt < u1_ListNum; u1_ListCnt++ )
                {
                    if( u2ConnId == ptConnIdList[u1_ListCnt] )
                    {
                        b_HitFlag = (boolean)TRUE;
                        break;
                    }
                }
                if( b_HitFlag == (boolean)FALSE)
                {
                    ptConnIdList[u1_ListNum]    = u2ConnId;
                    u1_ListNum = (uint8)(u1_ListNum + (uint8)1U);
                }
            }
        }
        *ptListNum = u1_ListNum;
    }

    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_MakeActConnectionIdList                    */
/* Description   | Make Active ConnectionId List from EventLogicTable       */
/* Preconditions | None                                                     */
/* Parameters    | [OUT] ptListNum          : ConnectionID List Number      */
/*               | [OUT] ptConnIdList       : ConnectionID List             */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_MakeActConnectionIdList
(
    P2VAR( uint8,  AUTOMATIC, DCM_APPL_DATA )   ptListNum,
    P2VAR( uint16, AUTOMATIC, DCM_APPL_DATA )   ptConnIdList
)
{
    uint16              u2_ConnId;
    uint16              u2_ConnIdMirror;
    uint8               u1_NumOfRoeEvent;
    uint8               u1_EvCnt;
    uint8               u1_Status;
    uint8               u1_ListNum;
    uint8               u1_ListCnt;
    boolean             b_HitFlag;

    u1_NumOfRoeEvent    = Dcm_Dsp_SID86_u1NumOfRoeEvent;
    u1_ListNum = (uint8)0U;

    /* lock */
    SchM_Enter_Dcm_Dsp_Roe();
    for( u1_EvCnt = (uint8)0U; u1_EvCnt < u1_NumOfRoeEvent; u1_EvCnt++ )
    {
        u1_Status       = Dcm_Dsp_SID86_stEventLogic[u1_EvCnt].u1Status;
        u2_ConnId       = Dcm_Dsp_SID86_stEventLogic[u1_EvCnt].u2ConnectionId;
        u2_ConnIdMirror = Dcm_Dsp_SID86_u2ConnectionIdMirror[u1_EvCnt];
        if( ( u1_Status == DCM_DSP_SID86_ROE_STS_START ) || ( u1_Status == DCM_DSP_SID86_ROE_STS_START_EVENT ) )
        {
            if( u2_ConnId == u2_ConnIdMirror )
            {
                if( u1_ListNum == (uint8)0U )
                {
                    ptConnIdList[u1_ListNum]    = u2_ConnId;
                    u1_ListNum                  = DCM_DSP_SID86_LIST_START_CNT;
                }
                else
                {
                    b_HitFlag   = (boolean)FALSE;
                    for( u1_ListCnt = (uint8)0U; u1_ListCnt < u1_ListNum; u1_ListCnt++ )
                    {
                        if( u2_ConnId == ptConnIdList[u1_ListCnt] )
                        {
                            b_HitFlag = (boolean)TRUE;
                            break;
                        }
                    }
                    if( b_HitFlag == (boolean)FALSE)
                    {
                        ptConnIdList[u1_ListNum] = u2_ConnId;
                        u1_ListNum = (uint8)(u1_ListNum + (uint8)1U);
                    }
                }
                if( u1_ListNum >= DCM_DSP_SID86_CONNID_LIST_NUM )
                {
                    break;
                }
            }
        }
    }
    /* unlock */
    SchM_Exit_Dcm_Dsp_Roe();

    *ptListNum = u1_ListNum;
    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_SetComActive                               */
/* Description   | Activate or inactivate the communication bus             */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1ListNum       : ConnectionID List Num             */
/*               | [IN] ptConnIdList    : ConnectionID List                 */
/*               | [IN] bActive         : Request Set Active Status         */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_SetComActive
(
    const uint8                                 u1ListNum,
    P2CONST( uint16, AUTOMATIC, DCM_APPL_DATA ) ptConnIdList,
    const boolean                               bActive
)
{
    uint16             u2_ConnectionId;
    uint8              u1_ListCnt;

    for( u1_ListCnt = (uint8)0U; u1_ListCnt < u1ListNum; u1_ListCnt++ )
    {
        u2_ConnectionId = ptConnIdList[u1_ListCnt];
        Dcm_Dsl_SetComActive( u2_ConnectionId, bActive );
    }

    return;
}


#endif /* DCM_SID86_ROE_USE == STD_ON */


#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-4-0         :2023-06-28                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
