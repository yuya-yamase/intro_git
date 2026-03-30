/**
 * @file
 ***********************************************************************************************
 * @brief CSAI HSM Miscellaneous Functionality.
 * This header file is part of the Cryptographic Service Application Interface and specifies
 * types and functions for miscellaneous HSM functions.
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2014, all rights reserved
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_CSAI_MISC_H
#define ECY_HSM_CSAI_MISC_H

/**
* @addtogroup GROUP_CSAI_MISC
* @{
*/

/* *** includes *******************************************************************************/

#include "ecy_hsm_csai_types.h"
#include "ecy_hsm_csai_error.h"
#include "ecy_hsm_csai_hash.h"

/* *** defines ********************************************************************************/
/* HSM Software Version Release types */
#define ecy_hsm_CSAI_SW_RELEASE_TYPE_DEBUG       (10U) /**< Release Type Debug. Just used for in house development.                        */
#define ecy_hsm_CSAI_SW_RELEASE_TYPE_ALPHA       (20U) /**< Release Type Alpha. The software is at alpha level.                            */
#define ecy_hsm_CSAI_SW_RELEASE_TYPE_BETA        (30U) /**< Release Type Beta. The software is at beta level.                              */
#define ecy_hsm_CSAI_SW_RELEASE_TYPE_RC          (40U) /**< Release Type Release Candidate. The software is a possible release candidate.  */
#define ecy_hsm_CSAI_SW_RELEASE_TYPE_RELEASE     (50U) /**< Release Type Release. The software is at release level.                        */

/** Defines for validation status of the flashed firmware */
#define ecy_hsm_CSAI_FW_RESET_VECTOR_VALID       1UL /**< Valid reset vector                                 */
#define ecy_hsm_CSAI_FW_VALIDATION_FLAG_VALID    2UL /**< Valid validation flags                             */
#define ecy_hsm_CSAI_FW_HSM_VERSION_VALID        4UL /**< Valid versions between bootloader and core         */
/** Define for valid Firmware state. All validation flags are valid. */
#define ecy_hsm_CSAI_FW_STATE_VALID_V1           (ecy_hsm_CSAI_FW_RESET_VECTOR_VALID | ecy_hsm_CSAI_FW_VALIDATION_FLAG_VALID | ecy_hsm_CSAI_FW_HSM_VERSION_VALID)

/** Maximum length for the encoded version (version 2) returned by HSM */
#define ecy_hsm_CSAI_MAX_ENC_VERSION_V2_LEN      (4U)
/** Minimum value of encoded version (version 2) returned by HSM */
#define ecy_hsm_CSAI_ENC_VERSION_V2_MIN          (0U)
/** Maximum value of encoded version (version 2) returned by HSM */
#define ecy_hsm_CSAI_ENC_VERSION_V2_MAX          (9999U)
/** Count of supported encoded version (version 2) numbers **/
#define ecy_hsm_CSAI_ENC_VERSION_V2_COUNT        (ecy_hsm_CSAI_ENC_VERSION_V2_MAX + 1)

/** Value returned when part verification data is successfully calculated by HSM */
#define ecy_hsm_CSAI_INTEGRITY_PART_DATA_SUCCESS (1)
/** Value returned when part verification data could not be calculated by HSM    */
#define ecy_hsm_CSAI_INTEGRITY_PART_DATA_ERROR   (0)
/* *** type declarations **********************************************************************/

/** Define FLASH blocks controlled by the HSM */
typedef enum ecy_hsm_Csai_FLASH_BlockT
{
    ecy_hsm_CSAI_FLASH_LOW_64k_BLK2 = 0U,         /**< 64k FLASH block in low address space                 */
    ecy_hsm_CSAI_FLASH_LOW_64k_BLK3 = 1U,         /**< 64k FLASH block in low address space                 */
    ecy_hsm_CSAI_FLASH_LOW_16k_BLK5 = 2U,         /**< 16k FLASH block in low address space                 */
    ecy_hsm_CSAI_FLASH_MID_16k_BLK0 = 3U,         /**< 16k EEPROM block in mid address space                */
    ecy_hsm_CSAI_FLASH_MID_16k_BLK1 = 4U,         /**< 16k EEPROM block in mid address space                */
    ecy_hsm_CSAI_FLASH_BLK_NONE     = 5U,         /**< Invalid value                                        */
    ecy_hsm_CSAI_FLASH_RESERVED     = 0x7fffffffu /**< Value defined to use memory size of uint32 for enums */
} ecy_hsm_Csai_FLASH_BlockT;

/** Enum for the compiler used  */
typedef enum ecy_hsm_Csai_CompilerTag
{
    CSAI_CompilerHighTec    = 1,          /**< Code was compiled with a HighTec compiler            */
    CSAI_CompilerGreenHills = 2,          /**< Code was compiled with a GreenHills compiler         */
    CSAI_CompilerClang      = 3,          /**< Code was compiled with a Clang compiler              */
    CSAI_COMPILER_RESERVED  = 0x7fffffffU /**< Value defined to use memory size of uint32 for enums */
} ecy_hsm_Csai_CompilerT;

