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
 [ ehvm_types_cfg_mp_dtsg.h ] - DTSG module's configuration types header
****************************************************************************/

#ifndef EHVM_TYPES_CFG_MP_DTSG_H
#define EHVM_TYPES_CFG_MP_DTSG_H

/* type definitions */

typedef struct {
    ehvm_uint32_t                       DtsgPROT;
} ehvm_dtsg_channel_t;

typedef struct {
    ehvm_uint32_t                       DtsgChannelNumber;
    ehvm_uint32_t                       DtsgPROT;
} ehvm_dtsg_n_channel_t;

typedef struct {
    ehvm_uint32_t                       DtsgSPID;
} ehvm_dtsg_spid_t;

typedef struct {
    ehvm_uint32_t                       DtsgNumOfSPID;
    EhvmConst ehvm_dtsg_spid_t*        DtsgSPIDPtr;
    ehvm_uint32_t                       DtsgNumOfDTSG_n;
    EhvmConst ehvm_dtsg_n_channel_t*   DtsgDTSG_n_Ptr;
    ehvm_uint32_t                       DtsgNumOfDTSG_GR;
    EhvmConst ehvm_dtsg_channel_t*     DtsgDTSG_GR_Ptr;
} ehvm_dtsg_config_t;

#endif /* EHVM_TYPES_CFG_MP_DTSG_H */
