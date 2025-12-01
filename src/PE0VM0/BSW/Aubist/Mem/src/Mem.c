/* Mem_c                                                                    */
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
#include "../inc/Mem_Internal.h"
#include "../inc/Mem_Sub.h"
#include "../inc/CodeFls.h"
#include "../usr/Mem_Usr.h"


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define MEM_START_SEC_VAR_NO_INIT_32
#include <Mem_MemMap.h>

VAR(uint8, MEM_VAR_NO_INIT) Mem_u1gJobStatus;                 /* Job Status                                   */
VAR(uint8, MEM_VAR_NO_INIT) Mem_u1gMirrorJobStatus;           /* Job Status Mirror Area                       */
VAR(uint8, MEM_VAR_NO_INIT) Mem_u1gJobResult;                 /* Job Processing Results                       */
VAR(uint8, MEM_VAR_NO_INIT) Mem_u1gMirrorJobResult;           /* Job Processing Results Mirror Area           */
VAR(uint8, MEM_VAR_NO_INIT) Mem_u1gErrorNotifyFlag;           /* Error Notification Receive Flag              */
VAR(uint8, MEM_VAR_NO_INIT) Mem_u1gMirrorErrorNotifyFlag;     /* Error Notification Receive Flag Mirror Area  */
VAR(Mem_MultiOpType, MEM_VAR_NO_INIT)  Mem_stgMultiOpInfo;    /* Operational Information                      */
VAR(Mem_OpMirrorType, MEM_VAR_NO_INIT) Mem_stgMirrorArea;     /* Operation Information Mirror Area            */
VAR(uint8, MEM_VAR_NO_INIT) Mem_u1gJobDelayCount;             /* Job Delay Counter                            */

#define MEM_STOP_SEC_VAR_NO_INIT_32
#include <Mem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define MEM_START_SEC_CONST_32
#include <Mem_MemMap.h>

static CONST( AB_83_ConstV Std_VersionInfoType, MEM_CONST ) Mem_VersionInfo = {
    MEM_VERSIONINFO_VENDER_ID,          /* vendorID          */
    MEM_VERSIONINFO_MODULE_ID,          /* moduleID          */
    MEM_VERSIONINFO_SW_MAJOR_VERSION,   /* sw_major_version  */
    MEM_VERSIONINFO_SW_MINOR_VERSION,   /* sw_minor_version  */
    MEM_VERSIONINFO_SW_PATCH_VERSION    /* sw_patch_version  */
};

#define MEM_STOP_SEC_CONST_32
#include <Mem_MemMap.h>


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define MEM_START_SEC_CODE_FAR
#include <Mem_MemMap.h>

/****************************************************************************/
/* Function Name | Mem_Init                                                 */
/* Description   | In preparation for rewriting the code flash memory, the  */
/*               | necessary initialization processing is performed for the */
/*               | RAM used by the OTA_CodeFlash driver and the flash       */
/*               | controller.                                              */
/* Preconditions | -                                                        */
/* Parameters    | [IN]configPtr : Storage area for configuration           */
/*               |                 information.                             */
/* Return Value  | -                                                        */
/* Notes         | Synchronous processing                                   */
/****************************************************************************/
FUNC(void, MEM_CODE_FAR) Mem_Init
(
    P2CONST(Mem_ConfigType, AUTOMATIC, MEM_APPL_DATA) configPtr
)
{
    /* Variable Declarations */
    VAR(uint8, AUTOMATIC) u1aMemInstanceId;
    VAR(uint8, AUTOMATIC) u1_CodeFlsStatus;

    /* Configuration parameter is null */
    if( NULL_PTR == configPtr )
    {
        /* Initialize RAM */
        Mem_Sub_InitVariables();

        CodeFls_Init();

        u1_CodeFlsStatus = CodeFls_GetJobStatus();
        if( CODEFLS_IDLE == u1_CodeFlsStatus )
        {
            /* Set Job Status to MEM_IDLE */
            Mem_Sub_SetJobStatus(MEM_IDLE);
            /* Set MEM_JOB_OK to job processing result */
            Mem_u1gJobResult = MEM_JOB_OK;
            Mem_u1gMirrorJobResult = Mem_u1gJobResult;
        }
        else
        {
            /* Set MEM_JOB_FAILED to job processing result */
            Mem_u1gJobResult = MEM_JOB_FAILED;
            Mem_u1gMirrorJobResult = Mem_u1gJobResult;
        }
    }
    else
    {
        /* Set MEM_JOB_FAILED to job processing result */
        Mem_u1gJobResult = MEM_JOB_FAILED;
        Mem_u1gMirrorJobResult = Mem_u1gJobResult;

        /* Error notification for development - Configuration parameter error */
        u1aMemInstanceId = (uint8)MemInstance.MemInstanceId;
        Mem_Sub_Det_ReportError((uint16)MEM_MODULE_ID, u1aMemInstanceId, (uint8)MEM_API_ID_INIT, (uint8)MEM_E_PARAM_POINTER);
    }

    return;
}

/****************************************************************************/
/* Function Name | Mem_GetVersionInfo                                       */
/* Description   | Get OTA_CodeFlash driver version information.            */
/* Preconditions | -                                                        */
/* Parameters    | [OUT]versionInfoPtr : Storage space for version          */
/*               |                       information                        */
/* Return Value  | -                                                        */
/* Notes         | Synchronous processing                                   */
/****************************************************************************/
FUNC(void, MEM_CODE_FAR) Mem_GetVersionInfo
(
    P2VAR(Std_VersionInfoType, AUTOMATIC, MEM_APPL_DATA) versionInfoPtr
)
{
    VAR(uint8, AUTOMATIC) u1aMemInstanceId;

    /* VersionInfo parameter is not null */
    if( NULL_PTR != versionInfoPtr )
    {
        /* Set Version Information to Parameters */
        versionInfoPtr->vendorID         = Mem_VersionInfo.vendorID;
        versionInfoPtr->moduleID         = Mem_VersionInfo.moduleID;
        versionInfoPtr->sw_major_version = Mem_VersionInfo.sw_major_version;
        versionInfoPtr->sw_minor_version = Mem_VersionInfo.sw_minor_version;
        versionInfoPtr->sw_patch_version = Mem_VersionInfo.sw_patch_version;
    }
    else
    {
        /* Error notification for development - Param pointer error */
        u1aMemInstanceId = (uint8)MemInstance.MemInstanceId;
        Mem_Sub_Det_ReportError((uint16)MEM_MODULE_ID,u1aMemInstanceId, (uint8)MEM_API_ID_GETVERSIONINFO, (uint8)MEM_E_PARAM_POINTER);
    }

    return;
}

