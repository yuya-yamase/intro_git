/**
 * @file
 ***********************************************************************************************
 * @brief ECY HSM CSAI Trusted boot operations
 * This header file is part of the Trusted Boot Interface and specifies types and functions
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2017, all rights reserved
 **********************************************************************************************/

#ifndef ECY_HSM_CSAI_TRUST_BOOT_H
#define ECY_HSM_CSAI_TRUST_BOOT_H

/**
 * @addtogroup GROUP_CSAI_TRUST_BOOT
 * @{
 */

/* *** includes *******************************************************************************/
#include "Std_Types.h"
#include "ecy_hsm_csai.h"
#include "ecy_hsm_csai_vms_pub_data.h"
#include "ecy_hsm_csai_keyid.h"
#include "ecy_hsm_service_crypt_types.h"

/**
 * @image html states_TrustedBoot_Verify.png "Verification States of a SW- Parts (Shared-RAM)"
 * @image rtf states_TrustedBoot_Verify.png "Verification States of a SW- Parts (Shared-RAM)"
 */
/* *** defines ********************************************************************************/

/* Compatibility macros: old function names are still supported to ensure compatibility with previous releases */
/** Backwards compatibility macro. @deprecated by @ref ecy_hsm_Csai_TbRequestSwVerification */
#define ecy_hsm_CSAI_TB_RequestSwVerification(p1,p2,p3,p4,p5)       ecy_hsm_Csai_TbRequestSwVerification(p1,p2,p3,p4,p5)
/** Backwards compatibility macro. @deprecated by @ref ecy_hsm_Csai_TbGetSwIdStatus */
#define ecy_hsm_CSAI_TB_GetSwIdStatus(p1,p2,p3,p4,p5,p6,p7)         ecy_hsm_Csai_TbGetSwIdStatus(p1,p2,p3,p4,p5,p6,p7)
/** Backwards compatibility macro. @deprecated by @ref ecy_hsm_Csai_TbEndOfBootChain */
#define ecy_hsm_CSAI_TB_EndOfBootChain(p1,p2,p3)                    ecy_hsm_Csai_TbEndOfBootChain(p1,p2,p3)

/* FROM HERE: This Defines will be removed after be set in a global config data*/

/** Define TB boot verification modes */
#define ecy_hsm_CSAI_TB_BOOT_MODE_BOOTABLE                                       ((uint8)0x01) /**< SW part is responsible for Host boot */
#define ecy_hsm_CSAI_TB_BOOT_MODE_SECURE                                         ((uint8)0x02) /**< SW part is marked for secure boot */
#define ecy_hsm_CSAI_TB_BOOT_MODE_AUTHENTIC                                      ((uint8)0x04) /**< SW part is marked for authentic boot */
#define ecy_hsm_CSAI_TB_BOOT_MODE_RTMD_ONCE                                      ((uint8)0x08) /**< SW part is marked for a first run of RTMD */
#define ecy_hsm_CSAI_TB_BOOT_MODE_RTMD_CONT                                      ((uint8)0x10) /**< SW part is marked for a continuous RTMD */
#define ecy_hsm_CSAI_TB_BOOT_MODE_AUTHENTIC_EXTENDED_RESET                       ((uint8)0x20) /**< SW part is marked for authentic boot. If not authentic, ECU will reset */
#define ecy_hsm_CSAI_TB_BOOT_MODE_SECURE_WITH_DIRECT_RELEASE                     ((uint8)0x40) /**< SW part is marked for secure boot with direct release */
#define ecy_hsm_CSAI_TB_EXT_BOOT_MODE_FAILSAFE                                   ((uint16)0x1000) /**< Failsafe SW part type */

/** Defines necessary to extend the verification mirror table */
#define ecy_hsm_CSAI_TB_VER_HOST_PATTERN     0xDEAD0000U /**< HOST sided handshake pattern */
#define ecy_hsm_CSAI_TB_VER_HSM_PATTERN      0xBEEF0000U /**< HSM sided handshake pattern */
#define ecy_hsm_CSAI_TB_VER_PATTERN_MSK      0xFFFF0000U /**< Bitmask for handshake patterns */
#define ecy_hsm_CSAI_TB_VER_VERSION_MSK      0x0000FFFFU /**< Bitmask of version information */

/** Default (legacy) size of Trusted boot reference table */
#define ecy_hsm_CSAI_TB_REF_TABLE_SIZE_LEGACY       12

/** Signature verification modes (as defined in field @ref SwPartVerifSignMode)
 * @internal
 * @note If these values are updated, please consider updating the corresponding enumeration
 *       values of @ref SW_PART_TABS_SIGN_MODE in the cfg_intdata.yml file as well.
 * @endinternal
 */
#define ecy_hsm_CSAI_TB_VERIFMODE_NONE                                   ((uint8)0U) /**< TABS verification is disabled (must be 0 for backward-compatibility) */
#define ecy_hsm_CSAI_TB_VERIFMODE_MEMMAPPED_CERT                         ((uint8)1U) /**< Memory-mapped certificate mode */
#define ecy_hsm_CSAI_TB_VERIFMODE_KEYSTORE_PUBKEY                        ((uint8)2U) /**< Keystore-based public key mode */
#define ecy_hsm_CSAI_TB_VERIFMODE_KEYSTORE_CERT                          ((uint8)3U) /**< Keystore-based certificate mode */
#define ecy_hsm_CSAI_TB_VERIFMODE_MANUAL_HEADER_BASED_VERIFICATION_V1    ((uint8)4U) /**< Manual header based SwPart verification version 1 */

/** Sw part properties */
#define ecy_hsm_CSAI_TB_PROP_NONE                                        ((uint8)0x00U) /**< No distinctive properties assigned to SW part       */
#define ecy_hsm_CSAI_TB_PROP_FIXED                                       ((uint8)0x01U) /**< Fixed block : SW part attributes are not modifiable */
#define ecy_hsm_TB_REF_VERIF_VALUE_SIZE_BYTES                            AES_BLOCK_SIZE_BYTES /**< SW part verification value size */
/* *********** Deprecated definitions ***************/
/**
 * @deprecated by ecy_hsm_CSAI_TB_BOOT_MODE_BOOTABLE
 */
#define TB_BOOT_MODE_BOOTABLE ecy_hsm_CSAI_TB_BOOT_MODE_BOOTABLE
/**
 * @deprecated by ecy_hsm_CSAI_TB_BOOT_MODE_SECURE
 */
#define TB_BOOT_MODE_SECURE ecy_hsm_CSAI_TB_BOOT_MODE_SECURE
/**
 * @deprecated by ecy_hsm_CSAI_TB_BOOT_MODE_AUTHENTIC
 */
#define TB_BOOT_MODE_AUTHENTIC ecy_hsm_CSAI_TB_BOOT_MODE_AUTHENTIC
/**
 * @deprecated by ecy_hsm_CSAI_TB_BOOT_MODE_RTMD_ONCE
 */
#define TB_BOOT_MODE_RTMD_ONCE ecy_hsm_CSAI_TB_BOOT_MODE_RTMD_ONCE
/**
 * @deprecated by ecy_hsm_CSAI_TB_BOOT_MODE_RTMD_CONT
 */
#define TB_BOOT_MODE_RTMD_CONT ecy_hsm_CSAI_TB_BOOT_MODE_RTMD_CONT
/**
 * @deprecated by ecy_hsm_CSAI_TB_BOOT_MODE_AUTHENTIC_EXTENDED_RESET
 */
#define TB_BOOT_MODE_AUTHENTIC_EXTENDED_RESET ecy_hsm_CSAI_TB_BOOT_MODE_AUTHENTIC_EXTENDED_RESET
/**
 * @deprecated by ecy_hsm_CSAI_TB_BOOT_MODE_SECURE_WITH_DIRECT_RELEASE
 */
#define TB_BOOT_MODE_SECURE_WITH_DIRECT_RELEASE ecy_hsm_CSAI_TB_BOOT_MODE_SECURE_WITH_DIRECT_RELEASE
/**
 * @deprecated by ecy_hsm_CSAI_TB_VER_HOST_PATTERN
 */
#define TB_VER_HOST_PATTERN ecy_hsm_CSAI_TB_VER_HOST_PATTERN
/**
 * @deprecated by ecy_hsm_CSAI_TB_VER_HSM_PATTERN
 */
#define TB_VER_HSM_PATTERN ecy_hsm_CSAI_TB_VER_HSM_PATTERN
/**
 * @deprecated by ecy_hsm_CSAI_TB_VER_PATTERN_MSK
 */
#define TB_VER_PATTERN_MSK ecy_hsm_CSAI_TB_VER_PATTERN_MSK
/**
 * @deprecated by ecy_hsm_CSAI_TB_VER_VERSION_MSK
 */
#define TB_VER_VERSION_MSK ecy_hsm_CSAI_TB_VER_VERSION_MSK
/**
 * @deprecated by ecy_hsm_CSAI_TB_VER_VERSION_MSK
 */
#define TB_REF_TABLE_SIZE_LEGACY ecy_hsm_CSAI_TB_REF_TABLE_SIZE_LEGACY
/**
 * @deprecated by ecy_hsm_CSAI_TB_VERIFMODE_NONE
 */
