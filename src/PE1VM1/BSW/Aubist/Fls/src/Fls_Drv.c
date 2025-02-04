/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Fls/Drv/CODE                                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../inc/Fls_Sfr.h"
#include "../inc/Fls_Mpu.h"
#include "../inc/Fls_Cdd_Mpu.h"
#include "../inc/Fls_Drv.h"
#include "../usr/Fls_Callout.h"
#include <Fls.h>
#include <Fls_Cdd.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

#define FLS_START_SEC_CODE
#include <Fls_MemMap.h>
FLS_DRV_STATIC FUNC( uint8, FLS_CODE ) Fls_Drv_ReadMemoryU08(uint32 u4_add);
FLS_DRV_STATIC FUNC( uint16, FLS_CODE ) Fls_Drv_ReadMemoryU16(uint32 u4_add);
FLS_DRV_STATIC FUNC( uint32, FLS_CODE ) Fls_Drv_ReadMemoryU32(uint32 u4_add);
FLS_DRV_STATIC FUNC( void, FLS_CODE ) Fls_Drv_WriteMemoryU08(uint32 u4_add, uint8  u1_val);
FLS_DRV_STATIC FUNC( void, FLS_CODE ) Fls_Drv_WriteMemoryU16(uint32 u4_add, uint16 u2_val);
FLS_DRV_STATIC FUNC( void, FLS_CODE ) Fls_Drv_WriteMemoryU32(uint32 u4_add, uint32 u4_val);

FLS_DRV_STATIC FUNC( Fls_StatusType, FLS_CODE ) Fls_Drv_ForcedStop(uint8 u1_area);
FLS_DRV_STATIC FUNC( void, FLS_CODE ) Fls_Drv_ClearStatus(uint8 u1_area);

FLS_DRV_STATIC FUNC( Fls_FlagType, FLS_CODE ) Fls_Drv_OperationCheck(P2VAR( Fls_StatusType, AUTOMATIC, TYPEDEF ) pt_stat, uint8 u1_area);

FLS_DRV_STATIC FUNC( Fls_FlagType, FLS_CODE ) Fls_Drv_ChkReady(uint8 u1_area);

FLS_DRV_STATIC FUNC( Fls_FlagType, FLS_CODE ) Fls_Drv_ReactOnFatalErrors(P2VAR( Fls_StatusType, AUTOMATIC, TYPEDEF ) pt_stat, uint8 u1_area);
FLS_DRV_STATIC FUNC( Fls_StatusType, FLS_CODE ) Fls_Drv_GetStat(uint8 u1_area);
FLS_DRV_STATIC FUNC( Fls_StatusType, FLS_CODE ) Fls_Drv_CheckFatalError(uint8 u1_area);
FLS_DRV_STATIC FUNC( Fls_StatusType, FLS_CODE ) Fls_Drv_ChkAccessRight(uint8 u1_area);


#define FLS_STOP_SEC_CODE
#include <Fls_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define FLS_START_SEC_CONST_32
#include <Fls_MemMap.h>

FLS_DRV_STATIC CONST(AB_83_ConstV FLS_DRV_REGADDFCI_T, FLS_CONST) Fls_RegAdd_Fci[FLS_DRV_U1_FCU_MAX] =
{
    {
        FLS_DRV_U4_REGADD_FASTAT_0,    /* Flash Access Status Register( for data area 0) */
        FLS_DRV_U4_REGADD_FAEINT_0,    /* Flash Access Error Interrupt Enable Register( for data area 0) */
        FLS_DRV_U4_REGADD_FSADR_0,     /* FACI Command Start Address Register( for data area 0) */
        FLS_DRV_U4_REGADD_FEADR_0,     /* FACI Command End Address Register( for data area 0)*/
        FLS_DRV_U4_REGADD_FSTATR_0,    /* Flash Status Register ( for data area 0)*/
        FLS_DRV_U4_REGADD_FENTRYR_0,   /* Flash P/E Mode Entry Register */
        FLS_DRV_U4_REGADD_FSUINITR_0,  /* Flash Sequencer Set-Up Initialize Register */
        FLS_DRV_U4_REGADD_FBCCNT_0,    /* Data Flash Blank Check Control RegisterData Flash */
#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A8 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A16 )
        FLS_DRV_U4_REGADD_FCPSR_0,     /* Flash Sequencer Process Switch Register */
#endif
        FLS_DRV_U4_REGADD_FBCSTAT_0,   /* Data Flash Blank Check Status Register */
        FLS_DRV_U4_REGADD_FECCTMD_0,   /* Flash ECC Test Mode Register */
        FLS_DRV_U4_REGADD_FHVE3FP0,    /* FHVE3 Control Register ( for data area 0)*/
        FLS_DRV_U4_REGADD_FHVE15FP0,   /* FHVE15 Control Register( for data area 0) */
        FLS_DRV_U4_DFLASH_CMD_ADD_0    /* FACI 0 command issue area */
    },
#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A8 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A16 )
    {
        FLS_DRV_U4_REGADD_FASTAT_1,    /* Flash Access Status Register( for data area 1) */
        FLS_DRV_U4_REGADD_FAEINT_1,    /* Flash Access Error Interrupt Enable Register( for data area 1) */
        FLS_DRV_U4_REGADD_FSADR_1,     /* FACI Command Start Address Register( for data area 1) */
        FLS_DRV_U4_REGADD_FEADR_1,     /* FACI Command End Address Register( for data area 1)*/
        FLS_DRV_U4_REGADD_FSTATR_1,    /* Flash Status Register ( for data area 1)*/
        FLS_DRV_U4_REGADD_FENTRYR_1,   /* Flash P/E Mode Entry Register */
        FLS_DRV_U4_REGADD_FSUINITR_1,  /* Flash Sequencer Set-Up Initialize Register */
        FLS_DRV_U4_REGADD_FBCCNT_1,    /* Data Flash Blank Check Control RegisterData Flash */
        FLS_DRV_U4_REGADD_FCPSR_1,     /* Flash Sequencer Process Switch Register */
        FLS_DRV_U4_REGADD_FBCSTAT_1,   /* Data Flash Blank Check Status Register */
        FLS_DRV_U4_REGADD_FECCTMD_1,   /* Flash ECC Test Mode Register */
        FLS_DRV_U4_REGADD_FHVE3FP1,    /* FHVE3 Control Register ( for data area 1)*/
        FLS_DRV_U4_REGADD_FHVE15FP1,   /* FHVE15 Control Register( for data area 1) */
        FLS_DRV_U4_DFLASH_CMD_ADD_1    /* FACI 1 command issue area */
    }
#endif
};

#define FLS_STOP_SEC_CONST_32
#include <Fls_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define FLS_START_SEC_CODE
#include <Fls_MemMap.h>
/*****************************************************************************
   Function      : Read Data Function (8-bit data)
   Description   : This function reads the data(8-bit) from the specified address.
   param[in]     : u4_add                          (Read-target address)
   return        :  *( (volatile uint8 *)(add) )   (Read data)
   Note          : -
*****************************************************************************/
FLS_DRV_STATIC FUNC( uint8, FLS_CODE )  
Fls_Drv_ReadMemoryU08(uint32 u4_add)
{
    /* MISRA DEVIATION                                                */
    /* Volatile is required to directly access the address determined */
    /* by the hardware specification.                                 */
    return(*((volatile uint8 *)(u4_add)));

} /* Fls_Drv_ReadMemoryU08 */

/*****************************************************************************
   Function      : Read Data Function (16-bit data)
   Description   : This function reads the data(16-bit) from the specified address.
   param[in]     : u4_add                          (Read-target address)
   return        :  *( (volatile uint16 *)(add) )  (Read data)
   Note          : -
*****************************************************************************/
FLS_DRV_STATIC FUNC( uint16, FLS_CODE )  
Fls_Drv_ReadMemoryU16(uint32 u4_add)
{
    /* MISRA DEVIATION                                                */
    /* Volatile is required to directly access the address determined */
    /* by the hardware specification.                                 */
    return (*((volatile uint16 *)(u4_add)));

} /* Fls_Drv_ReadMemoryU16 */

/*****************************************************************************
   Function      : Read Data Function (32-bit data)
   Description   : This function reads the data(32-bit) from the specified address.
   param[in]     : u4_add                          (Read-target address)
   return        :  *( (volatile uint32 *)(add) )  (Read data)
   Note          : -
*****************************************************************************/
FLS_DRV_STATIC FUNC( uint32, FLS_CODE )  
Fls_Drv_ReadMemoryU32(uint32 u4_add)
{
    /* MISRA DEVIATION                                                */
    /* Volatile is required to directly access the address determined */
    /* by the hardware specification.                                 */
    return (*((volatile uint32 *)(u4_add)));

} /* Fls_Drv_ReadMemoryU32 */

/*****************************************************************************
   Function      : Write Data Function (8-bit data)
   Description   : This function writes the data(8-bit) to the specified address.
   param[in]     : u4_add  (Write-target address)
   param[in]     : u1_val  (Write data)
   return        : -
   Note          : -
*****************************************************************************/
FLS_DRV_STATIC FUNC( void, FLS_CODE ) 
Fls_Drv_WriteMemoryU08(uint32 u4_add, uint8 u1_val)
{
    /* MISRA DEVIATION                                                */
    /* Volatile is required to directly access the address determined */
    /* by the hardware specification.                                 */
    (*((volatile uint8 *)(u4_add))) = u1_val;

} /* Fls_Drv_WriteMemoryU08 */

/*****************************************************************************
   Function      : Write Data Function (16-bit data)
   Description   : This function writes the data(16-bit) to the specified address.
   param[in]     : u4_add  (Write-target address)
   param[in]     : u2_val  (Write data)
   return        : -
   Note          : -
*****************************************************************************/
FLS_DRV_STATIC FUNC( void, FLS_CODE ) 
Fls_Drv_WriteMemoryU16(uint32 u4_add, uint16 u2_val)
{
    /* MISRA DEVIATION                                                */
    /* Volatile is required to directly access the address determined */
    /* by the hardware specification.                                 */
    (*((volatile uint16 *)(u4_add))) = u2_val;

} /* Fls_Drv_WriteMemoryU16 */