/****************************************************************************/
/* Function Name | Mem_MainFunction                                         */
/* Description   | Check the progress of code flush control jobs and update */
/*               | job status and job results.                              */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | -                                                        */
/* Notes         | Asynchronous processing                                  */
/****************************************************************************/
FUNC(void, MEM_CODE_FAR) Mem_MainFunction(void)
{
    VAR(Std_ReturnType, AUTOMATIC) u1aResult;

    if( Mem_u1gMirrorJobStatus == Mem_u1gJobStatus )
    {
        if( MEM_BUSY == Mem_u1gJobStatus )
        {
            u1aResult = Mem_Sub_CheckMirrorOpInfo();
            if( (Std_ReturnType)E_OK == u1aResult )
            {
                if( MEM_REQ_READ == Mem_stgMultiOpInfo.u1Cmd )
                {
                    Mem_Sub_ReadOp();
                }
                else
                {
                    if( MEM_U1_FALSE == Mem_stgMultiOpInfo.u1CtrlStartFlag )
                    {
                        Mem_Sub_ReqCodeFls();
                    }
                    else
                    {
                        Mem_Sub_CmpltChkCodeFls();
                    }
                }
            }
            else
            {
                Mem_Sub_Failed();
                CodeFls_ClearJobStatus();
            }
        }
    }
    else
    {
        Mem_Sub_Failed();
        CodeFls_ClearJobStatus();
    }

    return;
}

/****************************************************************************/
/* Function Name | Mem_GetJobResult                                         */
/* Description   | Check the job results for the code flash memory and      */
/*               | return the return value according to each result.        */
/* Preconditions | -                                                        */
/* Parameters    | [IN]instanceId           : Instance ID                   */
/* Return Value  | MEM_JOB_OK               : Successful completion         */
/*               | MEM_JOB_PENDING          : In Progress                   */
/*               | MEM_JOB_FAILED           : Failed                        */
/*               | MEM_INCONSISTENT         : Blank check error             */
/*               | MEM_ECC_UNCORRECTED      : Unrecoverable ECC error       */
/*               | MEM_ECC_CORRECTED        : Recoverable ECC error         */
/* Notes         | Synchronous processing                                   */
/****************************************************************************/
FUNC(Mem_JobResultType, MEM_CODE_FAR) Mem_GetJobResult
(
    VAR(Mem_InstanceIdType, AUTOMATIC) instanceId   /* MISRA DEVIATION */ /* For the commonization of source code */
)
{
    if( Mem_u1gMirrorJobResult == Mem_u1gJobResult )
    {
        /* Do Nothing */
    }
    else
    {
        Mem_u1gJobResult = MEM_JOB_FAILED;
        Mem_u1gMirrorJobResult = Mem_u1gJobResult;
    }

    return((Mem_JobResultType)Mem_u1gJobResult);
}

