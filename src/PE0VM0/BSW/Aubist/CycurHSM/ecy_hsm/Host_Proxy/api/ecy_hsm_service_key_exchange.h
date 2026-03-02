/**
 * @file
 ***********************************************************************************************
 * @brief Header file for key exchange data structures
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2019, all rights reserved.
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_SERVICE_KEY_EXCHANGE_H
#define ECY_HSM_SERVICE_KEY_EXCHANGE_H

/* *** includes *******************************************************************************/

#include "ecy_hsm_csai_key_exchange.h"

/* *** defines ********************************************************************************/

/* *** type declarations **********************************************************************/

/** Structure for the data passed to the key exchange call ecy_hsm_Csai_DhInit */
typedef struct ecy_hsm_KeyExchangeDhInitParamTag
{
    uint32                  algorithm;         /**< DH algorithm to be used */
    ecy_hsm_Csai_KeyHandleT hKey;              /**< Handle to the key pair that should be used for the key exchange */
    uint8*                  pPublicKey;        /**< Buffer to receive the public key to be given to a peer */
    uint32                  publicKeyBuffSize; /**< Length of buffer to receive the public key */
    uint32*                 pPublicKeyLength;  /**< Length of the actual key written to publicKey[] */
} ecy_hsm_KeyExchangeDhInitParamT;

/** Structure for the data passed to the key exchange call ecy_hsm_Csai_DhComputeExt */
typedef struct ecy_hsm_KeyExchangeDhComputeExtParamTag
{
    const uint8* pRemotePublicKey;   /**< Public key of the conversation partner */
    uint32       publicKeyLength;    /**< Length of the remote public key */
    uint8*       pSharedSecret;      /**< Buffer to receive the shared secret to be used for further communication */
    uint32       sharedSecretLen;    /**< Size of the sharedSecretBuffer */
    uint32*      pSharedSecretCount; /**< Length of the actual sharedSecret written to sharedSecret[] */
} ecy_hsm_KeyExchangeDhComputeExtParamT;

/** Structure for the data passed to the key exchange call ecy_hsm_Csai_DhComputeInt */
typedef struct ecy_hsm_KeyExchangeDhComputeIntParamTag
{
    const uint8*             pRemotePublicKey; /**< Public key of the conversation partner */
    uint32                   publicKeyLength;  /**< Length of the remote public key */
    ecy_hsm_Csai_KeyHandleT* phSecret;         /**< The key handle of the shared secret */
} ecy_hsm_KeyExchangeDhComputeIntParamT;

/** Structure for the data passed to the key exchange call ecy_hsm_Csai_EcbdInit */
typedef struct ecy_hsm_KeyExchangeEcbdInitParamTag
{
    uint32                   curveId;        /**< Curve's ID to be used */
    uint32                   assignedNumber; /**< The assigned number (i) in the ring of participants */
    uint32                   partyCount;     /**< The total number of participants in the ring */
    ecy_hsm_Csai_KeyHandleT* phKey;          /**< Pointer to the handle for the key pair that should be used for the ECBD operation */
} ecy_hsm_KeyExchangeEcbdInitParamT;

/** Structure for the data passed to the key exchange call ecy_hsm_Csai_EcbdCompute2ndPubKey */
typedef struct ecy_hsm_KeyExchangeEcbdComp2ndPubKeyParamTag
{
    const uint8* pPublicKeyPreceding; /**< Public key of preceding party Z_(i-1) */
    const uint8* pPublicKeyNext;      /**< Public key of following party Z_(i+1) */
    uint8*       pPublicKey;          /**< Buffer to receive the public key for the second broadcast (X_i) */
    uint32       publicKeyBuffSize;   /**< Length of buffer to receive the public key */
    uint32*      pPublicKeyLength;    /**< Length of the actual key written to publicKey (depends on the selected curve) */
} ecy_hsm_KeyExchangeEcbdComp2ndPubKeyParamT;

/** Structure for the data passed to the key exchange call ecy_hsm_Csai_EcbdUpdate */
typedef struct ecy_hsm_KeyExchangeEcbdUpdateParamTag
{
    const uint8* pPublicKey;      /**< 2nd public key (X_j) of a party member */
    uint32       publicKeyLength; /**< Length of all public keys*/
    uint32       assignedNumber;  /**< The assigned number (i) in the ring of participants */
} ecy_hsm_KeyExchangeEcbdUpdateParamT;

/** Structure for the data passed to the key exchange call ecy_hsm_Csai_EcbdFinishInt */
typedef struct ecy_hsm_KeyExchangeEcbdFinishParamTag
{
    ecy_hsm_Csai_KeyHandleT* phKey; /**< Key handle to the shared secret */
} ecy_hsm_KeyExchangeEcbdFinishParamT;

