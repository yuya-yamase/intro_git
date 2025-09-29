/**
 * @file
 ***********************************************************************************************
 * @brief This header file defines the structures and enums used for host <-> HSM communications
 * @details This is the basic header file, ecy_hsm_service.h is the public one for the bridge
 * interface
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2014, all rights reserved
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_SERVICE_BASIC_H
#define ECY_HSM_SERVICE_BASIC_H

/**
 * @addtogroup GROUP_HSM_BRIDGE_PUBLIC_TYPES
 * @{
 */

/* *** includes *******************************************************************************/
#include "ecy_hsm_service_misc.h"
#include "ecy_hsm_csai_trusted_boot.h"

#if defined(GUAM)
#include "ecy_hsm_general.h"
#else
#include "ecy_hsm_general_pubcfg.h"
#endif

#include "ecy_hsm_timing_diagnostics.h"

/* *** type declarations **********************************************************************/

/** @brief Enumeration to define the function requested on the HSM core. Numbers are fixed to obtain
 *         backward compatibility.
*/
typedef enum HSM_FunctionTag {
    HSM_FUNC_NONE             = 0,  /**< No function                                             */
    HSM_FUNC_DIAGNOSTICS      = 2,  /**< Provide HSM core diagnostics information                */
    HSM_FUNC_SHE_MAC_GENERATE = 46, /**< CMAC generation                                         */
    HSM_FUNC_SHE_MAC_VERIFY   = 47, /**< CMAC verification                                       */
    HSM_FUNC_CMAC_GENERATE    = 63, /**< Perform a fast Mac generation                           */
    HSM_FUNC_CMAC_VERIFY      = 64, /**< Perform a fast Mac Verification                         */
    HSM_FUNC_SIPHASH_GENERATE = 65, /**< Perform a fast Mac generation                           */
    HSM_FUNC_SIPHASH_VERIFY   = 66, /**< Perform a fast Mac Verification                         */

    HSM_FUNC_RESERVED = 0x7FFFFFFFU /**< Value defined to use memory size of uint32 for enums    */
} HSM_FunctionT;

/** @brief Enumeration to define the suspend functions requested on the HSM core     */
typedef enum HSM_SuspendFunctionTag {
    HSM_SUSP_NONE = 0,                      /**< No function                                         */
    HSM_SUSP_START,                         /**< Suspend Start                                       */
    HSM_SUSP_KEEP,                          /**< Suspend Keep                                        */
    HSM_SUSP_LEAVE,                         /**< Suspend Leave                                       */
    HSM_SUSP_DISABLE_SECCRIT,               /**< Suspend - Disable Security critical functions       */
    HSM_SUSP_RESERVED = 0x7FFFFFFFU         /**< Value defined to use memory size of uint32 for enums*/
} HSM_SuspendFunctionT;

/* *** type declarations **********************************************************************/


/* *** global constants ***********************************************************************
 * HSM <-> Host flag definitions
 *
 * Remember that these trigger interrupts so RTA-OS interrupts will need to be adjusted if these are changed
 * Don't use the bitwise access for clearing flags because it is a read-then-write
 * And don't use bitwise access for setting flags either because that will cause repeated setting of bits and
 * could lead to a race condition.
 */

/* Host to HSM flags register bit fields    */
#if (ECY_HSM_VMS_ARCH_FAMILY == ECY_HSM_VMS_ARCH_FAMILY_STSR6)
/* ST SR6 has a completely different IRQ mapping due to 4 bridges;
 * therefore as a first solution, these common bits are adapted.
 */
