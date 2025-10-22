/**
 * @file
 ***********************************************************************************************
 * @brief Functions and data structures for the host communication with the HSM Bridge Registers
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2014, all rights reserved
 **********************************************************************************************/

#include "ecy_hsm_host_proxy.h"
#include "ecy_hsm_basicsrvs.h"
#include "ecy_hsm_csai_trusted_boot.h"
#include "ecy_hsm_host_mcal.h"
#include "ecy_hsm_ipcdrv.h"
#include "ecy_hsm_proxy.h"
#include "ecy_hsm_sessions_params.h"
#include "ecy_hsm_timing_diagnostics.h"
#if (ecy_hsm_HOST_STORAGE == ENABLED)
#include "ecy_hsm_host_storage.h"
#include "ecy_hsm_host_storage_internal.h"
#endif /* #if (ecy_hsm_HOST_STORAGE == ENABLED) */

#if defined(GUAM) && defined (TEST_GROUP_NO_WAIT_MODE_OPEN_SESSION)
#include "test_no_wait_mode.h"
#endif /* #if defined(GUAM) && defined (TEST_GROUP_NO_WAIT_MODE_OPEN_SESSION) */

#if defined(GUAM) && defined (TEST_GROUP_CSAI_WAITMODE_SESSION)
#include "test_csai_session.h"
#endif /* #if defined(GUAM) && defined (TEST_GROUP_CSAI_SESSION) */

/* To avoid the Guam specific file includes*/
#if defined(GUAM)
#include "ecy_hsm_general.h"
#else
#include "ecy_hsm_general_pubcfg.h"
#endif

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_VAR_HSMSHARED_CLEARED_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/* mirror in RAM for the trusted boot results.
 * Version information of table will be used for an handshake to exchange the possible size of the mirror table between HSM and Host */
static volatile ecy_hsm_Host_TB_VerifTableT verifTableMirror;

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_VAR_HSMSHARED_CLEARED_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_VAR_HSMSHARED_INIT_32
#include "ecy_hsm_MemMap.h"

/*The number of elements in the trusted boot table on HSM side*/
static volatile uint32 verifTableMaxNumOfElementsHSM = ecy_hsm_CSAI_TB_REF_TABLE_SIZE_LEGACY;
/* PRQA S 5087 2 */ /* include is necessary here since the location of the ram mirror of TB result has to be guaranteed */
#define ECY_HSM_STOP_SEC_VAR_HSMSHARED_INIT_32
#include "ecy_hsm_MemMap.h"

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_VAR_HSMSHARED_INIT_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

#if defined(GUAM) && (HSM_INJECT_TEST == ENABLED) && (BUILD_TYPE == DEBUG)
/** In test mode the bridge should be directly accessible from other modules, to be able
to bypass the CSAI interface and write directly to it. Used to implement attack scenarios
in which the host is compromised */
volatile HSM_HostSideBridgePortT host2HSM_BridgePorts[CYCURHSM_SC_MAX_HOST_HSM_SESSIONS] = {{HSM_STATUS_IDLE, 0U, 0U, {HSM_FUNC_NONE}}};
HSM_HostSideOpParamsT            opParams                                                = {HSM_FUNC_NONE, ecy_hsm_CSAI_PRIO_BACKGROUND, 0U, {0U}};
#else
/** The host side array of bridge ports, host and HSM both write and read */
/* All write accesses to this should be protected by OsResource_HsmBridge   */
/* PRQA S 0686 1 */ /* Justification: further array elements will be initialized to 0 */
static volatile HSM_HostSideBridgePortT host2HSM_BridgePorts[CYCURHSM_SC_MAX_HOST_HSM_SESSIONS] = {{HSM_STATUS_IDLE, 0U, 0U, {HSM_FUNC_NONE}}};

/** The host side shared RAM for operation parameters  */
/** @details Only the host writes to this but placed in special section to protect against corruption by RAM checking function   */
static HSM_HostSideOpParamsT opParams = {HSM_FUNC_NONE, ecy_hsm_CSAI_PRIO_BACKGROUND, 0U, {0U}};
#endif

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_VAR_HSMSHARED_INIT_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

#if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED)

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_VAR_HSMSHARED_INIT_32
#include "ecy_hsm_MemMap.h"

/* Array with timestamp to detect timeout in job request */
static volatile uint32 host2HSM_BridgePortsTimeoutStamp[CYCURHSM_SC_MAX_HOST_HSM_SESSIONS] = {0UL};

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_VAR_HSMSHARED_INIT_32
#include "ecy_hsm_MemMap.h"

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_VAR_HSMSHARED_INIT_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/* array with current quick route status for different sessions */
/* PRQA S 0686 1 */ /* Justification: further array elements will be initialized to ecy_hsm_QR_STATUS_IDLE */
static volatile ecy_hsm_QuickRouteStatusT host2HSM_QuickRouteStatus[CYCURHSM_SC_MAX_HOST_HSM_SESSIONS] = {ecy_hsm_QR_STATUS_IDLE};

/* PRQA S 3218 4 */ /* Justification: Only one function makes use this variable to share data with HSM through shared memory. Hence this has to be
                       global and volatile. */
/* PRQA S 0686 1 */ /* Justification: further array elements will be initialized */
static volatile HSM_SessionOpenNoWaitModeT sessionOpenNoWaitMode[CYCURHSM_SC_MAX_HOST_HSM_SESSIONS] = {{(uint32) 0UL, (uint32) 0UL}};

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_VAR_HSMSHARED_INIT_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_VAR_HSMSHARED_CLEARED_8
#include "ecy_hsm_MemMap.h"

/* session specific mac generate buffer for quick route use case */
static uint8 hsm2hst_qmacBuffer[CYCURHSM_SC_MAX_HOST_HSM_SESSIONS][AES_BLOCK_SIZE_BYTES];

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_VAR_HSMSHARED_CLEARED_8
#include "ecy_hsm_MemMap.h"

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_VAR_HSMSHARED_CLEARED_8
#include "ecy_hsm_MemMap.h"
/* PRQA S 3218 6 */ /* Justification: Only one function makes use of this variable to share data with the HSM through shared memory.
                                      Hence this has to be global and volatile. */
/* Counter to read from the intermediate buffer for open session incase of no wait mode is enabled */
static volatile uint8 openSessionReadIdxNoWaitMode ;
/* Counter to write to the intermediate buffer for open session incase of no wait mode is enabled */
static volatile uint8 openSessionWriteIdxNoWaitMode;

/* Open session status incase of no wait mode is enabled */
static volatile boolean openSessionStatusNoWaitMode;

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_VAR_HSMSHARED_CLEARED_8
#include "ecy_hsm_MemMap.h"

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_VAR_HSMSHARED_INIT_32
#include "ecy_hsm_MemMap.h"

/* session specific mac verify buffer for quick route use case */
static uint32 hsm2hst_qmacResultFlagBuffer[CYCURHSM_SC_MAX_HOST_HSM_SESSIONS] = {0UL};

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_VAR_HSMSHARED_INIT_32
#include "ecy_hsm_MemMap.h"

#endif /* #if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED)*/

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_VAR_HSMSHARED_INIT_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/** The host side shared RAM for suspend operations parameters  */
static HSM_HostSideSuspendParamsT suspendOpParams = {HSM_SUSP_NONE, ecy_hsm_CSAI_SUCCESS, 0U, 0U};

/** The host side shared RAM for suspending HSM from writing to shared memory operations parameters */
/* PRQA S 3218 2 */ /* Justification: Only one function makes use this variable to share data with HSM through shared memory.
                        Hence this has to be global. */
static HSM_HostSideSuspendSharedRamParamsT suspendSharedRamOpParams = {ecy_hsm_CSAI_SUCCESS};

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_VAR_HSMSHARED_INIT_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_VAR_HSMSHARED_INIT_8
#include "ecy_hsm_MemMap.h"

/** CMAC buffer for the Quick CMAC shortcut function (generation only!), defining this here saves the requirement to range check a pointer during
 *  Quick CMAC execution, and means that the truncation is done on the host core which runs faster than the HSM. */
static uint8 qmacBuffer[AES_BLOCK_SIZE_BYTES] = {0U};

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_VAR_HSMSHARED_INIT_8
#include "ecy_hsm_MemMap.h"

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_VAR_HSMSHARED_INIT_32
#include "ecy_hsm_MemMap.h"
static uint32 resultFlagBuffer = 0U;

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_VAR_HSMSHARED_INIT_32
#include "ecy_hsm_MemMap.h"

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_CONST_32
#include "ecy_hsm_MemMap.h"
/**
 * Maximum number of sessions
 * The define can have different values over multiple configurations.
 * This parameter is used to unify the code to get a cleaner coverage report.
 */
static const uint32 maxHostHsmSessions = CYCURHSM_SC_MAX_HOST_HSM_SESSIONS;

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_CONST_32
#include "ecy_hsm_MemMap.h"

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_VAR_PTR
#include "ecy_hsm_MemMap.h"

/** Pointer to the GetResource() callout    */
static ecy_hsm_pFunctionGetResourceT pCalloutGetResource = NULL_PTR;

/** Pointer to the ReleaseResource() callout    */
static ecy_hsm_pFunctionReleaseResourceT pCalloutReleaseResource = NULL_PTR;

/** Pointer to the GetCounterValue() callout    */
static ecy_hsm_pFunctionGetCounterValueT ecy_hsm_pCalloutGetCounterValue = NULL_PTR;

/** Pointer to the GetElapsedCounterValue() callout    */
static ecy_hsm_pFunctionGetElapsedCounterValueT ecy_hsm_pCalloutGetElapsedCounterValue = NULL_PTR;

/** Pointer to any external callouts needed by external teams    */
static ecy_hsm_pFunctionExtendedCalloutsT ecy_hsm_pFunctionExtendedCallouts = NULL_PTR;

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_VAR_PTR
#include "ecy_hsm_MemMap.h"

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_VAR_INIT_8
#include "ecy_hsm_MemMap.h"

#if (ecy_hsm_ENABLE_RESOURCE_ERROR_HANDLING == ENABLED)
/** Variable holding the current resource state (locked/unlocked) */
static volatile boolean resourceIsLocked = FALSE;
#endif

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_VAR_INIT_8
#include "ecy_hsm_MemMap.h"

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_VAR_INIT_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

#if defined(TIMING_DIAGNOSTICS) && (TIMING_DIAGNOSTICS != DISABLED)
static ecy_hsm_DiagnosticsT diagnostics = {0, {0}, {0}};
#endif

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

#ifdef QACCHECK
#pragma PRQA_NO_SIDE_EFFECTS HSM_CheckHsmCoreStarted
#endif

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_VAR_HSMSHARED_INIT_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/* Declare the configuration variable as static to restrict the variable scope to file.   */
/* Otherwise the compiler uses the same memory space for the loop variable and things don't quite work...   */
/* Needs to be volatile to stop the compiler for optimizing the writes to it    */
/* PRQA S 3218 2 */ /* Justification: Only one function makes use this variable to share data with HSM through shared memory. Hence this has to be
                       global and volatile. */
static volatile HSM_BridgeConfigurationT bridgeConfiguration = {
    ecy_hsm_CSAI_ERR_UNDEFINED,
    0U,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
#if defined(TIMING_DIAGNOSTICS) && (TIMING_DIAGNOSTICS != DISABLED)
    &diagnostics,
#endif
};

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_VAR_HSMSHARED_INIT_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_VAR_HSMSHARED_CLEARED_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/* Needs to be static to restrict file scope    */
/* PRQA S 3218 2 */ /* Justification: Only one function makes use this variable to share data with HSM through shared memory. Hence this has to be
                       global and volatile. */
static volatile HSM_SessionOpenT sessionOpen;

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_VAR_HSMSHARED_CLEARED_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/* *** defines ********************************************************************************/
#if (ECY_HSM_VMS_ARCH_GROUP == ECY_HSM_VMS_ARCH_GROUP_CYPRESS_TRAVEO2)
#define ONE_BYTE_SHIFT               8UL          /* Value to be used to shift one byte */
#define CLOCK_DIVIDER_VALUE_BIT_MASK 0xFFUL       /* Bit mask for valid values for the clock dividers */
#define CLOCK_DIVIDER_TYPE_BIT_MASK  0x80000000UL /* Bit mask to indicate type of clock divider */
#endif                                            /* (ECY_HSM_VMS_ARCH_GROUP == ECY_HSM_VMS_ARCH_GROUP_CYPRESS_TRAVEO2)  */

/* *** function prototypes ********************************************************************/
/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

static ecy_hsm_Csai_ErrorT HSM_CheckHsmCoreStarted(void);
static ecy_hsm_Csai_ErrorT ecy_hsm_Mgmt_SuspendOpExec(uint32 numMsTimeout);

static ecy_hsm_Csai_ErrorT
LoadOp(ecy_hsm_Csai_JobHandleT hJob, ecy_hsm_Csai_JobPriorityT priority, HSM_FunctionT function, uint32 paramBlockSize, const void* pParamBlock);

static void HSM_Configure_MirrorTable(void);
static void HSM_Check_MirrorTable(void);

LOCAL_INLINE ecy_hsm_Csai_ErrorT
DoLoadOp(ecy_hsm_Csai_JobHandleT hJob, ecy_hsm_Csai_JobPriorityT priority, HSM_FunctionT function, uint32 paramBlockSize, const void* pParamBlock);

LOCAL_INLINE ecy_hsm_Csai_ErrorT ecy_HSM_DoQuickRoute(ecy_hsm_Csai_SessionHandleT hSession,
                                                      HSM_FunctionT               function,
                                                      uint32                      paramBlockSize,
                                                      void*                       pParamBlock,
                                                      ecy_hsm_Csai_JobHandleT*    phJob);

LOCAL_INLINE ecy_hsm_Csai_ErrorT ecy_HSM_DoQuickRoute_LoadOp(ecy_hsm_Csai_SessionHandleT hSession, ecy_hsm_Csai_JobHandleT* phJob);

/**
 * This function updates the variable @ref verifTableMaxNumOfElementsHSM which stores the current number of elements
 * in the trusted boot table on HSM side.
 *
 * @param[in] value                         new number of elements
 *
 */
static void ecy_hsm_TbSetVerifTableMaxNumOfElementsHSM(uint32 value);

#if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED)
/**
 * @brief This function is used to check the status of all jobs before opening new job session
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                The call succeeded.
 *  - @ref ecy_hsm_CSAI_FC_BUSY                Another job is still pending completion in this session.
 *  - @ref ecy_hsm_CSAI_ERR_HSM_SUSPENDED      If the HSM is in suspended mode
 *  - @ref ecy_hsm_CSAI_ERR_HSM2HTS_LOCKUP     If the HSM is in an undefined mode (possibly crashed)
 *
 */
LOCAL_INLINE ecy_hsm_Csai_ErrorT ecy_HSM_CheckOpenSessionAllowed(void);

/**
 * @brief This function checks if any of job are in TRANSMIT status
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS           The call succeeded.
 *  - @ref ecy_hsm_CSAI_FC_BUSY           Another job is still pending completion in this session.
 *
 */
LOCAL_INLINE ecy_hsm_Csai_ErrorT ecy_HSM_CheckJobTransmit(void);

/**
 * @brief This function is used to check if previously requested open session is completed
 *
 *  @param[in]  pTempWriteIdx           Pointer to store the write index if previous open session is completed.
 *                                      which shall be used to write to intermediate buffer.
 * @return
 *  - @ref ecy_hsm_CSAI_FC_BUSY         Previous open session job is still pending
 *  - @ref ecy_hsm_CSAI_SUCCESS         Previous open session is completed
 */
LOCAL_INLINE ecy_hsm_Csai_ErrorT ecy_HSM_CheckPreviousOpenSessionCompleted(uint8* pTempWriteIdx);

/**
 * @brief This function will get the resource lock and will check if a quickroute job is allowed
          (quickroute buffer and operation buffer unlocked). If not it will directly release the lock
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                                The call succeeded
 *  - @ref ecy_hsm_CSAI_ERR_QUICK_ROUTE_NOT_POSSIBLE           The HSM's internal state meant that the quick route could not be used
 *  - @ref ecy_hsm_CSAI_ERR_RESOURCE_ALREADY_LOCKED_UNLOCKED   The resource was already locked.
 *
 */
LOCAL_INLINE ecy_hsm_Csai_ErrorT ecy_HSM_CheckQuickRouteAllowed(void);

/**
 * @brief This function will set the Sessionbuffer to Transmit mode and lock the quickroute resource at quickroute jobs
 *
 * @param[in] hSession        Handle to the session in which the job is placed
 * @param[in] quickRouteMode  Quick route mode
 */
LOCAL_INLINE void ecy_hsm_QuickRouteSetSessionToTransmit(ecy_hsm_Csai_SessionHandleT hSession, HSM_FunctionT function);

/**
 * @brief This function sets the corresponding Job status for QuickRoute operations
 *
 * @param[in] hSession   Handle to the session in which the job is placed
 * @param[in] qrStatus   Quick route status
 **/
LOCAL_INLINE void ecy_hsm_setQuickRouteStatus(ecy_hsm_Csai_SessionHandleT hSession, ecy_hsm_QuickRouteStatusT qrStatus);

/**
 * @brief This function will copy the QuickRoute operation results into its respective global buffers based on the operation
 * NOTE: Make sure that the resource is locked before calling this function and later released
 *
 * @param[in] hSession   Handle to the session in which the job is placed
 *
 **/
LOCAL_INLINE void ecy_hsm_copyQuickRouteResult(ecy_hsm_Csai_SessionHandleT hSession);

/**
 * @brief This function is used to check the status of job before sending a CSAI job request to HSM
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                          The call succeeded
 *  - @ref ecy_hsm_CSAI_FC_BUSY                          Another job is still pending completion in this session.
 *  - @ref ecy_hsm_CSAI_ERR_HSM_SUSPENDED                The HSM is in suspended mode
 *  - @ref ecy_hsm_CSAI_ERR_SWITCHING_FROM_CORE_TO_BOOT  The HSM transitions from core to bootloader in order to remain there. Requesting a new job from the host will fail as long as the booting was not finished.
 *  - @ref ecy_hsm_CSAI_ERR_HSM2HTS_LOCKUP               The HSM is not in expected state.
 **/
LOCAL_INLINE ecy_hsm_Csai_ErrorT ecy_HSM_CheckLoadJobAllowed(void);

/**
 * @brief This function is used to check the open session status
 *
 * @param[in] releaseResource                  Shall be passed TRUE to release resource else FALSE.
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                Open session job is completed
 *  - @ref ecy_hsm_CSAI_FC_BUSY                Open session job is still pending
 *
 */
LOCAL_INLINE ecy_hsm_Csai_ErrorT ecy_HSM_CheckOpenSessionCompleted(boolean releaseResource);

#endif /* #if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED)*/

/**
 * Wait for the HSM to perform a reset.
 *
 * @param[in] delay Milliseconds to wait
 *
 * @returns @ref ecy_hsm_CSAI_SUCCESS           If Ok.
 * @returns @ref ecy_hsm_CSAI_ERR_TIMEOUT       The HSM did not clear the reset flag
 *                                              within the specified timeout.
 * @returns @ref ecy_hsm_CSAI_ERR_NULL_CALLOUT  At least one of the callouts @ref ecy_hsm_pCalloutGetCounterValue
 *                                              or @ref ecy_hsm_pCalloutGetElapsedCounterValue is not set.
 */
static ecy_hsm_Csai_ErrorT ecy_HSM_WaitForReset(uint32 timeout);

