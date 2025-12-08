/* Fee_Dfc.c v2-1-0                                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/DFC/CODE                                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Fee.h>

#include "../inc/Fee_Common.h"

#include "../inc/Fee_Dfc.h"
#include "../inc/Fee_Dfc_Internal.h"
#include "../inc/Fee_Dfc_Ram.h"
#include "../inc/Fee_DfcMpu.h"

#include <Fls.h>
#include <Mscd_Common.h>

#include "../inc/Fee_ExConst.h"

#include "../inc/Fee_Mpu_Dev_Const.h"
#include "../inc/Fee_Lib.h"
#include "../inc/Fee_Legacy.h"
#include "../inc/Fee_FlsWrp.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Return Values and Hook Result */
#define FEE_DFC_RSP_OK                      ((uint8)0x00)   /* Success         */
#define FEE_DFC_RSP_NG_PARAM_ERROR          ((uint8)0x81)   /* Parameter error */
#define FEE_DFC_RSP_NG_DECLINE              ((uint8)0x82)   /* Request reject  */
#define FEE_DFC_RSP_NG_BUSY                 ((uint8)0x83)   /* Failure(busy)   */
#define FEE_DFC_RSP_NG_HARD_ERROR           ((uint8)0x84)   /* Hard error      */
#define FEE_DFC_RSP_NG_RAM_ERROR            ((uint8)0x85)   /* RAM error       */
#define FEE_DFC_RSP_NG_BLANK_ERROR          ((uint8)0x86)   /* Blank error     */

/* Data Flash base address */
#define FEE_DFC_BASEADDRESS     FEE_DATA_FLASH_ADDRESS_START

/* Erase unit size */
#define FEE_DFC_DEFAULT_ERASE_SIZE      (FEE_DATA_FLASH_SECTOR_SIZE)

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* Function Name | Fee_Dfc_CheckRAM                                         */
/* Description   | Function to check RAMs.                                  */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Check result.                                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, FEE_CODE )
Fee_Dfc_CheckRAM( void )
{
#if ( FEE_USE_REDUNDANCY_RAM == STD_ON )
    Std_ReturnType Rtn = E_NOT_OK;

    if((( Fee_DrvWrap_State            ^ Fee_DrvWrap_StateSub            ) == (uint32)FEE_MIRROR_CHECK_UINT32 )
    && (( Fee_DrvWrap_WrittenAdr       ^ Fee_DrvWrap_WrittenAdrSub       ) == (uint32)FEE_MIRROR_CHECK_UINT32 )
    && (( Fee_Dfc_BlankCheckEndAdr     ^ Fee_Dfc_BlankCheckEndAdrSub     ) == (uint32)FEE_MIRROR_CHECK_UINT32 )
    && (( Fee_Dfc_MaxBlankCheckNum     ^ Fee_Dfc_MaxBlankCheckNumSub     ) == (uint32)FEE_MIRROR_CHECK_UINT32 )
    && (( Fee_DrvWrap_BlankCheck_State ^ Fee_DrvWrap_BlankCheck_StateSub ) == (uint32)FEE_MIRROR_CHECK_UINT32 ))
    {
        Rtn = E_OK;
    }

    return Rtn;
#else /* FEE_USE_REDUNDANCY_RAM == STD_OFF */
    return E_OK;
#endif /* FEE_USE_REDUNDANCY_RAM */
}

/****************************************************************************/
/* Function Name | Fee_Dfc_SetRAMSub                                        */
/* Description   | Function to set value to sub RAMs from main RAMs.        */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Dfc_SetRAMSub( void )
{
#if ( FEE_USE_REDUNDANCY_RAM == STD_ON )
    Fee_DrvWrap_StateSub            = (uint32)(~Fee_DrvWrap_State);
    Fee_DrvWrap_WrittenAdrSub       = (uint32)(~Fee_DrvWrap_WrittenAdr);
    Fee_Dfc_BlankCheckEndAdrSub     = (uint32)(~Fee_Dfc_BlankCheckEndAdr);
    Fee_Dfc_MaxBlankCheckNumSub     = (uint32)(~Fee_Dfc_MaxBlankCheckNum);
    Fee_DrvWrap_BlankCheck_StateSub = (uint32)(~Fee_DrvWrap_BlankCheck_State);
#endif /* FEE_USE_REDUNDANCY_RAM == STD_ON */

    return;
}