/*****************************************************************************
   Function      : Write Data Function (32-bit data)
   Description   : This function writes the data(32-bit) to the specified address.
   param[in]     : u4_add (Write-target address)
   param[in]     : u4_val (Write data)
   return        : -
   Note          : -
*****************************************************************************/
FLS_DRV_STATIC FUNC( void, FLS_CODE ) 
Fls_Drv_WriteMemoryU32(uint32 u4_add, uint32 u4_val)
{
    /* MISRA DEVIATION                                                */
    /* Volatile is required to directly access the address determined */
    /* by the hardware specification.                                 */
    (*((volatile uint32 *)(u4_add))) = u4_val;

} /* Fls_Drv_WriteMemoryU32 */

/*****************************************************************************
   Function      : Internal Variable Initialization Function
   Description   : This function initializes the internal infomation(global variables) 
                    which are used by Data Flash Driver.
   param         : -
   return        : -
   Note          : -
*****************************************************************************/
FUNC( void, FLS_CODE ) 
Fls_Drv_InitVariables(void)
{
    /* clear operation information */
    Fls_Drv_ClearOperationInfo();

    /* set FLS internal state to IDLE */
    Fls_Str.stiStat_enu = MEMIF_IDLE;

    /* set FLS job result to job failed */
    Fls_Str.stiJobResult_enu = MEMIF_JOB_FAILED;

} /* Fls_Drv_InitVariables */

/*****************************************************************************
   Function      : Clear Operations Information Function
   Description   : This function clears the members of the operation information.
   param         : u1_area (target area)
   return        : -
   Note          : -
*****************************************************************************/
FUNC( void, FLS_CODE ) 
Fls_Drv_ClearOperationInfo(void)
{
    uint32 u4_AreaLoopCnt;   /* area loop counter */

#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2B6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2B10 )
    u4_AreaLoopCnt = FLS_DRV_U4_VAL_0;
#endif

#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A8 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A16 )
    for( u4_AreaLoopCnt = FLS_DRV_U4_VAL_0; u4_AreaLoopCnt < FLS_DRV_U1_FCU_MAX; u4_AreaLoopCnt++ )
    {
#endif
        /* clear operation information for data area */
        Fls_Str.stMulOp_str[u4_AreaLoopCnt].ptBufAdd       = NULL_PTR;                /* address                */
        Fls_Str.stMulOp_str[u4_AreaLoopCnt].u4FlashAdd     = FLS_DRV_U4_VAL_0;        /* start address of Flash */
        Fls_Str.stMulOp_str[u4_AreaLoopCnt].u4FlashAddEnd  = FLS_DRV_U4_VAL_0;        /* last address of Flash  */
        Fls_Str.stMulOp_str[u4_AreaLoopCnt].stCommand_enu  = FLS_DRV_U1_CMDTYPE_NONE; /* command                */
        Fls_Str.stMulOp_str[u4_AreaLoopCnt].stStatus       = FLS_DRV_U1_OK;           /* Command Status         */
#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A8 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A16 )
    }
#endif

} /* Fls_Drv_ClearOperationInfo */

/*****************************************************************************
   Function      : Initialize Register Function
   Description   : This function performs the initialization settings of the register.
   param         : u1_area (target area)
   return        : -
   Note          : -
*****************************************************************************/
FUNC( void, FLS_CODE ) 
Fls_Drv_InitRegister(uint8 u1_area)
{
    /* initialize Flash Access Error Interrupt Enable Register(FAEINT) (interrupt unauthorized) */
    Fls_Drv_WriteMemoryU08(Fls_RegAdd_Fci[u1_area].u4RegAddFAEINT, FLS_DRV_U1_REGBIT_FAEINT_RESET);

    /* initialize Flash Sequencer Set-up Initialize Register(FSUINITR) (keep the value of setting register) */
    Fls_Drv_WriteMemoryU16(Fls_RegAdd_Fci[u1_area].u4RegAddFSUINITR, 
                            FLS_DRV_U2_REGBIT_FSUINITR_OFF + FLS_DRV_U2_REGBIT_FSUINITR_KEY);

    /* initialize FHVE15 Control Register and FHVE3 Control Register(FHVE15/FHVE3)*/
    Fls_Drv_SetProtect(FLS_DRV_U4_PROTECT_MODE_ON, u1_area);


} /* Fls_Drv_InitRegister */

/*****************************************************************************
   Function      : Register Re-setting Function
   Description   : This function performs the re-setting of the register.
   param         : u1_area (target area)
   return        : -
   Note          : -
*****************************************************************************/
FUNC( void, FLS_CODE ) 
Fls_Drv_ResetRegister(uint8 u1_area)
{

    /* initialize Flash Sequencer Set-Up Initialize Register(FSUINITR) (keep the value of setting register) */
    Fls_Drv_WriteMemoryU16(Fls_RegAdd_Fci[u1_area].u4RegAddFSUINITR,
                            FLS_DRV_U2_REGBIT_FSUINITR_OFF + FLS_DRV_U2_REGBIT_FSUINITR_KEY);

    /* initialize Flash ECC Test Mode Register(FECCTMD) */
    Fls_Drv_WriteMemoryU16(Fls_RegAdd_Fci[u1_area].u4RegAddFECCTMD,
                            FLS_DRV_U2_REGBIT_FECCTMD_RESET + FLS_DRV_U2_REGBIT_FECCTMD_KEY);

} /* Fls_Drv_ResetRegister */

/*****************************************************************************
   Function      : Flash Sequencer Set-up Initialize Register(FSUINITR)
                    Initialization Function
   Description   : This function sets an initial value to Flash Sequencer Set-up
                    Initialize Register(FSUINITR).
   param         : u1_area (target area)
   return        : -
   Note          : -
*****************************************************************************/
FUNC( void, FLS_CODE ) 
Fls_Drv_ResetInitr(uint8 u1_area)
{
    Fls_FlagType    st_contHdrFct;

    st_contHdrFct = Fls_Drv_ChkReady(u1_area);

    if( FLS_DRV_U1_TRUE == st_contHdrFct )
    {
        Fls_Drv_WriteMemoryU16(Fls_RegAdd_Fci[u1_area].u4RegAddFSUINITR,
                                FLS_DRV_U2_REGBIT_FSUINITR_OFF + FLS_DRV_U2_REGBIT_FSUINITR_KEY);

    }
}

/*****************************************************************************
   Function      : Enable/Disable Protect Function
   Description   : This function enables/disables protection via the
                    FHVE3 and FHVE15 Control Register.
   param         : u4_mode (protect mode specified)
                   u1_area (target area)
   return        : -
   Note          : -
*****************************************************************************/
FUNC( void, FLS_CODE ) 
Fls_Drv_SetProtect(uint32 u4_mode, uint8 u1_area)
{
    /* Set data area 0*/
    /* set the FHVE15 Control Register to enabled/disabled */
    Fls_Drv_WriteMemoryU32(Fls_RegAdd_Fci[u1_area].u4RegAddFHVE15, u4_mode);

    /* set the FHVE3 Control Register to enabled/disabled */
    Fls_Drv_WriteMemoryU32(Fls_RegAdd_Fci[u1_area].u4RegAddFHVE3, u4_mode);

    /* Dummy read */
    (void)Fls_Drv_ReadMemoryU32(Fls_RegAdd_Fci[u1_area].u4RegAddFHVE3);

    /* SYNCP */
    Fls_Drv_Syncp_Asm();
 
} /* Fls_Drv_SetProtect */

/*****************************************************************************
   Function      : Reset Function
   Description   : This function stops any ongoing jobs and resets various registers.
   param         : u1_area (target area)
   return        : FLS_DRV_U1_OK             (Normal end)
                 : FLS_DRV_U1_ERR_INTERNAL   (Internal error)
                 : FLS_DRV_U1_ERR_TIMEOUT    (Timeout error)
                 : FLS_DRV_U1_ERR_ICU        (Execution during ICU operation)
   Note          : -
*****************************************************************************/
FUNC( Fls_StatusType, FLS_CODE ) 
Fls_Drv_Reset(uint8 u1_area)
{
    Fls_StatusType st_ret;  /* return value */

    /* switch to P/E mode */
    st_ret = Fls_Drv_SwitchMode(FLS_DRV_U2_MODE_PE, u1_area);

    if( FLS_DRV_U1_OK == st_ret )
    {
        /* issue forced stop command */
        st_ret = Fls_Drv_ForcedStop(u1_area);
        if( FLS_DRV_U1_OK == st_ret )
        {
            /* switch to read mode */
            st_ret = Fls_Drv_SwitchMode(FLS_DRV_U2_MODE_USER, u1_area);
        }
        else
        {
            /* when the forced stop command has timed out,                             */
            /* an illegal error is intentionally caused for recovery processing.       */
            /* and the mode is switched to read mode after releasing the command lock. */

            /* read FACI command area (occure illegal error and command lock) */
            (void)Fls_Drv_ReadMemoryU16(Fls_RegAdd_Fci[u1_area].u4RegAddFACICMD);
            /* Dummy read */
            (void)Fls_Drv_ReadMemoryU16(Fls_RegAdd_Fci[u1_area].u4RegAddFACICMD);

            Fls_Drv_ClearStatus(u1_area);
            (void)Fls_Drv_SwitchMode(FLS_DRV_U2_MODE_USER, u1_area);
        }

    }
    else
    {
        /* switch to read mode for the recovery process */
        (void)Fls_Drv_SwitchMode(FLS_DRV_U2_MODE_USER, u1_area);
    }

    return(st_ret);

} /* Fls_Drv_Reset */

