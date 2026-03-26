/*
    Copyright(C) 2021 eSOL Co., Ltd. All rights reserved.

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
[ mcos_v850_local_ghs.inc ] - eMCOS AUTOSAR hardware layer internal header for v850 (ASM)
****************************************************************************/
#ifndef MCOS_V850_LOCAL_GHS_INC
#define MCOS_V850_LOCAL_GHS_INC

#include "Os_Cfg_base.h"

#define _in_asm_source_

    .import _haldata_mcos_v850

#define STD_OFF                             0
#define STD_ON                              1

#define PRO_IGNORE                          0

    /*
     *  stack frame format:
     *
     *       interrupt
     *       stack frame
     *
     *          -notda
     *          -sda=0
     *
     *       +-----------+
     *     0 |plmr       |
     *     4 |ctpsw      |
     *     8 |ctpc       |
     *    12 |fpsr       |
     *    16 |eipsw/fepsw|
     *    20 |eipc/fepc  |
     *    24 |r19        |
     *    28 |r18        |
     *    32 |r17        |
     *    36 |r16        |
     *    40 |r15        |
     *    44 |r14        |
     *    48 |r13        |
     *    52 |r12        |
     *    56 |r11        |
     *    60 |r10        |
     *    64 |r9         |
     *    68 |r8         |
     *    72 |r7         |
     *    76 |r6         |     no r4-r5 -sda=0
     *    80 |r31(lp)    |
     *    84 |r30(ep)    |     -notda
     *  (88) |r19        |     SC3 only
     *  (92) |r18        |     SC3 only
     *88(96) |r1         |     SC1 (SC3)
     *       +-----------+
     */

#if defined(__ghs_sda)
#define REGS1   r6 - r19
#else
#define REGS1   r4 - r19    /* Now not supported. */
#endif

#if !defined(__ghs_tda)
#define REGS2   ep - lp
#else
#define REGS2   lp - lp     /* Now not supported. */
#endif

    /*
     *  save all registers to interrupt stack frame
     *
     *  should be used at the beggining of interrupt handler
     *  used registers: r12-r17
     *  ATTENTION! r1 is NOT saved. Save r1 before call this macro.
     */

    .macro  INTERRUPT_SAVE_REGS_EI
    /* push general registers */
    pushsp  REGS2
    pushsp  REGS1

    /* push special registers */
    stsr    eipc, r12, 0
    stsr    eipsw, r13, 0

    stsr    fpsr, r14, 0
    stsr    ctpc, r15, 0
    stsr    ctpsw, r16, 0

    stsr    14, r17, 2          /* r17 <- PLMR */
    pushsp  r12 - r17
    /* When an interrupt happened, PSW.ID is 1. */
    movhi   hi(_haldata_mcos_v850), r0, r10
    movea   lo(_haldata_mcos_v850), r10, r10
    ld.w    0[r10], r10
    ldsr    r10, 14, 2    /* PLMR */
    .endm


    .macro  INTERRUPT_SAVE_REGS_FE
    /* push general registers */
    pushsp  REGS2
    pushsp  REGS1

    /* push special registers */
    stsr    fepc, r12, 0
    stsr    fepsw, r13, 0

    stsr    fpsr, r14, 0
    stsr    ctpc, r15, 0
    stsr    ctpsw, r16, 0

    stsr    14, r17, 2    /* PLMR */
    pushsp  r12 - r17
    /* When an interrupt happened, PSW.ID is 1. */
    movhi   hi(_haldata_mcos_v850), r0, r10
    movea   lo(_haldata_mcos_v850), r10, r10
    ld.w    0[r10], r10
    ldsr    r10, 14, 2    /* PLMR */
    .endm


    /*
     *  restore all registers from interrupt stack frame
     *
     *  should be used at the end of interrupt handler
     *  used registers: none (all registers are restored from stack)
     *  ATTENTION! r1 is restored.
     */

    .macro  INTERRUPT_RESTORE_REGS_EI
    /* discard frame info */

    /* restore special registers */
    popsp   r12 - r17
    ldsr    r17, 14, 2    /* PLMR */

    /* restore special registers */
    ldsr    r12, eipc, 0
    ldsr    r13, eipsw, 0
    syncp   /* Resolve for System register hazard */
    synce   /* Resolve for System register hazard */
    ldsr    r14, fpsr, 0
    syncp   /* Resolve for System register hazard */
    ldsr    r15, ctpc, 0
    ldsr    r16, ctpsw, 0

    /* restore general registers */
    popsp   REGS1
    popsp   REGS2
    .endm


    .macro  INTERRUPT_RESTORE_REGS_FE
    /* discard frame info */

    /* restore special registers */
    di
    popsp   r12 - r17
    ldsr    r17, 14, 2    /* PLMR */

    /* restore special registers */
    ldsr    r12, fepc, 0
    ldsr    r13, fepsw, 0
    syncp   /* Resolve for System register hazard */
    synce   /* Resolve for System register hazard */
    ldsr    r14, fpsr, 0
    syncp   /* Resolve for System register hazard */
    ldsr    r15, ctpc, 0
    ldsr    r16, ctpsw, 0

    /* restore general registers */
    popsp   REGS1
    popsp   REGS2
    .endm

