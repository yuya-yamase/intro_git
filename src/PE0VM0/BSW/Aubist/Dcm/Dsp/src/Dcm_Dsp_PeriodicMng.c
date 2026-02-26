/* Dcm_Dsp_PeriodicMng_c(v5-3-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_PeriodicMng/CODE                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>

#if( DCM_PERIODIC_SEND_USE == STD_ON )

#include <Dcm/Dcm_Dsp_PeriodicMng.h>
#include <Dcm/Dcm_Dsp_SID2A.h>
#include <Dcm/Dcm_Dsp_Main.h>
#include "../../Dsd/inc/Dcm_Dsd_ServiceMng.h"
#include <Dcm/Dcm_Dsl_Ctrl.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Periodic Transfer Status Management */
#define DCM_DSP_PERIODICTRANSFER_ON                ((uint8)1U)
#define DCM_DSP_PERIODICTRANSFER_OFF               ((uint8)0U)

/* Periodic Information Table element Status */
#define DCM_DSP_PERIODIC_INIT                      ((uint8)0U)
#define DCM_DSP_PERIODIC_REGISTWAIT                ((uint8)1U)
#define DCM_DSP_PERIODIC_DOWNCOUNT                 ((uint8)2U)
#define DCM_DSP_PERIODIC_SENDWAIT                  ((uint8)3U)
#define DCM_DSP_PERIODIC_READWAIT                  ((uint8)4U)
#define DCM_DSP_PERIODIC_SENDCOMPWAIT              ((uint8)5U)

#define DCM_DSP_PERIODIC_TMCOUNTER_INITIAL         ((uint32)0x00000000U)

#define DCM_DSP_PERIODIC_TMMODEINFOTBL_INDEX       ((uint8)1U)

#define DCM_DSP_PERIODIC_RATEMODE_NUM              ((uint8)3U)
#define DCM_DSP_PERIODIC_READDATA_PDIDSIZE         ((uint8)1U)

#define DCM_DSP_PERIODIC_PDID_HIGHBITE             ((uint16)0xF200U)

#define DCM_DSP_PERIODIC_OK                        ((uint8)0U)
#define DCM_DSP_PERIODIC_PENDING                   ((uint8)1U)
#define DCM_DSP_PERIODIC_STOP                      ((uint8)2U)
#define DCM_DSP_PERIODIC_NOTOK                     ((uint8)3U)

#define DCM_DSP_PERIODIC_START_POS                 ((uint8)0U)
#define DCM_DSP_PERIODIC_START_CNT                 ((uint8)1U)
#define DCM_DSP_PERIODIC_CONNECTIONID_LISTNUM      ((uint8)30U)
#define DCM_DSP_PERIODIC_SID2A_SID                 ((uint8)0x2AU)

#define DCM_DSP_PERIODIC_INVALID_DOWNCNT           ((uint32)0xFFFFFFFFU)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct                                      /* Send queue info      */
{
    uint8   u1InPos;                                /* Write position       */
    uint8   u1OutPos;                               /* Read(Send) position  */
}Dcm_Dsp_Periodic_QueueInfoType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

static FUNC( void, DCM_CODE ) Dcm_Dsp_PeriodicMng_GetConnectionIdList
(
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) ptConnectionIdList,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)  ptListNum
);
static FUNC( void, DCM_CODE ) Dcm_Dsp_PeriodicMng_SetConnectionIdList
(
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) ptConnectionIdList,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)  ptListNum,
    const uint16                            u2ConnectionId
);
static FUNC( void, DCM_CODE ) Dcm_Dsp_PeriodicMng_SetComActive
(
    const boolean bActive,
    const uint8   u1ListNum,
    P2CONST( uint16, AUTOMATIC, DCM_APPL_DATA )     ptConnectionIdList
);
static FUNC( void, DCM_CODE ) Dcm_Dsp_PeriodicMng_DeletePDIDTbl
(
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)  ptUpdPDIDNum,
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) ptConnectionIdList,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)  ptListNum
);
static FUNC( void, DCM_CODE ) Dcm_Dsp_PeriodicMng_InitMsgCntxt
( void );
static FUNC( void, DCM_CODE ) Dcm_Dsp_PeriodicMng_SendMain
( void );
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_PeriodicMng_SendResult
( void );
static FUNC( void, DCM_CODE ) Dcm_Dsp_PeriodicMng_SendStop
( void );
static FUNC( void, DCM_CODE ) Dcm_Dsp_PeriodicMng_SendPDIDStatusUpdate
( void );
static FUNC( void, DCM_CODE ) Dcm_Dsp_PeriodicMng_SendQueueRebuild
( void );
static FUNC( void, DCM_CODE ) Dcm_Dsp_PeriodicMng_DeleteSendQueue
(
    const uint8 u1QueNum,
    const uint8 u1DelTargetPdid
);
static FUNC( void, DCM_CODE ) Dcm_Dsp_PeriodicMng_SendDownCount
( void );
static FUNC( void, DCM_CODE ) Dcm_Dsp_PeriodicMng_SendRequest
( void );
static FUNC( void, DCM_CODE ) Dcm_Dsp_PeriodicMng_SendReqMain
( 
    const uint8 u1QueNum 
);
static FUNC( void, DCM_CODE ) Dcm_Dsp_PeriodicMng_QueueNumChk
( 
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptQueNum
);
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_PeriodicMng_SetSendQueue
( 
    const uint8     u1PdidCnt
);
static FUNC( uint8, DCM_CODE ) Dcm_Dsp_PeriodicMng_ReadDidData
(
    P2VAR( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA )    ptMsgContext,
    const Dcm_OpStatusType                                   u1OpStatus,
    const uint8                                              u1Pdid
);
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_PeriodicMng_ReadPeriodicDid
(
    P2VAR( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA )    ptMsgContext,
    const Dcm_OpStatusType                                   u1OpStatus,
    const uint8                                              u1Pdid
);
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_PeriodicMng_CallReadDynDidFnc
(
    const uint16 u2DidIndex,
    const Dcm_OpStatusType u1OpStatus,
    const uint32 u4DataBufferLength,
    P2VAR( uint8,  AUTOMATIC, DCM_APPL_DATA ) ptData,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) ptDataLength
);

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>
VAR( Dcm_Dsp_Periodic_PdidInfoType, DCM_VAR_NO_INIT )    Dcm_Dsp_Periodic_stPdidInfoTbl[ DCM_DSP_PERIODIC_PDIDINFO_TBL ];
VAR( uint8, DCM_VAR_NO_INIT )    Dcm_Dsp_Periodic_u1DidInfo_RegNum;

static VAR( Dcm_MsgContextType, DCM_VAR_NO_INIT) Dcm_Dsp_Periodic_stMsgContext;  /* Transmit and receive management area */
static VAR( Dcm_Dsp_Periodic_QueueInfoType, DCM_VAR_NO_INIT ) Dcm_Dsp_Periodic_stQueueInfo;
static VAR( uint32,  DCM_VAR_NO_INIT )    Dcm_Dsp_Periodic_u4PeriodicTMCnt;
static VAR( uint32,  DCM_VAR_NO_INIT )    Dcm_Dsp_Periodic_u4PendingCnt;
static VAR( uint16,  DCM_VAR_NO_INIT )    Dcm_Dsp_Periodic_u2ConnectionIdMirror[ DCM_DSP_PERIODIC_PDIDINFO_TBL ];
static VAR( uint8,   DCM_VAR_NO_INIT )    Dcm_Dsp_Periodic_u1RegNumMirror;
static VAR( uint8,   DCM_VAR_NO_INIT )    Dcm_Dsp_Periodic_u1TransferMode;
static VAR( uint8,   DCM_VAR_NO_INIT )    Dcm_Dsp_Periodic_u1PendingPdid;
static VAR( boolean, DCM_VAR_NO_INIT )    Dcm_Dsp_Periodic_bSendResultChkFlag;
static VAR( boolean, DCM_VAR_NO_INIT )    Dcm_Dsp_Periodic_bQueueMaxFlag;

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
/* Function Name | Dcm_Dsp_PeriodicMng_Init                                 */
/* Description   | Periodic Transmission Initialization                     */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_PeriodicMng_Init
( void )
{
    uint8    u1_Cnt;
    uint8    u1_PDIDNum;

    Dcm_Dsp_Periodic_u4PeriodicTMCnt       = DCM_DSP_PERIODIC_TMCOUNTER_INITIAL;
    Dcm_Dsp_Periodic_u1TransferMode        = DCM_DSP_PERIODICTRANSFER_OFF;
    Dcm_Dsp_Periodic_u1DidInfo_RegNum      = (uint8)0U;
    Dcm_Dsp_Periodic_stQueueInfo.u1OutPos  = (uint8)0U;
    Dcm_Dsp_Periodic_stQueueInfo.u1InPos   = (uint8)0U;
    Dcm_Dsp_Periodic_u1PendingPdid         = (uint8)0U;
    Dcm_Dsp_Periodic_u4PendingCnt          = (uint32)0U;
    Dcm_Dsp_Periodic_bSendResultChkFlag    = (boolean)FALSE;
    Dcm_Dsp_Periodic_bQueueMaxFlag         = (boolean)FALSE;
    Dcm_Dsp_Periodic_u1RegNumMirror        = Dcm_Dsp_Periodic_u1DidInfo_RegNum;

    u1_PDIDNum = Dcm_Dsp_Periodic_u1PdidInfoTbl;
    for( u1_Cnt = 0U; u1_Cnt < u1_PDIDNum; u1_Cnt++ )
    {
        /* PDID information table clear */
        Dcm_Dsp_Periodic_stPdidInfoTbl[u1_Cnt].u4DownCounter  = (uint32)0U;
        Dcm_Dsp_Periodic_stPdidInfoTbl[u1_Cnt].u2ConnectionID = (uint16)0U;
        Dcm_Dsp_Periodic_stPdidInfoTbl[u1_Cnt].u1Pdid         = (uint8)0U;
        Dcm_Dsp_Periodic_stPdidInfoTbl[u1_Cnt].u1ReqType      = (uint8)0U;
        Dcm_Dsp_Periodic_stPdidInfoTbl[u1_Cnt].u1Rate         = (uint8)0U;
        Dcm_Dsp_Periodic_stPdidInfoTbl[u1_Cnt].u1Status       = DCM_DSP_PERIODIC_INIT;
        Dcm_Dsp_Periodic_stPdidInfoTbl[u1_Cnt].bQueueflg      = (boolean)FALSE;
        Dcm_Dsp_Periodic_u2ConnectionIdMirror[u1_Cnt]         = Dcm_Dsp_Periodic_stPdidInfoTbl[u1_Cnt].u2ConnectionID;
        /* Send Queue clear */
        Dcm_Dsp_Periodic_u1SendQueue[u1_Cnt] = (uint8)0U;
    }

    Dcm_Dsp_PeriodicMng_InitMsgCntxt();
    return;
}