/** Enum for the target hardware    */
typedef enum ecy_hsm_Csai_TargetTag
{
    CSAI_TargetEiger       = 100,        /**< Code was compiled for the Eiger/Chorus SPC58xx84 target        */
    CSAI_TargetMatterhorn  = 101,        /**< Code was compiled for the Matterhorn MPC5777M target           */
    CSAI_TargetChorus      = 102,        /**< Code was compiled for the Chorus SPC58ECxx target              */
    CSAI_TargetEiger_Cut2  = 103,        /**< Code was compiled for the Eiger/Chorus SPC58xx84 Cut2 target   */
    CSAI_TargetRH850       = 200,        /**< Code was compiled for the RH850 target                         */
    CSAI_TargetRH850_F1H   = 201,        /**< Code was compiled for the RH850_F1H target                     */
    CSAI_TargetTC27x       = 300,        /**< Code was compiled for the TC27x target                         */
    CSAI_TargetTC29x       = 301,        /**< Code was compiled for the TC29x target                         */
    CSAI_TargetTC23x       = 302,        /**< Code was compiled for the TC23x target                         */
    CSAI_TargetTC39x       = 400,        /**< Code was compiled for the TC39x target                         */
    CSAI_TargetTC35x       = 401,        /**< Code was compiled for the TC35x target                         */
    CSAI_TargetTC37x       = 402,        /**< Code was compiled for the TC37x target                         */
    CSAI_TargetTC33x       = 403,        /**< Code was compiled for the TC33x target                         */
    CSAI_TargetTC36x       = 404,        /**< Code was compiled for the TC36x target                         */
    CSAI_TargetTC32x       = 405,        /**< Code was compiled for the TC32x target                         */
    CSAI_TargetNXP_Calypso = 500,        /**< Code was compiled for the NXP Calypso target                   */
    CSAI_TargetCYT2_B9     = 600,        /**< Code was compiled for the Traveo2 B9 target                    */
    CSAI_TargetCYT2_BL     = 601,        /**< Code was compiled for the Traveo2 BL target                    */
    CSAI_TargetSR6X7       = 800,        /**< Code was compiled for the ST Stellar SR6X7 target              */
    CSAI_TargetSR6P7       = 801,        /**< Code was compiled for the ST Stellar SR6P7 target              */
    CSAI_TargetSR6G7       = 802,        /**< Code was compiled for the ST Stellar SR6G7 target              */
    CSAI_TargetSR6P6       = 803,        /**< Code was compiled for the ST Stellar SR6P6 target              */
    CSAI_TargetSR6P2       = 804,        /**< Code was compiled for the ST Stellar SR6P2 target              */
    CSAI_TargetSR6P3       = 805,        /**< Code was compiled for the ST Stellar SR6P3 target              */
    CSAI_TargetSR6P5       = 806,        /**< Code was compiled for the ST Stellar SR6P5 target              */
    CSAI_TargetPC          = 32000,      /**< Code was compiled for the PC target                            */
    CSAI_TARGET_RESERVED   = 0x7fffffffU /**< Value defined to use memory size of uint32 for enums           */
} ecy_hsm_Csai_TargetT;

/** Enum for the file type    */
typedef enum ecy_hsm_Csai_FileTypeT
{
    CSAI_CFILE               = 1,
    CSAI_HFILE               = 2,
    CSAI_RUBYFILE            = 3,
    CSAI_TXTFILE             = 4,
    CSAI_HEXFILE             = 5,
    CSAI_ELFFILE             = 6,
    CSAI_MAPFILE             = 7,
    CSAI_FILEFORMAT_RESERVED = 0x7fffffffU /**< Value defined to use memory size of uint32 for enums */
} ecy_hsm_Csai_FileTypeT;

/** Enum for the build type: core application, bootloader, etc   */
typedef enum ecy_hsm_Csai_BuildTypeTag
{
    CSAI_BUILDTYPE_INVALID  = 0,
    CSAI_StdCoreApplication = 10,         /**< Code is the standard core application                */
    CSAI_StdBootloader      = 20,         /**< Code is the standard bootloader                      */
    CSAI_BUILDTYPE_RESERVED = 0x7fffffffU /**< Value defined to use memory size of uint32 for enums */
} ecy_hsm_Csai_BuildTypeT;

/** Enum for the release status of the build */
typedef enum ecy_hsm_Csai_ReleaseStatusTag
{
    CSAI_ReleaseDebug           = 1,          /**< Code is not for beta or full release, just in house development  */
    CSAI_ReleaseBeta            = 2,          /**< Code is a beta release                                           */
    CSAI_ReleaseRelease         = 3,          /**< Code is a full release                                           */
    CSAI_RELEASESTATUS_RESERVED = 0x7fffffffU /**< Value defined to use memory size of uint32 for enums             */
} ecy_hsm_Csai_ReleaseStatusT;

/** Enum for the configuration type of power mode */
typedef enum ecy_hsm_Csai_ConfigPowerModeType
{
    ecy_hsm_CSAI_CONFIG_DEEP_SLEEP,                       /**< Deep sleep configuration type                        */
    ecy_hsm_CSAI_CONFIG_DEEP_SLEEP_EXTENDED,              /**< Deep sleep with retained RAM configuration type      */
    ecy_hsm_CSAI_CONFIG_POWER_MODE_RESERVED = 0x7fffffffU /**< Value defined to use memory size of uint32 for enums */
} ecy_hsm_Csai_ConfigPowerModeT;

/**
 * @brief Struct defining the HSM parts. The HSM has currently Core, Bootloader and Config as HSM parts.
 * HSM as a whole can be referenced using the ecy_hsm_CSAI_HSMPART_ALL enum value.
 *
 */
typedef enum ecy_hsm_Csai_HSMPartTag
{
    ecy_hsm_CSAI_HSMPART_CORE     = 1UL, /* Refers to the HSM Core application */
    ecy_hsm_CSAI_HSMPART_BOOT     = 2UL, /* Refers to the HSM bootloader application */
    ecy_hsm_CSAI_HSMPART_CFG      = 3UL, /* Refers to the HSM configuration */
    ecy_hsm_CSAI_HSMPART_ALL      = 4UL, /* Refers to all the HSM parts taken together */
    ecy_hsm_CSAI_HSMPART_RESERVED = 0x7fffffffUL
} ecy_hsm_Csai_HSMPartT;

