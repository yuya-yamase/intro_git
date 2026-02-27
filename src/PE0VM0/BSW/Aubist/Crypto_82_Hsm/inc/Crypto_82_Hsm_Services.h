/**
 * \file Crypto_82_Hsm_Services.h
 * \author      PiNTeam
 * \copyright   (c) DENSO KK, 2022
 *
 * \brief
 * \details
*/

#ifndef CRYPTO_82_HSM_SERVICES_H
#define CRYPTO_82_HSM_SERVICES_H

/**********************************************************************************************************************\
 * INCLUDES
\**********************************************************************************************************************/

#include "Std_Types.h"

#include "Csm.h"
#if ( (CSM_AR_RELEASE_MAJOR_VERSION == 4u) && (CSM_AR_RELEASE_MINOR_VERSION >= 5u) )
#include "Crypto_GeneralTypes.h"
#else
#include "Csm_Types.h"
#endif

#include "Crypto_82_Hsm.h"
#include "Crypto_82_Hsm_Internal.h"
#include "Crypto_82_Hsm_Custom_Algorithms.h"

#include "ecy_hsm_csai.h"
#include "ecy_hsm_csai_mac.h"
#include "ecy_hsm_csai_sign.h"
#include "ecy_hsm_csai_hash.h"
#include "ecy_hsm_csai_crypt.h"

/**********************************************************************************************************************\
 * PUBLIC MACROS
\**********************************************************************************************************************/

/**
 * \def   CRYPTO_82_HSM_PROCESSING_ASYNC
 * \brief Define for asynchronous processing mode.
 */
#define CRYPTO_82_HSM_PROCESSING_ASYNC          (1u << CRYPTO_PROCESSING_ASYNC)

/**
 * \def   CRYPTO_82_HSM_PROCESSING_SYNC 
 * \brief Define for synchronous processing mode.
 */
#define CRYPTO_82_HSM_PROCESSING_SYNC            (1u << CRYPTO_PROCESSING_SYNC )

/**
 * \def   CRYPTO_82_HSM_OPERATING_MODE_ALL
 * \brief Define for all operating modes.
 */
#define CRYPTO_82_HSM_OPERATING_MODE_ALL        ((1uL << CRYPTO_OPERATIONMODE_SINGLECALL)  | \
                                                 (1uL << CRYPTO_OPERATIONMODE_START)       | \
                                                 (1uL << CRYPTO_OPERATIONMODE_STREAMSTART) | \
                                                 (1uL << CRYPTO_OPERATIONMODE_UPDATE)      | \
                                                 (1uL << CRYPTO_OPERATIONMODE_FINISH))

/*
* CRYPTO_82_HSM_HASH SERVICE
*/

/**
 * \def   CRYPTO_82_HSM_HASH_ALGOFAM
 * \brief Define for supported algorithm families for HASH service
 */
#define CRYPTO_82_HSM_HASH_ALGOFAM              ((1uLL << CRYPTO_ALGOFAM_SHA1)         | \
                                                 (1uLL << CRYPTO_ALGOFAM_SHA2_224)     | \
                                                 (1uLL << CRYPTO_ALGOFAM_SHA2_256)     | \
                                                 (1uLL << CRYPTO_ALGOFAM_SHA2_384)     | \
                                                 (1uLL << CRYPTO_ALGOFAM_SHA2_512)     | \
                                                 (1uLL << CRYPTO_ALGOFAM_CUSTOM_AES_MP))

/* TODO: Identify correct configuration, this is currently stubbed for testing purposes. Also move these to correct place in file*/
/**
 * \def   CRYPTO_82_HSM_HASH_SECALGOFAM
 * \brief Hash secondary algorithm family.
 */
#define CRYPTO_82_HSM_HASH_SECALGOFAM           (1uLL << CRYPTO_ALGOFAM_NOT_SET)

/*
* TO DO: Identify what algorithm modes are relevant for HASH and decide which are supported.
*/
/**
 * \def   CRYPTO_82_HSM_HASH_ALGO_MODE
 * \brief Define for supported algorithm modes for HASH service
 */
#define CRYPTO_82_HSM_HASH_ALGO_MODE            (1uL << CRYPTO_ALGOMODE_NOT_SET)

/**
 * \def   CRYPTO_82_HSM_HASH_OPERATING_MODE
 * \brief Define for supported operating modes for HASH service
 */
#define CRYPTO_82_HSM_HASH_OPERATING_MODE       CRYPTO_82_HSM_OPERATING_MODE_ALL

/**
 * \def   CRYPTO_82_HSM_HASH_PROCESSING_MODE
 * \brief Define for supported processing modes for HASH service
 */
#define CRYPTO_82_HSM_HASH_PROCESSING_MODE      ((CRYPTO_82_HSM_PROCESSING_ASYNC) | (CRYPTO_82_HSM_PROCESSING_SYNC ))

/*
* CRYPTO_82_HSM_MACGEN SERVICE
*/

/*
* TO DO: Identify what algorithm families are relevant for MACGEN and decide which are supported.
*/
/**
 * \def   CRYPTO_82_HSM_MACGEN_ALGOFAM
 * \brief Define for supported algorithm families for MACGEN service
 */
#define CRYPTO_82_HSM_MACGEN_ALGOFAM            ((1uLL << CRYPTO_ALGOFAM_AES)     | \
                                                (1uLL << CRYPTO_ALGOFAM_SHA1)     | \
                                                (1uLL << CRYPTO_ALGOFAM_SHA2_256) | \
                                                (1uLL << CRYPTO_ALGOFAM_SHA2_512))

/**
 * \def   CRYPTO_82_HSM_MACGEN_SECALGOFAM
 * \brief MAC generation secondary algorithm family.
 */
#define CRYPTO_82_HSM_MACGEN_SECALGOFAM         (1uLL << CRYPTO_ALGOFAM_NOT_SET)

/**
 * \def   CRYPTO_82_HSM_MACGEN_ALGO_MODE
 * \brief Define for supported algorithm modes for MACGEN service
 */
#define CRYPTO_82_HSM_MACGEN_ALGO_MODE          ((1uL << CRYPTO_ALGOMODE_HMAC)       | \
                                                 (1uL << CRYPTO_ALGOMODE_CMAC))
/**
 * \def   CRYPTO_82_HSM_MACGEN_OPERATING_MODE
 * \brief Define for supported operating modes for MACGEN service
 */
#define CRYPTO_82_HSM_MACGEN_OPERATING_MODE     CRYPTO_82_HSM_OPERATING_MODE_ALL

/**
 * \def   CRYPTO_82_HSM_MACGEN_PROCESSING_MODE
 * \brief Define for supported processing modes for MACGEN service
 */
#define CRYPTO_82_HSM_MACGEN_PROCESSING_MODE    ((CRYPTO_82_HSM_PROCESSING_ASYNC) | (CRYPTO_82_HSM_PROCESSING_SYNC ))

/*
* CRYPTO_82_HSM_MACVERIFY SERVICE
*/

/**
 * \def   CRYPTO_82_HSM_MACVERIFY_ALGOFAM
 * \brief Define for supported algorithm families for MACVERIFY service
 */
#define CRYPTO_82_HSM_MACVERIFY_ALGOFAM         ((1uLL << CRYPTO_ALGOFAM_AES)     | \
                                                (1uLL << CRYPTO_ALGOFAM_SHA1)     | \
                                                (1uLL << CRYPTO_ALGOFAM_SHA2_256) | \
                                                (1uLL << CRYPTO_ALGOFAM_SHA2_512))


/**
 * \def   CRYPTO_82_HSM_MACVERIFY_SECALGOFAM
 * \brief MAC verification secondary algorithm family.
 */
#define CRYPTO_82_HSM_MACVERIFY_SECALGOFAM      (1uLL << CRYPTO_ALGOFAM_NOT_SET)

/**
 * \def   CRYPTO_82_HSM_MACVERIFY_ALGO_MODE
 * \brief Define for supported algorithm modes for MACVERIFY service
 */
#define CRYPTO_82_HSM_MACVERIFY_ALGO_MODE       ((1uL << CRYPTO_ALGOMODE_HMAC)       | \
                                                 (1uL << CRYPTO_ALGOMODE_CMAC))

/**
 * \def   CRYPTO_82_HSM_MACVERIFY_OPERATING_MODE
 * \brief Define for supported operating modes for MACVERIFY service
 */
#define CRYPTO_82_HSM_MACVERIFY_OPERATING_MODE  CRYPTO_82_HSM_OPERATING_MODE_ALL

/**
 * \def   CRYPTO_82_HSM_MACVERIFY_PROCESSING_MODE
 * \brief Define for supported processing modes for MACVERIFY service
 */
#define CRYPTO_82_HSM_MACVERIFY_PROCESSING_MODE     ((CRYPTO_82_HSM_PROCESSING_ASYNC) | (CRYPTO_82_HSM_PROCESSING_SYNC ))

/*
* CRYPTO_82_HSM_ENCRYPT SERVICE
*/

/*
* TO DO: Identify what algorithm families are relevant for ENCRYPT and decide which are supported.
* DOUBLE CHECK to see that current listed algorithms are relevant.
*/
/**
 * \def   CRYPTO_82_HSM_ENCRYPT_ALGOFAM
 * \brief Define for supported algorithm families for ENCRYPT service
 */
#define CRYPTO_82_HSM_ENCRYPT_ALGOFAM           ((1uLL << CRYPTO_ALGOFAM_AES)       | \
                                                 (1uLL << CRYPTO_ALGOFAM_RSA))

/**
 * \def   CRYPTO_82_HSM_ENCRYPT_SECALGOFAM
 * \brief Encrpyt secondary algorithm family.
 */
#define CRYPTO_82_HSM_ENCRYPT_SECALGOFAM        ((1uLL << CRYPTO_ALGOFAM_NOT_SET)           | \
                                                 (1uLL << CRYPTO_ALGOFAM_PADDING_PKCS7)     | \
                                                 (1uLL << CRYPTO_ALGOFAM_PADDING_ONEWITHZEROS))

/**
 * \def   CRYPTO_82_HSM_ENCRYPT_ALGO_MODE
 * \brief Define for supported algorithm modes for ENCRYPT service
 */
#define CRYPTO_82_HSM_ENCRYPT_ALGO_MODE         ((1uL << CRYPTO_ALGOMODE_ECB)                 |  \
                                                 (1uL << CRYPTO_ALGOMODE_CBC)                 |  \
                                                 (1uL << CRYPTO_ALGOMODE_CFB)                 |  \
                                                 (1uL << CRYPTO_ALGOMODE_OFB)                 |  \
                                                 (1uL << CRYPTO_ALGOMODE_CTR)                 |  \
                                                 (1uL << CRYPTO_ALGOMODE_XTS)                 |  \
                                                 (1uL << CRYPTO_ALGOMODE_RSAES_OAEP)          |  \
                                                 (1uL << CRYPTO_ALGOMODE_RSAES_PKCS1_v1_5))
/**
 * \def   CRYPTO_82_HSM_ENCRYPT_OPERATING_MODE
 * \brief Define for supported operating modes for ENCRYPT service
 */
#define CRYPTO_82_HSM_ENCRYPT_OPERATING_MODE    CRYPTO_82_HSM_OPERATING_MODE_ALL

/**
 * \def   CRYPTO_82_HSM_ENCRYPT_PROCESSING_MODE
 * \brief Define for supported processing modes for ENCRYPT service
 */
