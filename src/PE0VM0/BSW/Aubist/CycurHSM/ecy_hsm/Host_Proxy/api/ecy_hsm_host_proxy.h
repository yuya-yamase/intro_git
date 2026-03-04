/**
 * @file
 ***********************************************************************************************
 * @brief This header file defines the public structures and enums used for calls into the
 *        HSM Proxy Client. This is the software layer that talks to the HSM Bridge registers
 * @details This is the public header file for the proxy client
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2014, all rights reserved
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_HOST_PROXY_H
#define ECY_HSM_HOST_PROXY_H

/**
 * @addtogroup GROUP_HSM_PROXY_TYPES
 * @{
 */

/* *** includes *******************************************************************************/
#include "Std_Types.h"
#include "ecy_hsm_csai.h"
#include "ecy_hsm_service.h"
#include "ecy_hsm_general_host_cfg.h"

/**
 * Declare a type for the GetResource() callout function
 *
 * @details This function should lock an OS resource that is dedicated to the HSM Proxy */
typedef void (*ecy_hsm_pFunctionGetResourceT)(void);

/**
 * Declare a type for the ReleaseResource() callout function
 * @details This function should release an OS resource that is dedicated to the HSM Proxy */
typedef void (*ecy_hsm_pFunctionReleaseResourceT)(void);

/**
 * Declare a type for the GetCounterValue(uint32* pStartingValue) callout function
 * @details This function should return the value of a millisecond/microsecond counter */
typedef void (*ecy_hsm_pFunctionGetCounterValueT)(uint32* pStartingValue);

/**
 * Declare a type for the GetElapsedCounterValue(uint32 value, uint32* pStartingValue)
 * callout function.
 * @details This function should return the number of milliseconds that has elapsed
 *           between the time given by value and the current time.  */
typedef void (*ecy_hsm_pFunctionGetElapsedCounterValueT)(uint32 value, uint32* pElapsedValue);

/**
 * Define different states of the quickroute operation
 */
typedef enum ecy_hsm_QuickRouteStatusTag
{
    ecy_hsm_QR_STATUS_IDLE = 0,                   /**< No quickroute operation loaded on this port          */
    ecy_hsm_QR_STATUS_PENDING_VERIFY,             /**< Mac verify quickroute operation loaded               */
    ecy_hsm_QR_STATUS_PENDING_GENERATE,           /**< Mac generate quickroute operation loaded             */
    ecy_hsm_QR_STATUS_COPIED,                     /**< Result copied to session specific buffer             */
    ecy_hsm_QR_STATUS_COMPLETE,                   /**< Operation has completed on this port                 */
    ecy_hsm_QR_STATUS_ERROR,                      /**< Operation has completed with an error on this port   */
    ecy_hsm_QR_PORTSTATUS_RESERVED = 0x7FFFFFFFUL /**< Value defined to use memory size of uint32 for enums */
} ecy_hsm_QuickRouteStatusT;
/**
 * Declare a type for the ecy_HSM_ConfigureExtendedCallouts() callout function
 *
 * @details This function should be used for any external callouts needed by external teams e.g. to handle the watch dog, to handle the interrupts */
typedef void (*ecy_hsm_pFunctionExtendedCalloutsT)(void);

/**
 * Declare a type for the ecy_HSM_ConfigureExtendedCallouts() callout function
 *
 * @details This is an enum that provides tags that are used for any external callouts needed by external teams e.g. to handle the watch dog, to
 * handle the interrupts */
typedef enum ecy_HSM_configureExtendedCalloutsType
{
    ECY_HSM_PFUNCTION_IRQ_HANDLINGT, /**< The IRQ type for any external callouts needed by external teams e.g.
                                          to handle the watch dog, to handle the interrupts,*/
} ecy_HSM_configureExtendedCalloutsTypeT;

/* *** global constants ***********************************************************************/

