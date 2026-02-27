/**
 * @file
 ***********************************************************************************************
 * @brief SHE random number implementation file
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

/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_SHE */
SHE_ErrorCodeT SHE_InitRNG(void)
{
    /* PRQA S 0759 1 */ /* <Deviation: defintion of union is appropriate here */
    HSM_SheParamT paramBlock;

    /* HSM Applet Request */
    return SHE_LoadApplet( APPLET_SHE_FUNC_INIT_RNG, sizeof(paramBlock), &paramBlock );
}

/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_SHE */
SHE_ErrorCodeT SHE_ExtendSeed(const uint8 entropy[SHE_AES_BLOCK_SIZE_BYTES])
{
    /* PRQA S 0759 1 */ /* <Deviation: defintion of union is appropriate here */
    HSM_SheParamT paramBlock;

    paramBlock.SHE_ExtendSeedParam.entropy = entropy;

    /* HSM Applet Request */
    return SHE_LoadApplet( APPLET_SHE_FUNC_EXTEND_SEED, sizeof(paramBlock), &paramBlock );
}

/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_SHE */
SHE_ErrorCodeT SHE_Rnd(uint8 buffer[SHE_AES_BLOCK_SIZE_BYTES])
{
    /* PRQA S 0759 1 */ /* <Deviation: defintion of union is appropriate here */
    HSM_SheParamT paramBlock;

    paramBlock.SHE_RndParam.rnd = buffer;

    /* HSM Applet Request */
    return (SHE_LoadApplet( APPLET_SHE_FUNC_RND, sizeof(paramBlock), &paramBlock ));
}

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"
