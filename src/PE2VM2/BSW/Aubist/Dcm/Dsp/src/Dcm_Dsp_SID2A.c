/* Dcm_Dsp_SID2A_c(v5-3-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID2A/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>

#if( DCM_PERIODIC_SEND_USE == STD_ON )

#include <Dcm/Dcm_Dsp_SID2A.h>
#include "../../Dsp/inc/Dcm_Dsp_MsgMaker.h"
#include <Dcm/Dcm_Dsp_Main.h>
#include "../../Dsd/inc/Dcm_Dsd_ServiceMng.h"
#include <Dcm/Dcm_Dsl_Ctrl.h>
#include <Dcm/Dcm_Main_Common.h>
#include <Dcm/Dcm_Main_EvtDistr.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSP_SID2A_SID                   ((uint8)0x2AU)
#define DCM_DSP_SID2A_REQLEN_MIN            ((uint8)1U)
#define DCM_DSP_SID2A_REQLEN_MIN_PDID       ((uint8)2U)

#define DCM_DSP_SID2A_REQDATA_TMMODE_SIZE   ((uint8)1U)
#define DCM_DSP_SID2A_REQDATA_TMMODEPOS     ((uint8)0U)
#define DCM_DSP_SID2A_REQDATA_PDID_POS      ((uint8)1U)

#define DCM_DSP_SID2A_PDID_LEN              ((uint32)1U)
#define DCM_DSP_SID2A_PDID_HIGHBITE         ((uint16)0xF200U)

#define DCM_DSP_SID2A_SUPPORT_CHK           ((uint8)0x00U)
#define DCM_DSP_SID2A_DIDAVAILABLE          ((uint8)0x01U)
#define DCM_DSP_SID2A_READ_DATA_LEN         ((uint8)0x02U)

#define DCM_DSP_SID2A_RET_OK                ((uint8)0x00U)
#define DCM_DSP_SID2A_RET_NO_DATA           ((uint8)0x01U)
#define DCM_DSP_SID2A_RET_PENDING           ((uint8)0x02U)
#define DCM_DSP_SID2A_RET_NOT_OK            ((uint8)0x03U)

#if( DCM_PERIODIC_DDDID_USE == STD_ON )
#define DCM_DSP_SID2A_MASKPDIDLO            ((uint16)0x00FFU)
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2A_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID2A_CancelProc
( void );
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID2A_CheckReqPdidProc
( void );
static FUNC( boolean, DCM_CODE ) Dcm_Dsp_SID2A_CheckPdidInfoTblExistProc
(
    P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) ptPdid,
    const uint16 u2ReqPdidNum
);
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID2A_InspectPdidValidProc
(
    const uint8 u1ProcessId
);
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID2A_ChkPdidInspectResultProc
(
    const boolean    bValidFlg
);
static FUNC(void, DCM_CODE) Dcm_Dsp_SID2A_SetPdidUpdInfTblProc
(
    const uint8                               u1ReqPdid,
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA)   ptPdidNum,
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA)   ptPdidUpdNum
);
static FUNC(uint8, DCM_CODE) Dcm_Dsp_SID2A_CheckSupportProc
( void );
static FUNC(uint8, DCM_CODE) Dcm_Dsp_SID2A_IsDidAvailableProc
(
    const Dcm_OpStatusType                   u1OpStatus
);
static FUNC(uint8, DCM_CODE) Dcm_Dsp_SID2A_ReadDataLenProc
(
    const Dcm_OpStatusType                   u1OpStatus
);
static FUNC(uint8, DCM_CODE) Dcm_Dsp_SID2A_CheckConditionProc
(
    void
);
static FUNC(Dcm_Main_ReturnCheckType, DCM_CODE) Dcm_Dsp_SID2A_CheckValidDidProc
(
    boolean b_SupportEnabledDid
);

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>
VAR( Dcm_Dsp_SID2A_PDidUpdateInfoType, DCM_VAR_NO_INIT ) Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[ DCM_DSP_SID2A_PDIDUPDINFO_TBL ];
VAR( uint16, DCM_VAR_NO_INIT ) Dcm_Dsp_SID2A_u2PDidUpdInfoNum;

static VAR( uint32,  DCM_VAR_NO_INIT ) Dcm_Dsp_SID2A_u4MaxDataLen;
static VAR( uint16,  DCM_VAR_NO_INIT ) Dcm_Dsp_SID2A_u2ConnectionId;
static VAR( uint8,   DCM_VAR_NO_INIT ) Dcm_Dsp_SID2A_u1ReqType;
static VAR( uint16,  DCM_VAR_NO_INIT ) Dcm_Dsp_SID2A_u2PreRegNum;
static VAR( uint16,  DCM_VAR_NO_INIT ) Dcm_Dsp_SID2A_u2PDIDToChkCnt;
static VAR( uint16,  DCM_VAR_NO_INIT ) Dcm_Dsp_SID2A_u2ReqPDIDNum;
static VAR( uint8,   DCM_VAR_NO_INIT ) Dcm_Dsp_SID2A_u1TransmissionMode;

static VAR( uint16,  DCM_VAR_NO_INIT ) Dcm_Dsp_SID2A_u2Did;
static VAR( uint16,  DCM_VAR_NO_INIT ) Dcm_Dsp_SID2A_u2DidIndex;
static VAR( uint8,   DCM_VAR_NO_INIT ) Dcm_Dsp_SID2A_u1KindOfDid;
static VAR( boolean, DCM_VAR_NO_INIT ) Dcm_Dsp_SID2A_bExistValidPDID;

static VAR( uint16,  DCM_VAR_NO_INIT ) Dcm_Dsp_SID2A_u2EachRatePreNum[DCM_DSP_PERIODIC_TMMODEINFO_TBL];

#define DCM_STOP_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST
#include <Dcm_MemMap.h>

#define DCM_STOP_SEC_CONST
#include <Dcm_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2A_Init                                       */
/* Description   | SID 2A initialization                                    */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID2A_Init    /* MISRA DEVIATION */
( void )
{
    uint16   u2_PdidUpdInfoNum;
    uint16   u2_DidReadNum;
    uint16   u2_Cnt;
    uint8    u1_MaxSchdulerNum;
    uint8    u1_Cnt;
    uint8    u1_TMModeInfoNum;

    Dcm_Dsp_SID2A_u4MaxDataLen       = (uint32)0U;
    Dcm_Dsp_SID2A_u2ConnectionId     = (uint16)0U;
    Dcm_Dsp_SID2A_u1ReqType          = (uint8)0U;
    Dcm_Dsp_SID2A_u2PreRegNum        = (uint16)0U;
    Dcm_Dsp_SID2A_u2PDIDToChkCnt     = (uint16)0U;
    Dcm_Dsp_SID2A_u2ReqPDIDNum       = (uint16)0U;
    Dcm_Dsp_SID2A_u1TransmissionMode = (uint8)0U;

    Dcm_Dsp_SID2A_u2Did              = (uint16)0U;
    Dcm_Dsp_SID2A_u2DidIndex         = (uint16)0U;
    Dcm_Dsp_SID2A_u1KindOfDid        = (uint8)0U;
    Dcm_Dsp_SID2A_bExistValidPDID    = (boolean)FALSE;

    Dcm_Dsp_SID2A_u2PDidUpdInfoNum   = (uint16)0U;

    u1_MaxSchdulerNum = Dcm_Dsp_Periodic_u1Max_Schduler_Num;
    u2_DidReadNum     = Dcm_Dsp_Periodic_u2Max_DidRead_Num;
    u2_PdidUpdInfoNum = (uint16)( (uint16)u1_MaxSchdulerNum + u2_DidReadNum );
    for( u2_Cnt = (uint16)0U; u2_Cnt < u2_PdidUpdInfoNum; u2_Cnt++ )
    {
        Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_Cnt].u2ConnectionID = (uint16)0U;
        Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_Cnt].u1Pdid         = (uint8)0U;
        Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_Cnt].u1ReqType      = (uint8)0U;
        Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_Cnt].u1Condition    = DCM_DSP_SID2A_CONDITION_INVALID;
    }

    u1_TMModeInfoNum = Dcm_Dsp_Periodic_u1TMModeInfoTbl;
    for( u1_Cnt = (uint8)0U; u1_Cnt < u1_TMModeInfoNum; u1_Cnt++ )
    {
        Dcm_Dsp_SID2A_u2EachRatePreNum[u1_Cnt] = (uint16)0U;
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_SID2A                                                */
/* Description   | Request processing of SID 2A                             */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus       : Operation state                    */
/*               | [IN] pMsgContext    : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID2A    /* MISRA DEVIATION */
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SID2A_InitialProc( pMsgContext );
        if( u1_RetVal == (Std_ReturnType)E_NOT_OK )
        {
            u1_RetVal = E_OK;
        }
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_CANCEL )
    {
        Dcm_Dsp_SID2A_CancelProc();
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2A_IsDidAvailableCbk                          */
/* Description   | Callback function for event delivery registration of     */
/*               | Xxx_IsDidAvailable                                       */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u1EventId        :Event ID                           */
/* Return Value  | void                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID2A_IsDidAvailableCbk   /* MISRA DEVIATION */
(
    const uint8 u1EventId   /* MISRA DEVIATION */
)
{
    (void)Dcm_Dsp_SID2A_InspectPdidValidProc( DCM_DSP_SID2A_DIDAVAILABLE );                      /* no return check required */

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2A_DidRangeDataLenCbk                         */
/* Description   | Callback function for  event delivery registration of    */
/*               | Xxx_ ReadDidRangeDataLength                              */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u1EventId        :Event ID                           */
/* Return Value  | void                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsp_SID2A_DidRangeDataLenCbk    /* MISRA DEVIATION */
(
    const uint8 u1EventId   /* MISRA DEVIATION */
)
{
    (void)Dcm_Dsp_SID2A_InspectPdidValidProc( DCM_DSP_SID2A_READ_DATA_LEN );                        /* no return check required */

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2A_Confirmation                               */
/* Description   | Complete transmission of SID 2A response message.        */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1IdContext     : Id Context                        */
/*               | [IN] u2ConnectionId  : Connection Id                     */
/*               | [IN] u1Status        : Status                            */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID2A_Confirmation    /* MISRA DEVIATION */
(
    const Dcm_IdContextType u1IdContext,             /* MISRA DEVIATION */
    const uint16 u2ConnectionId,                     /* MISRA DEVIATION */
    const Dcm_ConfirmationStatusType u1Status
)
{
    if( u1Status == (Dcm_ConfirmationStatusType)DCM_RES_POS_OK )
    {
        /* Update PDID information table */
        Dcm_Dsp_PeriodicMng_UpdatePDIDTbl( (uint8)Dcm_Dsp_SID2A_u2PreRegNum, Dcm_Dsp_SID2A_u1TransmissionMode );
    }

    Dcm_Dsp_SID2A_u2PDidUpdInfoNum = (uint16)0U;

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2A_NotifySecCtrl                              */
/* Description   | Notify of security level change.                         */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1SecLevelOld     : Security level before change    */
/*               | [IN] u1SecLevelNew     : Security level after change     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID2A_NotifySecCtrl /* MISRA DEVIATION */
(
    const Dcm_SecLevelType u1SecLevelOld,          /* MISRA DEVIATION */
    const Dcm_SecLevelType u1SecLevelNew
)
{
    uint16                          u2_Did;
    uint16                          u2_Index;
    uint16                          u2_PDIDNum;
    uint16                          u2_UpdPDIDNum;
    uint16                          u2_Cnt;
    uint8                           u1_KindOfDid;
    uint8                           u1_Condition;
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_RetChkSec;
    boolean                         b_DelFlg;

    /* There is at least one PDID to be updated */
    if( Dcm_Dsp_SID2A_u2PDidUpdInfoNum != (uint16)0 )
    {
        b_DelFlg      = (boolean)FALSE;
        u1_KindOfDid  = (uint8)0U;
        u2_Index      = (uint16)0U;
        u2_PDIDNum    = Dcm_Dsp_SID2A_u2PDidUpdInfoNum;
        u2_UpdPDIDNum = u2_PDIDNum;
        
        /* Check and Update PDID updating information table */
        for( u2_Cnt = (uint16)0U; u2_Cnt < u2_PDIDNum; u2_Cnt++ )
        {
            u2_Did = (uint16)( DCM_DSP_SID2A_PDID_HIGHBITE | (uint16)Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_Cnt].u1Pdid );
            u1_RetVal = Dcm_Dsp_PeriodicMng_ChkDID( u2_Did, &u1_KindOfDid, &u2_Index );
            if( u1_RetVal == (Std_ReturnType)E_OK )
            {
                u1_RetChkSec = Dcm_Dsp_DidMng_ChkDidInfo( u2_Index, u1_KindOfDid, DCM_DSP_DIDMNG_CHECK_READ_SEC, u1SecLevelNew );
                if( u1_RetChkSec == (Std_ReturnType)E_OK )
                {
                    /* no process */
                }
                else
                {
                    b_DelFlg = (boolean)TRUE;
                    Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_Cnt].u1Condition = DCM_DSP_SID2A_CONDITION_INVALID;
                }
            }
            else
            {
                b_DelFlg = (boolean)TRUE;
                Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_Cnt].u1Condition = DCM_DSP_SID2A_CONDITION_INVALID;
            }
        }

        if( b_DelFlg == (boolean)TRUE )
        {
            u2_UpdPDIDNum = (uint16)0U;
            for( u2_Cnt = (uint16)0U; u2_Cnt < u2_PDIDNum; u2_Cnt++ )
            {
                u1_Condition = Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_Cnt].u1Condition;
                if( u1_Condition != DCM_DSP_SID2A_CONDITION_INVALID )
                {
                    if( u2_Cnt != u2_UpdPDIDNum)
                    {
                        Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_UpdPDIDNum].u2ConnectionID = Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_Cnt].u2ConnectionID;
                        Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_UpdPDIDNum].u1Pdid         = Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_Cnt].u1Pdid;
                        Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_UpdPDIDNum].u1ReqType      = Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_Cnt].u1ReqType;
                        Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_UpdPDIDNum].u1Condition    = Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_Cnt].u1Condition;
                    }
                    u2_UpdPDIDNum = (uint16)(u2_UpdPDIDNum + (uint16)1U);
                }
            }
        }
        Dcm_Dsp_SID2A_u2PDidUpdInfoNum = u2_UpdPDIDNum;
    }

    /* Check and Update PDID information table */
    Dcm_Dsp_PeriodicMng_NotifySecCtrl( u1SecLevelNew );
 
    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2A_NotifySesCtrl                              */
