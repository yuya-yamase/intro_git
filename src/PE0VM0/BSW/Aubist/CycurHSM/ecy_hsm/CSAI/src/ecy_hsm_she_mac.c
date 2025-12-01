/**
 * @file
 ***********************************************************************************************
 * @brief SHE Message Authenticated Code implementation file
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2014, all rights reserved
 **********************************************************************************************/

#if defined(GUAM)
# include "ecy_hsm_general.h"
#else
# include "ecy_hsm_general_pubcfg.h"
#endif
#include "ecy_hsm_general_host_cfg.h"
#include "ecy_hsm_proxy.h"
#include "ecy_hsm_she.h"
#include "ecy_hsm_she_host_private.h"

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_SHE */
SHE_ErrorCodeT SHE_GenerateMAC(SHE_KeyIdT keyId, const uint8* msg, uint32 msgLength, uint8 mac[SHE_AES_BLOCK_SIZE_BYTES])
{
    /* PRQA S 2981 2 */ /* <Justification: Initialization avoids compiler warning with Tasking compiler.
     For HT and GHS this is reported as redundant by QAC */
    SHE_ErrorCodeT sheErrorCode = ERC_NO_ERROR;

#if (ecy_hsm_QUICK_ROUTE == ENABLED)
    ecy_hsm_Csai_ErrorT csaiErrorCode = ecy_hsm_CSAI_ERR_QUICK_ROUTE_NOT_POSSIBLE;

    /* If we can't do a Quick CMAC, or it fails, then we'll do a normal SHE MAC Generate (remember that msgLength is
     in bits!) */
    if (msgLength <= (SHE_MAX_QUICK_ROUTE_BYTES * 8U))
    {
        /* PRQA S 0759 1 */ /* <Deviation: defintion of union is appropriate here */
        HSM_SheParamT paramBlock;

        /* Parameter update */
        /* PRQA S 2983 4 */ /* Deviation: rule_2.2_2983 */
        paramBlock.SHE_MACGenerateParam.keySlotId = keyId;
        paramBlock.SHE_MACGenerateParam.msg       = msg;
        paramBlock.SHE_MACGenerateParam.msgLength = msgLength;
        paramBlock.SHE_MACGenerateParam.mac       = mac;

        csaiErrorCode = SHE_QuickRoute(HSM_FUNC_SHE_MAC_GENERATE, sizeof(paramBlock), &paramBlock);
        // extract corresponding SHE error code from CSAI error code

        /* PRQA S 4342, 4394 4 */ /* Deviation: rule_10.8_4394_she */ /* Justification: Since csaiErrorCode is uint32,
                                                                       * no adverse behaviour expected in type cast. Casted values are expected to
                                                                       * fall within enumeration constants, otherwise clear & graceful SHE test
                                                                       * failures would be expected. */
        sheErrorCode = ecy_hsm_CSAI_EXTRACT_SHE_ERROR_CODE(csaiErrorCode);
    }
    /* If the Quick CMAC request failed (e.g. because the AES hardware was busy, or the key was not loaded), then we go
     by the normal route */
    if (ecy_hsm_CSAI_ERR_QUICK_ROUTE_NOT_POSSIBLE == csaiErrorCode)
#endif
    {
        /* PRQA S 0759 1 */ /* <Deviation: defintion of union is appropriate here */
        HSM_SheParamT paramBlock;

        /* PRQA S 2983 4 */ /* Deviation: rule_2.2_2983 */
        paramBlock.SHE_MACGenerateParam.keySlotId = keyId;
        paramBlock.SHE_MACGenerateParam.msg       = msg;
        paramBlock.SHE_MACGenerateParam.msgLength = msgLength;
        paramBlock.SHE_MACGenerateParam.mac       = mac;

        sheErrorCode = SHE_LoadApplet(APPLET_SHE_FUNC_MAC_GENERATE, sizeof(paramBlock), &paramBlock);
    }
    return sheErrorCode;
}

/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_SHE */
SHE_ErrorCodeT SHE_VerifyMAC(SHE_KeyIdT   keyId,
                             const uint8* msg,
                             uint32       msgLength,
                             const uint8  mac[SHE_AES_BLOCK_SIZE_BYTES],
                             uint32       macLength,
                             uint32*      pVerificationStatus)
{
    /* PRQA S 2981 2 */ /* <Justification: Initialization avoids compiler warning with Tasking compiler.
     For HT and GHS this is reported as redundant by QAC */
    SHE_ErrorCodeT sheErrorCode = ERC_NO_ERROR;

#if (ecy_hsm_QUICK_ROUTE == ENABLED)
    ecy_hsm_Csai_ErrorT csaiErrorCode = ecy_hsm_CSAI_ERR_QUICK_ROUTE_NOT_POSSIBLE;

    /* If we can't do a Quick CMAC, or it fails, then we'll do a normal SHE MAC Verify
     (remember that msgLength is in bits!) */
    if (msgLength <= (SHE_MAX_QUICK_ROUTE_BYTES * 8U))
    {
        /* PRQA S 0759 1 */ /* <Deviation: defintion of union is appropriate here */
        HSM_SheParamT paramBlock;

        /* Parameter update */
        /* PRQA S 2983 6 */ /* Deviation: rule_2.2_2983 */
        paramBlock.SHE_MACVerifyParam.keySlotId           = keyId;
        paramBlock.SHE_MACVerifyParam.msg                 = msg;
        paramBlock.SHE_MACVerifyParam.msgLength           = msgLength;
        paramBlock.SHE_MACVerifyParam.mac                 = mac;
        paramBlock.SHE_MACVerifyParam.macLength           = macLength;
        paramBlock.SHE_MACVerifyParam.pVerificationStatus = pVerificationStatus;

        csaiErrorCode = SHE_QuickRoute(HSM_FUNC_SHE_MAC_VERIFY, sizeof(paramBlock), &paramBlock);
        // extract corresponding SHE error code from CSAI error code

        /* PRQA S 4342, 4394 4 */ /* Deviation: rule_10.8_4394_she */ /* Justification: Since csaiError is uint32,
                                                                       * no adverse behaviour expected in type cast. Casted values are expected to
                                                                       * fall within enumeration constants, otherwise clear & graceful SHE test
                                                                       * failures would be expected. */
        sheErrorCode = ecy_hsm_CSAI_EXTRACT_SHE_ERROR_CODE(csaiErrorCode);
    }
    /* If the Quick CMAC request failed (e.g. because the AES hardware was busy, or the key was not loaded),
     then we go by the normal route */
    if (ecy_hsm_CSAI_ERR_QUICK_ROUTE_NOT_POSSIBLE == csaiErrorCode)
#endif
    {
        /* PRQA S 0759 1 */ /* <Deviation: defintion of union is appropriate here */
        HSM_SheParamT paramBlock;

        /* PRQA S 2983 6 */ /* Deviation: rule_2.2_2983 */
        paramBlock.SHE_MACVerifyParam.keySlotId           = keyId;
        paramBlock.SHE_MACVerifyParam.msg                 = msg;
        paramBlock.SHE_MACVerifyParam.msgLength           = msgLength;
        paramBlock.SHE_MACVerifyParam.mac                 = mac;
        paramBlock.SHE_MACVerifyParam.macLength           = macLength;
        paramBlock.SHE_MACVerifyParam.pVerificationStatus = pVerificationStatus;

        sheErrorCode = SHE_LoadApplet(APPLET_SHE_FUNC_MAC_VERIFY, sizeof(paramBlock), &paramBlock);
    }
    return sheErrorCode;
}

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"
