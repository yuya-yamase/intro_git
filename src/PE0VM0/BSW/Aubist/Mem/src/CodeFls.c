/* CodeFls_c                                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | RH850/U2Ax/CodeFls/CODE                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../inc/CodeFls.h"
#include "../inc/CodeFls_Internal.h"
#include "../inc/CodeFls_Sub.h"
#include "../inc/CodeFls_Drv.h"
#include "../inc/CodeFls_Device.h"
#include "../inc/CodeFls_Reg.h"
#include "../usr/CodeFls_Usr.h"


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

VAR(uint8, MEM_VAR_NO_INIT) CodeFls_u1gJobStatus;                                       /* Job Status                               */
VAR(uint8, MEM_VAR_NO_INIT) CodeFls_u1gMirrorJobStatus;                                 /* Job Status Mirror Area                   */
VAR(uint8, MEM_VAR_NO_INIT) CodeFls_u1gJobResult;                                       /* Job Processing Results                   */
VAR(uint8, MEM_VAR_NO_INIT) CodeFls_u1gMirrorJobResult;                                 /* Job Processing Results Mirror Area       */
VAR(uint32, MEM_VAR_NO_INIT) CodeFls_u4gJobTimer;                                       /* Job Management Timer                     */
VAR(CodeFls_MultiOpType, MEM_VAR_NO_INIT) CodeFls_stgMultiOpInfo;                       /* Operational Information                  */
VAR(CodeFls_OpMirrorType, MEM_VAR_NO_INIT) CodeFls_stgMirrorArea;                       /* Operation Information Mirror Area        */
VAR(uint16, MEM_VAR_NO_INIT) CodeFls_u2gCpuFreq;                                        /* CPU operating frequency                  */
VAR(uint32, MEM_VAR_NO_INIT) CodeFls_u4gWriteBuffer[CODEFLS_U1_TRANSFERSIZE_HWAREA];    /* Write Buffer                             */

#define MEM_STOP_SEC_VAR_NO_INIT_32
#include <Mem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define MEM_START_SEC_CONST_32
#include <Mem_MemMap.h>

#define MEM_STOP_SEC_CONST_32
#include <Mem_MemMap.h>


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define MEM_START_SEC_CODE
#include <Mem_MemMap.h>

/****************************************************************************/
/* Function Name | CodeFls_Init                                             */
/* Description   | In preparation for rewriting the code flash memory, the  */
/*               | necessary initialization processing is performed for the */
/*               | RAM used by the CodeFlash driver and the flash           */
/*               | controller.                                              */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | -                                                        */
/* Notes         | Synchronous processing                                   */
/****************************************************************************/
FUNC(void, MEM_CODE) CodeFls_Init(void)
{
    VAR(Std_ReturnType, AUTOMATIC) u1aResult;
    VAR(uint8, AUTOMATIC) u1aFaciMax;
    VAR(uint8, AUTOMATIC) u1aFaciNum;
    VAR(Std_ReturnType, AUTOMATIC)  u1aUsrResult;

    u1aResult = E_NOT_OK;

    /* Initialize RAM */
    CodeFls_Sub_InitVariables();

    /* Get Maximum Number of FACI */
    u1aFaciMax = CodeFls_Sub_GetFaciMax();

    /* LTSC timer start */
    CodeFls_Drv_StartTimer();

    /* Get CPU operating frequency */
    CodeFls_Drv_GetClockValue();

    /* Number of FACIs */
    for( u1aFaciNum = CODEFLS_U1_FACI_0; u1aFaciNum < u1aFaciMax; u1aFaciNum++ )
    {
        /* Initializing the Flash Sequencer Initialization Registers */
        CodeFls_Drv_ResetInitr(u1aFaciNum);

        /* Issue a forced-stop-command */
        u1aResult = CodeFls_Sub_Reset(u1aFaciNum);
        if( (Std_ReturnType)E_OK != u1aResult )
        {
            /* If successful completion is not possible, processing is interrupted */
            break;
        }
        else
        {
            /* No process */
        }
    }

    if( (Std_ReturnType)E_OK == u1aResult )
    {
        /* Initializing Flash-Related Registers */
        CodeFls_Drv_InitRegister(CODEFLS_U1_REQ_INIT, u1aFaciMax);

        u1aUsrResult = CodeFls_Drv_Usr_VerifyID();
        if( CODEFLS_E_NORESULT == u1aUsrResult )
        {
            u1aResult = CodeFls_Drv_VerifyID();
        }
        else
        {
            u1aResult = u1aUsrResult;
        }
    }

    /* Initial setup is E_OK */
    if( (Std_ReturnType)E_OK == u1aResult )
    {
        CodeFls_u1gJobStatus = CODEFLS_IDLE;
        CodeFls_u1gMirrorJobStatus = CodeFls_u1gJobStatus;
        CodeFls_u1gJobResult = CODEFLS_JOB_OK;
        CodeFls_u1gMirrorJobResult = CodeFls_u1gJobResult;
    }
    else
    {
        CodeFls_u1gJobResult = CODEFLS_JOB_FAILED;
        CodeFls_u1gMirrorJobResult = CodeFls_u1gJobResult;
    }
}