#define HT2HSMF_QUICK_ROUTE              (0x00000001U) /**< b01 is set to request a quick CMAC calculation                                              */
#define HT2HSMF_REQUEST                  (0x00000002U) /**< b02 is set to indicate a request message is in the HT2HSM status register                   */
#define HT2HSMF_SUSPEND                  (0x00000004U) /**< b03 is set to request an HSM suspend operation                                              */
#define HT2HSMF_SESSION_OPEN             (0x00000008U) /**< b04 is set to indicate a session open message is in the HT2HSM status register              */
#define HT2HSMF_CANCEL                   (0x00000010U) /**< b05 is set to indicate a cancellation message is in the HT2HSM status register              */
#define HT2HSMF_MTNC_REQUEST             (0x00000020U) /**< b06 is set to indicate an HSM maintenance request in the HT2HSM flag register               */
#define HT2HSMF_SECCRIT_FUNC             (0x00000040U) /**< b07 is used to indicate DisableSecCritFunctions                                             */
#define HT2HSMF_SUSPEND_SHARED_RAM_WRITE (0x00000080U) /**< b08 is used to request HSM to suspend the write to shared ram                              */
#define HT2HSMF_CONFIGURE                (0x00000100U) /**< b09 is set to indicate a configuration message is in the HT2HSM status register             */
/*                                       (0x00000200U)      b10 currently free */
#define HT2HSMF_CLOCK_CONFIG             (0x00000400U) /**< b11 is set to indicate a clock config message is in the HT2HSM status register              */
#define HT2HSMF_RESET                    (0x00000800U) /**< b12 is set to indicate a reset request to the HSM. HT2HSM should be ignored                 */
/*                                       (0x00001000U)      b13 currently free */
/*                                       (0x00002000U)      b14 currently free */
/*                                       (0x00004000U)      b15 currently free */
/*                                       (0x00008000U)      b16 currently free */
/*                                       (0x00010000U)      b17 currently free */
/*                                       (0x00020000U)      b18 currently free */
/*                                       (0x00040000U)      b19 currently free */
/*                                       (0x00080000U)      b20 currently free */
/*                                       (0x00100000U)      b21 currently free */
/*                                       (0x00200000U)      b22 currently free */
/*                                       (0x00400000U)      b23 currently free */
/*                                       (0x00800000U)      b24 currently free */
/*                                       (0x01000000U)      b25 currently free */
/*                                       (0x02000000U)      b26 currently free */
/*                                       (0x04000000U)      b27 currently free */
#define HT2HSMF_SECDEBUG_CONFIGURE       (0x08000000U) /**< b28 is set to indicate secure debug configuration for rh850 targets */
#define HT2HSMF_TEST_EVENT               (0x10000000U) /**< b29 request to handle a test event                                                          */
#define HT2HSMF_HOST_SECBOOT_PROCESSED   (0x20000000U) /**< b30 Host processed the Start Address of software part from SecBoot with direct release      */
#define HT2HSMF_HOST_STORAGE_CONFIG      (0x40000000U) /**< b31 is set to indicate that a host storage config message is in the HT2HSM status register  */
#define HT2HSMF_RELEASE                  (0x80000000U) /**< b32 is set to indicate that the HSM may now access its FLASH (FLASH setup is complete)      */

#define HT2HSMF_ALL_FLAGS                (0x0000FFFFUL) /**< All possible flags except functions handled by HSM boot exclusively                         */

#else
#define HT2HSMF_RELEASE                  (0x00000001U) /**< b01 is set to indicate that the HSM may now access its FLASH (FLASH setup is complete)       */
#define HT2HSMF_HOST_STORAGE_CONFIG      (0x00000002U) /**< b02 is set to indicate that a host storage config message is in the HT2HSM status register   */
#define HT2HSMF_HOST_SECBOOT_PROCESSED   (0x00000004U) /**< b03 Host processed the Start Address of software part from SecBoot with direct release       */
/*                                       (0x00000008U)      b04 currently free */
/*                                       (0x00000010U)      b05 currently free */
/*                                       (0x00000020U)      b06 currently free */
/*                                       (0x00000040U)      b07 currently free */
/*                                       (0x00000080U)      b08 currently free */
/*                                       (0x00000100U)      b09 currently free */
/*                                       (0x00000200U)      b10 currently free */
/*                                       (0x00000400U)      b11 currently free */
/*                                       (0x00000800U)      b12 currently free */
/*                                       (0x00001000U)      b13 currently free */
/*                                       (0x00002000U)      b14 currently free */
/*                                       (0x00004000U)      b15 currently free */
/*                                       (0x00008000U)      b16 currently free */
/*                                       (0x00010000U)      b17 currently free */
/*                                       (0x00020000U)      b18 currently free */
/*                                       (0x00040000U)      b19 currently free */
#define HT2HSMF_SUSPEND_SHARED_RAM_WRITE (0x00080000U) /**< b20 is used to request HSM to suspend the write to shared ram                              */
#define HT2HSMF_SECCRIT_FUNC             (0x00100000U) /**< b21 is used to indicate DisableSecCritFunctions                                             */
#define HT2HSMF_MTNC_REQUEST             (0x00200000U) /**< b22 is set to indicate an HSM maintenance request in the HT2HSM flag register               */
#define HT2HSMF_SUSPEND                  (0x00400000U) /**< b23 is set to request an HSM suspend operation                                              */
#define HT2HSMF_QUICK_ROUTE              (0x00800000U) /**< b24 is set to request a quick CMAC calculation                                              */
#define HT2HSMF_CANCEL                   (0x01000000U) /**< b25 is set to indicate a cancellation message is in the HT2HSM status register              */
#define HT2HSMF_REQUEST                  (0x02000000U) /**< b26 is set to indicate a request message is in the HT2HSM status register                   */
#define HT2HSMF_SESSION_OPEN             (0x04000000U) /**< b27 is set to indicate a session open message is in the HT2HSM status register              */
#define HT2HSMF_CONFIGURE                (0x08000000U) /**< b28 is set to indicate a configuration message is in the HT2HSM status register             */
#define HT2HSMF_TEST_EVENT               (0x10000000U) /**< b29 request to handle a test event                                                          */
#define HT2HSMF_SECDEBUG_CONFIGURE       (0x20000000U) /**< b30 is set to indicate secure debug configuration for rh850 targets */
#define HT2HSMF_CLOCK_CONFIG             (0x40000000U) /**< b31 is set to indicate a clock config message is in the HT2HSM status register              */
#define HT2HSMF_RESET                    (0x80000000U) /**< b32 is set to indicate a reset request to the HSM. HT2HSM should be ignored                 */

