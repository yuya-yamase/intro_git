/**
 * @file ecy_hsm_general_host_cfg.h
 ***********************************************************************************************
 * @brief CycurHSM HOST configuration file
 * Header containing macros used in the host driver
 *
 ***********************************************************************************************
 * @copyright                     Copyright (c) 2020 ESCRYPT GmbH, Bochum. All rights reserved.
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_GENERAL_HOST_CFG_H
#define ECY_HSM_GENERAL_HOST_CFG_H

#include "ecy_hsm_csai_vms_pub_data.h"

/* Default Qualified value : ecy_hsm_QUICK_ROUTE = ENABLED */
#ifndef ecy_hsm_QUICK_ROUTE
    /**
     * Enable / disable QuickRoute operations
     */
    #define ecy_hsm_QUICK_ROUTE                                     (ENABLED)
#endif

/* This macro will be used for our internal GUAM environment */
/* Default Qualified value : ecy_hsm_QUICK_ROUTE_FAILFAST = DISABLED */
#ifndef ecy_hsm_QUICK_ROUTE_FAILFAST
    /**
     * Enable / disable QuickRoute fail-fast switch
     */
    #define ecy_hsm_QUICK_ROUTE_FAILFAST (DISABLED)
#endif

/**
* @brief Upper limit for maximum block size "quick route"
*
*/
#define ecy_hsm_MAX_QUICK_ROUTE_BYTES_UPPER_LIMIT           (512U)

/* In case customer configure ecy_hsm_MAX_QUICK_ROUTE_BYTES higher than the upper limit prompt error */
#if (ecy_hsm_MAX_QUICK_ROUTE_BYTES > ecy_hsm_MAX_QUICK_ROUTE_BYTES_UPPER_LIMIT)
#error "ecy_hsm_MAX_QUICK_ROUTE_BYTES exceededs the upper limit(512 bytes)"
#endif

/* In case customer configure ecy_hsm_MAX_QUICK_ROUTE_BYTES to 0 prompt error */
#if (ecy_hsm_MAX_QUICK_ROUTE_BYTES == 0U)
#error "0 is not a valid value for ecy_hsm_MAX_QUICK_ROUTE_BYTES. Please set ecy_hsm_QUICK_ROUTE to DISABLED if you want to disable the quick route."
#endif

/* Default Qualified value : ecy_hsm_WAIT_FOR_MODE_WATCH_DOG = ENABLED */
#ifndef ecy_hsm_WAIT_FOR_MODE_WATCH_DOG
    /**
     * Enable / disable @ref ecy_HSM_WaitForModeWD interface support Watchdog Caller
     */
    #define ecy_hsm_WAIT_FOR_MODE_WATCH_DOG                                     (ENABLED)
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
 * The macro is by default set to ECY_HSM_VMS_FS_HOST_NO_WAIT_MODE whose value comes from the VMS configuration.
 *  This can be changed by user to set appropriate bridge mode
 */
#define ecy_hsm_CSAI_FS_NO_WAIT_MODE                          ECY_HSM_VMS_FS_HOST_NO_WAIT_MODE

/* NOTE : When ecy_HSM_STARTUP_DELAY is used as input for ecy_HSM_WaitForMode() API, the time scale resolution switch to microsecond/millisecond for this input timeout value
 * based on configuration is already handled in ecy_HSM_WaitForMode(), so ecy_HSM_STARTUP_DELAY need not be scaled again using ecy_hsm_COUNTER_VALUE_TIMEBASE here
 */

#define ecy_HSM_STARTUP_DELAY        (1000u)   /**< @deprecated: Number of milliseconds to wait for the HSM to start - only takes this long when booting with erased data EEPROM */

/* The configuration delay may need to be increased when secure boot is activated because the HSM Core App startup time can
 * be significantly increased due to time necessary to check the secure boot configured SW-parts (depending on their size)
 */
#define ecy_HSM_CONFIGURATION_DELAY (100U * ecy_hsm_COUNTER_VALUE_TIMEBASE) /**< Number of milliseconds to wait for the HSM to be configured */

/* Default value described in the user guide is the qualified value and if it is changed from that
 * then it must be qualified in the project side.
 * The proxy delays are documented in $ARCH 115
 */
# if(ECY_HSM_VMS_ARCH_FAMILY == ECY_HSM_VMS_ARCH_FAMILY_RH850)
/* @deprecated: Only required for backwards compatibility. */
#define ecy_HSM_PROXY_DELAY          (6u*ecy_hsm_COUNTER_VALUE_TIMEBASE)      /**< Number of milliseconds to wait for simple HSM functions */
# else
#define ecy_HSM_PROXY_DELAY          (5u*ecy_hsm_COUNTER_VALUE_TIMEBASE)      /**< Number of milliseconds to wait for simple HSM functions */
# endif /* if(ECY_HSM_VMS_ARCH_FAMILY == ECY_HSM_VMS_ARCH_FAMILY_RH850) */

/* Check for valid configurations of ecy_HSM_PROXY_DELAY in case ecy_hsm_USE_US_TIMEBASE is ENABLED.
 * NOTE : If other timing values are to be tested, remove the below warning but take note that its not qualified.
 */
