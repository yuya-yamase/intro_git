/**
 * @file
 *
 ***********************************************************************************************
 * @brief BULK Safe MAC verification services
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2021, all rights reserved.
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

/**
 * @addtogroup GROUP_CSAI_MAC_BULKMACFAST_SAFE_EXT
 * @{
 */

/* *** includes *******************************************************************************/
#if defined(GUAM)
#include "ecy_hsm_general.h"
#else
#include "ecy_hsm_general_pubcfg.h"
#endif
#include "ecy_hsm_basicsrvs.h"
#include "ecy_hsm_proxy.h"
#include "ecy_hsm_host_proxy.h"
#include "ecy_hsm_csai_mac_bulk_safe_ext.h"
#include "ecy_hsm_applet_mac_verify.h"
#include "ecy_hsm_applet_manager.h"

/* *** defines ********************************************************************************/
#define ecy_hsm_CRC32_START_VALUE   (0xFFFFFFFFU)  /**< Start value for CRC32 calculation */
#define ecy_hsm_MAX_AES_CMAC_BITS   (128U)         /**< Maximum bit number for the AES CMAC */

/**
 * Init value for the host checksum parameter in the safe context
 */
#define ecy_hsm_CHKSUM_HOST_INIT_VALUE  (0x55AAAA55U)

/**
 * Init value for the hsm checksum parameter in the safe context
 */
#define ecy_hsm_CHKSUM_HSM_INIT_VALUE   (0xAA5555AAU)

/* *** type declarations **********************************************************************/

/* *** global constants ***********************************************************************/

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_VAR_PTR
#include "ecy_hsm_MemMap.h"

/** Pointer to the GetSafeCmacCrc32Calculation() callout */
static ecy_hsm_pFunctionGetSafeCmacCrc32CalculationT ecy_hsm_pCalloutGetSafeCmacCrc32Calculation = NULL_PTR;

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_VAR_PTR
#include "ecy_hsm_MemMap.h"

/* *** local variables ************************************************************************/

/* *** local function prototypes **************************************************************/

