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
[Vcc.c] -  Virtual Communication Channel
****************************************************************************/

#include "Vcc.h"
#include "ehvm_Vcc_ghs.h"

/*---------------------------------------------------------------------------
  ehvm_vcc_transmit

  Input     :   vccid
                databuffer
                lenbytes
  Output    :   none
  Return    :   ehvm_std_return_t
  Note  :   none
 ---------------------------------------------------------------------------*/
ehvm_std_return_t ehvm_vcc_transmit(
    EhvmConstR ehvm_uint32_t vccid,
    EhvmConstR ehvm_uint32_t * EhvmConstR databuffer,
    EhvmConstR ehvm_uint32_t lenbytes)
{
    ehvm_std_return_t transmitResult;

    transmitResult = ehvm_Vcc_Transmit_hvc(vccid,databuffer,lenbytes);

    return transmitResult;

}
/*---------------------------------------------------------------------------
  ehvm_vcc_receive

  Input     :   vccid
                lenbytes
  Output    :   buf
                databytes
  Return    :   ehvm_std_return_t
  Note  :   none
 ---------------------------------------------------------------------------*/
ehvm_std_return_t ehvm_vcc_receive(
    EhvmConstR ehvm_uint32_t vccid,
    ehvm_uint32_t* EhvmConstR buf,
    EhvmConstR ehvm_uint32_t lenbytes,
    ehvm_uint32_t* EhvmConstR databytes)
{
    ehvm_std_return_t receiveResult;

    receiveResult = ehvm_Vcc_Receive_hvc(vccid,buf,lenbytes, databytes);

    return receiveResult;

}

/*---------------------------------------------------------------------------
  ehvm_vcc_clear

  Input     :   none
  Output    :   none
  Return    :   ehvm_std_return_t
  Note      :   none
 ---------------------------------------------------------------------------*/
ehvm_std_return_t ehvm_vcc_clear( void )
{
    ehvm_std_return_t clearResult;

    clearResult = ehvm_Vcc_Clear_hvc();

    return clearResult;
}

/*---------------------------------------------------------------------------
  ehvm_vcc_clear_channel

  Input     :   vccid
  Output    :   none
  Return    :   ehvm_std_return_t
  Note  :   none
 ---------------------------------------------------------------------------*/
ehvm_std_return_t ehvm_vcc_clear_channel(
    EhvmConstR ehvm_uint32_t vccid)
{
    ehvm_std_return_t clearChannelResult;
    
    clearChannelResult = ehvm_Vcc_Clear_Channel_hvc(vccid);
    
    return clearChannelResult;
    
}

/*---------------------------------------------------------------------------
  ehvm_vcc_get_overwrite_status

  Input     :   vccid
  Output    :   none
  Return    :   ehvm_std_return_t
  Note  :   none
 ---------------------------------------------------------------------------*/
ehvm_std_return_t ehvm_vcc_get_overwrite_status(
    EhvmConstR ehvm_uint32_t vccid)
{
    ehvm_std_return_t detectResult;

    detectResult = ehvm_Vcc_Get_Overwrite_Status_hvc(vccid);

    return detectResult;
    
}

