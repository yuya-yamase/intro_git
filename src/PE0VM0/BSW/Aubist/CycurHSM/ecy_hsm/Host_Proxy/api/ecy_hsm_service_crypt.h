/**
 * @file
 ***********************************************************************************************
 * @brief CSAI Crypto jobs.
 * This header file is part of the Cryptographic Service Application Interface and specifies
 * types and functions for Encryption and Decryption operations with CycurHSM.
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2014, all rights reserved.
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_SERVICE_CRYPT_H
#define ECY_HSM_SERVICE_CRYPT_H

/**
 * @addtogroup GROUP_CSAI_CRYPT
 * @{
 */

/* *** includes *******************************************************************************/

#include "ecy_hsm_csai_crypt.h"
#include "ecy_hsm_service_crypt_types.h"

/* *** type declarations **********************************************************************/

/** Structure for the data passed to a AuthUpdate operation     */
typedef struct ecy_hsm_AuthUpdateParamTag {
    const uint8* aad;                       /**< Next chunk or remainder of data for authentication                   */
    uint32 aadLength;                       /**< Length of the provided message or chunk                              */
}ecy_hsm_AuthUpdateParamT;

/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by @ref ecy_hsm_AuthUpdateParamTag
 */
#define HSM_AuthUpdateParamT ecy_hsm_AuthUpdateParamT
/**
 * @deprecated by @ref ecy_hsm_AuthUpdateParamTag
 */
#define HSM_AuthUpdateParamTag ecy_hsm_AuthUpdateParamTag
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
