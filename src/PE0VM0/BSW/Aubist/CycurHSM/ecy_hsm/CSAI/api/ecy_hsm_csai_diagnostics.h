/**
 * @file
 *  ********************************************************************************************
 * @brief CSAI Diagnostics jobs
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2020, all rights reserved.
 **********************************************************************************************/

#ifndef ECY_HSM_CSAI_DIAGNOSTICS_H
#define ECY_HSM_CSAI_DIAGNOSTICS_H

/**
 * @addtogroup GROUP_CSAI_DIAGNOSTICS
 * @{
 * Diagnostics API
 *
 */

/* *** includes *******************************************************************************/

#include "ecy_hsm_csai.h"

/* *** type declarations **********************************************************************/

/**
 * Define Dump Use Case Ids
 */
typedef enum ecy_hsm_Csai_DiagnosticsDumpUseCase
{
    ecy_hsm_CSAI_USECASE_UNDEFINED = 0,           /**< Undefined use case                                    */
    ecy_hsm_CSAI_USECASE_DUMP_STD  = 1,           /**< Standard dump use case, as defined in user guide      */
    ecy_hsm_CSAI_USECASE_RESERVED  = 0x7fffffffUL /**< Reserved value to enforce long enums                  */
} ecy_hsm_Csai_DiagnosticsDumpUseCaseT;

/**
 * Define Extended information structures based on Use Case. The type definitions below are used for the
 * use case specific structures. When using a specific use case, the pExtInfo parameter must point to the
 * correct structure type for the use case.
 */

/**
 * Define Memory types for @ref ecy_hsm_CSAI_USECASE_DUMP_STD use case
 */
typedef enum ecy_hsm_Csai_MemType
{
    ecy_hsm_MEMTYPE_PFLASH_CONFIG_DUMP = 0,           /**< Configuration Area dump             */
    ecy_hsm_MEMTYPE_PFLASH_CORE_DUMP   = 1,           /**< Bootloader + Application code dump  */
    ecy_hsm_MEMTYPE_DFLASH_DUMP        = 2,           /**< DFLASH dump                         */
    ecy_hsm_MEMTYPE_RESERVED           = 0x7fffffffUL /**< Reserved value                      */
} ecy_hsm_Csai_MemTypeT;

/**
 * @ref ecy_hsm_Csai_StdDumpParamTag is used for @ref ecy_hsm_CSAI_USECASE_DUMP_STD use case
 */
typedef struct ecy_hsm_Csai_StdDumpParamTag
{
    ecy_hsm_Csai_KeyHandleT hCert;     /**< Handle to certificate to be used, OR a keyId */
    ecy_hsm_Csai_MemTypeT   memTypeId; /**< Determines memory type Identification        */
} ecy_hsm_Csai_StdDumpInfoT;

/* *** global constants ***********************************************************************/

/* *** exported interfaces ********************************************************************/

