/* Dcm_Dsp_StorageMng_c(v5-3-0)                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_StorageMng/CODE                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_StorageMng.h>
#include <Dcm/Dcm_Dsp_StorageMng_Connector.h>
#include "../../Dsp/cfg/Dcm_Dsp_StorageMng_Cfg.h"
#include <Dcm/Dcm_Main_EvtDistr.h>
#include <Dcm/Dcm_Main_TmrSrv.h>

#if ( DCM_NVM_USE == STD_ON )
/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSP_STORAGEMNG_READALL_BLOCKID       ((uint16)0x0000U)    /* Block ID of NvM_ReadAll */
#define DCM_DSP_STORAGEMNG_BLOCKIDX_ALL          ((uint16)0xFFFFU)    /* Block IDX of NvM_ReadAll */

#define DCM_DSP_STORAGEMNG_RSTS_INITIAL          ((uint8)0x01U)
#define DCM_DSP_STORAGEMNG_RSTS_READALLWT        ((uint8)0x02U)
#define DCM_DSP_STORAGEMNG_RSTS_READBLKWT        ((uint8)0x04U)
#define DCM_DSP_STORAGEMNG_RSTS_READCOMPLETE     ((uint8)0x08U)

#define DCM_DSP_STORAGEMNG_WSTS_INITIAL          ((uint8)0x01U)
#define DCM_DSP_STORAGEMNG_WSTS_RETRYWT          ((uint8)0x02U)
#define DCM_DSP_STORAGEMNG_WSTS_WRITECMPWT       ((uint8)0x04U)

#define DCM_DSP_STORAGEMNG_BLOCKID_INVALID       ((uint16)0x0000U)

#define DCM_DSP_STORAGEMNG_QUEUE_TBL             (DCM_P_STORAGE_BLOCKID_NUM + (uint16)1U)

#define DCM_DSP_STORAGEMNG_FUNC_INVALID          ((uint8)0xFFU)

#define DCM_DSP_STORAGEMNG_READNOTCOMPLETE       ((uint32)0x00000000U)
#define DCM_DSP_STORAGEMNG_READCOMPLETE          ((uint32)0xA5A5A5A5U)

#define DCM_DSP_STORAGEMNG_WRITEINITIAL          ((uint32)0x00000000U)
#define DCM_DSP_STORAGEMNG_WRITENOTINITIAL       ((uint32)0xA5A5A5A5U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct{
    uint16       u2Count;
    uint16       u2WritePos;
    uint16       u2ReadPos;
}Dcm_Dsp_StorageMng_EvtInfoType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>
static FUNC( void, DCM_CODE ) Dcm_Dsp_StorageMng_ReadNvMbyAllProc
( void );
static FUNC( void, DCM_CODE ) Dcm_Dsp_StorageMng_ReadNvMbyBlockProc
( void );
static FUNC( void, DCM_CODE ) Dcm_Dsp_StorageMng_DeQueue
( void );
static FUNC( void, DCM_CODE ) Dcm_Dsp_StorageMng_WriteNvMbyBlockProc
( void );
static FUNC( void, DCM_CODE ) Dcm_Dsp_StorageMng_ReadNvMCompProc
(
    const uint16 u2BlockIdx
);
static FUNC( void, DCM_CODE ) Dcm_Dsp_StorageMng_ReadNvMFailProc
(
    const uint16 u2BlockIdx
);
static FUNC( void, DCM_CODE ) Dcm_Dsp_StorageMng_SetDataStorage2Mirror
(
    const uint16 u2BlockIdx
);
static FUNC( void, DCM_CODE ) Dcm_Dsp_StorageMng_SetDataMirror2Storage
(
    const uint16 u2BlockIdx
);
static FUNC( void, DCM_CODE ) Dcm_Dsp_StorageMng_Queue_DelDuplicate
(
    const uint16 u2BlockIdx
);

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>
static VAR( uint8, DCM_VAR_NO_INIT )    Dcm_Dsp_StorageMng_u1NvMReadStatus;
static VAR( uint8, DCM_VAR_NO_INIT )    Dcm_Dsp_StorageMng_u1NvMWriteStatus;

static VAR( uint8, DCM_VAR_NO_INIT )    Dcm_Dsp_StorageMng_u1WriteCnt;
static VAR( uint8, DCM_VAR_NO_INIT )    Dcm_Dsp_StorageMng_u1GetErrStsCnt;

static VAR( uint16, DCM_VAR_NO_INIT )   Dcm_Dsp_StorageMng_u2ReadIdx;
static VAR( uint16, DCM_VAR_NO_INIT )   Dcm_Dsp_StorageMng_u2WriteBlockId;

static VAR( Dcm_Dsp_StorageMng_EvtInfoType, DCM_VAR_NO_INIT )  Dcm_Dsp_StorageMng_stEvtInfo;
static VAR( uint16, DCM_VAR_NO_INIT )   Dcm_Dsp_StorageMng_u2EvtQueue[ DCM_DSP_STORAGEMNG_QUEUE_TBL ];

