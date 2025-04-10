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
 [ ehvm_VmM_ghs.h ] - Memory Protection module's configuration data file
****************************************************************************/
#ifndef EHVM_VMM_GHS_H
#define EHVM_VMM_GHS_H

#include "ehvm_types.h"

extern ehvm_std_return_t ehvm_vmm_exit_hvc(ehvm_exit_factor_t vm_exit_factor, ehvm_vm_action_t vm_action);
extern ehvm_std_return_t ehvm_vmm_get_reset_factor_hvc(ehvm_reset_factor_t * reset_factor);
extern ehvm_std_return_t ehvm_vmm_enable_suppression_hvc(void);
extern ehvm_std_return_t ehvm_vmm_disable_suppression_hvc(void);
extern ehvm_std_return_t ehvm_vmm_get_vm_status_table_hvc(ehvm_vm_status_t * EhvmConstR vm_current_status );
extern ehvm_std_return_t ehvm_vmm_reset_vm_hvc(EhvmConstR ehvm_resetype_t resettype, EhvmConstR ehvm_contextId_t contextId, EhvmConstR ehvm_exit_factor_t vm_exit_factor,  EhvmConstR ehvm_vm_action_t vm_action);
extern ehvm_std_return_t ehvm_vmm_get_wakeup_factor_hvc(EhvmConstR ehvm_wakeup_factor_size_t wakeup_factor_size, ehvm_wakeup_factor_t * EhvmConstR wakeup_factor_status);
extern ehvm_std_return_t ehvm_vmm_set_wakeup_factor_hvc(EhvmConstR ehvm_wakeup_factor_num_t wakeup_factor_num, EhvmConstR ehvm_wakeup_factor_bit_t set_bit_num);
extern ehvm_std_return_t ehvm_vmm_clear_wakeup_factor_hvc(EhvmConstR ehvm_wakeup_factor_num_t wakeup_factor_num, EhvmConstR ehvm_wakeup_factor_bit_t clear_bit_num);
extern ehvm_std_return_t ehvm_vmm_enable_wakeup_factor_hvc(EhvmConstR ehvm_wakeup_factor_num_t wakeup_factor_mask_num, EhvmConstR ehvm_wakeup_factor_bit_t enable_bit_num);
extern ehvm_std_return_t ehvm_vmm_disable_wakeup_factor_hvc(EhvmConstR ehvm_wakeup_factor_num_t wakeup_factor_mask_num, EhvmConstR ehvm_wakeup_factor_bit_t disable_bit_num);
extern ehvm_std_return_t ehvm_vmm_get_all_other_vm_status_hvc(ehvm_status_check_t * EhvmConstR  vm_status_check);


#endif /* #define EHVM_VMM_GHS_H */
