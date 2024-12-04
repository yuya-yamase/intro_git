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
 [ ehvm_cfg_pe1.h ] - EHVM module's configuration data file
****************************************************************************/

#ifndef EHVM_CFG_PE1_H
#define EHVM_CFG_PE1_H

#include "ehvm.h"
#include "ehvm_cfg_pe1.h"

#pragma ghs section rodata=".rodata.ehvm.cfg"

#define VM_NUM_PE1                        (1U)

#define EHVM_SCH_NUM_OF_PATTERNS_PE1      (1U)

#define VWDT_NUM_OF_VM_USING_VWDT_PE1     (1U)
#define VWDT_NUM_OF_CONF_VM0_PE1          (0U)

#define EM_ERROR_MSG_SIZE_VM0_PE1         (0x0000000CU)

#define EM_TOTAL_ERROR_MSG_SIZE_VM0_PE1   ((ehvm_uint32_t)EM_ERROR_HEADDER_SIZE + (ehvm_uint32_t)EM_ERROR_MSG_SIZE_VM0_PE1)

#define EM_ERROR_BUFFER_SIZE_VM0_PE1      ((ehvm_uint32_t)EM_TOTAL_ERROR_MSG_SIZE_VM0_PE1 / (ehvm_uint32_t)EM_MESSAGE_ALIGN)

extern ehvm_uint32_t  ehvm_em_err_msg_array_VM0_PE1[EM_ERROR_BUFFER_SIZE_VM0_PE1];

#pragma ghs section rodata=default

#endif /* EHVM_CFG_PE1_H */

/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-2                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/


