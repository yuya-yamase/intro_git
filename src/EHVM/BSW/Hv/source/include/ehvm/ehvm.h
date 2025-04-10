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
[ehvm.h] - EHVM API module header
****************************************************************************/

#ifndef EHVM_H
#define EHVM_H

#include "ehvm_types_stdint.h"
#include "ehvm_types_cfg.h"
#include "ehvm_types_api.h"

extern EhvmConst ehvm_cfg_tbl_cmn_t     ehvm_cfg_tbl_conmon;
extern EhvmConst ehvm_cfg_tbl_t         ehvm_cfg_tbl_pe0;
extern EhvmConst ehvm_cfg_tbl_t         ehvm_cfg_tbl_pe1;
#if ( EHVM_CORE_NUM > EHVM_CORE_NUM_2 )
extern EhvmConst ehvm_cfg_tbl_t         ehvm_cfg_tbl_pe2;
extern EhvmConst ehvm_cfg_tbl_t         ehvm_cfg_tbl_pe3;
#endif /* ( EHVM_CORE_NUM > EHVM_CORE_NUM_2 ) */

/* extern function */
extern void ehvm_user_startup_hook_call(void);

extern void ehvm_user_deep_stop_hook_call_1(void);
extern void ehvm_user_deep_stop_hook_call_2(void);
extern void ehvm_user_deep_stop_hook_call_3(void);

extern void ehvm_user_wakeup_event_init(void);
extern ehvm_std_return_t ehvm_vmm_get_reset_factor_register(ehvm_reset_factor_t * EhvmConstR reset_factor);

extern ehvm_std_return_t ehvm_vmm_get_wakeup_factor(EhvmConstR ehvm_wakeup_factor_size_t wakeup_factor_size, ehvm_wakeup_factor_t * EhvmConstR wakeup_factor_status);
extern ehvm_std_return_t ehvm_vmm_set_wakeup_factor(EhvmConstR ehvm_wakeup_factor_num_t wakeup_factor_num, EhvmConstR ehvm_wakeup_factor_bit_t set_bit_num);
extern ehvm_std_return_t ehvm_vmm_enable_wakeup_factor(EhvmConstR ehvm_wakeup_factor_num_t wakeup_factor_mask_num, EhvmConstR ehvm_wakeup_factor_bit_t enable_bit_num);

extern void ehvm_user_callout_hv_pre_start(void);
extern void ehvm_user_callout_hv_post_shared_init(void);

extern void ehvm_start_hv(void);

#endif /* EHVM_H */