/* *** public implementation  *****************************************************************/
/* [$Satisfies $DD 1017] */
/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_Proxy */
ecy_hsm_Csai_ErrorT ecy_HSM_ConfigureCallouts(ecy_hsm_pFunctionGetResourceT            pFunctionGetResource,
                                              ecy_hsm_pFunctionReleaseResourceT        pFunctionReleaseResource,
                                              ecy_hsm_pFunctionGetCounterValueT        pFunctionGetCounterValue,
                                              ecy_hsm_pFunctionGetElapsedCounterValueT pFunctionGetElapsedCounterValue)
{
    ecy_hsm_Csai_ErrorT errorCode = ecy_hsm_CSAI_SUCCESS;
    if ((NULL_PTR == pFunctionGetCounterValue) || (NULL_PTR == pFunctionGetElapsedCounterValue))
    {
        errorCode = ecy_hsm_CSAI_ERR_INVALID_PARAM;
    }
    else
    {
        /* pFunctionGetResource and  pFunctionReleaseResource can be a NULL_PTR as long as they are both a NULL_PTR */
        /* If only one of them is a NULL_PTR the errorCode is set to ecy_hsm_CSAI_ERR_INVALID_PARAM */
        if ((pFunctionGetResource != pFunctionReleaseResource) && ((NULL_PTR == pFunctionGetResource) || (NULL_PTR == pFunctionReleaseResource)))
        {
            errorCode = ecy_hsm_CSAI_ERR_INVALID_PARAM;
        }
        else
        {
            pCalloutGetResource                    = pFunctionGetResource;
            pCalloutReleaseResource                = pFunctionReleaseResource;
            ecy_hsm_pCalloutGetCounterValue        = pFunctionGetCounterValue;
            ecy_hsm_pCalloutGetElapsedCounterValue = pFunctionGetElapsedCounterValue;
        }
    }
    return (errorCode);
}

/* [$Satisfies $DD 1744] */
/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_Proxy */
ecy_hsm_Csai_ErrorT ecy_HSM_ConfigureExtendedCallouts(ecy_hsm_pFunctionExtendedCalloutsT     pFunctionExtendedCallouts,
                                                      ecy_HSM_configureExtendedCalloutsTypeT configureExtendedCalloutsType)
{
    ecy_hsm_Csai_ErrorT errorCode = ecy_hsm_CSAI_SUCCESS;

    if (pFunctionExtendedCallouts != NULL_PTR)
    {
        switch (configureExtendedCalloutsType)
        {
            case ECY_HSM_PFUNCTION_IRQ_HANDLINGT:
                ecy_hsm_pFunctionExtendedCallouts = pFunctionExtendedCallouts;
                break;

            default:
                errorCode = ecy_hsm_CSAI_ERR_INVALID_PARAM;
                break;
        }
    }
    else
    {
        errorCode = ecy_hsm_CSAI_ERR_INVALID_PARAM;
    }
    return (errorCode);
}

void ecy_hsm_FunctionIRQHandling(void)
{
    /* Get access to the HSM Bridge */
    if (ecy_hsm_pFunctionExtendedCallouts != NULL_PTR)
    {
        ecy_hsm_pFunctionExtendedCallouts();
    }
}

/* [$Satisfies $DD 1018]*/
/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_Proxy */
uint32 ecy_HSM_GetCoreErrorFlags(void)
{
    return (ecy_hsm_HsmMCAL_GetCoreErrorFlags());
}

/* [$Satisfies $DD 1409] */
/* PRQA S 1503 3 */ /* <Deviation: rule_2.1_1503_Proxy */
ecy_hsm_Csai_ErrorT ecy_hsm_GetCoreAppStatus(void)
{
    ecy_hsm_Csai_ErrorT errorCode;
    uint32              returnValue;

    returnValue = ecy_hsm_IpcDrv_GetHsmStatus();

    if ((HSM2HTS_BOOTED | HSM2HTS_CORE_APP) == (returnValue & (HSM2HTS_BOOTED | HSM2HTS_CORE_APP)))
    {
        errorCode = ecy_hsm_CSAI_SUCCESS;
    }
    else if (HSM2HTS_ERR_CMAC == (returnValue & HSM2HTS_ERR_CMAC))
    {
        errorCode = ecy_hsm_CSAI_ERR_CORE_INVALID;
    }
    else if (HSM2HTS_BOOTED == (returnValue & HSM2HTS_BOOTED))
    {
        errorCode = ecy_hsm_CSAI_ERR_CORE_PRESENT_INTEGRITY_NOT_CHECKED;
    }
    else
    {
        errorCode = ecy_hsm_CSAI_ERR_CORE_NOT_VERIFIED;
    }

    return (errorCode);
}

/* PRQA S 1503 2 */ /* Deviation: rule_2.1_1503_Proxy */
/* PRQA S 1505 1 */ /* <Deviation: This function is part of the public API and can therefore not be declared static. */
HSM_ModeT ecy_HSM_GetMode(void)
{
    return (ecy_hsm_HsmMCAL_GetMode());
}

/* [$Satisfies $DD 1024] */
/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_Proxy */
ecy_hsm_Csai_ErrorT ecy_HSM_Reset(HSM_ModeT expectedMode, uint32 timeout)
{
    ecy_hsm_Csai_ErrorT errorCode;
#if (COMPILER == COMPILER_TASKING)
/* Suppress TASKING compiler warning about errorCode being always SUCCESS, since the errorCode can change based on feature switches */
#pragma warning 549
#endif
    /* Get access to the HSM Bridge */
    errorCode = ecy_HSM_GetBridgeResource();

    /* PRQA S 2995, 2991 1 */ /* <Deviation: control flow depends on defines */
    if (ecy_hsm_CSAI_SUCCESS == errorCode)
#if (COMPILER == COMPILER_TASKING)
#pragma warning restore
#endif
    {
        /* Trigger the reset of the HSM */
        (void)ecy_hsm_HsmMCAL_SoftReset();

        /* Wait until the reset is done or a timeout is triggered */
        errorCode = ecy_HSM_WaitForReset(timeout);

        if (ecy_hsm_CSAI_SUCCESS == errorCode)
        {
            errorCode = ecy_HSM_WaitForBooted(timeout);
            if (ecy_hsm_CSAI_SUCCESS == errorCode)
            {
                (void)ecy_hsm_HsmMCAL_Release();
                errorCode = ecy_HSM_WaitForMode(expectedMode, timeout);
            }
        }
    }

    /* Release access to the HSM Bridge */
    ecy_HSM_RELEASE_BRIDGE_PORT(errorCode)

    return (errorCode);
}

static ecy_hsm_Csai_ErrorT ecy_HSM_WaitForReset(uint32 timeout)
{
    ecy_hsm_Csai_ErrorT errorCode;
    boolean             isResetDone   = FALSE;
    uint32              startingValue = (uint32) 0UL;
    uint32              elapsedValue  = (uint32) 0UL;

    timeout = timeout * ecy_hsm_COUNTER_VALUE_TIMEBASE;

    /* get point in time when request was made */
    errorCode = ecy_HSM_GetCounterValue(&startingValue);

    /* check if everything was fine so far */
    if (ecy_hsm_CSAI_SUCCESS == errorCode)
    {
        /* wait until reset is done or timeout is reached */
        do
        {
            ecy_hsm_FunctionIRQHandling();
            /* get elapsed time since request was made */
            errorCode = ecy_HSM_GetElapsedCounterValue(startingValue, &elapsedValue);
            if (ecy_hsm_CSAI_SUCCESS == errorCode)
            {
                isResetDone = ecy_hsm_HsmMCAL_IsResetAcknowledged();
            }
        }
        while ((FALSE == isResetDone) && (ecy_hsm_CSAI_SUCCESS == errorCode) && (timeout > elapsedValue));

        if ((ecy_hsm_CSAI_SUCCESS == errorCode) && (timeout <= elapsedValue))
        {
            errorCode = ecy_hsm_CSAI_ERR_TIMEOUT;
        }
    }

    return errorCode;
}

/* [$Satisfies $DD 1022] */
/* PRQA S 1503 2 */ /* Deviation: rule_2.1_1503_Proxy */
/* PRQA S 1505 1 */ /* <Deviation: This function is part of the public API and can therefore not be declared static. */
ecy_hsm_Csai_ErrorT ecy_HSM_WaitForBooted(uint32 timeout)
{
    ecy_hsm_Csai_ErrorT errorCode;
    HSM_ModeT           mode          = HSM_MODE_NOT_STARTED;
    uint32              startingValue = 0U;
    uint32              elapsedValue  = 0U;

    errorCode = ecy_HSM_GetCounterValue(&startingValue);

    timeout = timeout * ecy_hsm_COUNTER_VALUE_TIMEBASE;

    if (ecy_hsm_CSAI_SUCCESS == errorCode)
    {
        do
        {
            ecy_hsm_FunctionIRQHandling();
            errorCode = ecy_HSM_GetElapsedCounterValue(startingValue, &elapsedValue);
            if (ecy_hsm_CSAI_SUCCESS == errorCode)
            {
                mode = ecy_hsm_HsmMCAL_GetMode();
            }
        }
        while ((HSM_MODE_NOT_STARTED == mode) && (ecy_hsm_CSAI_SUCCESS == errorCode) && (timeout > elapsedValue));

        if ((ecy_hsm_CSAI_SUCCESS == errorCode) && (timeout <= elapsedValue))
        {
            errorCode = ecy_hsm_CSAI_ERR_TIMEOUT;
        }
    }
    return (errorCode);
}

/* [$Satisfies $DD 1023] */
/* PRQA S 1503 2 */ /* Deviation: rule_2.1_1503_Proxy */
/* PRQA S 1505 1 */ /* <Deviation: This function is part of the public API and can therefore not be declared static. */
ecy_hsm_Csai_ErrorT ecy_HSM_WaitForMode(HSM_ModeT mode, uint32 timeout)
{
    ecy_hsm_Csai_ErrorT errorCode;
    HSM_ModeT           currentMode   = HSM_MODE_RESERVED;
    uint32              startingValue = 0U;
    uint32              elapsedValue  = 0U;

    timeout = timeout * ecy_hsm_COUNTER_VALUE_TIMEBASE;

    errorCode = ecy_HSM_GetCounterValue(&startingValue);
    if (ecy_hsm_CSAI_SUCCESS == errorCode)
    {
        do
        {
            ecy_hsm_FunctionIRQHandling();
            errorCode = ecy_HSM_GetElapsedCounterValue(startingValue, &elapsedValue);
            if (ecy_hsm_CSAI_SUCCESS == errorCode)
            {
                currentMode = ecy_hsm_HsmMCAL_GetMode();
            }
        }
        while ((mode != currentMode) && (ecy_hsm_CSAI_SUCCESS == errorCode) && (timeout > elapsedValue));

        if ((ecy_hsm_CSAI_SUCCESS == errorCode) && (timeout <= elapsedValue))
        {
            errorCode = ecy_hsm_CSAI_ERR_TIMEOUT;
        }
    }
    return (errorCode);
}

#if (ecy_hsm_WAIT_FOR_MODE_WATCH_DOG == ENABLED)
/* PRQA S 1503 2 */ /* Deviation: rule_2.1_1503_Proxy */
/* PRQA S 1505 1 */ /* Deviation: This function is part of the public API and can therefore not be declared static. */
ecy_hsm_Csai_ErrorT ecy_HSM_WaitForModeWD(HSM_ModeT mode, CSAI_WatchdogFunctionT watchdog, void* pParam, uint32 timeout)
{
    ecy_hsm_Csai_ErrorT errorCode;
    HSM_ModeT           currentMode   = HSM_MODE_RESERVED;
    uint32              startingValue = (uint32) 0UL;
    uint32              elapsedValue  = (uint32) 0UL;
    uint32              abrt;

    timeout   = timeout * ecy_hsm_COUNTER_VALUE_TIMEBASE;
    errorCode = ecy_HSM_GetCounterValue(&startingValue);
    if (ecy_hsm_CSAI_SUCCESS == errorCode)
    {
        do
        {
            ecy_hsm_FunctionIRQHandling();
            if (NULL_PTR != watchdog)
            {
                abrt = watchdog(pParam);

                if (0UL != abrt)
                {
                    errorCode = ecy_hsm_CSAI_ERR_CRASH;
                }
            }
            if (ecy_hsm_CSAI_SUCCESS == errorCode)
            {
                errorCode = ecy_HSM_GetElapsedCounterValue(startingValue, &elapsedValue);
            }
            if (ecy_hsm_CSAI_SUCCESS == errorCode)
            {
                currentMode = ecy_hsm_HsmMCAL_GetMode();
            }
        }
        while ((mode != currentMode) && (ecy_hsm_CSAI_SUCCESS == errorCode) && (timeout > elapsedValue));

        if ((ecy_hsm_CSAI_SUCCESS == errorCode) && (timeout <= elapsedValue))
        {
            errorCode = ecy_hsm_CSAI_ERR_TIMEOUT;
        }
    }
    return (errorCode);
}
#endif /* ecy_hsm_WAIT_FOR_MODE_WATCH_DOG == ENABLED */

#if 0 /* not used now, but keep for future purpose */
static boolean HSM_IsBootloaderRunning(void);
static boolean HSM_IsBootloaderRunning(void)
{
    boolean isBootloaderRunning = FALSE;

    HSM_ModeT currentMode = ecy_hsm_HsmMCAL_GetMode();

    if(HSM_MODE_BOOTLOADER == currentMode)
    {
        isBootloaderRunning = TRUE;
    }

    return isBootloaderRunning;
}
#endif

/* [$Satisfies $DD 1021] */
/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_Proxy */
ecy_hsm_Csai_ErrorT ecy_HSM_ClockConfigure(uint32 divider)
{
    ecy_hsm_Csai_ErrorT errorCode;
    uint32              startingValue;
    uint32              elapsedValue;
    boolean             configSuccess = FALSE;

    /* As long as the BOOTED flag is set then the HSM can accept clock configuration commands    */
    if (HSM_MODE_NOT_STARTED == ecy_HSM_GetMode())
    {
        errorCode = ecy_hsm_CSAI_ERR_HSM_NOT_STARTED;
    }
    else if ((NULL_PTR == ecy_hsm_pCalloutGetCounterValue) || (NULL_PTR == ecy_hsm_pCalloutGetElapsedCounterValue))
    {
        errorCode = ecy_hsm_CSAI_ERR_NULL_CALLOUT;
    }
    else
    {
#if (COMPILER == COMPILER_TASKING)
/* Suppress TASKING compiler warning about errorCode being always SUCCESS, since the errorCode can change based on feature switches */
#pragma warning 549
#endif
        /* Get access to the HSM Bridge */
        errorCode = ecy_HSM_GetBridgeResource();
        /* PRQA S 2995, 2991 1 */ /* <Deviation: control flow depends on defines */
        if (ecy_hsm_CSAI_SUCCESS == errorCode)
#if (COMPILER == COMPILER_TASKING)
#pragma warning restore
#endif
        {
#if (ECY_HSM_VMS_ARCH_GROUP == ECY_HSM_VMS_ARCH_GROUP_CYPRESS_TRAVEO2)
            if (divider > 0xFFUL)
            {
                errorCode = ecy_hsm_CSAI_ERR_INVALID_PARAM;
            }
            else
            {
                /* Use the lowest byte as the slow clock divider */
                divider = (uint32)(divider & CLOCK_DIVIDER_VALUE_BIT_MASK);
                /* Trigger the clock configuration  */
                errorCode = ecy_hsm_HsmMCAL_ClockConfigure(divider);
            }
#else
            /* Trigger the clock configuration  */
            errorCode = ecy_hsm_HsmMCAL_ClockConfigure(divider);
#endif /* (ECY_HSM_VMS_ARCH_GROUP == ECY_HSM_VMS_ARCH_GROUP_CYPRESS_TRAVEO2) */

            /* PRQA S 2991,2995 1 */ /*Deviation: rule_14.3_Check_Target_Specific */
            if (ecy_hsm_CSAI_SUCCESS == errorCode)
            {

                /* Wait for response */
                ecy_hsm_pCalloutGetCounterValue(&startingValue);

                /* wait until the HSM is configured and has acknowledged the configuration request*/
                do
                {
                    /* We check first for acknowledged, since the HSM could still be configured from a previous call.
                     * This will be reset on HSM side previous to acknowledging the request. */
                    /* PRQA S 3415 1 */ /* <Deviation: rule_13.5_1> */
                    if ((TRUE == ecy_hsm_IsClockConfigure_Acknowledged()) && (TRUE == ecy_hsm_HsmMCAL_IsClockConfigured()))
                    {
                        configSuccess = TRUE;
                    }
                    ecy_hsm_pCalloutGetElapsedCounterValue(startingValue, &elapsedValue);
                }
                while ((FALSE == configSuccess) && (elapsedValue < ecy_HSM_CONFIGURATION_DELAY));

                /* if the timeout occurred and the HSM has not acknowledged or is set to configured then return error */
                if ((FALSE == configSuccess))
                {
                    errorCode = ecy_hsm_CSAI_ERR_TIMEOUT;
                }
            }
            /* Release the bridge ports */
            ecy_HSM_RELEASE_BRIDGE_PORT(errorCode)
        }
    }
    return (errorCode);

} /* PRQA S 6009 1 */ /* Justification: 5 nested levels are acceptable here, maintenance is not affected. Warning was introduced by adding a
                         NULL_PTR-check; complete refactoring is not plausible.*/

/* [$Satisfies $DD 2980] */
/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_Proxy */
ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_HSM_SuspendSharedRamWrite(void)
{
    ecy_hsm_Csai_ErrorT errorCode;
    uint32              startingValue;
    uint32              elapsedValue;
    boolean             IsSuspendSuccess = FALSE;

    errorCode = HSM_CheckHsmCoreStarted();

    if (errorCode == ecy_hsm_CSAI_SUCCESS)
    {
        if ((NULL_PTR == ecy_hsm_pCalloutGetCounterValue) || (NULL_PTR == ecy_hsm_pCalloutGetElapsedCounterValue))
        {
            errorCode = ecy_hsm_CSAI_ERR_NULL_CALLOUT;
        }
        else
        {
#if (COMPILER == COMPILER_TASKING)
/* Suppress TASKING compiler warning about errorCode being always SUCCESS, since the errorCode can change based on feature switches */
#pragma warning 549
#endif
            /* Get access to the HSM Bridge */
            errorCode = ecy_HSM_GetBridgeResource();
            /* PRQA S 2995, 2991 1 */ /* <Deviation: control flow depends on defines */
            if (ecy_hsm_CSAI_SUCCESS == errorCode)
#if (COMPILER == COMPILER_TASKING)
#pragma warning restore
#endif
            {
                /* Trigger the HSM suspend write to shared memory */
                ecy_hsm_HsmMCAL_SuspendSharedRamWrite(&suspendSharedRamOpParams);

                /* Wait for response */
                ecy_hsm_pCalloutGetCounterValue(&startingValue);

                /* wait until the shared memory write is suspended and has acknowledged the suspend write to shared memory request */
                do
                {
                    /* We check first for acknowledged, since the HSM could still be configured from a previous call.
                     * This will be reset on HSM side previous to acknowledging the request. */
                    /* PRQA S 3415 1 */ /* <Deviation: rule_13.5_1> */
                    if ((TRUE == ecy_hsm_IsSuspendSharedRamWrite_Acknowledged()) && (TRUE == ecy_hsm_HsmMCAL_IsSuspendedSharedRamWrite()))
                    {
                        IsSuspendSuccess = TRUE;
                    }
                    ecy_hsm_pCalloutGetElapsedCounterValue(startingValue, &elapsedValue);
                }
                while ((FALSE == IsSuspendSuccess) && (elapsedValue < ecy_HSM_CONFIGURATION_DELAY));

                if (FALSE == IsSuspendSuccess)
                {
                    /* override error code with timeout error */
                    suspendSharedRamOpParams.opErrorCode = ecy_hsm_CSAI_ERR_TIMEOUT;
                }

                errorCode = suspendSharedRamOpParams.opErrorCode;

                /* Release the bridge ports */
                ecy_HSM_RELEASE_BRIDGE_PORT(errorCode)
            }
        }
    }
    return (errorCode);
} /* PRQA S 6009 1 */ /* Justification:  Nested levels are acceptable here, maintenance is not affected */

