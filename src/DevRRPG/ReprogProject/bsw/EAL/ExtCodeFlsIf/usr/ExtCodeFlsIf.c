/* ExtCodeFlsIf_c_Revision(v3.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | ExtCodeFlsIf/CODE                                           */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <ExtCodeFlsIf.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/*===== Sample ===============================================================*/
#define EXTCODEFLSIF_PROCESS_NONE               ((uint8)0x00U)
#define EXTCODEFLSIF_PROCESS_ERASE_START        ((uint8)0x01U)
#define EXTCODEFLSIF_PROCESS_ERASE_END          ((uint8)0x02U)
#define EXTCODEFLSIF_PROCESS_WRITE_START        ((uint8)0x03U)
#define EXTCODEFLSIF_PROCESS_WRITE_UPDATE_START ((uint8)0x04U)
#define EXTCODEFLSIF_PROCESS_WRITE_UPDATE_END   ((uint8)0x05U)
#define EXTCODEFLSIF_PROCESS_WRITE_END          ((uint8)0x06U)
#define EXTCODEFLSIF_PROCESS_READ_START         ((uint8)0x07U)
#define EXTCODEFLSIF_PROCESS_READ_END           ((uint8)0x08U)
/*===== Sample ===============================================================*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
/*===== Sample ===============================================================*/
typedef struct {
    uint32 Address;
    uint32 Size;
} ExtCodeFlsIf_EraseInfoType;

typedef struct {
    uint32 TopAddress;
    uint32 TotalSize;
    P2CONST(uint8, TYPEDEF, EXTCODEFLSIF_CONST) Data;
    uint32 CurrentSize;
    uint32 WrittenSize;
} ExtCodeFlsIf_WriteInfoType;

typedef struct {
    P2VAR(uint8, TYPEDEF, EXTCODEFLSIF_APPL_DATA) Data;
    uint32 Address;
    uint32 Size;
} ExtCodeFlsIf_ReadInfoType;

typedef struct {
    ExtCodeFlsIf_EraseInfoType EraseInfo;
    ExtCodeFlsIf_WriteInfoType WriteInfo;
    ExtCodeFlsIf_ReadInfoType ReadInfo;
    ExtCodeFlsIf_JobResultType Result;
    ExtCodeFlsIf_StatusType Status;
    uint8 Process;
} ExtCodeFlsIf_JobInfoType;
/*===== Sample ===============================================================*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define EXTCODEFLSIF_START_SEC_VAR
#include <ExtCodeFlsIf_MemMap.h>

/*===== Sample ===============================================================*/
static VAR(ExtCodeFlsIf_JobInfoType, EXTCODEFLSIF_VAR_CLEARED) ExtCodeFlsIf_Job;
/*===== Sample ===============================================================*/

#define EXTCODEFLSIF_STOP_SEC_VAR
#include <ExtCodeFlsIf_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define EXTCODEFLSIF_START_SEC_CST
#include <ExtCodeFlsIf_MemMap.h>

#define EXTCODEFLSIF_STOP_SEC_CST
#include <ExtCodeFlsIf_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define EXTCODEFLSIF_START_SEC_CODE
#include <ExtCodeFlsIf_MemMap.h>

/******************************************************************************/
/* Function Name | ExtCodeFlsIf_Erase                                         */
/* Description   | Request to erase                                           */
/* Preconditions |                                                            */
/* Parameters    | [IN] TargetAddr : Erase address                            */
/*               | [IN] TargetSize : Erase size                               */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, EXTCODEFLSIF_CODE_SLOW) ExtCodeFlsIf_Erase
(
    VAR(uint32, AUTOMATIC) TargetAddr,
    VAR(uint32, AUTOMATIC) TargetSize
)
{
/*===== Sample ===============================================================*/
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    if( ExtCodeFlsIf_Job.Status == EXTCODEFLSIF_IDLE )
    {
        ExtCodeFlsIf_Job.EraseInfo.Address = TargetAddr;
        ExtCodeFlsIf_Job.EraseInfo.Size = TargetSize;

        ExtCodeFlsIf_Job.Process = EXTCODEFLSIF_PROCESS_ERASE_START;
        ExtCodeFlsIf_Job.Result = EXTCODEFLSIF_JOB_FAILED;
        ExtCodeFlsIf_Job.Status = EXTCODEFLSIF_BUSY;

        Ret = E_OK;
    }
    else
    {
        ExtCodeFlsIf_Job.Process = EXTCODEFLSIF_PROCESS_NONE;
        ExtCodeFlsIf_Job.Result = EXTCODEFLSIF_JOB_FAILED;
        ExtCodeFlsIf_Job.Status = EXTCODEFLSIF_IDLE;

        Ret = E_NOT_OK;
    }

    return Ret;
/*===== Sample ===============================================================*/
}

