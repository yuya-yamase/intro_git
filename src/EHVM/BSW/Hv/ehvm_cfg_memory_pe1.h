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
 [ ehvm_cfg_memory_pe1.h ] - Memory Protection module's configuration data file
****************************************************************************/

#ifndef EHVM_CFG_MEMORY_PE1_H
#define EHVM_CFG_MEMORY_PE1_H

#include "ehvm.h"

#pragma ghs section rodata=".rodata.ehvm.cfg"

/* MPU */
#define MPU_NUM_OF_VARIABLE_HOST_ENTRY_PE1  (7U)
#define MPU_NUM_OF_FIXED_HOST_ENTRY_PE1     (1U)
#define MPU_NUM_OF_HOST_ENTRY_PE1           (MPU_NUM_OF_VARIABLE_HOST_ENTRY_PE1 + MPU_NUM_OF_FIXED_HOST_ENTRY_PE1)
#define MPU_GUEST_ENTRY_T_PE1               (MPU_NUM_OF_ENTRY - MPU_NUM_OF_FIXED_HOST_ENTRY_PE1 - 1U)
#define MPU_START_HOST_MANAGEMENT_ENTRY_PE1 (MPU_NUM_OF_ENTRY - MPU_NUM_OF_HOST_ENTRY_PE1)
#define MPU_MPCFG_HBE_PE1                   (ehvm_uint32_t)((ehvm_uint32_t)MPU_START_HOST_MANAGEMENT_ENTRY_PE1 << (ehvm_uint32_t)MPU_MPCFG_HBE_SHIFT)

extern EhvmConst ehvm_mpu_config_t                   MpuConfigData_pe1;
extern EhvmConst ehvm_peg_config_t                   ehvm_PegConfigData_pe1;
extern EhvmConst ehvm_intc2g_prot_switch_config_t    ehvm_Intc2gSwitchConfigData_pe1;

#pragma ghs section rodata=default

#endif /* EHVM_CFG_MEMORY_PE1_H */

/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-2                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/