/* [$Satisfies $DD 1637] */
/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_Proxy */
ecy_hsm_Csai_ErrorT ecy_HSM_PeriClockConfigure(uint32 divider)
{
#if (ECY_HSM_VMS_ARCH_GROUP == ECY_HSM_VMS_ARCH_GROUP_CYPRESS_TRAVEO2)
    ecy_hsm_Csai_ErrorT errorCode;
    uint32              startingValue;
    uint32              elapsedValue;
    boolean             configSuccess = FALSE;

    /* As long as the BOOTED flag is set then the HSM can accept clock configuration commands    */
    if (HSM_MODE_NOT_STARTED == ecy_HSM_GetMode())
    {
        errorCode = ecy_hsm_CSAI_ERR_HSM_NOT_STARTED;
    }
    else if ((NULL_PTR == ecy_hsm_pCalloutGetCounterValue) || (NULL_PTR == ecy_hsm_pCalloutGetElapsedCounterValue))
    {
        errorCode = ecy_hsm_CSAI_ERR_NULL_CALLOUT;
    }
    else
    {
#if (COMPILER == COMPILER_TASKING)
/* Suppress TASKING compiler warning about errorCode being always SUCCESS, since the errorCode can change based on feature switches */
#pragma warning 549
#endif
        /* Get access to the HSM Bridge */
        errorCode = ecy_HSM_GetBridgeResource();
        /* PRQA S 2995, 2991 1 */ /* <Deviation: control flow depends on defines */
        if (ecy_hsm_CSAI_SUCCESS == errorCode)
#if (COMPILER == COMPILER_TASKING)
#pragma warning restore
#endif
        {
            if (divider > 0xFFU)
            {
                errorCode = ecy_hsm_CSAI_ERR_INVALID_PARAM;
            }
            else
            {
                /* Use the second lowest byte as the peripheral clock divider */
                divider = (uint32)((divider & CLOCK_DIVIDER_VALUE_BIT_MASK) << ONE_BYTE_SHIFT);
                /* Use the highest bit to indicate that only the peripheral clock divider shall be set */
                divider = (uint32)(divider | CLOCK_DIVIDER_TYPE_BIT_MASK);

                /* Trigger the clock configuration  */
                errorCode = ecy_hsm_HsmMCAL_ClockConfigure(divider);
            }

            /* PRQA S 2991,2995 1 */ /*Deviation: rule_14.3_Check_Target_Specific */
            if (ecy_hsm_CSAI_SUCCESS == errorCode)
            {

                /* Wait for response */
                ecy_hsm_pCalloutGetCounterValue(&startingValue);

                /* wait until the HSM is configured and has acknowledged the configuration request*/
                do
                {
                    /* We check first for acknowledged, since the HSM could still be configured from a previous call.
                     * This will be reset on HSM side previous to acknowledging the request. */
                    /* PRQA S 3415 1 */ /* <Deviation: rule_13.5_1> */
                    if ((TRUE == ecy_hsm_IsClockConfigure_Acknowledged()) && (TRUE == ecy_hsm_HsmMCAL_IsClockConfigured()))
                    {
                        configSuccess = TRUE;
                    }
                    ecy_hsm_pCalloutGetElapsedCounterValue(startingValue, &elapsedValue);
                }
                while ((FALSE == configSuccess) && (elapsedValue < ecy_HSM_CONFIGURATION_DELAY));

                /* if the timeout occurred and the HSM has not acknowledged or is set to configured then return error */
                if ((FALSE == configSuccess))
                {
                    errorCode = ecy_hsm_CSAI_ERR_TIMEOUT;
                }
            }

            /* Release the bridge ports */
            ecy_HSM_RELEASE_BRIDGE_PORT(errorCode)
        }
    }
#else
    ecy_hsm_Csai_ErrorT errorCode = ecy_hsm_CSAI_ERR_NOT_SUPPORTED;
    CSAI_PARAM_UNUSED(divider);
#endif /* (ECY_HSM_VMS_ARCH_GROUP != ECY_HSM_VMS_ARCH_GROUP_CYPRESS_TRAVEO2) */

    return errorCode;
} /* PRQA S 6009 1 */ /* Justification: 5 nested levels are acceptable here, maintenance is not affected. Warning was introduced by adding a
                         NULL_PTR-check; complete refactoring is not plausible.*/

#if (ecy_hsm_HOST_STORAGE == ENABLED)

/* [$Satisfies $DD 1215] [$Satisfies $DD 2520] */
/* PRQA S 1503 1 */ /* <Deviation: rule_2.1_1503_Proxy */ /* Justification: Public API function */
ecy_hsm_Csai_ErrorT ecy_HSM_HostStorageConfigure(void)
{
    ecy_hsm_Csai_ErrorT errorCode = ecy_hsm_CSAI_SUCCESS;
    boolean             configSuccess;
    uint32              startTime;
    uint32              elapsedTime;

    if (HSM_MODE_NOT_STARTED == ecy_HSM_GetMode())
    {
        /* HSM must be booted */
        errorCode = ecy_hsm_CSAI_ERR_HSM_NOT_STARTED;
    }
    else if ((NULL_PTR == ecy_hsm_pCalloutGetCounterValue) || (NULL_PTR == ecy_hsm_pCalloutGetElapsedCounterValue))
    {
        /* CycurHSM counter callout(s) must be registered */
        errorCode = ecy_hsm_CSAI_ERR_NULL_CALLOUT;
    }
    else if (FALSE == ecy_hsm_HostStorage_IsInitialized())
    {
        /* The state of the host storage cache is invalid */
        errorCode = ecy_hsm_CSAI_ERR_HOST_STORAGE_STATE_INVALID;
    }
    else
    {
#if (COMPILER == COMPILER_TASKING)
/* Suppress TASKING compiler warning about errorCode being always SUCCESS, since the errorCode can change based on feature switches */
#pragma warning 549
#endif
        /* Get access to the HSM Bridge */
        errorCode = ecy_HSM_GetBridgeResource();
        /* PRQA S 2995, 2991 1 */ /* <Deviation: control flow depends on defines */
        if (ecy_hsm_CSAI_SUCCESS == errorCode)
#if (COMPILER == COMPILER_TASKING)
#pragma warning restore
#endif
        {
            volatile HSM_HostStorageCacheT* pTempCache = ecy_hsm_HostStorage_GetCachePtr();

            /* Put the memory address of the cache on the HT2HSM status register */
            /* PRQA S 0303 2 */ /* <Justification: The location of the host storage cache must
            sent to the HSM and a conversion of the pointer to uint32 does not affect functionality */
            ecy_hsm_IpcDrv_SetStatus(ALL_FLAGS_ON, (uint32)pTempCache);

            /* Trigger a host storage config event */
            ecy_hsm_IpcDrv_SendEvents(HT2HSMF_HOST_STORAGE_CONFIG);

            /* Get the start counter */
            ecy_hsm_pCalloutGetCounterValue(&startTime);

            /* Wait until the event is acknowledged or a timeout occurs */
            do
            {
                configSuccess = ecy_hsm_IsHostStorageConfigure_Acknowledged();

                /* Update the elapsed counter */
                ecy_hsm_pCalloutGetElapsedCounterValue(startTime, &elapsedTime);
            }
            while ((FALSE == configSuccess) && (elapsedTime < ecy_HSM_CONFIGURATION_DELAY));

            if ((FALSE == configSuccess))
            {
                /* a timeout occurred before the HSM acknowledged the event */
                errorCode = ecy_hsm_CSAI_ERR_TIMEOUT;
            }

            /* Release the bridge ports */
            ecy_HSM_RELEASE_BRIDGE_PORT(errorCode)
        }
    }

    return (errorCode);
}

#endif /* #if (ecy_hsm_HOST_STORAGE == ENABLED) */

/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_Proxy */
ecy_hsm_Csai_ErrorT ecy_HSM_Configure(uint8* errorMessageBuffer, uint32 errorMessageBufferLength)
{

    volatile ecy_hsm_Csai_ErrorT errorCode;
    uint32                       startingValue;
    uint32                       elapsedValue;
    boolean                      configSuccess = FALSE;

    errorCode = HSM_CheckHsmCoreStarted();

    if ((NULL_PTR == ecy_hsm_pCalloutGetCounterValue) || (NULL_PTR == ecy_hsm_pCalloutGetElapsedCounterValue))
    {
        errorCode = ecy_hsm_CSAI_ERR_NULL_CALLOUT;
    }

    /* only continue when the HSM is started and counter callouts are initialized*/
    if (errorCode == ecy_hsm_CSAI_SUCCESS)
    {
#if (COMPILER == COMPILER_TASKING)
/* Suppress TASKING compiler warning about errorCode being always SUCCESS, since the errorCode can change based on feature switches */
#pragma warning 549
#endif
        /* Get access to the HSM Bridge */
        errorCode = ecy_HSM_GetBridgeResource();
        /* PRQA S 2995, 2991 1 */ /* <Deviation: control flow depends on defines */
        if (ecy_hsm_CSAI_SUCCESS == errorCode)
#if (COMPILER == COMPILER_TASKING)
#pragma warning restore
#endif
        {
#if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED)
            uint32 nSession;
            /* For NXP target these variables are not loaded with initialized value at startup. Hence init is needed */
            openSessionWriteIdxNoWaitMode  = 0U;
            openSessionReadIdxNoWaitMode   = 0U;
            openSessionStatusNoWaitMode    = FALSE;

            for (nSession = 0; nSession < CYCURHSM_SC_MAX_HOST_HSM_SESSIONS; nSession++)
            {
                (void)ecy_memset(hsm2hst_qmacBuffer[nSession], 0u, AES_BLOCK_SIZE_BYTES);
            }
#endif
            HSM_Configure_MirrorTable();

            /* Setup data */

            bridgeConfiguration.errorCode = ecy_hsm_CSAI_ERR_UNDEFINED;
            if (errorMessageBuffer != NULL_PTR)
            {
                bridgeConfiguration.HSM_ErrorMessageBufferSize = errorMessageBufferLength;
                bridgeConfiguration.pHSM_ErrorMessage          = errorMessageBuffer;
            }
            else
            {
                bridgeConfiguration.HSM_ErrorMessageBufferSize = 0U;
                bridgeConfiguration.pHSM_ErrorMessage          = NULL_PTR;
            }
            bridgeConfiguration.pHostSideBridgePorts = host2HSM_BridgePorts;
            bridgeConfiguration.pOpParams            = &opParams;
            bridgeConfiguration.pQmacBuffer          = qmacBuffer;
            bridgeConfiguration.pResultFlag          = &resultFlagBuffer;
            bridgeConfiguration.pTBVerifTable        = &verifTableMirror;
#if defined(TIMING_DIAGNOSTICS) && (TIMING_DIAGNOSTICS != DISABLED)
            pDiagnostics                    = &diagnostics; /* Un-comment unless trying to doing timing analysis of startup  */
            bridgeConfiguration.diagnostics = pDiagnostics;
#endif

            /* Initializes the HSM2HT interrupt register
             * Interrupts are disabled after initializing
             */
            ecy_hsm_IpcDrv_Initialize();

            /* Trigger the configuration    */
            ecy_hsm_HsmMCAL_Configure(&bridgeConfiguration);

            /* Wait for response */
            ecy_hsm_pCalloutGetCounterValue(&startingValue);

            /* wait until the HSM is configured and has acknowledged the configuration request*/
            do
            {
                /* We check first for acknowledged, since the HSM could still be configured from a previous call.
                 * This will be reset on HSM side previous to acknowledging the request. */
                /* PRQA S 3415 1 */ /* <Deviation: rule_13.5_1> */
                if ((TRUE == ecy_hsm_IsConfigure_Acknowledged()) && (TRUE == ecy_hsm_HsmMCAL_IsConfigured()))
                {
                    configSuccess = TRUE;
                }

                /* Calculate elapsed time (for timeout) */
                ecy_hsm_pCalloutGetElapsedCounterValue(startingValue, &elapsedValue);
            }
            while ((FALSE == configSuccess) && (elapsedValue < ecy_HSM_CONFIGURATION_DELAY));

            /* if NOT configured within timeout AND no initial error is set
             * @note:
             * ecy_hsm_CSAI_SUCCESS is checked below to prevent a potential race
             * condition when timeout occurs, but status already set to
             * ecy_hsm_CSAI_SUCCESS by ecy_hsm_HsmMCAL_Configure().
             * => ecy_hsm_CSAI_ERR_TIMEOUT to be reported in this case */
            if ((FALSE == configSuccess)
                && ((ecy_hsm_CSAI_ERR_CRASH == bridgeConfiguration.errorCode) || (ecy_hsm_CSAI_SUCCESS == bridgeConfiguration.errorCode)))
            {
                /* override error code with timeout error */
                bridgeConfiguration.errorCode = ecy_hsm_CSAI_ERR_TIMEOUT;
            }
            HSM_Check_MirrorTable();

            /* Copy error code from static structure to a volatile (so compiler does not optimize).
             * Otherwise bridgeConfiguration.errorCode could be overridden by an preempting task after
             * the resource has been released. */
            errorCode = bridgeConfiguration.errorCode;

            /* Release the bridge ports */
            ecy_HSM_RELEASE_BRIDGE_PORT(errorCode)
        }
    }
    return (errorCode);
}

/* const because we don't want the user writing to the status word  */
/* volatile because the HSM core can change it  */
/* PRQA S 1532 2 */ /*  non optimal reference of this function is tested and does not hinder functionality */
/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_Proxy */
ecy_hsm_Csai_ErrorT ecy_HSM_GetSessionStatusPointer(const volatile HSM_PortStatusT** ppStatus, ecy_hsm_Csai_SessionHandleT hSession)
{
    ecy_hsm_Csai_ErrorT errorCode = HSM_CheckHsmCoreStarted();

    if ((ecy_hsm_CSAI_SUCCESS == errorCode) && (maxHostHsmSessions <= hSession))
    {
        errorCode = ecy_hsm_CSAI_ERR_PORT_OUT_OF_RANGE;
    }

    if ((NULL_PTR != ppStatus) && (errorCode == ecy_hsm_CSAI_SUCCESS))
    {
        *ppStatus = &host2HSM_BridgePorts[hSession].status;
    }

    return (errorCode);
}

/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_Proxy */
ecy_hsm_Csai_ErrorT ecy_HSM_GetSessionStatus(ecy_hsm_Csai_SessionHandleT hSession)
{
    ecy_hsm_Csai_ErrorT errorCode = HSM_CheckHsmCoreStarted();

    if (errorCode == ecy_hsm_CSAI_SUCCESS)
    {
        if (maxHostHsmSessions <= hSession)
        {
            errorCode = ecy_hsm_CSAI_ERR_PORT_OUT_OF_RANGE;
        }
        else
        {
            /* Don't need to lock OsResource_HsmBridge because we are only changing from COMPLETE to IDLE
             * and nothing else should change it until it is IDLE */
            if (HSM_STATUS_COMPLETE == host2HSM_BridgePorts[hSession].status)
            {
                /* If the operation has just completed, change the status to idle and report the operation's error code */
                errorCode                             = host2HSM_BridgePorts[hSession].opErrorCode;
                host2HSM_BridgePorts[hSession].status = HSM_STATUS_IDLE;
            }
            else if (HSM_STATUS_IDLE == host2HSM_BridgePorts[hSession].status)
            {
                /* If the operation is idle (effectively not pending or processing) then report the last operation's
                error code */
                errorCode = host2HSM_BridgePorts[hSession].opErrorCode;
            }
#if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED)
            else if (HSM_STATUS_TRANSMIT_JOB == host2HSM_BridgePorts[hSession].status)
            {
                uint32 elapsedValue;
                errorCode = ecy_hsm_CSAI_FC_BUSY;
                if (NULL_PTR == ecy_hsm_pCalloutGetElapsedCounterValue)
                {
                    errorCode = ecy_hsm_CSAI_ERR_NULL_CALLOUT;
                }
                else
                {
                    ecy_hsm_pCalloutGetElapsedCounterValue(host2HSM_BridgePortsTimeoutStamp[hSession], &elapsedValue);
                    if (elapsedValue >= ecy_HSM_PROXY_DELAY)
                    {
                        errorCode                             = host2HSM_BridgePorts[hSession].opErrorCode;
                        host2HSM_BridgePorts[hSession].status = HSM_STATUS_IDLE;
                    }
                }
            }
#endif /* #if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED)*/
            else
            {
                /* Must be busy */
                errorCode = ecy_hsm_CSAI_FC_BUSY;
            }
        }
    }
    return (errorCode);
} /* PRQA S 6009 */ /*< Justification: The if-statement exceeding the limit doesn't make this function less readable. Refactoring due to HIS metric
                       LEVEL is not sensible. */

/* PRQA S 3238 10 */ /* Justification: LOCAL_INLINE is declared as 'static inline', function has NO external linkage. */
#if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED)
LOCAL_INLINE ecy_hsm_Csai_ErrorT ecy_HSM_CheckJobTransmit(void)
{
    ecy_hsm_Csai_ErrorT errorCode = ecy_hsm_CSAI_SUCCESS;
    uint32              jobSlot;
    for (jobSlot = (uint32) 0UL; jobSlot < maxHostHsmSessions; jobSlot++)
    {
        if (HSM_STATUS_TRANSMIT_JOB == host2HSM_BridgePorts[jobSlot].status)
        {
            /* one of the job slots has TRANSMIT status */
            errorCode = ecy_hsm_CSAI_FC_BUSY;
            break;
        }
    }
    return errorCode;
}

/* PRQA S 3238 22 */ /* Justification: LOCAL_INLINE is declared as 'static inline', function has NO external linkage. */
LOCAL_INLINE ecy_hsm_Csai_ErrorT ecy_HSM_CheckOpenSessionAllowed(void)
{
    ecy_hsm_Csai_ErrorT errorCode;
    uint32              startingValue;
    uint32              elapsedValue;
    boolean             bufferInUse;

    /* check if any session transmitting data at the moment.
     * depending on the configuration define wait to get the access to the transmission buffer. */
    ecy_hsm_pCalloutGetCounterValue(&startingValue);
    do
    {
        bufferInUse = FALSE;
        errorCode   = ecy_HSM_CheckJobTransmit();

        if (ecy_hsm_CSAI_FC_BUSY == errorCode)
        {
            bufferInUse = TRUE;
        }

        errorCode = HSM_CheckHsmCoreStarted();
        ecy_hsm_pCalloutGetElapsedCounterValue(startingValue, &elapsedValue);
#if ((ecy_hsm_NOWAIT_MODE_WAIT_WHEN_IN_TRANSMISSION == DISABLED) && (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED))
        /* Force Timeout if NOWAIT bridge mode is selected and POLL_AT_BUSY is disabled */
        break;
#endif
    }
    while ((bufferInUse == TRUE) && (errorCode == ecy_hsm_CSAI_SUCCESS) /* HSM Core App still running? */
           && (elapsedValue < ecy_hsm_NOWAIT_MODE_WAIT_WHEN_IN_TRANSMISSION_DELAY));

    if ((bufferInUse == TRUE) && (ecy_hsm_CSAI_SUCCESS == errorCode))
    {
        /* Release the bridge ports */
        ecy_HSM_RELEASE_BRIDGE_PORT(errorCode)
        /* timeout too long no free buffer */
        errorCode = ecy_hsm_CSAI_FC_BUSY;
    }
    return errorCode;
}
#endif /* #if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED)*/