/******************************************************************************/
/* Function Name | ExtCodeFlsIf_WriteStart                                    */
/* Description   | Request to start writing                                   */
/* Preconditions |                                                            */
/* Parameters    | [IN] DestAddr  : Destination address                       */
/*               | [IN] TotalSize : Total write size                          */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, EXTCODEFLSIF_CODE_SLOW) ExtCodeFlsIf_WriteStart
(
    VAR(uint32, AUTOMATIC) DestAddr,
    VAR(uint32, AUTOMATIC) TotalSize
)
{
/*===== Sample ===============================================================*/
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    if( ExtCodeFlsIf_Job.Status == EXTCODEFLSIF_IDLE )
    {
        ExtCodeFlsIf_Job.WriteInfo.TopAddress = DestAddr;
        ExtCodeFlsIf_Job.WriteInfo.TotalSize = TotalSize;
        ExtCodeFlsIf_Job.WriteInfo.CurrentSize = 0UL;
        ExtCodeFlsIf_Job.WriteInfo.WrittenSize = 0UL;

        ExtCodeFlsIf_Job.Process = EXTCODEFLSIF_PROCESS_NONE;
        ExtCodeFlsIf_Job.Result = EXTCODEFLSIF_JOB_FAILED;
        ExtCodeFlsIf_Job.Status = EXTCODEFLSIF_UPDATEIDLE;

        Ret = E_OK;
    }
    else
    {
        ExtCodeFlsIf_Job.Process = EXTCODEFLSIF_PROCESS_NONE;
        ExtCodeFlsIf_Job.Result = EXTCODEFLSIF_JOB_FAILED;
        ExtCodeFlsIf_Job.Status = EXTCODEFLSIF_IDLE;

        Ret = E_NOT_OK;
    }

    return Ret;
/*===== Sample ===============================================================*/
}

/******************************************************************************/
/* Function Name | ExtCodeFlsIf_WriteUpdate                                   */
/* Description   | Request to update writing                                  */
/* Preconditions |                                                            */
/* Parameters    | [IN] SrcAddr : Source address                              */
/*               | [IN] Size    : Write size                                  */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, EXTCODEFLSIF_CODE_SLOW) ExtCodeFlsIf_WriteUpdate
(
    P2CONST(uint8, AUTOMATIC, EXTCODEFLSIF_APPL_CONST) SrcAddr,
    VAR(uint32, AUTOMATIC) Size
)
{
/*===== Sample ===============================================================*/
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    if( ( ExtCodeFlsIf_Job.Status == EXTCODEFLSIF_UPDATEIDLE ) &&
        ( ( ExtCodeFlsIf_Job.WriteInfo.WrittenSize + Size ) <= ExtCodeFlsIf_Job.WriteInfo.TotalSize ) )
    {
        ExtCodeFlsIf_Job.WriteInfo.Data = SrcAddr;
        ExtCodeFlsIf_Job.WriteInfo.CurrentSize = Size;

        ExtCodeFlsIf_Job.Process = EXTCODEFLSIF_PROCESS_WRITE_UPDATE_START;
        ExtCodeFlsIf_Job.Result = EXTCODEFLSIF_JOB_FAILED;
        ExtCodeFlsIf_Job.Status = EXTCODEFLSIF_UPDATEBUSY;

        Ret = E_OK;
    }
    else
    {
        ExtCodeFlsIf_Job.Process = EXTCODEFLSIF_PROCESS_NONE;
        ExtCodeFlsIf_Job.Result = EXTCODEFLSIF_JOB_FAILED;
        ExtCodeFlsIf_Job.Status = EXTCODEFLSIF_IDLE;

        Ret = E_NOT_OK;
    }

    return Ret;
/*===== Sample ===============================================================*/
}

