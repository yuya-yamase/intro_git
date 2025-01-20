/* Startup_c_Revision(v2.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Startup/CODE                                                */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include "Startup_Ucfg.h"
#include "Startup_Local.h"

#include <WdgM.h>

#include "Section.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define STARTUP_CALC_BIT_SHIFT      (2UL)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
static FUNC(void, STARTUP_CODE_FAST) Startup_CopyRomToRam
(
    VAR(uint32, AUTOMATIC) DstAddr[],
    CONST(uint32, AUTOMATIC) SrcAddr[],
    CONST(uint32, AUTOMATIC) SrcEndAddr[],
    VAR(uint8, AUTOMATIC) WdgCtrlFlag,
    VAR(uint8, AUTOMATIC) SyncInstructionFlag
);
static FUNC(void, STARTUP_CODE_FAST) Startup_ClearRam
(
    VAR(uint32, AUTOMATIC) ClrAddr[],
    CONST(uint32, AUTOMATIC) EndAddr[],
    VAR(uint8, AUTOMATIC) WdgCtrlFlag
);
static FUNC(void, STARTUP_CODE_FAST) Startup_InitStackMax (void);
static FUNC(void, STARTUP_CODE_FAST) Startup_WdgTriggerByFlag
(
    VAR(uint8, AUTOMATIC) WdgCtrlFlag
);


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
/* Function Name | Startup_JudgeApCheckData                                   */
/* Description   | Check Ap check data in startup config                      */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Keyword check result                                       */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, STARTUP_CODE_FAST) Startup_JudgeApCheckData (void)
{
    VAR(uint32, AUTOMATIC) i;
    VAR(uint32, AUTOMATIC) j;
    VAR(uint32, AUTOMATIC) Cnt;
    P2CONST(uint32, AUTOMATIC, STARTUP_APPL_CONST) Address;
    P2CONST(Startup_ApCheckConfigType, AUTOMATIC, STARTUP_APPL_CONST) ConfigPtr;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = E_OK;

    /* Get Ap check info num from startup config */
    ConfigPtr = Startup_Cfg_Data.ApCheckDataPtr;

    for( i = 0UL; i < ConfigPtr->ApCheckNum; i++ )
    {
        /* Calc the count to check from starup config */
        /* ApChecksize divided by 4                   */
        Cnt = ConfigPtr->ApCheckInfoPtr[i].ApCheckSize >> STARTUP_CALC_BIT_SHIFT;

        /* Get check address from startup config */
        Address = (uint32 *)(ConfigPtr->ApCheckInfoPtr[i].ApCheckAddress);

        for( j = 0UL; j < Cnt; j++ )
        {
            /* Check if value of target address matches value in startup config */
            if( Address[j] != ConfigPtr->ApCheckInfoPtr[i].ApCheckValue )
            {
                Ret = E_NOT_OK;
                break;
            }
        }

        /* If keyword check detected unmatch, set return value and exit function */
        if( Ret != (Std_ReturnType)E_OK )
        {
            break;
        }
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | Startup_GetApAddress                                       */
/* Description   | Get Ap jump address from startup config                    */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Ap start address                                           */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint32, STARTUP_CODE_FAST) Startup_GetApAddress (void)
{
    VAR(uint32, AUTOMATIC) Address;

    Address = *(uint32 *)(Startup_Cfg_Data.ApJumpAddress);

    return Address;
}

/******************************************************************************/
/* Function Name | Startup_JudgeAddressApCheck                                */
/* Description   | Check address in Ap check info of startup config           */
/* Preconditions |                                                            */
/* Parameters    | [IN] Address : check address                               */
/* Return Value  | Address check result                                       */
/*               |  STARTUP_ADDR_AP                                           */
/*               |  STARTUP_ADDR_NOT_AP                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, STARTUP_CODE_FAST) Startup_JudgeAddressApCheck
(
    VAR(uint32, AUTOMATIC) Address
)
{
    VAR(uint32, AUTOMATIC) i;
    VAR(uint32, AUTOMATIC) CheckAddress;
    VAR(uint32, AUTOMATIC) CheckSize;
    P2CONST(Startup_ApCheckConfigType, AUTOMATIC, STARTUP_APPL_CONST) ConfigPtr;
    VAR(uint8, AUTOMATIC) Ret;

    Ret = STARTUP_ADDR_NOT_AP;

    /* Get Ap check info num from startup config */
    ConfigPtr = Startup_Cfg_Data.ApCheckDataPtr;

    for( i = 0UL; i < ConfigPtr->ApCheckNum; i++ )
    {
        /* Get check address from startup config */
        CheckAddress = ConfigPtr->ApCheckInfoPtr[i].ApCheckAddress;

        /* Get check size from startup config */
        CheckSize = ConfigPtr->ApCheckInfoPtr[i].ApCheckSize;

        /* Check if address exists within area defined in Ap check info */
        /* If address is in defined area, stop checking                 */
        if( ( Address >= CheckAddress ) &&
            ( Address <= ( ( CheckAddress + CheckSize ) - 1UL ) ) ) /* no wrap around */
        {
            Ret = STARTUP_ADDR_AP;
            break;
        }
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | Startup_JudgeAddressApArea                                 */
/* Description   | Check address in Ap area info of startup config            */
/* Preconditions |                                                            */
/* Parameters    | [IN] Address : check address                               */
/* Return Value  | Address check result                                       */
/*               |  STARTUP_ADDR_AP                                           */
/*               |  STARTUP_ADDR_NOT_AP                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, STARTUP_CODE_FAST) Startup_JudgeAddressApArea
(
    VAR(uint32, AUTOMATIC) Address
)
{
    VAR(uint32, AUTOMATIC) i;
    VAR(uint32, AUTOMATIC) AreaAddress;
    VAR(uint32, AUTOMATIC) AreaSize;
    P2CONST(Startup_ApAreaConfigType, AUTOMATIC, STARTUP_APPL_CONST) ConfigPtr;
    VAR(uint8, AUTOMATIC) Ret;

    Ret = STARTUP_ADDR_NOT_AP;

    /* Get Ap area info num from startup config */
    ConfigPtr = Startup_Cfg_Data.ApAreaDataPtr;

    for( i = 0UL; i < ConfigPtr->ApAreaNum; i++ )
    {
        /* Get area address from startup config */
        AreaAddress = ConfigPtr->ApAreaInfoPtr[i].ApAreaAddress;

        /* Get area size from startup config */
        AreaSize = ConfigPtr->ApAreaInfoPtr[i].ApAreaSize;

        /* Check if address exists within area defined in Ap area info */
        /* If address is in defined area, stop checking                */
        if( ( Address >= AreaAddress ) &&
            ( Address <= ( ( AreaAddress + AreaSize ) - 1UL ) ) )   /* no wrap around */
        {
            Ret = STARTUP_ADDR_AP;
            break;
        }
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | Startup_CopyRomToRam1st                                    */
/* Description   | Copy code and data to RAM and initialize bss               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, STARTUP_CODE_FAST) Startup_CopyRomToRam1st (void)
{
    VAR(uint32, AUTOMATIC) i;

    /* Copy .text section info from ROM to RAM */
    for( i = 0UL; i < Section_1stInfo.Text->Num; i++ )
    {
        Startup_CopyRomToRam(Section_1stInfo.Text->Info[i].DstAddr,
                            Section_1stInfo.Text->Info[i].SrcAddr,
                            Section_1stInfo.Text->Info[i].SrcEndAddr,
                            STD_OFF,
                            STD_ON);
    }

    /* Copy .rodata section info from ROM to RAM */
    for( i = 0UL; i < Section_1stInfo.Data->Num; i++ )
    {
        Startup_CopyRomToRam(Section_1stInfo.Data->Info[i].DstAddr,
                            Section_1stInfo.Data->Info[i].SrcAddr,
                            Section_1stInfo.Data->Info[i].SrcEndAddr,
                            STD_OFF,
                            STD_OFF);
    }

    /* Initialize .bss section */
    for( i = 0UL; i < Section_1stInfo.Bss->Num; i++ )
    {
        Startup_ClearRam(Section_1stInfo.Bss->Info[i].Addr,
                        Section_1stInfo.Bss->Info[i].EndAddr,
                        STD_OFF);
    }

    return;
}

/******************************************************************************/
/* Function Name | Startup_CopyRomToRam2nd                                    */
/* Description   | Copy code and data to RAM and initialize bss               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, STARTUP_CODE_FAST) Startup_CopyRomToRam2nd (void)
{
    VAR(uint32, AUTOMATIC) i;

    /* Copy .text section info from ROM to RAM */
    for( i = 0UL; i < Section_2ndInfo.Text->Num; i++ )
    {
        Startup_CopyRomToRam(Section_2ndInfo.Text->Info[i].DstAddr,
                            Section_2ndInfo.Text->Info[i].SrcAddr,
                            Section_2ndInfo.Text->Info[i].SrcEndAddr,
                            STD_ON,
                            STD_ON);
    }

    /* Copy .rodata section info from ROM to RAM */
    for( i = 0UL; i < Section_2ndInfo.Data->Num; i++ )
    {
        Startup_CopyRomToRam(Section_2ndInfo.Data->Info[i].DstAddr,
                            Section_2ndInfo.Data->Info[i].SrcAddr,
                            Section_2ndInfo.Data->Info[i].SrcEndAddr,
                            STD_ON,
                            STD_OFF);
    }

    /* Initialize .bss section */
    for( i = 0UL; i < Section_2ndInfo.Bss->Num; i++ )
    {
        Startup_ClearRam(Section_2ndInfo.Bss->Info[i].Addr,
                        Section_2ndInfo.Bss->Info[i].EndAddr,
                        STD_ON);
    }

    /* Copy vector info from ROM to RAM */
    Startup_CopyRomToRam(Section_VectorData.Ram->DstAddr,
                        Section_VectorData.Ram->SrcAddr,
                        Section_VectorData.Ram->SrcEndAddr,
                        STD_ON,
                        STD_ON);

    /* Initialize download section info */
    for( i = 0UL; i < Section_DlData.Num; i++ )
    {
        Startup_ClearRam(Section_DlData.Info[i].Addr,
                        Section_DlData.Info[i].EndAddr,
                        STD_ON);
    }

    /* Initialize stack area for max use */
    Startup_InitStackMax();

    return;
}

/******************************************************************************/
/* Function Name | Startup_WdgTrigger                                         */
/* Description   | Clear watchdog timer                                       */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, STARTUP_CODE_FAST) Startup_WdgTrigger (void)
{
    WdgM_SetTriggerCondition();
    WdgM_Trigger();

    return;
}


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

