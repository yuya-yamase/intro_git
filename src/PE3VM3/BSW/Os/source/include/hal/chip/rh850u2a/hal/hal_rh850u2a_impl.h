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
[ hal_rh850u2a_impl.h ] - HAL RH850U2A implementation header
****************************************************************************/
#ifndef HAL_RH850U2A_IMPL_H
#define HAL_RH850U2A_IMPL_H

#include <hal/hal_impl.h>
#include <hal/cpu/v850/hal/hal_v850_cpp_impl.h>
#include <hal/cpu/v850/hal/hal_v850_impl.h>
#include <hal/chip/rh850u2a/rh850u2a_impl.h>


#define OS_START_SEC_CODE
#include "Os_MemMap.h"

/*-------------------------------------------------------------------------
 interrupt
-------------------------------------------------------------------------*/
#define INT_NO_MIN_INTC1    ((hal_uint32_t)RH850U2A_INTC1_INTNO_MIN)
#define INT_NO_MAX_INTC1    ((hal_uint32_t)RH850U2A_INTC1_INTNO_MAX)
#define INT_NUM_INTC1       ((hal_uint32_t)RH850U2A_INTC1_NUM)
#define INT_NO_MIN_INTC2    ((hal_uint32_t)RH850U2A_INTC2_INTNO_MIN)
#define INT_NO_MAX_INTC2    ((hal_uint32_t)RH850U2A_INTC2_INTNO_MAX)
#define INT_NUM_INTC2       ((hal_uint32_t)RH850U2A_INTC2_NUM)

/* EEIC: Interrupt priority mask */
#define REG_EEIC_EIP_MASK       0x003fUL
/* EEIC: Interrupt mask */
#define REG_EEIC_EIMK           0x0080UL

/* EEIC: Interrupt table */
#define REG_EEIC_EITB           0x0040U

#define REG_EEIC_EITB_MASK      0x0040U

/* EEIC: Interrupt request flag */
#define REG_EEIC_EIRF           0x0010UL

/* IBDxx PEID */
#define IBD_GM_MASK             ((hal_uint32_t)0x00008000U)
#define IBD_GPID_MASK           ((hal_uint32_t)0x00000700U)
#define IBD_PEID_MASK           ((hal_uint32_t)0x00000007U)
#define IBD_BITPOS_GPID         (16U)

typedef union
{
    hal_reg16_t        reg16;
    struct
    {
        hal_reg8_t     reg8_l;     /* +0 */
        hal_reg8_t     reg8_h;     /* +1 */
    } byte;
} uni_reg16_t;

typedef union
{
    hal_reg32_t        reg32;
    struct
    {
        hal_reg16_t    reg16_l;    /* +0 */
        hal_reg16_t    reg16_h;    /* +1 */
    } byte16;
    struct
    {
        hal_reg8_t     reg8_0;     /* +0 */
        hal_reg8_t     reg8_1;     /* +1 */
        hal_reg8_t     reg8_2;     /* +2 */
        hal_reg8_t     reg8_3;     /* +3 */
    } byte8;
} uni_reg32_t;

#define REF_IC1_PAD1    ((hal_uint32_t)0x0F0)   /* IMR0   */
#define REF_IC1_PAD2    ((hal_uint32_t)0x100)   /* EIBD   */
#define REF_IC1_PAD3    ((hal_uint32_t)0x1C0)   /* FIBD   */
#define REF_IC1_PAD4    ((hal_uint32_t)0x200)   /* EEIC   */
#define REF_IC1_PAD5    ((hal_uint32_t)0x280)   /* EIBG   */
#define REF_IC1_PAD6    ((hal_uint32_t)0x2C0)   /* FIBG   */
#define REF_IC1_PAD7    ((hal_uint32_t)0x2F0)   /* IHVCFG */

