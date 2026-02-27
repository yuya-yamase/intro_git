/* Dcm_Dsp_SID86_Cfg_h(v5-3-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID86_Cfg/HEADER                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_DSP_SID86_CFG_H
#define DCM_DSP_SID86_CFG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSP_SID86_NVM_USE                           ( STD_ON )

#define DCM_DSP_SID86_ROE_INTMSGTIME                    ( (uint16)0U )
#define DCM_DSP_SID86_ROE_CHGDID_MAX                    ( (uint8)1U )
#define DCM_DSP_SID86_ROE_CMPDID_MAX                    ( (uint8)0U )
#define DCM_DSP_SID86_ROE_STRDTC_MAX                    ( (uint8)0U )

#define DCM_DSP_SID86_ROE_EVENT_NUM                     ( (uint8)1U )
#define DCM_DSP_SID86_ROE_ONDTCSTSCHG_EVID              ( (uint8)255U )

#define DCM_DSP_SID86_ROE_EVENWINDOWTIME_NUM            ( (uint8)1U )
#define DCM_DSP_SID86_ROE_EVENT_WINDOW_INFINITE         ( (uint8)2U )
#define DCM_DSP_SID86_ROE_EVENT_WINDOW_CURRENT_CYCLE    ( (uint8)3U )

#define DCM_DSP_SID86_ROE_CLEARED                       ( (uint8)0U)
#define DCM_DSP_SID86_ROE_STOPPED                       ( (uint8)1U)

#define DCM_DSP_SID86_EVENTTYPERECORD_MAX               ( (uint8)10U )
#define DCM_DSP_SID86_SERVICETORESPONDTORECORD_MAX      ( (uint8)13U )

#define DCM_DSP_SID86_SESSION_UPDATE_ROE_RESTART        ( (uint8)1U )
#define DCM_DSP_SID86_SESSION_UPDATE_ROE_STOP           ( (uint8)2U )
#define DCM_DSP_SID86_SESSION_UPDATE_ROE_CONTINUE       ( (uint8)3U )

#define DCM_DSP_SID86_ROE_BLOCKIDX_INVALID              ( (uint8)255U )
#define DCM_DSP_SID86_ROE_BLOCKIDX_NUM                  ( (uint8)1U )

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct
{
    uint16  u2EvProp;                   /* EventProperties                  */
    uint8   u1InitEvStatus;             /* InitialEventStatus               */
    uint8   u1ServToRespToRecLen;       /* ServiceToRespondToRecordLength   */
} Dcm_Dsp_SID86_RoeEvType;

typedef struct {
    uint16  u2ConnectionId;                                         /* ConnectionId of Setup Req.       */
    uint16  u2StartConnectionId;                                    /* ConnectionId of Start Req.       */
    uint8   u1ServiceToRespondToRecord[DCM_DSP_SID86_SERVICETORESPONDTORECORD_MAX];
                                                                    /* ServiceToRespondToRecord         */
    uint8   u1EventTypeRecord[DCM_DSP_SID86_EVENTTYPERECORD_MAX];   /* EventTypeRecord                  */
    uint8   u1EventWindowTime;                                      /* Setup EventWindowTime            */
    uint8   u1ServiceToRespondToRecordLength;                       /* ServiceToRespondToRecordLength   */
    uint8   u1RcvSubFunc;                                           /* Setup SubFunction(ReceiveImage)  */
    boolean bRoeStart;                                              /* Initial RoeRestart               */
} Dcm_Dsp_SID86_StorageEventLogicType;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

FUNC( boolean, DCM_CODE ) Dcm_Dsp_SID86_IsSupportEventWindowTime
(
    const   uint8   u1EvWinTime
);
FUNC( boolean, DCM_CODE ) Dcm_Dsp_SID86_IsDTCEvent
(
    const uint8 u1RoeEventId
);
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_SetComparisonOfValues
(
    const uint8 u1RoeEventId,
    P2CONST( Dcm_ComparisonValueType, AUTOMATIC, DCM_APPL_DATA ) ptRecord
);
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_CheckRoeCondition
(
    const uint8 u1SubFunction,
    const uint8 u1EventWindowTime,
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA ) ptEventTypeRecord,
    const uint8 u1EventTypeRecordLength,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
);
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_IndicateRoeStatusChange
(
    void
);
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_ChangeEvtId2RoeBlkIdx
(
    const uint8 u1RoeEventId,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptRoeBlockIdx
);
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_ChangeRoeBlkIdx2EvtId
(
    const uint8 u1RoeBlockIdx,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptRoeEventId
);

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
#define DCM_START_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>
/* Data of RoeEvent setting */
extern CONST( AB_83_ConstV Dcm_Dsp_SID86_RoeEvType, DCM_CONST_CONFIG )   Dcm_Dsp_SID86_stRoeEvent[DCM_DSP_SID86_ROE_EVENT_NUM ];

/* Number of RoeEventID */
extern CONST( AB_83_ConstV uint8, DCM_CONST_CONFIG )                     Dcm_Dsp_SID86_u1NumOfRoeEvent;
/* Value of DcmDspRoeInterMessageTime */
extern CONST( AB_83_ConstV uint16, DCM_CONST_CONFIG )                    Dcm_Dsp_SID86_u2InterMessageTime;
/* Value of DcmDspRoeMaxNumChangeOfDataIdentfierEvents */
extern CONST( AB_83_ConstV uint8, DCM_CONST_CONFIG )                     Dcm_Dsp_SID86_u1MaxNumChangeOfDataId;
/* Value of DcmDspRoeMaxNumComparisionOfValueEvents */
extern CONST( AB_83_ConstV uint8, DCM_CONST_CONFIG )                     Dcm_Dsp_SID86_u1MaxNumComparisionOfValue;
/* Value of DcmDspRoeMaxNumberOfStoredDTCStatusChangedEvents */
extern CONST( AB_83_ConstV uint8, DCM_CONST_CONFIG )                     Dcm_Dsp_SID86_u1MaxNumberOfStoredDTCStatusChangedEvents;
/* DcmDspRoeStopTransmissionSessionUpdate Type setting */
extern CONST( AB_83_ConstV uint8, DCM_CONST_CONFIG )                     Dcm_Dsp_SID86_u1RoeStopTransmissionSessionUpdate;
/* RoeEventID of DcmDspRoeOnDTCStatusChange setting */
extern CONST( AB_83_ConstV uint8, DCM_CONST_CONFIG )                     Dcm_Dsp_SID86_u1DTCStatusChangedEventId;
/* The number of RoeEvents to need a storage */
extern CONST( AB_83_ConstV uint8, DCM_CONST_CONFIG )                     Dcm_Dsp_SID86_u1NumOfStrageRoeEvent;
/* Whether to use Queue for DTC events */
extern CONST( AB_83_ConstV boolean, DCM_CONST_CONFIG )                   Dcm_Dsp_SID86_bUseQueueforDTCStatusChangedEvents;

#define DCM_STOP_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

#endif /* DCM_DSP_SID86_CFG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