/* *** public implementation  *****************************************************************/

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_BulkSafeCmacPrepareJobCtx(ecy_hsm_Csai_BulkMacFastVerJob* pBulkMacJobs,
                                                         ecy_hsm_Csai_SafeCmacCrcCtx*    pCrcCtx,
                                                         uint32                          numBulkMacJobs)
{
    uint32                       jobIndex;
    uint32                       csPdu;
    uint32                       csCmac;
    uint32                       macLengthBytes;
    ecy_hsm_Csai_SafeCmacCtx_V1* pCurrentSafeJobCtx;

    if (NULL_PTR == ecy_hsm_pCalloutGetSafeCmacCrc32Calculation)
    {
        return ecy_hsm_CSAI_ERR_NULL_CALLOUT;
    }

    if ((NULL_PTR == pBulkMacJobs) || (NULL_PTR == pCrcCtx))
    {
        return ecy_hsm_CSAI_ERR_INVALID_PARAM;
    }

    /* Loop over all given Jobs */
    for (jobIndex = 0U; jobIndex < numBulkMacJobs; jobIndex++)
    {

        if (FALSE == pBulkMacJobs[jobIndex].isActive)
        {
            pCrcCtx[jobIndex].isActive = FALSE;
            continue;
        }

        /* Update error flag */
        pBulkMacJobs[jobIndex].errorCode     = ecy_hsm_CSAI_SUCCESS;
        pBulkMacJobs[jobIndex].resultFlag    = FALSE;
        pCrcCtx[jobIndex].safeCmacResultFlag = FALSE;

        /* Check for NULL_PTR */
        if (   (NULL_PTR                  != pBulkMacJobs[jobIndex].extensionCtx)
            && (NULL_PTR                  != pBulkMacJobs[jobIndex].message     )
            && (NULL_PTR                  != pBulkMacJobs[jobIndex].mac         )
            && (ecy_hsm_MAX_AES_CMAC_BITS >= pBulkMacJobs[jobIndex].macLength   ))
        {
            /* PRQA S 0316 1 */ /* Justification: cast from void ptr to object ptr type is safe in this context*/
            pCurrentSafeJobCtx = (ecy_hsm_Csai_SafeCmacCtx_V1*)pBulkMacJobs[jobIndex]
                                                                         .extensionCtx;

            /* Calculate CRC32 over PDU and CMAC */
            macLengthBytes = ecy_hsm_BITS_TO_FULL_BYTE_LENGTH(pBulkMacJobs[jobIndex].macLength);

            csPdu  = ecy_hsm_pCalloutGetSafeCmacCrc32Calculation(pBulkMacJobs[jobIndex].message,
                                                                 pBulkMacJobs[jobIndex].messageLength,
                                                                 ecy_hsm_CRC32_START_VALUE,
                                                                 TRUE);
            csCmac = ecy_hsm_pCalloutGetSafeCmacCrc32Calculation(pBulkMacJobs[jobIndex].mac,
                                                                 macLengthBytes,
                                                                 ecy_hsm_CRC32_START_VALUE,
                                                                 TRUE);


            /* Check if current pBulkMacJobs[jobIndex] is a safety relevant job */
            if (ecy_hsm_SafeCMAC_VERIFICATION_SCHEME_V1 == pCurrentSafeJobCtx->versionTag)
            {
                if (TRUE == pCurrentSafeJobCtx->isSafeJob)
                {
                    /* Update safe ctx */
                    pCurrentSafeJobCtx->checksumHostPdu  = csPdu;
                    pCurrentSafeJobCtx->checksumHostCmac = csCmac;
                    pCurrentSafeJobCtx->checksumHsm      = ecy_hsm_CHKSUM_HSM_INIT_VALUE;
                    pCurrentSafeJobCtx->crcResultFlag    = FALSE;
                    pCurrentSafeJobCtx->isJobValid       = FALSE;

                    /* Update CRC32 ctx */
                    pCrcCtx[jobIndex].isSafeJob          = pCurrentSafeJobCtx->isSafeJob;
                    pCrcCtx[jobIndex].isActive           = TRUE;
                    pCrcCtx[jobIndex].message            = pBulkMacJobs[jobIndex].message;
                    pCrcCtx[jobIndex].messageLength      = pBulkMacJobs[jobIndex].messageLength;
                    pCrcCtx[jobIndex].mac                = pBulkMacJobs[jobIndex].mac;
                    pCrcCtx[jobIndex].macLength          = pBulkMacJobs[jobIndex].macLength;
                    pCrcCtx[jobIndex].checksumHostPdu    = csPdu;
                    pCrcCtx[jobIndex].checksumHost       = ecy_hsm_CHKSUM_HOST_INIT_VALUE;
                    pCrcCtx[jobIndex].isJobValid         = FALSE;

                    /* Remove mac from pBulkMacJobs as part of safety mechanism */
                    pBulkMacJobs[jobIndex].mac = NULL_PTR;
                }
                else
                {
                    /* Update invalid safe ctx */
                    pCurrentSafeJobCtx->checksumHostPdu  = 0U;
                    pCurrentSafeJobCtx->checksumHostCmac = 0U;
                    pCurrentSafeJobCtx->checksumHsm      = 0U;
                    pCurrentSafeJobCtx->crcResultFlag    = FALSE;
                    pCurrentSafeJobCtx->isJobValid       = FALSE;

                    pCrcCtx[jobIndex].isSafeJob          = pCurrentSafeJobCtx->isSafeJob;
                    pCrcCtx[jobIndex].isActive           = FALSE;
                    pCrcCtx[jobIndex].message            = NULL_PTR;
                    pCrcCtx[jobIndex].messageLength      = 0U;
                    pCrcCtx[jobIndex].mac                = NULL_PTR;
                    pCrcCtx[jobIndex].macLength          = 0U;
                    pCrcCtx[jobIndex].checksumHostPdu    = 0U;
                    pCrcCtx[jobIndex].checksumHost       = 0U;
                    pCrcCtx[jobIndex].isJobValid         = FALSE;
                }
            }
            else
            {
                /* invalid extension context version detected */
                pBulkMacJobs[jobIndex].errorCode = ecy_hsm_CSAI_ERR_INVALID_PARAM;
                pCrcCtx[jobIndex].isActive = FALSE;
            }
        }
        else
        {
            pBulkMacJobs[jobIndex].errorCode = ecy_hsm_CSAI_ERR_INVALID_PARAM;
            pCrcCtx[jobIndex].isActive = FALSE;
        }
    }
    return ecy_hsm_CSAI_SUCCESS;
    /* PRQA S 6010 1 */ /* <Deviation: Early returns in case of error handling is accepted */
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_BulkSafeCmacCalculateHostData(ecy_hsm_Csai_SafeCmacCrcCtx* pCrcCtx,
                                                             uint32                       numBulkMacJobs)
{
    ecy_hsm_Csai_ErrorT error = ecy_hsm_CSAI_SUCCESS;
    uint32              jobIndex;
    uint32              macLengthBytes;

    if (NULL_PTR == ecy_hsm_pCalloutGetSafeCmacCrc32Calculation)
    {
        return ecy_hsm_CSAI_ERR_NULL_CALLOUT;
    }

    if (NULL_PTR == pCrcCtx)
    {
        return ecy_hsm_CSAI_ERR_INVALID_PARAM;
    }

    /* Loop over all given Jobs */
    for (jobIndex = 0U; jobIndex < numBulkMacJobs; jobIndex++)
    {
        if ((TRUE == pCrcCtx[jobIndex].isActive) && (TRUE == pCrcCtx[jobIndex].isSafeJob))
        {
            if ((NULL_PTR == pCrcCtx[jobIndex].mac) || (ecy_hsm_MAX_AES_CMAC_BITS < pCrcCtx[jobIndex].macLength))
            {
                pCrcCtx[jobIndex].isJobValid = FALSE;
            }
            else
            {
                macLengthBytes    = ecy_hsm_BITS_TO_FULL_BYTE_LENGTH(pCrcCtx[jobIndex].macLength);
                pCrcCtx[jobIndex].checksumHost = ecy_hsm_pCalloutGetSafeCmacCrc32Calculation(pCrcCtx[jobIndex].mac,
                                                                                       macLengthBytes,
                                                                                       pCrcCtx[jobIndex].checksumHostPdu,
                                                                                       FALSE);
                pCrcCtx[jobIndex].isJobValid   = TRUE;
            }
        }
    }
    return error;
    /* PRQA S 6010 2 */ /* <Deviation: Early returns in case of error handling is accepted */
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_BulkSafeCmacVerify(ecy_hsm_Csai_BulkMacFastVerJob* pBulkMacJobs,
                                                  ecy_hsm_Csai_SafeCmacCrcCtx*    pCrcCtx,
                                                  uint32                          numBulkMacJobs)
{
    uint32                       jobIndex;
    ecy_hsm_Csai_SafeCmacCtx_V1* pCurrentSafeJobCtx;

    if ((NULL_PTR == pBulkMacJobs) || (NULL_PTR == pCrcCtx))
    {
        return ecy_hsm_CSAI_ERR_INVALID_PARAM;
    }

    /* Loop over all given Jobs */
    for (jobIndex = 0U; jobIndex < numBulkMacJobs; jobIndex++)
    {

        if (FALSE == pBulkMacJobs[jobIndex].isActive)
        {
            continue;
        }

        if (NULL_PTR == pBulkMacJobs[jobIndex].extensionCtx)
        {
            pBulkMacJobs[jobIndex].errorCode     = ecy_hsm_CSAI_ERR_INVALID_PARAM;
            pBulkMacJobs[jobIndex].resultFlag    = FALSE;
            pBulkMacJobs[jobIndex].isValid       = TRUE;
            pCrcCtx[jobIndex].safeCmacResultFlag = FALSE;
        }
        else
        {
            /* PRQA S 0316 1 */ /* Justification: cast from void ptr to object ptr type is safe in this context */
            pCurrentSafeJobCtx = (ecy_hsm_Csai_SafeCmacCtx_V1*)pBulkMacJobs[jobIndex].extensionCtx;

            if (ecy_hsm_SafeCMAC_VERIFICATION_SCHEME_V1 != pCurrentSafeJobCtx->versionTag)
            {
                /* this error should be set by previous processign steps if context is invalid version */
                pBulkMacJobs[jobIndex].errorCode     = ecy_hsm_CSAI_ERR_INVALID_PARAM;
                pBulkMacJobs[jobIndex].resultFlag    = FALSE;
                pBulkMacJobs[jobIndex].isValid       = TRUE;
                pCrcCtx[jobIndex].safeCmacResultFlag = FALSE;
                continue;
            }

            /* Check if current pBulkMacJobs[jobIndex] is a safety relevant job */
            if (FALSE == pCurrentSafeJobCtx->isSafeJob)
            {
                continue;
            }

            pBulkMacJobs[jobIndex].resultFlag    = FALSE;
            pCrcCtx[jobIndex].safeCmacResultFlag = FALSE;

            if (ecy_hsm_CSAI_SUCCESS == pBulkMacJobs[jobIndex].errorCode)
            {
                if ((FALSE == pCurrentSafeJobCtx->isJobValid) || (FALSE == pCrcCtx[jobIndex].isJobValid))
                {
                    /* If HOST or HSM sided isJobValid flag is set to false, the job is interrupted by an error */
                    pBulkMacJobs[jobIndex].errorCode = ecy_hsm_CSAI_ERR_INTERNAL_PARAM;
                }
                else if ((TRUE == pCurrentSafeJobCtx->crcResultFlag) && (pCurrentSafeJobCtx->checksumHsm == pCrcCtx[jobIndex].checksumHost))
                {
                    pBulkMacJobs[jobIndex].resultFlag    = TRUE;
                    pCrcCtx[jobIndex].safeCmacResultFlag = TRUE;
                }
                else
                {
                    /* do nothing */
                }
            }
            pBulkMacJobs[jobIndex].isValid = TRUE;
        }
    }

    return ecy_hsm_CSAI_SUCCESS;
    /* PRQA S 6010 2 */ /* <Deviation: Early returns in case of error handling is accepted */
    /* PRQA S 6009 1 */ /* <Deviation: Refactoring due to HIS level makes this code less readable */
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_HSM_ConfigureSafeCmacCallout(ecy_hsm_pFunctionGetSafeCmacCrc32CalculationT pFunctionGetSafeCmacCrc32Calculation)
{
    ecy_hsm_Csai_ErrorT errorCode = ecy_hsm_CSAI_SUCCESS;

    if(NULL_PTR == pFunctionGetSafeCmacCrc32Calculation)
    {
        errorCode = ecy_hsm_CSAI_ERR_NULL_CALLOUT;
    }
    else
    {
        ecy_hsm_pCalloutGetSafeCmacCrc32Calculation = pFunctionGetSafeCmacCrc32Calculation;
    }

    return(errorCode);
}

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* *** epilogue  ******************************************************************************/

/** @} */ // GROUP_CSAI_MAC_BULKMACFAST_SAFE_EXT
