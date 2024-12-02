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
[ ehvm_bios_dep_impl.h ] - BIOS RH850/U2A implementation header
****************************************************************************/
#ifndef EHVM_BIOS_DEP_IMPL_H
#define EHVM_BIOS_DEP_IMPL_H

#include <bios/chip/rh850/ehvm_chip_impl.h>
#include <bios/cpu/g4mh/bios/ehvm_bios_rh850g4mh_impl.h>

/*-------------------------------------------------------------------------
 intc
-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------
 RH850U2A
-------------------------------------------------------------------------*/
/* initialize */
void ehvm_bios_rh850_initialize_shared(void);
void ehvm_bios_rh850_initialize_corelocal(void);

/*-------------------------------------------------------------------------
 BARRIER
-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 Wakeup Factor
-------------------------------------------------------------------------*/
#define WUP_MASK_ALL                         (ehvm_uint32_t)(0xFFFFFFFFU)
#define WUP_MASK_BIT                         (ehvm_uint32_t)(0x00000001U)
#define WUP_MASK_NONE                        (ehvm_uint32_t)(0x00000000U)

#define WUP_MASK_A0_TNMI                     (ehvm_uint32_t)(WUP_MASK_BIT << 0U)
#define WUP_MASK_A0_INTWDTBA                 (ehvm_uint32_t)(WUP_MASK_BIT << 5U)
#define WUP_MASK_A0_INTP0                    (ehvm_uint32_t)(WUP_MASK_BIT << 6U)
#define WUP_MASK_A0_INTP1                    (ehvm_uint32_t)(WUP_MASK_BIT << 7U)
#define WUP_MASK_A0_INTP2                    (ehvm_uint32_t)(WUP_MASK_BIT << 8U)
#define WUP_MASK_A0_INTP3                    (ehvm_uint32_t)(WUP_MASK_BIT << 9U)
#define WUP_MASK_A0_INTP4                    (ehvm_uint32_t)(WUP_MASK_BIT << 10U)
#define WUP_MASK_A0_INTP5                    (ehvm_uint32_t)(WUP_MASK_BIT << 11U)
#define WUP_MASK_A0_INTP6                    (ehvm_uint32_t)(WUP_MASK_BIT << 12U)
#define WUP_MASK_A0_INTP7                    (ehvm_uint32_t)(WUP_MASK_BIT << 13U)
#define WUP_MASK_A0_INTP8                    (ehvm_uint32_t)(WUP_MASK_BIT << 14U)
#define WUP_MASK_A0_INTP9                    (ehvm_uint32_t)(WUP_MASK_BIT << 15U)
#define WUP_MASK_A0_INTP10                   (ehvm_uint32_t)(WUP_MASK_BIT << 16U)
#define WUP_MASK_A0_INTP11                   (ehvm_uint32_t)(WUP_MASK_BIT << 17U)
#define WUP_MASK_A0_INTP12                   (ehvm_uint32_t)(WUP_MASK_BIT << 18U)
#define WUP_MASK_A0_INTP13                   (ehvm_uint32_t)(WUP_MASK_BIT << 19U)
#define WUP_MASK_A0_INTP14                   (ehvm_uint32_t)(WUP_MASK_BIT << 20U)
#define WUP_MASK_A0_INTP15                   (ehvm_uint32_t)(WUP_MASK_BIT << 21U)
#define WUP_MASK_A0_RESERVED                 (ehvm_uint32_t)((WUP_MASK_BIT << 1U) |      \
                                                        (WUP_MASK_BIT << 2U) |      \
                                                        (WUP_MASK_BIT << 3U) |      \
                                                        (WUP_MASK_BIT << 4U) |      \
                                                        (WUP_MASK_BIT << 22U) |      \
                                                        (WUP_MASK_BIT << 23U) |      \
                                                        (WUP_MASK_BIT << 24U) |      \
                                                        (WUP_MASK_BIT << 25U) |      \
                                                        (WUP_MASK_BIT << 26U) |      \
                                                        (WUP_MASK_BIT << 27U) |      \
                                                        (WUP_MASK_BIT << 28U) |      \
                                                        (WUP_MASK_BIT << 29U) |      \
                                                        (WUP_MASK_BIT << 30U) |      \
                                                        (WUP_MASK_BIT << 31U))