typedef struct hal_rh850u2a_intc_regfile
{
    /* EIC  (+ 0x000) */
    uni_reg16_t eic_[(INT_NUM_INTC1)];
    /* reserved */
    const hal_reg8_t rsv0[(REF_IC1_PAD1 - ( sizeof(hal_reg16_t) * INT_NUM_INTC1 ))];
    /* IMR0 (+ 0x0F0) */
    hal_reg32_t imr0;
    /* reserved */
    const hal_reg8_t rsv1[(REF_IC1_PAD2 - sizeof(hal_reg32_t) - REF_IC1_PAD1)];
    /* EIBD (+ 0x100) */
    hal_reg32_t eibd_[INT_NUM_INTC1];
    /* reserved */
    const hal_reg8_t rsv2[(REF_IC1_PAD3 - ( sizeof(hal_reg32_t) * INT_NUM_INTC1 ) - REF_IC1_PAD2)];
    /* FIBD (+ 0x1C0) */
    hal_reg32_t fibd;
    /* reserved */
    const hal_reg8_t rsv3[(REF_IC1_PAD4 - sizeof(hal_reg32_t) - REF_IC1_PAD3)];
    /* EEIC (+ 0x200) */
    uni_reg32_t eeic_[INT_NUM_INTC1];
    /* EIBG (+ 0x280) */
    hal_reg32_t eibg;
    /* reserved */
    const hal_reg8_t rsv5[(REF_IC1_PAD6 - sizeof(hal_reg32_t) - REF_IC1_PAD5)];
    /* FIBG (+ 0x2C0) */
    hal_reg32_t figb;
    /* reserved */
    const hal_reg8_t rsv6[(REF_IC1_PAD7 - sizeof(hal_reg32_t) - REF_IC1_PAD6)];
    /* IHVCFG (+ 0x2F0) */
    uni_reg32_t ihvcfg;
} hal_rh850u2a_intc_regfile_t;

#define INTC_EEIC(regfile, intno)           ((regfile)->eeic_[intno].reg32)
#define INTC_EEIC_ADDR(regfile, intno)      (&((regfile)->eeic_[intno].reg32))

#define INTC_EEIC_L(regfile, intno)         ((regfile)->eeic_[intno].byte16.reg16_l)
#define INTC_EEIC_H(regfile, intno)         ((regfile)->eeic_[intno].byte16.reg16_h)
#define INTC_EEIC_L_ADDR(regfile, intno)    (&((regfile)->eeic_[intno].byte16.reg16_l))
#define INTC_EEIC_H_ADDR(regfile, intno)    (&((regfile)->eeic_[intno].byte16.reg16_h))

#define INTC_EEIC_BYTE8_0(regfile, intno)       ((regfile)->eeic_[intno].byte8.reg8_0)
#define INTC_EEIC_BYTE8_1(regfile, intno)       ((regfile)->eeic_[intno].byte8.reg8_1)
#define INTC_EEIC_BYTE8_2(regfile, intno)       ((regfile)->eeic_[intno].byte8.reg8_2)
#define INTC_EEIC_BYTE8_3(regfile, intno)       ((regfile)->eeic_[intno].byte8.reg8_3)
#define INTC_EEIC_BYTE8_0_ADDR(regfile, intno)  (&((regfile)->eeic_[intno].byte8.reg8_0))
#define INTC_EEIC_BYTE8_1_ADDR(regfile, intno)  (&((regfile)->eeic_[intno].byte8.reg8_1))
#define INTC_EEIC_BYTE8_2_ADDR(regfile, intno)  (&((regfile)->eeic_[intno].byte8.reg8_2))
#define INTC_EEIC_BYTE8_3_ADDR(regfile, intno)  (&((regfile)->eeic_[intno].byte8.reg8_3))

#define REF_IC2_PAD1    ((hal_uint32_t)0x1000)   /* IMR    */
#define REF_IC2_PAD2    ((hal_uint32_t)0x1FE0)   /* I2EIBG */
#define REF_IC2_PAD3    ((hal_uint32_t)0x2000)   /* EIBD   */
#define REF_IC2_PAD4    ((hal_uint32_t)0x4000)   /* EEIC   */

