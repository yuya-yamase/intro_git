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
 [ ehvm_types_cfg_uc.h ] - UC module's configuration types header
****************************************************************************/

#ifndef EHVM_TYPES_CFG_UC_H
#define EHVM_TYPES_CFG_UC_H

#include "ehvm_types_api.h"

typedef ehvm_std_return_t (*ehvm_uc_function_t)( ehvm_uint32_t* EhvmConstR functionparams );

typedef struct {
    ehvm_uc_function_t                      UcFnc;
    ehvm_spid_t                             CallSpid;
} ucFuncConfig_t;

typedef struct {
    ehvm_uint8_t                            NumOfFuncCfg;
    EhvmConst ucFuncConfig_t*               FuncConfig;
} ehvm_uc_config_t;

#endif /* EHVM_TYPES_CFG_UC_H */
