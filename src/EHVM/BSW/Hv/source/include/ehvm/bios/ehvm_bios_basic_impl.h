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
[ ehvm_bios_basic_impl.h ] - BIOS basic interfaces for implementers
****************************************************************************/
#ifndef EHVM_BIOS_BASIC_IMPL_H
#define EHVM_BIOS_BASIC_IMPL_H

#include "ehvm_types_stdint.h"
#include <bios/ehvm_bios_basic.h>

#define BIOS_REG8RFU_NUM3 (3U)
#define BIOS_REG8RFU_NUM7 (7U)

/* read/write 8bit register */
typedef volatile unsigned char bios_reg8_t;

/* read/write 16bit register */
typedef volatile unsigned short bios_reg16_t;

/* read/write 32bit register */
typedef volatile unsigned long bios_reg32_t;

/* read-only 8bit register */
typedef EhvmConst unsigned char bios_reg8r_t;

/* read-only 16bit register */
typedef EhvmConst unsigned short bios_reg16r_t;

/* read-only 32bit register */
typedef EhvmConst unsigned long bios_reg32r_t;

/* write-only 8bit register */
typedef volatile unsigned char bios_reg8w_t;

/* write-only 16bit register */
typedef volatile unsigned short bios_reg16w_t;

/* write-only 32bit register */
typedef volatile unsigned long bios_reg32w_t;

/* inaccessible 8bit register */
typedef EhvmConst unsigned char bios_reg8rfu_t;

/* inaccessible 16bit register */
typedef EhvmConst unsigned short bios_reg16rfu_t;

/* inaccessible 32bit register */
typedef EhvmConst unsigned long bios_reg32rfu_t;

/* read/write 16bit-aligned 8bit register (later ver2.0) */
typedef struct {
    /* the most significant 8bits */
    bios_reg8_t reg8;
    /* reseved */
    bios_reg8rfu_t rfu;
} bios_reg16_8_t;

/* read only 16bit-aligned 8bit register (later ver2.0) */
typedef EhvmConstR bios_reg16_8_t bios_reg16_8r_t;

/* write only 16bit-aligned 8bit register (later ver2.0) */
typedef bios_reg16_8_t bios_reg16_8w_t;

/* read/write 32bit-aligned 8bit register (later ver2.0) */
typedef struct {
    /* the most significant 8bits */
    bios_reg8_t reg8;
    /* reseved */
    bios_reg8rfu_t rfu[BIOS_REG8RFU_NUM3];
} bios_reg32_8_t;

/* read only 32bit-aligned 8bit register (later ver2.0) */
typedef EhvmConstR bios_reg32_8_t bios_reg32_8r_t;

/* write only 32bit-aligned 8bit register (later ver2.0) */
typedef bios_reg32_8_t bios_reg32_8w_t;

/* read/write 32bit-aligned 16bit register (later ver2.0) */
typedef struct {
    /* the most significant 16bits */
    bios_reg16_t reg16;
    /* reseved */
    bios_reg16rfu_t rfu;
} bios_reg32_16_t;

/* read only 32bit-aligned 16bit register (later ver2.0) */
typedef EhvmConstR bios_reg32_16_t bios_reg32_16r_t;

/* write only 32bit-aligned 16bit register (later ver2.0) */
typedef bios_reg32_16_t bios_reg32_16w_t;

/* read/write 64bit-aligned 8bit register (later ver2.0) */
typedef struct {
    /* the most significant 8bits */
    bios_reg8_t reg8;
    /* reseved */
    bios_reg8rfu_t rfu[BIOS_REG8RFU_NUM7];
} bios_reg64_8_t;

/* read only 64bit-aligned 8bit register (later ver2.0) */
typedef EhvmConstR bios_reg64_8_t bios_reg64_8r_t;

/* write only 64bit-aligned 8bit register (later ver2.0) */
typedef bios_reg64_8_t bios_reg64_8w_t;

/* read/write 64bit-aligned 16bit register (later ver2.0) */
typedef struct {
    /* the most significant 16bits */
    bios_reg16_t reg16;
    /* reseved */
    bios_reg16rfu_t rfu[BIOS_REG8RFU_NUM3];
} bios_reg64_16_t;

/* read only 64bit-aligned 16bit register (later ver2.0) */
typedef EhvmConstR bios_reg64_16_t bios_reg64_16r_t;

/* write only 64bit-aligned 16bit register (later ver2.0) */
typedef bios_reg64_16_t bios_reg64_16w_t;

/* read/write 64bit-aligned 32bit register (later ver2.0) */
typedef struct {
    /* the most significant 32bits */
    bios_reg32_t reg32;
    /* reseved */
    bios_reg32rfu_t rfu;
} bios_reg64_32_t;

/* read only 64bit-aligned 32bit register (later ver2.0) */
typedef EhvmConstR bios_reg64_32_t bios_reg64_32r_t;

/* write only 64bit-aligned 32bit register (later ver2.0) */
typedef bios_reg64_32_t bios_reg64_32w_t;

/* boolean type for internal use */
typedef signed char bios_bool8_t;

#endif /* #ifndef EHVM_BIOS_BASIC_IMPL_H */