#define WUP_MASK_A1_INTP16                   (ehvm_uint32_t)(WUP_MASK_BIT << 0U)
#define WUP_MASK_A1_INTP17                   (ehvm_uint32_t)(WUP_MASK_BIT << 1U)
#define WUP_MASK_A1_INTP18                   (ehvm_uint32_t)(WUP_MASK_BIT << 2U)
#define WUP_MASK_A1_INTP19                   (ehvm_uint32_t)(WUP_MASK_BIT << 3U)
#define WUP_MASK_A1_INTP20                   (ehvm_uint32_t)(WUP_MASK_BIT << 4U)
#define WUP_MASK_A1_INTP21                   (ehvm_uint32_t)(WUP_MASK_BIT << 5U)
#define WUP_MASK_A1_INTP22                   (ehvm_uint32_t)(WUP_MASK_BIT << 6U)
#define WUP_MASK_A1_INTP23                   (ehvm_uint32_t)(WUP_MASK_BIT << 7U)
#define WUP_MASK_A1_INTP24                   (ehvm_uint32_t)(WUP_MASK_BIT << 8U)
#define WUP_MASK_A1_INTP25                   (ehvm_uint32_t)(WUP_MASK_BIT << 9U)
#define WUP_MASK_A1_INTP26                   (ehvm_uint32_t)(WUP_MASK_BIT << 10U)
#define WUP_MASK_A1_INTP27                   (ehvm_uint32_t)(WUP_MASK_BIT << 11U)
#define WUP_MASK_A1_INTP28                   (ehvm_uint32_t)(WUP_MASK_BIT << 12U)
#define WUP_MASK_A1_INTP29                   (ehvm_uint32_t)(WUP_MASK_BIT << 13U)
#define WUP_MASK_A1_INTP30                   (ehvm_uint32_t)(WUP_MASK_BIT << 14U)
#define WUP_MASK_A1_INTP31                   (ehvm_uint32_t)(WUP_MASK_BIT << 15U)
#define WUP_MASK_A1_INTP32                   (ehvm_uint32_t)(WUP_MASK_BIT << 16U)
#define WUP_MASK_A1_INTP33                   (ehvm_uint32_t)(WUP_MASK_BIT << 17U)
#define WUP_MASK_A1_INTP34                   (ehvm_uint32_t)(WUP_MASK_BIT << 18U)
#define WUP_MASK_A1_INTP35                   (ehvm_uint32_t)(WUP_MASK_BIT << 19U)
#define WUP_MASK_A1_INTP36                   (ehvm_uint32_t)(WUP_MASK_BIT << 20U)
#define WUP_MASK_A1_INTP37                   (ehvm_uint32_t)(WUP_MASK_BIT << 21U)
#define WUP_MASK_A1_INTP38                   (ehvm_uint32_t)(WUP_MASK_BIT << 22U)
#define WUP_MASK_A1_INTP39                   (ehvm_uint32_t)(WUP_MASK_BIT << 23U)
#define WUP_MASK_A1_RESERVED                 (ehvm_uint32_t)((WUP_MASK_BIT << 24U) |      \
                                                        (WUP_MASK_BIT << 25U) |      \
                                                        (WUP_MASK_BIT << 26U) |      \
                                                        (WUP_MASK_BIT << 27U) |      \
                                                        (WUP_MASK_BIT << 28U) |      \
                                                        (WUP_MASK_BIT << 29U) |      \
                                                        (WUP_MASK_BIT << 30U) |      \
                                                        (WUP_MASK_BIT << 31U))

