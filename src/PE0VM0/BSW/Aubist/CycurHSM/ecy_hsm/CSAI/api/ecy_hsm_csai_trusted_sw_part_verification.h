/**
 * @file
 ***********************************************************************************************
 * @brief ECY HSM CSAI trusted sw part verification operations
 * This header file is part of the trusted sw part verification interface and specifies
 * types and functions
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2022, all rights reserved
 **********************************************************************************************/

#ifndef ECY_HSM_CSAI_TRUSTED_SW_PART_VERIFICATION_H
#define ECY_HSM_CSAI_TRUSTED_SW_PART_VERIFICATION_H

/**
 * @addtogroup GROUP_CSAI_TRUSTED_SW_PART_VERIFICATION
 * @{
 */

/* *** includes *******************************************************************************/
#include "Std_Types.h"
#include "ecy_hsm_csai.h"
#include "ecy_hsm_csai_sign.h"
#include "ecy_hsm_csai_hash.h"
#include "ecy_hsm_csai_keyid.h"

/* *** defines ********************************************************************************/

/** Maximum number of hash algorithms which can be calculated in parallel during sw-part verification */
#define ecy_hsm_CSAI_TRUSTED_SW_PART_VERIFICATION_MAX_PARALLEL_HASHES_V1 0x00000004UL

/* *** type declarations **********************************************************************/
/** @brief Enumeration to define the use cases for sw-part verification */
typedef enum ecy_hsm_Csai_TB_SwPartVerifUseCaseTag
{
    ecy_hsm_Csai_TB_SwPartVerif_USE_CASE_INIT_V1      = 0x00U,      /**< Trusted SW part verification use case initialize for version 1*/
    ecy_hsm_Csai_TB_SwPartVerif_USE_CASE_UPDATE_V1    = 0x01U,      /**< Trusted SW part verification use case update for version 1*/
    ecy_hsm_Csai_TB_SwPartVerif_USE_CASE_SIGNATURE_V1 = 0x02U,      /**< Trusted SW part verification use case set signature for version 1*/
    ecy_hsm_Csai_TB_SwPartVerif_USE_CASE_FINISH_V1    = 0x03U,      /**< Trusted SW part verification use case finish for version 1*/
    ecy_hsm_Csai_TB_SwPartVerif_USE_CASE_FINALIZE_V1  = 0x04U,      /**< Trusted SW part verification use case finalize for version 1*/
    ecy_hsm_Csai_TB_SwPartVerif_USE_CASE_MAX          = 0x05U,      /**< Max version value                                        */
    ecy_hsm_Csai_TB_SwPartVerif_USE_CASE_RESERVED     = 0x7FFFFFFFU /**< Value defined to use memory size of uint32 for enums     */
} ecy_hsm_Csai_TB_SwPartVerifUseCaseT;

/** Structure for passing data between host csai and hsm applet endpoint for trusted sw-part initialisation*/
typedef struct ecy_hsm_Csai_TB_SwPartInitData_V1Tag
{
    uint8 numbOfHashes;         /**< The number of how many hashes have to be calculated in parallel */
    uint8 swPartId;             /**< The identifier of the SW part to be verified */
    uint8 swPartVerifBootMode;  /**< The boot mode of the SW part */
    uint8 swPartVerifRtmdOrder; /**< The RTMD order of the SW part */
    ecy_hsm_Csai_HashAlgorithmT
        calcHashAlgorithm[ecy_hsm_CSAI_TRUSTED_SW_PART_VERIFICATION_MAX_PARALLEL_HASHES_V1]; /**< Array of hash algorithm which will be calculated in
                                                                                                parallel */
    uint32 swPartAddress;                                                                    /**< The address of the SW Part */
} ecy_hsm_Csai_TB_SwPartInitData_V1T;

/** Structure for passing data between host csai and hsm applet endpoint for trusted sw-part update*/
typedef struct ecy_hsm_Csai_TB_SwPartUpdateData_V1Tag
{
    const uint8* pSwPartChunk;        /**< A data chunk of the current SW part */
    uint32       swPartChunkNumBytes; /**< The length in bytes of the data chunk */
} ecy_hsm_Csai_TB_SwPartUpdateData_V1T;

