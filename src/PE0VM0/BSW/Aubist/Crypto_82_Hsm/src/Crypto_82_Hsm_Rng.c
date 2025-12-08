/**
 * \file Crypto_82_Hsm_Rng.c
 *
 * \author      PiNTeam
 * \copyright   (c) DENSO KK, 2022
 *
 * \brief Implementation of the RNG module
 *
*/

/**********************************************************************************************************************\
 * INCLUDES
\**********************************************************************************************************************/

#include "Crypto_82_Hsm_Internal.h"
#include "Crypto_82_Hsm_Services.h"

#include "ecy_hsm_csai.h"
#include "ecy_hsm_csai_types.h"
#include "ecy_hsm_csai_rng.h"

/**********************************************************************************************************************\
 * PRIVATE MACROS
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * PRIVATE TYPE DEFINITIONS
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * PUBLIC VARIABLES
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * PRIVATE VARIABLES
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * PRIVATE FUNCTION DECLARATIONS
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * PRIVATE FUNCTION IMPLEMENTATIONS
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * PUBLIC FUNCTION IMPLEMENTATIONS
\**********************************************************************************************************************/

#define CRYPTO_82_HSM_START_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"

FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Rng_Pseudo
(
    P2VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC, CRYPTO_82_HSM_VAR) csaiSession, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) random, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(uint32, AUTOMATIC) random_len
)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) errorCode;

    errorCode = ecy_hsm_Csai_RandomGenerate( csaiSession->hSession, csaiSession->priority, random,
                                             random_len, &(csaiSession->hJob) );

    return errorCode;
}

FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Rng_True
(
    P2VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC, CRYPTO_82_HSM_VAR) csaiSession, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) random, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(uint32, AUTOMATIC) random_len
)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) errorCode;

    errorCode = ecy_hsm_Csai_TrueRandomGenerate( csaiSession->hSession, csaiSession->priority, random,
                                                 random_len, &(csaiSession->hJob) );

    return errorCode;
}

FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Rng_Reseed
(
    P2VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC, CRYPTO_82_HSM_VAR) csaiSession, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) seed,
    VAR(uint32, AUTOMATIC) seed_len
)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) errorCode;

    errorCode = ecy_hsm_Csai_RandomSeedExtend( csaiSession->hSession, csaiSession->priority, seed,
                                               seed_len, &(csaiSession->hJob) );

    return errorCode;
}

#define CRYPTO_82_HSM_STOP_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"
