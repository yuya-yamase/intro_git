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
[Em.c] -  Error Management
****************************************************************************/

#include "Em.h"
#include "ehvm_Em_ghs.h"

/*---------------------------------------------------------------------------
  ehvm_em_err_msg_receive

  Input     :   contextId
                lenbytes
  Output    :   buf
                databytes
  Return    :   ehvm_std_return_t
  Note  :   none
 ---------------------------------------------------------------------------*/
ehvm_std_return_t ehvm_em_err_msg_receive(
    EhvmConstR ehvm_context_id_t contextId, 
    ehvm_uint32_t* EhvmConstR buf,
    EhvmConstR ehvm_uint32_t lenbytes,
    ehvm_uint32_t* EhvmConstR databytes)
{
    ehvm_std_return_t receiveResult;
    
    receiveResult = ehvm_Em_Receive_hvc( contextId, buf, lenbytes, databytes);
   
    return receiveResult;
    
}