/*****************************************************************************
   Function      : Forced Stop Function
   Description   : This function forcefully stops FCU by registering a Forced 
                    Stop command to issue area of command.
   param         : u1_area (target area)
   return        : FLS_DRV_U1_OK          (Normal end)
                 : FLS_DRV_U1_ERR_TIMEOUT (Timeout error)
   Note          : -
*****************************************************************************/
FLS_DRV_STATIC FUNC( Fls_StatusType, FLS_CODE ) 
Fls_Drv_ForcedStop(uint8 u1_area)
{
    uint32          u4_res;
    uint32          u4_watchTime;
    uint8           u1_res;
    Fls_StatusType  st_ret;

    /* read Flash Status Register(FSTATR) */
    u4_res = Fls_Drv_ReadMemoryU32(Fls_RegAdd_Fci[u1_area].u4RegAddFSTATR);

    if( FLS_DRV_U4_REGBIT_FSTATR_ILGERR == (FLS_DRV_U4_REGBIT_FSTATR_ILGERR & u4_res) )
    {
        /* when an illegal error has occurred, unlock command */
        u1_res = Fls_Drv_ReadMemoryU08(Fls_RegAdd_Fci[u1_area].u4RegAddFASTAT);
        if( FLS_DRV_U1_REGBIT_FASTAT_CMDLK != u1_res )
        {
            Fls_Drv_WriteMemoryU08(Fls_RegAdd_Fci[u1_area].u4RegAddFASTAT, FLS_DRV_U1_REGBIT_FASTAT_CMDLK);
        }
    }

    /* issue foreced stop command */
    Fls_Drv_WriteMemoryU08(Fls_RegAdd_Fci[u1_area].u4RegAddFACICMD, FLS_DRV_U1_CMD_FORCED_STOP);

    u4_watchTime = (uint32)(((FLS_DRV_U4_FORCEDSTOP_TIME * (uint32)FLS_Drv_CPU_FREQUENCY) + 
                             (FLS_DRV_U4_REGREADY_CLKCNT - FLS_DRV_U4_VAL_1)) / FLS_DRV_U4_REGREADY_CLKCNT);

    /* FRDY monitoring(timeout 40usec) */
    u1_res = Fls_Drv_GetRegReady_Asm( Fls_RegAdd_Fci[u1_area].u4RegAddFSTATR,
                                      FLS_DRV_U4_REGBIT_FSTATR_FRDY,
                                      FLS_DRV_U4_REGBIT_FSTATR_FRDY,
                                      u4_watchTime );

    if( ( FLS_DRV_U1_BIT1_TRUE == u1_res ) || ( FLS_DRV_U1_BIT2_TRUE == u1_res ) )
    {
        st_ret = FLS_DRV_U1_OK;           /* No timeout occurred (normal end) */

    }
    else
    {
        st_ret = FLS_DRV_U1_ERR_TIMEOUT;  /* timeout occurred */
    }

    return st_ret;

} /* Fls_Drv_ForcedStop */

/*****************************************************************************
   Function      : Clear Status Function
   Description   : This function clears the status of the flash driver,
                    registering a Clear Status command to issue area of command.
   param         : u1_area (target area)
   return        : -
   Note          : -
*****************************************************************************/
FLS_DRV_STATIC FUNC( void, FLS_CODE ) 
Fls_Drv_ClearStatus(uint8 u1_area)
{
    uint32  u4_res;
    uint8   u1_res;

    /* read Flash Status Register(FSTATR) */
    u4_res = Fls_Drv_ReadMemoryU32(Fls_RegAdd_Fci[u1_area].u4RegAddFSTATR);

    if( FLS_DRV_U4_REGBIT_FSTATR_ILGERR == ( FLS_DRV_U4_REGBIT_FSTATR_ILGERR & u4_res ) )
    {
        /* when an illegal error has occurred, unlock command */
        u1_res = Fls_Drv_ReadMemoryU08(Fls_RegAdd_Fci[u1_area].u4RegAddFASTAT);
        if( FLS_DRV_U1_REGBIT_FASTAT_CMDLK != u1_res )
        {
            Fls_Drv_WriteMemoryU08(Fls_RegAdd_Fci[u1_area].u4RegAddFASTAT, FLS_DRV_U1_REGBIT_FASTAT_CMDLK);
        }
    }

    /* issue the clear status command */
    Fls_Drv_WriteMemoryU08(Fls_RegAdd_Fci[u1_area].u4RegAddFACICMD, FLS_DRV_U1_CMD_CLEARSTAT);

} /* Fls_Drv_ClearStatus */

/*****************************************************************************
   Function      : Switch Flash Sequencer Operation Mode Function
   Description   : This function switches the mode of Flash Sequencer.
   param[in]     : u2_mode                 (Mode specified)
                   u1_area                 (Target area)
   return        : FLS_DRV_U1_OK              (Normal end)
                 : FLS_DRV_U1_ERR_INTERNAL    (Internal error)
                 : FLS_DRV_U1_ERR_ICU         (Execution during ICU operation)
                 : FLS_DRV_U1_ERR_TIMEOUT     (Timeout error)
   Note          : -
*****************************************************************************/
FUNC( Fls_StatusType, FLS_CODE ) 
Fls_Drv_SwitchMode(uint16 u2_mode, uint8 u1_area)
{
    uint32  u4_regFSTATR;
    uint32  u4_cmp;
    uint16  u2_regFENTRYR;
    Fls_StatusType  st_ret;

    st_ret = FLS_DRV_U1_OK;

    /* When the read mode change was specified. */
    if( FLS_DRV_U2_MODE_USER == u2_mode )
    {
        /* When illegal error/erasure error/write error has occured,        */
        /* Command lock is released and the clear status command is issued. */
        u4_regFSTATR = Fls_Drv_ReadMemoryU32(Fls_RegAdd_Fci[u1_area].u4RegAddFSTATR);
        u4_cmp = FLS_DRV_U4_REGBIT_FSTATR_ILGERR + FLS_DRV_U4_REGBIT_FSTATR_ERSERR + FLS_DRV_U4_REGBIT_FSTATR_PRGERR;
        if( FLS_DRV_U4_REGBIT_FSTATR_RESET != (u4_regFSTATR & u4_cmp) )
        {
            Fls_Drv_ClearStatus(u1_area);
        }
        /* Flash sequencer operation mode is changed to the read mode. */
        Fls_Drv_WriteMemoryU16(Fls_RegAdd_Fci[u1_area].u4RegAddFENTRYR,
                                 FLS_DRV_U2_MODE_USER + FLS_DRV_U2_REGBIT_FENTRY_KEY);

        /* Flash sequencer operation mode is read. */
        (void)Fls_Drv_ReadMemoryU16(Fls_RegAdd_Fci[u1_area].u4RegAddFENTRYR);    /* Dummy read */
        u2_regFENTRYR = Fls_Drv_ReadMemoryU16(Fls_RegAdd_Fci[u1_area].u4RegAddFENTRYR);
        u2_regFENTRYR &= (FLS_DRV_U2_MODE_PE + FLS_DRV_U2_MODE_CPE);
        if( u2_mode != u2_regFENTRYR )
        {
            /* It is internal error When the value is different from the value written in. */
            st_ret = FLS_DRV_U1_ERR_INTERNAL;
        }
    }
    /* when the P/E mode change was specified. */
    else
    {
        /* When Flash sequencer operation mode is the P/E mode already, nothing is done. */
        u2_regFENTRYR = Fls_Drv_ReadMemoryU16(Fls_RegAdd_Fci[u1_area].u4RegAddFENTRYR);
        u2_regFENTRYR &= (FLS_DRV_U2_MODE_PE + FLS_DRV_U2_MODE_CPE);
        if( u2_mode != u2_regFENTRYR )
        {
            /* Flash sequencer operation mode is changed to the P/E mode. */
            Fls_Drv_WriteMemoryU16(Fls_RegAdd_Fci[u1_area].u4RegAddFENTRYR,
                                     FLS_DRV_U2_MODE_PE + FLS_DRV_U2_REGBIT_FENTRY_KEY);

            /* FACI command processing start address/end address is reset. */
            Fls_Drv_WriteMemoryU32(Fls_RegAdd_Fci[u1_area].u4RegAddFSADR, FLS_DRV_U4_VAL_0);
            Fls_Drv_WriteMemoryU32(Fls_RegAdd_Fci[u1_area].u4RegAddFEADR, FLS_DRV_U4_VAL_0);
        }
        /* Flash sequencer operation mode is read. */
        (void)Fls_Drv_ReadMemoryU16(Fls_RegAdd_Fci[u1_area].u4RegAddFENTRYR); /* Dummy read */
        u2_regFENTRYR = Fls_Drv_ReadMemoryU16(Fls_RegAdd_Fci[u1_area].u4RegAddFENTRYR);
        u2_regFENTRYR &= (FLS_DRV_U2_MODE_PE + FLS_DRV_U2_MODE_CPE);
        if( u2_mode != u2_regFENTRYR )
        {
            /* It is internal error When the value is different from the value written in. */
            st_ret = FLS_DRV_U1_ERR_INTERNAL;
        }
    }

    return(st_ret);
} /* Fls_Drv_SwitchMode */

#if ( FLS_DEV_ERROR_DETECT == STD_ON )
/*****************************************************************************
   Function      : Buffer Confirmation Function (for 1byte uint pointer)
   Description   : This function performs the Null check of the starting address
                    of the data buffer.
   param[in]     : pt_addBuf   (Start address of the data buffer)
   return        : E_OK        (Processing result OK (API return value))
                 : E_NOT_OK    (Processing result NG (API return value))
   Note          : -
*****************************************************************************/
FUNC( Std_ReturnType, FLS_CODE ) 
Fls_Drv_ChkBuffer_u1( 
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) pt_addBuf
)
{
    Std_ReturnType st_ret;

    /* NULL check of the start address of a data buffer */
    if( NULL_PTR == pt_addBuf )
    {
        st_ret = E_NOT_OK;  /* Processing result NG */
    }
    else
    {
        st_ret = E_OK;      /* Processing result OK */
    }
    return(st_ret);

} /* Fls_Drv_ChkBuffer_u1 */

