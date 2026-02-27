/**
 * @cond SSS_DOXYGEN_ENABLED
 * @file
 ***********************************************************************************************
 * @brief Secure Space Scripting CSAI interface
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2021, all rights reserved
 **********************************************************************************************/
/* [$Satisfies $COMPONENT Secure_Space_Scripting_CSAI] */

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_CSAI_SSS_H
# define ECY_HSM_CSAI_SSS_H

/**
 * @addtogroup GROUP_CSAI_SSS
 * @{
 */

/* *** includes *******************************************************************************/

# include "Platform_Types.h"
# include "ecy_hsm_csai.h"
# include "ecy_hsm_csai_vms_pub_sss.h"

/* *** defines ********************************************************************************/

/**
 * @brief Default instruction code returned in the ecy_hsm_Csai_Sss_StatusInfoT when the actual
 * instruction code is not available
 */
# define ecy_hsm_SSS_FUNC_DEFAULT 0x0000U

/* *** type declarations **********************************************************************/

/**
 * @brief Possible VM states
 */
typedef enum ecy_hsm_Sss_VmStateTag
{
    ecy_hsm_SSS_VM_UNINITIALIZED = 0, /**< VM is not fully initialized (must have value 0) */
    ecy_hsm_SSS_VM_IDLE,              /**< VM is initialized and idle */
    ecy_hsm_SSS_VM_WAITING,           /**< VM is waiting */
    ecy_hsm_SSS_VM_RUNNING,           /**< VM is running instructions */
    ecy_hsm_SSS_VM_ERROR,             /**< VM entered erroneous state */
    ecy_hsm_SSS_VM_FINISHED,          /**< VM finished the script */

    ecy_hsm_SSS_VM_RESERVED = 0x7FFFFFFFU /**< Ensure 32 bits are used for the enum */
} ecy_hsm_Sss_VmStateT;

/**
 * @brief Enum which describe the Function Ids used in bytecode
 * @note !! Don't modify numbers as it is in sync with already existing scripts !!
 */
