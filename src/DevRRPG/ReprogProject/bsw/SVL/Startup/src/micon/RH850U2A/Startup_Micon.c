/* Startup_Micon_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Startup/Micon/CODE                                          */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include "Startup_Ucfg.h"
#include "Startup_Micon_Ucfg.h"
#include "Startup_Local.h"
#include "Startup_Micon.h"
#include "Startup_Usr_Micon.h"

#include <UsrSoftIf.h>
#include <Shutdown.h>
#include <EcuM.h>
#include <WdgM.h>
#include <MemErrM.h>
#include <Gpt.h>
#include <Mcu.h>
#include <Port.h>
#include <Wdg.h>
#include <Ecc.h>
#include <Spi.h>
#include <Cdd_Canic.h>

/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/* check result judge */
#if( REPROG_CFG_STAYINBOOT_ENABLE == STD_ON )
#define STARTUP_BIT8_STAYINBOOT         (1UL << 8U)
#endif
#define STARTUP_BIT7_REPROGENTRY        (1UL << 7U)
#define STARTUP_BIT6_USRSOFT_OK         (1UL << 6U)
#define STARTUP_BIT5_KEYWORD_OK         (1UL << 5U)
#define STARTUP_BIT4_RESERVED           (1UL << 4U)
#define STARTUP_BIT3_ECC_RAM_OK         (1UL << 3U)
#define STARTUP_BIT2_RESERVED           (1UL << 2U)
#define STARTUP_BIT1_ECC_ROM_NG_AP      (1UL << 1U)
#define STARTUP_BIT0_ECC_ROM_OK         (1UL << 0U)
#define STARTUP_ALL_BIT_INIT            (0x00000000UL)

#define STARTUP_JUDGE_AP_ENTRY          (STARTUP_BIT6_USRSOFT_OK| \
                                         STARTUP_BIT5_KEYWORD_OK| \
                                         STARTUP_BIT3_ECC_RAM_OK| \
                                         STARTUP_BIT0_ECC_ROM_OK)

#define STARTUP_JUDGE_REPROG_ENTRY_AP   (STARTUP_BIT7_REPROGENTRY| \
                                         STARTUP_BIT6_USRSOFT_OK|  \
                                         STARTUP_BIT5_KEYWORD_OK|  \
                                         STARTUP_BIT3_ECC_RAM_OK|  \
                                         STARTUP_BIT0_ECC_ROM_OK)

#if( REPROG_CFG_STAYINBOOT_ENABLE == STD_ON )
#define STARTUP_JUDGE_STAYINBOOT_ENTRY  (STARTUP_BIT8_STAYINBOOT| \
                                         STARTUP_JUDGE_AP_ENTRY)
#endif

#define WDG_BASE                     ((U4)0xFFBF1000UL) 
#define WDG_REG_WDTB0WDTE            (*(volatile U1*)(WDG_BASE + 0x00UL)) /* WDTB enable register */ 
#define WDG_WDTB0WDTE_VALUE          ((U1)0xACU)                          /* WDTB0 start/restart value */

/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
static FUNC(void, STARTUP_CODE_FAST) Startup_EccInit (void);
static FUNC(void, STARTUP_CODE_FAST) Startup_EccDeInit
(
    VAR(uint8, AUTOMATIC) ResetErrInt
);
static FUNC(void, STARTUP_CODE_FAST) Startup_CheckEcc
(
    P2VAR(uint32, AUTOMATIC, STARTUP_APPL_DATA) CheckedBitmapPtr
);
static FUNC(void, STARTUP_CODE_FAST) Startup_CheckReprogRequest
(
    P2VAR(uint32, AUTOMATIC, STARTUP_APPL_DATA) CheckedBitmapPtr
);
static FUNC(void, STARTUP_CODE_FAST) Startup_GotoAPL
(
    VAR(uint32, AUTOMATIC) ApJumpAddr
);
static FUNC(uint8, STARTUP_CODE_FAST) Startup_ConvBitmap2Bootkind
(
    VAR(uint32, AUTOMATIC) CheckedBitmap
);
static FUNC(void, STARTUP_CODE_FAST) Startup_CheckReprogStart (void);
#if( REPROG_CFG_STAYINBOOT_ENABLE == STD_ON )
static FUNC(Std_ReturnType, STARTUP_CODE_FAST) Startup_JudgeJumpAPL
(
    P2VAR(uint32, AUTOMATIC, STARTUP_APPL_DATA) CheckedBitmapPtr
);
#endif


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define STARTUP_START_SEC_VAR
#include <Startup_MemMap.h>