/****************************************************************************/
/* Function Name | Fee_Dfc_Write                                            */
/* Description   | Write data requested from DTF to data Flash.             */
/* Preconditions | None                                                     */
/* Parameters    | const uint 32 Address : Address to write data to         */
/*               | const uint 32 Data    : Data written to data Flash       */
/*               | const uint16 DataLen  : Write Data Length                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, FEE_CODE) Fee_Dfc_Write(const uint32 Address, P2CONST(uint8, AUTOMATIC, TYPEDEF) ptu1Data, const uint16 u2Len)
{
    Std_ReturnType ret;

    /* Send a write request to FLS */
    ret = Fee_FlsWrp_Write((Address - (Fls_AddressType)FEE_DFC_BASEADDRESS), ptu1Data, (Fls_LengthType)u2Len);

    if( ret == (Std_ReturnType)E_OK )
    {
        Fee_CpuDtfInfo.u4DFCTimerCnt = Fee_HwLmtWriteTime;
    }

    /* Convert the FLS response into the response expected by the upper layer and save it */
    Fee_DrvWrap_ConvDrvReqResult(ret);

    return;
}
/****************************************************************************/
/* Function Name | Fee_Dfc_Erase                                            */
/* Description   | Erase the contents of the block starting                 */
/*               | at the specified address                                 */
/* Preconditions | None                                                     */
/* Parameters    | const uint 32 Address: Address to start erasing          */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, FEE_CODE) Fee_Dfc_Erase(const uint32 Address)
{
    Std_ReturnType ret;

    /* Submit an erase request to FLS */
    ret = Fee_FlsWrp_Erase((Address - (Fls_AddressType)FEE_DFC_BASEADDRESS), (Fls_LengthType)FEE_DFC_DEFAULT_ERASE_SIZE);

    if( ret == (Std_ReturnType)E_OK )
    {
        Fee_CpuDtfInfo.u4DFCTimerCnt = Fee_HwlmtInitTime;
    }

    /* Save DTFD response as expected by upper layer */
    Fee_DrvWrap_ConvDrvReqResult(ret);

    return;
}
/****************************************************************************/
/* Function Name | Fee_Dfc_BlankCheck                                       */
/* Description   | Blank check block starting at specified address          */
/* Preconditions | None                                                     */
/* Parameters    | const uint 32 StartTailAddress: blank check              */
/*               |                                 start address            */
/*               | const uint 32 EndTopAddress   : blank check end address  */
/*               | uint32 MaxBlankCheckNum       : The number of blank      */
/*               |                                 check in one cycle.      */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Dfc_BlankCheck(
    const uint32 StartTailAddress,
    const uint32 EndTopAddress,
    uint32 MaxBlankCheckNum
){
    /* Set blank check state to "Running" */
    Fee_DrvWrap_BlankCheck_State = FEE_DFC_STATUS_BUSY;

    /* When starting a blank check, include the block trailing address in the blank check result (last write record address) */
    Fee_DrvWrap_WrittenAdr = StartTailAddress - (uint32)FEE_DATA_FLASH_ECC_FIX_SIZE;
    Fee_Dfc_BlankCheckEndAdr = EndTopAddress;
    Fee_Dfc_MaxBlankCheckNum = MaxBlankCheckNum;

    /* Perform blank check */
    Fee_DrvWrap_BlankCheck_Main();

    return;
}

#if ( MSCD_FREESPACE_USE == STD_ON )
/****************************************************************************/
/* Function Name | Fee_Dfc_GetBlankCheckResult                              */
/* Description   | Function to get blank check result.                      */
/* Preconditions | None                                                     */
/* Parameters    | WriteAddr : The flash address that is not a blank.       */
/* Return Value  | FEE_DFC_STATUS_OK                                        */
/*               | FEE_DFC_STATUS_ERROR                                     */
/*               | FEE_DFC_STATUS_BUSY                                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Dfc_GetBlankCheckResult(
    P2VAR( uint32, AUTOMATIC, TYPEDEF ) WriteAddr
){
    uint32 Rtn = Fee_DrvWrap_BlankCheck_State;

    if( Rtn == FEE_DFC_STATUS_ERROR )
    {
        *WriteAddr = Fee_DrvWrap_WrittenAdr;
    }

    return Rtn;
}
#endif /*( MSCD_FREESPACE_USE == STD_ON )*/

