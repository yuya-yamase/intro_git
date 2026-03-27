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

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_SERVICE_DATA_H
#define ECY_HSM_SERVICE_DATA_H

/**
 * @addtogroup GROUP_CSAI_CHKSUM
 * @{
 */

/* *** includes *******************************************************************************/
#include "ecy_hsm_csai_data.h"

/* *** defines ********************************************************************************/

/* *** type declarations **********************************************************************/

/** Structure for the data passed to a Secure Storage read operation */
typedef struct ecy_hsm_SecureStorageRdParamTag
{
    uint32  tag;        /**< ID of the secure data block to be read                 */
    void*   pData;      /**< Pointer to secure data buffer holding the read data    */
    uint32  dataLength; /**< Length of data buffer                                  */
    uint32* pDataCount; /**< Pointer to 4 bytes buffer to receive read data length  */
} ecy_hsm_SecureStorageRdParamT;

/** Structure for the data passed to a Secure Storage write operation */
typedef struct ecy_hsm_SecureStorageWrParamTag
{
    uint32      tag;        /**< ID of the secure data block to be written              */
    const void* pData;      /**< Pointer to secure data buffer holding data to write    */
    uint32      dataLength; /**< Length of data buffer                                  */
} ecy_hsm_SecureStorageWrParamT;

/** Structure for the data passed to a Secure Storage delete operation */
typedef struct ecy_hsm_SecureStorageDelParamTag
{
    uint32 tag;   /**< ID of the secure data block to be deleted              */
    uint32 dummy; /**< Proxy doesn't support parameter structs < 4 bytes      */
} ecy_hsm_SecureStorageDelParamT;

/** Structure for the data passed to Secure Storage applet */
/* PRQA S 0750 2 */ /* <Justification: Definition of a union is appropriate here */
typedef union ecy_hsm_SecureStorageParamT {
    ecy_hsm_SecureStorageRdParamT        readDataParam;     /**< Data passed within a structure for the Secure Storage read operation */
    ecy_hsm_SecureStorageWrParamT        writeDataParam;    /**< Data passed within a structure for the Secure Storage write operation */
    ecy_hsm_SecureStorageDelParamT       deleteDataParam;   /**< Data passed within a structure for the Secure Storage delete operation */
} ecy_hsm_SecureStorageParamT;

/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by @ref ecy_hsm_SecureStorageRdParamTag
 */
#define HSM_SecureStorageRdParamTag ecy_hsm_SecureStorageRdParamTag
/**
 * @deprecated by @ref ecy_hsm_SecureStorageRdParamTag
 */
#define HSM_SecureStorageRdParamT ecy_hsm_SecureStorageRdParamT
/**
 * @deprecated by @ref ecy_hsm_SecureStorageWrParamTag
 */
#define HSM_SecureStorageWrParamTag ecy_hsm_SecureStorageWrParamTag
/**
 * @deprecated by @ref ecy_hsm_SecureStorageWrParamTag
 */
#define HSM_SecureStorageWrParamT ecy_hsm_SecureStorageWrParamT
/**
 * @deprecated by @ref ecy_hsm_SecureStorageDelParamTag
 */
#define HSM_SecureStorageDelParamTag ecy_hsm_SecureStorageDelParamTag
/**
 * @deprecated by @ref ecy_hsm_SecureStorageDelParamTag
 */
#define HSM_SecureStorageDelParamT ecy_hsm_SecureStorageDelParamT
/**
 * @deprecated by @ref ecy_hsm_SecureStorageParamT
 */
#define HSM_SecureStorageParamT ecy_hsm_SecureStorageParamT
/* *** global constants ***********************************************************************/

/* *** exported interfaces ********************************************************************/

/* *INDENT-OFF* */
#ifdef __cplusplus
    extern "C" {
#endif
/* *INDENT-ON* */

/* *INDENT-OFF* */
#ifdef __cplusplus
    } /* extern "C" */
#endif
/* *INDENT-ON* */

/**
 * @}
 */

#endif /* Multiple inclusion lock  */