#define CRYPTO_82_HSM_ENCRYPT_PROCESSING_MODE   ((CRYPTO_82_HSM_PROCESSING_ASYNC) | (CRYPTO_82_HSM_PROCESSING_SYNC ))

/*
* CRYPTO_82_HSM_DECRYPT SERVICE
*/

/*
* TO DO: Identify what algorithm families are relevant for DECRYPT and decide which are supported.
* DOUBLE CHECK to see that current listed algorithms are relevant.
*/
/**
 * \def   CRYPTO_82_HSM_DECRYPT_ALGOFAM
 * \brief Define for supported algorithm families for DECRYPT service
 */
#define CRYPTO_82_HSM_DECRYPT_ALGOFAM           ((1uLL << CRYPTO_ALGOFAM_AES)       | \
                                                 (1uLL << CRYPTO_ALGOFAM_RSA))

/**
 * \def   CRYPTO_82_HSM_DECRYPT_SECALGOFAM
 * \brief Decrypt secondary algorithm family.
 */
#define CRYPTO_82_HSM_DECRYPT_SECALGOFAM        ((1uLL << CRYPTO_ALGOFAM_NOT_SET)           | \
                                                 (1uLL << CRYPTO_ALGOFAM_PADDING_PKCS7)     | \
                                                 (1uLL << CRYPTO_ALGOFAM_PADDING_ONEWITHZEROS))
/**
 * \def   CRYPTO_82_HSM_DECRYPT_ALGO_MODE
 * \brief Define for supported algorithm modes for DECRYPT service
 */
#define CRYPTO_82_HSM_DECRYPT_ALGO_MODE         ((1uL << CRYPTO_ALGOMODE_ECB)                |  \
                                                 (1uL << CRYPTO_ALGOMODE_CBC)                |  \
                                                 (1uL << CRYPTO_ALGOMODE_CFB)                |  \
                                                 (1uL << CRYPTO_ALGOMODE_OFB)                |  \
                                                 (1uL << CRYPTO_ALGOMODE_CTR)                |  \
                                                 (1uL << CRYPTO_ALGOMODE_XTS)                |  \
                                                 (1uL << CRYPTO_ALGOMODE_RSAES_OAEP)         |  \
                                                 (1uL << CRYPTO_ALGOMODE_RSAES_PKCS1_v1_5))

/**
 * \def   CRYPTO_82_HSM_DECRYPT_OPERATING_MODE
 * \brief Define for supported operating modes for DECRYPT service
 */
#define CRYPTO_82_HSM_DECRYPT_OPERATING_MODE    CRYPTO_82_HSM_OPERATING_MODE_ALL

/**
 * \def   CRYPTO_82_HSM_DECRYPT_PROCESSING_MODE
 * \brief Define for supported processing modes for DECRYPT service
 */
#define CRYPTO_82_HSM_DECRYPT_PROCESSING_MODE   ((CRYPTO_82_HSM_PROCESSING_ASYNC) | (CRYPTO_82_HSM_PROCESSING_SYNC ))

/*
* CRYPTO_82_HSM_AEAD_ENCRYPT SERVICE
*/ 

/**
 * \def   CRYPTO_82_HSM_AEAD_ENCRYPT_ALGOFAM
 * \brief Define for supported algorithm families for Authenticated ENCRYPT service
 */
#define CRYPTO_82_HSM_AEAD_ENCRYPT_ALGOFAM      ((1uLL << CRYPTO_ALGOFAM_AES))   

/**
 * \def   CRYPTO_82_HSM_AEAD_ENCRYPT_SECALGOFAM
 * \brief Define for supported algorithm families for Authenticated ENCRYPT service
 */
#define CRYPTO_82_HSM_AEAD_ENCRYPT_SECALGOFAM      ((1uLL << 0)) 

/**
 * \def   CRYPTO_82_HSM_AEAD_ENCRYPT_ALGO_MODE
 * \brief Define for supported algorithm modes for Authenticated ENCRYPT service
 */
#define CRYPTO_82_HSM_AEAD_ENCRYPT_ALGO_MODE         ((1uL << CRYPTO_ALGOMODE_GCM)  )

/**
 * \def   CRYPTO_82_HSM_AEAD_ENCRYPT_OPERATING_MODE
 * \brief Define for supported operating modes for Authenticated ENCRYPT service
 */
#define CRYPTO_82_HSM_AEAD_ENCRYPT_OPERATING_MODE    ((1uL << CRYPTO_OPERATIONMODE_SINGLECALL)  | \
                                                      (1uL << CRYPTO_OPERATIONMODE_START)       | \
                                                      (1uL << CRYPTO_OPERATIONMODE_UPDATE)      | \
                                                      (1uL << CRYPTO_OPERATIONMODE_FINISH))

/**
 * \def   CRYPTO_82_HSM_AEAD_ENCRYPT_PROCESSING_MODE
 * \brief Define for supported processing modes for Authenticated ENCRYPT service
 */
#define CRYPTO_82_HSM_AEAD_ENCRYPT_PROCESSING_MODE   ((CRYPTO_82_HSM_PROCESSING_ASYNC) | (CRYPTO_82_HSM_PROCESSING_SYNC ))   

/*
* CRYPTO_82_HSM_AEAD_DECRYPT SERVICE
*/

/**
 * \def   CRYPTO_82_HSM_AEAD_DECRYPT_ALGOFAM
 * \brief Define for supported algorithm families for Authenticated DECRYPT service
 */
#define CRYPTO_82_HSM_AEAD_DECRYPT_ALGOFAM      ((1uLL << CRYPTO_ALGOFAM_AES))

/**
 * \def   CRYPTO_82_HSM_AEAD_DECRYPT_SECALGOFAM
 * \brief Define for supported algorithm families for Authenticated DECRYPT service
 */
#define CRYPTO_82_HSM_AEAD_DECRYPT_SECALGOFAM      ((1uLL << 0))     

/**
 * \def CRYPTO_82_HSM_AEAD_DECRYPT_ALGO_MODE
 * \brief Define for supported algorithm modes for Authenticated DECRYPT service
 */
#define CRYPTO_82_HSM_AEAD_DECRYPT_ALGO_MODE         ((1uL << CRYPTO_ALGOMODE_GCM)  )

/**
 * \def   CRYPTO_82_HSM_AEAD_DECRYPT_OPERATING_MODE
 * \brief Define for supported operating modes for Authenticated DECRYPT service
 */
#define CRYPTO_82_HSM_AEAD_DECRYPT_OPERATING_MODE    ((1uL << CRYPTO_OPERATIONMODE_SINGLECALL)  | \
                                                      (1uL << CRYPTO_OPERATIONMODE_START)       | \
                                                      (1uL << CRYPTO_OPERATIONMODE_UPDATE)      | \
                                                      (1uL << CRYPTO_OPERATIONMODE_FINISH))

/**
 * \def   CRYPTO_82_HSM_AEAD_DECRYPT_PROCESSING_MODE
 * \brief Define for supported processing modes for Authenticated DECRYPT service
 */
#define CRYPTO_82_HSM_AEAD_DECRYPT_PROCESSING_MODE   ((CRYPTO_82_HSM_PROCESSING_ASYNC) | (CRYPTO_82_HSM_PROCESSING_SYNC )) 
        
/*
* CRYPTO_82_HSM_KEY_GENERATE SERVICE
*/

/**
 * \def   CRYPTO_82_HSM_KEY_GENERATE_ALGOFAM
 * \brief Key generate algorithm family.
 */
#define CRYPTO_82_HSM_KEY_GENERATE_ALGOFAM              (1uLL << CRYPTO_ALGOFAM_NOT_SET)

/**
 * \def   CRYPTO_82_HSM_KEY_GENERATE_SECALGOFAM
 * \brief Key generate secondary algorithm family.
 */
#define CRYPTO_82_HSM_KEY_GENERATE_SECALGOFAM           (1uLL << CRYPTO_ALGOFAM_NOT_SET)

/* TODO: Identify correct configuration, this is currently stubbed for testing purposes.*/
/**
 * \def   CRYPTO_82_HSM_KEY_GENERATE_ALGO_MODE
 * \brief Key generate algorithm mode.
 */
#define CRYPTO_82_HSM_KEY_GENERATE_ALGO_MODE     (1uL << CRYPTO_ALGOMODE_NOT_SET)

/**
 * \def   CRYPTO_82_HSM_KEY_GENERATE_OPERATING_MODE
 * \brief Key generate operating mode.
 */
#define CRYPTO_82_HSM_KEY_GENERATE_OPERATING_MODE (1uL << CRYPTO_OPERATIONMODE_SINGLECALL)

/**
 * \def   CRYPTO_82_HSM_KEY_GENERATE_PROCESSING_MODE
 * \brief Key generate processing mode.
 */
#define CRYPTO_82_HSM_KEY_GENERATE_PROCESSING_MODE      (1uL << CRYPTO_PROCESSING_ASYNC)

/*
* CRYPTO_82_HSM_KEY_SET_VALID SERVICE
*/

/* TODO: Identify correct configuration, this is currently stubbed for testing purposes.*/
/**
 * \def   CRYPTO_82_HSM_KEY_SET_VALID_ALGOFAM
 * \brief Key set valid algorithm family.
 */
#define CRYPTO_82_HSM_KEY_SET_VALID_ALGOFAM         (1uLL << CRYPTO_ALGOFAM_NOT_SET)

/* TODO: Identify correct configuration, this is currently stubbed for testing purposes.*/
/**
 * \def   CRYPTO_82_HSM_KEY_SET_VALID_SECALGOFAM
 * \brief Key set valid secondary algorithm family.
 */
#define CRYPTO_82_HSM_KEY_SET_VALID_SECALGOFAM      (1uLL << CRYPTO_ALGOFAM_NOT_SET)

/* TODO: Identify correct configuration, this is currently stubbed for testing purposes.*/
/**
 * \def   CRYPTO_82_HSM_KEY_SET_VALID_ALGO_MODE
 * \brief Key set valid algorithm mode.
 */
#define CRYPTO_82_HSM_KEY_SET_VALID_ALGO_MODE       (1uL << CRYPTO_ALGOMODE_NOT_SET)

/* TODO: Identify correct configuration, this is currently stubbed for testing purposes.*/
/**
 * \def   CRYPTO_82_HSM_KEY_SET_VALID_OPERATING_MODE
 * \brief Key set valid operating mode.
 */
#define CRYPTO_82_HSM_KEY_SET_VALID_OPERATING_MODE  (1uL << CRYPTO_OPERATIONMODE_SINGLECALL)

/* TODO: Identify correct configuration, this is currently stubbed for testing purposes.*/
/**
 * \def   CRYPTO_82_HSM_KEY_SET_VALID_PROCESSING_MODE
 * \brief Key set valid processing mode.
 */
#define CRYPTO_82_HSM_KEY_SET_VALID_PROCESSING_MODE (1uL << CRYPTO_PROCESSING_ASYNC)

/*
* CRYPTO_82_HSM_KEY_DERIVE SERVICE
*/

/* TODO: Identify correct configuration, this is currently stubbed for testing purposes.*/
/**
 * \def   CRYPTO_82_HSM_KEY_DERIVE_ALGOFAM
 * \brief Key derive processing algorithm family.
 */
#define CRYPTO_82_HSM_KEY_DERIVE_ALGOFAM         ( (1uLL << CRYPTO_ALGOFAM_PBKDF2) | \
                                                   (1uLL << CRYPTO_ALGOFAM_CUSTOM_KDF_NISTSP80056C) | \
                                                   (1uLL << CRYPTO_ALGOFAM_CUSTOM_KDF_NISTSP800108) | \
                                                   (1uLL << CRYPTO_ALGOFAM_CUSTOM_KDF_ANSIX963))