/******************************************************************************/
/* Function Name | ExtCodeFlsIf_WriteFinish                                   */
/* Description   | Request to finish writing                                  */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, EXTCODEFLSIF_CODE_SLOW) ExtCodeFlsIf_WriteFinish (void)
{
/*===== Sample ===============================================================*/
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    if( ExtCodeFlsIf_Job.Status == EXTCODEFLSIF_UPDATEIDLE )
    {
        ExtCodeFlsIf_Job.Process = EXTCODEFLSIF_PROCESS_WRITE_UPDATE_START;
        ExtCodeFlsIf_Job.Result = EXTCODEFLSIF_JOB_FAILED;
        ExtCodeFlsIf_Job.Status = EXTCODEFLSIF_UPDATEBUSY;

        Ret = E_OK;
    }
    else
    {
        ExtCodeFlsIf_Job.Process = EXTCODEFLSIF_PROCESS_NONE;
        ExtCodeFlsIf_Job.Result = EXTCODEFLSIF_JOB_FAILED;
        ExtCodeFlsIf_Job.Status = EXTCODEFLSIF_IDLE;

        Ret = E_NOT_OK;
    }

    return Ret;
/*===== Sample ===============================================================*/
}

/******************************************************************************/
/* Function Name | ExtCodeFlsIf_Read                                          */
/* Description   | Request to read                                            */
/* Preconditions |                                                            */
/* Parameters    | [IN]  SrcAddr  : Source address                            */
/*               | [OUT] DestAddr : Destination address                       */
/*               | [IN]  Size     : Read size                                 */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, EXTCODEFLSIF_CODE_SLOW) ExtCodeFlsIf_Read
(
    VAR(uint32, AUTOMATIC) SrcAddr,
    P2VAR(uint8, AUTOMATIC, EXTCODEFLSIF_APPL_DATA) DestAddr,
    VAR(uint32, AUTOMATIC) Size
)
{
/*===== Sample ===============================================================*/
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    if( ExtCodeFlsIf_Job.Status == EXTCODEFLSIF_UPDATECOMPLETE )
    {
        ExtCodeFlsIf_Job.ReadInfo.Data = DestAddr;
        ExtCodeFlsIf_Job.ReadInfo.Address = SrcAddr;
        ExtCodeFlsIf_Job.ReadInfo.Size = Size;

        ExtCodeFlsIf_Job.Process = EXTCODEFLSIF_PROCESS_NONE;
        ExtCodeFlsIf_Job.Result = EXTCODEFLSIF_JOB_OK;
        ExtCodeFlsIf_Job.Status = EXTCODEFLSIF_IDLE;

        Ret = E_OK;
    }
    else
    {
        ExtCodeFlsIf_Job.Process = EXTCODEFLSIF_PROCESS_NONE;
        ExtCodeFlsIf_Job.Result = EXTCODEFLSIF_JOB_FAILED;
        ExtCodeFlsIf_Job.Status = EXTCODEFLSIF_IDLE;

        Ret = E_NOT_OK;
    }

    return Ret;
/*===== Sample ===============================================================*/
}

/******************************************************************************/
/* Function Name | ExtCodeFlsIf_GetStatus                                     */
/* Description   | Get job status                                             */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | JobStatus                                                  */
/*               |  EXTCODEFLSIF_UNINIT                                       */
/*               |  EXTCODEFLSIF_IDLE                                         */
/*               |  EXTCODEFLSIF_BUSY                                         */
/*               |  EXTCODEFLSIF_UPDATEIDLE                                   */
/*               |  EXTCODEFLSIF_UPDATEBUSY                                   */
/*               |  EXTCODEFLSIF_UPDATECOMPLETE                               */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(ExtCodeFlsIf_StatusType, EXTCODEFLSIF_CODE_SLOW) ExtCodeFlsIf_GetStatus (void)
{
/*===== Sample ===============================================================*/
    return ExtCodeFlsIf_Job.Status;
/*===== Sample ===============================================================*/
}