/* Mask definitions */
#define HT2HSMF_ALL_FLAGS                (0xFFFF0000U) /**< All possible flags                                                                          */
#endif /* #if (ECY_HSM_VMS_ARCH_FAMILY == ECY_HSM_VMS_ARCH_FAMILY_STSR6) */

/* HSM to Host flags register bit fields    */
#define HSM2HTF_HSM_READY                (0x00000001U) /**< b01 is set to tell the host BAF code that the HSM has initialised and the BAF may proceed    */
#define HSM2HTF_SECBOOT_FINISHED         (0x00000002U) /**< b02 SecBoot with direct release was successful and address of authentic SW-PART in status    */
#define HSM2HTF_GHSM_HBMI_READY          (0x00000004U) /**< b03 is set to indicate that host boot manager interface is ready, especially after reset     */
/*                                       (0x00000008U)      b04 currently free */
/*                                       (0x00000010U)      b05 currently free */
/*                                       (0x00000020U)      b06 currently free */
/*                                       (0x00000040U)      b07 currently free */
/*                                       (0x00000080U)      b08 currently free */
/*                                       (0x00000100U)      b09 currently free */
/*                                       (0x00000200U)      b10 currently free */
/*                                       (0x00000400U)      b11 currently free */
/*                                       (0x00000800U)      b12 currently free */
/*                                       (0x00001000U)      b13 currently free */
/*                                       (0x00002000U)      b14 currently free */
/*                                       (0x00004000U)      b15 currently free */
/*                                       (0x00008000U)      b16 currently free */
/*                                       (0x00010000U)      b17 currently free */
/*                                       (0x00020000U)      b18 currently free */
/*                                       (0x00040000U)      b19 currently free */
#define HSM2HTF_SUSPEND_SHARED_RAM_WRITE (0x00080000U) /**< b20 is set to indicate suspend shared ram write operation completed                         */
#define HSM2HTF_SECCRIT_FUNC             (0x00100000U) /**< b21 is set to acknowledge an HSM Disable                                                    */
#define HSM2HTF_MTNC_REQUEST             (0x00200000U) /**< b22 is set to acknowledge an HSM maintenance request                                        */
#define HSM2HTF_SUSPEND                  (0x00400000U) /**< b23 is set to acknowledge an HSM suspend operation                                          */
/*                                       (0x00800000U)      b24 currently free */
#define HSM2HTF_CANCELLED                (0x01000000U) /**< b25 is set to acknowledge cancellation of the current/latest operation on the given session */
#define HSM2HTF_ERRORMSG                 (0x02000000U) /**< b26 is set when the HSM has written data to the error message buffer                        */
/*                                       (0x04000000U)      b27 currently free */
/*                                       (0x08000000U)      b28 currently free */
#define HSM2HTF_TEST_EVENT               (0x10000000U) /**< b29 is set to acknowledge a test event */
#define HSM2HTF_SECDEBUG_CONFIGURE       (0x20000000U) /**< b30 is set to acknowledge secure debug configuration for rh850 */
/*                                       (0x40000000U)      b31 currently free */
/*                                       (0x80000000U)      b32 currently free */

