/* CodeFls_Sub_c                                                            */
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


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
static FUNC(Std_ReturnType, MEM_CODE) CodeFls_Sub_sMultiOperationSVA
(
    P2VAR(uint8, AUTOMATIC, MEM_APPL_DATA) pu1IsFinish
);
static FUNC(uint8, MEM_CODE) CodeFls_Sub_sCheckAddress
(
    VAR(uint32, AUTOMATIC) u4Addr,
    VAR(uint32, AUTOMATIC) u4Size
);
static FUNC(void, MEM_CODE) CodeFls_Sub_sExecPropertyErasure(void);
static FUNC(Std_ReturnType, MEM_CODE) CodeFls_Sub_sExecPropertyProgramming1(void);
static FUNC(Std_ReturnType, MEM_CODE) CodeFls_Sub_sExecPropertyProgramming2(void);
static FUNC(Std_ReturnType, MEM_CODE) CodeFls_Sub_sExecTagErasePre1(void);
static FUNC(Std_ReturnType, MEM_CODE) CodeFls_Sub_sExecTagUpdatePre1(void);
static FUNC(Std_ReturnType, MEM_CODE) CodeFls_Sub_sExecTagErasePre2(void);
static FUNC(Std_ReturnType, MEM_CODE) CodeFls_Sub_sExecTagUpdatePre2(void);
static FUNC(void, MEM_CODE) CodeFls_Sub_sExecSwitchErasure(void);
static FUNC(Std_ReturnType, MEM_CODE) CodeFls_Sub_sExecSwitchProgramming(void);
static FUNC(Std_ReturnType, MEM_CODE) CodeFls_Sub_sExecTagErasure(void);
static FUNC(Std_ReturnType, MEM_CODE) CodeFls_Sub_sExecTagUpdate(void);
static FUNC(uint8, MEM_CODE) CodeFls_Sub_sCheckTopAddress
(
    VAR(uint32, AUTOMATIC) u4Addr
);
static FUNC(uint8, MEM_CODE) CodeFls_Sub_sCheckEndAddress
(
    VAR(uint32, AUTOMATIC) u4Addr,
    VAR(uint32, AUTOMATIC) u4Size
);
static FUNC(uint8, MEM_CODE) CodeFls_Sub_CheckInvalidArea_InfoNum
(
    VAR(uint8, AUTOMATIC) u1aInfoNum
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

#define MEM_STOP_SEC_CONST_32
#include <Mem_MemMap.h>


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define MEM_START_SEC_CODE
#include <Mem_MemMap.h>

/****************************************************************************/
/* Function Name | CodeFls_Sub_InitVariables                                */
/* Description   | Initialize RAM Used by CODEFLS Driver                    */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, MEM_CODE) CodeFls_Sub_InitVariables(void)
{
    VAR(uint8, AUTOMATIC) u1aLoopCnt;

    CodeFls_u1gJobStatus = CODEFLS_UNINIT;
    CodeFls_u1gMirrorJobStatus = CodeFls_u1gJobStatus;

    CodeFls_u1gJobResult = CODEFLS_JOB_OK;
    CodeFls_u1gMirrorJobResult = CodeFls_u1gJobResult;

    CodeFls_u4gJobTimer = CODEFLS_U4_JOBTIMER_RESET;

    CodeFls_Sub_InitOpInfo();

    /* Initialize the CPU operating frequency to the maximum CPU operating frequency for each microcomputer */
    CodeFls_u2gCpuFreq = CODEFLS_U2_CPUCLK_MAX;

    for( u1aLoopCnt = CODEFLS_U1_VAL_0; u1aLoopCnt < CODEFLS_U1_TRANSFERSIZE_HWAREA; u1aLoopCnt++ )
    {
        CodeFls_u4gWriteBuffer[u1aLoopCnt] = CODEFLS_U4_VAL_0;
    }
}

/****************************************************************************/
/* Function Name | CodeFls_Sub_InitOpInfo                                   */
/* Description   | Initialize Operation Information                         */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, MEM_CODE) CodeFls_Sub_InitOpInfo(void)
{
    CodeFls_stgMultiOpInfo.u1Cmd       = CODEFLS_U1_OPINFO_CMD_NONE;
    CodeFls_stgMultiOpInfo.u4OpAddr    = CODEFLS_U4_OPINFO_ADDR_NONE;
    CodeFls_stgMultiOpInfo.pu1BufAddr  = CODEFLS_PU1_OPINFO_BUFFER_NULL;
    CodeFls_stgMultiOpInfo.u4OpSize    = CODEFLS_U4_OPINFO_SIZE_NONE;
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
}

