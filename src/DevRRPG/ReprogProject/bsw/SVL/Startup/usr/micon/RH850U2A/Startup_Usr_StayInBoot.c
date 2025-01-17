/* Startup_Usr_StayInBoot_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Startup/Usr/StayInBoot/CODE                                 */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include "Startup_Usr_Micon.h"


#if (REPROG_CFG_STAYINBOOT_ENABLE == STD_ON)
/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/*===== Sample ===============================================================*/
/* Type */
#define STARTUP_USR_STAYINBOOT_TYPE_A           (1U)    /* Power on reset only */
#define STARTUP_USR_STAYINBOOT_TYPE_B           (2U)    /* Every reset */
#define STARTUP_USR_STAYINBOOT_TYPE             (STARTUP_USR_STAYINBOOT_TYPE_A)

/* Register */
#define STARTUP_USR_REG_READ32(addr)            (*((volatile uint32 *)(addr)))

#define STARTUP_USR_REG_RESF                    (0xFF988500UL)
#define STARTUP_USR_MASK_RESF_PRESF0            (0x00000001UL)  /* Power on reset */
#define STARTUP_USR_MASK_RESF_HWBISTF0          (0x00001000UL)  /* HW BIST (Field BIST0) Execution Flag */

#define STARTUP_USR_REG_MBISTSIG3               (0xFF9A6024UL)
#define STARTUP_USR_VAL_MBIST3_NOEXE            (0x000555AAUL)

/* RAM */
#define STARTUP_USR_RAM_WRITE32(addr, data)     (*((volatile uint32 *)(addr)) = (data))
#define STARTUP_USR_RAM_READ32(addr)            (*((volatile uint32 *)(addr)))

#define STARTUP_USR_STAYINBOOTFLAG_ADDR         (0xFE80002CUL)  /* Address of StayInBoot flag area */
#define STARTUP_USR_STAYINBOOTFLAG_VAL_NOENTRY  (0xA55A5AA5UL)  /* Value to prevent transition to StayInBoot */
/*===== Sample ===============================================================*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
/*===== Sample ===============================================================*/
typedef struct {
    uint32 RegAddr;
    uint32 RamAddr;
} Startup_Usr_RegBackupInfoType;
/*===== Sample ===============================================================*/


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

/*===== Sample ===============================================================*/
static CONST(AB_83_ConstV Startup_Usr_RegBackupInfoType, STARTUP_CONST) Startup_Usr_RegBackupInfo[] = {
     /* Source(REG),   Destination(RAM) */
     { 0xFF988500UL,   0xFE800030UL }   /* RESF */
    ,{ 0xFF9A4400UL,   0xFE800034UL }   /* BSEQ0ST */
    ,{ 0xFF9A4404UL,   0xFE800038UL }   /* BSEQ0STB */
    ,{ 0xFF9A4408UL,   0xFE80003CUL }   /* BISTST */
    ,{ 0xFF9A6000UL,   0xFE800040UL }   /* LBISTREF1 */
    ,{ 0xFF9A6004UL,   0xFE800044UL }   /* LBISTREF2 */
    ,{ 0xFF9A6008UL,   0xFE800048UL }   /* MBISTREF1 */
    ,{ 0xFF9A600CUL,   0xFE80004CUL }   /* MBISTREF2 */
    ,{ 0xFF9A6010UL,   0xFE800050UL }   /* MBISTREF3 */
    ,{ 0xFF9A6014UL,   0xFE800054UL }   /* LBISTSIG1 */
    ,{ 0xFF9A6018UL,   0xFE800058UL }   /* LBISTSIG2 */
    ,{ 0xFF9A601CUL,   0xFE80005CUL }   /* MBISTSIG1 */
    ,{ 0xFF9A6020UL,   0xFE800060UL }   /* MBISTSIG2 */
    ,{ 0xFF9A6024UL,   0xFE800064UL }   /* MBISTSIG3 */
};
static CONST(AB_83_ConstV uint8, STARTUP_CONST) Startup_Usr_RegBackupInfoNum = (sizeof(Startup_Usr_RegBackupInfo) / sizeof(Startup_Usr_RegBackupInfo[0]));
/*===== Sample ===============================================================*/

#define STARTUP_STOP_SEC_CST
#include <Startup_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define STARTUP_START_SEC_CODE
#include <Startup_MemMap.h>