/* *** exported interfaces ********************************************************************/

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/**
 * [$DD 1017]
 * [$Satisfies $ARCH 111][$Satisfies $ARCH 112][$Satisfies $ARCH 438]
 * Pass callout function pointers to the HSM host sided drivers.
 * The HSM host sided drivers will execute call outs to the host software to keep the drivers
 * free of dependencies to any operating system chosen on the host.
 *
 * @note
 * Please consult the HSM User's Guide and understand what the HSM host sided driver
 * expects from these callout. Failing to provide the required functionality may
 * result in subtle failure of your system.
 *
 * The following callout functionality should be provided by the system integrator:
 *
 * - @c GetResource, @c ReleaseResource
 *      A function to lock an OS resource (or enter a critical section lock)
 *      dedicated to the HSM. The HSM driver uses this to serialize
 *      access to the inter-core communication structures in a
 *      multi-tasking environment. The resource is locked for very short
 *      periods of time.
 *      The caller may set this to @c NULL_PTR in which case the HSM doesn't
 *      attempt to lock any resource, e.g. in a non-multitasking
 *      environment like a boot loader.
 *
 * - @c GetCounterValue, GetElapsedCounterValue
 *      A function to get the value of a millisecond/microsecond tick counter and the elapsed
 *      number of milliseconds/microsecond since the supplied value.
 *   @note By default this function should return millisecond unless the feature TIMER_RESOLUTION_MICROSECOND is enabled.
 *
 * @param pFunctionGetResource            Pointer to a function which will lock an OS resource
 *                                        that is dedicated to the HSM Proxy
 *                                        Can be @c NULL_PTR if all accesses to the HSM interfaces
 *                                        (SHE and CSAI) are performed by a single task
 * @param pFunctionReleaseResource        Pointer to a function which will release an OS resource that is dedicated to
 *                                        the HSM Proxy
 *                                        Can be @c null if all accesses to the HSM interfaces (SHE and CSAI) are
 *                                        performed by a single task
 * @param pFunctionGetCounterValue        Pointer to a function which returns the value of a millisecond/microsecond counter
 * @param pFunctionGetElapsedCounterValue Pointer to a function which returns the number of milliseconds/microseconds elapsed since
 *                                        the supplied "value"
 *                                        number of milliseconds/microseconds.
 *
 * @returns
 * - ecy_hsm_CSAI_ERR_INVALID_PARAM       If a NULL_PTR pointer is passed as either pFunctionGetCounterValue
 *                                        or pFunctionGetElapsedCounterValue.
 *                                        If pFunctionGetResource and pFunctionReleaseResource are different
 *                                        If pFunctionGetResource xor pFunctionReleaseResource is a NULL_PTR
 * - ecy_hsm_CSAI_SUCCESS                 If no errors
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_HSM_ConfigureCallouts(ecy_hsm_pFunctionGetResourceT            pFunctionGetResource,
                                            ecy_hsm_pFunctionReleaseResourceT        pFunctionReleaseResource,
                                            ecy_hsm_pFunctionGetCounterValueT        pFunctionGetCounterValue,
                                            ecy_hsm_pFunctionGetElapsedCounterValueT pFunctionGetElapsedCounterValue);

/**
 * [$DD 1744]
 * Pass callout function pointers to the HSM host sided drivers.
 * used for any external callouts needed by external teams.
 * The HSM host sided drivers will execute call outs to the host software to keep the drivers
 * free of dependencies to any operating system chosen on the host.
 * [$Satisfies $ARCH 438] [$Satisfies $SW_ARCH EB4B0E00]
 *
 * @note
 * this feature is still in development.
 *
 * The following callout functionality should be provided by the system integrator:
 *
 * - @c ecy_hsm_pFunctionExtendedCallouts
 *      A function should be used for any external callouts needed by external teams
 *      e.g. to handle the watch dog, to handle the interrupts,
 *
 * @param pFunctionExtendedCallouts        Pointer to a function which will execute any external callouts needed by external teams.
 * @param configureExtendedCalloutsType    This is an enum that provides different types of external callouts needed by external teams,
 *                                         so far only ECY_HSM_PFUNCTION_IRQ_HANDLINGT type is available.
 *
 * @returns
 * - ecy_hsm_CSAI_ERR_INVALID_PARAM       If a NULL_PTR pointer is passed as pFunctionExtendedCallouts
 * - ecy_hsm_CSAI_SUCCESS                 If no errors
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_HSM_ConfigureExtendedCallouts(ecy_hsm_pFunctionExtendedCalloutsT     pFunctionExtendedCallouts,
                                                    ecy_HSM_configureExtendedCalloutsTypeT configureExtendedCalloutsType);

/**
 * [$DD 1018]
 * [$Satisfies $SW_ARCH 19707FC0]
 * Extracts critical errors, like for example startup errors, reported by the HSM core via the HSM2Host flags register.
 * @details Concrete errors can be extracted by masking the single bits with the provided HSM2HTS_ERR_* defines.
 *
 * @returns A numeric value representing the critical error(s) reported by the HSM core. Zero indicates that no error
 *          was reported.
 */
