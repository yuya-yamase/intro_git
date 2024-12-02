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
[ ehvm_bios_basic.h ] - BIOS basic interfaces
****************************************************************************/
#ifndef EHVM_BIOS_BASIC_H
#define EHVM_BIOS_BASIC_H

/* version (ver2.2 rev5) */
#define BIOS_VERSION 225

/* Green Hills C/C++ compiler */
#define BIOS_INLINE static __inline

/* signed integer */
typedef signed long bios_int_t;

/* unsigned integer */
typedef unsigned long bios_uint_t;

/* signed 8-bit integer */
typedef signed char bios_int8_t;

/* unsigned 8-bit integer */
typedef unsigned char bios_uint8_t;

/* signed 16-bit integer */
typedef signed short bios_int16_t;

/* unsigned 16-bit integer */
typedef unsigned short bios_uint16_t;

/* signed 32-bit integer */
typedef signed long bios_int32_t;

/* unsigned 32-bit integer */
typedef unsigned long bios_uint32_t;

/* signed 64-bit integer (later ver2.0) */
typedef signed long long bios_int64_t;

/* unsigned 64-bit integer (later ver2.0) */
typedef unsigned long long bios_uint64_t;


/* 32-bit floating-point (later ver2.1 rev1) */
typedef float bios_float32_t;

/* 64-bit floating-point (later ver2.1 rev1) */
typedef double bios_float64_t;

/* integer for address */
typedef bios_uint_t bios_addr_t;

typedef bios_uint32_t bios_bool_t;
/* false */
#define bios_FALSE (bios_bool_t)(0U)
/* true */
#define bios_TRUE  (bios_bool_t)(1U)

typedef bios_int32_t bios_error_t;
/* error codes */
/* no error */
#define     bios_error_OK              (bios_error_t)(0)
/* system error */
#define     bios_error_SYSTEM          (bios_error_t)(-5)
/* not supported function */
#define     bios_error_NOT_SUPPORTED   (bios_error_t)(-9)
/* invalid argument */
#define     bios_error_INVALID_ARGUMEN (bios_error_t)(-17)
/* inaccessible context (later ver2.2 rev0) */
#define     bios_error_CONTEXT         (bios_error_t)(-25)
/* illegal usage */
#define     bios_error_ILLEGAL_USAGE   (bios_error_t)(-28)
/* no allocateble object (later ver2.2 rev0) */
#define     bios_error_NO_FREE_OBJECT  (bios_error_t)(-34)
/* invalid object state (later ver2.0 rev0) */
#define     bios_error_STATE           (bios_error_t)(-41)
/* not found (later ver1.6 rev0) */
#define     bios_error_NOT_FOUND       (bios_error_t)(-100)
/* invalid object (later ver2.0 rev0) */
#define     bios_error_OBJECT          (bios_bool_t)(-101)

#endif /* #ifndef EHVM_BIOS_BASIC_H */