/* PRQA S 1532 2 */ /*  non optimal reference of this function is tested and does not hinder functionality */
/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_Proxy */
ecy_hsm_Csai_ErrorT ecy_HSM_OpenSession(ecy_hsm_Csai_JobPriorityT priority, ecy_hsm_Csai_SessionHandleT* phSession)
{
    uint32 startingValue = 0U;
    uint32 elapsedValue  = 0U;

#if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED)
    /* PRQA S 2981 1 */ /* Justification: This initialization is needed to release resource */
    ecy_hsm_Csai_ErrorT errorCodeNoWaitMode = ecy_hsm_CSAI_ERR_RESOURCE_ALREADY_LOCKED_UNLOCKED;
#endif /* #if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED) */

    volatile ecy_hsm_Csai_ErrorT errorCode = HSM_CheckHsmCoreStarted();

    if (ecy_hsm_CSAI_SUCCESS == errorCode)
    {
        if ((NULL_PTR == ecy_hsm_pCalloutGetCounterValue) || (NULL_PTR == ecy_hsm_pCalloutGetElapsedCounterValue))
        {
            errorCode = ecy_hsm_CSAI_ERR_NULL_CALLOUT;
        }
    }

    if (ecy_hsm_CSAI_SUCCESS == errorCode)
    {

        /* A valid priority (not ecy_hsm_CSAI_PRIO_UNCHANGED) must be specified here, return immediately with error if not    */
        if (CSAI_PRIO_MAX_HOST_TASK < priority)
        {
            errorCode = ecy_hsm_CSAI_ERR_INVALID_PARAM;
        }
        else
        {
#if (COMPILER == COMPILER_TASKING)
/* Suppress TASKING compiler warning about errorCode being always SUCCESS, since the errorCode can change based on feature switches */
#pragma warning 549
#endif
            /* Get access to the HSM Bridge */
            errorCode = ecy_HSM_GetBridgeResource();

            if (ecy_hsm_CSAI_SUCCESS == errorCode)
            {
#if (COMPILER == COMPILER_TASKING)
#pragma warning restore
#endif
#if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED)
                /* Since shared variables are getting updated in multicore environment by different core.
                This variables hold the index of each core which shall be used to write to the intermediate buffer */
                uint8 tmpWriteIdxNoWaitMode;

                errorCode = ecy_HSM_CheckOpenSessionAllowed();

                if (ecy_hsm_CSAI_SUCCESS != errorCode)
                {
                    return errorCode;
                }

                errorCode = ecy_HSM_CheckPreviousOpenSessionCompleted(&tmpWriteIdxNoWaitMode);
                if (errorCode != ecy_hsm_CSAI_SUCCESS)
                {
                    return errorCode;
                }
#endif /* #if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED) */

                /* initialize parameter struct */
                sessionOpen.errorCode       = ecy_hsm_CSAI_ERR_TIMEOUT;
                sessionOpen.initialPriority = priority;
                sessionOpen.hSession        = ecy_hsm_CSAI_INVALID_SESSION_HANDLE_VALUE;

                /* Ask the HSM for a session handle   */
                ecy_hsm_HsmMCAL_OpenSession(&sessionOpen);

#if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED)
                /* Set the openSessionStatusNoWaitMode to TRUE to indicate there is open session job started */
                openSessionStatusNoWaitMode = TRUE;

                /* Release the bridge ports */
                ecy_HSM_RELEASE_BRIDGE_PORT(errorCode)
#endif /* #if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED) */

#if defined(GUAM) && defined (TEST_GROUP_NO_WAIT_MODE_OPEN_SESSION)
                Test_ecy_HSM_No_Wait_Mode_OpenSessionHelperFunction();
#endif /* #if defined(GUAM) && defined (TEST_GROUP_NO_WAIT_MODE_OPEN_SESSION) */
                /* Wait for response */
                ecy_hsm_pCalloutGetCounterValue(&startingValue);
                do
                {
                    ecy_hsm_pCalloutGetElapsedCounterValue(startingValue, &elapsedValue);
                    /* PRQA S 3415 3 */ /* Deviation: rule_13.5_1 */
                }
                while ((FALSE == ecy_hsm_HsmMCAL_IsSessionOpen())
#if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED)
                        && (openSessionWriteIdxNoWaitMode == tmpWriteIdxNoWaitMode)
#endif /* #if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED) */
                        && (ecy_hsm_CSAI_SUCCESS == HSM_CheckHsmCoreStarted()) /* HSM Core App still running? */
                        && (ecy_HSM_PROXY_DELAY > elapsedValue));

#if defined(GUAM) && defined (TEST_GROUP_NO_WAIT_MODE_OPEN_SESSION)
                Test_ecy_HSM_No_Wait_Mode_OpenSessionHelperFunction();
#endif /* #if defined(GUAM) && defined (TEST_GROUP_NO_WAIT_MODE_OPEN_SESSION) */

#if defined(GUAM) && defined (TEST_GROUP_CSAI_WAITMODE_SESSION)
                Test_ecy_HSM_Wait_Mode_OpenSessionHelperFunction();
#endif /* #if defined(GUAM) && defined (TEST_GROUP_CSAI_WAITMODE_SESSION) */

                errorCode = HSM_CheckHsmCoreStarted();

#if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED)
                /* clear the intermediate global buffer after copying to actual handle */
                /* Get access to the HSM Bridge */
                if (ecy_hsm_CSAI_SUCCESS == errorCode)
                {
                    errorCode = ecy_HSM_GetBridgeResource();
                }

                errorCodeNoWaitMode = errorCode;

                /* If the previous open session is completed copy from the intermediate buffer to actual handle. */
                /* openSessionWriteIdxNoWaitMode would be incremented only incase of new open session requested */
                if (openSessionReadIdxNoWaitMode != openSessionWriteIdxNoWaitMode)
                {
                    if (ecy_hsm_CSAI_SUCCESS == errorCode)
                    {
                        *phSession = sessionOpenNoWaitMode[openSessionReadIdxNoWaitMode].hSession;
                        errorCode  = sessionOpenNoWaitMode[openSessionReadIdxNoWaitMode].errorCode;
                    }

                    /* Increment the open session read index to read the information from next index for other request */
                    openSessionReadIdxNoWaitMode = (uint8) (openSessionReadIdxNoWaitMode + 1U) % CYCURHSM_SC_MAX_HOST_HSM_SESSIONS;
                }
                else
                    /* If there is no other request for opening a session, copy the handle from sessionOpen itself. */
#endif /* #if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED) */
                {
                    if (FALSE == ecy_hsm_HsmMCAL_IsSessionOpen())
                    {
                        sessionOpen.hSession  = ecy_hsm_CSAI_INVALID_SESSION_HANDLE_VALUE;
                        sessionOpen.errorCode = ((errorCode == ecy_hsm_CSAI_SUCCESS) ? ecy_hsm_CSAI_ERR_TIMEOUT : errorCode);
                    }

                    /* Return the session handle    */
                    *phSession = sessionOpen.hSession;

                    /* Copy error code from static structure to a volatile (so compiler does not optimize).
                     * Otherwise sessionOpen.errorCode could be overridden by an preempting task after
                     * the resource has been released. */
                    errorCode = sessionOpen.errorCode;

#if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED)
                    if (ecy_hsm_CSAI_SUCCESS == errorCodeNoWaitMode)
                    {
                        /* on going open session job is completed hence set openSessionStatusNoWaitMode to FALSE*/
                        openSessionStatusNoWaitMode = FALSE;
                    }
#endif /* #if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED) */
                }
#if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED)
                if (ecy_hsm_CSAI_SUCCESS == errorCodeNoWaitMode)
#endif /* #if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED) */
                {
                    /* Release the bridge ports */
                    ecy_HSM_RELEASE_BRIDGE_PORT(errorCode)
                }
            }
        }
    }
    return (errorCode);
    /* PRQA S 6010 2 */ /* <Deviation: Early returns in case of error handling is accepted */
} /* PRQA S 6009 */ /*< Justification: The if-statement exceeding the limit doesn't make this function less readable. Refactoring due to HIS metric
                        LEVEL is not sensible. */

#if (ENABLED == ecy_hsm_ENABLE_LEGACY_HOST_PROXY_INTERFACES)
/* PRQA S 1532 2 */ /*  non optimal reference of this function is tested and does not hinder functionality */
/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_Proxy */
ecy_hsm_Csai_ErrorT ecy_HSM_NopRequest(ecy_hsm_Csai_SessionHandleT hSession, ecy_hsm_Csai_JobHandleT* phJob)
{
    ecy_hsm_Csai_ErrorT errorCode = ecy_hsm_CSAI_SUCCESS;
    if (NULL_PTR == phJob)
    {
        errorCode = ecy_hsm_CSAI_ERR_INVALID_PARAM;
    }

    if (ecy_hsm_CSAI_SUCCESS == errorCode)
    {
        if (hSession >= maxHostHsmSessions)
        {
            *phJob    = ecy_hsm_CSAI_INVALID_JOB_HANDLE_VALUE;
            errorCode = ecy_hsm_CSAI_ERR_INVALID_HANDLE;
        }
        else
        {
            if (host2HSM_BridgePorts[hSession].status != HSM_STATUS_IDLE)
            {
                *phJob    = ecy_hsm_CSAI_INVALID_JOB_HANDLE_VALUE;
                errorCode = ecy_hsm_CSAI_FC_BUSY;
            }
            else
            {
                /* For now, both session and job handles are simply the index of the associated port    */
                *phJob                                        = hSession;
                host2HSM_BridgePorts[*phJob].requestErrorCode = ecy_hsm_CSAI_SUCCESS;
                host2HSM_BridgePorts[*phJob].opErrorCode      = ecy_hsm_CSAI_SUCCESS;
                host2HSM_BridgePorts[hSession].status         = HSM_STATUS_COMPLETE;
            }
        }
    }

    return (errorCode);
}
#endif // if (ENABLED == ecy_hsm_ENABLE_LEGACY_HOST_PROXY_INTERFACES)

/* PRQA S 1532 2 */ /*  non optimal reference of this function is tested and does not hinder functionality */
/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_Proxy */
ecy_hsm_Csai_ErrorT ecy_HSM_OpRequest_NoJobHandle(ecy_hsm_Csai_SessionHandleT hSession,
                                                  ecy_hsm_Csai_JobPriorityT   priority,
                                                  HSM_FunctionT               function,
                                                  uint32                      paramBlockSize,
                                                  const void*                 pParamBlock,
                                                  ecy_hsm_Csai_JobHandleT*    phJob)
{
    ecy_hsm_Csai_ErrorT errorCode;
#if ((ecy_hsm_NOWAIT_MODE_WAIT_WHEN_IN_TRANSMISSION == ENABLED) && (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED))
    uint32 startingValue = (uint32) 0UL;
    uint32 elapsedValue  = (uint32) 0UL;
#endif

    if (NULL_PTR == phJob)
    {
        errorCode = ecy_hsm_CSAI_ERR_INVALID_PARAM;
    }
    else if (hSession >= maxHostHsmSessions)
    {
        *phJob    = ecy_hsm_CSAI_INVALID_JOB_HANDLE_VALUE;
        errorCode = ecy_hsm_CSAI_ERR_INVALID_HANDLE;
    }
    else
    {
#if (COMPILER == COMPILER_TASKING)
/* Suppress TASKING compiler warning about errorCode being always SUCCESS, since the errorCode can change based on feature switches */
#pragma warning 549
#endif
#if ((ecy_hsm_NOWAIT_MODE_WAIT_WHEN_IN_TRANSMISSION == ENABLED) && (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED))
        if ((NULL_PTR == ecy_hsm_pCalloutGetCounterValue) || (NULL_PTR == ecy_hsm_pCalloutGetElapsedCounterValue))
        {
            errorCode = ecy_hsm_CSAI_ERR_NULL_CALLOUT;
        }
        else
        {
            ecy_hsm_pCalloutGetCounterValue(&startingValue);
            do
            {
#endif
                /* Get access to the HSM Bridge */
                errorCode = ecy_HSM_GetBridgeResource();
                /* PRQA S 2995, 2991 1 */ /* <Deviation: control flow depends on defines */
                if (ecy_hsm_CSAI_SUCCESS == errorCode)
#if (COMPILER == COMPILER_TASKING)
#pragma warning restore
#endif
                {
                    if (host2HSM_BridgePorts[hSession].status != HSM_STATUS_IDLE)
                    {
                        *phJob    = ecy_hsm_CSAI_INVALID_JOB_HANDLE_VALUE;
                        errorCode = ecy_hsm_CSAI_FC_BUSY;
                    }
                    else
                    {
                        /* For now, both session and job handles are simply the index of the associated port    */
                        *phJob    = hSession;
                        errorCode = LoadOp(*phJob, priority, function, paramBlockSize, pParamBlock);
                        if (ecy_hsm_CSAI_SUCCESS != errorCode)
                        {
                            /* The CSM uses this to know that the call to ecy_HSM_OpRequest_NoJobHandle has failed  */
                            *phJob = ecy_hsm_CSAI_INVALID_JOB_HANDLE_VALUE;
                        }
                    }
                    /* Release the bridge ports */
                    ecy_HSM_RELEASE_BRIDGE_PORT(errorCode)
                }
#if ((ecy_hsm_NOWAIT_MODE_WAIT_WHEN_IN_TRANSMISSION == ENABLED) && (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED))
                /* PRQA S 2813 1 */ /* Deviation: EXP34 : It's a false positive warning as we can see ecy_hsm_pCalloutGetElapsedCounterValue is already checked for nullptr. */
                ecy_hsm_pCalloutGetElapsedCounterValue(startingValue, &elapsedValue);
            }
            while ((errorCode == ecy_hsm_CSAI_FC_BUSY) && (elapsedValue < ecy_hsm_NOWAIT_MODE_WAIT_WHEN_IN_TRANSMISSION_DELAY));
        }
#endif
    }

    return (errorCode);
} /* PRQA S 6009 */ /*< Justification: The if-statement exceeding the limit doesn't make this function less readable. Refactoring due to HIS metric
                       LEVEL is not sensible. */

/* PRQA S 2889 1  */ /* Justification: Functions which have many error checks need to return immediately in case of an error */
ecy_hsm_Csai_ErrorT ecy_HSM_DoDisableSecCritFunctions(ecy_hsm_Csai_SessionHandleT hSession,
                                                      uint32                      paramBlockSize,
                                                      const void*                 pParamBlock,
                                                      ecy_hsm_Csai_JobHandleT*    phJob)
{
    ecy_hsm_Csai_ErrorT errorCode;
    uint32              startingValue;
    uint32              elapsedValue;

    CSAI_PARAM_UNUSED(pParamBlock);

    if ((uint32)HSM_OP_PARAM_BLOCK_SIZE < paramBlockSize)
    {
        return ecy_hsm_CSAI_ERR_INPUT_TOO_LARGE;
    }

#if (COMPILER == COMPILER_TASKING)
/* Suppress TASKING compiler warning about errorCode being always SUCCESS, since the errorCode can change based on feature switches */
#pragma warning 549
#endif
    /* Get access to the HSM Bridge */
    errorCode = ecy_HSM_GetBridgeResource();
    /* PRQA S 2995, 2991 1 */ /* <Deviation: control flow depends on defines */
    if (ecy_hsm_CSAI_SUCCESS == errorCode)
#if (COMPILER == COMPILER_TASKING)
#pragma warning restore
#endif
    {
        (void)ecy_hsm_HsmMCAL_DoDisableSecCritOp(hSession);
        if ((NULL_PTR == ecy_hsm_pCalloutGetCounterValue) || (NULL_PTR == ecy_hsm_pCalloutGetElapsedCounterValue))
        {
            errorCode = ecy_hsm_CSAI_ERR_NULL_CALLOUT;
        }
        else
        {
            ecy_hsm_pCalloutGetCounterValue(&startingValue);
            do
            {
                ecy_hsm_pCalloutGetElapsedCounterValue(startingValue, &elapsedValue);

                /* PRQA S 3415 4 */ /* Deviation: rule_13.5_1 */ /* Justification: ecy_hsm_HsmMCAL_GetMode() only reads the status and
                                                                  * does no write operations, that might interfere with this function. */
            }
            while ((HSM_STATUS_COMPLETE != host2HSM_BridgePorts[hSession].status)
                   && ((HSM_MODE_CORE_APP == ecy_hsm_HsmMCAL_GetMode()) || (HSM_MODE_SUSPENDED == ecy_hsm_HsmMCAL_GetMode()))
                   && (ecy_HSM_PROXY_DELAY > elapsedValue));

            /* PRQA S 3415 3 */ /* Deviation: rule_13.5_1 */ /* Justification: ecy_hsm_HsmMCAL_GetMode() only reads the status and
                                                              * does no write operations, that might interfere with this function. */
            errorCode = ((HSM_MODE_CORE_APP == ecy_hsm_HsmMCAL_GetMode()) || (HSM_MODE_SUSPENDED == ecy_hsm_HsmMCAL_GetMode()))
                            ? ecy_hsm_CSAI_SUCCESS
                            : ecy_hsm_CSAI_ERR_HSM2HTS_LOCKUP;

            if (HSM_STATUS_COMPLETE != host2HSM_BridgePorts[hSession].status)
            {
                /* if the HSM is still running, we want to return a timeout error */
                if (errorCode == ecy_hsm_CSAI_SUCCESS)
                {
                    errorCode = ecy_hsm_CSAI_ERR_TIMEOUT;
                }
                host2HSM_BridgePorts[hSession].opErrorCode = ecy_hsm_CSAI_ERR_OP_REQUEST_FAILED;
            }
            else
            {
                errorCode = host2HSM_BridgePorts[hSession].requestErrorCode;
                /* If the request returned an error, clear the port status down to HSM_STATUS_IDLE and cancel the job  */
                if (ecy_hsm_CSAI_SUCCESS != errorCode)
                {
                    host2HSM_BridgePorts[hSession].status      = HSM_STATUS_IDLE;
                    host2HSM_BridgePorts[hSession].opErrorCode = ecy_hsm_CSAI_ERR_OP_REQUEST_FAILED;
                    /* The CSM uses this to know that the call to ecy_HSM_OpRequest_NoJobHandle has failed  */
                    if (NULL_PTR != phJob)
                    {
                        *phJob = ecy_hsm_CSAI_INVALID_JOB_HANDLE_VALUE;
                    }
                }
            }
        }
        /* Release access to the HSM Bridge */
        ecy_HSM_RELEASE_BRIDGE_PORT(errorCode)
    }
    ecy_hsm_ListDiagnosticValues();
    return (errorCode);
    /* PRQA S 6010 2 */ /* <Deviation: Early returns in case of error handling is accepted */
    /* PRQA S 6002 1 */ /* <Deviation: High complexity due to NULL_PTR checks to add more stability to the function. */
} /* PRQA S 6009 */ /*< Justification: The if-statement exceeding the limit doesn't make this function less readable. Refactoring due to HIS metric
                       LEVEL is not sensible. */

/* PRQA S 3238 24 */ /* Justification: LOCAL_INLINE is declared as 'static inline', function has NO external linkage. */
#if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED)
LOCAL_INLINE void ecy_hsm_QuickRouteSetSessionToTransmit(ecy_hsm_Csai_SessionHandleT hSession, HSM_FunctionT function)
{
    uint32 startingValue;
    /* set Quickroute Mode */
    if ( (HSM_FUNC_SHE_MAC_VERIFY == function) || (HSM_FUNC_CMAC_VERIFY == function) || (HSM_FUNC_SIPHASH_VERIFY == function))
    {
        host2HSM_QuickRouteStatus[hSession] = ecy_hsm_QR_STATUS_PENDING_VERIFY;
    }
    else if ( (HSM_FUNC_SHE_MAC_GENERATE == function) || (HSM_FUNC_CMAC_GENERATE == function) || (HSM_FUNC_SIPHASH_GENERATE == function))
    {
        host2HSM_QuickRouteStatus[hSession] = ecy_hsm_QR_STATUS_PENDING_GENERATE;
    }
    else
    {
        host2HSM_QuickRouteStatus[hSession] = ecy_hsm_QR_STATUS_IDLE;
    }

    /* set Transmit state for new bridge modes */
    host2HSM_BridgePorts[hSession].status           = HSM_STATUS_TRANSMIT_JOB;
    host2HSM_BridgePorts[hSession].requestErrorCode = ecy_hsm_CSAI_SUCCESS;
    host2HSM_BridgePorts[hSession].opErrorCode      = ecy_hsm_CSAI_SUCCESS;
    ecy_hsm_pCalloutGetCounterValue(&startingValue);
    host2HSM_BridgePortsTimeoutStamp[hSession] = startingValue;
}

/* PRQA S 3238 39 */ /* Justification: LOCAL_INLINE is declared as 'static inline', function has NO external linkage. */
LOCAL_INLINE void ecy_hsm_copyQuickRouteResult(ecy_hsm_Csai_SessionHandleT hSession)
{
    uint32 jobSlot, jobSlotMax;
    /* check if any Session has used the quickroute and copy the buffer to the correct session */
   if (hSession < CYCURHSM_SC_MAX_HOST_HSM_SESSIONS)
   {
        /* Only check / copy one session */
        jobSlot    = hSession;
        jobSlotMax = hSession;
    }
    else
    {
        /* Check / copy all sessions */
        jobSlot    = (uint32) 0UL;
        jobSlotMax = CYCURHSM_SC_MAX_HOST_HSM_SESSIONS - 1UL;
    }

    for (; jobSlot <= jobSlotMax; jobSlot++)
    {
        if ((ecy_hsm_QR_STATUS_PENDING_VERIFY == host2HSM_QuickRouteStatus[jobSlot])
           && (HSM_STATUS_COMPLETE == host2HSM_BridgePorts[jobSlot].status))
        {
            hsm2hst_qmacResultFlagBuffer[jobSlot] = resultFlagBuffer;
            host2HSM_QuickRouteStatus[jobSlot]    = ecy_hsm_QR_STATUS_COPIED;
        }
        else if ((ecy_hsm_QR_STATUS_PENDING_GENERATE == host2HSM_QuickRouteStatus[jobSlot])
             && (HSM_STATUS_COMPLETE == host2HSM_BridgePorts[jobSlot].status))
        {
            (void)ecy_memcpy(hsm2hst_qmacBuffer[jobSlot], qmacBuffer, AES_BLOCK_SIZE_BYTES);
            host2HSM_QuickRouteStatus[jobSlot] = ecy_hsm_QR_STATUS_COPIED;
        }
        else
        {
            /* nothing to do */
        }
    }
}

