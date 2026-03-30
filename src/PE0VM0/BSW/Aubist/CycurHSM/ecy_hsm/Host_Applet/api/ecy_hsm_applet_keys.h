/**
 * @file
 ***********************************************************************************************
 * @brief Keys applet interface.
 * This header file is part of the Cryptographic Service Application Interface and specifies
 * key management functions for CycurHSM.
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2016, all rights reserved.
 **********************************************************************************************/

#ifndef ECY_HSM_APPLET_KEYS_H
#define ECY_HSM_APPLET_KEYS_H

/*
************************************************************************************************
* Includes
************************************************************************************************
*/
#include "ecy_hsm_applet.h"
#include "ecy_hsm_csai_keys.h"


/**
 * @addtogroup APPLET_IMPL
 * @{
 */
/*
************************************************************************************************
* Type definitions
************************************************************************************************
*/
/**
 * @brief Possible states for keys applet
 * @details
 * @section APPLET_KEYS Random number generation applet
 *
 * @subsection APPLET_KEYS_STATES Applet states
 *
 * @image html ./states_keys.png "State diagram of applet: keys" width=15cm
 * @image rtf  ./states_keys.png "State diagram of applet: Keys" width=15cm
 */
typedef enum ecy_hsm_Applet_Keys_StateT
{
    ecy_hsm_APPLET_KEYS_FUNC_DERIVE_KEY,                 /*!< derive keys from a parent key in the HSM */
    ecy_hsm_APPLET_KEYS_FUNC_INJECT_KEY,                 /*!< CSAI inject key or key pair into the HSM */
    ecy_hsm_APPLET_KEYS_FUNC_WRITE_KEY_TO_NVM_KEY_STORE, /*!< CSAI write key to the non-volatile keystore */
    ecy_hsm_APPLET_KEYS_FUNC_LOAD_KEY,                   /*!< CSAI load key from the secure key store and cache it in the
                                                              session context in HSM RAM */
    ecy_hsm_APPLET_KEYS_FUNC_RELEASE_KEY,                /*!< unload a key from the session context in HSM RAM */
    ecy_hsm_APPLET_KEYS_FUNC_READ_PUBLIC_KEY,            /*!< read public key or public part of the key pair */
    ecy_hsm_APPLET_KEYS_FUNC_GENERATE_KEY,               /*!< generation of a new key in the HSM */
    ecy_hsm_APPLET_KEYS_FUNC_RELEASE_KEY_FORCE,          /*!< unload a key from the HSM RAM */
    ecy_hsm_APPLET_KEYS_FUNC_DERIVE_MULTIPLE_KEYS,       /*!< derive multiple keys from a parent key in the HSM */
    ecy_hsm_APPLET_KEYS_FUNC_DERIVE_KEY_EXT,             /*!< derive keys from a parent key with generic kdf params */
    ecy_hsm_APPLET_KEYS_FUNC_GET_STORAGE_LOCATION,       /*!< return storage location of a given key ID */
    ecy_hsm_APPLET_KEYS_FUNC_ASSIGN_RAM_KEY_TO_RAM_SLOT, /*!< write key to a RAM key slot */
    ecy_hsm_APPLET_KEYS_FUNC_DERIVE_MULTIPLE_KEYS_EXT,   /*!< derive multiple keys for multiple sizes from a parent key in the HSM */
    /* This needs to be the final entry */
    ecy_hsm_APPLET_KEYS_NUMSTATES                        /*!< number of states */
} ecy_hsm_Applet_Keys_StateT;

/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by @ref ecy_hsm_Applet_Keys_StateT
 */
#define Applet_Keys_StateT ecy_hsm_Applet_Keys_StateT
/* *********** Deprecated enum definitions ***************/
/**
 * @deprecated by @ref ecy_hsm_APPLET_KEYS_FUNC_DERIVE_KEY
 */
#define APPLET_KEYS_FUNC_DERIVE_KEY ecy_hsm_APPLET_KEYS_FUNC_DERIVE_KEY
/**
 * @deprecated by @ref ecy_hsm_APPLET_KEYS_FUNC_INJECT_KEY
 */