/* TODO: Identify correct configuration, this is currently stubbed for testing purposes.*/
/**
 * \def   CRYPTO_82_HSM_KEY_DERIVE_SECALGOFAM
 * \brief Key derive secondary algorithm family.
 */
#define CRYPTO_82_HSM_KEY_DERIVE_SECALGOFAM     (1uLL << 0u)

/* TODO: Identify correct configuration, this is currently stubbed for testing purposes.*/
/**
 * \def   CRYPTO_82_HSM_KEY_DERIVE_ALGO_MODE
 * \brief Key derive processing algorithm mode.
 */
#define CRYPTO_82_HSM_KEY_DERIVE_ALGO_MODE       (1uL << 0u)

/* TODO: Identify correct configuration, this is currently stubbed for testing purposes.*/
/**
 * \def   CRYPTO_82_HSM_KEY_DERIVE_OPERATING_MODE
 * \brief Key derive processing operating mode.
 */
#define CRYPTO_82_HSM_KEY_DERIVE_OPERATING_MODE  (1uL << CRYPTO_OPERATIONMODE_SINGLECALL)

/* TODO: Identify correct configuration, this is currently stubbed for testing purposes.*/
/**
 * \def   CRYPTO_82_HSM_KEY_DERIVE_PROCESSING_MODE
 * \brief Key derive processing mode.
 */
#define CRYPTO_82_HSM_KEY_DERIVE_PROCESSING_MODE  (1uL << CRYPTO_PROCESSING_ASYNC)

/*
* CRYPTO_82_HSM_RNG SERVICE
*/

/* TODO: Identify correct configuration, this is currently stubbed for testing purposes.*/
/**
 * \def   CRYPTO_82_HSM_RNG_ALGOFAM
 * \brief Random number generation algorithm family.
 */
#define CRYPTO_82_HSM_RNG_ALGOFAM               ((1uLL << CRYPTO_ALGOFAM_RNG) | \
                                                (1uLL << CRYPTO_ALGOFAM_DRBG))

/**
 * \def   CRYPTO_82_HSM_RNG_SECALGOFAM
 * \brief Random number generation secondary algorithm family.
 */
#define CRYPTO_82_HSM_RNG_SECALGOFAM            (1uLL << CRYPTO_ALGOFAM_NOT_SET)

/* TODO: Identify correct configuration, this is currently stubbed for testing purposes.*/
/**
 * \def   CRYPTO_82_HSM_RNG_ALGO_MODE
 * \brief Random number generation algorithm mode.
 */
#define CRYPTO_82_HSM_RNG_ALGO_MODE             (1uL << CRYPTO_ALGOMODE_NOT_SET)

/**
 * \def   CRYPTO_82_HSM_RNG_OPERATING_MODE
 * \brief Random number generation operating mode.
 */
#define CRYPTO_82_HSM_RNG_OPERATING_MODE        (1uL << CRYPTO_OPERATIONMODE_SINGLECALL)

/**
 * \def   CRYPTO_82_HSM_RNG_PROCESSING_MODE
 * \brief Random number generation processing mode.
 */
#define CRYPTO_82_HSM_RNG_PROCESSING_MODE       ((CRYPTO_82_HSM_PROCESSING_ASYNC) | (CRYPTO_82_HSM_PROCESSING_SYNC ))

/*
* CRYPTO_82_HSM_SIGNATURE_GENERATE SERVICE
*/

/* TODO: Identify correct configuration, this is currently stubbed for testing purposes.*/
/**
 * \def   CRYPTO_82_HSM_SIGNATURE_GENERATE_ALGOFAM
 * \brief Signature generate algorithm family.
 */
#define CRYPTO_82_HSM_SIGNATURE_GENERATE_ALGOFAM            ((1uLL << CRYPTO_ALGOFAM_ECCNIST)                                   | \
                                                            (1uLL << CRYPTO_ALGOFAM_RSA)                                        | \
                                                            (1uLL << CRYPTO_ALGOFAM_ED25519)                                    | \
                                                            (1uLL << CRYPTO_ALGOFAM_CUSTOM_ED25519_SHA_512_DOM2_PH_USERHASHED)  | \
                                                            (1uLL << CRYPTO_ALGOFAM_CUSTOM_ECCNIST_USERHASHED))

/* TODO: Identify correct configuration, this is currently stubbed for testing purposes.*/
/**
 * \def   CRYPTO_82_HSM_SIGNATURE_GENERATE_ALGOSECFAM
 * \brief Signature generate algorithm secondary family.
 */
#define CRYPTO_82_HSM_SIGNATURE_GENERATE_ALGOSECFAM         ((1uLL << CRYPTO_ALGOFAM_SHA2_256) | \
                                                             (1uLL << CRYPTO_ALGOFAM_SHA2_512) | \
                                                             (1uLL << CRYPTO_ALGOFAM_SHA2_224) | \
                                                             (1uLL << CRYPTO_ALGOFAM_SHA2_384) | \
                                                             (1uLL << CRYPTO_ALGOFAM_NOT_SET))

/* TODO: Identify correct configuration, this is currently stubbed for testing purposes.*/
/**
 * \def   CRYPTO_82_HSM_SIGNATURE_GENERATE_ALGO_MODE
 * \brief Signature generate algorithm mode.
 */
#define CRYPTO_82_HSM_SIGNATURE_GENERATE_ALGO_MODE          ((1uL << CRYPTO_ALGOMODE_RSASSA_PKCS1_v1_5) | \
                                                             (1uL << CRYPTO_ALGOMODE_NOT_SET)           | \
                                                             (1uL << CRYPTO_ALGOMODE_RSASSA_PSS))

/**
 * \def   CRYPTO_82_HSM_SIGNATURE_GENERATE_OPERATING_MODE
 * \brief Signature generate operating mode.
 */
#define CRYPTO_82_HSM_SIGNATURE_GENERATE_OPERATING_MODE     CRYPTO_82_HSM_OPERATING_MODE_ALL

/**
 * \def   CRYPTO_82_HSM_SIGNATURE_GENERATE_PROCESSING_MODE
 * \brief Signature generate processing mode.
 */
#define CRYPTO_82_HSM_SIGNATURE_GENERATE_PROCESSING_MODE    ((CRYPTO_82_HSM_PROCESSING_ASYNC) | (CRYPTO_82_HSM_PROCESSING_SYNC ))

/*
* CRYPTO_82_HSM_SIGNATURE_VERIFY SERVICE
*/

/* TODO: Identify correct configuration, this is currently stubbed for testing purposes.*/
/**
 * \def   CRYPTO_82_HSM_SIGNATURE_VERIFY_ALGOFAM
 * \brief Signature verify algorithm family.
 */
#define CRYPTO_82_HSM_SIGNATURE_VERIFY_ALGOFAM            ((1uLL << CRYPTO_ALGOFAM_ECCNIST)                                   | \
                                                          (1uLL << CRYPTO_ALGOFAM_RSA)                                        | \
                                                          (1uLL << CRYPTO_ALGOFAM_ED25519)                                    | \
                                                          (1uLL << CRYPTO_ALGOFAM_CUSTOM_ED25519_SHA_512_DOM2_PH_USERHASHED)  | \
                                                          (1uLL << CRYPTO_ALGOFAM_CUSTOM_ECCNIST_USERHASHED))
/* TODO: Identify correct configuration, this is currently stubbed for testing purposes.*/
/**
 * \def   CRYPTO_82_HSM_SIGNATURE_VERIFY_ALGOSECFAM
 * \brief Signature verify algorithm secondary family.
 */
#define CRYPTO_82_HSM_SIGNATURE_VERIFY_ALGOSECFAM         ((1uLL << CRYPTO_ALGOFAM_SHA2_256) | \
                                                           (1uLL << CRYPTO_ALGOFAM_SHA2_512) | \
                                                           (1uLL << CRYPTO_ALGOFAM_SHA2_224) | \
                                                           (1uLL << CRYPTO_ALGOFAM_SHA2_384) | \
                                                           (1uLL << CRYPTO_ALGOFAM_NOT_SET))

/* TODO: Identify correct configuration, this is currently stubbed for testing purposes.*/
/**
 * \def   CRYPTO_82_HSM_SIGNATURE_VERIFY_ALGO_MODE
 * \brief Signature verify algorithm mode.
 */
#define CRYPTO_82_HSM_SIGNATURE_VERIFY_ALGO_MODE          ((1uL << CRYPTO_ALGOMODE_RSASSA_PKCS1_v1_5) | \
                                                           (1uL << CRYPTO_ALGOMODE_NOT_SET)           | \
                                                           (1uL << CRYPTO_ALGOMODE_RSASSA_PSS))

/**
 * \def   CRYPTO_82_HSM_SIGNATURE_VERIFY_OPERATING_MODE
 * \brief Signature verify operating mode.
 */
#define CRYPTO_82_HSM_SIGNATURE_VERIFY_OPERATING_MODE     CRYPTO_82_HSM_OPERATING_MODE_ALL

/**
 * \def   CRYPTO_82_HSM_SIGNATURE_VERIFY_PROCESSING_MODE
 * \brief Signature verify processing mode.
 */
#define CRYPTO_82_HSM_SIGNATURE_VERIFY_PROCESSING_MODE    ((CRYPTO_82_HSM_PROCESSING_ASYNC) | (CRYPTO_82_HSM_PROCESSING_SYNC ))

/*
* CRYPTO_82_HSM_KEY_EXCHANGE_CALCPUBVAL SERVICE
*/

/* TODO: Identify correct configuration, this is currently stubbed for testing purposes.*/
/**
 * \def   CRYPTO_82_HSM_KEY_EXCHANGE_CALCPUBVAL_ALGOFAM
 * \brief Key exchange public value calculation algorithm family.
 */
#define CRYPTO_82_HSM_KEY_EXCHANGE_CALCPUBVAL_ALGOFAM            (1uLL << CRYPTO_ALGOFAM_DH)
                                                                 
/**
 * \def   CRYPTO_82_HSM_KEY_EXCHANGE_CALCPUBVAL_SECALGOFAM
 * \brief Key exchange public value calculation secondary algorithm family.
 */
#define CRYPTO_82_HSM_KEY_EXCHANGE_CALCPUBVAL_SECALGOFAM        (1uLL << CRYPTO_ALGOFAM_NOT_SET)

/**
 * \def   CRYPTO_82_HSM_KEY_EXCHANGE_CALCPUBVAL_ALGO_MODE
 * \brief Key exchange public value calculation algorithm mode.
 */
#define CRYPTO_82_HSM_KEY_EXCHANGE_CALCPUBVAL_ALGO_MODE         (1uL << CRYPTO_ALGOMODE_NOT_SET)

/**
 * \def   CRYPTO_82_HSM_KEY_EXCHANGE_CALCPUBVAL_OPERATING_MODE
 * \brief Key exchange public value calculation operating mode.
 */
#define CRYPTO_82_HSM_KEY_EXCHANGE_CALCPUBVAL_OPERATING_MODE    (1uL << CRYPTO_OPERATIONMODE_SINGLECALL)

/**
 * \def   CRYPTO_82_HSM_KEY_EXCHANGE_CALCPUBVAL_PROCESSING_MODE
 * \brief Key exchange public value calculation processing mode.
 */