/* PRQA S 3238 12 */ /* Justification: LOCAL_INLINE is declared as 'static inline', function has NO external linkage. */
LOCAL_INLINE void ecy_hsm_setQuickRouteStatus(ecy_hsm_Csai_SessionHandleT hSession, ecy_hsm_QuickRouteStatusT qrStatus)
{
    ecy_hsm_Csai_ErrorT errorCode;
    if (hSession < CYCURHSM_SC_MAX_HOST_HSM_SESSIONS)
    {
        /* Get access to the HSM Bridge */
        errorCode = ecy_HSM_GetBridgeResource();
        /* PRQA S 2995, 2991 1 */ /* <Deviation: control flow depends on defines */
        if(errorCode == ecy_hsm_CSAI_SUCCESS )
        {
            host2HSM_QuickRouteStatus[hSession] = qrStatus;

            /* Release access to the HSM Bridge */
            ecy_HSM_RELEASE_BRIDGE_PORT(errorCode)
        }
    }
}

/* PRQA S 3238 31 */ /* Justification: LOCAL_INLINE is declared as 'static inline', function has NO external linkage. */
LOCAL_INLINE ecy_hsm_Csai_ErrorT ecy_HSM_CheckQuickRouteAllowed(void)
{
    ecy_hsm_Csai_ErrorT errorCode ;
    uint32              startingValue = (uint32) 0UL;
    uint32              elapsedValue  = (uint32) 0UL;
    /* PRQA S 2981 1 */ /* <Justification: initialization avoids compiler warning */
    ecy_hsm_Csai_ErrorT checkHsmCore = ecy_hsm_CSAI_SUCCESS;
    uint32               jobSlot;

     /* check if any session transmitting data at the moment.
     * depending on the configuration define wait to get the access to the transmission buffer. */
    /* PRQA S 3238 1 */ /* Justification: LOCAL_INLINE is declared as 'static inline', function has NO external linkage. */
    ecy_hsm_pCalloutGetCounterValue(&startingValue);
    do
    {
        errorCode = ecy_HSM_GetBridgeResource();
        /* PRQA S 2995, 2991 1 */ /* <Deviation: control flow depends on defines */
        if(errorCode == ecy_hsm_CSAI_SUCCESS)
        {
            for (jobSlot = 0u; jobSlot < CYCURHSM_SC_MAX_HOST_HSM_SESSIONS; jobSlot++)
            {
                if (HSM_STATUS_TRANSMIT_JOB == host2HSM_BridgePorts[jobSlot].status)
                {
                    /* Release access to the HSM Bridge */
                    (void)ecy_HSM_ReleaseBridgeResource();
                    errorCode = ecy_hsm_CSAI_ERR_QUICK_ROUTE_NOT_POSSIBLE;
                    break;
                }
            }
            checkHsmCore = HSM_CheckHsmCoreStarted();
            ecy_hsm_pCalloutGetElapsedCounterValue(startingValue, &elapsedValue);
        }
        else
        {
            /* PRQA S 2880 1 */ /* <Deviation: control flow depends on defines */
            break ;
        }

#if (ecy_hsm_NO_WAIT_MODE_QUICK_ROUTE_FORCE_TIMEOUT == DISABLED)
        /* Force Timeout NOWAIT bridge mode is selected and no FORCE_TIMEOUT is enabled */
        break;
#endif
    }
    while ((ecy_hsm_CSAI_ERR_QUICK_ROUTE_NOT_POSSIBLE == errorCode) && (checkHsmCore == ecy_hsm_CSAI_SUCCESS) /* HSM Core App still running? */
           && (elapsedValue < ecy_hsm_NOWAIT_MODE_TRANSMIT_CHECK_DELAY));
    return errorCode;
}

/* PRQA S 3238 39 */ /* Justification: LOCAL_INLINE is declared as 'static inline', function has NO external linkage. */
LOCAL_INLINE ecy_hsm_Csai_ErrorT ecy_HSM_CheckPreviousOpenSessionCompleted(uint8* pTempWriteIdx)
{
    ecy_hsm_Csai_ErrorT errorCode = ecy_hsm_CSAI_SUCCESS;

    /* Check if the openSessionStatusNoWaitMode variable is set to TRUE.
    * This condition will be entered if open session is called again before previous open session is completed.*/
    if (openSessionStatusNoWaitMode == TRUE)
    {
        /* When a new open session request is received, increment the local pointer to move to the next index. */
        *pTempWriteIdx = (uint8) (openSessionWriteIdxNoWaitMode + 1U) % CYCURHSM_SC_MAX_HOST_HSM_SESSIONS;

        /* Since lock on resource is released in no wait mode this checks if the previous open session is completed and copies
           session handle to intermediate buffer */
        /* PRQA S 3415 1 */ /* Deviation: rule_13.5_1 */ /* Justification: no side effect by not processing right hand operand. */
        if ((ecy_hsm_HsmMCAL_IsSessionOpen() == TRUE) && (openSessionReadIdxNoWaitMode != *pTempWriteIdx))
        {
            /* copy the open session handle to intermediate global buffer if the previous open session is completed */
            sessionOpenNoWaitMode[openSessionWriteIdxNoWaitMode].hSession = sessionOpen.hSession;
            sessionOpenNoWaitMode[openSessionWriteIdxNoWaitMode].errorCode = sessionOpen.errorCode;

            openSessionWriteIdxNoWaitMode = *pTempWriteIdx;
        }
        else
        {
            /* Release the bridge ports */
            ecy_HSM_RELEASE_BRIDGE_PORT(errorCode)

            /* Return busy if previous open session is not completed */
            errorCode = ecy_hsm_CSAI_FC_BUSY;
        }
    }
    else
    {
        /* If the open session is for first time pTempWriteIdx initialized with openSessionWriteIdxNoWaitMode.*/
        *pTempWriteIdx = openSessionWriteIdxNoWaitMode;
    }

    return errorCode;
}
#endif /* #if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED)*/

/* Refactored from ecy_HSM_QuickRoute() due to HIS metrics, see description below */
/* PRQA S 3238 135 */ /* LOCAL_INLINE is declared as 'static inline', function has NO external linkage. */
/* PRQA S 3673 6 */ /* Justification: Function fits a generic interface, pointer to const not always feasible */
/* PRQA S 2889 1 */ /* Justification: Functions which have many error checks need to return immediately in case of an error */
LOCAL_INLINE ecy_hsm_Csai_ErrorT ecy_HSM_DoQuickRoute(ecy_hsm_Csai_SessionHandleT hSession,
                                                      HSM_FunctionT               function,
                                                      uint32                      paramBlockSize,
                                                      void*                       pParamBlock,
                                                      ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* PRQA S 2981 1 */ /* Justification: This initialization is needed incase NO WAIT MODE disabled */
    ecy_hsm_Csai_ErrorT errorCode = ecy_hsm_CSAI_SUCCESS;

    ecy_hsm_AddDiagnosticValue(0, function);

    /* If Parameters are correct and quickroute is available the quickroute will be locked */
    if (NULL_PTR == pParamBlock)
    {
        errorCode = ecy_hsm_CSAI_ERR_INVALID_PARAM;
    }
    else if ((uint32)HSM_OP_PARAM_BLOCK_SIZE < paramBlockSize)
    {
        errorCode = ecy_hsm_CSAI_ERR_INPUT_TOO_LARGE;
    }
    else if ((NULL_PTR == ecy_hsm_pCalloutGetElapsedCounterValue) || (NULL_PTR == ecy_hsm_pCalloutGetCounterValue))
    {
        errorCode = ecy_hsm_CSAI_ERR_NULL_CALLOUT;
    }
    else
    {
#if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED)
        /* check Quickroute is allowed and use spinlock to get exclusive access to all needed resources */
        errorCode = ecy_HSM_CheckQuickRouteAllowed();
#endif
    }

    if (ecy_hsm_CSAI_SUCCESS == errorCode)
    {
#if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED)
        errorCode = ecy_HSM_CheckOpenSessionCompleted(TRUE);
        if (ecy_hsm_CSAI_SUCCESS == errorCode)
#endif /* #if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED) */
        {
#if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED)
            /* check if any Session has used the quickroute and copy the buffer to the correct session */
            ecy_hsm_copyQuickRouteResult(CYCURHSM_SC_MAX_HOST_HSM_SESSIONS);
#endif
            /* consider only MAC Verify as potentially safety-relevant operations */
            if ((HSM_FUNC_CMAC_VERIFY == function) || (HSM_FUNC_SIPHASH_VERIFY == function))
            {
                /* PRQA S 0316 1 */ /* <Deviation: cast is unavoidable and does not affect functionality*/
                HSM_MacQuickParamT* const qMacBlock = (HSM_MacQuickParamT*)pParamBlock;
                qMacBlock->safetyMac                = NULL_PTR; /* default initialization */
            }
#if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED)
            ecy_hsm_QuickRouteSetSessionToTransmit(hSession, function);
#endif
            opParams.functionId     = function;
            opParams.paramBlockSize = paramBlockSize;

            /** It's OK to pass a NULL_PTR pointer if the length is zero (which it will be)  */
            /* PRQA S 0316 1 */ /* <Deviation: cast is unavoidable and does not affect functionality */
            (void)ecy_memcpy(opParams.paramBlock, (const uint8*)pParamBlock, paramBlockSize);

            errorCode =ecy_HSM_DoQuickRoute_LoadOp(hSession, phJob);
        }
    }
    ecy_hsm_ListDiagnosticValues();
    return (errorCode);
}

/* Refactored from ecy_HSM_DoQuickRoute() due to HIS metrics */
LOCAL_INLINE ecy_hsm_Csai_ErrorT ecy_HSM_DoQuickRoute_LoadOp(ecy_hsm_Csai_SessionHandleT hSession,ecy_hsm_Csai_JobHandleT* phJob)
{
    /* PRQA S 2981 1 */ /* Justification: This initialization is needed to release resource */
    ecy_hsm_Csai_ErrorT errorCode = ecy_hsm_CSAI_SUCCESS;
    uint32              startingValue  = 0U;
    uint32              elapsedValue   = 0U;

    ecy_hsm_HsmMCAL_LoadQuickRoute(hSession);

#if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED)
        /* directly release resource in new bridge mode */
        /* Release access to the HSM Bridge */
        ecy_HSM_RELEASE_BRIDGE_PORT(errorCode);
#endif

    ecy_hsm_pCalloutGetCounterValue(&startingValue);
    do
    {
        ecy_hsm_pCalloutGetElapsedCounterValue(startingValue, &elapsedValue);
        errorCode = HSM_CheckHsmCoreStarted();
    }
    while ((HSM_STATUS_COMPLETE != host2HSM_BridgePorts[hSession].status)
            && (ecy_hsm_CSAI_SUCCESS == errorCode) /* HSM Core App still running? */
            && (ecy_HSM_PROXY_DELAY > elapsedValue));

    errorCode = HSM_CheckHsmCoreStarted();

    if (HSM_STATUS_COMPLETE != host2HSM_BridgePorts[hSession].status)
    {
#if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED)
        ecy_hsm_setQuickRouteStatus(hSession, ecy_hsm_QR_STATUS_ERROR);
#endif
        /* if the HSM is still running, we want to return a timeout error */
        if (errorCode == ecy_hsm_CSAI_SUCCESS)
        {
            errorCode = ecy_hsm_CSAI_ERR_TIMEOUT;
        }
        host2HSM_BridgePorts[hSession].opErrorCode = ecy_hsm_CSAI_ERR_OP_REQUEST_FAILED;
        host2HSM_BridgePorts[hSession].status      = HSM_STATUS_IDLE;
    }
    else
    {
#if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED)
        /* Job finished successful. Copy the content of the buffer to the session specific buffer */
        errorCode = ecy_HSM_GetBridgeResource();
        /* PRQA S 2995, 2991 1 */ /* <Deviation: control flow depends on defines */
        if(errorCode == ecy_hsm_CSAI_SUCCESS)
        {
            ecy_hsm_copyQuickRouteResult(hSession);

            /* Release access to the HSM Bridge */
            ecy_HSM_RELEASE_BRIDGE_PORT(errorCode)
        }
#endif
        errorCode = host2HSM_BridgePorts[hSession].requestErrorCode;

        /* If the request returned an error, clear the port status down to HSM_STATUS_IDLE and cancel the job  */
        if (ecy_hsm_CSAI_SUCCESS != errorCode)
        {
#if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED)
            ecy_hsm_setQuickRouteStatus(hSession, ecy_hsm_QR_STATUS_ERROR);
#endif
            host2HSM_BridgePorts[hSession].opErrorCode = ecy_hsm_CSAI_ERR_OP_REQUEST_FAILED;
            host2HSM_BridgePorts[hSession].status      = HSM_STATUS_IDLE;

            /* The CSM uses this to know that the call to ecy_HSM_OpRequest_NoJobHandle has failed  */
            if (NULL_PTR != phJob)
            {
                *phJob = ecy_hsm_CSAI_INVALID_JOB_HANDLE_VALUE;
            }
        }
    }
    return (errorCode);
}

/**
 * This works as follows:
 *   Host calls ecy_hsm_Csai_MacGenerate as usual
 *   If data length is <= 256 bytes, host calls ecy_HSM_QuickRoute( )
 *    ecy_HSM_QuickRoute sets a flag (if the HSM core is started), on the PowerPC this triggers an independent Cat1 ISR
 *    on the HSM, on the RH850 and Aurix it is handled through the single HSM_Request ISR, which is a Cat2. Either way,
 *    inside the HSM, HSM_DoQuickRoute() is called.  This:
 *      - First checks a flag called lockQuickRoute.  This flag is set whenever the AES hardware is busy (at the same
 *        time as OsResourceAES is locked).  If the flag is set then HSM_DoQuickRoute() returns
 *        ecy_hsm_CSAI_ERR_QUICK_ROUTE_NOT_POSSIBLE to the host through the operation request error code.
 *      - Then attempts to get a pointer to the required key.  If the key is not present in the RAM keystore, then
 *        ecy_hsm_CSAI_ERR_QUICK_ROUTE_NOT_POSSIBLE is returned to the host through the operation request error code.
 *      - If the lockQuickRoute flag is clear and the key is in the RAM keystore, then HSM_DoQuickRoute() proceeds.
 *      - The key flags are checked, if the key cannot be used then an appropriate error is returned to the host through
 *        the operation error code.
 *      - Some basic checks are made on the session.
 *      - The address pointers are checked to ensure they do not point into HSM memory.
 *      - A specially optimized version of the CMAC calculation function is called.  This contains no resource locks
 *        because we are in the ISR handler.  As usual, this writes the result back to host memory.
 *      - The error codes are written back to the host and the session status is set to COMPLETE
 *      - The ISR returns
 *   IF ecy_hsm_CSAI_ERR_QUICK_ROUTE_NOT_POSSIBLE was returned, then the operation is scheduled in the normal way
 *    instead, and will find its way into the HSMs task queue as usual.  If the problem was that the key was not available,
 *    then this time the key will be loaded on demand as usual. IF some other error was returned then this will be returned
 *    to a subsequent PollHandle call. IF the operation succeeded then the data is ready on the host side.  Here there is a
 *    subtle tweak: Truncation of the generated MAC is done on the host.  There are two reasons for this, 1) It means that
 *    a pre-arranged buffer can be used for the MAC value, which removes the need to range check the buffer.  This buffer
 *    is configured as part of ecy_HSM_Configure. 2) It means that we get the benefit of the higher speed of the host core.
 *   ecy_hsm_Csai_MacGenerate() now returns
 *   The host now calls ecy_hsm_Csai_PollHandle(), if the quick route was used then the results will definitely be
 *    available, if in fact the operation took the slow lane then the host might need to poll several times. Operation is
 *    complete.
 */
/* The error code returned is the request error code */
/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_Proxy */
ecy_hsm_Csai_ErrorT ecy_HSM_QuickRoute(ecy_hsm_Csai_SessionHandleT hSession,
                                       HSM_FunctionT               function,
                                       uint32                      paramBlockSize,
                                       void* const                 pParamBlock,
                                       ecy_hsm_Csai_JobHandleT*    phJob)
{
    ecy_hsm_Csai_ErrorT errorCode = HSM_CheckHsmCoreStarted();

    /* Don't place do a quick route if the core is not started (e.g. in suspend mode) */
    if (errorCode == ecy_hsm_CSAI_SUCCESS)
    {
        if (hSession >= maxHostHsmSessions)
        {
            if (NULL_PTR != phJob)
            {
                *phJob = ecy_hsm_CSAI_INVALID_JOB_HANDLE_VALUE;
            }
            errorCode = ecy_hsm_CSAI_ERR_INVALID_HANDLE;
        }
        else
        {
            /* Populate the job handle whatever happens, may overwrite with ecy_hsm_CSAI_ERR_INVALID_HANDLE if the
             * request fails */
            if (NULL_PTR != phJob)
            {
                *phJob = hSession;
            }

            if (host2HSM_BridgePorts[hSession].status != HSM_STATUS_IDLE)
            {
                if (NULL_PTR != phJob)
                {
                    *phJob = ecy_hsm_CSAI_INVALID_JOB_HANDLE_VALUE;
                }
                errorCode = ecy_hsm_CSAI_ERR_QUICK_ROUTE_NOT_POSSIBLE;
            }
            else
            {
                errorCode = ecy_HSM_DoQuickRoute(hSession, function, paramBlockSize, pParamBlock, phJob);
            }
        }
    }

    return errorCode;
}

/* PRQA S 1532 2 */ /*  non optimal reference of this function is tested and does not hinder functionality */
/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_Proxy */
void ecy_HSM_TruncateAndCopyMac(ecy_hsm_Csai_SessionHandleT hSession,
                                uint32                      truncatedLengthBits,
                                boolean                     truncationAllowed,
                                uint8*                      pDestination,
                                uint32*                     pMacCountBytes,
                                ecy_hsm_Csai_MACAlgorithmT  algorithm)
{
    uint8* pMacBuffer;

    if (hSession < maxHostHsmSessions)
    {
#if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED)
        pMacBuffer = hsm2hst_qmacBuffer[hSession];
#else
        pMacBuffer = qmacBuffer;
#endif
        /* If there has already been an error reported, then we skip this, otherwise we would over-write
           the real error */
        if (ecy_hsm_CSAI_SUCCESS == host2HSM_BridgePorts[hSession].opErrorCode)
        {
            ecy_hsm_Csai_ErrorT errorCode = ecy_hsm_CSAI_SUCCESS;

            if ((ecy_hsm_CSAI_AES_CMAC == algorithm) && (truncatedLengthBits >= AES_BLOCK_SIZE_BITS))
            {
                (void)ecy_memcpy(pDestination, pMacBuffer, AES_BLOCK_SIZE_BYTES);
                if (pMacCountBytes != NULL_PTR)
                {
                    *pMacCountBytes = AES_BLOCK_SIZE_BYTES;
                }
            }
            else if ((ecy_hsm_CSAI_SIPHASH_24 == algorithm) && (truncatedLengthBits >= ecy_hsm_SIP_HASH_24_MAX_MAC_SIZE_BITS))
            {
                (void)ecy_memcpy(pDestination, pMacBuffer, ecy_hsm_SIP_HASH_24_MAX_MAC_SIZE_BYTES);
                if (pMacCountBytes != NULL_PTR)
                {
                    *pMacCountBytes = ecy_hsm_SIP_HASH_24_MAX_MAC_SIZE_BYTES;
                }
            }
            else if (TRUE == truncationAllowed)
            {
                uint32 numCopyBytes     = ecy_hsm_BITS_TO_FULL_BYTE_LENGTH(truncatedLengthBits);
                uint32 numRemainderBits = (truncatedLengthBits & 0x07U);

                /* Clear bits in the buffer */
                if (numRemainderBits > 0U)
                {
                    uint8 bitMask = (uint8)(~((1U << (8U - numRemainderBits)) - 1U));
                    pMacBuffer[numCopyBytes - 1U] &= bitMask;
                }
                (void)ecy_memcpy(pDestination, pMacBuffer, numCopyBytes);

                if (pMacCountBytes != NULL_PTR)
                {
                    *pMacCountBytes = numCopyBytes;
                }
            }
            else
            {
                errorCode = ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL;
                if (pMacCountBytes != NULL_PTR)
                {
                    *pMacCountBytes = 0U;
                }
            }
            host2HSM_BridgePorts[hSession].opErrorCode = errorCode;
        }
#if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED)
        ecy_hsm_setQuickRouteStatus(hSession, ecy_hsm_QR_STATUS_COMPLETE);
#endif
    }
    /* PRQA S 6009 1 */ /* Justification: Refactoring due to HIS level makes this code less readable*/
}