#define WUP_MASK_A2_WUTRG0                   (ehvm_uint32_t)(WUP_MASK_BIT << 0U)
#define WUP_MASK_A2_WUTRG1                   (ehvm_uint32_t)(WUP_MASK_BIT << 1U)
#define WUP_MASK_A2_INTDCUTDI                (ehvm_uint32_t)(WUP_MASK_BIT << 2U)
#define WUP_MASK_A2_INTTAUJ2I0               (ehvm_uint32_t)(WUP_MASK_BIT << 3U)
#define WUP_MASK_A2_INTTAUJ2I1               (ehvm_uint32_t)(WUP_MASK_BIT << 4U)
#define WUP_MASK_A2_INTTAUJ2I2               (ehvm_uint32_t)(WUP_MASK_BIT << 5U)
#define WUP_MASK_A2_INTTAUJ2I3               (ehvm_uint32_t)(WUP_MASK_BIT << 6U)
#define WUP_MASK_A2_INTTAUJ3I0               (ehvm_uint32_t)(WUP_MASK_BIT << 7U)
#define WUP_MASK_A2_INTTAUJ3I1               (ehvm_uint32_t)(WUP_MASK_BIT << 8U)
#define WUP_MASK_A2_INTTAUJ3I2               (ehvm_uint32_t)(WUP_MASK_BIT << 9U)
#define WUP_MASK_A2_INTTAUJ3I3               (ehvm_uint32_t)(WUP_MASK_BIT << 10U)
#define WUP_MASK_A2_INTRTCA01S               (ehvm_uint32_t)(WUP_MASK_BIT << 11U)
#define WUP_MASK_A2_INTRTCA0AL               (ehvm_uint32_t)(WUP_MASK_BIT << 12U)
#define WUP_MASK_A2_INTRTCA0R                (ehvm_uint32_t)(WUP_MASK_BIT << 13U)
#define WUP_MASK_A2_INTADCJ2I0               (ehvm_uint32_t)(WUP_MASK_BIT << 14U)
#define WUP_MASK_A2_INTADCJ2I1               (ehvm_uint32_t)(WUP_MASK_BIT << 15U)
#define WUP_MASK_A2_INTADCJ2I2               (ehvm_uint32_t)(WUP_MASK_BIT << 16U)
#define WUP_MASK_A2_INTADCJ2I3               (ehvm_uint32_t)(WUP_MASK_BIT << 17U)
#define WUP_MASK_A2_INTADCJ2I4               (ehvm_uint32_t)(WUP_MASK_BIT << 18U)
#define WUP_MASK_A2_RESERVED                 (ehvm_uint32_t)((WUP_MASK_BIT << 19U) |      \
                                                        (WUP_MASK_BIT << 20U) |      \
                                                        (WUP_MASK_BIT << 21U) |      \
                                                        (WUP_MASK_BIT << 22U) |      \
                                                        (WUP_MASK_BIT << 23U) |      \
                                                        (WUP_MASK_BIT << 24U) |      \
                                                        (WUP_MASK_BIT << 25U) |      \
                                                        (WUP_MASK_BIT << 26U) |      \
                                                        (WUP_MASK_BIT << 27U) |      \
                                                        (WUP_MASK_BIT << 28U) |      \
                                                        (WUP_MASK_BIT << 29U) |      \
                                                        (WUP_MASK_BIT << 30U) |      \
                                                        (WUP_MASK_BIT << 31U))

