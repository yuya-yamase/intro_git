/**
 * @file
 ***********************************************************************************************
 * @brief Secure access applet
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2014, all rights reserved.
 **********************************************************************************************/

#ifndef ECY_HSM_APPLET_SECACC_H
#define ECY_HSM_APPLET_SECACC_H

/*
**********************************************************************************************************************
* Includes
**********************************************************************************************************************
*/
#include "ecy_hsm_applet.h"
#include "ecy_hsm_csai_secacc.h"

/**
 * @addtogroup APPLET_IMPL
 * @{
 */

/** Maximum possible challenge length in bytes */
#define ecy_hsm_MAX_LEN_CHALLENGE                          256UL

/** Maximum possible challenge response length in bytes. */
#define ecy_hsm_MAX_LEN_RESPONSE                           1024UL

/** Supported challenge response sequence tag. */
#define ecy_hsm_SECACC_RESPONSE_SUPPORTED_SEQUENCE_TAG     0x30U

/** Supported challenge response version tag. */
#define ecy_hsm_SECACC_RESPONSE_SUPPORTED_VERSION_TAG      0x80U

/** Supported challenge response message type tag. */
#define ecy_hsm_SECACC_RESPONSE_SUPPORTED_MSG_TYPE_TAG     0x81U

/** Supported challenge response signature tag. */
#define ecy_hsm_SECACC_RESPONSE_SUPPORTED_SIGNATURE_TAG    0x29U

/** Supported challenge response cert chain tag. */
#define ecy_hsm_SECACC_RESPONSE_SUPPORTED_CERT_CHAIN_TAG   0x2AU

/** Supported challenge response octet string tag. */
#define ecy_hsm_SECACC_RESPONSE_SUPPORTED_OCTET_STRING_TAG 0x04U

/** Supported challenge response version. */
#define ecy_hsm_SECACC_RESPONSE_SUPPORTED_VERSION          1UL

/** Supported challenge response message type. */
#define ecy_hsm_SECACC_RESPONSE_SUPPORTED_MSG_TYPE         1UL

/* *********** Deprecated Macro definitions ***************/
/**
 * @deprecated by ecy_hsm_MAX_LEN_CHALLENGE
 */
#define MAX_LEN_CHALLENGE                                  ecy_hsm_MAX_LEN_CHALLENGE
/**
 * @deprecated by ecy_hsm_MAX_LEN_RESPONSE
 */
#define MAX_LEN_RESPONSE                                   ecy_hsm_MAX_LEN_RESPONSE
/**
 * @deprecated by ecy_hsm_SECACC_RESPONSE_SUPPORTED_SEQUENCE_TAG
 */
#define SECACC_RESPONSE_SUPPORTED_SEQUENCE_TAG             ecy_hsm_SECACC_RESPONSE_SUPPORTED_SEQUENCE_TAG
/**
 * @deprecated by ecy_hsm_SECACC_RESPONSE_SUPPORTED_VERSION_TAG
 */
#define SECACC_RESPONSE_SUPPORTED_VERSION_TAG              ecy_hsm_SECACC_RESPONSE_SUPPORTED_VERSION_TAG
/**
 * @deprecated by ecy_hsm_SECACC_RESPONSE_SUPPORTED_MSG_TYPE_TAG
 */
#define SECACC_RESPONSE_SUPPORTED_MSG_TYPE_TAG             ecy_hsm_SECACC_RESPONSE_SUPPORTED_MSG_TYPE_TAG
/**
 * @deprecated by ecy_hsm_SECACC_RESPONSE_SUPPORTED_SIGNATURE_TAG
 */
#define SECACC_RESPONSE_SUPPORTED_SIGNATURE_TAG            ecy_hsm_SECACC_RESPONSE_SUPPORTED_SIGNATURE_TAG
/**
 * @deprecated by ecy_hsm_SECACC_RESPONSE_SUPPORTED_CERT_CHAIN_TAG
 */
