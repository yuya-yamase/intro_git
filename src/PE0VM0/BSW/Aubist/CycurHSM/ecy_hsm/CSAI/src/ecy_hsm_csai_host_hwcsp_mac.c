/**
 * @file
 ***********************************************************************************************
 * @brief CSAI Interface for the CMAC Generation and Verification on the Host side using the Hardware Crypto Service Provider.
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2023, all rights reserved
 ***********************************************************************************************/
/* [$Satisfies $COMPONENT Host_HWCSP_CSAI] */

/* *** prologue  ******************************************************************************/

/**
 * @addtogroup GROUP_HOST_HWCSP_MAC
 * @{
 */

/* *** includes *******************************************************************************/
#include "ecy_hsm_csai.h"
#include "ecy_hsm_csai_host_hwcsp_callout.h"
#include "ecy_hsm_csai_host_hwcsp_mac.h"
#include "ecy_hsm_general_host_cfg.h"
#include "ecy_hsm_host_hwcsp_mac_mcal.h"
#if (ecy_hsm_HOST_HWCSP_MAC_QUICK == ENABLED)
# include "ecy_hsm_hwcsp_keystore_cfg_arch.h"
# include "ecy_hsm_srv_host_hwcsp_callout.h"
#endif /* (ecy_hsm_HOST_HWCSP_MAC_QUICK == ENABLED) */

/* *** defines ********************************************************************************/

/* *** type declarations **********************************************************************/

/* *** global constants ***********************************************************************/

/* *** local variables ************************************************************************/

/* *** local function prototypes **************************************************************/

/* *** public implementation  *****************************************************************/

/* PRQA S 1503 5 */ /* Deviation: rule_2.1_1503_CSAI */
/* PRQA S 3673 4 */ /* Justification: Function fits a generic interface, pointer to const not always feasible */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL
ecy_hsm_Csai_HostHwCsp_MacGenerate(ecy_hsm_Csai_WorkspaceIdT                          hostWksp,
                                   ecy_hsm_Csai_JobHandleT*                           phJob,
                                   ecy_hsm_Csai_HostHwCsp_MacGen_ParamSetAndVersionT* pParamSetAndVersion)
{
    ecy_hsm_Csai_ErrorT errorCode;

#if (ecy_hsm_HOST_HWCSP_MAC_QUICK == ENABLED)

    /* Use case param struct must not be nullpointer because that is where all the function specific parameters are */
    if (NULL_PTR == pParamSetAndVersion)
    {
        return ecy_hsm_CSAI_ERR_INVALID_PARAM;
    }

    /* Check Use Case ID. In this version only ecy_hsm_CSAI_HOST_HWCSP_MAC_GENERATE_V0 is supported */
    if (ecy_hsm_CSAI_HOST_HWCSP_MAC_GENERATE_V0 != pParamSetAndVersion->paramSetVersion)
    {
        return ecy_hsm_CSAI_ERR_NOT_SUPPORTED;
    }

    /* Currently only Quickroute mode is implemented */
    if (ecy_hsm_CSAI_INTERFACE_MODE_QUICKROUTE != pParamSetAndVersion->hostHwCspMacGenParam.paramV0.interfaceMode)
    {
        return ecy_hsm_CSAI_ERR_NOT_IMPLEMENTED;
    }

    /* With Quickroute the job handle must be nullpointer to make sure that the user understands that he will not get a job handle */
    if (NULL_PTR != phJob)
    {
        return ecy_hsm_CSAI_ERR_INVALID_PARAM;
    }

    /* Quickroute is currently only available with cpu mode */
    if (ecy_hsm_CSAI_HARDWARE_MODE_CPU != pParamSetAndVersion->hostHwCspMacGenParam.paramV0.hardwareMode)
    {
        return ecy_hsm_CSAI_ERR_NOT_SUPPORTED;
    }

    /* Quickroute is currently only available with CMAC algorithm */
    if (ecy_hsm_CSAI_AES_CMAC != pParamSetAndVersion->hostHwCspMacGenParam.paramV0.algorithm)
    {
        return ecy_hsm_CSAI_ERR_NOT_SUPPORTED;
    }

    errorCode = ecy_hsm_HostHwCspSrv_GetCallout(hostWksp);

    if (ecy_hsm_CSAI_SUCCESS == errorCode)
    {
        /* Call MCAL level function directly */
        errorCode = ecy_hsm_HostHwCspMcal_MacGenerate_Reg_Cmac(hostWksp,
                                                               pParamSetAndVersion->hostHwCspMacGenParam.paramV0.hKey,
                                                               pParamSetAndVersion->hostHwCspMacGenParam.paramV0.msg,
                                                               pParamSetAndVersion->hostHwCspMacGenParam.paramV0.msgLength,
                                                               pParamSetAndVersion->hostHwCspMacGenParam.paramV0.macBitLength,
                                                               pParamSetAndVersion->hostHwCspMacGenParam.paramV0.pMac);
        /* Release resource after call */
        ecy_hsm_HostHwCspSrv_ReleaseCallout(hostWksp);
    }

#else
    CSAI_PARAM_UNUSED(hostWksp);
    CSAI_PARAM_UNUSED(phJob);
    CSAI_PARAM_UNUSED(pParamSetAndVersion);
    errorCode = ecy_hsm_CSAI_ERR_NOT_SUPPORTED;
#endif /* (ecy_hsm_HOST_HWCSP_MAC_QUICK == ENABLED) */

    return errorCode;
} /* PRQA S 6010 */ /* Deviation: Early returns in case of error handling is accepted */

