/**
 * @file
 * @brief system applet interface
 */

/***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2014, all rights reserved
 **********************************************************************************************/

#ifndef ESC_HSM_APPLET_SYSTEM_H
#define ESC_HSM_APPLET_SYSTEM_H

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
 * @brief Possible states for session handling applet
 *
 * @details
 * @section APPLET_SESSION session handling applet
 *
 * @image html ./states_system.png "State diagram of applet: Session handling" width=15cm
 * @image rtf  ./states_system.png "State diagram of applet: Session handling" width=15cm
 */
typedef enum Applet_System_StateT
{
    /* Please note that SessionOpen uses a direct ISR signal to HSM
     * rather than a regular job, therefore it's not part of the applet
     */
    APPLET_SYSTEM_STATE_SESSION_CLOSE_E,               /**< close session */
    APPLET_SYSTEM_STATE_SESSION_QUERY_E,               /**< query session stSession */
    APPLET_SYSTEM_STATE_JOB_CANCEL_E,                  /**< cancel a job */
    APPLET_SYSTEM_STATE_VERSION_QUERY_E,               /**< query HSM version */
    APPLET_SYSTEM_STATE_DIAGNOSE_QUERY_E,              /**< query HSM diagnostic data */
    APPLET_SYSTEM_STATE_SETSERIALNO_E,                 /**< query HSM diagnostic data */
    APPLET_SYSTEM_STATE_GETDEVICEID_E,                 /**< query HSM diagnostic data */
    APPLET_SYSTEM_STATE_CONFIG_READ_GENDATA_E,         /**< read generic data from config */
    APPLET_SYSTEM_STATE_READ_REGISTER_E,               /**< read HSM register content */
    APPLET_SYSTEM_STATE_VERIFY_FIRMWARE_E,             /**< query HSM verification state */
    APPLET_SYSTEM_STATE_VERSION_QUERY_FORMAT_ID_E,     /**< query HSM version information based on format ID. */
    APPLET_SYSTEM_STATE_POWER_MODE_CONFIG_E,           /**< configure power mode */
    APPLET_SYSTEM_STATE_FEEMGR_TRIGGER_REORG_E,        /**< trigger FEE reorg manually */
    APPLET_SYSTEM_STATE_FEEMGR_CHECK_REORG_ON_WRITE_E, /**< check for number of FEE writes before reorganisation */
    APPLET_SYSTEM_STATE_SYSTEM_VERIFICATION_VALUE,     /**< Fetch part verification values for the system */
    APPLET_SYSTEM_STATE_VERIFY_REGISTER_E,             /**< Verify the requested register addresses  */
    APPLET_SYSTEM_STATE_VERIFY_HSM_CONFIGURATION_E ,   /**< Verify HSM configuration area */
    /* This needs to be the final entry */
    APPLET_SYSTEM_NUMSTATES_E      /**< number of states */
} Applet_System_StateT;


/*
**********************************************************************************************************************
* Extern declarations
**********************************************************************************************************************
*/
/**
 * Parameter union type for system applet
 */
/* PRQA S 0750 2 */ /* <Deviation: definition of union is appropriate here */
typedef union {
    HSM_SessionStatusT              stSession;               /**< Parameters for session state query */
    HSM_GetVersionParamT            stVersion;               /**< Parameters for HSM version query */
    HSM_GetDiagnosticsParamT        stDiag;                  /**< Parameters for HSM diagnostic request */
    HSM_SetSerialNoParamT           stSetSerialNo;           /**< Parameters for Setting of the Serial No */
    HSM_GetDeviceIdParamT           stGetDeviceId;           /**< Parameters for Getting the Device ID */
    HSM_ConfigReadGenericDataParamT stConfigReadGenericData; /**< Parameters for Getting generic data from config */
    HSM_SystemReadRegisterParamT    stReadRegisterData;      /**< Parameters for reading HSM register content */
    HSM_VerifyFirmwareT             stVerificationState;     /**< Parameters for Getting the verification state of the HSM firmware */
    HSM_GetVersionAndEncodingParamT stGetVersion;            /**< Parameters for HSM version query */
    HSM_PowerModeConfigDataParamT   stPowerModeConfigData;   /**< Parameters for configuring power mode */
    HSM_FEEManagerCheckReorgParamT  stCheckReorgOnWriteData; /**< Parameters within a structure for the FEE check for reorganisation */
    HSM_PartVerificationDataParamT  stPartVerificationData;  /**< Parameter to fetch part verification information */
    HSM_VerifyRegisterParamT        stVerifyRegister;        /**< Parameter to verify the requested register values */
} Applet_SystemParamT;

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @brief SESSION applet control structures
 */
extern const Applet_ts Applet_System_HSM;

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @}
 */
#endif // ECY_HSM_APPLET_SYSTEM_H
