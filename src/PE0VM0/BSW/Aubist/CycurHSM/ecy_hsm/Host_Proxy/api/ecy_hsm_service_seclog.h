/**
 * @file
 ***********************************************************************************************
 * @brief CSAI Secure Logging.
 * This header file is part of the Cryptographic Service Application Interface and specifies
 * types for interacting with the HSM secure logging interface of the CycurHSM.
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2019, all rights reserved.
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_SERVICE_SECLOG_H
#define ECY_HSM_SERVICE_SECLOG_H

/**
 * @addtogroup GROUP_CSAI_SECLOG
 * @{
 */

/* *** includes *******************************************************************************/
#include "ecy_hsm_csai_seclog.h"
#include "ecy_hsm_csai_keyid.h"


/* *** defines ********************************************************************************/

/* *** type declarations **********************************************************************/
/** Structure for the data passed to a Secure Logging Configuration operation */
typedef struct ecy_hsm_SecureLoggingCfgParamTag
{
    void*  envDataAddr;     /**< Address in global RAM to share context data from host with the HSM */
    uint32 envDataNumBytes; /**< Length, in byte, of the shared env. data to read                   */
} ecy_hsm_SecureLoggingCfgParamT;

/** Structure for the data passed to a Secure Logging Read operation */
typedef struct ecy_hsm_SecureLoggingRdParamTag
{
    void*   pEventData;        /**< Pointer to a buffer for the returned Secure Log data         */
    uint32  eventDataNumBytes; /**< Length, in byte, of the provided buffer                      */
    uint32* pEventCount;       /**< Pointer to receive the current counter of the specific event */
    uint8   eventId;           /**< ID of the event to be read                                   */
} ecy_hsm_SecureLoggingRdParamT;

/** Structure for the data passed to a Secure Logging Write operation */
typedef struct ecy_hsm_SecureLoggingWrParamTag
{
    const void* pEventData;        /**< Pointer to event data to write                 */
    uint32      eventDataNumBytes; /**< Size in byte of the data buffer                */
    uint8       eventId;           /**< ID of the event to be stored in the Secure Log */
} ecy_hsm_SecureLoggingWrParamT;

/** Structure for the data passed to a Secure Logging Read Extended operation */
typedef struct ecy_hsm_SecureLoggingRdExtParamTag
{
    ecy_hsm_Csai_SecLogReadExt_UseCaseAndParamT    secLogReadExtUseCaseAndParam;         /**< Data structure of the seclog read extended */
} ecy_hsm_SecureLoggingRdExtParamT;

/** Structure for the data passed to a Secure Logging Write Extended operation */
typedef struct ecy_hsm_SecureLoggingWrExtParamTag
{
    ecy_hsm_Csai_SecLogWriteExt_UseCaseAndParamT  secLogWriteExtUseCaseAndParam;         /**< Data structure of the seclog write extended */
} ecy_hsm_SecureLoggingWrExtParamT;

/** Structure for the data passed to Secure Logging applet */
/* PRQA S 0750 2 */ /* <Justification: Definition of a union is appropriate here */
typedef union ecy_hsm_SecureLoggingParamT
{
    ecy_hsm_SecureLoggingCfgParamT    cfgLogParam;          /**< Data passed within a structure for the Secure Logging cfg operation            */
    ecy_hsm_SecureLoggingRdParamT     readLogParam;         /**< Data passed within a structure for the Secure Logging read operation           */
    ecy_hsm_SecureLoggingWrParamT     writeLogParam;        /**< Data passed within a structure for the Secure Logging write operation          */
    ecy_hsm_SecureLoggingRdExtParamT  readExtLogParam;      /**< Data passed within a structure for the Secure Logging Extended read operation  */
    ecy_hsm_SecureLoggingWrExtParamT  writeExtLogParam;     /**< Data passed within a structure for the Secure Logging Extended write operation */
} ecy_hsm_SecureLoggingParamT;

/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by ecy_hsm_SecureLoggingCfgParamTag
 */
#define HSM_SecureLoggingCfgParamTag ecy_hsm_SecureLoggingCfgParamTag
/**
 * @deprecated by ecy_hsm_SecureLoggingCfgParamT
 */

#define HSM_SecureLoggingCfgParamT ecy_hsm_SecureLoggingCfgParamT
/**
 * @deprecated by ecy_hsm_SecureLoggingRdParamTag
 */
#define HSM_SecureLoggingRdParamTag ecy_hsm_SecureLoggingRdParamTag
/**
 * @deprecated by ecy_hsm_SecureLoggingRdParamT
 */

#define HSM_SecureLoggingRdParamT ecy_hsm_SecureLoggingRdParamT
/**
 * @deprecated by ecy_hsm_SecureLoggingWrParamTag
 */
#define HSM_SecureLoggingWrParamTag ecy_hsm_SecureLoggingWrParamTag
/**
 * @deprecated by ecy_hsm_SecureLoggingWrParamT
 */
#define HSM_SecureLoggingWrParamT ecy_hsm_SecureLoggingWrParamT
/**
 * @deprecated by ecy_hsm_SecureLoggingParamT
 */
#define HSM_SecureLoggingParamT ecy_hsm_SecureLoggingParamT

/* *** global constants ***********************************************************************/

/* *** exported interfaces ********************************************************************/

/**
 * @}
 */

#endif /* Multiple inclusion lock  */