/* PRQA S 1532 2 */ /*  non optimal reference of this function is tested and does not hinder functionality */
/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_Proxy */
ecy_hsm_Csai_ErrorT ecy_HSM_CopyResultFlag(uint32* pMacResultFlag, ecy_hsm_Csai_SessionHandleT hSession)
{
    ecy_hsm_Csai_ErrorT errorCode = ecy_hsm_CSAI_SUCCESS;
    if (NULL_PTR == pMacResultFlag)
    {
        return ecy_hsm_CSAI_ERR_INVALID_PARAM;
    }
#if (ecy_hsm_CSAI_FS_NO_WAIT_MODE != ENABLED)
    CSAI_PARAM_UNUSED(hSession);
    *pMacResultFlag = resultFlagBuffer;
#else
    if (hSession > maxHostHsmSessions)
    {
        return ecy_hsm_CSAI_ERR_INVALID_PARAM;
    }
    *pMacResultFlag = hsm2hst_qmacResultFlagBuffer[hSession];
    ecy_hsm_setQuickRouteStatus(hSession, ecy_hsm_QR_STATUS_COMPLETE);
#endif /* #if(ecy_hsm_CSAI_FS_NO_WAIT_MODE != ENABLED) */
    return errorCode;
}/* PRQA S 6010 1 */ /* <Deviation: Early returns in case of error handling is accepted */
//#endif   (ECY_HSM_VMS_FS_JOB_HANDLER_QUICK_CMAC == ENABLED)

#if (ENABLED == ecy_hsm_ENABLE_LEGACY_HOST_PROXY_INTERFACES)
/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_Proxy */
ecy_hsm_Csai_ErrorT
ecy_HSM_OpRequest_WithJobHandle(ecy_hsm_Csai_JobHandleT hJob, HSM_FunctionT function, uint32 paramBlockSize, const void* pParamBlock)
{
    uint32              startingValue;
    uint32              elapsedValue;
    ecy_hsm_Csai_ErrorT errorCode = HSM_CheckHsmCoreStarted();

    if (errorCode == ecy_hsm_CSAI_SUCCESS)
    {
        if (hJob >= maxHostHsmSessions)
        {
            errorCode = ecy_hsm_CSAI_ERR_INVALID_HANDLE;
        }
        else
        {
#if (COMPILER == COMPILER_TASKING)
/* Suppress TASKING compiler warning about errorCode being always SUCCESS, since the errorCode can change based on feature switches */
#pragma warning 549
#endif
#if ((ecy_hsm_NOWAIT_MODE_WAIT_WHEN_IN_TRANSMISSION == ENABLED) && (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED))
            ecy_hsm_pCalloutGetCounterValue(&startingValue);
            do
            {
#endif
                /* Get access to the HSM Bridge */
                errorCode = ecy_HSM_GetBridgeResource();
                /* PRQA S 2995, 2991 1 */ /* <Deviation: control flow depends on defines */
                if (ecy_hsm_CSAI_SUCCESS == errorCode)
#if (COMPILER == COMPILER_TASKING)
#pragma warning restore
#endif
                {

                    if (host2HSM_BridgePorts[hJob].status != HSM_STATUS_IDLE)
                    {
                        errorCode = ecy_hsm_CSAI_FC_BUSY;
                    }
                    else
                    {
                        errorCode = LoadOp(hJob, ecy_hsm_CSAI_PRIO_UNCHANGED, function, paramBlockSize, pParamBlock);
                    }

                    /* Release the bridge ports */
                    ecy_HSM_RELEASE_BRIDGE_PORT(errorCode)
                }
#if ((ecy_hsm_NOWAIT_MODE_WAIT_WHEN_IN_TRANSMISSION == ENABLED) && (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED))
                ecy_hsm_pCalloutGetElapsedCounterValue(startingValue, &elapsedValue);
            }
            while ((errorCode == ecy_hsm_CSAI_FC_BUSY) && (elapsedValue < ecy_hsm_NOWAIT_MODE_WAIT_WHEN_IN_TRANSMISSION_DELAY));
#endif
        }
    }
    return (errorCode);
}
#endif // if (ENABLED == ecy_hsm_ENABLE_LEGACY_HOST_PROXY_INTERFACES)

ecy_hsm_Csai_ErrorT ecy_HSM_GetOpStatus(ecy_hsm_Csai_JobHandleT hJob, HSM_PortStatusT* pStatus)
{
    return ecy_HSM_ReadOpStatus(hJob, pStatus, ecy_hsm_OPT_STAT_IDLE | ecy_hsm_OPT_RESET_ERR);
}

ecy_hsm_Csai_ErrorT ecy_HSM_ReadOpStatus(ecy_hsm_Csai_JobHandleT hJob, HSM_PortStatusT* pStatus, uint32 options)
{
#if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED)
    uint32              elapsedValue;
#endif
    ecy_hsm_Csai_ErrorT errorCode = HSM_CheckHsmCoreStarted();

    /* Check both for CSAI_SUCCESS and NULL_PTR, so the first errorCode is not hidden by the second */
    if ((ecy_hsm_CSAI_SUCCESS == errorCode) && (NULL_PTR == pStatus))
    {
        errorCode = ecy_hsm_CSAI_ERR_INVALID_PARAM;
    }

    if (errorCode == ecy_hsm_CSAI_SUCCESS)
    {

        /* This check is vital because a failed attempt to schedule a job will result in a job handle of
           CSAI_INVALID_JOB_HANDLE    */
        if (hJob >= maxHostHsmSessions)
        {
            *pStatus  = HSM_STATUS_COMPLETE;
            errorCode = ecy_hsm_CSAI_ERR_INVALID_HANDLE;
        }
        else
        {
#if (COMPILER == COMPILER_TASKING)
/* Suppress TASKING compiler warning about errorCode being always SUCCESS, since the errorCode can change based on feature switches */
#pragma warning 549
#endif
            /* Get access to the HSM Bridge */
            errorCode = ecy_HSM_GetBridgeResource();
            /* PRQA S 2995, 2991 1 */ /* <Deviation: control flow depends on defines */
            if (ecy_hsm_CSAI_SUCCESS == errorCode)
#if (COMPILER == COMPILER_TASKING)
#pragma warning restore
#endif
            {
                /** If the operation has just completed, change the status to idle and report the operation's error code
                 * or if the operation is idle but a recent error is still present in bridge (rationale: an error before scheduling
                 * will cause that the status is IDLE, but opErrorCode will contain an error, that we want to return to the
                 * caller function) */
                *pStatus = host2HSM_BridgePorts[hJob].status;
#if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED)
                ecy_hsm_pCalloutGetElapsedCounterValue(host2HSM_BridgePortsTimeoutStamp[hJob], &elapsedValue);
#endif
                if ((HSM_STATUS_COMPLETE == *pStatus) || (HSM_STATUS_IDLE == *pStatus))
                {
#if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED)
                    /* first check if an error occurs at the operation request.*/
                    errorCode = host2HSM_BridgePorts[hJob].requestErrorCode;

                    /* If the request returned an error, clear the port status down to HSM_STATUS_IDLE  */
                    /* Any in-progress job will have been cancelled by the core */
                    if (ecy_hsm_CSAI_SUCCESS != errorCode)
                    {
                        if ((options & ecy_hsm_OPT_STAT_IDLE) != 0U)
                        {
                            host2HSM_BridgePorts[hJob].status = HSM_STATUS_IDLE;
                        }
                        // if option to reset error code allowed
                        if ((options & ecy_hsm_OPT_RESET_ERR) != 0U)
                        {
                            host2HSM_BridgePorts[hJob].opErrorCode = ecy_hsm_CSAI_SUCCESS;
                            host2HSM_BridgePorts[hJob].requestErrorCode = ecy_hsm_CSAI_SUCCESS;
                        }
                    }

#endif /* #if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED)*/
                    /* PRQA S 2995, 2991 1 */ /* <Deviation: control flow depends on defines */
#if (COMPILER == COMPILER_TASKING)
/* Suppress TASKING compiler warning about errorCode being always SUCCESS. This is not correct since the errorCode can change based on feature
 * switches */
#pragma warning 549
#endif
                    if (errorCode == ecy_hsm_CSAI_SUCCESS)
#if (COMPILER == COMPILER_TASKING)
#pragma warning restore
#endif
                    {
                        errorCode = host2HSM_BridgePorts[hJob].opErrorCode;
                        // if option to reset state to idle is allowed
                        if ((options & ecy_hsm_OPT_STAT_IDLE) != 0U)
                        {
                            host2HSM_BridgePorts[hJob].status = HSM_STATUS_IDLE;
                        }
                        // if option to reset error code allowed
                        if ((options & ecy_hsm_OPT_RESET_ERR) != 0U)
                        {
                            host2HSM_BridgePorts[hJob].opErrorCode = ecy_hsm_CSAI_SUCCESS;
                        }
                        ecy_hsm_ListDiagnosticValues();
                    }
                }
#if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED)
                else if (HSM_STATUS_TRANSMIT_JOB == *pStatus)
                {
                    if (elapsedValue >= ecy_HSM_PROXY_DELAY)
                    {
                        errorCode = ecy_hsm_CSAI_ERR_TIMEOUT;

                        if ((options & ecy_hsm_OPT_STAT_IDLE) != 0U)
                        {
                            host2HSM_BridgePorts[hJob].status = HSM_STATUS_IDLE;
                        }

                        if ((options & ecy_hsm_OPT_RESET_ERR) != 0U)
                        {
                            host2HSM_BridgePorts[hJob].opErrorCode = ecy_hsm_CSAI_SUCCESS;
                        }
                    }
                }
#endif
                else
                {
                    /* nothing to do */
                }

                /* Bridge Port UnLock Measurement Point */
                ecy_HSM_RELEASE_BRIDGE_PORT(errorCode);
            }
        }
    }
    return errorCode;
    /* PRQA S 6004 1 */ /* Justification: Refactoring due to cyclomatic complexity makes this code less readable */
} /* PRQA S 6009 1 */ /*< Justification: The if-statement exceeding the limit doesn't make this function less readable. Refactoring due to HIS metric
                         LEVEL is not sensible. */

/* PRQA S 1532 2 */ /*  non optimal reference of this function is tested and does not hinder functionality */
/* PRQA S 1503 1 */ /* Justification: Function may also be called from external, for QA-C invisible code */
ecy_hsm_Csai_ErrorT ecy_HSM_GetOpStatusNonConsuming(ecy_hsm_Csai_JobHandleT hJob, HSM_PortStatusT* pStatus)
{
    ecy_hsm_Csai_ErrorT errorCode = HSM_CheckHsmCoreStarted();

    /* Check both for CSAI_SUCCESS and NULL_PTR, so the first errorCode is not hidden by the second */
    if ((ecy_hsm_CSAI_SUCCESS == errorCode) && (NULL_PTR == pStatus))
    {
        errorCode = ecy_hsm_CSAI_ERR_INVALID_PARAM;
    }

    if (errorCode == ecy_hsm_CSAI_SUCCESS)
    {
        /* This check is vital because a failed attempt to schedule a job will result in a job handle of CSAI_INVALID_JOB_HANDLE    */
        if (hJob >= maxHostHsmSessions)
        {
            *pStatus  = HSM_STATUS_COMPLETE;
            errorCode = ecy_hsm_CSAI_ERR_INVALID_HANDLE;
        }
        else
        {
#if (COMPILER == COMPILER_TASKING)
/* Suppress TASKING compiler warning about errorCode being always SUCCESS, since the errorCode can change based on feature switches */
#pragma warning 549
#endif
            /* Get access to the HSM Bridge */
            errorCode = ecy_HSM_GetBridgeResource();
            /* PRQA S 2995, 2991 1 */ /* <Deviation: control flow depends on defines */
            if (ecy_hsm_CSAI_SUCCESS == errorCode)
#if (COMPILER == COMPILER_TASKING)
#pragma warning restore
#endif
            {
                *pStatus = host2HSM_BridgePorts[hJob].status;
                /* Release the bridge ports */
#if (ecy_hsm_ENABLE_RESOURCE_ERROR_HANDLING == ENABLED)
                errorCode = ecy_HSM_ReleaseBridgeResource();
#else
                (void)ecy_HSM_ReleaseBridgeResource();
#endif
            }
        }
    }

    return (errorCode);
}

/* PRQA S 1532 2 */ /* non optimal reference of this function is tested and does not hinder functionality */
/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_Proxy */
boolean ecy_HSM_IsOpFinishedOK(ecy_hsm_Csai_JobHandleT hJob)
{
    boolean             retval = FALSE;
    ecy_hsm_Csai_ErrorT errorCode;

    /* This check is vital because a failed attempt to schedule a job will result in a job handle of
       CSAI_INVALID_JOB_HANDLE    */
    if ((HSM_CheckHsmCoreStarted() != ecy_hsm_CSAI_SUCCESS) || (hJob >= maxHostHsmSessions))
    {
        retval = FALSE;
    }
    else
    {
#if (COMPILER == COMPILER_TASKING)
/* Suppress TASKING compiler warning about errorCode being always SUCCESS, since the errorCode can change based on feature switches */
#pragma warning 549
#endif
        /* Get access to the HSM Bridge */
        errorCode = ecy_HSM_GetBridgeResource();
        /* PRQA S 2995, 2991 1 */ /* <Deviation: control flow depends on defines */
        if (ecy_hsm_CSAI_SUCCESS == errorCode)
#if (COMPILER == COMPILER_TASKING)
#pragma warning restore
#endif
        {
            /* If the operation has just completed, change the status to IDLE   */
            /* If completed or idle, return TRUE                                */
            if ((HSM_STATUS_COMPLETE == host2HSM_BridgePorts[hJob].status) || (HSM_STATUS_IDLE == host2HSM_BridgePorts[hJob].status))
            {
                host2HSM_BridgePorts[hJob].status = HSM_STATUS_IDLE;
                if (ecy_hsm_CSAI_SUCCESS == host2HSM_BridgePorts[hJob].opErrorCode)
                {
                    retval = TRUE;
                }
                else
                {
                    retval = FALSE;
                }
            }

            /* Release the bridge ports */
#if (ecy_hsm_ENABLE_RESOURCE_ERROR_HANDLING == ENABLED)
            errorCode = ecy_HSM_ReleaseBridgeResource();
            if (ecy_hsm_CSAI_SUCCESS != errorCode)
            {
                retval = FALSE;
            }
#else
            (void)ecy_HSM_ReleaseBridgeResource();
#endif
        }
    }

    return (retval);
}

/* PRQA S 1532 2 */ /* non optimal reference of this function is tested and does not hinder functionality */
/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_Proxy */
ecy_hsm_Csai_ErrorT ecy_HSM_GetOpCode(ecy_hsm_Csai_JobHandleT hJob)
{
    ecy_hsm_Csai_ErrorT errorCode = HSM_CheckHsmCoreStarted();

    if (errorCode == ecy_hsm_CSAI_SUCCESS)
    {

        /* This check is vital because a failed attempt to schedule a job will result in a
           job handle of CSAI_INVALID_JOB_HANDLE    */
        if (hJob >= maxHostHsmSessions)
        {
            errorCode = ecy_hsm_CSAI_ERR_INVALID_HANDLE;
        }
        else if (HSM_STATUS_IDLE == host2HSM_BridgePorts[hJob].status)
        {
            errorCode = host2HSM_BridgePorts[hJob].opErrorCode | ecy_hsm_CSAI_ERR_FLAG_PREVIOUS_OP;
        }
        else
        {
            errorCode = ecy_hsm_CSAI_FC_PENDING;
        }
    }
    return (errorCode);
}

/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_Proxy */
ecy_hsm_Csai_ErrorT ecy_HSM_WaitForOpToComplete(ecy_hsm_Csai_JobHandleT hJob, uint16 millisecondsToWait)
{
    uint32 startingValue;
    uint32 elapsedValue;
    uint32 delayTimeout;

    HSM_PortStatusT status = HSM_STATUS_IDLE;

    ecy_hsm_Csai_ErrorT errorCode = HSM_CheckHsmCoreStarted();

    delayTimeout = (uint32)millisecondsToWait * ecy_hsm_COUNTER_VALUE_TIMEBASE;

    if (ecy_hsm_CSAI_SUCCESS == errorCode)
    {
        if ((NULL_PTR == ecy_hsm_pCalloutGetCounterValue) || (NULL_PTR == ecy_hsm_pCalloutGetElapsedCounterValue))
        {
            errorCode = ecy_hsm_CSAI_ERR_NULL_CALLOUT;
        }
    }

    if (errorCode == ecy_hsm_CSAI_SUCCESS)
    {
        ecy_hsm_pCalloutGetCounterValue(&startingValue);
        do
        {
            errorCode = ecy_HSM_GetOpStatus(hJob, &status);
            ecy_hsm_pCalloutGetElapsedCounterValue(startingValue, &elapsedValue);
        }
        while ((status != HSM_STATUS_COMPLETE) && (elapsedValue < delayTimeout));

        if (status != HSM_STATUS_COMPLETE)
        {
            errorCode = ecy_hsm_CSAI_ERR_TIMEOUT;
        }
    }
    return (errorCode);
}

/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_Proxy */
ecy_hsm_Csai_ErrorT ecy_HSM_CancelOp(ecy_hsm_Csai_SessionHandleT hSession)
{
    uint32 startingValue;
    uint32 elapsedValue;

    ecy_hsm_Csai_ErrorT errorCode = HSM_CheckHsmCoreStarted();

    /* Check for both CSAI_SUCCESS and MAX_HOST_HSM_SESSION to make sure the previous errorCode will not be hidden */
    if ((ecy_hsm_CSAI_SUCCESS == errorCode) && (maxHostHsmSessions <= hSession))
    {
        errorCode = ecy_hsm_CSAI_ERR_INVALID_PARAM;
    }

    if ((ecy_hsm_CSAI_SUCCESS == errorCode)
        && ((NULL_PTR == ecy_hsm_pCalloutGetCounterValue) || (NULL_PTR == ecy_hsm_pCalloutGetElapsedCounterValue)))
    {
        errorCode = ecy_hsm_CSAI_ERR_NULL_CALLOUT;
    }

    if (errorCode == ecy_hsm_CSAI_SUCCESS)
    {
#if (COMPILER == COMPILER_TASKING)
/* Suppress TASKING compiler warning about errorCode being always SUCCESS, since the errorCode can change based on feature switches */
#pragma warning 549
#endif
        /* Get access to the HSM Bridge */
        errorCode = ecy_HSM_GetBridgeResource();
        /* PRQA S 2995, 2991 1 */ /* <Deviation: control flow depends on defines */
        if (ecy_hsm_CSAI_SUCCESS == errorCode)
#if (COMPILER == COMPILER_TASKING)
#pragma warning restore
#endif
        {

            ecy_hsm_HsmMCAL_CancelOp(hSession);

            /* Wait for response */
            ecy_hsm_pCalloutGetCounterValue(&startingValue);
            do
            {
                ecy_hsm_pCalloutGetElapsedCounterValue(startingValue, &elapsedValue);
            }
            while ((FALSE == ecy_hsm_HsmMCAL_IsOperationCancelled()) && (elapsedValue < ecy_HSM_PROXY_DELAY));

            if (FALSE == ecy_hsm_HsmMCAL_IsOperationCancelled())
            {
                errorCode = ecy_hsm_CSAI_ERR_TIMEOUT;
            }

            /* Release the bridge ports */
            ecy_HSM_RELEASE_BRIDGE_PORT(errorCode)
        }
    }
    return (errorCode);
}

