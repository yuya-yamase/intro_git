/**
 * @file
 ***********************************************************************************************
 * @brief CSAI Error Management.
 * This header file is part of the Cryptographic Service Application Interface and specifies
 * error and flow control return codes of all interface functions.
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2014, all rights reserved
 **********************************************************************************************/

/* *** prologue ******************************************************************************/

#ifndef ECY_HSM_CSAI_ERROR_H
#define ECY_HSM_CSAI_ERROR_H

/**
 * @addtogroup GROUP_CSAI_ERROR_MANAGEMENT
 * @{
 */

/* *** includes *******************************************************************************/

#include "ecy_hsm_csai_types.h"

/* *** defines ********************************************************************************/

/** Flag in result code, which classifies a result as an error */
#define ecy_hsm_CSAI_ERR_FLAG_ERROR          (0x80000000U)

/** Flag in result code, which classifies an expected flow control result */
#define ecy_hsm_CSAI_ERR_FLAG_FLOW_CONTROL   (0x40000000U)

/** Flag in result code, which indicates this error relates to the previously scheduled operation */
#define ecy_hsm_CSAI_ERR_FLAG_PREVIOUS_OP    (0x20000000U)

/** @deprecated Flag in result code which indicates the error was indicated by applet/applet manager.
 *              Is no longer in use, but can not be fully removed, since it would be a breaking change. */
#define ecy_hsm_CSAI_ERR_FLAG_APPLET         (0x10000000U)

/** HSM operation flag which indicates HSM shall switch to RamOs */
#define ecy_hsm_CSAI_OP_FLAG_NEEDS_RAMOS     (0x00800000U)

/** mask for HSM internal operation request flags */
#define ecy_hsm_CSAI_OP_FLAG_MASK            (0x00F00000U)

/** Mask for error class */
#define ecy_hsm_CSAI_ERR_CLASS_MASK          (0x0000F000U)

/** Mask for error code */
#define ecy_hsm_CSAI_ERR_CODE_MASK           (0x00000FFFU)

/** Generic test whether an error result indicates a failure on any result code of an API call */
#define ecy_hsm_CSAI_FAILED(err)             (ecy_hsm_CSAI_ERR_FLAG_ERROR == ((err)&ecy_hsm_CSAI_ERR_FLAG_ERROR))

/** Generic test whether an error result indicates success on any result code of an API call. */
#define ecy_hsm_CSAI_SUCCEEDED(err)          (0U == ((err)&ecy_hsm_CSAI_ERR_FLAG_ERROR))

/** Generic test whether an error result indicates a security policy violation on any result code of an API call. */
#define ecy_hsm_CSAI_VIOLATION(err)          ((ecy_hsm_CSAI_ERR_CLASS_VIOLATION == ((err)&ecy_hsm_CSAI_ERR_CLASS_MASK)))

/** Generic test whether an error result indicates a SHE error. */
#define ecy_hsm_CSAI_SHE_ERROR(err)          ((ecy_hsm_CSAI_ERR_CLASS_SHE == ((err)&ecy_hsm_CSAI_ERR_CLASS_MASK)))

/** Generic test whether an error result indicates a non-SHE error. */
#define ecy_hsm_CSAI_NOT_SHE_ERROR(err)      ((ecy_hsm_CSAI_ERR_CLASS_SHE != ((err)&ecy_hsm_CSAI_ERR_CLASS_MASK)))

/** Generic test whether an error result indicates success on any result code of an API call. */
#define ecy_hsm_CSAI_FLOW_CONTROL(err)       ((ecy_hsm_CSAI_ERR_FLAG_FLOW_CONTROL == ((err)&ecy_hsm_CSAI_ERR_FLAG_FLOW_CONTROL)))

/** Class of error result codes that indicate parameter validation failed. */
#define ecy_hsm_CSAI_ERR_CLASS_PARAM         (0x00001000UL)

/** Class of error result codes that indicate semantic or precondition validation failed. */
#define ecy_hsm_CSAI_ERR_CLASS_SEMANTIC      (0x00002000UL)

/** Class of error result codes that indicate that the HSM has run out a resources. */
#define ecy_hsm_CSAI_ERR_CLASS_RESOURCE      (0x00003000UL)

/** Class of error result codes that indicate an error in the communication to the HSM. */
#define ecy_hsm_CSAI_ERR_CLASS_COMMUNICATION (0x00004000UL)

/** Class of error result codes that indicate an internal assertion error. */
#define ecy_hsm_CSAI_ERR_CLASS_INTERNAL      (0x00005000UL)

/** Class of error result codes that indicate violations of the HSM's security policy */
#define ecy_hsm_CSAI_ERR_CLASS_VIOLATION     (0x00006000UL)

/** Class of error result codes from the SHE emulation */
#define ecy_hsm_CSAI_ERR_CLASS_SHE           (0x00007000UL)

/** Class of error result codes from parsers */
#define ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE    (0x00008000UL)

/** CLass of error result codes */
/*#define ecy_hsm_CSAI_ERR_CLASS_UNUSED      (0x00009000UL)*/

/** CLass of error result codes from CycurLib */
#define ecy_hsm_CSAI_ERR_CLASS_CYCURLIB      (0x0000A000UL)

/** Class of error result codes from Secure Space Scripting */
#define ecy_hsm_CSAI_ERR_CLASS_SSS           (0x0000B000UL)

/** Class of error result codes for customers (SolDev and GM) specific error codes. All error definitions of this class will be defined outside of
 * this header
 */
#define ecy_hsm_CSAI_ERR_CLASS_CUST          (0x0000E000UL)

/** Class of error result codes for errors not included in the above */
#define ecy_hsm_CSAI_ERR_CLASS_OTHER         (0x0000F000UL)

/** mask CycurLib error into CSAI error */
#define ecy_hsm_CSAI_LIB_ERROR(_errLib)                                                                                                              \
    (0U != ((uint32)(_errLib))) ? (((uint32)(_errLib)) | ecy_hsm_CSAI_ERR_CLASS_CYCURLIB | ecy_hsm_CSAI_ERR_FLAG_ERROR) : ecy_hsm_CSAI_SUCCESS

/** Separate the result code class information */
#define ecy_hsm_CSAI_RESULT_TYPE(err) ((code)&ecy_hsm_CSAI_ERR_CLASS_MASK)

/** SHE error code to be embedded in the CSAI codes, should match the values in she_common.h, but redefined here to avoid the include. All shifted 16
 * bits left. */
typedef enum ecy_hsm_Csai_SHE_CompatErrorTag
{
    ecy_hsm_CSAI_SHE_COMPAT_ERC_NO_ERROR               = 0U,
    ecy_hsm_CSAI_SHE_COMPAT_ERC_BUSY                   = 1U,
    ecy_hsm_CSAI_SHE_COMPAT_ERC_GENERAL_ERROR          = 2U,
    ecy_hsm_CSAI_SHE_COMPAT_ERC_KEY_EMPTY              = 3U,
    ecy_hsm_CSAI_SHE_COMPAT_ERC_KEY_INVALID            = 4U,
    ecy_hsm_CSAI_SHE_COMPAT_ERC_KEY_NOT_AVAILABLE      = 5U,
    ecy_hsm_CSAI_SHE_COMPAT_ERC_KEY_UPDATE_ERROR       = 6U,
    ecy_hsm_CSAI_SHE_COMPAT_ERC_KEY_WRITE_PROTECTED    = 7U,
    ecy_hsm_CSAI_SHE_COMPAT_ERC_MEMORY_FAILURE         = 8U,
    ecy_hsm_CSAI_SHE_COMPAT_ERC_NO_DEBUGGING           = 9U,
    ecy_hsm_CSAI_SHE_COMPAT_ERC_NO_SECURE_BOOT         = 10U,
    ecy_hsm_CSAI_SHE_COMPAT_ERC_RNG_SEED               = 11U,
    ecy_hsm_CSAI_SHE_COMPAT_ERC_SEQUENCE_ERROR         = 12U,
    ecy_hsm_CSAI_SHE_COMPAT_ERC_SHE_ERRORCODE_RESERVED = 0x7FFFFFFFU /**< Ensure full 32 bits are used for the enum */
} ecy_hsm_Csai_SHE_CompatErrorT;