/****************************************************************************/
/* Function Name | Mem_Read                                                 */
/* Description   | Read from the specified address in memory by the         */
/*               | specified size and store it in the data reading area.    */
/* Preconditions | -                                                        */
/* Parameters    | [IN]instanceId          : Instance ID                    */
/*               | [IN]sourceAddress       : Read start address             */
/*               | [OUT]destinationDataPtr : Read data storage area         */
/*               | [IN]length              : Read data length               */
/* Return Value  | E_OK                    : Successful completion          */
/*               | E_NOT_OK                : Failed                         */
/*               | E_MEM_SERVICE_NOT_AVAIL : The service is not implemented */
/* Notes         | Asynchronous processing                                  */
/****************************************************************************/
FUNC(Std_ReturnType, MEM_CODE_FAR) Mem_Read
(
    VAR(Mem_InstanceIdType, AUTOMATIC) instanceId,
    VAR(Mem_AddressType, AUTOMATIC) sourceAddress,
    P2VAR(Mem_DataType, AUTOMATIC, MEM_APPL_DATA) destinationDataPtr,
    VAR(Mem_LengthType, AUTOMATIC) length
)
{
    /* Variable Declarations */
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;
    VAR(uint8, AUTOMATIC) u1aInfoNum;

    if( Mem_u1gMirrorJobStatus == Mem_u1gJobStatus )
    {
        /* Job status is MEM_IDLE */
        if( MEM_IDLE == Mem_u1gJobStatus )
        {
            /* Set Error Notification Receive Flag to MEM_U1_FALSE */
            Mem_u1gErrorNotifyFlag = MEM_U1_FALSE;
            Mem_u1gMirrorErrorNotifyFlag = Mem_u1gErrorNotifyFlag;

            /* Bank Number Initialization */
            u1aInfoNum = MEM_U1_INFONUM_0;
            /* Check Parameter and get Bank Number */
            u1aRet = Mem_Sub_CheckParamRead(instanceId, (uint32)sourceAddress, destinationDataPtr, (uint32)length, &u1aInfoNum);

            /* Parameter check is E_OK */
            if( (Std_ReturnType)E_OK == u1aRet )
            {
                /* Configuring Operation Information */
                Mem_stgMultiOpInfo.u1Cmd            = MEM_REQ_READ;
                Mem_stgMultiOpInfo.u4OpAddr         = (uint32)sourceAddress;
                Mem_stgMultiOpInfo.pu1ReadBufAddr   = destinationDataPtr;
                Mem_stgMultiOpInfo.pu1WriteBufAddr  = MEM_PU1_OPINFO_BUFFER_NULL;
                Mem_stgMultiOpInfo.u4OpSize         = (uint32)length;
                Mem_stgMultiOpInfo.u1SectorBatchNum = u1aInfoNum;
                Mem_stgMultiOpInfo.u1CtrlStartFlag  = MEM_U1_FALSE;
                Mem_stgMultiOpInfo.u1ECCErrStatus   = MEM_JOB_OK;

                /* Configuring Operation Mirror Information */
                Mem_stgMirrorArea.u1CheckCmd            = Mem_stgMultiOpInfo.u1Cmd;
                Mem_stgMirrorArea.u4CheckAddr           = Mem_stgMultiOpInfo.u4OpAddr;
                Mem_stgMirrorArea.pu1CheckReadBuf       = Mem_stgMultiOpInfo.pu1ReadBufAddr;
                Mem_stgMirrorArea.pu1CheckWriteBuf      = Mem_stgMultiOpInfo.pu1WriteBufAddr;
                Mem_stgMirrorArea.u4CheckSize           = Mem_stgMultiOpInfo.u4OpSize;
                Mem_stgMirrorArea.u1CheckSectorBatchNum = Mem_stgMultiOpInfo.u1SectorBatchNum;
                Mem_stgMirrorArea.u1CheckCtrlStartFlag  = Mem_stgMultiOpInfo.u1CtrlStartFlag;
                Mem_stgMirrorArea.u1CheckECCErrStatus   = Mem_stgMultiOpInfo.u1ECCErrStatus;

                /* Set Job Status to MEM_BUSY */
                Mem_Sub_SetJobStatus(MEM_BUSY);
                /* Set job processing result to MEM_JOB_PENDING */
                Mem_u1gJobResult = MEM_JOB_PENDING;
                Mem_u1gMirrorJobResult = Mem_u1gJobResult;
            }
            else
            {
                /* Parameter Error */
                /* Do not change Mem_u1gJobResult */
            }
        }
        else
        {
            /* Job Status is MEM_UNINIT */
            if( MEM_UNINIT == Mem_u1gJobStatus )
            {
                /* Error notification for development - Job status error - UNINIT */
                Mem_Sub_Det_ReportError((uint16)MEM_MODULE_ID, (uint8)instanceId, (uint8)MEM_API_ID_READ, (uint8)MEM_E_UNINIT);
            }
            else if( MEM_BUSY == Mem_u1gJobStatus )
            {/* Job Status is MEM_BUSY */
                /* Error notification for development - Job status error - BUSY */
                Mem_Sub_Det_ReportError((uint16)MEM_MODULE_ID, (uint8)instanceId, (uint8)MEM_API_ID_READ, (uint8)MEM_E_JOB_PENDING);
            }
            else
            {
                /* Do Nothing */
            }
            /* Set return value is E_NOT_OK */
            /* Do not change Mem_u1gJobResult */
            u1aRet = E_NOT_OK;
        }
    }
    else
    {
        u1aRet = E_NOT_OK;
    }

    return((Std_ReturnType)u1aRet);
}

/****************************************************************************/
/* Function Name | Mem_Write                                                */
/* Description   | Execute a write of the write data size from the          */
/*               | write-start address specified in the argument.           */
/* Preconditions | -                                                        */
/* Parameters    | [IN]instanceId          : Instance ID                    */
/*               | [IN]targetAddress       : Write start address            */
/*               | [IN]sourceDataPtr       : Write data storage space       */
/*               | [IN]length              : Write data length              */
/* Return Value  | E_OK                    : Successful completion          */
/*               | E_NOT_OK                : Failed                         */
/*               | E_MEM_SERVICE_NOT_AVAIL : The service is not implemented */
/* Notes         | Asynchronous processing                                  */
/****************************************************************************/
FUNC(Std_ReturnType, MEM_CODE_FAR) Mem_Write
(
    VAR(Mem_InstanceIdType, AUTOMATIC) instanceId,
    VAR(Mem_AddressType, AUTOMATIC) targetAddress,
    P2CONST(Mem_DataType, AUTOMATIC, MEM_APPL_DATA) sourceDataPtr,
    VAR(Mem_LengthType, AUTOMATIC) length
)
{
    /* Variable Declarations */
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;
    VAR(uint8, AUTOMATIC) u1aInfoNum;

    if( Mem_u1gMirrorJobStatus == Mem_u1gJobStatus )
    {
        /* Job status is MEM_IDLE */
        if( MEM_IDLE == Mem_u1gJobStatus )
        {
            /* Bank Number Initialization */
            u1aInfoNum = MEM_U1_INFONUM_0;
            /* Check Parameter and get Bank Number */
            u1aRet = Mem_Sub_CheckParamWrite(instanceId, (uint32)targetAddress, sourceDataPtr, (uint32)length, &u1aInfoNum);

            /* Parameter check is E_OK */
            if( (Std_ReturnType)E_OK == u1aRet )
            {
                /* Configuring Operation Information */
                Mem_stgMultiOpInfo.u1Cmd            = MEM_REQ_WRITE;
                Mem_stgMultiOpInfo.u4OpAddr         = (uint32)targetAddress;
                Mem_stgMultiOpInfo.pu1ReadBufAddr   = MEM_PU1_OPINFO_BUFFER_NULL;
                Mem_stgMultiOpInfo.pu1WriteBufAddr  = sourceDataPtr;
                Mem_stgMultiOpInfo.u4OpSize         = (uint32)length;
                Mem_stgMultiOpInfo.u1SectorBatchNum = u1aInfoNum;
                Mem_stgMultiOpInfo.u1CtrlStartFlag  = MEM_U1_FALSE;
                Mem_stgMultiOpInfo.u1ECCErrStatus   = MEM_JOB_OK;

                /* Configuring Operation Mirror Information */
                Mem_stgMirrorArea.u1CheckCmd            = Mem_stgMultiOpInfo.u1Cmd;
                Mem_stgMirrorArea.u4CheckAddr           = Mem_stgMultiOpInfo.u4OpAddr;
                Mem_stgMirrorArea.pu1CheckReadBuf       = Mem_stgMultiOpInfo.pu1ReadBufAddr;
                Mem_stgMirrorArea.pu1CheckWriteBuf      = Mem_stgMultiOpInfo.pu1WriteBufAddr;
                Mem_stgMirrorArea.u4CheckSize           = Mem_stgMultiOpInfo.u4OpSize;
                Mem_stgMirrorArea.u1CheckSectorBatchNum = Mem_stgMultiOpInfo.u1SectorBatchNum;
                Mem_stgMirrorArea.u1CheckCtrlStartFlag  = Mem_stgMultiOpInfo.u1CtrlStartFlag;
                Mem_stgMirrorArea.u1CheckECCErrStatus   = Mem_stgMultiOpInfo.u1ECCErrStatus;

                /* Reset the job delay counter */
                Mem_u1gJobDelayCount = MEM_U1_VAL_0;

                /* Set Job Status to MEM_BUSY */
                Mem_Sub_SetJobStatus(MEM_BUSY);
                /* Set job processing result to MEM_JOB_PENDING */
                Mem_u1gJobResult = MEM_JOB_PENDING;
                Mem_u1gMirrorJobResult = Mem_u1gJobResult;
            }
            else
            {
                /* Parameter Error */
                /* Do not change Mem_u1gJobResult */
            }
        }
        else
        {
            /* Job Status is MEM_UNINIT */
            if( MEM_UNINIT == Mem_u1gJobStatus )
            {
                /* Error notification for development - Job status error - UNINIT */
                Mem_Sub_Det_ReportError((uint16)MEM_MODULE_ID, (uint8)instanceId, (uint8)MEM_API_ID_WRITE, (uint8)MEM_E_UNINIT);
            }
            else if( MEM_BUSY == Mem_u1gJobStatus )
            {/* Job status is MEM_BUSY */
                /* Error notification for development - Job status error - BUSY */
                Mem_Sub_Det_ReportError((uint16)MEM_MODULE_ID, (uint8)instanceId, (uint8)MEM_API_ID_WRITE, (uint8)MEM_E_JOB_PENDING);
            }
            else
            {
                /* Do Nothing */
            }
            /* Set return value is E_NOT_OK */
            /* Do not change Mem_u1gJobResult */
            u1aRet = E_NOT_OK;
        }
    }
    else
    {
        u1aRet = E_NOT_OK;
    }

    return((Std_ReturnType)u1aRet);
}

