/**
 * @file
 ***********************************************************************************************
 * @brief CSAI Signature verification and generation.
 * This header file is part of the Cryptographic Service Application Interface and specifies
 * types and functions for generating and verifying digital signatures.
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2014, all rights reserved
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_CSAI_SIGN
#define ECY_HSM_CSAI_SIGN

/**
 * @addtogroup GROUP_CSAI_SIGNATURE
 * @{
 */

/* *** includes *******************************************************************************/
#include "ecy_hsm_csai.h"

/* *** defines ********************************************************************************/
#define ecy_hsm_CSAI_EDDSA_ED25519_SIGNATURE_SIZE_BYTE      (2U * ecy_hsm_CSAI_EDDSA_ED25519_KEY_SIZE_BYTE)             /**< EdDSA signature length */
#define ecy_hsm_CSAI_EDDSA_ED448_SIGNATURE_SIZE_BYTE        (2U * ecy_hsm_CSAI_EDDSA_ED448_KEY_SIZE_BYTE)               /**< EdDSA ED448 signature length */
#define ecy_hsm_CSAI_ECDSA_SECP224_SIGNATURE_SIZE_BYTE      (2U * ecy_hsm_CSAI_ECDSA_SECP224_PRIV_KEY_SIZE_BYTE)        /**< secp 224 signature size in bytes */
#define ecy_hsm_CSAI_ECDSA_SECP256_SIGNATURE_SIZE_BYTE      (2U * ecy_hsm_CSAI_ECDSA_SECP256_PRIV_KEY_SIZE_BYTE)        /**< secp 256 signature size in bytes */
#define ecy_hsm_CSAI_ECDSA_SECP384_SIGNATURE_SIZE_BYTE      (2U * ecy_hsm_CSAI_ECDSA_SECP384_PRIV_KEY_SIZE_BYTE)        /**< secp 384 signature size in bytes */
#define ecy_hsm_CSAI_ECDSA_SECP521_SIGNATURE_SIZE_BYTE      (2U * ecy_hsm_CSAI_ECDSA_SECP521_PRIV_KEY_SIZE_BYTE)        /**< secp 521 signature size in bytes */
#define ecy_hsm_CSAI_ECDSA_SM2_DSA_SM3_SIGNATURE_SIZE_BYTE  (2U * ecy_hsm_CSAI_ECDSA_SM2_DSA_SM3_PRIV_KEY_SIZE_BYTE)    /**< SM2 DSA SM3 signature length */
#define ecy_hsm_RSA_SSA_PSS_DEFAULT_SALT_LENGTH          (0xFFFFFFFFUL)                                                 /**< Value indicating the usage of RSASSA-PSS default salt length,
                                                                                                                             which is the hash digest length (32 bytes and 48 bytes for
                                                                                                                             SHA2-256 and SHA2-384 respectively). */

/* *********** Deprecated Macro definitions ***************/
/**
 * @deprecated by ecy_hsm_CSAI_EDDSA_ED25519_SIGNATURE_SIZE_BYTE
 */
#define EDDSA_ED25519_SIGNATURE_SIZE_BYTE ecy_hsm_CSAI_EDDSA_ED25519_SIGNATURE_SIZE_BYTE
/**
 * @deprecated by ecy_hsm_CSAI_ECDSA_SECP224_SIGNATURE_SIZE_BYTE
 */
#define ECDSA_SECP224_SIGNATURE_SIZE_BYTE ecy_hsm_CSAI_ECDSA_SECP224_SIGNATURE_SIZE_BYTE
/**
 * @deprecated by ecy_hsm_CSAI_ECDSA_SECP256_SIGNATURE_SIZE_BYTE
 */
#define ECDSA_SECP256_SIGNATURE_SIZE_BYTE ecy_hsm_CSAI_ECDSA_SECP256_SIGNATURE_SIZE_BYTE
/**
 * @deprecated by ecy_hsm_CSAI_ECDSA_SECP384_SIGNATURE_SIZE_BYTE
 */
#define ECDSA_SECP384_SIGNATURE_SIZE_BYTE ecy_hsm_CSAI_ECDSA_SECP384_SIGNATURE_SIZE_BYTE

/* *** type declarations **********************************************************************/
/** Declare digital signature schemes supported by the HSM
 * @internal
 * @note When enum list is modified, please consider updating the @ref getParams_TABS function from the Trusted Boot module
 *       and the corresponding enumeration values of @ref SW_PART_TABS_SIGN_MODE in the cfg_intdata.yml file as well.
 * @endinternal
 */
