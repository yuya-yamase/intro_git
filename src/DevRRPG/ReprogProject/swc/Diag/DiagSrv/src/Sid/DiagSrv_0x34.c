/* DiagSrv_0x34_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagSrv/0x34/CODE                                           */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <CmpDecmp.h>
#include <Decrypt.h>
#include <DiagLib.h>
#include <FscDtct.h>
#include <RpgLib.h>
#include <RpgMfr.h>
#include <RpgSpp.h>
#include <Rte.h>

#include <DiagSrv.h>
#include "DiagSrv_0x34.h"
#include "DiagSrv_0x34_Cfg.h"
#include "DiagSrv_0x36.h"
#include "DiagSrv_Local.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/* Job Status */
#define DIAGSRV_0X34_STAT_IDLE                  ((uint8)0x00U)
#define DIAGSRV_0X34_STAT_WAIT_PREDEC           ((uint8)0x01U)
#define DIAGSRV_0X34_STAT_WAIT_PREDECMP         ((uint8)0x02U)
#define DIAGSRV_0X34_STAT_WAIT_PRE_FSCDTCT      ((uint8)0x03U)

/* Data Length */
#define DIAGSRV_0X34_REQ_MSG_MIN_LEN            ((uint8)5U)
#define DIAGSRV_0X34_SID_TO_ALFID_LEN           ((uint8)3U)
#define DIAGSRV_0X34_SID_TO_MNROB_B4_LEN        ((uint8)6U)

/* Message Parameter Position */
#define DIAGSRV_0X34_MEM_ADDR_POS               ((uint8)3U)
#define DIAGSRV_0X34_DFI_POS                    ((uint8)1U)
#define DIAGSRV_0X34_ALFID_POS                  ((uint8)2U)
#define DIAGSRV_0X34_SID_POS                    ((uint8)0U)
#define DIAGSRV_0X34_LFID_POS                   ((uint8)1U)
#define DIAGSRV_0X34_MNROB_B1_POS               ((uint8)2U)
#define DIAGSRV_0X34_MNROB_B2_POS               ((uint8)3U)
#define DIAGSRV_0X34_MNROB_B3_POS               ((uint8)4U)
#define DIAGSRV_0X34_MNROB_B4_POS               ((uint8)5U)

/* Length Format Identifier */
#define DIAGSRV_0X34_LFID_MNROB_4BYTE           ((uint8)0x40U)

/* Bit Calculation */
#define DIAGSRV_0X34_BIT_SHIFT_4                ((uint8)4U)
#define DIAGSRV_0X34_BIT_SHIFT_8                ((uint8)8U)
#define DIAGSRV_0X34_BIT_SHIFT_16               ((uint8)16U)
#define DIAGSRV_0X34_BIT_SHIFT_24               ((uint8)24U)
#define DIAGSRV_0X34_ALFID_LOW_MASK             ((uint8)0x0FU)
#define DIAGSRV_0X34_DFI_LOW_MASK               ((uint8)0x0FU)
#define DIAGSRV_0X34_DFI_HIGH_MASK              ((uint8)0xF0U)
#define DIAGSRV_0X34_MNOBL_LOW_MASK             ((uint16)0x00FFU)

/* Encryption Mode */
#define DIAGSRV_0X34_METHOD_CIPHER              ((uint8)0x01U)

/* Compression Mode */
#define DIAGSRV_0X34_METHOD_COMPRESSION         ((uint8)0x10U)

/* Memory Area */
#define DIAGSRV_0x34_MEM_INVALID_AREA           ((uint8)0x00U)
#define DIAGSRV_0x34_MEM_REWRITE_AREA           ((uint8)0x01U)
#define DIAGSRV_0x34_MEM_SBL_AREA               ((uint8)0x02U)

