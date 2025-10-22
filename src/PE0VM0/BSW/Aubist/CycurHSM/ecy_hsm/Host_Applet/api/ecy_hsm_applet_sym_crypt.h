/**
 * @file
 ***********************************************************************************************
 * @brief symmetric de/encryption applet interface
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2014, all rights reserved.
 **********************************************************************************************/

#ifndef ECY_HSM_APPLET_SYM_CRYPT_H
#define ECY_HSM_APPLET_SYM_CRYPT_H

/*
**********************************************************************************************************************
* Includes
**********************************************************************************************************************
*/
#include "ecy_hsm_applet.h"

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
 * @brief Possible states for the de/encryption applets
 *
 * @details
 * @section APPLET_SYM_CRYPT Symmetric decryption applet
 *
 */
typedef enum ecy_hsm_Applet_SymCrypt_StateT
{
    ecy_hsm_APPLET_SYM_CRYPT_STATE_INIT,        /**< Symmetric de/encryption - Initialize cryptographic routine */
    ecy_hsm_APPLET_SYM_CRYPT_STATE_UPDATE,      /**< Symmetric de/encryption - Update data */
    ecy_hsm_APPLET_SYM_CRYPT_STATE_FINAL,       /**< Symmetric de/encryption - Finish cryptographic routine */
    ecy_hsm_APPLET_SYM_CRYPT_STATE_FULL,        /**< Symmetric de/encryption - Perform full cryptographic routine */

    ecy_hsm_APPLET_SYM_AUTH_CRYPT_STATE_INIT,   /**< Symmetric authentication de/encryption - Initialize cryptographic routine */
    ecy_hsm_APPLET_SYM_AUTH_CRYPT_STATE_UPDATE, /**< Symmetric authentication de/encryption - Update data */
    ecy_hsm_APPLET_SYM_AUTH_CRYPT_STATE_FINAL,  /**< Symmetric authentication de/encryption - Finish cryptographic routine */
    ecy_hsm_APPLET_SYM_AUTH_CRYPT_STATE_FULL,   /**< Symmetric authentication de/encryption - Perform full cryptographic routine */

    /* This needs to be the final entry */
    ecy_hsm_APPLET_SYM_CRYPT_NUMSTATES          /**< Symmetric de/encryption - number of states */
} ecy_hsm_Applet_SymCrypt_StateT;

/**
 * Applet context data for symmetric cypto operations
 * @ingroup APPLET_CONTEXT
 */
typedef struct ecy_hsm_Applet_SymCryptParamTag
{
    ecy_hsm_Csai_SymCipherModeT cipherMode;       /**< Cipher suite mode to use for the de/encryption operation */
    ecy_hsm_Csai_PaddingModeT   paddingMode;      /**< Padding mode to use for the de/encryption operation */
    ecy_hsm_Csai_KeyHandleT     hKey;             /**< Handle to a key available in the HSM's session context to use for de/encryption */
    const uint8*                iv;               /**< Array of data for the initialization vector */
    uint32                      ivLength;         /**< Length of the IV data array in bytes */
    const uint8*                aad;              /**< Array of data for authentication. */
    uint32                      aadLength;        /**< Length of data for authentication */
    const uint8*                inputText;        /**< First chunk or entire message to de/encrypted */
    uint32                      inputTextLength;  /**< Length of the provided message or chunk */
    uint8*                      outputText;       /**< Pointer to space where the HSM can store the de/encrypted chunk */
    uint32                      outputTextLength; /**< Length of data block */
    uint32*                     pOutputTextCount; /**< Pointer to buffer to receive number of bytes written */
    uint8*                      pTag;             /**< Pointer to buffer to receive the authentication tag */
    uint32                      tagLength;        /**< Size of the tag buffer in bytes, must be at least 16 */
} ecy_hsm_Applet_SymCryptParamT;

/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by @ref ecy_hsm_Applet_SymCryptParamT
 */
#define Applet_SymCryptParamT ecy_hsm_Applet_SymCryptParamT
/**
 * @deprecated by @ref ecy_hsm_Applet_SymCrypt_StateT
 */
#define Applet_SymCrypt_StateT ecy_hsm_Applet_SymCrypt_StateT
/**
 * @deprecated by @ref ecy_hsm_Applet_SymCryptParamTag
 */
#define Applet_SymCryptParamTag ecy_hsm_Applet_SymCryptParamTag
/* *********** Deprecated enum definitions ***************/
/**
 * @deprecated by @ref ecy_hsm_APPLET_SYM_CRYPT_STATE_INIT
 */
#define APPLET_SYM_CRYPT_STATE_INIT ecy_hsm_APPLET_SYM_CRYPT_STATE_INIT
/**
 * @deprecated by @ref ecy_hsm_APPLET_SYM_CRYPT_STATE_UPDATE
 */
#define APPLET_SYM_CRYPT_STATE_UPDATE ecy_hsm_APPLET_SYM_CRYPT_STATE_UPDATE
/**
 * @deprecated by @ref ecy_hsm_APPLET_SYM_CRYPT_STATE_FINAL
 */
#define APPLET_SYM_CRYPT_STATE_FINAL ecy_hsm_APPLET_SYM_CRYPT_STATE_FINAL
/**
 * @deprecated by @ref ecy_hsm_APPLET_SYM_CRYPT_STATE_FULL
 */
#define APPLET_SYM_CRYPT_STATE_FULL ecy_hsm_APPLET_SYM_CRYPT_STATE_FULL
/**
 * @deprecated by @ref ecy_hsm_APPLET_SYM_AUTH_CRYPT_STATE_INIT
 */
#define APPLET_SYM_AUTH_CRYPT_STATE_INIT ecy_hsm_APPLET_SYM_AUTH_CRYPT_STATE_INIT
/**
 * @deprecated by @ref ecy_hsm_APPLET_SYM_AUTH_CRYPT_STATE_UPDATE
 */
#define APPLET_SYM_AUTH_CRYPT_STATE_UPDATE ecy_hsm_APPLET_SYM_AUTH_CRYPT_STATE_UPDATE
/**
 * @deprecated by @ref ecy_hsm_APPLET_SYM_AUTH_CRYPT_STATE_FINAL
 */
#define APPLET_SYM_AUTH_CRYPT_STATE_FINAL ecy_hsm_APPLET_SYM_AUTH_CRYPT_STATE_FINAL
/**
 * @deprecated by @ref ecy_hsm_APPLET_SYM_AUTH_CRYPT_STATE_FULL
 */
#define APPLET_SYM_AUTH_CRYPT_STATE_FULL ecy_hsm_APPLET_SYM_AUTH_CRYPT_STATE_FULL
/**
 * @deprecated by @ref ecy_hsm_APPLET_SYM_CRYPT_NUMSTATES
 */
#define APPLET_SYM_CRYPT_NUMSTATES ecy_hsm_APPLET_SYM_CRYPT_NUMSTATES
/*
**********************************************************************************************************************
* Extern declarations
**********************************************************************************************************************
*/

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @brief Symmetric decryption applet control structures
 */
extern const Applet_ts Applet_SymDecrypt_HSM;

/**
 * @brief Symmetric encryption applet control structures
 */
extern const Applet_ts Applet_SymEncrypt_HSM;

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @}
 */
#endif // ECY_HSM_APPLET_SYM_CRYPT_H
