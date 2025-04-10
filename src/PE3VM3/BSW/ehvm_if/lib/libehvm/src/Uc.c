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
[Uc.c] -  User Callout
****************************************************************************/

#include "Uc.h"
#include "ehvm_Uc_ghs.h"

/*---------------------------------------------------------------------------
  ehvm_uc_call_function

  Input     :   functionid
                functionparams
  Output    :   none
  Return    :   ehvm_std_return_t
  Note      :   none
 ---------------------------------------------------------------------------*/
ehvm_std_return_t ehvm_uc_call_function( EhvmConstR ehvm_user_func_id_t functionid, ehvm_uint32_t* EhvmConstR functionparams )

{
    ehvm_std_return_t result;

    result = ehvm_Uc_Call_Function_hvc( functionid, functionparams );

    return result;
}