/****************************************************************************/
/* Function Name | CodeFls_StartCtrl                                        */
/* Description   | Allow erase/write/blank check/flash memory switching to  */
/*               | the area indicated.                                      */
/* Preconditions | -                                                        */
/* Parameters    | [IN]ReqKind             : Request control type           */
/*               | [IN]Addr                : Control Address                */
/*               | [IN]Size                : Size - byte                    */
/* Return Value  | E_OK                    : Successful completion          */
/*               | E_NOT_OK                : Failed                         */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, MEM_CODE) CodeFls_StartCtrl
(
    VAR(uint8, AUTOMATIC) ReqKind,
    VAR(uint32, AUTOMATIC) Addr,
    VAR(uint32, AUTOMATIC) Size
)
{
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;
    VAR(uint8, AUTOMATIC) u1aFaciNum;

    u1aRet = E_NOT_OK;

    if( CodeFls_u1gMirrorJobStatus == CodeFls_u1gJobStatus )
    {
        if( CODEFLS_IDLE == CodeFls_u1gJobStatus )
        {
            u1aRet = CodeFls_Sub_CheckParamCtrl(ReqKind, Addr, Size);
            if( (Std_ReturnType)E_OK == u1aRet )
            {
                if( CODEFLS_REQ_BLANKCHECK != ReqKind )
                {
                    if( CODEFLS_REQ_SWITCHVALIDAREA == ReqKind )
                    {
                        u1aFaciNum = CODEFLS_U1_FACI_0;
                    }
                    else
                    {
                        /* Get FACI number from address and size */
                        u1aFaciNum = CodeFls_Sub_GetFaciNum(Addr, Size);
                    }

                    /* Resetting Flash-Related Registers */
                    CodeFls_Drv_ResetRegister(u1aFaciNum);

                    if( CODEFLS_REQ_SWITCHVALIDAREA == ReqKind )
                    {
                        /* Change Data Flash P/E mode */
                        u1aRet = CodeFls_Drv_SwitchModeStart(u1aFaciNum, CODEFLS_U2_MODE_DPE);
                    }
                    else
                    {
                        /* Change Code Flash P/E mode */
                        u1aRet = CodeFls_Drv_SwitchModeStart(u1aFaciNum, CODEFLS_U2_MODE_CPE);
                    }

                    if( (Std_ReturnType)E_OK != u1aRet )
                    {
                        /* Do not check the results because it is a recovery process after an error occurs. */
                        (void)CodeFls_Drv_SwitchModeStart(u1aFaciNum, CODEFLS_U2_MODE_USER);
                    }
                    else
                    {
                        /* No process */
                    }
                }
            }
            else
            {
                /* No process */
            }
        }
        else
        {
            /* No process */
        }
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_EndCtrl                                          */
/* Description   | Prohibit erase/write/blank checking.                     */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, MEM_CODE) CodeFls_EndCtrl(void)
{
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;
    VAR(uint8, AUTOMATIC) u1aFaciMax;
    VAR(uint8, AUTOMATIC) u1aFaciNum;

    u1aRet = E_NOT_OK;

    if( CODEFLS_IDLE == CodeFls_u1gJobStatus )
    {
        /* Get maximum number of FACI */
        u1aFaciMax = CodeFls_Sub_GetFaciMax();

        for( u1aFaciNum = CODEFLS_U1_FACI_0; u1aFaciNum < u1aFaciMax; u1aFaciNum++ )
        {
            /* Transition to Read Mode */
            u1aRet = CodeFls_Drv_SwitchModeStart(u1aFaciNum, CODEFLS_U2_MODE_USER);
            if( (Std_ReturnType)E_OK != u1aRet )
            {
                break;
            }
            else
            {
                /* No process */
            }
        }

        if( (Std_ReturnType)E_OK == u1aRet )
        {
            CodeFls_Sub_InitOpInfo();
        }
        else
        {
            /* No process */
        }
    }

    if( (Std_ReturnType)E_OK != u1aRet )
    {
        CodeFls_u1gJobResult = CODEFLS_JOB_FAILED;
        CodeFls_u1gMirrorJobResult = CodeFls_u1gJobResult;
    }
    else
    {
        /* No process */
    }
}

/****************************************************************************/
/* Function Name | CodeFls_Erase                                            */
/* Description   | Perform the erase operation on the block indicated by    */
/*               | the erase start address and erase size specified in the  */
/*               | argument.                                                */
/* Preconditions | -                                                        */
/* Parameters    | [IN]EraseAddr           : Erase Start Address            */
/*               | [IN]EraseSize           : Erased data length             */
/* Return Value  | E_OK                    : Successful completion          */
/*               | E_NOT_OK                : Failed                         */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, MEM_CODE) CodeFls_Erase
(
    VAR(uint32, AUTOMATIC) EraseAddr,
    VAR(uint32, AUTOMATIC) EraseSize
)
{
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;
    VAR(uint8, AUTOMATIC) u1aInfoNum;

    if( CodeFls_u1gMirrorJobStatus == CodeFls_u1gJobStatus )
    {
        if( CODEFLS_IDLE == CodeFls_u1gJobStatus )
        {
            u1aInfoNum = CODEFLS_U1_INFONUM_0;
            u1aRet = CodeFls_Sub_CheckParamErase(EraseAddr, EraseSize, &u1aInfoNum);
            if( (Std_ReturnType)E_OK == u1aRet )
            {
                CodeFls_stgMultiOpInfo.u1Cmd       = CODEFLS_REQ_ERASE;
                CodeFls_stgMultiOpInfo.u4OpAddr    = EraseAddr;
                CodeFls_stgMultiOpInfo.pu1BufAddr  = CODEFLS_PU1_OPINFO_BUFFER_NULL;
                CodeFls_stgMultiOpInfo.u4OpSize    = EraseSize;
                CodeFls_stgMultiOpInfo.u4BankAddr  = CODEFLS_DEVCFG_DATA.CodeFlsSetting->CodeFlsInfo[u1aInfoNum].Addr;
                CodeFls_stgMultiOpInfo.u1FaciNum   = CodeFls_Sub_GetFaciNum(EraseAddr, EraseSize);
                CodeFls_stgMultiOpInfo.u1SVAStatus = CODEFLS_U1_SVA_NONE;

                CodeFls_stgMirrorArea.u1CheckCmd = CodeFls_stgMultiOpInfo.u1Cmd;
                CodeFls_stgMirrorArea.u4CheckAddr = CodeFls_stgMultiOpInfo.u4OpAddr;
                CodeFls_stgMirrorArea.pu1CheckBuf = CodeFls_stgMultiOpInfo.pu1BufAddr;
                CodeFls_stgMirrorArea.u4CheckSize = CodeFls_stgMultiOpInfo.u4OpSize;
                CodeFls_stgMirrorArea.u4CheckBank = CodeFls_stgMultiOpInfo.u4BankAddr;
                CodeFls_stgMirrorArea.u1CheckFaci = CodeFls_stgMultiOpInfo.u1FaciNum;
                CodeFls_stgMirrorArea.u1CheckSVA  = CodeFls_stgMultiOpInfo.u1SVAStatus;

                CodeFls_Drv_EraseOp(CodeFls_stgMultiOpInfo.u1FaciNum);

                /* Set job management timer */
                CodeFls_Drv_GetCounterValue(&CodeFls_u4gJobTimer);

                CodeFls_u1gJobStatus = CODEFLS_BUSY;
                CodeFls_u1gMirrorJobStatus = CodeFls_u1gJobStatus;
                CodeFls_u1gJobResult = CODEFLS_JOB_PENDING;
                CodeFls_u1gMirrorJobResult = CodeFls_u1gJobResult;
            }
            else
            {
                /* Parameter Error */
                CodeFls_u1gJobResult = CODEFLS_JOB_FAILED;
                CodeFls_u1gMirrorJobResult = CodeFls_u1gJobResult;
            }
        }
        /* UNINIT,BUSY is Failed */
        else
        {
            CodeFls_u1gJobStatus = CODEFLS_UNINIT;
            CodeFls_u1gMirrorJobStatus = CodeFls_u1gJobStatus;
            CodeFls_u1gJobResult = CODEFLS_JOB_FAILED;
            CodeFls_u1gMirrorJobResult = CodeFls_u1gJobResult;
        }
    }
    else
    {
        CodeFls_u1gJobStatus = CODEFLS_IDLE;
        CodeFls_u1gMirrorJobStatus = CodeFls_u1gJobStatus;
        CodeFls_u1gJobResult = CODEFLS_JOB_FAILED;
        CodeFls_u1gMirrorJobResult = CodeFls_u1gJobResult;
    }
}

