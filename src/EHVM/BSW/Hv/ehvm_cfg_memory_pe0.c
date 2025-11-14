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
 [ ehvm_cfg_memory_pe0.c ] - Memory Protection module's configuration data file
****************************************************************************/

#include "ehvm.h"
#include "ehvm_cfg_pe0.h"
#include "ehvm_cfg_memory_pe0.h"

#pragma ghs section rodata=".rodata.ehvm.cfg"

/****************************************************************************************/
/* Hv4mMemoryProtectionUnitConfigSet                                                    */
/****************************************************************************************/
static EhvmConst ehvm_mpu_guest_spid_t s_MpuGuestSpidData_VM0_pe0[1] = {
    {
        0x00000001U  /* MpuSpid */
    }
};

static EhvmConst ehvm_mpu_guest_memory_t s_MpuGuestMemoryData_pe0[VM_NUM_PE0] = {
    {
        GPID_VM0,                       /* MpuGpid */
        1U,                             /* MpuNumOfGuestSpid */
        &s_MpuGuestSpidData_VM0_pe0[0]  /* MpuGuestSpid */
    }
};

static EhvmConst ehvm_mpu_memory_entry_t s_MpuHostEntryData_VM0_pe0[MPU_NUM_OF_VARIABLE_HOST_ENTRY_PE0] = {
    {
        0x00000000U, /* MPLA */
        0xFFFFFFFCU, /* MPUA */
        0x01010080U  /* MPAT */
    },
    {
        0x00000000U, /* MPLA */
        0x0FFFFFFCU, /* MPUA */
        0x010100BFU  /* MPAT */
    },
    {
        0x10000000U, /* MPLA */
        0xF900FFFCU, /* MPUA */
        0x010100BFU  /* MPAT */
    },
    {
        0xF9010000U, /* MPLA */
        0xFD5FFFFCU, /* MPUA */
        0x010100BFU  /* MPAT */
    },
    {
        0xFD600000U, /* MPLA */
        0xFDFFFFFCU, /* MPUA */
        0x010100BFU  /* MPAT */
    },
    {
        0xFE000000U, /* MPLA */
        0xFEFFFFFCU, /* MPUA */
        0x010100BFU  /* MPAT */
    },
    {
        0xFF000000U, /* MPLA */
        0xFFFFFFFCU, /* MPUA */
        0x010100BFU  /* MPAT */
    }
};

static EhvmConst ehvm_mpu_host_memory_t s_MpuHostVariableMemoryData_pe0[VM_NUM_PE0] = {
    {
        &s_MpuHostEntryData_VM0_pe0[0]      /* MpuHostEntryPtr */
    }
};

static EhvmConst ehvm_mpu_memory_entry_t s_MpuHostFixedMemoryData_pe0[MPU_NUM_OF_FIXED_HOST_ENTRY_PE0] = {
    {
        0x00000000U, /* MPLA */
        0xFFFFFFFCU, /* MPUA */
        0x808000BFU  /* MPAT */
    }
};

EhvmConst ehvm_mpu_config_t MpuConfigData_pe0 = {
    VM_NUM_PE0,                           /* MpuNumOfGuest */
    &s_MpuGuestMemoryData_pe0[0],         /* MpuGuestMemoryPtr */
    MPU_NUM_OF_VARIABLE_HOST_ENTRY_PE0,   /* MpuNumOfVariableHostMemory */
    &s_MpuHostVariableMemoryData_pe0[0],  /* MpuVariableHostMemoryPtr */
    MPU_NUM_OF_FIXED_HOST_ENTRY_PE0,      /* MpuNumOfFixedHostEntry */
    &s_MpuHostFixedMemoryData_pe0[0]      /* MpuFixedHostEntryPtr */
};

/****************************************************************************************/
/* Hv4mProcessorElementGuardConfig                                                      */
/****************************************************************************************/
static EhvmConst ehvm_peg_spid_t s_Peg_SpidData_CH0[3] = {
    {
        0x00000001U  /* PEGSPID */
    },
    {
        0x00000002U  /* PEGSPID */
    },
    {
        0x00000002U  /* PEGSPID */
    }
};

static EhvmConst ehvm_peg_prot_t s_Peg_ProtData_CH0[3] = {
    {
        0xFDC00000U,  /* PEGBAD */
        0x03FF8000U,  /* PEGADV */
        0x00000043U   /* PEGPROT */
    },
    {
        0xFDC08000U,  /* PEGBAD */
        0x03FF8000U,  /* PEGADV */
        0x00000043U   /* PEGPROT */
    },
    {
        0xFFFC4000U,  /* PEGBAD */
        0x03FFC000U,  /* PEGADV */
        0x00000043U   /* PEGPROT */
    }
};

EhvmConst ehvm_peg_config_t ehvm_PegConfigData_pe0 = {
    3U,                      /* PegNumOfSpid */
    &s_Peg_SpidData_CH0[0],  /* PegSpidPtr */
    3U,                      /* PegNumOfProt */
    &s_Peg_ProtData_CH0[0]   /* PegProtPtr */
};

/****************************************************************************************/
/* Hv4mCommonInterruptControllerGuardConfig - Hv4mIntc2gCoreConfig                      */
/****************************************************************************************/
static EhvmConst ehvm_intc2g_n_channel_switch_t s_Intc2g_ChannelSwitchData_VM0_pe0[11] = {
    {
        INTC2GPROT_ADDRESS(103U)  /* Intc2gProtAddress */
    },
    {
        INTC2GPROT_ADDRESS(121U)  /* Intc2gProtAddress */
    },
    {
        INTC2GPROT_ADDRESS(204U)  /* Intc2gProtAddress */
    },
    {
        INTC2GPROT_ADDRESS(308U)  /* Intc2gProtAddress */
    },
    {
        INTC2GPROT_ADDRESS(309U)  /* Intc2gProtAddress */
    },
    {
        INTC2GPROT_ADDRESS(314U)  /* Intc2gProtAddress */
    },
    {
        INTC2GPROT_ADDRESS(315U)  /* Intc2gProtAddress */
    },
    {
        INTC2GPROT_ADDRESS(320U)  /* Intc2gProtAddress */
    },
    {
        INTC2GPROT_ADDRESS(321U)  /* Intc2gProtAddress */
    },
    {
        INTC2GPROT_ADDRESS(334U)  /* Intc2gProtAddress */
    },
    {
        INTC2GPROT_ADDRESS(335U)  /* Intc2gProtAddress */
    }
};

static EhvmConst ehvm_intc2g_prot_switch_t s_Intc2g_ProtSwitchData_pe0[VM_NUM_PE0] = {
    {
        INTC2GMPID_ADDRESS(PEID_0),             /* Intc2gMpidAddress */
        0x00000001U,                            /* Intc2gSPID */
        11U,                                    /* Intc2gNumOfChannelSwitch */
        &s_Intc2g_ChannelSwitchData_VM0_pe0[0]  /* Intc2gChannelSwitchPtr */
    }
};

EhvmConst ehvm_intc2g_prot_switch_config_t ehvm_Intc2gSwitchConfigData_pe0 = {
    VM_NUM_PE0,                      /* Intc2gNumOfVM */
    &s_Intc2g_ProtSwitchData_pe0[0]  /* Intc2gProtSwitchPtr */
};

#pragma ghs section rodata=default

/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-2-0-z0001                                        */
/****************************************************************************/

