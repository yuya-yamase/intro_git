/**
 * @file
 ***********************************************************************************************
 * @brief CSAI Random number generation.
 * This header file is part of the Cryptographic Service Application Interface and specifies
 * types and functions for generating random numbers with CycurHSM.
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2014, all rights reserved.
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_SERVICE_RNG_H
#define ECY_HSM_SERVICE_RNG_H

/**
 * @addtogroup GROUP_CSAI_RNG
 * @{
 */

/* *** includes *******************************************************************************/

#include "ecy_hsm_csai_rng.h"
/* *** defines ********************************************************************************/

/* *** type declarations **********************************************************************/

/* *** global constants ***********************************************************************/

/* *** exported interfaces ********************************************************************/

/** Structure for the data passed to pseudo-random number generator   */
typedef struct ecy_hsm_RandomGenerateParamTag
{
    uint8* random; /**< Pointer to buffer to receive the random number data */
    uint32 length; /**< Length of buffer to receive the random number data */
} ecy_hsm_RandomGenerateParamT;

/** Structure for the data passed to true-random number generator   */
typedef struct ecy_hsm_TrueRandomGenerateParamTag
{
    uint8* random; /**< Pointer to buffer to receive the random number data */
    uint32 length; /**< Length of buffer to receive the random number data */
} ecy_hsm_TrueRandomGenerateParamT;

/** Structure for the data to explicitly trigger a re-seed of the PRNG in the HSM  */
typedef struct ecy_hsm_RandomSeedExtendParamTag
{
    const uint8* seed;   /**< Data to be compressed with true random data to form the seed */
    uint32       length; /**< Length of data to be compressed */
} ecy_hsm_RandomSeedExtendParamT;

/** Structure for the data passed to RNG applet */
/* PRQA S 0750 2 */ /* <Deviation: definition of union is appropriate here */
typedef union ecy_hsm_RngParamT
{
    ecy_hsm_RandomGenerateParamT     randomGenerateParam;     /**< Parameter structure for pseudo-random number generation */
    ecy_hsm_TrueRandomGenerateParamT trueRandomGenerateParam; /**< Parameter structure for true-random number generation */
    ecy_hsm_RandomSeedExtendParamT   randomSeedExtendParam;   /**< Parameter structure for explicit trigger of a re-seed of the PRNG in the HSM */
} ecy_hsm_RngParamT;

/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by ecy_hsm_RandomGenerateParamTag
 */
#define HSM_RandomGenerateParamTag     ecy_hsm_RandomGenerateParamTag
/**
 * @deprecated by ecy_hsm_RandomGenerateParamT
 */
#define HSM_RandomGenerateParamT       ecy_hsm_RandomGenerateParamT
/**
 * @deprecated by ecy_hsm_TrueRandomGenerateParamTag
 */
#define HSM_TrueRandomGenerateParamTag ecy_hsm_TrueRandomGenerateParamTag
/**
 * @deprecated by ecy_hsm_TrueRandomGenerateParamT
 */
#define HSM_TrueRandomGenerateParamT   ecy_hsm_TrueRandomGenerateParamT
/**
 * @deprecated by ecy_hsm_RandomSeedExtendParamTag
 */
#define HSM_RandomSeedExtendParamTag   ecy_hsm_RandomSeedExtendParamTag
/**
 * @deprecated by ecy_hsm_RandomSeedExtendParamT
 */
#define HSM_RandomSeedExtendParamT     ecy_hsm_RandomSeedExtendParamT
/**
 * @deprecated by ecy_hsm_RngParamT
 */
#define HSM_RngParamT                  ecy_hsm_RngParamT
/**
 * @}
 */

#endif /* Multiple inclusion lock  */
