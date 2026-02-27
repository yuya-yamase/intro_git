/**
 * \file Crypto_82_Hsm_UserCallout.h
 * \author      PiNTeam
 * \copyright   (c) DENSO KK, 2022
 *
 * \brief Header file for user callouts
 * \details
*/

#ifndef CRYPTO_82_HSM_USER_H
#define CRYPTO_82_HSM_USER_H

/**********************************************************************************************************************\
 * INCLUDES
\**********************************************************************************************************************/

#include "ecy_hsm_csai_types.h"

/**********************************************************************************************************************\
 * PUBLIC MACROS
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * PUBLIC TYPE DEFINITIONS
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * EXTERN PUBLIC VARIABLES
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * PUBLIC FUNCTION DECLARATIONS
\**********************************************************************************************************************/

#define CRYPTO_82_HSM_START_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"
/**
 * \brief Poll the status of a CSAI job.
 * 
 * \param [in] serviceId    The service for which the csai error is reported.
 * \param [in] jobId        The jobID for which the csai erorr is reported.
 * \param [in] csai_err     The reported csai error value.
 */
FUNC(void, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Error_Callback(uint8 serviceId, uint32 jobId, ecy_hsm_Csai_ErrorT csai_err);


#define CRYPTO_82_HSM_STOP_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"

#endif /* CRYPTO_82_HSM_USER_H */
