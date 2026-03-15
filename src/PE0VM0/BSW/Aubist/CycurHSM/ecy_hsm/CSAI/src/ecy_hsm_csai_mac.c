/**
 * @file
 ***********************************************************************************************
 * @brief CSAI Message Authenticated Code implementation file
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2014, all rights reserved.
 **********************************************************************************************/

#if defined(GUAM)
#include "ecy_hsm_general.h"
#else
#include "ecy_hsm_general_pubcfg.h"
#endif
#include "ecy_hsm_general_host_cfg.h"
#include "ecy_hsm_csai_mac.h"
#include "ecy_hsm_proxy.h"
#include "ecy_hsm_applet_mac_gen.h"
#include "ecy_hsm_applet_mac_verify.h"
#include "ecy_hsm_applet_manager.h"
#include "ecy_hsm_timing_diagnostics.h"

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* [$Satisfies $DD 462] CSAI MAC Generate Start Interface */
/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_MacGenerateStart(ecy_hsm_Csai_SessionHandleT hSession,
                                                ecy_hsm_Csai_MACAlgorithmT  algorithm,
                                                ecy_hsm_Csai_KeyHandleT     hKey,
                                                ecy_hsm_Csai_JobPriorityT   priority,
                                                const uint8                 msg[],
                                                uint32                      msgLength,
                                                ecy_hsm_Csai_JobHandleT*    phJob)
{

    /* Initialization */
    HSM_MacGenerateParamT paramBlock;
    Applet_ReturnTypeT result; /* initialized by Applet_Function() */
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_MACGEN, APPLET_MACGEN_STATE_INIT_E);

    /* Parameter update */
    /* PRQA S 2983 6 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.algorithm = algorithm;
    paramBlock.hKey = hKey;
    paramBlock.msg = msg;
    paramBlock.msgLength = msgLength;
    paramBlock.pMac = NULL_PTR;         /* default initialization in context of ffi */
    paramBlock.pMacCount = NULL_PTR;    /* default initialization in context of ffi */

    ecy_hsm_AddDiagnosticStopwatch('S');

    // execute applet
    result = Applet_Function( hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock );

    /* Update given job handle */
    if( phJob != NULL_PTR )
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* [$Satisfies $DD 463] CSAI MAC Generate Update Interface */
/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_MacGenerateUpdate(ecy_hsm_Csai_JobHandleT hJob, const uint8 data[], uint32 dataLength)
{
    /* Initialization */
    HSM_MacGenerateParamT paramBlock;
    Applet_ReturnTypeT result; /* initialized by Applet_Function() */
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_MACGEN, APPLET_MACGEN_STATE_UPDATE_E);


    /*Structure Update */
    /* PRQA S 2983 4 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.msgLength = dataLength;
    paramBlock.msg = data;
    paramBlock.pMac = NULL_PTR;         /* default initialization in context of ffi */
    paramBlock.pMacCount = NULL_PTR;    /* default initialization in context of ffi */

    ecy_hsm_AddDiagnosticStopwatch('U');

    // execute applet
    result = Applet_Function( hJob,ecy_hsm_CSAI_PRIO_UNCHANGED, appletFunc, sizeof(paramBlock), &paramBlock );

    return CSAI_ERR(result.stError);
}

/* [$Satisfies $DD 464] CSAI MAC Generate Finish Interface */
/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_MacGenerateFinish(ecy_hsm_Csai_JobHandleT hJob,
                                                 uint8*                  pMac,
                                                 uint32                  macBitLength,
                                                 uint32*                 pMacCount,
                                                 boolean                 truncationAllowed)
{
    /* Initialization */
    HSM_MacGenerateParamT paramBlock;
    Applet_ReturnTypeT result; /* initialized by Applet_Function() */
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_MACGEN, APPLET_MACGEN_STATE_FINAL_E);

    /* Parameter update */
    /* PRQA S 2983 6 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.msg = NULL_PTR;      /* default initialization in context of ffi */
    paramBlock.pMac = pMac;
    paramBlock.macBitLength = macBitLength;
    paramBlock.pMacCount = pMacCount;
    /* PRQA S 4304 1 */ /* <Deviation: rule_10.3_4404_10.5_4304_boolean */
    paramBlock.truncationAllowed = (uint32)truncationAllowed;

    ecy_hsm_AddDiagnosticStopwatch('F');

    // execute applet
    result = Applet_Function( hJob, ecy_hsm_CSAI_PRIO_UNCHANGED, appletFunc, sizeof(paramBlock), &paramBlock );

    return CSAI_ERR(result.stError);
}

