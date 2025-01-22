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
 [ ehvm_cfg_pe2.c ] - EHVM module's configuration data file
****************************************************************************/

#define EHVM_CFG_PE2_C
#include "ehvm.h"
#include "ehvm_cfg.h"
#include "ehvm_cfg_pe2.h"
#include "ehvm_cfg_memory_pe2.h"

#pragma ghs section rodata=".rodata.ehvm.cfg"

/****************************************************************************************/
/* Hv4mVmConfig                                                                         */
/****************************************************************************************/
static EhvmConst ehvm_guest_int_config_t ehvm_guest_int_configs_pe2[14] = {
    {
        50U,  /* intno */
        PEID_2,  /* Peid */
        GPID_VM0  /* Gpid */
    },
    {
        107U,  /* intno */
        PEID_2,  /* Peid */
        GPID_VM0  /* Gpid */
    },
    {
        125U,  /* intno */
        PEID_2,  /* Peid */
        GPID_VM0  /* Gpid */
    },
    {
        200U,  /* intno */
        PEID_2,  /* Peid */
        GPID_VM0  /* Gpid */
    },
    {
        207U,  /* intno */
        PEID_2,  /* Peid */
        GPID_VM0  /* Gpid */
    },
    {
        582U,  /* intno */
        PEID_2,  /* Peid */
        GPID_VM0  /* Gpid */
    },
    {
        685U,  /* intno */
        PEID_2,  /* Peid */
        GPID_VM0  /* Gpid */
    },
    {
        686U,  /* intno */
        PEID_2,  /* Peid */
        GPID_VM0  /* Gpid */
    },
    {
        687U,  /* intno */
        PEID_2,  /* Peid */
        GPID_VM0  /* Gpid */
    },
    {
        688U,  /* intno */
        PEID_2,  /* Peid */
        GPID_VM0  /* Gpid */
    },
    {
        689U,  /* intno */
        PEID_2,  /* Peid */
        GPID_VM0  /* Gpid */
    },
    {
        690U,  /* intno */
        PEID_2,  /* Peid */
        GPID_VM0  /* Gpid */
    },
    {
        691U,  /* intno */
        PEID_2,  /* Peid */
        GPID_VM0  /* Gpid */
    },
    {
        692U,  /* intno */
        PEID_2,  /* Peid */
        GPID_VM0  /* Gpid */
    }
};

static EhvmConst ehvm_vm_exit_int_num_table_t ehvm_vm_exit_int_num_table_pe2[VM_NUM_PE2] = {
    {
        107U,   /* VM0 EXIT */
        125U    /* VM0 RESET */
    }
};

static EhvmConst ehvm_uint32_t ehvm_vm_exit_retry_num_pe2[VM_NUM_PE2] = {
    10U
};

static EhvmConst ehvm_guest_ctx_register_t ehvm_guest_initialize_ctx_list_pe2[VM_NUM_PE2] = {
    {
        0x0000000CU,  /* GMSPID */
        0x00001000U   /* GMSPIDLIST */
    }
};

static EhvmConst ehvm_guest_pc_register_t ehvm_guest_initialize_pc_list_pe2[VM_NUM_PE2] = {
    {
        (ehvm_uint32_t)0x00400000U  /* GMEIPC/GMFEPC */
    }
};

static EhvmConst ehvm_guest_peid_register_t ehvm_guest_peid_list_pe2[VM_NUM_PE2] = {
    {
        PEID_0  /* GMPEID */
    }
};

/****************************************************************************************/
/* Hv4mSchedulingConfigSet                                                              */
/****************************************************************************************/
static EhvmConst ehvm_vm_table_info_t ehvm_sch_SchTable_pe2_0[1] = {
    {
        400U,               /* VMCycle */
        GPID_VM0            /* VMId */
    }
};

static EhvmConst ehvm_sch_info_t ehvm_sch_Info_pe2[EHVM_SCH_NUM_OF_PATTERNS_PE2] = {
    {
        &ehvm_sch_SchTable_pe2_0[0],  /* SchTableInfo */
        1U                            /* SchNumOfStgVMPerTbl */
    }
};

static EhvmConst ehvm_vm_margin_info_t ehvm_sch_vm_margin_pe2[VM_NUM_PE2] = {
    0U
};

static EhvmConst ehvm_sch_config_t ehvm_sch_ConfigData_pe2 = {
    &ehvm_sch_Info_pe2[0],        /* SchInfo */
    &ehvm_sch_vm_margin_pe2[0],   /* SchMarginInfo */
    EHVM_SCH_NUM_OF_PATTERNS_PE2  /* SchNumOfSch */
};