#define TB_VERIFMODE_NONE ecy_hsm_CSAI_TB_VERIFMODE_NONE
/**
 * @deprecated by ecy_hsm_CSAI_TB_VERIFMODE_MEMMAPPED_CERT
 */
#define TB_VERIFMODE_MEMMAPPED_CERT ecy_hsm_CSAI_TB_VERIFMODE_MEMMAPPED_CERT
/**
 * @deprecated by ecy_hsm_CSAI_TB_VERIFMODE_KEYSTORE_PUBKEY
 */
#define TB_VERIFMODE_KEYSTORE_PUBKEY ecy_hsm_CSAI_TB_VERIFMODE_KEYSTORE_PUBKEY
/**
 * @deprecated by ecy_hsm_CSAI_TB_VERIFMODE_KEYSTORE_CERT
 */
#define TB_VERIFMODE_KEYSTORE_CERT ecy_hsm_CSAI_TB_VERIFMODE_KEYSTORE_CERT
/**
 * @deprecated by ecy_hsm_CSAI_TB_VERIFMODE_MANUAL_HEADER_BASED_VERIFICATION_V1
 */
#define TB_VERIFMODE_MANUAL_HEADER_BASED_VERIFICATION_V1 ecy_hsm_CSAI_TB_VERIFMODE_MANUAL_HEADER_BASED_VERIFICATION_V1

/* *** type declarations **********************************************************************/

/**
 * @brief Enum for the different boot mode use cases also to set @c failureMode
 * in @c ecy_hsm_Csai_SecLog_ExtendedLogDataT, The values within this enum must fit an unsigned nibble up to 16.
 */
typedef enum ecy_hsm_Csai_TB_ModeTag
{
    ecy_hsm_Csai_TB_SECURE_BOOT_MODE  = 0,   /**< (sequential / parallel) Secure Boot / Autonomous Authenticated Boot use case */
    ecy_hsm_Csai_TB_TRUSTED_BOOT_MODE = 4,   /**< Authentic Boot use case - this use case is applied when the verification job is triggered by the host, including verification (including @ref ecy_hsm_Csai_TabsVerify_SwPart)  */
    ecy_hsm_Csai_TB_RTMD_MODE         = 8,   /**< RTMD use case - this use case is applied during the runtime when the RTMD is triggered by the back ground task*/

    ecy_hsm_Csai_TB_MODE_RESERVED     = 16,  /**< do not exceed as these values set the 4 bits variable failureMode
                                                in the struct ecy_hsm_Csai_SecLog_ExtendedLogDataT which has maximum value of 16 */
} ecy_hsm_Csai_TB_ModeT;

/**
 * @brief Enum for the different trusted boot sub-modes
 */
typedef enum ecy_hsm_Csai_TB_SubModeTag
{
    ecy_hsm_Csai_TB_UNDEFINED_SUBMODE      = 0,  /**< Undefined sub-mode - use case ecy_hsm_Csai_TB_ModeT applies */
    ecy_hsm_Csai_TB_ABHSM_GENERIC_SUBMODE  = 1,  /**< Authentic Boot General sub-mode - see @ref ecy_hsm_Csai_TbRequestVerification */
    ecy_hsm_Csai_TB_ABHSM_EXTENDED_SUBMODE = 2,  /**< Extended Authentic Boot (Trusted boot with ECU reset) sub-mode - see @ref ecy_hsm_Csai_TbRequestVerification */
} ecy_hsm_Csai_TB_SubModeT;

/** Define Trusted Boot verification states */
typedef enum {
    /** Trusted Boot Block initialized from host side */
    ecy_hsm_TB_STATE_HOST_INIT_E    = -4,
    /** Trusted Boot State no update - @deprecated, do not use any more */
    ecy_hsm_TB_STATE_NO_UPDATE      = -3,
    /** Trusted Boot State test currently running - intermediate state, only used for verification table */
    ecy_hsm_TB_STATE_PENDING        = -2,
    /** Trusted Boot State not tested */
    ecy_hsm_TB_STATE_NOT_TESTED     = -1,
    /** Trusted Boot Verification failed */
    ecy_hsm_TB_STATE_INVALID_E      = 0,
    /** Trusted Boot Verification successful */
    ecy_hsm_TB_STATE_VALID_E        = 1

} ecy_hsm_TB_Verification_StatesT;

typedef struct
{
    /** The start address of the host SW part to be verified */
    uint32 swPartAddress;
    /** The last verification result for the SW part, read from NVM */
    sint8  swPartLastVerifState;
    /** The current verification result for the SW part */
    sint8  swPartCurrVerifState;
    /** The ID of the host SW part to be verified by the HSM */
    uint8  swPartId;
    /** The configured TB boot verification mode */
    uint8  swPartVerifBootMode;
} ecy_hsm_TB_VerifTable_RecordT;

typedef struct
{
    /** The version id of the verification table structure */
    uint32 verifTableVersion; /* will be available from a header shared with the host */
    /** The global verification flag */
    sint8  gblVerifStateFlag;
    /** The manipulation verification flag */
    sint8  mnplVerifStateFlag;
    /** Verification process complete flag */
    uint8  verifChainEnded;
    /** At first configuration the Host transmit the number of elements and the HSM response with the HSM max size of elements */
    uint8 numOfElements;
    /** The verification table records with the verification states */
    ecy_hsm_TB_VerifTable_RecordT verifTableInfoArray[TB_REF_TABLE_SIZE];
} ecy_hsm_Host_TB_VerifTableT;

/**
 * @brief Structure of the RTMD manual suspension data
 */
typedef struct
{
    uint8  dataVersion;                                 /**< The version id of the RTMD manual suspension data */
    uint8  rtmdManualSuspensionStatus;                  /**< Status of the RTMD manual suspension */
    uint16 reservedBytes_1;                             /**< Reserved Byte */
    uint16 totalRTMDSuspensions;                        /**< Total number of RTMD suspensions */
    uint16 totalNumberRTMDAutoReactivations;            /**< Total number of RTMD auto reactivations */
    uint32 lastRTMDSuspensionEntryPowerCycleCounter;    /**< Power cycle counter of the last RTMD suspension entry */
    uint32 totalNumberRTMDSuspendedPowerCycles;         /**< Sum of all RTMD suspended power cycles */
} ecy_hsm_Csai_RTMD_ManualSuspensionDataT;

/**
 * @brief List of RTMD suspension data version id
 */
typedef enum
{
    ecy_hsm_Csai_RTMD_MANUAL_SUSPENSION_DATA_VERSION_0 = 0x00U,       /**< Only basic data: rtmdManualSuspensionStatus and totalRTMDSuspensions */
    ecy_hsm_Csai_RTMD_MANUAL_SUSPENSION_DATA_VERSION_1 = 0x01U,       /**< Basic and power cycle dependent data: rtmdManualSuspensionStatus,
                                                                           totalRTMDSuspensions, totalNumberRTMDAutoReactivations,
                                                                           lastRTMDSuspensionEntryPowerCycleCounter and totalNumberRTMDSuspendedPowerCycles */
    ecy_hsm_Csai_RTMD_MANUAL_SUSPENSION_DATA_VERSION_INVALID = 0xFFU, /**< Invalid RTMD manual suspension data version id */
} ecy_hsm_Csai_RTMD_ManualSuspensionDataVersionIdT;

/**
 * @brief List of RTMD manual suspension status
 */
typedef enum {
    ecy_hsm_Csai_RTMD_MANUAL_SUSPENSION_STATUS_SUSPENDED     = 0x00U, /**< RTMD is manually suspended */
    ecy_hsm_Csai_RTMD_MANUAL_SUSPENSION_STATUS_NOT_SUSPENDED = 0x01U, /**< RTMD is not manually suspended */
    ecy_hsm_Csai_RTMD_MANUAL_SUSPENSION_STATUS_INVALID       = 0xFFU, /**< Invalid RTMD manual suspension status */
} ecy_hsm_Csai_RTMD_ManualSuspensionStatusT;

/** Enumeration of TB FOTA Use cases */
typedef enum ecy_hsm_Csai_TB_FOTAUseCaseTag
{
    ecy_hsm_CSAI_FOTA_USECASE_UNDEFINED            = 0U,           /**< Undefined use case */
    ecy_hsm_CSAI_FOTA_USECASE_COPY_REF_TABLE       = 1U,           /**< Use case of copying TB reference table of the active bank to the TB reference table of the inactive bank  */
    ecy_hsm_CSAI_FOTA_USECASE_RESERVED             = 0x7FFFFFFFUL  /**< Reserved value to enforce long enums  */
} ecy_hsm_Csai_TB_FOTAUseCaseT;

/** Structure for passing data between host csai and hsm applet endpoint for the TB FOTA use case */
typedef struct ecy_hsm_Csai_TB_FOTADataTag
{
    ecy_hsm_Csai_TB_FOTAUseCaseT  useCaseId;            /**< Determines the TB FOTA use case to be supported */
    void*                         pUsecaseParam;        /**< pointer to receive the user specific structure  */
} ecy_hsm_Csai_TB_FOTA_DataT;

