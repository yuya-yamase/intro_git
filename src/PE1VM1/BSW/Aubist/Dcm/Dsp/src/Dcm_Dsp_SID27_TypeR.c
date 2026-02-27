/* Dcm_Dsp_SID27_TypeR_c(v5-3-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID27_TypeR/CODE                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_SID27.h>
#if ( DCM_SUPPORT_SID27 == STD_ON )
#if ( DCM_SEC_PECULIAR_TYPE_RED == STD_ON )
#include <Dcm/Dcm_Dsp_SID27_Callout.h>
#include <Dcm/Dcm_Dsp_StorageMng.h>
#include <Dcm/Dcm_Dsp_Main.h>
#include "../../Dsp/inc/Dcm_Dsp_MsgMaker.h"
#include <Dcm/Dcm_Dsl_Ctrl.h>
#include <Dcm/Dcm_Main_EvtDistr.h>
#include <Dcm/Dcm_Main_TmrSrv.h>
#include <Dcm_NvM.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

#define DCM_DSP_SID27_NO_SEEDREQUEST    ((uint8)0x00U)              /* Seed not requested state */
#define DCM_DSP_SID27_CALC_SEC_ADD_VAL  ((uint8)0x01U)              /* For security level calculation */
#define DCM_DSP_SID27_CALC_SHIFT_VAL    ((uint8)0x01U)              /* For shift value calculation */
#define DCM_DSP_SID27_INVALID_INDEX     ((uint8)0xFFU)              /* Invalid index of the Dcm_Dsp_SecurityParamTbl */
#define DCM_DSP_SID27_STATUS_1BIT       ((uint32)0x00000001UL)      /* For bit shift operation */
#define DCM_DSP_SID27_DTMR_STOP         ((uint8)0x00U)              /* delay timer stop  */
#define DCM_DSP_SID27_DTMR_START        ((uint8)0x01U)              /* delay timer start */
#define DCM_DSP_SID27_DTMR_STATUS_STOP  ((uint8)0x00U)              /* For checking delay timer activation */
#define DCM_DSP_SID27_DTMR_NOT_START    ((uint32)0UL)               /* Do not start timer */
#define DCM_DSP_SID27_ATT_CNT_INVALID   ((uint8)0U)                 /* Invalid value of the attempt counter */
#define DCM_DSP_SID27_WRITE_STORAGE_OFF ((uint8)0x00U)              /* Write Storage Flag OFF */
#define DCM_DSP_SID27_WRITE_STORAGE_ON  ((uint8)0x01U)              /* Write Storage Flag ON  */