/*
 * The SHE error code should be kept within the lower 16 bits, so the code can be created with an add16i (PPC) instruction. Moving it into the top 16
 * bits increases the size of the PPC_HT bootloader by about 260 bytes.
 */

/**
 * Shift the SHE errors to optimize for processing in specific hardware architecture.
 * @{
 */
// clang-format off
#define ecy_hsm_CSAI_SHE_POSITION                          (8U)
#define ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_NO_ERROR            ((uint32)ecy_hsm_CSAI_SHE_COMPAT_ERC_NO_ERROR            << ecy_hsm_CSAI_SHE_POSITION)
#define ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_BUSY                ((uint32)ecy_hsm_CSAI_SHE_COMPAT_ERC_BUSY                << ecy_hsm_CSAI_SHE_POSITION)
#define ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR       ((uint32)ecy_hsm_CSAI_SHE_COMPAT_ERC_GENERAL_ERROR       << ecy_hsm_CSAI_SHE_POSITION)
#define ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_KEY_EMPTY           ((uint32)ecy_hsm_CSAI_SHE_COMPAT_ERC_KEY_EMPTY           << ecy_hsm_CSAI_SHE_POSITION)
#define ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_KEY_INVALID         ((uint32)ecy_hsm_CSAI_SHE_COMPAT_ERC_KEY_INVALID         << ecy_hsm_CSAI_SHE_POSITION)
#define ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_KEY_NOT_AVAILABLE   ((uint32)ecy_hsm_CSAI_SHE_COMPAT_ERC_KEY_NOT_AVAILABLE   << ecy_hsm_CSAI_SHE_POSITION)
#define ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_KEY_UPDATE_ERROR    ((uint32)ecy_hsm_CSAI_SHE_COMPAT_ERC_KEY_UPDATE_ERROR    << ecy_hsm_CSAI_SHE_POSITION)
#define ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_KEY_WRITE_PROTECTED ((uint32)ecy_hsm_CSAI_SHE_COMPAT_ERC_KEY_WRITE_PROTECTED << ecy_hsm_CSAI_SHE_POSITION)
#define ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_MEMORY_FAILURE      ((uint32)ecy_hsm_CSAI_SHE_COMPAT_ERC_MEMORY_FAILURE      << ecy_hsm_CSAI_SHE_POSITION)
#define ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_NO_DEBUGGING        ((uint32)ecy_hsm_CSAI_SHE_COMPAT_ERC_NO_DEBUGGING        << ecy_hsm_CSAI_SHE_POSITION)
#define ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_NO_SECURE_BOOT      ((uint32)ecy_hsm_CSAI_SHE_COMPAT_ERC_NO_SECURE_BOOT      << ecy_hsm_CSAI_SHE_POSITION)
#define ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_RNG_SEED            ((uint32)ecy_hsm_CSAI_SHE_COMPAT_ERC_RNG_SEED            << ecy_hsm_CSAI_SHE_POSITION)
#define ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_SEQUENCE_ERROR      ((uint32)ecy_hsm_CSAI_SHE_COMPAT_ERC_SEQUENCE_ERROR      << ecy_hsm_CSAI_SHE_POSITION)
// clang-format on

/**
 * @}
 */
#define ecy_hsm_CSAI_EXTRACT_SHE_ERROR_CODE(x)                                                                                                       \
    ((SHE_ErrorCodeT)(((x) >> ecy_hsm_CSAI_SHE_POSITION) & 0x0000000FUL)) /**< Shift back from hw optimized to SHE error */

/**
 * @anchor ANCHOR_CSAI_ERROR_RESULT_CODES
 * @name   CSAI Error Result Codes
 * @brief  Predefined values of @ref ecy_hsm_Csai_ErrorT to specify a result code.
 * @{
 */

/** Special value to indicate that the call succeeded without error */
#define ecy_hsm_CSAI_SUCCESS (0U)

/**
 * @anchor ANCHOR_CSAI_ERROR_CLASS_PARAM
 * @name   Members of the CSAI error class @ref CSAI_ERROR_CLASS_PARAM
 * @brief  These error codes indicate an error in some parameter of a call.
 * @{
 */

/** The parameter is not a valid handle or the used handle has the wrong type. */
#define ecy_hsm_CSAI_ERR_INVALID_HANDLE                                                                                                              \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_PARAM | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x01U)

/** At least one given parameter of the call is wrong, invalid or out of range. */
#define ecy_hsm_CSAI_ERR_INVALID_PARAM                                                                                                               \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_PARAM | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x02U)

/** At least one given parameter of the call is wrong, invalid or out of range. */
#define ecy_hsm_CSAI_ERR_INCONSISTENT_PARAM_SET                                                                                                      \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_PARAM | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x03U)

/** The parameter structure is too big to fit in the paramBlock member of the HSM_HostSideOpParamsT structure */
#define ecy_hsm_CSAI_ERR_PARAM_BLOCK_TOO_LARGE                                                                                                       \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_PARAM | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x04U)

/** The given input data block was too large to be handled by the HSM. */
#define ecy_hsm_CSAI_ERR_INPUT_TOO_LARGE                                                                                                             \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_PARAM | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x05U)

/** The output data was too large to fit into the given buffer and was truncated. */
#define ecy_hsm_CSAI_ERR_OUTPUT_TRUNCATED                                                                                                            \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_PARAM | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x06U)

/** The provided login credentials are invalid */
#define ecy_hsm_CSAI_ERR_INVALID_CREDENTIALS                                                                                                         \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_PARAM | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x07U)

/** The required job function or algorithm is not supported */
#define ecy_hsm_CSAI_ERR_NOT_SUPPORTED                                                                                                               \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_PARAM | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x08U)

/** The required job function or algorithm is not implemented (yet?) */
#define ecy_hsm_CSAI_ERR_NOT_IMPLEMENTED                                                                                                             \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_PARAM | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x09U)

/** The specified HSM port is out of range */
#define ecy_hsm_CSAI_ERR_PORT_OUT_OF_RANGE                                                                                                           \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_PARAM | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x0AU)

/** The HSM has suffered a memory protection exception (can be caused by an illegal access to the host-side) */
#define ecy_hsm_CSAI_ERR_MEM_PROTECTION                                                                                                              \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_PARAM | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_MEMORY_FAILURE | 0x0BU)

/** The output data was too large to fit into the given buffer, nothing was written */
#define ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL                                                                                                            \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_PARAM | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x0CU)

/** The specified EEPROM tag value was not found by an EEPROM read attempt This usually means that a specified key slot (keyId) is not populated */
#define ecy_hsm_CSAI_ERR_EEPROM_TAG_NOT_FOUND                                                                                                        \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_PARAM | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_KEY_EMPTY | 0x0DU)

/** An address or pointer parameter was not four-byte aligned, but it needed to be */
#define ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT                                                                                                           \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_PARAM | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x0EU)

/** The required job function or algorithm is not supported by the bootloader, it may be supported by the core application */
#define ecy_hsm_CSAI_ERR_BOOTLOADER_NOT_SUPPORTED                                                                                                    \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_PARAM | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x0FU)

/** The counter not being greater than the current counter */
#define ecy_hsm_CSAI_ERR_INVALID_KEY_COUNTER                                                                                                         \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_PARAM | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_KEY_UPDATE_ERROR | 0x10U)

/** The supplied UID being incorrect */
#define ecy_hsm_CSAI_ERR_INVALID_UID                                                                                                                 \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_PARAM | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_KEY_UPDATE_ERROR | 0x11U)

/** The authorizing key being empty */
#define ecy_hsm_CSAI_ERR_EMPTY_AUTH_KEY                                                                                                              \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_PARAM | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_KEY_UPDATE_ERROR | 0x12U)