/*****************************************************************************
   Function      : Buffer Confirmation Function (for 4byte uint pointer)
   Description   : This function performs the Null check of the starting address
                    of the data buffer.
   param[in]     : pt_addBuf   (Start address of the data buffer)
   return        : E_OK        (Processing result OK (API return value))
                 : E_NOT_OK    (Processing result NG (API return value))
   Note          : -
*****************************************************************************/
FUNC( Std_ReturnType, FLS_CODE )
Fls_Drv_ChkBuffer_u4(
    P2CONST( uint32, AUTOMATIC, TYPEDEF ) pt_addBuf 
)
{
    Std_ReturnType st_ret;

    /* NULL check of the start address of a data buffer */
    if( NULL_PTR == pt_addBuf )
    {
        st_ret = E_NOT_OK;  /* Processing result NG */
    }
    else
    {
        st_ret = E_OK;      /* Processing result OK */
    }

    return(st_ret);
} /* Fls_Drv_ChkBuffer_u4 */

/*****************************************************************************
   Function      : Address Confirmation Function
   Description   : This function checks the range and alignment of the start address.
   param[in]     : u4_addStart (Start address)
   param[in]     : u4_align    (Alignment)
   return        : E_OK        (Processing result OK (API return value))
                 : E_NOT_OK    (Processing result NG (API return value))
   Note          : -
*****************************************************************************/
FUNC( Std_ReturnType, FLS_CODE ) 
Fls_Drv_ChkAddress( uint32 u4_addStart, uint32 u4_align )
{
    Std_ReturnType st_ret;

    /* check whether the start address is not in the data Flash area. */
    if( u4_addStart > ( FLS_DRV_U4_TOTAL_SIZE - FLS_DRV_U4_VAL_1 ) )
    {
        st_ret = E_NOT_OK;
    }
    /* Aligning check of the start address */
    else if( ( u4_addStart & ( u4_align - FLS_DRV_U4_VAL_1 ) ) != FLS_DRV_U4_VAL_0 )
    {
        st_ret = E_NOT_OK;     /* Processing result NG */
    }
    else
    {
        st_ret = E_OK;         /* Processing result OK */
    }
    return(st_ret);

} /* Fls_Drv_ChkAddress */

/*****************************************************************************
   Function      : Length Confirmation Function
   Description   : This function checks the length.
   param[in]     : u4_addStart (Start address)
   param[in]     : u4_bCnt     (Length of the address)
   param[in]     : u4_align    (Alignment)
   return        : E_OK        (Processing result OK (API return value))
                 : E_NOT_OK    (Processing result NG (API return value))
   Note          : -
*****************************************************************************/
FUNC( Std_ReturnType, FLS_CODE ) 
Fls_Drv_ChkLength( uint32 u4_addStart, uint32 u4_bCnt, uint32 u4_align )
{
    uint32  u4_addEnd;
    Std_ReturnType  st_ret;

    /* Check the processing size */
    if( FLS_DRV_U4_VAL_0 == u4_bCnt )
    {
        st_ret = E_NOT_OK;  /* Processing result NG */
    }
    /* Check the alignment */
    else if( ( ( u4_addStart & ( u4_align - FLS_DRV_U4_VAL_1 ) ) != FLS_DRV_U4_VAL_0 ) ||
             ( ( u4_bCnt & ( u4_align - FLS_DRV_U4_VAL_1 ) ) != FLS_DRV_U4_VAL_0 ) )
    {
        st_ret = E_NOT_OK;  /* Processing result NG */
    }
    else
    {
        if( (FLS_DRV_U4_MAX_NUM - u4_addStart) < u4_bCnt )
        {
            st_ret = E_NOT_OK;  /* Processing result NG */
        }
        else
        {
            /* The end address is calculated. */
            u4_addEnd = (u4_addStart + u4_bCnt) - FLS_DRV_U4_VAL_1;
            /* check whether the end address isn't the Data Flash area. */
            if( u4_addEnd > (FLS_DRV_U4_TOTAL_SIZE - FLS_DRV_U4_VAL_1) )
            {
                st_ret = E_NOT_OK;  /* Processing result NG */
            }
            else
            {
                st_ret = E_OK;  /* Processing result OK */
            }
        }
    }

    return(st_ret);

} /* Fls_Drv_ChkLength */

/*****************************************************************************
   Function      : Erasure Request Length Confirmation Function
   Description   : This function checks the length.(erase request only)
   param[in]     : u4_addStart (Start address)
   param[in]     : u4_bCnt     (Length of the address)
   return        : E_OK     (Processing result OK (API return value))
                 : E_NOT_OK (Processing result NG (API return value))
   Note          : -
*****************************************************************************/
FUNC( Std_ReturnType, FLS_CODE ) 
Fls_Drv_ChkEraseLength( uint32 u4_addStart, uint32 u4_bCnt )
{
    uint32     u4_addEnd;
    Std_ReturnType st_ret;

    /* Check the processing size */
    if( FLS_DRV_U4_VAL_0 == u4_bCnt )
    {
        st_ret = E_NOT_OK;     /* Processing result NG */
    }
    else
    {
        if( (FLS_DRV_U4_MAX_NUM - u4_addStart) < u4_bCnt )
        {
            st_ret = E_NOT_OK;  /* Processing result NG */
        }
        else
        {
            /* The end address is calculated. */
            u4_addEnd = (u4_addStart + u4_bCnt) - FLS_DRV_U4_VAL_1;
            /* check whether the end address isn't in the Data Flash area. */
            if( u4_addEnd > ( FLS_DRV_U4_TOTAL_SIZE - FLS_DRV_U4_VAL_1 ) )
            {
                st_ret = E_NOT_OK;     /* Processing result NG */
            }
            else
            {
                st_ret = E_OK;         /* Processing result OK */
            }
        }
    }
    return(st_ret);

} /* Fls_Drv_ChkEraseLength */
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */

/*****************************************************************************
   Function      : Accessibility Confirmation Function
   Description   : This function checks the area whether accessible.
   param         : u1_area                (Target area)
   return        : FLS_DRV_U1_BUSY        (During operation)
                 : FLS_DRV_U1_ERR_INTERNAL(Internal error)
   Note          : -
*****************************************************************************/
FLS_DRV_STATIC FUNC( Fls_StatusType, FLS_CODE ) 
Fls_Drv_ChkAccessRight( uint8 u1_area )
{
    uint32  u4_addStart;
    uint32  u4_addEnd;
    Fls_StatusType  st_ret;

    st_ret = FLS_DRV_U1_BUSY;

    /* check whether the start address isn't in the Data Flash area. */
    u4_addStart = Fls_Drv_ReadMemoryU32(Fls_RegAdd_Fci[u1_area].u4RegAddFSADR);
    if( u4_addStart > ( FLS_DRV_U4_TOTAL_SIZE - FLS_DRV_U4_VAL_1 ) )
    {
        st_ret = FLS_DRV_U1_ERR_INTERNAL;      /* Internal error */
    }

    /* check whether the end address isn't the Data Flash area. */
    u4_addEnd = Fls_Drv_ReadMemoryU32(Fls_RegAdd_Fci[u1_area].u4RegAddFEADR) + (FLS_DRV_U4_ACCESS_SIZE - FLS_DRV_U4_VAL_1);
    if( u4_addEnd > ( FLS_DRV_U4_TOTAL_SIZE - FLS_DRV_U4_VAL_1 ) )
    {
        st_ret = FLS_DRV_U1_ERR_INTERNAL;      /* Internal error */
    }

    return(st_ret);

} /* Fls_Drv_ChkAccessRight */

/*****************************************************************************
   Function      : Write Function
   Description   : This function writes the data, which is read from the
                    specified RAM area, to the specified address.
   param[in]     : pt_AddSrc               (Source address)
   param[in]     : u4_addDest              (Write address)
   param[in]     : u4_cnt                  (Write size)
   param[in]     : u1_area                 (Target area)
   return        : FLS_DRV_U1_BUSY            (During processing execution)
                 : FLS_DRV_U1_ERR_INTERNAL    (Internal error)
   Note          : -
*****************************************************************************/
FUNC( Fls_StatusType, FLS_CODE ) 
Fls_Drv_StartWriteOperation( P2CONST( uint8, AUTOMATIC, FLS_APPL_CONST )pt_AddSrc,
                             uint32 u4_addDest,
                             uint32 u4_cnt,
                             uint8 u1_area)
{
    uint32          u4_writesize;
    uint32          u4_data;
    uint32          u4_TempData;
    P2CONST( uint8, AUTOMATIC, FLS_APPL_CONST ) pt_AddSrc_tmp;
    Fls_StatusType  st_ret;

    pt_AddSrc_tmp = pt_AddSrc;

    /* The write address is set to a FACI command processing start address register. */
    Fls_Drv_WriteMemoryU32(Fls_RegAdd_Fci[u1_area].u4RegAddFSADR, u4_addDest);

    /* The end address is calculated and  set to a FACI command processing end address register. */
    Fls_Drv_WriteMemoryU32(Fls_RegAdd_Fci[u1_area].u4RegAddFEADR, u4_addDest + ( u4_cnt - FLS_DRV_U4_VAL_1 ) );

    /* 0xE8 is written to FACI command issue area. */
    Fls_Drv_WriteMemoryU08(Fls_RegAdd_Fci[u1_area].u4RegAddFACICMD, FLS_DRV_U1_CMD_WRITE);

    /* "N"(in case of writing 4 byte : 0x02) is written in FACI command issue area. */
    u4_writesize = u4_cnt / FLS_DRV_U4_DATA_TRANSFERSIZE_4BYTE;

    Fls_Drv_WriteMemoryU08(Fls_RegAdd_Fci[u1_area].u4RegAddFACICMD, (uint8)u4_writesize);

    /* the write data is acquired from the address. */
    u4_TempData = (uint32)(pt_AddSrc_tmp[FLS_DRV_U1_IDX_3]);
    u4_data     = (uint32)(u4_TempData << FLS_DRV_U1_BITSHIFT_24);
    u4_TempData = (uint32)(pt_AddSrc_tmp[FLS_DRV_U1_IDX_2]);
    u4_data    |= (uint32)(u4_TempData << FLS_DRV_U1_BITSHIFT_16);
    u4_TempData = (uint32)(pt_AddSrc_tmp[FLS_DRV_U1_IDX_1]);
    u4_data    |= (uint32)(u4_TempData << FLS_DRV_U1_BITSHIFT_8);
    u4_data    |= (uint32)(pt_AddSrc_tmp[FLS_DRV_U1_IDX_0]);

    /* Data is written in FACI command issue area. */
    Fls_Drv_WriteMemoryU32(Fls_RegAdd_Fci[u1_area].u4RegAddFACICMD, u4_data);

    /* FACI command processing start address/end address is checked. */
    st_ret = Fls_Drv_ChkAccessRight(u1_area);
    if( FLS_DRV_U1_BUSY == st_ret )
    {
        /* 0xD0 is written to FACI command issue area. */
        Fls_Drv_WriteMemoryU08(Fls_RegAdd_Fci[u1_area].u4RegAddFACICMD, FLS_DRV_U1_CMD_EXE);
    }

    return(st_ret);

} /* Fls_Drv_StartWriteOperation */