/* [$Satisfies $DD 465] CSAI MAC Generate Fast call Interface */
/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_MacGenerate(ecy_hsm_Csai_SessionHandleT hSession,
                                           ecy_hsm_Csai_MACAlgorithmT  algorithm,
                                           ecy_hsm_Csai_KeyHandleT     hKey,
                                           ecy_hsm_Csai_JobPriorityT   priority,
                                           const uint8                 msg[],
                                           uint32                      msgLength,
                                           uint8*                      pMac,
                                           uint32                      macBitLength,
                                           uint32*                     pMacCount,
                                           boolean                     truncationAllowed,
                                           ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* If we can't do a Quick CMAC, or it fails, then we'll do a normal MAC Generate unless ecy_hsm_QUICK_ROUTE_FAILFAST is enabled */
    ecy_hsm_Csai_ErrorT errorCode = ecy_hsm_CSAI_ERR_QUICK_ROUTE_NOT_POSSIBLE;

#if (ecy_hsm_QUICK_ROUTE == ENABLED)

#if (ecy_hsm_QUICK_ROUTE_FAILFAST == ENABLED)
    boolean quickRouteFailed = FALSE;
#endif

    if (((ecy_hsm_CSAI_AES_CMAC == algorithm) || (ecy_hsm_CSAI_SIPHASH_24 == algorithm)) && (msgLength <= ecy_hsm_MAX_QUICK_ROUTE_BYTES))
    {
        HSM_MacQuickParamT paramBlock;

        /* Parameter update */
        /* PRQA S 2983 8 */ /* <Deviation: rule_2.2_2983 */
        paramBlock.hKey      = hKey;
        paramBlock.msg       = msg;
        paramBlock.msgLength = msgLength;

        /* default initialization in context of ffi */
        paramBlock.pExpectedMac = NULL_PTR;
        paramBlock.macBitLength = 0x0;
        paramBlock.safetyMac    = NULL_PTR;

#if (COMPILER == COMPILER_TASKING)
/* Suppress TASKING compiler warning about errorCode beeing always SUCCESS. This is not correct since the errorCode can change based on feature
 * switches */
#pragma warning 549
#endif
#if(ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED)
        /* The resource locking will be handled in @ref ecy_HSM_QuickRoute, if the NO_WAIT mode is enabled */
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
            if(ecy_hsm_CSAI_AES_CMAC == algorithm)
            {
                errorCode = ecy_HSM_QuickRoute(hSession, HSM_FUNC_CMAC_GENERATE, sizeof(paramBlock), &paramBlock, phJob);
            }
            else
            {
                errorCode = ecy_HSM_QuickRoute(hSession, HSM_FUNC_SIPHASH_GENERATE, sizeof(paramBlock), &paramBlock, phJob);
            }

            if(ecy_hsm_CSAI_SUCCESS == errorCode)
            {
                if (pMac != NULL_PTR)
                {
                    /* No error returned because it comes via a call to PollHandle */
                    ecy_HSM_TruncateAndCopyMac(hSession, macBitLength, truncationAllowed, pMac, pMacCount, algorithm);
                }
                else
                {
                    errorCode = ecy_hsm_CSAI_ERR_INVALID_PARAM;
                }
            }
            else
            {
    #if (ecy_hsm_QUICK_ROUTE_FAILFAST == ENABLED)
                quickRouteFailed = TRUE;
    #endif
            }
#if(ecy_hsm_CSAI_FS_NO_WAIT_MODE != ENABLED)
            ecy_HSM_RELEASE_BRIDGE_PORT(errorCode)
#endif /* #if(ecy_hsm_CSAI_FS_NO_WAIT_MODE != ENABLED) */
        }
    }
    /* If the Quick CMAC request failed (e.g. because the AES hardware was busy, or
    the key was not loaded), then we go by the normal route unless ecy_hsm_QUICK_ROUTE_FAILFAST is enabled */
    if (
#if (ecy_hsm_QUICK_ROUTE_FAILFAST == ENABLED)
        (FALSE == quickRouteFailed) &&
#endif
        (ecy_hsm_CSAI_ERR_QUICK_ROUTE_NOT_POSSIBLE == errorCode))
