/**
 * @file
 ***********************************************************************************************
 * @brief SHE key implementation file
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
#include "ecy_hsm_she_host_private.h"
#include "ecy_hsm_proxy.h"

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* PRQA S 1503 1 */ /* Deviation: rule_2.1 */ /* Justification: As this is a library interface, appearing unused is acceptable. */
SHE_ErrorCodeT SHE_LoadKey(const uint8 m1[SHE_M1_BLOCK_SIZE_BYTES],
                           const uint8 m2[SHE_M2_BLOCK_SIZE_BYTES],
                           const uint8 m3[SHE_M3_BLOCK_SIZE_BYTES],
                           uint8       m4[SHE_M4_BLOCK_SIZE_BYTES],
                           uint8       m5[SHE_M5_BLOCK_SIZE_BYTES])
{
    /* PRQA S 0750,0759 1 */ /* Justification: Use of union provides polymorphism of SHE parameters and reuse of a single API. */
    HSM_SheParamT paramBlock;

    /* PRQA S 4404 1 */ /* <Deviation: rule_10.3_4404_10.5_4304_boolean */
    paramBlock.SHE_LoadKeyToBankParam.csaiErrors = FALSE;
    paramBlock.SHE_LoadKeyToBankParam.m1         = m1;
    paramBlock.SHE_LoadKeyToBankParam.m2         = m2;
    paramBlock.SHE_LoadKeyToBankParam.m3         = m3;
    paramBlock.SHE_LoadKeyToBankParam.m4         = m4;
    paramBlock.SHE_LoadKeyToBankParam.m5         = m5;
    paramBlock.SHE_LoadKeyToBankParam.bankIndex  = 0xFF;

    /* HSM Applet Request */
    return (SHE_LoadApplet( APPLET_SHE_FUNC_LOAD_KEY, sizeof(paramBlock), &paramBlock ));
}

/* PRQA S 1503 1 */ /* Deviation: rule_2.1 */ /* Justification: As this is a library interface, appearing unused is acceptable. */
SHE_ErrorCodeT SHE_LoadKeyExtended(const uint8 m1[SHE_M1_BLOCK_SIZE_BYTES],
                                   const uint8 m2[SHE_M2_BLOCK_SIZE_BYTES],
                                   const uint8 m3[SHE_M3_BLOCK_SIZE_BYTES],
                                   uint8       m4[SHE_M4_BLOCK_SIZE_BYTES],
                                   uint8       m5[SHE_M5_BLOCK_SIZE_BYTES])
{
    /* PRQA S 0750,0759 1 */ /* Justification: Use of union provides polymorphism of SHE parameters and reuse of a single API. */
    HSM_SheParamT paramBlock;

    /* PRQA S 4404 1 */ /* <Deviation: rule_10.3_4404_10.5_4304_boolean */
    paramBlock.SHE_LoadKeyToBankParam.csaiErrors = FALSE;
    paramBlock.SHE_LoadKeyToBankParam.m1         = m1;
    paramBlock.SHE_LoadKeyToBankParam.m2         = m2;
    paramBlock.SHE_LoadKeyToBankParam.m3         = m3;
    paramBlock.SHE_LoadKeyToBankParam.m4         = m4;
    paramBlock.SHE_LoadKeyToBankParam.m5         = m5;
    paramBlock.SHE_LoadKeyToBankParam.bankIndex  = 0xFF;

    /* HSM Job Request */
    return SHE_LoadApplet( APPLET_SHE_FUNC_LOAD_KEY_EXTENDED, sizeof(paramBlock), &paramBlock );
}

