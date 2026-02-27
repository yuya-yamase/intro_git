/**
 * \file Crypto_82_Hsm_HAL.c
 * \author      PiNTeam
 * \copyright   (c) DENSO KK, 2022
 * 
 * \brief Hardware Abstraction Layer implementation
 * \details Contains hardware specific implementation
*/

/**********************************************************************************************************************\
 * INCLUDES
\**********************************************************************************************************************/

#include "Crypto_82_Hsm_Cfg.h"
#include "SchM_Crypto_82_Hsm.h"
#include "Os.h"

/**********************************************************************************************************************\
 * PRIVATE MACROS
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * PRIVATE TYPE DEFINITIONS
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * PRIVATE VARIABLES
\**********************************************************************************************************************/

#define CRYPTO_82_HSM_START_SEC_VAR_NOINIT_32BIT
#include "Crypto_82_Hsm_MemMap.h"

/**
 * \brief Used to save and restore the Base Priority (BASEPRI) Mask register.
 */

#define CRYPTO_82_HSM_STOP_SEC_VAR_NOINIT_32BIT
#include "Crypto_82_Hsm_MemMap.h"

/**********************************************************************************************************************\
 * PRIVATE FUNCTIONS DECLARATIONS
\**********************************************************************************************************************/

#define CRYPTO_82_HSM_START_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"

/**
 * \brief User defined function for suspending interrupts.
 */
static FUNC(void, CRYPTO_82_HSM_CODE) cryptoSuspendAllInterrupts(void);

/**
 * \brief User defined function for resuming interrupts.
 */
static FUNC(void, CRYPTO_82_HSM_CODE) cryptoResumeAllInterrupts(void);

/**********************************************************************************************************************\
 * PRIVATE FUNCTIONS IMPLEMENTATIONS
\**********************************************************************************************************************/

static FUNC(void, CRYPTO_82_HSM_CODE) cryptoSuspendAllInterrupts(void)
{
    /* -- UserCode Start ------------- */
    
    /* -- UserCode End   ------------- */    
}

static FUNC(void, CRYPTO_82_HSM_CODE) cryptoResumeAllInterrupts(void)
{
    /* -- UserCode Start ------------- */
    
    /* -- UserCode End   ------------- */    
}

/**********************************************************************************************************************\
 * PUBLIC VARIABLES
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * PUBLIC FUNCTIONS IMPLEMENTATIONS
\**********************************************************************************************************************/

FUNC(void, RTE_CODE_SLOW) SchM_Enter_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_INIT_DRIVER_OBJECT(void)
{
    cryptoSuspendAllInterrupts();
}

FUNC(void, RTE_CODE_SLOW) SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_INIT_DRIVER_OBJECT(void)
{
    cryptoResumeAllInterrupts();
}

FUNC(void, RTE_CODE_SLOW) SchM_Enter_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_DRIVER_OBJECT(void)
{
#if (CRYPTO_82_HSM_USER_DEF_EXCLUSIVE_AREA == STD_OFF)
    SuspendAllInterrupts();
#else
    cryptoSuspendAllInterrupts();
#endif
}

FUNC(void, RTE_CODE_SLOW) SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_DRIVER_OBJECT(void)
{
#if (CRYPTO_82_HSM_USER_DEF_EXCLUSIVE_AREA == STD_OFF)
    ResumeAllInterrupts();
#else
    cryptoResumeAllInterrupts();
#endif
}

FUNC(void, RTE_CODE_SLOW) SchM_Enter_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_KEYS(void)
{
#if (CRYPTO_82_HSM_USER_DEF_EXCLUSIVE_AREA == STD_OFF)
    SuspendAllInterrupts();
#else
    cryptoSuspendAllInterrupts();
#endif
}

FUNC(void, RTE_CODE_SLOW) SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_KEYS(void)
{
#if (CRYPTO_82_HSM_USER_DEF_EXCLUSIVE_AREA == STD_OFF)
    ResumeAllInterrupts();
#else
    cryptoResumeAllInterrupts();
#endif
}

#if (CRYPTO_82_HSM_USER_DEF_INIT == STD_OFF)
FUNC(void, RTE_CODE_SLOW) SchM_Enter_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_INIT_LLD(void)
{
    cryptoSuspendAllInterrupts();
}

FUNC(void, RTE_CODE_SLOW) SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_INIT_LLD(void)
{
    cryptoResumeAllInterrupts();
}
#endif /* (CRYPTO_82_HSM_USER_DEF_INIT == STD_OFF) */

FUNC(void, RTE_CODE_SLOW) SchM_Enter_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_QUEUE(void)
{
#if (CRYPTO_82_HSM_USER_DEF_EXCLUSIVE_AREA == STD_OFF)
    SuspendAllInterrupts();
#else
    cryptoSuspendAllInterrupts();
#endif
}

FUNC(void, RTE_CODE_SLOW) SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_QUEUE(void)
{
#if (CRYPTO_82_HSM_USER_DEF_EXCLUSIVE_AREA == STD_OFF)
    ResumeAllInterrupts();
#else
    cryptoResumeAllInterrupts();
#endif
}

#define CRYPTO_82_HSM_STOP_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"
