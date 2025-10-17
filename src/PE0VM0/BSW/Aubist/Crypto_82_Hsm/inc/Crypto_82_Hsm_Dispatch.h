/**
 * \file Crypto_82_Hsm_Dispatch.h
 * \author      PiNTeam
 * \copyright   (c) DENSO KK, 2022
 *
 * \brief Header file for dispatch implementation
 * \details
*/

#ifndef CRYPTO_82_HSM_DISPATCH_H
#define CRYPTO_82_HSM_DISPATCH_H

/**********************************************************************************************************************\
 * INCLUDES
\**********************************************************************************************************************/

#include "Csm.h"

#include "Std_Types.h"
#if ( (CSM_AR_RELEASE_MAJOR_VERSION == 4u) && (CSM_AR_RELEASE_MINOR_VERSION >= 5u) )
#include "Crypto_GeneralTypes.h"
#else
#include "Csm_Types.h"
#endif
#include "Crypto_82_Hsm_Cfg.h"
#include "Crypto_82_Hsm_Internal.h"
#include "Crypto_82_Hsm_Services.h"

#include <ecy_hsm_csai.h>

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
 * \startuml {Crypto_82_Hsm_Hash_Dispatch.png}
 *
 *"Start" --> if "Operation Mode Streamstart?" then

 *  -->[false] if "Operation Mode Start?\n" then
 *
 *  -->[false] if "Operation Mode Update?\n" then
 *
 *      -->[false] if "Operation Mode Finish?" then
 *
 *          -->[false] if "Operation Mode SingleCall?" then
 *
 *          -->[true] "Call SvcLayer Implementation" as SVC
 *
 *          else
 *
 *          -->[false] "Return E_NOT_OK" as RNK
 *
 *          endif
 *
 *      else
 *
 *      -->[true] SVC
 *
 *      endif
 *
 *  else
 *
 *  -->[true] SVC
 *
 *  endif
 *
 * else
 *
 * -->[true] SVC
 *
 * endif
 *
 * else
 *
 * -->[true] SVC
 *
 * endif
 *
 * SVC --> if "Internal error?" then
 *
 *  -->[true] RNK
 *
 *  else
 *
 *  -->[false] "Return E_OK" as REK
 *
 *  endif
 *
 * RNK --> "End"
 * REK --> "End"
 *
 * \enduml
 */
/**
 * \brief Dispatches a Hash job to the service layer
 *
 * \param [in, out] driverObject        Pointer to Crypto Driver object

 *
 * \retval E_OK                         Hashing successful
 * \retval E_NOT_OK                     Hashing failed
*/
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Hash_Dispatch(
    P2VAR(Crypto_82_Hsm_DriverObjectType, CRYPTO_82_HSM_VAR, AUTOMATIC) driverObject); /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */

#if ( CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON )
FUNC(uint8, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_MacGenerate_DET_Checking(
                                P2CONST(uint8, AUTOMATIC, AUTOMATIC) msg, 
                                P2VAR(uint8, AUTOMATIC, AUTOMATIC) mac, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
                                CONST(uint32, AUTOMATIC) msg_len,
                                P2VAR(uint32, AUTOMATIC, AUTOMATIC) mac_len, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
                                VAR(Crypto_OperationModeType, AUTOMATIC) opMode,
                                VAR(Crypto_82_Hsm_Service_MACAlgorithmType, AUTOMATIC) Crypto_algo
                                );

FUNC(uint8, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_MacVerify_DET_Checking(
                                P2CONST(uint8, AUTOMATIC, AUTOMATIC) msg, 
                                P2CONST(uint8, AUTOMATIC, AUTOMATIC) mac,
                                CONST(uint32, AUTOMATIC) msg_len,
                                VAR(uint32, AUTOMATIC) mac_size,
                                VAR(Crypto_OperationModeType, AUTOMATIC) opMode,
                                VAR(Crypto_82_Hsm_Service_MACAlgorithmType, AUTOMATIC) Crypto_algo,
                                P2VAR(uint8, AUTOMATIC, AUTOMATIC) verifyPtr /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
                                );
#endif                                

/**
 * \startuml {Crypto_82_Hsm_MacGenerate_Dispatch.png}
 *
 *"Start" --> if "Operation Mode Streamstart?" then

 *  -->[false] if "Operation Mode Start?\n" then
 *
 *  -->[false] if "Operation Mode Update?\n" then
 *
 *      -->[false] if "Operation Mode Finish?" then
 *
 *          -->[false] if "Operation Mode SingleCall?" then
 *
 *          -->[true] "Call SvcLayer Implementation" as SVC
 *
 *          else
 *
 *          -->[false] "Return E_NOT_OK" as RNK
 *
 *          endif
 *
 *      else
 *
 *      -->[true] SVC
 *
 *      endif
 *
 *  else
 *
 *  -->[true] SVC
 *
 *  endif
 *
 * else
 *
 * -->[true] SVC
 *
 * endif
 *
 * else
 *
 * -->[true] SVC
 *
 * endif
 *
 * SVC --> if "Internal error?" then
 *
 *  -->[true] RNK
 *
 *  else
 *
 *  -->[false] "Return E_OK" as REK
 *
 *  endif
 *
 * RNK --> "End"
 * REK --> "End"
 *
 * \enduml
 */
/**
 * \brief Dispatches a Mac Generate job to the service layer
 *
 * \param [in, out] driverObject        Pointer to Crypto Driver object

 *
 * \retval E_OK                         Mac Generation successful
 * \retval E_NOT_OK                     Mac Generation failed
*/
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_MacGenerate_Dispatch(
    P2VAR(Crypto_82_Hsm_DriverObjectType, CRYPTO_82_HSM_VAR, AUTOMATIC) driverObject); /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */

/**
 * \brief Mapping for MAC algorithms.
 *
 * \param [in] algofam        Algorithm family.
 * \param [in] algomode       Algorithm mode.
 *
 * \return ret_algo           Corresponding MAC algorithm supported by the Crypto Service layer.
 */
FUNC(Crypto_82_Hsm_Service_MACAlgorithmType, CRYPTO_82_HSM_CODE) get_serviceLayerMacAlgo(uint32 algofam, uint32 algomode);

/**
 * \startuml {Crypto_82_Hsm_MacVerify_Dispatch.png}
 *
  *"Start" --> if "Operation Mode Streamstart?" then

 *  -->[false] if "Operation Mode Start?\n" then
 *
 *  -->[false] if "Operation Mode Update?\n" then
 *
 *      -->[false] if "Operation Mode Finish?" then
 *
 *          -->[false] if "Operation Mode SingleCall?" then
 *
 *          -->[true] "Call SvcLayer Implementation" as SVC
 *
 *          else
 *
 *          -->[false] "Return E_NOT_OK" as RNK
 *
 *          endif
 *
 *      else
 *
 *      -->[true] SVC
 *
 *      endif
 *
 *  else
 *
 *  -->[true] SVC
 *
 *  endif
 *
 * else
 *
 * -->[true] SVC
 *
 * endif
 *
 * else
 *
 * -->[true] SVC
 *
 * endif
 *
 * SVC --> if "Internal error?" then
 *
 *  -->[true] RNK
 *
 *  else
 *
 *  -->[false] if "Verification error?"
 *
 *      -->[true] RNK
 *
 *      else
 *
 *      -->[false] "Return E_OK" as REK
 *
 *      endif
 *
 *  endif
 *
 * RNK --> "End"
 * REK --> "End"
 *
 * \enduml
 */
/**
 * \brief Dispatches a Mac Verify job to the service layer
 *
 * \param [in, out] driverObject        Pointer to Crypto Driver object

 *
 * \retval E_OK                         Mac Verification successful
 * \retval E_NOT_OK                     Mac Verification failed
*/
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_MacVerify_Dispatch(
    P2VAR(Crypto_82_Hsm_DriverObjectType, CRYPTO_82_HSM_VAR, AUTOMATIC) driverObject); /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */

/* This is for entire encryption service, not only symmetric. Currently it is only symmetric. TODO: Implement asym enc.  */

/**
 * \startuml {Crypto_82_Hsm_Encrypt_Dispatch.png}
 *
 *"Start" --> if "Operation Mode Streamstart?" then

 *  -->[false] if "Operation Mode Start?\n" then
 *
 *  -->[false] if "Operation Mode Update?\n" then
 *
 *      -->[false] if "Operation Mode Finish?" then
 *
 *          -->[false] if "Operation Mode SingleCall?" then
 *
 *          -->[true] "Call SvcLayer Implementation" as SVC
 *
 *          else
 *
 *          -->[false] "Return E_NOT_OK" as RNK
 *
 *          endif
 *
 *      else
 *
 *      -->[true] SVC
 *
 *      endif
 *
 *  else
 *
 *  -->[true] SVC
 *
 *  endif
 *
 * else
 *
 * -->[true] SVC
 *
 * endif
 *
 * else
 *
 * -->[true] SVC
 *
 * endif
 *
 * SVC --> if "Internal error?" then
 *
 *  -->[true] RNK
 *
 *  else
 *
 *  -->[false] "Return E_OK" as REK
 *
 *  endif
 *
 * RNK --> "End"
 * REK --> "End"
 *
 * \enduml
 */
/**
 * \brief Dispatches a Encrypt job to the service layer
 *
 * \param [in, out] driverObject        Pointer to Crypto Driver object

 *
 * \retval E_OK                         Encryption successful
 * \retval E_NOT_OK                     Encryption failed
*/
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Encrypt_Dispatch(
    P2VAR(Crypto_82_Hsm_DriverObjectType, CRYPTO_82_HSM_VAR, AUTOMATIC) driverObject); /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */

/**
 * \startuml {Crypto_82_Hsm_Decrypt_Dispatch.png}
 *
 *"Start" --> if "Operation Mode Streamstart?" then

 *  -->[false] if "Operation Mode Start?\n" then
 *
 *  -->[false] if "Operation Mode Update?\n" then
 *
 *      -->[false] if "Operation Mode Finish?" then
 *
 *          -->[false] if "Operation Mode SingleCall?" then
 *
 *          -->[true] "Call SvcLayer Implementation" as SVC
 *
 *          else
 *
 *          -->[false] "Return E_NOT_OK" as RNK
 *
 *          endif
 *
 *      else
 *
 *      -->[true] SVC
 *
 *      endif
 *
 *  else
 *
 *  -->[true] SVC
 *
 *  endif
 *
 * else
 *
 * -->[true] SVC
 *
 * endif
 *
 * else
 *
 * -->[true] SVC
 *
 * endif
 *
 * SVC --> if "Internal error?" then
 *
 *  -->[true] RNK
 *
 *  else
 *
 *  -->[false] "Return E_OK" as REK
 *
 *  endif
 *
 * RNK --> "End"
 * REK --> "End"
 *
 * \enduml
 */
/**
 * \brief Dispatches a Decrypt job to the service layer
 *
 * \param [in, out] driverObject        Pointer to Crypto Driver object

 *
 * \retval E_OK                         Decryption successful
 * \retval E_NOT_OK                     Decryption failed
*/
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Decrypt_Dispatch(
    P2VAR(Crypto_82_Hsm_DriverObjectType, CRYPTO_82_HSM_VAR, AUTOMATIC) driverObject); /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */

/**
 * \startuml {Crypto_82_Hsm_AEADEncrypt_Dispatch.png}
 *
 *"Start" --> if "Input/Output parameters are valid"
 *          -->[true] if "Operation Mode Streamstart?\n" then
 *
 *          -->[false] if "Operation Mode Start?\n" then
 *
 *          -->[false] if "Operation Mode Update?\n" then
 *
 *              -->[false] if "Operation Mode Finish?" then
 *
 *                  -->[false] if "Operation Mode SingleCall?" then
 *
 *                  -->[true] "Call SvcLayer Implementation" as SVC
 *
 *                  else
 *
 *                  -->[false] "Return E_NOT_OK" as RNK
 *
 *                  endif
 *
 *              else
 *
 *              -->[true] SVC
 *
 *              endif
 *
 *          else
 *
 *          -->[true] SVC
 *
 *          endif
 *
 *      else
 *
 *      -->[true] SVC
 *
 *      endif
 *
 *      else
 *
 *      -->[true] SVC
 *
 *      endif
 *  else
 *  -->[false] "Return E_NOT_OK" as RNK
 *
 *      endif
 *
 * SVC --> if "Internal error?" then
 *
 *  -->[true] RNK
 *
 *  else
 *
 *  -->[false] "Return E_OK" as REK
 *
 *  endif
 *
 * RNK --> "End"
 * REK --> "End"
 *
 * \enduml
 */
/**
 * \brief Dispatches an Authenticated Encrypt job to the service layer
 *
 * \param [in, out] driverObject        Pointer to Crypto Driver object

 *
 * \retval E_OK                         Authenticated Encryption successful
 * \retval E_NOT_OK                     Authenticated Encryption failed
*/
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_AEADEncrypt_Dispatch(
    P2VAR(Crypto_82_Hsm_DriverObjectType, CRYPTO_82_HSM_VAR, AUTOMATIC) driverObject); /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */

/**
 * \startuml {Crypto_82_Hsm_AEADDecrypt_Dispatch.png}
 *
 *"Start" --> if "Input/Output parameters are valid"
 *          -->[true] if "Operation Mode Streamstart?\n" then
 *
 *          -->[false] if "Operation Mode Start?\n" then
 *
 *          -->[false] if "Operation Mode Update?\n" then
 *
 *              -->[false] if "Operation Mode Finish?" then
 *
 *                  -->[false] if "Operation Mode SingleCall?" then
 *
 *                  -->[true] "Call SvcLayer Implementation" as SVC
 *
 *                  else
 *
 *                  -->[false] "Return E_NOT_OK" as RNK
 *
 *                  endif
 *
 *              else
 *
 *              -->[true] SVC
 *
 *              endif
 *
 *          else
 *
 *          -->[true] SVC
 *
 *          endif
 *
 *      else
 *
 *      -->[true] SVC
 *
 *      endif
 *
 *      else
 *
 *      -->[true] SVC
 *
 *      endif
 *  else
 *  -->[false] "Return E_NOT_OK" as RNK
 *  endif
 * SVC --> if "Internal error?" then
 *
 *  -->[true] RNK
 *
 *  else
 *
 *  -->[false] "Return E_OK" as REK
 *
 *  endif
 *
 * RNK --> "End"
 * REK --> "End"
 *
 * \enduml
 */
/**
 * \brief Dispatches an Authenticated Decrypt job to the service layer
 *
 * \param [in, out] driverObject        Pointer to Crypto Driver object

 *
 * \retval E_OK                         Authenticated Decryption successful
 * \retval E_NOT_OK                     Authenticated Decryption failed
*/
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_AEADDecrypt_Dispatch(
    P2VAR(Crypto_82_Hsm_DriverObjectType, CRYPTO_82_HSM_VAR, AUTOMATIC) driverObject); /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */

/**
 * \brief Dispatches a Random Number Generation job to the service layer
 *
 * \param [in, out] driverObject        Pointer to Crypto Driver object

 *
 * \retval E_OK                         Random Number Generation successful
 * \retval E_NOT_OK                     Random Number Generation failed
 * \retval CRYPTO_E_ENTROPY_EXHAUSTED   Random Number Generation failed because entropy of the random number generator is exhausted
*/
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Rng_Dispatch(
    P2VAR(Crypto_82_Hsm_DriverObjectType, CRYPTO_82_HSM_VAR, AUTOMATIC) driverObject); /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */

/**
 * \brief Dispatches a Random Reseed job to the service layer
 *
 * \param [in, out] driverObject        Pointer to Crypto Driver object

 *
 * \retval E_OK                         Reseed successful
 * \retval E_NOT_OK                     Reseed failed
*/
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_RngReseed_Dispatch(
    P2VAR(Crypto_82_Hsm_DriverObjectType, CRYPTO_82_HSM_VAR, AUTOMATIC) driverObject); /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */

/**
 * \startuml {Crypto_82_Hsm_SignatureGenerate_Dispatch.png}
 *
 * "Start" --> "Identify Sign Algo" as ISA
 *
 *  ISA --> if "Operation Mode Streamstart?" then
 *
 *  -->[false] if "Operation Mode Start?\n" then
 *
 *  -->[false] if "Operation Mode Update?\n" then
 *
 *      -->[false] if "Operation Mode Finish?" then
 *
 *          -->[false] if "Operation Mode SingleCall?" then
 *
 *          -->[true] "Call SvcLayer Implementation" as SVC
 *
 *          else
 *
 *          -->[false] "Return E_NOT_OK" as RNK
 *
 *          endif
 *
 *      else
 *
 *      -->[true] SVC
 *
 *      endif
 *
 *  else
 *
 *  -->[true] SVC
 *
 *  endif
 *
 * else
 *
 * -->[true] SVC
 *
 * endif
 *
 * else
 *
 * -->[true] SVC
 *
 * endif
 *
 * SVC --> if "Internal error?" then
 *
 *  -->[true] RNK
 *
 *  else
 *
 *  -->[false] "Return E_OK" as REK
 *
 *  endif
 *
 * RNK --> "End"
 * REK --> "End"
 *
 * \enduml
 */
/**
 * \brief Dispatches a Signature Generate job to the service layer
 *
 * \param [in, out] driverObject        Pointer to Crypto Driver object

 *
 * \retval E_OK                         Signing successful
 * \retval E_NOT_OK                     Signing failed
*/
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_SignatureGenerate_Dispatch(
    P2VAR(Crypto_82_Hsm_DriverObjectType, CRYPTO_82_HSM_VAR, AUTOMATIC) driverObject); /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */

/**
 * \startuml {Crypto_82_Hsm_SignatureVerify_Dispatch.png}
 *
 * "Start" --> "Identify Sign Algo" as ISA
 *
 *  ISA --> if "Operation Mode Streamstart?" then
 *
 *  -->[false] if "Operation Mode Start?\n" then
 *
 *  -->[false] if "Operation Mode Update?\n" then
 *
 *      -->[false] if "Operation Mode Finish?" then
 *
 *          -->[false] if "Operation Mode SingleCall?" then
 *
 *          -->[true] "Call SvcLayer Implementation" as SVC
 *
 *          else
 *
 *          -->[false] "Return E_NOT_OK" as RNK
 *
 *          endif
 *
 *      else
 *
 *      -->[true] SVC
 *
 *      endif
 *
 *  else
 *
 *  -->[true] SVC
 *
 *  endif
 *
 * else
 *
 * -->[true] SVC
 *
 * endif
 *
 * else
 *
 * -->[true] SVC
 *
 * endif
 *
 * SVC --> if "Internal error?" then
 *
 *  -->[true] RNK
 *
 *  else
 *
 *  -->[false] if "Verification error?"
 *
 *      -->[true] RNK
 *
 *      else
 *
 *      -->[false] "Return E_OK" as REK
 *
 *      endif
 *
 *  endif
 *
 * RNK --> "End"
 * REK --> "End"
 *
 * \enduml
 */
/**
 * \brief Dispatches a Signature Verify job to the service layer
 *
 * \param [in, out] driverObject        Pointer to Crypto Driver object

 *
 * \retval E_OK                         Verification successful
 * \retval E_NOT_OK                     Verification failed
*/
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_SignatureVerify_Dispatch(
    P2VAR(Crypto_82_Hsm_DriverObjectType, CRYPTO_82_HSM_VAR, AUTOMATIC) driverObject); /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */

/**
 * \brief Dispatches a KeySetValid job.
 * 
 * This function acts as a wrapper for \ref Crypto_82_Hsm_Job_KeySetValid.
 *
 * \param [in, out] driverObject        Pointer to Crypto Driver object

 *
 * \retval E_OK                         KeySetValid operation successful
 * \retval E_NOT_OK                     KeySetValid operation failed
*/
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_KeySetValid_Dispatch(
    P2VAR(Crypto_82_Hsm_DriverObjectType, CRYPTO_82_HSM_VAR, AUTOMATIC) driverObject); /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */

/**
 * \brief Dispatches a KeyGenerate job.
 * 
 * This function acts as a wrapper for \ref Crypto_82_Hsm_Job_KeyGenerate.
 *
 * \param [in, out] driverObject         Pointer to Crypto Driver object

 *
 * \retval E_OK                          KeyGenerate operation successful
 * \retval E_NOT_OK                      KeyGenerate operation failed
 * \retval CRYPTO_E_KEY_NOT_VALID        Request failed, the key's state is "invalid"
*/
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_KeyGenerate_Dispatch(
    P2VAR(Crypto_82_Hsm_DriverObjectType, CRYPTO_82_HSM_VAR, AUTOMATIC) driverObject); /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */

/**
 * \brief Dispatches a KeyDerive job.
 * 
 * This function acts as a wrapper for \ref Crypto_82_Hsm_Job_KeyDerive.
 *
 * \param [in, out] driverObject         Pointer to Crypto Driver object

 *
 * \retval E_OK                          KeyDerive operation successful
 * \retval E_NOT_OK                      KeyDerive operation failed
*/
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_KeyDerive_Dispatch(
    P2VAR(Crypto_82_Hsm_DriverObjectType, CRYPTO_82_HSM_VAR, AUTOMATIC) driverObject); /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */

/**
 * \brief Dispatches a KeyExchangeCalcPubVal job.
 * 
 * This function acts as a wrapper for \ref Crypto_82_Hsm_Job_KeyExchangeCalcPubVal except the Poll Handle.
 *
 * \param [in, out] driverObject        Pointer to Crypto Driver object

 *
 * \retval E_OK                         KeyExchangeCalcPubVal operation successful
 * \retval E_NOT_OK                     KeyExchangeCalcPubVal operation failed
 * \retval CRYPTO_E_KEY_NOT_VALID       Key Element CRYPTO_KE_KEYEXCHANGE_ALGORITHM has incorrect data or is a NULL_PTR
*/
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_KeyExchangeCalcPubVal_Dispatch(
    P2VAR(Crypto_82_Hsm_DriverObjectType, CRYPTO_82_HSM_VAR, AUTOMATIC) driverObject); /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */

/**
 * \brief Dispatches a KeyExchangeCalcSecret job.
 * 
 * This function acts as a wrapper for \ref Crypto_82_Hsm_Job_KeyExchangeCalcSecret except the Poll Handle.
 *
 * \param [in, out] driverObject        Pointer to Crypto Driver object

 *
 * \retval E_NOT_OK                     KeyExchangeCalcSecret operation failed
*/
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_KeyExchangeCalcSecret_Dispatch(
    P2VAR(Crypto_82_Hsm_DriverObjectType, CRYPTO_82_HSM_VAR, AUTOMATIC) driverObject); /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */

/**
 * \brief Generates new key material store it in the key identified by cryptoKeyId.
 *
 * \param [in]      driverObject     Pointer to Crypto Driver object
 * \param [in out]  job              Pointer to the job configuration passed down from CryIf
 *
 * \retval E_OK                      Request successful
 * \retval E_NOT_OK                  Request failed
 * \retval CRYPTO_E_KEY_NOT_VALID    Request failed, the key's state is "invalid"
*/
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Job_KeyGenerate(
    P2VAR(Crypto_82_Hsm_DriverObjectType, CRYPTO_82_HSM_VAR, AUTOMATIC) driverObject, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    CONSTP2CONST(Crypto_JobType, CRYPTO_82_HSM_CONST, CRYPTO_82_HSM_CONST) job
);

/**
 * \brief Derives a new key by using the key elements in the given key identified by the cryptoKeyId.
 *
 * The given key contains the key elements for the password, salt. The derived key is stored in the key element with the
 * id 1 of the key identified by targetCryptoKeyId. The number of iterations is given in the key element
 * CRYPTO_KE_KEYDERIVATION_ITERATIONS.
 *
 * \param [in]      driverObject    Pointer to Crypto Driver object
 * \param [in out]  job             Pointer to the job configuration passed down from CryIf
 *
 * \retval E_OK                     Request successful
 * \retval E_NOT_OK                 Request failed
*/
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Job_KeyDerive(
    P2VAR(Crypto_82_Hsm_DriverObjectType, CRYPTO_82_HSM_VAR, AUTOMATIC) driverObject, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    CONSTP2CONST(Crypto_JobType, CRYPTO_82_HSM_CONST, CRYPTO_82_HSM_CONST) job
);


/**
 * \brief Calculates the public value for the key exchange and stores the public key in the memory location pointed by
 *        the public value pointer.
 * \note  The Key element used for algo selection ( CRYPTO_KE_KEYEXCHANGE_ALGORITHM ) can be either NULL or stored in 
 *        CRYPTO_82_HSM_DATA_BUFFER_KEY_ELEMENT.
 *
 * \param [in]      driverObject    Pointer to Crypto Driver object
 * \param [in out]  job             Pointer to the job configuration passed down from CryIf
 *
 * \retval E_OK                     Request successful
 * \retval E_NOT_OK                 Request failed
 * \retval CRYPTO_E_KEY_NOT_VALID   Key Element CRYPTO_KE_KEYEXCHANGE_ALGORITHM has incorrect data or is a NULL_PTR
*/
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Job_KeyExchangeCalcPubVal(
    P2VAR(Crypto_82_Hsm_DriverObjectType, CRYPTO_82_HSM_VAR, AUTOMATIC) driverObject, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    CONSTP2CONST(Crypto_JobType, CRYPTO_82_HSM_CONST, CRYPTO_82_HSM_CONST) job
);

/**
 * \brief Calculates the shared secret key for the key exchange with the key material of the key identified by the
 *        cryptoKeyId and the partner public key.
 *
 * The shared secret key is stored as a key element in the same key.
 *
 * \param [in]      driverObject    Pointer to Crypto Driver object
 * \param [in, out] job             Pointer to the job configuration passed down from CryIf
 *
 * \retval E_NOT_OK                 Request failed
*/
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Job_KeyExchangeCalcSecret(
    P2VAR(Crypto_82_Hsm_DriverObjectType, CRYPTO_82_HSM_VAR, AUTOMATIC) driverObject, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    CONSTP2CONST(Crypto_JobType, CRYPTO_82_HSM_CONST, CRYPTO_82_HSM_CONST) job
);

/**
 * \brief Job which sets the key state of the key identified by cryptoKeyId to valid.
 * 
 * \param [in out]  job        Pointer to the job configuration passed down from CryIf
 * \param [in] objectID        Crypto driver object id.
 *
 * \retval E_OK                Request successful
 * \retval E_NOT_OK            Request failed
 */
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Job_KeySetValid(
    CONSTP2CONST(Crypto_JobType, CRYPTO_82_HSM_CONST, CRYPTO_82_HSM_CONST) job,
    VAR(uint32, AUTOMATIC) objectId
);

/**
 * \brief Postprocessing after Key Generate job.
 *
 * \param [in]      driverObject    Pointer to Crypto Driver object
*/
FUNC(void, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_JobKeyGenerate_Cbk(
    VAR(uint32, AUTOMATIC) objectId
);

/**
 * \brief Postprocessing after Key Derive job.
 *
 * \param [in]      driverObject    Pointer to Crypto Driver object
*/
FUNC(void, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_JobKeyDerive_Cbk(
    VAR(uint32, AUTOMATIC) objectId
);

#define CRYPTO_82_HSM_STOP_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"

#endif
