/**
 * @file
 ***********************************************************************************************
 * @brief CSAI ECC DH functions.
 * This header file is part of the Cryptographic Service Application Interface and specifies
 * types and functions for ECC DH with CycurHSM.
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2014, all rights reserved.
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_SERVICE_DH_H
#define ECY_HSM_SERVICE_DH_H

/* *** includes *******************************************************************************/

#include "ecy_hsm_csai_dh.h"

/* *** defines ********************************************************************************/

/* *** type declarations **********************************************************************/

/** Structure for the data passed to the ECC DH public key generate function   */
typedef struct ecy_hsm_EccDhPublicKeyGenerateParamTag
{
    uint8*  pPublicKey; /**< Pointer to buffer to receive the public key data */
    uint32* pLength;    /**< Pointer to length of buffer to receive the public key data  */
} ecy_hsm_EccDhPublicKeyGenerateParamT;

/** Structure for the data passed to the ECC DH compute shared secret function   */
typedef struct ecy_hsm_EccDhSharedSecretComputeParamTag
{
    const uint8* pRemotePublicKey;    /**< Pointer to buffer to receive the remote public key data */
    uint32       publicKeyLength;     /**< Length of buffer to receive the remote public key data  */
    uint8*       pSharedSecret;       /**< Pointer to buffer to return the shared secret data */
    uint32*      pSharedSecretLength; /**< Pointer to length of buffer to return the shared secret data  */
} ecy_hsm_EccDhSharedSecretComputeParamT;

/** Structure for the data passed to DH applet */
/* PRQA S 0750 2 */ /* <Deviation: Definition of a union is appropriate here */
typedef union ecy_hsm_EccDhParamTag
{
    ecy_hsm_EccDhPublicKeyGenerateParamT   dhPublicKeyGenParam;        /**< Parameter structure for ECC DH public key generation function */
    ecy_hsm_EccDhSharedSecretComputeParamT dhSharedSecretComputeParam; /**< Parameter structure for ECC DH compute shared secret function */
} ecy_hsm_EccDhParamT;

/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by @ref ecy_hsm_EccDhPublicKeyGenerateParamTag
 */
#define HSM_EccDhPublicKeyGenerateParamTag ecy_hsm_EccDhPublicKeyGenerateParamTag
/**
 * @deprecated by @ref ecy_hsm_EccDhPublicKeyGenerateParamTag
 */
#define HSM_EccDhPublicKeyGenerateParamT ecy_hsm_EccDhPublicKeyGenerateParamT
/**
 * @deprecated by @ref ecy_hsm_EccDhSharedSecretComputeParamTag
 */
#define HSM_EccDhSharedSecretComputeParamTag ecy_hsm_EccDhSharedSecretComputeParamTag
/**
 * @deprecated by @ref ecy_hsm_EccDhSharedSecretComputeParamTag
 */
#define HSM_EccDhSharedSecretComputeParamT ecy_hsm_EccDhSharedSecretComputeParamT
/**
 * @deprecated by @ref ecy_hsm_EccDhParamTag
 */
#define HSM_EccDhParamTag ecy_hsm_EccDhParamTag
/**
 * @deprecated by @ref ecy_hsm_EccDhParamTag
 */
#define HSM_EccDhParamT ecy_hsm_EccDhParamT

/* *** global constants ***********************************************************************/

/* *** exported interfaces ********************************************************************/

#endif /* Multiple inclusion lock  */
