/* Mem_Sub_c                                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | RH850/U2Ax/Mem/CODE                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Mem.h>
#include <Det.h>
#include "../inc/Mem_Internal.h"
#include "../inc/Mem_Sub.h"
#include "../inc/CodeFls.h"


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define MEM_INVALID_ADDR            (0xFFFFFFFFUL)
#define MEM_INVALID_SIZE            (0UL)
#define MEM_ADJUST_ENDADDR          (1UL)


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct
{
    uint32 u4WriteSize;
    uint32 u4BlankCheckSize;
} Mem_SizeInfoType;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
static FUNC(void, MEM_CODE) Mem_Sub_sInitOpInfo(void);
static FUNC(uint8, MEM_CODE) Mem_Sub_sCheckAddress
(
    VAR(uint8, AUTOMATIC) u1ReqKind,
    VAR(uint32, AUTOMATIC) u4Addr,
    VAR(uint32, AUTOMATIC) u4Size
);
static FUNC(void, MEM_CODE) Mem_Sub_CheckCodeFlsJob(void);
static FUNC(void, MEM_CODE) Mem_Sub_EraseReq(void);
static FUNC(void, MEM_CODE) Mem_Sub_WriteReq(void);
static FUNC(void, MEM_CODE) Mem_Sub_BlankCheckReq(void);
static FUNC(void, MEM_CODE) Mem_Sub_SwitchValidAreaReq(void);
static FUNC(Std_ReturnType, MEM_CODE) Mem_Sub_CheckBlockInfo
(
    VAR(uint32, AUTOMATIC) TargetAddr,
    VAR(uint32, AUTOMATIC) TargetSize
);


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define MEM_START_SEC_VAR_NO_INIT_32
#include <Mem_MemMap.h>

#define MEM_STOP_SEC_VAR_NO_INIT_32
#include <Mem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define MEM_START_SEC_CONST_32
#include <Mem_MemMap.h>

static CONST(AB_83_ConstV Mem_SizeInfoType, MEM_CONST) Mem_SizeInfo = {
    CODEFLS_WRITE_SIZE,
    CODEFLS_U4_BLANKCHECK_ALIGN_SIZE
};

#define MEM_STOP_SEC_CONST_32
#include <Mem_MemMap.h>


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define MEM_START_SEC_CODE
#include <Mem_MemMap.h>

/****************************************************************************/
/* Function Name | Mem_Sub_InitVariables                                    */
/* Description   | Initialize the RAM used by the CODEFLS driver.           */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, MEM_CODE) Mem_Sub_InitVariables(void)
{
    /* Set Error Notification Recieve Flag to MEM_U1_FALSE */
    Mem_u1gErrorNotifyFlag = MEM_U1_FALSE;
    Mem_u1gMirrorErrorNotifyFlag = Mem_u1gErrorNotifyFlag;

    /* Set the flash control job state to MEM_UNINIT */
    Mem_u1gJobStatus = MEM_UNINIT;
    Mem_u1gMirrorJobStatus = Mem_u1gJobStatus;

    /* Set MEM_JOB_OK in the flash control job result */
    Mem_u1gJobResult = MEM_JOB_OK;
    Mem_u1gMirrorJobResult = Mem_u1gJobResult;

    /* Initialize each member of the operation information */
    Mem_Sub_sInitOpInfo();

    /* Reset the job delay counter */
    Mem_u1gJobDelayCount = MEM_U1_VAL_0;

    return;
}