#define STARTUP_STOP_SEC_VAR
#include <Startup_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define STARTUP_START_SEC_CST
#include <Startup_MemMap.h>

#define STARTUP_STOP_SEC_CST
#include <Startup_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define STARTUP_START_SEC_CODE
#include <Startup_MemMap.h>

/******************************************************************************/
/* Function Name | Startup_JudgeApStart                                       */
/* Description   | Judge Ap jump or reprog start and judge reprog mode        */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Reprog start mode                                          */
/*               |  ECUM_START_AP_ENTRY                                       */
/*               |  ECUM_START_BOOT_ENTRY                                     */
/*               |  ECUM_START_STAYINBOOT_ENTRY                               */
/* Notes         | - This function will never return when starting Ap.        */
/*               | - ECUM_START_STAYINBOOT_ENTRY can be used when             */
/*               |   REPROG_CFG_STAYINBOOT_ENABLE is STD_ON.                  */
/******************************************************************************/
FUNC(uint8, STARTUP_CODE_FAST) Startup_JudgeApStart (void)
{
    VAR(uint32, AUTOMATIC) ApJumpAddr;
    VAR(uint32, AUTOMATIC) CheckedBitmap;
    VAR(uint32, AUTOMATIC) ApVerifyRet;
    VAR(uint8, AUTOMATIC) BootKind;
    VAR(uint8, AUTOMATIC) FuncRet;
    VAR(Std_ReturnType, AUTOMATIC) StdRet;

    WDG_REG_WDTB0WDTE = WDG_WDTB0WDTE_VALUE;
    CheckedBitmap = STARTUP_ALL_BIT_INIT;

    /* Initialize ECC */
    Startup_EccInit();

    /* Check keyword check and get check result */
    StdRet = Startup_JudgeApCheckData();
    if( StdRet == (Std_ReturnType)E_OK )
    {
        /* Set a keyword check ok bit if keyword check result is ok */
        CheckedBitmap = STARTUP_BIT5_KEYWORD_OK;

        ApJumpAddr = Startup_GetApAddress();

        /* Call user defined software destruction check */
        StdRet = UsrSoftIf_CheckDestruction();
        if( StdRet == (Std_ReturnType)E_OK )
        {
            CheckedBitmap = (STARTUP_BIT5_KEYWORD_OK | STARTUP_BIT6_USRSOFT_OK);

            /* On power-on reset, values in backup area are unstable. */
            /* So treat this situation as no Ap reset request.        */
            FuncRet = Startup_CheckPoweronReset();
            if( FuncRet == (uint8)STD_OFF )
            {
                Startup_CheckReprogRequest(&CheckedBitmap);
            }
        }
    }

    /* Clear user defined reprog request */
    UsrSoftIf_ClearEntryRequest();

    /* Check ECC error status */
    Startup_CheckEcc(&CheckedBitmap);

    /* Jump to Ap start address if Ap start condition fits */
    if( CheckedBitmap == STARTUP_JUDGE_AP_ENTRY )
    {
        /* At secure boot, verify that Ap area should be safe for boot. */
        ApVerifyRet = Startup_Usr_VerifyAp();
        if( ApVerifyRet == 0UL )
        {
#if( REPROG_CFG_STAYINBOOT_ENABLE == STD_ON )
            StdRet = Startup_JudgeJumpAPL(&CheckedBitmap);
            if( StdRet == (Std_ReturnType)E_OK )
#endif
            {
                /* no return */
                Startup_GotoAPL(ApJumpAddr);
            }
        }
    }

    /* Notify user of starting Reprog */
    Startup_Usr_PreReprog();

    /* Set reprog boot mode from check result */
    BootKind = Startup_ConvBitmap2Bootkind(CheckedBitmap);

    /* Clear code flash ECC error status */
    Startup_ClearEccRomErrorStatus();

    WDG_REG_WDTB0WDTE = WDG_WDTB0WDTE_VALUE;

    return BootKind;
}