uint32 ecy_HSM_GetCoreErrorFlags(void);

/**
 * [$DD 1019]
 * [$Satisfies $ARCH 459]
 * Tell the HSM that it is now OK for it to access it's FLASH.
 * @details The startup sequence is that the HSM executes its bootstrapper, which loads itself into
 *          the HSM private RAM.  It then set HSM_READY and HSM_BOOTED and waits in a loop for this
 *          function to be called.  Once this function has been called, the HSM will check the core
 *          application's CRC and then jump to the core application.
 *
 * @returns ecy_hsm_CSAI_SUCCESS
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_HSM_Release(void);

/**
 * [$DD 1020]
 * [$Satisfies $ARCH 115] [$Satisfies $SW_ARCH FFD0C668] [$Satisfies $SW_ARCH C12CA6C0]
 * @brief Tell the HSM to perform maintenance operations
 * @details The function is used to request the HSM to start a FEE maintenance operation & check its running status.
 *          The FEE maintenance consists in repairing redundant FEE blocks having one copy being corrupted.
 *          The function returns ecy_hsm_CSAI_FC_PENDING while maintenance is in progress.
 *          The function shall be called repeatedly until the operation has completed (ecy_hsm_CSAI_SUCCESS or CSAI_ERR_xxx).
 *          The Host shall call ecy_HSM_DoMaintenance() while the HSM is idle (e.g. during PostDrive) to avoid delaying
 *          other, high-prio operations.
 *
 *          Note: the total execution time of ecy_HSM_DoMaintenance() is non deterministic, depending upon the number of
 *          used
 *          FEE blocks and their corruption state. In the worst case, ecy_HSM_DoMaintenance() may trigger an FEE sector
 *          reorganization, which can last several seconds.
 *
 * @return
 * - ecy_hsm_CSAI_SUCCESS: The HSM maintenance operation has completed.
 * - ecy_hsm_CSAI_FC_PENDING: The operation is still in progress.
 * - ecy_hsm_CSAI_ERR_TIMEOUT: A timeout occurred while waiting for HSM's request acknowledgment.
 * - ecy_hsm_CSAI_ERR_HSM2HTS_LOCKUP: The HSM Core Application is not running.
 * - ecy_hsm_CSAI_ERR_NULL_CALLOUT: The callout function pointer for @ref ecy_hsm_pFunctionGetCounterValueT
 *                                  or @ref ecy_hsm_pFunctionGetElapsedCounterValueT is null.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_HSM_DoMaintenance(void);

/**
 * [$DD 1021]
 * [$Satisfies $ARCH 458]
 * Tell the HSM what clock divider to use.
 * @details The divider will not actually change until a divider update is triggered
 *          Normally this updates all the system clock dividers together.  If the HSM core
 *          crashes (Core in CheckStop) after the divider update then it can be that the
 *          system clock dividers no longer have the correct relative values.
 *
 * @param[in] divider Value for the HSM clock divider, 5 causes a divide by six
 *
 * @return
 * - ecy_hsm_CSAI_SUCCESS: The HSM maintenance operation has completed.
 * - ecy_hsm_CSAI_ERR_INVALID_PARAM: invalid value provided for the divider parameter
 * - ecy_hsm_CSAI_ERR_TIMEOUT: A timeout occurred while waiting for HSM's request acknowledgment.
 * - ecy_hsm_CSAI_ERR_HSM_NOT_STARTED: The HSM doesn't accept clock configuration commands.
 * - ecy_hsm_CSAI_ERR_NULL_CALLOUT: The callout function pointer for @ref ecy_hsm_pFunctionGetCounterValueT
 *                                  or @ref ecy_hsm_pFunctionGetElapsedCounterValueT is null.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_HSM_ClockConfigure(uint32 divider);

/**
 * [$DD 2980]
 * [$Satisfies $SW_ARCH A65D75DC]
 * Tell the HSM to suspend the writing to the shared RAM.
 * @details This shall be called to suspend HSM from writing to the shared memory. The later request job
 *           data would stored the local memory.
 *
 * @note ecy_HSM_Configure shall be called again to enable writing to shared RAM
 *
 * @return
 * - ecy_hsm_CSAI_SUCCESS:              The HSM has been suspended from writing to shared memory.
 * - ecy_hsm_CSAI_ERR_TIMEOUT:          A timeout occurred while waiting for HSM's request acknowledgment or feature is disabled.
 * - ecy_hsm_CSAI_ERR_NULL_CALLOUT:     The callout function pointer for @ref ecy_hsm_pFunctionGetCounterValueT
 *                                           or @ref ecy_hsm_pFunctionGetElapsedCounterValueT is null.
 * - ecy_hsm_CSAI_ERR_HSM2HTS_LOCKUP    The HSM is not in expected state.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_HSM_SuspendSharedRamWrite (void);

/**
 * [$DD 1637]
 * [$Satisfies $ARCH 458]
 * Tell the HSM what peripheral clock divider to use.
 * @note This function is currently only supported for Cypress Traveo II.
 *       It sets the clock divider for CLK_PERI (this clock is the divided
 *       version of CLK_HF0), whereas ecy_HSM_ClockConfigure() sets the
 *       clock divider for CLK_SLOW (that clock is the divided version of CLK_PERI)
 *
 * @pre The HSM should be booted (HSM_BOOTED) prior to calling this function.
 * @pre HSM callout(s) should be configured prior to calling this function.
 * The configuration of peripheral clock divider will fail if any the above pre-condition is not fulfilled.
 *
 * @param[in] divider Value for the HSM peripheral clock divider (division by divider value + 1)
 *
 * @return
 * - ecy_hsm_CSAI_SUCCESS: The HSM maintenance operation has completed.
 * - ecy_hsm_CSAI_ERR_INVALID_PARAM: invalid value provided for the divider parameter (divider > 0xFF).
 * - ecy_hsm_CSAI_ERR_TIMEOUT: A timeout occurred while waiting for HSM's request acknowledgment.
 * - ecy_hsm_CSAI_ERR_HSM_NOT_STARTED: The HSM doesn't accept clock configuration commands.
 * - ecy_hsm_CSAI_ERR_NULL_CALLOUT: The callout function pointer for @ref ecy_hsm_pFunctionGetCounterValueT
 *                                  or @ref ecy_hsm_pFunctionGetElapsedCounterValueT is null.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_HSM_PeriClockConfigure(uint32 divider);

#if (ecy_hsm_HOST_STORAGE == ENABLED)

/**
 * [$DD 1215]
 * Tell the HSM the memory address of the host storage cache.
 * [$Satisfies $ARCH 782]
 *
 * @details This function verifies that the host storage cache is in a valid state (i.e. initialised)
 * and sends the memory address of the cache to the HSM.
 * The memory address is only sent to the HSM if the cache is in a valid state; otherwise
 * an indicative fail-mode error is returned to the client.
 *
 * @note
 * Please consult the HSM User Guide to understand the initialisation procedures for CycurHSM Host Storage.
 * It is important that data stored within the cache is correct to prevent storage errors.
 * The HSM will use the cache to read/write cryptographic material.
 *
 * @pre The HSM should be booted (HSM_BOOTED) prior to calling this function.
 * @pre HSM callout(s) should be configured prior to calling this function.
 * @pre The cache should be in a valid state prior to calling this function.
 * The configuration of host storage will fail if any the above pre-condition is not fulfilled.
 *
 * @return      Status code to signal success or failure.
 * @retval      ecy_hsm_CSAI_SUCCESS                            Host Storage configuration successful.
 * @retval      ecy_hsm_CSAI_ERR_HOST_STORAGE_STATE_INVALID     State of the Host Storage Cache is invalid (e.g. not initialised)
 * @retval      ecy_hsm_CSAI_ERR_HSM_NOT_STARTED                HSM has not started.
 * @retval      ecy_hsm_CSAI_ERR_NULL_CALLOUT                   HSM proxy callout(s) are not configured.
 * @retval      ecy_hsm_CSAI_ERR_TIMEOUT                        Timeout (ecy_HSM_CONFIGURATION_DELAY) occurred during configuration.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_HSM_HostStorageConfigure(void);

#endif /* #if (ecy_hsm_HOST_STORAGE == ENABLED) */

