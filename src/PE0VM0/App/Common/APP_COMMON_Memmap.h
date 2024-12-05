/****************************************************************************/
/* Copyright DENSO Corporation. All rights reserved                         */
/*************************************************************************//**
* @file APP_COMMON_Memmap.h
 ****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Check Error                                                              */
/*--------------------------------------------------------------------------*/
#if (defined MEMMAP_ERROR)  /* Memmapが間違った方法で使用されていないか確認 */
    #error MEMMAP_ERROR defined, wrong Memmap.h usage
#endif /* if (defined MEMMAP_ERROR) */

#define MEMMAP_ERROR

/*--------------------------------------------------------------------------*/
/* Start Memory Mapping                                                     */
/*--------------------------------------------------------------------------*/
/* APP_COMMON_CRAM0_BSS */
#if defined APP_COMMON_START_SEC_CRAM0_BSS
    #undef MEMMAP_ERROR
    #pragma ghs section bss=".app_common_cram0_bss"
    #undef APP_COMMON_START_SEC_CRAM0_BSS
#elif defined APP_COMMON_STOP_SEC_CRAM0_BSS
    #undef MEMMAP_ERROR
    #pragma ghs section
    #undef APP_COMMON_STOP_SEC_CRAM0_BSS

#endif

#if defined MEMMAP_ERROR
    #error "APP_COMMON_Memmap.h, wrong Memmap.h usage"
#endif /* MEMMAP_ERROR */
