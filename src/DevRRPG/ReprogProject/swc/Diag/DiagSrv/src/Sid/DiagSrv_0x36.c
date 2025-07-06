/* DiagSrv_0x36_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagSrv/0x36/CODE                                           */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <CmpDecmp.h>
#include <Decrypt.h>
#include <DiagLib.h>
#include <FscDtct.h>
#include <ReprogOpt.h>
#include <RpgLib.h>
#include <RpgMfr.h>
#include <RpgSpp.h>
#include <Rte.h>

#include <DiagSrv.h>
#include "DiagSrv_0x36.h"
#include "DiagSrv_Local.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/* Job Status */
#define DIAGSRV_0X36_STAT_IDLE                      ((uint8)0x00U)
#define DIAGSRV_0X36_STAT_RECEPTION                 ((uint8)0x01U)
#define DIAGSRV_0X36_STAT_WAIT_DECODE               ((uint8)0x02U)
#define DIAGSRV_0X36_STAT_WAIT_DECMP                ((uint8)0x03U)
#define DIAGSRV_0X36_STAT_WAIT_WRITE                ((uint8)0x04U)
#define DIAGSRV_0X36_STAT_WAIT_DECMP_WRITE          ((uint8)0x05U)
#define DIAGSRV_0X36_STAT_WAIT_SIGVERIFY            ((uint8)0x06U)

/* Data Length */
#define DIAGSRV_0X36_SID_LEN                        ((uint16)1U)
#define DIAGSRV_0X36_BSC_LEN                        ((uint16)1U)
#define DIAGSRV_0X36_REQ_DOWNLOAD_MSG_MIN_LEN       ((uint16)3U)
#define DIAGSRV_0X36_RSP_DOWNLOAD_MSG_LEN           ((uint16)2U)
#define DIAGSRV_0X36_GET_REQ_PARAM_LEN(reqDataLen)  ((reqDataLen) - (DIAGSRV_0X36_SID_LEN + DIAGSRV_0X36_BSC_LEN))
#define DIAGSRV_0x36_TOTAL_CMP_SIZE_PARAM_LEN       ((uint16)4U)
#define DIAGSRV_0x36_CMP_RESERVED_PARAM_LEN         ((uint16)12U)
#define DIAGSRV_0x36_CMP_INFOMATION_LEN             ((DIAGSRV_0x36_TOTAL_CMP_SIZE_PARAM_LEN + DIAGSRV_0x36_CMP_RESERVED_PARAM_LEN))

/* Message Parameter Position */
#define DIAGSRV_0X36_SID_POS                        ((uint16)0U)
#define DIAGSRV_0X36_BSC_POS                        ((uint16)1U)
#define DIAGSRV_0X36_TRTP1_POS                      ((uint16)2U)

/* PKCS#7 Padding */
#define DIAGSRV_0X36_PADDING_SIZE_16                ((uint8)16U)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef struct {
    uint32 ReqWriteSize;
    uint32 WrittenSize;
    uint32 TargetAreaSize;
    uint32 TransferRemainSize;
    uint32 TotalCmpDataSize;
    uint8 PaddingSize;
} DiagSrv_0x36_SizeInfoType;

typedef struct {
    uint32 StartAddr;
    uint32 AvailableSize;
} DiagSrv_0x36_VerifyInfoType;

typedef struct {
    P2VAR(Diag_MsgContextType, DIAGSRV_VAR_CLEARED, DIAGSRV_APPL_DATA) WaitMsg;
    uint32 CodeFlsStartAddr;
    uint8 Nrc;
} DiagSrv_0x36_ParallelInfoType;