/* SwVerification ABHost structure for a single SW part */
typedef struct ecy_hsm_Csai_TB_SwPartVerificationABHostTag
{
    uint32 swPartAddress;                                            /**< [in] The Address of the SW part, if SwPartId is 0 */
    uint8  swPartId;                                                 /**< [in] The identifier of the SW part to be verified */
    uint8  verificationValue[ecy_hsm_TB_REF_VERIF_VALUE_SIZE_BYTES]; /**< [in] The verification value for the SW part*/
} ecy_hsm_Csai_TB_SwPartVerificationABHostT;

/** SwVerification ABHost parameter struct version 0.*/
typedef struct ecy_hsm_Csai_TB_SwVerification_ABHost_V0Tag
{
    ecy_hsm_Csai_TB_SwPartVerificationABHostT* pSwParts;   /**< [in] Pointer to table containing SW part identifier and verification values */
    uint32                                     cntSwParts; /**< [in] The number of SW parts requested for verification.
                                                               If cntSwParts is 0, CycurHSM will not perform any verification but will still return success if the other input parameters are valid.*/
} ecy_hsm_Csai_TB_SwVerification_ABHost_V0T;

/* SwVerification ABHSM structure for a single SW part */
typedef struct ecy_hsm_Csai_TB_SwPartVerification_ABHSM_Tag
{
    uint32                          swPartAddress; /**< [in] The Address of the SW part, if swPartId is 0 */
    uint8                           swPartId;      /**< [in] The identifier of the SW part to be verified */
} ecy_hsm_Csai_TB_SwPartVerification_ABHSM_T;

/** SwVerification ABHSM parameter struct version 1 */
typedef struct ecy_hsm_Csai_TB_SwVerification_ABHSM_V0Tag
{
    ecy_hsm_Csai_TB_SwPartVerification_ABHSM_T* pSwParts;   /**< [in] Pointer to table containing SW part identifier and verification values */
    uint32                                      cntSwParts; /**< [in] The number of SW parts requested for verification.
                                                               If cntSwParts is 0, CycurHSM will not perform any verification but will still return success if the other input parameters are valid.*/
    ecy_hsm_Csai_TB_SubModeT                    subMode;    /**< [in] SW verification sub-mode */
} ecy_hsm_Csai_TB_SwVerification_ABHSM_V0T;

/** SwVerification parameter struct version identifiers.*/
typedef enum ecy_hsm_Csai_TB_SwVerification_ParamSetVersionTag
{
    ecy_hsm_Csai_TB_SwVerification_ABHost_VID_0 = 0,    /**< Version 0 of ABHost param struct identifier. */
    ecy_hsm_Csai_TB_SwVerification_ABHSM_VID_0  = 1,    /**< Version 0 of ABHSM param struct identifier. */
    ecy_hsm_Csai_TB_SwVerification_RESERVED     = 0x7FFFFFFF,
} ecy_hsm_Csai_TB_SwVerification_ParamSetVersionT;

/** SwVerification parameter struct union.*/
/* PRQA S 0750 2 */ /* <Deviation: definition of union is appropriate here */
typedef union ecy_hsm_Csai_TB_SwVerification_ParamSetUnionTag
{
    ecy_hsm_Csai_TB_SwVerification_ABHost_V0T paramSet_ABHost_V0; /**< Version 0 of ABHost parameter struct. */
    ecy_hsm_Csai_TB_SwVerification_ABHSM_V0T  paramSet_ABHSM_V0;  /**< Version 0 of ABHSM parameter struct. */
} ecy_hsm_Csai_TB_SwVerification_ParamSetUnionT;

/** SwVerification wrapper structure for interface parameter extensibility. */
typedef struct ecy_hsm_Csai_TB_SwVerification_ParamSetAndVersionTag
{
    ecy_hsm_Csai_TB_SwVerification_ParamSetVersionT paramSetVersion; /**< Param set version identifier. */
    ecy_hsm_Csai_TB_SwVerification_ParamSetUnionT   paramSet;        /**< Param set union. */
} ecy_hsm_Csai_TB_SwVerification_ParamSetAndVersionT;

/** SW Part definition */
typedef struct ecy_hsm_Csai_TB_SwPartDefinitionTag
{
    uint32 swPartAddress;       /**< [out] The address of the SW Part */
    uint32 swPartLength;        /**< [out] The length of the SW Part in bytes */
    uint8  swPartId;            /**< [out] The identifier of the SW part to be verified */
    uint8  swPartVerifBootMode; /**< [out] SW part verification mode */
} ecy_hsm_Csai_TB_SwPartDefinitionT;

/** Init ABHost parameter struct version 0.*/
typedef struct ecy_hsm_Csai_TB_Init_ABHost_V0Tag
{
    ecy_hsm_Csai_WorkspacesMaskT hostWksps; /**< [in] Bit Mask of the workspaces the trusted boot key shall be loaded to. */
    ecy_hsm_Csai_HostKeyHandleT* phHostKey; /**< [out] Buffer to store the host key handle. */
    uint32* pCntSwParts; /**< [in/out] Inputs the buffer size of pSwParts in num elements of ecy_hsm_Csai_TB_SwPartDefinitionT and outputs the number
                            of SW parts filled by the service */
    ecy_hsm_Csai_TB_SwPartDefinitionT* pSwParts; /**< [out] Pointer to array of SW part definition structure with *pCntSwParts elements */
} ecy_hsm_Csai_TB_Init_ABHost_V0T;

/** Init parameter struct version identifiers.*/
typedef enum ecy_hsm_Csai_TB_Init_ParamSetVersionTag
{
    ecy_hsm_Csai_TB_Init_ABHost_VID_0 = 0, /**< Version 0 param struct identifier. */
    ecy_hsm_Csai_TB_Init_RESERVED     = 0x7FFFFFFF,
} ecy_hsm_Csai_TB_Init_ParamSetVersionT;

/** Init parameter struct union.*/
/* PRQA S 0750 2 */ /* <Deviation: definition of union is appropriate here */
typedef union ecy_hsm_Csai_TB_Init_ParamSetUnionTag
{
    ecy_hsm_Csai_TB_Init_ABHost_V0T paramSet_ABHost_V0; /**< Version 0 of the parameter struct used for ABHost feature */
} ecy_hsm_Csai_TB_Init_ParamSetUnionT;

/** Init wrapper structure for interface parameter extensibility. */
typedef struct ecy_hsm_Csai_TB_Init_ParamSetAndVersionTag
{
    ecy_hsm_Csai_TB_Init_ParamSetVersionT paramSetVersion; /**< Param set version identifier. */
    ecy_hsm_Csai_TB_Init_ParamSetUnionT   paramSet;        /**< Param set union. */
} ecy_hsm_Csai_TB_Init_ParamSetAndVersionT;

/* *** defines ********************************************************************************/
/*************************************************************************************************/
/**
* @image html Sequence_Diagram.png "Sequence Diagram for Authenticated Boot (Host<->HSM)"
* @image rtf Sequence_Diagram.png "Sequence Diagram for Authenticated Boot (Host<->HSM)"
*/
/* *** global constants ***********************************************************************/

/* *** exported interfaces ********************************************************************/
/*************************************************************************************************/

