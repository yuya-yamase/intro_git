/**
 * @file
 ***********************************************************************************************
 * @brief Trusted Platform Module (TPM) CSAI.
 * This header file is part of the Cryptographic Service Application Interface and specifies
 * types and functions for the Trusted Platform Module (TPM) operations
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2024, all rights reserved.
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_SERVICE_TPM_H
#define ECY_HSM_SERVICE_TPM_H

/* *** includes *******************************************************************************/
#include "ecy_hsm_csai_tpm.h"

/**
 * @addtogroup GROUP_CSAI_TPM
 * @{
 */

/** Structure for the data passed to a release tpm value */
typedef struct ecy_hsm_Tpm_ReleaseParamTag
{
    ecy_hsm_Csai_KeyHandleT                               hKeyToRelease;            /**< Parameters for releasing tpm value of handle to the TPM data */
    ecy_hsm_Csai_Tpm_ReleaseTpmValue_ParamSetAndVersionT* pTpmReleaseExtendedParam; /**< Pointer to extendable parameter sets, used by the corresponding
                                                                                     extended CSAI */
} ecy_hsm_Tpm_ReleaseParamT;

/** Structure for the data passed to load tpm value */
typedef struct ecy_hsm_Tpm_LoadParamTag
{
    ecy_hsm_Csai_KeyIdT                                 persistedKeyId;             /**< Parameters for load tpm value of persisted key ID */
    ecy_hsm_Csai_KeyHandleT*                            phTpmValue;                 /**< Pointer to handle tpm value */
    ecy_hsm_Csai_Tpm_LoadTpmValue_ParamSetAndVersionT*  pTpmLoadExtendedParam;      /**< Pointer to extendable parameter sets, used by the corresponding
                                                                                     extended CSAI */
} ecy_hsm_Tpm_LoadParamT;

/** Structure for the data passed to delete tpm value */
typedef struct ecy_hsm_Tpm_DeleteParamTag
{
    ecy_hsm_Csai_KeyIdT                                   persistedKeyId;           /**< Parameters for deleting tpm value of persisted key ID */
    ecy_hsm_Csai_Tpm_DeleteTpmValue_ParamSetAndVersionT*  pTpmDeleteExtendedParam;  /**< Pointer to extendable parameter sets, used by the corresponding
                                                                                     extended CSAI */
} ecy_hsm_Tpm_DeleteParamT;

/**
 * @}
 */

/* *** exported interfaces ********************************************************************/

/* *INDENT-OFF* */
#ifdef __cplusplus
    extern "C" {
#endif
/* *INDENT-ON* */

/* *INDENT-OFF* */
#ifdef __cplusplus
    } /* extern "C" */
#endif
/* *INDENT-ON* */

#endif /* ECY_HSM_SERVICE_TPM_H  */
