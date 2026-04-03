/* Dcm_Dsp_SID86_Cfg_c(v5-3-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID86_Cfg/CODE                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../../Dsp/cfg/Dcm_Dsp_SID86_Cfg.h"
#include <Dcm/Dcm_Dsp_SID86_Callout.h>
#include <Dcm.h>

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
CONST( AB_83_ConstV Dcm_Dsp_SID86_RoeEvType, DCM_CONST_CONFIG )  Dcm_Dsp_SID86_stRoeEvent[DCM_DSP_SID86_ROE_EVENT_NUM] =

{
        /* EventProperties */   /* InitialEventStatus */       /* ServiceToRespondToRecordLength */
        { (uint16)0xA005U,      DCM_DSP_SID86_ROE_STOPPED,     (uint8)13U   }  /* Properties is Did            */
};
/* Data of EventWindowTime */
static CONST( AB_83_ConstV uint8, DCM_CONST_CONFIG )             Dcm_Dsp_SID86_u1EventWinTime[DCM_DSP_SID86_ROE_EVENWINDOWTIME_NUM] =
{
    DCM_DSP_SID86_ROE_EVENT_WINDOW_INFINITE
};
/* Data of RoeEventId2RoeBlockId */
static CONST( AB_83_ConstV uint8, DCM_CONST_CONFIG )             Dcm_Dsp_SID86_u1EvtId2RoeBlkIdx[DCM_DSP_SID86_ROE_EVENT_NUM] =
{
    (uint8)0U
};
/* Data of RoeBlockId2EventId */
static CONST( AB_83_ConstV uint8, DCM_CONST_CONFIG )             Dcm_Dsp_SID86_u1RoeBlkIdx2EvtId[DCM_DSP_SID86_ROE_BLOCKIDX_NUM] =
{
    (uint8)0U
};

/* Number of StorageRoeEventID */
CONST( AB_83_ConstV uint8, DCM_CONST_CONFIG )    Dcm_Dsp_SID86_u1NumOfStrageRoeEvent = DCM_DSP_SID86_ROE_BLOCKIDX_NUM;
/* Number of RoeEventID */
CONST( AB_83_ConstV uint8, DCM_CONST_CONFIG )    Dcm_Dsp_SID86_u1NumOfRoeEvent   = DCM_DSP_SID86_ROE_EVENT_NUM;
/* Value of DcmDspRoeInterMessageTime */
CONST( AB_83_ConstV uint16, DCM_CONST_CONFIG )   Dcm_Dsp_SID86_u2InterMessageTime    = DCM_DSP_SID86_ROE_INTMSGTIME;
/* Value of DcmDspRoeMaxNumChangeOfDataIdentfierEvents */
CONST( AB_83_ConstV uint8, DCM_CONST_CONFIG )    Dcm_Dsp_SID86_u1MaxNumChangeOfDataId    = DCM_DSP_SID86_ROE_CHGDID_MAX;
/* Value of DcmDspRoeMaxNumComparisionOfValueEvents */
CONST( AB_83_ConstV uint8, DCM_CONST_CONFIG )    Dcm_Dsp_SID86_u1MaxNumComparisionOfValue    = DCM_DSP_SID86_ROE_CMPDID_MAX;
/* Value of DcmDspRoeMaxNumberOfStoredDTCStatusChangedEvents */
CONST( AB_83_ConstV uint8, DCM_CONST_CONFIG )    Dcm_Dsp_SID86_u1MaxNumberOfStoredDTCStatusChangedEvents = DCM_DSP_SID86_ROE_STRDTC_MAX;
/* DcmDspRoeStopTransmissionSessionUpdate Type setting */
CONST( AB_83_ConstV uint8, DCM_CONST_CONFIG )  Dcm_Dsp_SID86_u1RoeStopTransmissionSessionUpdate = DCM_DSP_SID86_SESSION_UPDATE_ROE_CONTINUE;
/* RoeEventID of DcmDspRoeOnDTCStatusChange setting */
CONST( AB_83_ConstV uint8, DCM_CONST_CONFIG )    Dcm_Dsp_SID86_u1DTCStatusChangedEventId     = DCM_DSP_SID86_ROE_ONDTCSTSCHG_EVID;
/* Whether to use Queue for DTC events */
CONST( AB_83_ConstV boolean, DCM_CONST_CONFIG )  Dcm_Dsp_SID86_bUseQueueforDTCStatusChangedEvents = (boolean)FALSE;
/* Number of DcmDspRoeEventWindowTime setting */
static CONST( AB_83_ConstV uint8, DCM_CONST_CONFIG )    Dcm_Dsp_SID86_u1NumOfEventWindowTime = DCM_DSP_SID86_ROE_EVENWINDOWTIME_NUM;

#define DCM_STOP_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_IsSupportEventWindowTime                   */
/* Description   | Check In EventId is supported EventWindowTime            */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EvWinTime     : EventWindowTime                   */
/* Return Value  | boolean                                                  */
/*               |   TRUE               : EventWindowTime supported         */
/*               |   FALSE              : EventWindowTime not supported     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( boolean, DCM_CODE ) Dcm_Dsp_SID86_IsSupportEventWindowTime
(
    const   uint8   u1EvWinTime
)
{
    uint8                   u1_Cnt;
    uint8                   u1_NumOfEventWindowTime;
    boolean                 b_CheckResult;

    b_CheckResult           = (boolean)FALSE;
    u1_NumOfEventWindowTime = Dcm_Dsp_SID86_u1NumOfEventWindowTime;
    for( u1_Cnt = (uint8)0U; u1_Cnt < u1_NumOfEventWindowTime; u1_Cnt++ )
    {
        if( u1EvWinTime == Dcm_Dsp_SID86_u1EventWinTime[u1_Cnt] )
        {
            b_CheckResult   = (boolean)TRUE;
        }
    }

    return b_CheckResult;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_IsDTCEvent                                 */