/*****************************************************************************
   Function      : Start Blank Check / Erase Process Function
   Description   : This function starts a blank check or erase.
   param[in]     : u4_addStart             (Start adress)
   param[in]     : u4_addEnd               (End adress)
   param[in]     : u1_fcuCmd               (FACI command)
   param[in]     : u1_area                 (Target area)
   return        : FLS_DRV_U1_BUSY            (During processing execution)
                 : FLS_DRV_U1_ERR_INTERNAL    (Internal error)
   Note          : -
*****************************************************************************/
FUNC( Fls_StatusType, FLS_CODE ) 
Fls_Drv_StartBCEraseOperation( uint32   u4_addStart,
                               uint32   u4_addEnd,
                               uint8    u1_fcuCmd,
                               uint8    u1_area )
{
    Fls_StatusType st_ret;

#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A8 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A16 )
    /* Flash Sequencer Process Switch Register(FCPSR) is set to the Suspension-priority mode. */
    Fls_Drv_WriteMemoryU16(Fls_RegAdd_Fci[u1_area].u4RegAddFCPSR, FLS_DRV_U2_REGBIT_FCPSR_SUSPMD);
#endif

    /* FACI command processing start address register is established. */
    Fls_Drv_WriteMemoryU32(Fls_RegAdd_Fci[u1_area].u4RegAddFSADR, u4_addStart);

    /* FACI command processing end address register is established. */
    Fls_Drv_WriteMemoryU32(Fls_RegAdd_Fci[u1_area].u4RegAddFEADR, u4_addEnd);

    /* 0x20 (Erase)is written to FACI command issue area. */
    Fls_Drv_WriteMemoryU08(Fls_RegAdd_Fci[u1_area].u4RegAddFACICMD, u1_fcuCmd);

    /* FACI command processing start address/end address is checked. */
    st_ret = Fls_Drv_ChkAccessRight(u1_area);
    if( FLS_DRV_U1_BUSY == st_ret )
    {
        /* 0xD0 is written to FACI command issue area. */
        Fls_Drv_WriteMemoryU08(Fls_RegAdd_Fci[u1_area].u4RegAddFACICMD, FLS_DRV_U1_CMD_EXE);
    }

    return(st_ret);

}/* Fls_Drv_StartBCEraseOperation */

#if ( FLS_CDD_READ_API == STD_ON ) || ( FLS_CDD_COMPARE_API == STD_ON )
/*****************************************************************************
   Function      : Read Function
   Description   : This function reads the specified amount of data from the
                    specified address.
   param[in]     : u4_addSrc           (Source address)
   param[in]     : pt_AddDest          (Write address)
   param[in]     : u4_cnt              (Number of words)
   return        : FLS_DRV_U1_BUSY          (Normal end)
                 : FLS_DRV_U1_ERR_ECC_DED (ECC(2-bit) error)
   Note          : -
*****************************************************************************/
FUNC( Fls_StatusType, FLS_CODE ) 
Fls_Drv_ReadOperation( uint32 u4_addSrc, P2VAR( uint8, AUTOMATIC, TYPEDEF )pt_AddDest, uint32 u4_cnt )
{
    uint32          u4_addEnd;
    uint32          u4_add;
    P2VAR( uint8, AUTOMATIC, TYPEDEF )pt_AddDest_tmp;
    uint32          u4_DataBufPos;
    Fls_StatusType  st_ret;
#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A8 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A16 )
    uint32          u4_regDFERSTR;
#elif ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2B6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2B10 )
    uint32          u4_regDFSERSTR;
    uint32          u4_regDFDERSTR;
#endif
    uint32          u4_LoopCnt;          /* loop counter */
    uint32          u4DataBuf;           /* Data buffer */
    uint32          u4_sizeMask;         /* size mask */

    pt_AddDest_tmp = pt_AddDest;
    u4_DataBufPos = FLS_DRV_U4_VAL_0;
    st_ret = FLS_DRV_U1_BUSY;
    u4_LoopCnt = FLS_DRV_U4_VAL_0;

    /* The target address of the reading is calculated. */
    u4_add     = u4_addSrc + FLS_BASE_ADDRESS;    /* The reading starting address */
    u4_addEnd  = u4_add    + u4_cnt;              /* The reading end address */
    u4_sizeMask = FLS_DRV_U4_ACCESS_SIZE - FLS_DRV_U4_VAL_1;

#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A8 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A16 )
    /* An error flag of Data flash error status clear register(DFERSTC) is cleared. */
    Fls_Drv_WriteMemoryU32(FLS_DRV_U4_REGADD_DFERSTC, FLS_DRV_U4_REGBIT_DFERSTC_ERRCLR);
#elif ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2B6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2B10 )
    /* An error flag of Data flash 1-bit error status clear register(DFSERSTC) is cleared. */
    Fls_Drv_WriteMemoryU32(FLS_DRV_U4_REGADD_DFSERSTC, FLS_DRV_U4_REGBIT_DFSERSTC_SSTCLR);
    /* An error flag of Data flash 2-bit error status clear register(DFDERSTC) is cleared. */
    Fls_Drv_WriteMemoryU32(FLS_DRV_U4_REGADD_DFDERSTC, FLS_DRV_U4_REGBIT_DFDERSTC_DSTCLR);
#endif

    do
    {
        /* Check whether target address is 4 byte alignment or not */
        if( ( u4_add & u4_sizeMask ) != FLS_DRV_U4_VAL_0 )
        {
            /* if target address is  2 byte alignment, change the target address to 4 byte alignment */
            /* Note that it is necessary to deal with the extra data   */
            u4_add -= FLS_DRV_U4_READ_SIZE;
        }

        /* by the 4Byte unit, reading */
        u4DataBuf = Fls_Drv_ReadMemoryU32(u4_add);    /* from a data flash, reading */

#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A8 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A16 )
        /* Reading of Data flash error status register(DFERSTR) */
        /* in case of F1L, P1M-E, D1M1A or E2M */
        u4_regDFERSTR = Fls_Drv_ReadMemoryU32(FLS_DRV_U4_REGADD_DFERSTR);
        if( FLS_DRV_U4_REGVAL_DFERSTR_NOERR != u4_regDFERSTR )
        {
            /* When an ECC 2bit error has occurred. */
            if( FLS_DRV_U4_REGBIT_DFERSTR_DEDF == (FLS_DRV_U4_REGBIT_DFERSTR_DEDF & u4_regDFERSTR) )
            {
                st_ret = FLS_DRV_U1_ERR_ECC_DED;      /* ECC 2bit error */
            }

            /* An error flag of Data flash error status clear register(DFERSTC) is cleared. */
            Fls_Drv_WriteMemoryU32(FLS_DRV_U4_REGADD_DFERSTC, FLS_DRV_U4_REGBIT_DFERSTC_ERRCLR);
        }
#elif ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2B6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2B10 )
        /* Reading of Data flash error status register(DFSERSTR) and register(DFSERSTR) */
        /* in case of U2Bx */
        u4_regDFSERSTR = Fls_Drv_ReadMemoryU32(FLS_DRV_U4_REGADD_DFSERSTR);
        u4_regDFDERSTR = Fls_Drv_ReadMemoryU32(FLS_DRV_U4_REGADD_DFDERSTR);
        if( FLS_DRV_U4_REGVAL_DFDERSTR_NOERR != u4_regDFDERSTR )
        {
            st_ret = FLS_DRV_U1_ERR_ECC_DED;      /* ECC 2bit error */

            /* An error flag of Data flash error status clear register(DFDERSTC) is cleared. */
            Fls_Drv_WriteMemoryU32(FLS_DRV_U4_REGADD_DFDERSTC, FLS_DRV_U4_REGBIT_DFDERSTC_DSTCLR);
        }
        if( FLS_DRV_U4_REGVAL_DFSERSTR_NOERR != u4_regDFSERSTR )
        {
            /* An error flag of Data flash error status clear register(DFERSTC) is cleared. */
            Fls_Drv_WriteMemoryU32(FLS_DRV_U4_REGADD_DFSERSTC, FLS_DRV_U4_REGBIT_DFSERSTC_SSTCLR);
        }
        /* When an ECC 2bit error has occurred. */
#endif

        /* if target address or read size is  2 byte alignment, delete the extra data . */
        if( ( ( u4_addSrc & u4_sizeMask ) != FLS_DRV_U4_VAL_0 ) ||
            ( ( u4_cnt & u4_sizeMask ) != FLS_DRV_U4_VAL_0 ) )
        {
            /* if target address is  2 byte alignment, delete the first 2 byte data. */
            if( ( u4_addSrc & u4_sizeMask ) != FLS_DRV_U4_VAL_0 ) 
            {
                if(u4_LoopCnt == FLS_DRV_U4_VAL_0)
                {
                    /* first read operation */
                    /* delete the first 2 byte data. */
                    pt_AddDest_tmp[u4_DataBufPos] = (uint8)((u4DataBuf & FLS_DRV_U4_BITMASK_16_TO_23BIT) >> FLS_DRV_U1_BITSHIFT_16);
                    u4_DataBufPos++;
                    pt_AddDest_tmp[u4_DataBufPos] = (uint8)(u4DataBuf >> FLS_DRV_U1_BITSHIFT_24);
                    u4_DataBufPos++;
                    u4_LoopCnt = FLS_DRV_U4_VAL_1;
                }
                else if(((u4_add + FLS_DRV_U4_ACCESS_SIZE) >= u4_addEnd)
                    && (( u4_cnt & u4_sizeMask ) == FLS_DRV_U4_VAL_0))
                {
                    /* target address is  2 byte alignment while read size is  4 byte alignment . */
                    /* last read operation */
                    /* delete the last 2 byte data. */
                    pt_AddDest_tmp[u4_DataBufPos] = (uint8)((u4DataBuf & FLS_DRV_U4_BITMASK_0_TO_7BIT));
                    u4_DataBufPos++;
                    pt_AddDest_tmp[u4_DataBufPos] = (uint8)((u4DataBuf & FLS_DRV_U4_BITMASK_8_TO_15BIT) >> FLS_DRV_U1_BITSHIFT_8);
                    u4_DataBufPos++;
                }
                else
                {
                    /* store read data */
                    pt_AddDest_tmp[u4_DataBufPos] = (uint8)((u4DataBuf & FLS_DRV_U4_BITMASK_0_TO_7BIT));
                    u4_DataBufPos++;
                    pt_AddDest_tmp[u4_DataBufPos] = (uint8)((u4DataBuf & FLS_DRV_U4_BITMASK_8_TO_15BIT)  >> FLS_DRV_U1_BITSHIFT_8);
                    u4_DataBufPos++;
                    pt_AddDest_tmp[u4_DataBufPos] = (uint8)((u4DataBuf & FLS_DRV_U4_BITMASK_16_TO_23BIT) >> FLS_DRV_U1_BITSHIFT_16);
                    u4_DataBufPos++;
                    pt_AddDest_tmp[u4_DataBufPos] = (uint8)((u4DataBuf                                 ) >> FLS_DRV_U1_BITSHIFT_24);
                    u4_DataBufPos++;
                }
    
            }
            else
            {
                /* target address is  4 byte alignment while read size is  2 byte alignment . */
                /* store read data */
                if( (u4_add + FLS_DRV_U4_ACCESS_SIZE) >= u4_addEnd )
                {
                    /* last read operation */
                    /* delete the last 2 byte data. */
                    pt_AddDest_tmp[u4_DataBufPos] = (uint8)((u4DataBuf & FLS_DRV_U4_BITMASK_0_TO_7BIT));
                    u4_DataBufPos++;
                    pt_AddDest_tmp[u4_DataBufPos] = (uint8)((u4DataBuf & FLS_DRV_U4_BITMASK_8_TO_15BIT) >> FLS_DRV_U1_BITSHIFT_8);
                    u4_DataBufPos++;
                }
                else
                {
                    /* store read data */
                    pt_AddDest_tmp[u4_DataBufPos] = (uint8)((u4DataBuf & FLS_DRV_U4_BITMASK_0_TO_7BIT));
                    u4_DataBufPos++;
                    pt_AddDest_tmp[u4_DataBufPos] = (uint8)((u4DataBuf & FLS_DRV_U4_BITMASK_8_TO_15BIT)  >> FLS_DRV_U1_BITSHIFT_8);
                    u4_DataBufPos++;
                    pt_AddDest_tmp[u4_DataBufPos] = (uint8)((u4DataBuf & FLS_DRV_U4_BITMASK_16_TO_23BIT) >> FLS_DRV_U1_BITSHIFT_16);
                    u4_DataBufPos++;
                    pt_AddDest_tmp[u4_DataBufPos] = (uint8)((u4DataBuf                                 ) >> FLS_DRV_U1_BITSHIFT_24);
                    u4_DataBufPos++;
                }
            }
        }
        else
        {
            /* store read data */
            pt_AddDest_tmp[u4_DataBufPos] = (uint8)((u4DataBuf & FLS_DRV_U4_BITMASK_0_TO_7BIT));
            u4_DataBufPos++;
            pt_AddDest_tmp[u4_DataBufPos] = (uint8)((u4DataBuf & FLS_DRV_U4_BITMASK_8_TO_15BIT)  >> FLS_DRV_U1_BITSHIFT_8);
            u4_DataBufPos++;
            pt_AddDest_tmp[u4_DataBufPos] = (uint8)((u4DataBuf & FLS_DRV_U4_BITMASK_16_TO_23BIT) >> FLS_DRV_U1_BITSHIFT_16);
            u4_DataBufPos++;
            pt_AddDest_tmp[u4_DataBufPos] = (uint8)((u4DataBuf                                 ) >> FLS_DRV_U1_BITSHIFT_24);
            u4_DataBufPos++;
        }

        /* the reading address, inclement. */
        u4_add += FLS_DRV_U4_ACCESS_SIZE;

    }
    while( u4_add < u4_addEnd );     /* Repeat until the end address has been reached. */

    return(st_ret);

} /* Fls_Drv_ReadOperation */
#endif /* ( FLS_CDD_READ_API == STD_ON ) || ( FLS_CDD_COMPARE_API == STD_ON ) */

