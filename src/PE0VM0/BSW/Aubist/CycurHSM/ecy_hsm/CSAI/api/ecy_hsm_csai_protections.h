/**
 * @file
 ***********************************************************************************************
 * @brief CSAI protections operations
 * This header file is part of the Cryptographic Service Application Interface and specifies
 * types and functions for secure flash programming
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2014, all rights reserved.
 **********************************************************************************************/

#ifndef ECY_HSM_CSAI_PROTECTIONS
#define ECY_HSM_CSAI_PROTECTIONS

/* *** includes *******************************************************************************/

#include "ecy_hsm_csai.h"

/* *** defines ********************************************************************************/
#define ecy_hsm_CSAI_PROTECTION_PLANTIF_SERIALNUM_LEN            (16U)       /**< Length of serial number*/
#define ecy_hsm_CSAI_PROTECTION_PASSWORD_LIST_ENTRIES_MAX        (4U)        /**< Max number of password list entries */
#define ecy_hsm_CSAI_PROTECTION_PASSWORD_PASSWD_LEN_MAX          (32U)       /**< Size in bytes of a password */
#define ecy_hsm_CSAI_PROTECTION_PASSWORD_PFLASH_PASSWD_LEN_F1KM  (16U)       /**< Size in bytes of a password */

/* *********** Deprecated Macro definitions ***************/
/**
 * @deprecated by ecy_hsm_CSAI_PROTECTION_PLANTIF_SERIALNUM_LEN
 */
#define PROTECTION_PLANTIF_SERIALNUM_LEN ecy_hsm_CSAI_PROTECTION_PLANTIF_SERIALNUM_LEN
/**
 * @deprecated by ecy_hsm_CSAI_PROTECTION_PASSWORD_LIST_ENTRIES_MAX
 */
#define PROTECTION_PASSWORD_LIST_ENTRIES_MAX ecy_hsm_CSAI_PROTECTION_PASSWORD_LIST_ENTRIES_MAX
/**
 * @deprecated by ecy_hsm_CSAI_PROTECTION_PASSWORD_PASSWD_LEN_MAX
 */
#define PROTECTION_PASSWORD_PASSWD_LEN_MAX ecy_hsm_CSAI_PROTECTION_PASSWORD_PASSWD_LEN_MAX
/**
 * @deprecated by ecy_hsm_CSAI_PROTECTION_PASSWORD_PFLASH_PASSWD_LEN_F1KM
 */
#define PROTECTION_PASSWORD_PFLASH_PASSWD_LEN_F1KM ecy_hsm_CSAI_PROTECTION_PASSWORD_PFLASH_PASSWD_LEN_F1KM

/* *** type declarations **********************************************************************/

