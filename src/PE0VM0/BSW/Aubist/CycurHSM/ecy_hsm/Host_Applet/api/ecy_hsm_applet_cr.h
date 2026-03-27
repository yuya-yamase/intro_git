/**
 * @file
 ***********************************************************************************************
 * @brief Challenge response applet
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2020, all rights reserved.
 **********************************************************************************************/

/* *** prologue  *******************************************************************************/

#ifndef ECY_HSM_APPLET_CR_H
#define ECY_HSM_APPLET_CR_H
/*
**********************************************************************************************************************
* Includes
**********************************************************************************************************************
*/
#include "ecy_hsm_applet.h"
#include "ecy_hsm_csai_cr.h"
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
 * @brief Possible states for challenge-response applet
 *
 * @details
 * @section APPLET_CR challenge-response applet
 *
 * Please note that there is no final state in the below diagrams. The challenge-response applet is only terminated
 * in case of an error, when another applet job is started in the session, or when the session is closed.
 *
 * Moreover, the transfer and verify operations may be called multiple times for the same challenge. Although this is
 * contrary to security principles (scanning should be avoided), it was explicitly requested as such by the customer/OEM.
 * The customer/OEM agrees to take full responsibility for this potential security weakness. Allowing the APIs to be
 * called multiple times is required for the robustness of the Immobilizer application making use of this challenge-response
 * feature.
 *
 * @subsection APPLET_CR_STATES_VL6 Applet states (Verlog6 use case)
 *
 * Applies when the APPLET_CHALLENGE_RESPONSE_VERLOG6 sub-feature is enabled.
 *
 * @startuml
 * state "ecy_hsm_APPLET_CR_STATE_CHALLENGE_E" as Challenge     : Get a new challenge
 * state "ecy_hsm_APPLET_CR_STATE_TRANSFER_E" as Transfer       : Transfer ICU response
 * state "ecy_hsm_APPLET_CR_STATE_VERIFY_E" as Verify           : Verify ICU response
 *
 * [*] --> Challenge
 * Challenge --> Transfer
 * Challenge --> Challenge
 * Transfer --> Challenge
 *
 * Challenge --> Verify
 * Transfer --> Verify
 * Transfer --> Transfer
 *
 * Verify --> Transfer
 * Verify --> Challenge
 * Verify --> Verify
 *
 * @enduml
 *
 * @subsection APPLET_CR_STATES_VL7 Applet states (Verlog7 use case)
 *
 * Applies when the APPLET_CHALLENGE_RESPONSE_VERLOG7 sub-feature is enabled.
 *
 * For the @ref ecy_hsm_CSAI_VERLOG7 use case, the @ref ecy_hsm_APPLET_CR_STATE_TRANSFER_E applet state
 * is internally splitted into 2 sub-states:
 * - Data (see @ref APPLET_CR_VERLOG7_TRANSFER_DATA): mandatory sub-state
 * - Resp (see @ref APPLET_CR_VERLOG7_TRANSFER_RESP): optional sub-state (as in the Verlog6 use case)
 *
 * @startuml
 * state "ecy_hsm_APPLET_CR_STATE_CHALLENGE_E" as Challenge         : Get a new challenge
 * state "ecy_hsm_APPLET_CR_STATE_TRANSFER_E(Data)" as TransferData : Transfer ICU challenge
 * state "ecy_hsm_APPLET_CR_STATE_TRANSFER_E(Resp)" as TransferResp : Transfer ICU response
 * state "ecy_hsm_APPLET_CR_STATE_VERIFY_E" as Verify               : Verify ICU response
 *
 * [*] --> Challenge
 * Challenge --> Challenge
 * Challenge --> TransferData
 *
 * TransferData --> Challenge
 * TransferData --> TransferData
 * TransferData --> TransferResp
 *
 * TransferResp --> Challenge
 * TransferResp --> TransferResp
 * TransferResp --> TransferData
 *
 * TransferData --> Verify
 * TransferResp --> Verify
 *
 * Verify --> TransferResp
 * Verify --> TransferData
 * Verify --> Challenge
 * Verify --> Verify
 *
 * @enduml
 *
 */