/*****************************************************************************
   Function      : Processing Progress Function
   Description   : This function advances the processing of the command in
                    Periodic Process.
   param         : pt_stat         (Type of error)
                   u1_area         (target area)
   return        : FLS_DRV_U1_FALSE   (False(Flag used within FLS_DRV))
                 : FLS_DRV_U1_TRUE    (True (Flag used within FLS_DRV))
   Note          : -
*****************************************************************************/
FUNC( Fls_FlagType, FLS_CODE ) 
Fls_Drv_MultiOperation(
    P2VAR( Fls_StatusType, AUTOMATIC, TYPEDEF ) pt_stat, uint8 u1_area
)
{
    Fls_FlagType    st_cont;
    Fls_StatusType  st_result;          /* return value of a called function */

    st_cont = FLS_DRV_U1_TRUE; 
    st_result = FLS_DRV_U1_OK;

   if( Fls_Str.stMulOp_str[u1_area].stCommand_enu == FLS_DRV_U1_CMDTYPE_WRITE )
   {
        if( Fls_Str.stMulOp_str[u1_area].u4FlashAdd < Fls_Str.stMulOp_str[u1_area].u4FlashAddEnd )
        {
            st_cont = FLS_DRV_U1_FALSE;

            /* write in data area */
            st_result = Fls_Drv_StartWriteOperation(Fls_Str.stMulOp_str[u1_area].ptBufAdd,
                                                    Fls_Str.stMulOp_str[u1_area].u4FlashAdd,
                                                    FLS_DRV_U4_ACCESS_SIZE,
                                                    u1_area);

            Fls_Str.stMulOp_str[u1_area].u4FlashAdd += FLS_DRV_U4_ACCESS_SIZE;
            Fls_Str.stMulOp_str[u1_area].ptBufAdd    = &(Fls_Str.stMulOp_str[u1_area].ptBufAdd[FLS_DRV_U4_ACCESS_SIZE]);

            if( FLS_DRV_U1_BUSY != st_result )
            {
                Fls_Drv_ErrRefresh(u1_area);
                (void)Fls_Drv_SwitchMode(FLS_DRV_U2_MODE_USER, u1_area);
            }

        }

        (*pt_stat) = st_result;

    }
    else if( Fls_Str.stMulOp_str[u1_area].stCommand_enu == FLS_DRV_U1_CMDTYPE_ERASE )
    {

        if( Fls_Str.stMulOp_str[u1_area].u4FlashAdd < Fls_Str.stMulOp_str[u1_area].u4FlashAddEnd )
        {
            st_cont = FLS_DRV_U1_FALSE;

            /* erase in data area 0*/
            st_result = Fls_Drv_StartBCEraseOperation(Fls_Str.stMulOp_str[u1_area].u4FlashAdd,
                                                      (Fls_Str.stMulOp_str[u1_area].u4FlashAdd
                                                          + FLS_DRV_U4_BLOCK_SIZE) - FLS_DRV_U4_VAL_1,
                                                      FLS_DRV_U1_CMD_ERASE,
                                                      u1_area);

            Fls_Str.stMulOp_str[u1_area].u4FlashAdd += FLS_DRV_U4_BLOCK_SIZE;

            if( FLS_DRV_U1_BUSY != st_result )
            {
                Fls_Drv_ErrRefresh(u1_area);
                (void)Fls_Drv_SwitchMode(FLS_DRV_U2_MODE_USER, u1_area);
            }

        }

        (*pt_stat) = st_result;

    }
    else
    {
        /* (*pt_stat) = FLS_DRV_U1_ERR_INTERNAL; */
         (*pt_stat) = st_result;
    }

    return(st_cont);

} /* Fls_Drv_MultiOperation */

/*****************************************************************************
   Function      : FLASH Sequencer State Confirmation Function
   Description   : This function reads the FRDY bit of Flash Status Register
                    and checks the status of Flash Sequencer.
   param         : u1_area (target area)
   return        : FLS_DRV_U1_FALSE   (False(Flag used within FLS_DRV))
                 : FLS_DRV_U1_TRUE    (True (Flag used within FLS_DRV))
   Note          : -
*****************************************************************************/
FLS_DRV_STATIC FUNC( Fls_FlagType, FLS_CODE ) 
Fls_Drv_ChkReady(uint8 u1_area)
{
    uint32          u4_regFSTATR;
    Fls_FlagType    st_ret;

    /* Reading of Flash status register(FSTATR0) */
    u4_regFSTATR = Fls_Drv_ReadMemoryU32(Fls_RegAdd_Fci[u1_area].u4RegAddFSTATR);

    /* Flash Rady bit(FRDY) is checked. */
    if( FLS_DRV_U4_REGBIT_FSTATR_FRDY == ( u4_regFSTATR & FLS_DRV_U4_REGBIT_FSTATR_FRDY ) )
    {
        st_ret = FLS_DRV_U1_TRUE;     /* Flash Rady state */
    }
    else
    {
        st_ret = FLS_DRV_U1_FALSE;    /* During a command processing */
    }

    return(st_ret);

} /* Fls_Drv_ChkReady */

