/**
 * @file ecy_hsm_flash_sync.c
 ***********************************************************************************************
 * @brief CSAI Flash Sync code implementation file
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2020, all rights reserved
 **********************************************************************************************/

#if defined(GUAM)
#include "ecy_hsm_general.h"
#else
#include "ecy_hsm_general_pubcfg.h"
#endif
#include "ecy_hsm_csai.h"
#include "ecy_hsm_proxy.h"
#include "ecy_hsm_applet.h"
#include "ecy_hsm_flash_sync.h"
#include "ecy_hsm_flash_sync_drv.h"
#include "ecy_hsm_general_host_cfg.h"

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
/* PRQA S 3673 1 */ /* Justification: Function fits a generic interface, pointer to const not always feasible */
ecy_hsm_Csai_ErrorT ecy_hsm_Csai_FlashSync_HostRead(void* pParam, uint32 timeout_ms)
{
/* PRQA S 3112 1 */ /* <Deviation: rule_9.1_0> */ /* Justification: Statement has side effect for compiling for other targets and can not be removed
                                                   */
#if (IS_FLASH_SYNC_REQUIRED == ENABLED)
    ecy_hsm_Csai_ErrorT errorCodeTimer;

    /* Initialize the variable below to avoid unknown values if GetCounterValue fails */
    ecy_hsm_Csai_ErrorT errorCodeFlashSync = ecy_hsm_CSAI_ERR_TIMEOUT;
    uint32              startingTime       = 0UL;
    uint32              elapsedTime        = 0UL;

    errorCodeTimer = ecy_HSM_GetCounterValue(&startingTime);

    do
    {
        ecy_hsm_FunctionIRQHandling();
        if (ecy_hsm_CSAI_SUCCESS == errorCodeTimer)
        {
            errorCodeTimer = ecy_HSM_GetElapsedCounterValue(startingTime, &elapsedTime);
        }

        if (ecy_hsm_CSAI_SUCCESS == errorCodeTimer)
        {
            errorCodeFlashSync = ecy_hsm_FlashSyncDrv_HostRead(pParam);
        }
    }
    while(   (ecy_hsm_CSAI_SUCCESS == errorCodeTimer)
          && (elapsedTime < timeout_ms)
          && (ecy_hsm_CSAI_SUCCESS != errorCodeFlashSync));

    /* If the flash state change was not successful return a timeout issue */
    return (ecy_hsm_CSAI_SUCCESS == errorCodeFlashSync) ? ecy_hsm_CSAI_SUCCESS : ecy_hsm_CSAI_ERR_TIMEOUT;
#else
    CSAI_PARAM_UNUSED(pParam);
    CSAI_PARAM_UNUSED(timeout_ms);

    return ecy_hsm_CSAI_ERR_NOT_SUPPORTED;
#endif /* IS_FLASH_SYNC_REQUIRED == ENABLED */
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
/* PRQA S 3673 1 */ /* Justification: Function fits a generic interface, pointer to const not always feasible */
ecy_hsm_Csai_ErrorT ecy_hsm_Csai_FlashSync_HostWrite(void* pParam, uint32 timeout_ms)
{
#if (IS_FLASH_SYNC_REQUIRED == ENABLED)
    ecy_hsm_Csai_ErrorT errorCodeTimer;

    /* Initialize the variable below to avoid unknown values if GetCounterValue fails */
    ecy_hsm_Csai_ErrorT errorCodeFlashSync = ecy_hsm_CSAI_ERR_TIMEOUT;
    uint32              startingTime       = 0UL;
    uint32              elapsedTime        = 0UL;

    errorCodeTimer = ecy_HSM_GetCounterValue(&startingTime);

    do
    {
        ecy_hsm_FunctionIRQHandling();
        if (ecy_hsm_CSAI_SUCCESS == errorCodeTimer)
        {
            errorCodeTimer = ecy_HSM_GetElapsedCounterValue(startingTime, &elapsedTime);
        }

        if (ecy_hsm_CSAI_SUCCESS == errorCodeTimer)
        {
            errorCodeFlashSync = ecy_hsm_FlashSyncDrv_HostWrite(pParam);
        }
    }
    while(   (ecy_hsm_CSAI_SUCCESS == errorCodeTimer)
          && (elapsedTime < timeout_ms)
          && (ecy_hsm_CSAI_SUCCESS != errorCodeFlashSync));

    /* If the flash state change was not successful return a timeout issue */
    return (ecy_hsm_CSAI_SUCCESS == errorCodeFlashSync) ? ecy_hsm_CSAI_SUCCESS : ecy_hsm_CSAI_ERR_TIMEOUT;
#else
    CSAI_PARAM_UNUSED(pParam);
    CSAI_PARAM_UNUSED(timeout_ms);

    return ecy_hsm_CSAI_ERR_NOT_SUPPORTED;
#endif /* IS_FLASH_SYNC_REQUIRED == ENABLED */
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
/* PRQA S 3673 1 */ /* Justification: Function fits a generic interface, pointer to const not always feasible */
ecy_hsm_Csai_ErrorT ecy_hsm_Csai_FlashSync_HostEnd(void* pParam, uint32 timeout_ms)
{
#if (IS_FLASH_SYNC_REQUIRED == ENABLED)
    ecy_hsm_Csai_ErrorT errorCodeTimer;
    /* Initialize the variable below to avoid unknown values if GetCounterValue fails */
    ecy_hsm_Csai_ErrorT errorCodeFlashSync = ecy_hsm_CSAI_ERR_TIMEOUT;
    uint32              startingTime       = 0UL;
    uint32              elapsedTime        = 0UL;

    errorCodeTimer = ecy_HSM_GetCounterValue(&startingTime);

    do
    {
        ecy_hsm_FunctionIRQHandling();
        if (ecy_hsm_CSAI_SUCCESS == errorCodeTimer)
        {
            errorCodeTimer = ecy_HSM_GetElapsedCounterValue(startingTime, &elapsedTime);
        }

        if (ecy_hsm_CSAI_SUCCESS == errorCodeTimer)
        {
            errorCodeFlashSync = ecy_hsm_FlashSyncDrv_HostEnd(pParam);
        }
    }
    while(   (ecy_hsm_CSAI_SUCCESS == errorCodeTimer)
          && (elapsedTime < timeout_ms)
          && (ecy_hsm_CSAI_SUCCESS != errorCodeFlashSync) );

    /* If the flash state change was not successful return a timeout issue */
    return (ecy_hsm_CSAI_SUCCESS == errorCodeFlashSync) ? ecy_hsm_CSAI_SUCCESS : ecy_hsm_CSAI_ERR_TIMEOUT;
#else
    CSAI_PARAM_UNUSED(pParam);
    CSAI_PARAM_UNUSED(timeout_ms);

    return ecy_hsm_CSAI_ERR_NOT_SUPPORTED;
#endif /* IS_FLASH_SYNC_REQUIRED == ENABLED */
}
/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"
