/**
 * \file Crypto_82_Hsm_MemMap.h
 * \author      PiNTeam
 * \copyright   (c) DENSO KK, 2022
 *
 * \brief Header file for MemMap
 * \details
*/
#define CRYPTO_82_HSM_CODE
#define CRYPTO_82_HSM_VAR
#define CRYPTO_82_HSM_CONST

#ifdef CRYPTO_82_HSM_START_SEC_CODE
    #pragma ghs section text = ".bsw_crypto_text"
    #undef CRYPTO_82_HSM_START_SEC_CODE
    /*	#define START_SEC_CODE	*/
    /*	#include "MemMap.h"	*/
#endif

#ifdef CRYPTO_82_HSM_STOP_SEC_CODE
    #pragma ghs section text = default
    #undef CRYPTO_82_HSM_STOP_SEC_CODE
    /*	#define STOP_SEC_CODE	*/
    /*	#include "MemMap.h"	*/
#endif

#ifdef CRYPTO_82_HSM_START_SEC_CONST_8BIT
    #pragma ghs startdata
    #pragma ghs section rodata = ".bsw_crypto_rodata"
    #undef CRYPTO_82_HSM_START_SEC_CONST_8BIT
    /*	#define START_SEC_CONST_8BIT	*/
    /*	#include "MemMap.h"	*/
#endif

#ifdef CRYPTO_82_HSM_STOP_SEC_CONST_8BIT
    #pragma ghs section rodata = default
    #pragma ghs enddata
    #undef CRYPTO_82_HSM_STOP_SEC_CONST_8BIT
    /*	#define STOP_SEC_CONST	*/
    /*	#include "MemMap.h"	*/
#endif

#ifdef CRYPTO_82_HSM_START_SEC_CONST_32BIT
    #pragma ghs startdata
    #pragma ghs section rodata = ".bsw_crypto_rodata"
    #undef CRYPTO_82_HSM_START_SEC_CONST_32BIT
    /*	#define START_SEC_CONST_32BIT	*/
    /*	#include "MemMap.h"	*/
#endif

#ifdef CRYPTO_82_HSM_STOP_SEC_CONST_32BIT
    #pragma ghs section rodata = default
    #pragma ghs enddata
    #undef CRYPTO_82_HSM_STOP_SEC_CONST_32BIT
    /*	#define STOP_SEC_CONST	*/
    /*	#include "MemMap.h"	*/
#endif

#ifdef CRYPTO_82_HSM_START_SEC_CONST_UNSPECIFIED
    #pragma ghs startdata
    #pragma ghs section rodata = ".bsw_crypto_rodata"
    #undef CRYPTO_82_HSM_START_SEC_CONST_UNSPECIFIED
    /*	#define START_SEC_CONST_UNSPECIFIED	*/
    /*	#include "MemMap.h"	*/
#endif

#ifdef CRYPTO_82_HSM_STOP_SEC_CONST_UNSPECIFIED
    #pragma ghs section rodata = default
    #pragma ghs enddata
    #undef CRYPTO_82_HSM_STOP_SEC_CONST_UNSPECIFIED
    /*	#define STOP_SEC_CONST	*/
    /*	#include "MemMap.h"	*/
#endif

#ifdef CRYPTO_82_HSM_START_SEC_VAR_NOINIT_8BIT
    #pragma ghs startdata
    #pragma ghs section bss = ".bsw_crypto_bss"
    #undef CRYPTO_82_HSM_START_SEC_VAR_NOINIT_8BIT
    /*	#define START_SEC_VAR_NOINIT_8BIT	*/
    /*	#include "MemMap.h"	*/
#endif

#ifdef CRYPTO_82_HSM_STOP_SEC_VAR_NOINIT_8BIT
    #pragma ghs section bss = default
    #pragma ghs enddata
    #undef CRYPTO_82_HSM_STOP_SEC_VAR_NOINIT_8BIT
    /*	#define STOP_SEC_VAR	*/
    /*	#include "MemMap.h"	*/
#endif

#ifdef CRYPTO_82_HSM_START_SEC_VAR_NOINIT_32BIT
    #pragma ghs startdata
    #pragma ghs section bss = ".bsw_crypto_bss"
    #undef CRYPTO_82_HSM_START_SEC_VAR_NOINIT_32BIT
    /*	#define START_SEC_VAR_NOINIT_32BIT	*/
    /*	#include "MemMap.h"	*/
#endif

#ifdef CRYPTO_82_HSM_STOP_SEC_VAR_NOINIT_32BIT
    #pragma ghs section bss = default
    #pragma ghs enddata
    #undef CRYPTO_82_HSM_STOP_SEC_VAR_NOINIT_32BIT
    /*	#define STOP_SEC_VAR	*/
    /*	#include "MemMap.h"	*/
#endif

#ifdef CRYPTO_82_HSM_START_SEC_VAR_NOINIT_UNSPECIFIED
    #pragma ghs startdata
    #pragma ghs section bss = ".bsw_crypto_bss"
    #undef CRYPTO_82_HSM_START_SEC_VAR_NOINIT_UNSPECIFIED
    /*	#define START_SEC_VAR_NOINIT_UNSPECIFIED	*/
    /*	#include "MemMap.h"	*/
#endif

#ifdef CRYPTO_82_HSM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
    #pragma ghs section bss = default
    #pragma ghs enddata
    #undef CRYPTO_82_HSM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
    /*	#define STOP_SEC_VAR	*/
    /*	#include "MemMap.h"	*/
