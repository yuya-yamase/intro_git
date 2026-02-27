/****************************************************************************
 * Protected                                                                *
 * Copyright AUBASS CO., LTD.                                               *
 ****************************************************************************

    Copyright (C) 2022 eSOL Co.,Ltd. Tokyo, Japan

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
 [ Os_Cfg_memmap.h ] - OS module's configuration data file
****************************************************************************/

/* Define error for xxx */
#define MEMMAP_ERROR



#if defined __ghs__
#include "Os_Cfg_memmap_ghs.h"
#elif defined __GNUC__ && !defined __ARMCC_VERSION /* #if defined __ghs__ */
#error "No support"
#elif defined __ARMCC_VERSION /* #elif defined __GNUC__ && !defined __ARMCC_VERSION */
#if __ARMCC_VERSION >= 6000000U
#include "Os_Cfg_memmap_armclang.h"
#else /* #if __ARMCC_VERSION >= 6000000U */
#error "No support"
#endif /* #if __ARMCC_VERSION >= 6000000U */
#else /* #elif defined __ARMCC_VERSION */
#undef MEMMAP_ERROR
#endif /* #else */



/*----------------------------------
Error check
-----------------------------------*/
#ifdef MEMMAP_ERROR
#error "Os_Cfg_memmap.h, wrong pragma command"
#endif /* MEMMAP_ERROR */

/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/