/* clang-format off */
typedef enum ecy_hsm_SssFunctionTag
{
     /* General flow control instructions */
    ecy_hsm_SSS_FUNC_NOP                                                = 0x0000U,
    ecy_hsm_SSS_FUNC_STOP                                               = 0x0001U,
    ecy_hsm_SSS_FUNC_WAIT                                               = 0x0002U,
    ecy_hsm_SSS_FUNC_JUMP                                               = 0x0003U,
    ecy_hsm_SSS_FUNC_JUMP_IF_EQUAL                                      = 0x0004U,
    ecy_hsm_SSS_FUNC_JUMP_IF_NOT_EQUAL                                  = 0x0005U,
    ecy_hsm_SSS_FUNC_JUMP_IF_GREATER                                    = 0x0006U,
    ecy_hsm_SSS_FUNC_JUMP_IF_GREATER_OR_EQUAL                           = 0x0007U,
    ecy_hsm_SSS_FUNC_JUMP_IF_SMALLER                                    = 0x0008U,
    ecy_hsm_SSS_FUNC_JUMP_IF_SMALLER_OR_EQUAL                           = 0x0009U,

    /* Basic calculus */
    ecy_hsm_SSS_FUNC_ADD                                                = 0x000AU,
    ecy_hsm_SSS_FUNC_SUB                                                = 0x000BU,
    ecy_hsm_SSS_FUNC_MUL                                                = 0x000CU,
    ecy_hsm_SSS_FUNC_DIV                                                = 0x000DU, /* Untypical on embedded but for completeness */
    ecy_hsm_SSS_FUNC_MOD                                                = 0x000EU,

    /* Bitwise / logical operations */
    ecy_hsm_SSS_FUNC_BINARY_OR                                          = 0x0010U,
    ecy_hsm_SSS_FUNC_BINARY_AND                                         = 0x0011U,
    ecy_hsm_SSS_FUNC_BINARY_XOR                                         = 0x0012U,
    ecy_hsm_SSS_FUNC_BINARY_NOT                                         = 0x0013U,
    ecy_hsm_SSS_FUNC_BINARY_LSHIFT                                      = 0x0014U,
    ecy_hsm_SSS_FUNC_BINARY_RSHIFT                                      = 0x0015U,

    /* Memory modification */
    ecy_hsm_SSS_FUNC_MEMCPY                                             = 0x0018U,
    ecy_hsm_SSS_FUNC_MEMSET                                             = 0x0019U,
    ecy_hsm_SSS_FUNC_MEMCMP                                             = 0x001AU,
    ecy_hsm_SSS_FUNC_ASSERT_MEM_EQUAL                                   = 0x001BU,
    ecy_hsm_SSS_FUNC_ASSERT_VAL_EQUAL                                   = 0x001CU,
    ecy_hsm_SSS_FUNC_VALUE_CPY                                          = 0x001DU,

    /* Memory (de)allocation */
    ecy_hsm_SSS_FUNC_MEM_ALLOC                                          = 0x001EU,
    ecy_hsm_SSS_FUNC_MEM_DEALLOC                                        = 0x001FU,

    /* Service calls */
    ecy_hsm_SSS_FUNC_SERVICE_ENCRYPT                                    = 0x0020U,
    ecy_hsm_SSS_FUNC_SERVICE_ENCRYPT_START                              = 0x0021U,
    ecy_hsm_SSS_FUNC_SERVICE_ENCRYPT_UPDATE                             = 0x0022U,
    ecy_hsm_SSS_FUNC_SERVICE_ENCRYPT_FINISH                             = 0x0023U,

    ecy_hsm_SSS_FUNC_SERVICE_DECRYPT                                    = 0x0024U,
    ecy_hsm_SSS_FUNC_SERVICE_DECRYPT_START                              = 0x0025U,
    ecy_hsm_SSS_FUNC_SERVICE_DECRYPT_UPDATE                             = 0x0026U,
    ecy_hsm_SSS_FUNC_SERVICE_DECRYPT_FINISH                             = 0x0027U,

    ecy_hsm_SSS_FUNC_SERVICE_INJECT_SYM_KEY                             = 0x0028U,
    ecy_hsm_SSS_FUNC_SERVICE_INJECT_RSA_PAIR_KEY                        = 0x0029U,
    ecy_hsm_SSS_FUNC_SERVICE_INJECT_RSA_PUBLIC_KEY                      = 0x002AU,
    ecy_hsm_SSS_FUNC_SERVICE_INJECT_RSA_PRIVATE_KEY                     = 0x002BU,
    ecy_hsm_SSS_FUNC_SERVICE_INJECT_EDDSA_PAIR_KEY                      = 0x002CU,
    ecy_hsm_SSS_FUNC_SERVICE_INJECT_EDDSA_PUBLIC_KEY                    = 0x002DU,
    ecy_hsm_SSS_FUNC_SERVICE_INJECT_ECDSA_PAIR_KEY                      = 0x002EU,
    ecy_hsm_SSS_FUNC_SERVICE_INJECT_ECDSA_PUBLIC_KEY                    = 0x002FU,
    ecy_hsm_SSS_FUNC_SERVICE_INJECT_ECDSA_PRIVATE_KEY                   = 0x0030U,
    ecy_hsm_SSS_FUNC_SERVICE_INJECT_ELLIPTIC_CURVE_POINT                = 0x0031U,

    ecy_hsm_SSS_FUNC_SERVICE_DERIVE_KEY                                 = 0x0032U,

    ecy_hsm_SSS_FUNC_SERVICE_DH_INIT                                    = 0x0033U,
    ecy_hsm_SSS_FUNC_SERVICE_DH_COMPUTE_INT                             = 0x0034U,
    ecy_hsm_SSS_FUNC_SERVICE_DH_COMPUTE_EXT                             = 0x0035U,

    ecy_hsm_SSS_FUNC_SERVICE_ASSERT_SESSION_PRIVILEGE                   = 0x0036U,
    ecy_hsm_SSS_FUNC_SERVICE_GETPASSWORD_FROM_DFLASH                    = 0x0037U,
    ecy_hsm_SSS_FUNC_SERVICE_DEACTIVATE_HSM                             = 0x0038U,
    ecy_hsm_SSS_FUNC_SERVICE_RTMD_CHECK                                 = 0x0039U,
    ecy_hsm_SSS_FUNC_SERVICE_SOFT_DEACTIVATE_HSM                        = 0x003AU,
    ecy_hsm_SSS_FUNC_SERVICE_GET_LIFECYCLE_STATE                        = 0x003BU,
    ecy_hsm_SSS_FUNC_SERVICE_CALC_HASH                                  = 0x003CU,
    ecy_hsm_SSS_FUNC_SERVICE_READ_KEY                                   = 0x003DU,

    ecy_hsm_SSS_FUNC_PRESERVE_KEY                                       = 0x0040U,
    ecy_hsm_SSS_FUNC_LOAD_KEY                                           = 0x0041U,
    /* Leave space 0x0040U - 0x004FU free */

    ecy_hsm_SSS_FUNC_SERVICE_MAC_GENERATE                               = 0x0050U,
    ecy_hsm_SSS_FUNC_SERVICE_MAC_GENERATE_START                         = 0x0051U,
    ecy_hsm_SSS_FUNC_SERVICE_MAC_GENERATE_UPDATE                        = 0x0052U,
    ecy_hsm_SSS_FUNC_SERVICE_MAC_GENERATE_FINISH                        = 0x0053U,
    ecy_hsm_SSS_FUNC_SERVICE_MAC_VERIFY                                 = 0x0054U,
    ecy_hsm_SSS_FUNC_SERVICE_MAC_VERIFY_START                           = 0x0055U,
    ecy_hsm_SSS_FUNC_SERVICE_MAC_VERIFY_UPDATE                          = 0x0056U,
    ecy_hsm_SSS_FUNC_SERVICE_MAC_VERIFY_FINISH                          = 0x0057U,
    /* Leave some space for bulk and safe mac operations */

    ecy_hsm_SSS_FUNC_SERVICE_RANDOM_GENERATE                            = 0x0060U,

    ecy_hsm_SSS_FUNC_SERVICE_JTAG_UNLOCK_HOST                           = 0x0064U,

    ecy_hsm_SSS_FUNC_SERVICE_READ_TB_SW_PART_INFO_BASED_INDEX           = 0x0070U,

    ecy_hsm_SSS_FUNC_SERVICE_SECLOG_READ_EXT_LOG                        = 0x0071U,

    /* To ensure backward compatibility issues, the Seclog Read Ext Log instruction has been replaced with
       the read log based on user request bit. This change allows for the use of these instructions in other
       use cases as well in future. As a result, the same enum value is used to maintain consistency.
    */
    ecy_hsm_SSS_FUNC_SERVICE_SECLOG_READ_USER_REQUESTBIT                = ecy_hsm_SSS_FUNC_SERVICE_SECLOG_READ_EXT_LOG,

    ecy_hsm_SSS_FUNC_SERVICE_SECLOG_HISTORY_STATUS                      = 0x0072U,

    /* To ensure backward compatibility issues, the Seclog Ext update history status instruction has been replaced with
       the Seclog update status based on user request bit. This change allows for the use of these instructions for to
       update the any other bit as well according to the use case. As a result, the same enum value is used to maintain
       consistency.
    */
    ecy_hsm_SSS_FUNC_SERVICE_SECLOG_UPDATE_EVENT_STATUS_USER_REQ_BIT    = ecy_hsm_SSS_FUNC_SERVICE_SECLOG_HISTORY_STATUS,

    ecy_hsm_SSS_FUNC_SERVICE_SECLOG_GET_EVENT_INFO                      = 0x0073U,

    ecy_hsm_SSS_FUNC_SERVICE_SECLOG_READ_LOGENTRIES                     = 0x0074U,

    /* ... to be continued ... */

    /* Get maximum of function Ids for LUT */
    ecy_hsm_SSS_FUNC_MAX
} ecy_hsm_SssFunctionT;
/* clang-format on */