#define REF_IMR_NUM      (23UL)
#define REF_I2EIBG_NUM    (4UL)

typedef struct hal_rh850u2a_intc32_regfile
{
    /* offset EIC (+ 0x040) */
    const hal_reg8_t offset0[( sizeof(hal_reg16_t) * INT_NUM_INTC1 )];
    /* EIC (+ 0x040) */
    uni_reg16_t eic32_[INT_NUM_INTC2];
    /* reserved */
    const hal_reg8_t rsv0[REF_IC2_PAD1 - ( sizeof(hal_reg16_t) * (INT_NUM_INTC2 + INT_NUM_INTC1) )];
    /* IMR (+ 0x1000) */
    uni_reg32_t imr1_23[REF_IMR_NUM];
    /* reserved */
    const hal_reg8_t rsv1[REF_IC2_PAD2 - ( sizeof(hal_reg32_t) * REF_IMR_NUM ) - REF_IC2_PAD1];
    /* I2EIBG (+ 0x1FE0) */
    uni_reg32_t i2eibg_[REF_I2EIBG_NUM];
    /* reserved */
    const hal_reg8_t rsv2[REF_IC2_PAD3 - ( sizeof(hal_reg32_t) * REF_I2EIBG_NUM ) - REF_IC2_PAD2];
    /* EIBD (+ 0x2000) */
    /* EIBD Offset(+ 0x0080) */
    const hal_reg8_t offset1[( sizeof(hal_reg32_t) * INT_NUM_INTC1 )];
    hal_reg32_t eibd32_[INT_NUM_INTC2];
    /* reserved */
    const hal_reg8_t rsv3[REF_IC2_PAD4 - ( sizeof(hal_reg32_t) * (INT_NUM_INTC2 + INT_NUM_INTC1) ) - REF_IC2_PAD3];
    /* EEIC (+ 0x4000) */
    /* EEIC Offset(+ 0x0080) */
    const hal_reg8_t offset2[( sizeof(hal_reg32_t) * INT_NUM_INTC1 )];
    uni_reg32_t eeic32_[INT_NUM_INTC2];
} hal_rh850u2a_intc32_regfile_t;

#define INTC32_EEIC(regfile, intno)         ((regfile)->eeic32_[(hal_uint32_t)(intno) - (hal_uint32_t)INT_NUM_INTC1].reg32)
#define INTC32_EEIC_ADDR(regfile, intno)    (&((regfile)->eeic32_[(hal_uint32_t)(intno) - (hal_uint32_t)INT_NUM_INTC1].reg32))

#define INTC32_EEIC_L(regfile, intno)       ((regfile)->eeic32_[(hal_uint32_t)(intno) - (hal_uint32_t)INT_NUM_INTC1].byte16.reg16_l)
#define INTC32_EEIC_H(regfile, intno)       ((regfile)->eeic32_[(hal_uint32_t)(intno) - (hal_uint32_t)INT_NUM_INTC1].byte16.reg16_h)
#define INTC32_EEIC_L_ADDR(regfile, intno)  (&((regfile)->eeic32_[(hal_uint32_t)(intno) - (hal_uint32_t)INT_NUM_INTC1].byte16.reg16_l))
#define INTC32_EEIC_H_ADDR(regfile, intno)  (&((regfile)->eeic32_[(hal_uint32_t)(intno) - (hal_uint32_t)INT_NUM_INTC1].byte16.reg16_h))