/****************************************************************************/
/* Function Name | Dcm_Dsp_PeriodicMng_Main                                 */
/* Description   | Periodic Transmission Execution Cycle Judgment           */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_PeriodicMng_Main
( void )
{
    uint32   u4_TransmissionCount;
    
    if( Dcm_Dsp_Periodic_u1DidInfo_RegNum != Dcm_Dsp_Periodic_u1RegNumMirror )
    {
        Dcm_Dsp_PeriodicMng_SendStop();
    }
    
    if( Dcm_Dsp_Periodic_u1TransferMode == DCM_DSP_PERIODICTRANSFER_ON )
    {
        u4_TransmissionCount = Dcm_Dsp_Periodic_u4TransmissionCount;
        Dcm_Dsp_Periodic_u4PeriodicTMCnt++; /* no wrap around */
        if( Dcm_Dsp_Periodic_u4PeriodicTMCnt >= u4_TransmissionCount )
        {
            Dcm_Dsp_Periodic_u4PeriodicTMCnt = DCM_DSP_PERIODIC_TMCOUNTER_INITIAL;
            Dcm_Dsp_PeriodicMng_SendMain();
        }
    }
    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_PeriodicMng_PeriodicStatusCheck                  */
/* Description   | Check the execution status of periodic transmission      */
/* Preconditions | None                                                     */
/* Parameters    | [IN/OUT] ptActive : active Status                        */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_PeriodicMng_PeriodicStatusCheck
(
    P2VAR( Dcm_ActiveStateType, AUTOMATIC, DCM_APPL_DATA ) ptActive
)
{
    if( Dcm_Dsp_Periodic_u1TransferMode == DCM_DSP_PERIODICTRANSFER_ON )
    {
        if( Dcm_Dsp_Periodic_u1DidInfo_RegNum != (uint8)0U )
        {
            *ptActive |= DCM_EXE_PERIODIC;
        }
    }
    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_PeriodicMng_SetActiveResponse                    */
/* Description   | Set Communication Bus for periodic transmission          */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1ActiveStatus : each service Active Status         */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_PeriodicMng_SetActiveResponse
(
    const Dcm_ActiveStateType u1ActiveStatus
)
{
    uint16    u2_ConnectionIdList[DCM_DSP_PERIODIC_CONNECTIONID_LISTNUM] = {0};
    uint8     u1_ListNum;
    
    u1_ListNum = (uint8)0U;
    
    if( (u1ActiveStatus & DCM_EXE_PERIODIC) == DCM_EXE_PERIODIC )
    {
        /* Get ConnectionID from PDID table */
        Dcm_Dsp_PeriodicMng_GetConnectionIdList( &u2_ConnectionIdList[DCM_DSP_PERIODIC_START_POS], &u1_ListNum);
    
        if( u1_ListNum > (uint8)0U )
        {
            Dcm_Dsp_PeriodicMng_SetComActive( (boolean)TRUE, u1_ListNum, &u2_ConnectionIdList[DCM_DSP_PERIODIC_START_POS] );
        }
        else
        {
            /* Inactive the communication bus for all clients */
            Dcm_Dsl_SetComActive( DCM_DSL_ALL_TARGETS, (boolean)FALSE );
        }
    }
    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_PeriodicMng_UpdatePDIDTbl                        */
/* Description   | Check the execution status of periodic transmission      */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1PdidNumNew : updated PDID information table num   */
/*               | [IN] u1ReqTMmode  : Transmission mode                    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_PeriodicMng_UpdatePDIDTbl
(
    const uint8 u1PdidNumNew,
    const uint8 u1ReqTMmode
)
{
    uint32        u4_DownCounter;
    uint16        u2_ReqPDIDNum;
    uint16        u2_CntReq;
    uint16        u2_ConnectionIdList[DCM_DSP_PERIODIC_CONNECTIONID_LISTNUM] = {0};
    uint8         u1_Status;
    uint8         u1_PDIDNum;
    uint8         u1_UpdPDIDNum;
    uint8         u1_Cnt;
    uint8         u1_TransferModeOld;
    uint8         u1_ListNum;
    boolean       b_DelFlg;

    u1_ListNum = (uint8)0U;
    if( u1PdidNumNew == (uint8)0U )
    {
        Dcm_Dsp_PeriodicMng_GetConnectionIdList( &u2_ConnectionIdList[DCM_DSP_PERIODIC_START_POS], &u1_ListNum );
        u1_UpdPDIDNum = (uint8)0U;
    }
    else
    {
        u2_ReqPDIDNum = Dcm_Dsp_SID2A_u2PDidUpdInfoNum;
        u1_PDIDNum    = Dcm_Dsp_Periodic_u1DidInfo_RegNum;
        u1_UpdPDIDNum = u1_PDIDNum;
        if( u1ReqTMmode == DCM_DSP_SID2A_CONDITION_STOP )
        {
            b_DelFlg = (boolean)FALSE;
            for( u1_Cnt = (uint8)0U; u1_Cnt < u1_PDIDNum; u1_Cnt++ )
            {
                for( u2_CntReq = (uint16)0U; u2_CntReq < u2_ReqPDIDNum; u2_CntReq++ )
                {
                    if( Dcm_Dsp_Periodic_stPdidInfoTbl[u1_Cnt].u1Pdid == Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_CntReq].u1Pdid )
                    {
                        b_DelFlg = (boolean)TRUE;
                        Dcm_Dsp_Periodic_stPdidInfoTbl[u1_Cnt].u1Status = DCM_DSP_PERIODIC_INIT;
                    }
                }
            }
            if( b_DelFlg == (boolean)TRUE)
            {
                Dcm_Dsp_PeriodicMng_DeletePDIDTbl( &u1_UpdPDIDNum, &u2_ConnectionIdList[DCM_DSP_PERIODIC_START_POS], &u1_ListNum );
            }
        }
        else
        {
            if( u1_PDIDNum == (uint8)0U )
            {
                for( u2_CntReq = (uint16)0U; u2_CntReq < u2_ReqPDIDNum; u2_CntReq++ )
                {
                    if( Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_CntReq].u1Condition != DCM_DSP_SID2A_CONDITION_STOP )
                    {
                        Dcm_Dsp_Periodic_stPdidInfoTbl[u1_UpdPDIDNum].u4DownCounter  = (uint32)0U;
                        Dcm_Dsp_Periodic_stPdidInfoTbl[u1_UpdPDIDNum].u2ConnectionID = Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_CntReq].u2ConnectionID;
                        Dcm_Dsp_Periodic_stPdidInfoTbl[u1_UpdPDIDNum].u1Pdid         = Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_CntReq].u1Pdid;
                        Dcm_Dsp_Periodic_stPdidInfoTbl[u1_UpdPDIDNum].u1ReqType      = Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_CntReq].u1ReqType;
                        Dcm_Dsp_Periodic_stPdidInfoTbl[u1_UpdPDIDNum].u1Rate         = Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_CntReq].u1Condition;
                        Dcm_Dsp_Periodic_stPdidInfoTbl[u1_UpdPDIDNum].u1Status       = DCM_DSP_PERIODIC_DOWNCOUNT;
                        Dcm_Dsp_Periodic_stPdidInfoTbl[u1_UpdPDIDNum].bQueueflg      = (boolean)FALSE;
                        Dcm_Dsp_Periodic_u2ConnectionIdMirror[u1_UpdPDIDNum]         = Dcm_Dsp_Periodic_stPdidInfoTbl[u1_UpdPDIDNum].u2ConnectionID;
                        u1_UpdPDIDNum = (uint8)(u1_UpdPDIDNum + (uint8)1U); /* Already checked the limit in request processing */
                    }
                }
            }
            else
            {
                u4_DownCounter = (uint32)0U;
                u1_Status      = DCM_DSP_PERIODIC_DOWNCOUNT;
                for( u1_Cnt = u1_PDIDNum; u1_Cnt > (uint8)0U; u1_Cnt-- )
                {
                    if( Dcm_Dsp_Periodic_stPdidInfoTbl[u1_Cnt - (uint8)1U].u1Rate == u1ReqTMmode )
                    {
                        if( Dcm_Dsp_Periodic_stPdidInfoTbl[u1_Cnt - (uint8)1U].u1Status == DCM_DSP_PERIODIC_DOWNCOUNT )
                        {
                            u4_DownCounter = Dcm_Dsp_Periodic_stPdidInfoTbl[u1_Cnt - (uint8)1U].u4DownCounter;
                            u1_Status      = DCM_DSP_PERIODIC_DOWNCOUNT;
                        }
                        else
                        {
                            u4_DownCounter = Dcm_Dsp_stTransMissionModeInfoTbl[u1ReqTMmode - (uint8)1U].u4DownCounter;
                            u1_Status      = DCM_DSP_PERIODIC_REGISTWAIT;
                        }
                        break;
                    }
                }
                b_DelFlg = (boolean)FALSE;
                for( u2_CntReq = (uint16)0U; u2_CntReq < u2_ReqPDIDNum; u2_CntReq++ )
                {
                    if( Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_CntReq].u1Condition == DCM_DSP_SID2A_CONDITION_STOP )
                    {
                        for( u1_Cnt = (uint8)0U; u1_Cnt < u1_PDIDNum; u1_Cnt++ )
                        {
                            if( Dcm_Dsp_Periodic_stPdidInfoTbl[u1_Cnt].u1Pdid == Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_CntReq].u1Pdid )
                            {
                                if(b_DelFlg == (boolean)FALSE)
                                {
                                    b_DelFlg = (boolean)TRUE;
                                }
                                Dcm_Dsp_Periodic_stPdidInfoTbl[u1_Cnt].u1Status = DCM_DSP_PERIODIC_INIT;
                            }
                        }
                    }
                }
                if( b_DelFlg == (boolean)TRUE )
                {
                    Dcm_Dsp_PeriodicMng_DeletePDIDTbl( &u1_UpdPDIDNum, &u2_ConnectionIdList[DCM_DSP_PERIODIC_START_POS], &u1_ListNum );
                }
                for( u2_CntReq = (uint16)0U; u2_CntReq < u2_ReqPDIDNum; u2_CntReq++ )
                {
                    if( Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_CntReq].u1Condition != DCM_DSP_SID2A_CONDITION_STOP )
                    {
                        Dcm_Dsp_Periodic_stPdidInfoTbl[u1_UpdPDIDNum].u4DownCounter  = u4_DownCounter;
                        Dcm_Dsp_Periodic_stPdidInfoTbl[u1_UpdPDIDNum].u2ConnectionID = Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_CntReq].u2ConnectionID;
                        Dcm_Dsp_Periodic_stPdidInfoTbl[u1_UpdPDIDNum].u1Pdid         = Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_CntReq].u1Pdid;
                        Dcm_Dsp_Periodic_stPdidInfoTbl[u1_UpdPDIDNum].u1ReqType      = Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_CntReq].u1ReqType;
                        Dcm_Dsp_Periodic_stPdidInfoTbl[u1_UpdPDIDNum].u1Rate         = Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[u2_CntReq].u1Condition;
                        Dcm_Dsp_Periodic_stPdidInfoTbl[u1_UpdPDIDNum].u1Status       = u1_Status;
                        Dcm_Dsp_Periodic_stPdidInfoTbl[u1_UpdPDIDNum].bQueueflg      = (boolean)FALSE;
                        Dcm_Dsp_Periodic_u2ConnectionIdMirror[u1_UpdPDIDNum]         = Dcm_Dsp_Periodic_stPdidInfoTbl[u1_UpdPDIDNum].u2ConnectionID;
                        u1_UpdPDIDNum = (uint8)(u1_UpdPDIDNum + (uint8)1U); /* Already checked the limit in request processing */
                    }
                }
            }
        }
    }
    Dcm_Dsp_Periodic_u1DidInfo_RegNum = u1_UpdPDIDNum;
    Dcm_Dsp_Periodic_u1RegNumMirror = Dcm_Dsp_Periodic_u1DidInfo_RegNum;
    Dcm_Dsp_PeriodicMng_SetComActive( (boolean)FALSE, u1_ListNum, &u2_ConnectionIdList[DCM_DSP_PERIODIC_START_POS] );

    u1_TransferModeOld = Dcm_Dsp_Periodic_u1TransferMode;
    if( u1_UpdPDIDNum > (uint8)0U )
    {
        if( u1_TransferModeOld != DCM_DSP_PERIODICTRANSFER_ON )
        {
            Dcm_Dsp_Periodic_u1TransferMode = DCM_DSP_PERIODICTRANSFER_ON;
            Dcm_Dsp_Periodic_u4PeriodicTMCnt = DCM_DSP_PERIODIC_TMCOUNTER_INITIAL;
            Dcm_Dsp_Periodic_stQueueInfo.u1OutPos = (uint8)0U;
            Dcm_Dsp_Periodic_stQueueInfo.u1InPos  = (uint8)0U;
            Dcm_Dsp_Periodic_u4PendingCnt         = (uint32)0U;
            Dcm_Dsp_Periodic_bSendResultChkFlag   = (boolean)FALSE;
            Dcm_Dsp_Periodic_bQueueMaxFlag        = (boolean)FALSE;
        }
    }
    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_PeriodicMng_NotifySecCtrl                        */