/*****************************************************************************
   Function      : Error Status Acquisition Function
   Description   : This function reads Flash Status Register
                    and checks the error state.
   param         : u1_area (target area)
   return        : FLS_DRV_U1_OK           (Normal end)
                 : FLS_DRV_U1_ERR_INTERNAL (Internal error)
   Note          : -
*****************************************************************************/
FLS_DRV_STATIC FUNC( Fls_StatusType, FLS_CODE ) 
Fls_Drv_CheckFatalError(uint8 u1_area)
{
    uint32          u4_regFSTATR;
    uint32          u4_checkVal;
    Fls_StatusType  st_ret;

    st_ret = FLS_DRV_U1_OK;

    /* Reading of Flash status register(FSTATR0) */
    u4_regFSTATR = Fls_Drv_ReadMemoryU32(Fls_RegAdd_Fci[u1_area].u4RegAddFSTATR);

    /* Except the FCU related error */
    u4_checkVal = ( FLS_DRV_U4_REGBIT_FSTATR_TBLDTCT     /* 2 bit error(Rewriting parameter table)    */
                  + FLS_DRV_U4_REGBIT_FSTATR_CFGDTCT     /* 2 bit error(Configuration setting)        */
                  + FLS_DRV_U4_REGBIT_FSTATR_FHVEERR     /* Flash Write Erase Protect Error           */
                  + FLS_DRV_U4_REGBIT_FSTATR_SECDTCT     /* 2 bit error(Security setting area)        */
                  + FLS_DRV_U4_REGBIT_FSTATR_ILGERR      /* illegal command error                     */
                  + FLS_DRV_U4_REGBIT_FSTATR_BPLDTCT     /* 2 bit error(Block Protection Area)        */
                  + FLS_DRV_U4_REGBIT_FSTATR_ERCDTCT     /* 2 bit error(Erase counter)                */
                  + FLS_DRV_U4_REGBIT_FSTATR_SWTDTCT     /* 2 bit error(Switch Area and TAG Area)     */
                  );

    if( ( u4_checkVal & u4_regFSTATR ) != FLS_DRV_U4_VAL_0 )
    {
        st_ret = FLS_DRV_U1_ERR_INTERNAL;  /* Internal error */
    }

    return(st_ret);

} /* Fls_Drv_CheckFatalError */

/*****************************************************************************
   Function      : Command Status Acquisition Function
   Description   : This function checks the error state for the command.
   param         : u1_area (target area)
   return        : FLS_DRV_U1_OK             (Normal end)
                 : FLS_DRV_U1_ERR_WRITE      (Write error)
                 : FLS_DRV_U1_ERR_ERASE      (Erase error)
                 : FLS_DRV_U1_ERR_BLANKCHECK (Blank Check error)
   Note          : -
*****************************************************************************/
FLS_DRV_STATIC FUNC( Fls_StatusType, FLS_CODE ) 
Fls_Drv_GetStat(uint8 u1_area)
{
    uint32          u4_regFSTATR;
    Fls_StatusType  st_stat;


    /* When write with FACI0 command has failed. */
    u4_regFSTATR = Fls_Drv_ReadMemoryU32(Fls_RegAdd_Fci[u1_area].u4RegAddFSTATR);
    if( FLS_DRV_U4_REGBIT_FSTATR_PRGERR == ( u4_regFSTATR & FLS_DRV_U4_REGBIT_FSTATR_PRGERR ) )
    {
        st_stat = FLS_DRV_U1_ERR_WRITE;        /* Write error */
    }
    else
    {
        /* When erasure with FACI0 command has failed. */
        if( FLS_DRV_U4_REGBIT_FSTATR_ERSERR == ( u4_regFSTATR & FLS_DRV_U4_REGBIT_FSTATR_ERSERR ) )
        {
            st_stat = FLS_DRV_U1_ERR_ERASE;    /* Erase error */
        }
        else
        {
            /* When there are no relevant errors with FACI0.(When the command has normally ended.) */
            st_stat = FLS_DRV_U1_OK;           /* Normal end */
        }
    }

    return (st_stat);

} /* Fls_Drv_GetStat */

/*****************************************************************************
   Function      : Command Execution State Confirmation Function
   Description   : This function checks command execution status.
   param[out]    : pt_stat            (Processing result)
   param[in]     : u1_area            (target area)
   return        : FLS_DRV_U1_FALSE   (False(Flag used within FLS_DRV))
                 : FLS_DRV_U1_TRUE    (True (Flag used within FLS_DRV))
   Note          : -
*****************************************************************************/
FLS_DRV_STATIC FUNC( Fls_FlagType, FLS_CODE ) 
Fls_Drv_OperationCheck(
    P2VAR( Fls_StatusType, AUTOMATIC, TYPEDEF ) pt_stat, uint8 u1_area
)
{
    Fls_FlagType    st_cont;

    st_cont = FLS_DRV_U1_TRUE;

    /* The command state is acquired. */
    (*pt_stat) = Fls_Drv_GetStat(u1_area);

    /* The status clear command is issued. */
    Fls_Drv_ClearStatus(u1_area);

    if( FLS_DRV_U1_OK != *pt_stat )
    {
        /* When an error is detected, switch to read mode. */
        (void)Fls_Drv_SwitchMode(FLS_DRV_U2_MODE_USER, u1_area);
        st_cont = FLS_DRV_U1_FALSE;
    }


    return(st_cont);

} /* Fls_Drv_OperationCheck */

/*****************************************************************************
   Function      : Error State Confirmation Function
   Description   : This function checks the FCU error state,
                    and carries out post-processing when an error has occurred.
   param[out]    : pt_stat            (Type of error)
   param[in]     : u1_area            (target area)
   return        : FLS_DRV_U1_FALSE   (False(Flag used within FLS_DRV))
                 : FLS_DRV_U1_TRUE    (True (Flag used within FLS_DRV))
   Note          : -
*****************************************************************************/
FLS_DRV_STATIC FUNC( Fls_FlagType, FLS_CODE ) 
Fls_Drv_ReactOnFatalErrors(
    P2VAR( Fls_StatusType, AUTOMATIC, TYPEDEF ) pt_stat, uint8 u1_area
)
{
    Fls_FlagType    st_cont;
    Fls_StatusType  st_status;

    st_cont = FLS_DRV_U1_TRUE;

    /* Error Status Function Acquisition */
    st_status = Fls_Drv_CheckFatalError(u1_area);

    if( FLS_DRV_U1_OK != st_status )
    {
        /* The forced stop command is issued. */
        (void)Fls_Drv_ForcedStop(u1_area);

        /* switch to the read mode. */
        (void)Fls_Drv_SwitchMode(FLS_DRV_U2_MODE_USER, u1_area);

        (*pt_stat) = st_status;

        st_cont = FLS_DRV_U1_FALSE;
    }

    return(st_cont);

} /* Fls_Drv_ReactOnFatalErrors */

/*****************************************************************************
   Function      : Execution State Confirmation Function
   Description   : This function checks the state of command being executed
                    in Periodic process.
   param[in]     : pt_stat          (Type of error)
                   u1_area          (target area)
   return        : FLS_DRV_U1_FALSE (False(Flag used within FLS_DRV))
                 : FLS_DRV_U1_TRUE  (True (Flag used within FLS_DRV))
   Note          : -
*****************************************************************************/
FUNC( Fls_FlagType, FLS_CODE ) 
Fls_Drv_CheckStatus(
    P2VAR( Fls_StatusType, AUTOMATIC, TYPEDEF ) pt_stat, uint8 u1_area
)
{
    Fls_FlagType    st_contHdrFct;
    Fls_StatusType  st_status;

    st_status = FLS_DRV_U1_BUSY;

    /* Flash sequencer execution state is confirmed. */
    st_contHdrFct = Fls_Drv_ChkReady(u1_area);

    if( FLS_DRV_U1_TRUE == st_contHdrFct )
    {
        /* The error occurrence state is confirmed. */
        st_contHdrFct = Fls_Drv_ReactOnFatalErrors(&st_status, u1_area);
        if( FLS_DRV_U1_TRUE == st_contHdrFct )
        {
            /* The command execution state is confirmed. */
            st_contHdrFct = Fls_Drv_OperationCheck(&st_status, u1_area);
        }
    }
    (*pt_stat) = st_status;

    return(st_contHdrFct);

} /* Fls_Drv_CheckStatus */

/*****************************************************************************
   Function      : Error Recovery Function
   Description   : This function reads the FACI command issuing region to stop 
                    the processing of the FCU to generate command lock,
                    and issues Forced Stop command.
   param         : u1_area            (target area)
   return        : -
   Note          : -
*****************************************************************************/
FUNC( void, FLS_CODE ) 
Fls_Drv_ErrRefresh(uint8 u1_area)
{
    /* FACI0 command area reading(Command lock occurs.) */
    (void)Fls_Drv_ReadMemoryU16(Fls_RegAdd_Fci[u1_area].u4RegAddFACICMD);
    /* Dummy read */
    (void)Fls_Drv_ReadMemoryU16(Fls_RegAdd_Fci[u1_area].u4RegAddFACICMD);

    /* Forced stop command is issued. */
    (void)Fls_Drv_ForcedStop(u1_area);

} /* Fls_Drv_ErrRefresh */

