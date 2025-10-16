/**
 * @file
 ***********************************************************************************************
 * @brief SHE (+) command interface.
 * This header file is part of the CycurHSM's Secure Hardware Extensions command interface
 * and specifies types and functions for interfacing with the SHE emulation in the HSM.
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2014, all rights reserved
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_SERVICE_MISC_H
#define ECY_HSM_SERVICE_MISC_H

/**
 * @addtogroup GROUP_HSM_BRIDGE_PUBLIC_TYPES
 * @{
 */

/* *** includes *******************************************************************************/
#include "ecy_hsm_csai.h"
#include "ecy_hsm_csai_misc.h"

/* *** defines ********************************************************************************/

/** Define for max size of param block in buffer */
#define HSM_OP_PARAM_BLOCK_SIZE 60

/** Define HSM operational modes */
typedef enum HSM_ModeTag
{
    /** The HSM has not been started */
    HSM_MODE_NOT_STARTED                    = 1U,
    /** The HSM has booted but not is yet in either full bootloader or application mode */
    HSM_MODE_BOOTING                        = 2U,
    /** The HSM is running in bootloader mode */
    HSM_MODE_BOOTLOADER                     = 3U,
    /** The HSM is running in core application (normal) mode */
    HSM_MODE_CORE_APP                       = 4U,
    /** The HSM mode is invalid */
    HSM_MODE_INVALID                        = 5U,
    /** The HSM is running in core application (stopped) mode */
    HSM_MODE_CORE_APP_STOPPED               = 6U,
    /** The HSM is running in suspended mode */
    HSM_MODE_SUSPENDED                      = 7U,
    /** The HSM transitions from core to bootloader in order to remain there, e.g., triggered via @ref ecy_hsm_Csai_SecFlash_Init */
    HSM_MODE_SWITCHING_FROM_CORE_TO_BOOT    = 8U,
    /** Reserved value. Ensures enum is 32-bit wide. */
    HSM_MODE_RESERVED                       = 0x7FFFFFFFU
} HSM_ModeT;

/** @brief Enumeration for the status of a port/job/operation on the HSM */
typedef enum HSM_PortStatusTag
{
    HSM_STATUS_IDLE = 0U,                 /**< No operation loaded on this port                                  */
    HSM_STATUS_PENDING,                   /**< Operation loaded on this port, not processing yet                 */
    HSM_STATUS_PROCESSING,                /**< Operation being processed on this port                            */
    HSM_STATUS_COMPLETE,                  /**< Operation has completed on this port                              */
    HSM_STATUS_TRANSMIT_JOB,              /**< Operation is loaded on this port and HSM needs to receive the job
                                               This state is present only when ECY_HSM_VMS_FS_HOST_NO_WAIT_MODE
                                               is enabled                                                        */
    HSM_PORTSTATUS_RESERVED = 0x7fffffffU /**< Value defined to use memory size of uint32 for enums              */
} HSM_PortStatusT;

/** @brief Structure to contain HSM Core diagnostics information */
typedef struct HSM_DiagnosticsDataTag
{
    uint32 CoreFrequencyHz;          /**< The core clock frequency in Hz, measured by the CMU against the INTOSC */
    uint32 clockConfigureMaxStack;   /**< Max stack usage by the HSM_ClockConfigure ISR                          */
    uint32 configureMaxStack;        /**< Max stack usage by the HSM_Configure ISR                               */
    uint32 openSessionMaxStack;      /**< Max stack usage by the HSM_Open Session ISR                            */
    uint32 operationRequestMaxStack; /**< Max stack usage by the HSM_OperationReq ISR                            */
    uint32 cancelOperationMaxStack;  /**< Max stack usage by the HSM_CancelOperation ISR                         */
    uint32 millisecondMaxStack;      /**< Max stack usage by the Millisecond ISR                                 */
    uint32 housekeeperMaxStack;      /**< Max stack usage by the Housekeeper task                                */
    uint32 workerBackgroundMaxStack; /**< Max stack usage by the WorkerBackground task                           */
    uint32 workerMediumMaxStack;     /**< Max stack usage by the WorkerMedium task                               */
    uint32 workerHighMaxStack;       /**< Max stack usage by the WorkerHigh task                                 */
} HSM_DiagnosticsDataT;

/** Structure for the data passed to a GetVersion operation */
typedef struct HSM_GetVersionParamTag
{
    ecy_hsm_Csai_VersionDataT* pVersionData; /**< Pointer to buffer for the version information */
} HSM_GetVersionParamT;

/** Structure for the data passed to a VerifyFirmware operation */
typedef struct HSM_VerifyFirmwareTag
{
    ecy_hsm_Csai_FwVerificationStateRefT* pVerificationData; /**< Pointer to buffer for the version information       */
    uint32                                memRangeStart;     /**< HSM start address which should be verified          */
} HSM_VerifyFirmwareT;

/** Structure for the data passed to a GetDiagnostics operation */
typedef struct HSM_GetDiagnosticsParamTag
{
    HSM_DiagnosticsDataT* pDiagnosticsData; /**< Pointer to buffer for the diagnostics information */
} HSM_GetDiagnosticsParamT;

/** Structure for the data passed to a set serial number operation */
typedef struct HSM_SetSerialNoParamTag
{
    uint8* pBufferSerialNo;      /**< Pointer to serial number           */
    uint8  bufferLengthSerialNo; /**< Length of the serial number buffer */
} HSM_SetSerialNoParamT;

