/**
 * @file
 ***********************************************************************************************
 * @brief CSAI Hash jobs.
 * This header file is part of the Cryptographic Service Application Interface and specifies
 * types and functions for Hashing with CycurHSM.
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2014, all rights reserved.
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_SERVICE_HASH_H
#define ECY_HSM_SERVICE_HASH_H

/* *** includes *******************************************************************************/

#include "ecy_hsm_csai_hash.h"

/**
 * @addtogroup GROUP_CSAI_HASHING
 * @{
 */

/* *** defines ********************************************************************************/

/** Structure for the data passed to a Hash Fast call operation   */
typedef struct ecy_hsm_HashParamTag {
    ecy_hsm_Csai_HashAlgorithmT algorithm;          /**< Algorithm for checksum or CRC                                        */
    const uint8* msg;                       /**< Pointer to first (or only) data block for operation,
                                               can be NULL_PTR if msgLength is zero      */
    uint32 msgLength;                       /**< Length of data block                                                 */
    uint8* digest;                          /**< Pointer to buffer for result                                         */
    uint32 digestLength;                    /**< Length of digest buffer                                              */
    uint32* pDigestCount;                   /**< Pointer to buffer for the number of bytes written to digest buffer   */
    uint32 truncationAllowed;               /**< Set TRUE to permit the hash to be truncated to fit
                                               within digestLength bytes, if FALSE and digestLength bytes is
                                               insufficent, ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL will be returned   */
} ecy_hsm_HashParamT;

/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by @ref ecy_hsm_HashParamTag
 */
#define HSM_HashParamTag ecy_hsm_HashParamTag
/**
 * @deprecated by @ref ecy_hsm_HashParamTag
 */
#define HSM_HashParamT ecy_hsm_HashParamT

/**
 * @}
 */

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

#endif /* Multiple inclusion lock  */
