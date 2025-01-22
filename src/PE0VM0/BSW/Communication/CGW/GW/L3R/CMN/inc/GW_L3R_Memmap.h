/****************************************************************************/
/* Copyright DENSO Corporation. All rights reserved                         */
/*************************************************************************//**
 * @file GW_L3R_Memmap.h
 ****************************************************************************/

#include "L3R_Section.h"

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
/* GW_L3R_CODE */
#if defined GW_L3R_START_SEC_CODE
    #undef MEMMAP_ERROR
    L3R_PRAGMA_SECTION_CODE_START
    #undef GW_L3R_START_SEC_CODE
#elif defined GW_L3R_STOP_SEC_CODE
    #undef MEMMAP_ERROR
    L3R_PRAGMA_SECTION_CODE_STOP
    #undef GW_L3R_STOP_SEC_CODE

/* GW_L3R_CONST */
#elif defined GW_L3R_START_SEC_CONST
    #undef MEMMAP_ERROR
    L3R_PRAGMA_SECTION_CONST_START
    #undef GW_L3R_START_SEC_CONST
#elif defined GW_L3R_STOP_SEC_CONST
    #undef MEMMAP_ERROR
    L3R_PRAGMA_SECTION_CONST_STOP
    #undef GW_L3R_STOP_SEC_CONST

/* GW_L3R_VAR */
/* #elif defined GW_L3R_START_SEC_VAR */
/*     #undef MEMMAP_ERROR */
/*     L3R_PRAGMA_SECTION_DATA_START */
/*     L3R_PRAGMA_SECTION_NO_INIT_START */
/*     #undef GW_L3R_START_SEC_VAR */
/* #elif defined GW_L3R_STOP_SEC_VAR */
/*     #undef MEMMAP_ERROR */
/*     L3R_PRAGMA_SECTION_DATA_STOP */
/*     L3R_PRAGMA_SECTION_NO_INIT_STOP */
/*     #undef GW_L3R_STOP_SEC_VAR */

/* GW_L3R_VAR_NO_INIT */
/* #elif defined GW_L3R_START_SEC_VAR_NO_INIT */
/*     #undef MEMMAP_ERROR */
/*     L3R_PRAGMA_SECTION_NO_INIT_START */
/*     #undef GW_L3R_START_SEC_VAR_NO_INIT */
/* #elif defined GW_L3R_STOP_SEC_VAR_NO_INIT */
/*     #undef MEMMAP_ERROR */
/*     L3R_PRAGMA_SECTION_NO_INIT_STOP */
/*     #undef GW_L3R_STOP_SEC_VAR_NO_INIT */

/* Non-Backup Variables w/ Zero Initialization */
#elif defined GW_L3R_START_SEC_NBVA_ZI
    #undef MEMMAP_ERROR
    L3R_PRAGMA_SECTION_NBVA_ZI_START
    #undef GW_L3R_START_SEC_NBVA_ZI
#elif defined GW_L3R_STOP_SEC_NBVA_ZI
    #undef MEMMAP_ERROR
    L3R_PRAGMA_SECTION_NBVA_ZI_STOP
    #undef GW_L3R_STOP_SEC_NBVA_ZI

/* GW_L3R_VAR_SAVED_ZONE */
/* #elif defined GW_L3R_START_SEC_VAR_SAVED_ZONE */
/*     #undef MEMMAP_ERROR */
/*     L3R_PRAGMA_SECTION_DATA_BKUP_START */
/*     L3R_PRAGMA_SECTION_NO_INIT_BKUP_START */
/*     #undef GW_L3R_START_SEC_VAR_SAVED_ZONE */
/* #elif defined GW_L3R_STOP_SEC_VAR_SAVED_ZONE */
/*     #undef MEMMAP_ERROR */
/*     L3R_PRAGMA_SECTION_DATA_BKUP_STOP */
/*     L3R_PRAGMA_SECTION_NO_INIT_BKUP_STOP */
/*     #undef GW_L3R_STOP_SEC_VAR_SAVED_ZONE */

/* Backup/Retentionable Variables w/ Zero Initialization */
#elif defined GW_L3R_START_SEC_BUVA_ZI
    #undef MEMMAP_ERROR
    L3R_PRAGMA_SECTION_BUVA_ZI_START
    #undef GW_L3R_START_SEC_BUVA_ZI
#elif defined GW_L3R_STOP_SEC_BUVA_ZI
    #undef MEMMAP_ERROR
    L3R_PRAGMA_SECTION_BUVA_ZI_STOP
    #undef GW_L3R_STOP_SEC_BUVA_ZI

#endif

#if defined MEMMAP_ERROR
    #error "GW_L3R_Memmap.h, wrong Memmap.h usage"
#endif /* MEMMAP_ERROR */
