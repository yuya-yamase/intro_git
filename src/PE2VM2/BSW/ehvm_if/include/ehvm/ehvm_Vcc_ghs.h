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
 [ ehvm_Vcc_ghs.h ] - Memory Protection module's configuration data file
****************************************************************************/
#ifndef EHVM_VCC_GHS_H
#define EHVM_VCC_GHS_H

#include "ehvm_types.h"

extern ehvm_std_return_t ehvm_Vcc_Transmit_hvc(
    EhvmConstR ehvm_uint32_t val,
    EhvmConstR ehvm_uint32_t * EhvmConstR databuffer,
    EhvmConstR ehvm_uint32_t lenbytes);

extern ehvm_std_return_t ehvm_Vcc_Receive_hvc(
    EhvmConstR ehvm_uint32_t vccid,
    ehvm_uint32_t* EhvmConstR buf,
    EhvmConstR ehvm_uint32_t lenbytes,
    ehvm_uint32_t* EhvmConstR databytes);

extern ehvm_std_return_t ehvm_Vcc_Clear_hvc( void );
extern ehvm_std_return_t ehvm_Vcc_Clear_Channel_hvc( EhvmConstR ehvm_uint32_t vccid );
extern ehvm_std_return_t ehvm_Vcc_Get_Overwrite_Status_hvc( EhvmConstR ehvm_uint32_t vccid );

#endif /* #define EHVM_VCC_GHS_H */
