/* UsrSoftIf_c_Revision(v4.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | UsrSoftIf/CODE                                              */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <UsrSoftIf.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/*===== Sample ===============================================================*/
/* RAM */
#define USRSOFTIF_RAM_WRITE32(addr, data)   (*((volatile uint32 *)(addr)) = (data))
#define USRSOFTIF_RAM_READ32(addr)          (*((volatile uint32 *)(addr)))

#define USRSOFTIF_ENTRYFLAG_ADDR            (0xFE800000UL)  /* Address of the entry flag area */
#define USRSOFTIF_ENTRYFLAG_VAL             (0x5AA5A55AUL)  /* Value of the entry flag area */

/* Register */
#define USRSOFTIF_REG_READ32(addr)          (*((volatile uint32 *)(addr)))

#define USRSOFTIF_REG_RESF                  (0xFF988500UL)
#define USRSOFTIF_MASK_RESF_HWBISTF0        (0x00001000UL)  /* HW BIST (Field BIST0) Execution Flag */

#define USRSOFTIF_REG_MBISTSIG3             (0xFF9A6024UL)
#define USRSOFTIF_VAL_MBIST3_NOEXE          (0x000555AAUL)
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
#define USRSOFTIF_START_SEC1_VAR
#include <UsrSoftIf_MemMap.h>

#define USRSOFTIF_STOP_SEC1_VAR
#include <UsrSoftIf_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define USRSOFTIF_START_SEC1_CST
#include <UsrSoftIf_MemMap.h>

#define USRSOFTIF_STOP_SEC1_CST
#include <UsrSoftIf_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define USRSOFTIF_START_SEC1_CODE
#include <UsrSoftIf_MemMap.h>

/******************************************************************************/
/* Function Name | UsrSoftIf_GetEntryRequest                                  */
/* Description   | Acquire entry request                                      */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Entry request                                              */
/*               |  USRSOFTIF_RPGENTRY                                        */
/*               |  USRSOFTIF_NOENTRY                                         */
/* Notes         | - This function can use stack area with limitations        */
/*               |   specified by Startup unit's configuration.               */
/*               |   The configuration parameters are as follows.             */
/*               |    - STARTUP_UCFG_APCHECK_SP_ADDR                          */
/*               |    - STARTUP_UCFG_APCHECK_SP_SIZE                          */
/*               | - Code before this function call has already consumed a    */
/*               |   few bytes in the stack.                                  */
/*               | - All RAM data except for stack area specified by Startup  */
/*               |   unit's configuration is not initialized.                 */
/******************************************************************************/
FUNC(uint8, USRSOFTIF_CODE_SLOW) UsrSoftIf_GetEntryRequest (void)
{
/*===== Sample ===============================================================*/
    VAR(uint32, AUTOMATIC) Value;
    VAR(uint8, AUTOMATIC) Ret;
    VAR(uint8, AUTOMATIC) Mbist3Flag;

    Ret = USRSOFTIF_NOENTRY;
    Mbist3Flag = STD_OFF;

    Value = USRSOFTIF_REG_READ32(USRSOFTIF_REG_RESF);
    if( ( Value & USRSOFTIF_MASK_RESF_HWBISTF0 ) != 0UL )
    {
        /* Field BIST0 was executed */
        Value = USRSOFTIF_REG_READ32(USRSOFTIF_REG_MBISTSIG3);
        if( Value != USRSOFTIF_VAL_MBIST3_NOEXE )
        {
            /* BIST is executed with MBIST scenario 1 */
            Mbist3Flag = STD_ON;
        }
    }

    if( Mbist3Flag == (uint8)STD_OFF )
    {
        Value = USRSOFTIF_RAM_READ32(USRSOFTIF_ENTRYFLAG_ADDR);
        if( Value == USRSOFTIF_ENTRYFLAG_VAL )
        {
            Ret = USRSOFTIF_RPGENTRY;
        }
    }

    return Ret;
/*===== Sample ===============================================================*/
}

/******************************************************************************/
/* Function Name | UsrSoftIf_ClearEntryRequest                                */
/* Description   | Clear entry request                                        */
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
/******************************************************************************/
FUNC(void, USRSOFTIF_CODE_SLOW) UsrSoftIf_ClearEntryRequest (void)
{
/*===== Sample ===============================================================*/
    USRSOFTIF_RAM_WRITE32(USRSOFTIF_ENTRYFLAG_ADDR, 0UL);
/*===== Sample ===============================================================*/

    return;
}

/******************************************************************************/
/* Function Name | UsrSoftIf_CheckDestruction                                 */
/* Description   | Destruction check                                          */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Status                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | - This function can use stack area with limitations        */
/*               |   specified by Startup unit's configuration.               */
/*               |   The configuration parameters are as follows.             */
/*               |    - STARTUP_UCFG_APCHECK_SP_ADDR                          */
/*               |    - STARTUP_UCFG_APCHECK_SP_SIZE                          */
/*               | - Code before this function call has already consumed a    */
/*               |   few bytes in the stack.                                  */
/*               | - All RAM data except for stack area specified by Startup  */
/*               |   unit's configuration is not initialized.                 */
/******************************************************************************/
FUNC(Std_ReturnType, USRSOFTIF_CODE_SLOW) UsrSoftIf_CheckDestruction (void)
{
/*===== Sample ===============================================================*/
    return E_OK;
/*===== Sample ===============================================================*/
}


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

#define USRSOFTIF_STOP_SEC1_CODE
#include <UsrSoftIf_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2018/06/19 :Update                                rel.AUBASS */
/*  v3.00       :2018/10/23 :Update                                rel.AUBASS */
/*  v4.00       :2021/09/14 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

