/* Shutdown_Usr_StayInBoot_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Shutdown/Usr/StayInBoot/CODE                                */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include "Shutdown_Usr_Micon.h"


#if (REPROG_CFG_STAYINBOOT_ENABLE == STD_ON)
/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/*===== Sample ===============================================================*/
/* Type */
#define SHUTDOWN_USR_STAYINBOOT_TYPE_A           (1U)    /* Power on reset only */
#define SHUTDOWN_USR_STAYINBOOT_TYPE_B           (2U)    /* Every reset */
#define SHUTDOWN_USR_STAYINBOOT_TYPE_C           (3U)    /* Every reset(Skip StayInBoot when rewriting is completed) */
#define SHUTDOWN_USR_STAYINBOOT_TYPE_D           (4U)    /* Skip StayInBoot after Reprog shutdown */
#define SHUTDOWN_USR_STAYINBOOT_TYPE             (SHUTDOWN_USR_STAYINBOOT_TYPE_A)

/* Register */
#define SHUTDOWN_USR_REG_WRITE32(addr, data)    (*((volatile uint32 *)(addr)) = (data))

#define SHUTDOWN_USR_REG_RESKCPROT0             (0xFF980F00UL)
#define SHUTDOWN_USR_VAL_RESKCPROT_WE           (0xA5A5A501UL)
#define SHUTDOWN_USR_VAL_RESKCPROT_WD           (0xA5A5A500UL)

#define SHUTDOWN_USR_REG_BSEQ0CTL               (0xFF988400UL)
#define SHUTDOWN_USR_VAL_BSEQ0CTL_BISTSKIP      (0x00000002UL)

/* RAM */
#define SHUTDOWN_USR_RAM_WRITE32(addr, data)    (*((volatile uint32 *)(addr)) = (data))

#define SHUTDOWN_USR_STAYINBOOTFLAG_ADDR        (0xFE80002CUL)  /* Address of StayInBoot flag area */
#define SHUTDOWN_USR_STAYINBOOTFLAG_VAL_NOENTRY (0xA55A5AA5UL)  /* Value to prevent transition to StayInBoot */
/*===== Sample ===============================================================*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/


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
/* Function Name | Shutdown_Usr_SetEntryStayInBoot                            */
/* Description   | Set whether to transition to StayInBoot or not at next     */
/*               | reset                                                      */
/* Preconditions |                                                            */
/* Parameters    | [IN] State : StayInBoot state                              */
/*               |  SHUTDOWN_STATE_BOOT_ENTRY                                 */
/*               |  SHUTDOWN_STATE_AP_ENTRY                                   */
/*               |  SHUTDOWN_STATE_STAYINBOOT_WAIT                            */
/*               |  SHUTDOWN_STATE_STAYINBOOT_TMO                             */
/*               |  SHUTDOWN_STATE_STAYINBOOT_PRGRCV                          */
/*               | [IN] RewriteCompFlg : Rewrite completion flag              */
/*               |  STD_ON                                                    */
/*               |  STD_OFF                                                   */
/* Return Value  | None                                                       */
/* Notes         | This function can be used when                             */
/*               | REPROG_CFG_STAYINBOOT_ENABLE is STD_ON.                    */
/******************************************************************************/
FUNC(void, SHUTDOWN_CODE_FAST) Shutdown_Usr_SetEntryStayInBoot
(
    VAR(uint8, AUTOMATIC) State,
    VAR(uint8, AUTOMATIC) RewriteCompFlg
)
{
/*===== Sample ===============================================================*/
#if( SHUTDOWN_USR_STAYINBOOT_TYPE == SHUTDOWN_USR_STAYINBOOT_TYPE_D )
    /* Ram set(= Set not to transition to StayInBoot at next reset) */
    SHUTDOWN_USR_RAM_WRITE32(SHUTDOWN_USR_STAYINBOOTFLAG_ADDR, SHUTDOWN_USR_STAYINBOOTFLAG_VAL_NOENTRY);
    /* BIST skip */
    SHUTDOWN_USR_REG_WRITE32(SHUTDOWN_USR_REG_RESKCPROT0, SHUTDOWN_USR_VAL_RESKCPROT_WE);
    SHUTDOWN_USR_REG_WRITE32(SHUTDOWN_USR_REG_BSEQ0CTL, SHUTDOWN_USR_VAL_BSEQ0CTL_BISTSKIP);
    SHUTDOWN_USR_REG_WRITE32(SHUTDOWN_USR_REG_RESKCPROT0, SHUTDOWN_USR_VAL_RESKCPROT_WD);
#else
    if( State == SHUTDOWN_STATE_STAYINBOOT_TMO )
    {
 #if( (SHUTDOWN_USR_STAYINBOOT_TYPE == SHUTDOWN_USR_STAYINBOOT_TYPE_B) || (SHUTDOWN_USR_STAYINBOOT_TYPE == SHUTDOWN_USR_STAYINBOOT_TYPE_C) )
        /* Ram set(= Set not to transition to StayInBoot at next reset) */
        SHUTDOWN_USR_RAM_WRITE32(SHUTDOWN_USR_STAYINBOOTFLAG_ADDR, SHUTDOWN_USR_STAYINBOOTFLAG_VAL_NOENTRY);
 #endif
        /* BIST skip */
        SHUTDOWN_USR_REG_WRITE32(SHUTDOWN_USR_REG_RESKCPROT0, SHUTDOWN_USR_VAL_RESKCPROT_WE);
        SHUTDOWN_USR_REG_WRITE32(SHUTDOWN_USR_REG_BSEQ0CTL, SHUTDOWN_USR_VAL_BSEQ0CTL_BISTSKIP);
        SHUTDOWN_USR_REG_WRITE32(SHUTDOWN_USR_REG_RESKCPROT0, SHUTDOWN_USR_VAL_RESKCPROT_WD);
    }
 #if( SHUTDOWN_USR_STAYINBOOT_TYPE == SHUTDOWN_USR_STAYINBOOT_TYPE_C )
    else
    {
        if( RewriteCompFlg == (uint8)STD_ON )
        {
            /* Ram set(= Set not to transition to StayInBoot at next reset) */
            SHUTDOWN_USR_RAM_WRITE32(SHUTDOWN_USR_STAYINBOOTFLAG_ADDR, SHUTDOWN_USR_STAYINBOOTFLAG_VAL_NOENTRY);
            /* BIST skip */
            SHUTDOWN_USR_REG_WRITE32(SHUTDOWN_USR_REG_RESKCPROT0, SHUTDOWN_USR_VAL_RESKCPROT_WE);
            SHUTDOWN_USR_REG_WRITE32(SHUTDOWN_USR_REG_BSEQ0CTL, SHUTDOWN_USR_VAL_BSEQ0CTL_BISTSKIP);
            SHUTDOWN_USR_REG_WRITE32(SHUTDOWN_USR_REG_RESKCPROT0, SHUTDOWN_USR_VAL_RESKCPROT_WD);
        }
    }
 #endif
#endif
/*===== Sample ===============================================================*/

    return;
}


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

#define SHUTDOWN_STOP_SEC_CODE
#include <Shutdown_MemMap.h>

#endif /* (REPROG_CFG_STAYINBOOT_ENABLE == STD_ON) */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/03/01 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

