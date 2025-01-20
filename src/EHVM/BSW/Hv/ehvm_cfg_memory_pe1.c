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
 [ ehvm_cfg_memory_pe1.c ] - Memory Protection module's configuration data file
****************************************************************************/

#include "ehvm.h"
#include "ehvm_cfg_pe1.h"
#include "ehvm_cfg_memory_pe1.h"

#pragma ghs section rodata=".rodata.ehvm.cfg"

/****************************************************************************************/
/* Hv4mMemoryProtectionUnitConfigSet                                                    */
/****************************************************************************************/
static EhvmConst ehvm_mpu_guest_spid_t s_MpuGuestSpidData_VM0_pe1[1] = {
    {
        0x00000004U  /* MpuSpid */
    }
};

static EhvmConst ehvm_mpu_guest_memory_t s_MpuGuestMemoryData_pe1[VM_NUM_PE1] = {
    {
        GPID_VM0,                       /* MpuGpid */
        1U,                             /* MpuNumOfGuestSpid */
        &s_MpuGuestSpidData_VM0_pe1[0]  /* MpuGuestSpid */
    }
};

static EhvmConst ehvm_mpu_memory_entry_t s_MpuHostEntryData_VM0_pe1[MPU_NUM_OF_VARIABLE_HOST_ENTRY_PE1] = {
    {
        0x00020000U, /* MPLA */
        0xFFFFFFFCU, /* MPUA */
        0x010100BFU  /* MPAT */ /* change from 0x01010080 -> 0x010100BF */
    },
    {
        0x00400000U, /* MPLA */
        0x005FFFFCU, /* MPUA */
        0x010100BFU  /* MPAT */
    },
    {
        0xFDA08000U, /* MPLA */
        0xFDA0FFFCU, /* MPUA */
        0x010100BFU  /* MPAT */
    },
    {
        0xFE020000U, /* MPLA */
        0xFE02FFFCU, /* MPUA */
        0x010100BFU  /* MPAT */
    },
    {
        0xFE120000U, /* MPLA */
        0xFE12FFFCU, /* MPUA */
        0x010100BFU  /* MPAT */
    },
    {
        0xFE480000U, /* MPLA */
        0xFE4BFFFCU, /* MPUA */
        0x010100BFU  /* MPAT */
    },
    {
        0xFE810000U, /* MPLA */
        0xFE817FFCU, /* MPUA */
        0x010100BFU  /* MPAT */
    },
    {
        0xFFF80000U, /* MPLA */
        0xFFF8FFFCU, /* MPUA */
        0x010100BFU  /* MPAT */
    },
    {
        0xFE000000U, /* MPLA */
//        0xFFBF09FCU, /* MPUA */
        0xFFFFFFFCU, /* MPUA */   /* @zantei: WDTへのアクセスを許可する */
        0x010100BFU  /* MPAT */
    },
    {
        0xFFD90000U, /* MPLA */
        0xFFD9FFFCU, /* MPUA */
        0x010100BFU  /* MPAT */
    },
    {
        0xFF980000U, /* MPLA */
        0xFF98FFFCU, /* MPUA */
        0x010100BFU  /* MPAT */
    }
};

static EhvmConst ehvm_mpu_host_memory_t s_MpuHostVariableMemoryData_pe1[VM_NUM_PE1] = {
    {
        &s_MpuHostEntryData_VM0_pe1[0]      /* MpuHostEntryPtr */
    }
};

static EhvmConst ehvm_mpu_memory_entry_t s_MpuHostFixedMemoryData_pe1[MPU_NUM_OF_FIXED_HOST_ENTRY_PE1] = {
    {
        0x00000000U, /* MPLA */
        0xFFFFFFFCU, /* MPUA */
        0x808000BFU  /* MPAT */
    }
};

EhvmConst ehvm_mpu_config_t MpuConfigData_pe1 = {
    VM_NUM_PE1,                           /* MpuNumOfGuest */
    &s_MpuGuestMemoryData_pe1[0],         /* MpuGuestMemoryPtr */
    MPU_NUM_OF_VARIABLE_HOST_ENTRY_PE1,   /* MpuNumOfVariableHostMemory */
    &s_MpuHostVariableMemoryData_pe1[0],  /* MpuVariableHostMemoryPtr */
    MPU_NUM_OF_FIXED_HOST_ENTRY_PE1,      /* MpuNumOfFixedHostEntry */
    &s_MpuHostFixedMemoryData_pe1[0]      /* MpuFixedHostEntryPtr */
};

/****************************************************************************************/
/* Hv4mProcessorElementGuardConfig                                                      */
/****************************************************************************************/
static EhvmConst ehvm_peg_spid_t s_Peg_SpidData_CH1[3] = {
    {
        0x00000001U  /* PEGSPID */
    },
    {
        0x00000010U  /* PEGSPID */
    },
    {
        0x00000010U  /* PEGSPID */
    }
};

static EhvmConst ehvm_peg_prot_t s_Peg_ProtData_CH1[3] = {
    {
        0x01A00000U,  /* PEGBAD */
        0x03FF8000U,  /* PEGADV */
        0x00000140U   /* PEGPROT */
    },
    {
        0x01A08000U,  /* PEGBAD */
        0x03FF8000U,  /* PEGADV */
        0x00000140U   /* PEGPROT */
    },
    {
        0x03FC8000U,  /* PEGBAD */
        0x03FFC000U,  /* PEGADV */
        0x00000140U   /* PEGPROT */
    }
};

EhvmConst ehvm_peg_config_t ehvm_PegConfigData_pe1 = {
    3U,                      /* PegNumOfSpid */
    &s_Peg_SpidData_CH1[0],  /* PegSpidPtr */
    3U,                      /* PegNumOfProt */
    &s_Peg_ProtData_CH1[0]   /* PegProtPtr */
};

/****************************************************************************************/
/* Hv4mCommonInterruptControllerGuardConfig - Hv4mIntc2gCoreConfig                      */
/****************************************************************************************/
static EhvmConst ehvm_intc2g_n_channel_switch_t s_Intc2g_ChannelSwitchData_VM0_pe1[5] = {
    {
        INTC2GPROT_ADDRESS(48U)  /* Intc2gProtAddress */
    },
    {
        INTC2GPROT_ADDRESS(105U)  /* Intc2gProtAddress */
    },
    {
        INTC2GPROT_ADDRESS(123U)  /* Intc2gProtAddress */
    },
    {
        INTC2GPROT_ADDRESS(199U)  /* Intc2gProtAddress */
    },
    {
        INTC2GPROT_ADDRESS(205U)  /* Intc2gProtAddress */
    }
};

static EhvmConst ehvm_intc2g_prot_switch_t s_Intc2g_ProtSwitchData_pe1[VM_NUM_PE1] = {
    {
        INTC2GMPID_ADDRESS(PEID_1),             /* Intc2gMpidAddress */
        0x00000004U,                            /* Intc2gSPID */
        5U,                                    /* Intc2gNumOfChannelSwitch */
        &s_Intc2g_ChannelSwitchData_VM0_pe1[0]  /* Intc2gChannelSwitchPtr */
    }
};

EhvmConst ehvm_intc2g_prot_switch_config_t ehvm_Intc2gSwitchConfigData_pe1 = {
    VM_NUM_PE1,                      /* Intc2gNumOfVM */
    &s_Intc2g_ProtSwitchData_pe1[0]  /* Intc2gProtSwitchPtr */
};

#pragma ghs section rodata=default

/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-2                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/