/** Structure for the data passed to key exchange applet */
/* PRQA S 0750 2 */ /* <Deviation: Definition of a union is appropriate here */
typedef union ecy_hsm_KeyExchangeParamTag
{
    ecy_hsm_KeyExchangeDhInitParamT            keyExchangeDhInitParam;            /**< Parameter structure for ecy_hsm_Csai_DhInit */
    ecy_hsm_KeyExchangeDhComputeExtParamT      keyExchangeDhComputeExtParam;      /**< Parameter structure for ecy_hsm_Csai_DhComputeExt */
    ecy_hsm_KeyExchangeDhComputeIntParamT      keyExchangeDhComputeIntParam;      /**< Parameter structure for ecy_hsm_Csai_DhComputeInt */
    ecy_hsm_KeyExchangeEcbdInitParamT          keyExchangeEcbdInitParam;          /**< Parameter structure for ecy_hsm_Csai_EcbdInit */
    ecy_hsm_KeyExchangeEcbdComp2ndPubKeyParamT keyExchangeEcbdComp2ndPubKeyParam; /**< Parameter structure for ecy_hsm_Csai_EcbdCompute2ndPubKey */
    ecy_hsm_KeyExchangeEcbdUpdateParamT        keyExchangeEcbdUpdateParam;        /**< Parameter structure for ecy_hsm_Csai_EcbdUpdate */
    ecy_hsm_KeyExchangeEcbdFinishParamT        keyExchangeEcbdFinishParam;        /**< Parameter structure for ecy_hsm_Csai_EcbdFinishInt */
} ecy_hsm_KeyExchangeParamT;

/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by @ref ecy_hsm_KeyExchangeDhInitParamTag
 */
#define HSM_KeyExchangeDhInitParamTag            ecy_hsm_KeyExchangeDhInitParamTag
/**
 * @deprecated by @ref ecy_hsm_KeyExchangeDhInitParamTag
 */
#define HSM_KeyExchangeDhInitParamT              ecy_hsm_KeyExchangeDhInitParamT
/**
 * @deprecated by @ref ecy_hsm_KeyExchangeDhComputeExtParamTag
 */
#define HSM_KeyExchangeDhComputeExtParamTag      ecy_hsm_KeyExchangeDhComputeExtParamTag
/**
 * @deprecated by @ref ecy_hsm_KeyExchangeDhComputeExtParamTag
 */
#define HSM_KeyExchangeDhComputeExtParamT        ecy_hsm_KeyExchangeDhComputeExtParamT
/**
 * @deprecated by @ref ecy_hsm_KeyExchangeDhComputeIntParamTag
 */
#define HSM_KeyExchangeDhComputeIntParamTag      ecy_hsm_KeyExchangeDhComputeIntParamTag
/**
 * @deprecated by @ref ecy_hsm_KeyExchangeDhComputeIntParamTag
 */
#define HSM_KeyExchangeDhComputeIntParamT        ecy_hsm_KeyExchangeDhComputeIntParamT
/**
 * @deprecated by @ref ecy_hsm_KeyExchangeEcbdInitParamTag
 */
#define HSM_KeyExchangeEcbdInitParamTag          ecy_hsm_KeyExchangeEcbdInitParamTag
/**
 * @deprecated by @ref ecy_hsm_KeyExchangeEcbdInitParamTag
 */
#define HSM_KeyExchangeEcbdInitParamT            ecy_hsm_KeyExchangeEcbdInitParamT
/**
 * @deprecated by @ref ecy_hsm_KeyExchangeEcbdComp2ndPubKeyParamTag
 */
#define HSM_KeyExchangeEcbdComp2ndPubKeyParamTag ecy_hsm_KeyExchangeEcbdComp2ndPubKeyParamTag
/**
 * @deprecated by @ref  ecy_hsm_KeyExchangeEcbdComp2ndPubKeyParamTag
 */
#define HSM_KeyExchangeEcbdComp2ndPubKeyParamT   ecy_hsm_KeyExchangeEcbdComp2ndPubKeyParamT
/**
 * @deprecated by @ref ecy_hsm_KeyExchangeEcbdUpdateParamTag
 */
#define HSM_KeyExchangeEcbdUpdateParamTag        ecy_hsm_KeyExchangeEcbdUpdateParamTag
/**
 * @deprecated by @ref  ecy_hsm_KeyExchangeEcbdUpdateParamTag
 */
#define HSM_KeyExchangeEcbdUpdateParamT          ecy_hsm_KeyExchangeEcbdUpdateParamT
/**
 * @deprecated by @ref ecy_hsm_KeyExchangeEcbdFinishParamTag
 */
#define HSM_KeyExchangeEcbdFinishParamTag        ecy_hsm_KeyExchangeEcbdFinishParamTag
/**
 * @deprecated by @ref  ecy_hsm_KeyExchangeEcbdFinishParamTag
 */
#define HSM_KeyExchangeEcbdFinishParamT          ecy_hsm_KeyExchangeEcbdFinishParamT
/**
 * @deprecated by @ref ecy_hsm_KeyExchangeParamTag
 */
#define HSM_KeyExchangeParamTag                  ecy_hsm_KeyExchangeParamTag
/**
 * @deprecated by @ref  ecy_hsm_KeyExchangeParamTag
 */
#define HSM_KeyExchangeParamT                    ecy_hsm_KeyExchangeParamT

/* *** global constants ***********************************************************************/

/* *** exported interfaces ********************************************************************/

#endif /* ECY_HSM_SERVICE_KEY_EXCHANGE_H  */
