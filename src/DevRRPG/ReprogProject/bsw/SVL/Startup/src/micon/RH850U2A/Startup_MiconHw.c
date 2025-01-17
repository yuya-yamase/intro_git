/* Startup_MiconHw_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Startup/Micon/Hw/CODE                                       */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include "Startup_Reg.h"
#include "Startup_Ucfg.h"
#include "Startup_Micon_Cfg.h"
#include "Startup_Micon_Ucfg.h"
#include "Startup_Micon.h"

#include <Vect.h>
#include <Shutdown.h>

#include "Section.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/* ECC(RAM) error check num */
#define STARTUP_ECCRAMCHECKINFO_NUM     (sizeof(Startup_EccRamCheckInfo) / sizeof(Startup_EccRamCheckInfo[0]))

/* Register access */
#define STARTUP_REG_WRITE32(addr, data) (*((volatile uint32 *)(addr)) = (data))
#define STARTUP_REG_READ32(addr)        (*((volatile uint32 *)(addr)))


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef struct {
    uint32 RegAddr;
    uint32 MaskVal;
} Startup_EccRamCheckInfoType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/


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

static CONST(AB_83_ConstV Startup_EccRamCheckInfoType, STARTUP_CONST) Startup_EccRamCheckInfo[] = {
     { STARTUP_REG_MECCCAP_LR_PE0CL0_LR0_SERSTR,    STARTUP_MASK_LR0_SERSTR }
    ,{ STARTUP_REG_MECCCAP_LR_PE0CL0_LR0_DERSTR,    STARTUP_MASK_LR0_DERSTR }
    ,{ STARTUP_REG_MECCCAP_CRAM_CR_SERSTR,          STARTUP_MASK_CR_SERSTR  }
    ,{ STARTUP_REG_MECCCAP_CRAM_CR_DERSTR,          STARTUP_MASK_CR_DERSTR  }
};

#define STARTUP_STOP_SEC_CST
#include <Startup_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define STARTUP_START_SEC_CODE
#include <Startup_MemMap.h>

/******************************************************************************/
/* Function Name | Startup_CheckPoweronReset                                  */
/* Description   | Check if power on reset or not                             */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Poweron reset state                                        */
/*               |  STD_OFF                                                   */
/*               |  STD_ON                                                    */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, STARTUP_CODE_FAST) Startup_CheckPoweronReset (void)
{
    VAR(uint32, AUTOMATIC) ResfValue;
    VAR(uint8, AUTOMATIC) Ret;

    Ret = STD_OFF;

    ResfValue = STARTUP_REG_READ32(STARTUP_REG_RESET_RESF);
    if( ( ResfValue & STARTUP_MASK_RESET_RESF_PRESF0 ) != 0UL )
    {
        /* Poweron Reset */
        Ret = STD_ON;
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | Startup_ClearResetFactor                                   */
/* Description   | Clear reset factor                                         */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, STARTUP_CODE_FAST) Startup_ClearResetFactor (void)
{
    /* Initialize reset reason */
    STARTUP_REG_WRITE32(STARTUP_REG_RESET_RESFC, STARTUP_VAL_RESET_RESFC_CLEAR);

    return;
}

/******************************************************************************/
/* Function Name | Startup_EccRomInit                                         */
/* Description   | Initialize ECC for code flash                              */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, STARTUP_CODE_FAST) Startup_EccRomInit (void)
{
    STARTUP_REG_WRITE32(STARTUP_REG_ECCKCPROT, STARTUP_VAL_KCPROT_ENABLE);

    /* Ecc disable */
    STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_CFP_PE0CL0_CFPECCCTL, STARTUP_VAL_PE0CL0_CFPECCCTL_OFF);
    (void)STARTUP_REG_READ32(STARTUP_REG_ECCCNT_CFP_PE0CL0_CFPECCCTL);
    Startup_SyncBarrier();

    STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_CFCCL0_CFCECCCTL, STARTUP_VAL_CFCCL0_CFCECCCTL_OFF);
    (void)STARTUP_REG_READ32(STARTUP_REG_ECCCNT_CFCCL0_CFCECCCTL);
    Startup_SyncBarrier();

    if( Startup_Cfg_MiconName == STARTUP_MICON_NAME_RH850U2A16 )
    {
        STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_CFCCL1_CFCECCCTL, STARTUP_VAL_CFCCL1_CFCECCCTL_OFF);
        (void)STARTUP_REG_READ32(STARTUP_REG_ECCCNT_CFCCL1_CFCECCCTL);
        Startup_SyncBarrier();
    }

    /* Status clear */
    Startup_ClearEccRomErrorStatus();

    /* Notification disable */
    STARTUP_REG_WRITE32(STARTUP_REG_MECCCAP_CFL_CF_ERRINT, STARTUP_VAL_CF_ERRINT_OFF);

    /* Ecc enable */
    STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_CFP_PE0CL0_CFPECCCTL, STARTUP_VAL_PE0CL0_CFPECCCTL_ON);
    (void)STARTUP_REG_READ32(STARTUP_REG_ECCCNT_CFP_PE0CL0_CFPECCCTL);
    Startup_SyncBarrier();

    STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_CFCCL0_CFCECCCTL, STARTUP_VAL_CFCCL0_CFCECCCTL_ON);
    (void)STARTUP_REG_READ32(STARTUP_REG_ECCCNT_CFCCL0_CFCECCCTL);
    Startup_SyncBarrier();

    if( Startup_Cfg_MiconName == STARTUP_MICON_NAME_RH850U2A16 )
    {
        STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_CFCCL1_CFCECCCTL, STARTUP_VAL_CFCCL1_CFCECCCTL_ON);
        (void)STARTUP_REG_READ32(STARTUP_REG_ECCCNT_CFCCL1_CFCECCCTL);
        Startup_SyncBarrier();
    }

    STARTUP_REG_WRITE32(STARTUP_REG_ECCKCPROT, STARTUP_VAL_KCPROT_DISABLE);

    return;
}

