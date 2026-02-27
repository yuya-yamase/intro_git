
/**
 * @file
 ***********************************************************************************************
 * @brief Applet Interface
 * @details Interface structures for each applet implementation
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2014, all rights reserved
 **********************************************************************************************/


#ifndef ECY_HSM_APPLET_H
#define ECY_HSM_APPLET_H

/** define symbol for usage of applets */
#define APPLET_USED

/*
**********************************************************************************************************************
* Includes
**********************************************************************************************************************
*/
#include "Platform_Types.h"
#include "ecy_hsm_csai.h"
#include "ecy_hsm_service.h"


/**
 * @addtogroup APPLET
 * @{
 */

/*
**********************************************************************************************************************
* Defines/Macros
**********************************************************************************************************************
*/
#if !defined(CPU_BYTE_ORDER)
#error CPU endianess is not defined. Please set CPU_BYTE_ORDER accordingly.
#endif

/** state indication of terminated */
#define APPLET_STATE_TERMINATED   ((uint8)0xFFU)

/** number of bytes to represent the authenticated User Id */
#define APPLET_USER_ID_BYTES (4U)

/** @deprecated: Wrapper macro to remove APPLET and operation flags from generated errors.
 *               Can only be removed with a breaking change release. */
#define CSAI_ERR(_err)   ((_err) & ~(ecy_hsm_CSAI_ERR_FLAG_APPLET | ecy_hsm_CSAI_OP_FLAG_MASK))

/** Priority flags
 *  priority_flags_u8 field shall contain a bit mask of all allowed priorities which my be used for applet execution
 * */
#define APPLET_PRIO_BACKGROUND_FLAG  ((uint8)(1u << (uint8)ecy_hsm_CSAI_PRIO_BACKGROUND))
#define APPLET_PRIO_LOW_FLAG         ((uint8)(1u << (uint8)ecy_hsm_CSAI_PRIO_LOW))
#define APPLET_PRIO_MEDIUM_FLAG      ((uint8)(1u << (uint8)ecy_hsm_CSAI_PRIO_MEDIUM))
#define APPLET_PRIO_HIGH_FLAG        ((uint8)(1u << (uint8)ecy_hsm_CSAI_PRIO_HIGH))
#define APPLET_PRIO_SAFETY_FLAG      ((uint8)(1u << (uint8)ecy_hsm_CSAI_PRIO_SAFETY))

/** Wrapper macro to convert CSAI priority to a field */
#define CONVERT_CSAI2APPLETPRIO(_prio) ((uint8)(1u <<(_prio)))

#define APPLET_OPT_MULTI_INST   ((uint8)(1u << (uint8)APPLET_OPTION_MULTI_INST_E))

/**
 * Option IDs for applet execution
 */
typedef enum
{
     /** Allow usage of multiple instances of this applet */
    APPLET_OPTION_MULTI_INST_E
    // ...
    // currently limited to max 8 options
} Applet_Option_IdT;


/**
 * Privilege IDs for applet execution
 */
typedef enum
{
    APPLET_PRIVILEGE_SECFLASH_E = 0,        /**< Allow Secure flashing operations */
    APPLET_PRIVILEGE_LC_USER_E,             /**< Allow user lifecycle changes */
    APPLET_PRIVILEGE_LC_PRIV_E,             /**< Allow privileged lifecycle changes */
    APPLET_PRIVILEGE_SECDBG_HSM_E,          /**< Allow HSM Debugging */
    APPLET_PRIVILEGE_DELETE_TB_ENTRY_E,     /**< Allow deletion of TB Entry */
    APPLET_PRIVILEGE_SECDEACT_HSM_E,        /**< Allow deactivation of HSM */
    // ...
    // currently limited to max 8 privileges
} Applet_Privilege_IdT;

/**
 * Convenience macro to build privilege bit-masks for applet usage
 * @param _privilegeId privilege ID for which to get bit mask
 * @return corresponding bit mask for specified privilege ID
 */
#define PRIVILEGE( _privilegeId ) ( 1UL << (uint8)(_privilegeId) )

/**
 * Convenience macro to build 8-bit sequence bit-masks for applet usage
 * @param _state state to be masked in
 * @return corresponding bit mask for specified _state
 */
#define STEP_U8( _state ) (1U << (uint8)(_state))

/**
 * Convenience macro to build 16-bit sequence bit-masks for applet usage
 * @param _state state to be masked in
 * @return corresponding bit mask for specified _state
 */