/** M3 not matching the expected value */
#define ecy_hsm_CSAI_ERR_INVALID_M3                                                                                                                  \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_PARAM | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_KEY_UPDATE_ERROR | 0x13U)

/** The supplied certificate is of the wrong type for the operation/job */
#define ecy_hsm_CSAI_ERR_WRONG_CERT_ATTRIBS (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_PARAM | 0x14U)

/** The supplied response total data has the wrong length */
#define ecy_hsm_CSAI_ERR_SECUACC_RESPONSE_TOTALDATA_SIZE_WRONG                                                                                       \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_PARAM | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_KEY_UPDATE_ERROR | 0x15U)

/** The supplied response data chunk has the wrong length */
#define ecy_hsm_CSAI_ERR_SECUACC_RESPONSE_CHUNK_SIZE_WRONG                                                                                           \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_PARAM | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_KEY_UPDATE_ERROR | 0x16U)

/** The supplied response is incomplete */
#define ecy_hsm_CSAI_ERR_SECUACC_RESPONSE_NOT_ENOUGH_VERIFY_DATA                                                                                     \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_PARAM | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_KEY_UPDATE_ERROR | 0x17U)

/** Necessary challenge parameter not available */
#define ecy_hsm_CSAI_ERR_CHALLENGE_PARAMETER_ABSENT                                                                                                  \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_PARAM | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_KEY_UPDATE_ERROR | 0x18U)

/** unsupported scheme version */
#define ecy_hsm_CSAI_ERR_SECUACC_RESPONSE_INVALID_VERSION                                                                                            \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_PARAM | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_KEY_UPDATE_ERROR | 0x19U)

/** unsupported response message type */
#define ecy_hsm_CSAI_ERR_SECUACC_RESPONSE_INVALID_MSG_TYPE                                                                                           \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_PARAM | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_KEY_UPDATE_ERROR | 0x1AU)

/** invalid secacc use case */
#define ecy_hsm_CSAI_ERR_CHALLENGE_INVALID_USECASE                                                                                                   \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_PARAM | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_KEY_UPDATE_ERROR | 0x1BU)

/** unsupported response sequence tag */
#define ecy_hsm_CSAI_ERR_SECACC_RESPONSE_INVALID_SEQUENCE_TAG                                                                                        \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_PARAM | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_KEY_UPDATE_ERROR | 0x1CU)

/** unsupported response version tag */
#define ecy_hsm_CSAI_ERR_SECUACC_RESPONSE_INVALID_VERSION_TAG                                                                                        \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_PARAM | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_KEY_UPDATE_ERROR | 0x1DU)

/** unsupported response message type tag */
#define ecy_hsm_CSAI_ERR_SECACC_RESPONSE_INVALID_MSG_TYPE_TAG                                                                                        \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_PARAM | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_KEY_UPDATE_ERROR | 0x1EU)

/** unsupported response signature tag */
#define ecy_hsm_CSAI_ERR_SECACC_RESPONSE_INVALID_SIGNATURE_TAG                                                                                       \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_PARAM | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_KEY_UPDATE_ERROR | 0x1FU)

/** unsupported response certchain tag */
#define ecy_hsm_CSAI_ERR_SECACC_RESPONSE_INVALID_CERT_CHAIN_TAG                                                                                      \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_PARAM | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_KEY_UPDATE_ERROR | 0x20U)

/** unsupported response octet string tag */
#define ecy_hsm_CSAI_ERR_SECACC_RESPONSE_INVALID_OCTET_STRING_TAG                                                                                    \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_PARAM | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_KEY_UPDATE_ERROR | 0x21U)

/** Number of password entries wrong */
#define ecy_hsm_CSAI_ERR_PROT_PASSWORD_ENTRIES_WRONG                                                                                                 \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_PARAM | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x28U)

/** Size of at least one password is incorrect */
#define ecy_hsm_CSAI_ERR_PROT_PASSWORD_SIZE_WRONG                                                                                                    \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_PARAM | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x29U)

/** At least one password flag is incorrect */
#define ecy_hsm_CSAI_ERR_PROT_PASSWORD_FLAG_WRONG                                                                                                    \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_PARAM | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x2AU)

/** The supplied response total data has the wrong length */
#define ecy_hsm_CSAI_ERR_SECUACC_NONCE_SIZE_WRONG                                                                                                    \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_PARAM | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x2BU)

/** The debug functionality of the JTAG port is locked */
#define ecy_hsm_CSAI_ERR_JTAG_LOCKED                                                                                                                 \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_PARAM | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x2CU)

/** Wrong internal state during JTAG communication */
#define ecy_hsm_CSAI_ERR_JTAG_CBS_STATE                                                                                                              \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_PARAM | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x2DU)

/** Wrong internal error on JTAG Interface */
#define ecy_hsm_CSAI_ERR_JTAG_CBS_ACCESS                                                                                                             \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_PARAM | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x2FU)

/** The MAC verification fails during ECIES execution */
#define ecy_hsm_CSAI_ERR_ECIES_MAC_VERIFICATION_FAIL                                                                                                 \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_PARAM | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x30U)

/** @} */ // ANCHOR_CSAI_ERROR_CLASS_PARAM

/**
 * @anchor ANCHOR_CSAI_ERROR_CLASS_SEMANTIC
 * @name   Members of the CSAI error class @ref CSAI_ERROR_CLASS_SEMANTIC
 * @brief  These error codes indicate an error in the precondition of some call.
 * @{
 */

/** The state of the session or job is invalid for the call */
#define ecy_hsm_CSAI_ERR_INVALID_STATE                                                                                                               \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_SEQUENCE_ERROR | 0x01U)

/** The HSM has not been configured */
#define ecy_hsm_CSAI_ERR_HSM_NOT_CONFIGURED                                                                                                          \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x02U)

/** A session open call has been made on a port which already has an open session */
#define ecy_hsm_CSAI_ERR_SESSION_ALREADY_OPEN                                                                                                        \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_SEQUENCE_ERROR | 0x03U)

/** A session close call has been made on a port which does not have an open session */
#define ecy_hsm_CSAI_ERR_SESSION_ALREADY_CLOSED                                                                                                      \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_SEQUENCE_ERROR | 0x04U)

/** A job or operation request has been made on a port which does not have an open session */
#define ecy_hsm_CSAI_ERR_SESSION_CLOSED                                                                                                              \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_SEQUENCE_ERROR | 0x05U)

/** A job start call has been made on a session with a job that is already running */
#define ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED                                                                                                         \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_SEQUENCE_ERROR | 0x06U)

/** A service update or finish call has been made on a port with a job that is not started */
#define ecy_hsm_CSAI_ERR_JOB_NOT_STARTED                                                                                                             \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_SEQUENCE_ERROR | 0x07U)

/**A job update or finish call has been made on a session/port which is not the started job. For example the user started the hash job and called
 * update on an encryption job */
#define ecy_hsm_CSAI_ERR_WRONG_JOB                                                                                                                   \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_SEQUENCE_ERROR | 0x08U)

/** The HSM is not in the bootloader mode when it should be */
#define ecy_hsm_CSAI_ERR_NOT_BOOTLOADER                                                                                                              \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x09U)

/** The HSM is not in the core application mode when it should be */
#define ecy_hsm_CSAI_ERR_NOT_CORE_APP                                                                                                                \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x0AU)

/** The required key has not been loaded into the session */
#define ecy_hsm_CSAI_ERR_KEY_NOT_LOADED                                                                                                              \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_KEY_NOT_AVAILABLE | 0x0BU)

/** The supplied key is of the wrong type for the operation/job */
#define ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE                                                                                                              \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_KEY_INVALID | 0x0CU)

/** Only the last update call of a job may have a block size that is not a multiple of sixteen, and for an unpadded block cipher all blocks must be a
 * multiple of sixteen */
#define ecy_hsm_CSAI_ERR_UPDATE_BLOCK_SIZE                                                                                                           \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x0DU)

/** The supplied key ID does not map to a valid key slot */
#define ecy_hsm_CSAI_ERR_KEY_ID_INVALID                                                                                                              \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_KEY_INVALID | 0x0EU)

