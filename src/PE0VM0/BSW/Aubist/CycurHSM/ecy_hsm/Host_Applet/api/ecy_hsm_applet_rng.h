/**
 * @file
 ***********************************************************************************************
 * @brief RNG applet interface
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2014, all rights reserved.
 **********************************************************************************************/

#ifndef ECY_HSM_APPLET_RNG_H
#define ECY_HSM_APPLET_RNG_H

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
 * @brief Possible states for RNG applet
 * @details
 * @section APPLET_RNG Random number generation applet
 *
 * @subsection APPLET_RNG_STATES Applet states
 *
 * @image html ./states_rng.png "State diagram of applet: rng" width=15cm
 * @image rtf  ./states_rng.png "State diagram of applet: Rng" width=15cm
 */
typedef enum ecy_hsm_Applet_Rng_StateT
{
    ecy_hsm_APPLET_RNG_FUNC_RANDOM_GENERATE,      /**< state for function random generate */
    ecy_hsm_APPLET_RNG_FUNC_TRUE_RANDOM_GENERATE, /**< state for function true random generate */
    ecy_hsm_APPLET_RNG_FUNC_SEED_EXTEND,          /**< state for function seed extend */
    /* This needs to be the final entry */
    ecy_hsm_APPLET_RNG_NUMSTATES /**< number of states */
} ecy_hsm_Applet_Rng_StateT;

/* *********** Deprecated enum definitions ***************/
/**
 * @deprecated by ecy_hsm_APPLET_RNG_FUNC_RANDOM_GENERATE
 */
#define APPLET_RNG_FUNC_RANDOM_GENERATE      ecy_hsm_APPLET_RNG_FUNC_RANDOM_GENERATE
/**
 * @deprecated by ecy_hsm_APPLET_RNG_FUNC_TRUE_RANDOM_GENERATE
 */
#define APPLET_RNG_FUNC_TRUE_RANDOM_GENERATE ecy_hsm_APPLET_RNG_FUNC_TRUE_RANDOM_GENERATE
/**
 * @deprecated by ecy_hsm_APPLET_RNG_FUNC_SEED_EXTEND
 */
#define APPLET_RNG_FUNC_SEED_EXTEND          ecy_hsm_APPLET_RNG_FUNC_SEED_EXTEND
/**
 * @deprecated by ecy_hsm_APPLET_RNG_NUMSTATES
 */
#define APPLET_RNG_NUMSTATES                 ecy_hsm_APPLET_RNG_NUMSTATES

/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by ecy_hsm_Applet_Rng_StateT
 */
#define Applet_Rng_StateT                    ecy_hsm_Applet_Rng_StateT

/**
 * Applet context data for RNG testing applet
 * @ingroup APPLET_CONTEXT
 */
typedef HSM_RngParamT Applet_RngCtx_tst;

/*
**********************************************************************************************************************
* Extern declarations
**********************************************************************************************************************
*/

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @brief RNG applet control structures
 */
extern const Applet_ts Applet_Rng_HSM;

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @}
 */
#endif // ECY_HSM_APPLET_RNG_H
