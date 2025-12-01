/**
 * @file ecy_hsm_csai_job.c
 ***********************************************************************************************
 * @brief CSAI Job implementation file
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2014, all rights reserved
 **********************************************************************************************/

#if defined(GUAM)
# include "ecy_hsm_general.h"
#else
# include "ecy_hsm_general_pubcfg.h"
#endif
#include "ecy_hsm_applet_manager.h"
#include "ecy_hsm_applet_system.h"
#include "ecy_hsm_csai.h"
#include "ecy_hsm_csai_vms_pub_data.h"
#include "ecy_hsm_host_proxy.h"
#include "ecy_hsm_proxy.h"
#include "ecy_hsm_sessions_params.h"

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_CancelJob(ecy_hsm_Csai_JobHandleT hJob)
{
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SYSTEM, APPLET_SYSTEM_STATE_JOB_CANCEL_E);

    result = Applet_Function(hJob, ecy_hsm_CSAI_PRIO_HIGH, appletFunc, 0, NULL_PTR);

    /* Wait for the operation to complete */
    if (ecy_hsm_CSAI_SUCCESS == result.stError)
    {
        result.stError = ecy_HSM_WaitForOpToComplete(hJob, 10u);
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_CancelOperation(ecy_hsm_Csai_SessionHandleT hSession)
{
    ecy_hsm_Csai_ErrorT errorCode;
    if (hSession < CYCURHSM_SC_MAX_HOST_HSM_SESSIONS)
    {
        errorCode = ecy_HSM_CancelOp(hSession);
    }
    else
    {
        errorCode = ecy_hsm_CSAI_ERR_INVALID_HANDLE;
    }
    return (errorCode);
}

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_WaitForHandle(ecy_hsm_Csai_JobHandleT hJob,
                                             CSAI_WatchdogFunctionT  watchdog,
                                             void*                   pParam,
                                             uint32                  timeout_ms)
{
    ecy_hsm_Csai_ErrorT errorCode;
    HSM_PortStatusT     status = HSM_STATUS_IDLE;
    uint32              startingTime;
    uint32              elapsedTime;
    uint32              abrt;
    uint32              delayTimeout = timeout_ms * ecy_hsm_COUNTER_VALUE_TIMEBASE;
    errorCode                        = ecy_HSM_GetCounterValue(&startingTime);

    if (ecy_hsm_CSAI_SUCCESS == errorCode)
    {
        do
        {
            ecy_hsm_FunctionIRQHandling();
            /* Takeover from HSM 1.x */
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
                /* Sample the elapsed time first */
                errorCode = ecy_HSM_GetElapsedCounterValue(startingTime, &elapsedTime);
            }

            if (ecy_hsm_CSAI_SUCCESS == errorCode)
            {
                /* Sample the operation status AFTER sampling the elapsed time */
                errorCode = ecy_HSM_GetOpStatus(hJob, &status);
            }

            if ((ecy_hsm_CSAI_SUCCESS == errorCode)
                && ((HSM_STATUS_PENDING == status) || (HSM_STATUS_PROCESSING == status))
                && (elapsedTime >= delayTimeout))
            {
                /*
                 * Return a time out only if the following conditions are met:
                 * - Previous calls of ecy_HSM_GetElapsedCounterValue and ecy_HSM_GetOpStatus were successful.
                 * - ecy_HSM_GetOpStatus returns the status pending or processing, i.e. the job did not complete yet.
                 * - ecy_HSM_GetElapsedCounterValue returns a time equal or larger than the timeout value.
                 * - ecy_HSM_GetElapsedCounterValue was called BEFORE ecy_HSM_GetOpStatus, hence the pending/processing
                 *   status was observed (only) AFTER the time limit was exceeded.
                 *   This ensures, that time out is never returned when the job actually completed. This occurred when
                 *   the task running this code was preempted just after having
                 *   called ecy_HSM_GetOpStatus() which returned HSM_STATUS_PENDING. After resumption (after some time)
                 *   (only) ecy_HSM_GetElapsedCounterValue() was called,
                 *   which now returned time out. Time out was then returned to the caller, although the job might have
                 *   finished during the preemption.
                 */
                errorCode = ecy_hsm_CSAI_ERR_TIMEOUT;
            }
        }
        while ((ecy_hsm_CSAI_SUCCESS == errorCode)
               && ((HSM_STATUS_PENDING == status) || (HSM_STATUS_PROCESSING == status) || (HSM_STATUS_TRANSMIT_JOB == status)));
    }

    return (CSAI_ERR(errorCode));
}