/* Description   | Notify of session state change.                          */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1SesCtrlTypeOld     : Session before change        */
/*               | [IN] u1SesCtrlTypeNew     : Session after change         */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID2A_NotifySesCtrl /* MISRA DEVIATION */
(
    const Dcm_SesCtrlType u1SesCtrlTypeOld,        /* MISRA DEVIATION */
    const Dcm_SesCtrlType u1SesCtrlTypeNew
)
{
    uint16                          u2_Did;
    uint16                          u2_Index;
    uint16                          u2_PDIDNum;
    uint16                          u2_UpdPDIDNum;
    uint16                          u2_Cnt;
    PduIdType                       u2_RxPduId;
    uint8                           u1_KindOfDid;
    uint8                           u1_TransmissonUpdType;
    uint8                           u1_Condition;
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_RetChkSec;
    Std_ReturnType                  u1_RetSupported;
    boolean                         b_DelFlg;
    boolean                         b_ResetFlag;

    /* There is at least one PDID to be updated */
    if( Dcm_Dsp_SID2A_u2PDidUpdInfoNum != (uint16)0 )
    {
        u1_TransmissonUpdType = Dcm_Dsp_Periodic_u1TransmissonUpdType;
        if( u1_TransmissonUpdType == DCM_DSP_PERIODIC_TRANSMISSIONUPD_TYPE1 )
        {
            b_DelFlg      = (boolean)FALSE;
            u1_KindOfDid  = (uint8)0U;
            u2_Index      = (uint16)0U;
            u2_PDIDNum    = Dcm_Dsp_SID2A_u2PDidUpdInfoNum;
            u2_UpdPDIDNum = u2_PDIDNum;

            /* Check and Update PDID updating information table */
            for( u2_Cnt = (uint16)0U; u2_Cnt < u2_PDIDNum; u2_Cnt++ ) 
            {
                u2_Did = (uint16)( DCM_DSP_SID2A_PDID_HIGHBITE | (uint16)Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_Cnt].u1Pdid );
                u1_RetVal = Dcm_Dsp_PeriodicMng_ChkDID( u2_Did, &u1_KindOfDid, &u2_Index );
                if( u1_RetVal == (Std_ReturnType)E_OK )
                {
                    u1_RetChkSec = Dcm_Dsp_DidMng_ChkDidInfo( u2_Index, u1_KindOfDid, DCM_DSP_DIDMNG_CHECK_READ_SES, u1SesCtrlTypeNew );
                    if( u1_RetChkSec == (Std_ReturnType)E_OK )
                    {
                        /* no process */
                    }
                    else
                    {
                        b_DelFlg = (boolean)TRUE;
                        Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_Cnt].u1Condition = DCM_DSP_SID2A_CONDITION_INVALID;
                    }
                }
                else
                {
                    b_DelFlg = (boolean)TRUE;
                    Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_Cnt].u1Condition = DCM_DSP_SID2A_CONDITION_INVALID;
                }
            }
            if( b_DelFlg == (boolean)TRUE )
            {
                u2_UpdPDIDNum = (uint16)0U;
                for( u2_Cnt = (uint16)0U; u2_Cnt < u2_PDIDNum; u2_Cnt++ )
                {
                    u1_Condition = Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_Cnt].u1Condition;
                    if( u1_Condition != DCM_DSP_SID2A_CONDITION_INVALID )
                    {
                        if( u2_Cnt != u2_UpdPDIDNum)
                        {
                            Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_UpdPDIDNum].u2ConnectionID = Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_Cnt].u2ConnectionID;
                            Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_UpdPDIDNum].u1Pdid         = Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_Cnt].u1Pdid;
                            Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_UpdPDIDNum].u1ReqType      = Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_Cnt].u1ReqType;
                            Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_UpdPDIDNum].u1Condition    = Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_Cnt].u1Condition;
                        }
                        u2_UpdPDIDNum = (uint16)(u2_UpdPDIDNum + (uint16)1U);
                    }
                }
            }
            Dcm_Dsp_SID2A_u2PDidUpdInfoNum = u2_UpdPDIDNum;
        }
        else if( u1_TransmissonUpdType == DCM_DSP_PERIODIC_TRANSMISSIONUPD_TYPE3 )
        {
            b_ResetFlag = (boolean)FALSE;
            if( u1SesCtrlTypeNew == (uint8)DCM_DEFAULT_SESSION )
            {
                b_ResetFlag = (boolean)TRUE;
            }
            else
            {
                u2_RxPduId = 0x0000U;
                (void)Dcm_GetRxPduID( (uint16 *)&u2_RxPduId );
                u1_RetSupported = Dcm_Dsd_ChkServiceSupported( DCM_DSP_SID2A_SID, u2_RxPduId ,u1SesCtrlTypeNew );
                if( u1_RetSupported != (Std_ReturnType)E_OK )
                {
                    b_ResetFlag = (boolean)TRUE;
                }
            }
            
            if( b_ResetFlag == (boolean)TRUE )
            {
                /* Clear PDID updating information table */
                Dcm_Dsp_SID2A_u2PDidUpdInfoNum = (uint16)0U;
            }
            else
            {
                b_DelFlg      = (boolean)FALSE;
                u1_KindOfDid  = (uint8)0U;
                u2_Index      = (uint16)0U;
                u2_PDIDNum    = Dcm_Dsp_SID2A_u2PDidUpdInfoNum;
                u2_UpdPDIDNum = u2_PDIDNum;
                
                /* Check and Update PDID updating information table */
                for( u2_Cnt = (uint16)0U; u2_Cnt < u2_PDIDNum; u2_Cnt++ ) 
                {
                    u2_Did = (uint16)( DCM_DSP_SID2A_PDID_HIGHBITE | (uint16)Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_Cnt].u1Pdid );
                    u1_RetVal = Dcm_Dsp_PeriodicMng_ChkDID( u2_Did, &u1_KindOfDid, &u2_Index );
                    if( u1_RetVal == (Std_ReturnType)E_OK )
                    {
                        u1_RetChkSec = Dcm_Dsp_DidMng_ChkDidInfo( u2_Index, u1_KindOfDid, DCM_DSP_DIDMNG_CHECK_READ_SES, u1SesCtrlTypeNew );
                        if( u1_RetChkSec == (Std_ReturnType)E_OK )
                        {
                            /* no process */
                        }
                        else
                        {
                            b_DelFlg = (boolean)TRUE;
                            Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_Cnt].u1Condition = DCM_DSP_SID2A_CONDITION_INVALID;
                        }
                    }
                    else
                    {
                        b_DelFlg = (boolean)TRUE;
                        Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_Cnt].u1Condition = DCM_DSP_SID2A_CONDITION_INVALID;
                    }
                }
                if( b_DelFlg == (boolean)TRUE )
                {
                    u2_UpdPDIDNum = (uint16)0U;
                    for( u2_Cnt = (uint16)0U; u2_Cnt < u2_PDIDNum; u2_Cnt++ )
                    {
                        u1_Condition = Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_Cnt].u1Condition;
                        if( u1_Condition != DCM_DSP_SID2A_CONDITION_INVALID )
                        {
                            if( u2_Cnt != u2_UpdPDIDNum)
                            {
                                Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_UpdPDIDNum].u2ConnectionID = Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_Cnt].u2ConnectionID;
                                Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_UpdPDIDNum].u1Pdid         = Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_Cnt].u1Pdid;
                                Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_UpdPDIDNum].u1ReqType      = Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_Cnt].u1ReqType;
                                Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_UpdPDIDNum].u1Condition    = Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_Cnt].u1Condition;
                            }
                            u2_UpdPDIDNum = (uint16)(u2_UpdPDIDNum + (uint16)1U);
                        }
                    }
                }
                Dcm_Dsp_SID2A_u2PDidUpdInfoNum = u2_UpdPDIDNum;
            }
        }
        else
        {
            /* Clear PDID updating information table */
            Dcm_Dsp_SID2A_u2PDidUpdInfoNum = (uint16)0U;
        }
    }

    /* Check and Update PDID information table */
    Dcm_Dsp_PeriodicMng_NotifySesCtrl( u1SesCtrlTypeNew );

    return;
}