#define STEP_U16( _state ) ((uint16)1U << (uint8)(_state))

/**
 * Convenience macro to build 32-bit sequence bit-masks for applet usage
 * @param _state state to be masked in
 * @return corresponding bit mask for specified _state
 */
#define STEP_U32( _state ) (1UL << (uint8)(_state))

/**
 * Convenience macro to check sequence bit-masks for applet usage
 * @param _val bit masked variable to be checked
 * @param _state state to be checked for
 * @return TRUE if step is needed (bit is set), otherwise FALSE
 */
#define CHECKSTEP( _val, _state) (( (_val) & (STEP_U32(_state))) != 0UL)

/**
 * Macro to define a applet function
 * @param _applet ID of applet to be used @ref Applet_Id
 * @param _function ID of the applet's functions/state to be requested
 */
#if(CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
#define APPFUNC_ID(_applet, _function) { { (uint16)(_applet), (uint16)(_function) } }
#else
#define APPFUNC_ID(_applet, _function) { { (uint16)(_function), (uint16)(_applet) } }
#endif //(CPU_BYTE_ORDER == HIGH_BYTE_FIRST)

/*
**********************************************************************************************************************
* Type definitions
**********************************************************************************************************************
*/

/** Applet manager job state */
typedef HSM_PortStatusT Applet_JobStateT;
/** Applet execution error state @see ecy_hsm_Csai_ErrorT */
typedef ecy_hsm_Csai_ErrorT     Applet_ErrorStateT;

/**
 * @brief Applet return type
 *
 * @details
 * The return type contains state of the job handling, and error code of the job execution.
 * The error code of job execution is valid only after job is finished
 */
typedef struct Applet_ReturnTypeT
{
    Applet_JobStateT    stJob;      /**< Applet job handler state */
    Applet_ErrorStateT  stError;    /**< Applet job execution error code */
} Applet_ReturnTypeT;

/**
 * Type wrappers for Applet namespace
 */

/** Applet session handle @see ecy_hsm_Csai_SessionHandleT */
typedef ecy_hsm_Csai_SessionHandleT Applet_SessionT;
/** Applet Job handle @see ecy_hsm_Csai_JobHandleT */
typedef ecy_hsm_Csai_JobHandleT Applet_JobHandleT;
/** Applet priority is a bit field where the n-th bit is set if ecy_hsm_Csai_JobPriorityT is n @see ecy_hsm_Csai_JobPriorityT */
typedef ecy_hsm_Csai_JobPriorityT Applet_PriorityT;

/**
 * @brief Identification of an applet function
 * This union is used to allow mixed operation between applet - and legacy proxy interface
 *
 * If the @ref appletId (which is the high significant 16-bit word) is set != 0 it triggers
 * applet operation, otherwise the legacy proxy mechanism is used.
 */
/* PRQA S 0750 2 */ /* <Deviation: definition of union is appropriate here */
typedef union Applet_FunctionT
{
    struct
    {
#if(CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
        uint16   appletId;       /**< ID of Applet */
        uint16   functionId;     /**< ID of function/state within applet */
#else
        uint16   functionId;     /**< ID of function/state within applet */
        uint16   appletId;       /**< ID of Applet */
#endif
    } Applet;                    /**< Applet function ID (for applet usage) */
    HSM_FunctionT HSM_FuncId;    /**< HSM function ID (for compatibility with Proxy) */
} Applet_FunctionT;

/**
 * @brief Applet manager context data
 */
typedef struct AppletCtx_st {
    Applet_FunctionT appState;          /**< current applet state */
    uint8 priority_flags_u8;            /**< Priority */
    uint8 privileges_u8;                /**< privilege bits of last authentication */
    uint8 data_u8;                      /**< Applet specific data (modes, switches, etc.) */
    uint8 _reserved1;                   /**< reserved for future use (to keep 32 bit aligned) */
    uint8 userId[APPLET_USER_ID_BYTES]; /**< user id of last authentication */
# if (APPLET_TEST_JOBTIME_PROFILE == ENABLED)
    uint32 hostStartTime_u32;           /**< Applet start time (host) */
    uint32 hsmStartTime_u32;            /**< Applet start time (HSM) */
    uint32 hsmEndTime_u32;              /**< Applet finish time (HSM) */
# endif
# if (APPLET_TEST_PROFILE == ENABLED)
    uint32 hostEndTime_u32;             /**< Applet finish time (HOST) */
    uint32 jobDurationMax_u32;          /**< maximum job duration */
    uint32 funcSel_u32;                 /**< function selection */
    uint32 beforeExecuteCheckTime_u32;  /**< Check time before execution */
    uint32 afterExecuteCheckTime_u32;   /**< Check time after execution */
    uint32 beforeExecuteTime_u32;       /**< Time befor execution */
    uint32 afterExecuteTime_u32;        /**< Time after execution */
# endif
} AppletCtx_st;

