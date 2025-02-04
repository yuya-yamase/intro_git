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
[ hal_basic_impl.h ] - HAL basic interfaces for implementers
****************************************************************************/
#ifndef HAL_BASIC_IMPL_H
#define HAL_BASIC_IMPL_H

#include <hal/hal_basic.h>

/* read/write 8bit register */
typedef volatile unsigned char hal_reg8_t;

/* read/write 16bit register */
typedef volatile unsigned short hal_reg16_t;

/* read/write 32bit register */
typedef volatile unsigned long hal_reg32_t;

/* read/write 64bit register */
typedef volatile unsigned long long hal_reg64_t;

/* read-only 8bit register */
typedef volatile const unsigned char hal_reg8r_t;

/* read-only 16bit register */
typedef volatile const unsigned short hal_reg16r_t;

/* read-only 32bit register */
typedef volatile const unsigned long hal_reg32r_t;

/* write-only 8bit register */
typedef volatile unsigned char hal_reg8w_t;

/* write-only 16bit register */
typedef volatile unsigned short hal_reg16w_t;

/* write-only 32bit register */
typedef volatile unsigned long hal_reg32w_t;

/* inaccessible 8bit register */
typedef volatile const unsigned char hal_reg8rfu_t;

/* inaccessible 16bit register */
typedef volatile const unsigned short hal_reg16rfu_t;

/* inaccessible 32bit register */
typedef volatile const unsigned long hal_reg32rfu_t;

struct hal_reg16_8
{
    /* the most significant 8bits */
    hal_reg8_t reg8;
    /* reseved */
    hal_reg8rfu_t rfu;
}; /* struct hal_reg16_8 */

/* read/write 16bit-aligned 8bit register */
typedef struct hal_reg16_8 hal_reg16_8_t;

/* read only 16bit-aligned 8bit register */
typedef const hal_reg16_8_t hal_reg16_8r_t;

/* write only 16bit-aligned 8bit register */
typedef hal_reg16_8_t hal_reg16_8w_t;

struct hal_reg32_8
{
    /* the most significant 8bits */
    hal_reg8_t reg8;
    /* reseved */
    hal_reg8rfu_t rfu[3];
}; /* struct hal_reg32_8 */

/* read/write 32bit-aligned 8bit register */
typedef struct hal_reg32_8 hal_reg32_8_t;

/* read only 32bit-aligned 8bit register */
typedef const hal_reg32_8_t hal_reg32_8r_t;

/* write only 32bit-aligned 8bit register */
typedef hal_reg32_8_t hal_reg32_8w_t;

struct hal_reg32_16
{
    /* the most significant 16bits */
    hal_reg16_t reg16;
    /* reseved */
    hal_reg16rfu_t rfu;
}; /* struct hal_reg32_16 */

/* read/write 32bit-aligned 16bit register */
typedef struct hal_reg32_16 hal_reg32_16_t;

/* read only 32bit-aligned 16bit register */
typedef const hal_reg32_16_t hal_reg32_16r_t;

/* write only 32bit-aligned 16bit register */
typedef hal_reg32_16_t hal_reg32_16w_t;

#endif /* #ifndef HAL_BASIC_IMPL_H */