/** Structure containing the data elements for the Software Version */
typedef struct ecy_hsm_Csai_VersionDataTag
{
    ecy_hsm_Csai_CompilerT      compiler;                /**< Compiler used for build                                                */
    ecy_hsm_Csai_TargetT        target;                  /**< Build target                                                           */
    ecy_hsm_Csai_BuildTypeT     buildType;               /**< Core application or bootloader                                         */
    ecy_hsm_Csai_ReleaseStatusT releaseStatus;           /**< @deprecated: Release status of the software. It is only available for
                                                         *   compatibility reasons. Use the new parameter softwareReleaseType.  */
    uint32                      buildYear;               /**< Year of software build                                                 */
    uint32                      buildMonth;              /**< Month of software build (1-12)                                         */
    uint32                      buildDay;                /**< Day of software build (1-31)                                           */
    uint32                      buildHour;               /**< Hour of software build (0-23)                                          */
    uint32                      buildMinute;             /**< Minute of software build (0-59)                                        */
    uint32                      repoRevision;            /**< Repository revision when software built (should equal the tag revision)*/
    uint32                      interfaceVersion;        /**< Version number of the bridge interface specification                   */
    uint32                      minimumInterfaceVersion; /**< Lowest bridge interface version with which this version is compatible  */
    uint8                       softwareMajorVersion;    /**< Major part of the software version number                              */
    uint8                       softwareMinorVersion;    /**< Minor part of the software version number                              */
    uint8                       softwareRevision;        /**< Software revision number (internally called software patch version)    */
    uint8                       softwareReleaseType;     /**< Release type of the software                                           */
#if defined(GUAM)
# if (HSM_INJECT_TEST == ENABLED) && (BUILD_TYPE == DEBUG)
    uint32* testAddress;
    uint32  testValue;
    uint8   testOperation;
# endif
#endif
} ecy_hsm_Csai_VersionDataT;

/** Define of supported interface version
 *  enum supports definition of new Version for @ref ecy_hsm_Csai_Misc_GetHsmIntegrityData
 *  Currently the interface supports only version V1
 */
typedef enum ecy_hsm_Csai_FwVerificationVersion
{
    FIRMWARE_VERIFICATION_SCHEME_V1 = 1U, /**< Standard firmware verification scheme, must be type of
                                                           @c ecy_hsm_Csai_HSMVerificationStatus_V1                 */
    FIRMWARE_VERIFICATION_SCHEME_MAX,     /**< Max version value                                        */
    FW_VER_SCHEME_RESERVED = 0x7FFFFFFFU  /**< Value defined to use memory size of uint32 for enums     */
} ecy_hsm_Csai_FwVerificationVersionT;

/**
 * @brief Interface version for @ref ecy_hsm_Csai_Misc_GetHsmIntegrityData
 */
typedef enum ecy_hsm_Csai_FwIntegrityDataVersionTag
{
    FW_INTEGRITY_DATA_SCHEME_V1       = 1U,         /**< Standard firmware integrity data scheme, must be type of
                                                            @c ecy_hsm_Csai_FwIntegrityData_V1T                      */
    FW_INTEGRITY_DATA_SCHEME_RESERVED = 0x7FFFFFFFU /**< Value defined to use memory size of uint32 for enums     */
} ecy_hsm_Csai_FwIntegrityDataVersionT;

/**
 * @brief Framework Verification result handle with type(version) and result
 */
typedef struct ecy_hsm_Csai_FwVerificationStateRef
{
    ecy_hsm_Csai_FwVerificationVersionT fwVerificationVersion;     /**< Verification scheme version */
    void*                               pHSMVerificationStatus_VX; /**< Firmware verification status*/
} ecy_hsm_Csai_FwVerificationStateRefT;

/** Verification result type V1 */
typedef struct ecy_hsm_Csai_HSMVerificationStatus_V1
{
    uint32 bootloaderValid; /**< Verification of the bootloader.
                             *  Validation pattern can be found in ecy_hsm_CSAI_FW_STATE_VALID_V1   */
    uint32 bootVersion;     /**< Firmware Version of the HSM Firmware    */
    uint32 coreValid;       /**< Verification of the core.
                             *  Validation pattern can be found in ecy_hsm_CSAI_FW_STATE_VALID_V1   */
    uint32 coreVersion;     /**< Firmware Version of the HSM Firmware                               */
    uint32 repoRevision;    /**< Repo Revision of the HSM Firmware                                  */
} ecy_hsm_Csai_HSMVerificationStatus_V1;

/**
 * @brief Integrity data interface structure, containing the data handle version and a pointer to data handle
 */
typedef struct ecy_hsm_Csai_FwPartsIntegrityDataTag
{
    ecy_hsm_Csai_FwIntegrityDataVersionT fwIntegrityDataVersion; /**< Verification scheme version;
                                                                  * version of struct ecy_hsm_Csai_fwIntegrityData_VX chosen based on the version here. */
    void*                                fwIntegrityData;        /**< Pointer to integrity data element */
} ecy_hsm_Csai_FwPartsIntegrityDataT;

/**
 * @brief this structure corresponds to version V1 for integrity data and is used as a handle in the
 * structure ecy_hsm_Csai_FwPartsIntegrityDataT.
 * The user must assign valid pointer addresses to the pointers and valid lengths for each part buffer in order to get the results
 * for the corresponding HSM verification data. If any of the Core, bootloader, config or complete pointers is set to null,
 * or the length is 0 the corresponding data is not returned.
 */
