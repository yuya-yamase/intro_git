/**
 * @file
 ***********************************************************************************************
 * @brief CSAI Message safe verification.
 * This header file is part of the Cryptographic Service Application Interface and specifies
 * types and functions for a safe verification of Message Authentication Codes.
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2021, all rights reserved.
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_CSAI_MAC_BULK_SAFEEXT_H
#define ECY_HSM_CSAI_MAC_BULK_SAFEEXT_H

/**
 * @addtogroup GROUP_CSAI_MAC
 * @{
 */

/* *** includes *******************************************************************************/

#include "ecy_hsm_csai_mac.h"

/* *** typedefs and defines *******************************************************************/

/**
 * Declare a type for the callout function:
 * GetSafeCmacCrc32Calculation(const uint8* Crc_DataPtr,
 *                             uint32 Crc_Length
 *                             uint32 Crc_StartValue32,
 *                             boolean Crc_IsFirstCall)
 *
 * @note Function parameters and return value is aligned with AUTOSAR standard
 * @details This function will return the CRC32   */
typedef uint32 (*ecy_hsm_pFunctionGetSafeCmacCrc32CalculationT)(const uint8* Crc_DataPtr,
                                                                uint32       Crc_Length,
                                                                uint32       Crc_StartValue32,
                                                                boolean      Crc_IsFirstCall);

/** Version scheme for safe CMAC verification. */
typedef enum ecy_hsm_Csai_SafeCMACVersion
{
    ecy_hsm_SafeCMAC_VERIFICATION_SCHEME_V1 = 1U,         /**< Standard safe CMAC verification scheme, must be type of
                                                               @c ecy_hsm_Csai_SafeCMAC_CtxTag_V1                     */
    ecy_hsm_SafeCMAC_VERIFICATION_SCHEME_MAX,             /**< Max version value                                      */
    ecy_hsm_SafeCMAC_VERIFICATION_RESERVED = 0x7FFFFFFFU  /**< Value defined to use memory size of uint32 for enums   */
} ecy_hsm_Csai_SafeCMACVersionT;

/**
 * [$DD 2266]
 *
 * Context for safe CMAC calculation on HSM side.
 * This is for passing data to HSM and back
 * [$Satisfies $SW_ARCH 970]
 */
typedef struct ecy_hsm_Csai_SafeCmacCtx_V1Tag
{
    ecy_hsm_Csai_SafeCMACVersionT versionTag;       /**< Version of BulkMac extension                                 */
    uint32                        isSafeJob;        /**< Indicates if the job shall be processed as a SafeCmac job    */
    uint32                        checksumHostPdu;  /**< checksum of PDU calculated by HOST                           */
    uint32                        checksumHostCmac; /**< checksum of CMAC calculated by HOST                          */
    uint32                        checksumHsm;      /**< checksum of PDU + CMAC calculated by HSM                     */
    uint32                        crcResultFlag;    /**< Result of the CRC(CMAC) verification                         */
    uint32                        isJobValid;       /**< Indicates if the job has been finished and can be processed  */
} ecy_hsm_Csai_SafeCmacCtx_V1;

/**
 * [$DD 2267]
 *
 * Context for safe CMAC calculation on HOST side.
 * Contains the CMAC which is not known on HSM side in SafeCMAC use case.
 * [$Satisfies $SW_ARCH 976]
 */
typedef struct ecy_hsm_Csai_SafeCmacCrcCtxTag
{
    uint32       isSafeJob;                 /**< Indicates if the job shall be treated as a SafeCmac job         */
    uint32       isActive;                  /**< Indicates if the job shall be processed                         */
    const uint8* message;                   /**< Pointer to the message of which the MAC shall be verified       */
    uint32       messageLength;             /**< Length of the message buffer that has to be verified in bytes   */
    const uint8* mac;                       /**< Pointer to the expected MAC                                     */
    uint32       macLength;                 /**< Length of the MAC in bits                                       */
    uint32       checksumHostPdu;           /**< checksum of PDU calculated by HOST                              */
    uint32       checksumHost;              /**< checksum of PDU + CMAC calculated by HOST                       */
    uint32       isJobValid;                /**< Indicates if the job has been finished and can be processed     */
    uint32       safeCmacResultFlag;        /**< Result of the SafeCmac verification                             */
} ecy_hsm_Csai_SafeCmacCrcCtx;

/** @} */ /* GROUP_CSAI_MAC */

/* *** exported interfaces ********************************************************************/