typedef enum ecy_hsm_Csai_SignatureSchemeTag
{
    ecy_hsm_CSAI_SIG_NONE = 0,                                 /**< NULL definition to allow defined parameter when
                                                                    signature scheme is ignored. */
    /* PRQA S 0785 1 */                                        /* Deviation: rule_5.5_0785_backwards_compatibility */
    ecy_hsm_CSAI_RSA_SSA_PKCS1_1V5_SHA256 = 1,                 /**< RSA signature scheme with appendix
                                                                    as specified by RFC 3447 as RSASSA-PKCS1-v1_5,
                                                                    using SHA-2 256 bit as hashing function.*/
    /* PRQA S 0785 1 */                                        /* Deviation: rule_5.5_0785_backwards_compatibility */
    ecy_hsm_CSAI_RSA_SSA_PSS_SHA256 = 2,                       /**< RSA improved probabilistic signature scheme
                                                                    as specified by RFC 3447 as RSASSA-PSS,
                                                                    using SHA-2 256 bit as hashing function. */
    ecy_hsm_CSAI_ED25519_SHA_512_PURE    = 3,                  /**< Pure EDDSA based on 25519 curve ID and 512 Digest Type*/
    ecy_hsm_CSAI_ED25519_SHA_512_DOM2_PH = 4,                  /**< Prehashed EDDSA based on Curve 25519 and SHA-512 as specified by
                                                                    draft-irtf-cfrg-eddsa-05. */
    ecy_hsm_CSAI_SECP224_SHA_224 = 5,                          /**< ECDSA signature scheme with curve secp224r1
                                                                    as specified by FIPS-186-4
                                                                    using SHA-2 224 bit as hashing function. */
    ecy_hsm_CSAI_SECP256_SHA_256 = 6,                          /**< ECDSA signature scheme with curve secp256r1
                                                                    as specified by FIPS-186-4
                                                                    using SHA-2 256 bit as hashing function. */
    ecy_hsm_CSAI_SECP384_SHA_384 = 7,                          /**< ECDSA signature scheme with curve secp384r1
                                                                    as specified by FIPS-186-4
                                                                    using SHA-2 384 bit as hashing function. */
    /* PRQA S 0785 1 */                                        /* Deviation: rule_5.5_0785_backwards_compatibility */
    ecy_hsm_CSAI_RSA_SSA_PSS_SHA256_USERHASHED = 8,            /**< RSA improved probabilistic signature scheme
                                                                    as specified by RFC 3447 as RSASSA-PSS.
                                                                    The passed message is interpreted as a SHA256 hash of some payload
                                                                    rather then the payload itself. So no further hashing is done.
                                                                    NOTE: only supported for the fastcall interface.
                                                                    NOTE: the only accepted data length is 32 bytes (256 bit) */
    /* PRQA S 0785 1 */                                        /* Deviation: rule_5.5_0785_backwards_compatibility */
    ecy_hsm_CSAI_RSA_SSA_PKCS1_1V5_SHA256_USERHASHED = 9,      /**< RSA signature scheme with appendix
                                                                    as specified by RFC 3447 as RSASSA-PKCS1-v1_5,
                                                                    The passed message is interpreted as a SHA256 hash of some payload
                                                                    rather then the payload itself. So no further hashing is done.
                                                                    NOTE: only supported for the fastcall interface.
                                                                    NOTE: the only accepted data length is 32 bytes (256 bit) */
    ecy_hsm_CSAI_SECP224_SHA_224_USERHASHED = 10,              /**< ECDSA signature scheme with curve secp224r1
                                                                    as specified by FIPS-186-4
                                                                    using SHA-2 224 bit as hashing function.
                                                                    The passed message is interpreted as a SHA-2 224 hash of some payload
                                                                    rather then the payload itself. So no further hashing is done.
                                                                    NOTE: only supported for the fastcall interface.
                                                                    NOTE: the only accepted data length is 28 bytes (224 bit) */
    ecy_hsm_CSAI_SECP256_SHA_256_USERHASHED = 11,              /**< ECDSA signature scheme with curve secp256r1
                                                                    as specified by FIPS-186-4
                                                                    using SHA-2 256 bit as hashing function.
                                                                    The passed message is interpreted as a SHA-2 256 hash of some payload
                                                                    rather then the payload itself. So no further hashing is done.
                                                                    NOTE: only supported for the fastcall interface.
                                                                    NOTE: the only accepted data length is 32 bytes (256 bit) */
    ecy_hsm_CSAI_SECP384_SHA_384_USERHASHED = 12,              /**< ECDSA signature scheme with curve secp384r1
                                                                    as specified by FIPS-186-4
                                                                    using SHA-2 384 bit as hashing function.
                                                                    The passed message is interpreted as a SHA-2 384 hash of some payload
                                                                    rather then the payload itself. So no further hashing is done.
                                                                    NOTE: only supported for the fastcall interface.
                                                                    NOTE: the only accepted data length is 48 bytes (384 bit) */
    ecy_hsm_CSAI_SECP256_SHA_512 = 13,                         /**< ECDSA signature scheme with curve secp256r1
                                                                    as specified by FIPS-186-4
                                                                    using SHA-2 512 bit as hashing function. */
    ecy_hsm_CSAI_SECP256_SHA_512_USERHASHED = 14,              /**< ECDSA signature scheme with curve secp256r1
                                                                    as specified by FIPS-186-4
                                                                    using SHA-2 512 bit as hashing function.
                                                                    The passed message is interpreted as a SHA-2 512 hash of some payload
                                                                    rather then the payload itself. So no further hashing is done.
                                                                    NOTE: only supported for the fastcall interface.
                                                                    NOTE: the only accepted data length is 64 bytes (512 bit) */
    ecy_hsm_CSAI_SECP384_SHA_512 = 15,                         /**< ECDSA signature scheme with curve secp384r1
                                                                    as specified by FIPS-186-4
                                                                    using SHA-2 512 bit as hashing function. */
    ecy_hsm_CSAI_SECP384_SHA_512_USERHASHED = 16,              /**< ECDSA signature scheme with curve secp384r1
                                                                    as specified by FIPS-186-4
                                                                    using SHA-2 512 bit as hashing function.
                                                                    The passed message is interpreted as a SHA-2 512 hash of some payload
                                                                    rather then the payload itself. So no further hashing is done.
                                                                    NOTE: only supported for the fastcall interface.
                                                                    NOTE: the only accepted data length is 64 bytes (512 bit) */
    ecy_hsm_CSAI_ED25519_SHA_512_DOM2_PH_USERHASHED = 17,      /**< Prehashed EDDSA based on Curve 25519 and SHA-512 as specified by
                                                                    draft-irtf-cfrg-eddsa-05.
                                                                    The passed message is interpreted as a SHA-2 512 hash of some payload
                                                                    rather then the payload itself. So no further hashing is done.
                                                                    NOTE: only supported for the fastcall interface.
                                                                    NOTE: the only accepted data length is 64 bytes (512 bit)*/
    ecy_hsm_CSAI_SECP384_SHA_256 = 18,                         /**< ECDSA signature scheme with curve secp384r1
                                                                    as specified by FIPS-186-4
                                                                    using SHA-2 256 bit as hashing function.
                                                                    NOTE: the overall security level is reduced to the security
                                                                    level of the hash function */
    ecy_hsm_CSAI_SECP384_SHA_256_USERHASHED = 19,              /**< ECDSA signature scheme with curve secp384r1
                                                                    as specified by FIPS-186-4
                                                                    using SHA-2 256 bit as hashing function.
                                                                    The passed message is interpreted as a SHA-2 256 hash of some payload
                                                                    rather then the payload itself. So no further hashing is done.
                                                                    NOTE: only supported for the fastcall interface.
                                                                    NOTE: the only accepted data length is 32 bytes (256 bit)
                                                                    NOTE: the overall security level is reduced to the security
                                                                    level of the hash function */
    ecy_hsm_CSAI_SM2_DSA_SM3 = 20,                             /**< SM2 signature scheme according to the GM/T 0003.2-2012 standard
                                                                    using SM3 as hashing function.
                                                                    NOTE: uses the internal PRNG
                                                                    NOTE: the hashed user information according to the standard (ZA)
                                                                         needs to precede the actual message*/
    ecy_hsm_CSAI_SM2_DSA_SM3_USERHASHED = 21,                  /**< SM2 signature scheme according to the GM/T 0003.2-2012 standard
                                                                    using SM3 as hashing function.
                                                                    The passed message is interpreted as a SM3 hash of the payload
                                                                    rather then the payload itself. So no further hashing is done.
                                                                    NOTE: only supported for the fastcall interface.
                                                                    NOTE: the only accepted data length is 32 bytes (256 bit)
                                                                    NOTE: uses the internal PRNG */
    ecy_hsm_CSAI_RSA_SSA_PSS_SHA384 = 22,                      /**< RSA improved probabilistic signature scheme
                                                                    as specified by RFC 3447 as RSASSA-PSS,
                                                                    using SHA-2 384 bit as hashing function. */
    ecy_hsm_CSAI_RSA_SSA_PSS_SHA384_USERHASHED = 23,           /**< RSA improved probabilistic signature scheme
                                                                    as specified by RFC 3447 as RSASSA-PSS.
                                                                    The passed message is interpreted as a SHA384 hash of some payload
                                                                    rather then the payload itself. So no further hashing is done.
                                                                    NOTE: only supported for the fastcall interface.
                                                                    NOTE: the only accepted data length is 48 bytes (384 bit) */
    ecy_hsm_CSAI_ED25519_SHA_512_PH_WITHOUT_DOM2_NON_STD = 24, /**< NON-STANDARD algorithm based on Ed25519 or Ed25519ph (depends on the view) and
                                                                    SHA-512!
                                                                    - The deviation from the RFC8032 Ed25519 is that a SHA256 hash of the message
                                                                    to be signed is being used as input to the signing/verification function. This
                                                                    means that instead of calculating as described by RFC8032 for Step 2 in Section
                                                                    "5.1.6. Sign" SHA-512(prefix || M) for Ed25519, SHA-512(prefix || SHA512(M)) gets
                                                                    calculated instead. SHA512(M) will by calculated by this algorithm and the caller
                                                                    must pass the message M.
                                                                    - On the another hand, the deviation from from the RFC8032 Ed25519ph is
                                                                    that dom2 is a blank octet string. Supported by the streaming and fastcall
                                                                    interfaces  */
    ecy_hsm_CSAI_SECP521_SHA_512 = 25,                         /**< ECDSA signature scheme with curve secp521r1
                                                                    as specified by FIPS-186-4
                                                                    using SHA-2 512 bit as hashing function. */
    ecy_hsm_CSAI_SECP521_SHA_512_USERHASHED = 26,              /**< ECDSA signature scheme with curve secp521r1
                                                                    as specified by FIPS-186-4
                                                                    using SHA-2 512 bit as hashing function.
                                                                    The passed message is interpreted as a SHA-2 512 hash of some payload
                                                                    rather than the payload itself. So no further hashing is done.
                                                                    NOTE: only supported for the fastcall interface.
                                                                    NOTE: the only accepted data length is 66 bytes (521 bit) */
    ecy_hsm_CSAI_ED448_SHAKE_256_PURE       =  27,             /**< Pure EDDSA based on 448 curve ID and SHAKE 256 as Digest Type as specified by
                                                                    RFC 8032. */
    ecy_hsm_CSAI_ED448_SHAKE_256_DOM2_PH    =  28,             /**< Prehashed EDDSA based on Curve 448 and SHAKE 256 as specified by
                                                                    RFC 8032. */
    ecy_hsm_CSAI_ED448_SHAKE_256_DOM2_PH_USERHASHED   =  29,   /**< Prehashed EDDSA based on Curve 448 and SHAKE 256 as specified by
                                                                    RFC 8032. The passed message is interpreted as a SHA-2 512 hash of some payload. */
    ecy_hsm_CSAI_SIGNSCHEME_RESERVED = 0x7fffffffu             /**< Value defined to use memory size of uint32 for enums. */

} ecy_hsm_Csai_SignatureSchemeT;

/* @deprecated
 * these definitions are for backwards compatibility, because of the renaming from PREHASHED to USERHASHED */
