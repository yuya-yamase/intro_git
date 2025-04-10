/*
    Copyright (C) 2016 eSOL Co.,Ltd. Tokyo, Japan

    This software is protected by the law and the agreement concerning
    a Japanese country copyright method, an international agreement,
    and other intellectual property right and may be used and copied
    only in accordance with the terms of such license and with the inclusion
    of the above copyright notice.

    This software or any other copies thereof may not be provided
    or otherwise made available to any other person.  No title to
    and ownership of the software is hereby transferred.

    The information in this software is subject to change without
    notice and should not be construed as a commitment by eSOL Co.,Ltd.
*/
/****************************************************************************
[ os_memmap_entry.h ] - Memory Mapping public header for OS module
****************************************************************************/

/* Define error for xxx */
#define MEMMAP_ERROR

#if defined __ghs__
#include "os_memmap_ghs.h"
#elif defined __GNUC__ && !defined __ARMCC_VERSION /* #if defined __ghs__ */
#include "os_memmap_gcc.h"
#elif defined __ARMCC_VERSION /* #elif defined __GNUC__ && !defined __ARMCC_VERSION */
#if __ARMCC_VERSION >= 6000000U
#include "os_memmap_armclang.h"
#else /* #if __ARMCC_VERSION >= 6000000U */
#include "os_memmap_armct.h"
#endif /* #if __ARMCC_VERSION >= 6000000U */
#else /* #elif defined __ARMCC_VERSION */
#undef MEMMAP_ERROR
#endif /* #else */

/*----------------------------------
     Error check
 -----------------------------------*/
#ifdef MEMMAP_ERROR
#error "Os_MemMap.h, wrong pragma command"
#endif /* MEMMAP_ERROR */
