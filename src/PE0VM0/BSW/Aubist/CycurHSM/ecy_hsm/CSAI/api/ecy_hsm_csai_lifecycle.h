/**
 * @file
 ***********************************************************************************************
 * @brief CSAI Lifecycle operations
 * This header file is part of the Cryptographic Service Application Interface and specifies
 * types and functions for lifecycle state handling
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2014, all rights reserved.
 **********************************************************************************************/

#ifndef ECY_HSM_CSAI_LIFECYCLE_H
#define ECY_HSM_CSAI_LIFECYCLE_H

/* *** includes *******************************************************************************/

#include "ecy_hsm_csai.h"

/* *INDENT-OFF* */
#ifdef __cplusplus
extern "C" {
#endif
/* *INDENT-ON* */

/**
 * @addtogroup GROUP_CSAI_LIFE_CYCLE
 * @{
 */

/**
 * Lifecycle state definitions
 */
typedef enum ecy_hsm_Csai_LifecycleStateTag
{
    ecy_hsm_CSAI_LC_STATE_INFIELD1       = 0x01000000UL, /**< Lifecycle State InField 1  */
    ecy_hsm_CSAI_LC_STATE_INFIELD2       = 0x02000000UL, /**< Lifecycle State InField 2  */
    ecy_hsm_CSAI_LC_STATE_TEMPORARY      = 0x03000000UL, /**< Lifecycle State Temporary */
    ecy_hsm_CSAI_LC_STATE_PRIVMODESERIAL = 0x04000000UL, /**< Lifecycle State PRIVMODESERIAL */
    ecy_hsm_CSAI_LC_STATE_PRIVMODEDEV    = 0x05000000UL, /**< Lifecycle State PRIVMODEDEV */
    ecy_hsm_CSAI_LC_STATE_DEBUG          = 0x0E000000UL, /**< Lifecycle State HSM Debug   */
    ecy_hsm_CSAI_LC_STATE_PRODUCTION     = 0x0F000000UL, /**< Lifecycle State Production */
    ecy_hsm_CSAI_LC_STATE_RETURN         = 0x7F000000UL, /**< Return to the previous Lifecycle State */
    ecy_hsm_CSAI_LC_STATE_RESERVED       = 0x7FFFFFFFUL  /**< reserved state to ensure 32 bit enum */
} ecy_hsm_Csai_LifecycleStateT;

#define ecy_hsm_LC_MAINSTATE                0x7F000000UL /**< Bit mask for main state of Lifecycle state */
#define ecy_hsm_LC_SUBSTATE                 0x00FFFFFFUL /**< Bit mask for sub state of Lifecycle state */

/** Macro to extract the main state out of a Lifecycle state */
#define ecy_hsm_LC_GET_MAINSTATE(_LC_state) (((uint32)(_LC_state)) & ecy_hsm_LC_MAINSTATE)
/** Macro to extract the sub state out of a Lifecycle state */
#define ecy_hsm_LC_GET_SUBSTATE(_LC_state)  ((_LC_state) & ecy_hsm_LC_SUBSTATE)
/** Macro that check if a Lifecycle state is valid. It also checks against a given maximal mains state.
 *  Be aware, that this must really be a main state! Otherwise the check might not be correct. ecy_hsm_LC_GET_MAINSTATE can be used here. */
#define ecy_hsm_LC_IS_VALID_MAINSTATE(_LC_mainState, _LC_maxMainState)                                                                               \
    ((((_LC_mainState) != 0UL) && ((_LC_mainState) <= (_LC_maxMainState))) ? TRUE : FALSE)

/**
 * Lifecycle hardware state definitions
 */
typedef enum ecy_hsm_Csai_HwStateTag
{
    ecy_hsm_CSAI_HW_STATE_RESERVED = 0x7FFFFFFFUL /**< Hardware state should be defined here !!! */
} ecy_hsm_Csai_HwStateT;

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/**
 * [$DD 2392]
 * [$Satisfies $ARCH 454_v1]
 * @brief Set a new lifecycle state
 *
 * This function sets a new lifecycle state.
 *
 *
 * @param[in]   hSession     Handle to the session in which the job will be placed.
 * @param[in]   priority     Requested scheduling priority for this job on the HSM.
 * @param[in]   nextState    New state of the lifecycle to be set.
 * @param[out]  phJob        Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 *
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_SetLifecycleState(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                           ecy_hsm_Csai_JobPriorityT   priority,
                                                                                           uint32                      nextState,
                                                                                           ecy_hsm_Csai_JobHandleT*    phJob);
/**
 * [$DD 2393]
 * [$Satisfies $ARCH 455_v1]
 * @brief Read out the lifecycle state
 *
 * This function gives back the lifecycle state.
 *
 * @note
 * This functions reads DFlash if called in bootloader mode. This can potentially cause conflict states if Host accesses DFlash in parallel.
 *
 * @param[in]   hSession     Handle to the session in which the job will be placed.
 * @param[in]   priority     Requested scheduling priority for this job on the HSM.
 * @param[out]  pCurState    Pointer to the current state of the lifecycle.
 * @param[out]  pHwState     Pointer to the state of the microcontroller.
 * @param[out]  phJob        Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 *
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_GetLifecycleState(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                           ecy_hsm_Csai_JobPriorityT   priority,
                                                                                           uint32*                     pCurState,
                                                                                           uint32*                     pHwState,
                                                                                           ecy_hsm_Csai_JobHandleT*    phJob);

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* *INDENT-OFF* */
#ifdef __cplusplus
} /* extern "C" */
#endif
/* *INDENT-ON* */

/**
 * @}
 */

#endif /* ECY_HSM_CSAI_LIFECYCLE_H */