typedef enum ecy_hsm_Applet_CR_StateT
{
    ecy_hsm_APPLET_CR_STATE_CHALLENGE_E, /**< State for getting challenge */
    ecy_hsm_APPLET_CR_STATE_TRANSFER_E,  /**< State for verifying the response */
    ecy_hsm_APPLET_CR_STATE_VERIFY_E,    /**< State for verifying the response */
    /* This needs to be the final entry */
    ecy_hsm_APPLET_CR_NUMSTATES_E /**< Number of states */
} ecy_hsm_Applet_CR_StateT;
/**
 * @brief Parameters for CR applet for GetChallenge interface
 */
typedef struct ecy_hsm_Applet_CR_ChallengeParam
{
    uint8*                     pResponse;                   /**< Pointer to buffer to receive challenge data */
    uint32                     numBytes;                    /**< Length of buffer (in bytes) to receive challenge data */
    uint32*                    pNumBytesChallenge;          /**< Length of challenge data that is really generated */
    ecy_hsm_Csai_CR_NonceCtrlT nonceCtrl;                   /**< ID of nonce type @see ecy_hsm_Csai_CR_NonceCtrlT */
    ecy_hsm_Csai_CR_UseCaseT   useCaseId;                   /**< To define which Algorithm for the CR to be used */
    void*                      pUserSpecificChallengeParam; /**< pointer to receive the user specific structure */
} ecy_hsm_Applet_CR_ChallengeParamT;
/**
 * @brief Parameters for CR applet for Transfer response and verify response interfaces
 */
typedef struct ecy_hsm_Applet_CR_VerifyParamT
{
    const uint8*             pResponse;          /**< Pointer to buffer to receive challenge response */
    uint32                   numBytes;           /**< Absolute length the whole response data */
    uint32                   numBytesCurrent;    /**< Actual length of the transferred response data (actual chunk size) */
    uint32*                  pResult;            /**< Pointer to verification result status */
    ecy_hsm_Csai_CR_UseCaseT useCaseId;          /**< To define which Algorithm for the CR to be used */
    void*                    pUserSpecificParam; /**< Pointer to receive the user specific structure */
} ecy_hsm_Applet_CR_VerifyParamT;

/* *********** Deprecated enum definitions ***************/
/**
 * @deprecated by @ref ecy_hsm_APPLET_CR_STATE_CHALLENGE_E
 */
#define APPLET_CR_STATE_CHALLENGE_E ecy_hsm_APPLET_CR_STATE_CHALLENGE_E
/**
 * @deprecated by @ref ecy_hsm_APPLET_CR_STATE_TRANSFER_E
 */
#define APPLET_CR_STATE_TRANSFER_E  ecy_hsm_APPLET_CR_STATE_TRANSFER_E
/**
 * @deprecated by @ref ecy_hsm_APPLET_CR_STATE_VERIFY_E
 */
#define APPLET_CR_STATE_VERIFY_E    ecy_hsm_APPLET_CR_STATE_VERIFY_E
/**
 * @deprecated by @ref ecy_hsm_APPLET_CR_NUMSTATES_E
 */
#define APPLET_CR_NUMSTATES_E       ecy_hsm_APPLET_CR_NUMSTATES_E

/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by @ref ecy_hsm_Applet_CR_StateT
 */
#define Applet_CR_StateT            ecy_hsm_Applet_CR_StateT
/**
 * @deprecated by @ref ecy_hsm_Applet_CR_ChallengeParamT
 */
#define Applet_CR_ChallengeParamT   ecy_hsm_Applet_CR_ChallengeParamT
/**
 * @deprecated by @ref ecy_hsm_Applet_CR_ChallengeParam
 */
#define Applet_CR_ChallengeParam    ecy_hsm_Applet_CR_ChallengeParam
/**
 * @deprecated by @ref ecy_hsm_Applet_CR_VerifyParamT
 */
#define Applet_CR_VerifyParamT      ecy_hsm_Applet_CR_VerifyParamT
/*
**********************************************************************************************************************
* Extern declarations
**********************************************************************************************************************
*/

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @brief Challenge Response applet control structures
 */
extern const Applet_ts Applet_CR_HSM;

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @}
 */
#endif /* ECY_HSM_APPLET_CR_H */