/** The supplied key is too big to fit in the keystore */
#define ecy_hsm_CSAI_ERR_KEY_TOO_BIG                                                                                                                 \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x0FU)

/** The required key has already been loaded into the session */
#define ecy_hsm_CSAI_ERR_KEY_ALREADY_LOADED                                                                                                          \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x11U)

/** The required key ID is currently loaded into an active session */
#define ecy_hsm_CSAI_ERR_KEY_ID_IN_USE                                                                                                               \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_KEY_NOT_AVAILABLE | 0x14U)

/** The required key ID contains a read-only key and may not be updated */
#define ecy_hsm_CSAI_ERR_KEY_IS_READ_ONLY                                                                                                            \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_KEY_WRITE_PROTECTED | 0x15U)

/** The specified key length is not supported */
#define ecy_hsm_CSAI_ERR_KEY_LENGTH_NOT_SUPPORTED                                                                                                    \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x18U)

/** The specified initialisation vector length is not supported */
#define ecy_hsm_CSAI_ERR_IV_LENGTH_NOT_SUPPORTED                                                                                                     \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x19U)

/** The HSM did not start when requested to do so */
#define ecy_hsm_CSAI_ERR_HSM_NOT_STARTED                                                                                                             \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x1AU)

/** The Secure Boot has failed, keys with the ecy_hsm_CSAI_KEYPROP_SECURE_BOOT_MUST_PASS property will not be available */
#define ecy_hsm_CSAI_ERR_NO_SECURE_BOOT                                                                                                              \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_NO_SECURE_BOOT | 0x1BU)

/** It is not allowed to persist or update a key with an existing KeyId to another KeyId (injected or derived keys do not initially have a KeyId at
 * all) */
#define ecy_hsm_CSAI_ERR_KEY_ID_CANNOT_BE_CHANGED                                                                                                    \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x1CU)

/** The HSM Proxy callouts have not been configured (the pointer is NULL_PTR) */
#define ecy_hsm_CSAI_ERR_NULL_CALLOUT                                                                                                                \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x1DU)

/** Catch-all error code to be returned from the QuickCMAC function if for some reason (like key not loaded) this feature is not available and the
 * regular CMAC should be used instead */
#define ecy_hsm_CSAI_ERR_QUICK_ROUTE_NOT_POSSIBLE                                                                                                    \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x1EU)

/** The authorization of CMD_DEBUG session failed. */
#define ecy_hsm_CSAI_ERR_DBG_AUTHENTICATION_FAILED                                                                                                   \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_NO_DEBUGGING | 0x1FU)

/** The priority of an operation is not supported. */
#define ecy_hsm_CSAI_ERR_PRIORITY_NOT_ALLOWED                                                                                                        \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x20U)

/** The required key is debug protected and may not be used when a debugger is attached */
#define ecy_hsm_CSAI_ERR_KEY_IS_DEBUG_PROTECTED                                                                                                      \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_KEY_NOT_AVAILABLE | 0x15U)

/** session/user privilege missing for privileged operation */
#define ecy_hsm_CSAI_ERR_PRIVILEGE_MISSING                                                                                                           \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x21U)

/** The supplied slot ID does not map to a valid key slot */
#define ecy_hsm_CSAI_ERR_SLOT_ID_TRUST_ANCHOR_INVALID                                                                                                \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_KEY_INVALID | 0x22U)

/** The supplied slot ID does not map to a valid OID slot */
#define ecy_hsm_CSAI_ERR_SLOT_ID_OID_INVALID                                                                                                         \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_KEY_INVALID | 0x23U)

/** only single instance of this applet type allowed */
#define ecy_hsm_CSAI_ERR_INSTANCE_EXCEEDED                                                                                                           \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x24U)

#define ecy_hsm_CSAI_ERR_TRUST_ANCHOR_INVALID                                                                                                        \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_KEY_INVALID | 0x25U)

/** The HSM is in suspended state, cannot execute the requested operation */
#define ecy_hsm_CSAI_ERR_HSM_SUSPENDED                                                                                                               \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x26U)

/** The Ecu is in wrong lifecycle */
#define ecy_hsm_CSAI_ERR_LIFECYCLE_WRONG                                                                                                             \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_SEQUENCE_ERROR | 0x2BU)

/** The passwords are programmed already */
#define ecy_hsm_CSAI_ERR_DATA_ALREADY_STORED                                                                                                         \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_SEQUENCE_ERROR | 0x2CU)

/** The state of the host storage module / cache is invalid */
#define ecy_hsm_CSAI_ERR_HOST_STORAGE_STATE_INVALID                                                                                                  \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x2DU)

/** The host storage module is not initialized */
#define ecy_hsm_CSAI_ERR_HOST_STORAGE_UNINITIALIZED                                                                                                  \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x2EU)

/** The host storage module / property is already initialized */
#define ecy_hsm_CSAI_ERR_HOST_STORAGE_ALREADY_INITIALIZED                                                                                            \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x2FU)

/** The DFLASH resources are inappropriately configured for the Host Storage feature */
#define ecy_hsm_CSAI_ERR_HOST_STORAGE_CONFIG_BAD                                                                                                     \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x30U)

/** The HSM transitions from core to bootloader in order to remain there. Requesting a new job from the host will fail as long as the booting was not
 * finished. */
#define ecy_hsm_CSAI_ERR_SWITCHING_FROM_CORE_TO_BOOT                                                                                                 \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x31U)

/** The RTMD was not suspended */
#define ecy_hsm_CSAI_ERR_TB_RTMD_NOT_SUSPENDED                                                                                                       \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x32U)

/** The RTMD is already suspended */
#define ecy_hsm_CSAI_ERR_TB_RTMD_IS_ALREADY_SUSPENDED                                                                                                \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x33U)

/**  */
/** The HSM bridge resource was falsely locked or unlocked multiple times. */
#define ecy_hsm_CSAI_ERR_RESOURCE_ALREADY_LOCKED_UNLOCKED                                                                                            \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x34U)

/** The RTMD check is not completed */
#define ecy_hsm_CSAI_ERR_TB_RTMD_CHECK_NOT_COMPLETED                                                                                                 \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x35U)

/** The RTMD is suspended */
#define ecy_hsm_CSAI_ERR_TB_RTMD_SUSPENDED                                                                                                           \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x36U)

/** An attempt was made to change one of the OTP attributes of a trusted sw part ref table entry */
#define ecy_hsm_CSAI_ERR_TRUSTED_SW_PART_OTP_VIOLATION                                                                                               \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x37U)

/** Signature verification has failed */
#define ecy_hsm_CSAI_ERR_SIGNATURE_VERIF_FAILED                                                                                                      \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x38U)

/** In SMART TB, An attempt was made to modify Trusted boot table attributes for Fixed SW-Part */
#define ecy_hsm_CSAI_ERR_SMART_TB_FIXED_BLOCK_VIOLATION                                                                                              \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x39U)

/** In SMART TB, An attempt was made to modify swPartSignMode other than ecy_hsm_CSAI_TB_VERIFMODE_MEMMAPPED_CERT for Fail-safe SW-Part */
#define ecy_hsm_CSAI_ERR_SMART_TB_FAILSAFE_BLOCK_VIOLATION                                                                                           \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x3AU)

/** Descriptor information is invalid or missing */
#define ecy_hsm_CSAI_ERR_SMART_TB_DESCRIPTOR_INFO_INVALID                                                                                            \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x3CU)

/** In SMART TB, the reference Table records does not cover the entirety of the configured Host PFlash range */
#define ecy_hsm_CSAI_ERR_SMART_TB_COVERAGE_CHECK_FAILED                                                                                              \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x3DU)

/** The HwCsp module is not initialized */
#define ecy_hsm_CSAI_ERR_HWCSP_UNINITIALIZED                                                                                                         \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x3EU)

/** The host integrity is failed */
#define ecy_hsm_CSAI_ERR_HOST_INTEGRITY_FAILED                                                                                                       \
 (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x3FU)

