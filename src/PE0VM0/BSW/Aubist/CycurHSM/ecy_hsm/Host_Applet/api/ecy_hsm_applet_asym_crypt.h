/**
 * @file
 ***********************************************************************************************
 * @brief Asymmetric de-/encryption applet interface
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2020, all rights reserved.
 **********************************************************************************************/



#ifndef ECY_HSM_APPLET_ASYM_CRYPT_H
#define ECY_HSM_APPLET_ASYM_CRYPT_H

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
 * @brief Possible states for asymmetric decryption applet
 *
 * @details
 * @section APPLET_ASYM_CRYPT Asymmetric decryption applet
 */
typedef enum ecy_hsm_Applet_AsymCryptStatusTag
{
    ecy_hsm_APPLET_ASYM_CRYPT_STATE_FULL,          /**< state for full asymmetric de-/encryption */
    ecy_hsm_APPLET_ASYM_CRYPT_EXTENDED_STATE_FULL, /**< state for full asymmetric de-/encryption extended */
    /* This needs to be the final entry */
    ecy_hsm_APPLET_ASYM_CRYPT_NUMSTATES            /**< number of states */
} ecy_hsm_Applet_AsymCryptStatusT;

/**
 * Parameters for asymmetric decryption applet
 */
typedef struct ecy_hsm_Applet_AsymCryptParamTag
{
    ecy_hsm_Csai_AsymCipherModeT cipherMode;       /**< Cipher suite mode to use for the decryption operation */
    ecy_hsm_Csai_KeyHandleT      hKey;             /**< Handle to a key available in the HSM's session context to use for decryption */
    const uint8*                 inputText;        /**< First chunk or entire message to de/en-crypt */
    uint32                       inputTextLength;  /**< Length of the provided message or chunk */
    uint8*                       outputText;       /**< Pointer to space where the HSM can store the de-/encryption chunk */
    uint32                       outputTextLength; /**< Length of clear text buffer */
    uint32*                      pOutputTextCount; /**< Pointer to buffer for the number of bytes written to clear text buffer */
} ecy_hsm_Applet_AsymCryptParamT;

/**
 * Parameters for asymmetric encrypt applet with extendable CSAI
 */
typedef struct ecy_hsm_Applet_AsymEncryptExtendedParamTag {
    ecy_hsm_Applet_AsymCryptParamT                   asymCryptBasicParam;              /**< Original parameters of AsymCrypt, to be used along side with extendable parameters */
    ecy_hsm_Csai_AsymEncryptExt_ParamSetAndVersionT *pAsymEncryptParamSetAndVersion;   /**< Pointer to the extendable parameter set and its version used by the corresponding extended CSAI */
} ecy_hsm_Applet_AsymEncryptExtendedParamT;

/**
 * Parameters for asymmetric decrypt applet with extendable CSAI
 */
typedef struct ecy_hsm_Applet_AsymDecryptExtendedParamTag {
    ecy_hsm_Applet_AsymCryptParamT                   asymCryptBasicParam;              /**< Original parameters of AsymCrypt, to be used along side with extendable parameters */
    ecy_hsm_Csai_AsymDecryptExt_ParamSetAndVersionT *pAsymDecryptParamSetAndVersion;   /**< Pointer to the extendable parameter set and its version used by the corresponding extended CSAI */
} ecy_hsm_Applet_AsymDecryptExtendedParamT;
/* *********** Deprecated enum definitions ***************/
/**
 * @deprecated by @ref ecy_hsm_APPLET_ASYM_CRYPT_STATE_FULL
 */
#define APPLET_ASYM_CRYPT_STATE_FULL ecy_hsm_APPLET_ASYM_CRYPT_STATE_FULL
/**
 * @deprecated by @ref ecy_hsm_APPLET_ASYM_CRYPT_NUMSTATES
 */
#define APPLET_ASYM_CRYPT_NUMSTATES ecy_hsm_APPLET_ASYM_CRYPT_NUMSTATES

/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by @ref ecy_hsm_Applet_AsymCryptStatusT
 */
#define Applet_AsymCryptStatusT ecy_hsm_Applet_AsymCryptStatusT
/**
 * @deprecated by @ref ecy_hsm_Applet_AsymCryptParamT
 */
#define Applet_AsymCryptParamT ecy_hsm_Applet_AsymCryptParamT
/**
 * @deprecated by @ref ecy_hsm_Applet_AsymCryptStatusTag
 */
#define Applet_AsymCryptStatusTag ecy_hsm_Applet_AsymCryptStatusTag
/**
 * @deprecated by @ref ecy_hsm_Applet_AsymCryptParamTag
 */
#define Applet_AsymCryptParamTag ecy_hsm_Applet_AsymCryptParamTag

/*
**********************************************************************************************************************
* Extern declarations
**********************************************************************************************************************
*/
/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @brief AsymEncrypt applet control structures
 */
extern const Applet_ts Applet_AsymEncrypt_HSM;

/**
 * @brief AsymDecrypt applet control structures
 */
extern const Applet_ts Applet_AsymDecrypt_HSM;

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @}
 */
#endif // ECY_HSM_APPLET_ASYM_CRYPT_H