/** Structure for passing data between host csai and hsm applet endpoint for trusted sw-part signature information */
typedef struct ecy_hsm_Csai_TB_SwPartSetSignData_V1Tag
{
    uint8 swPartVerifSignMode;     /**< The signature verification mode (must be ecy_hsm_CSAI_TB_VERIFMODE_KEYSTORE_PUBKEY
                                    *  or ecy_hsm_CSAI_TB_VERIFMODE_KEYSTORE_CERT or ecy_hsm_CSAI_TB_VERIFMODE_MEMMAPPED_CERT) */
    uint8  reservedBytes_1;        /**< Reserved Byte */
    uint16 swPartSignatureType;    /**< The type of the signature, in case
                                    *  the swPartVerifSignMode is ecy_hsm_CSAI_TB_VERIFMODE_KEYSTORE_PUBKEY
                                    *  or ecy_hsm_CSAI_TB_VERIFMODE_KEYSTORE_CERT (see: @ref ecy_hsm_Csai_SignatureSchemeT) */
    uint32 swPartSignatureAddress; /**< The address of the signature */
    /* PRQA S 0750 2 */ /* <Justification: Definition of a union is appropriate here */
    union
    {
        ecy_hsm_Csai_KeyIdT swPartKeyId; /**< The key ID of the certificate or public key, in case
                                          *  the swPartVerifSignMode is ecy_hsm_CSAI_TB_VERIFMODE_KEYSTORE_PUBKEY
                                          *  or ecy_hsm_CSAI_TB_VERIFMODE_KEYSTORE_CERT */
        uint32 swPartCertAddress;        /**< The address of the certificate, in case the swPartVerifSignMode is
                                          *  ecy_hsm_CSAI_TB_VERIFMODE_MEMMAPPED_CERT */
    } swPartVerifParam;            /**< Parameter structure for sw-part verification */
} ecy_hsm_Csai_TB_SwPartSetSignData_V1T;

/** Structure for passing data between host csai and hsm applet endpoint for trusted sw-part finish*/
typedef struct ecy_hsm_Csai_TB_SwPartFinishData_V1Tag
{
    uint32* pResultFlag; /**< Verification result information */

} ecy_hsm_Csai_TB_SwPartFinishData_V1T;

/** Structure for passing data between host csai and hsm applet endpoint for trusted sw-part finalize*/
typedef struct ecy_hsm_Csai_TB_SwPartFinalizeData_V1Tag
{
    uint32* pNumPersistedEntries; /**< Pointer to the location of the number of reference
                                       table entries that were persisted */
} ecy_hsm_Csai_TB_SwPartFinalizeData_V1T;

/** Structure for the data passed to a trusted sw-part operation */
typedef struct ecy_hsm_Csai_TB_SwPartContextTag
{
    ecy_hsm_Csai_TB_SwPartVerifUseCaseT useCase; /**< Version for the current job.
                                                  *  The version defines the content and type of the sw part parameters */
    void* pTrustedSwPartData;                    /**< Pointer to the trusted sw part context data structure @c ecy_hsm_Csai_TB_SwPartInitData_V1T
                                                  *  @c ecy_hsm_Csai_TB_SwPartUpdateData_V1T @c ecy_hsm_Csai_TB_SwPartSetSignData_V1T
                                                  *  @c ecy_hsm_Csai_TB_SwPartFinishData_V1T @c ecy_hsm_Csai_TB_SwPartFinalizeData_V1T */
} ecy_hsm_Csai_TB_SwPartContextT;

