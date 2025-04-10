/* bsw_cs_system_exclusive_c_v3-0-0                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CS_SYSTEM/EXCLUSIVE/CODE                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>
#include <cs/bsw_cs_system_memmap_pre.h>
#include <ComStack_Types.h>
#include "../cfg/CS_System_Cfg.h"
#include <cs/bsw_cs_system_memmap_post.h>

#if ( (BSW_CS_SYSTEM_CFG_EXCLUSIVE == BSW_CS_SYSTEM_EXCLUSIVE_SCHM) || (BSW_CS_SYSTEM_CFG_EXCLUSIVE == BSW_CS_SYSTEM_EXCLUSIVE_SEPSCHM) )

#include <SchM_Com.h>

#include <cs/bsw_cs_system_memmap_pre.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

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

/****************************************************************************/
/* Function Name | bsw_cs_system_DI                                         */
/* Description   | Disable Interrupts                                       */
/* Preconditions | Before Disable Interurpt                                 */
/* Parameters    | None                                                     */
/* Return Value  | PSW(Program Status Word) before DI                       */
/* Notes         | None                                                     */
/****************************************************************************/
BswU4
bsw_cs_system_DI( void )
{
    SchM_Enter_Com_All();

    /* Fixed return value of 0UL for SchM nested control */
    return (BswU4)0UL;
}

/****************************************************************************/
/* Function Name | bsw_cs_system_EI                                         */
/* Description   | Enable Interrupts                                        */
/* Preconditions | Before Enable Interrupt                                  */
/* Parameters    | u4Prestat : PSW(Program Status Word) before DI           */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_cs_system_EI( BswU4 u4PreStat )
{
    /* SchM nested control, so u4PreState is not referenced */
    SchM_Exit_Com_All();
}

/****************************************************************************/
/* Function Name | bsw_cs_system_ImmDI                                      */
/* Description   | Disable Interrupts                                       */
/* Preconditions | Before Disable Interurpt                                 */
/* Parameters    | None                                                     */
/* Return Value  | PSW(Program Status Word) before DI                       */
/* Notes         | None                                                     */
/****************************************************************************/
BswU4
bsw_cs_system_ImmDI( void )
{
#if ( BSW_CS_SYSTEM_CFG_EXCLUSIVE == BSW_CS_SYSTEM_EXCLUSIVE_SCHM )
    SchM_Enter_Com_All();
#else /* ( BSW_CS_SYSTEM_CFG_EXCLUSIVE == BSW_CS_SYSTEM_EXCLUSIVE_SEPSCHM ) */
    SchM_Enter_Com_ImmAll();
#endif /* ( BSW_CS_SYSTEM_CFG_EXCLUSIVE ) */
    /* Fixed return value of 0UL for SchM nested control */
    return (BswU4)0UL;
}

/****************************************************************************/
/* Function Name | bsw_cs_system_ImmEI                                      */
/* Description   | Enable Interrupts                                        */
/* Preconditions | Before Enable Interrupt                                  */
/* Parameters    | u4Prestat : PSW(Program Status Word) before DI           */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_cs_system_ImmEI( BswU4 u4PreStat )
{
    /* SchM nested control, so u4PreState is not referenced */
#if ( BSW_CS_SYSTEM_CFG_EXCLUSIVE == BSW_CS_SYSTEM_EXCLUSIVE_SCHM )
    SchM_Exit_Com_All();
#else /* ( BSW_CS_SYSTEM_CFG_EXCLUSIVE == BSW_CS_SYSTEM_EXCLUSIVE_SEPSCHM ) */
    SchM_Exit_Com_ImmAll();
#endif /* ( BSW_CS_SYSTEM_CFG_EXCLUSIVE ) */
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#include <cs/bsw_cs_system_memmap_post.h>

#endif /* ( (BSW_CS_SYSTEM_CFG_EXCLUSIVE == BSW_CS_SYSTEM_EXCLUSIVE_SCHM) || (BSW_CS_SYSTEM_CFG_EXCLUSIVE == BSW_CS_SYSTEM_EXCLUSIVE_SEPSCHM) ) */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/10/17                                             */
/*  v1-0-1          :2018/01/07                                             */
/*  v2-0-0          :2021/12/02                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
