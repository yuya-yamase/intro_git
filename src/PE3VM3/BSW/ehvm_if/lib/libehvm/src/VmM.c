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
[VmM.c] -  Virtual Communication Channel
****************************************************************************/

#include "VmM.h"
#include "ehvm_VmM_ghs.h"

ehvm_std_return_t ehvm_vmm_exit(ehvm_exit_factor_t vm_exit_factor, ehvm_vm_action_t vm_action)
{

    ehvm_std_return_t receive_result;

    receive_result = ehvm_vmm_exit_hvc(vm_exit_factor, vm_action);

    return receive_result;
}

ehvm_std_return_t ehvm_vmm_get_reset_factor(ehvm_reset_factor_t * reset_factor)
{
    ehvm_std_return_t receive_result;

    receive_result = ehvm_vmm_get_reset_factor_hvc(reset_factor);

    return receive_result;
}

ehvm_std_return_t ehvm_vmm_enable_suppression(void)
{
    ehvm_std_return_t receive_result;

    receive_result = ehvm_vmm_enable_suppression_hvc();

    return receive_result;
}

ehvm_std_return_t ehvm_vmm_disable_suppression(void)
{
    ehvm_std_return_t receive_result;

    receive_result = ehvm_vmm_disable_suppression_hvc();

    return receive_result;
}

ehvm_std_return_t ehvm_vmm_get_vm_status_table(ehvm_vm_status_t * EhvmConstR vm_current_status )
{
    ehvm_std_return_t receive_result;

    receive_result = ehvm_vmm_get_vm_status_table_hvc(vm_current_status);

    return receive_result;
}

ehvm_std_return_t ehvm_vmm_reset_vm(EhvmConstR ehvm_resetype_t resettype, EhvmConstR ehvm_contextId_t contextId, EhvmConstR ehvm_exit_factor_t vm_exit_factor,  EhvmConstR ehvm_vm_action_t vm_action)
{
    ehvm_std_return_t receive_result;

    receive_result = ehvm_vmm_reset_vm_hvc(resettype, contextId, vm_exit_factor, vm_action);

    return receive_result;
}

ehvm_std_return_t ehvm_vmm_get_wakeup_factor(EhvmConstR ehvm_wakeup_factor_size_t wakeup_factor_size, ehvm_wakeup_factor_t * EhvmConstR wakeup_factor_status)
{
    ehvm_std_return_t get_result;
    
    get_result = ehvm_vmm_get_wakeup_factor_hvc(wakeup_factor_size, wakeup_factor_status);
    
    return get_result;
}

ehvm_std_return_t ehvm_vmm_set_wakeup_factor(EhvmConstR ehvm_wakeup_factor_num_t wakeup_factor_num, EhvmConstR ehvm_wakeup_factor_bit_t set_bit_num)
{
    ehvm_std_return_t set_result;
    
    set_result = ehvm_vmm_set_wakeup_factor_hvc(wakeup_factor_num, set_bit_num);
    
    return set_result;
}

ehvm_std_return_t ehvm_vmm_clear_wakeup_factor(EhvmConstR ehvm_wakeup_factor_num_t wakeup_factor_num, EhvmConstR ehvm_wakeup_factor_bit_t clear_bit_num)
{
    ehvm_std_return_t clear_result;
    
    clear_result = ehvm_vmm_clear_wakeup_factor_hvc(wakeup_factor_num, clear_bit_num);
    
    return clear_result;
}

ehvm_std_return_t ehvm_vmm_enable_wakeup_factor(EhvmConstR ehvm_wakeup_factor_num_t wakeup_factor_mask_num, EhvmConstR ehvm_wakeup_factor_bit_t enable_bit_num)
{
    ehvm_std_return_t enable_result;
    
    enable_result = ehvm_vmm_enable_wakeup_factor_hvc(wakeup_factor_mask_num, enable_bit_num);
    
    return enable_result;
}

ehvm_std_return_t ehvm_vmm_disable_wakeup_factor(EhvmConstR ehvm_wakeup_factor_num_t wakeup_factor_mask_num, EhvmConstR ehvm_wakeup_factor_bit_t disable_bit_num)
{
    ehvm_std_return_t disable_result;
    
    disable_result = ehvm_vmm_disable_wakeup_factor_hvc(wakeup_factor_mask_num, disable_bit_num);
    
    return disable_result;
}

ehvm_std_return_t ehvm_vmm_get_all_other_vm_status(ehvm_status_check_t * EhvmConstR  vm_status_check)
{
    ehvm_std_return_t receive_result;

    receive_result = ehvm_vmm_get_all_other_vm_status_hvc(vm_status_check);

    return receive_result;
}