/* *INDENT-OFF* */
#ifdef __cplusplus
extern "C" {
#endif
/* *INDENT-ON* */

/**
 * @addtogroup GROUP_CSAI_BULKSAFECMAC_PREPAREJOBCONTEXT
 * @{
 */

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/**
 * [$DD 1627]
 * [$Satisfies $SW_ARCH 973] [$Satisfies $SW_ARCH 979]
 * Preprocessing interface for safety related fast bulk CMAC jobs
 *
 * @details
 * The function is a part of the safe verification of CMACs. The caller must provide a function pointer
 * to a CRC32 calculation function (independent from hardware or software implementation) according to the AUTOSAR 4.3.1
 * specification.
 * The function will use the provided function to calculate the CRC32 over the message and the CMAC of that message.
 * Truncated MACs will be rounded up to their next 32bit aligned value.
 *
 * The CRC32 context is copied into the ecy_hsm_Csai_SafeCmacCrcCtx array for further processing on HOST side.
 *
 * If the caller marked a Job as isSafeJob, then all MAC related information is deleted and replaced
 * by a null pointer. See the communicated safety documents for more details.
 *
 * @note For better performance, it is recommended that the bulk MAC jobs using the same key be placed adjacent
 * to each other in the job table, so that the keys are not loaded multiple times on the HSM.
 *
 * @note The bulk CMAC interface only processes all entries to a maximal number which shall be defined.
 *
 * @param[in]   pBulkMacJobs                            Array of MAC job descriptions
 * @param[in]   pCrcCtx                                 Array of CRC context elements for each MAC job description
 * @param[in]   numBulkMacJobs                          Number of entries in the pBulkMacJobs array
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                     Checksum calculation and copy of job context was successful
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM           A parameter was invalid
 *  - @ref ecy_hsm_CSAI_ERR_NULL_CALLOUT            CRC Calculation Callout not configured
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_BulkSafeCmacPrepareJobCtx(ecy_hsm_Csai_BulkMacFastVerJob* pBulkMacJobs,
                                                         ecy_hsm_Csai_SafeCmacCrcCtx*    pCrcCtx,
                                                         uint32                          numBulkMacJobs);

/** @} */ /* GROUP_CSAI_BULKSAFECMAC_PREPAREJOBCONTEXT */

/**
 * @addtogroup GROUP_CSAI_BULKSAFECMAC_CALCULATEHOSTDATA
 * @{
 */

/**
 * [$DD 1629]
 * Intermediate Interface for calculations of safety related fast bulk CMAC jobs [$Satisfies $SW_ARCH 972]
 *
 * @details
 * The function is a part of the safe verification of CMACs. The function iterates over each CRC-Context structure.
 * For each active safetyJob with mac != NULL_PTR and a valid macLength it calculates the Host CRC over PDU and
 * CMAC data (concatenated) and sets the isJobValid flag to TRUE.
 *
 * @note
 * As Precondition, the interface @ref ecy_hsm_Csai_BulkSafeCmacPrepareJobCtx has to be executed before.
 * The caller must provide a function pointer to a CRC32 calculation function
 * (independent from hardware or software implementation) according to the AUTOSAR 4.3.1 specification.
 *
 * @param[in,out]   pCrcCtx             Array of CRC context elements for each MAC job description
 * @param[in]       numBulkMacJobs      Number of entries in the pBulkMacJobs array
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                     Input parameters and CRC Calculation Callout are valid
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM           No CRC context elements have been provided
 *  - @ref ecy_hsm_CSAI_ERR_NULL_CALLOUT            CRC Calculation Callout not configured
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_BulkSafeCmacCalculateHostData(ecy_hsm_Csai_SafeCmacCrcCtx* pCrcCtx,
                                                             uint32                       numBulkMacJobs);

/** @} */ /* GROUP_CSAI_BULKSAFECMAC_CALCULATEHOSTDATA */

/**
 * @addtogroup GROUP_CSAI_BULKSAFECMAC_VERIFY
 * @{
 */

/**
 * [$DD 1625]
 * [$Satisfies $SW_ARCH 971]
 * Postprocessing Interface for calculations of safety related fast bulk CMAC jobs
 *
 * @details
 * The function is a part of the safe verification of CMACs. The function iterates over each fast bulk mac jobs and host
 * sided CRC context structures. For each safetyJob it compares the Host CRC with the Hsm CRC that was calculated in
 * before. If a comparison result is positive a job is marked as valid.
 *
 * @note
 * As Precondition, the interface @ref ecy_hsm_Csai_BulkSafeCmacPrepareJobCtx and @ref
 * ecy_hsm_Csai_BulkSafeCmacCalculateHostData has to be executed before.
 *
 * @param[in]   pBulkMacJobs        Array of MAC job descriptions
 * @param[in]   pCrcCtx             Array of CRC context elements for each MAC job description
 * @param[in]   numBulkMacJobs      Number of entries in the pBulkMacJobs and pCrcCtx array
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                     Postprocessing was successful.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM           A parameter was invalid
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_BulkSafeCmacVerify(ecy_hsm_Csai_BulkMacFastVerJob* pBulkMacJobs,
                                                  ecy_hsm_Csai_SafeCmacCrcCtx*    pCrcCtx,
                                                  uint32                          numBulkMacJobs);

/** @} */ /* GROUP_CSAI_BULKSAFECMAC_VERIFY */

/**
 * @addtogroup GROUP_CSAI_BULKSAFECMAC_CALLOUTS
 * @{
 */

/**
 * [$DD 1616]
 * [$Satisfies $SW_ARCH 974]
 *
 * @details
 * The function links the user specific callout to the function call used in the safe CMAC extension.
 * The user specific callout for the CRC32 shall match the parameters from the AUTOSAR standard 4.3.1.
 * The calculation method of the CRC32 is implemented according to IEEE802.3 (Ethernet).
 *
 * @param[in]   pFunctionGetSafeCmacCrc32Calculation        Pointer to CRC32 calculation function
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                 The configuration of the callout was successful
 *  - @ref ecy_hsm_CSAI_ERR_NULL_CALLOUT        The given pointer is a NULL_PTR
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_HSM_ConfigureSafeCmacCallout(ecy_hsm_pFunctionGetSafeCmacCrc32CalculationT pFunctionGetSafeCmacCrc32Calculation);

/** @} */ /* GROUP_CSAI_BULKSAFECMAC_CALLOUTS */

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* *INDENT-OFF* */
#ifdef __cplusplus
} /* extern "C" */
#endif
/* *INDENT-ON* */

#endif /* Multiple inclusion lock */