#endif
    {
        HSM_MacGenerateParamT paramBlock;
        Applet_ReturnTypeT result; /* initialized by Applet_Function() */
        /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
        Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_MACGEN, APPLET_MACGEN_STATE_FULL_E);

        /* Parameter update */
        /* PRQA S 2983 9 */ /* <Deviation: rule_2.2_2983 */
        paramBlock.algorithm    = algorithm;
        paramBlock.hKey         = hKey;
        paramBlock.msg          = msg;
        paramBlock.msgLength    = msgLength;
        paramBlock.pMac         = pMac;
        paramBlock.macBitLength = macBitLength;
        paramBlock.pMacCount    = pMacCount;
        /* PRQA S 4304 1 */ /* <Deviation: rule_10.3_4404_10.5_4304_boolean */
        paramBlock.truncationAllowed = (uint32)truncationAllowed;

        // execute applet
        result = Applet_Function( hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock );

        errorCode = CSAI_ERR(result.stError);
    }

    /* Update given job handle */
    if( phJob != NULL_PTR )
    {
        *phJob = hSession;
    }

    return (errorCode);
/* PRQA S 6007 1 */ /* <Deviation: number of function parameters is fixed by design */
}
/* [$Satisfies $DD 466] CSAI Bulk MAC Generate interface, defined in dox */
/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_BulkMacGenerate(ecy_hsm_Csai_SessionHandleT hSession,
                                               ecy_hsm_Csai_JobPriorityT   priority,
                                               const void*                 pTable,
                                               uint32                      numOfEntries,
                                               uint32                      macByteSize,
                                               uint8*                      pData1,
                                               uint32                      data1Size,
                                               uint8*                      pData2,
                                               uint32                      data2Size,
                                               ecy_hsm_Csai_JobHandleT*    phJob)

{
    /* Initialization */
    HSM_BulkMacGenerateParamT paramBlock;
    Applet_ReturnTypeT        result; /* initialized by Applet_Function() */
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT          appletFunc = APPFUNC_ID(APPLET_ID_MACGEN, APPLET_MACGEN_STATE_BULK_E);

    /* Parameter update */
    /* PRQA S 2983 8 */ /* <Deviation: rule_2.2_2983 */
    /* PRQA S 0316 2 */ /*  <Deviation: Rule 11.5 -  Advisory - Justification: pTable is always of type  pointer to ecy_hsm_Csai_BulkMacControlGenerateJobT */
    paramBlock.pTable       = (const ecy_hsm_Csai_BulkMacControlGenerateJobT*)pTable;
    paramBlock.numOfEntries = numOfEntries;
    paramBlock.macByteSize  = macByteSize;
    paramBlock.data1        = pData1;
    paramBlock.data1Size    = data1Size;
    paramBlock.data2        = pData2;
    paramBlock.data2Size    = data2Size;

    // execute applet
    result    = Applet_Function( hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock );

    /* Update given job handle */
    if( phJob != NULL_PTR )
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
/* PRQA S 6007 1 */ /* <Deviation: number of function parameters is fixed by design */
}
/**************************************************************************************************/
/**************************************************************************************************/
/**************************************************************************************************/
/* [$Satisfies $DD 467] CSAI MAC Verify Start Interface */
/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_MacVerifyStart(ecy_hsm_Csai_SessionHandleT hSession,
                                              ecy_hsm_Csai_MACAlgorithmT  algorithm,
                                              ecy_hsm_Csai_KeyHandleT     hKey,
                                              ecy_hsm_Csai_JobPriorityT   priority,
                                              const uint8                 msg[],
                                              uint32                      msgLength,
                                              ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    HSM_MacVerifyParamT paramBlock;
    Applet_ReturnTypeT result; /* initialized by Applet_Function() */
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_MAC_VERIFY, APPLET_MACVERIFY_STATE_INIT_E);


    /* Parameter update */
    /* PRQA S 2983 7 */ /* <Deviation: rule_2.2_2983  */
    paramBlock.algorithm    = algorithm;
    paramBlock.hKey         = hKey;
    paramBlock.msg          = msg;
    paramBlock.msgLength    = msgLength;
    paramBlock.pExpectedMac = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.pResultFlag  = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.safetyMac    = NULL_PTR; /* default initialization in context of ffi */

    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);
    /* Update given job handle */
    if( phJob != NULL_PTR )
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/**************************************************************************************************/
/* [$Satisfies $DD 468] CSAI MAC Verify Update Interface */
/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_MacVerifyUpdate(ecy_hsm_Csai_JobHandleT hJob,
                                               const uint8             data[],
                                               uint32                  dataLength)
{
    /* Initialization */
    Applet_ReturnTypeT result; /* initialized by Applet_Function() */
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_MAC_VERIFY, APPLET_MACVERIFY_STATE_UPDATE_E);
    HSM_MacVerifyParamT paramBlock;

    /* Parameter update */
    /* PRQA S 2983 5 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.msgLength    = dataLength;
    paramBlock.msg          = data;
    paramBlock.pExpectedMac = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.pResultFlag  = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.safetyMac    = NULL_PTR; /* default initialization in context of ffi */

    // execute applet
    result = Applet_Function(hJob, ecy_hsm_CSAI_PRIO_UNCHANGED, appletFunc, sizeof(paramBlock), &paramBlock);

    return CSAI_ERR(result.stError);
}