#if( DCM_PERIODIC_DDDID_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2A_PDidInfoChkByDDDidClr                      */
/* Description   | Process if DDDID table cleared                           */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2ClrDDDidInfo : Cleared DDDID                      */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID2A_PDidInfoChkByDDDidClr /* MISRA DEVIATION */
(
    const uint16 u2ClrDDDidInfo
)
{
    uint16                          u2_Did;
    uint16                          u2_Index;
    uint16                          u2_DynamicIndex;
    uint16                          u2_PDIDNum;
    uint16                          u2_UpdPDIDNum;
    uint16                          u2_Cnt;
    uint16                          u2_CntUpd;
    uint8                           u1_KindOfDid;
    uint8                           u1_NumOfSourceDid;
    uint8                           u1_ClrDDDid;
    uint8                           u1_Condition;
    Std_ReturnType                  u1_RetVal;
    boolean                         b_DeleteFlg;

    u2_PDIDNum        = Dcm_Dsp_SID2A_u2PDidUpdInfoNum;
    u2_UpdPDIDNum     = u2_PDIDNum;
    u1_KindOfDid      = (uint8)0U;
    u2_Index          = (uint16)0U;
    u1_NumOfSourceDid = (uint8)0U;
    u2_DynamicIndex   = (uint16)0U;

    if( u2ClrDDDidInfo == DCM_DSP_SID2A_DDDID_ALLCLR )
    {
        b_DeleteFlg = (boolean)FALSE;
        /* Check and Update PDID updating information table */
        for( u2_Cnt = (uint16)0U; u2_Cnt < u2_PDIDNum; u2_Cnt++ ) 
        {
            u2_Did = (uint16)( DCM_DSP_SID2A_PDID_HIGHBITE | (uint16)Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_Cnt].u1Pdid );
            u1_RetVal = Dcm_Dsp_PeriodicMng_ChkDID( u2_Did, &u1_KindOfDid, &u2_Index );
            if( u1_RetVal == (Std_ReturnType)E_OK )
            {
                if( u1_KindOfDid == DCM_DSP_DIDMNG_DID_DYNAMIC )
                {
                    /* Get NumOfSourceDid */
                    u1_RetVal = Dcm_Dsp_DidMng_ChkDynamic( u2_Did, &u1_NumOfSourceDid, &u2_DynamicIndex );
                    if( u1_RetVal == (Std_ReturnType)E_OK )
                    {
                        if( u1_NumOfSourceDid > (uint8)0U )
                        {
                            /* Do not delete Pdid update information */
                        }
                        else
                        {
                            /* Delete Pdid update information */
                            b_DeleteFlg = (boolean)TRUE;
                            Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_Cnt].u1Condition = DCM_DSP_SID2A_CONDITION_INVALID;
                        }
                    }
                }
            }
        }
        if( b_DeleteFlg == (boolean)TRUE )
        {
            u2_UpdPDIDNum = (uint16)0U;
            for( u2_Cnt = (uint16)0U; u2_Cnt < u2_PDIDNum; u2_Cnt++ )
            {
                u1_Condition = Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_Cnt].u1Condition;
                if( u1_Condition != DCM_DSP_SID2A_CONDITION_INVALID )
                {
                    if( u2_Cnt != u2_UpdPDIDNum)
                    {
                        Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_UpdPDIDNum].u2ConnectionID = Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_Cnt].u2ConnectionID;
                        Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_UpdPDIDNum].u1Pdid         = Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_Cnt].u1Pdid;
                        Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_UpdPDIDNum].u1ReqType      = Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_Cnt].u1ReqType;
                        Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_UpdPDIDNum].u1Condition    = Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_Cnt].u1Condition;
                    }
                    u2_UpdPDIDNum = (uint16)(u2_UpdPDIDNum + (uint16)1U);
                }
            }
        }
        /* Check and Update PDID information table */
        Dcm_Dsp_PeriodicMng_UpdPDidInfDDDidClr();
    }
    else
    {
        u1_ClrDDDid = (uint8)( u2ClrDDDidInfo & (uint16)DCM_DSP_SID2A_MASKPDIDLO );

        /* Check and Update PDID updating information table */
        for( u2_Cnt = (uint16)0U; u2_Cnt < u2_PDIDNum; u2_Cnt++ )
        {
            if( Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_Cnt].u1Pdid == u1_ClrDDDid )
            {
                /* Update PDID updating information table */
                for( u2_CntUpd = u2_Cnt; u2_CntUpd < ( u2_PDIDNum - (uint16)1U ); u2_CntUpd++ )
                {
                    Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_CntUpd].u2ConnectionID = Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_CntUpd + (uint16)1U].u2ConnectionID;
                    Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_CntUpd].u1Pdid         = Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_CntUpd + (uint16)1U].u1Pdid;
                    Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_CntUpd].u1ReqType      = Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_CntUpd + (uint16)1U].u1ReqType;
                    Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_CntUpd].u1Condition    = Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_CntUpd + (uint16)1U].u1Condition;
                }
                u2_UpdPDIDNum = (uint16)(u2_UpdPDIDNum - (uint16)1U);
                break;
            }
        }

        /* Check and Update PDID information table */
        Dcm_Dsp_PeriodicMng_UpdPDidInfSpecDDDidClr( u1_ClrDDDid );
    }
    Dcm_Dsp_SID2A_u2PDidUpdInfoNum = u2_UpdPDIDNum;

    return;
}
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON */


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2A_InitialProc                                */
/* Description   | Initial process of SID 2A request                        */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext   : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   E_NOT_OK          : Processing not normal              */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2A_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    uint32                          u4_ReqPdidNum;
    uint16                          u2_MaxDidReadNum;
    uint8                           u1_TransmissionMode;
    uint8                           u1_Cnt;
    uint8                           u1_TMModeInfoNum;
    uint8                           u1_PdidNum;
    uint8                           u1_ElmNo;
    uint8                           u1_PdidTbleRate;
    Std_ReturnType                  u1_RetVal;

    u1_RetVal = (Std_ReturnType)E_OK;

    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );

    Dcm_Dsp_Main_stMsgContext = *ptMsgContext;

    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

    Dcm_Dsp_SID2A_u4MaxDataLen     = (uint32)0U;
    Dcm_Dsp_SID2A_u2ConnectionId   = (uint16)0U;
    Dcm_Dsp_SID2A_u2DidIndex       = (uint16)0U;
    Dcm_Dsp_SID2A_u1KindOfDid      = (uint8)0U;
    Dcm_Dsp_SID2A_u2PDIDToChkCnt   = (uint16)0U;
    Dcm_Dsp_SID2A_u2ReqPDIDNum     = (uint16)0U;
    Dcm_Dsp_SID2A_u2PDidUpdInfoNum = (uint16)0U;
    Dcm_Dsp_SID2A_u1ReqType        = Dcm_Dsp_Main_stMsgContext.msgAddInfo.reqType;
    Dcm_Dsp_SID2A_bExistValidPDID  = (boolean)FALSE; /* Check for valid PDID under already periodic sending */
    Dcm_Dsp_SID2A_u1TransmissionMode = (uint8)0U;
    Dcm_Dsp_SID2A_u2Did            = (uint16)0U;
    Dcm_Dsp_SID2A_u2PreRegNum      = (uint16)Dcm_Dsp_Periodic_u1DidInfo_RegNum;

    u1_TMModeInfoNum = Dcm_Dsp_Periodic_u1TMModeInfoTbl;
    u2_MaxDidReadNum = Dcm_Dsp_Periodic_u2Max_DidRead_Num;
    
    for( u1_Cnt = (uint8)0U; u1_Cnt < u1_TMModeInfoNum; u1_Cnt++ )
    {
        Dcm_Dsp_SID2A_u2EachRatePreNum[u1_Cnt] = (uint16)0U;
    }
    u1_PdidNum       = Dcm_Dsp_Periodic_u1DidInfo_RegNum;
    for( u1_Cnt = 0U; u1_Cnt < u1_PdidNum; u1_Cnt++ )
    {
        u1_PdidTbleRate = Dcm_Dsp_Periodic_stPdidInfoTbl[u1_Cnt].u1Rate;
        if( ( u1_PdidTbleRate >= DCM_DSP_SID2A_CONDITION_SLOW ) && ( u1_PdidTbleRate <= DCM_DSP_SID2A_CONDITION_FAST ) ) 
        {        
            u1_ElmNo = u1_PdidTbleRate - (uint8)1U;
            Dcm_Dsp_SID2A_u2EachRatePreNum[u1_ElmNo] = (uint16)(Dcm_Dsp_SID2A_u2EachRatePreNum[u1_ElmNo] + (uint16)1U);
        }
    }

    /* Check minimum message length */
    if( Dcm_Dsp_Main_stMsgContext.reqDataLen >= DCM_DSP_SID2A_REQLEN_MIN )
    {
        /* Get transmissionMode */
        u1_TransmissionMode = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2A_REQDATA_TMMODEPOS];
        Dcm_Dsp_SID2A_u1TransmissionMode = u1_TransmissionMode;

        /* Check transmissionMode */
        if( u1_TransmissionMode != DCM_DSP_SID2A_CONDITION_STOP )
        {
            
            if( Dcm_Dsp_Main_stMsgContext.reqDataLen >= DCM_DSP_SID2A_REQLEN_MIN_PDID )
            {
                /* Get the number of Requested PDID */
                u4_ReqPdidNum = Dcm_Dsp_Main_stMsgContext.reqDataLen - (uint32)DCM_DSP_SID2A_REQDATA_TMMODE_SIZE;   /* no wrap around */
                
                /* Check maximum message length(the number of Requested PDID) */
                if( u4_ReqPdidNum <= (uint32)u2_MaxDidReadNum )
                {
                    if( ( u1_TransmissionMode == DCM_DSP_SID2A_CONDITION_SLOW )   ||
                        ( u1_TransmissionMode == DCM_DSP_SID2A_CONDITION_MEDIUM ) ||
                        ( u1_TransmissionMode == DCM_DSP_SID2A_CONDITION_FAST ) )
                    {
                        /* transmissionMode: sendAtSlowRate, sendAtMediumRate, sendAtFastRate */
                        if( Dcm_Dsp_stTransMissionModeInfoTbl[ u1_TransmissionMode - (uint8)1U ].u1MaxPdidNum > (uint8)0U )
                        {
                            /* Check Request PDID */
                            u1_RetVal = Dcm_Dsp_SID2A_CheckReqPdidProc();
                        }
                        else
                        {
                            /* NRC 0x31 */
                            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
                        }
                    }
                    else
                    {
                        /* NRC 0x31 */
                        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
                    }
                }
                else
                {
                    /* NRC 0x13 */
                    Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT );
                }
            }
            else
            {
                /* NRC 0x13 */
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT );
            }
        }
        else
        {
            /* transmissionMode: stopSending */
            if( Dcm_Dsp_Main_stMsgContext.reqDataLen == DCM_DSP_SID2A_REQLEN_MIN )
            {
                /* Stop all PDID */
                Dcm_Dsp_SID2A_u2PreRegNum = (uint16)0U;
                Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
            }
            else
            {
                /* Get the number of Requested PDID */
                u4_ReqPdidNum = Dcm_Dsp_Main_stMsgContext.reqDataLen - (uint32)DCM_DSP_SID2A_REQDATA_TMMODE_SIZE;   /* no wrap around */

                /* Check maximum message length(the number of Requested PDID) */
                if( u4_ReqPdidNum <= (uint32)u2_MaxDidReadNum )
                {
                    /* Stop some PDID */
                    /* Check Request PDID */
                    u1_RetVal = Dcm_Dsp_SID2A_CheckReqPdidProc();
                }
                else
                {
                    /* NRC 0x13 */
                    Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT );
                }
            }
        }
    }
    else
    {
        /* NRC 0x13 */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT );
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2A_CancelProc                                 */
/* Description   | Cancel process of SID 2A request                         */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID2A_CancelProc
( void )
{
    uint32                          u4_DataLength;
    uint16                          u2_Did;
    uint16                          u2_DidIndex;
    Dcm_DidSupportedType            u1_Supported;
    boolean                         b_UserNotifyFlag;

    u4_DataLength   = 0x00000000U;
    u2_Did          = Dcm_Dsp_SID2A_u2Did;
    u2_DidIndex     = Dcm_Dsp_SID2A_u2DidIndex;
    u1_Supported    = DCM_DID_NOT_SUPPORTED;

    b_UserNotifyFlag = Dcm_Dsp_Main_GetUserNotifyFlag();

    if( b_UserNotifyFlag == (boolean)TRUE )
    {
        if( Dcm_Dsp_SID2A_u1KindOfDid == DCM_DSP_DIDMNG_DID_RANGE )
        {
            ( void )Dcm_Dsp_DidMng_CallAvailableFnc( u2_DidIndex,
                                                     u2_Did,
                                                     DCM_CANCEL,
                                                     &u1_Supported
                                                     );                                     /* no return check required */

            ( void )Dcm_Dsp_DidMng_CallDataLengthFnc( u2_DidIndex,
                                                      u2_Did,
                                                      DCM_CANCEL,
                                                      &u4_DataLength
                                                      );                                    /* no return check required */

            (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID2A_DIDAVAILABLE,      (boolean)FALSE );     /* no return check required */
            (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID2A_RANGE_DATA_LEN,    (boolean)FALSE );     /* no return check required */
        }
        else
        {
            /* No process */
        }

        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

    }
    else
    {
        /* No process */
    }

    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2A_CheckReqPdidProc                           */
/* Description   | Check Request PDID                                       */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                                                     */
/*               | E_NOT_OK                                                 */
/*               | DCM_E_PENDING                                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID2A_CheckReqPdidProc
( void )
{
    Dcm_MsgLenType    u4_MaxDataLen;
    uint32            u4_ReqPdidNum;
    uint16            u2_ConnectionId;
    uint8             u1_TransmissionMode;
    uint8             u1_MaxSchdulerNum;
    Std_ReturnType    u1_RetVal;
    boolean           b_ChkResult;

    u1_RetVal           = E_NOT_OK;
    u1_TransmissionMode = Dcm_Dsp_SID2A_u1TransmissionMode;
    u1_MaxSchdulerNum   = Dcm_Dsp_Periodic_u1Max_Schduler_Num;

    /* Get the number of Requested PDID */
    u4_ReqPdidNum = Dcm_Dsp_Main_stMsgContext.reqDataLen - (uint32)DCM_DSP_SID2A_REQDATA_TMMODE_SIZE;   /* no wrap around */

    if( u1_TransmissionMode == DCM_DSP_SID2A_CONDITION_STOP )
    {
        b_ChkResult = (boolean)TRUE;
    }
    else
    {
        /* Check if the space for registration of PDID exist or not */
        if( Dcm_Dsp_Periodic_u1DidInfo_RegNum < u1_MaxSchdulerNum )
        {
            b_ChkResult = (boolean)TRUE;
        }
        else if( Dcm_Dsp_Periodic_u1DidInfo_RegNum == u1_MaxSchdulerNum )
        {
            b_ChkResult = Dcm_Dsp_SID2A_CheckPdidInfoTblExistProc( &Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2A_REQDATA_PDID_POS], (uint16)u4_ReqPdidNum );
        }
        else
        {
            b_ChkResult = (boolean)FALSE;
        }
    }

    if( b_ChkResult == (boolean)TRUE )
    {
        Dcm_Dsp_SID2A_u2ReqPDIDNum = (uint16)u4_ReqPdidNum;

        /* Get Connection Id */
        (void)Dcm_GetActiveProtocol( NULL_PTR, &u2_ConnectionId, NULL_PTR ); /* no return check required */
        Dcm_Dsp_SID2A_u2ConnectionId = u2_ConnectionId;

        /* Get MaxDataLen for Periodic Sending */
        u4_MaxDataLen = Dcm_Dsl_GetSizeOfPeriodicBuffer( u2_ConnectionId );
        Dcm_Dsp_SID2A_u4MaxDataLen = u4_MaxDataLen;

        /* Check support */
        u1_RetVal = Dcm_Dsp_SID2A_InspectPdidValidProc( DCM_DSP_SID2A_SUPPORT_CHK );

    }
    else
    {
        /* NRC 0x31 */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2A_CheckPdidInfoTblExistProc                  */
/* Description   | Check if requested PDIDs have already existed            */
/*               | in PDID information table                                */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptPdid         : Requested Periodic Did             */
/*               | [IN] u2ReqPdidNum   : Number of Requested Periodic Did   */
/* Return Value  | boolean                                                  */
/*               |   TRUE              : exist                              */
/*               |   FALSE             : not exist                          */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( boolean, DCM_CODE ) Dcm_Dsp_SID2A_CheckPdidInfoTblExistProc
(
    P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) ptPdid,
    const uint16 u2ReqPdidNum
)
{
    uint16                   u2_Cnt;
    uint8                    u1_PDIDNum;
    uint8                    u1_PdidTblCnt;
    boolean                  b_PDIDExist;

    b_PDIDExist          = (boolean)FALSE;
    u1_PDIDNum           = Dcm_Dsp_Periodic_u1DidInfo_RegNum;

    for( u1_PdidTblCnt = (uint8)0U; u1_PdidTblCnt < u1_PDIDNum; u1_PdidTblCnt++ )
    {
        for( u2_Cnt = (uint16)0U; u2_Cnt < u2ReqPdidNum; u2_Cnt++ )
        {
            if( ptPdid[u2_Cnt] == Dcm_Dsp_Periodic_stPdidInfoTbl[u1_PdidTblCnt].u1Pdid )
            {
                b_PDIDExist = (boolean)TRUE;
                break;
            }
        }
        if( b_PDIDExist == (boolean)TRUE )
        {
            break;
        }
    }

    return b_PDIDExist;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2A_InspectPdidValidProc                       */
/* Description   | Inspect PDID for validness                               */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u1ProcessId      :Process ID                         */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                                                     */
/*               | E_NOT_OK                                                 */
/*               | DCM_E_PENDING                                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC (Std_ReturnType, DCM_CODE) Dcm_Dsp_SID2A_InspectPdidValidProc
(
    const uint8 u1ProcessId
)
{
    uint16                          u2_Did;
    uint16                          u2_PrePDIDNum;
    uint16                          u2_PDIDUpdNum;
    uint16                          u2_ChkCnt;
    uint16                          u2_Cnt;
    uint16                          u2_ReqPdidNum;
    uint8                           u1_ReqPdid;
    uint8                           u1_ChkId;
    uint8                           u1_ChkReturnFnc;
    Std_ReturnType                  u1_RetVal;
    boolean                         b_OverlapFlag;
    boolean                         b_ValidFlag;
    boolean                         b_BreakFlag;

    u1_RetVal       = E_OK;

    u1_ChkId        = u1ProcessId;
    b_BreakFlag     = (boolean)FALSE;

    u2_ChkCnt           = Dcm_Dsp_SID2A_u2PDIDToChkCnt;
    u2_ReqPdidNum       = Dcm_Dsp_SID2A_u2ReqPDIDNum;
    u2_PDIDUpdNum       = Dcm_Dsp_SID2A_u2PDidUpdInfoNum;
    b_ValidFlag         = Dcm_Dsp_SID2A_bExistValidPDID;
    u2_PrePDIDNum       = Dcm_Dsp_SID2A_u2PreRegNum;

    for( u2_Cnt = u2_ChkCnt; u2_Cnt < u2_ReqPdidNum; u2_Cnt++ )
    {
        /* Get target PDID */
        u1_ReqPdid = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2A_REQDATA_PDID_POS + u2_Cnt];
        u2_Did = (uint16)( DCM_DSP_SID2A_PDID_HIGHBITE | (uint16)u1_ReqPdid );
        Dcm_Dsp_SID2A_u2Did = u2_Did;

        b_OverlapFlag = (boolean)FALSE;
        /* Check if requested PDID Overlap */
        for( u2_ChkCnt = 0U; u2_ChkCnt < u2_PDIDUpdNum; u2_ChkCnt++ )
        {
            if( u1_ReqPdid == Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_ChkCnt].u1Pdid )
            {
                b_OverlapFlag = (boolean)TRUE;
                break;
            }
        }

        if( b_OverlapFlag == (boolean)FALSE )
        {
            if( u1_ChkId == DCM_DSP_SID2A_DIDAVAILABLE )
            {
                u1_ChkReturnFnc = Dcm_Dsp_SID2A_IsDidAvailableProc( DCM_PENDING );
            }
            else if( u1_ChkId == DCM_DSP_SID2A_READ_DATA_LEN )
            {
                u1_ChkReturnFnc = Dcm_Dsp_SID2A_ReadDataLenProc( DCM_PENDING );
            }
            else
            {
                u1_ChkReturnFnc = Dcm_Dsp_SID2A_CheckSupportProc();
            }

            if( u1_ChkReturnFnc == DCM_DSP_SID2A_RET_OK )
            {
                b_ValidFlag = (boolean)TRUE; /* if there is 1 or more PDID which all inspection passed */
                u1_ChkId  = DCM_DSP_SID2A_SUPPORT_CHK;

                /* Set PDID update information table(Dcm_Dsp_SID2A_stPDIDUpdInfoTbl) */
                Dcm_Dsp_SID2A_SetPdidUpdInfTblProc( u1_ReqPdid, &u2_PrePDIDNum, &u2_PDIDUpdNum );
            }
            else if( u1_ChkReturnFnc == DCM_DSP_SID2A_RET_NO_DATA )
            {
                u1_ChkId  = DCM_DSP_SID2A_SUPPORT_CHK;
            }
            else if( u1_ChkReturnFnc == DCM_DSP_SID2A_RET_PENDING )
            {
                Dcm_Dsp_SID2A_u2PDIDToChkCnt = u2_Cnt;
                Dcm_Dsp_SID2A_u2PDidUpdInfoNum = u2_PDIDUpdNum;
                Dcm_Dsp_SID2A_bExistValidPDID = b_ValidFlag;
                Dcm_Dsp_SID2A_u2PreRegNum = u2_PrePDIDNum;
                u1_RetVal = DCM_E_PENDING;
                b_BreakFlag = (boolean)TRUE;
            }
            else
            {
                Dcm_Dsp_SID2A_u2PDidUpdInfoNum = (uint16)0U;
                b_BreakFlag = (boolean)TRUE;
                u1_RetVal = E_NOT_OK;
            }

            if( b_BreakFlag == (boolean)TRUE )
            {
                b_ValidFlag = (boolean)FALSE;
                break;
            }
        }
    }

    if( u1_RetVal == (Std_ReturnType)E_OK )
    {
        Dcm_Dsp_SID2A_u2PDidUpdInfoNum = u2_PDIDUpdNum;
        Dcm_Dsp_SID2A_u2PreRegNum = u2_PrePDIDNum;

        /* Check PDID inspection result of all */
        u1_RetVal = Dcm_Dsp_SID2A_ChkPdidInspectResultProc( b_ValidFlag );
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2A_ChkPdidInspectResultProc                   */
/* Description   | Check PDID inspection result                             */
/* Preconditions | None                                                     */
/* Parameters    | [IN]bValidFlg :If Exist PDID which all inspection passed */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                                                     */
/*               | E_NOT_OK                                                 */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC (Std_ReturnType, DCM_CODE) Dcm_Dsp_SID2A_ChkPdidInspectResultProc
(
    const boolean    bValidFlg
)
{
    uint16                          u2_PrePDIDNum;
    Std_ReturnType                  u1_RetVal;
    uint8                           u1_MaxSchdulerNum;
    uint8                           u1_TransmissionMode;
    boolean                         b_TransmissionMultiFlag;

    u1_RetVal               = E_OK;
    b_TransmissionMultiFlag = Dcm_Dsp_Periodic_bTransmissionMultiple;
    

    /* Check the value of DcmDspPeriodicTransmissionMultiple */
    if( b_TransmissionMultiFlag == (boolean)TRUE )
    {
        /* No process */
    }
    else
    {
        if( Dcm_Dsp_SID2A_u2EachRatePreNum[DCM_DSP_SID2A_CONDITION_SLOW - (uint8)1U] > (uint16)0U )
        {
            if( Dcm_Dsp_SID2A_u2EachRatePreNum[DCM_DSP_SID2A_CONDITION_MEDIUM - (uint8)1U] > (uint16)0U )
            {
                /* NRC 0x22 */
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_CONDITIONSNOTCORRECT );
                u1_RetVal = E_NOT_OK;
            }
            else if( Dcm_Dsp_SID2A_u2EachRatePreNum[DCM_DSP_SID2A_CONDITION_FAST - (uint8)1U] > (uint16)0U )
            {
                /* NRC 0x22 */
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_CONDITIONSNOTCORRECT );
                u1_RetVal = E_NOT_OK;
            }
            else
            {
                /* No process */
            }
        }
        else
        {
            if( Dcm_Dsp_SID2A_u2EachRatePreNum[DCM_DSP_SID2A_CONDITION_MEDIUM - (uint8)1U] > (uint16)0U )
            {
                if( Dcm_Dsp_SID2A_u2EachRatePreNum[DCM_DSP_SID2A_CONDITION_FAST - (uint8)1U] > (uint16)0U )
                {
                    /* NRC 0x22 */
                    Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_CONDITIONSNOTCORRECT );
                    u1_RetVal = E_NOT_OK;
                }
            }
        }
    }

    if( u1_RetVal == (Std_ReturnType)E_OK )
    {
        if( bValidFlg == (boolean)TRUE )
        {
            u1_TransmissionMode = Dcm_Dsp_SID2A_u1TransmissionMode;
            u2_PrePDIDNum       = Dcm_Dsp_SID2A_u2PreRegNum;

            /* Number of PDID which passed all check > 0 */
            if( u1_TransmissionMode == DCM_DSP_SID2A_CONDITION_STOP )
            {
                /* transmissionMode = stopSending(0x04) */

                Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
            }
            else
            {
                /* transmissionMode = sendAtSlowRate(0x01), sendAtMediumRate(0x02), sendAtFastRate(0x03) */

                u1_MaxSchdulerNum = Dcm_Dsp_Periodic_u1Max_Schduler_Num;
                /* Check DcmDspMaxPeriodicDidScheduler */
                if( u2_PrePDIDNum <= (uint16)u1_MaxSchdulerNum )
                {
                    /* Check DcmDspMaxPeriodicDid of requested rate */
                    if( Dcm_Dsp_SID2A_u2EachRatePreNum[u1_TransmissionMode - (uint8)1U] <= (uint16)Dcm_Dsp_stTransMissionModeInfoTbl[u1_TransmissionMode - (uint8)1U].u1MaxPdidNum )
                    {
                        Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
                    }
                    else
                    {
                        /* NRC 0x31 */
                        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
                        u1_RetVal = E_NOT_OK;
                    }
                }
                else
                {
                    /* NRC 0x31 */
                    Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
                    u1_RetVal = E_NOT_OK;
                }
            }
        }
        else
        {
            /* NRC 0x31 */
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
            u1_RetVal = E_NOT_OK;
        }
    }

    if( u1_RetVal == (Std_ReturnType)E_NOT_OK )
    {
        Dcm_Dsp_SID2A_u2PDidUpdInfoNum = (uint16)0U;
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2A_SetPDIDUodInfTblProc                       */
/* Description   | Set PDID update information table                        */
/* Preconditions | None                                                     */
/* Parameters    | [in]     u1ReqPdid : PDID                                */
/*               | [in/out] ptPdidNum : PDID information table Num          */
/*               | [in/out] ptPdidUpdNum: PDID Update information table Num */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC (void, DCM_CODE) Dcm_Dsp_SID2A_SetPdidUpdInfTblProc
(
    const uint8                               u1ReqPdid,
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA)   ptPdidNum,
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA)   ptPdidUpdNum
)
{
    uint16                          u2_ConnectionId;
    uint16                          u2_PdidTbleConnectionId;
    uint16                          u2_PDIDUpdNum;
    uint8                           u1_ReqType;
    uint8                           u1_CntPdidTbl;
    uint8                           u1_PdidNum;
    uint8                           u1_TransmissionMode;
    uint8                           u1_PdidTbleRate;
    boolean                         b_ExistFlag;

    u2_ConnectionId     = Dcm_Dsp_SID2A_u2ConnectionId;
    u1_ReqType          = Dcm_Dsp_SID2A_u1ReqType;
    u1_TransmissionMode = Dcm_Dsp_SID2A_u1TransmissionMode;
    u1_PdidNum          = Dcm_Dsp_Periodic_u1DidInfo_RegNum;
    u2_PDIDUpdNum       = *ptPdidUpdNum;

    /* Check PDID information table */
    b_ExistFlag = (boolean)FALSE;
    for( u1_CntPdidTbl = 0U; u1_CntPdidTbl < u1_PdidNum; u1_CntPdidTbl++ )
    {
        if( u1ReqPdid == Dcm_Dsp_Periodic_stPdidInfoTbl[u1_CntPdidTbl].u1Pdid )
        {
            u1_PdidTbleRate = Dcm_Dsp_Periodic_stPdidInfoTbl[u1_CntPdidTbl].u1Rate;
            if( u1_TransmissionMode == DCM_DSP_SID2A_CONDITION_STOP )
            {
                /* transmissionMode = stopSending(0x04) */
                (*ptPdidNum) = (uint16)((*ptPdidNum) - (uint16)1U);
                if( ( u1_PdidTbleRate >= DCM_DSP_SID2A_CONDITION_SLOW ) && ( u1_PdidTbleRate <= DCM_DSP_SID2A_CONDITION_FAST ) )
                {
                    Dcm_Dsp_SID2A_u2EachRatePreNum[u1_PdidTbleRate - (uint8)1U] = (uint16)(Dcm_Dsp_SID2A_u2EachRatePreNum[u1_PdidTbleRate - (uint8)1U] - (uint16)1U);
                }
            }
            else
            {
                u2_PdidTbleConnectionId = Dcm_Dsp_Periodic_stPdidInfoTbl[u1_CntPdidTbl].u2ConnectionID;
                /* transmissionMode = sendAtSlowRate(0x01), sendAtMediumRate(0x02), sendAtFastRate(0x03) */
                if( ( u1_TransmissionMode == u1_PdidTbleRate ) && 
                    ( u2_ConnectionId == u2_PdidTbleConnectionId ) )
                {
                    /* has already existed in PDID information table(same rate, same connectionID) */
                    b_ExistFlag = (boolean)TRUE;
                }
                else
                {
                    /* ADD the PDID to PDID Update information table for delete from PDID information table */
                    Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_PDIDUpdNum].u2ConnectionID = u2_PdidTbleConnectionId;
                    Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_PDIDUpdNum].u1Pdid         = u1ReqPdid;
                    Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_PDIDUpdNum].u1ReqType      = u1_ReqType;
                    Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_PDIDUpdNum].u1Condition    = DCM_DSP_SID2A_CONDITION_STOP;
                    u2_PDIDUpdNum = (uint16)(u2_PDIDUpdNum + (uint16)1U);

                    (*ptPdidNum) = (uint16)((*ptPdidNum) - (uint16)1U);
                    if( ( u1_PdidTbleRate >= DCM_DSP_SID2A_CONDITION_SLOW ) && ( u1_PdidTbleRate <= DCM_DSP_SID2A_CONDITION_FAST ) )
                    {                    
                        Dcm_Dsp_SID2A_u2EachRatePreNum[u1_PdidTbleRate - (uint8)1U] = (uint16)( Dcm_Dsp_SID2A_u2EachRatePreNum[u1_PdidTbleRate - (uint8)1U] - (uint16)1U);
                    }
                }
            }
        }
    }

    if( b_ExistFlag == (boolean)FALSE )
    {
        /* ADD the PDID to PDID Update information table */
        Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_PDIDUpdNum].u2ConnectionID = u2_ConnectionId;
        Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_PDIDUpdNum].u1Pdid         = u1ReqPdid;
        Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_PDIDUpdNum].u1ReqType      = u1_ReqType;
        Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_PDIDUpdNum].u1Condition    = u1_TransmissionMode;
        u2_PDIDUpdNum = (uint16)(u2_PDIDUpdNum + (uint16)1U);

        if( u1_TransmissionMode != DCM_DSP_SID2A_CONDITION_STOP )
        {
            (*ptPdidNum) = (uint16)((*ptPdidNum) + (uint16)1U);
            Dcm_Dsp_SID2A_u2EachRatePreNum[u1_TransmissionMode - (uint8)1U] = (uint16)(Dcm_Dsp_SID2A_u2EachRatePreNum[u1_TransmissionMode - (uint8)1U] + (uint16)1U);
        }
    }
    *ptPdidUpdNum = u2_PDIDUpdNum;
    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2A_CheckSupportProc                           */