#define CRYPTO_82_HSM_KEY_EXCHANGE_CALCPUBVAL_PROCESSING_MODE   (1uL << CRYPTO_PROCESSING_ASYNC)

/*
* CRYPTO_82_HSM_KEY_EXCHANGE_CALCSECRET SERVICE
*/

/* TODO: Identify correct configuration, this is currently stubbed for testing purposes.*/
/**
 * \def   CRYPTO_82_HSM_KEY_EXCHANGE_CALCSECRET_ALGOFAM
 * \brief Key exchange secret calculation algorithm family.
 */
#define CRYPTO_82_HSM_KEY_EXCHANGE_CALCSECRET_ALGOFAM           (1uLL << CRYPTO_ALGOFAM_DH)

/**
 * \def   CRYPTO_82_HSM_KEY_EXCHANGE_CALCSECRET_SECALGOFAM
 * \brief Key exchange secret calculation secondary algorithm family.
 */
#define CRYPTO_82_HSM_KEY_EXCHANGE_CALCSECRET_SECALGOFAM        (1uLL << CRYPTO_ALGOFAM_NOT_SET)

/**
 * \def   CRYPTO_82_HSM_KEY_EXCHANGE_CALCSECRET_ALGO_MODE
 * \brief Key exchange secret calculation algorithm mode.
 */
#define CRYPTO_82_HSM_KEY_EXCHANGE_CALCSECRET_ALGO_MODE         (1uL << CRYPTO_ALGOMODE_NOT_SET)

/**
 * \def   CRYPTO_82_HSM_KEY_EXCHANGE_CALCSECRET_OPERATING_MODE
 * \brief Key exchange secret calculation operating mode.
 */
#define CRYPTO_82_HSM_KEY_EXCHANGE_CALCSECRET_OPERATING_MODE    (1uL << CRYPTO_OPERATIONMODE_SINGLECALL)

/**
 * \def   CRYPTO_82_HSM_KEY_EXCHANGE_CALCSECRET_PROCESSING_MODE
 * \brief Key exchange secret calculation processing mode.
 */
#define CRYPTO_82_HSM_KEY_EXCHANGE_CALCSECRET_PROCESSING_MODE   (1uL << CRYPTO_PROCESSING_ASYNC)

/*
* CRYPTO_82_HSM_CERTIFICATE_PARSE SERVICE
*/

/* TODO: Identify correct configuration, this is currently stubbed for testing purposes.*/
/**
 * \def   CRYPTO_82_HSM_CERTIFICATE_PARSE_ALGOFAM
 * \brief Certificate parse algorithm family.
 */
#define CRYPTO_82_HSM_CERTIFICATE_PARSE_ALGOFAM           (1uLL << 0u)

/**
 * \def   CRYPTO_82_HSM_CERTIFICATE_PARSE_SECALGOFAM
 * \brief Certificate parse secondary algorithm family.
 */
#define CRYPTO_82_HSM_CERTIFICATE_PARSE_SECALGOFAM        (1uLL << 0u)

/**
 * \def   CRYPTO_82_HSM_CERTIFICATE_PARSE_ALGO_MODE
 * \brief Certificate parse secondary algorithm mode.
 */
#define CRYPTO_82_HSM_CERTIFICATE_PARSE_ALGO_MODE         (1uL << 0u)

/**
 * \def   CRYPTO_82_HSM_CERTIFICATE_PARSE_OPERATING_MODE
 * \brief Certificate parse secondary operating mode.
 */
#define CRYPTO_82_HSM_CERTIFICATE_PARSE_OPERATING_MODE    (1uL << 0u)

/**
 * \def   CRYPTO_82_HSM_CERTIFICATE_PARSE_PROCESSING_MODE
 * \brief Certificate parse secondary processing mode.
 */
#define CRYPTO_82_HSM_CERTIFICATE_PARSE_PROCESSING_MODE   (1uL << 0u)

/*
* CRYPTO_82_HSM_CERTIFICATE_VERIFY SERVICE
*/

/* TODO: Identify correct configuration, this is currently stubbed for testing purposes.*/
/**
 * \def   CRYPTO_82_HSM_CERTIFICATE_VERIFY_ALGOFAM
 * \brief Certificate verify algorithm family.
 */
#define CRYPTO_82_HSM_CERTIFICATE_VERIFY_ALGOFAM           (1uLL << 0u)

/**
 * \def   CRYPTO_82_HSM_CERTIFICATE_VERIFY_SECALGOFAM
 * \brief Certificate verify secondary algorithm family.
 */
#define CRYPTO_82_HSM_CERTIFICATE_VERIFY_SECALGOFAM        (1uLL << 0u)

/**
 * \def   CRYPTO_82_HSM_CERTIFICATE_VERIFY_ALGO_MODE
 * \brief Certificate verify algorithm mode.
 */
#define CRYPTO_82_HSM_CERTIFICATE_VERIFY_ALGO_MODE         (1uL << 0u)

/**
 * \def   CRYPTO_82_HSM_CERTIFICATE_VERIFY_OPERATING_MODE
 * \brief Certificate verify operating mode.
 */
#define CRYPTO_82_HSM_CERTIFICATE_VERIFY_OPERATING_MODE    (1uL << 0u)

/**
 * \def   CRYPTO_82_HSM_CERTIFICATE_VERIFY_PROCESSING_MODE
 * \brief Certificate verify processing mode.
 */
#define CRYPTO_82_HSM_CERTIFICATE_VERIFY_PROCESSING_MODE   (1uL << 0u)

/*
* CRYPTO_82_HSM_RANDOM_SEED SERVICE
*/

/* TODO: Identify correct configuration, this is currently stubbed for testing purposes.*/
/**
 * \def   CRYPTO_82_HSM_RANDOM_SEED_ALGOFAM
 * \brief Random seed algorithm family.
 */
#define CRYPTO_82_HSM_RANDOM_SEED_ALGOFAM           (1uLL << CRYPTO_ALGOFAM_DRBG)

/**
 * \def   CRYPTO_82_HSM_RANDOM_SEED_SECALGOFAM
 * \brief Random seed secondary algorithm family.
 */
#define CRYPTO_82_HSM_RANDOM_SEED_SECALGOFAM        (1uLL << CRYPTO_ALGOFAM_NOT_SET)

/**
 * \def   CRYPTO_82_HSM_RANDOM_SEED_PROCESSING_MODE
 * \brief Random seed processing mode.
 */
#define CRYPTO_82_HSM_RANDOM_SEED_PROCESSING_MODE   ((CRYPTO_82_HSM_PROCESSING_ASYNC) | (CRYPTO_82_HSM_PROCESSING_SYNC ))

/**
 * \def   CRYPTO_82_HSM_RANDOM_SEED_ALGO_MODE
 * \brief Random seed algorithm mode.
 */
#define CRYPTO_82_HSM_RANDOM_SEED_ALGO_MODE         (1uL << CRYPTO_ALGOMODE_NOT_SET)

/**
 * \def   CRYPTO_82_HSM_RANDOM_SEED_OPERATING_MODE
 * \brief Random seed operating mode.
 */
#define CRYPTO_82_HSM_RANDOM_SEED_OPERATING_MODE    (1uL << CRYPTO_OPERATIONMODE_SINGLECALL)

/*
* CRYPTO_82_HSM_SEC_COUNTER_INCREMENT SERVICE
*/

/* TODO: Identify correct configuration, this is currently stubbed for testing purposes.*/
/**
 * \def   CRYPTO_82_HSM_SEC_COUNTER_INCREMENT_ALGOFAM
 * \brief Secure counter increment algorithm family.
 */
#define CRYPTO_82_HSM_SEC_COUNTER_INCREMENT_ALGOFAM           (1uLL << 0u)

/**
 * \def   CRYPTO_82_HSM_SEC_COUNTER_INCREMENT_ALGOSECFAM
 * \brief Secure counter increment secondary algorithm family.
 */
#define CRYPTO_82_HSM_SEC_COUNTER_INCREMENT_ALGOSECFAM        (1uLL << 0u)

/**
 * \def   CRYPTO_82_HSM_SEC_COUNTER_INCREMENT_ALGO_MODE
 * \brief Secure counter increment algorithm mode.
 */
#define CRYPTO_82_HSM_SEC_COUNTER_INCREMENT_ALGO_MODE         (1uL << 0u)

/**
 * \def   CRYPTO_82_HSM_SEC_COUNTER_INCREMENT_OPERATING_MODE
 * \brief Secure counter increment operating mode.
 */
#define CRYPTO_82_HSM_SEC_COUNTER_INCREMENT_OPERATING_MODE    (1uL << 0u)

/**
 * \def   CRYPTO_82_HSM_SEC_COUNTER_INCREMENT_PROCESSING_MODE
 * \brief Secure counter increment processing mode.
 */
#define CRYPTO_82_HSM_SEC_COUNTER_INCREMENT_PROCESSING_MODE   (1uL << 0u)

/*
* CRYPTO_82_HSM_SEC_COUNTER_READ SERVICE
*/

/* TODO: Identify correct configuration, this is currently stubbed for testing purposes.*/
/**
 * \def   CRYPTO_82_HSM_SEC_COUNTER_READ_ALGOFAM
 * \brief Secure counter read algorithm family.
 */
#define CRYPTO_82_HSM_SEC_COUNTER_READ_ALGOFAM           (1uLL << 0u)

/**
 * \def   CRYPTO_82_HSM_SEC_COUNTER_READ_ALGOSECFAM
 * \brief Secure counter read secondary algorithm family.
 */
#define CRYPTO_82_HSM_SEC_COUNTER_READ_ALGOSECFAM        (1uLL << 0u)

/**
 * \def   CRYPTO_82_HSM_SEC_COUNTER_READ_PROCESSING_MODE
 * \brief Secure counter read secondary processing mode.
 */
#define CRYPTO_82_HSM_SEC_COUNTER_READ_PROCESSING_MODE   (1uL << 0u)

/**
 * \def   CRYPTO_82_HSM_SEC_COUNTER_READ_ALGO_MODE
 * \brief Secure counter read secondary algorithm mode.
 */
#define CRYPTO_82_HSM_SEC_COUNTER_READ_ALGO_MODE         (1uL << 0u)

/**
 * \def   CRYPTO_82_HSM_SEC_COUNTER_READ_OPERATING_MODE
 * \brief Secure counter read secondary operating mode.
 */
#define CRYPTO_82_HSM_SEC_COUNTER_READ_OPERATING_MODE    (1uL << 0u)

/**
 * \def   CRYPTO_82_HSM_KEY_MANAGEMENT_CALLBACK_ERROR
 * \brief Value used for job id in case of key management APIs
 */
#define CRYPTO_82_HSM_CALLBACK_NO_JOBID_AVAILABLE    (0xFFFFFFFFu)
/**********************************************************************************************************************\
 * PUBLIC TYPE DEFINITIONS
\**********************************************************************************************************************/

/**
 * \brief Holds CSAI Parameters; session handle, job handle and job priority.
 */
typedef struct sCrypto_82_Hsm_Service_CsaiSessionType
{
    ecy_hsm_Csai_SessionHandleT hSession;
    ecy_hsm_Csai_JobHandleT hJob;
    ecy_hsm_Csai_JobPriorityT priority;
} Crypto_82_Hsm_Service_CsaiSessionType;

/**
 * \brief Crypto Service layer supported Hash algorithms.
 */