/*
    typedef struct mkcb_cmn_st
    {
        mcos_uintptr_t *psp;         # offset 0
        uint16_t inest;              # offset 1
        mcos_id_t lcid;              # offset 2
        clscb_t * cls;               # offset 3 <- clscb is here
        ...
    }
 */
#define MKCB_CMN_OFFSET_0_PSP       (0)
#define MKCB_CMN_OFFSET_1_INEST     (4)
#define MKCB_CMN_OFFSET_2_LCID      (6)
#define MKCB_CMN_OFFSET_3_CLS       (8)
#define MKCB_CMN_OFFSET_4_STKTOP    (12)
#define MKCB_CMN_OFFSET_5_STKBTM    (16)

/*
    struct clscb_st
    {
        tcb_t *running;
        tcb_t *ready;
        tcb_t *wait;
        tcb_t *dormant;
        tcb_t *nonexist;
    #if !MCOS_AUTOSAR
        tcb_t *suspended;
    #endif
        mcos_uintptr_t sp;
 */
#define CLSCB_ST_OFFSET_0_RUNNING               0
#define CLSCB_ST_OFFSET_1_READY                 4
#define CLSCB_ST_OFFSET_2_WAIT                  8
#define CLSCB_ST_OFFSET_3_DORMANT               12
#define CLSCB_ST_OFFSET_4_NONEXIST              16
#define CLSCB_ST_OFFSET_8_CTX                   28
#define CLSCB_ST_OFFSET_X_AROSCB_CURRENT_OSAP   88
#define CLSCB_ST_OFFSET_X_OSARCH_SP             (100)
#define CLSCB_ST_OFFSET_X_OSARCH_CHK_SP_ADDR    (104)
#define CLSCB_ST_OFFSET_X_OSARCH_CHK_SP_SIZE    (108)
#define CLSCB_ST_OFFSET_X_OSARCH_INT_MNG_CNT    (112)

/* Offset of clscb.sp from mkcb */
#define MKCB_CMN_OFFSET_X_CLSCB     (36)
#define MKCB_CMN_OFFSET_X_CLS_SP    (MKCB_CMN_OFFSET_X_CLSCB + 20)
#define MKCB_CMN_OFFSET_X_CLS_OSARCH_SP    \
    (MKCB_CMN_OFFSET_X_CLSCB + CLSCB_ST_OFFSET_X_OSARCH_SP)
#define MKCB_CMN_OFFSET_X_CLS_OSARCH_CHK_SP_ADDR    \
    (MKCB_CMN_OFFSET_X_CLSCB + CLSCB_ST_OFFSET_X_OSARCH_CHK_SP_ADDR)
#define MKCB_CMN_OFFSET_X_CLS_OSARCH_CHK_SP_SIZE    \
    (MKCB_CMN_OFFSET_X_CLSCB + CLSCB_ST_OFFSET_X_OSARCH_CHK_SP_SIZE)
