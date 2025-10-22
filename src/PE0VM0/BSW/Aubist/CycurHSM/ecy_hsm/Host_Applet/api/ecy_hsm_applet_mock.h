/**
 * @file
 ***********************************************************************************************
 * @brief Mock testing applet interface
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2014, all rights reserved.
 **********************************************************************************************/

#ifndef APPLET_MOCK_H
#define APPLET_MOCK_H

/*
**********************************************************************************************************************
* Includes
**********************************************************************************************************************
*/
#include "ecy_hsm_applet.h"

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
 * Applet context data for MOCK testing applet
 * @ingroup APPLET_CONTEXT
 */
typedef struct ecy_hsm_Applet_MockCtx_tst {
    /* Public */
    void*               pHostCtx;                            /**< [in]: pointer to host side context (for synchronisation) */
    uint8               expectedState_u8;                    /**< [in]: the expected state */
    uint8               allowedFunc_u8;                      /**< [in]: the function the call is allowed for */
    uint32              isInitializeFunc_b;                  /**< [in]: is this a initialize call */
    uint32              isDestroyFunc_b;                     /**< [in]: is this a destroy call */
    uint16              initializeResult_u16;                /**< [in]: result of initialize */
    Applet_ReturnTypeT  executeCheckResult_st;               /**< [in]: result of execute check */
    Applet_ReturnTypeT  executeResult_st;                    /**< [in]: result of execute */
    uint32              initializeCallCount_u32;             /**< [in][out]: increment counter for initialize calls */
    uint32              executeCheckCallCount_u32;           /**< [in][out]: execute check call counter */
    uint32              executeCallCount_u32;                /**< [in][out]: execute call counter */
    uint32              isValidFunctionCallCount_u32;        /**< [in][out]: is valid function call counter */
    uint32              destroyCallCount_u32;                /**< [in][out]: destroy call counter */
} ecy_hsm_Applet_MockCtx_tst;

/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by ecy_hsm_Applet_MockCtx_tst
 */
#define Applet_MockCtx_tst ecy_hsm_Applet_MockCtx_tst

/*
**********************************************************************************************************************
* Extern declarations
**********************************************************************************************************************
*/

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/** MOCK applet control structures */
extern const Applet_ts Applet_Mock_HSM;

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/** @} */ // APPLET_IMPL

#endif // APPLET_MOCK_H
