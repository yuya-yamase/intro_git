/**
 * @file
 ***********************************************************************************************
 * @brief ECY HSM CSAI Secure Memory based on Authenticated descriptoR Table (SMART)
 * This header file is part of the trusted boot with SMART interface and specifies
 * types and functions
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2022, all rights reserved.
 ***********************************************************************************************/

#ifndef ECY_HSM_CSAI_SMART_TB_H
#define ECY_HSM_CSAI_SMART_TB_H

/**
 * @addtogroup GROUP_CSAI_SMART_TB
 * @{
 */

/* *** includes *******************************************************************************/
#include "Std_Types.h"
#include "ecy_hsm_csai.h"
#include "ecy_hsm_csai_sign.h"
#include "ecy_hsm_csai_keyid.h"

/* *** defines ********************************************************************************/

/** Descriptor supported type */
#define ecy_hsm_CSAI_SMART_TB_DESCRIPTOR_SUPPORTED_TYPE                      (0xAA01)
/** Descriptor supported version */
#define ecy_hsm_CSAI_SMART_TB_DESCRIPTOR_SUPPORTED_VER                       (0xBBBB)

/* *** type declarations **********************************************************************/
/** Enumeration of SMART TB Use cases */
typedef enum ecy_hsm_Csai_SMART_TBUseCaseTag
{
    ecy_hsm_CSAI_SMART_USECASE_UNDEFINED        = 0,            /**< Undefined use case                                   */
    ecy_hsm_CSAI_SMART_USECASE_STANDARD         = 1,            /**< SMART TB use case : Standard / Active Bank Update    */
    ecy_hsm_CSAI_SMART_USECASE_UPDATE_INACTIVE  = 2,            /**< SMART TB use case : Inactive Bank Update             */
    ecy_hsm_CSAI_SMART_USECASE_RESERVED         = 0x7fffffffUL  /**< Reserved value to enforce long enums                 */
} ecy_hsm_Csai_SMART_TBUseCaseT;

/** Structure for passing data between host csai and hsm applet endpoint for SMART TB */
typedef struct ecy_hsm_Csai_SMART_TBDataTag
{
    ecy_hsm_Csai_SMART_TBUseCaseT useCaseId;            /**< Determines the SMART TB use case to be supported */
    void*                         pUsecaseParam;        /**< pointer to receive the user specific structure   */
    const uint32*                 pHeaderAddr;          /**< Pointer to the location of the Update Header or descriptor placed in Shared RAM          */
    uint8*                        pFailedSwPartId;      /**< Pointer to the location of the SW part ID of first failed SW Part          */
    uint32*                       pNumPersistedEntries; /**< Pointer to the location to retrieve the number of reference table entries that were persisted */
} ecy_hsm_Csai_SMART_TBDataT;

/* *********** Deprecated type definitions ***************/

/* *** global constants ***********************************************************************/

/* *** exported interfaces ********************************************************************/
/*************************************************************************************************/

