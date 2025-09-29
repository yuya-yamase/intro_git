/**
 * \file Crypto_82_Hsm_Cfg.h
 * \author      PiNTeam
 * \copyright   (c) DENSO KK, 2022
 *
 * \brief Generated configuration file
 * \details
*/

#ifndef CRYPTO_82_HSM_CFG_H
#define CRYPTO_82_HSM_CFG_H

#include <Platform_Types.h>
#include <Compiler.h>

/***********************************************************************************************************************
 * PUBLIC MACROS
 **********************************************************************************************************************/

/*** General Definitions **********************************************************************************************/

/**
 * \def CRYPTO_82_HSM_INSTANCE_ID
 * \brief Crypto Driver Instance ID.
 */
#define CRYPTO_82_HSM_INSTANCE_ID                                                                                   (0u)

#define CRYPTO_82_HSM_DEV_ERROR_REPORT                                                                           STD_OFF
#define CRYPTO_82_HSM_DEV_ERROR_DETECT                                                                           STD_OFF
#define CRYPTO_82_HSM_RUNTIME_ERROR_REPORT                                                                       STD_OFF
#define CRYPTO_82_HSM_EXT_DEV_ERROR_DETECT                                                                       STD_OFF
#define CRYPTO_82_HSM_VERSION_INFO_API                                                                           STD_OFF
#define CRYPTO_82_HSM_DENSO_EXTENSIONS                                                                            STD_ON

/*** Denso Extension Features *****************************************************************************************/
/** Key Related Features ************************************************************************************************/
#define CRYPTO_82_HSM_DENSO_KEY_VALIDITY                                                                         STD_OFF
#define CRYPTO_82_HSM_KEY_SETTING                                                                                 STD_ON
#define CRYPTO_82_HSM_KEY_RESETTING                                                                               STD_ON
#define CRYPTO_82_HSM_KEY_RETRIEVAL                                                                               STD_ON
#define CRYPTO_82_HSM_KEY_LOADING                                                                                 STD_ON
#define CRYPTO_82_HSM_AUTOSAR_KEY_VALIDITY                                                                        STD_ON
/**SHE features********************************************************************************************************/
#define CRYPTO_82_HSM_SHE_GET_ID_AND_STATUS                                                                       STD_ON
#define CRYPTO_82_HSM_SHE_CANCEL                                                                                 STD_OFF
#define CRYPTO_82_HSM_SHE_DEBUG                                                                                   STD_ON
/**MISC features*******************************************************************************************************/
#define CRYPTO_82_HSM_POWER_MODE                                                                                  STD_ON
#define CRYPTO_82_HSM_FLASH_SYNC                                                                                  STD_ON
#define CRYPTO_82_HSM_FEE_REORG                                                                                  STD_OFF

#define CRYPTO_82_HSM_RELOAD_PREVIOUS_SHE_KEYS                                                                    STD_ON
#define CRYPTO_82_HSM_SYNC_POLL_AT_INIT                                                                          STD_OFF
#define CRYPTO_82_HSM_CANCEL_JOB_WITH_JOB_INFO_TYPE                                                              STD_OFF
#define CRYPTO_82_HSM_CALLBACK_NOTIF_AUTOSAR_VERSION_SELECT                                                      STD_OFF
#define CRYPTO_82_HSM_USER_DEF_INIT                                                                               STD_ON
#define CRYPTO_82_HSM_DENSO_BULK_MAC                                                                              STD_ON
#define CRYPTO_82_HSM_USER_DEF_EXCLUSIVE_AREA                                                                    STD_OFF
#define CRYPTO_82_HSM_CLOCK_DIVIDER                                                                                 (1u)
#define CRYPTO_82_HSM_MAIN_FUNCTION_PERIOD                                                                       (0.001)
#define CRYPTO_82_HSM_MAX_NUM_REQUESTS_BULK_MAC_GEN                                                                 (7u)
#define CRYPTO_82_HSM_MAX_NUM_REQUESTS_BULK_MAC_VER                                                                 (8u)
#define CRYPTO_82_HSM_INIT_TIMEOUT                                                                                (400u)

/*** Driver Objects Definitions ***************************************************************************************/
#define CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS                                                                      (6u)
#define CryptoConf_CryptoDriverObject_CryptoDriverObject_DensoExt                                                      0
#define CryptoConf_CryptoDriverObject_CryptoDriverObject_KeyManagement                                                 1
#define CryptoConf_CryptoDriverObject_CryptoDriverObject_DensoExtDFlashReorg                                           2
#define CryptoConf_CryptoDriverObject_CryptoDriverObject_DensoBulkMacVer                                               3
#define CryptoConf_CryptoDriverObject_CryptoDriverObject_DensoBulkMacGen                                               4
#define CryptoConf_CryptoDriverObject_CryptoDriverObject_General                                                       5

/*** Keys and Key Elements Definitions ********************************************************************************/
#define CRYPTO_82_HSM_NUMBER_OF_KEYS                                                                                (2u)
#define CRYPTO_82_HSM_NUMBER_OF_KEY_ELEMENTS                                                                        (4u)

#define CryptoConf_CryptoKey_CryptoKey_KeyVerify_SecOC_Mac                                                             0
#define CryptoConf_CryptoKey_CryptoKey_MASTER_ECU_KEY                                                                  1

/**********************************************************************************************************************\
 * PUBLIC TYPE DEFINITIONS
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * EXTERN PUBLIC VARIABLES
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * PUBLIC FUNCTION DECLARATIONS
\**********************************************************************************************************************/

#endif