/******************************************************************************/
/* Function Name | Startup_EccRomDeInit                                       */
/* Description   | Set ECC to reset value for code flash                      */
/* Preconditions |                                                            */
/* Parameters    | [IN] ResetErrInt : Reset ERRINT register or not            */
/*               |  STD_ON                                                    */
/*               |  STD_OFF                                                   */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, STARTUP_CODE_FAST) Startup_EccRomDeInit
(
    VAR(uint8, AUTOMATIC) ResetErrInt
)
{
    STARTUP_REG_WRITE32(STARTUP_REG_ECCKCPROT, STARTUP_VAL_KCPROT_ENABLE);

    /* Ecc disable */
    STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_CFP_PE0CL0_CFPECCCTL, STARTUP_VAL_PE0CL0_CFPECCCTL_OFF);
    (void)STARTUP_REG_READ32(STARTUP_REG_ECCCNT_CFP_PE0CL0_CFPECCCTL);
    Startup_SyncBarrier();

    STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_CFCCL0_CFCECCCTL, STARTUP_VAL_CFCCL0_CFCECCCTL_OFF);
    (void)STARTUP_REG_READ32(STARTUP_REG_ECCCNT_CFCCL0_CFCECCCTL);
    Startup_SyncBarrier();

    if( Startup_Cfg_MiconName == STARTUP_MICON_NAME_RH850U2A16 )
    {
        STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_CFCCL1_CFCECCCTL, STARTUP_VAL_CFCCL1_CFCECCCTL_OFF);
        (void)STARTUP_REG_READ32(STARTUP_REG_ECCCNT_CFCCL1_CFCECCCTL);
        Startup_SyncBarrier();
    }

    /* Status clear */
    Startup_ClearEccRomErrorStatus();

    /* Reset value */
    if( ResetErrInt == (uint8)STD_ON )
    {
        STARTUP_REG_WRITE32(STARTUP_REG_MECCCAP_CFL_CF_ERRINT, STARTUP_VAL_CF_ERRINT_ON);
        (void)STARTUP_REG_READ32(STARTUP_REG_MECCCAP_CFL_CF_ERRINT);
        Startup_SyncBarrier();
    }

    STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_CFP_PE0CL0_CFPECCCTL, STARTUP_VAL_PE0CL0_CFPECCCTL_RESET);
    (void)STARTUP_REG_READ32(STARTUP_REG_ECCCNT_CFP_PE0CL0_CFPECCCTL);
    Startup_SyncBarrier();

    STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_CFCCL0_CFCECCCTL, STARTUP_VAL_CFCCL0_CFCECCCTL_RESET);
    (void)STARTUP_REG_READ32(STARTUP_REG_ECCCNT_CFCCL0_CFCECCCTL);
    Startup_SyncBarrier();

    if( Startup_Cfg_MiconName == STARTUP_MICON_NAME_RH850U2A16 )
    {
        STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_CFCCL1_CFCECCCTL, STARTUP_VAL_CFCCL1_CFCECCCTL_RESET);
        (void)STARTUP_REG_READ32(STARTUP_REG_ECCCNT_CFCCL1_CFCECCCTL);
        Startup_SyncBarrier();
    }

    STARTUP_REG_WRITE32(STARTUP_REG_ECCKCPROT, STARTUP_VAL_KCPROT_DISABLE);

    return;
}