#define WUP_MASK_I0_INTRCANGRECC0            (ehvm_uint32_t)(WUP_MASK_BIT << 0U)
#define WUP_MASK_I0_INTRCAN0REC              (ehvm_uint32_t)(WUP_MASK_BIT << 1U)
#define WUP_MASK_I0_INTRCAN1REC              (ehvm_uint32_t)(WUP_MASK_BIT << 2U)
#define WUP_MASK_I0_INTRCAN2REC              (ehvm_uint32_t)(WUP_MASK_BIT << 3U)
#define WUP_MASK_I0_INTRCAN3REC              (ehvm_uint32_t)(WUP_MASK_BIT << 4U)
#define WUP_MASK_I0_INTRCAN4REC              (ehvm_uint32_t)(WUP_MASK_BIT << 5U)
#define WUP_MASK_I0_INTRCAN5REC              (ehvm_uint32_t)(WUP_MASK_BIT << 6U)
#define WUP_MASK_I0_INTRCAN6REC              (ehvm_uint32_t)(WUP_MASK_BIT << 7U)
#define WUP_MASK_I0_INTRCAN7REC              (ehvm_uint32_t)(WUP_MASK_BIT << 8U)
#define WUP_MASK_I0_INTRCANGRECC1            (ehvm_uint32_t)(WUP_MASK_BIT << 9U)
#define WUP_MASK_I0_INTRCAN8REC              (ehvm_uint32_t)(WUP_MASK_BIT << 10U)
#define WUP_MASK_I0_INTRCAN9REC              (ehvm_uint32_t)(WUP_MASK_BIT << 11U)
#define WUP_MASK_I0_INTRCAN10REC             (ehvm_uint32_t)(WUP_MASK_BIT << 12U)
#define WUP_MASK_I0_INTRCAN11REC             (ehvm_uint32_t)(WUP_MASK_BIT << 13U)
#define WUP_MASK_I0_INTRCAN12REC             (ehvm_uint32_t)(WUP_MASK_BIT << 14U)
#define WUP_MASK_I0_INTRCAN13REC             (ehvm_uint32_t)(WUP_MASK_BIT << 15U)
#define WUP_MASK_I0_INTRCAN14REC             (ehvm_uint32_t)(WUP_MASK_BIT << 16U)
#define WUP_MASK_I0_INTRCAN15REC             (ehvm_uint32_t)(WUP_MASK_BIT << 17U)
#define WUP_MASK_I0_RESERVED                 (ehvm_uint32_t)((WUP_MASK_BIT << 18U) |      \
                                                        (WUP_MASK_BIT << 19U) |      \
                                                        (WUP_MASK_BIT << 20U) |      \
                                                        (WUP_MASK_BIT << 21U) |      \
                                                        (WUP_MASK_BIT << 22U) |      \
                                                        (WUP_MASK_BIT << 23U) |      \
                                                        (WUP_MASK_BIT << 24U) |      \
                                                        (WUP_MASK_BIT << 25U) |      \
                                                        (WUP_MASK_BIT << 26U) |      \
                                                        (WUP_MASK_BIT << 27U) |      \
                                                        (WUP_MASK_BIT << 28U) |      \
                                                        (WUP_MASK_BIT << 29U) |      \
                                                        (WUP_MASK_BIT << 30U) |      \
                                                        (WUP_MASK_BIT << 31U))

#define WUP_MASK_I1_INTRLIN30                (ehvm_uint32_t)(WUP_MASK_BIT << 0U)
#define WUP_MASK_I1_INTRLIN31                (ehvm_uint32_t)(WUP_MASK_BIT << 1U)
#define WUP_MASK_I1_INTRLIN32                (ehvm_uint32_t)(WUP_MASK_BIT << 2U)
#define WUP_MASK_I1_INTRLIN33                (ehvm_uint32_t)(WUP_MASK_BIT << 3U)
#define WUP_MASK_I1_INTRLIN34                (ehvm_uint32_t)(WUP_MASK_BIT << 4U)
#define WUP_MASK_I1_INTRLIN35                (ehvm_uint32_t)(WUP_MASK_BIT << 5U)
#define WUP_MASK_I1_INTRLIN36                (ehvm_uint32_t)(WUP_MASK_BIT << 6U)
#define WUP_MASK_I1_INTRLIN37                (ehvm_uint32_t)(WUP_MASK_BIT << 7U)
#define WUP_MASK_I1_INTRLIN38                (ehvm_uint32_t)(WUP_MASK_BIT << 8U)
#define WUP_MASK_I1_INTRLIN39                (ehvm_uint32_t)(WUP_MASK_BIT << 9U)
#define WUP_MASK_I1_INTRLIN310               (ehvm_uint32_t)(WUP_MASK_BIT << 10U)
#define WUP_MASK_I1_INTRLIN311               (ehvm_uint32_t)(WUP_MASK_BIT << 11U)
#define WUP_MASK_I1_INTRLIN312               (ehvm_uint32_t)(WUP_MASK_BIT << 12U)
#define WUP_MASK_I1_INTRLIN313               (ehvm_uint32_t)(WUP_MASK_BIT << 13U)
#define WUP_MASK_I1_INTRLIN314               (ehvm_uint32_t)(WUP_MASK_BIT << 14U)
#define WUP_MASK_I1_INTRLIN315               (ehvm_uint32_t)(WUP_MASK_BIT << 15U)
#define WUP_MASK_I1_INTRLIN316               (ehvm_uint32_t)(WUP_MASK_BIT << 16U)
#define WUP_MASK_I1_INTRLIN317               (ehvm_uint32_t)(WUP_MASK_BIT << 17U)
#define WUP_MASK_I1_INTRLIN318               (ehvm_uint32_t)(WUP_MASK_BIT << 18U)
#define WUP_MASK_I1_INTRLIN319               (ehvm_uint32_t)(WUP_MASK_BIT << 19U)
#define WUP_MASK_I1_INTRLIN320               (ehvm_uint32_t)(WUP_MASK_BIT << 20U)
#define WUP_MASK_I1_INTRLIN321               (ehvm_uint32_t)(WUP_MASK_BIT << 21U)
#define WUP_MASK_I1_INTRLIN322               (ehvm_uint32_t)(WUP_MASK_BIT << 22U)
#define WUP_MASK_I1_INTRLIN323               (ehvm_uint32_t)(WUP_MASK_BIT << 23U)
#define WUP_MASK_I1_RESERVED                 (ehvm_uint32_t)((WUP_MASK_BIT << 24U) |      \
                                                        (WUP_MASK_BIT << 25U) |      \
                                                        (WUP_MASK_BIT << 26U) |      \
                                                        (WUP_MASK_BIT << 27U) |      \
                                                        (WUP_MASK_BIT << 28U) |      \
                                                        (WUP_MASK_BIT << 29U) |      \
                                                        (WUP_MASK_BIT << 30U) |      \
                                                        (WUP_MASK_BIT << 31U))