/** Instruction code typedef to be used in structure definitions to ensure 16 bits are used */
typedef uint16 ecy_hsm_Sss_U16_FunctionT;

/**
 * @brief VM error information
 */
typedef struct ecy_hsm_Sss_ErrorInfoTag
{
    ecy_hsm_Csai_ErrorT vmError;      /**< Internal VM error code */
    ecy_hsm_Csai_ErrorT serviceError; /**< Internal service error code */
} ecy_hsm_Sss_ErrorInfoT;

/**
 * @brief VM instruction information
 */
typedef struct ecy_hsm_Sss_InstructionInfoTag
{
    uint32                    bytecodeOffset;  /**< Last executed instruction bytecode offset */
    ecy_hsm_Sss_U16_FunctionT instructionCode; /**< Last executed instruction code */
    uint16                    reserved;        /**< Padding */
} ecy_hsm_Sss_InstructionInfoT;

/**
 * @brief State of the error handler execution
 */
typedef enum ecy_hsm_Sss_ErrorHandlerStateTag
{
    ecy_hsm_SSS_ERR_HANDLER_NOT_STARTED,     /**< Error handler was not started */
    ecy_hsm_SSS_ERR_HANDLER_STARTED_FAIL,    /**< Error handler was started, but not finished due to a fatal error */
    ecy_hsm_SSS_ERR_HANDLER_FINISHED_FAIL,   /**< One or more instructions in the error handler failed, but it run until the end */
    ecy_hsm_SSS_ERR_HANDLER_FINISHED_SUCCESS /**< All error handler instructions executed successfully */
} ecy_hsm_Sss_ErrorHandlerStateT;