/** The ephemeral key pair are not available in TPM context */
#define ecy_hsm_CSAI_ERR_TPM_EPHEMERAL_KEYPAIR_NOT_AVAILABLE                                                                                         \
 (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SEMANTIC | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x40U)

/** @} */ // ANCHOR_CSAI_ERROR_CLASS_SEMANTIC

/**
 * @anchor ANCHOR_CSAI_ERROR_CLASS_RESOURCE
 * @name   Members of the CSAI error class @ref CSAI_ERROR_CLASS_RESOURCE
 * @brief  These error codes indicate a lack of resource within the HSM
 * @{
 */

/** The HSM has no more ports left to open a new session */
#define ecy_hsm_CSAI_ERR_OUT_OF_SESSION_PORTS                                                                                                        \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_RESOURCE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x1U)

/** The HSM has run out of available AES contexts */
#define ecy_hsm_CSAI_ERR_OUT_OF_AES_CONTEXTS                                                                                                         \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_RESOURCE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x3U)

/** The HSM has run out of space to queue requests at the specified priority level */
#define ecy_hsm_CSAI_ERR_NO_SPACE_FOR_REQUEST                                                                                                        \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_RESOURCE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x4U)

/** There are no key handle spaces left in this session */
#define ecy_hsm_CSAI_ERR_NO_SPACE_FOR_KEY_HANDLE                                                                                                     \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_RESOURCE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x5U)

/** There are no spare symmetric RAM key slots left */
#define ecy_hsm_CSAI_ERR_NO_SPACE_SYM_RAM_KEY                                                                                                        \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_RESOURCE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x6U)

/** There are no spare asymmetric RAM key slots left */
#define ecy_hsm_CSAI_ERR_NO_SPACE_ASYM_RAM_KEY                                                                                                       \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_RESOURCE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x7U)

/** There are no reference table entry slots left */
#define ecy_hsm_CSAI_ERR_NO_SPACE_REFTBL                                                                                                             \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_RESOURCE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x8U)

/** There is not enough dynamic memory left for allocating resources */
#define ecy_hsm_CSAI_ERR_NO_SPACE                                                                                                                    \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_RESOURCE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x9U)

/** The HwCsp keystore has run out of space to load a new key */
#define ecy_hsm_CSAI_ERR_HWCSP_NO_SPACE_FOR_KEY                                                                                                      \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_RESOURCE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0xAU)

/** The Host HwCsp was not able to lock the expected resource */
#define ecy_hsm_CSAI_ERR_HWCSP_RESOURCE_LOCKED                                                                                                       \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_RESOURCE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0xBU)

/** @} */ // ANCHOR_CSAI_ERROR_CLASS_RESOURCE

/**
 * @anchor ANCHOR_CSAI_ERROR_CLASS_COMMUNICATION
 * @name   Members of the CSAI error class @ref CSAI_ERROR_CLASS_COMMUNICATION
 * @brief  These error codes indicate an error in the communication to the HSM.
 * @{
 */

/** An unexpected timeout occurred while trying to communicate with the HSM. */
#define ecy_hsm_CSAI_ERR_TIMEOUT                                                                                                                     \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_COMMUNICATION | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_SEQUENCE_ERROR | 0x1U)

/** @} */ // ANCHOR_CSAI_ERROR_CLASS_COMMUNICATION

/**
 * @anchor ANCHOR_CSAI_ERROR_CLASS_INTERNAL
 * @name   Members of the CSAI error class @ref CSAI_ERROR_CLASS_INTERNAL
 * @brief  These error codes indicate an internal error in the HSM.
 * @{
 */

/** Parameter to an internal function is invalid */
#define ecy_hsm_CSAI_ERR_INTERNAL_PARAM                                                                                                              \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_INTERNAL | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x01U)

/** The HSM has crashed, probably bus error or watchdog timeout */
#define ecy_hsm_CSAI_ERR_CRASH (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_INTERNAL | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x02U)

/** The OS cannot activate a task to action an operation request */
#define ecy_hsm_CSAI_ERR_OS_CANNOT_ACTIVATE_TASK                                                                                                     \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_INTERNAL | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x03U)

/** The HSM has encountered a hardware error */
#define ecy_hsm_CSAI_ERR_HARDWARE                                                                                                                    \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_INTERNAL | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x04U)

/** An error has been returned by CycurLib */
#define ecy_hsm_CSAI_ERR_CYCURLIB                                                                                                                    \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_INTERNAL | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x05U)

/** The OS cannot activate a task to action an operation request */
#define ecy_hsm_CSAI_ERR_OS_SCHEDULE_ERROR                                                                                                           \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_INTERNAL | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x06U)

/** There has been error reported from the EEPROM emulation */
#define ecy_hsm_CSAI_ERR_EEPROM_EMULATION                                                                                                            \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_INTERNAL | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_MEMORY_FAILURE | 0x07U)

/** The EEPROM emulation is full */
#define ecy_hsm_CSAI_ERR_EEPROM_FULL                                                                                                                 \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_INTERNAL | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_MEMORY_FAILURE | 0x08U)

/** There has been a miscellaneous keystore error */
#define ecy_hsm_CSAI_ERR_KEYSTORE                                                                                                                    \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_INTERNAL | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x09U)

/** The True Random Number Generator reports an error */
#define ecy_hsm_CSAI_ERR_TRNG (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_INTERNAL | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x0AU)

/** The AES Accelerator reports an error */
#define ecy_hsm_CSAI_ERR_AES_ACCELERATOR1                                                                                                            \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_INTERNAL | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x0BU)

/** The AES Accelerator reports an error */
#define ecy_hsm_CSAI_ERR_AES_ACCELERATOR2                                                                                                            \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_INTERNAL | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x0CU)

/** The HSM has detected an operation that would result in buffer over-run */
#define ecy_hsm_CSAI_ERR_HSM_BUFFER_OVERRUN                                                                                                          \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_INTERNAL | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x0DU)

/** There is a problem with the HT2HSMF (flags) register, probably caused by trying to configure
    before starting the HSM */
#define ecy_hsm_CSAI_ERR_HT2HSMF_LOCKUP                                                                                                              \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_INTERNAL | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x0EU)

/** There is a problem with the HSM2HTS (status) register, probably caused by a failed HSM startup */
#define ecy_hsm_CSAI_ERR_HSM2HTS_LOCKUP (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_INTERNAL | 0x0FU)

/** The EEPROM was not erased when it should have been */
#define ecy_hsm_CSAI_ERR_EEPROM_NOT_ERASED                                                                                                           \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_INTERNAL | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_MEMORY_FAILURE | 0x10U)

/** The stack overflow hook has been hit */
#define ecy_hsm_CSAI_ERR_STACK_OVERFLOW                                                                                                              \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_INTERNAL | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x11U)

/** The EEPROM access was not successful */
#define ecy_hsm_CSAI_ERR_EEPROM_ACCESS                                                                                                               \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_INTERNAL | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_MEMORY_FAILURE | 0x12U)

/** The Renesas FAL library reported an error */
#define ecy_hsm_CSAI_ERR_FAL_LIBRARY                                                                                                                 \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_INTERNAL | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_MEMORY_FAILURE | 0x13U)

/** There has been a miscellaneous datastore error */
#define ecy_hsm_CSAI_ERR_DATASTORE                                                                                                                   \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_INTERNAL | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_MEMORY_FAILURE | 0x14U)

/** There CFG Version missmatch error */
#define ecy_hsm_CSAI_ERR_CFG_VERSION_MISSMATCH                                                                                                       \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_INTERNAL | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_MEMORY_FAILURE | 0x15U)

/** There could be no password protections password found */
#define ecy_hsm_CSAI_ERR_NO_PROT_PASSWORD_STORED                                                                                                     \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_INTERNAL | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x16U)

/** The task is already active */
#define ecy_hsm_CSAI_ERR_TASK_ALREADY_ACTIVATED                                                                                                      \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_INTERNAL | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_MEMORY_FAILURE | 0x17U)