/**
 * [$DD 1022]
 * [$Satisfies $SW_ARCH FFD0C668] [$Satisfies $ARCH 460]
 * Wait for the HSM to have booted far enough to accept the following commands:
 *  - Clock configuration
 *  - Switch to bootloader
 *  - HSM Release
 *
 * @param[in] timeout Milliseconds to wait
 *
 * @returns
 * - @ref ecy_hsm_CSAI_SUCCESS           HSM is started
 * - @ref ecy_hsm_CSAI_ERR_TIMEOUT       A timeout occurred
 * - @ref ecy_hsm_CSAI_ERR_NULL_CALLOUT  At least one of the callouts @ref ecy_hsm_pCalloutGetCounterValue
 *                                       or @ref ecy_hsm_pCalloutGetElapsedCounterValue is not set.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_HSM_WaitForBooted(uint32 timeout);

/**
 * [$DD 1023]
 * [$Satisfies $SW_ARCH FFD0C668]
 * Wait for the HSM to be in the specified mode
 *
 * @param[in] mode    HSM mode to wait for
 * @param[in] timeout Milliseconds to wait
 *
 * @returns
 * - @ref ecy_hsm_CSAI_SUCCESS           HSM reached @c mode
 * - @ref ecy_hsm_CSAI_ERR_TIMEOUT       A timeout occurred
 * - @ref ecy_hsm_CSAI_ERR_NULL_CALLOUT  At least one of the callouts @ref ecy_hsm_pCalloutGetCounterValue
 *                                       or @ref ecy_hsm_pCalloutGetElapsedCounterValue is not set.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_HSM_WaitForMode(HSM_ModeT mode, uint32 timeout);

#if (ecy_hsm_WAIT_FOR_MODE_WATCH_DOG == ENABLED)
/**
 * [$DD 2173]
 * Wait for the HSM to be in the specified mode with the additional watchdog function
 * [$Satisfies $SW_ARCH 1245]
 *
 * @note
 * An optional safety feature is built into this function that allows the caller
 * to specify a watchdog callback routine that is periodically called while
 * the function busy spins. Should the watchdog return any other value than @c 0
 * then this function immediately returns thereafter with @ref ecy_hsm_CSAI_ERR_CRASH.
 *
 * @param[in] mode        HSM mode to wait for
 * @param[in] watchdog    A pointer to an application watchdog function.
 *                          May be @c NULL_PTR.
 * @param[in] pParam      A parameter of type void * passed back to the watchdog function.
 * @param[in] timeout     Milliseconds to wait
 *
 * @returns
 * - @ref ecy_hsm_CSAI_SUCCESS           HSM reached @c mode
 * - @ref ecy_hsm_CSAI_ERR_TIMEOUT       A timeout occurred
 * - @ref ecy_hsm_CSAI_ERR_NULL_CALLOUT  The error code returned by @ref ecy_HSM_GetCounterValue or @ref ecy_HSM_GetElapsedCounterValue .
 * - @ref ecy_hsm_CSAI_ERR_CRASH         The call has been aborted by the watchdog.
 */
