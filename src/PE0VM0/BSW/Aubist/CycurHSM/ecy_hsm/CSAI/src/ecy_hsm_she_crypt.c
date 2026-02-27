/**
 * @file
 ***********************************************************************************************
 * @brief SHE Encryption and Decryption implementation file
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2014, all rights reserved
 **********************************************************************************************/
#if defined(GUAM)
#include "ecy_hsm_general.h"
#else
#include "ecy_hsm_general_pubcfg.h"
#endif
#include "ecy_hsm_she.h"
#include "ecy_hsm_proxy.h"
#include "ecy_hsm_she_host_private.h"

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_SHE */
SHE_ErrorCodeT SHE_EncryptEcb(SHE_KeyIdT  keyId,
                              const uint8 pPlainText[SHE_AES_BLOCK_SIZE_BYTES],
                              uint32      plainTextLength,
                              uint8       pCipherText[SHE_AES_BLOCK_SIZE_BYTES],
                              uint32      cipherTextSize)
{
    /* PRQA S 0759 1 */ /* <Deviation: defintion of union is appropriate here */
    HSM_SheParamT paramBlock;

    /* PRQA S 2983 5 */ /* Deviation: rule_2.2_2983 */
    paramBlock.SHE_EncryptEcbParam.keySlotId       = keyId;
    paramBlock.SHE_EncryptEcbParam.plainText       = pPlainText;
    paramBlock.SHE_EncryptEcbParam.plainTextLength = plainTextLength;
    paramBlock.SHE_EncryptEcbParam.cipherText      = pCipherText;
    paramBlock.SHE_EncryptEcbParam.cipherTextSize  = cipherTextSize;

    /* HSM Applet Request */
    return SHE_LoadApplet( APPLET_SHE_FUNC_ENCRYPT_ECB, sizeof(paramBlock), &paramBlock );

}

/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_SHE */
SHE_ErrorCodeT SHE_DecryptEcb(SHE_KeyIdT keyId,
                              const uint8 cipherText[SHE_AES_BLOCK_SIZE_BYTES],
                              uint32 cipherTextLength,
                              uint8 plainText[SHE_AES_BLOCK_SIZE_BYTES],
                              uint32 plainTextSize)
{
    /* PRQA S 0759 1 */ /* <Deviation: defintion of union is appropriate here */
    HSM_SheParamT paramBlock;

    /* PRQA S 2983 5 */ /* Deviation: rule_2.2_2983 */
    paramBlock.SHE_DecryptEcbParam.keySlotId        = keyId;
    paramBlock.SHE_DecryptEcbParam.cipherText       = cipherText;
    paramBlock.SHE_DecryptEcbParam.cipherTextLength = cipherTextLength;
    paramBlock.SHE_DecryptEcbParam.plainText        = plainText;
    paramBlock.SHE_DecryptEcbParam.plainTextSize    = plainTextSize;

    /* HSM Applet Request */
    return SHE_LoadApplet( APPLET_SHE_FUNC_DECRYPT_ECB, sizeof(paramBlock), &paramBlock );
}

/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_SHE */
SHE_ErrorCodeT SHE_EncryptCbc(SHE_KeyIdT keyId,
                              const uint8 iv[SHE_AES_BLOCK_SIZE_BYTES],
                              const uint8* plainText,
                              uint32 plainTextLength,
                              uint8* cipherText,
                              uint32 cipherTextSize)
{
    /* PRQA S 0759 1 */ /* <Deviation: defintion of union is appropriate here */
    HSM_SheParamT paramBlock;

    /* PRQA S 2983 6 */ /* Deviation: rule_2.2_2983 */
    paramBlock.SHE_EncryptCbcParam.keySlotId       = keyId;
    paramBlock.SHE_EncryptCbcParam.iv              = iv;
    paramBlock.SHE_EncryptCbcParam.plainText       = plainText;
    paramBlock.SHE_EncryptCbcParam.plainTextLength = plainTextLength;
    paramBlock.SHE_EncryptCbcParam.cipherText      = cipherText;
    paramBlock.SHE_EncryptCbcParam.cipherTextSize  = cipherTextSize;

    /* HSM Applet Request */
    return SHE_LoadApplet( APPLET_SHE_FUNC_ENCRYPT_CBC, sizeof(paramBlock), &paramBlock );
}

/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_SHE */
SHE_ErrorCodeT SHE_DecryptCbc(SHE_KeyIdT keyId,
                              const uint8 iv[SHE_AES_BLOCK_SIZE_BYTES],
                              const uint8* cipherText,
                              uint32 cipherTextLength,
                              uint8* plainText,
                              uint32 plainTextSize)
{
    /* PRQA S 0759 1 */ /* <Deviation: defintion of union is appropriate here */
    HSM_SheParamT paramBlock;

    /* PRQA S 2983 6 */ /* Deviation: rule_2.2_2983 */
    paramBlock.SHE_DecryptCbcParam.keySlotId        = keyId;
    paramBlock.SHE_DecryptCbcParam.iv               = iv;
    paramBlock.SHE_DecryptCbcParam.cipherText       = cipherText;
    paramBlock.SHE_DecryptCbcParam.cipherTextLength = cipherTextLength;
    paramBlock.SHE_DecryptCbcParam.plainText        = plainText;
    paramBlock.SHE_DecryptCbcParam.plainTextSize    = plainTextSize;

    /* HSM Applet Request */
    return SHE_LoadApplet( APPLET_SHE_FUNC_DECRYPT_CBC, sizeof(paramBlock), &paramBlock );
}

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"