/** Structure for the data passed to a get device id operation */
typedef struct HSM_GetDeviceIdParamTag
{
    uint8* pNumBytesBufferSerialNo; /**< Pointer to length of the serial number buffer */
    uint8* pBufferSerialNo;         /**< Pointer to serial number                      */
    uint8* pNumBytesBufferChipId;   /**< Pointer to length of chip id buffer           */
    uint8* pBufferChipId;           /**< Pointer to chip id                            */
} HSM_GetDeviceIdParamT;

/** Structure for the data passed to a SessionOpen ISR  */
typedef struct HSM_SessionOpenTag
{
    ecy_hsm_Csai_ErrorT         errorCode;       /**< Error code or ecy_hsm_CSAI_SUCCESS if no error */
    ecy_hsm_Csai_JobPriorityT   initialPriority; /**< Initial priority for the session               */
    ecy_hsm_Csai_SessionHandleT hSession;        /**< The HSM will write the session handle to here  */
} HSM_SessionOpenT;

/** Structure to copy the intermediate SessionOpen ISR parameters incase of no wait mode */
typedef struct HSM_SessionOpenNoWaitModeTag
{
    ecy_hsm_Csai_ErrorT         errorCode;       /**< Error code or ecy_hsm_CSAI_SUCCESS if no error */
    ecy_hsm_Csai_SessionHandleT hSession;        /**< HSM session handle copied from HSM buffer to intermediate buffer */
} HSM_SessionOpenNoWaitModeT;

/** Structure for the data passed to a SessionStatus operation  */
typedef struct HSM_SessionStatusTag
{
    ecy_hsm_Csai_SessionStatusT* pSessionStatus; /**< Pointer to buffer for the session status information */
} HSM_SessionStatusT;

/** Parameter used for config area read out of generic data */
typedef struct HSM_ConfigReadGenericDataParamTag
{
    uint8*  pData;             /**< Pointer to a buffer to read the generic data into */
    uint32  numBytesData;      /**< Length of the buffer @p pData points to           */
    uint32* pNumBytesDataRead; /**< Number of bytes actually read into the buffer     */
} HSM_ConfigReadGenericDataParamT;

/** Structure for the parameters passed to the system function ecy_hsm_Csai_System_ReadRegister */
typedef struct HSM_SystemReadRegisterParamTag
{
    uint32 registerAddress;  /**< Address of the register to be read */
    uint8* pRegisterSize;    /**< Size of the register to be read out in bytes */
    uint8* pRegisterValue;   /**< Output buffer for the retrieved register value */
    uint8* pRegisterBitmask; /**< Output buffer for the retrieved bitmask*/
} HSM_SystemReadRegisterParamT;

/** Structure for the parameters passed to the function @ref ecy_hsm_Csai_GetVersion
 *  @note: The structure would be renamed in the future, introducing a breaking change.
 */
typedef struct HSM_GetVersionAndEncodingParamTag
{
    void*                         pRequestParams; /**< Request parameters. Depend on the format type */
    void*                         pVersionData;   /**< Response parameters. Depend on the format type */
    ecy_hsm_Csai_VersionFormatIdT requestFormat;  /**< The format of request / response structures. */
} HSM_GetVersionAndEncodingParamT;

/** Parameter used for configuring the power mode */
typedef struct HSM_PowerModeConfigDataParamTag {
    ecy_hsm_Csai_ConfigPowerModeT configType;   /**< Configuration type for power mode */
    void  *pConfigData;                         /**< Pointer to the configuration data for deep sleep */
    uint32 configDataLen;                       /**< Length of the configuration data for deep sleep in bytes */
} HSM_PowerModeConfigDataParamT;

/** Structure for the data passed to a FEE manager - check for FEE reorganisation */
/* TODO: unify the naming scheme for void* param concept */
typedef struct HSM_FEEManagerCheckReorgParamTag
{
    ecy_hsm_Csai_FeeMgr_StructVersionIdT version;         /**< Version ID of the structure for pFeeParams              */
    void*                                pFeeParams;      /**< Pointer to a structure of parameters for the FEE manager */
    uint32                               feeParamsLength; /**< Length of the FEE parameter structure */
} HSM_FEEManagerCheckReorgParamT;

/** Structure for data passed in API @ref ecy_hsm_Csai_Misc_GetHsmIntegrityData */
typedef struct HSM_PartVerificationDataParamTag
{
    ecy_hsm_Csai_FwIntegrityDataVersionT fwIntegrityDataVersion; /**< Version number for the request/response structure */
    void*                                pVerificationData;      /**< Actual request/response structure */
} HSM_PartVerificationDataParamT;

/** Structure for data passed in API @ref ecy_hsm_Csai_System_VerifyRegister */
typedef struct HSM_VerifyRegisterParamTag
{
    void*                                pVerifyRegister;       /**< It holds the use case Id and Verify register address and result value structure */
    ecy_hsm_Csai_VerifyRegisterUseCaseT  useCaseId;             /**< Determines the Verify register use case to be supported */
    uint16                               totalNumOfRegisters;   /**< Total number of registers requested for verification */
} HSM_VerifyRegisterParamT;


/* *** exported interfaces ********************************************************************/

/* *INDENT-OFF* */
#ifdef __cplusplus
extern "C"
{
#endif
/* *INDENT-ON* */

/* *INDENT-OFF* */
#ifdef __cplusplus
} /* extern "C" */
#endif
/* *INDENT-ON* */

/**
 * @}
 */
#endif /* Multiple inclusion lock  */