/* Won't work for key handles yet, (probably never) only works for job handles and session handles because they are the
   same thing. If not finished error code ecy_hsm_CSAI_FC_PENDING must be returned.   */
/* PRQA S 1532 2 */ /*  non optimal reference of this function is tested and does not hinder functionality */
/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_PollHandle(ecy_hsm_Csai_JobHandleT handle)
{
    HSM_PortStatusT     status;
    ecy_hsm_Csai_ErrorT errorCode;

    errorCode = ecy_HSM_GetOpStatus(handle, &status);
    if ((ecy_hsm_CSAI_ERR_SWITCHING_FROM_CORE_TO_BOOT == errorCode)
        || ((ecy_hsm_CSAI_SUCCESS == errorCode) && (HSM_STATUS_IDLE != status) && (HSM_STATUS_COMPLETE != status)))
    {
        errorCode = ecy_hsm_CSAI_FC_PENDING;
    }
    return (CSAI_ERR(errorCode));
}

/* PRQA S 1503 2 */ /* Deviation: rule_2.1_1503_Proxy */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_PollStatus(ecy_hsm_Csai_JobHandleT handle)
{
    HSM_PortStatusT     status;
    ecy_hsm_Csai_ErrorT errorCode;

    errorCode = ecy_HSM_ReadOpStatus(handle, &status, ecy_hsm_OPT_NONE);
    if ((ecy_hsm_CSAI_SUCCESS == errorCode) && (HSM_STATUS_IDLE != status) && (HSM_STATUS_COMPLETE != status))
    {
        errorCode = ecy_hsm_CSAI_FC_PENDING;
    }
    return (CSAI_ERR(errorCode));
}

/* PRQA S 1503 2 */ /* Deviation: rule_2.1_1503_Proxy */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_GetJobStatus(ecy_hsm_Csai_JobHandleT  handle,
                                            ecy_hsm_Csai_JobStatusT* pStatus)
{
    HSM_PortStatusT     status;
    ecy_hsm_Csai_ErrorT errorCode;

    if (NULL_PTR == pStatus)
    {
        errorCode = ecy_hsm_CSAI_ERR_INVALID_PARAM;
    }
    else
    {
        errorCode = ecy_HSM_GetOpStatusNonConsuming(handle, &status);
        if (ecy_hsm_CSAI_SUCCESS == errorCode)
        {
            switch (status)
            {
                case HSM_STATUS_IDLE:
                    *pStatus = ecy_hsm_CSAI_JOBSTATUS_IDLE;
                    break;
                case HSM_STATUS_TRANSMIT_JOB:
                case HSM_STATUS_PENDING:
                    *pStatus = ecy_hsm_CSAI_JOBSTATUS_PENDING;
                    break;
                case HSM_STATUS_PROCESSING:
                    *pStatus = ecy_hsm_CSAI_JOBSTATUS_PROCESSING;
                    break;
                case HSM_STATUS_COMPLETE:
                    *pStatus = ecy_hsm_CSAI_JOBSTATUS_COMPLETE;
                    break;
                default:
                    *pStatus  = ecy_hsm_CSAI_JOBSTATUS_IDLE;
                    errorCode = ecy_hsm_CSAI_ERR_INVALID_HANDLE;
                    break;
            }
        }
        else
        {
            *pStatus = ecy_hsm_CSAI_JOBSTATUS_IDLE;
        }
    }
    return (errorCode);
}

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"