/** Backwards compatibility macro. @deprecated by @ref ecy_hsm_CSAI_RSA_SSA_PSS_SHA256_USERHASHED */
# define ecy_hsm_CSAI_RSA_SSA_PSS_SHA256_PREHASHED       ecy_hsm_CSAI_RSA_SSA_PSS_SHA256_USERHASHED
/** Backwards compatibility macro. @deprecated by @ref ecy_hsm_CSAI_RSA_SSA_PKCS1_1V5_SHA256_USERHASHED */
# define ecy_hsm_CSAI_RSA_SSA_PKCS1_1V5_SHA256_PREHASHED ecy_hsm_CSAI_RSA_SSA_PKCS1_1V5_SHA256_USERHASHED
/** Backwards compatibility macro. @deprecated by @ref ecy_hsm_CSAI_SECP224_SHA_224_USERHASHED */
# define ecy_hsm_CSAI_SECP224_SHA_224_PREHASHED          ecy_hsm_CSAI_SECP224_SHA_224_USERHASHED
/** Backwards compatibility macro. @deprecated by @ref ecy_hsm_CSAI_SECP256_SHA_256_USERHASHED */
# define ecy_hsm_CSAI_SECP256_SHA_256_PREHASHED          ecy_hsm_CSAI_SECP256_SHA_256_USERHASHED
/** Backwards compatibility macro. @deprecated by @ref ecy_hsm_CSAI_SECP384_SHA_384_USERHASHED */
# define ecy_hsm_CSAI_SECP384_SHA_384_PREHASHED          ecy_hsm_CSAI_SECP384_SHA_384_USERHASHED
/** Backwards compatibility macro. @deprecated by @ref ecy_hsm_CSAI_SECP256_SHA_512_USERHASHED */
# define ecy_hsm_CSAI_SECP256_SHA_512_PREHASHED          ecy_hsm_CSAI_SECP256_SHA_512_USERHASHED
/** Backwards compatibility macro. @deprecated by @ref ecy_hsm_CSAI_SECP384_SHA_512_USERHASHED */
# define ecy_hsm_CSAI_SECP384_SHA_512_PREHASHED          ecy_hsm_CSAI_SECP384_SHA_512_USERHASHED
/** Backwards compatibility macro. @deprecated by @ref ecy_hsm_CSAI_SECP384_SHA_256_USERHASHED */
# define ecy_hsm_CSAI_SECP384_SHA_256_PREHASHED          ecy_hsm_CSAI_SECP384_SHA_256_USERHASHED

/**
 * Enum for versioning the parameter set for Signature CSAIs with extendable interface.
 * New IDs for future structure shall be added here.
 */
typedef enum ecy_hsm_Csai_Sign_ParamSetVersionTag
{
    ecy_hsm_CSAI_SIGN_PARAMSET_V0,                            /**< Corresponds to Version 0 of the extendable data struct   */
    ecy_hsm_CSAI_SIGN_PARAMSET_MAX = 0x7FFFFFFFUL             /**< Value defined to use memory size of uint32 for enums     */
} ecy_hsm_Csai_Sign_ParamSetVersionT;

/**
 * Structures of extendable parameters for Signature Generation using extendable CSAI
 */
/** Structure for extendable parameter set - version 0 */
typedef struct ecy_hsm_Csai_SignGen_ParamSet_V0Tag
{
    uint32 saltLength;                                          /**< Salt length for RSA SSA PSS algorithms (ecy_hsm_CSAI_RSA_SSA_PSS_SHA256
                                                                     and ecy_hsm_CSAI_RSA_SSA_PSS_SHA384). Valid range is from 0 to
                                                                     (RSA keyLen - digestLen - 2). The default value ecy_hsm_RSA_SSA_PSS_DEFAULT_SALT_LENGTH
                                                                     can be selected to use the hash digest length as the salt length */
} ecy_hsm_Csai_SignGen_ParamSet_V0T;

/**
 * Structures for streaming Signature Generation - Start using extendable CSAI
 */
/** Union of extendable data structures. New structures for future parameters shall be added here. */
/* PRQA S 0750 2 */ /* <Deviation: definition of union is appropriate here */
typedef union ecy_hsm_Csai_SignGenStart_ParamSetTag
{
    ecy_hsm_Csai_SignGen_ParamSet_V0T paramV0;                  /**< Data structure of Version 0 */
} ecy_hsm_Csai_SignGenStart_ParamSetT;

/**
 * Structures for streaming Signature Generation - Update using extendable CSAI
 */
/** Placeholder definition for expansion in the future */
typedef uint32 ecy_hsm_Csai_SignGenUpdate_ParamSetT;

/**
 * Structures for streaming Signature Generation - Finish using extendable CSAI
 */
/** Placeholder definition for expansion in the future */
typedef uint32 ecy_hsm_Csai_SignGenFinish_ParamSetT;

/**
 * Structures for Fast call Signature Generation using extendable CSAI
 */
/** Union of extendable data structures. New structures for future parameters shall be added here. */
/* PRQA S 0750 2 */ /* <Deviation: definition of union is appropriate here */
typedef union ecy_hsm_Csai_SignGenFastCall_ParamSetTag
{
    ecy_hsm_Csai_SignGen_ParamSet_V0T paramV0;                  /**< Data structure of Version 0 */
} ecy_hsm_Csai_SignGenFastCall_ParamSetT;

/**
 * Union of parameter sets for signature generation extendable CSAIs
 */
/* PRQA S 0750 1 */ /* <Deviation: definition of union is appropriate here */
typedef union ecy_hsm_Csai_SignGenExtended_ParamSetUnionTag {
    ecy_hsm_Csai_SignGenStart_ParamSetT*        pSignStartParamSet;     /**< Pointer to the extendable parameter set for Start CSAI */
    ecy_hsm_Csai_SignGenUpdate_ParamSetT*       pSignUpdateParamSet;    /**< Pointer to the extendable parameter set for Update CSAI */
    ecy_hsm_Csai_SignGenFinish_ParamSetT*       pSignFinishParamSet;    /**< Pointer to the extendable parameter set for Finish CSAI */
    ecy_hsm_Csai_SignGenFastCall_ParamSetT*     pSignFastCallParamSet;  /**< Pointer to the extendable parameter set for Fast Call CSAI */
} ecy_hsm_Csai_SignGenExtended_ParamSetUnionT;

/**
 * Structure of parameter set union and its version for signature generation extendable CSAIs
 */
typedef struct ecy_hsm_Csai_SignGenExtended_ParamSetAndVersionTag {
    ecy_hsm_Csai_Sign_ParamSetVersionT                 signParamSetVersion;  /**< Version of the selected structure within @c signParamSet union */
    ecy_hsm_Csai_SignGenExtended_ParamSetUnionT        signParamSet;         /**< Union of the extendable parameter set */
} ecy_hsm_Csai_SignGenExtended_ParamSetAndVersionT;

/**
 * Structures of extendable parameters for Signature Verification using extendable CSAI
 */
/** Structure for extendable parameter set - version 0 */
typedef struct ecy_hsm_Csai_SignVer_ParamSet_V0Tag
{
    uint32 saltLength;                                          /**< Salt length for RSA SSA PSS algorithms (ecy_hsm_CSAI_RSA_SSA_PSS_SHA256
                                                                     and ecy_hsm_CSAI_RSA_SSA_PSS_SHA384). Valid range is from 0 to
                                                                     (RSA keyLen - digestLen - 2). The default value ecy_hsm_RSA_SSA_PSS_DEFAULT_SALT_LENGTH
                                                                     can be selected to use the hash digest length as the salt length */
} ecy_hsm_Csai_SignVer_ParamSet_V0T;

/**
 * Structures for streaming Signature Verification - Start using extendable CSAI
 */
/** Union of extendable data structures. New structures for future parameters shall be added here. */
/* PRQA S 0750 2 */ /* <Deviation: definition of union is appropriate here */
typedef union ecy_hsm_Csai_SignVerStart_ParamSetTag
{
    ecy_hsm_Csai_SignVer_ParamSet_V0T paramV0;                  /**< Data structure of Version 0 */
} ecy_hsm_Csai_SignVerStart_ParamSetT;

/**
 * Structures for streaming Signature Verification - Update using extendable CSAI
 */
/** Placeholder definition for expansion in the future */
typedef uint32 ecy_hsm_Csai_SignVerUpdate_ParamSetT;

/**
 * Structures for streaming Signature Verification - Finish using extendable CSAI
 */
/** Placeholder definition for expansion in the future */
typedef uint32 ecy_hsm_Csai_SignVerFinish_ParamSetT;

/**
 * Structures for Fast call Signature Verification using extendable CSAI
 */
/** Union of extendable data structures. New structures for future parameters shall be added here. */
/* PRQA S 0750 2 */ /* <Deviation: definition of union is appropriate here */
typedef union ecy_hsm_Csai_SignVerFastCall_ParamSetTag
{
    ecy_hsm_Csai_SignVer_ParamSet_V0T paramV0;                  /**< Data structure of Version 0 */
} ecy_hsm_Csai_SignVerFastCall_ParamSetT;

/**
 * Union of parameter sets for signature verification extendable CSAIs
 */