/* Description   | Check In EventId equal DTCStatusChangedEventId           */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1RoeEventId     : Event ID                         */
/* Return Value  | boolean                                                  */
/*               |   TRUE             : EventId is DTCStatusChangedEvent    */
/*               |   FALSE            : EventId isn't DTCStatusChangedEvent */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( boolean, DCM_CODE ) Dcm_Dsp_SID86_IsDTCEvent
(
    const   uint8   u1RoeEventId
)
{
    boolean             b_CheckResult;

    b_CheckResult       = (boolean)FALSE;

    if( DCM_DSP_SID86_ROE_ONDTCSTSCHG_EVID == u1RoeEventId )
    {
        b_CheckResult   = (boolean)TRUE;
    }

    return b_CheckResult;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_SetComparisonOfValues                      */
/* Description   | Then there is a demand of onComparisonOfValues,          */
/*               | this function is started.                                */
/* Preconditions | None                                                     */
/* Parameters    | [IN]  u1RoeEventId  : RoeEventID                         */
/*               | [IN]  ptRecord      : Pointer to reception information   */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Accept onComparisonOfValues in     */
/*               |                       notice information                 */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_SetComparisonOfValues
(
    const uint8 u1RoeEventId,
    P2CONST( Dcm_ComparisonValueType, AUTOMATIC, DCM_APPL_DATA ) ptRecord
)
{
    Std_ReturnType u1_RetVal;
    
    u1_RetVal = Dcm_SetComparisonOfValues( u1RoeEventId, ptRecord );
    
    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_CheckRoeCondition                          */
/* Description   | Check Setup and Start Reuests.                           */
/* Preconditions | None                                                     */
/* Parameters    | [IN]  u1SubFunction  : SubFunction                       */
/*               | [IN]  u1EventWindowTime  : EventWindowTime               */
/*               | [IN]  ptEventTypeRecord  : Pointer to EventTypeRecord    */
/*               | [IN]  u1EventTypeRecordLength: Length of EventTypeRecord */
/*               | [OUT] ptErrorCode      : Pointer to NRC                  */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Accept this Request                */
/*               |   E_NOT_OK          : Not accept this Request            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_CheckRoeCondition
(
    const uint8 u1SubFunction,
    const uint8 u1EventWindowTime,
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA ) ptEventTypeRecord,
    const uint8 u1EventTypeRecordLength,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
)
{
    Std_ReturnType u1_RetVal;
    
    u1_RetVal = Dcm_CheckRoeCondition( u1SubFunction, u1EventWindowTime, ptEventTypeRecord, u1EventTypeRecordLength, ptErrorCode );
    
    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_IndicateRoeStatusChange                    */
/* Description   | Notify of a Status Change in the ROE Event State.        */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Accept this Request                */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_IndicateRoeStatusChange
(
    void
)
{
    Std_ReturnType u1_RetVal;
    
    u1_RetVal = Dcm_IndicateRoeStatusChange();
    
    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_ChangeEvtId2RoeBlkIdx                      */
/* Description   | Change RoeEventId to RoeBlockIndex                       */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1RoeEventId    : RoeEventId                        */
/*               | [OUT] ptRoeBlockIdx  : RoeBlockIndex                     */
/*               |        ( Relative position from the begining of          */
/*               |          StaRoe Block Index )                            */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK        : Valid RoeBlockIndex exists               */
/*               |   E_NOT_OK    : Valid RoeBlockIndex not exists           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_ChangeEvtId2RoeBlkIdx
(
    const   uint8                               u1RoeEventId,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA )    ptRoeBlockIdx
)
{
    Std_ReturnType          u1_RetVal;
    uint8                   u1_wkRoeBlockIdx;

    u1_RetVal               = (Std_ReturnType)E_NOT_OK;

    if( u1RoeEventId < DCM_DSP_SID86_ROE_EVENT_NUM )
    {
        u1_wkRoeBlockIdx    = Dcm_Dsp_SID86_u1EvtId2RoeBlkIdx[u1RoeEventId];
        if( u1_wkRoeBlockIdx != DCM_DSP_SID86_ROE_BLOCKIDX_INVALID )
        {
            u1_RetVal       = (Std_ReturnType)E_OK;
            *ptRoeBlockIdx  = u1_wkRoeBlockIdx;
        }
    }
    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID86_ChangeRoeBlkIdx2EvtId                      */
/* Description   | Change RoeBlockIndex to RoeEventId                       */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1RoeBlockIdx  : RoeBlockIndex                      */
/*               |        ( Relative position from the begining of          */
/*               |          StaRoe Block Index )                            */
/*               | [OUT] ptRoeEventId    : RoeEventId                       */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK        : The change is successful                 */
/*               |   E_NOT_OK    : The change is not successful             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID86_ChangeRoeBlkIdx2EvtId
(
    const uint8 u1RoeBlockIdx,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptRoeEventId
)
{
    Std_ReturnType          u1_RetVal;

    u1_RetVal               = (Std_ReturnType)E_NOT_OK;

    if( u1RoeBlockIdx < DCM_DSP_SID86_ROE_BLOCKIDX_NUM )
    {
        u1_RetVal       = (Std_ReturnType)E_OK;
        *ptRoeEventId   = Dcm_Dsp_SID86_u1RoeBlkIdx2EvtId[u1RoeBlockIdx];
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
