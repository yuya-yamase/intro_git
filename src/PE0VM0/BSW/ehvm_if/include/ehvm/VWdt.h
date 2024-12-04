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
[VWdt.h] - VWdt module's header
****************************************************************************/

#ifndef VWDT_H
#define VWDT_H

#include "ehvm_types.h"

#define VWDT_FAST_MODE       (1U)
#define VWDT_VM0_00          (0x00U)
#define VWDT_VM0_01          (0x01U)
#define VWDT_VM0_02          (0x02U)
#define VWDT_VM0_03          (0x03U)
#define VWDT_VM0_04          (0x04U)
#define VWDT_VM0_05          (0x05U)
#define VWDT_VM0_06          (0x06U)
#define VWDT_VM0_07          (0x07U)

typedef ehvm_uint32_t     ehvm_vwdt_mode_t;

extern ehvm_std_return_t ehvm_vwdt_set_mode( EhvmConstR ehvm_uint8_t DeviceIndex, EhvmConstR ehvm_vwdt_mode_t VWdtMode );
extern ehvm_std_return_t ehvm_vwdt_set_trigger_condition( EhvmConstR ehvm_uint8_t DeviceIndex, EhvmConstR ehvm_uint16_t Timeout );

#endif /* VWDT_H */
