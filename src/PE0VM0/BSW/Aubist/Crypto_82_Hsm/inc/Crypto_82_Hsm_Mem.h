/**
 * \file Crypto_82_Hsm_Mem.h
 * \author      PiNTeam
 * \copyright   (c) DENSO KK, 2022
 *
 * \brief Header file for memory operations
 * \details
*/

#ifndef CRYPTO_82_HSM_MEM_H
#define CRYPTO_82_HSM_MEM_H

/**********************************************************************************************************************\
 * INCLUDES
\**********************************************************************************************************************/

#include "Std_Types.h"

#define CRYPTO_82_HSM_START_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"

/**********************************************************************************************************************\
 * PUBLIC MACROS
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * PUBLIC TYPE DEFINITIONS
\**********************************************************************************************************************/

/**
 * \brief Type to abstract the memory return
 */
typedef enum eCrypto_82_Hsm_MemReturnType
{
    CRYPTO_82_HSM_MEM_OK                     = 0u, /**< Operation successful */
    CRYPTO_82_HSM_MEM_NULL_POINTER           = 1u, /**< Destination or source pointer is NULL */
    CRYPTO_82_HSM_MEM_ZERO_SIZE              = 2u, /**< Destination size or number of bytes to be copied/set is zero */
    CRYPTO_82_HSM_MEM_NO_SPACE               = 3u, /**< Destination size is smaller than number of bytes to be copied/set */
    CRYPTO_82_HSM_MEM_RESTRICTED             = 4u, /**< Source size is smaller than number of bytes to be copied */
    CRYPTO_82_HSM_MEM_OVERLAP                = 5u  /**< Source memory overlaps destination memory */

} Crypto_82_Hsm_MemReturnType;

/**********************************************************************************************************************\
 * EXTERN PUBLIC VARIABLES
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * PUBLIC FUNCTION DECLARATIONS
\**********************************************************************************************************************/

/** \brief Copies data from one memory location to another
 * 
 *  \sync Synchronous
 *  \reentrant Non Reentrant
 * 
 *  \param[out]  destinationPointer     Pointer to the memory location to copy to
 *  \param[in]   destinationSize        Maximum length of destination in bytes
 *  \param[in]   sourcePointer          Pointer to the memory location to copy from
 *  \param[in]   sourceSize             Maximum length of source in bytes
 *  \param[in]   numberOfBytes          Number of bytes to copy from source
 * 
 *  \retval CRYPTO_82_HSM_MEM_NULL_POINTER       The destination pointer or the source pointer was NULL 
 *  \retval CRYPTO_82_HSM_MEM_ZERO_SIZE          The destination size, the source size or the number of bytes to be copied was zero
 *  \retval CRYPTO_82_HSM_MEM_NO_SPACE           The destination size was less than the number of bytes to be copied
 *  \retval CRYPTO_82_HSM_MEM_RESTRICTED         The number of bytes to copy was more than the source size
 *  \retval CRYPTO_82_HSM_MEM_OVERLAP            The source memory overlapped the destination memory
 *  \retval CRYPTO_82_HSM_MEM_OK                 Copy operation was successful
*/
FUNC(Crypto_82_Hsm_MemReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Memcpy_s(
    P2VAR(void, AUTOMATIC, CRYPTO_82_HSM_VAR) destinationPointer, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(uint32, AUTOMATIC) destinationSize,
    P2CONST(void, AUTOMATIC, CRYPTO_82_HSM_VAR) sourcePointer,
    VAR(uint32, AUTOMATIC) sourceSize,
    VAR(uint32, AUTOMATIC) numberOfBytes);

/** \brief Initializes memory to a specified pattern
 * 
 *  \sync Synchronous
 *  \reentrant Non Reentrant
 * 
 *  \param[out]  destinationPointer     Pointer to the memory location to be initialized
 *  \param[in]   destinationSize        Maximum length of destination in bytes
 *  \param[in]   pattern                The byte to be used to initialize the memory
 *  \param[in]   numberOfBytes          Number of bytes to be set
 *
 *  \retval CRYPTO_82_HSM_MEM_NULL_POINTER       The destination pointer was NULL 
 *  \retval CRYPTO_82_HSM_MEM_ZERO_SIZE          The destination size or the number of bytes to be set was zero
 *  \retval CRYPTO_82_HSM_MEM_NO_SPACE           The destination size was less than the number of bytes to be set
 *  \retval CRYPTO_82_HSM_MEM_OK                 Set operation was successful
*/
FUNC(Crypto_82_Hsm_MemReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Memset_s(
    P2VAR(void, AUTOMATIC, CRYPTO_82_HSM_VAR) destinationPointer, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(uint32, AUTOMATIC) destinationSize,
    VAR(uint8, AUTOMATIC) pattern,
    VAR(uint32, AUTOMATIC) numberOfBytes);

#define CRYPTO_82_HSM_STOP_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"

#endif /* CRYPTO_82_HSM_MEM_H */