/** Structure for the data passed to a trusted sw-part operation */
typedef struct TB_SwPartParamTag
{
    ecy_hsm_Csai_TB_SwPartContextT* pSwPartCtx; /**< Parameter structure for trusted sw-part operation */
} TB_SwPartParamT;

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
 * [$DD 1862]
 * @brief Create a temporary SW-part reference table entry in RAM, initialize CMAC and parallel HASH calculation for this
 *        SW-part.
 * [$Satisfies $SW_ARCH 1137]
 *
 * At HSM startup the temporary reference table in RAM contains no entries. This function creates a new entry in
 * the temporary reference table, for a SW-part that the host is willing to update in the host PFlash (a SW-part is
 * a contiguous host flash region). The RTMD must be suspended until the SW-part is updated.(This is done automatically
 * in case the manual RTMD suspension is disabled.)
 *
 * The CMAC, HASH and length calculation for this SW-part are initialized. The newly created reference table entry will be
 * considered valid only after subsequent calls to the @ref ecy_hsm_Csai_TrustedSwPartUpdate and
 * @ref ecy_hsm_Csai_TrustedSwPartFinish functions.
 *
 * The specified SW-part becomes the active SW-part in this session for all @ref ecy_hsm_Csai_TrustedSwPartUpdate subsequent
 * and @ref ecy_hsm_Csai_TrustedSwPartSetSignature calls and until @ref ecy_hsm_Csai_TrustedSwPartFinish is called.
 *
 * The following session rules apply:
 * - Only one SW-part may be active at a given time in a given session.
 * - Multi-instance are not support.
 *
 * The following consistency checks are performed before initiating the new SW-part:
 * - If an entry for the same SW-part already exists in the temporary reference table, this entry is re-used (it is
 * invalidated and overwritten, no new entry is created)
 * - The SW-part start address @p swPartAddr shall not be within the address range of an existing SW-part in the
 * temporary reference table (there shall be no overlapping SW-parts). The User of this interface is responsible,
 * that the different entries don't overlap. If an overlap takes place, the older entry will be inconsistent and
 * errors will occur during Trusted Boot/RTMD.
 *
 * The feature performs a verification of a software part with a signature for a defined software part layout @ref ecy_hsm_Csai_TB_SwPartInitData_V1T.
 * The signature range is excluded from the signature verification, while the CMAC is calculated over the whole SwPart.
 *
 * The result of the SwPart verification is stored in @c pResultInfo of the @c ecy_hsm_Csai_TrustedSwPartFinalize.
 * After successful validation the new software part is persisted in the reference table.
 *
 * @note
 * - Functions for managing the trusted boot reference table are available in the lifecycle of
 *   the CycurHSM @ref ecy_hsm_CSAI_LC_STATE_PRODUCTION and afterwards.
 *   These API's can only be used only after the table has been initialised, either through lifecycle switch or 'full init' API
 * - In case the RTMD feature with the RTMD manual suspension is enabled, the RTMD must be manually
 *   suspended. In case the RTMD is not manually suspended an error will be returned.
 * - Currently supported hash algorithm: @ref ecy_hsm_CSAI_SHA2_224 @ref ecy_hsm_CSAI_SHA2_256
 *   @ref ecy_hsm_CSAI_SHA2_384 @ref ecy_hsm_CSAI_SHA2_512
 * - Function is only available if @ref ecy_hsm_Csai_Protection_DisableSecCritFunction is not called before
 *
 * @warning
 *   In case the RTMD manual suspension is enabled, the behavior of the RTMD suspension will be changed.
 *   - If RTMD manual suspension is disabled, the RTMD will be automatically suspended by the function call
 *     and reactivated after a reset. This is the old behavior.
 *   - If RTMD manual suspension is enabled, the automatic RTMD suspension is deactivated.
 *     The RTMD can only be suspended with @ref ecy_hsm_Csai_TbRtmdSuspend and also needs to be manually
 *     reactivated with @ref ecy_hsm_Csai_TbRtmdReactivate. The RTMD must be suspended befor the function
 *     ecy_hsm_Csai_TbRefTblPartInit is called. If the RTMD is not suspended an error code will be returned.
 * - The following attributes are OTP and cannot be changed:
 * -- SW-part address
 * -- Part ID
 * -- Signature type
 * -- Key ID
 * -- Verification Boot Mode
 * -- RTMD order
 * -- Signature mode
 *
 * @param[in]       hSession         Handle to an open HSM session.
 * @param[in]       priority         Scheduling priority of the operation on the HSM.
 * @param[in,out]   pSwPartInitCtx   Address to the structure @ref ecy_hsm_Csai_TB_SwPartContextT which contains
 *                                   the information of the @ref ecy_hsm_Csai_TB_SwPartVerifUseCaseT and points
 *                                   to the sw part init data struct @ref ecy_hsm_Csai_TB_SwPartInitData_V1T
 * @param[out]      phJob            Receives the job handle of the initialized job.
 *
 * @return
 * - @ref ecy_hsm_CSAI_SUCCESS                      Success
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM            Inconsistent parameters have been entered (e.g. invalid ID and address)
 * - @ref ecy_hsm_CSAI_ERR_TB_RTMD_NOT_SUSPENDED    The RTMD is currently not manually suspended
 * - @ref ecy_hsm_CSAI_ERR_SECFUNC_LOCKED           Security critical functions are currently disabled
 *                                                  (see @ref ecy_hsm_Csai_Protection_DisableSecCritFunctions)
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_TrustedSwPartInit(ecy_hsm_Csai_SessionHandleT     hSession,
                                                                     ecy_hsm_Csai_JobPriorityT       priority,
                                                                     ecy_hsm_Csai_TB_SwPartContextT* pSwPartInitCtx,
                                                                     ecy_hsm_Csai_JobHandleT*        phJob);