/******************************************************************************/
/* Function Name | Startup_CheckRomErrorAddress                               */
/* Description   | Identification of ROM error location from address          */
/* Preconditions |                                                            */
/* Parameters    | [IN] Address : Check ROM ECC address                       */
/* Return Value  | Code flash ECC error status                                */
/*               |  STARTUP_ECC_ROM_NG_AP                                     */
/*               |  STARTUP_ECC_ROM_NG_NOT_AP                                 */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, STARTUP_CODE_FAST) Startup_CheckRomErrorAddress
(
    VAR(uint32, AUTOMATIC) Address
)
{
    VAR(uint8, AUTOMATIC) AddressCheck;
    VAR(uint8, AUTOMATIC) Ret;

    Ret = STARTUP_ECC_ROM_NG_AP;

    /* Check if error address is in Ap check info defined in startup config */
    AddressCheck = Startup_JudgeAddressApCheck(Address);
    if( AddressCheck != STARTUP_ADDR_AP )
    {
        /* Check if error address is in Ap area info defined in startup config */
        AddressCheck = Startup_JudgeAddressApArea(Address);
        if( AddressCheck != STARTUP_ADDR_AP )
        {
            /* Error address is not in Ap area info */
            Ret = STARTUP_ECC_ROM_NG_NOT_AP;
        }
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | Startup_PreGearUp                                          */
/* Description   | Settings before gear up                                    */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, STARTUP_CODE_FAST) Startup_PreGearUp (void)
{
    VAR(Std_ReturnType, AUTOMATIC) StdRet;

    StdRet = Startup_StandbyInit();
    if( StdRet != (Std_ReturnType)E_OK )
    {
        /* no return */
        Shutdown_ResetMcu();
    }

    /* Initialize reset reason */
    Startup_ClearResetFactor();

    /* Set vector(ROM) */
    Startup_SetVector(STARTUP_VECT_ROM);

    return;
}

/******************************************************************************/
/* Function Name | Startup_SetGearUp                                          */
/* Description   | Initialize MCAL and set cpu clock                          */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, STARTUP_CODE_FAST) Startup_SetGearUp (void)
{
    VAR(uint32, AUTOMATIC) i;
    P2CONST(Startup_InitCfgConfigType, AUTOMATIC, STARTUP_APPL_CONST) InitConfigPtr;
    VAR(Mcu_PllStatusType, AUTOMATIC) PllRet;
    VAR(Std_ReturnType, AUTOMATIC) StdRet;

    InitConfigPtr = Startup_Cfg_Data.InitCfgDataPtr;

    WDG_REG_WDTB0WDTE = WDG_WDTB0WDTE_VALUE;

    /* Copy MCAL, Sys, and others from ROM to RAM for gear up and initialize bss area */
    Startup_CopyRomToRam1st();

    /* Clear ECU error state */
    EcuM_ClearReportError();

    /* Initialize MCU of MCAL */
    Mcu_Init(InitConfigPtr->McuConfigTypePtr);

    StdRet = Mcu_InitClock(MCU_CLOCKSETTING_ID);
    if( StdRet != (Std_ReturnType)E_OK )
    {
        /* If MCU init failed, so reset MCU(no return) */
        Shutdown_ResetMcu();
    }

    /* Initialize PLL if PLL use setting in startup config */
    if( InitConfigPtr->McuConfigTypePtr->ClockCommon->PllUse == (U1)STD_ON )
    {
        /* Setup PLL and wait for locked state */
        PllRet = MCU_PLL_STATUS_UNDEFINED;
        for( i = 0UL; i < Startup_Cfg_Data.PllLockCheckMaxNum; i++ )
        {
            PllRet = Mcu_GetPllStatus();
            if( PllRet == MCU_PLL_LOCKED )
            {
                break;
            }
        }

        if( PllRet != MCU_PLL_LOCKED )
        {
            /* PLL setting failed, so reset(no return) */
            Shutdown_ResetMcu();
        }

        /* Distribute PLL clock */
        StdRet = Mcu_DistributePllClock();
        if( StdRet != (Std_ReturnType)E_OK )
        {
            /* If PLL distribution failed, so reset MCU(no return) */
            Shutdown_ResetMcu();
        }
    }

    /* Initialize MCAL */
    Spi_Init1();

    Gpt_Init(InitConfigPtr->GptConfigTypePtr);

    Spi_PrePortInit();

    Port_Init(NULL_PTR);

    WDG_REG_WDTB0WDTE = WDG_WDTB0WDTE_VALUE;
//    Wdg_Init(InitConfigPtr->WdgConfigTypePtr);
    Cdd_Canic_Init();

    WDG_REG_WDTB0WDTE = WDG_WDTB0WDTE_VALUE;
    WdgM_Init(InitConfigPtr->WdgMConfigTypePtr);

    StdRet = EcuM_CheckError();
    if( StdRet != (Std_ReturnType)E_OK )
    {
        /* If MCAL initialization failed, so reset MCU(no return) */
        Shutdown_ResetMcu();
    }

    return;
}