/****************************************************************************/
/* Function Name | CodeFls_Write                                            */
/* Description   | Execute a write of the write data size from the          */
/*               | write-start address specified in the argument.           */
/* Preconditions | -                                                        */
/* Parameters    | [IN]TargetAddr          : Write start address            */
/*               | [IN]SourceAddr          : Write data storage space       */
/*               | [IN]DataSize            : Write data length(unit:byte)   */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, MEM_CODE) CodeFls_Write
(
    VAR(uint32, AUTOMATIC) TargetAddr,
    P2CONST(uint8, AUTOMATIC, MEM_APPL_DATA) SourceAddr,
    VAR(uint32, AUTOMATIC) DataSize
)
{
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;

    if( CodeFls_u1gMirrorJobStatus == CodeFls_u1gJobStatus )
    {
        if( CODEFLS_IDLE == CodeFls_u1gJobStatus )
        {
            u1aRet = CodeFls_Sub_CheckParamWrite(TargetAddr, DataSize);
            if( (Std_ReturnType)E_OK == u1aRet )
            {
                CodeFls_stgMultiOpInfo.u1Cmd       = CODEFLS_REQ_WRITE;
                CodeFls_stgMultiOpInfo.u4OpAddr    = TargetAddr;
                CodeFls_stgMultiOpInfo.pu1BufAddr  = SourceAddr;
                CodeFls_stgMultiOpInfo.u4OpSize    = DataSize;
                CodeFls_stgMultiOpInfo.u4BankAddr  = CODEFLS_U4_OPINFO_ADDR_NONE;
                CodeFls_stgMultiOpInfo.u1FaciNum   = CodeFls_Sub_GetFaciNum(TargetAddr, DataSize);
                CodeFls_stgMultiOpInfo.u1SVAStatus = CODEFLS_U1_SVA_NONE;

                CodeFls_stgMirrorArea.u1CheckCmd = CodeFls_stgMultiOpInfo.u1Cmd;
                CodeFls_stgMirrorArea.u4CheckAddr = CodeFls_stgMultiOpInfo.u4OpAddr;
                CodeFls_stgMirrorArea.pu1CheckBuf = CodeFls_stgMultiOpInfo.pu1BufAddr;
                CodeFls_stgMirrorArea.u4CheckSize = CodeFls_stgMultiOpInfo.u4OpSize;
                CodeFls_stgMirrorArea.u4CheckBank = CodeFls_stgMultiOpInfo.u4BankAddr;
                CodeFls_stgMirrorArea.u1CheckFaci = CodeFls_stgMultiOpInfo.u1FaciNum;
                CodeFls_stgMirrorArea.u1CheckSVA  = CodeFls_stgMultiOpInfo.u1SVAStatus;

                CodeFls_Drv_WriteOp(CodeFls_stgMultiOpInfo.u1FaciNum);

                /* Set job management timer */
                CodeFls_Drv_GetCounterValue(&CodeFls_u4gJobTimer);

                CodeFls_u1gJobStatus = CODEFLS_BUSY;
                CodeFls_u1gMirrorJobStatus = CodeFls_u1gJobStatus;
                CodeFls_u1gJobResult = CODEFLS_JOB_PENDING;
                CodeFls_u1gMirrorJobResult = CodeFls_u1gJobResult;

            }
            else
            {
                /* Parameter Error */
                CodeFls_u1gJobResult = CODEFLS_JOB_FAILED;
                CodeFls_u1gMirrorJobResult = CodeFls_u1gJobResult;
            }
        }
        /* UNINIT,BUSY is Failed */
        else
        {
            CodeFls_u1gJobStatus = CODEFLS_UNINIT;
            CodeFls_u1gMirrorJobStatus = CodeFls_u1gJobStatus;
            CodeFls_u1gJobResult = CODEFLS_JOB_FAILED;
            CodeFls_u1gMirrorJobResult = CodeFls_u1gJobResult;
        }
    }
    else
    {
        CodeFls_u1gJobStatus = CODEFLS_IDLE;
        CodeFls_u1gMirrorJobStatus = CodeFls_u1gJobStatus;
        CodeFls_u1gJobResult = CODEFLS_JOB_FAILED;
        CodeFls_u1gMirrorJobResult = CodeFls_u1gJobResult;
    }
}

