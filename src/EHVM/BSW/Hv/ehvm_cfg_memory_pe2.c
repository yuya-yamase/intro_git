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
 [ ehvm_cfg_memory_pe2.c ] - Memory Protection module's configuration data file
****************************************************************************/

#include "ehvm.h"
#include "ehvm_cfg_pe2.h"
#include "ehvm_cfg_memory_pe2.h"

#pragma ghs section rodata=".rodata.ehvm.cfg"

/****************************************************************************************/
/* Hv4mMemoryProtectionUnitConfigSet                                                    */
/****************************************************************************************/
static EhvmConst ehvm_mpu_guest_spid_t s_MpuGuestSpidData_VM0_pe2[1] = {
    {
        0x0000000CU  /* MpuSpid */
    }
};

static EhvmConst ehvm_mpu_guest_memory_t s_MpuGuestMemoryData_pe2[VM_NUM_PE2] = {
    {
        GPID_VM0,                       /* MpuGpid */
        1U,                             /* MpuNumOfGuestSpid */
        &s_MpuGuestSpidData_VM0_pe2[0]  /* MpuGuestSpid */
    }
};

static EhvmConst ehvm_mpu_memory_entry_t s_MpuHostEntryData_VM0_pe2[MPU_NUM_OF_VARIABLE_HOST_ENTRY_PE2] = {
    {
        0x00020000U, /* MPLA */
        0xFFFFFFFCU, /* MPUA */
        0x010100BFU  /* MPAT */ /* change from 0x01010080 -> 0x010100BF */
    },
    {
        0x00800000U, /* MPLA */
        0x009FFFFCU, /* MPUA */
        0x010100BFU  /* MPAT */
    },
    {
        0xFD808000U, /* MPLA */
        0xFD80FFFCU, /* MPUA */
        0x010100BFU  /* MPAT */
    },
    {
        0xFE030000U, /* MPLA */
        0xFE03FFFCU, /* MPUA */
        0x010100BFU  /* MPAT */
    },
    {
        0xFE130000U, /* MPLA */
        0xFE13FFFCU, /* MPUA */
        0x010100BFU  /* MPAT */
    },
    {
        0xFE4C0000U, /* MPLA */
        0xFE4FFFFCU, /* MPUA */
        0x010100BFU  /* MPAT */
    },
    {
        0xFE818000U, /* MPLA */
        0xFE81FFFCU, /* MPUA */
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

static EhvmConst ehvm_mpu_host_memory_t s_MpuHostVariableMemoryData_pe2[VM_NUM_PE2] = {
    {
        &s_MpuHostEntryData_VM0_pe2[0]      /* MpuHostEntryPtr */
    }
};

static EhvmConst ehvm_mpu_memory_entry_t s_MpuHostFixedMemoryData_pe2[MPU_NUM_OF_FIXED_HOST_ENTRY_PE2] = {
    {
        0x00000000U, /* MPLA */
        0xFFFFFFFCU, /* MPUA */
        0x808000BFU  /* MPAT */
    }
};

EhvmConst ehvm_mpu_config_t MpuConfigData_pe2 = {
    VM_NUM_PE2,                           /* MpuNumOfGuest */
    &s_MpuGuestMemoryData_pe2[0],         /* MpuGuestMemoryPtr */
    MPU_NUM_OF_VARIABLE_HOST_ENTRY_PE2,   /* MpuNumOfVariableHostMemory */
    &s_MpuHostVariableMemoryData_pe2[0],  /* MpuVariableHostMemoryPtr */
    MPU_NUM_OF_FIXED_HOST_ENTRY_PE2,      /* MpuNumOfFixedHostEntry */
    &s_MpuHostFixedMemoryData_pe2[0]      /* MpuFixedHostEntryPtr */
};

/****************************************************************************************/
/* Hv4mProcessorElementGuardConfig                                                      */
/****************************************************************************************/
static EhvmConst ehvm_peg_spid_t s_Peg_SpidData_CH2[3] = {
    {
        0x00000001U  /* PEGSPID */
    },
    {
        0x00001000U  /* PEGSPID */
    },
    {
        0x00001000U  /* PEGSPID */
    }
};

static EhvmConst ehvm_peg_prot_t s_Peg_ProtData_CH2[3] = {
    {
        0x01800000U,  /* PEGBAD */
        0x03FF8000U,  /* PEGADV */
        0x00000140U   /* PEGPROT */
    },
    {
        0x01808000U,  /* PEGBAD */
        0x03FF8000U,  /* PEGADV */
        0x00000140U   /* PEGPROT */
    },
    {
        0x03FCC000U,  /* PEGBAD */
        0x03FFC000U,  /* PEGADV */
        0x00000140U   /* PEGPROT */
    }
};

EhvmConst ehvm_peg_config_t ehvm_PegConfigData_pe2 = {
    3U,                      /* PegNumOfSpid */
    &s_Peg_SpidData_CH2[0],  /* PegSpidPtr */
    3U,                      /* PegNumOfProt */
    &s_Peg_ProtData_CH2[0]   /* PegProtPtr */
};

/****************************************************************************************/
/* Hv4mCommonInterruptControllerGuardConfig - Hv4mIntc2gCoreConfig                      */
/****************************************************************************************/
static EhvmConst ehvm_intc2g_n_channel_switch_t s_Intc2g_ChannelSwitchData_VM0_pe2[13] = {
    {
        INTC2GPROT_ADDRESS(107U)  /* Intc2gProtAddress */
    },
    {
        INTC2GPROT_ADDRESS(125U)  /* Intc2gProtAddress */
    },
    {
        INTC2GPROT_ADDRESS(200U)  /* Intc2gProtAddress */
    },
    {
        INTC2GPROT_ADDRESS(207U)  /* Intc2gProtAddress */
    },
    {
        INTC2GPROT_ADDRESS(582U)  /* Intc2gProtAddress */
    },
    {
        INTC2GPROT_ADDRESS(685U)  /* Intc2gProtAddress */
    },
    {
        INTC2GPROT_ADDRESS(686U)  /* Intc2gProtAddress */
    },
    {
        INTC2GPROT_ADDRESS(687U)  /* Intc2gProtAddress */
    },
    {
        INTC2GPROT_ADDRESS(688U)  /* Intc2gProtAddress */
    },
    {
        INTC2GPROT_ADDRESS(689U)  /* Intc2gProtAddress */
    },
    {
        INTC2GPROT_ADDRESS(690U)  /* Intc2gProtAddress */
    },
    {
        INTC2GPROT_ADDRESS(691U)  /* Intc2gProtAddress */
    },
    {
        INTC2GPROT_ADDRESS(692U)  /* Intc2gProtAddress */
    }
};

static EhvmConst ehvm_intc2g_prot_switch_t s_Intc2g_ProtSwitchData_pe2[VM_NUM_PE2] = {
    {
        INTC2GMPID_ADDRESS(PEID_2),             /* Intc2gMpidAddress */
        0x0000000CU,                            /* Intc2gSPID */
        13U,                                    /* Intc2gNumOfChannelSwitch */
        &s_Intc2g_ChannelSwitchData_VM0_pe2[0]  /* Intc2gChannelSwitchPtr */
    }
};

EhvmConst ehvm_intc2g_prot_switch_config_t ehvm_Intc2gSwitchConfigData_pe2 = {
    VM_NUM_PE2,                      /* Intc2gNumOfVM */
    &s_Intc2g_ProtSwitchData_pe2[0]  /* Intc2gProtSwitchPtr */
};

#pragma ghs section rodata=default

/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-2                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/