/**
 * @brief Info about the error handler execution
 */
typedef struct ecy_hsm_Sss_CleanUpInfoTag
{
    ecy_hsm_Sss_ErrorHandlerStateT errorHandlerState;     /**< Indicates whether error handler was run and if so, its outcome */
    ecy_hsm_Csai_ErrorT            autoCleanupError;      /**< Error code indicating the auto-cleanup outcome */
    ecy_hsm_Sss_InstructionInfoT   failedInstructionInfo; /**< Info about the first failed instruction in the error handler.
                                                               Can be used for error diagnostic if errorHandlerState is
                                                               @ref ecy_hsm_SSS_ERR_HANDLER_STARTED_FAIL or
                                                               @ref ecy_hsm_SSS_ERR_HANDLER_FINISHED_FAIL */
    ecy_hsm_Sss_ErrorInfoT errorInfo;                     /**< Info about the first encountered failure in the error handler.
                                                               Can be used for error diagnostic if errorHandlerState is
                                                               @ref ecy_hsm_SSS_ERR_HANDLER_STARTED_FAIL or
                                                               @ref ecy_hsm_SSS_ERR_HANDLER_FINISHED_FAIL */
} ecy_hsm_Sss_CleanUpInfoT;

/**
 * @brief Structure for reporting SSS errors and VM status
 */
typedef struct ecy_hsm_Csai_Sss_StatusInfoTag
{
    ecy_hsm_Sss_VmStateT         vmState;         /**< VM state: ecy_hsm_SSS_VM_IDLE, ecy_hsm_SSS_VM_WAITING ... */
    ecy_hsm_Sss_ErrorInfoT       errorInfo;       /**< Error information */
    ecy_hsm_Sss_InstructionInfoT instructionInfo; /**< Last executed instruction info */
    ecy_hsm_Sss_CleanUpInfoT     cleanUpInfo;     /**< Information about the cleanup (error handler execution and automatic cleanup) */
    uint16                       waitCode;        /**< Parameter value of the last executed WAIT instruction */
    uint16                       reserved;        /**< Padding */
} ecy_hsm_Csai_Sss_StatusInfoT;

/**
 * @brief Definition of a single script input
 */
typedef struct ecy_hsm_Csai_Sss_ScriptInputTag
{
    uint32 inputIndex; /**< Script input index */
    uint32 inputValue; /**< Script input value */
} ecy_hsm_Csai_Sss_ScriptInputT;

/* *** exported interfaces ********************************************************************/

