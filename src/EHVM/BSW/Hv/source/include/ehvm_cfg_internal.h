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
 [ ehvm_cfg_internal.h ] - EHVM module's configuration data file
****************************************************************************/
#ifndef EHVM_CFG_INTERNAL_H
#define EHVM_CFG_INTERNAL_H

#if defined (EHVM_CFG_INTERNAL_C) || defined (EHVM_CFG_INTERNAL_ASM) /* define groups used in assembler or C language files */
#define VM_NUM_MAX                          (8U)
#define GR_ALL_SIZE                         (32U)
#define BACKUP_GR_STACK_SIZE                (GR_ALL_SIZE)
#define BACKUP_GR_STACK_SIZE_BYTE           (BACKUP_GR_STACK_SIZE * 4U)
#define VM_GR_STACK_SIZE                    (VM_NUM_MAX * GR_ALL_SIZE)
#define VM_GR_STACK_SIZE_BYTE               (VM_GR_STACK_SIZE * 4U)
#define HV_SYSSTACK_SIZE_ONE                (168U)
#define HV_SYSSTACK_SIZE_ALL                (VM_NUM_MAX * HV_SYSSTACK_SIZE_ONE)
#define HV_SYSSTACK_SIZE_BYTE               (HV_SYSSTACK_SIZE_ALL * 4U)

/* initialize register */
#define DEFAULT_PSW                 0x03F08020U          /* FPU | EBV | ID */
#define DEFAULT_INTCFG              0x000F0002U          /* ULNR | EPL | ISPC */
#define DEFAULT_PLMR                0x0000003FU          /* PLM */

/* deep stop sequence register */
#define DEEP_STOP_SEQ_PSWH            0x00000000U
#define DEEP_STOP_SEQ_PSW             0x03F080A0U          /* FPU | EBV | ID | NP */
#define DEEP_STOP_SEQ_FUNC            _ehvm_psm_deep_stop_main

/* initialize guest contextregister */
#define DEFAULT_FPSR                   (0x00200000U)
#define DEFAULT_FPEPC                  DEFAULT_INIT
#define DEFAULT_CTPC                   DEFAULT_INIT
#define DEFAULT_CTPSW                  DEFAULT_INIT
#define DEFAULT_CTBP                   DEFAULT_INIT
#define DEFAULT_MCTL                   DEFAULT_INIT
#define DEFAULT_SCCFG                  DEFAULT_INIT
#define DEFAULT_SCBP                   DEFAULT_INIT
#define DEFAULT_RBCR0                  DEFAULT_INIT
#define DEFAULT_RBCR1                  DEFAULT_INIT
#define DEFAULT_RBNR                   DEFAULT_INIT
#define DEFAULT_RBIP                   DEFAULT_INIT
#define DEFAULT_MCA                    DEFAULT_INIT
#define DEFAULT_MCS                    DEFAULT_INIT
#define DEFAULT_MCR                    DEFAULT_INIT
#define DEFAULT_MCI                    DEFAULT_INIT
#define DEFAULT_MPIDX                  DEFAULT_INIT
#define DEFAULT_GMEIPC                 DEFAULT_INIT
#define DEFAULT_GMEIPSW                (0x00000020U)
#define DEFAULT_GMFEPC                 DEFAULT_INIT
#define DEFAULT_GMFEPSW                (0x00000020U)
#define DEFAULT_GMPSW                  (0x00008020U)
#define DEFAULT_GMMEA                  DEFAULT_INIT
#define DEFAULT_GMMEI                  DEFAULT_INIT
#define DEFAULT_GMEIIC                 DEFAULT_INIT
#define DEFAULT_GMFEIC                 DEFAULT_INIT
#define DEFAULT_GMEBASE                DEFAULT_INIT
#define DEFAULT_GMINTBP                DEFAULT_INIT
#define DEFAULT_GMINTCFG               (0x000F0002U)
#define DEFAULT_GMPLMR                 (0x0000003FU)
#define DEFAULT_GMSVLOCK               DEFAULT_INIT
#define DEFAULT_GMMPM                  (0x00000004U)
#define DEFAULT_GMEIWR                 DEFAULT_INIT
#define DEFAULT_GMFEWR                 DEFAULT_INIT

#define DEFAULT_FEPSWH                 (0x80000000U)     /* GM */

#define HMSPID_PE0                  (0x00U)
#define HMSPID_PE1                  (0x00U)
#if ( EHVM_CORE_NUM > EHVM_CORE_NUM_2 )
#define HMSPID_PE2                  (0x00U)
#define HMSPID_PE3                  (0x00U)
#endif /* ( EHVM_CORE_NUM > EHVM_CORE_NUM_2 ) */

#endif /* EHVM_CFG_INTERNAL_C || EHVM_CFG_INTERNAL_ASM */