/******************************************************************************/
/* Function Name | Startup_EccRamInit                                         */
/* Description   | Initialize ECC for RAM                                     */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, STARTUP_CODE_FAST) Startup_EccRamInit (void)
{
    STARTUP_REG_WRITE32(STARTUP_REG_ECCKCPROT, STARTUP_VAL_KCPROT_ENABLE);

    /*********************/
    /* Local RAM setting */
    /*********************/
    /* Ecc disable */
    STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_LR_PE0CL0_LRECCCTL, STARTUP_VAL_PE0CL0_LRECCCTL_OFF);
    (void)STARTUP_REG_READ32(STARTUP_REG_ECCCNT_LR_PE0CL0_LRECCCTL);
    Startup_SyncBarrier();

    /* Status clear */
    STARTUP_REG_WRITE32(STARTUP_REG_MECCCAP_LR_PE0CL0_LR0_SSTCLR, STARTUP_VAL_LR0_SSTCLR);
    STARTUP_REG_WRITE32(STARTUP_REG_MECCCAP_LR_PE0CL0_LR0_DSTCLR, STARTUP_VAL_LR0_DSTCLR);
    STARTUP_REG_WRITE32(STARTUP_REG_MECCCAP_LR_PE0CL0_LR0_OVFCLR, STARTUP_VAL_LR0_OVFCLR);

    /* Notification disable */
    STARTUP_REG_WRITE32(STARTUP_REG_MECCCAP_LR_PE0CL0_LR0_ERRINT, STARTUP_VAL_LR0_ERRINT_OFF);

    /* Normal mode */
    STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_LR_PE0CL0_LRECCTSTCTL, STARTUP_VAL_PE0CL0_LRECCTSTCTL_OFF);

    /* Ecc enable */
    STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_LR_PE0CL0_LRECCCTL, STARTUP_VAL_PE0CL0_LRECCCTL_ON);
    (void)STARTUP_REG_READ32(STARTUP_REG_ECCCNT_LR_PE0CL0_LRECCCTL);
    Startup_SyncBarrier();

    /***********************/
    /* Cluster RAM setting */
    /***********************/
    /* Ecc disable */
    STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_CRCCL0_CRCAFCTL, STARTUP_VAL_CRCCL0_CRCAFCTL_OFF);
    (void)STARTUP_REG_READ32(STARTUP_REG_ECCCNT_CRCCL0_CRCAFCTL);
    Startup_SyncBarrier();

    if( Startup_Cfg_MiconName == STARTUP_MICON_NAME_RH850U2A16 )
    {
        STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_CRCCL1_CRCAFCTL, STARTUP_VAL_CRCCL1_CRCAFCTL_OFF);
        (void)STARTUP_REG_READ32(STARTUP_REG_ECCCNT_CRCCL1_CRCAFCTL);
        Startup_SyncBarrier();
    }

    if( (Startup_Cfg_MiconName == STARTUP_MICON_NAME_RH850U2A8) ||
        (Startup_Cfg_MiconName == STARTUP_MICON_NAME_RH850U2A16) )
    {
        STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_CRCCL2_CRCAFCTL, STARTUP_VAL_CRCCL2_CRCAFCTL_OFF);
        (void)STARTUP_REG_READ32(STARTUP_REG_ECCCNT_CRCCL2_CRCAFCTL);
        Startup_SyncBarrier();
    }

    STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_CRCCL3_CRCAFCTL, STARTUP_VAL_CRCCL3_CRCAFCTL_OFF);
    (void)STARTUP_REG_READ32(STARTUP_REG_ECCCNT_CRCCL3_CRCAFCTL);
    Startup_SyncBarrier();

    STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_CRA_CRAECCCTL, STARTUP_VAL_CRA_CRAECCCTL_OFF);
    (void)STARTUP_REG_READ32(STARTUP_REG_ECCCNT_CRA_CRAECCCTL);
    Startup_SyncBarrier();

    /* Status clear */
    STARTUP_REG_WRITE32(STARTUP_REG_MECCCAP_CRAM_CR_SSTCLR, STARTUP_VAL_CR_SSTCLR);
    STARTUP_REG_WRITE32(STARTUP_REG_MECCCAP_CRAM_CR_DSTCLR, STARTUP_VAL_CR_DSTCLR);
    STARTUP_REG_WRITE32(STARTUP_REG_MECCCAP_CRAM_CR_OVFCLR, STARTUP_VAL_CR_OVFCLR);

    /* Notification disable */
    STARTUP_REG_WRITE32(STARTUP_REG_MECCCAP_CRAM_CR_ERRINT, STARTUP_VAL_CR_ERRINT_OFF);

    /* Normal mode */
    STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_CRCCL0_CRCECCTSTCTL, STARTUP_VAL_CRCCL0_CRCECCTSTCTL_OFF);

    if( Startup_Cfg_MiconName == STARTUP_MICON_NAME_RH850U2A16 )
    {
        STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_CRCCL1_CRCECCTSTCTL, STARTUP_VAL_CRCCL1_CRCECCTSTCTL_OFF);
    }

    if( (Startup_Cfg_MiconName == STARTUP_MICON_NAME_RH850U2A8) ||
        (Startup_Cfg_MiconName == STARTUP_MICON_NAME_RH850U2A16) )
    {
        STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_CRCCL2_CRCECCTSTCTL, STARTUP_VAL_CRCCL2_CRCECCTSTCTL_OFF);
    }

    STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_CRCCL3_CRCECCTSTCTL, STARTUP_VAL_CRCCL3_CRCECCTSTCTL_OFF);

    /* Ecc enable */
    STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_CRCCL0_CRCAFCTL, STARTUP_VAL_CRCCL0_CRCAFCTL_ON);
    (void)STARTUP_REG_READ32(STARTUP_REG_ECCCNT_CRCCL0_CRCAFCTL);
    Startup_SyncBarrier();

    if( Startup_Cfg_MiconName == STARTUP_MICON_NAME_RH850U2A16 )
    {
        STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_CRCCL1_CRCAFCTL, STARTUP_VAL_CRCCL1_CRCAFCTL_ON);
        (void)STARTUP_REG_READ32(STARTUP_REG_ECCCNT_CRCCL1_CRCAFCTL);
        Startup_SyncBarrier();
    }

    if( (Startup_Cfg_MiconName == STARTUP_MICON_NAME_RH850U2A8) ||
        (Startup_Cfg_MiconName == STARTUP_MICON_NAME_RH850U2A16) )
    {
        STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_CRCCL2_CRCAFCTL, STARTUP_VAL_CRCCL2_CRCAFCTL_ON);
        (void)STARTUP_REG_READ32(STARTUP_REG_ECCCNT_CRCCL2_CRCAFCTL);
        Startup_SyncBarrier();
    }

    STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_CRCCL3_CRCAFCTL, STARTUP_VAL_CRCCL3_CRCAFCTL_ON);
    (void)STARTUP_REG_READ32(STARTUP_REG_ECCCNT_CRCCL3_CRCAFCTL);
    Startup_SyncBarrier();

    STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_CRA_CRAECCCTL, STARTUP_VAL_CRA_CRAECCCTL_ON);
    (void)STARTUP_REG_READ32(STARTUP_REG_ECCCNT_CRA_CRAECCCTL);
    Startup_SyncBarrier();

    STARTUP_REG_WRITE32(STARTUP_REG_ECCKCPROT, STARTUP_VAL_KCPROT_DISABLE);

    return;
}