typedef struct ecy_hsm_Csai_FwIntegrityData_V1Tag
{
    ecy_hsm_Csai_HashAlgorithmT partVerificationAlgo;    /**< Algorithm to calculate the part verification value                    */
    uint32                      memRangeStart;           /**< Start address of Active/inactive bank for which the
                                                       * integrity data is requested. Used for bankswap.
                                                       * By default, data for active bank is returned                            */
    uint32                      partInfoCoreLength;      /**< Length of the core verification data buffer pointer                   */
    uint32                      partInfoBootLength;      /**< Length of the boot verification data buffer pointer                   */
    uint32                      partInfoConfigLength;    /**< Length of the config verification data buffer pointer                 */
    uint32                      partInfoCompleteLength;  /**< Length of the complete sw verification data buffer pointer            */
    uint8*                      pPartInfoCore;           /**< Verification data of core app;
                                                       * if NULL, no data is returned;                                           */
    uint8*                      pPartInfoBoot;           /**< Verification data of bootloader app
                                                       * if NULL, no data is returned;                                           */
    uint8*                      pPartInfoConfig;         /**< Verification data of config app
                                                       * if NULL, no data is returned;                                           */
    uint8*                      pPartInfoComplete;       /**< Verification data of complete hsm
                                                       * if NULL, no data is returned;                                           */
    uint8*                      pPartInfoCoreStatus;     /**< 1 Byte Flag to inform if Core sw verification data was returned in
                                                       * the output data buffer. On successful calculation,
                                                       * ecy_hsm_CSAI_INTEGRITY_PART_DATA_SUCCESS is returned,
                                                       * otherwise ecy_hsm_CSAI_INTEGRITY_PART_DATA_ERROR                        */
    uint8*                      pPartInfoBootStatus;     /**< 1 Byte Flag to inform if Boot sw verification data was returned in
                                                       * the output data buffer. On successful calculation,
                                                       * ecy_hsm_CSAI_INTEGRITY_PART_DATA_SUCCESS is returned,
                                                       * otherwise ecy_hsm_CSAI_INTEGRITY_PART_DATA_ERROR                        */
    uint8*                      pPartInfoConfigStatus;   /**< 1 Byte Flag to inform if Config sw verification data was returned in
                                                       * the output data buffer. On successful calculation,
                                                       * ecy_hsm_CSAI_INTEGRITY_PART_DATA_SUCCESS is returned,
                                                       * otherwise ecy_hsm_CSAI_INTEGRITY_PART_DATA_ERROR                        */
    uint8*                      pPartInfoCompleteStatus; /**< 1 Byte Flag to inform if Complete sw verification data was returned in
                                                       * the output data buffer. On successful calculation,
                                                       * ecy_hsm_CSAI_INTEGRITY_PART_DATA_SUCCESS is returned,
                                                       * otherwise ecy_hsm_CSAI_INTEGRITY_PART_DATA_ERROR                        */
} ecy_hsm_Csai_FwIntegrityData_V1T;

/** Format IDs of supported extended version request and response structures. */
typedef enum ecy_hsm_Csai_VersionFormatIdTag
{
    ecy_hsm_CSAI_RELEASE_VERSION_FORMAT_V1  = 0x01U,       /**< Reserved */
    ecy_hsm_CSAI_RELEASE_VERSION_FORMAT_V2  = 0x02U,       /**< Release information request format ID (Version2) */
    ecy_hsm_CSAI_RELEASE_VERSION_FORMAT_MAX = 0x7FFFFFFFUL /**< Maximum supported format IDs */
} ecy_hsm_Csai_VersionFormatIdT;

/** Response structure for extended version request - version 2 */
typedef struct ecy_hsm_Csai_VersionParamsV2Tag
{
    ecy_hsm_Csai_CompilerT  compiler;                                            /**< Compiler used for build                              */
    ecy_hsm_Csai_TargetT    target;                                              /**< Build target                                         */
    ecy_hsm_Csai_BuildTypeT buildType;                                           /**< Core application or bootloader                       */
    uint32                  buildYear;                                           /**< Year of software build                               */
    uint32                  buildMonth;                                          /**< Month of software build (1-12)                       */
    uint32                  buildDay;                                            /**< Day of software build (1-31)                         */
    uint32                  buildHour;                                           /**< Hour of software build (0-23)                        */
    uint32                  buildMinute;                                         /**< Minute of software build (0-59)                      */
    uint32                  repoRevision;                                        /**< Repository revision when software
                                                                                  * built (should equal the tag revision)                  */
    uint32                  interfaceVersion;                                    /**< Version number of the bridge interface specification */
    uint32                  minimumInterfaceVersion;                             /**< Lowest bridge interface version with which this
                                                                                  * version is compatible                                  */
    uint8                   softwareGeneration;                                  /**< Generation part of the software version number       */
    uint8                   softwareMajorVersion;                                /**< Major part of the software version number            */
    uint8                   softwareMinorVersion;                                /**< Minor part of the software version number            */
    uint8                   softwareRevision;                                    /**< Software revision number
                                                                                  * (internally called software patch version)             */
    uint8                   softwareReleaseType;                                 /**< Release type of the software                         */
    uint8                   userConfigVersion;                                   /**< Version of the user configuration installed          */
    uint8                   encodedVersion[ecy_hsm_CSAI_MAX_ENC_VERSION_V2_LEN]; /**< Encoded version returned by HSM; Based on
                                                                                  * the user config version and HSM version. Currently
                                                                                  * filled with default value                              */
} ecy_hsm_Csai_VersionParamsV2T;

/** Struct for configuring deep sleep mode */
typedef struct ecy_hsm_Csai_DeepSleepConfigData
{
    uint32  intSrc;  /**< System interrupt source */
    uint32  intIdx;  /**< CPU interrupt index (Note: For deep sleep only IRQ#7 (0x7) is valid) */
    boolean enabled; /**< Enabling/disabling system interruption */
} ecy_hsm_Csai_DeepSleepConfigDataT;

/** Struct for configuring deep sleep mode including the retention RAM */
typedef struct ecy_hsm_Csai_DeepSleepConfigDataExtended
{
    ecy_hsm_Csai_DeepSleepConfigDataT basicDeepSleepConfigData; /**< Original config data is only for configuring deep sleep mode    */
    uint32                            retainedRAMBitMap;        /**< Bitmap for configuring RAM retention:
                                                                         1 bit for each RAM block: 0 = OFF / 1 = RETAINED
                                                                         SRAM0: bits 0..15 / SRAM1: bit16                                */
} ecy_hsm_Csai_DeepSleepConfigDataExtendedT;

/** Structure for FEE manager parameters for ecy_hsm_Csai_FEEMGR_CheckReorgOnWrite() */
typedef struct ecy_hsm_Csai_FeeMgr_FeeParamTag
{
    uint32 tag;               /**< ID of the NVM key slot to check for FEE reorganisation                      */
    uint32 sizeToCheck;       /**< Size of the user data to check                                              */
    uint32 isSafeToWrite;     /**< Status on whether the user data size can be written without reorganisation  */
    uint32 possibleNumWrites; /**< The number of data writes before FEE reorganisation                         */
} ecy_hsm_Csai_FeeMgr_FeeParamT;