/* PRQA S 0750 1 */ /* <Deviation: definition of union is appropriate here */
typedef union ecy_hsm_Csai_SignVerExtended_ParamSetUnionTag {
    ecy_hsm_Csai_SignVerStart_ParamSetT*        pSignStartParamSet;     /**< Pointer to the extendable parameter set for Start CSAI */
    ecy_hsm_Csai_SignVerUpdate_ParamSetT*       pSignUpdateParamSet;    /**< Pointer to the extendable parameter set for Update CSAI */
    ecy_hsm_Csai_SignVerFinish_ParamSetT*       pSignFinishParamSet;    /**< Pointer to the extendable parameter set for Finish CSAI */
    ecy_hsm_Csai_SignVerFastCall_ParamSetT*     pSignFastCallParamSet;  /**< Pointer to the extendable parameter set for Fast Call CSAI */
} ecy_hsm_Csai_SignVerExtended_ParamSetUnionT;

/**
 * Structure of parameter set union and its version for signature verification extendable CSAIs
 */
typedef struct ecy_hsm_Csai_SignVerExtended_ParamSetAndVersionTag {
    ecy_hsm_Csai_Sign_ParamSetVersionT                 signParamSetVersion;  /**< Version of the selected structure within @c signParamSet union */
    ecy_hsm_Csai_SignVerExtended_ParamSetUnionT        signParamSet;         /**< Union of the extendable parameter set */
} ecy_hsm_Csai_SignVerExtended_ParamSetAndVersionT;

/* *** global constants ***********************************************************************/

/* *** exported interfaces ********************************************************************/

