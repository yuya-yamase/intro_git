/**
 * @file
 ***********************************************************************************************
 * @brief temporary header containing macros which should not be visible in delivered headers
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2018, all rights reserved
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_GENERAL_PUBCFG_TEMP_H
#define ECY_HSM_GENERAL_PUBCFG_TEMP_H

#if !defined(GUAM)

#ifdef ENABLED
#if (ENABLED == 1)
// same value as in GUAM
#else
#error ENABLED already defined with different value than required by GUAM host SW
#endif
#else
#define ENABLED 1
#endif

#ifdef DISABLED
#if (DISABLED == 0)
// same value as in GUAM
#else
#error DISABLED already defined with different value than required by GUAM host SW
#endif
#else
#define DISABLED 0
#endif

#ifdef APP
#if (APP == 0)
// same value as in GUAM
#else
#error APP already defined with different value than required by GUAM host SW
#endif
#else
#define APP 0
#endif

#ifdef LIB
#if (LIB == 1)
// same value as in GUAM
#else
#error LIB already defined with different value than required by GUAM host SW
#endif
#else
#define LIB 1
#endif

#ifdef APPLET_TEST_JOBTIME_PROFILE
#if (APPLET_TEST_JOBTIME_PROFILE == DISABLED)
// same value as in GUAM
#else
#error APPLET_TEST_JOBTIME_PROFILE already defined with different value than required by GUAM host SW
#endif
#else
#define APPLET_TEST_JOBTIME_PROFILE DISABLED
#endif

#ifdef ecy_hsm_CSAI_BUILD_TYPE
#if (ecy_hsm_CSAI_BUILD_TYPE == APP)
// same value as in GUAM
#else
#error ecy_hsm_CSAI_BUILD_TYPE already defined with different value than required by GUAM host SW
#endif
#else
#define ecy_hsm_CSAI_BUILD_TYPE APP
#endif

#ifdef ESC_SUPPORT_SAFETY_IN_HSM
#if (ESC_SUPPORT_SAFETY_IN_HSM == DISABLED)
// same value as in GUAM
#else
#error ESC_SUPPORT_SAFETY_IN_HSM already defined with different value than required by GUAM host SW
#endif
#else
#define ESC_SUPPORT_SAFETY_IN_HSM DISABLED
#endif

#ifdef APPLET_TEST_PROFILE
#if (APPLET_TEST_PROFILE == DISABLED)
// same value as in GUAM
#else
#error APPLET_TEST_PROFILE already defined with different value than required by GUAM host SW
#endif
#else
#define APPLET_TEST_PROFILE DISABLED
#endif

#ifdef ecy_hsm_HOST_STORAGE
//  customer choice
#else
/** Host Storage feature support. If not defined, disabled by default */
#define ecy_hsm_HOST_STORAGE DISABLED
#endif

#ifdef ecy_hsm_ENABLE_LEGACY_HOST_PROXY_INTERFACES
//  customer choice
#else
/** Host legacy interface support. If not defined, disabled by default */
#define ecy_hsm_ENABLE_LEGACY_HOST_PROXY_INTERFACES DISABLED
#endif

/* Quick route configuration (ecy_hsm_QUICK_ROUTE) has been moved to ecy_hsm_general_host_cfg.h */

#ifdef TIMING_DIAGNOSTICS
#if (TIMING_DIAGNOSTICS == DISABLED)
// same value as in GUAM
#else
#error TIMING_DIAGNOSTICS already defined with different value than required by GUAM host SW
#endif
#else
#define TIMING_DIAGNOSTICS DISABLED
#endif

#ifdef HSM_BRIDGE_ACCESSIBLE_CHECK
#  if ( DISABLED == HSM_BRIDGE_ACCESSIBLE_CHECK )
// same value as in GUAM
#  else
#error HSM_BRIDGE_ACCESSIBLE_CHECK already defined with different value than required by CycurHSM host SW
#  endif
#else
    /* Default: DISABLED
     * Only affects: TC2xx
     * This should only be enabled, if the HSM Bridge accessible check is necessary, as this worsens the performance of the
     * bridge access, which for example has an impact on the quick route. */
#define HSM_BRIDGE_ACCESSIBLE_CHECK DISABLED
#endif

/**
* @brief Wait loop for placing a quick route job while HSM-Host communication is in transmission state
*
* @details
* If this is enabled, the host driver will immediately return ecy_hsm_CSAI_ERR_QUICK_ROUTE_NOT_POSSIBLE and application must retry later.
* If this is disabled, the host driver will wait for the ongoing transmission of a previous quick route job request before placing the current request with ecy_hsm_NOWAIT_MODE_TRANSMIT_CHECK_DELAY.
*
* @note This is only relevant if ecy_hsm_CSAI_FS_NO_WAIT_MODE is enabled.
*
*/
#ifndef ecy_hsm_NO_WAIT_MODE_QUICK_ROUTE_FORCE_TIMEOUT
    /**
     * Enable / disable Force Timeout for NOWAIT bridge mode during Quick route operations
     */
    #define ecy_hsm_NO_WAIT_MODE_QUICK_ROUTE_FORCE_TIMEOUT                       (ENABLED)
#endif

/**
* @brief Enables wait loop for placing a job while HSM-Host communication is in transmission state
*
* @details
* If this is enabled, the host driver will wait the configured ecy_hsm_NOWAIT_MODE_WAIT_WHEN_IN_TRANSMISSION_DELAY amount before returning ecy_hsm_CSAI_FC_BUSY
* If this is disabled, the host driver will immediately return ecy_hsm_CSAI_FC_BUSY and application must retry later.
*
* @note
* This is only relevant if ecy_hsm_CSAI_FS_NO_WAIT_MODE is enabled.
*
*/
#ifndef ecy_hsm_NOWAIT_MODE_WAIT_WHEN_IN_TRANSMISSION
    /**
     * Enable / disable polling during BUSY
     */
    #define ecy_hsm_NOWAIT_MODE_WAIT_WHEN_IN_TRANSMISSION           (ENABLED)
#endif

#endif /*GUAM*/

#endif /* Multiple inclusion lock ECY_HSM_GENERAL_PUBCFG_TEMP_H */
/* *** history ********************************************************************************/

/*/
 * @history 2014-03-10 [CPL] #2014-03-10CPL. First implementation.
 */