/* Mask definitions */
#define HSM2HTF_ALL_FLAGS                (0xFFFFFFFFU) /**< All possible flags                                                                          */

/* HSM to Host status register bit fields                                                                                 */
/* SHE CMD_BOOT_FAILURE needs to be able to clear the SHE_SECURE_BOOT_OK even if it was set by a successful secure boot.
 * Therefore these flags can't be in the flags register because it is not possible for the HSM to clear those flags.      */
/*                                       (0x00000001U)      b01 currently free */
#define HSM2HTS_SHE_SECURE_BOOT_ACTIVE   (0x00000002U) /**< b02 is set while the SHE secure booting is running                                                                                                 */
#define HSM2HTS_SHE_SECURE_BOOT_INIT     (0x00000004U) /**< b03 is set if the secure boot was the first time and a MAC was calculated                                                                          */
#define HSM2HTS_SHE_SECURE_BOOT_FINISHED (0x00000008U) /**< b04 is set when the secure boot has finished                                                                                                       */
#define HSM2HTS_SHE_SECURE_BOOT_OK       (0x00000010U) /**< b05 is set if the secure boot was successful (MAC matched)                                                                                         */
#define HSM2HTS_SHE_RND_INIT             (0x00000020U) /**< b06 is set if the random number generator has been initialised                                                                                     */
#define HSM2HTS_SHE_EXT_DEBUGGER         (0x00000040U) /**< b07 is set if an external debugger is connected to the chip                                                                                        */
#define HSM2HTS_SHE_INT_DEBUGGER         (0x00000080U) /**< b08 is set if an internal debugger is connected to the chip                                                                                        */
#define HSM2HTS_ERR_EEPROM_INIT          (0x00000100U) /**< b09 is set to indicate that EEPROM initialization failed during HSM startup                                                                        */
#define HSM2HTS_ERR_CRYPTO_INIT          (0x00000200U) /**< b10 is set to indicate that crypto initialization failed during HSM startup                                                                        */
#define HSM2HTS_ERR_KEYSTORE_INIT        (0x00000400U) /**< b11 is set to indicate that keystore initialization failed during HSM startup                                                                      */
#define HSM2HTS_ERR_SHE_INIT             (0x00000800U) /**< b12 is set to indicate that SHE initialization failed during HSM startup                                                                           */
#define HSM2HTS_ERR_INTERNAL_CONFIG      (0x00001000U) /**< b13 is set to indicate that internal proxy initialization failed during HSM startup                                                                */
#define HSM2HTS_ERR_DATASTORE_INIT       (0x00002000U) /**< b14 is set to indicate that datastore initialization failed during HSM startup. In case if b28 already set, the meaning is generic datastore error */
#define HSM2HTS_ERR_MEM_PROT             (0x00004000U) /**< b15 is set to indicate that a memory protection exception occurred                                                                                 */
#define HSM2HTS_ERR_UNEXPECTED_EX        (0x00008000U) /**< b16 is set to indicate that an unexpected exception occurred (shared with HSM2HTS_ERR_OS_EXCEPTION)                                                */
#define HSM2HTS_ERR_OS_EXCEPTION         (0x00008000U) /**< b16 is set to indicate that an exception handled by the OS   (shared with HSM2HTS_ERR_UNEXPECTED_EX)                                               */
#define HSM2HTS_ERR_CACHRAM_ECC          (0x00010000U) /**< b17 is set to indicate that an exception occurred caused by access on cache RAM                                                                    */
#define HSM2HTS_ERR_LOCLRAM_ECC          (0x00020000U) /**< b18 is set to indicate that an exception occurred caused by access on local RAM                                                                    */
#define HSM2HTS_ERR_DATAFLSH_ECC         (0x00040000U) /**< b19 is set to indicate that an exception occurred caused by access on D-Flash                                                                      */
#define HSM2HTS_ERR_STOP_REQ             (0x00080000U) /**< b20 is set to indicate that a stop request occurred                                                                                                */
#define HSM2HTS_ERR_CODEFLSH_ECC         (0x00100000U) /**< b21 is set to indicate that a code flash ecc exception occurred                                                                                    */
#define HSM2HTS_BACKUP_BOOT              (0x00200000U) /**< b22 is set to indicate execution from the backup bootloader                                                                                        */
#define HSM2HTS_SUSPEND                  (0x00400000U) /**< b23 is set to indicate that the HSM has entered suspend mode                                                                                       */
#define HSM2HTS_HSM_REPROG               (0x00800000U) /**< b24 is set to indicate execution of HSM reprogramming mode                                                                                         */
#define HSM2HTS_ERR_CRYPTO_HW_EX         (0x01000000U) /**< b25 is set to indicate that an ECC exception occurred caused by accessing the cryptographic engines                                                */
#define HSM2HTS_UPDATE_BUSY              (0x02000000U) /**< @deprecated b26 is set to indicate that the HSM is busy during long operation of verification in HSM Update (unused)                               */
#define HSM2HTS_HSM_BUSY                 (0x02000000U) /**< b26 is set to indicate that the HSM is busy during non-preemptable operation                                                                       */
#define HSM2HTS_ERR_CMAC                 (0x04000000U) /**< b27 is set to indicate that the CMAC check over HSM CORE-App failed                                                                                */
#define HSM2HTS_CONFIGURED               (0x08000000U) /**< b28 is set to acknowledge a configuration message                                                                                                  */
#define HSM2HTS_CORE_APP                 (0x10000000U) /**< b29 is set to indicate that the HSM core  application has been started                                                                             */
#define HSM2HTS_BOOTLOADER               (0x20000000U) /**< b30 is set to indicate that the HSM is in bootloader mode                                                                                          */
#define HSM2HTS_CLOCK_CONFIGURED         (0x40000000U) /**< b31 is set to indicate that the HSM has actioned a clock configuration request                                                                     */
#define HSM2HTS_BOOTED                   (0x80000000U) /**< b32 is set to indicate that the HSM has booted                                                                                                     */

