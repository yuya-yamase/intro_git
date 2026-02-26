/**
 * @file
 ***********************************************************************************************
 * @brief SHE Helpers
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2014, all rights reserved
 **********************************************************************************************/

#if defined(GUAM)
#include "ecy_hsm_general.h"
#else
#include "ecy_hsm_general_pubcfg.h"
#endif
#include "ecy_hsm_applet_manager.h"
#include "ecy_hsm_general_host_cfg.h"
#include "ecy_hsm_proxy.h"
#include "ecy_hsm_she.h"
#include "ecy_hsm_she_host_private.h"

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_VAR_INIT_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

ecy_hsm_Csai_SessionHandleT             SHE_Session             = ecy_hsm_CSAI_INVALID_SESSION_HANDLE_VALUE;
#if (ECY_HSM_VMS_FS_APPLET_SHE_CANCEL == ENABLED)
/* This is an additional backup session handle for the hot swap concept that was introduced for SHE_CMD_CANCEL.
   If SHE_CMD_CANCEL is executed, it will swap SHE_Session and SHE_Session_backup. */
ecy_hsm_Csai_SessionHandleT             SHE_Session_backup      = ecy_hsm_CSAI_INVALID_SESSION_HANDLE_VALUE;
/* This is an additional variable containing the priority information for the hot swap concept that was introduced for SHE_CMD_CANCEL.
   If SHE_CMD_CANCEL is executed twice and the current job has medium priority, ERC_BUSY will be returned. */
ecy_hsm_Csai_JobPriorityT               SHE_Priority            = ecy_hsm_CSAI_PRIO_LOW;
#endif
static ecy_hsm_Csai_JobHandleT          SHE_Job                 = ecy_hsm_CSAI_INVALID_JOB_HANDLE_VALUE;

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_VAR_PTR
#include "ecy_hsm_MemMap.h"

/* PRQA S 1531 3 */ /*  non optimal reference of this object is tested and does not hinder functionality */
const volatile HSM_PortStatusT* pSHE_SessionStatus = NULL_PTR;
#if (ECY_HSM_VMS_FS_APPLET_SHE_CANCEL == ENABLED)
/* This is an additional status pointer for the backup session */
const volatile HSM_PortStatusT* pSHE_SessionStatus_backup = NULL_PTR;
#endif

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_VAR_PTR
#include "ecy_hsm_MemMap.h"

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

SHE_ErrorCodeT SHE_LoadApplet(Applet_She_StateT function, uint32 paramBlockSize, void * const pParamBlock)
{
    SHE_ErrorCodeT     errorCode;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: defintion of union is appropriate here */
    Applet_FunctionT   appletFunc;
    ecy_hsm_Csai_JobPriorityT   priority = ecy_hsm_CSAI_PRIO_LOW;

#if (ECY_HSM_VMS_FS_APPLET_SHE_CANCEL == ENABLED)
    /* pSHE_SessionStatus_backup holds the status of the operation in the deactivated session (see SHE init and deinit
       function). If the deactivated operation is in pending or processing state, the new operation on the active
       session has to be escalated with a higher priority. */
    if(NULL_PTR != pSHE_SessionStatus_backup)
    {
        register HSM_PortStatusT status = *pSHE_SessionStatus_backup;

        if((HSM_STATUS_PENDING == status) || (HSM_STATUS_PROCESSING == status))
        {
            priority = ecy_hsm_CSAI_PRIO_MEDIUM;
        }
    }

    SHE_Priority = priority;
#endif

#if (ECY_HSM_VMS_FS_APPLET_SHE_DEBUG_UNLOCK == ENABLED)
    /* Only background priority is allowed so that CMD DEBUG can wait and run last */
    if (APPLET_SHE_FUNC_DEBUG_AUTHORIZE == function)
    {
        priority = ecy_hsm_CSAI_PRIO_BACKGROUND;
    }
#endif /* ECY_HSM_VMS_FS_APPLET_SHE_DEBUG_UNLOCK */

    appletFunc.Applet.appletId = (uint16) APPLET_ID_SHE;
    appletFunc.Applet.functionId = (uint16) function;

    result = Applet_Function( SHE_Session, priority, appletFunc, paramBlockSize, pParamBlock );

    // update given job handle
    SHE_Job = SHE_Session;

    if(ecy_hsm_CSAI_FC_BUSY == result.stError)
    {
        errorCode = ERC_BUSY;
    }
    else if((result.stError & ecy_hsm_CSAI_ERR_FLAG_PREVIOUS_OP) != 0U)
    {
        errorCode = ERC_GENERAL_ERROR;
    }
    else
    {
        /* PRQA S 4342, 4394 3 */ /* Deviation: rule_10.8_4394_she */ /* Justification: Since result.stError is uint32,
         * no adverse behaviour expected in type cast. Casted values are expected to fall within enumeration constants,
         * otherwise clear & graceful SHE test failures would be expected. */
        errorCode = ecy_hsm_CSAI_EXTRACT_SHE_ERROR_CODE(result.stError);
    }

    return errorCode;
}

/* The error code returned is the request error code */
/* PRQA S 1532 1 */ /*  non optimal reference of this function is tested and does not hinder functionality */
ecy_hsm_Csai_ErrorT SHE_QuickRoute(HSM_FunctionT function, uint32 paramBlockSize, void* const pParamBlock)
{
    ecy_hsm_Csai_ErrorT errorCode;

#if (COMPILER == COMPILER_TASKING)
/* Suppress TASKING compiler warning about errorCode beeing always SUCCESS. This is not correct since the errorCode can change based on feature
 * switches */
#pragma warning 549
#endif
#if(ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED)
    /* The resource locking will be handled in ecy_HSM_QuickRoute, if the NO_WAIT mode is enabled */
    errorCode = ecy_hsm_CSAI_SUCCESS;
#else
    /* Get access to the HSM Bridge */
    errorCode = ecy_HSM_GetBridgeResource();
#endif
    /* PRQA S 2995, 2991 1 */ /* <Deviation: control flow depends on defines */
    if (ecy_hsm_CSAI_SUCCESS == errorCode)
#if (COMPILER == COMPILER_TASKING)
#pragma warning restore
#endif
    {
        errorCode = ecy_HSM_QuickRoute(SHE_Session, function, paramBlockSize, pParamBlock, &SHE_Job);
#if (ecy_hsm_CSAI_FS_NO_WAIT_MODE != ENABLED)
        /* Release the bridge ports */
        ecy_HSM_RELEASE_BRIDGE_PORT(errorCode)
#endif /* (ecy_hsm_CSAI_FS_NO_WAIT_MODE != ENABLED) */

    }

    return errorCode;
}

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"