/******************************************************************************/
/* Function Name | Startup_CopyRomToRam                                       */
/* Description   | Copy from ROM to RAM                                       */
/* Preconditions |                                                            */
/* Parameters    | [OUT] DstAddr : Copy destination address                   */
/*               | [IN]  SrcAddr : Copy source address                        */
/*               | [IN]  SrcEndAddr : Copy source end address                 */
/*               | [IN]  WdgCtrlFlag : WDG control or not                     */
/*               |        STD_ON                                              */
/*               |        STD_OFF                                             */
/*               | [IN]  SyncInstructionFlag : Sync or not                    */
/*               |        STD_ON                                              */
/*               |        STD_OFF                                             */
/* Return Value  | None                                                       */
/* Notes         | DstAddr, SrcAddr and SrcEndAddr must be 4 byte aligned.    */
/******************************************************************************/
static FUNC(void, STARTUP_CODE_FAST) Startup_CopyRomToRam
(
    VAR(uint32, AUTOMATIC) DstAddr[],
    CONST(uint32, AUTOMATIC) SrcAddr[],
    CONST(uint32, AUTOMATIC) SrcEndAddr[],
    VAR(uint8, AUTOMATIC) WdgCtrlFlag,
    VAR(uint8, AUTOMATIC) SyncInstructionFlag
)
{
    VAR(uint32, AUTOMATIC) Index;
    VAR(uint32, AUTOMATIC) WdgClearNum;
    VAR(uint32, AUTOMATIC) WdgClearMax;

    WdgClearMax = Startup_Cfg_Data.ClearRamBlockSize >> STARTUP_CALC_BIT_SHIFT;
    WdgClearNum = 0UL;
    Index = 0UL;

    Startup_WdgTriggerByFlag(WdgCtrlFlag);

    while( &SrcAddr[Index] < SrcEndAddr )
    {
        if( WdgClearNum > WdgClearMax )
        {
            Startup_WdgTriggerByFlag(WdgCtrlFlag);
            WdgClearNum = 0UL;
        }
        else
        {
            WdgClearNum++;  /* no wrap around */
        }
        DstAddr[Index] = SrcAddr[Index];
        Index++;            /* no wrap around */
    }

    if( ( SyncInstructionFlag == (uint8)STD_ON ) && ( Index != 0UL ) )
    {
        /* Memory to be used in the instruction fetch of the subsequent instruction */
        Startup_MemBarrier32(&DstAddr[Index - 1UL]);
    }

    Startup_WdgTriggerByFlag(WdgCtrlFlag);

    return;
}