/******************************************************************************
 * @anchor APPLET_FUNCTION_TEMPLATES
 * @name   Applet Function template type definitions
 * @brief  Function templates to be implemented with each applet
 ******************************************************************************/



/**
 * @brief Function to check applet priority
 *
 * @details
 * Implementations of this function template shall check,
 * if the requested priority is allowed
 *
 * @note Null pointer checks of the input functions have already been performed.
 *
 * @param pPriority requested priority
 * @param appFunc requested function/state of the applet
 * @param pParamBlock Operation parameters block
 *
 * @return
 *      ecy_hsm_CSAI_SUCCESS                  if requested priority OK
 *      ecy_hsm_CSAI_ERR_NOT_IMPLEMENTED      if applet not found
 *      ecy_hsm_CSAI_ERR_PRIORITY_NOT_ALLOWED if requested priority is not supported by applet or function
 *
 */
typedef Applet_ErrorStateT (*Applet_isPriorityOk_tf)( ecy_hsm_Csai_JobPriorityT *pPriority,
                                                      Applet_FunctionT appFunc,
                                                      const uint8 *pParamBlock );

/**
 * @brief Applet state transition check function - template
 *
 * @details
 * Implementations of this function template shall check, if the requested state transition is allowed
 *
 * @note Null pointer checks of the input functions have already been performed.
 *
 * @relates Applet_ts
 *
 * @param ctx_cpv   Pointer to applet instance context data
 * @param state     current state/function of applet instance
 * @param function  requested state/function of applet instance
 *
 * @return ecy_hsm_CSAI_SUCCESS if transition is allowed, otherwise error state of transition check
 *
 */
typedef Applet_ErrorStateT (*Applet_TransitionCheck_tf)( void * const ctx_cpv,
                                                         uint8 const state,
                                                         uint8 const function );

/**
 * @brief Applet Parameter Check - Check input parameters - template
 *
 * @details
 * Implementations of this function shall check all input parameters for the requested
 * function call
 *
 * @note Null pointer checks of the input functions have already been performed.
 *
 * @relates Applet_ts
 *
 * @param ctx_cpv   Pointer to applet instance context data
 * @param func_cu8  requested state/function of applet instance
 *
 * @return Result code of function execution @ref Applet_ReturnTypeT
 */
typedef Applet_ReturnTypeT (*Applet_ParamCheck_tf)( void * const ctx_cpv,
                                                    uint8 const func_cu8 );

/**
 * @brief Applet execution dispatch function - template
 *
 * @details
 * Implementations of this function template shall dispatch the requested function ID to
 * call the corresponding middleware function
 *
 * @note Null pointer checks of the input functions have already been performed.
 *
 * @relates Applet_ts
 *
 * @param hSession  handle to current session
 * @param ctx_cpv   Pointer to applet instance context data
 * @param func_cu8  requested state/function of applet instance
 *
 * @return Result code of function execution @ref Applet_ReturnTypeT
 *
 */
typedef Applet_ReturnTypeT (*Applet_Execution_tf)( Applet_SessionT hSession,
                                                   void * const ctx_cpv,
                                                   uint8 const func_cu8 );

/**
 * @brief Applet initialisation function - template pointer
 *
 * @details
 * Implementations of this function template shall allocate and initialize all resources
 * required for the applet functionality
 *
 * @note Null pointer checks of the input functions have already been performed.
 *
 * @relates Applet_ts
 *
 * @param ctx_cpv   Pointer to applet instance context data
 * @param func_cu8  requested state/function of applet instance
 *
 * @return Result code of function execution @ref Applet_ErrorStateT
 *
 */
typedef Applet_ErrorStateT (*Applet_Initialization_tf)( void * const ctx_cpv,
                                                        uint8 const func_cu8 );