typedef enum eCrypto_82_Hsm_Service_HashAlgorithmType
{
    CryptoDriver_SHA1           = 1u,
    CryptoDriver_SHA2_256       = 2u,
    CryptoDriver_SHA2_512       = 3u,
    CryptoDriver_SHA2_224       = 4u,
    CryptoDriver_SHA2_384       = 5u,
    CryptoDriver_AES_MP         = 6u,
    CryptoDriver_HASH_RESERVED  = 0xffu
} Crypto_82_Hsm_Service_HashAlgorithmType;

/**
 * \brief Crypto Service layer supported Symmetric cipher modes.
 */
typedef enum eCrypto_82_Hsm_Service_SymCipherModeType
{
    CryptoDriver_AES_ECB            = 1,
    CryptoDriver_AES_CBC            = 2,
    CryptoDriver_AES_CFB128         = 3,
    CryptoDriver_AES_OFB            = 4,
    CryptoDriver_AES_CTR            = 5,
    CryptoDriver_AES_XTS            = 6,
    CryptoDriver_AES_GCM            = 7,
    CryptoDriver_SYMCIPHER_RESERVED = 0xffu
} Crypto_82_Hsm_Service_SymCipherModeType;

/**
 * \brief Crypto Service layer supported auto padding modes.
 */
typedef enum eCrypto_82_Hsm_Service_PaddingModeType
{
    CryptoDriver_PAD_NONE               = 1,
    CryptoDriver_PAD_PKCS7              = 2,
    CryptoDriver_NIST_SP800             = 3,
    CryptoDriver_PADDINGMODE_RESERVED   = 0xffu
} Crypto_82_Hsm_Service_PaddingModeType;

/**
 * \brief Crypto Service layer supported Asymmetric cipher modes.
 */
typedef enum eCrypto_82_Hsm_Service_AsymCipherModeType
{
    CryptoDriver_RSA_ES_PKCS1_v15       = 1,
    CryptoDriver_RSA_ES_OAEP            = 2,
    CryptoDriver_ASYMCIPHER_RESERVED    = 0x7fffffffu
} Crypto_82_Hsm_Service_AsymCipherModeType;

/**
* \brief Crypto Service layer supported Sign algorithms.
*/
typedef enum eCrypto_82_Hsm_Service_SignAlgorithmType
{
    CryptoDriver_RSA_SSA_PKCS1_1V5_SHA256           = 1,
    CryptoDriver_RSA_SSA_PSS_SHA256                 = 2,
    CryptoDriver_ED25519_SHA_512_PURE               = 3,
    CryptoDriver_ED25519_SHA_512_DOM2_PH            = 4,
    CryptoDriver_SECP224_SHA_224                    = 5,
    CryptoDriver_SECP256_SHA_256                    = 6,
    CryptoDriver_SECP384_SHA_512                    = 7,
    CryptoDriver_SECP384_SHA_384                    = 8,
    CryptoDriver_SECP384_SHA_256_USERHASHED         = 9,
    CryptoDriver_SECP384_SHA_384_USERHASHED         = 10,
    CryptoDriver_SECP384_SHA_512_USERHASHED         = 11,
    CryptoDriver_ED25519_SHA_512_DOM2_PH_USERHASHED = 12,
    CryptoDriver_SIGN_RESERVED                      = 0xffu
} Crypto_82_Hsm_Service_SignAlgorithmType;

/**
 * \brief Crypto Service layer supported Key Derive algorithms.
 */
typedef enum eCrypto_82_Hsm_KeyDeriveFunctionType
{
    CryptoDriver_KDF_PKCS5_PBKDF2 = 1u,
    CryptoDriver_KDF_NIST_SP800_56C_ONESTEP_AES_SHA256 = 2u,
    CryptoDriver_KDF_NIST_SP800_108_AES_CMAC = 3u,
    CryptoDriver_KDF_ANSI_X9_63 = 4u,
    CryptoDriver_KDF_RESERVED = 0xffu
} Crypto_82_Hsm_KeyDeriveFunctionType;

/**
 * \brief Crypto Service layer supported Key Exchange Calc Secret algorithms.
 */
typedef enum eCrypto_82_Hsm_KeyExchangeCalcSecretFunctionType
{
    CryptoDriver_ECDH_CURVE_P_224 = 1u,
    CryptoDriver_ECDH_CURVE_P_256 = 2u,
    CryptoDriver_ECDH_CURVE_P_384 = 3u,
    CryptoDriver_ECDH_RESERVED = 0xffu
} Crypto_82_Hsm_KeyExchangeCalcSecretFunctionType;

/**********************************************************************************************************************\
 * EXTERN PUBLIC VARIABLES
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * PUBLIC FUNCTION DECLARATIONS
\**********************************************************************************************************************/

#define CRYPTO_82_HSM_START_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"

/**
 * \brief                 Function used to determine whether a service from a job is supported or not.
 *
 * \param [in] job        Pointer to Crypto_JobType parameter passed from Crypto_ProcessJob.
 *
 * \retval TRUE           Service Supported.
 * \retval FALSE          Service Not Supported.
 */
static INLINE boolean isJobServiceSupported(const Crypto_JobType* job)
{
    boolean ret_val;
    const Crypto_82_Hsm_ServiceDataType* serviceData = &(Crypto_82_Hsm_ServiceDataArray[job->jobPrimitiveInfo->primitiveInfo->service]);

    if (job->jobPrimitiveInfo->primitiveInfo->service <= CRYPTO_KEYSETVALID) /* Checking if a configured job is supported by comparing the service algorithm family, algorithm mode, etc. combinations against the bit coded masks defined above in this file (e.g. CRYPTO_82_HSM_HASH_ALGOFAM). */
    {
        ret_val = (boolean)( ( serviceData->serviceSupported != 0u ) &&
                    (((1uLL << job->jobPrimitiveInfo->processingType) & serviceData->supportedProcessingTypes) != 0u ) && /* CRYPTO_82_HSM_****_PROCESSING_MODE */
                    (((1uLL << job->jobPrimitiveInfo->primitiveInfo->algorithm.mode) & serviceData->supportedAlgorithmMode) != 0u ) && /* CRYPTO_82_HSM_****_ALGO_MODE */
                    (((1uLL << job->jobPrimitiveInfo->primitiveInfo->algorithm.family) & serviceData->supportedAlgorithmFamily) != 0u ) && /* CRYPTO_82_HSM_****_ALGOFAM */
                    (((1uLL << job->jobPrimitiveInfo->primitiveInfo->algorithm.secondaryFamily )& serviceData->supportedAlgorithmSecondaryFamily) != 0u) && /* CRYPTO_82_HSM_****_ALGOSECFAM */
                    (((1uLL << job->jobPrimitiveInputOutput.mode) & serviceData->supportedOperatingMode ) != 0u ) ); /* CRYPTO_82_HSM_****_OPERATING_MODE */
    }
    else
    {
        ret_val = (boolean)( (serviceData->supportedProcessingTypes != 0x00u)    ||
                    (serviceData->supportedAlgorithmMode != 0x00u)               ||
                    (serviceData->supportedAlgorithmFamily != 0x00u)             ||
                    (serviceData->supportedAlgorithmSecondaryFamily != 0x00u) );
    }

    return ret_val;
}

/**
 * \brief Wait for a CSAI job to finish.
 * 
 * \param [in] jobHandle  The handle of the CSAI job.
 * \param [in] serviceId    The service for which polling is done.
 * \param [in] jobId        The jobID for which the polling is done.
 * 
 * \retval E_OK           The job finished successfully.
 * \retval E_NOT_OK       The job encountered an error.
 */
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_WaitForJobFinished(ecy_hsm_Csai_JobHandleT jobHandle, uint8 serviceId, uint32 jobId);

/**
 * \brief Poll the status of a CSAI job.
 * 
 * \param [in] jobHandle The handle of the CSAI job.
 * \param [in] serviceId    The service for which polling is done.
 * \param [in] jobId        The jobID for which the polling is done.
 * \param [in] objectId     Id of the crypto driver object.
 * 
 * \retval E_OK                                     The job has finished successfully.
 * \retval CRYPTO_E_ENTROPY_EXHAUSTED               The job has finished with this specific error code
 * \retval CRYPTO_E_CUSTOM_VAL_TAG_NOT_FOUND        The job has finished with this specific error code
 * \retval E_NOT_OK                                 The job encountered an error.
 * \retval CRYPTO_E_BUSY                            The job is pending.
 */
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_PollJob(ecy_hsm_Csai_JobHandleT jobHandle, uint8 serviceId, uint32 jobId, uint32 objectId);

/**
 * \brief Executes Asymmetric encryption job.
 *
 * \param [in, out] csaiSession     Pointer to structure which contains CSAI session handle, job priority and job handle.
 * \param [in]      hKey            CSAI Key Handle or keyId.
 * \param [in]      asymCipherMode  Asymmetric cipher mode to use.
 * \param [in]      msg             Pointer to message to encrypt.
 * \param [in]      msg_len         Length of the provided message.
 * \param [out]     cipher          Pointer to where to store the encrypted message.
 * \param [in, out] cipher_len      Pointer to the length of the cipher and buffer where the function stores the amount of bytes that have been written to the cipher buffer.
 *
 * \retval errorCode                Return value of the CSAI call that has been performed.
 */
FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_AsymC_Encrypt
(
    P2VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC, CRYPTO_82_HSM_VAR) csaiSession, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(ecy_hsm_Csai_KeyHandleT, AUTOMATIC) hKey,
    VAR(Crypto_82_Hsm_Service_AsymCipherModeType, AUTOMATIC) asymCipherMode,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) msg,
    VAR(uint32, CRYPTO_82_HSM_VAR) msg_len,
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) cipher, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) cipher_len /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
);

/**
 * \brief Executes Asymmetric decryption job.
 *
 * \param [in, out] csaiSession     Pointer to structure which contains CSAI session handle, job priority and job handle.
 * \param [in]      hKey            CSAI Key Handle or keyId.
 * \param [in]      asymCipherMode  Asymmetric cipher mode to use.
 * \param [in]      cipher          Pointer to cipher text to decrypt.
 * \param [in]      cipher_len      Length of the provided cipher text.
 * \param [out]     msg             Pointer to where to store the decrypted cipher text.
 * \param [in, out] msg_len         Pointer to the length of the message buffer and where the function stores the amount of bytes that have been written to the message buffer.
 *
 * \retval errorCode                Return value of the CSAI call that has been performed.
 */
FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_AsymC_Decrypt
(
    P2VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC, CRYPTO_82_HSM_VAR) csaiSession, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(ecy_hsm_Csai_KeyHandleT, AUTOMATIC) hKey,
    VAR(Crypto_82_Hsm_Service_AsymCipherModeType, AUTOMATIC) asymCipherMode,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) cipher,
    VAR(uint32, CRYPTO_82_HSM_VAR) cipher_len,
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) msg, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) msg_len /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
);

/**
 * \brief Executes Hash calculation job.
 *
 * \param [in, out] csaiSession     Pointer to structure which contains CSAI session handle, job priority and job handle.
 * \param [in]      hashAlgo        Hash algorithm variant to use.
 * \param [in]      msg             Pointer to message to hash.
 * \param [in]      msg_len         Length of the provided message.
 * \param [out]     digest          Pointer to where to store the hash digest.
 * \param [in, out] digest_len      Pointer to the length of the hash digest and buffer where the function stores the amount of bytes that have been written to the hash digest buffer.
 *
 * \retval errorCode                Return value of the CSAI call that has been performed.
 */
FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Hash_Compute
(
    P2VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC, CRYPTO_82_HSM_VAR) csaiSession, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(Crypto_82_Hsm_Service_HashAlgorithmType, AUTOMATIC) hashAlgo,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) msg,
    VAR(uint32, AUTOMATIC) msg_len,
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) digest, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) digest_len    /*[SWS_Crypto_00071]*/ /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
);

/**
 * \brief Executes START operation of Hash calculation job.
 *
 * \param [in, out] csaiSession     Pointer to structure which contains CSAI session handle, job priority and job handle.
 * \param [in]      hashAlgo        Hash algorithm variant to use.
 * \param [in]      msg             Pointer to message to hash.
 * \param [in]      msg_len         Length of the provided message.
 *
 * \retval errorCode                Return value of the CSAI call that has been performed.
 */
FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Hash_Start
(
    P2VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC, CRYPTO_82_HSM_VAR) csaiSession, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(Crypto_82_Hsm_Service_HashAlgorithmType, AUTOMATIC) hashAlgo,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) msg,
    VAR(uint32, AUTOMATIC) msg_len
);

/**
 * \brief Executes UPDATE operation of Hash calculation job.
 *
 * \param [in]      csaiSession     Pointer to structure which contains CSAI session handle, job priority and job handle.
 * \param [in]      msg             Pointer to message to hash.
 * \param [in]      msg_len         Length of the provided message.
 *
 * \retval errorCode                Return value of the CSAI call that has been performed.
 */
FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Hash_Update
(
    VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC) csaiSession,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) msg,
    VAR(uint32, AUTOMATIC) msg_len
);

/**
 * \brief Executes FINISH operation of Hash calculation job.
 *
 * \param [in]      csaiSession     Pointer to structure which contains CSAI session handle, job priority and job handle.
 * \param [out]     digest          Pointer to where to store the hash digest.
 * \param [in, out] digest_len      Pointer to the length of the hash digest and buffer where the function stores the amount of bytes that have been written to the hash digest buffer.
 *
 * \retval errorCode                Return value of the CSAI call that has been performed.
 */
FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Hash_Finish
(
    VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC) csaiSession,
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) digest, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) digest_len    /*[SWS_Crypto_00071]*/ /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
);

/**
 * \brief Executes MAC signature generation job.
 *
 * \param [in, out] csaiSession     Pointer to structure which contains CSAI session handle, job priority and job handle.
 * \param [in]      hKey            CSAI Key Handle or keyId.
 * \param [in]      macAlgo         MAC algorithm variant to use.
 * \param [in]      msg             Pointer to message to sign.
 * \param [in]      msg_len         Length of the provided message.
 * \param [out]     mac             Pointer to where to store the signed message.
 * \param [in, out] mac_len         Pointer to the length of the MAC and buffer where the function stores the amount of bytes that have been written to the MAC buffer.
 *
 * \retval errorCode                Return value of the CSAI call that has been performed.
 */
FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Mac_Generate
(
    P2VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC, CRYPTO_82_HSM_VAR) csaiSession, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(ecy_hsm_Csai_KeyHandleT, AUTOMATIC) hKey,
    VAR(Crypto_82_Hsm_Service_MACAlgorithmType, AUTOMATIC) macAlgo,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) msg,
    VAR(uint32, AUTOMATIC) msg_len,
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) mac, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) mac_len /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
);

/**
 * \brief Executes START operation of MAC signature generation job.
 *
 * \param [in, out] csaiSession     Pointer to structure which contains CSAI session handle, job priority and job handle.
 * \param [in]      hKey            CSAI Key Handle or keyId.
 * \param [in]      macAlgo         MAC algorithm variant to use.
 * \param [in]      msg             Pointer to message to sign.
 * \param [in]      msg_len         Length of the provided message.
 *
 * \retval errorCode                Return value of the CSAI call that has been performed.
 */
FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Mac_Generate_Start
(
    P2VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC, CRYPTO_82_HSM_VAR) csaiSession, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(ecy_hsm_Csai_KeyHandleT, AUTOMATIC) hKey,
    VAR(Crypto_82_Hsm_Service_MACAlgorithmType, AUTOMATIC) macAlgo,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) msg,
    VAR(uint32, AUTOMATIC) msg_len
);

/**
 * \brief Executes UPDATE operation of MAC signature generation job.
 *
 * \param [in]      csaiSession     Pointer to structure which contains CSAI session handle, job priority and job handle.
 * \param [in]      msg             Pointer to message to sign.
 * \param [in]      msg_len         Length of the provided message.
 *
 * \retval errorCode                Return value of the CSAI call that has been performed.
 */
FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Mac_Generate_Update
(
    VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC) csaiSession,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) msg,
    VAR(uint32, AUTOMATIC) msg_len
);

/**
 * \brief Executes FINISH operation of MAC signature generation job.
 *
 * \param [in]      csaiSession     Pointer to structure which contains CSAI session handle, job priority and job handle.
 * \param [out]     mac             Pointer to where to store the signed message.
 * \param [in, out] mac_len         Pointer to the length of the MAC and buffer where the function stores the amount of bytes that have been written to the MAC buffer.
 *
 * \retval errorCode                Return value of the CSAI call that has been performed.
 */
FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Mac_Generate_Finish
(
    VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC) csaiSession,
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) mac, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) mac_len /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
);

/**
 * \brief Executes MAC signature verification job.
 *
 * \param [in, out] csaiSession          Pointer to structure which contains CSAI session handle, job priority and job handle.
 * \param [in]      hKey                 CSAI Key Handle or keyId.
 * \param [in]      macAlgo              MAC algorithm variant to use.
 * \param [in]      msg                  Pointer to message to sign.
 * \param [in]      msg_len              Length of the provided message.
 * \param [in]      mac                  Pointer to expected MAC.
 * \param [in]      mac_size             MAC length in bits.
 * \param [out]     verificationResult   Verification result (0u = verification failed, 1u = verification successful).
 *
 * \retval errorCode                     Return value of the CSAI call that has been performed.
 */
FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Mac_Verify
(
    P2VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC, CRYPTO_82_HSM_VAR) csaiSession, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(ecy_hsm_Csai_KeyHandleT, AUTOMATIC) hKey,
    VAR(Crypto_82_Hsm_Service_MACAlgorithmType, AUTOMATIC) macAlgo,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) msg,
    VAR(uint32, AUTOMATIC) msg_len,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) mac,
    VAR(uint32, AUTOMATIC) mac_size,
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) verificationResult /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
);

/**
 * \brief Executes START operation of MAC signature verification job.
 *
 * \param [in, out] csaiSession          Pointer to structure which contains CSAI session handle, job priority and job handle.
 * \param [in]      hKey                 CSAI Key Handle or keyId.
 * \param [in]      macAlgo              MAC algorithm variant to use.
 * \param [in]      msg                  Pointer to message to sign.
 * \param [in]      msg_len              Length of the provided message.
 *
 * \retval errorCode                     Return value of the CSAI call that has been performed.
 */
FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Mac_Verify_Start
(
    P2VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC, CRYPTO_82_HSM_VAR) csaiSession, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(ecy_hsm_Csai_KeyHandleT, AUTOMATIC) hKey,
    VAR(Crypto_82_Hsm_Service_MACAlgorithmType, AUTOMATIC) macAlgo,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) msg,
    VAR(uint32, AUTOMATIC) msg_len
);

/**
 * \brief Executes UPDATE operation of MAC signature verification job.
 *
 * \param [in]      csaiSession          Pointer to structure which contains CSAI session handle, job priority and job handle.
 * \param [in]      msg                  Pointer to message to sign.
 * \param [in]      msg_len              Length of the provided message.
 *
 * \retval errorCode                     Return value of the CSAI call that has been performed.
 */
FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Mac_Verify_Update
(
    VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC) csaiSession,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) msg,
    VAR(uint32, AUTOMATIC) msg_len
);

/**
 * \brief Executes FINISH operation of MAC signature verification job.
 *
 * \param [in]      csaiSession          Pointer to structure which contains CSAI session handle, job priority and job handle.
 * \param [in]      mac                  Pointer to expected MAC.
 * \param [in]      mac_size             Length of the provided message.
 * \param [out]     verificationResult   Verification result (0u = verification failed, 1u = verification successful).
 *
 * \retval errorCode                     Return value of the CSAI call that has been performed.
 */
FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Mac_Verify_Finish
(
    VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC) csaiSession,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) mac,
    VAR(uint32, AUTOMATIC) mac_size,
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) verificationResult /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
);

#if (CRYPTO_82_HSM_DENSO_BULK_MAC == STD_ON)

/**
 * \brief Triggers bulk mac generation operation.
 *
 * \param [in]      numBulkMacJobs       Number of mac jobs to trigger in the bulkMac interface.
 *
 * \retval ret      E_OK                 Dispatching successful.
 * \retval ret      E_NOT_OK             Dispatching unsuccessful.
 */
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Bulk_Mac_Generate_Fast(VAR(uint32, AUTOMATIC) numBulkMacJobs);

/**
 * \brief Triggers bulk mac verification operation.
 *
 * \param [in]      numBulkMacJobs       Number of mac jobs to trigger in the bulkMac interface.
 *
 * \retval ret      E_OK                 Dispatching successful.
 * \retval ret      E_NOT_OK             Dispatching unsuccessful.
 */
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Bulk_Mac_Verify_Fast(VAR(uint32, AUTOMATIC) numBulkMacJobs);

#endif

/**
 * \brief Executes Pseudo Random Number Generation job.
 *
 * \param [in, out] csaiSession          Pointer to structure which contains CSAI session handle, job priority and job handle.
 * \param [out]     random               Pointer to buffer to receive the random number data.
 * \param [in]      random_len           Length of buffer to receive the random number data.
 *
 * \retval errorCode                     Return value of the CSAI call that has been performed.
 */
FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Rng_Pseudo
(
    P2VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC, CRYPTO_82_HSM_VAR) csaiSession, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) random, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(uint32, AUTOMATIC) random_len
);

/**
 * \brief Executes True Random Number Generation job.
 *
 * \param [in, out] csaiSession          Pointer to structure which contains CSAI session handle, job priority and job handle.
 * \param [out]     random               Pointer to buffer to receive the random number data.
 * \param [in]      random_len           Length of buffer to receive the random number data.
 *
 * \retval errorCode                     Return value of the CSAI call that has been performed.
 */
FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Rng_True
(
    P2VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC, CRYPTO_82_HSM_VAR) csaiSession, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) random, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(uint32, AUTOMATIC) random_len
);

/**
 * \brief Executes re-seed for the pseudo random number generation.
 *
 * \param [in, out] csaiSession          Pointer to structure which contains CSAI session handle, job priority and job handle.
 * \param [in]      seed                 Pointer to buffer where seed to be provided for the PRNG is located.
 * \param [in]      seed_len             Length of the provided seed buffer.
 *
 * \retval errorCode                     Return value of the CSAI call that has been performed.
 */
FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Rng_Reseed
(
    P2VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC, CRYPTO_82_HSM_VAR) csaiSession, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) seed,
    VAR(uint32, AUTOMATIC) seed_len
);

/**
 * \brief Executes Signature generation job.
 * 
 * \param [in, out] csaiSession     Pointer to structure which contains CSAI session handle, job priority and job handle.
 * \param [in]      hKey            CSAI Key Handle or keyId.
 * \param [in]      signAlgo        Sign algorithm variant to use.
 * \param [in]      msg             Pointer to message to sign.
 * \param [in]      msg_len         Length of the provided message.
 * \param [out]     sign            Pointer to where to store the signed message.
 * \param [in, out] sign_len        Pointer to the length of the signature and buffer where the function stores the amount of bytes that have been written to the signature buffer.
 *
 * \retval errorCode                Return value of the CSAI call that has been performed.
 */
FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Sign_Generate
(
    P2VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC, CRYPTO_82_HSM_VAR) csaiSession, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(ecy_hsm_Csai_KeyHandleT, AUTOMATIC) hKey,
    VAR(Crypto_82_Hsm_Service_SignAlgorithmType, AUTOMATIC) signAlgo,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) msg,
    VAR(uint32, AUTOMATIC) msg_len,
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) sign, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) sign_len /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
);

/**
 * \brief Executes START operation of Signature generation job.
 * 
 * \param [in, out] csaiSession     Pointer to structure which contains CSAI session handle, job priority and job handle.
 * \param [in]      hKey            CSAI Key Handle or keyId.
 * \param [in]      signAlgo        Sign algorithm variant to use.
 * \param [in]      msg             Pointer to message to sign.
 * \param [in]      msg_len         Length of the provided message.
 *
 * \retval errorCode                Return value of the CSAI call that has been performed.
 */
FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Sign_Generate_Start
(
    P2VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC, CRYPTO_82_HSM_VAR) csaiSession, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(ecy_hsm_Csai_KeyHandleT, AUTOMATIC) hKey,
    VAR(Crypto_82_Hsm_Service_SignAlgorithmType, AUTOMATIC) signAlgo,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) msg,
    VAR(uint32, AUTOMATIC) msg_len
);

/**
 * \brief Executes UPDATE operation of Signature generation job.
 * 
 * \param [in]      csaiSession     Pointer to structure which contains CSAI session handle, job priority and job handle.
 * \param [in]      msg             Pointer to message to sign.
 * \param [in]      msg_len         Length of the provided message.
 *
 * \retval errorCode                Return value of the CSAI call that has been performed.
 */
FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Sign_Generate_Update
(
    VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC) csaiSession,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) msg,
    VAR(uint32, AUTOMATIC) msg_len
);

/**
 * \brief Executes FINISH operation of Signature generation job.
 * 
 * \param [in]      csaiSession     Pointer to structure which contains CSAI session handle, job priority and job handle.
 * \param [out]     sign            Pointer to where to store the signed message.
 * \param [in, out] sign_len        Pointer to the length of the signature and buffer where the function stores the amount of bytes that have been written to the signature buffer.
 *
 * \retval errorCode                Return value of the CSAI call that has been performed.
 */
FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Sign_Generate_Finish
(
    VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC) csaiSession,
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) sign, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) sign_len /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
);

/**
 * \brief Executes Signature verification job.
 *
 * \param [in, out] csaiSession          Pointer to structure which contains CSAI session handle, job priority and job handle.
 * \param [in]      hKey                 CSAI Key Handle or keyId.
 * \param [in]      signAlgo             Sign algorithm variant to use.
 * \param [in]      msg                  Pointer to message to sign.
 * \param [in]      msg_len              Length of the provided message.
 * \param [in]      sign                 Pointer to expected signature.
 * \param [in]      sign_len             Signature length.
 * \param [out]     verificationResult   Verification result (0u = verification failed, 1u = verification successful).
 *
 * \retval errorCode                     Return value of the CSAI call that has been performed.
 */
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
);

/**
 * \brief Executes START operation of Signature verification job.
 *
 * \param [in, out] csaiSession          Pointer to structure which contains CSAI session handle, job priority and job handle.
 * \param [in]      hKey                 CSAI Key Handle or keyId.
 * \param [in]      signAlgo             Sign algorithm variant to use.
 * \param [in]      msg                  Pointer to message to sign.
 * \param [in]      msg_len              Length of the provided message.
 *
 * \retval errorCode                     Return value of the CSAI call that has been performed.
 */
FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Sign_Verify_Start
(
    P2VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC, CRYPTO_82_HSM_VAR) csaiSession, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(ecy_hsm_Csai_KeyHandleT, AUTOMATIC) hKey,
    VAR(Crypto_82_Hsm_Service_SignAlgorithmType, AUTOMATIC) signAlgo,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) msg,
    VAR(uint32, AUTOMATIC) msg_len
);

/**
 * \brief Executes UPDATE operation of Signature verification job.
 *
 * \param [in]      csaiSession          Pointer to structure which contains CSAI session handle, job priority and job handle.
 * \param [in]      msg                  Pointer to message to sign.
 * \param [in]      msg_len              Length of the provided message.
 *
 * \retval errorCode                     Return value of the CSAI call that has been performed.
 */
FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Sign_Verify_Update
(
    VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC) csaiSession,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) msg,
    VAR(uint32, AUTOMATIC) msg_len
);

/**
 * \brief Executes FINISH operation of Signature verification job.
 *
 * \param [in]      csaiSession          Pointer to structure which contains CSAI session handle, job priority and job handle.
 * \param [in]      sign                 Pointer to expected signature.
 * \param [in]      sign_len             Signature length.
 * \param [out]     verificationResult   Verification result (0u = verification failed, 1u = verification successful).
 *
 * \retval errorCode                     Return value of the CSAI call that has been performed.
 */
FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Sign_Verify_Finish
(
    VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC) csaiSession,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) sign,
    VAR(uint32, AUTOMATIC) sign_len,
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) verificationResult /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
);

/**
 * \brief Executes Symmetric encryption job.
 *
 * \param [in, out] csaiSession     Pointer to structure which contains CSAI session handle, job priority and job handle.
 * \param [in]      hKey            CSAI Key Handle or keyId.
 * \param [in]      symCipherMode   Symmetric cipher mode to use.
 * \param [in]      paddingMode     Padding mode to use.
 * \param [in]      msg             Pointer to message to encrypt.
 * \param [in]      msg_len         Length of the provided message.
 * \param [in]      iv              Pointer to initialization vector.
 * \param [in]      iv_len          Length of the provided initialization vector.
 * \param [out]     cipher          Pointer to where to store the encrypted message.
 * \param [in, out] cipher_len      Pointer to the length of the cipher and buffer where the function stores the amount of bytes that have been written to the cipher buffer.
 *
 * \retval errorCode                Return value of the CSAI call that has been performed.
 */
FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_SymC_Encrypt
(
    P2VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC, CRYPTO_82_HSM_VAR) csaiSession, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(ecy_hsm_Csai_KeyHandleT, AUTOMATIC) hKey,
    VAR(Crypto_82_Hsm_Service_SymCipherModeType, AUTOMATIC) symCipherMode,
    VAR(Crypto_82_Hsm_Service_PaddingModeType, AUTOMATIC) paddingMode,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) msg,
    VAR(uint32, AUTOMATIC) msg_len,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) iv,
    VAR(uint32, AUTOMATIC) iv_len,
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) cipher, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) cipher_len /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
);

/**
 * \brief Executes START operation of Symmetric encryption job.
 *
 * \param [in, out] csaiSession     Pointer to structure which contains CSAI session handle, job priority and job handle.
 * \param [in]      hKey            CSAI Key Handle or keyId.
 * \param [in]      symCipherMode   Symmetric cipher mode to use.
 * \param [in]      paddingMode     Padding mode to use.
 * \param [in]      msg             Pointer to message to encrypt.
 * \param [in]      msg_len         Length of the provided message.
 * \param [in]      iv              Pointer to initialization vector.
 * \param [in]      iv_len          Length of the provided initialization vector.
 * \param [out]     cipher          Pointer to where to store the encrypted message.
 * \param [in, out] cipher_len      Pointer to the length of the cipher and buffer where the function stores the amount of bytes that have been written to the cipher buffer.
 *
 * \retval errorCode                Return value of the CSAI call that has been performed.
 */
FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_SymC_Encrypt_Start
(
    P2VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC, CRYPTO_82_HSM_VAR) csaiSession, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(ecy_hsm_Csai_KeyHandleT, AUTOMATIC) hKey,
    VAR(Crypto_82_Hsm_Service_SymCipherModeType, AUTOMATIC) symCipherMode,
    VAR(Crypto_82_Hsm_Service_PaddingModeType, AUTOMATIC) paddingMode,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) msg,
    VAR(uint32, AUTOMATIC) msg_len,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) iv,
    VAR(uint32, AUTOMATIC) iv_len,
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) cipher, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) cipher_len /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
);

/**
 * \brief Executes UPDATE operation of Symmetric encryption job.
 *
 * \param [in]      csaiSession     Pointer to structure which contains CSAI session handle, job priority and job handle.
 * \param [in]      msg             Pointer to message to encrypt.
 * \param [in]      msg_len         Length of the provided message.
 * \param [out]     cipher          Pointer to where to store the encrypted message.
 * \param [in, out] cipher_len      Pointer to the length of the cipher and buffer where the function stores the amount of bytes that have been written to the cipher buffer.
 *
 * \retval errorCode                Return value of the CSAI call that has been performed.
 */
FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_SymC_Encrypt_Update
(
    VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC) csaiSession,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) msg,
    VAR(uint32, AUTOMATIC) msg_len,
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) cipher, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) cipher_len /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
);

/**
 * \brief Executes FINISH operation of Symmetric encryption job.
 *
 * \param [in]      csaiSession     Pointer to structure which contains CSAI session handle, job priority and job handle.
 * \param [out]     cipher          Pointer to where to store the encrypted message.
 * \param [in, out] cipher_len      Pointer to the length of the cipher and buffer where the function stores the amount of bytes that have been written to the cipher buffer.
 *
 * \retval errorCode                Return value of the CSAI call that has been performed.
 */
FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_SymC_Encrypt_Finish
(
    VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC) csaiSession,
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) cipher, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) cipher_len /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
);

/**
 * \brief Executes Symmetric decryption job.
 *
 * \param [in, out] csaiSession     Pointer to structure which contains CSAI session handle, job priority and job handle.
 * \param [in]      hKey            CSAI Key Handle or keyId.
 * \param [in]      symCipherMode   Symmetric cipher mode to use.
 * \param [in]      paddingMode     Padding mode to use.
 * \param [in]      cipher          Pointer to cipher to decrypt.
 * \param [in]      cipher_len      Length of the provided cipher.
 * \param [in]      iv              Pointer to initialization vector.
 * \param [in]      iv_len          Length of the provided initialization vector.
 * \param [out]     msg             Pointer to where to store the decrypted message.
 * \param [in, out] msg_len         Pointer to the length of the message and buffer where the function stores the amount of bytes that have been written to the message buffer.
 *
 * \retval errorCode                Return value of the CSAI call that has been performed.
 */
FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_SymC_Decrypt
(
    P2VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC, CRYPTO_82_HSM_VAR) csaiSession, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(ecy_hsm_Csai_KeyHandleT, AUTOMATIC) hKey,
    VAR(Crypto_82_Hsm_Service_SymCipherModeType, AUTOMATIC) symCipherMode,
    VAR(Crypto_82_Hsm_Service_PaddingModeType, AUTOMATIC) paddingMode,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) cipher,
    VAR(uint32, AUTOMATIC) cipher_len,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) iv,
    VAR(uint32, AUTOMATIC) iv_len,
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) msg, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) msg_len /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
);