/****************************************************************************/
/* Function Name | Mem_Erase                                                */
/* Description   | Perform the erase operation on the block indicated by    */
/*               | the erase start address and erase size specified in the  */
/*               | argument.                                                */
/* Preconditions | -                                                        */
/* Parameters    | [IN]instanceId          : Instance ID                    */
/*               | [IN]targetAddress       : Erase Start Address            */
/*               | [IN]length              : Erased data length             */
/* Return Value  | E_OK                    : Successful completion          */
/*               | E_NOT_OK                : Failed                         */
/*               | E_MEM_SERVICE_NOT_AVAIL : The service is not implemented */
/* Notes         | Asynchronous processing                                  */
/****************************************************************************/
FUNC(Std_ReturnType, MEM_CODE_FAR) Mem_Erase
(
    VAR(Mem_InstanceIdType, AUTOMATIC) instanceId,
    VAR(Mem_AddressType, AUTOMATIC) targetAddress,
    VAR(Mem_LengthType, AUTOMATIC) length
)
{
    /* Variable Declarations */
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;
    VAR(uint8, AUTOMATIC) u1aInfoNum;

    if( Mem_u1gMirrorJobStatus == Mem_u1gJobStatus )
    {
        /* Job status is MEM_IDLE */
        if( MEM_IDLE == Mem_u1gJobStatus )
        {
            /* Bank Number Initialization */
            u1aInfoNum = MEM_U1_INFONUM_0;
            /* Check Parameter and get Bank Number */
            u1aRet = Mem_Sub_CheckParamErase(instanceId, (uint32)targetAddress, (uint32)length, &u1aInfoNum);

            /* Parameter check is E_OK */
            if( (Std_ReturnType)E_OK == u1aRet )
            {
                /* Configuring Operation Information */
                Mem_stgMultiOpInfo.u1Cmd            = MEM_REQ_ERASE;
                Mem_stgMultiOpInfo.u4OpAddr         = (uint32)targetAddress;
                Mem_stgMultiOpInfo.pu1ReadBufAddr   = MEM_PU1_OPINFO_BUFFER_NULL;
                Mem_stgMultiOpInfo.pu1WriteBufAddr  = MEM_PU1_OPINFO_BUFFER_NULL;
                Mem_stgMultiOpInfo.u4OpSize         = (uint32)length;
                Mem_stgMultiOpInfo.u1SectorBatchNum = u1aInfoNum;
                Mem_stgMultiOpInfo.u1CtrlStartFlag  = MEM_U1_FALSE;
                Mem_stgMultiOpInfo.u1ECCErrStatus   = MEM_JOB_OK;

                /* Configuring Operation Mirror Information */
                Mem_stgMirrorArea.u1CheckCmd            = Mem_stgMultiOpInfo.u1Cmd;
                Mem_stgMirrorArea.u4CheckAddr           = Mem_stgMultiOpInfo.u4OpAddr;
                Mem_stgMirrorArea.pu1CheckReadBuf       = Mem_stgMultiOpInfo.pu1ReadBufAddr;
                Mem_stgMirrorArea.pu1CheckWriteBuf      = Mem_stgMultiOpInfo.pu1WriteBufAddr;
                Mem_stgMirrorArea.u4CheckSize           = Mem_stgMultiOpInfo.u4OpSize;
                Mem_stgMirrorArea.u1CheckSectorBatchNum = Mem_stgMultiOpInfo.u1SectorBatchNum;
                Mem_stgMirrorArea.u1CheckCtrlStartFlag  = Mem_stgMultiOpInfo.u1CtrlStartFlag;
                Mem_stgMirrorArea.u1CheckECCErrStatus   = Mem_stgMultiOpInfo.u1ECCErrStatus;

                /* Reset the job delay counter */
                Mem_u1gJobDelayCount = MEM_U1_VAL_0;

                /* Set Job Status to MEM_BUSY */
                Mem_Sub_SetJobStatus(MEM_BUSY);
                /* Set job processing result to MEM_JOB_PENDING */
                Mem_u1gJobResult = MEM_JOB_PENDING;
                Mem_u1gMirrorJobResult = Mem_u1gJobResult;
            }
            else
            {
                /* Parameter Error */
                /* Do not change Mem_u1gJobResult */
            }
        }
        else
        {
            /* Job Status is MEM_UNINIT */
            if( MEM_UNINIT == Mem_u1gJobStatus )
            {
                /* Error notification for development - Job status error - UNINIT */
                Mem_Sub_Det_ReportError((uint16)MEM_MODULE_ID, (uint8)instanceId, (uint8)MEM_API_ID_ERASE, (uint8)MEM_E_UNINIT);
            }
            else if( MEM_BUSY == Mem_u1gJobStatus )
            {/* Job status is MEM_BUSY */
                /* Error notification for development - Job status error - BUSY */
                Mem_Sub_Det_ReportError((uint16)MEM_MODULE_ID, (uint8)instanceId, (uint8)MEM_API_ID_ERASE, (uint8)MEM_E_JOB_PENDING);
            }
            else
            {
                /* Do Nothing */
            }
            /* Set return value is E_NOT_OK */
            /* Do not change Mem_u1gJobResult */
            u1aRet = E_NOT_OK;
        }
    }
    else
    {
        u1aRet = E_NOT_OK;
    }

    return((Std_ReturnType)u1aRet);
}

