/*
    Copyright (C) 2022 eSOL Co.,Ltd. All rights reserved.

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
[ehvm_types_stdint.h] - EHVM API module header
****************************************************************************/

#ifndef EHVM_TYPES_STDINT_H
#define EHVM_TYPES_STDINT_H

#define EHVM_INT8_MIN    (-0x7f-1)
#define EHVM_INT16_MIN   (-0x7fff-1)
#define EHVM_INT32_MIN   (-0x7fffffff-1)
#define EHVM_INT64_MIN   (-0x7fffffffffffffffLL-1)

#define EHVM_INT8_MAX    0x7f
#define EHVM_INT16_MAX   0x7fff
#define EHVM_INT32_MAX   0x7fffffff
#define EHVM_INT64_MAX   0x7fffffffffffffffLL

#define EHVM_UINT8_MAX   0xffU
#define EHVM_UINT16_MAX  0xffffU
#define EHVM_UINT32_MAX  0xffffffffUL
#define EHVM_UINT64_MAX  0xffffffffffffffffULL

#define EhvmConst       volatile const
#define EhvmConstR      const

typedef unsigned char                   ehvm_uint8_t;
typedef unsigned short                  ehvm_uint16_t;
typedef unsigned long                   ehvm_uint32_t;
typedef unsigned long long              ehvm_uint64_t;
typedef signed char                     ehvm_int8_t;
typedef signed short                    ehvm_int16_t;
typedef signed long                     ehvm_int32_t;
typedef signed long long                ehvm_int64_t;

typedef signed long                     ehvm_intptr_t;
typedef unsigned long                   ehvm_uintptr_t;

#endif /* EHVM_TYPES_STDINT_H */