#define MKCB_CMN_OFFSET_X_CLS_OSARCH_INT_MNG_CNT    \
    (MKCB_CMN_OFFSET_X_CLSCB + CLSCB_ST_OFFSET_X_OSARCH_INT_MNG_CNT)
#define MKCB_CMN_OFFSET_X_AROSCB_CURRENT_OSAP   \
    (MKCB_CMN_OFFSET_X_CLSCB + CLSCB_ST_OFFSET_X_AROSCB_CURRENT_OSAP)

/*
    typedef struct tcb_st
    {
    2   mcos_id_t tid;
    2   mcos_id_t tid_af;
    4   void *stack;
    4   struct tcb_st *next;
        migratable_tcb_t migratable;
        mcos_uintptr_t sp;
    } tcb_t;
 */

/*
    typedef struct
    {
        uint32_t state      :   2;
    1   uint32_t flags      :   6;
    1   uint32_t attr       :   8;
    1   uint32_t wupcnt     :   8;
    1   uint32_t prinest    :   8;
    } tcb_attr_state_t;

    typedef struct
    {
    4    tcb_attr_state_t attr_state;
    1    uint8_t bpri;
    1    uint8_t cpri;
    1    uint8_t actcnt;
    1    uint8_t maxact;
    4    void (*entry)(const uint32_t, const mcos_uintptr_t);
    4    mcos_uintptr_t *stkaddr;
    4    uint32_t stksz;
    4    void *rep;
    4    mcos_uintptr_t exinf;
    } migratable_tcb_t;
 */
#define TCB_ST_OFFSET_0_TID        (0)
#define TCB_ST_OFFSET_1_TID_AF     (2)
#define TCB_ST_OFFSET_2_STACK      (4)
#define TCB_ST_OFFSET_2_NEXT       (8)
#define TCB_ST_OFFSET_3_MIGRATABLE (12)
#define TCB_ST_OFFSET_4_SP         (40)

#define MIGRATABLE_ST_STKADDR      (12)
#define MIGRATABLE_ST_STKSZ        (16)

#define MKCB_CMN_OFFSET_X_CLS_0_RUNNING    \
    (MKCB_CMN_OFFSET_X_CLSCB + CLSCB_ST_OFFSET_0_RUNNING)

#define TCB_OFFSET_X_MIGRATABLE_STKADDR    \
    (TCB_ST_OFFSET_3_MIGRATABLE + MIGRATABLE_ST_STKADDR)
#define TCB_OFFSET_X_MIGRATABLE_STKSZ    \
    (TCB_ST_OFFSET_3_MIGRATABLE + MIGRATABLE_ST_STKSZ)


/*
struct ar_osap_config_st {
    4 osap_startup_hook_func_t    startup_hook;
    4 osap_shutdown_hook_func_t   shutdown_hook;
    4 osap_error_hook_func_t      error_hook;
#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)
    4 ar_tcb_t        *p_restart_tcb;
    4 uint32          osap_bitmask;
    1 boolean         osap_trusted;
    1 boolean         osap_protected;
    1 boolean         osap_terminatable;
    1 --
#endif
#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) || (AR_OS_USE_MULTICORE == STD_ON)
    4 ar_osapcb_t     *p_osapcb;
#endif
    1 ApplicationType osap_id;
    1 --
    2 mcos_id_t lcid;
};
*/

#define OSAPCONFIG_OFFSET_OSAP_ID       28

#define MCOS_V850_CONTEXT_SWITCH_OFF (0)
#define MCOS_V850_CONTEXT_SWITCH_ON  (1)


 /*---------------------------------------------------------------------------
  ENABLE_MEMORY_PROTECTION_IF_NECESSARY
     Enable memory protection
  Input     :   reg         previous MPU_MPM_MPE register value
  Output    :   none
  Note  :  use reg registers, SVLOCK ON!
 ---------------------------------------------------------------------------*/
    .macro  ENABLE_MEMORY_PROTECTION_IF_NECESSARY reg
    cmp     r0, reg
    be      1f

    /* Enable Memory Protection */
    ldsr    zero, svlock, 1             /* lock off */
    synci
    stsr    mpm, reg, 5
    ori     MPU_MPM_MPE_MASK, reg, reg
    ldsr    reg, mpm, 5
    synci
