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
 [ ehvm_cfg_memory_pe3.c ] - Memory Protection module's configuration data file
****************************************************************************/

#include "ehvm.h"
#include "ehvm_cfg_pe3.h"
#include "ehvm_cfg_memory_pe3.h"

#pragma ghs section rodata=".rodata.ehvm.cfg"

/****************************************************************************************/
/* Hv4mMemoryProtectionUnitConfigSet                                                    */
/****************************************************************************************/
static EhvmConst ehvm_mpu_guest_spid_t s_MpuGuestSpidData_VM0_pe3[1] = {
    {
        0x0000000EU  /* MpuSpid */
    }
};

static EhvmConst ehvm_mpu_guest_memory_t s_MpuGuestMemoryData_pe3[VM_NUM_PE3] = {
    {
        GPID_VM0,                       /* MpuGpid */
        1U,                             /* MpuNumOfGuestSpid */
        &s_MpuGuestSpidData_VM0_pe3[0]  /* MpuGuestSpid */
    }
};

static EhvmConst ehvm_mpu_memory_entry_t s_MpuHostEntryData_VM0_pe3[MPU_NUM_OF_VARIABLE_HOST_ENTRY_PE3] = {
    {
        0x00020000U, /* MPLA */
        0xFFFFFFFCU, /* MPUA */
        0x010100BFU  /* MPAT */ /* change from 0x01010080 -> 0x010100BF */
    },
    {
        0x00C00000U, /* MPLA */
        0x00DFFFFCU, /* MPUA */
        0x010100BFU  /* MPAT */
    },
    {
        0xFD608000U, /* MPLA */
        0xFD60FFFCU, /* MPUA */
        0x010100BFU  /* MPAT */
    },
    {
        0xFE040000U, /* MPLA */
        0xFE04FFFCU, /* MPUA */
        0x010100BFU  /* MPAT */
    },
    {
        0xFE140000U, /* MPLA */
        0xFE14FFFCU, /* MPUA */
        0x010100BFU  /* MPAT */
    },
    {
        0xFE500000U, /* MPLA */
        0xFE53FFFCU, /* MPUA */
        0x010100BFU  /* MPAT */
    },
    {
        0xFE820000U, /* MPLA */
        0xFE827FFCU, /* MPUA */
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

static EhvmConst ehvm_mpu_host_memory_t s_MpuHostVariableMemoryData_pe3[VM_NUM_PE3] = {
    {
        &s_MpuHostEntryData_VM0_pe3[0]      /* MpuHostEntryPtr */
    }
};

static EhvmConst ehvm_mpu_memory_entry_t s_MpuHostFixedMemoryData_pe3[MPU_NUM_OF_FIXED_HOST_ENTRY_PE3] = {
    {
        0x00000000U, /* MPLA */
        0xFFFFFFFCU, /* MPUA */
        0x808000BFU  /* MPAT */
    }
};

EhvmConst ehvm_mpu_config_t MpuConfigData_pe3 = {
    VM_NUM_PE3,                           /* MpuNumOfGuest */
    &s_MpuGuestMemoryData_pe3[0],         /* MpuGuestMemoryPtr */
    MPU_NUM_OF_VARIABLE_HOST_ENTRY_PE3,   /* MpuNumOfVariableHostMemory */
    &s_MpuHostVariableMemoryData_pe3[0],  /* MpuVariableHostMemoryPtr */
    MPU_NUM_OF_FIXED_HOST_ENTRY_PE3,      /* MpuNumOfFixedHostEntry */
    &s_MpuHostFixedMemoryData_pe3[0]      /* MpuFixedHostEntryPtr */
};

/****************************************************************************************/
/* Hv4mProcessorElementGuardConfig                                                      */
/****************************************************************************************/
static EhvmConst ehvm_peg_spid_t s_Peg_SpidData_CH3[3] = {
    {
        0x00000001U  /* PEGSPID */
    },
    {
        0x00004000U  /* PEGSPID */
    },
    {
        0x00004000U  /* PEGSPID */
    }
};

static EhvmConst ehvm_peg_prot_t s_Peg_ProtData_CH3[3] = {
    {
        0x01600000U,  /* PEGBAD */
        0x03FF8000U,  /* PEGADV */
        0x00000140U   /* PEGPROT */
    },
    {
        0x01608000U,  /* PEGBAD */
        0x03FF8000U,  /* PEGADV */
        0x00000140U   /* PEGPROT */
    },
    {
        0x03FD0000U,  /* PEGBAD */
        0x03FFC000U,  /* PEGADV */
        0x00000140U   /* PEGPROT */
    }
};

EhvmConst ehvm_peg_config_t ehvm_PegConfigData_pe3 = {
    3U,                      /* PegNumOfSpid */
    &s_Peg_SpidData_CH3[0],  /* PegSpidPtr */
    3U,                      /* PegNumOfProt */
    &s_Peg_ProtData_CH3[0]   /* PegProtPtr */
};

/****************************************************************************************/
/* Hv4mCommonInterruptControllerGuardConfig - Hv4mIntc2gCoreConfig                      */
/****************************************************************************************/
static EhvmConst ehvm_intc2g_n_channel_switch_t s_Intc2g_ChannelSwitchData_VM0_pe3[5] = {
    {
        INTC2GPROT_ADDRESS(109U)  /* Intc2gProtAddress */
    },
    {
        INTC2GPROT_ADDRESS(127U)  /* Intc2gProtAddress */
    },
    {
        INTC2GPROT_ADDRESS(201U)  /* Intc2gProtAddress */
    },
    {
        INTC2GPROT_ADDRESS(202U)  /* Intc2gProtAddress */
    },
    {
        INTC2GPROT_ADDRESS(548U)  /* Intc2gProtAddress */
    }
};

static EhvmConst ehvm_intc2g_prot_switch_t s_Intc2g_ProtSwitchData_pe3[VM_NUM_PE3] = {
    {
        INTC2GMPID_ADDRESS(PEID_3),             /* Intc2gMpidAddress */
        0x0000000EU,                            /* Intc2gSPID */
        5U,                                    /* Intc2gNumOfChannelSwitch */
        &s_Intc2g_ChannelSwitchData_VM0_pe3[0]  /* Intc2gChannelSwitchPtr */
    }
};

EhvmConst ehvm_intc2g_prot_switch_config_t ehvm_Intc2gSwitchConfigData_pe3 = {
    VM_NUM_PE3,                      /* Intc2gNumOfVM */
    &s_Intc2g_ProtSwitchData_pe3[0]  /* Intc2gProtSwitchPtr */
};

#pragma ghs section rodata=default

/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-2                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/

