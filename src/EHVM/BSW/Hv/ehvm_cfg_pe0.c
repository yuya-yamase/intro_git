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
 [ ehvm_cfg_pe0.c ] - EHVM module's configuration data file
****************************************************************************/

#define EHVM_CFG_PE0_C
#include "ehvm.h"
#include "ehvm_cfg.h"
#include "ehvm_cfg_pe0.h"
#include "ehvm_cfg_memory_pe0.h"

#pragma ghs section rodata=".rodata.ehvm.cfg"

/****************************************************************************************/
/* Hv4mVmConfig                                                                         */
/****************************************************************************************/
static EhvmConst ehvm_guest_int_config_t ehvm_guest_int_configs_pe0[10] = {
    {
        26U,  /* intno */
        PEID_0,  /* Peid */
        GPID_VM0  /* Gpid */
    },
    {
        103U,  /* intno */
        PEID_0,  /* Peid */
        GPID_VM0  /* Gpid */
    },
    {
        121U,  /* intno */
        PEID_0,  /* Peid */
        GPID_VM0  /* Gpid */
    },
    {
        204U,  /* intno */
        PEID_0,  /* Peid */
        GPID_VM0  /* Gpid */
    },
    {
        308U,  /* intno */
        PEID_0,  /* Peid */
        GPID_VM0  /* Gpid */
    },
    {
        309U,  /* intno */
        PEID_0,  /* Peid */
        GPID_VM0  /* Gpid */
    },
    {
        314U,  /* intno */
        PEID_0,  /* Peid */
        GPID_VM0  /* Gpid */
    },
    {
        315U,  /* intno */
        PEID_0,  /* Peid */
        GPID_VM0  /* Gpid */
    },
    {
        320U,  /* intno */
        PEID_0,  /* Peid */
        GPID_VM0  /* Gpid */
    },
    {
        321U,  /* intno */
        PEID_0,  /* Peid */
        GPID_VM0  /* Gpid */
    }
};

static EhvmConst ehvm_vm_exit_int_num_table_t ehvm_vm_exit_int_num_table_pe0[VM_NUM_PE0] = {
    {
        103U,   /* VM0 EXIT */
        121U    /* VM0 RESET */
    }
};

static EhvmConst ehvm_uint32_t ehvm_vm_exit_retry_num_pe0[VM_NUM_PE0] = {
    10U
};

static EhvmConst ehvm_guest_ctx_register_t ehvm_guest_initialize_ctx_list_pe0[VM_NUM_PE0] = {
    {
        0x00000001U,  /* GMSPID */
        0x00000002U   /* GMSPIDLIST */
    }
};

static EhvmConst ehvm_guest_pc_register_t ehvm_guest_initialize_pc_list_pe0[VM_NUM_PE0] = {
    {
        (ehvm_uint32_t)0x00060000U  /* GMEIPC/GMFEPC */
    }
};

static EhvmConst ehvm_guest_peid_register_t ehvm_guest_peid_list_pe0[VM_NUM_PE0] = {
    {
        PEID_0  /* GMPEID */
    }
};

/****************************************************************************************/
/* Hv4mSchedulingConfigSet                                                              */
/****************************************************************************************/
static EhvmConst ehvm_vm_table_info_t ehvm_sch_SchTable_pe0_0[1] = {
    {
#if (PROCESSING_LOAD_MEASURE_TIME > 0)
        4850U,               /* VMCycle */
#else
        400U,               /* VMCycle */
#endif
        GPID_VM0            /* VMId */
    }
};

static EhvmConst ehvm_sch_info_t ehvm_sch_Info_pe0[EHVM_SCH_NUM_OF_PATTERNS_PE0] = {
    {
        &ehvm_sch_SchTable_pe0_0[0],  /* SchTableInfo */
        1U                            /* SchNumOfStgVMPerTbl */
    }
};

static EhvmConst ehvm_vm_margin_info_t ehvm_sch_vm_margin_pe0[VM_NUM_PE0] = {
    0U
};

static EhvmConst ehvm_sch_config_t ehvm_sch_ConfigData_pe0 = {
    &ehvm_sch_Info_pe0[0],        /* SchInfo */
    &ehvm_sch_vm_margin_pe0[0],   /* SchMarginInfo */
    EHVM_SCH_NUM_OF_PATTERNS_PE0  /* SchNumOfSch */
};

/****************************************************************************************/
/* Hv4mWatchdogConfigSet                                                                */
/****************************************************************************************/


