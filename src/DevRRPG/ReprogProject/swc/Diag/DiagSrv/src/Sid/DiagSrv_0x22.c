/* DiagSrv_0x22_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagSrv/0x22/CODE                                           */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <DiagLib.h>
#include <DiagSrv.h>

#include <RpgLib.h>
#include <Rte.h>
#include <ReprogOpt.h>

#include "DiagSrv_lib_Cfg.h"
#include "DiagSrv_0x22.h"
#include "DiagSrv_0x22_Cfg.h"
#include "DiagSrv_Local.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/* DID */
#define DIAGSRV_0X22_DID_NONCE                      ((uint16)0xF050U)
#define DIAGSRV_0X22_DID_FINGERPRINT_0              ((uint16)0xF120U)
#define DIAGSRV_0X22_DID_FINGERPRINT_31             ((uint16)0xF13FU)
#define DIAGSRV_0X22_DID_SESSION                    ((uint16)0xF186U)
#define DIAGSRV_0X22_DID_SOFTWARENUMBER             ((uint16)0xF188U)

/* Data Length */
#define DIAGSRV_0X22_SID_LEN                        ((uint8)1U)
#define DIAGSRV_0X22_DID_LEN                        ((uint8)2U)
#if (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON)
#define DIAGSRV_0X22_SUBM_REQDATA_SIZE              (DIAG_DIDMSG_MIN_SIZE)
#define DIAGSRV_0x22_SUBM_RSPDATA_SIZE              (DIAG_DIDMSG_MIN_SIZE + DIAGSRV_CFG_FINGERPRINT_SIZE)
#endif
#define DIAGSRV_0X22_DID_NONCE_LENGTH               (sizeof(DiagSrv_0x22_NonceData) / sizeof(DiagSrv_0x22_NonceData[0]))
#define DIAGSRV_0X22_DID_SOFTWARENUMBER_LENGTH      (sizeof(DiagSrv_0x22_SoftwareNumberData) / sizeof(DiagSrv_0x22_SoftwareNumberData[0]))

/* Message Parameter Position */
#define DIAGSRV_0X22_DID_H_POS                      ((uint8)1U)
#if (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON)
#define DIAGSRV_0X22_DID_L_POS                      ((uint8)2U)
#endif

/* Message Check */
#define DIAGSRV_0X22_MSG_LEN_LOW_MASK               ((uint16)0x0001U)
#define DIAGSRV_0X22_MSG_LEN_ODD                    ((uint16)0x0001U)

/* Job state */
#define DIAGSRV_0X22_STAT_IDLE                      ((uint8)0x01U)
#define DIAGSRV_0X22_STAT_DID_PROCESSING            ((uint8)0x02U)
#define DIAGSRV_0X22_STAT_WAIT_READ_FINGER          ((uint8)0x03U)
#define DIAGSRV_0X22_STAT_WAIT_READ_USR_DID         ((uint8)0x04U)
#if (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON)
#define DIAGSRV_0X22_STAT_SUBM_WAIT_READ_FINGER     ((uint8)0x05U)
#endif

/* Other */
#define DIAGSRV_0X22_MASK_DID_TO_REWRITEAREANUM     ((uint16)0x001FU)
#define DIAGSRV_0X22_DID_LOW_MASK                   ((uint16)0x00FFU)
#define DIAGSRV_0X22_BIT_SHIFT_8                    ((uint8)8U)
#define DIAGSRV_0X22_FINGER_INVALID                 ((uint8)0xFFU)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef struct {
    uint16 Did[DIAGSRV_CFG_0X22_MULTIPLE_DID_MAX];
    uint16 DataLength[DIAGSRV_CFG_0X22_MULTIPLE_DID_MAX];
    uint8 Head;
    uint8 Tail;
} DiagSrv_0x22_QueueInfoType;

typedef struct {
    P2CONST(uint8, TYPEDEF, DIAGSRV_APPL_CONST) DataPtr;
    uint16 DataSize;
} DiagSrv_0x22_NonceInfoType;

