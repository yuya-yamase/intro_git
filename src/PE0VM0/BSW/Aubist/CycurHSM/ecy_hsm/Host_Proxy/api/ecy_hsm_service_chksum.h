/**
 * @file
 ***********************************************************************************************
 * @brief CSAI checksum jobs.
 * This header file is part of the Cryptographic Service Application Interface and specifies
 * types and functions for calculating checksums and CRCs.
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2014, all rights reserved.
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_SERVICE_CHKSUM_H
#define ECY_HSM_SERVICE_CHKSUM_H

/**
 * @addtogroup GROUP_CSAI_CHKSUM
 * @{
 */

/* *** includes *******************************************************************************/
#include "ecy_hsm_csai_chksum.h"

/* *** defines ********************************************************************************/

/* *** type declarations **********************************************************************/

/** Structure for the data passed to a CheckSum Fast call operation   */
typedef struct ecy_hsm_CheckSumParamTag
{
    ecy_hsm_Csai_ChksumAlgorithmT algorithm;    /**< Algorithm for checksum or CRC                                                                  */
    const uint8*                  msg;          /**< Pointer to first (or only) data block for operation, may be NULL_PTR                           */
    uint32                        msgLength;    /**< Length of data block                                                                           */
    uint8*                        pResult;      /**< Pointer to buffer for result                                                                   */
    uint32                        resultLength; /**< Length of buffer for result                                                                    */
    uint32*                       pResultCount; /**< Pointer to buffer for the number of bytes written to the checksum buffer                       */
    uint32 truncationAllowed;                   /**< Set TRUE to permit the checksum to be truncated to fit within resultLength bytes, if FALSE
                                                     and resultLength bytes is insufficent, ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL will be returned      */
} ecy_hsm_CheckSumParamT;

/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by @ref ecy_hsm_CheckSumParamTag
 */
#define HSM_CheckSumParamT ecy_hsm_CheckSumParamT
/**
 * @deprecated by @ref ecy_hsm_CheckSumParamTag
 */
#define HSM_CheckSumParamTag ecy_hsm_CheckSumParamTag
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