static EhvmConst ehvm_vwdt_control_config_t s_VWdtControlConfigData_pe0[VWDT_NUM_OF_VM_USING_VWDT_PE0] = {
    {
        VWDT_NUM_OF_CONF_VM0_PE0,       /* VWdtNumOfVmConfig */
        NULL_PTR                        /* VWdtVmConfig */
    }
};

static EhvmConst ehvm_vwdt_config_t VWdtConfigData_pe0 = {
    VWDT_NUM_OF_VM_USING_VWDT_PE0,   /* VWdtNumOfVm */
    &s_VWdtControlConfigData_pe0[0]  /* VWdtControlConfig */
};

/****************************************************************************************/
/* Hv4mVmSystemControl                                                                  */
/****************************************************************************************/
static EhvmConst ehvm_vm_control_t ehvm_vm_system_control1_pe0[VM_NUM_PE0] = {
    0xFFFFFFFFU
};

static EhvmConst ehvm_vm_control_t ehvm_vm_system_control2_pe0[VM_NUM_PE0] = {
    0xFFFFFFFFU
};

static EhvmConst ehvm_vm_control_t ehvm_vm_system_control3_pe0[VM_NUM_PE0] = {
    0xFFFFFFFFU
};

#pragma ghs section rodata=default

#pragma ghs section bss=".bss.ehvm.cfg.global"

/****************************************************************************************/
/* ehvm_em_err_msg_array                                                                */
/****************************************************************************************/
ehvm_uint32_t  ehvm_em_err_msg_array_VM0_PE0[EM_ERROR_BUFFER_SIZE_VM0_PE0];

#pragma ghs section bss=default

/****************************************************************************************/
/* ehvm_vmsv_VWdtInfo_pe0                                                               */
/****************************************************************************************/
#pragma ghs section bss=".bss.ehvm.cfg"


#pragma ghs section bss=default

#pragma ghs section rodata=".rodata.ehvm.cfg"

static EhvmConst ehvm_vmsv_info_t ehvm_vmsv_VWdtInfo_pe0[VWDT_NUM_OF_VM_USING_VWDT_PE0] = {
    {
        NULL_PTR
    }
};

#pragma ghs section rodata=default

#pragma ghs section rodata=".rodata.ehvm.cfg"

/****************************************************************************************/
/* ehvm_cfg_tbl_pe0                                                                     */
/****************************************************************************************/
EhvmConst ehvm_cfg_tbl_t ehvm_cfg_tbl_pe0 =
{
    0U,                             /* tptm_dividingratio */
    VM_NUM_PE0,                     /* vmnum */
    10U,                            /* guest_int_num */
#if (PROCESSING_LOAD_MEASURE_TIME > 0)
    (ehvm_uint32_t)5000U,           /* hv_cycle */
#else
    (ehvm_uint32_t)500U,           /* hv_cycle */
#endif
    MPU_MPCFG_HBE_PE0,                  /* mpu_mpcfg_hbe */
    MPU_NUM_OF_HOST_ENTRY_PE0,          /* mpu_num_of_host_entry */
    MPU_GUEST_ENTRY_T_PE0,              /* mpu_guest_entry_t */
    ehvm_guest_int_configs_pe0,         /* ehvm_guest_int_configs */
    ehvm_guest_initialize_ctx_list_pe0, /* ehvm_guest_initialize_ctx_list */
    ehvm_guest_initialize_pc_list_pe0,  /* ehvm_guest_initialize_pc_list */
    ehvm_guest_peid_list_pe0,           /* ehvm_guest_peid_list */
    &MpuConfigData_pe0,               /* MpuConfigData */
    &ehvm_sch_ConfigData_pe0,         /* SchConfigData */
    &VWdtConfigData_pe0,              /* VWdtConfigData */
    ehvm_vmsv_VWdtInfo_pe0,           /* VWdtInfo */
    ehvm_vm_exit_int_num_table_pe0,   /* ehvm_vm_exit_int_num_table */
    ehvm_vm_exit_retry_num_pe0,       /* ehvm_vm_exit_retry_num */
    ehvm_vm_system_control1_pe0,      /* ehvm_vm_system_control1 */
    ehvm_vm_system_control2_pe0,      /* ehvm_vm_system_control2 */
    ehvm_vm_system_control3_pe0,      /* ehvm_vm_system_control3 */
    &ehvm_PegConfigData_pe0,          /* ehvm_PegConfigData */
    &ehvm_Intc2gSwitchConfigData_pe0  /* Intc2g_ProtSwitchConfigData */
};


#pragma ghs section rodata=default

/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/