/****************************************************************************/
/* Function Name | Fee_Dfc_ExecBlankCheck                                   */
/* Description   | Blank check block starting at specified address          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | uint 32: Data Flash operation confirmation result        */
/*               |   FEE _ DFC _ STATUS _ OK Full space blank               */
/*               |   FEE _ DFC _ STATUS _ ERROR There is non-blank space    */
/*               |   FEE _ DFC _ STATUS _ BUSY Blank checking               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint32 ,FEE_CODE )
Fee_Dfc_ExecBlankCheck( void )
{
    if( Fee_DrvWrap_BlankCheck_State == FEE_DFC_STATUS_BUSY )
    {
        /* Perform blank check */
        Fee_DrvWrap_BlankCheck_Main();
    }

    return Fee_DrvWrap_BlankCheck_State;
}

/****************************************************************************/
/* Function Name | Fee_DrvWrap_BlankCheck_Main                              */
/* Description   | Blank check block starting at specified address          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void , FEE_CODE) Fee_DrvWrap_BlankCheck_Main(void)
{
    uint8  DfcMpuResult;
    uint32 NotBlankAddress;
    uint32 BlankCheckStartAdr;
    uint32 BlankCheckEndAdr;
    uint32 BlankCheckLength;
    uint32 MaxLength;
    uint32 MaxBlankCheckNum = Fee_Dfc_MaxBlankCheckNum;

    if( MaxBlankCheckNum > (uint32)FEE_BLANKCHECK_COUNT_ZERO )
    {
        BlankCheckStartAdr = Fee_DrvWrap_WrittenAdr + (uint32)FEE_DATA_FLASH_ECC_FIX_SIZE;
        BlankCheckEndAdr = Fee_Dfc_BlankCheckEndAdr;
        NotBlankAddress = BlankCheckStartAdr;

        /* Set length of blank check. */
        MaxLength = MaxBlankCheckNum * (uint32)FEE_DATA_FLASH_ECC_FIX_SIZE;
        BlankCheckLength = BlankCheckStartAdr - BlankCheckEndAdr;
        if( BlankCheckLength > MaxLength )
        {
            BlankCheckLength = MaxLength;
        }

        /* Execute blank check. */
        DfcMpuResult = Fee_DfcMpu_SyncNotBlankAddress( ( BlankCheckStartAdr - BlankCheckLength ), BlankCheckLength, &NotBlankAddress );
        if( DfcMpuResult == FEE_DFCMPU_RESULT_OK )
        {
            /* Set last written position. */
            Fee_DrvWrap_WrittenAdr = NotBlankAddress - ( NotBlankAddress % (uint32)FEE_DATA_FLASH_ECC_FIX_SIZE );
            Fee_DrvWrap_BlankCheck_State = FEE_DFC_STATUS_ERROR;
        }
        else if( DfcMpuResult == FEE_DFCMPU_RESULT_BLANK )
        {
            /* Update search address. */
            Fee_DrvWrap_WrittenAdr -= BlankCheckLength;
            if( Fee_DrvWrap_WrittenAdr < BlankCheckEndAdr )
            {
                /* In case of whole target area is blank. */
                Fee_DrvWrap_BlankCheck_State = FEE_DFC_STATUS_OK;
            }
        }
        else
        {
            /* Assume that last written position is found. */
            Fee_DrvWrap_BlankCheck_State = FEE_DFC_STATUS_ERROR;
        }
    }

    return;
}
/****************************************************************************/
/* Function Name | Fee_Dfc_ExecFlsMainFunction                              */
/* Description   | Run the Data Flash Driver, and return the results.       */
/* Preconditions | None                                                     */
/* Parameters    | u1_callmode : type of periodic process                   */
/* Return Value  | Result of running Data Flash                             */
/*               |  FEE_DFC_STATUS_OK    Processing Success                 */
/*               |  FEE_DFC_STATUS_ERROR Error Occurred                     */
/*               |  FEE_DFC_STATUS_BUSY  Continue Processing                */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_Dfc_ExecFlsMainFunction( uint8 u1_callmode )
{
    uint32 ret;
    MemIf_JobResultType FlsJobResult;
    uint32 drvwrap_state_current = Fee_DrvWrap_State;

    Fee_FlsWrp_MainFunction( u1_callmode );

    FlsJobResult = Fee_FlsWrp_GetJobResult();

    if( drvwrap_state_current == FEE_DFC_STATUS_OK ){
        Fee_DrvWrap_State = FEE_DFC_STATUS_OK;
    }
    else if( drvwrap_state_current == FEE_DFC_STATUS_BUSY )
    {
        switch( FlsJobResult ){
            case MEMIF_JOB_OK:
                Fee_DrvWrap_State = FEE_DFC_STATUS_OK;
                break;
            case MEMIF_JOB_PENDING:
                Fee_DrvWrap_State = FEE_DFC_STATUS_BUSY;
                break;
            default:
                Fee_DrvWrap_State = FEE_DFC_STATUS_ERROR;
                break;
        }
    }
    else{
        Fee_DrvWrap_State = FEE_DFC_STATUS_ERROR;
    }

    if( FlsJobResult == MEMIF_JOB_PENDING )
    {
        ret = FEE_DFC_STATUS_BUSY;
    }
    else
    {
        ret = Fee_DrvWrap_State;
        Fee_CpuDtfInfo.u4DFCTimerCnt = FEE_TM_INVALID;
    }

    return (ret);
}