/******************************************************************************/
/* Function Name | Startup_Usr_CheckEntryStayInBoot                           */
/* Description   | Check whether to transition to StayInBoot or not and       */
/*               | set whether to transition to StayInBoot or not at next     */
/*               | reset                                                      */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Entry request                                              */
/*               |  STARTUP_STAYINBOOT_ENTRY                                  */
/*               |  STARTUP_STAYINBOOT_NOT_ENTRY                              */
/* Notes         | - This function can use stack area with limitations        */
/*               |   specified by Startup unit's configuration.               */
/*               |   The configuration parameters are as follows.             */
/*               |    - STARTUP_UCFG_APCHECK_SP_ADDR                          */
/*               |    - STARTUP_UCFG_APCHECK_SP_SIZE                          */
/*               | - Code before this function call has already consumed a    */
/*               |   few bytes in the stack.                                  */
/*               | - All RAM data except for stack area specified by Startup  */
/*               |   unit's configuration is not initialized.                 */
/*               | - This function can be used when                           */
/*               |   REPROG_CFG_STAYINBOOT_ENABLE is STD_ON.                  */
/******************************************************************************/
FUNC(uint8, STARTUP_CODE_FAST) Startup_Usr_CheckEntryStayInBoot (void)
{
/*===== Sample ===============================================================*/
    VAR(uint32, AUTOMATIC) Value;
    VAR(uint8, AUTOMATIC) Ret;
#if (STARTUP_USR_STAYINBOOT_TYPE == STARTUP_USR_STAYINBOOT_TYPE_B)
    VAR(uint8, AUTOMATIC) Mbist3Flag;
#endif

    Ret = STARTUP_STAYINBOOT_ENTRY;

    Value = STARTUP_USR_REG_READ32(STARTUP_USR_REG_RESF);
    if( ( Value & STARTUP_USR_MASK_RESF_PRESF0 ) == 0UL )
    {
#if (STARTUP_USR_STAYINBOOT_TYPE == STARTUP_USR_STAYINBOOT_TYPE_A)
        Ret = STARTUP_STAYINBOOT_NOT_ENTRY;

#elif (STARTUP_USR_STAYINBOOT_TYPE == STARTUP_USR_STAYINBOOT_TYPE_B)
        Mbist3Flag = STD_OFF;

        if( ( Value & STARTUP_USR_MASK_RESF_HWBISTF0 ) != 0UL )
        {
            /* Field BIST0 was executed */
            Value = STARTUP_USR_REG_READ32(STARTUP_USR_REG_MBISTSIG3);
            if( Value != STARTUP_USR_VAL_MBIST3_NOEXE )
            {
                /* BIST is executed with MBIST scenario 1 */
                Mbist3Flag = STD_ON;
            }
        }

        if( Mbist3Flag == (uint8)STD_OFF )
        {
            Value = STARTUP_USR_RAM_READ32(STARTUP_USR_STAYINBOOTFLAG_ADDR);
            if( Value == STARTUP_USR_STAYINBOOTFLAG_VAL_NOENTRY )
            {
                /* Skip */
                Ret = STARTUP_STAYINBOOT_NOT_ENTRY;
            }
        }
#endif
    }

#if (STARTUP_USR_STAYINBOOT_TYPE == STARTUP_USR_STAYINBOOT_TYPE_B)
    /* Ram clear(= Set to transition to StayInBoot at next reset) */
    STARTUP_USR_RAM_WRITE32(STARTUP_USR_STAYINBOOTFLAG_ADDR, 0UL);
#endif

    return Ret;
/*===== Sample ===============================================================*/
}

/******************************************************************************/
/* Function Name | Startup_Usr_PreStayInBoot                                  */
/* Description   | Preprocessing function before StayInBoot process           */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | - This function can use stack area with limitations        */
/*               |   specified by Startup unit's configuration.               */
/*               |   The configuration parameters are as follows.             */
/*               |    - STARTUP_UCFG_APCHECK_SP_ADDR                          */
/*               |    - STARTUP_UCFG_APCHECK_SP_SIZE                          */
/*               | - Code before this function call has already consumed a    */
/*               |   few bytes in the stack.                                  */
/*               | - All RAM data except for stack area specified by Startup  */
/*               |   unit's configuration is not initialized.                 */
/*               | - This function can be used when                           */
/*               |   REPROG_CFG_STAYINBOOT_ENABLE is STD_ON.                  */
/******************************************************************************/
FUNC(void, STARTUP_CODE_FAST) Startup_Usr_PreStayInBoot (void)
{
/*===== Sample ===============================================================*/
    VAR(uint32, AUTOMATIC) Value;
    VAR(uint32, AUTOMATIC) Reg;
    VAR(uint32, AUTOMATIC) Ram;
    VAR(uint8, AUTOMATIC) i;
    VAR(uint8, AUTOMATIC) TblNum;

    /* The following register values must be used in the ECU software. */
    /* Therefore, this function saves the register value to RAM.       */
    /*  - RESF                                                         */
    /*  - BSEQ0ST, BSEQ0STB, BISTST                                    */
    /*  - LBISTREF1, LBISTREF2                                         */
    /*  - MBISTREF1, MBISTREF2, MBISTREF3                              */
    /*  - LBISTSIG1, LBISTSIG2                                         */
    /*  - MBISTSIG1, MBISTSIG2, MBISTSIG3                              */
    TblNum = Startup_Usr_RegBackupInfoNum;
    for( i = 0U; i < TblNum; i++ )
    {
        Reg = Startup_Usr_RegBackupInfo[i].RegAddr;
        Ram = Startup_Usr_RegBackupInfo[i].RamAddr;

        Value = STARTUP_USR_REG_READ32(Reg);
        STARTUP_USR_RAM_WRITE32(Ram, Value);
    }
/*===== Sample ===============================================================*/

    return;
}


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

#define STARTUP_STOP_SEC_CODE
#include <Startup_MemMap.h>

#endif /* (REPROG_CFG_STAYINBOOT_ENABLE == STD_ON) */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/03/01 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