#define APPLET_KEYS_FUNC_INJECT_KEY ecy_hsm_APPLET_KEYS_FUNC_INJECT_KEY
/**
 * @deprecated by @ref ecy_hsm_APPLET_KEYS_FUNC_WRITE_KEY_TO_NVM_KEY_STORE
 */
#define APPLET_KEYS_FUNC_WRITE_KEY_TO_NVM_KEY_STORE ecy_hsm_APPLET_KEYS_FUNC_WRITE_KEY_TO_NVM_KEY_STORE
/**
 * @deprecated by @ref ecy_hsm_APPLET_KEYS_FUNC_LOAD_KEY
 */
#define APPLET_KEYS_FUNC_LOAD_KEY ecy_hsm_APPLET_KEYS_FUNC_LOAD_KEY
/**
 * @deprecated by @ref ecy_hsm_APPLET_KEYS_FUNC_RELEASE_KEY
 */
#define APPLET_KEYS_FUNC_RELEASE_KEY ecy_hsm_APPLET_KEYS_FUNC_RELEASE_KEY
/**
 * @deprecated by @ref ecy_hsm_APPLET_KEYS_FUNC_READ_PUBLIC_KEY
 */
#define APPLET_KEYS_FUNC_READ_PUBLIC_KEY ecy_hsm_APPLET_KEYS_FUNC_READ_PUBLIC_KEY
/**
 * @deprecated by @ref ecy_hsm_APPLET_KEYS_FUNC_GENERATE_KEY
 */
#define APPLET_KEYS_FUNC_GENERATE_KEY ecy_hsm_APPLET_KEYS_FUNC_GENERATE_KEY
/**
 * @deprecated by @ref ecy_hsm_APPLET_KEYS_FUNC_RELEASE_KEY_FORCE
 */
#define APPLET_KEYS_FUNC_RELEASE_KEY_FORCE ecy_hsm_APPLET_KEYS_FUNC_RELEASE_KEY_FORCE
/**
 * @deprecated by @ref ecy_hsm_APPLET_KEYS_FUNC_DERIVE_MULTIPLE_KEYS
 */
#define APPLET_KEYS_FUNC_DERIVE_MULTIPLE_KEYS ecy_hsm_APPLET_KEYS_FUNC_DERIVE_MULTIPLE_KEYS
/**
 * @deprecated by @ref ecy_hsm_APPLET_KEYS_FUNC_DERIVE_KEY_EXT
 */
#define APPLET_KEYS_FUNC_DERIVE_KEY_EXT ecy_hsm_APPLET_KEYS_FUNC_DERIVE_KEY_EXT
/**
 * @deprecated by @ref ecy_hsm_APPLET_KEYS_FUNC_GET_STORAGE_LOCATION
 */
#define APPLET_KEYS_FUNC_GET_STORAGE_LOCATION ecy_hsm_APPLET_KEYS_FUNC_GET_STORAGE_LOCATION
/**
 * @deprecated by @ref ecy_hsm_APPLET_KEYS_FUNC_ASSIGN_RAM_KEY_TO_RAM_SLOT
 */
#define APPLET_KEYS_FUNC_ASSIGN_RAM_KEY_TO_RAM_SLOT ecy_hsm_APPLET_KEYS_FUNC_ASSIGN_RAM_KEY_TO_RAM_SLOT
/**
 * @deprecated by @ref ecy_hsm_APPLET_KEYS_NUMSTATES
 */
#define APPLET_KEYS_NUMSTATES ecy_hsm_APPLET_KEYS_NUMSTATES
/**
 * Applet context data for KEYS testing applet
 * @ingroup APPLET_CONTEXT
 */
typedef HSM_KeysParamT Applet_KeysCtx_tst;


/*
************************************************************************************************
* Extern declarations
************************************************************************************************
*/

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"


/**
 * @brief KEYS applet control structures
 */
extern const Applet_ts Applet_Keys_HSM;

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @}
 */
#endif // ECY_HSM_APPLET_KEYS_H