#define SECACC_RESPONSE_SUPPORTED_CERT_CHAIN_TAG           ecy_hsm_SECACC_RESPONSE_SUPPORTED_CERT_CHAIN_TAG
/**
 * @deprecated by ecy_hsm_SECACC_RESPONSE_SUPPORTED_OCTET_STRING_TAG
 */
#define SECACC_RESPONSE_SUPPORTED_OCTET_STRING_TAG         ecy_hsm_SECACC_RESPONSE_SUPPORTED_OCTET_STRING_TAG
/**
 * @deprecated by ecy_hsm_SECACC_RESPONSE_SUPPORTED_VERSION
 */
#define SECACC_RESPONSE_SUPPORTED_VERSION                  ecy_hsm_SECACC_RESPONSE_SUPPORTED_VERSION
/**
 * @deprecated by ecy_hsm_SECACC_RESPONSE_SUPPORTED_MSG_TYPE
 */
#define SECACC_RESPONSE_SUPPORTED_MSG_TYPE                 ecy_hsm_SECACC_RESPONSE_SUPPORTED_MSG_TYPE

/*
**********************************************************************************************************************
* Type definitions
**********************************************************************************************************************
*/
/**
 * @brief Possible states for secure access applet
 *
 * @details
 * @section APPLET_SECACC Secure access applet
 *
 * @image html ./states_secacc.png "State diagram of applet: Secure access" width=15cm
 * @image rtf  ./states_secacc.png "State diagram of applet: Secure access" width=15cm
 */
typedef enum ecy_hsm_Applet_SecAcc_StateT
{
    ecy_hsm_APPLET_SECACC_STATE_CHALLENGE_E,         /**< state for getting challenge */
    ecy_hsm_APPLET_SECACC_STATE_TRANSFER_RESPONSE_E, /**< state for transferring response data */
    ecy_hsm_APPLET_SECACC_STATE_VERIFY_E,            /**< state for verifying the response */
    /* This needs to be the final entry */
    ecy_hsm_APPLET_SECACC_NUMSTATES_E /**< number of states */
} ecy_hsm_Applet_SecAcc_StateT;

/**
 * @brief Possible types of challenge data to be requested
 * @ingroup APPLET_PARAMETERS
 */
typedef enum ecy_hsm_Applet_SecAcc_ChallengeTypeT
{
    ecy_hsm_APPLET_SECACC_CHALLENGE_PRN_E,  /**< Challenge type: PSEUDO random number (not supported !!!) */
    ecy_hsm_APPLET_SECACC_CHALLENGE_TRN_E,  /**< Challenge type: TRUE random number (not supported !!!) */
    ecy_hsm_APPLET_SECACC_CHALLENGE_PFRB_E, /**< Challenge type: RB platform */
    /* This needs to be the final entry */
    ecy_hsm_APPLET_SECACC_CHALLENGE_NUMTYPES_E /**< number of challenge types */
} ecy_hsm_Applet_SecAcc_ChallengeTypeT;

/**
 * @brief Possible verification response types
 * @ingroup APPLET_PARAMETERS
 */
typedef enum ecy_hsm_Applet_SecAcc_ResponseTypeT
{
    ecy_hsm_APPLET_SECACC_RESPONSE_INVERT_E,    /**< Response type: inverted challenge (for testing only) (not supported !!!) */
    ecy_hsm_APPLET_SECACC_RESPONSE_SIGNATURE_E, /**< Response type: signature (not supported !!!) */
    ecy_hsm_APPLET_SECACC_RESPONSE_CMAC_E,      /**< Response type: CMAC calculated over challenge (not supported !!!) */
    ecy_hsm_APPLET_SECACC_RESPONSE_USERCERT_E,  /**< Response type: user certificate (with signed challenge) (not supported !!!) */
    ecy_hsm_APPLET_SECACC_RESPONSE_PFRB_E,      /**< Response type: RB platform */

    ecy_hsm_APPLET_SECACC_RESPONSE_NUMTYPES_E /**< number of challenge types */
} ecy_hsm_Applet_SecAcc_ResponseTypeT;

