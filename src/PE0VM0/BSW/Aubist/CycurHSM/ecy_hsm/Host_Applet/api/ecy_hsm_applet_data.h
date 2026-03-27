/**
 * @file
 ***********************************************************************************************
 * @brief CSAI Secure Storage.
 * This header file is part of the Cryptographic Service Application Interface and specifies
 * types for reading/writing data to the HSM secure storage with CycurHSM.
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2016, all rights reserved.
 **********************************************************************************************/

#ifndef ECY_HSM_APPLET_DATA_H
#define ECY_HSM_APPLET_DATA_H
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
 * @brief Possible states for secure storage applet
 * @details
 * @section APPLET_SECURESTORAGE Secure storage applet
 *
 * @subsection APPLET_SECURESTORAGE_STATES Applet states
 *
 * @startuml
 * state "APPLET_SECURESTORAGE_WRITE" as WriteData        : write Data into EEPROM
 * state "APPLET_SECURESTORAGE_READ" as ReadData  : read Data from EEPROM
 * state "APPLET_SECURESTORAGE_DELETE" as DeleteData    : delete Data from EEPROM
 *
 * [*] --> WriteData
 * WriteData --> [*]
 *
 * [*] --> ReadData
 * ReadData --> [*]
 *
 * [*] --> DeleteData
 * DeleteData --> [*]
 *
 * @enduml
 */
typedef enum ecy_hsm_Applet_SecureStorage_StateT
{
    ecy_hsm_APPLET_SECURESTORAGE_WRITE,                       /**< state for write data */
    ecy_hsm_APPLET_SECURESTORAGE_READ,                        /**< state for read data */
    ecy_hsm_APPLET_SECURESTORAGE_DELETE,                      /**< state for delete data */
    ecy_hsm_APPLET_SECURESTORAGE_RELEASE,                     /**< state for release data from RAM */
    /* This needs to be the final entry */
    ecy_hsm_APPLET_SECURESTORAGE_NUMSTATES    /**< number of states */
} ecy_hsm_Applet_SecureStorage_StateT;

/* *********** Deprecated enum definitions ***************/
/**
 * @deprecated by @ref ecy_hsm_APPLET_SECURESTORAGE_WRITE
 */
#define APPLET_SECURESTORAGE_WRITE ecy_hsm_APPLET_SECURESTORAGE_WRITE
/**
 * @deprecated by @ref ecy_hsm_APPLET_SECURESTORAGE_READ
 */
#define APPLET_SECURESTORAGE_READ ecy_hsm_APPLET_SECURESTORAGE_READ
/**
 * @deprecated by @ref ecy_hsm_APPLET_SECURESTORAGE_DELETE
 */
#define APPLET_SECURESTORAGE_DELETE ecy_hsm_APPLET_SECURESTORAGE_DELETE
/**
 * @deprecated by @ref ecy_hsm_APPLET_SECURESTORAGE_RELEASE
 */
#define APPLET_SECURESTORAGE_RELEASE ecy_hsm_APPLET_SECURESTORAGE_RELEASE
/**
 * @deprecated by @ref ecy_hsm_APPLET_SECURESTORAGE_NUMSTATES
 */
#define APPLET_SECURESTORAGE_NUMSTATES ecy_hsm_APPLET_SECURESTORAGE_NUMSTATES
/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by @ref ecy_hsm_Applet_SecureStorage_StateT
 */
#define Applet_SecureStorage_StateT ecy_hsm_Applet_SecureStorage_StateT
/**
 * Applet context data for HASH testing applet
 * @ingroup APPLET_CONTEXT
 */
typedef HSM_SecureStorageParamT Applet_SecureStorageCtx_tst;

/*
**********************************************************************************************************************
* Extern declarations
**********************************************************************************************************************
*/

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @brief secure storage applet control structures
 */
extern const Applet_ts Applet_SecureStorage_HSM;

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @}
 */
#endif /* ECY_HSM_APPLET_DATA_H */
