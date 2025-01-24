/****************************************************************************/
/* Copyright DENSO Corporation. All rights reserved                         */
/*************************************************************************//**
 * @file GW_CHM_Memmap.h
 ****************************************************************************/

#include "Section_Util.h"

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
/* GW_CHM_CONST */
#if defined GW_CHM_START_SEC_CONST
    #undef MEMMAP_ERROR
    PRAGMA_SECTION(rodata, ".gw_chm_const")
    #undef GW_CHM_START_SEC_CONST
#elif defined GW_CHM_STOP_SEC_CONST
    #undef MEMMAP_ERROR
    PRAGMA_SECTION_DEFAULT(rodata)
    #undef GW_CHM_STOP_SEC_CONST

#endif

#if defined MEMMAP_ERROR
    #error "GW_CHM_Memmap.h, wrong Memmap.h usage"
#endif /* MEMMAP_ERROR */