/**
 * @brief parameters for secure access challenge request
 * @ingroup APPLET_PARAMETERS
 */
typedef struct ecy_hsm_Applet_SecAcc_ChallengeParamT
{
    uint8*  pData;              /**< Pointer to buffer to receive challenge data */
    uint32  numBytes;           /**< Length of buffer (in bytes) to receive challenge data */
    uint32* pNumBytesChallenge; /**< Length of challenge data that is really generated */
    uint32  slotIdTrustAnchor;  /**< Slot id to the trust anchor where the user certificate should
                                     be associated */
    uint32 slotIdAuthzOid;      /**< Slot id to the authorization OID which the user certificate
                                     should contain */
    const uint8* pAuthzValue;   /**< Authorization bits the user certificate shall fulfill */
    const uint8* pAuthzMask;    /**< Mask of authorization bits the user certificate: they specify
                                     if a bit is relevant or not */
    uint32 numAuthzBits;        /**< Length of the buffers pAuthzValue and pAuthzMask */
    uint8  useCaseId;           /**< ID of use case @see ecy_hsm_Csai_SecAcc_UseCaseT */
    uint8  nonceCtrl;           /**< ID of nonce type @see ecy_hsm_Csai_SecAcc_NonceCtrlT */
    uint8  typeId;              /**< ID of challenge type @see Applet_SecAcc_ChallengeTypeT */
    uint8  authLevel;           /**< ID of auth level; not supported at the moment */

} ecy_hsm_Applet_SecAcc_ChallengeParamT;

/**
 * @brief parameters for secure access verification
 * @ingroup APPLET_PARAMETERS
 */
typedef struct ecy_hsm_Applet_SecAcc_VerifyParamT
{
    const uint8* pData;           /**< Pointer to buffer to receive challenge data */
    uint32       numBytes;        /**< absolute length the whole response data */
    uint32       numBytesCurrent; /**< actual length ot the transferred response data (actual chunk size) */
    uint32*      pResult;         /**< Pointer to verification result status */

    uint8 typeId; /**< ID of challenge type @see Applet_SecAcc_ResponseTypeT */
    uint8 keyId;  /**< ID of key to be used for verification */
} ecy_hsm_Applet_SecAcc_VerifyParamT;

/**
 * Applet parameter data for secure access
 * @ingroup APPLET_PARAMETERS
 */
typedef struct ecy_hsm_SecAcc_ParamT
{
    ecy_hsm_Applet_SecAcc_ChallengeParamT challenge_st; /**< Challenge parameters */
    ecy_hsm_Applet_SecAcc_VerifyParamT    verify_st;    /**< Response verification parameters */
} ecy_hsm_SecAcc_ParamT;

/* *********** Deprecated enum definitions ***************/
/**
 * @deprecated by ecy_hsm_APPLET_SECACC_STATE_CHALLENGE_E
 */
#define APPLET_SECACC_STATE_CHALLENGE_E         ecy_hsm_APPLET_SECACC_STATE_CHALLENGE_E
/**
 * @deprecated by ecy_hsm_APPLET_SECACC_STATE_TRANSFER_RESPONSE_E
 */
#define APPLET_SECACC_STATE_TRANSFER_RESPONSE_E ecy_hsm_APPLET_SECACC_STATE_TRANSFER_RESPONSE_E
/**
 * @deprecated by ecy_hsm_APPLET_SECACC_STATE_VERIFY_E
 */
#define APPLET_SECACC_STATE_VERIFY_E            ecy_hsm_APPLET_SECACC_STATE_VERIFY_E
/**
 * @deprecated by ecy_hsm_APPLET_SECACC_NUMSTATES_E
 */
#define APPLET_SECACC_NUMSTATES_E               ecy_hsm_APPLET_SECACC_NUMSTATES_E
/**
 * @deprecated by ecy_hsm_APPLET_SECACC_CHALLENGE_PRN_E
 */