/** The task is already deactivated */
#define ecy_hsm_CSAI_ERR_TASK_ALREADY_DEACTIVATED                                                                                                    \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_INTERNAL | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_MEMORY_FAILURE | 0x18U)

/** Integrity check of HSM core application failed */
#define ecy_hsm_CSAI_ERR_CORE_INVALID                                                                                                                \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_INTERNAL | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x19U)

/** HSM has not been booted. Neither end pattern nor CMAC of HSM core application has been verified. */
#define ecy_hsm_CSAI_ERR_CORE_NOT_VERIFIED                                                                                                           \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_INTERNAL | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x1AU)

/** Integrity check of HSM core application partially executed. End pattern is correct, CMAC not verified. */
#define ecy_hsm_CSAI_ERR_CORE_PRESENT_INTEGRITY_NOT_CHECKED                                                                                          \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_INTERNAL | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x1BU)

/** The HASH Accelerator reports an error */
#define ecy_hsm_CSAI_ERR_HASH_ACCELERATOR                                                                                                            \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_INTERNAL | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x1CU)

/** Internal assert error @note: This error code shall be used only for ESCRYPT internal testing */
#define ecy_hsm_CSAI_ERR_ASSERT_DEBUG_ERROR                                                                                                          \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_INTERNAL | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x1DU)

/** The ECC Accelerator reports an error */
#define ecy_hsm_CSAI_ERR_ECC_ACCELERATOR                                                                                                             \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_INTERNAL | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x1EU)

/** A write or read access to a memory location by an HW accelerator or the CPU caused an error/exception (e.g. ECC) */
#define ecy_hsm_CSAI_ERR_MEMORY_ACCESS                                                                                                               \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_INTERNAL | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x1FU)

/** A read access to HOST NVM by an HW accelerator or the CPU caused an error/exception (e.g. ECC) */
#define ecy_hsm_CSAI_ERR_HOST_CODENVM_READ                                                                                                           \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_INTERNAL | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x20U)

/** The HwCsp reports an error */
#define ecy_hsm_CSAI_ERR_HWCSP (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_INTERNAL | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x21U)

/** @} */ // ANCHOR_CSAI_ERROR_CLASS_INTERNAL

/**
 * @anchor ANCHOR_CSAI_ERROR_CLASS_VIOLATION
 * @name   Members of the CSAI error class @ref CSAI_ERROR_CLASS_VIOLATION
 * @brief  These error codes indicate security policy violations.
 * @{
 */

/** General security policy violation */
#define ecy_hsm_CSAI_ERR_POLICY_VIOLATION                                                                                                            \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_VIOLATION | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x01U)

/** There has been an attempt to use a key in violation of its property flags */
#define ecy_hsm_CSAI_ERR_KEY_PROPERTY_VIOLATION                                                                                                      \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_VIOLATION | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_KEY_INVALID | 0x02U)

/** There has been an attempt to access the SHE BOOT_MAC or BOOT_MAC_KEY key via the CSAI */
#define ecy_hsm_CSAI_ERR_SHE_KEY_NOT_ALLOWED                                                                                                         \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_VIOLATION | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_KEY_INVALID | 0x03U)

/** There has been an attempt to access HSM ram address via the CSAI or SHE interface*/
#define ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION                                                                                                           \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_VIOLATION | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x04U)

/** The specified key has not been loaded into this session */
#define ecy_hsm_CSAI_ERR_KEY_WRONG_SESSION                                                                                                           \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_VIOLATION | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x05U)

/** The specified key is locked because SHE Secure Boot failed (the key must have the ecy_hsm_CSAI_KEYPROP_SECURE_BOOT_MUST_PASS property) */
#define ecy_hsm_CSAI_ERR_KEY_LOCKED_BY_SECURE_BOOT                                                                                                   \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_VIOLATION | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_KEY_NOT_AVAILABLE | 0x06U)

/** The specified key is locked because SHE Secure Boot failed (the key must have the ecy_hsm_CSAI_KEYPROP_SECURE_BOOT_MUST_PASS property) */
#define ecy_hsm_CSAI_ERR_KEY_LOCKED_BY_DEBUG                                                                                                         \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_VIOLATION | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_KEY_NOT_AVAILABLE | 0x07U)

/** The security critical functions are disabled */
#define ecy_hsm_CSAI_ERR_SECFUNC_LOCKED                                                                                                              \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_VIOLATION | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x08U)

/** No privilege to delete the trusted boot table entry */
#define ecy_hsm_CSAI_ERR_TB_SECACC_PRIVILEGE_MISSING                                                                                                 \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_VIOLATION | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x09U)

/** No privilege for HSM deactivation */
#define ecy_hsm_CSAI_ERR_HSMDEACT_SECACC_PRIVILEGE_MISSING                                                                                           \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_VIOLATION | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x0AU)

/** General error to indicate that the SW Part verification failed */
#define ecy_hsm_CSAI_ERR_TB_VERIFICATION_FAILED                                                                                                      \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_VIOLATION | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x0BU)

/** The specified key has not been loaded into these workspaces */
#define ecy_hsm_CSAI_ERR_KEY_WRONG_WORKSPACES                                                                                                        \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_VIOLATION | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x0CU)

/** @} */ // ANCHOR_CSAI_ERROR_CLASS_VIOLATION

/**
 * @anchor ANCHOR_CSAI_ERR_CLASS_MIDDLEWARE
 * @name   Members of the CSAI error class @ref ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE
 * @brief  These error codes indicate parsing/encoding errors.
 * @{
 */

/** A DER encoded element cannot be parsed since it is not entirely accessible. By providing the missing data the element may still be parsed
 * successfully. */
#define ecy_hsm_CSAI_ERR_PARSER_INSUFFICIENT_DATA                                                                                                    \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x01U)

/** A DER encoded element is considered invalid since its tag is either too long or malformed */
#define ecy_hsm_CSAI_ERR_PARSER_INVALID_TAG_SIZE                                                                                                     \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x02U)

/** A DER encoded element is considered invalid since its length is either too long or malformed */
#define ecy_hsm_CSAI_ERR_PARSER_INVALID_LENGTH_SIZE                                                                                                  \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x03U)

/** During DER encoding a malformed DER element was found (Tag=0) -> Recommendation: Discard whole parsing results of that stream */
/** DER forbids elements with a Tag = 0 (See X.690 Chapter 8.1.3.6) */
#define ecy_hsm_CSAI_ERR_PARSER_MALFORMED_DATA                                                                                                       \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x04U)

/**  During parsing process the amount of nested levels was exceeded -> Parsing of that stream not possible */
#define ecy_hsm_CSAI_ERR_PARSER_NESTED_LEVEL                                                                                                         \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x05U)

/**  Parser function call with invalid parameter */
#define ecy_hsm_CSAI_ERR_PARSER_INVALID_PARAMETER                                                                                                    \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x06U)

/**  Parser function could not find any element in stream to be parsed */
#define ecy_hsm_CSAI_ERR_PARSER_NO_ELEMENTS_FOUND                                                                                                    \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x07U)

/** output buffer pointer not initialized */
#define ecy_hsm_CSAI_ERR_ENCODING_NULL_PTR                                                                                                           \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x0AU)

/** not supported encoding method, class */
#define ecy_hsm_CSAI_ERR_ENCODING_METHOD_NOT_SUPPORTED                                                                                               \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x0BU)

/**  not supported type, class */
#define ecy_hsm_CSAI_ERR_ENCODING_TYPE_NOT_SUPPORTED                                                                                                 \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x0CU)

/**  not enough space in output buffer */
#define ecy_hsm_CSAI_ERR_ENCODING_NOT_ENOUGH_SPACE                                                                                                   \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x0DU)

/**  Certificate contains wrong signature */
#define ecy_hsm_CSAI_ERR_CERT_WRONG_SIGNATURE                                                                                                        \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x0EU)

/**  Parser function call with invalid parameter */
#define ecy_hsm_CSAI_ERR_PARSER_NULL_POINTER                                                                                                         \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x0FU)