#if (ecy_hsm_USE_US_TIMEBASE == ENABLED)
#  if (   ((ECY_HSM_VMS_ARCH_FAMILY == ECY_HSM_VMS_ARCH_FAMILY_RH850) && (ecy_HSM_PROXY_DELAY != 6000)) \
       || ((ECY_HSM_VMS_ARCH_FAMILY != ECY_HSM_VMS_ARCH_FAMILY_RH850) && (ecy_HSM_PROXY_DELAY != 5000)) )

     /* PRQA S 3115 1 */ /*< Deviation: rule_20.13_3115 */
#    warning  not configured with the default value as suggested by vendors
#  endif
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

/* Below mentioned definitions are required only when ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED */
#if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED)
#if (ecy_hsm_USE_US_TIMEBASE == ENABLED)
    #ifndef ecy_hsm_NOWAIT_MODE_WAIT_WHEN_IN_TRANSMISSION_DELAY
        /**
        ** The host driver will wait the configured ecy_hsm_NOWAIT_MODE_WAIT_WHEN_IN_TRANSMISSION_DELAY in microsecond(us) before returning ecy_hsm_CSAI_FC_BUSY if ecy_hsm_NOWAIT_MODE_WAIT_WHEN_IN_TRANSMISSION is enabled.
        */
        #define ecy_hsm_NOWAIT_MODE_WAIT_WHEN_IN_TRANSMISSION_DELAY   120u
    #endif
    #ifndef ecy_hsm_NOWAIT_MODE_TRANSMIT_CHECK_DELAY
        /**
        * Number of us to wait to get transmission buffer
        */
        #define ecy_hsm_NOWAIT_MODE_TRANSMIT_CHECK_DELAY              120u    /* Number of us to wait to get transmission buffer */
    #endif
#else
    /* Waitloop in Milliseconds will lead in a task timeout!*/
    #ifndef ecy_hsm_NOWAIT_MODE_WAIT_WHEN_IN_TRANSMISSION_DELAY
        /**
         *The host driver will wait the configured ecy_hsm_NOWAIT_MODE_WAIT_WHEN_IN_TRANSMISSION_DELAY in millisecond(ms) before returning ecy_hsm_CSAI_FC_BUSY if ecy_hsm_NOWAIT_MODE_WAIT_WHEN_IN_TRANSMISSION is enabled.
         */
        #define ecy_hsm_NOWAIT_MODE_WAIT_WHEN_IN_TRANSMISSION_DELAY   2u
    #endif
    #ifndef ecy_hsm_NOWAIT_MODE_TRANSMIT_CHECK_DELAY
        /**
         * Number of us to wait to get transmission buffer
         */
        #define ecy_hsm_NOWAIT_MODE_TRANSMIT_CHECK_DELAY              2u      /* Number of ms to wait to get transmission buffer */
    #endif
#endif /* (ecy_hsm_USE_US_TIMEBASE == ENABLED) */
#endif /* #if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED) */

#ifdef ecy_hsm_HOST_STORAGE
//  customer choice
#else
/** Host Storage feature support. If not defined, disabled by default */
#define ecy_hsm_HOST_STORAGE (DISABLED)
#endif

#ifdef ecy_hsm_ENABLE_LEGACY_HOST_PROXY_INTERFACES
//  customer choice
#else
/** Host legacy interface support. If not defined, disabled by default */
#define ecy_hsm_ENABLE_LEGACY_HOST_PROXY_INTERFACES (DISABLED)
#endif

/** Global switch to enable error handling in HSM bridge resource locking and unlocking. Error handling will check that
 * the resource is never falsely locked or unlocked twice.
 */
#ifndef ecy_hsm_ENABLE_RESOURCE_ERROR_HANDLING
    /**
     * Enable / disable HSM bridge resource locking/unlocking error handling
     */
    #define ecy_hsm_ENABLE_RESOURCE_ERROR_HANDLING                  (DISABLED)
#endif

/**
 * Global switch to enable Quickroute Mac Generation and Verification using the Host Hardware Crypto Service Provider.
 * This is a Customer Choice, and it is disabled by default.
 */
#ifndef ecy_hsm_CUSTOMER_HOST_HWCSP_MAC_QUICK
/**
 * Enable / disable Host HwCsp Quickroute Mac.
 */
# define ecy_hsm_CUSTOMER_HOST_HWCSP_MAC_QUICK (DISABLED)
#endif

/**
 * Allow the User to enable Host HwCsp features if HwCsp is enabled
 */
/* Customer has requested that Host HwCsp Mac Quickroute be enabled */
#if (ENABLED == ecy_hsm_CUSTOMER_HOST_HWCSP_MAC_QUICK)
/* HwCsp Enabled */ /* HwCsp feature load release key is required */
# if ((ENABLED == ECY_HSM_VMS_FS_APPLETHWCSP) && (ENABLED == ECY_HSM_VMS_FS_APPLET_HWCSP_LOAD_RELEASE_KEY))
/** Customer has requested that this Host HwCsp feature be enabled AND the preconditions for this have been met -> enable feature */
#  define ecy_hsm_HOST_HWCSP_MAC_QUICK (ENABLED)
# else
/** Customer has requested that this Host HwCsp feature be enabled AND the preconditions for this have NOT been met -> set to disabled */
# define ecy_hsm_HOST_HWCSP_MAC_QUICK (DISABLED)
# endif
#else
/** Customer has requested that this Host HwCsp feature NOT be enabled -> set to disabled */
# define ecy_hsm_HOST_HWCSP_MAC_QUICK (DISABLED)
#endif

#endif /* ECY_HSM_GENERAL_HOST_CFG_H */