typedef struct bios_rh850u2a_wakeup_status_st{
    ehvm_uint32_t      wuf0_a0;
    ehvm_uint32_t      wuf0_a1;
    ehvm_uint32_t      wuf0_a2;
    ehvm_uint32_t      wuf0_i0;
    ehvm_uint32_t      wuf0_i1;
    ehvm_uint32_t      wuf1_a0;
    ehvm_uint32_t      wuf1_a1;
    ehvm_uint32_t      wuf1_a2;
    ehvm_uint32_t      wuf1_i0;
    ehvm_uint32_t      wuf1_i1;
} bios_rh850u2a_wakeup_status_config_t;

typedef struct bios_rh850u2a_wakeup_mask_addr_st{
    ehvm_uint32_t*      wufmskaddr0_a0;
    ehvm_uint32_t*      wufmskaddr0_a1;
    ehvm_uint32_t*      wufmskaddr0_a2;
    ehvm_uint32_t*      wufmskaddr0_i0;
    ehvm_uint32_t*      wufmskaddr0_i1;
    ehvm_uint32_t*      wufmskaddr1_a0;
    ehvm_uint32_t*      wufmskaddr1_a1;
    ehvm_uint32_t*      wufmskaddr1_a2;
    ehvm_uint32_t*      wufmskaddr1_i0;
    ehvm_uint32_t*      wufmskaddr1_i1;
} bios_rh850u2a_wakeup_mask_addr_config_t;

typedef struct bios_rh850u2a_wakeup_clear_addr_st{
    ehvm_uint32_t*      wufcaddr0_a0;
    ehvm_uint32_t*      wufcaddr0_a1;
    ehvm_uint32_t*      wufcaddr0_a2;
    ehvm_uint32_t*      wufcaddr0_i0;
    ehvm_uint32_t*      wufcaddr0_i1;
    ehvm_uint32_t*      wufcaddr1_a0;
    ehvm_uint32_t*      wufcaddr1_a1;
    ehvm_uint32_t*      wufcaddr1_a2;
    ehvm_uint32_t*      wufcaddr1_i0;
    ehvm_uint32_t*      wufcaddr1_i1;
} bios_rh850u2a_wakeup_clear_addr_config_t;

#endif /* #ifndef EHVM_BIOS_DEP_IMPL_H */