/******************************************************************************/
/* Function Name | Startup_ClearRam                                           */
/* Description   | Clear RAM                                                  */
/* Preconditions |                                                            */
/* Parameters    | [OUT] ClrAddr : Clear address                              */
/*               | [IN]  EndAddr : Clear end address                          */
/*               | [IN]  WdgCtrlFlag : WDG control or not                     */
/*               |        STD_ON                                              */
/*               |        STD_OFF                                             */
/* Return Value  | None                                                       */
/* Notes         | ClrAddr and EndAddr must be 4 byte aligned.                */
/******************************************************************************/
static FUNC(void, STARTUP_CODE_FAST) Startup_ClearRam
(
    VAR(uint32, AUTOMATIC) ClrAddr[],
    CONST(uint32, AUTOMATIC) EndAddr[],
    VAR(uint8, AUTOMATIC) WdgCtrlFlag
)
{
    VAR(uint32, AUTOMATIC) Index;
    VAR(uint32, AUTOMATIC) WdgClearNum;
    VAR(uint32, AUTOMATIC) WdgClearMax;

    WdgClearMax = Startup_Cfg_Data.ClearRamBlockSize >> STARTUP_CALC_BIT_SHIFT;
    WdgClearNum = 0UL;
    Index = 0UL;

    Startup_WdgTriggerByFlag(WdgCtrlFlag);

    while( &ClrAddr[Index] < EndAddr )
    {
        if( WdgClearNum > WdgClearMax )
        {
            Startup_WdgTriggerByFlag(WdgCtrlFlag);
            WdgClearNum = 0UL;
        }
        else
        {
            WdgClearNum++;  /* no wrap around */
        }
        ClrAddr[Index] = 0UL;
        Index++;            /* no wrap around */
    }

    Startup_WdgTriggerByFlag(WdgCtrlFlag);

    return;
}