/* *INDENT-OFF* */
#ifdef __cplusplus
extern "C" {
#endif
/* *INDENT-ON* */

/*************************************************************************************************/
/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/**
 * [$DD 2723]
 * SMART TB Init phase - This API indicates the start of an SMART Trusted boot table update process.
 * [$Satisfies $SW_ARCH 77C96BF1]
 * @details
 *   The Memory descriptor address is fetched from HSM Info block. Then the memory descriptor is copied from Host
 *   PFlash to HSM RAM and its signature is verified.
 *   Once the signature of the Fail-safe SW part which includes the Memory Descriptor is verified,
 *   the Fixed and Fail-safe SW part details are parsed and saved temporarily.
 *
 * @param[in]       hSession            Handle to an open HSM session.
 * @param[in]       priority            Scheduling priority of the operation on the HSM.
 * @param[in]       pSmartInitData      Address to the structure @c ecy_hsm_Csai_SMART_TBDataT which contains
 *                                      the information of the @ref ecy_hsm_Csai_SMART_TBUseCaseTag and pointer
 *                                      to buffer to receive the user specific information.
 * @param[out]      phJob               Receives the job handle of the initialized job.
 *
 * @return
 * - @ref ecy_hsm_CSAI_SUCCESS                                  If the memory descriptor parsing and verification is successful
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                        If a parameter is invalid
 * - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION                    There has been an attempt to access HSM address via the CSAI
 * - @ref ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL                     If memory descriptor length is greater than configured RAM buffer size
 * - @ref ecy_hsm_CSAI_ERR_SIGNATURE_VERIF_FAILED               Signature verification failed
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                        The given function is not supported by this HSM build
 * - @ref ecy_hsm_CSAI_ERR_NOT_IMPLEMENTED                      The sign verification mode is not implemented yet
 * - @ref ecy_hsm_CSAI_ERR_CYCURLIB                             An error has been returned by CycurLib
 * - @ref ecy_hsm_CSAI_ERR_SMART_TB_DESCRIPTOR_INFO_INVALID     Memory Descriptor information is invalid/missing
 */
ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_SMART_RefTblInit(ecy_hsm_Csai_SessionHandleT     hSession,
                                                                    ecy_hsm_Csai_JobPriorityT       priority,
                                                                    ecy_hsm_Csai_SMART_TBDataT*     pSmartInitData,
                                                                    ecy_hsm_Csai_JobHandleT*        phJob);

/**
 * [$DD 2724]
 * SMART TB Update phase - Host passes the update header start address as input parameter.
 * [$Satisfies $SW_ARCH 59E8766C] [$Satisfies $SW_ARCH 14CC61CC]
 * @details
 *    Based on update header address passed by Host, the HSM copies the update header to HSM RAM and verifies its signature.
 *    If the verification is successful, the SW part details from the Update Header are parsed and checked for
 *    any Fixed or Fail-safe SW part violations. If no violations was found, then the signature is verified.
 *    Only when the SW parts signatures are verified, then they are marked as entry into a temporary reference table in RAM.
 *    If the signature verification fails, the SW part ID of first failed SW Part is returned through pFailedSwPartId parameter
 *    from structure @c ecy_hsm_Csai_SMART_TBDataT.
 *    The useCaseId must be same as the one provided as an input in the @ref ecy_hsm_Csai_SMART_RefTblInit
 *
 * @param[in]       hSession            Handle to an open HSM session.
 * @param[in]       priority            Scheduling priority of the operation on the HSM.
 * @param[in,out]   pSmartUpdateData    Address to the structure @c ecy_hsm_Csai_SMART_TBDataT which contains
 *                                      Pointer to the location of the Update Header placed in Shared RAM,
 *                                      Pointer to the location of the SW part ID of first failed SW Part
 *                                      and pointer to buffer to receive the user specific information.
 * @param[out]      phJob               Receives the job handle of the initialized job.
 *
 * @return
 * - @ref ecy_hsm_CSAI_SUCCESS                                  If the Update header parsing and verification is successful
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                        If a parameter is invalid
 * - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION                    There has been an attempt to access HSM address via the CSAI
 * - @ref ecy_hsm_CSAI_ERR_SIGNATURE_VERIF_FAILED               Signature verification failed
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                        The given function is not supported by this HSM build
 * - @ref ecy_hsm_CSAI_ERR_NOT_IMPLEMENTED                      The sign verification mode is not implemented yet
 * - @ref ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL                     The update header length is greater than configured RAM buffer size /
 *                                                              no space left in the temporary reference table
 * - @ref ecy_hsm_CSAI_ERR_TB_RTMD_NOT_SUSPENDED                The RTMD is currently not manually suspended
 * - @ref ecy_hsm_CSAI_ERR_SMART_TB_FIXED_BLOCK_VIOLATION       Violation for Fixed block update
 * - @ref ecy_hsm_CSAI_ERR_SMART_TB_FAILSAFE_BLOCK_VIOLATION    Violation for Fail-safe block update
 * - @ref ecy_hsm_CSAI_ERR_INVALID_STATE                        Internal state is not correct (there is no temporary reference table)
 * - @ref ecy_hsm_CSAI_ERR_CYCURLIB                             An error has been returned by CycurLib
 * - @ref ecy_hsm_CSAI_ERR_KEY_PROPERTY_VIOLATION               Key ID for sign verification of update header does not have required property
 */
ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_SMART_RefTblUpdate(ecy_hsm_Csai_SessionHandleT       hSession,
                                                                      ecy_hsm_Csai_JobPriorityT         priority,
                                                                      ecy_hsm_Csai_SMART_TBDataT*       pSmartUpdateData,
                                                                      ecy_hsm_Csai_JobHandleT*          phJob);

/**
 * [$DD 2725]
 * SMART TB Finish phase - This API Indicates the end of Trusted boot table update process.
 * [$Satisfies $SW_ARCH 425724F7]
 * @details
 *   HSM fetches the Host PFlash address ranges to be considered for Host PFlash coverage from HSM Info block.
 *   then HSM checks if the reference Table records covers the entirety of the configured Host PFlash range
 *   without any gaps. ONLY if this check is successful, then the temporary reference table is "merged" with the existing
 *   reference table in HSM DFlash.
 *      - If Trusted Boot table record corresponding to the SW part already exists, then update an existing record with latest information.
 *      - If no Trusted Boot table record already exists, create a new SW-part record in the reference table.
 *   The total number of persisted entries is returned through pNumPersistedEntries parameter
 *   from structure @c ecy_hsm_Csai_SMART_TBDataT.
 *   The useCaseId must be same as the one provided as an input in the @ref ecy_hsm_Csai_SMART_RefTblInit
 *
 * @param[in]       hSession            Handle to an open HSM session.
 * @param[in]       priority            Scheduling priority of the operation on the HSM.
 * @param[in,out]   pSmartFinishData    Address to the structure @c ecy_hsm_Csai_SMART_TBDataT which contains
 *                                      Pointer to the location of the no of ref table entries that were persisted,
 *                                      and pointer to buffer to receive the user specific information.
 * @param[out]      phJob               Receives the job handle of the initialized job.
 *
 * @return
 * - @ref ecy_hsm_CSAI_SUCCESS                                  If the SW-Part was successfully verified
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                        If a parameter is invalid
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                        The given function is not supported by this HSM build
 * - @ref ecy_hsm_CSAI_ERR_INVALID_STATE                        Internal state is not correct (there is no temporary reference table)
 * - @ref ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL                     There is no space left in the current reference table
 * - @ref ecy_hsm_CSAI_ERR_INCONSISTENT_PARAM_SET               The temporary reference table is inconsistent and cannot be persisted
 * - @ref ecy_hsm_CSAI_ERR_SMART_TB_COVERAGE_CHECK_FAILED       Host PFlash coverage check has failed
 */
ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_SMART_RefTblFinish(ecy_hsm_Csai_SessionHandleT       hSession,
                                                                      ecy_hsm_Csai_JobPriorityT         priority,
                                                                      ecy_hsm_Csai_SMART_TBDataT*       pSmartFinishData,
                                                                      ecy_hsm_Csai_JobHandleT*          phJob);

/**
 * [$DD 2726]
 * This is Single-Shot interface supporting Init, Update and Finish Phases of SMART TB in single call
 * This API is recommended to be used only when update header is configured with less than or equal to 12 SW part Info.
 * [$Satisfies $SW_ARCH E09714B6] [$Satisfies $SW_ARCH E86AE17A]
 * @details
 * - The Memory descriptor address is fetched from HSM Info block. Then the memory descriptor is copied from Host
 *   PFlash to HSM RAM and its signature is verified.
 *   Once the signature of the Fail-safe SW part which includes the Memory Descriptor is verified,
 *   the Fixed and Fail-safe SW part details are parsed and saved temporarily.
 * - Based on update header address passed by Host, the HSM copies the update header to HSM RAM and verifies its signature.
 *   If the verification is successful, the SW part details from the Update Header are parsed and checked for
 *   any Fixed or Fail-safe SW part violations. If no violations was found, then the signature is verified.
 *   Only when the SW parts signatures are verified, then they are marked as entry into a temporary reference table in RAM.
 *   If the signature verification fails, the SW part ID of first failed SW Part is returned through pFailedSwPartId parameter
 *   from structure @c ecy_hsm_Csai_SMART_TBDataT.
 * - HSM fetches the Host PFlash address ranges to be considered for Host PFlash coverage from HSM Info block.
 *   then HSM checks if the reference Table records covers the entirety of the configured Host PFlash range
 *   without any gaps. ONLY if this check is successful,the temporary reference table is "merged" with the existing
 *   reference table in HSM DFlash.
 *      - If Trusted Boot table record corresponding to the SW part already exists, then update an existing record with latest information.
 *      - If no Trusted Boot table record already exists, create a new SW-part record in the reference table.
 *   The total number of persisted entries is returned through pNumPersistedEntries parameter
 *   from structure @c ecy_hsm_Csai_SMART_TBDataT.
 *
 *
 * @param[in]       hSession            Handle to an open HSM session.
 * @param[in]       priority            Scheduling priority of the operation on the HSM.
 * @param[in,out]   pSmartFullData      Address to the structure @c ecy_hsm_Csai_SMART_TBDataT which contains
 *                                      the information of the @ref ecy_hsm_Csai_SMART_TBUseCaseTag,
 *                                      Pointer to the location of the Update Header placed in Shared RAM,
 *                                      Pointer to the location of the SW part ID of first failed SW Part,
 *                                      Pointer to the location of the no of ref table entries that were persisted
 *                                      and pointer to buffer to receive the user specific information
 * @param[out]      phJob               Receives the job handle of the initialized job.
 *
 * @return
 * - @ref ecy_hsm_CSAI_SUCCESS                                  If the memory descriptor & update header parsing and verification is successful
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                        If a parameter is invalid
 * - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION                    There has been an attempt to access HSM address via the CSAI
 * - @ref ecy_hsm_CSAI_ERR_SIGNATURE_VERIF_FAILED               Signature verification failed
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                        The given function is not supported by this HSM build
 * - @ref ecy_hsm_CSAI_ERR_NOT_IMPLEMENTED                      The sign verification mode is not implemented yet
 * - @ref ecy_hsm_CSAI_ERR_INVALID_STATE                        Internal state is not correct (there is no temporary reference table)
 * - @ref ecy_hsm_CSAI_ERR_CYCURLIB                             An error has been returned by CycurLib
 * - @ref ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL                     The memory descriptor/update header length is greater than configured RAM buffer size /
 *                                                              no space left in the temporary reference table
 * - @ref ecy_hsm_CSAI_ERR_TB_RTMD_NOT_SUSPENDED                The RTMD is currently not manually suspended
 * - @ref ecy_hsm_CSAI_ERR_SMART_TB_FIXED_BLOCK_VIOLATION       Violation for Fixed block update
 * - @ref ecy_hsm_CSAI_ERR_SMART_TB_FAILSAFE_BLOCK_VIOLATION    Violation for Fail-safe block update
 * - @ref ecy_hsm_CSAI_ERR_INCONSISTENT_PARAM_SET               The temporary reference table is inconsistent and cannot be persisted
 * - @ref ecy_hsm_CSAI_ERR_SMART_TB_DESCRIPTOR_INFO_INVALID     Memory Descriptor information is invalid/missing
 * - @ref ecy_hsm_CSAI_ERR_SMART_TB_COVERAGE_CHECK_FAILED       Host PFlash coverage check has failed
 * - @ref ecy_hsm_CSAI_ERR_KEY_PROPERTY_VIOLATION               Key ID for sign verification of update header does not have required property
 */
ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_SMART_RefTblFull(ecy_hsm_Csai_SessionHandleT     hSession,
                                                                    ecy_hsm_Csai_JobPriorityT       priority,
                                                                    ecy_hsm_Csai_SMART_TBDataT*     pSmartFullData,
                                                                    ecy_hsm_Csai_JobHandleT*        phJob);


/**
 * [$DD 2727]
 * @brief SMART TB Update Descriptor - Host passes the start address of updated descriptor as input parameter.
 * [$Satisfies $SW_ARCH AFB71814] [$Satisfies $SW_ARCH AE662884_v3] [$Satisfies $SW_ARCH 68F623D9]
 * @details
 *    Based on descriptor address passed by Host, the HSM copies the descriptor to HSM RAM.
 *    If the verification of all the descriptor fields are successful only then the descriptor data is
 *    persisted into the DFlash.
 *
 * @param[in]       hSession             Handle to an open HSM session.
 * @param[in]       priority             Scheduling priority of the operation on the HSM.
 * @param[in,out]   pSmartDescriptorData Address to the structure @c ecy_hsm_Csai_SMART_TBDataT which contains
 *                                       Pointer to the location of the Descriptor placed in Shared RAM
 * @param[out]      phJob                Receives the job handle of the initialized job.
 *
 * @return
 * - @ref ecy_hsm_CSAI_SUCCESS                                  If the descriptor parsing and update is successful
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                        If a parameter is invalid
 * - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION                    There has been an attempt to access HSM address via the CSAI
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                        The given function is not supported by this HSM build
 * - @ref ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL                     The descriptor length is greater than configured RAM buffer size
 * - @ref ecy_hsm_CSAI_ERR_KEY_PROPERTY_VIOLATION               Key ID for sign verification of descriptor does not have required property
 *
 */
/* PRQA S 0777 1 */ /* Deviation: rule_5.1_0777 */
ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_SMART_RefTblUpdateDescriptor(ecy_hsm_Csai_SessionHandleT       hSession,
                                                                                ecy_hsm_Csai_JobPriorityT         priority,
                                                                                ecy_hsm_Csai_SMART_TBDataT*       pSmartDescriptorData,
                                                                                ecy_hsm_Csai_JobHandleT*          phJob);

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

#endif /* ECY_HSM_CSAI_SMART_TB_H */