/****************************************************************************/
/* Function Name | Mem_PropagateError                                       */
/* Description   | Notifies of ECC errors and suspends running jobs.        */
/* Preconditions | -                                                        */
/* Parameters    | [IN]instanceId : Instance ID                             */
/* Return Value  | -                                                        */
/* Notes         | Synchronous processing                                   */
/****************************************************************************/
FUNC(void, MEM_CODE_FAR) Mem_PropagateError
(
    VAR(Mem_InstanceIdType, AUTOMATIC) instanceId
)
{
    /* Variable Declarations */
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;

    if( Mem_u1gMirrorJobStatus == Mem_u1gJobStatus )
    {
        /* Job status is not MEM_UNINIT */
        if( MEM_UNINIT != Mem_u1gJobStatus )
        {
            /* Instance id check */
            u1aRet = Mem_Sub_InstanceIdCheck(instanceId);

            /* Instance id check result is E_OK */
            if( (Std_ReturnType)E_OK == u1aRet )
            {
                /* Set Error Notification Receive Flag to MEM_U1_TRUE */
                Mem_u1gErrorNotifyFlag = MEM_U1_TRUE;
                Mem_u1gMirrorErrorNotifyFlag = Mem_u1gErrorNotifyFlag;
            }
            else
            {
                /* Error notification for development - Instance id error  */
                Mem_Sub_Det_ReportError((uint16)MEM_MODULE_ID,(uint8)instanceId,(uint8)MEM_API_ID_PROPAGATEERROR,(uint8)MEM_E_PARAM_INSTANCE_ID);
            }
        }
        else
        {
            /* UNINIT is error */
            /* Error notification for development - Job status error - UNINIT */
            Mem_Sub_Det_ReportError((uint16)MEM_MODULE_ID, (uint8)instanceId, (uint8)MEM_API_ID_PROPAGATEERROR, (uint8)MEM_E_UNINIT);
            /* Do not change Mem_u1gJobResult */
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Mem_BlankCheck                                           */
/* Description   | Checks whether the start address and data size specified */
/*               | in the arguments can be written.                         */
/* Preconditions | -                                                        */
/* Parameters    | [IN]instanceId          : Instance ID                    */
/*               | [IN]targetAddress       : Blank check start address      */
/*               | [IN]length              : Blank check data length        */
/* Return Value  | E_OK                    : Successful completion          */
/*               | E_NOT_OK                : Failed                         */
/*               | E_MEM_SERVICE_NOT_AVAIL : The service is not implemented */
/* Notes         | Asynchronous processing                                  */
/****************************************************************************/
FUNC(Std_ReturnType, MEM_CODE_FAR) Mem_BlankCheck
(
    VAR(Mem_InstanceIdType, AUTOMATIC) instanceId,
    VAR(Mem_AddressType, AUTOMATIC) targetAddress,
    VAR(Mem_LengthType, AUTOMATIC) length
)
{
    /* Variable Declarations */
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;
    VAR(uint8, AUTOMATIC) u1aInfoNum;

    if( Mem_u1gMirrorJobStatus == Mem_u1gJobStatus )
    {
        /* Job status is MEM_IDLE */
        if( MEM_IDLE == Mem_u1gJobStatus )
        {
            /* Bank Number Initialization */
            u1aInfoNum = MEM_U1_INFONUM_0;
            /* Check Parameter and get Bank Number */
            u1aRet = Mem_Sub_CheckParamBlankCheck(instanceId, (uint32)targetAddress, (uint32)length, &u1aInfoNum);

            /* Parameter check is E_OK */
            if( (Std_ReturnType)E_OK == u1aRet )
            {
                /* Configuring Operation Information */
                Mem_stgMultiOpInfo.u1Cmd            = MEM_REQ_BLANKCHECK;
                Mem_stgMultiOpInfo.u4OpAddr         = (uint32)targetAddress;
                Mem_stgMultiOpInfo.pu1ReadBufAddr   = MEM_PU1_OPINFO_BUFFER_NULL;
                Mem_stgMultiOpInfo.pu1WriteBufAddr  = MEM_PU1_OPINFO_BUFFER_NULL;
                Mem_stgMultiOpInfo.u4OpSize         = (uint32)length;
                Mem_stgMultiOpInfo.u1SectorBatchNum = u1aInfoNum;
                Mem_stgMultiOpInfo.u1CtrlStartFlag  = MEM_U1_FALSE;
                Mem_stgMultiOpInfo.u1ECCErrStatus   = MEM_JOB_OK;

                /* Configuring Operation Mirror Information */
                Mem_stgMirrorArea.u1CheckCmd            = Mem_stgMultiOpInfo.u1Cmd;
                Mem_stgMirrorArea.u4CheckAddr           = Mem_stgMultiOpInfo.u4OpAddr;
                Mem_stgMirrorArea.pu1CheckReadBuf       = Mem_stgMultiOpInfo.pu1ReadBufAddr;
                Mem_stgMirrorArea.pu1CheckWriteBuf      = Mem_stgMultiOpInfo.pu1WriteBufAddr;
                Mem_stgMirrorArea.u4CheckSize           = Mem_stgMultiOpInfo.u4OpSize;
                Mem_stgMirrorArea.u1CheckSectorBatchNum = Mem_stgMultiOpInfo.u1SectorBatchNum;
                Mem_stgMirrorArea.u1CheckCtrlStartFlag  = Mem_stgMultiOpInfo.u1CtrlStartFlag;
                Mem_stgMirrorArea.u1CheckECCErrStatus   = Mem_stgMultiOpInfo.u1ECCErrStatus;

                /* Set Job Status to MEM_BUSY */
                Mem_Sub_SetJobStatus(MEM_BUSY);
                /* Set job processing result to MEM_JOB_PENDING */
                Mem_u1gJobResult = MEM_JOB_PENDING;
                Mem_u1gMirrorJobResult = Mem_u1gJobResult;
            }
            else
            {
                if( MEM_U1_INFONUM_NONE_KIND == u1aInfoNum )
                {
                    u1aRet = E_MEM_SERVICE_NOT_AVAIL;
                }
                else
                {
                    /* Parameter Error */
                    /* Do not change Mem_u1gJobResult */
                }
            }
        }
        else
        {
            /* Job Status is MEM_UNINIT */
            if( MEM_UNINIT == Mem_u1gJobStatus )
            {
                /* Error notification for development - Job status error - UNINIT */
                Mem_Sub_Det_ReportError((uint16)MEM_MODULE_ID, (uint8)instanceId, (uint8)MEM_API_ID_BLANKCHECK, (uint8)MEM_E_UNINIT);
            }
            else if( MEM_BUSY == Mem_u1gJobStatus )
            {/* Job status is MEM_BUSY */
                /* Error notification for development - Job status error - BUSY */
                Mem_Sub_Det_ReportError((uint16)MEM_MODULE_ID, (uint8)instanceId, (uint8)MEM_API_ID_BLANKCHECK, (uint8)MEM_E_JOB_PENDING);
            }
            else
            {
                /* Do Nothing */
            }
            /* Set return value is E_NOT_OK */
            /* Do not change Mem_u1gJobResult */
            u1aRet = E_NOT_OK;
        }
    }
    else
    {
        u1aRet = E_NOT_OK;
    }

    return((Std_ReturnType)u1aRet);
}

/****************************************************************************/
/* Function Name | Mem_HwSpecificService                                    */
/* Description   | Performs hardware-specific service processing specified  */
/*               | by the service ID.                                       */
/* Preconditions | -                                                        */
/* Parameters    | [IN]instanceId          : Instance ID                    */
/*               | [IN]hwServiceId         : Service ID                     */
/*               | [IN]dataPtr             : Data Area Pointer              */
/*               | [IN]lengthPtr           : Data Length Pointer            */
/* Return Value  | E_OK                    : Successful completion          */
/*               | E_NOT_OK                : Failed                         */
/*               | E_MEM_SERVICE_NOT_AVAIL : The service is not implemented */
/* Notes         | Asynchronous processing                                  */
/****************************************************************************/
/* MISRA DEVIATION */ /* dataPtr and lengthPtr may be able to be declared as a const object pointer type */
FUNC(Std_ReturnType, MEM_CODE_FAR) Mem_HwSpecificService
(
    VAR(Mem_InstanceIdType, AUTOMATIC) instanceId,
    VAR(Mem_HwServiceIdType, AUTOMATIC) hwServiceId,
    P2VAR(Mem_DataType, AUTOMATIC, MEM_APPL_DATA) dataPtr,
    P2VAR(Mem_LengthType, AUTOMATIC, MEM_APPL_DATA) lengthPtr
)
{
    /* Variable Declarations */
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;

    u1aRet = E_NOT_OK;

    if( Mem_u1gMirrorJobStatus == Mem_u1gJobStatus )
    {
        /* Job status is MEM_IDLE */
        if( MEM_IDLE == Mem_u1gJobStatus )
        {
            /* Data Area Pointer is not null */
            if( NULL_PTR != dataPtr )
            {
                /* Data Length Pointer is not null */
                if( NULL_PTR != lengthPtr )
                {
                    /* Instance id check */
                    u1aRet = Mem_Sub_InstanceIdCheck(instanceId);

                    /* Instance id check result is E_OK */
                    if( (Std_ReturnType)E_OK == u1aRet )
                    {
                        /* Process for each service id */
                        switch( hwServiceId )
                        {
                            /* Flash Memory valid area switching request */
                            case MEM_SRV_ID_SWITCHVALIDAREA :
                                /* Flash Memory valid area switchable check */
                                u1aRet = CodeFls_CheckSwitchValidArea();

                                /* Valid area check result is E_OK */
                                if( (Std_ReturnType)E_OK == u1aRet )
                                {
                                    u1aRet = Mem_Usr_Check_HwSpecificService();
                                    if( (Std_ReturnType)E_OK == u1aRet )
                                    {
                                        /* Configuring Operation Information */
                                        Mem_stgMultiOpInfo.u1Cmd            = MEM_REQ_SWITCHVALIDAREA;
                                        Mem_stgMultiOpInfo.u4OpAddr         = MEM_U4_OPINFO_ADDR_NONE;
                                        Mem_stgMultiOpInfo.pu1ReadBufAddr   = MEM_PU1_OPINFO_BUFFER_NULL;
                                        Mem_stgMultiOpInfo.pu1WriteBufAddr  = MEM_PU1_OPINFO_BUFFER_NULL;
                                        Mem_stgMultiOpInfo.u4OpSize         = MEM_U4_OPINFO_SIZE_NONE;
                                        Mem_stgMultiOpInfo.u1SectorBatchNum = MEM_U1_SECTOR_BATCH_NUM_NONE;
                                        Mem_stgMultiOpInfo.u1CtrlStartFlag  = MEM_U1_FALSE;
                                        Mem_stgMultiOpInfo.u1ECCErrStatus   = MEM_JOB_OK;

                                        /* Configuring Operation Mirror Information */
                                        Mem_stgMirrorArea.u1CheckCmd            = Mem_stgMultiOpInfo.u1Cmd;
                                        Mem_stgMirrorArea.u4CheckAddr           = Mem_stgMultiOpInfo.u4OpAddr;
                                        Mem_stgMirrorArea.pu1CheckReadBuf       = Mem_stgMultiOpInfo.pu1ReadBufAddr;
                                        Mem_stgMirrorArea.pu1CheckWriteBuf      = Mem_stgMultiOpInfo.pu1WriteBufAddr;
                                        Mem_stgMirrorArea.u4CheckSize           = Mem_stgMultiOpInfo.u4OpSize;
                                        Mem_stgMirrorArea.u1CheckSectorBatchNum = Mem_stgMultiOpInfo.u1SectorBatchNum;
                                        Mem_stgMirrorArea.u1CheckCtrlStartFlag  = Mem_stgMultiOpInfo.u1CtrlStartFlag;
                                        Mem_stgMirrorArea.u1CheckECCErrStatus   = Mem_stgMultiOpInfo.u1ECCErrStatus;

                                        /* Set Job Status to MEM_BUSY */
                                        Mem_Sub_SetJobStatus(MEM_BUSY);
                                        /* Set job processing result to MEM_JOB_PENDING */
                                        Mem_u1gJobResult = MEM_JOB_PENDING;
                                        Mem_u1gMirrorJobResult = Mem_u1gJobResult;

                                        break;
                                    }
                                }
                                else
                                {
                                    /* Parameter Error */
                                    /* Do not change Mem_u1gJobResult */
                                }
                                break;

                            default:
                                /* service id error */
                                /* Set job processing result to E_MEM_SERVICE_NOT_AVAIL */
                                u1aRet = E_MEM_SERVICE_NOT_AVAIL;
                                break;
                        }
                    }
                    else
                    {
                        /* Error notification for development - Instance id error  */
                        Mem_Sub_Det_ReportError((uint16)MEM_MODULE_ID,(uint8)instanceId,(uint8)MEM_API_ID_HWSPECIFICSERVICE,(uint8)MEM_E_PARAM_INSTANCE_ID);
                        /* Do not change Mem_u1gJobResult */
                    }
                }
                else
                {
                    /* Error notification for development - Data length error */
                    Mem_Sub_Det_ReportError((uint16)MEM_MODULE_ID,(uint8)instanceId,(uint8)MEM_API_ID_HWSPECIFICSERVICE,(uint8)MEM_E_PARAM_POINTER);
                    /* Do not change Mem_u1gJobResult */
                }
            }
            else
            {
                /* Error notification for development - Param pointer error */
                Mem_Sub_Det_ReportError((uint16)MEM_MODULE_ID,(uint8)instanceId,(uint8)MEM_API_ID_HWSPECIFICSERVICE,(uint8)MEM_E_PARAM_POINTER);
                /* Do not change Mem_u1gJobResult */
            }
        }
        else
        {
            /* Job Status is MEM_UNINIT */
            if( MEM_UNINIT == Mem_u1gJobStatus )
            {
                /* Error notification for development - Job status error - UNINIT */
                Mem_Sub_Det_ReportError((uint16)MEM_MODULE_ID, (uint8)instanceId, (uint8)MEM_API_ID_HWSPECIFICSERVICE, (uint8)MEM_E_UNINIT);
            }
            else
            {
                /* Do Nothing */
            }
            /* Do not change Mem_u1gJobResult */
        }
    }
    else
    {
        /* Do Nothing */
    }

    return((Std_ReturnType)u1aRet);
}

/****************************************************************************/
/* Function Name | Mem_DeInit                                               */
/* Description   | Reset the RAM used for code flash memory rewriting and   */
/*               | the flash controller.                                    */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | -                                                        */
/* Notes         | Synchronous processing                                   */
/****************************************************************************/
FUNC(void, MEM_CODE_FAR) Mem_DeInit(void)
{

    /* Initialize RAM */
    Mem_Sub_InitVariables();

    CodeFls_DeInit();

    return;
}

/****************************************************************************/
/* Function Name | Mem_Suspend                                              */
/* Description   | OTA_CodeFlash interrupts memory operations that          */
/*               | the driver is performing on the hardware.                */
/* Preconditions | -                                                        */
/* Parameters    | [IN]instanceId             : Instance ID                 */
/* Return Value  | E_OK                       : Successful completion       */
/*               | E_NOT_OK                   : Failed                      */
/* Notes         | Synchronous processing                                   */
/****************************************************************************/
FUNC(Std_ReturnType, MEM_CODE_FAR) Mem_Suspend
(
    VAR(Mem_InstanceIdType, AUTOMATIC) instanceId
)
{
    /* Variable Declarations */
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;

    if( Mem_u1gMirrorJobStatus == Mem_u1gJobStatus )
    {
        /* Job Status is MEM_BUSY */
        if( MEM_BUSY == Mem_u1gJobStatus )
        {
            /* Instance id check */
            u1aRet = Mem_Sub_InstanceIdCheck(instanceId);

            /* Instance id check result is E_OK */
            if( (Std_ReturnType)E_OK == u1aRet )
            {
                if( (Mem_stgMirrorArea.u1CheckCmd == Mem_stgMultiOpInfo.u1Cmd ) &&
                    (Mem_stgMirrorArea.u1CheckCtrlStartFlag == Mem_stgMultiOpInfo.u1CtrlStartFlag) )
                {
                    if( Mem_stgMultiOpInfo.u1CtrlStartFlag == MEM_U1_TRUE )
                    {
                        u1aRet = CodeFls_Suspend();
                        /* Suspend result is E_OK */
                        if( (Std_ReturnType)E_OK == u1aRet )
                        {
                            /* Set Job Status to MEM_SUSPEND */
                            Mem_Sub_SetJobStatus(MEM_SUSPEND);
                        }
                    }
                    else
                    {
                        if( MEM_REQ_SWITCHVALIDAREA == Mem_stgMultiOpInfo.u1Cmd )
                        {
                            u1aRet = E_NOT_OK;
                        }
                        else
                        {
                            /* Set Job Status to MEM_SUSPEND */
                            Mem_Sub_SetJobStatus(MEM_SUSPEND);
                        }
                    }
                }
                else
                {
                    u1aRet = E_NOT_OK;
                }
            }
            else
            {
                /* Set return value is E_NOT_OK */
                /* Do not change Mem_u1gJobResult */
                /* Do Nothing */
            }
        }
        else
        {
            /* Job Status is MEM_UNINIT */
            if( MEM_UNINIT == Mem_u1gJobStatus )
            {
                /* Error notification for development - Job status error - UNINIT */
                Mem_Sub_Det_ReportError((uint16)MEM_MODULE_ID, (uint8)instanceId, (uint8)MEM_API_ID_SUSPEND, (uint8)MEM_E_UNINIT);
            }
            else
            {
                /* Do Nothing */
            }
            /* Set return value is E_NOT_OK */
            /* Do not change Mem_u1gJobResult */
            u1aRet = E_NOT_OK;
        }
    }
    else
    {
        u1aRet = E_NOT_OK;
    }

    return((Std_ReturnType)u1aRet);
}

/****************************************************************************/
/* Function Name | Mem_Resume                                               */
/* Description   | Resume memory operations that the OTA_CodeFlash driver   */
/*               | interrupted to the hardware.                             */
/* Preconditions | -                                                        */
/* Parameters    | [IN]instanceId : Instance ID                             */
/* Return Value  | E_OK           : Successful completion                   */
/*               | E_NOT_OK       : Failed                                  */
/* Notes         | Synchronous processing                                   */
/****************************************************************************/
FUNC(Std_ReturnType, MEM_CODE_FAR) Mem_Resume
(
    VAR(Mem_InstanceIdType, AUTOMATIC) instanceId
)
{
    /* Variable Declarations */
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;

    if( Mem_u1gMirrorJobStatus == Mem_u1gJobStatus )
    {
        /* Job Status is MEM_SUSPEND */
        if( MEM_SUSPEND == Mem_u1gJobStatus )
        {
            /* Instance id check */
            u1aRet = Mem_Sub_InstanceIdCheck(instanceId);

            /* Instance id check result is E_OK */
            if( (Std_ReturnType)E_OK == u1aRet )
            {
                if( (Mem_stgMirrorArea.u1CheckCmd == Mem_stgMultiOpInfo.u1Cmd ) &&
                    (Mem_stgMirrorArea.u1CheckCtrlStartFlag == Mem_stgMultiOpInfo.u1CtrlStartFlag) )
                {
                    if( Mem_stgMultiOpInfo.u1CtrlStartFlag == MEM_U1_TRUE )
                    {
                        u1aRet = CodeFls_Resume();
                        /* Suspend result is E_OK */
                        if( (Std_ReturnType)E_OK == u1aRet )
                        {
                            /* Set Job Status to MEM_BUSY */
                            Mem_Sub_SetJobStatus(MEM_BUSY);
                        }
                    }
                    else
                    {
                        if( MEM_REQ_SWITCHVALIDAREA == Mem_stgMultiOpInfo.u1Cmd )
                        {
                            u1aRet = E_NOT_OK;
                        }
                        else
                        {
                            if( MEM_REQ_ERASE == Mem_stgMultiOpInfo.u1Cmd )
                            {
                                Mem_u1gJobDelayCount = MEM_DEVCFG_DATA.Mem_Ab_ControlSetting->Mem_Ab_Erase_Delay_Count;
                            }
                            else if( MEM_REQ_WRITE == Mem_stgMultiOpInfo.u1Cmd )
                            {
                                Mem_u1gJobDelayCount = MEM_DEVCFG_DATA.Mem_Ab_ControlSetting->Mem_Ab_Write_Delay_Count;
                            }
                            else
                            {
                                /* Do Nothing */
                            }

                            /* Set Job Status to MEM_BUSY */
                            Mem_Sub_SetJobStatus(MEM_BUSY);
                        }
                    }
                }
                else
                {
                    u1aRet = E_NOT_OK;
                }
            }
            else
            {
                /* Set return value is E_NOT_OK */
                /* Do not change Mem_u1gJobResult */
                /* Do Nothing */
            }
        }
        else
        {
            /* Job Status is MEM_UNINIT */
            if( MEM_UNINIT == Mem_u1gJobStatus )
            {
                /* Error notification for development - Job status error - UNINIT */
                Mem_Sub_Det_ReportError((uint16)MEM_MODULE_ID, (uint8)instanceId, (uint8)MEM_API_ID_RESUME, (uint8)MEM_E_UNINIT);
            }
            else
            {
                /* Do Nothing */
            }
            /* Set return value is E_NOT_OK */
            /* Do not change Mem_u1gJobResult */
            u1aRet = E_NOT_OK;
        }
    }
    else
    {
        u1aRet = E_NOT_OK;
    }

    return((Std_ReturnType)u1aRet);
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define MEM_STOP_SEC_CODE_FAR
#include <Mem_MemMap.h>


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1.00          :2025/03/24                                              */
/*  v1.01          :2025/04/14                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