typedef struct {
    CmpDecmp_DecompressInfoType Info;
    uint8 Op;
} DiagSrv_0x36_DecmpInfoType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x36_Time_Reception (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x36_Time_Download (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x36_Time_Decode (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x36_Time_Decmp (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x36_Time_Write (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x36_Time_DecmpWrite (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x36_Time_SigVerify (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x36_CheckMsg
(
    VAR(uint8, AUTOMATIC) RewriteStatus
);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x36_CheckSameBSC
(
    VAR(uint8, AUTOMATIC) RewriteStatus
);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x36_CheckBSC
(
    VAR(uint8, AUTOMATIC) RewriteStatus
);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x36_CalcPaddingSize
(
    VAR(uint32, AUTOMATIC) TotalSize
);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x36_CheckPaddingData
(
    CONST(uint8, AUTOMATIC) Buf[],
    VAR(uint8, AUTOMATIC) PaddingSize
);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x36_CheckMNOBL (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x36_CheckCondition (void);
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x36_UpdateTargetAreaInfo
(
    VAR(uint8, AUTOMATIC) RewriteStatus
);
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x36_UpdateParallelInfo (void);
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x36_ExecuteTransferData (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x36_DecryptCiphertext (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x36_WritePlaintext (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x36_StartDecompress (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x36_Decompress (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x36_WriteDecompressData
(
    VAR(Std_ReturnType, AUTOMATIC) DecmpResult
);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x36_WriteMemUpdate
(
    P2CONST(uint8, AUTOMATIC, DIAGSRV_APPL_CONST) SrcAddr,
    VAR(uint32, AUTOMATIC) Size
);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x36_WriteFinish (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x36_PostTransfer (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x36_SigVerify (void);
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x36_TransferSuccess (void);
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x36_TransferFailed
(
    VAR(uint8, AUTOMATIC) Nrc
);
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x36_SendPosRsp (void);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_VAR
#include <DiagSrv_MemMap.h>

static VAR(uint8, DIAGSRV_VAR_CLEARED) DiagSrv_0x36_Status;
static VAR(uint8, DIAGSRV_VAR_CLEARED) DiagSrv_0x36_Bsc;
static P2VAR(Diag_MsgContextType, DIAGSRV_VAR_CLEARED, DIAGSRV_APPL_DATA) DiagSrv_0x36_Msg;
static VAR(DiagSrv_0x36_SizeInfoType, DIAGSRV_VAR_CLEARED) DiagSrv_0x36_SizeInfo;
static VAR(DiagSrv_0x36_VerifyInfoType, DIAGSRV_VAR_CLEARED) DiagSrv_0x36_VerifyInfo;
static VAR(DiagSrv_0x36_ParallelInfoType, DIAGSRV_VAR_CLEARED) DiagSrv_0x36_ParallelInfo;
static VAR(DiagSrv_0x36_DecmpInfoType, DIAGSRV_VAR_CLEARED) DiagSrv_0x36_DecmpInfo;

#define DIAGSRV_STOP_SEC_VAR
#include <DiagSrv_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_CST
#include <DiagSrv_MemMap.h>

#define DIAGSRV_STOP_SEC_CST
#include <DiagSrv_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define DIAGSRV_START_SEC_CODE
#include <DiagSrv_MemMap.h>

/******************************************************************************/
/* Function Name | DiagSrv_0x36_Init                                          */
/* Description   | Initialize                                                 */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x36_Init (void)
{
    DiagSrv_0x36_ClearInfo();

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x36_Time                                          */
/* Description   | Time function                                              */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x36_Time (void)
{
    VAR(uint8, AUTOMATIC) Nrc;

    if( DiagSrv_0x36_Status == DIAGSRV_0X36_STAT_IDLE )
    {
        /* No process */
    }
    else if( DiagSrv_0x36_Status == DIAGSRV_0X36_STAT_RECEPTION )
    {
        DiagSrv_0x36_Time_Reception();
    }
    else
    {
        Nrc = DiagSrv_0x36_Time_Download();
        if( Nrc == DIAG_NRC_RCRRP )
        {
            /* No process */
        }
        else if( Nrc == DIAG_NRC_PR )
        {
            DiagSrv_0x36_VerifyInfo.AvailableSize = 0UL;

            if( ReprogOpt_ParallelConfig == (uint8)STD_ON )
            {
                DiagSrv_0x36_UpdateParallelInfo();
            }
            else
            {
                DiagSrv_0x36_Status = DIAGSRV_0X36_STAT_IDLE;
                DiagSrv_0x36_SendPosRsp();
                DiagSrv_0x36_Msg = NULL_PTR;
            }
        }
        else
        {
            if( ReprogOpt_ParallelConfig == (uint8)STD_ON )
            {
                DiagSrv_0x36_UpdateParallelInfo();
                DiagSrv_0x36_ParallelInfo.Nrc = Nrc;
            }
            else
            {
                DiagSrv_0x36_TransferFailed(Nrc);
            }
        }
    }

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x36_Processing                                    */
/* Description   | Processing function                                        */
/* Preconditions |                                                            */
/* Parameters    | [IN] Msg : Message                                         */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x36_Processing
(
    P2VAR(Diag_MsgContextType, AUTOMATIC, DIAGSRV_APPL_DATA) Msg
)
{
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DiagSrv_0x36_GetProcessStatus();
    if( Nrc == DIAG_NRC_RCRRP )
    {
        DiagSrv_0x36_ParallelInfo.WaitMsg = Msg;
    }
    else
    {
        DiagSrv_0x36_Status = DIAGSRV_0X36_STAT_RECEPTION;
        DiagSrv_0x36_Msg = Msg;
    }

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x36_Confirmation                                  */
/* Description   | Confirmation function                                      */
/* Preconditions |                                                            */
/* Parameters    | [IN] Status : Transmission complete status                 */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x36_Confirmation
(
    VAR(uint8, AUTOMATIC) Status
)
{
    /* No process */
    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x36_ClearInfo                                     */
/* Description   | Clear information function                                 */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x36_ClearInfo (void)
{
    DiagSrv_0x36_Msg = NULL_PTR;
    DiagSrv_0x36_Bsc = 0U;
    DiagSrv_0x36_Status = DIAGSRV_0X36_STAT_IDLE;

    DiagSrv_0x36_SizeInfo.ReqWriteSize = 0UL;
    DiagSrv_0x36_SizeInfo.WrittenSize = 0UL;
    DiagSrv_0x36_SizeInfo.TargetAreaSize = 0UL;
    DiagSrv_0x36_SizeInfo.TransferRemainSize = 0UL;
    DiagSrv_0x36_SizeInfo.TotalCmpDataSize = 0UL;
    DiagSrv_0x36_SizeInfo.PaddingSize = 0U;

    DiagSrv_0x36_VerifyInfo.StartAddr = 0UL;
    DiagSrv_0x36_VerifyInfo.AvailableSize = 0UL;

    DiagSrv_0x36_ParallelInfo.WaitMsg = NULL_PTR;
    DiagSrv_0x36_ParallelInfo.CodeFlsStartAddr = 0UL;
    DiagSrv_0x36_ParallelInfo.Nrc = DIAG_NRC_PR;

    DiagSrv_0x36_DecmpInfo.Op = CMPDECMP_DECMP_START;
    DiagSrv_0x36_DecmpInfo.Info.CompData = NULL_PTR;
    DiagSrv_0x36_DecmpInfo.Info.CompDataSize = 0UL;
    DiagSrv_0x36_DecmpInfo.Info.CompDataTotalSize = 0UL;
    DiagSrv_0x36_DecmpInfo.Info.DecompBuf = NULL_PTR;
    DiagSrv_0x36_DecmpInfo.Info.DecompResultSize = 0UL;

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x36_GetProcessStatus                              */
/* Description   | Get parallelization process status                         */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  Depends on parallel processing result                     */
/*               |   - DIAG_NRC_PR                                            */
/*               |   - DIAG_NRC_RCRRP                                         */
/*               |   - DIAG_NRC_ROOR                                          */
/*               |   - DIAG_NRC_TDS                                           */
/*               |   - DIAG_NRC_VTL                                           */
/*               |   - DIAG_NRC_GPF                                           */
/*               |   - other(Depends on UserCustom)                           */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x36_GetProcessStatus (void)
{
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DIAG_NRC_RCRRP;

    if( DiagSrv_0x36_Status == DIAGSRV_0X36_STAT_IDLE )
    {
        Nrc = DiagSrv_0x36_ParallelInfo.Nrc;
    }

    return Nrc;
}

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

/******************************************************************************/
/* Function Name | DiagSrv_0x36_Time_Reception                                */
/* Description   | Time of DIAGSRV_0X36_STAT_RECEPTION                        */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x36_Time_Reception (void)
{
    VAR(uint8, AUTOMATIC) TransferMode;
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(uint8, AUTOMATIC) DeviceType;
    VAR(uint8, AUTOMATIC) RewriteStatus;

    Nrc = DIAG_NRC_RSE;

    TransferMode = DiagLib_GetTransferMode();
    if( TransferMode == DIAG_TFMODE_DL )
    {
        RewriteStatus = DiagSrv_GetRewriteStatus();
        Nrc = DiagSrv_0x36_CheckMsg(RewriteStatus);
    }

    if( Nrc == DIAG_NRC_PR )
    {
        /* Check same BSC */
        Nrc = DiagSrv_0x36_CheckSameBSC(RewriteStatus);
        if( Nrc == DIAG_NRC_PR )
        {
            /* Send positive response because BSC is the same value. */
            DiagSrv_0x36_Status = DIAGSRV_0X36_STAT_IDLE;
            DiagSrv_0x36_SendPosRsp();
            DiagSrv_0x36_Msg = NULL_PTR;

            if( ReprogOpt_ParallelConfig == (uint8)STD_ON )
            {
                DiagSrv_0x36_UpdateParallelInfo();
            }
        }
        else
        {
            /* Check BSC */
            Nrc = DiagSrv_0x36_CheckBSC(RewriteStatus);
            if( Nrc == DIAG_NRC_PR )
            {
                if( ReprogOpt_ParallelConfig == (uint8)STD_ON )
                {
                    /* Send positive response first for parallelization. */
                    DiagSrv_0x36_SendPosRsp();

                    DeviceType = DiagSrv_GetWriteDeviceType();
                    if( DeviceType == DIAGSRV_DEVICE_TYPE_CODEFLS )
                    {
                        DiagSrv_0x36_ParallelInfo.CodeFlsStartAddr = RpgLib_GetNextWriteAddr();
                    }
                }
                /* Execute the following TransferData process. */
                DiagSrv_0x36_UpdateTargetAreaInfo(RewriteStatus);
                DiagSrv_0x36_ExecuteTransferData();
            }
        }
    }

    if( Nrc != DIAG_NRC_PR )
    {
        DiagSrv_0x36_TransferFailed(Nrc);

        if( ReprogOpt_ParallelConfig == (uint8)STD_ON )
        {
            DiagSrv_0x36_UpdateParallelInfo();
        }
    }

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x36_Time_Download                                 */
/* Description   | Time function for download mode                            */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_ROOR                                             */
/*               |  DIAG_NRC_TDS                                              */
/*               |  DIAG_NRC_VTL                                              */
/*               |  DIAG_NRC_GPF                                              */
/*               |  other(Depends on UserCustom)                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x36_Time_Download (void)
{
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DIAG_NRC_GPF;

    if( DiagSrv_0x36_Status == DIAGSRV_0X36_STAT_WAIT_DECODE )
    {
        Nrc = DiagSrv_0x36_Time_Decode();
    }
    else if( DiagSrv_0x36_Status == DIAGSRV_0X36_STAT_WAIT_DECMP )
    {
        Nrc = DiagSrv_0x36_Time_Decmp();
    }
    else if( DiagSrv_0x36_Status == DIAGSRV_0X36_STAT_WAIT_WRITE )
    {
        Nrc = DiagSrv_0x36_Time_Write();
    }
    else if( DiagSrv_0x36_Status == DIAGSRV_0X36_STAT_WAIT_DECMP_WRITE )
    {
        Nrc = DiagSrv_0x36_Time_DecmpWrite();
    }
    else if( DiagSrv_0x36_Status == DIAGSRV_0X36_STAT_WAIT_SIGVERIFY )
    {
        Nrc = DiagSrv_0x36_Time_SigVerify();
    }
    else
    {
        /* No process */
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x36_Time_Decode                                   */
/* Description   | Time of DIAGSRV_0X36_STAT_WAIT_DECODE                      */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_ROOR                                             */
/*               |  DIAG_NRC_TDS                                              */
/*               |  DIAG_NRC_VTL                                              */
/*               |  DIAG_NRC_GPF                                              */
/*               |  other(Depends on UserCustom)                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x36_Time_Decode (void)
{
    VAR(uint8, AUTOMATIC) Status;
    VAR(uint8, AUTOMATIC) JobResult;
    VAR(uint8, AUTOMATIC) CompressionMode;
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DIAG_NRC_RCRRP;

    Status = Decrypt_GetStatus();
    if( Status == DECRYPT_IDLE )
    {
        Nrc = DIAG_NRC_GPF;

        JobResult = Decrypt_GetJobResult();
        if( JobResult == DECRYPT_JOB_OK )
        {
            CompressionMode = DiagSrv_GetCompressionMode();
            if( CompressionMode == (uint8)STD_ON )
            {
                Nrc = DiagSrv_0x36_StartDecompress();
            }
            else
            {
                Nrc = DiagSrv_0x36_WritePlaintext();
            }
        }
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x36_Time_Decmp                                    */
/* Description   | Time of DIAGSRV_0X36_STAT_WAIT_DECMP                       */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_ROOR                                             */
/*               |  DIAG_NRC_TDS                                              */
/*               |  DIAG_NRC_VTL                                              */
/*               |  DIAG_NRC_GPF                                              */
/*               |  other(Depends on UserCustom)                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x36_Time_Decmp (void)
{
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DiagSrv_0x36_Decompress();

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x36_Time_Write                                    */
/* Description   | Time of DIAGSRV_0X36_STAT_WAIT_WRITE                       */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_VTL                                              */
/*               |  DIAG_NRC_GPF                                              */
/*               |  other(Depends on UserCustom)                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x36_Time_Write (void)
{
    VAR(uint8, AUTOMATIC) Status;
    VAR(uint8, AUTOMATIC) JobResult;
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DIAG_NRC_GPF;

    Status = RpgLib_GetStatus();
    if( (Status == RPGLIB_UPDATEIDLE) || (Status == RPGLIB_UPDATECOMPLETE) )
    {
        JobResult = RpgLib_GetJobResult();
        if( JobResult == RPGLIB_JOB_OK )
        {
            Nrc = DiagSrv_0x36_WriteFinish();
            if( Nrc == DIAG_NRC_PR )
            {
                DiagSrv_0x36_Status = DIAGSRV_0X36_STAT_IDLE;
            }
        }
    }
    else if( Status == RPGLIB_UPDATEBUSY )
    {
        Nrc = DIAG_NRC_RCRRP;
    }
    else
    {
        /* No process */
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x36_Time_DecmpWrite                               */
/* Description   | Time of DIAGSRV_0X36_STAT_WAIT_DECMP_WRITE                 */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GPF                                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x36_Time_DecmpWrite (void)
{
    VAR(uint8, AUTOMATIC) Status;
    VAR(uint8, AUTOMATIC) JobResult;
    VAR(uint8, AUTOMATIC) DeviceType;
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DIAG_NRC_GPF;

    Status = RpgLib_GetStatus();
    if( (Status == RPGLIB_UPDATEIDLE) || (Status == RPGLIB_UPDATECOMPLETE) )
    {
        JobResult = RpgLib_GetJobResult();
        if( JobResult == RPGLIB_JOB_OK )
        {
            DiagSrv_0x36_SizeInfo.WrittenSize += DiagSrv_0x36_SizeInfo.ReqWriteSize;    /* no wrap around */

            DeviceType = DiagSrv_GetWriteDeviceType();
            if( DeviceType == DIAGSRV_DEVICE_TYPE_CODERAM )
            {
                DiagSrv_0x36_VerifyInfo.AvailableSize += DiagSrv_0x36_SizeInfo.ReqWriteSize;    /* no wrap around */
            }
            else
            {
                /* No process */
                /* For CODEFLS, the write request size and the written size are different(for write alignment). */
                /* So, the verification size will be calculated later (= DiagSrv_0x36_WriteFinish).             */
                /* For EXTROM, verification is processed in SID 0x31, so "AvailableSize" is always 0.           */
            }

            DiagSrv_0x36_Status = DIAGSRV_0X36_STAT_WAIT_DECMP;
            Nrc = DIAG_NRC_RCRRP;
        }
    }
    else if( Status == RPGLIB_UPDATEBUSY )
    {
        Nrc = DIAG_NRC_RCRRP;
    }
    else
    {
        /* No process */
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x36_Time_SigVerify                                */
/* Description   | Time of DIAGSRV_0X36_STAT_WAIT_SIGVERIFY                   */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GPF                                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x36_Time_SigVerify (void)
{
#if 0	/* @@@ */
    VAR(uint8, AUTOMATIC) Status;
    VAR(uint8, AUTOMATIC) JobResult;
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DIAG_NRC_RCRRP;

    Status = FscDtct_GetStatus();
    if( Status == FSCDTCT_IDLE )
    {
        Nrc = DIAG_NRC_GPF;

        JobResult = FscDtct_GetJobResult();
        if( JobResult == FSCDTCT_JOB_OK )
        {
            Nrc = DIAG_NRC_PR;
        }
    }

#endif	/* @@@ */
    return DIAG_NRC_PR;	/* @@@ */
}

/******************************************************************************/
/* Function Name | DiagSrv_0x36_CheckMsg                                      */
/* Description   | Check request message                                      */
/* Preconditions |                                                            */
/* Parameters    | [IN] RewriteStatus : Rewrite Status                        */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_IMLOIF                                           */
/*               |  DIAG_NRC_RSE                                              */
/*               |  other(Depends on parallel processing result)              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x36_CheckMsg
(
    VAR(uint8, AUTOMATIC) RewriteStatus
)
{
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DiagSrv_0x36_ParallelInfo.Nrc;
    if( Nrc == DIAG_NRC_PR )
    {
        Nrc = DIAG_NRC_IMLOIF;

        if( DiagSrv_0x36_Msg->ReqDataLen >= DIAGSRV_0X36_REQ_DOWNLOAD_MSG_MIN_LEN )
        {
            Nrc = DIAG_NRC_RSE;

            if( (RewriteStatus == DIAGSRV_REWRITESTAT_SBL_DL_START) ||
                (RewriteStatus == DIAGSRV_REWRITESTAT_SBL_DL_UPDATE) ||
                (RewriteStatus == DIAGSRV_REWRITESTAT_DATA_DL_START) ||
                (RewriteStatus == DIAGSRV_REWRITESTAT_DATA_DL_UPDATE) )
            {
                Nrc = DIAG_NRC_PR;
            }
        }
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x36_CheckSameBSC                                  */
/* Description   | Check same BSC                                             */
/* Preconditions |                                                            */
/* Parameters    | [IN] RewriteStatus : Rewrite Status                        */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_WBSC                                             */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x36_CheckSameBSC
(
    VAR(uint8, AUTOMATIC) RewriteStatus
)
{
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DIAG_NRC_WBSC;

    if( ((RewriteStatus == DIAGSRV_REWRITESTAT_SBL_DL_UPDATE) || (RewriteStatus == DIAGSRV_REWRITESTAT_DATA_DL_UPDATE)) &&
        (DiagSrv_0x36_Msg->ReqData[DIAGSRV_0X36_BSC_POS] == DiagSrv_0x36_Bsc) )
    {
        Nrc = DIAG_NRC_PR;
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x36_CheckBSC                                      */
/* Description   | Check BSC                                                  */
/* Preconditions |                                                            */
/* Parameters    | [IN] RewriteStatus : Rewrite Status                        */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_WBSC                                             */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x36_CheckBSC
(
    VAR(uint8, AUTOMATIC) RewriteStatus
)
{
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DIAG_NRC_WBSC;

    if( (RewriteStatus == DIAGSRV_REWRITESTAT_SBL_DL_START) ||
        (RewriteStatus == DIAGSRV_REWRITESTAT_DATA_DL_START) )
    {
        if( DiagSrv_0x36_Msg->ReqData[DIAGSRV_0X36_BSC_POS] == (uint8)0x01U )
        {
            Nrc = DIAG_NRC_PR;
        }
    }
    else
    {
        if( DiagSrv_0x36_Msg->ReqData[DIAGSRV_0X36_BSC_POS] == (uint8)(DiagSrv_0x36_Bsc + (uint8)0x01U) )
        {
            Nrc = DIAG_NRC_PR;
        }
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x36_CalcPaddingSize                               */
/* Description   | Calculate padding size                                     */
/* Preconditions |                                                            */
/* Parameters    | [IN] TotalSize : Total data size                           */
/* Return Value  | Padding size                                               */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x36_CalcPaddingSize
(
    VAR(uint32, AUTOMATIC) TotalSize
)
{
    VAR(uint8, AUTOMATIC) CipherTextMode;
    VAR(uint8, AUTOMATIC) PaddingSize;

    PaddingSize = 0U;

    CipherTextMode = DiagSrv_GetCipherTextMode();
    if( CipherTextMode == (uint8)STD_ON )
    {
        PaddingSize = DIAGSRV_0X36_PADDING_SIZE_16
                    - (uint8)(TotalSize & (DIAGSRV_0X36_PADDING_SIZE_16 - (uint8)1U));
    }

    return PaddingSize;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x36_CheckPaddingData                              */
/* Description   | Check padding data                                         */
/* Preconditions |                                                            */
/* Parameters    | [IN] Buf         : Buffer                                  */
/*               | [IN] PaddingSize : Padding Size                            */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_ROOR                                             */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x36_CheckPaddingData
(
    CONST(uint8, AUTOMATIC) Buf[],
    VAR(uint8, AUTOMATIC) PaddingSize
)
{
    VAR(uint8, AUTOMATIC) i;
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DIAG_NRC_PR;

    for( i = 0U; i < PaddingSize; i++ )
    {
        if( Buf[i] != PaddingSize )
        {
            Nrc = DIAG_NRC_ROOR;
            break;
        }
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x36_CheckMNOBL                                    */
/* Description   | Check MNOBL                                                */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_ROOR                                             */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x36_CheckMNOBL (void)
{
    VAR(uint32, AUTOMATIC) MaxNumberOfBlockLength;
    VAR(uint32, AUTOMATIC) RecordSize;
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DIAG_NRC_PR;

    MaxNumberOfBlockLength = DiagLib_GetMNOBL();
    MaxNumberOfBlockLength -= (DIAGSRV_0X36_SID_LEN + DIAGSRV_0X36_BSC_LEN);            /* no wrap around */
    RecordSize = DIAGSRV_0X36_GET_REQ_PARAM_LEN((uint32)DiagSrv_0x36_Msg->ReqDataLen);  /* no wrap around */

    if( DiagSrv_0x36_SizeInfo.TransferRemainSize != (uint32)0UL )
    {
        if( RecordSize != MaxNumberOfBlockLength )
        {
            Nrc = DIAG_NRC_ROOR;
        }
    }
    else
    {
        if( RecordSize > MaxNumberOfBlockLength )
        {
            Nrc = DIAG_NRC_ROOR;
        }
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x36_CheckCondition                                */
/* Description   | Check the following conditions                             */
/*               |  - data is correctly altered                               */
/*               |  - voltage condition                                       */
/*               |  - manufacturer or supplier specific                       */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_VTL                                              */
/*               |  DIAG_NRC_GPF                                              */
/*               |  other(Depends on UserCustom)                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x36_CheckCondition (void)
{
    VAR(uint16, AUTOMATIC) Volt;
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(Std_ReturnType, AUTOMATIC) GetVoltRet;

    Nrc = DIAG_NRC_GPF;

    Volt = 0U;
    GetVoltRet = VehInf_GetVoltForDataWrite(&Volt);
    if( GetVoltRet == (Std_ReturnType)E_OK )
    {
        Nrc = RpgMfr_VoltCheckConditionForDataWrite(Volt);
        if( Nrc == DIAG_NRC_PR )
        {
            Nrc = RpgMfr_MsgCheckCondition(DiagSrv_0x36_Msg);
            if( Nrc == DIAG_NRC_PR )
            {
                Nrc = RpgSpp_MsgCheckCondition(DiagSrv_0x36_Msg);
            }
        }
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x36_UpdateTargetAreaInfo                          */
/* Description   | Update target area address and size                        */
/* Preconditions |                                                            */
/* Parameters    | [IN] RewriteStatus : Rewrite status                        */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x36_UpdateTargetAreaInfo
(
    VAR(uint8, AUTOMATIC) RewriteStatus
)
{
    VAR(uint8, AUTOMATIC) RewriteAreaNum;
    VAR(uint8, AUTOMATIC) CalcSize;

    CalcSize = STD_OFF;

    if( RewriteStatus == DIAGSRV_REWRITESTAT_SBL_DL_START )
    {
        /* SBL */
        DiagSrv_0x36_VerifyInfo.StartAddr = 0UL;

        DiagSrv_GetSblAreaInfo(&DiagSrv_0x36_VerifyInfo.StartAddr,
                            &DiagSrv_0x36_SizeInfo.TargetAreaSize);

        CalcSize = STD_ON;
    }
    else if( RewriteStatus == DIAGSRV_REWRITESTAT_DATA_DL_START )
    {
        /* Rewriting Data */
        DiagSrv_0x36_VerifyInfo.StartAddr = 0UL;
        RewriteAreaNum = DiagSrv_GetRewriteAreaNumber();

        DiagSrv_GetRewriteAreaInfo(RewriteAreaNum,
                                &DiagSrv_0x36_VerifyInfo.StartAddr,
                                &DiagSrv_0x36_SizeInfo.TargetAreaSize);

        CalcSize = STD_ON;
    }
    else
    {
        /* No process */
    }

    if( CalcSize == (uint8)STD_ON )
    {
        /* Calculate the size once at this timing.                                       */
        /* For compressed data, overwrite the data again (DiagSrv_0x36_StartDecompress). */
        DiagSrv_0x36_SizeInfo.PaddingSize = DiagSrv_0x36_CalcPaddingSize(DiagSrv_0x36_SizeInfo.TargetAreaSize);
        DiagSrv_0x36_SizeInfo.TransferRemainSize = DiagSrv_0x36_SizeInfo.TargetAreaSize + DiagSrv_0x36_SizeInfo.PaddingSize;    /* no wrap around */
    }

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x36_UpdateParallelInfo                            */
/* Description   | Update parallel information                                */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x36_UpdateParallelInfo (void)
{
    if( DiagSrv_0x36_ParallelInfo.WaitMsg != NULL_PTR )
    {
        DiagSrv_0x36_Status = DIAGSRV_0X36_STAT_RECEPTION;
        DiagSrv_0x36_Msg = DiagSrv_0x36_ParallelInfo.WaitMsg;
        DiagSrv_0x36_ParallelInfo.WaitMsg = NULL_PTR;
    }
    else
    {
        DiagSrv_0x36_Status = DIAGSRV_0X36_STAT_IDLE;
    }

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x36_ExecuteTransferData                           */
/* Description   | Execute TransferData message                               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x36_ExecuteTransferData (void)
{
    VAR(uint8, AUTOMATIC) CompressionMode;
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DiagSrv_0x36_DecryptCiphertext();
    if( Nrc == DIAG_NRC_PR )
    {
        CompressionMode = DiagSrv_GetCompressionMode();
        if( CompressionMode == (uint8)STD_ON )
        {
            Nrc = DiagSrv_0x36_StartDecompress();
        }
        else
        {
            Nrc = DiagSrv_0x36_WritePlaintext();
        }
    }

    if( Nrc != DIAG_NRC_RCRRP ) /* Not return DIAG_NRC_PR here. */
    {
        if( ReprogOpt_ParallelConfig == (uint8)STD_ON )
        {
            DiagSrv_0x36_UpdateParallelInfo();
            DiagSrv_0x36_ParallelInfo.Nrc = Nrc;
        }
        else
        {
            DiagSrv_0x36_TransferFailed(Nrc);
        }
    }

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x36_DecryptCiphertext                             */
/* Description   | Decrypt ciphertext                                         */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_RCRRP                                            */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x36_DecryptCiphertext (void)
{
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(uint8, AUTOMATIC) CipherTextMode;

    Nrc = DIAG_NRC_PR;

    CipherTextMode = DiagSrv_GetCipherTextMode();
    if( CipherTextMode == (uint8)STD_ON )
    {
        Decrypt_ReqDecode(&DiagSrv_0x36_Msg->ReqData[DIAGSRV_0X36_TRTP1_POS],
                        &DiagSrv_0x36_Msg->ReqData[DIAGSRV_0X36_TRTP1_POS],
                        DIAGSRV_0X36_GET_REQ_PARAM_LEN(DiagSrv_0x36_Msg->ReqDataLen));

        DiagSrv_0x36_Status = DIAGSRV_0X36_STAT_WAIT_DECODE;
        Nrc = DIAG_NRC_RCRRP;
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x36_WritePlaintext                                */
/* Description   | Write plaintext                                            */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_ROOR                                             */
/*               |  DIAG_NRC_TDS                                              */
/*               |  DIAG_NRC_VTL                                              */
/*               |  DIAG_NRC_GPF                                              */
/*               |  other(Depends on UserCustom)                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x36_WritePlaintext (void)
{
    VAR(uint32, AUTOMATIC) CurrentDataSize;
    VAR(uint32, AUTOMATIC) CurrentWriteSize;
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DIAG_NRC_ROOR;

    CurrentDataSize = DIAGSRV_0X36_GET_REQ_PARAM_LEN((uint32)DiagSrv_0x36_Msg->ReqDataLen); /* no wrap around */
    if( DiagSrv_0x36_SizeInfo.TransferRemainSize >= CurrentDataSize )
    {
        Nrc = DIAG_NRC_PR;
        CurrentWriteSize = CurrentDataSize;

        DiagSrv_0x36_SizeInfo.TransferRemainSize -= CurrentDataSize;
        if( DiagSrv_0x36_SizeInfo.TransferRemainSize == (uint32)0UL )
        {
            /* Call the function even in plaintext(Padding = 0). */
            Nrc = DiagSrv_0x36_CheckPaddingData(&DiagSrv_0x36_Msg->ReqData[DiagSrv_0x36_Msg->ReqDataLen - DiagSrv_0x36_SizeInfo.PaddingSize],
                                                DiagSrv_0x36_SizeInfo.PaddingSize);
            if( Nrc == DIAG_NRC_PR )
            {
                CurrentWriteSize -= DiagSrv_0x36_SizeInfo.PaddingSize;  /* no wrap around */
            }
        }
    }

    if( Nrc == DIAG_NRC_PR )
    {
        if( CurrentWriteSize > (uint32)0UL )
        {
            Nrc = DIAG_NRC_TDS;

            if( DiagSrv_0x36_SizeInfo.TargetAreaSize >= (DiagSrv_0x36_SizeInfo.WrittenSize + CurrentWriteSize) )    /* no wrap around */
            {
                Nrc = DiagSrv_0x36_CheckMNOBL();
                if( Nrc == DIAG_NRC_PR )
                {
                    Nrc = DiagSrv_0x36_WriteMemUpdate(&DiagSrv_0x36_Msg->ReqData[DIAGSRV_0X36_TRTP1_POS], CurrentWriteSize);
                    if( Nrc == DIAG_NRC_RCRRP )
                    {
                        DiagSrv_0x36_Status = DIAGSRV_0X36_STAT_WAIT_WRITE;
                    }
                }
            }
        }
        else
        {
            /* This route is when TransferData is only padding. */
            Nrc = DiagSrv_0x36_PostTransfer();
        }
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x36_StartDecompress                               */
/* Description   | Start decompress                                           */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_ROOR                                             */
/*               |  DIAG_NRC_TDS                                              */
/*               |  DIAG_NRC_VTL                                              */
/*               |  DIAG_NRC_GPF                                              */
/*               |  other(Depends on UserCustom)                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x36_StartDecompress (void)
{
    P2CONST(uint8, AUTOMATIC, DIAGSRV_APPL_CONST) CmpDataAddr;
    VAR(uint32, AUTOMATIC) CmpDataSize;
    VAR(uint32, AUTOMATIC) CurrentDataSize;
    VAR(uint32, AUTOMATIC) TotalDataSize;
    VAR(uint32, AUTOMATIC) ParamCmpDataSize;
    VAR(uint8, AUTOMATIC) RewriteStatus;
    VAR(uint8, AUTOMATIC) CipherTextMode;
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DIAG_NRC_PR;

    CurrentDataSize = DIAGSRV_0X36_GET_REQ_PARAM_LEN((uint32)DiagSrv_0x36_Msg->ReqDataLen); /* no wrap around */
    CmpDataAddr = &DiagSrv_0x36_Msg->ReqData[DIAGSRV_0X36_TRTP1_POS];
    CmpDataSize = CurrentDataSize;

    RewriteStatus = DiagSrv_GetRewriteStatus();
    if( (RewriteStatus == DIAGSRV_REWRITESTAT_SBL_DL_START) || (RewriteStatus == DIAGSRV_REWRITESTAT_DATA_DL_START) )
    {
        Nrc = DIAG_NRC_ROOR;

        if( CurrentDataSize >= DIAGSRV_0x36_CMP_INFOMATION_LEN )
        {
            /* Calculate the total transfer size from the compressed data length in the first data */
            ParamCmpDataSize = Rte_Rpg_ByteCombine(&DiagSrv_0x36_Msg->ReqData[DIAGSRV_0X36_TRTP1_POS],
                                                    (uint8)DIAGSRV_0x36_TOTAL_CMP_SIZE_PARAM_LEN);
            if( ParamCmpDataSize > 0UL )
            {
                DiagSrv_0x36_SizeInfo.TotalCmpDataSize = ParamCmpDataSize;
                TotalDataSize = DIAGSRV_0x36_CMP_INFOMATION_LEN + ParamCmpDataSize; /* no wrap around */

                /* Since compressed data, overwrite the data again. */
                DiagSrv_0x36_SizeInfo.PaddingSize = DiagSrv_0x36_CalcPaddingSize(TotalDataSize);
                DiagSrv_0x36_SizeInfo.TransferRemainSize = TotalDataSize + DiagSrv_0x36_SizeInfo.PaddingSize;   /* no wrap around */

                /* Exclude the first 16 bytes (compressed information) of the transferred data */
                CmpDataAddr = &DiagSrv_0x36_Msg->ReqData[DIAGSRV_0X36_TRTP1_POS + DIAGSRV_0x36_CMP_INFOMATION_LEN];
                CmpDataSize -= DIAGSRV_0x36_CMP_INFOMATION_LEN; /* no wrap around */

                Nrc = DIAG_NRC_PR;
            }
        }
    }

    if( Nrc == DIAG_NRC_PR )
    {
        Nrc = DIAG_NRC_ROOR;

        if( DiagSrv_0x36_SizeInfo.TransferRemainSize >= CurrentDataSize )
        {
            Nrc = DIAG_NRC_PR;

            DiagSrv_0x36_SizeInfo.TransferRemainSize -= CurrentDataSize;

            CipherTextMode = DiagSrv_GetCipherTextMode();
            if( CipherTextMode == (uint8)STD_ON )
            {
                if( DiagSrv_0x36_SizeInfo.TransferRemainSize == (uint32)0UL )
                {
                    Nrc = DiagSrv_0x36_CheckPaddingData(&DiagSrv_0x36_Msg->ReqData[DiagSrv_0x36_Msg->ReqDataLen - DiagSrv_0x36_SizeInfo.PaddingSize],
                                                        DiagSrv_0x36_SizeInfo.PaddingSize);
                    if( Nrc == DIAG_NRC_PR )
                    {
                        /* Exclude padding data */
                        CmpDataSize -= DiagSrv_0x36_SizeInfo.PaddingSize;   /* no wrap around */
                    }
                }
            }
        }
    }

    if( Nrc == DIAG_NRC_PR )
    {
        if( CmpDataSize > (uint32)0UL )
        {
            /* Setting of decompression start information. */
            DiagSrv_0x36_DecmpInfo.Op = CMPDECMP_DECMP_START;
            DiagSrv_0x36_DecmpInfo.Info.CompData = CmpDataAddr;
            DiagSrv_0x36_DecmpInfo.Info.CompDataSize = CmpDataSize;
            DiagSrv_0x36_DecmpInfo.Info.CompDataTotalSize = DiagSrv_0x36_SizeInfo.TotalCmpDataSize;
            DiagSrv_0x36_DecmpInfo.Info.DecompBuf = NULL_PTR;
            DiagSrv_0x36_DecmpInfo.Info.DecompResultSize = 0UL;

            Nrc = DiagSrv_0x36_Decompress();
        }
        else
        {
            /* This route is when TransferData is only padding. */
            Nrc = DiagSrv_0x36_PostTransfer();
        }
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x36_Decompress                                    */
/* Description   | Decompression                                              */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_ROOR                                             */
/*               |  DIAG_NRC_TDS                                              */
/*               |  DIAG_NRC_VTL                                              */
/*               |  DIAG_NRC_GPF                                              */
/*               |  other(Depends on UserCustom)                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x36_Decompress (void)
{
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(Std_ReturnType, AUTOMATIC) DecompRet;

    Nrc = DIAG_NRC_GPF;

    DecompRet = CmpDecmp_Decompress(DiagSrv_0x36_DecmpInfo.Op, &DiagSrv_0x36_DecmpInfo.Info);
    if( DecompRet == CMPDECMP_E_PENDING )
    {
        DiagSrv_0x36_Status = DIAGSRV_0X36_STAT_WAIT_DECMP;

        Nrc = DIAG_NRC_RCRRP;
    }
    else if( (DecompRet == (Std_ReturnType)E_OK) || (DecompRet == CMPDECMP_E_SUSPEND) )
    {
        Nrc = DIAG_NRC_TDS;

        if( DiagSrv_0x36_SizeInfo.TargetAreaSize >= (DiagSrv_0x36_SizeInfo.WrittenSize + DiagSrv_0x36_DecmpInfo.Info.DecompResultSize) )    /* no wrap around */
        {
            Nrc = DiagSrv_0x36_WriteDecompressData(DecompRet);
        }
    }
    else
    {
        /* No Process */
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x36_WriteDecompressData                           */
/* Description   | Write decompress data                                      */
/* Preconditions |                                                            */
/* Parameters    | [IN] DecmpResult : Return value of CmpDecmp_Decompress()   */
/*               |       E_OK                                                 */
/*               |       CMPDECMP_E_SUSPEND                                   */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_ROOR                                             */
/*               |  DIAG_NRC_VTL                                              */
/*               |  DIAG_NRC_GPF                                              */
/*               |  other(Depends on UserCustom)                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x36_WriteDecompressData
(
    VAR(Std_ReturnType, AUTOMATIC) DecmpResult
)
{
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DIAG_NRC_PR;

    if( DecmpResult == (Std_ReturnType)E_OK )
    {
        Nrc = DiagSrv_0x36_CheckMNOBL();
    }

    if( Nrc == DIAG_NRC_PR )
    {
        if( DiagSrv_0x36_DecmpInfo.Info.DecompResultSize > 0UL )
        {
            Nrc = DiagSrv_0x36_WriteMemUpdate(DiagSrv_0x36_DecmpInfo.Info.DecompBuf,
                                            DiagSrv_0x36_DecmpInfo.Info.DecompResultSize);
            if( Nrc == DIAG_NRC_RCRRP )
            {
                if( DecmpResult == (Std_ReturnType)E_OK )
                {
                    DiagSrv_0x36_Status = DIAGSRV_0X36_STAT_WAIT_WRITE;
                }
                else
                {
                    /* Setting of decompression restart information. */
                    /* The following is already set at the start,    */
                    /* so there is no need to update.                */
                    /*  - CompData                                   */
                    /*  - CompDataSize                               */
                    /*  - CompDataTotalSize                          */
                    DiagSrv_0x36_DecmpInfo.Op = CMPDECMP_DECMP_RESUME;
                    DiagSrv_0x36_DecmpInfo.Info.DecompBuf = NULL_PTR;
                    DiagSrv_0x36_DecmpInfo.Info.DecompResultSize = 0UL;

                    DiagSrv_0x36_Status = DIAGSRV_0X36_STAT_WAIT_DECMP_WRITE;
                }
            }
        }
        else
        {
            Nrc = DIAG_NRC_GPF;

            if( DecmpResult == (Std_ReturnType)E_OK )
            {
                /* All compressed data has been written, so exit without writing. */
                DiagSrv_0x36_SizeInfo.ReqWriteSize = 0UL;

                Nrc = DiagSrv_0x36_WriteFinish();
                if( Nrc == DIAG_NRC_PR )
                {
                    DiagSrv_0x36_Status = DIAGSRV_0X36_STAT_IDLE;
                }
            }
        }
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x36_WriteMemUpdate                                */
/* Description   | Requests RpgLib to update writing                          */
/* Preconditions |                                                            */
/* Parameters    | [IN] SrcAddr : Source address                              */
/*               | [IN] Size    : Write size                                  */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GPF                                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x36_WriteMemUpdate
(
    P2CONST(uint8, AUTOMATIC, DIAGSRV_APPL_CONST) SrcAddr,
    VAR(uint32, AUTOMATIC) Size
)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DIAG_NRC_GPF;

    FuncRet = RpgLib_ReqWriteMemUpdate(SrcAddr, Size);
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        DiagSrv_0x36_SizeInfo.ReqWriteSize = Size;

        Nrc = DIAG_NRC_RCRRP;
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x36_WriteFinish                                   */
/* Description   | Writing finish processing of transfer data                 */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_VTL                                              */
/*               |  DIAG_NRC_GPF                                              */
/*               |  other(Depends on UserCustom)                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x36_WriteFinish (void)
{
    VAR(uint32, AUTOMATIC) NextWriteAddr;
    VAR(uint8, AUTOMATIC) DeviceType;
    VAR(uint8, AUTOMATIC) Nrc;

    DiagSrv_0x36_SizeInfo.WrittenSize += DiagSrv_0x36_SizeInfo.ReqWriteSize;    /* no wrap around */

    DeviceType = DiagSrv_GetWriteDeviceType();
    if( DeviceType == DIAGSRV_DEVICE_TYPE_CODEFLS )
    {
        /* For CODEFLS, the write request size and the written size are different(for write alignment). */
        /* So, use the written size as the verification size.                                           */
        NextWriteAddr = RpgLib_GetNextWriteAddr();
        DiagSrv_0x36_VerifyInfo.AvailableSize = NextWriteAddr - DiagSrv_0x36_ParallelInfo.CodeFlsStartAddr; /* no wrap around */
    }
    else if( DeviceType == DIAGSRV_DEVICE_TYPE_CODERAM )
    {
        DiagSrv_0x36_VerifyInfo.AvailableSize += DiagSrv_0x36_SizeInfo.ReqWriteSize;    /* no wrap around */
    }
    else
    {
        /* For EXTROM, verification is processed in SID 0x31, so "AvailableSize" is always 0. */
        DiagSrv_0x36_VerifyInfo.AvailableSize = 0UL;
    }

    Nrc = DiagSrv_0x36_PostTransfer();
    if( Nrc == DIAG_NRC_PR )
    {
        if( ReprogOpt_ParallelConfig == (uint8)STD_ON )
        {
            Nrc = DiagSrv_0x36_SigVerify();
        }
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x36_PostTransfer                                  */
/* Description   | Post-transfer processing                                   */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_VTL                                              */
/*               |  DIAG_NRC_GPF                                              */
/*               |  other(Depends on UserCustom)                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x36_PostTransfer (void)
{
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DiagSrv_0x36_CheckCondition();
    if( Nrc == DIAG_NRC_PR )
    {
        DiagSrv_0x36_TransferSuccess();
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x36_SigVerify                                     */
/* Description   | Signature verification                                     */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_RCRRP                                            */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x36_SigVerify (void)
{
    VAR(uint8, AUTOMATIC) Nrc;

#if 0	/* @@@ */
    Nrc = DIAG_NRC_PR;

    if( DiagSrv_0x36_VerifyInfo.AvailableSize > (uint32)0UL )
    {
        FscDtct_ReqSigVerify(DiagSrv_0x36_VerifyInfo.StartAddr,
                            DiagSrv_0x36_VerifyInfo.AvailableSize);

        DiagSrv_0x36_VerifyInfo.StartAddr += DiagSrv_0x36_VerifyInfo.AvailableSize; /* no wrap around */

        DiagSrv_0x36_Status = DIAGSRV_0X36_STAT_WAIT_SIGVERIFY;
        Nrc = DIAG_NRC_RCRRP;
    }
#endif	/* @@@ */
    DiagSrv_0x36_Status = DIAGSRV_0X36_STAT_WAIT_SIGVERIFY;	/* @@@ */
    Nrc = DIAG_NRC_RCRRP;	/* @@@ */

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x36_TransferSuccess                               */
/* Description   | Series of processing executed when transfer succeeded      */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x36_TransferSuccess (void)
{
    VAR(uint8, AUTOMATIC) RewriteStatus;

    DiagSrv_0x36_Bsc = DiagSrv_0x36_Msg->ReqData[DIAGSRV_0X36_BSC_POS];

    RewriteStatus = DiagSrv_GetRewriteStatus();
    if( RewriteStatus == DIAGSRV_REWRITESTAT_SBL_DL_START )
    {
        RewriteStatus = DIAGSRV_REWRITESTAT_SBL_DL_UPDATE;
        DiagSrv_SetRewriteStatus(RewriteStatus);
    }
    else if( RewriteStatus == DIAGSRV_REWRITESTAT_DATA_DL_START )
    {
        RewriteStatus = DIAGSRV_REWRITESTAT_DATA_DL_UPDATE;
        DiagSrv_SetRewriteStatus(RewriteStatus);
    }
    else
    {
        /* No process */
    }

    if( DiagSrv_0x36_SizeInfo.WrittenSize == DiagSrv_0x36_SizeInfo.TargetAreaSize )
    {
        if( DiagSrv_0x36_SizeInfo.TransferRemainSize == (uint32)0UL )
        {
            if( RewriteStatus == DIAGSRV_REWRITESTAT_SBL_DL_UPDATE )
            {
                DiagSrv_SetRewriteStatus(DIAGSRV_REWRITESTAT_SBL_DL_END);
            }
            else if( RewriteStatus == DIAGSRV_REWRITESTAT_DATA_DL_UPDATE )
            {
                DiagSrv_SetRewriteStatus(DIAGSRV_REWRITESTAT_DATA_DL_END);
            }
            else
            {
                /* No process */
            }
        }
    }

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x36_TransferFailed                                */
/* Description   | Series of processing executed when transfer failed         */
/* Preconditions |                                                            */
/* Parameters    | [IN] Nrc : NRC                                             */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x36_TransferFailed
(
    VAR(uint8, AUTOMATIC) Nrc
)
{
    VAR(uint8, AUTOMATIC) RewriteAreaNum;

    RewriteAreaNum = DiagSrv_GetRewriteAreaNumber();

    DiagSrv_SetRewriteAreaStatus(RewriteAreaNum, DIAGSRV_LBSTAT_REWRITING_NG);

    DiagSrv_SetRewriteStatus(DIAGSRV_REWRITESTAT_IDLE);

    DiagLib_SendNegRsp(Nrc, DiagSrv_0x36_Msg);

    DiagSrv_0x36_ClearInfo();

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x36_SendPosRsp                                    */
/* Description   | Send positive response                                     */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x36_SendPosRsp (void)
{
    DiagSrv_0x36_Msg->ResData[DIAGSRV_0X36_SID_POS] = DIAG_MAKE_POSRSP_SID(DiagSrv_0x36_Msg);
    DiagSrv_0x36_Msg->ResData[DIAGSRV_0X36_BSC_POS] = DiagSrv_0x36_Msg->ReqData[DIAGSRV_0X36_BSC_POS];

    DiagSrv_0x36_Msg->ResDataLen = DIAGSRV_0X36_RSP_DOWNLOAD_MSG_LEN;

    DiagLib_SendPosRsp(DiagSrv_0x36_Msg);

    return;
}


#define DIAGSRV_STOP_SEC_CODE
#include <DiagSrv_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/06/07 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