/******************************************************************************/
/* Function Name | Startup_ReprogStart                                        */
/* Description   | Start reprog                                               */
/* Preconditions |                                                            */
/* Parameters    | [IN] BootKind : Reprog start mode                          */
/*               |  ECUM_START_AP_ENTRY                                       */
/*               |  ECUM_START_BOOT_ENTRY                                     */
/*               |  ECUM_START_STAYINBOOT_ENTRY                               */
/* Return Value  | None                                                       */
/* Notes         | ECUM_START_STAYINBOOT_ENTRY can be used when               */
/*               | REPROG_CFG_STAYINBOOT_ENABLE is STD_ON.                    */
/******************************************************************************/
FUNC(void, STARTUP_CODE_FAST) Startup_ReprogStart
(
    VAR(uint8, AUTOMATIC) BootKind
)
{
    /* Copy all units from ROM to RAM on demand */
    /* and initialize stack for max use         */
    Startup_CopyRomToRam2nd();
    Startup_WdgTrigger();

    /* Initialize HW */
    Startup_InitHw();
    Startup_WdgTrigger();

    Startup_Usr_InitHw();
    Startup_WdgTrigger();

    /* Set vector(RAM) */
    Startup_SetVector(STARTUP_VECT_RAM);
    Startup_WdgTrigger();

    /* Set boot mode for EcuM unit */
    EcuM_SetBootMode(BootKind);
    Startup_WdgTrigger();

    /* Check reprog start condition */
    Startup_CheckReprogStart();
    Startup_WdgTrigger();

    /* Set ECC to reset value */
    Startup_EccDeInit(STD_OFF);
    Startup_WdgTrigger();

    /* Initialize ECC using MCAL */
    Ecc_Init();
    Startup_WdgTrigger();

    MemErrM_Init();
    Startup_WdgTrigger();

    return;
}


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

/******************************************************************************/
/* Function Name | Startup_EccInit                                            */
/* Description   | Initialize ECC for code flash and RAM                      */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, STARTUP_CODE_FAST) Startup_EccInit (void)
{
    Startup_EccRomInit();
    Startup_EccRamInit();

    return;
}