/* *INDENT-OFF* */
#ifdef __cplusplus
extern "C" {
#endif
/* *INDENT-ON* */

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/**
 * [$DD 2307]
 * @brief Initialization of Diagnostics - HSM dumping
 * [$Satisfies $SW_ARCH 924][$Satisfies $SW_ARCH 928][$Satisfies $SW_ARCH 922]
 * This function initializes the HSM dumping operation.
 *
 * @note HSM DFLASH dumping is not supported on the TC23x.
 *
 * @param[in]   hSession     Handle to the session in which the job is placed.
 * @param[in]   useCaseId    Use Case for Dump operation.
 * @param[in]   pExtInfo     Pointer to the structure to receive the usecase specific parameters which might vary
 *                           based on the @ref ecy_hsm_Csai_DiagnosticsDumpUseCase.
 * @param[out]  pImageSize   Pointer to output the total image size of the dump.
 * @param[out]  pImageAddr   Pointer to output the start address of the image.
 * @param[in]   priority     The priority of the DumpInit job.
 * @param[in]   phJob        Pointer to handle of the initialized job.
 *
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                       The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE            The given job handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                       Another job is still pending completion in this session.
 *                                                     Either finish the previous job or cancel the running job
 *                                                     using @ref ecy_hsm_Csai_CancelJob.
 *   - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED             The HSM dump functionality is not supported for the
 *                                                     provided usecase and parameters.
 *   - @ref ecy_hsm_CSAI_ERR_NOT_IMPLEMENTED           The HSM dump functionality is not implemented in this HSM
 *                                                     build.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_Diagnostics_DumpInit(ecy_hsm_Csai_SessionHandleT          hSession,
                                                                                              ecy_hsm_Csai_DiagnosticsDumpUseCaseT useCaseId,
                                                                                              void*                                pExtInfo,
                                                                                              uint32*                              pImageSize,
                                                                                              uint32*                              pImageAddr,
                                                                                              ecy_hsm_Csai_JobPriorityT            priority,
                                                                                              ecy_hsm_Csai_JobHandleT*             phJob);

/**
 * [$DD 2308]
 * @brief Update function for Diagnostics - HSM dumping
 * [$Satisfies $SW_ARCH 921][$Satisfies $SW_ARCH 924][$Satisfies $SW_ARCH 926][$Satisfies $SW_ARCH 929]
 *
 * This function updates the hsm flash dumping. It will fill the provided buffer with the dumped flash content
 * up to the specified length or until the whole flash was dumped.
 * The function will output the number of bytes dumped on the last call and whether or not more bytes need to
 * be dumped.
 *
 * @param[in]       hSession            Handle to the session in which the job is placed.
 * @param[out]      pBuffer             Buffer to store the dumped flash in.
 * @param[in]       bufferSize          Size of the provided buffer in bytes.
 * @param[out]      pNumBytesDumped     Number of bytes dumped by the last call.
 * @param[out]      pBytesLeftFlag      @c TRUE if bytes are remaining to be dumped
 *                                      and the function has to be called again.
 * @param[in]       phJob               Pointer to handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                       The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE            The given job handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                       Another job is still pending completion in this session.
 *                                                     Either finish the previous job or cancel the running job
 *                                                     using @ref ecy_hsm_Csai_CancelJob.
 *   - @ref ecy_hsm_CSAI_ERR_NOT_IMPLEMENTED           The HSM dump functionality is not implemented in this HSM
 *                                                     build.
 *
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_Diagnostics_DumpUpdate(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                                uint8*                      pBuffer,
                                                                                                uint32                      bufferSize,
                                                                                                uint32*                     pNumBytesDumped,
                                                                                                uint32*                     pBytesLeftFlag,
                                                                                                ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 2309]
 * @brief Finalize function for Diagnostics - HSM dumping
 * [$Satisfies $SW_ARCH 921]
 * [$Satisfies $SW_ARCH 924]
 *
 * This function finishes a diagnostics HSM dump operation.
 *
 * For HSM Dump use case the parameters are ignored, as they are not needed. The function just cleans up the job after
 * the dump operation.
 *
 * @param[in]       hSession            Handle to the session in which the job is placed.
 * @param[in]       phJob               Pointer to handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                       The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE            The given job handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                       Another job is still pending completion in this session.
 *                                                     Either finish the previous job or cancel the running job
 *                                                     using @ref ecy_hsm_Csai_CancelJob.
 *   - @ref ecy_hsm_CSAI_ERR_NOT_IMPLEMENTED           The HSM dump functionality is not implemented in this HSM
 *                                                     build.
 *
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_Diagnostics_DumpFinalize(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                                  ecy_hsm_Csai_JobHandleT*    phJob);

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* *INDENT-OFF* */
#ifdef __cplusplus
} /* extern "C" */
#endif
/* *INDENT-ON* */
/** @} */ // GROUP_CSAI_DIAGNOSTICS

#endif /* Multiple inclusion lock  */