/**
 * \brief Executes START operation of Symmetric decryption job.
 *
 * \param [in, out] csaiSession     Pointer to structure which contains CSAI session handle, job priority and job handle.
 * \param [in]      hKey            CSAI Key Handle or keyId.
 * \param [in]      symCipherMode   Symmetric cipher mode to use.
 * \param [in]      paddingMode     Padding mode to use.
 * \param [in]      cipher          Pointer to cipher to decrypt.
 * \param [in]      cipher_len      Length of the provided cipher.
 * \param [in]      iv              Pointer to initialization vector.
 * \param [in]      iv_len          Length of the provided initialization vector.
 * \param [out]     msg             Pointer to where to store the decrypted message.
 * \param [in, out] msg_len         Pointer to the length of the message and buffer where the function stores the amount of bytes that have been written to the message buffer.
 *
 * \retval errorCode                Return value of the CSAI call that has been performed.
 */
FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_SymC_Decrypt_Start
(
    P2VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC, CRYPTO_82_HSM_VAR) csaiSession, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(ecy_hsm_Csai_KeyHandleT, AUTOMATIC) hKey,
    VAR(Crypto_82_Hsm_Service_SymCipherModeType, AUTOMATIC) symCipherMode,
    VAR(Crypto_82_Hsm_Service_PaddingModeType, AUTOMATIC) paddingMode,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) cipher,
    VAR(uint32, AUTOMATIC) cipher_len,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) iv,
    VAR(uint32, AUTOMATIC) iv_len,
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) msg, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) msg_len /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
);

/**
 * \brief Executes UPDATE operation of Symmetric decryption job.
 *
 * \param [in]      csaiSession     Pointer to structure which contains CSAI session handle, job priority and job handle.
 * \param [in]      cipher          Pointer to cipher to decrypt.
 * \param [in]      cipher_len      Length of the provided cipher.
 * \param [out]     msg             Pointer to where to store the decrypted message.
 * \param [in, out] msg_len         Pointer to the length of the message and buffer where the function stores the amount of bytes that have been written to the message buffer.
 *
 * \retval errorCode                Return value of the CSAI call that has been performed.
 */
FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_SymC_Decrypt_Update
(
    VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC) csaiSession,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) cipher,
    VAR(uint32, AUTOMATIC) cipher_len,
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) msg, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) msg_len /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
);

/**
 * \brief Executes FINISH operation of Symmetric decryption job.
 *
 * \param [in]      csaiSession     Pointer to structure which contains CSAI session handle, job priority and job handle.
 * \param [out]     msg             Pointer to where to store the decrypted message.
 * \param [in, out] msg_len         Pointer to the length of the message and buffer where the function stores the amount of bytes that have been written to the message buffer.
 *
 * \retval errorCode                Return value of the CSAI call that has been performed.
 */
FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_SymC_Decrypt_Finish
(
    VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC) csaiSession,
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) msg, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) msg_len /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
);

/**
 * \brief Executes Authenticated Decryption job.
 *
 * \param [in, out] csaiSession       Pointer to structure which contains CSAI session handle, job priority and job handle.
 * \param [in]      hKey              CSAI Key Handle or keyId.
 * \param [in]      symCipherMode     Symmetric cipher mode to use.
 * \param [in]      paddingMode       Padding mode to use.
 * \param [in]      cipher            Pointer to cipher to decrypt.
 * \param [in]      cipher_len        Length of the provided cipher.
 * \param [in]      iv                Pointer to initialization vector.
 * \param [in]      iv_len            Length of the provided initialization vector.
 * \param [in]      aad               Pointer to data for authentication.
 * \param [in]      aadLength         Length of the data for authentication.
 * \param [out]     msg               Pointer to buffer to store any residual decrypted message.
 * \param [in, out] msg_length        Pointer to the length of the message and buffer where the function stores the amount of bytes that have been written to the message buffer.
 * \param [out]     pTag              Pointer to buffer to receive the authentication tag data.
 * \param [in]      tagLength         Length of buffer for authentication tag data (should be at least 16 bytes).
 *
 * \retval errorCode                  Return value of the CSAI call that has been performed.
 */
FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Auth_Decrypt
(
    P2VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC, CRYPTO_82_HSM_VAR) csaiSession, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(ecy_hsm_Csai_KeyHandleT, AUTOMATIC) hKey,
    VAR(Crypto_82_Hsm_Service_SymCipherModeType, AUTOMATIC) symCipherMode,
    VAR(Crypto_82_Hsm_Service_PaddingModeType, AUTOMATIC) paddingMode,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) cipher,
    VAR(uint32, AUTOMATIC) cipher_len,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) iv,
    VAR(uint32, AUTOMATIC) iv_len,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) aad,
    VAR(uint32, AUTOMATIC) aadLength,
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) msg, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) msg_length, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) pTag, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(uint32, AUTOMATIC) tagLength
);

/**
 * \brief Executes START operation of Authenticated Decryption job.
 *
 * \param [in, out] csaiSession       Pointer to structure which contains CSAI session handle, job priority and job handle.
 * \param [in]      hKey              CSAI Key Handle or keyId.
 * \param [in]      symCipherMode     Symmetric cipher mode to use.
 * \param [in]      paddingMode       Padding mode to use.
 * \param [in]      iv                Pointer to initialization vector.
 * \param [in]      iv_len            Length of the provided initialization vector.
 *
 * \retval errorCode                  Return value of the CSAI call that has been performed.
 */
FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Auth_Decrypt_Start
(
    P2VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC, CRYPTO_82_HSM_VAR) csaiSession, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(ecy_hsm_Csai_KeyHandleT, AUTOMATIC) hKey,
    VAR(Crypto_82_Hsm_Service_SymCipherModeType, AUTOMATIC) symCipherMode,
    VAR(Crypto_82_Hsm_Service_PaddingModeType, AUTOMATIC) paddingMode,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) iv,
    VAR(uint32, AUTOMATIC) iv_len
);

/**
 * \brief Executes UPDATE operation of Authenticated Decryption job.
 *
 * \param [in]      csaiSession       Pointer to structure which contains CSAI session handle, job priority and job handle.
 * \param [in]      aad               Pointer to data for authentication.
 * \param [in]      aadLength         Length of the data for authentication.
 *
 * \retval errorCode                  Return value of the CSAI call that has been performed.
 */
FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Auth_Decrypt_Update
(
        VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC) csaiSession,
        P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) aad,
        VAR(uint32, AUTOMATIC) aadLength
);

/**
 * \brief Executes FINISH operation of Authenticated Decryption job.
 *
 * \param [in]      csaiSession       Pointer to structure which contains CSAI session handle, job priority and job handle.
 * \param [out]     msg               Pointer to buffer to store any residual decrypted message.
 * \param [in, out] msg_length        Pointer to the length of the message and buffer where the function stores the amount of bytes that have been written to the message buffer.
 * \param [out]     pTag              Pointer to buffer to receive the authentication tag data.
 * \param [in]      tagLength         Length of buffer for authentication tag data (should be at least 16 bytes).
 *
 * \retval errorCode                  Return value of the CSAI call that has been performed.
 */
FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Auth_Decrypt_Finish
(
        VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC) csaiSession,
        P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) msg, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
        P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) msg_len, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
        P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) pTag, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
        VAR(uint32, AUTOMATIC) tagLength
);

/**
 * \brief Executes Authenticated Encryption job.
 * 
 * \param [in, out] csaiSession       Pointer to structure which contains CSAI session handle, job priority and job handle.
 * \param [in]      hKey              CSAI Key Handle or keyId.
 * \param [in]      symCipherMode     Symmetric cipher mode to use.
 * \param [in]      paddingMode       Padding mode to use.
 * \param [in]      msg               Pointer to message to encrypt.
 * \param [in]      msg_len           Length of the provided message.
 * \param [in]      iv                Pointer to initialization vector.
 * \param [in]      iv_len            Length of the provided initialization vector.
 * \param [in]      aad               Pointer to data for authentication.
 * \param [in]      aadLength         Length of the data for authentication.
 * \param [out]     cipher            Pointer to where to store the encrypted message.
 * \param [in, out] cipher_len        Pointer to the length of the cipher and buffer where the function stores the amount of bytes that have been written to the cipher buffer.
 * \param [out]     pTag              Pointer to buffer to receive the authentication tag data.
 * \param [in]      tagLength         Length of buffer for authentication tag data (should be at least 16 bytes).
 * 
 * \retval errorCode                  Return value of the CSAI call that has been performed.
 */
FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Auth_Encrypt
(
    P2VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC, CRYPTO_82_HSM_VAR) csaiSession, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(ecy_hsm_Csai_KeyHandleT, AUTOMATIC) hKey,
    VAR(Crypto_82_Hsm_Service_SymCipherModeType, AUTOMATIC) symCipherMode,
    VAR(Crypto_82_Hsm_Service_PaddingModeType, AUTOMATIC) paddingMode,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) msg,
    VAR(uint32, AUTOMATIC) msg_len,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) iv,
    VAR(uint32, AUTOMATIC) iv_len,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) aad,
    VAR(uint32, AUTOMATIC) aadLength,
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) cipher, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) cipher_len, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) pTag, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(uint32, AUTOMATIC) tagLength
);

/**
 * \brief Executes START operation of Authenticated Encryption job.
 * 
 * \param [in, out] csaiSession       Pointer to structure which contains CSAI session handle, job priority and job handle.
 * \param [in]      hKey              CSAI Key Handle or keyId.
 * \param [in]      symCipherMode     Symmetric cipher mode to use.
 * \param [in]      paddingMode       Padding mode to use.
 * \param [in]      iv                Pointer to initialization vector.
 * \param [in]      iv_len            Length of the provided initialization vector.
 * 
 * \retval errorCode                  Return value of the CSAI call that has been performed.
 */
FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Auth_Encrypt_Start
(
        P2VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC, CRYPTO_82_HSM_VAR) csaiSession, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
        VAR(ecy_hsm_Csai_KeyHandleT, AUTOMATIC) hKey,
        VAR(Crypto_82_Hsm_Service_SymCipherModeType, AUTOMATIC) symCipherMode,
        VAR(Crypto_82_Hsm_Service_PaddingModeType, AUTOMATIC) paddingMode,
        P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) iv,
        VAR(uint32, AUTOMATIC) iv_len
);

/**
 * \brief Executes UPDATE operation of Authenticated Encryption job.
 * 
 * \param [in]      csaiSession       Pointer to structure which contains CSAI session handle, job priority and job handle.
 * \param [in]      aad               Pointer to data for authentication.
 * \param [in]      aadLength         Length of the data for authentication.
 * 
 * \retval errorCode                  Return value of the CSAI call that has been performed.
 */
FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Auth_Encrypt_Update
(
        VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC) csaiSession,
        P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) aad,
        VAR(uint32, AUTOMATIC) aadLength
);

/**
 * \brief Executes FINISH operation of Authenticated Encryption job.
 * 
 * \param [in]      csaiSession       Pointer to structure which contains CSAI session handle, job priority and job handle.
 * \param [out]     cipher            Pointer to where to store the encrypted message.
 * \param [in, out] cipher_len        Pointer to the length of the cipher and buffer where the function stores the amount of bytes that have been written to the cipher buffer.
 * \param [out]     pTag              Pointer to buffer to receive the authentication tag data.
 * \param [in]      tagLength         Length of buffer for authentication tag data (should be at least 16 bytes).
 * 
 * \retval errorCode                  Return value of the CSAI call that has been performed.
 */
FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Auth_Encrypt_Finish
(
        VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC) csaiSession,
        P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) cipher, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
        P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) cipher_len, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
        P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) pTag, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
        VAR(uint32, AUTOMATIC) tagLength
);

#define CRYPTO_82_HSM_STOP_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"

#endif /* CRYPTO_82_HSM_SERVICES_H */
