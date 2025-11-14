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
 [ ehvm_types_cfg.h ] - Master of configuration types headers
****************************************************************************/

#ifndef EHVM_TYPES_CFG_H
#define EHVM_TYPES_CFG_H

#include "ehvm_types_cfg_hv.h"
#include "ehvm_types_cfg_vcc.h"
#include "ehvm_types_cfg_em.h"
#include "ehvm_types_cfg_intm.h"
#include "ehvm_types_cfg_mp_mpu.h"
#include "ehvm_types_cfg_mp_crg.h"
#include "ehvm_types_cfg_mp_dmag.h"
#include "ehvm_types_cfg_mp_dtsg.h"
#include "ehvm_types_cfg_mp_dmag.h"
#include "ehvm_types_cfg_mp_hbg.h"
#include "ehvm_types_cfg_mp_ibg.h"
#include "ehvm_types_cfg_mp_intc2g.h"
#include "ehvm_types_cfg_mp_peg.h"
#include "ehvm_types_cfg_mp_pbg.h"
#include "ehvm_types_cfg_mp_spid.h"
#include "ehvm_types_cfg_vwdt.h"
#include "ehvm_types_cfg_hvcm.h"
#include "ehvm_types_cfg_uc.h"

typedef struct
{
    ehvm_uint32_t spid;
    ehvm_uint32_t spidlist;
} ehvm_guest_ctx_register_t;

typedef struct
{
    ehvm_uint32_t savedpc;
} ehvm_guest_pc_register_t;

typedef struct
{
    ehvm_uint32_t peid;
} ehvm_guest_peid_register_t;

/* VMSch */
typedef struct{
    ehvm_uint32_t     VMCycle;
    ehvm_gpid_t  VMId;
} ehvm_vm_table_info_t;

typedef struct{
    EhvmConst ehvm_vm_table_info_t*     SchTableInfo;
    ehvm_uint8_t                         SchNumOfStgVMPerTbl;
} ehvm_sch_info_t;

typedef ehvm_uint8_t ehvm_vm_margin_info_t;

typedef struct{
    EhvmConst ehvm_sch_info_t*  SchInfo;
    EhvmConst ehvm_vm_margin_info_t* SchMarginInfo;
    ehvm_uint8_t                 SchNumOfSch;
} ehvm_sch_config_t;


typedef struct {
    ehvm_intno_t      int_sleep_no;
    ehvm_intno_t      int_reset_no;
} ehvm_vm_exit_int_num_table_t;

typedef struct {
    ehvm_uint32_t                      VccIndexOfWp;
    ehvm_uint8_t                       VccNumOfReceiveVM;
    ehvm_vcc_ring_buffer_t*       VccRingBufferInfo;
    ehvm_uint8_t                       VccNumOfFrameOfRingBuffer;
    ehvm_vcc_ring_element_t*      VccRingElementInfo;
} ehvm_vcc_info_t;

/* VMSv */
typedef struct {
    ehvm_uint32_t         VWdtCounter;
    ehvm_uint32_t         VWdtTriggerVal;
    ehvm_vwdt_mode_t VWdtCurrentMode;
    ehvm_uint8_t          VWdtStatus;
} ehvm_vmsv_vm_info_t;

typedef struct {
    ehvm_vmsv_vm_info_t* VWdtVmInfo;
} ehvm_vmsv_info_t;

typedef struct {
    ehvm_uint32_t                      EmIndexOfWp;
    ehvm_uint8_t                       EmNumOfReceiveVM;
    ehvm_em_ring_buffer_t*        EmRingBufferInfo;
    ehvm_uint8_t                       EmNumOfFrameOfRingBuffer;
    ehvm_em_ring_element_t*       EmRingElementInfo;
} ehvm_em_info_t;