/* PRQA S 1503 1 */ /* Deviation: rule_2.1 */ /* Justification: As this is a library interface, appearing unused is acceptable. */
SHE_ErrorCodeT SHE_LoadKeyToBank(const uint8 m1[SHE_M1_BLOCK_SIZE_BYTES],
                                 const uint8 m2[SHE_M2_BLOCK_SIZE_BYTES],
                                 const uint8 m3[SHE_M3_BLOCK_SIZE_BYTES],
                                 uint8       m4[SHE_M4_BLOCK_SIZE_BYTES],
                                 uint8       m5[SHE_M5_BLOCK_SIZE_BYTES],
                                 uint32      bankIndex)
{
    /* PRQA S 0750,0759 1 */ /* Justification: Use of union provides polymorphism of SHE parameters and reuse of a single API. */
    HSM_SheParamT paramBlock;

    /* PRQA S 4404 1 */ /* <Deviation: rule_10.3_4404_10.5_4304_boolean */
    paramBlock.SHE_LoadKeyToBankParam.csaiErrors = FALSE;
    paramBlock.SHE_LoadKeyToBankParam.m1         = m1;
    paramBlock.SHE_LoadKeyToBankParam.m2         = m2;
    paramBlock.SHE_LoadKeyToBankParam.m3         = m3;
    paramBlock.SHE_LoadKeyToBankParam.m4         = m4;
    paramBlock.SHE_LoadKeyToBankParam.m5         = m5;
    paramBlock.SHE_LoadKeyToBankParam.bankIndex  = bankIndex;

    /* HSM Job Request */
    return SHE_LoadApplet( APPLET_SHE_FUNC_LOAD_KEY_TO_BANK, sizeof(paramBlock), &paramBlock );
}

/* PRQA S 1503 1 */ /* Deviation: rule_2.1 */ /* Justification: As this is a library interface, appearing unused is acceptable. */
SHE_ErrorCodeT SHE_LoadPlainKey(const uint8 key[SHE_AES_BLOCK_SIZE_BYTES])
{
    /* PRQA S 0750,0759 1 */ /* Justification: Use of union provides polymorphism of SHE parameters and reuse of a single API. */
    HSM_SheParamT paramBlock;

    /* PRQA S 4404 1 */ /* <Deviation: rule_10.3_4404_10.5_4304_boolean */
    paramBlock.SHE_LoadPlainKeyParam.csaiErrors = FALSE;
    paramBlock.SHE_LoadPlainKeyParam.key        = key;

    /* HSM Applet Request */
    return SHE_LoadApplet( APPLET_SHE_FUNC_LOAD_PLAIN_KEY, sizeof(paramBlock), &paramBlock );
}

/* PRQA S 1503 1 */ /* Deviation: rule_2.1 */ /* Justification: As this is a library interface, appearing unused is acceptable. */
SHE_ErrorCodeT SHE_ExportRAMKey(uint8 m1[SHE_M1_BLOCK_SIZE_BYTES],
                                uint8 m2[SHE_M2_BLOCK_SIZE_BYTES],
                                uint8 m3[SHE_M3_BLOCK_SIZE_BYTES],
                                uint8 m4[SHE_M4_BLOCK_SIZE_BYTES],
                                uint8 m5[SHE_M5_BLOCK_SIZE_BYTES])
{
    /* PRQA S 0750,0759 1 */ /* Justification: Use of union provides polymorphism of SHE parameters and reuse of a single API. */
    HSM_SheParamT paramBlock;

    /* PRQA S 4404 1 */ /* <Deviation: rule_10.3_4404_10.5_4304_boolean */
    paramBlock.SHE_ExportRamKeyParam.csaiErrors = FALSE;
    paramBlock.SHE_ExportRamKeyParam.m1         = m1;
    paramBlock.SHE_ExportRamKeyParam.m2         = m2;
    paramBlock.SHE_ExportRamKeyParam.m3         = m3;
    paramBlock.SHE_ExportRamKeyParam.m4         = m4;
    paramBlock.SHE_ExportRamKeyParam.m5         = m5;

    /* HSM Applet Request */
    return SHE_LoadApplet( APPLET_SHE_FUNC_EXPORT_RAM_KEY, sizeof(paramBlock), &paramBlock );
}

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"