/**  Parser function call with invalid parameter */
#define ecy_hsm_CSAI_ERR_PARSER_WRONG_TYPE                                                                                                           \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x10U)

/**  Parser function call with invalid parameter */
#define ecy_hsm_CSAI_ERR_PARSER_WRONG_SIZE                                                                                                           \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x11U)

/** not supported encoding class */
#define ecy_hsm_CSAI_ERR_ENCODING_CLASS_NOT_SUPPORTED                                                                                                \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x12U)

/** Number range of CSAI_ERR_UPDATE_... must be a continuous block !!! */

#define ecy_hsm_CSAI_ERR_UPDATE_UNSPECIFIED_ERROR                                                                                                    \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x18U)

#define ecy_hsm_CSAI_ERR_UPDATE_INTERNAL                                                                                                             \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x19U)

#define ecy_hsm_CSAI_ERR_UPDATE_ERASEINIT                                                                                                            \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x1AU)

#define ecy_hsm_CSAI_ERR_UPDATE_ERASE                                                                                                                \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x1BU)

/**  Error occurred during start of the update of Security Settings Area. */
#define ecy_hsm_CSAI_ERR_UPDATE_PROGINIT                                                                                                             \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x1CU)

/** Error occurred during the update of Security Settings Area. */
#define ecy_hsm_CSAI_ERR_UPDATE_PROG                                                                                                                 \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x1DU)

#define ecy_hsm_CSAI_ERR_UPDATE_BACKUP                                                                                                               \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x1EU)

#define ecy_hsm_CSAI_ERR_UPDATE_VAL_BOOT                                                                                                             \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x1FU)

/** The signature of the boot area could not be verified successfully. */
#define ecy_hsm_CSAI_ERR_UPDATE_BOOT_VER                                                                                                             \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x20U)

#define ecy_hsm_CSAI_ERR_UPDATE_COPY_BOOT                                                                                                            \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x21U)

/** The signature/hash of the configuration area could not be verified successfully. */
#define ecy_hsm_CSAI_ERR_UPDATE_CFG_VER                                                                                                              \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x22U)

/** The signature of the core area could not be verified successfully. */
#define ecy_hsm_CSAI_ERR_UPDATE_CORE_VER                                                                                                             \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x23U)

/** The epilog contained in the configuration area could not be parsed successfully. */
#define ecy_hsm_CSAI_ERR_UPDATE_PARSE_CFG_EPILOG                                                                                                     \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x24U)

/** The user certificate contained in the epilog of the configuration area could not be verified successfully. */
#define ecy_hsm_CSAI_ERR_UPDATE_CFG_CERT_VER                                                                                                         \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x25U)

/** The HSM synchronous update failed due to timeout in performing FLS job. */
#define ecy_hsm_CSAI_ERR_UPDATE_POLL_TIMEOUT                                                                                                         \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x26U)

/** An invalid parameter was passed to the update job, e.g. NULL_PTR, invalid flash  length or options */
#define ecy_hsm_CSAI_ERR_ERR_UPDATE_INVALID_PARAM                                                                                                    \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x27U)

/**  Certificate contains wrong OID */
#define ecy_hsm_CSAI_ERR_CERT_WRONG_OID                                                                                                              \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x28U)

/* ************************** HSM update - with verification header - Error codes ********************************/
/** The HSM Signed Header was not verified prior to a Data Transfer Request being sent to the HSM. **/
#define ecy_hsm_CSAI_ERR_UPDATE_TRANSFER_REQ                                                                                                         \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x29U)

/** This error indicates that the HSM Update container is not in the appropriate memory of the host. */
#define ecy_hsm_CSAI_ERR_UPDATE_HOST_MEMORY                                                                                                          \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x2AU)

/** This is an attempt to flash the same firmware that is already installed. The Message Digest of Plaintext HSM Application in HSM Signed Header is
 * the same as the message digest currently in the HSM Application SW Info stored in the HSM code flash. */
#define ecy_hsm_CSAI_ERR_UPDATE_CORE_APP_SAME                                                                                                        \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x2BU)

/** Length of the HSM bootloader and HSM application as defined in the SW Location Info of the HSM Signed Header is more than the allocated space. */
#define ecy_hsm_CSAI_ERR_UPDATE_LENGTH_EXCEEDED                                                                                                      \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x2CU)

/** Module ID is not valid. */
#define ecy_hsm_CSAI_ERR_UPDATE_MODULE_ID                                                                                                            \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x2DU)

/** HSM core application SW is not compatible with HSM boot SW. major version mismatch */
#define ecy_hsm_CSAI_ERR_UPDATE_CORE_BOOT_COMPAT                                                                                                     \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x2EU)

/** The ECU name in the Signed Header does not match the one stored in the HSM Info Block. */
#define ecy_hsm_CSAI_ERR_UPDATE_ECU_NAME                                                                                                             \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x2FU)

/** The Signed Header has an invalid signature. */
#define ecy_hsm_CSAI_ERR_UPDATE_SIGNED_HEADER_VER                                                                                                    \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x30U)

/** The HSM SW has an older security version than the current programmed version.*/
#define ecy_hsm_CSAI_ERR_UPDATE_DOWNGRADE_ATTEMPT                                                                                                    \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x31U)

/** The Subject Name in the Signed Header does not match the expected Subject Name stored in the HSM Info block. */
#define ecy_hsm_CSAI_ERR_UPDATE_SUBJECT_NAME                                                                                                         \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x32U)

/** The Signer Info certificate has an older security version than the previously used one known to the HSM.*/
#define ecy_hsm_CSAI_ERR_UPDATE_KEY_NBID                                                                                                             \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x33U)

/** The message digest calculated over the full HSM update container in the host code flash does not match the Message Digest of Full HSM
 * Update in the HSM Signed Header.*/
#define ecy_hsm_CSAI_ERR_UPDATE_MD_FULL                                                                                                              \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x34U)

/** The Signer Info certificate has an invalid signature. */
#define ecy_hsm_CSAI_ERR_UPDATE_SIGNERINFO_ROOT_SIG_VERIFICATION                                                                                     \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x35U)

/** @deprecated: The Signer Info certificate has an invalid signature. Only required for backwards compatibility */
#define ecy_hsm_CSAI_ERR_UPDATE_SIGNERINFO_ROOT_SIG_VER                                                                                              \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x35U)

/** The update of the inactive bank was not successful */
#define ecy_hsm_CSAI_ERR_UPDATE_INACTIVE_BANK_FAILED                                                                                                 \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x36U)

/** The firmware decryption key was not found. */
#define ecy_hsm_CSAI_ERR_UPDATE_FW_DEC_KEY_ABSENT                                                                                                    \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x37U)

/** Firmware decryption of the incoming update container failed. */
#define ecy_hsm_CSAI_ERR_UPDATE_FW_DEC_FAILED                                                                                                        \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x38U)

/** The hash of the custom epilog area could not be verified successfully. */
#define ecy_hsm_CSAI_ERR_UPDATE_CUST_EPILOG_VER                                                                                                      \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x39U)

/** A downgrade protection configuration resource could not be located/Magic string incorrect. */
#define ecy_hsm_CSAI_ERR_UPDATE_ERR_DOWNGRADE_PROT_CONFIG_WRONG                                                                                      \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x3AU)

/** The resource configuration is invalid */
#define ecy_hsm_CSAI_ERR_INVALID_CONFIG_OBJ                                                                                                          \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x3BU)

/** The Custom code header information are invalid */
#define ecy_hsm_CSAI_ERR_INVALID_CUSTOMCODE_HEADER                                                                                                   \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x3CU)

/** Bootloader hash does not match the hash contained as prevPartHash in Core */
#define ecy_hsm_CSAI_ERR_UPDATE_BOOT_CORE_COUPLING_MISMATCH                                                                                          \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x3DU)

/** The digital signature algorithm in the signer info doesn't match the one in the HSM info block */
#define ecy_hsm_CSAI_ERR_UPDATE_SIGNERINFO_DSA_MISMATCH                                                                                              \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x3EU)

