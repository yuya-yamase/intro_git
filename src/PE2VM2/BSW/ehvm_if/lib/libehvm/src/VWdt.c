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
[VWdt.c] -  Virtual Watch Dog Timer
****************************************************************************/

#include "VWdt.h"
#include "ehvm_VWdt_ghs.h"

/*---------------------------------------------------------------------------
  ehvm_vwdt_set_mode

  Input     :   DeviceIndex
                WdgMode
  Output    :   none
  Return    :   ehvm_std_return_t
  Note  :   none
 ---------------------------------------------------------------------------*/
ehvm_std_return_t ehvm_vwdt_set_mode( EhvmConstR ehvm_uint8_t DeviceIndex, EhvmConstR ehvm_vwdt_mode_t VWdtMode )
{
    ehvm_std_return_t setModeResult;

    setModeResult = hvm_VWdt_SetMode_hvc( DeviceIndex, VWdtMode );
    return setModeResult;
}

/*---------------------------------------------------------------------------
  ehvm_vwdt_set_trigger_condition

  Input     :   DeviceIndex
                Timeout
  Output    :   none
  Return    :   ehvm_std_return_t
  Note  :   none
 ---------------------------------------------------------------------------*/
ehvm_std_return_t ehvm_vwdt_set_trigger_condition( EhvmConstR ehvm_uint8_t DeviceIndex, EhvmConstR ehvm_uint16_t Timeout )
{
    ehvm_std_return_t setModeResult;

    setModeResult = hvm_VWdt_SetTriggerCondition_hvc( DeviceIndex, Timeout );
    return setModeResult;
}