/**
 * List of version ID for ecy_hsm_Csai_FeeMgr_FeeParamT struct. When this structure is changed in the future,
 * then the version ID shall be increased
 */
typedef enum ecy_hsm_Csai_FeeMgr_StructVersionId
{
    ecy_hsm_CSAI_FEEMGR_STRUCT_VERSION_0 = 0x0UL, /**< Return the following parameters: tag, sizeToCheck  */
                                                  /**< isSafeToWrite, possibleNumWrites                   */

    ecy_hsm_CSAI_FEEMGR_STRUCT_VERSION_INVALID = 0xFFUL /**< Invalid FEE manager (CheckReorgOnWrite) version ID */
} ecy_hsm_Csai_FeeMgr_StructVersionIdT;

/** Enumeration of Verify Register Use cases */
typedef enum ecy_hsm_Csai_VerifyRegisterUseCaseTag
{
    ecy_hsm_CSAI_VERIFY_REGISTER_AGAINST_DEFAULT_VAL_USECASE = 0x0UL,       /**< Verify the requested register value with default value */
    ecy_hsm_CSAI_VERIFY_REGISTER_USECASE_RESERVED            = 0x7fffffffUL /**< Reserved value to enforce long enums */
} ecy_hsm_Csai_VerifyRegisterUseCaseT;