/****************************************************************************/
/* Function Name | CodeFls_GetJobStatus                                     */
/* Description   | Verify the state during code flash memory control        */
/*               | and return appropriate return values based on the state  */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | CODEFLS_UNINIT             : Initial Setup Uncompleted   */
/*               | CODEFLS_IDLE               : Idle State                  */
/*               | CODEFLS_BUSY               : Busy State                  */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(uint8, MEM_CODE) CodeFls_GetJobStatus(void)
{
    return(CodeFls_u1gJobStatus);
}

/****************************************************************************/
/* Function Name | CodeFls_GetJobResult                                     */
/* Description   | Verify the job result for code flash memory and return   */
/*               | appropriate return values based on the result            */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | CODEFLS_JOB_OK             : Success                     */
/*               | CODEFLS_JOB_FAILED         : Failure                     */
/*               | CODEFLS_JOB_PENDING        : Unconfirmed                 */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(uint8, MEM_CODE) CodeFls_GetJobResult(void)
{
    if( CodeFls_u1gMirrorJobResult == CodeFls_u1gJobResult )
    {
        /* Do Nothing */
    }
    else
    {
        CodeFls_u1gJobResult = CODEFLS_JOB_FAILED;
        CodeFls_u1gMirrorJobResult = CodeFls_u1gJobResult;
    }

    return(CodeFls_u1gJobResult);
}

/****************************************************************************/
/* Function Name | CodeFls_GetBlockInfo                                     */
/* Description   | Retrieve block information for the address specified by  */
/*               | the 'Addr' argument                                      */
/* Preconditions | -                                                        */
/* Parameters    | [IN]Addr             : Code flash memory address         */
/*               | [OUT]BlockInfo       : Block information storage address */
/* Return Value  | E_OK                 : Normal completion                 */
/*               | E_NOT_OK             : Abnormal termination              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, MEM_CODE) CodeFls_GetBlockInfo
(
    VAR(uint32, AUTOMATIC) Addr,
    P2VAR(CodeFls_BlockInfoType, AUTOMATIC, MEM_APPL_DATA) BlockInfo
)
{
    VAR(Std_ReturnType, AUTOMATIC) staRet;
    VAR(uint32, AUTOMATIC) u4aFirstAddr;
    VAR(uint32, AUTOMATIC) u4aSize;
    VAR(uint8, AUTOMATIC) u1aLoopCnt;

    staRet = E_NOT_OK;
    u4aFirstAddr = CODEFLS_U4_BLKINFO_ADDR_NONE;
    u4aSize = CODEFLS_U4_BLKINFO_SIZE_NONE;

    for( u1aLoopCnt = CODEFLS_U1_VAL_0; u1aLoopCnt < CODEFLS_DEVCFG_DATA.CodeFlsSetting->CodeFlsInfoNum; u1aLoopCnt++ )
    {
        if( (CODEFLS_DEVCFG_DATA.CodeFlsSetting->CodeFlsInfo[u1aLoopCnt].Addr <= Addr) &&
            ((CODEFLS_DEVCFG_DATA.CodeFlsSetting->CodeFlsInfo[u1aLoopCnt].Addr + CODEFLS_DEVCFG_DATA.CodeFlsSetting->CodeFlsInfo[u1aLoopCnt].Size) > Addr) )
        {
            if( (CODEFLS_DEVCFG_DATA.CodeFlsSetting->CodeFlsInfo[u1aLoopCnt].Addr + CODEFLS_U4_CF1_ADDR_64K_START) > Addr )
            {
                /* 64K block */
                u4aFirstAddr = (Addr & CODEFLS_U4_SMALL_BLOCK_ADDR_MASK);
                u4aSize      = CODEFLS_U4_SMALL_BLOCK_SIZE;
            }
            else
            {
                /* 16K block */
                u4aFirstAddr = (Addr & CODEFLS_U4_BLOCK_ADDR_MASK);
                u4aSize      = CODEFLS_U4_BLOCK_SIZE;
            }

            staRet = E_OK;
            break;
        }
        else
        {
            /* No process */
        }
    }

    if( (Std_ReturnType)E_OK == staRet )
    {
        BlockInfo->Addr = u4aFirstAddr;
        BlockInfo->Size = u4aSize;
    }
    else
    {
        /* No process */
    }

    return(staRet);
}

/****************************************************************************/
/* Function Name | CodeFls_DeInit                                           */
/* Description   | Reset the RAM used for code flash memory rewriting and   */
/*               | the flash controller.                                    */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, MEM_CODE) CodeFls_DeInit(void)
{
    VAR(Std_ReturnType, AUTOMATIC) u1aResult;
    VAR(uint8, AUTOMATIC) u1aFaciMax;
    VAR(uint8, AUTOMATIC) u1aFaciNum;

    u1aResult = E_NOT_OK;

    /* Initialize RAM */
    CodeFls_Sub_InitVariables();

    /* Get Maximum Number of FACI */
    u1aFaciMax = CodeFls_Sub_GetFaciMax();

    /* Number of FACIs */
    for( u1aFaciNum = CODEFLS_U1_FACI_0; u1aFaciNum < u1aFaciMax; u1aFaciNum++ )
    {
        /* Issue a forced-stop-command */
        u1aResult = CodeFls_Sub_Reset(u1aFaciNum);
        if( (Std_ReturnType)E_OK != u1aResult )
        {
            /* Interrupted on failure */
            break;
        }
        else
        {
            /* No process */
        }
    }

    if( (Std_ReturnType)E_OK == u1aResult )
    {
        /* Initializing Flash-Related Registers */
        CodeFls_Drv_InitRegister(CODEFLS_U1_REQ_DEINIT, u1aFaciMax);
    }

}