typedef DiagSrv_0x22_NonceInfoType DiagSrv_0x22_SoftwareNumberInfoType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x22_Enqueue
(
    VAR(uint16, AUTOMATIC) Did,
    VAR(uint16, AUTOMATIC) DataLength
);
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x22_Dequeue
(
    P2VAR(uint16, AUTOMATIC, DIAGSRV_APPL_DATA) Did,
    P2VAR(uint16, AUTOMATIC, DIAGSRV_APPL_DATA) DataLength
);
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x22_ClearQueue (void);
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x22_SendNegRsp
(
    VAR(uint8, AUTOMATIC) Nrc,
    P2VAR(Diag_MsgContextType, AUTOMATIC, DIAGSRV_APPL_DATA) Msg
);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x22_CheckReqMsgLen
(
    P2CONST(Diag_MsgContextType, AUTOMATIC, DIAGSRV_APPL_CONST) Msg
);
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x22_SetDidForRspData
(
    VAR(uint16, AUTOMATIC) Did
);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x22_UpdateJobStatus (void);
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x22_SetDataForRspData
(
    P2CONST(uint8, AUTOMATIC, DIAGSRV_APPL_CONST) SrcData,
    VAR(uint16, AUTOMATIC) SrcDataLen
);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x22_WaitForFingerPrintRead (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x22_WaitForUsrDidRead (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x22_CheckRspDataLen
(
    VAR(uint16, AUTOMATIC) DataLength
);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x22_ReadDidData
(
    VAR(uint16, AUTOMATIC) Did,
    VAR(uint16, AUTOMATIC) DataLength
);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x22_ReadDidData_FingerPrint
(
    VAR(uint16, AUTOMATIC) Did,
    VAR(uint16, AUTOMATIC) DataLength
);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x22_ReadDidData_FingerPrint_Proc
(
    VAR(uint16, AUTOMATIC) Did,
    VAR(uint16, AUTOMATIC) DataLength
);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x22_ReadDidData_FingerPrint_Check
(
    VAR(uint8, AUTOMATIC) RewriteAreaStatus
);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x22_CheckDid
(
    P2CONST(Diag_MsgContextType, AUTOMATIC, DIAGSRV_APPL_CONST) Msg
);
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x22_ClearInfo (void);
static FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_0x22_CheckFingerPrintData
(
    CONST(uint8, AUTOMATIC) Finger[],
    VAR(uint16, AUTOMATIC) FingerSize
);
#if (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON)
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x22_ReadDidData_FingerPrint_Gw
(
    VAR(uint16, AUTOMATIC) Did
);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x22_SubM_WaitForFingerPrintRead (void);
#endif


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_VAR
#include <DiagSrv_MemMap.h>

static P2VAR(Diag_MsgContextType, DIAGSRV_VAR_CLEARED, DIAGSRV_APPL_DATA) DiagSrv_0x22_Msg;
static VAR(uint8, DIAGSRV_VAR_CLEARED) DiagSrv_0x22_JobStatus;

static VAR(DiagSrv_0x22_QueueInfoType, DIAGSRV_VAR_CLEARED) DiagSrv_0x22_Queue;

static VAR(uint16, DIAGSRV_VAR_CLEARED) DiagSrv_0x22_RemainRspLen;
static VAR(uint16, DIAGSRV_VAR_CLEARED) DiagSrv_0x22_DataPos;
static VAR(uint16, DIAGSRV_VAR_CLEARED) DiagSrv_0x22_AsyncDataLength;

#if (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON)
static VAR(uint8, DIAGSRV_VAR_CLEARED) DiagSrv_0x22_SubM_MiconId;
static VAR(Rte_SubMiconIf_RespInfoType, DIAGSRV_VAR_CLEARED) DiagSrv_0x22_SubM_RspInfo;
/* Buffer */
static VAR(uint8, DIAGSRV_VAR_CLEARED) DiagSrv_0x22_SubM_ReqData[DIAGSRV_0X22_SUBM_REQDATA_SIZE];
static VAR(uint8, DIAGSRV_VAR_CLEARED) DiagSrv_0x22_SubM_RspData[DIAGSRV_0x22_SUBM_RSPDATA_SIZE];
#endif

#define DIAGSRV_STOP_SEC_VAR
#include <DiagSrv_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_CST
#include <DiagSrv_MemMap.h>

static CONST(uint8, DIAGSRV_CONST) DiagSrv_0x22_NonceData[] = {
    0x00U, 0x11U, 0x22U, 0x33U, 0x44U, 0x55U, 0x66U, 0x77U,
    0x88U, 0x99U, 0xAAU, 0xBBU, 0xCCU, 0xDDU, 0xEEU, 0xFFU
};

static CONST(AB_83_ConstV DiagSrv_0x22_NonceInfoType, DIAGSRV_CONST) DiagSrv_0x22_NonceInfo = {
    &DiagSrv_0x22_NonceData[0],
    DIAGSRV_0X22_DID_NONCE_LENGTH
};

static CONST(uint8, DIAGSRV_CONST) DiagSrv_0x22_SoftwareNumberData[] = {
    0x01U, 0x10U, 0x01U,
    0x21U, 0x21U, 0x21U, 0x21U, 0x21U, 0x21U, 0x21U, 0x21U,
    0x21U, 0x21U, 0x21U, 0x21U, 0x21U, 0x21U, 0x21U, 0x21U
};

static CONST(AB_83_ConstV DiagSrv_0x22_SoftwareNumberInfoType, DIAGSRV_CONST) DiagSrv_0x22_SoftwareNumberInfo = {
    &DiagSrv_0x22_SoftwareNumberData[0],
    DIAGSRV_0X22_DID_SOFTWARENUMBER_LENGTH
};

#if (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON)
static CONST(Rte_SubMiconIf_ReqInfoType, DIAGSRV_CONST) DiagSrv_0x22_SubM_ReqInfo = {
    &DiagSrv_0x22_SubM_ReqData[0],
    DIAGSRV_0X22_SUBM_REQDATA_SIZE
};
#endif

#define DIAGSRV_STOP_SEC_CST
#include <DiagSrv_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define DIAGSRV_START_SEC_CODE
#include <DiagSrv_MemMap.h>

/******************************************************************************/
/* Function Name | DiagSrv_0x22_Init                                          */
/* Description   | Initialize                                                 */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x22_Init (void)
{
    DiagSrv_0x22_ClearInfo();

#if (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON)
    DiagSrv_0x22_SubM_RspInfo.RespData = &DiagSrv_0x22_SubM_RspData[0];
    DiagSrv_0x22_SubM_RspInfo.RespDataSize = DIAGSRV_0x22_SUBM_RSPDATA_SIZE;
#endif

    DiagSrv_0x22_Usr_Init();

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x22_Time                                          */
/* Description   | Time function                                              */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x22_Time (void)
{
    VAR(uint16, AUTOMATIC) Did;
    VAR(uint16, AUTOMATIC) DataLength;
    VAR(uint8, AUTOMATIC) Nrc;

    DiagSrv_0x22_Usr_Time();

    if( DiagSrv_0x22_JobStatus != DIAGSRV_0X22_STAT_IDLE )
    {
        if( DiagSrv_0x22_JobStatus == DIAGSRV_0X22_STAT_WAIT_READ_FINGER )
        {
            Nrc = DiagSrv_0x22_WaitForFingerPrintRead();
        }
#if (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON)
        else if( DiagSrv_0x22_JobStatus == DIAGSRV_0X22_STAT_SUBM_WAIT_READ_FINGER )
        {
            Nrc = DiagSrv_0x22_SubM_WaitForFingerPrintRead();
        }
#endif
        else if( DiagSrv_0x22_JobStatus == DIAGSRV_0X22_STAT_WAIT_READ_USR_DID )
        {
            Nrc = DiagSrv_0x22_WaitForUsrDidRead();
        }
        else
        {
            Did = 0U;
            DataLength = 0U;
            DiagSrv_0x22_Dequeue(&Did, &DataLength);
            Nrc = DiagSrv_0x22_CheckRspDataLen(DataLength);

            if( Nrc == DIAG_NRC_RCRRP )
            {
                Nrc = DiagSrv_0x22_ReadDidData(Did, DataLength);
            }
        }

        if( Nrc == DIAG_NRC_RCRRP )
        {
            /* No process */
        }
        else if( Nrc == DIAG_NRC_PR )
        {
            DiagSrv_0x22_Msg->ResDataLen = DiagSrv_0x22_Msg->ResMaxDataLen - DiagSrv_0x22_RemainRspLen;
            DiagLib_SendPosRsp(DiagSrv_0x22_Msg);
            DiagSrv_0x22_ClearInfo();
        }
        else
        {
            DiagSrv_0x22_SendNegRsp(Nrc, DiagSrv_0x22_Msg);
        }
    }

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x22_Processing                                    */
/* Description   | Processing function                                        */
/* Preconditions |                                                            */
/* Parameters    | [IN] Msg : Message                                         */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x22_Processing
(
    P2VAR(Diag_MsgContextType, AUTOMATIC, DIAGSRV_APPL_DATA) Msg
)
{
    VAR(uint8, AUTOMATIC) RspSID;
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DiagSrv_0x22_CheckReqMsgLen(Msg);
    if( Nrc == DIAG_NRC_RCRRP )
    {
        Nrc = DiagSrv_0x22_CheckDid(Msg);
    }

    if( Nrc == DIAG_NRC_RCRRP )
    {
        DiagSrv_0x22_Msg = Msg;
        DiagSrv_0x22_JobStatus = DIAGSRV_0X22_STAT_DID_PROCESSING;
        DiagSrv_0x22_RemainRspLen = Msg->ResMaxDataLen;
        DiagSrv_0x22_DataPos = 0U;
        DiagSrv_0x22_AsyncDataLength = 0U;
        RspSID = DIAG_MAKE_POSRSP_SID(DiagSrv_0x22_Msg);
        DiagSrv_0x22_SetDataForRspData(&RspSID, DIAGSRV_0X22_SID_LEN);
    }
    else
    {
        DiagSrv_0x22_SendNegRsp(Nrc, Msg);
    }

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x22_Confirmation                                  */
/* Description   | Confirmation function                                      */
/* Preconditions |                                                            */
/* Parameters    | [IN] Status : Transmission complete status                 */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x22_Confirmation
(
    VAR(uint8, AUTOMATIC) Status
)
{
    /* No process */
    return;
}

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

/******************************************************************************/
/* Function Name | DiagSrv_0x22_Enqueue                                       */
/* Description   | Set DID to queue                                           */
/* Preconditions |                                                            */
/* Parameters    | [IN] Did        : DID                                      */
/*               | [IN] DataLength : Data record length                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x22_Enqueue
(
    VAR(uint16, AUTOMATIC) Did,
    VAR(uint16, AUTOMATIC) DataLength
)
{
    DiagSrv_0x22_Queue.Did[DiagSrv_0x22_Queue.Tail] = Did;
    DiagSrv_0x22_Queue.DataLength[DiagSrv_0x22_Queue.Tail] = DataLength;
    DiagSrv_0x22_Queue.Tail++;  /* no wrap around */

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x22_Dequeue                                       */
/* Description   | Remove DID from queue                                      */
/* Preconditions |                                                            */
/* Parameters    | [OUT] Did        : DID                                     */
/*               | [OUT] DataLength : Data record length                      */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x22_Dequeue
(
    P2VAR(uint16, AUTOMATIC, DIAGSRV_APPL_DATA) Did,
    P2VAR(uint16, AUTOMATIC, DIAGSRV_APPL_DATA) DataLength
)
{
    *Did = DiagSrv_0x22_Queue.Did[DiagSrv_0x22_Queue.Head];
    *DataLength = DiagSrv_0x22_Queue.DataLength[DiagSrv_0x22_Queue.Head];
    DiagSrv_0x22_Queue.Head++;  /* no wrap around */

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x22_ClearQueue                                    */
/* Description   | Retention queue initialization                             */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x22_ClearQueue (void)
{
    VAR(uint8, AUTOMATIC) Loop;

    for( Loop = 0U; Loop < DiagSrv_0x22_Config.MultipleDidNum; Loop++ )
    {
        DiagSrv_0x22_Queue.Did[Loop] = 0U;
        DiagSrv_0x22_Queue.DataLength[Loop] = 0U;
    }

    DiagSrv_0x22_Queue.Tail = 0U;
    DiagSrv_0x22_Queue.Head = 0U;

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x22_SendNegRsp                                    */
/* Description   | Send negative response                                     */
/* Preconditions |                                                            */
/* Parameters    | [IN] Nrc    : NRC                                          */
/*               | [IN] Msg    : Message                                      */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x22_SendNegRsp
(
    VAR(uint8, AUTOMATIC) Nrc,
    P2VAR(Diag_MsgContextType, AUTOMATIC, DIAGSRV_APPL_DATA) Msg
)
{
    DiagLib_SendNegRsp(Nrc, Msg);
    DiagSrv_0x22_ClearInfo();

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x22_CheckReqMsgLen                                */
/* Description   | Check request message length                               */
/* Preconditions |                                                            */
/* Parameters    | [IN] Msg : Message                                         */
/* Return Value  | NRC                                                        */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x22_CheckReqMsgLen
(
    P2CONST(Diag_MsgContextType, AUTOMATIC, DIAGSRV_APPL_CONST) Msg
)
{
    VAR(uint16, AUTOMATIC) ChkDataLen;
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DIAG_NRC_IMLOIF;

    if( Msg->ReqDataLen >= DIAG_DIDMSG_MIN_SIZE )
    {
        ChkDataLen = Msg->ReqDataLen & DIAGSRV_0X22_MSG_LEN_LOW_MASK;
        if( ChkDataLen == DIAGSRV_0X22_MSG_LEN_ODD )
        {
            ChkDataLen = ( (uint16)DIAGSRV_0X22_SID_LEN + ( (uint16)DIAGSRV_0X22_DID_LEN * (uint16)DiagSrv_0x22_Config.MultipleDidNum ) );
            if( ChkDataLen >= Msg->ReqDataLen )
            {
                Nrc = DIAG_NRC_RCRRP;
            }
        }
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x22_SetDidForRspData                              */
/* Description   | Set DID for response data                                  */
/* Preconditions |                                                            */
/* Parameters    | [IN] Did : DID                                             */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x22_SetDidForRspData
(
    VAR(uint16, AUTOMATIC) Did
)
{
    DiagSrv_0x22_Msg->ResData[DiagSrv_0x22_DataPos] = (uint8)(Did >> DIAGSRV_0X22_BIT_SHIFT_8);
    DiagSrv_0x22_DataPos++;                             /* no wrap around */
    DiagSrv_0x22_Msg->ResData[DiagSrv_0x22_DataPos] = (uint8)(Did & DIAGSRV_0X22_DID_LOW_MASK);
    DiagSrv_0x22_DataPos++;                             /* no wrap around */
    DiagSrv_0x22_RemainRspLen -= DIAGSRV_0X22_DID_LEN;  /* no wrap around */

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x22_UpdateJobStatus                               */
/* Description   | Update job status                                          */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x22_UpdateJobStatus (void)
{
    VAR(uint8, AUTOMATIC) Nrc;

    DiagSrv_0x22_JobStatus = DIAGSRV_0X22_STAT_IDLE;
    Nrc = DIAG_NRC_PR;

    if( DiagSrv_0x22_Queue.Tail > DiagSrv_0x22_Queue.Head )
    {
        DiagSrv_0x22_JobStatus = DIAGSRV_0X22_STAT_DID_PROCESSING;
        Nrc = DIAG_NRC_RCRRP;
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x22_SetDataForRspData                             */
/* Description   | Set data for response data                                 */
/* Preconditions |                                                            */
/* Parameters    | [IN] SrcData    : Source data                              */
/*               | [IN] SrcDataLen : Source data length                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x22_SetDataForRspData
(
    P2CONST(uint8, AUTOMATIC, DIAGSRV_APPL_CONST) SrcData,
    VAR(uint16, AUTOMATIC) SrcDataLen
)
{
    Rte_Rpg_MemCopy(&DiagSrv_0x22_Msg->ResData[DiagSrv_0x22_DataPos], SrcData, (uint32)SrcDataLen);
    DiagSrv_0x22_RemainRspLen -= SrcDataLen;    /* no wrap around */
    DiagSrv_0x22_DataPos += SrcDataLen;         /* no wrap around */

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x22_WaitForFingerPrintRead                        */
/* Description   | Wait for Fingerprint reading                               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x22_WaitForFingerPrintRead (void)
{
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(uint8, AUTOMATIC) RpgLibStatus;
    VAR(uint8, AUTOMATIC) JobResult;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Nrc = DIAG_NRC_RCRRP;

    RpgLibStatus = RpgLib_GetStatus();
    if( RpgLibStatus == RPGLIB_IDLE )
    {
        JobResult = RpgLib_GetJobResult();
        if( JobResult == RPGLIB_JOB_OK )
        {
            Ret = DiagSrv_0x22_CheckFingerPrintData(&DiagSrv_0x22_Msg->ResData[DiagSrv_0x22_DataPos],
                                                    DiagSrv_0x22_AsyncDataLength);
            if( Ret != (Std_ReturnType)E_OK )
            {
                Rte_Rpg_MemSet(&DiagSrv_0x22_Msg->ResData[DiagSrv_0x22_DataPos], 0U, (uint32)DiagSrv_0x22_AsyncDataLength);
            }

            Nrc = DiagSrv_0x22_UpdateJobStatus();
            DiagSrv_0x22_RemainRspLen -= DiagSrv_0x22_AsyncDataLength;  /* no wrap around */
            DiagSrv_0x22_DataPos += DiagSrv_0x22_AsyncDataLength;       /* no wrap around */
        }
        else if( JobResult == RPGLIB_JOB_MEMERR )
        {
            Nrc = DiagSrv_0x22_UpdateJobStatus();
            Rte_Rpg_MemSet(&DiagSrv_0x22_Msg->ResData[DiagSrv_0x22_DataPos], 0U, (uint32)DiagSrv_0x22_AsyncDataLength);
            DiagSrv_0x22_RemainRspLen -= DiagSrv_0x22_AsyncDataLength;  /* no wrap around */
            DiagSrv_0x22_DataPos += DiagSrv_0x22_AsyncDataLength;       /* no wrap around */
        }
        else
        {
            DiagSrv_0x22_JobStatus = DIAGSRV_0X22_STAT_IDLE;
            Nrc = DIAG_NRC_GR;
        }
    }
    else if( RpgLibStatus == RPGLIB_BUSY )
    {
        /* No process */
    }
    else
    {
        DiagSrv_0x22_JobStatus = DIAGSRV_0X22_STAT_IDLE;
        Nrc = DIAG_NRC_GR;
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x22_WaitForUsrDidRead                             */
/* Description   | Wait for user optional did reading                         */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x22_WaitForUsrDidRead (void)
{
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(uint8, AUTOMATIC) UsrStatus;

    Nrc = DIAG_NRC_RCRRP;

    UsrStatus = DiagSrv_0x22_Usr_GetStatus();
    if( UsrStatus == DIAGSRV_0X22_USR_IDLE)
    {
        Nrc = DiagSrv_0x22_Usr_GetJobResult();
        if( Nrc == DIAG_NRC_PR )
        {
            Nrc = DiagSrv_0x22_UpdateJobStatus();
            DiagSrv_0x22_RemainRspLen -= DiagSrv_0x22_AsyncDataLength;  /* no wrap around */
            DiagSrv_0x22_DataPos += DiagSrv_0x22_AsyncDataLength;       /* no wrap around */
        }
        else
        {
            DiagSrv_0x22_JobStatus = DIAGSRV_0X22_STAT_IDLE;
        }
    }
    else if( UsrStatus == DIAGSRV_0X22_USR_BUSY )
    {
        /* No process */
    }
    else
    {
        DiagSrv_0x22_JobStatus = DIAGSRV_0X22_STAT_IDLE;
        Nrc = DIAG_NRC_GR;
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x22_CheckRspDataLen                               */
/* Description   | Check response data length                                 */
/* Preconditions |                                                            */
/* Parameters    | [IN] DataLength : Data record length                       */
/* Return Value  | NRC                                                        */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x22_CheckRspDataLen
(
    VAR(uint16, AUTOMATIC) DataLength
)
{
    VAR(uint16, AUTOMATIC) ChkDataLen;
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DIAG_NRC_RCRRP;
    ChkDataLen = DataLength + DIAGSRV_0X22_DID_LEN;
    if( DiagSrv_0x22_RemainRspLen < ChkDataLen )
    {
        DiagSrv_0x22_JobStatus = DIAGSRV_0X22_STAT_IDLE;
        Nrc = DIAG_NRC_RTL;
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x22_ReadDidData                                   */
/* Description   | Read DID data                                              */
/* Preconditions |                                                            */
/* Parameters    | [IN] Did        : DID                                      */
/*               | [IN] DataLength : Data record length                       */
/* Return Value  | NRC                                                        */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x22_ReadDidData
(
    VAR(uint16, AUTOMATIC) Did,
    VAR(uint16, AUTOMATIC) DataLength
)
{
    VAR(uint8, AUTOMATIC) DiagLibSession;
    VAR(uint8, AUTOMATIC) Nrc;
    P2CONST(uint8, AUTOMATIC, DIAGSRV_APPL_CONST) ReadDataPtr;

    if( Did == DIAGSRV_0X22_DID_SESSION )
    {
        DiagLibSession = DiagLib_GetSession();

        Nrc = DiagSrv_0x22_UpdateJobStatus();
        DiagSrv_0x22_SetDidForRspData(Did);
        DiagSrv_0x22_SetDataForRspData(&DiagLibSession, DataLength);
    }
    else if( Did == DIAGSRV_0X22_DID_NONCE )
    {
        ReadDataPtr = DiagSrv_0x22_NonceInfo.DataPtr;

        Nrc = DiagSrv_0x22_UpdateJobStatus();
        DiagSrv_0x22_SetDidForRspData(Did);
        DiagSrv_0x22_SetDataForRspData(ReadDataPtr, DataLength);
    }
    else if( Did == DIAGSRV_0X22_DID_SOFTWARENUMBER )
    {
        ReadDataPtr = DiagSrv_0x22_SoftwareNumberInfo.DataPtr;

        Nrc = DiagSrv_0x22_UpdateJobStatus();
        DiagSrv_0x22_SetDidForRspData(Did);
        DiagSrv_0x22_SetDataForRspData(ReadDataPtr, DataLength);
    }
    else if( (Did >= DIAGSRV_0X22_DID_FINGERPRINT_0) && (Did <= DIAGSRV_0X22_DID_FINGERPRINT_31) )
    {
        Nrc = DiagSrv_0x22_ReadDidData_FingerPrint(Did, DataLength);
    }
    else
    {
        DiagSrv_0x22_SetDidForRspData(Did);
        Nrc = DiagSrv_0x22_Usr_ReqReadDidData(Did, &DiagSrv_0x22_Msg->ResData[DiagSrv_0x22_DataPos], DataLength);
        if( Nrc == DIAG_NRC_RCRRP )
        {
            DiagSrv_0x22_AsyncDataLength = DataLength;
            DiagSrv_0x22_JobStatus = DIAGSRV_0X22_STAT_WAIT_READ_USR_DID;
        }
        else
        {
            DiagSrv_0x22_JobStatus = DIAGSRV_0X22_STAT_IDLE;
        }
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x22_ReadDidData_FingerPrint                       */
/* Description   | Read DID data for Fingerprint                              */
/* Preconditions |                                                            */
/* Parameters    | [IN] Did        : DID                                      */
/*               | [IN] DataLength : Data record length                       */
/* Return Value  | NRC                                                        */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x22_ReadDidData_FingerPrint
(
    VAR(uint16, AUTOMATIC) Did,
    VAR(uint16, AUTOMATIC) DataLength
)
{
    VAR(uint8, AUTOMATIC) Nrc;
#if (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON)
    VAR(uint8, AUTOMATIC) RewriteAreaNum;

    RewriteAreaNum = (uint8)(Did & DIAGSRV_0X22_MASK_DID_TO_REWRITEAREANUM);

    DiagSrv_0x22_SubM_MiconId = DiagSrv_SubM_ConvertRewriteArea2MiconId(RewriteAreaNum);
    if( DiagSrv_0x22_SubM_MiconId == DIAGSRV_SUBM_ID_MAIN )
    {
        Nrc = DiagSrv_0x22_ReadDidData_FingerPrint_Proc(Did, DataLength);
    }
    else
    {
        Nrc = DiagSrv_0x22_ReadDidData_FingerPrint_Gw(Did);
    }
#else
    Nrc = DiagSrv_0x22_ReadDidData_FingerPrint_Proc(Did, DataLength);
#endif

    if( (Nrc != DIAG_NRC_PR) && (Nrc != DIAG_NRC_RCRRP) )
    {
        DiagSrv_0x22_JobStatus = DIAGSRV_0X22_STAT_IDLE;
        Nrc = DIAG_NRC_GR;
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x22_ReadDidData_FingerPrint_Proc                  */
/* Description   | Read DID data process for Fingerprint process              */
/* Preconditions |                                                            */
/* Parameters    | [IN] Did        : DID                                      */
/*               | [IN] DataLength : Data record length                       */
/* Return Value  | NRC                                                        */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x22_ReadDidData_FingerPrint_Proc
(
    VAR(uint16, AUTOMATIC) Did,
    VAR(uint16, AUTOMATIC) DataLength
)
{
    VAR(uint32, AUTOMATIC) FingerprintAddr;
    VAR(uint32, AUTOMATIC) RprgDataAddr;
    VAR(uint32, AUTOMATIC) RprgDataSize;
    VAR(uint32, AUTOMATIC) PhysicalAddr;
    VAR(uint32, AUTOMATIC) MemoryId;
    VAR(uint8, AUTOMATIC) DeviceType;
    VAR(uint8, AUTOMATIC) RewriteAreaNum;
    VAR(uint8, AUTOMATIC) RewriteAreaStatus;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;
    VAR(uint8, AUTOMATIC) ValidFlag;
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DIAG_NRC_GR;
    MemoryId = RPGLIB_MEMORYID_0;

    RewriteAreaNum = (uint8)(Did & DIAGSRV_0X22_MASK_DID_TO_REWRITEAREANUM);
    RprgDataAddr = 0UL;
    RprgDataSize = 0UL;

    DiagSrv_GetRprgDataAreaInfo(RewriteAreaNum, &RprgDataAddr, &RprgDataSize);
    FingerprintAddr = DIAGSRV_GET_RPRGDATA_FINGERPRINTDATA_ADDR(RprgDataAddr);  /* no wrap around */
    RewriteAreaStatus = DiagSrv_GetRewriteAreaStatus(RewriteAreaNum);

    if( ReprogOpt_DoubleMapConfig == (uint8)REPROGOPT_DOUBLEMAP_REWRITE_INVALID )
    {
        DeviceType = RPGLIB_DEVICE_TYPE_CODEFLS;

        FuncRet = RpgLib_CnvPhysicalAddr(MemoryId, FingerprintAddr, &PhysicalAddr, &DeviceType);
        if( FuncRet == (Std_ReturnType)E_OK )
        {
            if( DeviceType == RPGLIB_DEVICE_TYPE_CODEFLS )
            {
                if( RewriteAreaStatus != DIAGSRV_LBSTAT_REWRITING_OK )
                {
                    MemoryId = RPGLIB_MEMORYID_1;   /* Valid area */
                }
                ValidFlag = STD_ON;
            }
            else
            {
                ValidFlag = DiagSrv_0x22_ReadDidData_FingerPrint_Check(RewriteAreaStatus);
            }
            Nrc = DIAG_NRC_PR;
        }
    }
    else
    {
        ValidFlag = DiagSrv_0x22_ReadDidData_FingerPrint_Check(RewriteAreaStatus);
        Nrc = DIAG_NRC_PR;
    }

    if( Nrc == DIAG_NRC_PR )
    {
        if( ValidFlag == (uint8)STD_ON )
        {
            Nrc = DIAG_NRC_GR;

            DiagSrv_0x22_SetDidForRspData(Did);
            FuncRet = RpgLib_ReqMemRead(MemoryId,
                                        &DiagSrv_0x22_Msg->ResData[DiagSrv_0x22_DataPos],
                                        FingerprintAddr,
                                        DIAGSRV_CFG_FINGERPRINT_SIZE);
            if( FuncRet == (Std_ReturnType)E_OK )
            {
                DiagSrv_0x22_AsyncDataLength = DataLength;
                DiagSrv_0x22_JobStatus = DIAGSRV_0X22_STAT_WAIT_READ_FINGER;
                Nrc = DIAG_NRC_RCRRP;
            }
        }
        else
        {
            /* Set invalid value 0 */
            Nrc = DiagSrv_0x22_UpdateJobStatus();
            DiagSrv_0x22_SetDidForRspData(Did);
            Rte_Rpg_MemSet(&DiagSrv_0x22_Msg->ResData[DiagSrv_0x22_DataPos], 0U, (uint32)DataLength);
            DiagSrv_0x22_RemainRspLen -= DataLength;    /* no wrap around */
            DiagSrv_0x22_DataPos += DataLength;         /* no wrap around */
        }
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x22_ReadDidData_FingerPrint_Check                 */
/* Description   | Check if Fingerprint is valid                              */
/* Preconditions |                                                            */
/* Parameters    | [IN] RewriteAreaStatus : Rewrite area status               */
/* Return Value  | Valid                                                      */
/*               |  STD_ON                                                    */
/*               |  STD_OFF                                                   */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x22_ReadDidData_FingerPrint_Check
(
    VAR(uint8, AUTOMATIC) RewriteAreaStatus
)
{
    VAR(uint8, AUTOMATIC) ValidFlag;
    VAR(uint8, AUTOMATIC) BootMode;

    ValidFlag = STD_OFF;

    if( RewriteAreaStatus == DIAGSRV_LBSTAT_REWRITING_OK )
    {
        ValidFlag = STD_ON;
    }
    else if( RewriteAreaStatus == DIAGSRV_LBSTAT_BEFORE_REWRITING )
    {
        BootMode = Rte_EcuM_GetBootMode();
        if( BootMode != RTE_ECUM_START_BOOT_ENTRY )
        {
            ValidFlag = STD_ON;
        }
    }
    else
    {
        /* No process */
    }

    return ValidFlag;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x22_CheckDid                                      */
/* Description   | Check DID                                                  */
/* Preconditions |                                                            */
/* Parameters    | [IN] Msg : Message                                         */
/* Return Value  | NRC                                                        */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x22_CheckDid
(
    P2CONST(Diag_MsgContextType, AUTOMATIC, DIAGSRV_APPL_CONST) Msg
)
{
    VAR(uint16, AUTOMATIC) Did;
    VAR(uint16, AUTOMATIC) MsgIdx;
    VAR(uint8, AUTOMATIC) CfgIdx;
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DIAG_NRC_ROOR;
    MsgIdx = DIAGSRV_0X22_DID_H_POS;
    while( MsgIdx < (Msg->ReqDataLen - DIAGSRV_0X22_SID_LEN) )
    {
        CfgIdx = 0U;
        Did = (uint16)Rte_Rpg_ByteCombine(&Msg->ReqData[MsgIdx], DIAGSRV_0X22_DID_LEN);
        Nrc = DiagLib_CheckDidSupport(Did, &DiagSrv_0x22_DidConfig, &CfgIdx);

        if( Nrc == DIAG_NRC_PR )
        {
            Nrc = DIAG_NRC_RCRRP;
            DiagSrv_0x22_Enqueue(Did, DiagSrv_0x22_DidConfig.InfoPtr[CfgIdx].Length);
        }
        else if( Nrc == DIAG_NRC_SAD )
        {
            break;
        }
        else
        {
            /* No process */
        }
        MsgIdx += DIAGSRV_0X22_DID_LEN; /* no wrap around */
    }
    if( Nrc == DIAG_NRC_ROOR )
    {
        if( DiagSrv_0x22_Queue.Tail != DiagSrv_0x22_Queue.Head )
        {
            Nrc = DIAG_NRC_RCRRP;
        }
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x22_ClearInfo                                     */
/* Description   | Clear information function                                 */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x22_ClearInfo (void)
{
    DiagSrv_0x22_Msg = NULL_PTR;
    DiagSrv_0x22_JobStatus = DIAGSRV_0X22_STAT_IDLE;
    DiagSrv_0x22_RemainRspLen = 0U;
    DiagSrv_0x22_DataPos = 0U;
    DiagSrv_0x22_AsyncDataLength = 0U;
#if (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON)
    DiagSrv_0x22_SubM_MiconId = DIAGSRV_SUBM_ID_MAIN;
    Rte_Rpg_MemSet(&DiagSrv_0x22_SubM_ReqData[0], 0U, sizeof(DiagSrv_0x22_SubM_ReqData));
    Rte_Rpg_MemSet(&DiagSrv_0x22_SubM_RspData[0], 0U, sizeof(DiagSrv_0x22_SubM_RspData));
#endif

    DiagSrv_0x22_ClearQueue();

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x22_CheckFingerPrintData                          */
/* Description   | Check Fingerprint                                          */
/* Preconditions |                                                            */
/* Parameters    | [IN] Finger     : Fingerprint                              */
/*               | [IN] FingerSize : Fingerprint size                         */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_0x22_CheckFingerPrintData
(
    CONST(uint8, AUTOMATIC) Finger[],
    VAR(uint16, AUTOMATIC) FingerSize
)
{
    VAR(uint16, AUTOMATIC) i;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = E_NOT_OK;

    for( i = 0U; i < FingerSize; i++ )
    {
        if( Finger[i] != DIAGSRV_0X22_FINGER_INVALID )
        {
            Ret = E_OK;
            break;
        }
    }

    return Ret;
}

#if (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON)
/******************************************************************************/
/* Function Name | DiagSrv_0x22_ReadDidData_FingerPrint_Gw                    */
/* Description   | Gateway Fingerprint reads                                  */
/* Preconditions |                                                            */
/* Parameters    | [IN] Did : DID                                             */
/* Return Value  | NRC                                                        */
/* Notes         | This function is valid when REPROG_CFG_SUBMICON_USE_MAIN   */
/*               | is defined.                                                */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x22_ReadDidData_FingerPrint_Gw
(
    VAR(uint16, AUTOMATIC) Did
)
{
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    Nrc = DIAG_NRC_GR;

    DiagSrv_0x22_SubM_ReqData[0] = DIAG_SID_RDBI;
    DiagSrv_0x22_SubM_ReqData[DIAGSRV_0X22_DID_H_POS] = (uint8)(Did >> DIAGSRV_0X22_BIT_SHIFT_8);
    DiagSrv_0x22_SubM_ReqData[DIAGSRV_0X22_DID_L_POS] = (uint8)(Did & DIAGSRV_0X22_DID_LOW_MASK);
    DiagSrv_0x22_SubM_RspInfo.RespDataSize = DIAGSRV_0x22_SUBM_RSPDATA_SIZE;

    FuncRet = Rte_SubMiconIf_Main_RequestService(DiagSrv_0x22_SubM_MiconId,
                                                &DiagSrv_0x22_SubM_ReqInfo,
                                                &DiagSrv_0x22_SubM_RspInfo,
                                                RTE_SUBMICONIF_INITIAL);
    if( FuncRet == RTE_SUBMICONIF_E_PENDING )
    {
        DiagSrv_0x22_JobStatus = DIAGSRV_0X22_STAT_SUBM_WAIT_READ_FINGER;
        Nrc = DIAG_NRC_RCRRP;
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x22_SubM_WaitForFingerPrintRead                   */
/* Description   | Wait for Sub-microcontroller Fingerprint reading           */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/* Notes         | This function is valid when REPROG_CFG_SUBMICON_USE_MAIN   */
/*               | is defined.                                                */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x22_SubM_WaitForFingerPrintRead (void)
{
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(Std_ReturnType, AUTOMATIC) Result;
    VAR(uint8, AUTOMATIC) CheckRspSID;

    Nrc = DIAG_NRC_RCRRP;

    Result = Rte_SubMiconIf_Main_RequestService(DiagSrv_0x22_SubM_MiconId,
                                                &DiagSrv_0x22_SubM_ReqInfo,
                                                &DiagSrv_0x22_SubM_RspInfo,
                                                RTE_SUBMICONIF_PENDING);
    if( Result == RTE_SUBMICONIF_E_PENDING )
    {
        /* No process */
    }
    else if( Result == (Std_ReturnType)E_OK )
    {
        CheckRspSID = DIAG_MAKE_POSRSP_SID(DiagSrv_0x22_Msg);
        if( DiagSrv_0x22_SubM_RspInfo.RespData[0] == CheckRspSID )
        {
            Nrc = DiagSrv_0x22_UpdateJobStatus();
            DiagSrv_0x22_SetDataForRspData(&DiagSrv_0x22_SubM_RspInfo.RespData[DIAGSRV_0X22_DID_H_POS],
                                           DiagSrv_0x22_SubM_RspInfo.RespDataSize - DIAGSRV_0X22_SID_LEN);
        }
        else
        {
            DiagSrv_0x22_JobStatus = DIAGSRV_0X22_STAT_IDLE;
            Nrc = DIAG_NRC_GR;
        }
    }
    else
    {
        DiagSrv_0x22_JobStatus = DIAGSRV_0X22_STAT_IDLE;
        Nrc = DIAG_NRC_GR;
    }

    return Nrc;
}

#endif

#define DIAGSRV_STOP_SEC_CODE
#include <DiagSrv_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2023/01/17 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/