/* PRQA S 1503 5 */ /* Deviation: rule_2.1_1503_CSAI */
/* PRQA S 3673 4 */ /* Justification: Function fits a generic interface, pointer to const not always feasible */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL
ecy_hsm_Csai_HostHwCsp_MacVerify(ecy_hsm_Csai_WorkspaceIdT                          hostWksp,
                                 ecy_hsm_Csai_JobHandleT*                           phJob,
                                 ecy_hsm_Csai_HostHwCsp_MacVer_ParamSetAndVersionT* pParamSetAndVersion)
{
    ecy_hsm_Csai_ErrorT errorCode;

#if (ecy_hsm_HOST_HWCSP_MAC_QUICK == ENABLED)

    /* Use case param struct must not be nullpointer because that is where all the function specific parameters are */
    if (NULL_PTR == pParamSetAndVersion)
    {
        return ecy_hsm_CSAI_ERR_INVALID_PARAM;
    }

    /* Check Use Case ID. In this version only ecy_hsm_CSAI_HOST_HWCSP_MAC_VERIFY_V0 is supported */
    if (ecy_hsm_CSAI_HOST_HWCSP_MAC_VERIFY_V0 != pParamSetAndVersion->paramSetVersion)
    {
        return ecy_hsm_CSAI_ERR_NOT_SUPPORTED;
    }

    /* Currently only Quickroute mode is implemented */
    if (ecy_hsm_CSAI_INTERFACE_MODE_QUICKROUTE != pParamSetAndVersion->hostHwCspMacVerParam.paramV0.interfaceMode)
    {
        return ecy_hsm_CSAI_ERR_NOT_IMPLEMENTED;
    }

    /* With Quickroute the job handle must be nullpointer to make sure that the user understands that he will not get a job handle */
    if (NULL_PTR != phJob)
    {
        return ecy_hsm_CSAI_ERR_INVALID_PARAM;
    }

    /* Quickroute is currently only available with cpu mode */
    if (ecy_hsm_CSAI_HARDWARE_MODE_CPU != pParamSetAndVersion->hostHwCspMacVerParam.paramV0.hardwareMode)
    {
        return ecy_hsm_CSAI_ERR_NOT_SUPPORTED;
    }

    /* Quickroute is currently only available with CMAC algorithm */
    if (ecy_hsm_CSAI_AES_CMAC != pParamSetAndVersion->hostHwCspMacVerParam.paramV0.algorithm)
    {
        return ecy_hsm_CSAI_ERR_NOT_SUPPORTED;
    }

    errorCode = ecy_hsm_HostHwCspSrv_GetCallout(hostWksp);

    if (ecy_hsm_CSAI_SUCCESS == errorCode)
    {
        /* Call MCAL level function directly */
        errorCode = ecy_hsm_HostHwCspMcal_MacVerify_Reg_Cmac(hostWksp,
                                                             pParamSetAndVersion->hostHwCspMacVerParam.paramV0.hKey,
                                                             pParamSetAndVersion->hostHwCspMacVerParam.paramV0.msg,
                                                             pParamSetAndVersion->hostHwCspMacVerParam.paramV0.msgLength,
                                                             pParamSetAndVersion->hostHwCspMacVerParam.paramV0.macBitLength,
                                                             pParamSetAndVersion->hostHwCspMacVerParam.paramV0.pExpectedMac,
                                                             pParamSetAndVersion->hostHwCspMacVerParam.paramV0.pResultFlag);
        /* Release resource after call */
        ecy_hsm_HostHwCspSrv_ReleaseCallout(hostWksp);
    }

#else
    CSAI_PARAM_UNUSED(hostWksp);
    CSAI_PARAM_UNUSED(phJob);
    CSAI_PARAM_UNUSED(pParamSetAndVersion);
    errorCode = ecy_hsm_CSAI_ERR_NOT_SUPPORTED;
#endif /* (ecy_hsm_HOST_HWCSP_MAC_QUICK == ENABLED) */

    return errorCode;
} /* PRQA S 6010 */ /* Deviation: Early returns in case of error handling is accepted */

/* *** private implementation  ****************************************************************/

/* *** epilogue  ******************************************************************************/

/** @} */ // GROUP_HOST_HWCSP_MAC