/******************************************************************************/
/* Function Name | ExtCodeFlsIf_GetJobResult                                  */
/* Description   | Get job result                                             */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | JobResult                                                  */
/*               |  EXTCODEFLSIF_JOB_OK                                       */
/*               |  EXTCODEFLSIF_JOB_FAILED                                   */
/*               |  EXTCODEFLSIF_JOB_PENDING                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(ExtCodeFlsIf_JobResultType, EXTCODEFLSIF_CODE_SLOW) ExtCodeFlsIf_GetJobResult (void)
{
/*===== Sample ===============================================================*/
    return ExtCodeFlsIf_Job.Result;
/*===== Sample ===============================================================*/
}

/******************************************************************************/
/* Function Name | ExtCodeFlsIf_Init                                          */
/* Description   | Initialize ExtCodeFlsIf                                    */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, EXTCODEFLSIF_CODE_SLOW) ExtCodeFlsIf_Init (void)
{
/*===== Sample ===============================================================*/
    ExtCodeFlsIf_Job.Process = EXTCODEFLSIF_PROCESS_NONE;
    ExtCodeFlsIf_Job.Result = EXTCODEFLSIF_JOB_FAILED;
    ExtCodeFlsIf_Job.Status = EXTCODEFLSIF_IDLE;

    ExtCodeFlsIf_Job.EraseInfo.Address = 0UL;
    ExtCodeFlsIf_Job.EraseInfo.Size = 0UL;

    ExtCodeFlsIf_Job.WriteInfo.TopAddress = 0UL;
    ExtCodeFlsIf_Job.WriteInfo.TotalSize = 0UL;
    ExtCodeFlsIf_Job.WriteInfo.Data = NULL_PTR;
    ExtCodeFlsIf_Job.WriteInfo.CurrentSize = 0UL;
    ExtCodeFlsIf_Job.WriteInfo.WrittenSize = 0UL;

    ExtCodeFlsIf_Job.ReadInfo.Data = NULL_PTR;
    ExtCodeFlsIf_Job.ReadInfo.Address = 0UL;
    ExtCodeFlsIf_Job.ReadInfo.Size = 0UL;
/*===== Sample ===============================================================*/

    return;
}

/******************************************************************************/
/* Function Name | ExtCodeFlsIf_MainFunction                                  */
/* Description   | MainFunction                                               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, EXTCODEFLSIF_CODE_SLOW) ExtCodeFlsIf_MainFunction (void)
{
/*===== Sample ===============================================================*/
    if( ExtCodeFlsIf_Job.Process == EXTCODEFLSIF_PROCESS_ERASE_START )
    {
        ExtCodeFlsIf_Job.Process = EXTCODEFLSIF_PROCESS_ERASE_END;
    }
    else if( ExtCodeFlsIf_Job.Process == EXTCODEFLSIF_PROCESS_ERASE_END )
    {
        ExtCodeFlsIf_Job.EraseInfo.Address = 0UL;
        ExtCodeFlsIf_Job.EraseInfo.Size = 0UL;

        ExtCodeFlsIf_Job.Process = EXTCODEFLSIF_PROCESS_NONE;
        ExtCodeFlsIf_Job.Result = EXTCODEFLSIF_JOB_OK;
        ExtCodeFlsIf_Job.Status = EXTCODEFLSIF_IDLE;
    }
    else if( ExtCodeFlsIf_Job.Process == EXTCODEFLSIF_PROCESS_WRITE_UPDATE_START )
    {
        ExtCodeFlsIf_Job.Process = EXTCODEFLSIF_PROCESS_WRITE_UPDATE_END;
    }
    else if( ExtCodeFlsIf_Job.Process == EXTCODEFLSIF_PROCESS_WRITE_UPDATE_END )
    {
        ExtCodeFlsIf_Job.WriteInfo.Data = NULL_PTR;
        ExtCodeFlsIf_Job.WriteInfo.WrittenSize += ExtCodeFlsIf_Job.WriteInfo.CurrentSize;
        ExtCodeFlsIf_Job.WriteInfo.CurrentSize = 0UL;

        ExtCodeFlsIf_Job.Process = EXTCODEFLSIF_PROCESS_NONE;
        ExtCodeFlsIf_Job.Result = EXTCODEFLSIF_JOB_OK;

        if( ExtCodeFlsIf_Job.WriteInfo.WrittenSize < ExtCodeFlsIf_Job.WriteInfo.TotalSize )
        {
            ExtCodeFlsIf_Job.Status = EXTCODEFLSIF_UPDATEIDLE;
        }
        else
        {
            ExtCodeFlsIf_Job.WriteInfo.TopAddress = 0UL;
            ExtCodeFlsIf_Job.WriteInfo.TotalSize = 0UL;
            ExtCodeFlsIf_Job.WriteInfo.WrittenSize = 0UL;

            ExtCodeFlsIf_Job.Status = EXTCODEFLSIF_UPDATECOMPLETE;
        }
    }
    else if( ExtCodeFlsIf_Job.Process == EXTCODEFLSIF_PROCESS_READ_START )
    {
        ExtCodeFlsIf_Job.Process = EXTCODEFLSIF_PROCESS_READ_END;
    }
    else if ( ExtCodeFlsIf_Job.Process == EXTCODEFLSIF_PROCESS_READ_END )
    {
        ExtCodeFlsIf_Job.ReadInfo.Data = NULL_PTR;
        ExtCodeFlsIf_Job.ReadInfo.Address = 0UL;
        ExtCodeFlsIf_Job.ReadInfo.Size = 0UL;

        ExtCodeFlsIf_Job.Process = EXTCODEFLSIF_PROCESS_NONE;
        ExtCodeFlsIf_Job.Result = EXTCODEFLSIF_JOB_OK;
        ExtCodeFlsIf_Job.Status = EXTCODEFLSIF_IDLE;
    }
    else
    {
        /* No process */
    }
