/**
 * @file
 ***********************************************************************************************
 * @brief This header file defines CycurHSM system constants for the core application.
 * CycurHSM System Constants.
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2019, all rights reserved
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_SESSIONS_PARAMS_CORE_H
#define ECY_HSM_SESSIONS_PARAMS_CORE_H

/* *** includes *******************************************************************************/

#if defined(GUAM)
#include "ecy_hsm_general.h"
#else
#include "ecy_hsm_general_pubcfg.h"
#include "ecy_hsm_csai_vms_pub_data.h"
#endif

/**
 * @addtogroup GROUP_CYCURHSM_SYSTEM_CONSTANTS
 * @{
 */

/* *** defines ********************************************************************************/

#if !defined(GUAM) || (BUILDING != HSM_BOOT_BUILD)
    /* Session parameters for external/delivery builds or internal/GUAM-specific Host and HSM Core builds */

    #if ((ECY_HSM_VMS_FS_APPLET_SHE_CANCEL == ENABLED) && (ECY_HSM_VMS_ARCH_TARGET == ECY_HSM_VMS_ARCH_TARGET_IFX_TC3XX_TC3HX))
        #define ADDITIONAL_SHE_SESSION                              (1U)
    #else
        #define ADDITIONAL_SHE_SESSION                              (0U)
    #endif

    #if !defined(CYCURHSM_SC_MAX_HOST_HSM_SESSIONS)
        /** Define the maximum number of sessions that can be concurrently opened from the host to the HSM */
        #if defined(ECY_HSM_VMS_ARCH_MAX_HOST_SESSIONS_CORE)
            #define CYCURHSM_SC_MAX_HOST_HSM_SESSIONS               (ECY_HSM_VMS_ARCH_MAX_HOST_SESSIONS_CORE + ADDITIONAL_SHE_SESSION)
        #else
            #if (ECY_HSM_VMS_ARCH_TARGET == ECY_HSM_VMS_ARCH_TARGET_IFX_TC2XX_TC23X)
                #define CYCURHSM_SC_MAX_HOST_HSM_SESSIONS           (5U + ADDITIONAL_SHE_SESSION)
            #elif (ECY_HSM_VMS_ARCH_TARGET == ECY_HSM_VMS_ARCH_TARGET_POWER_MPC_MPC5748X)
                #define CYCURHSM_SC_MAX_HOST_HSM_SESSIONS           (5U + ADDITIONAL_SHE_SESSION)
            /* The following targets can only accommodate VKMS with fewer sessions configured */
            #elif (((ECY_HSM_VMS_ARCH_TARGET == ECY_HSM_VMS_ARCH_TARGET_POWER_SPC_SPC58EC84) /* Chorus4M */  \
                || (ECY_HSM_VMS_ARCH_TARGET == ECY_HSM_VMS_ARCH_TARGET_POWER_SPC_SPC58EG84)  /* Chorus6M */  \
                || (ECY_HSM_VMS_ARCH_TARGET == ECY_HSM_VMS_ARCH_TARGET_IFX_TC2XX_TC2HX)      /* TC2Hx    */  \
                || (ECY_HSM_VMS_ARCH_TARGET == ECY_HSM_VMS_ARCH_TARGET_RH850_V1_D3)          /* RH850_D3 */  \
                || (ECY_HSM_VMS_ARCH_TARGET == ECY_HSM_VMS_ARCH_TARGET_RH850_V2_D4)          /* RH850_D4 */  \
                || (ECY_HSM_VMS_ARCH_TARGET == ECY_HSM_VMS_ARCH_TARGET_RH850_V2_D5) )        /* RH850_D5 */  \
            && ((ECY_HSM_VMS_FS_APPLETVKMS == ENABLED) || (ECY_HSM_VMS_FS_APPLETVKMS3 == ENABLED)))
                #define CYCURHSM_SC_MAX_HOST_HSM_SESSIONS           (5U + ADDITIONAL_SHE_SESSION)
            #else
                #define CYCURHSM_SC_MAX_HOST_HSM_SESSIONS           (16U + ADDITIONAL_SHE_SESSION)
            #endif
        #endif /* #if defined(ECY_HSM_VMS_ARCH_MAX_HOST_SESSIONS_CORE) */
    #endif /* #if !defined(CYCURHSM_SC_MAX_HOST_HSM_SESSIONS) */

    #ifndef CYCURHSM_SC_MAX_HSM_INTERNAL_SESSIONS
        /**
         * Define the maximum number of sessions that can be concurrently opened from HSM internal applications
         * @details The internal HSM sessions are numerically after the host sessions in the HSM_BridgePorts array
         */
        #define CYCURHSM_SC_MAX_HSM_INTERNAL_SESSIONS               (1U)
    #endif /* #ifndef CYCURHSM_SC_MAX_HSM_INTERNAL_SESSIONS */

    #ifndef CYCURHSM_SC_MAX_SESSIONS
        /**
         * [$DD 1010]
         * Define the maximum number of sessions that can be concurrently opened in total
         * [$Satisfies $ARCH 322]
         **/
        #define CYCURHSM_SC_MAX_SESSIONS             (CYCURHSM_SC_MAX_HOST_HSM_SESSIONS + CYCURHSM_SC_MAX_HSM_INTERNAL_SESSIONS)
    #endif /* #ifndef CYCURHSM_SC_MAX_SESSIONS*/

    #ifndef CYCURHSM_SC_MAX_MSG_CHUNK_LENGTH
        /**
         * Define the maximum number of bytes that can be processed in one chunk by the HSM.
         **/
        #if defined(CYCURHSM_PC_MAX_MSG_CHUNK_LENGTH)
            #define CYCURHSM_SC_MAX_MSG_CHUNK_LENGTH CYCURHSM_PC_MAX_MSG_CHUNK_LENGTH
        #else
            #define CYCURHSM_SC_MAX_MSG_CHUNK_LENGTH                (32768U)
        #endif

    #endif /* #ifndef CYCURHSM_SC_MAX_MSG_CHUNK_LENGTH */

    /* The maximum number of host sessions in the bootloader mode as defined in "ecy_hsm_sessions_params_boot.h" */
