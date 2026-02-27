/**
 * @file
 ***********************************************************************************************
 * @brief She applet interface
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2017, all rights reserved
 **********************************************************************************************/

#ifndef ECY_HSM_APPLET_SHE_H
#define ECY_HSM_APPLET_SHE_H

/*
**********************************************************************************************************************
* Includes
**********************************************************************************************************************
*/
#include "ecy_hsm_applet.h"
#include "ecy_hsm_csai.h"


/**
 * @addtogroup APPLET_IMPL
 * @{
 */
/*
**********************************************************************************************************************
* Type definitions
**********************************************************************************************************************
*/
/**
 * @brief Possible states for she applet
 * @details
 * @section APPLET_SHE Random number generation applet
 *
 * @subsection APPLET_SHE_STATES Applet states
 *
 * @image html ./states_she.png "State diagram of applet: She" width=15cm
 * @image rtf  ./states_she.png "State diagram of applet: She" width=15cm
 */
typedef enum ecy_hsm_Applet_She_StateT
{
    ecy_hsm_APPLET_SHE_FUNC_GET_ID,              /**< The function returns the identity (UID) and the value of the status register protected by a */
                                                 /**< * MAC over a challenge and the data as specified by SHE V1.1. in section 7.17. */
    ecy_hsm_APPLET_SHE_FUNC_LOAD_KEY,            /**< Update a key according to the key update protocol specified by SHE v1.1 in section 9. */
    ecy_hsm_APPLET_SHE_FUNC_LOAD_KEY_EXTENDED,   /**< Update an extended key according to the key update protocol specified by SHE v1.1 in section 9. */
    ecy_hsm_APPLET_SHE_FUNC_LOAD_PLAIN_KEY,      /**< Load a key without encryption or verification into the RAM_KEY slot of SHE according */
                                                 /**< * SHE v1.1 section 7.8. */
    ecy_hsm_APPLET_SHE_FUNC_EXPORT_RAM_KEY,      /**< Export a previously loaded RAM_KEY into a format protected by SECRET_KEY. */
    ecy_hsm_APPLET_SHE_FUNC_SECURE_BOOT,         /**< Start the secure boot process. This functionality is only available when Secure */
                                                 /**< * Boot is supported by the HSM, otherwise it returns ecy_hsm_CSAI_ERR_NO_SECURE_BOOT. */
    ecy_hsm_APPLET_SHE_FUNC_SECURE_BOOT_OK,      /**< * Mark the secure boot process as OK. This functionality is only available when Secure */
                                                 /**< * Boot is supported by the HSM, otherwise it returns ecy_hsm_CSAI_ERR_NO_SECURE_BOOT. */
    ecy_hsm_APPLET_SHE_FUNC_SECURE_BOOT_FAILURE, /**< * Mark the secure boot process of failed. This function is not reversible before */
                                                 /**< * the next power cycle. This functionality is only available when Secure */
                                                 /**< * Boot is supported by the HSM, otherwise it returns ecy_hsm_CSAI_ERR_NO_SECURE_BOOT. */
    ecy_hsm_APPLET_SHE_FUNC_DEBUG_CHALLENGE,     /**< Activate any internal debug facilities in the SHE module. Activating the debugger implies */
                                                 /**< * erasing all keys except @ref SECRET_KEY, UID, and the PRNG seed and will only work if */
                                                 /**< * no keys are write protected. */
    ecy_hsm_APPLET_SHE_FUNC_DEBUG_AUTHORIZE,     /**< Activate HSM debugging (NOP) */
    ecy_hsm_APPLET_SHE_FUNC_ENCRYPT_ECB,         /**< Perform an ECB encryption. This function can process exactly 128 bits. */
                                                 /**< * SHE does not pad, so it is in the caller's responsibility to pad properly. */
    ecy_hsm_APPLET_SHE_FUNC_DECRYPT_ECB,         /**< Perform an ECB decryption. This function can process exactly 128 bits. */
                                                 /**< * SHE does not pad, so it is in the caller's responsibility to pad properly. */
    ecy_hsm_APPLET_SHE_FUNC_ENCRYPT_CBC,         /**< Perform a CBC encryption. */
                                                 /**< * SHE does not pad, thus a chunk must be a multiple of the supported block width, */
                                                 /**< * 128 bits. It is the caller's duty to pad properly. */
    ecy_hsm_APPLET_SHE_FUNC_DECRYPT_CBC,         /**< Perform a CBC decryption. */
                                                 /**< * SHE does not pad, thus a chunk must be a multiple of the supported block width, */
                                                 /**< * 128 bits. It is the caller's duty to pad properly. */
                                                 /**< * This function imposes limits on the chunk size, see CYCURHSM_SC_MAX_CHUNK_SIZE. */
    ecy_hsm_APPLET_SHE_FUNC_EXTEND_SEED,         /**< Extend the seed of the PRNG with the caller supplied entropy. */
                                                 /**< * @details As the HSM uses a high quality TRNG for the PRNG seed, the entropy provided to this */
                                                 /**< * function is ignored. */
    ecy_hsm_APPLET_SHE_FUNC_MAC_GENERATE,        /**< Start a MAC generation. This function supports updating the message to MAC with additional */
                                                 /**< * chunks and can thus process messages of theoretically up to 2^^32 bits, however there */
                                                 /**< * are restrictions regarding the chunk sizes provided to this call and */
                                                 /**< * @ref SHE_GenerateMAC. */
                                                 /**< * SHE does not pad, thus a chunk must be a multiple of the supported block width, */
                                                 /**< * 128 bits. It is the caller's duty to pad properly. */
                                                 /**< * This function imposes limits on the chunk size, see CYCURHSM_SC_MAX_CHUNK_SIZE. */
    ecy_hsm_APPLET_SHE_FUNC_MAC_VERIFY,          /**< Start a MAC verification. This function supports updating the message to MAC with additional */
                                                 /**< * chunks and can thus process messages of theoretically up to 2^^32 bits, however there */
                                                 /**< * are restrictions regarding the chunk sizes provided to this call and */
                                                 /**< * @ref SHE_VerifyMAC. A chunk must be a multiple of the supported block width, */
                                                 /**< * 128 bits. */
    ecy_hsm_APPLET_SHE_FUNC_RND,                 /**< Start the generation of a vector of 128 bits random data */
    ecy_hsm_APPLET_SHE_FUNC_LOAD_KEY_TO_BANK,    /**< Update a key according to the key update protocol specified by SHE v1.1 in section 9, in accordance with further extended requirements initially stipulated in CYS2200. */
    ecy_hsm_APPLET_SHE_FUNC_INIT_RNG,            /**< Sets the bit for RND_INIT in the SHE status register (HSM TRNG and PRNG require no special initialization) */
    /* This needs to be the final entry */
    ecy_hsm_APPLET_SHE_NUMSTATES                 /**< number of states */
} ecy_hsm_Applet_She_StateT;