/* Description   | Notify of security level change.                         */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1SecLevelNew     : Security level after change     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_PeriodicMng_NotifySecCtrl /* MISRA DEVIATION */
(
    const Dcm_SecLevelType u1SecLevelNew
)
{
    uint16                          u2_Did;
    uint16                          u2_Index;
    uint16                          u2_ConnectionIdList[DCM_DSP_PERIODIC_CONNECTIONID_LISTNUM] = {0};
    uint8                           u1_KindOfDid;
    uint8                           u1_PDIDNum;
    uint8                           u1_UpdPDIDNum;
    uint8                           u1_Cnt;
    uint8                           u1_ListNum;
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_RetChkSec;
    boolean                         b_DelFlg;

    /* At least one PDID in operation */
    if( Dcm_Dsp_Periodic_u1DidInfo_RegNum != (uint8)0 )
    {
        b_DelFlg      = (boolean)FALSE;
        u1_KindOfDid  = (uint8)0U;
        u2_Index      = (uint16)0U;
        u1_PDIDNum    = Dcm_Dsp_Periodic_u1DidInfo_RegNum;
        u1_UpdPDIDNum = u1_PDIDNum;
        u1_ListNum    = (uint8)0U;
        /* Check and Update PDID information table */
        for( u1_Cnt = (uint8)0U; u1_Cnt < u1_PDIDNum; u1_Cnt++ )
        {
            u2_Did = (uint16)( DCM_DSP_PERIODIC_PDID_HIGHBITE | (uint16)Dcm_Dsp_Periodic_stPdidInfoTbl[u1_Cnt].u1Pdid );
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
                    Dcm_Dsp_Periodic_stPdidInfoTbl[u1_Cnt].u1Status = DCM_DSP_PERIODIC_INIT;
                }
            }
            else
            {
                b_DelFlg = (boolean)TRUE;
                Dcm_Dsp_Periodic_stPdidInfoTbl[u1_Cnt].u1Status = DCM_DSP_PERIODIC_INIT;
            }
        }
        if( b_DelFlg == (boolean)TRUE )
        {
            Dcm_Dsp_PeriodicMng_DeletePDIDTbl( &u1_UpdPDIDNum, &u2_ConnectionIdList[DCM_DSP_PERIODIC_START_POS], &u1_ListNum );
        }
        Dcm_Dsp_Periodic_u1DidInfo_RegNum = u1_UpdPDIDNum;
        Dcm_Dsp_Periodic_u1RegNumMirror = Dcm_Dsp_Periodic_u1DidInfo_RegNum;

        /* Inactive communication bus  */
        Dcm_Dsp_PeriodicMng_SetComActive( (boolean)FALSE, u1_ListNum, &u2_ConnectionIdList[DCM_DSP_PERIODIC_START_POS] );
    }
    
    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_PeriodicMng_NotifySesCtrl                        */
/* Description   | Notify of session state change.                          */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1SesCtrlTypeNew     : Session after change         */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_PeriodicMng_NotifySesCtrl /* MISRA DEVIATION */
(
    const Dcm_SesCtrlType u1SesCtrlTypeNew
)
{
    uint16                          u2_Did;
    uint16                          u2_Index;
    uint16                          u2_ConnectionIdList[DCM_DSP_PERIODIC_CONNECTIONID_LISTNUM] = {0};
    PduIdType                       u2_RxPduId;
    uint8                           u1_KindOfDid;
    uint8                           u1_PDIDNum;
    uint8                           u1_UpdPDIDNum;
    uint8                           u1_Cnt;
    uint8                           u1_TMUpdType;
    uint8                           u1_ListNum;
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_RetChkSec;
    Std_ReturnType                  u1_RetSupported;
    boolean                         b_DelFlg;
    boolean                         b_ResetFlag;

    /* At least one PDID in operation */
    if( Dcm_Dsp_Periodic_u1DidInfo_RegNum != (uint8)0 )
    {
        u1_TMUpdType = Dcm_Dsp_Periodic_u1TransmissonUpdType;
        u1_ListNum    = (uint8)0U;
        if( u1_TMUpdType == DCM_DSP_PERIODIC_TRANSMISSIONUPD_TYPE1 )
        {
            b_DelFlg      = (boolean)FALSE;
            u1_KindOfDid  = (uint8)0U;
            u2_Index      = (uint16)0U;
            u1_PDIDNum    = Dcm_Dsp_Periodic_u1DidInfo_RegNum;
            u1_UpdPDIDNum = u1_PDIDNum;

            /* Check and Update PDID information table */
            for( u1_Cnt = (uint8)0U; u1_Cnt < u1_PDIDNum; u1_Cnt++ )
            {
                u2_Did = (uint16)( DCM_DSP_PERIODIC_PDID_HIGHBITE | (uint16)Dcm_Dsp_Periodic_stPdidInfoTbl[u1_Cnt].u1Pdid );
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
                        Dcm_Dsp_Periodic_stPdidInfoTbl[u1_Cnt].u1Status = DCM_DSP_PERIODIC_INIT;
                    }
                }
                else
                {
                    b_DelFlg = (boolean)TRUE;
                    Dcm_Dsp_Periodic_stPdidInfoTbl[u1_Cnt].u1Status = DCM_DSP_PERIODIC_INIT;
                }
            }
            if( b_DelFlg == (boolean)TRUE )
            {
                Dcm_Dsp_PeriodicMng_DeletePDIDTbl( &u1_UpdPDIDNum, &u2_ConnectionIdList[DCM_DSP_PERIODIC_START_POS], &u1_ListNum );
            }
            Dcm_Dsp_Periodic_u1DidInfo_RegNum = u1_UpdPDIDNum;
        }
        else if( u1_TMUpdType == DCM_DSP_PERIODIC_TRANSMISSIONUPD_TYPE3 )
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
                u1_RetSupported = Dcm_Dsd_ChkServiceSupported( DCM_DSP_PERIODIC_SID2A_SID, u2_RxPduId ,u1SesCtrlTypeNew );
                if( u1_RetSupported != (Std_ReturnType)E_OK )
                {
                    b_ResetFlag = (boolean)TRUE;
                }
            }
            
            if( b_ResetFlag == (boolean)TRUE )
            {
                /* Get ConnectionID from PDID table */
                Dcm_Dsp_PeriodicMng_GetConnectionIdList( &u2_ConnectionIdList[DCM_DSP_PERIODIC_START_POS], &u1_ListNum);
                /* Clear PDID information table */
                Dcm_Dsp_Periodic_u1DidInfo_RegNum = (uint8)0U;
            }
            else
            {
                b_DelFlg      = (boolean)FALSE;
                u1_KindOfDid  = (uint8)0U;
                u2_Index      = (uint16)0U;
                u1_PDIDNum    = Dcm_Dsp_Periodic_u1DidInfo_RegNum;
                u1_UpdPDIDNum = u1_PDIDNum;
                
                /* Check and Update PDID information table */
                for( u1_Cnt = (uint8)0U; u1_Cnt < u1_PDIDNum; u1_Cnt++ )
                {
                    u2_Did = (uint16)( DCM_DSP_PERIODIC_PDID_HIGHBITE | (uint16)Dcm_Dsp_Periodic_stPdidInfoTbl[u1_Cnt].u1Pdid );
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
                            Dcm_Dsp_Periodic_stPdidInfoTbl[u1_Cnt].u1Status = DCM_DSP_PERIODIC_INIT;
                        }
                    }
                    else
                    {
                        b_DelFlg = (boolean)TRUE;
                        Dcm_Dsp_Periodic_stPdidInfoTbl[u1_Cnt].u1Status = DCM_DSP_PERIODIC_INIT;
                    }
                }
                if( b_DelFlg == (boolean)TRUE )
                {
                    Dcm_Dsp_PeriodicMng_DeletePDIDTbl( &u1_UpdPDIDNum, &u2_ConnectionIdList[DCM_DSP_PERIODIC_START_POS], &u1_ListNum );
                }
                Dcm_Dsp_Periodic_u1DidInfo_RegNum = u1_UpdPDIDNum;
            }
        }
        else
        {
            /* Get ConnectionID from PDID table */
            Dcm_Dsp_PeriodicMng_GetConnectionIdList( &u2_ConnectionIdList[DCM_DSP_PERIODIC_START_POS], &u1_ListNum );
            /* Clear PDID information table */
            Dcm_Dsp_Periodic_u1DidInfo_RegNum = (uint8)0U;
        }
        Dcm_Dsp_Periodic_u1RegNumMirror = Dcm_Dsp_Periodic_u1DidInfo_RegNum;
        /* Inactive communication bus  */
        Dcm_Dsp_PeriodicMng_SetComActive( (boolean)FALSE, u1_ListNum, &u2_ConnectionIdList[DCM_DSP_PERIODIC_START_POS] );
    }

    return;
}


#if( DCM_PERIODIC_DDDID_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_PeriodicMng_UpdPDidInfDDDidClr                   */
/* Description   | Update PDID information table to clear on DDDid          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_PeriodicMng_UpdPDidInfDDDidClr
( void )
{
    uint16                          u2_Did;
    uint16                          u2_Index;
    uint16                          u2_ConnectionIdList[DCM_DSP_PERIODIC_CONNECTIONID_LISTNUM] = {0};
    uint16                          u2_DynamicIndex;
    uint8                           u1_KindOfDid;
    uint8                           u1_NumOfSourceDid;
    uint8                           u1_PDIDNum;
    uint8                           u1_UpdPDIDNum;
    uint8                           u1_Cnt;
    uint8                           u1_ListNum;
    Std_ReturnType                  u1_RetVal;
    boolean                         b_DeleteFlg;

    u1_PDIDNum        = Dcm_Dsp_Periodic_u1DidInfo_RegNum;
    u1_UpdPDIDNum     = u1_PDIDNum;
    u1_KindOfDid      = (uint8)0U;
    u2_Index          = (uint16)0U;
    u1_NumOfSourceDid = (uint8)0U;
    u2_DynamicIndex   = (uint16)0U;
    u1_ListNum        = (uint8)0U;
    b_DeleteFlg = (boolean)FALSE;
    
    for( u1_Cnt = (uint8)0U; u1_Cnt < u1_PDIDNum; u1_Cnt++ )
    {
        u2_Did = (uint16)( DCM_DSP_PERIODIC_PDID_HIGHBITE | (uint16)Dcm_Dsp_Periodic_stPdidInfoTbl[u1_Cnt].u1Pdid );
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
                        Dcm_Dsp_Periodic_stPdidInfoTbl[u1_Cnt].u1Status = DCM_DSP_PERIODIC_INIT;
                    }
                }
            }
        }
    }
    if( b_DeleteFlg == (boolean)TRUE )
    {
        Dcm_Dsp_PeriodicMng_DeletePDIDTbl( &u1_UpdPDIDNum, &u2_ConnectionIdList[DCM_DSP_PERIODIC_START_POS], &u1_ListNum );
    }
    Dcm_Dsp_Periodic_u1DidInfo_RegNum = u1_UpdPDIDNum;
    Dcm_Dsp_Periodic_u1RegNumMirror = Dcm_Dsp_Periodic_u1DidInfo_RegNum;

    /* Inactive communication bus  */
    Dcm_Dsp_PeriodicMng_SetComActive( (boolean)FALSE, u1_ListNum, &u2_ConnectionIdList[DCM_DSP_PERIODIC_START_POS] );

    return;
}
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON */


#if( DCM_PERIODIC_DDDID_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_PeriodicMng_UpdPDidInfSpecDDDidClr               */
/* Description   | Update PDID information table to clear on specified      */
/*               | DDDid                                                    */
/* Preconditions | None                                                     */
/* Parameters    | [in] u1ClrDDDid : Cleared DDDID                          */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_PeriodicMng_UpdPDidInfSpecDDDidClr
(
    const uint8 u1ClrDDDid
)
{
    uint16                          u2_ConnectionIdList[DCM_DSP_PERIODIC_CONNECTIONID_LISTNUM] = {0};
    uint16                          u2_PdidConnectionId;
    uint8                           u1_PDIDNum;
    uint8                           u1_Cnt;
    uint8                           u1_CntUpd;
    uint8                           u1_ListNum;

    u1_PDIDNum    = Dcm_Dsp_Periodic_u1DidInfo_RegNum;
    u1_ListNum    = (uint8)0U;

    for( u1_Cnt = (uint8)0U; u1_Cnt < u1_PDIDNum; u1_Cnt++ )
    {
        if( Dcm_Dsp_Periodic_stPdidInfoTbl[u1_Cnt].u1Pdid == u1ClrDDDid )
        {
            /* Register the Connection ID to be deleted in the list */
            u2_PdidConnectionId = Dcm_Dsp_Periodic_stPdidInfoTbl[u1_Cnt].u2ConnectionID;
            Dcm_Dsp_PeriodicMng_SetConnectionIdList( &u2_ConnectionIdList[DCM_DSP_PERIODIC_START_POS], &u1_ListNum, u2_PdidConnectionId );
            for( u1_CntUpd = u1_Cnt; u1_CntUpd < ( u1_PDIDNum - (uint8)1U ); u1_CntUpd++ )
            {
                Dcm_Dsp_Periodic_stPdidInfoTbl[u1_CntUpd].u4DownCounter  = Dcm_Dsp_Periodic_stPdidInfoTbl[u1_CntUpd + (uint8)1U].u4DownCounter;
                Dcm_Dsp_Periodic_stPdidInfoTbl[u1_CntUpd].u2ConnectionID = Dcm_Dsp_Periodic_stPdidInfoTbl[u1_CntUpd + (uint8)1U].u2ConnectionID;
                Dcm_Dsp_Periodic_stPdidInfoTbl[u1_CntUpd].u1Pdid         = Dcm_Dsp_Periodic_stPdidInfoTbl[u1_CntUpd + (uint8)1U].u1Pdid;
                Dcm_Dsp_Periodic_stPdidInfoTbl[u1_CntUpd].u1ReqType      = Dcm_Dsp_Periodic_stPdidInfoTbl[u1_CntUpd + (uint8)1U].u1ReqType;
                Dcm_Dsp_Periodic_stPdidInfoTbl[u1_CntUpd].u1Rate         = Dcm_Dsp_Periodic_stPdidInfoTbl[u1_CntUpd + (uint8)1U].u1Rate;
                Dcm_Dsp_Periodic_stPdidInfoTbl[u1_CntUpd].u1Status       = Dcm_Dsp_Periodic_stPdidInfoTbl[u1_CntUpd + (uint8)1U].u1Status;
                Dcm_Dsp_Periodic_stPdidInfoTbl[u1_CntUpd].bQueueflg      = Dcm_Dsp_Periodic_stPdidInfoTbl[u1_CntUpd + (uint8)1U].bQueueflg;
                Dcm_Dsp_Periodic_u2ConnectionIdMirror[u1_CntUpd]         = Dcm_Dsp_Periodic_stPdidInfoTbl[u1_CntUpd].u2ConnectionID;
            }
            Dcm_Dsp_Periodic_u1DidInfo_RegNum = (uint8)(Dcm_Dsp_Periodic_u1DidInfo_RegNum - (uint8)1U);
            Dcm_Dsp_Periodic_u1RegNumMirror = Dcm_Dsp_Periodic_u1DidInfo_RegNum;
            /* Inactive communication bus  */
            Dcm_Dsp_PeriodicMng_SetComActive( (boolean)FALSE, u1_ListNum, &u2_ConnectionIdList[DCM_DSP_PERIODIC_START_POS] );
            break;
        }
    }

    return;
}
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON */


