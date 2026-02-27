/**
 * \file  Hsm_82_CycurHsm_Cfg.h
 * \copyright  DENSO Corporation 2022
*/
#ifndef HSM_82_CYCURHSM_CFG
#define HSM_82_CYCURHSM_CFG

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "Std_Types.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define USR_HSM_MICRO_TC3X                    (0U)
#define USR_HSM_MICRO_RH850                   (1U)
#define USR_HSM_MICRO_T2B                     (2U)

#define USR_HSM_MICRO                         (USR_HSM_MICRO_RH850) /* User Setting */

#if (USR_HSM_MICRO == USR_HSM_MICRO_TC3X)
#define USR_HSM_REG_HF_STATUS                 ( *((volatile uint32*)0xF8040010U) )
#define USR_HSM_REG_HF_STATUS_BITPOS_D0BUSY   ( 0x00000001U )
#define USR_HSM_REG_HF_STATUS_BITPOS_D1BUSY   ( 0x00000002U )
#define USR_HSM_DFBUSY_TIMEOUT                (5000U)   /* User Setting */
#endif

#define USR_HSM_VERSION_V2x                     (0U)
#define USR_HSM_VERSION_V3x                     (1U)

#define USR_HSM_VERSION                       (USR_HSM_VERSION_V2x) /* User Setting */

#define USR_HSM_WAITFORBOOTED_TIMEOUT         (1100U)   /* User Setting */

#define USR_HSM_WAITFORMODEAPPL_DOWHILE       (STD_ON)  /* User Setting */
#if (USR_HSM_WAITFORMODEAPPL_DOWHILE == STD_ON)
#define USR_HSM_WAITFORMODEAPPL_TIMEOUT       (5U)        /* User Setting: Blocking Time for HSM Initializing */
#define USR_HSM_WAITFORMODEAPPL_COUNT         (1000UL)    /* User Setting: Blocking Time for HSM Initializing */
#else
#define USR_HSM_WAITFORMODEAPPL_TIMEOUT       (5000U)   /* User Setting */
#endif

#define USR_HSM_RESETTING_HSMCONF             (STD_OFF)  /* User Setting */

#define USR_HSM_SETTINR_RAM                   (STD_OFF)  /* User Setting */
#if (USR_HSM_SETTINR_RAM == STD_ON)
extern char __ghsbegin_RamCopy_hsm_DstStart[];
extern char __ghsbegin_RamCopy_hsm_SrcStart[];
extern char __ghsbegin_RamCopy_hsm_SrcEnd[];
#define SECTION_RAMCOPY_HSM_DST_ADDR        ((uint32 *)(void *)__ghsbegin_RamCopy_hsm_DstStart)
#define SECTION_RAMCOPY_HSM_SRC_ADDR        ((uint32 *)(void *)__ghsbegin_RamCopy_hsm_SrcStart)
#define SECTION_RAMCOPY_HSM_SRC_END_ADDR    ((uint32 *)(void *)__ghsbegin_RamCopy_hsm_SrcEnd)
#endif

#define USE_NO_CRYPTO_DRIVER                  (0U)
#define USE_CRYPTO_82_HSM                     (1U)

#define USR_CRYPTO_DRIVER                     (USE_CRYPTO_82_HSM) /* User Setting */
#define USR_INITIALKEYREAD_INETEVALTIME       (5UL)     /* User Setting */
#define USR_INITIALKEYREAD_MAXCOUNT           (10UL)    /* User Setting */
#define USR_USE_OSTIMER_ONE                   (STD_OFF) /* User Setting */
#if (USR_USE_OSTIMER_ONE == STD_ON)
#define USR_OSTIMER_ID                        (SystemTimer) /* User Setting from Os configuration */
#endif

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

#if (USR_HSM_SETTINR_RAM == STD_ON)
#pragma ghs section text = ".P_RAM_RPGEVTHK"
extern void Hsm_82_CycurHsm_GetResourceRAM(void);
extern void Hsm_82_CycurHsm_ReleaseResourceRAM(void);
extern void Hsm_82_CycurHsm_GetCounterValueRAM(uint32 * value);
extern void Hsm_82_CycurHsm_GetElapsedCounterValueRAM(uint32 startvalue, uint32 * elapsedvalue);
extern void Hsm_82_CycurHsm_Callout_ErrorRAM(void);
#pragma ghs section text = default
#endif

#define CRYPTO_82_HSM_START_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"

extern void Hsm_82_CycurHsm_GetResource0(void);
extern void Hsm_82_CycurHsm_ReleaseResource0(void);
extern void Hsm_82_CycurHsm_GetCounterValue0(uint32 * value);
extern void Hsm_82_CycurHsm_GetElapsedCounterValue0(uint32 startvalue, uint32 * elapsedvalue);

#if (USR_HSM_RESETTING_HSMCONF == STD_ON)
extern void Hsm_82_CycurHsm_GetResource1(void);
extern void Hsm_82_CycurHsm_ReleaseResource1(void);
extern void Hsm_82_CycurHsm_GetCounterValue1(uint32 * value);
extern void Hsm_82_CycurHsm_GetElapsedCounterValue1(uint32 startvalue, uint32 * elapsedvalue);
#endif

extern void Hsm_82_CycurHsm_Callout_ClockConfig(void);
extern void Hsm_82_CycurHsm_Callout_Error(void);

#if (USR_HSM_WAITFORMODEAPPL_DOWHILE == STD_ON)
extern void Hsm_82_CycurHsm_Callout_WaitForMode(void);
#endif

#if (USR_CRYPTO_DRIVER == USE_CRYPTO_82_HSM)
extern void Hsm_82_CycurHsm_Callout_WaitForInitialKeyRead(void);
#endif

#define CRYPTO_82_HSM_STOP_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif /* HSM_82_CYCURHSM_CFG */

/*--------------------------------------------------------------------------*/
/* History                                                                  */
/*  Version    :Date       :Description                                     */
/*  1.0.0      :yyyy/mm/dd :Create new                xxx                   */
/*--------------------------------------------------------------------------*/
/**** End of File ***********************************************************/