#define APPLET_SECACC_CHALLENGE_PRN_E           ecy_hsm_APPLET_SECACC_CHALLENGE_PRN_E
/**
 * @deprecated by ecy_hsm_APPLET_SECACC_CHALLENGE_TRN_E
 */
#define APPLET_SECACC_CHALLENGE_TRN_E           ecy_hsm_APPLET_SECACC_CHALLENGE_TRN_E
/**
 * @deprecated by ecy_hsm_APPLET_SECACC_CHALLENGE_PFRB_E
 */
#define APPLET_SECACC_CHALLENGE_PFRB_E          ecy_hsm_APPLET_SECACC_CHALLENGE_PFRB_E
/**
 * @deprecated by ecy_hsm_APPLET_SECACC_CHALLENGE_NUMTYPES_E
 */
#define APPLET_SECACC_CHALLENGE_NUMTYPES_E      ecy_hsm_APPLET_SECACC_CHALLENGE_NUMTYPES_E
/**
 * @deprecated by ecy_hsm_APPLET_SECACC_RESPONSE_INVERT_E
 */
#define APPLET_SECACC_RESPONSE_INVERT_E         ecy_hsm_APPLET_SECACC_RESPONSE_INVERT_E
/**
 * @deprecated by ecy_hsm_APPLET_SECACC_RESPONSE_SIGNATURE_E
 */
#define APPLET_SECACC_RESPONSE_SIGNATURE_E      ecy_hsm_APPLET_SECACC_RESPONSE_SIGNATURE_E
/**
 * @deprecated by ecy_hsm_APPLET_SECACC_RESPONSE_CMAC_E
 */
#define APPLET_SECACC_RESPONSE_CMAC_E           ecy_hsm_APPLET_SECACC_RESPONSE_CMAC_E
/**
 * @deprecated by ecy_hsm_APPLET_SECACC_RESPONSE_USERCERT_E
 */
#define APPLET_SECACC_RESPONSE_USERCERT_E       ecy_hsm_APPLET_SECACC_RESPONSE_USERCERT_E
/**
 * @deprecated by ecy_hsm_APPLET_SECACC_RESPONSE_PFRB_E
 */
#define APPLET_SECACC_RESPONSE_PFRB_E           ecy_hsm_APPLET_SECACC_RESPONSE_PFRB_E
/**
 * @deprecated by ecy_hsm_APPLET_SECACC_RESPONSE_NUMTYPES_E
 */
#define APPLET_SECACC_RESPONSE_NUMTYPES_E       ecy_hsm_APPLET_SECACC_RESPONSE_NUMTYPES_E

/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by ecy_hsm_Applet_SecAcc_StateT
 */
#define Applet_SecAcc_StateT                    ecy_hsm_Applet_SecAcc_StateT
/**
 * @deprecated by ecy_hsm_Applet_SecAcc_ChallengeTypeT
 */
#define Applet_SecAcc_ChallengeTypeT            ecy_hsm_Applet_SecAcc_ChallengeTypeT
/**
 * @deprecated by ecy_hsm_Applet_SecAcc_ResponseTypeT
 */
#define Applet_SecAcc_ResponseTypeT             ecy_hsm_Applet_SecAcc_ResponseTypeT
/**
 * @deprecated by ecy_hsm_Applet_SecAcc_ChallengeParamT
 */
#define Applet_SecAcc_ChallengeParamT           ecy_hsm_Applet_SecAcc_ChallengeParamT
/**
 * @deprecated by ecy_hsm_Applet_SecAcc_VerifyParamT
 */
#define Applet_SecAcc_VerifyParamT              ecy_hsm_Applet_SecAcc_VerifyParamT
/**
 * @deprecated by ecy_hsm_SecAcc_ParamT
 */
#define HSM_SecAcc_ParamT                       ecy_hsm_SecAcc_ParamT

/*
**********************************************************************************************************************
* Extern declarations
**********************************************************************************************************************
*/

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @brief Secure access applet control structures
 */
extern const Applet_ts Applet_SecAcc_HSM;

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @}
 */
#endif // ECY_HSM_APPLET_SECACC_H
