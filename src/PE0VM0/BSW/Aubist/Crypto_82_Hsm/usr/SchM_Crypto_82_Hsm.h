/**********************************************************************************************************************
 *             File:  SchM_Crypto_82_Hsm.h
 *********************************************************************************************************************/
#ifndef SCHM_CRYPTO_82_HSM_H
# define SCHM_CRYPTO_82_HSM_H

#include "Std_Types.h"
#include "Crypto_82_Hsm_Cfg.h"
# include "Os.h" /* PRQA S 0828, 0883 */ /* MD_MSR_Dir1.1, MD_Rte_Os */

# define CRYPTO_82_HSM_START_SEC_CODE
# include "Crypto_82_Hsm_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

FUNC(void, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_MainFunction(void); /* PRQA S 3451, 3449 */ /* MD_Rte_3451, MD_Rte_3449 */


FUNC(void, RTE_CODE_SLOW) SchM_Enter_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_INIT_DRIVER_OBJECT(void);
FUNC(void, RTE_CODE_SLOW) SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_INIT_DRIVER_OBJECT(void);
FUNC(void, RTE_CODE_SLOW) SchM_Enter_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_DRIVER_OBJECT(void);
FUNC(void, RTE_CODE_SLOW) SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_DRIVER_OBJECT(void);
FUNC(void, RTE_CODE_SLOW) SchM_Enter_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_KEYS(void);
FUNC(void, RTE_CODE_SLOW) SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_KEYS(void);
FUNC(void, RTE_CODE_SLOW) SchM_Enter_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_QUEUE(void);
FUNC(void, RTE_CODE_SLOW) SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_QUEUE(void);
#if (CRYPTO_82_HSM_USER_DEF_INIT == STD_OFF)
FUNC(void, RTE_CODE_SLOW) SchM_Enter_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_INIT_LLD(void);
FUNC(void, RTE_CODE_SLOW) SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_INIT_LLD(void);
#endif /* (CRYPTO_82_HSM_USER_DEF_INIT == STD_OFF) */

# define CRYPTO_82_HSM_STOP_SEC_CODE
# include "Crypto_82_Hsm_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#endif /* SCHM_CRYPTO_82_HSM_H */