/****************************************************************************/
/* Function Name | Dcm_Dsp_PeriodicMng_ChkDID                               */
/* Description   | Check DID                                                */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u2Did           : DDDID                             */
/*               | [OUT] ptKindOfDid    : Kind Of Did                       */
/*               | [OUT] ptDidIndex     : DID Index                         */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                                                     */
/*               | E_NOT_OK                                                 */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_PeriodicMng_ChkDID
(
    const uint16 u2Did,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptKindOfDid,
    P2VAR( uint16, AUTOMATIC, DCM_APPL_DATA ) ptDidIndex
)
{
    uint16                          u2_RangeIndex;
    uint16                          u2_DynamicIndex;
    uint8                           u1_CRWSupport;
    uint8                           u1_NumOfSourceDid;
    uint8                           u1_ChkReadSupport;
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_RetChkDynamicDid;
    Dcm_Main_ReturnCheckType        u1_RetDidRange;

    u1_RetVal                   = E_NOT_OK;
    u2_RangeIndex               = (uint16)0U;
    u1_CRWSupport               = (uint8)0U;
    u1_NumOfSourceDid           = (uint8)0U;
    u2_DynamicIndex             = (uint16)0U;

    *ptKindOfDid = DCM_DSP_DIDMNG_DID_DYNAMIC;
    *ptDidIndex  = (uint16)0U;

    u1_RetChkDynamicDid = Dcm_Dsp_DidMng_ChkDynamic( u2Did, &u1_NumOfSourceDid, &u2_DynamicIndex );
    if( u1_RetChkDynamicDid == (Std_ReturnType)E_OK )
    {
        *ptKindOfDid = DCM_DSP_DIDMNG_DID_DYNAMIC;
        *ptDidIndex  = u2_DynamicIndex;
        u1_RetVal = E_OK;
    }
    else
    {
        u1_RetDidRange = Dcm_Dsp_DidMng_ChkDid( u2Did,
                                                DCM_DSP_DIDMNG_DID_RANGE,
                                                &u2_RangeIndex,
                                                &u1_CRWSupport
                                                );

        if( u1_RetDidRange == DCM_MAIN_E_CHECK_OK )
        {
            u1_ChkReadSupport = u1_CRWSupport & DCM_DSP_DIDMNG_READ_ONLY;
            if( u1_ChkReadSupport == DCM_DSP_DIDMNG_READ_ONLY )
            {
                *ptKindOfDid = DCM_DSP_DIDMNG_DID_RANGE;
                *ptDidIndex  = u2_RangeIndex;
                u1_RetVal = E_OK;
            }
        }
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Dcm_Dsp_PeriodicMng_GetConnectionIdList                  */
/* Description   | Get ConnectionID List from PDID table                    */
/* Preconditions | None                                                     */
/* Parameters    | [OUT] ptConnectionIdList : ConnectionID List             */
/*               | [OUT] ptListNum          : ConnectionID List Num         */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_PeriodicMng_GetConnectionIdList
(
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) ptConnectionIdList,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)  ptListNum
)
{
    uint16      u2_PdidConnectionId;
    uint16      u2_ConnectionIdMirror;
    uint8       u1_PdidRegNum;
    uint8       u1_PdidCnt;
    uint8       u1_ListNum;
    uint8       u1_ListCnt;
    boolean     b_HitFlag;
    
    u1_PdidRegNum = Dcm_Dsp_Periodic_u1DidInfo_RegNum;
    u1_ListNum = (uint8)0U;

    for( u1_PdidCnt = (uint8)0U; u1_PdidCnt < u1_PdidRegNum; u1_PdidCnt++ )
    {
        u2_PdidConnectionId = Dcm_Dsp_Periodic_stPdidInfoTbl[u1_PdidCnt].u2ConnectionID;
        u2_ConnectionIdMirror = Dcm_Dsp_Periodic_u2ConnectionIdMirror[u1_PdidCnt];
        
        if( u2_PdidConnectionId == u2_ConnectionIdMirror )
        {
            if( u1_ListNum == (uint8)0U )
            {
                ptConnectionIdList[u1_ListNum] = u2_PdidConnectionId;
                u1_ListNum = DCM_DSP_PERIODIC_START_CNT;
            }
            else
            {
                b_HitFlag = (boolean)FALSE;
                for( u1_ListCnt = (uint8)0U; u1_ListCnt < u1_ListNum; u1_ListCnt++ )
                {
                    if( u2_PdidConnectionId == ptConnectionIdList[u1_ListCnt] )
                    {
                        b_HitFlag = (boolean)TRUE;
                        break;
                    }
                }
                if( b_HitFlag == (boolean)FALSE)
                {
                    ptConnectionIdList[u1_ListNum] = u2_PdidConnectionId;
                    u1_ListNum = (uint8)(u1_ListNum + (uint8)1U);
                }
            }
            if( u1_ListNum >= DCM_DSP_PERIODIC_CONNECTIONID_LISTNUM )
            {
                break;
            }
        }
    }
    *ptListNum = u1_ListNum;
    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_PeriodicMng_SetConnectionIdList                  */
/* Description   | Set Connection ID to list                                */
/* Preconditions | None                                                     */
/* Parameters    | [IN/OUT] ptConnectionIdList : ConnectionID List          */
/*               | [IN/OUT] ptListNum          : ConnectionID List Num      */
/*               | [IN]     u2ConnectionID     : ConnectionID               */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_PeriodicMng_SetConnectionIdList
(
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) ptConnectionIdList,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)  ptListNum,
    const uint16                            u2ConnectionId
)
{
    uint8       u1_ListNum;
    uint8       u1_ListCnt;
    boolean     b_HitFlag;

    u1_ListNum = *ptListNum;
    
    if( u1_ListNum < DCM_DSP_PERIODIC_CONNECTIONID_LISTNUM )
    {
        if ( u1_ListNum == (uint8)0U )
        {
            ptConnectionIdList[u1_ListNum] = u2ConnectionId;
            u1_ListNum = DCM_DSP_PERIODIC_START_CNT;
        }
        else
        {
            b_HitFlag = (boolean)FALSE;
            for( u1_ListCnt = (uint8)0U; u1_ListCnt < u1_ListNum; u1_ListCnt++ )
            {
                if( u2ConnectionId == ptConnectionIdList[u1_ListCnt] )
                {
                    b_HitFlag = (boolean)TRUE;
                    break;
                }
            }
            if( b_HitFlag == (boolean)FALSE)
            {
                ptConnectionIdList[u1_ListNum] = u2ConnectionId;
                u1_ListNum = (uint8)(u1_ListNum + (uint8)1U);
            }
        }
    }
    *ptListNum = u1_ListNum;
    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_PeriodicMng_SetComActive                         */
/* Description   | Activate or inactivate the communication bus             */
/* Preconditions | None                                                     */
/* Parameters    | [IN] bActive        : Request Set Active Status          */
/*               | [IN] u1ListNum      : ConnectionID List Num              */
/*               | [IN] ptConnectionIdList : ConnectionID List              */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_PeriodicMng_SetComActive
(
    const boolean bActive,
    const uint8   u1ListNum,
    P2CONST( uint16, AUTOMATIC, DCM_APPL_DATA )     ptConnectionIdList
)
{
    uint16             u2_PdidConnectionId;
    uint16             u2_ConnectionId;
    uint8              u1_PdidRegNum;
    uint8              u1_ListCnt;
    uint8              u1_PdidCnt;
    boolean            b_HitFlag;
    
    u1_PdidRegNum = Dcm_Dsp_Periodic_u1DidInfo_RegNum;

    if( bActive == (boolean)TRUE )
    {
        for( u1_ListCnt = (uint8)0U; u1_ListCnt < u1ListNum; u1_ListCnt++ )
        {
            u2_ConnectionId = ptConnectionIdList[u1_ListCnt];
            Dcm_Dsl_SetComActive( u2_ConnectionId, (boolean)TRUE );
        }
    }
    else
    {
        if( u1_PdidRegNum != (uint8)0U )
        {
            for( u1_ListCnt = (uint8)0U; u1_ListCnt < u1ListNum; u1_ListCnt++ )
            {
                b_HitFlag = (boolean)FALSE;
                u2_ConnectionId = ptConnectionIdList[u1_ListCnt];
                for( u1_PdidCnt = (uint8)0U; u1_PdidCnt < u1_PdidRegNum; u1_PdidCnt++ )
                {
                    u2_PdidConnectionId = Dcm_Dsp_Periodic_stPdidInfoTbl[u1_PdidCnt].u2ConnectionID;
                    if( u2_ConnectionId == u2_PdidConnectionId )
                    {
                        b_HitFlag = (boolean)TRUE;
                        break;
                    }
                }
                if( b_HitFlag == (boolean)FALSE)
                {
                    Dcm_Dsl_SetComActive( u2_ConnectionId, (boolean)FALSE );
                }
            }
        }
        else
        {
            for( u1_ListCnt = (uint8)0U; u1_ListCnt < u1ListNum; u1_ListCnt++ )
            {
                u2_ConnectionId = ptConnectionIdList[u1_ListCnt];
                Dcm_Dsl_SetComActive( u2_ConnectionId, (boolean)FALSE );
            }
            
        }
    }
    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_PeriodicMng_DeletePDIDTbl                        */
/* Description   | Delete the PDIDTbl that needs to be deleted              */
/* Preconditions | None                                                     */
/* Parameters    | [OUT] ptUpdPDIDNum : updated PDID table num              */
/*               | [OUT] ptConnectionIdList : ConnectionID List             */
/*               | [IN/OUT] ptListNum       : ConnectionID List Num         */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_PeriodicMng_DeletePDIDTbl
(
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptUpdPDIDNum,
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA)ptConnectionIdList,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptListNum
)
{
    uint16        u2_PdidConnectionId;
    uint8         u1_Cnt;
    uint8         u1_PDIDNum;
    uint8         u1_DelStatus;
    uint8         u1_ExistPDIDNum;
    
    u1_PDIDNum    = Dcm_Dsp_Periodic_u1DidInfo_RegNum;
    u1_ExistPDIDNum = (uint8)0U;
    
    for( u1_Cnt = (uint8)0U; u1_Cnt < u1_PDIDNum; u1_Cnt++ )
    {
        u1_DelStatus = Dcm_Dsp_Periodic_stPdidInfoTbl[u1_Cnt].u1Status;
        if( u1_DelStatus != DCM_DSP_PERIODIC_INIT)
        {
            if( u1_Cnt != u1_ExistPDIDNum)
            {
                Dcm_Dsp_Periodic_stPdidInfoTbl[u1_ExistPDIDNum].u4DownCounter  = Dcm_Dsp_Periodic_stPdidInfoTbl[u1_Cnt].u4DownCounter;
                Dcm_Dsp_Periodic_stPdidInfoTbl[u1_ExistPDIDNum].u2ConnectionID = Dcm_Dsp_Periodic_stPdidInfoTbl[u1_Cnt].u2ConnectionID;
                Dcm_Dsp_Periodic_stPdidInfoTbl[u1_ExistPDIDNum].u1Pdid         = Dcm_Dsp_Periodic_stPdidInfoTbl[u1_Cnt].u1Pdid;
                Dcm_Dsp_Periodic_stPdidInfoTbl[u1_ExistPDIDNum].u1ReqType      = Dcm_Dsp_Periodic_stPdidInfoTbl[u1_Cnt].u1ReqType;
                Dcm_Dsp_Periodic_stPdidInfoTbl[u1_ExistPDIDNum].u1Rate         = Dcm_Dsp_Periodic_stPdidInfoTbl[u1_Cnt].u1Rate;
                Dcm_Dsp_Periodic_stPdidInfoTbl[u1_ExistPDIDNum].u1Status       = Dcm_Dsp_Periodic_stPdidInfoTbl[u1_Cnt].u1Status;
                Dcm_Dsp_Periodic_stPdidInfoTbl[u1_ExistPDIDNum].bQueueflg      = Dcm_Dsp_Periodic_stPdidInfoTbl[u1_Cnt].bQueueflg;
                Dcm_Dsp_Periodic_u2ConnectionIdMirror[u1_ExistPDIDNum]         = Dcm_Dsp_Periodic_stPdidInfoTbl[u1_ExistPDIDNum].u2ConnectionID;
            }
            u1_ExistPDIDNum = (uint8)(u1_ExistPDIDNum + (uint8)1U);
        }
        else
        {
            u2_PdidConnectionId = Dcm_Dsp_Periodic_stPdidInfoTbl[u1_Cnt].u2ConnectionID;
            Dcm_Dsp_PeriodicMng_SetConnectionIdList( ptConnectionIdList, ptListNum, u2_PdidConnectionId );
        }
    }
    *ptUpdPDIDNum = u1_ExistPDIDNum;
    
    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_PeriodicMng_InitMsgCntxt                         */
/* Description   | This function sets designation parameter in              */
/*               | the transmit and receive management area.                */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsp_PeriodicMng_InitMsgCntxt
( void )
{
    Dcm_Dsp_Periodic_stMsgContext.reqData        = NULL_PTR;
    Dcm_Dsp_Periodic_stMsgContext.reqDataLen     = (uint32)0U;
    Dcm_Dsp_Periodic_stMsgContext.resData        = NULL_PTR;
    Dcm_Dsp_Periodic_stMsgContext.resDataLen     = (uint32)0U;
    Dcm_Dsp_Periodic_stMsgContext.msgAddInfo.reqType             = (uint8)0U;
    Dcm_Dsp_Periodic_stMsgContext.msgAddInfo.suppressPosResponse = STD_OFF;
    Dcm_Dsp_Periodic_stMsgContext.resMaxDataLen  = (uint32)0U;
    Dcm_Dsp_Periodic_stMsgContext.idContext      = (uint8)0U;
    Dcm_Dsp_Periodic_stMsgContext.dcmRxPduId     = (uint16)0U;

    return ;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_PeriodicMng_SendMain                             */
/* Description   | Periodic Transmisson Send Main                           */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_PeriodicMng_SendMain
( void ) 
{
    Std_ReturnType u1_RetSendResult;

    if( Dcm_Dsp_Periodic_u1DidInfo_RegNum == (uint8)0U )
    {
        Dcm_Dsp_PeriodicMng_SendStop();
    }
    else
    {
        /* Confirmation of Periodic transmission results */
        u1_RetSendResult = Dcm_Dsp_PeriodicMng_SendResult();
        if( u1_RetSendResult == (Std_ReturnType)E_OK )
        {
            Dcm_Dsp_PeriodicMng_SendPDIDStatusUpdate();
            Dcm_Dsp_PeriodicMng_SendQueueRebuild();
            Dcm_Dsp_PeriodicMng_SendDownCount();
            Dcm_Dsp_PeriodicMng_SendRequest();
        }
    }
    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_PeriodicMng_SendResult                           */
/* Description   | Periodic Transmisson Send Result                         */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK     : Transmission success or Sending        */
/*               |        E_NOT_OK : Transmission failure                   */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_PeriodicMng_SendResult
( void ) 
{
    uint16             u2_ConnectionId;
    Std_ReturnType     u1_RetVal;
    Std_ReturnType     u1_RetSendResult;
    uint8              u1_Rate;
    uint8              u1_PdidRegNum;
    uint8              u1_PdidCnt;

    u1_RetVal          = E_OK;

    if( Dcm_Dsp_Periodic_bSendResultChkFlag == (boolean)TRUE )
    {
        u2_ConnectionId = DCM_DSL_ALL_TARGETS ;
        u1_RetSendResult = Dcm_Dsl_GetPeriodicSendResult(u2_ConnectionId);
        
        if( u1_RetSendResult == DCM_DSL_PERIODICTX_COMPLETE )
        {
            Dcm_Dsp_Periodic_bSendResultChkFlag = (boolean)FALSE;
            u1_PdidRegNum = Dcm_Dsp_Periodic_u1DidInfo_RegNum;
            for( u1_PdidCnt = (uint8)0U; u1_PdidCnt < u1_PdidRegNum; u1_PdidCnt++ )
            {
                if( Dcm_Dsp_Periodic_stPdidInfoTbl[u1_PdidCnt].u1Status == DCM_DSP_PERIODIC_SENDCOMPWAIT )
                {
                    Dcm_Dsp_Periodic_stPdidInfoTbl[u1_PdidCnt].u1Status = DCM_DSP_PERIODIC_DOWNCOUNT;
                    u1_Rate = Dcm_Dsp_Periodic_stPdidInfoTbl[u1_PdidCnt].u1Rate ;
                    if( ( u1_Rate >= DCM_DSP_SID2A_CONDITION_SLOW ) && ( u1_Rate <= DCM_DSP_SID2A_CONDITION_FAST ) ) 
                    {
                        Dcm_Dsp_Periodic_stPdidInfoTbl[u1_PdidCnt].u4DownCounter = Dcm_Dsp_stTransMissionModeInfoTbl[u1_Rate - DCM_DSP_PERIODIC_TMMODEINFOTBL_INDEX].u4DownCounter;
                    }
                    else
                    {
                        /* Suppress Periodic Transmission and Wait for deletion */
                        Dcm_Dsp_Periodic_stPdidInfoTbl[u1_PdidCnt].u4DownCounter = DCM_DSP_PERIODIC_INVALID_DOWNCNT;
                        Dcm_Dsp_Periodic_stPdidInfoTbl[u1_PdidCnt].u1Status = DCM_DSP_PERIODIC_INIT;
                    }
                }
            }
        } 
        else if( u1_RetSendResult == DCM_DSL_PERIODICTX_ERROR )
        {
            Dcm_Dsp_PeriodicMng_SendStop();
            u1_RetVal = E_NOT_OK;
        }
        else
        {
            /*Check The result Again In The Next Periodic Transmission Cycle */
            /* No process */
        }
    }
    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_PeriodicMng_SendStop                             */
/* Description   | Clear the execution status of periodic transmission      */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_PeriodicMng_SendStop
( void ) 
{
    uint16  u2_ConnectionIdList[DCM_DSP_PERIODIC_CONNECTIONID_LISTNUM] = {0};
    uint8   u1_OpStatus;
    uint8   u1_Pdid;
    uint8   u1_ListNum;
    
    u1_ListNum = (uint8)0U;
    
    if( Dcm_Dsp_Periodic_u4PendingCnt != (uint32)0U )
    {
        u1_OpStatus = DCM_PERIODIC_CANCEL;
        u1_Pdid = Dcm_Dsp_Periodic_u1PendingPdid;
        (void)Dcm_Dsp_PeriodicMng_ReadPeriodicDid( &Dcm_Dsp_Periodic_stMsgContext, u1_OpStatus, u1_Pdid );             /* no return check required */
    }
    
    /* Get ConnectionID from PDID table */
    Dcm_Dsp_PeriodicMng_GetConnectionIdList( &u2_ConnectionIdList[DCM_DSP_PERIODIC_START_POS], &u1_ListNum);
    
    Dcm_Dsp_Periodic_u1TransferMode       = DCM_DSP_PERIODICTRANSFER_OFF;
    Dcm_Dsp_Periodic_u1DidInfo_RegNum     = (uint8)0U;
    Dcm_Dsp_Periodic_stQueueInfo.u1OutPos = (uint8)0U;
    Dcm_Dsp_Periodic_stQueueInfo.u1InPos  = (uint8)0U;
    Dcm_Dsp_Periodic_u4PendingCnt         = (uint32)0U;
    Dcm_Dsp_Periodic_bSendResultChkFlag   = (boolean)FALSE;
    Dcm_Dsp_Periodic_bQueueMaxFlag        = (boolean)FALSE;
    Dcm_Dsp_Periodic_u1RegNumMirror       = Dcm_Dsp_Periodic_u1DidInfo_RegNum;
    
    /* Inactive communication bus  */
    Dcm_Dsp_PeriodicMng_SetComActive( (boolean)FALSE, u1_ListNum, &u2_ConnectionIdList[DCM_DSP_PERIODIC_START_POS] );
    
    return;

}


/****************************************************************************/
/* Function Name | Dcm_Dsp_PeriodicMng_SendPDIDStatusUpdate                 */
/* Description   | Status Update the PDID information .                     */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_PeriodicMng_SendPDIDStatusUpdate
( void ) 
{
    uint8              u1_Rate;
    uint8              u1_PdidRegNum;
    uint8              u1_PdidCnt;
    uint8              u1_PrevCnt;
    uint8              u1_PdidPrevCnt;
    boolean            bSameRateHitFlag;
    
    u1_PdidRegNum = Dcm_Dsp_Periodic_u1DidInfo_RegNum;
    
    for( u1_PdidCnt = (uint8)0U; u1_PdidCnt < u1_PdidRegNum; u1_PdidCnt++ )
    {
        if( Dcm_Dsp_Periodic_stPdidInfoTbl[u1_PdidCnt].u1Status == DCM_DSP_PERIODIC_REGISTWAIT )
        {
            bSameRateHitFlag = (boolean)FALSE;
            u1_Rate = Dcm_Dsp_Periodic_stPdidInfoTbl[u1_PdidCnt].u1Rate;
            for( u1_PdidPrevCnt = u1_PdidCnt; u1_PdidPrevCnt > (uint8)0U; u1_PdidPrevCnt-- )
            {
                u1_PrevCnt = (uint8)(u1_PdidPrevCnt - (uint8)1U);
                if( Dcm_Dsp_Periodic_stPdidInfoTbl[u1_PrevCnt].u1Rate == u1_Rate )
                {
                    bSameRateHitFlag = (boolean)TRUE;
                    if( Dcm_Dsp_Periodic_stPdidInfoTbl[u1_PrevCnt].u1Status == DCM_DSP_PERIODIC_DOWNCOUNT )
                    {
                        Dcm_Dsp_Periodic_stPdidInfoTbl[u1_PdidCnt].u1Status = DCM_DSP_PERIODIC_DOWNCOUNT;
                        Dcm_Dsp_Periodic_stPdidInfoTbl[u1_PdidCnt].u4DownCounter = Dcm_Dsp_Periodic_stPdidInfoTbl[u1_PrevCnt].u4DownCounter;
                    }
                    break;
                }
            }
            if( bSameRateHitFlag == (boolean)FALSE )
            {
                /* The same rate does not exist before the own PDID (Delete or stop case) */
                Dcm_Dsp_Periodic_stPdidInfoTbl[u1_PdidCnt].u1Status = DCM_DSP_PERIODIC_DOWNCOUNT;
                Dcm_Dsp_Periodic_stPdidInfoTbl[u1_PdidCnt].u4DownCounter = (uint8)0U;
            }
        }
    }
    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_PeriodicMng_SendQueueRebuild                     */
/* Description   | Rebuild send queue only for the PDIDs which is valid.    */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_PeriodicMng_SendQueueRebuild
( void ) 
{
    uint32  u4_PendCnt;
    uint16  u2_TargetQuePos;
    uint8   u1_QueNum;
    uint8   u1_PdidRegNum;
    uint8   u1_OpStatus;
    uint8   u1_Pdid;
    uint8   u1_PdidCnt;
    uint8   u1_Status;
    uint8   u1_QuePosCnt;
    uint8   u1_OutPos;
    uint8   u1_QueMaxNum;
    uint8   u1_DelTargetPdid;
    boolean b_DelFlag;
    boolean b_DelTargetPdidDetectedFlag;
    
    u1_QueNum  = (uint8)0U;
    u1_PdidRegNum = Dcm_Dsp_Periodic_u1DidInfo_RegNum;
    u1_OutPos = Dcm_Dsp_Periodic_stQueueInfo.u1OutPos;
    u1_QueMaxNum = Dcm_Dsp_Periodic_u1PdidInfoTbl;
    u4_PendCnt   = Dcm_Dsp_Periodic_u4PendingCnt;
    
    Dcm_Dsp_PeriodicMng_QueueNumChk( &u1_QueNum );
    
    if( u1_QueNum != (uint8)0U )
    {
        b_DelTargetPdidDetectedFlag = (boolean)FALSE;
        for( u1_QuePosCnt = (uint8)0U; u1_QuePosCnt < u1_QueNum; u1_QuePosCnt++ )
        {
            b_DelFlag = (boolean)FALSE;
            u2_TargetQuePos = (uint16)((uint16)u1_OutPos + (uint16)u1_QuePosCnt);
            if( u2_TargetQuePos >= (uint16)u1_QueMaxNum )
            {
                u2_TargetQuePos -= (uint16)u1_QueMaxNum;
            }
            for( u1_PdidCnt = (uint8)0U; u1_PdidCnt < u1_PdidRegNum; u1_PdidCnt++ )
            {
                if( Dcm_Dsp_Periodic_u1SendQueue[u2_TargetQuePos] == Dcm_Dsp_Periodic_stPdidInfoTbl[u1_PdidCnt].u1Pdid )
                {
                    u1_Status = Dcm_Dsp_Periodic_stPdidInfoTbl[u1_PdidCnt].u1Status;
                    if(( u1_Status == DCM_DSP_PERIODIC_DOWNCOUNT ) || ( u1_Status == DCM_DSP_PERIODIC_REGISTWAIT ))
                    {
                        /* If PDID is re-registered */
                        b_DelFlag = (boolean)TRUE;
                    }
                    break;
                }
            }
            if( u1_PdidCnt == u1_PdidRegNum )
            {
                /* If PDID is not in Dcm_Dsp_Periodic_stPdidInfoTbl */
                b_DelFlag = (boolean)TRUE;
            }

            if( b_DelFlag == (boolean)TRUE )
            {
                if( u4_PendCnt != (uint32)0U )
                {
                    u1_OpStatus = DCM_PERIODIC_CANCEL;
                    u1_Pdid = Dcm_Dsp_Periodic_u1PendingPdid;
                    (void)Dcm_Dsp_PeriodicMng_ReadDidData( &Dcm_Dsp_Periodic_stMsgContext, u1_OpStatus, u1_Pdid );             /* no return check required */
                    u4_PendCnt = (uint32)0U;
                    Dcm_Dsp_Periodic_u4PendingCnt = u4_PendCnt;
                }
                if( b_DelTargetPdidDetectedFlag == (boolean)FALSE)
                {
                    b_DelTargetPdidDetectedFlag = (boolean)TRUE;
                    u1_DelTargetPdid = Dcm_Dsp_Periodic_u1SendQueue[u2_TargetQuePos];
                }
                else
                {
                    Dcm_Dsp_Periodic_u1SendQueue[u2_TargetQuePos] = u1_DelTargetPdid;
                }
            }
        }
        if( b_DelTargetPdidDetectedFlag == (boolean)TRUE)
        {
            Dcm_Dsp_PeriodicMng_DeleteSendQueue( u1_QueNum, u1_DelTargetPdid);
        }
    }
    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_PeriodicMng_DeleteSendQueue                      */
/* Description   | Delete the Send Queue that needs to be deleted           */
/* Preconditions | None                                                     */
/* Parameters    | [IN]  u1QueNum        : Send Queue Regist num            */
/*               | [IN]  u1DelTargetPdid : Delete Target PDID               */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_PeriodicMng_DeleteSendQueue
(
    const uint8 u1QueNum,
    const uint8 u1DelTargetPdid
)
{
    uint16        u2_TargetQuePos;
    uint16        u2_ExistQuePos;
    uint8         u1_OutPos;
    uint8         u1_ExistQueNum;
    uint8         u1_QueMaxNum;
    uint8         u1_QuePdid;
    uint8         u1_QuePosCnt;
    
    u1_OutPos    = Dcm_Dsp_Periodic_stQueueInfo.u1OutPos;
    u1_QueMaxNum = Dcm_Dsp_Periodic_u1PdidInfoTbl;
    u1_ExistQueNum = (uint8)0U;
    
    for( u1_QuePosCnt = (uint8)0U; u1_QuePosCnt < u1QueNum; u1_QuePosCnt++ )
    {
        u2_TargetQuePos = (uint16)((uint16)u1_OutPos + (uint16)u1_QuePosCnt);
        if( u2_TargetQuePos >= (uint16)u1_QueMaxNum )
        {
            u2_TargetQuePos -= (uint16)u1_QueMaxNum;
        }
        u1_QuePdid = Dcm_Dsp_Periodic_u1SendQueue[u2_TargetQuePos];
        if( u1DelTargetPdid != u1_QuePdid)
        {
            u2_ExistQuePos = (uint16)((uint16)u1_OutPos + (uint16)u1_ExistQueNum); 
            if( u2_ExistQuePos >= (uint16)u1_QueMaxNum )
            {
                u2_ExistQuePos -= (uint16)u1_QueMaxNum;
            }
            if( u2_TargetQuePos != u2_ExistQuePos)
            {
                Dcm_Dsp_Periodic_u1SendQueue[u2_ExistQuePos] = Dcm_Dsp_Periodic_u1SendQueue[u2_TargetQuePos];
            }
            u1_ExistQueNum = (uint8)(u1_ExistQueNum + (uint8)1U);
        }
    }
    u2_ExistQuePos = (uint16)((uint16)u1_OutPos + (uint16)u1_ExistQueNum);
    if( u2_ExistQuePos >= (uint16)u1_QueMaxNum )
    {
        u2_ExistQuePos -= (uint16)u1_QueMaxNum;
    }
    Dcm_Dsp_Periodic_stQueueInfo.u1InPos = (uint8)u2_ExistQuePos;
    Dcm_Dsp_Periodic_bQueueMaxFlag = (boolean)FALSE;
    
    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_PeriodicMng_SendDownCount                        */
/* Description   | Down Count Processing of PDID Info TBL Down Counter      */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_PeriodicMng_SendDownCount
( void ) 
{
    uint8   u1_Rate;
    uint8   u1_PdidRegNum;
    uint8   u1_PdidCnt;
    uint8   u1_PdidCnt2;
    uint8   u1_RateEndPdid[ DCM_DSP_PERIODIC_RATEMODE_NUM ] = {0};
    boolean b_SkipFlag;
    Std_ReturnType u1_RetSetQue;
    
    u1_PdidRegNum = Dcm_Dsp_Periodic_u1DidInfo_RegNum;
    b_SkipFlag    = (boolean)FALSE;
    

    for( u1_PdidCnt = (uint8)0U; u1_PdidCnt < u1_PdidRegNum; u1_PdidCnt++ )
    {
        if( Dcm_Dsp_Periodic_stPdidInfoTbl[u1_PdidCnt].u1Status == DCM_DSP_PERIODIC_DOWNCOUNT )
        {
            u1_Rate = Dcm_Dsp_Periodic_stPdidInfoTbl[u1_PdidCnt].u1Rate ;
            if( ( u1_Rate >= DCM_DSP_SID2A_CONDITION_SLOW ) && ( u1_Rate <= DCM_DSP_SID2A_CONDITION_FAST ) )
            {
                /* [0]:SlowRate,[1]:MediumRate,[2]:FastRate */
                u1_RateEndPdid[u1_Rate - (uint8)1U] = Dcm_Dsp_Periodic_stPdidInfoTbl[u1_PdidCnt].u1Pdid;
            }
        }
    }
    for( u1_PdidCnt = (uint8)0U; u1_PdidCnt < u1_PdidRegNum; u1_PdidCnt++ )
    {
        if( Dcm_Dsp_Periodic_stPdidInfoTbl[u1_PdidCnt].u1Status == DCM_DSP_PERIODIC_DOWNCOUNT )
        {
            if( Dcm_Dsp_Periodic_stPdidInfoTbl[u1_PdidCnt].u4DownCounter != (uint32)0U )
            {
                 Dcm_Dsp_Periodic_stPdidInfoTbl[u1_PdidCnt].u4DownCounter--;
            }
            if( Dcm_Dsp_Periodic_stPdidInfoTbl[u1_PdidCnt].u4DownCounter == (uint32)0U )
            {
                if( Dcm_Dsp_Periodic_stPdidInfoTbl[u1_PdidCnt].bQueueflg == (boolean)FALSE )
                {
                    u1_RetSetQue = Dcm_Dsp_PeriodicMng_SetSendQueue( u1_PdidCnt );
                    if( u1_RetSetQue == (Std_ReturnType)E_OK )
                    {
                        Dcm_Dsp_Periodic_stPdidInfoTbl[u1_PdidCnt].u1Status  = DCM_DSP_PERIODIC_SENDWAIT;
                        Dcm_Dsp_Periodic_stPdidInfoTbl[u1_PdidCnt].bQueueflg = (boolean)TRUE;
                    }
                    u1_Rate = Dcm_Dsp_Periodic_stPdidInfoTbl[u1_PdidCnt].u1Rate;
                    if( ( u1_Rate >= DCM_DSP_SID2A_CONDITION_SLOW ) && ( u1_Rate <= DCM_DSP_SID2A_CONDITION_FAST ) ) 
                    {
                        if( Dcm_Dsp_Periodic_stPdidInfoTbl[u1_PdidCnt].u1Pdid == u1_RateEndPdid[u1_Rate - (uint8)1U] )
                        {
                            for( u1_PdidCnt2 = (uint8)0U; u1_PdidCnt2 < u1_PdidRegNum; u1_PdidCnt2++ )
                            {
                                if( u1_Rate == Dcm_Dsp_Periodic_stPdidInfoTbl[u1_PdidCnt2].u1Rate )
                                {
                                    Dcm_Dsp_Periodic_stPdidInfoTbl[u1_PdidCnt2].bQueueflg = (boolean)FALSE;
                                }
                            }
                        }
                    }
                }
                else
                {
                    b_SkipFlag = (boolean)TRUE;
                }
            }
        }
    }
    if ( b_SkipFlag == (boolean)TRUE )
    {
        for( u1_PdidCnt = (uint8)0U; u1_PdidCnt < u1_PdidRegNum; u1_PdidCnt++ )
        {
            if( Dcm_Dsp_Periodic_stPdidInfoTbl[u1_PdidCnt].u1Status == DCM_DSP_PERIODIC_DOWNCOUNT )
            {
                if( Dcm_Dsp_Periodic_stPdidInfoTbl[u1_PdidCnt].u4DownCounter == (uint32)0U )
                {
                    u1_RetSetQue = Dcm_Dsp_PeriodicMng_SetSendQueue( u1_PdidCnt );
                    if( u1_RetSetQue == (Std_ReturnType)E_OK )
                    {
                        Dcm_Dsp_Periodic_stPdidInfoTbl[u1_PdidCnt].u1Status  = DCM_DSP_PERIODIC_SENDWAIT;
                        Dcm_Dsp_Periodic_stPdidInfoTbl[u1_PdidCnt].bQueueflg = (boolean)TRUE;
                    }
                }
            }
        }
    }
    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_PeriodicMng_SendRequest                          */
/* Description   | Periodic Transmisson Send Request                        */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_PeriodicMng_SendRequest
( void ) 
{
    uint16          u2_ConnectionId;
    uint8           u1_QueNum;

    if( Dcm_Dsp_Periodic_bSendResultChkFlag == (boolean)FALSE )
    {
        Dcm_Dsp_PeriodicMng_QueueNumChk( &u1_QueNum );
        if( u1_QueNum != (uint8)0U )
        {
            if( Dcm_Dsp_Periodic_u4PendingCnt == (uint32)0U )
            {
                u2_ConnectionId = DCM_DSL_ALL_TARGETS ;
                Dcm_Dsl_PeriodicSendStart( u2_ConnectionId );
            }
            /* Periodic Transmission Send Request Main Proc */
            Dcm_Dsp_PeriodicMng_SendReqMain( u1_QueNum );
        } 
    }
    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_PeriodicMng_SendReqMain                          */
/* Description   | Periodic Transmisson Send Request Main                   */
/* Preconditions | None                                                     */
/* Parameters    | [in] u1QueNum : Send Queue Regist Num                    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_PeriodicMng_SendReqMain
( 
    const uint8 u1QueNum 
) 
{
    uint32          u4_PendCnt;
    uint32          u4_PaddingCnt;
    uint16          u2_ConnectionId;
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pt_PeriodicBuf;
    Dcm_MsgLenType  u4_ResMaxDataLen;
    Dcm_MsgLenType  u4_PaddingMaxDataLen;
    Std_ReturnType  u1_RetReadDid;
    Std_ReturnType  u1_RetSendReq;
    uint8           u1_PdidRegNum;
    uint8           u1_QueCnt;
    uint8           u1_OpStatus;
    uint8           u1_QuePdid;
    uint8           u1_PdidCnt;
    uint8           u1_ReqType;
    uint8           u1_QueMaxNum;
    uint8           u1_OutPos;
    uint8           u1_PaddingValue;
    boolean         b_SendFlag;
    boolean         b_BreakFlag;
    boolean         b_PaddingUsed;

    u1_PdidRegNum = Dcm_Dsp_Periodic_u1DidInfo_RegNum;
    u1_QueMaxNum = Dcm_Dsp_Periodic_u1PdidInfoTbl;
    u4_PendCnt   = Dcm_Dsp_Periodic_u4PendingCnt;
    u1_OutPos    = Dcm_Dsp_Periodic_stQueueInfo.u1OutPos;
    
    b_BreakFlag = (boolean)FALSE;
    u2_ConnectionId = (uint16)0U;
    u1_ReqType = (uint8)0U;
    
    for( u1_QueCnt = (uint8)0U; u1_QueCnt < u1QueNum; u1_QueCnt++ )
    {
        b_SendFlag = (boolean)FALSE;
        if( u1_OutPos < u1_QueMaxNum )
        {
            u1_QuePdid = Dcm_Dsp_Periodic_u1SendQueue[ u1_OutPos ];
            for(u1_PdidCnt = (uint8)0U; u1_PdidCnt < u1_PdidRegNum; u1_PdidCnt++ )
            {
                if ( u1_QuePdid == Dcm_Dsp_Periodic_stPdidInfoTbl[u1_PdidCnt].u1Pdid )
                {
                    u2_ConnectionId = Dcm_Dsp_Periodic_stPdidInfoTbl[u1_PdidCnt].u2ConnectionID;
                    u1_ReqType      = Dcm_Dsp_Periodic_stPdidInfoTbl[u1_PdidCnt].u1ReqType;
                    break;
                }
            }
            if( u4_PendCnt == (uint32)0U )
            {
                pt_PeriodicBuf = Dcm_Dsl_GetPeriodicTxBuf( u2_ConnectionId, &u4_ResMaxDataLen);
                if( pt_PeriodicBuf != NULL_PTR )
                {
                    u1_OpStatus = DCM_PERIODIC_INITIAL;
                    Dcm_Dsp_Periodic_stMsgContext.resData = pt_PeriodicBuf;
                    Dcm_Dsp_Periodic_stMsgContext.resData[0] = u1_QuePdid;
                    Dcm_Dsp_Periodic_stMsgContext.resDataLen = DCM_DSP_PERIODIC_READDATA_PDIDSIZE;
                    Dcm_Dsp_Periodic_stMsgContext.msgAddInfo.reqType = u1_ReqType;
                    Dcm_Dsp_Periodic_stMsgContext.resMaxDataLen = u4_ResMaxDataLen;
                    u1_RetReadDid = Dcm_Dsp_PeriodicMng_ReadDidData( &Dcm_Dsp_Periodic_stMsgContext, u1_OpStatus, u1_QuePdid );
                    if( u1_RetReadDid == DCM_DSP_PERIODIC_PENDING )
                    {
                        Dcm_Dsp_Periodic_stPdidInfoTbl[u1_PdidCnt].u1Status = DCM_DSP_PERIODIC_READWAIT;
                        Dcm_Dsp_Periodic_bSendResultChkFlag = (boolean)FALSE;
                        b_BreakFlag = (boolean)TRUE;
                    }
                    else if( u1_RetReadDid == DCM_DSP_PERIODIC_STOP )
                    {
                        b_BreakFlag = (boolean)TRUE;
                    }
                    else
                    {
                        b_SendFlag = (boolean)TRUE;
                    }
                }
                else
                {
                    /* NULL Pointe equal Reached the maximum number of transmissions */
                    b_BreakFlag = (boolean)TRUE;
                }
            }
            else
            {
                u1_OpStatus = DCM_PERIODIC_PENDING;
                u1_RetReadDid = Dcm_Dsp_PeriodicMng_ReadDidData( &Dcm_Dsp_Periodic_stMsgContext, u1_OpStatus, u1_QuePdid );
                if( (u1_RetReadDid == DCM_DSP_PERIODIC_PENDING ) || ( u1_RetReadDid == DCM_DSP_PERIODIC_STOP ) )
                {
                    Dcm_Dsp_Periodic_bSendResultChkFlag = (boolean)FALSE;
                    b_BreakFlag = (boolean)TRUE;
                }
                else
                {
                    b_SendFlag = (boolean)TRUE;
                    if( u1_RetReadDid == DCM_DSP_PERIODIC_NOTOK )
                    {
                        /* When reading fails from pending, transfer data is PDID only. */
                        Dcm_Dsp_Periodic_stMsgContext.resDataLen = DCM_DSP_PERIODIC_READDATA_PDIDSIZE;
                    }
                }
            }
            
            if( b_SendFlag == (boolean)TRUE )
            {
                b_PaddingUsed = Dcm_Dsp_Periodic_bPaddingUsed;
                if( b_PaddingUsed == (boolean)TRUE )
                {
                    u4_PaddingMaxDataLen = Dcm_Dsp_Periodic_stMsgContext.resMaxDataLen;
                    u1_PaddingValue = Dcm_Dsp_Periodic_u1PaddingValue;
                    for( u4_PaddingCnt = Dcm_Dsp_Periodic_stMsgContext.resDataLen; u4_PaddingCnt < u4_PaddingMaxDataLen; u4_PaddingCnt++ )
                    {
                        Dcm_Dsp_Periodic_stMsgContext.resData[u4_PaddingCnt] = u1_PaddingValue;
                    }
                    Dcm_Dsp_Periodic_stMsgContext.resDataLen = u4_PaddingMaxDataLen;
                }

                u1_RetSendReq = Dcm_Dsl_PeriodicSendReq( &Dcm_Dsp_Periodic_stMsgContext, u2_ConnectionId );
                if( u1_RetSendReq == (Std_ReturnType)E_OK )
                {
                    Dcm_Dsp_Periodic_stPdidInfoTbl[u1_PdidCnt].u1Status = DCM_DSP_PERIODIC_SENDCOMPWAIT;
                    if( u1_OutPos == (uint8)( u1_QueMaxNum - (uint8)1U ) )
                    {
                        u1_OutPos = (uint8)0U;
                    }
                    else
                    {
                        u1_OutPos = (uint8)(u1_OutPos + (uint8)1U);
                    }
                    Dcm_Dsp_Periodic_stQueueInfo.u1OutPos = u1_OutPos;
                    Dcm_Dsp_Periodic_bQueueMaxFlag = (boolean)FALSE;
                    Dcm_Dsp_Periodic_bSendResultChkFlag = (boolean)TRUE;
                }
                else
                {
                    b_BreakFlag     = (boolean)TRUE;
                }
            }
        }
        else
        {
            Dcm_Dsp_PeriodicMng_SendStop();
            b_BreakFlag = (boolean)TRUE;
        }
        if( b_BreakFlag == (boolean)TRUE )
        {
            break;
        }
    }
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_PeriodicMng_QueueNumChk                          */
/* Description   | Send Queue Num Check                                     */
/* Preconditions | None                                                     */
/* Parameters    | [Out] ptQueNum : Queue Regist Num                        */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_PeriodicMng_QueueNumChk
( 
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptQueNum
) 
{
    boolean   b_Quemaxflag;
    
    b_Quemaxflag = Dcm_Dsp_Periodic_bQueueMaxFlag;
    
    if ( Dcm_Dsp_Periodic_stQueueInfo.u1OutPos ==  Dcm_Dsp_Periodic_stQueueInfo.u1InPos )
    {
        if( b_Quemaxflag != (boolean)TRUE)
        {
            *ptQueNum = (uint8)0U;
        }
        else
        {
            *ptQueNum = Dcm_Dsp_Periodic_u1PdidInfoTbl;
        }
    }
    else if( Dcm_Dsp_Periodic_stQueueInfo.u1OutPos < Dcm_Dsp_Periodic_stQueueInfo.u1InPos )
    {
        *ptQueNum = (uint8)(Dcm_Dsp_Periodic_stQueueInfo.u1InPos - Dcm_Dsp_Periodic_stQueueInfo.u1OutPos);
    }
    else
    {
        /* Dcm_Dsp_Periodic_stQueueInfo.u1OutPos > Dcm_Dsp_Periodic_stQueueInfo.u1InPos */
        *ptQueNum = (uint8)( Dcm_Dsp_Periodic_u1PdidInfoTbl - (Dcm_Dsp_Periodic_stQueueInfo.u1OutPos - Dcm_Dsp_Periodic_stQueueInfo.u1InPos));
    }
    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_PeriodicMng_SetSendQueue                         */
/* Description   | Periodic Transmisson Set Send Queue                      */
/* Preconditions | None                                                     */
/* Parameters    | [in] u1PdidCnt : Periodic Did Index Count                */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Set Send Queue OK                          */
/*               |        E_NOT_OK : Set Send Queue NG (Queue Full)         */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_PeriodicMng_SetSendQueue
( 
    const uint8 u1PdidCnt 
) 
{
    Std_ReturnType u1_RetVal;
    uint8          u1_QueMaxNum;
    boolean   b_Quemaxflag;
    
    u1_RetVal = E_NOT_OK;
    u1_QueMaxNum = Dcm_Dsp_Periodic_u1PdidInfoTbl;
    b_Quemaxflag = Dcm_Dsp_Periodic_bQueueMaxFlag;
    
    if( Dcm_Dsp_Periodic_stQueueInfo.u1InPos < u1_QueMaxNum )
    {
        if( b_Quemaxflag != (boolean)TRUE)
        {
            Dcm_Dsp_Periodic_u1SendQueue[Dcm_Dsp_Periodic_stQueueInfo.u1InPos] = Dcm_Dsp_Periodic_stPdidInfoTbl[u1PdidCnt].u1Pdid;
            if( Dcm_Dsp_Periodic_stQueueInfo.u1InPos == (uint8)( u1_QueMaxNum - (uint8)1U ) )
            {
                Dcm_Dsp_Periodic_stQueueInfo.u1InPos = (uint8)0U;
            }
            else
            {
                Dcm_Dsp_Periodic_stQueueInfo.u1InPos = (uint8)(Dcm_Dsp_Periodic_stQueueInfo.u1InPos + (uint8)1U);
            
            }
            if ( Dcm_Dsp_Periodic_stQueueInfo.u1OutPos == Dcm_Dsp_Periodic_stQueueInfo.u1InPos )
            {
                Dcm_Dsp_Periodic_bQueueMaxFlag = (boolean)TRUE ;
            }
            u1_RetVal = E_OK;
        }
    }
    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_PeriodicMng_ReadDidData                          */
/* Description   | Read data from PDID                                      */
/* Preconditions | None                                                     */
/* Parameters    | [in] ptMsgContext : Message Context                      */
/*               | [in] u1OpStatus   : Operation Status                     */
/*               | [in] u1Pdid       : Periodic Did                         */
/* Return Value  | uint8                                                    */
/*               |        DCM_DSP_PERIODIC_OK      : PDID Read OK           */
/*               |        DCM_DSP_PERIODIC_NOTOK   : PDID Read NG           */
/*               |        DCM_DSP_PERIODIC_PENDING : PDID Read PENDING      */
/*               |        DCM_DSP_PERIODIC_STOP    : Periodic TM Stop       */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( uint8, DCM_CODE ) Dcm_Dsp_PeriodicMng_ReadDidData
( 
    P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA)    ptMsgContext,
    const Dcm_OpStatusType                                 u1OpStatus,
    const uint8                                            u1Pdid
) 
{
    uint32              u4_UpperLimit;
    Std_ReturnType      u1_RetReadPDid;
    uint8               u1_RetVal;
    
    u1_RetVal      = DCM_DSP_PERIODIC_OK;
    u4_UpperLimit  = Dcm_Dsp_Periodic_u4DidReadUpperLimit;
    
    switch( u1OpStatus )
    {
        case DCM_PERIODIC_INITIAL:
        case DCM_PERIODIC_PENDING:
            u1_RetReadPDid = Dcm_Dsp_PeriodicMng_ReadPeriodicDid( ptMsgContext, u1OpStatus, u1Pdid );
            if( u1_RetReadPDid == (Std_ReturnType)E_OK )
            {
                Dcm_Dsp_Periodic_u4PendingCnt = (uint8)0U;
                u1_RetVal = DCM_DSP_PERIODIC_OK;
            }
            else if( u1_RetReadPDid == (Std_ReturnType)E_NOT_OK )
            {
                Dcm_Dsp_Periodic_u4PendingCnt = (uint8)0U;
                u1_RetVal = DCM_DSP_PERIODIC_NOTOK;
            }
            else
            {
                /* u1_RetReadPDid == (Std_ReturnType)DCM_E_PENDING */
                if( Dcm_Dsp_Periodic_u4PendingCnt < u4_UpperLimit )
                {
                    Dcm_Dsp_Periodic_u1PendingPdid = u1Pdid;
                    Dcm_Dsp_Periodic_u4PendingCnt++;
                    u1_RetVal = DCM_DSP_PERIODIC_PENDING;
                }
                else
                {
                    Dcm_Dsp_PeriodicMng_SendStop();
                    u1_RetVal = DCM_DSP_PERIODIC_STOP;
                }
            }
            break;
        case DCM_PERIODIC_CANCEL:
            (void)Dcm_Dsp_PeriodicMng_ReadPeriodicDid( ptMsgContext, u1OpStatus, u1Pdid );       /* no return check required */
            break;
        default:
            /* no process */
            break;
    }
    
    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_PeriodicMng_ReadPeriodicDid                      */
/* Description   | Data is read from the PDID                               */
/* Preconditions | None                                                     */
/* Parameters    | [IN/OUT]pMsgContext :Message Context(send data info)     */
/*               | [IN]u1OpStatus      :Operation Status                    */
/*               | [IN]u1Pdid          :Periodic DID(without "0xF2")        */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                                                     */
/*               | E_NOT_OK                                                 */
/*               | DCM_E_PENDING                                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_PeriodicMng_ReadPeriodicDid
(
    P2VAR( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA )    ptMsgContext,
    const Dcm_OpStatusType                                   u1OpStatus,
    const uint8                                              u1Pdid
)
{
    Dcm_MsgContextType                          st_MsgContext;
    uint32                                      u4_DataLen;
    uint32                                      u4_DataBufferLen;
    uint16                                      u2_Did;
    uint16                                      u2_Index;
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA )    pt_SendData;
    uint8                                       u1_KindOfDid;
    Std_ReturnType                              u1_RetVal;
    Std_ReturnType                              u1_RetChkDDDid;
    Std_ReturnType                              u1_RetReadDidDataFnc;
    Dcm_NegativeResponseCodeType                u1_LocalErrorCode;

    u1_RetVal               = E_NOT_OK;
    u4_DataLen              = 0U;
    st_MsgContext           = *ptMsgContext;
    pt_SendData             = &ptMsgContext->resData[st_MsgContext.resDataLen];
    u4_DataBufferLen        = st_MsgContext.resMaxDataLen;
    u1_LocalErrorCode       = (Dcm_NegativeResponseCodeType)0x00U;

    u2_Did = (uint16)( DCM_DSP_PERIODIC_PDID_HIGHBITE | ((uint16)u1Pdid) );

    /* Check DID */
    u1_RetChkDDDid = Dcm_Dsp_PeriodicMng_ChkDID( u2_Did, &u1_KindOfDid, &u2_Index );
    if( u1_RetChkDDDid == (Std_ReturnType)E_OK )
    {
        if( u1_KindOfDid == DCM_DSP_DIDMNG_DID_RANGE )
        {
            /* Call Xxx_ReadDidData function */
            u1_RetReadDidDataFnc = Dcm_Dsp_DidMng_CallReadDidFnc( u2_Index, u2_Did, pt_SendData, u1OpStatus, u4_DataBufferLen, &u4_DataLen, &u1_LocalErrorCode );
        }
        else
        {
            /* Call Xxx_ReadDidData function */
            u1_RetReadDidDataFnc = Dcm_Dsp_PeriodicMng_CallReadDynDidFnc( u2_Index, u1OpStatus, u4_DataBufferLen, pt_SendData, &u4_DataLen );
        }
        if( ( u1OpStatus == DCM_PERIODIC_INITIAL ) ||
            ( u1OpStatus == DCM_PERIODIC_PENDING ) )
        {
            if( u1_RetReadDidDataFnc == (Std_ReturnType)E_OK )
            {
                if( (st_MsgContext.resDataLen + u4_DataLen) <= u4_DataBufferLen )   /* no wrap around */
                {
                    ptMsgContext->resDataLen += u4_DataLen; /* no wrap around */
                    u1_RetVal = E_OK;
                }
            }
            else if( u1_RetReadDidDataFnc == (Std_ReturnType)DCM_E_PENDING )
            {
                if( (st_MsgContext.resDataLen + u4_DataLen) <= u4_DataBufferLen )   /* no wrap around */
                {
                    ptMsgContext->resDataLen += u4_DataLen; /* no wrap around */
                    u1_RetVal = DCM_E_PENDING;
                }
            }
            else
            {
                /* No process */
            }
        }
        else
        {
            u1_RetVal = E_OK;
        }
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_PeriodicMng_CallReadDynDidFnc                    */
/* Description   | Call the ReadDidFnc                                      */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2DidIndex : Index of the Did Table                 */
/*               | [in] u1OpStatus : Operation state                        */
/*               | [in] u4DataBufferLength : Buffer Length                  */
/*               | [out] ptData : Start pointer of read data                */
/*               | [out] ptDataLength : Read Data Length                    */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Process complete                           */
/*               |        E_NOT_OK : Process abnormal termination           */
/*               |        DCM_E_PENDING : Process pending                   */
/* Notes         | None                                                     */
/****************************************************************************/
#if( DCM_PERIODIC_DDDID_USE == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_PeriodicMng_CallReadDynDidFnc
(
    const uint16 u2DidIndex,
    const Dcm_OpStatusType u1OpStatus,
    const uint32 u4DataBufferLength,
    P2VAR( uint8,  AUTOMATIC, DCM_APPL_DATA ) ptData,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) ptDataLength
)
{
    Std_ReturnType    u1_RetVal;

    u1_RetVal = Dcm_Dsp_DidMng_CallReadDynDidFncForPeriodic( u2DidIndex, u1OpStatus, u4DataBufferLength, ptData, ptDataLength );

    return u1_RetVal;
}
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON */
#if( DCM_PERIODIC_DDDID_USE == STD_OFF )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_PeriodicMng_CallReadDynDidFnc
(
    const uint16 u2DidIndex,                               /* MISRA DEVIATION */
    const Dcm_OpStatusType u1OpStatus,                     /* MISRA DEVIATION */
    const uint32 u4DataBufferLength,                       /* MISRA DEVIATION */
    P2VAR( uint8,  AUTOMATIC, DCM_APPL_DATA ) ptData,      /* MISRA DEVIATION */
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) ptDataLength /* MISRA DEVIATION */
)
{
    return ( E_NOT_OK );
}
#endif /* DCM_PERIODIC_DDDID_USE == STD_OFF */


#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
#endif /* DCM_PERIODIC_SEND_USE */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