/**
 * [$DD 1863]
 * Update the CMAC and HASH's of the active SW-part with the given data chunk and calculate the new length of the SW-part
 * [$Satisfies $SW_ARCH 1137]
 *
 * The CMAC and HASH's of the active SW-part for the given session is updated with the content of the provided data chunk.
 *
 * The active SW-part must have been initialized by a previous call to @ref ecy_hsm_Csai_TrustedSwPartInit.
 *
 * The function may be called repeatedly until the complete SW-part has been processed by the HSM.
 * When the complete SW-part has been processed, the @ref ecy_hsm_Csai_TrustedSwPartFinish function must be called.
 *
 * Important restrictions:
 * - The SW-part must be continuous in the host memory. It is therefore not allowed for the host to "skip"
 * some areas within the SW-part address range.
 * - The chunks must be processed in strict steadily increasing host address order.
 * - In case the signature is located in the SW-part the function @ref ecy_hsm_Csai_TrustedSwPartSetSignature must be called
 *   with the information about the signature before the chunk with the signature is send to the HSM. Because of the HASH
 *   calculation.
 * - If the certificate based signature verification mode is used, the certificate must be written into the real
 *   location when the data chunk will be updated.
 *
 * Failing to apply these rules would result in a wrongly computed CMAC and subsequent TrustedBoot / RTMD verification
 * failures.
 *
 *
 * @note
 * - Functions for managing the trusted boot reference table are available in the lifecycle of the CycurHSM
 *   @ref ecy_hsm_CSAI_LC_STATE_PRODUCTION and afterwards @ref ecy_hsm_Csai_SetLifecycleState.
 * - Function is only available if @ref ecy_hsm_Csai_Protection_DisableSecCritFunction is not called before.
 *
 * @param[in]       hSession         Handle to an open HSM session.
 * @param[in]       priority         Scheduling priority of the operation on the HSM.
 * @param[in,out]   pSwPartUpdateCtx Address to the structure @ref ecy_hsm_Csai_TB_SwPartContextT which contains
 *                                   the information of the @ref ecy_hsm_Csai_TB_SwPartVerifUseCaseT and points
 *                                   to the sw part update data struct @ref ecy_hsm_Csai_TB_SwPartUpdateData_V1T
 * @param[out]      phJob            Receives the job handle of the initialized job.
 *
 * @return
 * - @ref ecy_hsm_CSAI_SUCCESS                      Success
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM            Inconsistent parameters have been entered (e.g. invalid ID and address)
 * - @ref ecy_hsm_CSAI_ERR_TB_RTMD_NOT_SUSPENDED    The RTMD is currently not manually suspended
 * - @ref ecy_hsm_CSAI_ERR_SECFUNC_LOCKED           Security critical functions are currently disabled
 *                                                  (see @ref ecy_hsm_Csai_Protection_DisableSecCritFunctions)
 *
 * @see ecy_hsm_Csai_TrustedSwPartInit, ecy_hsm_Csai_TrustedSwPartUpdate, ecy_hsm_Csai_TrustedSwPartSetSignature, ecy_hsm_Csai_TrustedSwPartFinish
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_TrustedSwPartUpdate(ecy_hsm_Csai_SessionHandleT     hSession,
                                                                       ecy_hsm_Csai_JobPriorityT       priority,
                                                                       ecy_hsm_Csai_TB_SwPartContextT* pSwPartUpdateCtx,
                                                                       ecy_hsm_Csai_JobHandleT*        phJob);

/**
 * [$DD 1864]
 * Set the address and type of the signature of the active SW-part and specify the keystore-slot of the certificate or public key or
 * specify the address of the certificate in memory.
 * [$Satisfies $SW_ARCH 1137]
 *
 * The address and type of the signature and the key ID of the certificate or public key of the active SW-part
 * for the given session are updated or the address of the signature and the memory address of the certificate
 * of the active SW-part for the given session are updated.
 *
 * The active SW-part must have been initialized by a previous call to @ref ecy_hsm_Csai_TrustedSwPartInit.
 *
 * The function can be called after @ref ecy_hsm_Csai_TrustedSwPartInit or after @ref ecy_hsm_Csai_TrustedSwPartUpdate put must be called before the
 * chunk with the signature is send to the HSM.
 * @note
 * - Functions for managing the trusted boot reference table are available in the lifecycle of
 *   the CycurHSM @ref ecy_hsm_CSAI_LC_STATE_PRODUCTION and afterwards.
 * - The signature shall be located completely inside or completely outside of the respective SW-part, it shall not overlap it (in the sense that the
 * signature shall not be located half-way outside and half-way inside the SW-part).
 * - Function is only available if @ref ecy_hsm_Csai_Protection_DisableSecCritFunction is not called before.
 * - In case the signature is located in the SW-part the function @ref ecy_hsm_Csai_TrustedSwPartSetSignature must be called
 *   with the information about the signature before the chunk with the signature is send to the HSM. Because of the HASH
 *   calculation.
 *
 * @warning
 * The function must be called before the chunk with the signature information is send to the HSM.
 *
 * @param[in]       hSession    Handle to an open HSM session.
 * @param[in]       priority    Scheduling priority of the operation on the HSM.
 * @param[in,out]   pSetSignCtx Address to the structure @ref ecy_hsm_Csai_TB_SwPartContextT which contains
 *                              the information of the @ref ecy_hsm_Csai_TB_SwPartVerifUseCaseT and points
 *                              to the sw part set signature data struct @ref ecy_hsm_Csai_TB_SwPartSetSignData_V1T
 * @param[out]      phJob       Receives the job handle of the initialized job.
 *
 * @return
 * - @ref ecy_hsm_CSAI_SUCCESS              Success
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM    Inconsistent parameters have been entered (e.g. invalid ID, address or signature verification mode)
 * - @ref ecy_hsm_CSAI_ERR_INVALID_STATE    Current RefTable state is incorrect
 * - @ref ecy_hsm_CSAI_ERR_SECFUNC_LOCKED   Security critical functions are currently disabled
 *                                          (see @ref ecy_hsm_Csai_Protection_DisableSecCritFunctions)
 *
 * @see ecy_hsm_Csai_TbRefTblPartInit, ecy_hsm_Csai_TbRefTblPartUpdate, ecy_hsm_Csai_TbRefTblPartFinish, ecy_hsm_Csai_TbRefTblFinalize
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_TrustedSwPartSetSignature(ecy_hsm_Csai_SessionHandleT     hSession,
                                                                             ecy_hsm_Csai_JobPriorityT       priority,
                                                                             ecy_hsm_Csai_TB_SwPartContextT* pSetSignCtx,
                                                                             ecy_hsm_Csai_JobHandleT*        phJob);

/**
 * [$DD 1865]
 * Finish the CMAC calculation and hash calculation and perform the security checks (OTP parameter, signature validation)
 * of the active SW-part.
 * [$Satisfies $SW_ARCH 1135] [$Satisfies $SW_ARCH 1136] [$Satisfies $SW_ARCH 1137]
 *
 * The previously initiated CMAC and HASH calculation (through calls to @ref ecy_hsm_Csai_TrustedSwPartInit and @ref
 * ecy_hsm_Csai_TrustedSwPartUpdate) for a given SW-part is finished.
 *
 * The CMAC reference value of the SW-part and the SW-part length are updated into the corresponding temporary
 * reference table entry, which is then considered to be valid (i.e. ready to be persisted in non-volatile storage).
 *
 * The HASH will be used for the verification calculation over the SW-part.
 *
 * In order for the updated SW-part to be considered by the TrustedBoot & RTMD features, the reference table must be
 * persisted into non-volatile storage by calling the @ref ecy_hsm_Csai_TrustedSwPartFinalize function.
 *
 * After @ref ecy_hsm_Csai_TrustedSwPartFinish is called, there is no more "active SW-part" for the given session.
 * A new active SW-part may be initiated by calling the @ref ecy_hsm_Csai_TrustedSwPartInit function.
 *
 * The deletion of an entry and changing of the OTP attributes will only be allowed when the device is
 * in lifecycle state @ref ecy_hsm_CSAI_LC_STATE_PRIVMODEDEV.
 * or @ref ecy_hsm_CSAI_LC_STATE_PRIVMODESERIAL or a valid secure access is executed.
 * Otherwise the function will return @ref ecy_hsm_CSAI_ERR_TB_SECACC_PRIVILEGE_MISSING.
 * If an error is returned by this function the complete update procedure is cancelled and no @ref ecy_hsm_Csai_TrustedSwPartFinalize is possible.
 *
 * @note
 * - Functions for managing the trusted boot reference table are available in the lifecycle of the CycurHSM @ref ecy_hsm_CSAI_LC_STATE_PRODUCTION and
 * afterwards.
 * - Function is only available if @ref ecy_hsm_Csai_Protection_DisableSecCritFunction is not called before
 *
 * @param[in]       hSession         Handle to an open HSM session.
 * @param[in]       priority         Scheduling priority of the operation on the HSM.
 * @param[in,out]   pSwPartFinishCtx Address to the structure @ref ecy_hsm_Csai_TB_SwPartContextT which contains
 *                                   the information of the @ref ecy_hsm_Csai_TB_SwPartVerifUseCaseT and points
 *                                   to the sw part finish data struct @ref ecy_hsm_Csai_TB_SwPartFinishData_V1T
 * @param[out]      phJob            Receives the job handle of the initialized job.
 *
 *
 * @return
 * - @ref ecy_hsm_CSAI_SUCCESS              Success
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM    Inconsistent parameters have been entered (e.g. invalid ID and address)
 * - @ref ecy_hsm_CSAI_ERR_SECFUNC_LOCKED   Security critical functions are currently disabled
 *                                          (see @ref ecy_hsm_Csai_Protection_DisableSecCritFunctions)
 * - @ref ecy_hsm_CSAI_ERR_TB_SECACC_PRIVILEGE_MISSING  No Privilege to delete an entry of the trusted boot table
 * - @ref ecy_hsm_CSAI_ERR_TRUSTED_SW_PART_OTP_VIOLATION    A OTP attribute violation is detected
 *
 * @see ecy_hsm_Csai_TrustedSwPartInit, ecy_hsm_Csai_TrustedSwPartUpdate, ecy_hsm_Csai_TrustedSwPartFinish,
 *      ecy_hsm_Csai_TrustedSwPartFinalize
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_TrustedSwPartFinish(ecy_hsm_Csai_SessionHandleT     hSession,
                                                                       ecy_hsm_Csai_JobPriorityT       priority,
                                                                       ecy_hsm_Csai_TB_SwPartContextT* pSwPartFinishCtx,
                                                                       ecy_hsm_Csai_JobHandleT*        phJob);

/**
 * [$DD 1866]
 * Persist the temporary reference table updates into HSM non-volatile storage
 * [$Satisfies $SW_ARCH 1135] [$Satisfies $SW_ARCH 1137]
 *
 * This function terminates a sequence of calls to @ref ecy_hsm_Csai_TrustedSwPartInit, @ref ecy_hsm_Csai_TrustedSwPartUpdate
 * and @ref ecy_hsm_Csai_TrustedSwPartFinish for one or multiple SW parts. For each Sw-part a temporary reference
 * table entry was created, which has to be persisted into HSM non-volatile storage for use by the TrustedBoot
 * and RTMD features.
 *
 * The current reference table in non-volatile storage is updated with the information from the temporary reference table
 * according to the following rules:
 * - only valid reference table entries are considered (i.e. entries for which the CMAC calculation was completed)
 *      - if there are invalid entries in the temporary reference table, it is considered inconsistent and the
 *      reference table in non-volatile storage is not updated. An error is returned to the caller.
 * - if the same SW-part (SwId or start address) exists in the current reference table, the existing entry is updated
 *      - if the SW-part length in the temporary reference table is 0, the corresponding entry is deleted from the current
 *      reference table. This allows the host to change the memory layout of the application software, by calling
 *      @ref ecy_hsm_Csai_TrustedSwPartInit followed by @ref ecy_hsm_Csai_TrustedSwPartFinish (without any call to
 *      @ref ecy_hsm_Csai_TrustedSwPartUpdate).
 * - if the SW-part doesn't exist in the current reference table
 *      - if there is space left in the current reference table, a new entry is added to the table
 *      - if there is no space left in the current reference table, an error is returned.
 *
 * In case of any error an inconsistent state is to be assumed. This means that the reference table in non-volatile
 * storage may not correspond to the current state of the host software. This means that subsequent verifications
 * performed by the TrustedBoot & RTMD features after the next HSM startup are likely to fail.
 *
 * In order to ensure that the temporary reference table is consistent the following rules apply:
 * - For each SW-part that was previously initiated by the host (through a call to @ref ecy_hsm_Csai_TrustedSwPartInit),
 * the @ref ecy_hsm_Csai_TrustedSwPartFinish function must have been called.
 * - @ref ecy_hsm_Csai_TrustedSwPartFinalize shall be called at most once and after all SW-parts have been processed.
 *
 * After having being persisted successfully, the temporary reference table in RAM is cleared (no entries anymore).
 * The host may check the pNumPersistedEntries parameter to ensure that all SW-parts that it has programmed have
 * been updated in the reference table and will therefore be considered after the next startup by the TrustedBoot
 * and RTMD features.
 *
 * In case of error the temporary reference table in RAM is also cleared. The host must restart the flash programming
 * process from the beginning.
 *
 * @note
 * - Functions for managing the trusted boot reference table are available in the lifecycle of the CycurHSM
 *   @ref ecy_hsm_CSAI_LC_STATE_PRODUCTION and afterwards.
 * - Function is only available if @ref ecy_hsm_Csai_Protection_DisableSecCritFunction is not called before.
 *
 * @param[in]       hSession           Handle to an open HSM session.
 * @param[in]       priority           Scheduling priority of the operation on the HSM.
 * @param[in,out]   pSwPartFinalizeCtx Address to the structure @ref ecy_hsm_Csai_TB_SwPartContextT which contains
 *                                     the information of the @ref ecy_hsm_Csai_TB_SwPartVerifUseCaseT and points
 *                                     to the sw part finalize data struct @ref ecy_hsm_Csai_TB_SwPartFinishData_V1T
 * @param[out]      phJob              Receives the job handle of the initialized job.
 *
 * @return
 * - @ref ecy_hsm_CSAI_SUCCESS              Success
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM    Inconsistent parameters have been entered (e.g. invalid ID and address)
 * - @ref ecy_hsm_CSAI_ERR_NO_SPACE_REFTBL  No space left in the reference table
 * - @ref ecy_hsm_CSAI_ERR_SECFUNC_LOCKED   Security critical functions are currently disabled
 *                                          (see @ref ecy_hsm_Csai_Protection_DisableSecCritFunctions)
 *
 * @see ecy_hsm_Csai_TrustedSwPartInit, ecy_hsm_Csai_TrustedSwPartFinish
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_TrustedSwPartFinalize(ecy_hsm_Csai_SessionHandleT     hSession,
                                                                         ecy_hsm_Csai_JobPriorityT       priority,
                                                                         ecy_hsm_Csai_TB_SwPartContextT* pSwPartFinalizeCtx,
                                                                         ecy_hsm_Csai_JobHandleT*        phJob);

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

#endif /* ECY_HSM_CSAI_TRUSTED_SW_PART_VERIFICATION_H */