/******************************************************************************/
/* Function Name | Startup_EccDeInit                                          */
/* Description   | Set ECC to reset value                                     */
/* Preconditions |                                                            */
/* Parameters    | [IN] ResetErrInt : Reset ERRINT register or not            */
/*               |  STD_ON                                                    */
/*               |  STD_OFF                                                   */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, STARTUP_CODE_FAST) Startup_EccDeInit
(
    VAR(uint8, AUTOMATIC) ResetErrInt
)
{
    Startup_EccRamDeInit(ResetErrInt);
    Startup_EccRomDeInit(ResetErrInt);

    return;
}

/******************************************************************************/
/* Function Name | Startup_CheckEcc                                           */
/* Description   | Check ECC and reset when unrecoverable error happended     */
/* Preconditions |                                                            */
/* Parameters    | [INOUT] CheckedBitmapPtr : Pointer to check result bitmap  */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, STARTUP_CODE_FAST) Startup_CheckEcc
(
    P2VAR(uint32, AUTOMATIC, STARTUP_APPL_DATA) CheckedBitmapPtr
)
{
    VAR(uint8, AUTOMATIC) FuncRet;

    FuncRet = Startup_GetEccRomErrorStatus();
    if( FuncRet == STARTUP_ECC_ROM_OK )
    {
        *CheckedBitmapPtr |= STARTUP_BIT0_ECC_ROM_OK;
    }
    else if( FuncRet == STARTUP_ECC_ROM_NG_AP )
    {
        *CheckedBitmapPtr |= STARTUP_BIT1_ECC_ROM_NG_AP;
    }
    else
    {
        /* no return */
        Shutdown_ResetMcu();
    }

    FuncRet = Startup_GetEccRamErrorStatus();
    if( FuncRet == STARTUP_ECC_RAM_OK )
    {
        *CheckedBitmapPtr |= STARTUP_BIT3_ECC_RAM_OK;
    }
    else
    {
        /* no return */
        Shutdown_ResetMcu();
    }

    return;
}

/******************************************************************************/
/* Function Name | Startup_CheckReprogRequest                                 */
/* Description   | Check startup request                                      */
/* Preconditions |                                                            */
/* Parameters    | [INOUT] CheckedBitmapPtr : Pointer to check result bitmap  */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, STARTUP_CODE_FAST) Startup_CheckReprogRequest
(
    P2VAR(uint32, AUTOMATIC, STARTUP_APPL_DATA) CheckedBitmapPtr
)
{
    VAR(uint8, AUTOMATIC) FuncRet;

    /* Call user defined reprog request check */
    FuncRet = UsrSoftIf_GetEntryRequest();
    if( FuncRet == USRSOFTIF_RPGENTRY )
    {
#if ( REPROG_CFG_REPROG_RICOVERY_ONLY == STD_ON )
        *CheckedBitmapPtr = STARTUP_ALL_BIT_INIT;
#else
        *CheckedBitmapPtr |= STARTUP_BIT7_REPROGENTRY;
#endif
    }

    return;
}

/******************************************************************************/
/* Function Name | Startup_GotoAPL                                            */
/* Description   | Prepare for APL jump and goto APL                          */
/* Preconditions |                                                            */
/* Parameters    | [IN] ApJumpAddr : Address of APL to jump                   */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, STARTUP_CODE_FAST) Startup_GotoAPL
(
    VAR(uint32, AUTOMATIC) ApJumpAddr
)
{
    /* Set ECC registers to reset value */
    Startup_EccDeInit(STD_ON);

    /* Notify user of starting Ap */
    Startup_Usr_PreAp(ApJumpAddr);

    /* Jump to Ap start address(no return) */
    Startup_JumpApCore(ApJumpAddr);

    return;
}