/******************************************************************************/
/* Function Name | Startup_EccRamDeInit                                       */
/* Description   | Set ECC to reset value for RAM                             */
/* Preconditions |                                                            */
/* Parameters    | [IN] ResetErrInt : Reset ERRINT register or not            */
/*               |  STD_ON                                                    */
/*               |  STD_OFF                                                   */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, STARTUP_CODE_FAST) Startup_EccRamDeInit
(
    VAR(uint8, AUTOMATIC) ResetErrInt
)
{
    STARTUP_REG_WRITE32(STARTUP_REG_ECCKCPROT, STARTUP_VAL_KCPROT_ENABLE);

    /***********************/
    /* Cluster RAM setting */
    /***********************/
    /* Ecc disable */
    STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_CRCCL0_CRCAFCTL, STARTUP_VAL_CRCCL0_CRCAFCTL_OFF);
    (void)STARTUP_REG_READ32(STARTUP_REG_ECCCNT_CRCCL0_CRCAFCTL);
    Startup_SyncBarrier();

    if( Startup_Cfg_MiconName == STARTUP_MICON_NAME_RH850U2A16 )
    {
        STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_CRCCL1_CRCAFCTL, STARTUP_VAL_CRCCL1_CRCAFCTL_OFF);
        (void)STARTUP_REG_READ32(STARTUP_REG_ECCCNT_CRCCL1_CRCAFCTL);
        Startup_SyncBarrier();
    }

    if( (Startup_Cfg_MiconName == STARTUP_MICON_NAME_RH850U2A8) ||
        (Startup_Cfg_MiconName == STARTUP_MICON_NAME_RH850U2A16) )
    {
        STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_CRCCL2_CRCAFCTL, STARTUP_VAL_CRCCL2_CRCAFCTL_OFF);
        (void)STARTUP_REG_READ32(STARTUP_REG_ECCCNT_CRCCL2_CRCAFCTL);
        Startup_SyncBarrier();
    }

    STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_CRCCL3_CRCAFCTL, STARTUP_VAL_CRCCL3_CRCAFCTL_OFF);
    (void)STARTUP_REG_READ32(STARTUP_REG_ECCCNT_CRCCL3_CRCAFCTL);
    Startup_SyncBarrier();

    STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_CRA_CRAECCCTL, STARTUP_VAL_CRA_CRAECCCTL_OFF);
    (void)STARTUP_REG_READ32(STARTUP_REG_ECCCNT_CRA_CRAECCCTL);
    Startup_SyncBarrier();

    /* Status clear */
    STARTUP_REG_WRITE32(STARTUP_REG_MECCCAP_CRAM_CR_SSTCLR, STARTUP_VAL_CR_SSTCLR);
    STARTUP_REG_WRITE32(STARTUP_REG_MECCCAP_CRAM_CR_DSTCLR, STARTUP_VAL_CR_DSTCLR);
    STARTUP_REG_WRITE32(STARTUP_REG_MECCCAP_CRAM_CR_OVFCLR, STARTUP_VAL_CR_OVFCLR);

    /* Reset value */
    if( ResetErrInt == (uint8)STD_ON )
    {
        STARTUP_REG_WRITE32(STARTUP_REG_MECCCAP_CRAM_CR_ERRINT, STARTUP_VAL_CR_ERRINT_ON);
        (void)STARTUP_REG_READ32(STARTUP_REG_MECCCAP_CRAM_CR_ERRINT);
        Startup_SyncBarrier();
    }

    STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_CRCCL0_CRCECCTSTCTL, STARTUP_VAL_CRCCL0_CRCECCTSTCTL_OFF);

    if( Startup_Cfg_MiconName == STARTUP_MICON_NAME_RH850U2A16 )
    {
        STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_CRCCL1_CRCECCTSTCTL, STARTUP_VAL_CRCCL1_CRCECCTSTCTL_OFF);
    }

    if( (Startup_Cfg_MiconName == STARTUP_MICON_NAME_RH850U2A8) ||
        (Startup_Cfg_MiconName == STARTUP_MICON_NAME_RH850U2A16) )
    {
        STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_CRCCL2_CRCECCTSTCTL, STARTUP_VAL_CRCCL2_CRCECCTSTCTL_OFF);
    }

    STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_CRCCL3_CRCECCTSTCTL, STARTUP_VAL_CRCCL3_CRCECCTSTCTL_OFF);

    STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_CRCCL0_CRCAFCTL, STARTUP_VAL_CRCCL0_CRCAFCTL_ON);
    (void)STARTUP_REG_READ32(STARTUP_REG_ECCCNT_CRCCL0_CRCAFCTL);
    Startup_SyncBarrier();

    if( Startup_Cfg_MiconName == STARTUP_MICON_NAME_RH850U2A16 )
    {
        STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_CRCCL1_CRCAFCTL, STARTUP_VAL_CRCCL1_CRCAFCTL_ON);
        (void)STARTUP_REG_READ32(STARTUP_REG_ECCCNT_CRCCL1_CRCAFCTL);
        Startup_SyncBarrier();
    }

    if( (Startup_Cfg_MiconName == STARTUP_MICON_NAME_RH850U2A8) ||
        (Startup_Cfg_MiconName == STARTUP_MICON_NAME_RH850U2A16) )
    {
        STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_CRCCL2_CRCAFCTL, STARTUP_VAL_CRCCL2_CRCAFCTL_ON);
        (void)STARTUP_REG_READ32(STARTUP_REG_ECCCNT_CRCCL2_CRCAFCTL);
        Startup_SyncBarrier();
    }

    STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_CRCCL3_CRCAFCTL, STARTUP_VAL_CRCCL3_CRCAFCTL_ON);
    (void)STARTUP_REG_READ32(STARTUP_REG_ECCCNT_CRCCL3_CRCAFCTL);
    Startup_SyncBarrier();

    STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_CRA_CRAECCCTL, STARTUP_VAL_CRA_CRAECCCTL_RESET);
    (void)STARTUP_REG_READ32(STARTUP_REG_ECCCNT_CRA_CRAECCCTL);
    Startup_SyncBarrier();

    /*********************/
    /* Local RAM setting */
    /*********************/
    /* Ecc disable */
    STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_LR_PE0CL0_LRECCCTL, STARTUP_VAL_PE0CL0_LRECCCTL_OFF);
    (void)STARTUP_REG_READ32(STARTUP_REG_ECCCNT_LR_PE0CL0_LRECCCTL);
    Startup_SyncBarrier();

    /* Status clear */
    STARTUP_REG_WRITE32(STARTUP_REG_MECCCAP_LR_PE0CL0_LR0_SSTCLR, STARTUP_VAL_LR0_SSTCLR);
    STARTUP_REG_WRITE32(STARTUP_REG_MECCCAP_LR_PE0CL0_LR0_DSTCLR, STARTUP_VAL_LR0_DSTCLR);
    STARTUP_REG_WRITE32(STARTUP_REG_MECCCAP_LR_PE0CL0_LR0_OVFCLR, STARTUP_VAL_LR0_OVFCLR);

    /* Reset value */
    if( ResetErrInt == (uint8)STD_ON )
    {
        STARTUP_REG_WRITE32(STARTUP_REG_MECCCAP_LR_PE0CL0_LR0_ERRINT, STARTUP_VAL_LR0_ERRINT_ON);
        (void)STARTUP_REG_READ32(STARTUP_REG_MECCCAP_LR_PE0CL0_LR0_ERRINT);
        Startup_SyncBarrier();
    }

    STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_LR_PE0CL0_LRECCTSTCTL, STARTUP_VAL_PE0CL0_LRECCTSTCTL_OFF);

    STARTUP_REG_WRITE32(STARTUP_REG_ECCCNT_LR_PE0CL0_LRECCCTL, STARTUP_VAL_PE0CL0_LRECCCTL_RESET);
    (void)STARTUP_REG_READ32(STARTUP_REG_ECCCNT_LR_PE0CL0_LRECCCTL);
    Startup_SyncBarrier();

    STARTUP_REG_WRITE32(STARTUP_REG_ECCKCPROT, STARTUP_VAL_KCPROT_DISABLE);

    return;
}