#endif

#ifdef CRYPTO_82_HSM_START_SEC_VAR_INIT_UNSPECIFIED
    #pragma ghs startdata
    #pragma ghs section data = ".bsw_crypto_data"
    #undef CRYPTO_82_HSM_START_SEC_VAR_INIT_UNSPECIFIED
    /*	#define START_SEC_VAR_NOINIT_UNSPECIFIED	*/
    /*	#include "MemMap.h"	*/
#endif

#ifdef CRYPTO_82_HSM_STOP_SEC_VAR_INIT_UNSPECIFIED
    #pragma ghs section data = default
    #pragma ghs enddata
    #undef CRYPTO_82_HSM_STOP_SEC_VAR_INIT_UNSPECIFIED
    /*	#define STOP_SEC_VAR	*/
    /*	#include "MemMap.h"	*/
#endif

#ifdef CRYPTO_82_HSM_START_SEC_VAR_INIT_8BIT
    #pragma ghs startdata
    #pragma ghs section data = ".bsw_crypto_data"
    #undef CRYPTO_82_HSM_START_SEC_VAR_INIT_8BIT
    /*	#define START_SEC_VAR_INIT_8BIT	*/
    /*	#include "MemMap.h"	*/
#endif

#ifdef CRYPTO_82_HSM_STOP_SEC_VAR_INIT_8BIT
    #pragma ghs section data = default
    #pragma ghs enddata
    #undef CRYPTO_82_HSM_STOP_SEC_VAR_INIT_8BIT
    /*	#define STOP_SEC_VAR	*/
    /*	#include "MemMap.h"	*/
#endif

#ifdef CRYPTO_82_HSM_START_SEC_VAR_INIT_32BIT
    #pragma ghs startdata
    #pragma ghs section data = ".bsw_crypto_data"
    #undef CRYPTO_82_HSM_START_SEC_VAR_INIT_32BIT
    /*	#define START_SEC_VAR_INIT_32BIT	*/
    /*	#include "MemMap.h"	*/
#endif

#ifdef CRYPTO_82_HSM_STOP_SEC_VAR_INIT_32BIT
    #pragma ghs section data = default
    #pragma ghs enddata
    #undef CRYPTO_82_HSM_STOP_SEC_VAR_INIT_32BIT
    /*	#define STOP_SEC_VAR	*/
    /*	#include "MemMap.h"	*/
#endif

#ifdef CRYPTO_82_HSM_START_SEC_VAR_CRYPTO_SHARED_NOINIT
    /* Enter here a #pragma command for opening the specified section */
    #pragma ghs startdata
    #pragma ghs section bss=".bsw_crypto_hsm_shared_bss"
    #undef CRYPTO_82_HSM_START_SEC_VAR_CRYPTO_SHARED_NOINIT
#endif

#ifdef CRYPTO_82_HSM_STOP_SEC_VAR_CRYPTO_SHARED_NOINIT
    /* Enter here a #pragma command for opening the specified section */
    /*    #pragma */
    #pragma ghs section bss=default
    #pragma ghs enddata
    #undef CRYPTO_82_HSM_STOP_SEC_VAR_CRYPTO_SHARED_NOINIT
#endif

#ifdef CRYPTO_82_HSM_START_SEC_VAR_CRYPTO_SHARED_INIT
    /* Enter here a #pragma command for opening the specified section */
    #pragma ghs startdata
    #pragma ghs section data=".bsw_crypto_hsm_shared_data"
    #undef CRYPTO_82_HSM_START_SEC_VAR_CRYPTO_SHARED_INIT
#endif

#ifdef CRYPTO_82_HSM_STOP_SEC_VAR_CRYPTO_SHARED_INIT
    /* Enter here a #pragma command for opening the specified section */
    /*    #pragma */
    #pragma ghs section data=default
    #pragma ghs enddata
    #undef CRYPTO_82_HSM_STOP_SEC_VAR_CRYPTO_SHARED_INIT
#endif

#ifdef CRYPTO_82_HSM_START_SEC_CONST_CRYPTO_SHARED
    /* Enter here a #pragma command for opening the specified section */
    #pragma ghs startdata
    #pragma ghs section rodata = ".bsw_crypto_rodata"
    #undef CRYPTO_82_HSM_START_SEC_CONST_CRYPTO_SHARED
#endif

#ifdef CRYPTO_82_HSM_STOP_SEC_CONST_CRYPTO_SHARED
    /* Enter here a #pragma command for opening the specified section */
    #pragma ghs section rodata = default
    #pragma ghs enddata
    #undef CRYPTO_82_HSM_STOP_SEC_CONST_CRYPTO_SHARED
#endif

#if ((defined CRYPTO_82_HSM_START_SEC_VAR_CRYPTO_SHARED_NOINIT  ) || \
     (defined CRYPTO_82_HSM_START_SEC_VAR_CRYPTO_SHARED_INIT    ) || \
     (defined CRYPTO_82_HSM_START_SEC_CONST_CRYPTO_SHARED       ))
#error "Crypto_82_Hsm_MemMap.h: New section opened before closing the former one. Please close the former code/const/data section before opening a new one. (Check_2)"
#endif /* PRQA S 0883  #This rule violation is suppressed because MemMap must allow for multiple reinclusion in order to change memory section. */