/*----------------------------------------------------------------------------*/
/* Internal Function Prototypes                                               */
/*----------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID27_RSeedInitialProc
(
    const uint8 u1SubFncId,
    const Dcm_OpStatusType u1OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID27_SKeyInitialProc
(
    const uint8 u1SubFncId,
    const Dcm_OpStatusType u1OpStatus,
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
);
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID27_GetSeedProc
(
    const uint8 u1SecLevel,
    const Dcm_OpStatusType u1OpStatus
);
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID27_CompareKeyProc
(
    const uint8 u1SecLevel,
    const Dcm_OpStatusType u1OpStatus
);
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID27_FailedKeyProc
(
    void
);
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID27_RSeedCancelProc
(
    const Dcm_OpStatusType u1OpStatus
);
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID27_SKeyCancelProc
(
    const Dcm_OpStatusType u1OpStatus
);
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID27_SetDelayTimerSt
(
    const uint8 u1SecLevelIndex,
    const uint8 u1StatusId
);
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID27_Init_Storage
(
    void
);
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID27_WriteStorage
(
    void
);
#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*----------------------------------------------------------------------------*/
/* data                                                                       */
/*----------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

static VAR( uint32, DCM_VAR_NO_INIT )  Dcm_Dsp_SID27_u4DelayTimerSt;
static VAR( uint8, DCM_VAR_NO_INIT )   Dcm_Dsp_SID27_u1AttCntTmp[DCM_P_NVSEC_BLOCK_LEN];
static VAR( uint8, DCM_VAR_NO_INIT )   Dcm_Dsp_SID27_u1SecLvIndex;
static VAR( uint8, DCM_VAR_NO_INIT )   Dcm_Dsp_SID27_u1MngStatus;
static VAR( uint8, DCM_VAR_NO_INIT )   Dcm_Dsp_SID27_u1ReadStorageResult;
static VAR( boolean, DCM_VAR_NO_INIT ) Dcm_Dsp_SID27_bSeedFlag;
static VAR( boolean, DCM_VAR_NO_INIT ) Dcm_Dsp_SID27_bReadStorageCompleteFlag;

#define DCM_STOP_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

#define DCM_START_SEC_VAR_SAVED_ZONE
#include <Dcm_MemMap.h>

VAR( uint8, DCM_VAR_SAVED_ZONE )   Dcm_u1AttCnt[DCM_P_NVSEC_BLOCK_LEN];

#define DCM_STOP_SEC_VAR_SAVED_ZONE
#include <Dcm_MemMap.h>


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID27_Init                                       */
/* Description   | SID27 Initialization processing                          */
/* Preconditions | None                                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID27_Init                /* MISRA DEVIATION */
(
    void
)
{
    uint32  u4_DelayTimerOnBoot;
    uint8   u1_NvSecBlockLen;
    uint8   u1_AttClrCnt;
    uint8   u1_Cnt;
    uint8   u1_SecurityNum;
    uint8   u1_TimerId;

    Dcm_Dsp_SID27_u4DelayTimerSt = (uint32)0UL;
    u1_NvSecBlockLen             = Dcm_Dsp_u1Nvsec_Block_Len;
    u1_SecurityNum               = Dcm_Dsp_u1Security_N;

    for ( u1_AttClrCnt = (uint8)0U; u1_AttClrCnt < u1_NvSecBlockLen; u1_AttClrCnt++ )
    {
        Dcm_Dsp_SID27_u1AttCntTmp[u1_AttClrCnt] = (uint8)0U;
    }
    for ( u1_Cnt = (uint8)0U; u1_Cnt < u1_SecurityNum; u1_Cnt++ )
    {
        /* Initialize attempt counter with failsafe value */
        Dcm_Dsp_SID27_u1AttCntTmp[u1_Cnt] = Dcm_Dsp_SecurityParamTbl[u1_Cnt].u1NumAttDelay;
        u4_DelayTimerOnBoot = Dcm_Dsp_SecurityParamTbl[u1_Cnt].u4DelayTimeOnBoot;
        if( u4_DelayTimerOnBoot > DCM_DSP_SID27_DTMR_NOT_START )
        {
            /* DelayTimer Start */
            u1_TimerId = Dcm_Dsp_ConvertIdTbl[u1_Cnt].u1TimerId;
            Dcm_Main_TmrSrv_StartTimer( u1_TimerId, u4_DelayTimerOnBoot );
            Dcm_Dsp_SID27_SetDelayTimerSt( u1_Cnt, DCM_DSP_SID27_DTMR_START );
        }
    }
    Dcm_Dsp_SID27_u1MngStatus = DCM_DSP_SID27_NO_SEEDREQUEST;
    Dcm_Dsp_SID27_u1SecLvIndex = DCM_DSP_SID27_INVALID_INDEX;
    Dcm_Dsp_SID27_bSeedFlag = (boolean)FALSE;
    /* Initialization of storage related information */
    Dcm_Dsp_SID27_Init_Storage();

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID27_Refresh                                    */
/* Description   | SID27 Refresh processing                                 */
/* Preconditions | None                                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID27_Refresh             /* MISRA DEVIATION */
(
    void
)
{
    P2VAR(volatile boolean, AUTOMATIC, DCM_APPL_DATA) pt_ReadStorageCompleteFlag;
    boolean   b_ReadStorageCompleteFlag;

    pt_ReadStorageCompleteFlag  = &Dcm_Dsp_SID27_bReadStorageCompleteFlag;
    b_ReadStorageCompleteFlag   = *pt_ReadStorageCompleteFlag;
    *pt_ReadStorageCompleteFlag = b_ReadStorageCompleteFlag ;

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID27_GetSeedCbk                                 */
/* Description   | Callback function for event delivery registration of     */
/*               | Xxx_GetSeed                                              */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u1EventId        :Event ID                           */
/* Return Value  | void                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID27_GetSeedCbk          /* MISRA DEVIATION */
(
    const uint8 u1EventId   /* MISRA DEVIATION */
)
{
    uint8       u1_SecurityNum;
    uint8       u1_SecLvIndex;
    uint8       u1_SecLevel;

    u1_SecurityNum  = Dcm_Dsp_u1Security_N;
    u1_SecLvIndex   = Dcm_Dsp_SID27_u1SecLvIndex;

    if( u1_SecLvIndex < u1_SecurityNum )
    {
        u1_SecLevel = Dcm_Dsp_SecurityParamTbl[u1_SecLvIndex].u1Level;
        (void)Dcm_Dsp_SID27_GetSeedProc( u1_SecLevel, DCM_PENDING );    /* no return check required */
    }
    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID27_CompareKeyCbk                              */
/* Description   | Callback function for event delivery registration of     */
/*               | Xxx_CompareKey                                           */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u1EventId        :Event ID                           */
/* Return Value  | void                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID27_CompareKeyCbk       /* MISRA DEVIATION */
(
    const uint8 u1EventId   /* MISRA DEVIATION */
)
{
    uint8       u1_SecurityNum;
    uint8       u1_SecLvIndex;
    uint8       u1_SecLevel;

    u1_SecurityNum  = Dcm_Dsp_u1Security_N;
    u1_SecLvIndex   = Dcm_Dsp_SID27_u1SecLvIndex;

    if( u1_SecLvIndex < u1_SecurityNum )
    {
        u1_SecLevel = Dcm_Dsp_SecurityParamTbl[u1_SecLvIndex].u1Level;
        (void)Dcm_Dsp_SID27_CompareKeyProc( u1_SecLevel, DCM_PENDING ); /* no return check required */
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID27_DelayTimerCbk                              */
/* Description   | Callback function for Stop DelayTimer                    */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u1TimerId        :Timer ID                           */
/* Return Value  | void                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID27_DelayTimerCbk       /* MISRA DEVIATION */
(
    const uint8 u1TimerId
)
{
    uint8   u1_SecurityNum;
    uint8   u1_Cnt;

    u1_SecurityNum = Dcm_Dsp_u1Security_N;
    
    for( u1_Cnt = (uint8)0U; u1_Cnt < u1_SecurityNum; u1_Cnt++ )
    {
        if( u1TimerId == Dcm_Dsp_ConvertIdTbl[u1_Cnt].u1TimerId )
        {
            Dcm_Dsp_SID27_SetDelayTimerSt( u1_Cnt, DCM_DSP_SID27_DTMR_STOP );
            break;
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID27_ReadConfCbk                                */
/* Description   | Callback function for event delivery registration of     */
/*               | ReadConfirmation                                         */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u1EventId        :Event ID                           */
/* Return Value  | void                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID27_ReadConfCbk
(
    const uint8 u1EventId   /* MISRA DEVIATION */
)
{
    uint32              u4_ChkDelayTimerSt;
    uint32              u4_DelayTimerOnBoot;
    Std_ReturnType      u1_RetDTOnBoot;
    Std_ReturnType      u1_ReadStorageResult;
    uint8               u1_Cnt;
    uint8               u1_SecurityNum;
    uint8               u1_TimerId;
    uint8               u1_SecLevel;
    uint8               u1_AttCnt;
    uint8               u1_NumAttDelay;
    uint8               u1_WriteStorageFlag;

    u1_SecurityNum = Dcm_Dsp_u1Security_N;
    u1_ReadStorageResult = Dcm_Dsp_SID27_u1ReadStorageResult;
    u1_WriteStorageFlag = DCM_DSP_SID27_WRITE_STORAGE_OFF;
    
    for( u1_Cnt = (uint8)0U; u1_Cnt < u1_SecurityNum; u1_Cnt++ )
    {
        u4_DelayTimerOnBoot = Dcm_Dsp_SecurityParamTbl[u1_Cnt].u4DelayTimeOnBoot;
        if( u4_DelayTimerOnBoot > DCM_DSP_SID27_DTMR_NOT_START )
        {
            u1_SecLevel = Dcm_Dsp_SecurityParamTbl[u1_Cnt].u1Level;
            u1_AttCnt   = Dcm_Dsp_SID27_u1AttCntTmp[u1_Cnt];
            u1_NumAttDelay = Dcm_Dsp_SecurityParamTbl[u1_Cnt].u1NumAttDelay;
            u1_RetDTOnBoot = Dcm_CheckStartDelayTimerOnBoot( u1_ReadStorageResult, u1_SecLevel, u1_AttCnt, u1_NumAttDelay );
            if ( u1_RetDTOnBoot == (uint8)E_NOT_OK )
            {
                u1_TimerId = Dcm_Dsp_ConvertIdTbl[u1_Cnt].u1TimerId;
                Dcm_Main_TmrSrv_StopTimer( u1_TimerId );
                Dcm_Dsp_SID27_SetDelayTimerSt( u1_Cnt, DCM_DSP_SID27_DTMR_STOP );
            }
            else
            {
                u4_ChkDelayTimerSt = DCM_DSP_SID27_STATUS_1BIT << u1_Cnt;
                u4_ChkDelayTimerSt &= Dcm_Dsp_SID27_u4DelayTimerSt;
                if( u4_ChkDelayTimerSt == DCM_DSP_SID27_DTMR_STATUS_STOP )
                {
                    Dcm_Dsp_SID27_u1AttCntTmp[u1_Cnt] = (uint8)0U;
                    u1_WriteStorageFlag = DCM_DSP_SID27_WRITE_STORAGE_ON;
                }
            }
        }
    }
    if( u1_WriteStorageFlag == DCM_DSP_SID27_WRITE_STORAGE_ON )
    {
        Dcm_Dsp_SID27_WriteStorage();
    }
    Dcm_Dsp_SID27_bReadStorageCompleteFlag = (boolean)TRUE;

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID27_ClearReqSt                                 */
/* Description   | Clear request status                                     */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u1ErrorCode  :NRC to be sent if E_NOT_OK is returned */
/* Return Value  | void                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID27_ClearReqSt          /* MISRA DEVIATION */
(
    const Dcm_NegativeResponseCodeType u1ErrorCode  /* MISRA DEVIATION */
)
{
    Dcm_Dsp_SID27_u1MngStatus = DCM_DSP_SID27_NO_SEEDREQUEST;

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID27_ClearSeed                                  */
/* Description   | Clear the Seed information held by the user              */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u1SesCtrlTypeOld     :Old Security control type      */
/*               | [IN]u1SesCtrlTypeNew     :New Security control type      */
/* Return Value  | void                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE) Dcm_Dsp_SID27_ClearSeed            /* MISRA DEVIATION */
(
    const Dcm_SesCtrlType u1SesCtrlTypeOld,     /* MISRA DEVIATION */
    const Dcm_SesCtrlType u1SesCtrlTypeNew      /* MISRA DEVIATION */
)
{
    if( Dcm_Dsp_SID27_bSeedFlag == (boolean)TRUE )
    {
        Dcm_Dsp_SID27_u1MngStatus = DCM_DSP_SID27_NO_SEEDREQUEST;
        Dcm_Dsp_SID27_bSeedFlag = (boolean)FALSE;
    }  
    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID27_RequestSeed                                */
/* Description   | RequestSeed request processing                           */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u1SubFncId   :Sub Function                           */
/*               | [IN]u1OpStatus   :Operation Status                       */
/*               | [IN]ptMsgContext :Message Context                        */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                                                     */
/*               | DCM_E_PENDING                                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID27_RequestSeed /* MISRA DEVIATION */
(
    const uint8 u1SubFncId,
    const Dcm_OpStatusType u1OpStatus,
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;

    if( u1OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SID27_RSeedInitialProc( u1SubFncId, DCM_INITIAL, ptMsgContext );
    }
    else if( u1OpStatus == (Dcm_OpStatusType)DCM_CANCEL )
    {
        u1_RetVal = Dcm_Dsp_SID27_RSeedCancelProc( DCM_CANCEL );
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID27_SendKey                                    */
/* Description   | SendKey request processing                               */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u1SubFncId   :Sub Function                           */
/*               | [IN]u1OpStatus   :Operation Status                       */
/*               | [IN]ptMsgContext :Message Context                        */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                                                     */
/*               | DCM_E_PENDING                                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID27_SendKey     /* MISRA DEVIATION */
(
    const uint8 u1SubFncId,
    const Dcm_OpStatusType u1OpStatus,
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;

    if( u1OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SID27_SKeyInitialProc( u1SubFncId, DCM_INITIAL, ptMsgContext );
    }
    else if( u1OpStatus == (Dcm_OpStatusType)DCM_CANCEL )
    {
        u1_RetVal = Dcm_Dsp_SID27_SKeyCancelProc( DCM_CANCEL );
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID27_SetDataStorage2Mirror                      */
/* Description   | Storage to Mirror                                        */
/* Preconditions | None                                                     */
/* Parameters    |  [in] u2BlockIdx : Block Index                           */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID27_SetDataStorage2Mirror
(
    const uint16 u2BlockIdx
)
{
    uint16              u2_BIdxStaSec;
    uint16              u2_BIdxEndSec;
    uint8               u1_SecurityNum;
    uint8               u1_Cnt;

    u2_BIdxStaSec       = Dcm_Dsp_StorageMng_u2BIdx_StaSec;
    u2_BIdxEndSec       = Dcm_Dsp_StorageMng_u2BIdx_EndSec;
    u1_SecurityNum      = Dcm_Dsp_u1Security_N;
    
    if( ( u2_BIdxStaSec <= u2BlockIdx ) && ( u2BlockIdx <= u2_BIdxEndSec ) )
    {
        for ( u1_Cnt = (uint8)0U; u1_Cnt < u1_SecurityNum; u1_Cnt++ )
        {
            Dcm_Dsp_SID27_u1AttCntTmp[u1_Cnt] = Dcm_u1AttCnt[u1_Cnt];
        }
    }
    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID27_SetDataMirror2Storage                      */
/* Description   | Mirror to Storage                                        */
/* Preconditions | None                                                     */
/* Parameters    |  [in] u2BlockIdx : Block Index                           */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID27_SetDataMirror2Storage
(
    const uint16 u2BlockIdx
)
{
    uint16              u2_BIdxStaSec;
    uint16              u2_BIdxEndSec;
    uint8               u1_NvSecBlockLen;
    uint8               u1_Cnt;

    u2_BIdxStaSec       = Dcm_Dsp_StorageMng_u2BIdx_StaSec;
    u2_BIdxEndSec       = Dcm_Dsp_StorageMng_u2BIdx_EndSec;
    u1_NvSecBlockLen    = Dcm_Dsp_u1Nvsec_Block_Len;
    
    if( ( u2_BIdxStaSec <= u2BlockIdx ) && ( u2BlockIdx <= u2_BIdxEndSec ) )
    {
        for ( u1_Cnt = (uint8)0U; u1_Cnt < u1_NvSecBlockLen; u1_Cnt++ )
        {
            Dcm_u1AttCnt[u1_Cnt] = Dcm_Dsp_SID27_u1AttCntTmp[u1_Cnt];
        }
    }
    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID27_ReadConfirmation                           */
/* Description   | Read Storage Confirmation                                */
/* Preconditions | None                                                     */
/* Parameters    |  [in] u2BlockIdx : Block Index                           */
/*               |  [in] u1Result : Read Storage Result                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID27_ReadConfirmation
(
    const uint16 u2BlockIdx,         /* MISRA DEVIATION */
    const uint8  u1Result
)
{
    if( u1Result == (uint8)E_OK )
    {
        Dcm_Dsp_SID27_u1ReadStorageResult = E_OK;
    }
    else
    {
        Dcm_Dsp_SID27_u1ReadStorageResult = E_NOT_OK;
    }
    
    (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID27_READCONF );            /* no return check required */
    

    return;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID27_RSeedInitialProc                           */
/* Description   | Execute requestSeed processing                           */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u1SubFncId   :Sub Function                           */
/*               | [IN]u1OpStatus   :Operation Status                       */
/*               | [IN]ptMsgContext :Message Context                        */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                                                     */
/*               | DCM_E_PENDING                                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID27_RSeedInitialProc
(
    const uint8 u1SubFncId,
    const Dcm_OpStatusType u1OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    uint32                          u4_ADRSize;
    Std_ReturnType                  u1_RetVal;
    uint8                           u1_SecLevel;
    uint8                           u1_Cnt;
    uint8                           u1_NrcReqBeforeHistRead;
    uint8                           u1_SecurityNum;

    u1_RetVal               = E_OK;
    u1_NrcReqBeforeHistRead = Dcm_Dsp_u1Nrc_Req_Before_Hist_Read;
    u1_SecurityNum          = Dcm_Dsp_u1Security_N;
    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );
    Dcm_Dsp_Main_stMsgContext = *ptMsgContext;
    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    Dcm_Dsp_SID27_u1SecLvIndex = (uint8)0x00U;

    if( Dcm_Dsp_SID27_bReadStorageCompleteFlag != (boolean)FALSE )
    {
        u1_SecLevel = ( u1SubFncId + DCM_DSP_SID27_CALC_SEC_ADD_VAL ) >> DCM_DSP_SID27_CALC_SHIFT_VAL;
        for( u1_Cnt = (uint8)0U; u1_Cnt < u1_SecurityNum; u1_Cnt++ )
        {
            /* Judgment is always true on config settings */
            if( u1_SecLevel == Dcm_Dsp_SecurityParamTbl[u1_Cnt].u1Level )    /* MISRA DEVIATION */
            {
                Dcm_Dsp_SID27_u1SecLvIndex = u1_Cnt;
                break;
            }
        }
        if( Dcm_Dsp_SecurityNumTbl[Dcm_Dsp_SID27_u1SecLvIndex].bSecADRSizeFlag == (boolean)TRUE )    /* MISRA DEVIATION */
        {
            u4_ADRSize = Dcm_Dsp_SecurityParamTbl[Dcm_Dsp_SID27_u1SecLvIndex].u4ADRSize;
        }
        else
        {
            u4_ADRSize = (uint32)0UL;
        }
        if( Dcm_Dsp_Main_stMsgContext.reqDataLen == u4_ADRSize )
        {
            if( Dcm_Dsp_Main_stMsgContext.resMaxDataLen >= Dcm_Dsp_SecurityParamTbl[Dcm_Dsp_SID27_u1SecLvIndex].u4SeedSize )
            {
                u1_RetVal = Dcm_Dsp_SID27_GetSeedProc( u1_SecLevel, u1OpStatus );
            }
            else
            {
                Dcm_Dsp_SID27_u1MngStatus = DCM_DSP_SID27_NO_SEEDREQUEST;
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_RESPONSETOOLONG );        /* NRC 0x14 */
            }
        }
        else
        {
            Dcm_Dsp_SID27_u1MngStatus = DCM_DSP_SID27_NO_SEEDREQUEST;
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT );        /* NRC 0x13 */
        }
    }
    else
    {
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_NrcReqBeforeHistRead );                             /* NRC DcmDspSecurityNrcReqBeforeHistRead */
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID27_SKeyInitialProc                            */
/* Description   | Execute sendKey processing                               */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u1SubFncId   :Sub Function                           */
/*               | [IN]u1OpStatus   :Operation Status                       */
/*               | [IN]ptMsgContext :Message Context                        */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                                                     */
/*               | DCM_E_PENDING                                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID27_SKeyInitialProc
(
    const uint8 u1SubFncId,
    const Dcm_OpStatusType u1OpStatus,
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
)
{
    Std_ReturnType                  u1_RetVal;
    uint8                           u1_SecLevel;
    uint8                           u1_SecLvIndex;
    uint8                           u1_SecurityNum;

    u1_RetVal               = E_OK;
    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );
    Dcm_Dsp_Main_stMsgContext = *ptMsgContext;
    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    u1_SecLevel = ( u1SubFncId + DCM_DSP_SID27_CALC_SEC_ADD_VAL ) >> DCM_DSP_SID27_CALC_SHIFT_VAL;

    if( Dcm_Dsp_SID27_u1MngStatus == u1_SecLevel )
    {
        u1_SecLvIndex = Dcm_Dsp_SID27_u1SecLvIndex;
        u1_SecurityNum = Dcm_Dsp_u1Security_N;
        if( u1_SecLvIndex < u1_SecurityNum )
        {
            if( Dcm_Dsp_Main_stMsgContext.reqDataLen == Dcm_Dsp_SecurityParamTbl[u1_SecLvIndex].u4KeySize )
            {
                u1_RetVal = Dcm_Dsp_SID27_CompareKeyProc( u1_SecLevel, u1OpStatus );
            }
            else
            {
                Dcm_Dsp_SID27_u1MngStatus = DCM_DSP_SID27_NO_SEEDREQUEST;
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT );     /* NRC 0x13 */
            }
        }
        else
        {
            Dcm_Dsp_SID27_u1MngStatus = DCM_DSP_SID27_NO_SEEDREQUEST;
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_GENERALREJECT );                             /* NRC 0x10 */
        }
    }
    else if( Dcm_Dsp_SID27_u1MngStatus == DCM_DSP_SID27_NO_SEEDREQUEST )
    {
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTSEQUENCEERROR );                          /* NRC 0x24 */
    }
    else
    {
        Dcm_Dsp_SID27_u1MngStatus = DCM_DSP_SID27_NO_SEEDREQUEST;
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTSEQUENCEERROR );                          /* NRC 0x24 */
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID27_GetSeedProc                                */
/* Description   | Seed request processing                                  */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u1SecLevel   :Security Level                         */
/*               | [IN]u1OpStatus   :Operation Status                       */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                                                     */
/*               | DCM_E_PENDING                                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID27_GetSeedProc
(
    const uint8 u1SecLevel,
    const Dcm_OpStatusType u1OpStatus
)
{
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) pt_SecurityAccessDataRecord;
    uint32                          u4_SeedSize;
    uint32                          u4_Cnt;
    uint32                          u4_ChkDelayTimerSt;
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_RetCalloutFnc;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;
    uint8                           u1_CurrentSecurityLevel;
    uint8                           u1_SecurityNum;
    uint8                           u1_SecLvIndex;

    u1_RetVal                   = E_OK;
    u1_CurrentSecurityLevel     = DCM_SEC_LEV_LOCKED;
    u1_SecurityNum              = Dcm_Dsp_u1Security_N;
    u1_SecLvIndex               = Dcm_Dsp_SID27_u1SecLvIndex;

    if( u1_SecLvIndex < u1_SecurityNum )
    {
        u1_ErrorCode                = DCM_E_GENERALREJECT;
        pt_SecurityAccessDataRecord = Dcm_Dsp_Main_stMsgContext.reqData;
        u1_RetCalloutFnc = Dcm_Dsp_SID27_CallGetSeedCout( u1_SecLvIndex,
                                                          pt_SecurityAccessDataRecord,
                                                          u1OpStatus,
                                                          Dcm_Dsp_Main_stMsgContext.resData,
                                                          &u1_ErrorCode
                                                          );
        switch( u1_RetCalloutFnc )
        {
            case E_OK:
                Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
                Dcm_Dsp_SID27_bSeedFlag = (boolean)TRUE;
                u4_ChkDelayTimerSt = DCM_DSP_SID27_STATUS_1BIT << u1_SecLvIndex;
                u4_ChkDelayTimerSt &= Dcm_Dsp_SID27_u4DelayTimerSt;
                if( u4_ChkDelayTimerSt == DCM_DSP_SID27_DTMR_STATUS_STOP )
                {
                    (void)Dcm_GetSecurityLevel( &u1_CurrentSecurityLevel );                 /* no return check required */
                    u4_SeedSize = Dcm_Dsp_SecurityParamTbl[u1_SecLvIndex].u4SeedSize;
                    if( u1SecLevel != u1_CurrentSecurityLevel )
                    {
                        Dcm_Dsp_SID27_u1MngStatus = u1SecLevel;
                    }
                    else
                    {
                        for( u4_Cnt = (uint32)0UL; u4_Cnt < u4_SeedSize; u4_Cnt++ )
                        {
                            Dcm_Dsp_Main_stMsgContext.resData[u4_Cnt] = (uint8)0U;
                        }
                        Dcm_Dsp_SID27_u1MngStatus = DCM_DSP_SID27_NO_SEEDREQUEST;
                    }
                    Dcm_Dsp_Main_stMsgContext.resDataLen = u4_SeedSize;
                    Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
                }
                else
                {
                    Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUIREDTIMEDELAYNOTEXPIRED );                          /* NRC 0x37 */
                }
                break;
            case E_NOT_OK:
                Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
                Dcm_Dsp_SID27_u1MngStatus = DCM_DSP_SID27_NO_SEEDREQUEST;
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_ErrorCode );
                break;
            case DCM_E_PENDING:
                Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
                (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID27_GET_SEED );            /* no return check required */
                u1_RetVal = DCM_E_PENDING;
                break;
            default:
                Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
                Dcm_Dsp_SID27_u1MngStatus = DCM_DSP_SID27_NO_SEEDREQUEST;
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_GENERALREJECT );    /* NRC 0x10 */
                break;
        }
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID27_CompareKeyProc                             */
/* Description   | Key verification processing                              */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u1SecLevel   :Security Level                         */
/*               | [IN]u1OpStatus   :Operation Status                       */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                                                     */
/*               | DCM_E_PENDING                                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID27_CompareKeyProc
(
    const uint8 u1SecLevel,
    const Dcm_OpStatusType u1OpStatus
)
{
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_RetCompareKeyFnc;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;
    uint8                           u1_SecLvIndex;
    uint8                           u1_SecurityNum;

    u1_RetVal               = E_OK;
    u1_SecLvIndex           = Dcm_Dsp_SID27_u1SecLvIndex;
    u1_SecurityNum          = Dcm_Dsp_u1Security_N;

    if( u1_SecLvIndex < u1_SecurityNum )
    {
        u1_ErrorCode        = DCM_E_GENERALREJECT;
        u1_RetCompareKeyFnc = Dcm_Dsp_SID27_CallCompKeyCout( u1_SecLvIndex,
                                                             Dcm_Dsp_Main_stMsgContext.reqData,
                                                             u1OpStatus,
                                                             &u1_ErrorCode
                                                             );
        switch( u1_RetCompareKeyFnc )
        {
            case E_OK:
                Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
                Dcm_Dsp_SID27_u1AttCntTmp[u1_SecLvIndex] = (uint8)0U;
                Dcm_Dsp_SID27_WriteStorage();
                DslInternal_SetSecurityLevel( u1SecLevel );
                Dcm_Dsp_Main_stMsgContext.resDataLen = (uint32)0U;
                Dcm_Dsp_SID27_u1MngStatus = DCM_DSP_SID27_NO_SEEDREQUEST;
                Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
                break;
            case E_NOT_OK:
                Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
                Dcm_Dsp_SID27_u1MngStatus = DCM_DSP_SID27_NO_SEEDREQUEST;
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_ErrorCode );
                break;
            case DCM_E_PENDING:
                Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
                (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID27_COMPARE_KEY );         /* no return check required */
                u1_RetVal = DCM_E_PENDING;
                break;
            case DCM_E_COMPARE_KEY_FAILED:
                Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
                if( Dcm_Dsp_SID27_u1AttCntTmp[u1_SecLvIndex] < Dcm_Dsp_SecurityParamTbl[u1_SecLvIndex].u1NumAttDelay )
                {
                    Dcm_Dsp_SID27_u1AttCntTmp[u1_SecLvIndex] = (uint8)(Dcm_Dsp_SID27_u1AttCntTmp[u1_SecLvIndex] + (uint8)1U);
                }
                else
                {
                    Dcm_Dsp_SID27_u1AttCntTmp[u1_SecLvIndex] = Dcm_Dsp_SecurityParamTbl[u1_SecLvIndex].u1NumAttDelay;
                }
                Dcm_Dsp_SID27_WriteStorage();
                Dcm_Dsp_SID27_FailedKeyProc( );
                break;
            default:
                Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
                Dcm_Dsp_SID27_u1MngStatus = DCM_DSP_SID27_NO_SEEDREQUEST;
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_GENERALREJECT );        /* NRC 0x10 */
                break;
        }
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID27_FailedKeyProc                              */
/* Description   | Key verification processing Failed                       */
/* Preconditions | None                                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC (void, DCM_CODE ) Dcm_Dsp_SID27_FailedKeyProc
(
    void
)
{
    uint32                          u4_DelayTime;
    Dcm_NegativeResponseCodeType    u1_NrcMsg;
    uint8                           u1_SecLvIndex;
    uint8                           u1_SecurityNum;
    uint8                           u1_TimerId;

    u1_SecLvIndex   = Dcm_Dsp_SID27_u1SecLvIndex;
    u1_SecurityNum  = Dcm_Dsp_u1Security_N;

    if( u1_SecLvIndex < u1_SecurityNum )
    {
        if( Dcm_Dsp_SecurityParamTbl[u1_SecLvIndex].u1NumAttDelay == DCM_DSP_SID27_ATT_CNT_INVALID )
        {
            /* NRC 0x35 */
            u1_NrcMsg = DCM_E_INVALIDKEY;
        }
        else
        {
            if( Dcm_Dsp_SID27_u1AttCntTmp[u1_SecLvIndex] < Dcm_Dsp_SecurityParamTbl[u1_SecLvIndex].u1NumAttDelay )
            {
                /* NRC 0x35 */
                u1_NrcMsg = DCM_E_INVALIDKEY;
            }
            else
            {
                if( Dcm_Dsp_SecurityParamTbl[u1_SecLvIndex].u4DelayTime > DCM_DSP_SID27_DTMR_NOT_START )
                {
                    u1_TimerId = Dcm_Dsp_ConvertIdTbl[u1_SecLvIndex].u1TimerId;
                    u4_DelayTime = Dcm_Dsp_SecurityParamTbl[u1_SecLvIndex].u4DelayTime;
                    Dcm_Main_TmrSrv_StartTimer( u1_TimerId, u4_DelayTime );
                    Dcm_Dsp_SID27_SetDelayTimerSt( u1_SecLvIndex, DCM_DSP_SID27_DTMR_START );
                }
                /* NRC 0x36 */
                u1_NrcMsg = DCM_E_EXCEEDNUMBEROFATTEMPTS;
            }
        }
        Dcm_Dsp_SID27_u1MngStatus = DCM_DSP_SID27_NO_SEEDREQUEST;
        /* NRC 0x35 or NRC 0x36 */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_NrcMsg );
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID27_RSeedCancelProc                            */
/* Description   | Seed request cancel processing                           */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u1OpStatus   :Operation Status                       */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID27_RSeedCancelProc
(
    const Dcm_OpStatusType u1OpStatus
)
{
    uint8                           u1_SecurityAccessDataRecord;
    uint8                           u1_Seed;
    uint8                           u1_SecLvIndex;
    uint8                           u1_SecurityNum;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;
    boolean                         b_UserNotifyFlag;

    u1_SecurityAccessDataRecord = (uint8)0U;
    u1_ErrorCode                = DCM_E_GENERALREJECT;
    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID27_GET_SEED, (boolean)FALSE );      /* no return check required */
    b_UserNotifyFlag = Dcm_Dsp_Main_GetUserNotifyFlag();

    if( b_UserNotifyFlag == (boolean)TRUE )
    {
        u1_SecLvIndex               = Dcm_Dsp_SID27_u1SecLvIndex;
        u1_SecurityNum              = Dcm_Dsp_u1Security_N;
        if ( u1_SecLvIndex < u1_SecurityNum )
        {
            (void)Dcm_Dsp_SID27_CallGetSeedCout( u1_SecLvIndex,
                                                 &u1_SecurityAccessDataRecord,
                                                 u1OpStatus,
                                                 &u1_Seed,
                                                 &u1_ErrorCode
                                                 );                                         /* no return check required */
        }
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    }
    Dcm_Dsp_SID27_u1MngStatus = DCM_DSP_SID27_NO_SEEDREQUEST;
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return E_OK;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID27_SKeyCancelProc                             */
/* Description   | Key verification cancel processing                       */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u1OpStatus   :Operation Status                       */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID27_SKeyCancelProc
(
    const Dcm_OpStatusType u1OpStatus
)
{
    uint8                           u1_Key;
    uint8                           u1_SecLvIndex;
    uint8                           u1_SecurityNum;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;
    boolean                         b_UserNotifyFlag;

    u1_Key          = (uint8)0U;
    u1_ErrorCode    = DCM_E_GENERALREJECT;
    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID27_COMPARE_KEY, (boolean)FALSE );   /* no return check required */
    b_UserNotifyFlag = Dcm_Dsp_Main_GetUserNotifyFlag();

    if( b_UserNotifyFlag == (boolean)TRUE )
    {
        u1_SecLvIndex   = Dcm_Dsp_SID27_u1SecLvIndex;
        u1_SecurityNum  = Dcm_Dsp_u1Security_N;
        if ( u1_SecLvIndex < u1_SecurityNum )
        {
            (void)Dcm_Dsp_SID27_CallCompKeyCout( u1_SecLvIndex,
                                                 &u1_Key,
                                                 u1OpStatus,
                                                 &u1_ErrorCode
                                                 );                                         /* no return check required */
        }
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    }
    Dcm_Dsp_SID27_u1MngStatus = DCM_DSP_SID27_NO_SEEDREQUEST;
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return E_OK;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID27_SetDelayTimerSt                            */
/* Description   | State setting of DelayTimer                              */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u1SecLevelIndex  :Index Number                       */
/*               | [IN]u1StatusId       :Status ID                          */
/* Return Value  | void                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID27_SetDelayTimerSt
(
    const uint8 u1SecLevelIndex,
    const uint8 u1StatusId
)
{
    uint32      u4_CompVal;
    uint32      u4_SetDelayTimerSt;
    uint8       u1_SecurityNum;
    
    u1_SecurityNum = Dcm_Dsp_u1Security_N;

    if( u1SecLevelIndex < u1_SecurityNum )
    {
        u4_CompVal = DCM_DSP_SID27_STATUS_1BIT << u1SecLevelIndex;
        if( u1StatusId == DCM_DSP_SID27_DTMR_START )
        {
            Dcm_Dsp_SID27_u4DelayTimerSt |= u4_CompVal;
        }
        else
        {
            u4_SetDelayTimerSt = ~u4_CompVal;
            Dcm_Dsp_SID27_u4DelayTimerSt &= u4_SetDelayTimerSt;
            if( Dcm_Dsp_SID27_bReadStorageCompleteFlag != (boolean)FALSE )
            {
                Dcm_Dsp_SID27_u1AttCntTmp[u1SecLevelIndex] = (uint8)0U;
                Dcm_Dsp_SID27_WriteStorage();
            }
        }
    }
    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID27_Init_Storage                               */
/* Description   | Init processing of SID27 Storage                         */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID27_Init_Storage
(
    void
)
{
    /* Set to False to wait for NvM to reflect */
    Dcm_Dsp_SID27_bReadStorageCompleteFlag = (boolean)FALSE;
    Dcm_Dsp_SID27_u1ReadStorageResult = E_NOT_OK;

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID27_WriteStorage                               */
/* Description   | Write data to StorageMng using BlockIdx.                 */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID27_WriteStorage
( 
    void
)
{
    uint16              u2_BlockIdx;

    u2_BlockIdx         = Dcm_Dsp_StorageMng_u2BIdx_StaSec;

    (void)Dcm_Dsp_StorageMng_EnQueue( u2_BlockIdx );

    return;
}


#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
#endif /* DCM_SEC_PECULIAR_TYPE_RED == STD_ON */
#endif /* DCM_SUPPORT_SID27 == STD_ON */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-0-0         :2019-07-29                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

