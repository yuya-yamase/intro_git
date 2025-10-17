/**
 * \file Crypto_82_Hsm_Mem.c
 * \author      PiNTeam
 * \copyright   (c) DENSO KK, 2022
 *
 * \brief Implementation of memory operations
 * \details
 */

/**********************************************************************************************************************\
 * INCLUDES
\**********************************************************************************************************************/

#include "Crypto_82_Hsm_Cfg.h"
#include "Crypto_82_Hsm_Mem.h"

/**********************************************************************************************************************\
 * PRIVATE MACROS
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * PRIVATE TYPE DEFINITIONS
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * PUBLIC VARIABLES
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * PRIVATE VARIABLES
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * PRIVATE FUNCTION DECLARATIONS
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * PRIVATE FUNCTION IMPLEMENTATIONS
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * PUBLIC FUNCTION IMPLEMENTATIONS
\**********************************************************************************************************************/

#define CRYPTO_82_HSM_START_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"

FUNC(Crypto_82_Hsm_MemReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Memcpy_s(
    P2VAR(void, AUTOMATIC, CRYPTO_82_HSM_VAR) destinationPointer, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(uint32, AUTOMATIC) destinationSize,
    P2CONST(void, AUTOMATIC, CRYPTO_82_HSM_VAR) sourcePointer,
    VAR(uint32, AUTOMATIC) sourceSize,
    VAR(uint32, AUTOMATIC) numberOfBytes)
{
    /* ----- Local Variables ---------------------------------------------- */
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) byteDestinationPointer = (P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR))destinationPointer; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) byteSourcePointer = (P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR))sourcePointer;
    VAR(Crypto_82_Hsm_MemReturnType, AUTOMATIC) res = CRYPTO_82_HSM_MEM_OK;
    VAR(uint32, AUTOMATIC) index;

#if (CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON)
    if ((byteDestinationPointer == NULL_PTR) || (byteSourcePointer == NULL_PTR))
    {
        res = CRYPTO_82_HSM_MEM_NULL_POINTER;
    }
    else if ((destinationSize == 0u) || (sourceSize == 0u) || (numberOfBytes == 0u))
    {
        res = CRYPTO_82_HSM_MEM_ZERO_SIZE;
    }
    else if (numberOfBytes > destinationSize)
    {
        res = CRYPTO_82_HSM_MEM_NO_SPACE;
    }
    else if (sourceSize < numberOfBytes)
    {
        res = CRYPTO_82_HSM_MEM_RESTRICTED;
    }
    else if ((byteDestinationPointer > byteSourcePointer) && (byteDestinationPointer < (&byteSourcePointer[numberOfBytes]))) 
    {
        res = CRYPTO_82_HSM_MEM_OVERLAP;
    }
    else if ((byteSourcePointer > byteDestinationPointer) && (byteSourcePointer < (&byteDestinationPointer[destinationSize])))
    {
        res = CRYPTO_82_HSM_MEM_OVERLAP;
    }
    else
#endif
    {
        for (index = 0u; index < numberOfBytes; index++)
        {
            byteDestinationPointer[index] = byteSourcePointer[index];
        }
    }
    return res;
}

FUNC(Crypto_82_Hsm_MemReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Memset_s(
    P2VAR(void, AUTOMATIC, CRYPTO_82_HSM_VAR) destinationPointer, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(uint32, AUTOMATIC) destinationSize,
    VAR(uint8, AUTOMATIC) pattern,
    VAR(uint32, AUTOMATIC) numberOfBytes)
{
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) byteDestinationPointer = (P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR))destinationPointer; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(Crypto_82_Hsm_MemReturnType, AUTOMATIC) res = CRYPTO_82_HSM_MEM_OK;
    VAR(uint32, AUTOMATIC) index;

#if (CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON)
    if (byteDestinationPointer == NULL_PTR)
    {
        res = CRYPTO_82_HSM_MEM_NULL_POINTER;
    }
    else if ((destinationSize == 0u) || (numberOfBytes == 0u))
    {
        res = CRYPTO_82_HSM_MEM_ZERO_SIZE;
    }
    else if (numberOfBytes > destinationSize)
    {
        res = CRYPTO_82_HSM_MEM_NO_SPACE;
    }
    else
#endif
    {
        for (index = 0u; index < numberOfBytes; index++)
        {
            byteDestinationPointer[index] = pattern;
        }
    }
    return res;
}

#define CRYPTO_82_HSM_STOP_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"
