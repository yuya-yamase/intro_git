/****************************************************************************/
/* Copyright DENSO Corporation. All rights reserved                         */
/*************************************************************************//**
 * @file GW_CID_Memmap.h
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
/* GW_CID_CODE */
#if defined GW_CID_START_SEC_CODE
    #undef MEMMAP_ERROR
    PRAGMA_SECTION(text, ".gw_cid_code")
    #undef GW_CID_START_SEC_CODE
#elif defined GW_CID_STOP_SEC_CODE
    #undef MEMMAP_ERROR
    PRAGMA_SECTION_DEFAULT(text)
    #undef GW_CID_STOP_SEC_CODE

/* GW_CID_CONST */
#elif defined GW_CID_START_SEC_CONST
    #undef MEMMAP_ERROR
    PRAGMA_SECTION(rodata, ".gw_cid_const")
    #undef GW_CID_START_SEC_CONST
#elif defined GW_CID_STOP_SEC_CONST
    #undef MEMMAP_ERROR
    PRAGMA_SECTION_DEFAULT(rodata)
    #undef GW_CID_STOP_SEC_CONST

#endif

#if defined MEMMAP_ERROR
    #error "GW_CID_Memmap.h, wrong Memmap.h usage"
#endif /* MEMMAP_ERROR */
