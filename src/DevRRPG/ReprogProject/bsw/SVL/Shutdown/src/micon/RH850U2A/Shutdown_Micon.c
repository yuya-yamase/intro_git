/* Shutdown_Micon_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Shutdown/Micon/CODE                                         */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <Shutdown.h>
#include "Shutdown_Reg.h"
#include "Shutdown_Local.h"
#include "Shutdown_Micon.h"
#include "Shutdown_Usr_Micon.h"

#include <Gpt.h>
#include <Wdg.h>
#include <Mcu.h>
#include <WdgM.h>
#include <MemErrM.h>
#include <Vect.h>
#include <Port.h>
#include <Ecc.h>

#include "Section.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/* Register access */
#define SHUTDOWN_REG_WRITE32(addr, data)    (*((volatile uint32 *)(addr)) = (data))
#define SHUTDOWN_REG_READ32(addr)           (*((volatile uint32 *)(addr)))


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
static FUNC(void, SHUTDOWN_CODE_FAST) Shutdown_DeInitHw (void);
static FUNC(void, SHUTDOWN_CODE_FAST) Shutdown_EccDeInit (void);
static FUNC(void, SHUTDOWN_CODE_FAST) Shutdown_SetVector (void);


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
/* Function Name | Shutdown_ResetRequest                                      */
/* Description   | Request shutdown                                           */
/* Preconditions |                                                            */
/* Parameters    | [IN] ResetMode : Reset mode                                */
/* Return Value  | None                                                       */
/* Notes         | This function will never return.                           */
/******************************************************************************/
FUNC(void, SHUTDOWN_CODE_SLOW) Shutdown_ResetRequest
(
    VAR(uint8, AUTOMATIC) ResetMode
)
{
#if( REPROG_CFG_STAYINBOOT_ENABLE == STD_ON )
    VAR(uint8, AUTOMATIC) State;
    VAR(uint8, AUTOMATIC) RewriteCompFlg;
#endif

    Shutdown_DI();
    Shutdown_WdgTrigger();

    MemErrM_DeInit();
    Shutdown_WdgTrigger();

    Ecc_DeInit();
    Shutdown_WdgTrigger();

    Shutdown_EccDeInit();
    Shutdown_WdgTrigger();

    /* Request SubCore to shutdown */
    Shutdown_Usr_RequestSubCore();
    Shutdown_WdgTrigger();

#if( REPROG_CFG_STAYINBOOT_ENABLE == STD_ON )
    RewriteCompFlg = SchM_GetRewriteCompFlg();
    State = SchM_GetStayInBootState();
    if( State != SCHM_STATE_STAYINBOOT_TMO )
#endif
    {
        Shutdown_ClearRamUnused();
        Shutdown_WdgTrigger();
    }

    /* Set vector(ROM) */
    Shutdown_SetVector();
    Shutdown_WdgTrigger();

    Shutdown_Usr_DeInitHw();
    Shutdown_WdgTrigger();

    Shutdown_DeInitHw();
    Shutdown_WdgTrigger();

    Shutdown_ClearRam2nd();
    Shutdown_WdgTrigger();

    /* Wait for SubCore to finish shutdown */
    Shutdown_Usr_WaitSubCore();
    Shutdown_WdgTrigger();

    WdgM_DeInit();

    Wdg_DeInit();

    Port_DeInit();

    Gpt_DeInit();

    Mcu_DeInit();

    Shutdown_ClearRam1st();

#if( REPROG_CFG_STAYINBOOT_ENABLE == STD_ON )
    Shutdown_Usr_SetEntryStayInBoot(State, RewriteCompFlg);
#endif

    /* Clear stack and reset(no return) */
    Shutdown_ResetCore(ResetMode);

    return;
}

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

/******************************************************************************/
/* Function Name | Shutdown_DeInitHw                                          */
/* Description   | Initialize register values same as reset value             */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, SHUTDOWN_CODE_FAST) Shutdown_DeInitHw (void)
{
    Shutdown_DeInitHwCore();

    return;
}

/******************************************************************************/
/* Function Name | Shutdown_EccDeInit                                         */
/* Description   | Set ECC to reset value                                     */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, SHUTDOWN_CODE_FAST) Shutdown_EccDeInit (void)
{
    SHUTDOWN_REG_WRITE32(SHUTDOWN_REG_ECCKCPROT, SHUTDOWN_VAL_KCPROT_ENABLE);

    /* Reset value */
    SHUTDOWN_REG_WRITE32(SHUTDOWN_REG_MECCCAP_CRAM_CR_ERRINT, SHUTDOWN_VAL_CR_ERRINT_ON);
    (void)SHUTDOWN_REG_READ32(SHUTDOWN_REG_MECCCAP_CRAM_CR_ERRINT);
    Shutdown_SyncBarrier();

    SHUTDOWN_REG_WRITE32(SHUTDOWN_REG_MECCCAP_LR_PE0CL0_LR0_ERRINT, SHUTDOWN_VAL_LR0_ERRINT_ON);
    (void)SHUTDOWN_REG_READ32(SHUTDOWN_REG_MECCCAP_LR_PE0CL0_LR0_ERRINT);
    Shutdown_SyncBarrier();

    SHUTDOWN_REG_WRITE32(SHUTDOWN_REG_MECCCAP_CFL_CF_ERRINT, SHUTDOWN_VAL_CF_ERRINT_ON);
    (void)SHUTDOWN_REG_READ32(SHUTDOWN_REG_MECCCAP_CFL_CF_ERRINT);
    Shutdown_SyncBarrier();

    SHUTDOWN_REG_WRITE32(SHUTDOWN_REG_ECCKCPROT, SHUTDOWN_VAL_KCPROT_DISABLE);

    return;
}

/******************************************************************************/
/* Function Name | Shutdown_SetVector                                         */
/* Description   | Set vector address                                         */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, SHUTDOWN_CODE_FAST) Shutdown_SetVector (void)
{
    VAR(uint32, AUTOMATIC) Address;

    Address = (uint32)Section_VectorData.Rom->Addr;
    Address |= SHUTDOWN_VAL_EBASE_RINT_DV_ON;
    Vect_SetVectorAddress(Address);

    return;
}


#define SHUTDOWN_STOP_SEC_CODE
#include <Shutdown_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2021/09/14 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