/* *********** Deprecated enum definitions ***************/
/**
 * @deprecated by ecy_hsm_APPLET_SHE_FUNC_GET_ID
 */
#define APPLET_SHE_FUNC_GET_ID ecy_hsm_APPLET_SHE_FUNC_GET_ID
/**
 * @deprecated by ecy_hsm_APPLET_SHE_FUNC_LOAD_KEY
 */
#define APPLET_SHE_FUNC_LOAD_KEY ecy_hsm_APPLET_SHE_FUNC_LOAD_KEY
/**
 * @deprecated by ecy_hsm_APPLET_SHE_FUNC_LOAD_KEY_EXTENDED
 */
#define APPLET_SHE_FUNC_LOAD_KEY_EXTENDED ecy_hsm_APPLET_SHE_FUNC_LOAD_KEY_EXTENDED
/**
 * @deprecated by ecy_hsm_APPLET_SHE_FUNC_LOAD_PLAIN_KEY
 */
#define APPLET_SHE_FUNC_LOAD_PLAIN_KEY ecy_hsm_APPLET_SHE_FUNC_LOAD_PLAIN_KEY
/**
 * @deprecated by ecy_hsm_APPLET_SHE_FUNC_EXPORT_RAM_KEY
 */
#define APPLET_SHE_FUNC_EXPORT_RAM_KEY ecy_hsm_APPLET_SHE_FUNC_EXPORT_RAM_KEY
/**
 * @deprecated by ecy_hsm_APPLET_SHE_FUNC_SECURE_BOOT
 */
#define APPLET_SHE_FUNC_SECURE_BOOT ecy_hsm_APPLET_SHE_FUNC_SECURE_BOOT
/**
 * @deprecated by ecy_hsm_APPLET_SHE_FUNC_SECURE_BOOT_OK
 */
