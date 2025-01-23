/*
    Copyright (C) 2016 By eSOL Co.,Ltd. Tokyo, Japan

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
[stdlib.h] - AUTOSAR stdlib header
****************************************************************************/
#ifndef STDLIB_H_AUTOSAR
#define STDLIB_H_AUTOSAR

#include "inttypes.h"

/* NULL */
#ifndef NULL

#if defined(__null)
#define NULL    __null
#else   /* defined(__null) */
#if defined(__cplusplus)
#define NULL    0
#else   /* defined(__cplusplus) */
#define NULL    (void *)0
#endif  /* defined(__cplusplus) */
#endif  /* defined(__null) */

#endif  /* #ifndef  NULL */

/* size_t, ssize_t */
typedef TYPE_SIZE    size_t;
typedef TYPE_SSIZE   ssize_t;

#endif  /* STDLIB_H_AUTOSAR */