/****************************************************************************/
/* Function Name | CodeFls_MainFunction                                     */
/* Description   | Check the progress of code flush control jobs and update */
/*               | job status and job results.                              */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, MEM_CODE) CodeFls_MainFunction(void)
{
    VAR(Std_ReturnType, AUTOMATIC) u1aResult;
    VAR(uint8, AUTOMATIC) u1aFaciMax;
    VAR(uint8, AUTOMATIC) u1aFaciNum;
    VAR(uint8, AUTOMATIC) u1aFrdy;
    VAR(uint8, AUTOMATIC) u1aIsFinish;

    if( CodeFls_u1gMirrorJobStatus == CodeFls_u1gJobStatus )
    {
        if( CODEFLS_BUSY == CodeFls_u1gJobStatus )
        {
            u1aResult = CodeFls_Sub_CheckMirrorOpInfo();
            if( (Std_ReturnType)E_OK == u1aResult )
            {
                u1aFaciMax = CodeFls_Sub_GetFaciMax();

                if( CodeFls_stgMultiOpInfo.u1FaciNum < u1aFaciMax )
                {
                    u1aFaciNum = CodeFls_stgMultiOpInfo.u1FaciNum;

                    u1aFrdy = CodeFls_Drv_CheckReady(u1aFaciNum);
                    if( CODEFLS_U1_TRUE == u1aFrdy )
                    {
                        u1aResult = CodeFls_Drv_CheckError(u1aFaciNum);
                        if( (Std_ReturnType)E_OK == u1aResult )
                        {
                            u1aIsFinish = CODEFLS_U1_FALSE;
                            u1aResult = CodeFls_Sub_MultiOperation(u1aFaciNum, &u1aIsFinish);
                            if( (Std_ReturnType)E_OK == u1aResult )
                            {
                                if( CODEFLS_U1_TRUE == u1aIsFinish )
                                {
                                    /* All jobs completed successfully */
                                    CodeFls_u1gJobStatus = CODEFLS_IDLE;
                                    CodeFls_u1gMirrorJobStatus = CodeFls_u1gJobStatus;
                                    CodeFls_u1gJobResult = CODEFLS_JOB_OK;
                                    CodeFls_u1gMirrorJobResult = CodeFls_u1gJobResult;
                                }
                                else
                                {
                                    /* No process */
                                }
                            }
                            else if( (Std_ReturnType)CODEFLS_U1_BLANKCHECK_NOT_BLANK == u1aResult )
                            {
                                CodeFls_u1gJobStatus = CODEFLS_IDLE;
                                CodeFls_u1gMirrorJobStatus = CodeFls_u1gJobStatus;
                                CodeFls_u1gJobResult = CODEFLS_INCONSISTENT;
                                CodeFls_u1gMirrorJobResult = CodeFls_u1gJobResult;
                            }
                            else
                            {
                                CodeFls_u1gJobStatus = CODEFLS_IDLE;
                                CodeFls_u1gMirrorJobStatus = CodeFls_u1gJobStatus;
                                CodeFls_u1gJobResult = CODEFLS_JOB_FAILED;
                                CodeFls_u1gMirrorJobResult = CodeFls_u1gJobResult;
                            }
                        }
                        else
                        {
                            CodeFls_u1gJobStatus = CODEFLS_IDLE;
                            CodeFls_u1gMirrorJobStatus = CodeFls_u1gJobStatus;
                            CodeFls_u1gJobResult = CODEFLS_JOB_FAILED;
                            CodeFls_u1gMirrorJobResult = CodeFls_u1gJobResult;
                        }
                    }
                    else
                    {
                        /* Flash Sequencer Busy, timeout check */
                        u1aResult = CodeFls_Sub_CheckTimeOut();
                        if( (Std_ReturnType)E_OK != u1aResult )
                        {
                            /* Stop the sequencer with a kill command */
                            /* Do not check the results because it is a recovery process after an error occurs. */
                            (void)CodeFls_Drv_ForcedStop(u1aFaciNum);
                            (void)CodeFls_Drv_SwitchModeStart(u1aFaciNum, CODEFLS_U2_MODE_USER);
                            CodeFls_u1gJobStatus = CODEFLS_IDLE;
                            CodeFls_u1gMirrorJobStatus = CodeFls_u1gJobStatus;
                            CodeFls_u1gJobResult = CODEFLS_JOB_FAILED;
                            CodeFls_u1gMirrorJobResult = CodeFls_u1gJobResult;
                        }
                        else
                        {
                            /* No process */
                        }
                    }
                }
                else
                {
                    CodeFls_u1gJobStatus = CODEFLS_IDLE;
                    CodeFls_u1gMirrorJobStatus = CodeFls_u1gJobStatus;
                    CodeFls_u1gJobResult = CODEFLS_JOB_FAILED;
                    CodeFls_u1gMirrorJobResult = CodeFls_u1gJobResult;
                }
            }
            else
            {
                CodeFls_u1gJobStatus = CODEFLS_IDLE;
                CodeFls_u1gMirrorJobStatus = CodeFls_u1gJobStatus;
                CodeFls_u1gJobResult = CODEFLS_JOB_FAILED;
                CodeFls_u1gMirrorJobResult = CodeFls_u1gJobResult;
            }
        }
        else if( CODEFLS_UNINIT == CodeFls_u1gJobStatus )
        {
            CodeFls_u1gJobResult = CODEFLS_JOB_FAILED;
            CodeFls_u1gMirrorJobResult = CodeFls_u1gJobResult;
        }
        else
        {
            /* No process */
        }
    }
    else
    {
        CodeFls_u1gJobStatus = CODEFLS_IDLE;
        CodeFls_u1gMirrorJobStatus = CodeFls_u1gJobStatus;
        CodeFls_u1gJobResult = CODEFLS_JOB_FAILED;
        CodeFls_u1gMirrorJobResult = CodeFls_u1gJobResult;
    }
}