#if defined (EHVM_CFG_INTERNAL_C)
#include "ehvm_types_stdint.h"
#define EHVM_TYPES_HV_C
#include "ehvm_types_hv.h"
#include "ehvm_scheduler.h"

#define GUEST_CTX_REG_LIST_FPSR             (0U)
#define GUEST_CTX_REG_LIST_FPEPC            (1U)
#define GUEST_CTX_REG_LIST_CTPC             (2U)
#define GUEST_CTX_REG_LIST_CTPSW            (3U)
#define GUEST_CTX_REG_LIST_CTBP             (4U)
#define GUEST_CTX_REG_LIST_MCTL             (5U)
#define GUEST_CTX_REG_LIST_SCCFG            (6U)
#define GUEST_CTX_REG_LIST_SCBP             (7U)
#define GUEST_CTX_REG_LIST_RBCR0            (8U)
#define GUEST_CTX_REG_LIST_RBCR1            (9U)
#define GUEST_CTX_REG_LIST_RBNR             (10U)
#define GUEST_CTX_REG_LIST_RBIP             (11U)
#define GUEST_CTX_REG_LIST_MCA              (12U)
#define GUEST_CTX_REG_LIST_MCS              (13U)
#define GUEST_CTX_REG_LIST_MCR              (14U)
#define GUEST_CTX_REG_LIST_MCI              (15U)
#define GUEST_CTX_REG_LIST_MPIDX            (16U)
#define GUEST_CTX_REG_LIST_GMEIPC           (17U)
#define GUEST_CTX_REG_LIST_GMEIPSW          (18U)
#define GUEST_CTX_REG_LIST_GMFEPC           (19U)
#define GUEST_CTX_REG_LIST_GMFEPSW          (20U)
#define GUEST_CTX_REG_LIST_GMPSW            (21U)
#define GUEST_CTX_REG_LIST_GMMEA            (22U)
#define GUEST_CTX_REG_LIST_GMMEI            (23U)
#define GUEST_CTX_REG_LIST_GMEIIC           (24U)
#define GUEST_CTX_REG_LIST_GMFEIC           (25U)
#define GUEST_CTX_REG_LIST_GMSPID           (26U)
#define GUEST_CTX_REG_LIST_GMSPIDLIST       (27U)
#define GUEST_CTX_REG_LIST_GMEBASE          (28U)
#define GUEST_CTX_REG_LIST_GMINTBP          (29U)
#define GUEST_CTX_REG_LIST_GMINTCFG         (30U)
#define GUEST_CTX_REG_LIST_GMPLMR           (31U)
#define GUEST_CTX_REG_LIST_GMSVLOC          (32U)
#define GUEST_CTX_REG_LIST_GMMPM            (33U)
#define GUEST_CTX_REG_LIST_GMEIWR           (34U)
#define GUEST_CTX_REG_LIST_GMFEWR           (35U)
#define GUEST_CTX_REG_LIST_SIZE             (36U)
#define VM_STARTING_NUM_PER_CYCLE_MAX       16

/* stack size */
typedef unsigned long                   ehvm_stack_t;
#define EHVM_STACK_SIZE(size)           (((sizeof(ehvm_stack_t) + (ehvm_uint32_t)(size)) - 1UL) / sizeof(ehvm_stack_t))

extern ehvm_uint32_t* ehvm_hv_sysstack_tbl[VM_NUM_MAX];
extern ehvm_uint32_t* ehvm_vm_general_register_stack[VM_NUM_MAX];
extern ehvm_uint32_t ehvm_vm_gr_stack[VM_GR_STACK_SIZE];
extern ehvm_uint32_t hv_sysstack[HV_SYSSTACK_SIZE_ALL];
extern ehvm_uint32_t backup_gr_stack[BACKUP_GR_STACK_SIZE];
extern ehvm_uint32_t hv_sysstack_curbtm;
extern ehvm_sch_host_app_suspend_t ehvm_host_app_suspend[VM_NUM_MAX];
extern ehvm_uint32_t ehvm_hv_sysstackbtm_tbl[VM_NUM_MAX];
extern ehvm_uint32_t* ehvm_switcher_tb_guest_ctx_register_list[VM_NUM_MAX];
extern ehvm_guest_pc_register_t ehvm_guest_pc_list[VM_NUM_MAX];

extern ehvm_uint32_t* ehvm_mpu_tb_memory_entry[VM_NUM_MAX];
extern ehvm_uint32_t* ehvm_mpu_tb_mpid_entry[VM_NUM_MAX];

extern EhvmConst ehvm_uintptr_t * EhvmConst ehvm_mksysstack_bottom_addr_table[PEID_CONTROL_NUM];
#endif /* EHVM_CFG_INTERNAL_C */

#undef EHVM_CFG_INTERNAL_C
#undef EHVM_CFG_INTERNAL_ASM

#endif /* EHVM_CFG_INTERNAL_H */

/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v1-1-0                                              */
/*  BSW plug-in        :v1-0-0                                              */
/****************************************************************************/