/* Address And Length Format Identifier */
#define DIAGSRV_0X34_CONVERT_ALFID_TO_SIZE_LENGTH(alfid)     ((alfid) >> DIAGSRV_0X34_BIT_SHIFT_4)
#define DIAGSRV_0X34_CONVERT_ALFID_TO_ADDRESS_LENGTH(alfid)  ((alfid) & DIAGSRV_0X34_ALFID_LOW_MASK)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x34_ClearInfo (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x34_Time_PreDecode (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x34_Time_PreDecmp (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x34_Time_PreFscDtct (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x34_CheckReqMsg (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x34_CheckDfi
(
    VAR(uint8, AUTOMATIC) ReqDfi
);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x34_CheckAlfid
(
    VAR(uint8, AUTOMATIC) ReqAlfid
);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x34_CheckMemArea
(
    VAR(uint32, AUTOMATIC) MemoryAddr,
    VAR(uint32, AUTOMATIC) MemorySize,
    P2VAR(uint8, AUTOMATIC, DIAGSRV_APPL_DATA) MemoryArea
);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x34_CheckRewriteStatus
(
    VAR(uint8, AUTOMATIC) MemoryArea
);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x34_CheckCondition (void);
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x34_SetInformation
(
    VAR(uint8, AUTOMATIC) ReqDfi,
    VAR(uint32, AUTOMATIC) MemoryAddr,
    VAR(uint32, AUTOMATIC) MemorySize
);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x34_PreTransferProcess (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x34_PreDecode (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x34_PreCommon (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x34_PreDecompress (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x34_PreSigVerify (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x34_WriteStart (void);
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x34_SendPosRsp (void);
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x34_SendNegRsp
(
    VAR(uint8, AUTOMATIC) Nrc
);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_VAR
#include <DiagSrv_MemMap.h>

static VAR(uint8, DIAGSRV_VAR_CLEARED) DiagSrv_0x34_Status;
static P2VAR(Diag_MsgContextType, DIAGSRV_VAR_CLEARED, DIAGSRV_APPL_DATA) DiagSrv_0x34_Msg;
static VAR(uint32, DIAGSRV_VAR_CLEARED) DiagSrv_0x34_WriteAddr;
static VAR(uint32, DIAGSRV_VAR_CLEARED) DiagSrv_0x34_WriteSize;
static VAR(uint8, DIAGSRV_VAR_CLEARED) DiagSrv_0x34_EncryptionMode;
static VAR(uint8, DIAGSRV_VAR_CLEARED) DiagSrv_0x34_CompressionMode;

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
/* Function Name | DiagSrv_0x34_Init                                          */
/* Description   | Initialize                                                 */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x34_Init (void)
{
    DiagSrv_0x34_ClearInfo();

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x34_Time                                          */
/* Description   | Time function                                              */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x34_Time (void)
{
    VAR(uint8, AUTOMATIC) Nrc;

    if( DiagSrv_0x34_Status != DIAGSRV_0X34_STAT_IDLE )
    {
        Nrc = DIAG_NRC_GR;

        if( DiagSrv_0x34_Status == DIAGSRV_0X34_STAT_WAIT_PREDEC )
        {
            Nrc = DiagSrv_0x34_Time_PreDecode();
        }
        else if( DiagSrv_0x34_Status == DIAGSRV_0X34_STAT_WAIT_PREDECMP )
        {
            Nrc = DiagSrv_0x34_Time_PreDecmp();
        }
        else if( DiagSrv_0x34_Status == DIAGSRV_0X34_STAT_WAIT_PRE_FSCDTCT )
        {
            Nrc = DiagSrv_0x34_Time_PreFscDtct();
        }
        else
        {
            /* No process */
        }

        if( Nrc == DIAG_NRC_RCRRP )
        {
            /* No process */
        }
        else if( Nrc == DIAG_NRC_PR )
        {
            DiagSrv_0x34_SendPosRsp();
        }
        else
        {
            DiagSrv_0x34_SendNegRsp(Nrc);
        }
    }

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x34_Processing                                    */
/* Description   | Processing function                                        */
/* Preconditions |                                                            */
/* Parameters    | [IN] Msg : Message                                         */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x34_Processing
(
    P2VAR(Diag_MsgContextType, AUTOMATIC, DIAGSRV_APPL_DATA) Msg
)
{
    VAR(uint32, AUTOMATIC) MemoryAddr;
    VAR(uint32, AUTOMATIC) MemorySize;
    VAR(uint8, AUTOMATIC) MemoryArea;
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(uint8, AUTOMATIC) ReqAlfid;
    VAR(uint8, AUTOMATIC) AddrLength;
    VAR(uint8, AUTOMATIC) SizeLength;

    DiagSrv_0x34_Msg = Msg;

    Nrc = DiagSrv_0x34_CheckReqMsg();
    if( Nrc == DIAG_NRC_PR )
    {
        ReqAlfid = DiagSrv_0x34_Msg->ReqData[DIAGSRV_0X34_ALFID_POS];
        AddrLength = DIAGSRV_0X34_CONVERT_ALFID_TO_ADDRESS_LENGTH(ReqAlfid);
        SizeLength = DIAGSRV_0X34_CONVERT_ALFID_TO_SIZE_LENGTH(ReqAlfid);

        MemoryAddr = Rte_Rpg_ByteCombine(&DiagSrv_0x34_Msg->ReqData[DIAGSRV_0X34_MEM_ADDR_POS],
                                        AddrLength);
        MemorySize = Rte_Rpg_ByteCombine(&DiagSrv_0x34_Msg->ReqData[DIAGSRV_0X34_SID_TO_ALFID_LEN + AddrLength],
                                        SizeLength);
        MemoryArea = DIAGSRV_0x34_MEM_INVALID_AREA;

        Nrc = DiagSrv_0x34_CheckMemArea(MemoryAddr, MemorySize, &MemoryArea);
        if( Nrc == DIAG_NRC_PR )
        {
            Nrc = DiagSrv_0x34_CheckRewriteStatus(MemoryArea);
            if( Nrc == DIAG_NRC_PR )
            {
                Nrc = DiagSrv_0x34_CheckCondition();
            }
        }

        if( Nrc == DIAG_NRC_PR )
        {
            DiagSrv_0x34_SetInformation(DiagSrv_0x34_Msg->ReqData[DIAGSRV_0X34_DFI_POS],
                                        MemoryAddr,
                                        MemorySize);

            DiagSrv_DisableChangePrgSession();

            Nrc = DiagSrv_0x34_PreTransferProcess();
        }
    }

    if( Nrc != DIAG_NRC_RCRRP )
    {
        DiagSrv_0x34_SendNegRsp(Nrc);
    }

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x34_Confirmation                                  */
/* Description   | Confirmation function                                      */
/* Preconditions |                                                            */
/* Parameters    | [IN] Status : Transmission complete status                 */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x34_Confirmation
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
/* Function Name | DiagSrv_0x34_ClearInfo                                     */
/* Description   | Clear information function                                 */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x34_ClearInfo (void)
{
    DiagSrv_0x34_Status = DIAGSRV_0X34_STAT_IDLE;
    DiagSrv_0x34_Msg = NULL_PTR;
    DiagSrv_0x34_WriteAddr = 0UL;
    DiagSrv_0x34_WriteSize = 0UL;
    DiagSrv_0x34_EncryptionMode = STD_OFF;
    DiagSrv_0x34_CompressionMode = STD_OFF;

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x34_Time_PreDecode                                */
/* Description   | Time of DIAGSRV_0X34_STAT_WAIT_PREDEC                      */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GR                                               */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x34_Time_PreDecode (void)
{
    VAR(uint8, AUTOMATIC) Status;
    VAR(uint8, AUTOMATIC) JobResult;
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DIAG_NRC_RCRRP;

    Status = Decrypt_GetStatus();
    if( Status == DECRYPT_IDLE )
    {
        Nrc = DIAG_NRC_GR;
        JobResult = Decrypt_GetJobResult();
        if( JobResult == DECRYPT_JOB_OK )
        {
            Nrc = DiagSrv_0x34_PreCommon();
        }
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x34_Time_PreDecmp                                 */
/* Description   | Time of DIAGSRV_0X34_STAT_WAIT_PREDECMP                    */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GR                                               */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x34_Time_PreDecmp (void)
{
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DiagSrv_0x34_PreCommon();

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x34_Time_PreFscDtct                               */
/* Description   | Time of DIAGSRV_0X34_STAT_WAIT_PRE_FSCDTCT                 */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GR                                               */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x34_Time_PreFscDtct (void)
{
#if 0   /* @@@ T.Inoue start : without Crypto_sw */
    VAR(uint8, AUTOMATIC) Status;
    VAR(uint8, AUTOMATIC) JobResult;
#endif  /* @@@ T.Inoue end : without Crypto_sw */
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DIAG_NRC_RCRRP;

#if 0   /* @@@ T.Inoue start : without Crypto_sw */
    Status = FscDtct_GetStatus();
    if( Status == FSCDTCT_IDLE )
    {
        Nrc = DIAG_NRC_GR;

        JobResult = FscDtct_GetJobResult();
        if( JobResult == FSCDTCT_JOB_OK )
        {
#endif  /* @@@ T.Inoue end : without Crypto_sw */
            Nrc = DiagSrv_0x34_WriteStart();
            if( Nrc == DIAG_NRC_PR )
            {
                DiagSrv_0x34_Status = DIAGSRV_0X34_STAT_IDLE;
            }
#if 0   /* @@@ T.Inoue start : without Crypto_sw */
        }
    }
#endif  /* @@@ T.Inoue end : without Crypto_sw */

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x34_CheckReqMsg                                   */
/* Description   | Check request message                                      */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_IMLOIF                                           */
/*               |  DIAG_NRC_ROOR                                             */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x34_CheckReqMsg (void)
{
    VAR(uint8, AUTOMATIC) ReqDfi;
    VAR(uint8, AUTOMATIC) ReqAlfid;
    VAR(uint8, AUTOMATIC) FullLen;
    VAR(uint8, AUTOMATIC) AddrLength;
    VAR(uint8, AUTOMATIC) SizeLength;
    VAR(uint8, AUTOMATIC) Nrc;

    if( DiagSrv_0x34_Msg->ReqDataLen < DIAGSRV_0X34_REQ_MSG_MIN_LEN )
    {
        Nrc = DIAG_NRC_IMLOIF;
    }
    else
    {
        ReqDfi = DiagSrv_0x34_Msg->ReqData[DIAGSRV_0X34_DFI_POS];
        Nrc = DiagSrv_0x34_CheckDfi(ReqDfi);
        if( Nrc == DIAG_NRC_PR )
        {
            ReqAlfid = DiagSrv_0x34_Msg->ReqData[DIAGSRV_0X34_ALFID_POS];
            Nrc = DiagSrv_0x34_CheckAlfid(ReqAlfid);
            if( Nrc == DIAG_NRC_PR )
            {
                AddrLength = DIAGSRV_0X34_CONVERT_ALFID_TO_ADDRESS_LENGTH(ReqAlfid);
                SizeLength = DIAGSRV_0X34_CONVERT_ALFID_TO_SIZE_LENGTH(ReqAlfid);

                FullLen = DIAGSRV_0X34_SID_TO_ALFID_LEN + AddrLength + SizeLength;
                if( DiagSrv_0x34_Msg->ReqDataLen != FullLen )
                {
                    Nrc = DIAG_NRC_IMLOIF;
                }
            }
        }
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x34_CheckDfi                                      */
/* Description   | Check data format identifier                               */
/* Preconditions |                                                            */
/* Parameters    | [IN] ReqDfi : Data format identifier                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_ROOR                                             */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x34_CheckDfi
(
    VAR(uint8, AUTOMATIC) ReqDfi
)
{
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(uint8, AUTOMATIC) SupportDfi;

    Nrc = DIAG_NRC_PR;

    SupportDfi = ReqDfi & (uint8)(~DiagSrv_0x34_Config.DataFormatId);
    if( SupportDfi != ((uint8)0x00U) )
    {
        Nrc = DIAG_NRC_ROOR;
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x34_CheckAlfid                                    */
/* Description   | Check address and length format identifier                 */
/* Preconditions |                                                            */
/* Parameters    | [IN] ReqAlfid : address and length format identifier       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_ROOR                                             */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x34_CheckAlfid
(
    VAR(uint8, AUTOMATIC) ReqAlfid
)
{
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(uint8, AUTOMATIC) SupportAlfid;

    Nrc = DIAG_NRC_PR;

    SupportAlfid = ((uint8)(DiagSrv_0x34_Config.MemorySizeLength << DIAGSRV_0X34_BIT_SHIFT_4))
                    | DiagSrv_0x34_Config.MemoryAddressLength;
    if( ReqAlfid != SupportAlfid )
    {
        Nrc = DIAG_NRC_ROOR;
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x34_CheckMemArea                                  */
/* Description   | Check memory area                                          */
/* Preconditions |                                                            */
/* Parameters    | [IN]  MemoryAddr : Memory address                          */
/*               | [IN]  MemorySize : Memory size                             */
/*               | [OUT] MemoryArea : Rewrite Area or SBL Area                */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_ROOR                                             */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x34_CheckMemArea
(
    VAR(uint32, AUTOMATIC) MemoryAddr,
    VAR(uint32, AUTOMATIC) MemorySize,
    P2VAR(uint8, AUTOMATIC, DIAGSRV_APPL_DATA) MemoryArea
)
{
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(uint8, AUTOMATIC) RewriteAreaNum;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    Nrc = DIAG_NRC_ROOR;

    FuncRet = DiagSrv_CheckSblArea(MemoryAddr, MemorySize);
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        *MemoryArea = DIAGSRV_0x34_MEM_SBL_AREA;
        Nrc = DIAG_NRC_PR;
    }
    else
    {
        RewriteAreaNum = DiagSrv_GetRewriteAreaNumber();

        FuncRet = DiagSrv_CheckRewriteArea(RewriteAreaNum, MemoryAddr, MemorySize);
        if( FuncRet == (Std_ReturnType)E_OK )
        {
            *MemoryArea = DIAGSRV_0x34_MEM_REWRITE_AREA;
            Nrc = DIAG_NRC_PR;
        }
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x34_CheckRewriteStatus                            */
/* Description   | Check rewrite status                                       */
/* Preconditions |                                                            */
/* Parameters    | [IN] MemoryArea : Rewrite Area or SBL Area                 */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_CNC                                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x34_CheckRewriteStatus
(
    VAR(uint8, AUTOMATIC) MemoryArea
)
{
    VAR(uint8, AUTOMATIC) RewriteStatus;
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DIAG_NRC_CNC;

    RewriteStatus = DiagSrv_GetRewriteStatus();
    if( ((RewriteStatus == DIAGSRV_REWRITESTAT_READY) && (MemoryArea == DIAGSRV_0x34_MEM_SBL_AREA)) ||
        ((RewriteStatus == DIAGSRV_REWRITESTAT_ERASE) && (MemoryArea == DIAGSRV_0x34_MEM_REWRITE_AREA)) )
    {
        Nrc = DIAG_NRC_PR;
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x34_CheckCondition                                */
/* Description   | Check condition                                            */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  other(Depends on UserCustom)                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x34_CheckCondition (void)
{
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = RpgMfr_MsgCheckCondition(DiagSrv_0x34_Msg);
    if( Nrc == DIAG_NRC_PR )
    {
        Nrc = RpgSpp_MsgCheckCondition(DiagSrv_0x34_Msg);
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x34_SetInformation                                */
/* Description   | Set information                                            */
/* Preconditions |                                                            */
/* Parameters    | [IN] ReqDfi     : Data format identifier                   */
/*               | [IN] MemoryAddr : Memory address                           */
/*               | [IN] MemorySize : Memory size                              */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x34_SetInformation
(
    VAR(uint8, AUTOMATIC) ReqDfi,
    VAR(uint32, AUTOMATIC) MemoryAddr,
    VAR(uint32, AUTOMATIC) MemorySize
)
{
    if( (ReqDfi & DIAGSRV_0X34_DFI_LOW_MASK) == DIAGSRV_0X34_METHOD_CIPHER )
    {
        DiagSrv_0x34_EncryptionMode = STD_ON;
    }

    if( (ReqDfi & DIAGSRV_0X34_DFI_HIGH_MASK) == DIAGSRV_0X34_METHOD_COMPRESSION )
    {
        DiagSrv_0x34_CompressionMode = STD_ON;
    }

    DiagSrv_0x34_WriteAddr = MemoryAddr;
    DiagSrv_0x34_WriteSize = MemorySize;

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x34_PreTransferProcess                            */
/* Description   | Pre-transfer processing                                    */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GR                                               */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x34_PreTransferProcess (void)
{
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DiagSrv_0x34_PreDecode();
    if( Nrc == DIAG_NRC_PR )
    {
        Nrc = DiagSrv_0x34_PreCommon();
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x34_PreDecode                                     */
/* Description   | Pre-processing of decryption                               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_RCRRP                                            */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x34_PreDecode (void)
{
    VAR(Decrypt_NonceInfoType, AUTOMATIC) NonceInfo;
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DIAG_NRC_PR;

    if( DiagSrv_0x34_EncryptionMode == (uint8)STD_ON )
    {
        NonceInfo.Nonce = DiagSrv_GetNonceTempArea();
        NonceInfo.NonceSize = DIAGSRV_NONCE_BUFF_SIZE;

        Decrypt_ReqPreDecode(&NonceInfo);

        DiagSrv_0x34_Status = DIAGSRV_0X34_STAT_WAIT_PREDEC;

        Nrc = DIAG_NRC_RCRRP;
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x34_PreCommon                                     */
/* Description   | Common pre-processing                                      */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GR                                               */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x34_PreCommon (void)
{
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DiagSrv_0x34_PreDecompress();
    if( Nrc == DIAG_NRC_PR )
    {
        Nrc = DiagSrv_0x34_PreSigVerify();
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x34_PreDecompress                                 */
/* Description   | Pre-processing of decompression                            */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GR                                               */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x34_PreDecompress (void)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DIAG_NRC_PR;

    if( DiagSrv_0x34_CompressionMode == (uint8)STD_ON )
    {
        FuncRet = CmpDecmp_PreDecompress();
        if( FuncRet == (Std_ReturnType)E_OK )
        {
            /* No process */
        }
        else if( FuncRet == CMPDECMP_E_PENDING )
        {
            DiagSrv_0x34_Status = DIAGSRV_0X34_STAT_WAIT_PREDECMP;
            Nrc = DIAG_NRC_RCRRP;
        }
        else
        {
            Nrc = DIAG_NRC_GR;
        }
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x34_PreSigVerify                                  */
/* Description   | Pre-processing of signature verification                   */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GR                                               */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x34_PreSigVerify (void)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(uint8, AUTOMATIC) DeviceType;
    VAR(uint32, AUTOMATIC) PhysicalAddr;

    Nrc = DIAG_NRC_GR;

    PhysicalAddr = 0UL;
    DeviceType = RPGLIB_DEVICE_TYPE_CODERAM;

    FuncRet = RpgLib_CnvPhysicalAddr(RPGLIB_MEMORYID_0,
                                    DiagSrv_0x34_WriteAddr,
                                    &PhysicalAddr,
                                    &DeviceType);
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        DiagSrv_SetWriteDeviceType(DeviceType);

/*        FscDtct_ReqPreSigVerify();*//* @@@ T.Inoue : without Crypto_sw */

        DiagSrv_0x34_Status = DIAGSRV_0X34_STAT_WAIT_PRE_FSCDTCT;
        Nrc = DIAG_NRC_RCRRP;
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x34_WriteStart                                    */
/* Description   | Requests to start writing                                  */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_GR                                               */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x34_WriteStart (void)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;
    VAR(uint8, AUTOMATIC) RewriteStatus;
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DIAG_NRC_GR;

    FuncRet = RpgLib_WriteMemStart(RPGLIB_MEMORYID_0, DiagSrv_0x34_WriteAddr, DiagSrv_0x34_WriteSize);
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        DiagSrv_SetCipherTextMode(DiagSrv_0x34_EncryptionMode);
        DiagSrv_SetCompressionMode(DiagSrv_0x34_CompressionMode);
        DiagSrv_0x36_ClearInfo();
        DiagLib_SetTransferMode(DIAG_TFMODE_DL);

        RewriteStatus = DiagSrv_GetRewriteStatus();
        if( RewriteStatus == DIAGSRV_REWRITESTAT_READY )
        {
            DiagSrv_SetRewriteStatus(DIAGSRV_REWRITESTAT_SBL_DL_START);
            Nrc = DIAG_NRC_PR;
        }
        else if( RewriteStatus == DIAGSRV_REWRITESTAT_ERASE )
        {
            DiagSrv_SetRewriteStatus(DIAGSRV_REWRITESTAT_DATA_DL_START);
            Nrc = DIAG_NRC_PR;
        }
        else
        {
            /* No process */
        }
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x34_SendPosRsp                                    */
/* Description   | Send positive response                                     */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x34_SendPosRsp (void)
{
    VAR(uint32, AUTOMATIC) MaxNumberOfBlockLength;

    MaxNumberOfBlockLength = DiagLib_GetMNOBL();

    DiagSrv_0x34_Msg->ResData[DIAGSRV_0X34_SID_POS] = DIAG_MAKE_POSRSP_SID(DiagSrv_0x34_Msg);

    DiagSrv_0x34_Msg->ResData[DIAGSRV_0X34_LFID_POS] = DIAGSRV_0X34_LFID_MNROB_4BYTE;
    DiagSrv_0x34_Msg->ResData[DIAGSRV_0X34_MNROB_B1_POS] = (uint8)(MaxNumberOfBlockLength >> DIAGSRV_0X34_BIT_SHIFT_24);
    DiagSrv_0x34_Msg->ResData[DIAGSRV_0X34_MNROB_B2_POS] = (uint8)(MaxNumberOfBlockLength >> DIAGSRV_0X34_BIT_SHIFT_16);
    DiagSrv_0x34_Msg->ResData[DIAGSRV_0X34_MNROB_B3_POS] = (uint8)(MaxNumberOfBlockLength >> DIAGSRV_0X34_BIT_SHIFT_8);
    DiagSrv_0x34_Msg->ResData[DIAGSRV_0X34_MNROB_B4_POS] = (uint8)(MaxNumberOfBlockLength & DIAGSRV_0X34_MNOBL_LOW_MASK);
    DiagSrv_0x34_Msg->ResDataLen = DIAGSRV_0X34_SID_TO_MNROB_B4_LEN;

    DiagLib_SendPosRsp(DiagSrv_0x34_Msg);

    DiagSrv_0x34_ClearInfo();

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x34_SendNegRsp                                    */
/* Description   | Send negative response                                     */
/* Preconditions |                                                            */
/* Parameters    | [IN] Nrc : NRC                                             */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x34_SendNegRsp
(
    VAR(uint8, AUTOMATIC) Nrc
)
{
    VAR(uint8, AUTOMATIC) RewriteAreaNum;

    RewriteAreaNum = DiagSrv_GetRewriteAreaNumber();

    DiagSrv_SetRewriteAreaStatus(RewriteAreaNum, DIAGSRV_LBSTAT_REWRITING_NG);

    DiagSrv_SetRewriteStatus(DIAGSRV_REWRITESTAT_IDLE);

    DiagLib_SendNegRsp(Nrc, DiagSrv_0x34_Msg);

    DiagSrv_0x34_ClearInfo();

    return;
}

#define DIAGSRV_STOP_SEC_CODE
#include <DiagSrv_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2021/09/14 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