#if 0   /* Nbr1503 */
/****************************************************************************/
/* Function Name | CodeFls_WritableCheck                                    */
/* Description   | This request checks whether writing data is possible     */
/*               | starting from the specified code flash memory address    */
/*               | and for the given data size. Specifically                */
/* Preconditions | -                                                        */
/* Parameters    | [IN]TargetAddr             : Write start address         */
/*               | [IN]SourceAddr             : Write data storage address  */
/*               | [IN]DataSize               : Write data size (in bytes)  */
/* Return Value  | -                                                        */
/* Notes         |                                                          */
/****************************************************************************/
FUNC(void, MEM_CODE) CodeFls_WritableCheck
(
    VAR(uint32, AUTOMATIC) TargetAddr,
    P2CONST(uint8, AUTOMATIC, MEM_APPL_DATA) SourceAddr,
    VAR(uint32, AUTOMATIC) DataSize
)
{
    if( CodeFls_u1gMirrorJobStatus == CodeFls_u1gJobStatus )
    {
        if( CODEFLS_IDLE == CodeFls_u1gJobStatus )
        {
            CodeFls_u1gJobResult = CODEFLS_JOB_FAILED;
            CodeFls_u1gMirrorJobResult = CodeFls_u1gJobResult;
        }
        /* UNINIT,BUSY is Failed */
        else
        {
            CodeFls_u1gJobStatus = CODEFLS_UNINIT;
            CodeFls_u1gMirrorJobStatus = CodeFls_u1gJobStatus;
            CodeFls_u1gJobResult = CODEFLS_JOB_FAILED;
            CodeFls_u1gMirrorJobResult = CodeFls_u1gJobResult;
        }
    }
    else
    {
        CodeFls_u1gJobStatus = CODEFLS_IDLE;
        CodeFls_u1gMirrorJobStatus = CodeFls_u1gJobStatus;
        CodeFls_u1gJobResult = CODEFLS_JOB_FAILED;
        CodeFls_u1gMirrorJobResult = CodeFls_u1gJobResult;
    }
}
#endif

/****************************************************************************/
/* Function Name | CodeFls_SwitchValidArea                                  */
/* Description   | Execute Flash Memory Active Surface Switching Procedure  */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | -                                                        */
/* Notes         |                                                          */
/****************************************************************************/
FUNC(void, MEM_CODE) CodeFls_SwitchValidArea(void)
{
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;

    if( CodeFls_u1gMirrorJobStatus == CodeFls_u1gJobStatus )
    {
        if( CODEFLS_IDLE == CodeFls_u1gJobStatus )
        {
            /* Flash Memory valid area switchable check */
            u1aRet = CodeFls_Sub_CheckSwitchValidArea();
            if( (Std_ReturnType)E_OK == u1aRet )
            {
                CodeFls_stgMultiOpInfo.u1Cmd       = CODEFLS_REQ_SWITCHVALIDAREA;
                CodeFls_stgMultiOpInfo.u4OpAddr    = CODEFLS_U4_OPINFO_ADDR_NONE;
                CodeFls_stgMultiOpInfo.pu1BufAddr  = CODEFLS_PU1_OPINFO_BUFFER_NULL;
                CodeFls_stgMultiOpInfo.u4OpSize    = CODEFLS_U4_OPINFO_SIZE_NONE;
                CodeFls_stgMultiOpInfo.u4BankAddr  = CODEFLS_U4_OPINFO_ADDR_NONE;
                CodeFls_stgMultiOpInfo.u1FaciNum   = CODEFLS_U1_FACI_0;
                CodeFls_stgMultiOpInfo.u1SVAStatus = CODEFLS_U1_SVA_PROPERTY_ERASE;

                CodeFls_stgMirrorArea.u1CheckCmd = CodeFls_stgMultiOpInfo.u1Cmd;
                CodeFls_stgMirrorArea.u4CheckAddr = CodeFls_stgMultiOpInfo.u4OpAddr;
                CodeFls_stgMirrorArea.pu1CheckBuf = CodeFls_stgMultiOpInfo.pu1BufAddr;
                CodeFls_stgMirrorArea.u4CheckSize = CodeFls_stgMultiOpInfo.u4OpSize;
                CodeFls_stgMirrorArea.u4CheckBank = CodeFls_stgMultiOpInfo.u4BankAddr;
                CodeFls_stgMirrorArea.u1CheckFaci = CodeFls_stgMultiOpInfo.u1FaciNum;
                CodeFls_stgMirrorArea.u1CheckSVA  = CodeFls_stgMultiOpInfo.u1SVAStatus;

                /* Configration Setting Area(back side) Erase */
                CodeFls_Drv_CsaEraseOp();

                /* Set job management timer */
                CodeFls_Drv_GetCounterValue(&CodeFls_u4gJobTimer);

                CodeFls_u1gJobStatus = CODEFLS_BUSY;
                CodeFls_u1gMirrorJobStatus = CodeFls_u1gJobStatus;
                CodeFls_u1gJobResult = CODEFLS_JOB_PENDING;
                CodeFls_u1gMirrorJobResult = CodeFls_u1gJobResult;
            }
            else
            {
                /* Parameter Error */
                CodeFls_u1gJobResult = CODEFLS_JOB_FAILED;
                CodeFls_u1gMirrorJobResult = CodeFls_u1gJobResult;
            }
        }
        /* UNINIT,BUSY is Failed */
        else
        {
            CodeFls_u1gJobStatus = CODEFLS_UNINIT;
            CodeFls_u1gMirrorJobStatus = CodeFls_u1gJobStatus;
            CodeFls_u1gJobResult = CODEFLS_JOB_FAILED;
            CodeFls_u1gMirrorJobResult = CodeFls_u1gJobResult;
        }
    }
    else
    {
        CodeFls_u1gJobStatus = CODEFLS_IDLE;
        CodeFls_u1gMirrorJobStatus = CodeFls_u1gJobStatus;
        CodeFls_u1gJobResult = CODEFLS_JOB_FAILED;
        CodeFls_u1gMirrorJobResult = CodeFls_u1gJobResult;
    }
}

