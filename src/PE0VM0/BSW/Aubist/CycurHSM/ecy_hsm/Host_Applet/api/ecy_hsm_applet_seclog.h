/**
 * @file
 ***********************************************************************************************
 * @brief CSAI Secure Logging.
 * This header file is part of the Cryptographic Service Application Interface and specifies
 * types for interacting with the HSM secure logging.
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2019, all rights reserved.
 **********************************************************************************************/

#ifndef ECY_HSM_APPLET_SECLOG_H
#define ECY_HSM_APPLET_SECLOG_H
/*
**********************************************************************************************************************
* Includes
**********************************************************************************************************************
*/

#include "ecy_hsm_applet.h"
#include "ecy_hsm_service_seclog.h"

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
 * @brief Possible states for secure logging applet
 * @details
 * @section APPLET_SECLOG Secure logging applet
 *
 * @subsection APPLET_SECLOG_STATES Applet states
 *
 * @startuml
 * state "ecy_hsm_APPLET_SECLOG_CFG" as ConfigLog                       : Configure SecLog context data buffer
 * state "ecy_hsm_APPLET_SECLOG_WRITE" as WriteEvent                    : Write external event data with added context data to HSM
 * state "ecy_hsm_APPLET_SECLOG_READ" as ReadEvent                      : Read out SecLog logs for a given EventID
 * state "ecy_hsm_APPLET_SECLOG_READOEM" as ReadOemEvent                : Read SecLog data in a specific format
 * state "ecy_hsm_APPLET_SECLOG_WRITE_EXT" as WriteExtendedEvent        : Extended write external event data with added context data to HSM
 * state "ecy_hsm_APPLET_SECLOG_READ_EXT" as ReadExtendedEvent          : Extended read out SecLog logs for a given EventID
 *
 * [*] --> ConfigLog
 * ConfigLog --> [*]
 *
 * [*] --> WriteEvent
 * WriteEvent --> [*]
 *
 * [*] --> ReadEvent
 * ReadEvent --> [*]
 *
 * [*] --> ReadOemEvent
 * ReadOemEvent --> [*]
 *
 * @enduml
 */
typedef enum ecy_hsm_Applet_SecureLogging_StateT
{
    ecy_hsm_APPLET_SECLOG_CFG,         /**< state for config log */
    ecy_hsm_APPLET_SECLOG_WRITE,       /**< state for write log */
    ecy_hsm_APPLET_SECLOG_READ,        /**< state for read entries */
    ecy_hsm_APPLET_SECLOG_READOEM,     /**< state for read entries */
    ecy_hsm_APPLET_SECLOG_WRITE_EXT,   /**< state for extended write log */
    ecy_hsm_APPLET_SECLOG_READ_EXT,    /**< state for extended read entries */
    /* This needs to be the final entry */
    ecy_hsm_APPLET_SECLOG_NUMSTATES    /**< number of states */
} ecy_hsm_Applet_SecureLogging_StateT;

/* *********** Deprecated enum definitions ***************/
/**
 * @deprecated by ecy_hsm_APPLET_SECLOG_CFG
 */
#define APPLET_SECLOG_CFG ecy_hsm_APPLET_SECLOG_CFG
/**
 * @deprecated by ecy_hsm_APPLET_SECLOG_WRITE
 */
#define APPLET_SECLOG_WRITE ecy_hsm_APPLET_SECLOG_WRITE
/**
 * @deprecated by ecy_hsm_APPLET_SECLOG_READ
 */
#define APPLET_SECLOG_READ ecy_hsm_APPLET_SECLOG_READ
/**
 * @deprecated by ecy_hsm_APPLET_SECLOG_READOEM
 */
#define APPLET_SECLOG_READOEM ecy_hsm_APPLET_SECLOG_READOEM
/**
 * @deprecated by ecy_hsm_APPLET_SECLOG_NUMSTATES
 */
#define APPLET_SECLOG_NUMSTATES ecy_hsm_APPLET_SECLOG_NUMSTATES
/**
 * @deprecated by ecy_hsm_Applet_SecureLogging_StateT
 */
#define Applet_SecureLogging_StateT ecy_hsm_Applet_SecureLogging_StateT
/* *********** Deprecated type definitions ***************/
/**
 * Applet context data for the Secure Logging Configuration operation
 * @ingroup APPLET_CONTEXT
 */
typedef HSM_SecureLoggingCfgParamT Applet_SecureLoggingCfgCtx_tst;

/**
 * Applet context data for the Secure Logging Read operation
 * @ingroup APPLET_CONTEXT
 */
typedef HSM_SecureLoggingRdParamT Applet_SecureLoggingRdCtx_tst;

/**
 * Applet context data for the Secure Logging Write operation
 * @ingroup APPLET_CONTEXT
 */
typedef HSM_SecureLoggingWrParamT Applet_SecureLoggingWrCtx_tst;

/*
**********************************************************************************************************************
* Extern declarations
**********************************************************************************************************************
*/

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @brief Secure Logging applet control structure
 */
extern const Applet_ts Applet_SecureLogging_HSM;

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @}
 */
#endif /* ECY_HSM_APPLET_SECLOG_H */
