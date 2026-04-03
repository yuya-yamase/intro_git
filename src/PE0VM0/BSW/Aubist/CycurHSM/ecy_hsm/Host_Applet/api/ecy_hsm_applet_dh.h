/**
 * @file
 ***********************************************************************************************
 * @brief Rnging applet interface
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2014, all rights reserved.
 **********************************************************************************************/

#ifndef ECY_HSM_APPLET_DH_H
#define ECY_HSM_APPLET_DH_H

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
 * @brief Possible states for ECC-DHing applet
 * @details
 * @section APPLET_DH ECC-DH functions applet
 *
 * @subsection APPLET_DH_STATES Applet states
 *
 * @image html ./states_rng.png "State diagram of applet: rng" width=15cm
 * @image rtf  ./states_rng.png "State diagram of applet: Rng" width=15cm
 */
typedef enum ecy_hsm_Applet_EccDh_StateT
{
    ecy_hsm_APPLET_DH_FUNC_PUBLIC_KEY_GENERATE,   /**!< state for function ecy_hsm_Csai_DhPublicKeyGenerate */
    ecy_hsm_APPLET_DH_FUNC_SHARED_SECRET_COMPUTE, /**!< state for function ecy_hsm_Csai_DhSharedSecretCompute */
                                          /* This needs to be the final entry */
    ecy_hsm_APPLET_DH_NUMSTATES                   /**!< number of states */
} ecy_hsm_Applet_EccDh_StateT;

/* *********** Deprecated enum definitions ***************/
/**
 * @deprecated by @ref ecy_hsm_APPLET_DH_FUNC_PUBLIC_KEY_GENERATE
 */
#define APPLET_DH_FUNC_PUBLIC_KEY_GENERATE ecy_hsm_APPLET_DH_FUNC_PUBLIC_KEY_GENERATE
/**
 * @deprecated by @ref ecy_hsm_APPLET_DH_FUNC_SHARED_SECRET_COMPUTE
 */
#define APPLET_DH_FUNC_SHARED_SECRET_COMPUTE ecy_hsm_APPLET_DH_FUNC_SHARED_SECRET_COMPUTE
/**
 * @deprecated by @ref ecy_hsm_APPLET_DH_NUMSTATES
 */
#define APPLET_DH_NUMSTATES ecy_hsm_APPLET_DH_NUMSTATES
/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by @ref ecy_hsm_Applet_EccDh_StateT
 */
#define Applet_EccDh_StateT ecy_hsm_Applet_EccDh_StateT

/**
 * Applet context data for DH testing applet
 * @ingroup APPLET_CONTEXT
 */
typedef HSM_EccDhParamT Applet_EccDhCtx_tst;

/*
**********************************************************************************************************************
* Extern declarations
**********************************************************************************************************************
*/

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @brief DH applet control structures
 */
extern const Applet_ts Applet_EccDh_HSM;

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @}
 */
#endif // ECY_HSM_APPLET_DH_H