/* [$Satisfies $DD 1019] */
/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_Proxy */
ecy_hsm_Csai_ErrorT ecy_HSM_Release(void)
{
    ecy_hsm_Csai_ErrorT errorCode;
#if (COMPILER == COMPILER_TASKING)
/* Suppress TASKING compiler warning about errorCode being always SUCCESS, since the errorCode can change based on feature switches */
#pragma warning 549
#endif
    /* Get access to the HSM Bridge */
    errorCode = ecy_HSM_GetBridgeResource();

    /* PRQA S 2995, 2991 1 */ /* <Deviation: control flow depends on defines */
    if (ecy_hsm_CSAI_SUCCESS == errorCode)
#if (COMPILER == COMPILER_TASKING)
#pragma warning restore
#endif
    {
        errorCode = ecy_hsm_HsmMCAL_Release();
    }

    /* Release access to the HSM Bridge */
    ecy_HSM_RELEASE_BRIDGE_PORT(errorCode)

    return (errorCode);
}

/* [$Satisfies $DD 1020] */
/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_Proxy */
ecy_hsm_Csai_ErrorT ecy_HSM_DoMaintenance(void)
{
    uint32              startingValue;
    uint32              elapsedValue;
    ecy_hsm_Csai_ErrorT errorCode;
    static boolean      isMaintenanceRunning = FALSE; /* state of an on-going maintenance operation */

    /* abort if the HSM is in BOOTLOADER mode */
    if (HSM_MODE_BOOTLOADER == ecy_HSM_GetMode())
    {
        errorCode = ecy_hsm_CSAI_ERR_NOT_SUPPORTED;
    }
    else
    {
        /* abort immediately if the HSM Core App is not running */
        errorCode = HSM_CheckHsmCoreStarted();

        if (errorCode == ecy_hsm_CSAI_SUCCESS)
        {
#if (COMPILER == COMPILER_TASKING)
/* Suppress TASKING compiler warning about errorCode being always SUCCESS, since the errorCode can change based on feature switches */
#pragma warning 549
#endif
            /* Get access to the HSM Bridge */
            errorCode = ecy_HSM_GetBridgeResource();
            /* PRQA S 2995, 2991 1 */ /* <Deviation: control flow depends on defines */
            if (ecy_hsm_CSAI_SUCCESS == errorCode)
#if (COMPILER == COMPILER_TASKING)
#pragma warning restore
#endif
            {
                /* check if this is the first call (maintenance was not started yet on the HSM) */
                if (isMaintenanceRunning == FALSE)
                {
                    /* first call: trigger a HSM maintenance request */
                    (void)ecy_hsm_HsmMCAL_DoMaintenance();

                    /* get point in time when request was made */
                    errorCode = ecy_HSM_GetCounterValue(&startingValue);

                    /* continue if everything was successful so far */
                    if (ecy_hsm_CSAI_SUCCESS == errorCode)
                    {
                        /* wait for the HSM to accept the request, but only for a short maximal time */
                        do
                        {
                            ecy_hsm_FunctionIRQHandling();
                            /* get elapsed time interval since request was made */
                            errorCode = ecy_HSM_GetElapsedCounterValue(startingValue, &elapsedValue);

                            /* continue if everything was successful so far */
                            if (ecy_hsm_CSAI_SUCCESS == errorCode)
                            {
                                /* HSM Core App still running? */
                                errorCode = HSM_CheckHsmCoreStarted();
                            }
                        }
                        while ((FALSE == ecy_hsm_HsmMCAL_IsMaintenanceStarted()) && (ecy_hsm_CSAI_SUCCESS == errorCode)
                               && (ecy_HSM_PROXY_DELAY > elapsedValue));

                        /* has the HSM accepted the maintenance request? */
                        if (TRUE == ecy_hsm_HsmMCAL_IsMaintenanceStarted())
                        {
                            /* maintenance has started, inform Host that it shall wait and poll */
                            errorCode            = ecy_hsm_CSAI_FC_PENDING;
                            isMaintenanceRunning = TRUE;
                        }
                        else if (ecy_hsm_CSAI_SUCCESS == errorCode)
                        {
                            /* HSM is still running, this is a timeout error */
                            errorCode = ecy_hsm_CSAI_ERR_TIMEOUT;
                        }
                        else
                        {
                            /* the errorCode returned is the one set by the previous call to HSM_CheckHsmCoreStarted() */
                        }
                    }
                }
                else /* maintenance is running on the HSM, check its status and report it */
                {
                    errorCode = HSM_CheckHsmCoreStarted();

                    if (ecy_hsm_HsmMCAL_IsMaintenanceDone() == TRUE)
                    {
                        /* maintenance has completed */
                        errorCode            = ecy_hsm_CSAI_SUCCESS;
                        isMaintenanceRunning = FALSE;
                    }
                    else if (errorCode == ecy_hsm_CSAI_SUCCESS)
                    {
                        /* maintenance is still running, HSM Ok, host shall retry later */
                        errorCode = ecy_hsm_CSAI_FC_PENDING;
                    }
                    else
                    {
                        /* HSM has is not in the expected mode, abort maintenance request */
                        isMaintenanceRunning = FALSE;
                    }
                }
                /* Release access to the HSM Bridge */
                ecy_HSM_RELEASE_BRIDGE_PORT(errorCode)
            }
        }
    }
    return (errorCode);
    /* PRQA S 6004 1 */ /*< Justification: Number of if-else-statements is fundamental to this function's purpose */
} /* PRQA S 6009 */ /*< Justification: The if-statement exceeding the limit doesn't make this function less readable. Refactoring due to HIS metric
                       LEVEL is not sensible. */

/* PRQA S 1532 2 */ /*  non optimal reference of this function is tested and does not hinder functionality */
/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_Proxy */
ecy_hsm_Csai_ErrorT ecy_HSM_GetCounterValue(uint32* pStartingValue)
{
    ecy_hsm_Csai_ErrorT errorCode = ecy_hsm_CSAI_SUCCESS;
    if (NULL_PTR == pStartingValue)
    {
        errorCode = ecy_hsm_CSAI_ERR_INVALID_PARAM;
    }
    else if (NULL_PTR == ecy_hsm_pCalloutGetCounterValue)
    {
        errorCode = ecy_hsm_CSAI_ERR_NULL_CALLOUT;
    }
    else
    {
        ecy_hsm_pCalloutGetCounterValue(pStartingValue);
    }
    return (errorCode);
}

/* PRQA S 1532 2 */ /*  non optimal reference of this function is tested and does not hinder functionality */
/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_Proxy */
ecy_hsm_Csai_ErrorT ecy_HSM_GetElapsedCounterValue(uint32 value, uint32* pElapsedValue)
{
    ecy_hsm_Csai_ErrorT errorCode = ecy_hsm_CSAI_SUCCESS;
    if (NULL_PTR == pElapsedValue)
    {
        errorCode = ecy_hsm_CSAI_ERR_INVALID_PARAM;
    }
    else if (NULL_PTR == ecy_hsm_pCalloutGetElapsedCounterValue)
    {
        errorCode = ecy_hsm_CSAI_ERR_NULL_CALLOUT;
    }
    else
    {
        ecy_hsm_pCalloutGetElapsedCounterValue(value, pElapsedValue);
    }
    return (errorCode);
}
/* PRQA S 1505 1 */ /* This function getting called in other files based defines from configuration */
ecy_hsm_Csai_ErrorT ecy_HSM_GetBridgeResource(void)
{
    ecy_hsm_Csai_ErrorT errorCode = ecy_hsm_CSAI_SUCCESS;

    /* Get access to the HSM Bridge */
    if (pCalloutGetResource != NULL_PTR)
    {
        pCalloutGetResource();
#if (ecy_hsm_ENABLE_RESOURCE_ERROR_HANDLING == ENABLED)
        if (FALSE == resourceIsLocked)
        {
            resourceIsLocked = TRUE;
        }
        /* Resource was not previously released but pCalloutGetResource returned -> bridge resource was locked twice */
        else
        {
            errorCode = ecy_hsm_CSAI_ERR_RESOURCE_ALREADY_LOCKED_UNLOCKED;
        }
#endif /* #if (ecy_hsm_ENABLE_RESOURCE_ERROR_HANDLING == ENABLED) */
    }
    return errorCode;
}
/* PRQA S 1505 1 */ /* This function getting called in other files based defines from configuration */
ecy_hsm_Csai_ErrorT ecy_HSM_ReleaseBridgeResource(void)
{
    ecy_hsm_Csai_ErrorT errorCode = ecy_hsm_CSAI_SUCCESS;

    /* Release access to the HSM Bridge */
    if (pCalloutReleaseResource != NULL_PTR)
    {
        pCalloutReleaseResource();
#if (ecy_hsm_ENABLE_RESOURCE_ERROR_HANDLING == ENABLED)
        if (TRUE == resourceIsLocked)
        {
            resourceIsLocked = FALSE;
        }
        /* Resource was not previously locked but release was called */
        else
        {
            errorCode = ecy_hsm_CSAI_ERR_RESOURCE_ALREADY_LOCKED_UNLOCKED;
        }
#endif /* #if (ecy_hsm_ENABLE_RESOURCE_ERROR_HANDLING == ENABLED) */
    }
    return errorCode;
}

volatile ecy_hsm_Host_TB_VerifTableT* HSM_GetTBVerifTable(void)
{
    return &verifTableMirror;
}

/* [$Satisfies $DD 123] */
/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_Proxy */
ecy_hsm_Csai_ErrorT ecy_hsm_Mgmt_SuspendStart(uint32 numMsTimeout, uint32* pFirstChallengeVal)

{
    ecy_hsm_Csai_ErrorT errorCode;

    /* perform parameter sanity check */
    if ((pFirstChallengeVal == NULL_PTR) || (0U == numMsTimeout))
    {
        errorCode = ecy_hsm_CSAI_ERR_INVALID_PARAM;
    }
    else
    {
        /* abort immediately if the HSM Core App is not running */
        errorCode = HSM_CheckHsmCoreStarted();

        if (errorCode == ecy_hsm_CSAI_SUCCESS)
        {
            /* prepare the operation parameters */
            suspendOpParams.functionId = HSM_SUSP_START;

            /* execute the suspend operation */
            errorCode = ecy_hsm_Mgmt_SuspendOpExec(numMsTimeout);

            /* Check if we are really in suspend mode */
            /* PRQA S 3415 2 */ /* Deviation: rule_13.5_1 */ /* Justification: ecy_HSM_GetMode() only reads the status and
                                                              * does no write operations, that might interfere with this function. */
            if ((errorCode == ecy_hsm_CSAI_SUCCESS) && (HSM_MODE_SUSPENDED != ecy_HSM_GetMode()))
            {
                /* Suspend request was successful, but the suspend mode is not set for some reason. Return with an error. */
                errorCode = ecy_hsm_CSAI_ERR_INVALID_STATE;
            }

            /* return the HSM-provided challenge */
            *pFirstChallengeVal = suspendOpParams.challengeVal;
        }
    }

    return (errorCode);
}

/* [$Satisfies $DD 124] */
/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_Proxy */
ecy_hsm_Csai_ErrorT ecy_hsm_Mgmt_SuspendKeep(uint32 numMsTimeout, uint32 responseVal, uint32* pNewChallengeVal)
{
    ecy_hsm_Csai_ErrorT errorCode;

    /* perform parameter sanity check */
    if ((pNewChallengeVal == NULL_PTR) || (0U == numMsTimeout))
    {
        errorCode = ecy_hsm_CSAI_ERR_INVALID_PARAM;
    }
    else if (HSM_MODE_SUSPENDED != ecy_HSM_GetMode())
    {
        /* abort immediately if the HSM is not suspended */
        errorCode = ecy_hsm_CSAI_ERR_INVALID_STATE;
    }
    else
    {
        /* prepare the operation parameters */
        suspendOpParams.functionId  = HSM_SUSP_KEEP;
        suspendOpParams.responseVal = responseVal;
        /* execute the suspend operation */
        errorCode = ecy_hsm_Mgmt_SuspendOpExec(numMsTimeout);

        /* return the HSM-provided challenge */
        *pNewChallengeVal = suspendOpParams.challengeVal;
    }
    return (errorCode);
}

/* [$Satisfies $DD 125] */
/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_Proxy */
ecy_hsm_Csai_ErrorT ecy_hsm_Mgmt_SuspendLeave(uint32 numMsTimeout)
{
    ecy_hsm_Csai_ErrorT errorCode;

    /* abort immediately if the HSM is not suspended or the numMsTimeout is invalid */
    if (0U == numMsTimeout)
    {
        errorCode = ecy_hsm_CSAI_ERR_INVALID_PARAM;
    }
    else if (HSM_MODE_SUSPENDED != ecy_HSM_GetMode())
    {
        errorCode = ecy_hsm_CSAI_ERR_INVALID_STATE;
    }
    else
    {
        /* prepare the operation parameters */
        suspendOpParams.functionId = HSM_SUSP_LEAVE;
        /* execute the suspend operation */
        errorCode = ecy_hsm_Mgmt_SuspendOpExec(numMsTimeout);
    }
    return (errorCode);
}

/* [$Satisfies $DD 1464] */
uint32 ecy_hsm_TbGetVerifTableMaxNumOfElementsHSM(void)
{
    return verifTableMaxNumOfElementsHSM;
}

/* [$Satisfies $DD 2627] */
/* PRQA S 3673 2 */ /* <Justification: Function fits a generic interface, pointer to const not always feasible */
/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_Proxy */
ecy_hsm_Csai_ErrorT ecy_hsm_SecDebug_ConfigureBuffer(HSM_SecureDebugConfigureParamsT* pSecureDebugParam)
{
    ecy_hsm_Csai_ErrorT errorCode;
#if(   (ECY_HSM_VMS_ARCH_GROUP == ECY_HSM_VMS_ARCH_GROUP_RH850_V1)      \
    || (ECY_HSM_VMS_ARCH_GROUP == ECY_HSM_VMS_ARCH_GROUP_RH850_V2)      \
    || (ECY_HSM_VMS_ARCH_GROUP == ECY_HSM_VMS_ARCH_GROUP_RH850_V4))
    uint32              startingValue;
    uint32              elapsedValue;

    /* perform parameter sanity check */
    if ((pSecureDebugParam == NULL_PTR) || (pSecureDebugParam->pDebugDataBuffer == NULL_PTR)\
         || (pSecureDebugParam->pChallengeBuffer == NULL_PTR) || (pSecureDebugParam->pResponseBuffer == NULL_PTR)\
         || (pSecureDebugParam->debugDataBufferSize == 0U) || (pSecureDebugParam->challengeBufferSize == 0U )\
         || (pSecureDebugParam->responseBufferSize == 0U))
    {
        errorCode = ecy_hsm_CSAI_ERR_INVALID_PARAM;
    }
    else
    {
        /* abort if the HSM is in BOOTLOADER mode */
        if (HSM_MODE_BOOTLOADER == ecy_HSM_GetMode())
        {
            errorCode = ecy_hsm_CSAI_ERR_NOT_SUPPORTED;
        }
        else
        {
            /* abort immediately if the HSM Core App is not running */
            errorCode = HSM_CheckHsmCoreStarted();

            if (errorCode == ecy_hsm_CSAI_SUCCESS)
            {
    #if (COMPILER == COMPILER_TASKING)
    /* Suppress TASKING compiler warning about errorCode beeing always SUCCESS.
    * This is not correct since the errorCode can change based on feature switches */
    #pragma warning 549
    #endif
                /* Get access to the HSM Bridge */
                errorCode = ecy_HSM_GetBridgeResource();
                /* PRQA S 2995, 2991 1 */ /* <Deviation: control flow depends on defines */
                if (ecy_hsm_CSAI_SUCCESS == errorCode)
    #if (COMPILER == COMPILER_TASKING)
    #pragma warning restore
    #endif
                {
                    /* Trigger a Secure Debug buffer configuration request */
                    (void)ecy_hsm_HsmMCAL_DoSecureDebugConfigureOp(pSecureDebugParam);

                    /* get point in time when request was made */
                    errorCode = ecy_HSM_GetCounterValue(&startingValue);

                    /* continue if everything was successful so far */
                    if (ecy_hsm_CSAI_SUCCESS == errorCode)
                    {
                        /* wait for the HSM to accept the request, but only for a short maximal time */
                        do
                        {
                            ecy_hsm_FunctionIRQHandling();
                            /* get elapsed time interval since request was made */
                            errorCode = ecy_HSM_GetElapsedCounterValue(startingValue, &elapsedValue);

                            /* continue if everything was successful so far */
                            if (ecy_hsm_CSAI_SUCCESS == errorCode)
                            {
                                /* HSM Core App still running? */
                                errorCode = HSM_CheckHsmCoreStarted();
                            }
                        }
                        while ((FALSE == ecy_hsm_HsmMCAL_IsSecureDebugConfigureDone()) && (ecy_hsm_CSAI_SUCCESS == errorCode)
                                && (ecy_HSM_PROXY_DELAY > elapsedValue));

                        if (TRUE == ecy_hsm_HsmMCAL_IsSecureDebugConfigureDone())
                        {
                            /* request completed */
                            errorCode = ecy_hsm_CSAI_SUCCESS;
                        }
                        else if (ecy_hsm_CSAI_SUCCESS == errorCode)
                        {
                            /* return timeout error */
                            errorCode = ecy_hsm_CSAI_ERR_TIMEOUT;
                        }
                        else
                        {
                            /* the errorCode returned is the one set by the previous call to HSM_CheckHsmCoreStarted() */
                        }
                    }

                    /* Release access to the HSM Bridge */
                    ecy_HSM_RELEASE_BRIDGE_PORT(errorCode)
                }
            }
        }
    }
#else
    CSAI_PARAM_UNUSED(pSecureDebugParam);
    errorCode = ecy_hsm_CSAI_ERR_NOT_SUPPORTED;
#endif /* #if(   (ECY_HSM_VMS_ARCH_GROUP == ECY_HSM_VMS_ARCH_GROUP_RH850_V1)    \
            || (ECY_HSM_VMS_ARCH_GROUP == ECY_HSM_VMS_ARCH_GROUP_RH850_V2)      \
            || (ECY_HSM_VMS_ARCH_GROUP == ECY_HSM_VMS_ARCH_GROUP_RH850_V4)) */

    return (errorCode);
    /* PRQA S 6004 3 */ /*< Justification: Number of if-else-statements is fundamental to this function's purpose */
    /* PRQA S 6006 2 */ /*< Justification:  The function is good structured(readable and maintainable) */
    /* PRQA S 6009 1 */ /*< Justification:  The function is good structured(readable and maintainable) */
}

/* *** private implementation  ****************************************************************/

/**
 * Execute a suspended mode operation
 *
 * @details
 * This function uses a dedicated communication protocol (not session-based)
 *
 * @param[in] numMsTimeout   Pointer to a location where to return the error code (if NULL_PTR, no error code is returned).
 *
 * @returns
 * - @ref ecy_hsm_CSAI_ERR_TIMEOUT  A communication timeout occurred
 * - other                          The error code returned by the HSM
 */
