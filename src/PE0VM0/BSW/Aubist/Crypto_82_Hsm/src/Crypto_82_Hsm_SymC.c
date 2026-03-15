/**
 * \file Crypto_82_Hsm_SymC.c
 *
 * \author      PiNTeam
 * \copyright   (c) DENSO KK, 2022
 *
 * \brief Implementation of the Symmetric Cryptography module
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
 * \brief Mapping for symmetric cipher modes.
 *
 * \param [in] mode           Crypto Service layer supported symmetric cipher mode.
 *
 * \return ret_mode           Corresponding symmetric cipher mode supported by the HSM.
 */
static FUNC(ecy_hsm_Csai_SymCipherModeT , CRYPTO_82_HSM_CODE) get_symCipherMode(Crypto_82_Hsm_Service_SymCipherModeType mode);

/**
 * \brief Mapping for padding modes.
 *
 * \param [in] padding        Crypto Service layer supported padding mode.
 *
 * \return ret_padding        Corresponding symmetric cipher padding mode supported by the HSM.
 */
static FUNC(ecy_hsm_Csai_PaddingModeT , CRYPTO_82_HSM_CODE) get_paddingMode(Crypto_82_Hsm_Service_PaddingModeType padding);

/**********************************************************************************************************************\
 * PRIVATE FUNCTION IMPLEMENTATIONS
\**********************************************************************************************************************/

static FUNC(ecy_hsm_Csai_SymCipherModeT, CRYPTO_82_HSM_CODE) get_symCipherMode(Crypto_82_Hsm_Service_SymCipherModeType mode)
{
    ecy_hsm_Csai_SymCipherModeT ret_mode = CSAI_SYMCIPHER_RESERVED;

    switch (mode)
    {
    case CryptoDriver_AES_ECB:
        ret_mode = ecy_hsm_CSAI_AES_ECB;
        break;
    case CryptoDriver_AES_CBC:
        ret_mode = ecy_hsm_CSAI_AES_CBC;
        break;
    case CryptoDriver_AES_CFB128:
        ret_mode = ecy_hsm_CSAI_AES_CFB128;
        break;
    case CryptoDriver_AES_OFB:
        ret_mode = ecy_hsm_CSAI_AES_OFB;
        break;
    case CryptoDriver_AES_CTR:
        ret_mode = ecy_hsm_CSAI_AES_CTR;
        break;
    case CryptoDriver_AES_XTS:
        ret_mode = ecy_hsm_CSAI_AES_XTS;
        break;
    case CryptoDriver_AES_GCM:
        ret_mode = ecy_hsm_CSAI_AES_GCM;
        break;
    default:
        ret_mode = CSAI_SYMCIPHER_RESERVED;
        break;
    }

    return ret_mode;
}

static FUNC(ecy_hsm_Csai_PaddingModeT, CRYPTO_82_HSM_CODE) get_paddingMode(Crypto_82_Hsm_Service_PaddingModeType padding)
{
    ecy_hsm_Csai_PaddingModeT ret_padding = CSAI_PADDINGMODE_RESERVED;

    switch (padding)
    {
    case CryptoDriver_PAD_NONE:
        ret_padding = ecy_hsm_CSAI_PAD_NONE;
        break;
    case CryptoDriver_PAD_PKCS7:
        ret_padding = ecy_hsm_CSAI_PAD_PKCS7;
        break;
    case CryptoDriver_NIST_SP800:
        ret_padding = ecy_hsm_CSAI_PAD_NIST_SP800;
        break;
    default:
        ret_padding = CSAI_PADDINGMODE_RESERVED;
        break;
    }

    return ret_padding;
}
/**********************************************************************************************************************\
 * PUBLIC FUNCTION IMPLEMENTATIONS
\**********************************************************************************************************************/

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
)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) errorCode;
    ecy_hsm_Csai_SymCipherModeT csai_SymCipherMode = get_symCipherMode(symCipherMode);
    ecy_hsm_Csai_PaddingModeT csai_paddingMode = get_paddingMode(paddingMode);

    /* Satisfies SWS_Crypto_00135 */
     errorCode = ecy_hsm_Csai_Encrypt( csaiSession->hSession, csaiSession->priority, csai_SymCipherMode,
                                       csai_paddingMode, hKey, iv,
                                       iv_len, msg, msg_len,
                                       cipher, *cipher_len, cipher_len,
                                       &(csaiSession->hJob) );

    return errorCode;
}

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
)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) errorCode;
    ecy_hsm_Csai_SymCipherModeT csai_SymCipherMode = (ecy_hsm_Csai_SymCipherModeT)get_symCipherMode(symCipherMode);
    ecy_hsm_Csai_PaddingModeT csai_paddingMode = (ecy_hsm_Csai_PaddingModeT)get_paddingMode(paddingMode);

    errorCode = ecy_hsm_Csai_EncryptStart( csaiSession->hSession, csaiSession->priority, csai_SymCipherMode,
                                           csai_paddingMode, hKey, iv,
                                           iv_len, msg, msg_len,
                                           cipher, *cipher_len, cipher_len,
                                           &(csaiSession->hJob) );

    return errorCode;
}

FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_SymC_Encrypt_Update
(
    VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC) csaiSession,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) msg,
    VAR(uint32, AUTOMATIC) msg_len,
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) cipher, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) cipher_len /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) errorCode;

    errorCode = ecy_hsm_Csai_EncryptUpdate( csaiSession.hJob, msg, msg_len,
                                            cipher, *cipher_len, cipher_len);

    return errorCode;
}

FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_SymC_Encrypt_Finish
(
    VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC) csaiSession,
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) cipher, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) cipher_len /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) errorCode;

    /* Satisfies SWS_Crypto_00135 */
    errorCode = ecy_hsm_Csai_EncryptFinish( csaiSession.hJob , cipher, *cipher_len,
                                            cipher_len );

    return errorCode;
}

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
)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) errorCode;
    ecy_hsm_Csai_SymCipherModeT csai_SymCipherMode = (ecy_hsm_Csai_SymCipherModeT)get_symCipherMode(symCipherMode);
    ecy_hsm_Csai_PaddingModeT csai_paddingMode = (ecy_hsm_Csai_PaddingModeT)get_paddingMode(paddingMode);

    /* Satisfies SWS_Crypto_00135 */
    errorCode = ecy_hsm_Csai_Decrypt( csaiSession->hSession, csaiSession->priority, csai_SymCipherMode,
                                      csai_paddingMode, hKey, iv,
                                      iv_len, cipher, cipher_len,
                                      msg, *msg_len, msg_len,
                                      &(csaiSession->hJob) );

    return errorCode;
}

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
)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) errorCode;
    ecy_hsm_Csai_SymCipherModeT csai_SymCipherMode = (ecy_hsm_Csai_SymCipherModeT)get_symCipherMode(symCipherMode);
    ecy_hsm_Csai_PaddingModeT csai_paddingMode = (ecy_hsm_Csai_PaddingModeT)get_paddingMode(paddingMode);

    errorCode = ecy_hsm_Csai_DecryptStart( csaiSession->hSession, csaiSession->priority, csai_SymCipherMode,
                                           csai_paddingMode, hKey, iv,
                                           iv_len, cipher, cipher_len,
                                           msg, *msg_len, msg_len,
                                           &(csaiSession->hJob) );

    return errorCode;
}

FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_SymC_Decrypt_Update
(
    VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC) csaiSession,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) cipher,
    VAR(uint32, AUTOMATIC) cipher_len,
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) msg, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) msg_len /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) errorCode;

    errorCode = ecy_hsm_Csai_DecryptUpdate( csaiSession.hJob, cipher, cipher_len,
                                            msg, *msg_len, msg_len );

    return errorCode;
}

FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_SymC_Decrypt_Finish
(
    VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC) csaiSession,
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) msg, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) msg_len /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) errorCode;

    /* Satisfies SWS_Crypto_00135 */
    errorCode = ecy_hsm_Csai_DecryptFinish( csaiSession.hJob , msg, *msg_len,
                                            msg_len );

    return errorCode;
}

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
)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) errorCode;
    ecy_hsm_Csai_SymCipherModeT csai_SymCipherMode = (ecy_hsm_Csai_SymCipherModeT)get_symCipherMode(symCipherMode);
    ecy_hsm_Csai_PaddingModeT csai_paddingMode = (ecy_hsm_Csai_PaddingModeT)get_paddingMode(paddingMode);


    errorCode = ecy_hsm_Csai_AuthDecrypt( csaiSession->hSession, csaiSession->priority, csai_SymCipherMode,
                                          csai_paddingMode, hKey, iv,
                                          iv_len,
                                          aad, aadLength,
                                          cipher, cipher_len,
                                          msg, *msg_length,
                                          msg_length, pTag, tagLength,
                                          &(csaiSession->hJob) );

    return errorCode;
}

FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Auth_Decrypt_Start
(
    P2VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC, CRYPTO_82_HSM_VAR) csaiSession, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(ecy_hsm_Csai_KeyHandleT, AUTOMATIC) hKey,
    VAR(Crypto_82_Hsm_Service_SymCipherModeType, AUTOMATIC) symCipherMode,
    VAR(Crypto_82_Hsm_Service_PaddingModeType, AUTOMATIC) paddingMode,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) iv,
    VAR(uint32, AUTOMATIC) iv_len
)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) errorCode;
    ecy_hsm_Csai_SymCipherModeT csai_SymCipherMode = (ecy_hsm_Csai_SymCipherModeT)get_symCipherMode(symCipherMode);
    ecy_hsm_Csai_PaddingModeT csai_paddingMode = (ecy_hsm_Csai_PaddingModeT)get_paddingMode(paddingMode);

    errorCode = ecy_hsm_Csai_AuthDecryptStart( csaiSession->hSession, csaiSession->priority, csai_SymCipherMode,
                                               csai_paddingMode, hKey, iv,
                                               iv_len,
                                               &(csaiSession->hJob) );

    return errorCode;
}

FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Auth_Decrypt_Update
(
    VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC) csaiSession,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) aad,
    VAR(uint32, AUTOMATIC) aadLength
)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) errorCode;

    errorCode = ecy_hsm_Csai_AuthDecryptUpdate( csaiSession.hJob, aad, aadLength );

    return errorCode;
}

FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Auth_Decrypt_Finish
(
    VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC) csaiSession,
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) msg, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) msg_len, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) pTag, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(uint32, AUTOMATIC) tagLength
)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) errorCode;

    errorCode = ecy_hsm_Csai_AuthDecryptFinish( csaiSession.hJob, msg, *msg_len,
                                                msg_len, pTag, tagLength );

    return errorCode;
}

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
)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) errorCode;
    ecy_hsm_Csai_SymCipherModeT csai_SymCipherMode = (ecy_hsm_Csai_SymCipherModeT)get_symCipherMode(symCipherMode);
    ecy_hsm_Csai_PaddingModeT csai_paddingMode = (ecy_hsm_Csai_PaddingModeT)get_paddingMode(paddingMode);

    errorCode = ecy_hsm_Csai_AuthEncrypt( csaiSession->hSession, csaiSession->priority, csai_SymCipherMode,
                                          csai_paddingMode, hKey, iv,
                                          iv_len,
                                          aad, aadLength,
                                          msg, msg_len,
                                          cipher, *cipher_len,
                                          cipher_len, pTag, tagLength,
                                          &(csaiSession->hJob) );

    return errorCode;
}

FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Auth_Encrypt_Start
(
    P2VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC, CRYPTO_82_HSM_VAR) csaiSession, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(ecy_hsm_Csai_KeyHandleT, AUTOMATIC) hKey,
    VAR(Crypto_82_Hsm_Service_SymCipherModeType, AUTOMATIC) symCipherMode,
    VAR(Crypto_82_Hsm_Service_PaddingModeType, AUTOMATIC) paddingMode,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) iv,
    VAR(uint32, AUTOMATIC) iv_len
)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) errorCode;
    ecy_hsm_Csai_SymCipherModeT csai_SymCipherMode = (ecy_hsm_Csai_SymCipherModeT)get_symCipherMode(symCipherMode);
    ecy_hsm_Csai_PaddingModeT csai_paddingMode = (ecy_hsm_Csai_PaddingModeT)get_paddingMode(paddingMode);

    errorCode = ecy_hsm_Csai_AuthEncryptStart( csaiSession->hSession, csaiSession->priority, csai_SymCipherMode,
                                               csai_paddingMode, hKey, iv,
                                               iv_len,
                                               &(csaiSession->hJob) );

    return errorCode;
}

FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Auth_Encrypt_Update
(
    VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC) csaiSession,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) aad,
    VAR(uint32, AUTOMATIC) aadLength
)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) errorCode;

    errorCode = ecy_hsm_Csai_AuthUpdate( csaiSession.hJob, aad, aadLength );

    return errorCode;
}

FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Auth_Encrypt_Finish
(
    VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC) csaiSession,
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) cipher, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) cipher_len, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) pTag, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(uint32, AUTOMATIC) tagLength
)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) errorCode;

    errorCode = ecy_hsm_Csai_AuthEncryptFinish  ( csaiSession.hJob,
                                                  cipher, *cipher_len, cipher_len,
                                                  pTag, tagLength );

    return errorCode;
}


#define CRYPTO_82_HSM_STOP_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"