/*****************************************************************************
   Function      : End Command Processing Function
   Description   : This function is called when the command processing is completed, 
                    to initialize the operation information.
                    (setting FLS processing results and the FLS internal state)
                    Also, this function calls Report Function and 
                    Processing Result Response Hook Function in accordance 
                    with the processing result.
   param[in]     : st_stat (Processing state)
                   u1_area (target area)
   return        : -
   Note          : -
*****************************************************************************/
FUNC( void, FLS_CODE ) 
Fls_Drv_EndCurrentOperation(Fls_StatusType st_stat, uint8 u1_area)
{
#if ( FLS_DEV_ERROR_DETECT == STD_ON )
    uint8   u1_reportErr;
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */
    /* It's confirmed whether the command result normally ends. */
    if( FLS_DRV_U1_OK == st_stat )
    {
        /* FLS processing result is established. */
        Fls_Str.stiJobResult_enu = MEMIF_JOB_OK;
        /* FLS internal state is established. */
        Fls_Str.stiStat_enu = MEMIF_IDLE;

        Fee_JobEndNotification();
        /* Information on the execution command is cleared. */
        Fls_Drv_ClearOperationInfo();
    }
    else
    {
#if ( FLS_DEV_ERROR_DETECT == STD_ON )
        /* abnormal end */
        if( FLS_DRV_U1_CMDTYPE_ERASE == Fls_Str.stMulOp_str[u1_area].stCommand_enu )
        {   /* When the command is an erase request. */
            u1_reportErr = FLS_E_EXT_ERASE_FAILED;
        }
        else
        {   /* When the command is a write request. */
            u1_reportErr = FLS_E_EXT_WRITE_FAILED;
        }
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */
        /* FLS processing result is established (processing failure). */
        Fls_Str.stiJobResult_enu = MEMIF_JOB_FAILED;
        /* FLS internal state is established. */
        Fls_Str.stiStat_enu = MEMIF_IDLE;

        Fee_JobErrorNotification();
        /* Information on the execution command is cleared. */
        Fls_Drv_ClearOperationInfo();

#if ( FLS_DEV_ERROR_DETECT == STD_ON )
        (void)Fls_ErrorHook(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_APIID_MAINFUNCTION, u1_reportErr);
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */
    }
} /* Fls_Drv_EndCurrentOperation */

#if ( FLS_CDD_COMPARE_API == STD_ON )
/*****************************************************************************
   Function      : Execute Comparison Process
   Description   : This function is called from Comparison Request,
                    to compare the read data from the Flash with User-specified data.
   param[in]     : pt_AddBuf     (Address of the read data)
   param[in]     : pt_CompareBuf (Address of the compare data)
   param[in]     : u4_cntTotal   (Length of the compare data)
   return        : FLS_CDD_RSP_NG_BUSY         (Normal end (Complex Driver))
                 : FLS_CDD_RSP_NG_COMPARE  (Comparison error (Complex Driver))
   Note          : -
*****************************************************************************/
FUNC( Fls_Cdd_JobResultType, FLS_CODE ) 
Fls_Drv_CheckCompare(P2CONST( uint8, AUTOMATIC, TYPEDEF )pt_AddBuf, 
                            P2CONST( uint8, AUTOMATIC, TYPEDEF )pt_CompareBuf,
                            uint32 u4_cntTotal)
{
    Fls_Cdd_JobResultType  st_ret;
    uint32          u4_LoopCnt;

    st_ret = FLS_CDD_RSP_OK;
    for( u4_LoopCnt = FLS_DRV_U4_VAL_0; u4_LoopCnt < u4_cntTotal; u4_LoopCnt++ )
    {
        /* It's compared each 1 byte. */
        if( pt_AddBuf[u4_LoopCnt] != pt_CompareBuf[u4_LoopCnt] )
        {
            st_ret = FLS_CDD_RSP_NG_COMPARE;    /* Comparative failure */
            break;
        }
    }
   return(st_ret);
}
#endif /* FLS_CDD_COMPARE_API == STD_ON */

#if ( FLS_CDD_AUTH_DFID_API == STD_ON )
/*****************************************************************************
   Function      : Verify ID Function
   Description   : Function to verify the given ID against the stored reference ID
                   The reference ID is tranferred to the check unit and the comparison
                   result is returned to the calling function. Depending on the comparison result,
                   all further Flash operations will be accepted or rejected by the hardware.
   param[in]     : -
   return        : FLS_DRV_U1_FALSE (False(Flag used within FLS_DRV))
                 : FLS_DRV_U1_TRUE  (True (Flag used within FLS_DRV))
   Note          : -
*****************************************************************************/
FUNC( Fls_FlagType, FLS_CODE )
Fls_Drv_VerifyID(P2CONST( Fls_Cdd_DataFlashIDType, AUTOMATIC, FLS_APPL_CONST ) pt_IDValue)
{
    uint32          u4_regIDST;
    Fls_FlagType    st_ret;

    st_ret = FLS_DRV_U1_TRUE;

    Fls_Drv_WriteMemoryU32(FLS_DRV_U4_REGADD_DFIDIN0, pt_IDValue->DataFlashID0);
    Fls_Drv_WriteMemoryU32(FLS_DRV_U4_REGADD_DFIDIN1, pt_IDValue->DataFlashID1);
    Fls_Drv_WriteMemoryU32(FLS_DRV_U4_REGADD_DFIDIN2, pt_IDValue->DataFlashID2);
    Fls_Drv_WriteMemoryU32(FLS_DRV_U4_REGADD_DFIDIN3, pt_IDValue->DataFlashID3);
    Fls_Drv_WriteMemoryU32(FLS_DRV_U4_REGADD_DFIDIN4, pt_IDValue->DataFlashID4);
    Fls_Drv_WriteMemoryU32(FLS_DRV_U4_REGADD_DFIDIN5, pt_IDValue->DataFlashID5);
    Fls_Drv_WriteMemoryU32(FLS_DRV_U4_REGADD_DFIDIN6, pt_IDValue->DataFlashID6);
    Fls_Drv_WriteMemoryU32(FLS_DRV_U4_REGADD_DFIDIN7, pt_IDValue->DataFlashID7);

    (void)Fls_Drv_ReadMemoryU32(FLS_DRV_U4_REGADD_DFIDIN7); /* Dummy read */ 

    u4_regIDST = Fls_Drv_ReadMemoryU32(FLS_DRV_U4_REGADD_IDST);
    if( (u4_regIDST & FLS_DRV_U4_REGBIT_DFIDR) == FLS_DRV_U4_REGBIT_DFIDR )
    {
        st_ret = FLS_DRV_U1_FALSE;
    }

    return st_ret;

} /* Fls_Drv_VerifyID */
#endif /* FLS_CDD_AUTH_DFID_API == STD_ON */

#if ( FLS_CDD_BLANK_CHECK_API == STD_ON ) || ( FLS_CDD_NOT_BLANK_ADDRESS_API == STD_ON )
/*****************************************************************************
   Function      : Start Blank Check Process Function
   Description   : This function starts a blank check.
   param[in]     : u4_addStart         (Blank Check Start address)
   param[in]     : u4_addEnd           (Blank Check End address)
   param[in]     : pt_AddDest          (Not-Blank Address)
   return        : FLS_DRV_U1_BUSY              (Normal end (Complex Driver))
                 : FLS_DRV_U1_ERR_BLANKCHECK   (Blank check error (Complex Driver))
   Note          : -
*****************************************************************************/
FUNC( Fls_StatusType, FLS_CODE )
Fls_Drv_StartBCOperation( uint32 u4_addStart, uint32 u4_addEnd, Fls_AddressType* pt_AddDest)
{
    Fls_StatusType          st_ret;
    uint32                  u4_regBlankCheck;
    uint32                  u4_addStart_tmp;
    uint32                  u4_addEnd_tmp;

    st_ret      = FLS_DRV_U1_BUSY;

    u4_addStart_tmp = u4_addStart + FLS_BASE_ADDRESS + FLS_DRV_U4_REGADD_BLANKOFFSET;
    u4_addEnd_tmp   = u4_addEnd   + FLS_BASE_ADDRESS + FLS_DRV_U4_REGADD_BLANKOFFSET;

    do
    {
        /* reading of Blank check address of Data Area register */
        u4_regBlankCheck = Fls_Drv_ReadMemoryU32(u4_addEnd_tmp);

        /* FLS_DRV_U4_REGBIT_BLANKCHECK_BLANK bit is confirmed. */
        if( FLS_DRV_U4_REGBIT_BLANKCHECK_BLANK == ( u4_regBlankCheck & FLS_DRV_U4_REGBIT_BLANKCHECK_BLANK ) )
        {
            /* the reading address, declement. */
            u4_addEnd_tmp -= FLS_DRV_U4_ACCESS_SIZE;
        }
        else
        {
            st_ret = FLS_DRV_U1_ERR_BLANKCHECK;    /* Blank check error */
            *pt_AddDest = u4_addEnd_tmp - FLS_DRV_U4_REGADD_BLANKOFFSET - FLS_BASE_ADDRESS;
        }
       
    }
    while( (u4_addStart_tmp < u4_addEnd_tmp) && (st_ret == FLS_DRV_U1_BUSY) );
    
    return st_ret;
}

#endif/* ( ( FLS_CDD_BLANK_CHECK_API == STD_ON ) || ( FLS_CDD_NOT_BLANK_ADDRESS_API == STD_ON ) )  */

#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A8 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A16 )
/*****************************************************************************
   Function      : Fls_Drv_CalculateTargetArea
   Description   : Function to Calculate Target Area for Writing or Erasing
   param[in]     : Fls_AddressType TargetAddress,
   param[in]     : u4_addStart                         (Start address)
   param[in]     : u4_bCnt                             (Length of the address)
   return        : FLS_DRV_U1_AREA_FACI0               (data area 0)
                   FLS_DRV_U1_AREA_FACI1               (data area 1)
                   FLS_DRV_U1_AREA_FACIALL             (data area 0 & 1)
   Note          : -
*****************************************************************************/
FUNC(Fls_DataArea, FLS_CODE)
Fls_Drv_CalculateTargetArea( uint32 u4_addStart, uint32 u4_bCnt )
{
    Fls_DataArea    st_area;

    if( u4_addStart < FLS_DRV_U4_BOUNDARY_ONE_BLOCK_SIZE )
    {
        /* Target area is data area 0 */
        st_area = FLS_DRV_U1_AREA_FACI0;

        /* Check whether data area 1 is target area or not  */
        if((u4_addStart + u4_bCnt) > FLS_DRV_U4_BOUNDARY_ONE_BLOCK_SIZE)
        {
            /* Target area is data area 0 & 1 */
            st_area = FLS_DRV_U1_AREA_FACIALL;
        }
    }
    else
    {
        /* Target area is data area 1 */
        st_area = FLS_DRV_U1_AREA_FACI1;
    }
    return(st_area);
} /* Fls_Drv_CalculateBlankCheckAddr */
#endif


#define FLS_STOP_SEC_CODE
#include <Fls_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/* Version :Date                                                            */
/* [Number] :[Date]                                                         */
/****************************************************************************/

/**** End of File ***********************************************************/
