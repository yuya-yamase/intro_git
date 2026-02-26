/**
 * \file        Crypto_82_Hsm_Custom_Algorithms.h
 * \author      PiNTeam
 * \copyright   (c) DENSO KK, 2022
 * 
 * \brief       File that contains custom defined algorithms and is then included in Csm_Cfg.h
 * \details
*/

#ifndef CRYPTO_82_HSM_CUSTOM_ALGORITHMS_H
#define CRYPTO_82_HSM_CUSTOM_ALGORITHMS_H

/**********************************************************************************************************************\
 * INCLUDES
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * PUBLIC MACROS
\**********************************************************************************************************************/

/* ECC curves with option 'USERHASHED' supported by cycurHSM but not yet in CSM */
# ifndef CRYPTO_ALGOFAM_CUSTOM_ECCNIST_USERHASHED 
#  define CRYPTO_ALGOFAM_CUSTOM_ECCNIST_USERHASHED                               (39u)
# endif

/* Algo fam for HSM CycurHSM Key Derive processing */
# ifndef CRYPTO_ALGOFAM_CUSTOM_KDF_NISTSP80056C 
#  define CRYPTO_ALGOFAM_CUSTOM_KDF_NISTSP80056C                                 (42u)
# endif

/* Algo fam for HSM CycurHSM Hash processing */
# ifndef CRYPTO_ALGOFAM_CUSTOM_AES_MP 
#  define CRYPTO_ALGOFAM_CUSTOM_AES_MP                                           (43u)
#endif

/* EdDSA curve with option 'SHA_512_DOM2_PH_USERHASHED' supported by cycurHSM but not yet in CSM */
# ifndef CRYPTO_ALGOFAM_CUSTOM_ED25519_SHA_512_DOM2_PH_USERHASHED
#  define CRYPTO_ALGOFAM_CUSTOM_ED25519_SHA_512_DOM2_PH_USERHASHED               (44u)
# endif

/* Algo fam for HSM CycurHSM Key Derive processing */
# ifndef CRYPTO_ALGOFAM_CUSTOM_KDF_NISTSP800108 
#  define CRYPTO_ALGOFAM_CUSTOM_KDF_NISTSP800108                                 (45u)
# endif

/* Algo fam for HSM CycurHSM Key Derive processing */
# ifndef CRYPTO_ALGOFAM_CUSTOM_KDF_ANSIX963 
#  define CRYPTO_ALGOFAM_CUSTOM_KDF_ANSIX963                                     (46u)
# endif

/* CRYPTO_ALGOFAM_PADDING_PKCS7: Cipher padding according to PKCS.7 */
# ifndef CRYPTO_ALGOFAM_CUSTOM_PADDING_PKCS7 
#  define CRYPTO_ALGOFAM_CUSTOM_PADDING_PKCS7                                    (CRYPTO_ALGOFAM_PADDING_PKCS7)
# endif

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