/* Mask definitions */
#define HSM2HTS_SHE_MASK                 (0x000000FFU) /**< Mask for the bits used for the SHE status register                       */
#define HSM2HTS_SHE_MASK_WO_EXT_DEBUGGER (0x000000BFU) /**< Mask for the bits used for SHE status register without EXT_DEBUGGER bit  */
#define HSM2HTS_ALL_MASK                 (0xFFFFFFFFU) /**< Mask for ALL bits                                                        */
#define HSM2HTS_ERROR_MASK               (0x0001FF00U) /**< Mask for the startup error flags                                         */
#define HSM2HTS_STOPPED_MASK             (0x001FC000U) /**< Mask for all fatal error conditions (HSM is stopped)                     */

/* *** exported interfaces ********************************************************************/

#if (ecy_hsm_HOST_STORAGE == ENABLED)

/** @brief Structure containing data for host storage synchronisation */
typedef struct HSM_HostStorageSyncTag{
    /**
     * @brief List of counter values that track when a section persist operation has been performed for a
     *        given section by using a counter value mechanism to detect changes
     *
     * @remarks The items addressed by this property are intended to be used exclusively by the host side of the
     *          host storage module and shall therefore not be changed by the HSM
     */
    uint16 *pPreviousCounter;

    /**
     * @brief List of counter values that track when a section was modified by using a counter value mechanism to
     *        signal a change happened
     *
     * @remarks The items addressed by this property are intended to be exclusively written by the HSM.
     *          The host may read them but shall not make any modifications to any items (except during the
     *          initialization phase)
     */
    uint16 *pCurrentCounter;
} HSM_HostStorageSyncT;

/**
 * @brief Structure containing data for the host storage cache
 *
 * @remarks Some elements in this structure have alignment constraints. As this data is read / written by the host
 *          and hsm, CPU memory cache needs to be considered to ensure stale data is not used and flushing certain
 *          cache lines won't cause inconsistency of data. Currently, the critical elements requiring alignment are:
 *          - @ref HSM_HostStorageCacheTag.pImage
 *          - @ref HSM_HostStorageCacheTag.sync
 *
 *          These constraints need to be accounted for when setting those properties
 */
typedef struct HSM_HostStorageCacheTag{
    uint8 *pImage;                                                  /**< Buffer for the HSM host storage cache image             */
    HSM_HostStorageSyncT sync;                                      /**< The synchronisation primitives                          */
    uint32 numSections;                                             /**< The number of sections in the data image[]              */
    uint32 numBytesPerSection;                                      /**< The number of bytes in each section of the data image[] */
} HSM_HostStorageCacheT;

#endif /* #if (ecy_hsm_HOST_STORAGE == ENABLED) */

typedef uint8 HSM_PortT;            /**< HSM Port index value type                              */


/** @brief Structure holding the safety-relevant jobs information */
typedef struct HSM_SafetyJobTag
{
   HSM_FunctionT function;     /**< Operation being performed */
} HSM_SafetyJobT;

