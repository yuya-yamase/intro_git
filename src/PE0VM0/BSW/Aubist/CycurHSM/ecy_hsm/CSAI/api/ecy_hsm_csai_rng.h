/**
 * @file
 ***********************************************************************************************
 * @brief CSAI Random number generation.
 * This header file is part of the Cryptographic Service Application Interface and specifies
 * types and functions for generating random numbers with CycurHSM.
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2014, all rights reserved.
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_CSAI_RNG_H
#define ECY_HSM_CSAI_RNG_H

/**
 * @addtogroup GROUP_CSAI_RNG
 * @{
 */

/* *** includes *******************************************************************************/

#include "ecy_hsm_csai.h"
/* *** defines ********************************************************************************/

/* *** type declarations **********************************************************************/

/* *** global constants ***********************************************************************/

/* *** exported interfaces ********************************************************************/

/* *INDENT-OFF* */
#ifdef __cplusplus
extern "C" {
#endif
/* *INDENT-ON* */

/**
 * @addtogroup GROUP_CSAI_RANDOM_GENERATE
 * @{
 */

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/**
 * [$DD 2454]
 * Generate random data from a pseudo-random number generator source built into the HSM.
 * [$Satisfies $SW_ARCH F7F35662]
 *
 * @note
 * Some devices provide a dedicated TRNG/PRNG hardware peripheral producing random numbers
 * compliant to NIST SP800-90a and BSI AIS 20/31.
 *
 * @note
 * By default, the PRNG is implemented using the NIST SP 800-90A CTR_DRBG algorithm. Internally,
 * the algorithm uses the unique HSM Chip ID as the personalization data parameter during the
 * Instantiation step. Entropy data is taken from the true random number generator peripheral. The
 * PRNG is initially seeded and, periodically re-seeded, with a 256-bit seed from the TRNG
 * peripheral. The TRNG peripheral delivers an average Shannon entropy of 0.997 per bit, which
 * yields an average seed entropy of 255.232 bits.
 *
 * @note
 * If configured, the PRNG implementation follows BSI AIS20 functional class DRG.2 and internally
 * uses AES in OFB mode, initially seeded and periodically re-seeded with a 128 bit seed from the
 * true random number generator peripheral. The TRNG peripheral delivers an average Shannon entropy
 * of 0.997 per bit, which yields an average seed entropy of 127.616 bits.
 *
 * - Finalization and result query:
 *      The caller finishes and polls for the result of the random data generation using
 *      @ref ecy_hsm_Csai_PollHandle
 *
 * @param[in]   hSession     Handle to the session in which the job will be placed.
 * @param[in]   priority     Requested scheduling priority for this job on the HSM.
 * @param[out]  random       Pointer to buffer to receive the random number data
 * @param[in]   length       Length of buffer to receive the random number data
 * @param[out]  phJob        Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED          There was another job already in progress in the session
 * - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT            An address or pointer parameter was not four-byte aligned
 * - @ref ecy_hsm_CSAI_ERR_TRNG                         Error reported by random number generator hardware
 * - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR1             Error reported by AES hardware (for PRNG based on AES)
 * - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR2             Error reported by AES hardware (for PRNG based on AES)
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_RandomGenerate(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                        ecy_hsm_Csai_JobPriorityT   priority,
                                                                                        uint8                       random[],
                                                                                        uint32                      length,
                                                                                        ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_TRUE_RANDOM_GENERATE
 * @{
 */

/**
 * [$DD 2455]
 * Generate random numbers directly from the true random number generator peripheral
 * of the HSM.
 * [$Satisfies $SW_ARCH AB1955FC]
 *
 * @note
 * Generating random numbers from the TRNG is much slower than generating from the
 * PRNG. Consider using @ref ecy_hsm_Csai_RandomGenerate where applicable by the use case.
 *
 * - Finalization and result query:
 *      The caller finishes and polls for the result of the random data generation using
 *      @ref ecy_hsm_Csai_PollHandle.
 *
 * @param[in]   hSession     Handle to the session in which the job will be placed.
 * @param[in]   priority     Requested scheduling priority for this job on the HSM.
 * @param[out]  random       Pointer to buffer to receive the random number data
 * @param[in]   length       Length of buffer to receive the random number data
 * @param[out]  phJob        Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED          There was another job already in progress in the session
 * - @ref ecy_hsm_CSAI_ERR_TRNG                         Error reported by random number generator hardware
 * - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT            The buffer pointer was not word (4 byte) aligned
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_TrueRandomGenerate(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                            ecy_hsm_Csai_JobPriorityT   priority,
                                                                                            uint8                       random[],
                                                                                            uint32                      length,
                                                                                            ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_RANDOM_SEED_EXTEND
 * @{
 */

/**
 * [$DD 2456]
 * Explicitly trigger a re-seed of the pseudo-random generator generator in the HSM.
 * The PRNG is always re-seeded with random data from the true random data generator HSM peripheral.
 * The caller may provide additional seed data with this call. Depending on the PRNG algorithm
 * configured, either this data is mixed with the random data from the TRNG or it is ignored.
 * [$Satisfies $SW_ARCH 2F6F6E66]
 *
 * @note
 * Some devices provide a dedicated TRNG/PRNG hardware peripheral producing random numbers
 * compliant to NIST SP800-90a and BSI AIS 20/31. Re-seeding is a HW function of this peripheral.
 *
 * @note
 * By default, the PRNG is implemented using the NIST SP 800-90A CTR_DRBG algorithm. Entropy data
 * is taken from the true random number generator peripheral. The PRNG is re-seeded with a 256-bit
 * seed from the TRNG peripheral. The TRNG peripheral delivers an average Shannon entropy of 0.997
 * per bit, which yields an average seed entropy of 255.232 bits. Optionally, additional input can
 * be provided via the seed parameter, which is then mixed with the entropy data per the CTR_DRBG
 * algorithm specification.
 *
 * @note
 * If configured, the PRNG implementation follows BSI AIS20 functional class DRG.2 and internally
 * uses AES in OFB mode, initially seeded and periodically re-seeded with a 128 bit seed from the
 * true random number generator peripheral. The TRNG peripheral delivers an average Shannon entropy
 * of 0.997 per bit, which yields an average seed entropy of 127.616 bits. The seed parameter is
 * ignored.
 *
 * - Finalization query:
 *      The caller finishes and polls for completion of the re-seed using
 *      @ref ecy_hsm_Csai_PollHandle.
 *
 * @param[in]   hSession     Handle to the session in which the job will be placed.
 * @param[in]   priority     Requested scheduling priority for this job on the HSM.
 * @param[in]   seed         Additional data to be mixed with true random data to form the seed
 * @param[in]   length       Length of additional data.
 * @param[out]  phJob        Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED          There was another job already in progress in the session
 * - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT            An address or pointer parameter was not four-byte aligned
 * - @ref ecy_hsm_CSAI_ERR_TRNG                         Error reported by random number generator hardware
 * - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR1             Error reported by AES hardware (for PRNG based on AES)
 * - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR2             Error reported by AES hardware (for PRNG based on AES)
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_RandomSeedExtend(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                          ecy_hsm_Csai_JobPriorityT   priority,
                                                                                          const uint8                 seed[],
                                                                                          uint32                      length,
                                                                                          ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * @}
 */

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* *INDENT-OFF* */
#ifdef __cplusplus
} /* extern "C" */
#endif
/* *INDENT-ON* */

/**
 * @}
 */

#endif /* Multiple inclusion lock  */
