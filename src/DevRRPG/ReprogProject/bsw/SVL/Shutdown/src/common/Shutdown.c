/* Shutdown_c_Revision(v3.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Shutdown/CODE                                               */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include "Shutdown_Local.h"
#include "Startup_Ucfg.h"
#include "Startup_Local.h"

#include <WdgM.h>

#include "Section.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define SHUTDOWN_CALC_BIT_SHIFT (2UL)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
static FUNC(void, SHUTDOWN_CODE_FAST) Shutdown_ClearRam1
(
    VAR(uint32, AUTOMATIC) ClrAddr[],
    CONST(uint32, AUTOMATIC) SrcAddr[],
    CONST(uint32, AUTOMATIC) SrcEndAddr[],
    VAR(uint8, AUTOMATIC) WdgCtrlFlag
);
static FUNC(void, SHUTDOWN_CODE_FAST) Shutdown_ClearRam2
(
    VAR(uint32, AUTOMATIC) ClrAddr[],
    CONST(uint32, AUTOMATIC) EndAddr[],
    VAR(uint8, AUTOMATIC) WdgCtrlFlag
);
static FUNC(void, SHUTDOWN_CODE_FAST) Shutdown_WdgTriggerByFlag
(
    VAR(uint8, AUTOMATIC) WdgCtrlFlag
);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define SHUTDOWN_START_SEC_VAR
#include <Shutdown_MemMap.h>

#define SHUTDOWN_STOP_SEC_VAR
#include <Shutdown_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define SHUTDOWN_START_SEC_CST
#include <Shutdown_MemMap.h>

#define SHUTDOWN_STOP_SEC_CST
#include <Shutdown_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define SHUTDOWN_START_SEC_CODE
#include <Shutdown_MemMap.h>

/******************************************************************************/
/* Function Name | Shutdown_ClearRamUnused                                    */
/* Description   | Clear unused RAM section                                   */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, SHUTDOWN_CODE_FAST) Shutdown_ClearRamUnused (void)
{
    VAR(uint32, AUTOMATIC) i;

    /* Clear unused RAM section */
    for( i = 0UL; i < Section_UnusedRamData.Num; i++ )
    {
        Shutdown_ClearRam2(Section_UnusedRamData.Info[i].Addr,
                            Section_UnusedRamData.Info[i].EndAddr,
                            STD_ON);
    }

    return;
}

/******************************************************************************/
/* Function Name | Shutdown_ClearRam2nd                                       */
/* Description   | Clear RAM 2nd section                                      */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, SHUTDOWN_CODE_FAST) Shutdown_ClearRam2nd (void)
{
    VAR(uint32, AUTOMATIC) i;

    /* Clear text section info */
    for( i = 0UL; i < Section_2ndInfo.Text->Num; i++ )
    {
        Shutdown_ClearRam1(Section_2ndInfo.Text->Info[i].DstAddr,
                            Section_2ndInfo.Text->Info[i].SrcAddr,
                            Section_2ndInfo.Text->Info[i].SrcEndAddr,
                            STD_ON);
    }

    /* Clear data section info */
    for( i = 0UL; i < Section_2ndInfo.Data->Num; i++ )
    {
        Shutdown_ClearRam1(Section_2ndInfo.Data->Info[i].DstAddr,
                            Section_2ndInfo.Data->Info[i].SrcAddr,
                            Section_2ndInfo.Data->Info[i].SrcEndAddr,
                            STD_ON);
    }

    /* Clear bss section info */
    for( i = 0UL; i < Section_2ndInfo.Bss->Num; i++ )
    {
        Shutdown_ClearRam2(Section_2ndInfo.Bss->Info[i].Addr,
                            Section_2ndInfo.Bss->Info[i].EndAddr,
                            STD_ON);
    }

    /* Clear vector info */
    Shutdown_ClearRam1(Section_VectorData.Ram->DstAddr,
                        Section_VectorData.Ram->SrcAddr,
                        Section_VectorData.Ram->SrcEndAddr,
                        STD_ON);

    /* Clear download section info */
    for( i = 0UL; i < Section_DlData.Num; i++ )
    {
        Shutdown_ClearRam2(Section_DlData.Info[i].Addr,
                            Section_DlData.Info[i].EndAddr,
                            STD_ON);
    }

    return;
}

/******************************************************************************/
/* Function Name | Shutdown_ClearRam1st                                       */
/* Description   | Clear RAM 1st section                                      */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, SHUTDOWN_CODE_FAST) Shutdown_ClearRam1st (void)
{
    VAR(uint32, AUTOMATIC) i;

    /* Clear text section info */
    for( i = 0UL; i < Section_1stInfo.Text->Num; i++ )
    {
        Shutdown_ClearRam1(Section_1stInfo.Text->Info[i].DstAddr,
                            Section_1stInfo.Text->Info[i].SrcAddr,
                            Section_1stInfo.Text->Info[i].SrcEndAddr,
                            STD_OFF);
    }

    /* Clear data section info */
    for( i = 0UL; i < Section_1stInfo.Data->Num; i++ )
    {
        Shutdown_ClearRam1(Section_1stInfo.Data->Info[i].DstAddr,
                            Section_1stInfo.Data->Info[i].SrcAddr,
                            Section_1stInfo.Data->Info[i].SrcEndAddr,
                            STD_OFF);
    }

    /* Clear bss section info */
    for( i = 0UL; i < Section_1stInfo.Bss->Num; i++ )
    {
        Shutdown_ClearRam2(Section_1stInfo.Bss->Info[i].Addr,
                            Section_1stInfo.Bss->Info[i].EndAddr,
                            STD_OFF);
    }

    return;
}