1:
    mov     SVLOCK_SVL, reg
    ldsr    reg, svlock, 1              /* lock on */
    synci
    .endm

 /*---------------------------------------------------------------------------
  DISABLE_MEMORY_PROTECTION_IF_NECESSARY
     Disable memory protection
  Input     :   none
  Output    :   out         previous MPU_MPM_MPE register value
  Note  :  use tmp, out registers, SVLOCK ON!
 ---------------------------------------------------------------------------*/
    .macro  DISABLE_MEMORY_PROTECTION_IF_NECESSARY out, tmp
    stsr    mpm, tmp, 5
    andi    MPU_MPM_MPE_MASK, tmp, out  /* out = 0 or MPU_MPM_MPE_MASK */
    be      1f

    ldsr    zero, svlock, 1             /* lock off */
    synci
    not     out, out                    /* out = ~MPU_MPM_MPE_MASK */
    and     out, tmp                    /* tmp = new MPM */
    ldsr    tmp, mpm, 5                 /* The MPE bit is cleared only in the kernel */
    synci
    mov     MPU_MPM_MPE_MASK, out       /* previous memory protection: enabled */
1:
    mov     SVLOCK_SVL, tmp
    ldsr    tmp, svlock, 1              /* lock on */
    synci

    .endm


 /*---------------------------------------------------------------------------
  ENABLE_MEMORY_PROTECTION
     Enable memory protection
  Input     :   none
  Output    :   none
  Note  :  use tmp registers, SVLOCK ON!
 ---------------------------------------------------------------------------*/
    .macro  ENABLE_MEMORY_PROTECTION tmp
    /* Enable Memory Protection */
    ldsr    zero, svlock, 1             /* lock off */
    synci
    stsr    mpm, tmp, 5
    ori     MPU_MPM_MPE_MASK, tmp, tmp
    ldsr    tmp, mpm, 5                 /* the MPE bit is set */
    synci
    mov     SVLOCK_SVL, tmp
    ldsr    tmp, svlock, 1              /* lock on */
    synci
    .endm


 /*---------------------------------------------------------------------------
  DISABLE_MEMORY_PROTECTION
     Disable memory protection
  Input     :   none
  Output    :   out         previous MPM register value
  Note  :  use tmp, out registers, SVLOCK ON!
 ---------------------------------------------------------------------------*/
    .macro  DISABLE_MEMORY_PROTECTION   out, tmp
    /* Allow full access in the kernel */
    ldsr    zero, svlock, 1             /* lock off */
    synci
    mov     MPU_MPM_MPE_MASK, tmp
    not     tmp, tmp
    stsr    mpm, out, 5
    and     out, tmp
    ldsr    tmp, mpm, 5                 /* The MPE bit is cleared in the kernel */
    synci
    mov     SVLOCK_SVL, tmp
    ldsr    tmp, svlock, 1              /* lock on */
    synci
    .endm


.macro EI_RETURN
#if AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON
    jmp     mcos_v850_ei_return[r0]
#else /* #if AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON */
    popsp   r1
    eiret
#endif /* #if AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON */
.endm

.macro FE_RETURN
#if AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON
    jmp     mcos_v850_fe_return[r0]
#else /* #if AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON */
    popsp   r1
    feret
#endif /* #if AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON */
.endm

.macro SPCHK_EXC    Usage
.macrolocal     L_chk, L_err, L_ok

    /* r20 - r22 have already pushed */

    /* r2 <- mkcb */
    movhi   hi(_mcos_mkcb_ptr_table), r0, r20
    movea   lo(_mcos_mkcb_ptr_table), r20, r20
    stsr    0, r21, 2   /* Get PEID */
    shl     2, r21
    add     r21, r20
    ld.w    0[r20], r2

    /***********************************************************
     * Stack Range Check
     ***********************************************************/

    ld.hu   MKCB_CMN_OFFSET_1_INEST[r2], r20                /* load inest */

    /* r2 = mkcb, r20=inest */

    cmp     0, r20
    bne     1f

    /** task stack **/
    ld.w    MKCB_CMN_OFFSET_X_CLS_0_RUNNING[r2], r22        /* Get Running Task's TCB */
    ld.w    TCB_OFFSET_X_MIGRATABLE_STKADDR[r22], r20       /* Get Stack Address */
    ld.w    TCB_OFFSET_X_MIGRATABLE_STKSZ[r22], r21         /* Get Stack Size */
    add     r20, r21                                        /* uppder limit */
    br      L_chk