/****************************************************************************/
/* Function Name | CodeFls_Sub_GetFaciMax                                   */
/* Description   | Retrieve Maximum FACI Count Based on Configured          */
/*               | Microcontroller Type                                     */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | Maximum FACI Count                                       */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(uint8, MEM_CODE) CodeFls_Sub_GetFaciMax(void)
{
    VAR(uint8, AUTOMATIC) u1aRet;

    /* Set the value of the microcontroller with the fewest number of FACI as the initial value */
    u1aRet = CODEFLS_U1_FACI_NUM_U2A8_U2A6;

    if( CODEFLS_PRODUCT_U2A16 == CODEFLS_DEVCFG_DATA.ProductSetting->ProductType )
    {
        u1aRet = CODEFLS_U1_FACI_NUM_U2A16;
    }
    else
    {
        /* No process */
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_Sub_GetFaciNum                                   */
/* Description   | Obtain FACI Number from Address                          */
/* Preconditions | -                                                        */
/* Parameters    | [IN]u4Addr           : Address                           */
/*               | [IN]u4Size           : Size                              */
/* Return Value  | FACI Identifier                                          */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(uint8, MEM_CODE) CodeFls_Sub_GetFaciNum
(
    VAR(uint32, AUTOMATIC) u4Addr,
    VAR(uint32, AUTOMATIC) u4Size
)
{
    VAR(uint8, AUTOMATIC) u1aInfoNum;
    VAR(uint8, AUTOMATIC) u1aMapMode;
    VAR(uint8, AUTOMATIC) u1aRet;

    u1aRet = CODEFLS_U1_FACI_0;

    if( CODEFLS_PRODUCT_U2A16 == CODEFLS_DEVCFG_DATA.ProductSetting->ProductType )
    {
        /* checks which Bank the target address belongs to */
        u1aInfoNum = CodeFls_Sub_sCheckAddress(u4Addr, u4Size);
        if( CODEFLS_U1_INFONUM_NONE != u1aInfoNum )
        {
            /* Because the bank arrangement differs depending on the Map Mode, perform judgment for each Map Mode */
            u1aMapMode = CodeFls_Drv_GetMapMode();
            if( CODEFLS_U1_MAPMODE_DOUBLE == u1aMapMode )
            {
                if( (CODEFLS_U1_VAL_1 == u1aInfoNum) ||
                    (CODEFLS_U1_VAL_3 == u1aInfoNum) )
                {
                    u1aRet = CODEFLS_U1_FACI_1;
                }
                else
                {
                    /* No process */
                }
            }
            else
            {
                if( (CODEFLS_U1_VAL_2 == u1aInfoNum) ||
                    (CODEFLS_U1_VAL_3 == u1aInfoNum) )
                {
                    u1aRet = CODEFLS_U1_FACI_1;
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

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_Sub_Reset                                        */
/* Description   | Issue Forced Termination Command to Stop Flash Sequencer */
/* Preconditions | -                                                        */
/* Parameters    | [IN]u1FaciNum           : FACI Identifier                */
/* Return Value  | E_OK                    : Successful completion          */
/*               | E_NOT_OK                : Failed                         */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, MEM_CODE) CodeFls_Sub_Reset
(
    VAR(uint8, AUTOMATIC) u1FaciNum
)
{
    VAR(uint16, AUTOMATIC) u2aFlashMode;
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;

    u1aRet = E_OK;

    u2aFlashMode = CodeFls_Drv_GetFlashMode(u1FaciNum);
    if( CODEFLS_U2_MODE_USER == u2aFlashMode )
    {
        /* Transition to data flash P/E mode */
        u1aRet = CodeFls_Drv_SwitchModeStart(u1FaciNum, CODEFLS_U2_MODE_DPE);
    }
    else
    {
        /* No process */
    }

    if( (Std_ReturnType)E_OK == u1aRet )
    {
        u1aRet = CodeFls_Drv_ForcedStop(u1FaciNum);
        if( (Std_ReturnType)E_OK == u1aRet )
        {
            /* Transition to read mode */
            u1aRet = CodeFls_Drv_SwitchModeStart(u1FaciNum, CODEFLS_U2_MODE_USER);
        }
        else
        {
            /* Transition to read mode after the recovery process */
            CodeFls_Drv_ErrRefresh(u1FaciNum);
            /* Do not check the results because it is a recovery process after an error occurs. */
            (void)CodeFls_Drv_SwitchModeStart(u1FaciNum, CODEFLS_U2_MODE_USER);
        }

    }
    else
    {
        /* Re-set to read mode for recovery process */
        /* Do not check the results because it is a recovery process after an error occurs. */
        (void)CodeFls_Drv_SwitchModeStart(u1FaciNum, CODEFLS_U2_MODE_USER);
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_Sub_CheckParamCtrl                               */
/* Description   | Validate Code Flash Control Initialization Arguments     */
/* Preconditions | -                                                        */
/* Parameters    | [IN]u1ReqKind           : Request Control Type           */
/*               | [IN]u4Addr              : Control Address                */
/*               | [IN]u4Size              : Size (Unit: Byte)              */
/* Return Value  | E_OK                    : Successful completion          */
/*               | E_NOT_OK                : Failed                         */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, MEM_CODE) CodeFls_Sub_CheckParamCtrl
(
    VAR(uint8, AUTOMATIC) u1ReqKind,
    VAR(uint32, AUTOMATIC) u4Addr,
    VAR(uint32, AUTOMATIC) u4Size
)
{
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;
    VAR(uint8, AUTOMATIC) u1aInfoNum;

    u1aRet = E_NOT_OK;

    if( (CODEFLS_REQ_WRITE == u1ReqKind) || (CODEFLS_REQ_ERASE == u1ReqKind) ||
        (CODEFLS_REQ_WRITABLECHECK == u1ReqKind) || ( CODEFLS_REQ_BLANKCHECK == u1ReqKind) )
    {
        /* Check whether it is within the code flash area range */
        u1aInfoNum = CodeFls_Sub_sCheckAddress(u4Addr, u4Size);
        if( CODEFLS_U1_INFONUM_NONE != u1aInfoNum )
        {
            u1aRet = E_OK;
        }
        else
        {
            /* No process */
        }
    }
    else if( CODEFLS_REQ_SWITCHVALIDAREA == u1ReqKind )
    {
        /* Address and size are Don't care */
        u1aRet = E_OK;
    }
    else
    {
        /* No process */
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_Sub_CheckParamErase                              */
/* Description   | Validate Erase Request Arguments                         */
/* Preconditions | -                                                        */
/* Parameters    | [IN]u4EraseAddr         : Starting Block Address of      */
/*               |                           Erase Target Area              */
/*               | [IN]u4EraseSize         : Erase Size (Unit: Byte)        */
/*               | [OUT]pu1InfoNum         : Index in Code Flash Region     */
/*               |                           Information Configuration      */
/*               |                           Table                          */
/* Return Value  | E_OK                    : Successful completion          */
/*               | E_NOT_OK                : Failed                         */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, MEM_CODE) CodeFls_Sub_CheckParamErase
(
    VAR(uint32, AUTOMATIC) u4EraseAddr,
    VAR(uint32, AUTOMATIC) u4EraseSize,
    P2VAR(uint8, AUTOMATIC, MEM_APPL_DATA) pu1InfoNum
)
{
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;
    VAR(uint8, AUTOMATIC) u1aInfoNum;
    VAR(uint32, AUTOMATIC) u4aEndAddr;

    u1aRet = E_NOT_OK;

    /* Check whether it is within the code flash area range */
    u1aInfoNum = CodeFls_Sub_sCheckAddress(u4EraseAddr, u4EraseSize);
    if( CODEFLS_U1_INFONUM_NONE != u1aInfoNum )
    {
        /* Alignment check of the start address */
        if( (((CODEFLS_DEVCFG_DATA.CodeFlsSetting->CodeFlsInfo[u1aInfoNum].Addr + CODEFLS_U4_CF1_ADDR_64K_START) > u4EraseAddr) &&
                (CODEFLS_U4_VAL_0 == (u4EraseAddr & CODEFLS_U4_SMALL_BLOCK_MASK))) ||
            (((CODEFLS_DEVCFG_DATA.CodeFlsSetting->CodeFlsInfo[u1aInfoNum].Addr + CODEFLS_U4_CF1_ADDR_64K_START) <= u4EraseAddr) &&
                (CODEFLS_U4_VAL_0 == (u4EraseAddr & CODEFLS_U4_BLOCK_MASK))) )
        {
            /* The overflow check of the final address is ensured by CodeFls_Sub_sCheckAddress */
            u4aEndAddr = u4EraseAddr + (u4EraseSize - CODEFLS_U4_VAL_1);

            /* Alignment check of the enf address */
            if( (((CODEFLS_DEVCFG_DATA.CodeFlsSetting->CodeFlsInfo[u1aInfoNum].Addr + CODEFLS_U4_CF1_ADDR_64K_START) > u4aEndAddr) &&
                    (CODEFLS_U4_VAL_0 == ((u4aEndAddr + CODEFLS_U4_VAL_1) & CODEFLS_U4_SMALL_BLOCK_MASK))) ||
                (((CODEFLS_DEVCFG_DATA.CodeFlsSetting->CodeFlsInfo[u1aInfoNum].Addr + CODEFLS_U4_CF1_ADDR_64K_START) <= u4aEndAddr) &&
                    (CODEFLS_U4_VAL_0 == ((u4aEndAddr + CODEFLS_U4_VAL_1) & CODEFLS_U4_BLOCK_MASK))) )
            {
                *pu1InfoNum = u1aInfoNum;
                u1aRet = E_OK;
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
    else
    {
        /* Outside the code flash area range */
        /* No process */
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_Sub_CheckParamWrite                              */
/* Description   | Validate Write Request Arguments                         */
/* Preconditions | -                                                        */
/* Parameters    | [IN]u4TargetAddr        : Starting Code Flash Memory     */
/*               |                           Address for Write Operation    */
/*               | [IN]u4DataSize          : Write Data Size (Unit: Byte)   */
/* Return Value  | E_OK                    : Successful completion          */
/*               | E_NOT_OK                : Failed                         */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, MEM_CODE) CodeFls_Sub_CheckParamWrite
(
    VAR(uint32, AUTOMATIC) u4TargetAddr,
    VAR(uint32, AUTOMATIC) u4DataSize
)
{
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;
    VAR(uint8, AUTOMATIC) u1aInfoNum;

    u1aRet = E_NOT_OK;

     /* Check whether it is within the code flash area range */
    u1aInfoNum = CodeFls_Sub_sCheckAddress(u4TargetAddr, u4DataSize);
    if( CODEFLS_U1_INFONUM_NONE != u1aInfoNum )
    {
        /* Address and size alignment check */
        if( (CODEFLS_U4_VAL_0 == (u4TargetAddr & CODEFLS_WRITEDATA_MASK)) &&
            (CODEFLS_U4_VAL_0 == (u4DataSize & CODEFLS_WRITEDATA_MASK)) )
        {
            u1aRet = E_OK;
        }
        else
        {
            /* No process */
        }
    }
    else
    {
        /* Outside the code flash area range */
        /* No process */
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_Sub_CheckParamBlankCheck                         */
/* Description   | Check the arguments of the blank check request.          */
/* Preconditions | -                                                        */
/* Parameters    | [IN]u4TargetAddr        : Blank check start address      */
/*               | [IN]u4DataSize          : Blank check data length        */
/* Return Value  | E_OK                    : Successful completion          */
/*               | E_NOT_OK                : Failed                         */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, MEM_CODE) CodeFls_Sub_CheckParamBlankCheck
(
    VAR(uint32, AUTOMATIC) u4TargetAddr,
    VAR(uint32, AUTOMATIC) u4DataSize
)
{
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;
    VAR(uint8, AUTOMATIC) u1aInfoNum;

    u1aRet = E_NOT_OK;

    /* Check if it is within the code flash area range. */
    u1aInfoNum = CodeFls_Sub_sCheckAddress(u4TargetAddr, u4DataSize);
    if( CODEFLS_U1_INFONUM_NONE != u1aInfoNum )
    {
        /* Verify that the code flash memory address and data size (in bytes) are size-aligned. */
        if( (CODEFLS_U4_VAL_0 == (u4TargetAddr & CODEFLS_BLANK_CHECK_DATA_MASK)) &&
            (CODEFLS_U4_VAL_0 == (u4DataSize & CODEFLS_BLANK_CHECK_DATA_MASK)) )
        {
            u1aRet = E_OK;
        }
        else
        {
            /* No process */
        }
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_Sub_CheckTimeOut                                 */
/* Description   | Check for Flash Control Timeout                          */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | E_OK                    : No Timeout                     */
/*               | E_NOT_OK                :Timeout Occurred                */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, MEM_CODE) CodeFls_Sub_CheckTimeOut(void)
{
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;
    VAR(uint32, AUTOMATIC) u4aTimeOut;

    u1aRet = E_OK;

    /* Set job management timer */
    CodeFls_Drv_GetCounterValue(&u4aTimeOut);

    if( CodeFls_u4gJobTimer <= u4aTimeOut )
    {
        u4aTimeOut -= CodeFls_u4gJobTimer;
    }
    else
    {
        u4aTimeOut += ((CODEFLS_U4_TIMER_MAX - CodeFls_u4gJobTimer) + CODEFLS_U4_VAL_1);
    }

    if( CODEFLS_REQ_SWITCHVALIDAREA == CodeFls_stgMultiOpInfo.u1Cmd )
    {
        /* SwitchValidArea */
        /* Timeout occurrence check (considering overflow) */
        if( ((CODEFLS_U1_SVA_PROPERTY_ERASE  == CodeFls_stgMultiOpInfo.u1SVAStatus) && (CODEFLS_U4_PROPERTY_ERASE_TIME <= u4aTimeOut)) ||
            ((CODEFLS_U1_SVA_PROPERTY_WRITE1 == CodeFls_stgMultiOpInfo.u1SVAStatus) && (CODEFLS_U4_PROPERTY_WRITE_TIME <= u4aTimeOut)) ||
            ((CODEFLS_U1_SVA_PROPERTY_WRITE2 == CodeFls_stgMultiOpInfo.u1SVAStatus) && (CODEFLS_U4_PROPERTY_WRITE_TIME <= u4aTimeOut)) ||
            ((CODEFLS_U1_SVA_TAG_ERASE_PRE1  == CodeFls_stgMultiOpInfo.u1SVAStatus) && (CODEFLS_U4_TAG_ERASE_TIME      <= u4aTimeOut)) ||
            ((CODEFLS_U1_SVA_TAG_UPDATE_PRE1 == CodeFls_stgMultiOpInfo.u1SVAStatus) && (CODEFLS_U4_TAG_UPDATE_TIME     <= u4aTimeOut)) ||
            ((CODEFLS_U1_SVA_TAG_ERASE_PRE2  == CodeFls_stgMultiOpInfo.u1SVAStatus) && (CODEFLS_U4_TAG_ERASE_TIME      <= u4aTimeOut)) ||
            ((CODEFLS_U1_SVA_TAG_UPDATE_PRE2 == CodeFls_stgMultiOpInfo.u1SVAStatus) && (CODEFLS_U4_TAG_UPDATE_TIME     <= u4aTimeOut)) ||
            ((CODEFLS_U1_SVA_SWITCH_ERASE    == CodeFls_stgMultiOpInfo.u1SVAStatus) && (CODEFLS_U4_SWITCH_ERASE_TIME   <= u4aTimeOut)) ||
            ((CODEFLS_U1_SVA_SWITCH_WRITE    == CodeFls_stgMultiOpInfo.u1SVAStatus) && (CODEFLS_U4_SWITCH_WRITE_TIME   <= u4aTimeOut)) ||
            ((CODEFLS_U1_SVA_TAG_ERASE       == CodeFls_stgMultiOpInfo.u1SVAStatus) && (CODEFLS_U4_TAG_ERASE_TIME      <= u4aTimeOut)) ||
            ((CODEFLS_U1_SVA_TAG_UPDATE      == CodeFls_stgMultiOpInfo.u1SVAStatus) && (CODEFLS_U4_TAG_UPDATE_TIME     <= u4aTimeOut)) )
        {
            u1aRet = E_NOT_OK;
        }
        else
        {
            /* No process */
        }
    }
    else
    {
        /* Write/Erase */
        /* Timeout occurrence check (considering overflow) */
        if( ((CODEFLS_REQ_ERASE == CodeFls_stgMultiOpInfo.u1Cmd) && (CODEFLS_U4_ERASE_TIME <= u4aTimeOut)) ||
            ((CODEFLS_REQ_WRITE == CodeFls_stgMultiOpInfo.u1Cmd) && (CODEFLS_U4_WRITE_TIME <= u4aTimeOut)) )
        {
            u1aRet = E_NOT_OK;
        }
        else
        {
            /* No process */
        }
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_Sub_CheckSwitchValidArea                         */
/* Description   | Verify Flash Memory Page/Block Switching Capability      */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | E_OK                    : Swappable                      */
/*               | E_NOT_OK                : Non-Swappable                  */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, MEM_CODE) CodeFls_Sub_CheckSwitchValidArea(void)
{
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;
    VAR(uint8, AUTOMATIC) u1aMapMode;

    u1aRet = E_NOT_OK;

    u1aMapMode = CodeFls_Drv_GetMapMode();

    if( CODEFLS_U1_MAPMODE_DOUBLE == u1aMapMode )
    {
        u1aRet = E_OK;
    }
    else
    {
        /* No process */
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_Sub_MultiOperation                               */
/* Description   | Perform Processing During Flash Control Execution        */
/* Preconditions | -                                                        */
/* Parameters    | [IN]u1FaciNum           : FACI Identifier                */
/*               | [OUT]pu1IsFinish        : Job Completion Check Flag      */
/* Return Value  | E_OK                    : Successful completion          */
/*               | E_NOT_OK                : Failed                         */
/*               | CODEFLS_U1_BLANKCHECK_NOT_BLANK : writing in impossible  */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, MEM_CODE) CodeFls_Sub_MultiOperation
(
    VAR(uint8, AUTOMATIC) u1FaciNum,
    P2VAR(uint8, AUTOMATIC, MEM_APPL_DATA) pu1IsFinish
)
{
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;

    u1aRet = E_OK;
    *pu1IsFinish = CODEFLS_U1_FALSE;

    if( CODEFLS_REQ_SWITCHVALIDAREA == CodeFls_stgMultiOpInfo.u1Cmd )
    {
        u1aRet = CodeFls_Sub_sMultiOperationSVA(pu1IsFinish);
    }
    else
    {
        if( CODEFLS_U4_OPINFO_SIZE_NONE < CodeFls_stgMultiOpInfo.u4OpSize )
        {
            if( CODEFLS_REQ_ERASE == CodeFls_stgMultiOpInfo.u1Cmd )
            {
                CodeFls_Drv_EraseOp(u1FaciNum);
                /* Set job management timer */
                CodeFls_Drv_GetCounterValue(&CodeFls_u4gJobTimer);
            }
            else if( CODEFLS_REQ_WRITE == CodeFls_stgMultiOpInfo.u1Cmd )
            {
                CodeFls_Drv_WriteOp(u1FaciNum);
                /* Set job management timer */
                CodeFls_Drv_GetCounterValue(&CodeFls_u4gJobTimer);
            }
            else if( CODEFLS_REQ_BLANKCHECK == CodeFls_stgMultiOpInfo.u1Cmd )
            {
                u1aRet = CodeFls_Drv_BlankCheckOp();
            }
            else
            {
                /* No process */
            }
        }
        else
        {
            /* no remaining jobs, enable the job completion check flag */
            *pu1IsFinish = CODEFLS_U1_TRUE;
        }
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_Sub_CheckInvalidArea                             */
/* Description   | Verifies that the invalid area of the flash memory is    */
/*                 specified.                                               */
/* Preconditions | -                                                        */
/* Parameters    | [IN]u4Addr      :address                                 */
/*               | [IN]u4Size      :size - byte                             */
/* Return Value  | E_OK           : Successful completion                   */
/*               | E_NOT_OK       : Failed                                  */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, MEM_CODE) CodeFls_Sub_CheckInvalidArea
(
    VAR(uint32, AUTOMATIC) u4Addr,
    VAR(uint32, AUTOMATIC) u4Size
)
{
    VAR(uint8, AUTOMATIC) u1aInfoNum;
    VAR(uint8, AUTOMATIC) u1aRet;

    u1aInfoNum = CodeFls_Sub_sCheckTopAddress(u4Addr);
    u1aRet = CodeFls_Sub_CheckInvalidArea_InfoNum(u1aInfoNum);

    if( (Std_ReturnType)E_OK == u1aRet )
    {
        u1aInfoNum = CodeFls_Sub_sCheckEndAddress(u4Addr, u4Size);
        u1aRet = CodeFls_Sub_CheckInvalidArea_InfoNum(u1aInfoNum);
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_Sub_CheckMirrorOpInfo                            */
/* Description   | Check if it is a registered Mirror.                      */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | E_OK            : Successful completion                  */
/*               | E_NOT_OK        : Failed                                 */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, MEM_CODE) CodeFls_Sub_CheckMirrorOpInfo(void)
{
    /* Variable Declarations */
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;

    u1aRet = E_NOT_OK;
    if( (CodeFls_stgMirrorArea.u1CheckCmd == CodeFls_stgMultiOpInfo.u1Cmd) &&
        (CodeFls_stgMirrorArea.u4CheckAddr == CodeFls_stgMultiOpInfo.u4OpAddr) &&
        (CodeFls_stgMirrorArea.pu1CheckBuf == CodeFls_stgMultiOpInfo.pu1BufAddr) &&
        (CodeFls_stgMirrorArea.u4CheckSize == CodeFls_stgMultiOpInfo.u4OpSize) &&
        (CodeFls_stgMirrorArea.u4CheckBank == CodeFls_stgMultiOpInfo.u4BankAddr) &&
        (CodeFls_stgMirrorArea.u1CheckFaci == CodeFls_stgMultiOpInfo.u1FaciNum) &&
        (CodeFls_stgMirrorArea.u1CheckSVA == CodeFls_stgMultiOpInfo.u1SVAStatus) )
    {
        u1aRet = E_OK;
    }

    return(u1aRet);
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | CodeFls_Sub_sMultiOperationSVA                           */
/* Description   | Control Execution-Based Processing for Flash Memory      */
/*               | Page/Block Switching in Flash Control                    */
/* Preconditions | -                                                        */
/* Parameters    | [OUT]pu1IsFinish        : Job Completion Check Flag      */
/* Return Value  | E_OK                    : Successful completion          */
/*               | E_NOT_OK                : Failed                         */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(Std_ReturnType, MEM_CODE) CodeFls_Sub_sMultiOperationSVA
(
    P2VAR(uint8, AUTOMATIC, MEM_APPL_DATA) pu1IsFinish
)
{
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;

    u1aRet = E_NOT_OK;
    *pu1IsFinish = CODEFLS_U1_FALSE;

    /* Proceed with processing by flash memory valid area switching state */
    switch( CodeFls_stgMultiOpInfo.u1SVAStatus )
    {
    case CODEFLS_U1_SVA_PROPERTY_ERASE :
        /* Property Erasure running */
        CodeFls_Sub_sExecPropertyErasure();
        u1aRet = E_OK;
        break;

    case CODEFLS_U1_SVA_PROPERTY_WRITE1:
        /* Property Programming Running1 */
        u1aRet = CodeFls_Sub_sExecPropertyProgramming1();
        break;

    case CODEFLS_U1_SVA_PROPERTY_WRITE2:
        /* Property Programming Running2 */
        u1aRet = CodeFls_Sub_sExecPropertyProgramming2();
        break;

    case CODEFLS_U1_SVA_TAG_ERASE_PRE1 :
        /* TAG Erasure running pre1 */
        u1aRet = CodeFls_Sub_sExecTagErasePre1();
        break;

    case CODEFLS_U1_SVA_TAG_UPDATE_PRE1:
        /* TAG Update running pre1 */
        u1aRet = CodeFls_Sub_sExecTagUpdatePre1();
        break;

    case CODEFLS_U1_SVA_TAG_ERASE_PRE2 :
        /* TAG Erasure running pre2 */
        u1aRet = CodeFls_Sub_sExecTagErasePre2();
        break;

    case CODEFLS_U1_SVA_TAG_UPDATE_PRE2:
        /* TAG Update running pre2 */
        u1aRet = CodeFls_Sub_sExecTagUpdatePre2();
        break;

    case CODEFLS_U1_SVA_SWITCH_ERASE   :
        /* Switch Erasure running */
        CodeFls_Sub_sExecSwitchErasure();
        u1aRet = E_OK;
        break;

    case CODEFLS_U1_SVA_SWITCH_WRITE   :
        /* Switch Programming running */
        u1aRet = CodeFls_Sub_sExecSwitchProgramming();
        break;

    case CODEFLS_U1_SVA_TAG_ERASE      :
        /* TAG erasure running */
        u1aRet = CodeFls_Sub_sExecTagErasure();
        break;

    case CODEFLS_U1_SVA_TAG_UPDATE     :
        /* TAG Update running */
        u1aRet = CodeFls_Sub_sExecTagUpdate();
        *pu1IsFinish = CODEFLS_U1_TRUE;
        break;

    default:
        /* No process */
        break;
    }

    /* Evacuate operation information to operation information mirror area */
    CodeFls_stgMirrorArea.u1CheckSVA  = CodeFls_stgMultiOpInfo.u1SVAStatus;

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_Sub_sExecPropertyErasure                         */
/* Description   | Executing Property Erasure                               */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(void, MEM_CODE) CodeFls_Sub_sExecPropertyErasure(void)
{
    CodeFls_Drv_SetCsaWriteDataChengeArea();
    CodeFls_Drv_CsaWriteOp();
    CodeFls_stgMultiOpInfo.u1SVAStatus = CODEFLS_U1_SVA_PROPERTY_WRITE1;

    /* Set job management timer */
    CodeFls_Drv_GetCounterValue(&CodeFls_u4gJobTimer);
}

/****************************************************************************/
/* Function Name | CodeFls_Sub_sExecPropertyProgramming1                    */
/* Description   | Executing Property Programming (first time)              */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | E_OK                    :                                */
/*               | E_NOT_OK                :                                */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(Std_ReturnType, MEM_CODE) CodeFls_Sub_sExecPropertyProgramming1(void)
{
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;
    VAR(uint8, AUTOMATIC) u1aResult;

    u1aRet = E_NOT_OK;

    u1aResult = CodeFls_Drv_SetCsaWriteDataOtherArea();
    if( CODEFLS_U1_TRUE == u1aResult )
    {
        CodeFls_Drv_CsaWriteOp();
        CodeFls_stgMultiOpInfo.u1SVAStatus = CODEFLS_U1_SVA_PROPERTY_WRITE2;

        /* Set job management timer */
        CodeFls_Drv_GetCounterValue(&CodeFls_u4gJobTimer);
        u1aRet = E_OK;
    }
    else
    {
        /* No process */
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_Sub_sExecPropertyProgramming2                    */
/* Description   | Executing Property Programming                           */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | E_OK                    :                                */
/*               | E_NOT_OK                :                                */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(Std_ReturnType, MEM_CODE) CodeFls_Sub_sExecPropertyProgramming2(void)
{
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;
    VAR(uint8, AUTOMATIC) u1aResult;

    u1aResult = CodeFls_Drv_SetCsaWriteDataOtherArea();
    if( CODEFLS_U1_TRUE == u1aResult )
    {
        CodeFls_Drv_CsaWriteOp();
        CodeFls_stgMultiOpInfo.u1SVAStatus = CODEFLS_U1_SVA_PROPERTY_WRITE2;

        /* Set job management timer */
        CodeFls_Drv_GetCounterValue(&CodeFls_u4gJobTimer);
        u1aRet = E_OK;
    }
    else
    {
        u1aResult = CodeFls_Drv_CheckSwitchArea();
        if( CODEFLS_U1_TRUE == u1aResult )
        {
            u1aRet = CodeFls_Drv_TagEraseOp();
            if( (Std_ReturnType)E_OK == u1aRet )
            {
                CodeFls_stgMultiOpInfo.u1SVAStatus = CODEFLS_U1_SVA_TAG_ERASE_PRE1;

                /* Set job management timer */
                CodeFls_Drv_GetCounterValue(&CodeFls_u4gJobTimer);
            }
            else
            {
                /* No process */
            }
        }
        else
        {
            u1aRet = CodeFls_Drv_SwitchEraseOp();
            if( (Std_ReturnType)E_OK == u1aRet )
            {
                CodeFls_stgMultiOpInfo.u1SVAStatus = CODEFLS_U1_SVA_SWITCH_ERASE;

                /* Set job management timer */
                CodeFls_Drv_GetCounterValue(&CodeFls_u4gJobTimer);
            }
            else
            {
                /* No process */
            }
        }
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_Sub_sExecTagErasePre1                            */
/* Description   | Executing TAG Erasure (Pre1)                             */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | E_OK                    :                                */
/*               | E_NOT_OK                :                                */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(Std_ReturnType, MEM_CODE) CodeFls_Sub_sExecTagErasePre1(void)
{
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;

    u1aRet = CodeFls_Drv_TagUpdateOp();
    if( (Std_ReturnType)E_OK == u1aRet )
    {
        CodeFls_stgMultiOpInfo.u1SVAStatus = CODEFLS_U1_SVA_TAG_UPDATE_PRE1;

        /* Set job management timer */
        CodeFls_Drv_GetCounterValue(&CodeFls_u4gJobTimer);
    }
    else
    {
        /* No process */
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_Sub_sExecTagUpdatePre1                           */
/* Description   | Executing TAG Update (Pre1)                              */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | E_OK                    :                                */
/*               | E_NOT_OK                :                                */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(Std_ReturnType, MEM_CODE) CodeFls_Sub_sExecTagUpdatePre1(void)
{
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;

    u1aRet = CodeFls_Drv_TagEraseOp();
    if( (Std_ReturnType)E_OK == u1aRet )
    {
        CodeFls_stgMultiOpInfo.u1SVAStatus = CODEFLS_U1_SVA_TAG_ERASE_PRE2;

        /* Set job management timer */
        CodeFls_Drv_GetCounterValue(&CodeFls_u4gJobTimer);
    }
    else
    {
        /* No process */
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_Sub_sExecTagErasePre2                            */
/* Description   | Executing TAG Erasure (Pre2)                             */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | E_OK                    :                                */
/*               | E_NOT_OK                :                                */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(Std_ReturnType, MEM_CODE) CodeFls_Sub_sExecTagErasePre2(void)
{
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;

    u1aRet = CodeFls_Drv_TagUpdateOp();
    if( (Std_ReturnType)E_OK == u1aRet )
    {
        CodeFls_stgMultiOpInfo.u1SVAStatus = CODEFLS_U1_SVA_TAG_UPDATE_PRE2;

        /* Set job management timer */
        CodeFls_Drv_GetCounterValue(&CodeFls_u4gJobTimer);
    }
    else
    {
        /* No process */
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_Sub_sExecTagUpdatePre2                           */
/* Description   | Executing TAG Update (Pre2)                              */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | E_OK                    :                                */
/*               | E_NOT_OK                :                                */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(Std_ReturnType, MEM_CODE) CodeFls_Sub_sExecTagUpdatePre2(void)
{
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;

    u1aRet = CodeFls_Drv_SwitchEraseOp();
    if( (Std_ReturnType)E_OK == u1aRet )
    {
        CodeFls_stgMultiOpInfo.u1SVAStatus = CODEFLS_U1_SVA_SWITCH_ERASE;

        /* Set job management timer */
        CodeFls_Drv_GetCounterValue(&CodeFls_u4gJobTimer);
    }
    else
    {
        /* No process */
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_Sub_sExecSwitchErasure                           */
/* Description   | Executing Switch Erasure                                 */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(void, MEM_CODE) CodeFls_Sub_sExecSwitchErasure(void)
{
    CodeFls_Drv_SetSwitchWriteData();
    CodeFls_Drv_SwitchWriteOp();
    CodeFls_stgMultiOpInfo.u1SVAStatus = CODEFLS_U1_SVA_SWITCH_WRITE;

    /* Set job management timer */
    CodeFls_Drv_GetCounterValue(&CodeFls_u4gJobTimer);
}

/****************************************************************************/
/* Function Name | CodeFls_Sub_sExecSwitchProgramming                       */
/* Description   | Executing Switch Programming                             */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | E_OK                    :                                */
/*               | E_NOT_OK                :                                */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(Std_ReturnType, MEM_CODE) CodeFls_Sub_sExecSwitchProgramming(void)
{
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;

    u1aRet = CodeFls_Drv_TagEraseOp();
    if( (Std_ReturnType)E_OK == u1aRet )
    {
        CodeFls_stgMultiOpInfo.u1SVAStatus = CODEFLS_U1_SVA_TAG_ERASE;

        /* Set job management timer */
        CodeFls_Drv_GetCounterValue(&CodeFls_u4gJobTimer);
    }
    else
    {
        /* No process */
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_Sub_sExecTagErasure                              */
/* Description   | Executing TAG Erasure                                    */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | E_OK                    :                                */
/*               | E_NOT_OK                :                                */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(Std_ReturnType, MEM_CODE) CodeFls_Sub_sExecTagErasure(void)
{
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;

    u1aRet = CodeFls_Drv_TagUpdateOp();
    if( (Std_ReturnType)E_OK == u1aRet )
    {
        CodeFls_stgMultiOpInfo.u1SVAStatus = CODEFLS_U1_SVA_TAG_UPDATE;

        /* Set job management timer */
        CodeFls_Drv_GetCounterValue(&CodeFls_u4gJobTimer);
    }
    else
    {
        /* No process */
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_Sub_sExecTagUpdate                               */
/* Description   | Executing TAG Update                                     */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | E_OK                    :                                */
/*               | E_NOT_OK                :                                */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(Std_ReturnType, MEM_CODE) CodeFls_Sub_sExecTagUpdate(void)
{
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;

    CodeFls_stgMultiOpInfo.u1SVAStatus = CODEFLS_U1_SVA_NONE;
    u1aRet = CodeFls_Drv_FinishSwitchValidArea();

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_Sub_sCheckAddress                                */
/* Description   | Check if the provided address and size fit within the    */
/*               | configured code flash region                             */
/*               | Return the index of the target code flash region         */
/*               | information setting table if the provided address and    */
/*               | size fit within the code flash region                    */
/* Preconditions | -                                                        */
/* Parameters    | [IN]u4Addr                 : Address                     */
/*               | [IN]u4Size                 : Size (Unit: Byte)           */
/* Return Value  | Index of Code Flash Region Information Setting Table     */
/*               | (CODEFLS_U1_INFONUM_0                                    */
/*               |   - Number of Entries in Code Flash Region Information   */
/*               |           Setting Table : Within Code Flash Region       */
/*               |  CODEFLS_U1_INFONUM_NONE: Outside Code Flash Region)     */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC(uint8, MEM_CODE) CodeFls_Sub_sCheckAddress
(
    VAR(uint32, AUTOMATIC) u4Addr,
    VAR(uint32, AUTOMATIC) u4Size
)
{
    VAR(uint8, AUTOMATIC) u1aRet;
    VAR(uint8, AUTOMATIC) u1aLoopCnt;
    VAR(uint32, AUTOMATIC) u4aEndAddr;

    u1aRet = CODEFLS_U1_INFONUM_NONE;       /* Outside the code flash area range */

    /* Check if the final address has overflowed */
    if( CODEFLS_U4_VAL_0 != u4Size )
    {
        if( u4Addr <= (CODEFLS_U4_VAL_MAX - (u4Size - CODEFLS_U4_VAL_1)) )
        {
            u4aEndAddr = u4Addr + (u4Size - CODEFLS_U4_VAL_1);
            for( u1aLoopCnt = CODEFLS_U1_INFONUM_0; u1aLoopCnt < CODEFLS_DEVCFG_DATA.CodeFlsSetting->CodeFlsInfoNum; u1aLoopCnt++ )
            {
                /* Verify whether the address and size (in bytes) specified by the arguments fit within the region specified in the configuration */
                if( (CODEFLS_DEVCFG_DATA.CodeFlsSetting->CodeFlsInfo[u1aLoopCnt].Addr <= u4Addr) &&
                    ((CODEFLS_DEVCFG_DATA.CodeFlsSetting->CodeFlsInfo[u1aLoopCnt].Addr + CODEFLS_DEVCFG_DATA.CodeFlsSetting->CodeFlsInfo[u1aLoopCnt].Size) > u4aEndAddr) )
                {
                    u1aRet = u1aLoopCnt;
                    break;
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

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_Sub_sCheckTopAddress                             */
/* Description   | Check if the given starting address fits within the      */
/*               | configured code flash region. If the provided starting   */
/*               | address is within the code flash region, return the      */
/*               | index of the target code flash region information        */
/*               | setting table.                                           */
/* Preconditions | -                                                        */
/* Parameters    | [IN]u4Addr                 : Address                     */
/* Return Value  | Index of Code Flash Region Information Setting Table     */
/*               | (CODEFLS_U1_INFONUM_0                                    */
/*               |   - Number of Entries in Code Flash Region Information   */
/*               |           Setting Table : Within Code Flash Region       */
/*               |  CODEFLS_U1_INFONUM_NONE: Outside Code Flash Region)     */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC(uint8, MEM_CODE) CodeFls_Sub_sCheckTopAddress
(
    VAR(uint32, AUTOMATIC) u4Addr
)
{
    VAR(uint8, AUTOMATIC) u1aRet;
    VAR(uint8, AUTOMATIC) u1aLoopCnt;

    u1aRet = CODEFLS_U1_INFONUM_NONE;       /* Outside the code flash area range */

    for( u1aLoopCnt = CODEFLS_U1_INFONUM_0; u1aLoopCnt < CODEFLS_DEVCFG_DATA.CodeFlsSetting->CodeFlsInfoNum; u1aLoopCnt++ )
    {
        /* Verify whether the address specified by the arguments fit within the region specified in the configuration */
        if( (CODEFLS_DEVCFG_DATA.CodeFlsSetting->CodeFlsInfo[u1aLoopCnt].Addr <= u4Addr) &&
            ((CODEFLS_DEVCFG_DATA.CodeFlsSetting->CodeFlsInfo[u1aLoopCnt].Addr + CODEFLS_DEVCFG_DATA.CodeFlsSetting->CodeFlsInfo[u1aLoopCnt].Size) > u4Addr) )
        {
            u1aRet = u1aLoopCnt;
            break;
        }
        else
        {
            /* No process */
        }
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_Sub_sCheckEndAddress                             */
/* Description   | Check if the end address calculated from the provided    */
/*               | address and size fits within the configured code flash   */
/*               | region. If the calculated end address is within the      */
/*               | code flash region, return the index of the target        */
/*               | code flash region information setting table.             */
/* Preconditions | -                                                        */
/* Parameters    | [IN]u4Addr                 : Address                     */
/*               | [IN]u4Size                 : Size (Unit: Byte)           */
/* Return Value  | Index of Code Flash Region Information Setting Table     */
/*               | (CODEFLS_U1_INFONUM_0                                    */
/*               |   - Number of Entries in Code Flash Region Information   */
/*               |           Setting Table : Within Code Flash Region       */
/*               |  CODEFLS_U1_INFONUM_NONE: Outside Code Flash Region)     */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC(uint8, MEM_CODE) CodeFls_Sub_sCheckEndAddress
(
    VAR(uint32, AUTOMATIC) u4Addr,
    VAR(uint32, AUTOMATIC) u4Size
)
{
    VAR(uint8, AUTOMATIC) u1aRet;
    VAR(uint8, AUTOMATIC) u1aLoopCnt;
    VAR(uint32, AUTOMATIC) u4aEndAddr;

    u1aRet = CODEFLS_U1_INFONUM_NONE;       /* Outside the code flash area range */

    /* Check if the final address has overflowed */
    if( CODEFLS_U4_VAL_0 != u4Size )
    {
        if( u4Addr <= (CODEFLS_U4_VAL_MAX - (u4Size - CODEFLS_U4_VAL_1)) )
        {
            u4aEndAddr = u4Addr + (u4Size - CODEFLS_U4_VAL_1);
            for( u1aLoopCnt = CODEFLS_U1_INFONUM_0; u1aLoopCnt < CODEFLS_DEVCFG_DATA.CodeFlsSetting->CodeFlsInfoNum; u1aLoopCnt++ )
            {
                /* Verify if the end address calculated from the address and size (in bytes) specified */
                /* by the arguments fits within the region specified in the configuration. */
                if( (CODEFLS_DEVCFG_DATA.CodeFlsSetting->CodeFlsInfo[u1aLoopCnt].Addr <= u4aEndAddr) &&
                    ((CODEFLS_DEVCFG_DATA.CodeFlsSetting->CodeFlsInfo[u1aLoopCnt].Addr + CODEFLS_DEVCFG_DATA.CodeFlsSetting->CodeFlsInfo[u1aLoopCnt].Size) > u4aEndAddr) )
                {
                    u1aRet = u1aLoopCnt;
                    break;
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

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_Sub_CheckInvalidArea_InfoNum                     */
/* Description   | Verifies that the invalid area of the flash memory is    */
/*                 specified.                                               */
/* Preconditions | -                                                        */
/* Parameters    | [IN]u1aInfoNum  :Index of Code Flash Region Information  */
/*               |                  Setting Table                           */
/* Return Value  | E_OK           : Successful completion                   */
/*               | E_NOT_OK       : Failed                                  */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(uint8, MEM_CODE) CodeFls_Sub_CheckInvalidArea_InfoNum
(
    VAR(uint8, AUTOMATIC) u1aInfoNum
)
{
    VAR(uint8, AUTOMATIC) u1aMapMode;
    VAR(uint8, AUTOMATIC) u1aRet;

    u1aRet = E_NOT_OK;

    if( CODEFLS_U1_INFONUM_NONE != u1aInfoNum )
    {
        u1aMapMode = CodeFls_Drv_GetMapMode();
        if( CODEFLS_U1_MAPMODE_DOUBLE == u1aMapMode )
        {
            if( CODEFLS_PRODUCT_U2A16 == CODEFLS_DEVCFG_DATA.ProductSetting->ProductType )
            {
                if( CODEFLS_U1_VAL_2 == u1aInfoNum )
                {
                    u1aRet = E_OK;
                }
                else if( CODEFLS_U1_VAL_3 == u1aInfoNum )
                {
                    u1aRet = E_OK;
                }
                else
                {
                    /* No process */
                }
            }
            else
            {
                if( CODEFLS_U1_VAL_1 == u1aInfoNum )
                {
                    u1aRet = E_OK;
                }
            }
        }
        else
        {
            /* Single map is allowed */
            u1aRet = E_OK;
        }
    }

    return(u1aRet);
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
