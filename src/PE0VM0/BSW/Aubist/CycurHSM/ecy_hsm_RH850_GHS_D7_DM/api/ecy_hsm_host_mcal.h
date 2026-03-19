/* Int Hint : File from cycurHSM at : hsm_host\hsm_proxy\include\hsm_proxy_mcal.h*/
/* $Id$ */
/**
 * @file
 ***********************************************************************************************
 * @brief This header file if for definitions that are internal to the HSM Proxy Client
 *

 ***********************************************************************************************
 * @copyright                     Copyright (c) 2014 ESCRYPT GmbH, Bochum. All rights reserved.
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_HOST_MCAL_H
#define ECY_HSM_HOST_MCAL_H

#include "ecy_hsm_service_basic.h"
#include "ecy_hsm_service_misc.h"

/**
 * @addtogroup GROUP_HSM_PROXY_MCAL_TYPES
 * @{
 */

/* *** includes *******************************************************************************/

/* *** defines ********************************************************************************/

/* *** type declarations **********************************************************************/

/* *** global constants ***********************************************************************/

/* *** exported interfaces ********************************************************************/

/* *INDENT-OFF* */
#ifdef __cplusplus
    extern "C" {
#endif
/* *INDENT-ON* */

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/**
 * [$DD 1470]
 * [$Satisfies $ARCH 461]
 * Get the operational mode of the HSM Core
 *
 * @returns
 * - @ref HSM_MODE_INVALID                     Both the bootloader and the core app bits are set
 * - @ref HSM_MODE_NOT_STARTED                 The HSM core has not been started
 * - @ref HSM_MODE_BOOTLOADER                  The HSM core is in bootloader mode
 * - @ref HSM_MODE_CORE_APP                    The HSM core application is running
 * - @ref HSM_MODE_BOOTING                     The HSM is neither in core nor in bootloader nor suspended
 * - @ref HSM_MODE_SUSPENDED                   The HSM is in suspend mode
 * - @ref HSM_MODE_CORE_APP_STOPPED            An error occurred and HSM stopped
 * - @ref HSM_MODE_SWITCHING_FROM_CORE_TO_BOOT An update was triggered and the HSM is in
 *                                             transition to bootloader
 * [$Satisfies $SW_ARCH 905]
 */
HSM_ModeT ecy_hsm_HsmMCAL_GetMode(void);

/**
 * Extracts critical errors reported by the HSM core via the HSM2Host flags register. Concrete errors can be extracted
 * by masking the single bits
 * with the provided HSM2HTS_ERR_* defines.
 *
 * @returns A numeric value representing the critical error(s) reported by the HSM core. Zero indicates that no error
 * was reported.
 */
uint32 ecy_hsm_HsmMCAL_GetCoreErrorFlags(void);

/**
 * Check the @ref HSM2HTS_BOOTED flag of the HSM2Host flags register
 *
 * @returns @c TRUE if the HSM has booted, @c FALSE if the HSM has not booted
 */
boolean ecy_hsm_HsmMCAL_IsBooted(void);

/**
 * Check the @ref HSM2HTS_CONFIGURED flag of the HSM2Host flags register
 *
 * @returns @c TRUE if the HSM has been configured, @c FALSE if the HSM has not been configured
 */
boolean ecy_hsm_HsmMCAL_IsConfigured(void);

/**
 * Check the @ref HSM2HTF_SUSPEND_SHARED_RAM_WRITE flag of the HSM2Host flags register
 *
 * @returns @c TRUE if shared ram write is suspended, @c FALSE if shared ram write is not suspended
 */

boolean ecy_hsm_HsmMCAL_IsSuspendedSharedRamWrite(void);

/**
 * Check the @ref HSM2HTS_CLOCK_CONFIGURED flag of the HSM2Host flags register
 *
 * @returns @c TRUE if the HSM clock has been configured, @c FALSE if the HSM clock has not been configured
 */
boolean ecy_hsm_HsmMCAL_IsClockConfigured(void);

/**
 * Check the @ref HT2HSMF_SESSION_OPEN flag of the Host2HSM flags register
 * @details Use this function to get the status after triggering the open session interrupt
 *
 * @returns @c TRUE if the session has been opened, @c FALSE if still waiting for the session to be opened
 */
boolean ecy_hsm_HsmMCAL_IsSessionOpen(void);

/**
 * Check the @ref HSM2HTF_CANCELLED flag of the HSM2Host flags register
 * @details Use this function to get the status after triggering the cancel operation interrupt
 *
 * @returns @c TRUE if the operation has been cancelled, @c FALSE if still waiting for the operation to be cancelled
 */
boolean ecy_hsm_HsmMCAL_IsOperationCancelled(void);

/**
 * Do the hardware-specific part of requesting the HSM to switch into bootloader mode
 */
void ecy_hsm_HsmMCAL_SwitchToBootloader(void);

/**
 * [$DD 1468]
 * Do the hardware-specific part of telling the HSM what clock divider to use.
 * Includes a host-side check that the specified divider appears to be valid for this target
 *
 * @param[in] divider Value for the HSM clock divider, 5 causes a divide by six
 *
 * @returns
 * - @ref ecy_hsm_CSAI_SUCCESS Completed without errors
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM divider had an invalid value
 *
 * [$Satisfies $ARCH 458]
 */
ecy_hsm_Csai_ErrorT ecy_hsm_HsmMCAL_ClockConfigure(uint32 divider);

/**
 * Do the hardware-specific part of telling HSM to suspend writing to shared memory
 *
 * @param[in] pSuspendSharedRamOpParams Const pointer to shared configuration structure
 */
void ecy_hsm_HsmMCAL_SuspendSharedRamWrite(const volatile HSM_HostSideSuspendSharedRamParamsT* pSuspendSharedRamOpParams);

/**
 * Check if the HSM has acknowledged the suspend writing to shared memory request
 *
 * @details
 * This function checks if the HSM has actually acknowledged a suspend writing to shared memory
 * request that was send earlier.
 *
 * @returns TRUE if the HSM has acknowledged a @ref ecy_hsm_IpcDrv_SendEvents(@ref HT2HSMF_SUSPEND_SHARED_RAM_WRITE);
 */

boolean ecy_hsm_IsSuspendSharedRamWrite_Acknowledged(void);

/**
 * Check if the HSM has acknowledged the clock configuration request
 *
 * @details
 * This function checks if the HSM has actually aknowledged a clock configuration request that was send earlier.
 *
 *
 * @returns TRUE if the HSM has acknowledged a @ref ecy_hsm_IpcDrv_SendEvents(@ref HT2HSMF_CLOCK_CONFIG);
 */
boolean ecy_hsm_IsClockConfigure_Acknowledged(void);


#if (ecy_hsm_HOST_STORAGE == ENABLED)

/**
 * Check if the HSM has acknowledged the host storage configuration request.
 *
 * @details
 * This function checks if the HSM has actually acknowledged a host storage configuration request that was sent earlier.
 *
 * @return      boolean to signal the acknowledgement status of a host storage configuration request.
 * @retval      TRUE        The HSM has acknowledged a  ecy_hsm_IpcDrv_SendEvents(HT2HSMF_HOST_STORAGE_CONFIG).
 * @retval      FALSE       The HSM has not acknowledged a  ecy_hsm_IpcDrv_SendEvents(HT2HSMF_HOST_STORAGE_CONFIG).
 */
boolean ecy_hsm_IsHostStorageConfigure_Acknowledged(void);

#endif /* #if (ecy_hsm_HOST_STORAGE == ENABLED) */

/**
 * Do the hardware-specific part of configuring the HSM
 * @details This means telling the HSM where it's shared memory regions are
 *
 * @param[in] pBridgeConfiguration Pointer to bridge configuration structure
 */
void ecy_hsm_HsmMCAL_Configure(const volatile HSM_BridgeConfigurationT* pBridgeConfiguration);

/**
 * Check if the HSM has acknowledged the configuration request
 *
 * @details
 * This function checks if the HSM has actually aknowledged a configuration request that was send earlier.
 *
 *
 * @returns TRUE if the HSM has acknowledged a ecy_hsm_IpcDrv_SendEvents(HT2HSMF_CONFIGURE);
 */
boolean ecy_hsm_IsConfigure_Acknowledged(void);

/**
 * Do the hardware-specific part of loading an operation on to the HSM
 *
 * @param[in] hJob Handle of the job operation to be loaded on to the HSM
 */
void ecy_hsm_HsmMCAL_LoadOp(ecy_hsm_Csai_JobHandleT hJob);

/**
 * Do the hardware-specific part of loading a management operation on to the HSM
 * @details Unlike regular operations, only one management operation can be performed at a time.
 */
void ecy_hsm_HsmMCAL_MgmtLoadOp(void);

/**
 * Do the hardware-specific part of opening a session with the HSM
 *
 * @param[in] pSessionOpen Address of structure containing the parameters of the session
 *                         opening.  Gets written to the Host2HSM status register.
 */
void ecy_hsm_HsmMCAL_OpenSession(const volatile HSM_SessionOpenT* pSessionOpen);


/**
 * Do the hardware-specific part of cancelling an operation on the HSM
 *
 * @param[in] hSession Session on which to cancel the last/current operation
 */
void ecy_hsm_HsmMCAL_CancelOp(ecy_hsm_Csai_SessionHandleT hSession);


/**
 * Do the hardware specific bit of setting the HSM Release flag
 *
 * @returns ecy_hsm_CSAI_SUCCESS
 */
ecy_hsm_Csai_ErrorT ecy_hsm_HsmMCAL_Release(void);

/**
 * Signal HSM to do a software reset
 *
 * @details This function will send the @ref HT2HSMF_RESET flag to the Host2HSM status register.
 *          Use @ref ecy_hsm_HsmMCAL_IsResetAcknowledged to check if it was acknowledged correctly.
 * @note    The Softreset can only be triggered at the end of a secflash operation.
 *
 * @returns ecy_hsm_CSAI_SUCCESS
 */
ecy_hsm_Csai_ErrorT ecy_hsm_HsmMCAL_SoftReset(void);

/**
 * Check the @ref HT2HSMF_RESET flag of the HSM2Host status register
 * @details Use this function to get the status after requesting a HSM softreset using @ref ecy_hsm_HsmMCAL_Softreset.
 *
 * @returns @c TRUE if the HSM soft reset has been acknowledged, otherwise @c FALSE
 */
boolean ecy_hsm_HsmMCAL_IsResetAcknowledged( void );

/**
 * Do the hardware specific bit of setting the Quick Route request flag and writing the
 * session number into the HT2HSMS (PE2ICUS) register
 *
 * @param[in] hSession Session on which to load the quick-route operation
 */
void ecy_hsm_HsmMCAL_LoadQuickRoute(ecy_hsm_Csai_SessionHandleT hSession);

/**
 * Do the hardware specific bit of setting the HSM Suspend flag
 *
 * @returns ecy_hsm_CSAI_SUCCESS
 */
ecy_hsm_Csai_ErrorT ecy_hsm_HsmMCAL_Suspend(void);

/**
 * Check the @ref HSM2HTF_SUSPEND flag of the HSM2Host flags register
 * @details Use this function to get the status after requesting HSM suspend
 *
 * @returns @c TRUE if the HSM is suspended, otherwise @c FALSE
 */
boolean ecy_hsm_HsmMCAL_IsSuspended(void);

/**
 * Do the hardware specific bit of setting the HSM maintenance flag
 *
 * @returns ecy_hsm_CSAI_SUCCESS
 */
ecy_hsm_Csai_ErrorT ecy_hsm_HsmMCAL_DoMaintenance(void);

/**
 * Check the @ref HSM2HTF_MTNC_REQUEST flag of the HSM2Host status register
 * @details Use this function to get the status after requesting HSM maintenance
 *
 * @returns @c TRUE if the HSM maintenance has completed, otherwise @c FALSE
 */
boolean ecy_hsm_HsmMCAL_IsMaintenanceDone(void);

/**
 * Check the @ref HT2HSMF_MTNC_REQUEST flag of the Host2HSM status register
 * @details Use this function to get the status of the HSM maintenance request
 * (the flag is reset by the HSM after accepting the request and starting the maintenance)
 *
 * @returns @c TRUE if the HSM maintenance has started, otherwise @c FALSE
 */
boolean ecy_hsm_HsmMCAL_IsMaintenanceStarted(void);

/**
 * Do the hardware specific bit of setting the HSM suspend flag
 *
 * @param[in] pSuspendParams Pointer to host side suspend parameter structure
 *
 * @returns ecy_hsm_CSAI_SUCCESS
 */
ecy_hsm_Csai_ErrorT ecy_hsm_HsmMCAL_DoSuspendOp(const HSM_HostSideSuspendParamsT *pSuspendParams);

/**
 * Check the @ref HSM2HTS_SUSPEND flag of the HSM2Host status register
 * @details Use this function to get the status after requesting HSM suspend operation
 *
 * @returns @c TRUE if the HSM suspend operation has completed, otherwise @c FALSE
 */
boolean ecy_hsm_HsmMCAL_IsSuspendOpDone(void);

/**
 * Check the @ref HSM2HTS_SUSPEND flag of the Host2HSM status register
 * @details Use this function to get the status of the HSM suspend request
 * (the flag is reset by the HSM after accepting the request and starting the request)
 *
 * @returns @c TRUE if the HSM suspend operation has started, otherwise @c FALSE
 */
boolean ecy_hsm_HsmMCAL_IsSuspendOpStarted(void);

/**
 * Trigger a Disable Security Critical Functions request
 *
* @param[in] hSession Session for the disable operation
 *
 * @returns ecy_hsm_CSAI_SUCCESS
 */
ecy_hsm_Csai_ErrorT ecy_hsm_HsmMCAL_DoDisableSecCritOp( ecy_hsm_Csai_SessionHandleT hSession );


/**
 * Do the configuration of Secure debug challenge and response related data buffer
 *
 * @param[in] pDebugConfigParam Pointer to host side debug configuration parameter structure
 *
 * @returns ecy_hsm_CSAI_SUCCESS
 */
ecy_hsm_Csai_ErrorT ecy_hsm_HsmMCAL_DoSecureDebugConfigureOp( const HSM_SecureDebugConfigureParamsT *pDebugConfigParam );

/**
 * Check the @ref HSM2HTF_SECDEBUG_CONFIGURE flag of the HSM2HOST status register
 * @details Use this function to get the status after requesting secure debug configuration operation
 *
 * @returns @c TRUE if the secure debug configuration operation has completed, otherwise @c FALSE
 */
boolean ecy_hsm_HsmMCAL_IsSecureDebugConfigureDone(void);

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

#endif /* Multiple inclusion lock  */

/* *** history ********************************************************************************/

/*/
 * @history 2014-04-18 [MMc] First implementation.
 */