/****************************************************************************/
/* Function Name | CodeFls_CheckSwitchValidArea                             */
/* Description   | Verifies that Flash Memory valid area can be switched.   */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | E_OK                 :switchable                         */
/*               | E_NOT_OK             :non-switchable                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, MEM_CODE) CodeFls_CheckSwitchValidArea(void)
{
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;

    u1aRet = CodeFls_Sub_CheckSwitchValidArea();

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_BlankCheck                                       */
/* Description   | Checks whether the start address and data size           */
/*               | specified in the arguments can be written.               */
/* Preconditions | -                                                        */
/* Parameters    | [IN]targetAddress       : Blank check start address      */
/*               | [IN]length              : Blank check data length        */
/* Return Value  |  -                                                       */
/* Notes         | Asynchronous processing                                  */
/****************************************************************************/
FUNC(void, MEM_CODE) CodeFls_BlankCheck
(
    VAR(uint32, AUTOMATIC) targetAddress,
    VAR(uint32, AUTOMATIC) length
)
{
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;

    if( CodeFls_u1gMirrorJobStatus == CodeFls_u1gJobStatus )
    {
        if( CODEFLS_IDLE == CodeFls_u1gJobStatus )
        {
            u1aRet = CodeFls_Sub_CheckParamBlankCheck(targetAddress, length);
            if( (Std_ReturnType)E_OK == u1aRet )
            {
                CodeFls_stgMultiOpInfo.u1Cmd       = CODEFLS_REQ_BLANKCHECK;
                CodeFls_stgMultiOpInfo.u4OpAddr    = targetAddress;
                CodeFls_stgMultiOpInfo.pu1BufAddr  = CODEFLS_PU1_OPINFO_BUFFER_NULL;
                CodeFls_stgMultiOpInfo.u4OpSize    = length;
                CodeFls_stgMultiOpInfo.u4BankAddr  = CODEFLS_U4_OPINFO_ADDR_NONE;
                CodeFls_stgMultiOpInfo.u1FaciNum   = CODEFLS_U1_FACI_0;
                CodeFls_stgMultiOpInfo.u1SVAStatus = CODEFLS_U1_SVA_NONE;

                CodeFls_stgMirrorArea.u1CheckCmd = CodeFls_stgMultiOpInfo.u1Cmd;
                CodeFls_stgMirrorArea.u4CheckAddr = CodeFls_stgMultiOpInfo.u4OpAddr;
                CodeFls_stgMirrorArea.pu1CheckBuf = CodeFls_stgMultiOpInfo.pu1BufAddr;
                CodeFls_stgMirrorArea.u4CheckSize = CodeFls_stgMultiOpInfo.u4OpSize;
                CodeFls_stgMirrorArea.u4CheckBank = CodeFls_stgMultiOpInfo.u4BankAddr;
                CodeFls_stgMirrorArea.u1CheckFaci = CodeFls_stgMultiOpInfo.u1FaciNum;
                CodeFls_stgMirrorArea.u1CheckSVA  = CodeFls_stgMultiOpInfo.u1SVAStatus;

                /* Blank Check processing */
                u1aRet = CodeFls_Drv_BlankCheckOp();
                if( (Std_ReturnType)E_OK == u1aRet )
                {
                    CodeFls_u1gJobStatus = CODEFLS_BUSY;
                    CodeFls_u1gMirrorJobStatus = CodeFls_u1gJobStatus;
                    CodeFls_u1gJobResult = CODEFLS_JOB_PENDING;
                    CodeFls_u1gMirrorJobResult = CodeFls_u1gJobResult;
                }
                else
                {
                    CodeFls_u1gJobStatus = CODEFLS_IDLE;
                    CodeFls_u1gMirrorJobStatus = CodeFls_u1gJobStatus;
                    CodeFls_u1gJobResult = CODEFLS_INCONSISTENT;
                    CodeFls_u1gMirrorJobResult = CodeFls_u1gJobResult;
                }
            }
            else
            {
                /* Parameter Error */
                CodeFls_u1gJobResult = CODEFLS_JOB_FAILED;
                CodeFls_u1gMirrorJobResult = CodeFls_u1gJobResult;
            }
        }
        /* UNINIT,BUSY is Failed */
        else
        {
            CodeFls_u1gJobStatus = CODEFLS_UNINIT;
            CodeFls_u1gMirrorJobStatus = CodeFls_u1gJobStatus;
            CodeFls_u1gJobResult = CODEFLS_JOB_FAILED;
            CodeFls_u1gMirrorJobResult = CodeFls_u1gJobResult;
        }
    }
    else
    {
        CodeFls_u1gJobStatus = CODEFLS_IDLE;
        CodeFls_u1gMirrorJobStatus = CodeFls_u1gJobStatus;
        CodeFls_u1gJobResult = CODEFLS_JOB_FAILED;
        CodeFls_u1gMirrorJobResult = CodeFls_u1gJobResult;
    }
}

