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
[ehvm_hvcb.h] - Hypervisor Control Block define header
****************************************************************************/

#ifndef EHVM_HVCB_H
#define EHVM_HVCB_H

typedef struct ehvm_hvcb_st {
    EhvmConstR ehvm_uint32_t                                  peid;
    EhvmConstR ehvm_spid_t                               ehvm_host_spid;
    EhvmConst ehvm_cfg_tbl_cmn_t * EhvmConst                ehvm_cfg_tbl_cmn;
    EhvmConst ehvm_cfg_tbl_t * EhvmConst                    ehvm_cfg_tbl;
} ehvm_hvcb_t;

extern EhvmConst ehvm_hvcb_t hvcb_pe0;
extern EhvmConst ehvm_hvcb_t hvcb_pe1;
#if ( EHVM_CORE_NUM > EHVM_CORE_NUM_2 )
extern EhvmConst ehvm_hvcb_t hvcb_pe2;
extern EhvmConst ehvm_hvcb_t hvcb_pe3;
#endif /* ( EHVM_CORE_NUM > EHVM_CORE_NUM_2 ) */

#endif /* #ifndef EHVM_HVCB_H */
