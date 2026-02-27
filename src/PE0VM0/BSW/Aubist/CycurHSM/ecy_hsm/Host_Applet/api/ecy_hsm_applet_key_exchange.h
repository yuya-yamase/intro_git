/**
 * @file ecy_hsm_applet_key_exchange.h
 ***********************************************************************************************
 * @brief Header file for the key exchange applet
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2019, all rights reserved.
 **********************************************************************************************/

#ifndef ECY_HSM_APPLET_KEY_EXCHANGE_H
#define ECY_HSM_APPLET_KEY_EXCHANGE_H

/*
**********************************************************************************************************************
* Includes
**********************************************************************************************************************
*/
#include "ecy_hsm_applet.h"
#include "ecy_hsm_service_key_exchange.h"

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
 * @brief Possible states for key exchange applet
 * @details
 * @section APPLET_KEY_EXCHANGE key exchange functions applet
 *
 * @subsection APPLET_KEY_EXCHANGE_STATES Applet states
 *
 */
typedef enum ecy_hsm_Applet_KeyExchange_StateT
{
    ecy_hsm_APPLET_KEY_EXCHANGE_FUNC_DH_INIT,         /**!< state for function ecy_hsm_Csai_DhInit */
    ecy_hsm_APPLET_KEY_EXCHANGE_FUNC_DH_COMPUTE_EXT,  /**!< state for function ecy_hsm_Csai_DhComputeExt */
    ecy_hsm_APPLET_KEY_EXCHANGE_FUNC_DH_COMPUTE_INT,  /**!< state for function ecy_hsm_Csai_DhComputeInt */
    ecy_hsm_APPLET_KEY_EXCHANGE_FUNC_ECBD_INIT,       /**!< state for function ecy_hsm_Csai_EcbdInit */
    ecy_hsm_APPLET_KEY_EXCHANGE_FUNC_ECBD_2ND_PUBKEY, /**!< state for function ecy_hsm_Csai_EcbdCompute2ndPubKey */
    ecy_hsm_APPLET_KEY_EXCHANGE_FUNC_ECBD_UPDATE,     /**!< state for function ecy_hsm_Csai_EcbdUpdate */
    ecy_hsm_APPLET_KEY_EXCHANGE_FUNC_ECBD_FINISH,     /**!< state for function ecy_hsm_Csai_EcbdFinish */

    /* This needs to be the final entry */
    ecy_hsm_APPLET_KEY_EXCHANGE_NUMSTATES /**!< number of states */
} ecy_hsm_Applet_KeyExchange_StateT;

/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by @ref ecy_hsm_Applet_KeyExchange_StateT
 */
#define Applet_KeyExchange_StateT                ecy_hsm_Applet_KeyExchange_StateT
/* *********** Deprecated enum definitions ***************/
/**
 * @deprecated by @ref ecy_hsm_APPLET_KEY_EXCHANGE_FUNC_DH_INIT
 */
#define APPLET_KEY_EXCHANGE_FUNC_DH_INIT         ecy_hsm_APPLET_KEY_EXCHANGE_FUNC_DH_INIT
/**
 * @deprecated by @ref ecy_hsm_APPLET_KEY_EXCHANGE_FUNC_DH_COMPUTE_EXT
 */
#define APPLET_KEY_EXCHANGE_FUNC_DH_COMPUTE_EXT  ecy_hsm_APPLET_KEY_EXCHANGE_FUNC_DH_COMPUTE_EXT
/**
 * @deprecated by @ref ecy_hsm_APPLET_KEY_EXCHANGE_FUNC_DH_COMPUTE_INT
 */
#define APPLET_KEY_EXCHANGE_FUNC_DH_COMPUTE_INT  ecy_hsm_APPLET_KEY_EXCHANGE_FUNC_DH_COMPUTE_INT
/**
 * @deprecated by @ref ecy_hsm_APPLET_KEY_EXCHANGE_FUNC_ECBD_INIT
 */
#define APPLET_KEY_EXCHANGE_FUNC_ECBD_INIT       ecy_hsm_APPLET_KEY_EXCHANGE_FUNC_ECBD_INIT
/**
 * @deprecated by @ref ecy_hsm_APPLET_KEY_EXCHANGE_FUNC_ECBD_2ND_PUBKEY
 */
#define APPLET_KEY_EXCHANGE_FUNC_ECBD_2ND_PUBKEY ecy_hsm_APPLET_KEY_EXCHANGE_FUNC_ECBD_2ND_PUBKEY
/**
 * @deprecated by @ref ecy_hsm_APPLET_KEY_EXCHANGE_FUNC_ECBD_UPDATE
 */
#define APPLET_KEY_EXCHANGE_FUNC_ECBD_UPDATE     ecy_hsm_APPLET_KEY_EXCHANGE_FUNC_ECBD_UPDATE
/**
 * @deprecated by @ref ecy_hsm_APPLET_KEY_EXCHANGE_FUNC_ECBD_FINISH
 */
#define APPLET_KEY_EXCHANGE_FUNC_ECBD_FINISH     ecy_hsm_APPLET_KEY_EXCHANGE_FUNC_ECBD_FINISH
/**
 * @deprecated by @ref ecy_hsm_APPLET_KEY_EXCHANGE_NUMSTATES
 */
#define APPLET_KEY_EXCHANGE_NUMSTATES            ecy_hsm_APPLET_KEY_EXCHANGE_NUMSTATES

/**
 * Applet context data for key exchange testing applet
 * @ingroup APPLET_CONTEXT
 */
typedef HSM_KeyExchangeParamT Applet_KeyExchangeCtx_tst;

/*
**********************************************************************************************************************
* Extern declarations
**********************************************************************************************************************
*/

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @brief Key exchange applet control structures
 */
extern const Applet_ts Applet_KeyExchange_HSM;

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @}
 */
#endif /* ECY_HSM_APPLET_KEY_EXCHANGE_H */
