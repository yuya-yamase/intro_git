/**
 * @file
 ***********************************************************************************************
 * @brief ECY HSM CSAI manual tabs verification operations
 * This header file is part of the manual tabs verification interface and specifies
 * types and functions
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2021, all rights reserved
 **********************************************************************************************/

#ifndef ECY_HSM_CSAI_MANUAL_TABS_VERIFICATION_H
#define ECY_HSM_CSAI_MANUAL_TABS_VERIFICATION_H

/**
 * @addtogroup GROUP_CSAI_MANUAL_TABS_VERIFICATION
 * @{
 */

/* *** includes *******************************************************************************/
#include "Std_Types.h"
#include "ecy_hsm_csai.h"
#include "ecy_hsm_csai_sign.h"

/* *** defines ********************************************************************************/

/* *** type declarations **********************************************************************/
/** Version scheme for manual tabs verification data structure */
typedef enum ecy_hsm_Csai_ManualTabsVerifyUseCase
{
    ecy_hsm_ManualTabsVerification_SCHEME_V1 = 1U,        /**< Standard Manual Tabs verification scheme, must be type of
                                                               @c ecy_hsm_Csai_TB_swPartLayout_V1T                      */
    ecy_hsm_ManualTabsVerification_SCHEME_MAX,            /**< Max version value                                        */
    ecy_hsm_ManualTabsVerification_RESERVED = 0x7FFFFFFFU /**< Value defined to use memory size of uint32 for enums     */
} ecy_hsm_Csai_ManualTabsVerifyUseCaseT;

/** Structure to pass a software part information */
typedef struct ecy_hsm_Csai_swPartInfoTag {
    uint32 id;           /**< The software part identification number */
    uint32 startAddress; /**< The software part start address */
    uint32 length;       /**< The software part length */
} ecy_hsm_Csai_TB_swPartInfoT;

/** Struct to use when passing a software part that abides by the header/data structure */
typedef struct ecy_hsm_Csai_swPartLayout_V1
{
    /* SwPart information */
    ecy_hsm_Csai_TB_swPartInfoT   swPartInfo;         /**< Data structure containing information about the software part */
    ecy_hsm_Csai_CertHandleT      hCert;              /**< Handle to the certificate to retrieve the public key */

    /* SwPart header */
    uint32                        headerStartAddress; /**< The SW part header start address */
    uint32                        headerLength;       /**< Length of the SW part file header in bytes
                                                           * Signature is calculated from headerStartAddress till headerStartAddress + headerLength */
    uint32                        signStartAddress;   /**< Start address of the signature */
    ecy_hsm_Csai_SignatureSchemeT signatureAlgorithm; /**< Signature algorithm of the header signature */

    /* SwPart data field */
    uint32                        dataStartAddress;   /**< The SW part data start address */
    uint32                        dataLength;         /**< Length of the SW part file data in bytes
                                                           * digest is calculated from dataStartAddress till dataStartAddress + dataLength */
    uint32                        digestAddress;      /**< Address of the digest in the file header */
    ecy_hsm_Csai_HashAlgorithmT   hashAlgorithm;      /**< Algorithm used to verify digest */

    /* Job result info */
    uint32*                       pResultInfo;        /**< pointer for verification result information as result of operation*/
} ecy_hsm_Csai_TB_swPartLayout_V1T;

/** Structure for the context with use case ID to select the relevant data structure */
typedef struct ecy_hsm_Csai_RequestManualVerifyContextTag
{
    ecy_hsm_Csai_ManualTabsVerifyUseCaseT useCase;               /**< Use case for the current job.
                                                                      * The use case defines the content and type of @c pManualTabsVerifyData */
    void*                                 pManualTabsVerifyData; /**< Data structure for the selected use case*/
} ecy_hsm_Csai_RequestManualVerifyContextT;

/** Structure for the data passed to a manual tabs software part verification operation */
typedef struct ecy_hsm_Csai_TB_RequestManualVerifyParamTag
{
    /**< The Address of manual Tabs Context data structure @c ecy_hsm_Csai_RequestManualVerifyContextT */
    ecy_hsm_Csai_RequestManualVerifyContextT* pManualTabsCtx;
} ecy_hsm_Csai_TB_RequestManualVerifyParamT;

/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by @ref ecy_hsm_Csai_swPartInfoTag
 */
#define TB_swPartInfoT ecy_hsm_Csai_TB_swPartInfoT
/**
 * @deprecated by @ref ecy_hsm_Csai_swPartLayout_V1
 */
#define TB_swPartLayout_V1T ecy_hsm_Csai_TB_swPartLayout_V1T
/**
 * @deprecated by @ref ecy_hsm_Csai_TB_RequestManualVerifyParamTag
 */
#define TB_RequestManualVerifyParamT ecy_hsm_Csai_TB_RequestManualVerifyParamT
/**
 * @deprecated by @ref ecy_hsm_Csai_TB_RequestManualVerifyParamTag
 */
#define TB_RequestManualVerifyParamTag ecy_hsm_Csai_TB_RequestManualVerifyParamTag
/**
 * @deprecated by @ref ecy_hsm_Csai_swPartLayout_V1
 */
#define swPartLayout_V1 ecy_hsm_Csai_swPartLayout_V1
/**
 * @deprecated by @ref ecy_hsm_Csai_swPartInfoTag
 */
#define swPartInfoTag ecy_hsm_Csai_swPartInfoTag
/* *** global constants ***********************************************************************/

/* *** exported interfaces ********************************************************************/
/*************************************************************************************************/

/* *INDENT-OFF* */
#ifdef __cplusplus
extern "C" {
#endif
/* *INDENT-ON* */

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/*************************************************************************************************/
/**
 * [$DD 1658]
 * @brief Start a manual tabs software part verification.
 * [$Satisfies $SW_ARCH 1031][$Satisfies $SW_ARCH 1033][$Satisfies $SW_ARCH 1036]
 *
 * The feature performs a verification of a software part with a signature for a defined software part layout.
 * The fallback mechanism is deactivated when this feature is active. The addresses of the different parts of
 * the new software container must be set in the corresponding @c ecy_hsm_Csai_TB_swPartLayout_V1T structure.
 * The signature range is excluded from the signature verification, while the CMAC is calculated over the whole SwPart.
 *
 * The result of the SwPart verification is stored in @c pResultInfo of the @c ecy_hsm_Csai_RequestManualVerifyContextT.
 * After successful validation the new software part is persisted in the reference table.
 *
 * @param[in]       hSession         Handle to an open HSM session.
 * @param[in]       priority         Scheduling priority of the operation on the HSM.
 * @param[in,out]   pManualTabsCtx   Address to the data structure that holds the manual tabs context information
 * @param[out]      phJob            Receives the job handle of the initialized job.
 *
 * @return
 * - @ref ecy_hsm_CSAI_SUCCESS                      Success
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM            Inconsistent parameters have been entered
 * - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION        Address violation has occurred
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED            Applet function not supported
 * - @ref ecy_hsm_CSAI_ERR_CERT_WRONG_SIGNATURE     Signature verification was not successful
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_TabsVerify_SwPart(ecy_hsm_Csai_SessionHandleT               hSession,
                                                 ecy_hsm_Csai_JobPriorityT                 priority,
                                                 ecy_hsm_Csai_RequestManualVerifyContextT* pManualTabsCtx,
                                                 ecy_hsm_Csai_JobHandleT*                  phJob);

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"

/**
 * @}
 */

/* *INDENT-OFF* */
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* ECY_HSM_CSAI_MANUAL_TABS_VERIFICATION_H */
