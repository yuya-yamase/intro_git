/*
    Copyright(C) 2019 eSOL Co., Ltd. All rights reserved.

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
[stdint_v850_ghs.h] - AUTOSAR stdint header for V850/GHS
****************************************************************************/
#ifndef STDINT_V850_GHS_H
#define STDINT_V850_GHS_H

/*-----------------------------------------------------------------------------
    Type definitions
 -----------------------------------------------------------------------------*/

typedef unsigned char                   uint8_t;
typedef unsigned short int              uint16_t;
typedef unsigned int                    uint32_t;
typedef unsigned long long int          uint64_t;
typedef signed char                     int8_t;
typedef signed short int                int16_t;
typedef signed int                      int32_t;
typedef signed long long int            int64_t;

typedef uint8_t                         uint8_least_t;
typedef uint16_t                        uint16_least_t;
typedef uint32_t                        uint32_least_t;
typedef uint64_t                        uint64_least_t;
typedef int8_t                          int8_least_t;
typedef int16_t                         int16_least_t;
typedef int32_t                         int32_least_t;
typedef int64_t                         int64_least_t;

typedef unsigned int                    uint_fast8_t;
typedef unsigned int                    uint_fast16_t;
typedef unsigned int                    uint_fast32_t;
typedef uint64_t                        uint_fast64_t;
typedef int                             int_fast8_t;
typedef int                             int_fast16_t;
typedef int                             int_fast32_t;
typedef int64_t                         int_fast64_t;

typedef signed int                      mcos_intptr_t;
typedef unsigned int                    mcos_uintptr_t;

typedef int64_t                         mcos_intmax_t;
typedef uint64_t                        mcos_uintmax_t;

/*-----------------------------------------------------------------------------
    MIN/MAX macros
 -----------------------------------------------------------------------------*/
#if ((!defined(__cplusplus)) || (defined(__STDC_LIMIT_MACROS)))

#define INT8_MIN    (-0x7f-1)
#define INT16_MIN   (-0x7fff-1)
#define INT32_MIN   (-0x7fffffff-1)
#define INT64_MIN   (-0x7fffffffffffffffLL-1)

#define INT8_MAX    0x7f
#define INT16_MAX   0x7fff
#define INT32_MAX   0x7fffffff
#define INT64_MAX   0x7fffffffffffffffLL

#define UINT8_MAX   0xffU
#define UINT16_MAX  0xffffU
#define UINT32_MAX  0xffffffffU
#define UINT64_MAX  0xffffffffffffffffULL

#define INT_LEAST8_MIN  (-0x7f-1)
#define INT_LEAST16_MIN (-0x7fff-1)
#define INT_LEAST32_MIN (-0x7fffffff-1)
#define INT_LEAST64_MIN (-0x7fffffffffffffffLL-1)

#define INT_LEAST8_MAX  0x7f
#define INT_LEAST16_MAX 0x7fff
#define INT_LEAST32_MAX 0x7fffffff
#define INT_LEAST64_MAX 0x7fffffffffffffffLL

#define UINT_LEAST8_MAX  0xffU
#define UINT_LEAST16_MAX 0xffffU
#define UINT_LEAST32_MAX 0xffffffffU
#define UINT_LEAST64_MAX 0xffffffffffffffffULL

#define INT_FAST8_MIN   (-0x7fffffff-1)
#define INT_FAST16_MIN  (-0x7fffffff-1)
#define INT_FAST32_MIN  (-0x7fffffff-1)
#define INT_FAST64_MIN  (-0x7fffffffffffffffLL-1)

#define INT_FAST8_MAX   0x7fffffff
#define INT_FAST16_MAX  0x7fffffff
#define INT_FAST32_MAX  0x7fffffff
#define INT_FAST64_MAX  0x7fffffffffffffffLL

#define UINT_FAST8_MAX  0xffffffffU
#define UINT_FAST16_MAX 0xffffffffU
#define UINT_FAST32_MAX 0xffffffffU
#define UINT_FAST64_MAX 0xffffffffffffffffULL

#define MCOS_UINTPTR_MAX 0xffffffffU

#define MCOS_INTMAX_MAX  0x7fffffffffffffffLL

#define TYPE_SIZE  uint32_t
#define TYPE_SSIZE int32_t

#endif  /* ((!defined(__cplusplus)) || (defined(__STDC_LIMIT_MACROS))) */

#endif  /* STDINT_V850_GHS_H */