/** Define protection security levels */
typedef enum ecy_hsm_Csai_ProtSecLevelTag
{
    ecy_hsm_CSAI_PROT_SEC_Csai_Protection_FlashUnlock,   /**< Flag for disabling function Csai_Protection_FlashUnlock */
    ecy_hsm_CSAI_PROT_SEC_Mgmt_SuspendStart,             /**< Flag for disabling function Mgmt_SuspendStart */
    ecy_hsm_CSAI_PROT_SEC_Csai_TbRefTblPartInit,         /**< Flag for disabling function Csai_TbRefTblPartInit */
    ecy_hsm_CSAI_PROT_SEC_Csai_TbRefTblPartUpdate,       /**< Flag for disabling function Csai_TbRefTblPartUpdate */
    ecy_hsm_CSAI_PROT_SEC_Csai_TbRefTblPartFinish,       /**< Flag for disabling function Csai_TbRefTblPartFinish */
    ecy_hsm_CSAI_PROT_SEC_Csai_TbRefTblPartFinalize,     /**< Flag for disabling function Csai_TbRefTblPartFinalize */
    /* PRQA S 0785 1 */                                  /* Deviation: rule_5.5_0785_backwards_compatibility */
    ecy_hsm_CSAI_PROT_SEC_Csai_SecFlash,                 /**< Flag for disabling of functions
                                                              @ref ecy_hsm_Csai_SecFlash_Init and
                                                              @ref ecy_hsm_Csai_SecFlash_VerifySignedHeader. Both
                                                              functions are used for initialization of HSM
                                                              reprogramming process without that HSM update process
                                                              cannot be performed. */
    ecy_hsm_CSAI_PROT_SEC_Csai_TbRefTblPartSetSignature, /**< Flag for disabling function
                                                              Csai_TbRefTblPartSetSignWithKeystoreSlot and
                                                              Csai_TbRefTblPartSetSignWithCertAddress */
    ecy_hsm_CSAI_PROT_SEC_Csai_ReadHSMRegisters,         /**< Flag for disabling function
                                                              @ref ecy_hsm_Csai_System_ReadRegister */
    ecy_hsm_CSAI_PROT_SEC_Mgmt_SuspendKeep,              /**< Flag for disabling function Mgmt_SuspendKeep */
    ecy_hsm_CSAI_PROT_SEC_Csai_TbRefTblFullInit,         /**< Flag for disabling function Csai_TbRefTblFullInit */
    ecy_hsm_CSAI_PROT_SEC_Csai_TbRtmdSuspend,            /**< Flag for disabling function Csai_TbRtmdSuspend */
    ecy_hsm_CSAI_PROT_SEC_Csai_TbRtmdReactivate,         /**< Flag for disabling function Csai_TbRtmdReactivate */
    ecy_hsm_CSAI_PROT_SEC_Csai_HSMDeactivation,          /**< Flag for disabling function Csai_HSMDeactivation */
    ecy_hsm_CSAI_PROT_SEC_Csai_Protection_Bankswap,      /**< Flag for disabling unlocking bankswap protection with Csai_Protection_Unlock */
    ecy_hsm_CSAI_PROT_SEC_Csai_TrustedSwPartInit,        /**< Flag for disabling function Csai_TrustedSwPartInit */
    ecy_hsm_CSAI_PROT_SEC_Csai_TrustedSwPartUpdate,      /**< Flag for disabling function Csai_TrustedSwPartUpdate */
    ecy_hsm_CSAI_PROT_SEC_Csai_TrustedSwPartSetSignature,/**< Flag for disabling function Csai_TrustedSwPartSetSignature */
    ecy_hsm_CSAI_PROT_SEC_Csai_TrustedSwPartFinish,      /**< Flag for disabling function Csai_TrustedSwPartFinish */
    ecy_hsm_CSAI_PROT_SEC_Csai_TrustedSwPartFinalize,    /**< Flag for disabling function Csai_TrustedSwPartFinalize */
    ecy_hsm_CSAI_PROT_SEC_Csai_InstallRootCertificate,   /**< Flag for disabling function Csai_InstallRootCertificate */
    ecy_hsm_CSAI_PROT_SEC_Csai_Protection_Syscfg,        /**< Flag for disabling unlocking syscfg protection with Csai_Protection_Unlock */
    ecy_hsm_CSAI_PROT_SEC_Csai_SmartTbInit,              /**< Flag for disabling function Csai_SmartTbInit */
    ecy_hsm_CSAI_PROT_SEC_Csai_SmartTbUpdate,            /**< Flag for disabling function Csai_SmartTbUpdate */
    ecy_hsm_CSAI_PROT_SEC_Csai_SmartTbFinish,            /**< Flag for disabling function Csai_SmartTbFinish */
    ecy_hsm_CSAI_PROT_SEC_Csai_SmartTbFull,              /**< Flag for disabling function Csai_SmartTbFull */
    ecy_hsm_CSAI_PROT_SEC_Csai_VerifyRegister,           /**< Flag for disabling function Csai_VerifyRegister */
    ecy_hsm_CSAI_PROT_SEC_Csai_SuspendSharedRamWrite,    /**< Flag for disabling function SuspendSharedRamWrite */
    ecy_hsm_CSAI_PROT_SEC_Csai_VerifyHSMConfig,          /**< Flag for disabling function Csai_VerifyHSMConfig */
    /* This needs to be the final entry */
    ecy_hsm_CSAI_PROT_SEC_NUM,                          /**< Number of flags */
    ecy_hsm_CSAI_PROT_SEC_LEVEL_RESERVED = 0x7FFFFFFFUL /**< Value defined to use memory size of uint32 for enums */
} ecy_hsm_Csai_ProtSecLevelT;

