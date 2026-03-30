/**
 * \file Crypto_82_Hsm_AsymC.c
 * 
 * \author      PiNTeam
 * \copyright   (c) DENSO KK, 2022
 *
 * \brief Implementation of the Asymmetric Cryptography module
 *
*/

/**********************************************************************************************************************\
 * INCLUDES
\**********************************************************************************************************************/

#include "Crypto_82_Hsm_Internal.h"
#include "Crypto_82_Hsm_Services.h"

#include "ecy_hsm_csai.h"
#include "ecy_hsm_csai_types.h"
#include "ecy_hsm_csai_crypt.h"

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

#define CRYPTO_82_HSM_START_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"

/**
 * \brief Mapping for asymmetric cipher modes.
 *
 * \param [in] mode           Crypto Service layer supported asymmetric cipher mode.
 *
 * \return ret_mode           Corresponding asymmetric cipher mode supported by the HSM.
 */
static FUNC(ecy_hsm_Csai_AsymCipherModeT , CRYPTO_82_HSM_CODE) get_asymCipherMode(Crypto_82_Hsm_Service_AsymCipherModeType mode);

/**********************************************************************************************************************\
 * PRIVATE FUNCTION IMPLEMENTATIONS
\**********************************************************************************************************************/

static FUNC(ecy_hsm_Csai_AsymCipherModeT, CRYPTO_82_HSM_CODE) get_asymCipherMode(Crypto_82_Hsm_Service_AsymCipherModeType mode)
{
    ecy_hsm_Csai_AsymCipherModeT ret_mode = ecy_hsm_CSAI_ASYMCIPHER_RESERVED;

    switch (mode)
    {
    case CryptoDriver_RSA_ES_PKCS1_v15:
        ret_mode = ecy_hsm_CSAI_RSA_ES_PKCS1_v15;
        break;
    case CryptoDriver_RSA_ES_OAEP:
        ret_mode = ecy_hsm_CSAI_RSA_ES_OAEP;
        break;
    default:
        ret_mode = ecy_hsm_CSAI_ASYMCIPHER_RESERVED;
        break;
    }

    return ret_mode;
}
/**********************************************************************************************************************\
 * PUBLIC FUNCTION IMPLEMENTATIONS
\**********************************************************************************************************************/

FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_AsymC_Encrypt
(
    P2VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC, CRYPTO_82_HSM_VAR) csaiSession, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(ecy_hsm_Csai_KeyHandleT, AUTOMATIC) hKey,
    VAR(Crypto_82_Hsm_Service_AsymCipherModeType, AUTOMATIC) asymCipherMode,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) msg,
    VAR(uint32, CRYPTO_82_HSM_VAR) msg_len,
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) cipher, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) cipher_len /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) errorCode;
    ecy_hsm_Csai_AsymCipherModeT csai_AsymCipherMode = get_asymCipherMode(asymCipherMode);

    /* Satisfies SWS_Crypto_00135 */
    errorCode = ecy_hsm_Csai_AsymEncrypt( csaiSession->hSession, csaiSession->priority, csai_AsymCipherMode,
                                          hKey, msg, msg_len, cipher, *cipher_len, cipher_len, &(csaiSession->hJob) );

    return errorCode;
}

FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_AsymC_Decrypt
(
    P2VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC, CRYPTO_82_HSM_VAR) csaiSession, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(ecy_hsm_Csai_KeyHandleT, AUTOMATIC) hKey,
    VAR(Crypto_82_Hsm_Service_AsymCipherModeType, AUTOMATIC) asymCipherMode,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) cipher,
    VAR(uint32, CRYPTO_82_HSM_VAR) cipher_len,
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) msg, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) msg_len /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) errorCode;
    ecy_hsm_Csai_AsymCipherModeT csai_AsymCipherMode = get_asymCipherMode(asymCipherMode);

    /* Satisfies SWS_Crypto_00135 */
    errorCode = ecy_hsm_Csai_AsymDecrypt( csaiSession->hSession, csaiSession->priority, csai_AsymCipherMode,
                                          hKey, cipher, cipher_len, msg, *msg_len, msg_len, &(csaiSession->hJob) );

    return errorCode;
}

#define CRYPTO_82_HSM_STOP_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"