/******************************************************************************/
/* Function Name | Startup_InitStackMax                                       */
/* Description   | Initialize stack area for max use                          */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, STARTUP_CODE_FAST) Startup_InitStackMax (void)
{
    VAR(uint32, AUTOMATIC) i;
    VAR(uint32, AUTOMATIC) LoopEnd;
    VAR(uint32, AUTOMATIC) WdgClearNum;
    VAR(uint32, AUTOMATIC) WdgClearMax;
    P2VAR(uint32, AUTOMATIC, STARTUP_APPL_DATA) ClrAddr;

    /* Initialize stack area for max use                                                 */
    /*                          <lower address>                                          */
    /*                                |                    |                             */
    /*                                |                    |                             */
    /*                 - - - - - - - -|--------------------|- - - - - - - -              */
    /*   Section_StackData.LowAddr ==>| Stack area         | Maxsize                     */
    /*                                | (0 Clear)          | (Section_StackData.MaxSize) */
    /*                                |                    |                             */
    /*                                |                    |                             */
    /*                 - - - - - - - -|--------------------|                             */
    /*                       Min size | (Already cleared)  |                             */
    /*    (Section_StackData.MinSize) |                    |                             */
    /*                 - - - - - - - -|--------------------|- - - - - - - -              */
    /* SP = Section_StackData.Addr ==>|                    |                             */
    /*                                |                    |                             */
    /*                          <higher address>                                         */
    /*                                                                                   */
    WdgClearMax = Startup_Cfg_Data.ClearRamBlockSize >> STARTUP_CALC_BIT_SHIFT;
    WdgClearNum = 0UL;
    ClrAddr = Section_StackData.LowAddr;
    LoopEnd = Section_StackData.MaxSize - Section_StackData.MinSize;    /* no wrap around */
    LoopEnd >>= STARTUP_CALC_BIT_SHIFT;

    Startup_WdgTrigger();

    for( i = 0UL; i < LoopEnd; i++ )
    {
        if( WdgClearNum > WdgClearMax )
        {
            Startup_WdgTrigger();
            WdgClearNum = 0UL;
        }
        else
        {
            WdgClearNum++;  /* no wrap around */
        }

        ClrAddr[i] = 0UL;
    }

    Startup_WdgTrigger();

    return;
}

/******************************************************************************/
/* Function Name | Startup_WdgTriggerByFlag                                   */
/* Description   | Clear watchdog timer                                       */
/* Preconditions |                                                            */
/* Parameters    | [IN] WdgCtrlFlag : WDG control or not                      */
/*               |       STD_ON                                               */
/*               |       STD_OFF                                              */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, STARTUP_CODE_FAST) Startup_WdgTriggerByFlag
(
    VAR(uint8, AUTOMATIC) WdgCtrlFlag
)
{
    if( WdgCtrlFlag == (uint8)STD_ON )
    {
        Startup_WdgTrigger();
    }

    return;
}


#define STARTUP_STOP_SEC_CODE
#include <Startup_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2022/06/07 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