/**
 * @deprecated
 * This define is for backwards compatibility, because of the renaming of ecy_hsm_CSAI_PROT_SEC_Csai_SecFlash_Init
 */
#define ecy_hsm_CSAI_PROT_SEC_Csai_SecFlash_Init            ecy_hsm_CSAI_PROT_SEC_Csai_SecFlash

/** Define password usage flags */
typedef enum ecy_hsm_Csai_ProtUsageFlagTag {
    ecy_hsm_CSAI_PROT_FLAG_UNUSED       = 0x0000UL,       /**< Flag for define the password is unused */
    ecy_hsm_CSAI_PROT_FLAG_PFLASH_READ  = 0x0001UL,       /**< Flag for define the usage of this password as PFLASH read protection
                                                             Currently not (fully) supported. See @ref ecy_hsm_Csai_Protection_SetPasswords */
    ecy_hsm_CSAI_PROT_FLAG_PFLASH_WRITE = 0x0002UL,       /**< Flag for define the usage of this password as PFLASH write protection */
    ecy_hsm_CSAI_PROT_FLAG_DFLASH_READ  = 0x0004UL,       /**< Flag for define the usage of this password as DFLASH read protection
                                                             Currently not (fully) supported. See @ref ecy_hsm_Csai_Protection_SetPasswords */
    ecy_hsm_CSAI_PROT_FLAG_DFLASH_WRITE = 0x0008UL,       /**< Flag for define the usage of this password as DFLASH write protection */
    ecy_hsm_CSAI_PROT_FLAG_DEBUGIF      = 0x0010UL,       /**< Flag for define the usage of this password as debugger protection */
    /* Set to ecy_hsm_CSAI_PROT_FLAG_PFLASH_WRITE to allow the old concept also for u2a */
    ecy_hsm_CSAI_PROT_FLAG_CUST_ID_A    = ecy_hsm_CSAI_PROT_FLAG_PFLASH_WRITE, /**< Flag for define the usage of this password as Customer ID A */
    ecy_hsm_CSAI_PROT_FLAG_CUST_ID_B    = 0x0040UL,       /**< Flag for define the usage of this password as Customer ID B */
    ecy_hsm_CSAI_PROT_FLAG_CUST_ID_C    = 0x0080UL,       /**< Flag for define the usage of this password as Customer ID C */
    ecy_hsm_CSAI_PROT_FLAG_TC3H_BMHD0   = 0x0100UL,       /**< Flag for define the usage of this password for Boot mode header */
    ecy_hsm_CSAI_PROT_FLAG_TC3H_SWAP    = 0x0200UL,       /**< Flag for define the usage of this password for PFLASH memory swap */
    ecy_hsm_CSAI_PROT_FLAG_HSM_DEACT    = 0x0400UL,       /**< Flag for define the usage of this password for HSM deactivation */
    ecy_hsm_CSAI_PROT_FLAG_SYSCFG       = ecy_hsm_CSAI_PROT_FLAG_TC3H_BMHD0, /**< Flag for define the usage of this password for a system configuration area */
    ecy_hsm_CSAI_PROT_FLAG_SWAP         = ecy_hsm_CSAI_PROT_FLAG_TC3H_SWAP,  /**< Flag for define the usage of this password for a bank swap configuration area */
    ecy_hsm_CSAI_PROT_FLAG_RESERVED     = 0x7FFFFFFFUL    /**< Value defined to use memory size of uint32 for enums */
} ecy_hsm_Csai_ProtUsageFlagT;