1:
    /* osap/system stack */

    ld.w    MKCB_CMN_OFFSET_0_PSP[r2], r20                  /* Load current stack information */
    addi    MKCB_CMN_OFFSET_X_CLS_SP, r2, r21               /* Load system sp address */

    cmp     r20, r21
    bne     2f

    /** system stack **/
    ld.w    MKCB_CMN_OFFSET_4_STKTOP[r2], r20          /* Get Stack Lower Address */
    ld.w    MKCB_CMN_OFFSET_5_STKBTM[r2], r21          /* Get Stack Upper Address */
    br      L_chk

2:
    /** osap stack **/
    /* r20 = pointer to ar_osapcb_st.osap_sp */
    ld.w    -4[r20], r22                                    /* r22 = ar_osapcb_t.p_config */
    ld.bu   OSAPCONFIG_OFFSET_OSAP_ID[r22], r22             /* Get OSAP Id */
    shl     3, r22                                          /* x8 */
    movhi   hi(_ar_osap_stack_table), r0, r21
    movea   lo(_ar_osap_stack_table), r21, r21
    add     r21, r22
    ld.w    0[r22], r20                                      /* Get Stack Lower Address */
    ld.w    4[r22], r21                                      /* Get Stack Size */
    add     r20, r21                                         /* uppder limit */

L_chk:
    /* r20: lower, r21: upper */
    /* sp check */

    movhi   hi(Usage), r0, r22
    movea   lo(Usage), r22, r22
    ld.w    0[r22], r22
    add     r22, r20                                        /* lower limit */

    addi    12, sp, r22                                     /* exclude pushed 3 registers */
    cmp     r22, r20
    bh      L_err       /* sp < r20 */
    cmp     r22, r21                                         /* upper limit */
    bnl     L_ok        /* sp <= r21 == not (sp > r21) */

L_err:
    jmp     _mcos_hwl_mk_sp_error [r0]

L_ok:
    popsp   r20 - r22                                       /* pushed genereated code */

.endm


.macro SPCHK_SWITCH_INT
.macrolocal     L_err, L_ok

    /***********************************************************
     * Stack Range Check
     ***********************************************************/

    ld.hu   MKCB_CMN_OFFSET_1_INEST[r2], r18                /* load inest */

    /* r2 = mkcb, r18=inest */

    cmp     0, r18
    bne     L_ok                                            /* from idle */

    /** task stack **/
    ld.w    MKCB_CMN_OFFSET_X_CLS_0_RUNNING[r2], r17        /* Get Running Task's TCB */
    ld.w    TCB_OFFSET_X_MIGRATABLE_STKADDR[r17], r18       /* Get Stack Address */
    ld.w    TCB_OFFSET_X_MIGRATABLE_STKSZ[r17], r19         /* Get Stack Size */
    add     r18, r19                                        /* uppder limit */

    movhi   hi(_mcos_stack_check_switch_int), r0, r17
    movea   lo(_mcos_stack_check_switch_int), r17, r17
    ld.w    0[r17], r17
    add     r17, r18

    /* r18: lower, r19: upper */
    /* sp check */
    cmp     sp, r18
    bh      L_err       /* sp < r18 */
    cmp     sp, r19                             /* upper limit */
    bnl     L_ok        /* sp <= r19 == not (sp > r19) */

L_err:
    jmp     _mcos_hwl_mk_sp_error [r0]

L_ok:

.endm

#endif /* #ifndef MCOS_V850_LOCAL_GHS_INC */
