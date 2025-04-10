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
 [ ehvm_types_cfg_hvcm.h ] - HVCM module's configuration types header
****************************************************************************/

#ifndef EHVM_TYPES_CFG_HVCM_H
#define EHVM_TYPES_CFG_HVCM_H

/* type definitions */
#define HVCM_NUM_OF_HVC_MAX    (0x80U)

typedef struct {
    EhvmConst ehvm_uint32_t                        hvcAclVmMask;
    EhvmConst ehvm_uint32_t                        hvcFixedAclVmMask;
} ehvm_hvcm_vm_acl_inf_t;

typedef struct {
    EhvmConst ehvm_hvcm_vm_acl_inf_t * EhvmConst  hvcmVmAclConfigInf;
    EhvmConst ehvm_uint8_t                        hvcmNumOfUseHvc;
    EhvmConst ehvm_uint8_t                        hvcmNumOfPe;
    EhvmConst ehvm_uint8_t * EhvmConst                numOfVmByPe;
} ehvm_hvcm_config_t;

typedef struct {
    EhvmConst ehvm_hvcm_config_t * EhvmConst     hvcmConfigData;
    ehvm_uint32_t * EhvmConst                     hvcAccDenyList;
} ehvm_hvcm_info_t;



#endif /* EHVM_TYPES_CFG_HVCM_H */
