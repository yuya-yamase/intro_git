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
[ mcos_v850_stack_check_ghs.inc ] - MCOS v850 stack check macro
****************************************************************************/

    .export     ar_user_config
#define OFFSET_AR_HOOK_STACKSIZE        4

    /*
     *  mk stack check
     *  input: r2  mkcb
     *  changed registers: r9
     */
    .macro  CHECK_MK_SP_RANGE   error_label
    /* stack overflow check (range) */
    ld.w    MKCB_CMN_OFFSET_5_STKBTM[r2], r9    /* stack bottom address (higher) */
    cmp     r9, sp
    bh      1f          /* sp > r3 [btm] : error */
    ld.w    MKCB_CMN_OFFSET_4_STKTOP[r2], r9    /* stack top address (lower) */
    cmp     r9, sp
    bh      2f          /* sp > r3 [top] : ok */
1:
    jr      error_label
    /* never reached */
2:
    .endm

    /*
     *  mk stack check
     *  input: r2  mkcb
     *  changed registers: r8, r9
     */
    .macro  CHECK_MK_SP_MAGIC_NUMBER    error_label
    /* stack overflow check (magic number) */
    ld.w    MKCB_CMN_OFFSET_4_STKTOP[r2], r9    /* stack top address (lower) */
    ld.w    0[r9], r9                           /* magic number of stack top */
    mov     MCOS_STACK_MAGIC, r8
    cmp     r9, r8
    be      1f
    jr      error_label
    /* never reached */
1:
    .endm

    /*
     *  mk stack check
     *  input: r2  mkcb
     *  changed registers: r8, r9
     */
    .macro  CHECK_MK_SP_HOOK_REMAINING_SIZE  error_label
    /* stack overflow check (size) */
    movhi   hi(ar_user_config), r0, r9
    movea   lo(ar_user_config), r9, r9
    ld.w    OFFSET_AR_HOOK_STACKSIZE[r9], r8    /* stack size of hook */
    ld.w    MKCB_CMN_OFFSET_4_STKTOP[r2], r9    /* stack top address (lower) */
    add     r8, r9
    cmp     r9, sp
    bh      1f              /* sp > r3 [top+hksz] : ok */
    jr      error_label
    /* never reached */
1:
    .endm

    /*
     *  mk stack check
     *  input: r2  mkcb
     *  changed registers: r8, r9
     */
    .macro  CHECK_MK_SP_MKMSG_REMAINING_SIZE  error_label
    /* stack overflow check (size) */
    mov     MCOS_AR_MKMSG_STACKSIZE, r8         /* stack size of mkmsg */
    ld.w    MKCB_CMN_OFFSET_4_STKTOP[r2], r9    /* stack top address (lower) */
    add     r8, r9
    cmp     r9, sp
    bh      1f              /* sp > r3 [top+hksz] : ok */
    jr      error_label
    /* never reached */
1:
    .endm