/* *INDENT-OFF* */
#ifdef __cplusplus
extern "C" {
#endif
/* *INDENT-ON* */

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/*************************************************************************************************/
/**
 * [$DD 1447]
 * Verify the SW part and check against the saved reference verification value
 * [$Satisfies $SW_ARCH 714] [$Satisfies $ARCH 143] [$Satisfies $ARCH 161]
 *
 * @note
 * - Functions for managing the trusted boot reference table are only available after the lifecycle of
 *   the CycurHSM has been switched away from @ref ecy_hsm_CSAI_LC_STATE_PRODUCTION using the function
 *   @ref ecy_hsm_Csai_SetLifecycleState.
 * - This function will be executed in any lifecycle state of the HSM, except in "Production" state.
 * - If the TABS feature is enabled this function can only be executed with the @ref ecy_hsm_CSAI_PRIO_BACKGROUND
 *   priority.
 *   If the feature is not enabled all priorities are allowed to account for backwards compatibility.
 *
 * @param[in] hSession    Handle to an open HSM session.
 * @param[in] priority    Scheduling priority of the operation on the HSM.
 * @param[in] swPartId    The identifier of the SW part to be verified
 * @param[in] swPartAddr  The Address of the SW Part, if SwPartId is 0
 * @param[out] phJob      Receives the job handle of the initialized job.
 *
 * @return
 * - @ref ecy_hsm_CSAI_SUCCESS                      Success
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM            Inconsistent parameters have been entered (e.g. invalid ID and address)
 * - @ref ecy_hsm_CSAI_ERR_INVALID_STATE            Lifecycle is in an invalid state (Production)
 * - @ref ecy_hsm_CSAI_ERR_PRIORITY_NOT_ALLOWED     TABS feature is enabled and requested priority was higher than Background
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_TbRequestSwVerification(ecy_hsm_Csai_SessionHandleT hSession,
                                                       ecy_hsm_Csai_JobPriorityT   priority,
                                                       uint8                       swPartId,
                                                       uint32                      swPartAddr,
                                                       ecy_hsm_Csai_JobHandleT*    phJob);

/*************************************************************************************************/
/**
 * [$DD 2747]
 * Get global verification and manipulation status.
 * [$Satisfies $SW_ARCH A3090060]
 *
 * Parameter \p pGblVerifStateFlag represents the global verification state. It is updated after a verification of a SW part (by RTMD or
 * user request) and by call of @ref ecy_hsm_Csai_TbEndOfBootChain(). It is set to valid, if all SW parts have been verified as valid. It is
 * immediately set to invalid when a SW part is verified as invalid by either RTMD or call of @ref ecy_hsm_Csai_TbRequestSwVerification().
 *
 * Parameter \p pMnplVerifStateFlag represents the general manipulation state. It is handled like the global state with the exception that
 * once set to INVALID it retains that state for the lifetime of an ECU.
 *
 * All pointer parameters are checked for validity, i.e. must not be NULL_PTR.
 *
 * @note Functions for managing the trusted boot reference table are only available after the lifecycle of
 *       the CycurHSM has been switched away from @ref ecy_hsm_CSAI_LC_STATE_PRODUCTION using the function
 *       @ref ecy_hsm_Csai_SetLifecycleState.
 *
 * @param[out] pGblVerifStateFlag        Pointer to variable for global verification state
 * @param[out] pMnplVerifStateFlag       Pointer to variable for global manipulation state
 *
 * @return
 * - @ref ecy_hsm_CSAI_ERR_CFG_VERSION_MISSMATCH    The version of the verification table is inconsistent between host and HSM
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM            A parameter was invalid (e.g. null pointer)
 * - @ref ecy_hsm_CSAI_SUCCESS                      Success
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_TbGetGlobalStatus(ecy_hsm_TB_Verification_StatesT* pGblVerifStateFlag,
                                                 ecy_hsm_TB_Verification_StatesT* pMnplVerifStateFlag);

/*************************************************************************************************/
/**
 * [$DD 957]
 * Get boot mode, current and last status of a SW part by ID or start address, and global verification and manipulation status.
 * [$Satisfies $SW_ARCH 159_v1][$Satisfies $ARCH 147]
 *
 * Parameter \p pSwPartCurrVerifState represents the current verification state of the requested SW part. The state is initialized
 * to NOT_TESTED during HSM initialization (in case there is no Secure Boot present). It is set to PENDING on request of verification
 * by call of @ref ecy_hsm_Csai_TbRequestSwVerification() or RTMD. After the verification process is finished the state is updated to
 * either VALID or INVALID depending on the verification result.
 *
 * Parameter \p pLastSwPartVerifState represents the result from the last verification of the requested SW part. This can be either
 * the result from a previous power cycle (if the SW was not checked yet in current power cycle) loaded from HSM data NVM or the result
 * from a completed verification in current power cycle (which is then equal to the final result of \p pSwPartCurrVerifState)
 *
 * Parameter \p pGblVerifStateFlag represents the global verification state. It is updated after a verification of a SW part (by RTMD or
 * user request) and by call of @ref ecy_hsm_Csai_TbEndOfBootChain(). It is set to valid, if all SW parts have been verified as valid. It is
 * immediately set to invalid when a SW part is verified as invalid by either RTMD or call of @ref ecy_hsm_Csai_TbRequestSwVerification().
 *
 * Parameter \p pMnplVerifStateFlag represents the general manipulation state. It is handled like the global state with the exception that
 * once set to INVALID it retains that state for the lifetime of an ECU.
 *
 * All pointer parameters are checked for validity, i.e. must not be NULL_PTR.
 *
 * @note Functions for managing the trusted boot reference table are only available after the lifecycle of
 *       the CycurHSM has been switched away from @ref ecy_hsm_CSAI_LC_STATE_PRODUCTION using the function
 *       @ref ecy_hsm_Csai_SetLifecycleState.
 *
 * @param[in] swPartId                   The ID of the host SW part to get the Status
 * @param[in] swPartAddr                 The start address of the host SW part to get the Status
 * @param[out] pSwPartVerifBootMode      Pointer to variable for Boot Mode of a SW part
 * @param[out] pSwPartCurrVerifState     Pointer to variable for current state of a SW part
 * @param[out] pLastSwPartVerifState     Pointer to variable for last state of a SW part
 * @param[out] pGblVerifStateFlag        Pointer to variable for global verification state
 * @param[out] pMnplVerifStateFlag       Pointer to variable for global manipulation state
 *
 * @return
 * - @ref ecy_hsm_CSAI_ERR_CFG_VERSION_MISSMATCH    The version of the verification table is inconsistent between host and HSM
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM            A parameter was invalid (e.g. null pointer)
 * - @ref ecy_hsm_CSAI_SUCCESS                      Success
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_TbGetSwIdStatus(uint8                            swPartId,
                                               uint32                           swPartAddr,
                                               uint8*                           pSwPartVerifBootMode,
                                               ecy_hsm_TB_Verification_StatesT* pSwPartCurrVerifState,
                                               ecy_hsm_TB_Verification_StatesT* pLastSwPartVerifState,
                                               ecy_hsm_TB_Verification_StatesT* pGblVerifStateFlag,
                                               ecy_hsm_TB_Verification_StatesT* pMnplVerifStateFlag);

/*************************************************************************************************/
/**
 * [$DD 1349] [$Satisfies $ARCH 840]
 * *
 * Get maximum size of elements in HSM trusted boot table
 *
 * @param[out] pNumOfElements            number of elements in the trusted boot table on HSM side
 *
 * @return
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM  Null Pointer as parameter
 * - @ref ecy_hsm_CSAI_SUCCESS            Success
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_TbGetHSMMaxNumberOfElements(uint32* pNumOfElements);

/*************************************************************************************************/
/**
 * [$DD 958]
 * This signals that authenticated boot is finished
 * [$Satisfies $ARCH 160]
 *
 * @note
 * - This function will be executed only if the lifecycle state of the HSM is "In Field".
 *
 * @param[in]  hSession  Handle to an open HSM session.
 * @param[in]  priority  Scheduling priority of the operation on the HSM
 * @param[out] phJob     Receives the job handle of the initialized job.
 *
 * @return
 * - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR1  Error reported by AES hardware
 * - @ref ecy_hsm_CSAI_SUCCESS               Success
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_TbEndOfBootChain(ecy_hsm_Csai_SessionHandleT hSession,
                                                ecy_hsm_Csai_JobPriorityT   priority,
                                                ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 2768]
 * [$Satisfies $SW_ARCH B566F968]
 *
 * Initialize authenticated boot sequence.
 * Supported use case is @c ecy_hsm_Csai_TB_Init_ABHost_VID_0
 *
 * @details
 * This function will be executed in any lifecycle state of the HSM, except in "Production" state.
 *
 * For the @ref ecy_hsm_Csai_TB_Init_ABHost_VID_0 use case, this interface loads the trusted boot key to the HwCsp
 * module. Additionally it delivers information about the used SW parts which the user requires to utilize HwCsp for
 * calculating the SW parts CMAC verification value.
 *
 * @note The ecy_hsm_Csai_TB_Init_ParamSetAndVersionT buffer passed needs to be preserved until the job is finished.
 *
 * @param[in]       hSession            Handle to an open HSM session.
 * @param[in]       priority            Scheduling priority of the operation on the HSM.
 * @param[in,out]   pParams             Pointer to the structure @c ecy_hsm_Csai_TB_Init_ParamSetAndVersionT which specifies
 *                                      the requested use case @c ecy_hsm_Csai_TB_Init_ParamSetVersionT and pointer
 *                                      to the buffer to receive the user information for the chosen use case.
 *
 * @param[out]      phJob               Receives the job handle of the initialized job.
 *
 * @return
 * - @ref ecy_hsm_CSAI_SUCCESS                    Requested use case executed successfully.
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED          The feature is disabled by configuration.
 * - @ref ecy_hsm_CSAI_ERR_INVALID_STATE          Calling this function multiple times with initialization of different HwCsp modules is not supported.
 * - @ref ecy_hsm_CSAI_ERR_HWCSP_UNINITIALIZED    HwCsp module is not initialized.
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM          Parameter set version is not supported or invalid HwCsp workspace.
 * - @ref ecy_hsm_CSAI_ERR_HWCSP_NO_SPACE_FOR_KEY No space in HwCsp keystore for loading trusted boot key.
 *
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_TbInit(ecy_hsm_Csai_SessionHandleT               hSession,
                                                                                ecy_hsm_Csai_JobPriorityT                 priority,
                                                                                ecy_hsm_Csai_TB_Init_ParamSetAndVersionT* pParams,
                                                                                ecy_hsm_Csai_JobHandleT*                  phJob);

/**
 * [$DD 2769]
 *
 * Verify multiple SW parts according to a specific use case.
 * Supported use cases are:
 * - @ref ecy_hsm_Csai_TB_SwVerification_ABHost_VID_0
 * - @ref ecy_hsm_Csai_TB_SwVerification_ABHSM_VID_0 : Extended Authenticated Boot with optional system reset
 * [$Satisfies $SW_ARCH 607DFAB1_v1] [$Satisfies $SW_ARCH 31F29237] [$Satisfies $SW_ARCH B8C5A959]
 *
 * @details
 * This function will be executed in any lifecycle state of the HSM, except in "Production" state.
 * This function can only be executed with the @ref ecy_hsm_CSAI_PRIO_BACKGROUND.
 *
 * For the @ref ecy_hsm_Csai_TB_SwVerification_ABHost_VID_0 use case, this interface verifies the SW-part against
 * the user supplied verification value.
 *
 * For the @ref ecy_hsm_Csai_TB_SwVerification_ABHSM_VID_0 use case, this interface verifies the provided SW parts
 * against their reference values, according to the user-specified SW parts verification sub-mode (subMode):
 * - @ref ecy_hsm_Csai_TB_ABHSM_EXTENDED_SUBMODE : If a SW part configured as @ref ecy_hsm_CSAI_TB_BOOT_MODE_AUTHENTIC_EXTENDED_RESET is detected
 * as manipulated, the verification stops and a system reset is performed (if supported by the target hardware). In this case,
 * some SW parts may not have been verified and their verification status may not have been updated. During execution of this
 * function the HSM doesn't respond to any other service request from the Host (even higher priority ones).
 * @warning The verification status of the SW parts is not always updated when this sub-mode is used, please check the User Guide.
 * - @ref ecy_hsm_Csai_TB_ABHSM_GENERIC_SUBMODE : all provided SW parts are verified and their verification status is updated. No reset
 * is performed. The function is interruptible by higher-priority Host service requests.
 *
 * Consider cross dependencies with other features (like TABS) which might impact the verification time and result.
 * The returned error code represents the most recent SW part verification error. A verification error will
 * not abort the verification process of other SW parts (unless a system reset is triggered).
 *
 * @note
 * The ecy_hsm_Csai_TB_SwVerification_ParamSetAndVersionT buffer passed needs to be preserved until the job is finished.
 * Verification is continued also in case a single SW part verification ends with an error. If multiple errors occur, the last error is returned.
 * An error shall not be misunderstood as verification result, it means, that one or more verifications did not take place.
 *
 * @param[in]       hSession            Handle to an open HSM session.
 * @param[in]       priority            Scheduling priority of the operation on the HSM.
 * @param[in,out]   pParams             Pointer to the structure @c ecy_hsm_Csai_TB_SwVerification_ParamSetAndVersionT which specifies
 *                                      the requested use case @c ecy_hsm_Csai_TB_SwVerification_ParamSetVersionT and pointer
 *                                      to the buffer to receive the user information for the chosen use case.
 * @param[out]      phJob               Receives the job handle of the initialized job.
 *
 * @return
 * - @ref ecy_hsm_CSAI_SUCCESS              Requested use case executed successfully.
 * - @ref ecy_hsm_CSAI_ERR_INTERNAL_PARAM   One or more of the SW parts length is 0 and cannot be verified.
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM    Parameter set version is not supported or inconsistent parameters have been entered (e.g. invalid ID and address).
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED    The feature is disabled by configuration.
 *
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_TbRequestVerification(ecy_hsm_Csai_SessionHandleT                         hSession,
                                                                                               ecy_hsm_Csai_JobPriorityT                           priority,
                                                                                               ecy_hsm_Csai_TB_SwVerification_ParamSetAndVersionT* pParams,
                                                                                               ecy_hsm_Csai_JobHandleT*                            phJob);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_SECFLASH
 * @{
 * Secure flash programming API
 *
 */

/**
 * @addtogroup GROUP_CSAI_REFTABLE
 * @{
 * functions for handling the reference table
 */

/*************************************************************************************************/
/**
 * [$DD 959]
 * Create a temporary SW-part reference table entry in RAM and initialize CMAC calculation for this SW-part
 * [$Satisfies $ARCH 156]
 *
 * At HSM startup the temporary reference table in RAM contains no entries. This function creates a new entry in
 * the temporary reference table, for a SW-part that the host is willing to update in the host PFlash (a SW-part is
 * a contiguous host flash region). A possibly running RTMD is permanently suspended (until the next reset).
 *
 * The CMAC and length calculation for this SW-part are initialized. The newly created reference table entry will be
 * considered valid only after subsequent calls to the @ref ecy_hsm_Csai_TbRefTblPartUpdate and
 * @ref ecy_hsm_Csai_TbRefTblPartFinish functions.
 *
 * The specified SW-part becomes the active SW-part in this session for all @ref ecy_hsm_Csai_TbRefTblPartUpdate
 * subsequent calls and until @ref ecy_hsm_Csai_TbRefTblPartFinish is called.
 *
 * Special use case: @ref ecy_hsm_Csai_TbRefTblPartFinish may be called directly thereafter (no call to @ref
 * ecy_hsm_Csai_TbRefTblPartUpdate) if the host wants to delete an existing SW-part from the reference table. The
 * resulting SW-part length is 0 in this case.
 *
 * The following session rules apply:
 * - Only one SW-part may be active at a given time in a given session.
 * - Multiple SW-parts may be active at a given time in different sessions. However, these must be distinct SW-parts.
 * (it is not allowed to have the same SW-part active in different sessions at the same time)
 *
 * The following consistency checks are performed before initiating the new SW-part:
 * - If an entry for the same SW-part already exists in the temporary reference table, this entry is re-used (it is
 * invalidated and overwritten, no new entry is created)
 * - The SW-part start address @p swPartAddr shall not be within the address range of an existing SW-part in the
 * temporary reference table (there shall be no overlapping SW-parts). The User of this interface is responsible,
 * that the different entries don't overlap. If an overlap takes place, the older entry will be inconsistent and
 * errors will occur during Trusted Boot/RTMD.
 *
 * @note
 * - Functions for managing the trusted boot reference table are available in the lifecycle of
 *   the CycurHSM @ref ecy_hsm_CSAI_LC_STATE_PRODUCTION and afterwards.
 *   These API's can only be used only after the table has been initialised, either through lifecycle switch or 'full init' API
 * - In case the RTMD feature with the RTMD manual suspension is enabled, the RTMD must be manually
 *   suspended. In case the RTMD is not manually suspended an error will be returned.
 *
 * @warning
 *   In case the RTMD manual suspension is enabled, the behavior of the RTMD suspension will be changed.
 *   - If RTMD manual suspension is disabled, the RTMD will be automatically suspended by the function call
 *     and reactivated after a reset. This is the old behavior.
 *   - If RTMD manual suspension is enabled, the automatic RTMD suspension is deactivated.
 *     The RTMD can only be suspended with @ref ecy_hsm_Csai_TbRtmdSuspend and also needs to be manually
 *     reactivated with @ref ecy_hsm_Csai_TbRtmdReactivate. The RTMD must be suspended befor the function
 *     ecy_hsm_Csai_TbRefTblPartInit is called. If the RTMD is not suspended an error code will be returned.
 *
 * @param[in] hSession          Handle to an open HSM session.
 * @param[in] priority          Scheduling priority of the operation on the HSM.
 * @param[in] swPartId          The identifier of the SW part to be verified. Must not be equal to 0 when the entry does not yet exist.
 *                              If this parameter is set to 0 and the @p swPartAddr is identical to an entry already present in the
 *                              reference table, this entry will be selected for updating.
 * @param[in] swPartAddr        The Address of the SW Part
 * @param[in] swPartBootMode    The boot mode of the SW part. Can be @ref ecy_hsm_CSAI_TB_BOOT_MODE_SECURE, @ref ecy_hsm_CSAI_TB_BOOT_MODE_AUTHENTIC,
 *                              @ref ecy_hsm_CSAI_TB_BOOT_MODE_RTMD_ONCE or @ref ecy_hsm_CSAI_TB_BOOT_MODE_RTMD_CONT
 * @param[in] swPartRtmdOrder   The RTMD order of the SW Part
 * @param[out] phJob            Receives the job handle of the initialized job.
 *
 * @return
 * - @ref ecy_hsm_CSAI_SUCCESS                      Success
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM            Inconsistent parameters have been entered (e.g. invalid ID and address)
 * - @ref ecy_hsm_CSAI_ERR_TB_RTMD_NOT_SUSPENDED    The RTMD is currently not manually suspended
 * - @ref ecy_hsm_CSAI_ERR_SECFUNC_LOCKED           Security critical functions are currently disabled
 *                                                  (see @ref ecy_hsm_Csai_Protection_DisableSecCritFunctions)
 *
 * @see ecy_hsm_Csai_TbRefTblPartUpdate, ecy_hsm_Csai_TbRefTblPartFinish
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_TbRefTblPartInit(ecy_hsm_Csai_SessionHandleT hSession,
                                                ecy_hsm_Csai_JobPriorityT   priority,
                                                uint8                       swPartId,
                                                uint32                      swPartAddr,
                                                uint8                       swPartBootMode,
                                                uint8                       swPartRtmdOrder,
                                                ecy_hsm_Csai_JobHandleT*    phJob);

/*************************************************************************************************/
/**
 * [$DD 1350]
 * Set the address and type of the signature of the active SW-part and specify the keystore-slot of the certificate or public key
 * [$Satisfies $ARCH 715]
 *
 * The address and type of the signature and the key ID of the certificate or public key of the active SW-part
 * for the given session are updated.
 *
 * The active SW-part must have been initialized by a previous call to @ref ecy_hsm_Csai_TbRefTblPartInit.
 *
 * The function can only be called after @ref ecy_hsm_Csai_TbRefTblPartInit. The @ref ecy_hsm_Csai_TbRefTblPartUpdate - @ref ecy_hsm_Csai_TbRefTblPartFinish -sequence
 * should be executed afterwards. This ensures that a particular SW part setup is finished with the @ref ecy_hsm_Csai_TbRefTblPartFinish function.
 * Additionally the @ref APPLET_TB_STATES transitions are simplified by avoiding parallel paths that could arise when transitions from
 * ecy_hsm_APPLET_TB_FUNC_REF_Table_PART_INIT->ecy_hsm_APPLET_TB_FUNC_REF_Table_PART_SET_SIGNATURE and ecy_hsm_APPLET_TB_FUNC_REF_Table_PART_SET_SIGNATURE->ecy_hsm_APPLET_TB_FUNC_REF_Table_FINALIZE
 * were allowed.
 *
 * @note
 * - Functions for managing the trusted boot reference table are available in the lifecycle of
 *   the CycurHSM @ref ecy_hsm_CSAI_LC_STATE_PRODUCTION and afterwards.
 * - The signature shall be located completely inside or completely outside of the respective SW-part, it shall not overlap it (in the sense that the signature
 *   shall not be located half-way outside and half-way inside the SW-part).
 *
 * @warning
 * - the function doesn't perform any signature verification. Therefore there is no error returned by the function if the provided signature is invalid.
 * - the function doesn't check the correct location of the signature. No error is returned by the function if the signature overlaps the SW-part, but the TABS feature
 * will always report an invalid SW-part.
 *
 * @param[in] hSession                  Handle to an open HSM session.
 * @param[in] priority                  Scheduling priority of the operation on the HSM.
 * @param[in] swPartSignatureAddress    The address of the signature
 * @param[in] swPartSignatureType       The type of the signature (see: @ref ecy_hsm_Csai_SignatureSchemeT)
 * @param[in] swPartKeyId               The key ID of the certificate or public key
 * @param[in] swPartVerifSignMode       The signature verification mode (must be ecy_hsm_CSAI_TB_VERIFMODE_KEYSTORE_PUBKEY or ecy_hsm_CSAI_TB_VERIFMODE_KEYSTORE_CERT)
 * @param[out] phJob                    Receives the job handle of the initialized job.
 *
 * @return
 * - @ref ecy_hsm_CSAI_SUCCESS              Success
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM    Inconsistent parameters have been entered (e.g. invalid ID, address or signature verification mode)
 * - @ref ecy_hsm_CSAI_ERR_INVALID_STATE    Current RefTable state is incorrect
 * - @ref ecy_hsm_CSAI_ERR_SECFUNC_LOCKED   Security critical functions are currently disabled
 *                                          (see @ref ecy_hsm_Csai_Protection_DisableSecCritFunctions)
 *
 * @see ecy_hsm_Csai_TbRefTblPartInit, ecy_hsm_Csai_TbRefTblPartUpdate, ecy_hsm_Csai_TbRefTblPartFinish, ecy_hsm_Csai_TbRefTblFinalize
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_TbRefTblPartSetSignWithKeyId(ecy_hsm_Csai_SessionHandleT hSession,
                                                            ecy_hsm_Csai_JobPriorityT   priority,
                                                            uint32                      swPartSignatureAddress,
                                                            uint16                      swPartSignatureType,
                                                            ecy_hsm_Csai_KeyIdT         swPartKeyId,
                                                            uint8                       swPartVerifSignMode,
                                                            ecy_hsm_Csai_JobHandleT    *phJob);

/*************************************************************************************************/
/**
 * [$DD 1351]
 * Set the address of the signature of the active SW-part and specify the address of the certificate in memory
 * [$Satisfies $ARCH 715]
 *
 * The address of the signature and the memory address of the certificate of the active SW-part
 * for the given session are updated.
 *
 * The active SW-part must have been initialized by a previous call to @ref ecy_hsm_Csai_TbRefTblPartInit.
 *
 * The function can only be called after @ref ecy_hsm_Csai_TbRefTblPartInit. The @ref ecy_hsm_Csai_TbRefTblPartUpdate - @ref ecy_hsm_Csai_TbRefTblPartFinish -sequence
 * should be executed afterwards. This ensures that a particular SW part setup is finished with the @ref ecy_hsm_Csai_TbRefTblPartFinish function.
 * Additionally the @ref APPLET_TB_STATES transitions are simplified by avoiding parallel paths that could arise when transitions from
 * ecy_hsm_APPLET_TB_FUNC_REF_Table_PART_INIT->ecy_hsm_APPLET_TB_FUNC_REF_Table_PART_SET_SIGNATURE and ecy_hsm_APPLET_TB_FUNC_REF_Table_PART_SET_SIGNATURE->ecy_hsm_APPLET_TB_FUNC_REF_Table_FINALIZE
 * were allowed.
 *
 * @note
 * - Functions for managing the trusted boot reference table are available in the lifecycle of the CycurHSM @ref ecy_hsm_CSAI_LC_STATE_PRODUCTION and afterwards.
 * - The signature shall be located completely inside or completely outside of the respective SW-part, it shall not overlap it (in the sense that the signature
 *   shall not be located half-way outside and half-way inside the SW-part).
 *
 * @warning
 * - the function doesn't perform any signature verification. Therefore there is no error returned by the function if the provided signature is invalid.
 * - the function doesn't check the correct location of the signature. No error is returned by the function if the signature overlaps the SW-part, but the TABS feature
 * will always report an invalid SW-part.
 *
 * @param[in] hSession                  Handle to an open HSM session.
 * @param[in] priority                  Scheduling priority of the operation on the HSM.
 * @param[in] swPartSignatureAddress    The address of the signature
 * @param[in] swPartCertAddress         The address of the certificate
 * @param[in] swPartVerifSignMode       The signature verification mode (must be ecy_hsm_CSAI_TB_VERIFMODE_MEMMAPPED_CERT)
 * @param[out] phJob                    Receives the job handle of the initialized job.
 *
 * @return
 * - @ref ecy_hsm_CSAI_SUCCESS              Success
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM    Inconsistent parameters have been entered (e.g. invalid ID, address or signature verification mode)
 * - @ref ecy_hsm_CSAI_ERR_INVALID_STATE    Current RefTable state is incorrect
 * - @ref ecy_hsm_CSAI_ERR_SECFUNC_LOCKED   Security critical functions are currently disabled
 *                                          (see @ref ecy_hsm_Csai_Protection_DisableSecCritFunctions)
 *
 * @see ecy_hsm_Csai_TbRefTblPartInit, ecy_hsm_Csai_TbRefTblPartUpdate, ecy_hsm_Csai_TbRefTblPartFinish, ecy_hsm_Csai_TbRefTblFinalize
 */
/* PRQA S 0777 2 */ /* Deviation: rule_5.1_0777 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_TbRefTblPartSetSignWithCertAddress(ecy_hsm_Csai_SessionHandleT hSession,
                                                                  ecy_hsm_Csai_JobPriorityT   priority,
                                                                  uint32                      swPartSignatureAddress,
                                                                  uint32                      swPartCertAddress,
                                                                  uint8                       swPartVerifSignMode,
                                                                  ecy_hsm_Csai_JobHandleT*    phJob);

/*************************************************************************************************/
/**
 * [$DD 960]
 * Update the CMAC of the active SW-part with the given data chunk and calculate the new length of the SW-part
 * [$Satisfies $ARCH 174]
 *
 * The CMAC of the active SW-part for the given session is updated with the content of the provided data chunk.
 *
 * The active SW-part must have been initialized by a previous call to @ref ecy_hsm_Csai_TbRefTblPartInit.
 *
 * The function may be called repeatedly until the complete SW-part has been processed by the HSM.
 * When the complete SW-part has been processed, the @ref ecy_hsm_Csai_TbRefTblPartFinish function must be called.
 *
 * Important restrictions:
 * - The SW-part must be continuous in the host memory. It is therefore not allowed for the host to "skip"
 * some areas within the SW-part address range.
 * - The chunks must be processed in strict steadily increasing host address order.
 *
 * Failing to apply these rules would result in a wrongly computed CMAC and subsequent TrustedBoot / RTMD verification
 * failures.
 *
 * Special use case: @ref ecy_hsm_Csai_TbRefTblPartUpdate shall not be called if the host wants to delete an existing
 * SW-part from the reference table. The host shall call @ref ecy_hsm_Csai_TbRefTblPartInit directly followed by
 * @ref ecy_hsm_Csai_TbRefTblPartFinish.
 *
 * @note Functions for managing the trusted boot reference table are available in the lifecycle of the CycurHSM
 * @ref ecy_hsm_CSAI_LC_STATE_PRODUCTION and afterwards.
 *   @ref ecy_hsm_Csai_SetLifecycleState.
 *
 * @param[in] hSession              Handle to an open HSM session.
 * @param[in] priority              Scheduling priority of the operation on the HSM.
 * @param[in] swPartChunk           A data chunk of the current SW part to be verified
 * @param[in] swPartChunkNumBytes   The length in bytes of the data chunk
 * @param[out] phJob                Receives the job handle of the initialized job.
 *
 * @return
 * - @ref ecy_hsm_CSAI_SUCCESS              Success
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM    Inconsistent parameters have been entered (e.g. invalid ID and address)
 * - @ref ecy_hsm_CSAI_ERR_SECFUNC_LOCKED   Security critical functions are currently disabled
 *                                          (see @ref ecy_hsm_Csai_Protection_DisableSecCritFunctions)
 *
 * @see ecy_hsm_Csai_TbRefTblPartInit, ecy_hsm_Csai_TbRefTblPartFinish
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_TbRefTblPartUpdate(ecy_hsm_Csai_SessionHandleT hSession,
                                                  ecy_hsm_Csai_JobPriorityT   priority,
                                                  const uint8                 swPartChunk[],
                                                  uint32                      swPartChunkNumBytes,
                                                  ecy_hsm_Csai_JobHandleT*    phJob);

/*************************************************************************************************/
/**
 * [$DD 961]
 * Finish the CMAC calculation of the active SW-part
 * [$Satisfies $ARCH 158]
 *
 * The previously initiated CMAC calculation (through calls to @ref ecy_hsm_Csai_TbRefTblPartInit and @ref
 * ecy_hsm_Csai_TbRefTblPartUpdate) for a given SW-part is finished.
 *
 * The CMAC reference value of the SW-part and the SW-part length are updated into the corresponding temporary
 * reference table entry, which is then considered to be valid (i.e. ready to be persisted in non-volatile storage).
 *
 * In order for the updated SW-part to be considered by the TrustedBoot & RTMD features, the reference table must be
 * persisted into non-volatile storage by calling the @ref ecy_hsm_Csai_TbRefTblFinalize function.
 *
 * After @ref ecy_hsm_Csai_TbRefTblPartFinish is called, there is no more "active SW-part" for the given session.
 * A new active SW-part may be initiated by calling the @ref ecy_hsm_Csai_TbRefTblPartInit function.
 *
 * In case of VMS configuration @ref MW_TB_SECACC_PROTECTED_DELETE_ENTRY is ENABLED the deletion of an entry will only be allowed
 * when the device is in lifecycle state @ref ecy_hsm_CSAI_LC_STATE_PRIVMODEDEV or @ref ecy_hsm_CSAI_LC_STATE_PRIVMODESERIAL or a valid secure access is executed.
 * Otherwise the function will return @ref ecy_hsm_CSAI_ERR_TB_SECACC_PRIVILEGE_MISSING.
 * If an error is returned by this function the complete update procedure is cancelled and no @ref ecy_hsm_Csai_TbRefTblFinalize is possible.
 *
 * @note Functions for managing the trusted boot reference table are available in the lifecycle of the CycurHSM @ref ecy_hsm_CSAI_LC_STATE_PRODUCTION and afterwards.
 *
 * @param[in] hSession              Handle to an open HSM session.
 * @param[in] priority              Scheduling priority of the operation on the HSM.
 * @param[out] phJob                Receives the job handle of the initialized job.
 *
 * @return
 * - @ref ecy_hsm_CSAI_SUCCESS                          Success
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                Inconsistent parameters have been entered (e.g. invalid ID and address)
 * - @ref ecy_hsm_CSAI_ERR_SECFUNC_LOCKED               Security critical functions are currently disabled
 *                                                      (see @ref ecy_hsm_Csai_Protection_DisableSecCritFunctions)
 * - @ref ecy_hsm_CSAI_ERR_TB_SECACC_PRIVILEGE_MISSING  No Privilege to delete an entry of the trusted boot table
 *
 * @see ecy_hsm_Csai_TbRefTblPartInit, ecy_hsm_Csai_TbRefTblPartUpdate, ecy_hsm_Csai_TbRefTblPartFinish,
 *      ecy_hsm_Csai_TbRefTblFinalize
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_TbRefTblPartFinish(ecy_hsm_Csai_SessionHandleT hSession,
                                                  ecy_hsm_Csai_JobPriorityT   priority,
                                                  ecy_hsm_Csai_JobHandleT*    phJob);

/*************************************************************************************************/
/**
 * [$DD 962]
 * Persist the temporary reference table updates into HSM non-volatile storage
 * [$Satisfies $ARCH 157] [$Satisfies $ARCH 152] [$Satisfies $ARCH 153]
 *
 * This function terminates a sequence of calls to @ref ecy_hsm_Csai_TbRefTblPartInit, @ref ecy_hsm_Csai_TbRefTblPartUpdate
 * and @ref ecy_hsm_Csai_TbRefTblPartFinish for one or multiple SW parts. For each Sw-part a temporary reference
 * table entry was created, which has to be persisted into HSM non-volatile storage for use by the TrustedBoot
 * and RTMD features.
 *
 * The current reference table in non-volatile storage is updated with the information from the temporary reference table
 * according to the following rules:
 * - only valid reference table entries are considered (i.e. entries for which the CMAC calculation was completed)
 *      - if there are invalid entries in the temporary reference table, it is considered inconsistent and the
 *      reference table in non-volatile storage is not updated. An error is returned to the caller.
 * - if the same SW-part (SwId or start address) exists in the current reference table, the existing entry is updated
 *      - if the SW-part length in the temporary reference table is 0, the corresponding entry is deleted from the current
 *      reference table. This allows the host to change the memory layout of the application software, by calling
 *      @ref ecy_hsm_Csai_TbRefTblPartInit followed by @ref ecy_hsm_Csai_TbRefTblPartFinish (without any call to
 *      @ref ecy_hsm_Csai_TbRefTblPartUpdate).
 * - if the SW-part doesn't exist in the current reference table
 *      - if there is space left in the current reference table, a new entry is added to the table
 *      - if there is no space left in the current reference table, an error is returned.
 *
 * In case of any error an inconsistent state is to be assumed. This means that the reference table in non-volatile
 * storage may not correspond to the current state of the host software. This means that subsequent verifications
 * performed by the TrustedBoot & RTMD features after the next HSM startup are likely to fail.
 *
 * In order to ensure that the temporary reference table is consistent the following rules apply:
 * - For each SW-part that was previously initiated by the host (through a call to @ref ecy_hsm_Csai_TbRefTblPartInit),
 * the @ref ecy_hsm_Csai_TbRefTblPartFinish function must have been called.
 * - @ref ecy_hsm_Csai_TbRefTblFinalize shall be called at most once and after all SW-parts have been processed. In case
 * that different SW-parts were processed in different sessions, only a single session may call
 * @ref ecy_hsm_Csai_TbRefTblFinalize.
 *
 * After having being persisted successfully, the temporary reference table in RAM is cleared (no entries anymore).
 * The host may check the pNumPersistedEntries parameter to ensure that all SW-parts that it has programmed have
 * been updated in the reference table and will therefore be considered after the next startup by the TrustedBoot
 * and RTMD features.
 *
 * In case of error the temporary reference table in RAM is also cleared. The host must restart the flash programming
 * process from the beginning.
 *
 * @note Functions for managing the trusted boot reference table are available in the lifecycle of the CycurHSM
 * @ref ecy_hsm_CSAI_LC_STATE_PRODUCTION and afterwards.
 *
 * @param[in] hSession              Handle to an open HSM session.
 * @param[in] priority              Scheduling priority of the operation on the HSM.
 * @param[out] pNumPersistedEntries Pointer to the location of the number of reference table entries that were persisted
 * @param[out] phJob                Receives the job handle of the initialized job.
 *
 * @return
 * - @ref ecy_hsm_CSAI_SUCCESS              Success
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM    Inconsistent parameters have been entered (e.g. invalid ID and address)
 * - @ref ecy_hsm_CSAI_ERR_NO_SPACE_REFTBL  No space left in the reference table
 * - @ref ecy_hsm_CSAI_ERR_SECFUNC_LOCKED   Security critical functions are currently disabled
 *                                          (see @ref ecy_hsm_Csai_Protection_DisableSecCritFunctions)
 *
 * @see ecy_hsm_Csai_TbRefTblPartInit, ecy_hsm_Csai_TbRefTblPartFinish
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_TbRefTblFinalize(ecy_hsm_Csai_SessionHandleT hSession,
                                                ecy_hsm_Csai_JobPriorityT   priority,
                                                uint32*                     pNumPersistedEntries,
                                                ecy_hsm_Csai_JobHandleT*    phJob);

/*************************************************************************************************/
/**
 * [$DD 1472]
 * Creates the table from the reference table configured in the P-Flash config area
 * [$Satisfies $ARCH 156][$Satisfies $ARCH 157][$Satisfies $ARCH 158][$Satisfies $ARCH 174]
 *
 * This function conducts a full reference table CMAC calculation for all SW parts in the production phase
 * For each Sw-part entry a reference table has been updated by taking the configured table in the P-Flash config area
 *
 * @note
 * Trusted boot reference table has to configured in Project_EcucValues.arxml
 * When configuring the SW Parts for the first time in Project_EcucValues.arxml, 0 shall not be used as a SW-part Id
 *
 * @param[in] hSession              Handle to an open HSM session.
 * @param[in] priority              Scheduling priority of the operation on the HSM.
 * @param[out] phJob                Receives the job handle of the initialized job.
 *
 * @return
 * - @ref ecy_hsm_CSAI_SUCCESS              Success
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM    Inconsistent parameters have been entered (e.g. invalid ID and address)
 * - @ref ecy_hsm_CSAI_ERR_SECFUNC_LOCKED   Security critical functions are currently disabled
 *                                          (see @ref ecy_hsm_Csai_Protection_DisableSecCritFunctions)
 *  @ref ecy_hsm_CSAI_ERR_LIFECYCLE_WRONG   If the current Lifecycle is not in Production state
 * @see TrustedBoot_InitRefTables
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_TbRefTblFullInit(ecy_hsm_Csai_SessionHandleT hSession,
                                                ecy_hsm_Csai_JobPriorityT   priority,
                                                ecy_hsm_Csai_JobHandleT*    phJob);

/*************************************************************************************************/
/**
 * [$DD 1668]
 * This function suspend the RTMD.
 * [$Satisfies $SW_ARCH 1027]
 *
 * @note
 * - DFLASH data operations will always performed in background priority.
 * The DFLASH is needed to store the current RTMD suspend status.
 * - The RTMD remains suspended until the @ref ecy_hsm_Csai_TbRtmdReactivate is called or
 * the RTMD auto reactivation is triggered. The RTMD auto reactivation can only be triggered in case it was enabled
 * on build time and the set limit of power cycles has been reached.
 * - In case the RTMD is suspended all keys with the flag @ref ecy_hsm_CSAI_KEYPROP_SECURE_BOOT_MUST_PASS are no longer accessible until
 * the RTMD is reactivated.
 *
 * @param[in]  hSession              Handle to an open HSM session.
 * @param[in]  priority              Scheduling priority of the operation on the HSM.
 * @param[out] phJob                 Receives the job handle of the initialized job.
 *
 * @return
 * - @ref ecy_hsm_CSAI_SUCCESS                              Success
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                    Inconsistent parameters have been entered
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                    The RTMD manually suspend is not supported by this HSM build
 * - @ref ecy_hsm_CSAI_ERR_TB_RTMD_IS_ALREADY_SUSPENDED     The RTMD is already manually suspended
 * - @ref ecy_hsm_CSAI_ERR_TB_RTMD_NOT_SUSPENDED            The RTMD suspend timer is exceeded and the RTMD can not be
 *                                                          suspended anymore within this power cycle
 * - @ref ecy_hsm_CSAI_ERR_DATASTORE                        A data store error occurred while reading or writing
 * - @ref ecy_hsm_CSAI_ERR_INVALID_STATE                    The RTMD is not initialized
 * - @ref ecy_hsm_CSAI_ERR_SECFUNC_LOCKED                   Security critical functions are currently disabled
 *                                                          (see @ref ecy_hsm_Csai_Protection_DisableSecCritFunctions)
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_TbRtmdSuspend(ecy_hsm_Csai_SessionHandleT hSession,
                                             ecy_hsm_Csai_JobPriorityT   priority,
                                             ecy_hsm_Csai_JobHandleT*    phJob);

/*************************************************************************************************/
/**
 * [$DD 1669]
 * This function reactivate the RTMD.
 * [$Satisfies $SW_ARCH 1027]
 *
 * @note
 * - DFLASH data operations will always performed in background priority.
 * The DFLASH is needed to store the current RTMD suspend status.
 * - Only works if the RTMD is suspended.
 *
 * @param[in] hSession              Handle to an open HSM session.
 * @param[in] priority              Scheduling priority of the operation on the HSM.
 * @param[out] phJob                Receives the job handle of the initialized job.
 *
 * @return
 * - @ref ecy_hsm_CSAI_SUCCESS                   Success
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM         Inconsistent parameters have been entered
 * - @ref ecy_hsm_CSAI_ERR_TB_RTMD_NOT_SUSPENDED The RTMD is currently not manually suspended
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED         The RTMD reactivation is not supported by this HSM build
 * - @ref ecy_hsm_CSAI_ERR_DATASTORE             A data store error occurred while reading or writing
 * - @ref ecy_hsm_CSAI_ERR_SECFUNC_LOCKED        Security critical functions are currently disabled
 *                                               (see @ref ecy_hsm_Csai_Protection_DisableSecCritFunctions)
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_TbRtmdReactivate(ecy_hsm_Csai_SessionHandleT hSession,
                                                ecy_hsm_Csai_JobPriorityT   priority,
                                                ecy_hsm_Csai_JobHandleT*    phJob);

/*************************************************************************************************/
/**
 * [$DD 1670]
 * This function reads out the specific RTMD manually suspension data.
 * [$Satisfies $SW_ARCH 8B9AB840]
 *
 * @note
 * - DFLASH data operations will always performed in background priority.
 * - Not all variables of the struct @ref ecy_hsm_Csai_RTMD_ManualSuspensionDataT are always used.
 * Which of the variables are used can be read out via the dataVersion.
 *      - The dataVersion is @ref ecy_hsm_Csai_RTMD_MANUAL_SUSPENSION_DATA_VERSION_0, in case only RTMD manually suspend is enabled without the rtmd auto reactivation feature.
 *      - The dataVersion is @ref ecy_hsm_Csai_RTMD_MANUAL_SUSPENSION_DATA_VERSION_1, in case RTMD manually suspend and the rtmd auto reactivation feature are enabled.
 *
 * If dataVersion is @ref ecy_hsm_Csai_RTMD_MANUAL_SUSPENSION_DATA_VERSION_0 then the following variables are used and the others are always set to zero:
 * - @ref ecy_hsm_Csai_RTMD_ManualSuspensionDataT.rtmdManualSuspensionStatus
 * - @ref ecy_hsm_Csai_RTMD_ManualSuspensionDataT.totalRTMDSuspensions
 *
 * If dataVersion is @ref ecy_hsm_Csai_RTMD_MANUAL_SUSPENSION_DATA_VERSION_1 then the following variables are used:
 * - @ref ecy_hsm_Csai_RTMD_ManualSuspensionDataT.rtmdManualSuspensionStatus
 * - @ref ecy_hsm_Csai_RTMD_ManualSuspensionDataT.totalRTMDSuspensions
 * - @ref ecy_hsm_Csai_RTMD_ManualSuspensionDataT.totalNumberRTMDAutoReactivations
 * - @ref ecy_hsm_Csai_RTMD_ManualSuspensionDataT.lastRTMDSuspensionEntryPowerCycleCounter
 * - @ref ecy_hsm_Csai_RTMD_ManualSuspensionDataT.totalNumberRTMDSuspendedPowerCycles
 *
 *
 * @param[in]  hSession     Handle to an open HSM session.
 * @param[in]  priority     Scheduling priority of the operation on the HSM.
 * @param[out] pData        Pointer to buffer to receive the rtmd suspend data (\ref ecy_hsm_Csai_RTMD_ManualSuspensionDataT)
 * @param[in]  dataLength   Length of buffer to receive the rtmd suspend data.
 * @param[out] phJob        Receives the job handle of the initialized job.
 *
 * @return
 * - @ref ecy_hsm_CSAI_SUCCESS                   Success
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM         Inconsistent parameters have been entered
 * - @ref ecy_hsm_CSAI_ERR_TB_RTMD_NOT_SUSPENDED The RTMD is currently not manually suspended
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED         The RTMD manually suspend data is not supported by this HSM build
 * - @ref ecy_hsm_CSAI_ERR_DATASTORE             A data store error occurred while reading the data
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_TbReadRtmdSuspensionData(ecy_hsm_Csai_SessionHandleT hSession,
                                                        ecy_hsm_Csai_JobPriorityT   priority,
                                                        void*                       pData,
                                                        uint32                      dataLength,
                                                        ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 2715]
 * The trusted boot handling of the inactive bank TB use cases for the TB FOTA requirements.
 * Currently supported use case is @c ecy_hsm_CSAI_FOTA_USECASE_COPY_REF_TABLE.
 * [$Satisfies $SW_ARCH B870CA1E]
 *
 * @details
 * For the @ref ecy_hsm_CSAI_FOTA_USECASE_COPY_REF_TABLE use case, this interface copies the trusted boot reference table
 * of the active bank to the trusted boot reference table of the inactive bank. HSM internally checks which bank is active and reads the
 * trusted boot reference table of the active bank and copies the trusted boot reference table data of the active bank to the
 * trusted boot reference of the inactive bank and persist into the inactive bank reference table in DFLASH.
 * @note
 * As precondition: The trusted boot table configuration of the inactive bank shall be available.
 *
 *
 * @param[in]       hSession            Handle to an open HSM session.
 * @param[in]       priority            Scheduling priority of the operation on the HSM.
 * @param[in]       pTBFOTAData         Address to the structure @c ecy_hsm_Csai_TB_FOTA_DataT which contains
 *                                      the information of the @ref ecy_hsm_Csai_TB_FOTAUseCaseTag and pointer
 *                                      to the buffer to receive the user specific information for specific use case.
 * @param[out]      phJob               Receives the job handle of the initialized job.
 *
 * @return
 * - @ref ecy_hsm_CSAI_SUCCESS                                  Requested use case executed successfully.
 * - @ref ecy_hsm_CSAI_ERR_EEPROM_TAG_NOT_FOUND                 Trusted boot reference table cannot be found in the DFLASH.
 *
 */
ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_HandleInactiveBankTbRefTbl(ecy_hsm_Csai_SessionHandleT     hSession,
                                                                              ecy_hsm_Csai_JobPriorityT       priority,
                                                                              ecy_hsm_Csai_TB_FOTA_DataT*     pTBFOTAData,
                                                                              ecy_hsm_Csai_JobHandleT*        phJob);

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"

/** @} */ // GROUP_CSAI_REFTABLE
/** @} */// GROUP_CSAI_SECFLASH

/* *INDENT-OFF* */
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* ECY_HSM_CSAI_TRUST_BOOT_H */
