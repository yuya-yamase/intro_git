/**
 * @file
 ***********************************************************************************************
 * @brief Hashing applet interface
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2014, all rights reserved.
 **********************************************************************************************/

#ifndef ECY_HSM_APPLET_HASH_H
#define ECY_HSM_APPLET_HASH_H

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
 * @brief Possible states for hashing applet
 * @details
 * @section APPLET_HASH Hashing applet
 *
 * @subsection APPLET_HASH_STATES Applet states
 *
 * @image html ./states_hash.png "State diagram of applet: hash" width=15cm
 * @image rtf  ./states_hash.png "State diagram of applet: Hash" width=15cm
 */
typedef enum ecy_hsm_Applet_Hash_StateT
{
    ecy_hsm_APPLET_HASH_STATE_INIT,  /**< state for hash init */
    ecy_hsm_APPLET_HASH_STATE_UPDATE,/**< state for hash update */
    ecy_hsm_APPLET_HASH_STATE_FINAL, /**< state for hash final */
    ecy_hsm_APPLET_HASH_STATE_FULL,  /**< state for full hashing */
    /* This needs to be the final entry */
    ecy_hsm_APPLET_HASH_NUMSTATES    /**< number of states */
} ecy_hsm_Applet_Hash_StateT;

/* *********** Deprecated enum definitions ***************/
/**
 * @deprecated by @ref ecy_hsm_APPLET_HASH_STATE_INIT
 */
#define APPLET_HASH_STATE_INIT ecy_hsm_APPLET_HASH_STATE_INIT
/**
 * @deprecated by @ref ecy_hsm_APPLET_HASH_STATE_UPDATE
 */
#define APPLET_HASH_STATE_UPDATE ecy_hsm_APPLET_HASH_STATE_UPDATE
/**
 * @deprecated by @ref ecy_hsm_APPLET_HASH_STATE_FINAL
 */
#define APPLET_HASH_STATE_FINAL ecy_hsm_APPLET_HASH_STATE_FINAL
/**
 * @deprecated by @ref ecy_hsm_APPLET_HASH_STATE_FULL
 */
#define APPLET_HASH_STATE_FULL ecy_hsm_APPLET_HASH_STATE_FULL
/**
 * @deprecated by @ref ecy_hsm_APPLET_HASH_NUMSTATES
 */
#define APPLET_HASH_NUMSTATES ecy_hsm_APPLET_HASH_NUMSTATES
/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by @ref ecy_hsm_Applet_Hash_StateT
 */
#define Applet_Hash_StateT ecy_hsm_Applet_Hash_StateT

/**
 * Applet context data for HASH testing applet
 * @ingroup APPLET_CONTEXT
 */
typedef HSM_HashParamT Applet_HashCtx_tst;

/*
**********************************************************************************************************************
* Extern declarations
**********************************************************************************************************************
*/
/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @brief HASH applet control structures
 */
extern const Applet_ts Applet_Hash_HSM;

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @}
 */
#endif /* ECY_HSM_APPLET_HASH_H */
