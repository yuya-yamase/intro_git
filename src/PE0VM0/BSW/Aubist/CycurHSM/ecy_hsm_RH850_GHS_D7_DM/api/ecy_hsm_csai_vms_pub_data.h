/**
 * @file
 ***********************************************************************************************
 * @brief File generated from @ref VMS resource configuration step.
 *
 ***********************************************************************************************

 * @copyright                                 Copyright (c) ETAS GmbH 2023, all rights reserved.

 ***********************************************************************************************/

#ifndef ECY_HSM_CSAI_VMS_PUB_DATA_H
#define ECY_HSM_CSAI_VMS_PUB_DATA_H

/* *** includes *******************************************************************************/
#if defined(GUAM)
#include "ecy_hsm_general.h"
#else
#include "ecy_hsm_general_pubcfg.h"
#endif

/* *** defines ********************************************************************************/

/** Trusted Boot Table size */
#define TB_REF_TABLE_SIZE (12U)

/** Trusted Boot Table version */
#define TB_REF_TABLE_VERSION (1000U)

/** Available P_Flash banks */
#define SMART_TB_PFLASH_BANKS (4U)

/** Trusted Boot Table version */
#define TB_REF_TABLE_VERSION_E (1000U)

/** Trusted Boot Table size */
#define TB_REF_TABLE_SIZE_E (24U)

/** HSM suspend time out */
#define HSM_SUSPEND_TIME (500U)

/** RTMD reactivation power cycle counter limit */
#define RTMD_AUTO_REACTIVATION_POWER_CYCLE_LIMIT (1U)

/** NonceCtrl used in Secure Debug for ecy_hsm_Csai_SecAcc_NonceCtrlT */
#define SECURE_DEBUG_NONCE_CNTRL (2U)

/** This is just a dummy to keep the D-Flash and FEE layout compatible with older versions. */
#define SECURE_DEBUG_USE_CASE_DUMMY (1U)

/** ChallengeLength used in Secure Debug */
#define SECURE_DEBUG_CHALLENGE_LEN (32U)

/** Maximum number of log entries per internal event for the HSM Secure Logging feature - default value is 255 */
#define SECLOG_MAX_NUMBER_OF_EVENT_LOGS_INTERNAL (255U)

/** Maximum number of log entries per external event for the HSM Secure Logging feature - default value is 255 */
#define SECLOG_MAX_NUMBER_OF_EVENT_LOGS_EXTERNAL (255U)

/* (ECY_HSM_VMS_FS_MW_TB_EXTEND_TABLE is DISABLED) */

/* (TIMER_RESOLUTION_MICROSECOND is DISABLED) */
#define ecy_hsm_USE_US_TIMEBASE         DISABLED

#define ecy_hsm_COUNTER_VALUE_TIMEBASE  (1U)


/* (NO_WAIT_MODE is ENABLED) */
#define ECY_HSM_VMS_FS_HOST_NO_WAIT_MODE               ENABLED

#if !defined(GUAM)

/* (HwCsp Applet is DISABLED) */
#define ECY_HSM_VMS_FS_APPLETHWCSP                     DISABLED

/* (HwCsp feature Load/Release Key is DISABLED) */
#define ECY_HSM_VMS_FS_APPLET_HWCSP_LOAD_RELEASE_KEY   DISABLED

/** VKMS feature switch */
#define ECY_HSM_VMS_FS_APPLETVKMS                      DISABLED

/** VKMS3 feature switch */
#define ECY_HSM_VMS_FS_APPLETVKMS3                     DISABLED

/** SHE Cancel feature switch */
#define ECY_HSM_VMS_FS_APPLET_SHE_CANCEL               DISABLED

/** SHE Debug Unlock feature switch */

#define ECY_HSM_VMS_FS_APPLET_SHE_DEBUG_UNLOCK         ENABLED

/** Pseudo Random Generate feature switch */
#define ECY_HSM_VMS_FS_APPLET_PSEUDO_RANDOM_GENERATE   ENABLED

/** HSM Reprog Singleshot feature switch */
#define ECY_HSM_VMS_FS_SECFLASH_HSM_REPROG_SINGLESHOT  DISABLED

/** GM Secure Boot feature switch */
#define ECY_HSM_VMS_FS_APPLET_GHSM_SECURE_BOOT  DISABLED

#endif /* if !defined(GUAM) */

/* *** type declarations **********************************************************************/

#endif /* ECY_HSM_CSAI_VMS_PUB_DATA_H */