/** This structure defines the parameters for verifying a register value */
/** Structure for the parameters passed to the system function ecy_hsm_Csai_VerifyRegisterParam */
typedef struct ecy_hsm_Csai_VerifyRegisterParam
{
    uint32  registerAddress; /**< The address of the register to be verified */
    boolean result;          /**< The result of the verification operation */
} ecy_hsm_Csai_VerifyRegisterParamT;

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
 * [$DD 2465]
 * [$Satisfies $SW_ARCH E797CAE8] [$Satisfies $SW_ARCH 1C978857]
 * Retrieves HSM core version information.
 * Should the HSM Epilog be corrupted (e.g. during a SecureFlash operation), a hardcoded fallback version is returned instead.
 *
 * @param[in]   hSession     Handle to the session in which the job is placed.
 * @param[in]   priority     Requested scheduling priority for this job on the HSM.
 * @param[out]  pVersionData Receives the HSM core version information.
 * @param[out]  phJob        Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 *   - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION.         A pointer parameter references HSM internal memory.
 *   - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED              The version retrieval is not supported by this HSM build
 *
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_GetCoreVersion(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                        ecy_hsm_Csai_JobPriorityT   priority,
                                                                                        ecy_hsm_Csai_VersionDataT*  pVersionData,
                                                                                        ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 277]
 * CSAI Interface to store serial number in DFLASH. Interface can be used with active HSM in lifecycle state 'Production'.
 * The serial number can be written only once.
 * [$Satisfies $ARCH 766]
 *
 * Setting of the Serial No.
 *
 * Stores the serial number in HSM memory.
 *
 * This interface can be used only after HSM has been activated, as long as the HSM is in
 * lifecycle state 'PRODUCTION'. The function will return an error in lifecycle states
 * other than PRODUCTION.
 *
 * The serial number can be written only once. A second write attempt will fail and return an
 * error.
 *
 * @param[in]    hSession                Handle to the session in which the job is placed.
 * @param[in]    priority                Requested scheduling priority for this job on the HSM.
 * @param[in]    bufferLengthSerialNo    Pointer to length of the serial number buffer.
 * @param[in]    pBufferSerialNo         Pointer to serial number.
 * @param[out]   phJob                   Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                    Some parameter is incorrect
 * - @ref ecy_hsm_CSAI_ERR_LIFECYCLE_WRONG                  The Ecu is in wrong lifecycle
 * - @ref ecy_hsm_CSAI_ERR_DATA_ALREADY_STORED              The serial number is programmed already
 * - Other return codes:
 * - @ref ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL                 The provided buffer is too small to hold the data object, or the local temporary buffer is
 * too small.
 * - @ref ecy_hsm_CSAI_ERR_DATASTORE                        The authentication tags differ or the decrypted size is not consistent
 * - @ref ecy_hsm_CSAI_ERR_OUTPUT_TRUNCATED                 The FEE block is too small to hold the recorded data and the management overhead
 *
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_SetSerialNo(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                     ecy_hsm_Csai_JobPriorityT   priority,
                                                                                     uint8                       bufferLengthSerialNo,
                                                                                     uint8*                      pBufferSerialNo,
                                                                                     ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 2535]
 * [$Satisfies $ARCH 765] [$Satisfies $SW_ARCH 4E75C353]
 *
 * Getting the Device ID.
 *
 * This interface returns the Device ID, consisting of Serial Number and the Chip ID.
 * Until the serial number is not written, the return value will be set to 0.
 *
 * @param[in]        hSession                Handle to the session in which the job is placed.
 * @param[in]        priority                Requested scheduling priority for this job on the HSM.
 * @param[in,out]    pNumBytesBufferSerialNo Pointer to length of the serial number buffer.
 *                                           pNumBytesBufferSerialNo is set to the correct length of the serial number.
 * @param[out]       pBufferSerialNo         Pointer to serial number.
 * @param[in,out]    pNumBytesBufferChipId   Pointer to length of chip id buffer.
 *                                           pNumBytesBufferChipId is set to the correct length of the chip id string.
 * @param[out]       pBufferChipId           Pointer to chip id.
 * @param[out]       phJob                   Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                         The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE              The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                         Another job is still pending completion in this session.
 *                                                       Either finish the previous job or cancel the running job
 *                                                       using @ref ecy_hsm_Csai_CancelJob.
 * - Other return codes:
 * - @ref ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL              The provided buffer is too small to hold the data object, or the local temporary buffer is
 * too small.
 * - @ref ecy_hsm_CSAI_ERR_DATASTORE                     The authentication tags differ or the decrypted size is not consistent
 * - @ref ecy_hsm_CSAI_ERR_OUTPUT_TRUNCATED              The FEE block is too small to hold the recorded data and the management overhead
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                    Some parameter is incorrect
 *
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_GetDeviceId(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                     ecy_hsm_Csai_JobPriorityT   priority,
                                                                                     uint8*                      pNumBytesBufferSerialNo,
                                                                                     uint8*                      pBufferSerialNo,
                                                                                     uint8*                      pNumBytesBufferChipId,
                                                                                     uint8*                      pBufferChipId,
                                                                                     ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * @brief Read generic data section from config area
 *
 * This interface returns the amount of data read into the buffer. If the buffer provided is larger than
 * the size of generic data only the amount of available generic data is copied into the buffer. If the buffer is
 * smaller than the configured amount of generic data only the buffer size is used.
 *
 * @param[in]   hSession            Handle to the session in which the job will be placed.
 * @param[in]   priority            Requested scheduling priority for this job on the HSM.
 * @param[in]   pData               Pointer to the buffer to write the generic data into.
 * @param[in]   numBytesData        Length of the provided @c pData buffer.
 * @param[out]  pNumBytesDataRead   Number of bytes read from generic data.
 * @param[out]  phJob               Receives the job handle of the initialized job.
 *
 * @return ecy_hsm_Csai_ErrorT                 Error/Status code indicating success or failure.
 * @retval ecy_hsm_CSAI_SUCCESS                The call succeeded. The operation is pending on the HSM.
 * @retval ecy_hsm_CSAI_ERR_NOT_SUPPORTED      If config area does not have generic data.
 * @retval ecy_hsm_CSAI_ERR_INVALID_PARAM      A parameter was invalid.
 * @retval ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION  A parameter points to HSM internal memory.
 * @retval ecy_hsm_CSAI_ERR_INVALID_HANDLE     The given session handle is invalid.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_Config_ReadGenericData(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                                ecy_hsm_Csai_JobPriorityT   priority,
                                                                                                uint8*                      pData,
                                                                                                uint32                      numBytesData,
                                                                                                uint32*                     pNumBytesDataRead,
                                                                                                ecy_hsm_Csai_JobHandleT*    phJob);

/** [$DD 2967]
 * [$Satisfies $ARCH 940] [$Satisfies $ARCH 941] [$Satisfies $SW_ARCH 940_v1] [$Satisfies $SW_ARCH 941_v1] [$Satisfies $SW_ARCH D7C83A6F]
 * @brief Read out whitelisted HSM register or device configuration values
 *
 * Writes the content of the specified register or device configuration to an output buffer if the
 * complete range of requested data is whitelisted. If only certain bits of a register are whitelisted,
 * a corresponding bitmask is returned to indicate which register bits were retrieved.
 *
 * @note
 * The whitelist definitions are selected and configured at compile time.
 *
 * @param[in]  hSession            Handle to the session in which the job will be placed.
 * @param[in]  priority            Requested scheduling priority for this job on the HSM.
 * @param[in]  registerAddress     Address of the register or device configuration to be read.
 * @param[in,out]  pRegisterSize   Size of the register to be read out in bytes. If the supplied size is too large,
 *                                 the actually used size will be stored into this parameter. If the supplied size
 *                                 is too small, only the beginning of the register will be written into the output
 *                                 buffers.
 * @param[out]  pRegisterValue     Output buffer for the retrieved register or device configuration value.
 * @param[out]  pRegisterBitmask   Output buffer for the retrieved bitmask.
 * @param[out]  phJob              Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM              The given status flags pointer is invalid
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_ERR_NOT_IMPLEMENTED            The ReadRegister function is not implemented.
 *   - @ref ecy_hsm_CSAI_ERR_SECFUNC_LOCKED             This security-critical functions is disabled until the next reset
 *   - @ref ecy_hsm_CSAI_ERR_INCONSISTENT_PARAM_SET     The Parity bit of at least one device configuration is not valid,
 *                                                      content of device configuration will provided even if parity bit not valid.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_System_ReadRegister(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                             ecy_hsm_Csai_JobPriorityT   priority,
                                                                                             uint32                      registerAddress,
                                                                                             uint8*                      pRegisterSize,
                                                                                             uint8*                      pRegisterValue,
                                                                                             uint8*                      pRegisterBitmask,
                                                                                             ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * @brief Retrieves HSM firmware verification state.
 *
 * @details This interface triggers a firmware verification.
 * If the result is ecy_hsm_CSAI_FW_STATE_VALID_V1, a valid and bootable firmware is detected.
 * Error can be derived by the bits of pHSMVerificationStatus_VX.
 *
 * @note
 * This Interface is only supported in bank swap mode.
 * If bank swap mode is inactive the error ecy_hsm_CSAI_ERR_NOT_SUPPORTED is returned.
 *
 * @note
 * Before a bank swap is triggered it is recommended to check the inactive bank for a valid and bootable firmware
 * using this function.
 *
 * @param[in]        hSession                           Handle to the session in which the job is placed
 * @param[in]        priority                           Requested scheduling priority for this job on the HSM
 * @param[in]        memRangeStart                      Start address of HSM which should be verified
 *                                                      (on active bank at HSM_CORE_FLASH_BASE
 *                                                      or inactive bank shifted by offset).
 * @param[in,out]    pVerificationResult                ->fwVerificationVersion      Version of the firmware
 *                                                                                   verification scheme
 *                                                      ->pHSMVerificationStatus_VX  Receives the HSM firmware
 *                                                                                   verification information
 * @param[out]       phJob                              Receives the job handle of the initialized job
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to ecy_hsm_Csai_PollHandle
 *   - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION.         A pointer parameter references HSM internal memory.
 *   - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED              bank swap is not supported on the device.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM              The address in memRangeStart
 *                                                      or the pVerificationResult is invalid.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL
ecy_hsm_Csai_Verify_HSM_Firmware(ecy_hsm_Csai_SessionHandleT           hSession,
                                 ecy_hsm_Csai_JobPriorityT             priority,
                                 const uint32                          memRangeStart,
                                 ecy_hsm_Csai_FwVerificationStateRefT* pVerificationResult,
                                 ecy_hsm_Csai_JobHandleT*              phJob);
/**
 * [$DD 1539]
 * Returns HSM version based on the request format ID.
 * [$Satisfies $SW_ARCH E797CAE8]
 *
 * For Format version 2, HSM version together with the variant version is mapped to a number between 1 and 9999.
 * The version number will consist of four bytes and will be ASCII encoded. If the corresponding variant version info
 * is not found within HSM, the version number returned will be "9999" (0x39393939).
 * Also, until the final implementation is completed, the version number returned would be "9999" (0x39393939).
 *
 * @param[in]  hSession            Handle of the HSM session.
 * @param[in]  priority            Priority with which the job should be executed.
 * @param[in]  requestFormat       Request/response type format selected.
 * @param[out] phJob               Receives the job handle of the initialized job.
 * @param[in]  pRequestParams      Request parameters based on the Request type selected.
 *                                 Currently ignored.
 * @param[out] pVersionData        Output buffer containing the result. The type should be selected
 *                                 using parameter requestFormat. Currently only ecy_hsm_Csai_VersionParamsV2T
 *                                 is supported.
 *
 * @returns
 * @ref ecy_hsm_CSAI_SUCCESS             function call was successful.
 * @ref ecy_hsm_CSAI_ERR_INVALID_PARAM   Invalid parameters supplied.
 *
 * else                                  Other HSM errors.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_GetVersion(ecy_hsm_Csai_SessionHandleT   hSession,
                                                                                    ecy_hsm_Csai_JobPriorityT     priority,
                                                                                    ecy_hsm_Csai_JobHandleT*      phJob,
                                                                                    ecy_hsm_Csai_VersionFormatIdT requestFormat,
                                                                                    void*                         pRequestParams,
                                                                                    void*                         pVersionData);

/**
 * @brief
 * This function configures and initializes the HSM system interrupt control register
 * by setting the given configuration data as interrupt vector.
 * This interrupt can then be used as the wakeup factor from a lower power mode
 * according to the chosen power mode type.
 *
 * @param[in] hSession            Handle to the session in which the job will be placed.
 * @param[in] priority            Requested scheduling priority for this job on the HSM.
 * @param[in] pConfigData         Pointer to the power mode configuration data
 * @param[in] configDataLen       Length of the power mode configuration data in bytes
 * @param[in] configType          Power mode configuration type (see also @ref ecy_hsm_Csai_ConfigPowerModeType)
 *                                of the given configuration data
 * @param[out] phJob              Receives the job handle of the initialized job.
 *
 * @return
 * - @ref ecy_hsm_CSAI_SUCCESS                    The call succeeded.
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM          A given parameter is invalid.
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED          The feature is not supported for the given config type.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_Config_PowerMode(ecy_hsm_Csai_SessionHandleT   hSession,
                                                                                          ecy_hsm_Csai_JobPriorityT     priority,
                                                                                          ecy_hsm_Csai_ConfigPowerModeT configType,
                                                                                          void*                         pConfigData,
                                                                                          uint32                        configDataLen,
                                                                                          ecy_hsm_Csai_JobHandleT*      phJob);

/**
 * [$DD 1678]
 * @brief Free memory space for HSM secure storage (EEPROM) by triggering FEE reorganisation manually
 *        from host side.
 * [$Satisfies $SW_ARCH 1037]
 *
 * @param[in]   hSession     Handle to the session in which the job will be placed.
 * @param[in]   priority     Not applicable, since just BACKGROUND priority for this
 *                           job is allowed. Any input will be overriden.
 * @param[out]  phJob        Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED          There was another job already in progress in the session
 * - @ref ecy_hsm_CSAI_ERR_EEPROM_EMULATION             The EEPROM emulation returned an error
 * - @ref ecy_hsm_CSAI_ERR_EEPROM_FULL                  The EEPROM emulation is full
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                Manually triggering FEE reorg is not supported
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_FEEMGR_TriggerReorg(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                             ecy_hsm_Csai_JobPriorityT   priority,
                                                                                             ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 1679]
 * @brief Check if a total amount of data size to write to the HSM secure storage (for a particular data block ID)
 *        would trigger an FEE hard reorganisation.
 * [$Satisfies $SW_ARCH 1038]
 *
 * @note
 * - IMPORTANT: Since this function only returns the availability of DFLASH space at the requested time,
 *   please be careful that the returned results might not be accurate anymore if multiple concurrent
 *   activities (HSM background tasks, or parallel HOST calls to HSM) write to the DFLASH and reduce
 *   its space.
 *
 * - This function uses a ecy_hsm_Csai_FeeMgr_FeeParamT structure which stores the parameters
 *   related to FEE reorganisation, and can be extendable in the future by using the version parameter
 *   feeParamsVersion.
 *
 *   If feeParamsVersion is ecy_hsm_CSAI_FEEMGR_STRUCT_VERSION_0 then the following parameters as used:
 *    - ecy_hsm_Csai_FeeMgr_FeeParamT.tag                  [in] Id of the data block to be examined.
 *
 *       Valid data ID is for all available entries in <code>ecy_hsm_csai_keyid.h</code>, with
 *       the condition is that the data must be available on DFLASH only.
 *
 *    - ecy_hsm_Csai_FeeMgr_FeeParamT.sizeToCheck          [in] The total amount of data size to be checked
 *                                                              against the reorganisation threshold. To write this
 *                                                              much data, multiple DFLASH write cycles can be performed.
 *    - ecy_hsm_Csai_FeeMgr_FeeParamT.isSafeToWrite       [out] Status indicating if sizeToCheck amount is
 *                                                              possible to write without triggering FEE hard
 *                                                              reorganisation.
 *    - ecy_hsm_Csai_FeeMgr_FeeParamT.possibleNumWrites   [out] The maximum number of FEE write for this ID
 *                                                              without triggering hard reorganisation. Note that
 *                                                              this value is not necessarily the amount of write
 *                                                              cycles to write sizeToCheck.
 *
 * - FEE works by writing the entire data block with constant block size (depending on data ID),
 *   regardless of the length of user data. Optionally, This API returns the amount of data blocks
 *   available to write before hitting the FEE hard reorganisation threshold on DFLASH.
 *
 * @param[in]       hSession            Handle to the session in which the job will be placed.
 * @param[in]       priority            Not applicable, since just BACKGROUND priority for this
 *                                      job is allowed. Any input will be overriden.
 * @param[in]       feeParamsVersion    The version ID of the FEE parameters structure.
 * @param[in,out]   pFeeParams          Pointer to buffer for parameters on FEE reorganisation.
 *                                      ( ecy_hsm_Csai_FeeMgr_FeeParamT )
 * @param[in]       feeParamsLength     Length of the pFeeParams buffer, must be the same size as
 *                                      the ecy_hsm_Csai_FeeMgr_FeeParamT structure.
 * @param[out]      phJob               Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED          There was another job already in progress in the session
 * - @ref ecy_hsm_CSAI_ERR_EEPROM_EMULATION             The EEPROM emulation returned an error
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                This API is not supported for the running target
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL
ecy_hsm_Csai_FEEMGR_CheckReorgOnWrite(ecy_hsm_Csai_SessionHandleT          hSession,
                                      ecy_hsm_Csai_JobPriorityT            priority,
                                      ecy_hsm_Csai_FeeMgr_StructVersionIdT feeParamsVersion,
                                      void*                                pFeeParams,
                                      uint32                               feeParamsLength,
                                      ecy_hsm_Csai_JobHandleT*             phJob);

/**
 * [$DD 1787]
 * [$Satisfies $SW_ARCH 1076]
 * @brief Function to return the hashes of HSM parts (Core, Bootloader, Config or Complete HSM)
 *
 * @param[in]     hSession               Handle to the session in which the job will be placed.
 * @param[in]     priority               Requested scheduling priority for this job on the HSM.
 * @param[in]     fwIntegrityDataVersion Version of the request/response structure being passed.
 * @param[in,out] pValidationData        Pointer to the structure containing the version information for
 *                                       output data and a pointer to receive output data.
 * @param[out]    phJob                  Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                       The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE            The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                       Another job is still pending completion in this session.
 *                                                     Either finish the previous job or cancel the running job
 *                                                     using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM             A parameter was invalid
 *   - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED             This request or its parameters are not supported
 *   - @ref ecy_hsm_CSAI_ERR_CYCURLIB                  Underlying library returned an error
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL
ecy_hsm_Csai_Misc_GetHsmIntegrityData(ecy_hsm_Csai_SessionHandleT          hSession,
                                      ecy_hsm_Csai_JobPriorityT            priority,
                                      ecy_hsm_Csai_FwIntegrityDataVersionT fwIntegrityDataVersion,
                                      void*                                pValidationData,
                                      ecy_hsm_Csai_JobHandleT*             phJob);
/**
 * [$DD 2895]
 * [$Satisfies $SW_ARCH C138583C] [$Satisfies $SW_ARCH 9CA2DAE8]
 * @brief The function verifies if the registers specified by the user do not have the defined values according to the usecase.
 * This feature is available on RH850 U2A target and the list of registers considered for verification is
 * OCDID, SPID, CUSTOMERIDA/B/C,CTESTID.
 *
 * @param[in]     hSession               Handle to the session in which the job will be placed.
 * @param[in]     priority               Requested scheduling priority for this job on the HSM.
 * @param[in]     useCaseId              It contains information about the use case Id (see also @ref ecy_hsm_Csai_VerifyRegisterUseCaseTag).
 *                                       Currently only ecy_hsm_CSAI_VERIFY_REGISTER_AGAINST_DEFAULT_VAL_USECASE use case is supported.
 * @param[inout]  pRegisterParam         A pointer that stores the addresses of registers and their corresponding verify result values (see also @ref ecy_hsm_Csai_VerifyRegisterParam).
 * @param[in]     totalNumOfRegisters    Overall count of registers that have been requested for verification
 * @param[out]    phJob                  Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                       The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE            The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                       Another job is still pending completion in this session.
 *                                                     Either finish the previous job or cancel the running job
 *                                                     using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM             A parameter was invalid
 *   - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED             This request or its parameters are not supported
 *   - @ref ecy_hsm_CSAI_ERR_SECFUNC_LOCKED            Security critical functions are currently disabled
 *                                                     (see @ref ecy_hsm_Csai_Protection_DisableSecCritFunctions)
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_System_VerifyRegister(ecy_hsm_Csai_SessionHandleT         hSession,
                                                                                               ecy_hsm_Csai_JobPriorityT           priority,
                                                                                               ecy_hsm_Csai_VerifyRegisterUseCaseT useCaseId,
                                                                                               void*                               pRegisterParam,
                                                                                               uint16                   totalNumOfRegisters,
                                                                                               ecy_hsm_Csai_JobHandleT* phJob);

/**
 * [$DD 2978]
 * [$Satisfies $SW_ARCH 714D4107]
 * @brief The function verifies the HSM configuration register against the correct value configured.
 * This feature is available on RH850 U2A targets, and it verifies if the HSM P-Flash and
 * HSM D-Flash start addresses are configured correctly by checking the values from the
 * ICUM_OPBT2 and ICUM_OPBT3 configuration areas.
 *
 * @param[in]     hSession               Handle to the session in which the job will be placed.
 * @param[in]     priority               Requested scheduling priority for this job on the HSM.
 * @param[out]    phJob                  Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                       The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE            The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                       Another job is still pending completion in this session.
 *                                                     Either finish the previous job or cancel the running job
 *                                                     using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 *     @ref ecy_hsm_CSAI_ERR_INVALID_HSM_CONFIGURATION Verification fails, configuration register has incorrect values.
 *   - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED             This request or its parameters are not supported
 *   - @ref ecy_hsm_CSAI_ERR_SECFUNC_LOCKED            Security critical functions are currently disabled
 *                                                     (see @ref ecy_hsm_Csai_Protection_DisableSecCritFunctions)
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_System_VerifyHsmConfiguration(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                                       ecy_hsm_Csai_JobPriorityT   priority,
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

#endif /* Multiple inclusion lock  */