static ecy_hsm_Csai_ErrorT ecy_hsm_Mgmt_SuspendOpExec(uint32 numMsTimeout)
{
    ecy_hsm_Csai_ErrorT errorCode;
    uint32              startingValue;
    uint32              elapsedValue;
    uint32              delayTimeout = numMsTimeout * ecy_hsm_COUNTER_VALUE_TIMEBASE;

    /* Counter callouts must be valid, otherwise the timeout mechanism won't work */
    if ((NULL_PTR == ecy_hsm_pCalloutGetCounterValue) || (NULL_PTR == ecy_hsm_pCalloutGetElapsedCounterValue))
    {
        errorCode = ecy_hsm_CSAI_ERR_NULL_CALLOUT;
    }
    else
    {
#if (COMPILER == COMPILER_TASKING)
/* Suppress TASKING compiler warning about errorCode being always SUCCESS, since the errorCode can change based on feature switches */
#pragma warning 549
#endif
        /* Get access to the HSM Bridge */
        errorCode = ecy_HSM_GetBridgeResource();
        /* PRQA S 2995, 2991 1 */ /* <Deviation: control flow depends on defines */
        if (ecy_hsm_CSAI_SUCCESS == errorCode)
#if (COMPILER == COMPILER_TASKING)
#pragma warning restore
#endif
        {
            /* Trigger a HSM suspended mode request */
            (void)ecy_hsm_HsmMCAL_DoSuspendOp(&suspendOpParams);
            /* Wait for the HSM to accept the request, but only for a short maximal time */
            ecy_hsm_pCalloutGetCounterValue(&startingValue);
            do
            {
                ecy_hsm_pCalloutGetElapsedCounterValue(startingValue, &elapsedValue);
            }
            while ((FALSE == ecy_hsm_HsmMCAL_IsSuspendOpStarted()) && (elapsedValue < ecy_HSM_PROXY_DELAY));

            /* Has the HSM accepted the suspend request? */
            if (ecy_hsm_HsmMCAL_IsSuspendOpStarted() == TRUE)
            {
                /* Wait for the HSM to complete the request, but only for the user-specified maximal time */
                ecy_hsm_pCalloutGetCounterValue(&startingValue);
                do
                {
                    ecy_hsm_pCalloutGetElapsedCounterValue(startingValue, &elapsedValue);
                }
                while ((FALSE == ecy_hsm_HsmMCAL_IsSuspendOpDone()) && (elapsedValue < delayTimeout));

                if (ecy_hsm_HsmMCAL_IsSuspendOpDone() == TRUE)
                {
                    /* Suspend Request is done, get delivered error */
                    errorCode = suspendOpParams.opErrorCode;
                }
                else
                {
                    /* Suspend Request was not done in time */
                    errorCode = ecy_hsm_CSAI_ERR_TIMEOUT;
                }
            }
            else
            {
                /* suspend has not started, inform the Host */
                errorCode = ecy_hsm_CSAI_ERR_TIMEOUT;
            }

            /* Release the bridge ports */
            ecy_HSM_RELEASE_BRIDGE_PORT(errorCode)
        }
    }

    return errorCode;
}

/**
 * Check if the HSM is in Bootloader or Core Application mode
 *
 * @details
 * This function is provided to make sure the HSM is in the right mode before sending a CSAI job request to it.
 *
 * @param[out] pError   Pointer to a location where to return the error code (if NULL_PTR, no error code is returned).
 *                      The error code returned can be:
 *                      - @ref ecy_hsm_CSAI_SUCCESS             If the HSM is running in Bootloader or Core Application mode
 *                      - @ref ecy_hsm_CSAI_ERR_HSM_SUSPENDED   If the HSM is in suspended mode
 *                      - @ref ecy_hsm_CSAI_ERR_HSM2HTS_LOCKUP  If the HSM is in an undefined mode (possibly crashed)
 *
 * @returns TRUE if the HSM is running in Bootloader or Core Application mode, FALSE otherwise
 */
static ecy_hsm_Csai_ErrorT HSM_CheckHsmCoreStarted(void)
{
    ecy_hsm_Csai_ErrorT error;

    HSM_ModeT hsmMode = ecy_hsm_HsmMCAL_GetMode();

    if ((HSM_MODE_CORE_APP == hsmMode) || (HSM_MODE_BOOTLOADER == hsmMode))
    {
        error = ecy_hsm_CSAI_SUCCESS;
    }
    else if (HSM_MODE_SUSPENDED == hsmMode)
    {
        /* return a distinct error to inform the caller of the HSM suspended state */
        error = ecy_hsm_CSAI_ERR_HSM_SUSPENDED;
    }
    else if (HSM_MODE_SWITCHING_FROM_CORE_TO_BOOT == hsmMode)
    {
        error = ecy_hsm_CSAI_ERR_SWITCHING_FROM_CORE_TO_BOOT;
    }
    else
    {
        /* return a generic error to inform the caller that the HSM is not in the expected state */
        error = ecy_hsm_CSAI_ERR_HSM2HTS_LOCKUP;
    }

    return error;
}

#if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED)
/* PRQA S 3238 10 */ /* Justification: LOCAL_INLINE is declared as 'static inline', function has NO external linkage. */
LOCAL_INLINE ecy_hsm_Csai_ErrorT ecy_HSM_CheckLoadJobAllowed(void)
{
    ecy_hsm_Csai_ErrorT errorCode;
    errorCode = ecy_HSM_CheckJobTransmit();
    if (ecy_hsm_CSAI_SUCCESS == errorCode)
    {
        errorCode = HSM_CheckHsmCoreStarted();
    }
    return errorCode;
}

/* PRQA S 3238 15 */ /* Justification: LOCAL_INLINE is declared as 'static inline', function has NO external linkage. */
LOCAL_INLINE ecy_hsm_Csai_ErrorT ecy_HSM_CheckOpenSessionCompleted(boolean releaseResource)
{
    ecy_hsm_Csai_ErrorT errorCode = ecy_hsm_CSAI_SUCCESS;
    /* Check if the openSessionStatusNoWaitMode variable is set to TRUE.
    * This condition will be entered if open session is called again before previous open session is completed.*/
    if (openSessionStatusNoWaitMode == TRUE)
    {
        if (ecy_hsm_HsmMCAL_IsSessionOpen() == FALSE)
        {
            if (releaseResource == TRUE)
            {
                /* Release the bridge ports */
                ecy_HSM_RELEASE_BRIDGE_PORT(errorCode)
            }
            /* Return busy if previous open session is not completed */
            errorCode = ecy_hsm_CSAI_FC_BUSY;
        }
    }
    return errorCode;
}
#endif /* #if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED) */

/* Refactored from LoadOp() due to HIS metrics, see description below */
/* PRQA S 3238 113 */ /* LOCAL_INLINE is declared as 'static inline', function has NO external linkage. */
LOCAL_INLINE ecy_hsm_Csai_ErrorT
DoLoadOp(ecy_hsm_Csai_JobHandleT hJob, ecy_hsm_Csai_JobPriorityT priority, HSM_FunctionT function, uint32 paramBlockSize, const void* pParamBlock)
{
    /* PRQA S 2981 1 */ /* Justification: This initialization is needed incase NO WAIT MODE disabled */
    ecy_hsm_Csai_ErrorT errorCode;
    uint32              elapsedValue;
#if (ecy_hsm_CSAI_FS_NO_WAIT_MODE != ENABLED)
    uint32              timeoutDelay;
    uint32              startingValue;
#else
    errorCode = ecy_HSM_CheckLoadJobAllowed();
    if (ecy_hsm_CSAI_SUCCESS == errorCode)
#endif /* #if(ecy_hsm_CSAI_FS_NO_WAIT_MODE != ENABLED) */
    {
#if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED)
        errorCode = ecy_HSM_CheckOpenSessionCompleted(FALSE);
        if (ecy_hsm_CSAI_SUCCESS == errorCode)
#endif /* #if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED) */
        {
            opParams.functionId     = function;
            opParams.opPriority     = priority;
            opParams.paramBlockSize = paramBlockSize;
            /* NULL_PTR == pParamBlock may be intended, just make sure the paramBlockSize is 0 to be compatible with the upcoming memcpy. */
            if ((NULL_PTR == pParamBlock) && (0UL != paramBlockSize))
            {
                errorCode = ecy_hsm_CSAI_ERR_INVALID_PARAM;
            }
            else if ((uint32)HSM_OP_PARAM_BLOCK_SIZE < paramBlockSize)
            {
                errorCode = ecy_hsm_CSAI_ERR_INPUT_TOO_LARGE;
            }
            else if ((NULL_PTR == ecy_hsm_pCalloutGetCounterValue) || (NULL_PTR == ecy_hsm_pCalloutGetElapsedCounterValue))
            {
                errorCode = ecy_hsm_CSAI_ERR_NULL_CALLOUT;
            }
            else
            {
#if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED)
                ecy_hsm_QuickRouteSetSessionToTransmit(hJob, HSM_FUNC_NONE);
#endif
                /* It's OK to pass a NULL_PTR pointer if the length is zero (which it will be)  */
                /* PRQA S 0316 1 */ /* <Deviation: cast is unavoidable and does not affect functionality*/
                (void)ecy_memcpy(opParams.paramBlock, (const uint8*)pParamBlock, paramBlockSize);

                ecy_hsm_HsmMCAL_LoadOp(hJob);

#if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED)
                /* direct check if job transmit ends in error and check timeout value */
                if (HSM_STATUS_TRANSMIT_JOB == host2HSM_BridgePorts[hJob].status)
                {
                    ecy_hsm_pCalloutGetElapsedCounterValue(host2HSM_BridgePortsTimeoutStamp[hJob], &elapsedValue);
                    /* if the HSM is still running, we want to return a timeout error */
                    if (elapsedValue >= ecy_HSM_PROXY_DELAY)
                    {
                        errorCode                              = ecy_hsm_CSAI_ERR_TIMEOUT;
                        host2HSM_BridgePorts[hJob].opErrorCode = ecy_hsm_CSAI_ERR_OP_REQUEST_FAILED;
                        host2HSM_BridgePorts[hJob].status      = HSM_STATUS_IDLE;
                    }
                }
                else
                {
                    errorCode = host2HSM_BridgePorts[hJob].requestErrorCode;

                    /* If the request returned an error, clear the port status down to HSM_STATUS_IDLE  */
                    /* Any in-progress job will have been cancelled by the core */
                    if (ecy_hsm_CSAI_SUCCESS != errorCode)
                    {
                        host2HSM_BridgePorts[hJob].opErrorCode = ecy_hsm_CSAI_ERR_OP_REQUEST_FAILED;
                        host2HSM_BridgePorts[hJob].status      = HSM_STATUS_IDLE;
                    }
                }
#else
                timeoutDelay = ecy_HSM_PROXY_DELAY;
                /* Wait for response */
                ecy_hsm_pCalloutGetCounterValue(&startingValue);
                do
                {
                    ecy_hsm_pCalloutGetElapsedCounterValue(startingValue, &elapsedValue);
                    errorCode = HSM_CheckHsmCoreStarted();
                }
                while ((HSM_STATUS_IDLE == host2HSM_BridgePorts[hJob].status) && (ecy_hsm_CSAI_SUCCESS == errorCode) /* HSM Core App still running? */
                    && (elapsedValue < timeoutDelay));

                errorCode = HSM_CheckHsmCoreStarted();

                if (HSM_STATUS_IDLE == host2HSM_BridgePorts[hJob].status)
                {
                    /* if the HSM is still running, we want to return a timeout error */
                    if (errorCode == ecy_hsm_CSAI_SUCCESS)
                    {
                        errorCode = ecy_hsm_CSAI_ERR_TIMEOUT;
                    }
                    host2HSM_BridgePorts[hJob].opErrorCode = ecy_hsm_CSAI_ERR_OP_REQUEST_FAILED;
                }
                else
                {
                    errorCode = host2HSM_BridgePorts[hJob].requestErrorCode;

                    /* If the request returned an error, clear the port status down to HSM_STATUS_IDLE  */
                    /* Any in-progress job will have been cancelled by the core */
                    if (ecy_hsm_CSAI_SUCCESS != errorCode)
                    {
                        host2HSM_BridgePorts[hJob].opErrorCode = ecy_hsm_CSAI_ERR_OP_REQUEST_FAILED;
                        host2HSM_BridgePorts[hJob].status      = HSM_STATUS_IDLE;
                    }
                }
#endif /* #if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED)*/
            }
        }
    }
    return errorCode;
    /* PRQA S 6009 1 */ /* <Deviation: the number of levels does not make the code unreadable */
}

/**
 * Load an operation onto the HSM.
 *
 * @details OsResource_HsmBridge should be locked before calling this function.
 * Also host2HSM_BridgePorts[hJob].status will be HSM_STATUS_IDLE because that must be checked before calling this.
 * @param hJob Handle to the job that the operation being loaded belongs to (range checked by caller).
 * @param priority Priority that the operation will be run at.
 * @param function Operation function code.
 * @param paramBlockSize Length of the parameters block.
 * @param pParamBlock Pointer to the parameters block.
 * @returns ecy_hsm_CSAI_SUCCESS or error code
 */
static ecy_hsm_Csai_ErrorT
LoadOp(ecy_hsm_Csai_JobHandleT hJob, ecy_hsm_Csai_JobPriorityT priority, HSM_FunctionT function, uint32 paramBlockSize, const void* pParamBlock)
{
    /* make sure the HSM is ready to process the command, i.e. in bootloader or Core Application mode */
    ecy_hsm_Csai_ErrorT errorCode = HSM_CheckHsmCoreStarted();

    if (errorCode == ecy_hsm_CSAI_SUCCESS)
    {

        if ((HSM_STATUS_PENDING == host2HSM_BridgePorts[hJob].status) || (HSM_STATUS_PROCESSING == host2HSM_BridgePorts[hJob].status))
        {
            /* If port status is pending or processing then return ecy_hsm_CSAI_FC_BUSY */
            errorCode = ecy_hsm_CSAI_FC_BUSY;
        }
        else if (paramBlockSize > (uint32)HSM_OP_PARAM_BLOCK_SIZE)
        {
            /* Check that the shared memory area is big enough   */
            errorCode = ecy_hsm_CSAI_ERR_PARAM_BLOCK_TOO_LARGE;
        }
        else
        {
            errorCode = DoLoadOp(hJob, priority, function, paramBlockSize, pParamBlock);
        }
    }
    return (errorCode);
}

/**
 * Initialize the mirror table from host side to set the host version.
 * All entries will be set to a default state to detect if the HSM has initialize all entries.
 *
 */
static void HSM_Configure_MirrorTable(void)
{
    uint32 i;

    ecy_hsm_TbSetVerifTableMaxNumOfElementsHSM(ecy_hsm_CSAI_TB_REF_TABLE_SIZE_LEGACY);

    verifTableMirror.verifTableVersion  = ecy_hsm_CSAI_TB_VER_HOST_PATTERN;
    verifTableMirror.gblVerifStateFlag  = (sint8)ecy_hsm_TB_STATE_HOST_INIT_E;
    verifTableMirror.mnplVerifStateFlag = (sint8)ecy_hsm_TB_STATE_HOST_INIT_E;
    verifTableMirror.verifChainEnded    = FALSE;
    verifTableMirror.numOfElements      = TB_REF_TABLE_SIZE;

    for (i = 0; i < TB_REF_TABLE_SIZE; i++)
    {
        verifTableMirror.verifTableInfoArray[i].swPartAddress        = 0x0U;
        verifTableMirror.verifTableInfoArray[i].swPartLastVerifState = (sint8)ecy_hsm_TB_STATE_HOST_INIT_E;
        verifTableMirror.verifTableInfoArray[i].swPartCurrVerifState = (sint8)ecy_hsm_TB_STATE_HOST_INIT_E;
        verifTableMirror.verifTableInfoArray[i].swPartId             = 0U;
        verifTableMirror.verifTableInfoArray[i].swPartVerifBootMode  = 0U;
    }
}

/**
 * The function read out the number of elements of HSM trusted boot table and call the function ecy_hsm_TbSetVerifTableMaxNumOfElementsHSM
 * to store the value in the global variable @ref verifTableMaxNumOfElementsHSM.
 * A pattern is checked in the trusted boot version information if the HSM will transmit the number of elements.
 * Otherwise it is an legacy HSM with 12 elements.
 *
 */
static void HSM_Check_MirrorTable(void)
{
    volatile ecy_hsm_Host_TB_VerifTableT* pReadVerifTable = HSM_GetTBVerifTable();

    if ((pReadVerifTable->verifTableVersion & ecy_hsm_CSAI_TB_VER_PATTERN_MSK) == ecy_hsm_CSAI_TB_VER_HSM_PATTERN)
    {
        ecy_hsm_TbSetVerifTableMaxNumOfElementsHSM(pReadVerifTable->numOfElements);
    }
    else
    {
        ecy_hsm_TbSetVerifTableMaxNumOfElementsHSM(ecy_hsm_CSAI_TB_REF_TABLE_SIZE_LEGACY);
    }
}

/* [$Satisfies $DD 1389] */
#if (ECY_HSM_VMS_FS_APPLET_SHE_CANCEL == ENABLED)
/* PRQA S 3673 3 */ /* Justification: Function fits a generic interface, pointer to const not always feasible */
ecy_hsm_Csai_ErrorT ecy_HSM_SessionHotSwap(const volatile HSM_PortStatusT** ppStatus,
                                           ecy_hsm_Csai_SessionHandleT*     phSession,
                                           const volatile HSM_PortStatusT** ppStatus_backup,
                                           ecy_hsm_Csai_SessionHandleT*     phSession_backup)
{
    ecy_hsm_Csai_ErrorT         errorCode = ecy_hsm_CSAI_ERR_INVALID_PARAM;
    ecy_hsm_Csai_SessionHandleT hSession_temp;

    if ((phSession != NULL_PTR) && (phSession_backup != NULL_PTR))
    {
        if (ecy_hsm_CSAI_SUCCESS == ecy_HSM_GetSessionStatusPointer(ppStatus, *phSession_backup))
        {
            if (ecy_hsm_CSAI_SUCCESS == ecy_HSM_GetSessionStatusPointer(ppStatus_backup, *phSession))
            {
                hSession_temp     = *phSession;
                *phSession        = *phSession_backup;
                *phSession_backup = hSession_temp;
                errorCode         = ecy_hsm_CSAI_SUCCESS;
            }
            else
            {
                /* In case the 2nd pointer switch fails, the 1st one has to be switched back. */
                (void)ecy_HSM_GetSessionStatusPointer(ppStatus, *phSession);
            }
        }
    }

    return (errorCode);
}
#endif

/* [$Satisfies $DD 1385] Check if the HSM is busy with a job that is pending or being processed */
/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_Proxy */
ecy_hsm_Csai_ErrorT ecy_hsm_IsHsmBusy(void)
{
    uint32                  sessionCounter;
    uint8                   maxNumberOfHostHsmSessions;
    ecy_hsm_Csai_ErrorT     errorCode;
    HSM_HostSideBridgePortT port;
    HSM_ModeT               hsmMode;

    /* Get the HSM mode and accordingly update the maximum number of available session */
    hsmMode = ecy_HSM_GetMode();
    if (HSM_MODE_CORE_APP == hsmMode)
    {
        maxNumberOfHostHsmSessions = CYCURHSM_SC_MAX_HOST_HSM_SESSIONS;
    }
    else if (HSM_MODE_BOOTLOADER == hsmMode)
    {
        maxNumberOfHostHsmSessions = ECY_HSM_MAX_NUMBER_OF_HOST_HSM_SESSIONS_IN_BOOTLOADER_MODE;
    }
    else
    { /* HSM is not in bootloader nor application */
        return ecy_hsm_CSAI_ERR_INVALID_STATE;
    }

#if (COMPILER == COMPILER_TASKING)
/* Suppress TASKING compiler warning about errorCode being always SUCCESS, since the errorCode can change based on feature switches */
#pragma warning 549
#endif
    /* Get access to the HSM Bridge */
    errorCode = ecy_HSM_GetBridgeResource();
    /* PRQA S 2995, 2991 1 */ /* <Deviation: control flow depends on defines */
    if (ecy_hsm_CSAI_SUCCESS == errorCode)
#if (COMPILER == COMPILER_TASKING)
#pragma warning restore
#endif
    {

        for (sessionCounter = (uint32) 0UL; (maxNumberOfHostHsmSessions > sessionCounter) && (ecy_hsm_CSAI_SUCCESS == errorCode); sessionCounter++)
        {
            port = host2HSM_BridgePorts[sessionCounter];
            if ((HSM_STATUS_IDLE == port.status) || (HSM_STATUS_COMPLETE == port.status))
            {
                errorCode = ecy_hsm_CSAI_SUCCESS;
            }
            else /* The job is either HSM_STATUS_PENDING or HSM_STATUS_PROCESSING */
            {
                errorCode = ecy_hsm_CSAI_FC_BUSY;
            }
        }

        /* Release the bridge ports */
        ecy_HSM_RELEASE_BRIDGE_PORT(errorCode)
    }

    /* PRQA S 6010 2 */ /* Deviation: multiple returns are required to avoid unnecessary resource locking */
    return errorCode;
}

static void ecy_hsm_TbSetVerifTableMaxNumOfElementsHSM(uint32 value)
{
    verifTableMaxNumOfElementsHSM = value;
}

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"
