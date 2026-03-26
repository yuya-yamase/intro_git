/**
 * @file
 ***********************************************************************************************
 * @brief CSAI Message Authenticated Code implementation file
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2014, all rights reserved.
 **********************************************************************************************/

#include "Platform_Types.h"
#if defined(GUAM)
# include "ecy_hsm_general.h"
#else
# include "ecy_hsm_general_pubcfg.h"
#endif
#include "ecy_hsm_applet_manager.h"
#include "ecy_hsm_applet_secflash.h"
#include "ecy_hsm_csai_secflash.h"
#include "ecy_hsm_csai_vms_pub_data.h"
#include "ecy_hsm_host_mcal.h"
#include "ecy_hsm_host_proxy.h"
#include "ecy_hsm_ipcdrv.h"
#include "ecy_hsm_proxy.h"

#if (ecy_hsm_USE_US_TIMEBASE == ENABLED)
/* Maximum possible timeout value before overflow occurs*/
# define MAX_TIMEOUT_VALUE (uint32)(0xFFFFFFFFUL / ecy_hsm_COUNTER_VALUE_TIMEBASE)
#endif
/**************************************************************************************************/
/**************************************************************************************************/
/**************************************************************************************************/

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_SecFlash_Init(ecy_hsm_Csai_SessionHandleT       hSession,
                                                                                       ecy_hsm_Csai_JobPriorityT         priority,
                                                                                       ecy_hsm_Csai_SignatureSchemeT     sigScheme,
                                                                                       uint8 const*                      pMemRangeStart,
                                                                                       uint32                            numBytesMemRange,
                                                                                       ecy_hsm_Csai_SecFlash_FlashOptBmT bmFlashOptions,
                                                                                       uint32                            numMsTimeout,
                                                                                       ecy_hsm_Csai_JobHandleT*          phJob)
{
    /* Initialization */
    HSM_SecFlashParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SECFLASH, APPLET_SECFLASH_STATE_INIT_E);

    CSAI_PARAM_UNUSED(priority);
    /* Parameter update */
    /* PRQA S 2983 7 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.scheme        = sigScheme;
    paramBlock.pFlashStart   = pMemRangeStart;
    paramBlock.numBytesFlash = numBytesMemRange;
    paramBlock.bmOptions     = bmFlashOptions;
    paramBlock.msg           = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.pSign         = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.pResultFlag   = NULL_PTR; /* default initialization in context of ffi */

    // execute applet: force Background priority because it involves stack-consuming RSA operations
    result = Applet_Function(hSession, ecy_hsm_CSAI_PRIO_BACKGROUND, appletFunc, sizeof(paramBlock), &paramBlock);

    if (result.stError == ecy_hsm_CSAI_SUCCESS)
    {
        uint32 startingValue;
        uint32 elapsedValue = 0U;

        Applet_ErrorStateT stError;

        /* Conversion to timebase */
        /* PRQA S 2995, 2991 1 */ /* <Deviation: control flow depends on defines */
#if (ecy_hsm_USE_US_TIMEBASE == ENABLED)
        if (numMsTimeout < MAX_TIMEOUT_VALUE)
        {
            numMsTimeout *= ecy_hsm_COUNTER_VALUE_TIMEBASE;
        }
        else
        {
            /* PRQA S 2880 1 */ /* <Deviation: control flow input parameters*/
            numMsTimeout = 0xFFFFFFFFUL;
        }
#endif

        stError = ecy_HSM_GetCounterValue(&startingValue);
        if (ecy_hsm_CSAI_SUCCESS == stError)
        {
            HSM_ModeT hsmMode;

            do
            {
                ecy_hsm_FunctionIRQHandling();
                stError = ecy_HSM_GetElapsedCounterValue(startingValue, &elapsedValue);
                if (ecy_hsm_CSAI_SUCCESS == stError)
                {
                    stError = ecy_hsm_Csai_PollHandle(hSession);
                }

                if (ecy_hsm_CSAI_FAILED(stError))
                {
                    result.stError = stError;
                    break;
                }

                hsmMode = ecy_hsm_HsmMCAL_GetMode();
            }
            while ((((ecy_hsm_CSAI_SECFLASH_OPT_FOTA != (paramBlock.bmOptions & ecy_hsm_CSAI_SECFLASH_OPT_FOTA))
                     && (HSM_MODE_BOOTLOADER != hsmMode))
                    || (stError == ecy_hsm_CSAI_FC_PENDING))
                   && ((elapsedValue < numMsTimeout) || (numMsTimeout == 0U)));
        }
        else
        {
            result.stError = stError;
        }

        /* if timeout has occurred
         * AND a timeout is configured
         * report TIMEOUT error
         */
        if ((elapsedValue >= numMsTimeout) && (numMsTimeout != 0U))
        {
            result.stError = ecy_hsm_CSAI_ERR_TIMEOUT;
        }
    }

    /* Update given job handle */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
    /* PRQA S 6007 1 */ /* <Deviation: number of function parameters is fixed by design */
}

