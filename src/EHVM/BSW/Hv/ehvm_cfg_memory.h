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
 [ ehvm_cfg_memory.h ] - Memory Protection module's configuration data file
****************************************************************************/

#ifndef EHVM_CFG_MEMORY_H
#define EHVM_CFG_MEMORY_H

#include "ehvm.h"
#include "ehvm_cfg_memory_pe0.h"
#include "ehvm_cfg_memory_pe1.h"
#include "ehvm_cfg_memory_pe2.h"
#include "ehvm_cfg_memory_pe3.h"

#pragma ghs section rodata=".rodata.ehvm.cfg"

#define INTC2G_SWITCH_REGISTER          (INTC2G_SWITCH_ENABLE)
#define MM_NUM_OF_ROMRAM_AREA           (3U)

extern EhvmConst ehvm_mm_common_config_t ehvmMmCommonConfigData;

#pragma ghs section rodata=default

#endif /* EHVM_CFG_MEMORY_H */

/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-2-0-z0001                                        */
/****************************************************************************/

