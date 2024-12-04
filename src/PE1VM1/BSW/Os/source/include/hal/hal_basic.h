/*
    Copyright (C) 2018 By eSOL Co.,Ltd. Tokyo, Japan

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
[ hal_basic.h ] - HAL basic interfaces
****************************************************************************/
#ifndef HAL_BASIC_H
#define HAL_BASIC_H

/* MACRO for inline keywords */
#if defined __ARMCC_VERSION

/* ARM Compiler */
#define HAL_INLINE  static inline __attribute__((always_inline))

#elif defined __TMS470__ /* #if defined __ARMCC_VERSION */

/* Texias Instruments TMS470 */
#define HAL_INLINE __inline

#elif defined __HITACHI__ /* #elif defined __TMS470__ */

/* Renesas C/C++ compiler */
#define HAL_INLINE static

#elif defined __ghs__ /* #elif defined __HITACHI__ */

/* Green Hills C/C++ compiler */
#define HAL_INLINE static __inline

#elif defined __GNUC__

/* GNU C/C++ compiler */
#define HAL_INLINE static __inline__

#else /* #elif defined __GNUC__ */

/* NOTE : just for LINT */
#define HAL_INLINE static

#endif /* #else */

/* signed integer */
typedef signed int hal_int_t;

/* unsigned integer */
typedef unsigned int hal_uint_t;

/* signed 8-bit integer */
typedef signed char hal_int8_t;

/* unsigned 8-bit integer */
typedef unsigned char hal_uint8_t;

/* signed 16-bit integer */
typedef signed short hal_int16_t;

/* unsigned 16-bit integer */
typedef unsigned short hal_uint16_t;

/* signed 32-bit integer */
typedef signed long hal_int32_t;

/* unsigned 32-bit integer */
typedef unsigned long hal_uint32_t;


/* boolean value */
#define hal_FALSE   0L
#define hal_TRUE    1L
typedef hal_int32_t hal_bool_t;

/* error code */
#define hal_error_OK      0L
#define hal_error_ERROR (-1L)
typedef hal_int32_t hal_error_t;

struct hal_pic_info
{
    hal_int_t minIntno;
    hal_int_t maxIntno;
};
typedef struct hal_pic_info hal_pic_info_t;

#endif /* #ifndef HAL_BASIC_H */
