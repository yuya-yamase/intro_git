/**
 * \file Crypto_82_Hsm_Sign.c
 *
 * \author      PiNTeam
 * \copyright   (c) DENSO KK, 2022
 *
 * \brief Implementation of the Sign module
 *
*/

/**********************************************************************************************************************\
 * INCLUDES
\**********************************************************************************************************************/

#include "Crypto_82_Hsm_Internal.h"
#include "Crypto_82_Hsm_Services.h"

#include "ecy_hsm_csai.h"
#include "ecy_hsm_csai_types.h"
#include "ecy_hsm_csai_sign.h"

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
 * \brief Mapping for signature algorithms.
 *
 * \param [in] algo           Crypto Service layer supported sign algorithm.
 *
 * \return ret_algo           Corresponding sign algorithm supported by the Hsm.
 */
static FUNC(ecy_hsm_Csai_SignatureSchemeT, CRYPTO_82_HSM_CODE) get_signAlgo(Crypto_82_Hsm_Service_SignAlgorithmType algo);
/**********************************************************************************************************************\
 * PRIVATE FUNCTION IMPLEMENTATIONS
\**********************************************************************************************************************/

static FUNC(ecy_hsm_Csai_SignatureSchemeT, CRYPTO_82_HSM_CODE) get_signAlgo(Crypto_82_Hsm_Service_SignAlgorithmType algo)
{
    ecy_hsm_Csai_SignatureSchemeT ret_algo = ecy_hsm_CSAI_SIGNSCHEME_RESERVED;

    switch (algo)
    {
    case CryptoDriver_RSA_SSA_PKCS1_1V5_SHA256:
        ret_algo = ecy_hsm_CSAI_RSA_SSA_PKCS1_1V5_SHA256;
        break;
    case CryptoDriver_RSA_SSA_PSS_SHA256:
        ret_algo = ecy_hsm_CSAI_RSA_SSA_PSS_SHA256;
        break;
    case CryptoDriver_ED25519_SHA_512_PURE:
        ret_algo = ecy_hsm_CSAI_ED25519_SHA_512_PURE;
        break;
    case CryptoDriver_ED25519_SHA_512_DOM2_PH:
        ret_algo = ecy_hsm_CSAI_ED25519_SHA_512_DOM2_PH;
        break;
    case CryptoDriver_SECP224_SHA_224:
        ret_algo = ecy_hsm_CSAI_SECP224_SHA_224;
        break;
    case CryptoDriver_SECP256_SHA_256:
        ret_algo = ecy_hsm_CSAI_SECP256_SHA_256;
        break;
    case CryptoDriver_SECP384_SHA_512:
        ret_algo = ecy_hsm_CSAI_SECP384_SHA_512;
        break;
    case CryptoDriver_SECP384_SHA_384:
        ret_algo = ecy_hsm_CSAI_SECP384_SHA_384;
        break;
    case CryptoDriver_SECP384_SHA_256_USERHASHED:
        ret_algo = ecy_hsm_CSAI_SECP384_SHA_256_USERHASHED;
        break;
    case CryptoDriver_SECP384_SHA_384_USERHASHED:
        ret_algo = ecy_hsm_CSAI_SECP384_SHA_384_USERHASHED;
        break;
    case CryptoDriver_SECP384_SHA_512_USERHASHED:
        ret_algo = ecy_hsm_CSAI_SECP384_SHA_512_USERHASHED;
        break;
    case CryptoDriver_ED25519_SHA_512_DOM2_PH_USERHASHED:
        ret_algo = ecy_hsm_CSAI_ED25519_SHA_512_DOM2_PH_USERHASHED;
        break;

    default:
        ret_algo = ecy_hsm_CSAI_SIGNSCHEME_RESERVED;
        break;
    }

    return ret_algo;
}

/**********************************************************************************************************************\
 * PUBLIC FUNCTION IMPLEMENTATIONS
\**********************************************************************************************************************/

FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Sign_Generate
(
    P2VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC, CRYPTO_82_HSM_VAR) csaiSession, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(ecy_hsm_Csai_KeyHandleT, AUTOMATIC) hKey,
    VAR(Crypto_82_Hsm_Service_SignAlgorithmType, AUTOMATIC) signAlgo,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) msg,
    VAR(uint32, AUTOMATIC) msg_len,
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) sign, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) sign_len /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) errorCode;
    ecy_hsm_Csai_SignatureSchemeT csai_signAlgo = (ecy_hsm_Csai_SignatureSchemeT)get_signAlgo(signAlgo);

    /* Satisfies SWS_Crypto_00135 */
    errorCode = ecy_hsm_Csai_SignGenerate( csaiSession->hSession, csai_signAlgo, hKey,
                                           csaiSession->priority, msg, msg_len,
                                           sign, *sign_len, sign_len,
                                           &(csaiSession->hJob) );

    return errorCode;
}

FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Sign_Generate_Start
(
    P2VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC, CRYPTO_82_HSM_VAR) csaiSession, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(ecy_hsm_Csai_KeyHandleT, AUTOMATIC) hKey,
    VAR(Crypto_82_Hsm_Service_SignAlgorithmType, AUTOMATIC) signAlgo,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) msg,
    VAR(uint32, AUTOMATIC) msg_len
)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) errorCode;
    ecy_hsm_Csai_SignatureSchemeT csai_signAlgo = (ecy_hsm_Csai_SignatureSchemeT)get_signAlgo(signAlgo);

    errorCode = ecy_hsm_Csai_SignGenerateStart( csaiSession->hSession, csai_signAlgo, hKey,
                                                csaiSession->priority, msg, msg_len,
                                                &(csaiSession->hJob) );

    return errorCode;
}

FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Sign_Generate_Update
(
    VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC) csaiSession,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) msg,
    VAR(uint32, AUTOMATIC) msg_len
)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) errorCode;

    errorCode = ecy_hsm_Csai_SignGenerateUpdate( csaiSession.hJob, msg, msg_len );

    return errorCode;
}

FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Sign_Generate_Finish
(
    VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC) csaiSession,
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) sign, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) sign_len /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) errorCode;

    /* Satisfies SWS_Crypto_00135 */
    errorCode = ecy_hsm_Csai_SignGenerateFinish( csaiSession.hJob, sign, *sign_len,
                                                 sign_len );

    return errorCode;
}

FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Sign_Verify
(
    P2VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC, CRYPTO_82_HSM_VAR) csaiSession, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(ecy_hsm_Csai_KeyHandleT, AUTOMATIC) hKey,
    VAR(Crypto_82_Hsm_Service_SignAlgorithmType, AUTOMATIC) signAlgo,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) msg,
    VAR(uint32, AUTOMATIC) msg_len,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) sign,
    VAR(uint32, AUTOMATIC) sign_len,
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) verificationResult /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) errorCode;
    ecy_hsm_Csai_SignatureSchemeT csai_signAlgo = (ecy_hsm_Csai_SignatureSchemeT)get_signAlgo(signAlgo);

    errorCode = ecy_hsm_Csai_SignVerify ( csaiSession->hSession, csai_signAlgo, hKey,
                                          csaiSession->priority, msg, msg_len,
                                          sign, sign_len, verificationResult,
                                          &(csaiSession->hJob) );

    return errorCode;
}

FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Sign_Verify_Start
(
    P2VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC, CRYPTO_82_HSM_VAR) csaiSession, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(ecy_hsm_Csai_KeyHandleT, AUTOMATIC) hKey,
    VAR(Crypto_82_Hsm_Service_SignAlgorithmType, AUTOMATIC) signAlgo,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) msg,
    VAR(uint32, AUTOMATIC) msg_len
)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) errorCode;
    ecy_hsm_Csai_SignatureSchemeT csai_signAlgo = (ecy_hsm_Csai_SignatureSchemeT)get_signAlgo(signAlgo);

    errorCode = ecy_hsm_Csai_SignVerifyStart( csaiSession->hSession, csai_signAlgo, hKey,
                                              csaiSession->priority, msg, msg_len,
                                              &(csaiSession->hJob) );

    return errorCode;
}

FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Sign_Verify_Update
(
    VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC) csaiSession,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) msg,
    VAR(uint32, AUTOMATIC) msg_len
)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) errorCode;

    errorCode = ecy_hsm_Csai_SignVerifyUpdate( csaiSession.hJob, msg, msg_len );

    return errorCode;
}

FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Sign_Verify_Finish
(
    VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC) csaiSession,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) sign,
    VAR(uint32, AUTOMATIC) sign_len,
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) verificationResult /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) errorCode;

    errorCode = ecy_hsm_Csai_SignVerifyFinish( csaiSession.hJob, sign, sign_len,
                                               verificationResult );

    return errorCode;
}

#define CRYPTO_82_HSM_STOP_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"