#define INTC32_EEIC_BYTE8_0(regfile, intno)         ((regfile)->eeic32_[(hal_uint32_t)(intno) - (hal_uint32_t)INT_NUM_INTC1].byte8.reg8_0)
#define INTC32_EEIC_BYTE8_1(regfile, intno)         ((regfile)->eeic32_[(hal_uint32_t)(intno) - (hal_uint32_t)INT_NUM_INTC1].byte8.reg8_1)
#define INTC32_EEIC_BYTE8_2(regfile, intno)         ((regfile)->eeic32_[(hal_uint32_t)(intno) - (hal_uint32_t)INT_NUM_INTC1].byte8.reg8_2)
#define INTC32_EEIC_BYTE8_3(regfile, intno)         ((regfile)->eeic32_[(hal_uint32_t)(intno) - (hal_uint32_t)INT_NUM_INTC1].byte8.reg8_3)
#define INTC32_EEIC_BYTE8_0_ADDR(regfile, intno)    (&((regfile)->eeic32_[(hal_uint32_t)(intno) - (hal_uint32_t)INT_NUM_INTC1].byte8.reg8_0))
#define INTC32_EEIC_BYTE8_1_ADDR(regfile, intno)    (&((regfile)->eeic32_[(hal_uint32_t)(intno) - (hal_uint32_t)INT_NUM_INTC1].byte8.reg8_1))
#define INTC32_EEIC_BYTE8_2_ADDR(regfile, intno)    (&((regfile)->eeic32_[(hal_uint32_t)(intno) - (hal_uint32_t)INT_NUM_INTC1].byte8.reg8_2))
#define INTC32_EEIC_BYTE8_3_ADDR(regfile, intno)    (&((regfile)->eeic32_[(hal_uint32_t)(intno) - (hal_uint32_t)INT_NUM_INTC1].byte8.reg8_3))

#define INTC32_EIBD(regfile, intno)         ((regfile)->eibd32_[(hal_uint32_t)(intno) - (hal_uint32_t)INT_NUM_INTC1])


#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"


#define OS_START_SEC_CODE
#include "Os_MemMap.h"

/* set EIBD for INTC2 */
void hal_rh850u2a_intc32_setEIBD(
    hal_rh850u2a_intc32_regfile_t * const regfile,
    const hal_int_t intno,
    const hal_uint32_t value);

/* enable an interrupt for 'intno' */
void hal_rh850u2a_intc_enableInt(
    hal_rh850u2a_intc_regfile_t * const regfile,
    const hal_int_t intno);

/* disable an interrupt for 'intno' */
void hal_rh850u2a_intc_disableInt(
    hal_rh850u2a_intc_regfile_t * const regfile,
    const hal_int_t intno);

/* clear an asserted interrupt for 'intno' */
void hal_rh850u2a_intc_clearInt(
    hal_rh850u2a_intc_regfile_t * const regfile,
    const hal_int_t intno);

/* clear an pending interrupt for 'intno' */
void hal_rh850u2a_intc_clearPendingInt(
    hal_rh850u2a_intc_regfile_t * const regfile,
    const hal_int_t intno);

/* is an interrupt for 'intno' enabled ? */
hal_bool_t hal_rh850u2a_intc_isIntEnabled(
    hal_rh850u2a_intc_regfile_t const * const regfile,
    const hal_int_t intno);

/* set a 'priority' for an interrupt for 'intno' */
void hal_rh850u2a_intc_setIntPriority(
    hal_rh850u2a_intc_regfile_t * const regfile,
    const hal_int_t intno,
    const hal_int_t priority);

hal_bool_t hal_rh850u2a_intc_checkEEIC(
    hal_rh850u2a_intc_regfile_t const * const regfile,
    const hal_int_t intno,
    const hal_int_t priority);

/* enable an interrupt for 'intno' */
void hal_rh850u2a_intc32_enableInt(
    hal_rh850u2a_intc32_regfile_t * const regfile,
    const hal_int_t intno);

/* disable an interrupt for 'intno' */
void hal_rh850u2a_intc32_disableInt(
    hal_rh850u2a_intc32_regfile_t * const regfile,
    const hal_int_t intno);

