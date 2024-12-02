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
 [ ehvm_VWdt_ghs.h ] - Memory Protection module's configuration data file
****************************************************************************/
#ifndef EHVM_VWDT_GHS_H
#define EHVM_VWDT_GHS_H

#include "ehvm_types.h"

extern ehvm_std_return_t hvm_VWdt_SetMode_hvc( EhvmConstR ehvm_uint8_t DeviceIndex, EhvmConstR ehvm_vwdt_mode_t VWdtMode );
extern ehvm_std_return_t hvm_VWdt_SetTriggerCondition_hvc( EhvmConstR ehvm_uint8_t DeviceIndex, EhvmConstR ehvm_uint16_t Timeout );

#endif /* #define EHVM_VWDT_GHS_H */