/** The HSM Signed Header has an invalid MAC. */
#define ecy_hsm_CSAI_ERR_UPDATE_SIGNED_HEADER_MAC_VERIF                                                                                              \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x3FU)

/* ********************************** HSM update - with verification header - Error List end ********************************/

/** The new context patterns was not set correctly for the bank switching */
#define ecy_hsm_CSAI_ERR_BANK_SWAP_PATTERNS_FAILED                                                                                                   \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x40U)

/** The HW feature is not enabled for the context switch (bank swap) */
#define ecy_hsm_CSAI_ERR_BANK_SWAP_NOT_SUPPORTED                                                                                                     \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x41U)

/** The SECACC challenge signature verification failed. The user cert passed within the response is ok.
    This is an internal error code not passed to the user. */
#define ecy_hsm_CSAI_ERR_SECACC_WRONG_SIGNATURE                                                                                                      \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x42U)

/** The bank has not been swapped until now after the last HSM bank swap set up */
#define ecy_hsm_CSAI_ERR_BANK_NOT_SWAPPED                                                                                                            \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x43U)

/** CycurHSM firmware update is rejected. The padding bytes of the bootloader or the core app have been modified. */
#define ecy_hsm_CSAI_ERR_UPDATE_PADDING_BYTES_MANIPULATED                                                                                            \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x44U)

/** The bank mode and map mode are not consistent during HSM update */
#define ecy_hsm_CSAI_ERR_FLASH_BANK_MODE_INCONSISTENT                                                                                                \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x45U)

/** CycurHSM firmware update is rejected. An unauthorized pattern has been found in a section where it is not allowed e.g. start config area */
#define ecy_hsm_CSAI_ERR_UPDATE_CONTAINER_INVALID_PATTERN                                                                                            \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x46U)
/** @} */ // ANCHOR_CSAI_ERR_CLASS_MIDDLEWARE

/** HSM flash address configuration incorrect **/
#define ecy_hsm_CSAI_ERR_INVALID_HSM_CONFIGURATION                                                                                            \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_MIDDLEWARE | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x47U)

/**
 * @anchor ANCHOR_CSAI_ERROR_CLASS_SSS
 * @name   Members of the CSAI error class @ref CSAI_ERROR_CLASS_SSS
 * @brief  These error codes indicate errors that origin from the Secure Space Scripting module
 * @{
 */

/** Reached end of script bytecode while reading */
#define ecy_hsm_CSAI_ERR_SSS_END_OF_BYTECODE                                                                                                         \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SSS | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x01U)

/** Read param value from script bytecode is invalid */
#define ecy_hsm_CSAI_ERR_SSS_PARAM_VALUE_INVALID                                                                                                     \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SSS | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x02U)

/** Read param mode from script bytecode is invalid */
#define ecy_hsm_CSAI_ERR_SSS_PARAM_MODE_INVALID                                                                                                      \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SSS | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x03U)

/** Invalid script ID provided to Script Database */
#define ecy_hsm_CSAI_ERR_SSS_INVALID_SCRIPT_ID                                                                                                       \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SSS | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x04U)

/** One of the instructions failed */
#define ecy_hsm_CSAI_ERR_SSS_VM_INSTRUCTION_ERROR                                                                                                    \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SSS | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x05U)

/** Invalid function code encountered in the bytecode */
#define ecy_hsm_CSAI_ERR_SSS_INVALID_INSTRUCTION_CODE                                                                                                \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SSS | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x06U)

/** Sanity check of the script header failed */
#define ecy_hsm_CSAI_ERR_SSS_INVALID_SCRIPT_HEADER                                                                                                   \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SSS | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x07U)

/** Read param mode from script bytecode is not allowed for this parameter */
#define ecy_hsm_CSAI_ERR_SSS_PARAM_MODE_NOT_ALLOWED                                                                                                  \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SSS | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x08U)

/** Garbage collector cannot collect anymore since it is full */
#define ecy_hsm_CSAI_ERR_SSS_GARBAGE_COLLECTOR_FULL                                                                                                  \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SSS | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x0AU)

/** Garbage collector cannot remove anything from its collection since it is empty */
#define ecy_hsm_CSAI_ERR_SSS_GARBAGE_COLLECTOR_EMPTY                                                                                                 \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SSS | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x0BU)

/** Garbage collector is used before it was initialized */
#define ecy_hsm_CSAI_ERR_SSS_GARBAGE_COLLECTOR_UNINITIALIZED                                                                                         \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SSS | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x0CU)

/** Garbage collector is invoked to drop a handle which is not in its list  */
#define ecy_hsm_CSAI_ERR_SSS_GARBAGE_COLLECTOR_HANDLE_NOT_FOUND                                                                                      \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SSS | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x0DU)

/** Release of collected handles failed partially or completely  */
#define ecy_hsm_CSAI_ERR_SSS_GARBAGE_COLLECTOR_RELEASE_FAILED                                                                                        \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SSS | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x0EU)

/** Execution of the assert instruction failed */
#define ecy_hsm_CSAI_ERR_SSS_ASSERT_FAILED                                                                                                           \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SSS | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x0FU)

/** @} */ // ANCHOR_CSAI_ERROR_CLASS_SSS

/**
 * @anchor ANCHOR_CSAI_ERROR_CLASS_OTHER
 * @name   Members of the CSAI error class @ref CSAI_ERROR_CLASS_OTHER
 * @brief  These error codes indicate errors that do not fit in the other classes.
 * @{
 */

/** Undefined error used to initialise an error code variable before some tests */
#define ecy_hsm_CSAI_ERR_UNDEFINED (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_OTHER | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x1U)

/** Error code used for the operation error code in the event that an operation request fails */
#define ecy_hsm_CSAI_ERR_OP_REQUEST_FAILED                                                                                                           \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_OTHER | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x2U)

/** Code used to indicate that a slot in the bulk MAC control table is to be ignored (skipped) */
#define ecy_hsm_CSAI_ERR_BULK_MAC_SKIP                                                                                                               \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_OTHER | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x3U)

/** Code used to indicate that a slot in the bulk MAC control table is ready for processing */
#define ecy_hsm_CSAI_ERR_BULK_MAC_READY                                                                                                              \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_OTHER | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x4U)

/** Code used to indicate that a slot in the bulk MAC control table failed the safety check */
#define ecy_hsm_CSAI_ERR_MAC_VERIFY_SAFETY_FAILED                                                                                                    \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_OTHER | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR | 0x5U)

/** @} */ // ANCHOR_CSAI_ERROR_CLASS_OTHER

/**
 * @anchor ANCHOR_CSAI_ERROR_FLOW_CONTROL_CODES
 * @name   CSAI Flow Control Result Codes
 * @brief  Predefined values of @ref ecy_hsm_Csai_ErrorT to specify an expected flow control result.
 * @{
 */

/**
 * The called functionality is busy, i.e. the port/session is processing a different operation.
 * This code is returned by the operation request functions (ecy_HSM_OpRequest_NoJobHandle and ecy_HSM_OpRequest_WithJobHandle).
 * Please try again later.
 */
#define ecy_hsm_CSAI_FC_BUSY    (ecy_hsm_CSAI_ERR_FLAG_FLOW_CONTROL | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_BUSY | 0x1U)

/**
 * The called functionality is busy, the requested job is either pending or processing.
 * This code is returned by the poll job handle function.
 * Please keep trying.
 */
#define ecy_hsm_CSAI_FC_PENDING (ecy_hsm_CSAI_ERR_FLAG_FLOW_CONTROL | ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_BUSY | 0x2U)

/** @} */ // ANCHOR_CSAI_ERROR_FLOW_CONTROL_CODES

/** @} */ // ANCHOR_CSAI_ERROR_RESULT_CODES

/* *** type declarations **********************************************************************/

/* *** global constants ***********************************************************************/

/* *** exported interfaces ********************************************************************/

/** @} */ // GROUP_CSAI_ERROR_MANAGEMENT

#endif    /* Multiple inclusion lock */