/** @brief Structure containing the data held in the one host side bridge interface slot                      */
typedef struct HSM_HostSideBridgePortTag {
    HSM_PortStatusT status;                 /**< Operation status                                                     */
    ecy_hsm_Csai_ErrorT requestErrorCode;   /**< Error code returned from the operation request                       */
                                            /**< @details This is valid once the status >= HSM_STATUS_PENDING         */
    ecy_hsm_Csai_ErrorT opErrorCode;        /**< Error code returned from the operation completion                    */
                                            /**< @details This is valid once the status = HSM_STATUS_COMPLETE         */
    HSM_SafetyJobT  safetyJob;              /**< Safety-relevant jobs information                                     */
                                            /**< @details This information is required for the host-side safety check */
} HSM_HostSideBridgePortT;

/** Structure containing the data for an HSM operation    */
/** @details the paramBlockSize member is used to copy only as much of the paramBlock as is actually used   */
typedef struct HSM_HostSideOpParamsTag {
    HSM_FunctionT functionId;                   /**< The function to be performed by the operation           */
    ecy_hsm_Csai_JobPriorityT opPriority;       /**< The operation priority, may be inherited by the job     */
    uint32 paramBlockSize;                      /**< Size of parameter block, used to reduce copying time    */
    uint8 paramBlock[HSM_OP_PARAM_BLOCK_SIZE];  /**< Operation parameters, must be last element in structure */
} HSM_HostSideOpParamsT;

/** @brief Structure containing pointers to the shared memory areas used for host <-> HSM communications        */
typedef struct HSM_BridgeConfigurationTag {
    ecy_hsm_Csai_ErrorT errorCode;                          /**< Error code buffer for error returned from configuration      */
    uint32 HSM_ErrorMessageBufferSize;                      /**< Length in bytes of the error message area                    */
    uint8* pHSM_ErrorMessage;                               /**< Pointer to error message area                                */
    volatile HSM_HostSideBridgePortT* pHostSideBridgePorts; /**< Pointer to the host side job/port array                      */
    HSM_HostSideOpParamsT* pOpParams;                       /**< Pointer to the shared memory for the operation params        */
    uint8* pQmacBuffer;                                     /**< Pointer to buffer to receive generated Quick CMACs           */
    uint32* pResultFlag;                                    /**< Pointer to buffer for the MAC verification result            */
    volatile ecy_hsm_Host_TB_VerifTableT* pTBVerifTable;    /**< Pointer to the shared verif. table for trusted boot          */
#if defined(TIMING_DIAGNOSTICS) && (TIMING_DIAGNOSTICS != DISABLED)
    ecy_hsm_DiagnosticsT* diagnostics;                      /**< Array of values for diagnostics, such as  timing, and index  */
#endif
} HSM_BridgeConfigurationT;


/** Structure containing the parameters for an HSM suspend operation    */
typedef struct HSM_HostSideSuspendParamsTag {
    HSM_SuspendFunctionT functionId;        /**< The function to be performed by the operation              */
    ecy_hsm_Csai_ErrorT opErrorCode;        /**< Error code returned from the operation completion          */
    uint32 challengeVal;                    /**< challenge returned from the HSM                            */
    uint32 responseVal;                     /**< Response value to the preceding challenge                  */
} HSM_HostSideSuspendParamsT;

/** Structure containing the parameters for an HSM secure debug operation */
typedef struct HSM_SecureDebugConfigureParamsTag {
    uint8*  pDebugDataBuffer;              /**< Pointer to buffer to exchange basic debug data              */
    uint32  debugDataBufferSize;           /**< Length in bytes of debug data buffer                        */
    uint8*  pChallengeBuffer;              /**< Pointer to buffer to exchange the challenge data            */
    uint32  challengeBufferSize;           /**< Length in bytes of challenge data buffer                    */
    uint8*  pResponseBuffer;               /**< Pointer to buffer to exchange the response data             */
    uint32  responseBufferSize;            /**< Length in bytes of response data buffer                     */
} HSM_SecureDebugConfigureParamsT;

typedef struct HSM_HostSideSuspendSharedRamParamsTag {
    ecy_hsm_Csai_ErrorT opErrorCode;        /**< Error code returned from the suspend shared RAM operation completion          */
} HSM_HostSideSuspendSharedRamParamsT;

/* *** exported interfaces ********************************************************************/

/**
 * @}
 */

#endif /* Multiple inclusion lock  */
