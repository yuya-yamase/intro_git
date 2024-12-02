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
 [ ehvm_types_cfg_mp_dmag.h ] - DMAG module's configuration types header
****************************************************************************/

#ifndef EHVM_TYPES_CFG_MP_DMAG_H
#define EHVM_TYPES_CFG_MP_DMAG_H

/* type definitions */

typedef struct {
    ehvm_uint32_t                       DmagPROT;
} ehvm_dmag_channel_t;

typedef struct {
    ehvm_uint32_t                       DmagChannelNumber;
    ehvm_uint32_t                       DmagPROT;
} ehvm_dmag_n_channel_t;

typedef struct {
    ehvm_uint32_t                       DmagSPID;
} ehvm_dmag_spid_t;

typedef struct {
    ehvm_uint32_t                       Dmag_GroupNumber;
    ehvm_uint32_t                       Dmag_NumOfSPID;
    EhvmConst ehvm_dmag_spid_t*        Dmag_SPIDPtr;
    ehvm_uint32_t                       Dmag_NumOfDMAG_n;
    EhvmConst ehvm_dmag_n_channel_t*   Dmag_DMAG_n_Ptr;
    ehvm_uint32_t                       Dmag_NumOfDMAG_GR;
    EhvmConst ehvm_dmag_channel_t*     Dmag_DMAG_GR_Ptr;
    ehvm_uint32_t                       Dmag_NumOfDMAG_DP;
    EhvmConst ehvm_dmag_channel_t*     Dmag_DMAG_DP_Ptr;
} ehvm_dmag_group_t;

typedef struct {
    ehvm_uint32_t                       Dmag_NumOfGroup;
    EhvmConst ehvm_dmag_group_t*       Dmag_GroupPtr;
} ehvm_dmag_config_t;

#endif /* EHVM_TYPES_CFG_MP_DMAG_H */