/*===== Sample ===============================================================*/

    return;
}

/******************************************************************************/
/* Function Name | ExtCodeFlsIf_DeInit                                        */
/* Description   | Deinitialize ExtCodeFlsIf                                  */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, EXTCODEFLSIF_CODE_SLOW) ExtCodeFlsIf_DeInit (void)
{
/*===== Sample ===============================================================*/
    ExtCodeFlsIf_Job.Process = EXTCODEFLSIF_PROCESS_NONE;
    ExtCodeFlsIf_Job.Result = EXTCODEFLSIF_JOB_FAILED;
    ExtCodeFlsIf_Job.Status = EXTCODEFLSIF_UNINIT;

    ExtCodeFlsIf_Job.EraseInfo.Address = 0UL;
    ExtCodeFlsIf_Job.EraseInfo.Size = 0UL;

    ExtCodeFlsIf_Job.WriteInfo.TopAddress = 0UL;
    ExtCodeFlsIf_Job.WriteInfo.TotalSize = 0UL;
    ExtCodeFlsIf_Job.WriteInfo.Data = NULL_PTR;
    ExtCodeFlsIf_Job.WriteInfo.CurrentSize = 0UL;
    ExtCodeFlsIf_Job.WriteInfo.WrittenSize = 0UL;

    ExtCodeFlsIf_Job.ReadInfo.Data = NULL_PTR;
    ExtCodeFlsIf_Job.ReadInfo.Address = 0UL;
    ExtCodeFlsIf_Job.ReadInfo.Size = 0UL;
/*===== Sample ===============================================================*/

    return;
}

#if ( REPROG_CFG_GETBLOCKINFO_USE == STD_ON )
/******************************************************************************/
/* Function Name | ExtCodeFlsIf_GetBlockInfo                                  */
/* Description   | Acquire block information about address and size           */
/* Preconditions |                                                            */
/* Parameters    | [IN]  Addr      : Address                                  */
/*               | [OUT] BlockInfo : Block information                        */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, EXTCODEFLSIF_CODE_SLOW) ExtCodeFlsIf_GetBlockInfo
(
    VAR(uint32, AUTOMATIC) Addr,
    P2VAR(ExtCodeFlsIf_BlockInfoType, AUTOMATIC, EXTCODEFLSIF_APPL_DATA) BlockInfo
)
{
/*===== Sample ===============================================================*/
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = E_NOT_OK;

    if( ExtCodeFlsIf_Job.Status == EXTCODEFLSIF_IDLE )
    {
        BlockInfo->Addr = 0UL;
        BlockInfo->Size = 1UL;

        Ret = E_OK;
    }

    return Ret;
/*===== Sample ===============================================================*/
}
#endif

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

#define EXTCODEFLSIF_STOP_SEC_CODE
#include <ExtCodeFlsIf_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2018/10/23 :Update                                rel.AUBASS */
/*  v3.00       :2021/09/14 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