static VAR( uint32, DCM_VAR_NO_INIT )   Dcm_Dsp_StorageMng_u4NvMReadCompFlg;
static VAR( uint32, DCM_VAR_NO_INIT )   Dcm_Dsp_StorageMng_u4NvMWriteInitialFlg;

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
/* Function Name | Dcm_Dsp_StorageMng_Init                                  */
/* Description   | StorageMng initialization                                */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_StorageMng_Init
( void )
{
    uint32  u4_ReadAllFsTime;

    Dcm_Dsp_StorageMng_u1NvMReadStatus          = DCM_DSP_STORAGEMNG_RSTS_INITIAL;
    Dcm_Dsp_StorageMng_u1NvMWriteStatus         = DCM_DSP_STORAGEMNG_WSTS_INITIAL;

    Dcm_Dsp_StorageMng_u1GetErrStsCnt           = (uint8)0U;
    Dcm_Dsp_StorageMng_u1WriteCnt               = (uint8)0U;

    Dcm_Dsp_StorageMng_u2WriteBlockId           = DCM_DSP_STORAGEMNG_BLOCKID_INVALID;

    Dcm_Dsp_StorageMng_stEvtInfo.u2Count        = (uint16)0U;
    Dcm_Dsp_StorageMng_stEvtInfo.u2WritePos     = (uint16)0U;
    Dcm_Dsp_StorageMng_stEvtInfo.u2ReadPos      = (uint16)0U;

    Dcm_Dsp_StorageMng_u4NvMReadCompFlg         = DCM_DSP_STORAGEMNG_READNOTCOMPLETE;
    Dcm_Dsp_StorageMng_u4NvMWriteInitialFlg     = DCM_DSP_STORAGEMNG_WRITEINITIAL;

    /* ReadAll FailSafeTimer Start */
    u4_ReadAllFsTime = Dcm_Dsp_StorageMng_u4ReadAllFsTime;
    Dcm_Main_TmrSrv_StartTimer( DCM_M_TMRID_STORAGEMNG_READALLFS, u4_ReadAllFsTime );

    Dcm_Dsp_StorageMng_u1NvMReadStatus          = DCM_DSP_STORAGEMNG_RSTS_READALLWT;
    Dcm_Dsp_StorageMng_ReadNvMbyAllProc();

    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_StorageMng_Refresh                               */
/* Description   | StorageMng Refresh processing                            */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_StorageMng_Refresh
( void )
{
    uint32   u4_ReadCompFlag;
    uint32   u4_WriteInitFlag;
    P2VAR(volatile uint8,  AUTOMATIC, DCM_APPL_DATA) pt_NvMReadStatus;
    P2VAR(volatile uint32, AUTOMATIC, DCM_APPL_DATA) pt_ReadCompFlag;
    P2VAR(volatile uint8,  AUTOMATIC, DCM_APPL_DATA) pt_NvMWriteStatus;
    P2VAR(volatile uint32, AUTOMATIC, DCM_APPL_DATA) pt_WriteInitFlag;
    P2VAR(volatile uint16, AUTOMATIC, DCM_APPL_DATA) pt_WritePos;
    P2VAR(volatile uint16, AUTOMATIC, DCM_APPL_DATA) pt_ReadPos;
    P2VAR(volatile uint16, AUTOMATIC, DCM_APPL_DATA) pt_Count;
    uint16   u2_WritePos;
    uint16   u2_ReadPos;
    uint16   u2_Count;
    uint16   u2_CalcCount;
    uint8    u1_NvMReadStatus;
    uint8    u1_NvMWriteStatus;

    /* Data Refresh */
    pt_NvMReadStatus    = &Dcm_Dsp_StorageMng_u1NvMReadStatus;
    pt_ReadCompFlag     = &Dcm_Dsp_StorageMng_u4NvMReadCompFlg;
    pt_NvMWriteStatus   = &Dcm_Dsp_StorageMng_u1NvMWriteStatus;
    pt_WriteInitFlag    = &Dcm_Dsp_StorageMng_u4NvMWriteInitialFlg;
    pt_WritePos         = &Dcm_Dsp_StorageMng_stEvtInfo.u2WritePos;
    pt_ReadPos          = &Dcm_Dsp_StorageMng_stEvtInfo.u2ReadPos;
    pt_Count            = &Dcm_Dsp_StorageMng_stEvtInfo.u2Count;

    u1_NvMReadStatus    = *pt_NvMReadStatus;
    u4_ReadCompFlag     = *pt_ReadCompFlag;
    u1_NvMWriteStatus   = *pt_NvMWriteStatus;
    u4_WriteInitFlag    = *pt_WriteInitFlag;
    u2_WritePos         = *pt_WritePos;
    u2_ReadPos          = *pt_ReadPos;
    u2_Count            = *pt_Count;

    *pt_NvMReadStatus   = u1_NvMReadStatus;
    *pt_ReadCompFlag    = u4_ReadCompFlag;
    *pt_NvMWriteStatus  = u1_NvMWriteStatus;
    *pt_WriteInitFlag   = u4_WriteInitFlag;
    *pt_WritePos        = u2_WritePos;
    *pt_ReadPos         = u2_ReadPos;
    *pt_Count           = u2_Count;

    /* Check ReadStatus and ReadCompFlag */
    if( u1_NvMReadStatus != DCM_DSP_STORAGEMNG_RSTS_READCOMPLETE )
    {
        if( u4_ReadCompFlag == DCM_DSP_STORAGEMNG_READCOMPLETE )
        {
            Dcm_Dsp_StorageMng_u1NvMReadStatus = DCM_DSP_STORAGEMNG_RSTS_READCOMPLETE;
        }
    }
    else /* DCM_DSP_STORAGEMNG_RSTS_READCOMPLETE */
    {
        Dcm_Dsp_StorageMng_u4NvMReadCompFlg = DCM_DSP_STORAGEMNG_READCOMPLETE;
    }

    /* Check WriteStatus and WriteInitialFlag */
    if( u1_NvMWriteStatus != DCM_DSP_STORAGEMNG_WSTS_INITIAL )
    {
        if( u4_WriteInitFlag == DCM_DSP_STORAGEMNG_WRITEINITIAL )
        {
            Dcm_Dsp_StorageMng_u1NvMWriteStatus = DCM_DSP_STORAGEMNG_WSTS_INITIAL;
        }
    }
    else /* DCM_DSP_STORAGEMNG_WSTS_INITIAL */
    {
        Dcm_Dsp_StorageMng_u4NvMWriteInitialFlg = DCM_DSP_STORAGEMNG_WRITEINITIAL;
    }

    /* Check if the relationship between u2WritePos and u2ReadPos and u2Count is broken */
    if( u2_WritePos >= u2_ReadPos )
    {
        u2_CalcCount = (uint16)(u2_WritePos - u2_ReadPos);
    }
    else
    {
        u2_CalcCount = (uint16)((Dcm_Dsp_StorageMng_u2Queue_Max + u2_WritePos) - u2_ReadPos);
    }
    if( u2_Count == u2_CalcCount )
    {
        /* No Proc because correct */
    }
    else
    {
        /* If the relationship is broken, initialize the data */
        Dcm_Dsp_StorageMng_u1NvMWriteStatus         = DCM_DSP_STORAGEMNG_WSTS_INITIAL;
        Dcm_Dsp_StorageMng_u4NvMWriteInitialFlg     = DCM_DSP_STORAGEMNG_WRITEINITIAL;
        Dcm_Dsp_StorageMng_u1GetErrStsCnt           = (uint8)0U;
        Dcm_Dsp_StorageMng_u1WriteCnt               = (uint8)0U;
        Dcm_Dsp_StorageMng_u2WriteBlockId           = DCM_DSP_STORAGEMNG_BLOCKID_INVALID;
        Dcm_Dsp_StorageMng_stEvtInfo.u2Count        = (uint16)0U;
        Dcm_Dsp_StorageMng_stEvtInfo.u2WritePos     = (uint16)0U;
        Dcm_Dsp_StorageMng_stEvtInfo.u2ReadPos      = (uint16)0U;

        (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_STORAGEMNG_WRITEGETSTS, (boolean)FALSE );  /* no return check required */
        (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_STORAGEMNG_WRITEDEQ,    (boolean)FALSE );  /* no return check required */
        (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_STORAGEMNG_WRITERETRY,  (boolean)FALSE );  /* no return check required */
        Dcm_Main_TmrSrv_StopTimer( DCM_M_TMRID_STORAGEMNG_WRITEFS );
    }

    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_StorageMng_ReReadAllCbk                          */
/* Description   | Callback function for event delivery registration of     */
/*               | ReadNvMbyAllProc                                         */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u1EventId        :Event ID                           */
/* Return Value  | void                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_StorageMng_ReReadAllCbk
(
    const uint8 u1EventId
)
{
    if( u1EventId == DCM_M_EVTID_STORAGEMNG_READALL )
    {
        if( Dcm_Dsp_StorageMng_u1NvMReadStatus == DCM_DSP_STORAGEMNG_RSTS_READALLWT )
        {
            Dcm_Dsp_StorageMng_ReadNvMbyAllProc();
        }

    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_StorageMng_ReReadBlockCbk                        */
/* Description   | Callback function for event delivery registration of     */
/*               | ReadNvMbyBlockProc                                       */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u1EventId        :Event ID                           */
/* Return Value  | void                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_StorageMng_ReReadBlockCbk
(
    const uint8 u1EventId
)
{
    if( u1EventId == DCM_M_EVTID_STORAGEMNG_READBLOCK )
    {
        if( Dcm_Dsp_StorageMng_u1NvMReadStatus == DCM_DSP_STORAGEMNG_RSTS_READBLKWT )
        {
            Dcm_Dsp_StorageMng_ReadNvMbyBlockProc();
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_StorageMng_ReReadBlockCbk                        */
/* Description   | Callback function for ReadAll FalesafeTimer              */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u1TimerId        :Timer ID                           */
/* Return Value  | void                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_StorageMng_ReadAllFsTOCbk
(
    const uint8 u1TimerId
)
{
    if( u1TimerId == DCM_M_TMRID_STORAGEMNG_READALLFS )
    {
        (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_STORAGEMNG_READALL, (boolean)FALSE );  /* no return check required */
        Dcm_Dsp_StorageMng_ReadNvMFailProc( DCM_DSP_STORAGEMNG_BLOCKIDX_ALL );
        Dcm_Dsp_StorageMng_u1NvMReadStatus = DCM_DSP_STORAGEMNG_RSTS_READCOMPLETE;
        Dcm_Dsp_StorageMng_u4NvMReadCompFlg = DCM_DSP_STORAGEMNG_READCOMPLETE;
        Dcm_Dsp_StorageMng_DeQueue();
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_StorageMng_EnQueue                               */
/* Description   | Enqueue block index to write                             */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u2BlockIdx   :Block index                            */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                                                     */
/*               | E_NOT_OK                                                 */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE) Dcm_Dsp_StorageMng_EnQueue
(
    const uint16 u2BlockIdx
)
{
    uint16            u2_BlockId_Num;
    uint16            u2_Queue_Max;
    Std_ReturnType    u1_RetVal;

    u1_RetVal = E_NOT_OK;
    u2_BlockId_Num = Dcm_Dsp_StorageMng_u2BlockId_Num;
    u2_Queue_Max = Dcm_Dsp_StorageMng_u2Queue_Max;

    if( u2BlockIdx <  u2_BlockId_Num )
    {
        /* Delete duplicate index */
        Dcm_Dsp_StorageMng_Queue_DelDuplicate( u2BlockIdx );

        /* Queue overflow check */
        if( Dcm_Dsp_StorageMng_stEvtInfo.u2Count < u2_Queue_Max )
        {
            /* Enqueue */
            u1_RetVal = E_OK;

            if( Dcm_Dsp_StorageMng_stEvtInfo.u2WritePos < u2_Queue_Max )
            {
                Dcm_Dsp_StorageMng_u2EvtQueue[ Dcm_Dsp_StorageMng_stEvtInfo.u2WritePos ] = u2BlockIdx;
            }

            /* Write position update */
            if( Dcm_Dsp_StorageMng_stEvtInfo.u2WritePos >= (uint16)(u2_Queue_Max - (uint16)1U) )
            {
                Dcm_Dsp_StorageMng_stEvtInfo.u2WritePos = (uint16)0U;
            }
            else
            {
                Dcm_Dsp_StorageMng_stEvtInfo.u2WritePos = (uint16)(Dcm_Dsp_StorageMng_stEvtInfo.u2WritePos + (uint16)1U);
            }
            Dcm_Dsp_StorageMng_stEvtInfo.u2Count = (uint16)(Dcm_Dsp_StorageMng_stEvtInfo.u2Count + (uint16)1U);

            /* Dequeue */
            Dcm_Dsp_StorageMng_DeQueue();
        }
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_StorageMng_GetErrorStsCbk                        */
/* Description   | Callback function for event delivery registration of     */
/*               | GetErrorSts                                              */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u1EventId        :Event ID                           */
/* Return Value  | void                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_StorageMng_GetErrorStsCbk
(
    const uint8 u1EventId
)
{

    Std_ReturnType              u1_RetGetErrStFnc;
    Dcm_NvM_RequestResultType   u1_ReqResult;
    uint8                       u1_GetErrRetry_Max;

    u1_GetErrRetry_Max = Dcm_Dsp_StorageMng_u1GetErrRetry_Max;

    if( u1EventId == DCM_M_EVTID_STORAGEMNG_WRITEGETSTS )
    {
        if( Dcm_Dsp_StorageMng_u1NvMWriteStatus == DCM_DSP_STORAGEMNG_WSTS_WRITECMPWT )
        {
            u1_ReqResult = DCM_NVM_REQ_NOT_OK;
            u1_RetGetErrStFnc = Dcm_Dsp_StorageMng_Cnct_NvMGetErrSt( Dcm_Dsp_StorageMng_u2WriteBlockId, &u1_ReqResult );

            if( u1_RetGetErrStFnc == (Std_ReturnType)E_OK )
            {
                switch( u1_ReqResult )
                {
                    case DCM_NVM_REQ_PENDING:
                        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_STORAGEMNG_WRITEGETSTS );  /* no return check required */
                        break;
                    case DCM_NVM_REQ_OK:
                    case DCM_NVM_REQ_BLOCK_SKIPPED:
                    case DCM_NVM_REQ_NOT_OK:
                    default:
                        Dcm_Dsp_StorageMng_u1GetErrStsCnt           = (uint8)0U;
                        Dcm_Main_TmrSrv_StopTimer( DCM_M_TMRID_STORAGEMNG_WRITEFS );
                        Dcm_Dsp_StorageMng_u1NvMWriteStatus         = DCM_DSP_STORAGEMNG_WSTS_INITIAL;
                        Dcm_Dsp_StorageMng_u4NvMWriteInitialFlg     = DCM_DSP_STORAGEMNG_WRITEINITIAL;
                        Dcm_Dsp_StorageMng_u2WriteBlockId           = DCM_DSP_STORAGEMNG_BLOCKID_INVALID;
                        Dcm_Dsp_StorageMng_DeQueue();
                        break;
                }
            }
            else
            {
                if( Dcm_Dsp_StorageMng_u1GetErrStsCnt < u1_GetErrRetry_Max )
                {
                    Dcm_Dsp_StorageMng_u1GetErrStsCnt = (uint8)(Dcm_Dsp_StorageMng_u1GetErrStsCnt + (uint8)1U);
                    (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_STORAGEMNG_WRITEGETSTS );  /* no return check required */
                }
                else
                {
                    Dcm_Main_TmrSrv_StopTimer( DCM_M_TMRID_STORAGEMNG_WRITEFS );
                    (void)Dcm_Dsp_StorageMng_Cnct_NvMCancelJob( Dcm_Dsp_StorageMng_u2WriteBlockId );  /* no return check required */
                    Dcm_Dsp_StorageMng_u1NvMWriteStatus         = DCM_DSP_STORAGEMNG_WSTS_INITIAL;
                    Dcm_Dsp_StorageMng_u4NvMWriteInitialFlg     = DCM_DSP_STORAGEMNG_WRITEINITIAL;
                    Dcm_Dsp_StorageMng_u2WriteBlockId           = DCM_DSP_STORAGEMNG_BLOCKID_INVALID;
                    Dcm_Dsp_StorageMng_u1GetErrStsCnt           = (uint8)0U;
                    (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_STORAGEMNG_WRITEDEQ );
                }
            }

        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_StorageMng_DeQueueCbk                            */
/* Description   | Callback function for event delivery registration of     */
/*               | DeQueue                                                  */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u1EventId        :Event ID                           */
/* Return Value  | void                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_StorageMng_DeQueueCbk
(
    const uint8 u1EventId
)
{
    if( u1EventId == DCM_M_EVTID_STORAGEMNG_WRITEDEQ )
    {
        Dcm_Dsp_StorageMng_DeQueue();
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_StorageMng_RewriteCbk                            */
/* Description   | Callback function for event delivery registration of     */
/*               | WriteBlockProc                                           */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u1EventId        :Event ID                           */
/* Return Value  | void                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_StorageMng_RewriteCbk
(
    const uint8 u1EventId
)
{
    if( u1EventId == DCM_M_EVTID_STORAGEMNG_WRITERETRY )
    {
        if( Dcm_Dsp_StorageMng_u1NvMWriteStatus == DCM_DSP_STORAGEMNG_WSTS_RETRYWT )
        {
            Dcm_Dsp_StorageMng_WriteNvMbyBlockProc();
        }
        else
        {
            Dcm_Dsp_StorageMng_u1NvMWriteStatus     = DCM_DSP_STORAGEMNG_WSTS_INITIAL;
            Dcm_Dsp_StorageMng_u4NvMWriteInitialFlg = DCM_DSP_STORAGEMNG_WRITEINITIAL;
            Dcm_Dsp_StorageMng_u2WriteBlockId       = DCM_DSP_STORAGEMNG_BLOCKID_INVALID;
            Dcm_Dsp_StorageMng_u1WriteCnt           = (uint8)0U;
            (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_STORAGEMNG_WRITEDEQ );  /* no return check required */
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_StorageMng_WriteBlFsTOCbk                        */
/* Description   | Callback function for WriteBL FalesafeTimer              */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u1TimerId        :Timer ID                           */
/* Return Value  | void                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_StorageMng_WriteBlFsTOCbk
(
    const uint8 u1TimerId
)
{
    if( u1TimerId == DCM_M_TMRID_STORAGEMNG_WRITEFS )
    {
        (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_STORAGEMNG_WRITEGETSTS, (boolean)FALSE );  /* no return check required */
        (void)Dcm_Dsp_StorageMng_Cnct_NvMCancelJob( Dcm_Dsp_StorageMng_u2WriteBlockId );  /* no return check required */
        Dcm_Dsp_StorageMng_u1NvMWriteStatus         = DCM_DSP_STORAGEMNG_WSTS_INITIAL;
        Dcm_Dsp_StorageMng_u4NvMWriteInitialFlg     = DCM_DSP_STORAGEMNG_WRITEINITIAL;
        Dcm_Dsp_StorageMng_u2WriteBlockId           = DCM_DSP_STORAGEMNG_BLOCKID_INVALID;
        Dcm_Dsp_StorageMng_u1GetErrStsCnt           = (uint8)0U;
        Dcm_Dsp_StorageMng_DeQueue();
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_StorageMng_GetSleepPermission                    */
/* Description   | Notify of sleep availability information of StorageMng.  */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : Sleep possible                            */
/*               |        FALSE : Sleep impossible                          */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( boolean, DCM_CODE ) Dcm_Dsp_StorageMng_GetSleepPermission
( void )
{
    boolean b_RetVal;

    b_RetVal = (boolean)TRUE;

    if( Dcm_Dsp_StorageMng_stEvtInfo.u2Count != (uint16)0U )
    {
        b_RetVal = (boolean)FALSE;
        
    }
    else
    {
        if( ( Dcm_Dsp_StorageMng_u1NvMWriteStatus == DCM_DSP_STORAGEMNG_WSTS_RETRYWT    ) ||
            ( Dcm_Dsp_StorageMng_u1NvMWriteStatus == DCM_DSP_STORAGEMNG_WSTS_WRITECMPWT ) )
        {
            b_RetVal = (boolean)FALSE;
         }
     }

    return b_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_StorageMng_PreWriteAll                           */
/* Description   | Preparatory process before writeall.                     */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_StorageMng_PreWriteAll
( void )
{
    uint16 u2_BlockIdx;
    uint16 u2_Queue_Max;

    u2_Queue_Max = Dcm_Dsp_StorageMng_u2Queue_Max;

    if( Dcm_Dsp_StorageMng_u1NvMReadStatus == DCM_DSP_STORAGEMNG_RSTS_READCOMPLETE )
    {
        if( Dcm_Dsp_StorageMng_stEvtInfo.u2ReadPos < u2_Queue_Max )
        {
            while( Dcm_Dsp_StorageMng_stEvtInfo.u2Count > (uint16)0U )
            {
                u2_BlockIdx = Dcm_Dsp_StorageMng_u2EvtQueue[ Dcm_Dsp_StorageMng_stEvtInfo.u2ReadPos ];

                /* Read position update */
                if( Dcm_Dsp_StorageMng_stEvtInfo.u2ReadPos >= (uint16)( u2_Queue_Max - (uint16)1U ) )
                {
                    Dcm_Dsp_StorageMng_stEvtInfo.u2ReadPos = (uint16)0U;
                }
                else
                {
                    Dcm_Dsp_StorageMng_stEvtInfo.u2ReadPos = (uint16)(Dcm_Dsp_StorageMng_stEvtInfo.u2ReadPos + (uint16)1U);
                }
                Dcm_Dsp_StorageMng_stEvtInfo.u2Count = (uint16)(Dcm_Dsp_StorageMng_stEvtInfo.u2Count - (uint16)1U);

                Dcm_Dsp_StorageMng_SetDataMirror2Storage( u2_BlockIdx );
            }
        }
    }

    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_STORAGEMNG_READALL,     (boolean)FALSE );  /* no return check required */
    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_STORAGEMNG_READBLOCK,   (boolean)FALSE );  /* no return check required */
    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_STORAGEMNG_WRITEGETSTS, (boolean)FALSE );  /* no return check required */
    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_STORAGEMNG_WRITEDEQ,    (boolean)FALSE );  /* no return check required */
    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_STORAGEMNG_WRITERETRY,  (boolean)FALSE );  /* no return check required */
    Dcm_Main_TmrSrv_StopTimer( DCM_M_TMRID_STORAGEMNG_READALLFS );
    Dcm_Main_TmrSrv_StopTimer( DCM_M_TMRID_STORAGEMNG_WRITEFS );

    Dcm_Dsp_StorageMng_u1NvMReadStatus      = DCM_DSP_STORAGEMNG_RSTS_INITIAL;
    Dcm_Dsp_StorageMng_u1NvMWriteStatus     = DCM_DSP_STORAGEMNG_WSTS_INITIAL;
    Dcm_Dsp_StorageMng_stEvtInfo.u2Count    = (uint16)0U;
    Dcm_Dsp_StorageMng_stEvtInfo.u2WritePos = (uint16)0U;
    Dcm_Dsp_StorageMng_stEvtInfo.u2ReadPos  = (uint16)0U;
    Dcm_Dsp_StorageMng_u4NvMReadCompFlg     = DCM_DSP_STORAGEMNG_READNOTCOMPLETE;
    Dcm_Dsp_StorageMng_u4NvMWriteInitialFlg = DCM_DSP_STORAGEMNG_WRITEINITIAL;

    return;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dcm_Dsp_StorageMng_ReadNvMbyAllProc                      */