/**
 * @brief Applet_xxx_Cleanup - Applet cleanup function - template pointer
 *
 * @details
 * Implementations of this function template shall clean up and release all resources
 * required for the applet functionality
 *
 * @note Null pointer checks of the input functions have already been performed.
 *
 * @relates Applet_ts
 *
 * @param ctx_cpv   Pointer to applet instance context data
 *
 */
typedef void (*Applet_Cleanup_tf)( void * const ctx_cpv );



/**
 * @brief Applet state execution function - template pointer
 *
 * @details
 * Applets need to implement a execution function for each defined state of the applet
 *
 * @note Null pointer checks of the input functions have already been performed.
 *
 * @relates Applet_ts
 *
 * @param ctx_cpv   Pointer to applet instance context data
 *
 * @return Result code of function execution @ref Applet_ReturnTypeT
 *
 */
typedef Applet_ReturnTypeT (*Applet_StateExecution_tf)( void * const ctx_cpv );

/**
 * @brief Generic applet state check function to check the specified state for certain conditions
 *
 * @details
 * Applets need to implement this for check of initial state, or final state ...
 *
 * @note Null pointer checks of the input functions have already been performed.
 *
 * @relates Applet_ts
 *
 * @param state to be checked
 *
 * @return boolean true if state fulfills requirement, otherwise false
 */
typedef boolean (*Applet_StateCheck_tf)( uint8 state );

/**
 * @brief Applet control data structure
 *
 * @details
 * This Interface has to be implemented and provided by each applet
 */
typedef struct Applet_ts {
    uint8 id_u8;             /**< Applet ID */
    uint8 numStates_u8;      /**< Maximum number of states */
    uint8 priority_flags_u8; /**< bit mask of all allowed priorities which may be used */
    uint8 options_u8;        /**< Only one instance of this applet type allowed */

    /**
     * @details
     * Implementations of this function template shall check,
     * if the requested priority is allowed
     *
     * @nullable:
     * Set to @ref NULL_PTR if no priority check per applet function is required.
     *
     *
     * @param priority  requested priority
     * @param appFunc   requested function/state of the applet or NULL_PTR if no priority check per applet function is required.
     *
     * @return
     *      ecy_hsm_CSAI_SUCCESS                  if requested priority OK
     *      ecy_hsm_CSAI_ERR_NOT_IMPLEMENTED      if applet not found
     *      ecy_hsm_CSAI_ERR_PRIORITY_NOT_ALLOWED if requested priority is not supported by applet or function
     *
     */
    Applet_isPriorityOk_tf isPriorityOk_pf; /**< Transition allowed check */

    /**
     * @brief Function to check if given state is applet's initial state
     *
     * @details
     * This check is used to decide if the applet need to perform initialisation, or not
     *
     * @param state to be checked
     *
     * @return boolean TRUE if state fulfills requirement, otherwise FALSE
     */
    Applet_StateCheck_tf isInitialState_pf; /**< Check if applet initial state */

    /**
     * @brief Function to check if given state is applet's final state
     *
     * @details
     * This check is used to decide if the applet need to perform finalization, or not
     *
     * @param state to be checked
     *
     * @return boolean TRUE if state fulfills requirement, otherwise FALSE
     */
    Applet_StateCheck_tf isFinalState_pf; /**< Check if applet final state */

    /**
     * @brief Function to check applet state transition
     *
     * @details
     * Implementations of this function template shall check,
     * if the requested state transition is allowed
     *
     * @param ctx_cpv   Pointer to applet instance context data
     * @param state     current state/function of applet instance
     * @param function  requested state/function of applet instance
     *
     * @return boolean TRUE if state transition is allowed, otherwise FALSE
     *
     */
    Applet_TransitionCheck_tf isTransitionOk_pf; /**< Transition allowed check */

    /**
     * @brief Function for applet initialisation
     *
     * @details
     * Implementations of this function template shall allocate and initialize all resources
     * required for the applet functionality
     *
     * @param ctx_cpv   Pointer to applet instance context data
     * @param func_cu8  requested state/function of applet instance
     *
     * @return Result code of function execution @ref Applet_ErrorStateT
     *
     */
    Applet_Initialization_tf Init_pf; /**< Initialisation function */

    /**
     * @brief Function for applet cleanup
     *
     * @details
     * Implementations of this function template shall clean up and release all resources
     * required for the applet functionality
     *
     * @param ctx_cpv   Pointer to applet instance context data
     *
     */
    Applet_Cleanup_tf Cleanup_pf; /**< Cleanup function */

    /**
     * @brief Function to check input parameters
     *
     * @details
     * Implementations of this function shall check all input parameters for the requested function call
     *
     * @param ctx_cpv   Pointer to applet instance context data
     * @param func_cu8  requested state/function of applet instance
     *
     * @return Result code of function execution @ref Applet_ReturnTypeT
     */
    Applet_ParamCheck_tf ParamCheck_pf; /**< Parameter check */

    /**
     * @brief Function to dispatch applet execution
     *
     * @details
     * Implementations of this function shall dispatch the requested function to execute the
     * corresponding middleware functions.
     *
     * @param hSession  handle to current session
     * @param ctx_cpv   Pointer to applet instance context data
     * @param func_cu8  requested state/function of applet instance
     *
     * @return Result code of function execution @ref Applet_ReturnTypeT
     *
     */
    Applet_Execution_tf Execute_pf; /**< Execution dispatcher function */
} Applet_ts;