/**************************************************************************************************/
/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_SecFlash_Update(ecy_hsm_Csai_JobHandleT hJob,
                                                                                         const uint8             data[],
                                                                                         uint32                  numBytesData)
{
    /* Initialization */
    HSM_SecFlashParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SECFLASH, APPLET_SECFLASH_STATE_UPDATE_E);

    /* Parameter update */
    /* PRQA S 2983 5 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.msg         = data;
    paramBlock.msgLength   = numBytesData;
    paramBlock.pFlashStart = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.pSign       = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.pResultFlag = NULL_PTR; /* default initialization in context of ffi */

    result = Applet_Function(hJob, ecy_hsm_CSAI_PRIO_UNCHANGED, appletFunc, sizeof(paramBlock), &paramBlock);

    return CSAI_ERR(result.stError);
}

/**************************************************************************************************/
/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_SecFlash_Finalize(ecy_hsm_Csai_JobHandleT hJob,
                                                                                           uint8 const*            pSigData,
                                                                                           uint32                  numBytesSig,
                                                                                           ecy_hsm_Csai_KeyHandleT hKey,
                                                                                           uint32*                 pResultFlag)
{
    HSM_SecFlashParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SECFLASH, APPLET_SECFLASH_STATE_FINAL_E);

    // Initialize result to verification failed
    if (pResultFlag != NULL_PTR)
    {
        /* PRQA S 4404 1 */ /* <Deviation: rule_10.3_4404_10.5_4304_boolean */
        *pResultFlag = TRUE;
    }

    /* Parameter update */
    /* PRQA S 2983 6 */                /* <Deviation: rule_2.2_2983 */
    paramBlock.pFlashStart = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.msg         = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.pSign       = pSigData;
    paramBlock.signLength  = numBytesSig;
    paramBlock.hKey        = hKey;
    paramBlock.pResultFlag = pResultFlag;

    result = Applet_Function(hJob, ecy_hsm_CSAI_PRIO_UNCHANGED, appletFunc, sizeof(paramBlock), &paramBlock);

    return CSAI_ERR(result.stError);
}