ecy_hsm_Csai_ErrorT ecy_HSM_WaitForModeWD(HSM_ModeT mode, CSAI_WatchdogFunctionT watchdog, void* pParam, uint32 timeout);
#endif /* ecy_hsm_WAIT_FOR_MODE_WATCH_DOG == ENABLED */
/**
 * [$DD 1024]
 * [$Satisfies $SW_ARCH FFD0C668] [$Satisfies $SW_ARCH 21A5B583]
 * Trigger HSM reset
 *
 * @param[in] expectedMode Expected runtime mode of HSM after re-boot
 * @param[in] timeout      Milliseconds to wait
 *
 * @note The reset can only be triggered within RAM mode, e.g. after performing a secflash operation.
 *       ecy_HSM_Reset has no functionality during normal operation and will simply return @ref ecy_hsm_CSAI_SUCCESS,
 *       depending on the input parameters.
 *
 * @note Because @c timeout is evaluated multiple times within this function,
 *       it may take longer than the specified @c timeout and still succeed.
 *
 * @returns @ref ecy_hsm_CSAI_SUCCESS           If Ok.
 * @returns @ref ecy_hsm_CSAI_ERR_TIMEOUT       A timeout occurred.
 * @returns @ref ecy_hsm_CSAI_ERR_NULL_CALLOUT  At least one of the callouts @ref ecy_hsm_pCalloutGetCounterValue
 *                                              or @ref ecy_hsm_pCalloutGetElapsedCounterValue is not set.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_HSM_Reset(HSM_ModeT expectedMode, uint32 timeout);

/**
 * [$DD 1385]
 * [$Satisfies $SW_ARCH 886]
 * @brief Check if the HSM is busy
 *
 * @details This function iterates through all the available host sessions to check if there is any scheduled or pending
 *          job. If there is a scheduled or pending job, the HSM is considered BUSY, otherwise, the HSM is considered free.
 *
 * @return
 * - @ref ecy_hsm_CSAI_SUCCESS                    HSM is free, i.e., no jobs are pending nor being processed on any session.
 * - @ref ecy_hsm_CSAI_FC_BUSY                    HSM is busy, i.e., at least one session has a job that is pending or being processed.
 * - @ref ecy_hsm_CSAI_ERR_INVALID_STATE          HSM is neither in the bootloader nor application mode.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_IsHsmBusy(void);

/**
 * [$DD 1409]
 * [$Satisfies $SW_ARCH 887]
 * @brief Check if valid core app is installed in HSM
 *
 * @details This function evaluates the HSM2HTS register and returns the status of the core app verification, i.e.,
 *          end pattern is correct and integrity is checked.
 *
 * @return
 * - @ref ecy_hsm_CSAI_SUCCESS                                  End pattern ok, CMAC ok
 * - @ref ecy_hsm_CSAI_ERR_CORE_INVALID                         End pattern is invalid or CMAC verification failed
 * - @ref ecy_hsm_CSAI_ERR_CORE_NOT_VERIFIED                    HSM has not been booted. Neither end pattern nor CMAC has been verified.
 * - @ref ecy_hsm_CSAI_ERR_CORE_PRESENT_INTEGRITY_NOT_CHECKED   End pattern ok, CMAC not verified yet
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_GetCoreAppStatus(void);

/**
 * [$DD 1464]
 * [$Satisfies $ARCH 840]
 * @brief This function gets the maximum number of elements in the trusted boot table on HSM side.
 *
 * @returns number of elements in the trusted boot table on HSM side
 */
uint32 ecy_hsm_TbGetVerifTableMaxNumOfElementsHSM(void);

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

/**
 * @}
 */

#endif /* Multiple inclusion lock  */
