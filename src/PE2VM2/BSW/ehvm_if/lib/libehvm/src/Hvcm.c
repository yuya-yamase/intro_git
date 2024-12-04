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
[Hvcm.c] -  HyperVisor Call Management
****************************************************************************/

#include "Hvcm.h"
#include "ehvm_Hvcm_ghs.h"

/*---------------------------------------------------------------------------
  ehvm_hvc_set_access_deny_list

  Input     :   contextId
                denylist
  Output    :   none
  Return    :   ehvm_std_return_t
  Note  :   none
 ---------------------------------------------------------------------------*/
ehvm_std_return_t  ehvm_hvc_set_access_deny_list(
    EhvmConstR ehvm_context_id_t contextId,
    EhvmConstR ehvm_uint32_t * EhvmConstR denylist )
{
    ehvm_std_return_t result;

    result = ehvm_hvc_set_access_deny_list_hvc(contextId,denylist);

    return result;

}

/*---------------------------------------------------------------------------
  ehvm_hvc_get_access_deny_list

  Input     :   contextId
  Output    :   denylist
  Return    :   ehvm_std_return_t
  Note  :   none
 ---------------------------------------------------------------------------*/
ehvm_std_return_t  ehvm_hvc_get_access_deny_list(
    EhvmConstR ehvm_context_id_t contextId,
    ehvm_uint32_t * EhvmConstR denylist )
{
    ehvm_std_return_t result;

    result = ehvm_hvc_get_access_deny_list_hvc(contextId, denylist);

    return result;

}