/* *INDENT-OFF* */
# ifdef __cplusplus
extern "C" {
# endif
/* *INDENT-ON* */

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
# define ECY_HSM_START_SEC_CODE
# include "ecy_hsm_MemMap.h"

/**
 * [$DD 1856]
 * [$Satisfies $SW_ARCH 257595AA]
 * @brief Initialize a script for execution in a VM
 *
 * @param[in]   hSession        Handle to an open HSM session
 * @param[in]   priority        Scheduling priority of the operation on the HSM
 * @param[in]   scriptId        Script identifier. Available script IDs can be found in ecy_hsm_csai_vms_pub_sss.h
 * @param[out]  phJob           Receives the job handle of the initialized job
 * @param[in]   pParam          Pointer to type specific parameter structure. (Not used. Left for future extensions)
 * @param[in]   paramSize       Size of pParam structure in Bytes.
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                The call succeeded.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_Sss_ScriptInit(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                        ecy_hsm_Csai_JobPriorityT   priority,
                                                                                        uint32                      scriptId,
                                                                                        ecy_hsm_Csai_JobHandleT*    phJob,
                                                                                        void*                       pParam,
                                                                                        const uint32                paramSize);

/**
 * [$DD 1857]
 * [$Satisfies $SW_ARCH 4F643B6C]
 * @brief Sets script input parameters in a bulk fashion
 *
 * @param[in]   hSession            Handle to an open HSM session
 * @param[in]   priority            Scheduling priority of the operation on the HSM
 * @param[in]   pScriptInput        Pointer to an array with input parameters for the script
 * @param[in]   scriptInputCount    Number of script input parameters
 * @param[out]  phJob               Receives the job handle of the initialized job
 * @param[in]   pParam              Pointer to type specific parameter structure. (Not used. Left for future extensions)
 * @param[in]   paramSize           Size of pParam structure in Bytes.
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                The call succeeded.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_Sss_SetScriptInputs(ecy_hsm_Csai_SessionHandleT          hSession,
                                                                                             ecy_hsm_Csai_JobPriorityT            priority,
                                                                                             const ecy_hsm_Csai_Sss_ScriptInputT* pScriptInput,
                                                                                             const uint32                         scriptInputCount,
                                                                                             ecy_hsm_Csai_JobHandleT*             phJob,
                                                                                             void*                                pParam,
                                                                                             const uint32                         paramSize);
/**
 * [$DD 1858]
 * [$Satisfies $SW_ARCH 196B1AE6]
 * @brief Run the previously initialized script
 *
 * @note Can be invoked to start a script or to continue a running script if the state is @ref ecy_hsm_SSS_VM_WAITING
 *
 * @param[in]   hSession        Handle to an open HSM session
 * @param[in]   priority        Scheduling priority of the operation on the HSM
 * @param[out]  pStatusInfo     Receives the VM status info (including error status)
 * @param[out]  phJob           Receives the job handle of the initialized job
 * @param[in]   pParam          Pointer to type specific parameter structure. (Not used. Left for future extensions)
 * @param[in]   paramSize       Size of pParam structure in Bytes.
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS
 *  - @ref ecy_hsm_CSAI_ERR_SSS_END_OF_BYTECODE
 *  - @ref ecy_hsm_CSAI_ERR_SSS_VM_INSTRUCTION_ERROR
 *  - @ref ecy_hsm_CSAI_ERR_SSS_INVALID_INSTRUCTION_CODE
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_Sss_RunScript(ecy_hsm_Csai_SessionHandleT   hSession,
                                                                                       ecy_hsm_Csai_JobPriorityT     priority,
                                                                                       ecy_hsm_Csai_Sss_StatusInfoT* pStatusInfo,
                                                                                       ecy_hsm_Csai_JobHandleT*      phJob,
                                                                                       void*                         pParam,
                                                                                       const uint32                  paramSize);

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
# define ECY_HSM_STOP_SEC_CODE
# include "ecy_hsm_MemMap.h"

/* *INDENT-OFF* */
# ifdef __cplusplus
} /* extern "C" */
# endif
/* *INDENT-ON* */

/**
 * @}
 */
#endif /* ECY_HSM_CSAI_SSS_H */

/**
 * @endcond
 */