/******************************************************************************/
/* Function Name | Shutdown_WdgTrigger                                        */
/* Description   | Clear watchdog timer                                       */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, SHUTDOWN_CODE_FAST) Shutdown_WdgTrigger (void)
{
    WdgM_SetTriggerCondition();
    WdgM_Trigger();

    return;
}


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

/******************************************************************************/
/* Function Name | Shutdown_ClearRam1                                         */
/* Description   | Clear RAM                                                  */
/* Preconditions |                                                            */
/* Parameters    | [OUT] ClrAddr : Clear address                              */
/*               |                 = Copy destination address to copy from    */
/*               |                   ROM to RAM                               */
/*               | [IN]  SrcAddr : Clear range calculation address            */
/*               |                 = Copy source address to copy from ROM to  */
/*               |                   RAM                                      */
/*               | [IN]  SrcEndAddr : Clear range calculation address         */
/*               |                    = Copy source end address to copy from  */
/*               |                      ROM to RAM                            */
/*               | [IN]  WdgCtrlFlag : WDG control or not                     */
/*               |        STD_ON                                              */
/*               |        STD_OFF                                             */
/* Return Value  | None                                                       */
/* Notes         | ClrAddr, SrcAddr and SrcEndAddr must be 4 byte aligned.    */
/******************************************************************************/
static FUNC(void, SHUTDOWN_CODE_FAST) Shutdown_ClearRam1
(
    VAR(uint32, AUTOMATIC) ClrAddr[],
    CONST(uint32, AUTOMATIC) SrcAddr[],
    CONST(uint32, AUTOMATIC) SrcEndAddr[],
    VAR(uint8, AUTOMATIC) WdgCtrlFlag
)
{
    VAR(uint32, AUTOMATIC) Index;
    VAR(uint32, AUTOMATIC) WdgClearNum;
    VAR(uint32, AUTOMATIC) WdgClearMax;

    WdgClearMax = Startup_Cfg_Data.ClearRamBlockSize >> SHUTDOWN_CALC_BIT_SHIFT;
    WdgClearNum = 0UL;
    Index = 0UL;

    Shutdown_WdgTriggerByFlag(WdgCtrlFlag);

    while( &SrcAddr[Index] < SrcEndAddr )
    {
        if( WdgClearNum > WdgClearMax )
        {
            Shutdown_WdgTriggerByFlag(WdgCtrlFlag);
            WdgClearNum = 0UL;
        }
        else
        {
            WdgClearNum++;  /* no wrap around */
        }
        ClrAddr[Index] = 0UL;
        Index++;            /* no wrap around */
    }

    Shutdown_WdgTriggerByFlag(WdgCtrlFlag);

    return;
}

/******************************************************************************/
/* Function Name | Shutdown_ClearRam2                                         */
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
static FUNC(void, SHUTDOWN_CODE_FAST) Shutdown_ClearRam2
(
    VAR(uint32, AUTOMATIC) ClrAddr[],
    CONST(uint32, AUTOMATIC) EndAddr[],
    VAR(uint8, AUTOMATIC) WdgCtrlFlag
)
{
    VAR(uint32, AUTOMATIC) Index;
    VAR(uint32, AUTOMATIC) WdgClearNum;
    VAR(uint32, AUTOMATIC) WdgClearMax;

    WdgClearMax = Startup_Cfg_Data.ClearRamBlockSize >> SHUTDOWN_CALC_BIT_SHIFT;
    WdgClearNum = 0UL;
    Index = 0UL;

    Shutdown_WdgTriggerByFlag(WdgCtrlFlag);

    while( &ClrAddr[Index] < EndAddr )
    {
        if( WdgClearNum > WdgClearMax )
        {
            Shutdown_WdgTriggerByFlag(WdgCtrlFlag);
            WdgClearNum = 0UL;
        }
        else
        {
            WdgClearNum++;  /* no wrap around */
        }
        ClrAddr[Index] = 0UL;
        Index++;            /* no wrap around */
    }

    Shutdown_WdgTriggerByFlag(WdgCtrlFlag);

    return;
}

/******************************************************************************/
/* Function Name | Shutdown_WdgTriggerByFlag                                  */
/* Description   | Clear watchdog timer                                       */
/* Preconditions |                                                            */
/* Parameters    | [IN] WdgCtrlFlag : WDG control or not                      */
/*               |       STD_ON                                               */
/*               |       STD_OFF                                              */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, SHUTDOWN_CODE_FAST) Shutdown_WdgTriggerByFlag
(
    VAR(uint8, AUTOMATIC) WdgCtrlFlag
)
{
    if( WdgCtrlFlag == (uint8)STD_ON )
    {
        Shutdown_WdgTrigger();
    }

    return;
}


#define SHUTDOWN_STOP_SEC_CODE
#include <Shutdown_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2018/06/19 :Update                                rel.AUBASS */
/*  v3.00       :2022/06/07 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