/****************************************************************************/
/* Function Name | CodeFls_Suspend                                          */
/* Description   | OTA_CodeFlash interrupts memory operations that          */
/*               | the driver is performing on the hardware.                */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | E_OK                       : Successful completion       */
/*               | E_NOT_OK                   : Failed                      */
/* Notes         | Synchronous processing                                   */
/****************************************************************************/
FUNC(Std_ReturnType, MEM_CODE) CodeFls_Suspend(void)
{
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;

    u1aRet = E_NOT_OK;

    if( CodeFls_u1gMirrorJobStatus == CodeFls_u1gJobStatus )
    {
        if( CODEFLS_BUSY == CodeFls_u1gJobStatus )
        {
            if( (CodeFls_stgMirrorArea.u1CheckCmd == CodeFls_stgMultiOpInfo.u1Cmd) &&
                (CodeFls_stgMirrorArea.u1CheckFaci == CodeFls_stgMultiOpInfo.u1FaciNum) )
            {
                if( (CODEFLS_REQ_ERASE == CodeFls_stgMultiOpInfo.u1Cmd) || (CODEFLS_REQ_WRITE == CodeFls_stgMultiOpInfo.u1Cmd) )
                {
                    /* FACI Number is nomal */
                    if( (CODEFLS_U1_FACI_0 == CodeFls_stgMultiOpInfo.u1FaciNum) || (CODEFLS_U1_FACI_1 == CodeFls_stgMultiOpInfo.u1FaciNum) )
                    {
                        /* Perform suspend processing */
                        u1aRet = CodeFls_Drv_SuspendOp(CodeFls_stgMultiOpInfo.u1FaciNum);

                        /* Suspend result is E_OK */
                        if( (Std_ReturnType)E_OK == u1aRet )
                        {
                            /* Transition to Read Mode */
                            u1aRet = CodeFls_Drv_SwitchModeStart(CodeFls_stgMultiOpInfo.u1FaciNum, CODEFLS_U2_MODE_USER);
                        }
                    }
                }
                else if( CODEFLS_REQ_SWITCHVALIDAREA == CodeFls_stgMultiOpInfo.u1Cmd )
                {
                    /* Do Nothing */
                }
                else if( CODEFLS_REQ_BLANKCHECK == CodeFls_stgMultiOpInfo.u1Cmd )
                {
                    u1aRet = E_OK;
                }
                else
                {
                    /* Do Nothing */
                }
            }
        }
    }
    return((Std_ReturnType)u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_Resume                                           */
/* Description   | Resume memory operations that the OTA_CodeFlash driver   */
/*               | interrupted to the hardware.                             */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | E_OK           : Successful completion                   */
/*               | E_NOT_OK       : Failed                                  */
/* Notes         | Synchronous processing                                   */
/****************************************************************************/
FUNC(Std_ReturnType, MEM_CODE) CodeFls_Resume(void)
{
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;

    /* Set return value is E_NOT_OK */
    u1aRet = E_NOT_OK;

    if( CodeFls_u1gMirrorJobStatus == CodeFls_u1gJobStatus )
    {
        if( CODEFLS_BUSY == CodeFls_u1gJobStatus )
        {
            if( CodeFls_stgMirrorArea.u1CheckCmd == CodeFls_stgMultiOpInfo.u1Cmd )
            {
                if( (CODEFLS_REQ_ERASE == CodeFls_stgMultiOpInfo.u1Cmd) || (CODEFLS_REQ_WRITE == CodeFls_stgMultiOpInfo.u1Cmd) )
                {
                    u1aRet = E_OK;
                }
                else if( CODEFLS_REQ_SWITCHVALIDAREA == CodeFls_stgMultiOpInfo.u1Cmd )
                {
                    /* Do Nothing */
                }
                else if( CODEFLS_REQ_BLANKCHECK == CodeFls_stgMultiOpInfo.u1Cmd )
                {
                    u1aRet = E_OK;
                }
                else
                {
                    /* Do Nothing */
                }
            }
        }
    }
    return((Std_ReturnType)u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_CheckInvalidArea                                 */
/* Description   | Verifies that the invalid area of the flash memory is    */
/*                 specified.                                               */
/* Preconditions | -                                                        */
/* Parameters    | [IN]u4Addr      :address                                 */
/*               | [IN]u4Size      :size - byte                             */
/* Return Value  | E_OK           : Successful completion                   */
/*               | E_NOT_OK       : Failed                                  */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, MEM_CODE) CodeFls_CheckInvalidArea
(
    VAR(uint32, AUTOMATIC) u4Addr,
    VAR(uint32, AUTOMATIC) u4Size
)
{
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;

    u1aRet = CodeFls_Sub_CheckInvalidArea(u4Addr, u4Size);

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_GetEccErrorAddressRom                            */
/* Description   | It confirms the occurrence of the ECC error of a ROM     */
/*               | area.                                                    */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | CODEFLS_U1_ECC_CHECK_OK        : ECC error not occurring */
/*               | CODEFLS_U1_ECC_CHECK_ERROR_1BIT  :                       */
/*               |                               ECC error occurrence(1bit) */
/*               | CODEFLS_U1_ECC_CHECK_ERROR_2BIT  :                       */
/*               |                               ECC error occurrence(2bit) */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(uint8, MEM_CODE) CodeFls_GetEccErrorAddressRom
(
    VAR(uint32, AUTOMATIC) TargetAddr,
    VAR(uint32, AUTOMATIC) TargetSize
)
{
    VAR(uint8, AUTOMATIC) u1aRet;

    u1aRet = CodeFls_Drv_GetEccErrorAddressRom1bit(TargetAddr, TargetSize);

    if( CODEFLS_U1_ECC_CHECK_OK == u1aRet )
    {
        u1aRet = CodeFls_Drv_GetEccErrorAddressRom2bit(TargetAddr, TargetSize);
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_ClearJobStatus                                   */
/* Description   | Clear the job in CodeFls.                                */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, MEM_CODE) CodeFls_ClearJobStatus(void)
{
    VAR(uint8, AUTOMATIC) u1aFaciNum;

    u1aFaciNum = CodeFls_stgMultiOpInfo.u1FaciNum;

    if( CODEFLS_IDLE == CodeFls_u1gJobStatus )
    {
        /* No process */
    }
    else if( CODEFLS_BUSY == CodeFls_u1gJobStatus )
    {
        /* Stop the sequencer with a kill command */
        /* Do not check the results because it is a recovery process after an error occurs. */
        (void)CodeFls_Drv_ForcedStop(u1aFaciNum);
        (void)CodeFls_Drv_SwitchModeStart(u1aFaciNum, CODEFLS_U2_MODE_USER);

        CodeFls_u1gJobStatus = CODEFLS_IDLE;
        CodeFls_u1gMirrorJobStatus = CodeFls_u1gJobStatus;
    }
    else if( CODEFLS_UNINIT == CodeFls_u1gJobStatus )
    {
        /* No process */
    }
    else
    {
        CodeFls_u1gJobStatus = CODEFLS_IDLE;
        CodeFls_u1gMirrorJobStatus = CodeFls_u1gJobStatus;
    }
    CodeFls_u1gJobResult = CODEFLS_JOB_FAILED;
    CodeFls_u1gMirrorJobResult = CodeFls_u1gJobResult;

}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define MEM_STOP_SEC_CODE
#include <Mem_MemMap.h>


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1.00          :2025/03/24                                              */
/*  v1.01          :2025/04/14                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