/* Description   | Read all process                                         */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_StorageMng_ReadNvMbyAllProc
( void )
{

    Std_ReturnType              u1_RetGetErrStFnc;
    Dcm_NvM_RequestResultType   u1_ReqResult;
    uint8                       u1_GetErrRetry_Max;

    u1_GetErrRetry_Max = Dcm_Dsp_StorageMng_u1GetErrRetry_Max;

    u1_ReqResult = DCM_NVM_REQ_NOT_OK;
    u1_RetGetErrStFnc = Dcm_Dsp_StorageMng_Cnct_NvMGetErrSt( DCM_DSP_STORAGEMNG_READALL_BLOCKID, &u1_ReqResult );

    if( u1_RetGetErrStFnc == (Std_ReturnType)E_OK )
    {
        switch( u1_ReqResult )
        {
            case DCM_NVM_REQ_OK:
            case DCM_NVM_REQ_BLOCK_SKIPPED:
                Dcm_Dsp_StorageMng_u2ReadIdx = (uint16)0U;
                Dcm_Dsp_StorageMng_u1GetErrStsCnt = (uint8)0U;
                Dcm_Main_TmrSrv_StopTimer( DCM_M_TMRID_STORAGEMNG_READALLFS );
                Dcm_Dsp_StorageMng_u1NvMReadStatus = DCM_DSP_STORAGEMNG_RSTS_READBLKWT;
                Dcm_Dsp_StorageMng_ReadNvMbyBlockProc();
                break;

            case DCM_NVM_REQ_PENDING:
                (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_STORAGEMNG_READALL );            /* no return check required */
                break;

            case DCM_NVM_REQ_NOT_OK:
            default:
                Dcm_Dsp_StorageMng_u1GetErrStsCnt = (uint8)0U;
                Dcm_Main_TmrSrv_StopTimer( DCM_M_TMRID_STORAGEMNG_READALLFS );
                Dcm_Dsp_StorageMng_ReadNvMFailProc( DCM_DSP_STORAGEMNG_BLOCKIDX_ALL );
                Dcm_Dsp_StorageMng_u1NvMReadStatus = DCM_DSP_STORAGEMNG_RSTS_READCOMPLETE;
                Dcm_Dsp_StorageMng_u4NvMReadCompFlg = DCM_DSP_STORAGEMNG_READCOMPLETE;
                Dcm_Dsp_StorageMng_DeQueue();
                break;
        }
    }
    else
    {
        if( Dcm_Dsp_StorageMng_u1GetErrStsCnt < u1_GetErrRetry_Max )
        {
            Dcm_Dsp_StorageMng_u1GetErrStsCnt = (uint8)(Dcm_Dsp_StorageMng_u1GetErrStsCnt + (uint8)1U);
            (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_STORAGEMNG_READALL );            /* no return check required */
        }
        else
        {
            Dcm_Main_TmrSrv_StopTimer( DCM_M_TMRID_STORAGEMNG_READALLFS );
            Dcm_Dsp_StorageMng_ReadNvMFailProc( DCM_DSP_STORAGEMNG_BLOCKIDX_ALL );
            Dcm_Dsp_StorageMng_u1GetErrStsCnt = (uint8)0U;
            Dcm_Dsp_StorageMng_u1NvMReadStatus = DCM_DSP_STORAGEMNG_RSTS_READCOMPLETE;
            Dcm_Dsp_StorageMng_u4NvMReadCompFlg = DCM_DSP_STORAGEMNG_READCOMPLETE;
            Dcm_Dsp_StorageMng_DeQueue();
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_StorageMng_ReadNvMbyBlockProc                    */
/* Description   | Read block process                                       */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_StorageMng_ReadNvMbyBlockProc
( void )
{

    uint16                      u2_ReadIdx;
    uint16                      u2_PerCycleCnt;
    uint16                      u2_BlockId_Num;
    uint16                      u2_BlockId;
    uint16                      u2_IdNum_PerCycle;
    uint8                       u1_BlockResult;
    Std_ReturnType              u1_RetGetErrStFnc;
    Dcm_NvM_RequestResultType   u1_ReqResult;
    uint8                       u1_FailFuncIdx;
    uint8                       u1_GetErrRetry_Max;
    boolean                     b_SendEvent;

    u2_ReadIdx     = Dcm_Dsp_StorageMng_u2ReadIdx;
    u2_PerCycleCnt = (uint16)0U;
    u1_FailFuncIdx = DCM_DSP_STORAGEMNG_FUNC_INVALID;
    u2_BlockId_Num = Dcm_Dsp_StorageMng_u2BlockId_Num;
    u1_GetErrRetry_Max = Dcm_Dsp_StorageMng_u1GetErrRetry_Max;
    u2_IdNum_PerCycle  = Dcm_Dsp_StorageMng_u2IdNum_PerCycle;
    b_SendEvent    = (boolean)FALSE;

    for( ; u2_ReadIdx < u2_BlockId_Num; u2_ReadIdx++ )
    {
        if( Dcm_Dsp_StorageMng_stBlockList[u2_ReadIdx].u1FuncIdx != u1_FailFuncIdx )
        {
            u1_FailFuncIdx = DCM_DSP_STORAGEMNG_FUNC_INVALID;

            if( u2_PerCycleCnt >= u2_IdNum_PerCycle )
            {
                Dcm_Dsp_StorageMng_u2ReadIdx = u2_ReadIdx;
                (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_STORAGEMNG_READBLOCK );            /* no return check required */
                b_SendEvent = (boolean)TRUE;
            }
            else
            {
                u2_PerCycleCnt = (uint16)(u2_PerCycleCnt + (uint16)1U);

                u1_BlockResult = E_NOT_OK;

                u1_ReqResult = DCM_NVM_REQ_NOT_OK;
                u2_BlockId = Dcm_Dsp_StorageMng_stBlockList[u2_ReadIdx].u2BlockId;
                u1_RetGetErrStFnc = Dcm_Dsp_StorageMng_Cnct_NvMGetErrSt( u2_BlockId, &u1_ReqResult );

                if( u1_RetGetErrStFnc == (Std_ReturnType)E_OK )
                {
                    switch( u1_ReqResult )
                    {
                        case DCM_NVM_REQ_OK:
                        case DCM_NVM_REQ_BLOCK_SKIPPED:
                            u1_BlockResult = E_OK;
                            Dcm_Dsp_StorageMng_u1GetErrStsCnt = (uint8)0U;
                            Dcm_Dsp_StorageMng_SetDataStorage2Mirror( u2_ReadIdx );
                            break;

                        case DCM_NVM_REQ_PENDING:
                        case DCM_NVM_REQ_NOT_OK:
                        default:
                            /* No process */
                            break;
                    }
                }
                else
                {
                    if( Dcm_Dsp_StorageMng_u1GetErrStsCnt < u1_GetErrRetry_Max )
                    {
                        Dcm_Dsp_StorageMng_u2ReadIdx = u2_ReadIdx;
                        Dcm_Dsp_StorageMng_u1GetErrStsCnt = (uint8)(Dcm_Dsp_StorageMng_u1GetErrStsCnt + (uint8)1U);
                        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_STORAGEMNG_READBLOCK );            /* no return check required */
                        b_SendEvent = (boolean)TRUE;
                    }
                    else
                    {
                        Dcm_Dsp_StorageMng_u1GetErrStsCnt = (uint8)0U;
                    }
                }
                if( b_SendEvent == (boolean)FALSE )
                {
                    if( u1_BlockResult == (Std_ReturnType)E_OK )
                    {
                        Dcm_Dsp_StorageMng_ReadNvMCompProc( u2_ReadIdx );
                    }
                    else  /* E_NOT_OK */
                    {
                        Dcm_Dsp_StorageMng_ReadNvMFailProc( u2_ReadIdx );

                        /* Skip fail function */
                        u1_FailFuncIdx = Dcm_Dsp_StorageMng_stBlockList[u2_ReadIdx].u1FuncIdx;
                    }
                }
            }
            if( b_SendEvent == (boolean)TRUE )
            {
                break;
            }
        }
    }

    if( u2_ReadIdx >= u2_BlockId_Num )
    {
        Dcm_Dsp_StorageMng_u1GetErrStsCnt = (uint8)0U;
        Dcm_Dsp_StorageMng_u1NvMReadStatus = DCM_DSP_STORAGEMNG_RSTS_READCOMPLETE;
        Dcm_Dsp_StorageMng_u4NvMReadCompFlg = DCM_DSP_STORAGEMNG_READCOMPLETE;
        Dcm_Dsp_StorageMng_DeQueue();
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_StorageMng_DeQueue                               */
/* Description   | Dequeue block index and start writing                    */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_StorageMng_DeQueue
( void )
{

    uint16         u2_BlockIdx;
    uint16         u2_Queue_Max;
    uint16         u2_BlockId_Num;

    u2_Queue_Max = Dcm_Dsp_StorageMng_u2Queue_Max;
    u2_BlockId_Num = Dcm_Dsp_StorageMng_u2BlockId_Num;

    if( Dcm_Dsp_StorageMng_u1NvMReadStatus == DCM_DSP_STORAGEMNG_RSTS_READCOMPLETE )
    {
        if( Dcm_Dsp_StorageMng_stEvtInfo.u2ReadPos < u2_Queue_Max )
        {
            if( Dcm_Dsp_StorageMng_stEvtInfo.u2Count > (uint16)0U )
            {
                if( Dcm_Dsp_StorageMng_u1NvMWriteStatus == DCM_DSP_STORAGEMNG_WSTS_INITIAL )
                {
                    u2_BlockIdx = Dcm_Dsp_StorageMng_u2EvtQueue[ Dcm_Dsp_StorageMng_stEvtInfo.u2ReadPos ];
                    if( u2_BlockIdx < u2_BlockId_Num )
                    {
                        /* Read position update */
                        if( Dcm_Dsp_StorageMng_stEvtInfo.u2ReadPos >= (uint16)( u2_Queue_Max - (uint16)1U ) )
                        {
                            Dcm_Dsp_StorageMng_stEvtInfo.u2ReadPos = (uint16)0U;
                        }
                        else
                        {
                            Dcm_Dsp_StorageMng_stEvtInfo.u2ReadPos = (uint16)(Dcm_Dsp_StorageMng_stEvtInfo.u2ReadPos + (uint16)1U);
                        }
                        Dcm_Dsp_StorageMng_stEvtInfo.u2Count = (uint16)(Dcm_Dsp_StorageMng_stEvtInfo.u2Count - (uint16)1U);

                        Dcm_Dsp_StorageMng_SetDataMirror2Storage( u2_BlockIdx );
                        Dcm_Dsp_StorageMng_u2WriteBlockId = Dcm_Dsp_StorageMng_stBlockList[u2_BlockIdx].u2BlockId;
                        Dcm_Dsp_StorageMng_u1WriteCnt = (uint8)0U;
                        Dcm_Dsp_StorageMng_WriteNvMbyBlockProc();
                    }
                }
            }
        }
    }

    return;
}
/****************************************************************************/
/* Function Name | Dcm_Dsp_StorageMng_WriteNvMbyBlockProc                   */
/* Description   | Write block process                                      */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_StorageMng_WriteNvMbyBlockProc
( void )
{
    uint32            u4_SingleBlockFsTime;
    Std_ReturnType    u1_RetWriteBLFnc;
    uint8             u1_WriteRetry_Max;

    u1_WriteRetry_Max = Dcm_Dsp_StorageMng_u1WriteRetry_Max;

    u1_RetWriteBLFnc = Dcm_Dsp_StorageMng_Cnct_NvMWriteBL( Dcm_Dsp_StorageMng_u2WriteBlockId );

    if( u1_RetWriteBLFnc == (Std_ReturnType)E_OK )
    {
        Dcm_Dsp_StorageMng_u1NvMWriteStatus         = DCM_DSP_STORAGEMNG_WSTS_WRITECMPWT;
        Dcm_Dsp_StorageMng_u4NvMWriteInitialFlg     = DCM_DSP_STORAGEMNG_WRITENOTINITIAL;
        Dcm_Dsp_StorageMng_u1WriteCnt               = (uint8)0U;
        Dcm_Dsp_StorageMng_u1GetErrStsCnt           = (uint8)0U;
        /* WriteBl FailSafeTimer Start */
        u4_SingleBlockFsTime = Dcm_Dsp_StorageMng_u4SingleBlockFsTime;
        Dcm_Main_TmrSrv_StartTimer( DCM_M_TMRID_STORAGEMNG_WRITEFS, u4_SingleBlockFsTime );
        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_STORAGEMNG_WRITEGETSTS );  /* no return check required */
    }
    else
    {
        if( Dcm_Dsp_StorageMng_u1WriteCnt < u1_WriteRetry_Max )
        {
            Dcm_Dsp_StorageMng_u1WriteCnt = (uint8)(Dcm_Dsp_StorageMng_u1WriteCnt + (uint8)1U);
            Dcm_Dsp_StorageMng_u1NvMWriteStatus = DCM_DSP_STORAGEMNG_WSTS_RETRYWT;
            Dcm_Dsp_StorageMng_u4NvMWriteInitialFlg = DCM_DSP_STORAGEMNG_WRITENOTINITIAL;
            (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_STORAGEMNG_WRITERETRY );  /* no return check required */
        }
        else
        {
            Dcm_Dsp_StorageMng_u1NvMWriteStatus   = DCM_DSP_STORAGEMNG_WSTS_INITIAL;
            Dcm_Dsp_StorageMng_u4NvMWriteInitialFlg = DCM_DSP_STORAGEMNG_WRITEINITIAL;
            Dcm_Dsp_StorageMng_u2WriteBlockId     = DCM_DSP_STORAGEMNG_BLOCKID_INVALID;
            Dcm_Dsp_StorageMng_u1WriteCnt         = (uint8)0U;
            (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_STORAGEMNG_WRITEDEQ );  /* no return check required */
        }
    }
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_StorageMng_ReadNvMCompProc                       */
/* Description   | Read complete process                                    */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_StorageMng_ReadNvMCompProc
(
    const uint16 u2BlockIdx
)
{
    uint16   u2_BlockId_Num;
    uint8    u1_FuncIdx;

    u2_BlockId_Num = Dcm_Dsp_StorageMng_u2BlockId_Num;

    if( u2BlockIdx < u2_BlockId_Num )
    {
        if( ( (u2BlockIdx + (uint16)1U) == u2_BlockId_Num ) ||
            ( Dcm_Dsp_StorageMng_stBlockList[u2BlockIdx].u1FuncIdx !=
                  Dcm_Dsp_StorageMng_stBlockList[u2BlockIdx + (uint16)1U].u1FuncIdx ) )
        {
            u1_FuncIdx = Dcm_Dsp_StorageMng_stBlockList[u2BlockIdx].u1FuncIdx;
            if( Dcm_Dsp_StorageMng_stFuncList[u1_FuncIdx].ptReadComfFunc !=  NULL_PTR )
            {
#ifndef JGXSTACK
                Dcm_Dsp_StorageMng_stFuncList[u1_FuncIdx].ptReadComfFunc( u2BlockIdx, E_OK );
#else /* JGXSTACK */
                Dcm_Stack_StorageReadComfFunc( u2BlockIdx, E_OK );
#endif /* JGXSTACK */
            }
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_StorageMng_ReadNvMFailProc                       */
/* Description   | Read failure process                                     */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_StorageMng_ReadNvMFailProc
(
    const uint16 u2BlockIdx
)
{
    uint16   u2_BlockId_Num;
    uint8    u1_FuncIdx;
    uint8    u1_FuncList_Num;

    u2_BlockId_Num = Dcm_Dsp_StorageMng_u2BlockId_Num;
    u1_FuncList_Num = Dcm_Dsp_StorageMng_u1FuncList_Num;

    if( u2BlockIdx == DCM_DSP_STORAGEMNG_BLOCKIDX_ALL )
    {
        for( u1_FuncIdx = (uint8)0U; u1_FuncIdx < u1_FuncList_Num; u1_FuncIdx++ )
        {
            if( Dcm_Dsp_StorageMng_stFuncList[u1_FuncIdx].ptReadComfFunc !=  NULL_PTR )
            {
#ifndef JGXSTACK
                Dcm_Dsp_StorageMng_stFuncList[u1_FuncIdx].ptReadComfFunc( u2BlockIdx, E_NOT_OK );
#else /* JGXSTACK */
                Dcm_Stack_StorageReadComfFunc( u2BlockIdx, E_NOT_OK );
#endif /* JGXSTACK */
            }
        }
    }
    else if( u2BlockIdx < u2_BlockId_Num )
    {
        u1_FuncIdx = Dcm_Dsp_StorageMng_stBlockList[u2BlockIdx].u1FuncIdx;
        if( Dcm_Dsp_StorageMng_stFuncList[u1_FuncIdx].ptReadComfFunc !=  NULL_PTR )
        {
#ifndef JGXSTACK
            Dcm_Dsp_StorageMng_stFuncList[u1_FuncIdx].ptReadComfFunc( u2BlockIdx, E_NOT_OK );
#else /* JGXSTACK */
                Dcm_Stack_StorageReadComfFunc( u2BlockIdx, E_NOT_OK );
#endif /* JGXSTACK */
        }
    }
    else
    {
        /* no process */
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_StorageMng_SetDataStorage2Mirror                 */
/* Description   | Set data from storeage to mirror                         */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u2BlockIdx   :Block index                            */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_StorageMng_SetDataStorage2Mirror
(
    const uint16 u2BlockIdx
)
{
    uint16   u2_BlockId_Num;
    uint8    u1_FuncIdx;

    u2_BlockId_Num = Dcm_Dsp_StorageMng_u2BlockId_Num;

    if( u2BlockIdx < u2_BlockId_Num )
    {
        u1_FuncIdx = Dcm_Dsp_StorageMng_stBlockList[u2BlockIdx].u1FuncIdx;
        if( Dcm_Dsp_StorageMng_stFuncList[u1_FuncIdx].ptSetDataS2MFunc !=  NULL_PTR )
        {
#ifndef JGXSTACK
            Dcm_Dsp_StorageMng_stFuncList[u1_FuncIdx].ptSetDataS2MFunc( u2BlockIdx );
#else /* JGXSTACK */
                Dcm_Stack_StorageSetDataS2MFunc( u2BlockIdx );
#endif /* JGXSTACK */
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_StorageMng_SetDataMirror2Storage                 */
/* Description   | Set data from mirror to storeage                         */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u2BlockIdx   :Block index                            */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_StorageMng_SetDataMirror2Storage
(
    const uint16 u2BlockIdx
)
{
    uint16   u2_BlockId_Num;
    uint8    u1_FuncIdx;

    u2_BlockId_Num = Dcm_Dsp_StorageMng_u2BlockId_Num;

    if( u2BlockIdx < u2_BlockId_Num )
    {
        u1_FuncIdx = Dcm_Dsp_StorageMng_stBlockList[u2BlockIdx].u1FuncIdx;
        if( Dcm_Dsp_StorageMng_stFuncList[u1_FuncIdx].ptSetDataM2SFunc !=  NULL_PTR )
        {
#ifndef JGXSTACK
            Dcm_Dsp_StorageMng_stFuncList[u1_FuncIdx].ptSetDataM2SFunc( u2BlockIdx );
#else /* JGXSTACK */
                Dcm_Stack_StorageSetDataM2SFunc( u2BlockIdx );
#endif /* JGXSTACK */
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_StorageMng_Queue_DelDuplicate                    */
/* Description   | Delete duplicate index from queue                        */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u2BlockIdx   :Block index                            */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_StorageMng_Queue_DelDuplicate
(
    const uint16 u2BlockIdx
)
{
    uint16            u2_ReadPos;
    uint16            u2_QueCnt;
    uint16            u2_Queue_Max;
    boolean           b_DuplFlag;

    b_DuplFlag = (boolean)FALSE;
    u2_ReadPos = Dcm_Dsp_StorageMng_stEvtInfo.u2ReadPos;
    u2_Queue_Max = Dcm_Dsp_StorageMng_u2Queue_Max;

    if( u2_ReadPos < u2_Queue_Max )
    {
        for( u2_QueCnt = (uint16)0U; u2_QueCnt < Dcm_Dsp_StorageMng_stEvtInfo.u2Count; u2_QueCnt++ )
        {
            if( b_DuplFlag == (boolean)FALSE )
            {
                if( Dcm_Dsp_StorageMng_u2EvtQueue[u2_ReadPos] == u2BlockIdx )
                {
                    b_DuplFlag = (boolean)TRUE;
                }
            }
            else
            {
                /* Copy to previous position */
                if( u2_ReadPos > (uint16)0U )
                {
                    Dcm_Dsp_StorageMng_u2EvtQueue[u2_ReadPos - (uint16)1U] = Dcm_Dsp_StorageMng_u2EvtQueue[u2_ReadPos];
                }
                else
                {
                    Dcm_Dsp_StorageMng_u2EvtQueue[u2_Queue_Max - (uint16)1U] = Dcm_Dsp_StorageMng_u2EvtQueue[u2_ReadPos];
                }
            }

            /* Read position update */
            if( u2_ReadPos >= (uint16)( u2_Queue_Max - (uint16)1U ) )
            {
                u2_ReadPos = (uint16)0U;
            }
            else
            {
                u2_ReadPos = (uint16)(u2_ReadPos + (uint16)1U);
            }
        }

        if( b_DuplFlag == (boolean)TRUE )
        {
            /* Write position update */
            if( Dcm_Dsp_StorageMng_stEvtInfo.u2WritePos == (uint16)0U )
            {
                Dcm_Dsp_StorageMng_stEvtInfo.u2WritePos = (uint16)(u2_Queue_Max - (uint16)1U);
            }
            else
            {
                Dcm_Dsp_StorageMng_stEvtInfo.u2WritePos = (uint16)(Dcm_Dsp_StorageMng_stEvtInfo.u2WritePos - (uint16)1U);
            }
            Dcm_Dsp_StorageMng_stEvtInfo.u2Count = (uint16)(Dcm_Dsp_StorageMng_stEvtInfo.u2Count - (uint16)1U);
        }
    }

    return;
}

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

#endif
/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
