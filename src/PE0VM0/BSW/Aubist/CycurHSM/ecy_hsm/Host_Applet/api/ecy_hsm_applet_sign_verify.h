/**
 * @file
 ***********************************************************************************************
 * @brief Signature verification applet interface
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2014, all rights reserved
 **********************************************************************************************/

#ifndef ECY_HSM_APPLET_SIGN_VERIFY_H
#define ECY_HSM_APPLET_SIGN_VERIFY_H

/*
**********************************************************************************************************************
* Includes
**********************************************************************************************************************
*/
#include "ecy_hsm_applet.h"
#include "ecy_hsm_csai_sign.h"

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
 * @brief Possible states for signature verification applet
 *
 * @details
 * @section APPLET_SIGN_VERIFY Signature verification applet
 *
 * @image html ./states_sign_verify.png "State diagram of applet: signature verification" width=15cm
 * @image rtf  ./states_sign_verify.png "State diagram of applet: signature verification" width=15cm
 */
typedef enum ecy_hsm_Applet_SignVerifyStatusTag
{
    ecy_hsm_APPLET_SIGN_VERIFY_STATE_INIT,               /**< state for signature verify init */
    ecy_hsm_APPLET_SIGN_VERIFY_STATE_UPDATE,             /**< state for signature verify update */
    ecy_hsm_APPLET_SIGN_VERIFY_STATE_FINAL,              /**< state for signature verify final */
    ecy_hsm_APPLET_SIGN_VERIFY_STATE_FULL,               /**< state for full signature verification */
    ecy_hsm_APPLET_SIGN_VERIFY_EXTENDED_STATE_INIT,      /**< state for signature verify extended init */
    ecy_hsm_APPLET_SIGN_VERIFY_EXTENDED_STATE_UPDATE,    /**< state for signature verify extended update */
    ecy_hsm_APPLET_SIGN_VERIFY_EXTENDED_STATE_FINAL,     /**< state for signature verify extended final */
    ecy_hsm_APPLET_SIGN_VERIFY_EXTENDED_STATE_FULL,      /**< state for full signature verification extended */
    /* This needs to be the final entry */
    ecy_hsm_APPLET_SIGN_VERIFY_NUMSTATES        /**< number of states */
} ecy_hsm_Applet_SignVerifyStatusT;

/* *********** Deprecated enum definitions ***************/
/**
 * @deprecated by ecy_hsm_APPLET_SIGN_VERIFY_STATE_INIT
 */
#define APPLET_SIGN_VERIFY_STATE_INIT ecy_hsm_APPLET_SIGN_VERIFY_STATE_INIT
/**
 * @deprecated by ecy_hsm_APPLET_SIGN_VERIFY_STATE_UPDATE
 */
#define APPLET_SIGN_VERIFY_STATE_UPDATE ecy_hsm_APPLET_SIGN_VERIFY_STATE_UPDATE
/**
 * @deprecated by ecy_hsm_APPLET_SIGN_VERIFY_STATE_FINAL
 */
#define APPLET_SIGN_VERIFY_STATE_FINAL ecy_hsm_APPLET_SIGN_VERIFY_STATE_FINAL
/**
 * @deprecated by ecy_hsm_APPLET_SIGN_VERIFY_STATE_FULL
 */
#define APPLET_SIGN_VERIFY_STATE_FULL ecy_hsm_APPLET_SIGN_VERIFY_STATE_FULL
/**
 * @deprecated by ecy_hsm_APPLET_SIGN_VERIFY_NUMSTATES
 */
#define APPLET_SIGN_VERIFY_NUMSTATES ecy_hsm_APPLET_SIGN_VERIFY_NUMSTATES

/**
 * Parameters for signature verification applet
 */
typedef struct ecy_hsm_Applet_SignVerifyParamTag
{
    ecy_hsm_Csai_SignatureSchemeT scheme;      /**< digital signature schemes supported by the HSM         */
    ecy_hsm_Csai_KeyHandleT       hKey;        /**< Handle to a key available in the HSM's session context to use for signature */
    const uint8*                  msg;         /**< Pointer to first (or only) data block for operation    */
    uint32                        msgLength;   /**< Length of data block                                   */
    const uint8*                  pSign;       /**< Pointer to the signature for verification              */
    uint32                        signLength;  /**< Length of signature                                    */
    uint32*                       pResultFlag; /**< Signature verification result Flag                     */
} ecy_hsm_Applet_SignVerifyParamT;

/**
 * Parameters for signature verification applet with extendable CSAI
 */
typedef struct ecy_hsm_Applet_SignVerifyExtendedParamTag
{
    ecy_hsm_Applet_SignVerifyParamT signBasicParam;                       /**< Basic parameter set of Signature verification, to be used along side
                                                                               with extendable parameter set */
    ecy_hsm_Csai_SignVerExtended_ParamSetAndVersionT* pSignExtendedParam; /**< Pointer to the extendable parameter sets, used by the corresponding
                                                                               extended CSAI */
} ecy_hsm_Applet_SignVerifyExtendedParamT;

/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by ecy_hsm_Applet_SignVerifyStatusTag
 */
#define Applet_SignVerifyStatusTag ecy_hsm_Applet_SignVerifyStatusTag
/**
 * @deprecated by ecy_hsm_Applet_SignVerifyStatusT
 */
#define Applet_SignVerifyStatusT ecy_hsm_Applet_SignVerifyStatusT
/**
 * @deprecated by ecy_hsm_Applet_SignVerifyParamTag
 */
#define Applet_SignVerifyParamTag ecy_hsm_Applet_SignVerifyParamTag
/**
 * @deprecated by ecy_hsm_Applet_SignVerifyParamT
 */
#define Applet_SignVerifyParamT ecy_hsm_Applet_SignVerifyParamT
/*
**********************************************************************************************************************
* Extern declarations
**********************************************************************************************************************
*/

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @brief SignVerify applet control structures
 */
extern const Applet_ts Applet_SignVerify_HSM;

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @}
 */
#endif // ECY_HSM_APPLET_SIGN_VERIFY_H
