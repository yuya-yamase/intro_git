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
 [ ehvm_types_cfg_dep_mp_pbg.h ] - PBG module's configuration types header
****************************************************************************/

#ifndef EHVM_TYPES_CFG_DEP_MP_PBG_H
#define EHVM_TYPES_CFG_DEP_MP_PBG_H

/* type definitions */

#define PBG_GROUP_00        (0x00U)
#define PBG_GROUP_10        (0x10U)
#define PBG_GROUP_20        (0x20U)
#define PBG_GROUP_30        (0x30U)
#define PBG_GROUP_40        (0x40U)
#define PBG_GROUP_50        (0x50U)
#define PBG_GROUP_6L0       (0x60U)
#define PBG_GROUP_6L1       (0x61U)
#define PBG_GROUP_6H0       (0x62U)
#define PBG_GROUP_70        (0x70U)
#define PBG_GROUP_80        (0x80U)
#define PBG_GROUP_90        (0x90U)

#define PBG_MODULE_00       (0x00U)
#define PBG_MODULE_01       (0x01U)
#define PBG_MODULE_10       (0x10U)
#define PBG_MODULE_20       (0x20U)
#define PBG_MODULE_21       (0x21U)
#define PBG_MODULE_22       (0x22U)
#define PBG_MODULE_30       (0x30U)
#define PBG_MODULE_31       (0x31U)
#define PBG_MODULE_32       (0x32U)
#define PBG_MODULE_33       (0x33U)
#define PBG_MODULE_40       (0x40U)
#define PBG_MODULE_50       (0x50U)
#define PBG_MODULE_51       (0x51U)
#define PBG_MODULE_52       (0x52U)
#define PBG_MODULE_53       (0x53U)
#define PBG_MODULE_6L0      (0x60U)
#define PBG_MODULE_6L1      (0x61U)
#define PBG_MODULE_6H0      (0x62U)
#define PBG_MODULE_70       (0x70U)
#define PBG_MODULE_80       (0x80U)
#define PBG_MODULE_90       (0x90U)

#define PBG_CHANNEL_0       (0x00U)
#define PBG_CHANNEL_1       (0x01U)
#define PBG_CHANNEL_2       (0x02U)
#define PBG_CHANNEL_3       (0x03U)
#define PBG_CHANNEL_4       (0x04U)
#define PBG_CHANNEL_5       (0x05U)
#define PBG_CHANNEL_6       (0x06U)
#define PBG_CHANNEL_7       (0x07U)
#define PBG_CHANNEL_8       (0x08U)
#define PBG_CHANNEL_9       (0x09U)
#define PBG_CHANNEL_10      (0x0AU)
#define PBG_CHANNEL_11      (0x0BU)
#define PBG_CHANNEL_12      (0x0CU)
#define PBG_CHANNEL_13      (0x0DU)
#define PBG_CHANNEL_14      (0x0EU)
#define PBG_CHANNEL_15      (0x0FU)

typedef struct {
    ehvm_uint32_t                    PbgChannelNumber;
    ehvm_uint32_t                    PbgPROT_0;
    ehvm_uint32_t                    PbgPROT_1;
} ehvm_pbg_channel_t;

typedef struct {
    ehvm_uint32_t                    PbgModuleNumber;
    ehvm_uint32_t                    PbgNumOfPbgChannel;
    EhvmConst ehvm_pbg_channel_t*   PbgChannelPtr;
} ehvm_pbg_module_t;

typedef struct {
    ehvm_uint32_t                    PbgGroupNumber;
    ehvm_uint32_t                    PbgNumOfPbgModule;
    EhvmConst ehvm_pbg_module_t*    PbgModulePtr;
} ehvm_pbg_group_t;

typedef struct {
    ehvm_uint32_t                    PbgNumOfGroup;
    EhvmConst ehvm_pbg_group_t*     PbgGroupPtr;
} ehvm_pbg_config_t;

#endif /* EHVM_TYPES_CFG_DEP_MP_PBG_H */