/**************************************************************************************************/
/* [$Satisfies $DD 469] CSAI MAC Verify Finish Interface */
/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_MacVerifyFinish(ecy_hsm_Csai_JobHandleT hJob,
                                               const uint8*            pExpectedMac,
                                               uint32                  macBitLength,
                                               uint32*                 pResultFlag)
{
    Applet_ReturnTypeT result; /* initialized by Applet_Function() */
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_MAC_VERIFY, APPLET_MACVERIFY_STATE_FINAL_E);
    HSM_MacVerifyParamT paramBlock;

    /* Parameter update */
    /* PRQA S 2983 4 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.msg          = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.pExpectedMac = pExpectedMac;
    paramBlock.macBitLength = macBitLength;
    paramBlock.pResultFlag  = pResultFlag;

    // execute applet
    result = Applet_Function(hJob, ecy_hsm_CSAI_PRIO_UNCHANGED, appletFunc, sizeof(paramBlock), &paramBlock);

    return CSAI_ERR(result.stError);
}

/**************************************************************************************************/
/* [$Satisfies $DD 470] CSAI MAC Verify fast call Interface */
/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_MacVerify(ecy_hsm_Csai_SessionHandleT hSession,
                                         ecy_hsm_Csai_MACAlgorithmT  algorithm,
                                         ecy_hsm_Csai_KeyHandleT     hKey,
                                         ecy_hsm_Csai_JobPriorityT   priority,
                                         const uint8                 msg[],
                                         uint32                      msgLength,
                                         const uint8*                pExpectedMac,
                                         uint32                      macBitLength,
                                         uint32*                     pResultFlag,
                                         ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* If we can't do a Quick CMAC, or it fails, then we'll do a normal MAC Verify unless ecy_hsm_QUICK_ROUTE_FAILFAST is enabled */
    ecy_hsm_Csai_ErrorT errorCode = ecy_hsm_CSAI_ERR_QUICK_ROUTE_NOT_POSSIBLE;

#if (ecy_hsm_QUICK_ROUTE == ENABLED)

#if (ecy_hsm_QUICK_ROUTE_FAILFAST == ENABLED)
    boolean quickRouteFailed = FALSE;
#endif

    if (((ecy_hsm_CSAI_AES_CMAC == algorithm) || (ecy_hsm_CSAI_SIPHASH_24 == algorithm)) && (msgLength <= ecy_hsm_MAX_QUICK_ROUTE_BYTES))
    {
        HSM_MacQuickParamT paramBlock;

        /* Parameter update */
        /* PRQA S 2983 6 */ /* <Deviation: rule_2.2_2983  */
        paramBlock.hKey         = hKey;
        paramBlock.msg          = msg;
        paramBlock.msgLength    = msgLength;
        paramBlock.pExpectedMac = pExpectedMac;
        paramBlock.macBitLength = macBitLength;
        paramBlock.safetyMac    = NULL_PTR; /* default initialization in context of ffi */

#if (COMPILER == COMPILER_TASKING)
/* Suppress TASKING compiler warning about errorCode beeing always SUCCESS. This is not correct since the errorCode can change based on feature
 * switches */
#  pragma warning 549
# endif
# if (ecy_hsm_CSAI_FS_NO_WAIT_MODE == ENABLED)
        /* The resource locking will be handled in @ref ecy_HSM_QuickRoute, if the NO_WAIT mode is enabled */
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
            if (ecy_hsm_CSAI_AES_CMAC == algorithm)
            {
                errorCode = ecy_HSM_QuickRoute(hSession, HSM_FUNC_CMAC_VERIFY, sizeof(paramBlock), &paramBlock, phJob);
            }
            else
            {
                errorCode = ecy_HSM_QuickRoute(hSession, HSM_FUNC_SIPHASH_VERIFY, sizeof(paramBlock), &paramBlock, phJob);
            }

            if(ecy_hsm_CSAI_SUCCESS == errorCode)
            {
                /* The HSM writes the result flag to a buffer defined by ecy_HSM_Configure that is static to the proxy.
                * This is quicker than range checking another pointer
                */
                if (pResultFlag != NULL_PTR)
                {
                    errorCode = ecy_HSM_CopyResultFlag(pResultFlag, hSession);
                }
                else
                {
                    errorCode = ecy_hsm_CSAI_ERR_INVALID_PARAM;
                }
            }
            else
            {
    #if (ecy_hsm_QUICK_ROUTE_FAILFAST == ENABLED)
                quickRouteFailed = TRUE;
    #endif
            }
#if(ecy_hsm_CSAI_FS_NO_WAIT_MODE != ENABLED)
            ecy_HSM_RELEASE_BRIDGE_PORT(errorCode)
#endif /* #if(ecy_hsm_CSAI_FS_NO_WAIT_MODE != ENABLED) */
        }
    }
    /* If the Quick CMAC request failed (e.g. because the AES hardware was busy, or
       the key was not loaded), then we go by the normal route unless ecy_hsm_QUICK_ROUTE_FAILFAST is enabled */
    if (
#if (ecy_hsm_QUICK_ROUTE_FAILFAST == ENABLED)
        (FALSE == quickRouteFailed) &&
#endif
        (ecy_hsm_CSAI_ERR_QUICK_ROUTE_NOT_POSSIBLE == errorCode))