/**
 * @brief ID's for each @ref applet
 */
typedef enum Applet_Id
{
    APPLET_ID_NONE = 0           /**< No applet selected (used for mixed operation with legacy proxy calls) */
    ,APPLET_ID_SYSTEM             /**< System functions applet (sessions/jobs ...) */
    ,APPLET_ID_MOCK               /**< MOCK testing applet */
    ,APPLET_ID_HASH               /**< HASH applet */
    ,APPLET_ID_MACGEN             /**< MAC generation applet */
    ,APPLET_ID_MAC_VERIFY         /**< MAC verification applet */
    ,APPLET_ID_SIGN_VERIFY        /**< Signature verification applet */
    ,APPLET_ID_SECACC             /**< Security access applet */
    ,APPLET_ID_SECFLASH           /**< Secure flash programming applet */
    ,APPLET_ID_CHKSUM             /**< ChkSum applet */
    ,APPLET_ID_CERT               /**< Cert applet */
    ,APPLET_ID_RNG                /**< RNG applet */
    ,APPLET_ID_SIGN_GENERATE      /**< Signature generation applet */
    ,APPLET_ID_ASYM_ENCRYPT       /**< Asymmetric encryption applet */
    ,APPLET_ID_ASYM_DECRYPT       /**< Asymmetric decryption applet */
    ,APPLET_ID_SECURESTORAGE      /**< Data applet */
    ,APPLET_ID_SYM_DECRYPT        /**< Symmetric decryption */
    ,APPLET_ID_SYM_ENCRYPT        /**< Symmetric encryption */
    ,APPLET_ID_DH                 /**< ECC DH applet */
    ,APPLET_ID_KEYS               /**< Keys applet */
    ,APPLET_ID_SHE                /**< She applet */
    ,APPLET_ID_TB                 /**< Trusted Boot applet */
    ,APPLET_ID_LIFECYCLE          /**< Lifecycle applet */
    ,APPLET_ID_PROTECTIONS        /**< Protections applet */
    ,APPLET_ID_VKMS               /**< VKMS applet */
    ,APPLET_ID_KEY_EXCHANGE       /**< Key exchange applet */
    ,APPLET_ID_WFS                /**< WFS applet */
    ,APPLET_ID_SECLOG             /**< Secure Logging applet */
    ,APPLET_ID_CR                 /**< Generic Challenge response applet */
    ,APPLET_ID_DIAGNOSTICS        /**< Hsm Diagnostics applet */
    ,APPLET_ID_MDK                /**< MDK applet */
    ,APPLET_ID_SSS                /**< Secure Space Scripting (SSS) applet */
    ,APPLET_ID_VKMS3              /**< VKMS3 applet */
    ,APPLET_ID_HWCSP              /**< HwCsp applet */
    ,APPLET_ID_GHSM               /**< GHSM applet */
    ,APPLET_ID_TPM                /**< Trusted Platform Module applet */
    /* @important:
     * Please add new applet ID's only to the end of this list
     * to ensure backward compatibility.
     * For any new applet ID also add a NULL_PTR to the initialisation
     * of ecy_hsm_AppletList_cas in ecy_hsm_applet_cfg.c
    */

    /* following entry must be the last entry of enum */
    ,APPLET_ID_MAXNUM_APPLETS     /**< MAX number of known applets */
}Applet_Id;

/**
 * @}
 */

#endif /* ECY_HSM_APPLET_H */