/**************************************************************************************************/
/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_SecFlash_Cancel(ecy_hsm_Csai_JobHandleT hJob)
{
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SECFLASH, APPLET_SECFLASH_STATE_CANCEL_E);

    result = Applet_Function(hJob, ecy_hsm_CSAI_PRIO_UNCHANGED, appletFunc, 0, NULL_PTR);

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_SecFlash_VerifySignedHeader(ecy_hsm_Csai_SessionHandleT    hSession,
                                                                                                     ecy_hsm_Csai_JobPriorityT      priority,
                                                                                                     ecy_hsm_Csai_SignedHeaderRefT* pSignedHeaderRef,
                                                                                                     ecy_hsm_Csai_JobHandleT*       phJob)
{
    /* Initialization */
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* Applet_FunctionT is an union */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SECFLASH, APPLET_SECFLASH_SIGNED_HEADER_VERIFICATION_E);

    /* execute applet */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(ecy_hsm_Csai_SignedHeaderRefT), pSignedHeaderRef);

    /* update given job handle */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_SecFlash_RetrieveSignedHeaderMac(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                                          uint8                       pHeaderMac[],
                                                                                                          uint32*                  pHeaderMacLength,
                                                                                                          ecy_hsm_Csai_JobHandleT* phJob)
{
    /* Initialization */
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SECFLASH, APPLET_SECFLASH_SIGNED_HEADER_VERIFICATION_RETRIEVE_MAC_E);

    ecy_hsm_RetrieveSignedHeaderMacParamT paramBlock;
    paramBlock.pHeaderMac       = pHeaderMac;
    paramBlock.pHeaderMacLength = pHeaderMacLength;

    /* execute applet */
    result = Applet_Function(hSession, ecy_hsm_CSAI_PRIO_UNCHANGED, appletFunc, sizeof(paramBlock), &paramBlock);

    /* update given job handle */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_SecFlash_SetSignedHeaderMac(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                                     ecy_hsm_Csai_JobPriorityT   priority,
                                                                                                     const uint8                 pHeaderMac[],
                                                                                                     uint32                      headerMacLength,
                                                                                                     ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* Applet_FunctionT is an union */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SECFLASH, APPLET_SECFLASH_SIGNED_HEADER_VERIFICATION_STORE_MAC_E);

    ecy_hsm_SetSignedHeaderMacParamT paramBlock;
    paramBlock.pHeaderMac      = pHeaderMac;
    paramBlock.headerMacLength = headerMacLength;

    /* execute applet */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

    /* update given job handle */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_SecFlash_VerifyHostSignedHeader( ecy_hsm_Csai_SessionHandleT hSession,
                                                                ecy_hsm_Csai_JobPriorityT priority,
                                                                ecy_hsm_Csai_SignedHeaderRefT *pSignedHeaderRef,
                                                                ecy_hsm_Csai_JobHandleT* phJob )
{
    /* Initialization */
    Applet_ReturnTypeT  result;
    /* PRQA S 0759 1 */ /* Applet_FunctionT is an union */
    Applet_FunctionT    appletFunc = APPFUNC_ID(APPLET_ID_SECFLASH, ecy_hsm_APPLET_SECFLASH_HOST_SIGNED_HEADER_VERIFICATION_E);

    /* execute applet */
    result = Applet_Function(hSession,
                             priority,
                             appletFunc,
                             sizeof(ecy_hsm_Csai_SignedHeaderRefT),
                             pSignedHeaderRef);

    /* update given job handle */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return result.stError;
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL
ecy_hsm_Csai_SecFlash_UpdateFromDataContainer(ecy_hsm_Csai_JobHandleT              hJob,
                                              ecy_hsm_Csai_JobPriorityT            priority,
                                              ecy_hsm_Csai_SyncFlashAccessUpdateT* pFlashUsageSyncHost,
                                              ecy_hsm_Csai_UpdateContainerParamT*  pCustomParam)
{
    /* Initialization */
    HSM_SecFlashSingleShotParamT paramBlock;
    Applet_ReturnTypeT           result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SECFLASH, APPLET_SECFLASH_UPDATE_FROM_DATA_CONTAINER_E);

    /* Parameter update */
    /* PRQA S 2983 2 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.pCustomParam        = pCustomParam;
    paramBlock.pFlashUsageSyncHost = pFlashUsageSyncHost;

    /* Execute applet */
    result = Applet_Function(hJob, priority, appletFunc, sizeof(paramBlock), &paramBlock);

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_SecFlash_SyncInactiveBank(ecy_hsm_Csai_JobHandleT hJob)
{
    /* Initialization */
    HSM_SecFlashParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SECFLASH, APPLET_SECFLASH_STATE_SYNC_E);

    result = Applet_Function(hJob, ecy_hsm_CSAI_PRIO_UNCHANGED, appletFunc, sizeof(paramBlock), &paramBlock);

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_SecFlash_BankSwap(ecy_hsm_Csai_JobHandleT hJob)
{
    /* Initialization */
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SECFLASH, ecy_hsm_APPLET_SECFLASH_STATE_BANKSWAP_E);

    result = Applet_Function(hJob, ecy_hsm_CSAI_PRIO_UNCHANGED, appletFunc, 0U, NULL_PTR);

    return CSAI_ERR(result.stError);
}

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"