#endif
    {
        /* Initialization */
        Applet_ReturnTypeT result; /* initialized by Applet_Function() */
        /* PRQA S 0759 1 */        /* <Deviation: usage of union is appropriate here */
        Applet_FunctionT    appletFunc = APPFUNC_ID(APPLET_ID_MAC_VERIFY, APPLET_MACVERIFY_STATE_FULL_E);
        HSM_MacVerifyParamT paramBlock;

        /* Parameter update */
        paramBlock.algorithm    = algorithm;
        /* PRQA S 2983 7 */ /* <Deviation: rule_2.2_2983 */
        paramBlock.hKey         = hKey;
        paramBlock.msg          = msg;
        paramBlock.msgLength    = msgLength;
        paramBlock.pExpectedMac = pExpectedMac;
        paramBlock.macBitLength = macBitLength;
        paramBlock.pResultFlag  = pResultFlag;
        paramBlock.safetyMac    = NULL_PTR; /* default initialization */

        /* Execute applet */
        result    = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);
        errorCode = CSAI_ERR(result.stError);
    }

    /* Update given job handle */
    if( phJob != NULL_PTR )
    {
        *phJob = hSession;
    }

    return errorCode;
/* PRQA S 6007 1 */ /* <Deviation: number of function parameters is fixed by design */
}

/* [$Satisfies $DD 471] CSAI Bulk safe MAC verify interface */
/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_BulkMacVerify(ecy_hsm_Csai_SessionHandleT hSession,
                                             ecy_hsm_Csai_JobPriorityT   priority,
                                             const void*                 pTable,
                                             uint32                      numOfEntries,
                                             uint32                      macByteSize,
                                             uint8*                      pData1,
                                             uint32                      data1Size,
                                             uint8*                      pData2,
                                             uint32                      data2Size,
                                             ecy_hsm_Csai_JobHandleT*    phJob)

{
    /* Initialization */
    HSM_BulkMacVerifyParamT paramBlock;
    Applet_ReturnTypeT      result; /* initialized by Applet_Function() */
    /* PRQA S 0759 1 */             /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_MAC_VERIFY, APPLET_MACVERIFY_STATE_BULK_E);

    /* Parameter update */
    /* PRQA S 2983 20 */ /* <Deviation: rule_2.2_2983 */
    /* PRQA S 0316 1 */  /* <Deviation: pTable is always of type pointer to ecy_hsm_Csai_BulkMacControlVerifyJobT */
    paramBlock.pTable       = (const ecy_hsm_Csai_BulkMacControlVerifyJobT*)pTable;
    paramBlock.numOfEntries = numOfEntries;
    paramBlock.macByteSize  = macByteSize;
    paramBlock.data1        = pData1;
    paramBlock.data1Size    = data1Size;
    paramBlock.data2        = pData2;
    paramBlock.data2Size    = data2Size;

    /* Execute applet */
    result    = Applet_Function( hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock );

    /* Update given job handle */
    if( phJob != NULL_PTR )
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
/* PRQA S 6007 1 */ /* <Deviation: number of function parameters is fixed by design */
}

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"