/* clear an asserted interrupt for 'intno' */
void hal_rh850u2a_intc32_clearInt(
    hal_rh850u2a_intc32_regfile_t * const regfile,
    const hal_int_t intno);

/* clear an pending interrupt for 'intno' */
void hal_rh850u2a_intc32_clearPendingInt(
    hal_rh850u2a_intc32_regfile_t * const regfile,
    const hal_int_t intno);

/* is an interrupt for 'intno' enabled ? */
hal_bool_t hal_rh850u2a_intc32_isIntEnabled(
    hal_rh850u2a_intc32_regfile_t const * const regfile,
    const hal_int_t intno);

/* set a 'priority' for an interrupt for 'intno' */
void hal_rh850u2a_intc32_setIntPriority(
    hal_rh850u2a_intc32_regfile_t * const regfile,
    const hal_int_t intno,
    const hal_int_t priority);

hal_bool_t hal_rh850u2a_intc32_checkEEIC(
    hal_rh850u2a_intc32_regfile_t const * const regfile,
    const hal_int_t intno,
    const hal_int_t priority);

hal_bool_t hal_rh850u2a_intc32_checkEIBD(
    hal_rh850u2a_intc32_regfile_t const * const regfile,
    const hal_int_t intno,
    const hal_uint32_t value);

/*-------------------------------------------------------------------------
 RH850U2A
-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------
 BARRIER
-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------
 OSTM
-------------------------------------------------------------------------*/
/*
 * OS Timer register
 */
typedef struct hal_rh850u2a_ostm_regfile
{
    hal_reg32_t cmp;                   /* [+0x00] */
    hal_reg32_t cnt;                   /* [+0x04] */
    hal_reg8_t to;                     /* [+0x08] */
    const hal_uint8_t rsv_009[3];      /* [+0x09] */
    hal_reg8_t toe;                    /* [+0x0C] */
    const hal_uint8_t rsv_00d[3];      /* [+0x0D] */
    hal_reg8_t te;                     /* [+0x10] */
    const hal_uint8_t rsv_011[3];      /* [+0x11] */
    hal_reg8_t ts;                     /* [+0x14] */
    const hal_uint8_t rsv_015[3];      /* [+0x15] */
    hal_reg8_t tt;                     /* [+0x18] */
    const hal_uint8_t rsv_019[7];      /* [+0x19] */
    hal_reg8_t ctl;                    /* [+0x20] */
} hal_rh850u2a_ostm_regfile_t;

/* open OSTM */
void hal_rh850u2a_ostm_open(
    hal_rh850u2a_ostm_regfile_t * const ostm,
        hal_uint32_t interval);

/* close OSTM */
void hal_rh850u2a_ostm_close(
    hal_rh850u2a_ostm_regfile_t * const ostm);


/*-------------------------------------------------------------------------
 Register protection
-------------------------------------------------------------------------*/
static inline void hal_rh850u2a_write_protreg(hal_reg32_t * const regaddr,
    hal_reg32_t * const cmd_regaddr, const hal_uint32_t val);

/*-------------------------------------------------------------------------
  hal_rh850u2a_write_protreg
     write to protected register
  Input     :   regaddr         protected register address
  Input     :   cmd_regaddr     protection command register address
  Input     :   sts_regaddr     protection status register address
  Input     :   val             write data
  Return    :   none
  Note  :   none
-------------------------------------------------------------------------*/
static inline void hal_rh850u2a_write_protreg(
    hal_reg32_t * const regaddr,
    hal_reg32_t * const cmd_regaddr,
    const hal_uint32_t val)
{
        /* step-1: write 0xa5a5a501 to protection command register */
        *cmd_regaddr = 0xa5a5a501UL;

        /* step-2: write val to protected register */
        *regaddr = val;

        /* step-3: write 0xa5a5a500 to protection command register */
        *cmd_regaddr = 0xa5a5a500UL;

}

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#endif /* #ifndef HAL_RH850U2A_IMPL_H */