/* *INDENT-OFF* */
#ifdef __cplusplus
extern "C" {
#endif
/* *INDENT-ON* */

/**
 * @addtogroup GROUP_CSAI_SIGN_GENERATE_START
 * @{
 */

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/**
 * [$DD 2369]
 * [$Satisfies $ARCH 556][$Satisfies $ARCH 263]
 * Initialize and start a multi part or single shot signature generation operation. The caller
 * must specify in which session context the job is to be executed, a digital signature scheme to
 * use, a handle to a key available to the session and a scheduling priority for the job on the HSM.
 * This function does not block but immediately returns when the job is queued on the HSM.
 * @note
 * - Multi-part mode:
 *      The caller may update the digital signature operation with further message chunks using
 *      @ref ecy_hsm_Csai_SignGenerateUpdate.
 * - Finalization and result query:
 *      The caller finalizes and polls for the result of the digital signature scheme using
 *      @ref ecy_hsm_Csai_SignGenerateFinish.
 *
 *
 * @param[in]   hSession     Handle to the session in which the job is placed.
 * @param[in]   scheme       Specification of the SHA variant to use.
 * @param[in]   hKey         Key handle for the job, OR a keyId
 * @param[in]   priority     Requested scheduling priority for this job on the HSM.
 * @note
 * Signature operations will always be executed on low priority.
 * Parameter will be overridden by implementation.
 * @param[in]   msg          First chunk or entire message to sign.
 * @param[in]   msgLength    Length of the provided message or chunk.
 * @param[in]   phJob        Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                The given digital signature scheme is not supported by this
 *                                                      HSM build.
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED          The Job is in the wrong state to perform this operation
 * - @ref ecy_hsm_CSAI_ERR_KEY_NOT_LOADED               The required key has not been loaded into the session
 * - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE               The given key type needs to be an asymmetric private key
 * - @ref ecy_hsm_CSAI_ERR_CYCURLIB                     CycurLib returned an error.
 * - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION            There has been an attempt to access HSM ram address via the CSAI
 *                                                      interface
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_SignGenerateStart(ecy_hsm_Csai_SessionHandleT   hSession,
                                                 ecy_hsm_Csai_SignatureSchemeT scheme,
                                                 ecy_hsm_Csai_KeyHandleT       hKey,
                                                 ecy_hsm_Csai_JobPriorityT     priority,
                                                 const uint8                   msg[],
                                                 uint32                        msgLength,
                                                 ecy_hsm_Csai_JobHandleT*      phJob);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_SIGN_GENERATE_UPDATE
 * @{
 */

/**
 * [$DD 2370]
 * [$Satisfies $ARCH 556][$Satisfies $ARCH 263]
 * Update a running digital signature job with another message chunk.
 *
 * @note This function may return @ref ecy_hsm_CSAI_SUCCESS or @ref ecy_hsm_CSAI_FC_BUSY, an
 * expected flow control value. In the latter case, the HSM is still busy in signing
 * the previous chunk and cannot queue more data at the moment. Try again later.
 *
 *
 * @param[in]   hJob            Handle to the initialized job
 * @param[in]   chunk           Next chunk or entire message to sign.
 * @param[in]   length          Length of the provided chunk of message.
 *
 * Multi-part mode:
 * The caller may repeatedly call this function to provide additional message chunks.
 *
 * Finalization and result query:
 * The caller finalizes and polls for the result of the digital signature scheme using
 * @ref ecy_hsm_Csai_SignGenerateFinish.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                The given digital signature scheme is not supported by this HSM build
 * - @ref ecy_hsm_CSAI_ERR_JOB_NOT_STARTED              The Job is in the wrong state to perform this operation
 * - @ref ecy_hsm_CSAI_ERR_CYCURLIB                     CycurLib returned an error.
 * - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION            There has been an attempt to access HSM ram address via the CSAI
 *                                                      interface
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_SignGenerateUpdate(ecy_hsm_Csai_JobHandleT hJob,
                                                  const uint8             chunk[],
                                                  uint32                  length);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_SIGN_GENERATE_FINISH
 * @{
 */

/**
 * [$DD 2371]
 * [$Satisfies $ARCH 556][$Satisfies $ARCH 263]
 * Finalize a digital signature generation scheme and query its result.
 *
 * @note This function may return @ref ecy_hsm_CSAI_SUCCESS or @ref ecy_hsm_CSAI_FC_BUSY, an
 * expected flow control value. In the latter case, the HSM is still busy signing
 * and cannot provide the result yet. Try again later.
 *
 *
 * @param[in]   hJob                Handle to the initialized job
 * @param[out]  pSign               Pointer to space where the HSM can store the result.
 * @param[in]   signLength          Length of the provided @c pSign buffer.
 * @param[out]  pSignCount          Pointer to space, where the function can store how
 *                                  many bytes have been written to the sign buffer
 *                                  provided here.
 *                                  The caller may provide @c NULL_PTR in which case no
 *                                  count is provided.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                The given digital signature scheme is not supported by this HSM build
 * - @ref ecy_hsm_CSAI_ERR_JOB_NOT_STARTED              The Job is in the wrong state to perform this operation
 * - @ref ecy_hsm_CSAI_ERR_CYCURLIB                     CycurLib returned an error.
 * - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION            There has been an attempt to access HSM ram address via the
 *                                                      CSAI interface
 *
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_SignGenerateFinish(ecy_hsm_Csai_JobHandleT hJob,
                                                  uint8*                  pSign,
                                                  uint32                  signLength,
                                                  uint32*                 pSignCount);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_SIGN_GENERATE_EXTENDED_START
 * @{
 */

/**
 * [$DD 2372]
 * [$Satisfies $ARCH 556][$Satisfies $ARCH 263]
 * Initialize and start a multi part or single shot signature generation operation, using extendable
 * set of parameters. The caller must specify in which session context the job is to be executed, a
 * digital signature scheme to use, a pointer to the extendable parameter set and a scheduling
 * priority for the job on the HSM. This function does not block but immediately returns when the job
 * is queued on the HSM.
 *
 * The function uses a pointer to @c ecy_hsm_Csai_SignGenExtended_ParamSetAndVersionT structure which contains
 * additional parameters related to Signature generation (Start stage). These can be extended in the future
 * by incrementing the signParamSetVersion and adding new structures to the @c ecy_hsm_Csai_SignGenStart_ParamSetT union.
 *
 * @note
 * - Multi-part mode:
 *      The caller may update the digital signature operation with further message chunks using
 *      @ref ecy_hsm_Csai_SignGenerateExtendedUpdate.
 * - Finalization and result query:
 *      The caller finalizes and polls for the result of the digital signature scheme using
 *      @ref ecy_hsm_Csai_SignGenerateExtendedFinish.
 *
 *
 * @param[in]   hSession                        Handle to the session in which the job is placed.
 * @param[in]   priority                        Requested scheduling priority for this job on the HSM.
 * @note
 * Signature operations will always be executed on low priority.
 * Parameter will be overridden by implementation.
 * @param[in]   scheme                          Specification of the SHA variant to use.
 * @param[in]   pSignStartParamSetAndVersion    Pointer to the extendable parameter set and their corresponding version.
 *                                              The caller may provide @c NULL in which case no additional
 *                                              parameter is provided. Otherwise pSignStartParamSet must not be @c NULL.
 * @param[in]   hKey                            Key handle for the job, OR a keyId
 * @param[in]   pMsg                            First chunk or entire message to sign.
 * @param[in]   msgLength                       Length of the provided message or chunk.
 * @param[out]  phJob                           Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                The given digital signature scheme is not supported by this
 *                                                      HSM build.
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED          The Job is in the wrong state to perform this operation
 * - @ref ecy_hsm_CSAI_ERR_KEY_NOT_LOADED               The required key has not been loaded into the session
 * - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE               The given key type needs to be an asymmetric private key
 * - @ref ecy_hsm_CSAI_ERR_CYCURLIB                     CycurLib returned an error.
 * - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION            There has been an attempt to access HSM ram address via the CSAI
 *                                                      interface
 */
/* PRQA S 0777 2 */ /* Deviation: rule_5.1_0777 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_SignGenerateExtendedStart(ecy_hsm_Csai_SessionHandleT                       hSession,
                                                         ecy_hsm_Csai_JobPriorityT                         priority,
                                                         ecy_hsm_Csai_SignatureSchemeT                     scheme,
                                                         ecy_hsm_Csai_SignGenExtended_ParamSetAndVersionT* pSignStartParamSetAndVersion,
                                                         ecy_hsm_Csai_KeyHandleT                           hKey,
                                                         const uint8*                                      pMsg,
                                                         uint32                                            msgLength,
                                                         ecy_hsm_Csai_JobHandleT*                          phJob);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_SIGN_GENERATE_EXTENDED_UPDATE
 * @{
 */

/**
 * [$DD 2373]
 * [$Satisfies $ARCH 556][$Satisfies $ARCH 263]
 * Update a running digital signature job with another message chunk, using extendable set of parameters.
 *
 * The function uses a pointer to @c ecy_hsm_Csai_SignGenExtended_ParamSetAndVersionT structure which contains
 * additional parameters related to Signature generation (Update stage). These can be extended in the future
 * by incrementing the signParamSetVersion and adding new structures to the @c ecy_hsm_Csai_SignGenUpdate_ParamSetT union.
 *
 * @note This function may return @ref ecy_hsm_CSAI_SUCCESS or @ref ecy_hsm_CSAI_FC_BUSY, an
 * expected flow control value. In the latter case, the HSM is still busy in signing
 * the previous chunk and cannot queue more data at the moment. Try again later.
 *
 *
 * @param[in]   hJob                           Handle to the initialized job
 * @param[in]   pSignUpdateParamSetAndVersion  Pointer to the extendable parameter set and their corresponding version.
 *                                             The caller may provide @c NULL in which case no additional
 *                                             parameter is provided.
 * @param[in]   pChunk                         Next chunk or entire message to sign.
 * @param[in]   length                         Length of the provided chunk of message.
 *
 * Multi-part mode:
 * The caller may repeatedly call this function to provide additional message chunks.
 *
 * Finalization and result query:
 * The caller finalizes and polls for the result of the digital signature scheme using
 * @ref ecy_hsm_Csai_SignGenerateFinish.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                The given digital signature scheme is not supported by this HSM build
 * - @ref ecy_hsm_CSAI_ERR_JOB_NOT_STARTED              The Job is in the wrong state to perform this operation
 * - @ref ecy_hsm_CSAI_ERR_CYCURLIB                     CycurLib returned an error.
 * - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION            There has been an attempt to access HSM ram address via the CSAI
 *                                                      interface
 */
/* PRQA S 0777 2 */ /* Deviation: rule_5.1_0777 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_SignGenerateExtendedUpdate(ecy_hsm_Csai_JobHandleT                           hJob,
                                                          ecy_hsm_Csai_SignGenExtended_ParamSetAndVersionT* pSignUpdateParamSetAndVersion,
                                                          const uint8*                                      pChunk,
                                                          uint32                                            length);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_SIGN_GENERATE_EXTENDED_FINISH
 * @{
 */

/**
 * [$DD 2374]
 * [$Satisfies $ARCH 556][$Satisfies $ARCH 263]
 * Finalize a digital signature generation scheme and query its result, using extendable set of parameters.
 *
 * The function uses a pointer to @c ecy_hsm_Csai_SignGenExtended_ParamSetAndVersionT structure which contains
 * additional parameters related to Signature generation (Finish stage). These can be extended in the future
 * by incrementing the signParamSetVersion and adding new structures to the @c ecy_hsm_Csai_SignGenFinish_ParamSetT union.
 *
 * @note This function may return @ref ecy_hsm_CSAI_SUCCESS or @ref ecy_hsm_CSAI_FC_BUSY, an
 * expected flow control value. In the latter case, the HSM is still busy signing
 * and cannot provide the result yet. Try again later.
 *
 *
 * @param[in]       hJob                           Handle to the initialized job
 * @param[in,out]   pSignFinishParamSetAndVersion  Pointer to the extendable parameter set and their corresponding version.
 *                                                 The caller may provide @c NULL in which case no additional
 *                                                 parameter is provided
 * @param[out]      pSign                          Pointer to space where the HSM can store the result.
 * @param[in]       signLength                     Length of the provided @c pSign buffer.
 * @param[out]      pSignCount                     Pointer to space, where the function can store how
 *                                                 many bytes have been written to the sign buffer
 *                                                 provided here.
 *                                                 The caller may provide @c NULL_PTR in which case no
 *                                                 count is provided.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                The given digital signature scheme is not supported by this HSM build
 * - @ref ecy_hsm_CSAI_ERR_JOB_NOT_STARTED              The Job is in the wrong state to perform this operation
 * - @ref ecy_hsm_CSAI_ERR_CYCURLIB                     CycurLib returned an error.
 * - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION            There has been an attempt to access HSM ram address via the
 *                                                      CSAI interface
 *
 */
/* PRQA S 0777 2 */ /* Deviation: rule_5.1_0777 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_SignGenerateExtendedFinish(ecy_hsm_Csai_JobHandleT                           hJob,
                                                          ecy_hsm_Csai_SignGenExtended_ParamSetAndVersionT* pSignFinishParamSetAndVersion,
                                                          uint8*                                            pSign,
                                                          uint32                                            signLength,
                                                          uint32*                                           pSignCount);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_SIGN_GENERATE_ONESHOT
 * @{
 */

/**
 * [$DD 2375]
 * [$Satisfies $ARCH 596][$Satisfies $ARCH 263]
 * Initialize and start a single shot signature generation operation.
 * The caller must specify in which session context the job is to be executed, a digital signature scheme to
 * use, a handle to a key available to the session and a scheduling priority for the job on the HSM,
 * data to be signed and the length of it. The caller must also provide the buffer to place the signed result,
 * length of the result buffer and buffer to store the count of the bytes written to sign buffer.
 * This function does not block but immediately returns when the job is queued on the HSM.
 *
 * @note This function does not block but immediately returns when the job is queued on the HSM.
 * The caller should subsequently
 * call @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle with the returned
 * @c ecy_hsm_Csai_JobHandleT to synchronize with the result.
 *
 * @note This function may return @ref ecy_hsm_CSAI_SUCCESS or @ref ecy_hsm_CSAI_FC_BUSY, an
 * expected flow control value. In the latter case, the HSM is still busy with previous data
 * and cannot provide the result yet. Try again later.
 *
 * @note The fast call interface allows a single block of data to be Signed.  Alternatively,
 * use the streaming interface (see @ref ecy_hsm_Csai_SignGenerateStart) if an update of the running job is required.
 *
 * @param[in]   hSession            Handle to the session in which the job is placed.
 * @param[in]   scheme              Specification of the SHA variant to use.
 * @param[in]   hKey                Key handle for the job, OR a keyId
 * @param[in]   priority            Requested scheduling priority for this job on the HSM.
 * @note
 * Signature operations will always be executed on low priority.
 * Parameter will be overridden by implementation.
 * @param[in]   msg                 First chunk or entire message to sign.
 * @param[in]   msgLength           Length of the provided message or chunk.
 * @param[out]  pSign               Pointer to space where the HSM can store the result.
 * @param[in]   signLength          Length of the provided @c pSign buffer.
 * @param[out]  pSignCount          Pointer to space, where the function can store how
 *                                  many bytes have been written to the sign buffer
 *                                  provided here.
 *                                  The caller may provide @c NULL in which case no
 *                                  count is provided.
 * @param[in]   phJob               Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                The given digital signature scheme is not supported by this
 *                                                      HSM build.
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED          The Job is in the wrong state to perform this operation
 * - @ref ecy_hsm_CSAI_ERR_KEY_NOT_LOADED               The required key has not been loaded into the session
 * - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE               The given key type needs to be an asymmetric private key
 * - @ref ecy_hsm_CSAI_ERR_CYCURLIB                     CycurLib returned an error.
 * - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION            There has been an attempt to access HSM ram address
 *                                                      via the CSAI interface
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_SignGenerate(ecy_hsm_Csai_SessionHandleT   hSession,
                                            ecy_hsm_Csai_SignatureSchemeT scheme,
                                            ecy_hsm_Csai_KeyHandleT       hKey,
                                            ecy_hsm_Csai_JobPriorityT     priority,
                                            const uint8*                  msg,
                                            uint32                        msgLength,
                                            uint8*                        pSign,
                                            uint32                        signLength,
                                            uint32*                       pSignCount,
                                            ecy_hsm_Csai_JobHandleT*      phJob);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_SIGN_GENERATE_EXTENDED_ONESHOT
 * @{
 */

/**
 * [$DD 2376]
 * [$Satisfies $ARCH 596][$Satisfies $ARCH 263]
 * Initialize and start a single shot signature generation operation, using extendable set of parameters.
 * The caller must specify in which session context the job is to be executed, a digital signature scheme to
 * use, a pointer to the extendable parameter set, a scheduling priority for the job on the HSM,
 * data to be signed and the length of it. The caller must also provide the buffer to place the signed result,
 * length of the result buffer and buffer to store the count of the bytes written to sign buffer.
 * This function does not block but immediately returns when the job is queued on the HSM.
 *
 * The function uses a pointer to @c ecy_hsm_Csai_SignGenExtended_ParamSetAndVersionT structure which contains
 * additional parameters related to Signature generation (one shot). These can be extended in the future
 * by incrementing the signParamSetVersion and adding new structures to the @c ecy_hsm_Csai_SignGenFastCall_ParamSetT union.
 *
 * @note This function does not block but immediately returns when the job is queued on the HSM.
 * The caller should subsequently
 * call @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle with the returned
 * @c ecy_hsm_Csai_JobHandleT to synchronize with the result.
 *
 * @note This function may return @ref ecy_hsm_CSAI_SUCCESS or @ref ecy_hsm_CSAI_FC_BUSY, an
 * expected flow control value. In the latter case, the HSM is still busy with previous data
 * and cannot provide the result yet. Try again later.
 *
 * @note The fast call interface allows a single block of data to be Signed. Alternatively,
 * use the streaming interface (see @ref ecy_hsm_Csai_SignGenerateExtendedStart) if an update of
 * the running job is required.
 *
 * @param[in]   hSession                   Handle to the session in which the job is placed.
 * @param[in]   priority                   Requested scheduling priority for this job on the HSM.
 * @note
 * Signature operations will always be executed on low priority.
 * Parameter will be overridden by implementation.
 * @param[in]   scheme                     Specification of the SHA variant to use.
 * @param[in]   pSignParamSetAndVersion    Pointer to the extendable parameter set and their corresponding version.
 *                                         The caller may provide @c NULL in which case no additional
 *                                         parameter is provided. Otherwise pSignFastCallParamSet must not be @c NULL.
 * @param[in]   hKey                       Key handle for the job, OR a keyId
 * @param[in]   pMsg                       First chunk or entire message to sign.
 * @param[in]   msgLength                  Length of the provided message or chunk.
 * @param[out]  pSign                      Pointer to space where the HSM can store the result.
 * @param[in]   signLength                 Length of the provided @c pSign buffer.
 * @param[out]  pSignCount                 Pointer to space, where the function can store how
 *                                         many bytes have been written to the sign buffer
 *                                         provided here.
 *                                         The caller may provide @c NULL in which case no
 *                                         count is provided.
 * @param[out]  phJob                      Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                The given digital signature scheme is not supported by this
 *                                                      HSM build.
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED          The Job is in the wrong state to perform this operation
 * - @ref ecy_hsm_CSAI_ERR_KEY_NOT_LOADED               The required key has not been loaded into the session
 * - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE               The given key type needs to be an asymmetric private key
 * - @ref ecy_hsm_CSAI_ERR_CYCURLIB                     CycurLib returned an error.
 * - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION            There has been an attempt to access HSM ram address
 *                                                      via the CSAI interface
 */
/* PRQA S 0777 2 */ /* Deviation: rule_5.1_0777 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_SignGenerateExtended(ecy_hsm_Csai_SessionHandleT                       hSession,
                                                    ecy_hsm_Csai_JobPriorityT                         priority,
                                                    ecy_hsm_Csai_SignatureSchemeT                     scheme,
                                                    ecy_hsm_Csai_SignGenExtended_ParamSetAndVersionT* pSignParamSetAndVersion,
                                                    ecy_hsm_Csai_KeyHandleT                           hKey,
                                                    const uint8*                                      pMsg,
                                                    uint32                                            msgLength,
                                                    uint8*                                            pSign,
                                                    uint32                                            signLength,
                                                    uint32*                                           pSignCount,
                                                    ecy_hsm_Csai_JobHandleT*                          phJob);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_SIGN_VERIFY_START
 * @{
 */

/**
 * [$DD 2377]
 * [$Satisfies $ARCH 542][$Satisfies $ARCH 263]
 * Initialize and start a multi part or single shot signature verify operation.
 * The caller must  specify in which session context the job is to be executed, a digital signature
 * scheme to use, a handle to a key available to the session and a scheduling priority for the
 * job on the HSM.
 * This function does not block but immediately returns when the job is queued on the HSM.
 * @note
 * - Multi-part mode:
 *      The caller may update the digital signature verify operation with further message chunks using
 *      @ref ecy_hsm_Csai_SignVerifyUpdate.
 * - Finalization and result query:
 *      The caller finalizes and polls for the result of the digital signature verify operation using
 *      @ref ecy_hsm_Csai_SignVerifyFinish.
 *
 *
 * @param[in]   hSession     Handle to the session in which the job is placed.
 * @param[in]   scheme       Specification of the SHA variant to use.
 * @param[in]   hKey         Handle to key to be used, OR a keyId
 * @param[in]   priority     Requested scheduling priority for this job on the HSM.
 * @note
 * Signature operations will always be executed on low priority.
 * Parameter will be overridden by implementation.
 * @param[in]   msg          First chunk or entire message to sign.
 * @param[in]   msgLength    Length of the provided message or chunk.
 * @param[in]   phJob        Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                The given digital signature scheme is not supported by this HSM build
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED          The Job is in the wrong state to perform this operation
 * - @ref ecy_hsm_CSAI_ERR_KEY_NOT_LOADED               The required key has not been loaded into the session
 * - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE               The given key type needs to be an asymmetric public key
 * - @ref ecy_hsm_CSAI_ERR_CYCURLIB                     CycurLib returned an error.
 * - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION            There has been an attempt to access HSM ram address via
 *                                                      the CSAI interface
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_SignVerifyStart(ecy_hsm_Csai_SessionHandleT   hSession,
                                               ecy_hsm_Csai_SignatureSchemeT scheme,
                                               ecy_hsm_Csai_KeyHandleT       hKey,
                                               ecy_hsm_Csai_JobPriorityT     priority,
                                               const uint8                   msg[],
                                               uint32                        msgLength,
                                               ecy_hsm_Csai_JobHandleT*      phJob);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_SIGN_VERIFY_UPDATE
 * @{
 */

/**
 * [$DD 2378]
 * [$Satisfies $ARCH 542][$Satisfies $ARCH 263]
 * Update a running digital signature verify job with another message chunk.
 *
 * @note This function may return @ref ecy_hsm_CSAI_SUCCESS or @ref ecy_hsm_CSAI_FC_BUSY, an
 * expected flow control value. In the latter case, the HSM is still busy in signing
 * the previous chunk and cannot queue more data at the moment. Try again later.
 *
 *
 * @param[in]   hJob            Handle to the initialized job
 * @param[in]   chunk           Next chunk or entire message to sign.
 * @param[in]   length          Length of the provided chunk of message.
 *
 * Multi-part mode:
 * The caller may repeatedly call this function to provide additional message chunks.
 *
 * Finalization and result query:
 * The caller finalizes and polls for the result of the digital signature scheme using
 * @ref ecy_hsm_Csai_SignGenerateFinish.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                The given digital signature scheme is not supported by this HSM build
 * - @ref ecy_hsm_CSAI_ERR_JOB_NOT_STARTED              The Job is in the wrong state to perform this operation
 * - @ref ecy_hsm_CSAI_ERR_CYCURLIB                     CycurLib returned an error.
 * - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION            There has been an attempt to access HSM ram address via the
 *                                                      CSAI interface
 *
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_SignVerifyUpdate(ecy_hsm_Csai_JobHandleT hJob,
                                                const uint8             chunk[],
                                                uint32                  length);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_SIGN_VERIFY_FINISH
 * @{
 */

/**
 * [$DD 2379]
 * [$Satisfies $ARCH 542][$Satisfies $ARCH 263]
 * Finalize a digital signature verify scheme and query its result.
 *
 * @note This function returns @ref ecy_hsm_CSAI_SUCCESS when the call was
 * successfully posted to the HSM. The synchronize completion of the
 * operation call @ref ecy_hsm_Csai_PollHandle. afterwards
 *
 *
 * @param[in]   hJob                Handle to the initialized job
 * @param[in]   pSign               Pointer to the signature for verification.
 * @param[in]   signLength          Length of the provided @c pSign buffer.
 * @param[out]  pResultFlag         Pointer to a buffer to receive the result of the sign verify operation.
 *                                  Value 0u(FALSE) means signature does not match and 1u(TRUE) means signature matches.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                The given digital signature scheme is not supported by this HSM build
 * - @ref ecy_hsm_CSAI_ERR_JOB_NOT_STARTED              The Job is in the wrong state to perform this operation
 * - @ref ecy_hsm_CSAI_ERR_CYCURLIB                     CycurLib returned an error.
 * - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION            There has been an attempt to access HSM ram address via the
 *                                                      CSAI interface
 *
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_SignVerifyFinish(ecy_hsm_Csai_JobHandleT hJob,
                                                const uint8*            pSign,
                                                uint32                  signLength,
                                                uint32*                 pResultFlag);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_SIGN_VERIFY_EXTENDED_START
 * @{
 */

/**
 * [$DD 2380]
 * [$Satisfies $ARCH 542][$Satisfies $ARCH 263]
 * Initialize and start a multi part or single shot signature verify operation, using extendable set of
 * parameters. The caller must specify in which session context the job is to be executed, a digital
 * signature scheme to use, a pointer to the extendable parameter set and a scheduling priority for the
 * job on the HSM.
 * This function does not block but immediately returns when the job is queued on the HSM.
 *
 * The function uses a pointer to @c ecy_hsm_Csai_SignVerExtended_ParamSetAndVersionT structure which contains
 * additional parameters related to Signature verification (Start stage). These can be extended in the future
 * by incrementing the signParamSetVersion and adding new structures to the @c ecy_hsm_Csai_SignVerStart_ParamSetT union.
 *
 * @note
 * - Multi-part mode:
 *      The caller may update the digital signature verify operation with further message chunks using
 *      @ref ecy_hsm_Csai_SignVerifyUpdate.
 * - Finalization and result query:
 *      The caller finalizes and polls for the result of the digital signature verify operation using
 *      @ref ecy_hsm_Csai_SignVerifyFinish.
 *
 *
 * @param[in]   hSession                    Handle to the session in which the job is placed.
 * @param[in]   priority                    Requested scheduling priority for this job on the HSM.
 * @note
 * Signature operations will always be executed on low priority.
 * Parameter will be overridden by implementation.
 * @param[in]   scheme                          Specification of the SHA variant to use.
 * @param[in]   pSignStartParamSetAndVersion    Pointer to the extendable parameter set and their corresponding version.
 *                                              The caller may provide @c NULL in which case no additional
 *                                              parameter is provided. Otherwise pSignStartParamSet must not be @c NULL.
 * @param[in]   hKey                            Handle to key to be used, OR a keyId
 * @param[in]   pMsg                            First chunk or entire message to sign.
 * @param[in]   msgLength                       Length of the provided message or chunk.
 * @param[out]  phJob                           Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                The given digital signature scheme is not supported by this HSM build
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED          The Job is in the wrong state to perform this operation
 * - @ref ecy_hsm_CSAI_ERR_KEY_NOT_LOADED               The required key has not been loaded into the session
 * - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE               The given key type needs to be an asymmetric public key
 * - @ref ecy_hsm_CSAI_ERR_CYCURLIB                     CycurLib returned an error.
 * - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION            There has been an attempt to access HSM ram address via
 *                                                      the CSAI interface
 */
/* PRQA S 0777 2 */ /* Deviation: rule_5.1_0777 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_SignVerifyExtendedStart(ecy_hsm_Csai_SessionHandleT                       hSession,
                                                       ecy_hsm_Csai_JobPriorityT                         priority,
                                                       ecy_hsm_Csai_SignatureSchemeT                     scheme,
                                                       ecy_hsm_Csai_SignVerExtended_ParamSetAndVersionT* pSignStartParamSetAndVersion,
                                                       ecy_hsm_Csai_KeyHandleT                           hKey,
                                                       const uint8*                                      pMsg,
                                                       uint32                                            msgLength,
                                                       ecy_hsm_Csai_JobHandleT*                          phJob);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_SIGN_VERIFY_EXTENDED_UPDATE
 * @{
 */

/**
 * [$DD 2381]
 * [$Satisfies $ARCH 542][$Satisfies $ARCH 263]
 * Update a running digital signature verify job with another message chunk, using extendable set of
 * parameters
 *
 * The function uses a pointer to @c ecy_hsm_Csai_SignVerExtended_ParamSetAndVersionT structure which contains
 * additional parameters related to Signature verification (Update stage). These can be extended in the future
 * by incrementing the signParamSetVersion and adding new structures to the @c ecy_hsm_Csai_SignVerUpdate_ParamSetT union.
 *
 * @note This function may return @ref ecy_hsm_CSAI_SUCCESS or @ref ecy_hsm_CSAI_FC_BUSY, an
 * expected flow control value. In the latter case, the HSM is still busy in signing
 * the previous chunk and cannot queue more data at the moment. Try again later.
 *
 *
 * @param[in]   hJob                            Handle to the initialized job
 * @param[in]   pSignUpdateParamSetAndVersion   Pointer to the extendable parameter set and their corresponding version.
 *                                              The caller may provide @c NULL in which case no additional
 *                                              parameter is provided
 * @param[in]   pChunk                          Next chunk or entire message to sign.
 * @param[in]   length                          Length of the provided chunk of message.
 *
 * Multi-part mode:
 * The caller may repeatedly call this function to provide additional message chunks.
 *
 * Finalization and result query:
 * The caller finalizes and polls for the result of the digital signature scheme using
 * @ref ecy_hsm_Csai_SignGenerateFinish.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                The given digital signature scheme is not supported by this HSM build
 * - @ref ecy_hsm_CSAI_ERR_JOB_NOT_STARTED              The Job is in the wrong state to perform this operation
 * - @ref ecy_hsm_CSAI_ERR_CYCURLIB                     CycurLib returned an error.
 * - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION            There has been an attempt to access HSM ram address via the
 *                                                      CSAI interface
 *
 */
/* PRQA S 0777 2 */ /* Deviation: rule_5.1_0777 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_SignVerifyExtendedUpdate(ecy_hsm_Csai_JobHandleT                           hJob,
                                                        ecy_hsm_Csai_SignVerExtended_ParamSetAndVersionT* pSignUpdateParamSetAndVersion,
                                                        const uint8*                                      pChunk,
                                                        uint32                                            length);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_SIGN_VERIFY_EXTENDED_FINISH
 * @{
 */

/**
 * [$DD 2382]
 * [$Satisfies $ARCH 542][$Satisfies $ARCH 263]
 * Finalize a digital signature verify scheme and query its result, using extendable set of
 * parameters.
 *
 * The function uses a pointer to @c ecy_hsm_Csai_SignVerExtended_ParamSetAndVersionT structure which contains
 * additional parameters related to Signature verification (Finish stage). These can be extended in the future
 * by incrementing the signParamSetVersion and adding new structures to the @c ecy_hsm_Csai_SignVerFinish_ParamSetT union.
 *
 * @note This function returns @ref ecy_hsm_CSAI_SUCCESS when the call was
 * successfully posted to the HSM. The synchronize completion of the
 * operation call @ref ecy_hsm_Csai_PollHandle. afterwards
 *
 *
 * @param[in]       hJob                           Handle to the initialized job
 * @param[in,out]   pSignFinishParamSetAndVersion  Pointer to the extendable parameter set and their corresponding version.
 *                                                 The caller may provide @c NULL in which case no additional
 *                                                 parameter is provided
 * @param[in]       pSign                          Pointer to the signature for verification.
 * @param[in]       signLength                     Length of the provided @c pSign buffer.
 * @param[out]      pResultFlag                    Pointer to a buffer to receive the result of the sign verify operation.
 *                                                 Value 0u(FALSE) means signature does not match and 1u(TRUE) means signature matches.

 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                The given digital signature scheme is not supported by this HSM build
 * - @ref ecy_hsm_CSAI_ERR_JOB_NOT_STARTED              The Job is in the wrong state to perform this operation
 * - @ref ecy_hsm_CSAI_ERR_CYCURLIB                     CycurLib returned an error.
 * - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION            There has been an attempt to access HSM ram address via the
 *                                                      CSAI interface
 *
 */
/* PRQA S 0777 2 */ /* Deviation: rule_5.1_0777 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_SignVerifyExtendedFinish(ecy_hsm_Csai_JobHandleT                           hJob,
                                                        ecy_hsm_Csai_SignVerExtended_ParamSetAndVersionT* pSignFinishParamSetAndVersion,
                                                        const uint8*                                      pSign,
                                                        uint32                                            signLength,
                                                        uint32*                                           pResultFlag);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_SIGN_VERIFY_ONESHOT
 * @{
 */

/**
 * [$DD 2383]
 * [$Satisfies $ARCH 597][$Satisfies $ARCH 263]
 * Initialize and start a single shot signature verify operation.
 * The caller must  specify in which session context the job is to be executed, a digital signature
 * scheme to use, a handle to a key available to the session, scheduling priority for the
 * job on the HSM, data to be signed and the length of it. The caller must also provide the buffer to
 * placed the verified result, length of the result buffer and result flag.
 * This function does not block but immediately returns when the job is queued on the HSM.
 *
 * @note This function does not block but immediately returns when the job is queued on the HSM.
 * The caller should subsequently
 * call @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle with the returned
 * @c ecy_hsm_Csai_JobHandleT to synchronize with the result.
 *
 * @note This function may return @ref ecy_hsm_CSAI_SUCCESS or @ref ecy_hsm_CSAI_FC_BUSY, an
 * expected flow control value. In the latter case, the HSM is still busy with previous data
 * and cannot provide the result yet. Try again later.
 *
 * @note The fast call interface allows a single block of data to be verified.  Alternatively,
 * use the streaming interface (see @ref ecy_hsm_Csai_SignVerifyStart) if an update of the running job is required.
 *
 * @param[in]   hSession            Handle to the session in which the job is placed.
 * @param[in]   scheme              Specification of the SHA variant to use.
 * @param[in]   hKey                Handle to key to be used, OR a keyId
 * @param[in]   priority            Requested scheduling priority for this job on the HSM.
 * @note
 * Signature operations will always be executed on low priority.
 * Parameter will be overridden by implementation.
 * @param[in]   msg                 First chunk or entire message to sign.
 * @param[in]   msgLength           Length of the provided message or chunk.
 * @param[in]   pSign               Pointer to the signature for verification.
 * @param[in]   signLength          Length of the provided @c pSign buffer.
 * @param[out]  pResultFlag         Pointer to a buffer to receive the result of the sign verify operation.
 *                                  Value 0u(FALSE) means signature does not match and 1u(TRUE) means signature matches.
 * @param[in]   phJob               Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                The given digital signature scheme is not supported by this HSM build
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED          The Job is in the wrong state to perform this operation
 * - @ref ecy_hsm_CSAI_ERR_KEY_NOT_LOADED               The required key has not been loaded into the session
 * - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE               The given key type needs to be an asymmetric public key
 * - @ref ecy_hsm_CSAI_ERR_CYCURLIB                     CycurLib returned an error.
 * - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION            There has been an attempt to access HSM ram address via the
 *                                                      CSAI interface
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_SignVerify(ecy_hsm_Csai_SessionHandleT   hSession,
                                          ecy_hsm_Csai_SignatureSchemeT scheme,
                                          ecy_hsm_Csai_KeyHandleT       hKey,
                                          ecy_hsm_Csai_JobPriorityT     priority,
                                          const uint8*                  msg,
                                          uint32                        msgLength,
                                          const uint8*                  pSign,
                                          uint32                        signLength,
                                          uint32*                       pResultFlag,
                                          ecy_hsm_Csai_JobHandleT*      phJob);

/** @} */ // GROUP_CSAI_SIGN_VERIFY_ONESHOT

/**
 * @addtogroup GROUP_CSAI_SIGN_VERIFY_EXTENDED_ONESHOT
 * @{
 */

/**
 * [$DD 2384]
 * [$Satisfies $ARCH 597][$Satisfies $ARCH 263]
 * Initialize and start a single shot signature verify operation, using extendable set of parameters.
 * The caller must specify in which session context the job is to be executed, a digital signature
 * scheme to use, a pointer to the extendable parameter set, scheduling priority for the
 * job on the HSM, data to be signed and the length of it. The caller must also provide the buffer to
 * placed the verified result, length of the result buffer and result flag.
 * This function does not block but immediately returns when the job is queued on the HSM.
 *
 * The function uses a pointer to @c ecy_hsm_Csai_SignVerExtended_ParamSetAndVersionT structure which contains
 * additional parameters related to Signature verification (one shot). These can be extended in the future
 * by incrementing the signParamSetVersion and adding new structures to the @c ecy_hsm_Csai_SignVerFastCall_ParamSetT union.
 *
 * @note This function does not block but immediately returns when the job is queued on the HSM.
 * The caller should subsequently
 * call @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle with the returned
 * @c ecy_hsm_Csai_JobHandleT to synchronize with the result.
 *
 * @note This function may return @ref ecy_hsm_CSAI_SUCCESS or @ref ecy_hsm_CSAI_FC_BUSY, an
 * expected flow control value. In the latter case, the HSM is still busy with previous data
 * and cannot provide the result yet. Try again later.
 *
 * @note The fast call interface allows a single block of data to be verified. Alternatively,
 * use the streaming interface (see @ref ecy_hsm_Csai_SignVerifyExtendedStart) if an update of the
 * running job is required.
 *
 * @param[in]     hSession                   Handle to the session in which the job is placed.
 * @param[in]     priority                   Requested scheduling priority for this job on the HSM.
 * @note
 * Signature operations will always be executed on low priority.
 * Parameter will be overridden by implementation.
 * @param[in]     scheme                     Specification of the SHA variant to use.
 * @param[in,out] pSignParamSetAndVersion    Pointer to the extendable parameter set and their corresponding version.
 *                                           The caller may provide @c NULL in which case no additional
 *                                           parameter is provided. Otherwise pSignFastCallParamSet must not be @c NULL.
 * @param[in]     hKey                       Handle to key to be used, OR a keyId
 * @param[in]     pMsg                       First chunk or entire message to sign.
 * @param[in]     msgLength                  Length of the provided message or chunk.
 * @param[in]     pSign                      Pointer to the signature for verification.
 * @param[in]     signLength                 Length of the provided @c pSign buffer.
 * @param[out]    pResultFlag                Pointer to a buffer to receive the result of the sign verify operation.
 *                                           Value 0u(FALSE) means signature does not match and 1u(TRUE) means signature matches.
 * @param[out]    phJob                      Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                The given digital signature scheme is not supported by this HSM build
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED          The Job is in the wrong state to perform this operation
 * - @ref ecy_hsm_CSAI_ERR_KEY_NOT_LOADED               The required key has not been loaded into the session
 * - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE               The given key type needs to be an asymmetric public key
 * - @ref ecy_hsm_CSAI_ERR_CYCURLIB                     CycurLib returned an error.
 * - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION            There has been an attempt to access HSM ram address via the
 *                                                      CSAI interface
 */
/* PRQA S 0777 2 */ /* Deviation: rule_5.1_0777 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_SignVerifyExtended(ecy_hsm_Csai_SessionHandleT                       hSession,
                                                  ecy_hsm_Csai_JobPriorityT                         priority,
                                                  ecy_hsm_Csai_SignatureSchemeT                     scheme,
                                                  ecy_hsm_Csai_SignVerExtended_ParamSetAndVersionT* pSignParamSetAndVersion,
                                                  ecy_hsm_Csai_KeyHandleT                           hKey,
                                                  const uint8*                                      pMsg,
                                                  uint32                                            msgLength,
                                                  const uint8*                                      pSign,
                                                  uint32                                            signLength,
                                                  uint32*                                           pResultFlag,
                                                  ecy_hsm_Csai_JobHandleT*                          phJob);

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"

/**
 * @}
 */

/** @} */ // GROUP_CSAI_SIGNATURE

/* *INDENT-OFF* */
#ifdef __cplusplus
} /* extern "C" */
#endif
/* *INDENT-ON* */

#endif /* Multiple inclusion lock  */