/****************************************************************************************/
/* Hv4mWatchdogConfigSet                                                                */
/****************************************************************************************/


static EhvmConst ehvm_vwdt_control_config_t s_VWdtControlConfigData_pe2[VWDT_NUM_OF_VM_USING_VWDT_PE2] = {
    {
        VWDT_NUM_OF_CONF_VM0_PE2,       /* VWdtNumOfVmConfig */
        NULL_PTR                        /* VWdtVmConfig */
    }
};

static EhvmConst ehvm_vwdt_config_t VWdtConfigData_pe2 = {
    VWDT_NUM_OF_VM_USING_VWDT_PE2,   /* VWdtNumOfVm */
    &s_VWdtControlConfigData_pe2[0]  /* VWdtControlConfig */
};

/****************************************************************************************/
/* Hv4mVmSystemControl                                                                  */
/****************************************************************************************/
static EhvmConst ehvm_vm_control_t ehvm_vm_system_control1_pe2[VM_NUM_PE2] = {
    0x40000008U
};

static EhvmConst ehvm_vm_control_t ehvm_vm_system_control2_pe2[VM_NUM_PE2] = {
    0x00000000U
};

static EhvmConst ehvm_vm_control_t ehvm_vm_system_control3_pe2[VM_NUM_PE2] = {
    0x00000000U
};

#pragma ghs section rodata=default

#pragma ghs section bss=".bss.ehvm.cfg.global"

/****************************************************************************************/
/* ehvm_em_err_msg_array                                                                */
/****************************************************************************************/
ehvm_uint32_t  ehvm_em_err_msg_array_VM0_PE2[EM_ERROR_BUFFER_SIZE_VM0_PE2];

#pragma ghs section bss=default

/****************************************************************************************/
/* ehvm_vmsv_VWdtInfo_pe2                                                               */
/****************************************************************************************/
#pragma ghs section bss=".bss.ehvm.cfg"


#pragma ghs section bss=default

#pragma ghs section rodata=".rodata.ehvm.cfg"

static EhvmConst ehvm_vmsv_info_t ehvm_vmsv_VWdtInfo_pe2[VWDT_NUM_OF_VM_USING_VWDT_PE2] = {
    {
        NULL_PTR
    }
};

#pragma ghs section rodata=default

#pragma ghs section rodata=".rodata.ehvm.cfg"

/****************************************************************************************/
/* ehvm_cfg_tbl_pe2                                                                     */
/****************************************************************************************/
EhvmConst ehvm_cfg_tbl_t ehvm_cfg_tbl_pe2 =
{
    0U,                             /* tptm_dividingratio */
    VM_NUM_PE2,                     /* vmnum */
    14U,                            /* guest_int_num */
    (ehvm_uint32_t)500U,           /* hv_cycle */
    MPU_MPCFG_HBE_PE2,                  /* mpu_mpcfg_hbe */
    MPU_NUM_OF_HOST_ENTRY_PE2,          /* mpu_num_of_host_entry */
    MPU_GUEST_ENTRY_T_PE2,              /* mpu_guest_entry_t */
    ehvm_guest_int_configs_pe2,         /* ehvm_guest_int_configs */
    ehvm_guest_initialize_ctx_list_pe2, /* ehvm_guest_initialize_ctx_list */
    ehvm_guest_initialize_pc_list_pe2,  /* ehvm_guest_initialize_pc_list */
    ehvm_guest_peid_list_pe2,           /* ehvm_guest_peid_list */
    &MpuConfigData_pe2,               /* MpuConfigData */
    &ehvm_sch_ConfigData_pe2,         /* SchConfigData */
    &VWdtConfigData_pe2,              /* VWdtConfigData */
    ehvm_vmsv_VWdtInfo_pe2,           /* VWdtInfo */
    ehvm_vm_exit_int_num_table_pe2,   /* ehvm_vm_exit_int_num_table */
    ehvm_vm_exit_retry_num_pe2,       /* ehvm_vm_exit_retry_num */
    ehvm_vm_system_control1_pe2,      /* ehvm_vm_system_control1 */
    ehvm_vm_system_control2_pe2,      /* ehvm_vm_system_control2 */
    ehvm_vm_system_control3_pe2,      /* ehvm_vm_system_control3 */
    &ehvm_PegConfigData_pe2,          /* ehvm_PegConfigData */
    &ehvm_Intc2gSwitchConfigData_pe2  /* Intc2g_ProtSwitchConfigData */
};


#pragma ghs section rodata=default

/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-2                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/