/******************************************************************************/
/* Function Name | Startup_ClearEccRomErrorStatus                             */
/* Description   | Clear ECC error status for code flash                      */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, STARTUP_CODE_FAST) Startup_ClearEccRomErrorStatus (void)
{
    STARTUP_REG_WRITE32(STARTUP_REG_MECCCAP_CFL_CF_SSTCLR, STARTUP_VAL_CF_SSTCLR);
    STARTUP_REG_WRITE32(STARTUP_REG_MECCCAP_CFL_CF_DSTCLR, STARTUP_VAL_CF_DSTCLR);
    STARTUP_REG_WRITE32(STARTUP_REG_MECCCAP_CFL_CF_OVFCLR, STARTUP_VAL_CF_OVFCLR);
    (void)STARTUP_REG_READ32(STARTUP_REG_MECCCAP_CFL_CF_OVFCLR);
    Startup_SyncBarrier();

    return;
}

/******************************************************************************/
/* Function Name | Startup_GetEccRomErrorStatus                               */
/* Description   | Get code flash ECC status and check address                */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Code flash ECC error status                                */
/*               |  STARTUP_ECC_ROM_OK                                        */
/*               |  STARTUP_ECC_ROM_NG_AP                                     */
/*               |  STARTUP_ECC_ROM_NG_NOT_AP                                 */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, STARTUP_CODE_FAST) Startup_GetEccRomErrorStatus (void)
{
    VAR(uint32, AUTOMATIC) i;
    VAR(uint32, AUTOMATIC) Address;
    VAR(uint32, AUTOMATIC) Status;
    VAR(uint32, AUTOMATIC) Mask;
    VAR(uint8, AUTOMATIC) Ret;

    Ret = STARTUP_ECC_ROM_OK;

    /* Get code flash ECC 1-bit error status */
    Status = STARTUP_REG_READ32(STARTUP_REG_MECCCAP_CFL_CF_SERSTR);
    Status &= STARTUP_MASK_CF_SERSTR;

    /* Check code flash ECC 1-bit error */
    i = 0UL;
    while( Status != 0UL )
    {
        Mask = 1UL << i;
        if( ( Status & Mask ) != 0UL )
        {
            /* ECC 1-bit error found */
            Address = STARTUP_REG_READ32(STARTUP_REG_MECCCAP_CFL_CF_00SEADR + (i * STARTUP_CF_SEADR_STEP)); /* no wrap around */
            Address = STARTUP_GET_CF_ECCADR(Address);

            Ret = Startup_CheckRomErrorAddress(Address);
            if( Ret != STARTUP_ECC_ROM_NG_AP )
            {
                break;
            }
            Status &= ~Mask;
        }
        i++;    /* no wrap around */
    }

    if( Ret != STARTUP_ECC_ROM_NG_NOT_AP )
    {
        /* Get code flash ECC fatal error status */
        Status = STARTUP_REG_READ32(STARTUP_REG_MECCCAP_CFL_CF_DERSTR);

        /* Check code flash ECC fatal error */
        if( ( Status & STARTUP_MASK_CF_DERSTR ) != 0UL )
        {
            Address = STARTUP_REG_READ32(STARTUP_REG_MECCCAP_CFL_CF_00DEADR);
            Address = STARTUP_GET_CF_ECCADR(Address);

            Ret = Startup_CheckRomErrorAddress(Address);
        }
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | Startup_GetEccRamErrorStatus                               */
/* Description   | Get RAM ECC error status                                   */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | RAM ECC error status                                       */
/*               |  STARTUP_ECC_RAM_OK                                        */
/*               |  STARTUP_ECC_RAM_NG                                        */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, STARTUP_CODE_FAST) Startup_GetEccRamErrorStatus (void)
{
    VAR(uint32, AUTOMATIC) Status;
    VAR(uint8, AUTOMATIC) Ret;
    VAR(uint8, AUTOMATIC) i;

    Ret = STARTUP_ECC_RAM_OK;

    for( i = 0U; i < STARTUP_ECCRAMCHECKINFO_NUM; i++ )
    {
        Status = STARTUP_REG_READ32(Startup_EccRamCheckInfo[i].RegAddr);
        if( ( Status & Startup_EccRamCheckInfo[i].MaskVal ) != 0UL )
        {
            Ret = STARTUP_ECC_RAM_NG;
            break;
        }
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | Startup_SetVector                                          */
/* Description   | Set vector address                                         */
/* Preconditions |                                                            */
/* Parameters    | [IN] VectKind : Kind of Vector(ROM or RAM)                 */
/*               |  STARTUP_VECT_ROM                                          */
/*               |  STARTUP_VECT_RAM                                          */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, STARTUP_CODE_FAST) Startup_SetVector
(
    VAR(uint8, AUTOMATIC) VectKind
)
{
    VAR(uint32, AUTOMATIC) Address;

    if( VectKind == STARTUP_VECT_ROM )
    {
        Address = (uint32)Section_VectorData.Rom->Addr;
    }
    else
    {
        Address = (uint32)Section_VectorData.Ram->DstAddr;
    }

    Address |= STARTUP_VAL_EBASE_RINT_DV_ON;
    Vect_SetVectorAddress(Address);

    return;
}

/******************************************************************************/
/* Function Name | Startup_StandbyInit                                        */
/* Description   | Initialize module standby register                         */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Status                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, STARTUP_CODE_FAST) Startup_StandbyInit (void)
{
    VAR(uint32, AUTOMATIC) i;
    VAR(uint32, AUTOMATIC) Address;
    VAR(uint32, AUTOMATIC) WriteValue;
    VAR(uint32, AUTOMATIC) ReadValue;
    VAR(Std_ReturnType, AUTOMATIC) StdRet;

    StdRet = E_OK;

    STARTUP_REG_WRITE32(STARTUP_REG_MSRKCPROT, STARTUP_VAL_KCPROT_ENABLE);

    for( i = 0UL; i < Startup_Cfg_StandbyData.StandbyNum; i++ )
    {
        Address = Startup_Cfg_StandbyData.StandbyInfoPtr[i].RegAddr;
        WriteValue = Startup_Cfg_StandbyData.StandbyInfoPtr[i].RegVal;
        STARTUP_REG_WRITE32(Address, WriteValue);

        ReadValue = STARTUP_REG_READ32(Address);
        if( ReadValue != WriteValue )
        {
            StdRet = E_NOT_OK;
            break;
        }
    }

    STARTUP_REG_WRITE32(STARTUP_REG_MSRKCPROT, STARTUP_VAL_KCPROT_DISABLE);

    ReadValue = STARTUP_REG_READ32(STARTUP_REG_MSRKCPROT);
    if( ReadValue != 0UL )
    {
        StdRet = E_NOT_OK;
    }

    return StdRet;
}

/******************************************************************************/
/* Function Name | Startup_InitHw                                             */
/* Description   | Initialize MPU/BUS setting                                 */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, STARTUP_CODE_FAST) Startup_InitHw (void)
{
    /* Initialize MPU and others in assembler code */
    Startup_InitHwCore();

    return;
}


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/


#define STARTUP_STOP_SEC_CODE
#include <Startup_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/07/05 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