/******************************************************************************/
/* Function Name | Startup_ConvBitmap2Bootkind                                */
/* Description   | Convert boot kind for EcuM_SetBootMode                     */
/* Preconditions |                                                            */
/* Parameters    | [IN] CheckedBitmap : Result of jump APL condition check    */
/* Return Value  | Reprog start mode                                          */
/*               |  ECUM_START_AP_ENTRY                                       */
/*               |  ECUM_START_BOOT_ENTRY                                     */
/*               |  ECUM_START_STAYINBOOT_ENTRY                               */
/* Notes         | ECUM_START_STAYINBOOT_ENTRY can be used when               */
/*               | REPROG_CFG_STAYINBOOT_ENABLE is STD_ON.                    */
/******************************************************************************/
static FUNC(uint8, STARTUP_CODE_FAST) Startup_ConvBitmap2Bootkind
(
    VAR(uint32, AUTOMATIC) CheckedBitmap
)
{
    VAR(uint8, AUTOMATIC) BootKind;

    if( CheckedBitmap == STARTUP_JUDGE_REPROG_ENTRY_AP )
    {
        BootKind = ECUM_START_AP_ENTRY;
    }
#if( REPROG_CFG_STAYINBOOT_ENABLE == STD_ON )
    else if( CheckedBitmap == STARTUP_JUDGE_STAYINBOOT_ENTRY )
    {
        BootKind = ECUM_START_STAYINBOOT_ENTRY;
    }
#endif
    else
    {
        BootKind = ECUM_START_BOOT_ENTRY;
    }

    return BootKind;
}

/******************************************************************************/
/* Function Name | Startup_CheckReprogStart                                   */
/* Description   | Check ECC error and MCAL error before starting reprog      */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, STARTUP_CODE_FAST) Startup_CheckReprogStart (void)
{
    VAR(uint8, AUTOMATIC) FuncRet;
    VAR(Std_ReturnType, AUTOMATIC) StdRet;

    FuncRet = Startup_GetEccRomErrorStatus();
    if( ( FuncRet != STARTUP_ECC_ROM_OK ) && ( FuncRet != STARTUP_ECC_ROM_NG_AP ) )
    {
        /* no return */
        Shutdown_ResetMcu();
    }

    FuncRet = Startup_GetEccRamErrorStatus();
    if( FuncRet != STARTUP_ECC_RAM_OK )
    {
        /* no return */
        Shutdown_ResetMcu();
    }

    StdRet = EcuM_CheckError();
    if( StdRet != (Std_ReturnType)E_OK )
    {
        /* no return */
        Shutdown_ResetMcu();
    }

    return;
}

#if( REPROG_CFG_STAYINBOOT_ENABLE == STD_ON )
/******************************************************************************/
/* Function Name | Startup_JudgeJumpAPL                                       */
/* Description   | Judge whether to jump to APL or not                        */
/* Preconditions |                                                            */
/* Parameters    | [INOUT] CheckedBitmapPtr : Pointer to check result bitmap  */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | This function can be used when                             */
/*               | REPROG_CFG_STAYINBOOT_ENABLE is STD_ON.                    */
/******************************************************************************/
static FUNC(Std_ReturnType, STARTUP_CODE_FAST) Startup_JudgeJumpAPL
(
    P2VAR(uint32, AUTOMATIC, STARTUP_APPL_DATA) CheckedBitmapPtr
)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret;
    VAR(uint8, AUTOMATIC) FuncRet;

    Ret = E_NOT_OK;

    FuncRet = Startup_Usr_CheckEntryStayInBoot();

    Startup_CheckEcc(CheckedBitmapPtr);
    if( *CheckedBitmapPtr == STARTUP_JUDGE_AP_ENTRY )
    {
        if( FuncRet == STARTUP_STAYINBOOT_NOT_ENTRY )
        {
            Ret = E_OK;
        }
        else
        {
            *CheckedBitmapPtr = (STARTUP_BIT8_STAYINBOOT | STARTUP_JUDGE_AP_ENTRY);
            Startup_Usr_PreStayInBoot();
        }
    }

    return Ret;
}
#endif


#define STARTUP_STOP_SEC_CODE
#include <Startup_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/10/04 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