#if ((ECY_HSM_VMS_ARCH_TARGET == ECY_HSM_VMS_ARCH_TARGET_IFX_TC2XX_TC23X) \
      || ((ECY_HSM_VMS_FS_APPLET_GHSM_SECURE_BOOT == ENABLED) && (ECY_HSM_VMS_ARCH_TARGET == ECY_HSM_VMS_ARCH_TARGET_RH850_V2_D4)))
    /* The TC23x is a resource constrained target and a session reduction provides additional RAM for important boot features
     * such as boot cmac check, protections, and secure flashing. Due to the limited feature set, multi-session usage is not required.
     * Multi-session usage is not needed when GM Secure Boot is enabled. 
     * Disable multi-session support in the bootloader for resource constrained targets that support GM Secure Boot. */
    #define ECY_HSM_MAX_NUMBER_OF_HOST_HSM_SESSIONS_IN_BOOTLOADER_MODE  (1U)
#else
    #define ECY_HSM_MAX_NUMBER_OF_HOST_HSM_SESSIONS_IN_BOOTLOADER_MODE  (2U)
#endif

#else /* #if !defined(GUAM) || (BUILDING != HSM_BOOT_BUILD) */
    /* Session parameters for internal/GUAM-specific HSM bootloader builds */
    #error Wrong header file included. Use "ecy_hsm_sessions_params_boot.h" instead.
#endif

/* *** type declarations **********************************************************************/

/* *** global constants ***********************************************************************/

/* *** exported interfaces ********************************************************************/

/**
 * @}
 */

#endif /* ECY_HSM_SESSIONS_PARAMS_CORE_H */