/****************************************************************************/
/* Function Name | Fee_Dfc_End                                              */
/* Description   | End flash operation                                      */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, FEE_CODE) Fee_Dfc_End(void)
{
    /* Initialize RAM for bonding layer */
    Fee_DrvWrap_Init();

    return;
}

/****************************************************************************/
/* Function Name | Fee_Dfc_Cancel                                           */
/* Description   | Function to initialize under module.                     */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Dfc_Init( void )
{
    /* Do Nothing */
    return;
}

/****************************************************************************/
/* Function Name | Fee_Dfc_Cancel                                           */
/* Description   | Function to cancel under module.                         */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Dfc_Cancel( void )
{
    Fee_FlsWrp_Cancel();

    return;
}

/****************************************************************************/
/* Function Name | Fee_Dfc_GetFLAP                                          */
/* Description   | Return addresses found by blank check that are not blank */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | U4: address where not blank                              */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_Dfc_GetFLAP(void)
{
    /* returns the first address of the last saved write record */
    return (Fee_DrvWrap_WrittenAdr);
}

/****************************************************************************/
/* Function Name | Fee_Dfc_GetStatus                                        */
/* Description   | Function to return the Fls module status.                */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Fls module status                                        */
/*               |  MEMIF_IDLE          :The Fls module is currently idle.  */
/*               |  MEMIF_BUSY          :The Fls module is currently busy.  */
/*               |  MEMIF_UNINIT        :The Fls module has not been        */
/*               |                       initialized (yet).                 */
/*               |  MEMIF_BUSY_INTERNAL :A fatal error has occured.         */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( MemIf_StatusType, FEE_CODE ) Fee_Dfc_GetStatus(void)
{
    MemIf_StatusType FlsStatus;

    FlsStatus = Fee_FlsWrp_GetStatus();

    return (FlsStatus);
}

/****************************************************************************/
/* Function Name | Fee_DrvWrap_ConvDrvReqResult                             */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | result                                                   */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC(void, FEE_CODE) Fee_DrvWrap_ConvDrvReqResult(
    const Std_ReturnType result
){
    uint32 drvwrap_state_new;

    switch(result){
        /* Returns "Process Continued" if "Process Succeeded" */
        case E_OK:
            drvwrap_state_new = FEE_DFC_STATUS_BUSY;
            break;

        /* Returns "Error occurred" for "Request denied," "Parameter error" and "Other (abnormal)" */
        default:
            drvwrap_state_new = FEE_DFC_STATUS_ERROR;
            break;
    }

    Fee_DrvWrap_State = drvwrap_state_new;

    return;
}

/****************************************************************************/
/* Function Name | Fee_DrvWrap_Init                                         */
/* Description   | Clear RAM in bonding layer                               */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, FEE_CODE) Fee_DrvWrap_Init(void)
{
    Fee_DrvWrap_State = FEE_DFC_STATUS_OK;
    Fee_DrvWrap_WrittenAdr          = FEE_DFC_ADDRESS_INVALID;
    Fee_Dfc_BlankCheckEndAdr        = FEE_DFC_ADDRESS_INVALID;
    Fee_Dfc_MaxBlankCheckNum        = FEE_BLANKCHECK_COUNT_ZERO;
    Fee_DrvWrap_BlankCheck_State    = FEE_DFC_STATUS_OK;

    return;
}

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  1-1-0          :2019/08/19                                              */
/*  2-0-0          :2022/08/24                                              */
/*  2-1-0          :2024/09/04                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