/** Define a compound type to hold a protection password  */
typedef struct ecy_hsm_Csai_ProtPasswordTag {
    uint32 pwdTypeFlags;                                            /**< Flags to define the usage of this password */
    uint8  pwd[ecy_hsm_CSAI_PROTECTION_PASSWORD_PASSWD_LEN_MAX];    /**< password */
    uint8  pwdLength;                                               /**< password length in Byte */
} ecy_hsm_Csai_ProtPasswordT;

/** Defined protection use cases */
typedef enum ecy_hsm_Csai_ProtUseCaseIdTag
{
    ecy_hsm_CSAI_PROT_ID_PFLASH_MASK_V1 = 0UL,         /**< Flag for using bitmask for unlocking specified PFlash banks. Expects an additional parameter of
                                                         type ecy_hsm_Csai_ProtFlashBankT for bank selection. */
    ecy_hsm_CSAI_PROT_ID_DFLASH_MASK_V1 = 10UL,        /**< Flag for calling dflash protection unlocking */
    ecy_hsm_CSAI_PROT_ID_BANKSWAP_V1    = 50UL,        /**< Flag for calling bankswap protection unlocking */
    ecy_hsm_CSAI_PROT_ID_SYSCFG_V1      = 70UL,        /**< Flag for calling system configuration unlocking */
    ecy_hsm_CSAI_PROT_ID_RESERVED       = 0x7FFFFFFFUL /**< Value defined to use memory size of uint32 for enums */
} ecy_hsm_Csai_ProtUseCaseIdT;

/** Define resumption IDs */
typedef enum ecy_hsm_Csai_ProtResumeIdTag
{
    ecy_hsm_CSAI_PROT_RESUME_ALL_PROT = 0UL,         /**< Flag for restoring all protections as they were configured */
    ecy_hsm_CSAI_PROT_RESUME_RESERVED = 0x7FFFFFFFUL /**< Value defined to use memory size of uint32 for enums */
} ecy_hsm_Csai_ProtResumeProtIdT;

/** Define PFlash banks for (un-)lock operation */
typedef enum ecy_hsm_Csai_ProtFlashBankTag
{
    ecy_hsm_CSAI_PROT_PFLASH_BANK_UNUSED = 0x0000UL,    /**< Flag for unlocking PFlash banks unused */
    ecy_hsm_CSAI_PROT_PFLASH_BANK_0      = 0x0001UL,    /**< Flag used for unlocking PFlash bank 0 */
    ecy_hsm_CSAI_PROT_PFLASH_BANK_1      = 0x0002UL,    /**< Flag used for unlocking PFlash bank 1 */
    ecy_hsm_CSAI_PROT_PFLASH_BANK_2      = 0x0004UL,    /**< Flag used for unlocking PFlash bank 2 */
    ecy_hsm_CSAI_PROT_PFLASH_BANK_3      = 0x0008UL,    /**< Flag used for unlocking PFlash bank 3 */
    ecy_hsm_CSAI_PROT_PFLASH_BANK_4      = 0x0010UL,    /**< Flag used for unlocking PFlash bank 4 */
    ecy_hsm_CSAI_PROT_PFLASH_BANK_5      = 0x0020UL,    /**< Flag used for unlocking PFlash bank 5 */
    ecy_hsm_CSAI_PROT_PFLASH_BANK_ALL    = 0xFFFFUL,    /**< Flag used for unlocking all PFlash banks */
    ecy_hsm_CSAI_PROT_PFLASH_RESERVED    = 0x7FFFFFFFUL /**< Value defined to use memory size of uint32 for enums */
} ecy_hsm_Csai_ProtFlashBankT;

