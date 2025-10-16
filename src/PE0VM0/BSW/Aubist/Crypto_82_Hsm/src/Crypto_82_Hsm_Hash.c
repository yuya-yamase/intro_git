/**
 * \file Crypto_82_Hsm_Hash.c
 *
 * \author      PiNTeam
 * \copyright   (c) DENSO KK, 2022
 *
 * \brief Implementation of the HASH module
 *
*/

/**********************************************************************************************************************\
 * INCLUDES
\**********************************************************************************************************************/

#include "Crypto_82_Hsm_Internal.h"
#include "Crypto_82_Hsm_Services.h"

#include "ecy_hsm_csai.h"
#include "ecy_hsm_csai_types.h"
#include "ecy_hsm_csai_hash.h"

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
 * \brief Mapping for hash algorithms.
 *
 * \param [in] algo           Crypto Service layer supported Hash algorithm.
 *
 * \return ret_algo           Corresponding hash algorithm supported by the HSM.
 */
static FUNC(ecy_hsm_Csai_HashAlgorithmT , CRYPTO_82_HSM_CODE) get_hashAlgo(Crypto_82_Hsm_Service_HashAlgorithmType algo);

/**********************************************************************************************************************\
 * PRIVATE FUNCTION IMPLEMENTATIONS
\**********************************************************************************************************************/

static FUNC(ecy_hsm_Csai_HashAlgorithmT, CRYPTO_82_HSM_CODE) get_hashAlgo(Crypto_82_Hsm_Service_HashAlgorithmType algo)
{
    ecy_hsm_Csai_HashAlgorithmT ret_algo = ecy_hsm_CSAI_HASH_RESERVED;

    switch (algo)
    {
    case CryptoDriver_SHA1:
        ret_algo = ecy_hsm_CSAI_SHA1;
        break;
    case CryptoDriver_SHA2_256:
        ret_algo = ecy_hsm_CSAI_SHA2_256;
        break;
    case CryptoDriver_SHA2_512:
        ret_algo = ecy_hsm_CSAI_SHA2_512;
        break;
    case CryptoDriver_SHA2_224:
        ret_algo = ecy_hsm_CSAI_SHA2_224;
        break;
    case CryptoDriver_SHA2_384:
        ret_algo = ecy_hsm_CSAI_SHA2_384;
        break;
    case CryptoDriver_AES_MP:
        ret_algo = ecy_hsm_CSAI_AES_MP;
        break;
    default:
        ret_algo = ecy_hsm_CSAI_HASH_RESERVED;
        break;
    }

    return ret_algo;
}
/**********************************************************************************************************************\
 * PUBLIC FUNCTION IMPLEMENTATIONS
\**********************************************************************************************************************/

FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Hash_Compute(
    P2VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC, CRYPTO_82_HSM_VAR) csaiSession, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(Crypto_82_Hsm_Service_HashAlgorithmType, AUTOMATIC) hashAlgo,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) msg,
    VAR(uint32, AUTOMATIC) msg_len,
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) digest, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) digest_len  /*[SWS_Crypto_00071]*/ /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) errorCode;
    CONST(boolean, AUTOMATIC) truncationAllowed = TRUE /*[SWS_Crypto_00065]*/;
    ecy_hsm_Csai_HashAlgorithmT csai_hashAlgo = (ecy_hsm_Csai_HashAlgorithmT)get_hashAlgo(hashAlgo);

    /* Satisfies SWS_Crypto_00135 */
    errorCode = ecy_hsm_Csai_Hash( csaiSession->hSession, csai_hashAlgo, csaiSession->priority,
                                   msg, msg_len, digest,
                                   *digest_len, digest_len, truncationAllowed,
                                   &(csaiSession->hJob) );

    return errorCode;
}

FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Hash_Start(
    P2VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC, CRYPTO_82_HSM_VAR) csaiSession, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(Crypto_82_Hsm_Service_HashAlgorithmType, AUTOMATIC) hashAlgo,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) msg,
    VAR(uint32, AUTOMATIC) msg_len
)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) errorCode;
    ecy_hsm_Csai_HashAlgorithmT csai_hashAlgo = (ecy_hsm_Csai_HashAlgorithmT)get_hashAlgo(hashAlgo);

    errorCode = ecy_hsm_Csai_HashStart( csaiSession->hSession, csai_hashAlgo, csaiSession->priority,
                                        msg, msg_len, &(csaiSession->hJob) );

    return errorCode;
}

FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Hash_Update
(
    VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC) csaiSession,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) msg,
    VAR(uint32, AUTOMATIC) msg_len
)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) errorCode;

    errorCode = ecy_hsm_Csai_HashUpdate( csaiSession.hJob, msg, msg_len );

    return errorCode;
}

FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Hash_Finish(
    VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC) csaiSession,
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) digest, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) digest_len  /*[SWS_Crypto_00071]*/ /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) errorCode;
    CONST(boolean, AUTOMATIC) truncationAllowed = TRUE /*[SWS_Crypto_00065]*/;

    /* Satisfies SWS_Crypto_00135 */
    errorCode = ecy_hsm_Csai_HashFinish( csaiSession.hJob, digest, *digest_len,
                                         digest_len, truncationAllowed );

    return errorCode;
}

#define CRYPTO_82_HSM_STOP_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"