typedef struct ehvm_cfg_tbl_cmn_st{
    EhvmConst ehvm_uint8_t * EhvmConst                           SchPatternNumTable;
    ehvm_vcc_info_t * EhvmConst                         VccInfo;
    ehvm_uint32_t *EhvmConst* EhvmConst                               Vcc_Msg_Buffer_Management;
    ehvm_uint8_t *EhvmConst* EhvmConst                                Vcc_Receive_SPID_Management;
    ehvm_vcc_ring_buffer_t *EhvmConst* EhvmConst                 Vcc_Ring_Buffer_Management;
    ehvm_vcc_ring_element_t *EhvmConst* EhvmConst                Vcc_Ring_Element_Management;
    EhvmConst ehvm_vcc_config_t * EhvmConst                 VccConfigData;
    ehvm_em_info_t * EhvmConst                          EmInfo;
    ehvm_uint32_t *EhvmConst* EhvmConst                               Em_Msg_Buffer_Management;
    ehvm_uint8_t *EhvmConst* EhvmConst                                Em_Receive_SPID_Management;
    ehvm_em_ring_buffer_t *EhvmConst* EhvmConst                  Em_Ring_Buffer_Management;
    ehvm_em_ring_element_t *EhvmConst* EhvmConst                 Em_Ring_Element_Management;
    EhvmConst ehvm_em_config_t * EhvmConst                  EmConfigData;
    EhvmConst ehvm_pbg_config_t * EhvmConst                 ehvm_PbgConfigData;
    EhvmConst ehvm_hbg_config_t * EhvmConst                 ehvm_HbgConfigData;
    EhvmConst ehvm_ibg_config_t * EhvmConst                 ehvm_IbgConfigData;
    EhvmConst ehvm_dmag_config_t * EhvmConst                ehvm_DmagConfigData;
    EhvmConst ehvm_dtsg_config_t * EhvmConst                ehvm_DtsgConfigData;
    EhvmConst ehvm_intc2g_config_t * EhvmConst              ehvm_Intc2gConfigData;
    EhvmConst ehvm_crg_config_t * EhvmConst                 ehvm_CrgConfigData;
    EhvmConst ehvm_spid_config_t * EhvmConst                ehvm_SpidConfigData;
    EhvmConst ehvm_intm_common_config_t * EhvmConst         ehvm_IntmCommonConfigData;
    EhvmConst ehvm_uint32_t                                  ehvm_intc2g_switch_register;
    EhvmConst ehvm_uint32_t                                  vm_status_update_int_no;
#if defined ( EHVM_TARGET_U2A )
    EhvmConst ehvm_uint32_t                                  pwrgd_cnt_value_deep_stop;
#endif /* defined ( EHVM_TARGET_U2A ) */
    EhvmConst ehvm_uint32_t                                  master_vm;
    EhvmConst ehvm_uint32_t                                  special_vm_mask;
    EhvmConst ehvm_uint32_t                                  VWdtEnable;
    EhvmConst ehvm_hvcm_info_t * EhvmConst                  HvcmInfo;
    EhvmConst ehvm_uc_config_t * EhvmConst                  ehvm_UcConfig;
    EhvmConst ehvm_uint32_t                                  ehvm_sch_disable_vm_switch_upper_margin;
    EhvmConst ehvm_mm_common_config_t * EhvmConst           MmCommonConfigData;
    EhvmConst ehvm_uint32_t * EhvmConst                     ehvm_hvm_get_lock_timeout_loop_count_info;
    EhvmConst ehvm_uint32_t                                 deep_stop_seq_core_stop_wait_timeout_loop_count;
}ehvm_cfg_tbl_cmn_t;

typedef struct ehvm_cfg_tbl_st{
    EhvmConst ehvm_uint32_t                                  tptm_dividingratio;
    EhvmConst ehvm_uint32_t                                  vmnum;
    EhvmConst ehvm_uint32_t                                  guest_int_num;
    EhvmConst ehvm_uint32_t                                  hv_cycle;
    EhvmConst ehvm_uint32_t                                  mpu_mpcfg_hbe;
    EhvmConst ehvm_uint32_t                                  mpu_num_of_host_entry;
    EhvmConst ehvm_uint32_t                                  mpu_guest_entry_t;
    EhvmConst ehvm_guest_int_config_t * EhvmConst           ehvm_guest_int_configs;
    EhvmConst ehvm_guest_ctx_register_t * EhvmConst         ehvm_guest_initialize_ctx_list;
    EhvmConst ehvm_guest_pc_register_t * EhvmConst          ehvm_guest_initialize_pc_list;
    EhvmConst ehvm_guest_peid_register_t * EhvmConst        ehvm_guest_peid_list;
    EhvmConst ehvm_mpu_config_t * EhvmConst                 MpuConfigData;
    EhvmConst ehvm_sch_config_t * EhvmConst                 SchConfigData;
    EhvmConst ehvm_vwdt_config_t * EhvmConst                VWdtConfigData;
    EhvmConst ehvm_vmsv_info_t* EhvmConst                   VWdtInfo;
    EhvmConst ehvm_vm_exit_int_num_table_t  * EhvmConst     ehvm_vm_exit_int_num_table;
    EhvmConst ehvm_uint32_t * EhvmConst                          ehvm_vm_exit_retry_num;
    EhvmConst ehvm_vm_control_t * EhvmConst                 ehvm_vm_system_control1;
    EhvmConst ehvm_vm_control_t * EhvmConst                 ehvm_vm_system_control2;
    EhvmConst ehvm_vm_control_t * EhvmConst                 ehvm_vm_system_control3;
    EhvmConst ehvm_peg_config_t * EhvmConst                 ehvm_PegConfigData;
    EhvmConst ehvm_intc2g_prot_switch_config_t * EhvmConst  Intc2g_ProtSwitchConfigData;
    EhvmConst ehvm_uint8_t * EhvmConst                      ehvm_vmm_clear_int_flag_config;
}ehvm_cfg_tbl_t;

#endif  /* EHVM_TYPES_CFG_H */