/****************************************************************************/
/* Function Name | Mem_Sub_CheckParamRead                                   */
/* Description   | Check the arguments of the read request.                 */
/* Preconditions | -                                                        */
/* Parameters    | [IN]instanceId   :Instance ID                            */
/*               | [IN]u4SourceAddr :read start address                     */
/*               | [IN]u4TargetAddr :read data storage address              */
/*               | [IN]u4DataSize   :Read data size - byte                  */
/*               | [OUT]pu1InfoNum  :Index of the code flash area           */
/*               |                   information setting table              */
/* Return Value  | E_OK             :Successful completion                  */
/*               | E_NOT_OK         :Failed                                 */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, MEM_CODE) Mem_Sub_CheckParamRead
(
    VAR(Mem_InstanceIdType, AUTOMATIC) instanceId,
    VAR(uint32, AUTOMATIC) u4SourceAddr,
    P2CONST(Mem_DataType, AUTOMATIC, MEM_APPL_DATA) pu1TargetAddr,
    VAR(uint32, AUTOMATIC) u4DataSize,
    P2VAR(uint8, AUTOMATIC, MEM_APPL_DATA) pu1InfoNum
)
{
    /* Variable Declarations */
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;
    VAR(uint8, AUTOMATIC) u1aInfoNum;

    /* Instance id check */
    u1aRet = Mem_Sub_InstanceIdCheck(instanceId);

    /* Instance id check result is E_OK */
    if( (Std_ReturnType)E_OK == u1aRet )
    {
        /* Set return value to E_NOT_OK */
        u1aRet = E_NOT_OK;

        /* Read data length greater than or equal to 1 */
        if( u4DataSize >= MEM_U4_VAL_1 )
        {
            /* Read data storage address is not null */
            if( NULL_PTR != pu1TargetAddr )
            {
                /* Check address and data length */
                u1aInfoNum = Mem_Sub_sCheckAddress(MEM_REQ_READ, u4SourceAddr, u4DataSize);

                /* Data length is failed */
                if( MEM_U1_INFONUM_NONE_LEN == u1aInfoNum )
                {
                    /* Error notification for development - Data length error */
                    Mem_Sub_Det_ReportError((uint16)MEM_MODULE_ID,(uint8)instanceId,(uint8)MEM_API_ID_READ,(uint8)MEM_E_PARAM_LENGTH);
                }
                else if( MEM_U1_INFONUM_NONE_ADD == u1aInfoNum )
                {/* Address is failed */
                    /* Error notification for development - Address error */
                    Mem_Sub_Det_ReportError((uint16)MEM_MODULE_ID,(uint8)instanceId,(uint8)MEM_API_ID_READ,(uint8)MEM_E_PARAM_ADDRESS);
                }
                else
                {
                    /* Set the obtained block number to pu1InfoNum */
                    /* Set return value to E_OK */
                    *pu1InfoNum = u1aInfoNum;
                    u1aRet = E_OK;
                }
            }
            else
            {
                /* Error notification for development - Param pointer error */
                Mem_Sub_Det_ReportError((uint16)MEM_MODULE_ID,(uint8)instanceId,(uint8)MEM_API_ID_READ,(uint8)MEM_E_PARAM_POINTER);
            }
        }
        else
        {
            /* Error notification for development - Data length error */
            Mem_Sub_Det_ReportError((uint16)MEM_MODULE_ID,(uint8)instanceId,(uint8)MEM_API_ID_READ,(uint8)MEM_E_PARAM_LENGTH);
        }
    }
    else
    {
        /* Error notification for development - Instance id error */
        Mem_Sub_Det_ReportError((uint16)MEM_MODULE_ID,(uint8)instanceId,(uint8)MEM_API_ID_READ,(uint8)MEM_E_PARAM_INSTANCE_ID);
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | Mem_Sub_CheckParamWrite                                  */
/* Description   | Check the arguments of the write request.                */
/* Preconditions | -                                                        */
/* Parameters    | [IN]instanceId   :Instance ID                            */
/*               | [IN]u4TargetAddr :Write start address                    */
/*               | [IN]u4SourceAddr :Write data storage                     */
/*               | [IN]u4DataSize   :Write data size - byte                 */
/*               | [OUT]pu1InfoNum  :Index of the code flash area           */
/*               |                   information setting table              */
/* Return Value  | E_OK             :Successful completion                  */
/*               | E_NOT_OK         :Failed                                 */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, MEM_CODE) Mem_Sub_CheckParamWrite
(
    VAR(Mem_InstanceIdType, AUTOMATIC) instanceId,
    VAR(uint32, AUTOMATIC) u4TargetAddr,
    P2CONST(Mem_DataType, AUTOMATIC, MEM_APPL_DATA) pu1sourceDataPtr,
    VAR(uint32, AUTOMATIC) u4DataSize,
    P2VAR(uint8, AUTOMATIC, MEM_APPL_DATA) pu1InfoNum
)
{
    /* Variable Declarations */
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;
    VAR(uint8, AUTOMATIC) u1aInfoNum;

    /* Instance id check */
    u1aRet = Mem_Sub_InstanceIdCheck(instanceId);

    /* Instance id check result is E_OK */
    if( (Std_ReturnType)E_OK == u1aRet )
    {
        /* Set return value to E_NOT_OK */
        u1aRet = E_NOT_OK;

        /* Write data length greater than or equal to 1 */
        if( u4DataSize >= MEM_U4_VAL_1 )
        {
            /* Write data storage address is not null */
            if( NULL_PTR != pu1sourceDataPtr )
            {
                /* Check address and data length */
                u1aInfoNum = Mem_Sub_sCheckAddress(MEM_REQ_WRITE, u4TargetAddr, u4DataSize);

                /* Data length is failed */
                if( MEM_U1_INFONUM_NONE_LEN == u1aInfoNum )
                {
                    /* Error notification for development - Data length error */
                    Mem_Sub_Det_ReportError((uint16)MEM_MODULE_ID,(uint8)instanceId,(uint8)MEM_API_ID_WRITE,(uint8)MEM_E_PARAM_LENGTH);
                }
                else if( MEM_U1_INFONUM_NONE_ADD == u1aInfoNum )
                {/* Address is failed */
                    /* Error notification for development - Address error */
                    Mem_Sub_Det_ReportError((uint16)MEM_MODULE_ID,(uint8)instanceId,(uint8)MEM_API_ID_WRITE,(uint8)MEM_E_PARAM_ADDRESS);
                }
                else
                {
                    u1aRet = CodeFls_CheckInvalidArea(u4TargetAddr, u4DataSize);
                    if( (Std_ReturnType)E_OK != u1aRet )
                    {
                        /* Error notification for development - Data length error */
                        Mem_Sub_Det_ReportError((uint16)MEM_MODULE_ID,(uint8)instanceId,(uint8)MEM_API_ID_WRITE,(uint8)MEM_E_PARAM_ADDRESS);
                    }
                    else
                    {
                        /* Set the obtained block number to pu1InfoNum */
                        /* Set return value to E_OK */
                        *pu1InfoNum = u1aInfoNum;
                        u1aRet = E_OK;
                    }
                }
            }
            else
            {
                /* Error notification for development - Param pointer error */
                Mem_Sub_Det_ReportError((uint16)MEM_MODULE_ID,(uint8)instanceId,(uint8)MEM_API_ID_WRITE,(uint8)MEM_E_PARAM_POINTER);
            }
        }
        else
        {
            /* Error notification for development - Data length error */
            Mem_Sub_Det_ReportError((uint16)MEM_MODULE_ID,(uint8)instanceId,(uint8)MEM_API_ID_WRITE,(uint8)MEM_E_PARAM_LENGTH);
        }
    }
    else
    {
        /* Error notification for development - Instance id error */
        Mem_Sub_Det_ReportError((uint16)MEM_MODULE_ID,(uint8)instanceId,(uint8)MEM_API_ID_WRITE,(uint8)MEM_E_PARAM_INSTANCE_ID);
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | Mem_Sub_CheckParamErase                                  */
/* Description   | Check the arguments of the erase request.                */
/* Preconditions | -                                                        */
/* Parameters    | [IN]instanceId  :Instance ID                             */
/*               | [IN]u4EraseAddr :Block address area to be erased         */
/*               | [IN]u4EraseSize :erasing size - byte                     */
/*               | [OUT]pu1InfoNum :Index of the code flash area            */
/*               |                  information setting table               */
/* Return Value  | E_OK            :Successful completion                   */
/*               | E_NOT_OK        :Failed                                  */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, MEM_CODE) Mem_Sub_CheckParamErase
(
    VAR(Mem_InstanceIdType, AUTOMATIC) instanceId,
    VAR(uint32, AUTOMATIC) u4EraseAddr,
    VAR(uint32, AUTOMATIC) u4EraseSize,
    P2VAR(uint8, AUTOMATIC, MEM_APPL_DATA) pu1InfoNum
)
{
    /* Variable Declarations */
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;
    VAR(uint8, AUTOMATIC) u1aInfoNum;

    /* Instance id check */
    u1aRet = Mem_Sub_InstanceIdCheck(instanceId);

    /* Instance id check result is E_OK */
    if( (Std_ReturnType)E_OK == u1aRet )
    {
        /* Set return value to E_NOT_OK */
        u1aRet = E_NOT_OK;

        /* Erase data length greater than or equal to 1 */
        if( u4EraseSize >= MEM_U4_VAL_1 )
        {
            /* Check address and data length */
            u1aInfoNum = Mem_Sub_sCheckAddress(MEM_REQ_ERASE, u4EraseAddr, u4EraseSize);

            /* Data length is failed */
            if( MEM_U1_INFONUM_NONE_LEN == u1aInfoNum )
            {
                /* Error notification for development - Data length error */
                Mem_Sub_Det_ReportError((uint16)MEM_MODULE_ID,(uint8)instanceId,(uint8)MEM_API_ID_ERASE,(uint8)MEM_E_PARAM_LENGTH);
            }
            else if( MEM_U1_INFONUM_NONE_ADD == u1aInfoNum )
            {/* Address is failed */
                /* Error notification for development - Address error */
                Mem_Sub_Det_ReportError((uint16)MEM_MODULE_ID,(uint8)instanceId,(uint8)MEM_API_ID_ERASE,(uint8)MEM_E_PARAM_ADDRESS);
            }
            else
            {
                u1aRet = CodeFls_CheckInvalidArea(u4EraseAddr, u4EraseSize);
                if( (Std_ReturnType)E_OK != u1aRet )
                {
                    /* Error notification for development - Data length error */
                    Mem_Sub_Det_ReportError((uint16)MEM_MODULE_ID,(uint8)instanceId,(uint8)MEM_API_ID_ERASE,(uint8)MEM_E_PARAM_ADDRESS);
                }
                else
                {
                    u1aRet = Mem_Sub_CheckBlockInfo(u4EraseAddr, u4EraseSize);
                    if( (Std_ReturnType)E_OK != u1aRet )
                    {
                        /* Error notification for development - Data length error */
                        Mem_Sub_Det_ReportError((uint16)MEM_MODULE_ID,(uint8)instanceId,(uint8)MEM_API_ID_ERASE,(uint8)MEM_E_PARAM_ADDRESS);
                    }
                    else
                    {
                            /* Set the obtained block number to pu1InfoNum */
                            /* Set return value to E_OK */
                            *pu1InfoNum = u1aInfoNum;
                            u1aRet = E_OK;
                    }
                }
            }
        }
        else
        {
            /* Error notification for development - Data length error */
            Mem_Sub_Det_ReportError((uint16)MEM_MODULE_ID,(uint8)instanceId,(uint8)MEM_API_ID_ERASE,(uint8)MEM_E_PARAM_LENGTH);
        }
    }
    else
    {
        /* Error notification for development - Instance id error */
        Mem_Sub_Det_ReportError((uint16)MEM_MODULE_ID,(uint8)instanceId,(uint8)MEM_API_ID_ERASE,(uint8)MEM_E_PARAM_INSTANCE_ID);
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | Mem_Sub_CheckParamBlankCheck                             */
/* Description   | Check the blank request arguments.                       */
/* Preconditions | -                                                        */
/* Parameters    | [IN]instanceId   :Instance ID                            */
/*               | [IN]u4TargetAddr :blank check start address              */
/*               | [IN]u4DataSize   :Blank check data size - byte           */
/*               | [OUT]pu1InfoNum  :Index of the code flash area           */
/*               |                   information setting table              */
/* Return Value  | E_OK             :Successful completion                  */
/*               | E_NOT_OK         :Failed                                 */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, MEM_CODE) Mem_Sub_CheckParamBlankCheck
(
    VAR(Mem_InstanceIdType, AUTOMATIC) instanceId,
    VAR(uint32, AUTOMATIC) u4TargetAddr,
    VAR(uint32, AUTOMATIC) u4DataSize,
    P2VAR(uint8, AUTOMATIC, MEM_APPL_DATA) pu1InfoNum
)
{
    /* Variable Declarations */
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;
    VAR(uint8, AUTOMATIC) u1aInfoNum;

    /* Instance id check */
    u1aRet = Mem_Sub_InstanceIdCheck(instanceId);

    /* Instance id check result is E_OK */
    if( (Std_ReturnType)E_OK == u1aRet )
    {
        /* Set return value to E_NOT_OK */
        u1aRet = E_NOT_OK;

        /* Blank check length greater than or equal to 1 */
        if( u4DataSize >= MEM_U4_VAL_1 )
        {
            /* Check address and data length */
            u1aInfoNum = Mem_Sub_sCheckAddress(MEM_REQ_BLANKCHECK, u4TargetAddr, u4DataSize);

            /* Data length is failed */
            if( MEM_U1_INFONUM_NONE_LEN == u1aInfoNum )
            {
                /* Error notification for development - Data length error */
                Mem_Sub_Det_ReportError((uint16)MEM_MODULE_ID,(uint8)instanceId,(uint8)MEM_API_ID_BLANKCHECK,(uint8)MEM_E_PARAM_LENGTH);
            }
            else if( MEM_U1_INFONUM_NONE_ADD == u1aInfoNum )
            {/* Address is failed */
                /* Error notification for development - Address error */
                Mem_Sub_Det_ReportError((uint16)MEM_MODULE_ID,(uint8)instanceId,(uint8)MEM_API_ID_BLANKCHECK,(uint8)MEM_E_PARAM_ADDRESS);
            }
            else if( MEM_U1_INFONUM_NONE_KIND == u1aInfoNum )
            {
                *pu1InfoNum = u1aInfoNum;
                u1aRet = E_NOT_OK;
            }
            else
            {
                /* Set the obtained block number to pu1InfoNum */
                /* Set return value to E_OK */
                *pu1InfoNum = u1aInfoNum;
                u1aRet = E_OK;
            }
        }
        else
        {
            /* Error notification for development - Data length error */
            Mem_Sub_Det_ReportError((uint16)MEM_MODULE_ID,(uint8)instanceId,(uint8)MEM_API_ID_BLANKCHECK,(uint8)MEM_E_PARAM_LENGTH);
        }
    }
    else
    {
        /* Error notification for development - Instance id error */
        Mem_Sub_Det_ReportError((uint16)MEM_MODULE_ID,(uint8)instanceId,(uint8)MEM_API_ID_BLANKCHECK,(uint8)MEM_E_PARAM_INSTANCE_ID);
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | Mem_Sub_InstanceIdCheck                                  */
/* Description   | Check if it is a registered instance ID.                 */
/* Preconditions | -                                                        */
/* Parameters    | [IN]InstanceID  : Instance ID                            */
/* Return Value  | E_OK            : Successful completion                  */
/*               | E_NOT_OK        : Failed                                 */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, MEM_CODE) Mem_Sub_InstanceIdCheck
(
    VAR(Mem_InstanceIdType, AUTOMATIC) instanceId
)
{
    /* Variable Declarations */
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;

    /* Matches the instance ID of the configuration information */
    if( instanceId == MemInstance.MemInstanceId )
    {
        /* Set return value to E_OK */
        u1aRet = E_OK;
    }
    else
    {
        /* Set return value to E_NOT_OK */
        u1aRet = E_NOT_OK;
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | Mem_Sub_Det_ReportError                                  */
/* Description   | Error notification for OTA_CodeFlash driver development. */
/* Preconditions | -                                                        */
/* Parameters    | [IN]ModuleID    : Module ID                              */
/*               | [IN]InstanceID  : Instance ID                            */
/*               | [IN]ApiID       : API ID - Service ID                    */
/*               | [IN]ErrID       : Development error ID                   */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, MEM_CODE) Mem_Sub_Det_ReportError
(
    VAR(uint16, AUTOMATIC) ModuleID,    /* MISRA DEVIATION */ /* For the commonization of source code with compile switches */
    VAR(uint8, AUTOMATIC) InstanceID,   /* MISRA DEVIATION */ /* For the commonization of source code with compile switches */
    VAR(uint8, AUTOMATIC) ApiID,        /* MISRA DEVIATION */ /* For the commonization of source code with compile switches */
    VAR(uint8, AUTOMATIC) ErrID         /* MISRA DEVIATION */ /* For the commonization of source code with compile switches */
)
{

#if (MEM_DEV_ERROR_DETECT == STD_ON)
    /* Development error notification */
    (void)Det_ReportError(ModuleID, InstanceID, ApiID, ErrID);  /* No need to check return value */
#endif
    return;
}

/****************************************************************************/
/* Function Name | Mem_Sub_SetJobStatus                                     */
/* Description   | Set the job status.                                      */
/* Preconditions | -                                                        */
/* Parameters    | [IN]sts   : Job status value to set                      */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, MEM_CODE) Mem_Sub_SetJobStatus
(
    VAR(uint8, AUTOMATIC) sts
)
{
    /* Set parameter value to job status */
    Mem_u1gJobStatus = sts;
    Mem_u1gMirrorJobStatus = Mem_u1gJobStatus;

    return;
}

/****************************************************************************/
/* Function Name | Mem_Sub_CheckMirrorOpInfo                                */
/* Description   | Check if it is a registered Mirror.                      */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | E_OK            : Successful completion                  */
/*               | E_NOT_OK        : Failed                                 */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, MEM_CODE) Mem_Sub_CheckMirrorOpInfo(void)
{
    /* Variable Declarations */
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;

    u1aRet = E_NOT_OK;
    if( (Mem_stgMirrorArea.u1CheckCmd == Mem_stgMultiOpInfo.u1Cmd) &&
        (Mem_stgMirrorArea.u4CheckAddr == Mem_stgMultiOpInfo.u4OpAddr) &&
        (Mem_stgMirrorArea.pu1CheckReadBuf == Mem_stgMultiOpInfo.pu1ReadBufAddr) &&
        (Mem_stgMirrorArea.pu1CheckWriteBuf == Mem_stgMultiOpInfo.pu1WriteBufAddr) &&
        (Mem_stgMirrorArea.u4CheckSize == Mem_stgMultiOpInfo.u4OpSize) &&
        (Mem_stgMirrorArea.u1CheckSectorBatchNum == Mem_stgMultiOpInfo.u1SectorBatchNum) &&
        (Mem_stgMirrorArea.u1CheckCtrlStartFlag == Mem_stgMultiOpInfo.u1CtrlStartFlag) &&
        (Mem_stgMirrorArea.u1CheckECCErrStatus == Mem_stgMultiOpInfo.u1ECCErrStatus) )
    {
        u1aRet = E_OK;
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | Mem_Sub_ReadOp                                           */
/* Description   | executes reading.                                        */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, MEM_CODE) Mem_Sub_ReadOp(void)
{
    /* Variable Declarations */
    VAR(uint32, AUTOMATIC) u4aLoopCnt;
    P2CONST(volatile uint8, AUTOMATIC, MEM_APPL_DATA) pu1aSrcAddr;
    VAR(uint8, AUTOMATIC) u1aSectorBatchNum;
    VAR(uint32, AUTOMATIC) u4aPageSize;
    VAR(uint8, AUTOMATIC) u1aResult;
    VAR(uint32, AUTOMATIC) u4aEccTargetAddr;

    /* Acquisition of read start address from operation information */
    pu1aSrcAddr = (volatile uint8*)Mem_stgMultiOpInfo.u4OpAddr;     /* MISRA DEVIATION */ /* Casting between a object pointer and a generic integer type */
    u4aEccTargetAddr = Mem_stgMultiOpInfo.u4OpAddr;
    u1aSectorBatchNum = Mem_stgMultiOpInfo.u1SectorBatchNum;
    u4aPageSize = MemInstance.MemSectorBatch[u1aSectorBatchNum].MemReadPageSize;

    /* Number of read bytes per cycle */
    for( u4aLoopCnt = MEM_U1_VAL_0; u4aLoopCnt < u4aPageSize; u4aLoopCnt++ )
    {
        /* Transfers memory data to a the reading data storage address */
        Mem_stgMultiOpInfo.pu1ReadBufAddr[u4aLoopCnt] = pu1aSrcAddr[u4aLoopCnt];
    }

    /* Update operation information to the next write data */
    Mem_stgMultiOpInfo.u4OpAddr      += u4aPageSize;        /* no wrap around */
    Mem_stgMultiOpInfo.pu1ReadBufAddr = &Mem_stgMultiOpInfo.pu1ReadBufAddr[u4aPageSize];
    Mem_stgMultiOpInfo.u4OpSize      -= u4aPageSize;        /* no wrap around */

    /* Copy Control Address and Size */
    Mem_stgMirrorArea.u4CheckAddr = Mem_stgMultiOpInfo.u4OpAddr;
    Mem_stgMirrorArea.pu1CheckReadBuf = Mem_stgMultiOpInfo.pu1ReadBufAddr;
    Mem_stgMirrorArea.u4CheckSize = Mem_stgMultiOpInfo.u4OpSize;

    if( Mem_u1gMirrorErrorNotifyFlag == Mem_u1gErrorNotifyFlag )
    {
        if( MEM_U1_TRUE == Mem_u1gErrorNotifyFlag )
        {
            Mem_Sub_SetJobStatus(MEM_IDLE);
            Mem_u1gJobResult = MEM_ECC_UNCORRECTED;
            Mem_u1gMirrorJobResult = Mem_u1gJobResult;
        }
        else
        {
            u1aResult = CodeFls_GetEccErrorAddressRom(u4aEccTargetAddr, u4aPageSize);

            /* ECC error 2 bits occurred */
            if( CODEFLS_U1_ECC_CHECK_ERROR_2BIT == u1aResult )
            {
                Mem_Sub_SetJobStatus(MEM_IDLE);
                Mem_u1gJobResult = MEM_ECC_UNCORRECTED;
                Mem_u1gMirrorJobResult = Mem_u1gJobResult;
            }
            else
            {
                /* ECC error 1 bits occurred */
                if( CODEFLS_U1_ECC_CHECK_ERROR_1BIT == u1aResult )
                {
                    Mem_stgMultiOpInfo.u1ECCErrStatus = MEM_ECC_CORRECTED;
                    Mem_stgMirrorArea.u1CheckECCErrStatus = Mem_stgMultiOpInfo.u1ECCErrStatus;
                }

                if( MEM_U4_OPINFO_SIZE_NONE >= Mem_stgMultiOpInfo.u4OpSize )
                {
                    Mem_Sub_SetJobStatus(MEM_IDLE);

                    if( Mem_stgMultiOpInfo.u1ECCErrStatus == MEM_ECC_CORRECTED )
                    {
                        Mem_u1gJobResult = MEM_ECC_CORRECTED;
                        Mem_u1gMirrorJobResult = Mem_u1gJobResult;
                    }
                    else
                    {
                        Mem_u1gJobResult = MEM_JOB_OK;
                        Mem_u1gMirrorJobResult = Mem_u1gJobResult;
                    }
                    Mem_Sub_sInitOpInfo();
                }
            }
        }
    }
    else
    {
        Mem_Sub_Failed();
    }

    return;
}

/****************************************************************************/
/* Function Name | Mem_Sub_ReqCodeFls                                       */
/* Description   | Request codeFls job.                                     */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, MEM_CODE) Mem_Sub_ReqCodeFls(void)
{

    if( MEM_REQ_SWITCHVALIDAREA == Mem_stgMultiOpInfo.u1Cmd )
    {
        Mem_Sub_SwitchValidAreaReq();
    }
    else if( MEM_REQ_ERASE == Mem_stgMultiOpInfo.u1Cmd )
    {
        Mem_Sub_EraseReq();
    }
    else if( MEM_REQ_WRITE == Mem_stgMultiOpInfo.u1Cmd )
    {
        Mem_Sub_WriteReq();
    }
    else if( MEM_REQ_BLANKCHECK == Mem_stgMultiOpInfo.u1Cmd )
    {
        Mem_Sub_BlankCheckReq();
    }
    else
    {
        /* Fail-safe support */
        /* If the command has an unexpected value, do nothing */
        Mem_Sub_Failed();
    }

    return;
}

/****************************************************************************/
/* Function Name | Mem_Sub_Failed                                           */
/* Description   | Set the information to failed                            */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, MEM_CODE) Mem_Sub_Failed(void)
{
    Mem_Sub_SetJobStatus(MEM_IDLE);
    Mem_u1gJobResult = MEM_JOB_FAILED;
    Mem_u1gMirrorJobResult = Mem_u1gJobResult;

    return;
}

/****************************************************************************/
/* Function Name | Mem_Sub_CmpltChkCodeFls                                  */
/* Description   | Wait for completion of CodeFls                           */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, MEM_CODE) Mem_Sub_CmpltChkCodeFls(void)
{
    CodeFls_MainFunction();

    Mem_Sub_CheckCodeFlsJob();

    if( (MEM_U1_FALSE == Mem_stgMultiOpInfo.u1CtrlStartFlag) && (MEM_U4_VAL_0  < Mem_stgMultiOpInfo.u4OpSize) )
    {
        /* If CodeFls has completed the job, the u1CtrlStartFlag will be set to FALSE.  */
        /* Additionally, if u4OpSize is greater than 0, there are remaining jobs.       */
        Mem_Sub_ReqCodeFls();
    }

    return;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Mem_Sub_sInitOpInfo                                      */
/* Description   | Initialize operation information.                        */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(void, MEM_CODE) Mem_Sub_sInitOpInfo(void)
{
    /* Initialize operation information */
    Mem_stgMultiOpInfo.u1Cmd            = MEM_U1_OPINFO_CMD_NONE;
    Mem_stgMultiOpInfo.u4OpAddr         = MEM_U4_OPINFO_ADDR_NONE;
    Mem_stgMultiOpInfo.pu1ReadBufAddr   = MEM_PU1_OPINFO_BUFFER_NULL;
    Mem_stgMultiOpInfo.pu1WriteBufAddr  = MEM_PU1_OPINFO_BUFFER_NULL;
    Mem_stgMultiOpInfo.u4OpSize         = MEM_U4_OPINFO_SIZE_NONE;
    Mem_stgMultiOpInfo.u1SectorBatchNum = MEM_U1_SECTOR_BATCH_NUM_NONE;
    Mem_stgMultiOpInfo.u1CtrlStartFlag  = MEM_U1_FALSE;
    Mem_stgMultiOpInfo.u1ECCErrStatus   = MEM_JOB_OK;

    /* Copy operation information to the Operations Information Mirror area */
    Mem_stgMirrorArea.u1CheckCmd            = Mem_stgMultiOpInfo.u1Cmd;
    Mem_stgMirrorArea.u4CheckAddr           = Mem_stgMultiOpInfo.u4OpAddr;
    Mem_stgMirrorArea.pu1CheckReadBuf       = Mem_stgMultiOpInfo.pu1ReadBufAddr;
    Mem_stgMirrorArea.pu1CheckWriteBuf      = Mem_stgMultiOpInfo.pu1WriteBufAddr;
    Mem_stgMirrorArea.u4CheckSize           = Mem_stgMultiOpInfo.u4OpSize;
    Mem_stgMirrorArea.u1CheckSectorBatchNum = Mem_stgMultiOpInfo.u1SectorBatchNum;
    Mem_stgMirrorArea.u1CheckCtrlStartFlag  = Mem_stgMultiOpInfo.u1CtrlStartFlag;
    Mem_stgMirrorArea.u1CheckECCErrStatus   = Mem_stgMultiOpInfo.u1ECCErrStatus;

    return;
}

/****************************************************************************/
/* Function Name | Mem_Sub_sCheckAddress                                    */
/* Description   | Check that the address and size of the argument are      */
/*               | within the code flash area defined in the configuration. */
/*               | When it is contained within the code flash area, the     */
/*               | index of the target code flash area information setting  */
/*               | table is returned.                                       */
/* Preconditions | -                                                        */
/* Parameters    | [IN]u4Addr      :address                                 */
/*               | [IN]u4Size      :size - byte                             */
/* Return Value  | index of target code flash area information setting      */
/*               | table                                                    */
/*               |    MEM_U1_INFONUM_0                                      */
/*               |    - Number of code flash area information settings-1 :  */
/*               |          Within the cord flush area range                */
/*               |    MEM_U1_INFONUM_NONE_KIND :                            */
/*               |          Out of the code flash area range - kind         */
/*               |    MEM_U1_INFONUM_NONE_LEN :                             */
/*               |          Out of the code flash area range - size         */
/*               |    MEM_U1_INFONUM_NONE_ADD :                             */
/*               |          Out of the code flash area range - address      */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(uint8, MEM_CODE) Mem_Sub_sCheckAddress
(
    VAR(uint8, AUTOMATIC) u1ReqKind,
    VAR(uint32, AUTOMATIC) u4Addr,
    VAR(uint32, AUTOMATIC) u4Size
)
{
    /* Variable Declarations */
    VAR(uint8, AUTOMATIC) u1aRet;
    VAR(uint8, AUTOMATIC) u1aLoopCnt;
    VAR(uint32, AUTOMATIC) u4aJobEndAddr;
    VAR(uint32, AUTOMATIC) u4aChkSize;
    VAR(uint32, AUTOMATIC) u4aBlkStaAddr;
    VAR(uint32, AUTOMATIC) u4aBlkEndAddr;
    VAR(uint32, AUTOMATIC) u4aRemainderAddr;
    VAR(uint32, AUTOMATIC) u4aRemainderSize;
    VAR(uint32, AUTOMATIC) u1aBankNum;

    /* Set return value to MEM_U1_INFONUM_NONE_ADD */
    u1aRet = MEM_U1_INFONUM_NONE_ADD;
    u1aBankNum = MemInstance.MemSectorBatchNum;


    /* Number of BANKS */
    for( u1aLoopCnt = MEM_U1_INFONUM_0; u1aLoopCnt < u1aBankNum; u1aLoopCnt++ )
    {
        /* Set size check init value to 0 */
        u4aChkSize = MEM_U4_VAL_0;

        /* Get the check size from the configuration information */
        switch( u1ReqKind )
        {
            /* u1ReqKind is MEM_REQ_READ */
            case MEM_REQ_READ:
                /* Get job processing size from configuration information */
                u4aChkSize = MemInstance.MemSectorBatch[u1aLoopCnt].MemReadPageSize;
                break;
            /* u1ReqKind is MEM_REQ_WRITE */
            case MEM_REQ_WRITE:
                /* Get job processing size from configuration information */
                u4aChkSize = MemInstance.MemSectorBatch[u1aLoopCnt].MemWritePageSize;
                break;
            /* u1ReqKind is MEM_REQ_ERASE */
            case MEM_REQ_ERASE:
                /* Get job processing size from configuration information */
                u4aChkSize = MemInstance.MemSectorBatch[u1aLoopCnt].MemEraseSectorSize;
                break;
            /* u1ReqKind is MEM_REQ_BLANKCHECK */
            case MEM_REQ_BLANKCHECK:
                /* Get job processing size from configuration information */
                u4aChkSize = Mem_SizeInfo.u4BlankCheckSize;
                break;
            default:
                /* Do Nothing */
                break;
        }

        /* Check size greater than or equal to 1 */
        if( u4aChkSize >= MEM_U4_VAL_1 )
        {

            /* Get the check start address from the configuration information */
            u4aBlkStaAddr = MemInstance.MemSectorBatch[u1aLoopCnt].MemStartAddress;

            /* Calculate the check end address from the number of consecutive sectors in the configuration information */
            u4aBlkEndAddr = u4aBlkStaAddr + (MemInstance.MemSectorBatch[u1aLoopCnt].MemEraseSectorSize * MemInstance.MemSectorBatch[u1aLoopCnt].MemNumberOfSectors);

            /* Calculate the Address Align */
            if( MEM_REQ_READ == u1ReqKind )
            {
                /* Since there are no restrictions on the start address, alignment check is not required */
                u4aRemainderAddr = MEM_U4_VAL_0;
            }
            else
            {
                u4aRemainderAddr = (u4Addr & (u4aChkSize - 1UL));
            }

            /* Job start address within block range and job size alignment */
            if( ( u4aBlkStaAddr <= u4Addr ) &&
                ( u4aBlkEndAddr >  u4Addr ) &&
                ( MEM_U4_VAL_0 == u4aRemainderAddr ) )
            {

                if( u4Addr <= (MEM_U4_VAL_MAX - u4Size) )
                {
                    /* Calculate the job end address */
                    u4aJobEndAddr = u4Addr + u4Size;

                    /* Calculate the Size Align */
                    u4aRemainderSize = (u4Size & (u4aChkSize - 1UL));

                    /* Job end address within block range and job size alignment */
                    if( ( u4aBlkEndAddr >=  u4aJobEndAddr ) &&
                        ( MEM_U4_VAL_0 == u4aRemainderSize ) )
                    {
                        /* Set return value to loop counter */
                        u1aRet = u1aLoopCnt;
                    }
                    else
                    {
                        /* Set return value to MEM_U1_INFONUM_NONE_LEN */
                        u1aRet = MEM_U1_INFONUM_NONE_LEN;
                    }
                }
                else
                {
                    /* Set return value to MEM_U1_INFONUM_NONE_LEN */
                    u1aRet = MEM_U1_INFONUM_NONE_LEN;
                }

                /* Search ends because the target address has been found in the configuration range. */
                break;
            }
            else
            {

                /* Next block check or Address error */
            }
        }
        else
        {
            if( MEM_REQ_BLANKCHECK == u1ReqKind )
            {
                /* Set return value to MEM_U1_INFONUM_NONE_KIND */
                u1aRet = MEM_U1_INFONUM_NONE_KIND;
            }
            else
            {
                /* Set return value to MEM_U1_INFONUM_NONE_LEN */
                u1aRet = MEM_U1_INFONUM_NONE_LEN;
            }
        }
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | Mem_Sub_CheckCodeFlsJob                                  */
/* Description   | Request codeFls job.                                     */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(void, MEM_CODE) Mem_Sub_CheckCodeFlsJob(void)
{
    VAR(uint8, AUTOMATIC) u1_CodeFlsStatus;
    VAR(uint8, AUTOMATIC) u1_CodeFlsJobResult;

    u1_CodeFlsStatus = CodeFls_GetJobStatus();
    if( CODEFLS_IDLE == u1_CodeFlsStatus )
    {

        CodeFls_EndCtrl();

        u1_CodeFlsJobResult = CodeFls_GetJobResult();

        if( CODEFLS_JOB_OK == u1_CodeFlsJobResult )
        {
            if( MEM_U4_VAL_0  < Mem_stgMultiOpInfo.u4OpSize )
            {
                /* Mem_u1gJobStatus keeps MEM_BUSY */
                /* Mem_u1gJobResult keeps MEM_JOB_PENDING */
                Mem_stgMultiOpInfo.u1CtrlStartFlag  = MEM_U1_FALSE;
                Mem_stgMirrorArea.u1CheckCtrlStartFlag = Mem_stgMultiOpInfo.u1CtrlStartFlag;
            }
            else
            {
                Mem_Sub_SetJobStatus(MEM_IDLE);
                Mem_u1gJobResult = MEM_JOB_OK;
                Mem_u1gMirrorJobResult = Mem_u1gJobResult;
                Mem_Sub_sInitOpInfo();
            }
        }
        else if( CODEFLS_INCONSISTENT == u1_CodeFlsJobResult )
        {
            Mem_Sub_SetJobStatus(MEM_IDLE);
            /* Set MEM_INCONSISTENT to job processing result */
            Mem_u1gJobResult = MEM_INCONSISTENT;
            Mem_u1gMirrorJobResult = Mem_u1gJobResult;
            Mem_Sub_sInitOpInfo();
        }
        else
        {
            Mem_Sub_SetJobStatus(MEM_IDLE);
            /* Set MEM_JOB_FAILED to job processing result */
            Mem_u1gJobResult = MEM_JOB_FAILED;
            Mem_u1gMirrorJobResult = Mem_u1gJobResult;
            Mem_Sub_sInitOpInfo();
        }

    }
    else if( CODEFLS_BUSY == u1_CodeFlsStatus )
    {
        /* No process */
    }
    else
    {
        CodeFls_EndCtrl();
        Mem_Sub_Failed();
        Mem_Sub_sInitOpInfo();
    }

    return;
}

/****************************************************************************/
/* Function Name | Mem_Sub_EraseReq                                         */
/* Description   | Request the Erase of a job in CodeFls.                   */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | E_OK            :Successful completion                   */
/*               | E_NOT_OK        :Failed                                  */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(void, MEM_CODE) Mem_Sub_EraseReq(void)
{
    VAR(CodeFls_BlockInfoType, AUTOMATIC) BlockInfo;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    if( MEM_U1_VAL_0 == Mem_u1gJobDelayCount )
    {
        BlockInfo.Addr = MEM_INVALID_ADDR;
        BlockInfo.Size = MEM_INVALID_SIZE;
        FuncRet = CodeFls_GetBlockInfo(Mem_stgMultiOpInfo.u4OpAddr, &BlockInfo);
        if( (Std_ReturnType)E_OK == FuncRet )
        {
            FuncRet = CodeFls_StartCtrl(Mem_stgMultiOpInfo.u1Cmd, Mem_stgMultiOpInfo.u4OpAddr, BlockInfo.Size);

            if( (Std_ReturnType)E_OK == FuncRet )
            {
                Mem_stgMultiOpInfo.u1CtrlStartFlag  = MEM_U1_TRUE;
                Mem_stgMirrorArea.u1CheckCtrlStartFlag = Mem_stgMultiOpInfo.u1CtrlStartFlag;

                CodeFls_Erase(Mem_stgMultiOpInfo.u4OpAddr, BlockInfo.Size);

                Mem_stgMultiOpInfo.u4OpAddr += BlockInfo.Size;      /* no wrap around */
                Mem_stgMirrorArea.u4CheckAddr = Mem_stgMultiOpInfo.u4OpAddr;

                Mem_stgMultiOpInfo.u4OpSize -= BlockInfo.Size;      /* no wrap around */
                Mem_stgMirrorArea.u4CheckSize = Mem_stgMultiOpInfo.u4OpSize;

                Mem_u1gJobDelayCount = MEM_DEVCFG_DATA.Mem_Ab_ControlSetting->Mem_Ab_Erase_Delay_Count;

                Mem_Sub_CheckCodeFlsJob();
            }
            else
            {
                Mem_Sub_Failed();
            }
        }
        else
        {
            Mem_Sub_Failed();
        }
    }
    else
    {
        Mem_u1gJobDelayCount--;
    }

    return;
}

/****************************************************************************/
/* Function Name | Mem_Sub_WriteReq                                         */
/* Description   | Request the Write of a job in CodeFls.                   */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | E_OK            :Successful completion                   */
/*               | E_NOT_OK        :Failed                                  */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(void, MEM_CODE) Mem_Sub_WriteReq(void)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;
    VAR(uint32, AUTOMATIC) u4_WriteSize;

    if( MEM_U1_VAL_0 == Mem_u1gJobDelayCount )
    {
        u4_WriteSize = Mem_SizeInfo.u4WriteSize;
        FuncRet = CodeFls_StartCtrl(Mem_stgMultiOpInfo.u1Cmd, Mem_stgMultiOpInfo.u4OpAddr, u4_WriteSize);

        if( (Std_ReturnType)E_OK == FuncRet )
        {
            Mem_stgMultiOpInfo.u1CtrlStartFlag  = MEM_U1_TRUE;
            Mem_stgMirrorArea.u1CheckCtrlStartFlag = Mem_stgMultiOpInfo.u1CtrlStartFlag;

            CodeFls_Write(Mem_stgMultiOpInfo.u4OpAddr, Mem_stgMultiOpInfo.pu1WriteBufAddr, u4_WriteSize);

            Mem_stgMultiOpInfo.u4OpAddr += u4_WriteSize;        /* no wrap around */
            Mem_stgMirrorArea.u4CheckAddr = Mem_stgMultiOpInfo.u4OpAddr;

            Mem_stgMultiOpInfo.pu1WriteBufAddr = &Mem_stgMultiOpInfo.pu1WriteBufAddr[u4_WriteSize];
            Mem_stgMirrorArea.pu1CheckWriteBuf = Mem_stgMultiOpInfo.pu1WriteBufAddr;

            Mem_stgMultiOpInfo.u4OpSize -= u4_WriteSize;        /* no wrap around */
            Mem_stgMirrorArea.u4CheckSize = Mem_stgMultiOpInfo.u4OpSize;

            Mem_u1gJobDelayCount = MEM_DEVCFG_DATA.Mem_Ab_ControlSetting->Mem_Ab_Write_Delay_Count;

            Mem_Sub_CheckCodeFlsJob();
        }
        else
        {
            Mem_Sub_Failed();
        }
    }
    else
    {
        Mem_u1gJobDelayCount--;
    }

    return;
}

/****************************************************************************/
/* Function Name | Mem_Sub_BlankCheckReq                                    */
/* Description   | Request the BlankCheck of a job in CodeFls.              */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | E_OK            :Successful completion                   */
/*               | E_NOT_OK        :Failed                                  */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(void, MEM_CODE) Mem_Sub_BlankCheckReq(void)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;
    VAR(uint32, AUTOMATIC) u4_BlankCheckSize;

    u4_BlankCheckSize = Mem_SizeInfo.u4BlankCheckSize;
    FuncRet = CodeFls_StartCtrl(Mem_stgMultiOpInfo.u1Cmd, Mem_stgMultiOpInfo.u4OpAddr, u4_BlankCheckSize);
    if( (Std_ReturnType)E_OK == FuncRet )
    {

        Mem_stgMultiOpInfo.u1CtrlStartFlag  = MEM_U1_TRUE;
        Mem_stgMirrorArea.u1CheckCtrlStartFlag = Mem_stgMultiOpInfo.u1CtrlStartFlag;

        CodeFls_BlankCheck(Mem_stgMultiOpInfo.u4OpAddr, u4_BlankCheckSize);

        Mem_stgMultiOpInfo.u4OpAddr += u4_BlankCheckSize;        /* no wrap around */
        Mem_stgMirrorArea.u4CheckAddr = Mem_stgMultiOpInfo.u4OpAddr;

        Mem_stgMultiOpInfo.u4OpSize -= u4_BlankCheckSize;        /* no wrap around */
        Mem_stgMirrorArea.u4CheckSize = Mem_stgMultiOpInfo.u4OpSize;

        Mem_Sub_CheckCodeFlsJob();
    }
    else
    {
        Mem_Sub_Failed();
    }

    return;
}

/****************************************************************************/
/* Function Name | Mem_Sub_SwitchValidAreaReq                               */
/* Description   | Request the SwitchValidArea of a job in CodeFls.         */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | E_OK            :Successful completion                   */
/*               | E_NOT_OK        :Failed                                  */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(void, MEM_CODE) Mem_Sub_SwitchValidAreaReq(void)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    FuncRet = CodeFls_StartCtrl(Mem_stgMultiOpInfo.u1Cmd, Mem_stgMultiOpInfo.u4OpAddr, Mem_stgMultiOpInfo.u4OpSize);
    if( (Std_ReturnType)E_OK == FuncRet )
    {
        Mem_stgMultiOpInfo.u1CtrlStartFlag  = MEM_U1_TRUE;
        Mem_stgMirrorArea.u1CheckCtrlStartFlag = Mem_stgMultiOpInfo.u1CtrlStartFlag;

        CodeFls_SwitchValidArea();

        Mem_Sub_CheckCodeFlsJob();
    }
    else
    {
        Mem_Sub_Failed();
    }

    return;
}

/******************************************************************************/
/* Function Name | Mem_Sub_CheckBlockInfo                                     */
/* Description   | Check the address of GetBlockInfo.                         */
/* Preconditions |                                                            */
/* Parameters    | [IN] TargetAddr : Erase address                            */
/*               | [IN] TargetSize : Erase size                               */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(Std_ReturnType, MEM_CODE) Mem_Sub_CheckBlockInfo
(
    VAR(uint32, AUTOMATIC) TargetAddr,
    VAR(uint32, AUTOMATIC) TargetSize
)
{
    VAR(Std_ReturnType, AUTOMATIC) Result;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;
    VAR(CodeFls_BlockInfoType, AUTOMATIC) BlockInfo;

    Result = E_NOT_OK;

    if( 0UL != TargetSize )
    {
        BlockInfo.Addr = MEM_INVALID_ADDR;
        BlockInfo.Size = MEM_INVALID_SIZE;
        FuncRet = CodeFls_GetBlockInfo(TargetAddr, &BlockInfo);
        if( (Std_ReturnType)E_OK == FuncRet )
        {
            if( BlockInfo.Addr == TargetAddr )
            {
                FuncRet = CodeFls_GetBlockInfo(TargetAddr + (TargetSize - MEM_ADJUST_ENDADDR), &BlockInfo);   /* no wrap around */
                if( (Std_ReturnType)E_OK == FuncRet )
                {
                    if( (BlockInfo.Addr + (BlockInfo.Size - MEM_ADJUST_ENDADDR)) ==    /* no wrap around */
                            (TargetAddr + (TargetSize - MEM_ADJUST_ENDADDR)) )         /* no wrap around */
                    {
                        Result = E_OK;
                    }
                }
            }
        }
    }

    return Result;
}

#define MEM_STOP_SEC_CODE
#include <Mem_MemMap.h>


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1.00          :2025/03/24                                              */
/*  v1.01          :2025/04/14                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
