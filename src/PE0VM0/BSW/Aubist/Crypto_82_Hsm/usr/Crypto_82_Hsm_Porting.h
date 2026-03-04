/**
 * \file Crypto_82_Hsm_Porting.h
 * \author      PiNTeam
 * \copyright   (c) DENSO KK, 2022
 * 
 * \brief This file contains an abstraction above the underlying CycurHSM layer.
 * \details This file is to be updated when switching CycurHSM versions.
*/

#ifndef CRYPTO_82_HSM_PORTING_H
#define CRYPTO_82_HSM_PORTING_H

/**********************************************************************************************************************\
 * INCLUDES
\**********************************************************************************************************************/

#include "ecy_hsm_csai_keyid.h"
#include "ecy_hsm_csai_keys.h"
#include "ecy_hsm_csai_shecompat.h"

/**********************************************************************************************************************\
 * PUBLIC MACROS
\**********************************************************************************************************************/

/**
 * \def SHE_RAM_KEY
 * \brief SHE RAM key as defined in "SHE specification V1.1"
*/
#define SHE_RAM_KEY                     0x0Eu

/**
 * \def KEYTYPE_RESERVED
 * \brief Key Type Reserved
*/
#define KEYTYPE_RESERVED                ecy_hsm_CSAI_KEYTYPE_RESERVED

/**
 * \def KEY_STATUS_STORE_ID_START
 * \brief Key Status Store ID
*/
#define KEY_STATUS_STORE_ID_START       ecy_hsm_CSAI_KEYID_SECRET_DATA_DYNAMIC_CFG_SECRET_DATA_SMALL_0_INST_1

/**
 * \def M1_SIZE
 * \brief Size of the M1 key data block
*/
#define M1_SIZE ecy_hsm_CSAI_SHE_M1_BLOCK_SIZE_BYTES
/**
 * \def M2_SIZE
 * \brief  Size of the M2 key data block
*/
#define M2_SIZE ecy_hsm_CSAI_SHE_M2_BLOCK_SIZE_BYTES
/**
 * \def M3_SIZE
 * \brief Size of the M3 key data block
*/
#define M3_SIZE ecy_hsm_CSAI_SHE_M3_BLOCK_SIZE_BYTES
/**
 * \def M4_SIZE
 * \brief Size of the M4 key data block
*/
#define M4_SIZE ecy_hsm_CSAI_SHE_M4_BLOCK_SIZE_BYTES
/**
 * \def M5_SIZE
 * \brief Size of the M5 key data block
*/
#define M5_SIZE ecy_hsm_CSAI_SHE_M5_BLOCK_SIZE_BYTES

/* TODO: Decide if this macro should be public */
/**
 * \def TOTAL_SHE_RAM_KEY_BUFFER_LEN
 * \brief Total SHE RAM Key Buffer Length
*/
#define TOTAL_SHE_RAM_KEY_BUFFER_LEN (ecy_hsm_CSAI_SHE_M1_BLOCK_SIZE_BYTES + \
                                      ecy_hsm_CSAI_SHE_M2_BLOCK_SIZE_BYTES + \
                                      ecy_hsm_CSAI_SHE_M3_BLOCK_SIZE_BYTES + \
                                      ecy_hsm_CSAI_SHE_M4_BLOCK_SIZE_BYTES + \
                                      ecy_hsm_CSAI_SHE_M5_BLOCK_SIZE_BYTES)
                                   
#define MAX_SIZE_ECDSA_PUBLIC_KEY   (96u)                                 

#define INVALID_KEY_HANDLE_VALUE    ecy_hsm_CSAI_INVALID_KEY_HANDLE_VALUE 
#define INVALID_JOB_HANDLE_VALUE    ecy_hsm_CSAI_INVALID_JOB_HANDLE_VALUE
                                    
#endif /* CRYPTO_82_HSM_PORTING_H */