/** Define DFlash banks for (un-)lock operation */
typedef enum ecy_hsm_Csai_ProtDataFlashBankTag
{
    ecy_hsm_CSAI_PROT_DFLASH_BANK_UNUSED = 0x0000UL,    /**< Flag for unlocking DFlash banks unused */
    ecy_hsm_CSAI_PROT_DFLASH_BANK_0      = 0x0001UL,    /**< Flag used for unlocking DFlash bank 0 */
    ecy_hsm_CSAI_PROT_DFLASH_BANK_1      = 0x0002UL,    /**< Flag used for unlocking DFlash bank 1 */
    ecy_hsm_CSAI_PROT_DFLASH_BANK_2      = 0x0004UL,    /**< Flag used for unlocking DFlash bank 2 */
    ecy_hsm_CSAI_PROT_DFLASH_BANK_ALL    = 0xFFFFUL,    /**< Flag used for unlocking all DFlash banks */
    ecy_hsm_CSAI_PROT_DFLASH_RESERVED    = 0x7FFFFFFFUL /**< Value defined to use memory size of uint32 for enums */
} ecy_hsm_Csai_ProtDataFlashBankT;


/* *INDENT-OFF* */
#ifdef __cplusplus
extern "C" {
#endif
/* *INDENT-ON* */

/**
 * @addtogroup GROUP_CSAI_SECFLASH
 * @{
 * Secure flash programming API
 *
 */

/**
 * @addtogroup GROUP_CSAI_PROTECTIONS
 * @{
 * functions for handling the hardware protections
 */

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/**
 * [$DD 2555]
 * @brief Unlocks the given memory region, if supported.
 * [$Satisfies $SW_ARCH 3ADC0BE9] [$Satisfies $SW_ARCH A1D45DD8]
 *
 * This function temporarily unlocks the read/write protections for the specified memory region.
 *
 * @param[in]   hSession            Handle to the session in which the job will be placed.
 * @param[in]   priority            Requested scheduling priority for this job on the HSM.
 * @param[in]   memRangeAddStart    Physical start address of SW memory range to be unlocked
 * @param[in]   memRangeNumBytes    Length of memory range to be unlocked (in bytes).
 * @param[out]  phJob               Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 *   - @ref ecy_hsm_CSAI_ERR_NOT_IMPLEMENTED            The CSAI Protection interface is not implemented in this HSM
 *                                                      build.
 *
 * @note
 * On Renesas target, the host needs to disable the lock bit (FPROTCRn) as part of the flash program sequence,
 * after calling ecy_hsm_Csai_Protection_FlashUnlock.
 *
 * @note
 * Aurix targets allow enabling of sector wise PFlash write protection.
 * However, PFlash write protection can only be unlocked "globally",
 * meaning all write protected PFlash sectors will be unlocked,
 * even if only one sector was selected / addressed for unlocking.
 * Example: Unlock PF0 S0 (memRangeAddStart = 0x80000000 and memRangeNumBytes = 0x4000) will unlock all PFlash sectors with write protection enabled.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED          There was another job already in progress in the session
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                The given function is not supported by this HSM build
 * - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT            An address or pointer parameter was not four-byte aligned
 * - @ref ecy_hsm_CSAI_ERR_PRIVILEGE_MISSING            session/user privilege(s) missing for privileged operation
 *                                                      (not supported yet, reserved for future use)
 * - @ref ecy_hsm_CSAI_ERR_INVALID_CREDENTIALS          Invalid or incorrect protection credentials
 * - @ref ecy_hsm_CSAI_ERR_EEPROM_TAG_NOT_FOUND         Protection credentials missing in non-volatile storage
 * - @ref ecy_hsm_CSAI_ERR_SECFUNC_LOCKED               Security critical functions are currently disabled
 *                                                      (see @ref ecy_hsm_Csai_Protection_DisableSecCritFunctions)
 * - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION            Provided address range overlaps with HSM memory region
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_Protection_FlashUnlock(ecy_hsm_Csai_SessionHandleT hSession,
                                                      ecy_hsm_Csai_JobPriorityT   priority,
                                                      uint32                      memRangeAddStart,
                                                      uint32                      memRangeNumBytes,
                                                      ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 2556]
 * @brief Resume protections of host PFlash and DFlash
 * [$Satisfies $SW_ARCH FC5890A8] [$Satisfies $SW_ARCH A2A8F6FD]
 *
 * This function resumes (i.e. locks) the read/write protections for all configured memory regions.
 * In some lifecycle states the protections may be disabled at HSM startup. This function may be used to
 * explicitly lock the host PFlash (mostly for manufacturing test purposes).
 *
 * Use of this function during the host flash programming sequence is not mandatory if the sequence is terminated by
 * an ECU reset, since the protections are expected to be activated automatically by the HSM at startup.
 *
 * @param[in]   hSession            Handle to the session in which the job will be placed.
 * @param[in]   priority            Requested scheduling priority for this job on the HSM.
 * @param[out]  phJob               Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 *   - @ref ecy_hsm_CSAI_ERR_NOT_IMPLEMENTED            The CSAI Protection interface is not implemented in this HSM
 *                                                      build.
 *
 * @note
 * On Renesas target, the host needs to enable the lock bit (FPROTCRn) as part of the flash program sequence,
 * before calling ecy_hsm_Csai_Protection_FlashResume.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED          There was another job already in progress in the session
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                The given function is not supported by this HSM build
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_Protection_FlashResume(ecy_hsm_Csai_SessionHandleT hSession,
                                                      ecy_hsm_Csai_JobPriorityT   priority,
                                                      ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 252]
 * @brief Store protection passwords
 * [$Satisfies $SW_ARCH 12AAC305]
 *
 * Stores the protection passwords in HSM memory only. The passwords are not written to the
 * hardware to activate the protections.
 *
 * This interface can be used only after HSM has been activated, as long as the HSM is in
 * lifecycle state 'PRODUCTION'. The function will return an error in lifecycle states
 * other than PRODUCTION.
 *
 * The passwords can be written only once. A second write attempt will fail and return an
 * error. Thus all passwords have to be written in one call.
 *
 * Because of the usage of one password for several purposes (e.g. Read-/Write-Protection
 * are usually the same for one dedicated area), the total amount of handled password inside
 * the HSM is limited to four.
 *
 * Password based flash read protection is currently not supported. The corresponding flags
 * @ref ecy_hsm_CSAI_PROT_FLAG_PFLASH_READ and @ref ecy_hsm_CSAI_PROT_FLAG_DFLASH_READ behave as follows:
 * - A password which is either flagged with @ref ecy_hsm_CSAI_PROT_FLAG_PFLASH_READ or
 *   @ref ecy_hsm_CSAI_PROT_FLAG_PFLASH_WRITE or both, can be used to successfully unlock
 *   PFLASH write protection using @ref ecy_hsm_Csai_Protection_FlashUnlock or @ref ecy_hsm_Csai_Protection_Unlock.
 *
 * - A password which is either flagged with @ref ecy_hsm_CSAI_PROT_FLAG_DFLASH_READ or
 *   @ref ecy_hsm_CSAI_PROT_FLAG_DFLASH_WRITE or both, can be used to successfully unlock
 *   DFLASH write protection using @ref ecy_hsm_Csai_Protection_FlashUnlock or @ref ecy_hsm_Csai_Protection_Unlock.
 *
 * @param[in]   hSession            Handle to the session in which the job will be placed.
 * @param[in]   priority            Requested scheduling priority for this job on the HSM.
 * @param[in]   numListEntries      Num of entries in password list
 * @param[in]   pList               pointer to Password list
 * @param[out]  phJob               Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 *   - @ref ecy_hsm_CSAI_ERR_NOT_IMPLEMENTED            The CSAI Protection interface is not implemented in this HSM
 *                                                      build.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                    A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED                   The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                    The given function is not supported by this HSM build
 * - @ref ecy_hsm_CSAI_ERR_PROT_PASSWORD_ENTRIES_WRONG      Number of password entries wrong
 * - @ref ecy_hsm_CSAI_ERR_PROT_PASSWORD_SIZE_WRONG         Size of at least one password is incorrect
 * - @ref ecy_hsm_CSAI_ERR_PROT_PASSWORD_FLAG_WRONG         At least one password flag is incorrect
 * - @ref ecy_hsm_CSAI_ERR_LIFECYCLE_WRONG                  The Ecu is in wrong lifecycle
 * - @ref ecy_hsm_CSAI_ERR_DATA_ALREADY_STORED              The passwords are programmed already
 * - @ref ecy_hsm_CSAI_ERR_EEPROM_EMULATION                 Internal EEPROM error occurred
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_Protection_SetPasswords(ecy_hsm_Csai_SessionHandleT hSession,
                                                       ecy_hsm_Csai_JobPriorityT   priority,
                                                       uint8                       numListEntries,
                                                       ecy_hsm_Csai_ProtPasswordT* pList,
                                                       ecy_hsm_Csai_JobHandleT*    phJob);

/** @} */ // GROUP_CSAI_PROTECTIONS

/**
 * @addtogroup GROUP_CSAI_SECCRIT_FUNCS
 * @{
 */

/**
 * [$DD 953]
 * @brief Disable the security critical functions
 * [$Satisfies $ARCH 141]
 *
 * This function is used to protect HSM highly critical security functions from misuse. Specifically, this function
 * makes it impossible for any software running on the host to:
 * - suspend the HSM Core application
 * - update the host software
 * - update the HSM firmware
 *
 * The function sets an HSM-internal security flag that is checked by the following functions:
 * @ref ecy_hsm_Csai_Protection_FlashUnlock, @ref ecy_hsm_Mgmt_SuspendStart, @ref ecy_hsm_Csai_TbRefTblPartInit,
 * @ref ecy_hsm_Csai_TbRefTblPartUpdate, @ref ecy_hsm_Csai_TbRefTblPartFinish, @ref ecy_hsm_Csai_TbRefTblFinalize,
 * @ref ecy_hsm_Csai_SecFlash_Init, @ref ecy_hsm_Csai_InstallRootCertificate, @ref ecy_hsm_Csai_Sss_RunScript for HSM
 * deactivation use case
 *
 * In case the security flag is set, the above listed functions immediately return an error.
 *
 * After ecy_hsm_Csai_Protection_DisableSecCritFunctions has been called, the security-critical functions are disabled
 * until the next reset. There is no possibility to re-enable the security-critical functions on host request.
 *
 * @param[in]   hSession            Handle to the session in which the job will be placed. @deprecated This might
 *                                  be deleted in a future major release
 * @param[in]   priority            Requested scheduling priority for this job on the HSM.
 * @param[in]   secLevel            For future use. Disables the security critical functions regarding their security
 *                                  level. Currently all functions are disabled.
 * @param[out]  phJob               Receives the job handle of the initialized job. @deprecated This might be deleted
 *                                  in a future major release
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 *   - @ref ecy_hsm_CSAI_ERR_NOT_IMPLEMENTED            The CSAI Protection interface is not implemented in this HSM
 *                                                      build.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED          There was another job already in progress in the session
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_Protection_DisableSecCritFunctions(ecy_hsm_Csai_SessionHandleT hSession,
                                                                  ecy_hsm_Csai_JobPriorityT   priority,
                                                                  ecy_hsm_Csai_ProtSecLevelT  secLevel,
                                                                  ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 2546]
 * @brief Generic function for temporarily disabling specific protection regions
 * [$Satisfies $SW_ARCH 4AC1429E]
 *
 * This function implements a generic protection unlock feature. By now, IFX and RH850 (U2A and P1x) targets are supported.
 * The following options are available by choosing the appropriate useCaseId:
 *
 * - The use case ID @ref ecy_hsm_CSAI_PROT_ID_PFLASH_MASK_V1 allows to unlock predefined PFlash banks. The parameter pUseCaseIdParam
 * then inputs a specific bank mask to define the banks that shall be unlocked. In case of an error during execution, the same parameter outputs
 * a mask showing all PFlash banks, where unlocking has failed.
 * As TC2x devices only support global PFlash unlocking, all PFlash banks have to be selected in pUseCaseIdParam.
 *
 * - If bankswap is available, the UCB_SWAP protection for IFX and OPBT protection for RH850 U2A can be disabled by using @ref ecy_hsm_CSAI_PROT_ID_BANKSWAP_V1 as use case ID.
 * No further parameters are needed, i.e., pUseCaseIdParam can be set to NULL_PTR.
 *
 * @param[in]     hSession            Handle to the session in which the job will be placed.
 * @param[in]     priority            Requested scheduling priority for this job on the HSM.
 * @param[in]     useCaseId           Specifies the type of protection that shall be unlocked. All available use case IDs are defined in
 *                                    ecy_hsm_Csai_ProtUseCaseIdT.
 * @param[in,out] pUseCaseIdParam     Pointer to parameters that are needed for unlocking purposes. In case of unlocking PFlash banks,
 *                                    this should be a pointer to a ecy_hsm_Csai_ProtFlashBankT parameter and for DFlash this should be
 *                                    pointer to ecy_hsm_Csai_ProtDataFlashBankT. Depending on the use case ID, this
 *                                    parameter is also used to output result data.
 * @param[out]    phJob               Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 *   - @ref ecy_hsm_CSAI_ERR_NOT_IMPLEMENTED            The CSAI Protection interface is not implemented in this HSM
 *                                                      build.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED          There was another job already in progress in the session
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                The given function is not supported by this HSM build
 * - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT            An address or pointer parameter was not four-byte aligned
 * - @ref ecy_hsm_CSAI_ERR_PRIVILEGE_MISSING            session/user privilege(s) missing for privileged operation
 *                                                      (not supported yet, reserved for future use)
 * - @ref ecy_hsm_CSAI_ERR_INVALID_CREDENTIALS          Invalid or incorrect protection credentials
 * - @ref ecy_hsm_CSAI_ERR_EEPROM_TAG_NOT_FOUND         Protection credentials missing in non-volatile storage
 * - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION            Provided address range overlaps with HSM memory region
 * - @ref ecy_hsm_CSAI_ERR_SECFUNC_LOCKED               Security critical functions are currently disabled
 *                                                      (see @ref ecy_hsm_Csai_Protection_DisableSecCritFunctions)
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_Protection_Unlock(ecy_hsm_Csai_SessionHandleT hSession,
                                                 ecy_hsm_Csai_JobPriorityT   priority,
                                                 ecy_hsm_Csai_ProtUseCaseIdT useCaseId,
                                                 void*                       pUseCaseIdParam,
                                                 ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 2547]
 * @brief Generic function for resetting the protections to the initially configured state.
 * [$Satisfies $SW_ARCH C1DCFDAC]
 *
 * This function resets protection settings to their original read/write access configuration. The following
 * option is available:
 *
 * - By choosing ecy_hsm_CSAI_PROT_RESUME_ALL_PROT as value for resumeProtId, all protection settings are restored.
 * Previous calls to @ref ecy_hsm_Csai_Protection_Unlock or @ref ecy_hsm_Csai_Protection_FlashUnlock are reverted.
 *
 * @param[in]   hSession            Handle to the session in which the job will be placed.
 * @param[in]   priority            Requested scheduling priority for this job on the HSM.
 * @param[in]   resumeProtId        Type of resumption that shall be executed.
 * @param[in]   pResumeProtIdParam  Pointer to parameters that are needed for specified type of resumption.
 * @param[out]  phJob               Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 *   - @ref ecy_hsm_CSAI_ERR_NOT_IMPLEMENTED            The CSAI Protection interface is not implemented in this HSM
 *                                                      build.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED          There was another job already in progress in the session
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                The given function is not supported by this HSM build
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_Protection_Resume(ecy_hsm_Csai_SessionHandleT    hSession,
                                                 ecy_hsm_Csai_JobPriorityT      priority,
                                                 ecy_hsm_Csai_ProtResumeProtIdT resumeProtId,
                                                 void*                          pResumeProtIdParam,
                                                 ecy_hsm_Csai_JobHandleT*       phJob);

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* *INDENT-OFF* */
#ifdef __cplusplus
    } /* extern "C" */
#endif
/* *INDENT-ON* */

/** @} */ // GROUP_CSAI_SECCRIT_FUNCS
/** @} */ // GROUP_CSAI_SECFLASH
#endif /* ECY_HSM_CSAI_PROTECTIONS */