#define APPLET_SHE_FUNC_SECURE_BOOT_OK ecy_hsm_APPLET_SHE_FUNC_SECURE_BOOT_OK
/**
 * @deprecated by ecy_hsm_APPLET_SHE_FUNC_SECURE_BOOT_FAILURE
 */
#define APPLET_SHE_FUNC_SECURE_BOOT_FAILURE ecy_hsm_APPLET_SHE_FUNC_SECURE_BOOT_FAILURE
/**
 * @deprecated by ecy_hsm_APPLET_SHE_FUNC_DEBUG_CHALLENGE
 */
#define APPLET_SHE_FUNC_DEBUG_CHALLENGE ecy_hsm_APPLET_SHE_FUNC_DEBUG_CHALLENGE
/**
 * @deprecated by ecy_hsm_APPLET_SHE_FUNC_DEBUG_AUTHORIZE
 */
#define APPLET_SHE_FUNC_DEBUG_AUTHORIZE ecy_hsm_APPLET_SHE_FUNC_DEBUG_AUTHORIZE
/**
 * @deprecated by ecy_hsm_APPLET_SHE_FUNC_ENCRYPT_ECB
 */
#define APPLET_SHE_FUNC_ENCRYPT_ECB ecy_hsm_APPLET_SHE_FUNC_ENCRYPT_ECB
/**
 * @deprecated by ecy_hsm_APPLET_SHE_FUNC_DECRYPT_ECB
 */
#define APPLET_SHE_FUNC_DECRYPT_ECB ecy_hsm_APPLET_SHE_FUNC_DECRYPT_ECB
/**
 * @deprecated by ecy_hsm_APPLET_SHE_FUNC_ENCRYPT_CBC
 */
#define APPLET_SHE_FUNC_ENCRYPT_CBC ecy_hsm_APPLET_SHE_FUNC_ENCRYPT_CBC
/**
 * @deprecated by ecy_hsm_APPLET_SHE_FUNC_DECRYPT_CBC
 */
#define APPLET_SHE_FUNC_DECRYPT_CBC ecy_hsm_APPLET_SHE_FUNC_DECRYPT_CBC
/**
 * @deprecated by ecy_hsm_APPLET_SHE_FUNC_EXTEND_SEED
 */
#define APPLET_SHE_FUNC_EXTEND_SEED ecy_hsm_APPLET_SHE_FUNC_EXTEND_SEED
/**
 * @deprecated by ecy_hsm_APPLET_SHE_FUNC_MAC_GENERATE
 */
#define APPLET_SHE_FUNC_MAC_GENERATE ecy_hsm_APPLET_SHE_FUNC_MAC_GENERATE
/**
 * @deprecated by ecy_hsm_APPLET_SHE_FUNC_MAC_VERIFY
 */
#define APPLET_SHE_FUNC_MAC_VERIFY ecy_hsm_APPLET_SHE_FUNC_MAC_VERIFY
/**
 * @deprecated by ecy_hsm_APPLET_SHE_FUNC_RND
 */
#define APPLET_SHE_FUNC_RND ecy_hsm_APPLET_SHE_FUNC_RND
/**
 * @deprecated by ecy_hsm_APPLET_SHE_FUNC_LOAD_KEY_TO_BANK
 */
#define APPLET_SHE_FUNC_LOAD_KEY_TO_BANK ecy_hsm_APPLET_SHE_FUNC_LOAD_KEY_TO_BANK
/**
 * @deprecated by ecy_hsm_APPLET_SHE_FUNC_INIT_RNG
 */
#define APPLET_SHE_FUNC_INIT_RNG ecy_hsm_APPLET_SHE_FUNC_INIT_RNG
/**
 * @deprecated by ecy_hsm_APPLET_SHE_NUMSTATES
 */
#define APPLET_SHE_NUMSTATES ecy_hsm_APPLET_SHE_NUMSTATES
/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by ecy_hsm_Applet_She_StateT
 */
#define Applet_She_StateT ecy_hsm_Applet_She_StateT

/**
 * Applet context data for SHE testing applet
 * @ingroup APPLET_CONTEXT
 */
typedef HSM_SheParamT Applet_SheCtx_tst;



/*
**********************************************************************************************************************
* Extern declarations
**********************************************************************************************************************
*/

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @brief SHE applet control structures
 */
extern const Applet_ts Applet_SHE_HSM;

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @}
 */
#endif // ECY_HSM_APPLET_SHE_H