/* Description   | Confirm whether request DID is supported                 */
/* Preconditions | None                                                     */
/* Parameters    | void                                                     */
/* Return Value  | uint8                                                    */
/*               | DCM_DSP_SID2A_RET_OK                                     */
/*               | DCM_DSP_SID2A_RET_NO_DATA                                */
/*               | DCM_DSP_SID2A_RET_PENDING                                */
/*               | DCM_DSP_SID2A_RET_NOT_OK                                 */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC (uint8, DCM_CODE) Dcm_Dsp_SID2A_CheckSupportProc
(
    void
)
{
    uint8                           u1_RetVal;
    Dcm_Main_ReturnCheckType        u1_RetValidDid;

    u1_RetValidDid = Dcm_Dsp_SID2A_CheckValidDidProc( (boolean)TRUE );

    if( u1_RetValidDid == DCM_MAIN_E_CHECK_OK )
    {
        if( Dcm_Dsp_SID2A_u1KindOfDid == DCM_DSP_DIDMNG_DID_DYNAMIC )
        {
            if( Dcm_Dsp_SID2A_u1TransmissionMode == DCM_DSP_SID2A_CONDITION_STOP )
            {
                /* In case of stopSending, the following check is unnecessary */
                u1_RetVal = DCM_DSP_SID2A_RET_OK;
            }
            else
            {
                u1_RetVal = Dcm_Dsp_SID2A_CheckConditionProc();
            }
        }
        else
        {
            u1_RetVal = Dcm_Dsp_SID2A_IsDidAvailableProc( DCM_INITIAL );
        }
    }
    else if( u1_RetValidDid == DCM_MAIN_E_CHECK_NOT_OK )
    {
        u1_RetVal = DCM_DSP_SID2A_RET_NO_DATA;
    }
    else
    {
        /* NRC 0x10 */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_GENERALREJECT );
        u1_RetVal = DCM_DSP_SID2A_RET_NOT_OK;
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2A_IsDidAvailableProc                         */
/* Description   | Confirm whether the requested DID is located in the      */
/*               | valid range within DidRange                              */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u1OpStatus       :Operation Status                   */
/* Return Value  | uint8                                                    */
/*               | DCM_DSP_SID2A_RET_OK                                     */
/*               | DCM_DSP_SID2A_RET_NO_DATA                                */
/*               | DCM_DSP_SID2A_RET_PENDING                                */
/*               | DCM_DSP_SID2A_RET_NOT_OK                                 */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(uint8, DCM_CODE) Dcm_Dsp_SID2A_IsDidAvailableProc
(
    const Dcm_OpStatusType u1OpStatus
)
{
    uint16                  u2_Did;
    uint16                  u2_DidIndex;
    uint8                   u1_RetVal;
    Std_ReturnType          u1_RetAvailableFnc;
    Std_ReturnType          u1_RetSupportedDid;
    Dcm_DidSupportedType    u1_Supported;

    u1_RetVal               = DCM_DSP_SID2A_RET_NOT_OK;
    u1_Supported            = DCM_DID_NOT_SUPPORTED;
    u2_Did                  = Dcm_Dsp_SID2A_u2Did;
    u2_DidIndex             = Dcm_Dsp_SID2A_u2DidIndex;

    /* Call Xxx_IsDidAvailable function */
    u1_RetAvailableFnc = Dcm_Dsp_DidMng_CallAvailableFnc( u2_DidIndex,
                                                          u2_Did,
                                                          u1OpStatus,
                                                          &u1_Supported
                                                          );

    if( u1_RetAvailableFnc == (Std_ReturnType)E_OK )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

        if( u1_Supported == (Dcm_DidSupportedType)DCM_DID_SUPPORTED )
        {
            u1_RetSupportedDid = Dcm_Dsp_DidMng_CheckSupportedDid( u2_Did, DCM_DID_REQTYPE_READ, Dcm_Dsp_Main_stMsgContext.dcmRxPduId );
            if( u1_RetSupportedDid == (Std_ReturnType)E_OK )
            {
                if( Dcm_Dsp_SID2A_u1TransmissionMode == DCM_DSP_SID2A_CONDITION_STOP )
                {
                    /* In case of stopSending, the following check is unnecessary */
                    u1_RetVal = DCM_DSP_SID2A_RET_OK;
                }
                else
                {
                    u1_RetVal = Dcm_Dsp_SID2A_CheckConditionProc();
                }
            }
            else
            {
                u1_RetVal = DCM_DSP_SID2A_RET_NO_DATA;
            }
        }
        else
        {
            u1_RetVal = DCM_DSP_SID2A_RET_NO_DATA;
        }
    }
    else if( u1_RetAvailableFnc == (Std_ReturnType)DCM_E_PENDING )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        ( void )Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID2A_DIDAVAILABLE );              /* no return check required */
        u1_RetVal = DCM_DSP_SID2A_RET_PENDING;
    }
    else
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        /* NRC 0x10 */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_GENERALREJECT );
    }

    return u1_RetVal;

}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2A_ReadDataLenProc                            */
/* Description   | DID data length acquisition processing                   */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u1OpStatus       :Operation Status                   */
/* Return Value  | uint8                                                    */
/*               | DCM_DSP_SID2A_RET_OK                                     */
/*               | DCM_DSP_SID2A_RET_NO_DATA                                */
/*               | DCM_DSP_SID2A_RET_PENDING                                */
/*               | DCM_DSP_SID2A_RET_NOT_OK                                 */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(uint8, DCM_CODE) Dcm_Dsp_SID2A_ReadDataLenProc
(
    const Dcm_OpStatusType                    u1OpStatus
)
{
    uint32                  u4_DidDataLen;
    uint16                  u2_Did;
    uint16                  u2_DidIndex;
    uint8                   u1_RetVal;
    Std_ReturnType          u1_RetGetDataLen;

    u1_RetVal     = DCM_DSP_SID2A_RET_OK;
    u2_Did        = Dcm_Dsp_SID2A_u2Did;
    u2_DidIndex   = Dcm_Dsp_SID2A_u2DidIndex;
    u4_DidDataLen = (uint32)0U;

    if( Dcm_Dsp_SID2A_u1KindOfDid == DCM_DSP_DIDMNG_DID_RANGE )
    {
        u1_RetGetDataLen = Dcm_Dsp_DidMng_CallDataLengthFnc( u2_DidIndex,
                                                             u2_Did,
                                                             u1OpStatus,
                                                             &u4_DidDataLen
                                                             );
    }
    else
    {
        u1_RetGetDataLen = Dcm_Dsp_DidMng_GetDynDidDataLen( u2_DidIndex,
                                                            &u4_DidDataLen
                                                            );
    }

    if( u1_RetGetDataLen == (Std_ReturnType)E_OK )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

        if( u4_DidDataLen <= ( Dcm_Dsp_SID2A_u4MaxDataLen - DCM_DSP_SID2A_PDID_LEN ) )  /* no wrap around */
        {
            /* no process */
        }
        else
        {
            u1_RetVal = DCM_DSP_SID2A_RET_NO_DATA;
        }
    }
    else if( u1_RetGetDataLen == (Std_ReturnType)DCM_E_PENDING )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        ( void )Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID2A_RANGE_DATA_LEN );            /* no return check required */
        u1_RetVal = DCM_DSP_SID2A_RET_PENDING;
    }
    else
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        /* NRC 0x10 */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_GENERALREJECT );
        u1_RetVal = DCM_DSP_SID2A_RET_NOT_OK;
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2A_CheckConditionProc                         */
/* Description   | Check whether the prerequisite is satisfied for          */
/*               | the requested DID                                        */
/* Preconditions | None                                                     */
/* Parameters    | void                                                     */
/* Return Value  | uint8                                                    */
/*               | DCM_DSP_SID2A_RET_OK                                     */
/*               | DCM_DSP_SID2A_RET_NO_DATA                                */
/*               | DCM_DSP_SID2A_RET_PENDING                                */
/*               | DCM_DSP_SID2A_RET_NOT_OK                                 */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(uint8, DCM_CODE) Dcm_Dsp_SID2A_CheckConditionProc
(
    void
)
{
    uint16                          u2_DidIndex;
    uint16                          u2_DynamicIndex;
    uint16                          u2_Did;
    uint8                           u1_NumOfSourceDid;
    uint8                           u1_KindOfDid;
    uint8                           u1_RetVal;
    Std_ReturnType                  u1_RetChkSes;
    Std_ReturnType                  u1_RetChkSec;
    Std_ReturnType                  u1_RetReadDataLen;
    Std_ReturnType                  u1_RetChkModeRule;
    Std_ReturnType                  u1_RetChkDynamicDid;
    Dcm_SesCtrlType                 u1_SesCtrlType;
    Dcm_SecLevelType                u1_SecLevel;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;
    boolean                         b_KeepChkFlg;

    u1_RetVal         = DCM_DSP_SID2A_RET_NOT_OK;
    u1_ErrorCode      = (Dcm_NegativeResponseCodeType)0x00U;
    b_KeepChkFlg      = (boolean)FALSE;
    u1_NumOfSourceDid = (uint8)0U;
    u2_DynamicIndex   = (uint16)0U;
    u1_SesCtrlType    = DCM_DEFAULT_SESSION;
    u1_SecLevel       = DCM_SEC_LEV_LOCKED;
    u2_Did            = Dcm_Dsp_SID2A_u2Did;
    u2_DidIndex       = Dcm_Dsp_SID2A_u2DidIndex;
    u1_KindOfDid      = Dcm_Dsp_SID2A_u1KindOfDid;

    ( void )Dcm_GetSesCtrlType( &u1_SesCtrlType );      /* no return check required */

    u1_RetChkSes = Dcm_Dsp_DidMng_ChkDidInfo( u2_DidIndex, u1_KindOfDid, DCM_DSP_DIDMNG_CHECK_READ_SES, u1_SesCtrlType );

    if( u1_RetChkSes == (Std_ReturnType)E_OK )
    {
        if( u1_KindOfDid == DCM_DSP_DIDMNG_DID_DYNAMIC )
        {
            u1_RetChkDynamicDid = Dcm_Dsp_DidMng_ChkDynamic( u2_Did, &u1_NumOfSourceDid, &u2_DynamicIndex );

            if( u1_RetChkDynamicDid == (Std_ReturnType)E_OK )
            {
                if( u1_NumOfSourceDid > (uint8)0U )
                {
                    b_KeepChkFlg = (boolean)TRUE;
                }
                else
                {
                    u1_RetVal = DCM_DSP_SID2A_RET_NO_DATA;
                }
            }
        }
        else
        {
            b_KeepChkFlg = (boolean)TRUE;
        }
    }
    else
    {
        u1_RetVal = DCM_DSP_SID2A_RET_NO_DATA;
    }

    if( b_KeepChkFlg == (boolean)TRUE )
    {
        u1_RetReadDataLen = Dcm_Dsp_SID2A_ReadDataLenProc( DCM_INITIAL );
        if( u1_RetReadDataLen == DCM_DSP_SID2A_RET_OK )
        {
            ( void )Dcm_GetSecurityLevel( &u1_SecLevel );   /* no return check required */
            u1_RetChkSec = Dcm_Dsp_DidMng_ChkDidInfo( u2_DidIndex, u1_KindOfDid, DCM_DSP_DIDMNG_CHECK_READ_SEC, u1_SecLevel );

            if( u1_RetChkSec == (Std_ReturnType)E_OK )
            {
                if( u1_KindOfDid == DCM_DSP_DIDMNG_DID_RANGE )
                {
                    u1_RetChkModeRule = Dcm_Dsp_DidMng_CallModeRuleFnc( u2_DidIndex, DCM_DSP_DIDMNG_CHECK_READ_MR, Dcm_Dsp_SID2A_u2Did, &u1_ErrorCode );
                }
                else
                {
                    u1_RetChkModeRule = Dcm_Dsp_DidMng_DynDidModeRuleFnc( u2_DidIndex, DCM_DSP_DIDMNG_CHECK_READ_MR, &u1_ErrorCode );

                }
                if( u1_RetChkModeRule == (Std_ReturnType)E_OK )
                {
                    u1_RetVal = DCM_DSP_SID2A_RET_OK;
                }
                else if( u1_RetChkModeRule == (Std_ReturnType)E_NOT_OK )
                {
                    if( u1_ErrorCode != (Dcm_NegativeResponseCodeType)0x00U )
                    {
                        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_ErrorCode );
                    }
                    else
                    {
                        /* NRC 0x10 */
                        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_GENERALREJECT );
                    }
                }
                else
                {
                    /* NRC 0x10 */
                    Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_GENERALREJECT );
                }

            }
            else
            {
                /* NRC 0x33 */
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_SECURITYACCESSDENIED );
            }
        }
        else
        {
            u1_RetVal = u1_RetReadDataLen;
        }
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2A_CheckValidDidProc                          */
/* Description   | Check if the DIDRange table has a valid DID              */
/* Preconditions | None                                                     */
/* Parameters    | void                                                     */
/* Return Value  | Dcm_Main_ReturnCheckType                                 */
/*               | DCM_MAIN_E_CHECK_OK                                      */
/*               | DCM_MAIN_E_CHECK_NOT_OK                                  */
/*               | DCM_MAIN_E_INVALID_CONFIG                                */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Dcm_Main_ReturnCheckType,DCM_CODE) Dcm_Dsp_SID2A_CheckValidDidProc
(
    boolean b_SupportEnabledDid
)
{
    uint16                          u2_IndividualDidIndex;
    uint16                          u2_RangeIndex;
    uint16                          u2_Did;
    uint16                          u2_DynamicIndex;
    uint8                           u1_IndividualDidCRWSupport;
    uint8                           u1_CRWSupport;
    uint8                           u1_ChkReadSupport;
    uint8                           u1_NumOfSourceDid;
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_RetChkDynamicDid;
    Std_ReturnType                  u1_RetSupportedDid;
    Dcm_Main_ReturnCheckType        u1_RetIndividualDid;
    Dcm_Main_ReturnCheckType        u1_RetDidRange;
    boolean                         b_IndividualDid;
    boolean                         b_ChkDynamicExe;

    u1_RetVal                  = DCM_MAIN_E_CHECK_NOT_OK;
    b_IndividualDid            = (boolean)FALSE;
    u2_Did                     = Dcm_Dsp_SID2A_u2Did;
    u2_DynamicIndex            = (uint16)0U;
    u2_RangeIndex              = (uint16)0U;
    u2_IndividualDidIndex      = (uint16)0U;
    u1_IndividualDidCRWSupport = (uint8)0U;
    u1_CRWSupport              = (uint8)0U;
    u1_NumOfSourceDid          = (uint8)0U;

    /* Check DID Support IndividualDID */
    u1_RetIndividualDid = Dcm_Dsp_DidMng_ChkDid( u2_Did,
                                                 DCM_DSP_DIDMNG_DID,
                                                 &u2_IndividualDidIndex,
                                                 &u1_IndividualDidCRWSupport
                                                 );

    if( u1_RetIndividualDid == DCM_MAIN_E_CHECK_OK )
    {
        u1_ChkReadSupport = u1_IndividualDidCRWSupport & DCM_DSP_DIDMNG_READ_ONLY_DYN;

        if( u1_ChkReadSupport == DCM_DSP_DIDMNG_READ_ONLY_DYN )
        {
            if( b_SupportEnabledDid == (boolean)TRUE )
            {
                u1_RetSupportedDid = Dcm_Dsp_DidMng_CheckSupportedDid( u2_Did, DCM_DID_REQTYPE_READ, Dcm_Dsp_Main_stMsgContext.dcmRxPduId );
                if( u1_RetSupportedDid == (Std_ReturnType)E_OK )
                {
                    b_ChkDynamicExe = (boolean)TRUE;
                }
                else
                {
                    b_ChkDynamicExe = (boolean)FALSE;
                    b_IndividualDid = (boolean)TRUE;
                }
            }
            else
            {
                b_ChkDynamicExe = (boolean)TRUE;
            }

            if( b_ChkDynamicExe == (boolean)TRUE )
            {
                u1_RetChkDynamicDid = Dcm_Dsp_DidMng_ChkDynamic( u2_Did, &u1_NumOfSourceDid, &u2_DynamicIndex );

                if( u1_RetChkDynamicDid == (Std_ReturnType)E_OK )
                {
                    if( u1_NumOfSourceDid > (uint8)0U )
                    {
                        Dcm_Dsp_SID2A_u1KindOfDid = DCM_DSP_DIDMNG_DID_DYNAMIC;
                        Dcm_Dsp_SID2A_u2DidIndex  = u2_DynamicIndex;

                        b_IndividualDid = (boolean)TRUE;
                        u1_RetVal = DCM_MAIN_E_CHECK_OK;
                    }
                    else
                    {
                        /* no process */
                    }
                }
            }
            else
            {
                /* no process */
            }
        }
        else
        {
            /* no process */
        }
    }
    else
    {
        /* no process */
    }

    if( b_IndividualDid == (boolean)FALSE)
    {
        /* Check DID Support Range */
        u1_RetDidRange = Dcm_Dsp_DidMng_ChkDid( u2_Did,
                                                DCM_DSP_DIDMNG_DID_RANGE,
                                                &u2_RangeIndex,
                                                &u1_CRWSupport
                                                );

        if( u1_RetDidRange == DCM_MAIN_E_CHECK_OK )
        {
            u1_ChkReadSupport = u1_CRWSupport & DCM_DSP_DIDMNG_READ_ONLY;

            if( u1_ChkReadSupport == DCM_DSP_DIDMNG_READ_ONLY )
            {

                Dcm_Dsp_SID2A_u1KindOfDid = DCM_DSP_DIDMNG_DID_RANGE;
                Dcm_Dsp_SID2A_u2DidIndex  = u2_RangeIndex;

                u1_RetVal = DCM_MAIN_E_CHECK_OK;
            }
            else
            {
                /* no process */
            }
        }
        else if( u1_RetDidRange == DCM_MAIN_E_CHECK_NOT_OK )
        {
            /* no process */
        }
        else
        {
            u1_RetVal = DCM_MAIN_E_INVALID_CONFIG;
        }
    }
    else
    {
        /* no process */
    }

    return u1_RetVal;
}


#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
#endif /* DCM_PERIODIC_SEND_USE */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-09-26                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
