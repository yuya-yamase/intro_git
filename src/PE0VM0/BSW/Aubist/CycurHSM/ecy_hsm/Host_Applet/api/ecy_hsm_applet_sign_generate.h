/**
 * @file
 ***********************************************************************************************
 * @brief Signature generation applet interface
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2014, all rights reserved
 **********************************************************************************************/

#ifndef ECY_HSM_APPLET_SIGN_GENERATE_H
#define ECY_HSM_APPLET_SIGN_GENERATE_H

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
 * @brief Possible states for signature generation applet
 *
 * @details
 * @section APPLET_SIGN_GEN Signature generation applet
 *
 * @image html ./states_sign_generate.png "State diagram of applet: signature generation" width=15cm
 * @image rtf  ./states_sign_generate.png "State diagram of applet: signature generation" width=15cm
 */
typedef enum ecy_hsm_Applet_SignGenerateStatusTag
{
    ecy_hsm_APPLET_SIGN_GENERATE_STATE_INIT,            /**< state for signature generate init */
    ecy_hsm_APPLET_SIGN_GENERATE_STATE_UPDATE,          /**< state for signature generate update */
    ecy_hsm_APPLET_SIGN_GENERATE_STATE_FINAL,           /**< state for signature generate final */
    ecy_hsm_APPLET_SIGN_GENERATE_STATE_FULL,            /**< state for full signature generation */
    ecy_hsm_APPLET_SIGN_GENERATE_EXTENDED_STATE_INIT,   /**< state for signature generate extended init */
    ecy_hsm_APPLET_SIGN_GENERATE_EXTENDED_STATE_UPDATE, /**< state for signature generate extended update */
    ecy_hsm_APPLET_SIGN_GENERATE_EXTENDED_STATE_FINAL,  /**< state for signature generate extended final */
    ecy_hsm_APPLET_SIGN_GENERATE_EXTENDED_STATE_FULL,   /**< state for full signature generation extended */
                                                        /* This needs to be the final entry */
    ecy_hsm_APPLET_SIGN_GENERATE_NUMSTATES              /**< number of states */
} ecy_hsm_Applet_SignGenerateStatusT;

/* *********** Deprecated enum definitions ***************/
/**
 * @deprecated by ecy_hsm_APPLET_SIGN_GENERATE_STATE_INIT
 */
#define APPLET_SIGN_GENERATE_STATE_INIT ecy_hsm_APPLET_SIGN_GENERATE_STATE_INIT
/**
 * @deprecated by ecy_hsm_APPLET_SIGN_GENERATE_STATE_UPDATE
 */
#define APPLET_SIGN_GENERATE_STATE_UPDATE ecy_hsm_APPLET_SIGN_GENERATE_STATE_UPDATE
/**
 * @deprecated by ecy_hsm_APPLET_SIGN_GENERATE_STATE_FINAL
 */
#define APPLET_SIGN_GENERATE_STATE_FINAL ecy_hsm_APPLET_SIGN_GENERATE_STATE_FINAL
/**
 * @deprecated by ecy_hsm_APPLET_SIGN_GENERATE_STATE_FULL
 */
#define APPLET_SIGN_GENERATE_STATE_FULL ecy_hsm_APPLET_SIGN_GENERATE_STATE_FULL
/**
 * @deprecated by ecy_hsm_APPLET_SIGN_GENERATE_NUMSTATES
 */
#define APPLET_SIGN_GENERATE_NUMSTATES  ecy_hsm_APPLET_SIGN_GENERATE_NUMSTATES

/**
 * Parameters for signature generation applet
 */
typedef struct ecy_hsm_Applet_SignGenerateParamTag
{
    ecy_hsm_Csai_SignatureSchemeT scheme;     /**< digital signature schemes supported by the HSM         */
    ecy_hsm_Csai_KeyHandleT       hKey;       /**< Handle to a key available in the HSM's session context to use for signature */
    const uint8*                  msg;        /**< Pointer to first (or only) data block for operation    */
    uint32                        msgLength;  /**< Length of data block                                   */
    uint8*                        pSign;      /**< Pointer to buffer for result                           */
    uint32                        signLength; /**< Length of signature                                    */
    uint32*                       pSignCount; /**< Pointer to space, where the function can store how many bytes have been written to the sign buffer provided here */
} ecy_hsm_Applet_SignGenerateParamT;

/**
 * Parameters for signature generation applet with extendable CSAI
 */
typedef struct ecy_hsm_Applet_SignGenerateExtendedParamTag
{
    ecy_hsm_Applet_SignGenerateParamT signBasicParam;                     /**< Basic parameter set of Signature generation, to be used along side
                                                                               with extendable parameter set */
    ecy_hsm_Csai_SignGenExtended_ParamSetAndVersionT* pSignExtendedParam; /**< Pointer to extendable parameter sets, used by the corresponding
                                                                               extended CSAI */
} ecy_hsm_Applet_SignGenerateExtendedParamT;

/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by ecy_hsm_Applet_SignGenerateStatusTag
 */
#define Applet_SignGenerateStatusTag ecy_hsm_Applet_SignGenerateStatusTag
/**
 * @deprecated by ecy_hsm_Applet_SignGenerateStatusT
 */
#define Applet_SignGenerateStatusT ecy_hsm_Applet_SignGenerateStatusT
/**
 * @deprecated by ecy_hsm_Applet_SignGenerateParamTag
 */
#define Applet_SignGenerateParamTag ecy_hsm_Applet_SignGenerateParamTag
/**
 * @deprecated by ecy_hsm_Applet_SignGenerateParamT
 */
#define Applet_SignGenerateParamT ecy_hsm_Applet_SignGenerateParamT
/*
**********************************************************************************************************************
* Extern declarations
**********************************************************************************************************************
*/

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @brief SignGenerate applet control structures
 */
extern const Applet_ts Applet_SignGenerate_HSM;

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @}
 */
#endif // ECY_HSM_APPLET_SIGN_GENERATE_H
